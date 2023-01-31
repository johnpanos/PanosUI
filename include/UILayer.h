#ifndef _UILAYER_H
#define _UILAYER_H

#include "UIRect.h"

typedef struct _UILayer UILayer;

UILayer *UILayerCreate(UIRect frame, UIRect bounds);
void UILayerDestroy(UILayer *view);

#endif