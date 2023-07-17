/*

	DRAT Definition ALPHA - Deep Recursive Attributes
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#define DRAT_HEADER

#include <string>
#include <vector>

#include "../Base/unBase.h"

namespace DRAT
{

class FileDescriptor
{
public:
	std::string m_Filename;
	std::string m_Ext;

	/// Flags
	bool SaveIncrement;
	unsigned short Flags;

private:
	std::vector<UN::UNclass> m_class;

public:
	DRAT::DratDef _dratAttr;
};

};