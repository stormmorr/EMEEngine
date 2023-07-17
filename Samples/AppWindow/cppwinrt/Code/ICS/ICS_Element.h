/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ICS_ELEMENT_H
#define ICS_ELEMENT_H

#include <vector>
#include <math.h>

#include "ICS_Color.h"

#include "Include\Cube.h"

#include "../Musion/Code.h"

#define COMPONENT_CNT_BASE 2
#define VARIABLE_STATE_NORMAL 1
#define VARIABLE_STATE_POINTER 2
#define ELEMENT_SCRIPT_LANGUAGE_C 1
#define ELEMENT_SCRIPT_LANGUAGE_ESL 2
#define COMPONENT_TYPE_VARINSTA 1
#define COMPONENT_TYPE_FUNCTIONCALL 2
#define VARIABLE_TYPE_INT 1
#define COMPONENT_ELEMENT_TYPE_VARIABLE 1
#define COMPONENT_ELEMENT_TYPE_FUNCTION 2
#define COMPONENT_ELEMENT_TYPE_PROG 3
#define PROG_TYPE_OPERATOR 1
#define PROG_TYPE_BKT 2
#define PROG_TYPE_PAREN 3
#define OPERATOR_TYPE_PLUS 1

using namespace Cube;
using namespace std;

namespace ecoin
{

	enum
	{
		ICS_ELEM_Element
	};

	enum
	{
		ICS_ELEM_Status_Birth,
		ICS_ELEM_Status_Processing,
		ICS_ELEM_Status_Accepted,
		ICS_ELEM_Status_Total
	};

	class ICS_classElement;

	class ICS_classWorth : public ecom_base
	{
	public:
		ICS_classWorth()
			{
			//...
			};
		ICS_classWorth(shared_ptr<ICS_classElement> f_Element)
			{
			//...
			};
		~ICS_classWorth() {};

		float m_USD;
		float m_BTC;
		float m_GBP;
	};

	class ICS_classCorner;
	class ICS_classSurface;
	class ICS_classLeg;

	class ICS_classJoint
	{
	public:
		ICS_classJoint()
			{
			m_Aggressor = nullptr;
			m_Saint = nullptr;
			};
		ICS_classJoint(shared_ptr<ICS_classElement> f_A, shared_ptr<ICS_classElement> f_S)
			{
			m_Aggressor = f_A;
			m_Saint = f_S;
			};
		~ICS_classJoint() {};

		shared_ptr<ICS_classElement> m_Aggressor;
		shared_ptr<ICS_classElement> m_Saint;
	};
	
	class ICS_classResult : public ecom_base_flap
	{
	public:
		ICS_classResult()
			{
			m_vec_Corner.clear();
			};
		~ICS_classResult()
			{
			m_vec_Corner.clear();
			};

		vector<ICS_classCorner> m_vec_Corner;

		float m_Dist01;
		float m_Dist23;
		float m_Dist45;
		float m_Dist67;

		float m_Dist02;
		float m_Dist13;
		float m_Dist46;
		float m_Dist57;

		float m_Dist04;
		float m_Dist15;
		float m_Dist26;
		float m_Dist37;

		float m_Dist01234567;
		float m_Dist02134657;
		float m_Dist04152637;

		int m_LevelParent;
		shared_ptr<ICS_classElement> m_Parent;

		float m_SurfToLegRatio;
		float m_SurfToLegRatioX;
		float m_SurfToLegRatioY;
		float m_SurfToLegRatioZ;

		BiPlane m_ProportionalPlane;
	};

	class ICS_classElement : public ecom_base
	{
	public:
		ICS_classElement(shared_ptr<ICS_classElement> f_Element) : m_Type(f_Element->m_Type), m_Status(f_Element->m_Status)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			m_R = f_Element->m_R;
			m_G = f_Element->m_G;
			m_B = f_Element->m_B;

			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(shared_ptr<CubeBicycle> f_Bicycle) : m_Type(ICS_ELEM_Element), m_Status(ICS_ELEM_Element)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			vec_Vertex.reserve(8);
			vec_Color.reserve(8);

