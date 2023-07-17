/*

    VEX - NVSG Extension Helper
    Copyright RageComm/SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of Ragecomm and/or the original author. Ragecomm and
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

//----------------------------------------------------------------------------//
// VEX INCLUDES				                                                  //
//----------------------------------------------------------------------------//

//#include <windows.h>				// Header File For Windows
//#include <stdio.h>					// Header File For Standard Input/Output
#include <gl\gl.h>					// Header File For The OpenGL32 Library
#include <gl\glu.h>					// Header File For The GLu32 Library
#include <glew.h>

//----------------------------------------------------------------------------//
// VEX DEFINITIONS                                                            //
//----------------------------------------------------------------------------//

//const GLubyte* APIENTRY vex_err (/*SOLID LIB CONVERTION - GLenum   errCode*/);

#define VEX_EXTERN extern
VEX_EXTERN bool vex_shading_enabled;
VEX_EXTERN bool vex_setup_glsl;

#ifdef _WIN32
  #define glXGetProcAddress(x) wglGetProcAddress((LPCSTR)x)
  #define WIN32_OR_X11
#else
#ifdef _APPLE
  void setupExtensions()
  { vex_shading_enabled = true; }; // OS X already has these extensions
#else
#ifdef LINUX
  #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)(x))
  #define WIN32_OR_X11
#else
  void setupExtensions()
  { vex_shading_enabled = false; }; // just fail otherwise?
#endif
#endif
#endif

//----------------------------------------------------------------------------//
// VEX API			                                                          //
//----------------------------------------------------------------------------//

#define VEXAPI extern __declspec(dllimport)
#define VEX_GET_FUN(x) x

//----------------------------------------------------------------------------//
// NVGL DEFINES			                                                      //
//----------------------------------------------------------------------------//

#define nvglProgramStringARB VEX_GET_FUN(__glewProgramStringARB)
#define nvglDisableVertexAttribArrayARB VEX_GET_FUN(__glewDisableVertexAttribArrayARB)
#define nvglProgramLocalParameter4fvARB VEX_GET_FUN(__glewProgramLocalParameter4fvARB)
#define nvglVertexAttribPointerARB VEX_GET_FUN(__glewVertexAttribPointerARB)
#define nvglEnableVertexAttribArrayARB VEX_GET_FUN(__glewEnableVertexAttribArrayARB)

#define nvglBufferDataARB VEX_GET_FUN(__glewBufferDataARB)
#define nvglCompressedTexImage2D VEX_GET_FUN(__glewCompressedTexImage2D)
#define nvglBindBufferARB VEX_GET_FUN(__glewBindBufferARB)
#define nvglGenBuffersARB VEX_GET_FUN(__glewGenBuffersARB)
#define nvglClientActiveTextureARB VEX_GET_FUN(__glewClientActiveTextureARB)
#define nvglBufferSubDataARB VEX_GET_FUN(__glewBufferSubDataARB)
#define nvglActiveTextureARB VEX_GET_FUN(__glewActiveTextureARB)
//----------------------------------------------------------------------------//
// FUNCTION POINTERS                                                          //
//----------------------------------------------------------------------------//

VEX_EXTERN PFNGLPROGRAMSTRINGARBPROC __glewProgramStringARB;
VEX_EXTERN PFNGLDISABLEVERTEXATTRIBARRAYARBPROC __glewDisableVertexAttribArrayARB;
VEX_EXTERN PFNGLPROGRAMLOCALPARAMETER4FVARBPROC __glewProgramLocalParameter4fvARB;
VEX_EXTERN PFNGLVERTEXATTRIBPOINTERARBPROC __glewVertexAttribPointerARB;
VEX_EXTERN PFNGLENABLEVERTEXATTRIBARRAYARBPROC __glewEnableVertexAttribArrayARB;

VEX_EXTERN PFNGLBUFFERDATAARBPROC __glewBufferDataARB;
VEX_EXTERN PFNGLCOMPRESSEDTEXIMAGE2DPROC __glewCompressedTexImage2D;
VEX_EXTERN PFNGLBINDBUFFERARBPROC __glewBindBufferARB;
VEX_EXTERN PFNGLGENBUFFERSARBPROC __glewGenBuffersARB;
VEX_EXTERN PFNGLCLIENTACTIVETEXTUREARBPROC __glewClientActiveTextureARB;
VEX_EXTERN PFNGLBUFFERSUBDATAARBPROC __glewBufferSubDataARB;
VEX_EXTERN PFNGLACTIVETEXTUREARBPROC __glewActiveTextureARB;

//----------------------------------------------------------------------------//
// VEX SETUP GLSL                                                             //
//----------------------------------------------------------------------------//

VEX_EXTERN void VEX_SetupGLSL(void);

