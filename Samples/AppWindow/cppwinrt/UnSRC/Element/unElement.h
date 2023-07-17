/*

    unElement - Open GL Class/Struct clone_structor
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unElement_h__
#define __unElement_h__

#if 1
#include "../Utility/DataTypes.h"
#include "../Render/unBufferSet.h"

/// PhysX Includes
//*#include "PxPhysics.h"
//*#include "PxCooking.h"
//*#include "PxVec3.h"
//*#include "PxActor.h"

//#include "boost/multi_array.hpp"
//#include "boost/array.hpp"
//#include "boost/cstdlib.hpp"

//*** INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

//*using namespace physx;

#define UN_ELEMENT_DIM 15000

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

//typedef boost::multi_array<float, 1> shapeVertexAry;
//typedef shapeVertexAry::index shapeBufferIndex;

//typedef boost::multi_array<int, 1> shapeIndicesAry;
//typedef shapeIndicesAry::index shapeIndicesIndex;

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

class Element_CC //Class Cache
{
public:
	float Cos, Sin;
	pVector pVector1, pResult;
	unsigned int m_ExecMode;
	float ScaleFT;
	int vPort[4];
	unsigned int i, k, l;

	QpoVec3d campos;
	QpoVec3d destpos;
	QpoVec3d transvert;
	QpoVec3d InVec;
	QpoVec3d UpVec;
	QpoVec3d LeftVec;

	float m_Red;
	float m_Green;
	float m_Blue;
	float m_Alpha;

	QpoVec3d Vert1;
	QpoVec3d Vert2;
	QpoVec3d Vert3;
	QpoVec3d Vert4;

	float m_1U;
	float m_1V;
	float m_2U;
	float m_2V;
	float m_3U;
	float m_3V;
	float m_4U;
	float m_4V;

	bool setExecMode(int i_ExecMode);
};

typedef struct unElementInstance
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
} unElementInstance;

class unElement
{
public:
	unElement() {}
	unElement(unsigned int i_ShapeIndex, unsigned int i_nverts, float i_radius);
	virtual ~unElement();

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

	//shapeVertexAry i_VertexBuffer;
	//shapeVertexAry i_WeightBuffer;
	//shapeVertexAry i_MatrixIndexBuffer;
	//shapeVertexAry i_NormalBuffer;
	//shapeVertexAry i_TexCoordBuffer;
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

class unElementBank
{
public:
	unElementBank();
	~unElementBank();

	bool acRender(UInt16 i_Flags, bool i_Textured);
	void acSaveStructure(const char* filename);

	void acCreateShape(unsigned int i_ShapeIndex, float i_radius);
	void acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z);

	void acReset(void);
	void acSoftReset(void);

	void acSetBuffers(void);

	void acRender(void);

	int acAdd_Bitmap(GLuint f_Bitmap);

	bool Poly_AddOnce(QpoVertex * Verts, int NumVerts, unsigned int Bitmap, UInt8 TypeFLAGS, UInt8 RendFLAGS, float Scale);

	/// Shape Elements Storage Bank
	std::vector<unElement*> m_Shape;

private:
	int nverts;
	int nfaces;

	float *m_Vertex;
	float *m_Color;
	float *m_TextureCoord;
	GLuint *m_Bitmap;
	GLuint *m_Index;

	void acAdd_Vertex(float f_U, float f_V, int f_Bitmap,
					  float f_X, float f_Y, float f_Z,
					  float f_R, float f_G, float f_B, float f_A);

public:
	GLuint m_VertexBuffer;
	GLuint m_ColorBuffer;
	GLuint m_TextureCoordBuffer;
	GLuint m_IndexBuffer;

	Element_CC CC;

	std::vector<GLuint> m_vec_Bitmap;

	int m_VertexCount;
	int m_Triple;
	int m_FaceCount;

	GLuint mElProgram;

	GLint m0ElVertexAttribLocation;
	GLint m1ElColorAttribLocation;
	GLint m2ElTexCoordAttribLocation;

	GLint mElModelUniformLocation;
	GLint mElViewUniformLocation;
	GLint mElProjUniformLocation;
	GLint mElTextureUniformLocation;
	GLint mElLightPosUniformLocation;
};

};

#endif
#endif