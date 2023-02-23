#pragma once

#include "UIGeometry.h"

typedef struct _UIGraphicsContext UIGraphicsContext;
typedef struct _UIPoint UIPoint;
typedef struct _UIColor UIColor;

void UIGraphicsContextMakeCurrent(UIGraphicsContext *context);
void UIGraphicsContextClear(UIGraphicsContext *context);
void UIGraphicsContextFlush(UIGraphicsContext *context);

void UIGraphicsSetFillColor(UIGraphicsContext *context, const UIColor *color);
void UIGraphicsSetStrokeColor(UIGraphicsContext *context, const UIColor *color);
void UIGraphicsSetStrokeWidth(UIGraphicsContext *context, UIFloat width);

// MARK: Context
void UIGraphicsContextSave(UIGraphicsContext *context);
void UIGraphicsContextRestore(UIGraphicsContext *context);

// MARK:
void UIGraphicsContextClipToRect(UIGraphicsContext *context, UIRect rect, UIFloat radius);

// MARK: Shapes
void UIGraphicsContextAddPath(UIGraphicsContext *context);
void UIGraphicsContextAddLine(UIGraphicsContext *context, UIPoint p1, const UIPoint p2);
void UIGraphicsContextAddRect(UIGraphicsContext *context, UIRect rect, UIFloat radius);
void UIGraphicsContextAddOval(UIGraphicsContext *context, UIPoint p, UIFloat width, UIFloat height);

// MARK: Shadow
void UIGraphicsContextSetShadow(UIGraphicsContext *context, UIPoint offset, UIFloat blur);
void UIGraphicsContextSetShadowColor(UIGraphicsContext *context, const UIColor *color);

void UIGraphicsContextSetTransform(UIGraphicsContext *context, UIFloat x, UIFloat y);