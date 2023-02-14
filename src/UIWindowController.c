#include <stdlib.h>
#include <stdio.h>
#include "UIWindowController.h"
#include "UIWindow.h"

void doNothing()
{
}

UIRect defaultWindowWillResize(UIWindow window, UIRect to)
{
    printf("Window will resize: w(%f) h(%f)\n", to.size.width, to.size.height);
    if (to.size.width == 0 && to.size.height == 0)
    {
        return window->frame;
    }

    return to;
}

void defaultWindowDidResize(UIWindow window)
{
    printf("Window did resize: w(%f) h(%f)\n", window->frame.size.width, window->frame.size.height);
    window->contentFrame = UIRectInset(window->frame, 16.0f, 16.0f);
}

struct _UIWindowController UIWindowControllerDefault = {
    .windowWillLoad = &doNothing,
    .windowDidLoad = &doNothing,
    .windowWillResize = &defaultWindowWillResize,
    .windowDidResize = &defaultWindowDidResize};

UIWindowController UIWindowControllerGetDefault()
{
    return &UIWindowControllerDefault;
}

UIWindowController UIWindowControllerCreate()
{
    UIWindowController windowController = calloc(1, sizeof(struct _UIWindowController));

    windowController->windowWillLoad = &doNothing;
    windowController->windowDidLoad = &doNothing;
    windowController->windowWillResize = &defaultWindowWillResize;
    windowController->windowDidResize = &defaultWindowDidResize;

    return windowController;
}

void UIWindowControllerDestroy(UIWindowController windowController)
{
    windowController->_window = NULL;
    free(windowController);
}