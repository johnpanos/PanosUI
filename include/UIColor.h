#pragma once

typedef struct _UIColor {
    int r, g, b, a;
} UIColor;

UIColor UIColorCreateRGBA(int r, int g, int b, int a);