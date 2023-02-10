#include "UIPoint.h"
#include "UIRect.h"

UIPoint UIPointCreate(int x, int y) {
    UIPoint p = {
        .x = x,
        .y = y
    };
    return p;
}

int UIPointInRect(UIPoint p, UIRect rect)
{
    if (p.x >= 0 && p.x <= rect.x + rect.width &&
        p.y >= 0 && p.y <= rect.y + rect.height)
    {
        return 1;
    }
    return 0;
}