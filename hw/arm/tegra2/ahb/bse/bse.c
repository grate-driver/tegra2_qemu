/*
 * ARM NVIDIA Tegra2 emulation.
 *
 * Copyright (c) 2014-2015 Dmitry Osipenko <digetx@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "hw/sysbus.h"
#include "sysemu/dma.h"
#include "qemu/aes.h"

#include "bse.h"
#include "iomap.h"
#include "tegra_trace.h"

#define TYPE_TEGRA_BSE "tegra.bse"
#define TEGRA_BSE(obj) OBJECT_CHECK(tegra_bse, (obj), TYPE_TEGRA_BSE)
#define DEFINE_REG32(reg) reg##_t reg
#define WR_MASKED(r, d, m)  r = (r & ~m##_WRMASK) | (d & m##_WRMASK)

#define CMD_BLKSTARTENGINE  0x0E
#define CMD_DMASETUP        0x10
#define CMD_DMACOMPLETE     0x11
#define CMD_SETTABLE        0x15
#define CMD_MEMDMAVD        0x22

#define SUBCMD_VRAM_SEL             0x1
#define SUBCMD_CRYPTO_TABLE_SEL     0x3
#define SUBCMD_KEY_SCHED_TABLE_SEL  0x4
#define SUBCMD_KEY_TABLE_SEL        0x8

#define SLOTS_MAX_NB    8

#define XOR_DISABLED    0
#define XOR_TOP         2
#define XOR_BOTTOM      3

#define TABLE_IV_OFFSET 240
#define TABLE_SIZE      256

#define DPRINT(off, fmt, ...)                               \
do { TPRINT( "%s" fmt ,                                     \
    off == (TEGRA_BSEA_BASE + 0x1000) ? "BSEA: " : "BSEV: ",\
    ## __VA_ARGS__); } while (0)

enum {
    IDLE = 0,
    DMA_SETUP = 2,
    COPY_TO_VRAM = 4,
    LOADED = 8,
    FAKE = 16,
};

/* Bypass fastboot SSK locking */
static uint8_t fake[] = {
    0x87, 0x92, 0x52, 0x0F,
    0xB0, 0xE0, 0x8A, 0x9F,
    0x0F, 0x61, 0x6B, 0xE3,
    0xC1, 0xAE, 0xB0, 0x7C
};

typedef struct tegra_bse_state {
    SysBusDevice parent_obj;

    qemu_irq irq;

    uint32_t state;
    uint8_t aes_key[SLOTS_MAX_NB][32];
    uint8_t aes_iv[SLOTS_MAX_NB][AES_BLOCK_SIZE];
    uint32_t src_addr;
    bool has_key_sched_gen;
    uint8_t hw_key_sched_length;

    MemoryRegion iomem;
    DEFINE_REG32(cmdque_control);
    DEFINE_REG32(intr_status);
    DEFINE_REG32(bse_config);
    DEFINE_REG32(secure_dest_addr);
    DEFINE_REG32(secure_input_select);
    DEFINE_REG32(secure_config);
    DEFINE_REG32(secure_config_ext);
    DEFINE_REG32(secure_security); /* FIXME shared */
    DEFINE_REG32(secure_hash_result)[4];
    DEFINE_REG32(secure_sec_sel)[SLOTS_MAX_NB];
} tegra_bse;

