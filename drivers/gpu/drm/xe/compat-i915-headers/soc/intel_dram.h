/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2020 Intel Corporation
 */

#ifndef __INTEL_DRAM_H__
#define __INTEL_DRAM_H__

struct xe_device;

void intel_dram_edram_detect(struct xe_device *xe);
void intel_dram_detect(struct xe_device *xe);
unsigned int i9xx_fsb_freq(struct xe_device *xe);

#endif /* __INTEL_DRAM_H__ */
