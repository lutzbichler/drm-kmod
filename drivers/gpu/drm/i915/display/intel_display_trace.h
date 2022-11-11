/* Public domain. */

#ifndef __INTEL_DISPLAY_TRACE_H__
#define __INTEL_DISPLAY_TRACE_H__

#include <sys/param.h>
#include <sys/ktr.h>

#include "i915_drv.h"
#include "i915_irq.h"
#include "intel_crtc.h"
#include "intel_display_types.h"

static inline void
trace_intel_pipe_enable(struct intel_crtc *crtc)
{
#ifdef KTR
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const char *name = dev_name(i915->base.dev->dev);
	struct intel_crtc *it__;
	uint32_t frame[3], scanline[3];

	for_each_intel_crtc(&dev_priv->drm, it__) {
		frame[it__->pipe] = intel_crtc_get_vblank_counter(it__);
		scanline[it__->pipe] = intel_get_crtc_scanline(it__);
	}
#endif

	CTR2(KTR_DRM,
	    "intel_pipe_enable[1/4]: dev %s, pipe %c enable",
		name, pipe_name(crtc->pipe));
	CTR3(KTR_DRM,
	    "intel_pipe_enable[2/4]: dev %s, "
	    "pipe A: frame=%u, scanline=%u",
		name, frame[PIPE_A], scanline[PIPE_A]);
	CTR3(KTR_DRM,
	    "intel_pipe_enable[3/4]: dev %s, "
	    "pipe B: frame=%u, scanline=%u",
		name, frame[PIPE_B], scanline[PIPE_B]);
	CTR3(KTR_DRM,
	    "intel_pipe_enable[4/4]: dev %s, "
	    "pipe C: frame=%u, scanline=%u",
		name, frame[PIPE_C], scanline[PIPE_C]);
}

static inline void
trace_intel_pipe_disable(struct intel_crtc *crtc)
{
#ifdef KTR
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	const char *name = dev_name(i915->base.dev->dev);
	struct intel_crtc *it__;
	uint32_t frame[3], scanline[3];

	for_each_intel_crtc(&dev_priv->drm, it__) {
		frame[it__->pipe] = intel_crtc_get_vblank_counter(it__);
		scanline[it__->pipe] = intel_get_crtc_scanline(it__);
	}
#endif

	CTR2(KTR_DRM,
	    "intel_pipe_enable[1/4]: dev %s, pipe %c enable",
		name, pipe_name(crtc->pipe));
	CTR3(KTR_DRM,
	    "intel_pipe_disable[2/4]: dev %s"
	    "pipe A: frame=%u, scanline=%u",
		name, frame[PIPE_A], scanline[PIPE_A]);
	CTR3(KTR_DRM,
	    "intel_pipe_disable[3/4]: dev %s"
	    "pipe B: frame=%u, scanline=%u",
		name, frame[PIPE_B], scanline[PIPE_B]);
	CTR3(KTR_DRM,
	    "intel_pipe_disable[4/4]: dev %s"
	    "pipe C: frame=%u, scanline=%u",
		name, frame[PIPE_C], scanline[PIPE_C]);
}

static inline void
trace_intel_pipe_crc(struct intel_crtc *crtc, const u32 *crcs)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR4(KTR_DRM,
	    "intel_pipe_crc[1/2]: dev %s, pipe %c, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe),
	    intel_crtc_get_vblank_counter(crtc),
	    intel_get_crtc_scanline(crtc));
	CTR6(KTR_DRM,
	    "intel_pipe_crc[2/2]: dev %s, crc=%08x %08x %08x %08x %08x",
	    name, crcs[0], crcs[1], crcs[2], crcs[3], crcs[4]);
}

