/*

	unIdentManager - Memory Segment Header
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UN_IDENTMANAGER_H
#define UN_IDENTMANAGER_H

#include <string>
#include <map>

#define DllImport  __declspec( dllimport )
#define DllExport  __declspec( dllexport )

namespace UN
{

#define UN_IDENT_LEN 10

extern DllExport std::map< const char * , int > map_globalidents;
extern DllExport std::string m_InheritanceStr;

inline std::string acIdentGen(const char* i_classname, bool i_Inherit = false)
{
	int i_value;
	char casecntbuf[100];

	i_value = map_globalidents[i_classname];
	map_globalidents[i_classname]++;

	itoa(i_value, casecntbuf, 10);

	std::string i_strproc = i_classname;
	std::string i_strnumber = casecntbuf;
	std::string i_identname = i_strproc + i_strnumber;

	if(!i_Inherit) m_InheritanceStr = i_identname;
	else std::string i_inheritname = m_InheritanceStr + i_identname;

	printf("UN:::Dispatch:::NameIdent::: %s\n", i_identname.c_str());

	return i_identname;
};

inline std::string acIdentExt(const char* i_classname, int i_value)
{
	char casecntbuf[100];

	itoa(i_value, casecntbuf, 10);

	std::string i_strproc = i_classname;
	std::string i_strnumber = casecntbuf;
	std::string i_identname = i_strproc + i_strnumber;

	return i_identname;
}

};

#endif