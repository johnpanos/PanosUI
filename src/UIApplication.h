#ifndef _UIAPPLICATION_H
#define _UIAPPLICATION_H

#include "UIWindow.h"
#include "platform.h"

typedef struct _UIApplicationDelegate UIApplicationDelegate;
typedef struct _UIApplication
{
    int running;
    UIWindow *window;
    UIApplicationDelegate *delegate;
} UIApplication;

typedef struct _UIApplicationDelegate
{
    void (*didFinishLaunching)(UIApplication *application);
} UIApplicationDelegate;

void UIApplicationMain(UIApplicationDelegate *delegate);
void UIApplicationRun();
UIApplication *UIApplicationShared();

#endif