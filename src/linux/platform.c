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
#include "deps/ext-blur-mask-unstable-v1.h"
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

    if (strcmp(interface, ext_blur_mask_manager_v1_interface.name))
    {
        UIPlatformGlobalsShared.blur_mask_manager = wl_registry_bind(registry, id, &ext_blur_mask_manager_v1_interface, 1);
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

    // setupSeat();

    wl_display_roundtrip(UIPlatformGlobalsShared.display);
}

void _UIPlatformEventLoop(UIApplication *application)
{
    wl_display_dispatch(UIPlatformGlobalsShared.display);

    for (int i = 0; i < ArrayGetCapacity(application->windows); i++)
    {
        UIWindow window = ArrayGetValueAtIndex(application->windows, i);
        UIWindowUpdate(window);
    }
}