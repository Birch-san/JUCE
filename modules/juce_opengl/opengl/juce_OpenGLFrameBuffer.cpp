/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

BEGIN_JUCE_NAMESPACE

#if JUCE_WINDOWS
enum
{
    GL_FRAMEBUFFER_EXT = 0x8D40,
    GL_RENDERBUFFER_EXT = 0x8D41,
    GL_COLOR_ATTACHMENT0_EXT = 0x8CE0,
    GL_DEPTH_ATTACHMENT_EXT = 0x8D00,
    GL_STENCIL_ATTACHMENT_EXT = 0x8D20,
    GL_FRAMEBUFFER_COMPLETE_EXT = 0x8CD5,
    GL_DEPTH24_STENCIL8_EXT = 0x88F0,
    GL_RENDERBUFFER_DEPTH_SIZE_EXT = 0x8D54
};
#endif

#if JUCE_WINDOWS || JUCE_LINUX

#define FRAMEBUFFER_FUNCTION_LIST(USE_FUNCTION) \
    USE_FUNCTION (glIsRenderbufferEXT,                          GLboolean, (GLuint renderbuffer))\
    USE_FUNCTION (glBindRenderbufferEXT,                        void, (GLenum target, GLuint renderbuffer))\
    USE_FUNCTION (glDeleteRenderbuffersEXT,                     void, (GLsizei n, const GLuint *renderbuffers))\
    USE_FUNCTION (glGenRenderbuffersEXT,                        void, (GLsizei n, GLuint *renderbuffers))\
    USE_FUNCTION (glRenderbufferStorageEXT,                     void, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height))\
    USE_FUNCTION (glGetRenderbufferParameterivEXT,              void, (GLenum target, GLenum pname, GLint* params))\
    USE_FUNCTION (glIsFramebufferEXT,                           GLboolean, (GLuint framebuffer))\
    USE_FUNCTION (glBindFramebufferEXT,                         void, (GLenum target, GLuint framebuffer))\
    USE_FUNCTION (glDeleteFramebuffersEXT,                      void, (GLsizei n, const GLuint *framebuffers))\
    USE_FUNCTION (glGenFramebuffersEXT,                         void, (GLsizei n, GLuint *framebuffers))\
    USE_FUNCTION (glCheckFramebufferStatusEXT,                  GLenum, (GLenum target))\
    USE_FUNCTION (glFramebufferTexture1DEXT,                    void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))\
    USE_FUNCTION (glFramebufferTexture2DEXT,                    void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level))\
    USE_FUNCTION (glFramebufferTexture3DEXT,                    void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset))\
    USE_FUNCTION (glFramebufferRenderbufferEXT,                 void, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer))\
    USE_FUNCTION (glGetFramebufferAttachmentParameterivEXT,     void, (GLenum target, GLenum attachment, GLenum pname, GLint *params))\
    USE_FUNCTION (glGenerateMipmapEXT,                          void, (GLenum target))\

#if JUCE_WINDOWS
 #define APICALLTYPE __stdcall
#else
 #define APICALLTYPE
#endif

