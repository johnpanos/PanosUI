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

// MARK: Getters
UIRect UIViewGetFrame(UIView *view);
UIRect UIViewGetBounds(UIView *view);
UIColor UIViewGetBackgroundColor(UIView *view);
UIFloat UIViewGetCornerRadius(UIView *view);
UIColor UIViewGetBorderColor(UIView *view);
UIFloat UIViewGetBorderWidth(UIView *view);

UIPoint UIViewGetShadowOffset(UIView *view);
UIColor UIViewGetShadowColor(UIView *view);
UIFloat UIViewGetShadowRadius(UIView *view);

// MARK: Setters
void UIViewSetFrame(UIView *view, UIRect frame);
void UIViewSetBounds(UIView *view, UIRect bounds);
void UIViewSetBackgroundColor(UIView *view, UIColor backgroundColor);
void UIViewSetCornerRadius(UIView *view, UIFloat cornerRadius);
void UIViewSetBorderColor(UIView *view, UIColor borderColor);
void UIViewSetBorderWidth(UIView *view, UIFloat borderWidth);

void UIViewSetShadowOffset(UIView *view, UIPoint shadowOffset);
void UIViewSetShadowColor(UIView *view, UIColor shadowColor);
void UIViewSetShadowRadius(UIView *view, UIFloat shadowRadius);