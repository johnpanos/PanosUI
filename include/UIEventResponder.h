#pragma once

#include "UIEvent.h"

enum UIEventResponderCallback
{
	UIEventResponderLeftMouseDown = 0,
	UIEventResponderLeftMouseUp,
	UIEventResponderRightMouseDown,
	UIEventResponderRightMouseUp,
	UIEventResponderMouseMove,
	UIEventResponderMouseScroll
};

typedef struct _UIEventResponder UIEventResponder;

UIEventResponder *UIEventResponderCreate();
void UIEventResponderDestroy(UIEventResponder *responder);