#include <stdio.h>

typedef struct UIPoint
{
    float x, y;
} UIPoint;

typedef struct UISize
{
    float width, height;
} UISize;

typedef struct UIRect
{
    UIPoint origin;
    UISize size;
} UIRect;

float UIRectGetWidth(UIRect r)
{
    return r.size.width;
}
float UIRectGetHeight(UIRect r)
{
    return r.size.height;
}

float UIRectGetMinX(UIRect r)
{
    return r.origin.x;
}
float UIRectGetMinY(UIRect r)
{
    return r.origin.y;
}

float UIRectGetMaxX(UIRect r)
{
    return UIRectGetMinX(r) + r.size.width;
}
float UIRectGetMaxY(UIRect r)
{
    return UIRectGetMinY(r) + r.size.height;
}

float UIRectGetMidX(UIRect r)
{
    return ((UIRectGetMaxX(r) - UIRectGetMinX(r)) / 2.0f) + UIRectGetMinX(r);
}
float UIRectGetMidY(UIRect r)
{
    return ((UIRectGetMaxY(r) - UIRectGetMinY(r)) / 2.0f) + UIRectGetMinY(r);
}

UIRect UIRectInset(UIRect r, float dx, float dy) {
    UIRect i = r;

    i.origin.x += dx;
    i.origin.y += dy;

    i.size.width -= (2.0f * dx);
    i.size.height -= (2.0f * dy);

    return i;
}

UIRect UIRectOutset(UIRect r, float dx, float dy) {
    return UIRectInset(r, -dx, -dy);
}

UIRect UIRectMake(float x, float y, float width, float height) {
    UIPoint origin = {
        .x = x,
        .y = y
    };
    UISize size = {
        .width = width,
        .height = height
    };

    UIRect r = {
        .origin = origin,
        .size = size
    };

    return r;
}

void printRect(UIRect r) {
    printf("====== ORIGIN ======\n");
    printf("x(%f) y(%f)\n", UIRectGetMinX(r), UIRectGetMinY(r));

    printf("=== BOTTOM RIGHT ===\n");
    printf("x(%f) y(%f)\n", UIRectGetMaxX(r), UIRectGetMaxY(r));

    printf("====== CENTER ======\n");
    printf("x(%f) y(%f)\n\n", UIRectGetMidX(r), UIRectGetMidY(r));
}

int main() {
    UIRect r = UIRectMake(10.0f, 10.0f, 200.0f, 40.0f);
    printRect(r);
    UIRect inset = UIRectInset(r, 25, 25);
    UIRect outset = UIRectOutset(inset, 25, 25);

    printRect(inset);
    printRect(outset);
}

// typedef struct UILayer
// {
//     UIPoint position;
//     UIPoint anchorPoint;
// } UILayer;