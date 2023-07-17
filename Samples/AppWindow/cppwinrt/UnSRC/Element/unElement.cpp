/*

    unElement - Open GL Class
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/
#include "pch.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

#include "unElement.h"

#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"

#include "MathHelper.h"

#include "../Avatar/unMesh.h"

#include "../Render/unRenderer/unRenderer.h"

extern unRenderer *unRender;

using namespace UN;

namespace UN
{

shapeCC CC;

unElement::unElement(unsigned int i_ShapeIndex, unsigned int i_nverts, float i_radius)
{
#if 0
	switch(i_ShapeIndex)
		{
		case UN_SHAPE_QFACE:
			{
			radius = i_radius;
			nverts = i_nverts;
			nfaces = 2;
			m_scale = 1.0f;
			m_texscale = 1.0f;
			m_terrainWidth = 1.0f;

			// Shape Attributes
			m_pVertexBuffer = (float*)&i_VertexBuffer;
			m_vertexStride = 0;
			m_pIndexBuffer = (int*)CC.UnFace;
			m_pNormalBuffer = (char*)&i_NormalBuffer;
			m_normalStride = 3*sizeof(float);
			m_pWeightBuffer = (char*)&i_WeightBuffer;
			m_weightStride = 4*sizeof(float);
			m_pMatrixIndexBuffer = (char*)&i_MatrixIndexBuffer;
			m_matrixIndexStride = 4*sizeof(float);
			m_textureCoordNum = 1;
			m_pTextureCoordBuffer[0] = (char*)&i_TexCoordBuffer;
			m_textureCoordStride[0] = 2*sizeof(float);

			///////acMollFace(PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			/*glGenBuffersARB(6, m_bufferObject);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*3*sizeof(float), (const void*)&i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*4*sizeof(float), (const void*)&i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*3*sizeof(float), (const void*)&i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*4*sizeof(float), (const void*)&i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*2*sizeof(float), (const void*)&i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);*/
			} break;

		case UN_SHAPE_CUBE:
			{
			nverts = i_nverts;
			nfaces = 6;
			m_scale = 1.0f;
			m_texscale = 1.0f;
			m_terrainWidth = 1.0f;

			// Shape Attributes
			m_pVertexBuffer = (float*)&i_VertexBuffer;
			m_vertexStride = 0;
			m_pIndexBuffer = (int*)CC.UnFace;
			m_pNormalBuffer = (char*)&i_NormalBuffer;
			m_normalStride = 3*sizeof(float);
			m_pWeightBuffer = (char*)&i_WeightBuffer;
			m_weightStride = 4*sizeof(float);
			m_pMatrixIndexBuffer = (char*)&i_MatrixIndexBuffer;
			m_matrixIndexStride = 4*sizeof(float);
			m_textureCoordNum = 1;
			m_pTextureCoordBuffer[0] = (char*)&i_TexCoordBuffer;
			m_textureCoordStride[0] = 2*sizeof(float);

			///////acMollCube(PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			/*glGenBuffersARB(6, m_bufferObject);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*3*sizeof(float), (const void*)&i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*4*sizeof(float), (const void*)&i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*3*sizeof(float), (const void*)&i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*4*sizeof(float), (const void*)&i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, nverts*2*sizeof(float), (const void*)&i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);*/
			} break;

		case UN_SHAPE_CIRCLE:
			{
			} break;

		case UN_SHAPE_SPHERE:
			{
			} break;
		}
#endif
}

unElement::~unElement(void)
{
}

unElementBank::unElementBank(void)
{
		///
	/////////
	// Element
	static int f_FaceNum = 2;
	static int f_VertexNum = 6;
	static int f_UVNum = 6;
	static int f_VertexFloat = 3;
	static int f_ColorFloat = 4;
	static int f_FaceIndexVec = 3;
	static int f_FaceIndex = 3;
	static int f_FaceFloat = 9;
	static int f_UVFloat = 2;

	m_Vertex = new float[4 * f_VertexFloat];
	m_Color = new float[UN_ELEMENT_DIM * f_ColorFloat * f_FaceIndexVec * f_FaceNum];
	m_TextureCoord = new float[UN_ELEMENT_DIM * f_UVFloat * f_FaceIndexVec * f_FaceNum];
	m_Bitmap = new GLuint[UN_ELEMENT_DIM * f_FaceNum];
	m_Index = new GLuint[UN_ELEMENT_DIM * f_FaceIndex * f_FaceNum];

	m_VertexCount = 0;
	m_FaceCount = 0;
	m_Triple = 0;
}

void unElementBank::acReset(void)
{
	///
	/////////
	// Element
	static int f_FaceNum = 2;
	static int f_VertexNum = 6;
	static int f_UVNum = 6;
	static int f_VertexFloat = 3;
	static int f_ColorFloat = 4;
	static int f_FaceIndexVec = 3;
	static int f_FaceIndex = 3;
	static int f_FaceFloat = 9;
	static int f_UVFloat = 2;

	//if(m_Vertex) delete m_Vertex;
	//if(m_Color) delete m_Color;
	//if(m_TextureCoord) delete m_TextureCoord;
	//if(m_Bitmap) delete m_Bitmap;
	//if(m_Index) delete m_Index;

	if(mCubeRenderer->mVertexPositionBuffer) glDeleteBuffers(1, &mCubeRenderer->mVertexPositionBuffer);
	if(m_ColorBuffer) glDeleteBuffers(1, &m_ColorBuffer);
	if(m_TextureCoordBuffer) glDeleteBuffers(1, &m_TextureCoordBuffer);
	if(mCubeRenderer->mIndexBuffer) glDeleteBuffers(1, &mCubeRenderer->mIndexBuffer);

	//m_Vertex = new float[UN_ELEMENT_DIM * f_VertexFloat * f_FaceIndexVec * f_FaceNum];
	//m_Color = new float[UN_ELEMENT_DIM * f_ColorFloat * f_FaceIndexVec * f_FaceNum];
	//m_TextureCoord = new float[UN_ELEMENT_DIM * f_UVFloat * f_FaceIndexVec * f_FaceNum];
	//m_Bitmap = new GLuint[UN_ELEMENT_DIM * f_FaceNum];
	//m_Index = new GLuint[UN_ELEMENT_DIM * f_FaceIndex * f_FaceNum];

	/*m_Vertex[0] = 50;
	m_Vertex[1] = 50;
	m_Vertex[2] = 0;

	m_TextureCoord[0] = 0;
	m_TextureCoord[1] = 1;

	m_Vertex[3] = -50;
	m_Vertex[4] = 50;
	m_Vertex[5] = 0;

	m_TextureCoord[0] = 1;
	m_TextureCoord[1] = 1;

	m_Vertex[6] = 50;
	m_Vertex[7] = -50;
	m_Vertex[8] = 0;

	m_TextureCoord[0] = 0;
	m_TextureCoord[1] = 0;

	m_Vertex[9] = -50;
	m_Vertex[10] = -50;
	m_Vertex[11] = 0;

	m_TextureCoord[0] = 0;
	m_TextureCoord[1] = 0;

	m_Index[0] = 0;
	m_Index[1] = 2;
	m_Index[2] = 1;

	m_Index[3] = 1;
	m_Index[4] = 3;
	m_Index[5] = 2;*/

	if (mCubeRenderer->mVertexPositionBuffer) glDeleteBuffers(1, &mCubeRenderer->mVertexPositionBuffer);
	if (mCubeRenderer->mVertexColorBuffer) glDeleteBuffers(1, &mCubeRenderer->mVertexColorBuffer);
	if (mCubeRenderer->mIndexBuffer) glDeleteBuffers(1, &mCubeRenderer->mIndexBuffer);

	 // Then set up the cube geometry.
    GLfloat vertexPositions[] =
    {
        -4.0f, -4.0f, -4.0f,
        -4.0f, -4.0f,  4.0f,
        -4.0f,  4.0f, -4.0f,
        -4.0f,  4.0f,  4.0f,
         4.0f, -4.0f, -4.0f,
         4.0f, -4.0f,  4.0f,
         4.0f,  4.0f, -4.0f,
         4.0f,  4.0f,  4.0f,
    };

    //glGenBuffers(1, &mCubeRenderer->mVertexPositionBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, mCubeRenderer->mVertexPositionBuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
    };

    //glGenBuffers(1, &mCubeRenderer->mVertexColorBuffer);
    //glBindBuffer(GL_ARRAY_BUFFER, mCubeRenderer->mVertexColorBuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,
              
        0, 6, 4, // -z
        0, 2, 6,
              
        1, 7, 3, // +z
        1, 5, 7,
    };

	//glGenBuffers(1, &mCubeRenderer->mIndexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCubeRenderer->mIndexBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_VertexCount = 0;
	m_FaceCount = 0;
	m_Triple = 0;
}

