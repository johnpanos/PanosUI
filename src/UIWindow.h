#pragma once

#include "UIApplication.h"
#include "UIView.h"
#include "UIRect.h"
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

    UIView mainView;

    UIWindowController controller;
    UIPoint mousePos;

    UIGraphicsContext *graphicsContext;
    UIView frameView;
    
    UIPlatformWindow *platformWindow;
} *UIWindow;

UIWindow UIWindowCreate(UIRect frame);
void UIWindowDestroy(UIWindow window);

void UIWindowShow(UIWindow window);
void UIWindowUpdate(UIWindow window);
void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);
void UIWindowDoDrag(UIWindow window, UIEvent event);