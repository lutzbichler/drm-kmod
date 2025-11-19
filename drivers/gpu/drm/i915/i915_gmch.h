/* SPDX-License-Identifier: MIT */
/* Copyright © 2025 Intel Corporation */

#ifndef __I915_GMCH_H__
#define __I915_GMCH_H__

struct drm_i915_private;

int i915_gmch_bridge_setup(struct drm_i915_private *i915);
void i915_gmch_bar_setup(struct drm_i915_private *i915);
void i915_gmch_bar_teardown(struct drm_i915_private *i915);

#ifdef __FreeBSD__
void *bsd_intel_pci_bus_alloc_mem(device_t dev, int *rid, uintmax_t size,
    resource_size_t *start, resource_size_t *end);
void bsd_intel_pci_bus_release_mem(device_t dev, int rid, void *res);
#endif

#endif /* __I915_GMCH_H__ */
