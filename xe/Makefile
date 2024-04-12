# $FreeBSD$

SRCDIR=	${.CURDIR:H}/drivers/gpu/drm/xe
I915_SRCDIR= ${.CURDIR:H}/drivers/gpu/drm/i915

.PATH:	${SRCDIR} \
	${SRCDIR}/display \
	${SRCDIR}/display/ext \
	${SRCDIR}/generated \
	${I915_SRCDIR} \
	${I915_SRCDIR}/display \
	${I915_SRCDIR}/soc

.include "../kconfig.mk"
.include "../linuxkpi_version.mk"

KMOD=	xe

all:	xe_wa_oob.c

xe_gen_wa_oob:	${SRCDIR}/xe_gen_wa_oob.c
	cc -o xe_gen_wa_oob ${SRCDIR}/xe_gen_wa_oob.c

xe_wa_oob.c:	xe_wa_oob.h

xe_wa_oob.h:	xe_wa_oob.rules	xe_gen_wa_oob
	mkdir -p ${SRCDIR}/generated
	./xe_gen_wa_oob ${SRCDIR}/xe_wa_oob.rules ${SRCDIR}/generated/xe_wa_oob.c ${SRCDIR}/generated/xe_wa_oob.h

#	xe_hmm.c	// disabled

# xe
SRCS=	xe_bb.c \
	xe_bo.c \
	xe_bo_evict.c \
	xe_devcoredump.c \
	xe_device.c \
	xe_device_sysfs.c \
	xe_dma_buf.c \
	xe_drm_client.c \
	xe_exec.c \
	xe_exec_queue.c \
	xe_execlist.c \
	xe_force_wake.c \
	xe_ggtt.c \
	xe_gpu_scheduler.c \
	xe_gsc.c \
	xe_gsc_proxy.c \
	xe_gsc_submit.c \
	xe_gt.c \
	xe_gt_ccs_mode.c \
	xe_gt_clock.c \
	xe_gt_freq.c \
	xe_gt_idle.c \
	xe_gt_mcr.c \
	xe_gt_pagefault.c \
	xe_gt_sysfs.c \
	xe_gt_throttle_sysfs.c \
	xe_gt_tlb_invalidation.c \
	xe_gt_topology.c \
	xe_guc.c \
	xe_guc_ads.c \
	xe_guc_ct.c \
	xe_guc_db_mgr.c \
	xe_guc_hwconfig.c \
	xe_guc_id_mgr.c \
	xe_guc_klv_helpers.c \
	xe_guc_log.c \
	xe_guc_pc.c \
	xe_guc_relay.c \
	xe_guc_submit.c \
	xe_heci_gsc.c \
	xe_huc.c \
	xe_hw_engine.c \
	xe_hw_engine_class_sysfs.c \
	xe_hw_fence.c \
	xe_irq.c \
	xe_lrc.c \
	xe_memirq.c \
	xe_migrate.c \
	xe_mmio.c \
	xe_mocs.c \
	xe_module.c \
	xe_pat.c \
	xe_pci.c \
	xe_pcode.c \
	xe_pm.c \
	xe_preempt_fence.c \
	xe_pt.c \
	xe_pt_walk.c \
	xe_query.c \
	xe_range_fence.c \
	xe_reg_sr.c \
	xe_reg_whitelist.c \
	xe_ring_ops.c \
	xe_rtp.c \
	xe_sa.c \
	xe_sched_job.c \
	xe_sriov.c \
	xe_step.c \
	xe_sync.c \
	xe_tile.c \
	xe_tile_sysfs.c \
	xe_ttm_stolen_mgr.c \
	xe_ttm_sys_mgr.c \
	xe_ttm_vram_mgr.c \
	xe_tuning.c \
	xe_uc.c \
	xe_uc_fw.c \
	xe_vm.c \
	xe_vram_freq.c \
	xe_wa.c \
	xe_wait_user_fence.c \
	xe_wopcm.c

# xe/display
SRCS+=	intel_fb_bo.c \
	intel_fbdev_fb.c \
	xe_display.c \
	xe_display_misc.c \
	xe_display_rps.c \
	xe_dsb_buffer.c \
	xe_fb_pin.c \
	xe_hdcp_gsc.c \
	xe_plane_initial.c

# xe/display/ext
SRCS+=	i915_irq.c \
	i915_utils.c

.if !empty(KCONFIG:MHWMON)
SRCS+=  xe_hwmon.c
.endif

.if !empty(KCONFIG:MPCI_IOV)
SRCS+=	xe_gt_sriov_pf.c \
	xe_gt_sriov_pf_config.c \
	xe_gt_sriov_pf_control.c \
	xe_gt_sriov_pf_policy.c \
	xe_lmtt.c \
	xe_lmtt_2l.c \
	xe_lmtt_ml.c \
	xe_sriov_pf.c
.endif

.if !empty(KCONFIG:MDEBUG_FS)
SRCS+=	xe_debugfs.c \
	xe_gt_debugfs.c \
	xe_guc_debugfs.c \
	xe_huc_debugfs.c \
	xe_uc_debugfs.c
.endif

# i915
SRCS+=	intel_freebsd.c

