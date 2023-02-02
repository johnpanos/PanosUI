#ifndef _UIWINDOW_H
#define _UIWINDOW_H

#include "UIViewController.h"
#include "UIEvent.h"

typedef struct _UIWindow
{
    const char *title;
} UIWindow;

UIWindow *UIWindowCreate(UIRect rect);
void UIWindowDestroy(UIWindow *window);

void UIWindowSetTitle(UIWindow *window, const char *title);
void UIWindowSetRootViewController(UIWindow *window, UIViewController *viewController);
void UIWindowSendEvent(UIWindow *window, UIEvent *event);

#endif