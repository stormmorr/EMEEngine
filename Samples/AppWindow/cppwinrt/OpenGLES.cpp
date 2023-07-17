//
// OpenGLES.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"
#include "OpenGLES.h"

#include <string.h>
#include <iostream>
#include <utility>

#define ANGLE_EGL_LIBRARY_NAME "libEGL"

#if defined(ANGLE_PLATFORM_WINDOWS)
#include "util/windows/WGLWindow.h"
#endif  // defined(ANGLE_PLATFORM_WINDOWS)

OSWindow* mOSWindow;

namespace gl::priv
{
    std::ostream* gSwallowStream;
}

using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::Foundation::Collections;

using namespace angle;

namespace
{
    const char* kUseAngleArg = "--use-angle=";
    const char* kUseGlArg = "--use-gl=native";
}  // anonymous namespace

namespace angle
{

Library *OpenSharedLibrary(const char *libraryName, SearchType searchType)
{
    void *libraryHandle = OpenSystemLibraryAndGetError(libraryName, searchType, nullptr);
    return new Library(libraryHandle);
}

Library *OpenSharedLibraryWithExtension(const char *libraryName, SearchType searchType)
{
    void *libraryHandle = OpenSystemLibraryWithExtensionAndGetError(libraryName, searchType, nullptr);
    return new Library(libraryHandle);
}

Library *OpenSharedLibraryAndGetError(const char *libraryName, SearchType searchType, std::string *errorOut)
{
    void *libraryHandle = OpenSystemLibraryAndGetError(libraryName, searchType, errorOut);
    return new Library(libraryHandle);
}

Library *OpenSharedLibraryWithExtensionAndGetError(const char *libraryName, SearchType searchType, std::string *errorOut)
{
    void *libraryHandle = OpenSystemLibraryWithExtensionAndGetError(libraryName, searchType, errorOut);
    return new Library(libraryHandle);
}

void *OpenSystemLibrary(const char *libraryName, SearchType searchType)
{
    return OpenSystemLibraryAndGetError(libraryName, searchType, nullptr);
}

void *OpenSystemLibraryWithExtension(const char *libraryName, SearchType searchType)
{
    return OpenSystemLibraryWithExtensionAndGetError(libraryName, searchType, nullptr);
}

void *OpenSystemLibraryAndGetError(const char *libraryName, SearchType searchType, std::string *errorOut)
{
    std::string libraryWithExtension = std::string(libraryName);
    std::string dotExtension         = std::string(".") + GetSharedLibraryExtension();
    // Only append the extension if it's not already present. This enables building libEGL.so.1
    // and libGLESv2.so.2 by setting these as ANGLE_EGL_LIBRARY_NAME and ANGLE_GLESV2_LIBRARY_NAME.
    if (libraryWithExtension.find(dotExtension) == std::string::npos)
        {
        libraryWithExtension += dotExtension;
        }
#if ANGLE_PLATFORM_IOS_FAMILY
    // On iOS, libraryWithExtension is a directory in which the library resides.
    // The actual library name doesn't have an extension at all.
    // E.g. "libEGL.framework/libEGL"
    libraryWithExtension = libraryWithExtension + "/" + libraryName;
#endif
    return OpenSystemLibraryWithExtensionAndGetError(libraryWithExtension.c_str(), searchType, errorOut);
}

#if 0
bool UnsetEnvironmentVar(const char *variableName)
{
    return (SetEnvironmentVariableW(Widen(variableName).c_str(), nullptr) == TRUE);
}

bool SetEnvironmentVar(const char *variableName, const char *value)
{
    return (SetEnvironmentVariableW(Widen(variableName).c_str(), Widen(value).c_str()) == TRUE);
}

std::string GetEnvironmentVar(const char *variableName)
{
    std::wstring variableNameUtf16 = Widen(variableName);
    FastVector<wchar_t, MAX_PATH> value;

    DWORD result;

    // First get the length of the variable, including the null terminator
    result = GetEnvironmentVariableW(variableNameUtf16.c_str(), nullptr, 0);

    // Zero means the variable was not found, so return now.
    if (result == 0)
    {
        return std::string();
    }

    // Now size the vector to fit the data, and read the environment variable.
    value.resize(result, 0);
    result = GetEnvironmentVariableW(variableNameUtf16.c_str(), value.data(), result);

    return Narrow(value.data());
}
#endif

std::string StripFilenameFromPath(const std::string& path)
{
    size_t lastPathSepLoc = path.find_last_of("\\/");
    return (lastPathSepLoc != std::string::npos) ? path.substr(0, lastPathSepLoc) : "";
}

void *OpenSystemLibraryWithExtensionAndGetError(const char *libraryName, SearchType searchType, std::string *errorOut)
{
    char buffer[MAX_PATH];
    int ret = snprintf(buffer, MAX_PATH, "%s.%s", libraryName, GetSharedLibraryExtension());
    if (ret <= 0 || ret >= MAX_PATH)
        {
        fprintf(stderr, "Error generating library path: 0x%x", ret);
        return nullptr;
        }

    HMODULE libraryModule = nullptr;

    switch (searchType)
        {
        case SearchType::ModuleDir:
            {
            std::string moduleRelativePath = ConcatenatePath(GetModuleDirectory(), libraryName);
            libraryModule                  = LoadLibraryW(Widen(moduleRelativePath).c_str());
            if (libraryModule == nullptr && errorOut)
                {
                *errorOut = std::string("failed to load library (SearchType::ModuleDir) ") +
                            moduleRelativePath;
                }
            break;
            }

        case SearchType::SystemDir:
            {
            libraryModule =
                LoadLibraryExW(Widen(libraryName).c_str(), nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            if (libraryModule == nullptr && errorOut)
                {
                *errorOut =
                    std::string("failed to load library (SearchType::SystemDir) ") + libraryName;
                }
            break;
            }

        case SearchType::AlreadyLoaded:
            {
            libraryModule = GetModuleHandleW(Widen(libraryName).c_str());
            if (libraryModule == nullptr && errorOut)
                {
                *errorOut = std::string("failed to load library (SearchType::AlreadyLoaded) ") +
                            libraryName;
                }
            break;
            }
        }

    return reinterpret_cast<void *>(libraryModule);
}

std::string GetPath(HMODULE module)
{
    std::array<wchar_t, MAX_PATH> executableFileBuf;
    DWORD executablePathLen = GetModuleFileNameW(module, executableFileBuf.data(),
                                                 static_cast<DWORD>(executableFileBuf.size()));
    return Narrow(executablePathLen > 0 ? executableFileBuf.data() : L"");
}

std::string GetDirectory(HMODULE module)
{
    std::string executablePath = GetPath(module);
    return StripFilenameFromPath(executablePath);
}

//}  // angle namespace

std::string GetExecutablePath()
{
    return GetPath(nullptr);
}

std::string GetExecutableDirectory()
{
    return GetDirectory(nullptr);
}

const char *GetSharedLibraryExtension()
{
    return "dll";
}

Optional<std::string> GetCWD()
{
    std::array<wchar_t, MAX_PATH> pathBuf;
    DWORD result = GetCurrentDirectoryW(static_cast<DWORD>(pathBuf.size()), pathBuf.data());
    if (result == 0)
    {
        return Optional<std::string>::Invalid();
    }
    return Narrow(pathBuf.data());
}

bool SetCWD(const char *dirName)
{
    return (SetCurrentDirectoryW(Widen(dirName).c_str()) == TRUE);
}

const char *GetPathSeparatorForEnvironmentVar()
{
    return ";";
}

double GetCurrentSystemTime()
{
    LARGE_INTEGER frequency = {};
    QueryPerformanceFrequency(&frequency);

    LARGE_INTEGER curTime;
    QueryPerformanceCounter(&curTime);

    return static_cast<double>(curTime.QuadPart) / frequency.QuadPart;
}

double GetCurrentProcessCpuTime()
{
    FILETIME creationTime = {};
    FILETIME exitTime     = {};
    FILETIME kernelTime   = {};
    FILETIME userTime     = {};

    // Note this will not give accurate results if the current thread is
    // scheduled for less than the tick rate, which is often 15 ms. In that
    // case, GetProcessTimes will not return different values, making it
    // possible to end up with 0 ms for a process that takes 93% of a core
    // (14/15 ms)!  An alternative is QueryProcessCycleTime but there is no
    // simple way to convert cycles back to seconds, and on top of that, it's
    // not supported pre-Windows Vista.

    // Returns 100-ns intervals, so we want to divide by 1e7 to get seconds
    GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime);

    ULARGE_INTEGER kernelInt64;
    kernelInt64.LowPart      = kernelTime.dwLowDateTime;
    kernelInt64.HighPart     = kernelTime.dwHighDateTime;
    double systemTimeSeconds = static_cast<double>(kernelInt64.QuadPart) * 1e-7;

    ULARGE_INTEGER userInt64;
    userInt64.LowPart      = userTime.dwLowDateTime;
    userInt64.HighPart     = userTime.dwHighDateTime;
    double userTimeSeconds = static_cast<double>(userInt64.QuadPart) * 1e-7;

    return systemTimeSeconds + userTimeSeconds;
}

bool IsFullPath(std::string dirName)
{
    if (dirName.find(GetRootDirectory()) == 0)
    {
        return true;
    }
    return false;
}

std::string ConcatenatePath(std::string first, std::string second)
{
    if (first.empty())
    {
        return second;
    }
    if (second.empty())
    {
        return first;
    }
    if (IsFullPath(second))
    {
        return second;
    }
    bool firstRedundantPathSeparator = first.find_last_of(GetPathSeparator()) == first.length() - 1;
    bool secondRedundantPathSeparator = second.find(GetPathSeparator()) == 0;
    if (firstRedundantPathSeparator && secondRedundantPathSeparator)
    {
        return first + second.substr(1);
    }
    else if (firstRedundantPathSeparator || secondRedundantPathSeparator)
    {
        return first + second;
    }
    return first + GetPathSeparator() + second;
}

Optional<std::string> CreateTemporaryFile()
{
    const Optional<std::string> tempDir = GetTempDirectory();
    if (!tempDir.valid())
        return Optional<std::string>::Invalid();

    return CreateTemporaryFileInDirectory(tempDir.value());
}

PageFaultHandler::PageFaultHandler(PageFaultCallback callback) : mCallback(callback) {}
PageFaultHandler::~PageFaultHandler() {}

bool IsDirectory(const char *filename)
{
    WIN32_FILE_ATTRIBUTE_DATA fileInformation;

    BOOL result = GetFileAttributesExW(Widen(filename).c_str(), GetFileExInfoStandard, &fileInformation);
    
    if(result)
        {
        DWORD attribs = fileInformation.dwFileAttributes;
        return (attribs != INVALID_FILE_ATTRIBUTES) && ((attribs & FILE_ATTRIBUTE_DIRECTORY) > 0);
        }

    return false;
}

bool IsDebuggerAttached()
{
    return !!::IsDebuggerPresent();
}

void BreakDebugger()
{
    __debugbreak();
}

const char *GetExecutableExtension()
{
    return ".exe";
}

char GetPathSeparator()
{
    return '\\';
}

std::string GetModuleDirectory()
{
// GetModuleHandleEx is unavailable on UWP
#if !defined(ANGLE_IS_WINUWP)
    static int placeholderSymbol = 0;
    HMODULE module               = nullptr;
    if(GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(&placeholderSymbol), &module))
        {
        return GetDirectory(module);
        }
#endif

