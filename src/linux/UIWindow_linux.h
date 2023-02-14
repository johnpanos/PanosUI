#pragma once
#include <EGL/egl.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include "../UIWindow.h"

typedef struct _UIPlatformWindow
{
    UIWindow window;

    struct wl_surface *wlSurface;
    struct xdg_surface *xdgSurface;
    struct xdg_toplevel *xdgToplevel;

    struct wl_egl_window *eglWindow;
    EGLSurface eglSurface;
} UIPlatformWindow;