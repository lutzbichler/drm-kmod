/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_HOTPLUG_H__
#define __INTEL_HOTPLUG_H__

#include <linux/types.h>

struct intel_connector;
struct intel_digital_port;
struct intel_encoder;
struct xe_device;
enum port;

void intel_hpd_poll_enable(struct xe_device *xe);
void intel_hpd_poll_disable(struct xe_device *xe);
enum intel_hotplug_state intel_encoder_hotplug(struct intel_encoder *encoder,
					       struct intel_connector *connector);
void intel_hpd_irq_handler(struct xe_device *xe,
			   u32 pin_mask, u32 long_mask);
void intel_hpd_trigger_irq(struct intel_digital_port *dig_port);
void intel_hpd_init(struct xe_device *xe);
void intel_hpd_init_early(struct xe_device *xe);
void intel_hpd_cancel_work(struct xe_device *xe);
enum hpd_pin intel_hpd_pin_default(struct xe_device *xe,
				   enum port port);
bool intel_hpd_disable(struct xe_device *xe, enum hpd_pin pin);
void intel_hpd_enable(struct xe_device *dev_priv, enum hpd_pin pin);
void intel_hpd_debugfs_register(struct xe_device *xe);

void intel_hpd_enable_detection_work(struct xe_device *xe);
void intel_hpd_disable_detection_work(struct xe_device *xe);
bool intel_hpd_schedule_detection(struct xe_device *xe);

#endif /* __INTEL_HOTPLUG_H__ */
