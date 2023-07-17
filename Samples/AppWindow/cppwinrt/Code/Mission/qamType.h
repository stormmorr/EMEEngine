/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAMTYPE_H
#define QAMTYPE_H

#include <vector>
#include <math.h>

#if 0
#define uint unsigned int
#else
#define uint int
#endif

#ifdef ECOIN
using namespace ecoin;
#endif

namespace ecoin
{
	enum
	{
		qamTYPE_Trigger,
		qamTYPE_Variable,
		qamTYPE_Spawn,
		qamTYPE_Event,
		qamTYPE_Terrain,
		qamTYPE_Function,
		qamTYPE_System,
		qamTYPE_Graph,
		qamTYPE_QAM,
		qamTYPE_Any,
		qamTYPE_Total
	};

	class qamType : public ecom_base
		{
		public:
			qamType() : m_Type(qamTYPE_Any) {};
			qamType(uint f_Type) : m_Type(f_Type) {};
			uint m_Type;
		};

}


#endif