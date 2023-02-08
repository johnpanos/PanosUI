#include <stdlib.h>
#include "UIWindowController.h"
#include "UIWindow.h"

void doNothing()
{
}

UIRect defaultWindowWillResize(UIWindow window, UIRect to)
{
    if (to.width == 0 && to.height == 0)
    {
        return window->frame;
    }

    return to;
}

struct _UIWindowController UIWindowControllerDefault = {
    .windowWillLoad = &doNothing,
    .windowDidLoad = &doNothing,
    .windowWillResize = &defaultWindowWillResize,
    .windowDidResize = &doNothing};

UIWindowController UIWindowControllerGetDefault() {
    return &UIWindowControllerDefault;
}

UIWindowController UIWindowControllerCreate()
{
    UIWindowController windowController = calloc(1, sizeof(struct _UIWindowController));

    windowController->windowWillLoad = &doNothing;
    windowController->windowDidLoad = &doNothing;
    windowController->windowWillResize = &defaultWindowWillResize;
    windowController->windowDidResize = &doNothing;

    return windowController;
}

void UIWindowControllerDestroy(UIWindowController windowController)
{
    windowController->_window = NULL;
    free(windowController);
}