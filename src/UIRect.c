#include "UIGeometry.h"

UIRect UIRectCreate(UIFloat x, UIFloat y, UIFloat width, UIFloat height)
{
	UIPoint origin = UIPointCreate(x, y);
	UISize size = {.width = width, .height = height};

	UIRect r = {.origin = origin, .size = size};

	return r;
}

UIFloat UIRectGetWidth(UIRect r)
{
	return r.size.width;
}
UIFloat UIRectGetHeight(UIRect r)
{
	return r.size.height;
}

UIFloat UIRectGetMinX(UIRect r)
{
	return r.origin.x;
}
UIFloat UIRectGetMinY(UIRect r)
{
	return r.origin.y;
}

UIFloat UIRectGetMaxX(UIRect r)
{
	return UIRectGetMinX(r) + r.size.width;
}
UIFloat UIRectGetMaxY(UIRect r)
{
	return UIRectGetMinY(r) + r.size.height;
}

UIFloat UIRectGetMidX(UIRect r)
{
	return ((UIRectGetMaxX(r) - UIRectGetMinX(r)) / 2.0f) + UIRectGetMinX(r);
}
UIFloat UIRectGetMidY(UIRect r)
{
	return ((UIRectGetMaxY(r) - UIRectGetMinY(r)) / 2.0f) + UIRectGetMinY(r);
}

UIRect UIRectInset(UIRect r, UIFloat dx, UIFloat dy)
{
	UIRect i = r;

	i.origin.x += dx;
	i.origin.y += dy;

	i.size.width -= (2.0f * dx);
	i.size.height -= (2.0f * dy);

	return i;
}

UIRect UIRectOutset(UIRect r, UIFloat dx, UIFloat dy)
{
	return UIRectInset(r, -dx, -dy);
}