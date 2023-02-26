/**
 * @file UILayer.c
 * @author John Panos
 * @brief UILayer
 * @version 1.0
 * @date 2023-02-21
 *
 *
 */

#include "UILayer.h"
#include "UIAnimation.h"
#include "include/UIColor.h"
#include "include/UILayerDelegate.h"
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_EQUAL(anim, str) strcmp(anim->forKey, str) == 0
#define VALUE_FOR_TYPE(anim, type, prop) *((type *)anim->prop)

const char *kUILayerKeyPositionX = "position.x";
const char *kUILayerKeyPositionY = "position.y";

const char *kUILayerKeyBoundsWidth = "bounds.width";
const char *kUILayerKeyBoundsHeight = "bounds.height";

const char *kUILayerKeyBackgroundColor = "backgroundColor";

const char *kUILayerKeyBorderWidth = "borderWidth";
const char *kUILayerKeyBorderColor = "borderColor";

const char *kUILayerKeyShadowOffset = "shadowOffset";
const char *kUILayerKeyShadowColor = "shadowColor";
const char *kUILayerKeyShadowRadius = "shadowRadius";

const char *kUILayerKeyCornerRadius = "cornerRadius";
const char *kUILayerKeyOpacity = "opacity";

float lerp(float a, float b, float t)
{
	return a + (t * (b - a));
}

void _UILayerUpdateFrame(UILayer *layer)
{
	UIRect frame = layer->bounds;
	frame.origin = UIPointOffset(layer->position, -(layer->bounds.size.width * layer->anchorPoint.x),
								 -(layer->bounds.size.height * layer->anchorPoint.y));
	layer->frame = frame;
}

void UILayerAddAnimation(UILayer *layer, UIAnimation anim)
{
	UIAnimation *copiedAnim = calloc(1, sizeof(UIAnimation));
	*copiedAnim = UIAnimationCopy(anim);
	ArrayAddValue(layer->animations, copiedAnim);
}

UIAnimation UILayerGetAnimationFor(UILayer *layer, const char *key, size_t valueSize, void *startValue, void *endValue)
{
	UIAnimation implicitAnim;
	implicitAnim.finished = 0;
	implicitAnim.forKey = key;
	implicitAnim.timingFunction = &UIAnimationTimingFunctionEaseInCubic;
	implicitAnim.startValue = startValue;
	implicitAnim.endValue = endValue;
	implicitAnim.startTime = UIAnimationGetCurrentTime();
	implicitAnim.endTime = UIAnimationGetCurrentTime();
	implicitAnim._valueSize = valueSize;
	implicitAnim.duration = 0;

	return UIAnimationCopy(implicitAnim);
}

UILayer *UILayerCreate(UIRect frame, UIRect bounds)
{
	printf("Creating layer w(%f) h(%f)\n", frame.size.width, frame.size.height);
	UILayer *layer = calloc(1, sizeof(UILayer));
	layer->animations = ArrayCreate(sizeof(UIAnimation *));
	layer->sublayers = ArrayCreate(sizeof(UILayer *));
	layer->shadowColor = UIColorCreateRGBA(0, 0, 0, 0);
	layer->backgroundColor = UIColorCreateRGBA(0, 0, 0, 0);

	layer->position = UIPointCreate(0.0f, 0.0f);
	layer->anchorPoint = UIPointCreate(0.5f, 0.5f);
	layer->bounds = UIRectCreate(0.0f, 0.0f, 0.0f, 0.0f);
	_UILayerUpdateFrame(layer);

	return layer;
}

UILayerDelegate UILayerGetDelegate(const UILayer *layer)
{
	return layer->delegate;
}
void UILayerSetDelegate(UILayer *layer, UILayerDelegate delegate)
{
	layer->delegate = delegate;
}

// frame
UIRect UILayerGetFrame(const UILayer *layer)
{
	return layer->frame;
}

// bounds
UIRect UILayerGetBounds(const UILayer *layer)
{
	return layer->bounds;
}
void UILayerSetBounds(UILayer *layer, UIRect bounds)
{
	UIAnimation anim = UILayerGetAnimationFor(layer, kUILayerKeyBoundsWidth, sizeof(UIFloat), &layer->bounds.size.width,
											  &bounds.size.width);
	UIAnimation animY = UILayerGetAnimationFor(layer, kUILayerKeyBoundsHeight, sizeof(UIFloat),
											   &layer->bounds.size.height, &bounds.size.height);
	layer->bounds = bounds;
	_UILayerUpdateFrame(layer);
	UILayerAddAnimation(layer, anim);
	UILayerAddAnimation(layer, animY);
}

