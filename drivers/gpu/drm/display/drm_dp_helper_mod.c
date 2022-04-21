// SPDX-License-Identifier: MIT

#include <linux/module.h>

#include "drm_dp_helper_internal.h"

#ifdef __linux__
MODULE_DESCRIPTION("DRM DisplayPort helper");
MODULE_LICENSE("GPL and additional rights");
#elif defined(__FreeBSD__)
MODULE_VERSION(drm_dp_helper, 1);
MODULE_DEPEND(drm_dp_helper, drmn, 2, 2, 2);
MODULE_DEPEND(drm_dp_helper, linuxkpi, 1, 1, 1);
MODULE_DEPEND(drm_dp_helper, linuxkpi_gplv2, 1, 1, 1);
#ifdef CONFIG_DEBUG_FS
MODULE_DEPEND(drm_dp_helper, lindebugfs, 1, 1, 1);
#endif
#endif

static int __init drm_dp_helper_module_init(void)
{
	return drm_dp_aux_dev_init();
}

static void __exit drm_dp_helper_module_exit(void)
{
	/* Call exit functions from specific dp helpers here */
	drm_dp_aux_dev_exit();
}

module_init(drm_dp_helper_module_init);
module_exit(drm_dp_helper_module_exit);
