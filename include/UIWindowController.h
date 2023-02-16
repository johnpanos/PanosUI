#pragma once

#include "UIGeometry.h"

typedef struct _UIWindow *UIWindow;
typedef struct _UIWindowController
{
    void *_self;
    UIRect (*windowWillResize)(void *self, UIWindow window, UIRect size);
    void (*windowDidResize)(void *self, UIWindow window);
    void (*windowWillLoad)(void *self, UIWindow window);
    void (*windowDidLoad)(void *self, UIWindow window);

    UIWindow *_window;
} *UIWindowController;

UIWindowController UIWindowControllerCreate();
void UIWindowControllerDestroy(UIWindowController windowController);