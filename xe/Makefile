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
	xe_display.c

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
CFLAGS+= -I${SRCDIR}/compat-i915-headers

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

