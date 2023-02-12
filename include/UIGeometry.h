#pragma once

#include <stdbool.h>

#define UIFloat float

typedef struct _UIPoint
{
    UIFloat x, y;
} UIPoint;

typedef struct _UISize
{
    UIFloat width, height;
} UISize;

typedef struct _UIRect
{
    UIPoint origin;
    UISize size;
} UIRect;

// MARK: UIRect
UIRect UIRectCreate(UIFloat x, UIFloat y, UIFloat width, UIFloat height);
UIFloat UIRectGetWidth(UIRect r);
UIFloat UIRectGetHeight(UIRect r);
UIFloat UIRectGetMinX(UIRect r);
UIFloat UIRectGetMinY(UIRect r);
UIFloat UIRectGetMaxX(UIRect r);
UIFloat UIRectGetMaxY(UIRect r);
UIFloat UIRectGetMidX(UIRect r);
UIFloat UIRectGetMidY(UIRect r);
UIRect UIRectInset(UIRect r, UIFloat dx, UIFloat dy);
UIRect UIRectOutset(UIRect r, UIFloat dx, UIFloat dy);

// MARK: UIPoint
UIPoint UIPointCreate(UIFloat x, UIFloat y);
bool UIPointInRect(UIPoint p, UIRect r);