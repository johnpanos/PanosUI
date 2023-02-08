#pragma once

#include "UIRect.h"
#include "UIGraphicsContext.h"

typedef struct _UILayer UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer *view);

void UILayerRenderInContext(UILayer *layer, UIGraphicsContext *context);