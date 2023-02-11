#pragma once
#include <wayland-egl.h>
#include <EGL/egl.h>

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

    EGLData eglData;
};

extern struct UIPlatformGlobals UIPlatformGlobalsShared;