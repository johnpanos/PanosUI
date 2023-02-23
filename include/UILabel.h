#pragma once

#include "UIColor.h"
#include "UIGeometry.h"

typedef struct _UILabel UILabel;

UILabel *UILabelCreate(UIRect frame);

void UILabelSetContents(UILabel *label, const char *contents);
void UILabelSetFontSize(UILabel *label, UIFloat fontSize);
void UILabelSetFontColor(UILabel *label, UIColor fontColor);
void UILabelSizeToFit(UILabel *label);

const char *UILabelGetContents(UILabel *label);
UIFloat UILabelGetFontSize(UILabel *label);
UIColor UILabelGetFontColor(UILabel *label);