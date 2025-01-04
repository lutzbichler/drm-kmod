/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2023 Intel Corporation
 */

#ifndef __INTEL_HDCP_GSC_H__
#define __INTEL_HDCP_GSC_H__

#include <linux/err.h>
#include <linux/types.h>

struct intel_hdcp_gsc_message;
struct xe_device;

bool intel_hdcp_gsc_cs_required(struct xe_device *xe);
ssize_t intel_hdcp_gsc_msg_send(struct xe_device *xe, u8 *msg_in,
				size_t msg_in_len, u8 *msg_out,
				size_t msg_out_len);
int intel_hdcp_gsc_init(struct xe_device *xe);
void intel_hdcp_gsc_fini(struct xe_device *xe);
bool intel_hdcp_gsc_check_status(struct xe_device *xe);

#endif /* __INTEL_HDCP_GCS_H__ */
