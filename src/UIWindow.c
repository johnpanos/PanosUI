#include <stdlib.h>
#include "UIWindow.h"

UIView _UIWindowCreateFrameView(UIWindow window)
{
    UIRect titlebarFrame = {
        .x = 0, .y = 0, .width = window->frame.width, .height = 28};
    UIView titlebar = UIViewCreate(titlebarFrame, titlebarFrame);
    titlebar->borderColor = UIColorCreateRGBA(0, 0, 0, 21);
    titlebar->backgroundColor = UIColorCreateRGBA(255, 255, 255, 255);
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
    window->frameView = _UIWindowCreateFrameView(window);

    UIRect newFrame = frame;
    newFrame.height = newFrame.height + window->frameView->frame.height;

    window->frame = newFrame;
    window->mainView = UIViewCreate(frame, frame);
    window->mainView->clipToBounds = 1;
    window->graphicsContext = NULL;
    window->controller = UIWindowControllerGetDefault();

    return window;
}

void UIWindowShow(UIWindow window)
{
    window->controller->windowWillLoad(window);

    _UIPlatformWindowCreate(window);

    window->controller->windowDidLoad(window);
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
    if (window->_platformData != NULL)
    {
        _UIPlatformWindowSetTitle(window, title);
    }
}

void RENDER_SUBVIEWS(UIView view, UIGraphicsContext *context)
{
    if (view->needsLayout)
    {
        view->layoutSubviews(view);
        view->needsLayout = 0;
    }

    UIGraphicsContextSave(context);
    if (view->parentView != NULL)
    {
        UIGraphicsContextSetTransform(context, view->parentView->frame.x, view->parentView->frame.y);
    }
    UILayer layer = UILayerGetInFlight(*view->layer);
    UILayerRenderInContext(&layer, context);
    for (int i = 0; i < ArrayGetCapacity(view->subviews); i++)
    {
        UIView viewToRender = ArrayGetValueAtIndex(view->subviews, i);
        RENDER_SUBVIEWS(viewToRender, context);
    }
    UIGraphicsContextRestore(context);
}

void UIWindowUpdate(UIWindow window)
{
    UIView rootView = window->mainView;

    // if (rootView != NULL && rootView->needsDisplay)
    if (rootView != NULL)
    {
        UIGraphicsContextMakeCurrent(window->graphicsContext);

        // Draw dropshadow
        UIGraphicsContextSave(window->graphicsContext);
        {
            // UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(0, 0, 0, 31));
            // UIRect shadowOffset = {.x = 0, .y = 25, .width = 0, .height = 0};
            // UIGraphicsContextSetShadow(window->graphicsContext, shadowOffset, 30.0f);
            // UIGraphicsContextAddRect(window->graphicsContext, window->frame, 10.0f);
            // UIGraphicsContextRestore(window->graphicsContext);

            // Clip all children to inside
            UIGraphicsContextClipToRect(window->graphicsContext, window->frame, 10.0f);

            // Draw background
            UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(255, 255, 255, 255));
            UIGraphicsContextAddRect(window->graphicsContext, window->frame, 0.0f);

            RENDER_SUBVIEWS(window->frameView, window->graphicsContext);

            UIGraphicsContextSave(window->graphicsContext);
            {
                UIGraphicsContextSetTransform(window->graphicsContext, 0, 28);
                UIGraphicsContextClipToRect(window->graphicsContext, window->mainView->frame, 0.0f);
                RENDER_SUBVIEWS(rootView, window->graphicsContext);
                rootView->needsDisplay = 0;
            }
            UIGraphicsContextRestore(window->graphicsContext);
        }
        UIGraphicsContextRestore(window->graphicsContext);

        UIGraphicsContextFlush(window->graphicsContext);
    }
}

void UIWindowSendEvent(UIWindow window, UIEvent event)
{
    if (event.type == UIEventTypeMouseMotion)
    {
        window->mousePos.x = event._eventData.mouseMotion.x;
        window->mousePos.y = event._eventData.mouseMotion.y;

        UIPoint hitPoint = {
            .x = window->mousePos.x,
            .y = window->mousePos.y - 28};
        // UIView hitView = UIViewHitTest(window->mainView, hitPoint);
        // printf("Hit view: %p\n", hitView);
    }
    else if (event.type == UIEventTypeMouseDown)
    {
        if ((window->mousePos.x > 0 && window->mousePos.x < window->frame.width) &&
            (window->mousePos.y > 0 && window->mousePos.y < 28))
        {
            _UIPlatformWindowMove(window, event);
        }
        else if ((window->mousePos.x > window->frame.width - 8 &&
                  window->mousePos.x < window->frame.width) &&

                 (window->mousePos.y > window->frame.height-8 &&
                  window->mousePos.y < window->frame.height))
        {
            _UIPlatformWindowResize(window, event);
        }
        else
        {
            UIPoint hitPoint = {
                .x = window->mousePos.x,
                .y = window->mousePos.y - 28};
            // UIView hitView = UIViewHitTest(window->mainView, hitPoint);
            // printf("Hit view: %p\n", hitView);
        }
    }
}