#pragma once

#include "../UIGraphicsContext.h"
#include "../UIWindow.h"
#include "globals.h"
#include <EGL/egl.h>
#include <wayland-egl.h>

EGLData init_egl(struct wl_display *wl_display);

UIGraphicsContext *UIGraphicsContextCreate(EGLSurface eglSurface, int width, int height);
void UIGraphicsContextDestroy(UIGraphicsContext *context);