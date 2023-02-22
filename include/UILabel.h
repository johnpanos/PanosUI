#pragma once
#include "UIView.h"

typedef struct _UILabel
{
	struct _UIView base;
	const char *contents;
	UIFloat fontSize;
	UIColor fontColor;
} *UILabel;

UILabel UILabelCreate(UIRect frame);

void UILabelSetContents(UILabel label, const char *contents);
void UILabelSetFontSize(UILabel label, UIFloat fontSize);
void UILabelSetFontColor(UILabel label, UIColor fontColor);
void UILabelSizeToFit(UILabel label);

const char *UILabelGetContents(UILabel label);
UIFloat UILabelGetFontSize(UILabel label);
UIColor UILabelGetFontColor(UILabel label);