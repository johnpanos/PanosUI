#include "PanosUI.h"
#include "UIGeometry.h"
#include "UIView.h"
#include <assert.h>

void TestConvertPoint() {
	
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

	return 0;
}