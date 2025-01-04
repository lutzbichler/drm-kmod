/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_COLOR_H__
#define __INTEL_COLOR_H__

#include <linux/types.h>

struct drm_property_blob;
struct intel_atomic_state;
struct intel_crtc_state;
struct intel_crtc;
struct xe_device;

void intel_color_init_hooks(struct xe_device *xe);
int intel_color_init(struct xe_device *xe);
void intel_color_crtc_init(struct intel_crtc *crtc);
int intel_color_check(struct intel_atomic_state *state,
		      struct intel_crtc *crtc);
void intel_color_prepare_commit(struct intel_atomic_state *state,
				struct intel_crtc *crtc);
void intel_color_cleanup_commit(struct intel_crtc_state *crtc_state);
bool intel_color_uses_dsb(const struct intel_crtc_state *crtc_state);
void intel_color_wait_commit(const struct intel_crtc_state *crtc_state);
void intel_color_commit_noarm(const struct intel_crtc_state *crtc_state);
void intel_color_commit_arm(const struct intel_crtc_state *crtc_state);
void intel_color_post_update(const struct intel_crtc_state *crtc_state);
void intel_color_load_luts(const struct intel_crtc_state *crtc_state);
void intel_color_get_config(struct intel_crtc_state *crtc_state);
bool intel_color_lut_equal(const struct intel_crtc_state *crtc_state,
			   const struct drm_property_blob *blob1,
			   const struct drm_property_blob *blob2,
			   bool is_pre_csc_lut);
void intel_color_assert_luts(const struct intel_crtc_state *crtc_state);

#endif /* __INTEL_COLOR_H__ */
