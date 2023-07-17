/*

	Command - Osirus Command
	Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef OSICLASS_H
#define OSICLASS_H

#include "../Utility/nPatriciaTrie.h"
#include "Function.h"

namespace OSI
{

typedef struct Class
{
	std::string m_Name;

	nPatriciaTrie<Function*>* m_FunctionTrie;
	std::vector<Function> vec_Function;

	unsigned int nom_Function;
} Class;

};

#endif