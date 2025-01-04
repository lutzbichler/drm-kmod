/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef _I915_VGPU_H_
#define _I915_VGPU_H_

#include <linux/types.h>

struct xe_device;

static inline bool intel_vgpu_active(struct xe_device *xe)
{
	return false;
}

#endif /* _I915_VGPU_H_ */
