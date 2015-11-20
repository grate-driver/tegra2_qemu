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

#include "hw/arm/arm.h"
#include "sysemu/sysemu.h"

#include "tcg-op.h"

#include "tegra_cpu.h"
#include "tegra_trace.h"

#include "tegra_cpu_priv.h"

#undef TPRINT
#define TPRINT(...) {}

static volatile int tcpu_halted[TEGRA2_NCPUS];

void tegra_cpu_hlt_clr(void)
{
    int i;

    for (i = 0; i < TEGRA2_NCPUS; i++)
        tcpu_halted[i] = 0;
}

void tegra_cpu_stop(int cpu_id)
{
    CPUState *cs = qemu_get_cpu(cpu_id);
    ARMCPU *cpu = ARM_CPU(cs);

    if (tcpu_halted[cpu_id])
        return;

    if (tegra_cpu_reset_asserted(cpu_id))
        return;

    cpu->powered_off = 1;
    cpu_interrupt(cs, CPU_INTERRUPT_HALT);

    if (tcg_enabled() && qemu_cpu_is_self(cs)) {
        if (tcg_ctx.gen_next_op_idx != OPC_BUF_SIZE) {
            tcg_gen_exit_tb(0);
        }
    }
}

void tegra_cpu_run(int cpu_id)
{
    CPUState *cs = qemu_get_cpu(cpu_id);
    ARMCPU *cpu = ARM_CPU(cs);

    if (tcpu_halted[cpu_id]) {
        TPRINT("%s cpu %d HALTED!\n", __func__, cpu_id);
        return;
    }

    if (tegra_cpu_reset_asserted(cpu_id)) {
        TPRINT("%s cpu %d IN RESET!\n", __func__, cpu_id);
        return;
    }

    TPRINT("%s cpu %d\n", __func__, cpu_id);

    cpu_reset_interrupt(cs, CPU_INTERRUPT_HALT);
    cs->halted = cpu->powered_off = 0;

    cpu_resume(cs);
}

void tegra_cpu_halt(int cpu_id)
{
    TPRINT("%s cpu %d\n", __func__, cpu_id);

    tegra_cpu_stop(cpu_id);
    tcpu_halted[cpu_id] = 1;
}

void tegra_cpu_unhalt(int cpu_id)
{
    if (!tcpu_halted[cpu_id]) {
        TPRINT("%s cpu %d NOT HALTED!\n", __func__, cpu_id);
        return;
    }

    TPRINT("%s cpu %d\n", __func__, cpu_id);

    tcpu_halted[cpu_id] = 0;
    tegra_cpu_run(cpu_id);
}
