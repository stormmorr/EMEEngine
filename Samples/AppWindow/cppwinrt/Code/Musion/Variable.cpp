/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Variable.h"
#include "Code.h"
#include "CodeLine.h"

using namespace ecoin;

namespace ecoin
{

#ifdef SEPER_ANY_CAST
#ifndef HAS_BOOST_ANY_CAST
template<class T>
T ag_any_cast(boost::any f_Any)
{
	try
		{
		return boost::any_cast<T>(f_Any);
		}

	catch (boost::bad_any_cast &e)
		{

#if 0
		std::cerr << e.what() << '\n';
#endif

#if 1
		__debugbreak();
#endif

		return T(0);
		}
}
#else
#define ag_any_cast boost::any_cast
#endif
#endif

Variable::Variable() : MuType(MuTYPE_Variable), m_MxName("EmptyName"), m_CodeType(MuCode_Var), m_PrecType(MuVar_Full), m_Variable(ECN_VAR_DEFAULT)
{
	acClear();
};

Variable::Variable(std::string f_Stg, uint f_CodeType) : MuType(MuTYPE_Variable), m_MxName(f_Stg), m_CodeType(f_CodeType), m_PrecType(MuVar_Full), m_Variable(ECN_VAR_DEFAULT)
{
	acClear();

	m_Action = MuAct_Start;
}

Variable::Variable(uint f_PrecType) : MuType(MuTYPE_Variable), m_MxName("IdentVar"), m_CodeType(0), m_PrecType(f_PrecType), m_Variable(agFind_VarType_from_Precision(f_PrecType))
{
	acClear();

	m_Action = MuAct_Start;
}

Variable::Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType) : MuType(MuTYPE_Variable), m_MxName(f_Stg), m_CodeType(f_CodeType), m_PrecType(f_PrecType), m_Variable(agFind_VarType_from_Precision(f_PrecType))
{
	acClear();

	m_Action = MuAct_Start;
}

Variable::Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType, uint f_Variable) : MuType(MuTYPE_Variable), m_MxName(f_Stg), m_CodeType(f_CodeType), m_PrecType(f_PrecType), m_Variable(f_Variable)
{
	acClear();

	m_Action = MuAct_Start;
}

Variable::Variable(std::string f_Stg, uint f_CodeType, boost::any f_a) : MuType(MuTYPE_Variable), m_MxName(f_Stg), m_CodeType(f_CodeType), m_PrecType(MuVar_Full), m_Variable(ECN_VAR_DEFAULT), m_Var(f_a)
{
	acClear();

	m_Action = MuAct_Start;
}

#if 0
Variable& Variable::operator=(boost::any rhs)
{
	Variable* f_Variable = this;
	f_Variable->m_Var = rhs;
	return *this;
}
#endif

Variable::~Variable()
{
	acClear();

	m_Action = MuAct_Finish;
}

