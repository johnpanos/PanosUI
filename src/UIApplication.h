#pragma once

#include "UIWindow.h"
#include "include/Array.h"
#include "include/UIEvent.h"
#include "platform.h"

typedef struct _UIApplicationDelegate UIApplicationDelegate;
typedef struct _UIApplication
{
	int running;
	UIApplicationDelegate *delegate;

	Array windows;
} UIApplication;

typedef struct _UIApplicationDelegate
{
	void (*didFinishLaunching)(UIApplication *application);
} UIApplicationDelegate;

void UIApplicationMain(UIApplicationDelegate *delegate);
void UIApplicationRun();

UIApplication *UIApplicationShared();

void UIApplicationSendEvent(UIEvent event);