/*

    unShapeMouldings - Open GL Class
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/
#include "pch.h"
#if 0
#include "unShape.h"
#include "../../DigitalMass/source/geometry/ungeometry.h"
#include "../../DigitalMass/Source/Digi/Vertex.h"

using namespace Digi;
using namespace trr;

namespace UN
{

/**void unShape::acMollFace(PxVec3 min, PxVec3 max)
{
#if 0
	// Vertex 1
	m_pVertexBuffer[0] = 0;
	m_pVertexBuffer[1] = 0;
	m_pVertexBuffer[2] = 0;

	// Vertex 2
	m_pVertexBuffer[3] = max.x;
	m_pVertexBuffer[4] = 0;
	m_pVertexBuffer[5] = 0;

	// Vertex 3
	m_pVertexBuffer[6] = -max.x;
	m_pVertexBuffer[7] = -max.y;
	m_pVertexBuffer[8] = -max.z;

	// Vertex 4
	m_pVertexBuffer[9] = 0;
	m_pVertexBuffer[10] = max.y;
	m_pVertexBuffer[12] = 0;
#endif

#if 1
	// Vertex 1
	m_pVertexBuffer[0] = 0;
	m_pVertexBuffer[1] = 0;
	m_pVertexBuffer[2] = 0;

	// Vertex 2
	m_pVertexBuffer[3] = max.x;
	m_pVertexBuffer[4] = 0;
	m_pVertexBuffer[5] = 0;

	// Vertex 3
	m_pVertexBuffer[6] = max.x;
	m_pVertexBuffer[7] = max.y;
	m_pVertexBuffer[8] = 0;

	// Vertex 4
	m_pVertexBuffer[9] = 0;
	m_pVertexBuffer[10] = max.y;
	m_pVertexBuffer[12] = 0;
#endif

#if 1
	// Face 1
	m_pIndexBuffer[0] = 0;
	m_pIndexBuffer[1] = 1;
	m_pIndexBuffer[2] = 2;

	// Face 2
	m_pIndexBuffer[3] = 0;
	m_pIndexBuffer[4] = 2;
	m_pIndexBuffer[5] = 3;
#endif
}*/

