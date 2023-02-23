#pragma once

#include "UIApplication.h"
#include "UIEvent.h"
#include "UIEventResponder.h"
#include "UIGeometry.h"
#include "UIGraphicsContext.h"
#include "UIView.h"
#include "UIWindowController.h"
#include "include/UIWindow.h"

typedef struct _UIPlatformWindow UIPlatformWindow;
typedef struct _UIWindow
{
	unsigned int windowFlags;

	const char *title;
	UIRect frame;
	UIRect contentFrame;

	UIEventResponder *responder;

	UILayer *rootLayer;
	UIView *mainView;

	UIWindowController controller;
	UIPoint mousePos;

	UIView *frameView;

	UIGraphicsContext *graphicsContext;

	UIPlatformWindow *platformWindow;
} UIWindow;