// position
UIPoint UILayerGetPosition(const UILayer *layer)
{
	return layer->position;
}
void UILayerSetPosition(UILayer *layer, UIPoint position)
{
	UIAnimation anim =
		UILayerGetAnimationFor(layer, kUILayerKeyPositionX, sizeof(UIFloat), &layer->position.x, &position.x);
	UIAnimation animY =
		UILayerGetAnimationFor(layer, kUILayerKeyPositionX, sizeof(UIFloat), &layer->position.y, &position.y);
	layer->position = position;
	_UILayerUpdateFrame(layer);
	UILayerAddAnimation(layer, anim);
	UILayerAddAnimation(layer, animY);
}

// anchorPoint
UIPoint UILayerGetAnchorPoint(const UILayer *layer)
{
	return layer->anchorPoint;
}
void UILayerSetAnchorPoint(UILayer *layer, UIPoint anchorPoint)
{
	layer->anchorPoint = anchorPoint;
	_UILayerUpdateFrame(layer);
}

// backgroundColor
UIColor *UILayerGetBackgroundColor(const UILayer *layer)
{
	return layer->backgroundColor;
}
void UILayerSetBackgroundColor(UILayer *layer, UIColor *backgroundColor)
{
	layer->backgroundColor = backgroundColor;
}

// borderWidth
UIFloat UILayerGetBorderWidth(const UILayer *layer)
{
	return layer->borderWidth;
}
void UILayerSetBorderWidth(UILayer *layer, UIFloat borderWidth)
{
	layer->borderWidth = borderWidth;
}

// borderColor
UIColor *UILayerGetBorderColor(const UILayer *layer)
{
	return layer->borderColor;
}
void UILayerSetBorderColor(UILayer *layer, UIColor *borderColor)
{
	layer->borderColor = borderColor;
}

// shadowOffset
UIPoint UILayerGetShadowOffset(const UILayer *layer)
{
	return layer->shadowOffset;
}
void UILayerSetShadowOffset(UILayer *layer, UIPoint shadowOffset)
{
	layer->shadowOffset = shadowOffset;
}

// shadowColor
UIColor *UILayerGetShadowColor(const UILayer *layer)
{
	return layer->shadowColor;
}
void UILayerSetShadowColor(UILayer *layer, UIColor *shadowColor)
{
	layer->shadowColor = shadowColor;
}

// shadowRadius
UIFloat UILayerGetShadowRadius(const UILayer *layer)
{
	return layer->shadowRadius;
}
void UILayerSetShadowRadius(UILayer *layer, UIFloat shadowRadius)
{
	layer->shadowRadius = shadowRadius;
}

// opacity
UIFloat UILayerGetOpacity(const UILayer *layer)
{
	return layer->opacity;
}
void UILayerSetOpacity(UILayer *layer, UIFloat opacity)
{
	layer->opacity = opacity;
}

// cornerRadius
UIFloat UILayerGetCornerRadius(const UILayer *layer)
{
	return layer->cornerRadius;
}
void UILayerSetCornerRadius(UILayer *layer, UIFloat cornerRadius)
{
	layer->cornerRadius = cornerRadius;
}

// clipToBounds
bool UILayerGetClipToBounds(const UILayer *layer)
{
	return layer->clipToBounds;
}
void UILayerSetClipToBounds(UILayer *layer, bool clipToBounds)
{
	layer->clipToBounds = clipToBounds;
}

void UILayerAddSublayer(UILayer *layer, UILayer *sublayer)
{
	ArrayAddValue(layer->sublayers, sublayer);
	sublayer->parent = layer;
}

void UILayerRemoveSublayer(UILayer *layer, UILayer *sublayer)
{
	ArrayRemoveValueByRef(layer->sublayers, sublayer);
	sublayer->parent = NULL;
}

