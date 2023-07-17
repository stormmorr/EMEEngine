/*

	unBaseBoost
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "boost/multi_array.hpp"
#include "boost/array.hpp"
#include "boost/cstdlib.hpp"
#include "boost/any.hpp"

namespace unBoost
{
using boost::any_cast;
boost::any Variable = 5;

void functy(const boost::any & operand)
	{
	any_cast<int>(operand);
	//operand += 5;
	}

//////// Boost Declarations ////////
//typedef boost::multi_array<unAvatar, 1> barAvatarArray;
//typedef boost::multi_array<unMesh, 1> barMeshArray;
typedef boost::multi_array<unLight, 1> barLightArray;
//typedef boost::multi_array<unObject, 1> barObjectArray;
//typedef boost::multi_array<unPoly, 1> barPolyOnceArray;
//typedef boost::multi_arr