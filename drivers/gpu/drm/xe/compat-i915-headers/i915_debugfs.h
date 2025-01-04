/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __I915_DEBUGFS_H__
#define __I915_DEBUGFS_H__

struct seq_file;
struct xe_bo;

static inline void i915_debugfs_describe_obj(struct seq_file *m, struct xe_bo *obj) {}

#endif /* __I915_DEBUGFS_H__ */
