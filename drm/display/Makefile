# $FreeBSD$

SRCDIR= ${.CURDIR:H:H}/drivers/gpu/drm

.PATH:	${SRCDIR}/display

.include "../../kconfig.mk"

KMOD=   drm_dp_helper
SRCS=   drm_dp.c \
        drm_dp_dual_mode_helper.c \
	drm_dp_helper_mod.c \
        drm_dp_mst_topology.c

.if !empty(KCONFIG:MDRM_DP_AUX_BUS)
SRCS+=  drm_dp_aux_bus.c
.endif

.if !empty(KCONFIG:MDRM_DP_AUX_CHARDEV)
SRCS+=  drm_dp_aux_dev.c
.endif
        
SRCS+=  device_if.h vnode_if.h bus_if.h pci_if.h pci_iov_if.h device_if.h iicbus_if.h opt_drm.h \
        opt_vm.h opt_syscons.h opt_acpi.h

CLEANFILES+= ${KMOD}.ko.full ${KMOD}.ko.debug

CFLAGS+= -I${.CURDIR:H:H}/linuxkpi/gplv2/include
CFLAGS+= -I${.CURDIR:H:H}/linuxkpi/bsd/include
CFLAGS+= -I${SYSDIR}/compat/linuxkpi/common/include
CFLAGS+= -I${.CURDIR:H:H}/linuxkpi/dummy/include # fallback to dummy
CFLAGS+= -I${SYSDIR}/compat/linuxkpi/dummy/include

CFLAGS+= -I${.CURDIR:H:H}/include
CFLAGS+= -I${.CURDIR:H:H}/include/drm
CFLAGS+= -I${.CURDIR:H:H}/include/uapi
CFLAGS+= -I${SRCDIR:H:H}
CFLAGS+= -I${SRCDIR:H}
CFLAGS+= '-DKBUILD_MODNAME="${KMOD}"'
CFLAGS+= '-DLINUXKPI_PARAM_PREFIX=drm_' -DDRM_SYSCTL_PARAM_PREFIX=_dri -DLINUXKPI_VERSION=51600
CFLAGS+= ${KCONFIG:C/(.*)/-DCONFIG_\1/}

CWARNFLAGS+= -Wno-pointer-sign -Wno-format

.include <bsd.kmod.mk>
