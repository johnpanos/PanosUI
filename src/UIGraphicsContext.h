#ifndef _UIGRAPHICSCONTEXT_H
#define _UIGRAPHICSCONTEXT_H

#include "UIRect.h"

typedef struct _UIGraphicsContext UIGraphicsContext;
typedef struct _UIPoint UIPoint;
typedef struct _UIColor UIColor;

void UIGraphicsContextMakeCurrent(UIGraphicsContext *context);
void UIGraphicsContextFlush(UIGraphicsContext *context);

void UIGraphicsSetFillColor(UIGraphicsContext *context, UIColor color);
void UIGraphicsSetStrokeColor(UIGraphicsContext *context, UIColor color);
void UIGraphicsSetStrokeWidth(UIGraphicsContext *context, float width);

// MARK: Context
void UIGraphicsContextSave(UIGraphicsContext *context);
void UIGraphicsContextRestore(UIGraphicsContext *context);

// MARK:
void UIGraphicsContextClipToRect(UIGraphicsContext *context, UIRect rect, double radius);

// MARK: Shapes
void UIGraphicsContextAddPath(UIGraphicsContext *context);
void UIGraphicsContextAddLine(UIGraphicsContext *context, UIPoint p1, const UIPoint p2);
void UIGraphicsContextAddRect(UIGraphicsContext *context, UIRect rect, double radius);
void UIGraphicsContextAddOval(UIGraphicsContext *context, UIPoint p, int width, int height);

// MARK: Shadow
void UIGraphicsContextSetShadow(UIGraphicsContext *context, UIPoint offset, float blur);
void UIGraphicsContextSetShadowColor(UIGraphicsContext *context, UIColor color);

#endif