static const VMStateDescription vmstate_tegra_bse = {
    .name = "tegra.bse",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(state, tegra_bse),
        VMSTATE_UINT8_2DARRAY(aes_key, tegra_bse, SLOTS_MAX_NB, 32),
        VMSTATE_UINT8_2DARRAY(aes_iv, tegra_bse, SLOTS_MAX_NB, AES_BLOCK_SIZE),
        VMSTATE_UINT32(src_addr, tegra_bse),
        VMSTATE_BOOL(has_key_sched_gen, tegra_bse),
        VMSTATE_UINT8(hw_key_sched_length, tegra_bse),
        VMSTATE_UINT32(cmdque_control.reg32, tegra_bse),
        VMSTATE_UINT32(intr_status.reg32, tegra_bse),
        VMSTATE_UINT32(bse_config.reg32, tegra_bse),
        VMSTATE_UINT32(secure_dest_addr.reg32, tegra_bse),
        VMSTATE_UINT32(secure_input_select.reg32, tegra_bse),
        VMSTATE_UINT32(secure_config.reg32, tegra_bse),
        VMSTATE_UINT32(secure_config_ext.reg32, tegra_bse),
        VMSTATE_UINT32(secure_security.reg32, tegra_bse),
        VMSTATE_ARRAY(secure_hash_result, tegra_bse, 4, 0,
                      vmstate_info_uint32, secure_hash_result_t),
        VMSTATE_ARRAY(secure_sec_sel, tegra_bse, SLOTS_MAX_NB, 0,
                      vmstate_info_uint32, secure_sec_sel_t),
        VMSTATE_END_OF_LIST()
    }
};

static void tegra_debug_buffer(tegra_bse *s, uint8_t *buf, int sz)
{
    int i;

    for (i = 0; i < sz * AES_BLOCK_SIZE; i++)
        TPRINT("0x%02X,%s", buf[i],
               ((i + 1) % 16 == 0 || i == sz * AES_BLOCK_SIZE - 1) ? "\n" : " ");
}

static uint64_t tegra_bse_priv_read(void *opaque, hwaddr offset,
                                    unsigned size)
{
    tegra_bse *s = opaque;
    uint64_t ret = 0;
    int i;

    assert(size == 4);

    switch (offset) {
    case CMDQUE_CONTROL_OFFSET:
        ret = s->cmdque_control.reg32;
        break;
    case INTR_STATUS_OFFSET:
        ret = s->intr_status.reg32;

        TRACE_IRQ_LOWER(s->iomem.addr, s->irq);
        break;
    case BSE_CONFIG_OFFSET:
        ret = s->bse_config.reg32;
        break;
    case SECURE_DEST_ADDR_OFFSET:
        ret = s->secure_dest_addr.reg32;
        break;
    case SECURE_INPUT_SELECT_OFFSET:
        ret = s->secure_input_select.reg32;
        break;
    case SECURE_CONFIG_OFFSET:
        ret = s->secure_config.reg32;
        break;
    case SECURE_CONFIG_EXT_OFFSET:
        ret = s->secure_config_ext.reg32;
        break;
    case SECURE_SECURITY_OFFSET:
        ret = s->secure_security.reg32;
        break;
    case SECURE_HASH_RESULT0_OFFSET ... SECURE_HASH_RESULT3_OFFSET:
        i = (offset & 0xf) >> 2;
        ret = s->secure_hash_result[i].reg32;
        break;
    case SECURE_SEC_SEL0_OFFSET ... SECURE_SEC_SEL7_OFFSET:
        i = (offset & 0x1f) >> 2;
        ret = s->secure_sec_sel[i].reg32;
        break;
    default:
        break;
    }

    TRACE_READ(s->iomem.addr, offset, ret);

    return ret;
}

