// SPDX-License-Identifier: MIT

#include <linux/module.h>

#include "drm_dp_helper_internal.h"

#ifdef __linux__
MODULE_DESCRIPTION("DRM display adapter helper");
MODULE_LICENSE("GPL and additional rights");
#elif defined(__FreeBSD__)
MODULE_VERSION(drm_display_helper, 1);
MODULE_DEPEND(drm_display_helper, drmn, 2, 2, 2);
MODULE_DEPEND(drm_display_helper, linuxkpi, 1, 1, 1);
MODULE_DEPEND(drm_display_helper, linuxkpi_gplv2, 1, 1, 1);
#if __FreeBSD_version >= 1400085
MODULE_DEPEND(drmn, linuxkpi_hdmi, 1, 1, 1);
#endif
#ifdef CONFIG_DEBUG_FS
MODULE_DEPEND(drm_display_helper, lindebugfs, 1, 1, 1);
#endif
#endif

static int __init drm_display_helper_module_init(void)
{
	return drm_dp_aux_dev_init();
}

static void __exit drm_display_helper_module_exit(void)
{
	/* Call exit functions from specific dp helpers here */
	drm_dp_aux_dev_exit();
}

module_init(drm_display_helper_module_init);
module_exit(drm_display_helper_module_exit);
