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

/* Autogenerated from TRM v02p */

#ifndef TEGRA_EVP_H
#define TEGRA_EVP_H

#define EVP_RESET_VECTOR_OFFSET 0x0
#define EVP_RESET_VECTOR_RESET  0xFFF00000
typedef union evp_reset_vector_u {
    struct {
        unsigned int reset_vector:32;       /* RESET Exception Vector Pointer  */
    };

    uint32_t reg32;
} evp_reset_vector_t;

#define EVP_UNDEF_VECTOR_OFFSET 0x4
#define EVP_UNDEF_VECTOR_RESET  0xFFF00004
typedef union evp_undef_vector_u {
    struct {
        unsigned int undef_vector:32;       /* Undefined Exception Vector Pointer */
    };

    uint32_t reg32;
} evp_undef_vector_t;

#define EVP_SWI_VECTOR_OFFSET 0x8
#define EVP_SWI_VECTOR_RESET  0xFFF00008
typedef union evp_swi_vector_u {
    struct {
        unsigned int swi_vector:32;         /* Software Interrupt Vector Pointer */
    };

    uint32_t reg32;
} evp_swi_vector_t;

#define EVP_PREFETCH_ABORT_VECTOR_OFFSET 0xC
#define EVP_PREFETCH_ABORT_VECTOR_RESET  0xFFF0000C
typedef union evp_prefetch_abort_vector_u {
    struct {
        unsigned int pre_abort_vector:32;   /* Code Prefetch ABORT Vector Pointer  */
    };

    uint32_t reg32;
} evp_prefetch_abort_vector_t;

#define EVP_DATA_ABORT_VECTOR_OFFSET 0x10
#define EVP_DATA_ABORT_VECTOR_RESET  0xFFF00010
typedef union evp_data_abort_vector_u {
    struct {
        unsigned int data_abort_vector:32;  /* Data ABORT Vector Pointer */
    };

    uint32_t reg32;
} evp_data_abort_vector_t;

#define EVP_RSVD_VECTOR_OFFSET 0x14
#define EVP_RSVD_VECTOR_RESET  0xFFF00014
typedef union evp_rsvd_vector_u {
    struct {
        unsigned int rsvd_vector:32;        /* Reserved Exception Vector Pointer */
    };

    uint32_t reg32;
} evp_rsvd_vector_t;

#define EVP_IRQ_VECTOR_OFFSET 0x18
#define EVP_IRQ_VECTOR_RESET  0xFFF00018
typedef union evp_irq_vector_u {
    struct {
        unsigned int irq_vector:32;         /* IRQ Vector Pointer  */
    };

    uint32_t reg32;
} evp_irq_vector_t;

#define EVP_FIQ_VECTOR_OFFSET 0x1C
#define EVP_FIQ_VECTOR_RESET  0xFFF00000
typedef union evp_fiq_vector_u {
    struct {
        unsigned int fiq_vector:32;         /* FIQ Vector Pointer  */
    };

    uint32_t reg32;
} evp_fiq_vector_t;

#define EVP_IRQ_STS_OFFSET 0x20
#define EVP_IRQ_STS_RESET  0x00000080
typedef union evp_irq_sts_u {
    struct {
        unsigned int irq_sts:32;            /* FFS (from lsb) IRQ index  (0x80 indicates no active IRQ) */
    };

    uint32_t reg32;
} evp_irq_sts_t;

#define EVP_PRI_IRQ_STS_OFFSET 0x24
#define EVP_PRI_IRQ_STS_RESET  0x00000080
typedef union evp_pri_irq_sts_u {
    struct {
        unsigned int pri_irq_sts:32;        /* Current highest priority active IRQ (0x80 indicates no active priority IRQ) */
    };

    uint32_t reg32;
} evp_pri_irq_sts_t;

#define EVP_FIQ_STS_OFFSET 0x28
#define EVP_FIQ_STS_RESET  0x00000080
typedef union evp_fiq_sts_u {
    struct {
        unsigned int fiq_sts:32;            /* FFS (from lsb) FIQ index (0x80 indicates no active FIQ) */
    };

    uint32_t reg32;
} evp_fiq_sts_t;

