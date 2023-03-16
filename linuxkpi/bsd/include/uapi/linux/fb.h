/*-
 * Copyright (c) 2023 Beckhoff Automation GmbH & Co. KG
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _BSD_LKPI_UAPI_LINUX_FB_H_
#define	_BSD_LKPI_UAPI_LINUX_FB_H_

#define	FB_ACCEL_NONE	0

#define	FB_ACCELF_TEXT	1

#define	FB_ACTIVATE_NOW	1

#define	FB_BLANK_UNBLANK       0
#define	FB_BLANK_NORMAL	       1
#define	FB_BLANK_HSYNC_SUSPEND 2
#define	FB_BLANK_VSYNC_SUSPEND 3
#define	FB_BLANK_POWERDOWN     4

#define	FB_ROTATE_UR	0
#define	FB_ROTATE_CW	1
#define	FB_ROTATE_UD	2
#define	FB_ROTATE_CCW	3

#define	FB_SCREENINFO_ID 16

#define	FB_TYPE_PACKED_PIXELS 1

#define	FB_VISUAL_PSEUDOCOLOR 1
#define	FB_VISUAL_TRUECOLOR   2

#define	FBIO_WAITFORVSYNC	_IOW('F', 0x20, __u32)

#define	KHZ2PICOS(x) 	(1000000000ul * (x))

#define	ROP_COPY 1

struct fb_bitfield {
	uint32_t offset;
	uint32_t length;
	bool	 msb_right;
};

struct fb_cmap {
	uint32_t start;
	uint32_t len;

	uint16_t *red;
	uint16_t *green;
	uint16_t *blue;
};

struct fb_copyarea {
	uint32_t dx;
	uint32_t dy;

	uint32_t width;
	uint32_t height;
};

struct fb_cursor {
};

struct fb_fillrect {
	uint32_t dx;
	uint32_t dy;

	uint32_t width;
	uint32_t height;

	uint32_t color;
	int		 rop;
};

struct fb_fix_screeninfo {
	int		   line_length;
	int		   visual;

	int		   type;
	int		   type_aux;

	int		   accel;

	int		   xpanstep;
	int		   ypanstep;
	int		   ywrapstep;

	vm_paddr_t mmio_start;
	uint64_t   mmio_len;

	vm_paddr_t smem_start;
	uint64_t   smem_len;

	char	   id[FB_SCREENINFO_ID];
};

struct fb_image {
	uint32_t dx;
	uint32_t dy;

	uint32_t width;
	uint32_t height;
	uint32_t depth;

	uint32_t fg_color;
	uint32_t bg_color;

	const char *data;
};

struct fb_var_screeninfo {
	uint32_t width;
	uint32_t height;

	int		 xres;
	int		 yres;
	int		 xres_virtual;
	int		 yres_virtual;

	uint32_t xoffset;
	uint32_t yoffset;

	int		 bits_per_pixel;
	int		 grayscale;

	uint32_t pixclock;

	int		 accel_flags;
	int		 activate;

	struct fb_bitfield red;
	struct fb_bitfield green;
	struct fb_bitfield blue;
	struct fb_bitfield transp;
};

#endif	/* _BSD_LKPI_UAPI_FB_H_ */
