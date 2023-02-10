#include <stdlib.h>
#include <stdio.h>
#include "UIWindowController.h"
#include "UIWindow.h"

void doNothing()
{
}

UIRect defaultWindowWillResize(UIWindow window, UIRect to)
{
    printf("Window will resize: w(%d) h(%d)\n", to.width, to.height);
    if (to.width == 0 && to.height == 0)
    {
        return window->frame;
    }

    return to;
}

void defaultWindowDidResize(UIWindow window) {
    printf("Window did resize: w(%d) h(%d)\n", window->frame.width, window->frame.height);
    window->contentFrame = UIRectInset(window->frame, 16, 16, 16, 16);
}

struct _UIWindowController UIWindowControllerDefault = {
    .windowWillLoad = &doNothing,
    .windowDidLoad = &doNothing,
    .windowWillResize = &defaultWindowWillResize,
    .windowDidResize = &defaultWindowDidResize};

UIWindowController UIWindowControllerGetDefault() {
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