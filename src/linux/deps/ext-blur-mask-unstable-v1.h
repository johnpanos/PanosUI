/* Generated by wayland-scanner 1.21.0 */

#ifndef EXT_BLUR_MASK_UNSTABLE_V1_CLIENT_PROTOCOL_H
#define EXT_BLUR_MASK_UNSTABLE_V1_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_ext_blur_mask_unstable_v1 The ext_blur_mask_unstable_v1 protocol
 * @section page_ifaces_ext_blur_mask_unstable_v1 Interfaces
 * - @subpage page_iface_ext_blur_mask_manager_v1 - protocol for setting a blur mask on a wl_surface
 * - @subpage page_iface_ext_blur_mask_v1 - per-surface blur interface
 * @section page_copyright_ext_blur_mask_unstable_v1 Copyright
 * <pre>
 *
 * Copyright © 2023 John Panos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * </pre>
 */
struct ext_blur_mask_manager_v1;
struct ext_blur_mask_v1;
struct wl_buffer;
struct wl_surface;

#ifndef EXT_BLUR_MASK_MANAGER_V1_INTERFACE
#define EXT_BLUR_MASK_MANAGER_V1_INTERFACE
/**
 * @page page_iface_ext_blur_mask_manager_v1 ext_blur_mask_manager_v1
 * @section page_iface_ext_blur_mask_manager_v1_desc Description
 *
 * Adds a blur mask to a part of a wl_surface.
 *
 * This interface defines a mechanism for a Wayland client to tell the
 * compositor to blur the background of a wl_surface given a specified
 * wl_buffer based blur mask.
 *
 * Warning! The protocol described in this file is experimental and
 * backward incompatible changes may be made. Backward compatible changes
 * may be added together with the corresponding interface version bump.
 * Backward incompatible changes are done by bumping the version number in
 * the protocol and interface names and resetting the interface version.
 * Once the protocol is to be declared stable, the 'z' prefix and the
 * version number in the protocol and interface names are removed and the
 * interface version number is reset.
 * @section page_iface_ext_blur_mask_manager_v1_api API
 * See @ref iface_ext_blur_mask_manager_v1.
 */
/**
 * @defgroup iface_ext_blur_mask_manager_v1 The ext_blur_mask_manager_v1 interface
 *
 * Adds a blur mask to a part of a wl_surface.
 *
 * This interface defines a mechanism for a Wayland client to tell the
 * compositor to blur the background of a wl_surface given a specified
 * wl_buffer based blur mask.
 *
 * Warning! The protocol described in this file is experimental and
 * backward incompatible changes may be made. Backward compatible changes
 * may be added together with the corresponding interface version bump.
 * Backward incompatible changes are done by bumping the version number in
 * the protocol and interface names and resetting the interface version.
 * Once the protocol is to be declared stable, the 'z' prefix and the
 * version number in the protocol and interface names are removed and the
 * interface version number is reset.
 */
extern const struct wl_interface ext_blur_mask_manager_v1_interface;
#endif
#ifndef EXT_BLUR_MASK_V1_INTERFACE
#define EXT_BLUR_MASK_V1_INTERFACE
/**
 * @page page_iface_ext_blur_mask_v1 ext_blur_mask_v1
 * @section page_iface_ext_blur_mask_v1_desc Description
 *
 * An additional interface to a wl_surface object, which allows the client
 * to hint to the compositor that it would like to blur a section of a wl_surface.
 * @section page_iface_ext_blur_mask_v1_api API
 * See @ref iface_ext_blur_mask_v1.
 */
/**
 * @defgroup iface_ext_blur_mask_v1 The ext_blur_mask_v1 interface
 *
 * An additional interface to a wl_surface object, which allows the client
 * to hint to the compositor that it would like to blur a section of a wl_surface.
 */
extern const struct wl_interface ext_blur_mask_v1_interface;
#endif

#ifndef EXT_BLUR_MASK_MANAGER_V1_ERROR_ENUM
#define EXT_BLUR_MASK_MANAGER_V1_ERROR_ENUM
enum ext_blur_mask_manager_v1_error {
	/**
	 * the surface already has a blur mask object associated
	 */
	EXT_BLUR_MASK_MANAGER_V1_ERROR_BLUR_MASK_EXISTS = 0,
	/**
	 * the specified wl_buffer mask is invalid
	 */
	EXT_BLUR_MASK_MANAGER_V1_ERROR_BLUR_MASK_INVALID = 1,
};
#endif /* EXT_BLUR_MASK_MANAGER_V1_ERROR_ENUM */

#define EXT_BLUR_MASK_MANAGER_V1_GET_BLUR 0


/**
 * @ingroup iface_ext_blur_mask_manager_v1
 */
#define EXT_BLUR_MASK_MANAGER_V1_GET_BLUR_SINCE_VERSION 1

