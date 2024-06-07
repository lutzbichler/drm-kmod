/* Public domain */

#ifndef _XE_TRACE_GUC_FREEBSD_H_
#define _XE_TRACE_GUC_FREEBSD_H_

#include <sys/param.h>
#include <sys/ktr.h>

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

#endif /* _XE_TRACE_GUC_FREEBSD_H_ */

