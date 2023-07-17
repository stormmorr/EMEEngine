/*

qcom.h - ECOM Native Decl osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef PREDATOR_H
#define PREDATOR_H

#include "Include/Cube.h"

#include "Code/Work/Schedular.h"

#include "Code/Cube/qcom.h"

#include <vector>
#include <map>
#include <boost/any.hpp>

using namespace Cube;
using namespace ecoin;

namespace Cube
{
extern int g_InstantIDX;
extern std::vector<std::string>		g_vec_InstantFunction_NameGroup;
extern std::vector<time_t>			g_vec_InstantFunction_Time;

//unused
extern std::vector<int>				g_vec_InstantFunction_Type;

extern int ag_Register_FunctionConstructorInstantly(std::string f_Function_NameGroup);
extern void ag_Click_InstantFunction(std::string f_Function_NameGroup);

};

#endif