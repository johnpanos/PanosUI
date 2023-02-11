#include <stdlib.h>
#include "UIWindow.h"

UIView _UIWindowCreateFrameView(UIWindow window)
{
    UIRect titlebarFrame = {
        .x = 8, .y = 8, .width = window->frame.width, .height = 28};
    UIView titlebar = UIViewCreate(titlebarFrame, titlebarFrame);
    UIViewSetBackgroundColor(titlebar, UIColorCreateRGBA(255, 255, 255, 255));
    UIViewSetCornerRadius(titlebar, 0.0f);

    UIViewSetBorderColor(titlebar, UIColorCreateRGBA(0, 0, 0, 50));
    UIViewSetBorderWidth(titlebar, 0.0f);

    UIRect redFrame = {.x = 8, .y = 8, .width = 16, .height = 16};
    UIColor red = {.r = 120, .g = 27, .b = 112, .a = 255};
    UIView redLight = UIViewCreate(redFrame, redFrame);
    UIViewSetCornerRadius(redLight, 12);
    UIViewSetBackgroundColor(redLight, red);
    UIViewSetBorderColor(redLight, UIColorCreateRGBA(0, 0, 0, 21));
    UIViewSetBorderWidth(redLight, 0.5f);

    UIRect yellowFrame = {.x = 8 + 24, .y = 8, .width = 16, .height = 16};
    UIColor yellow = {.r = 120, .g = 27, .b = 112, .a = 100};
    UIView yellowLight = UIViewCreate(yellowFrame, yellowFrame);
    UIViewSetCornerRadius(yellowLight, 12);
    UIViewSetBackgroundColor(yellowLight, yellow);
    UIViewSetBorderColor(yellowLight, UIColorCreateRGBA(0, 0, 0, 21));
    UIViewSetBorderWidth(yellowLight, 0.5f);

    UIRect greenFrame = {.x = 8 + 48, .y = 8, .width = 16, .height = 16};
    UIColor green = {.r = 120, .g = 27, .b = 112, .a = 100};
    UIView greenLight = UIViewCreate(greenFrame, greenFrame);
    UIViewSetCornerRadius(greenLight, 12);
    UIViewSetBackgroundColor(greenLight, green);
    UIViewSetBorderColor(greenLight, UIColorCreateRGBA(0, 0, 0, 21));
    UIViewSetBorderWidth(greenLight, 0.5f);

    UIViewAddSubview(titlebar, redLight);
    UIViewAddSubview(titlebar, yellowLight);
    UIViewAddSubview(titlebar, greenLight);

    titlebar->needsDisplay = 1;

    return titlebar;
}

#define INSET_AMOUNT 16
UIWindow UIWindowCreate(UIRect frame)
{
    UIWindow window = calloc(1, sizeof(struct _UIWindow));

    window->responder = UIEventResponderCreate();

    ArrayAddValue(UIApplicationShared()->windows, window);

    window->frame = UIRectOutset(frame, INSET_AMOUNT, INSET_AMOUNT, INSET_AMOUNT, INSET_AMOUNT);
    window->frame.x = 0;
    window->frame.y = 0;
    window->contentFrame = UIRectInset(window->frame, INSET_AMOUNT, INSET_AMOUNT, INSET_AMOUNT, INSET_AMOUNT);
    window->graphicsContext = NULL;
    window->controller = UIWindowControllerGetDefault();

    return window;
}

void UIWindowShow(UIWindow window)
{
    window->controller->windowWillLoad(window);

    _UIPlatformWindowCreate(window);
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
    if (window->platformWindow != NULL)
    {
        _UIPlatformWindowSetTitle(window, title);
    }
}

void RENDER_SUBVIEWS(UIView view, UIGraphicsContext *context)
{
    UIGraphicsContextSave(context);
    if (view->parentView != NULL)
    {
        UIGraphicsContextSetTransform(context, view->parentView->frame.x, view->parentView->frame.y);
    }
    UILayer layer = UILayerGetInFlight(*view->layer);
    UILayerRenderInContext(&layer, context);
    ArrayForEach(UIView viewToRender, view->subviews)
    {
        RENDER_SUBVIEWS(viewToRender, context);
    }
    UIGraphicsContextRestore(context);
}

void _UIWindowLayoutPhase_UIViewLayout(UIView viewToLayout)
{
    if (viewToLayout->needsLayout)
    {
        viewToLayout->layoutSubviews(viewToLayout);
    }

    ArrayForEach(UIView child, viewToLayout->subviews)
    {
        _UIWindowLayoutPhase_UIViewLayout(child);
    }
}

