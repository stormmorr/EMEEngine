/*

VoxelGrid.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "predator.h"

#include "Code/CLS/Target.h"

#include "qam.h"

using namespace Cube;

namespace Cube
{
int g_InstantIDX = 1;
std::vector<std::string>		g_vec_InstantFunction_NameGroup;
std::vector<time_t>				g_vec_InstantFunction_Time;

//unused
extern std::vector<int>				g_vec_InstantFunction_Type;

int ag_Register_FunctionConstructorInstantly(std::string f_Function_NameGroup)
{
	time_t f_T;
	time(&f_T);
	g_vec_InstantFunction_Time.push_back(f_T);
	g_vec_InstantFunction_NameGroup.push_back(f_Function_NameGroup);

	return g_vec_InstantFunction_NameGroup.size() - 1;
}

void ag_Click_InstantFunction(std::string f_Function_NameGroup)
{
	ag_Click(f_Function_NameGroup);
}

};