void unElementBank::acSoftReset(void)
{
	///
	/////////
	// Element
	static int f_FaceNum = 2;
	static int f_VertexNum = 6;
	static int f_UVNum = 6;
	static int f_VertexFloat = 3;
	static int f_ColorFloat = 4;
	static int f_FaceIndexVec = 3;
	static int f_FaceIndex = 3;
	static int f_FaceFloat = 9;
	static int f_UVFloat = 2;

#if 0
	if(m_Vertex) delete m_Vertex;
	if(m_Color) delete m_Color;
	if(m_TextureCoord) delete m_TextureCoord;
	if(m_Bitmap) delete m_Bitmap;
	if(m_Index) delete m_Index;
#endif

	if(mCubeRenderer->mVertexPositionBuffer) glDeleteBuffers(1, &mCubeRenderer->mVertexPositionBuffer);
	if(m_ColorBuffer) glDeleteBuffers(1, &m_ColorBuffer);
	if(m_TextureCoordBuffer) glDeleteBuffers(1, &m_TextureCoordBuffer);
	if(mCubeRenderer->mIndexBuffer) glDeleteBuffers(1, &mCubeRenderer->mIndexBuffer);

#if 0
	m_Vertex = new float[UN_ELEMENT_DIM * f_VertexFloat * f_FaceIndexVec * f_FaceNum];
	m_Color = new float[UN_ELEMENT_DIM * f_ColorFloat * f_FaceIndexVec * f_FaceNum];
	m_TextureCoord = new float[UN_ELEMENT_DIM * f_UVFloat * f_FaceIndexVec * f_FaceNum];
	m_Bitmap = new GLuint[UN_ELEMENT_DIM  * f_FaceIndex * f_FaceNum];
	m_Index = new GLuint[UN_ELEMENT_DIM * f_FaceIndex * f_FaceNum];
#endif

	m_VertexCount = 0;
	m_FaceCount = 0;
	m_Triple = 0;
}

unElementBank::~unElementBank(void)
{
	if(mCubeRenderer->mVertexPositionBuffer) glDeleteBuffers(1, &mCubeRenderer->mVertexPositionBuffer);
	if(m_ColorBuffer) glDeleteBuffers(1, &m_ColorBuffer);
	if(m_TextureCoordBuffer) glDeleteBuffers(1, &m_TextureCoordBuffer);
	if(mCubeRenderer->mIndexBuffer) glDeleteBuffers(1, &mCubeRenderer->mIndexBuffer);

	if(m_Vertex) delete m_Vertex;
	if(m_Color) delete m_Color;
	if(m_TextureCoord) delete m_TextureCoord;
	if(m_Bitmap) delete m_Bitmap;
	if(m_Index) delete m_Index;

	m_VertexCount = 0;
	m_FaceCount = 0;
	m_Triple = 0;
}

int unElementBank::acAdd_Bitmap(GLuint f_Bitmap)
{
	bool f_Found = false;
	int f_Index = 0;

	for(uint16 f_Count = 0; f_Count < m_vec_Bitmap.size(); f_Count++)
		{
		if(m_vec_Bitmap[f_Count] == f_Bitmap)
			{
			f_Found = true;
			f_Index = f_Count;
			}
		}

	if(!f_Found)
		{
		m_vec_Bitmap.push_back(f_Bitmap);
		f_Index = m_vec_Bitmap.size() - 1;
		}

	return f_Index;
}

void unElementBank::acAdd_Vertex(float f_U, float f_V, int f_Bitmap,
								 float f_X, float f_Y, float f_Z,
								 float f_R, float f_G, float f_B, float f_A)
{
	///
	/////////
	// Element
	static int f_FaceNum = 2;
	static int f_VertexNum = 6;
	static int f_UVNum = 6;
	static int f_VertexFloat = 3;
	static int f_ColorFloat = 4;
	static int f_FaceIndexVec = 3;
	static int f_FaceIndex = 3;
	static int f_FaceFloat = 9;
	static int f_UVFloat = 2;

	if(m_VertexCount * f_FaceIndexVec < UN_ELEMENT_DIM * f_VertexFloat * f_FaceIndexVec * f_FaceNum)
		{
		m_Vertex[m_VertexCount * f_FaceIndexVec] = f_X;
		m_Vertex[m_VertexCount * f_FaceIndexVec + 1] = f_Y;
		m_Vertex[m_VertexCount * f_FaceIndexVec + 2] = f_Z;
		m_Color[m_VertexCount * f_ColorFloat] = f_R;
		m_Color[m_VertexCount * f_ColorFloat + 1] = f_G;
		m_Color[m_VertexCount * f_ColorFloat + 2] = f_B;
		m_Color[m_VertexCount * f_ColorFloat + 3] = f_A;
		m_TextureCoord[m_VertexCount * f_UVFloat] = f_U;
		m_TextureCoord[m_VertexCount * f_UVFloat + 1] = f_V;
		m_Bitmap[m_FaceCount] = f_Bitmap;

		m_VertexCount++;

		m_Triple++;

		if(m_Triple == 3)
			{
			m_Triple = 0;
			m_FaceCount++;
			}
		}

	if(m_VertexCount >= 6)
		{
		m_VertexCount = 6;
		m_FaceCount = 2;
		}
}

