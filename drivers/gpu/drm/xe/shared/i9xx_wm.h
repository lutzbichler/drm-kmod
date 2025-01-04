/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __I9XX_WM_H__
#define __I9XX_WM_H__

#include <linux/types.h>

struct intel_crtc_state;
struct intel_plane_state;
struct xe_device;

#ifdef I915
bool ilk_disable_lp_wm(struct xe_device *xe);
void ilk_wm_sanitize(struct xe_device *xe);
bool intel_set_memory_cxsr(struct xe_device *xe, bool enable);
void i9xx_wm_init(struct xe_device *xe);
#else
static inline bool ilk_disable_lp_wm(struct xe_device *xe)
{
	return false;
}
static inline void ilk_wm_sanitize(struct xe_device *xe)
{
}
static inline bool intel_set_memory_cxsr(struct xe_device *xe, bool enable)
{
	return false;
}
static inline void i9xx_wm_init(struct xe_device *xe)
{
}
#endif

#endif /* __I9XX_WM_H__ */
