/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2022-2023 Intel Corporation
 */

#ifndef __INTEL_DISPLAY_DRIVER_H__
#define __INTEL_DISPLAY_DRIVER_H__

#include <linux/types.h>

struct drm_atomic_state;
struct drm_modeset_acquire_ctx;
struct pci_dev;
struct xe_device;

bool intel_display_driver_probe_defer(struct pci_dev *pdev);
void intel_display_driver_init_hw(struct xe_device *xe);
void intel_display_driver_early_probe(struct xe_device *xe);
int intel_display_driver_probe_noirq(struct xe_device *xe);
int intel_display_driver_probe_nogem(struct xe_device *xe);
int intel_display_driver_probe(struct xe_device *xe);
void intel_display_driver_register(struct xe_device *xe);
void intel_display_driver_remove(struct xe_device *xe);
void intel_display_driver_remove_noirq(struct xe_device *xe);
void intel_display_driver_remove_nogem(struct xe_device *xe);
void intel_display_driver_unregister(struct xe_device *xe);
int intel_display_driver_suspend(struct xe_device *xe);
void intel_display_driver_resume(struct xe_device *xe);

/* interface for intel_display_reset.c */
int __intel_display_driver_resume(struct xe_device *xe,
				  struct drm_atomic_state *state,
				  struct drm_modeset_acquire_ctx *ctx);

void intel_display_driver_enable_user_access(struct xe_device *xe);
void intel_display_driver_disable_user_access(struct xe_device *xe);
void intel_display_driver_suspend_access(struct xe_device *xe);
void intel_display_driver_resume_access(struct xe_device *xe);
bool intel_display_driver_check_access(struct xe_device *xe);

#endif /* __INTEL_DISPLAY_DRIVER_H__ */

