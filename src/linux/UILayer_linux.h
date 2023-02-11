#pragma once

#include "../UILayer.h"
#include "wayland-client.h"
#include "wayland-egl.h"
#include <EGL/egl.h>

typedef struct _UIPlatformLayer
{
    struct wl_surface *surface;
    struct wl_subsurface *subsurface;
    struct wl_egl_window *egl_window;

    EGLSurface egl_surface;
} UIPlatformLayer;

static const struct wl_callback_listener frame_listener;

UIPlatformLayer *_UIPlatformCreateLayer();