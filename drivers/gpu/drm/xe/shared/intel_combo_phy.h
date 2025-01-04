/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_COMBO_PHY_H__
#define __INTEL_COMBO_PHY_H__

#include <linux/types.h>

struct xe_device;
enum phy;

void intel_combo_phy_init(struct xe_device *xe);
void intel_combo_phy_uninit(struct xe_device *xe);
void intel_combo_phy_power_up_lanes(struct xe_device *xe,
				    enum phy phy, bool is_dsi,
				    int lane_count, bool lane_reversal);

#endif /* __INTEL_COMBO_PHY_H__ */
