/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_PXP_H__
#define __INTEL_PXP_H__

#include <linux/errno.h>
#include <linux/types.h>

struct drm_gem_object;
struct xe_pxp;

static inline int intel_pxp_key_check(struct xe_pxp *pxp,
				      struct drm_gem_object *obj,
				      bool assign)
{
	return -ENODEV;
}

#endif
