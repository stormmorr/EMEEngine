//
// OpenGLES.h
// Include the standard header and generate the precompiled header.
//

#ifndef OGL_ES
#define OGL_ES

#include <stdint.h>
#include <list>
#include <string>
#include <stdlib.h>
#include <atomic>

#include "common/system_utils.h"
#include "common/debug.h"

#include "include/EGL/eglext.h"

#include "util/EGLPlatformParameters.h"
#include "OSWindow_EME_WIN64.h"
#include "util/Timer.h"
#include "util/EGLWindow.h"
#include "util/random_utils.h"
#include "util/shader_utils.h"
#include "util/test_utils.h"
#include "util/util_gl.h"

#if defined(ANGLE_PLATFORM_WINDOWS)
#include "util/windows/win32/Win32Window.h"
#endif

namespace angle
{

enum class ClientType
{
    // Client types used by the samples.  Add as needed.
    ES1,
    ES2,
    ES3_0,
    ES3_1,
    GL3_3_CORE,
    GL3_3_COMPATIBILITY,
    GL4_6_CORE,
    GL4_6_COMPATIBILITY,
};

class OpenGLES
{
public:
    OpenGLES(ClientType f_clientType = ClientType::ES3_0, uint32_t f_width = 1920, uint32_t f_height = 1080);
    ~OpenGLES();

    //EGLSurface CreateSurface(winrt::Windows::UI::Xaml::Controls::SwapChainPanel panel, const winrt::Windows::Foundation::Size* renderSurfaceSize, const float* renderResolutionScale);
    //void GetSurfaceDimensions(const EGLSurface surface, EGLint *width, EGLint *height);
    //void DestroySurface(const EGLSurface surface);
    void MakeCurrent(const EGLSurface surface);
    void SwapBuffers();
    void Reset();
    int run();

private:
    void Initialize();
    void Cleanup();

public:
    //EGLDisplay mEglDisplay;
    //EGLContext mEglContext;
    //EGLConfig  mEglConfig;

    std::string Name;
    ClientType clientType;
    ::uint32_t width;
    ::uint32_t height;
    bool mRunning;

    ::uint32_t mFrameCount;
    GLWindowBase* mGLWindow;
    EGLWindow* mEGLWindow;
    angle::GLESDriverType mDriverType;

    EGLPlatformParameters mPlatformParams;

    // Handle to the entry point binding library.
    std::unique_ptr<angle::Library> mEntryPointsLib;
};

};

extern OSWindow* mOSWindow;

#endif