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
    };
}

#endif