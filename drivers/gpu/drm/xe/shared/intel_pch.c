// SPDX-License-Identifier: MIT
/*
 * Copyright 2019 Intel Corporation.
 */

#include "i915_drv.h"
#include "i915_utils.h"
#include "intel_pch.h"

/* Map PCH device id to PCH type, or PCH_NONE if unknown. */
static enum intel_pch
intel_pch_type(const struct xe_device *xe, unsigned short id)
{
	switch (id) {
	case INTEL_PCH_IBX_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Ibex Peak PCH\n");
		drm_WARN_ON(&xe->drm, GRAPHICS_VER(xe) != 5);
		return PCH_IBX;
	case INTEL_PCH_CPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found CougarPoint PCH\n");
		drm_WARN_ON(&xe->drm,
			    GRAPHICS_VER(xe) != 6 && !IS_IVYBRIDGE(xe));
		return PCH_CPT;
	case INTEL_PCH_PPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found PantherPoint PCH\n");
		drm_WARN_ON(&xe->drm,
			    GRAPHICS_VER(xe) != 6 && !IS_IVYBRIDGE(xe));
		/* PPT is CPT compatible */
		return PCH_CPT;
	case INTEL_PCH_LPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found LynxPoint PCH\n");
		drm_WARN_ON(&xe->drm,
			    !IS_HASWELL(xe) && !IS_BROADWELL(xe));
		drm_WARN_ON(&xe->drm,
			    IS_HASWELL_ULT(xe) || IS_BROADWELL_ULT(xe));
		return PCH_LPT;
	case INTEL_PCH_LPT_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found LynxPoint LP PCH\n");
		drm_WARN_ON(&xe->drm,
			    !IS_HASWELL(xe) && !IS_BROADWELL(xe));
		drm_WARN_ON(&xe->drm,
			    !IS_HASWELL_ULT(xe) && !IS_BROADWELL_ULT(xe));
		return PCH_LPT;
	case INTEL_PCH_WPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found WildcatPoint PCH\n");
		drm_WARN_ON(&xe->drm,
			    !IS_HASWELL(xe) && !IS_BROADWELL(xe));
		drm_WARN_ON(&xe->drm,
			    IS_HASWELL_ULT(xe) || IS_BROADWELL_ULT(xe));
		/* WPT is LPT compatible */
		return PCH_LPT;
	case INTEL_PCH_WPT_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found WildcatPoint LP PCH\n");
		drm_WARN_ON(&xe->drm,
			    !IS_HASWELL(xe) && !IS_BROADWELL(xe));
		drm_WARN_ON(&xe->drm,
			    !IS_HASWELL_ULT(xe) && !IS_BROADWELL_ULT(xe));
		/* WPT is LPT compatible */
		return PCH_LPT;
	case INTEL_PCH_SPT_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found SunrisePoint PCH\n");
		drm_WARN_ON(&xe->drm,
			    !IS_SKYLAKE(xe) && !IS_KABYLAKE(xe));
		return PCH_SPT;
	case INTEL_PCH_SPT_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found SunrisePoint LP PCH\n");
		drm_WARN_ON(&xe->drm,
			    !IS_SKYLAKE(xe) &&
			    !IS_KABYLAKE(xe) &&
			    !IS_COFFEELAKE(xe) &&
			    !IS_COMETLAKE(xe));
		return PCH_SPT;
	case INTEL_PCH_KBP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Kaby Lake PCH (KBP)\n");
		drm_WARN_ON(&xe->drm,
			    !IS_SKYLAKE(xe) &&
			    !IS_KABYLAKE(xe) &&
			    !IS_COFFEELAKE(xe) &&
			    !IS_COMETLAKE(xe));
		/* KBP is SPT compatible */
		return PCH_SPT;
	case INTEL_PCH_CNP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Cannon Lake PCH (CNP)\n");
		drm_WARN_ON(&xe->drm,
			    !IS_COFFEELAKE(xe) &&
			    !IS_COMETLAKE(xe));
		return PCH_CNP;
	case INTEL_PCH_CNP_LP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm,
			    "Found Cannon Lake LP PCH (CNP-LP)\n");
		drm_WARN_ON(&xe->drm,
			    !IS_COFFEELAKE(xe) &&
			    !IS_COMETLAKE(xe));
		return PCH_CNP;
	case INTEL_PCH_CMP_DEVICE_ID_TYPE:
	case INTEL_PCH_CMP2_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Comet Lake PCH (CMP)\n");
		drm_WARN_ON(&xe->drm,
			    !IS_COFFEELAKE(xe) &&
			    !IS_COMETLAKE(xe) &&
			    !IS_ROCKETLAKE(xe));
		/* CMP is CNP compatible */
		return PCH_CNP;
	case INTEL_PCH_CMP_V_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Comet Lake V PCH (CMP-V)\n");
		drm_WARN_ON(&xe->drm,
			    !IS_COFFEELAKE(xe) &&
			    !IS_COMETLAKE(xe));
		/* CMP-V is based on KBP, which is SPT compatible */
		return PCH_SPT;
	case INTEL_PCH_ICP_DEVICE_ID_TYPE:
	case INTEL_PCH_ICP2_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Ice Lake PCH\n");
		drm_WARN_ON(&xe->drm, !IS_ICELAKE(xe));
		return PCH_ICP;
	case INTEL_PCH_MCC_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Mule Creek Canyon PCH\n");
		drm_WARN_ON(&xe->drm, !(IS_JASPERLAKE(xe) ||
					      IS_ELKHARTLAKE(xe)));
		/* MCC is TGP compatible */
		return PCH_TGP;
	case INTEL_PCH_TGP_DEVICE_ID_TYPE:
	case INTEL_PCH_TGP2_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Tiger Lake LP PCH\n");
		drm_WARN_ON(&xe->drm, !IS_TIGERLAKE(xe) &&
			    !IS_ROCKETLAKE(xe) &&
			    !IS_GEN9_BC(xe));
		return PCH_TGP;
	case INTEL_PCH_JSP_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Jasper Lake PCH\n");
		drm_WARN_ON(&xe->drm, !(IS_JASPERLAKE(xe) ||
					      IS_ELKHARTLAKE(xe)));
		/* JSP is ICP compatible */
		return PCH_ICP;
	case INTEL_PCH_ADP_DEVICE_ID_TYPE:
	case INTEL_PCH_ADP2_DEVICE_ID_TYPE:
	case INTEL_PCH_ADP3_DEVICE_ID_TYPE:
	case INTEL_PCH_ADP4_DEVICE_ID_TYPE:
		drm_dbg_kms(&xe->drm, "Found Alder Lake PCH\n");
		drm_WARN_ON(&xe->drm, !IS_ALDERLAKE_S(xe) &&
			    !IS_ALDERLAKE_P(xe));
		return PCH_ADP;
	default:
		return PCH_NONE;
	}
}

