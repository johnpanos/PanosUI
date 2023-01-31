#ifndef _UIWINDOW_H
#define _UIWINDOW_H

#include "UIApplication.h"
#include "UIRect.h"
#include "UIEvent.h"

#include "platform.h"

typedef struct _UIViewController UIViewController;
typedef struct _UIWindow
{
    const char *title;
    UIRect frame;
    UIViewController *rootViewController;

    void *_platformData;
} UIWindow;

UIWindow *UIWindowCreate();
void UIWindowDestroy(UIWindow *window);

void UIWindowSetTitle(UIWindow *window, const char *title);
void UIWindowSetRootViewController(UIWindow *window, UIViewController *viewController);
void UIWindowSendEvent(UIWindow *window, UIEvent *event);

#endif