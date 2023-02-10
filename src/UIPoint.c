#include "UIPoint.h"

UIPoint UIPointCreate(int x, int y) {
    UIPoint p = {
        .x = x,
        .y = y
    };
    return p;
}