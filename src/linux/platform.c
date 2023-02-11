#include <stdio.h>
#include <fcntl.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <gbm.h>
#include <string.h>

#include "../platform.h"
#include "../UIWindow.h"
#include "../UIApplication.h"
#include "../UIView.h"

#include "deps/linux-dmabuf_unstable-v1.h"
#include "deps/xdg-shell.h"
#include "platform.h"
#include "globals.h"
#include "UILayer_linux.h"

static void global_registry_handler(void *data, struct wl_registry *registry, uint32_t id,
                                    const char *interface, uint32_t version)
{
    // printf("Got a registry event for %s id %d\n", interface, id);

    if (strcmp(interface, "wl_compositor") == 0)
    {
        UIPlatformGlobalsShared.compositor = wl_registry_bind(registry,
                                                              id,
                                                              &wl_compositor_interface,
                                                              1);
    }

    if (strcmp(interface, "wl_subcompositor") == 0)
    {
        printf("found wl_subcompositor\n");
        UIPlatformGlobalsShared.subcompositor = wl_registry_bind(registry, id, &wl_subcompositor_interface, 1);
    }

    if (strcmp(interface, "xdg_wm_base") == 0)
    {
        UIPlatformGlobalsShared.wm_base = wl_registry_bind(registry, id, &xdg_wm_base_interface, 1);
    }

    if (strcmp(interface, "wl_seat") == 0)
    {
        UIPlatformGlobalsShared.wl_seat = wl_registry_bind(registry, id, &wl_seat_interface, 7);
    }

    if (strcmp(interface, "wl_shm") == 0)
    {
        UIPlatformGlobalsShared.wl_shm = wl_registry_bind(registry, id, &wl_shm_interface, version);
    }
}

static void
global_registry_remover(void *data, struct wl_registry *registry, uint32_t id)
{
    printf("Got a registry losing event for %d\n", id);
}

static const struct wl_registry_listener registry_listener = {
    global_registry_handler,
    global_registry_remover};

// XDG WM BASE
static void xdg_wm_base_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
    // printf("pong\n");
    xdg_wm_base_pong(UIPlatformGlobalsShared.wm_base, serial);
}

static const struct xdg_wm_base_listener wm_base_listener = {
    .ping = &xdg_wm_base_ping};

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
    struct UIPlatformWindow *platformData = (struct UIPlatformWindow *)data;
    UIRect configuredSize = {
        .x = 0,
        .y = 0,
        .width = width,
        .height = height};
    UIRect requestedSize = platformData->window->controller->windowWillResize(platformData->window, configuredSize);

    platformData->window->frame.width = requestedSize.width;
    platformData->window->frame.height = requestedSize.height;

    platformData->window->rootLayer->platformLayer->egl_window = wl_egl_window_create(
        platformData->window->rootLayer->platformLayer->surface,
        platformData->window->rootLayer->bounds.width,
        platformData->window->rootLayer->bounds.height);
    platformData->window->rootLayer->platformLayer->egl_surface = eglCreateWindowSurface(
        UIPlatformGlobalsShared.eglData.eglDisplay,
        UIPlatformGlobalsShared.eglData.eglConfig,
        platformData->window->rootLayer->platformLayer->egl_window,
        NULL);

    if (platformData->window->rootLayer->platformLayer->egl_surface == EGL_NO_SURFACE)
    {
        fprintf(stderr, "egl surface failed\n");
        exit(1);
    }

    if (eglMakeCurrent(UIPlatformGlobalsShared.eglData.eglDisplay, platformData->window->rootLayer->platformLayer->egl_surface, platformData->window->rootLayer->platformLayer->egl_surface, UIPlatformGlobalsShared.eglData.eglContext) == EGL_FALSE)
    {

        printf("Could not make egl context current: %d\n", eglGetError());
    }
    else
    {
        if (platformData->window->graphicsContext != NULL)
        {
            printf("Destroying context\n");
            UIGraphicsContextDestroy(platformData->window->graphicsContext);
        }

        // platformData->window->mainView->needsDisplay = 1;

        printf("before window did resize\n");
        platformData->window->controller->windowDidResize(platformData->window);

        UIRect contentRect = platformData->window->frame;
        xdg_surface_set_window_geometry(
            platformData->xdg_surface,
            contentRect.x,
            contentRect.y,
            contentRect.width,
            contentRect.height);

        glClearColor(0, 0, 0, 1);
        eglSwapBuffers(UIPlatformGlobalsShared.eglData.eglDisplay, platformData->window->rootLayer->platformLayer->egl_surface);

        // struct wl_region *inputRegion = wl_compositor_create_region(UIPlatformGlobalsShared.compositor);
        // wl_region_add(inputRegion, contentRect.x, contentRect.y, contentRect.width, contentRect.height);
        // wl_surface_set_input_region(platformData->window->rootLayer->platformLayer->surface, inputRegion);
        // wl_region_destroy(inputRegion);
    }
}

