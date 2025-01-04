/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_VGA_H__
#define __INTEL_VGA_H__

struct xe_device;

void intel_vga_reset_io_mem(struct xe_device *xe);
void intel_vga_disable(struct xe_device *xe);
void intel_vga_redisable(struct xe_device *xe);
void intel_vga_redisable_power_on(struct xe_device *xe);
int intel_vga_register(struct xe_device *xe);
void intel_vga_unregister(struct xe_device *xe);

#endif /* __INTEL_VGA_H__ */
