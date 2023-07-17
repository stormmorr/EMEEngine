/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ICS_LEG_H
#define ICS_LEG_H

#include <vector>
#include <math.h>

#include "ICS_Corner.h"

namespace ecoin
{

	enum ICS_LegType
	{
		ICS_CLS_Leg
	};

	class ICS_classLeg : public ecom_base
	{
	public:
		ICS_classLeg()
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "ICS_classLeg::ICS_classLeg";

			ag_StatusLive(f_ref_CurrentPath, "m_Position");
			m_Position = std::make_shared<Cube::BiVector>(0.0f);

			m_FULLON = false;

#ifndef OSI_MEM_APP
			ac_Push(m_Width, f_ref_CurrentPath + g_ref_Div + "m_Width");
			ac_Push(m_Height, f_ref_CurrentPath + g_ref_Div + "m_Height");
			ac_Push(m_Length, f_ref_CurrentPath + g_ref_Div + "m_Length");
			ac_Push(m_FULLON, f_ref_CurrentPath + g_ref_Div + "m_FULLON");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&DecisionCom::acClear);
#endif
			};

		ICS_classLeg(shared_ptr<ICS_classElement> f_Element)
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "ICS_classLeg::ICS_classLeg";

			ag_StatusLive(f_ref_CurrentPath, "m_Position");
			m_Position = std::make_shared<Cube::BiVector>(0.0f);

			m_FULLON = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Width, f_ref_CurrentPath + g_ref_Div + "m_Width");
			ac_Push(m_Height, f_ref_CurrentPath + g_ref_Div + "m_Height");
			ac_Push(m_Length, f_ref_CurrentPath + g_ref_Div + "m_Length");
			ac_Push(m_FULLON, f_ref_CurrentPath + g_ref_Div + "m_FULLON");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&DecisionCom::acClear);
#endif
			};

		~ICS_classLeg()
			{
			acClear();

			m_Position = nullptr;
			};

		void acClear(void)
			{
			m_Width = 0.0f;
			m_Height = 0.0f;
			m_Length = 0.0f;
			}

		float m_Width;
		float m_Height;
		float m_Length;

		std::shared_ptr<BiVector> m_Position;
		matrix m_Orientation;

		bool m_FULLON;
	};

};

#endif