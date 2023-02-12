#pragma once

#include "UIGeometry.h"

typedef struct _UIWindow *UIWindow;
typedef struct _UIWindowController
{
    UIRect (*windowWillResize)(UIWindow window, UIRect size);
    void (*windowDidResize)(UIWindow window);

    void (*windowWillLoad)(UIWindow window);
    void (*windowDidLoad)(UIWindow window);

    UIWindow *_window;
} *UIWindowController;

UIWindowController UIWindowControllerCreate();
void UIWindowControllerDestroy(UIWindowController windowController);