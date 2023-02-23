#ifndef _UIPLATFORM_H
#define _UIPLATFORM_H

typedef struct _UIWindow UIWindow;
typedef struct _UILayer UILayer;
typedef struct _UIEvent UIEvent;
typedef struct _UIApplication UIApplication;
typedef struct _UIPlatformLayer UIPlatformLayer;

void _UIPlatformMain(UIApplication *application);
void _UIPlatformEventLoop(UIApplication *application);

void _UIPlatformWindowCreate(UIWindow *window);
void _UIPlatformWindowDestroy(UIWindow *window);

// MARK: Platform Layer
UIPlatformLayer *_UIPlatformLayerCreate();
void _UIPlatformLayerDestroy(UILayer *layer);
void _UIPlatformLayerAddAnimation(UILayer *layer);

void _UIPlatformWindowSetTitle(UIWindow *window, const char *title);
void _UIPlatformWindowMove(UIWindow *window, UIEvent event);
void _UIPlatformWindowResize(UIWindow *window, UIEvent event);
void _UIPlatformWindowMakeCurrent(UIWindow *window);
void _UIPlatformWindowFlush(UIWindow *window);

#endif