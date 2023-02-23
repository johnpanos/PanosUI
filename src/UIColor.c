#include "UIColor.h"
#include <stdlib.h>

UIColor *UIColorCreateRGBA(int r, int g, int b, int a)
{
	UIColor *color = calloc(1, sizeof(UIColor));
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
	return color;
}

void UIColorDestroy(UIColor *color) {
	free(color);
}