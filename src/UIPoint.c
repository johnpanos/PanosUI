#include "UIGeometry.h"

UIPoint UIPointCreate(UIFloat x, UIFloat y)
{
    UIPoint p = {
        .x = x,
        .y = y};
    return p;
}

UIPoint UIPointOffset(UIPoint p, UIFloat dx, UIFloat dy) {
    UIPoint c = p;
    c.x += dx;
    c.y += dy;
    return c;
}

bool UIPointInRect(UIPoint p, UIRect r)
{
    if (p.x >= UIRectGetMinX(r) &&
        p.x <= UIRectGetMaxX(r) &&
        p.y >= UIRectGetMinY(r) &&
        p.y <= UIRectGetMaxY(r))
    {
        return true;
    }
    else
    {
        return false;
    }
}