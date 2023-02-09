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
    printf("Start: %ul\n", opacityAnim.startTime);
    printf("End: %ul\n", opacityAnim.endTime);

    UILayer copy = UILayerGetInFlight(*layer);
    printf("Color r(%d) g(%d) b(%d) a(%d)\n",
           copy.backgroundColor.r,
           copy.backgroundColor.g,
           copy.backgroundColor.b,
           copy.backgroundColor.a);
    printf("Opacity %f\n", copy.opacity);

    sleep(1);

    copy = UILayerGetInFlight(*layer);
    printf("Opacity %f\n", copy.opacity);
}