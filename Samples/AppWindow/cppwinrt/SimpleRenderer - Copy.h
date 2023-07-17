/*

	unSimpleRenderer - Unification Renderer
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SIMPLE_RENDERER
#define SIMPLE_RENDERER

#include "Include\Cube.h"

#if 0
#include "UnSRC\Element\unElement.h"
#endif

//*** INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

namespace Quantum_Angel
{

class SimpleRenderer
	{
	public:
		SimpleRenderer();
		~SimpleRenderer();

		void DrawPoint(float f_X, float f_Y, float f_Z, float f_Red, float f_Green, float f_Blue, float f_Alpha, unsigned int f_Bitmap, float f_Scale);

		void DrawTri(QpoVertex * Verts, GLuint f_Bitmap);
		void DrawQuad(QpoVertex * Verts, GLuint f_Bitmap);

		void DrawTriGor(QpoVertex * Verts);
		void DrawQuadGor(QpoVertex * Verts);

		void UpdateWindowSize(GLsizei width, GLsizei height);

		void acSelect_BlendFunction(void);

	public:
		GLuint mProgram[3];

		GLint mModelUniformLocation[3];
		GLint mViewUniformLocation[3];
		GLint mProjUniformLocation[3];

		GLint mPosUniformLocation[3];
		GLint mColorUniformLocation[3];
		GLint mUVUniformLocation[3];

		GLint mCamPosUniformLocation[3];
		GLint mTextureUniformLocation[3];

		GLint mVertNomAttribLocation[3];

		GLuint mIndexBuffer;
		GLuint mVertNomBuffer;
	};

extern SimpleRenderer* g_SimpleRenderer;

}

#endif