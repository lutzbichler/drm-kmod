/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2021 Intel Corporation
 */

#ifndef __VLV_DSI_H__
#define __VLV_DSI_H__

#include <linux/types.h>

enum port;
struct intel_dsi;
struct xe_device;

#ifdef I915
void vlv_dsi_wait_for_fifo_empty(struct intel_dsi *intel_dsi, enum port port);
enum mipi_dsi_pixel_format pixel_format_from_register_bits(u32 fmt);
void vlv_dsi_init(struct xe_device *xe);
#else
static inline void vlv_dsi_wait_for_fifo_empty(struct intel_dsi *intel_dsi, enum port port)
{
}
static inline enum mipi_dsi_pixel_format pixel_format_from_register_bits(u32 fmt)
{
	return 0;
}
static inline void vlv_dsi_init(struct xe_device *xe)
{
}
#endif

#endif /* __VLV_DSI_H__ */
