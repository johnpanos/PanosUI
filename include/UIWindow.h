#pragma once

#include "UIEvent.h"
#include "UIRect.h"

typedef struct _UIView *UIView;
typedef struct _UIWindowController *UIWindowController;
typedef struct _UIWindow
{
    const char *title;
    UIRect frame;
    UIRect contentFrame;

    UIView mainView;

    UIWindowController controller;
    UIRect mousePos;
} *UIWindow;

UIWindow UIWindowCreate(UIRect rect);
void UIWindowDestroy(UIWindow window);

void UIWindowShow(UIWindow window);
void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);