#include "UILayer_linux.h"
#include "globals.h"
#include "platform.h"
#include <GLES2/gl2.h>
#include <stdio.h>

static const struct wl_callback_listener frame_listener;
static void frame_done(void *data, struct wl_callback *callback,
                       uint32_t time)
{
    printf("frame handler\n");
    UILayer *layer = (UILayer *)data;

    if (ArrayGetCapacity(layer->animations) < 1)
    {
        printf("No animations\n");
        return;
    }

    UILayer inflight = UILayerGetInFlight(*layer);
    if (layer->parent != NULL)
    {
        printf("Setting position x(%d) y(%d)\n", inflight.frame.x - layer->parent->bounds.x, inflight.frame.y - layer->parent->bounds.y);
        wl_subsurface_set_position(
            layer->platformLayer->subsurface,
            inflight.frame.x - layer->parent->bounds.x,
            inflight.frame.y - layer->parent->bounds.y);
    }
    else
    {
        wl_subsurface_set_position(
            layer->platformLayer->subsurface,
            inflight.frame.x,
            inflight.frame.y);
    }

    wl_egl_window_resize(
        layer->platformLayer->egl_window,
        inflight.bounds.width,
        inflight.bounds.height,
        0,
        0);

    layer->ctx = UIGraphicsContextCreate(layer->platformLayer->egl_surface, inflight.bounds.width, inflight.bounds.height);

    UIGraphicsContextMakeCurrent(layer->ctx);
    UIGraphicsContextClear(layer->ctx);
    UILayerRenderInContext(&inflight, layer->ctx);
    UIGraphicsContextFlush(layer->ctx);
    UIGraphicsContextDestroy(layer->ctx);

    struct wl_callback *cb = wl_surface_frame(layer->platformLayer->surface);
    wl_callback_add_listener(cb, &frame_listener, data);
    wl_surface_damage(layer->platformLayer->surface, 0, 0, layer->bounds.width, layer->bounds.height);
    wl_surface_commit(layer->platformLayer->surface);
}

static const struct wl_callback_listener frame_listener = {
    .done = frame_done,
};

UIPlatformLayer *_UIPlatformLayerCreate()
{
    UIPlatformLayer *platformLayer = calloc(1, sizeof(UIPlatformLayer));

    return platformLayer;
}

void _UIPlatformLayerAddSublayer(UILayer *layer, UILayer *sublayer)
{
    printf("UI platform add layer\n");
    sublayer->platformLayer->surface = wl_compositor_create_surface(UIPlatformGlobalsShared.compositor);

    sublayer->platformLayer->subsurface = wl_subcompositor_get_subsurface(
        UIPlatformGlobalsShared.subcompositor,
        sublayer->platformLayer->surface, // Child
        layer->platformLayer->surface);   // Parent

    wl_subsurface_set_sync(sublayer->platformLayer->subsurface);

    wl_subsurface_set_position(
        sublayer->platformLayer->subsurface,
        sublayer->frame.x,
        sublayer->frame.y);

    sublayer->platformLayer->egl_window = wl_egl_window_create(
        sublayer->platformLayer->surface,
        sublayer->bounds.width,
        sublayer->bounds.height);

    sublayer->platformLayer->egl_surface = eglCreateWindowSurface(
        UIPlatformGlobalsShared.eglData.eglDisplay,
        UIPlatformGlobalsShared.eglData.eglConfig,
        sublayer->platformLayer->egl_window,
        NULL);

    sublayer->ctx = UIGraphicsContextCreate(layer->platformLayer->egl_surface, sublayer->bounds.width, sublayer->bounds.height);

    UIGraphicsContextMakeCurrent(sublayer->ctx);
    UIGraphicsContextClear(sublayer->ctx);
    UIGraphicsContextFlush(sublayer->ctx);
    UIGraphicsContextDestroy(sublayer->ctx);

    struct wl_callback *cb = wl_surface_frame(sublayer->platformLayer->surface);
    wl_callback_add_listener(cb, &frame_listener, sublayer);

    wl_surface_damage(sublayer->platformLayer->surface, 0, 0, sublayer->bounds.width, sublayer->bounds.height);
    wl_surface_commit(sublayer->platformLayer->surface);
}

void _UIPlatformLayerRemoveSublayer(UILayer *layer, UILayer *sublayer)
{
    wl_subsurface_destroy(sublayer->platformLayer->subsurface);
}

void _UIPlatformLayerAddAnimation(UILayer *layer)
{
    if (layer->platformLayer->egl_surface == NULL)
        return;
    struct wl_callback *cb = wl_surface_frame(layer->platformLayer->surface);
    wl_callback_add_listener(cb, &frame_listener, layer);
    wl_surface_damage(layer->platformLayer->surface, 0, 0, layer->bounds.width, layer->bounds.height);
    wl_surface_commit(layer->platformLayer->surface);
}