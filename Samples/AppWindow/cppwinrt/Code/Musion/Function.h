/*

Function - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <math.h>

#include "Code.h"
#include "CodeLine.h"
#include "MuType.h"
#include "Operator.h"
#include "System.h"
#include "Variable.h"

namespace ecoin
{

	enum MuFunc
	{
		MuFunc_Default,
		MuFunc_Reflection,
		MuFunc_Custom,
		MuFunc_Frame,
		MuFunc_RandFloat,
		MuFunc_RandInt,
		MuFunc_Sin,
		MuFunc_Cos,
		MuFunc_Tan,
		MuFunc_Log,
		MuFunc_InvSin,
		MuFunc_InvCos,
		MuFunc_InvTan,
		MuFunc_Sqr,
		MuFunc_Sqrt,
		MuFunc_ArcTan2,
		MuFunc_Gate_NOT,
		MuFunc_Gate_AND,
		MuFunc_Gate_OR,
		MuFunc_Gate_XOR,
		MuFunc_Gate_NAND,
		MuFunc_Gate_NOR,
		MuFunc_Gate_XNOR,
		MuFunc_MAX_
	};

	class Function : public MuType
		{
		public:
			Function() : MuType(MuTYPE_Function)
				{
				m_Contract = nullptr;
				m_Function = 0;
				m_Start_CodeLine = nullptr;
				m_vec_CodeLine.clear();
				m_Line.clear();
				m_MxName.clear();
				m_lnk_Class = nullptr;
				m_Inst_ClassVar = nullptr;
				};

			Function(uint f_Function) : MuType(MuTYPE_Function), m_Function(f_Function)
				{
				m_Contract = nullptr;
				m_Start_CodeLine = nullptr;
				m_vec_CodeLine.clear();
				m_Line.clear();
				m_MxName.clear();
				m_lnk_Class = nullptr;
				m_Inst_ClassVar = nullptr;
				};

			Function(uint f_Function, std::shared_ptr<Contract> f_Contract) : MuType(MuTYPE_Function), m_Function(f_Function)
				{
				m_Contract = f_Contract;
				m_Start_CodeLine = nullptr;
				m_vec_CodeLine.clear();
				m_Line.clear();
				m_MxName.clear();
				m_lnk_Class = nullptr;
				m_Inst_ClassVar = nullptr;
				};

#ifdef ESL_FUNCTION_SCOPE
			uint acPrep_addVariable(std::shared_ptr<Variable> f_Var);
#endif

			std::shared_ptr<Variable> acExecute(std::shared_ptr<Variable> f_A = nullptr, std::shared_ptr<Variable> f_B = nullptr);

#ifdef ESL_FUNCTION_SCOPE
			std::shared_ptr<Variable> acFind_Var(std::string f_VarName);
			std::shared_ptr<ClassVar> acFind_ClassVar(std::string f_VarName);
#endif

			int m_Function;

			std::shared_ptr<Class> m_lnk_Class;
			std::shared_ptr<CodeLine> m_Start_CodeLine;
			std::vector<std::shared_ptr<CodeLine>> m_vec_CodeLine;

			std::shared_ptr<ClassVar> m_Inst_ClassVar;

			std::vector<std::string> m_Line;
			std::string m_MxName;
			std::string m_ClassName;

			std::shared_ptr<Contract> m_Contract;
		};

	extern int agFind_FunctionType(std::string f_String);

	extern std::shared_ptr<Variable> ag_Find_Var(std::string f_String, std::shared_ptr<Variable> f_Variable, std::shared_ptr<Contract> f_Contract);
	extern std::shared_ptr<ClassVar> ag_Find_ClassVar(std::string f_VarName, std::shared_ptr<ClassVar> f_ClassVar, std::shared_ptr<Contract> f_Contract);

	extern void ag_New_Var(std::shared_ptr<Variable> f_Variable, std::shared_ptr<Contract> f_Contract);
	extern void ag_New_ClassVar(std::shared_ptr<ClassVar> f_ClassVar, std::shared_ptr<Contract> f_Contract);
};


#endif