static void xdg_toplevel_close_handler(void *data, struct xdg_toplevel *xdg_toplevel)
{
    struct UIPlatformWindow *platformData = (struct UIPlatformWindow *)data;
    UIWindowDestroy(platformData->window);
}

static const struct xdg_toplevel_listener xdg_top_level_listener = {
    .configure = xdg_toplevel_configure_handler,
    .close = xdg_toplevel_close_handler,
};

void _UIPlatformMain(UIApplication *application)
{
    UIPlatformGlobalsShared.display = wl_display_connect(NULL);

    if (UIPlatformGlobalsShared.display == NULL)
    {
        fprintf(stderr, "Can't connect to display\n");
        exit(1);
    }
    struct wl_registry *registry = wl_display_get_registry(UIPlatformGlobalsShared.display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(UIPlatformGlobalsShared.display);

    if (UIPlatformGlobalsShared.compositor == NULL)
    {
        fprintf(stderr, "Can't find compositor\n");
        exit(1);
    }

    if (UIPlatformGlobalsShared.wm_base == NULL)
    {
        fprintf(stderr, "Can't find wm_base\n");
        exit(1);
    }

    UIPlatformGlobalsShared.eglData = init_egl(UIPlatformGlobalsShared.display);

    xdg_wm_base_add_listener(UIPlatformGlobalsShared.wm_base, &wm_base_listener, NULL);

    setupSeat();

    wl_display_roundtrip(UIPlatformGlobalsShared.display);
}

void _UIPlatformEventLoop(UIApplication *application)
{
    wl_display_dispatch(UIPlatformGlobalsShared.display);

    for (int i = 0; i < ArrayGetCapacity(application->windows); i++)
    {
        struct UIPlatformWindow *platformData = ToPlatformData(ArrayGetValueAtIndex(application->windows, i));
        UIWindowUpdate(platformData->window);
    }
}

void _UIPlatformWindowCreate(UIWindow window)
{
    struct UIPlatformWindow *platformData = calloc(1, sizeof(struct UIPlatformWindow));

    platformData->window = window;

    // setup layer
    platformData->window->rootLayer = calloc(1, sizeof(UILayer));
    platformData->window->rootLayer->animations = ArrayCreate(sizeof(UIAnimation));
    platformData->window->rootLayer->sublayers = ArrayCreate(sizeof(UILayer *));
    platformData->window->rootLayer->bounds = window->frame;
    platformData->window->rootLayer->platformLayer = calloc(1, sizeof(UIPlatformLayer));
    platformData->window->rootLayer->platformLayer->surface = wl_compositor_create_surface(UIPlatformGlobalsShared.compositor);

    platformData->xdg_surface = xdg_wm_base_get_xdg_surface(UIPlatformGlobalsShared.wm_base, platformData->window->rootLayer->platformLayer->surface);
    xdg_surface_add_listener(platformData->xdg_surface, &xdg_surface_listener, platformData);

    platformData->toplevel = xdg_surface_get_toplevel(platformData->xdg_surface);
    xdg_toplevel_add_listener(platformData->toplevel, &xdg_top_level_listener, platformData);

    window->platformWindow = platformData;

    wl_surface_commit(platformData->window->rootLayer->platformLayer->surface);
}

void _UIPlatformWindowDestroy(UIWindow window)
{
    struct UIPlatformWindow *platformData = ToPlatformData(window);

    xdg_toplevel_destroy(platformData->toplevel);
    xdg_surface_destroy(platformData->xdg_surface);
    wl_surface_destroy(platformData->window->rootLayer->platformLayer->surface);
}

void _UIPlatformWindowSetTitle(UIWindow window, const char *title)
{
    struct UIPlatformWindow *platformData = ToPlatformData(window);
    xdg_toplevel_set_title(platformData->toplevel, title);
}

void _UIPlatformWindowMove(UIWindow window, UIEvent event)
{
    struct UIPlatformWindow *platformData = ToPlatformData(window);
    xdg_toplevel_move(platformData->toplevel, UIPlatformGlobalsShared.wl_seat, event.reserved);
}

void _UIPlatformWindowResize(UIWindow window, UIEvent event)
{
    struct UIPlatformWindow *platformData = ToPlatformData(window);
    xdg_toplevel_resize(platformData->toplevel, UIPlatformGlobalsShared.wl_seat, event.reserved, XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT);
}

struct UIPlatformWindow *ToPlatformData(UIWindow window)
{
    struct UIPlatformWindow *platformData = (struct UIPlatformWindow *)window->platformWindow;
    return platformData;
}