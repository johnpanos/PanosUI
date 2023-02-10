#pragma once

#include "UIRect.h"

typedef struct _UIPoint {
    int x;
    int y;
} UIPoint;

UIPoint UIPointCreate(int x, int y);
int UIPointInRect(UIPoint p, UIRect rect);