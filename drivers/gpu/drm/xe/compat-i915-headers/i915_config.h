/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __I915_CONFIG_H__
#define __I915_CONFIG_H__

#include <linux/sched.h>

struct xe_device;

static inline unsigned long
i915_fence_timeout(const struct xe_device *xe)
{
	return MAX_SCHEDULE_TIMEOUT;
}

#endif /* __I915_CONFIG_H__ */
