#pragma once

typedef enum _UIEventType
{
	UIEventTypeMouseDown = 1,
	UIEventTypeMouseUp = 2,
	UIEventTypeMouseMotion = 3,
	UIEventTypeMouseDrag = 4,
	UIEventTypeMouseEntered = 5,
	UIEventTypeMouseScroll = 6,
	UIEventTypeKeyboardDown = 7,
	UIEventTypeKeyboardUp = 8
} UIEventType;

enum UIEventMouseButtonType
{
	UIEventMouseButtonTypeLeft = 0,
	UIEventMouseButtonTypeRight = 1
};

enum UIEventMouseButtonState
{
	UIEventMouseButtonUp = 0,
	UIEventMouseButtonDown = 1
};

enum UIEventMouseScrollType
{
	UIEventMouseScrollTypeDiscrete = 0,
	UIEventMouseScrollTypeContinuous = 1,
};

enum UIEventMouseScrollDirection
{
	UIEventMouseScrollDirectionVertical = 0,
	UIEventMouseScrollDirectionHorizontal = 1,
	UIEventMouseScrollDirectionBoth = 2
};

typedef struct _UIWindow *UIWindow;
typedef struct _UIEvent
{
	UIEventType type;
	int time;
	UIWindow window;

	union {
		struct
		{
			enum UIEventMouseButtonType button;
			enum UIEventMouseButtonState state;
		} mouseButton;

		struct
		{
			int x, y;
		} mouseMotion;

		struct
		{
			enum UIEventMouseScrollType type;
			enum UIEventMouseScrollDirection direction;

			int x, y;
		} mouseScroll;

		struct
		{
		} keyboard;
	} _eventData;

	int reserved;
} UIEvent;