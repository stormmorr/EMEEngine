/*

    unBufferSet - OpenGL VBO Handlers
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unBufferSet_h__
#define __unBufferSet_h__

typedef struct unBufferSet
{
	unsigned int m_bufferObject[6];
	float * m_pVertexBuffer;
	int m_vertexStride;
	char * m_pNormalBuffer;
	int m_normalStride;
	char * m_pWeightBuffer;
	int m_weightStride;
	char * m_pMatrixIndexBuffer;
	int m_matrixIndexStride;
	char * m_pTextureCoordBuffer[8];
	int m_textureCoordStride[8];
	int m_textureCoordNum;
	char * m_pTangentSpaceBuffer[8];
	int m_tangentSpaceStride[8];
	int * m_pIndexBuffer;
	unsigned int m_VertexCounter;
} unBufferSet;

#endif