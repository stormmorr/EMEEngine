/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ICS_SURFACE_H
#define ICS_SURFACE_H

#include <vector>
#include <math.h>

#include "ICS_Corner.h"

namespace ecoin
{

	enum ICS_SurfaceType
	{
		ICS_Surface
	};

	class ICS_classSurface : public ecom_base
	{
	public:
		ICS_classSurface()
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "ICS_classSurface::ICS_classSurface";

			ag_StatusLive(f_ref_CurrentPath, "m_Position");
			m_Position = std::make_shared<Cube::BiVector>(0.0f);

			m_FULLON = false;

#ifndef OSI_MEM_APP
			ac_Push(m_FULLON, f_ref_CurrentPath + g_ref_Div + "m_FULLON");
#endif
			};

		ICS_classSurface(shared_ptr<ICS_classElement> f_Element)
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "ICS_classSurface::ICS_classSurface";

			ag_StatusLive(f_ref_CurrentPath, "m_Position");
			m_Position = std::make_shared<Cube::BiVector>(0.0f);

			m_FULLON = true;

#ifndef OSI_MEM_APP
			ac_Push(m_FULLON, f_ref_CurrentPath + g_ref_Div + "m_FULLON");
#endif
			};

		~ICS_classSurface()
			{
			m_Position = nullptr;
			};

		BiPlane m_PropPlane;
		matrix m_Orientation;
		std::shared_ptr<BiVector> m_Position;

		bool m_FULLON;
	};

};

#endif