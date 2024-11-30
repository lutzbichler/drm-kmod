/* Public domain */
#ifndef _GPU_SCHEDULER_TRACE_FREEBSD_H_
#define _GPU_SCHEDULER_TRACE_FREEBSD_H_

static inline void
trace_drm_sched_job(void *sched_job, void *entity) {
	CTR2(KTR_DRM, "drm_sched_job %p, entity %p", sched_job, entity);
}

static inline void
trace_drm_run_job(void *sched_job, void *entity) {
	CTR2(KTR_DRM, "drm_sched_job %p, entity %p", sched_job, entity);
}

static inline void
trace_drm_sched_job_wait_dep(struct drm_sched_job *job, struct dma_fence *fence) {
	CTR2(KTR_DRM, "drm_process_wait_job %p fence %p", job, fence);
}

static inline void
trace_drm_sched_process_job(void *s_fence) {
	CTR1(KTR_DRM, "drm_process_sched_job %p", s_fence);
}

#endif /* _GPU_SCHEDULER_TRACE_FREEBSD_H_ */