#define EVP_PRI_FIQ_STS_OFFSET 0x2C
#define EVP_PRI_FIQ_STS_RESET  0x00000080
typedef union evp_pri_fiq_sts_u {
    struct {
        unsigned int pri_fiq_sts:32;        /* Current highest priority active FIQ (0x80 indicates no active priority FIQ) */
    };

    uint32_t reg32;
} evp_pri_fiq_sts_t;

#define EVP_PRI_IRQ_NUM_0_OFFSET 0x40
#define EVP_PRI_IRQ_NUM_0_RESET  0x00000080
typedef union evp_pri_irq_num_0_u {
    struct {
        unsigned int pri_irq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_0_t;

#define EVP_PRI_IRQ_VEC_0_OFFSET 0x44
#define EVP_PRI_IRQ_VEC_0_RESET  0x40000018
typedef union evp_pri_irq_vec_0_u {
    struct {
        unsigned int pri_irq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_0_t;

#define EVP_PRI_IRQ_NUM_1_OFFSET 0x48
#define EVP_PRI_IRQ_NUM_1_RESET  0x00000080
typedef union evp_pri_irq_num_1_u {
    struct {
        unsigned int pri_irq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_1_t;

#define EVP_PRI_IRQ_VEC_1_OFFSET 0x4C
#define EVP_PRI_IRQ_VEC_1_RESET  0x40000018
typedef union evp_pri_irq_vec_1_u {
    struct {
        unsigned int pri_irq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_1_t;

#define EVP_PRI_IRQ_NUM_2_OFFSET 0x50
#define EVP_PRI_IRQ_NUM_2_RESET  0x00000080
typedef union evp_pri_irq_num_2_u {
    struct {
        unsigned int pri_irq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_2_t;

#define EVP_PRI_IRQ_VEC_2_OFFSET 0x54
#define EVP_PRI_IRQ_VEC_2_RESET  0x40000018
typedef union evp_pri_irq_vec_2_u {
    struct {
        unsigned int pri_irq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_2_t;

#define EVP_PRI_IRQ_NUM_3_OFFSET 0x58
#define EVP_PRI_IRQ_NUM_3_RESET  0x00000080
typedef union evp_pri_irq_num_3_u {
    struct {
        unsigned int pri_irq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_3_t;

#define EVP_PRI_IRQ_VEC_3_OFFSET 0x5C
#define EVP_PRI_IRQ_VEC_3_RESET  0x40000018
typedef union evp_pri_irq_vec_3_u {
    struct {
        unsigned int pri_irq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_3_t;

#define EVP_PRI_IRQ_NUM_4_OFFSET 0x60
#define EVP_PRI_IRQ_NUM_4_RESET  0x00000080
typedef union evp_pri_irq_num_4_u {
    struct {
        unsigned int pri_irq_num_4:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_4_t;

#define EVP_PRI_IRQ_VEC_4_OFFSET 0x64
#define EVP_PRI_IRQ_VEC_4_RESET  0x40000018
typedef union evp_pri_irq_vec_4_u {
    struct {
        unsigned int pri_irq_vec_4:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_4_t;

#define EVP_PRI_IRQ_NUM_5_OFFSET 0x68
#define EVP_PRI_IRQ_NUM_5_RESET  0x00000080
typedef union evp_pri_irq_num_5_u {
    struct {
        unsigned int pri_irq_num_5:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_5_t;

#define EVP_PRI_IRQ_VEC_5_OFFSET 0x6C
#define EVP_PRI_IRQ_VEC_5_RESET  0x40000018
typedef union evp_pri_irq_vec_5_u {
    struct {
        unsigned int pri_irq_vec_5:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_5_t;

#define EVP_PRI_IRQ_NUM_6_OFFSET 0x70
#define EVP_PRI_IRQ_NUM_6_RESET  0x00000080
typedef union evp_pri_irq_num_6_u {
    struct {
        unsigned int pri_irq_num_6:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_6_t;

#define EVP_PRI_IRQ_VEC_6_OFFSET 0x74
#define EVP_PRI_IRQ_VEC_6_RESET  0x40000018
typedef union evp_pri_irq_vec_6_u {
    struct {
        unsigned int pri_irq_vec_6:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_6_t;

#define EVP_PRI_IRQ_NUM_7_OFFSET 0x78
#define EVP_PRI_IRQ_NUM_7_RESET  0x00000080
typedef union evp_pri_irq_num_7_u {
    struct {
        unsigned int pri_irq_num_7:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_irq_num_7_t;

#define EVP_PRI_IRQ_VEC_7_OFFSET 0x7C
#define EVP_PRI_IRQ_VEC_7_RESET  0x40000018
typedef union evp_pri_irq_vec_7_u {
    struct {
        unsigned int pri_irq_vec_7:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_irq_vec_7_t;

#define EVP_PRI_FIQ_NUM_0_OFFSET 0x80
#define EVP_PRI_FIQ_NUM_0_RESET  0x00000080
typedef union evp_pri_fiq_num_0_u {
    struct {
        unsigned int pri_fiq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_fiq_num_0_t;

#define EVP_PRI_FIQ_VEC_0_OFFSET 0x84
#define EVP_PRI_FIQ_VEC_0_RESET  0x4000001C
typedef union evp_pri_fiq_vec_0_u {
    struct {
        unsigned int pri_fiq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_fiq_vec_0_t;

#define EVP_PRI_FIQ_NUM_1_OFFSET 0x88
#define EVP_PRI_FIQ_NUM_1_RESET  0x00000080
typedef union evp_pri_fiq_num_1_u {
    struct {
        unsigned int pri_fiq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_fiq_num_1_t;

#define EVP_PRI_FIQ_VEC_1_OFFSET 0x8C
#define EVP_PRI_FIQ_VEC_1_RESET  0x4000001C
typedef union evp_pri_fiq_vec_1_u {
    struct {
        unsigned int pri_fiq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_fiq_vec_1_t;

#define EVP_PRI_FIQ_NUM_2_OFFSET 0x90
#define EVP_PRI_FIQ_NUM_2_RESET  0x00000080
typedef union evp_pri_fiq_num_2_u {
    struct {
        unsigned int pri_fiq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_fiq_num_2_t;

#define EVP_PRI_FIQ_VEC_2_OFFSET 0x94
#define EVP_PRI_FIQ_VEC_2_RESET  0x4000001C
typedef union evp_pri_fiq_vec_2_u {
    struct {
        unsigned int pri_fiq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_fiq_vec_2_t;

#define EVP_PRI_FIQ_NUM_3_OFFSET 0x98
#define EVP_PRI_FIQ_NUM_3_RESET  0x00000080
typedef union evp_pri_fiq_num_3_u {
    struct {
        unsigned int pri_fiq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_pri_fiq_num_3_t;

#define EVP_PRI_FIQ_VEC_3_OFFSET 0x9C
#define EVP_PRI_FIQ_VEC_3_RESET  0x4000001C
typedef union evp_pri_fiq_vec_3_u {
    struct {
        unsigned int pri_fiq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_pri_fiq_vec_3_t;

#define EVP_CPU_RESET_VECTOR_OFFSET 0x100
#define EVP_CPU_RESET_VECTOR_RESET  0xFFF00000
typedef union evp_cpu_reset_vector_u {
    struct {
        unsigned int cpu_reset_vector:32;   /* RESET Exception Vector Pointer  */
    };

    uint32_t reg32;
} evp_cpu_reset_vector_t;

#define EVP_CPU_UNDEF_VECTOR_OFFSET 0x104
#define EVP_CPU_UNDEF_VECTOR_RESET  0xFFF00004
typedef union evp_cpu_undef_vector_u {
    struct {
        unsigned int cpu_undef_vector:32;   /* Undefined Exception Vector Pointer */
    };

    uint32_t reg32;
} evp_cpu_undef_vector_t;

#define EVP_CPU_SWI_VECTOR_OFFSET 0x108
#define EVP_CPU_SWI_VECTOR_RESET  0xFFF00008
typedef union evp_cpu_swi_vector_u {
    struct {
        unsigned int cpu_swi_vector:32;     /* Software Interrupt Vector Pointer */
    };

    uint32_t reg32;
} evp_cpu_swi_vector_t;

#define EVP_CPU_PREFETCH_ABORT_VECTOR_OFFSET 0x10C
#define EVP_CPU_PREFETCH_ABORT_VECTOR_RESET  0xFFF0000C
typedef union evp_cpu_prefetch_abort_vector_u {
    struct {
        unsigned int cpu_pre_abort_vector:32;/* Code Prefetch ABORT Vector Pointer  */
    };

    uint32_t reg32;
} evp_cpu_prefetch_abort_vector_t;

#define EVP_CPU_DATA_ABORT_VECTOR_OFFSET 0x110
#define EVP_CPU_DATA_ABORT_VECTOR_RESET  0xFFF00010
typedef union evp_cpu_data_abort_vector_u {
    struct {
        unsigned int cpu_data_abort_vector:32;/* Data ABORT Vector Pointer */
    };

    uint32_t reg32;
} evp_cpu_data_abort_vector_t;

#define EVP_CPU_RSVD_VECTOR_OFFSET 0x114
#define EVP_CPU_RSVD_VECTOR_RESET  0xFFF00014
typedef union evp_cpu_rsvd_vector_u {
    struct {
        unsigned int cpu_rsvd_vector:32;    /* Reserved Exception Vector Pointer */
    };

    uint32_t reg32;
} evp_cpu_rsvd_vector_t;

#define EVP_CPU_IRQ_VECTOR_OFFSET 0x118
#define EVP_CPU_IRQ_VECTOR_RESET  0xFFF00018
typedef union evp_cpu_irq_vector_u {
    struct {
        unsigned int cpu_irq_vector:32;     /* IRQ Vector Pointer  */
    };

    uint32_t reg32;
} evp_cpu_irq_vector_t;

#define EVP_CPU_FIQ_VECTOR_OFFSET 0x11C
#define EVP_CPU_FIQ_VECTOR_RESET  0xFFF0001C
typedef union evp_cpu_fiq_vector_u {
    struct {
        unsigned int cpu_fiq_vector:32;     /* FIQ Vector Pointer  */
    };

    uint32_t reg32;
} evp_cpu_fiq_vector_t;

#define EVP_CPU_IRQ_STS_OFFSET 0x120
#define EVP_CPU_IRQ_STS_RESET  0x00000080
typedef union evp_cpu_irq_sts_u {
    struct {
        unsigned int cpu_irq_sts:32;        /* FFS (from lsb) IRQ index  (0x80 indicates no active IRQ) */
    };

    uint32_t reg32;
} evp_cpu_irq_sts_t;

#define EVP_CPU_PRI_IRQ_STS_OFFSET 0x124
#define EVP_CPU_PRI_IRQ_STS_RESET  0x00000080
typedef union evp_cpu_pri_irq_sts_u {
    struct {
        unsigned int cpu_pri_irq_sts:32;    /* Current highest priority active IRQ (0x80 indicates no active priority IRQ) */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_sts_t;

#define EVP_CPU_FIQ_STS_OFFSET 0x128
#define EVP_CPU_FIQ_STS_RESET  0x00000080
typedef union evp_cpu_fiq_sts_u {
    struct {
        unsigned int cpu_fiq_sts:32;        /* FFS (from lsb) FIQ index (0x80 indicates no active FIQ) */
    };

    uint32_t reg32;
} evp_cpu_fiq_sts_t;

#define EVP_CPU_PRI_FIQ_STS_OFFSET 0x12C
#define EVP_CPU_PRI_FIQ_STS_RESET  0x00000080
typedef union evp_cpu_pri_fiq_sts_u {
    struct {
        unsigned int cpu_pri_fiq_sts:32;    /* Current highest priority active FIQ (0x80 indicates no active priority FIQ) */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_sts_t;

#define EVP_CPU_PRI_IRQ_NUM_0_OFFSET 0x140
#define EVP_CPU_PRI_IRQ_NUM_0_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_0_u {
    struct {
        unsigned int pri_irq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_0_t;

#define EVP_CPU_PRI_IRQ_VEC_0_OFFSET 0x144
#define EVP_CPU_PRI_IRQ_VEC_0_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_0_u {
    struct {
        unsigned int pri_irq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_0_t;

#define EVP_CPU_PRI_IRQ_NUM_1_OFFSET 0x148
#define EVP_CPU_PRI_IRQ_NUM_1_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_1_u {
    struct {
        unsigned int pri_irq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_1_t;

#define EVP_CPU_PRI_IRQ_VEC_1_OFFSET 0x14C
#define EVP_CPU_PRI_IRQ_VEC_1_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_1_u {
    struct {
        unsigned int pri_irq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_1_t;

#define EVP_CPU_PRI_IRQ_NUM_2_OFFSET 0x150
#define EVP_CPU_PRI_IRQ_NUM_2_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_2_u {
    struct {
        unsigned int pri_irq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_2_t;

#define EVP_CPU_PRI_IRQ_VEC_2_OFFSET 0x154
#define EVP_CPU_PRI_IRQ_VEC_2_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_2_u {
    struct {
        unsigned int pri_irq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_2_t;

#define EVP_CPU_PRI_IRQ_NUM_3_OFFSET 0x158
#define EVP_CPU_PRI_IRQ_NUM_3_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_3_u {
    struct {
        unsigned int pri_irq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_3_t;

#define EVP_CPU_PRI_IRQ_VEC_3_OFFSET 0x15C
#define EVP_CPU_PRI_IRQ_VEC_3_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_3_u {
    struct {
        unsigned int pri_irq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_3_t;

#define EVP_CPU_PRI_IRQ_NUM_4_OFFSET 0x160
#define EVP_CPU_PRI_IRQ_NUM_4_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_4_u {
    struct {
        unsigned int pri_irq_num_4:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_4_t;

#define EVP_CPU_PRI_IRQ_VEC_4_OFFSET 0x164
#define EVP_CPU_PRI_IRQ_VEC_4_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_4_u {
    struct {
        unsigned int pri_irq_vec_4:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_4_t;

#define EVP_CPU_PRI_IRQ_NUM_5_OFFSET 0x168
#define EVP_CPU_PRI_IRQ_NUM_5_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_5_u {
    struct {
        unsigned int pri_irq_num_5:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_5_t;

#define EVP_CPU_PRI_IRQ_VEC_5_OFFSET 0x16C
#define EVP_CPU_PRI_IRQ_VEC_5_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_5_u {
    struct {
        unsigned int pri_irq_vec_5:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_5_t;

#define EVP_CPU_PRI_IRQ_NUM_6_OFFSET 0x170
#define EVP_CPU_PRI_IRQ_NUM_6_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_6_u {
    struct {
        unsigned int pri_irq_num_6:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_6_t;

#define EVP_CPU_PRI_IRQ_VEC_6_OFFSET 0x174
#define EVP_CPU_PRI_IRQ_VEC_6_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_6_u {
    struct {
        unsigned int pri_irq_vec_6:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_6_t;

#define EVP_CPU_PRI_IRQ_NUM_7_OFFSET 0x178
#define EVP_CPU_PRI_IRQ_NUM_7_RESET  0x00000080
typedef union evp_cpu_pri_irq_num_7_u {
    struct {
        unsigned int pri_irq_num_7:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_num_7_t;

#define EVP_CPU_PRI_IRQ_VEC_7_OFFSET 0x17C
#define EVP_CPU_PRI_IRQ_VEC_7_RESET  0x40000018
typedef union evp_cpu_pri_irq_vec_7_u {
    struct {
        unsigned int pri_irq_vec_7:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_irq_vec_7_t;

#define EVP_CPU_PRI_FIQ_NUM_0_OFFSET 0x180
#define EVP_CPU_PRI_FIQ_NUM_0_RESET  0x00000080
typedef union evp_cpu_pri_fiq_num_0_u {
    struct {
        unsigned int pri_fiq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_num_0_t;

#define EVP_CPU_PRI_FIQ_VEC_0_OFFSET 0x184
#define EVP_CPU_PRI_FIQ_VEC_0_RESET  0x4000001C
typedef union evp_cpu_pri_fiq_vec_0_u {
    struct {
        unsigned int pri_fiq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_vec_0_t;

#define EVP_CPU_PRI_FIQ_NUM_1_OFFSET 0x188
#define EVP_CPU_PRI_FIQ_NUM_1_RESET  0x00000080
typedef union evp_cpu_pri_fiq_num_1_u {
    struct {
        unsigned int pri_fiq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_num_1_t;

#define EVP_CPU_PRI_FIQ_VEC_1_OFFSET 0x18C
#define EVP_CPU_PRI_FIQ_VEC_1_RESET  0x4000001C
typedef union evp_cpu_pri_fiq_vec_1_u {
    struct {
        unsigned int pri_fiq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_vec_1_t;

#define EVP_CPU_PRI_FIQ_NUM_2_OFFSET 0x190
#define EVP_CPU_PRI_FIQ_NUM_2_RESET  0x00000080
typedef union evp_cpu_pri_fiq_num_2_u {
    struct {
        unsigned int pri_fiq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_num_2_t;

#define EVP_CPU_PRI_FIQ_VEC_2_OFFSET 0x194
#define EVP_CPU_PRI_FIQ_VEC_2_RESET  0x4000001C
typedef union evp_cpu_pri_fiq_vec_2_u {
    struct {
        unsigned int pri_fiq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_vec_2_t;

#define EVP_CPU_PRI_FIQ_NUM_3_OFFSET 0x198
#define EVP_CPU_PRI_FIQ_NUM_3_RESET  0x00000080
typedef union evp_cpu_pri_fiq_num_3_u {
    struct {
        unsigned int pri_fiq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_num_3_t;

#define EVP_CPU_PRI_FIQ_VEC_3_OFFSET 0x19C
#define EVP_CPU_PRI_FIQ_VEC_3_RESET  0x4000001C
typedef union evp_cpu_pri_fiq_vec_3_u {
    struct {
        unsigned int pri_fiq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cpu_pri_fiq_vec_3_t;

#define EVP_COP_RESET_VECTOR_OFFSET 0x200
#define EVP_COP_RESET_VECTOR_RESET  0xFFF00000
typedef union evp_cop_reset_vector_u {
    struct {
        unsigned int cop_reset_vector:32;   /* RESET Exception Vector Pointer  */
    };

    uint32_t reg32;
} evp_cop_reset_vector_t;

#define EVP_COP_UNDEF_VECTOR_OFFSET 0x204
#define EVP_COP_UNDEF_VECTOR_RESET  0xFFF00004
typedef union evp_cop_undef_vector_u {
    struct {
        unsigned int cop_undef_vector:32;   /* Undefined Exception Vector Pointer */
    };

    uint32_t reg32;
} evp_cop_undef_vector_t;

#define EVP_COP_SWI_VECTOR_OFFSET 0x208
#define EVP_COP_SWI_VECTOR_RESET  0xFFF00008
typedef union evp_cop_swi_vector_u {
    struct {
        unsigned int cop_swi_vector:32;     /* Software Interrupt Vector Pointer */
    };

    uint32_t reg32;
} evp_cop_swi_vector_t;

#define EVP_COP_PREFETCH_ABORT_VECTOR_OFFSET 0x20C
#define EVP_COP_PREFETCH_ABORT_VECTOR_RESET  0xFFF0000C
typedef union evp_cop_prefetch_abort_vector_u {
    struct {
        unsigned int cop_pre_abort_vector:32;/* Code Prefetch ABORT Vector Pointer  */
    };

    uint32_t reg32;
} evp_cop_prefetch_abort_vector_t;

#define EVP_COP_DATA_ABORT_VECTOR_OFFSET 0x210
#define EVP_COP_DATA_ABORT_VECTOR_RESET  0xFFF00010
typedef union evp_cop_data_abort_vector_u {
    struct {
        unsigned int cop_data_abort_vector:32;/* Data ABORT Vector Pointer */
    };

    uint32_t reg32;
} evp_cop_data_abort_vector_t;

#define EVP_COP_RSVD_VECTOR_OFFSET 0x214
#define EVP_COP_RSVD_VECTOR_RESET  0xFFF00014
typedef union evp_cop_rsvd_vector_u {
    struct {
        unsigned int cop_rsvd_vector:32;    /* Reserved Exception Vector Pointer */
    };

    uint32_t reg32;
} evp_cop_rsvd_vector_t;

#define EVP_COP_IRQ_VECTOR_OFFSET 0x218
#define EVP_COP_IRQ_VECTOR_RESET  0xFFF00018
typedef union evp_cop_irq_vector_u {
    struct {
        unsigned int cop_irq_vector:32;     /* IRQ Vector Pointer  */
    };

    uint32_t reg32;
} evp_cop_irq_vector_t;

#define EVP_COP_FIQ_VECTOR_OFFSET 0x21C
#define EVP_COP_FIQ_VECTOR_RESET  0xFFF0001C
typedef union evp_cop_fiq_vector_u {
    struct {
        unsigned int cop_fiq_vector:32;     /* FIQ Vector Pointer  */
    };

    uint32_t reg32;
} evp_cop_fiq_vector_t;

#define EVP_COP_IRQ_STS_OFFSET 0x220
#define EVP_COP_IRQ_STS_RESET  0x00000080
typedef union evp_cop_irq_sts_u {
    struct {
        unsigned int cop_irq_sts:32;        /* FFS (from lsb) IRQ index  (0x80 indicates no active IRQ) */
    };

    uint32_t reg32;
} evp_cop_irq_sts_t;

#define EVP_COP_PRI_IRQ_STS_OFFSET 0x224
#define EVP_COP_PRI_IRQ_STS_RESET  0x00000080
typedef union evp_cop_pri_irq_sts_u {
    struct {
        unsigned int cop_pri_irq_sts:32;    /* Current highest priority active IRQ (0x80 indicates no active priority IRQ) */
    };

    uint32_t reg32;
} evp_cop_pri_irq_sts_t;

#define EVP_COP_FIQ_STS_OFFSET 0x228
#define EVP_COP_FIQ_STS_RESET  0x00000080
typedef union evp_cop_fiq_sts_u {
    struct {
        unsigned int cop_fiq_sts:32;        /* FFS (from lsb) FIQ index (0x80 indicates no active FIQ) */
    };

    uint32_t reg32;
} evp_cop_fiq_sts_t;

#define EVP_COP_PRI_FIQ_STS_OFFSET 0x22C
#define EVP_COP_PRI_FIQ_STS_RESET  0x00000080
typedef union evp_cop_pri_fiq_sts_u {
    struct {
        unsigned int cop_pri_fiq_sts:32;    /* Current highest priority active FIQ (0x80 indicates no active priority FIQ) */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_sts_t;

#define EVP_COP_PRI_IRQ_NUM_0_OFFSET 0x240
#define EVP_COP_PRI_IRQ_NUM_0_RESET  0x00000080
typedef union evp_cop_pri_irq_num_0_u {
    struct {
        unsigned int pri_irq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_0_t;

#define EVP_COP_PRI_IRQ_VEC_0_OFFSET 0x244
#define EVP_COP_PRI_IRQ_VEC_0_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_0_u {
    struct {
        unsigned int pri_irq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_0_t;

#define EVP_COP_PRI_IRQ_NUM_1_OFFSET 0x248
#define EVP_COP_PRI_IRQ_NUM_1_RESET  0x00000080
typedef union evp_cop_pri_irq_num_1_u {
    struct {
        unsigned int pri_irq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_1_t;

#define EVP_COP_PRI_IRQ_VEC_1_OFFSET 0x24C
#define EVP_COP_PRI_IRQ_VEC_1_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_1_u {
    struct {
        unsigned int pri_irq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_1_t;

#define EVP_COP_PRI_IRQ_NUM_2_OFFSET 0x250
#define EVP_COP_PRI_IRQ_NUM_2_RESET  0x00000080
typedef union evp_cop_pri_irq_num_2_u {
    struct {
        unsigned int pri_irq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_2_t;

#define EVP_COP_PRI_IRQ_VEC_2_OFFSET 0x254
#define EVP_COP_PRI_IRQ_VEC_2_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_2_u {
    struct {
        unsigned int pri_irq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_2_t;

#define EVP_COP_PRI_IRQ_NUM_3_OFFSET 0x258
#define EVP_COP_PRI_IRQ_NUM_3_RESET  0x00000080
typedef union evp_cop_pri_irq_num_3_u {
    struct {
        unsigned int pri_irq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_3_t;

#define EVP_COP_PRI_IRQ_VEC_3_OFFSET 0x25C
#define EVP_COP_PRI_IRQ_VEC_3_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_3_u {
    struct {
        unsigned int pri_irq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_3_t;

#define EVP_COP_PRI_IRQ_NUM_4_OFFSET 0x260
#define EVP_COP_PRI_IRQ_NUM_4_RESET  0x00000080
typedef union evp_cop_pri_irq_num_4_u {
    struct {
        unsigned int pri_irq_num_4:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_4_t;

#define EVP_COP_PRI_IRQ_VEC_4_OFFSET 0x264
#define EVP_COP_PRI_IRQ_VEC_4_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_4_u {
    struct {
        unsigned int pri_irq_vec_4:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_4_t;

#define EVP_COP_PRI_IRQ_NUM_5_OFFSET 0x268
#define EVP_COP_PRI_IRQ_NUM_5_RESET  0x00000080
typedef union evp_cop_pri_irq_num_5_u {
    struct {
        unsigned int pri_irq_num_5:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_5_t;

#define EVP_COP_PRI_IRQ_VEC_5_OFFSET 0x26C
#define EVP_COP_PRI_IRQ_VEC_5_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_5_u {
    struct {
        unsigned int pri_irq_vec_5:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_5_t;

#define EVP_COP_PRI_IRQ_NUM_6_OFFSET 0x270
#define EVP_COP_PRI_IRQ_NUM_6_RESET  0x00000080
typedef union evp_cop_pri_irq_num_6_u {
    struct {
        unsigned int pri_irq_num_6:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_6_t;

#define EVP_COP_PRI_IRQ_VEC_6_OFFSET 0x274
#define EVP_COP_PRI_IRQ_VEC_6_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_6_u {
    struct {
        unsigned int pri_irq_vec_6:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_6_t;

#define EVP_COP_PRI_IRQ_NUM_7_OFFSET 0x278
#define EVP_COP_PRI_IRQ_NUM_7_RESET  0x00000080
typedef union evp_cop_pri_irq_num_7_u {
    struct {
        unsigned int pri_irq_num_7:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_irq_num_7_t;

#define EVP_COP_PRI_IRQ_VEC_7_OFFSET 0x27C
#define EVP_COP_PRI_IRQ_VEC_7_RESET  0x40000018
typedef union evp_cop_pri_irq_vec_7_u {
    struct {
        unsigned int pri_irq_vec_7:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_irq_vec_7_t;

#define EVP_COP_PRI_FIQ_NUM_0_OFFSET 0x280
#define EVP_COP_PRI_FIQ_NUM_0_RESET  0x00000080
typedef union evp_cop_pri_fiq_num_0_u {
    struct {
        unsigned int pri_fiq_num_0:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_num_0_t;

#define EVP_COP_PRI_FIQ_VEC_0_OFFSET 0x284
#define EVP_COP_PRI_FIQ_VEC_0_RESET  0x4000001C
typedef union evp_cop_pri_fiq_vec_0_u {
    struct {
        unsigned int pri_fiq_vec_0:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_vec_0_t;

#define EVP_COP_PRI_FIQ_NUM_1_OFFSET 0x288
#define EVP_COP_PRI_FIQ_NUM_1_RESET  0x00000080
typedef union evp_cop_pri_fiq_num_1_u {
    struct {
        unsigned int pri_fiq_num_1:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_num_1_t;

#define EVP_COP_PRI_FIQ_VEC_1_OFFSET 0x28C
#define EVP_COP_PRI_FIQ_VEC_1_RESET  0x4000001C
typedef union evp_cop_pri_fiq_vec_1_u {
    struct {
        unsigned int pri_fiq_vec_1:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_vec_1_t;

#define EVP_COP_PRI_FIQ_NUM_2_OFFSET 0x290
#define EVP_COP_PRI_FIQ_NUM_2_RESET  0x00000080
typedef union evp_cop_pri_fiq_num_2_u {
    struct {
        unsigned int pri_fiq_num_2:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_num_2_t;

#define EVP_COP_PRI_FIQ_VEC_2_OFFSET 0x294
#define EVP_COP_PRI_FIQ_VEC_2_RESET  0x4000001C
typedef union evp_cop_pri_fiq_vec_2_u {
    struct {
        unsigned int pri_fiq_vec_2:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_vec_2_t;

#define EVP_COP_PRI_FIQ_NUM_3_OFFSET 0x298
#define EVP_COP_PRI_FIQ_NUM_3_RESET  0x00000080
typedef union evp_cop_pri_fiq_num_3_u {
    struct {
        unsigned int pri_fiq_num_3:32;      /* Number for the Interrupt associated with this entry */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_num_3_t;

#define EVP_COP_PRI_FIQ_VEC_3_OFFSET 0x29C
#define EVP_COP_PRI_FIQ_VEC_3_RESET  0x4000001C
typedef union evp_cop_pri_fiq_vec_3_u {
    struct {
        unsigned int pri_fiq_vec_3:32;      /* Pointer to the interrupt handler for the above interrupt  */
    };

    uint32_t reg32;
} evp_cop_pri_fiq_vec_3_t;

#endif // TEGRA_EVP_H