    return GetDirectory(nullptr);
}

std::string GetRootDirectory()
{
    return "C:\\";
}

Optional<std::string> GetTempDirectory()
{
    char tempDirOut[MAX_PATH + 1];
    GetTempPathA(MAX_PATH + 1, tempDirOut);
    std::string tempDir = std::string(tempDirOut);

    if(tempDir.length() < 0 || tempDir.length() > MAX_PATH)
        {
        return Optional<std::string>::Invalid();
        }

    if(tempDir.length() > 0 && tempDir.back() == '\\')
        {
        tempDir.pop_back();
        }

    return tempDir;
}

Optional<std::string> CreateTemporaryFileInDirectory(const std::string &directory)
{
    char fileName[MAX_PATH + 1];

    if(GetTempFileNameA(directory.c_str(), "ANGLE", 0, fileName) == 0)
        {
        return Optional<std::string>::Invalid();
        }

    return std::string(fileName);
}

std::string GetLibraryPath(void *libraryHandle)
{
    if(!libraryHandle)
        {
        return "";
        }

    std::array<wchar_t, MAX_PATH> buffer;

    if(GetModuleFileNameW(reinterpret_cast<HMODULE>(libraryHandle), buffer.data(), buffer.size()) == 0)
        {
        return "";
        }

    return Narrow(buffer.data());
}

