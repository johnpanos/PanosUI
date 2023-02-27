#pragma once

#include "UIColor.h"
#include "UIGeometry.h"

typedef struct _UISwitch UISwitch;

UISwitch *UISwitchCreate(UIRect frame);

bool UISwitchGetEnabled(UISwitch *uiswitch);
void UISwitchSetEnabled(UISwitch *uiswitch, bool enabled);