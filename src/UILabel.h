#pragma once
#include "UIView.h"
#include "include/UILabel.h"

typedef struct _UILabel
{
	UIView base;
	const char *contents;
	UIFloat fontSize;
	UIColor fontColor;
} UILabel;