void *GetLibrarySymbol(void *libraryHandle, const char *symbolName)
{
    if(!libraryHandle)
        {
        fprintf(stderr, "Module was not loaded\n");
        return nullptr;
        }

    return reinterpret_cast<void *>(GetProcAddress(reinterpret_cast<HMODULE>(libraryHandle), symbolName));
}

void CloseSystemLibrary(void *libraryHandle)
{
    if(libraryHandle)
        {
        FreeLibrary(reinterpret_cast<HMODULE>(libraryHandle));
        }
}

std::string Narrow(const std::wstring_view &utf16)
{
    if(utf16.empty())
        {
        return {};
        }

    int requiredSize = WideCharToMultiByte(CP_UTF8, 0, utf16.data(), static_cast<int>(utf16.size()),
                                           nullptr, 0, nullptr, nullptr);
    std::string utf8(requiredSize, '\0');
    WideCharToMultiByte(CP_UTF8, 0, utf16.data(), static_cast<int>(utf16.size()), &utf8[0], requiredSize, nullptr, nullptr);
    return utf8;
}

std::wstring Widen(const std::string_view &utf8)
{
    if(utf8.empty())
        {
        return {};
        }

    int requiredSize = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);
    std::wstring utf16(requiredSize, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), &utf16[0], requiredSize);
    
    return utf16;
}

