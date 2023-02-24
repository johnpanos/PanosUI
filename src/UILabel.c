#include "UILabel.h"
#include "UIGraphicsContext.h"
#include "include/UIColor.h"

void _UILabelDoNothing(UIView *view)
{
	view->needsLayout = 0;
}

UIColor *BLACK;

void UILabelDrawLayer(void *self, UILayer *layer, UIGraphicsContext *ctx) {
	UILabel *label = (UILabel*) self;
	UIGraphicsSetFillColor(ctx, BLACK);
	UIGraphicsContextAddText(ctx, layer->frame.origin, label->contents, NULL, label->fontSize, 0);
}

UILabel *UILabelCreate(UIRect frame)
{
	BLACK = UIColorCreateRGBA(0, 0, 0, 255);
	UILabel *label = calloc(1, sizeof(struct _UILabel));
	label->base.layer = UILayerCreate(frame, frame);

	label->base.responder = UIEventResponderCreate();
	UIViewSetFrame((UIView *)label, frame);
	UIRect boundsCopy = frame;
	boundsCopy.origin.x = 0;
	boundsCopy.origin.y = 0;

	UIViewSetBounds((UIView *)label, boundsCopy);
	label->base.subviews = ArrayCreate(sizeof(UIView *));
	label->base.needsDisplay = 1;
	label->base.needsLayout = 1;
	label->base.layoutSubviews = &_UILabelDoNothing;

	label->base.layer->delegate._self = label;
	label->base.layer->delegate.drawLayer = &UILabelDrawLayer;

	return label;
}

void UILabelSetContents(UILabel *label, const char *contents)
{
	label->contents = contents;
}
void UILabelSetFontSize(UILabel *label, UIFloat fontSize)
{
	label->fontSize = fontSize;
}
void UILabelSetFontColor(UILabel *label, UIColor fontColor)
{
	label->fontColor = fontColor;
}
void UILabelSizeToFit(UILabel *label)
{
	// TODO: Math
}

const char *UILabelGetContents(UILabel *label)
{
	return label->contents;
}
UIFloat UILabelGetFontSize(UILabel *label)
{
	return label->fontSize;
}
UIColor UILabelGetFontColor(UILabel *label)
{
	return label->fontColor;
}