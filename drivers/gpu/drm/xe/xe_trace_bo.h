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
	CTR4(KTR_DRM, "xe_bo_move bo %p new %u old %u lacks_src %d",
	    bo, new_mem_type, old_mem_type, move_lacks_source);
}

static inline void
trace_xe_bo_cpu_fault(struct xe_bo *bo)
{
	CTR3(KTR_DRM, "xe_bo_cpu_fault bo %p size %lu flags %x",
	    bo, bo->size, bo->flags);
}

static inline void
trace_xe_vm_cpu_bind(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_cpu_bind vm %p asid %u", vm, vm->usm.asid);
}

static inline void
trace_xe_vm_create(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_create vm %p asid %u", vm, vm->usm.asid);
}

static inline void
trace_xe_vm_free(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_free vm %p asid %u", vm, vm->usm.asid);
}

static inline void
trace_xe_vm_kill(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_kill vm %p asid %u", vm, vm->usm.asid);
}

static inline void
trace_xe_vm_rebind_worker_enter(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_rebind_worker_enter vm %p asid %u",
	    vm, vm->usm.asid);
}

static inline void
trace_xe_vm_rebind_worker_exit(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_rebind_worker_exit vm %p asid %u",
	    vm, vm->usm.asid);
}

static inline void
trace_xe_vm_rebind_worker_retry(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_rebind_worker_retry vm %p asid %u",
	    vm, vm->usm.asid);
}

static inline void
trace_xe_vm_ops_fail(struct xe_vm *vm)
{
	CTR2(KTR_DRM, "xe_vm_ops_fail vm %p asid %u", vm, vm->usm.asid);
}

static inline void
trace_xe_vma_evict(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_evict vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_pagefault(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_pagefault vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_pf_bind(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_pf_bind vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_acc(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_acc vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_rebind_worker(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_rebind_worker vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_rebind_exec(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_rebind_exec vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_bind(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_bind vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_unbind(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_unbind vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

static inline void
trace_xe_vma_invalidate(struct xe_vma *vma)
{
	CTR3(KTR_DRM, "xe_vma_invalidate vma %p start %lx end %lx",
	    vma, xe_vma_start(vma), xe_vma_end(vma));
}

#endif /* _XE_TRACE_BO_FREEBSD_H_ */

