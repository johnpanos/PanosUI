#ifndef _UIVIEW_HPP
#define _UIVIEW_HPP
extern "C"
{
#include "UIView.h"
}

namespace UI
{
    class View
    {
    public:
        UIView backing_view;

        View(){};

        View(UIRect frame, UIRect bounds)
        {
            this->backing_view = UIViewCreate(frame, bounds);
        }

        View(UIView backing_view)
        {
            this->backing_view = backing_view;
        }

        ~View()
        {
            UIViewDestroy(this->backing_view);
        }

        void add_subview(View *view)
        {
            UIViewAddSubview(this->backing_view, view->backing_view);
        }

        void set_frame(UIRect to)
        {
            this->backing_view->frame = to;
        }

        UIRect get_frame()
        {
            return this->backing_view->frame;
        }

        void set_background_color(UIColor color) {
            UIViewSetBackgroundColor(this->backing_view, color);
        }

        UIColor get_background_color() {
            return UIViewGetBackgroundColor(this->backing_view);
        }

        void set_corner_radius(float corner_radius) {
            UIViewSetCornerRadius(this->backing_view, corner_radius);
        }

        float get_corner_radius() {
            return UIViewGetCornerRadius(this->backing_view);
        }

        void set_border_color(UIColor border_color) {
            UIViewSetBorderColor(this->backing_view, border_color);
        }

        UIColor get_border_color() {
            return UIViewGetBorderColor(this->backing_view);
        }

        void set_border_width(float border_width) {
            UIViewSetBorderWidth(this->backing_view, border_width);
        }

        float get_border_width() {
            return UIViewGetBorderWidth(this->backing_view);
        }

        void set_shadow_offset(UIPoint offset) {
            UIViewSetShadowOffset(this->backing_view, offset);
        }

        UIPoint get_shadow_offset() {
            return UIViewGetShadowOffset(this->backing_view);
        }

        void set_shadow_color(UIColor color) {
            UIViewSetShadowColor(this->backing_view, color);
        }

        UIColor get_shadow_color() {
            return UIViewGetShadowColor(this->backing_view);
        }

        void set_shadow_radius(float shadow_radius) {
            UIViewSetShadowRadius(this->backing_view, shadow_radius);
        }

        float get_shadow_radius() {
            return UIViewGetShadowRadius(this->backing_view);
        }
    };
}

#endif