#pragma once

#include "UIWindow.h"
#include "platform.h"

typedef struct _UIApplicationDelegate* UIApplicationDelegate_t;
typedef struct _UIApplication* UIApplication_t;

struct _UIApplication
{
    int running;
    UIWindow *window;
    UIApplication_t delegate;
};

struct _UIApplicationDelegate
{
    void (*didFinishLaunching)(UIApplication_t application);
};

void UIApplicationMain(UIApplicationDelegate_t delegate);
void UIApplicationRun();
UIApplication_t UIApplicationShared();