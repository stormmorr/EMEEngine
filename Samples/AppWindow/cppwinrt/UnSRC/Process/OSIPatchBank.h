/*

	OSIPatchBank - Image Overlay
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef OSIPATCHBANK_H
#define OSIPATCHBANK_H

#include <windows.h>
#include <tlhelp32.h> // for the process snapshot

	//Cross-plat requirements
#include <vector>
#include <string>

#include "TCTraverse.h"
#include "MemWalk.h"

#include <map>

#include "SDL.h"

using namespace std;
using std::string;

namespace Point
{

class OSIPatchBank
{
public:
	OSIPatchBank();
	~OSIPatchBank();

	void acPush(std::string i_PatchName);
	void acInfo(const char* i_Filename);

	//std::vector<unPatch*> m_Patch;
	//std::vector<unPatchFunction*> m_Function;

	//std::map<const char *, std::vector<unPatchFunction*>*> map_Function;

	std::string m_Attribute;
};

	//typedef void (CALLBACK* LPFNDLLFUNC1)(void (*i_FunctionPTR)(QpoAvatarFlags * i_AV, const char * String, QpoTransform * Bone));
	//typedef float (CALLBACK* LPFNDLLFUNC10)(float (*i_FunctionPTR)(unsigned int i_Select, int in_X, int in_Y, float in_Z));
	typedef float (*LPFNDLLFUNC10)(unsigned int i_Select, int in_X, int in_Y, float in_Z);

};

#endif