static bool intel_is_virt_pch(unsigned short id,
			      unsigned short svendor, unsigned short sdevice)
{
	return (id == INTEL_PCH_P2X_DEVICE_ID_TYPE ||
		id == INTEL_PCH_P3X_DEVICE_ID_TYPE ||
		(id == INTEL_PCH_QEMU_DEVICE_ID_TYPE &&
		 svendor == PCI_SUBVENDOR_ID_REDHAT_QUMRANET &&
		 sdevice == PCI_SUBDEVICE_ID_QEMU));
}

static void
intel_virt_detect_pch(const struct xe_device *xe,
		      unsigned short *pch_id, enum intel_pch *pch_type)
{
	unsigned short id = 0;

	/*
	 * In a virtualized passthrough environment we can be in a
	 * setup where the ISA bridge is not able to be passed through.
	 * In this case, a south bridge can be emulated and we have to
	 * make an educated guess as to which PCH is really there.
	 */

	if (IS_ALDERLAKE_S(xe) || IS_ALDERLAKE_P(xe))
		id = INTEL_PCH_ADP_DEVICE_ID_TYPE;
	else if (IS_TIGERLAKE(xe) || IS_ROCKETLAKE(xe))
		id = INTEL_PCH_TGP_DEVICE_ID_TYPE;
	else if (IS_JASPERLAKE(xe) || IS_ELKHARTLAKE(xe))
		id = INTEL_PCH_MCC_DEVICE_ID_TYPE;
	else if (IS_ICELAKE(xe))
		id = INTEL_PCH_ICP_DEVICE_ID_TYPE;
	else if (IS_COFFEELAKE(xe) ||
		 IS_COMETLAKE(xe))
		id = INTEL_PCH_CNP_DEVICE_ID_TYPE;
	else if (IS_KABYLAKE(xe) || IS_SKYLAKE(xe))
		id = INTEL_PCH_SPT_DEVICE_ID_TYPE;
	else if (IS_HASWELL_ULT(xe) || IS_BROADWELL_ULT(xe))
		id = INTEL_PCH_LPT_LP_DEVICE_ID_TYPE;
	else if (IS_HASWELL(xe) || IS_BROADWELL(xe))
		id = INTEL_PCH_LPT_DEVICE_ID_TYPE;
	else if (GRAPHICS_VER(xe) == 6 || IS_IVYBRIDGE(xe))
		id = INTEL_PCH_CPT_DEVICE_ID_TYPE;
	else if (GRAPHICS_VER(xe) == 5)
		id = INTEL_PCH_IBX_DEVICE_ID_TYPE;

	if (id)
		drm_dbg_kms(&xe->drm, "Assuming PCH ID %04x\n", id);
	else
		drm_dbg_kms(&xe->drm, "Assuming no PCH\n");

	*pch_type = intel_pch_type(xe, id);

	/* Sanity check virtual PCH id */
	if (drm_WARN_ON(&xe->drm,
			id && *pch_type == PCH_NONE))
		id = 0;

	*pch_id = id;
}