static void tegra_exec_icmd(tegra_bse *s, uint64_t value)
{
    uint8_t opcode = value >> 26;

    if (s->state & DMA_SETUP) {
        DPRINT(s->iomem.addr, "dma set to 0x%08X\n", (uint32_t) value);
        s->src_addr = (uint32_t) value;
        s->state &= ~DMA_SETUP;
        return;
    }

    switch (opcode) {
    case CMD_SETTABLE:
    {
        bse_cmd_setup_table_t set_table_cmd = { .reg32 = value };
        dma_addr_t table_addr = TEGRA_IRAM_BASE;

        if (set_table_cmd.cmd1 & SUBCMD_KEY_TABLE_SEL &&
                set_table_cmd.cmd3 == SUBCMD_CRYPTO_TABLE_SEL)
        {
            int slot = set_table_cmd.cmd1 & 0x7;

            if (set_table_cmd.cmd2 == SUBCMD_VRAM_SEL) {
                DPRINT(s->iomem.addr, "cmd: opcode=CMD_SETTABLE fetch to VRAM\n");
            } else {
                table_addr += set_table_cmd.key_table_phy_addr << 2;

                DPRINT(s->iomem.addr, "cmd: opcode=CMD_SETTABLE fetch key "
                                      "@0x%X [slot=%d]\n",
                        (uint32_t) table_addr, slot);

                if (s->secure_sec_sel[slot].keyupdate_enb)
                    dma_memory_read(&address_space_memory, table_addr,
                                    s->aes_key[slot], 32);
            }
            break;
        }

        DPRINT(s->iomem.addr, "cmd: opcode=CMD_SETTABLE unknown sub_cmd "
                              "cmd1=%X undefined_bits=%X cmd2=%X cmd3=%X\n",
                set_table_cmd.cmd1, set_table_cmd.undefined_bits,
                set_table_cmd.cmd2, set_table_cmd.cmd3);
        break;
    }
    case CMD_DMASETUP:
        DPRINT(s->iomem.addr, "cmd: opcode=CMD_DMASETUP\n");
        s->state |= DMA_SETUP;
        break;
    case CMD_DMACOMPLETE:
        DPRINT(s->iomem.addr, "cmd: opcode=CMD_DMACOMPLETE\n");
        s->state = IDLE;
        break;
    case CMD_BLKSTARTENGINE:
    {
        bse_cmd_block_count_t cmd = { .reg32 = value };
        int xor_pos = s->secure_input_select.secure_xor_pos;
        int slot = s->secure_config.secure_key_index;
        int rng_en = s->secure_input_select.secure_rng_enb;
        int blk_cnt = cmd.block_count + 1;
        hwaddr len_out = AES_BLOCK_SIZE * blk_cnt;
        hwaddr len_in = AES_BLOCK_SIZE * blk_cnt;
        dma_addr_t dma_src_addr = s->src_addr;
        dma_addr_t dma_dst_addr = s->secure_dest_addr.reg32;
        int is_enc = s->secure_input_select.secure_core_sel;
        int key_len = s->secure_input_select.input_key_len;
        void *buffer_in;
        void *buffer_out;
        AES_KEY key;

        DPRINT(s->iomem.addr, "cmd: opcode=CMD_BLKSTARTENGINE block_count=%d\n",
                blk_cnt);

        buffer_in = dma_memory_map(&address_space_memory,
                                   dma_src_addr, &len_in,
                                   DMA_DIRECTION_TO_DEVICE);

        buffer_out = dma_memory_map(&address_space_memory,
                                    dma_dst_addr, &len_out,
                                    DMA_DIRECTION_FROM_DEVICE);

        g_assert(buffer_in != NULL);
        g_assert(buffer_out != NULL);

        if (s->state & FAKE) {
            DPRINT(s->iomem.addr, "return fake\n");
            memcpy(buffer_out, fake, sizeof(fake));
            goto unmap;
        }

        if (is_enc)
            AES_set_encrypt_key(s->aes_key[slot], key_len, &key);
        else
            AES_set_decrypt_key(s->aes_key[slot], key_len, &key);

        if (xor_pos >> 1) {
            DPRINT(s->iomem.addr, "%s using CBC algo 0x%08X -> 0x%08X key_len=%d\n",
                   is_enc ? "encrypting" : "decrypting", s->src_addr,
                   s->secure_dest_addr.reg32, key_len);

            DPRINT(s->iomem.addr, "--------- IV [SLOT=%d] --------\n", slot);
            tegra_debug_buffer(s, s->aes_iv[slot], 1);

            DPRINT(s->iomem.addr, "--------- KEY [SLOT=%d] --------\n", slot);
            tegra_debug_buffer(s, s->aes_key[slot], 1);

            DPRINT(s->iomem.addr, "----------- IN %s ----------\n",
                   is_enc ? "CLEARTEXT" : "CIPHER");
            tegra_debug_buffer(s, buffer_in, blk_cnt);

            AES_cbc_encrypt(buffer_in, buffer_out, blk_cnt * AES_BLOCK_SIZE,
                            &key, s->aes_iv[slot], is_enc);

            DPRINT(s->iomem.addr, "----------- OUT %s ----------\n",
                   is_enc ? "CIPHER" : "CLEARTEXT");
            tegra_debug_buffer(s, buffer_out, blk_cnt);

            goto unmap;
        }

        /* presume ECB mode */
        if (!rng_en) {
            int i;

            DPRINT(s->iomem.addr, "%s using ECB algo 0x%08X -> 0x%08X\n",
                   is_enc ? "encrypting" : "decrypting",
                   s->src_addr, s->secure_dest_addr.reg32);

            DPRINT(s->iomem.addr, "--------- KEY [SLOT=%d] --------\n", slot);
            tegra_debug_buffer(s, s->aes_key[slot], 1);

            DPRINT(s->iomem.addr, "----------- IN %s ----------\n",
                    is_enc ? "CLEARTEXT" : "CIPHER");
            tegra_debug_buffer(s, buffer_in, blk_cnt);

            for (i = 0; i < blk_cnt; i++) {
                uint32_t offset = i * AES_BLOCK_SIZE;

                if (is_enc)
                    AES_encrypt(buffer_in + offset, buffer_out + offset, &key);
                else
                    AES_decrypt(buffer_in + offset, buffer_out + offset, &key);
            }

            DPRINT(s->iomem.addr, "----------- OUT %s ----------\n",
                   is_enc ? "CIPHER" : "CLEARTEXT");
            tegra_debug_buffer(s, buffer_out, blk_cnt);

            goto unmap;
        }

        DPRINT(s->iomem.addr, "unimplemented!!!!\n");
        g_assert_not_reached();

unmap:
        dma_memory_unmap(&address_space_memory, buffer_in, dma_src_addr,
                            DMA_DIRECTION_TO_DEVICE, len_in);

        dma_memory_unmap(&address_space_memory, buffer_out, dma_dst_addr,
                            DMA_DIRECTION_FROM_DEVICE, len_out);
        s->state = IDLE;

        TRACE_IRQ_RAISE(s->iomem.addr, s->irq);

        break;
    }
    case CMD_MEMDMAVD:
        DPRINT(s->iomem.addr, "cmd: opcode=CMD_MEMDMAVD\n");
        break;
    case 0x1F:
        s->state |= FAKE;
        break;
    default:
        DPRINT(s->iomem.addr, "cmd: unknown opcode=0x%02X\n", opcode);
    }
}

