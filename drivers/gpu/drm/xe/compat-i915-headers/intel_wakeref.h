/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef COMPAT_I915_HEADER_INTEL_WAKEREF_
#define COMPAT_I915_HEADER_INTEL_WAKEREF_

#include <linux/types.h>

typedef unsigned long intel_wakeref_t;

#define INTEL_WAKEREF_DEF ((intel_wakeref_t)(-1))

#endif /* COMPAT_I915_HEADER_INTEL_WAKEREF_ */

