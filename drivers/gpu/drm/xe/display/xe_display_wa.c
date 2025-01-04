// SPDX-License-Identifier: MIT
/*
 * Copyright © 2024 Intel Corporation
 */

#include "intel_display_wa.h"

#include "xe_device.h"
#include "xe_wa.h"

#include <generated/xe_wa_oob.h>

bool intel_display_needs_wa_16023588340(struct xe_device *xe)
{
	return XE_WA(xe_root_mmio_gt(xe), 16023588340);
}
