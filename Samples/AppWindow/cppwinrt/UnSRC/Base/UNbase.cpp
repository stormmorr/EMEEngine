/*

    UNIbase - Base Definitions
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "UNbase.h"

using namespace UN;

UNclass::UNclass(const UNclass &src)
{
	m_public = src.m_public;
	m_private = src.m_private;
	m_protected = src.m_protected;
}

UNclass::UNclass(const UNstruct &src, unsigned int e_index)
{
#if 0
	switch(e_index)
		{
		case UNC_PUBLIC: m_public = &src;
		case UNC_PRIVATE: m_private = &src;
		case UNC_PROTECTED: m_protected = &src;
		}
#endif
}