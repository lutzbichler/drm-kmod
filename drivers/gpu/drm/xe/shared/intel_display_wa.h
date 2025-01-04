/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_DISPLAY_WA_H__
#define __INTEL_DISPLAY_WA_H__

#include <linux/types.h>

struct xe_device;

void intel_display_wa_apply(struct xe_device *xe);

#ifdef I915
static inline bool intel_display_needs_wa_16023588340(struct xe_device *xe) { return false; }
#else
bool intel_display_needs_wa_16023588340(struct xe_device *xe);
#endif

#endif
