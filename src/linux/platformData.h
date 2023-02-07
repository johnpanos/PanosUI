#pragma once

#include "../UIWindow.h"
#include <wayland-egl.h>
#include <EGL/egl.h>

struct UIPlatformGlobals
{
    struct wl_display *display;
    struct wl_compositor *compositor;
    struct wl_seat *wl_seat;
    struct wl_shm *wl_shm;
    struct wl_registry *wl_registry;
    struct xdg_wm_base *wm_base;
};

struct UIWindowPlatformData
{
    UIWindow window;

    struct wl_surface *surface;
    struct xdg_surface *xdg_surface;
    struct xdg_toplevel *toplevel;

    struct wl_egl_window *egl_window;

    EGLDisplay egl_display;
    EGLSurface egl_surface;
    EGLContext egl_context;
};

UIGraphicsContext *UIGraphicsContextCreate(int width, int height, EGLDisplay eglDisplay, EGLSurface eglSurface, EGLContext eglContext);

struct UIWindowPlatformData *ToPlatformData(UIWindow window);

void setupSeat();