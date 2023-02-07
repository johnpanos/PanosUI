#include <stdlib.h>
#include "UIWindow.h"

UIWindow UIWindowCreate(UIRect frame)
{
    UIWindow window = malloc(sizeof(struct _UIWindow));

    ArrayAddValue(UIApplicationShared()->windows, window);

    window->frame = frame;
    window->mainView = UIViewCreate(frame, frame);
    window->mainView->clipToBounds = 1;
    window->graphicsContext = NULL;
    window->controller = UIWindowControllerGetDefault();

    return window;
}

void UIWindowShow(UIWindow window)
{
    window->controller->windowWillLoad();

    _UIPlatformWindowCreate(window);

    window->controller->windowDidLoad();
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

void RENDER_SUBVIEWS(UIView view, UIGraphicsContext *context)
{
    UIViewDrawInContext(view, context);
    for (int i = 0; i < ArrayGetCapacity(view->subviews); i++)
    {
        UIView viewToRender = ArrayGetValueAtIndex(view->subviews, i);
        RENDER_SUBVIEWS(viewToRender, context);
    }
}

void UIWindowUpdate(UIWindow window)
{
    UIView rootView = window->mainView;

    if (rootView != NULL && rootView->needsDisplay)
    {
        UIGraphicsContextMakeCurrent(window->graphicsContext);

        RENDER_SUBVIEWS(rootView, window->graphicsContext);
        UIGraphicsContextFlush(window->graphicsContext);

        rootView->needsDisplay = 0;
    }
}