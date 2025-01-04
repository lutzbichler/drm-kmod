/* SPDX-License-Identifier: MIT */
/* Copyright © 2024 Intel Corporation */

/*
 * This header is for transitional struct intel_display conversion helpers only.
 */

#ifndef __INTEL_DISPLAY_CONVERSION__
#define __INTEL_DISPLAY_CONVERSION__

/*
 * Transitional macro to optionally convert struct drm_i915_private * to struct
 * intel_display *, also accepting the latter.
 */
#define __to_intel_display(p)						\
	_Generic(p,							\
		 const struct xe_device *: (&((const struct xe_device *)(p))->display), \
		 struct xe_device *: (&((struct xe_device *)(p))->display), \
		 const struct intel_display *: (p),			\
		 struct intel_display *: (p))

#endif /* __INTEL_DISPLAY_CONVERSION__ */
