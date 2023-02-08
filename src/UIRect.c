#include "UIRect.h"

int UIPointInRect(UIPoint p, UIRect rect)
{
    if (p.x >= 0 && p.x <= rect.x + rect.width &&
        p.y >= 0 && p.y <= rect.y + rect.height)
    {
        return 1;
    }
    return 0;
}

UIRect UIRectOutset(UIRect orig, int left, int right, int top, int bottom)
{
    UIRect result = {orig.x - left, orig.y - top, orig.width + left + right, orig.height + top + bottom};
    return result;
}

UIRect UIRectInset(UIRect orig, int left, int right, int top, int bottom)
{
    UIRect result = {orig.x + left, orig.y + top, orig.width - left - right, orig.height - top - bottom};
    return result;
}