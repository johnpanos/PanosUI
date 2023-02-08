#pragma once

#include <stdlib.h>

typedef struct _UIPoint {
    int x;
    int y;
} UIPoint;

typedef struct _UIRect
{
    int x, y;
    int width, height;
} UIRect;

UIRect UIRectOutset(UIRect orig, int left, int right, int top, int bottom);
UIRect UIRectInset(UIRect orig, int left, int right, int top, int bottom);