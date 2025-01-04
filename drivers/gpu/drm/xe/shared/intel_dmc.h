/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_DMC_H__
#define __INTEL_DMC_H__

#include <linux/types.h>

enum pipe;
struct drm_printer;
struct xe_device;

void intel_dmc_init(struct xe_device *xe);
void intel_dmc_load_program(struct xe_device *xe);
void intel_dmc_disable_program(struct xe_device *xe);
void intel_dmc_enable_pipe(struct xe_device *xe, enum pipe pipe);
void intel_dmc_disable_pipe(struct xe_device *xe, enum pipe pipe);
void intel_dmc_fini(struct xe_device *xe);
void intel_dmc_suspend(struct xe_device *xe);
void intel_dmc_resume(struct xe_device *xe);
bool intel_dmc_has_payload(struct xe_device *xe);
void intel_dmc_debugfs_register(struct xe_device *xe);
void intel_dmc_print_error_state(struct drm_printer *p,
				 struct xe_device *xe);

void assert_dmc_loaded(struct xe_device *xe);

#endif /* __INTEL_DMC_H__ */