UILayer UILayerGetInFlight(UILayer *layer)
{
	UILayer copied = *layer;

	for (int i = 0; i < ArrayGetCapacity(copied.animations); i++)
	{
		UIAnimation *anim = ArrayGetValueAtIndex(copied.animations, i);

		uint64_t now = UIAnimationGetCurrentTime();
		int deltaT = now - anim->startTime;
		float prog = (UIFloat)deltaT / (UIFloat)anim->duration;
		float progress = anim->timingFunction(prog);

		if (prog >= 1)
		{
			progress = 1.0f;
			anim->finished = 1;
		}
		else if (prog <= 0)
		{
			progress = 0.0f;
			anim->finished = 0;
		}

		if (KEY_EQUAL(anim, kUILayerKeyBackgroundColor))
		{
			UIColor *bg = VALUE_FOR_TYPE(anim, UIColor *, startValue);
			copied.backgroundColor = bg;
		}
		else if (KEY_EQUAL(anim, kUILayerKeyBorderColor))
		{
			UIColor *bc = VALUE_FOR_TYPE(anim, UIColor *, startValue);
			copied.borderColor = bc;
		}
		else if (KEY_EQUAL(anim, kUILayerKeyBorderWidth))
		{
			float bw = VALUE_FOR_TYPE(anim, float, startValue);
			copied.borderWidth = bw;
		}
		else if (KEY_EQUAL(anim, kUILayerKeyBoundsWidth))
		{
			copied.bounds.size.width = (UIFloat)lerp(VALUE_FOR_TYPE(anim, UIFloat, startValue),
													 VALUE_FOR_TYPE(anim, UIFloat, endValue), progress);
		}
		else if (KEY_EQUAL(anim, kUILayerKeyBoundsHeight))
		{
			copied.bounds.size.height = (UIFloat)lerp(VALUE_FOR_TYPE(anim, UIFloat, startValue),
													  VALUE_FOR_TYPE(anim, UIFloat, endValue), progress);
		}

		else if (KEY_EQUAL(anim, kUILayerKeyOpacity))
		{
			copied.opacity =
				lerp(VALUE_FOR_TYPE(anim, float, startValue), VALUE_FOR_TYPE(anim, float, endValue), progress);
		}
		else if (KEY_EQUAL(anim, kUILayerKeyPositionX))
		{
			copied.position.x =
				lerp(VALUE_FOR_TYPE(anim, UIFloat, startValue), VALUE_FOR_TYPE(anim, UIFloat, endValue), progress);
		}
		else if (KEY_EQUAL(anim, kUILayerKeyPositionY))
		{
			copied.position.y =
				lerp(VALUE_FOR_TYPE(anim, UIFloat, startValue), VALUE_FOR_TYPE(anim, UIFloat, endValue), progress);
		}
		else if (KEY_EQUAL(anim, kUILayerKeyShadowColor))
		{
		}
		else if (KEY_EQUAL(anim, kUILayerKeyShadowOffset))
		{
			UIPoint startOffset = VALUE_FOR_TYPE(anim, UIPoint, startValue);
			UIPoint endOffset = VALUE_FOR_TYPE(anim, UIPoint, endValue);
			copied.shadowOffset.x = lerp(startOffset.x, endOffset.x, progress);
			copied.shadowOffset.y = lerp(startOffset.y, endOffset.y, progress);
		}
		else if (KEY_EQUAL(anim, kUILayerKeyShadowRadius))
		{
			copied.shadowRadius =
				lerp(VALUE_FOR_TYPE(anim, UIFloat, startValue), VALUE_FOR_TYPE(anim, UIFloat, endValue), progress);
		}
		else if (KEY_EQUAL(anim, kUILayerKeyCornerRadius))
		{
			copied.cornerRadius =
				lerp(VALUE_FOR_TYPE(anim, UIFloat, startValue), VALUE_FOR_TYPE(anim, UIFloat, endValue), progress);
		}
		else
		{
			printf("No animation serializer found for key: %s\n", anim->forKey);
		}
	}

	_UILayerUpdateFrame(&copied);

	Array animsToDelete = ArrayCreate(sizeof(UIAnimation *));
	for (int i = 0; i < ArrayGetCapacity(layer->animations); i++)
	{
		UIAnimation *anim = ArrayGetValueAtIndex(layer->animations, i);
		if (anim->finished)
		{
			ArrayAddValue(animsToDelete, anim);
		}
	}

	for (int i = 0; i < ArrayGetCapacity(animsToDelete); i++)
	{
		UIAnimation *anim = ArrayGetValueAtIndex(animsToDelete, i);
		ArrayRemoveValueByRef(layer->animations, anim);
		UIAnimationDestroy(*anim);
		free(anim);
	}
	ArrayDestroy(animsToDelete);

	return copied;
}

void UILayerRenderInContext(const UILayer *layer, UIGraphicsContext *context)
{
	UIGraphicsContextSave(context);
	{
		if (layer->clipToBounds)
		{
			UIGraphicsContextClipToRect(context, layer->bounds, layer->cornerRadius);
		}

		if (layer->shadowColor->a > 0)
		{
			UIGraphicsContextSave(context);
			{
				UIGraphicsContextSetShadow(context, layer->shadowOffset, layer->shadowRadius);
				UIGraphicsSetFillColor(context, layer->shadowColor);
				UIGraphicsContextAddRect(context, layer->bounds, layer->cornerRadius);
			}
			UIGraphicsContextRestore(context);
		}

		UIGraphicsSetFillColor(context, layer->backgroundColor);
		UIGraphicsContextAddRect(context, layer->bounds, layer->cornerRadius);

		if (layer->borderWidth > 0)
		{
			UIGraphicsSetStrokeColor(context, layer->borderColor);
			UIGraphicsSetStrokeWidth(context, layer->borderWidth);
			UIGraphicsContextAddRect(context, layer->bounds, layer->cornerRadius);
		}

		if (layer->delegate.drawLayer != NULL)
		{
			UIGraphicsContextSave(context);
			{
				layer->delegate.drawLayer((void*)layer->delegate._self, layer, context);
			}
			UIGraphicsContextRestore(context);
		}
	}
	UIGraphicsContextRestore(context);
}
