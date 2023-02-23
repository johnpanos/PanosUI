#include "UIAnimation.h"
#include "UILayer.h"
#include "UIView.h"
#include <stdio.h>

int main()
{
	UIRect rect = UIRectCreate(0, 0, 200, 200);
	UIView *view = UIViewCreate(rect, rect);
	// UILayer *layer = view->layer;

	// UILayerSetBounds(layer, UIRectCreate(0, 0, 20, 20));
	// UILayerSetPosition(layer, UIPointCreate(50, 50));

	// float startOpacity = 40.0f;
	// float endOpacity = 80.0f;
	// UIAnimation opacityAnim = {
	//     .forKey = kUILayerKeyOpacity,
	//     .startValue = &startOpacity,
	//     .endValue = &endOpacity,
	//     .startTime = UIAnimationGetCurrentTime(),
	//     .endTime = UIAnimationGetCurrentTime() + 2000,
	//     .duration = 2000};
	// ArrayAddValue(layer->animations, &opacityAnim);
}