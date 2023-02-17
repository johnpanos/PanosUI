#pragma once
#include "UIView.h"

typedef struct _UILabel
{
    struct _UIView base;
    char *contents;
    UIFloat fontSize;
    UIColor fontColor;
} *UILabel;

void UILabelSetContents(UILabel label, char *contents);
void UILabelSetFontSize(UILabel label, UIFloat fontSize);
void UILabelSetFontColor(UILabel label, UIColor fontColor);
void UILabelSizeToFit(UILabel label);

char *UILabelGetContents(UILabel label);
UIFloat UILabelGetFontSize(UILabel label);
UIColor UILabelGetFontColor(UILabel label);