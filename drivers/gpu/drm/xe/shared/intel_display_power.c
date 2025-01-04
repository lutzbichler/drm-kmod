/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifdef __FreeBSD__
#include <linux/seq_file.h>
#endif
#include <linux/string_helpers.h>

#include "i915_drv.h"
#include "i915_irq.h"
#include "i915_reg.h"
#include "intel_backlight_regs.h"
#include "intel_cdclk.h"
#include "intel_clock_gating.h"
#include "intel_combo_phy.h"
#include "intel_de.h"
#include "intel_display_power.h"
#include "intel_display_power_map.h"
#include "intel_display_power_well.h"
#include "intel_display_types.h"
#include "intel_dmc.h"
#include "intel_mchbar_regs.h"
#include "intel_pch_refclk.h"
#include "intel_pcode.h"
#include "intel_pmdemand.h"
#include "intel_pps_regs.h"
#include "intel_snps_phy.h"
#include "skl_watermark.h"
#include "skl_watermark_regs.h"
#include "vlv_sideband.h"

#define for_each_power_domain_well(__xe, __power_well, __domain)	\
	for_each_power_well(__xe, __power_well)				\
		for_each_if(test_bit((__domain), (__power_well)->domains.bits))

#define for_each_power_domain_well_reverse(__xe, __power_well, __domain) \
	for_each_power_well_reverse(__xe, __power_well)		        \
		for_each_if(test_bit((__domain), (__power_well)->domains.bits))

static const char *
intel_display_power_domain_str(enum intel_display_power_domain domain)
{
	switch (domain) {
	case POWER_DOMAIN_DISPLAY_CORE:
		return "DISPLAY_CORE";
	case POWER_DOMAIN_PIPE_A:
		return "PIPE_A";
	case POWER_DOMAIN_PIPE_B:
		return "PIPE_B";
	case POWER_DOMAIN_PIPE_C:
		return "PIPE_C";
	case POWER_DOMAIN_PIPE_D:
		return "PIPE_D";
	case POWER_DOMAIN_PIPE_PANEL_FITTER_A:
		return "PIPE_PANEL_FITTER_A";
	case POWER_DOMAIN_PIPE_PANEL_FITTER_B:
		return "PIPE_PANEL_FITTER_B";
	case POWER_DOMAIN_PIPE_PANEL_FITTER_C:
		return "PIPE_PANEL_FITTER_C";
	case POWER_DOMAIN_PIPE_PANEL_FITTER_D:
		return "PIPE_PANEL_FITTER_D";
	case POWER_DOMAIN_TRANSCODER_A:
		return "TRANSCODER_A";
	case POWER_DOMAIN_TRANSCODER_B:
		return "TRANSCODER_B";
	case POWER_DOMAIN_TRANSCODER_C:
		return "TRANSCODER_C";
	case POWER_DOMAIN_TRANSCODER_D:
		return "TRANSCODER_D";
	case POWER_DOMAIN_TRANSCODER_EDP:
		return "TRANSCODER_EDP";
	case POWER_DOMAIN_TRANSCODER_DSI_A:
		return "TRANSCODER_DSI_A";
	case POWER_DOMAIN_TRANSCODER_DSI_C:
		return "TRANSCODER_DSI_C";
	case POWER_DOMAIN_TRANSCODER_VDSC_PW2:
		return "TRANSCODER_VDSC_PW2";
	case POWER_DOMAIN_PORT_DDI_LANES_A:
		return "PORT_DDI_LANES_A";
	case POWER_DOMAIN_PORT_DDI_LANES_B:
		return "PORT_DDI_LANES_B";
	case POWER_DOMAIN_PORT_DDI_LANES_C:
		return "PORT_DDI_LANES_C";
	case POWER_DOMAIN_PORT_DDI_LANES_D:
		return "PORT_DDI_LANES_D";
	case POWER_DOMAIN_PORT_DDI_LANES_E:
		return "PORT_DDI_LANES_E";
	case POWER_DOMAIN_PORT_DDI_LANES_F:
		return "PORT_DDI_LANES_F";
	case POWER_DOMAIN_PORT_DDI_LANES_TC1:
		return "PORT_DDI_LANES_TC1";
	case POWER_DOMAIN_PORT_DDI_LANES_TC2:
		return "PORT_DDI_LANES_TC2";
	case POWER_DOMAIN_PORT_DDI_LANES_TC3:
		return "PORT_DDI_LANES_TC3";
	case POWER_DOMAIN_PORT_DDI_LANES_TC4:
		return "PORT_DDI_LANES_TC4";
	case POWER_DOMAIN_PORT_DDI_LANES_TC5:
		return "PORT_DDI_LANES_TC5";
	case POWER_DOMAIN_PORT_DDI_LANES_TC6:
		return "PORT_DDI_LANES_TC6";
	case POWER_DOMAIN_PORT_DDI_IO_A:
		return "PORT_DDI_IO_A";
	case POWER_DOMAIN_PORT_DDI_IO_B:
		return "PORT_DDI_IO_B";
	case POWER_DOMAIN_PORT_DDI_IO_C:
		return "PORT_DDI_IO_C";
	case POWER_DOMAIN_PORT_DDI_IO_D:
		return "PORT_DDI_IO_D";
	case POWER_DOMAIN_PORT_DDI_IO_E:
		return "PORT_DDI_IO_E";
	case POWER_DOMAIN_PORT_DDI_IO_F:
		return "PORT_DDI_IO_F";
	case POWER_DOMAIN_PORT_DDI_IO_TC1:
		return "PORT_DDI_IO_TC1";
	case POWER_DOMAIN_PORT_DDI_IO_TC2:
		return "PORT_DDI_IO_TC2";
	case POWER_DOMAIN_PORT_DDI_IO_TC3:
		return "PORT_DDI_IO_TC3";
	case POWER_DOMAIN_PORT_DDI_IO_TC4:
		return "PORT_DDI_IO_TC4";
	case POWER_DOMAIN_PORT_DDI_IO_TC5:
		return "PORT_DDI_IO_TC5";
	case POWER_DOMAIN_PORT_DDI_IO_TC6:
		return "PORT_DDI_IO_TC6";
	case POWER_DOMAIN_PORT_DSI:
		return "PORT_DSI";
	case POWER_DOMAIN_PORT_CRT:
		return "PORT_CRT";
	case POWER_DOMAIN_PORT_OTHER:
		return "PORT_OTHER";
	case POWER_DOMAIN_VGA:
		return "VGA";
	case POWER_DOMAIN_AUDIO_MMIO:
		return "AUDIO_MMIO";
	case POWER_DOMAIN_AUDIO_PLAYBACK:
		return "AUDIO_PLAYBACK";
	case POWER_DOMAIN_AUX_IO_A:
		return "AUX_IO_A";
	case POWER_DOMAIN_AUX_IO_B:
		return "AUX_IO_B";
	case POWER_DOMAIN_AUX_IO_C:
		return "AUX_IO_C";
	case POWER_DOMAIN_AUX_IO_D:
		return "AUX_IO_D";
	case POWER_DOMAIN_AUX_IO_E:
		return "AUX_IO_E";
	case POWER_DOMAIN_AUX_IO_F:
		return "AUX_IO_F";
	case POWER_DOMAIN_AUX_A:
		return "AUX_A";
	case POWER_DOMAIN_AUX_B:
		return "AUX_B";
	case POWER_DOMAIN_AUX_C:
		return "AUX_C";
	case POWER_DOMAIN_AUX_D:
		return "AUX_D";
	case POWER_DOMAIN_AUX_E:
		return "AUX_E";
	case POWER_DOMAIN_AUX_F:
		return "AUX_F";
	case POWER_DOMAIN_AUX_USBC1:
		return "AUX_USBC1";
	case POWER_DOMAIN_AUX_USBC2:
		return "AUX_USBC2";
	case POWER_DOMAIN_AUX_USBC3:
		return "AUX_USBC3";
	case POWER_DOMAIN_AUX_USBC4:
		return "AUX_USBC4";
	case POWER_DOMAIN_AUX_USBC5:
		return "AUX_USBC5";
	case POWER_DOMAIN_AUX_USBC6:
		return "AUX_USBC6";
	case POWER_DOMAIN_AUX_TBT1:
		return "AUX_TBT1";
	case POWER_DOMAIN_AUX_TBT2:
		return "AUX_TBT2";
	case POWER_DOMAIN_AUX_TBT3:
		return "AUX_TBT3";
	case POWER_DOMAIN_AUX_TBT4:
		return "AUX_TBT4";
	case POWER_DOMAIN_AUX_TBT5:
		return "AUX_TBT5";
	case POWER_DOMAIN_AUX_TBT6:
		return "AUX_TBT6";
	case POWER_DOMAIN_GMBUS:
		return "GMBUS";
	case POWER_DOMAIN_INIT:
		return "INIT";
	case POWER_DOMAIN_GT_IRQ:
		return "GT_IRQ";
	case POWER_DOMAIN_DC_OFF:
		return "DC_OFF";
	case POWER_DOMAIN_TC_COLD_OFF:
		return "TC_COLD_OFF";
	default:
		MISSING_CASE(domain);
		return "?";
	}
}

static bool __intel_display_power_is_enabled(struct xe_device *xe,
					     enum intel_display_power_domain domain)
{
	struct i915_power_well *power_well;
	bool is_enabled;

	if (pm_runtime_suspended(xe->drm.dev))
		return false;

	is_enabled = true;

	for_each_power_domain_well_reverse(xe, power_well, domain) {
		if (intel_power_well_is_always_on(power_well))
			continue;

		if (!intel_power_well_is_enabled_cached(power_well)) {
			is_enabled = false;
			break;
		}
	}

	return is_enabled;
}

/**
 * intel_display_power_is_enabled - check for a power domain
 * @xe: i915 device instance
 * @domain: power domain to check
 *
 * This function can be used to check the hw power domain state. It is mostly
 * used in hardware state readout functions. Everywhere else code should rely
 * upon explicit power domain reference counting to ensure that the hardware
 * block is powered up before accessing it.
 *
 * Callers must hold the relevant modesetting locks to ensure that concurrent
 * threads can't disable the power well while the caller tries to read a few
 * registers.
 *
 * Returns:
 * True when the power domain is enabled, false otherwise.
 */
bool intel_display_power_is_enabled(struct xe_device *xe,
				    enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains;
	bool ret;

	power_domains = &xe->display.power.domains;

	mutex_lock(&power_domains->lock);
	ret = __intel_display_power_is_enabled(xe, domain);
	mutex_unlock(&power_domains->lock);

	return ret;
}

static u32
sanitize_target_dc_state(struct xe_device *xe,
			 u32 target_dc_state)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	static const u32 states[] = {
		DC_STATE_EN_UPTO_DC6,
		DC_STATE_EN_UPTO_DC5,
		DC_STATE_EN_DC3CO,
		DC_STATE_DISABLE,
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(states) - 1; i++) {
		if (target_dc_state != states[i])
			continue;

		if (power_domains->allowed_dc_mask & target_dc_state)
			break;

		target_dc_state = states[i + 1];
	}

	return target_dc_state;
}

