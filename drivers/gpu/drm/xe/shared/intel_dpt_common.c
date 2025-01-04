// SPDX-License-Identifier: MIT
/*
 * Copyright © 2023 Intel Corporation
 */

#include "i915_reg.h"
#include "intel_de.h"
#include "intel_display_types.h"
#include "intel_dpt_common.h"
#include "skl_universal_plane_regs.h"

void intel_dpt_configure(struct intel_crtc *crtc)
{
	struct xe_device *xe = to_xe(crtc->base.dev);

	if (DISPLAY_VER(xe) == 14) {
		enum pipe pipe = crtc->pipe;
		enum plane_id plane_id;

		for_each_plane_id_on_crtc(crtc, plane_id) {
			if (plane_id == PLANE_CURSOR)
				continue;

			intel_de_rmw(xe, PLANE_CHICKEN(pipe, plane_id),
				     PLANE_CHICKEN_DISABLE_DPT,
				     xe->display.params.enable_dpt ? 0 :
				     PLANE_CHICKEN_DISABLE_DPT);
		}
	} else if (DISPLAY_VER(xe) == 13) {
		intel_de_rmw(xe, CHICKEN_MISC_2,
			     CHICKEN_MISC_DISABLE_DPT,
			     xe->display.params.enable_dpt ? 0 :
			     CHICKEN_MISC_DISABLE_DPT);
	}
}
