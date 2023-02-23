#pragma once

#include "UIGeometry.h"
#include "UILayer.h"
#include "UIView.h"
#include "UIWindowController.h"

enum UIWindowType
{
	UIWindowTypeBorderless = 1 << 0,
	UIWindowTypeTitlebar = 1 << 1,
	UIWindowTypeHasClose = 1 << 2,
	UIWindowTypeHasHide = 1 << 3,
	UIWindowTypeHasResize = 1 << 4,
	UIWindowTypeShell = 1 << 5
};

typedef struct _UIWindow UIWindow;

/**
 * @brief Create a window with the passed in rect size
 *
 * @param rect Size to make the window
 * @return UIWindow The instantiated window object
 */
UIWindow *UIWindowCreate(UIRect rect);
/**
 * @brief
 *
 * @param frame
 * @param flags
 * @return UIWindow
 */
UIWindow *UIWindowCreateWithFlags(UIRect frame, unsigned int flags);
/**
 * @brief Frees the memory that the window is using
 *
 * @param window The window to free
 */
void UIWindowDestroy(UIWindow *window);

/**
 * @brief Creates the platform window and brings it to front
 *
 * @param window The window
 */
void UIWindowShow(UIWindow *window);
/**
 * @brief
 *
 * @param window
 * @param controller
 */
void UIWindowSetController(UIWindow *window, UIWindowController *controller);
/**
 * @brief Sets the window title
 *
 * @param window The window
 * @param title The text that the title will be set to
 */
void UIWindowSetTitle(UIWindow *window, const char *title);

UIView *UIWindowGetMainView(UIWindow *window);

/**
 * @brief Sends an event that will be passed down the event responder chain
 *
 * @param window The window the event will be sent to
 * @param event The current event
 */
void UIWindowSendEvent(UIWindow *window, UIEvent event);