bool IsGLExtensionEnabled(const std::string& extName)
{
    return angle::CheckExtensionExists(reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS)), extName);
}

//}; // angle namespace

OpenGLES::OpenGLES(ClientType f_clientType, uint32_t f_width, uint32_t f_height) :
    clientType(f_clientType),
    width(f_width),
    height(f_height),
    Name("EME-Engine"),
    mRunning(false),
    mFrameCount(0),
    mGLWindow(nullptr),
    mEGLWindow(nullptr),
    mDriverType(angle::GLESDriverType::AngleEGL)
{
    Initialize();
}

OpenGLES::~OpenGLES()
{
    Cleanup();
}

void OpenGLES::Initialize()
{
    mPlatformParams.renderer = EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE;
    bool useNativeGL         = false;

#if 0
    for(int argIndex = 1; argIndex < argc; argIndex++)
        {
        if(strncmp(argv[argIndex], kUseAngleArg, strlen(kUseAngleArg)) == 0)
            {
            const char *arg = argv[argIndex] + strlen(kUseAngleArg);
            mPlatformParams.renderer =
                angle::GetPlatformANGLETypeFromArg(arg, EGL_PLATFORM_ANGLE_TYPE_DEFAULT_ANGLE);
            mPlatformParams.deviceType = angle::GetANGLEDeviceTypeFromArg(
                arg, EGL_PLATFORM_ANGLE_DEVICE_TYPE_HARDWARE_ANGLE);
            }

        if(strncmp(argv[argIndex], kUseGlArg, strlen(kUseGlArg)) == 0)
            {
            useNativeGL = true;
            }
        }
#else
    mPlatformParams.deviceType = EGL_PLATFORM_ANGLE_DEVICE_TYPE_HARDWARE_ANGLE;
#endif

    EGLenum eglClientType = EGL_OPENGL_ES_API;
    EGLint glMajorVersion = 2;
    EGLint glMinorVersion = 0;
    EGLint profileMask    = 0;

    switch(clientType)
        {
        case ClientType::ES1:
            glMajorVersion = 1;
            break;
        case ClientType::ES2:
            break;
        case ClientType::ES3_0:
            glMajorVersion = 3;
            break;
        case ClientType::ES3_1:
            glMajorVersion = 3;
            glMinorVersion = 1;
            break;
        case ClientType::GL3_3_CORE:
            eglClientType  = EGL_OPENGL_API;
            glMajorVersion = 3;
            glMinorVersion = 3;
            profileMask    = EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT;
            break;
        case ClientType::GL3_3_COMPATIBILITY:
            eglClientType  = EGL_OPENGL_API;
            glMajorVersion = 3;
            glMinorVersion = 3;
            profileMask    = EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT;
            break;
        case ClientType::GL4_6_CORE:
            eglClientType  = EGL_OPENGL_API;
            glMajorVersion = 4;
            glMinorVersion = 6;
            profileMask    = EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT;
            break;
        case ClientType::GL4_6_COMPATIBILITY:
            eglClientType  = EGL_OPENGL_API;
            glMajorVersion = 4;
            glMinorVersion = 6;
            profileMask    = EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT;
            break;
        default:
            UNREACHABLE();
        }

    mOSWindow = OSWindow::New();

    // Load EGL library so we can initialize the display.
    if(useNativeGL)
        {
#if defined(ANGLE_PLATFORM_WINDOWS)
        mGLWindow = WGLWindow::New(eglClientType, glMajorVersion, glMinorVersion, profileMask);
        mEntryPointsLib.reset(angle::OpenSharedLibrary("opengl32", angle::SearchType::SystemDir));
        mDriverType = angle::GLESDriverType::SystemWGL;
#else
        mGLWindow = EGLWindow::New(eglClientType, glMajorVersion, glMinorVersion, profileMask);
        mEntryPointsLib.reset(angle::OpenSharedLibraryWithExtension(
            angle::GetNativeEGLLibraryNameWithExtension(), angle::SearchType::SystemDir));
        mDriverType = angle::GLESDriverType::SystemEGL;
#endif  // defined(ANGLE_PLATFORM_WINDOWS)
        }
    else
        {
#if defined(ANGLE_EXPOSE_WGL_ENTRY_POINTS)
        mGLWindow = WGLWindow::New(eglClientType, glMajorVersion, glMinorVersion, profileMask);
        mEntryPointsLib.reset(angle::OpenSharedLibrary("opengl32", angle::SearchType::ModuleDir));
        mDriverType = angle::GLESDriverType::SystemWGL;
#else
        mGLWindow = mEGLWindow = EGLWindow::New(eglClientType, glMajorVersion, glMinorVersion, profileMask);
        mEntryPointsLib.reset(angle::OpenSharedLibrary(ANGLE_EGL_LIBRARY_NAME, angle::SearchType::ModuleDir));
#endif  // defined(ANGLE_EXPOSE_WGL_ENTRY_POINTS)
        }

#if 0
    const EGLint configAttributes[] = 
    {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };

    const EGLint contextAttributes[] = 
    { 
        EGL_CONTEXT_CLIENT_VERSION, 2, 
        EGL_NONE
    };

    const EGLint defaultDisplayAttributes[] =
    {
        // These are the default display attributes, used to request ANGLE's D3D11 renderer.
        // eglInitialize will only succeed with these attributes if the hardware supports D3D11 Feature Level 10_0+.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,

        // EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER is an optimization that can have large performance benefits on mobile devices.
        // Its syntax is subject to change, though. Please update your Visual Studio templates if you experience compilation issues with it.
        /*EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER, EGL_TRUE,*/
        
        // EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE is an option that enables ANGLE to automatically call 
        // the IDXGIDevice3::Trim method on behalf of the application when it gets suspended. 
        // Calling IDXGIDevice3::Trim when an application is suspended is a Windows Store application certification requirement.
        EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE, EGL_TRUE,
        EGL_NONE,
    };
    
    const EGLint fl9_3DisplayAttributes[] =
    {
        // These can be used to request ANGLE's D3D11 renderer, with D3D11 Feature Level 9_3.
        // These attributes are used if the call to eglInitialize fails with the default display attributes.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
        EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE, 9,
        EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE, 3,
        /*EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER, EGL_TRUE,*/
        EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE, EGL_TRUE,
        EGL_NONE,
    };

    const EGLint warpDisplayAttributes[] =
    {
        // These attributes can be used to request D3D11 WARP.
        // They are used if eglInitialize fails with both the default display attributes and the 9_3 display attributes.
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
        EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE, /*EGL_PLATFORM_ANGLE_DEVICE_TYPE_WARP_ANGLE,
        EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER, EGL_TRUE,*/
        EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE, EGL_TRUE,
        EGL_NONE,
    };
    
    EGLConfig config = NULL;

    // eglGetPlatformDisplayEXT is an alternative to eglGetDisplay. It allows us to pass in display attributes, used to configure D3D11.
    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));

    if(!eglGetPlatformDisplayEXT)
        {
#if 0
        throw Exception::CreateException(E_FAIL, L"Failed to get function eglGetPlatformDisplayEXT");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        //__debugbreak();
#endif //add debug message
        }

    //
    // To initialize the display, we make three sets of calls to eglGetPlatformDisplayEXT and eglInitialize, with varying 
    // parameters passed to eglGetPlatformDisplayEXT:
    // 1) The first calls uses "defaultDisplayAttributes" as a parameter. This corresponds to D3D11 Feature Level 10_0+.
    // 2) If eglInitialize fails for step 1 (e.g. because 10_0+ isn't supported by the default GPU), then we try again 
    //    using "fl9_3DisplayAttributes". This corresponds to D3D11 Feature Level 9_3.
    // 3) If eglInitialize fails for step 2 (e.g. because 9_3+ isn't supported by the default GPU), then we try again 
    //    using "warpDisplayAttributes".  This corresponds to D3D11 Feature Level 11_0 on WARP, a D3D11 software rasterizer.
    //
    
    // This tries to initialize EGL to D3D11 Feature Level 10_0+. See above comment for details.
    mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, defaultDisplayAttributes);

    if(mEglDisplay == EGL_NO_DISPLAY)
        {
#if 0
        throw Exception::CreateException(E_FAIL, L"Failed to get EGL display");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        //__debugbreak();
#endif //add debug message
        }

    if(eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
        {
        // This tries to initialize EGL to D3D11 Feature Level 9_3, if 10_0+ is unavailable (e.g. on some mobile devices).
        mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, fl9_3DisplayAttributes);

#if 0
        if(mEglDisplay == EGL_NO_DISPLAY)
            {
            throw Exception::CreateException(E_FAIL, L"Failed to get EGL display");
            }
#endif

        if(eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
            {
            // This initializes EGL to D3D11 Feature Level 11_0 on WARP, if 9_3+ is unavailable on the default GPU.
            mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, warpDisplayAttributes);

            if(mEglDisplay == EGL_NO_DISPLAY)
                {
#if 0
                throw Exception::CreateException(E_FAIL, L"Failed to get EGL display");
#endif

#ifdef ECOIN_DEBUG_BREAKS
                __debugbreak();
#endif //add debug message
                }

            if(eglInitialize(mEglDisplay, NULL, NULL) == EGL_FALSE)
                {
#if 0
                // If all of the calls to eglInitialize returned EGL_FALSE then an error has occurred.
                throw Exception::CreateException(E_FAIL, L"Failed to initialize EGL");
#endif

#ifdef ECOIN_DEBUG_BREAKS
                __debugbreak();
#endif //add debug message
                }
            }
        }

    EGLint numConfigs = 0;

    if((eglChooseConfig(mEglDisplay, configAttributes, &mEglConfig, 1, &numConfigs) == EGL_FALSE) || (numConfigs == 0))
        {
#if 0
        throw Exception::CreateException(E_FAIL, L"Failed to choose first EGLConfig");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        __debugbreak();
#endif //add debug message
        }

    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, contextAttributes);
    if(mEglContext == EGL_NO_CONTEXT)
        {
#if 0
        throw Exception::CreateException(E_FAIL, L"Failed to create EGL context");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        __debugbreak();
#endif //add debug message
        }
