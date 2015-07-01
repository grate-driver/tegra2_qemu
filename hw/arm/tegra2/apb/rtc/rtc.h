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

#ifndef TEGRA_RTC_H
#define TEGRA_RTC_H

#define CONTROL_OFFSET 0x0
#define CONTROL_RESET  0x00000000
typedef union control_u {
    struct {
        unsigned int wr_sec_cnt:1;          /* When set, writes to SECONDS counter are disabled. can only cleared by resetting the RTC module  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    uint32_t reg32;
} control_t;

#define BUSY_OFFSET 0x4
#define BUSY_RESET  0x00000000
typedef union busy_u {
    struct {
        unsigned int status:1;              /* This bit is set when a write is initiated on the APB side. It is cleared once the write completes in RTC 32KHz clock domain which could be several thousands of APB clocks. This must be IDLE before a write is initiated. Note that this bit is only for writes. 0 = IDLE 1 = BUSY */
        unsigned int undefined_bits_1_31:31;
    };

    uint32_t reg32;
} busy_t;

#define SECONDS_OFFSET 0x8
#define SECONDS_RESET  0x00000000
typedef union seconds_u {
    struct {
        unsigned int seconds:32;            /* seconds counter is incremented for every 1000 milli-seconds */
    };

    uint32_t reg32;
} seconds_t;

#define SHADOW_SECONDS_OFFSET 0xC
#define SHADOW_SECONDS_RESET  0x00000000
typedef union shadow_seconds_u {
    struct {
        unsigned int shadow_seconds:32;     /* A snapshot of the SECONDS counter is taken whenever there is a read to MILLI_SECONDS Register */
    };

    uint32_t reg32;
} shadow_seconds_t;

#define MILLI_SECONDS_OFFSET 0x10
#define MILLI_SECONDS_RESET  0x00000000
typedef union milli_seconds_u {
    struct {
        unsigned int milli_seconds:10;      /* milliseconds counter is incremented using Bresenham algorithm */
        unsigned int undefined_bits_10_31:22;
    };

    uint32_t reg32;
} milli_seconds_t;

#define SECONDS_ALARM0_OFFSET 0x14
#define SECONDS_ALARM0_RESET  0x00000000
typedef union seconds_alarm0_u {
    struct {
        unsigned int secs_match_value:32;   /* match value to trigger the alarm */
    };

    uint32_t reg32;
} seconds_alarm0_t;

#define SECONDS_ALARM1_OFFSET 0x18
#define SECONDS_ALARM1_RESET  0x00000000
typedef union seconds_alarm1_u {
    struct {
        unsigned int secs_match_value:32;   /* match value to trigger the alarm */
    };

    uint32_t reg32;
} seconds_alarm1_t;

#define MILLI_SECONDS_ALARM_OFFSET 0x1C
#define MILLI_SECONDS_ALARM_RESET  0x00000000
typedef union milli_seconds_alarm_u {
    struct {
        unsigned int msec_match_value:10;   /* milliseconds match value */
        unsigned int undefined_bits_10_31:22;
    };

    uint32_t reg32;
} milli_seconds_alarm_t;

#define SECONDS_COUNTDOWN_ALARM_OFFSET 0x20
#define SECONDS_COUNTDOWN_ALARM_RESET  0x00000000
typedef union seconds_countdown_alarm_u {
    struct {
        unsigned int value:30;              /* number of milliseconds to countdown */
        unsigned int repeat:1;              /* repeat bit for the countdown operation  0 = DISABLED 1 = ENABLED */
        unsigned int enable:1;              /* enable bit for the countdown operation. If repeat is not set, this bit is cleared once the internal counters counts down to specified value. 0 = DISABLED 1 = ENABLED */
    };

    uint32_t reg32;
} seconds_countdown_alarm_t;

#define MILLI_SECONDS_COUNTDOWN_ALARM_OFFSET 0x24
#define MILLI_SECONDS_COUNTDOWN_ALARM_RESET  0x00000000
typedef union milli_seconds_countdown_alarm_u {
    struct {
        unsigned int value:30;              /* number of milliseconds to countdown */
        unsigned int repeat:1;              /* repeat bit for the countdown operation  0 = DISABLED 1 = ENABLED */
        unsigned int enable:1;              /* enable bit for the countdown operation. If repeat is not set, this bit is cleared once the internal counters counts down to specified value. 0 = DISABLED 1 = ENABLED */
    };

    uint32_t reg32;
} milli_seconds_countdown_alarm_t;

#define INTR_MASK_OFFSET 0x28
#define INTR_MASK_RESET  0x00000000
typedef union intr_mask_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    uint32_t reg32;
} intr_mask_t;

#define INTR_STATUS_OFFSET 0x2C
#define INTR_STATUS_RESET  0x00000000
typedef union intr_status_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    uint32_t reg32;
} intr_status_t;

#define INTR_SOURCE_OFFSET 0x30
#define INTR_SOURCE_RESET  0x00000000
typedef union intr_source_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    uint32_t reg32;
} intr_source_t;

#define INTR_SET_OFFSET 0x34
#define INTR_SET_RESET  0x00000000
typedef union intr_set_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    uint32_t reg32;
} intr_set_t;

#define CORRECTION_FACTOR_OFFSET 0x38
#define CORRECTION_FACTOR_RESET  0x00000000
typedef union correction_factor_u {
    struct {
        unsigned int ppm:9;
        unsigned int direction:1;           /* 0 = DECREMENT 1 = INCREMENT */
        unsigned int undefined_bits_10_31:22;
    };

    uint32_t reg32;
} correction_factor_t;

#endif // TEGRA_RTC_H