			acGen_fromBicycle(f_Bicycle);

			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(shared_ptr<CubeBicycle> f_Bicycle, bool f_Affinity) : m_Type(ICS_ELEM_Element), m_Status(ICS_ELEM_Element)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			vec_Vertex.reserve(8);
			vec_Color.reserve(8);

			acGen_fromBicycle(f_Bicycle);

			acSetup_Corners();

			//m_Orten = f_Element->m_Orten;
			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(uint f_Type) : m_Type(f_Type), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			acColorise(0.5f, 0.5f, 0.5f, 1.0f);
			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			acColorise(0.5f, 0.5f, 0.5f, 1.0f);
			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(uint f_Type, uint f_Status, classColor f_Color) : m_Type(f_Type), m_Status(f_Status)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			acColorise(f_Color.m_R, f_Color.m_G, f_Color.m_B, f_Color.m_A);
			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(uint f_Type, uint f_Status, classColor* f_Color) : m_Type(f_Type), m_Status(f_Status)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			acColorise(f_Color->m_R, f_Color->m_G, f_Color->m_B, f_Color->m_A);
			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement(float f_Volume) : m_Type(0), m_Status(0)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			m_Volume = f_Volume;
			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		ICS_classElement() : m_Type(0), m_Status(0)
			{
			std::string f_ref_CurrentPath = "classElement::classElement";

			m_OCSCP_Flag = true;

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_R, f_ref_CurrentPath + g_ref_Div + "m_R");
			ac_Push(m_G, f_ref_CurrentPath + g_ref_Div + "m_G");
			ac_Push(m_B, f_ref_CurrentPath + g_ref_Div + "m_B");
			ac_Push(m_A, f_ref_CurrentPath + g_ref_Div + "m_A");
			ac_Push(m_Volume, f_ref_CurrentPath + g_ref_Div + "m_Volume");
			ac_Push(m_vec_Collission, f_ref_CurrentPath + g_ref_Div + "m_vec_Collission");
			ac_Push(m_vec_IsIn, f_ref_CurrentPath + g_ref_Div + "m_vec_IsIn");
			ac_Push(m_Base, f_ref_CurrentPath + g_ref_Div + "m_Base");
			ac_Push(m_Index, f_ref_CurrentPath + g_ref_Div + "m_Index");
			ac_Push(m_OCSCP_Flag, f_ref_CurrentPath + g_ref_Div + "m_OCSCP_Flag");

			make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSetup_Corners", (void(ecom_base::*)(void))&ICS_classElement::acSetup_Corners);
#endif
			}

		~ICS_classElement()
			{
			m_vec_Element.clear();
			m_vec_Surface.clear();
			m_vec_Leg.clear();

			vec_Vertex.clear();
			vec_Color.clear();

			m_vec_Collission.clear();
			m_vec_IsIn.clear();

			m_vec_Joint.clear();
			};

		void acStructuredAnalysis(void);

		void acColorise(float f_R, float f_G, float f_B, float f_A)
			{
			m_R = f_R;
			m_G = f_G;
			m_B = f_B;
			m_A = f_A;
			}

		void acColorise(classColor *f_Color)
			{
			m_R = f_Color->m_R;
			m_G = f_Color->m_G;
			m_B = f_Color->m_B;
			m_A = f_Color->m_A;
			}

		void acColorise(classColor f_Color)
			{
			m_R = f_Color.m_R;
			m_G = f_Color.m_G;
			m_B = f_Color.m_B;
			m_A = f_Color.m_A;
			}

		void acGen_fromBicycle(shared_ptr<CubeBicycle> f_Bicycle);
		void acSync_fromBicycle(shared_ptr<CubeBicycle> f_Bicycle);
		void acSync_fromBicycle_affinity(shared_ptr<CubeBicycle> f_Bicycle);

		void acSetup_Corners(void);

		int acSize_Surface(void);
		int acSize_Leg(void);

		uint m_Type;
		uint m_Status;

		float m_R;
		float m_G;
		float m_B;
		float m_A;

		std::shared_ptr<BiVector> m_Center;

