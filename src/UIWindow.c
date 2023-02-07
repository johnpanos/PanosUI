#include <stdlib.h>
#include "UIWindow.h"

UIView _UIWindowCreateFrameView(UIWindow window)
{
    UIRect titlebarFrame = {
        .x = 0, .y = 0, .width = window->frame.width, .height = 28};
    UIView titlebar = UIViewCreate(titlebarFrame, titlebarFrame);
    titlebar->borderColor = UIColorCreateRGBA(0, 0, 0, 21);
    titlebar->borderWidth = 0.5f;

    UIRect redFrame = {.x = 8, .y = 8, .width = 12, .height = 12};
    UIColor red = {.r = 255, .g = 94, .b = 87, .a = 255};
    UIView redLight = UIViewCreate(redFrame, redFrame);
    redLight->cornerRadius = 12;
    redLight->backgroundColor = red;
    redLight->borderColor = UIColorCreateRGBA(0, 0, 0, 21);
    redLight->borderWidth = 0.5f;

    UIRect yellowFrame = {.x = 8 + 20, .y = 8, .width = 12, .height = 12};
    UIColor yellow = {.r = 255, .g = 187, .b = 46, .a = 255};
    UIView yellowLight = UIViewCreate(yellowFrame, yellowFrame);
    yellowLight->cornerRadius = 12;
    yellowLight->backgroundColor = yellow;
    yellowLight->borderColor = UIColorCreateRGBA(0, 0, 0, 21);
    yellowLight->borderWidth = 0.5f;

    UIRect greenFrame = {.x = 8 + 40, .y = 8, .width = 12, .height = 12};
    UIColor green = {.r = 56, .g = 193, .b = 73, .a = 255};
    UIView greenLight = UIViewCreate(greenFrame, greenFrame);
    greenLight->cornerRadius = 12;
    greenLight->backgroundColor = green;
    greenLight->borderColor = UIColorCreateRGBA(0, 0, 0, 21);
    greenLight->borderWidth = 0.5f;

    UIViewAddSubview(titlebar, redLight);
    UIViewAddSubview(titlebar, yellowLight);
    UIViewAddSubview(titlebar, greenLight);

    titlebar->needsDisplay = 1;

    return titlebar;
}

UIWindow UIWindowCreate(UIRect frame)
{
    UIWindow window = malloc(sizeof(struct _UIWindow));

    ArrayAddValue(UIApplicationShared()->windows, window);

    window->frame = frame;
    window->mainView = UIViewCreate(frame, frame);
    window->mainView->clipToBounds = 1;
    window->graphicsContext = NULL;
    window->controller = UIWindowControllerGetDefault();
    window->frameView = _UIWindowCreateFrameView(window);

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
        UIGraphicsContextClipToRect(window->graphicsContext, window->frame, 10.0f);
        UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(255, 255, 255, 255));
        UIGraphicsContextAddRect(window->graphicsContext, window->frame, 0.0f);

        RENDER_SUBVIEWS(window->frameView, window->graphicsContext);

        UIRect contentViewFrame = {
            .x = 0,
            .y = window->frameView->frame.height,
            .width = window->frame.width,
            .height = window->frame.height - window->frameView->frame.height
        };

        UIGraphicsContextClipToRect(window->graphicsContext, contentViewFrame, 0.0f);
        RENDER_SUBVIEWS(rootView, window->graphicsContext);
        rootView->needsDisplay = 0;

        UIGraphicsContextFlush(window->graphicsContext);
    }
}