/**
 * intel_display_power_set_target_dc_state - Set target dc state.
 * @xe: xe device
 * @state: state which needs to be set as target_dc_state.
 *
 * This function set the "DC off" power well target_dc_state,
 * based upon this target_dc_stste, "DC off" power well will
 * enable desired DC state.
 */
void intel_display_power_set_target_dc_state(struct xe_device *xe,
					     u32 state)
{
	struct i915_power_well *power_well;
	bool dc_off_enabled;
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	mutex_lock(&power_domains->lock);
	power_well = lookup_power_well(xe, SKL_DISP_DC_OFF);

	if (drm_WARN_ON(&xe->drm, !power_well))
		goto unlock;

	state = sanitize_target_dc_state(xe, state);

	if (state == power_domains->target_dc_state)
		goto unlock;

	dc_off_enabled = intel_power_well_is_enabled(xe, power_well);
	/*
	 * If DC off power well is disabled, need to enable and disable the
	 * DC off power well to effect target DC state.
	 */
	if (!dc_off_enabled)
		intel_power_well_enable(xe, power_well);

	power_domains->target_dc_state = state;

	if (!dc_off_enabled)
		intel_power_well_disable(xe, power_well);

unlock:
	mutex_unlock(&power_domains->lock);
}

static void __async_put_domains_mask(struct i915_power_domains *power_domains,
				     struct intel_power_domain_mask *mask)
{
	bitmap_or(mask->bits,
		  power_domains->async_put_domains[0].bits,
		  power_domains->async_put_domains[1].bits,
		  POWER_DOMAIN_NUM);
}

#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)

static bool
assert_async_put_domain_masks_disjoint(struct i915_power_domains *power_domains)
{
	struct xe_device *xe = container_of(power_domains,
						     struct xe_device,
						     display.power.domains);

	return !drm_WARN_ON(&xe->drm,
			    bitmap_intersects(power_domains->async_put_domains[0].bits,
					      power_domains->async_put_domains[1].bits,
					      POWER_DOMAIN_NUM));
}

static bool
__async_put_domains_state_ok(struct i915_power_domains *power_domains)
{
	struct xe_device *xe = container_of(power_domains,
						     struct xe_device,
						     display.power.domains);
	struct intel_power_domain_mask async_put_mask;
	enum intel_display_power_domain domain;
	bool err = false;

	err |= !assert_async_put_domain_masks_disjoint(power_domains);
	__async_put_domains_mask(power_domains, &async_put_mask);
	err |= drm_WARN_ON(&xe->drm,
			   !!power_domains->async_put_wakeref !=
			   !bitmap_empty(async_put_mask.bits, POWER_DOMAIN_NUM));

	for_each_power_domain(domain, &async_put_mask)
		err |= drm_WARN_ON(&xe->drm,
				   power_domains->domain_use_count[domain] != 1);

	return !err;
}

static void print_power_domains(struct i915_power_domains *power_domains,
				const char *prefix, struct intel_power_domain_mask *mask)
{
	struct xe_device *xe = container_of(power_domains,
						     struct xe_device,
						     display.power.domains);
	enum intel_display_power_domain domain;

	drm_dbg(&xe->drm, "%s (%d):\n", prefix, bitmap_weight(mask->bits, POWER_DOMAIN_NUM));
	for_each_power_domain(domain, mask)
		drm_dbg(&xe->drm, "%s use_count %d\n",
			intel_display_power_domain_str(domain),
			power_domains->domain_use_count[domain]);
}

static void
print_async_put_domains_state(struct i915_power_domains *power_domains)
{
	struct xe_device *xe = container_of(power_domains,
						     struct xe_device,
						     display.power.domains);

	drm_dbg(&xe->drm, "async_put_wakeref: %s\n",
		str_yes_no(power_domains->async_put_wakeref));

	print_power_domains(power_domains, "async_put_domains[0]",
			    &power_domains->async_put_domains[0]);
	print_power_domains(power_domains, "async_put_domains[1]",
			    &power_domains->async_put_domains[1]);
}

static void
verify_async_put_domains_state(struct i915_power_domains *power_domains)
{
	if (!__async_put_domains_state_ok(power_domains))
		print_async_put_domains_state(power_domains);
}

#else

static void
assert_async_put_domain_masks_disjoint(struct i915_power_domains *power_domains)
{
}

static void
verify_async_put_domains_state(struct i915_power_domains *power_domains)
{
}

#endif /* CONFIG_DRM_I915_DEBUG_RUNTIME_PM */

static void async_put_domains_mask(struct i915_power_domains *power_domains,
				   struct intel_power_domain_mask *mask)

{
	assert_async_put_domain_masks_disjoint(power_domains);

	__async_put_domains_mask(power_domains, mask);
}

static void
async_put_domains_clear_domain(struct i915_power_domains *power_domains,
			       enum intel_display_power_domain domain)
{
	assert_async_put_domain_masks_disjoint(power_domains);

	clear_bit(domain, power_domains->async_put_domains[0].bits);
	clear_bit(domain, power_domains->async_put_domains[1].bits);
}

static void
cancel_async_put_work(struct i915_power_domains *power_domains, bool sync)
{
	if (sync)
		cancel_delayed_work_sync(&power_domains->async_put_work);
	else
		cancel_delayed_work(&power_domains->async_put_work);

	power_domains->async_put_next_delay = 0;
}

static bool
intel_display_power_grab_async_put_ref(struct xe_device *xe,
				       enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct intel_power_domain_mask async_put_mask;
	bool ret = false;

	async_put_domains_mask(power_domains, &async_put_mask);
	if (!test_bit(domain, async_put_mask.bits))
		goto out_verify;

	async_put_domains_clear_domain(power_domains, domain);

	ret = true;

	async_put_domains_mask(power_domains, &async_put_mask);
	if (!bitmap_empty(async_put_mask.bits, POWER_DOMAIN_NUM))
		goto out_verify;

	cancel_async_put_work(power_domains, false);
	intel_runtime_pm_put_raw(&xe->runtime_pm,
				 fetch_and_zero(&power_domains->async_put_wakeref));
out_verify:
	verify_async_put_domains_state(power_domains);

	return ret;
}

static void
__intel_display_power_get_domain(struct xe_device *xe,
				 enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *power_well;

	if (intel_display_power_grab_async_put_ref(xe, domain))
		return;

	for_each_power_domain_well(xe, power_well, domain)
		intel_power_well_get(xe, power_well);

	power_domains->domain_use_count[domain]++;
}

/**
 * intel_display_power_get - grab a power domain reference
 * @xe: xe device instance
 * @domain: power domain to reference
 *
 * This function grabs a power domain reference for @domain and ensures that the
 * power domain and all its parents are powered up. Therefore users should only
 * grab a reference to the innermost power domain they need.
 *
 * Any power domain reference obtained by this function must have a symmetric
 * call to intel_display_power_put() to release the reference again.
 */
intel_wakeref_t intel_display_power_get(struct xe_device *xe,
					enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	intel_wakeref_t wakeref = intel_runtime_pm_get(&xe->runtime_pm);

	mutex_lock(&power_domains->lock);
	__intel_display_power_get_domain(xe, domain);
	mutex_unlock(&power_domains->lock);

	return wakeref;
}

/**
 * intel_display_power_get_if_enabled - grab a reference for an enabled display power domain
 * @xe: xe device instance
 * @domain: power domain to reference
 *
 * This function grabs a power domain reference for @domain and ensures that the
 * power domain and all its parents are powered up. Therefore users should only
 * grab a reference to the innermost power domain they need.
 *
 * Any power domain reference obtained by this function must have a symmetric
 * call to intel_display_power_put() to release the reference again.
 */
intel_wakeref_t
intel_display_power_get_if_enabled(struct xe_device *xe,
				   enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	intel_wakeref_t wakeref;
	bool is_enabled;

	wakeref = intel_runtime_pm_get_if_in_use(&xe->runtime_pm);
	if (!wakeref)
		return false;

	mutex_lock(&power_domains->lock);

	if (__intel_display_power_is_enabled(xe, domain)) {
		__intel_display_power_get_domain(xe, domain);
		is_enabled = true;
	} else {
		is_enabled = false;
	}

	mutex_unlock(&power_domains->lock);

	if (!is_enabled) {
		intel_runtime_pm_put(&xe->runtime_pm, wakeref);
		wakeref = 0;
	}

	return wakeref;
}

static void
__intel_display_power_put_domain(struct xe_device *xe,
				 enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains;
	struct i915_power_well *power_well;
	const char *name = intel_display_power_domain_str(domain);
	struct intel_power_domain_mask async_put_mask;

	power_domains = &xe->display.power.domains;

	drm_WARN(&xe->drm, !power_domains->domain_use_count[domain],
		 "Use count on domain %s is already zero\n",
		 name);
	async_put_domains_mask(power_domains, &async_put_mask);
	drm_WARN(&xe->drm,
		 test_bit(domain, async_put_mask.bits),
		 "Async disabling of domain %s is pending\n",
		 name);

	power_domains->domain_use_count[domain]--;

	for_each_power_domain_well_reverse(xe, power_well, domain)
		intel_power_well_put(xe, power_well);
}

static void __intel_display_power_put(struct xe_device *xe,
				      enum intel_display_power_domain domain)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	mutex_lock(&power_domains->lock);
	__intel_display_power_put_domain(xe, domain);
	mutex_unlock(&power_domains->lock);
}

static void
queue_async_put_domains_work(struct i915_power_domains *power_domains,
			     intel_wakeref_t wakeref,
			     int delay_ms)
{
	struct xe_device *xe = container_of(power_domains,
						     struct xe_device,
						     display.power.domains);
	drm_WARN_ON(&xe->drm, power_domains->async_put_wakeref);
	power_domains->async_put_wakeref = wakeref;
	drm_WARN_ON(&xe->drm, !queue_delayed_work(system_unbound_wq,
						    &power_domains->async_put_work,
						    msecs_to_jiffies(delay_ms)));
}

static void
release_async_put_domains(struct i915_power_domains *power_domains,
			  struct intel_power_domain_mask *mask)
{
	struct xe_device *xe =
		container_of(power_domains, struct xe_device,
			     display.power.domains);
	struct intel_runtime_pm *rpm = &xe->runtime_pm;
	enum intel_display_power_domain domain;
	intel_wakeref_t wakeref;

	wakeref = intel_runtime_pm_get_noresume(rpm);

	for_each_power_domain(domain, mask) {
		/* Clear before put, so put's sanity check is happy. */
		async_put_domains_clear_domain(power_domains, domain);
		__intel_display_power_put_domain(xe, domain);
	}

	intel_runtime_pm_put(rpm, wakeref);
}

