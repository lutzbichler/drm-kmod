/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_FBDEV_H__
#define __INTEL_FBDEV_H__

#include <linux/types.h>

struct drm_device;
struct intel_fbdev;
struct intel_framebuffer;
struct xe_device;

#ifdef CONFIG_DRM_FBDEV_EMULATION
void intel_fbdev_setup(struct xe_device *xe);
void intel_fbdev_set_suspend(struct drm_device *dev, int state, bool synchronous);
struct intel_framebuffer *intel_fbdev_framebuffer(struct intel_fbdev *fbdev);
#else
static inline void intel_fbdev_setup(struct xe_device *xe)
{
}

static inline void intel_fbdev_set_suspend(struct drm_device *dev, int state, bool synchronous)
{
}

static inline struct intel_framebuffer *intel_fbdev_framebuffer(struct intel_fbdev *fbdev)
{
	return NULL;
}
#endif

#endif /* __INTEL_FBDEV_H__ */
