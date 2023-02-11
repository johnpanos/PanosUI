#pragma once

#include "Callback.hpp"
extern "C"
{
#include "UIEvent.h"
#include "UIEventResponder.h"
}

typedef void (*callback_t)(UIEventResponder responder, UIEvent event);

namespace UI
{
    class EventResponder
    {
    protected:
        UIEventResponder backing_responder;

    public:
        void set(UIEventResponder backing_responder)
        {
            this->backing_responder = backing_responder;
            Callback<void(UIEventResponder responder, UIEvent event)>::func = std::bind(&EventResponder::_leftMouseDown, this, std::placeholders::_1, std::placeholders::_2);
            this->backing_responder->leftMouseDown = static_cast<callback_t>(Callback<void(UIEventResponder responder, UIEvent event)>::callback);
        }

        void _leftMouseDown(UIEventResponder self, UIEvent event)
        {
            this->leftMouseDown(event);
        }

        virtual void leftMouseDown(UIEvent event)
        {
            if (this->backing_responder->next != NULL)
            {
                this->backing_responder->next->leftMouseDown(this->backing_responder, event);
            }
        }
        virtual void leftMouseUp(UIEvent event)
        {
            if (this->backing_responder->next != NULL)
            {
                this->backing_responder->next->leftMouseUp(this->backing_responder, event);
            }
        }
        virtual void rightMouseDown(UIEvent event)
        {
            if (this->backing_responder->next != NULL)
            {
                this->backing_responder->next->rightMouseDown(this->backing_responder, event);
            }
        }
        virtual void rightMouseUp(UIEvent event)
        {
            if (this->backing_responder->next != NULL)
            {
                this->backing_responder->next->rightMouseUp(this->backing_responder, event);
            }
        }
        virtual void mouseMove(UIEvent event)
        {
            if (this->backing_responder->next != NULL)
            {
                this->backing_responder->next->mouseMove(this->backing_responder, event);
            }
        }
        virtual void mouseScroll(UIEvent event)
        {
            if (this->backing_responder->next != NULL)
            {
                this->backing_responder->next->mouseScroll(this->backing_responder, event);
            }
        }
    };
};