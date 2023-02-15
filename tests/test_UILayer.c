#include <stdio.h>
#include "UIView.h"
#include "UILayer.h"
#include "UIAnimation.h"

int main()
{
    UIRect rect = UIRectCreate(0, 0, 200, 200);
    UIView view = UIViewCreate(rect, rect);
    UILayer *layer = view->layer;

    // UILayerSetBounds(layer, UIRectCreate(0, 0, 20, 20));
    // UILayerSetPosition(layer, UIPointCreate(50, 50));
    
    printf("Frame: x(%f) y(%f) w(%f) h(%f)\n", 
        layer->frame.origin.x,
        layer->frame.origin.y,
        layer->frame.size.width,
        layer->frame.size.height);

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