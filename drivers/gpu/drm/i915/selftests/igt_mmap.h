/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2019 Intel Corporation
 */

#ifndef IGT_MMAP_H
#define IGT_MMAP_H

struct drm_i915_private;
struct drm_vma_offset_node;
struct file;

unsigned long igt_mmap_node(struct drm_i915_private *i915,
			    struct drm_vma_offset_node *node,
			    unsigned long addr,
			    unsigned long prot,
			    unsigned long flags);

unsigned long igt_mmap_offset_with_file(struct drm_i915_private *i915,
					u64 offset,
					unsigned long size,
					unsigned long prot,
					unsigned long flags,
					struct file *file);

#endif /* IGT_MMAP_H */
