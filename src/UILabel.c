#include "UILabel.h"

void UILabelSetContents(UILabel label, char *contents)
{
    label->contents = contents;
}
void UILabelSetFontSize(UILabel label, UIFloat fontSize)
{
    label->fontSize = fontSize;
}
void UILabelSetFontColor(UILabel label, UIColor fontColor)
{
    label->fontColor = fontColor;
}
void UILabelSizeToFit(UILabel label)
{
    // TODO: Math
}

char *UILabelGetContents(UILabel label)
{
    return label->contents;
}
UIFloat UILabelGetFontSize(UILabel label)
{
    return label->fontSize;
}
UIColor UILabelGetFontColor(UILabel label)
{
    return label->fontColor;
}