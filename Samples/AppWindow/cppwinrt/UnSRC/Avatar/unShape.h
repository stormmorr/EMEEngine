/*

    unShape - Open GL Class/Struct clone_structor
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unShape_h__
#define __unShape_h__
#if 0
#include "../Utility/DataTypes.h"
#include "../Render/unBufferSet.h"

/// PhysX Includes
//*#include "PxPhysics.h"
//*#include "PxCooking.h"
//*#include "PxVec3.h"
//*#include "PxActor.h"

#include "boost/multi_array.hpp"
#include "boost/array.hpp"
#include "boost/cstdlib.hpp"

//*using namespace physx;

namespace UN
{

#define SHAPE_UN_FACE_DIM 16192
#define UN_SHAPE_QFACE 0
#define UN_SHAPE_SQUARE 1
#define UN_SHAPE_UNSQUARE 2
#define UN_SHAPE_CUBE 3
#define UN_SHAPE_UNCUBE 4
#define UN_SHAPE_CIRCLE 5
#define UN_SHAPE_SPHERE 6

typedef boost::multi_array<float, 1> shapeVertexAry;
typedef shapeVertexAry::index shapeBufferIndex;

typedef boost::multi_array<int, 1> shapeIndicesAry;
typedef shapeIndicesAry::index shapeIndicesIndex;

class shapeCC //Class Cache
{
public:
	shapeCC::shapeCC()
	{
	/// Generate Unified Face Pattern
	UnFace = new unsigned int[SHAPE_UN_FACE_DIM];
	for(int i=0; i < SHAPE_UN_FACE_DIM; ++i) { UnFace[i] = i; }
	};

	inline void acPrepload(void)
		{
		};

	unsigned int *UnFace;
};

typedef struct unShapeInstance
{
	int x;
	int y;
	int z;

	/// Vertex and face counters
	//int nverts;
	//int nfaces;
	//float radius;

	/// New Terrain Super Class Inherit
	//float m_scale;
	//float m_texscale;
	//float m_terrainWidth;
} unShapeInstance;

class unShapeElement
{
public:
	unShapeElement(unsigned int i_nverts)
		: i_VertexBuffer(boost::extents[(i_nverts*3) + 1]),
		i_WeightBuffer(boost::extents[(i_nverts*4) + 1]),
		i_MatrixIndexBuffer(boost::extents[(i_nverts*4) + 1]),
		i_NormalBuffer(boost::extents[(i_nverts*3) + 1]),
		i_TexCoordBuffer(boost::extents[(i_nverts*2) + 1])
		{
		for (UInt32 i = 0 ; i < 35 ; ++i)
			{
			i_VertexBuffer[i*3] = 0;
			i_VertexBuffer[(i*3)+1] = 0.2;
			i_VertexBuffer[(i*3)+2] = 0.3;
			}
		}

	inline size_t getVerticesCount () { return nverts; }
	inline size_t getFacesCount () { return nfaces; }

	/// Vertex and face counters
	int nverts;
	int nfaces;
	float radius;

	/// New Terrain Super Class Inherit
	float m_scale;
	float m_texscale;
	float m_terrainWidth;

	shapeVertexAry i_VertexBuffer;
	shapeVertexAry i_WeightBuffer;
	shapeVertexAry i_MatrixIndexBuffer;
	shapeVertexAry i_NormalBuffer;
	shapeVertexAry i_TexCoordBuffer;
	shapeIndicesAry i_IndexBuffer;

	float *iptr_VertexBuffer;
	float *iptr_WeightBuffer;
	float *iptr_MatrixIndexBuffer;
	float *iptr_NormalBuffer;
	float *iptr_TexCoordBuffer;
	int *iptr_IndexBuffer;

	// Split Buffer Sets
	std::vector<unBufferSet*> m_BufferSet;
	std::vector<unShapeInstance*> m_Instance;
};

class unShape
{
public:
	unShape() {}
	unShape(unsigned int i_ShapeIndex, unsigned int i_nverts, float i_radius);
	virtual ~unShape();

	bool acRender(UInt16 i_Flags, bool i_Textured);
	void acSaveStructure(const char* filename);

	//*void acMollCube(PxVec3 min, PxVec3 max);
	//*void acMollFace(PxVec3 min, PxVec3 max);

	size_t getVerticesCount () { return nverts; }
	size_t getFacesCount () { return nfaces; }

	bool addPxActor(int VertexList);

	void setScale(float i_scale) { m_scale = i_scale; }
	float getScale(void) { return m_scale; }

private:
	int nverts;
	int nfaces;
	float radius;

	/// New Terrain Super Class Inherit
	float m_scale;
	float m_texscale;
	float m_terrainWidth;

///////////////////////////////////////////
////// Spliced GL-VBO /////////////////////
public:
	void acSetBuffers(void);
	void acLoadBuffers(void);
	void acRealBuffers(void);
	void setVertexBuffer(float * pVertexBuffer, int stride);
	void setIndexBuffer(int * pIndexBuffer);
	void setNormalBuffer(char * pNormalBuffer, int stride);
	void setWeightBuffer(char * pWeightBuffer, int stride);
	void setMatrixIndexBuffer(char * pMatrixIndexBuffer, int stride);
	void setTextureCoordNum(int textureCoordNum);
	void setTextureCoordBuffer(int mapId, char * pTextureCoordBuffer, int stride);
	void setTangentSpaceBuffer(int mapId, char * pTangentSpaceBuffer, int stride);

	shapeVertexAry i_VertexBuffer;
	shapeVertexAry i_WeightBuffer;
	shapeVertexAry i_MatrixIndexBuffer;
	shapeVertexAry i_NormalBuffer;
	shapeVertexAry i_TexCoordBuffer;
	//shapeIndicesAry i_IndexBuffer;

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
};

class unShapeBank
{
public:
	unShapeBank();
	virtual ~unShapeBank();

	bool acRender(UInt16 i_Flags, bool i_Textured);
	void acSaveStructure(const char* filename);

	// Radial Mouldings
	/**void acMollTest(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max);
	void acMollFace(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max);
	void acMollSquare(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max);
	void acMollUnSquare(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max);
	void acMollCube(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max);
	void acMollSphere(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max, unsigned int numRimVertices, bool reversed);

	bool addPxActor(int VertexList);*/

	void acCreateShape(unsigned int i_ShapeIndex, float i_radius);
	void acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z);

	/// Shape Elements Storage Bank
	std::vector<unShapeElement*> m_Shape;

private:
	//int nverts;
	//int nfaces;
	//float radius;

	/// New Terrain Super Class Inherit
	//float m_scale;
	//float m_texscale;
	//float m_terrainWidth;

public:
	void acSetBuffers(void);
	void acLoadBuffers(void);
	void acRealBuffers(void);
	void setVertexBuffer(float * pVertexBuffer, int stride);
	void setIndexBuffer(int * pIndexBuffer);
	void setNormalBuffer(char * pNormalBuffer, int stride);
	void setWeightBuffer(char * pWeightBuffer, int stride);
	void setMatrixIndexBuffer(char * pMatrixIndexBuffer, int stride);
	void setTextureCoordNum(int textureCoordNum);
	void setTextureCoordBuffer(int mapId, char * pTextureCoordBuffer, int stride);
	void setTangentSpaceBuffer(int mapId, char * pTangentSpaceBuffer, int stride);
};

};

#endif
#endif