static void
intel_display_power_put_async_work(struct work_struct *work)
{
	struct xe_device *xe =
		container_of(work, struct xe_device,
			     display.power.domains.async_put_work.work);
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct intel_runtime_pm *rpm = &xe->runtime_pm;
	intel_wakeref_t new_work_wakeref = intel_runtime_pm_get_raw(rpm);
	intel_wakeref_t old_work_wakeref = 0;

	mutex_lock(&power_domains->lock);

	/*
	 * Bail out if all the domain refs pending to be released were grabbed
	 * by subsequent gets or a flush_work.
	 */
	old_work_wakeref = fetch_and_zero(&power_domains->async_put_wakeref);
	if (!old_work_wakeref)
		goto out_verify;

	release_async_put_domains(power_domains,
				  &power_domains->async_put_domains[0]);

	/*
	 * Cancel the work that got queued after this one got dequeued,
	 * since here we released the corresponding async-put reference.
	 */
	cancel_async_put_work(power_domains, false);

	/* Requeue the work if more domains were async put meanwhile. */
	if (!bitmap_empty(power_domains->async_put_domains[1].bits, POWER_DOMAIN_NUM)) {
		bitmap_copy(power_domains->async_put_domains[0].bits,
			    power_domains->async_put_domains[1].bits,
			    POWER_DOMAIN_NUM);
		bitmap_zero(power_domains->async_put_domains[1].bits,
			    POWER_DOMAIN_NUM);
		queue_async_put_domains_work(power_domains,
					     fetch_and_zero(&new_work_wakeref),
					     power_domains->async_put_next_delay);
		power_domains->async_put_next_delay = 0;
	}

out_verify:
	verify_async_put_domains_state(power_domains);

	mutex_unlock(&power_domains->lock);

	if (old_work_wakeref)
		intel_runtime_pm_put_raw(rpm, old_work_wakeref);
	if (new_work_wakeref)
		intel_runtime_pm_put_raw(rpm, new_work_wakeref);
}

/**
 * __intel_display_power_put_async - release a power domain reference asynchronously
 * @xe: xe device instance
 * @domain: power domain to reference
 * @wakeref: wakeref acquired for the reference that is being released
 * @delay_ms: delay of powering down the power domain
 *
 * This function drops the power domain reference obtained by
 * intel_display_power_get*() and schedules a work to power down the
 * corresponding hardware block if this is the last reference.
 * The power down is delayed by @delay_ms if this is >= 0, or by a default
 * 100 ms otherwise.
 */
void __intel_display_power_put_async(struct xe_device *xe,
				     enum intel_display_power_domain domain,
				     intel_wakeref_t wakeref,
				     int delay_ms)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct intel_runtime_pm *rpm = &xe->runtime_pm;
	intel_wakeref_t work_wakeref = intel_runtime_pm_get_raw(rpm);

	delay_ms = delay_ms >= 0 ? delay_ms : 100;

	mutex_lock(&power_domains->lock);

	if (power_domains->domain_use_count[domain] > 1) {
		__intel_display_power_put_domain(xe, domain);

		goto out_verify;
	}

	drm_WARN_ON(&xe->drm, power_domains->domain_use_count[domain] != 1);

	/* Let a pending work requeue itself or queue a new one. */
	if (power_domains->async_put_wakeref) {
		set_bit(domain, power_domains->async_put_domains[1].bits);
		power_domains->async_put_next_delay = max(power_domains->async_put_next_delay,
							  delay_ms);
	} else {
		set_bit(domain, power_domains->async_put_domains[0].bits);
		queue_async_put_domains_work(power_domains,
					     fetch_and_zero(&work_wakeref),
					     delay_ms);
	}

out_verify:
	verify_async_put_domains_state(power_domains);

	mutex_unlock(&power_domains->lock);

	if (work_wakeref)
		intel_runtime_pm_put_raw(rpm, work_wakeref);

	intel_runtime_pm_put(rpm, wakeref);
}

/**
 * intel_display_power_flush_work - flushes the async display power disabling work
 * @xe: xe device instance
 *
 * Flushes any pending work that was scheduled by a preceding
 * intel_display_power_put_async() call, completing the disabling of the
 * corresponding power domains.
 *
 * Note that the work handler function may still be running after this
 * function returns; to ensure that the work handler isn't running use
 * intel_display_power_flush_work_sync() instead.
 */
void intel_display_power_flush_work(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct intel_power_domain_mask async_put_mask;
	intel_wakeref_t work_wakeref;

	mutex_lock(&power_domains->lock);

	work_wakeref = fetch_and_zero(&power_domains->async_put_wakeref);
	if (!work_wakeref)
		goto out_verify;

	async_put_domains_mask(power_domains, &async_put_mask);
	release_async_put_domains(power_domains, &async_put_mask);
	cancel_async_put_work(power_domains, false);

out_verify:
	verify_async_put_domains_state(power_domains);

	mutex_unlock(&power_domains->lock);

	if (work_wakeref)
		intel_runtime_pm_put_raw(&xe->runtime_pm, work_wakeref);
}

/**
 * intel_display_power_flush_work_sync - flushes and syncs the async display power disabling work
 * @xe: xe device instance
 *
 * Like intel_display_power_flush_work(), but also ensure that the work
 * handler function is not running any more when this function returns.
 */
static void
intel_display_power_flush_work_sync(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	intel_display_power_flush_work(xe);
	cancel_async_put_work(power_domains, true);

	verify_async_put_domains_state(power_domains);

	drm_WARN_ON(&xe->drm, power_domains->async_put_wakeref);
}

#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
/**
 * intel_display_power_put - release a power domain reference
 * @xe: xe device instance
 * @domain: power domain to reference
 * @wakeref: wakeref acquired for the reference that is being released
 *
 * This function drops the power domain reference obtained by
 * intel_display_power_get() and might power down the corresponding hardware
 * block right away if this is the last reference.
 */
void intel_display_power_put(struct xe_device *xe,
			     enum intel_display_power_domain domain,
			     intel_wakeref_t wakeref)
{
	__intel_display_power_put(xe, domain);
	intel_runtime_pm_put(&xe->runtime_pm, wakeref);
}
#else
/**
 * intel_display_power_put_unchecked - release an unchecked power domain reference
 * @xe: xe device instance
 * @domain: power domain to reference
 *
 * This function drops the power domain reference obtained by
 * intel_display_power_get() and might power down the corresponding hardware
 * block right away if this is the last reference.
 *
 * This function is only for the power domain code's internal use to suppress wakeref
 * tracking when the correspondig debug kconfig option is disabled, should not
 * be used otherwise.
 */
void intel_display_power_put_unchecked(struct xe_device *xe,
				       enum intel_display_power_domain domain)
{
	__intel_display_power_put(xe, domain);
	intel_runtime_pm_put_unchecked(&xe->runtime_pm);
}
#endif

void
intel_display_power_get_in_set(struct xe_device *xe,
			       struct intel_display_power_domain_set *power_domain_set,
			       enum intel_display_power_domain domain)
{
	intel_wakeref_t __maybe_unused wf;

	drm_WARN_ON(&xe->drm, test_bit(domain, power_domain_set->mask.bits));

	wf = intel_display_power_get(xe, domain);
#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
	power_domain_set->wakerefs[domain] = wf;
#endif
	set_bit(domain, power_domain_set->mask.bits);
}

bool
intel_display_power_get_in_set_if_enabled(struct xe_device *xe,
					  struct intel_display_power_domain_set *power_domain_set,
					  enum intel_display_power_domain domain)
{
	intel_wakeref_t wf;

	drm_WARN_ON(&xe->drm, test_bit(domain, power_domain_set->mask.bits));

	wf = intel_display_power_get_if_enabled(xe, domain);
	if (!wf)
		return false;

#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
	power_domain_set->wakerefs[domain] = wf;
#endif
	set_bit(domain, power_domain_set->mask.bits);

	return true;
}

void
intel_display_power_put_mask_in_set(struct xe_device *xe,
				    struct intel_display_power_domain_set *power_domain_set,
				    struct intel_power_domain_mask *mask)
{
	enum intel_display_power_domain domain;

	drm_WARN_ON(&xe->drm,
		    !bitmap_subset(mask->bits, power_domain_set->mask.bits, POWER_DOMAIN_NUM));

	for_each_power_domain(domain, mask) {
		intel_wakeref_t __maybe_unused wf = -1;

#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)
		wf = fetch_and_zero(&power_domain_set->wakerefs[domain]);
#endif
		intel_display_power_put(xe, domain, wf);
		clear_bit(domain, power_domain_set->mask.bits);
	}
}

static int
sanitize_disable_power_well_option(const struct xe_device *xe,
				   int disable_power_well)
{
	if (disable_power_well >= 0)
		return !!disable_power_well;

	return 1;
}

static u32 get_allowed_dc_mask(const struct xe_device *xe,
			       int enable_dc)
{
	u32 mask;
	int requested_dc;
	int max_dc;

	if (!HAS_DISPLAY(xe))
		return 0;

	if (DISPLAY_VER(xe) >= 20)
		max_dc = 2;
	else if (IS_DG2(xe))
		max_dc = 1;
	else if (IS_DG1(xe))
		max_dc = 3;
	else if (DISPLAY_VER(xe) >= 12)
		max_dc = 4;
	else if (IS_GEMINILAKE(xe) || IS_BROXTON(xe))
		max_dc = 1;
	else if (DISPLAY_VER(xe) >= 9)
		max_dc = 2;
	else
		max_dc = 0;

	/*
	 * DC9 has a separate HW flow from the rest of the DC states,
	 * not depending on the DMC firmware. It's needed by system
	 * suspend/resume, so allow it unconditionally.
	 */
	mask = IS_GEMINILAKE(xe) || IS_BROXTON(xe) ||
		DISPLAY_VER(xe) >= 11 ?
	       DC_STATE_EN_DC9 : 0;

	if (!xe->display.params.disable_power_well)
		max_dc = 0;

	if (enable_dc >= 0 && enable_dc <= max_dc) {
		requested_dc = enable_dc;
	} else if (enable_dc == -1) {
		requested_dc = max_dc;
	} else if (enable_dc > max_dc && enable_dc <= 4) {
		drm_dbg_kms(&xe->drm,
			    "Adjusting requested max DC state (%d->%d)\n",
			    enable_dc, max_dc);
		requested_dc = max_dc;
	} else {
		drm_err(&xe->drm,
			"Unexpected value for enable_dc (%d)\n", enable_dc);
		requested_dc = max_dc;
	}

	switch (requested_dc) {
	case 4:
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC6;
		break;
	case 3:
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC5;
		break;
	case 2:
		mask |= DC_STATE_EN_UPTO_DC6;
		break;
	case 1:
		mask |= DC_STATE_EN_UPTO_DC5;
		break;
	}

	drm_dbg_kms(&xe->drm, "Allowed DC state mask %02x\n", mask);

	return mask;
}

/**
 * intel_power_domains_init - initializes the power domain structures
 * @xe: xe device instance
 *
 * Initializes the power domain structures for @xe depending upon the
 * supported platform.
 */
int intel_power_domains_init(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	xe->display.params.disable_power_well =
		sanitize_disable_power_well_option(xe,
						   xe->display.params.disable_power_well);
	power_domains->allowed_dc_mask =
		get_allowed_dc_mask(xe, xe->display.params.enable_dc);

	power_domains->target_dc_state =
		sanitize_target_dc_state(xe, DC_STATE_EN_UPTO_DC6);

	mutex_init(&power_domains->lock);

	INIT_DELAYED_WORK(&power_domains->async_put_work,
			  intel_display_power_put_async_work);

	return intel_display_power_map_init(power_domains);
}

