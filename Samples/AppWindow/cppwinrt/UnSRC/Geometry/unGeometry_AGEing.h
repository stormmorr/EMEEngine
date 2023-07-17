/*

    unGeometry - C++ mapping
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef _UN_GEOMETRY_
#define _UN_GEOMETRY_

#include "../Digi/DataTypes.h"
#include "../Digi/Vertex.h"

namespace trr
{

#define TRRFACE_INST 0
#define TRRFACE_TERM 1
#define TRRFACE_XSPAN 2
#define TRRFACE_XTERM 3
#define TRRFACE_YSPAN 4
#define TRRFACE_YTERM 5

typedef struct Face3
{
	Face3() {};
	Face3(unsigned int i_v1, unsigned int i_v2, unsigned int i_v3, int i_Orientation)
		{
		m_v1 = i_v1;
		m_v2 = i_v2;
		m_v3 = i_v3;
		m_Orientation = i_Orientation;
		}
	~Face3() {};

	UInt32 m_v1;
	UInt32 m_v2;
	UInt32 m_v3;
	Digi::Vertex m_Normal;
	int m_Orientation;
}Face3;

typedef struct Face3M
{
	int m_v1;
	int m_v2;
	int m_v3;
	int m_material;
}Face3M;

typedef struct Face4
{
	UInt32 m_v1;
	UInt32 m_v2;
	UInt32 m_v3;
	UInt32 m_v4;
}Face4;

}

#endif