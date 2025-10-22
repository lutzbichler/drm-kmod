// SPDX-License-Identifier: MIT
/* Copyright © 2025 Intel Corporation */


#include "intel_display_utils.h"

#ifdef CONFIG_X86
#include <asm/hypervisor.h>
#endif

bool intel_display_run_as_guest(struct intel_display *display)
{
#if IS_ENABLED(CONFIG_X86)
	return !hypervisor_is_type(X86_HYPER_NATIVE);
#else
	/* Not supported yet */
	return false;
#endif
}
