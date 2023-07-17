/*

Class - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ESLCLASS_H
#define ESLCLASS_H

#include <vector>
#include <math.h>

#include "Code.h"
#include "CodeLine.h"
#include "MuType.h"
#include "Operator.h"
#include "System.h"
#include "Variable.h"
#include "Function.h"
#include "ClassVar.h"

using namespace ecoin;

namespace ecoin
{

	enum MuClassTypes
	{
		MuClass_Default,
		MuClass_Custom,
		MuClass_Custom_Any,
		MuClass_GLOBAL_,
	};

	class Class : public MuType
		{
		public:
			Class() : MuType(MuTYPE_Class) { acClear(); };
			Class(uint f_Class) : MuType(MuTYPE_Class) { acClear(); m_Class = f_Class; };

			void acClear(void)
				{
				m_Class_Declaration = nullptr;

				m_vec_Variable.clear();
				m_vec_Function.clear();
				}

			std::vector<std::shared_ptr<Variable>> m_vec_Variable;
			std::vector<std::shared_ptr<ClassVar>> m_vec_ClassVar;
			std::vector<std::shared_ptr<Function>> m_vec_Function;

			std::shared_ptr<Function> m_Constructor_Function;

			std::vector<std::shared_ptr<CodeLine>> m_vec_CodeLine;

			uint m_Class;

			std::string m_MxName;
			std::string m_Namespace;
			std::string m_Owner;
			std::string m_Group;
			
			void acReset(void);
			void acSet(std::string f_VarName, std::shared_ptr<Variable> f_Value);
			void acExecFunction(std::string f_FunctionName);
			
			std::shared_ptr<Variable> acFindVar(std::string f_Name);
			std::shared_ptr<ClassVar> acFindClassVar(std::string f_Name);
			std::shared_ptr<Function> acFindFunction(std::string f_FunctionName);

			std::shared_ptr<Class> m_Class_Declaration;
		};

	//extern int agFind_FunctionType(std::string f_String);

};


#endif