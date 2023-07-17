/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAM_VARIABLE_H
#define QAM_VARIABLE_H

#include <vector>
#include <math.h>

#include "Code/Musion/MuType.h"
#include "Code/Musion/Variable.h"

#include "qamType.h"

namespace ecoin
{

	class qamVariable : public qamType
		{
		public:
			qamVariable()
				{
				m_Action = MuAct_Start;
				m_Updated = false;
				};

			qamVariable(std::string f_Stg, uint f_CodeType, uint f_PrecType);
			~qamVariable() {};

			uint get_Value(void);

			qamVariable(uint f_PrecType);

			qamVariable(uint f_CodeType, uint f_PrecType) : qamType(qamTYPE_Variable), m_CodeType(f_CodeType), m_PrecType(f_PrecType)
				{
				m_Var = 0;
				m_Updated = false;
				};

            void operator=(const qamVariable &v)
				{
				m_Var = v.m_Var;
				}

			void operator+=(qamVariable &v)
				{
                if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) + boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) + boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) + boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(std::string))
                    {
                    m_Var = boost::any_cast<std::string>(m_Var) + boost::any_cast<std::string>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X += f_AddtoVar.m_X;
                    f_Var.m_X += f_AddtoVar.m_Y;
                    f_Var.m_X += f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

			void operator-=(qamVariable &v)
				{
				if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) - boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) - boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) - boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X -= f_AddtoVar.m_X;
                    f_Var.m_X -= f_AddtoVar.m_Y;
                    f_Var.m_X -= f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

            void operator*=(qamVariable &v)
				{
                if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) * boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) * boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) * boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X *= f_AddtoVar.m_X;
                    f_Var.m_X *= f_AddtoVar.m_Y;
                    f_Var.m_X *= f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

			void operator/=(qamVariable &v)
				{
				if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) / boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) / boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) / boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X /= f_AddtoVar.m_X;
                    f_Var.m_X /= f_AddtoVar.m_Y;
                    f_Var.m_X /= f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

            void operator+(qamVariable &v)
				{
                if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) + boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) + boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) + boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(std::string))
                    {
                    m_Var = boost::any_cast<std::string>(m_Var) + boost::any_cast<std::string>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X += f_AddtoVar.m_X;
                    f_Var.m_X += f_AddtoVar.m_Y;
                    f_Var.m_X += f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

			void operator-(qamVariable &v)
				{
				if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) - boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) - boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) - boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X -= f_AddtoVar.m_X;
                    f_Var.m_X -= f_AddtoVar.m_Y;
                    f_Var.m_X -= f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

            void operator*(qamVariable &v)
				{
                if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) * boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) * boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) * boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X *= f_AddtoVar.m_X;
                    f_Var.m_X *= f_AddtoVar.m_Y;
                    f_Var.m_X *= f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

			void operator/(qamVariable &v)
				{
				if(m_Var.type() == typeid(int))
                    {
                    m_Var = boost::any_cast<int>(m_Var) / boost::any_cast<int>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float))
                    {
                    m_Var = boost::any_cast<float>(m_Var) / boost::any_cast<float>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(char))
                    {
                    m_Var = boost::any_cast<char>(m_Var) / boost::any_cast<char>(v.m_Var);
                    }
                else if(m_Var.type() == typeid(float3))
                    {
                    float3 f_Var = boost::any_cast<float3>(m_Var);
                    float3 f_AddtoVar = boost::any_cast<float3>(v.m_Var);

                    f_Var.m_X /= f_AddtoVar.m_X;
                    f_Var.m_X /= f_AddtoVar.m_Y;
                    f_Var.m_X /= f_AddtoVar.m_Z;

                    m_Var = f_Var;
                    }
				}

			uint m_PrecType;
			uint m_CodeType;

			std::string m_MxName;

			int m_TriggerID;

			unsigned char m_Action;

			bool m_Updated;

			boost::any m_Var;

			float m_X;
			float m_Y;
			float m_Z;

			float m_Xrot;
			float m_Yrot;
			float m_Zrot;
		};

};

#endif