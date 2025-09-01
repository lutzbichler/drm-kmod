/* Public domain */
#ifndef _GPU_SCHEDULER_TRACE_FREEBSD_H_
#define _GPU_SCHEDULER_TRACE_FREEBSD_H_

static inline void
trace_drm_sched_job_queue(void *sched_job, void *entity) {
	CTR2(KTR_DRM, "drm_sched_job_queue %p, entity %p", sched_job, entity);
}

static inline void
trace_drm_sched_job_run(void *sched_job, void *entity) {
	CTR2(KTR_DRM, "drm_sched_job_run %p, entity %p", sched_job, entity);
}

static inline void
trace_drm_sched_job_unschedulable(struct drm_sched_job *job, struct dma_fence *fence) {
	CTR2(KTR_DRM, "drm_sched_job_unschedulable %p fence %p", job, fence);
}

static inline void
trace_drm_sched_job_done(void *s_fence) {
	CTR1(KTR_DRM, "drm_sched_job_done %p", s_fence);
}

static inline void
trace_drm_sched_job_add_dep(struct drm_sched_job *sched_job, struct dma_fence *fence)
{
	CTR2(KTR_DRM, "drm_sched_job_add_dep %p fence %p", job, fence);
}

#define trace_drm_sched_job_unschedulable_enabled()	false

#define trace_drm_sched_job_add_dep_enabled()	false

#endif /* _GPU_SCHEDULER_TRACE_FREEBSD_H_ */

