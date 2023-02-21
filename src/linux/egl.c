#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "platform.h"
#include <EGL/eglext.h>

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

EGLData init_egl(struct wl_display *wl_display)
{
	EGLData eglData;

	const char *clientExtensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);

	if (clientExtensions == NULL)
	{
		if (eglGetError() == EGL_BAD_DISPLAY)
		{
			fprintf(stderr, "EGL_EXT_client_extensions not supported\n");
			exit(1);
		}
		else
		{
			fprintf(stderr, "Failed to query EGL client extensions\n");
		}
	}

	eglData.eglDisplay = eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_EXT, wl_display, NULL);
	if (eglInitialize(eglData.eglDisplay, NULL, NULL) == EGL_FALSE)
	{
		fprintf(stderr, "eglInitialize failed");
		exit(1);
	}

	EGLint major = 0;
	EGLint minor = 0;
	if (eglInitialize(eglData.eglDisplay, &major, &minor) == EGL_FALSE)
	{
		fprintf(stderr, "Failed to initialize EGL\n");
		exit(1);
	}
	else
	{
		printf("major: %d | minor: %d\n", major, minor);
		if (!((major == 1 && minor >= 4) || major >= 2))
		{
			fprintf(stderr, "Too old\n");
			exit(1);
		}
	}

	EGLint matched = 0;
	if (!eglChooseConfig(eglData.eglDisplay, config_attributes, &eglData.eglConfig, 1, &matched))
	{
		fprintf(stderr, "egl choose config failed");
		exit(1);
	}

	eglData.eglContext = eglCreateContext(eglData.eglDisplay, eglData.eglConfig, EGL_NO_CONTEXT, context_attributes);
	if (eglData.eglContext == EGL_NO_CONTEXT)
	{
		fprintf(stderr, "egl context failed");
		exit(1);
	}

	printf("successfully setup egl\n");

	return eglData;
}