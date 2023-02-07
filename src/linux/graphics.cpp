#define SK_GL 1
#include "include/core/SkColorSpace.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/gpu/gl/GrGLAssembleInterface.h"
#include "include/gpu/gl/egl/GrGLMakeEGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include <iostream>

#include <assert.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/gl.h>
#include <GLES2/gl2.h>

#include "../UIRect.h"
#include "../UIColor.h"

typedef struct _UIGraphicsContext
{
    GrDirectContext *context;
    SkSurface *surface;
    SkCanvas *canvas;
    SkPaint *paint;
} UIGraphicsContext;

extern "C"
{
    static GrGLFuncPtr get_proc_address(void *context, const char name[])
    {
        printf("Being called!!! %s\n", name);
        GrGLFuncPtr func = eglGetProcAddress(name);
        return func;
    };

    void UIGraphicsContextFlush(UIGraphicsContext *context) {
        context->surface->flushAndSubmit();
    }

    void UIGraphicsSetFillColor(UIGraphicsContext *context, UIColor color) {
        context->paint->setARGB(color.a, color.r, color.g, color.b);
    }

    UIGraphicsContext *UIGraphicsContextCreate(int width, int height, EGLDisplay eglDisplay, EGLSurface eglSurface, EGLContext eglContext)
    {
        printf("get_proc_address: %p\n", &get_proc_address);

        const char *version = (const char*)glGetString(GL_VERSION);
        printf("opengl version: %s\n", version);

        printf("before\n");
        auto interface = GrGLMakeAssembledGLESInterface(nullptr, &get_proc_address);
        if (!interface)
        {
            printf("Error: GrGLMakeEGLInterface returned null\n");
            return nullptr;
        }
        SkASSERT(interface != nullptr);

        UIGraphicsContext *graphicsContext = (UIGraphicsContext *)malloc(sizeof(UIGraphicsContext));
        graphicsContext->paint = (SkPaint*)malloc(sizeof(SkPaint));

        graphicsContext->context = GrDirectContext::MakeGL(interface).release();
        SkASSERT(graphicsContext->context != nullptr);

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0; // assume default framebuffer
        // We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
        // framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
        framebufferInfo.fFormat = GL_RGBA8;

        GrBackendRenderTarget backendRenderTarget(width, height,
                                                  0, // sample count
                                                  0, // stencil bits
                                                  framebufferInfo);

        SkSurfaceProps surface_properties(0, kUnknown_SkPixelGeometry);

        SkSurface *surface = SkSurface::MakeFromBackendRenderTarget(
                                 graphicsContext->context,    // context
                                 backendRenderTarget,         // backend render target
                                 kBottomLeft_GrSurfaceOrigin, // surface origin
                                 kN32_SkColorType,            // color type
                                 SkColorSpace::MakeSRGB(),    // color space
                                 &surface_properties,         // surface properties
                                 nullptr,                     // release proc
                                 nullptr                      // release context
                                 )
                                 .release();

        graphicsContext->surface = surface;

        return graphicsContext;
    }

    void UIGraphicsContextSave(UIGraphicsContext *context)
    {
        context->canvas->save();
    }
    void UIGraphicsContextRestore(UIGraphicsContext *context)
    {
        context->canvas->restore();
    }

    // MARK:
    void UIGraphicsContextClipToRect(UIGraphicsContext *context, UIRect rect)
    {
        SkRect skrect = SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
        context->surface->getCanvas()->clipRect(skrect, true);
    }

    void UIGraphicsContextAddRect(UIGraphicsContext *context, UIRect rect, double radius)
    {
        SkRect skrect = SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
        context->surface->getCanvas()->drawRoundRect(skrect, radius, radius, *context->paint);
    }
}