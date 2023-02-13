#include <stdio.h>
#include "globals.h"
#include <GLES2/gl2.h>
#include "UIWindow_linux.h"
#include "deps/xdg-shell.h"
#include "UILayer_linux.h"

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
    UIRect requestedSize = window->controller->windowWillResize(window, configuredSize);

    UIPlatformLayer *platformLayer = window->rootLayer->platformLayer;

    // wl_egl_window_resize(platformLayer->egl_window, requestedSize.width, requestedSize.height, 0, 0);

    if (platformLayer->egl_surface == EGL_NO_SURFACE)
    {
        fprintf(stderr, "egl surface failed\n");
        exit(1);
    }

    if (
        eglMakeCurrent(
            UIPlatformGlobalsShared.eglData.eglDisplay,
            platformLayer->egl_surface,
            platformLayer->egl_surface,
            UIPlatformGlobalsShared.eglData.eglContext) == EGL_FALSE)
    {

        printf("Could not make egl context current: %d\n", eglGetError());
    }
    else
    {
        printf("before window did resize\n");
        window->controller->windowDidResize(window);

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        if (eglSwapBuffers(UIPlatformGlobalsShared.eglData.eglDisplay, window->rootLayer->platformLayer->egl_surface))
        {
            fprintf(stderr, "Swapped buffers\n");
        }
        else
        {
            fprintf(stderr, "Swapped buffers failed\n");
        }

        window->controller->windowDidLoad(window);

        // UIRect contentRect = window->frame;
        // xdg_surface_set_window_geometry(
        //     window->platformWindow->xdg_surface,
        //     contentRect.x,
        //     contentRect.y,
        //     contentRect.width,
        //     contentRect.height);

        // glClearColor(0, 0, 0, 1);
        // eglSwapBuffers(UIPlatformGlobalsShared.eglData.eglDisplay, platformLayer->egl_surface);

        // struct wl_region *inputRegion = wl_compositor_create_region(UIPlatformGlobalsShared.compositor);
        // wl_region_add(inputRegion, contentRect.x, contentRect.y, contentRect.width, contentRect.height);
        // wl_surface_set_input_region(platformLayer->surface, inputRegion);
        // wl_region_destroy(inputRegion);
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

UILayer *_UIPlatformWindowCreateUILayer(UIRect frame, UIRect bounds)
{
    UILayer *layer = calloc(1, sizeof(UILayer));
    layer->frame = frame;
    layer->bounds = bounds;
    layer->animations = ArrayCreate(sizeof(UIAnimation));
    layer->sublayers = ArrayCreate(sizeof(UILayer *));

    layer->platformLayer = calloc(1, sizeof(UIPlatformLayer));
    layer->platformLayer->surface = wl_compositor_create_surface(UIPlatformGlobalsShared.compositor);

    layer->platformLayer->egl_window = wl_egl_window_create(
        layer->platformLayer->surface,
        frame.size.width,
        frame.size.height);

    if (layer->platformLayer->egl_window == EGL_NO_SURFACE)
    {
        fprintf(stderr, "Can't create egl window\n");
        exit(1);
    }
    else
    {
        fprintf(stderr, "Created egl window\n");
    }

    layer->platformLayer->egl_surface = eglCreateWindowSurface(
        UIPlatformGlobalsShared.eglData.eglDisplay,
        UIPlatformGlobalsShared.eglData.eglConfig,
        layer->platformLayer->egl_window,
        NULL);

    return layer;
}

void _UIPlatformWindowCreate(UIWindow window)
{
    UIPlatformWindow *platformData = calloc(1, sizeof(UIPlatformWindow));
    platformData->window = window;
    window->platformWindow = platformData;

    window->rootLayer = _UIPlatformWindowCreateUILayer(window->frame, window->frame);

    window->platformWindow->xdg_surface = xdg_wm_base_get_xdg_surface(
        UIPlatformGlobalsShared.wm_base,
        window->rootLayer->platformLayer->surface);
    xdg_surface_add_listener(window->platformWindow->xdg_surface, &xdg_surface_listener, window);

    window->platformWindow->toplevel = xdg_surface_get_toplevel(window->platformWindow->xdg_surface);
    xdg_toplevel_add_listener(window->platformWindow->toplevel, &xdg_top_level_listener, window);

    wl_surface_commit(window->rootLayer->platformLayer->surface);
}

void _UIPlatformWindowDestroy(UIWindow window)
{
    xdg_toplevel_destroy(window->platformWindow->toplevel);
    xdg_surface_destroy(window->platformWindow->xdg_surface);
    wl_surface_destroy(window->rootLayer->platformLayer->surface);
}

void _UIPlatformWindowSetTitle(UIWindow window, const char *title)
{
    xdg_toplevel_set_title(window->platformWindow->toplevel, title);
}

void _UIPlatformWindowMove(UIWindow window, UIEvent event)
{
    xdg_toplevel_move(window->platformWindow->toplevel, UIPlatformGlobalsShared.wl_seat, event.reserved);
}

void _UIPlatformWindowResize(UIWindow window, UIEvent event)
{
    xdg_toplevel_resize(window->platformWindow->toplevel, UIPlatformGlobalsShared.wl_seat, event.reserved, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT);
}