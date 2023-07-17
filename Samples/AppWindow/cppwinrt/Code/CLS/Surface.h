/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SURFACE_H
#define SURFACE_H

#include <vector>
#include <math.h>

#include "Corner.h"

namespace ecoin
{

	enum CLS_SurfaceType
	{
		CLS_Surface
	};

	class classSurface : public ecom_base
	{
	public:
		classSurface()
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "classSurface::classSurface";

			ag_StatusLive(f_ref_CurrentPath, "m_Position");
			m_Position = std::make_shared<Cube::BiVector>(0.0f);

			m_FULLON = false;

#ifndef OSI_MEM_APP
			ac_Push(m_FULLON, f_ref_CurrentPath + g_ref_Div + "m_FULLON");
#endif
			};

		classSurface(shared_ptr<classElement> f_Element)
			{
			std::string f_ref_CurrentPath = g_ref_global_start + "classSurface::classSurface";

			ag_StatusLive(f_ref_CurrentPath, "m_Position");
			m_Position = std::make_shared<Cube::BiVector>(0.0f);

			m_FULLON = true;

#ifndef OSI_MEM_APP
			ac_Push(m_FULLON, f_ref_CurrentPath + g_ref_Div + "m_FULLON");
#endif
			};

		~classSurface()
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