/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_CRT_H__
#define __INTEL_CRT_H__

#include "i915_reg_defs.h"

enum pipe;
struct drm_encoder;
struct xe_device;

#ifdef I915
bool intel_crt_port_enabled(struct xe_device *xe,
			    i915_reg_t adpa_reg, enum pipe *pipe);
void intel_crt_init(struct xe_device *xe);
void intel_crt_reset(struct drm_encoder *encoder);
#else
static inline bool intel_crt_port_enabled(struct xe_device *xe,
					  i915_reg_t adpa_reg, enum pipe *pipe)
{
	return false;
}
static inline void intel_crt_init(struct xe_device *xe)
{
}
static inline void intel_crt_reset(struct drm_encoder *encoder)
{
}
#endif

#endif /* __INTEL_CRT_H__ */