int _UIWindowRenderPhase_ShouldRender(UIView view)
{
    if (ArrayGetCapacity(view->layer->animations) > 0 || view->needsDisplay)
    {
        view->needsDisplay = 0;
        return 1;
    }

    else
    {
        ArrayForEach(UIView child, view->subviews)
        {
            if (_UIWindowRenderPhase_ShouldRender(child) || child->needsDisplay)
            {
                child->needsDisplay = 0;
                return 1;
            }
        }
    }

    return 0;
}

void UIWindowUpdate(UIWindow window)
{
    // UIGraphicsContextMakeCurrent(window->graphicsContext);
    // UIGraphicsContextClear(window->graphicsContext);
    // UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(0, 0, 0, 255));
    // UIGraphicsContextAddRect(window->graphicsContext, window->frame, 0.0f);
    // UIGraphicsContextFlush(window->graphicsContext);
    return;
    UIView rootView = window->mainView;

    _UIWindowLayoutPhase_UIViewLayout(rootView);

    int shouldRender = _UIWindowRenderPhase_ShouldRender(rootView);

    if (shouldRender)
    {
        // printf("Should render: %d\n", shouldRender);
        UIGraphicsContextMakeCurrent(window->graphicsContext);
        UIGraphicsContextClear(window->graphicsContext);

        // Draw dropshadow
        UIGraphicsContextSave(window->graphicsContext);
        {
            UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(0, 0, 0, 42));
            UIGraphicsContextSetShadow(window->graphicsContext, UIPointCreate(0, 0), 12.0f);
            UIGraphicsContextAddRect(window->graphicsContext, window->contentFrame, 8.0f);
            UIGraphicsContextRestore(window->graphicsContext);

            // Clip all children to inside
            UIGraphicsContextClipToRect(window->graphicsContext, window->contentFrame, 8.0f);

            // Draw background
            UIGraphicsSetFillColor(window->graphicsContext, UIColorCreateRGBA(255, 255, 255, 255));
            UIGraphicsContextAddRect(window->graphicsContext, window->contentFrame, 8.0f);

            UIGraphicsContextSave(window->graphicsContext);
            {
                UIGraphicsContextSetTransform(window->graphicsContext, window->contentFrame.x, window->contentFrame.y);
                UIGraphicsContextClipToRect(window->graphicsContext, window->mainView->frame, 0.0f);
                RENDER_SUBVIEWS(rootView, window->graphicsContext);

                RENDER_SUBVIEWS(window->frameView, window->graphicsContext);
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
        window->mousePos.x = event._eventData.mouseMotion.x - window->contentFrame.x;
        window->mousePos.y = event._eventData.mouseMotion.y - window->contentFrame.y;
    }

    UIRect dragger = UIRectCreate(
        window->contentFrame.width,
        window->contentFrame.height,
        0,
        0);
    dragger = UIRectOutset(dragger, 10, 10, 10, 10);

    if ((window->mousePos.x > 0 && window->mousePos.x < window->frame.width) &&
        (window->mousePos.y > 0 && window->mousePos.y < 28))
    {
        _UIPlatformWindowMove(window, event);
    }
    else if (UIPointInRect(window->mousePos, dragger))
    {
        _UIPlatformWindowResize(window, event);
    }
    else
    {
        UIPoint hitPoint = {
            .x = window->mousePos.x,
            .y = window->mousePos.y};
        UIView hitView = UIViewHitTest(window->mainView, hitPoint);
        switch (event.type)
        {
        case UIEventTypeMouseDown:
            if (event._eventData.mouseButton.button == UIEventMouseButtonTypeLeft)
            {
                hitView->responder->leftMouseDown(
                    hitView->responder,
                    event);
            }
            else if (event._eventData.mouseButton.button == UIEventMouseButtonTypeRight)
            {
                hitView->responder->rightMouseDown(
                    hitView->responder,
                    event);
            }
            break;
        case UIEventTypeMouseUp:
            if (event._eventData.mouseButton.button == UIEventMouseButtonTypeLeft)
            {
                hitView->responder->leftMouseUp(
                    hitView->responder,
                    event);
            }
            else if (event._eventData.mouseButton.button == UIEventMouseButtonTypeRight)
            {
                hitView->responder->rightMouseUp(
                    hitView->responder,
                    event);
            }
            break;
        case UIEventTypeMouseMotion:
            hitView->responder->mouseMove(
                hitView->responder,
                event);
            break;
        };
    }
}