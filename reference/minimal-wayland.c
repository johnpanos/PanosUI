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

#include "../linux-dmabuf_unstable-v1.h"
#include "../xdg-shell.h"

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

EGLDisplay egl_display;
EGLConfig config;
EGLContext egl_context;
EGLSurface egl_surface;

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
    printf("xdg surface configure\n");
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

    printf("xdg toplevel configure\n");
    // printf("w: %d | h: %d\n", width, height);

    egl_display = eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT, display, NULL);
    if (eglInitialize(egl_display, NULL, NULL) == EGL_FALSE)
    {
        fprintf(stderr, "eglInitialize failed");
        return 1;
    }

    EGLint major = 0;
    EGLint minor = 0;
    if (eglInitialize(egl_display, &major, &minor) == EGL_FALSE)
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
    if (!eglChooseConfig(egl_display, config_attributes, &config, 1, &matched))
    {
        fprintf(stderr, "egl choose config failed");
        return 1;
    }

    egl_context = eglCreateContext(egl_display, config, EGL_NO_CONTEXT, context_attributes);
    if (egl_context == EGL_NO_CONTEXT)
    {
        fprintf(stderr, "egl context failed");
        return 1;
    }

    struct wl_egl_window *egl_window = wl_egl_window_create((struct wl_surface *)data, 100, 100);

    egl_surface = eglCreateWindowSurface(egl_display, config, egl_window, NULL);

    if (egl_surface == EGL_NO_SURFACE)
    {
        fprintf(stderr, "egl surface failed");
        return 1;
    }
}

static void xdg_toplevel_close_handler(void *data, struct xdg_toplevel *xdg_toplevel)
{
}

static const struct xdg_toplevel_listener xdg_top_level_listener = {
    .configure = xdg_toplevel_configure_handler,
    .close = xdg_toplevel_close_handler,
};

int main()
{
    display = wl_display_connect(NULL);

    if (display == NULL)
    {
        fprintf(stderr, "Can't connect to display\n");
        return 1;
    }
    printf("Connected to display\n");

    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);

    if (compositor == NULL)
    {
        fprintf(stderr, "Can't find compositor\n");
        return 1;
    }
    printf("Found compositor\n");

    if (wm_base == NULL)
    {
        fprintf(stderr, "Can't find wm_base\n");
        return 1;
    }
    printf("Found wm_base\n");
    xdg_wm_base_add_listener(wm_base, &wm_base_listener, NULL);

    struct wl_surface *surface = wl_compositor_create_surface(compositor);

    struct xdg_surface *xdg_surface = xdg_wm_base_get_xdg_surface(wm_base, surface);
    xdg_surface_add_listener(xdg_surface, &xdg_surface_listener, surface);

    struct xdg_toplevel *toplevel = xdg_surface_get_toplevel(xdg_surface);
    xdg_toplevel_add_listener(toplevel, &xdg_top_level_listener, surface);
    xdg_toplevel_set_title(toplevel, "Hello World");

    wl_surface_commit(surface);

    while (wl_display_dispatch(display) != -1)
    {
        eglMakeCurrent(egl_display, egl_surface, egl_surface, egl_context);
        glClearColor(0, 0, 0, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);

        if (eglSwapBuffers(egl_display, egl_surface) == EGL_FALSE)
        {
            fprintf(stderr, "%d: failed to swap buffers\n", eglGetError());
        }
    }

    wl_display_disconnect(display);

    return 0;
}