/**
 * intel_power_domains_cleanup - clean up power domains resources
 * @xe: xe device instance
 *
 * Release any resources acquired by intel_power_domains_init()
 */
void intel_power_domains_cleanup(struct xe_device *xe)
{
	intel_display_power_map_cleanup(&xe->display.power.domains);
}

static void intel_power_domains_sync_hw(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *power_well;

	mutex_lock(&power_domains->lock);
	for_each_power_well(xe, power_well)
		intel_power_well_sync_hw(xe, power_well);
	mutex_unlock(&power_domains->lock);
}

static void gen9_dbuf_slice_set(struct xe_device *xe,
				enum dbuf_slice slice, bool enable)
{
	i915_reg_t reg = DBUF_CTL_S(slice);
	bool state;

	intel_de_rmw(xe, reg, DBUF_POWER_REQUEST,
		     enable ? DBUF_POWER_REQUEST : 0);
	intel_de_posting_read(xe, reg);
	udelay(10);

	state = intel_de_read(xe, reg) & DBUF_POWER_STATE;
	drm_WARN(&xe->drm, enable != state,
		 "DBuf slice %d power %s timeout!\n",
		 slice, str_enable_disable(enable));
}

void gen9_dbuf_slices_update(struct xe_device *xe,
			     u8 req_slices)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	u8 slice_mask = DISPLAY_INFO(xe)->dbuf.slice_mask;
	enum dbuf_slice slice;

	drm_WARN(&xe->drm, req_slices & ~slice_mask,
		 "Invalid set of dbuf slices (0x%x) requested (total dbuf slices 0x%x)\n",
		 req_slices, slice_mask);

	drm_dbg_kms(&xe->drm, "Updating dbuf slices to 0x%x\n",
		    req_slices);

	/*
	 * Might be running this in parallel to gen9_dc_off_power_well_enable
	 * being called from intel_dp_detect for instance,
	 * which causes assertion triggered by race condition,
	 * as gen9_assert_dbuf_enabled might preempt this when registers
	 * were already updated, while xe was not.
	 */
	mutex_lock(&power_domains->lock);

	for_each_dbuf_slice(xe, slice)
		gen9_dbuf_slice_set(xe, slice, req_slices & BIT(slice));

	xe->display.dbuf.enabled_slices = req_slices;

	mutex_unlock(&power_domains->lock);
}

static void gen9_dbuf_enable(struct xe_device *xe)
{
	u8 slices_mask;

	xe->display.dbuf.enabled_slices =
		intel_enabled_dbuf_slices_mask(xe);

	slices_mask = BIT(DBUF_S1) | xe->display.dbuf.enabled_slices;

	if (DISPLAY_VER(xe) >= 14)
		intel_pmdemand_program_dbuf(xe, slices_mask);

	/*
	 * Just power up at least 1 slice, we will
	 * figure out later which slices we have and what we need.
	 */
	gen9_dbuf_slices_update(xe, slices_mask);
}

static void gen9_dbuf_disable(struct xe_device *xe)
{
	gen9_dbuf_slices_update(xe, 0);

	if (DISPLAY_VER(xe) >= 14)
		intel_pmdemand_program_dbuf(xe, 0);
}

static void gen12_dbuf_slices_config(struct xe_device *xe)
{
	enum dbuf_slice slice;

	if (IS_ALDERLAKE_P(xe))
		return;

	for_each_dbuf_slice(xe, slice)
		intel_de_rmw(xe, DBUF_CTL_S(slice),
			     DBUF_TRACKER_STATE_SERVICE_MASK,
			     DBUF_TRACKER_STATE_SERVICE(8));
}

static void icl_mbus_init(struct xe_device *xe)
{
	unsigned long abox_regs = DISPLAY_INFO(xe)->abox_mask;
	u32 mask, val, i;

	if (IS_ALDERLAKE_P(xe) || DISPLAY_VER(xe) >= 14)
		return;

	mask = MBUS_ABOX_BT_CREDIT_POOL1_MASK |
		MBUS_ABOX_BT_CREDIT_POOL2_MASK |
		MBUS_ABOX_B_CREDIT_MASK |
		MBUS_ABOX_BW_CREDIT_MASK;
	val = MBUS_ABOX_BT_CREDIT_POOL1(16) |
		MBUS_ABOX_BT_CREDIT_POOL2(16) |
		MBUS_ABOX_B_CREDIT(1) |
		MBUS_ABOX_BW_CREDIT(1);

	/*
	 * gen12 platforms that use abox1 and abox2 for pixel data reads still
	 * expect us to program the abox_ctl0 register as well, even though
	 * we don't have to program other instance-0 registers like BW_BUDDY.
	 */
	if (DISPLAY_VER(xe) == 12)
		abox_regs |= BIT(0);

	for_each_set_bit(i, &abox_regs, sizeof(abox_regs))
		intel_de_rmw(xe, MBUS_ABOX_CTL(i), mask, val);
}

static void hsw_assert_cdclk(struct xe_device *xe)
{
	u32 val = intel_de_read(xe, LCPLL_CTL);

	/*
	 * The LCPLL register should be turned on by the BIOS. For now
	 * let's just check its state and print errors in case
	 * something is wrong.  Don't even try to turn it on.
	 */

	if (val & LCPLL_CD_SOURCE_FCLK)
		drm_err(&xe->drm, "CDCLK source is not LCPLL\n");

	if (val & LCPLL_PLL_DISABLE)
		drm_err(&xe->drm, "LCPLL is disabled\n");

	if ((val & LCPLL_REF_MASK) != LCPLL_REF_NON_SSC)
		drm_err(&xe->drm, "LCPLL not using non-SSC reference\n");
}

static void assert_can_disable_lcpll(struct xe_device *xe)
{
	struct intel_crtc *crtc;

	for_each_intel_crtc(&xe->drm, crtc)
		I915_STATE_WARN(xe, crtc->active,
				"CRTC for pipe %c enabled\n",
				pipe_name(crtc->pipe));

	I915_STATE_WARN(xe, intel_de_read(xe, HSW_PWR_WELL_CTL2),
			"Display power well on\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, SPLL_CTL) & SPLL_PLL_ENABLE,
			"SPLL enabled\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, WRPLL_CTL(0)) & WRPLL_PLL_ENABLE,
			"WRPLL1 enabled\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, WRPLL_CTL(1)) & WRPLL_PLL_ENABLE,
			"WRPLL2 enabled\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, PP_STATUS(xe, 0)) & PP_ON,
			"Panel power on\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, BLC_PWM_CPU_CTL2) & BLM_PWM_ENABLE,
			"CPU PWM1 enabled\n");
	if (IS_HASWELL(xe))
		I915_STATE_WARN(xe,
				intel_de_read(xe, HSW_BLC_PWM2_CTL) & BLM_PWM_ENABLE,
				"CPU PWM2 enabled\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, BLC_PWM_PCH_CTL1) & BLM_PCH_PWM_ENABLE,
			"PCH PWM1 enabled\n");
	I915_STATE_WARN(xe,
			(intel_de_read(xe, UTIL_PIN_CTL) & (UTIL_PIN_ENABLE | UTIL_PIN_MODE_MASK)) == (UTIL_PIN_ENABLE | UTIL_PIN_MODE_PWM),
			"Utility pin enabled in PWM mode\n");
	I915_STATE_WARN(xe,
			intel_de_read(xe, PCH_GTC_CTL) & PCH_GTC_ENABLE,
			"PCH GTC enabled\n");

	/*
	 * In theory we can still leave IRQs enabled, as long as only the HPD
	 * interrupts remain enabled. We used to check for that, but since it's
	 * gen-specific and since we only disable LCPLL after we fully disable
	 * the interrupts, the check below should be enough.
	 */
	I915_STATE_WARN(xe, intel_irqs_enabled(xe),
			"IRQs enabled\n");
}

static u32 hsw_read_dcomp(struct xe_device *xe)
{
	if (IS_HASWELL(xe))
		return intel_de_read(xe, D_COMP_HSW);
	else
		return intel_de_read(xe, D_COMP_BDW);
}

static void hsw_write_dcomp(struct xe_device *xe, u32 val)
{
	if (IS_HASWELL(xe)) {
		if (snb_pcode_write(&xe->uncore, GEN6_PCODE_WRITE_D_COMP, val))
			drm_dbg_kms(&xe->drm,
				    "Failed to write to D_COMP\n");
	} else {
		intel_de_write(xe, D_COMP_BDW, val);
		intel_de_posting_read(xe, D_COMP_BDW);
	}
}

/*
 * This function implements pieces of two sequences from BSpec:
 * - Sequence for display software to disable LCPLL
 * - Sequence for display software to allow package C8+
 * The steps implemented here are just the steps that actually touch the LCPLL
 * register. Callers should take care of disabling all the display engine
 * functions, doing the mode unset, fixing interrupts, etc.
 */
static void hsw_disable_lcpll(struct xe_device *xe,
			      bool switch_to_fclk, bool allow_power_down)
{
	u32 val;

	assert_can_disable_lcpll(xe);

	val = intel_de_read(xe, LCPLL_CTL);

	if (switch_to_fclk) {
		val |= LCPLL_CD_SOURCE_FCLK;
		intel_de_write(xe, LCPLL_CTL, val);

		if (wait_for_us(intel_de_read(xe, LCPLL_CTL) &
				LCPLL_CD_SOURCE_FCLK_DONE, 1))
			drm_err(&xe->drm, "Switching to FCLK failed\n");

		val = intel_de_read(xe, LCPLL_CTL);
	}

	val |= LCPLL_PLL_DISABLE;
	intel_de_write(xe, LCPLL_CTL, val);
	intel_de_posting_read(xe, LCPLL_CTL);

	if (intel_de_wait_for_clear(xe, LCPLL_CTL, LCPLL_PLL_LOCK, 1))
		drm_err(&xe->drm, "LCPLL still locked\n");

	val = hsw_read_dcomp(xe);
	val |= D_COMP_COMP_DISABLE;
	hsw_write_dcomp(xe, val);
	ndelay(100);

	if (wait_for((hsw_read_dcomp(xe) &
		      D_COMP_RCOMP_IN_PROGRESS) == 0, 1))
		drm_err(&xe->drm, "D_COMP RCOMP still in progress\n");

	if (allow_power_down) {
		intel_de_rmw(xe, LCPLL_CTL, 0, LCPLL_POWER_DOWN_ALLOW);
		intel_de_posting_read(xe, LCPLL_CTL);
	}
}

/*
 * Fully restores LCPLL, disallowing power down and switching back to LCPLL
 * source.
 */