#endif
}

void OpenGLES::Cleanup()
{
    GLWindowBase::Delete(&mGLWindow);
    OSWindow::Delete(&mOSWindow);
}

void OpenGLES::Reset()
{
    Cleanup();
    Initialize();
}

int OpenGLES::run()
{
    if(!mOSWindow->initialize((const std::string&)Name, (int)width, (int)height))
        {
        return -1;
        }

    mOSWindow->setVisible(true);

    ConfigParameters configParams;
    configParams.redBits     = 8;
    configParams.greenBits   = 8;
    configParams.blueBits    = 8;
    configParams.alphaBits   = 8;
    configParams.depthBits   = 24;
    configParams.stencilBits = 8;

    if(!mGLWindow->initializeGL(mOSWindow, mEntryPointsLib.get(), mDriverType, mPlatformParams, configParams))
        {
        return -1;
        }

    // Disable vsync
    if(!mGLWindow->setSwapInterval(0))
        {
        return -1;
        }

    mRunning   = true;
    int result = 0;

#if defined(ANGLE_ENABLE_ASSERTS)
    if(IsGLExtensionEnabled("GL_KHR_debug"))
        {
        EnableDebugCallback(nullptr, nullptr);
        }
#endif

#if 0
    mTimer.start();
    double prevTime = 0.0;

    while (mRunning)
        {
        double elapsedTime = mTimer.getElapsedWallClockTime();
        double deltaTime   = elapsedTime - prevTime;

        step(static_cast<float>(deltaTime), elapsedTime);

        // Clear events that the application did not process from this frame
        Event event;
        while(popEvent(&event))
            {
            // If the application did not catch a close event, close now
            switch (event.Type)
                {
                case Event::EVENT_CLOSED:
                    exit();
                    break;
                case Event::EVENT_KEY_RELEASED:
                    onKeyUp(event.Key);
                    break;
                case Event::EVENT_KEY_PRESSED:
                    onKeyDown(event.Key);
                    break;
                default:
                    break;
                }
            }

        if(!mRunning)
            {
            break;
            }

        draw();
        swap();

        mOSWindow->messageLoop();

        prevTime = elapsedTime;

        mFrameCount++;

        if (mFrameCount % 100 == 0)
            {
            printf("Rate: %0.2lf frames / second\n",
                   static_cast<double>(mFrameCount) / mTimer.getElapsedWallClockTime());
            }
        }

    destroy();
    mGLWindow->destroyGL();
    mOSWindow->destroy();
#endif

    return result;
}

