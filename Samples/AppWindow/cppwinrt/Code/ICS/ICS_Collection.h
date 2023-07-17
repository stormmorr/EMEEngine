/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ICS_COLLECTION_H
#define ICS_COLLECTION_H

#include <vector>
#include <math.h>

#include "ICS_Corner.h"
#include "ICS_Surface.h"
#include "ICS_Leg.h"

using namespace Cube;

namespace ecoin
{

	enum ICS_CollectionStyle
	{
		ICS_Ground,
		ICS_Sky,
		ICS_CollectionStyleTotal
	};

	class ICS_classCollection : public ecom_base
	{
	public:
		ICS_classCollection(std::shared_ptr<Cube::CubeHESH> f_Hesh) : m_Type(ICS_Ground), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "ICS_classCollection::ICS_classCollection";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");
			ac_Push(m_idx_vec_Element, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Element");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&ICS_classCollection::acClear);
#endif
			};

		ICS_classCollection(uint f_Type) : m_Type(f_Type), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "ICS_classCollection::ICS_classCollection";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");
			ac_Push(m_idx_vec_Element, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Element");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&ICS_classCollection::acClear);
#endif
			};

		ICS_classCollection() : m_Type(ICS_Ground), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "ICS_classCollection::ICS_classCollection";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");
			ac_Push(m_idx_vec_Element, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Element");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&ICS_classCollection::acClear);
#endif
			};

		~ICS_classCollection()
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

		vector<shared_ptr<ICS_classElement>> m_vec_Element;
		vector<shared_ptr<ICS_classSurface>> m_vec_Surface;
		vector<shared_ptr<ICS_classLeg>> m_vec_Leg;

		int m_idx_vec_Element;
	};

	class ICS_classCollectionScript : public ecom_base
	{
	public:
		ICS_classCollectionScript(uint f_Type) : m_Type(f_Type), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "ICS_classCollectionScript::ICS_classCollectionScript";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&ICS_classCollectionScript::acClear);
#endif
			};
		ICS_classCollectionScript() : m_Type(ICS_Ground), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "ICS_classCollectionScript::ICS_classCollectionScript";

			acClear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Scale, f_ref_CurrentPath + g_ref_Div + "m_Scale");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&ICS_classCollectionScript::acClear);
#endif
			};

		~ICS_classCollectionScript() {};

		void acClear(void)
			{
			m_vec_ElementScript.clear();
			}

		ICS_classWorth* acStructuredAnalysis(/*target*/);

		uint m_Type;
		uint m_Status;

		float m_Scale;

		vector<shared_ptr<ICS_classElementScript>> m_vec_ElementScript;
	};

};

#include "ICS_Target.h"

#endif