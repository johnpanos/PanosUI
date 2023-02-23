#pragma once

#include "UIEvent.h"
#include "include/UIEventResponder.h"

typedef struct _UIEventResponder
{
	void *_self;
	UIEventResponder *next;

	void (*leftMouseDown)(UIEventResponder *self, UIEvent event);
	void (*leftMouseUp)(UIEventResponder *self, UIEvent event);

	void (*rightMouseDown)(UIEventResponder *self, UIEvent event);
	void (*rightMouseUp)(UIEventResponder *self, UIEvent event);

	void (*mouseMove)(UIEventResponder *self, UIEvent event);

	void (*mouseScroll)(UIEventResponder *self, UIEvent event);
} UIEventResponder;