#if 0
EGLSurface OpenGLES::CreateSurface(winrt::Windows::UI::Xaml::Controls::SwapChainPanel panel, const winrt::Windows::Foundation::Size* renderSurfaceSize, const float* resolutionScale)
{
    if(!panel)
        {
#if 0
        throw winrt::Exception::CreateException(E_INVALIDARG, L"SwapChainPanel parameter is invalid");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        __debugbreak();
#endif //add debug message
        }
    
    if(renderSurfaceSize != nullptr && resolutionScale != nullptr)
        {
#if 0
        throw Exception::CreateException(E_INVALIDARG, L"A size and a scale can't both be specified");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        __debugbreak();
#endif //add debug message
        }

    EGLSurface surface = EGL_NO_SURFACE;

    const EGLint surfaceAttributes[] =
        {
        // EGL_ANGLE_SURFACE_RENDER_TO_BACK_BUFFER is part of the same optimization as EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER (see above).
        // If you have compilation issues with it then please update your Visual Studio templates.
        /*EGL_ANGLE_SURFACE_RENDER_TO_BACK_BUFFER, EGL_TRUE,*/
        EGL_NONE
        };
    
    // Create a PropertySet and initialize with the EGLNativeWindowType.
    winrt::Windows::Foundation::Collections::PropertySet surfaceCreationProperties;

    surfaceCreationProperties.Insert((winrt::hstring)(EGLNativeWindowTypeProperty), panel);

    // If a render surface size is specified, add it to the surface creation properties
    if(renderSurfaceSize != nullptr)
        {
        surfaceCreationProperties.Insert((winrt::hstring)(EGLRenderSurfaceSizeProperty), winrt::Windows::Foundation::PropertyValue::CreateSingle(renderSurfaceSize->Height));
        }

    // If a resolution scale is specified, add it to the surface creation properties
    if(resolutionScale != nullptr)
        {
        surfaceCreationProperties.Insert((winrt::hstring)(EGLRenderResolutionScaleProperty), winrt::Windows::Foundation::PropertyValue::CreateSingle(*(resolutionScale)));
        }

#if 0
    EGLNativeWindowType win = reinterpret_cast<EGLNativeWindowType>(&surfaceCreationProperties);
#else
    EGLNativeWindowType win = static_cast<EGLNativeWindowType>(winrt::get_abi(surfaceCreationProperties));
#endif

    surface = eglCreateWindowSurface(mEglDisplay, mEglConfig, win, surfaceAttributes);

    if(surface == EGL_NO_SURFACE)
        {
#if 0
        throw Exception::CreateException(E_FAIL, L"Failed to create EGL surface");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        __debugbreak();
#endif //add debug message
        }

    return surface;
}

