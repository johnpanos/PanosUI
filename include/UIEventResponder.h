#pragma once

#include "UIEvent.h"

typedef struct _UIEventResponder *UIEventResponder;
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
void UIEventResponderDestroy(UIEventResponder *responder);