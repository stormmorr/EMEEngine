/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CODE_H
#define CODE_H

#include <vector>
#include <math.h>

#include "MuType.h"
#include "Variable.h"
#include "Condition.h"

namespace ecoin
{

#if 0 //Elevated to Variable.h
	enum MuCode
	{
		MuCode_Var,
		MuCode_ClassVar,
		MuCode_System,
		MuCode_Constant,
		MuCode_Operator,
		MuCode_Condition,
		MuCode_For_Loop,
		MuCode_Function,
		MuCode_FunctionStart,
		MuCode_Parameter,
		MuCode_ClassStart,
		MuCode_Return,
		MuCode_Template,
		MuCode_Total,
		MuCode_Override
	};
#endif

	enum
	{
		MuNameCall_Type_VarVar,
		MuNameCall_Type_VarIndexInt,
		MuNameCall_Type_MemberVar,
		MuNameCall_Type_MemberIndexInt,
		MuNameCall_Type_ClassVar,
		MuNameCall_Type_Total
	};

	class Contract;
	class Function;
	class Class;

	class Code : public MuType
	{
	public:
		Code();
		Code(std::string f_Line, uint* f_CHK, uint f_Index, uint f_CodeType = MuCode_Var, uint f_VarType = MuVar_Full, std::shared_ptr<Variable> f_PushVar = nullptr);

		~Code()
			{ acClear(); };

		void acClear(void)
			{
			m_Name.clear();
			m_Number.clear();
			m_Type.clear();
			m_Condition.clear();
			m_vec_Type.clear();
			m_vec_VarType.clear();
			m_MxName.clear();
			m_vec_NameCall.clear();
			m_vec_NameCallType.clear();
			m_FunctionLink = nullptr;
			m_Class = nullptr;
			m_MxVar = nullptr;
			m_ContractID = -1;
			m_Code = 0;
			}

		void acPrepare_CallNames(void);

		std::shared_ptr<Variable> acCodeCall_Var(int f_Index, int f_MaxIndex, std::shared_ptr<Variable> f_Variable, std::shared_ptr<Contract> f_Contract, int f_FindIndexInt = 0);

		uint m_Code;

		int m_VarType;

		int m_Final_CHK;

		std::string m_MxName;
		std::string m_Cvref_Name;
		std::string m_Cvref_FuncName;

		//main ecoin::Variable
		std::shared_ptr<Variable> m_MxVar;

		//assigned class
		std::shared_ptr<Class> m_Class;

		//native vector
		std::vector<std::string> m_vec_Type;
		std::vector<int> m_vec_VarType;

		uint m_Index;

		int m_ContractID;

		char m_Code_DigitA;
		char m_Code_DigitB;
		char m_Code_DigitC;

		std::vector<std::shared_ptr<Code>> m_Name;
		std::vector<std::shared_ptr<Code>> m_Number;
		std::vector<std::shared_ptr<Code>> m_Type;

		std::vector<std::shared_ptr<Condition>> m_Condition;

		std::shared_ptr<Function> m_FunctionLink;

		std::vector<std::string> m_vec_NameCall;
		std::vector<int> m_vec_NameCallType;
	};

};

#endif