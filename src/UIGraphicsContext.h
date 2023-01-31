#ifndef _UIGRAPHICSCONTEXT_H
#define _UIGRAPHICSCONTEXT_H

#include "UIView.h"

typedef struct _UIGraphicsContext UIGraphicsContext;
typedef struct _UIPoint UIPoint;

// MARK: Context
void UIGraphicsContextSave(UIGraphicsContext *context);
void UIGraphicsContextRestore(UIGraphicsContext *context);

// MARK:
void UIGraphicsContextClipToRect(UIGraphicsContext *context, UIRect rect);

// MARK: Shapes
void UIGraphicsContextAddPath(UIGraphicsContext *context);
void UIGraphicsContextAddLine(UIGraphicsContext *context, UIPoint p1, const UIPoint p2);
void UIGraphicsContextAddRect(UIGraphicsContext *context, UIRect rect, double radius);
void UIGraphicsContextAddOval(UIGraphicsContext *context);

// MARK: Shadow
void UIGraphicsContextSetShadow(UIGraphicsContext *context);
void UIGraphicsContextSetShadowColor(UIGraphicsContext *context);

#endif