#define DECLARE_FUNCTION(name, returnType, params) \
  typedef returnType (APICALLTYPE * type_ ## name) params; static type_ ## name name;
FRAMEBUFFER_FUNCTION_LIST (DECLARE_FUNCTION)
#undef DECLARE_FUNCTION

static bool framebufferFunctionsInitialised = false;

static void initialiseFrameBufferFunctions()
{
    if (! framebufferFunctionsInitialised)
    {
        framebufferFunctionsInitialised = true;

       #if JUCE_LINUX
        #define JUCE_LOOKUP_FUNCTION(name) glXGetProcAddress ((const GLubyte*) name)
       #else
        #define JUCE_LOOKUP_FUNCTION(name) wglGetProcAddress (name)
       #endif

       #define FIND_FUNCTION(name, returnType, params) name = (type_ ## name) JUCE_LOOKUP_FUNCTION (#name);
        FRAMEBUFFER_FUNCTION_LIST (FIND_FUNCTION)
       #undef FIND_FUNCTION
       #undef JUCE_LOOKUP_FUNCTION
    }
}

#undef FRAMEBUFFER_FUNCTION_LIST

//==============================================================================
#elif JUCE_OPENGL_ES

#define glIsRenderbufferEXT                         glIsRenderbufferOES
#define glBindRenderbufferEXT                       glBindRenderbufferOES
#define glDeleteRenderbuffersEXT                    glDeleteRenderbuffersOES
#define glGenRenderbuffersEXT                       glGenRenderbuffersOES
#define glRenderbufferStorageEXT                    glRenderbufferStorageOES
#define glGetRenderbufferParameterivEXT             glGetRenderbufferParameterivOES
#define glIsFramebufferEXT                          glIsFramebufferOES
#define glBindFramebufferEXT                        glBindFramebufferOES
#define glDeleteFramebuffersEXT                     glDeleteFramebuffersOES
#define glGenFramebuffersEXT                        glGenFramebuffersOES
#define glCheckFramebufferStatusEXT                 glCheckFramebufferStatusOES
#define glFramebufferTexture1DEXT                   glFramebufferTexture1DOES
#define glFramebufferTexture2DEXT                   glFramebufferTexture2DOES
#define glFramebufferTexture3DEXT                   glFramebufferTexture3DOES
#define glFramebufferRenderbufferEXT                glFramebufferRenderbufferOES
#define glGetFramebufferAttachmentParameterivEXT    glGetFramebufferAttachmentParameterivOES
#define glGenerateMipmapEXT                         glGenerateMipmapOES

#define GL_FRAMEBUFFER_EXT                          GL_FRAMEBUFFER_OES
#define GL_RGBA8                                    GL_RGBA
#define GL_COLOR_ATTACHMENT0_EXT                    GL_COLOR_ATTACHMENT0_OES
#define GL_RENDERBUFFER_EXT                         GL_RENDERBUFFER_OES
#define GL_DEPTH24_STENCIL8_EXT                     GL_DEPTH24_STENCIL8_OES
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT              GL_RENDERBUFFER_DEPTH_SIZE_OES
#define GL_DEPTH_ATTACHMENT_EXT                     GL_DEPTH_ATTACHMENT_OES
#define GL_STENCIL_ATTACHMENT_EXT                   GL_STENCIL_ATTACHMENT_OES
#define GL_FRAMEBUFFER_COMPLETE_EXT                 GL_FRAMEBUFFER_COMPLETE_OES
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT              GL_FRAMEBUFFER_UNSUPPORTED_OES
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT    GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES

#endif

//==============================================================================
class OpenGLFrameBuffer::Pimpl
{
public:
    Pimpl (const int width_, const int height_,
           const bool wantsDepthBuffer, const bool wantsStencilBuffer,
           const GLenum textureType = GL_TEXTURE_2D)
        : width (width_),
          height (height_),
          textureID (0),
          frameBufferHandle (0),
          depthOrStencilBuffer (0),
          hasDepthBuffer (false),
          hasStencilBuffer (false),
          ok (false)
    {
       #if JUCE_WINDOWS || JUCE_LINUX
        initialiseFrameBufferFunctions();

        if (glGenFramebuffersEXT == nullptr)
            return;
       #endif

        OpenGLHelpers::resetErrorState();

        glGenFramebuffersEXT (1, &frameBufferHandle);
        glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, frameBufferHandle);

        glGenTextures (1, &textureID);
        glBindTexture (textureType, textureID);
        glTexImage2D (textureType, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

        glTexParameterf (textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf (textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf (textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf (textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2DEXT (GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, textureType, textureID, 0);

        if (wantsDepthBuffer || wantsStencilBuffer)
        {
            glGenRenderbuffersEXT (1, &depthOrStencilBuffer);
            glBindRenderbufferEXT (GL_RENDERBUFFER_EXT, depthOrStencilBuffer);
            jassert (glIsRenderbufferEXT (depthOrStencilBuffer));

            if (wantsDepthBuffer && wantsStencilBuffer)
            {
                glRenderbufferStorageEXT (GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT, width, height);

                GLint params = 0;
                glGetRenderbufferParameterivEXT (GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_DEPTH_SIZE_EXT, &params);

                glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthOrStencilBuffer);
                glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthOrStencilBuffer);

                hasDepthBuffer = true;
                hasStencilBuffer = true;
            }
            else
            {
               #if JUCE_OPENGL_ES
                glRenderbufferStorageEXT (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT16, width, height);
               #else
                glRenderbufferStorageEXT (GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
               #endif

                GLint params = 0;
                glGetRenderbufferParameterivEXT (GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_DEPTH_SIZE_EXT, &params);
                glFramebufferRenderbufferEXT (GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthOrStencilBuffer);

                hasDepthBuffer = true;
            }
        }

        ok = checkStatus();

        glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, 0);
    }

    ~Pimpl()
    {
        if (textureID != 0)
            glDeleteTextures (1, &textureID);

        if (depthOrStencilBuffer != 0)
            glDeleteRenderbuffersEXT (1, &depthOrStencilBuffer);

        if (frameBufferHandle != 0)
            glDeleteFramebuffersEXT (1, &frameBufferHandle);
    }

    bool bind()    { return bind (frameBufferHandle); }
    bool unbind()  { return bind (0); }

    const int width, height;
    GLuint textureID, frameBufferHandle, depthOrStencilBuffer;
    bool hasDepthBuffer, hasStencilBuffer, ok;

private:
    bool bind (GLuint buffer)
    {
        if (ok)
        {
            glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, buffer);
            ok = checkStatus();
        }

        return ok;
    }

    static bool checkStatus() noexcept
    {
        const GLenum status = glCheckFramebufferStatusEXT (GL_FRAMEBUFFER_EXT);

        return status == GL_NO_ERROR
            || status == GL_FRAMEBUFFER_COMPLETE_EXT;
    }

    JUCE_DECLARE_NON_COPYABLE (Pimpl);
};

//==============================================================================
class OpenGLFrameBuffer::SavedState
{
public:
    SavedState (OpenGLFrameBuffer& buffer, const int w, const int h)
        : width (w), height (h),
          data (w * h)
    {
        buffer.readPixels (data, Rectangle<int> (0, 0, w, h));
    }

    bool restore (OpenGLFrameBuffer& buffer)
    {
        if (buffer.initialise (width, height))
        {
            buffer.writePixels (data, 4, Rectangle<int> (0, 0, width, height));
            return true;
        }

        return false;
    }

private:
    const int width, height;
    HeapBlock <int32> data;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SavedState);
};

//==============================================================================
OpenGLFrameBuffer::OpenGLFrameBuffer() {}
OpenGLFrameBuffer::~OpenGLFrameBuffer() {}

bool OpenGLFrameBuffer::initialise (int width, int height)
{
    pimpl = nullptr;
    pimpl = new Pimpl (width, height, false, false);

    if (! pimpl->ok)
        pimpl = nullptr;

    return pimpl != nullptr;
}

bool OpenGLFrameBuffer::initialise (const Image& image)
{
    if (initialise (image.getWidth(), image.getHeight()))
    {
        {
            Image::BitmapData bitmap (image, Image::BitmapData::readOnly);

            if (bitmap.lineStride == image.getWidth() * bitmap.pixelStride)
                return writePixels (bitmap.data, bitmap.pixelStride, image.getBounds());
        }

        return initialise (Image (image.getSharedImage()->clone()));
    }

    return false;
}

bool OpenGLFrameBuffer::initialise (const OpenGLFrameBuffer& other)
{
    const Pimpl* const p = other.pimpl;

    if (p == nullptr)
    {
        pimpl = nullptr;
        return true;
    }

    if (initialise (p->width, p->height))
    {
        pimpl->bind();
        glDisable (GL_BLEND);
        glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
        other.drawAt (0, 0);
        pimpl->unbind();
    }

    return false;
}

void OpenGLFrameBuffer::release()
{
    pimpl = nullptr;
    savedState = nullptr;
}

void OpenGLFrameBuffer::saveAndRelease()
{
    if (pimpl != nullptr)
    {
        savedState = new SavedState (*this, pimpl->width, pimpl->height);
        pimpl = nullptr;
    }
}

bool OpenGLFrameBuffer::reloadSavedCopy()
{
    if (savedState != nullptr)
    {
        ScopedPointer<SavedState> state (savedState);

        if (state->restore (*this))
            return true;

        savedState = state;
    }

    return false;
}

int OpenGLFrameBuffer::getWidth() const noexcept            { return pimpl != nullptr ? pimpl->width : 0; }
int OpenGLFrameBuffer::getHeight() const noexcept           { return pimpl != nullptr ? pimpl->height : 0; }
GLuint OpenGLFrameBuffer::getTextureID() const noexcept     { return pimpl != nullptr ? pimpl->textureID : 0; }

bool OpenGLFrameBuffer::makeCurrentRenderingTarget()
{
    // trying to use a framebuffer after saving it with saveAndRelease()! Be sure to call
    // reloadSavedCopy() to put it back into GPU memory before using it..
    jassert (savedState == nullptr);

    return pimpl != nullptr && pimpl->bind();
}

void OpenGLFrameBuffer::releaseAsRenderingTarget()
{
    if (pimpl != nullptr)
        pimpl->unbind();
}

void OpenGLFrameBuffer::clear (const Colour& colour)
{
    if (makeCurrentRenderingTarget())
    {
        OpenGLHelpers::clear (colour);
        releaseAsRenderingTarget();
    }
}

void OpenGLFrameBuffer::makeCurrentAndClear()
{
    if (makeCurrentRenderingTarget())
    {
        glClearColor (0, 0, 0, 0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
}

bool OpenGLFrameBuffer::readPixels (void* target, const Rectangle<int>& area)
{
    if (! makeCurrentRenderingTarget())
        return false;

    glPixelStorei (GL_PACK_ALIGNMENT, 4);
    glReadPixels (area.getX(), area.getY(), area.getWidth(), area.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, target);

    glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, 0);

    return true;
}

bool OpenGLFrameBuffer::writePixels (const void* data, int pixelStride, const Rectangle<int>& area)
{
    if (! makeCurrentRenderingTarget())
        return false;

    jassert (pixelStride == 3 || pixelStride == 4); // can only handle RGB or ARGB
    const int format = pixelStride == 3 ? GL_RGB : GL_BGRA_EXT;
    const int invertedY = pimpl->height - area.getBottom();

    OpenGLHelpers::prepareFor2D (pimpl->width, pimpl->height);
    glDisable (GL_DEPTH_TEST);
    glDisable (GL_BLEND);

   #if JUCE_OPENGL_ES
    // GLES has no glDrawPixels function, so we have to create a texture and draw it..
    GLuint temporaryTexture = 0;
    glGenTextures (1, &temporaryTexture);
    jassert (temporaryTexture != 0); // can't create a texture!

    if (temporaryTexture != 0)
    {
        glEnable (GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, temporaryTexture);

        glPixelStorei (GL_UNPACK_ALIGNMENT, pixelStride);
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, area.getWidth(), area.getHeight(), 0,
                      format, GL_UNSIGNED_BYTE, data);

        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        const int cropRect[4] = { 0, 0, area.getWidth(), area.getHeight() };
        glTexParameteriv (GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, cropRect);

        glDrawTexiOES (area.getX(), invertedY, 1, area.getWidth(), area.getHeight());

        glBindTexture (GL_TEXTURE_2D, 0);
        glDeleteTextures (1, &temporaryTexture);
    }

   #else
    glRasterPos2i (area.getX(), invertedY);
    glBindTexture (GL_TEXTURE_2D, 0);
    glPixelStorei (GL_UNPACK_ALIGNMENT, pixelStride);
    glPixelStorei (GL_UNPACK_ROW_LENGTH, 0);
    glDrawPixels (area.getWidth(), area.getHeight(), format, GL_UNSIGNED_BYTE, data);
   #endif

    glBindFramebufferEXT (GL_FRAMEBUFFER_EXT, 0);

    return true;
}

void OpenGLFrameBuffer::draw2D (float x1, float y1,
                                float x2, float y2,
                                float x3, float y3,
                                float x4, float y4,
                                const Colour& colour) const
{
    if (pimpl != nullptr)
    {
        glBindTexture (GL_TEXTURE_2D, pimpl->textureID);
        OpenGLHelpers::drawQuad2D (x1, y1, x2, y2, x3, y3, x4, y4, colour);
        glBindTexture (GL_TEXTURE_2D, 0);
    }
}

void OpenGLFrameBuffer::draw3D (float x1, float y1, float z1,
                                float x2, float y2, float z2,
                                float x3, float y3, float z3,
                                float x4, float y4, float z4,
                                const Colour& colour) const
{
    if (pimpl != nullptr)
    {
        glBindTexture (GL_TEXTURE_2D, pimpl->textureID);
        OpenGLHelpers::drawQuad3D (x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, colour);
        glBindTexture (GL_TEXTURE_2D, 0);
    }
}

void OpenGLFrameBuffer::drawAt (float x1, float y1) const
{
    if (pimpl != nullptr)
    {
        glEnable (GL_TEXTURE_2D);
        glBindTexture (GL_TEXTURE_2D, pimpl->textureID);

        glDisableClientState (GL_COLOR_ARRAY);
        glDisableClientState (GL_NORMAL_ARRAY);

        const GLfloat vertices[] = { x1, y1,
                                     x1 + pimpl->width, y1,
                                     x1, y1 + pimpl->height,
                                     x1 + pimpl->width, y1 + pimpl->height };

        const GLfloat textureCoords[] = { 0, 0, 1.0f, 0, 0, 1.0f, 1.0f, 1.0f };

        glEnableClientState (GL_VERTEX_ARRAY);
        glVertexPointer (2, GL_FLOAT, 0, vertices);

        glEnableClientState (GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer (2, GL_FLOAT, 0, textureCoords);

        glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture (GL_TEXTURE_2D, 0);
    }
}

//==============================================================================
void OpenGLFrameBuffer::createAlphaChannelFromPath (const Path& path, const AffineTransform& transform,
                                                    const int oversamplingLevel)
{
    makeCurrentRenderingTarget();

    glEnableClientState (GL_VERTEX_ARRAY);
    glEnableClientState (GL_TEXTURE_COORD_ARRAY);
    glDisableClientState (GL_COLOR_ARRAY);
    glDisableClientState (GL_NORMAL_ARRAY);
    glDisable (GL_TEXTURE_2D);
    glDisable (GL_DEPTH_TEST);
    glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glEnable (GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE);

    prepareFor2D();
    TriangulatedPath (path, transform).draw (oversamplingLevel);
}

END_JUCE_NAMESPACE
