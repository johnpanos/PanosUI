#include "UIRect.h"

UIRect UIRectOutset(UIRect orig, int left, int right, int top, int bottom) {
    UIRect result = {orig.x - left, orig.y - top, orig.width + left + right, orig.height + top + bottom};
    return result;
}

UIRect UIRectInset(UIRect orig, int left, int right, int top, int bottom) {
    UIRect result = {orig.x + left, orig.y + top, orig.width - left - right, orig.height - top - bottom};
    return result;
}