void OpenGLES::GetSurfaceDimensions(const EGLSurface surface, EGLint* width, EGLint* height)
{
    eglQuerySurface(mEglDisplay, surface, EGL_WIDTH, width);
    eglQuerySurface(mEglDisplay, surface, EGL_HEIGHT, height);
}

void OpenGLES::DestroySurface(const EGLSurface surface)
{
    if(mEglDisplay != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE)
        {
        eglDestroySurface(mEglDisplay, surface);
        }
}
#endif

void OpenGLES::MakeCurrent(const EGLSurface surface)
{
    if(mEGLWindow->makeCurrent(surface, surface, mEGLWindow->getContext()) == EGL_FALSE)
        {
#if 0
        throw Exception::CreateException(E_FAIL, L"Failed to make EGLSurface current");
#endif

#ifdef ECOIN_DEBUG_BREAKS
        __debugbreak();
#endif //add debug message
        }
}

void OpenGLES::SwapBuffers(void)
{
    mGLWindow->swap();
}

}; // angle namespace

namespace gl
{

LogMessage::LogMessage(const char* file, const char* function, int line, LogSeverity severity) : mLine(0), mSeverity(0)
{
/**/
}

LogMessage::~LogMessage()
{
/**/
}

namespace priv
{
    bool ShouldCreatePlatformLogMessage(int f_int)
        {
        return false;
        }
}

};