static inline void
trace_intel_cpu_fifo_underrun(struct drm_i915_private *dev_priv, enum pipe pipe)
{
#ifdef KTR
	const char *name = dev_name(i915->base.dev->dev);
	struct intel_crtc *crtc = intel_crtc_for_pipe(dev_priv, pipe);
#endif

	CTR4(KTR_DRM,
	    "intel_cpu_fifo_underrun: dev %s, pipe %c, frame=%u, scanline=%u",
	    name, pipe_name(pipe),
	    intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_pch_fifo_underrun(struct drm_i915_private *dev_priv, enum pipe pch_transcoder)
{
#ifdef KTR
	const char *name = dev_name(i915->base.dev->dev);
	enum pipe pipe = pch_transcoder;
	struct intel_crtc *crtc = intel_crtc_for_pipe(dev_priv, pipe);
#endif

	CTR4(KTR_DRM,
	    "intel_pch_fifo_underrun: dev %s, pch transcoder %c, frame=%u, scanline=%u",
	    name, pipe_name(pipe),
	    intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_memory_cxsr(struct drm_i915_private *dev_priv, bool old, bool new)
{
#ifdef KTR
	const char *name = dev_name(i915->base.dev->dev);
	struct intel_crtc *crtc;
	uint32_t frame[3], scanline[3];

	for_each_intel_crtc(&dev_priv->drm, crtc) {
		frame[crtc->pipe] = intel_crtc_get_vblank_counter(crtc);
		scanline[crtc->pipe] = intel_get_crtc_scanline(crtc);
	}
#endif

	CTR3(KTR_DRM,
	    "intel_memory_cxsr[1/4]: dev %s, %s->%s",
	    name, str_on_off(old), str_on_off(new));
	CTR3(KTR_DRM,
	    "intel_memory_cxsr[2/4]: dev %s, "
	    "pipe A: frame=%u, scanline=%u",
		name, frame[PIPE_A], scanline[PIPE_A]);
	CTR3(KTR_DRM,
	    "intel_memory_cxsr[3/4]: dev %s, "
	    "pipe B: frame=%u, scanline=%u",
	    name, frame[PIPE_B], scanline[PIPE_B]);
	CTR3(KTR_DRM,
	    "intel_memory_cxsr[4/4]: dev %s, "
	    "pipe C: frame=%u, scanline=%u",
	    name, frame[PIPE_C], scanline[PIPE_C]);
}

static inline void
trace_g4x_wm(struct intel_crtc *crtc, const struct g4x_wm_values *wm)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR4(KTR_DRM,
	    "g4x_wm[1/4]: dev %s, pipe %c, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe),
		intel_crtc_get_vblank_counter(crtc),
		intel_get_crtc_scanline(crtc));
	CTR4(KTR_DRM,
		"g4x_wm[2/4]: dev %s, wm %d/%d/%d",
		name,
	    wm->pipe[crtc->pipe].plane[PLANE_PRIMARY],
	    wm->pipe[crtc->pipe].plane[PLANE_SPRITE0],
	    wm->pipe[crtc->pipe].plane[PLANE_CURSOR]);
	CTR5(KTR_DRM,
	    "g4x_wm[3/4]: dev %s, sr %s/%d/%d/%d",
		name,
		str_yes_no(wm->cxsr),
		wm->sr.plane, wm->sr.cursor, wm->sr.fbc);
	CTR6(KTR_DRM,
	    "g4x_wm(4/4]: dev %s, hpll %s/%d/%d/%d, fbc %s",
	    name,
		str_yes_no(wm->hpll_en),
		wm->hpll.plane, wm->hpll.cursor, wm->hpll.fbc,
	    str_yes_no(wm->fbc_en));
}

static inline void
trace_vlv_wm(struct intel_crtc *crtc, const struct vlv_wm_values *wm)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR6(KTR_DRM,
	    "vlv_wm[1/3]: dev %s, pipe %c, frame=%u, scanline=%u, level=%d, cxsr=%d",
	    name, pipe_name(crtc->pipe), intel_crtc_get_vblank_counter(crtc),
	    intel_get_crtc_scanline(crtc), wm->level, wm->cxsr);
	CTR5(KTR_DRM,
	    "vlv_wm[2/3]: dev %s wm %d/%d/%d/%d",
		name,
	    wm->pipe[crtc->pipe].plane[PLANE_PRIMARY],
	    wm->pipe[crtc->pipe].plane[PLANE_SPRITE0],
	    wm->pipe[crtc->pipe].plane[PLANE_SPRITE1],
	    wm->pipe[crtc->pipe].plane[PLANE_CURSOR]);
	CTR3(KTR_DRM,
		"vlv_wm[3/3]: dev %s sr %d/%d",
		name, wm->sr.plane, wm->sr.cursor);
}

static inline void
trace_vlv_fifo_size(struct intel_crtc *crtc, u32 sprite0_start, u32 sprite1_start, u32 fifo_size)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR3(KTR_DRM,
	    "vlv_fifo_size[1/2]: dev %s, pipe %c, frame=%u",
	    name, pipe_name(crtc->pipe), intel_crtc_get_vblank_counter(crtc));
	CTR5(KTR_DRM,
		"vlv_fifo_size[2/2]: dev %s scanline=%u, %d/%d/%d",
	    name, intel_get_crtc_scanline(crtc),
		sprite0_start, sprite1_start, fifo_size);
}

static inline void
trace_intel_plane_update_noarm(struct intel_plane *plane, struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR5(KTR_DRM,
	    "intel_plane_update_noarm[1/3]: dev %s, pipe %c, plane %s, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), plane->base.name,
	    intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
	/* FIXME FreeBSD
	CTR8(KTR_DRM,
	    "intel_plane_update_noarm[2/3]: " DRM_RECT_FP_FMT " ->",
	    DRM_RECT_FP_ARG(&plane->base.state->src));
	CTR4(KTR_DRM,
	    "intel_plane_update_noarm[3/3]: " DRM_RECT_FMT,
	    DRM_RECT_ARG(&plane->base.state->dst)); */
}

static inline void
trace_intel_plane_update_arm(struct intel_plane *plane, struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR5(KTR_DRM,
	    "intel_plane_update_arm[1/3]: dev %s, pipe %c, plane %s, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), plane->base.name,
	    intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
	/* FIXME FreeBSD
	CTR8(KTR_DRM,
	    "intel_plane_update_arm[2/3]: " DRM_RECT_FP_FMT " ->",
	    DRM_RECT_FP_ARG(&plane->base.state->src));
	CTR4(KTR_DRM,
	    "intel_plane_update_arm[3/3]: " DRM_RECT_FMT,
	    DRM_RECT_ARG(&plane->base.state->dst)); */
}

static inline void
trace_intel_plane_disable_arm(struct intel_plane *plane, struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR5(KTR_DRM,
	    "intel_plane_disable_arm: dev %s, pipe %c, plane %s, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), plane->base.name,
	    intel_crtc_get_vblank_counter(crtc), __entry->scanline);
}

static inline void
trace_intel_fbc_activate(struct intel_plane *plane)
{
#ifdef KTR
	struct intel_crtc *crtc = intel_crtc_for_pipe(to_i915(plane->base.dev),
	    plane->pipe);
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR5(KTR_DRM,
	    "intel_fbc_activate: dev %s, pipe %c, plane %s, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), plane->base.name, intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_fbc_deactivate(struct intel_plane *plane)
{
#ifdef KTR
	struct intel_crtc *crtc = intel_crtc_for_pipe(to_i915(plane->base.dev),
	    plane->pipe);
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR5(KTR_DRM,
	    "intel_fbc_deactivate: dev %s, pipe %c, plane %s, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), plane->base.name, intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_fbc_nuke(struct intel_plane *plane)
{
#ifdef KTR
	struct intel_crtc *crtc = intel_crtc_for_pipe(to_i915(plane->base.dev),
	    plane->pipe);
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR5(KTR_DRM,
	    "intel_fbc_nuke: dev %s, pipe %c, plane %s, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), plane->base.name, intel_crtc_get_vblank_counter(crtc), intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_crtc_vblank_work_start(struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR4(KTR_DRM,
	    "intel_crtc_vblank_work_start: dev %s, pipe %c, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), intel_crtc_get_vblank_counter(crtc),
	    intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_crtc_vblank_work_end(struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR4(KTR_DRM,
	    "intel_crtc_vblank_work_end: dev %s, pipe %c, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), intel_crtc_get_vblank_counter(crtc),
	    intel_get_crtc_scanline(crtc));
}

static inline void
trace_intel_pipe_update_start(struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR6(KTR_DRM,
	    "dev %s, pipe %c, frame=%u, scanline=%u, min=%u, max=%u",
	    name, pipe_name(crtc->pipe), intel_crtc_get_vblank_counter(crtc),
	    intel_get_crtc_scanline(crtc), crtc->debug.min_vbl, crtc->debug.max_vbl);
}

static inline void
trace_intel_pipe_update_vblank_evaded(struct intel_crtc *crtc)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR6(KTR_DRM,
	    "intel_pipe_update_vblank_evaded: dev %s, pipe %c, frame=%u, scanline=%u, min=%u, max=%u",
	    name, pipe_name(crtc->pipe), crtc->debug.start_vbl_count,
	    crtc->debug.scanline_start, crtc->debug.min_vbl, crtc->debug.max_vbl);
}

static inline void
trace_intel_pipe_update_end(struct intel_crtc *crtc, u32 frame, int scanline_end)
{
#ifdef KTR
	const char *name = dev_name(crtc->base.dev->dev);
#endif

	CTR4(KTR_DRM,
	    "intel_pipe_update_end: dev %s, pipe %c, frame=%u, scanline=%u",
	    name, pipe_name(crtc->pipe), frame, scanline_end);
}

static inline void
trace_intel_frontbuffer_invalidate(struct drm_i915_private *i915, int frontbuffer_bits, unsigned int origin)
{
#ifdef KTR
	const char *name = dev_name(i915->base.dev->dev);
#endif

	CTR3(KTR_DRM,
	    "intel_frontbuffer_invalidate: dev %s, frontbuffer_bits=0x%08x, origin=%u",
	    name, frontbuffer_bits, origin);
}

static inline void
trace_intel_frontbuffer_flush(struct drm_i915_private *i915, unsigned int frontbuffer_bits, unsigned int origin)
{
#ifdef KTR
	const char *name = dev_name(i915->base.dev->dev);
#endif

	CTR3(KTR_DRM,
	    "intel_frontbuffer_flush: dev %s, frontbuffer_bits=0x%08x, origin=%u",
	    name, frontbuffer_bits, origin);
}

#endif /* __INTEL_DISPLAY_TRACE_H__ */
