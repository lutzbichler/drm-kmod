/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_CLOCK_GATING_H__
#define __INTEL_CLOCK_GATING_H__

struct xe_device;

void intel_clock_gating_init(struct xe_device *xe);
void intel_clock_gating_hooks_init(struct xe_device *xe);

#endif /* __INTEL_CLOCK_GATING_H__ */
