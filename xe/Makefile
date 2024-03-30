# $FreeBSD$

SRCDIR=	${.CURDIR:H}/drivers/gpu/drm/xe

.PATH:	${SRCDIR} \
	${SRCDIR}/display \
	${SRCDIR}/gem \
	${SRCDIR}/gt \
	${SRCDIR}/gt/uc \
	${SRCDIR}/oa \
	${SRCDIR}/pxp \
	${SRCDIR}/soc

.include "../kconfig.mk"
.include "../linuxkpi_version.mk"

KMOD=	xe
SRCS=	xe_bb.c \
	xe_bo.c \
	xe_bo_evict.c \
	xe_debugfs.c \
	xe_devcoredump.c \
	xe_device.c \
	xe_device_sysfs.c \
	xe_display.c \
	xe_dma_buf.c \
	xe_drm_client.c \
	xe_exec.c \
	xe_exec_queue.c \
	xe_execlist.c \
	xe_force_wake.c \
	xe_gen_wa_oob.c \
	xe_ggtt.c \
	xe_gpu_scheduler.c \
	xe_gsc.c \
	xe_gsc_submit.c \
	xe_gt.c \
	xe_gt_ccs_mode.c \
	xe_gt_clock.c \
	xe_gt_debugfs.c \
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
	xe_guc_debugfs.c \
	xe_guc_hwconfig.c \
	xe_guc_log.c \
	xe_guc_pc.c \
	xe_guc_submit.c \
	xe_heci_gsc.c \
	xe_huc.c \
	xe_huc_debugfs.c \
	xe_hw_engine.c \
	xe_hw_engine_class_sysfs.c \
	xe_hw_fence.c \
	xe_hwmon.c \
	xe_irq.c \
	xe_lmtt.c \
	xe_lmtt_2l.c \
	xe_lmtt_ml.c \
	xe_lrc.c \
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
	xe_uc_debugfs.c \
	xe_uc_fw.c \
	xe_vm.c \
	xe_wa.c \
	xe_wait_user_fence.c \
	xe_wopcm.c

CLEANFILES+= ${KMOD}.ko.full ${KMOD}.ko.debug

CFLAGS+= -I${.CURDIR:H}/linuxkpi/gplv2/include
CFLAGS+= -I${.CURDIR:H}/linuxkpi/bsd/include
CFLAGS+= -I${SYSDIR}/compat/linuxkpi/common/include
CFLAGS+= -I${.CURDIR:H}/linuxkpi/dummy/include
CFLAGS+= -I${SYSDIR}/compat/linuxkpi/dummy/include

CFLAGS+= -I${.CURDIR:H}/include
CFLAGS+= -I${.CURDIR:H}/include/drm
CFLAGS+= -I${.CURDIR:H}/include/uapi
CFLAGS+= -I${SRCDIR:H:H} -I${SRCDIR} -I${SRCDIR}/display
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

