/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_OVERLAY_H__
#define __INTEL_OVERLAY_H__

struct drm_device;
struct drm_file;
struct drm_printer;
struct intel_overlay;
struct intel_overlay_error_state;
struct xe_device;

#ifdef I915
void intel_overlay_setup(struct xe_device *xe);
void intel_overlay_cleanup(struct xe_device *xe);
int intel_overlay_switch_off(struct intel_overlay *overlay);
int intel_overlay_put_image_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file_priv);
int intel_overlay_attrs_ioctl(struct drm_device *dev, void *data,
			      struct drm_file *file_priv);
void intel_overlay_reset(struct xe_device *xe);
struct intel_overlay_error_state *
intel_overlay_capture_error_state(struct xe_device *xe);
void intel_overlay_print_error_state(struct drm_printer *p,
				     struct intel_overlay_error_state *error);
#else
static inline void intel_overlay_setup(struct xe_device *xe)
{
}
static inline void intel_overlay_cleanup(struct xe_device *xe)
{
}
static inline int intel_overlay_switch_off(struct intel_overlay *overlay)
{
	return 0;
}
static inline int intel_overlay_put_image_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file_priv)
{
	return 0;
}
static inline int intel_overlay_attrs_ioctl(struct drm_device *dev, void *data,
					    struct drm_file *file_priv)
{
	return 0;
}
static inline void intel_overlay_reset(struct xe_device *xe)
{
}
static inline struct intel_overlay_error_state *
intel_overlay_capture_error_state(struct xe_device *xe)
{
	return NULL;
}
static inline void intel_overlay_print_error_state(struct drm_printer *p,
						   struct intel_overlay_error_state *error)
{
}
#endif

#endif /* __INTEL_OVERLAY_H__ */