static void hsw_restore_lcpll(struct xe_device *xe)
{
	u32 val;

	val = intel_de_read(xe, LCPLL_CTL);

	if ((val & (LCPLL_PLL_LOCK | LCPLL_PLL_DISABLE | LCPLL_CD_SOURCE_FCLK |
		    LCPLL_POWER_DOWN_ALLOW)) == LCPLL_PLL_LOCK)
		return;

	/*
	 * Make sure we're not on PC8 state before disabling PC8, otherwise
	 * we'll hang the machine. To prevent PC8 state, just enable force_wake.
	 */
	intel_uncore_forcewake_get(&xe->uncore, FORCEWAKE_ALL);

	if (val & LCPLL_POWER_DOWN_ALLOW) {
		val &= ~LCPLL_POWER_DOWN_ALLOW;
		intel_de_write(xe, LCPLL_CTL, val);
		intel_de_posting_read(xe, LCPLL_CTL);
	}

	val = hsw_read_dcomp(xe);
	val |= D_COMP_COMP_FORCE;
	val &= ~D_COMP_COMP_DISABLE;
	hsw_write_dcomp(xe, val);

	val = intel_de_read(xe, LCPLL_CTL);
	val &= ~LCPLL_PLL_DISABLE;
	intel_de_write(xe, LCPLL_CTL, val);

	if (intel_de_wait_for_set(xe, LCPLL_CTL, LCPLL_PLL_LOCK, 5))
		drm_err(&xe->drm, "LCPLL not locked yet\n");

	if (val & LCPLL_CD_SOURCE_FCLK) {
		intel_de_rmw(xe, LCPLL_CTL, LCPLL_CD_SOURCE_FCLK, 0);

		if (wait_for_us((intel_de_read(xe, LCPLL_CTL) &
				 LCPLL_CD_SOURCE_FCLK_DONE) == 0, 1))
			drm_err(&xe->drm,
				"Switching back to LCPLL failed\n");
	}

	intel_uncore_forcewake_put(&xe->uncore, FORCEWAKE_ALL);

	intel_update_cdclk(xe);
	intel_cdclk_dump_config(xe, &xe->display.cdclk.hw, "Current CDCLK");
}

/*
 * Package states C8 and deeper are really deep PC states that can only be
 * reached when all the devices on the system allow it, so even if the graphics
 * device allows PC8+, it doesn't mean the system will actually get to these
 * states. Our driver only allows PC8+ when going into runtime PM.
 *
 * The requirements for PC8+ are that all the outputs are disabled, the power
 * well is disabled and most interrupts are disabled, and these are also
 * requirements for runtime PM. When these conditions are met, we manually do
 * the other conditions: disable the interrupts, clocks and switch LCPLL refclk
 * to Fclk. If we're in PC8+ and we get an non-hotplug interrupt, we can hard
 * hang the machine.
 *
 * When we really reach PC8 or deeper states (not just when we allow it) we lose
 * the state of some registers, so when we come back from PC8+ we need to
 * restore this state. We don't get into PC8+ if we're not in RC6, so we don't
 * need to take care of the registers kept by RC6. Notice that this happens even
 * if we don't put the device in PCI D3 state (which is what currently happens
 * because of the runtime PM support).
 *
 * For more, read "Display Sequences for Package C8" on the hardware
 * documentation.
 */
static void hsw_enable_pc8(struct xe_device *xe)
{
	drm_dbg_kms(&xe->drm, "Enabling package C8+\n");

	if (HAS_PCH_LPT_LP(xe))
		intel_de_rmw(xe, SOUTH_DSPCLK_GATE_D,
			     PCH_LP_PARTITION_LEVEL_DISABLE, 0);

	lpt_disable_clkout_dp(xe);
	hsw_disable_lcpll(xe, true, true);
}

static void hsw_disable_pc8(struct xe_device *xe)
{
	drm_dbg_kms(&xe->drm, "Disabling package C8+\n");

	hsw_restore_lcpll(xe);
	intel_init_pch_refclk(xe);

	/* Many display registers don't survive PC8+ */
	intel_clock_gating_init(xe);
}

static void intel_pch_reset_handshake(struct xe_device *xe,
				      bool enable)
{
	i915_reg_t reg;
	u32 reset_bits;

	if (IS_IVYBRIDGE(xe)) {
		reg = GEN7_MSG_CTL;
		reset_bits = WAIT_FOR_PCH_FLR_ACK | WAIT_FOR_PCH_RESET_ACK;
	} else {
		reg = HSW_NDE_RSTWRN_OPT;
		reset_bits = RESET_PCH_HANDSHAKE_ENABLE;
	}

	if (DISPLAY_VER(xe) >= 14)
		reset_bits |= MTL_RESET_PICA_HANDSHAKE_EN;

	intel_de_rmw(xe, reg, reset_bits, enable ? reset_bits : 0);
}

static void skl_display_core_init(struct xe_device *xe,
				  bool resume)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *well;

	gen9_set_dc_state(xe, DC_STATE_DISABLE);

	/* enable PCH reset handshake */
	intel_pch_reset_handshake(xe, !HAS_PCH_NOP(xe));

	if (!HAS_DISPLAY(xe))
		return;

	/* enable PG1 and Misc I/O */
	mutex_lock(&power_domains->lock);

	well = lookup_power_well(xe, SKL_DISP_PW_1);
	intel_power_well_enable(xe, well);

	well = lookup_power_well(xe, SKL_DISP_PW_MISC_IO);
	intel_power_well_enable(xe, well);

	mutex_unlock(&power_domains->lock);

	intel_cdclk_init_hw(xe);

	gen9_dbuf_enable(xe);

	if (resume)
		intel_dmc_load_program(xe);
}

static void skl_display_core_uninit(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *well;

	if (!HAS_DISPLAY(xe))
		return;

	gen9_disable_dc_states(xe);
	/* TODO: disable DMC program */

	gen9_dbuf_disable(xe);

	intel_cdclk_uninit_hw(xe);

	/* The spec doesn't call for removing the reset handshake flag */
	/* disable PG1 and Misc I/O */

	mutex_lock(&power_domains->lock);

	/*
	 * BSpec says to keep the MISC IO power well enabled here, only
	 * remove our request for power well 1.
	 * Note that even though the driver's request is removed power well 1
	 * may stay enabled after this due to DMC's own request on it.
	 */
	well = lookup_power_well(xe, SKL_DISP_PW_1);
	intel_power_well_disable(xe, well);

	mutex_unlock(&power_domains->lock);

	usleep_range(10, 30);		/* 10 us delay per Bspec */
}

static void bxt_display_core_init(struct xe_device *xe, bool resume)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *well;

	gen9_set_dc_state(xe, DC_STATE_DISABLE);

	/*
	 * NDE_RSTWRN_OPT RST PCH Handshake En must always be 0b on BXT
	 * or else the reset will hang because there is no PCH to respond.
	 * Move the handshake programming to initialization sequence.
	 * Previously was left up to BIOS.
	 */
	intel_pch_reset_handshake(xe, false);

	if (!HAS_DISPLAY(xe))
		return;

	/* Enable PG1 */
	mutex_lock(&power_domains->lock);

	well = lookup_power_well(xe, SKL_DISP_PW_1);
	intel_power_well_enable(xe, well);

	mutex_unlock(&power_domains->lock);

	intel_cdclk_init_hw(xe);

	gen9_dbuf_enable(xe);

	if (resume)
		intel_dmc_load_program(xe);
}

static void bxt_display_core_uninit(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *well;

	if (!HAS_DISPLAY(xe))
		return;

	gen9_disable_dc_states(xe);
	/* TODO: disable DMC program */

	gen9_dbuf_disable(xe);

	intel_cdclk_uninit_hw(xe);

	/* The spec doesn't call for removing the reset handshake flag */

	/*
	 * Disable PW1 (PG1).
	 * Note that even though the driver's request is removed power well 1
	 * may stay enabled after this due to DMC's own request on it.
	 */
	mutex_lock(&power_domains->lock);

	well = lookup_power_well(xe, SKL_DISP_PW_1);
	intel_power_well_disable(xe, well);

	mutex_unlock(&power_domains->lock);

	usleep_range(10, 30);		/* 10 us delay per Bspec */
}

struct buddy_page_mask {
	u32 page_mask;
	u8 type;
	u8 num_channels;
};

static const struct buddy_page_mask tgl_buddy_page_masks[] = {
	{ .num_channels = 1, .type = INTEL_DRAM_DDR4,   .page_mask = 0xF },
	{ .num_channels = 1, .type = INTEL_DRAM_DDR5,	.page_mask = 0xF },
	{ .num_channels = 2, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x1C },
	{ .num_channels = 2, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x1C },
	{ .num_channels = 2, .type = INTEL_DRAM_DDR4,   .page_mask = 0x1F },
	{ .num_channels = 2, .type = INTEL_DRAM_DDR5,   .page_mask = 0x1E },
	{ .num_channels = 4, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x38 },
	{ .num_channels = 4, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x38 },
	{}
};

static const struct buddy_page_mask wa_1409767108_buddy_page_masks[] = {
	{ .num_channels = 1, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x1 },
	{ .num_channels = 1, .type = INTEL_DRAM_DDR4,   .page_mask = 0x1 },
	{ .num_channels = 1, .type = INTEL_DRAM_DDR5,   .page_mask = 0x1 },
	{ .num_channels = 1, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x1 },
	{ .num_channels = 2, .type = INTEL_DRAM_LPDDR4, .page_mask = 0x3 },
	{ .num_channels = 2, .type = INTEL_DRAM_DDR4,   .page_mask = 0x3 },
	{ .num_channels = 2, .type = INTEL_DRAM_DDR5,   .page_mask = 0x3 },
	{ .num_channels = 2, .type = INTEL_DRAM_LPDDR5, .page_mask = 0x3 },
	{}
};

static void tgl_bw_buddy_init(struct xe_device *xe)
{
	enum intel_dram_type type = xe->dram_info.type;
	u8 num_channels = xe->dram_info.num_channels;
	const struct buddy_page_mask *table;
	unsigned long abox_mask = DISPLAY_INFO(xe)->abox_mask;
	int config, i;

	/* BW_BUDDY registers are not used on dgpu's beyond DG1 */
	if (IS_DGFX(xe) && !IS_DG1(xe))
		return;

	if (IS_ALDERLAKE_S(xe) ||
	    (IS_ROCKETLAKE(xe) && IS_DISPLAY_STEP(xe, STEP_A0, STEP_B0)))
		/* Wa_1409767108 */
		table = wa_1409767108_buddy_page_masks;
	else
		table = tgl_buddy_page_masks;

	for (config = 0; table[config].page_mask != 0; config++)
		if (table[config].num_channels == num_channels &&
		    table[config].type == type)
			break;

	if (table[config].page_mask == 0) {
		drm_dbg(&xe->drm,
			"Unknown memory configuration; disabling address buddy logic.\n");
		for_each_set_bit(i, &abox_mask, sizeof(abox_mask))
			intel_de_write(xe, BW_BUDDY_CTL(i),
				       BW_BUDDY_DISABLE);
	} else {
		for_each_set_bit(i, &abox_mask, sizeof(abox_mask)) {
			intel_de_write(xe, BW_BUDDY_PAGE_MASK(i),
				       table[config].page_mask);

			/* Wa_22010178259:tgl,dg1,rkl,adl-s */
			if (DISPLAY_VER(xe) == 12)
				intel_de_rmw(xe, BW_BUDDY_CTL(i),
					     BW_BUDDY_TLB_REQ_TIMER_MASK,
					     BW_BUDDY_TLB_REQ_TIMER(0x8));
		}
	}
}

