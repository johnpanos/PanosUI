#pragma once
#include <EGL/egl.h>
#include <wayland-egl.h>

#include "deps/ext-blur-mask-unstable-v1.h"

typedef struct _EGLData
{
	EGLDisplay eglDisplay;
	EGLContext eglContext;
	EGLConfig eglConfig;
} EGLData;

struct UIPlatformGlobals
{
	struct wl_display *display;
	struct wl_compositor *compositor;
	struct wl_subcompositor *subcompositor;
	struct wl_seat *wl_seat;
	struct wl_shm *wl_shm;
	struct wl_registry *wl_registry;
	struct xdg_wm_base *wm_base;
	struct ext_blur_mask_manager_v1 *blur_mask_manager;

	EGLData eglData;
};

extern struct UIPlatformGlobals UIPlatformGlobalsShared;