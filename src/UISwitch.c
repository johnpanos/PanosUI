#include "UISwitch.h"
#include "include/UIAnimation.h"
#include "include/UIColor.h"
#include "include/UIGeometry.h"
#include "include/UIView.h"

void _UISwitchDoNothing(UIView *view)
{
	view->needsLayout = 0;
}

void onSwitchClick(UIEventResponder *self, UIEvent event)
{
	UISwitch *s = (UISwitch *)self->_self;
	UIFloat start, end;

	if (s->enabled)
	{
		start = 19.0f + 10;
		end = 1.0f + 10;
		s->enabled = false;
	}
	else
	{
		start = 1.0f + 10;
		end = 19.0f + 10;
		s->enabled = true;
	}

	UIAnimation radiusAnim;
	radiusAnim.finished = 0;
	radiusAnim.forKey = kUILayerKeyPositionX;
	radiusAnim.timingFunction = &UIAnimationTimingFunctionEaseInOutCubic;
	radiusAnim.startValue = &start;
	radiusAnim.endValue = &end;
	radiusAnim.startTime = UIAnimationGetCurrentTime();
	radiusAnim.endTime = UIAnimationGetCurrentTime() + 250;
	radiusAnim._valueSize = sizeof(UIFloat);
	radiusAnim.duration = 250;
	UILayerAddAnimation(UIViewGetLayer(s->toggleView), radiusAnim);
}

UISwitch *UISwitchCreate(UIRect frame)
{
	UIRect switchFrame = {.origin = frame.origin, .size = {.width = 40, .height = 22}};
	UISwitch *uiswitch = calloc(1, sizeof(UISwitch));
	uiswitch->enabled = true;
	uiswitch->base.layer = UILayerCreate(switchFrame, switchFrame);

	uiswitch->base.responder = UIEventResponderCreate();
	uiswitch->base.responder->_self = uiswitch;
	uiswitch->base.responder->leftMouseDown = &onSwitchClick;
	UIViewSetFrame((UIView *)uiswitch, switchFrame);

	UIRect boundsCopy = switchFrame;
	boundsCopy.origin.x = 0;
	boundsCopy.origin.y = 0;

	UIViewSetBounds((UIView *)uiswitch, boundsCopy);
	uiswitch->base.subviews = ArrayCreate(sizeof(UIView *));
	uiswitch->base.needsDisplay = 1;
	uiswitch->base.needsLayout = 1;
	uiswitch->base.layoutSubviews = &_UISwitchDoNothing;

	UIViewSetBackgroundColor((UIView *)uiswitch, UIColorCreateRGBA(0, 122, 255, 255));
	UIViewSetCornerRadius((UIView *)uiswitch, switchFrame.size.height);

	UIViewSetBorderColor(uiswitch, UIColorCreateRGBA(0, 0, 0, 255 / 12));
	UIViewSetBorderWidth(uiswitch, 0.5f);

	UIRect cRect = UIRectCreate(19, 1, 20, 20);
	UIView *circle = UIViewCreate(cRect, cRect);

	UIViewSetBackgroundColor(circle, UIColorCreateRGBA(255, 255, 255, 255));
	UIViewSetCornerRadius(circle, 20.0f);

	UIViewSetShadowColor(circle, UIColorCreateRGBA(0, 0, 0, 255 / 20));
	UIViewSetShadowOffset(circle, UIPointCreate(0, 0.5f));
	UIViewSetShadowRadius(circle, 4);

	UIViewAddSubview(uiswitch, circle);

	uiswitch->toggleView = circle;

	return uiswitch;
}

bool UISwitchGetEnabled(UISwitch *uiswitch)
{
	return uiswitch->enabled;
}
void UISwitchSetEnabled(UISwitch *uiswitch, bool enabled)
{
	uiswitch->enabled = enabled;
}