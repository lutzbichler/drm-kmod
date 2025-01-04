/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_GMCH_H__
#define __INTEL_GMCH_H__

#include <linux/types.h>

struct pci_dev;
struct xe_device;

int intel_gmch_bridge_setup(struct xe_device *xe);
void intel_gmch_bar_setup(struct xe_device *xe);
void intel_gmch_bar_teardown(struct xe_device *xe);
int intel_gmch_vga_set_state(struct xe_device *xe, bool enable_decode);
unsigned int intel_gmch_vga_set_decode(struct pci_dev *pdev, bool enable_decode);

#ifdef __FreeBSD__
void *bsd_intel_pci_bus_alloc_mem(device_t dev, int *rid, uintmax_t size,
    resource_size_t *start, resource_size_t *end);
void bsd_intel_pci_bus_release_mem(device_t dev, int rid, void *res);
#endif
#endif /* __INTEL_GMCH_H__ */
