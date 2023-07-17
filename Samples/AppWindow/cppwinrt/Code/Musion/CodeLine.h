/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CODELINE_H
#define CODELINE_H

#include <vector>
#include <math.h>

#include "MuType.h"
#include "Code.h"
#include "Variable.h"
#include "Operator.h"
#include "Condition.h"
#include "System.h"

namespace ecoin
{

	enum MuLine
	{
		MuLine_Init_Var,		//1 V = 1								//V
		MuLine_Init_ClassVar,	//CV = V, CV							//CV
		MuLine_Assign,			//2 V = V								//V
		MuLine_Assign_Opr,		//V += V								//V
		MuLine_Condition_Ajax,	//V == V								//V
		MuLine_For_Loop,		//4 V = 1 if(V < 1) V++					//V
		MuLine_Function,		//V/CV = fcn(V, CV) math library		//V
		MuLine_Function_Custom, //V/VC = fundef(V, CV)					//CV
		MuLine_Function_Reflect,//V/EV reflectionfunctioncall(V, EV)	//EV (EV = ecom_base)
		MuLine_Return,			//return(V / CV)						//CV
		MuLine_Template,		//template(V)							//V/CV/EV
		MuLine_ClassStart,		//V/CV = clsdef(V, CV)					//CV
		MuLine_MAX
	};
	
	class Function;

	class CodeLine : public MuType
	{
	public:
		CodeLine() { acClear(); };
		CodeLine(std::string f_Line, uint* f_CHK, System* f_System);
		~CodeLine();

		void acClear(void)
			{
			m_vec_Code.clear();
			m_vec_Variable.clear();
			m_vec_Operator.clear();
			m_CodeString.clear();
			m_Execute = true;
			m_Returning = false;
			}

		int acSearch_CodeType(uint f_TYPE);

		void ac_Contract_Function(std::shared_ptr<Contract> f_Contract, std::shared_ptr<Function> f_Function);

		void ac_Compile_Execute(void);

		void ac_Execute(void);

		System* m_System;

		std::vector<std::shared_ptr<Code>> m_vec_Code;
		std::vector<std::shared_ptr<Variable>> m_vec_Variable;
		std::vector<std::shared_ptr<Operator>> m_vec_Operator;

		std::shared_ptr<Function> m_Function;
		std::shared_ptr<Contract> m_Contract;

		std::string m_CodeString;
		int m_ConditionCountID;
		uint m_CodeLine;
		bool m_Returning;
		bool m_Execute;
	};

};

#endif