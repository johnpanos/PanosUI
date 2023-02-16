#include <stdio.h>
#include "globals.h"
#include <GLES2/gl2.h>
#include "UIWindow_linux.h"
#include "platform.h"
#include "deps/xdg-shell.h"
#include "deps/ext-blur-mask-unstable-v1.h"

// XDG SURFACE
static void
xdg_surface_configure(void *data,
                      struct xdg_surface *xdg_surface, uint32_t serial)
{
    // printf("xdg surface configure\n");
    xdg_surface_ack_configure(xdg_surface, serial);
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_configure,
};

// XDG TOPLEVEL
static void
xdg_toplevel_configure_handler(void *data,
                               struct xdg_toplevel *xdg_toplevel,
                               int32_t width,
                               int32_t height,
                               struct wl_array *states)
{
    printf("XDG TOPLEVEL\n");
    UIWindow window = (UIWindow)data;
    UIRect configuredSize = UIRectCreate(0, 0, (UIFloat)width, (UIFloat)height);
    UIRect requestedSize = window->controller->windowWillResize(window->controller->_self, window, configuredSize);

    UIPlatformWindow *platformWindow = window->platformWindow;

    // TODO: Make a dmabuf mask and pass it to ext_blur_mask_v1
    // struct ext_blur_mask_v1 *blurMask = ext_blur_mask_manager_v1_get_blur(UIPlatformGlobalsShared.blur_mask_manager, platformLayer->surface);
    // ext_blur_mask_v1_set_mask(blurMask);

    if (platformWindow->eglWindow != NULL)
    {
        wl_egl_window_resize(
            platformWindow->eglWindow,
            requestedSize.size.width,
            requestedSize.size.height,
            0, 0);
    }
    else
    {
        platformWindow->eglWindow = wl_egl_window_create(
            platformWindow->wlSurface,
            requestedSize.size.width,
            requestedSize.size.height);
        platformWindow->eglSurface = eglCreateWindowSurface(
            UIPlatformGlobalsShared.eglData.eglDisplay,
            UIPlatformGlobalsShared.eglData.eglConfig,
            platformWindow->eglWindow,
            NULL);
    }

    if (platformWindow->eglSurface == EGL_NO_SURFACE)
    {
        fprintf(stderr, "egl surface failed\n");
        exit(1);
    }

    if (
        eglMakeCurrent(
            UIPlatformGlobalsShared.eglData.eglDisplay,
            platformWindow->eglSurface,
            platformWindow->eglSurface,
            UIPlatformGlobalsShared.eglData.eglContext) == EGL_FALSE)
    {

        printf("Could not make egl context current: %d\n", eglGetError());
    }
    else
    {
        window->frame = requestedSize;
        printf("before window did resize\n");
        window->controller->windowDidResize(window->controller->_self, window);

        if (window->graphicsContext != NULL)
        {
            UIGraphicsContextDestroy(window->graphicsContext);
        }

        window->graphicsContext = UIGraphicsContextCreate(platformWindow->eglSurface, window->frame.size.width, window->frame.size.height);
        window->mainView->needsDisplay = 1;
        window->mainView->needsLayout = 1;

        UIRect contentRect = window->contentFrame;
        printf("contentRect: x(%f) y(%f) w(%f) h(%f)\n",
               window->frame.origin.x,
               window->frame.origin.y,
               window->frame.size.width,
               window->frame.size.height);
        printf("contentRect: x(%f) y(%f) w(%f) h(%f)\n",
               contentRect.origin.x,
               contentRect.origin.y,
               contentRect.size.width,
               contentRect.size.height);
        xdg_surface_set_window_geometry(
            window->platformWindow->xdgSurface,
            (int32_t)contentRect.origin.x,
            (int32_t)contentRect.origin.y,
            (int32_t)contentRect.size.width,
            (int32_t)contentRect.size.height);

        struct wl_region *inputRegion = wl_compositor_create_region(UIPlatformGlobalsShared.compositor);
        wl_region_add(
            inputRegion,
            (int32_t)contentRect.origin.x,
            (int32_t)contentRect.origin.y,
            (int32_t)contentRect.size.width,
            (int32_t)contentRect.size.height);
        wl_surface_set_input_region(window->platformWindow->wlSurface, inputRegion);
        wl_region_destroy(inputRegion);
    }
}

static void xdg_toplevel_close_handler(void *data, struct xdg_toplevel *xdg_toplevel)
{
    UIWindow window = (UIWindow)data;
    UIWindowDestroy(window);
}

static const struct xdg_toplevel_listener xdg_top_level_listener = {
    .configure = xdg_toplevel_configure_handler,
    .close = xdg_toplevel_close_handler,
};

void _UIPlatformWindowCreate(UIWindow window)
{
    UIPlatformWindow *platformWindow = calloc(1, sizeof(UIPlatformWindow));
    platformWindow->window = window;
    window->platformWindow = platformWindow;

    platformWindow->wlSurface = wl_compositor_create_surface(UIPlatformGlobalsShared.compositor);
    platformWindow->xdgSurface = xdg_wm_base_get_xdg_surface(
        UIPlatformGlobalsShared.wm_base,
        platformWindow->wlSurface);
    xdg_surface_add_listener(platformWindow->xdgSurface, &xdg_surface_listener, window);

    platformWindow->xdgToplevel = xdg_surface_get_toplevel(platformWindow->xdgSurface);
    xdg_toplevel_add_listener(platformWindow->xdgToplevel, &xdg_top_level_listener, window);

    wl_surface_commit(platformWindow->wlSurface);
}

void _UIPlatformWindowDestroy(UIWindow window)
{
    UIPlatformWindow *platformWindow = window->platformWindow;
    wl_egl_window_destroy(platformWindow->eglWindow);
    xdg_toplevel_destroy(platformWindow->xdgToplevel);
    xdg_surface_destroy(platformWindow->xdgSurface);
    wl_surface_destroy(platformWindow->wlSurface);
}

void _UIPlatformWindowSetTitle(UIWindow window, const char *title)
{
    xdg_toplevel_set_title(window->platformWindow->xdgToplevel, title);
}

void _UIPlatformWindowMove(UIWindow window, UIEvent event)
{
    xdg_toplevel_move(window->platformWindow->xdgToplevel, UIPlatformGlobalsShared.wl_seat, event.reserved);
}

void _UIPlatformWindowResize(UIWindow window, UIEvent event)
{
    xdg_toplevel_resize(window->platformWindow->xdgToplevel, UIPlatformGlobalsShared.wl_seat, event.reserved, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT);
}

void _UIPlatformWindowMakeCurrent(UIWindow window)
{
    if (
        eglMakeCurrent(
            UIPlatformGlobalsShared.eglData.eglDisplay,
            window->platformWindow->eglSurface,
            window->platformWindow->eglSurface,
            UIPlatformGlobalsShared.eglData.eglContext) == EGL_FALSE)
    {

        printf("Could not make egl context current: %d\n", eglGetError());
    }
}

void _UIPlatformWindowFlush(UIWindow window)
{
    if (eglSwapBuffers(UIPlatformGlobalsShared.eglData.eglDisplay, window->platformWindow->eglSurface))
    {
        // fprintf(stderr, "Swapped buffers\n");
    }
    else
    {
        fprintf(stderr, "Swapped buffers failed\n");
    }
}