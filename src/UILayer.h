#pragma once

#include "shared/Array.h"
#include "UIRect.h"
#include "UIGraphicsContext.h"

const char* kUILayerKeyPositionX = "position.x";
const char* kUILayerKeyPositionY = "position.y";

const char* kUILayerKeyBoundsWidth = "bounds.width";
const char* kUILayerKeyBoundsHeight = "bounds.height";

const char* kUILayerKeyBackgroundColor = "backgroundColor";

const char* kUILayerKeyBorderWidth = "borderWidth";
const char* kUILayerKeyBorderColor = "borderColor";

const char* kUILayerKeyShadowOffset = "shadowOffset";
const char* kUILayerKeyShadowColor = "shadowColor";
const char* kUILayerKeyShadowRadius = "shadowRadius";

const char* kUILayerKeyOpacity = "opacity";

typedef struct _UILayer {
    Array animations;
    Array sublayers;

    UIColor backgroundColor;
    
    float borderWidth;
    UIColor borderColor;

    UIPoint shadowOffset;
    UIColor shadowColor;
    float shadowRadius;

    float opacity;
} *UILayer;

UILayer UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer layer);

void UILayerRenderInContext(UILayer layer, UIGraphicsContext *context);
UILayer UILayerGetInFlight(UILayer layer);