bool unElementBank::Poly_AddOnce(QpoVertex * Verts, int NumVerts, unsigned int Bitmap, UInt8 TypeFLAGS, UInt8 RendFLAGS, float Scale)
{
#if 0
	if(g_render->view.is_inside(pVector(Verts[0].x, Verts[0].y, Verts[0].z)))
		{
#endif
		//int f_BitmapIndex = acAdd_Bitmap(Bitmap); // Select Our Texture

		if(TypeFLAGS == QPOLY_TYPE_PNT || 1)
			{
			//*Qpo->Transform_GetIn(&g_render->camera.mat, &CC.InVec);
			//*Qpo->Transform_GetUp(&g_render->camera.mat, &CC.UpVec);
			//*Qpo->Transform_GetLeft(&g_render->camera.mat, &CC.LeftVec);

			CC.InVec.x = 0;
			CC.InVec.y = 0;
			CC.InVec.z = 1;

			CC.UpVec.x = 0;
			CC.UpVec.y = 0;
			CC.UpVec.z = 1;

			CC.LeftVec.x = -1;
			CC.LeftVec.y = 0;
			CC.LeftVec.z = 0;

			CC.destpos.x = Verts->x;
			CC.destpos.y = Verts->y;
			CC.destpos.z = Verts->z;

			CC.ScaleFT = Scale * 150;

			CC.m_Red = Verts->r;
			CC.m_Green = Verts->g;
			CC.m_Blue = Verts->b;
			CC.m_Alpha = Verts->a;

			CC.m_1U = 1; // Top Right
			CC.m_1V = 1;

			Qpo->Vec3d_AddScaled(&CC.destpos, -CC.ScaleFT / 2, &CC.LeftVec, &CC.Vert1);
			Qpo->Vec3d_AddScaled(&CC.transvert, CC.ScaleFT / 2, &CC.UpVec, &CC.Vert1);

			CC.m_2U = 0; // Top Left
			CC.m_2V = 1;

			Qpo->Vec3d_AddScaled(&CC.destpos, CC.ScaleFT / 2, &CC.LeftVec, &CC.Vert2);
			Qpo->Vec3d_AddScaled(&CC.transvert, CC.ScaleFT / 2, &CC.UpVec, &CC.Vert2);

			CC.m_3U = 1; // Bottom Right
			CC.m_3V = 0;

			Qpo->Vec3d_AddScaled(&CC.destpos, -CC.ScaleFT / 2, &CC.LeftVec, &CC.Vert3);
			Qpo->Vec3d_AddScaled(&CC.transvert, -CC.ScaleFT / 2, &CC.UpVec, &CC.Vert3);

			CC.m_4U = 0; // Bottom Left
			CC.m_4V = 0;

			Qpo->Vec3d_AddScaled(&CC.destpos, CC.ScaleFT / 2, &CC.LeftVec, &CC.Vert4);
			Qpo->Vec3d_AddScaled(&CC.transvert, -CC.ScaleFT / 2, &CC.UpVec, &CC.Vert4);

			CC.Vert1.x = 100;
			CC.Vert1.y = -100;
			CC.Vert1.z = 0;

			CC.Vert2.x = -100;
			CC.Vert2.y = -100;
			CC.Vert2.z = 0;

			CC.Vert3.x = 100;
			CC.Vert3.y = 100;
			CC.Vert3.z = 0;

			CC.Vert4.x = -100;
			CC.Vert4.y = 100;
			CC.Vert4.z = 0;

#if 0
			acAdd_Vertex(CC.m_1U, CC.m_1V, Bitmap,
						 CC.Vert1.x, CC.Vert1.y, CC.Vert1.z,
						 CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			acAdd_Vertex(CC.m_2U, CC.m_2V, Bitmap,
						 CC.Vert2.x, CC.Vert2.y, CC.Vert2.z,
						 CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			acAdd_Vertex(CC.m_3U, CC.m_3V, Bitmap,
						 CC.Vert3.x, CC.Vert3.y, CC.Vert3.z,
						 CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			acAdd_Vertex(CC.m_3U, CC.m_3V, Bitmap,
						 CC.Vert3.x, CC.Vert3.y, CC.Vert3.z,
						 CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			acAdd_Vertex(CC.m_2U, CC.m_2V, Bitmap,
						 CC.Vert2.x, CC.Vert2.y, CC.Vert2.z,
						 CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			acAdd_Vertex(CC.m_4U, CC.m_4V, Bitmap,
						 CC.Vert4.x, CC.Vert4.y, CC.Vert4.z,
						 CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);
#else
			// Then set up the cube geometry.
    GLfloat vertexPositions[] =
    {
		CC.destpos.x,  CC.destpos.z + CC.destpos.y, 1.0f,
    };

    GLfloat vertexColors[] =
    {
		CC.m_Red, CC.m_Green, CC.m_Blue
    };
#endif

	g_FirstStack[g_Player] = false;

	//glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (mCubeRenderer->mProgram == 0)
		return false;

	glUseProgram(mCubeRenderer->mProgram);

	//glBindBuffer(GL_ARRAY_BUFFER, mCubeRenderer->mVertexPositionBuffer);
	
	glVertexAttribPointer(mCubeRenderer->mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertexPositions), vertexPositions);
	glVertexAttribPointer(mCubeRenderer->mColorAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertexColors), vertexColors);

	glEnableVertexAttribArray(mCubeRenderer->mPositionAttribLocation);
	glEnableVertexAttribArray(mCubeRenderer->mColorAttribLocation);

	//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)mCubeRenderer->mDrawCount / 50.0f, 1.0f);
	//glUniformMatrix4fv(mCubeRenderer->mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewYRotationMatrix((float)M_PI + g_Spin);
	glUniformMatrix4fv(mCubeRenderer->mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mCubeRenderer->mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	//glEnable(GL_TEXTURE);
	//glBindTexture(GL_TEXTURE_2D, Bitmap);
	//glActiveTexture(GL_TEXTURE0);
	//glUniform1i(mCubeRenderer->mTextureUniformLocation, Bitmap);

	//float f_Pos[4];

	//f_Pos[0] = CC.destpos.x;
	//f_Pos[1] = CC.destpos.y;
	//f_Pos[2] = CC.destpos.z;
	//f_Pos[3] = 1.0f;

	//glUniform4fv(mCubeRenderer->mPosUniformLocation, 1, f_Pos);

	// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCubeRenderer->mIndexBuffer);
	glDrawArrays(GL_POINTS, 0, 1);

	mCubeRenderer->mDrawCount++;
			}

		if (TypeFLAGS == QPOLY_TYPE_TRI)
			{
			CC.ScaleFT = 5;

			CC.m_Red = Verts->r / 255;
			CC.m_Green = Verts->g / 255;
			CC.m_Blue = Verts->b / 255;
			CC.m_Alpha = Verts->a / 255;

			//glColor4ub(Verts->r, Verts->g, Verts->b, Verts->a);
			//*glColor4f(CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			if (NumVerts == 3)
				{
				//*glBegin(GL_POLYGON);

				////*glTexCoord2d(1,1);
				//*glTexCoord2d(Verts[0].u, Verts[0].v);
				//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

				////*glTexCoord2d(0,1);
				//*glTexCoord2d(Verts[1].u, Verts[1].v);
				//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				////*glTexCoord2d(1,0);
				//*glTexCoord2d(Verts[2].u, Verts[2].v);
				//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right
				
				////*glEnd();
				////*glBegin(GL_POLYGON);

				//### Reverse Winding
				////*glTexCoord2d(1,1);
				//*glTexCoord2d(Verts[2].u, Verts[2].v);
				//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Right

				////*glTexCoord2d(0,1);
				//*glTexCoord2d(Verts[1].u, Verts[1].v);
				//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				////*glTexCoord2d(1,0);
				//*glTexCoord2d(Verts[0].u, Verts[0].v);
				//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Right

				//*glEnd();
				}
			else
				{
				if (NumVerts == 4)
					{
					//*glBegin(GL_QUADS);

					////*glTexCoord2d(1,1);
					//*glTexCoord2d(Verts[0].u, Verts[0].v);
					//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

					////*glTexCoord2d(0,1);
					//*glTexCoord2d(Verts[1].u, Verts[1].v);
					//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

					////*glTexCoord2d(1,0);
					//*glTexCoord2d(Verts[2].u, Verts[2].v);
					//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

					////*glTexCoord2d(0,0);
					//*glTexCoord2d(Verts[3].u, Verts[3].v);
					//*glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Bottom Left

					//### Reverse Winding
					////*glTexCoord2d(1,1);
					//*glTexCoord2d(Verts[3].u, Verts[3].v);
					//*glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Top Right

					////*glTexCoord2d(0,1);
					//*glTexCoord2d(Verts[2].u, Verts[2].v);
					//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Left

					////*glTexCoord2d(1,0);
					//*glTexCoord2d(Verts[1].u, Verts[1].v);
					//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Bottom Right

					////*glTexCoord2d(0,0);
					//*glTexCoord2d(Verts[0].u, Verts[0].v);
					//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Left
					
					//*glEnd();
					}
				}
			}

		if (TypeFLAGS == QPOLY_TYPE_GOR)
			{
			CC.ScaleFT = 5;

			CC.m_Red = Verts->r / 255;
			CC.m_Green = Verts->g / 255;
			CC.m_Blue = Verts->b / 255;
			CC.m_Alpha = Verts->a / 255;

			//glColor4ub(Verts->r, Verts->g, Verts->b, Verts->a);
			//*glColor4f(CC.m_Red, CC.m_Green, CC.m_Blue, CC.m_Alpha);

			if (NumVerts == 3)
				{
				//*glBegin(GL_POLYGON);

				////*glTexCoord2d(1,1);
				//*glTexCoord2d(Verts[0].u, Verts[0].v);
				//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

				////*glTexCoord2d(0,1);
				//*glTexCoord2d(Verts[1].u, Verts[1].v);
				//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				////*glTexCoord2d(1,0);
				//*glTexCoord2d(Verts[2].u, Verts[2].v);
				//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

				////*glEnd();
				////*glBegin(GL_POLYGON);

				//### Reverse Winding
				////*glTexCoord2d(1,1);
				//*glTexCoord2d(Verts[2].u, Verts[2].v);
				//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Right

				////*glTexCoord2d(0,1);
				//*glTexCoord2d(Verts[1].u, Verts[1].v);
				//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				////*glTexCoord2d(1,0);
				//*glTexCoord2d(Verts[0].u, Verts[0].v);
				//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Right

				//*glEnd();
				}

			if (NumVerts == 4)
				{
				//*glBegin(GL_QUADS);

				////*glTexCoord2d(1,1);
				//*glTexCoord2d(Verts[0].u, Verts[0].v);
				//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Top Right

				////*glTexCoord2d(0,1);
				//*glTexCoord2d(Verts[1].u, Verts[1].v);
				//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Top Left

				////*glTexCoord2d(1,0);
				//*glTexCoord2d(Verts[2].u, Verts[2].v);
				//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Bottom Right

				////*glTexCoord2d(0,0);
				//*glTexCoord2d(Verts[3].u, Verts[3].v);
				//*glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Bottom Left

				//### Reverse Winding
				////*glTexCoord2d(1,1);
				//*glTexCoord2d(Verts[3].u, Verts[3].v);
				//*glVertex3f(Verts[3].x, Verts[3].y, Verts[3].z); // Top Right

				////*glTexCoord2d(0,1);
				//*glTexCoord2d(Verts[2].u, Verts[2].v);
				//*glVertex3f(Verts[2].x, Verts[2].y, Verts[2].z); // Top Left

				////*glTexCoord2d(1,0);
				//*glTexCoord2d(Verts[1].u, Verts[1].v);
				//*glVertex3f(Verts[1].x, Verts[1].y, Verts[1].z); // Bottom Right

				////*glTexCoord2d(0,0);
				//*glTexCoord2d(Verts[0].u, Verts[0].v);
				//*glVertex3f(Verts[0].x, Verts[0].y, Verts[0].z); // Bottom Left

				//*glEnd();
				}
			}

#if 0
		}
#endif

	return true;
}

void unElementBank::acSetBuffers(void)
{
	///
	/////////
	// Element
	static int f_FaceNum = 2;
	static int f_VertexNum = 6;
	static int f_UVNum = 6;
	static int f_VertexFloat = 3;
	static int f_ColorFloat = 4;
	static int f_FaceIndexVec = 3;
	static int f_FaceIndex = 3;
	static int f_FaceFloat = 9;
	static int f_UVFloat = 2;

	glGenBuffers(1, &mCubeRenderer->mVertexPositionBuffer);
	glGenBuffers(1, &m_ColorBuffer);
	glGenBuffers(1, &m_TextureCoordBuffer);
	glGenBuffers(1, &mCubeRenderer->mIndexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, mCubeRenderer->mVertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(float), (const void*)&m_Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), (const void*)&m_Color, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), (const void*)&m_TextureCoord, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCubeRenderer->mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_VertexCount * sizeof(unsigned int), (const void*)&m_Index, GL_STATIC_DRAW);

	printf("m_FaceCount * f_FaceIndex = %i\n", m_FaceCount * f_FaceIndex);
}

void unElementBank::acRender(void)
{
	glEnable(GL_DEPTH_TEST);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (mCubeRenderer->mProgram == 0)
		return;

	glUseProgram(mCubeRenderer->mProgram);

	glBindBuffer(GL_ARRAY_BUFFER, mCubeRenderer->mVertexPositionBuffer);
	glEnableVertexAttribArray(mCubeRenderer->mPositionAttribLocation);
	glVertexAttribPointer(mCubeRenderer->mPositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mCubeRenderer->mVertexColorBuffer);
	glEnableVertexAttribArray(mCubeRenderer->mColorAttribLocation);
	glVertexAttribPointer(mCubeRenderer->mColorAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)1.0, 1.0);
	//glUniformMatrix4fv(mCubeRenderer->mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewYRotationMatrix((float)M_PI + g_Spin);
	glUniformMatrix4fv(mCubeRenderer->mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mCubeRenderer->mWindowWidth) / float(mCubeRenderer->mWindowHeight));
	glUniformMatrix4fv(mCubeRenderer->mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	// Draw 36 indices: six faces, two triangles per face, 3 indices per triangle
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCubeRenderer->mIndexBuffer);
	glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_SHORT, 0);

