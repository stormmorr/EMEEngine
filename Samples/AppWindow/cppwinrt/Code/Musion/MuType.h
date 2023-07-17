/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef MUTYPE_H
#define MUTYPE_H

#include <vector>
#include <math.h>

#if 0
#define uint unsigned int
#else
#define uint int
#endif

using namespace ecoin;

namespace ecoin
{
	enum
	{
		MuTYPE_Function,
		MuTYPE_Variable,
		MuTYPE_System,
		MuTYPE_Class_Variable,
		MuTYPE_Any_Class_Variable,
		MuTYPE_Code,
		MuTYPE_Operator,
		MuTYPE_Condition,
		MuTYPE_Class,
		MuTYPE_Any,
		MuTYPE_Total
	};

#ifdef ECOIN_OSI_MEM_MUSION
	class MuType : public ecom_base
		{
		public:
			MuType() : m_Type(MuTYPE_Any) {};
			MuType(uint f_Type) : m_Type(f_Type) {};
			uint m_Type;
		};
#else
	class MuType
		{
		public:
			MuType() : m_Type(MuTYPE_Any) {};
			MuType(uint f_Type) : m_Type(f_Type) {};
			uint m_Type;
		};
#endif

}


#endif