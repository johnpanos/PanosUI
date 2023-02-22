#pragma once

#include "UIEvent.h"

typedef struct _UIEventResponder *UIEventResponder;

enum UIEventResponderCallback
{
	UIEventResponderLeftMouseDown = 0,
	UIEventResponderLeftMouseUp,
	UIEventResponderRightMouseDown,
	UIEventResponderRightMouseUp,
	UIEventResponderMouseMove,
	UIEventResponderMouseScroll
};

typedef struct _UIEventResponder
{
	void *_self;
	UIEventResponder next;

	void (*leftMouseDown)(UIEventResponder self, UIEvent event);
	void (*leftMouseUp)(UIEventResponder self, UIEvent event);

	void (*rightMouseDown)(UIEventResponder self, UIEvent event);
	void (*rightMouseUp)(UIEventResponder self, UIEvent event);

	void (*mouseMove)(UIEventResponder self, UIEvent event);

	void (*mouseScroll)(UIEventResponder self, UIEvent event);
} *UIEventResponder;

UIEventResponder UIEventResponderCreate();
void UIEventResponderSetCallback(UIEventResponder *responder, enum UIEventResponderCallback callback)
{
	int base = sizeof(void *) + sizeof(UIEventResponder *);
	void (*callbackFunc)(UIEventResponder * self, UIEvent event) =
		(void (*)(UIEventResponder * self, UIEvent event))(base + (sizeof(void *) * callback));
}
void UIEventResponderDestroy(UIEventResponder *responder);