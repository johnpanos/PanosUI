#pragma once

typedef enum _UIEventType
{
    UIEventMouseDown = 1,
    UIEventMouseUp = 2,
    UIEventMouseMotion = 3,
    UIEventMouseDrag = 4,
    UIEventMouseEntered = 5,
    UIEventMouseLeft = 6,
    UIEventMouseScroll = 7,
    UIEventKeyboardDown = 8,
} UIEventType;

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
    UIEventMouseScrolLDirectionBoth = 2
};

typedef struct _UIWindow *UIWindow;
typedef struct _UIEvent
{
    UIEventType type;
    int time;
    UIWindow window;

    union
    {
        struct
        {
            int button;
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
} UIEvent;