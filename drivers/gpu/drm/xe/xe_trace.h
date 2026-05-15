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
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_timeout xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_gt_tlb_invalidation_fence_signal(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_signal xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_gt_tlb_invalidation_fence_send(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_send xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_gt_tlb_invalidation_fence_recv(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_recv xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_gt_tlb_invalidation_fence_create(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_create xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_gt_tlb_invalidation_fence_work_func(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_work_func xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_gt_tlb_invalidation_fence_cb(struct xe_device *xe, struct xe_gt_tlb_invalidation_fence *fence)
{
	CTR3(KTR_DRM, "xe_gt_tlb_invalidation_fence_cb xe %p fence %p seqno %d",
	    xe, fence, fence->seqno);
}

static inline void
trace_xe_hw_fence_create(struct xe_hw_fence *fence)
{
	CTR1(KTR_DRM, "xe_hw_fence_create fence %p", fence);
}

static inline void
trace_xe_hw_fence_signal(struct xe_hw_fence *fence)
{
	CTR1(KTR_DRM, "xe_hw_fence_signal fence %p", fence);
}

static inline void
trace_xe_hw_fence_try_signal(struct xe_hw_fence *fence)
{
	CTR1(KTR_DRM, "xe_hw_fence_try_signal fence %p", fence);
}

static inline void
trace_xe_exec_queue_create(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_create q %p", q);
}

static inline void
trace_xe_exec_queue_register(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_register q %p", q);
}

static inline void
trace_xe_exec_queue_deregister(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_deregister q %p", q);
}

static inline void
trace_xe_exec_queue_deregister_done(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_deregister_done q %p", q);
}

static inline void
trace_xe_exec_queue_reset(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_reset q %p", q);
}

static inline void
trace_xe_exec_queue_stop(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_stop q %p", q);
}

static inline void
trace_xe_exec_queue_close(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_close q %p", q);
}

static inline void
trace_xe_exec_queue_kill(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_kill q %p", q);
}

static inline void
trace_xe_exec_queue_destroy(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_destroy q %p", q);
}

static inline void
trace_xe_exec_queue_lr_cleanup(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_lr_cleanup q %p", q);
}

static inline void
trace_xe_exec_queue_memory_cat_error(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_memory_cat_error q %p", q);
}

static inline void
trace_xe_exec_queue_cleanup_entity(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_cleanup_entity q %p", q);
}

static inline void
trace_xe_exec_queue_scheduling_enable(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_scheduling_enable q %p", q);
}

static inline void
trace_xe_exec_queue_scheduling_disable(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_scheduling_disable q %p", q);
}

static inline void
trace_xe_exec_queue_scheduling_done(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_scheduling_done q %p", q);
}

static inline void
trace_xe_exec_queue_submit(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_submit q %p", q);
}

static inline void
trace_xe_exec_queue_resubmit(struct xe_exec_queue *q)
{
	CTR1(KTR_DRM, "xe_exec_queue_resubmit q %p", q);
}

static inline void
trace_xe_sched_job_create(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_create job %p", job);
}

static inline void
trace_xe_sched_job_exec(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_exec job %p", job);
}

static inline void
trace_xe_sched_job_run(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_run job %p", job);
}

static inline void
trace_xe_sched_job_free(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_free job %p", job);
}

static inline void
trace_xe_sched_job_ban(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_ban job %p", job);
}

static inline void
trace_xe_sched_job_timedout(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_timedout job %p", job);
}

static inline void
trace_xe_sched_msg_recv(struct xe_sched_msg *msg)
{
	CTR2(KTR_DRM, "xe_sched_msg_recv msg %p opcode %u", msg, msg->opcode);
}

static inline void
trace_xe_sched_msg_add(struct xe_sched_msg *msg)
{
	CTR2(KTR_DRM, "xe_sched_msg_add msg %p opcode %u", msg, msg->opcode);
}

static inline void
trace_xe_sched_job_error(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_error job %p", job);
}

static inline void
trace_xe_sched_job_set_error(struct xe_sched_job *job)
{
	CTR1(KTR_DRM, "xe_sched_job_set_error job %p", job);
}

static inline void
trace_xe_reg_rw(struct xe_gt *gt, bool read, u32 addr, u8 val, size_t size)
{
	CTR5(KTR_DRM, "xe_reg_rw gt %p %s addr 0x%x val 0x%x size %lu",
	    gt, read ? "R" : "W", addr, val, size);
}

static inline void
trace_xe_pm_runtime_get(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_runtime_get xe %p caller %p", xe, caller);
}

static inline void
trace_xe_pm_runtime_put(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_runtime_put xe %p caller %p", xe, caller);
}

static inline void
trace_xe_pm_resume(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_resume xe %p caller %p", xe, caller);
}

static inline void
trace_xe_pm_suspend(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_suspend xe %p caller %p", xe, caller);
}

static inline void
trace_xe_pm_runtime_resume(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_runtime_resume xe %p caller %p", xe, caller);
}

static inline void
trace_xe_pm_runtime_suspend(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_runtime_suspend xe %p caller %p", xe, caller);
}

static inline void
trace_xe_pm_runtime_get_ioctl(struct xe_device *xe, void *caller)
{
	CTR2(KTR_DRM, "xe_pm_runtime_get_ioctl xe %p caller %p", xe, caller);
}

#endif /* _XE_TRACE_FREEBSD_H_ */

