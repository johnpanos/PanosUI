#pragma once

#include "UIApplication.h"
#include "UIEvent.h"
#include "UIEventResponder.h"
#include "UIGeometry.h"
#include "UIGraphicsContext.h"
#include "UIView.h"
#include "UIWindowController.h"

enum UIWindowType
{
	UIWindowTypeBorderless = 1 << 0,
	UIWindowTypeTitlebar = 1 << 1,
	UIWindowTypeHasClose = 1 << 2,
	UIWindowTypeHasHide = 1 << 3,
	UIWindowTypeHasResize = 1 << 4,
	UIWindowTypeShell = 1 << 5
};

typedef struct _UIPlatformWindow UIPlatformWindow;
typedef struct _UIWindow
{
	unsigned int windowFlags;

	const char *title;
	UIRect frame;
	UIRect contentFrame;

	UIEventResponder responder;

	UILayer *rootLayer;
	UIView mainView;

	UIWindowController controller;
	UIPoint mousePos;

	UIView frameView;

	UIGraphicsContext *graphicsContext;

	UIPlatformWindow *platformWindow;
} *UIWindow;

UIWindow UIWindowCreate(UIRect frame);
UIWindow UIWindowCreateWithFlags(UIRect frame, unsigned int flags);

void UIWindowDestroy(UIWindow window);

void UIWindowShow(UIWindow window);
void UIWindowUpdate(UIWindow window);
void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);
void UIWindowDoDrag(UIWindow window, UIEvent event);