static void icl_display_core_init(struct xe_device *xe,
				  bool resume)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *well;

	gen9_set_dc_state(xe, DC_STATE_DISABLE);

	/* Wa_14011294188:ehl,jsl,tgl,rkl,adl-s */
	if (INTEL_PCH_TYPE(xe) >= PCH_TGP &&
	    INTEL_PCH_TYPE(xe) < PCH_DG1)
		intel_de_rmw(xe, SOUTH_DSPCLK_GATE_D, 0,
			     PCH_DPMGUNIT_CLOCK_GATE_DISABLE);

	/* 1. Enable PCH reset handshake. */
	intel_pch_reset_handshake(xe, !HAS_PCH_NOP(xe));

	if (!HAS_DISPLAY(xe))
		return;

	/* 2. Initialize all combo phys */
	intel_combo_phy_init(xe);

	/*
	 * 3. Enable Power Well 1 (PG1).
	 *    The AUX IO power wells will be enabled on demand.
	 */
	mutex_lock(&power_domains->lock);
	well = lookup_power_well(xe, SKL_DISP_PW_1);
	intel_power_well_enable(xe, well);
	mutex_unlock(&power_domains->lock);

	if (DISPLAY_VER(xe) == 14)
		intel_de_rmw(xe, DC_STATE_EN,
			     HOLD_PHY_PG1_LATCH | HOLD_PHY_CLKREQ_PG1_LATCH, 0);

	/* 4. Enable CDCLK. */
	intel_cdclk_init_hw(xe);

	if (DISPLAY_VER(xe) >= 12)
		gen12_dbuf_slices_config(xe);

	/* 5. Enable DBUF. */
	gen9_dbuf_enable(xe);

	/* 6. Setup MBUS. */
	icl_mbus_init(xe);

	/* 7. Program arbiter BW_BUDDY registers */
	if (DISPLAY_VER(xe) >= 12)
		tgl_bw_buddy_init(xe);

	/* 8. Ensure PHYs have completed calibration and adaptation */
	if (IS_DG2(xe))
		intel_snps_phy_wait_for_calibration(xe);

	/* 9. XE2_HPD: Program CHICKEN_MISC_2 before any cursor or planes are enabled */
	if (DISPLAY_VER_FULL(xe) == IP_VER(14, 1))
		intel_de_rmw(xe, CHICKEN_MISC_2, BMG_DARB_HALF_BLK_END_BURST, 1);

	if (resume)
		intel_dmc_load_program(xe);

	/* Wa_14011508470:tgl,dg1,rkl,adl-s,adl-p,dg2 */
	if (IS_DISPLAY_VER_FULL(xe, IP_VER(12, 0), IP_VER(13, 0)))
		intel_de_rmw(xe, GEN11_CHICKEN_DCPR_2, 0,
			     DCPR_CLEAR_MEMSTAT_DIS | DCPR_SEND_RESP_IMM |
			     DCPR_MASK_LPMODE | DCPR_MASK_MAXLATENCY_MEMUP_CLR);

	/* Wa_14011503030:xelpd */
	if (DISPLAY_VER(xe) == 13)
		intel_de_write(xe, XELPD_DISPLAY_ERR_FATAL_MASK, ~0);

	/* Wa_15013987218 */
	if (DISPLAY_VER(xe) == 20) {
		intel_de_rmw(xe, SOUTH_DSPCLK_GATE_D,
			     0, PCH_GMBUSUNIT_CLOCK_GATE_DISABLE);
		intel_de_rmw(xe, SOUTH_DSPCLK_GATE_D,
			     PCH_GMBUSUNIT_CLOCK_GATE_DISABLE, 0);
	}
}

static void icl_display_core_uninit(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *well;

	if (!HAS_DISPLAY(xe))
		return;

	gen9_disable_dc_states(xe);
	intel_dmc_disable_program(xe);

	/* 1. Disable all display engine functions -> aready done */

	/* 2. Disable DBUF */
	gen9_dbuf_disable(xe);

	/* 3. Disable CD clock */
	intel_cdclk_uninit_hw(xe);

	if (DISPLAY_VER(xe) == 14)
		intel_de_rmw(xe, DC_STATE_EN, 0,
			     HOLD_PHY_PG1_LATCH | HOLD_PHY_CLKREQ_PG1_LATCH);

	/*
	 * 4. Disable Power Well 1 (PG1).
	 *    The AUX IO power wells are toggled on demand, so they are already
	 *    disabled at this point.
	 */
	mutex_lock(&power_domains->lock);
	well = lookup_power_well(xe, SKL_DISP_PW_1);
	intel_power_well_disable(xe, well);
	mutex_unlock(&power_domains->lock);

	/* 5. */
	intel_combo_phy_uninit(xe);
}

static void chv_phy_control_init(struct xe_device *xe)
{
	struct i915_power_well *cmn_bc =
		lookup_power_well(xe, VLV_DISP_PW_DPIO_CMN_BC);
	struct i915_power_well *cmn_d =
		lookup_power_well(xe, CHV_DISP_PW_DPIO_CMN_D);

	/*
	 * DISPLAY_PHY_CONTROL can get corrupted if read. As a
	 * workaround never ever read DISPLAY_PHY_CONTROL, and
	 * instead maintain a shadow copy ourselves. Use the actual
	 * power well state and lane status to reconstruct the
	 * expected initial value.
	 */
	xe->display.power.chv_phy_control =
		PHY_LDO_SEQ_DELAY(PHY_LDO_DELAY_600NS, DPIO_PHY0) |
		PHY_LDO_SEQ_DELAY(PHY_LDO_DELAY_600NS, DPIO_PHY1) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY0, DPIO_CH0) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY0, DPIO_CH1) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY1, DPIO_CH0);

	/*
	 * If all lanes are disabled we leave the override disabled
	 * with all power down bits cleared to match the state we
	 * would use after disabling the port. Otherwise enable the
	 * override and set the lane powerdown bits accding to the
	 * current lane status.
	 */
	if (intel_power_well_is_enabled(xe, cmn_bc)) {
		u32 status = intel_de_read(xe, DPLL(xe, PIPE_A));
		unsigned int mask;

		mask = status & DPLL_PORTB_READY_MASK;
		if (mask == 0xf)
			mask = 0x0;
		else
			xe->display.power.chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH0);

		xe->display.power.chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY0, DPIO_CH0);

		mask = (status & DPLL_PORTC_READY_MASK) >> 4;
		if (mask == 0xf)
			mask = 0x0;
		else
			xe->display.power.chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH1);

		xe->display.power.chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY0, DPIO_CH1);

		xe->display.power.chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(DPIO_PHY0);

		xe->display.power.chv_phy_assert[DPIO_PHY0] = false;
	} else {
		xe->display.power.chv_phy_assert[DPIO_PHY0] = true;
	}

	if (intel_power_well_is_enabled(xe, cmn_d)) {
		u32 status = intel_de_read(xe, DPIO_PHY_STATUS);
		unsigned int mask;

		mask = status & DPLL_PORTD_READY_MASK;

		if (mask == 0xf)
			mask = 0x0;
		else
			xe->display.power.chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY1, DPIO_CH0);

		xe->display.power.chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY1, DPIO_CH0);

		xe->display.power.chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(DPIO_PHY1);

		xe->display.power.chv_phy_assert[DPIO_PHY1] = false;
	} else {
		xe->display.power.chv_phy_assert[DPIO_PHY1] = true;
	}

	drm_dbg_kms(&xe->drm, "Initial PHY_CONTROL=0x%08x\n",
		    xe->display.power.chv_phy_control);

	/* Defer application of initial phy_control to enabling the powerwell */
}

static void vlv_cmnlane_wa(struct xe_device *xe)
{
	struct i915_power_well *cmn =
		lookup_power_well(xe, VLV_DISP_PW_DPIO_CMN_BC);
	struct i915_power_well *disp2d =
		lookup_power_well(xe, VLV_DISP_PW_DISP2D);

	/* If the display might be already active skip this */
	if (intel_power_well_is_enabled(xe, cmn) &&
	    intel_power_well_is_enabled(xe, disp2d) &&
	    intel_de_read(xe, DPIO_CTL) & DPIO_CMNRST)
		return;

	drm_dbg_kms(&xe->drm, "toggling display PHY side reset\n");

	/* cmnlane needs DPLL registers */
	intel_power_well_enable(xe, disp2d);

	/*
	 * From VLV2A0_DP_eDP_HDMI_DPIO_driver_vbios_notes_11.docx:
	 * Need to assert and de-assert PHY SB reset by gating the
	 * common lane power, then un-gating it.
	 * Simply ungating isn't enough to reset the PHY enough to get
	 * ports and lanes running.
	 */
	intel_power_well_disable(xe, cmn);
}

static bool vlv_punit_is_power_gated(struct xe_device *xe, u32 reg0)
{
	bool ret;

	vlv_punit_get(xe);
	ret = (vlv_punit_read(xe, reg0) & SSPM0_SSC_MASK) == SSPM0_SSC_PWR_GATE;
	vlv_punit_put(xe);

	return ret;
}

static void assert_ved_power_gated(struct xe_device *xe)
{
	drm_WARN(&xe->drm,
		 !vlv_punit_is_power_gated(xe, PUNIT_REG_VEDSSPM0),
		 "VED not power gated\n");
}

static void assert_isp_power_gated(struct xe_device *xe)
{
	static const struct pci_device_id isp_ids[] = {
		{PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x0f38)},
		{PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x22b8)},
		{}
	};

	drm_WARN(&xe->drm, !pci_dev_present(isp_ids) &&
		 !vlv_punit_is_power_gated(xe, PUNIT_REG_ISPSSPM0),
		 "ISP not power gated\n");
}

static void intel_power_domains_verify_state(struct xe_device *xe);

/**
 * intel_power_domains_init_hw - initialize hardware power domain state
 * @xe: xe device instance
 * @resume: Called from resume code paths or not
 *
 * This function initializes the hardware power domain state and enables all
 * power wells belonging to the INIT power domain. Power wells in other
 * domains (and not in the INIT domain) are referenced or disabled by
 * intel_modeset_readout_hw_state(). After that the reference count of each
 * power well must match its HW enabled state, see
 * intel_power_domains_verify_state().
 *
 * It will return with power domains disabled (to be enabled later by
 * intel_power_domains_enable()) and must be paired with
 * intel_power_domains_driver_remove().
 */
