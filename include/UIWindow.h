#pragma once

#include "UIEvent.h"
#include "UIEventResponder.h"
#include "UIGeometry.h"

typedef struct _UIView *UIView;
typedef struct _UILayer UILayer;
typedef struct _UIWindowController *UIWindowController;
typedef struct _UIWindow
{
	const char *title;
	UIRect frame;
	UIRect contentFrame;

	UIEventResponder responder;

	UILayer *rootLayer;
	UIView mainView;

	UIWindowController controller;
	UIPoint mousePos;

	UIView frameView;
} *UIWindow;

UIWindow UIWindowCreate(UIRect rect);
void UIWindowDestroy(UIWindow window);

void UIWindowShow(UIWindow window);
void UIWindowSetTitle(UIWindow window, const char *title);
void UIWindowSendEvent(UIWindow window, UIEvent event);