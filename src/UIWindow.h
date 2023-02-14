#pragma once

#include "UIApplication.h"
#include "UIView.h"
#include "UIGeometry.h"
#include "UIEvent.h"
#include "UIEventResponder.h"
#include "UIWindowController.h"
#include "UIGraphicsContext.h"

typedef struct _UIPlatformWindow UIPlatformWindow;
typedef struct _UIWindow
{
    const char *title;
    UIRect frame;
    UIRect contentFrame;

    UIEventResponder responder;

    UILayer *rootLayer;
    UIView mainView;

    UIWindowController controller;
    UIPoint mousePos;

    UIView frameView;

    UIGraphicsContext *graphicsContext;

    UIPlatformWindow *platformWindow;
} *UIWindow;

UIWindow UIWindowCreate(UIRect frame);
void UIWindowDestroy(UIWindow window);

void UIWindowShow(UIWindow window);
void UIWindowUpdate(UIWindow window);
void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);
void UIWindowDoDrag(UIWindow window, UIEvent event);