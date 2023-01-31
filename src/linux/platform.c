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

#include "deps/linux-dmabuf_unstable-v1.h"
#include "deps/xdg-shell.h"

struct UIWindowPlatformData
{
    UIWindow *window;

    struct wl_surface *surface;
    struct xdg_surface *xdg_surface;
    struct xdg_toplevel *toplevel;

    struct wl_egl_window *egl_window;

    EGLDisplay egl_display;
    EGLSurface egl_surface;
    EGLContext egl_context;
};

struct UIWindowPlatformData *ToPlatformData(UIWindow *window)
{
    struct UIWindowPlatformData *platformData = (struct UIWindowPlatformData *)window->_platformData;
    return platformData;
}

const EGLint config_attributes[] = {
    EGL_SURFACE_TYPE,
    EGL_WINDOW_BIT,
    EGL_RED_SIZE,
    8,
    EGL_GREEN_SIZE,
    8,
    EGL_BLUE_SIZE,
    8,
    EGL_ALPHA_SIZE,
    8,
    EGL_STENCIL_SIZE,
    8,
    EGL_RENDERABLE_TYPE,
    EGL_OPENGL_ES2_BIT,
    EGL_NONE,
};

const EGLint context_attributes[] = {
    EGL_CONTEXT_CLIENT_VERSION,
    2,
    EGL_NONE,
};

EGLConfig config;

struct wl_display *display = NULL;
struct wl_compositor *compositor = NULL;
struct xdg_wm_base *wm_base = NULL;

static void global_registry_handler(void *data, struct wl_registry *registry, uint32_t id,
                                    const char *interface, uint32_t version)
{
    printf("Got a registry event for %s id %d\n", interface, id);
    if (strcmp(interface, "wl_compositor") == 0)
        compositor = wl_registry_bind(registry,
                                      id,
                                      &wl_compositor_interface,
                                      1);
    if (strcmp(interface, "xdg_wm_base") == 0)
    {
        wm_base = wl_registry_bind(registry, id, &xdg_wm_base_interface, 1);
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
    printf("pong\n");
    xdg_wm_base_pong(wm_base, serial);
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
    struct UIWindowPlatformData *platformData = (struct UIWindowPlatformData *)data;

    printf("xdg toplevel configure\n");

    platformData->egl_display = eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT, display, NULL);
    if (eglInitialize(platformData->egl_display, NULL, NULL) == EGL_FALSE)
    {
        fprintf(stderr, "eglInitialize failed");
        exit(1);
    }

    EGLint major = 0;
    EGLint minor = 0;
    if (eglInitialize(platformData->egl_display, &major, &minor) == EGL_FALSE)
    {
        fprintf(stderr, "Failed to initialize EGL\n");
    }
    else
    {
        printf("major: %d | minor: %d\n", major, minor);
        if (!((major == 1 && minor >= 4) || major >= 2))
        {
            fprintf(stderr, "Too old\n");
            return;
        }
    }

    EGLint matched = 0;
    if (!eglChooseConfig(platformData->egl_display, config_attributes, &config, 1, &matched))
    {
        fprintf(stderr, "egl choose config failed");
        exit(1);
    }

    platformData->egl_context = eglCreateContext(platformData->egl_display, config, EGL_NO_CONTEXT, context_attributes);
    if (platformData->egl_context == EGL_NO_CONTEXT)
    {
        fprintf(stderr, "egl context failed");
        exit(1);
    }

    platformData->egl_window = wl_egl_window_create(platformData->surface, 100, 100);

    platformData->egl_surface = eglCreateWindowSurface(platformData->egl_display, config, platformData->egl_window, NULL);

    if (platformData->egl_surface == EGL_NO_SURFACE)
    {
        fprintf(stderr, "egl surface failed");
        exit(1);
    }
}

static void xdg_toplevel_close_handler(void *data, struct xdg_toplevel *xdg_toplevel)
{
    struct UIWindowPlatformData *platformData = (struct UIWindowPlatformData *)data;
    UIWindowDestroy(platformData->window);
}

static const struct xdg_toplevel_listener xdg_top_level_listener = {
    .configure = xdg_toplevel_configure_handler,
    .close = xdg_toplevel_close_handler,
};

void _UIPlatformMain(UIApplication *application)
{
    display = wl_display_connect(NULL);

    if (display == NULL)
    {
        fprintf(stderr, "Can't connect to display\n");
        exit(1);
    }
    printf("Connected to display\n");

    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);

    if (compositor == NULL)
    {
        fprintf(stderr, "Can't find compositor\n");
        exit(1);
    }
    printf("Found compositor\n");

    if (wm_base == NULL)
    {
        fprintf(stderr, "Can't find wm_base\n");
        exit(1);
    }
    printf("Found wm_base\n");
    xdg_wm_base_add_listener(wm_base, &wm_base_listener, NULL);
}

void _UIPlatformEventLoop(UIApplication *application)
{
    wl_display_dispatch(display);

    if (application->window == NULL)
    {
        printf("no window or platformdata\n");
        return;
    }

    struct UIWindowPlatformData *platformData = (struct UIWindowPlatformData *)application->window->_platformData;
    eglMakeCurrent(platformData->egl_display, platformData->egl_surface, platformData->egl_surface, platformData->egl_context);
    glClearColor(0, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    if (eglSwapBuffers(platformData->egl_display, platformData->egl_surface) == EGL_FALSE)
    {
        fprintf(stderr, "%d: failed to swap buffers\n", eglGetError());
    }
}

void _UIPlatformWindowCreate(UIWindow *window)
{
    struct UIWindowPlatformData *platformData = malloc(sizeof(struct UIWindowPlatformData));

    platformData->window = window;

    platformData->surface = wl_compositor_create_surface(compositor);
    platformData->xdg_surface = xdg_wm_base_get_xdg_surface(wm_base, platformData->surface);
    xdg_surface_add_listener(platformData->xdg_surface, &xdg_surface_listener, platformData);

    platformData->toplevel = xdg_surface_get_toplevel(platformData->xdg_surface);
    xdg_toplevel_add_listener(platformData->toplevel, &xdg_top_level_listener, platformData);

    window->_platformData = platformData;

    wl_surface_commit(platformData->surface);
}

void _UIPlatformWindowDestroy(UIWindow *window)
{
    struct UIWindowPlatformData *platformData = ToPlatformData(window);

    wl_egl_window_destroy(platformData->egl_window);
    xdg_toplevel_destroy(platformData->toplevel);
    xdg_surface_destroy(platformData->xdg_surface);
    wl_surface_destroy(platformData->surface);
}

void _UIPlatformWindowSetTitle(UIWindow *window, const char *title)
{
    struct UIWindowPlatformData *platformData = ToPlatformData(window);
    xdg_toplevel_set_title(platformData->toplevel, title);
}