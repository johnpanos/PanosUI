#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"

#include "../UIGraphicsContext.h"

typedef struct _UIGraphicsContext {
    SkSurface *surface;
    SkCanvas *canvas;
} UIGraphicsContext;

void UIGraphicsContextSave(UIGraphicsContext *context) {
    context->canvas->save();
}
void UIGraphicsContextRestore(UIGraphicsContext *context) {
    context->canvas->restore();
}

// MARK:
void UIGraphicsContextClipToRect(UIGraphicsContext *context, UIRect rect) {
    SkRect skrect = SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
    context->canvas->clipRect(skrect, true);
}

// MARK: Shapes
void UIGraphicsContextAddPath(UIGraphicsContext *context);
void UIGraphicsContextAddLine(UIGraphicsContext *context, UIPoint p1, const UIPoint p2);
void UIGraphicsContextAddRect(UIGraphicsContext *context, UIRect rect, double radius);
void UIGraphicsContextAddOval(UIGraphicsContext *context, UIPoint p, int width, int height);

// MARK: Shadow
void UIGraphicsContextSetShadow(UIGraphicsContext *context, UIPoint offset, float blur);
void UIGraphicsContextSetShadowColor(UIGraphicsContext *context, UIColor color);