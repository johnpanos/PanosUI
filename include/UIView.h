#pragma once

#include <stdbool.h>

#include "UIGeometry.h"

#include "Array.h"
#include "UIColor.h"
#include "UIEventResponder.h"
#include "UILayer.h"

typedef struct _UIView UIView;

/**
 * @brief Creates a view
 *
 * @param frame The size of the view in the parent coordinate space
 * @param bounds The size and position of the view in its own coordinate space
 * @return UIView
 */
UIView *UIViewCreate(UIRect frame, UIRect bounds);
/**
 * @brief Frees the memory the view is taking up
 *
 * @param view The view to free
 */
void UIViewDestroy(UIView *view);

/**
 * @brief Adds the subview as a child to the superview
 *
 * @param superview The parent view
 * @param subview The to-be added child view
 */
void UIViewAddSubview(UIView *superview, UIView *subview);
/**
 * @brief Removes the subview from superview. The subview must be a child of the superview.
 *
 * @param superview The parent view
 * @param subview The to-be removed child view
 */
void UIViewRemoveSubview(UIView *superview, UIView *subview);

UIPoint UIViewConvertPoint(UIView *from, UIView *to, UIPoint point);
UIView *UIViewHitTest(UIView *view, UIPoint point);

// layer
UILayer *UIViewGetLayer(UIView *view);
void UIViewSetLayer(UIView *view, UILayer *layer);

// responder
UIEventResponder *UIViewGetResponder(UIView *view);
void UIViewSetResponder(UIView *view, UIEventResponder *responder);

// frame
UIRect UIViewGetFrame(UIView *view);
void UIViewSetFrame(UIView *view, UIRect frame);

// bounds
UIRect UIViewGetBounds(UIView *view);
void UIViewSetBounds(UIView *view, UIRect bounds);

// parentView
UIView *UIViewGetParentView(UIView *view);
void UIViewSetParentView(UIView *view, UIView *parent);

// needsDisplay
bool UIViewGetNeedsDisplay(UIView *view);
void UIViewSetNeedsDisplay(UIView *view);

// needsLayout
bool UIViewGetNeedsLayout(UIView *view);
void UIViewSetNeedsLayout(UIView *view);

// clipTobounds
bool UIViewGetClipToBounds(UIView *view);
void UIViewSetClipToBounds(UIView *view, bool clipToBounds);

// layoutSubviews
void UIViewSetLayoutSubviews(UIView *view, void (*layoutSubviews)(UIView *view));

// backgroundColor
UIColor *UIViewGetBackgroundColor(UIView *view);
void UIViewSetBackgroundColor(UIView *view, UIColor *backgroundColor);

// cornerRadius
UIFloat UIViewGetCornerRadius(UIView *view);
void UIViewSetCornerRadius(UIView *view, UIFloat cornerRadius);

// borderColor
UIColor *UIViewGetBorderColor(UIView *view);
void UIViewSetBorderColor(UIView *view, UIColor *borderColor);

// borderWidth
UIFloat UIViewGetBorderWidth(UIView *view);
void UIViewSetBorderWidth(UIView *view, UIFloat borderWidth);

// shadowOffset
UIPoint UIViewGetShadowOffset(UIView *view);
void UIViewSetShadowOffset(UIView *view, UIPoint shadowOffset);

// shadowColor
UIColor *UIViewGetShadowColor(UIView *view);
void UIViewSetShadowColor(UIView *view, UIColor *shadowColor);

// shadowRadius
UIFloat UIViewGetShadowRadius(UIView *view);
void UIViewSetShadowRadius(UIView *view, UIFloat shadowRadius);