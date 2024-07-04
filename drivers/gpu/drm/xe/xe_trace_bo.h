/* Public domain */

#ifndef _XE_TRACE_BO_FREEBSD_H_
#define _XE_TRACE_BO_FREEBSD_H_

#include <sys/param.h>
#include <sys/ktr.h>

#include "xe_bo.h"
#include "xe_bo_types.h"
#include "xe_vm.h"

static inline void
trace_xe_bo_move(struct xe_bo *bo, u32 new_mem_type, u32 old_mem_type, bool move_lacks_source)
{
}

static inline void
trace_xe_bo_cpu_fault(struct xe_bo *bo)
{
}

static inline void
trace_xe_vm_cpu_bind(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_create(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_free(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_kill(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_rebind_worker_enter(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_rebind_worker_exit(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_rebind_worker_retry(struct xe_vm *vm)
{
}

static inline void
trace_xe_vm_ops_fail(struct xe_vm *vm)
{
}

static inline void
trace_xe_vma_evict(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_pagefault(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_pf_bind(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_acc(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_rebind_worker(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_rebind_exec(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_bind(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_unbind(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_invalidate(struct xe_vma *vma)
{
}

#endif /* _XE_TRACE_BO_FREEBSD_H_ */

