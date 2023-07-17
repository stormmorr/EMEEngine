/*

NonStaticArray - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

//#include "PortShell/NonStaticArray.h"

//*** INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include "Q-PortSHELL-Sound.h"

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"

using namespace Quantum_Angel;

namespace Quantum_Angel
{

void PointNonStaticArrayContainer::acMap(void)
{
	const unsigned int f_Nom = m_Size * 3;

	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);

	m_VertexPositionBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		m_VertexPositionBuff[(f_NomCount * 3)] = m_vec_NonStaticArray[f_NomCount]->m_X - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[(f_NomCount * 3) + 1] = m_vec_NonStaticArray[f_NomCount]->m_Y;
		m_VertexPositionBuff[(f_NomCount * 3) + 2] = (m_vec_NonStaticArray[f_NomCount]->m_Z - playerAV[0]->Xform.Translation.z) * -1;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);

	m_VertexColorBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		const unsigned int f_Count = f_NomCount * 4;
		m_VertexColorBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_R / 255.0f;
		m_VertexColorBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_G / 255.0f;
		m_VertexColorBuff[f_Count + 2] = m_vec_NonStaticArray[f_NomCount]->m_B / 255.0f;
		m_VertexColorBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_A / 255.0f;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriNonStaticArrayContainer::acMap(void)
{
	const unsigned int f_Nom = m_Size * 3;

	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);

	m_VertexPositionBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		const unsigned int f_Count = f_NomCount * 9;
		m_VertexPositionBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_X1 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_Y1;
		m_VertexPositionBuff[f_Count + 2] = (m_vec_NonStaticArray[f_NomCount]->m_Z1 - playerAV[0]->Xform.Translation.z) * -1;
		m_VertexPositionBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_X2 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 4] = m_vec_NonStaticArray[f_NomCount]->m_Y2;
		m_VertexPositionBuff[f_Count + 5] = (m_vec_NonStaticArray[f_NomCount]->m_Z2 - playerAV[0]->Xform.Translation.z) * -1;
		m_VertexPositionBuff[f_Count + 6] = m_vec_NonStaticArray[f_NomCount]->m_X3 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 7] = m_vec_NonStaticArray[f_NomCount]->m_Y3;
		m_VertexPositionBuff[f_Count + 8] = (m_vec_NonStaticArray[f_NomCount]->m_Z3 - playerAV[0]->Xform.Translation.z) * -1;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);

	m_VertexColorBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		const unsigned int f_Count = f_NomCount * 12;
		m_VertexColorBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_R1 / 255.0f;
		m_VertexColorBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_G1 / 255.0f;
		m_VertexColorBuff[f_Count + 2] = m_vec_NonStaticArray[f_NomCount]->m_B1 / 255.0f;
		m_VertexColorBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_A1 / 255.0f;
		m_VertexColorBuff[f_Count + 4] = m_vec_NonStaticArray[f_NomCount]->m_R2 / 255.0f;
		m_VertexColorBuff[f_Count + 5] = m_vec_NonStaticArray[f_NomCount]->m_G2 / 255.0f;
		m_VertexColorBuff[f_Count + 6] = m_vec_NonStaticArray[f_NomCount]->m_B2 / 255.0f;
		m_VertexColorBuff[f_Count + 7] = m_vec_NonStaticArray[f_NomCount]->m_A2 / 255.0f;
		m_VertexColorBuff[f_Count + 8] = m_vec_NonStaticArray[f_NomCount]->m_R3 / 255.0f;
		m_VertexColorBuff[f_Count + 9] = m_vec_NonStaticArray[f_NomCount]->m_G3 / 255.0f;
		m_VertexColorBuff[f_Count + 10] = m_vec_NonStaticArray[f_NomCount]->m_B3 / 255.0f;
		m_VertexColorBuff[f_Count + 11] = m_vec_NonStaticArray[f_NomCount]->m_A3 / 255.0f;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);

	m_TexCoordBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		const unsigned int f_Count = f_NomCount * 6;
		m_TexCoordBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_U1;
		m_TexCoordBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_V1;
		m_TexCoordBuff[f_Count + 2] = m_vec_NonStaticArray[f_NomCount]->m_U2;
		m_TexCoordBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_V2;
		m_TexCoordBuff[f_Count + 4] = m_vec_NonStaticArray[f_NomCount]->m_U3;
		m_TexCoordBuff[f_Count + 5] = m_vec_NonStaticArray[f_NomCount]->m_V3;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void QuadNonStaticArrayContainer::acMap(void)
{
	const unsigned int f_Nom = m_Size * 3;

	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);

	m_VertexPositionBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		const unsigned int f_Count = f_NomCount * 12;
		m_VertexPositionBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_X1 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_Y1;
		m_VertexPositionBuff[f_Count + 2] = (m_vec_NonStaticArray[f_NomCount]->m_Z1 - playerAV[0]->Xform.Translation.z) * -1;
		m_VertexPositionBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_X2 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 4] = m_vec_NonStaticArray[f_NomCount]->m_Y2;
		m_VertexPositionBuff[f_Count + 5] = (m_vec_NonStaticArray[f_NomCount]->m_Z2 - playerAV[0]->Xform.Translation.z) * -1;
		m_VertexPositionBuff[f_Count + 6] = m_vec_NonStaticArray[f_NomCount]->m_X3 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 7] = m_vec_NonStaticArray[f_NomCount]->m_Y3;
		m_VertexPositionBuff[f_Count + 8] = (m_vec_NonStaticArray[f_NomCount]->m_Z3 - playerAV[0]->Xform.Translation.z) * -1;
		m_VertexPositionBuff[f_Count + 9] = m_vec_NonStaticArray[f_NomCount]->m_X3 - playerAV[0]->Xform.Translation.x;
		m_VertexPositionBuff[f_Count + 10] = m_vec_NonStaticArray[f_NomCount]->m_Y4;
		m_VertexPositionBuff[f_Count + 11] = (m_vec_NonStaticArray[f_NomCount]->m_Z4 - playerAV[0]->Xform.Translation.z) * -1;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);

	m_VertexColorBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

	if(m_VertexColorBuff)
		{
		for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
			{
			const unsigned int f_Count = f_NomCount * 16;
			m_VertexColorBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_R1 / 255.0f;
			m_VertexColorBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_G1 / 255.0f;
			m_VertexColorBuff[f_Count + 2] = m_vec_NonStaticArray[f_NomCount]->m_B1 / 255.0f;
			m_VertexColorBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_A1 / 255.0f;
			m_VertexColorBuff[f_Count + 4] = m_vec_NonStaticArray[f_NomCount]->m_R2 / 255.0f;
			m_VertexColorBuff[f_Count + 5] = m_vec_NonStaticArray[f_NomCount]->m_G2 / 255.0f;
			m_VertexColorBuff[f_Count + 6] = m_vec_NonStaticArray[f_NomCount]->m_B2 / 255.0f;
			m_VertexColorBuff[f_Count + 7] = m_vec_NonStaticArray[f_NomCount]->m_A2 / 255.0f;
			m_VertexColorBuff[f_Count + 8] = m_vec_NonStaticArray[f_NomCount]->m_R3 / 255.0f;
			m_VertexColorBuff[f_Count + 9] = m_vec_NonStaticArray[f_NomCount]->m_G3 / 255.0f;
			m_VertexColorBuff[f_Count + 10] = m_vec_NonStaticArray[f_NomCount]->m_B3 / 255.0f;
			m_VertexColorBuff[f_Count + 11] = m_vec_NonStaticArray[f_NomCount]->m_A3 / 255.0f;
			m_VertexColorBuff[f_Count + 12] = m_vec_NonStaticArray[f_NomCount]->m_R4 / 255.0f;
			m_VertexColorBuff[f_Count + 13] = m_vec_NonStaticArray[f_NomCount]->m_G4 / 255.0f;
			m_VertexColorBuff[f_Count + 14] = m_vec_NonStaticArray[f_NomCount]->m_B4 / 255.0f;
			m_VertexColorBuff[f_Count + 15] = m_vec_NonStaticArray[f_NomCount]->m_A4 / 255.0f;
			}

		glUnmapBufferOES(GL_ARRAY_BUFFER);
		}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);

	m_TexCoordBuff = (GLfloat*)glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		const unsigned int f_Count = f_NomCount * 8;
		m_TexCoordBuff[f_Count] = m_vec_NonStaticArray[f_NomCount]->m_U1;
		m_TexCoordBuff[f_Count + 1] = m_vec_NonStaticArray[f_NomCount]->m_V1;
		m_TexCoordBuff[f_Count + 2] = m_vec_NonStaticArray[f_NomCount]->m_U2;
		m_TexCoordBuff[f_Count + 3] = m_vec_NonStaticArray[f_NomCount]->m_V2;
		m_TexCoordBuff[f_Count + 4] = m_vec_NonStaticArray[f_NomCount]->m_U3;
		m_TexCoordBuff[f_Count + 5] = m_vec_NonStaticArray[f_NomCount]->m_V3;
		m_TexCoordBuff[f_Count + 6] = m_vec_NonStaticArray[f_NomCount]->m_U3;
		m_TexCoordBuff[f_Count + 7] = m_vec_NonStaticArray[f_NomCount]->m_V3;
		}

	glUnmapBufferOES(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PointNonStaticArrayContainer::acBuild(void)
{
	if(mVertexPositionBuffer)
		{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
		}

	if(mVertexColorBuffer)
		{
		glDeleteBuffers(1, &mVertexColorBuffer);
		mVertexColorBuffer = 0;
		}

	if(mIndexBuffer)
		{
		glDeleteBuffers(1, &mIndexBuffer);
		mIndexBuffer = 0;
		}

	const unsigned int f_Nom = m_Size;

	GLfloat* f_Position = new GLfloat[f_Nom * 3];
	GLfloat* f_Color = new GLfloat[f_Nom * 4];
	short* f_Index = new short[f_Nom];
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		f_Position[(f_NomCount * 3)] = m_vec_NonStaticArray[f_NomCount]->m_X;
		f_Position[(f_NomCount * 3) + 1] = m_vec_NonStaticArray[f_NomCount]->m_Y;
		f_Position[(f_NomCount * 3) + 2] = m_vec_NonStaticArray[f_NomCount]->m_Z;
		f_Color[(f_NomCount * 4)] = m_vec_NonStaticArray[f_NomCount]->m_R / 255.0f;
		f_Color[(f_NomCount * 4) + 1] = m_vec_NonStaticArray[f_NomCount]->m_G / 255.0f;
		f_Color[(f_NomCount * 4) + 2] = m_vec_NonStaticArray[f_NomCount]->m_B / 255.0f;
		f_Color[(f_NomCount * 4) + 3] = m_vec_NonStaticArray[f_NomCount]->m_A / 255.0f;
		}

	int f_Ind = 0;
	for(unsigned int f_IndexCount = 0; f_IndexCount < m_Size; f_IndexCount++)
		{
		f_Index[f_IndexCount] = f_IndexCount;
		}

	glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 3, f_Position, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 4, f_Color, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_Nom, f_Index, GL_STATIC_DRAW);
}

void TriNonStaticArrayContainer::acBuild(void)
{
	if(mVertexPositionBuffer)
		{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
		}

	if(mVertexColorBuffer)
		{
		glDeleteBuffers(1, &mVertexColorBuffer);
		mVertexColorBuffer = 0;
		}

	if(mTexCoordBuffer)
		{
		glDeleteBuffers(1, &mTexCoordBuffer);
		mTexCoordBuffer = 0;
		}

	if(mIndexBuffer)
		{
		glDeleteBuffers(1, &mIndexBuffer);
		mIndexBuffer = 0;
		}

	const unsigned int f_Nom = m_Size * 3;

	GLfloat* f_Position = new GLfloat[f_Nom * 3];
	GLfloat* f_NewOS = new GLfloat[f_Nom * 4];
	GLfloat* f_Tex = new GLfloat[f_Nom * 2];
	short* f_Index = new short[f_Nom];
	
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		f_Position[(f_NomCount * 9)] = m_vec_NonStaticArray[f_NomCount]->m_X1;
		f_Position[(f_NomCount * 9) + 1] = m_vec_NonStaticArray[f_NomCount]->m_Y1;
		f_Position[(f_NomCount * 9) + 2] = m_vec_NonStaticArray[f_NomCount]->m_Z1;
		f_Position[(f_NomCount * 9) + 3] = m_vec_NonStaticArray[f_NomCount]->m_X2;
		f_Position[(f_NomCount * 9) + 4] = m_vec_NonStaticArray[f_NomCount]->m_Y2;
		f_Position[(f_NomCount * 9) + 5] = m_vec_NonStaticArray[f_NomCount]->m_Z2;
		f_Position[(f_NomCount * 9) + 6] = m_vec_NonStaticArray[f_NomCount]->m_X3;
		f_Position[(f_NomCount * 9) + 7] = m_vec_NonStaticArray[f_NomCount]->m_Y3;
		f_Position[(f_NomCount * 9) + 8] = m_vec_NonStaticArray[f_NomCount]->m_Z3;
		f_NewOS[(f_NomCount * 12)] = m_vec_NonStaticArray[f_NomCount]->m_R1 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 1] = m_vec_NonStaticArray[f_NomCount]->m_G1 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 2] = m_vec_NonStaticArray[f_NomCount]->m_B1 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 3] = m_vec_NonStaticArray[f_NomCount]->m_A1 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 4] = m_vec_NonStaticArray[f_NomCount]->m_R2 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 5] = m_vec_NonStaticArray[f_NomCount]->m_G2 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 6] = m_vec_NonStaticArray[f_NomCount]->m_B2 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 7] = m_vec_NonStaticArray[f_NomCount]->m_A2 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 8] = m_vec_NonStaticArray[f_NomCount]->m_R3 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 9] = m_vec_NonStaticArray[f_NomCount]->m_G3 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 10] = m_vec_NonStaticArray[f_NomCount]->m_B3 / 255.0f;
		f_NewOS[(f_NomCount * 12) + 11] = m_vec_NonStaticArray[f_NomCount]->m_A3 / 255.0f;
		f_Tex[(f_NomCount * 6)] = m_vec_NonStaticArray[f_NomCount]->m_U1;
		f_Tex[(f_NomCount * 6) + 1] = m_vec_NonStaticArray[f_NomCount]->m_V1;
		f_Tex[(f_NomCount * 6) + 2] = m_vec_NonStaticArray[f_NomCount]->m_U2;
		f_Tex[(f_NomCount * 6) + 3] = m_vec_NonStaticArray[f_NomCount]->m_V2;
		f_Tex[(f_NomCount * 6) + 4] = m_vec_NonStaticArray[f_NomCount]->m_U3;
		f_Tex[(f_NomCount * 6) + 5] = m_vec_NonStaticArray[f_NomCount]->m_V3;
		}

	int f_Ind = 0;
	for(unsigned int f_IndexCount = 0; f_IndexCount < m_Size; f_IndexCount++)
		{
		f_Index[(f_IndexCount * 3)] = (f_IndexCount * 3);
		f_Index[(f_IndexCount * 3) + 1] = (f_IndexCount * 3) + 1;
		f_Index[(f_IndexCount * 3) + 2] = (f_IndexCount * 3) + 2;
		}

	glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 3, f_Position, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 4, f_NewOS, GL_STATIC_DRAW);

	glGenBuffers(1, &mTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 2, f_Tex, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * f_Nom * 3, f_Index, GL_STATIC_DRAW);
}

void QuadNonStaticArrayContainer::acBuild(void)
{
	if(mVertexPositionBuffer)
		{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
		}

	if(mVertexColorBuffer)
		{
		glDeleteBuffers(1, &mVertexColorBuffer);
		mVertexColorBuffer = 0;
		}

	if(mTexCoordBuffer)
		{
		glDeleteBuffers(1, &mTexCoordBuffer);
		mTexCoordBuffer = 0;
		}

	if(mIndexBuffer)
		{
		glDeleteBuffers(1, &mIndexBuffer);
		mIndexBuffer = 0;
		}

	const unsigned int f_Nom = m_Size * 4;

	GLfloat* f_Position = new GLfloat[f_Nom * 3];
	GLfloat* f_Color = new GLfloat[f_Nom * 4];
	GLfloat* f_Tex = new GLfloat[f_Nom * 2];
	short* f_Index = new short[m_Size * 6];
	for(unsigned int f_NomCount = 0; f_NomCount < m_Size; f_NomCount++)
		{
		f_Position[(f_NomCount * 12)] = m_vec_NonStaticArray[f_NomCount]->m_X1;
		f_Position[(f_NomCount * 12) + 1] = m_vec_NonStaticArray[f_NomCount]->m_Y1;
		f_Position[(f_NomCount * 12) + 2] = m_vec_NonStaticArray[f_NomCount]->m_Z1;
		f_Position[(f_NomCount * 12) + 3] = m_vec_NonStaticArray[f_NomCount]->m_X2;
		f_Position[(f_NomCount * 12) + 4] = m_vec_NonStaticArray[f_NomCount]->m_Y2;
		f_Position[(f_NomCount * 12) + 5] = m_vec_NonStaticArray[f_NomCount]->m_Z2;
		f_Position[(f_NomCount * 12) + 6] = m_vec_NonStaticArray[f_NomCount]->m_X3;
		f_Position[(f_NomCount * 12) + 7] = m_vec_NonStaticArray[f_NomCount]->m_Y3;
		f_Position[(f_NomCount * 12) + 8] = m_vec_NonStaticArray[f_NomCount]->m_Z3;
		f_Position[(f_NomCount * 12) + 9] = m_vec_NonStaticArray[f_NomCount]->m_X4;
		f_Position[(f_NomCount * 12) + 10] = m_vec_NonStaticArray[f_NomCount]->m_Y4;
		f_Position[(f_NomCount * 12) + 11] = m_vec_NonStaticArray[f_NomCount]->m_Z4;
		f_Color[(f_NomCount * 16)] = m_vec_NonStaticArray[f_NomCount]->m_R1 / 255.0f;
		f_Color[(f_NomCount * 16) + 1] = m_vec_NonStaticArray[f_NomCount]->m_G1 / 255.0f;
		f_Color[(f_NomCount * 16) + 2] = m_vec_NonStaticArray[f_NomCount]->m_B1 / 255.0f;
		f_Color[(f_NomCount * 16) + 3] = m_vec_NonStaticArray[f_NomCount]->m_A1 / 255.0f;
		f_Color[(f_NomCount * 16) + 4] = m_vec_NonStaticArray[f_NomCount]->m_R2 / 255.0f;
		f_Color[(f_NomCount * 16) + 5] = m_vec_NonStaticArray[f_NomCount]->m_G2 / 255.0f;
		f_Color[(f_NomCount * 16) + 6] = m_vec_NonStaticArray[f_NomCount]->m_B2 / 255.0f;
		f_Color[(f_NomCount * 16) + 7] = m_vec_NonStaticArray[f_NomCount]->m_A2 / 255.0f;
		f_Color[(f_NomCount * 16) + 8] = m_vec_NonStaticArray[f_NomCount]->m_R3 / 255.0f;
		f_Color[(f_NomCount * 16) + 9] = m_vec_NonStaticArray[f_NomCount]->m_G3 / 255.0f;
		f_Color[(f_NomCount * 16) + 10] = m_vec_NonStaticArray[f_NomCount]->m_B3 / 255.0f;
		f_Color[(f_NomCount * 16) + 11] = m_vec_NonStaticArray[f_NomCount]->m_A3 / 255.0f;
		f_Color[(f_NomCount * 16) + 12] = m_vec_NonStaticArray[f_NomCount]->m_R4 / 255.0f;
		f_Color[(f_NomCount * 16) + 13] = m_vec_NonStaticArray[f_NomCount]->m_G4 / 255.0f;
		f_Color[(f_NomCount * 16) + 14] = m_vec_NonStaticArray[f_NomCount]->m_B4 / 255.0f;
		f_Color[(f_NomCount * 16) + 15] = m_vec_NonStaticArray[f_NomCount]->m_A4 / 255.0f;
		f_Tex[(f_NomCount * 8)] = m_vec_NonStaticArray[f_NomCount]->m_U1;
		f_Tex[(f_NomCount * 8) + 1] = m_vec_NonStaticArray[f_NomCount]->m_V1;
		f_Tex[(f_NomCount * 8) + 2] = m_vec_NonStaticArray[f_NomCount]->m_U2;
		f_Tex[(f_NomCount * 8) + 3] = m_vec_NonStaticArray[f_NomCount]->m_V2;
		f_Tex[(f_NomCount * 8) + 4] = m_vec_NonStaticArray[f_NomCount]->m_U3;
		f_Tex[(f_NomCount * 8) + 5] = m_vec_NonStaticArray[f_NomCount]->m_V3;
		f_Tex[(f_NomCount * 8) + 6] = m_vec_NonStaticArray[f_NomCount]->m_U4;
		f_Tex[(f_NomCount * 8) + 7] = m_vec_NonStaticArray[f_NomCount]->m_V4;
		}

	int f_Ind = 0;
	for(unsigned int f_IndexCount = 0; f_IndexCount < m_Size; f_IndexCount++)
		{
		f_Index[(f_IndexCount * 6)] = f_Ind;
		f_Index[(f_IndexCount * 6) + 1] = f_Ind + 1;
		f_Index[(f_IndexCount * 6) + 2] = f_Ind + 2;
		f_Index[(f_IndexCount * 6) + 3] = f_Ind + 2;
		f_Index[(f_IndexCount * 6) + 4] = f_Ind + 3;
		f_Index[(f_IndexCount * 6) + 5] = f_Ind;
		f_Ind += 4;
		}

	glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 3, f_Position, GL_STATIC_DRAW);

	glGenBuffers(1, &mVertexColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 4, f_Color, GL_STATIC_DRAW);

	glGenBuffers(1, &mTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * f_Nom * 2, f_Tex, GL_STATIC_DRAW);

	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short) * m_Size * 6, f_Index, GL_STATIC_DRAW);
}

};