static void tegra_bse_priv_write(void *opaque, hwaddr offset,
                                 uint64_t value, unsigned size)
{
    tegra_bse *s = opaque;
    int i;

    assert(size == 4);

    switch (offset) {
    case ICMDQUE_WR_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, value, value);
        tegra_exec_icmd(s, value);
        break;
    case CMDQUE_CONTROL_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->cmdque_control.reg32, value);
        s->cmdque_control.reg32 = value;
        break;
    case INTR_STATUS_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->intr_status.reg32, value & INTR_STATUS_WRMASK);
        WR_MASKED(s->intr_status.reg32, ~value, INTR_STATUS);
        break;
    case BSE_CONFIG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->bse_config.reg32, value);
        s->bse_config.reg32 = value;
        break;
    case SECURE_DEST_ADDR_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->secure_dest_addr.reg32, value);
        s->secure_dest_addr.reg32 = value;
        break;
    case SECURE_INPUT_SELECT_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->secure_input_select.reg32, value);
        s->secure_input_select.reg32 = value;
        break;
    case SECURE_CONFIG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->secure_config.reg32, value);
        s->secure_config.reg32 = value;
        break;
    case SECURE_CONFIG_EXT_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->secure_config_ext.reg32, value);
        s->secure_config_ext.reg32 = value;
        break;
    case SECURE_SECURITY_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->secure_security.reg32, value);
        s->secure_security.reg32 = value;
        break;
    case SECURE_HASH_RESULT0_OFFSET ... SECURE_HASH_RESULT3_OFFSET:
        i = (offset & 0xf) >> 2;

        TRACE_WRITE(s->iomem.addr, offset, s->secure_hash_result[i].reg32, value);
        s->secure_hash_result[i].reg32 = value;
        break;
    case SECURE_SEC_SEL0_OFFSET ... SECURE_SEC_SEL7_OFFSET:
        i = (offset & 0x1f) >> 2;

        TRACE_WRITE(s->iomem.addr, offset, s->secure_sec_sel[i].reg32, value);
        s->secure_sec_sel[i].reg32 = value;
        break;
    default:
        TRACE_WRITE(s->iomem.addr, offset, 0, value);
        break;
    }
}

