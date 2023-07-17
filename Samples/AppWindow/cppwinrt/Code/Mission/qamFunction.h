/*

Function - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAM_FUNCTION_H
#define QAM_FUNCTION_H

#include <vector>
#include <math.h>

#include "Code/Musion/MuType.h"
#include "Code/Musion/Variable.h"
#include "Code/Musion/Code.h"
#include "Code/Musion/Operator.h"

#include "Code/Mission/qam.h"

namespace ecoin
{

	enum
	{
		qamFunc_RandFloat,
		qamFunc_RandInt,
		qamFunc_Sin,
		qamFunc_Cos,
		qamFunc_Tan,
		qamFunc_Log,
		qamFunc_InvSin,
		qamFunc_InvCos,
		qamFunc_InvTan,
		qamFunc_Sqr,
		qamFunc_Sqrt,
		qamFunc_ArcTan2,
		qamFunc_Gate_NOT,
		qamFunc_Gate_AND,
		qamFunc_Gate_OR,
		qamFunc_Gate_XOR,
		qamFunc_Gate_NAND,
		qamFunc_Gate_NOR,
		qamFunc_Gate_XNOR,
		qamFunc_Live,
		qamFuncGLOBAL_,
	};

	class qamFunction : public qamType
		{
#if 0
		public:
			qamFunction() : qamType(qamTYPE_Function) { m_Updated = false; m_TriggerID = -1; };
			qamFunction(uint f_Function) : qamType(qamTYPE_Function), m_Function(f_Function)
				{
				m_Updated = false;
				m_Function = f_Function;
				m_TriggerID = -1;
				};

			template<class Var_Type>
			uint acPrep_addVariable(Variable f_Var);

			template<class Var_Type>
			qamVariable acExecute(void);

			uint m_Function;

			float m_X;
			float m_Y;
			float m_Z;

			float m_Xrot;
			float m_Yrot;
			float m_Zrot;

			int m_TriggerID;

			template<class Var_Type>
			std::vector<std::shared_ptr<Code>> m_vec_Code;
			std::vector<std::shared_ptr<Variable>> m_vec_Variable;
			std::vector<std::shared_ptr<Operator>> m_vec_Operator;

			bool m_Updated;
#endif
		};

	extern int agFind_FunctionType(std::string f_String);

};


#endif