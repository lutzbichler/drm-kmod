/* Public domain */
#ifndef _XE_TRACE_LRC_H_
#define _XE_TRACE_LRC_H_

#include <sys/param.h>
#include <sys/ktr.h>

#include "xe_exec_queue_types.h"
#include "xe_gt_types.h"
#include "xe_lrc.h"
#include "xe_lrc_types.h"

#define dev_name_lrc(lrc) \
	dev_name(gt_to_xe((lrc)->fence_ctx.gt)->drm.dev)

static void
trace_xe_lrc_update_timestamp(struct xe_lrc *lrc, u64 oid)
{
	CTR5(KTR_DRM, "lrc=:%p lrc->name=%s old=%llu new=%llu device_id:%s",
		 lrc, name, old, lrc->ctx_timestamp, dev_name_lrc(lrc));
}

static void
trace_xe_lrc_update_queue_timestamp(struct xe_lrc *lrc, uint64_t old)
{
	CTR6(KTR_DRM, "lrc=%p primary_lrc=%p lrc->name=%s old=%llu new=%llu "
		          "device_id:%s",
		 lrc, lrc->multi_queue.primary_lrc, name, old,
		 lrc->queue_timestamp, dev_name_lrc(lrc));
}

#endif