static void tegra_bse_priv_reset(DeviceState *dev)
{
    tegra_bse *s = TEGRA_BSE(dev);
    int i;

    s->cmdque_control.reg32 = CMDQUE_CONTROL_RESET;
    s->intr_status.reg32 = INTR_STATUS_RESET;
    s->bse_config.reg32 = BSE_CONFIG_RESET;
    s->secure_dest_addr.reg32 = SECURE_DEST_ADDR_RESET;
    s->secure_input_select.reg32 = SECURE_INPUT_SELECT_RESET;
    s->secure_config.reg32 = SECURE_CONFIG_RESET;
    s->secure_config_ext.reg32 = SECURE_CONFIG_EXT_RESET;
    s->secure_security.reg32 = SECURE_SECURITY_RESET;

    for (i = 0; i < 4; i++)
        s->secure_hash_result[i].reg32 = SECURE_HASH_RESULT_RESET;

    for (i = 0; i < SLOTS_MAX_NB; i++)
        s->secure_sec_sel[i].reg32 = SECURE_SEC_SEL_RESET;

    memset(s->aes_iv, 0, AES_BLOCK_SIZE * SLOTS_MAX_NB);
    memset(s->aes_key, 0, 32 * SLOTS_MAX_NB);

    s->state = IDLE;
}

static const MemoryRegionOps tegra_bse_mem_ops = {
    .read = tegra_bse_priv_read,
    .write = tegra_bse_priv_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static int tegra_bse_priv_init(SysBusDevice *dev)
{
    tegra_bse *s = TEGRA_BSE(dev);

    memory_region_init_io(&s->iomem, OBJECT(dev), &tegra_bse_mem_ops, s,
                          "tegra.bse", TEGRA_BSEA_SIZE);
    sysbus_init_mmio(dev, &s->iomem);

    sysbus_init_irq(SYS_BUS_DEVICE(dev), &s->irq);

    return 0;
}

static Property tegra_bse_props[] = {
    DEFINE_PROP_BOOL("key_sched_gen_supported", tegra_bse,
                     has_key_sched_gen, false),
    DEFINE_PROP_UINT8("hw_key_sched_length", tegra_bse,
                      hw_key_sched_length, 0),
    DEFINE_PROP_END_OF_LIST()
};

static void tegra_bse_class_init(ObjectClass *klass, void *data)
{
    SysBusDeviceClass *k = SYS_BUS_DEVICE_CLASS(klass);
    DeviceClass *dc = DEVICE_CLASS(klass);

    k->init = tegra_bse_priv_init;
    dc->vmsd = &vmstate_tegra_bse;
    dc->props = tegra_bse_props;
    dc->reset = tegra_bse_priv_reset;
}

static const TypeInfo tegra_bse_info = {
    .name = TYPE_TEGRA_BSE,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(tegra_bse),
    .class_init = tegra_bse_class_init,
};

static void tegra_bse_register_types(void)
{
    type_register_static(&tegra_bse_info);
}

type_init(tegra_bse_register_types)