/** @ingroup iface_ext_blur_mask_manager_v1 */
static inline void
ext_blur_mask_manager_v1_set_user_data(struct ext_blur_mask_manager_v1 *ext_blur_mask_manager_v1, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) ext_blur_mask_manager_v1, user_data);
}

/** @ingroup iface_ext_blur_mask_manager_v1 */
static inline void *
ext_blur_mask_manager_v1_get_user_data(struct ext_blur_mask_manager_v1 *ext_blur_mask_manager_v1)
{
	return wl_proxy_get_user_data((struct wl_proxy *) ext_blur_mask_manager_v1);
}

static inline uint32_t
ext_blur_mask_manager_v1_get_version(struct ext_blur_mask_manager_v1 *ext_blur_mask_manager_v1)
{
	return wl_proxy_get_version((struct wl_proxy *) ext_blur_mask_manager_v1);
}

/** @ingroup iface_ext_blur_mask_manager_v1 */
static inline void
ext_blur_mask_manager_v1_destroy(struct ext_blur_mask_manager_v1 *ext_blur_mask_manager_v1)
{
	wl_proxy_destroy((struct wl_proxy *) ext_blur_mask_manager_v1);
}

/**
 * @ingroup iface_ext_blur_mask_manager_v1
 *
 * Instantiate an interface extension for the given wl_surface to request
 * blurring.
 *
 * If the given wl_surface already has a ext_blur_v1 object
 * associated, the blur_mask_exists protocol error is raised.
 */
static inline struct ext_blur_mask_v1 *
ext_blur_mask_manager_v1_get_blur(struct ext_blur_mask_manager_v1 *ext_blur_mask_manager_v1, struct wl_surface *surface)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) ext_blur_mask_manager_v1,
			 EXT_BLUR_MASK_MANAGER_V1_GET_BLUR, &ext_blur_mask_v1_interface, wl_proxy_get_version((struct wl_proxy *) ext_blur_mask_manager_v1), 0, NULL, surface);

	return (struct ext_blur_mask_v1 *) id;
}

#define EXT_BLUR_MASK_V1_SET_MASK 0
#define EXT_BLUR_MASK_V1_RELEASE 1


/**
 * @ingroup iface_ext_blur_mask_v1
 */
#define EXT_BLUR_MASK_V1_SET_MASK_SINCE_VERSION 1
/**
 * @ingroup iface_ext_blur_mask_v1
 */
#define EXT_BLUR_MASK_V1_RELEASE_SINCE_VERSION 1

/** @ingroup iface_ext_blur_mask_v1 */
static inline void
ext_blur_mask_v1_set_user_data(struct ext_blur_mask_v1 *ext_blur_mask_v1, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) ext_blur_mask_v1, user_data);
}

/** @ingroup iface_ext_blur_mask_v1 */
static inline void *
ext_blur_mask_v1_get_user_data(struct ext_blur_mask_v1 *ext_blur_mask_v1)
{
	return wl_proxy_get_user_data((struct wl_proxy *) ext_blur_mask_v1);
}

static inline uint32_t
ext_blur_mask_v1_get_version(struct ext_blur_mask_v1 *ext_blur_mask_v1)
{
	return wl_proxy_get_version((struct wl_proxy *) ext_blur_mask_v1);
}

/** @ingroup iface_ext_blur_mask_v1 */
static inline void
ext_blur_mask_v1_destroy(struct ext_blur_mask_v1 *ext_blur_mask_v1)
{
	wl_proxy_destroy((struct wl_proxy *) ext_blur_mask_v1);
}

/**
 * @ingroup iface_ext_blur_mask_v1
 *
 * Set the blur mask for the associated wl_surface. This state is
 * double-buffered and is applied on the next wl_surface.commit.
 *
 * The compositor is free to dynamically respect or ignore this hint based
 * on various conditions like hardware capabilities, surface state and
 * user preferences.
 */
static inline struct wl_buffer *
ext_blur_mask_v1_set_mask(struct ext_blur_mask_v1 *ext_blur_mask_v1)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) ext_blur_mask_v1,
			 EXT_BLUR_MASK_V1_SET_MASK, &wl_buffer_interface, wl_proxy_get_version((struct wl_proxy *) ext_blur_mask_v1), 0, NULL);

	return (struct wl_buffer *) id;
}

/**
 * @ingroup iface_ext_blur_mask_v1
 *
 * Releases this surface blur object and disables all surface blurring.
 * The change will be applied on the next wl_surface.commit.
 */
static inline void
ext_blur_mask_v1_release(struct ext_blur_mask_v1 *ext_blur_mask_v1)
{
	wl_proxy_marshal_flags((struct wl_proxy *) ext_blur_mask_v1,
			 EXT_BLUR_MASK_V1_RELEASE, NULL, wl_proxy_get_version((struct wl_proxy *) ext_blur_mask_v1), WL_MARSHAL_FLAG_DESTROY);
}

#ifdef  __cplusplus
}
#endif

#endif