void intel_power_domains_init_hw(struct xe_device *xe, bool resume)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	power_domains->initializing = true;

	if (DISPLAY_VER(xe) >= 11) {
		icl_display_core_init(xe, resume);
	} else if (IS_GEMINILAKE(xe) || IS_BROXTON(xe)) {
		bxt_display_core_init(xe, resume);
	} else if (DISPLAY_VER(xe) == 9) {
		skl_display_core_init(xe, resume);
	} else if (IS_CHERRYVIEW(xe)) {
		mutex_lock(&power_domains->lock);
		chv_phy_control_init(xe);
		mutex_unlock(&power_domains->lock);
		assert_isp_power_gated(xe);
	} else if (IS_VALLEYVIEW(xe)) {
		mutex_lock(&power_domains->lock);
		vlv_cmnlane_wa(xe);
		mutex_unlock(&power_domains->lock);
		assert_ved_power_gated(xe);
		assert_isp_power_gated(xe);
	} else if (IS_BROADWELL(xe) || IS_HASWELL(xe)) {
		hsw_assert_cdclk(xe);
		intel_pch_reset_handshake(xe, !HAS_PCH_NOP(xe));
	} else if (IS_IVYBRIDGE(xe)) {
		intel_pch_reset_handshake(xe, !HAS_PCH_NOP(xe));
	}

	/*
	 * Keep all power wells enabled for any dependent HW access during
	 * initialization and to make sure we keep BIOS enabled display HW
	 * resources powered until display HW readout is complete. We drop
	 * this reference in intel_power_domains_enable().
	 */
	drm_WARN_ON(&xe->drm, power_domains->init_wakeref);
	power_domains->init_wakeref =
		intel_display_power_get(xe, POWER_DOMAIN_INIT);

	/* Disable power support if the user asked so. */
	if (!xe->display.params.disable_power_well) {
		drm_WARN_ON(&xe->drm, power_domains->disable_wakeref);
		xe->display.power.domains.disable_wakeref = intel_display_power_get(xe,
										      POWER_DOMAIN_INIT);
	}
	intel_power_domains_sync_hw(xe);

	power_domains->initializing = false;
}

/**
 * intel_power_domains_driver_remove - deinitialize hw power domain state
 * @xe: xe device instance
 *
 * De-initializes the display power domain HW state. It also ensures that the
 * device stays powered up so that the driver can be reloaded.
 *
 * It must be called with power domains already disabled (after a call to
 * intel_power_domains_disable()) and must be paired with
 * intel_power_domains_init_hw().
 */
void intel_power_domains_driver_remove(struct xe_device *xe)
{
	intel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&xe->display.power.domains.init_wakeref);

	/* Remove the refcount we took to keep power well support disabled. */
	if (!xe->display.params.disable_power_well)
		intel_display_power_put(xe, POWER_DOMAIN_INIT,
					fetch_and_zero(&xe->display.power.domains.disable_wakeref));

	intel_display_power_flush_work_sync(xe);

	intel_power_domains_verify_state(xe);

	/* Keep the power well enabled, but cancel its rpm wakeref. */
	intel_runtime_pm_put(&xe->runtime_pm, wakeref);
}

/**
 * intel_power_domains_sanitize_state - sanitize power domains state
 * @xe: xe device instance
 *
 * Sanitize the power domains state during driver loading and system resume.
 * The function will disable all display power wells that BIOS has enabled
 * without a user for it (any user for a power well has taken a reference
 * on it by the time this function is called, after the state of all the
 * pipe, encoder, etc. HW resources have been sanitized).
 */
void intel_power_domains_sanitize_state(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *power_well;

	mutex_lock(&power_domains->lock);

	for_each_power_well_reverse(xe, power_well) {
		if (power_well->desc->always_on || power_well->count ||
		    !intel_power_well_is_enabled(xe, power_well))
			continue;

		drm_dbg_kms(&xe->drm,
			    "BIOS left unused %s power well enabled, disabling it\n",
			    intel_power_well_name(power_well));
		intel_power_well_disable(xe, power_well);
	}

	mutex_unlock(&power_domains->lock);
}

/**
 * intel_power_domains_enable - enable toggling of display power wells
 * @xe: xe device instance
 *
 * Enable the ondemand enabling/disabling of the display power wells. Note that
 * power wells not belonging to POWER_DOMAIN_INIT are allowed to be toggled
 * only at specific points of the display modeset sequence, thus they are not
 * affected by the intel_power_domains_enable()/disable() calls. The purpose
 * of these function is to keep the rest of power wells enabled until the end
 * of display HW readout (which will acquire the power references reflecting
 * the current HW state).
 */
void intel_power_domains_enable(struct xe_device *xe)
{
	intel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&xe->display.power.domains.init_wakeref);

	intel_display_power_put(xe, POWER_DOMAIN_INIT, wakeref);
	intel_power_domains_verify_state(xe);
}

/**
 * intel_power_domains_disable - disable toggling of display power wells
 * @xe: xe device instance
 *
 * Disable the ondemand enabling/disabling of the display power wells. See
 * intel_power_domains_enable() for which power wells this call controls.
 */
void intel_power_domains_disable(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	drm_WARN_ON(&xe->drm, power_domains->init_wakeref);
	power_domains->init_wakeref =
		intel_display_power_get(xe, POWER_DOMAIN_INIT);

	intel_power_domains_verify_state(xe);
}

/**
 * intel_power_domains_suspend - suspend power domain state
 * @xe: xe device instance
 * @s2idle: specifies whether we go to idle, or deeper sleep
 *
 * This function prepares the hardware power domain state before entering
 * system suspend.
 *
 * It must be called with power domains already disabled (after a call to
 * intel_power_domains_disable()) and paired with intel_power_domains_resume().
 */
void intel_power_domains_suspend(struct xe_device *xe, bool s2idle)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	intel_wakeref_t wakeref __maybe_unused =
		fetch_and_zero(&power_domains->init_wakeref);

	intel_display_power_put(xe, POWER_DOMAIN_INIT, wakeref);

	/*
	 * In case of suspend-to-idle (aka S0ix) on a DMC platform without DC9
	 * support don't manually deinit the power domains. This also means the
	 * DMC firmware will stay active, it will power down any HW
	 * resources as required and also enable deeper system power states
	 * that would be blocked if the firmware was inactive.
	 */
	if (!(power_domains->allowed_dc_mask & DC_STATE_EN_DC9) && s2idle &&
	    intel_dmc_has_payload(xe)) {
		intel_display_power_flush_work(xe);
		intel_power_domains_verify_state(xe);
		return;
	}

	/*
	 * Even if power well support was disabled we still want to disable
	 * power wells if power domains must be deinitialized for suspend.
	 */
	if (!xe->display.params.disable_power_well)
		intel_display_power_put(xe, POWER_DOMAIN_INIT,
					fetch_and_zero(&xe->display.power.domains.disable_wakeref));

	intel_display_power_flush_work(xe);
	intel_power_domains_verify_state(xe);

	if (DISPLAY_VER(xe) >= 11)
		icl_display_core_uninit(xe);
	else if (IS_GEMINILAKE(xe) || IS_BROXTON(xe))
		bxt_display_core_uninit(xe);
	else if (DISPLAY_VER(xe) == 9)
		skl_display_core_uninit(xe);

	power_domains->display_core_suspended = true;
}

/**
 * intel_power_domains_resume - resume power domain state
 * @xe: xe device instance
 *
 * This function resume the hardware power domain state during system resume.
 *
 * It will return with power domain support disabled (to be enabled later by
 * intel_power_domains_enable()) and must be paired with
 * intel_power_domains_suspend().
 */
void intel_power_domains_resume(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	if (power_domains->display_core_suspended) {
		intel_power_domains_init_hw(xe, true);
		power_domains->display_core_suspended = false;
	} else {
		drm_WARN_ON(&xe->drm, power_domains->init_wakeref);
		power_domains->init_wakeref =
			intel_display_power_get(xe, POWER_DOMAIN_INIT);
	}

	intel_power_domains_verify_state(xe);
}

#if IS_ENABLED(CONFIG_DRM_I915_DEBUG_RUNTIME_PM)

static void intel_power_domains_dump_info(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *power_well;

	for_each_power_well(xe, power_well) {
		enum intel_display_power_domain domain;

		drm_dbg(&xe->drm, "%-25s %d\n",
			intel_power_well_name(power_well), intel_power_well_refcount(power_well));

		for_each_power_domain(domain, intel_power_well_domains(power_well))
			drm_dbg(&xe->drm, "  %-23s %d\n",
				intel_display_power_domain_str(domain),
				power_domains->domain_use_count[domain]);
	}
}

/**
 * intel_power_domains_verify_state - verify the HW/SW state for all power wells
 * @xe: xe device instance
 *
 * Verify if the reference count of each power well matches its HW enabled
 * state and the total refcount of the domains it belongs to. This must be
 * called after modeset HW state sanitization, which is responsible for
 * acquiring reference counts for any power wells in use and disabling the
 * ones left on by BIOS but not required by any active output.
 */
static void intel_power_domains_verify_state(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	struct i915_power_well *power_well;
	bool dump_domain_info;

	mutex_lock(&power_domains->lock);

	verify_async_put_domains_state(power_domains);

	dump_domain_info = false;
	for_each_power_well(xe, power_well) {
		enum intel_display_power_domain domain;
		int domains_count;
		bool enabled;

		enabled = intel_power_well_is_enabled(xe, power_well);
		if ((intel_power_well_refcount(power_well) ||
		     intel_power_well_is_always_on(power_well)) !=
		    enabled)
			drm_err(&xe->drm,
				"power well %s state mismatch (refcount %d/enabled %d)",
				intel_power_well_name(power_well),
				intel_power_well_refcount(power_well), enabled);

		domains_count = 0;
		for_each_power_domain(domain, intel_power_well_domains(power_well))
			domains_count += power_domains->domain_use_count[domain];

		if (intel_power_well_refcount(power_well) != domains_count) {
			drm_err(&xe->drm,
				"power well %s refcount/domain refcount mismatch "
				"(refcount %d/domains refcount %d)\n",
				intel_power_well_name(power_well),
				intel_power_well_refcount(power_well),
				domains_count);
			dump_domain_info = true;
		}
	}

	if (dump_domain_info) {
		static bool dumped;

		if (!dumped) {
			intel_power_domains_dump_info(xe);
			dumped = true;
		}
	}

	mutex_unlock(&power_domains->lock);
}

#else

static void intel_power_domains_verify_state(struct xe_device *xe)
{
}

#endif

void intel_display_power_suspend_late(struct xe_device *xe)
{
	if (DISPLAY_VER(xe) >= 11 || IS_GEMINILAKE(xe) ||
	    IS_BROXTON(xe)) {
		bxt_enable_dc9(xe);
	} else if (IS_HASWELL(xe) || IS_BROADWELL(xe)) {
		hsw_enable_pc8(xe);
	}

	/* Tweaked Wa_14010685332:cnp,icp,jsp,mcc,tgp,adp */
	if (INTEL_PCH_TYPE(xe) >= PCH_CNP && INTEL_PCH_TYPE(xe) < PCH_DG1)
		intel_de_rmw(xe, SOUTH_CHICKEN1, SBCLK_RUN_REFCLK_DIS, SBCLK_RUN_REFCLK_DIS);
}

