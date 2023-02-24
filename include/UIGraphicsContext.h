#include "UIColor.h"
#include "UIGeometry.h"

typedef struct _UIGraphicsContext UIGraphicsContext;

void UIGraphicsContextMakeCurrent(UIGraphicsContext *ctx);
void UIGraphicsContextClear(UIGraphicsContext *ctx);
void UIGraphicsContextFlush(UIGraphicsContext *ctx);

void UIGraphicsSetFillColor(UIGraphicsContext *ctx, const UIColor *color);
void UIGraphicsSetStrokeColor(UIGraphicsContext *ctx, const UIColor *color);
void UIGraphicsSetStrokeWidth(UIGraphicsContext *ctx, UIFloat width);

// MARK: Context
void UIGraphicsContextSave(UIGraphicsContext *ctx);
void UIGraphicsContextRestore(UIGraphicsContext *ctx);

// MARK: Masking
void UIGraphicsContextClipToRect(UIGraphicsContext *ctx, UIRect rect, UIFloat radius);

// MARK: Transform
void UIGraphicsContextSetTransform(UIGraphicsContext *ctx, UIFloat x, UIFloat y);

// MARK: Text
void UIGraphicsContextAddText(UIGraphicsContext *ctx, UIPoint pos, const char *str, const char *font, int fontSize,
							  int weight);

// MARK: Shapes
void UIGraphicsContextAddPath(UIGraphicsContext *ctx);
void UIGraphicsContextAddLine(UIGraphicsContext *ctx, UIPoint p1, const UIPoint p2);
void UIGraphicsContextAddRect(UIGraphicsContext *ctx, UIRect rect, UIFloat radius);
void UIGraphicsContextAddOval(UIGraphicsContext *ctx, UIPoint p, UIFloat width, UIFloat height);

// MARK: Shadow
void UIGraphicsContextSetShadow(UIGraphicsContext *ctx, UIPoint offset, UIFloat blur);
void UIGraphicsContextSetShadowColor(UIGraphicsContext *ctx, const UIColor *color);