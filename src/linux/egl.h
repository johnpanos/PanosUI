#pragma once
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <wayland-client.h>

typedef struct _EGLData {
    EGLDisplay eglDisplay;
    EGLContext eglContext;
    EGLConfig eglConfig;
} EGLData;

EGLData init_egl(struct wl_display *wl_display);
extern EGLData globalEglData;