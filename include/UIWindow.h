#pragma once

#include "UIEvent.h"
#include "UIRect.h"

typedef struct _UIWindow
{
    const char *title;
} *UIWindow;

UIWindow UIWindowCreate(UIRect rect);
void UIWindowDestroy(UIWindow window);

void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);