#if 0
#if 1
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(mElProgram == 0)
		{
		printf("unElementBank::acRender mElProgram is not loaded\n");
		for(;;) {}
		}

	glUseProgram(mElProgram);

	//Vertex Array - Position
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glEnableVertexAttribArray(m0ElVertexAttribLocation);
	glVertexAttribPointer(m0ElVertexAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normal Array - Colors
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glEnableVertexAttribArray(m1ElColorAttribLocation);
	glVertexAttribPointer(m1ElColorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - Texture Coords
	glBindBuffer(GL_ARRAY_BUFFER, m_TextureCoordBuffer);
	glEnableVertexAttribArray(m2ElTexCoordAttribLocation);
	glVertexAttribPointer(m2ElTexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Elements Array - Face Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCubeRenderer->mIndexBuffer);

	//MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix(25.0f / 50.0f);
	//glUniformMatrix4fv(mElModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewYRotationMatrix((float)M_PI + g_Spin);

#if 0
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
#else
	glUniformMatrix4fv(mElViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
#endif

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mElProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	glUniform1i(mElTextureUniformLocation, 0);

	float f_LightPos[4];
	f_LightPos[0] = 50;
	f_LightPos[1] = 50;
	f_LightPos[2] = 190;
	f_LightPos[3] = 1.0;

	glUniform4fv(mElLightPosUniformLocation, 1, &(f_LightPos[0]));

	//glEnable(GL_BLEND);
#if 0
	int f_Start = 0;
	int f_NewStart = 0;
	bool f_Scan = true;
	while(f_Scan)
		{
		f_Start = f_NewStart;
		GLuint f_Bitmap = m_Bitmap[f_Start];
		int f_FaceCount = 0;
		bool f_can = true;
		while(f_can)
			{
			int m_MidState = f_Start + f_FaceCount;

			if(f_Bitmap != m_Bitmap[m_MidState])
				{
				f_can = false;
				f_NewStart = m_MidState;

				if(m_MidState >= m_FaceCount)
					{
					f_can = false;
					f_Scan = false;
					}
				}
			else
				{
				f_FaceCount += 2;

				int m_MidState = f_Start + f_FaceCount;

				if(m_MidState >= m_FaceCount)
					{
					f_can = false;
					f_Scan = false;
					}
				}
			}
#else
		 //////////
		// Bind
		//glBindTexture(GL_TEXTURE_2D, f_Bitmap);

		 ///////////
		// Render
		//
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0);
#endif
#if 0
		}
#endif
#else
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glEnableVertexAttribArray(unRender->m0AttribLocation);
	glVertexAttribPointer(unRender->m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normal Array - Normals
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glEnableVertexAttribArray(unRender->m2AttribLocation);
	glVertexAttribPointer(unRender->m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - Texture Coords
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glEnableVertexAttribArray(unRender->m4AttribLocation);
	glVertexAttribPointer(unRender->m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - Weights
    glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glEnableVertexAttribArray(unRender->m1AttribLocation);
	glVertexAttribPointer(unRender->m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - MatrixIndex
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glEnableVertexAttribArray(unRender->m3AttribLocation);
	glVertexAttribPointer(unRender->m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Elements Array - Face Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	//*glLoadIdentity();
	//*glMultMatrixf((float *)&g_render->camera.mat_t);
	//*glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)mDrawCount / 50.0f);
	glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewYRotationMatrix((float)M_PI + g_Spin);
	glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mWindowWidth) / float(mWindowHeight));
	glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));
#else
#if 0
	MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix(25.0f / 50.0f);
	glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
	glUniformMatrix4fv(unRender->mModelUniformLocation, 1, GL_FALSE, playerAV[g_Player]->Xform.Matrix.mf);
#endif

	MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewYRotationMatrix((float)M_PI + g_Spin);

#if 0
	glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
#else
	glUniformMatrix4fv(unRender->mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
#endif

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(unRender->mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	float f_Team[4];

	if(player[g_Player]->Team == 0)
		{
		f_Team[0] = 0.0;
		f_Team[1] = 0.0;
		f_Team[2] = 0.0;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 1)
		{
		f_Team[0] = 0.08;
		f_Team[1] = 0.0;
		f_Team[2] = 0.2;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 2)
		{
		f_Team[0] = 0.18;
		f_Team[1] = 0.0;
		f_Team[2] = 0.0;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 3)
		{
		f_Team[0] = 0.25;
		f_Team[1] = 0.0;
		f_Team[2] = 0.25;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 4)
		{
		f_Team[0] = 0.23;
		f_Team[1] = 0.20;
		f_Team[2] = 0.0;
		f_Team[3] = 1.0;
		}

	glUniform4fv(unRender->mTeamUniformLocation, 1, &(f_Team[0]));

	if(playerAV[g_Player]->Xform.Translation.x > 900 * g_ArenaSize)
		{
		playerAV[g_Player]->Xform.Translation.x = 900 * g_ArenaSize;
		}
	if(playerAV[g_Player]->Xform.Translation.y > 900 * g_ArenaSize)
		{
		playerAV[g_Player]->Xform.Translation.y = 900 * g_ArenaSize;
		}
	if(playerAV[g_Player]->Xform.Translation.z > 900 * g_ArenaSize)
		{
		playerAV[g_Player]->Xform.Translation.z = 900 * g_ArenaSize;
		}

	if(playerAV[g_Player]->Xform.Translation.x < -900 * g_ArenaSize)
		{
		playerAV[g_Player]->Xform.Translation.x = -900 * g_ArenaSize;
		}
	if(playerAV[g_Player]->Xform.Translation.y < -900 * g_ArenaSize)
		{
		playerAV[g_Player]->Xform.Translation.y = -900 * g_ArenaSize;
		}
	if(playerAV[g_Player]->Xform.Translation.z < -900 * g_ArenaSize)
		{
		playerAV[g_Player]->Xform.Translation.z = -900 * g_ArenaSize;
		}

	QpoVec3d f_Diff;
	float f_Length = 50000.0;
	bool f_Touch = false;
	int f_Index = 0;

	for(int f_Count = 0; f_Count < _->NomAI; f_Count++)
		{
		if(Q_Forge->Forge[f_Count].LIVE)
			{
			if (Q_Forge->Forge[f_Count].Team != player[g_Player]->Team)
				{
				if(Q_Forge->Forge[f_Count].HB_Dead == 0)
					{
					Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[f_Count].AV.Xform.Translation, &f_Diff);

					float f_AvatarLength = Qpo->Vec3d_Length(&f_Diff);

					if(f_AvatarLength < f_Length)
						{
						f_Length = f_AvatarLength;
						f_Index = f_Count;
						f_Touch = true;
						}
					}
				}
			}
		}

	if(f_Touch && player[g_Player]->attackon && !player[g_Player]->HB_Dead)
		{
		float f_X = (Q_Forge->Forge[f_Index].AV.Xform.Translation.x - playerAV[g_Player]->Xform.Translation.x) * 0.2;
		float f_Y = (Q_Forge->Forge[f_Index].AV.Xform.Translation.z - playerAV[g_Player]->Xform.Translation.z) * 0.2;

		if(f_X > 2.9)
			{
			f_X = 2.9;
			}

		if(f_Y > 2.9)
			{
			f_Y = 2.9;
			}

		playerAV[g_Player]->Xform.Translation.x += f_X * _->TimeScale;
		playerAV[g_Player]->Xform.Translation.z += f_Y * _->TimeScale;
		}

	float f_Transport[3];

	if(_->TimeHole == 0)
		{
		g_ZoomFactor -= 0.05;

		if(g_ZoomFactor <= 0.0)
			{
			g_ZoomFactor = 0.0;
			}
		}
	else
		{
		g_ZoomFactor += 0.09;

		if(g_ZoomFactor >= 1.0)
			{
			g_ZoomFactor = 1.0;
			}
		}

	if(g_ZoomFactor > 0)
		{
		f_Transport[0] = playerAV[g_Player]->Xform.Translation.x * (1 - g_ZoomFactor);
		f_Transport[1] = ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y) * (1 - g_ZoomFactor)) - (65 * g_ZoomFactor);
		f_Transport[2] = 0;
		}
	else
		{
		f_Transport[0] = playerAV[g_Player]->Xform.Translation.x;
		f_Transport[1] = playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y;
		f_Transport[2] = 0;
		}

	glUniform3fv(unRender->mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

	f_Transport[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2));
	f_Transport[1] = playerAV[g_Player]->Xform.Translation.y + 100;
	f_Transport[2] = -playerAV[g_Player]->Xform.Translation.z - 75;

	glUniform3fv(unRender->mCameraTranslationUniformLocation, 1, &(f_Transport[0]));
#endif

#ifndef QAGEMODE_SURGERY
//*if(player[g_Player]->AirJinkRotFG == 1)
//*	{
//*	glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
//*	glMultMatrixf(playerAV[g_Player]->Viewform.mf);
//*	}
//*else
//*	{
//*	glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
//*	glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
//*	}
#endif

	/// Player Mesh Settings ///
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		float transformation[896];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

#if 0
			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#if 0
			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
				{
#endif
				transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
				transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
				transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
				transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;
				//transformation[(boneId * 16) + 12] = rotationMatrix.dzdx; transformation[(boneId * 16) + 13] = rotationMatrix.dzdy; transformation[(boneId * 16) + 14] = rotationMatrix.dzdz; transformation[(boneId * 16) + 15] = translationBoneSpace.z;

#if 0
				}
			else
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
				}
#endif

#if 0
			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

			////QDglActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		glUniform1i(unRender->mTextureUniformLocation, 0);

		glUniformMatrix4fv(unRender->mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

#if 1
		if(hardwareMeshId < 38)
			{
			diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
			diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
			diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
			}
		else
			{
			diffuseColor[0] = 1;
			diffuseColor[1] = 1;
			diffuseColor[2] = 1;
			}

		if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
			{
			diffuseColor[0] = 1;
			diffuseColor[1] = 1;
			diffuseColor[2] = 1;
			}
#endif

		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		//pVector lightpos;
		//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
		//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
		//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

		//*pVector eyepos;
		//*eyepos.x = g_render->camera.pos.x;
		//*eyepos.y = g_render->camera.pos.y;
		//*eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
		float f_LightPos[40];
		float f_LightColor[40];

		f_LightPos[0] = 5;
		f_LightPos[1] = 50;
		f_LightPos[2] = 190;
		f_LightPos[3] = 1.0;
		f_LightColor[0] = 0.8;
		f_LightColor[1] = 0.8;
		f_LightColor[2] = 0.65;
		f_LightColor[3] = 1.0;

		int f_Start = 0;
		if(Q_Nom_Light - 10 < 0)
			{
			f_Start = 50 + (Q_Nom_Light - 10);
			}
		else
			{
			f_Start = Q_Nom_Light - 10;
			}

		int f_Count = f_Start;
		for(int f_Point = 4; f_Point < 40; f_Point += 4)
			{
			f_LightPos[f_Point] = g_Light[f_Count].m_Pos.x;
			f_LightPos[f_Point + 1] = g_Light[f_Count].m_Pos.z + g_Light[f_Count].m_Pos.y;
			f_LightPos[f_Point + 2] = 0.0;
			f_LightPos[f_Point + 3] = 1.0;
			f_LightColor[f_Point] = g_Light[f_Count].m_Color.red / 255;
			f_LightColor[f_Point + 1] = g_Light[f_Count].m_Color.green / 255;
			f_LightColor[f_Point + 2] = g_Light[f_Count].m_Color.blue / 255;
			f_LightColor[f_Point + 3] = g_Light[f_Count].m_Color.alpha / 255;
			}

		if(Q_Nom_Light > 0)
			{
			f_LightPos[4] = g_Light[Q_Nom_Light - 1].m_Pos.x;
			f_LightPos[5] = g_Light[Q_Nom_Light - 1].m_Pos.y;
			f_LightPos[6] = g_Light[Q_Nom_Light - 1].m_Pos.z;
			f_LightPos[7] = 1.0;
			f_LightColor[4] = g_Light[Q_Nom_Light - 1].m_Color.red;
			f_LightColor[5] = g_Light[Q_Nom_Light - 1].m_Color.green;
			f_LightColor[6] = g_Light[Q_Nom_Light - 1].m_Color.blue;
			f_LightColor[7] = g_Light[Q_Nom_Light - 1].m_Color.alpha;
			}

		glUniform4fv(unRender->mLightPosUniformLocation, 10, &(f_LightPos[0]));
		glUniform4fv(unRender->mLightColorUniformLocation, 10, &(f_LightColor[0]));

		glDisable(GL_BLEND);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}
#endif
#endif
}

