/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_LVDS_H__
#define __INTEL_LVDS_H__

#include <linux/types.h>

#include "i915_reg_defs.h"

enum pipe;
struct xe_device;

#ifdef I915
bool intel_lvds_port_enabled(struct xe_device *xe,
			     i915_reg_t lvds_reg, enum pipe *pipe);
void intel_lvds_init(struct xe_device *xe);
struct intel_encoder *intel_get_lvds_encoder(struct xe_device *xe);
bool intel_is_dual_link_lvds(struct xe_device *xe);
#else
static inline bool intel_lvds_port_enabled(struct xe_device *xe,
					   i915_reg_t lvds_reg, enum pipe *pipe)
{
	return false;
}
static inline void intel_lvds_init(struct xe_device *xe)
{
}
static inline struct intel_encoder *intel_get_lvds_encoder(struct xe_device *xe)
{
	return NULL;
}
static inline bool intel_is_dual_link_lvds(struct xe_device *xe)
{
	return false;
}
#endif

#endif /* __INTEL_LVDS_H__ */
