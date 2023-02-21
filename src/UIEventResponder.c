#include "UIEventResponder.h"
#include <stdlib.h>

#define SET_HANDLER_IMPL(RESPONDER, HANDLER) RESPONDER->HANDLER = _UIEventResponder##HANDLER##Default
#define HANDLER_IMPL(HANDLER)                                                                                          \
	void _UIEventResponder##HANDLER##Default(UIEventResponder self, UIEvent event)                                     \
	{                                                                                                                  \
		if (self != NULL && self->next != NULL && self->next->HANDLER != NULL)                                         \
		{                                                                                                              \
			self->next->HANDLER(self->next, event);                                                                    \
		}                                                                                                              \
	}

HANDLER_IMPL(leftMouseDown);
HANDLER_IMPL(leftMouseUp);

HANDLER_IMPL(rightMouseDown);
HANDLER_IMPL(rightMouseUp);

HANDLER_IMPL(mouseMove);
HANDLER_IMPL(mouseScroll);

UIEventResponder UIEventResponderCreate()
{
	UIEventResponder responder = calloc(1, sizeof(struct _UIEventResponder));

	SET_HANDLER_IMPL(responder, leftMouseDown);
	SET_HANDLER_IMPL(responder, leftMouseUp);
	SET_HANDLER_IMPL(responder, rightMouseDown);
	SET_HANDLER_IMPL(responder, rightMouseUp);
	SET_HANDLER_IMPL(responder, mouseMove);
	SET_HANDLER_IMPL(responder, mouseScroll);

	return responder;
}

void UIEventResponderDestroy(UIEventResponder *responder)
{
	free(responder);
}