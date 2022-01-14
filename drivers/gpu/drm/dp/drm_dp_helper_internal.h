/* Public domain */
#ifndef _DRM_DP_HELPER_INTERNAL_H_
#define _DRM_DP_HELPER_INTERNAL_H_

struct drm_dp_aux;

/* drm_dp_aux_dev.c */
#ifdef CONFIG_DRM_DP_AUX_CHARDEV
int drm_dp_aux_dev_init(void);
void drm_dp_aux_dev_exit(void);
int drm_dp_aux_register_devnode(struct drm_dp_aux *aux);
void drm_dp_aux_unregister_devnode(struct drm_dp_aux *aux);
#else
static inline int drm_dp_aux_dev_init(void)
{
	return 0;
}

static inline void drm_dp_aux_dev_exit(void)
{
}

static inline int drm_dp_aux_register_devnode(struct drm_dp_aux *aux)
{
	return 0;
}

static inline void drm_dp_aux_unregister_devnode(struct drm_dp_aux *aux)
{
}
#endif

#endif /* _DRM_DP_HELPER_INTERNAL_H_ */