#if 0
void unElementBank::acCreateShape(unsigned int i_ShapeIndex, float i_radius)
{
	switch(i_ShapeIndex)
		{
		case UN_SHAPE_QFACE:
			{
#pragma message ("When integrating constant split buffers increase minimum size")
			unElement *i_ShapeElement = new unElement(4);
			/*i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 3;
			i_ShapeElement->nfaces = 1;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;*/

			// Add first Split Buffer Set
			unBufferSet *i_BufferSet = new unBufferSet();

			// Shape Attributes
			i_BufferSet->m_pVertexBuffer = (float*)&i_ShapeElement->i_VertexBuffer;
			i_BufferSet->m_vertexStride = 0;
			//*i_BufferSet->m_pIndexBuffer = (int*)CC.UnFace;
			i_BufferSet->m_pNormalBuffer = (char*)&i_ShapeElement->i_NormalBuffer;
			i_BufferSet->m_normalStride = 3*sizeof(float);
			i_BufferSet->m_pWeightBuffer = (char*)&i_ShapeElement->i_WeightBuffer;
			i_BufferSet->m_weightStride = 4*sizeof(float);
			i_BufferSet->m_pMatrixIndexBuffer = (char*)&i_ShapeElement->i_MatrixIndexBuffer;
			i_BufferSet->m_matrixIndexStride = 4*sizeof(float);
			i_BufferSet->m_textureCoordNum = 1;
			i_BufferSet->m_pTextureCoordBuffer[0] = (char*)&i_ShapeElement->i_TexCoordBuffer;
			i_BufferSet->m_textureCoordStride[0] = 2*sizeof(float);

#if 0		//Unused
			i_BufferSet->m_pTangentSpaceBuffer[mapId] = (char*)pTangentSpaceBuffer;
			i_BufferSet->m_tangentSpaceStride[mapId] = stride;
#endif

			// Add Buffer Set to shape
			//*i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			//*acMollFace(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			// Set Buffer Memory
#pragma message ("When integrating constant split buffers increase minimum size")
			/*glGenBuffersARB(6, i_ShapeElement->m_BufferSet[0]->m_bufferObject);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*2*sizeof(float), (const void*)&i_ShapeElement->i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);*/
			} break;

		case UN_SHAPE_SQUARE:
			{
#pragma message ("When integrating constant split buffers increase minimum size")
			unElement *i_ShapeElement = new unElement(4);
			/*i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 4;
			i_ShapeElement->nfaces = 2;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;*/

			// Add first Split Buffer Set
			unBufferSet *i_BufferSet = new unBufferSet();

			// Shape Attributes
			i_BufferSet->m_pVertexBuffer = (float*)&i_ShapeElement->i_VertexBuffer;
			i_BufferSet->m_vertexStride = 0;
			i_BufferSet->m_pIndexBuffer = (int*)CC.UnFace;
			i_BufferSet->m_pNormalBuffer = (char*)&i_ShapeElement->i_NormalBuffer;
			i_BufferSet->m_normalStride = 3*sizeof(float);
			i_BufferSet->m_pWeightBuffer = (char*)&i_ShapeElement->i_WeightBuffer;
			i_BufferSet->m_weightStride = 4*sizeof(float);
			i_BufferSet->m_pMatrixIndexBuffer = (char*)&i_ShapeElement->i_MatrixIndexBuffer;
			i_BufferSet->m_matrixIndexStride = 4*sizeof(float);
			i_BufferSet->m_textureCoordNum = 1;
			i_BufferSet->m_pTextureCoordBuffer[0] = (char*)&i_ShapeElement->i_TexCoordBuffer;
			i_BufferSet->m_textureCoordStride[0] = 2*sizeof(float);

#if 0		//Unused
			i_BufferSet->m_pTangentSpaceBuffer[mapId] = (char*)pTangentSpaceBuffer;
			i_BufferSet->m_tangentSpaceStride[mapId] = stride;
#endif

			// Add Buffer Set to shape
			//*i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			//*acMollSquare(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			// Set Buffer Memory
#pragma message ("When integrating constant split buffers increase minimum size")
			/*glGenBuffersARB(6, i_ShapeElement->m_BufferSet[0]->m_bufferObject);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*2*sizeof(float), (const void*)&i_ShapeElement->i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);*/
			} break;

		case UN_SHAPE_UNSQUARE:
			{
#pragma message ("When integrating constant split buffers increase minimum size")
			unElement *i_ShapeElement = new unElement(4);
			/*i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 6;
			i_ShapeElement->nfaces = 2;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;*/

			// Add first Split Buffer Set
			unBufferSet *i_BufferSet = new unBufferSet();

			// Shape Attributes
			i_BufferSet->m_pVertexBuffer = (float*)&i_ShapeElement->i_VertexBuffer;
			i_BufferSet->m_vertexStride = 0;
			i_BufferSet->m_pIndexBuffer = (int*)CC.UnFace;
			i_BufferSet->m_pNormalBuffer = (char*)&i_ShapeElement->i_NormalBuffer;
			i_BufferSet->m_normalStride = 3*sizeof(float);
			i_BufferSet->m_pWeightBuffer = (char*)&i_ShapeElement->i_WeightBuffer;
			i_BufferSet->m_weightStride = 4*sizeof(float);
			i_BufferSet->m_pMatrixIndexBuffer = (char*)&i_ShapeElement->i_MatrixIndexBuffer;
			i_BufferSet->m_matrixIndexStride = 4*sizeof(float);
			i_BufferSet->m_textureCoordNum = 1;
			i_BufferSet->m_pTextureCoordBuffer[0] = (char*)&i_ShapeElement->i_TexCoordBuffer;
			i_BufferSet->m_textureCoordStride[0] = 2*sizeof(float);

#if 0		//Unused
			i_BufferSet->m_pTangentSpaceBuffer[mapId] = (char*)pTangentSpaceBuffer;
			i_BufferSet->m_tangentSpaceStride[mapId] = stride;
#endif

			// Add Buffer Set to shape
			//*i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			//*acMollUnSquare(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			// Set Buffer Memory
#pragma message ("When integrating constant split buffers increase minimum size")
			/*glGenBuffersARB(6, i_ShapeElement->m_BufferSet[0]->m_bufferObject);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*2*sizeof(float), (const void*)&i_ShapeElement->i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);*/
			} break;

		case UN_SHAPE_CUBE:
			{
#pragma message ("When integrating constant split buffers increase minimum size")
			unElement *i_ShapeElement = new unElement(108);
			/*i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 108;
			i_ShapeElement->nfaces = 6;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;*/

			// Add first Split Buffer Set
			unBufferSet *i_BufferSet = new unBufferSet();

			i_BufferSet->m_pVertexBuffer = (float*)&i_ShapeElement->i_VertexBuffer;
			i_BufferSet->m_vertexStride = 0;
			i_BufferSet->m_pIndexBuffer = (int*)CC.UnFace;
			i_BufferSet->m_pNormalBuffer = (char*)&i_ShapeElement->i_NormalBuffer;
			i_BufferSet->m_normalStride = 3*sizeof(float);
			i_BufferSet->m_pWeightBuffer = (char*)&i_ShapeElement->i_WeightBuffer;
			i_BufferSet->m_weightStride = 4*sizeof(float);
			i_BufferSet->m_pMatrixIndexBuffer = (char*)&i_ShapeElement->i_MatrixIndexBuffer;
			i_BufferSet->m_matrixIndexStride = 4*sizeof(float);
			i_BufferSet->m_textureCoordNum = 1;
			i_BufferSet->m_pTextureCoordBuffer[0] = (char*)&i_ShapeElement->i_TexCoordBuffer;
			i_BufferSet->m_textureCoordStride[0] = 2*sizeof(float);

#if 0	//Unused
			i_BufferSet->m_pTangentSpaceBuffer[mapId] = pTangentSpaceBuffer;
			i_BufferSet->m_tangentSpaceStride[mapId] = stride;
#endif
			//Add Buffer Set to Shape Element
			//*i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			//*acMollCube(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			// Set Buffer Memory
#pragma message ("When integrating constant split buffers increase minimum size")
			/*glGenBuffersARB(6, i_ShapeElement->m_BufferSet[0]->m_bufferObject);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)&i_ShapeElement->i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)&i_ShapeElement->i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*2*sizeof(float), (const void*)&i_ShapeElement->i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);*/
			} break;

		case UN_SHAPE_CIRCLE:
			{
			} break;

		case UN_SHAPE_SPHERE:
			{
#pragma message ("When integrating constant split buffers increase minimum size")
			unElement *i_ShapeElement = new unElement(10 + ((10 / 2 - 1) * 10) * 2 + 2);
			/*i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 10 + ((10 / 2 - 1) * 10) * 2 + 2;
			i_ShapeElement->nfaces = 10 * (10 / 2 - 1) * 4 + 2 * 10;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;

			// Add first Split Buffer Set
			unBufferSet *i_BufferSet = new unBufferSet();*/

#if 1
			/*i_ShapeElement->iptr_VertexBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_WeightBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_MatrixIndexBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_NormalBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_TexCoordBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_IndexBuffer = new int[i_ShapeElement->nfaces*3];*/

			i_BufferSet->m_pVertexBuffer = i_ShapeElement->iptr_VertexBuffer;
			i_BufferSet->m_vertexStride = 0;
			i_BufferSet->m_pIndexBuffer = (int*)CC.UnFace;
			i_BufferSet->m_pNormalBuffer = (char*)i_ShapeElement->iptr_NormalBuffer;
			i_BufferSet->m_normalStride = 3*sizeof(float);
			i_BufferSet->m_pWeightBuffer = (char*)i_ShapeElement->iptr_WeightBuffer;
			i_BufferSet->m_weightStride = 4*sizeof(float);
			i_BufferSet->m_pMatrixIndexBuffer = (char*)i_ShapeElement->iptr_MatrixIndexBuffer;
			i_BufferSet->m_matrixIndexStride = 4*sizeof(float);
			i_BufferSet->m_textureCoordNum = 1;
			i_BufferSet->m_pTextureCoordBuffer[0] = (char*)i_ShapeElement->iptr_TexCoordBuffer;
			i_BufferSet->m_textureCoordStride[0] = 2*sizeof(float);
#endif

#if 0
			i_BufferSet->m_pVertexBuffer = (float*)&i_ShapeElement->i_VertexBuffer;
			i_BufferSet->m_vertexStride = 0;
			i_BufferSet->m_pIndexBuffer = (int*)CC.UnFace;
			i_BufferSet->m_pNormalBuffer = (char*)&i_ShapeElement->i_NormalBuffer;
			i_BufferSet->m_normalStride = 3*sizeof(float);
			i_BufferSet->m_pWeightBuffer = (char*)&i_ShapeElement->i_WeightBuffer;
			i_BufferSet->m_weightStride = 4*sizeof(float);
			i_BufferSet->m_pMatrixIndexBuffer = (char*)&i_ShapeElement->i_MatrixIndexBuffer;
			i_BufferSet->m_matrixIndexStride = 4*sizeof(float);
			i_BufferSet->m_textureCoordNum = 1;
			i_BufferSet->m_pTextureCoordBuffer[0] = (char*)&i_ShapeElement->i_TexCoordBuffer;
			i_BufferSet->m_textureCoordStride[0] = 2*sizeof(float);
#endif

#if 0	//Unused
			i_BufferSet->m_pTangentSpaceBuffer[mapId] = pTangentSpaceBuffer;
			i_BufferSet->m_tangentSpaceStride[mapId] = stride;
#endif
			//Add Buffer Set to Shape Element
			//*i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			for (UInt32 i = 0 ; i < 35 ; i++)
				{
				//*i_ShapeElement->m_BufferSet[0]->m_pVertexBuffer[i*3] = 0;
				//*i_ShapeElement->m_BufferSet[0]->m_pVertexBuffer[(i*3)+1] = 0;
				//*i_ShapeElement->m_BufferSet[0]->m_pVertexBuffer[(i*3)+2] = 0;
				}

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			//*acMollSphere(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius), 10, true);
			//acMollCube(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

			// Set Buffer Memory
#pragma message ("When integrating constant split buffers increase minimum size")
			/*glGenBuffersARB(6, i_ShapeElement->m_BufferSet[0]->m_bufferObject);

#if 0
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)i_ShapeElement->i_VertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)i_ShapeElement->i_WeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)i_ShapeElement->i_NormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)i_ShapeElement->i_MatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*2*sizeof(float), (const void*)i_ShapeElement->i_TexCoordBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[5]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);
#endif

#if 1
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[0]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)m_Shape[0]->m_BufferSet[0]->m_pVertexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[1]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)m_Shape[0]->m_BufferSet[0]->m_pWeightBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[2]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*3*sizeof(float), (const void*)m_Shape[0]->m_BufferSet[0]->m_pNormalBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[3]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*4*sizeof(float), (const void*)m_Shape[0]->m_BufferSet[0]->m_pMatrixIndexBuffer, GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[4]);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, i_ShapeElement->nverts*2*sizeof(float), (const void*)m_Shape[0]->m_BufferSet[0]->m_pTextureCoordBuffer[0], GL_STATIC_DRAW_ARB);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->m_BufferSet[0]->m_bufferObject[5]);
#if 0
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)CC.UnFace, GL_STATIC_DRAW_ARB);
#endif
#if 1
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeElement->nfaces*3*sizeof(unsigned int), (const void*)m_Shape[0]->m_BufferSet[0]->m_pIndexBuffer, GL_STATIC_DRAW_ARB);
#endif
#endif*/
			} break;
		}
}

