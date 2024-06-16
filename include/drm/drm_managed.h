/* Public domain. */

#ifndef _DRM_MANAGED_H_
#define _DRM_MANAGED_H_

#include <linux/mutex.h>
#include <linux/types.h>

struct drm_device;

typedef void (*drmm_func_t)(struct drm_device *, void *);

void *drmm_kmalloc(struct drm_device *, size_t, int);
void *drmm_kzalloc(struct drm_device *, size_t, int);
void *drmm_kcalloc(struct drm_device *, size_t, size_t, int);
char *drmm_kstrdup(struct drm_device *, const char *, int);
void drmm_kfree(struct drm_device *, void *);
int drmm_add_action(struct drm_device *, drmm_func_t, void *);
int drmm_add_action_or_reset(struct drm_device *, drmm_func_t, void *);
void drmm_release_action(struct drm_device *, drmm_func_t, void *);

void drmm_mutex_release(struct drm_device *, void *);

static inline int
drmm_mutex_init(struct drm_device *dev, struct mutex *m)
{
    mutex_init(m);
    return drmm_add_action_or_reset(dev, drmm_mutex_release, m);
}

#endif
