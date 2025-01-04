/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_PXP_H__
#define __INTEL_PXP_H__

#include <linux/errno.h>
#include <linux/types.h>

struct intel_pxp;
struct xe_bo;

static inline int intel_pxp_key_check(struct intel_pxp *pxp,
				      struct xe_bo *obj,
				      bool assign)
{
	return -ENODEV;
}

static inline bool
i915_gem_object_is_protected(const struct xe_bo *obj)
{
	return false;
}

#endif