void intel_detect_pch(struct xe_device *xe)
{
	struct pci_dev *pch = NULL;
	unsigned short id;
	enum intel_pch pch_type;

	/*
	 * South display engine on the same PCI device: just assign the fake
	 * PCH.
	 */
	if (DISPLAY_VER(xe) >= 20) {
		xe->pch_type = PCH_LNL;
		return;
	} else if (IS_BATTLEMAGE(xe) || IS_METEORLAKE(xe)) {
		/*
		 * Both north display and south display are on the SoC die.
		 * The real PCH (if it even exists) is uninvolved in display.
		 */
		xe->pch_type = PCH_MTL;
		return;
	} else if (IS_DG2(xe)) {
		xe->pch_type = PCH_DG2;
		return;
	} else if (IS_DG1(xe)) {
		xe->pch_type = PCH_DG1;
		return;
	}

	/*
	 * The reason to probe ISA bridge instead of Dev31:Fun0 is to
	 * make graphics device passthrough work easy for VMM, that only
	 * need to expose ISA bridge to let driver know the real hardware
	 * underneath. This is a requirement from virtualization team.
	 *
	 * In some virtualized environments (e.g. XEN), there is irrelevant
	 * ISA bridge in the system. To work reliably, we should scan trhough
	 * all the ISA bridge devices and check for the first match, instead
	 * of only checking the first one.
	 */
	while ((pch = pci_get_class(PCI_CLASS_BRIDGE_ISA << 8, pch))) {
		if (pch->vendor != PCI_VENDOR_ID_INTEL)
			continue;

		id = pch->device & INTEL_PCH_DEVICE_ID_MASK;

		pch_type = intel_pch_type(xe, id);
		if (pch_type != PCH_NONE) {
			xe->pch_type = pch_type;
			xe->pch_id = id;
			break;
		} else if (intel_is_virt_pch(id, pch->subsystem_vendor,
					     pch->subsystem_device)) {
			intel_virt_detect_pch(xe, &id, &pch_type);
			xe->pch_type = pch_type;
			xe->pch_id = id;
			break;
		}
	}

	/*
	 * Use PCH_NOP (PCH but no South Display) for PCH platforms without
	 * display.
	 */
	if (pch && !HAS_DISPLAY(xe)) {
		drm_dbg_kms(&xe->drm,
			    "Display disabled, reverting to NOP PCH\n");
		xe->pch_type = PCH_NOP;
		xe->pch_id = 0;
	} else if (!pch) {
		if (i915_run_as_guest() && HAS_DISPLAY(xe)) {
			intel_virt_detect_pch(xe, &id, &pch_type);
			xe->pch_type = pch_type;
			xe->pch_id = id;
		} else {
			drm_dbg_kms(&xe->drm, "No PCH found.\n");
		}
	}

	pci_dev_put(pch);
}
