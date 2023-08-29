/* Public domain */

#ifndef DRM_ACCEL_H_
#define DRM_ACCEL_H_

struct drm_device;
struct drm_minor;

static inline int
accel_core_init(void)
{

    return (0);
}

static inline void
accel_core_exit(void)
{

}

static inline int
accel_minor_alloc(void)
{

    return (-ENOTSUPP);
}

static inline void
accel_minor_remove(int index __unused)
{

} 

static inline void
accel_minor_replace(struct drm_minor *minor __unused, int index __unused)
{

}

static inline void
accel_debugfs_init(struct drm_device *dev)
{

}

static inline void
accel_debugfs_register(struct drm_device *dev)
{

}

#endif /* DRM_ACCEL_H_ */