std::shared_ptr<Variable> operator+ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(v1->m_RefVar == true)
			{
			if(v2->m_RefVar == true)
				{
				*(ag_any_cast<int*>(v1->m_Var)) = *(ag_any_cast<int*>(v1->m_Var)) + *(ag_any_cast<int*>(v2->m_Var));
				}
			else
				{
				*(ag_any_cast<int*>(v1->m_Var)) = *(ag_any_cast<int*>(v1->m_Var)) + ag_any_cast<int>(v2->m_Var);
				}
			}
		else
			{
			if(v2->m_RefVar == true)
				{
				v1->m_Var = ag_any_cast<int>(v1->m_Var) + *(ag_any_cast<int*>(v2->m_Var));
				}
			else
				{
				v1->m_Var = ag_any_cast<int>(v1->m_Var) + ag_any_cast<int>(v2->m_Var);
				}
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(v1->m_RefVar == true)
			{
			if(v2->m_RefVar == true)
				{
				*(ag_any_cast<unsigned int*>(v1->m_Var)) = *(ag_any_cast<unsigned int*>(v1->m_Var)) + *(ag_any_cast<unsigned int*>(v2->m_Var));
				}
			else
				{
				*(ag_any_cast<unsigned int*>(v1->m_Var)) = *(ag_any_cast<unsigned int*>(v1->m_Var)) + ag_any_cast<unsigned int>(v2->m_Var);
				}
			}
		else
			{
			if(v2->m_RefVar == true)
				{
				v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) + *(ag_any_cast<unsigned int*>(v2->m_Var));
				}
			else
				{
				v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) + ag_any_cast<unsigned int>(v2->m_Var);
				}
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(v1->m_RefVar == true)
			{
			if(v2->m_RefVar == true)
				{
				*(ag_any_cast<float*>(v1->m_Var)) = *(ag_any_cast<float*>(v1->m_Var)) + *(ag_any_cast<float*>(v2->m_Var));
				}
			else
				{
				*(ag_any_cast<float*>(v1->m_Var)) = *(ag_any_cast<float*>(v1->m_Var)) + ag_any_cast<float>(v2->m_Var);
				}
			}
		else
			{
			if(v2->m_RefVar == true)
				{
				v1->m_Var = ag_any_cast<float>(v1->m_Var) + *(ag_any_cast<float*>(v2->m_Var));
				}
			else
				{
				v1->m_Var = ag_any_cast<float>(v1->m_Var) + ag_any_cast<float>(v2->m_Var);
				}
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(v1->m_RefVar == true)
			{
			if(v2->m_RefVar == true)
				{
				*(ag_any_cast<float*>(v1->m_Var)) = *(ag_any_cast<float*>(v1->m_Var)) + *(ag_any_cast<float*>(v2->m_Var));
				}
			else
				{
				*(ag_any_cast<float*>(v1->m_Var)) = *(ag_any_cast<float*>(v1->m_Var)) + ag_any_cast<float>(v2->m_Var);
				}
			}
		else
			{
			if(v2->m_RefVar == true)
				{
				v1->m_Var = ag_any_cast<float>(v1->m_Var) + *(ag_any_cast<float*>(v2->m_Var));
				}
			else
				{
				v1->m_Var = ag_any_cast<float>(v1->m_Var) + ag_any_cast<float>(v2->m_Var);
				}
			}
		v1->m_Var = ag_any_cast<char>(v1->m_Var) + ag_any_cast<char>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(std::string))
        {
		v1->m_Var = ag_any_cast<std::string>(v1->m_Var) + ag_any_cast<std::string>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		v1->m_Var = ag_any_cast<double>(v1->m_Var) + ag_any_cast<double>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) + ag_any_cast<unsigned char>(v2->m_Var);
        }
	else if (v1->m_Var.type() == typeid(bool))
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X += f_AddtoVar.m_X;
        f_Var.m_Y += f_AddtoVar.m_Y;
        f_Var.m_Z += f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }
	else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X += f_AddtoVar.m_X;
        f_Var.m_Y += f_AddtoVar.m_Y;
        f_Var.m_Z += f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

std::shared_ptr<Variable> operator- (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) - ag_any_cast<int>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) - ag_any_cast<unsigned int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) - ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) - ag_any_cast<char>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		v1->m_Var = ag_any_cast<double>(v1->m_Var) - ag_any_cast<double>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) + ag_any_cast<unsigned char>(v2->m_Var);
        }
	else if (v1->m_Var.type() == typeid(bool))
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X -= f_AddtoVar.m_X;
        f_Var.m_Y -= f_AddtoVar.m_Y;
        f_Var.m_Z -= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

std::shared_ptr<Variable> operator* (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) * ag_any_cast<int>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) * ag_any_cast<unsigned int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) * ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) * ag_any_cast<char>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		v1->m_Var = ag_any_cast<double>(v1->m_Var) * ag_any_cast<double>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) + ag_any_cast<unsigned char>(v2->m_Var);
        }
	else if (v1->m_Var.type() == typeid(bool))
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X *= f_AddtoVar.m_X;
        f_Var.m_Y *= f_AddtoVar.m_Y;
        f_Var.m_Z *= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

