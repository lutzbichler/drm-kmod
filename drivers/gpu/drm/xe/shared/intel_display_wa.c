// SPDX-License-Identifier: MIT
/*
 * Copyright © 2023 Intel Corporation
 */

#include "i915_drv.h"
#include "i915_reg.h"
#include "intel_de.h"
#include "intel_display_wa.h"

static void gen11_display_wa_apply(struct xe_device *xe)
{
	/* Wa_14010594013 */
	intel_de_rmw(xe, GEN8_CHICKEN_DCPR_1, 0, ICL_DELAY_PMRSP);
}

static void xe_d_display_wa_apply(struct xe_device *xe)
{
	/* Wa_14013723622 */
	intel_de_rmw(xe, CLKREQ_POLICY, CLKREQ_POLICY_MEM_UP_OVRD, 0);
}

static void adlp_display_wa_apply(struct xe_device *xe)
{
	/* Wa_22011091694:adlp */
	intel_de_rmw(xe, GEN9_CLKGATE_DIS_5, 0, DPCE_GATING_DIS);

	/* Bspec/49189 Initialize Sequence */
	intel_de_rmw(xe, GEN8_CHICKEN_DCPR_1, DDI_CLOCK_REG_ACCESS, 0);
}

void intel_display_wa_apply(struct xe_device *xe)
{
	if (IS_ALDERLAKE_P(xe))
		adlp_display_wa_apply(xe);
	else if (DISPLAY_VER(xe) == 12)
		xe_d_display_wa_apply(xe);
	else if (DISPLAY_VER(xe) == 11)
		gen11_display_wa_apply(xe);
}