# i915/display
SRCS+=	icl_dsi.c \
    intel_acpi.c \
    intel_atomic.c \
    intel_atomic_plane.c \
    intel_audio.c \
    intel_backlight.c \
    intel_bios.c \
    intel_bw.c \
    intel_cdclk.c \
    intel_color.c \
    intel_combo_phy.c \
    intel_connector.c \
    intel_crtc.c \
    intel_crtc_state_dump.c \
    intel_cursor.c \
    intel_cx0_phy.c \
    intel_ddi.c \
    intel_ddi_buf_trans.c \
    intel_display.c \
    intel_display_debugfs.c \
    intel_display_debugfs_params.c \
    intel_display_device.c \
    intel_display_driver.c \
    intel_display_irq.c \
    intel_display_params.c \
    intel_display_power.c \
    intel_display_power_map.c \
    intel_display_power_well.c \
    intel_display_wa.c \
    intel_dkl_phy.c \
    intel_dmc.c \
    intel_dmc_wl.c \
    intel_dp.c \
    intel_dp_aux.c \
    intel_dp_aux_backlight.c \
    intel_dp_hdcp.c \
    intel_dp_link_training.c \
    intel_dp_mst.c \
    intel_dpll.c \
    intel_dpll_mgr.c \
    intel_dpt_common.c \
    intel_drrs.c \
    intel_dsb.c \
    intel_dsi.c \
    intel_dsi_dcs_backlight.c \
    intel_dsi_vbt.c \
    intel_fb.c \
    intel_fbc.c \
    intel_fbdev.c \
    intel_fdi.c \
    intel_fifo_underrun.c \
    intel_frontbuffer.c \
    intel_global_state.c \
    intel_gmbus.c \
    intel_hdcp.c \
    intel_hdcp_gsc_message.c \
    intel_hdmi.c \
    intel_hotplug.c \
    intel_hotplug_irq.c \
    intel_hti.c \
    intel_link_bw.c \
    intel_lspcon.c \
    intel_modeset_lock.c \
    intel_modeset_setup.c \
    intel_modeset_verify.c \
    intel_opregion.c \
    intel_panel.c \
    intel_pipe_crc.c \
    intel_pmdemand.c \
    intel_pps.c \
    intel_psr.c \
    intel_qp_tables.c \
    intel_quirks.c \
    intel_snps_phy.c \
    intel_tc.c \
    intel_vblank.c \
    intel_vdsc.c \
    intel_vga.c \
    intel_vrr.c \
    intel_wm.c \
    skl_scaler.c \
    skl_universal_plane.c \
    skl_watermark.c

# i915/soc
SRCS+=	intel_dram.c \
    intel_pch.c

CLEANFILES+= ${KMOD}.ko.full ${KMOD}.ko.debug

CFLAGS+= -I${.CURDIR:H}/linuxkpi/gplv2/include
CFLAGS+= -I${.CURDIR:H}/linuxkpi/bsd/include
CFLAGS+= -I${SYSDIR}/compat/linuxkpi/common/include
CFLAGS+= -I${SYSDIR}/compat/linuxkpi/dummy/include

CFLAGS+= -I${.CURDIR:H}/include
CFLAGS+= -I${.CURDIR:H}/include/drm
CFLAGS+= -I${.CURDIR:H}/include/uapi
CFLAGS+= -I${SRCDIR:H:H}
CFLAGS+= -I${SRCDIR}
CFLAGS+= -I${SRCDIR}/display
CFLAGS+= -I${SRCDIR}/display/ext
CFLAGS+= -I${SRCDIR}/compat-i915-headers
CFLAGS+= -I${.CURDIR:H}/drivers/gpu/drm/i915/display
CFLAGS+= -Ddrm_i915_gem_object=xe_bo -Ddrm_i915_private=xe_device

CFLAGS+= '-DKBUILD_MODNAME="${KMOD}"'
CFLAGS+= '-DLINUXKPI_PARAM_PREFIX=xe_' -DDRM_SYSCTL_PARAM_PREFIX=_${KMOD}
CFLAGS+= ${KCONFIG:C/(.*)/-DCONFIG_\1/}
CFLAGS+= -DXE

SRCS	+=			\
	opt_acpi.h		\
	opt_drm.h		\
	opt_syscons.h		\
	acpi_if.h		\
	bus_if.h		\
	fb_if.h			\
	device_if.h		\
	pci_if.h		\
	pci_iov_if.h		\
	vnode_if.h

.include <bsd.kmod.mk>

# Re-instate -Wno-cast-qual for all files
# Reason: More or less all files need it due to use of test_bit() macro
# error: cast from 'const unsigned long *' to 'volatile unsigned long *'
CWARNFLAGS += -Wno-pointer-arith -Wno-format -Wno-cast-qual

CWARNFLAGS.xe_dsb_buffer.c=		-Wno-uninitialized
CWARNFLAGS.xe_gt_topology.c=		-Wno-incompatible-pointer-types-discards-qualifiers
CWARNFLAGS.xe_pci.c=			-Wno-initializer-overrides
CWARNFLAGS.xe_query.c=			-Wno-incompatible-function-pointer-types
CWARNFLAGS.xe_step.c=			-Wno-initializer-overrides
CWARNFLAGS.xe_ttm_vram_mgr.c=		-Wno-integer-overflow
CWARNFLAGS.xe_wa.c=			-Wno-initializer-overrides

CWARNFLAGS.intel_bios.c=		-Wno-incompatible-pointer-types-discards-qualifiers
CWARNFLAGS.intel_display_device.c=	-Wno-initializer-overrides
CWARNFLAGS.intel_dpll_mgr.c=		-Wno-compare-distinct-pointer-types
CWARNFLAGS.intel_fbdev.c=		-Wno-initializer-overrides
CWARNFLAGS.intel_hdmi.c=		-Wno-unused-variable
