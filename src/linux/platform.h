#pragma once

#include <wayland-egl.h>
#include <EGL/egl.h>
#include "../UIGraphicsContext.h"
#include "../UIWindow.h"
#include "globals.h"

EGLData init_egl(struct wl_display *wl_display);

UIGraphicsContext *UIGraphicsContextCreate(EGLSurface eglSurface, int width, int height);
void UIGraphicsContextDestroy(UIGraphicsContext *context);