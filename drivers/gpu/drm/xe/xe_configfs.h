/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2025 Intel Corporation
 */
#ifndef _XE_CONFIGFS_H_
#define _XE_CONFIGFS_H_

#include <linux/limits.h>
#include <linux/types.h>

#include <xe_hw_engine_types.h>

struct pci_dev;

#if IS_ENABLED(CONFIG_CONFIGFS_FS)
int xe_configfs_init(void);
void xe_configfs_exit(void);
void xe_configfs_check_device(struct pci_dev *pdev);
bool xe_configfs_get_survivability_mode(struct pci_dev *pdev);
u64 xe_configfs_get_engines_allowed(struct pci_dev *pdev);
bool xe_configfs_get_psmi_enabled(struct pci_dev *pdev);
#ifdef __linux__
u32 xe_configfs_get_ctx_restore_post_bb(struct pci_dev *pdev, enum xe_engine_class,
					const u32 **cs);
#elif defined(__FreeBSD__)
u32 xe_configfs_get_ctx_restore_post_bb(struct pci_dev *pdev, enum xe_engine_class class,
                                        const u32 **cs);
#endif
#else
static inline int xe_configfs_init(void) { return 0; }
static inline void xe_configfs_exit(void) { }
static inline void xe_configfs_check_device(struct pci_dev *pdev) { }
static inline bool xe_configfs_get_survivability_mode(struct pci_dev *pdev) { return false; }
static inline u64 xe_configfs_get_engines_allowed(struct pci_dev *pdev) { return U64_MAX; }
static inline bool xe_configfs_get_psmi_enabled(struct pci_dev *pdev) { return false; }
#ifdef __linux__
static inline u32 xe_configfs_get_ctx_restore_post_bb(struct pci_dev *pdev, enum xe_engine_class,
						      const u32 **cs) { return 0; }
#elif defined(__FreeBSD__)
static inline u32 xe_configfs_get_ctx_restore_post_bb(struct pci_dev *pdev, enum xe_engine_class class,
						      const u32 **cs) { return 0; }
#endif

#endif

#endif
