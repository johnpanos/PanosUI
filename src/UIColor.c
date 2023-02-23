#include "UIColor.h"

UIColor *UIColorCreateRGBA(int r, int g, int b, int a)
{
	UIColor color = {.r = r, .g = g, .b = b, .a = a};
	return color;
}