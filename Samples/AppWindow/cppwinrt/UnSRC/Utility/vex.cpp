/*

    VEX - NVSG Extension Helper
    Copyright RageComm/SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of Ragecomm and/or the original author. Ragecomm and
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "vex.h"

/// Template Unknown Address
#include "Terrain/icTrr.h"

//----------------------------------------------------------------------------//
// VEX DECLARATIONS                                                           //
//----------------------------------------------------------------------------//

bool vex_shading_enabled = false;
bool vex_setup_glsl = false;

//----------------------------------------------------------------------------//
// FUNCTION POINTERS                                                          //
//----------------------------------------------------------------------------//

PFNGLPROGRAMSTRINGARBPROC __glewProgramStringARB = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC __glewDisableVertexAttribArrayARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC __glewProgramLocalParameter4fvARB = NULL;
PFNGLVERTEXATTRIBPOINTERARBPROC __glewVertexAttribPointerARB = NULL;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC __glewEnableVertexAttribArrayARB = NULL;

PFNGLBUFFERDATAARBPROC __glewBufferDataARB = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC __glewCompressedTexImage2D = NULL;
PFNGLBINDBUFFERARBPROC __glewBindBufferARB = NULL;
PFNGLGENBUFFERSARBPROC __glewGenBuffersARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC __glewClientActiveTextureARB = NULL;
PFNGLBUFFERSUBDATAARBPROC __glewBufferSubDataARB = NULL;
PFNGLACTIVETEXTUREARBPROC __glewActiveTextureARB = NULL;

//----------------------------------------------------------------------------//
// VEX SETUP GLSL                                                             //
//----------------------------------------------------------------------------//

void VEX_SetupGLSL(void)
{
if(!vex_setup_glsl)
	{
	printf("Entering VEX_SetupGLSL... ");

	GLboolean err = GL_FALSE;
	err = ((nvglProgramStringARB = (PFNGLPROGRAMSTRINGARBPROC)glXGetProcAddress((const GLubyte*)"glProgramStringARB")) == NULL) || err;
	err = ((nvglDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC)glXGetProcAddress((const GLubyte*)"glDisableVertexAttribArrayARB")) == NULL) || err;
	err = ((nvglProgramLocalParameter4fvARB = (PFNGLPROGRAMLOCALPARAMETER4FVARBPROC)glXGetProcAddress((const GLubyte*)"glProgramLocalParameter4fvARB")) == NULL) || err;
	err = ((nvglVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC)glXGetProcAddress((const GLubyte*)"glVertexAttribPointerARB")) == NULL) || err;
	err = ((nvglEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC)glXGetProcAddress((const GLubyte*)"glEnableVertexAttribArrayARB")) == NULL) || err;

	err = ((nvglBufferDataARB = (PFNGLBUFFERDATAARBPROC)glXGetProcAddress((const GLubyte*)"glBufferDataARB")) == NULL) || err;
	err = ((nvglCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)glXGetProcAddress((const GLubyte*)"glCompressedTexImage2D")) == NULL) || err;
	err = ((nvglBindBufferARB = (PFNGLBINDBUFFERARBPROC)glXGetProcAddress((const GLubyte*)"glBindBufferARB")) == NULL) || err;
	err = ((nvglGenBuffersARB = (PFNGLGENBUFFERSARBPROC)glXGetProcAddress((const GLubyte*)"glGenBuffersARB")) == NULL) || err;
	err = ((nvglClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)glXGetProcAddress((const GLubyte*)"glClientActiveTextureARB")) == NULL) || err;
	err = ((nvglBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)glXGetProcAddress((const GLubyte*)"glBufferSubDataARB")) == NULL) || err;
	err = ((nvglActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)glXGetProcAddress((const GLubyte*)"glActiveTextureARB")) == NULL) || err;

	if(err == GL_FALSE) printf("vex_shading_enabled\n");
	else printf("VEX-ERROR\n");
	}

vex_setup_glsl = true;
}

void trrBinaryCube::mkTemplate(int Template)
{
	if(Template == 0)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 0;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 0;
		bit[1][0][1] = 0;
		bit[2][0][1] = 0;

		bit[0][0][2] = 0;
		bit[1][0][2] = 0;
		bit[2][0][2] = 0;
		}

	if(Template == 1)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 0;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 1;

		bit[0][0][1] = 0;
		bit[1][0][1] = 0;
		bit[2][0][1] = 1;

		bit[0][0][2] = 0;
		bit[1][0][2] = 0;
		bit[2][0][2] = 1;
		}

	if(Template == 2)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 0;

		bit[0][0][1] = 0;
		bit[1][0][1] = 0;
		bit[2][0][1] = 0;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 3)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 0;
		bit[2][0][0] = 0;

		bit[0][0][1] = 1;
		bit[1][0][1] = 0;
		bit[2][0][1] = 0;

		bit[0][0][2] = 1;
		bit[1][0][2] = 0;
		bit[2][0][2] = 0;
		}

	/// Reverse Angular Refusal
	if(Template == 4)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 0;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 5)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 0;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 6)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 7)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 1;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 1;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	/// Mirror Refusal
	if(Template == 8)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 0;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 0;
		bit[1][0][2] = 0;
		bit[2][0][2] = 0;
		}

	if(Template == 9)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 0;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 10)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 0;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 0;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 0;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 0;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 0;
		}

	if(Template == 11)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 0;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 0;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 0;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 12)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 0;

		bit[0][0][1] = 0;
		bit[1][0][1] = 0;
		bit[2][0][1] = 0;

		bit[0][0][2] = 0;
		bit[1][0][2] = 0;
		bit[2][0][2] = 0;
		}

	if(Template == 13)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	/// Cross Angle
	if(Template == 14)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 1;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 0;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 0;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 0;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 0;
		bit[1][0][2] = 0;
		bit[2][0][2] = 1;
		}

	if(Template == 15)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 0;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 1;
		bit[1][1][0] = 0;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 0;
		bit[2][0][0] = 0;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 0;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 16)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 0;

		bit[0][2][2] = 1;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 0;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 0;

		bit[0][0][2] = 1;
		bit[1][0][2] = 0;
		bit[2][0][2] = 0;
		}

	if(Template == 17)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 1;

		bit[0][1][1] = 0;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 1;

		bit[0][0][1] = 0;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 18)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 19)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 20)
		{
		bit[0][2][0] = 1;
		bit[1][2][0] = 1;
		bit[2][2][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 21)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 22)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][1][2] = 0;
		bit[1][1][2] = 0;
		bit[2][1][2] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

		/// NEW! FORMAT CHANGE TO Z BLOCKS
	if(Template == 23)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

#if 0	/// Add when convert strips
	if(Template == 24)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][1][0] = 0;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][1][1] = 0;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][2] = 0;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 25)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 0;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 0;
		bit[2][2][1] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 0;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 0;
		bit[2][2][2] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 0;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}
#endif

	if(Template == 24)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 0;
		bit[2][2][0] = 1;

		bit[0][1][0] = 0;
		bit[1][1][0] = 0;
		bit[2][1][0] = 1;

		bit[0][0][0] = 0;
		bit[1][0][0] = 0;
		bit[2][0][0] = 1;

		bit[0][2][1] = 1;
		bit[1][2][1] = 1;
		bit[2][2][1] = 1;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][2][2] = 1;
		bit[1][2][2] = 1;
		bit[2][2][2] = 1;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}

	if(Template == 25)
		{
		bit[0][2][0] = 0;
		bit[1][2][0] = 1;
		bit[2][2][0] = 0;

		bit[0][1][0] = 1;
		bit[1][1][0] = 1;
		bit[2][1][0] = 1;

		bit[0][0][0] = 1;
		bit[1][0][0] = 1;
		bit[2][0][0] = 1;

		bit[0][2][1] = 0;
		bit[1][2][1] = 1;
		bit[2][2][1] = 0;

		bit[0][1][1] = 1;
		bit[1][1][1] = 1;
		bit[2][1][1] = 1;

		bit[0][0][1] = 1;
		bit[1][0][1] = 1;
		bit[2][0][1] = 1;

		bit[0][2][2] = 0;
		bit[1][2][2] = 1;
		bit[2][2][2] = 0;

		bit[0][1][2] = 1;
		bit[1][1][2] = 1;
		bit[2][1][2] = 1;

		bit[0][0][2] = 1;
		bit[1][0][2] = 1;
		bit[2][0][2] = 1;
		}
}