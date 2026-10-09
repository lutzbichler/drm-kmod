/* Public domain. */

#include <linux/acpi.h>
#include <acpi/video.h>

#include "i915_drv.h"
#include "intel_acpi.h"

void intel_register_dsm_handler(void)
{
}

void intel_unregister_dsm_handler(void)
{
}

void intel_dsm_get_bios_data_funcs_supported(struct intel_display *display)
{
}

void intel_acpi_device_id_update(struct intel_display *display)
{
}

void intel_acpi_assign_connector_fwnodes(struct intel_display *display)
{
}

void intel_acpi_video_register(struct intel_display *display)
{
	acpi_video_register();
}
