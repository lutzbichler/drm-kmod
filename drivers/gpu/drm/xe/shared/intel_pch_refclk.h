/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2021 Intel Corporation
 */

#ifndef _INTEL_PCH_REFCLK_H_
#define _INTEL_PCH_REFCLK_H_

#include <linux/types.h>

struct intel_crtc_state;
struct xe_device;

#ifdef I915
void lpt_program_iclkip(const struct intel_crtc_state *crtc_state);
void lpt_disable_iclkip(struct xe_device *xe);
int lpt_get_iclkip(struct xe_device *xe);
int lpt_iclkip(const struct intel_crtc_state *crtc_state);

void intel_init_pch_refclk(struct xe_device *xe);
void lpt_disable_clkout_dp(struct xe_device *xe);
#else
static inline void lpt_program_iclkip(const struct intel_crtc_state *crtc_state)
{
}
static inline void lpt_disable_iclkip(struct xe_device *dev_priv)
{
}
static inline int lpt_get_iclkip(struct xe_device *xe)
{
	return 0;
}
static inline int lpt_iclkip(const struct intel_crtc_state *crtc_state)
{
	return 0;
}
static inline void intel_init_pch_refclk(struct xe_device *xe)
{
}
static inline void lpt_disable_clkout_dp(struct xe_device *xe)
{
}
#endif

#endif
