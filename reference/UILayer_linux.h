#pragma once

#include "../UILayer.h"
#include "wayland-client.h"
#include "wayland-egl.h"
#include <EGL/egl.h>

typedef struct _UILayerWindow
{
    EGLSurface eglSurface;
    struct wl_surface *surface;
    struct wl_egl_window *eglWindow;
} UILayerWindow;

typedef struct _UILayerSubsurface
{
    struct wl_surface *surface;
    struct wl_subsurface *subsurface;
    struct wl_egl_window *eglWindow;

    EGLSurface surface;
} UILayerSubsurface;

static const struct wl_callback_listener frame_listener;

UIPlatformLayer *_UIPlatformCreateLayer();