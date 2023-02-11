#include "UILayer_linux.h"
#include "globals.h"

static const struct wl_callback_listener frame_listener;
static void frame_done(void *data, struct wl_callback *callback,
                       uint32_t time)
{
    printf("frame handler\n");
    UILayer *layer = (UILayer *)data;
    struct wl_callback *cb = wl_surface_frame(layer->platformLayer->surface);
    wl_callback_add_listener(cb, &frame_listener, data);
}

static const struct wl_callback_listener frame_listener = {
    .done = frame_done,
};

UIPlatformLayer *_UIPlatformLayerCreate()
{
    UIPlatformLayer *platformLayer = calloc(1, sizeof(UIPlatformLayer));

    platformLayer->surface = wl_compositor_create_surface(UIPlatformGlobalsShared.compositor);
    wl_surface_commit(platformLayer->surface);

    return platformLayer;
}

void _UIPlatformLayerAddSublayer(UILayer *layer, UILayer *sublayer)
{
    sublayer->platformLayer->subsurface = wl_subcompositor_get_subsurface(
        UIPlatformGlobalsShared.subcompositor,
        sublayer->platformLayer->surface, // Child
        layer->platformLayer->surface);   // Parent

    wl_subsurface_set_position(
        sublayer->platformLayer->subsurface,
        sublayer->bounds.x,
        sublayer->bounds.y);

    struct wl_callback *cb = wl_surface_frame(sublayer->platformLayer->surface);
    wl_callback_add_listener(cb, &frame_listener, sublayer);

    sublayer->platformLayer->egl_window = wl_egl_window_create(
        sublayer->platformLayer->surface,
        sublayer->bounds.width,
        sublayer->bounds.height);

    sublayer->platformLayer->egl_surface = eglCreateWindowSurface(
        UIPlatformGlobalsShared.eglData.eglDisplay,
        UIPlatformGlobalsShared.eglData.eglConfig,
        sublayer->platformLayer->egl_window,
        NULL);
}

void _UIPlatformLayerRemoveSublayer(UILayer *layer, UILayer *sublayer)
{
    wl_subsurface_destroy(sublayer->platformLayer->subsurface);
}