/**void unShape::acMollCube/*(PxVec3 min, PxVec3 max)
{
	// Vertex 1	- Facing
	m_pVertexBuffer[0] = min.x;
	m_pVertexBuffer[1] = min.y;
	m_pVertexBuffer[2] = min.z;

	m_pVertexBuffer[3] = min.x + max.x;
	m_pVertexBuffer[4] = min.y;
	m_pVertexBuffer[5] = min.z;

	m_pVertexBuffer[6] = min.x;
	m_pVertexBuffer[7] = min.y + max.y;
	m_pVertexBuffer[8] = min.z;

	// Vertex 2 - Facing
	m_pVertexBuffer[9] = min.x + max.x;
	m_pVertexBuffer[10] = min.y;
	m_pVertexBuffer[12] = min.z;

	m_pVertexBuffer[13] = min.x + max.x;
	m_pVertexBuffer[14] = min.y + max.y;
	m_pVertexBuffer[15] = min.z;

	m_pVertexBuffer[16] = min.x;
	m_pVertexBuffer[17] = min.y + max.y;
	m_pVertexBuffer[18] = min.z;

	// Vertex 3	- Opposite
	m_pVertexBuffer[19] = min.x;
	m_pVertexBuffer[20] = min.y;
	m_pVertexBuffer[21] = min.z + max.z;

	m_pVertexBuffer[22] = min.x + max.x;
	m_pVertexBuffer[23] = min.y;
	m_pVertexBuffer[24] = min.z + max.z;

	m_pVertexBuffer[25] = min.x;
	m_pVertexBuffer[26] = min.y + max.y;
	m_pVertexBuffer[27] = min.z + max.z;

	// Vertex 4	- Opposite
	m_pVertexBuffer[28] = min.x + max.x;
	m_pVertexBuffer[29] = min.y;
	m_pVertexBuffer[30] = min.z + max.z;

	m_pVertexBuffer[31] = min.x + max.x;
	m_pVertexBuffer[32] = min.y + max.y;
	m_pVertexBuffer[33] = min.z + max.z;

	m_pVertexBuffer[34] = min.x;
	m_pVertexBuffer[35] = min.y + max.y;
	m_pVertexBuffer[36] = min.z + max.z;

	// Vertex 5 - Right Side
	m_pVertexBuffer[37] = min.x + max.x;
	m_pVertexBuffer[38] = min.y;
	m_pVertexBuffer[39] = min.z;

	m_pVertexBuffer[40] = min.x + max.x;
	m_pVertexBuffer[41] = min.y;
	m_pVertexBuffer[42] = min.z + max.z;

	m_pVertexBuffer[43] = min.x + max.x;
	m_pVertexBuffer[44] = min.y + max.y;
	m_pVertexBuffer[45] = min.z;

	// Vertex 6 - Right Side
	m_pVertexBuffer[46] = min.x + max.x;
	m_pVertexBuffer[47] = min.y;
	m_pVertexBuffer[48] = min.z + max.z;

	m_pVertexBuffer[49] = min.x + max.x;
	m_pVertexBuffer[50] = min.y + max.y;
	m_pVertexBuffer[51] = min.z + max.z;

	m_pVertexBuffer[52] = min.x + max.x;
	m_pVertexBuffer[53] = min.y + max.y;
	m_pVertexBuffer[54] = min.z;

	// Vertex 7 - Left Side
	m_pVertexBuffer[55] = min.x;
	m_pVertexBuffer[56] = min.y;
	m_pVertexBuffer[57] = min.z;

	m_pVertexBuffer[58] = min.x;
	m_pVertexBuffer[59] = min.y;
	m_pVertexBuffer[60] = min.z + max.z;

	m_pVertexBuffer[61] = min.x;
	m_pVertexBuffer[62] = min.y + max.y;
	m_pVertexBuffer[63] = min.z;

	// Vertex 8 - Left Side
	m_pVertexBuffer[64] = min.x;
	m_pVertexBuffer[65] = min.y;
	m_pVertexBuffer[66] = min.z + max.z;

	m_pVertexBuffer[67] = min.x;
	m_pVertexBuffer[68] = min.y + max.y;
	m_pVertexBuffer[69] = min.z + max.z;

	m_pVertexBuffer[70] = min.x;
	m_pVertexBuffer[71] = min.y + max.y;
	m_pVertexBuffer[72] = min.z;

	// Vertex 9 - Top Side
	m_pVertexBuffer[73] = min.x;
	m_pVertexBuffer[74] = min.y + max.y;
	m_pVertexBuffer[75] = min.z;

	m_pVertexBuffer[76] = min.x + max.x;
	m_pVertexBuffer[77] = min.y + max.y;
	m_pVertexBuffer[78] = min.z;

	m_pVertexBuffer[79] = min.x;
	m_pVertexBuffer[80] = min.y + max.y;
	m_pVertexBuffer[81] = min.z + max.z;

	// Vertex 10 - Top Side
	m_pVertexBuffer[82] = min.x + max.x;
	m_pVertexBuffer[83] = min.y + max.y;
	m_pVertexBuffer[84] = min.z;

	m_pVertexBuffer[85] = min.x + max.x;
	m_pVertexBuffer[86] = min.y + max.y;
	m_pVertexBuffer[87] = min.z + max.z;

	m_pVertexBuffer[88] = min.x;
	m_pVertexBuffer[89] = min.y + max.y;
	m_pVertexBuffer[90] = min.z + max.z;

	// Vertex 11 - Bottom Side
	m_pVertexBuffer[91] = min.x;
	m_pVertexBuffer[92] = min.y;
	m_pVertexBuffer[93] = min.z;

	m_pVertexBuffer[94] = min.x + max.x;
	m_pVertexBuffer[95] = min.y;
	m_pVertexBuffer[96] = min.z;

	m_pVertexBuffer[97] = min.x;
	m_pVertexBuffer[98] = min.y;
	m_pVertexBuffer[99] = min.z + max.z;

	// Vertex 12 - Bottom Side
	m_pVertexBuffer[100] = min.x + max.x;
	m_pVertexBuffer[101] = min.y;
	m_pVertexBuffer[102] = min.z;

	m_pVertexBuffer[103] = min.x + max.x;
	m_pVertexBuffer[104] = min.y;
	m_pVertexBuffer[105] = min.z + max.z;

	m_pVertexBuffer[106] = min.x;
	m_pVertexBuffer[107] = min.y;
	m_pVertexBuffer[108] = min.z + max.z;

#if 0
	for(int i=0; i < SHAPE_UN_FACE_DIM; ++i) { m_pIndexBuffer[i] = i; }
#endif
}*/

