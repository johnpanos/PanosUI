#pragma once

#include "UIRect.h"

typedef struct _UIWindow *UIWindow;
typedef struct _UIWindowController
{
    UIRect (*windowWillResize)(UIWindow window, UIRect size);
    void (*windowDidResize)();

    void (*windowWillLoad)();
    void (*windowDidLoad)();

    UIWindow *_window;
} *UIWindowController;

UIWindowController UIWindowControllerCreate();
void UIWindowControllerDestroy(UIWindowController windowController);