std::shared_ptr<Variable> operator/ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) / ag_any_cast<int>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) / ag_any_cast<unsigned int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		v1->m_Var = ag_any_cast<float>(v1->m_Var) / ag_any_cast<float>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) / ag_any_cast<char>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		v1->m_Var = ag_any_cast<double>(v1->m_Var) / ag_any_cast<double>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) / ag_any_cast<unsigned char>(v2->m_Var);
        }
	else if (v1->m_Var.type() == typeid(bool))
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v2->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

        f_Var.m_X /= f_AddtoVar.m_X;
        f_Var.m_Y /= f_AddtoVar.m_Y;
        f_Var.m_Z /= f_AddtoVar.m_Z;

		v1->m_Var = f_Var;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

bool operator== (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(ag_any_cast<int>(v1->m_Var) == ag_any_cast<int>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(ag_any_cast<unsigned int>(v1->m_Var) == ag_any_cast<unsigned int>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(ag_any_cast<float>(v1->m_Var) == ag_any_cast<float>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(ag_any_cast<char>(v1->m_Var) == ag_any_cast<char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		if(ag_any_cast<unsigned char>(v1->m_Var) == ag_any_cast<unsigned char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(std::string))
        {
		if(ag_any_cast<std::string>(v1->m_Var).compare(ag_any_cast<std::string>(v2->m_Var)) == 0)
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(bool))
		{
		if(ag_any_cast<bool>(v1->m_Var) == ag_any_cast<bool>(v2->m_Var))
			{
			return true;
			}
		}
	else if(v1->m_Var.type() == typeid(double))
        {
		if(ag_any_cast<double>(v1->m_Var) == ag_any_cast<double>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v1->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

		if(f_Var.m_X != f_AddtoVar.m_X)
			{
			return false;
			}
		if(f_Var.m_Y != f_AddtoVar.m_Y)
			{
			return false;
			}
		if(f_Var.m_Z != f_AddtoVar.m_Z)
			{
			return false;
			}

		return true;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return false;
}

bool operator< (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(ag_any_cast<int>(v1->m_Var) < ag_any_cast<int>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(ag_any_cast<unsigned int>(v1->m_Var) < ag_any_cast<unsigned int>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(ag_any_cast<float>(v1->m_Var) < ag_any_cast<float>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(ag_any_cast<char>(v1->m_Var) < ag_any_cast<char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		if(ag_any_cast<unsigned char>(v1->m_Var) < ag_any_cast<unsigned char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(bool))
        {
		if(ag_any_cast<bool>(v1->m_Var) < ag_any_cast<bool>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		if(ag_any_cast<double>(v1->m_Var) < ag_any_cast<double>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v1->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

		if(f_Var.m_X >= f_AddtoVar.m_X)
			{
			return false;
			}
		if(f_Var.m_Y >= f_AddtoVar.m_Y)
			{
			return false;
			}
		if(f_Var.m_Z >= f_AddtoVar.m_Z)
			{
			return false;
			}

		return true;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return false;
}

bool operator> (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(ag_any_cast<int>(v1->m_Var) > ag_any_cast<int>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(ag_any_cast<unsigned int>(v1->m_Var) > ag_any_cast<unsigned int>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(ag_any_cast<float>(v1->m_Var) > ag_any_cast<float>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(ag_any_cast<char>(v1->m_Var) > ag_any_cast<char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		if(ag_any_cast<unsigned char>(v1->m_Var) > ag_any_cast<unsigned char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		if(ag_any_cast<double>(v1->m_Var) > ag_any_cast<double>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(bool))
        {
		if(ag_any_cast<bool>(v1->m_Var) > ag_any_cast<bool>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v1->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

		if(f_Var.m_X <= f_AddtoVar.m_X)
			{
			return false;
			}
		if(f_Var.m_Y <= f_AddtoVar.m_Y)
			{
			return false;
			}
		if(f_Var.m_Z <= f_AddtoVar.m_Z)
			{
			return false;
			}

		return true;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return false;
}

bool operator<= (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(ag_any_cast<int>(v1->m_Var) <= ag_any_cast<int>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(ag_any_cast<unsigned int>(v1->m_Var) <= ag_any_cast<unsigned int>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(ag_any_cast<float>(v1->m_Var) <= ag_any_cast<float>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(ag_any_cast<char>(v1->m_Var) <= ag_any_cast<char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		if(ag_any_cast<unsigned char>(v1->m_Var) <= ag_any_cast<unsigned char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		if(ag_any_cast<double>(v1->m_Var) <= ag_any_cast<double>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(bool))
        {
		if(ag_any_cast<bool>(v1->m_Var) <= ag_any_cast<bool>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v1->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

		if(f_Var.m_X > f_AddtoVar.m_X)
			{
			return false;
			}
		if(f_Var.m_Y > f_AddtoVar.m_Y)
			{
			return false;
			}
		if(f_Var.m_Z > f_AddtoVar.m_Z)
			{
			return false;
			}

		return true;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return false;
}

bool operator>= (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(ag_any_cast<int>(v1->m_Var) >= ag_any_cast<int>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(ag_any_cast<unsigned int>(v1->m_Var) >= ag_any_cast<unsigned int>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(ag_any_cast<float>(v1->m_Var) >= ag_any_cast<float>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(ag_any_cast<char>(v1->m_Var) >= ag_any_cast<char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		if(ag_any_cast<unsigned char>(v1->m_Var) >= ag_any_cast<unsigned char>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		if(ag_any_cast<double>(v1->m_Var) >= ag_any_cast<double>(v2->m_Var))
			{
			return true;
			}
        }
	else if(v1->m_Var.type() == typeid(bool))
        {
		if(ag_any_cast<bool>(v1->m_Var) >= ag_any_cast<bool>(v2->m_Var))
			{
			return true;
			}
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v1->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

		if(f_Var.m_X < f_AddtoVar.m_X)
			{
			return false;
			}
		if(f_Var.m_Y < f_AddtoVar.m_Y)
			{
			return false;
			}
		if(f_Var.m_Z < f_AddtoVar.m_Z)
			{
			return false;
			}

		return true;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return false;
}

bool operator!= (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(v1->m_lnk_ClassVar)
		{
		__debugbreak(); //add debug message
		}
#endif

	if(v1->m_Var.type() == typeid(int))
        {
		if(ag_any_cast<int>(v1->m_Var) == ag_any_cast<int>(v2->m_Var))
			{
			return false;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		if(ag_any_cast<unsigned int>(v1->m_Var) == ag_any_cast<unsigned int>(v2->m_Var))
			{
			return false;
			}
        }
    else if(v1->m_Var.type() == typeid(float))
        {
		if(ag_any_cast<float>(v1->m_Var) == ag_any_cast<float>(v2->m_Var))
			{
			return false;
			}
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		if(ag_any_cast<char>(v1->m_Var) == ag_any_cast<char>(v2->m_Var))
			{
			return false;
			}
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		if(ag_any_cast<unsigned char>(v1->m_Var) == ag_any_cast<unsigned char>(v2->m_Var))
			{
			return false;
			}
        }
	else if(v1->m_Var.type() == typeid(std::string))
        {
		if(ag_any_cast<std::string>(v1->m_Var).compare(ag_any_cast<std::string>(v2->m_Var)) == 0)
			{
			return false;
			}
        }
	else if(v1->m_Var.type() == typeid(double))
        {
		if(ag_any_cast<double>(v1->m_Var) == ag_any_cast<double>(v2->m_Var))
			{
			return false;
			}
        }
	else if(v1->m_Var.type() == typeid(bool))
        {
		if(ag_any_cast<bool>(v1->m_Var) == ag_any_cast<bool>(v2->m_Var))
			{
			return false;
			}
        }
    else if(v1->m_Var.type() == typeid(float3))
        {
        float3 f_Var = ag_any_cast<float3>(v1->m_Var);
        float3 f_AddtoVar = ag_any_cast<float3>(v2->m_Var);

		if(f_Var.m_X != f_AddtoVar.m_X)
			{
			return false;
			}
		if(f_Var.m_Y != f_AddtoVar.m_Y)
			{
			return false;
			}
		if(f_Var.m_Z != f_AddtoVar.m_Z)
			{
			return false;
			}

		return true;
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return true;
}

std::shared_ptr<Variable> Variable::CloneVar(std::shared_ptr<Variable> v1)
{
	if(v1->m_lnk_ClassVar)
		{
		m_lnk_ClassVar = v1->m_lnk_ClassVar;
		}
	else
		{
		if(m_Var.type() == typeid(int))
			{
			m_Var = ag_any_cast<int>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(float))
			{
			m_Var = ag_any_cast<float>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(unsigned int))
			{
			m_Var = ag_any_cast<unsigned int>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(char))
			{
			m_Var = ag_any_cast<char>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(unsigned char))
			{
			m_Var = ag_any_cast<unsigned char>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(double))
			{
			m_Var = ag_any_cast<int>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(bool))
			{
			m_Var = ag_any_cast<bool>(v1->m_Var);
			}
		else if(v1->m_Var.type() == typeid(float3))
			{
			float3 f_Var = ag_any_cast<float3>(v1->m_Var);
			float3 f_AddtoVar = ag_any_cast<float3>(m_Var);

			f_AddtoVar.m_X /= f_Var.m_X;
			f_AddtoVar.m_Y /= f_Var.m_Y;
			f_AddtoVar.m_Z /= f_Var.m_Z;

			m_Var = f_AddtoVar;
			}
#ifdef ECOIN_DEBUG_BREAKS
		else
			{
			__debugbreak();
			}
#endif
		}

    return v1;
}

std::shared_ptr<Variable> operator<< (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) << ag_any_cast<int>(v2->m_Var);
        }
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) << ag_any_cast<unsigned int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) << ag_any_cast<char>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) << ag_any_cast<unsigned char>(v2->m_Var);
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

std::shared_ptr<Variable> operator>> (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) >> ag_any_cast<int>(v2->m_Var);
        }
	if(v1->m_Var.type() == typeid(unsigned int))
        {
		v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) >> ag_any_cast<unsigned int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) >> ag_any_cast<char>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) >> ag_any_cast<unsigned char>(v2->m_Var);
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

std::shared_ptr<Variable> operator% (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2)
{
	if(v1->m_Var.type() == typeid(int))
        {
		v1->m_Var = ag_any_cast<int>(v1->m_Var) % ag_any_cast<int>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned int))
        {
		v1->m_Var = ag_any_cast<unsigned int>(v1->m_Var) % ag_any_cast<unsigned int>(v2->m_Var);
        }
    else if(v1->m_Var.type() == typeid(char))
        {
		v1->m_Var = ag_any_cast<char>(v1->m_Var) % ag_any_cast<char>(v2->m_Var);
        }
	else if(v1->m_Var.type() == typeid(unsigned char))
        {
		v1->m_Var = ag_any_cast<unsigned char>(v1->m_Var) % ag_any_cast<unsigned char>(v2->m_Var);
        }
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

    return v1;
}

int agFind_Precision(std::string f_String)
	{
	if(f_String.compare("float") == 0 ||
	   f_String.compare("Float") == 0)
		{
		return MuVar_Float;
		}
	else if(f_String.compare("int") == 0 ||
			f_String.compare("Int") == 0)
		{
		return MuVar_Int;
		}
	else if(f_String.compare("string") == 0 ||
			f_String.compare("String") == 0)
		{
		return MuVar_String;
		}
	else if(f_String.compare("uint") == 0 ||
			f_String.compare("UInt") == 0)
		{
		return MuVar_Int;
		}
	else if(f_String.compare("bool") == 0 ||
			f_String.compare("Bool") == 0)
		{
		return MuVar_Bool;
		}
	else if(f_String.compare("char") == 0 ||
			f_String.compare("Char") == 0)
		{
		return MuVar_Char;
		}
	else if(f_String.compare("uchar") == 0 ||
			f_String.compare("UChar") == 0)
		{
		return MuVar_Char;
		}
	else if(f_String.compare("double") == 0 ||
			f_String.compare("Double") == 0)
		{
		return MuVar_Double;
		}
	else if(f_String.compare("float2") == 0 ||
			f_String.compare("Float2") == 0)
		{
		return MuVar_Float2;
		}
	else if(f_String.compare("float3") == 0 ||
			f_String.compare("Float3") == 0)
		{
		return MuVar_Float3;
		}
	else if(f_String.compare("float4") == 0 ||
			f_String.compare("Float4") == 0)
		{
		return MuVar_Float4;
		}
	else if(f_String.compare("int2") == 0 ||
			f_String.compare("Int2") == 0)
		{
		return MuVar_Int2;
		}
	else if(f_String.compare("int3") == 0 ||
			f_String.compare("Int3") == 0)
		{
		return MuVar_Int3;
		}
	else if(f_String.compare("int4") == 0 ||
			f_String.compare("Int4") == 0)
		{
		return MuVar_Int4;
		}
	//Transient Types
	else if(f_String.compare("eslbase") == 0)
		{
		return MuVar_ClassVar_Reflect;
		}
	else
		{
		return MuVar_ClassVar_Class;
		}

	return MuVar_Custom;
	}

int agFind_VarType_from_Precision(int f_CurrentSpec)
	{
	if(f_CurrentSpec <= MuVar_Double)
		{
		switch(f_CurrentSpec)
			{
			case MuVar_Float:
				{
				return ECN_VAR_FLOAT;
				}break;

			case MuVar_Float2:
				{
				return ECN_VAR_FLOAT;
				}break;

			case MuVar_Float3:
				{
				return ECN_VAR_FLOAT;
				}break;

			case MuVar_Float4:
				{
				return ECN_VAR_FLOAT;
				}break;

			case MuVar_UInt:
				{
				return ECN_VAR_UINT;
				}break;

			case MuVar_Int:
				{
				return ECN_VAR_INT;
				}break;

			case MuVar_Int2:
				{
				return ECN_VAR_INT;
				}break;

			case MuVar_Int3:
				{
				return ECN_VAR_INT;
				}break;

			case MuVar_Int4:
				{
				return ECN_VAR_INT;
				}break;

			case MuVar_Bool:
				{
				return ECN_VAR_BOOL;
				}break;

			case MuVar_Char:
				{
				return ECN_VAR_CHAR;
				}break;

			case MuVar_UChar:
				{
				return ECN_VAR_UCHAR;
				}break;

			case MuVar_String:
				{
				return ECN_VAR_STRING;
				}break;

			case MuVar_Double:
				{
				return ECN_VAR_STRING;
				}break;
			}
		}
	else
		{
		switch(f_CurrentSpec)
			{
			case MuVar_Float_Reflect:
				{
				return ECN_VAR_FLOAT;
				}break;

			case MuVar_Int_Reflect:
				{
				return ECN_VAR_INT;
				}break;

			case MuVar_Bool_Reflect:
				{
				return ECN_VAR_BOOL;
				}break;

			case MuVar_UInt_Reflect:
				{
				return ECN_VAR_UINT;
				}break;

			case MuVar_Char_Reflect:
				{
				return ECN_VAR_CHAR;
				}break;

			case MuVar_String_Reflect:
				{
				return ECN_VAR_STRING;
				}break;

			case MuVar_Double_Reflect:
				{
				return ECN_VAR_DOUBLE;
				}break;

				//[WIP]//
			case MuVar_ClassVar_Class:
				{
				return ECN_VAR_DEFAULT;
				}break;

				//[WIP]//
			case MuVar_ClassVar_Reflect:
				{
				return ECN_VAR_DEFAULT;
				}break;

				//[WIP]//
			case MuVar_Custom:
				{
				return ECN_VAR_DEFAULT;
				}break;
			}
		}

#ifdef ECOIN_DEBUG_BREAKS
	__debugbreak(); //add debug message
#endif

	return ECN_VAR_INT; //default int
	}

boost::any Variable::get_Value(void)
	{
	return m_Var;
	}

void Variable::set_Value(boost::any f_Value)
	{
	m_Var = f_Value;
	}

std::shared_ptr<Variable> av_Identity(uint f_PrecType)
	{
	return std::make_shared<Variable>(f_PrecType);
	}

std::shared_ptr<ecom_base> ag_SharpenBase(std::string f_ClassPath, std::string f_ClassName, int f_instanceCount)
	{
	char* f_Char = ag_ClearChar(64);

	sprintf(f_Char, "%i", f_instanceCount);

	std::string f_TypeString = "class " + f_ClassName + g_ref_Div + std::string(f_Char) + g_ref_Div;

	return ag_Produce_base(f_ClassPath + f_TypeString);
	}

std::shared_ptr<Variable> ag_ReturnAnyVar(std::string f_StringName, int f_PrecType, std::string f_MainClassStringPath, std::string f_MainClassStringType, std::string f_MemberVarStringName, int f_instanceCount)
	{
	std::shared_ptr<ecom_base> f_MainClassBase = ag_SharpenBase(f_MainClassStringPath, f_MainClassStringType, f_instanceCount);

	std::shared_ptr<Variable> f_NewVar = std::make_shared<Variable>(f_StringName, MuCode_Var, MuVar_Full);

	if(f_PrecType >= 0)
		{
		f_NewVar->m_Variable = agFind_VarType_from_Precision(f_PrecType);

		switch(f_PrecType)
			{
			case MuVar_Float_Reflect:
				{
				if(f_MainClassBase->m_Map_Float.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Float.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_Float[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_UInt_Reflect:
				{
				if(f_MainClassBase->m_Map_UInt.find(f_MemberVarStringName) != f_MainClassBase->m_Map_UInt.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_UInt[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_Int_Reflect:
				{
				if(f_MainClassBase->m_Map_Int.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Int.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_Int[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_Bool_Reflect:
				{
				if(f_MainClassBase->m_Map_Bool.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Bool.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_Bool[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_Char_Reflect:
				{
				if(f_MainClassBase->m_Map_Char.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Char.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_Char[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_UChar_Reflect:
				{
				if(f_MainClassBase->m_Map_Char.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Char.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_Char[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_String_Reflect:
				{
				if(f_MainClassBase->m_Map_String.find(f_MemberVarStringName) != f_MainClassBase->m_Map_String.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_String[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;

			case MuVar_Double_Reflect:
				{
				if(f_MainClassBase->m_Map_Double.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Double.end())
					{
					f_NewVar->m_Var = f_MainClassBase->m_Map_Double[f_MemberVarStringName];

					return f_NewVar;
					}
				}break;
			}
		}
	else
		{
		if(f_MainClassBase->m_Map_Float.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Float.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_Float[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_Float_Reflect);

			return f_NewVar;
			}

		if(f_MainClassBase->m_Map_UInt.find(f_MemberVarStringName) != f_MainClassBase->m_Map_UInt.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_UInt[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_UInt_Reflect);

			return f_NewVar;
			}

		if(f_MainClassBase->m_Map_Int.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Int.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_Int[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_Int_Reflect);

			return f_NewVar;
			}
				
		if(f_MainClassBase->m_Map_Bool.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Bool.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_Bool[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_Bool_Reflect);

			return f_NewVar;
			}
				
		if(f_MainClassBase->m_Map_Char.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Char.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_Char[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_Char_Reflect);

			return f_NewVar;
			}
				
		if(f_MainClassBase->m_Map_String.find(f_MemberVarStringName) != f_MainClassBase->m_Map_String.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_String[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_String_Reflect);

			return f_NewVar;
			}
				
		if(f_MainClassBase->m_Map_Double.find(f_MemberVarStringName) != f_MainClassBase->m_Map_Double.end())
			{
			f_NewVar->m_Var = f_MainClassBase->m_Map_Double[f_MemberVarStringName];

			f_NewVar->m_Variable = agFind_VarType_from_Precision(MuVar_Double_Reflect);

			return f_NewVar;
			}
		}

#ifdef ECOIN_DEBUG_BREAKS
	__debugbreak(); // add debug msg
#endif

	f_NewVar->m_MxName = "Var socket in member variable not found";

	return f_NewVar;
	}

bool ag_Value_Check(std::string f_Input)
	{
	if(f_Input.at(0) != '&')
		{
		return false;
		}

	if(f_Input.at(1) != '%')
		{
		return false;
		}

	return true;
	}

bool ag_CVar_Check(std::string f_Input)
	{
	if(f_Input.at(0) != '%')
		{
		return false;
		}

	if(f_Input.at(1) != '%')
		{
		return false;
		}

	return true;
	}

};