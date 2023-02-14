#pragma once
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