#pragma once

#include "UIEvent.h"
#include "UIRect.h"
#include "UIView.h"

typedef struct _UIWindow
{
    const char *title;
    UIRect frame;
    UIView mainView;
} *UIWindow;

UIWindow UIWindowCreate(UIRect rect);
void UIWindowDestroy(UIWindow window);

void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);