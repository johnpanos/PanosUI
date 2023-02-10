#ifndef _UIRECT_H
#define _UIRECT_H
#include <stdlib.h>
#include "UIPoint.h"

typedef struct _UIRect
{
    int x, y;
    int width, height;
} UIRect;

UIRect UIRectCreate(int x, int y, int width, int height);
UIRect UIRectOutset(UIRect orig, int left, int right, int top, int bottom);
UIRect UIRectInset(UIRect orig, int left, int right, int top, int bottom);

#endif