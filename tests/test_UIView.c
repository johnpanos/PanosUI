#include <assert.h>
#include "UIView.h"

int main()
{
    UIRect rect = {
        .x = 0,
        .y = 0,
        .width = 100,
        .height = 100};

    UIView *view1 = UIViewCreate(rect, rect);
    assert(view1 != NULL);
    assert(view1->frame.x == rect.x);
    assert(view1->frame.y == rect.y);
    assert(view1->frame.width == rect.width);
    assert(view1->frame.height == rect.height);

    UIView *view2 = UIViewCreate(rect, rect);
    assert(view2 != NULL);
    assert(view2->frame.x == rect.x);
    assert(view2->frame.y == rect.y);
    assert(view2->frame.width == rect.width);
    assert(view2->frame.height == rect.height);

    UIViewAddSubview(view1, view2);
    assert(view1->subviews[0] == view2);
    assert(view2->parentView == view1);

    UIView *view3 = UIViewCreate(rect, rect);
    UIViewAddSubview(view1, view3);
    assert(view1->subviews[1] == view3);
    assert(view1->_subviewCount == 2);

    UIViewRemoveSubview(view1, view3);
    assert(view3->parentView == NULL);
    assert(view1->_subviewCount == 1);

    UIViewDestroy(view1);
    assert(view2->parentView == NULL);

    return 0;
}