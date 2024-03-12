/* Public domain */

#ifndef _XE_TRACE_FREEBSD_H_
#define _XE_TRACE_FREEBSD_H_

#include <sys/param.h>
#include <sys/ktr.h>

#include "xe_gpu_scheduler_types.h"
#include "xe_gt_tlb_invalidation_types.h"
#include "xe_sched_job_types.h"
#include "xe_vm_types.h"

static inline void
trace_xe_bo_move(struct xe_bo *bo, u32 new_mem_type, u32 old_mem_type, bool move_lacks_source)
{
}

static inline void
trace_xe_bo_cpu_fault(struct xe_bo *bo)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_timeout(struct xe_gt_tlb_invalidation_fence *fence) 
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_signal(struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_send(struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_recv(struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_create(struct xe_gt_tlb_invalidation_fence *fence)
{

}

static inline void
trace_xe_gt_tlb_invalidation_fence_work_func(struct xe_gt_tlb_invalidation_fence *fence)
{
    
}

static inline void
trace_xe_gt_tlb_invalidation_fence_cb(struct xe_gt_tlb_invalidation_fence *fence)
{
    
}

static inline void
trace_xe_hw_fence_create(struct xe_hw_fence *fence)
{
}

static inline void
trace_xe_hw_fence_free(struct xe_hw_fence *fence)
{
}

static inline void
trace_xe_hw_fence_signal(struct xe_hw_fence *fence)
{
}

static inline void
trace_xe_hw_fence_try_signal(struct xe_hw_fence *fence)
{
}

static inline void
trace_xe_guc_ctb_g2h(u32 head, u32 tail, u32 size, u32 space, u32 len)
{
}

static inline void
trace_xe_guc_ctb_h2g(u32 head, u32 tail, u32 size, u32 space, u32 len)
{
}

static inline void
trace_xe_guc_ct_g2h_flow_control(u32 head, u32 tail, u32 size, u32 space, u32 len)
{
}

static inline void
trace_xe_guc_ct_h2g_flow_control(u32 head, u32 tail, u32 size, u32 space, u32 len)
{
}

static inline void
trace_xe_exec_queue_create(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_register(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_deregister(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_deregister_done(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_reset(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_stop(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_close(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_kill(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_destroy(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_lr_cleanup(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_memory_cat_error(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_cleanup_entity(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_scheduling_enable(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_scheduling_disable(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_scheduling_done(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_submit(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_exec_queue_resubmit(struct xe_exec_queue *q)
{
}

static inline void
trace_xe_sched_job_create(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_job_exec(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_job_run(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_job_free(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_job_ban(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_job_timedout(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_msg_recv(struct xe_sched_msg *msg)
{
}

static inline void
trace_xe_sched_msg_add(struct xe_sched_msg *msg)
{
}

static inline void
trace_xe_sched_job_error(struct xe_sched_job *job)
{
}

static inline void
trace_xe_sched_job_set_error(struct xe_sched_job *job)
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
trace_xe_vma_fail(struct xe_vma *vma)
{
}

static inline void
trace_xe_vma_invalidate(struct xe_vma *vma)
{
}

#endif /* _XE_TRACE_FREEBSD_H_ */

