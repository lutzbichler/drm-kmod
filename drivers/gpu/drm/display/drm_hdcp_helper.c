/* Public domain */
#include <drm/display/drm_hdcp_helper.h>

int 
drm_hdcp_check_ksvs_revoked(struct drm_device *dev, u8 *ksvs, u32 ksv_count)
{
	return (0);
}

int
drm_connector_attach_content_protection_property(
	struct drm_connector *connector, bool hdcp_content_type)
{
	return (0);
}

void
drm_hdcp_update_content_protection(struct drm_connector *connector, u64 val)
{
}
