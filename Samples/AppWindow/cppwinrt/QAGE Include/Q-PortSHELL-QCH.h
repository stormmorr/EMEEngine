/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component - QCH -
	*/#include "pch.h"/*- Minor Component -= QCH Class Structures =-

*/

#ifndef __Q_PortSHELL_QCH__
#define __Q_PortSHELL_QCH__

//#### INCLUDE ENGINE SPECIFIC HEADERS

#include <iostream>
//#include "boost/multi_array.hpp"
//#include "boost/array.hpp"
//#include "boost/cstdlib.hpp"

//#####===--- [QCH] CLASS STRUCTURES ---===#####

namespace GVARS
{

class PolyLISTCLS
{
public:
	int								LIVE;
	int								POLY;
	int								TYPE;
	int								REND;
	int								TEXID;
	unsigned int TEX;
	float							SCALE;
	int								MESHWRAP;
	QpoVertex *						VERT;
	QpoVec3d						POS;

	int								mesh;
};

//typedef boost::multi_array<PolyLISTCLS, 1> PolyLISTarray;
//typedef PolyLISTarray::index index;

};

#endif