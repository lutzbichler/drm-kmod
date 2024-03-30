/* Public domain */

#ifndef _XE_TRACE_FREEBSD_H_
#define _XE_TRACE_FREEBSD_H_

#include <sys/param.h>
#include <sys/ktr.h>

static inline void
trace_xe_vma_evict(struct xe_vma *vma)
{
}

static inline void
trace_xe_bo_move(struct xe_bo *bo, u32 new_mem_type, u32 old_mem_type, bool move_lacks_source)
{
}

static inline void
trace_xe_bo_cpu_fault(struct xe_bo *bo)
{
}

static inline void
trace_xe_exec_queue_close(struct xe_exec_queue *q)
{
}

#endif /* _XE_TRACE_FREEBSD_H_ */

