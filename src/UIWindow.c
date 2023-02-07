#include <stdlib.h>
#include "UIWindow.h"
#include "UIViewController.h"

UIWindow UIWindowCreate(UIRect frame)
{
    UIWindow window = malloc(sizeof(struct _UIWindow));
    
    ArrayAddValue(UIApplicationShared()->windows, window);

    window->frame = frame;
    window->mainView = UIViewCreate(frame, frame);
    window->mainView->clipToBounds = 1;
    window->graphicsContext = NULL;

    _UIPlatformWindowCreate(window);

    return window;
}

void UIWindowDestroy(UIWindow window)
{
    _UIPlatformWindowDestroy(window);

    ArrayRemoveValueByRef(UIApplicationShared()->windows, window);

    free(window);    
}

void UIWindowSetTitle(UIWindow window, const char *title)
{
    window->title = title;
    _UIPlatformWindowSetTitle(window, title);
}