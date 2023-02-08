#include <stdio.h>
#include <wayland-client.h>
#include <wayland-cursor.h>
#include <linux/input-event-codes.h>

#include "../shared/Array.h"
#include "include/UIEvent.h"
#include "../UIWindow.h"
#include "../UIApplication.h"
#include "platformData.h"

extern struct UIPlatformGlobals UIPlatformGlobalsShared;

struct UIPlatformSeatData
{
    struct wl_seat *wl_seat;
    struct wl_pointer *wl_pointer;
    struct wl_surface *cursor_surface;

    UIWindow window;
};

struct wl_pointer_listener pointer_listener;

static void seat_handle_capabilities(void *data, struct wl_seat *wl_seat, uint32_t caps)
{
    struct UIPlatformSeatData *seatData = (struct UIPlatformSeatData *)data;
    printf("Pointer handle capabilities\n");

    if (seatData->wl_pointer != NULL)
    {
        wl_pointer_release(seatData->wl_pointer);
        seatData->wl_pointer = NULL;
    }

    if (caps & WL_SEAT_CAPABILITY_POINTER)
    {
        printf("Has pointer\n");
        seatData->wl_pointer = wl_seat_get_pointer(wl_seat);
        wl_pointer_add_listener(seatData->wl_pointer, &pointer_listener, seatData);
    }
}

static void seat_handle_name(void *data, struct wl_seat *wl_seat, const char *name)
{
}

const struct wl_seat_listener seat_listener = {
    .capabilities = seat_handle_capabilities,
    .name = seat_handle_name,
};

static void setup_cursor_image(void *data, uint32_t serial)
{
    struct UIPlatformSeatData *seatData = (struct UIPlatformSeatData *)data;

    struct wl_cursor_theme *cursor_theme = wl_cursor_theme_load(NULL, 16, UIPlatformGlobalsShared.wl_shm);
    struct wl_cursor_image *image = wl_cursor_theme_get_cursor(cursor_theme, "left_ptr")->images[0];

    seatData->cursor_surface = wl_compositor_create_surface(UIPlatformGlobalsShared.compositor);
    wl_surface_attach(seatData->cursor_surface,
                      wl_cursor_image_get_buffer(image), 0, 0);
    wl_surface_damage(seatData->cursor_surface, 1, 0,
                      image->width, image->height);
    wl_surface_commit(seatData->cursor_surface);
    wl_pointer_set_cursor(seatData->wl_pointer, serial, seatData->cursor_surface,
                          image->hotspot_x, image->hotspot_y);
}

static void wl_pointer_enter(void *data, struct wl_pointer *wl_pointer,
                             uint32_t serial, struct wl_surface *surface,
                             wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    struct UIPlatformSeatData *seatData = (struct UIPlatformSeatData *)data;

    setup_cursor_image(seatData, serial);

    Array windows = UIApplicationShared()->windows;
    UIWindow windowForEvent = NULL;

    for (int i = 0; i < ArrayGetCapacity(windows); i++)
    {
        UIWindow window = ArrayGetValueAtIndex(windows, i);
        struct UIWindowPlatformData *platformData = ToPlatformData(window);
        if (platformData->surface == surface)
        {
            windowForEvent = window;
        }
    }

    if (windowForEvent != NULL)
    {
        seatData->window = windowForEvent;
    }
}

static void wl_pointer_leave(void *data, struct wl_pointer *wl_pointer,
                             uint32_t serial, struct wl_surface *surface)
{
}

static void wl_pointer_motion(void *data, struct wl_pointer *wl_pointer,
                              uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
    struct UIPlatformSeatData *seatData = (struct UIPlatformSeatData *)data;

    if (seatData->window == NULL)
    {
        return;
    }

    UIEvent event = {
        .type = UIEventTypeMouseMotion,
        .window = seatData->window,
        ._eventData = {
            .mouseMotion = {
                .x = wl_fixed_to_int(surface_x),
                .y = wl_fixed_to_int(surface_y)}}};

    UIApplicationSendEvent(event);
}

static void wl_pointer_button(void *data, struct wl_pointer *wl_pointer,
                              uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
    struct UIPlatformSeatData *seatData = (struct UIPlatformSeatData *)data;

    UIEvent event = {
        .reserved = serial,
        .type = state ? UIEventTypeMouseDown : UIEventTypeMouseUp,
        .window = seatData->window,
        ._eventData = {
            .mouseButton = {
                .button = button == BTN_LEFT ? UIEventMouseButtonTypeLeft : UIEventMouseButtonTypeRight,
                .state = state
            }
        }
    };

    UIApplicationSendEvent(event);
}

static void wl_pointer_axis(void *data, struct wl_pointer *wl_pointer,
                            uint32_t time, uint32_t axis, wl_fixed_t value)
{
    struct UIPlatformSeatData *seatData = (struct UIPlatformSeatData *)data;

    if (seatData->window == NULL)
    {
        return;
    }

    UIEvent event = {
        .type = UIEventTypeMouseScroll,
        .window = seatData->window,
        ._eventData = {
            .mouseScroll = {
                .direction = axis,
                .type = UIEventMouseScrollTypeContinuous}}};

    if (axis)
    {
        event._eventData.mouseScroll.x = value;
    }
    else
    {
        event._eventData.mouseScroll.y = value;
    }

    UIApplicationSendEvent(event);
}

static void wl_pointer_frame(void *data, struct wl_pointer *wl_pointer)
{
    // Who cares
}

static void wl_pointer_axis_source(void *data, struct wl_pointer *wl_pointer,
                                   uint32_t axis_source)
{
    // Who cares
}

static void wl_pointer_axis_stop(void *data, struct wl_pointer *wl_pointer,
                                 uint32_t time, uint32_t axis)
{
    // Who cares
}

static void wl_pointer_axis_discrete(void *data, struct wl_pointer *wl_pointer,
                                     uint32_t axis, int32_t discrete)
{
    // Who cares
}

struct wl_pointer_listener pointer_listener = {
    .enter = wl_pointer_enter,
    .leave = wl_pointer_leave,
    .motion = wl_pointer_motion,
    .button = wl_pointer_button,
    .axis = wl_pointer_axis,
    .frame = wl_pointer_frame,
    .axis_source = wl_pointer_axis_source,
    .axis_stop = wl_pointer_axis_stop,
    .axis_discrete = wl_pointer_axis_discrete,
};

struct UIPlatformSeatData globalSeatData;

void setupSeat()
{
    if (UIPlatformGlobalsShared.wl_seat == NULL)
    {
        exit(1);
    }

    wl_seat_add_listener(UIPlatformGlobalsShared.wl_seat, &seat_listener, &globalSeatData);
}