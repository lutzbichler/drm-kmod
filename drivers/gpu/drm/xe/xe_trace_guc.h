/* Public domain */

#ifndef _XE_TRACE_GUC_FREEBSD_H_
#define _XE_TRACE_GUC_FREEBSD_H_

#include <sys/param.h>
#include <sys/ktr.h>

static inline void
trace_xe_guc_ctb_g2h(struct xe_device *xe, u32 head, u32 tail, u32 size,
        u32 space, u32 len)
{
}

static inline void
trace_xe_guc_ctb_h2g(struct xe_device *xe, u32 head, u32 tail, u32 size,
        u32 space, u32 len)
{
}

static inline void
trace_xe_guc_ct_g2h_flow_control(struct xe_device *xe, u32 head, u32 tail,
        u32 size, u32 space, u32 len)
{
}

static inline void
trace_xe_guc_ct_h2g_flow_control(struct xe_device *xe, u32 head, u32 tail,
        u32 size, u32 space, u32 len)
{
}

#endif /* _XE_TRACE_GUC_FREEBSD_H_ */