void unShapeBank::acMollTest(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max)
{
#if 0
	// Vertex 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = 0;

	// Vertex 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = 0;

	// Vertex 3
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = -50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = -50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = -50;

	// Vertex 4
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = 0;
#endif

#if 0
	// Vertex 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = 0;

	// Vertex 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = 0;

	// Vertex 3
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = 0;

	// Vertex 4
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = 0;
#endif

#if 1
	// Vertex 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = 0;

	// Vertex 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = 0;

	// Vertex 3
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = 0;

	// Vertex 4
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = 0;

	// Vertex 5
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = 0;

	// Vertex 6
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = 50;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = 0;
#endif

#if 1
	// Face 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[0] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[1] = 1;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[2] = 2;

	// Face 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[3] = 3;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[4] = 4;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[5] = 5;
#endif
}

void unShapeBank::acMollFace(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max)
{
	// Vertex 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = min.z;

	// Vertex 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = min.z;

	// Vertex 3
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = min.z;
}

void unShapeBank::acMollSquare(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max)
{
	// Vertex 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = min.z;

	// Vertex 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = min.z;

	// Vertex 3
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = min.z;

	// Vertex 4
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = min.z;

	// Face 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[0] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[1] = 1;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[2] = 2;

	// Face 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[3] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[4] = 2;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[5] = 3;
}

void unShapeBank::acMollUnSquare(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max)
{
	// Vertex 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = min.z;

	// Vertex 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = min.z;

	// Vertex 3
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = min.z;

	// Vertex 4
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[11] = min.z;

	// Vertex 5
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[13] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[14] = min.z;

	// Vertex 6
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[15] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[16] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[17] = min.z;

	// Face 1
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[0] = 0;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[1] = 1;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[2] = 2;

	// Face 2
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[3] = 3;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[4] = 4;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[5] = 5;
}

void unShapeBank::acMollCube(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max)
{
	// Vertex 1	- Facing
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = min.z;

	// Vertex 2 - Facing
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[11] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[13] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[14] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[15] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[16] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[17] = min.z;

	// Vertex 3	- Opposite
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[18] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[19] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[20] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[21] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[22] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[23] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[24] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[25] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[26] = min.z + max.z;

	// Vertex 4	- Opposite
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[27] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[28] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[29] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[30] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[31] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[32] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[33] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[34] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[35] = min.z + max.z;

	// Vertex 5 - Right Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[36] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[37] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[38] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[39] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[40] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[41] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[42] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[43] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[44] = min.z;

	// Vertex 6 - Right Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[45] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[46] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[47] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[48] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[49] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[50] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[51] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[52] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[53] = min.z;

	// Vertex 7 - Left Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[54] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[55] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[56] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[57] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[58] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[59] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[60] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[61] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[62] = min.z;

	// Vertex 8 - Left Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[63] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[64] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[65] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[66] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[67] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[68] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[69] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[70] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[71] = min.z;

#if 0
	// Vertex 9 - Top Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[72] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[73] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[74] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[75] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[76] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[77] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[78] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[79] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[80] = min.z + max.z;

	// Vertex 10 - Top Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[81] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[82] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[83] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[84] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[85] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[86] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[87] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[88] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[89] = min.z + max.z;

	// Vertex 11 - Bottom Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[90] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[91] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[92] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[93] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[94] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[95] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[96] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[97] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[98] = min.z + max.z;

	// Vertex 12 - Bottom Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[99] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[100] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[101] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[102] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[103] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[104] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[105] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[106] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[107] = min.z + max.z;
#endif

	//for(int i=0; i < SHAPE_UN_FACE_DIM; ++i) { m_pIndexBuffer[i] = i; }
}

// Send Solid Face Descriptions to buffer storage
//memcpy(&i_IndexBuffer[0], &CC.UnFace[0], sizeof(int)*(nfaces+nseals));

