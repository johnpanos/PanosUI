#include "PanosUI.h"
#include "UIGeometry.h"
#include "UIView.h"
#include <assert.h>
#include <stdio.h>

void TestHitTest()
{
	UIRect rv1 = UIRectCreate(0, 0, 100, 100);
	UIView *v1 = UIViewCreate(rv1, rv1);

	UIRect rv2 = UIRectCreate(10, 10, 100, 100);
	UIView *v2 = UIViewCreate(rv2, rv2);

	UIRect rv3 = UIRectCreate(50, 50, 100, 100);
	UIView *v3 = UIViewCreate(rv3, rv3);

	UIViewAddSubview(v1, v2);
	UIViewAddSubview(v2, v3);

	// Should land in v3
	UIPoint pointToHitTest = UIPointCreate(70, 70);
	UIView *hitView = UIViewHitTest(v1, pointToHitTest);

	assert(hitView == v3);
}

void TestConvertPointMultiple()
{
	UIRect rv1 = UIRectCreate(0, 0, 100, 100);
	UIView *v1 = UIViewCreate(rv1, rv1);

	UIRect rv2 = UIRectCreate(10, 10, 100, 100);
	UIView *v2 = UIViewCreate(rv2, rv2);

	UIRect rv3 = UIRectCreate(50, 50, 100, 100);
	UIView *v3 = UIViewCreate(rv3, rv3);

	UIViewAddSubview(v1, v2);
	UIViewAddSubview(v2, v3);

	UIPoint converted = UIViewConvertPoint(v1, v3, UIPointCreate(60, 60));

	printf("%f %f\n", converted.x, converted.y);

	assert(converted.x == 0.0);
	assert(converted.y == 0.0);

	UIViewDestroy(v1);
	UIViewDestroy(v2);
	UIViewDestroy(v3);
}

void TestConvertPoint()
{
	UIRect rv1 = UIRectCreate(50, 50, 128, 128);
	UIView *v1 = UIViewCreate(rv1, rv1);
	UIRect rv2 = UIRectCreate(200, 200, 128, 128);
	UIView *v2 = UIViewCreate(rv2, rv2);

	UIViewAddSubview(v1, v2);

	UIPoint toConvert = UIPointCreate(10, 10);
	UIPoint converted = UIViewConvertPoint(v1, v2, toConvert);

	printf("%f %f\n", converted.x, converted.y);

	assert(converted.x == -140.0);
	assert(converted.y == -140.0);

	UIViewDestroy(v1);
	UIViewDestroy(v2);
}

int main()
{
	UIRect rect = UIRectCreate(0, 0, 250, 250);

	UIView *v1 = UIViewCreate(rect, rect);
	UIRect v1Frame = UIViewGetFrame(v1);
	assert(v1 != NULL);
	assert(v1Frame.origin.x == rect.origin.x);
	assert(v1Frame.origin.y == rect.origin.y);
	assert(v1Frame.size.width == rect.size.width);
	assert(v1Frame.size.height == rect.size.height);

	UIView *v2 = UIViewCreate(rect, rect);
	UIRect v2Frame = UIViewGetFrame(v2);
	assert(v2 != NULL);
	assert(v2Frame.origin.x == rect.origin.x);
	assert(v2Frame.origin.y == rect.origin.y);
	assert(v2Frame.size.width == rect.size.width);
	assert(v2Frame.size.height == rect.size.height);

	UIViewAddSubview(v1, v2);
	// assert(UIViewGetParentView(v2) == v1);

	UIView *v3 = UIViewCreate(rect, rect);
	UIViewAddSubview(v1, v3);

	UIViewRemoveSubview(v1, v3);
	// assert(UIViewGetParentView(v3) == NULL);

	UIViewDestroy(v1);
	// assert(UIViewGetParentView(v2) == NULL);

	TestConvertPoint();
	TestConvertPointMultiple();

	TestHitTest();

	return 0;
}