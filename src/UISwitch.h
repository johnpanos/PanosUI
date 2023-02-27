#pragma once
#include "UIView.h"
#include "include/UISwitch.h"

typedef struct _UISwitch
{
	UIView base;
	UIView *toggleView;
	bool enabled;
} UISwitch;