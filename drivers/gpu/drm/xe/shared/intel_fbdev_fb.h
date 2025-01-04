/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_FBDEV_FB_H__
#define __INTEL_FBDEV_FB_H__

struct drm_fb_helper;
struct drm_fb_helper_surface_size;
struct fb_info;
struct i915_vma;
struct xe_bo;
struct xe_device;

struct intel_framebuffer *intel_fbdev_fb_alloc(struct drm_fb_helper *helper,
					       struct drm_fb_helper_surface_size *sizes);
int intel_fbdev_fb_fill_info(struct xe_device *xe, struct fb_info *info,
			     struct xe_bo *obj, struct i915_vma *vma);

#endif
