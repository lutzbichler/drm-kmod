/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_DISPLAY_RPS_H__
#define __INTEL_DISPLAY_RPS_H__

#include <linux/types.h>

struct dma_fence;
struct drm_crtc;
struct intel_atomic_state;
struct xe_device;

void intel_display_rps_boost_after_vblank(struct drm_crtc *crtc,
					  struct dma_fence *fence);
void intel_display_rps_mark_interactive(struct xe_device *xe,
					struct intel_atomic_state *state,
					bool interactive);

#endif /* __INTEL_DISPLAY_RPS_H__ */
