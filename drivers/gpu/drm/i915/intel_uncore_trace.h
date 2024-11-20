/* Public domain */

#ifndef _INTEL_UNCORE_TRACE_FREEBSD_H_
#define _INTEL_UNCORE_TRACE_FREEBSD_H_

#include <sys/param.h>
#include <sys/ktr.h>

static inline void
trace_i915_reg_rw(boolean_t rw, i915_reg_t reg, uint64_t val, int sz, bool trace)
{
 
        CTR4(KTR_DRM_REG, "[%x/%d] %c %x", reg.reg, sz, rw ? "w" : "r", val);
}

#endif /* _INTEL_UNCORE_TRACE_FREEBSD_H_ */