		ICS_classWorth m_Worth;

		vector<shared_ptr<ICS_classElement>> m_vec_Element;
		vector<shared_ptr<ICS_classSurface>> m_vec_Surface;
		vector<shared_ptr<ICS_classLeg>> m_vec_Leg;

		vector<shared_ptr<Cube::BiVector>> vec_Vertex;
		vector<shared_ptr<Cube::BiVector>> vec_Color;

		shared_ptr<aabb> m_aabb;
		float m_Volume;

		vector<int> m_vec_Collission;
		vector<int> m_vec_IsIn;

		vector<ICS_classJoint> m_vec_Joint;

		float acCompare(shared_ptr<ICS_classElement> f_Element, float f_QualityRank, bool f_testVolumes);

		  ////////////////////////////////////
		 // LEGACY of Structured Analysis
		//
		ICS_classResult m_Result;
		int m_Base;
		int m_Index;

		bool m_OCSCP_Flag;
	};

	class ICS_classComponent : public ecom_base
	{
	public:
		ICS_classComponent(std::shared_ptr<ICS_classComponent> f_Component) : m_Type(f_Component->m_Type), m_Status(f_Component->m_Status)
			{
			std::string f_ref_CurrentPath = "classComponent::classComponent";

			m_vec_String.clear();

			for(int f_Str = 0; f_Str < f_Component->m_vec_String.size(); f_Str++)
				{
				m_vec_String.push_back(f_Component->m_vec_String[f_Str]);
				}

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
			ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
			ac_Push(m_vec_String, f_ref_CurrentPath + g_ref_Div + "m_vec_String");
			ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
			ac_Push(m_Level, f_ref_CurrentPath + g_ref_Div + "m_Level");
#endif
			};

		ICS_classComponent(uint f_Type) : m_Type(f_Type), m_Status(ICS_ELEM_Status_Birth)
			{
			std::string f_ref_CurrentPath = "classComponent::classComponent";

			m_vec_String.clear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
			ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
			ac_Push(m_vec_String, f_ref_CurrentPath + g_ref_Div + "m_vec_String");
			ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
			ac_Push(m_Level, f_ref_CurrentPath + g_ref_Div + "m_Level");
#endif
			};

		ICS_classComponent(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			std::string f_ref_CurrentPath = "classComponent::classComponent";

			m_vec_String.clear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
			ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
			ac_Push(m_vec_String, f_ref_CurrentPath + g_ref_Div + "m_vec_String");
			ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
			ac_Push(m_Level, f_ref_CurrentPath + g_ref_Div + "m_Level");
#endif
			};

		ICS_classComponent(uint f_Type, uint f_Status, classColor f_Color) : m_Type(f_Type), m_Status(f_Status)
			{
			std::string f_ref_CurrentPath = "classComponent::classComponent";

			m_vec_String.clear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
			ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
			ac_Push(m_vec_String, f_ref_CurrentPath + g_ref_Div + "m_vec_String");
			ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
			ac_Push(m_Level, f_ref_CurrentPath + g_ref_Div + "m_Level");
#endif
			};

		ICS_classComponent() : m_Type(0), m_Status(0)
			{
			std::string f_ref_CurrentPath = "classComponent::classComponent";

			m_vec_String.clear();

#ifndef OSI_MEM_APP
			ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
			ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
			ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
			ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
			ac_Push(m_vec_String, f_ref_CurrentPath + g_ref_Div + "m_vec_String");
			ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
			ac_Push(m_Level, f_ref_CurrentPath + g_ref_Div + "m_Level");
#endif
			};

		~ICS_classComponent() {};

		uint m_Type;
		uint m_Status;
		ICS_classWorth m_Worth;

		std::string m_Name;
		std::string m_Hash;
		vector<std::string> m_vec_String;
		std::string m_String;

		vector<int> m_Level;
		vector<std::shared_ptr<CodeLine>> m_vec_Code;

		float acCompare(std::shared_ptr<ICS_classComponent> f_Element, float f_QualityRank, bool f_testVolumes);
	};

	class ICS_classElementScript : public ecom_base_flap
	{
	public:
		ICS_classElementScript(std::shared_ptr<ICS_classElementScript> f_ElementScript) : m_Type(f_ElementScript->m_Type), m_Status(f_ElementScript->m_Status)
			{
			m_vec_Component.clear();

			for(int f_Str = 0; f_Str < f_ElementScript->m_vec_Component.size(); f_Str++)
				{
				m_vec_Component.push_back(f_ElementScript->m_vec_Component[f_Str]);
				}

			//m_Orten = f_Element->m_Orten;
			};
		ICS_classElementScript(shared_ptr<ICS_classElement> f_Element) : m_Type(f_Element->m_Type), m_Status(f_Element->m_Status)
			{
			acGen_fromElement(f_Element);

			//m_Orten = f_Element->m_Orten;
			};
		ICS_classElementScript(uint f_Type) : m_Type(f_Type), m_Status(ICS_ELEM_Status_Birth)
			{
			m_vec_Component.clear();
			};
		ICS_classElementScript(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			m_vec_Component.clear();
			};
		ICS_classElementScript(float f_Volume) : m_Type(0), m_Status(0)
			{
			m_Volume = f_Volume;
			};
		ICS_classElementScript() : m_Type(0), m_Status(0)
			{
			};
		virtual ~ICS_classElementScript() {};

		shared_ptr<ICS_classResult> acStructuredAnalysis(void);

		void acGen_fromElement(shared_ptr<ICS_classElement> f_Element, int f_ScriptLanguageScheme = 1);

		uint m_Type;
		uint m_Status;

		BiVector m_Center;
		//BiOrientation m_Orten;
		ICS_classWorth m_Worth;

		vector<std::shared_ptr<ICS_classElementScript>> m_vec_ElementScript;

		vector<std::shared_ptr<ICS_classComponent>> m_vec_Component;
		std::string m_Data;
		std::string m_Hash;

		std::shared_ptr<aabb> m_aabb;
		float m_Volume;

		vector<int> m_vec_Collission;
		vector<int> m_vec_IsIn;

		vector<std::shared_ptr<ICS_classJoint>> m_vec_Joint;

		float acCompare(shared_ptr<ICS_classElement> f_Element, float f_QualityRank, bool f_testVolumes);

		  ////////////////////////////////////
		 // LEGACY of Structured Analysis
		//
		vector<shared_ptr<ICS_classResult>> m_vec_Result;
		int m_Base;
		int m_Index;
	};

	class ICS_classTestSchema : public ecom_base_flap
	{
	public:
		ICS_classTestSchema(ICS_classTestSchema* f_Schema) : m_Type(f_Schema->m_Type), m_Status(f_Schema->m_Status)
			{
			};
		ICS_classTestSchema(uint f_Type) : m_Type(f_Type), m_Status(ICS_ELEM_Status_Birth)
			{
			};
		ICS_classTestSchema(uint f_Type, uint f_Status) : m_Type(f_Type), m_Status(f_Status)
			{
			};
		ICS_classTestSchema(float f_Volume) : m_Type(0), m_Status(0)
			{
			m_Volume = f_Volume;
			};
		ICS_classTestSchema() : m_Type(0), m_Status(0)
			{
			};
		virtual ~ICS_classTestSchema() {};

		uint m_Type;
		uint m_Status;

		BiVector m_Center;
		//BiOrientation m_Orten;
		ICS_classWorth m_Worth;

		std::string m_Data;
		std::string m_Hash;

		std::shared_ptr<aabb> m_aabb;
		float m_Volume;

		vector<int> m_vec_Collission;
		vector<int> m_vec_IsIn;

		std::vector<BiVector> f_ReferencePoint;
	};

	extern std::string ag_ICS_takeMeasurement0(std::shared_ptr<ICS_classElement> f_Vertex);
	extern int ag_ICS_takeMeasurementINTV0(std::shared_ptr<ICS_classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart = 0, int f_Depth = 1);
	extern std::string ag_ICS_NameStamp0(std::string f_Measurement, int f_Type, int f_BitCount);
	extern std::string ag_ICS_GenerateValue0(std::string f_Measurement);
};

#endif