/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2022 Intel Corporation
 */

#ifndef __INTEL_DKL_PHY_H__
#define __INTEL_DKL_PHY_H__

#include <linux/types.h>

#include "intel_dkl_phy_regs.h"

struct xe_device;

void intel_dkl_phy_init(struct xe_device *xe);
u32
intel_dkl_phy_read(struct xe_device *xe, struct intel_dkl_phy_reg reg);
void
intel_dkl_phy_write(struct xe_device *xe, struct intel_dkl_phy_reg reg, u32 val);
void
intel_dkl_phy_rmw(struct xe_device *xe, struct intel_dkl_phy_reg reg, u32 clear, u32 set);
void
intel_dkl_phy_posting_read(struct xe_device *xe, struct intel_dkl_phy_reg reg);

#endif /* __INTEL_DKL_PHY_H__ */
