#ifndef _UIPLATFORM_H
#define _UIPLATFORM_H

typedef struct _UIWindow *UIWindow;
typedef struct _UIApplication UIApplication;

void _UIPlatformMain(UIApplication *application);
void _UIPlatformEventLoop(UIApplication *application);

void _UIPlatformWindowCreate(UIWindow window);
void _UIPlatformWindowDestroy(UIWindow window);

void _UIPlatformWindowSetTitle(UIWindow window, const char *title);
void _UIPlatformWindowRender(UIWindow window);

#endif