void unElementBank::acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z)
{
	unElementInstance *i_ShapeInstance = new unElementInstance();
	i_ShapeInstance->x = i_x;
	i_ShapeInstance->y = i_y;
	i_ShapeInstance->z = i_z;
	m_Shape[i_VectorIndex]->m_Instance.push_back(i_ShapeInstance);
}
#endif

///***## Class Cache Shell Execution Mode ***##///
bool Element_CC::setExecMode(int i_ExecMode)
	{
#if 0
	if(i_ExecMode == m_ExecMode) return false;

	switch(i_ExecMode)
		{
		case CCX_MODE_POLY:
			{
			glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
			glEnable(GL_BLEND);									// Enable Blending
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
			glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

#pragma message("Server Engine excludes")
#if defined(WIN32)
			//g_render->set_camera();
#endif
			} break;

		case CCX_MODE_BLIT:
			{
			glGetIntegerv(GL_VIEWPORT, vPort);
			//*glMatrixMode(GL_PROJECTION);
			//*glPushMatrix();
			//*glLoadIdentity();
			//*glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
			//*glMatrixMode(GL_MODELVIEW);
			//*glPushMatrix();
			//*glLoadIdentity();

			glEnable(GL_TEXTURE_2D);
			glDisable(GL_DEPTH_TEST);
			} break;

		case CCX_MODE_DRAW:
			{
			glGetIntegerv(GL_VIEWPORT, vPort);
			//*glMatrixMode(GL_PROJECTION);
			//*glPushMatrix();
			//*glLoadIdentity();
			//*glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
			//*glMatrixMode(GL_MODELVIEW);
			//*glPushMatrix();
			//*glLoadIdentity();

			glDisable(GL_DEPTH_TEST);
			} break;
		}

	m_ExecMode = i_ExecMode;
	return true;
#endif

	return true;
	}

};