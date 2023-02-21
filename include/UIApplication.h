#ifndef _UIAPPLICATION_H
#define _UIAPPLICATION_H

typedef struct _UIApplication
{
	int running;
} UIApplication;

typedef struct _UIApplicationDelegate
{
	void (*didFinishLaunching)(UIApplication *application);
} UIApplicationDelegate;

void UIApplicationMain(UIApplicationDelegate *delegate);
UIApplication *UIApplicationShared();

#endif