#define SK_GL 1
#include "include/core/SkColorSpace.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/gpu/gl/GrGLAssembleInterface.h"
#include "include/gpu/gl/egl/GrGLMakeEGLInterface.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkRRect.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkBlurTypes.h"
#include <iostream>

#include <assert.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/gl.h>
#include <GLES2/gl2.h>

#include "../UIGeometry.h"
#include "../UIColor.h"
#include "globals.h"

typedef struct _UIGraphicsContext
{
    EGLSurface eglSurface;
    SkSurface *surface;
    SkCanvas *canvas;
    SkPaint paint;
} UIGraphicsContext;

extern "C"
{
    sk_sp<const GrGLInterface> interface = nullptr;
    GrDirectContext *grDirectContext = nullptr;

    GrDirectContext *getContext()
    {
        GrGLGetProc get_proc = [](void *context, const char name[]) -> GrGLFuncPtr
        {
            return eglGetProcAddress(name);
        };
        if (interface == nullptr && grDirectContext == nullptr)
        {
            interface = GrGLMakeAssembledGLESInterface(nullptr, get_proc);
            grDirectContext = GrDirectContext::MakeGL(interface).release();
        }

        return grDirectContext;
    }

    void UIGraphicsContextMakeCurrent(UIGraphicsContext *context)
    {
        if (eglMakeCurrent(UIPlatformGlobalsShared.eglData.eglDisplay, context->eglSurface, context->eglSurface, UIPlatformGlobalsShared.eglData.eglContext) == EGL_FALSE)
        {
            printf("Could not make egl context current: %d\n", eglGetError());
        }
    }

    void UIGraphicsContextClear(UIGraphicsContext *context)
    {
        context->canvas->clear(SK_ColorTRANSPARENT);
    }

    void UIGraphicsContextFlush(UIGraphicsContext *context)
    {
        context->surface->flushAndSubmit();
        if (eglSwapBuffers(UIPlatformGlobalsShared.eglData.eglDisplay, context->eglSurface) == EGL_FALSE)
        {
            fprintf(stderr, "%d: failed to swap buffers\n", eglGetError());
        }
    }

    void UIGraphicsSetFillColor(UIGraphicsContext *context, UIColor color)
    {
        context->paint.setStroke(false);
        context->paint.setARGB(color.a, color.r, color.g, color.b);
    }

    void UIGraphicsSetStrokeColor(UIGraphicsContext *context, UIColor color)
    {
        context->paint.setStroke(true);
        context->paint.setARGB(color.a, color.r, color.g, color.b);
    }

    void UIGraphicsSetStrokeWidth(UIGraphicsContext *context, float width)
    {
        context->paint.setStrokeWidth(width);
    }

    UIGraphicsContext *UIGraphicsContextCreate(EGLSurface eglSurface, int width, int height)
    {
        const char *version = (const char *)glGetString(GL_VERSION);

        // printf("Creating context with w(%d) h(%d)\n", width, height);

        UIGraphicsContext *graphicsContext = (UIGraphicsContext *)calloc(1, sizeof(UIGraphicsContext));
        graphicsContext->eglSurface = eglSurface;
        graphicsContext->paint = SkPaint();
        graphicsContext->paint.setAntiAlias(true);

        GrGLFramebufferInfo framebufferInfo;
        framebufferInfo.fFBOID = 0; // Assume default FBO (framebuffer object)
        framebufferInfo.fFormat = GL_RGBA8;

        GrBackendRenderTarget backendRenderTarget(width, height,
                                                  0, // sample count
                                                  0, // stencil bits
                                                  framebufferInfo);
        SkSurfaceProps surface_properties(0, kUnknown_SkPixelGeometry);

        SkSurface *surface = SkSurface::MakeFromBackendRenderTarget(
                                 getContext(),                // context
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
        graphicsContext->canvas = surface->getCanvas();

        SkASSERT(graphicsContext->surface != nullptr);
        SkASSERT(graphicsContext->canvas != nullptr);

        return graphicsContext;
    }

    void UIGraphicsContextDestroy(UIGraphicsContext *context)
    {
        context->canvas = nullptr;
        delete context->surface;
        free(context);
    }

    void UIGraphicsContextSave(UIGraphicsContext *context)
    {
        context->canvas->save();
    }

    void UIGraphicsContextRestore(UIGraphicsContext *context)
    {
        context->canvas->restore();
        context->paint.setMaskFilter(nullptr);
    }

    // MARK:
    void UIGraphicsContextClipToRect(UIGraphicsContext *context, UIRect rect, double radius)
    {
        SkRect skrect = SkRect::MakeXYWH(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
        SkRRect skrrect = SkRRect::MakeRectXY(skrect, radius, radius);
        context->canvas->clipRRect(skrrect, true);
    }

    void UIGraphicsContextAddRect(UIGraphicsContext *context, UIRect rect, double radius)
    {
        SkRect skrect = SkRect::MakeXYWH(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
        context->canvas->drawRoundRect(skrect, radius, radius, context->paint);
    }

    void UIGraphicsContextSetShadow(UIGraphicsContext *context, UIRect offset, float blur)
    {
        context->canvas->translate(offset.origin.x, offset.origin.y);
        context->paint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, blur, false));
    }

    void UIGraphicsContextSetTransform(UIGraphicsContext *context, int x, int y)
    {
        context->canvas->translate(x, y);
    }
}