void unShapeBank::acMollSphere(unsigned int i_ShapeIndex, unsigned int i_SetIndex, PxVec3 min, PxVec3 max, unsigned int numRimVertices, bool reversed)
{
	Vertex size(max.x - min.x, max.y - min.y, max.z - min.z);

	size_t numVertices = numRimVertices + ((numRimVertices / 2 - 1) * numRimVertices) * 2 + 2;
	size_t numTriangles = numRimVertices * (numRimVertices / 2 - 1) * 4 + 2 * numRimVertices;
	float radius = 1.0f;

	UInt32 *prevVerticesT = new UInt32[numVertices];
	UInt32 *newVerticesT = new UInt32[numVertices];
	UInt32 *prevVerticesB = new UInt32[numVertices];
	UInt32 *newVerticesB = new UInt32[numVertices];
	Face3 *triangles = new Face3[numTriangles];

	static const float twoPI = 2 * PI;

	Vert2d *texels = new Vert2d [numVertices];
	Vertex *vertices = new Vertex [numVertices];
	Vertex *normals = new Vertex [numVertices];

	// Number of degrees between layers.
	float radiusStep = 180.0f / numRimVertices;
	float vertRadius = radius;

	UInt32 currVertID = 0;

	// Generate the first series of vertices (the outer circle).
	// Calculate u,v for them.
	for (UInt32 i = 0; i < numRimVertices; i++)
		{
		float newRadius = radius;
		float newHeight = 0.0f;
		float angle = i * 2.0f * radiusStep * twoPI / 360.0f;
		vertices[i] = Vertex (newRadius * (float) cos (angle), newHeight, newRadius * (float) sin (angle));
		texels[i] = Vert2d ((float) cos (angle) * 0.5f + 0.5f, (float) sin (angle) * 0.5f + 0.5f);
		prevVerticesT[currVertID] = currVertID;
		prevVerticesB[currVertID] = currVertID;
		currVertID++;
		}

	UInt32 currTriID = 0;

	// First create the layered triangle strips.
	for (UInt32 i = 1; i < (numRimVertices / 2); i++)
		{
		//-----
		// First create a new series of vertices.
		//-----
		// Angle from the center to the new circle of vertices.
		float newAngle = i * radiusStep * twoPI / 360.0f;
		// Radius of the new circle of vertices.
		float newRadius = radius * (float) cos (newAngle);
		// Height of the new circle of vertices.
		float newHeight = vertRadius * (float) sin (newAngle);
		// UV radius.
		float uvRadius = (1.0f - 2.0f * (float) i / (float)numRimVertices) * 0.5f;
		for (UInt32 j = 0; j < numRimVertices; j++)
			{
			float angle = j * 2.0f * radiusStep * twoPI / 360.0f;

			vertices[currVertID] = Vertex (newRadius * (float) cos (angle),
			newHeight, newRadius * (float) sin (angle));
			float u = uvRadius * (float) cos (angle) + 0.5f;
			float v = uvRadius * (float) sin (angle) + 0.5f;
			texels[currVertID] = Vert2d (u, v);
			newVerticesT[j] = currVertID;

			currVertID++;

			vertices[currVertID] = Vertex (newRadius * (float) cos (angle),
			-newHeight, newRadius * (float) sin (angle));
			texels[currVertID] = Vert2d (u, v);
			newVerticesB[j] = currVertID;

			currVertID++;
			}

		//-----
		// Now make the triangle strips.
		//-----
		for (UInt32 j = 0; j < numRimVertices; j++)
			{
			UInt32 j1num = (j+1) % numRimVertices;

			Face3 tri1(prevVerticesT[j], newVerticesT[j1num], newVerticesT[j], 0);
			triangles[currTriID] = tri1;
			currTriID++;

			Face3 tri2(prevVerticesT[j], prevVerticesT[j1num], newVerticesT[j1num], 0);
			triangles[currTriID] = tri2;
			currTriID++;

			Face3 tri3(prevVerticesB[j], newVerticesB[j1num], newVerticesB[j], 0);
			triangles[currTriID] = tri3;
			currTriID++;

			Face3 tri4(prevVerticesB[j], prevVerticesB[j1num], newVerticesB[j1num], 0);
			triangles[currTriID] = tri4;
			currTriID++;
			}

		//-----
		// Copy the new vertex array to prev_vertices.
		//-----
			for (UInt32 j = 0 ; j < numRimVertices ; j++)
			{
			prevVerticesT[j] = newVerticesT[j];
			prevVerticesB[j] = newVerticesB[j];
			}
		}

	// Create the top and bottom vertices.
	UInt32 topVertex = currVertID;
	vertices[currVertID] = Vertex (0.0f, vertRadius, 0.0f);
	texels[currVertID] = Vert2d (0.5f, 0.5f);
	currVertID++;
	UInt32 bottomVertex = 0;

	bottomVertex = currVertID;
	vertices[currVertID] = Vertex (0.0f, -vertRadius, 0.0f);
	texels[currVertID] = Vert2d (0.5f, 0.5f);
	currVertID++;

	//-----
	// Make the top triangle fan.
	//-----
	for (UInt32 j = 0 ; j < numRimVertices ; j++)
		{
		UInt32 j1num = (j+1)%numRimVertices;
		Face3 tri(topVertex, prevVerticesT[j], prevVerticesT[j1num], 0);
		triangles[currTriID] = tri;
		currTriID++;
		}

	//-----
	// Make the bottom triangle fan.
	//-----
	for (UInt32 j = 0 ; j < numRimVertices ; j++)
		{
		UInt32 j1num = (j+1)%numRimVertices;
		Face3 tri(bottomVertex, prevVerticesB[j], prevVerticesB[j1num], 0);
		triangles[currTriID] = tri;
		currTriID++;
		}

#if 1
	// Scale and shift all the vertices.
	for (UInt32 i = 0 ; i < currVertID ; i++)
		{
		vertices[i][0] *= size[0];
		vertices[i][1] *= size[1];
		vertices[i][2] *= size[2];
		Vertex normal = vertices[i];
		normal.Normalize();
		if(reversed)
			{
			normals[i][0] = -normal[0];
			normals[i][1] = -normal[1];
			normals[i][2] = -normal[2];
			}
		else
			{
			normals[i][0] = normal[0];
			normals[i][1] = normal[1];
			normals[i][2] = normal[2];
			}
		}
#endif

#if 1
	//printf("Trace currVertID %i\n", currVertID);
	//printf("Trace numVertices %i\n", numVertices);
	//printf("Trace numTriangles %i\n", numTriangles);

	UInt32 i_VertCount = 0;
	for (UInt32 i = 0 ; i < numVertices ; i++)
		{
		//printf("Trace i %i\n", i);
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[i_VertCount] = vertices[i][0];
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[i_VertCount+1] = vertices[i][1];
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[i_VertCount+2] = vertices[i][2];

		//m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pNormalBuffer[i_VertCount] = vertices[i][0];
		//m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pNormalBuffer[i_VertCount+1] = vertices[i][1];
		//m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pNormalBuffer[i_VertCount+2] = vertices[i][2];
		i_VertCount += 3;
#pragma message("Insert UV texture coord data")
		}
#endif

#if 0
	for (UInt32 i = 0 ; i < 35 ; i++)
		{
		printf("Trace %i\n", i);
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[i*3] = min.x;
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[(i*3)+1] = min.y;
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[(i*3)+2] = min.z + max.z;
		}
#endif

#if 0
	// Vertex 1	- Facing
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[0] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[1] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[2] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[3] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[4] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[5] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[6] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[7] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[8] = min.z;

	// Vertex 2 - Facing
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[9] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[10] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[11] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[12] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[13] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[14] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[15] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[16] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[17] = min.z;

	// Vertex 3	- Opposite
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[18] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[19] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[20] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[21] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[22] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[23] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[24] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[25] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[26] = min.z + max.z;

	// Vertex 4	- Opposite
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[27] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[28] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[29] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[30] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[31] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[32] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[33] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[34] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[35] = min.z + max.z;

	// Vertex 5 - Right Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[36] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[37] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[38] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[39] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[40] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[41] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[42] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[43] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[44] = min.z;

	// Vertex 6 - Right Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[45] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[46] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[47] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[48] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[49] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[50] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[51] = min.x + max.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[52] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[53] = min.z;

	// Vertex 7 - Left Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[54] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[55] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[56] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[57] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[58] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[59] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[60] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[61] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[62] = min.z;

	// Vertex 8 - Left Side
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[63] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[64] = min.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[65] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[66] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[67] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[68] = min.z + max.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[69] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[70] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[71] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[69] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[70] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[71] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[72] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[73] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[74] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[75] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[76] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[77] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[78] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[79] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[80] = min.z;

	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[81] = min.x;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[82] = min.y + max.y;
	m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pVertexBuffer[83] = min.z;
#endif

#if 1
	// Swap all triangles if needed.
	if (reversed)
		{
		for (size_t i = 0 ; i < numTriangles ; i++)
			{
			int s = triangles[i].m_v1;
			triangles[i].m_v1 = triangles[i].m_v3;
			triangles[i].m_v3 = s;
			}
		}
#endif

#if 1
	UInt32 i_IndexCount = 0;
	for (UInt32 i = 0 ; i < numTriangles ; ++i)
		{
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[i_IndexCount] = triangles[i].m_v1;
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[i_IndexCount+1] = triangles[i].m_v2;
		m_Shape[i_ShapeIndex]->m_BufferSet[i_SetIndex]->m_pIndexBuffer[i_IndexCount+2] = triangles[i].m_v3;
		i_IndexCount += 3;
		}
#endif

#if 1
	delete[] prevVerticesT;
	delete[] newVerticesT;
	delete[] prevVerticesB;
	delete[] newVerticesB;
	delete[] triangles;
	delete[] texels;
	delete[] vertices;
	delete[] normals;
#endif

#if 0
	for(int i=0; i < SHAPE_UN_FACE_DIM; ++i) { m_pIndexBuffer[i] = i; }
#endif
}

};
#endif