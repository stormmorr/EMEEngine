/*

    unShape - Open GL Class
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/
#include "pch.h"
#if 0
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#if 0
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#endif

#include "unShape.h"

extern PxPhysics *digi_PhysicsSDK;

namespace Digi
{

extern PxCooking *digi_Cooking;
extern PxScene *digi_Scene;

extern PxMaterial* mMaterial;

}

namespace UN
{

shapeCC CC;

unShape::unShape(unsigned int i_ShapeIndex, unsigned int i_nverts, float i_radius)
	: i_VertexBuffer(boost::extents[(i_nverts*3) + 1]),
	i_WeightBuffer(boost::extents[(i_nverts*4) + 1]),
	i_MatrixIndexBuffer(boost::extents[(i_nverts*4) + 1]),
	i_NormalBuffer(boost::extents[(i_nverts*3) + 1]),
	i_TexCoordBuffer(boost::extents[(i_nverts*2) + 1])
{
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

			acMollFace(PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

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

			acMollCube(PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

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
}

unShape::~unShape(void)
{
	//glDeleteBuffersARB(6, m_bufferObject);
}

unShapeBank::unShapeBank(void)
{
}

unShapeBank::~unShapeBank(void)
{
	int countshape;
	int countset;
	for(countshape = 0; countshape < m_Shape.size(); countshape++)
		{
		for(countset = 0; countset < m_Shape[countshape]->m_BufferSet.size(); countset++)
			{
			//glDeleteBuffersARB(6, m_Shape[countshape]->m_BufferSet[countset]->m_bufferObject);
			}
		}
	m_Shape.clear();
}

void unShapeBank::acCreateShape(unsigned int i_ShapeIndex, float i_radius)
{
	switch(i_ShapeIndex)
		{
		case UN_SHAPE_QFACE:
			{
#pragma message ("When integrating constant split buffers increase minimum size")
			unShapeElement *i_ShapeElement = new unShapeElement(4);
			i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 3;
			i_ShapeElement->nfaces = 1;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;

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
			i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			acMollFace(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

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
			unShapeElement *i_ShapeElement = new unShapeElement(4);
			i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 4;
			i_ShapeElement->nfaces = 2;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;

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
			i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			acMollSquare(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

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
			unShapeElement *i_ShapeElement = new unShapeElement(4);
			i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 6;
			i_ShapeElement->nfaces = 2;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;

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
			i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			acMollUnSquare(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

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
			unShapeElement *i_ShapeElement = new unShapeElement(108);
			i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 108;
			i_ShapeElement->nfaces = 6;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;

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
			i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			acMollCube(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius));

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
			unShapeElement *i_ShapeElement = new unShapeElement(10 + ((10 / 2 - 1) * 10) * 2 + 2);
			i_ShapeElement->radius = i_radius;
			i_ShapeElement->nverts = 10 + ((10 / 2 - 1) * 10) * 2 + 2;
			i_ShapeElement->nfaces = 10 * (10 / 2 - 1) * 4 + 2 * 10;
			i_ShapeElement->m_scale = 1.0f;
			i_ShapeElement->m_texscale = 1.0f;
			i_ShapeElement->m_terrainWidth = 1.0f;

			// Add first Split Buffer Set
			unBufferSet *i_BufferSet = new unBufferSet();

#if 1
			i_ShapeElement->iptr_VertexBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_WeightBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_MatrixIndexBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_NormalBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_TexCoordBuffer = new float[i_ShapeElement->nverts*3];
			i_ShapeElement->iptr_IndexBuffer = new int[i_ShapeElement->nfaces*3];

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
			i_ShapeElement->m_BufferSet.push_back(i_BufferSet);

			for (UInt32 i = 0 ; i < 35 ; i++)
				{
				i_ShapeElement->m_BufferSet[0]->m_pVertexBuffer[i*3] = 0;
				i_ShapeElement->m_BufferSet[0]->m_pVertexBuffer[(i*3)+1] = 0;
				i_ShapeElement->m_BufferSet[0]->m_pVertexBuffer[(i*3)+2] = 0;
				}

			// Add Shape to Bank
			m_Shape.push_back(i_ShapeElement);

			acMollSphere(m_Shape.size() - 1, 0, PxVec3(0,0,0), PxVec3(i_radius, i_radius, i_radius), 10, true);
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

void unShapeBank::acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z)
{
	unShapeInstance *i_ShapeInstance = new unShapeInstance();
	i_ShapeInstance->x = i_x;
	i_ShapeInstance->y = i_y;
	i_ShapeInstance->z = i_z;
	m_Shape[i_VectorIndex]->m_Instance.push_back(i_ShapeInstance);
}

};
#endif