/* SPDX-License-Identifier: MIT */

<<<<<<< HEAD
#ifndef DRM_FBDEV_SHMEM_H
#define DRM_FBDEV_SHMEM_H

struct drm_device;

#ifdef CONFIG_DRM_FBDEV_EMULATION
=======
#define DRM_FBDEV_SHMEM_H

struct drm_device;
struct drm_fb_helper;
struct drm_fb_helper_surface_size;

#ifdef CONFIG_DRM_FBDEV_EMULATION
int drm_fbdev_shmem_driver_fbdev_probe(struct drm_fb_helper *fb_helper,
                                      struct drm_fb_helper_surface_size *sizes);

#define DRM_FBDEV_SHMEM_DRIVER_OPS \
       .fbdev_probe = drm_fbdev_shmem_driver_fbdev_probe

>>>>>>> drm/fbdev-shmem: Support struct drm_driver.fbdev_probe
void drm_fbdev_shmem_setup(struct drm_device *dev, unsigned int preferred_bpp);
#else
static inline void drm_fbdev_shmem_setup(struct drm_device *dev, unsigned int preferred_bpp)
{ }
<<<<<<< HEAD
=======

#define DRM_FBDEV_SHMEM_DRIVER_OPS \
       .fbdev_probe = NULL
>>>>>>> drm/fbdev-shmem: Support struct drm_driver.fbdev_probe
#endif

#endif
