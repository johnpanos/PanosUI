#pragma once
#include "../UIWindow.h"

typedef struct _UIPlatformWindow
{
    UIWindow window;

    struct xdg_surface *xdg_surface;
    struct xdg_toplevel *toplevel;
} UIPlatformWindow;