void intel_display_power_resume_early(struct xe_device *xe)
{
	if (DISPLAY_VER(xe) >= 11 || IS_GEMINILAKE(xe) ||
	    IS_BROXTON(xe)) {
		gen9_sanitize_dc_state(xe);
		bxt_disable_dc9(xe);
	} else if (IS_HASWELL(xe) || IS_BROADWELL(xe)) {
		hsw_disable_pc8(xe);
	}

	/* Tweaked Wa_14010685332:cnp,icp,jsp,mcc,tgp,adp */
	if (INTEL_PCH_TYPE(xe) >= PCH_CNP && INTEL_PCH_TYPE(xe) < PCH_DG1)
		intel_de_rmw(xe, SOUTH_CHICKEN1, SBCLK_RUN_REFCLK_DIS, 0);
}

void intel_display_power_suspend(struct xe_device *xe)
{
	if (DISPLAY_VER(xe) >= 11) {
		icl_display_core_uninit(xe);
		bxt_enable_dc9(xe);
	} else if (IS_GEMINILAKE(xe) || IS_BROXTON(xe)) {
		bxt_display_core_uninit(xe);
		bxt_enable_dc9(xe);
	} else if (IS_HASWELL(xe) || IS_BROADWELL(xe)) {
		hsw_enable_pc8(xe);
	}
}

void intel_display_power_resume(struct xe_device *xe)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;

	if (DISPLAY_VER(xe) >= 11) {
		bxt_disable_dc9(xe);
		icl_display_core_init(xe, true);
		if (intel_dmc_has_payload(xe)) {
			if (power_domains->allowed_dc_mask & DC_STATE_EN_UPTO_DC6)
				skl_enable_dc6(xe);
			else if (power_domains->allowed_dc_mask & DC_STATE_EN_UPTO_DC5)
				gen9_enable_dc5(xe);
		}
	} else if (IS_GEMINILAKE(xe) || IS_BROXTON(xe)) {
		bxt_disable_dc9(xe);
		bxt_display_core_init(xe, true);
		if (intel_dmc_has_payload(xe) &&
		    (power_domains->allowed_dc_mask & DC_STATE_EN_UPTO_DC5))
			gen9_enable_dc5(xe);
	} else if (IS_HASWELL(xe) || IS_BROADWELL(xe)) {
		hsw_disable_pc8(xe);
	}
}

void intel_display_power_debug(struct xe_device *xe, struct seq_file *m)
{
	struct i915_power_domains *power_domains = &xe->display.power.domains;
	int i;

	mutex_lock(&power_domains->lock);

	seq_printf(m, "%-25s %s\n", "Power well/domain", "Use count");
	for (i = 0; i < power_domains->power_well_count; i++) {
		struct i915_power_well *power_well;
		enum intel_display_power_domain power_domain;

		power_well = &power_domains->power_wells[i];
		seq_printf(m, "%-25s %d\n", intel_power_well_name(power_well),
			   intel_power_well_refcount(power_well));

		for_each_power_domain(power_domain, intel_power_well_domains(power_well))
			seq_printf(m, "  %-23s %d\n",
				   intel_display_power_domain_str(power_domain),
				   power_domains->domain_use_count[power_domain]);
	}

	mutex_unlock(&power_domains->lock);
}

struct intel_ddi_port_domains {
	enum port port_start;
	enum port port_end;
	enum aux_ch aux_ch_start;
	enum aux_ch aux_ch_end;

	enum intel_display_power_domain ddi_lanes;
	enum intel_display_power_domain ddi_io;
	enum intel_display_power_domain aux_io;
	enum intel_display_power_domain aux_legacy_usbc;
	enum intel_display_power_domain aux_tbt;
};

static const struct intel_ddi_port_domains
i9xx_port_domains[] = {
	{
		.port_start = PORT_A,
		.port_end = PORT_F,
		.aux_ch_start = AUX_CH_A,
		.aux_ch_end = AUX_CH_F,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_A,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_A,
		.aux_io = POWER_DOMAIN_AUX_IO_A,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_A,
		.aux_tbt = POWER_DOMAIN_INVALID,
	},
};

static const struct intel_ddi_port_domains
d11_port_domains[] = {
	{
		.port_start = PORT_A,
		.port_end = PORT_B,
		.aux_ch_start = AUX_CH_A,
		.aux_ch_end = AUX_CH_B,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_A,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_A,
		.aux_io = POWER_DOMAIN_AUX_IO_A,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_A,
		.aux_tbt = POWER_DOMAIN_INVALID,
	}, {
		.port_start = PORT_C,
		.port_end = PORT_F,
		.aux_ch_start = AUX_CH_C,
		.aux_ch_end = AUX_CH_F,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_C,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_C,
		.aux_io = POWER_DOMAIN_AUX_IO_C,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_C,
		.aux_tbt = POWER_DOMAIN_AUX_TBT1,
	},
};

static const struct intel_ddi_port_domains
d12_port_domains[] = {
	{
		.port_start = PORT_A,
		.port_end = PORT_C,
		.aux_ch_start = AUX_CH_A,
		.aux_ch_end = AUX_CH_C,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_A,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_A,
		.aux_io = POWER_DOMAIN_AUX_IO_A,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_A,
		.aux_tbt = POWER_DOMAIN_INVALID,
	}, {
		.port_start = PORT_TC1,
		.port_end = PORT_TC6,
		.aux_ch_start = AUX_CH_USBC1,
		.aux_ch_end = AUX_CH_USBC6,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_TC1,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_TC1,
		.aux_io = POWER_DOMAIN_INVALID,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_USBC1,
		.aux_tbt = POWER_DOMAIN_AUX_TBT1,
	},
};

static const struct intel_ddi_port_domains
d13_port_domains[] = {
	{
		.port_start = PORT_A,
		.port_end = PORT_C,
		.aux_ch_start = AUX_CH_A,
		.aux_ch_end = AUX_CH_C,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_A,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_A,
		.aux_io = POWER_DOMAIN_AUX_IO_A,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_A,
		.aux_tbt = POWER_DOMAIN_INVALID,
	}, {
		.port_start = PORT_TC1,
		.port_end = PORT_TC4,
		.aux_ch_start = AUX_CH_USBC1,
		.aux_ch_end = AUX_CH_USBC4,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_TC1,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_TC1,
		.aux_io = POWER_DOMAIN_INVALID,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_USBC1,
		.aux_tbt = POWER_DOMAIN_AUX_TBT1,
	}, {
		.port_start = PORT_D_XELPD,
		.port_end = PORT_E_XELPD,
		.aux_ch_start = AUX_CH_D_XELPD,
		.aux_ch_end = AUX_CH_E_XELPD,

		.ddi_lanes = POWER_DOMAIN_PORT_DDI_LANES_D,
		.ddi_io = POWER_DOMAIN_PORT_DDI_IO_D,
		.aux_io = POWER_DOMAIN_AUX_IO_D,
		.aux_legacy_usbc = POWER_DOMAIN_AUX_D,
		.aux_tbt = POWER_DOMAIN_INVALID,
	},
};

static void
intel_port_domains_for_platform(struct xe_device *xe,
				const struct intel_ddi_port_domains **domains,
				int *domains_size)
{
	if (DISPLAY_VER(xe) >= 13) {
		*domains = d13_port_domains;
		*domains_size = ARRAY_SIZE(d13_port_domains);
	} else if (DISPLAY_VER(xe) >= 12) {
		*domains = d12_port_domains;
		*domains_size = ARRAY_SIZE(d12_port_domains);
	} else if (DISPLAY_VER(xe) >= 11) {
		*domains = d11_port_domains;
		*domains_size = ARRAY_SIZE(d11_port_domains);
	} else {
		*domains = i9xx_port_domains;
		*domains_size = ARRAY_SIZE(i9xx_port_domains);
	}
}

static const struct intel_ddi_port_domains *
intel_port_domains_for_port(struct xe_device *xe, enum port port)
{
	const struct intel_ddi_port_domains *domains;
	int domains_size;
	int i;

	intel_port_domains_for_platform(xe, &domains, &domains_size);
	for (i = 0; i < domains_size; i++)
		if (port >= domains[i].port_start && port <= domains[i].port_end)
			return &domains[i];

	return NULL;
}

enum intel_display_power_domain
intel_display_power_ddi_io_domain(struct xe_device *xe, enum port port)
{
	const struct intel_ddi_port_domains *domains = intel_port_domains_for_port(xe, port);

	if (drm_WARN_ON(&xe->drm, !domains || domains->ddi_io == POWER_DOMAIN_INVALID))
		return POWER_DOMAIN_PORT_DDI_IO_A;

	return domains->ddi_io + (int)(port - domains->port_start);
}

enum intel_display_power_domain
intel_display_power_ddi_lanes_domain(struct xe_device *xe, enum port port)
{
	const struct intel_ddi_port_domains *domains = intel_port_domains_for_port(xe, port);

	if (drm_WARN_ON(&xe->drm, !domains || domains->ddi_lanes == POWER_DOMAIN_INVALID))
		return POWER_DOMAIN_PORT_DDI_LANES_A;

	return domains->ddi_lanes + (int)(port - domains->port_start);
}

static const struct intel_ddi_port_domains *
intel_port_domains_for_aux_ch(struct xe_device *xe, enum aux_ch aux_ch)
{
	const struct intel_ddi_port_domains *domains;
	int domains_size;
	int i;

	intel_port_domains_for_platform(xe, &domains, &domains_size);
	for (i = 0; i < domains_size; i++)
		if (aux_ch >= domains[i].aux_ch_start && aux_ch <= domains[i].aux_ch_end)
			return &domains[i];

	return NULL;
}

enum intel_display_power_domain
intel_display_power_aux_io_domain(struct xe_device *xe, enum aux_ch aux_ch)
{
	const struct intel_ddi_port_domains *domains = intel_port_domains_for_aux_ch(xe, aux_ch);

	if (drm_WARN_ON(&xe->drm, !domains || domains->aux_io == POWER_DOMAIN_INVALID))
		return POWER_DOMAIN_AUX_IO_A;

	return domains->aux_io + (int)(aux_ch - domains->aux_ch_start);
}

enum intel_display_power_domain
intel_display_power_legacy_aux_domain(struct xe_device *xe, enum aux_ch aux_ch)
{
	const struct intel_ddi_port_domains *domains = intel_port_domains_for_aux_ch(xe, aux_ch);

	if (drm_WARN_ON(&xe->drm, !domains || domains->aux_legacy_usbc == POWER_DOMAIN_INVALID))
		return POWER_DOMAIN_AUX_A;

	return domains->aux_legacy_usbc + (int)(aux_ch - domains->aux_ch_start);
}

enum intel_display_power_domain
intel_display_power_tbt_aux_domain(struct xe_device *xe, enum aux_ch aux_ch)
{
	const struct intel_ddi_port_domains *domains = intel_port_domains_for_aux_ch(xe, aux_ch);

	if (drm_WARN_ON(&xe->drm, !domains || domains->aux_tbt == POWER_DOMAIN_INVALID))
		return POWER_DOMAIN_AUX_TBT1;

	return domains->aux_tbt + (int)(aux_ch - domains->aux_ch_start);
}
