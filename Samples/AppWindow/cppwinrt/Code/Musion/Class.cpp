/*

Class.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Class.h"

using namespace ecoin;

namespace ecoin
{
	void Class::acReset(void)
	    {
		m_vec_Variable.clear();
		m_vec_Function.clear();
		m_MxName.clear();
		m_Owner.clear();
		m_Group.clear();
		}
		
	std::shared_ptr<Function> Class::acFindFunction(std::string f_FunctionName)
		{
		for(int f_Helly = 0; f_Helly < m_vec_Function.size(); f_Helly++)
		    {
			if(f_FunctionName.compare(m_vec_Function[f_Helly]->m_MxName) == 0)
			    {
				return m_vec_Function[f_Helly];
				}
			}

		return nullptr;
		}
		
	std::shared_ptr<Variable> Class::acFindVar(std::string f_VarName)
	    {
		for(int f_Helly = 0; f_Helly < m_vec_Variable.size(); f_Helly++)
		    {
			if(f_VarName.compare(m_vec_Variable[f_Helly]->m_MxName) == 0)
			    {
				return m_vec_Variable[f_Helly];
				}
			}

		return nullptr;
		}

	std::shared_ptr<ClassVar> Class::acFindClassVar(std::string f_VarName)
	    {
		for(int f_Helly = 0; f_Helly < m_vec_ClassVar.size(); f_Helly++)
		    {
			if(f_VarName.compare(m_vec_ClassVar[f_Helly]->m_MxName) == 0)
			    {
				return m_vec_ClassVar[f_Helly];
				}
			}

		return nullptr;
		}
		
	void Class::acSet(std::string f_VarName, std::shared_ptr<Variable> f_Value)
	    {
		std::shared_ptr<Variable> f_Var = acFindVar(f_VarName);
	
		if(f_Var != nullptr)
			{
			*(f_Var) = *(f_Value);
			}
	    }
	
	void Class::acExecFunction(std::string f_FunctionName)
	    {
		std::shared_ptr<Function> f_Function = acFindFunction(f_FunctionName);
		
		if(f_Function != nullptr)
			{
			f_Function->acExecute();
			}
		}
};