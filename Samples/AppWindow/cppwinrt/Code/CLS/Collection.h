/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include <math.h>

#include "Corner.h"
#include "Surface.h"
#include "Leg.h"

using namespace Cube;

namespace ecoin
{

	enum CollectionStyle
	{
		Ground,
		Sky,
		CollectionStyleTotal
	};

	class classCollection : public ecom_base
	{
	public:
		classCollection(std::shared_ptr<Cube::CubeHESH> f_Hesh) : m_Type(Ground), m_Status(ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classCollection::classCollection";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");
			ac_Push(m_idx_vec_Element, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Element");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classCollection::acClear);
#endif
			};
		classCollection(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classCollection::classCollection";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");
			ac_Push(m_idx_vec_Element, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Element");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classCollection::acClear);
#endif
			};
		classCollection() : m_Type(Ground), m_Status(ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classCollection::classCollection";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");
			ac_Push(m_idx_vec_Element, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Element");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classCollection::acClear);
#endif
			};

		~classCollection()
			{
			acClear();
			};

		void acClear(void)
			{
			m_vec_Element.clear();
			m_vec_Surface.clear();
			m_vec_Leg.clear();

			m_idx_vec_Element = 0;
			}

		uint m_Type;
		uint m_Status;

		float m_Scale;

		vector<shared_ptr<classElement>> m_vec_Element;
		vector<shared_ptr<classSurface>> m_vec_Surface;
		vector<shared_ptr<classLeg>> m_vec_Leg;

		int m_idx_vec_Element;
	};

	class classCollectionScript : public ecom_base
	{
	public:
		classCollectionScript(uint f_Type) : m_Type(f_Type), m_Status(ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classCollectionScript::classCollectionScript";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classCollectionScript::acClear);
#endif
			};
		classCollectionScript() : m_Type(Ground), m_Status(ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classCollectionScript::classCollectionScript";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classCollectionScript::acClear);
#endif
			};

		~classCollectionScript() {};

		void acClear(void)
			{
			m_vec_ElementScript.clear();
			}

		classWorth* acStructuredAnalysis(/*target*/);

		uint m_Type;
		uint m_Status;

		float m_Scale;

		vector<shared_ptr<classElementScript>> m_vec_ElementScript;
	};

};

#include "Target.h"

#endif