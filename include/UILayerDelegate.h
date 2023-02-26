#pragma once

#include "UILayer.h"

typedef struct _UIGraphicsContext UIGraphicsContext;
typedef struct _UILayerDelegate
{
	void *_self;
	void (*drawLayer)(void *_self, UILayer *layer, UIGraphicsContext *ctx);
} UILayerDelegate;

UILayerDelegate *UILayerDelegateCreate();
void UILayerDelegateDestroy(UILayerDelegate *windowController);