#ifndef _UIWINDOW_H
#define _UIWINDOW_H

#include "UIApplication.h"
#include "UIView.h"
#include "UIRect.h"
#include "UIEvent.h"
#include "UIWindowController.h"
#include "UIGraphicsContext.h"

typedef struct _UIWindow
{
    const char *title;
    UIRect frame;
    UIView mainView;

    UIWindowController controller;

    UIGraphicsContext *graphicsContext;

    UIView frameView;

    void *_platformData;
} *UIWindow;

UIWindow UIWindowCreate(UIRect frame);
void UIWindowDestroy(UIWindow window);

void UIWindowShow(UIWindow window);
void UIWindowUpdate(UIWindow window);
void UIWindowSetTitle(UIWindow window, const char *title);
// void UIWindowSetWindowController(UIWindow window, UIWindowController windowController);
void UIWindowSendEvent(UIWindow window, UIEvent event);

#endif