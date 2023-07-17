/*

    UNcplusinterface - C++ mapping
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef _UN_CplusInterface_
#define _UN_CplusInterface_

#include <vector>
#include "../Utility/datatypes.h"

//#include "../Geometry/unTrr.h"

namespace UN
{

#if 0
enum UnifiedVariableDesc
{
  UNV_PUBLIC,
  UNV_PRIVATE,
  UNV_PROTECTED,
};
#endif

#if 0
typedef struct UNmap
{
  std::vector<int> vecint;
  std::vector<unsigned int> vecuint;
  std::vector<float> vecfloat;
  std::vector<char> vecchar;
  std::vector<unsigned char> vecuchar;
  std::vector<bool> vecbool;

  std::vector<class UN::UNclass> vecclass;
} UNmap;
#endif

};

#endif