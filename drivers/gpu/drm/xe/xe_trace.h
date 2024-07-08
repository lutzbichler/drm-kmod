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
trace_xe_gt_tlb_invalidation_fence_timeout(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_signal(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_send(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_recv(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
}

static inline void
trace_xe_gt_tlb_invalidation_fence_create(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{

}

static inline void
trace_xe_gt_tlb_invalidation_fence_work_func(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
    
}

static inline void
trace_xe_gt_tlb_invalidation_fence_cb(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
    
}

static inline void
trace_xe_hw_fence_create(struct xe_hw_fence *fence)
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
trace_xe_reg_rw(struct xe_gt *gt, bool read, u32 addr, u8 val, size_t size)
{
}

#endif /* _XE_TRACE_FREEBSD_H_ */

