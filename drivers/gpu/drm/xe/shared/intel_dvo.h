/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_DVO_H__
#define __INTEL_DVO_H__

struct xe_device;

#ifdef I915
void intel_dvo_init(struct xe_device *xe);
#else
static inline void intel_dvo_init(struct xe_device *xe)
{
}
#endif

#endif /* __INTEL_DVO_H__ */
