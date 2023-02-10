#include "UILayer.h"
#include "UIAnimation.h"

int main()
{
    UIRect rect = UIRectCreate(0, 0, 200, 200);
    UILayer *layer = UILayerCreate(rect, rect);

    float startOpacity = 40.0f;
    float endOpacity = 80.0f;
    UIAnimation opacityAnim = {
        .forKey = kUILayerKeyOpacity,
        .startValue = &startOpacity,
        .endValue = &endOpacity,
        .startTime = UIAnimationGetCurrentTime(),
        .endTime = UIAnimationGetCurrentTime() + 2000,
        .duration = 2000};
    ArrayAddValue(layer->animations, &opacityAnim);
}