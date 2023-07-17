/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code/myBO/icSafeL.h"

#include "Wallet/Wallet.h"

#include "Code/CLS/Target.h"
#include "Code/Cube/qcom.h"
#include "Code/Cube/predator.h"

#include <cctype>
#include <iostream>
#include <cstring>

using namespace ecoin;

namespace ecoin
{
int g_TargetID = 0;

Cube::BiVector g_SchemaRef[15];

bool g_EnablePR = false;

bool g_Result = false;

std::shared_ptr<Qcom> g_ShuttleCom;

std::vector<int> g_ElementDivisor;
std::vector<int> g_ElementDivisorInt;

std::shared_ptr<classCollection> g_Lowton_Collection;

std::shared_ptr<classLMap> g_classLMap;

int g_CountLM = 4;

int g_FunctionStamp = 0;

std::shared_ptr<classTarget_JScript> g_MasterTarget = ag_reference_NameObject<classTarget_JScript>(std::string(g_ref_CurrentPath) + std::string(g_ref_Div) + "g_MasterTarget");

std::vector<std::string> g_vec_scrInputName;
int g_idx_vec_scrInputName = 0;

std::vector<std::string> g_vec_scrInputHTML;
int g_idx_vec_scrInputHTML = 0;

std::vector<int> g_vec_scrInputType;
int g_idx_vec_scrInputType;

std::vector<nameFuncPtr> g_vec_scrInputNameCuteFunc;
int g_idx_vec_scrInputNameCuteFunc = 0;

std::vector<FuncPtr> g_vec_scrInputTestCuteFunc;
int g_idx_vec_scrInputTestCuteFunc = 0;

std::vector<std::string> g_vec_scrControlName;
int g_idx_vec_scrControlName = 0;

std::vector<int> g_vec_scrControlType;
int g_idx_vec_scrControlType = 0;

std::vector<std::string> g_vec_scrOutputName;
int g_idx_vec_scrOutputName = 0;

std::vector<int> g_vec_scrOutputType;
int g_idx_vec_scrOutputType = 0;

std::vector<std::shared_ptr<classBridge>> g_vec_control_Bridge;
int g_idx_vec_control_Bridge = 0;

std::vector<std::shared_ptr<classBridge>> g_vec_output_Bridge;
int g_idx_vec_output_Bridge = 0;

std::shared_ptr<classInsta> g_This = nullptr;

std::string g_ThisName = "Default_Insta";
int g_ThisType = ESL_INSTA_TYPE_FUNC_DEF;

std::shared_ptr<classTarget> g_Target_1;
std::shared_ptr<classTarget> g_Target_2;
std::shared_ptr<classTarget_Ecom> g_Target_3;
std::shared_ptr<classTarget_Ecom> g_Target_4;
std::shared_ptr<classTarget_ESL_Script> g_Target_5;
std::shared_ptr<classTarget_ESL_Script> g_Target_6;
std::shared_ptr<classTarget_Generation_Script> g_Target_7;
std::shared_ptr<classTarget_Generation_Script> g_Target_8;
std::shared_ptr<classTarget_JScript> g_Target_9;
std::shared_ptr<classTarget_JScript> g_Target_10;

std::shared_ptr<classTarget> gf_Target_1;
std::shared_ptr<classTarget> gf_Target_2;
std::shared_ptr<classTarget_Ecom> gf_Target_3;
std::shared_ptr<classTarget_Ecom> gf_Target_4;
std::shared_ptr<classTarget_ESL_Script> gf_Target_5;
std::shared_ptr<classTarget_ESL_Script> gf_Target_6;
std::shared_ptr<classTarget_Generation_Script> gf_Target_7;
std::shared_ptr<classTarget_Generation_Script> gf_Target_8;
std::shared_ptr<classTarget_JScript> gf_Target_9;
std::shared_ptr<classTarget_JScript> gf_Target_10;

std::shared_ptr<classTarget> g_LowtonTarget_1;
std::shared_ptr<classTarget> g_LowtonTarget_2;
std::shared_ptr<classTarget_Ecom> g_LowtonTarget_3;
std::shared_ptr<classTarget_Ecom> g_LowtonTarget_4;
std::shared_ptr<classTarget_ESL_Script> g_LowtonTarget_5;
std::shared_ptr<classTarget_ESL_Script> g_LowtonTarget_6;
std::shared_ptr<classTarget_Generation_Script> g_LowtonTarget_7;
std::shared_ptr<classTarget_Generation_Script> g_LowtonTarget_8;
std::shared_ptr<classTarget_JScript> g_LowtonTarget_9;
std::shared_ptr<classTarget_JScript> g_LowtonTarget_10;

std::shared_ptr<classTarget_Ecom> g_LowtonTarget;

bool g_currentLaunch = false;
int g_currentLaunchType = 0;
std::string g_currentLaunchPrefix = "";
std::string g_currentLaunchTypeName = "";

float ag_Get_current_Target_Mark(int f_Type)
{
	switch(f_Type)
		{
		case 0:
		case 1:
			{
			return gf_Target_1->m_Mark;
			}break;
		case 2:
			{
			return gf_Target_2->m_Mark;
			}break;
		case 3:
			{
			return gf_Target_3->m_Mark;
			}break;
		case 4:
			{
			return gf_Target_4->m_Mark;
			}break;
		case 5:
			{
			return gf_Target_5->m_Mark;
			}break;
		case 6:
			{
			return gf_Target_6->m_Mark;
			}break;
		case 7:
			{
			return gf_Target_7->m_Mark;
			}break;
		case 8:
			{
			return gf_Target_8->m_Mark;
			}break;
		case 9:
			{
			return gf_Target_9->m_Mark;
			}break;
		case 10:
			{
			return gf_Target_10->m_Mark;
			}break;
		}

	return FLT_MAX;
}

void ag_EcoinSecure_Break_Assert(int f_A, int f_B)
{
	if(f_A != f_B)
		{
		__debugbreak();
		}
}

template<class _Ty>
std::shared_ptr<_Ty> ag_reference_NameObject(std::string f_Name)
{
#if 0
	std::string f_ref_CurrentPath = "GlobalScope";

	ag_StatusLive(f_ref_CurrentPath, "f_Ptr", true);

	std::shared_ptr<_Ty> f_Ptr = std::make_shared_reflect<_Ty>();

	return f_Ptr;
#else

	return nullptr;
#endif
}

classTarget::classTarget(std::shared_ptr<CubeHESH> f_Hesh)
{
	std::string f_ref_CurrentPath = "classTarget::classTarget";

	ag_StatusLive(f_ref_CurrentPath, "m_Collection");
	m_Collection = std::make_shared_reflect<classCollection>();

	m_Collection->acClear();

	m_Mark = 0.0f;

#ifndef OSI_MEM_APP
	ac_Push(m_Mark, f_ref_CurrentPath + g_ref_Div + "m_Mark");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classTarget::acGen_Humanoid);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Vehicle_Ground", (void(ecom_base::*)(void))&classTarget::acGen_Vehicle_Ground);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrintStats", (void(ecom_base::*)(void))&classTarget::acPrintStats);
#endif

	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_Element");
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Count]);
		
		f_Element->acStructuredAnalysis();

		if(f_Element->m_Result.m_SurfToLegRatio > 0.17)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_Surface");
			std::shared_ptr<classSurface> f_Surface = std::make_shared_reflect<classSurface>(f_Element);

			if(f_Element->m_Result.m_LevelParent < 0)
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Surface.push_back(f_Surface);
				m_Collection->m_vec_Element.push_back(f_Element);
				m_Collection->m_vec_Surface.push_back(f_Surface);
				}
			else
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Surface.push_back(f_Surface);
				f_Element->m_Result.m_Parent->m_vec_Element.push_back(f_Element);
				f_Element->m_Result.m_Parent->m_vec_Surface.push_back(f_Surface);
				}
			}
		else
			{
			ag_StatusLive(f_ref_CurrentPath, "f_Leg");
			std::shared_ptr<classLeg> f_Leg = std::make_shared_reflect<classLeg>(f_Element);

			if(f_Element->m_Result.m_LevelParent < 0)
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Leg.push_back(f_Leg);
				m_Collection->m_vec_Leg.push_back(f_Leg);
				m_Collection->m_vec_Element.push_back(f_Element);
				}
			else
				{
				f_Element->m_vec_Element.push_back(f_Element);
				f_Element->m_vec_Leg.push_back(f_Leg);
				f_Element->m_Result.m_Parent->m_vec_Element.push_back(f_Element);
				f_Element->m_Result.m_Parent->m_vec_Leg.push_back(f_Leg);
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		for(int f_CountCollision = 0; f_CountCollision < m_Collection->m_vec_Element.size(); f_CountCollision++)
			{
			if(f_Count != f_CountCollision)
				{
				shared_ptr<classElement> f_ElementCollide = m_Collection->m_vec_Element[f_CountCollision];
				
				if(f_Element->m_aabb->collide(f_ElementCollide->m_aabb))
					{
					f_Element->m_vec_Collission.push_back(f_CountCollision);
					
					if(f_Element->m_aabb->inside(f_ElementCollide->m_Center))
						{
						f_ElementCollide->m_vec_IsIn.push_back(f_CountCollision);
						}

					if(f_ElementCollide->m_aabb->inside(f_Element->m_Center))
						{
						f_Element->m_vec_IsIn.push_back(f_Count);
						}
					}
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_IsIn.size() == 1)
			{
			shared_ptr<classElement> f_ParentElement = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]];

			f_ParentElement->m_vec_Element.push_back(f_Element);

			// Leg
			if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() >= 1)
				{
				f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
				}
			else // Surface
				{
				if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() == 0)
					{
					//Do nothing
					}
				else // Surface
					{
					if(f_Element->acSize_Surface() >= 1)
						{
						f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
						}
					}
				}

			for(int f_Coyu = 0; f_Coyu < f_Element->m_Result.m_vec_Corner.size(); f_Coyu++)
				{
				classCorner f_Corner;

				f_Corner.m_Corner = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Corner;
				f_Corner.m_X = f_Element->m_Result.m_vec_Corner[f_Coyu].m_X;
				f_Corner.m_Y = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Y;
				f_Corner.m_Z = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Z;

				f_ParentElement->m_Result.m_vec_Corner.push_back(f_Corner);
				}

			classJoint f_Joint(f_ParentElement, f_Element);

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_ParentElement->m_vec_Joint.push_back(f_Joint);
			}
		else if(f_Element->m_vec_IsIn.size() > 1)
			{
			float f_Size = 0.0f;
			int f_Index = -1;

			if(f_Count == 0)
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[1]]->m_Volume;
				}
			else
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]]->m_Volume;
				}

			for(int f_CountSize = 0; f_CountSize < m_Collection->m_vec_Element.size(); f_CountSize++)
				{
				if(f_Count != f_CountSize)
					{
					shared_ptr<classElement> f_SizeElement = m_Collection->m_vec_Element[f_CountSize];

					if(f_SizeElement->m_Volume < f_Size)
						{
						f_Size = f_SizeElement->m_Volume;
						f_Index = f_CountSize;
						}
					}
				}
			
			if(f_Index >= 0)
				{
				shared_ptr<classElement> f_ParentElement = m_Collection->m_vec_Element[f_Index];

				f_ParentElement->m_vec_Element.push_back(f_Element);

				// Leg
				if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() >= 1)
					{
					f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
					}
				else // Surface
					{
					if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() == 0)
						{
						//Do nothing
						}
					else // Surface
						{
						if(f_Element->acSize_Surface() >= 1)
							{
							f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
							}
						}
					}

				for(int f_Coyu = 0; f_Coyu < f_Element->m_Result.m_vec_Corner.size(); f_Coyu++)
					{
					classCorner f_Corner;

					f_Corner.m_Corner = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Corner;
					f_Corner.m_X = f_Element->m_Result.m_vec_Corner[f_Coyu].m_X;
					f_Corner.m_Y = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Y;
					f_Corner.m_Z = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Z;

					f_ParentElement->m_Result.m_vec_Corner.push_back(f_Corner);
					}

				classJoint f_Joint(f_ParentElement, f_Element);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_ParentElement->m_vec_Joint.push_back(f_Joint);
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_Collission.size() == 1)
			{
			shared_ptr<classElement> f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[0]];

			if (f_Element->m_Volume >= f_FriendlyElement->m_Volume)
				{
				classJoint f_Joint(f_Element, f_FriendlyElement);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
				}
			else
				{
				classJoint f_Joint(f_FriendlyElement, f_Element);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
				}
			}
		else if(f_Element->m_vec_Collission.size() > 1)
			{
			for(int f_CountElement = 0; f_CountElement < f_Element->m_vec_Collission.size(); f_CountElement++)
				{
				if(f_Count != f_CountElement)
					{
					shared_ptr<classElement> f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[f_CountElement]];

					if(f_Element->m_Volume >= f_FriendlyElement->m_Volume)
						{
						classJoint f_Joint(f_Element, f_FriendlyElement);

						f_Element->m_vec_Joint.push_back(f_Joint);
						f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
						}
					else
						{
						classJoint f_Joint(f_FriendlyElement, f_Element);

						f_Element->m_vec_Joint.push_back(f_Joint);
						f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
						}
					}
				}
			}
		}

	m_Mark = 0.0f;
}

classTarget::classTarget(std::shared_ptr<classCollection> f_Collection)
{
	std::string f_ref_CurrentPath = "classTarget::classTarget";

	m_Collection = f_Collection;
	m_Collection->acClear();

#ifndef OSI_MEM_APP
	ac_Push(m_Mark, f_ref_CurrentPath + g_ref_Div + "m_Mark");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Humanoid", (void(ecom_base::*)(void))&classTarget::acGen_Humanoid);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acGen_Vehicle_Ground", (void(ecom_base::*)(void))&classTarget::acGen_Vehicle_Ground);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrintStats", (void(ecom_base::*)(void))&classTarget::acPrintStats);
#endif
}

void classTarget::acSync_fromHesh(std::shared_ptr<CubeHESH> f_Hesh)
{
	std::string f_ref_CurrentPath = "classTarget::acSync_fromHesh";

	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		if(f_Count < m_Collection->m_vec_Element.size())
			{
			std::shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

			f_Element->m_vec_Element.clear();

			f_Element->acSync_fromBicycle_affinity(f_Hesh->vec_Bicycle[f_Count]);
		 
			f_Element->m_Result.m_vec_Corner.clear();
			f_Element->m_vec_Joint.clear();
			f_Element->m_vec_IsIn.clear();
			f_Element->m_vec_Collission.clear();

			f_Element->acStructuredAnalysis();

			if(f_Element->m_Result.m_SurfToLegRatio > 0.17)
				{
				std::shared_ptr<classSurface> f_Surface = m_Collection->m_vec_Surface[f_Count];
				std::shared_ptr<classLeg> f_OffLeg = m_Collection->m_vec_Leg[f_Count];

				f_Surface->m_FULLON = true;
				f_OffLeg->m_FULLON = false;
				}
			else
				{
				std::shared_ptr<classLeg> f_Leg = m_Collection->m_vec_Leg[f_Count];
				std::shared_ptr<classSurface> f_OffSurface = m_Collection->m_vec_Surface[f_Count];

				f_Leg->m_FULLON = true;
				f_OffSurface->m_FULLON = false;
				}

			f_Element->m_vec_Element.push_back(f_Element);
			}
		else
			{
			ag_StatusLive(f_ref_CurrentPath, "f_Element");
			std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Count]);
		 
			f_Element->acStructuredAnalysis();

			if(f_Element->m_Result.m_SurfToLegRatio > 0.17)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_Surface");
				std::shared_ptr<classSurface> f_Surface = std::make_shared_reflect<classSurface>(f_Element);

				ag_StatusLive(f_ref_CurrentPath, "f_OffLeg");
				std::shared_ptr<classLeg> f_OffLeg = std::make_shared_reflect<classLeg>();

				if(f_Element->m_Result.m_LevelParent < 0)
					{
					f_Element->m_vec_Element.push_back(f_Element);
					f_Element->m_vec_Surface.push_back(f_Surface);
					f_Element->m_vec_Leg.push_back(f_OffLeg);
					m_Collection->m_vec_Element.push_back(f_Element);
					m_Collection->m_vec_Surface.push_back(f_Surface);
					m_Collection->m_vec_Leg.push_back(f_OffLeg);
					}
				else
					{
					f_Element->m_vec_Element.push_back(f_Element);
					f_Element->m_vec_Surface.push_back(f_Surface);
					f_Element->m_vec_Leg.push_back(f_OffLeg);
					f_Element->m_Result.m_Parent->m_vec_Element.push_back(f_Element);
					f_Element->m_Result.m_Parent->m_vec_Surface.push_back(f_Surface);
					f_Element->m_Result.m_Parent->m_vec_Leg.push_back(f_OffLeg);
					}
				}
			else
				{
				ag_StatusLive(f_ref_CurrentPath, "f_Leg");
				std::shared_ptr<classLeg> f_Leg = std::make_shared_reflect<classLeg>(f_Element);

				ag_StatusLive(f_ref_CurrentPath, "f_OffSurface");
				std::shared_ptr<classSurface> f_OffSurface = std::make_shared_reflect<classSurface>();

				if(f_Element->m_Result.m_LevelParent < 0)
					{
					f_Element->m_vec_Element.push_back(f_Element);
					f_Element->m_vec_Leg.push_back(f_Leg);
					f_Element->m_vec_Surface.push_back(f_OffSurface);
					m_Collection->m_vec_Leg.push_back(f_Leg);
					m_Collection->m_vec_Surface.push_back(f_OffSurface);
					m_Collection->m_vec_Element.push_back(f_Element);
					}
				else
					{
					f_Element->m_vec_Element.push_back(f_Element);
					f_Element->m_vec_Leg.push_back(f_Leg);
					f_Element->m_vec_Surface.push_back(f_OffSurface);
					f_Element->m_Result.m_Parent->m_vec_Element.push_back(f_Element);
					f_Element->m_Result.m_Parent->m_vec_Leg.push_back(f_Leg);
					f_Element->m_Result.m_Parent->m_vec_Surface.push_back(f_OffSurface);
					}
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		f_Element->m_vec_Collission.clear();

		for(int f_CountCollision = 0; f_CountCollision < m_Collection->m_vec_Element.size(); f_CountCollision++)
			{
			if(f_Count != f_CountCollision)
				{
				shared_ptr<classElement> f_ElementCollide = m_Collection->m_vec_Element[f_CountCollision];
				
				if(f_Element->m_aabb->collide(f_ElementCollide->m_aabb))
					{
					f_Element->m_vec_Collission.push_back(f_CountCollision);
					
					if(f_Element->m_aabb->inside(f_ElementCollide->m_Center))
						{
						f_ElementCollide->m_vec_IsIn.push_back(f_CountCollision);
						}

					if(f_ElementCollide->m_aabb->inside(f_Element->m_Center))
						{
						f_Element->m_vec_IsIn.push_back(f_Count);
						}
					}
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_IsIn.size() == 1)
			{
			shared_ptr<classElement> f_ParentElement = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]];

			f_ParentElement->m_vec_Element.push_back(f_Element);

			// Leg
			if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() >= 1)
				{
				f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
				}
			else // Surface
				{
				if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() == 0)
					{
					//Do nothing
					}
				else // Surface
					{
					if(f_Element->acSize_Surface() >= 1)
						{
						f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
						}
					}
				}

			for(int f_Coyu = 0; f_Coyu < f_Element->m_Result.m_vec_Corner.size(); f_Coyu++)
				{
				classCorner f_Corner;

				f_Corner.m_Corner = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Corner;
				f_Corner.m_X = f_Element->m_Result.m_vec_Corner[f_Coyu].m_X;
				f_Corner.m_Y = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Y;
				f_Corner.m_Z = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Z;

				f_ParentElement->m_Result.m_vec_Corner.push_back(f_Corner);
				}

			classJoint f_Joint(f_ParentElement, f_Element);

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_ParentElement->m_vec_Joint.push_back(f_Joint);
			}
		else if(f_Element->m_vec_IsIn.size() > 1)
			{
			float f_Size = 0.0f;
			int f_Index = -1;

			if(f_Count == 0)
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[1]]->m_Volume;
				}
			else
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]]->m_Volume;
				}

			for(int f_CountSize = 0; f_CountSize < m_Collection->m_vec_Element.size(); f_CountSize++)
				{
				if(f_Count != f_CountSize)
					{
					std::shared_ptr<classElement> f_SizeElement = m_Collection->m_vec_Element[f_CountSize];

					if(f_SizeElement->m_Volume < f_Size)
						{
						f_Size = f_SizeElement->m_Volume;
						f_Index = f_CountSize;
						}
					}
				}
			
			if(f_Index >= 0)
				{
				std::shared_ptr<classElement> f_ParentElement = m_Collection->m_vec_Element[f_Index];

				f_ParentElement->m_vec_Element.push_back(f_Element);

				// Leg
				if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() >= 1)
					{
					f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
					}
				else // Surface
					{
					if(f_Element->acSize_Surface() == 0 && f_Element->acSize_Leg() == 0)
						{
						//Do nothing
						}
					else // Surface
						{
						if(f_Element->acSize_Surface() >= 1)
							{
							f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
							}
						}
					}

				for(int f_Coyu = 0; f_Coyu < f_Element->m_Result.m_vec_Corner.size(); f_Coyu++)
					{
					classCorner f_Corner;

					f_Corner.m_Corner = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Corner;
					f_Corner.m_X = f_Element->m_Result.m_vec_Corner[f_Coyu].m_X;
					f_Corner.m_Y = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Y;
					f_Corner.m_Z = f_Element->m_Result.m_vec_Corner[f_Coyu].m_Z;

					f_ParentElement->m_Result.m_vec_Corner.push_back(f_Corner);
					}

				classJoint f_Joint(f_ParentElement, f_Element);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_ParentElement->m_vec_Joint.push_back(f_Joint);
				}
			}
		}

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_Collission.size() == 1)
			{
			shared_ptr<classElement> f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[0]];

			if(f_Element->m_Volume >= f_FriendlyElement->m_Volume)
				{
				classJoint f_Joint(f_Element, f_FriendlyElement);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
				}
			else
				{
				classJoint f_Joint(f_FriendlyElement, f_Element);

				f_Element->m_vec_Joint.push_back(f_Joint);
				f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
				}
			}
		else if(f_Element->m_vec_Collission.size() > 1)
			{
			for(int f_CountElement = 0; f_CountElement < f_Element->m_vec_Collission.size(); f_CountElement++)
				{
				if(f_Count != f_CountElement)
					{
					shared_ptr<classElement> f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[f_CountElement]];

					if(f_Element->m_Volume >= f_FriendlyElement->m_Volume)
						{
						classJoint f_Joint(f_Element, f_FriendlyElement);

						f_Element->m_vec_Joint.push_back(f_Joint);
						f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
						}
					else
						{
						classJoint f_Joint(f_FriendlyElement, f_Element);

						f_Element->m_vec_Joint.push_back(f_Joint);
						f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
						}
					}
				}
			}
		}

	m_Mark = 0.0f;
}

classTargetScript::classTargetScript(std::shared_ptr<CubeHESH> f_Hesh)
{
	std::string f_ref_CurrentPath = "classTargetScript::classTargetScript";

#ifndef OSI_MEM_APP
	ac_Push(m_Mark, f_ref_CurrentPath + g_ref_Div + "m_Mark");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ag_PrintScriptHeader", (void(ecom_base::*)(void))&classTargetScript::ag_PrintScriptHeader);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrint", (void(ecom_base::*)(void))&classTargetScript::acPrint);
#endif

	ag_StatusLive(f_ref_CurrentPath, "m_Collection");
	m_Collection = std::make_shared_reflect<classCollection>();
	m_Collection->acClear();

	ag_StatusLive(f_ref_CurrentPath, "m_CollectionScript");
	m_CollectionScript = std::make_shared_reflect<classCollectionScript>();
	m_CollectionScript->acClear();

	for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_Element");
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Hesh->m_adIndex[f_Count]]);

		//ag_StatusLive(f_ref_CurrentPath, "f_ElementScript");
		//std::shared_ptr<classElementScript> f_ElementScript = std::make_shared_reflect<classElementScript>(f_Element);

		f_Element->acStructuredAnalysis();

		m_Collection->m_vec_Element.push_back(f_Element);
		//m_CollectionScript->m_vec_ElementScript.push_back(f_ElementScript);
		}

#pragma message("FIXME::Add connect the variable same names to collection script for circuit")

	m_Mark = 0.0f;
}

void classTarget::acPrintStats(void)
{
	printf("classTarget Statistics");

}

bool classTarget::acCompare(std::shared_ptr<classTarget> f_Target, float f_QualityRank, float f_Grade, bool f_testVolumes)
{
	 /////////////////////
	//Prime Decision
	bool f_True = false;

	if(m_Collection->m_vec_Element.size() < f_Target->m_Collection->m_vec_Element.size())
		{
		f_Target->m_Mark = 0.0f;

		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);

			f_Target->m_Mark += f_Mark;
			}
		}
	else
		{
		f_Target->m_Mark = 0.0f;

		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			float f_fakeMark = 0.0f;

			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);

			f_fakeMark = f_Mark;

			for(int f_Cam = 0; f_Cam < f_Target->m_Collection->m_vec_Element.size(); f_Cam++)
				{
				shared_ptr<classElement> f_ElementB = m_Collection->m_vec_Element[f_Count];
				shared_ptr<classElement> f_TestElementB = f_Target->m_Collection->m_vec_Element[f_Cam];

				f_Mark = f_ElementB->acCompare(f_TestElementB, f_QualityRank, f_testVolumes);

				if(f_Mark < f_fakeMark)
					{
					f_fakeMark = f_Mark;
					}
				}

			f_Target->m_Mark += f_fakeMark;
			}
		}

	if((f_Target->m_Mark > 0.0f) && (f_Target->m_Mark < f_Grade))
		{
		f_True = true;
		}
	else
		{
		f_True = false;
		}

#if 0
	CubeHESHGen(%i)QualityRank[%f]:Mark %f < Diff(%f) tVol=%i g_Boost(%f)\n", f_True, f_QualityRank, f_Target->m_Mark, f_Grade, f_testVolumes, g_CoolBoost
#endif

	return f_True;
}

float classTarget::acMatch(std::shared_ptr<classTarget> f_Target)
{
	float f_Mark = 0.0f;

	if(m_Collection->m_vec_Element.size() < f_Target->m_Collection->m_vec_Element.size())
		{
		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			for(int f_XY = 0; f_XY < 8; f_XY++)
				{
				BiVector f_Vector = *(f_Element->vec_Vertex[f_XY].get());
				BiVector f_TestVector = *(f_TestElement->vec_Vertex[f_XY].get());

				BiVector f_LengthVec = f_TestVector - f_Vector;

				float f_Length = f_LengthVec.acLength();

				f_Mark += f_Length * ECOIN_TARGET_MATCH_LENGTH_FACTOR;

				BiVector f_VectorC = *(f_Element->vec_Color[f_XY].get());
				BiVector f_TestVectorC = *(f_TestElement->vec_Color[f_XY].get());

				BiVector f_LengthVecC = f_TestVectorC - f_VectorC;

				float f_LengthC = f_LengthVecC.acLength();

				f_Mark += f_LengthC * ECOIN_TARGET_MATCH_COLOR_LENGTH_FACTOR;
				}
			}
		}
	else
		{
		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_Count];
			shared_ptr<classElement> f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			for(int f_XY = 0; f_XY < 8; f_XY++)
				{
				BiVector f_Vector = *(f_Element->vec_Vertex[f_XY].get());
				BiVector f_TestVector = *(f_TestElement->vec_Vertex[f_XY].get());

				BiVector f_LengthVec = f_TestVector - f_Vector;

				float f_Length = f_LengthVec.acLength();

				f_Mark += f_Length * ECOIN_TARGET_MATCH_LENGTH_FACTOR;

				BiVector f_VectorC = *(f_Element->vec_Color[f_XY].get());
				BiVector f_TestVectorC = *(f_TestElement->vec_Color[f_XY].get());

				BiVector f_LengthVecC = f_TestVectorC - f_VectorC;

				float f_LengthC = f_LengthVecC.acLength();

				f_Mark += f_LengthC * ECOIN_TARGET_MATCH_COLOR_LENGTH_FACTOR;
				}
			}
		}

	if(f_Mark > 0.0f)
		{
		return f_Mark;
		}

	return FLT_MAX;
}

void classTarget::acGen_Humanoid(void)
{
	std::string f_ref_CurrentPath = "classTarget::acGen_Humanoid";

	for(int f_XY = 0; f_XY < 1; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_Head");
		std::shared_ptr<classElement> f_Head = std::make_shared_reflect<classElement>(0.35f);
		ag_StatusLive(f_ref_CurrentPath, "f_Torso");
		std::shared_ptr<classElement> f_Torso = std::make_shared_reflect<classElement>(1.0f);
		ag_StatusLive(f_ref_CurrentPath, "f_Pelvis");
		std::shared_ptr<classElement> f_Pelvis = std::make_shared_reflect<classElement>(0.45f);
		ag_StatusLive(f_ref_CurrentPath, "f_RightArm");
		std::shared_ptr<classElement> f_RightArm = std::make_shared_reflect<classElement>(0.35f);
		ag_StatusLive(f_ref_CurrentPath, "f_LeftArm");
		std::shared_ptr<classElement> f_LeftArm = std::make_shared_reflect<classElement>(0.35f);
		ag_StatusLive(f_ref_CurrentPath, "f_RightLeg");
		std::shared_ptr<classElement> f_RightLeg = std::make_shared_reflect<classElement>(0.55f);
		ag_StatusLive(f_ref_CurrentPath, "f_LeftLeg");
		std::shared_ptr<classElement> f_LeftLeg = std::make_shared_reflect<classElement>(0.55f);

		f_Head->m_vec_Element.push_back(f_Head);
		f_Torso->m_vec_Element.push_back(f_Head);
		f_Pelvis->m_vec_Element.push_back(f_Head);
		f_RightArm->m_vec_Element.push_back(f_Head);
		f_LeftArm->m_vec_Element.push_back(f_Head);
		f_RightLeg->m_vec_Element.push_back(f_Head);
		f_LeftLeg->m_vec_Element.push_back(f_Head);

		ag_StatusLive(f_ref_CurrentPath, "f_Head->m_vec_Leg");
		f_Head->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Head));
		ag_StatusLive(f_ref_CurrentPath, "f_Torso->m_vec_Leg");
		f_Torso->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Torso));
		ag_StatusLive(f_ref_CurrentPath, "f_Pelvis->m_vec_Leg");
		f_Pelvis->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Pelvis));
		ag_StatusLive(f_ref_CurrentPath, "f_RightArm->m_vec_Leg");
		f_RightArm->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_RightArm));
		ag_StatusLive(f_ref_CurrentPath, "f_LeftArm->m_vec_Leg");
		f_LeftArm->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_LeftArm));
		ag_StatusLive(f_ref_CurrentPath, "f_RightLeg->m_vec_Leg");
		f_RightLeg->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_RightLeg));
		ag_StatusLive(f_ref_CurrentPath, "f_LeftLeg->m_vec_Leg");
		f_LeftLeg->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_LeftLeg));

		f_Head->m_Index = f_XY + 0;
		m_Collection->m_vec_Element.push_back(f_Head);
		f_Torso->m_Index = f_XY + 1;
		m_Collection->m_vec_Element.push_back(f_Torso);
		f_Pelvis->m_Index = f_XY + 2;
		m_Collection->m_vec_Element.push_back(f_Pelvis);
		f_RightArm->m_Index = f_XY + 3;
		m_Collection->m_vec_Element.push_back(f_RightArm);
		f_LeftArm->m_Index = f_XY + 4;
		m_Collection->m_vec_Element.push_back(f_LeftArm);
		f_RightLeg->m_Index = f_XY + 5;
		m_Collection->m_vec_Element.push_back(f_RightLeg);
		f_LeftLeg->m_Index = f_XY + 6;
		m_Collection->m_vec_Element.push_back(f_LeftLeg);

		m_Collection->m_vec_Leg.push_back(f_Head->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_Torso->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_Pelvis->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_RightArm->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_LeftArm->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_RightLeg->m_vec_Leg[0]);
		m_Collection->m_vec_Leg.push_back(f_LeftLeg->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_Head);
		f_Torso->m_vec_Leg.push_back(f_Head->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_Pelvis);
		f_Torso->m_vec_Leg.push_back(f_Pelvis->m_vec_Leg[0]);

		f_Pelvis->m_vec_Element.push_back(f_LeftLeg);
		f_Pelvis->m_vec_Leg.push_back(f_LeftLeg->m_vec_Leg[0]);

		f_Pelvis->m_vec_Element.push_back(f_RightLeg);
		f_Pelvis->m_vec_Leg.push_back(f_RightLeg->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_LeftArm);
		f_Torso->m_vec_Leg.push_back(f_LeftArm->m_vec_Leg[0]);

		f_Torso->m_vec_Element.push_back(f_RightArm);
		f_Torso->m_vec_Leg.push_back(f_RightArm->m_vec_Leg[0]);
		}

	m_Mark = 0.0f;
}

void classTarget::acGen_Vehicle_Ground(void)
{
	std::string f_ref_CurrentPath = "classTarget::acGen_Vehicle_Ground";
	ag_StatusLive(f_ref_CurrentPath, "f_Base");
	std::shared_ptr<classElement> f_Base = std::make_shared_reflect<classElement>(3.35f);
	ag_StatusLive(f_ref_CurrentPath, "f_Front");
	std::shared_ptr<classElement> f_Front = std::make_shared_reflect<classElement>(1.0f);
	ag_StatusLive(f_ref_CurrentPath, "f_Rear");
	std::shared_ptr<classElement> f_Rear = std::make_shared_reflect<classElement>(1.45f);
	ag_StatusLive(f_ref_CurrentPath, "f_Top");
	std::shared_ptr<classElement> f_Top = std::make_shared_reflect<classElement>(2.35f);
	ag_StatusLive(f_ref_CurrentPath, "f_LeftFrontTire");
	std::shared_ptr<classElement> f_LeftFrontTire = std::make_shared_reflect<classElement>(0.35f);
	ag_StatusLive(f_ref_CurrentPath, "f_RightFrontTire");
	std::shared_ptr<classElement> f_RightFrontTire = std::make_shared_reflect<classElement>(0.35f);
	ag_StatusLive(f_ref_CurrentPath, "f_LeftRearTire");
	std::shared_ptr<classElement> f_LeftRearTire = std::make_shared_reflect<classElement>(0.35f);
	ag_StatusLive(f_ref_CurrentPath, "f_RightRearTire");
	std::shared_ptr<classElement> f_RightRearTire = std::make_shared_reflect<classElement>(0.35f);

	ag_StatusLive(f_ref_CurrentPath, "f_Base->m_vec_Leg");
	f_Base->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Base));
	ag_StatusLive(f_ref_CurrentPath, "f_Front->m_vec_Leg");
	f_Front->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Front));
	ag_StatusLive(f_ref_CurrentPath, "f_Rear->m_vec_Leg");
	f_Rear->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Rear));
	ag_StatusLive(f_ref_CurrentPath, "f_Top->m_vec_Leg");
	f_Top->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_Top));
	ag_StatusLive(f_ref_CurrentPath, "f_LeftFrontTire->m_vec_Leg");
	f_LeftFrontTire->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_LeftFrontTire));
	ag_StatusLive(f_ref_CurrentPath, "f_RightFrontTire->m_vec_Leg");
	f_RightFrontTire->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_RightFrontTire));
	ag_StatusLive(f_ref_CurrentPath, "f_LeftRearTire->m_vec_Leg");
	f_LeftRearTire->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_LeftRearTire));
	ag_StatusLive(f_ref_CurrentPath, "f_RightRearTire->m_vec_Leg");
	f_RightRearTire->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_RightRearTire));

	f_Base->m_Index = 0;
	m_Collection->m_vec_Element.push_back(f_Base);
	f_Front->m_Index = 1;
	m_Collection->m_vec_Element.push_back(f_Front);
	f_Rear->m_Index = 2;
	m_Collection->m_vec_Element.push_back(f_Rear);
	f_Top->m_Index = 3;
	m_Collection->m_vec_Element.push_back(f_Top);
	f_LeftFrontTire->m_Index = 4;
	m_Collection->m_vec_Element.push_back(f_LeftFrontTire);
	f_RightFrontTire->m_Index = 5;
	m_Collection->m_vec_Element.push_back(f_RightFrontTire);
	f_LeftRearTire->m_Index = 6;
	m_Collection->m_vec_Element.push_back(f_LeftRearTire);
	f_RightRearTire->m_Index = 7;
	m_Collection->m_vec_Element.push_back(f_RightRearTire);

	m_Collection->m_vec_Leg.push_back(f_Base->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_Front->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_Rear->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_Top->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_LeftFrontTire->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_RightFrontTire->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_LeftRearTire->m_vec_Leg[0]);
	m_Collection->m_vec_Leg.push_back(f_RightRearTire->m_vec_Leg[0]);

	f_Base->m_vec_Element.push_back(f_Top);
	f_Base->m_vec_Leg.push_back(f_Top->m_vec_Leg[0]);

	f_Base->m_vec_Element.push_back(f_Front);
	f_Base->m_vec_Leg.push_back(f_Front->m_vec_Leg[0]);

	f_Base->m_vec_Element.push_back(f_Rear);
	f_Base->m_vec_Leg.push_back(f_Rear->m_vec_Leg[0]);

	f_Front->m_vec_Element.push_back(f_LeftFrontTire);
	f_Front->m_vec_Leg.push_back(f_LeftFrontTire->m_vec_Leg[0]);

	f_Front->m_vec_Element.push_back(f_RightFrontTire);
	f_Front->m_vec_Leg.push_back(f_RightFrontTire->m_vec_Leg[0]);

	f_Rear->m_vec_Element.push_back(f_LeftRearTire);
	f_Rear->m_vec_Leg.push_back(f_LeftRearTire->m_vec_Leg[0]);

	f_Rear->m_vec_Element.push_back(f_RightRearTire);
	f_Rear->m_vec_Leg.push_back(f_RightRearTire->m_vec_Leg[0]);

	m_Mark = 0.0f;
}

void classTarget::acLoad_from_TargetID(int f_TargetID)
{
	std::string f_ref_CurrentPath = "classTarget::acLoad_from_TargetID";

	int f_Int = 1;

	  ////////////////
	 // targets
	//
	if(f_TargetID > 0)
		{
		g_TargetID = f_TargetID;
		//ECN::Loading Target ID g_TargetID);

		char* elementquery;
		elementquery = (char*)malloc(sizeof(char) * 1024);

		::sprintf(elementquery, "SELECT id, volume FROM element WHERE targetid = %i", g_TargetID);

		g_SafeL[0]->acSelectCommand(elementquery, false, false);

		int f_eleCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_eleCount = 0;
			}
		else
			{
			f_eleCount = g_Schedular[0]->acEntrySize();
			}

		for(int f_EleID = 0; f_EleID < f_eleCount; f_EleID++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_NewElement");
			std::shared_ptr<classElement> f_NewElement = std::make_shared_reflect<classElement>((float)atof(g_Schedular[0]->acEntry(f_EleID)[1].c_str()));

			ag_StatusLive(f_ref_CurrentPath, "f_NewElement->m_vec_Leg");
			f_NewElement->m_vec_Leg.push_back(std::make_shared_reflect<classLeg>(f_NewElement));
			f_NewElement->m_Index = f_EleID;

			m_Collection->m_vec_Element.push_back(f_NewElement);
			}

		char* elindexquery;
		elindexquery = (char*)malloc(sizeof(char) * 1024);
		::sprintf(elindexquery, "SELECT elementid, resultid FROM elindex WHERE targetid = %i", g_TargetID);
		delete elindexquery;

		g_SafeL[0]->acSelectCommand(elindexquery, false, false);

		int f_elindexCount = 0;
		
		if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
			{
			f_elindexCount = 0;
			}
		else
			{
			f_elindexCount = g_Schedular[0]->acEntrySize();
			}

		for(int f_ElindexID = 0; f_ElindexID < f_elindexCount; f_ElindexID++)
			{
			shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[::atoi(g_Schedular[0]->acEntry(f_ElindexID)[0].c_str())];
			shared_ptr<classElement> f_AElement = m_Collection->m_vec_Element[::atoi(g_Schedular[0]->acEntry(f_ElindexID)[1].c_str())];
			
			f_Element->m_vec_Element.push_back(f_AElement);
			f_Element->m_vec_Leg.push_back(f_AElement->m_vec_Leg[0]);
			}

		m_Mark = 0.0f;
		}
}

void classTarget::acSaveCloud(std::string f_Name)
{
	  ////////////////
	 // targets
	//
	char* g_targetfield[5];
	char* g_targetvalue[5];

	for(int f_Count = 0; f_Count < 5; f_Count++)
		{
		g_targetfield[f_Count] = (char*)malloc(sizeof(char) * 64);
		g_targetvalue[f_Count] = (char*)malloc(sizeof(char) * 64);
		}

	::sprintf(g_targetfield[0], "name");
	::sprintf(g_targetfield[1], "difficulty");
	::sprintf(g_targetfield[2], "bckred");
	::sprintf(g_targetfield[3], "bckgreen");
	::sprintf(g_targetfield[4], "bckblue");

	::sprintf(g_targetvalue[0], "%s", f_Name.c_str());
	::sprintf(g_targetvalue[1], "%f", 89.75);
	::sprintf(g_targetvalue[2], "%f", Cube::random());
	::sprintf(g_targetvalue[3], "%f", Cube::random());
	::sprintf(g_targetvalue[4], "%f", Cube::random());

	int f_TargetID = g_SafeL[0]->Insert("target", (const char **)g_targetfield, (const char **)g_targetvalue, 5, false, false);

	for(int f_Count = 0; f_Count < 5; f_Count++)
		{
		free(g_targetfield[f_Count]);
		free(g_targetvalue[f_Count]);
		}

	for(int f_ElementID = 0; f_ElementID < m_Collection->m_vec_Element.size(); f_ElementID++)
		{
		  ////////////////
		 // element
		//
		char* g_elementfield[6];
		char* g_elementvalue[6];

		for(int f_Count = 0; f_Count < 6; f_Count++)
			{
			g_elementfield[f_Count] = (char*)malloc(sizeof(char) * 256);
			g_elementvalue[f_Count] = (char*)malloc(sizeof(char) * 256);
			}

		::sprintf(g_elementfield[0], "description");
		::sprintf(g_elementfield[1], "targetid");
		::sprintf(g_elementfield[2], "vert1x");
		::sprintf(g_elementfield[3], "vert1y");
		::sprintf(g_elementfield[4], "vert1z");
		::sprintf(g_elementfield[5], "volume");

		::sprintf(g_elementvalue[0], "%s", "Body Part");
		::sprintf(g_elementvalue[1], "%i", f_TargetID);
		::sprintf(g_elementvalue[2], "%f", 0.0f);
		::sprintf(g_elementvalue[3], "%f", 0.0f);
		::sprintf(g_elementvalue[4], "%f", 0.0f);
		::sprintf(g_elementvalue[5], "%f", m_Collection->m_vec_Element[f_ElementID]->m_Volume);

		g_SafeL[0]->Insert("element", (const char **)g_elementfield, (const char **)g_elementvalue, 6, false, false);

		for(int f_Count = 0; f_Count < 6; f_Count++)
			{
			free(g_elementfield[f_Count]);
			free(g_elementvalue[f_Count]);
			}
		}

	for(int f_ElementID2 = 0; f_ElementID2 < m_Collection->m_vec_Element.size(); f_ElementID2++)
		{
		for(int f_ElementID3 = 0; f_ElementID3 < m_Collection->m_vec_Element[f_ElementID2]->m_vec_Element.size(); f_ElementID3++)
			{
			  ////////////////
			 // elindex
			//
			char* g_elindexfield[3];
			char* g_elindexvalue[3];

			for(int f_Count = 0; f_Count < 3; f_Count++)
				{
				g_elindexfield[f_Count] = (char*)malloc(sizeof(char) * 256);
				g_elindexvalue[f_Count] = (char*)malloc(sizeof(char) * 256);
				}

			::sprintf(g_elindexfield[0], "targetid");
			::sprintf(g_elindexfield[1], "elementid");
			::sprintf(g_elindexfield[2], "resultid");

			::sprintf(g_elindexvalue[0], "%i", f_TargetID);
			::sprintf(g_elindexvalue[1], "%i", m_Collection->m_vec_Element[f_ElementID2]->m_Index);
			::sprintf(g_elindexvalue[2], "%i", m_Collection->m_vec_Element[f_ElementID2]->m_vec_Element[f_ElementID3]->m_Index);

			g_SafeL[0]->Insert("elindex", (const char **)g_elindexfield, (const char **)g_elindexvalue, 3, false, false);

			for(int f_Count = 0; f_Count < 3; f_Count++)
				{
				free(g_elindexfield[f_Count]);
				free(g_elindexvalue[f_Count]);
				}
			}
		}
}

void classTargetScript::ag_PrintScriptHeader(void)
{
	printf("|classTarget-Script Generated C Language|\n");
	printf("'''''''''''''''''''''''''''''''''''''''''\n");
	printf(".\n");
}

void classTargetScript::acPrint(void)
{
	ag_PrintScriptHeader();

	for(int f_XY = 0; f_XY < m_CollectionScript->m_vec_ElementScript.size(); f_XY++)
		{
		shared_ptr<classElementScript> f_ElementScript = m_CollectionScript->m_vec_ElementScript[f_XY];

		for(int f_Z = 0; f_Z < f_ElementScript->m_vec_Component.size(); f_Z++)
			{
			shared_ptr<classComponent> f_Component = f_ElementScript->m_vec_Component[f_Z];

			printf("%s\n", f_Component->m_String.c_str());
			}
		}
}

classTarget_JScript::classTarget_JScript()
{
	std::string f_ref_CurrentPath = "classTarget_JScript::classTarget_JScript";

	ag_StatusLive(f_ref_CurrentPath, "m_Collection");
	m_Collection = std::make_shared_reflect<classCollection>();

	m_Collection->acClear();

	m_vec_Function.clear();
	m_idx_vec_Function = 0;
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_Factor");
		m_Factor.push_back(std::make_shared_reflect<classFactor>());
		}

	ag_StatusLive(f_ref_CurrentPath, "m_Factor1");
	m_Factor.push_back(std::make_shared_reflect<classFactor>());

	m_InstaCountMap = 0;

	m_String = "";

	  ////////////////////////////////////
	 // LEGACY of Structured Analysis
	//
	//m_vec_Result.clear();
	//m_idx_vec_Result = 0;
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

classTarget_ESL_Script::classTarget_ESL_Script()
{
	std::string f_ref_CurrentPath = "classTarget_ESL_Script::classTarget_ESL_Script";

	ag_StatusLive(f_ref_CurrentPath, "m_Collection");
	m_Collection = std::make_shared_reflect<classCollection>();

	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_Factor");
		m_Factor.push_back(std::make_shared_reflect<classFactor>());
		}

	ag_StatusLive(f_ref_CurrentPath, "m_Factor1");
	m_Factor.push_back(std::make_shared_reflect<classFactor>());

	m_String = "";

	  ////////////////////////////////////
	 // LEGACY of Structured Analysis
	//
	//m_vec_Result.clear();
	//m_idx_vec_Result = 0;
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

classTarget_Ecom::classTarget_Ecom()
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::classTarget_Ecom";

	m_GlobalScope = true;

	ag_StatusLive(f_ref_CurrentPath, "m_Collection", true);
	m_Collection = std::make_shared_reflect<classCollection>();

	m_Collection->acClear();

	m_functionScan = true;
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();
	
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_Factor");
		m_Factor.push_back(std::make_shared_reflect<classFactor>());
		}

	ag_StatusLive(f_ref_CurrentPath, "m_Factor1");
	m_Factor.push_back(std::make_shared_reflect<classFactor>());

	m_String = "";

	  ////////////////////////////////////
	 // LEGACY of Structured Analysis
	//
	//m_vec_Result.clear();
	//m_idx_vec_Result = 0;
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();

#ifndef OSI_MEM_APP
	ac_Push(m_GRCinput, f_ref_CurrentPath + g_ref_Div + "m_GRCinput");
	ac_Push(m_GRMinput, f_ref_CurrentPath + g_ref_Div + "m_GRMinput");
	ac_Push(m_GRCcontrol, f_ref_CurrentPath + g_ref_Div + "m_GRCcontrol");
	ac_Push(m_GRMcontrol, f_ref_CurrentPath + g_ref_Div + "m_GRMcontrol");
	ac_Push(m_GRCoutput, f_ref_CurrentPath + g_ref_Div + "m_GRCoutput");
	ac_Push(m_GRMoutput, f_ref_CurrentPath + g_ref_Div + "m_GRMoutput");
	ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_LastType, f_ref_CurrentPath + g_ref_Div + "m_LastType");
	ac_Push(m_LastTypeII, f_ref_CurrentPath + g_ref_Div + "m_LastTypeII");
	ac_Push(m_LastTypeIII, f_ref_CurrentPath + g_ref_Div + "m_LastTypeIII");
	ac_Push(m_SchemaTop, f_ref_CurrentPath + g_ref_Div + "m_SchemaTop");
	ac_Push(m_idx_vec_Name, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Name");
	ac_Push(m_Mark, f_ref_CurrentPath + g_ref_Div + "m_Mark");
	ac_Push(m_functionScan, f_ref_CurrentPath + g_ref_Div + "m_functionScan");
	ac_Push(m_GlobalScope, f_ref_CurrentPath + g_ref_Div + "m_GlobalScope");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

classTarget_Ecom::classTarget_Ecom(bool f_Scope)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::classTarget_Ecom";

	m_GlobalScope = f_Scope;

	ag_StatusLive(f_ref_CurrentPath, "m_Collection");
	m_Collection = std::make_shared_reflect<classCollection>();

	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();
	
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_Factor");
		m_Factor.push_back(std::make_shared_reflect<classFactor>());
		}

	ag_StatusLive(f_ref_CurrentPath, "m_Factor1");
	m_Factor.push_back(std::make_shared_reflect<classFactor>());

	m_String = "";
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();

#ifndef OSI_MEM_APP
	ac_Push(m_GRCinput, f_ref_CurrentPath + g_ref_Div + "m_GRCinput");
	ac_Push(m_GRMinput, f_ref_CurrentPath + g_ref_Div + "m_GRMinput");
	ac_Push(m_GRCcontrol, f_ref_CurrentPath + g_ref_Div + "m_GRCcontrol");
	ac_Push(m_GRMcontrol, f_ref_CurrentPath + g_ref_Div + "m_GRMcontrol");
	ac_Push(m_GRCoutput, f_ref_CurrentPath + g_ref_Div + "m_GRCoutput");
	ac_Push(m_GRMoutput, f_ref_CurrentPath + g_ref_Div + "m_GRMoutput");
	ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_LastType, f_ref_CurrentPath + g_ref_Div + "m_LastType");
	ac_Push(m_LastTypeII, f_ref_CurrentPath + g_ref_Div + "m_LastTypeII");
	ac_Push(m_LastTypeIII, f_ref_CurrentPath + g_ref_Div + "m_LastTypeIII");
	ac_Push(m_SchemaTop, f_ref_CurrentPath + g_ref_Div + "m_SchemaTop");
	ac_Push(m_idx_vec_Name, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Name");
	ac_Push(m_Mark, f_ref_CurrentPath + g_ref_Div + "m_Mark");
	ac_Push(m_functionScan, f_ref_CurrentPath + g_ref_Div + "m_functionScan");
	ac_Push(m_GlobalScope, f_ref_CurrentPath + g_ref_Div + "m_GlobalScope");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

classTarget_Ecom::~classTarget_Ecom()
{
	m_Collection->acClear();
	
	m_Mark = 0.0;
	
	m_vec_Name.clear();
	m_idx_vec_Name = 0;
	
	m_SchemaTop = 0;
	m_SchemaRef.clear();

	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;

	m_Factor.clear();

	m_String = "";
	
	m_vec_CountLock.clear();
	m_idx_vec_CountLock = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();
}

void classTarget_JScript::acPowerDown(void)
{
	//...
}

void classTarget_Ecom::acPrepare_Lense(void)
{
	m_SchemaTop = 0;

	m_SchemaRef[0]->m_X = float(3.121113539F);
	m_SchemaRef[0]->m_Y = float(3.773584266F);
	m_SchemaRef[0]->m_Z = float(3.952468634F);
}

clsName::clsName(std::string f_Name, int f_BitCount, int f_INSTA, int f_index_Insta, int f_index_Function)
{
	std::string f_ref_CurrentPath = "clsName::clsName";

	m_Name = f_Name;
	m_BitCount = f_BitCount;
	m_INSTA_Type = f_INSTA;
	m_index_Insta = f_index_Insta;
	m_index_Function = f_index_Function;

	m_vec_Name.clear();
	m_idx_vec_Name = 0;

#ifndef OSI_MEM_APP
	ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
	ac_Push(m_BitCount, f_ref_CurrentPath + g_ref_Div + "m_BitCount");
	ac_Push(m_INSTA_Type, f_ref_CurrentPath + g_ref_Div + "m_INSTA_Type");
	ac_Push(m_index_Insta, f_ref_CurrentPath + g_ref_Div + "m_index_Insta");
	ac_Push(m_index_Function, f_ref_CurrentPath + g_ref_Div + "m_index_Function");
	ac_Push(m_idx_vec_Name, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Name");
#endif
}

classBridge::classBridge()
{
	std::string f_ref_CurrentPath = "classBridge::classBridge";

	m_vec_A.clear();
	m_vec_Type.clear();
	m_vec_LineType.clear();
	m_idx_vec = 0;

#ifndef OSI_MEM_APP
	ac_Push(m_vec_A, f_ref_CurrentPath + g_ref_Div + "m_vec_A");
	ac_Push(m_vec_Type, f_ref_CurrentPath + g_ref_Div + "m_vec_Type");
	ac_Push(m_vec_LineType, f_ref_CurrentPath + g_ref_Div + "m_vec_LineType");
	ac_Push(m_idx_vec, f_ref_CurrentPath + g_ref_Div + "m_idx_vec");
#endif
}

void classBridge::ac_add_Path(int f_A, int f_Type, int f_LineType)
{
	m_vec_A.push_back(f_A);
	m_vec_Type.push_back(f_Type);
	m_vec_LineType.push_back(f_LineType);
	m_idx_vec++;
}

classListI::classListI(int f_INSTA)
{
	std::string f_ref_CurrentPath = "classListI::classListI";

	m_vec_List.clear();
	m_idx_vec_List = 0;
	
	for(int f_Jet = 0; f_Jet < g_idx_vec_scrInputType; f_Jet++)
		{
		if(g_vec_scrInputType[f_Jet] == f_INSTA)
			{
			m_vec_List.push_back(g_vec_scrInputName[f_Jet]);
			m_idx_vec_List++;
			}
		}

#ifndef OSI_MEM_APP
	ac_Push(m_vec_List, f_ref_CurrentPath + g_ref_Div + "m_vec_List");
	ac_Push(m_idx_vec_List, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_List");
#endif
}

classListC::classListC(int f_INSTA)
{
	std::string f_ref_CurrentPath = "classListC::classListC";

	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < g_idx_vec_scrControlType; f_Jet++)
		{
		if(g_vec_scrControlType[f_Jet] == f_INSTA)
			{
			m_vec_List.push_back(g_vec_scrControlName[f_Jet]);
			m_idx_vec_List++;
			}
		}

#ifndef OSI_MEM_APP
	ac_Push(m_vec_List, f_ref_CurrentPath + g_ref_Div + "m_vec_List");
	ac_Push(m_idx_vec_List, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_List");
#endif
}

classListO::classListO(int f_INSTA)
{
	std::string f_ref_CurrentPath = "classListO::classListO";

	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < g_idx_vec_scrOutputType; f_Jet++)
		{
		if(g_vec_scrOutputType[f_Jet] == f_INSTA)
			{
			m_vec_List.push_back(g_vec_scrOutputName[f_Jet]);
			m_idx_vec_List++;
			}
		}

#ifndef OSI_MEM_APP
	ac_Push(m_vec_List, f_ref_CurrentPath + g_ref_Div + "m_vec_List");
	ac_Push(m_idx_vec_List, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_List");
#endif
}

classList_Target_Name::classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_JScript> f_Target)
{
	std::string f_ref_CurrentPath = "classList_Target_Name::classList_Target_Name";

	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < f_Target->m_idx_vec_Name; f_Jet++)
		{
		if(f_Target->m_vec_Name[f_Jet]->m_INSTA_Type == f_INSTA)
			{
			m_vec_List.push_back(f_Target->m_vec_Name[f_Jet]->m_Name);
			m_idx_vec_List++;
			}
		}

#ifndef OSI_MEM_APP
	ac_Push(m_vec_List, f_ref_CurrentPath + g_ref_Div + "m_vec_List");
	ac_Push(m_idx_vec_List, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_List");
#endif
}

classList_Target_Name::classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_ESL_Script> f_Target)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < f_Target->m_idx_vec_Name; f_Jet++)
		{
		if(f_Target->m_vec_Name[f_Jet]->m_INSTA_Type == f_INSTA)
			{
			m_vec_List.push_back(f_Target->m_vec_Name[f_Jet]->m_Name);
			m_idx_vec_List++;
			}
		}
}

classList_Target_Name::classList_Target_Name(int f_INSTA, std::shared_ptr<classTarget_Ecom> f_Target)
{
	m_vec_List.clear();
	m_idx_vec_List = 0;

	for(int f_Jet = 0; f_Jet < f_Target->m_idx_vec_Name; f_Jet++)
		{
		if(f_Target->m_vec_Name[f_Jet]->m_INSTA_Type == f_INSTA)
			{
			m_vec_List.push_back(f_Target->m_vec_Name[f_Jet]->m_Name);
			m_idx_vec_List++;
			}
		}
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_JScript::acMakeUnison(std::shared_ptr<classTarget_JScript> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acMakeUnison";

	if(f_INSTA == INSTA_TYPE_VAR_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared_reflect<classListI>(INSTA_TYPE_VAR_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(INSTA_TYPE_VAR_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_VAR_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared_reflect<classListC>(INSTA_TYPE_VAR_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared_reflect<classListO>(INSTA_TYPE_VAR_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_VAR_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared_reflect<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared_reflect<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared_reflect<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
		
	ag_StatusLive(f_ref_CurrentPath, "f_clsName");
	std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);

	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_Name;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_Ecom::acMakeUnison(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acMakeUnison";
		
	ag_StatusLive(f_ref_CurrentPath, "f_clsName");
	std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_Name;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_Ecom::acMakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function, int f_TypeGiven, bool f_FullDefinition)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acMakeUnisonType";

	std::string f_TypeAndNameResult;
	f_TypeAndNameResult.clear();

	bool isClassVar = false;

	if(f_FullDefinition == true)
		{
		if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1))
			{	//Sys
			f_TypeAndNameResult += "Sys%%";
			}
		else
			{
			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1))
				{	//Var
				f_TypeAndNameResult += "Var%%";
				}
			else
				{
				if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1))
					{	//ClassVar
					f_TypeAndNameResult += "ClassVar%%";

					isClassVar = true;
					}
				}
			}
		}

	if(isClassVar == false)
		{
		if(f_TypeGiven < 0)
			{
			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				f_TypeAndNameResult += "int&&";
				}
			else if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				f_TypeAndNameResult += "String&&";
				}
			}
		else
			{
			if(f_TypeGiven == ECN_VAR_FLOAT)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(f_TypeGiven == ECN_VAR_INT)
				{
				f_TypeAndNameResult += "int&&";
				}
			else if(f_TypeGiven == ECN_VAR_STRING)
				{
				f_TypeAndNameResult += "String&&";
				}
			}
		}
	else
		{
		std::string f_ClassVarType = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		f_TypeAndNameResult += f_ClassVarType + "&$";
		}

	f_TypeAndNameResult += f_Name + "%%";
		
	ag_StatusLive(f_ref_CurrentPath, "f_clsName");
	std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_TypeAndNameResult;
}

classLMap::classLMap(int f_IDX)
{
	//set Instance Index
	m_IDX = f_IDX;

	std::string f_ref_CurrentPath = "classLMap::classLMap";

#ifndef OSI_MEM_APP
	ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_SchemaMeasureIndex, f_ref_CurrentPath + g_ref_Div + "m_SchemaMeasureIndex");
	ac_Push(m_PushMeasureIndex, f_ref_CurrentPath + g_ref_Div + "m_PushMeasureIndex");
	ac_Push(m_CPS_Result, f_ref_CurrentPath + g_ref_Div + "m_CPS_Result");
	ac_Push(m_GRCinput, f_ref_CurrentPath + g_ref_Div + "m_GRCinput");
	ac_Push(m_GRMinput, f_ref_CurrentPath + g_ref_Div + "m_GRMinput");
	ac_Push(m_GRCcontrol, f_ref_CurrentPath + g_ref_Div + "m_GRCcontrol");
	ac_Push(m_GRMcontrol, f_ref_CurrentPath + g_ref_Div + "m_GRMcontrol");
	ac_Push(m_GRCoutput, f_ref_CurrentPath + g_ref_Div + "m_GRCoutput");
	ac_Push(m_GRMoutput, f_ref_CurrentPath + g_ref_Div + "m_GRMoutput");
	ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_idx_vec_Function, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Function");
	ac_Push(m_idx_vec_Achievement, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Achievement");
	ac_Push(m_idx_vec_CountLock, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_CountLock");
	ac_Push(m_idx_vec_Name, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Name");
	ac_Push(m_SchemaTop, f_ref_CurrentPath + g_ref_Div + "m_SchemaTop");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classLMap::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acRangeAD", (void(ecom_base::*)(void))&classLMap::acRangeAD);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&classLMap::acClear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClearAway", (void(ecom_base::*)(void))&classLMap::acClearAway);
#endif

	m_Mark = 0.0;

	ag_StatusLive(f_ref_CurrentPath, "m_LMap");
	m_LMap = std::make_shared_reflect<LMap>();

	acClear();

	m_SchemaTop = 0;
	m_SchemaRef.clear();
	g_ElementDivisor.clear();
	g_ElementDivisorInt.clear();

	m_Patched = false;
}

bool classLMap::acSaveLense(int f_OCSCP_ThreadIndex, int f_MeasureIndex, int f_DrawnIndex)
{
	if(((g_Result == false) || (f_DrawnIndex >= 2)) && (g_Wallet->m_vec_MainMode[m_IDX] == ECOIN_MODE_COMPRESS))
		{ //set result...
		g_Result = true;

#if 0
		char* f_Char = ag_ClearChar(512);
		sprintf(f_Char, "f_MeasureIndex %i == %i\n", f_MeasureIndex, (m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] + g_CountLM));
		winrt::hstring f_String = StrUsingStr(std::string(f_Char));
		OutputDebugString(f_String.c_str());
		delete f_Char;
#endif

		//save all thread schema when lucky
		if(f_MeasureIndex == (m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] + g_CountLM))
			{
			for(int f_Jet = 0; f_Jet < m_SchemaMeasureIndex.size(); f_Jet++)
				{
				m_SchemaMeasureIndex[f_Jet] = f_MeasureIndex;
				m_SaveSchemaRef[f_Jet]->m_X = m_SchemaRef[f_OCSCP_ThreadIndex]->m_X;
				m_SaveSchemaRef[f_Jet]->m_Y = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;
				m_SaveSchemaRef[f_Jet]->m_Z = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z;
				m_CPS_Result[f_Jet] = CPS_DRAW;
				}

			return true;
			}
		else if(f_MeasureIndex == m_LMap->m_vec_Measure.size())
			{
			for(int f_Jet = 0; f_Jet < m_SchemaMeasureIndex.size(); f_Jet++)
				{
				m_SchemaMeasureIndex[f_Jet] = f_MeasureIndex;
				m_SaveSchemaRef[f_Jet]->m_X = m_SchemaRef[f_OCSCP_ThreadIndex]->m_X;
				m_SaveSchemaRef[f_Jet]->m_Y = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;
				m_SaveSchemaRef[f_Jet]->m_Z = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z;
				m_CPS_Result[f_Jet] = CPS_DRAW;
				}

			return true;
			}
		else if(f_MeasureIndex > m_LMap->m_vec_Measure.size())
			{
			return false;
			}
		else
			{
			return false;
			}
		}

	return false;
}

bool classLMap::acSaveLensesSoft(int f_OCSCP_ThreadIndex, int f_MeasureIndex, int f_DrawnIndex)
{
	//save all thread schema when lucky
	if(f_DrawnIndex == -5)
		{
		m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] = f_MeasureIndex;
		m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_SchemaRef[f_OCSCP_ThreadIndex]->m_X;
		m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;
		m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z;

		return true;
		}
	else
		{
		if(f_MeasureIndex == (m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] + g_CountLM))
			{
			m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] = f_MeasureIndex;
			m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_SchemaRef[f_OCSCP_ThreadIndex]->m_X;
			m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;
			m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z;

			return true;
			}
		else if(f_MeasureIndex == m_LMap->m_vec_Measure.size() - 1)
			{
			m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] = f_MeasureIndex + 1;
			m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_SchemaRef[f_OCSCP_ThreadIndex]->m_X;
			m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;
			m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z;

			return true;
			}
		else if(f_MeasureIndex > m_LMap->m_vec_Measure.size())
			{
			return false;
			}
		else
			{
			return false;
			}
		}
}

bool classLMap::acPrepareLense(int f_OCSCP_ThreadIndex, int f_MeasureIndex)
{
	if(f_MeasureIndex == m_SchemaMeasureIndex[f_OCSCP_ThreadIndex])
		{
		m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X;
		m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y;
		m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z;

		return true;
		}

	return false;
}

void classLMap::acPushLensePos(int f_OCSCP_ThreadIndex)
{
	m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X;
	m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y;
	m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z;
	m_PushMeasureIndex[f_OCSCP_ThreadIndex] = m_SchemaMeasureIndex[f_OCSCP_ThreadIndex];
}

void classLMap::acPopLensePos(int f_OCSCP_ThreadIndex)
{
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_X;
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Y;
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Z;
	m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] = m_PushMeasureIndex[f_OCSCP_ThreadIndex];
}

void classLMap::acPrepareLense(int f_OCSCP_ThreadIndex)
{
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = float(3.121113539F);
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = float(3.773584266F);
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = float(3.952468634F);
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X = float(3.121113539F);
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y = float(3.773584266F);
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z = float(3.952468634F);
	m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] = 0;
	g_ElementDivisor[f_OCSCP_ThreadIndex] = 0;
	g_ElementDivisorInt[f_OCSCP_ThreadIndex] = 0;
}

bool classLMap::acPreCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex, int f_ElementMax)
{
	bool f_Success = true;

	int f_EndElementIndex = f_ElementMax;

	int f_MeasureIndex = 0;
	int f_EndMeasureIndex = g_CountLM * f_EndElementIndex;

	acPrepareLense(f_OCSCP_ThreadIndex);

	int f_DrawnElements = 0;
	int f_CorrectCount = 0;

	int f_StartDrawnElem = 0;
	int f_SrDrawnElem = 0;

	//main-flow - not print lowton
	for(int f_xx1 = 0; (f_xx1 < f_Collection->m_vec_Element.size()) && (f_Success == true); f_xx1++)
		{
		for(int f_yy1 = 0; (f_yy1 < g_CountLM) && (f_Success == true); f_yy1++)
			{
			f_MeasureIndex = (f_xx1 * g_CountLM) + f_yy1;

			int f_ElementIndex = m_LMap->m_vec_ElementID[f_MeasureIndex];

			std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementIndex];
			std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_MeasureIndex];

			f_DrawnElements = f_ElementIndex - f_StartDrawnElem;

			if(f_ElementIndex > f_SrDrawnElem)
				{
				if(acSaveLensesSoft(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
					{
					f_Element->m_OCSCP_Flag = false;
					f_Success = false;
					f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak();
#endif //add debug message
					}
				else
					{
					f_SrDrawnElem++;
					}
				}

			if(f_Success == true)
				{
				if(f_LMeasure->m_LMType == LMTYPE_MeasurementINTV1)
					{
					int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

					if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
						{
						f_Element->m_OCSCP_Flag = false;
						f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif //add debug message
						}
					else
						{
						f_CorrectCount++;
						}
					}
				else if(f_LMeasure->m_LMType == LMTYPE_MeasurementBLTV1)
					{
					bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

					if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
						{
						f_Element->m_OCSCP_Flag = false;
						f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif //add debug message
						}
					else
						{
						f_CorrectCount++;
						}
					}
				else
					{
#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak();
#endif //add debug message
					}
				}

			//win conditions! last mesurement.
			if((f_xx1 == f_Collection->m_vec_Element.size() - 1) && (f_yy1 == g_CountLM - 1))
				{													//rem: add one to measure index for being before
				if(acSaveLensesSoft(f_OCSCP_ThreadIndex, f_MeasureIndex + 1, -5) == false)
					{
					f_Success = false;
					f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak();
#endif //add debug message
					}
				else
					{
					f_SrDrawnElem++;

#ifdef ECOIN_DEBUG_BREAKS_PRES
					__debugbreak();
#endif //add debug message
					}
				}
			}
		}

	return f_Success;
}

int classLMap::ac_CalcLoadFinish(void)
{
	if(m_LoadFinish == true)
		{
		return 1;
		}
	else
		{
		int f_Count = 0;
		for(int f_Jet = 0; f_Jet < g_classLMap->m_CPS_Result.size(); f_Jet++)
			{
			if(g_classLMap->m_CPS_Result[f_Jet] == CPS_SCAN)
				{
				f_Count++;
				}
			}

		if(f_Count == g_SaveComplete_ThreadCount)
			{
			m_LoadFinish = true;

			return 1;
			}
		}

	return 0;
}

bool classLMap::ac_CalcScanReady(int f_Result)
{
	if(m_LoadFinish == false)
		{
		return f_Result;
		}

	//Calc Unkown Ready for Scanning
	int f_Count = 0;

	//Main Loop
	for(int f_Jet = 0; f_Jet < g_classLMap->m_CPS_Result.size(); f_Jet++)
		{
		if(g_classLMap->m_CPS_Result[f_Jet] == CPS_SCAN)
			{
			f_Count++;
			}
		}

	if(f_Count == g_SaveComplete_ThreadCount)
		{
		g_Result = false;

		return false; //Win Populus Fed! Force g_Result = 'False'
		}

	//Default 'false'
	return f_Result;
}

bool classLMap::acPatch_IntegerRanges(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex)
{
	std::string f_ref_CurrentPath = "classLMap::acPatch_IntegerRanges";

	int f_MeasureIndex = 0;

	if(acPrepareLense(f_OCSCP_ThreadIndex, f_MeasureIndex) == false)
		{
		return false;
		}

	int f_DrawnElements = 0;
	int f_CorrectCount = 0;
	int f_SrDrawnElem = 0;

	bool f_Usual_is_Insert = false;
	bool f_Last_is_Int = true;
	bool f_isLast_Insert = false;

	int f_CountHigh = 0;
	int m_OwnerEndRangeNext = 0;

#ifdef ECOIN_DEBUG_BREAKS
	int f_StartMeasureCount = m_LMap->m_vec_Measure.size();
#endif

	//main-flow - not print lowton
	for(int f_JetElemn = 0; f_JetElemn < m_LMap->m_vec_Measure.size(); f_JetElemn++)
		{
		f_MeasureIndex = f_JetElemn;

		int f_ElementID = m_LMap->m_vec_ElementID[f_MeasureIndex];

		if(f_ElementID >= f_Collection->m_vec_Element.size())
			{
			return true;
			}

		std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_MeasureIndex];

		std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementID];
			
		f_DrawnElements = f_MeasureIndex / g_CountLM;

		if(f_DrawnElements > f_SrDrawnElem)
			{
			if(acSaveLensesSoft(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
				{
				f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif //add debug message

				return false;
				}
			else
				{
				f_SrDrawnElem++;
				}
			}

		if(f_LMeasure->m_isOwnerID == true)
			{
			if(f_CountHigh <= 0)
				{
				int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, 0, 3, 0, 0, 0, f_OCSCP_ThreadIndex);

				f_LMeasure->m_MeasurementINTV1 = f_MeasureInteger;

				f_CorrectCount++;

				f_LMeasure->m_StartRange = 0;
				f_LMeasure->m_EndRange = 3;
				f_LMeasure->m_WeightRangetoStart = 0;
				f_LMeasure->m_isInsertID = false;
				f_LMeasure->m_isOwnerID = true;

				if(f_MeasureInteger == ECOIN_KEYTEXTTYPEB58_NUM)
					{
					m_OwnerEndRangeNext = 10;
					}
				else
					{
					m_OwnerEndRangeNext = 27;
					}

				f_Last_is_Int = true;
				f_isLast_Insert = false;
				f_Usual_is_Insert = false;

				f_CountHigh = 1;
				}
			else
				{
				int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, 0, m_OwnerEndRangeNext, 0, 0, 0, f_OCSCP_ThreadIndex);

				f_LMeasure->m_MeasurementINTV1 = f_MeasureInteger;

				f_CorrectCount++;

				f_LMeasure->m_StartRange = 0;
				f_LMeasure->m_EndRange = m_OwnerEndRangeNext;
				f_LMeasure->m_WeightRangetoStart = 0;
				f_LMeasure->m_isInsertID = false;
				f_LMeasure->m_isOwnerID = true;

				f_Last_is_Int = true;
				f_isLast_Insert = false;
				f_Usual_is_Insert = false;

				f_CountHigh = 0;
				}
			}
		else
			{
			if((f_LMeasure->m_isInsertID == false) && (f_Usual_is_Insert == false))
				{
				f_Last_is_Int = true;
				}
			else
				{
				if((f_LMeasure->m_isInsertID == true) && (f_Usual_is_Insert == false) && (f_isLast_Insert == false))
					{
					f_Last_is_Int = true;
					}
				}

			if(f_LMeasure->m_LMType == LMTYPE_MeasurementINTV1)
				{
				if(f_LMeasure->m_isInsertID == false)
					{
					if(f_Usual_is_Insert == false)
						{
						int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

						if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
							{
							f_Element->m_OCSCP_Flag = false;

#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif //add debug message
						
							return false;
							}
						else
							{
							f_CorrectCount++;
							}

						f_Last_is_Int = true;

						f_isLast_Insert = false;
						}
					else //INT Last is Int false (Usual is Insert true)
						{
						if(f_Last_is_Int == false)
							{
							int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, 0, 10, 0, -1, -1, f_OCSCP_ThreadIndex);

							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 10, 0, -1, -1, f_MeasureInteger);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							f_Last_is_Int = true;

							f_isLast_Insert = true;
							}
						else
							{
							bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, -2, -2, f_OCSCP_ThreadIndex);
						
							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(-1, -1, f_MeasureBoolean);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							if(f_MeasureBoolean == false)
								{
								if(f_LMeasure->m_MeasurementBLTV1 != false)
									{
									f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;

									f_JetElemn++;

									bool f_ScanUp = true;

									while(f_ScanUp == true)
										{
										if(f_JetElemn < m_LMap->m_vec_Measure.size())
											{
											std::shared_ptr<LMeasure> f_LF_Measure = m_LMap->m_vec_Measure[f_JetElemn];

											if(f_LF_Measure->m_isInsertID == true)
												{
												if((f_LF_Measure->m_LMType == 4) && (f_LF_Measure->m_MeasurementBLTV1 == false))
													{
													f_ScanUp = false;
													}
										
												m_LMap->ac_Delete_IDX(f_JetElemn);
												}
											else
												{
												f_ScanUp = false;
												}
											}
										else
											{
											f_ScanUp = false;
											}
										}

									f_JetElemn--;
									}

								f_Usual_is_Insert = false;
								}
							else
								{
								f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;
								}

							f_Last_is_Int = false;

							f_isLast_Insert = true;
							}
						}
					}
				else //InsertID true INTV1
					{
					if(f_Usual_is_Insert == false)
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak();
#endif //add debug message
						}
					else
						{
						if(f_Last_is_Int == false)
							{
							int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

							f_LMeasure->m_MeasurementINTV1 = f_MeasureInteger;

							f_LMeasure->m_isInsertID = true;

							f_CorrectCount++;

							f_Last_is_Int = true;

							f_isLast_Insert = true;
							}
						else
							{
							bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, -2, -2, f_OCSCP_ThreadIndex);
						
							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(-1, -1, f_MeasureBoolean);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							if(f_MeasureBoolean == false)
								{
								if(f_LMeasure->m_MeasurementBLTV1 != false)
									{
									f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;

									f_JetElemn++;

									bool f_ScanUp = true;

									while(f_ScanUp == true)
										{
										if(f_JetElemn < m_LMap->m_vec_Measure.size())
											{
											std::shared_ptr<LMeasure> f_LF_Measure = m_LMap->m_vec_Measure[f_JetElemn];

											if(f_LF_Measure->m_isInsertID == true)
												{
												if((f_LF_Measure->m_LMType == 4) && (f_LF_Measure->m_MeasurementBLTV1 == false))
													{
													f_ScanUp = false;
													}
										
												m_LMap->ac_Delete_IDX(f_JetElemn);
												}
											else
												{
												f_ScanUp = false;
												}
											}
										else
											{
											f_ScanUp = false;
											}
										}

									f_JetElemn--;
									}

								f_Usual_is_Insert = false;
								}
							else
								{
								f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;
								}

							f_Last_is_Int = false;

							f_isLast_Insert = true;
							}
						}
					}
				}
			else if(f_LMeasure->m_LMType == LMTYPE_MeasurementBLTV1)
				{
				if(f_LMeasure->m_isInsertID == false)
					{
					if(f_Usual_is_Insert == false)
						{
						bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);
						
						if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
							{
							f_Element->m_OCSCP_Flag = false;

#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak();
#endif //add debug message

							return false;
							}
						else
							{
							f_CorrectCount++;
							}

						f_Last_is_Int = false;

						f_isLast_Insert = false;
						}
					else //usual true insertid false BLT
						{
						if(f_Last_is_Int == true)
							{
							bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, -2, -2, f_OCSCP_ThreadIndex);
						
							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(-1, -1, f_MeasureBoolean);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							if(f_MeasureBoolean == false)
								{
								if(f_LMeasure->m_MeasurementBLTV1 != false)
									{
									f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;

									f_JetElemn++;

									bool f_ScanUp = true;

									while(f_ScanUp == true)
										{
										if(f_JetElemn < m_LMap->m_vec_Measure.size())
											{
											std::shared_ptr<LMeasure> f_LF_Measure = m_LMap->m_vec_Measure[f_JetElemn];

											if(f_LF_Measure->m_isInsertID == true)
												{
												if((f_LF_Measure->m_LMType == 4) && (f_LF_Measure->m_MeasurementBLTV1 == false))
													{
													f_ScanUp = false;
													}
										
												m_LMap->ac_Delete_IDX(f_JetElemn);
												}
											else
												{
												f_ScanUp = false;
												}
											}
										else
											{
											f_ScanUp = false;
											}
										}

									f_JetElemn--;
									}

								f_Usual_is_Insert = false;
								}
							else
								{
								f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;
								}

							f_Last_is_Int = false;

							f_isLast_Insert = true;
							}
						else
							{
							int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, 0, 9, 0, -1, -1, f_OCSCP_ThreadIndex);

							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 9, 0, -1, -1, f_MeasureInteger);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							f_Last_is_Int = true;

							f_isLast_Insert = true;
							}
						}
					}
				else //InsertID true as BLT
					{
					if(f_Usual_is_Insert == false)
						{
						bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

						f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;

						f_CorrectCount++;

						f_Usual_is_Insert = true;

						f_Last_is_Int = false;

						f_isLast_Insert = true;
						}
					else //usual true
						{
						if(f_Last_is_Int == true) //decider
							{
							bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

							f_CorrectCount++;

							if(f_MeasureBoolean == false)
								{
								if(f_LMeasure->m_MeasurementBLTV1 != false)
									{
									f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;

									f_JetElemn++;

									bool f_ScanUp = true;

									while(f_ScanUp == true)
										{
										if(f_JetElemn < m_LMap->m_vec_Measure.size())
											{
											std::shared_ptr<LMeasure> f_LF_Measure = m_LMap->m_vec_Measure[f_JetElemn];

											if(f_LF_Measure->m_isInsertID == true)
												{
												if((f_LF_Measure->m_LMType == 4) && (f_LF_Measure->m_MeasurementBLTV1 == false))
													{
													f_ScanUp = false;
													}
										
												m_LMap->ac_Delete_IDX(f_JetElemn);
												}
											else
												{
												f_ScanUp = false;
												}
											}
										else
											{
											f_ScanUp = false;
											}
										}

									f_JetElemn--;
									}

								f_Usual_is_Insert = false;
								}
							else
								{
								f_LMeasure->m_MeasurementBLTV1 = f_MeasureBoolean;
								}

							f_Last_is_Int = false;

							f_isLast_Insert = true;
							}
						else
							{
							int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, 0, 9, 0, -1, -1, f_OCSCP_ThreadIndex);

							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 9, 0, -1, -1, f_MeasureInteger);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							f_Last_is_Int = true;

							f_isLast_Insert = true;
							}
						}
					}
				}
			}
		}

#ifdef ECOIN_DEBUG_BREAKS
#if 1
	int f_FinishMeasureCount = m_LMap->m_vec_Measure.size();

	if(f_StartMeasureCount != f_FinishMeasureCount)
		{
		__debugbreak();
		}
#endif
#endif //add debug message

	return true;
}

classLMap::~classLMap()
{
	acClear();
}

void classLMap::acClearAway(void)
{
	m_String.clear();

	m_idx_vec_Function = 0;
	m_idx_vec_Achievement = 0;
	m_idx_vec_CountLock = 0;
	m_idx_vec_Name = 0;

	m_GRCinput.clear();
	m_GRMinput.clear();
	m_GRCcontrol.clear();
	m_GRMcontrol.clear();
	m_GRCoutput.clear();
	m_GRMoutput.clear();

	m_vec_Name.clear();
	m_SchemaRef.clear();
	m_Factor.clear();
	m_vec_CountLock.clear();
	m_vec_Achievement.clear();

	for(int f_Helly = 0; f_Helly < m_vec_Ecom.size(); f_Helly++)
		{
		m_vec_Ecom[f_Helly]->ac_Clear();
		}
	
	m_vec_Ecom.clear();
}

void classLMap::acClear(void)
{
	acClearAway();

	m_LMap->acClear();

	m_GlobalScope = false;
	m_Mark = 0.0f;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classLMap::acMakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_index_Insta, int f_index_Function, std::string f_LineString, int f_LineStartIndex, int f_TypeGiven, bool f_FullDefinition)
{
	std::string f_ref_CurrentPath = "classLMap::acMakeUnisonType";

	std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

	std::string f_TypeAndNameResult;
	f_TypeAndNameResult.clear();

	int f_ElementIndex = 0;

	bool isClassVar = false;

	if(f_FullDefinition == true)
		{
		char f_c = f_morfarray[f_LineStartIndex][0].at(0);

		if(f_c == 'S')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, true, f_ElementIndex); //has system

			f_TypeAndNameResult += "Sys%%";
			}
		else
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, false, f_ElementIndex); //has no system

			if(f_c == 'V')
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, true, f_ElementIndex); //has var

				f_TypeAndNameResult += "Var%%";
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, false, f_ElementIndex); //has var

				if(f_c == 'C')
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, true, f_ElementIndex); //has classvar

					f_TypeAndNameResult += "ClassVar%%";

					isClassVar = true;
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(f_StartAD, f_EndAD, false, f_ElementIndex); //has no system
					}
				}
			}
		}

	if(isClassVar == false)
		{
		if(f_TypeGiven < 0)
			{
			int f_VarType = agFind_VarType_from_Precision(agFind_Precision(f_morfarray[f_LineStartIndex + 1][0]));

			bool f_Spec_Three[3];

			if(f_VarType == ECN_VAR_FLOAT)
				{
				f_Spec_Three[0] = true;
				f_Spec_Three[1] = false;
				f_Spec_Three[2] = false;
				}
			else if(f_VarType == ECN_VAR_INT)
				{
				f_Spec_Three[0] = false;
				f_Spec_Three[1] = true;
				f_Spec_Three[2] = false;
				}
			else if(f_VarType == ECN_VAR_STRING)
				{
				f_Spec_Three[0] = false;
				f_Spec_Three[1] = false;
				f_Spec_Three[2] = true;
				}

			if(f_Spec_Three[0] == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

				f_TypeAndNameResult += "float&&";
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);

				if(f_Spec_Three[1] == true)
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

					f_TypeAndNameResult += "int&&";
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);

					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

					f_TypeAndNameResult += "String&&";
					}
				}
			}
		else
			{
			if(f_TypeGiven == ECN_VAR_FLOAT)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(f_TypeGiven == ECN_VAR_INT)
				{
				f_TypeAndNameResult += "int&&";
				}
			else
				{
				f_TypeAndNameResult += "String&&";
				}
			}
		}
	else
		{
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_TypeAndNameResult += ac_recordMeasurement(f_morfarray[f_LineStartIndex + 1][0], f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, 1);

		f_TypeAndNameResult += "&$";
		}

	f_TypeAndNameResult += f_Name + "%%";
		
	ag_StatusLive(f_ref_CurrentPath, "f_clsName");
	std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_TypeAndNameResult;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_ESL_Script::acMakeUnison(std::shared_ptr<classTarget_ESL_Script> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, shared_ptr<classElement> f_Element, int f_index_Insta, int f_index_Function)
{
	std::string f_ref_CurrentPath = "classTarget_ESL_Script::acMakeUnison";

	if(f_INSTA == ESL_INSTA_TYPE_VAR_DEF)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared_reflect<classListI>(ESL_INSTA_TYPE_VAR_DEF);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);

					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(ESL_INSTA_TYPE_VAR_DEF);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				ag_StatusLive(f_ref_CurrentPath, "f_clsName");
				std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Name");
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Control");
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared_reflect<classListC>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Output");
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared_reflect<classListO>(ESL_INSTA_TYPE_VAR_DEF);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Name");
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(ESL_INSTA_TYPE_VAR_DEF, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else if(f_INSTA == INSTA_TYPE_FUNC_CALL)
		{
		if(f_index_Function <= 100)
			{
			if(f_index_Insta > 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
				std::shared_ptr<classListI> f_VarCall_List = std::make_shared_reflect<classListI>(INSTA_TYPE_FUNC_CALL);
				
				int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
				return f_VarCall_List->m_vec_List[f_inputFactorFinger];
				}
			else
				{
				if(ac_takeMeasurementINTV1(f_Element, 0, 1, 0, 3, 1))
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];	
					}
				}
			}
		else if((f_index_Function > 100) &&
				(f_index_Function <= 500))
			{
			if(f_index_Insta > 0)
				{
				int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
				if(f_FingerFactorial >= 2)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListO> f_VarCall_List = std::make_shared_reflect<classListO>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 5);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				else
					{
					ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List");
					std::shared_ptr<classListC> f_VarCall_List = std::make_shared_reflect<classListC>(INSTA_TYPE_FUNC_CALL);
				
					int f_inputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List->m_idx_vec_List, 0, 3, 1);
				
					return f_VarCall_List->m_vec_List[f_inputFactorFinger];
					}
				}
			else
				{
				ag_StatusLive(f_ref_CurrentPath, "f_clsName");
				std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
				f_clsName->m_vec_Name.push_back(f_clsName);
				f_clsName->m_idx_vec_Name++;
				
				f_Target->m_vec_Name.push_back(f_clsName);
				f_Target->m_idx_vec_Name++;
				
				return f_Name;
				}
			}
		else if((f_index_Function > 500) &&
				(f_index_Function <= 750))
			{
			ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Name");
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else if(f_index_Function <= 1000)
			{
			if(f_index_Insta > 0)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Control");
				std::shared_ptr<classListC> f_VarCall_List_Control = std::make_shared_reflect<classListC>(INSTA_TYPE_FUNC_CALL);
			
				int f_controlFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Control->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Control->m_vec_List[f_controlFactorFinger];
				}
			else
				{
				ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Output");
				std::shared_ptr<classListO> f_VarCall_List_Output = std::make_shared_reflect<classListO>(INSTA_TYPE_FUNC_CALL);
			
				int f_outputFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Output->m_idx_vec_List, 0, 3, 7);
			
				return f_VarCall_List_Output->m_vec_List[f_outputFactorFinger];
				}
			}
		else
			{
			ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Name");
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
			
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 7);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		}
	else
		{
		int f_FingerFactorial = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
				
		if(f_FingerFactorial >= 2)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_VarCall_List_Name");
			std::shared_ptr<classList_Target_Name> f_VarCall_List_Name = std::make_shared_reflect<classList_Target_Name>(INSTA_TYPE_FUNC_CALL, f_Target);
		
			int f_nameFactorFinger = ac_takeMeasurementINTV1(f_Element, 0, f_VarCall_List_Name->m_idx_vec_List, 0, 3, 5);
		
			return f_VarCall_List_Name->m_vec_List[f_nameFactorFinger];
			}
		else
			{
			ag_StatusLive(f_ref_CurrentPath, "f_clsName");
			std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
			f_clsName->m_vec_Name.push_back(f_clsName);
			f_clsName->m_idx_vec_Name++;
			
			f_Target->m_vec_Name.push_back(f_clsName);
			f_Target->m_idx_vec_Name++;
			
			return f_Name;
			}
		}
		
	ag_StatusLive(f_ref_CurrentPath, "f_clsName");
	std::shared_ptr<clsName> f_clsName = std::make_shared_reflect<clsName>(f_Name, f_BitCount, f_INSTA, f_index_Insta, f_index_Function);
		
	f_clsName->m_vec_Name.push_back(f_clsName);
	f_clsName->m_idx_vec_Name++;
	
	f_Target->m_vec_Name.push_back(f_clsName);
	f_Target->m_idx_vec_Name++;
	
	return f_Name;
}

void classTarget_JScript::acGatherNames(void)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acGatherNames";

	//FROZEN//
	//AJAX bitcoin-office.com for gathering names
	//presents Math functions feel free to edit
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.abs(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	/*m_vec_Name[m_idx_vec_Name]->m_Code = function(f_IN)
		 {
	     var f_Input = f_IN;
		 var f_Output = 
	     }*/

	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.acos(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.acosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.asin(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.asinh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.atan(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.atan2(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.atanh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.acosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.cbrt(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.ceil(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.cos(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.atan2(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.atanh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.acosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.cbrt(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.ceil(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.cosh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.exp(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.floor(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.log(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.max(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.min(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.pow(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.random(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.round(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.sin(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.sinh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.sqrt(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.tan(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.tanh(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
	
	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	m_vec_Name.push_back(std::make_shared_reflect<clsName>("Math.trunc(", 0, INSTA_TYPE_FUNC_CALL, 0, 0));
	m_idx_vec_Name++;
}

std::string classTarget_JScript::ac_next_InputName(int f_Type)
{
	bool f_BoolScan = true;
	
	while((g_vec_scrInputType[m_GRCinput[f_Type]] != f_Type) && (f_BoolScan == true))
		{
		m_GRCinput[f_Type]++;
		
		if(m_GRCinput[f_Type] >= g_idx_vec_scrInputType)
			{
			f_BoolScan = false;
			}
		}
		
	m_GRMinput[f_Type] = m_GRCinput[f_Type];
	m_GRMinput[f_Type]++;
	
	if(f_BoolScan == true)
		{
		while((g_vec_scrInputType[m_GRMinput[f_Type]] != f_Type) && (f_BoolScan == true))
			{
			m_GRMinput[f_Type]++;
			
			if(m_GRMinput[f_Type] >= g_idx_vec_scrInputType)
				{
				f_BoolScan = false;
				}
			}
		}
	else
		{
		//throw;("Should not reach this point");
		}
		
	if(f_BoolScan == true)
		{
		return g_vec_scrInputName[m_GRCinput[f_Type]];
		}
	else
		{
		m_GRMinput[f_Type] = -5;
		return g_vec_scrInputName[m_GRCinput[f_Type]];
		}
}

std::string classTarget_JScript::ac_next_ControlName(int f_Type)
{
	bool f_BoolScan = true;
	
	while((g_vec_scrControlType[m_GRCcontrol[f_Type]] != f_Type) && (f_BoolScan == true))
		{
		m_GRCcontrol[f_Type]++;
		
		if(m_GRCcontrol[f_Type] >= g_idx_vec_scrControlType)
			{
			f_BoolScan = false;
			}
		}
		
	m_GRMcontrol[f_Type] = m_GRCcontrol[f_Type];
	m_GRMcontrol[f_Type]++;
	
	if(f_BoolScan == true)
		{
		while((g_vec_scrControlType[m_GRMcontrol[f_Type]] != f_Type) && (f_BoolScan == true))
			{
			m_GRMcontrol[f_Type]++;
			
			if(m_GRMcontrol[f_Type] >= g_idx_vec_scrControlType)
				{
				f_BoolScan = false;
				}
			}
		}
	else
		{
		for(;;)
			{
			//.
			}
		}
		
	if(f_BoolScan == true)
		{
		return g_vec_scrControlName[m_GRCcontrol[f_Type]];
		}
	else
		{
		m_GRMcontrol[f_Type] = -5;
		return g_vec_scrControlName[m_GRCcontrol[f_Type]];
		}
}

std::string classTarget_JScript::ac_next_OutputName(int f_Type)
{
	bool f_BoolScan = true;
	
	while((g_vec_scrOutputType[m_GRCoutput[f_Type]] != f_Type) && (f_BoolScan == true))
		{
		m_GRCoutput[f_Type]++;
		
		if(m_GRCoutput[f_Type] >= g_idx_vec_scrOutputType)
			{
			f_BoolScan = false;
			}
		}
		
	m_GRMoutput[f_Type] = m_GRCoutput[f_Type];
	m_GRMoutput[f_Type]++;
	
	if(f_BoolScan == true)
		{
		while((g_vec_scrOutputType[m_GRMoutput[f_Type]] != f_Type) && (f_BoolScan == true))
			{
			m_GRMoutput[f_Type]++;
			
			if(m_GRMoutput[f_Type] >= g_idx_vec_scrOutputType)
				{
				f_BoolScan = false;
				}
			}
		}
	else
		{
		for(;;)
			{
			//.
			}
		}
		
	if(f_BoolScan == true)
		{
		return g_vec_scrOutputName[m_GRCoutput[f_Type]];
		}
	else
		{
		m_GRMoutput[f_Type] = -5;
		return g_vec_scrOutputName[m_GRCoutput[f_Type]];
		}
}

void classTarget_JScript::acMerge_ICOtoName(void)
{
	std::string f_ref_CurrentPath = "m_vec_Name";

	//Input
	for(int f_XY = 0; f_XY < g_idx_vec_scrInputName; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
		m_vec_Name.push_back(std::make_shared_reflect<clsName>(g_vec_scrInputName[f_XY], 0, g_vec_scrInputType[f_XY], 0, 0));
		m_idx_vec_Name++;
		}

	//Control
	for(int f_XY = 0; f_XY < g_idx_vec_scrControlName; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
		m_vec_Name.push_back(std::make_shared_reflect<clsName>(g_vec_scrControlName[f_XY], 0, g_vec_scrControlType[f_XY], 0, 0));
		m_idx_vec_Name++;
		}
		
	//Output
	for(int f_XY = 0; f_XY < g_idx_vec_scrOutputName; f_XY++)
		{
		ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
		m_vec_Name.push_back(std::make_shared_reflect<clsName>(g_vec_scrOutputName[f_XY], 0, g_vec_scrOutputType[f_XY], 0, 0));
		m_idx_vec_Name++;
		}
}

void classTarget_JScript::acGatherICO_default(void)
{
	 //////////////////////////
	// 
	g_vec_scrInputName.push_back("ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrOutputName.push_back("");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("playSound");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
}

classBridgeResult::classBridgeResult()
{
	std::string f_ref_CurrentPath = "classBridgeResult::classBridgeResult";

	m_vec_LineIndex.clear();
	m_vec_Position_Equals.clear();
	m_vec_Position_Argument.clear();
	m_vec_String_Equal.clear();
	m_idx_vec = 0;

#ifndef OSI_MEM_APP
	ac_Push(m_vec_LineIndex, f_ref_CurrentPath + g_ref_Div + "m_vec_LineIndex");
	ac_Push(m_vec_Position_Equals, f_ref_CurrentPath + g_ref_Div + "m_vec_Position_Equals");
	ac_Push(m_vec_Position_Argument, f_ref_CurrentPath + g_ref_Div + "m_vec_Position_Argument");
	ac_Push(m_vec_String_Equal, f_ref_CurrentPath + g_ref_Div + "m_vec_String_Equal");
	ac_Push(m_idx_vec, f_ref_CurrentPath + g_ref_Div + "m_idx_vec");
#endif
}

classCodeLine::classCodeLine()
{
	m_vec_Code.clear();
	m_idx_vec_Code = 0;
}

std::shared_ptr<classBridgeResult> classTarget_JScript::acScan_Code_Bridges(std::shared_ptr<classFunction> f_Function, std::string f_String)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acScan_Code_Bridges";

	ag_StatusLive(f_ref_CurrentPath, "m_vec_Name");
	std::shared_ptr<classBridgeResult> f_Result = std::make_shared_reflect<classBridgeResult>();

	for(int f_XY = 0; f_XY < f_Function->m_idx_vec_CodeLineStorage; f_XY++)
		{
		std::shared_ptr<classCodeLine> f_Line = f_Function->m_vec_CodeLineStorage[f_XY];

		for(int f_I = 0; f_I < f_Line->m_idx_vec_Code; f_I++)
			{
			bool f_Found = true;

			for(int f_Grand = 0; (f_Grand < f_Line->m_vec_Code[f_I]->m_String.length()) && (f_Grand < f_String.length()); f_Grand++)
				{
				if(f_Line->m_vec_Code[f_I]->m_String.at(f_Grand) != f_String.at(f_Grand))
					{
					f_Found = false;
					}
				}
			
			if(f_Found == true)
				{
				f_Result->m_vec_LineIndex.push_back(f_XY);

				if(f_I == 0)
					{
					f_Result->m_vec_Position_Equals.push_back(f_I);
					f_Result->m_vec_Position_Argument.push_back(-5);
					f_Result->m_vec_String_Equal.push_back("E");
					}
				else
					{
					bool f_FunctionBool = false;
					int f_Index = 0;

					for(int f_Jet = 0; f_Jet < f_I; f_Jet++)
						{
						if(f_Line->m_vec_Code[f_Jet]->m_Type == INSTA_TYPE_FUNC_CALL)
							{
							f_FunctionBool = true;
							f_Index = f_Jet;
							}
						}

					if(f_FunctionBool == true)
						{
						f_Result->m_vec_Position_Equals.push_back(f_I);
						f_Result->m_vec_Position_Argument.push_back(f_I - f_Index);
						f_Result->m_vec_String_Equal.push_back("F");
						}
					else
						{
						f_Result->m_vec_Position_Equals.push_back(f_I);
						f_Result->m_vec_Position_Argument.push_back(-5);
						f_Result->m_vec_String_Equal.push_back(f_Line->m_vec_Code[0]->m_String);
						}
					}

				f_Result->m_idx_vec++;
				}
			}
		}

	return f_Result;
}

classTestArg::classTestArg()
{
	std::string f_ref_CurrentPath = "classTestArg::classTestArg";

	build_LastNameClose.clear();
	build_LastTypeClose.clear();
	f_indexInsta = 0;
	f_indexFunction = 0;

#ifndef OSI_MEM_APP
	ac_Push(build_LastNameClose, f_ref_CurrentPath + g_ref_Div + "m_vec_List");
	ac_Push(build_LastTypeClose, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_List");
	ac_Push(f_indexInsta, f_ref_CurrentPath + g_ref_Div + "f_indexInsta");
	ac_Push(f_indexFunction, f_ref_CurrentPath + g_ref_Div + "f_indexFunction");
#endif
}

std::shared_ptr<classMark> classTarget_JScript::acMark_TestICO(std::shared_ptr<classTarget_JScript> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acMark_TestICO";

	ag_StatusLive(f_ref_CurrentPath, "f_Mark");
	std::shared_ptr<classMark> f_Mark = std::make_shared_reflect<classMark>();
	
	ag_StatusLive(f_ref_CurrentPath, "f_Function");
	std::shared_ptr<classFunction> f_Function = m_vec_Function[0];
	
	int f_Run = 0;
	for(int f_XY = 0; f_XY < f_Function->m_idx_vec_CodeLineStorage; f_XY++)
		{
		std::shared_ptr<classCodeLine> f_Line = f_Function->m_vec_CodeLineStorage[f_XY];

		for(int f_I = 0; f_I < f_Line->m_idx_vec_Code; f_I++)
			{
			g_This = f_Line->m_vec_Code[f_I];
			g_ThisType = f_Line->m_vec_Code[f_I]->m_Type;
			g_ThisName = f_Line->m_vec_Code[f_I]->m_String;
			
			ag_StatusLive(f_ref_CurrentPath, "f_testARG");
			std::shared_ptr<classTestArg> f_testARG = std::make_shared_reflect<classTestArg>();

			f_testARG->f_indexInsta = f_I;
			f_testARG->f_indexFunction = f_Run + f_I;
			
			for(int f_L = f_I - 1; f_L >= 0; f_L--)
				{
				f_testARG->build_LastNameClose.push_back(f_Line->m_vec_Code[f_L]->m_String);
				f_testARG->build_LastTypeClose.push_back(f_Line->m_vec_Code[f_L]->m_Type);
				}
			
			f_testARG->build_LastNameClose.push_back("-5");
			f_testARG->build_LastTypeClose.push_back(-5);
			
			for(int f_A = 0; f_A < g_idx_vec_scrInputTestCuteFunc; f_A++)
				{
				std::shared_ptr<classAchievement> f_Achievement = g_vec_scrInputTestCuteFunc[f_A](f_Target, f_testARG);
			
				f_Mark->acIncrement(f_Achievement->m_Mark);
			
				if(f_Achievement->m_Success == true)
					{
					m_vec_Achievement.push_back(f_Achievement);
					m_idx_vec_Achievement++;
					}
				}
			}
			
		f_Run += f_Line->m_idx_vec_Code;
		}

	return f_Mark;
}

std::shared_ptr<classMark> classTarget_JScript::acMark_Bridges(void)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acMark_Bridges";

	ag_StatusLive(f_ref_CurrentPath, "f_Mark");
	std::shared_ptr<classMark> f_Mark = std::make_shared_reflect<classMark>();
	
	std::vector<std::string> f_vec_Scanlist;
	int f_idx_vec_Scanlist = 0;
	
	ag_StatusLive(f_ref_CurrentPath, "f_Function");
	std::shared_ptr<classFunction> f_Function = m_vec_Function[0];
	
	for(int f_Helly = 0; f_Helly < g_idx_vec_control_Bridge; f_Helly++)
		{
		std::shared_ptr<classBridge> f_Bridge = g_vec_control_Bridge[f_Helly];
		
		if(f_Bridge->m_vec_Type[0] == INSTA_TYPE_CONDITIONAL)
			{
			if((f_Bridge->m_vec_LineType[1] == LINE_TYPE_INPUT) &&
			   (f_Bridge->m_vec_LineType[2] == LINE_TYPE_INPUT))
				{
				//Scan, Search Wider			
				std::shared_ptr<classBridgeResult> f_BridgeResultB = acScan_Code_Bridges(f_Function, g_vec_scrInputName[f_Bridge->m_vec_A[1]]);
				std::shared_ptr<classBridgeResult> f_BridgeResultC = acScan_Code_Bridges(f_Function, g_vec_scrInputName[f_Bridge->m_vec_A[2]]);
				
				if(f_BridgeResultB->m_idx_vec == 0 &&
				   f_BridgeResultC->m_idx_vec == 0)
					{
					f_Mark->m_vec_Int[4] += 30;
					}
				else
					{
					if(f_BridgeResultB->m_idx_vec >= 1)
						{
						for(int f_Jet = 0; f_Jet < f_BridgeResultB->m_idx_vec; f_Jet++)
							{
							if(f_BridgeResultB->m_vec_Position_Equals[f_Jet] >= 1 ||
							   f_BridgeResultB->m_vec_Position_Argument[f_Jet] != -5)
								{
								f_Mark->m_vec_Int[6] += 3;
								
								f_vec_Scanlist.push_back(f_BridgeResultB->m_vec_String_Equal[f_Jet]);
								f_idx_vec_Scanlist++;
								}
							}
						}
					
					if(f_BridgeResultC->m_idx_vec >= 1)
						{
						for(int f_Jet = 0; f_Jet < f_BridgeResultC->m_idx_vec; f_Jet++)
							{
							if((f_BridgeResultC->m_vec_Position_Equals[f_Jet] >= 1) ||
							   (f_BridgeResultC->m_vec_Position_Argument[f_Jet] != -5))
								{
								f_Mark->m_vec_Int[6] += 3;
								
								f_vec_Scanlist.push_back(f_BridgeResultC->m_vec_String_Equal[f_Jet]);
								f_idx_vec_Scanlist++;
								}
							}
						}
					}
				}
			}
		}
		
	for(int f_Helly = 0; f_Helly < g_idx_vec_output_Bridge; f_Helly++)
		{
		std::shared_ptr<classBridge> f_Bridge = g_vec_output_Bridge[f_Helly];
		
		if(f_Bridge->m_vec_Type[0] == INSTA_TYPE_VAR_CALL)
			{
			if(f_Bridge->m_vec_LineType[1] == LINE_TYPE_INPUT &&
			   f_Bridge->m_vec_LineType[2] == LINE_TYPE_INPUT &&
			   f_Bridge->m_vec_LineType[3] == LINE_TYPE_INPUT)
				{
				//Scan, Search Wider
				std::shared_ptr<classBridgeResult> f_BridgeResultA = acScan_Code_Bridges(f_Function, g_vec_scrOutputName[f_Bridge->m_vec_A[0]]);
				
				if(f_BridgeResultA->m_idx_vec == 0)
					{
					f_Mark->m_vec_Int[4] += 15;
					}
				else
					{
					for(int f_Jet = 0; f_Jet < f_BridgeResultA->m_idx_vec; f_Jet++)
						{
						if((f_BridgeResultA->m_vec_Position_Equals[f_Jet] == 0) &&
						   (f_BridgeResultA->m_vec_Position_Argument[f_Jet] == -5))
							{
							f_Mark->m_vec_Int[5] += 3;
							}
						}
					}
					
				for(int f_XY = 0; f_XY < f_idx_vec_Scanlist; f_XY++)
					{
					std::shared_ptr<classBridgeResult> f_BridgeResult = acScan_Code_Bridges(f_Function, f_vec_Scanlist[f_XY]);
				
					if(f_BridgeResultA->m_idx_vec == 0)
						{
						f_Mark->m_vec_Int[4] += 15;
						}
					else
						{
						for(int f_Jet = 0; f_Jet < f_BridgeResultA->m_idx_vec; f_Jet++)
							{
							if((f_BridgeResultA->m_vec_Position_Equals[f_Jet] == 0) &&
							   (f_BridgeResultA->m_vec_Position_Argument[f_Jet] == -5))
								{
								f_Mark->m_vec_Int[5] += 3;
								}
							}
						}
					}
				}
			}
		if(f_Bridge->m_vec_A[1] == -5)
			{
			std::shared_ptr<classBridgeResult> f_ReturnBridgeResult = acScan_Code_Bridges(f_Function, g_vec_scrOutputName[f_Bridge->m_vec_A[0]]);
			
			if(f_ReturnBridgeResult->m_idx_vec == 0)
				{
				f_Mark->m_vec_Int[4] += 15;
				}
			else
				{
				for(int f_forge = 0; f_forge < f_ReturnBridgeResult->m_idx_vec; f_forge++)
					{
					if((f_ReturnBridgeResult->m_vec_Position_Equals[f_forge] == 0) &&
						(f_ReturnBridgeResult->m_vec_Position_Argument [f_forge] == -5))
						{
						f_Mark->m_vec_Int[6] += 5;
						}
					}
				}
			}
		}
		
	//console.log("f_Mark=" + JSON.stringify(f_Mark));

	return f_Mark;
}

void classTarget_JScript::acGatherICO_jscript_base(void)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acGatherICO_jscript_base";

	 //////////////////////////
	//
	g_vec_scrInputName.push_back("firstinput");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"number\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"1\" min=\"1\" max=\"5\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	
	g_vec_scrInputName.push_back("wwb_ecnbase_ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	
	g_vec_scrInputName.push_back("wwb_ecnbase_acMakeUnison");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("Ex");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputHTML.push_back("<input type=\"text\" name=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" id=\"" + "wwh_icobase_input_" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\" value=\"" + g_vec_scrInputName[g_idx_vec_scrInputName - 1] + "\">");
	g_idx_vec_scrInputHTML++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	ag_StatusLive(f_ref_CurrentPath, "f_ControlBridge1");
	std::shared_ptr<classBridge> f_ControlBridge1 = std::make_shared_reflect<classBridge>();
	
	f_ControlBridge1->ac_add_Path(g_idx_vec_scrControlName - 1, INSTA_TYPE_CONDITIONAL, LINE_TYPE_CONTROL);
	f_ControlBridge1->ac_add_Path(0, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_ControlBridge1->ac_add_Path(1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	
	g_vec_control_Bridge.push_back(f_ControlBridge1);
	g_idx_vec_control_Bridge++;
	
	g_vec_scrOutputName.push_back("f_Result");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	ag_StatusLive(f_ref_CurrentPath, "f_OutputBridge1");
	std::shared_ptr<classBridge> f_OutputBridge1 = std::make_shared_reflect<classBridge>();
	
	f_OutputBridge1->ac_add_Path(g_idx_vec_scrOutputName - 1, INSTA_TYPE_VAR_CALL, LINE_TYPE_OUTPUT);
	f_OutputBridge1->ac_add_Path(0, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_OutputBridge1->ac_add_Path(1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_INPUT);
	f_OutputBridge1->ac_add_Path(-5, INSTA_TYPE_VAR_CALL, LINE_TYPE_NORMAL);
	
	g_vec_output_Bridge.push_back(f_OutputBridge1);
	g_idx_vec_output_Bridge++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_base_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_navbar_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_content1_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_deploy_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_mission_output1).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("window.getElementById(wwb_mission_output2).innerHTML");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("return ");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
	
	ag_StatusLive(f_ref_CurrentPath, "f_OutputBridge2");
	std::shared_ptr<classBridge> f_OutputBridge2 = std::make_shared_reflect<classBridge>();
	
	f_OutputBridge2->ac_add_Path(g_idx_vec_scrOutputName - 1, INSTA_TYPE_FUNC_CALL, LINE_TYPE_OUTPUT);
	f_OutputBridge2->ac_add_Path(-5, INSTA_TYPE_VAR_DEF, LINE_TYPE_INPUT);
	
	g_vec_output_Bridge.push_back(f_OutputBridge2);
	g_idx_vec_output_Bridge++;
}

void classTarget_JScript::acGatherICO_html_base(void)
{
	 //////////////////////////
	// 
	g_vec_scrInputName.push_back("ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrOutputName.push_back("");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("playSound");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
}

void classTarget_JScript::acGatherICO_php_base(void)
{
	 //////////////////////////
	// 
	g_vec_scrInputName.push_back("ac_takeMeasurementINTV1");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_X");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Y");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrInputName.push_back("g_Z");
	g_idx_vec_scrInputName++;
	
	g_vec_scrInputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrInputType++;
	
	g_vec_scrControlName.push_back("Math.cos");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sin");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrControlName.push_back("Math.sqrt");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrControlType++;

	g_vec_scrControlName.push_back("if(");
	g_idx_vec_scrControlName++;
	
	g_vec_scrControlType.push_back(INSTA_TYPE_CONDITIONAL);
	g_idx_vec_scrControlType++;
	
	g_vec_scrOutputName.push_back("$output +=");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("write(");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_VAR_CALL);
	g_idx_vec_scrOutputType++;
	
	g_vec_scrOutputName.push_back("playSound");
	g_idx_vec_scrOutputName++;
	
	g_vec_scrOutputType.push_back(INSTA_TYPE_FUNC_CALL);
	g_idx_vec_scrOutputType++;
}

void classTarget_JScript::acGen_SuperName(std::string f_GeoName)
{
	//m_vec_Name.push_back("wwb_" + f_GeoName);
	//m_idx_vec_Name++;
}

classFactor::classFactor()
{
	std::string f_ref_CurrentPath = "classFactor::classFactor";

	m_Use = 0;

#ifndef OSI_MEM_APP
	ac_Push(m_Use, f_ref_CurrentPath + g_ref_Div + "m_Use");
#endif
}

void classTarget_JScript::acResetFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use = 0;
}

void classTarget_JScript::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_ESL_Script::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_JScript::acResetFactors(int f_Type)
{
	for(int f_XY = 0; f_XY < INSTA_TYPE_COUNT; f_XY++)
		{
		m_Factor[f_XY]->m_Use = 0;
		}
}

void classTarget_JScript::acResetLine(void)
{
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_DATA]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;
}

void classTarget_Ecom::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classLMap::acDecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_Ecom::acResetLine(void)
{
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_DATA]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;
}

void classLMap::acResetLine(void)
{
#if 0
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_DATA]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
#endif
}

bool classTarget_JScript::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element)
{
	int f_Finger = ac_takeMeasurementINTV1(f_Element, 1, f_ProbabilityExt, 0, 3, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}
}

bool classTarget_Ecom::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	int f_Finger = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1, f_ProbabilityExt, 0, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}
}

void classTarget_ESL_Script::acResetLine(void)
{
	m_Factor[INSTA_TYPE_VAR_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use = 0;
	m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use = 0;
	m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use = 0;
	m_Factor[INSTA_TYPE_VAR_CALL]->m_Use = 0;
	m_LastType = -5;
	m_LastTypeII = -5;
	m_LastTypeIII = -5;
}

bool classTarget_ESL_Script::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, shared_ptr<classElement> f_Element)
{
	int f_Finger = ac_takeMeasurementINTV1(f_Element, 1, f_ProbabilityExt, 0, 3, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}
}

bool classTarget_ESL_Script::acFactorStrengthVar(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element)
{
	return true;
}

bool classLMap::acFactorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	/*int f_Finger = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1, f_ProbabilityExt, 3, 3);

	if(f_Finger >= f_AboveLine)
		{
		return f_Answer;
		}
	else
		{
		if(f_Answer == true)
			{
			return false;
			}
		else
			{
			return true;
			}
		}*/
	//throw;;
}

bool classTarget_Ecom::acFactorStrengthVar(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	return ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 0);
}

bool classTarget_Ecom::acFactorStrengthVarString(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	return ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 0);
}

bool classLMap::acRecordStrengthVar(int f_Type, std::string f_LineString, float f_RecordResult, int f_ElementID, bool f_isRandom)
{
	std::string f_ref_CurrentPath = "classLMap::acRecordStrengthVar";

	switch(f_Type)
		{
		case VAR_DEF_TYPE_ZERO_TO_ONE:
			{
			if(f_isRandom == false)
				{
				if((f_RecordResult >= 0.0) && (f_RecordResult <= 1.0)) //hmmm is this nessassary, experiment
					{
					//###Position###
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_ONE_TO_HUNDRED:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 100.0 && f_RecordResult > 1.0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 5000.0 && f_RecordResult > 100.0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 50000000.0 && f_RecordResult > 5000.0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_RANDOM:
			{
			if(f_isRandom == true)
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_SYSTEM:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

#if 0
		case VAR_DEF_TYPE_VARCALL:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
#endif
		}

	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	//generate lense recording
	ag_StatusLive(f_ref_CurrentPath, "f_Measure");
	shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, false);

	//save
	m_LMap->m_vec_Measure.push_back(f_Measure);

	return false;
}

bool classLMap::acRecordStrengthVar(int f_Type, std::string f_LineString, int f_RecordResult, int f_ElementID, bool f_isRandom)
{
	std::string f_ref_CurrentPath = "classLMap::acRecordStrengthVar";

	switch(f_Type)
		{
		case VAR_DEF_TYPE_ZERO_TO_ONE:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 1 && f_RecordResult >= 0)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_ONE_TO_HUNDRED:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 100 && f_RecordResult > 1)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 5000 && f_RecordResult > 100)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION:
			{
			if(f_isRandom == false)
				{
				if(f_RecordResult <= 50000000 && f_RecordResult > 5000)
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case VAR_DEF_TYPE_RANDOM:
			{
			if(f_isRandom == true)
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_SYSTEM:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

#if 0
		case VAR_DEF_TYPE_VARCALL:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
#endif
		}

	return false;
}

bool classLMap::acRecordStrengthVarString(int f_Type, std::string f_LineString, std::string f_RecordResult, int f_ElementID)
{
	std::string f_ref_CurrentPath = "classLMap::acRecordStrengthVarString";

	switch(f_Type)
		{
		case VAR_DEF_TYPE_ZERO_TO_ONE:
			{
			if((f_RecordResult.length() >= 0) && (f_RecordResult.length() < (1 * ECOIN_DATA_CHUNK_LENGTH_COUNT)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_ONE_TO_HUNDRED:
			{
			if((f_RecordResult.length() >= (1 * ECOIN_DATA_CHUNK_LENGTH_COUNT)) && (f_RecordResult.length() <= (5 * ECOIN_DATA_CHUNK_LENGTH_COUNT)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND:
			{
			if((f_RecordResult.length() > (5 * ECOIN_DATA_CHUNK_LENGTH_COUNT)) && (f_RecordResult.length() <= (10 * ECOIN_DATA_CHUNK_LENGTH_COUNT)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION:
			{
			if((f_RecordResult.length() > (10 * ECOIN_DATA_CHUNK_LENGTH_COUNT)) || (f_RecordResult.length() <= (15 * ECOIN_DATA_CHUNK_LENGTH_COUNT)))
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		 case VAR_DEF_TYPE_SYSTEM:
			{
			std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

			if(f_morf[0][0].at(0) == 'S')
				{
				//reference element index
				m_LMap->m_vec_ElementID.push_back(f_ElementID);

				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

#if 0
		case VAR_DEF_TYPE_VARCALL:
			{
			if(f_isRandom == false)
				{
				std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

				if(f_morf[0][0].at(0) == 'S')
					{
					//reference element index
					m_LMap->m_vec_ElementID.push_back(f_ElementID);

					//generate lense recording
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 2, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
#endif

		}

	return false;
}

bool classLMap::acRecordStrength(int f_Type, std::string f_LineString, int f_ElementID)
{
	std::string f_ref_CurrentPath = "classLMap::acRecordStrength";

	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	switch(f_Type)
		{
		case ESL_INSTA_TYPE_VAR_DEF:
			{
			std::string f_Var_First_TypeName = ac_ext_eslLine_morf_array(f_LineString)[0][0];

			if(f_Var_First_TypeName.compare("Var"))
				{
				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case ESL_INSTA_TYPE_SYS_DEF:
			{
			std::string f_Var_First_TypeName = ac_ext_eslLine_morf_array(f_LineString)[0][0];

			if(f_Var_First_TypeName.compare("Sys") == 0)
				{
				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
			}break;

		case ESL_INSTA_TYPE_FUNC_DEF:
			{
#if 0
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();
			std::string f_Var_First_TypeName = ac_ext_eslLine_morf_array(f_LineString)[0][0];

			if(f_Var_First_TypeName.compare("Var") == 0)
				{

				}
			else if(f_Var_First_TypeName.compare("Sys") == 0)
				{

				}
			else if(f_Var_First_TypeName.compare("Sys") == 0)
				{

				}
			if((f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_DEF_MORF_COUNT) && (f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_DEF_MORF_COUNT +))
				{
				//generate lense recording
				ag_StatusLive(f_ref_CurrentPath, "f_Measure");
				shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

				//save
				m_LMap->m_vec_Measure.push_back(f_Measure);

				//return
				return true;
				}
#else
			return true;
#endif
			}break;

		case ESL_INSTA_TYPE_FUNC_CALL:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT)
				{
				char f_Var_Second_Char = ac_ext_eslLine_morf_array(f_LineString)[6][1].at(1);

				if(f_Var_Second_Char == '*')
					{
					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_CONDITIONAL:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size >= ESL_INSTA_TYPE_FUNC_CALL_MORF_COUNT)
				{
				char f_Var_Second_Char = ac_ext_eslLine_morf_array(f_LineString)[6][1].at(1);

				if(f_Var_Second_Char == '^')
					{
					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_LOOP_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size == ESL_INSTA_TYPE_LOOP_DEF_MORF_COUNT)
				{
				if((ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("For") == 0) || (ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("for") == 0))
					{
					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_CLASS_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size == ESL_INSTA_TYPE_CLASS_DEF_MORF_COUNT)
				{
				if((ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("ClassStart") == 0) || (ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("Class") == 0) || (ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("ClassDef") == 0))
					{
					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;

		case ESL_INSTA_TYPE_CLASSVAR_DEF:
			{
			int f_Var_Code_Size = ac_ext_eslLine_morf_array(f_LineString).size();

			if(f_Var_Code_Size >= ESL_INSTA_TYPE_CLASS_VAR_MORF_COUNT)
				{
				if(ac_ext_eslLine_morf_array(f_LineString)[0][0].compare("ClassVar") == 0)
					{
					//generate lense recording
					ag_StatusLive(f_ref_CurrentPath, "f_Measure");
					shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, true);

					//save
					m_LMap->m_vec_Measure.push_back(f_Measure);

					//return
					return true;
					}
				}
			}break;
		}

	//generate lense recording
	ag_StatusLive(f_ref_CurrentPath, "f_Measure");
	shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(2, 0, false);

	//save
	m_LMap->m_vec_Measure.push_back(f_Measure);

	//return
	return false;
}

int classLMap::acRecordLine(std::string f_LineString)
{
	std::vector<std::vector<std::string>> f_morf = ac_ext_eslLine_morf_array(f_LineString);

	if(f_morf.size() <= 4)
		{
		std::string f_Var_Code_Type_0 = f_morf[0][0];

		char f_Char_0 = f_Var_Code_Type_0.at(0);

		//first absolute knowns
		if((f_Char_0 == 'R') || (f_Char_0 == 'r'))
			{
			return ESL_INSTA_TYPE_RETURN;
			}
		else if(f_Char_0 == 'T')
			{
			return ESL_INSTA_TYPE_TEMPLATE;
			}

		bool f_Sock_0 = false;

		if(f_Char_0 == 'V')
			{
			f_Sock_0 = true;
			}
		else if(f_Char_0 == 'S')
			{
			f_Sock_0 = true;
			}
		else if(f_Char_0 == 'C')
			{
			f_Sock_0 = true;
			}

		if(f_Sock_0 == false) //no cvar
			{
			if ((f_Var_Code_Type_0.compare("Fcn") == 0) ||
				(f_Var_Code_Type_0.compare("Func") == 0) ||
				(f_Var_Code_Type_0.compare("Call") == 0) ||
				(f_Var_Code_Type_0.compare("FunctionCall") == 0))
				{
				return ESL_INSTA_TYPE_FUNC_CALL;
				}

			if ((f_Var_Code_Type_0.compare("Fus") == 0) ||
				(f_Var_Code_Type_0.compare("Def") == 0) ||
				(f_Var_Code_Type_0.compare("FuncDef") == 0) ||
				(f_Var_Code_Type_0.compare("Function") == 0) ||
				(f_Var_Code_Type_0.compare("FuncStart") == 0) ||
				(f_Var_Code_Type_0.compare("FunctionStart") == 0))
				{
				return ESL_INSTA_TYPE_FUNC_DEF;
				}

			if ((f_Var_Code_Type_0.compare("ClassStart") == 0) || (f_Var_Code_Type_0.compare("Class") == 0) || (f_Var_Code_Type_0.compare("ClassDef") == 0))
				{
				return ESL_INSTA_TYPE_CLASS_DEF; //CLASS_DEF
				}
				
			if ((f_Var_Code_Type_0.compare("Ifs") == 0) ||
				(f_Var_Code_Type_0.compare("Cond") == 0) ||
				(f_Var_Code_Type_0.compare("Conditional") == 0))
				{
				return ESL_INSTA_TYPE_CONDITIONAL;
				}

			if (f_Var_Code_Type_0.compare("ClassVar") == 0)
				{
				return ESL_INSTA_TYPE_CLASSVAR_DEF; //CLASS_DEF
				}

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif
			}
		else
			{
			//verify variable definition
			if(f_Char_0 == 'V')
				{
				return ESL_INSTA_TYPE_VAR_DEF;
				}
			else if(f_Char_0 == 'S')
				{
				return ESL_INSTA_TYPE_SYS_DEF;
				}
			else if(f_Char_0 == 'C')
				{
				return ESL_INSTA_TYPE_CLASSVAR_DEF;
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif
			}
		}
	else
		{
		std::string f_Var_Code_Type_0 = f_morf[0][0];
		std::string f_Var_Code_Type_3 = f_morf[3][0];
		std::string f_Var_Code_Value_3 = f_morf[3][1];

		char f_Char_0 = f_Var_Code_Type_0.at(0);
		char f_Char_3 = f_Var_Code_Type_3.at(0);

		bool f_Sock_0 = false;
		bool f_Value_3 = false;

		//quick selewctions
		if((f_Char_0 == 'R') || (f_Char_0 == 'r'))
			{
			return ESL_INSTA_TYPE_RETURN;
			}
		else if(f_Char_0 == 'T')
			{
			return ESL_INSTA_TYPE_TEMPLATE;
			}

		//detect socket LHS
		if(f_Char_0 == 'V')
			{
			f_Sock_0 = true;
			}
		else if(f_Char_0 == 'S')
			{
			f_Sock_0 = true;
			}
		else if(f_Char_0 == 'C')
			{
			f_Sock_0 = true;
			}

		if(f_Sock_0 == true)
			{
			//detect no value assign in Code[3]
			if(ag_Value_Check(f_Var_Code_Value_3))
				{
				f_Value_3 = true;
				}

			if(f_Value_3 == true)
				{
				std::string f_Var_Code_Typing_4 = f_morf[4][0];

				char f_Char_4 = f_Var_Code_Typing_4.at(0);

				//absolute knowns
				if (f_Char_4 == 'O')
					{
					return ESL_INSTA_TYPE_OPER;
					}

				if ((f_Var_Code_Typing_4.compare("Fcn") == 0) ||
					(f_Var_Code_Typing_4.compare("Func") == 0) ||
					(f_Var_Code_Typing_4.compare("Call") == 0) ||
					(f_Var_Code_Typing_4.compare("FunctionCall") == 0))
					{
					return ESL_INSTA_TYPE_FUNC_CALL;
					}

				//verify function definition
				if ((f_Var_Code_Typing_4.compare("Fus") == 0) ||
					(f_Var_Code_Typing_4.compare("Def") == 0) ||
					(f_Var_Code_Typing_4.compare("FuncDef") == 0) ||
					(f_Var_Code_Typing_4.compare("Function") == 0) ||
					(f_Var_Code_Typing_4.compare("FuncStart") == 0) ||
					(f_Var_Code_Typing_4.compare("FunctionStart") == 0))
					{
					return ESL_INSTA_TYPE_FUNC_DEF; //FUNC_DEF
					}

				if ((f_Var_Code_Typing_4.compare("ClassStart") == 0) || (f_Var_Code_Typing_4.compare("Class") == 0) || (f_Var_Code_Typing_4.compare("ClassDef") == 0))
					{
					return ESL_INSTA_TYPE_CLASS_DEF; //CLASS_DEF
					}
				
				if ((f_Var_Code_Typing_4.compare("Ifs") == 0) ||
					(f_Var_Code_Typing_4.compare("Cond") == 0) ||
					(f_Var_Code_Typing_4.compare("Conditional") == 0))
					{
					return ESL_INSTA_TYPE_CONDITIONAL;
					}

				if (f_Var_Code_Typing_4.compare("ClassVar") == 0)
					{
					return ESL_INSTA_TYPE_CLASSVAR_DEF; //CLASS_DEF
					}

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif
				}
			else
				{
				if(f_morf.size() < 5)
					{
					if(f_Char_0 == 'V')
						{
						return ESL_INSTA_TYPE_VAR_DEF;
						}
					else if(f_Char_0 == 'S')
						{
						return ESL_INSTA_TYPE_SYS_DEF;
						}
					else if(f_Char_0 == 'C')
						{
						return ESL_INSTA_TYPE_CLASSVAR_DEF;
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak();
						}
#endif
					}
				else
					{
					if(f_Char_3 == 'O')
						{
						return ESL_INSTA_TYPE_OPER;
						}

					if ((f_Var_Code_Type_3.compare("Fcn") == 0) ||
						(f_Var_Code_Type_3.compare("Func") == 0) ||
						(f_Var_Code_Type_3.compare("Call") == 0) ||
						(f_Var_Code_Type_3.compare("FunctionCall") == 0))
						{
						return ESL_INSTA_TYPE_FUNC_CALL;
						}

					//verify function definition
					if ((f_Var_Code_Type_3.compare("Fus") == 0) ||
						(f_Var_Code_Type_3.compare("Def") == 0) ||
						(f_Var_Code_Type_3.compare("FuncDef") == 0) ||
						(f_Var_Code_Type_3.compare("Function") == 0) ||
						(f_Var_Code_Type_3.compare("FuncStart") == 0) ||
						(f_Var_Code_Type_3.compare("FunctionStart") == 0))
						{
						return ESL_INSTA_TYPE_FUNC_DEF; //FUNC_DEF
						}

					if ((f_Var_Code_Type_3.compare("ClassStart") == 0) || (f_Var_Code_Type_3.compare("Class") == 0) || (f_Var_Code_Type_3.compare("ClassDef") == 0))
						{
						return ESL_INSTA_TYPE_CLASS_DEF; //CLASS_DEF
						}
				
					if ((f_Var_Code_Type_3.compare("Ifs") == 0) ||
						(f_Var_Code_Type_3.compare("Cond") == 0) ||
						(f_Var_Code_Type_3.compare("Conditional") == 0))
						{
						return ESL_INSTA_TYPE_CONDITIONAL;
						}

					if (f_Var_Code_Type_3.compare("ClassVar") == 0)
						{
						return ESL_INSTA_TYPE_CLASSVAR_DEF; //CLASS_DEF
						}

					if(f_Char_0 == 'V')
						{
						return ESL_INSTA_TYPE_VAR_DEF;
						}
					else if(f_Char_0 == 'S')
						{
						return ESL_INSTA_TYPE_SYS_DEF;
						}
					else if(f_Char_0 == 'C')
						{
						return ESL_INSTA_TYPE_CLASSVAR_DEF;
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak();
						}
#endif
					}
				}
			}
		else
			{
			if ((f_Var_Code_Type_0.compare("Fcn") == 0) ||
				(f_Var_Code_Type_0.compare("Func") == 0) ||
				(f_Var_Code_Type_0.compare("Call") == 0) ||
				(f_Var_Code_Type_0.compare("FunctionCall") == 0))
				{
				return ESL_INSTA_TYPE_FUNC_CALL;
				}

			if ((f_Var_Code_Type_0.compare("Fus") == 0) ||
				(f_Var_Code_Type_0.compare("Def") == 0) ||
				(f_Var_Code_Type_0.compare("FuncDef") == 0) ||
				(f_Var_Code_Type_0.compare("Function") == 0) ||
				(f_Var_Code_Type_0.compare("FuncStart") == 0) ||
				(f_Var_Code_Type_0.compare("FunctionStart") == 0))
				{
				return ESL_INSTA_TYPE_FUNC_DEF;
				}

			if (f_Var_Code_Type_0.compare("ClassVar") == 0)
				{
				return ESL_INSTA_TYPE_CLASSVAR_DEF;
				}

			if((f_Var_Code_Type_0.compare("ClassStart") == 0) || (f_Var_Code_Type_0.compare("Class") == 0) || (f_Var_Code_Type_0.compare("ClassDef") == 0))
				{
				return ESL_INSTA_TYPE_CLASS_DEF;
				}

			if ((f_Var_Code_Type_0.compare("For") == 0) ||
				(f_Var_Code_Type_0.compare("for") == 0))
				{
				return ESL_INSTA_TYPE_LOOP_DEF;
				}

#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif
			}
		}
	
#ifdef ECOIN_DEBUG_BREAKS
	__debugbreak();
#endif

	return ESL_INSTA_TYPE_VAR_DEF;
}

bool classTarget_JScript::acFactorStrength(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acFactorStrength";

	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_searchInsta");
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_searchInsta");
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{
			if(acFactorise(true, 4, 5, f_Element) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{
		if(acFactorise(true, 5, 6, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
		
	return true;
}

bool classTarget_ESL_Script::acFactorStrength(int f_Type, std::shared_ptr<classFunction> f_Function, shared_ptr<classElement> f_Element)
{
	std::string f_ref_CurrentPath = "classTarget_ESL_Script::acFactorStrength";

	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				ag_StatusLive(f_ref_CurrentPath, "f_searchInsta");
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_searchInsta");
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{
			if(acFactorise(true, 4, 5, f_Element) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{	
		if(acFactorise(true, 5, 6, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_Element) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
		
	return true;
}

bool classTarget_Ecom::acFactorStrength(int f_Type, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
#if 0
	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			/*for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}*/
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{			
			if(acFactorise(true, 4, 5, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{	
		if(acFactorise(true, 5, 6, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
#endif

	return ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 2);
}

bool classTarget_Ecom::acFactorStrengthAff(int f_Type, std::shared_ptr<classFunction> f_Function, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acFactorStrengthAff";

	m_LastTypeII = m_LastType;
	m_LastTypeIII = m_LastTypeII;
	
	if(f_Type == INSTA_TYPE_VAR_DEF)
		{
		if(m_Factor[INSTA_TYPE_VAR_DEF]->m_Use > 0)
			{
			return false;
			}
		
		if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_VAR_CALL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_LOOP_DEF]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_DATA]->m_Use > 0)
			{
			return false;
			}
			
		if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use > 0)
			{
			return false;
			}
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_VAR_CALL)
		{
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_FUNC_DEF)
		{
		bool f_Found = false;
		for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
			{
			/*for(int f_helly = 0; f_helly < m_vec_Function[f_XY]->m_idx_vec_Insta; f_helly++)
				{
				std::shared_ptr<classInsta> f_searchInsta = m_vec_Function[f_XY]->m_vec_Insta[f_helly];
				
				if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
					{
					f_Found = true;
					}
				}*/
			}
			
		for(int f_helly = 0; f_helly < f_Function->m_idx_vec_Insta; f_helly++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_searchInsta");
			std::shared_ptr<classInsta> f_searchInsta = f_Function->m_vec_Insta[f_helly];
			
			if(f_searchInsta->m_Type == INSTA_TYPE_FUNC_DEF)
				{
				f_Found = true;
				}
			}
		
		if(f_Found == true)
			{
			return false;
			}
		else
			{			
			if(acFactorise(true, 4, 5, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
				{
				m_LastType = f_Type;
				m_Factor[f_Type]->m_Use++;
				return true;
				}
			else
				{
				return false;
				}
			}
		}
	else if(f_Type == INSTA_TYPE_FUNC_CALL)
		{	
		if(acFactorise(true, 5, 6, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_CONDITIONAL)
		{
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_FUNC_CALL)
		    {
		    return false;
		    }
		
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
		    return false;
		    }
			
		if(m_LastType != -5)
			{
		    return false;
		    }
		
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
	else if(f_Type == INSTA_TYPE_LOOP_DEF)
		{
		if(m_LastType != -5)
		    {
		    return false;
		    }
			
		if(acFactorise(true, 9, 10, f_StartAD, f_EndAD, f_ElementMax, f_Depth) == true)
			{
			m_LastType = f_Type;
			m_Factor[f_Type]->m_Use++;
			return true;
			}
		else
			{
			return false;
			}
		}
	else if(f_Type == INSTA_TYPE_DATA)
		{
		if(m_LastType == -5)
		    {
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_VAR_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_FUNC_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_CONDITIONAL)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_LOOP_DEF)
		    {
			return false;
		    }
			
		if(m_LastType == INSTA_TYPE_VAR_CALL)
			{
			return false;
			}
			
		if(m_LastType == INSTA_TYPE_DATA)
			{
			return false;
			}
			
		m_LastType = f_Type;
		m_Factor[f_Type]->m_Use++;
		return true;
		}
		
	return true;
}

classCountLock::classCountLock(int f_Count, std::string f_StringC, int f_Type)
{
	std::string f_ref_CurrentPath = "classCountLock::classCountLock";

	m_Count = f_Count;
	m_String = f_StringC;
	m_Factor = f_Type;

#ifndef OSI_MEM_APP
	ac_Push(m_Count, f_ref_CurrentPath + g_ref_Div + "m_Count");
	ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_Factor, f_ref_CurrentPath + g_ref_Div + "m_Factor");
#endif
}

void classTarget_JScript::acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_JScript> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_JScript::acFromHesh";

	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_Element");
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Count]);

		m_Collection->m_vec_Element.push_back(f_Element);
		m_Collection->m_idx_vec_Element++;
		}
		
	m_SchemaTop = 0;
	m_SchemaRef[0]->m_X = float(3.121113539F);
	m_SchemaRef[0]->m_Y = float(3.773584266F);
	m_SchemaRef[0]->m_Z = float(3.952468634F);
	
	shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[0];
	
	int f_FunctionCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 1);

	for(int f_Jet = 0; f_Jet < f_FunctionCount; f_Jet++)
		{
		m_vec_CountLock.clear();

		int f_FunctionType = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 2);
		int f_ArgumentCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 2, 3, 3);
		int f_InstaCountMap = ac_takeMeasurementINTV1(f_Element, 1, 500, 20, 3, 4);
		m_InstaCountMap = f_InstaCountMap;
		
		ag_StatusLive(f_ref_CurrentPath, "f_vec_CodeLine");
		std::shared_ptr<classCodeLine> f_vec_CodeLine = std::make_shared_reflect<classCodeLine>();
		ag_StatusLive(f_ref_CurrentPath, "f_Function");
		std::shared_ptr<classFunction> f_Function = std::make_shared_reflect<classFunction>();

		f_Function->m_Type = f_FunctionType;
		f_Function->m_Name = ac_takeMeasurement(f_Element);
		
		std::string f_StringA = "function " + f_Function->m_Name + "(";

		ag_StatusLive(f_ref_CurrentPath, "f_Insta"); std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringA, INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;
		
		for(int f_Int = 0; f_Int < f_ArgumentCount; f_Int++)
			{
			if(f_Int > 0)
				{
				f_StringA += ", ";
				}
				
			std::string f_VarNameA = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

			f_Insta = std::make_shared<classInsta>(f_VarNameA, INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;
			
			f_StringA += f_VarNameA;
			}

		f_Function->m_vec_String += f_StringA;
		f_Function->m_vec_String += ")\n	{\n";
		
		acResetLine();
		
		m_idx_vec_CountLock = 0;
	
		ag_StatusLive(f_ref_CurrentPath, "m_vec_CountLock"); m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_InstaCountMap, "\n}//endfunc " + f_Function->m_Name + "\n", INSTA_TYPE_FUNC_DEF));
		m_idx_vec_CountLock++;

		int f_ElementID = 0;
		
		while(m_InstaCountMap > 0)
			{
			f_Element = m_Collection->m_vec_Element[f_ElementID];
			
			f_ElementID++;
			
			if(f_ElementID >= m_Collection->m_idx_vec_Element)
				{
				f_ElementID = 0;
				}
				
			bool f_Contact = false;
				
			int f_InstaType = ac_takeMeasurementINTV1(f_Element, 0, INSTA_TYPE_COUNT, 2, 3, 6);

			if(f_InstaType == INSTA_TYPE_VAR_DEF)
				{
				if(acFactorStrength(INSTA_TYPE_VAR_DEF, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_StringB = "var " + f_Name + " = ";
					f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_VAR_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					
					//std::shared_ptr<classInsta> f_InstaCount = ac_takeMeasurementINTV1(f_Element, 1, 4, 3, 3, 6);
					
					//m_vec_CountLock.push_back(std::make_shared<classCountLock(f_InstaCount, ";\n", INSTA_TYPE_VAR_DEF));
					//m_idx_vec_CountLock++;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_VAR_CALL)
				{
				if(acFactorStrength(INSTA_TYPE_VAR_CALL, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					 ///////////////////
					// preleah
					if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}
							
						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
							if(f_fingerCount <= 1)
								{
								f_Function->m_vec_String += " == ";
								}
							else if(f_fingerCount == 2)
								{
								f_Function->m_vec_String += " >= ";
								}
							else if(f_fingerCount == 3)
								{
								f_Function->m_vec_String += " <= ";
								}
							else if(f_fingerCount == 4)
								{
								f_Function->m_vec_String += " > ";
								}
							else if(f_fingerCount >= 5)
								{
								f_Function->m_vec_String += " < ";
								}
							}
						else
							{
							if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
								{
								if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
									{
									f_Function->m_vec_String += ", ";
									}

								if(m_LastTypeII == INSTA_TYPE_DATA)
									{
									f_Function->m_vec_String += ", ";
									}
								}
							}
						}
					else if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}

						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else
					    {
						if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
						    {
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
								
								m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
								
								if(f_fingerCount <= 1)
									{
									f_Function->m_vec_String += " = ";
									}
								else if(f_fingerCount == 2)
									{
									f_Function->m_vec_String += " -= ";
									}
								else if(f_fingerCount == 3)
									{
									f_Function->m_vec_String += " *= ";
									}
								else if(f_fingerCount == 4)
									{
									f_Function->m_vec_String += " /= ";
									}
								else if(f_fingerCount >= 5)
									{
									f_Function->m_vec_String += " += ";
									}
								}
							}
						else
							{
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
									
									m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " = ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " -= ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " *= ";
										}
									else if(f_fingerCount == 4)
										{
										f_Function->m_vec_String += " /= ";
										}
									else if(f_fingerCount >= 5)
										{
										f_Function->m_vec_String += " += ";
										}
									}
								else
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " - ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " * ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " / ";
										}
									else if(f_fingerCount >= 4)
										{
										f_Function->m_vec_String += " + ";
										}
									}
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_StringB = f_Name;
					f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_CONDITIONAL)
				{
				if(acFactorStrength(INSTA_TYPE_CONDITIONAL, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_StringB = "if(";
					f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_CONDITIONAL);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					
					int f_InstaCount = 2 + ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 5);
					
					std::vector<int> f_conInstaCount;
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 0, 2, 0, 3, 4));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 1, 12, 0, 3, 5));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 2, 25, 4, 3, 6));
					int f_Select = ac_takeMeasurementINTV1(f_Element, 0, 3, 1, 3, 3);
					
					ag_StatusLive(f_ref_CurrentPath, "m_vec_CountLock");
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_conInstaCount[f_Select], "\n}\n", INSTA_TYPE_CONDITIONAL));
					m_idx_vec_CountLock++;
					
					ag_StatusLive(f_ref_CurrentPath, "m_vec_CountLock");
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_InstaCount, ")\n	{", INSTA_TYPE_CONDITIONAL));
					m_idx_vec_CountLock++;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_LOOP_DEF)
				{
				if(acFactorStrength(INSTA_TYPE_LOOP_DEF, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_forVarName = ac_takeMeasurement(f_Element);
					std::string f_Str = "for(int " + f_forVarName + " = 0; " + f_forVarName + " < " + f_Name + "; " + f_forVarName + "++)\n	{\n 	";
					f_Insta = std::make_shared<classInsta>(f_Str, INSTA_TYPE_LOOP_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_Str;
					m_InstaCountMap--;
					
					int f_loopInstaCount = ac_takeMeasurementINTV1(f_Element, 8, 105, 8, 3, 1);
					
					ag_StatusLive(f_ref_CurrentPath, "m_vec_CountLock");
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_loopInstaCount, "\n}\n", INSTA_TYPE_LOOP_DEF));
					m_idx_vec_CountLock++;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_FUNC_CALL)
				{
				if(acFactorStrength(INSTA_TYPE_FUNC_CALL, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					 ///////////////////
					// preleah
					if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}
							
						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
							if(f_FingerCount <= 1)
								{
								f_Function->m_vec_String += " == ";
								}
							else if(f_FingerCount == 2)
								{
								f_Function->m_vec_String += " >= ";
								}
							else if(f_FingerCount == 3)
								{
								f_Function->m_vec_String += " <= ";
								}
							else if(f_FingerCount == 4)
								{
								f_Function->m_vec_String += " > ";
								}
							else if(f_FingerCount >= 5)
								{
								f_Function->m_vec_String += " < ";
								}
							}
						else
							{
							if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
								{
								if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
									{
									f_Function->m_vec_String += ", ";
									}

								if(m_LastTypeII == INSTA_TYPE_DATA)
									{
									f_Function->m_vec_String += ", ";
									}
								}
							}
						}
					else if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 2)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}

						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else
					    {
						if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
						    {
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
								
								m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
								
								if(f_FingerCount <= 1)
									{
									f_Function->m_vec_String += " = ";
									}
								else if(f_FingerCount == 2)
									{
									f_Function->m_vec_String += " -= ";
									}
								else if(f_FingerCount == 3)
									{
									f_Function->m_vec_String += " *= ";
									}
								else if(f_FingerCount == 4)
									{
									f_Function->m_vec_String += " /= ";
									}
								else if(f_FingerCount >= 5)
									{
									f_Function->m_vec_String += " += ";
									}
								}
							}
						else
							{
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
									{
									int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
									
									m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
									
									if(f_FingerCount <= 1)
										{
										f_Function->m_vec_String += " = ";
										}
									else if(f_FingerCount == 2)
										{
										f_Function->m_vec_String += " -= ";
										}
									else if(f_FingerCount == 3)
										{
										f_Function->m_vec_String += " *= ";
										}
									else if(f_FingerCount == 4)
										{
										f_Function->m_vec_String += " /= ";
										}
									else if(f_FingerCount >= 5)
										{
										f_Function->m_vec_String += " += ";
										}
									}
								else
									{
									int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
									
									if(f_FingerCount <= 1)
										{
										f_Function->m_vec_String += " - ";
										}
									else if(f_FingerCount == 2)
										{
										f_Function->m_vec_String += " * ";
										}
									else if(f_FingerCount == 3)
										{
										f_Function->m_vec_String += " / ";
										}
									else if(f_FingerCount >= 4)
										{
										f_Function->m_vec_String += " + ";
										}
									}
								}
							}
						}
						
					//target restriction point
					std::string f_FunctionName = acMakeUnison(f_Target, ac_takeMeasurement(f_Element), 1, INSTA_TYPE_FUNC_CALL, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_StringB = f_FunctionName + "(";
					
					f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_FUNC_CALL);
							
					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					
					int f_arguInstaCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 4);
					
					ag_StatusLive(f_ref_CurrentPath, "m_vec_CountLock");
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_arguInstaCount, ")", INSTA_TYPE_FUNC_CALL));
					m_idx_vec_CountLock++;
				    f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_DATA)
				{
				if(acFactorStrength(INSTA_TYPE_DATA, f_Function, f_Element) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					 ///////////////////
					// preleah
					if(m_Factor[INSTA_TYPE_FUNC_DEF]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}
							
						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else if(m_Factor[INSTA_TYPE_CONDITIONAL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
							if(f_fingerCount <= 1)
								{
								f_Function->m_vec_String += " == ";
								}
							else if(f_fingerCount == 2)
								{
								f_Function->m_vec_String += " >= ";
								}
							else if(f_fingerCount == 3)
								{
								f_Function->m_vec_String += " <= ";
								}
							else if(f_fingerCount == 4)
								{
								f_Function->m_vec_String += " > ";
								}
							else if(f_fingerCount >= 5)
								{
								f_Function->m_vec_String += " < ";
								}
							}
						else
							{
							if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
								{
								if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
									{
									f_Function->m_vec_String += ", ";
									}

								if(m_LastTypeII == INSTA_TYPE_DATA)
									{
									f_Function->m_vec_String += ", ";
									}
								}
							}
						}
					else if(m_Factor[INSTA_TYPE_FUNC_CALL]->m_Use >= 1)
						{
						if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
							{
							f_Function->m_vec_String += ", ";
							}

						if(m_LastTypeII == INSTA_TYPE_DATA)
							{
							f_Function->m_vec_String += ", ";
							}
						}
					else
					    {
						if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
						    {
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
								
								m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
								
								if(f_fingerCount <= 1)
									{
									f_Function->m_vec_String += " = ";
									}
								else if(f_fingerCount == 2)
									{
									f_Function->m_vec_String += " -= ";
									}
								else if(f_fingerCount == 3)
									{
									f_Function->m_vec_String += " *= ";
									}
								else if(f_fingerCount == 4)
									{
									f_Function->m_vec_String += " /= ";
									}
								else if(f_fingerCount >= 5)
									{
									f_Function->m_vec_String += " += ";
									}
								}
							}
						else
							{
							if(m_LastTypeII == INSTA_TYPE_VAR_CALL)
								{
								if(m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use == 0)
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 0, 3, 1);
									
									m_Factor[INSTA_TYPE_LM_OPER_EQUALS]->m_Use++;
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " = ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " -= ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " *= ";
										}
									else if(f_fingerCount == 4)
										{
										f_Function->m_vec_String += " /= ";
										}
									else if(f_fingerCount >= 5)
										{
										f_Function->m_vec_String += " += ";
										}
									}
								else
									{
									int f_fingerCount = ac_takeMeasurementINTV1(f_Element, 0, 5, 0, 3, 2);
									
									if(f_fingerCount <= 1)
										{
										f_Function->m_vec_String += " - ";
										}
									else if(f_fingerCount == 2)
										{
										f_Function->m_vec_String += " * ";
										}
									else if(f_fingerCount == 3)
										{
										f_Function->m_vec_String += " / ";
										}
									else if(f_fingerCount >= 4)
										{
										f_Function->m_vec_String += " + ";
										}
									}
								}
							}
						}

					//target restriction point
					std::string f_StringB = "";
					int f_Scale = 32;
					int f_VarType = ac_takeMeasurementINTV1(f_Element, 0, 3, 4, 3, 1);
					int f_VarSize = ac_takeMeasurementINTV1(f_Element, 1, f_Scale, 7, 3, 0);
					
					if(f_VarType == VAR_TYPE_INT)
						{
						char* f_Char = ag_ClearChar(255);

						::sprintf(f_Char, "%i", ac_takeMeasurementINTV1(f_Element, 1, 10, 2, 3, 7) * f_VarSize);

						f_StringB += f_Char;

						delete f_Char;
						}
					else if(f_VarType >= VAR_TYPE_FLT)
						{
						char* f_Char = ag_ClearChar(255);

						::sprintf(f_Char, "%f", (float)(ac_takeMeasurementINTV1(f_Element, 1, 10, 2, 3, 7)) * (float)(f_VarSize));

						f_StringB += f_Char;

						delete f_Char;
						}
					/*else if(f_VarType == VAR_TYPE_HEX)
						{
						for(int f_Flx = 0; f_Flx < f_VarSize; f_Flx++)
							{
							f_StringB += ac_takeMeasurement(f_Element);
							}
						}
					else if(f_VarType == VAR_TYPE_BIN)
						{
						for(int f_Flx = 0; f_Flx < f_VarSize; f_Flx++)
							{
							f_StringB += ac_takeMeasurement(f_Element);
							}
						}*/
					
					f_Insta = std::make_shared<classInsta>(f_StringB, INSTA_TYPE_DATA);
							
					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					f_Contact = true;
					}
				}
			else if(f_InstaType == INSTA_TYPE_FUNC_DEF)
				{
				/*if(acFactorStrength(INSTA_TYPE_FUNC_DEF, f_Function, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					ag_StatusLive(f_ref_CurrentPath, "f_Insta"); std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta(f_StringB, INSTA_TYPE_FUNC_DEF);
							
					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					m_InstaCountMap--;
					}*/
				}
				
			  ///////////////////
			 //
			// Count Map
			if(f_Contact == true)
				{
				f_vec_CodeLine->m_vec_Code.push_back(f_Function->m_vec_Insta[f_Function->m_idx_vec_Insta - 1]);
				f_vec_CodeLine->m_idx_vec_Code++;
					
#if 0
				if(m_idx_vec_CountLock > 0)
					{
					for(int f_cv = m_idx_vec_CountLock - 1; f_cv >= 0; f_cv--)
					     {
					     int f_Caramel = f_cv;

					     m_vec_CountLock[f_Caramel]->m_Count--;
					
					     if(m_vec_CountLock[f_Caramel]->m_Count <= 0)
							{
							bool f_on = true;

							if(f_Caramel < (m_idx_vec_CountLock - 1))
								{
								f_on = false;
								}
								
							if(f_on == true)
								{
								std::shared_ptr<classCountLock> f_Lock = m_vec_CountLock[f_Caramel];

								f_Function->m_vec_String += f_Lock->m_String;

								if(f_Lock->m_String.compare("\n") != 0)
									{
									acResetLine();
									f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
									f_Function->m_idx_vec_CodeLineStorage++;

									f_vec_CodeLine->m_vec_Code.clear();
									f_vec_CodeLine->m_idx_vec_Code = 0;
									}

								acDecFactor(f_Lock->m_Factor);

								m_idx_vec_CountLock--;
								
								for(int f_XY = f_Caramel; f_XY < m_idx_vec_CountLock; f_XY++)
									{
									m_vec_CountLock[f_XY] = m_vec_CountLock[f_XY + 1];
									}
								
								if(f_Lock->m_String.compare(")") == 0)
									{
									bool f_ont = true;
									
									for(int f_cv1 = 1; f_cv1 < m_idx_vec_CountLock; f_cv1++)
										{
										for(int f_cv3 = 0; f_cv3 < m_vec_CountLock[f_cv1]->m_String.length(); f_cv3++)
											{
											if(m_vec_CountLock[f_cv1]->m_String.at(f_cv3) == ')')
												{
												f_ont = false;
												}
											}
										}
										
									if(f_ont == true)
										{
										acResetLine();
										f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
										f_Function->m_idx_vec_CodeLineStorage++;
										f_Function->m_vec_String += ";\n";

										f_vec_CodeLine->m_vec_Code.clear();
										f_vec_CodeLine->m_idx_vec_Code = 0;
										}
									}

								m_vec_CountLock.pop_back();
								}
							else
								{
								m_vec_CountLock[f_Caramel]->m_Count = 1;
								}
							}
						}
					}
#endif
				}
			}

		m_String += f_Function->m_vec_String;

		m_vec_Function.push_back(f_Function);
		m_idx_vec_Function++;
		}
}

std::string classTarget_Ecom::acGen_genline_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_RecLine = "";

	int f_LineType = ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 2, 0, 3);

	if(f_LineType == 0)
		{
		f_RecLine += "Complete ";

		std::string f_LineCompleteName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineCompleteName + " ";

		std::string f_LineClassName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineClassName + " ";

		std::string f_LineName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineName + " ";

		std::string f_LineDefaultValue = ac_takeMeasurement_DefaultValue(-1, -1, -1, -1);

		f_RecLine += f_LineDefaultValue + " ";

		int f_LineSHRIDX = ac_takeMeasurementINTS(-1, -1, -1, -1);

		int f_LineELEIDX = ac_takeMeasurementINTS(-1, -1, -1, -1);

		char* f_Char = ag_ClearChar(255);

		::sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
			{
			std::string f_LineComment = ac_takeMeasurement(-1, -1, -1, -1);

			f_RecLine += f_LineComment;
			}
		}
	else if(f_LineType == 1)
		{
		f_RecLine += "Insert ";

		std::string f_LineClassName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineClassName + " ";

		std::string f_LineName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineName + " ";

		std::string f_LineDefaultValue = ac_takeMeasurement_DefaultValue(-1, -1, -1, -1);

		f_RecLine += f_LineDefaultValue + " ";

		int f_LineSHRIDX = ac_takeMeasurementINTS(-1, -1, -1, -1);

		int f_LineELEIDX = ac_takeMeasurementINTS(-1, -1, -1, -1);

		char* f_Char = ag_ClearChar(255);

		::sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
			{
			std::string f_LineComment = ac_takeMeasurement(-1, -1, -1, -1);

			f_RecLine += f_LineComment;
			}
		}
	else if(f_LineType == 2)
		{
		f_RecLine += "Delete ";

		std::string f_LineDeleteName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineDeleteName + " ";

		std::string f_LineClassName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineClassName + " ";

		std::string f_LineName = ac_takeMeasurement(-1, -1, -1, -1);

		f_RecLine += f_LineName + " ";

		std::string f_LineDefaultValue = ac_takeMeasurement_DefaultValue(-1, -1, -1, -1);

		f_RecLine += f_LineDefaultValue + " ";

		int f_LineSHRIDX = ac_takeMeasurementINTS(-1, -1, -1, -1);

		int f_LineELEIDX = ac_takeMeasurementINTS(-1, -1, -1, -1);

		char* f_Char = ag_ClearChar(255);

		::sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
			{
			std::string f_LineComment = ac_takeMeasurement(-1, -1, -1, -1);

			f_RecLine += f_LineComment;
			}
		}

	return f_RecLine;
}

std::string classLMap::acGen_genline_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_StrLine = f_Save_Com->m_genScript->m_vec_InitLineOrdered[f_StartAD];
	std::vector<std::string> f_vec_Package;
	std::string f_Packet = "";

	for(int f_CCount = 0; f_CCount < f_StrLine.length(); f_CCount++)
		{
		char f_c = f_StrLine.at(f_CCount);

		if ((f_c == ' ') || (f_CCount >= f_StrLine.length() - 1))
			{
			f_vec_Package.push_back(f_Packet);
			f_Packet.clear();
			}
		else
			{
			f_Packet.push_back(f_c);
			}
		}

	std::string f_RecLine = "";

	if(f_vec_Package[0].compare("Complete") == 0)
		{
		int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		//save line type
		ac_recordMeasurementINTV1(0, 2, 0, 3, 0, 0, f_ElementIndex);

		f_RecLine += "Complete ";

		//packet to complete name
		std::string f_Name = f_vec_Package[1];

		//complete this package name
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineCompleteName = ac_recordMeasurement(f_Name, f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineCompleteName + " ";

		//classname
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineClassName = ac_recordMeasurement(f_vec_Package[2], f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineClassName + " ";

		//insert name
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineName = ac_recordMeasurement(f_vec_Package[3], f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineName + " ";

		//default value notice no prepull element
		std::string f_LineDefaultValue = ac_recordMeasurement_DefaultValue(f_vec_Package[4], -1, -1, -1, -1);

		f_RecLine += f_LineDefaultValue + " ";

		//ShareID
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_LineSHRIDX = ac_recordMeasurementINTS(::atoi(f_vec_Package[5].c_str()), f_ElementIndex);

		//ElementID
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_LineELEIDX = ac_recordMeasurementINTS(::atoi(f_vec_Package[6].c_str()), f_ElementIndex);

		char* f_Char = ag_ClearChar(255);

		::sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(0, 9, (f_vec_Package.size() >= 8) ? true : false, f_ElementIndex) == true)
			{
			//comment
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			std::string f_LineComment = ac_recordMeasurement(f_vec_Package[7], f_ElementIndex, -1, -1, -1, -1);

			f_RecLine += f_LineComment;
			}
		}
	else if(f_vec_Package[0].compare("Insert") == 0)
		{
		int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		//save line type
		ac_recordMeasurementINTV1(0, 2, 0, 3, 0, 1, f_ElementIndex);

		f_RecLine += "Insert ";

		//classname
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineClassName = ac_recordMeasurement(f_vec_Package[1], f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineClassName + " ";

		//insert name
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineName = ac_recordMeasurement(f_vec_Package[2], f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineName + " ";

		//default value notice no prepull element
		std::string f_LineDefaultValue = ac_recordMeasurement_DefaultValue(f_vec_Package[3], -1, -1, -1, -1);

		f_RecLine += f_LineDefaultValue + " ";

		//ShareID
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_LineSHRIDX = ac_recordMeasurementINTS(::atoi(f_vec_Package[4].c_str()), f_ElementIndex);

		//ElementID
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_LineELEIDX = ac_recordMeasurementINTS(::atoi(f_vec_Package[5].c_str()), f_ElementIndex);

		char* f_Char = ag_ClearChar(255);

		::sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(0, 9, (f_vec_Package.size() >= 7) ? true : false, f_ElementIndex) == true)
			{
			//comment
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			std::string f_LineComment = ac_recordMeasurement(f_vec_Package[6], f_ElementIndex, -1, -1, -1, -1);

			f_RecLine += f_LineComment;
			}
		}
	else if(f_vec_Package[0].compare("Delete") == 0)
		{
		int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		//save line type
		ac_recordMeasurementINTV1(0, 2, 0, 3, 2, 2, f_ElementIndex);

		f_RecLine += "Delete ";

		//packet to delete name
		std::string f_Name = f_vec_Package[1];

		//delete this package name
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineCompleteName = ac_recordMeasurement(f_Name, f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineCompleteName + " ";

		//classname
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineClassName = ac_recordMeasurement(f_vec_Package[2], f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineClassName + " ";

		//insert name
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		std::string f_LineName = ac_recordMeasurement(f_vec_Package[3], f_ElementIndex, -1, -1, -1, -1);

		f_RecLine += f_LineName + " ";

		//default value notice no prepull element
		std::string f_LineDefaultValue = ac_recordMeasurement_DefaultValue(f_vec_Package[4], -1, -1, -1, -1);

		f_RecLine += f_LineDefaultValue + " ";

		//ShareID
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_LineSHRIDX = ac_recordMeasurementINTS(::atoi(f_vec_Package[5].c_str()), f_ElementIndex);

		//ElementID
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		int f_LineELEIDX = ac_recordMeasurementINTS(::atoi(f_vec_Package[6].c_str()), f_ElementIndex);

		char* f_Char = ag_ClearChar(255);

		::sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(0, 9, (f_vec_Package.size() >= 8) ? true : false, f_ElementIndex) == true)
			{
			//comment
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			std::string f_LineComment = ac_recordMeasurement(f_vec_Package[7], f_ElementIndex, -1, -1, -1, -1);

			f_RecLine += f_LineComment;
			}
		}

	return f_RecLine;
}

int classTarget_Ecom::ac_takeMeasurementINTS(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth)
{
	std::string f_Result = "";

	if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
		{
		f_Result.push_back('-');
		}

	bool f_Scan = true;
	while(f_Scan == true)
		{
		int f_CharInt = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 9, 0, 0);

		f_Result.push_back((char)(f_CharInt + '0'));

		//continue check
		f_Scan = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 4);
		}

	return ::atoi(f_Result.c_str());
}

int classLMap::ac_takeMeasurementINTS(shared_ptr<classElement> f_Vertex)
{
	std::string f_Result = "";

	if(ac_takeMeasurementBLTV1(f_Vertex, 0, 4, 0) == true)
		{
		f_Result.push_back('-');
		}

	bool f_Scan = true;

	while(f_Scan == true)
		{
		int f_CharInt = ac_takeMeasurementINTV1(f_Vertex, 0, 9, 0, 0, 0, 0);

		f_Result.push_back((char)(f_CharInt + '0'));

		//continue check
		f_Scan = ac_takeMeasurementBLTV1(f_Vertex, 0, 4, 0);
		}

	return ::atoi(f_Result.c_str());
}

void classLMap::ac_lastMeasurement(int f_IndexID)
{
	if(f_IndexID == 2)
		{
		if(m_LMap->m_vec_Measure.size() > 0)
			{
			m_LMap->m_vec_Measure[m_LMap->m_vec_Measure.size() - 1]->m_isOwnerID = true;
			}
		}
	else
		{
		if(m_LMap->m_vec_Measure.size() > 0)
			{
			m_LMap->m_vec_Measure[m_LMap->m_vec_Measure.size() - 1]->m_isInsertID = true;
			}
		}

}

int classLMap::ac_recordMeasurementINTS(int f_RecordResult, int f_ElementID, bool f_isIndexID)
{
	std::string f_ref_CurrentPath = "classLMap::ac_recordMeasurementINTS";

	//on position ignore all INTS changes in lensemap
	int f_IndexID = 1;

	char* f_Char = ag_ClearChar(255);

	::sprintf(f_Char, "%i", f_RecordResult);

	std::string f_StringResult = f_Char;
	std::string f_StringResultChars = "";

	bool f_Minus = ac_recordMeasurementBLTV1(0, 1, (f_StringResult.at(0) == '-') ? true : false, f_ElementID);

	ac_lastMeasurement(f_IndexID);

	int f_ElementIndex = 0;
	int f_StartVar = 0;

	if(f_Minus == true)
		{
		f_StartVar = 1;
		}

	bool f_On = true;
	int f_Jet = f_StartVar;

	while(f_On == true)
		{
		int f_CharInt = f_StringResult.at(f_Jet) - '0';

		if((f_CharInt >= 0) && (f_CharInt <= 9))
			{
			f_ElementID = acPull_gen_ElementID(-1, -1, -1, -1);

			int f_RecResultInt = ac_recordMeasurementINTV1(0, 9, 0, 3, 4, f_CharInt, f_ElementID);

			ac_lastMeasurement(f_IndexID);

			f_StringResultChars.push_back((char)(f_RecResultInt + '0'));
			}

		f_ElementID = acPull_gen_ElementID(-1, -1, -1, -1);

		f_On = ac_recordMeasurementBLTV1(2, 0, (f_Jet == (f_StringResult.length() - 1)) ? false : true, f_ElementID);

		ac_lastMeasurement(f_IndexID);

		f_Jet++;
		}

	delete f_Char;

	std::string f_String = "";

	if(f_Minus == true)
		{
		f_String.push_back('-');

		for(int f_Int = 0; f_Int < f_StringResultChars.length(); f_Int++)
			{
			f_String.push_back(f_StringResultChars.at(f_Int));
			}
		}
	else
		{
		f_String = f_StringResultChars;
		}

	int f_RecordedResult = ::atoi(f_String.c_str());

	//return
	return f_RecordedResult;
}

std::shared_ptr<Qcom_genScript> classTarget_Ecom::acGen_gen_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_gen_FromHesh";

	ag_StatusLive(f_ref_CurrentPath, "f_Measure");
	std::shared_ptr<Qcom_genScript> f_gen = std::make_shared_reflect<Qcom_genScript>();

	std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_gen->m_ComID = f_Com->m_ID;

	f_gen->m_birthcomid = f_Com->m_birthcomid;

	f_gen->m_QamID = f_Com->m_QamID;

	f_gen->m_QamLevel = f_Com->m_QamLevel;

	f_gen->m_ID = -5; //unknown

	f_gen->m_name = f_VarNameA;

	f_gen->m_owner = f_Com->m_owner;

	f_gen->m_description = ""; //add

	f_gen->m_Save = true;

	   ////////////////////////////
	  //
	 // Generation Script Gen
	// Insert Change Element restriction or other share entirely at this point
	int f_XY = 0;
	bool f_ScanLines = true;
	while(f_ScanLines == true)
		{
		f_ScanLines = ac_takeMeasurementBLTV1(1, 1, 1, 1, 1);

		if(f_ScanLines == true)
			{
			std::string f_String = acGen_genline_FromHesh(f_Hesh, f_XY, -1, f_ElementMax, f_Depth, f_Target);

			f_gen->m_vec_InitLine.push_back(f_String);
			f_gen->m_vec_InitLineOrdered.push_back(f_String);

			f_XY++;
			}
		}

	return f_gen;
}

std::shared_ptr<Qcom_genScript> classLMap::acGen_gen_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_gen_FromEcom";

	ag_StatusLive(f_ref_CurrentPath, "f_gen");
	std::shared_ptr<Qcom_genScript> f_gen = std::make_shared_reflect<Qcom_genScript>();

	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	std::string f_VarNameA = ac_recordMeasurement(f_Save_Com->m_genScript->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_gen->m_ComID = f_Save_Com->m_ID;
		
	f_gen->m_birthcomid = f_Save_Com->m_birthcomid;

	f_gen->m_QamID = f_Save_Com->m_QamID;

	f_gen->m_QamLevel = f_Save_Com->m_QamLevel;

	f_gen->m_ID = f_Save_Com->m_ID;

	f_gen->m_name = f_VarNameA;

	f_gen->m_owner = f_Save_Com->m_owner;

	f_gen->m_description = f_Save_Com->m_description;

	f_gen->m_Save = true;

	   ////////////////////////////
	  //
	 // Generation Script Gen
	// Insert Change Element restriction or other share entirely at this point
	int f_XY = 0;
	bool f_ScanLines = true;
	while(f_ScanLines == true)
		{
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_ScanLines = ac_recordMeasurementBLTV1(1, 1, (f_XY < f_Save_Com->m_genScript->m_vec_InitLineOrdered.size()) ? true : false, f_ElementIndex);

		if(f_ScanLines == true)
			{
			std::string f_String = acGen_genline_FromEcom(f_Save_Com, f_XY, f_Save_Com->m_genScript->m_vec_InitLineOrdered.size(), f_ElementMax, f_Depth, f_Target);

			f_gen->m_vec_InitLine.push_back(f_String);
			f_gen->m_vec_InitLineOrdered.push_back(f_String);

			f_XY++;
			}
		}

	return f_gen;
}

std::shared_ptr<Qcom> classTarget_Ecom::acGen_com_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_FromHesh";

	while(m_Collection->m_vec_Element.size() < f_Hesh->m_adIndex.size())
		{
#ifndef OSI_MEM_APP
		ag_StatusLive(f_ref_CurrentPath, "f_Element");
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[m_Collection->m_idx_vec_Element]);
#else
		std::shared_ptr<classElement> f_Element = std::make_shared<classElement>(f_Hesh->vec_Bicycle[m_Collection->m_idx_vec_Element]);
#endif

		m_Collection->m_vec_Element.push_back(f_Element);

		m_Collection->m_idx_vec_Element++;
		}

	if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_com");
		std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

		f_com->m_ID = -1551;

		if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
			{
			f_com->m_ID = ac_takeMeasurementINTS(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}

		std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_birthcomid = ac_takeMeasurementINTS(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_BossLVLMin = ac_takeMeasurementFLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_position->m_X = ac_takeMeasurementFLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		f_com->m_position->m_Y = ac_takeMeasurementFLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_Cost = ac_takeMeasurementFLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_name = f_VarNameA;

		f_com->m_owner = ac_takeMeasureKey(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
			{
			f_com->m_description = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}

		f_com->m_parentcomid = ac_takeMeasurementINTS(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_rebuild = true;
		f_com->m_Save = false;

		f_com->m_VoteScore = ac_takeMeasurementINTS(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		  ////////////////////////////
		 //
		// Generation Script Gen
		if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
			{
			f_com->m_genScript = acGen_gen_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			g_QcomManager->m_vec_GenScript.push_back(f_com->m_genScript);
			}

		//Insert Change Element restriction or other share entirely at this point
		if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_Frame_ESLFunction = f_Function;

			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}

		bool f_ScanFunc = true;
		while(f_ScanFunc == true)
			{
			f_ScanFunc = ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1);

			if(f_ScanFunc == true)
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

				f_com->m_vec_ESLFunction.push_back(f_Function);

				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}
			}
		
#ifdef ESL_CIRCUIT_APPENDIX
		bool f_ScanInput = true;
		while(f_ScanInput == true)
			{
			f_ScanInput = ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1);

			if(f_ScanInput == true)
				{ //dive in levels of element selection range
				std::shared_ptr<QcomInput> f_COM_Input = acGen_com_input_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

				if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
					{
					if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

						f_COM_Input->m_InputFunction = f_Function;

						g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
						}
					}

				f_com->m_vec_Input.push_back(f_COM_Input);
				g_QcomManager->m_vec_Input.push_back(f_COM_Input);
				}
			}

		bool f_ScanOutput = true;
		while(f_ScanOutput == true)
			{
			f_ScanOutput = ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1);

			if(f_ScanOutput == true)
				{ //levels of element selection range
				std::shared_ptr<QcomOutput> f_COM_Output = acGen_com_output_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

				if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
					{
					if(ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1) == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromHesh(f_Hesh, f_com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

						f_COM_Output->m_OutputFunction = f_Function;

						g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
						}
					}

				f_com->m_vec_Output.push_back(f_COM_Output);
				g_QcomManager->m_vec_Output.push_back(f_COM_Output);
				}
			}
#else
		ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1);
		ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1);
#endif

		//f_com->acWire(f_Hesh, 0, f_Hesh->vec_Bicycle.size());

		//Insert Change Element restriction or other share entirely at this point
		bool f_ScanCom = true;
		while(f_ScanCom == true)
			{
			f_ScanCom = ac_takeMeasurementBLTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1);

			if(f_ScanCom == true)
				{
				std::shared_ptr<Qcom> f_com_B = acGen_com_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

				f_com->m_vec_Qcom.push_back(f_com_B);

				g_QcomManager->m_vec_Qcom.push_back(f_com_B);
				}
			}

		return f_com;
		}
	else  //else comid structure build
		{ //obtain qcom db index
		int f_ComID = ac_takeMeasurementINTS(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if((m_GlobalScope == true) && (f_ComID > 0)) //global built from share and ids
			{
#if 1
			//switch on proper index db build here...
			ag_StatusLive(f_ref_CurrentPath, "f_com");
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>(f_ComID);
			//add bosslvl check to Qcom load
#else
			//appeasement com return
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

			f_com->m_ID = f_ComID;
			f_com->m_name = "BUILD-ME";
#endif

			return f_com;
			}
		}

	//appeasement return
	ag_StatusLive(f_ref_CurrentPath, "f_com");
	std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

	return f_com;
}

std::shared_ptr<QcomInput> classTarget_Ecom::acGen_com_input_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_input_FromHesh";

	ag_StatusLive(f_ref_CurrentPath, "f_comInput");
	std::shared_ptr<QcomInput> f_comInput = std::make_shared_reflect<QcomInput>();

	std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_comInput->m_position->m_X = ac_takeMeasurementFLTV1(-1, -1, -1, -1);
	f_comInput->m_position->m_Y = ac_takeMeasurementFLTV1(-1, -1, -1, -1);

	f_comInput->m_name = f_VarNameA;
	f_comInput->m_ID = -5;
	f_comInput->m_birthcomid = f_Com->m_birthcomid;
	f_comInput->m_ComID = f_Com->m_ID;
	f_comInput->m_QamID = f_Com->m_QamID;
	f_comInput->m_QamLevel = f_Com->m_QamLevel;
	f_comInput->m_owner = f_Com->m_owner;
	f_comInput->m_description = "";
	f_comInput->m_rebuild = true;
	f_comInput->m_Save = true;

	return f_comInput;
}

std::shared_ptr<QcomOutput> classTarget_Ecom::acGen_com_output_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_output_FromHesh";

	ag_StatusLive(f_ref_CurrentPath, "f_comOutput");
	std::shared_ptr<QcomOutput> f_comOutput = std::make_shared_reflect<QcomOutput>();

	std::string f_VarNameA = ac_takeMeasurement(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	f_comOutput->m_position->m_X = ac_takeMeasurementFLTV1(-1, -1, -1, -1);
	f_comOutput->m_position->m_Y = ac_takeMeasurementFLTV1(-1, -1, -1, -1);

	f_comOutput->m_name = f_VarNameA;
	f_comOutput->m_ID = -5;
	f_comOutput->m_birthcomid = f_Com->m_birthcomid;
	f_comOutput->m_ComID = f_Com->m_ID;
	f_comOutput->m_QamID = f_Com->m_QamID;
	f_comOutput->m_QamLevel = f_Com->m_QamLevel;
	f_comOutput->m_owner = f_Com->m_owner;
	f_comOutput->m_description = "";
	f_comOutput->m_rebuild = true;
	f_comOutput->m_Save = true;

	return f_comOutput;
}

void classTarget_Ecom::acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acFromHesh";

	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_Element");
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Count]);

		m_Collection->m_vec_Element.push_back(f_Element);

		m_Collection->m_idx_vec_Element++;
		}

	int f_StartAD = 0;
	int f_EndAD = m_Collection->m_vec_Element.size();
	int f_ElementMax = m_Collection->m_vec_Element.size();
	int f_Depth = 1;
		
	m_SchemaTop = 0;
	m_SchemaRef[0]->m_X = float(3.121113539F);
	m_SchemaRef[0]->m_Y = float(3.773584266F);
	m_SchemaRef[0]->m_Z = float(3.952468634F);
	
	int f_EcomCount = ac_takeMeasurementINTV1(f_StartAD, f_EndAD, f_ElementMax, f_Depth, 1, 3, 0, 3);

	int f_WireContract = -5;

	if(f_WireContractOverride >= 0)
		{
		f_WireContract = f_WireContractOverride;
		}
	else
		{
#if 0
		f_WireContract = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 1);
#endif
		}

	for(int f_Jet = 0; f_Jet < f_EcomCount; f_Jet++)
		{
		std::shared_ptr<Qcom> f_com = acGen_com_FromHesh(f_Hesh, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

		//first push to target
		m_vec_Ecom.push_back(f_com);

#ifdef ECOIN_QCOM_UPDATE_FROM_HESH
		//next push to manager mega list
		g_QcomManager->m_vec_Qcom.push_back(f_com);

		//finally conditionally update current board, pending perhaps
		g_QcomManager->m_Qcom->m_vec_Qcom.push_back(f_com);
#endif
		}
}

int classLMap::acPull_gen_ElementID(int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex)
{
	return ag_Pull_gen_Element(f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_OCSCP_ThreadIndex);
}

void classLMap::acRangeAD(void)
{
	int f_CountElement = 1;
	int f_CountFinger = 0;
	
	for(int f_Jet = 0; f_Jet < m_LMap->m_vec_Measure.size(); f_Jet++)
		{
		f_CountFinger++;

		if((f_CountFinger > g_CountLM) || (f_Jet == (m_LMap->m_vec_Measure.size() - 1)))
			{
			f_CountFinger = 1;

			f_CountElement++;
			}
		}

	m_ADHIGH = f_CountElement;
	m_ADLOW = f_CountElement;
	m_ADMAX = f_CountElement;

	g_BicycleContainer[0]->m_ADMAX = f_CountElement;
	g_BicycleContainer[0]->m_ADHIGH = f_CountElement;
	g_BicycleContainer[0]->m_ADLOW = f_CountElement;
}

std::string classLMap::acLenseMapHash(void)
{
	std::string f_ref_CurrentPath = g_ref_global_start + "acLenseMapHash";

	ag_StatusLive(f_ref_CurrentPath, "f_LMapHash");
	std::shared_ptr<Cube::CubeHASH_originstring> f_LMapHash = std::make_shared_reflect<Cube::CubeHASH_originstring>();

	f_LMapHash->acClear();

	for(int f_Jet = 0; f_Jet < m_LMap->m_vec_Measure.size(); f_Jet++)
		{
		std::shared_ptr<LMeasure> f_Measure = m_LMap->m_vec_Measure[f_Jet];

		if((f_Measure->m_isInsertID == false) && (f_Measure->m_isOwnerID == false))
			{
			if(f_Measure->m_LMType == LMTYPE_MeasurementINTV1)
				{
				f_LMapHash->acPushInt(f_Measure->m_MeasurementINTV1);
				f_LMapHash->acPushInt(f_Measure->m_StartRange);
				f_LMapHash->acPushInt(f_Measure->m_EndRange);
				f_LMapHash->acPushInt(f_Measure->m_WeightRangetoStart);
				}
			else if(f_Measure->m_LMType == LMTYPE_MeasurementBLTV1)
				{
				f_LMapHash->acPushInt(f_Measure->m_MeasurementBLTV1);
				}
			else
				{
				//throw;; //add debug message
				}
			}
		}

	std::string f_InputResult = f_LMapHash->acGetInput();

	g_hasha.init(); //reset hasher state
	g_hasha.process(f_InputResult.begin(), f_InputResult.end());
	g_hasha.finish();
	picosha2::get_hash_hex_string(g_hasha, f_LMapHash->m_OutputHash);

	return f_LMapHash->m_OutputHash;
}

std::shared_ptr<Qcom> classLMap::acGen_com_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_FromEcom";

	int f_ComID = -1551;

	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	if((ac_recordMeasurementBLTV1(1, 1, true/*(f_Save_Com->m_ID > 0) ? true : false*/, f_ElementIndex) == true) || 1)
		{
		if(f_Save_Com->m_ID > 0)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(1, 1, true, f_ElementIndex);

			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			//obtain qcom db index
			f_ComID = ac_recordMeasurementINTS(f_Save_Com->m_ID, f_ElementIndex, true);
			}
		else
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);
			}

		ag_StatusLive(f_ref_CurrentPath, "f_com", true);
		std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

		f_com->m_ID = f_ComID;

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		std::string f_VarNameA = ac_recordMeasurement(f_Save_Com->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		f_com->m_birthcomid = ac_recordMeasurementINTS(f_Save_Com->m_birthcomid, f_ElementIndex, true);

		std::string f_Boss_String = ag_StrUsingFloat(g_BossLVLMin);
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		std::string f_BossStr = ac_recordMeasurementFLTV1(f_ElementIndex, f_Boss_String);
		f_com->m_BossLVLMin = atof(f_BossStr.c_str());

		std::string f_X_String = ag_StrUsingFloat(f_Save_Com->m_position->m_X);
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		std::string f_X_Str = ac_recordMeasurementFLTV1(f_ElementIndex, f_X_String);
		f_com->m_position->m_X = atof(f_X_Str.c_str());

		std::string f_Y_String = ag_StrUsingFloat(f_Save_Com->m_position->m_Y);
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		std::string f_Y_Str = ac_recordMeasurementFLTV1(f_ElementIndex, f_Y_String);
		f_com->m_position->m_Y = atof(f_Y_Str.c_str());

		std::string f_CostString = ag_StrUsingFloat(f_Save_Com->m_Cost);
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		std::string f_Cost_Str = ac_recordMeasurementFLTV1(f_ElementIndex, f_CostString);
		f_com->m_Cost = atof(f_Cost_Str.c_str());

		f_com->m_name = f_VarNameA;

		//notice: no element pull prior to measure key
		f_com->m_owner = ac_recordMeasureKey(f_Save_Com->m_owner, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_description.length() > 0) ? true : false, f_ElementIndex) == true)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			f_com->m_description = ac_recordMeasurement(f_Save_Com->m_description, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_parentcomid = ac_recordMeasurementINTS(f_Save_Com->m_parentcomid, f_ElementIndex);

		f_com->m_rebuild = true;
		f_com->m_Save = true;

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_com->m_VoteScore = ac_recordMeasurementINTS(f_Save_Com->m_VoteScore, f_ElementIndex);

		  ////////////////////////////
		 //
		// Generation Script Gen
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_genScript != nullptr) ? true : false, f_ElementIndex) == true)
			{
			f_com->m_genScript = acGen_gen_FromEcom(f_Save_Com, 0, f_ElementMax, f_ElementMax, f_Depth, f_Target);

			g_QcomManager->m_vec_GenScript.push_back(f_com->m_genScript);
			}

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_Frame_ESLFunction != nullptr) ? true : false, f_ElementIndex) == true)
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_Frame_ESLFunction, f_Save_Com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

			f_com->m_Frame_ESLFunction = f_Function;

			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}

		//Insert Change Element restriction or other share entirely at this point
		int f_XY = 0;
		bool f_ScanFunc = true;
		while(f_ScanFunc == true)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			f_ScanFunc = ac_recordMeasurementBLTV1(1, 1, (f_XY < f_Save_Com->m_vec_ESLFunction.size()) ? true : false, f_ElementIndex);

			if(f_ScanFunc == true)
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_vec_ESLFunction[f_XY], f_Save_Com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);
			
				f_com->m_vec_ESLFunction.push_back(f_Function);

				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}

			f_XY++;
			}
		
#ifdef ESL_CIRCUIT_APPENDIX
		int f_Helly = 0;
		bool f_ScanInput = true;
		while(f_ScanInput == true)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			f_ScanInput = ac_recordMeasurementBLTV1(1, 1, (f_Helly < f_Save_Com->m_vec_Input.size()) ? true : false, f_ElementIndex);

			if(f_ScanInput == true)
				{ //levels of element selection range
				std::shared_ptr<QcomInput> f_COM_Input = acGen_com_input_FromEcom(f_Save_Com->m_vec_Input[f_Helly], f_Save_Com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

				f_COM_Input->m_owner = f_Save_Com->m_owner;
				f_COM_Input->m_ComID = f_Save_Com->m_ID;
				f_COM_Input->m_birthcomid = f_Save_Com->m_ID;

				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction != nullptr) ? true : false, f_ElementIndex) == true)
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction->m_vec_InitLineOrdered.size() > 0) ? true : false, f_ElementIndex) == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction, f_Save_Com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

						f_COM_Input->m_InputFunction = f_Function;

						g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
						}
					}

				f_com->m_vec_Input.push_back(f_COM_Input);
				g_QcomManager->m_vec_Input.push_back(f_COM_Input);
				}

			f_Helly++;
			}

		f_Helly = 0;
		bool f_ScanOutput = true;
		while(f_ScanOutput == true)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			f_ScanOutput = ac_recordMeasurementBLTV1(1, 1, (f_Helly < f_Save_Com->m_vec_Output.size()) ? true : false, f_ElementIndex);

			if(f_ScanOutput == true)
				{ //levels of element selection range
				std::shared_ptr<QcomOutput> f_COM_Output = acGen_com_output_FromEcom(f_Save_Com->m_vec_Output[f_Helly], f_Save_Com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target, f_WireContractOverride);

				f_COM_Output->m_owner = f_Save_Com->m_owner;
				f_COM_Output->m_ComID = f_Save_Com->m_ID;
				f_COM_Output->m_birthcomid = f_Save_Com->m_ID;

				f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction != nullptr) ? true : false, f_ElementIndex) == true)
					{
					f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

					if(ac_recordMeasurementBLTV1(1, 1, (f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction->m_vec_InitLineOrdered.size() > 0) ? true : false, f_ElementIndex) == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = acGen_com_function_FromEcom(f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction, f_Save_Com, f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

						f_COM_Output->m_OutputFunction = f_Function;

						g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
						}
					}


				f_com->m_vec_Output.push_back(f_COM_Output);
				g_QcomManager->m_vec_Output.push_back(f_COM_Output);
				}

			f_Helly++;
			}
#else
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		ac_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);
#endif

#if 0
		f_com->acWire(f_Hesh, 0, f_ElementMax);
#endif

		//Insert Change Element restriction or other share entirely at this point
		f_XY = 0;
		bool f_ScanCom = true;
		while(f_ScanCom == true)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			f_ScanCom = ac_recordMeasurementBLTV1(1, 1, (f_XY < f_Save_Com->m_vec_Qcom.size()) ? true : false, f_ElementIndex);

			if(f_ScanCom == true)
				{
				std::shared_ptr<Qcom> f_Add_Com = acGen_com_FromEcom(f_Save_Com->m_vec_Qcom[f_XY], f_StartAD, f_EndAD, f_ElementMax, f_Depth, f_Target);

#if 0
				f_Add_Com->m_parentcomid = f_com->m_ID;
#endif

				f_com->m_vec_Qcom.push_back(f_Add_Com);

				g_QcomManager->m_vec_Qcom.push_back(f_Add_Com);
				}

			f_XY++;
			}

		return f_com;
		}
	else //comid structure build
		{
		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		//obtain qcom db index
		f_ComID = ac_recordMeasurementINTS(f_Save_Com->m_ID, f_ElementIndex);

		if((m_GlobalScope == true) && (f_ComID > 0)) //global built from share and ids
			{
#if 0
			//switch on proper index db build here...
			ag_StatusLive(f_ref_CurrentPath, "f_com", true);
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>(f_ComID);
			//add bosslvl check to Qcom load
#else
			//appeasement com return
			ag_StatusLive(f_ref_CurrentPath, "f_com", true);
			std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

			f_com->m_ID = f_ComID;
			f_com->m_name = "BUILD:ME";
#endif	

			return f_com;
			}
		}

	//appeasement return
	ag_StatusLive(f_ref_CurrentPath, "f_com", true);
	std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

	f_com->m_name = "REPLACE:ME";

	return f_com;
}

std::shared_ptr<QcomInput> classLMap::acGen_com_input_FromEcom(std::shared_ptr<QcomInput> f_Save_Input, std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_input_FromEcom";

	ag_StatusLive(f_ref_CurrentPath, "f_comInput");
	std::shared_ptr<QcomInput> f_comInput = std::make_shared_reflect<QcomInput>();
	
	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
	std::string f_VarNameA = ac_recordMeasurement(f_Save_Input->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	std::string f_Pos_X_String = ag_StrUsingFloat(f_Save_Input->m_position->m_X);
	f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
	std::string f_PosXStr = ac_recordMeasurementFLTV1(f_ElementIndex, f_Pos_X_String);
	f_comInput->m_position->m_X = atof(f_PosXStr.c_str());

	std::string f_Pos_Y_String = ag_StrUsingFloat(f_Save_Input->m_position->m_Y);
	f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
	std::string f_PosYStr = ac_recordMeasurementFLTV1(f_ElementIndex, f_Pos_Y_String);
	f_comInput->m_position->m_Y = atof(f_PosYStr.c_str());

	f_comInput->m_name = f_VarNameA;
	f_comInput->m_ID = -5;
	f_comInput->m_birthcomid = f_Save_Com->m_birthcomid;
	f_comInput->m_ComID = f_Save_Com->m_ID;
	f_comInput->m_QamID = f_Save_Com->m_QamID;
	f_comInput->m_QamLevel = f_Save_Com->m_QamLevel;
	f_comInput->m_owner = f_Save_Com->m_owner;
	f_comInput->m_description = "";
	f_comInput->m_rebuild = true;
	f_comInput->m_Save = true;

	return f_comInput;
}

std::shared_ptr<QcomOutput> classLMap::acGen_com_output_FromEcom(std::shared_ptr<QcomOutput> f_Save_Output, std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_output_FromEcom";

	ag_StatusLive(f_ref_CurrentPath, "f_comOutput");
	std::shared_ptr<QcomOutput> f_comOutput = std::make_shared_reflect<QcomOutput>();

	int f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
	std::string f_VarNameA = ac_recordMeasurement(f_Save_Output->m_name, f_ElementIndex, f_StartAD, f_EndAD, f_ElementMax, f_Depth);

	std::string f_Pos_X_String = ag_StrUsingFloat(f_Save_Output->m_position->m_X);
	f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
	std::string f_PosXStr = ac_recordMeasurementFLTV1(f_ElementIndex, f_Pos_X_String);
	f_Save_Output->m_position->m_X = atof(f_PosXStr.c_str());

	std::string f_Pos_Y_String = ag_StrUsingFloat(f_Save_Output->m_position->m_Y);
	f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
	std::string f_PosYStr = ac_recordMeasurementFLTV1(f_ElementIndex, f_Pos_Y_String);
	f_Save_Output->m_position->m_Y = atof(f_PosYStr.c_str());

	f_comOutput->m_name = f_VarNameA;
	f_comOutput->m_ID = -5;
	f_comOutput->m_birthcomid = f_Save_Com->m_birthcomid;
	f_comOutput->m_ComID = f_Save_Com->m_ID;
	f_comOutput->m_QamID = f_Save_Com->m_QamID;
	f_comOutput->m_QamLevel = f_Save_Com->m_QamLevel;
	f_comOutput->m_owner = f_Save_Com->m_owner;
	f_comOutput->m_description = "";
	f_comOutput->m_rebuild = true;
	f_comOutput->m_Save = true;

	return f_comOutput;
}

std::shared_ptr<Qcom_eslfunction> classTarget_Ecom::acGen_com_function_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_function_FromHesh";

	if(m_Collection->m_vec_Element.size() < f_Hesh->m_adIndex.size())
		{
		for(int f_Count = m_Collection->m_vec_Element.size(); f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
			{
			ag_StatusLive(f_ref_CurrentPath, "f_Element");
			std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Count]);

			m_Collection->m_vec_Element.push_back(f_Element);

			m_Collection->m_idx_vec_Element++;
			}
		}

	int f_ConsensusID = ac_takeMeasurementINTS(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	int f_FunctionType = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, FuncExec_Total, 0, 3);

	int f_LineCount = 0;

	ag_StatusLive(f_ref_CurrentPath, "f_Function");
	std::shared_ptr<classFunction> f_Function = std::make_shared_reflect<classFunction>();

	f_Function->m_Type = f_FunctionType;

	if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
		{
		return f_Function->acConvert(f_Com);
		}

	if(f_ConsensusID != ECOIN_CONSENSUS_ID)
		{
		return f_Function->acConvert(f_Com);
		}

	if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
		{
		std::string f_ClassNameA = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
		std::string f_ClassNameB = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_StringE = "ClassStart%%" + f_ClassNameA + "%%" + f_ClassNameB + "%%";

		f_Function->m_Type = FuncExec_System_Load;

		f_Function->m_ClassName = f_ClassNameB;

		f_StringE += ESL_LINE_ENDING;

		f_Function->m_vec_String += f_StringE;

		ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
		std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringE, ESL_INSTA_TYPE_CLASS_DEF);

		f_Function->m_vec_Insta.push_back(f_InstaVs);
		f_Function->m_idx_vec_Insta++;

		f_LineCount++;
		}

	if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
		{
		f_Function->m_vec_String += acGen_Var_fromHesh();
		}

	if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 2) == true)
		{
		std::string f_FunctionNameA = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
		std::string f_FunctionNameB = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_StringEL = "FuncDef%%" + f_FunctionNameA + "&*" + f_FunctionNameB + "%%";

		f_Function->m_Name = f_FunctionNameB;

		ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
		std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringEL, ESL_INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_InstaVs);
		f_Function->m_idx_vec_Insta++;

		bool f_argScan = true;
		while(f_argScan == true)
			{
			f_argScan = ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1);

			if(f_argScan == true)
				{
				std::string f_ArgParam = acGen_Var_fromHesh();

				f_StringEL += f_ArgParam;
				}
			}

		f_StringEL += ESL_LINE_ENDING;

		f_Function->m_vec_String += f_StringEL;

		f_LineCount++;
		}
		
	acResetLine();

	m_functionScan = true;
	while(m_functionScan == true)
		{
		bool f_Contact = false;
				
		int f_InstaType = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, ESL_INSTA_TYPE_COUNT, 0, 3);

		if(f_InstaType == ESL_INSTA_TYPE_VAR_DEF) //un
			{
			std::string f_StringB = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			f_StringB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringB;
			f_LineCount++;
					
			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_SYS_DEF) //un
			{
			std::string f_StringB = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			f_StringB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringB;
			f_LineCount++;
					
			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_CONDITIONAL) //un
			{
			//Place LHS
			std::string f_StringVarA = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
			std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringVarA, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaA);
			f_Function->m_idx_vec_Insta++;

			int f_FingerCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 5, 0, 3);

			std::string f_Name = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_StringB = f_StringVarA + "Cond%%";
						
			switch(f_FingerCount)
				{
				case MuCon_Equal:
					{
					f_StringB += "==^^";
					}break;
				case MuCon_NotEqual:
					{
					f_StringB += "!=^^";
					}break;
				case MuCon_SmallThan:
					{
					f_StringB += "<<^^";
					}break;
				case MuCon_GreatThan:
					{
					f_StringB += ">>^^";
					}break;
				case MuCon_SmallThanorEqual:
					{
					f_StringB += "<=^^";
					}break;
				case MuCon_GreatThanorEqual:
					{
					f_StringB += ">=^^";
					}break;
				}

			f_StringB += f_Name + "%%";

			std::string f_StringVarB = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_instaStringVarB");
			std::shared_ptr<classInsta> f_instaStringVarB = std::make_shared_reflect<classInsta>(f_StringVarB, ESL_INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_instaStringVarB);
			f_Function->m_idx_vec_Insta++;

			f_StringB += f_StringVarB;

			ag_StatusLive(f_ref_CurrentPath, "f_StringB");
			std::shared_ptr<classInsta> f_InstaAB = std::make_shared_reflect<classInsta>(f_StringB, ESL_INSTA_TYPE_CONDITIONAL);

			f_Function->m_vec_Insta.push_back(f_InstaAB);
			f_Function->m_idx_vec_Insta++;

			f_StringB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringB;
			f_LineCount++;

			std::string f_StringFB = "Function%%EcomNative&*Success%%";

			ag_StatusLive(f_ref_CurrentPath, "f_InstaC");
			std::shared_ptr<classInsta> f_InstaC = std::make_shared_reflect<classInsta>(f_StringFB, ESL_INSTA_TYPE_FUNC_DEF);

			f_Function->m_vec_Insta.push_back(f_InstaC);
			f_Function->m_idx_vec_Insta++;

			f_StringFB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringFB;
			f_LineCount++;

			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_OPER) //un
			{
			//Place LHS
			std::string f_StringVarA = acGen_Var_fromHesh();

			std::string f_StringAB = "";

			ag_StatusLive(f_ref_CurrentPath, "f_StringVarA");
			std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringVarA, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaA);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVarA;

			int f_FingerCount = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 9, 0, 3);

			//operator take
			std::string f_StringABCF = "Opr%%";

			std::string f_Name = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			switch(f_FingerCount)
				{
				case MuOpr_Plus:
					{
					f_StringABCF += "Plus**" + f_Name;
					}break;
				case MuOpr_Minus:
					{
					f_StringABCF += "Minus**" + f_Name;
					}break;
				case MuOpr_Multiply:
					{
					f_StringABCF += "Mul**" + f_Name;
					}break;
				case MuOpr_Divide:
					{
					f_StringABCF += "Div**" + f_Name;
					}break;
				case MuOpr_Bitleft:
					{
					f_StringABCF += "<<**" + f_Name;
					}break;
				case MuOpr_Bitright:
					{
					f_StringABCF += ">>**" + f_Name;
					}break;
				case MuOpr_Modulus:
					{
					f_StringABCF += "Mod**" + f_Name;
					}break;
				case MuOpr_Copy:
					{
					f_StringABCF += "Copy**" + f_Name;
					}break;
				case MuOpr_Equals:
					{
					f_StringABCF += "Equals**" + f_Name;
					}break;
				case MuOpr_Random:
					{
					f_StringABCF += "Random**" + f_Name;
					}break;
				}

			f_StringABCF += "%%";

			f_StringAB += f_StringABCF;

			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true)
				{
				//Place RHS
				std::string f_StringVarB = acGen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaFS");
				std::shared_ptr<classInsta> f_InstaB = std::make_shared_reflect<classInsta>(f_StringVarB, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaB);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringVarB;
				}

			ag_StatusLive(f_ref_CurrentPath, "f_StringAB");
			std::shared_ptr<classInsta> f_InstaAB = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_OPER);

			f_Function->m_vec_Insta.push_back(f_InstaAB);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_LOOP_DEF) //un
			{
			std::string f_forName = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_StringF = "For%% " + f_forName + "%%";

			std::string f_StringAB = "";

			//Place Var 1
			std::string f_StringVar1 = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB1");
			std::shared_ptr<classInsta> f_InstaB1 = std::make_shared_reflect<classInsta>(f_StringVar1, ESL_INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB1);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVar1;

			//Place Var 2
			std::string f_StringVar2 = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB");
			std::shared_ptr<classInsta> f_InstaB2 = std::make_shared_reflect<classInsta>(f_StringVar2, ESL_INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB2);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVar2;

			//Place Var 3
			std::string f_StringVar3 = acGen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB3");
			std::shared_ptr<classInsta> f_InstaB3 = std::make_shared_reflect<classInsta>(f_StringVar3, ESL_INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB3);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVar3;

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_LOOP_DEF);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;
					
			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_FUNC_CALL) //un
			{
			bool f_returnarg = ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1); //has return arg

			std::string f_StringAB = "";

			if(f_returnarg == true)
				{
				//Place Var 1
				std::string f_StringReturnVar = acGen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaR");
				std::shared_ptr<classInsta> f_InstaR = std::make_shared_reflect<classInsta>(f_StringReturnVar, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaR);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringReturnVar;
				}
				
			std::string f_FunctionName1 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_FunctionName2 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_FunctionString = "Fcn%%" + f_FunctionName1 + "&*" + f_FunctionName2 + "%%";

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB");
			std::shared_ptr<classInsta> f_InstaB = std::make_shared_reflect<classInsta>(f_FunctionString, ESL_INSTA_TYPE_FUNC_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_FunctionString;

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1);

				if(m_arguScan == true)
					{
					//Place Argument Var
					std::string f_StringArgVar = acGen_Var_fromHesh();

					ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
					std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringArgVar, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA);
					f_Function->m_idx_vec_Insta++;

					f_StringAB += f_StringArgVar;
					}
				}

			f_StringAB += ESL_LINE_ENDING;
					
			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;
					
			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_FUNC_DEF) //un
			{
			bool f_returnarg = ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1); //has return arg

			std::string f_StringAB = "";

			if(f_returnarg == true)
				{
				//Place Var 1
				std::string f_StringReturnVar = acGen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaR");
				std::shared_ptr<classInsta> f_InstaR = std::make_shared_reflect<classInsta>(f_StringReturnVar, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaR);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringReturnVar;
				}

			std::string f_FunctionDefName1 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_FunctionDefName2 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_StringEB = "FuncDef%%" + f_FunctionDefName1 + "&*" + f_FunctionDefName2 + "%%";

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringEB, ESL_INSTA_TYPE_FUNC_DEF);
				
			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringEB;

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1);

				if(m_arguScan == true)
					{
					//Place Argument Var
					std::string f_StringArgVar = acGen_Var_fromHesh();

					ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
					std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringArgVar, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA);
					f_Function->m_idx_vec_Insta++;

					f_StringAB += f_StringArgVar;
					}
				}

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_CLASS_DEF) //un
			{
			std::string f_ClassStartName = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_ClassStartName2 = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_StringAB = "ClassStart%%" + f_ClassStartName + "&*" + f_ClassStartName2 + "%%";

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_CLASS_DEF);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;
				
			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true; //?
			}
		else if(f_InstaType == ESL_INSTA_TYPE_CLASSVAR_DEF) //un
			{
			std::string f_ClassVarType = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASSVAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_ClassVarName = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_CLASSVAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_StringAB = "ClassVar%%" + f_ClassVarType + "&$" + f_ClassVarName + "%%";

			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1) == true) // has reflection
				{
				std::string f_ReflectionVar1 = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				std::string f_ReflectionVar2 = ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				f_StringAB += f_ReflectionVar1 + "#?" + f_ReflectionVar2 + "#?";
				}

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_CLASSVAR_DEF);
				
			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1);

				if(m_arguScan == true)
					{
					//Place Argument Var
					std::string f_StringArgVar = acGen_Var_fromHesh();

					ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
					std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringArgVar, ESL_INSTA_TYPE_VAR_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaA);
					f_Function->m_idx_vec_Insta++;

					f_StringAB += f_StringArgVar;
					}
				}

			f_StringAB += ESL_LINE_ENDING;
				
			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_TEMPLATE) //un
			{
			std::string f_StringAB = "Template%%";

			ag_StatusLive(f_ref_CurrentPath, "f_InstaT");
			std::shared_ptr<classInsta> f_InstaT = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_TEMPLATE);

			f_Function->m_vec_Insta.push_back(f_InstaT);
			f_Function->m_idx_vec_Insta++;

			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 7) == true)
				{
				//Place Argument Var
				std::string f_StringArgVar = acGen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
				std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringArgVar, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringArgVar;
				}

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true;
			}
		else if(f_InstaType == ESL_INSTA_TYPE_RETURN) //un
			{
			std::string f_StringAB = "Return%%";

			if(ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 7))
				{
				//Place Argument Var
				std::string f_StringArgVar = acGen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
				std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringArgVar, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringArgVar;
				}

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;
			f_LineCount++;

			f_Contact = true;
			}
#ifdef ECOIN_DEBUG_BREAKS
		else
			{
			__debugbreak();
			}
#endif

		m_functionScan = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 7);

		if(m_functionScan == false)
			{
			f_Function->m_vec_String.pop_back();
			}
		}

#ifdef ESL_SPEED_BENCH
	std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert(f_Com, true); //com, lean benchmarking speed
#else
	std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert(f_Com, false); //com, full load
#endif

	return f_func;
}

shared_ptr<Qcom_eslfunction> classFunction::acConvert(shared_ptr<Qcom> f_Com, bool f_Lean)
{
	std::string f_ref_CurrentPath = "classFunction::acConvert";

	ag_StatusLive(f_ref_CurrentPath, "f_ESLfunc", true);
	shared_ptr<Qcom_eslfunction> f_ESLfunc = make_shared_reflect<Qcom_eslfunction>();

	f_ESLfunc->m_ID = -1551;

	f_ESLfunc->m_Save = false;

	f_ESLfunc->m_ComID = f_Com->m_ID;

	f_ESLfunc->m_birthcomid = f_Com->m_birthcomid;

	f_ESLfunc->m_QamID = f_Com->m_QamID;

	f_ESLfunc->m_QamLevel = f_Com->m_QamLevel;

	f_ESLfunc->m_owner = f_Com->m_owner;

	f_ESLfunc->m_name = m_Name;

	f_ESLfunc->m_classname = m_ClassName;

	f_ESLfunc->m_typed = 0;

	bool f_Some = false;
	bool f_StartLine = true;
	std::string f_Carriage = "";

	if(f_Lean == false)
		{
		for(int f_XY = 0; f_XY < m_vec_String.length(); f_XY++)
			{
			char f_c = m_vec_String.at(f_XY);

			if((f_c == '\n') || (f_c == '\r') || (f_XY >= (m_vec_String.length() - 1)))
				{
				if(f_StartLine == true)
					{
					if(f_Some == true)
						{
						f_ESLfunc->m_vec_InitLineOrdered.push_back(f_Carriage);
						f_Carriage.clear();
						f_Some = false;
						}
					}
				else
					{
					if(f_Some == true)
						{
						f_ESLfunc->m_vec_InitLineOrdered.push_back(f_Carriage);
						f_Carriage.clear();
						f_Some = false;
						}
					}
				}
			else
				{
				f_Carriage.push_back(f_c);
				f_Some = true;
				}
			}
		}

	f_ESLfunc->m_FunctionLine = m_vec_String;

#pragma message("ESL_COMPILE_MODE_EXECUTE is set...!")

	return f_ESLfunc;
}

bool classLMap::ac_ext_Typing_isEqual(int f_Var_Typing, int f_Var_Current_Code)
{
	if(f_Var_Current_Code == f_Var_Typing)
		{
		return true;
		}
	else
		{
		return false;
		}
}

std::vector<std::vector<std::string>> classLMap::ac_ext_eslLine_morf_array(std::string f_LineString)
{
	bool f_SomeC = false;
	std::string f_TextCarriage = "";
	std::string f_CodeCarriage = "";
	std::vector<std::string> f_VecBit;
	std::vector<std::vector<std::string>> f_String_Vector;

	for(int f_XY = 0; f_XY < f_LineString.length(); f_XY++)
		{
		char f_c = f_LineString.at(f_XY);

		if(f_XY == f_LineString.length() - 1) //end of start
			{
			if( (f_c == '&') || (f_c == '%') ||
				(f_c == '#') || (f_c == '/') ||
				(f_c == '*') || (f_c == '^') || (f_c == '$') || (f_c == '?'))
				{
				f_CodeCarriage.push_back(f_c);
				f_SomeC = true;
				}
			
			if(f_SomeC == true)
				{
				f_VecBit.clear();
				f_VecBit.push_back(f_TextCarriage);
				f_VecBit.push_back(f_CodeCarriage);
				f_String_Vector.push_back(f_VecBit);
				f_TextCarriage.clear();
				f_CodeCarriage.clear();
				f_SomeC = false;
				}
			}
		else
			{
			if( (f_c == '&') || (f_c == '%') ||
				(f_c == '#') || (f_c == '/') ||
				(f_c == '*') || (f_c == '^') || (f_c == '$') || (f_c == '?'))
				{
				f_CodeCarriage.push_back(f_c);
				f_SomeC = true;
				}
			else
				{
				if(f_SomeC == true)
					{
					f_VecBit.clear();
					f_VecBit.push_back(f_TextCarriage);
					f_VecBit.push_back(f_CodeCarriage);
					f_String_Vector.push_back(f_VecBit);
					f_TextCarriage.clear();
					f_CodeCarriage.clear();
					f_SomeC = false;
					}

				f_TextCarriage.push_back(f_c);
				}
			}
		}

	return f_String_Vector;
}

int classLMap::ac_ext_Scan_Lines_Keyword_Next(int f_LineCount, int f_morf1, int f_morf2, std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, std::string f_Keyword)
{
	for(int f_LineNo = f_LineCount; f_LineNo < f_Save_Com_Function->m_vec_InitLineOrdered.size(); f_LineNo++)
		{
		std::string f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineNo];

		std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

		if(f_morfarray[f_morf1][f_morf2].compare(f_Keyword) == 0)
			{
			return f_LineNo - f_LineCount;
			}
		}

	return -1;
}

std::string classLMap::acGen_Var_fromEcom(int f_Prec_Type, bool f_Value_Given_Bool, std::string f_Var_Type_String, std::string f_Var_Name_String, std::string f_Var_Value_String)
{
	int f_SIndex_Typ = f_Prec_Type;
	bool f_SValueOn = f_Value_Given_Bool;
	std::string f_ValueString = f_Var_Value_String;

	int f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

	//[0] - VarName
	std::string f_NameString = ac_recordMeasurement(f_Var_Name_String, f_ElementIndex, -1, -1, -1, -1);
	std::string f_VarName = f_NameString;
	std::string f_StringA = "";

	f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

	//[1] - ValueOn
	f_SValueOn = ac_recordMeasurementBLTV1(2, 0, f_SValueOn, f_ElementIndex);

	int f_VarType = agFind_VarType_from_Precision(agFind_Precision(f_Var_Type_String));

	//Transient Check
	if(f_VarType >= MuVar_ClassVar_Class)
		{
		f_SIndex_Typ = ESL_MORF_TYPE_CLSVAR;
		}

	f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

	//Varso...!
	if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ESL_MORF_TYPE_VAR, f_SIndex_Typ), f_ElementIndex) == true)
		{
		f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

		//Float Parameter
		if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_FLOAT, f_VarType), f_ElementIndex) == true)
			{
			if(f_SValueOn == true)
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(f_ElementIndex, f_ValueString).c_str());

				f_StringA += "Var%%float&&" + f_VarName + "%%" + f_Char + "&%";
				}
			else
				{
				f_StringA += "Var%%float&&" + f_VarName + "%%";
				}
			}
		else
			{
			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			//Int Parameter
			if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_INT, f_VarType), f_ElementIndex) == true)
				{
				if(f_SValueOn == true)
					{
					char f_Char[150];
					FillChar(f_Char, 150);

					int f_ValueNr = ::atoi(f_ValueString.c_str());

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					::sprintf(f_Char, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%int&&" + f_VarName + "%%" + f_Char + "&%";
					}
				else
					{
					f_StringA += "Var%%int&&" + f_VarName + "%%";
					}
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				//String Parameter
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_STRING, f_VarType), f_ElementIndex) == true)
					{
					if(f_SValueOn == true)
						{
						char f_Char[150];
						FillChar(f_Char, 150);

						std::string f_ValueNr = f_ValueString;

						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						::sprintf(f_Char, "%s", ac_recordMeasurement(f_ValueNr, f_ElementIndex, -1, -1, -1, -1).c_str());

						f_StringA += "Var%%string&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_StringA += "Var%%string&&" + f_VarName + "%%";
						}
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					//String Parameter
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_UINT, f_VarType), f_ElementIndex) == true)
						{
						if(f_SValueOn == true)
							{
							char f_Char[150];
							FillChar(f_Char, 150);

							int f_ValueNr = ::atoi(f_ValueString.c_str());

							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

							f_StringA += "Var%%uint&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_StringA += "Var%%uint&&" + f_VarName + "%%";
							}
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						//String Parameter
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_CHAR, f_VarType), f_ElementIndex) == true)
							{
							if(f_SValueOn == true)
								{
								char f_Char[150];
								FillChar(f_Char, 150);

								int f_ValueNr = ::atoi(f_ValueString.c_str());

								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

								f_StringA += "Var%%char&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_StringA += "Var%char&&" + f_VarName + "%%";
								}
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							//String Parameter
							if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_UCHAR, f_VarType), f_ElementIndex) == true)
								{
								if(f_SValueOn == true)
									{
									char f_Char[150];
									FillChar(f_Char, 150);

									int f_ValueNr = ::atoi(f_ValueString.c_str());

									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

									f_StringA += "Var%%uchar&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_StringA += "Var%%uchar&&" + f_VarName + "%%";
									}
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								//String Parameter
								if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_DOUBLE, f_VarType), f_ElementIndex) == true)
									{
									if(f_SValueOn == true)
										{
										char f_Char[150];
										FillChar(f_Char, 150);

										std::string f_ValueNr = f_ValueString;

										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										::sprintf(f_Char, "%s", ac_recordMeasurementFLTV1(f_ElementIndex, f_ValueString).c_str());

										f_StringA += "Var%%double&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_StringA += "Var%double&&" + f_VarName + "%%";
										}
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									//String Parameter
									if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_BOOL, f_VarType), f_ElementIndex) == true)
										{
										if(f_SValueOn == true)
											{
											char f_Char[150];
											FillChar(f_Char, 150);

											bool f_ValueNr = ::atoi(f_ValueString.c_str());

											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											::sprintf(f_Char, "%i", ac_recordMeasurementBLTV1(5, 0, f_ValueNr, f_ElementIndex));

											f_StringA += "Var%%bool&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_StringA += "Var%bool&&" + f_VarName + "%%";
											}
										}
									}
								}
							}
						}
					}
				}
			}
		} //END TYPE 'Var'
	else
		{ //Systema...! 'Sys'
		f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

		if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ESL_MORF_TYPE_SYS, f_SIndex_Typ), f_ElementIndex) == true)
			{
			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			//Float Parameter
			if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_FLOAT, f_VarType), f_ElementIndex) == true)
				{
				if(f_SValueOn == true)
					{
					char f_Char1[150];
					FillChar(f_Char1, 150);

					float f_ValueNr = atof(f_ValueString.c_str());

					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					::sprintf(f_Char1, "%s", ac_recordMeasurementFLTV1(f_ElementIndex, f_ValueString).c_str());

					f_StringA += "Sys%%float&&" + f_VarName + "%%" + f_Char1 + "&%";
					}
				else
					{
					f_StringA += "Sys%%float&&" + f_VarName + "%%";
					}
				}
			else //INT SYS
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				//Int Parameter
				if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_INT, f_VarType), f_ElementIndex) == true)
					{
					if(f_SValueOn == true)
						{
						char f_Char2[150];
						FillChar(f_Char2, 150);

						int f_ValueNr = ::atoi(f_ValueString.c_str());
						
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						::sprintf(f_Char2, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

						f_StringA += "Sys%%int&&" + f_VarName + "%%" + f_Char2 + "&%";
						}
					else
						{
						f_StringA += "Sys%%int&&" + f_VarName + "%%";
						}
					}
				else
					{
					f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

					//String Parameter
					if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_STRING, f_VarType), f_ElementIndex) == true)
						{
						if(f_SValueOn == true)
							{
							char f_Char3[150];
							FillChar(f_Char3, 150);

							std::string f_ValueNr = f_ValueString;

							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							::sprintf(f_Char3, "%s", ac_recordMeasurement(f_ValueNr, f_ElementIndex, -1, -1, -1, -1).c_str());

							f_StringA += "Sys%%string&&" + f_VarName + "%%" + f_Char3 + "&%";
							}
						else
							{
							f_StringA += "Sys%%string&&" + f_VarName + "%%";
							}
						}
					else
						{
						f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

						//UInt Parameter
						if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_UINT, f_VarType), f_ElementIndex) == true)
							{
							if(f_SValueOn == true)
								{
								char f_Char4[150];
								FillChar(f_Char4, 150);

								int f_ValueNr = ::atoi(f_ValueString.c_str());
						
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								::sprintf(f_Char4, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

								f_StringA += "Sys%%uint&&" + f_VarName + "%%" + f_Char4 + "&%";
								}
							else
								{
								f_StringA += "Sys%%uint&&" + f_VarName + "%%";
								}
							}
						else
							{
							f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

							//String Parameter
							if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_CHAR, f_VarType), f_ElementIndex) == true)
								{
								if(f_SValueOn == true)
									{
									char f_Char5[150];
									FillChar(f_Char5, 150);

									int f_ValueNr = ::atoi(f_ValueString.c_str());

									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									::sprintf(f_Char5, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

									f_StringA += "Sys%%char&&" + f_VarName + "%%" + f_Char5 + "&%";
									}
								else
									{
									f_StringA += "Sys%%char&&" + f_VarName + "%%";
									}
								}
							else
								{
								f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

								//String Parameter
								if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_UCHAR, f_VarType), f_ElementIndex) == true)
									{
									if(f_SValueOn == true)
										{
										char f_Char6[150];
										FillChar(f_Char6, 150);

										int f_ValueNr = ::atoi(f_ValueString.c_str());

										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										::sprintf(f_Char6, "%i", ac_recordMeasurementINTS(f_ValueNr, f_ElementIndex));

										f_StringA += "Sys%%uchar&&" + f_VarName + "%%" + f_Char6 + "&%";
										}
									else
										{
										f_StringA += "Sys%%uchar&&" + f_VarName + "%%";
										}
									}
								else
									{
									f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

									//Double Parameter
									if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_DOUBLE, f_VarType), f_ElementIndex) == true)
										{
										if(f_SValueOn == true)
											{
											char f_Char7[150];
											FillChar(f_Char7, 150);

											float f_ValueNr = atof(f_ValueString.c_str());
						
											f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

											::sprintf(f_Char7, "%s", ac_recordMeasurementFLTV1(f_ElementIndex, f_ValueString).c_str());

											f_StringA += "Sys%%double&&" + f_VarName + "%%" + f_Char7 + "&%";
											}
										else
											{
											f_StringA += "Sys%%double&&" + f_VarName + "%%";
											}
										}
									else
										{
										f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

										//String Parameter
										if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ECN_VAR_BOOL, f_VarType), f_ElementIndex) == true)
											{
											if(f_SValueOn == true)
												{
												char f_Char8[150];
												FillChar(f_Char8, 150);

												bool f_ValueNr = ::atoi(f_ValueString.c_str());

												f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

												::sprintf(f_Char8, "%i", ac_recordMeasurementBLTV1(5, 0, f_ValueNr, f_ElementIndex));

												f_StringA += "Sys%%bool&&" + f_VarName + "%%" + f_Char8 + "&%";
												}
											else
												{
												f_StringA += "Sys%%bool&&" + f_VarName + "%%";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			} // END TYPE 'Sys'
		else
			{ // ClassVar Singles
			f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

			if(ac_recordMeasurementBLTV1(2, 0, ac_ext_Typing_isEqual(ESL_MORF_TYPE_CLSVAR, f_SIndex_Typ), f_ElementIndex) == true)
				{
				f_ElementIndex = acPull_gen_ElementID(-1, -1, -1, -1);

				std::string f_TypeString = ac_recordMeasurement(f_Var_Type_String, f_ElementIndex, -1, -1, -1, -1);

				f_StringA += "ClassVar%%" + f_TypeString + "&&" + f_VarName + "%%";
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak(); //add debug message SIndex Type out of bounds
				}
#endif
			}
		}

	return f_StringA;
}

std::string classTarget_Ecom::acGen_Var_fromHesh(void)
{	
	//[0] - VarName
	std::string f_NameString = ac_takeMeasurement(-1, -1, -1, -1);

	std::string f_VarName = f_NameString;

	//[1] - ValueOn
	bool f_SValueOn = ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1);

	std::string f_StringA = "";

	//[2] - Varso
	if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
		{
		char f_Char[150];

		FillChar(f_Char, 150);

		//Float Parameter
		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
			{
			if(f_SValueOn == true)
				{
				::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1));

				f_StringA += "Var%%float&&" + f_VarName + "%%" + f_Char + "&%";
				}
			else
				{
				f_StringA += "Var%%float&&" + f_VarName + "%%";
				}
			}
		else
			{
			//Int Parameter
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
				{
				if(f_SValueOn == true)
					{
					::sprintf(f_Char, "%i", ac_takeMeasurementINTS(-1, -1, -1, -1));

					f_StringA += "Var%%int&&" + f_VarName + "%%" + f_Char + "&%";
					}
				else
					{
					f_StringA += "Var%%int&&" + f_VarName + "%%";
					}
				}
			else
				{
				//String Parameter
				if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
					{
					if(f_SValueOn == true)
						{
						::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

						f_StringA += "Var%%string&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_StringA += "Var%%string&&" + f_VarName + "%%";
						}
					}
				else
					{
					//UInt Parameter
					if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
						{
						if(f_SValueOn == true)
							{
							::sprintf(f_Char, "%i", ac_takeMeasurementINTS(-1, -1, -1, -1));

							f_StringA += "Var%%uint&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_StringA += "Var%%uint&&" + f_VarName + "%%";
							}
						}
					else
						{
						//char Parameter
						if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
							{
							if(f_SValueOn == true)
								{
								::sprintf(f_Char, "%i", ac_takeMeasurementINTS(-1, -1, -1, -1));

								f_StringA += "Var%%char&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_StringA += "Var%%char&&" + f_VarName + "%%";
								}
							}
						else
							{
							//UChar Parameter
							if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
								{
								if(f_SValueOn == true)
									{
									::sprintf(f_Char, "%i", ac_takeMeasurementINTS(-1, -1, -1, -1));

									f_StringA += "Var%%uchar&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_StringA += "Var%%uchar&&" + f_VarName + "%%";
									}
								}
							else
								{
								//double Parameter
								if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
									{
									if(f_SValueOn == true)
										{
										::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1));

										f_StringA += "Var%%double&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_StringA += "Var%%double&&" + f_VarName + "%%";
										}
									}
								else
									{
									//bool Parameter
									if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
										{
										if(f_SValueOn == true)
											{
											::sprintf(f_Char, "%i", ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1));

											f_StringA += "Var%%bool&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_StringA += "Var%%bool&&" + f_VarName + "%%";
											}
										}
									}
								}
							}
						}
					}
				}
			}
		} //END TYPE 'Var'
	else
		{ //Systema...! 'Sys'
		if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
			{
			char f_Char[150];
			FillChar(f_Char, 150);

			//Float Parameter
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
				{
				if(f_SValueOn == true)
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(-1, -1, -1, -1));

					f_StringA += "Sys%%float&&" + f_VarName + "%%" + f_Char + "&%";
					}
				else
					{
					f_StringA += "Sys%%float&&" + f_VarName + "%%";
					}
				}
			else
				{//Int Parameter
				if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
					{
					if(f_SValueOn == true)
						{
						::sprintf(f_Char, "%i", ac_takeMeasurementINTS(-1, -1, -1, -1));

						f_StringA += "Sys%%int&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_StringA += "Sys%%int&&" + f_VarName + "%%" + f_Char + "&%";
						}
					}
				else
					{//String Parameter
					if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
						{
						::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

						if(f_SValueOn == true)
							{
							f_StringA += "Sys%%string&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_StringA += "Sys%%string&&" + f_VarName + "%%";
							}
						}
					else
						{//uint
						if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
							{
							::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

							if(f_SValueOn == true)
								{
								f_StringA += "Sys%%uint&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_StringA += "Sys%%uint&&" + f_VarName + "%%";
								}
							}
						else
							{
							if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
								{
								::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

								if(f_SValueOn == true)
									{
									f_StringA += "Sys%%char&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_StringA += "Sys%%char&&" + f_VarName + "%%";
									}
								}
							else
								{
								if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
									{
									::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

									if(f_SValueOn == true)
										{
										f_StringA += "Sys%%uchar&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_StringA += "Sys%%uchar&&" + f_VarName + "%%";
										}
									}
								else
									{
									if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
										{
										::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

										if(f_SValueOn == true)
											{
											f_StringA += "Sys%%double&&" + f_VarName + "%%" + f_Char + "&%";
											}
										else
											{
											f_StringA += "Sys%%double&&" + f_VarName + "%%";
											}
										}
									else
										{
										if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1) == true)
											{
											::sprintf(f_Char, "%s", ac_takeMeasurement(-1, -1, -1, -1).c_str());

											if(f_SValueOn == true)
												{
												f_StringA += "Sys%%bool&&" + f_VarName + "%%" + f_Char + "&%";
												}
											else
												{
												f_StringA += "Sys%%bool&&" + f_VarName + "%%";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		else
			{ // ClassVar Singles
			if(ac_takeMeasurementBLTV1(-1, -1, -1, -1, -1))
				{
				std::string f_TypeString = ac_takeMeasurement(-1, -1, -1, -1);

				f_StringA += "ClassVar%%" + f_TypeString + "&&" + f_VarName + "%%";
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak(); //add debug message SIndex Type out of bounds
				}
#endif
			}
		}

	return f_StringA;
}

std::shared_ptr<Qcom_eslfunction> classLMap::acGen_com_function_FromEcom(std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, std::shared_ptr<Qcom> f_Save_Com, int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_function_FromEcom";

	int f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	//add here save check consensus id as part of dependency loading
	int f_ConcensusID = ac_recordMeasurementINTS(ECOIN_CONSENSUS_ID, f_ElementIndex);

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	//Functionality typing re-execution time, FIXME: add miner destiny
	int f_FunctionType = ac_recordMeasurementINTV1(0, FuncExec_Total, 0, 3, 2, FuncExec_System_Load, f_ElementIndex);

	ag_StatusLive(f_ref_CurrentPath, "f_Function");
	std::shared_ptr<classFunction> f_Function = std::make_shared_reflect<classFunction>();

	f_Function->m_Type = f_FunctionType;

	int f_StartLineCount = f_Save_Com_Function->m_vec_InitLineOrdered.size();
	int f_LineCount = f_StartLineCount - 1;
	int f_LineIndexCount = 0;

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	//empty converted and exit
	if(ac_recordMeasurementBLTV1(2, 0, (f_Save_Com_Function->m_vec_InitLineOrdered.size() <= 0) ? true : false, f_ElementIndex) == true)
		{
		std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert(f_Save_Com);

		return f_func;
		}

	std::string f_StartLine = f_Save_Com_Function->m_vec_InitLineOrdered[0];

	std::vector<std::vector<std::string>> f_StartMorf = ac_ext_eslLine_morf_array(f_StartLine);

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	//includes class def
	if(ac_recordMeasurementBLTV1(2, 0, (f_StartMorf[0][0].compare("ClassStart") == 0) || (f_StartMorf[0][0].compare("Class") == 0) || (f_StartMorf[0][0].compare("ClassDef") == 0) ? true : false, f_ElementIndex) == true)
		{ //first line class definition
		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_ClassStartName1 = ac_recordMeasurement(f_StartMorf[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_ClassStartName2 = ac_recordMeasurement(f_StartMorf[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_StringE = "ClassStart%%" + f_ClassStartName1 + "%%" + f_ClassStartName2 + "%%";

		std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringE, ESL_INSTA_TYPE_CLASS_DEF);

		f_Function->m_vec_Insta.push_back(f_InstaVs);
		f_Function->m_idx_vec_Insta++;

		f_StringE += ESL_LINE_ENDING;

		f_Function->m_vec_String += f_StringE;

		f_LineCount--;
		f_LineIndexCount++;
		}

	//pull line
	std::string f_StartFuncLine = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];

	//pull morf array
	std::vector<std::vector<std::string>> f_StartFunctionMorf = ac_ext_eslLine_morf_array(f_StartFuncLine);

	int f_Rarg_IDX = 0; // beginning index starts at zero
	int f_LineTypeVK = -1;

	if(f_StartFunctionMorf[0][0].compare("Var") == 0)
		{
		f_LineTypeVK = 0;
		}
	else if(f_StartFunctionMorf[0][0].compare("Sys") == 0)
		{
		f_LineTypeVK = 1;
		}
	else if(f_StartFunctionMorf[0][0].compare("ClassVar") == 0)
		{
		f_LineTypeVK = 2;
		}
	else
		{
		f_LineTypeVK = 3;
		}

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	ac_recordMeasurementBLTV1(2, 0, (f_LineTypeVK < 3) ? true : false, f_ElementIndex); //returning cvar

	if(f_LineTypeVK != 3)
		{
		std::string f_TypeString = f_StartMorf[1][0];
		std::string f_NameString = f_StartMorf[2][0];
		std::string f_ValueString = "";

		bool f_HasNumber = ag_Value_Check(f_StartFunctionMorf[3][1]);

		if(f_HasNumber == true)
			{
			f_ValueString = f_StartMorf[3][0];

			f_Rarg_IDX += 4;
			}
		else
			{
			f_Rarg_IDX += 3;
			}

		ag_StatusLive(f_ref_CurrentPath, "f_Insta");
		std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_NameString, ESL_INSTA_TYPE_VAR_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;

		std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeVK, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

		f_Function->m_vec_String += f_StringAdd;
		}

	f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

	//include function def
	if(ac_recordMeasurementBLTV1(2, 0, ((f_StartFunctionMorf[f_Rarg_IDX][0].compare("Fus") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("Def") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("FuncDef") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("Function") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("FuncStart") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("FunctionStart") == 0)) ? true : false, f_ElementIndex) == true)
		{ //second line class definition
		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_FunctionDefClassName = ac_recordMeasurement(f_StartFunctionMorf[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_FunctionDefName = ac_recordMeasurement(f_StartFunctionMorf[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

		std::string f_StringE = "FuncDef%%" + f_FunctionDefClassName + "&*" + f_FunctionDefName + "%%";

		ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
		std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_InstaVs);
		f_Function->m_idx_vec_Insta++;

		f_Function->m_vec_String += f_StringE;

		f_Save_Com_Function->m_name = f_FunctionDefName;

		f_Save_Com_Function->m_classname = f_FunctionDefClassName;

		std::vector<int> f_vec_SingleVCVS;
		f_vec_SingleVCVS.clear();

		std::vector<int> f_vec_SingleVCVS_Typ;
		f_vec_SingleVCVS_Typ.clear();

		std::vector<bool> f_vec_SingleVCVS_Number;
		f_vec_SingleVCVS_Number.clear();

		int f_ArgumentCount = 0;
		int f_SingleIndex = f_Rarg_IDX;

		//function args while
		while(f_SingleIndex < f_StartMorf.size())
			{
			std::string f_PositionOne = f_StartMorf[f_SingleIndex][0];

			if((f_PositionOne.compare("Var") == 0))
				{
				f_ArgumentCount++;

				f_vec_SingleVCVS.push_back(f_SingleIndex);
				f_vec_SingleVCVS_Typ.push_back(ESL_MORF_TYPE_VAR);

				f_SingleIndex += 3;

				if(f_SingleIndex < f_StartMorf.size())
					{
					std::string f_PositionNumber = f_StartMorf[f_SingleIndex][1];

					if(ag_Value_Check(f_PositionNumber))
						{
						f_vec_SingleVCVS_Number.push_back(true);
						}
					else
						{
						f_vec_SingleVCVS_Number.push_back(false);
						}

					f_SingleIndex++;
					}
				else
					{
					f_vec_SingleVCVS_Number.push_back(false);
					}
				}
			else if (f_PositionOne.compare("Sys") == 0)
				{
				f_ArgumentCount++;

				f_vec_SingleVCVS.push_back(f_SingleIndex);
				f_vec_SingleVCVS_Typ.push_back(ESL_MORF_TYPE_SYS);

				if(f_SingleIndex < f_StartMorf.size())
					{
					std::string f_PositionNumber = f_StartMorf[f_SingleIndex][1];

					if(ag_Value_Check(f_PositionNumber))
						{
						f_vec_SingleVCVS_Number.push_back(true);
						}
					else
						{
						f_vec_SingleVCVS_Number.push_back(false);
						}

					f_SingleIndex++;
					}
				else
					{
					f_vec_SingleVCVS_Number.push_back(false);
					}
				}
			else if (f_PositionOne.compare("ClassVar") == 0)
				{
				f_ArgumentCount++;

				f_vec_SingleVCVS.push_back(f_SingleIndex);
				f_vec_SingleVCVS_Typ.push_back(ESL_MORF_TYPE_CLSVAR);
				f_vec_SingleVCVS_Number.push_back(false);

				f_SingleIndex += 3;
				}
			else
				{
				f_SingleIndex++;
				}
			}

		int f_Int = 0;
		bool f_argScan = true;
		while(f_argScan == true)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_argScan = ac_recordMeasurementBLTV1(-1, -1, (f_Int < f_ArgumentCount) ? true : false, f_ElementIndex);

			if(f_argScan == true)
				{
				int f_SingIndex = f_vec_SingleVCVS[f_Int];
				int f_SIndex_Typ = f_vec_SingleVCVS_Typ[f_Int];
				std::string f_TypeString = f_StartMorf[f_SingIndex + 1][0];
				std::string f_NameString = f_StartMorf[f_SingIndex + 2][0];
				std::string f_ValueString = "";

				if(f_vec_SingleVCVS_Number[f_Int] == true)
					{
					f_ValueString = f_StartMorf[f_SingIndex + 3][0];
					}

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_NameString, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				std::string f_StringAdd = acGen_Var_fromEcom(f_SIndex_Typ, f_vec_SingleVCVS_Number[f_Int], f_TypeString, f_NameString, f_ValueString);

				f_Function->m_vec_String += f_StringAdd;
				}

			f_Int++;
			}

		f_Function->m_vec_String += ESL_LINE_ENDING; //END Function Definition and Parameters

		f_LineCount--;
		f_LineIndexCount++;
		}

	acResetLine();

	bool f_Scan = true;
	while(f_Scan == true)
		{
		bool f_Contact = false;

		std::string f_LineString = f_Save_Com_Function->m_vec_InitLineOrdered[f_LineIndexCount];

		int f_LineInstaType = acRecordLine(f_LineString);

		f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
				
		int f_LineType = ac_recordMeasurementINTV1(0, ESL_INSTA_TYPE_COUNT, 0, 3, 6, f_LineInstaType, f_ElementIndex);

		if(f_LineType == ESL_INSTA_TYPE_VAR_DEF)
			{
			std::vector<std::vector<std::string>> f_morf1 = ac_ext_eslLine_morf_array(f_LineString);

			int f_LineTypeVA = -1;

			if(f_morf1[0][0].compare("Var") == 0)
				{
				f_LineTypeVA = 0;
				}
			else if(f_morf1[0][0].compare("Sys") == 0)
				{
				f_LineTypeVA = 1;
				}
			else if(f_morf1[0][0].compare("ClassVar") == 0)
				{
				f_LineTypeVA = 2;
				}
			else
				{
				f_LineTypeVA = 3;
				}

			if(f_LineTypeVA != 3)
				{
				std::string f_TypeString = f_morf1[1][0];
				std::string f_NameString = f_morf1[2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morf1.size() >= 4)
					{
					f_HasNumber = ag_Value_Check(f_morf1[3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morf1[3][0];
						}
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeVA, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				f_StringAdd += ESL_LINE_ENDING;

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringAdd;
				}

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_SYS_DEF)
			{
			std::vector<std::vector<std::string>> f_morf1 = ac_ext_eslLine_morf_array(f_LineString);

			int f_LineTypeV = -1;

			if(f_morf1[0][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morf1[0][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morf1[0][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV != 3)
				{
				std::string f_TypeString = f_morf1[1][0];
				std::string f_NameString = f_morf1[2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morf1.size() >= 4)
					{
					f_HasNumber = ag_Value_Check(f_morf1[3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morf1[3][0];
						}
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				f_StringAdd += ESL_LINE_ENDING;

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringAdd;
				}

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_CONDITIONAL)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			std::string f_StringAB = "";

			int f_PositionSlider = 0;

			//definate lhs assumption
			int f_LineTypeV = -1;

			if(f_morfarray[0][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[0][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[0][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV != 3)
				{
				std::string f_TypeString = f_morfarray[f_PositionSlider + 1][0];
				std::string f_NameString = f_morfarray[f_PositionSlider + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = ag_Value_Check(f_morfarray[f_PositionSlider + 3][1]);

				if(f_HasNumber == true)
					{
					f_ValueString = f_morfarray[f_PositionSlider + 3][0];

					f_PositionSlider += 4;
					}
				else
					{
					f_PositionSlider += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_PositionSlider += 1;

			f_StringAB += "Cond%%";

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			int f_FingerCount = ac_recordMeasurementINTV1(0, 5, 0, 3, 2, agFind_ConType(f_morfarray[f_PositionSlider][0]), f_ElementIndex);

			f_PositionSlider += 1;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_Name = ac_recordMeasurement(f_morfarray[f_PositionSlider][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_PositionSlider += 1;

			if(f_FingerCount <= MuCon_Equal)
				{
				f_StringAB += "==^^";
				}
			else if(f_FingerCount == MuCon_NotEqual)
				{
				f_StringAB += "!=^^";
				}
			else if(f_FingerCount == MuCon_SmallThan)
				{
				f_StringAB += "<<^^";
				}
			else if(f_FingerCount == MuCon_GreatThan)
				{
				f_StringAB += ">>^^";
				}
			else if(f_FingerCount == MuCon_SmallThanorEqual)
				{
				f_StringAB += "<=^^";
				}
			else if(f_FingerCount == MuCon_GreatThanorEqual)
				{
				f_StringAB += ">=^^";
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif

			f_StringAB += f_Name + "%%";

			f_LineTypeV = -1;

			if(f_morfarray[f_PositionSlider][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[f_PositionSlider][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[f_PositionSlider][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV != 3)
				{
				std::string f_TypeString = f_morfarray[f_PositionSlider + 1][0];
				std::string f_NameString = f_morfarray[f_PositionSlider + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morfarray.size() > f_PositionSlider + 3)
					{
					f_HasNumber = ag_Value_Check(f_morfarray[f_PositionSlider + 3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morfarray[f_PositionSlider + 3][0];

						f_PositionSlider += 4;
						}
					else
						{
						f_PositionSlider += 3;
						}
					}
				else
					{
					f_PositionSlider += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;

			std::string f_StringFB = "Function%%EcomNative&*Success%%";

			ag_StatusLive(f_ref_CurrentPath, "f_InstaC");
			std::shared_ptr<classInsta> f_InstaC = std::make_shared_reflect<classInsta>(f_StringFB, ESL_INSTA_TYPE_FUNC_DEF);

			f_Function->m_vec_Insta.push_back(f_InstaC);
			f_Function->m_idx_vec_Insta++;

			f_StringFB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringFB;

			f_LineCount--;
			f_LineIndexCount++;
					
			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_OPER)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			std::string f_StringAB = "";

			int f_PositionSlider = 0;

			//definate lhs assumption
			int f_LineTypeV = -1;

			if(f_morfarray[0][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[0][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[0][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV != 3)
				{
				std::string f_TypeString = f_morfarray[f_PositionSlider + 1][0];
				std::string f_NameString = f_morfarray[f_PositionSlider + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = ag_Value_Check(f_morfarray[f_PositionSlider + 3][1]);

				if(f_HasNumber == true)
					{
					f_ValueString = f_morfarray[f_PositionSlider + 3][0];

					f_PositionSlider += 4;
					}
				else
					{
					f_PositionSlider += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_PositionSlider += 1;

			//operator record
			std::string f_StringABCF = "Opr%%";

			int f_OperType = agFind_OprType(f_morfarray[f_PositionSlider][0]);

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			int f_FingerCount = ac_recordMeasurementINTV1(0, 9, 0, 3, 2, f_OperType, f_ElementIndex);

			f_PositionSlider += 1;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_Name = ac_recordMeasurement(f_morfarray[f_PositionSlider][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(f_FingerCount == MuOpr_Plus)
				{
				f_StringABCF += "Plus**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Minus)
				{
				f_StringABCF += "Minus**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Multiply)
				{
				f_StringABCF += "Mul**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Divide)
				{
				f_StringABCF += "Div**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Bitleft)
				{
				f_StringABCF += "<<**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Bitright)
				{
				f_StringABCF += ">>**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Modulus)
				{
				f_StringABCF += "Mod**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Copy)
				{
				f_StringABCF += "Copy**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Equals)
				{
				f_StringABCF += "Equals**" + f_Name;
				}
			else if(f_FingerCount == MuOpr_Random)
				{
				f_StringABCF += "Random**" + f_Name;
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif

			f_StringABCF += "%%";

			f_StringAB += f_StringABCF;

			f_PositionSlider += 1;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			if(ac_recordMeasurementBLTV1(1, 0, (f_PositionSlider < f_morfarray.size()) ? true : false, f_ElementIndex) == true)
				{
				//add rhs
				f_LineTypeV = -1;

				if(f_morfarray[f_PositionSlider][0].compare("Var") == 0)
					{
					f_LineTypeV = 0;
					}
				else if(f_morfarray[f_PositionSlider][0].compare("Sys") == 0)
					{
					f_LineTypeV = 1;
					}
				else if(f_morfarray[f_PositionSlider][0].compare("ClassVar") == 0)
					{
					f_LineTypeV = 2;
					}
				else
					{
					f_LineTypeV = 3;
					}

				if(f_LineTypeV != 3)
					{
					std::string f_TypeString = f_morfarray[f_PositionSlider + 1][0];
					std::string f_NameString = f_morfarray[f_PositionSlider + 2][0];
					std::string f_ValueString = "";

					bool f_HasNumber = false;

					if(f_morfarray.size() > f_PositionSlider + 3)
						{
						f_HasNumber = ag_Value_Check(f_morfarray[f_PositionSlider + 3][1]);

						if(f_HasNumber == true)
							{
							f_ValueString = f_morfarray[f_PositionSlider + 3][0];

							f_PositionSlider += 4;
							}
						else
							{
							f_PositionSlider += 3;
							}
						}
					else
						{
						f_PositionSlider += 3;
						}

					std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

					ag_StatusLive(f_ref_CurrentPath, "f_Insta");
					std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_StringAB += f_StringAdd;
					}
				}

			ag_StatusLive(f_ref_CurrentPath, "f_InstaAB");
			std::shared_ptr<classInsta> f_InstaAB = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_OPER);

			f_Function->m_vec_Insta.push_back(f_InstaAB);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;
					
			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_LOOP_DEF)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			int f_OffsetInt = 1;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_forName = ac_recordMeasurement(f_morfarray[f_OffsetInt][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);
			std::string f_StringF = "For%% " + f_forName + "%%";

			std::string f_StringAB = "";

			f_OffsetInt += 1;

			//definate lhs assumption
			int f_LineTypeV = -1;

			if(f_morfarray[f_OffsetInt][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[f_OffsetInt][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[f_OffsetInt][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV < 2)
				{
				std::string f_TypeString = f_morfarray[f_OffsetInt + 1][0];
				std::string f_NameString = f_morfarray[f_OffsetInt + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morfarray.size() > f_OffsetInt + 3)
					{
					f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetInt + 3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morfarray[f_OffsetInt + 3][0];

						f_OffsetInt += 4;
						}
					else
						{
						f_OffsetInt += 3;
						}
					}
				else
					{
					f_OffsetInt += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_LineTypeV = -1;

			if(f_morfarray[f_OffsetInt][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[f_OffsetInt][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[f_OffsetInt][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV < 2)
				{
				std::string f_TypeString = f_morfarray[f_OffsetInt + 1][0];
				std::string f_NameString = f_morfarray[f_OffsetInt + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morfarray.size() > f_OffsetInt + 3)
					{
					f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetInt + 3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morfarray[f_OffsetInt + 3][0];

						f_OffsetInt += 4;
						}
					else
						{
						f_OffsetInt += 3;
						}
					}
				else
					{
					f_OffsetInt += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_LineTypeV = -1;

			if(f_morfarray[f_OffsetInt][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[f_OffsetInt][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[f_OffsetInt][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV < 2)
				{
				std::string f_TypeString = f_morfarray[f_OffsetInt + 1][0];
				std::string f_NameString = f_morfarray[f_OffsetInt + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morfarray.size() > f_OffsetInt + 3)
					{
					f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetInt + 3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morfarray[f_OffsetInt + 3][0];

						f_OffsetInt += 4;
						}
					else
						{
						f_OffsetInt += 3;
						}
					}
				else
					{
					f_OffsetInt += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			ag_StatusLive(f_ref_CurrentPath, "f_InstaAB");
			std::shared_ptr<classInsta> f_InstaAB = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_LOOP_DEF);

			f_Function->m_vec_Insta.push_back(f_InstaAB);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_FUNC_CALL)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			int f_OffsetIntReturn = 0;
			int f_OffsetIntArg = 0;

			std::string f_StringAB = "";

			//definate lhs assumption
			int f_LineTypeV = -1;

			if(f_morfarray[f_OffsetIntReturn][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[f_OffsetIntReturn][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[f_OffsetIntReturn][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			if(f_LineTypeV < 3)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has return arg

				std::string f_TypeString = f_morfarray[f_OffsetIntReturn + 1][0];
				std::string f_NameString = f_morfarray[f_OffsetIntReturn + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morfarray.size() > f_OffsetIntReturn + 3)
					{
					f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetIntReturn + 3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morfarray[f_OffsetIntReturn + 3][0];

						f_OffsetIntReturn += 4;
						}
					else
						{
						f_OffsetIntReturn += 3;
						}
					}
				else
					{
					f_OffsetIntReturn += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //has no return arg
				}

			f_OffsetIntArg = f_OffsetIntReturn;

			f_OffsetIntArg++;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_FunctionType1 = ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_OffsetIntArg++;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_FunctionName2 = ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_OffsetIntArg++;

			f_StringAB += "Fcn%%" + f_FunctionType1 + "&*" + f_FunctionName2 + "%%";

			m_arguScan = true;
			while(m_arguScan == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				m_arguScan = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, (f_OffsetIntArg < f_morfarray.size()) ? true : false, f_ElementIndex); //has arg

				if(m_arguScan == true)
					{
					f_LineTypeV = -1;

					if(f_morfarray[f_OffsetIntArg][0].compare("Var") == 0)
						{
						f_LineTypeV = 0;
						}
					else if(f_morfarray[f_OffsetIntArg][0].compare("Sys") == 0)
						{
						f_LineTypeV = 1;
						}
					else if(f_morfarray[f_OffsetIntArg][0].compare("ClassVar") == 0)
						{
						f_LineTypeV = 2;
						}
					else
						{
						f_LineTypeV = 3;

						f_OffsetIntArg = f_morfarray.size();
						}

					if(f_LineTypeV < 3)
						{
						std::string f_TypeString = f_morfarray[f_OffsetIntArg + 1][0];
						std::string f_NameString = f_morfarray[f_OffsetIntArg + 2][0];
						std::string f_ValueString = "";

						bool f_HasNumber = false;

						if(f_morfarray.size() > f_OffsetIntArg + 3)
							{
							f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetIntArg + 3][1]);

							if(f_HasNumber == true)
								{
								f_ValueString = f_morfarray[f_OffsetIntArg + 3][0];

								f_OffsetIntArg += 4;
								}
							else
								{
								f_OffsetIntArg += 3;
								}
							}
						else
							{
							f_OffsetIntArg += 3;
							}

						std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

						ag_StatusLive(f_ref_CurrentPath, "f_Insta");
						std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

						f_Function->m_vec_Insta.push_back(f_Insta);
						f_Function->m_idx_vec_Insta++;

						f_StringAB += f_StringAdd;
						}
					}
				}

			ag_StatusLive(f_ref_CurrentPath, "f_InstaAB");
			std::shared_ptr<classInsta> f_InstaAB = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_FUNC_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaAB);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;
					
			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_FUNC_DEF)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			std::string f_StringAB = "";

			int f_ReturnIntArg = 0;
			int f_OffsetIntArg = 0;

			//definate lhs assumption
			int f_LineTypeV = -1;

			if(f_morfarray[f_ReturnIntArg][0].compare("Var") == 0)
				{
				f_LineTypeV = 0;
				}
			else if(f_morfarray[f_ReturnIntArg][0].compare("Sys") == 0)
				{
				f_LineTypeV = 1;
				}
			else if(f_morfarray[f_ReturnIntArg][0].compare("ClassVar") == 0)
				{
				f_LineTypeV = 2;
				}
			else
				{
				f_LineTypeV = 3;
				}

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, (f_LineTypeV < 3) ? true : false, f_ElementIndex); //has return arg

			if(f_LineTypeV < 3)
				{
				std::string f_TypeString = f_morfarray[f_ReturnIntArg + 1][0];
				std::string f_NameString = f_morfarray[f_ReturnIntArg + 2][0];
				std::string f_ValueString = "";

				bool f_HasNumber = false;

				if(f_morfarray.size() > f_ReturnIntArg + 3)
					{
					f_HasNumber = ag_Value_Check(f_morfarray[f_ReturnIntArg + 3][1]);

					if(f_HasNumber == true)
						{
						f_ValueString = f_morfarray[f_ReturnIntArg + 3][0];

						f_ReturnIntArg += 4;
						}
					else
						{
						f_ReturnIntArg += 3;
						}
					}
				else
					{
					f_ReturnIntArg += 3;
					}

				std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_OffsetIntArg = f_ReturnIntArg;

			f_OffsetIntArg++;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_FunctionDefClassName = ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_OffsetIntArg++;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_FunctionDefName = ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_OffsetIntArg++;

			f_StringAB += "FuncDef%%" + f_FunctionDefClassName + "&*" + f_FunctionDefName + "%%";

			m_arguScan = true;
			while(m_arguScan == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				m_arguScan = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, (f_OffsetIntArg < f_morfarray.size()) ? true : false, f_ElementIndex); //has arg

				if(m_arguScan == true)
					{
					f_LineTypeV = -1;

					if(f_morfarray[f_OffsetIntArg][0].compare("Var") == 0)
						{
						f_LineTypeV = 0;
						}
					else if(f_morfarray[f_OffsetIntArg][0].compare("Sys") == 0)
						{
						f_LineTypeV = 1;
						}
					else if(f_morfarray[f_OffsetIntArg][0].compare("ClassVar") == 0)
						{
						f_LineTypeV = 2;
						}
					else
						{
						f_LineTypeV = 3;

						f_OffsetIntArg = f_morfarray.size();
						}

					if(f_LineTypeV < 3)
						{
						std::string f_TypeString = f_morfarray[f_OffsetIntArg + 1][0];
						std::string f_NameString = f_morfarray[f_OffsetIntArg + 2][0];
						std::string f_ValueString = "";

						bool f_HasNumber = false;

						if(f_morfarray.size() > f_OffsetIntArg + 3)
							{
							f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetIntArg + 3][1]);

							if(f_HasNumber == true)
								{
								f_ValueString = f_morfarray[f_OffsetIntArg + 3][0];

								f_OffsetIntArg += 4;
								}
							else
								{
								f_OffsetIntArg += 3;
								}
							}
						else
							{
							f_OffsetIntArg += 3;
							}

						std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

						ag_StatusLive(f_ref_CurrentPath, "f_Insta");
						std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

						f_Function->m_vec_Insta.push_back(f_Insta);
						f_Function->m_idx_vec_Insta++;

						f_StringAB += f_StringAdd;
						}
					}
				}

			ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
			std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_FUNC_DEF);

			f_Function->m_vec_Insta.push_back(f_InstaVs);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;
					
			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_CLASS_DEF)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_ClassDefNameSpace = ac_recordMeasurement(f_morfarray[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_ClassDefName = ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_StringE = "ClassStart%%" + f_ClassDefNameSpace + "%%" + f_ClassDefName + "%%";

			ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
			std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
				
			f_Function->m_vec_Insta.push_back(f_InstaVs);
			f_Function->m_idx_vec_Insta++;

			f_StringE += ESL_LINE_ENDING;
					
			f_Function->m_vec_String += f_StringE;

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_CLASSVAR_DEF)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_FunctionClassVarType = ac_recordMeasurement(f_morfarray[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_FunctionClassVarName = ac_recordMeasurement(f_morfarray[2][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			std::string f_StringAB = "ClassVar%%" + f_FunctionClassVarType + "&$" + f_FunctionClassVarName + "%%";

			int f_OffsetIntArg = 3;

			bool f_isLength = (f_OffsetIntArg < f_morfarray.size()) ? true : false;

			if(f_isLength == true)
				{
				bool f_isVar = ag_CVar_Check(f_morfarray[f_OffsetIntArg][1]);

				if(f_isVar == false)
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					//reflection class var init def
					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has reflection

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					std::string f_FunctionReflectionVarName1 = ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_OffsetIntArg++;

					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					std::string f_FunctionReflectionVarName2 = ac_recordMeasurement(f_morfarray[f_OffsetIntArg][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					f_OffsetIntArg++;

					f_StringAB += f_FunctionReflectionVarName1 + "#?" + f_FunctionReflectionVarName2 + "#?";
					}
				else // is a CVar!
					{
					f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

					//lass var init def
					ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex);
					}
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				//lass var init def - length 0 no arg stage
				ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex);
				}

			m_arguScan = true;
			while(m_arguScan == true)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				m_arguScan = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, (f_OffsetIntArg < f_morfarray.size()) ? true : false, f_ElementIndex); //has arg

				if(m_arguScan == true)
					{
					int f_LineTypeV = -1;

					if(f_morfarray[f_OffsetIntArg][0].compare("Var") == 0)
						{
						f_LineTypeV = 0;
						}
					else if(f_morfarray[f_OffsetIntArg][0].compare("Sys") == 0)
						{
						f_LineTypeV = 1;
						}
					else if(f_morfarray[f_OffsetIntArg][0].compare("ClassVar") == 0)
						{
						f_LineTypeV = 2;
						}
					else
						{
						f_LineTypeV = 3;

						f_OffsetIntArg = f_morfarray.size();
						}

					if(f_LineTypeV < 3)
						{
						std::string f_TypeString = f_morfarray[f_OffsetIntArg + 1][0];
						std::string f_NameString = f_morfarray[f_OffsetIntArg + 2][0];
						std::string f_ValueString = "";

						bool f_HasNumber = false;

						if(f_morfarray.size() > f_OffsetIntArg + 3)
							{
							f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetIntArg + 3][1]);

							if(f_HasNumber == true)
								{
								f_ValueString = f_morfarray[f_OffsetIntArg + 3][0];

								f_OffsetIntArg += 4;
								}
							else
								{
								f_OffsetIntArg += 3;
								}
							}
						else
							{
							f_OffsetIntArg += 3;
							}

						std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

						ag_StatusLive(f_ref_CurrentPath, "f_Insta");
						std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

						f_Function->m_vec_Insta.push_back(f_Insta);
						f_Function->m_idx_vec_Insta++;

						f_StringAB += f_StringAdd;
						}
					}
				}

			ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
			std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_CLASSVAR_DEF);
				
			f_Function->m_vec_Insta.push_back(f_InstaVs);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;
					
			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;

			f_Contact = true;
			}
		else if(f_LineType == ESL_INSTA_TYPE_TEMPLATE)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			if(f_morfarray.size() > 1)
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex); //has var arg

				std::string f_ClassTypeName = ac_recordMeasurement(f_morfarray[1][0], f_ElementIndex, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				std::string f_StringAB = "";

				f_StringAB += "Template%%" + f_ClassTypeName + "&%";

				ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
				std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_TEMPLATE);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringAB;
				f_LineCount--;
				f_LineIndexCount++;
					
				f_Contact = true;
				}
			else
				{
				f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex); //FALSE has var arg

				std::string f_StringAB = "Template%%";

				ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
				std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_TEMPLATE);

				f_Function->m_vec_Insta.push_back(f_InstaA);
				f_Function->m_idx_vec_Insta++;

				f_Function->m_vec_String += f_StringAB;
				f_LineCount--;
				f_LineIndexCount++;

				f_Contact = true;
				}
			}
		else if(f_LineType == ESL_INSTA_TYPE_RETURN)
			{
			std::vector<std::vector<std::string>> f_morfarray = ac_ext_eslLine_morf_array(f_LineString);

			std::string f_StringAB = "Return%%";

			int f_OffsetIntArg = 1;

			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			bool f_arguScan = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, (f_OffsetIntArg < f_morfarray.size()) ? true : false, f_ElementIndex); //has arg

			if(f_arguScan == true)
				{
				int f_LineTypeV = -1;

				if(f_morfarray[f_OffsetIntArg][0].compare("Var") == 0)
					{
					f_LineTypeV = 0;
					}
				else if(f_morfarray[f_OffsetIntArg][0].compare("Sys") == 0)
					{
					f_LineTypeV = 1;
					}
				else if(f_morfarray[f_OffsetIntArg][0].compare("ClassVar") == 0)
					{
					f_LineTypeV = 2;
					}
				else
					{
					f_LineTypeV = 3;
					}

				if(f_LineTypeV < 3)
					{
					std::string f_TypeString = f_morfarray[f_OffsetIntArg + 1][0];
					std::string f_NameString = f_morfarray[f_OffsetIntArg + 2][0];
					std::string f_ValueString = "";

					bool f_HasNumber = false;

					if(f_morfarray.size() > f_OffsetIntArg + 3)
						{
						f_HasNumber = ag_Value_Check(f_morfarray[f_OffsetIntArg + 3][1]);

						if(f_HasNumber == true)
							{
							f_ValueString = f_morfarray[f_OffsetIntArg + 3][0];

							f_OffsetIntArg += 4;
							}
						else
							{
							f_OffsetIntArg += 3;
							}
						}
					else
						{
						f_OffsetIntArg += 3;
						}

					std::string f_StringAdd = acGen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

					ag_StatusLive(f_ref_CurrentPath, "f_Insta");
					std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					f_StringAB += f_StringAdd;
					}
				}

			ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
			std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_RETURN);

			f_Function->m_vec_Insta.push_back(f_InstaA);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += ESL_LINE_ENDING;

			f_Function->m_vec_String += f_StringAB;

			f_LineCount--;
			f_LineIndexCount++;
					
			f_Contact = true;
			}
#ifdef ECOIN_DEBUG_BREAKS
		else
			{
			__debugbreak();
			}
#endif

		bool f_ExtraLines = true;

		if(f_LineCount < 0)
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_ExtraLines = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, false, f_ElementIndex);
			}
		else
			{
			f_ElementIndex = acPull_gen_ElementID(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth);

			f_ExtraLines = ac_recordMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, true, f_ElementIndex);
			}

		if(f_ExtraLines == false)
			{
			f_Scan = false;
			}
		}

		//end of script
	f_Function->m_vec_String.pop_back(); // '/n'

	std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert(f_Save_Com);

#ifdef ECOIN_DEBUG_BREAKS
	ag_EcoinSecure_Break_Assert(f_func->m_vec_InitLineOrdered.size(), f_LineIndexCount);
#endif

	return f_func;
}

#if 1
void classTarget_ESL_Script::acFromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_ESL_Script> f_Target)
{
#if 0
	for(int f_Count = 0; f_Count < f_Hesh->vec_Bicycle.size(); f_Count++)
		{
		std::shared_ptr<classElement> f_Element = std::make_shared_reflect<classElement>(f_Hesh->vec_Bicycle[f_Count]);

		m_Collection->m_vec_Element.push_back(f_Element);
		m_Collection->m_idx_vec_Element++;
		}

	int f_ElementStartAD = 0;
	int f_EndAD = 0;
		
	m_SchemaTop = 0;
	m_SchemaRef[0]->m_X = float(3.121113539F);
	m_SchemaRef[0]->m_Y = float(3.773584266F);
	m_SchemaRef[0]->m_Z = float(3.952468634F);
	
	shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[0];
	
	int f_FunctionCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 1);
	f_FunctionCount = 1;

	for(int f_Jet = 0; f_Jet < f_FunctionCount; f_Jet++)
		{
		m_vec_CountLock.clear();

		int f_FunctionType = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 2);
		//int f_ArgumentCount = ac_takeMeasurementINTV1(f_Element, 0, 2, 2, 3, 3);
		int f_LineCount = ac_takeMeasurementINTV1(f_Element, 1, 500, 20, 3, 4);
		//f_LineCount = f_InstaCountMap;
		
		std::shared_ptr<classCodeLine> f_vec_CodeLine = std::make_shared_reflect<classCodeLine>();

		std::shared_ptr<classFunction> f_Function = std::make_shared_reflect<classFunction>();
		f_Function->m_Type = f_FunctionType;
		f_Function->m_Name = ac_takeMeasurement(f_Element);
		
		std::string f_StringA = "FuncDef%%" + f_Function->m_Name + "&*ECNMiner_Affinity%%////";
		f_StringA += ESL_LINE_ENDING;

		ag_StatusLive(f_ref_CurrentPath, "f_Insta"); std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringA, ESL_INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_Insta);
		f_Function->m_idx_vec_Insta++;
		
		/*for(int f_Int = 0; f_Int < f_ArgumentCount; f_Int++)
			{
			std::string f_VarNameA = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
			ag_StatusLive(f_ref_CurrentPath, "f_Insta"); std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_VarNameA, ESL_INSTA_TYPE_VAR_DEF);

			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			if(ac_takeMeasurementBLTV1(f_Element, 2, 0))
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					::sprintf(f_Char, "Random");

					f_StringA += "Var%%" + f_VarNameA + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_SYSTEM, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					std::string f_SysName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 0.0f, 1.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 1.0f, 100.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2, 2, f_ValueNr, f_ElementIndex));
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");
						}

					f_StringA += "Sys%%" + f_SysName + "%%" + f_Char + "&%";
					}
				else if(acFactorStrengthVar(VAR_DEF_TYPE_VARCALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
					{
					std::string f_VarName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

					f_StringA += "Var%%" + f_VarName + "%%";
					}
				}
			else
				{
				f_StringA += "Var%%" + f_VarNameA + "%%////";
				}

			f_StringA += ESL_LINE_ENDING;
			}

		f_Function->m_vec_String += f_StringA;
		
		acResetLine();*/
		
		m_idx_vec_CountLock = 0;
		
		while(f_LineCount > 0)
			{
			bool f_Contact = false;
				
			int f_InstaType = ac_takeMeasurementINTV1(f_Element, 0, ESL_INSTA_TYPE_COUNT, 0, 3, 6);

			if(f_InstaType == ESL_INSTA_TYPE_VAR_DEF)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_VAR_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

					char f_Char[150];
					FillChar(f_Char, 150);

					std::string f_StringB;
					f_StringB.clear();

					if(acFactorStrengthVar(VAR_DEF_TYPE_ZERO_TO_ONE, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 0.0f, 1.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_ONE_TO_HUNDRED, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 1.0f, 100.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_HUNDRED_TO_FIVETHOUSAND, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_FIVETHOUSAND_TO_FIFTY_MILLION, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "%f", ac_takeMeasurementFLTV1(f_Element, 100.0f, 5000.0f, 0.0f, 2));

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_RANDOM, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						::sprintf(f_Char, "Random");

						f_StringB += "Var%%" + f_Name + "%%" + f_Char + "&%";
						}
					else if(acFactorStrengthVar(VAR_DEF_TYPE_VARCALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth))
						{
						f_StringB += "Var%%" + f_Name + "%%0.0&%////";

						std::string f_VarName = acMakeUnison(f_Target, ac_takeMeasurement(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);

						::sprintf(f_Char, "Opr%%Plus**Fork1%%Sys%%%s", f_VarName);

						f_StringB += "Var%%" + f_VarName + "%%" + f_Char + "%%";
						}

					f_StringB += ESL_LINE_ENDING;

					std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringB, ESL_INSTA_TYPE_VAR_DEF);

					f_Function->m_vec_Insta.push_back(f_InstaVs);
					f_Function->m_idx_vec_Insta++;

					f_Function->m_vec_String += f_StringB;
					f_LineCount--;
					
					f_Contact = true;
					}
				}
			else if(f_InstaType == ESL_INSTA_TYPE_CONDITIONAL)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_CONDITIONAL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::string f_StringB = "Cond%%";
					ag_StatusLive(f_ref_CurrentPath, "f_Insta"); std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringB, ESL_INSTA_TYPE_CONDITIONAL);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;

					int f_FingerCount = ac_takeMeasurementINTV1(f_Element, 0, 6, 1, 3, 2);
								
					if(f_FingerCount <= 1)
						{
						f_StringB += "==^^";
						}
					else if(f_FingerCount == 2)
						{
						f_StringB += "!=^^";
						}
					else if(f_FingerCount == 3)
						{
						f_StringB += "<<^^";
						}
					else if(f_FingerCount == 4)
						{
						f_StringB += ">>^^";
						}
					else if(f_FingerCount == 5)
						{
						f_StringB += "<=^^";
						}
					else
						{
						f_StringB += ">=^^";
						}

					f_Function->m_vec_String += f_StringB;
					f_LineCount--;
					
					std::vector<int> f_conInstaCount;
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 0, 2, 0, 3, 4));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 1, 12, 0, 3, 5));
					f_conInstaCount.push_back(3 + ac_takeMeasurementINTV1(f_Element, 2, 25, 4, 3, 6));
					int f_Select = ac_takeMeasurementINTV1(f_Element, 0, 3, 1, 3, 3);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock>(f_conInstaCount[f_Select], "ECNMiner_Affinity", ESL_INSTA_TYPE_CONDITIONAL));
					m_idx_vec_CountLock++;
					
					f_Contact = true;
					}
				}
			else if(f_InstaType == ESL_INSTA_TYPE_LOOP_DEF)
				{
				/*if(acFactorStrength(ESL_INSTA_TYPE_LOOP_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					 //////////
					// space
					if(m_LastTypeII == -5)
						{
						for(int f_cv2 = 0; f_cv2 < m_idx_vec_CountLock; f_cv2++)
							{
							if(m_vec_CountLock[f_cv2]->m_String.compare("}") == 0)
								{
								f_Function->m_vec_String += "	";
								}
							}
						}
						
					std::string f_Name = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_DEF, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_forVarName = ac_takeMeasurement(f_Element);
					std::string f_Str = "for(int " + f_forVarName + " = 0; " + f_forVarName + " < " + f_Name + "; " + f_forVarName + "++)\n	{\n 	";
					ag_StatusLive(f_ref_CurrentPath, "f_Insta"); std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta(f_Str, ESL_INSTA_TYPE_LOOP_DEF);

					f_Function->m_vec_Insta.push_back(f_Insta);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_Str;
					f_LineCount--;
					
					int f_loopInstaCount = ac_takeMeasurementINTV1(f_Element, 8, 105, 8, 3, 1);
					
					m_vec_CountLock.push_back(std::make_shared<classCountLock(f_loopInstaCount, "\n}\n", ESL_INSTA_TYPE_LOOP_DEF));
					m_idx_vec_CountLock++;
					f_Contact = true;
					}*/
				}
			else if(f_InstaType == ESL_INSTA_TYPE_FUNC_CALL)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_FUNC_CALL, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					//target restriction point
					std::string f_ReturnVarName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta, m_idx_vec_Function);
					std::string f_FunctionName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Element, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
					std::string f_Var1Name = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta + 2, m_idx_vec_Function);
					std::string f_Var2Name = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_VAR_CALL, f_Element, f_Function->m_idx_vec_Insta + 3, m_idx_vec_Function);

					std::string f_StringB = "Var%%" + f_ReturnVarName + "%%1.0&%Fcn%%" + f_FunctionName + "&*" + f_FunctionName + "FUNCCALL%%Var%%" + f_Var1Name + "%%1.0&%Var%%" + f_Var2Name + "%%0.0&%////";
					f_StringB += ESL_LINE_ENDING;
					
					std::shared_ptr<classInsta> f_InstaR = std::make_shared_reflect<classInsta>(f_ReturnVarName, ESL_INSTA_TYPE_VAR_CALL);
					std::shared_ptr<classInsta> f_InstaA1 = std::make_shared_reflect<classInsta>(f_Var1Name, ESL_INSTA_TYPE_VAR_CALL);
					std::shared_ptr<classInsta> f_InstaA2 = std::make_shared_reflect<classInsta>(f_Var2Name, ESL_INSTA_TYPE_VAR_CALL);
					std::shared_ptr<classInsta> f_InstaB = std::make_shared_reflect<classInsta>(f_FunctionName, ESL_INSTA_TYPE_FUNC_CALL);

					f_Function->m_vec_Insta.push_back(f_InstaR);
					f_Function->m_idx_vec_Insta++;
					f_Function->m_vec_Insta.push_back(f_InstaB);
					f_Function->m_idx_vec_Insta++;
					f_Function->m_vec_Insta.push_back(f_InstaA1);
					f_Function->m_idx_vec_Insta++;
					f_Function->m_vec_Insta.push_back(f_InstaA2);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringB;
					f_LineCount--;
					
					int f_arguInstaCount = ac_takeMeasurementINTV1(f_Element, 1, 3, 0, 3, 4);
					
				    f_Contact = true;
					}
				}
			else if(f_InstaType == ESL_INSTA_TYPE_FUNC_DEF)
				{
				if(acFactorStrength(ESL_INSTA_TYPE_FUNC_DEF, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth) == true)
					{
					std::string f_FunctionDefName = acMakeUnison(f_Target, ac_takeMeasurement(, f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Element, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

					std::string f_StringE = "FuncDef%%" + f_FunctionDefName + "&*ECNMiner_Affinity%%////";
					f_StringA += ESL_LINE_ENDING;

					std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringE, ESL_INSTA_TYPE_FUNC_DEF);
							
					f_Function->m_vec_Insta.push_back(f_InstaVs);
					f_Function->m_idx_vec_Insta++;
					
					f_Function->m_vec_String += f_StringE;
					f_LineCount--;
					}
				}
				
			  ///////////////////
			 //
			// Count Map
			if(f_Contact == true)
				{
				f_vec_CodeLine->m_vec_Code.push_back(f_Function->m_vec_Insta[f_Function->m_idx_vec_Insta - 1]);
				f_vec_CodeLine->m_idx_vec_Code++;
					
				if(m_idx_vec_CountLock > 0)
					{
					for(int f_cv = m_idx_vec_CountLock - 1; f_cv >= 0; f_cv--)
					     {
					     int f_Caramel = f_cv;

					     m_vec_CountLock[f_Caramel]->m_Count--;
					
					     if(m_vec_CountLock[f_Caramel]->m_Count <= 0)
							{
							bool f_on = true;

							if(f_Caramel < (m_idx_vec_CountLock - 1))
								{
								f_on = false;
								}
								
							if(f_on == true)
								{
								std::shared_ptr<classCountLock> f_Lock = m_vec_CountLock[f_Caramel];

								f_Function->m_vec_String += f_Lock->m_String;

								if(f_Lock->m_String.compare("\n") != 0)
									{
									acResetLine();
									f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
									f_Function->m_idx_vec_CodeLineStorage++;

									f_vec_CodeLine->m_vec_Code.clear();
									f_vec_CodeLine->m_idx_vec_Code = 0;
									}

								acDecFactor(f_Lock->m_Factor);

								m_idx_vec_CountLock--;
								
								for(int f_XY = f_Caramel; f_XY < m_idx_vec_CountLock; f_XY++)
									{
									m_vec_CountLock[f_XY] = m_vec_CountLock[f_XY + 1];
									}
								
								if(f_Lock->m_String.compare(")") == 0)
									{
									bool f_ont = true;
									
									for(int f_cv1 = 1; f_cv1 < m_idx_vec_CountLock; f_cv1++)
										{
										for(int f_cv3 = 0; f_cv3 < m_vec_CountLock[f_cv1]->m_String.length(); f_cv3++)
											{
											if(m_vec_CountLock[f_cv1]->m_String.at(f_cv3) == ')')
												{
												f_ont = false;
												}
											}
										}
										
									if(f_ont == true)
										{
										acResetLine();
										f_Function->m_vec_CodeLineStorage.push_back(f_vec_CodeLine);
										f_Function->m_idx_vec_CodeLineStorage++;
										f_Function->m_vec_String += ";\n";

										f_vec_CodeLine->m_vec_Code.clear();
										f_vec_CodeLine->m_idx_vec_Code = 0;
										}
									}

								m_vec_CountLock.pop_back();
								}
							else
								{
								m_vec_CountLock[f_Caramel]->m_Count = 1;
								}
							}
						}
					}
				}
			}

		f_Function->m_vec_String.pop_back();

		f_Function->m_vec_String += "####";

		m_String += f_Function->m_vec_String;

		m_vec_Function.push_back(f_Function);
		m_idx_vec_Function++;
		}
#endif
}
#endif

void classTarget_JScript::acMergeUpper(void)
{
	/*for(int f_XY = 0; f_XY < m_CollectionScript->m_idx_vec_ElementScript; f_XY++)
		{
		//m_CollectionScript->m_vec_Element[m_CollectionScript->m_idx_vec_Element] = g_MasterTarget->m_CollectionScript->m_vec_Element[f_XY];
		//m_CollectionScript->m_idx_vec_Element++;
		//m_CollectionScript->m_vec_ElementScript[m_CollectionScript->m_idx_vec_ElementScript] = g_MasterTarget->m_CollectionScript->m_vec_ElementScript[f_XY];
		//m_CollectionScript->m_idx_vec_ElementScript++;
		}*/
	
	for(int f_Count = 0; f_Count < g_MasterTarget->m_idx_vec_Name; f_Count++)
		{
		m_vec_Name.push_back(g_MasterTarget->m_vec_Name[f_Count]);
		m_idx_vec_Name++;
		}
}
			
void classTarget_JScript::acMergeSave(void)
{
	/*for(int f_XY = 0; f_XY < m_CollectionScript->m_idx_vec_ElementScript; f_XY++)
		{
		g_MasterTarget->m_CollectionScript->m_vec_Element[g_MasterTarget->m_CollectionScript->m_idx_vec_Element] = m_CollectionScript->m_vec_Element[f_XY];
		g_MasterTarget->m_CollectionScript->m_idx_vec_Element++;
		//g_MasterTarget->m_CollectionScript->m_vec_ElementScript[g_MasterTarget->m_CollectionScript->m_idx_vec_ElementScript] = m_CollectionScript->m_vec_ElementScript[f_XY];
		//g_MasterTarget->m_CollectionScript->m_idx_vec_ElementScript++;
		}*/
		
	for(int f_CAP = 0; f_CAP < m_idx_vec_Name; f_CAP++)
		{
		g_MasterTarget->m_vec_Name.push_back(m_vec_Name[f_CAP]);
		g_MasterTarget->m_idx_vec_Name++;
		}
		
	g_MasterTarget->m_String += m_String;
}

int classLMap::acCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex, int f_ThreadElementIndex, int f_HowManyOnce)
{
	bool f_Success = true;

	int f_CorrectCount = 0;

	int f_StartElementIndex = f_ThreadElementIndex;
	int f_EndElementIndex = f_ThreadElementIndex + f_HowManyOnce;

	int f_MeasureIndex = g_CountLM * f_StartElementIndex;
	int f_EndMeasureIndex = g_CountLM * f_EndElementIndex;

	if(acPrepareLense(f_OCSCP_ThreadIndex, f_MeasureIndex) == false)
		{
		return 0;
		}

	int f_StartingMeasureIndex = f_MeasureIndex;
	int f_DrawnElements = 0;

	g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

	if(g_Wallet->m_vec_ComputeText_PrintMode[m_IDX] == ECOIN_MUTEX_MODE_OFF)
		{
		g_Wallet->m_vec_ComputeText_PrintMode[m_IDX] = ECOIN_MUTEX_MODE_GATHER;
		g_Wallet->m_vec_ComputeText[m_IDX].clear();

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

		int f_StartDrawnElem = m_LMap->m_vec_ElementID[f_MeasureIndex];

		int f_SrDrawnElem = f_StartDrawnElem;

		while((f_MeasureIndex < (f_EndMeasureIndex + 1)) && (f_Success == true) && ((g_Result == false) || (f_DrawnElements > 0)))
			{
			if(f_MeasureIndex < m_LMap->m_vec_Measure.size())
				{
				int f_ElementIndex = m_LMap->m_vec_ElementID[f_MeasureIndex];

				if(f_ElementIndex < f_Collection->m_vec_Element.size())
					{
					std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_MeasureIndex];
					std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementIndex];

					f_DrawnElements = f_ElementIndex - f_StartDrawnElem;

					if(f_ElementIndex > f_SrDrawnElem)
						{
						if(acSaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
							{
							f_Element->m_OCSCP_Flag = false;
							f_Success = false;
							f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
							__debugbreak();
#endif
#endif //add debug message
							}
						else
							{
							f_SrDrawnElem++;
							}
						}

					if(((g_Result == false) || (f_DrawnElements > 0)) && (f_Success == true))
						{
						switch(f_LMeasure->m_LMType)
							{
							case LMTYPE_MeasurementINTV1:
								{
								int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
									__debugbreak();
#endif
#endif //add debug message
									}
								else
									{
									f_CorrectCount++;
									}
						
								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%i - %i | %i - %i-%i\n", f_MeasureInteger, f_LMeasure->m_EndRange, f_LMeasure->m_MeasurementINTV1, f_LMeasure->m_EndRange, f_Success);

								g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

								g_Wallet->m_vec_ComputeText[m_IDX] += f_Char;

								g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

								delete f_Char;

								}break;

							case LMTYPE_MeasurementBLTV1:
								{
								bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
									__debugbreak();
#endif
#endif //add debug message
									}
								else
									{
									f_CorrectCount++;
									}

								char* f_Char = ag_ClearChar(32);

								::sprintf(f_Char, "%i - %s | %i - %s-%i\n", f_MeasureBoolean, "true", f_LMeasure->m_MeasurementBLTV1, "true", f_Success);

								g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

								g_Wallet->m_vec_ComputeText[m_IDX] += f_Char;

								g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

								delete f_Char;

								}break;
							}
						}
					else
						{
						f_Element->m_OCSCP_Flag = false;

						f_Success = false;
						}
					}
				else //above vec element boundary fail easy
					{
					f_DrawnElements = f_ElementIndex - f_StartDrawnElem;

					if(f_ElementIndex > f_SrDrawnElem)
						{
						if(acSaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
							{
							f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
							__debugbreak();
#endif
#endif //add debug message
							}
						else
							{
							f_SrDrawnElem++;
							}
						}

					f_Success = false;
					}
				}
			else //irregular FULL win conditions!
				{//condition
				if(m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] < m_LMap->m_vec_Measure.size())
					{
					f_DrawnElements = f_HowManyOnce;

					if((f_StartDrawnElem + f_DrawnElements) > f_SrDrawnElem)
						{						
						if(acSaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
							{
							f_Success = false;
							f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
							__debugbreak();
#endif
#endif //add debug message
							}
						else
							{
							f_SrDrawnElem++;
							}
						}
					}
				else // or lose
					{
					f_Success = false;
					}
				}

			f_MeasureIndex++;
			}

		if(f_DrawnElements > 0)
			{
			char* f_CharX = ag_ClearChar(256);

			::sprintf(f_CharX, "%i All Correct Measures\n%i Measures %i Elements\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size());

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ComputeText[m_IDX] += f_CharX;

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

			delete f_CharX;
			}
		else
			{
			char* f_CharX = ag_ClearChar(256);

			::sprintf(f_CharX, "%i Correct Measures False\n%i Measures %i Elements\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size());

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ComputeText[m_IDX] += f_CharX;

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

			delete f_CharX;
			}

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

		g_Wallet->m_vec_ComputeText_PrintMode[m_IDX] = ECOIN_MUTEX_MODE_PRINT;

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();
		}
	else  //mainflow - usual
		{
		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

		int f_StartDrawnElem = m_LMap->m_vec_ElementID[f_MeasureIndex];

		int f_SrDrawnElem = f_StartDrawnElem;

		while((f_MeasureIndex < (f_EndMeasureIndex + 1)) && (f_Success == true) && ((g_Result == false) || (f_DrawnElements > 0)))
			{
			if(f_MeasureIndex < m_LMap->m_vec_Measure.size())
				{
				int f_ElementIndex = m_LMap->m_vec_ElementID[f_MeasureIndex];

				if(f_ElementIndex < f_Collection->m_vec_Element.size())
					{
					std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_MeasureIndex];
					std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_ElementIndex];

					f_DrawnElements = f_ElementIndex - f_StartDrawnElem;

					if(f_ElementIndex > f_SrDrawnElem)
						{
						if(acSaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
							{
							f_Element->m_OCSCP_Flag = false;
							f_Success = false;
							f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
							__debugbreak();
#endif
#endif //add debug message
							}
						else
							{
							f_SrDrawnElem++;
							}
						}

					if(((g_Result == false) || (f_DrawnElements > 0)) && (f_Success == true))
						{
						switch(f_LMeasure->m_LMType)
							{
							case LMTYPE_MeasurementINTV1:
								{
								int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
									__debugbreak();
#endif
#endif //add debug message
									}

								}break;

							case LMTYPE_MeasurementBLTV1:
								{
								bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

								if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
									{
									f_Element->m_OCSCP_Flag = false;
									f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
									__debugbreak();
#endif
#endif //add debug message
									}

								}break;
							}
						}
					else
						{
						f_Element->m_OCSCP_Flag = false;

						f_Success = false;
						}
					}
				else
					{
					f_DrawnElements = f_ElementIndex - f_StartDrawnElem;

					if(f_ElementIndex > f_SrDrawnElem)
						{
						if(acSaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
							{
							f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
							__debugbreak();
#endif
#endif //add debug message
							}
						else
							{
							f_SrDrawnElem++;
							}
						}

					f_Success = false;
					}
				}
			else  //irregular win
				{ //condition
				if(m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] < m_LMap->m_vec_Measure.size())
					{
					f_DrawnElements = f_HowManyOnce;

					if((f_StartDrawnElem + f_DrawnElements) > f_SrDrawnElem)
						{
						f_SrDrawnElem++;
						
						if(acSaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
							{
							f_Success = false;
							f_DrawnElements = 0;

#ifdef ECOIN_DEBUG_BREAKS
#if 0
							__debugbreak();
#endif
#endif //add debug message
							}
						else
							{
							f_SrDrawnElem++;
							}
						}
					}
				else // or lose
					{
					f_Success = false;
					}
				}

			f_MeasureIndex++;
			}
		}

	return f_DrawnElements;
}

bool classLMap::acFinalCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex)
{
	bool f_Success = true;
	int f_CorrectCount = 0;

	acPrepareLense(f_OCSCP_ThreadIndex);

	g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

	//main-flow
	if(g_Wallet->m_vec_ComputeText_PrintMode_Lowton[m_IDX] == ECOIN_MUTEX_MODE_OFF)
		{
		g_Wallet->m_vec_ComputeText_PrintMode_Lowton[m_IDX] = ECOIN_MUTEX_MODE_GATHER;
		g_Wallet->m_vec_ComputeText_Lowton[m_IDX].clear();

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

		for(int f_Helly = 0; (f_Helly < f_Collection->m_vec_Element.size()) && (f_Success == true); f_Helly++)
			{
			std::shared_ptr<classElement> f_Element = f_Collection->m_vec_Element[f_Helly];

			for(int f_LM = 0; (f_LM < g_CountLM) && (f_Success == true); f_LM++)
				{
				int f_IntLM = (f_Helly * g_CountLM) + f_LM;

				if(f_IntLM < m_LMap->m_vec_Measure.size())
					{
					std::shared_ptr<LMeasure> f_LMeasure = m_LMap->m_vec_Measure[f_IntLM];

					switch(f_LMeasure->m_LMType)
						{
						case LMTYPE_MeasurementINTV1:
							{
							int f_MeasureInteger = ac_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

							if(f_MeasureInteger != f_LMeasure->m_MeasurementINTV1)
								{
								f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak();
#endif //add debug message
								}
							else
								{
								f_CorrectCount++;
								}
						
							char* f_Char = ag_ClearChar(32);

							::sprintf(f_Char, "%i - %i | %i - %i-%i\n", f_MeasureInteger, f_LMeasure->m_EndRange, f_LMeasure->m_MeasurementINTV1, f_LMeasure->m_EndRange, f_Success);

							g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

							g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_Char;

							g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

							delete f_Char;

							}break;

						case LMTYPE_MeasurementBLTV1:
							{
							bool f_MeasureBoolean = ac_takeMeasurementBLTV1(f_Element, f_LMeasure->m_Depth, f_LMeasure->m_Cap, f_OCSCP_ThreadIndex);

							if(f_MeasureBoolean != f_LMeasure->m_MeasurementBLTV1)
								{
								f_Success = false;

#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak();
#endif
								}
							else
								{
								f_CorrectCount++;
								}

							char* f_Char = ag_ClearChar(32);

							::sprintf(f_Char, "%i - %s | %i - %s-%i\n", f_MeasureBoolean, "true", f_LMeasure->m_MeasurementBLTV1, "true", f_Success);

							g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

							g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_Char;

							g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

							delete f_Char;

							}break;
						}
					}
				else
					{
					char* f_CharX = ag_ClearChar(256);

					::sprintf(f_CharX, "%i 'All Good' Correct True\n%i Measures %i Elements On ElementsMAX[%i]\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size(), m_ADMAX);

					g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

					g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_CharX;

					g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

					delete f_CharX;

					return f_Success;
					}
				}
			}

		if(f_Success == true)
			{
			f_Success = true;

			char* f_CharX = ag_ClearChar(256);

			::sprintf(f_CharX, "%i 'All Good' Correct True\n%i Measures %i Elements On ElementsMAX[%i]\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size(), m_ADMAX);

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_CharX;

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

			delete f_CharX;
			}
		else
			{
			char* f_CharX = ag_ClearChar(256);

			::sprintf(f_CharX, "%i Correct Measures LoadCom(0) False\n%i Measures %i Elements On ElementsMAX[%i]\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size(), m_ADMAX);

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_CharX;

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

			delete f_CharX;

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif //add debug message
			}

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

		g_Wallet->m_vec_ComputeText_PrintMode_Lowton[m_IDX] = ECOIN_MUTEX_MODE_PRINT;

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();
		}
	else
		{

		g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

#if 0
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
#endif
		}

	return f_Success;
}

bool classTarget_ESL_Script::acCompare(std::shared_ptr<classTarget_ESL_Script> f_Target, float f_QualityRank, float f_Grade)
{

	return false;
}

bool classTarget_JScript::acCompare(std::shared_ptr<classTarget_JScript> f_Target, float f_QualityRank, float f_Grade)
{
	f_Target->m_Mark = 0.0;
	
	 /////////////////////
	// Prime Evaluation
	//for(int f_XY = 0; f_XY < m_idx_vec_Function; f_XY++)
	//	{
	//	int f_Mark = f_Function->acInterrogate(f_QualityRank);
		
		std::shared_ptr<classMark> f_Mark = acMark_Bridges();
		
		if(g_EnablePR == true)
			{
			f_Mark->acIncrement(acMark_TestICO(f_Target));
			}
		
		f_Target->m_Mark = f_Mark->acSumStuff(f_QualityRank);
	//	}
	//else
	//	{
	//	return false;
	//	}
	
	 ///////////////////////
	// Prime Conditional
	if(f_Target->m_Mark >= f_Grade)
		{
		return true;
		}
	else
		{
		return false;
		}
}

/*classTarget_JScript.prototype.acCompareStructure = function(f_Target, f_QualityRank, f_Grade, f_testVolumes)
{
	f_Target->m_Mark = 0.0;
	
	 /////////////////////
	//Prime Conditional
	if(m_CollectionScript->m_idx_vec_ElementScript < f_Target->m_Collection->m_idx_vec_ElementScript)
		{
		for(int f_Count = 0; f_Count < m_Collection->m_idx_vec_Element; f_Count++)
			{
			var f_Element = m_Collection->m_vec_Element[f_Count];
			var f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			f_Target->m_Mark += f_Element.acCompare(f_TestElement, f_QualityRank, f_testVolumes);
			}
		}
	else
		{
		for(int f_Count = 0; f_Count < m_Collection->m_idx_vec_Element; f_Count++)
			{
			var f_fakeMark = 0.0;

			var f_Element = m_Collection->m_vec_Element[f_Count];
			var f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			var f_Mark = f_Element.acCompare(f_TestElement, f_QualityRank, f_testVolumes);
			f_fakeMark = f_Mark;

			for(int f_Cam = 0; f_Cam < f_Target->m_Collection->m_idx_vec_Element; f_Cam++)
				{
				var f_Element = m_Collection->m_vec_Element[f_Count];
				var f_TestElement = f_Target->m_Collection->m_vec_Element[f_Cam];

				var f_Mark = f_Element.acCompare(f_TestElement, f_QualityRank, f_testVolumes);
				if(f_Mark < f_fakeMark)
					{
					f_fakeMark = f_Mark;
					}
				}

			f_Target->m_Mark += f_fakeMark;
			}
		}

	if((f_Target->m_Mark <= f_Grade) && (f_Target->m_Mark != 0.0) && (f_Target->m_Mark > 1060.0))
		{
		return true;
		}
	else
		{
		return false;
		}

	/*if(Math.random() < 0.1)
		{
		console.log("CubeHESHGen(" + f_True + ")QualityRank[" + f_QualityRank + "]:Mark " + f_Target->m_Mark + " < Diff(" + f_Grade + ")tVol=" + f_testVolumes);
		}*/
//}

classInsta::classInsta(std::string f_StringC, int f_Type)
{
	std::string f_ref_CurrentPath = "classInsta::classInsta";

	m_Type = f_Type;
	m_String = f_StringC;
	
	m_Value = 0.0;

#ifndef OSI_MEM_APP
	ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
	ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Value");
#endif
}

/*classInsta.prototype.acInterrogation = function(f_LineCount, f_InstaCount, f_Line, f_LineSize)
{	
	var f_Mark = std::make_shared_reflect<classMark();
	
	 //////////////////////
	// Calc Results
	for(int f_Count = 0; f_Count < f_LineSize; f_Count++)
		{
		if(f_Line->m_vec_Code[f_Count]->m_Type != f_Target->m_vec_CodeLineStorage[f_LineCount][f_InstaCount]->m_Type)
			{
			f_Mark->m_vec_Int[0]++;
			}
			
		if(f_Count >= 1)
			{
			for(int f_inputCount = 0; f_inputCount < f_Target->m_idx_vec_CodeInputs; f_inputCount++)
				{
				if(f_Line->m_vec_Code[f_Count]->m_String != f_Target->m_vec_CodeInput[f_inputCount])
					{
					f_Mark->m_vec_Int[3]++;
					}
				}
			}
			
		if(f_Line->m_vec_Code[f_Count]->m_String != f_Target->m_vec_CodeLineStorage[f_LineCount][f_InstaCount]->m_String)
			{
			f_Mark->m_vec_Int[1]++;
			}
		}

	return f_Mark;
}*/

classMark::classMark()
{
	std::string f_ref_CurrentPath = "classMark::classMark";

	m_vec_Int.clear();
	m_idx_flip = 5;
	m_idx_vec_Int = 7;
	
	for(int f_X = 0; f_X < m_idx_vec_Int; f_X++)
		{
		m_vec_Int.push_back(0);
		}

#ifndef OSI_MEM_APP
	ac_Push(m_vec_Int, f_ref_CurrentPath + g_ref_Div + "m_vec_Int");
	ac_Push(m_idx_flip, f_ref_CurrentPath + g_ref_Div + "m_idx_flip");
	ac_Push(m_idx_vec_Int, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Int");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acReset", (void(ecom_base::*)(void))&classMark::acReset);
#endif
}

void classMark::acReset(void)
{
	for(int f_X = 0; f_X < m_idx_vec_Int; f_X++)
		{
		m_vec_Int[f_X] = 0;
		}
}

void classMark::acIncrement(std::shared_ptr<classMark> f_Mark)
{
	for(int f_X = 0; f_X < m_idx_vec_Int; f_X++)
		{
		m_vec_Int[f_X] += f_Mark->m_vec_Int[f_X];
		}
}

float classMark::acSumStuff(float f_QualityRank)
{
	float f_Mark = 0.0;

	   ////////////////
	  //
	 //
	// Movin to positive Marking Scheme
	for(int f_X = m_idx_flip; f_X < m_idx_vec_Int; f_X++)
		{
		f_Mark += m_vec_Int[f_X] * f_QualityRank; //adjustment
		}
	
	for(int f_X = 0; f_X < m_idx_flip; f_X++)
		{
		f_Mark -= m_vec_Int[f_X] * f_QualityRank;
		}
		
	return f_Mark;
}

classAchievement::classAchievement()
{
	std::string f_ref_CurrentPath = "classAchievement::classAchievement";

	ag_StatusLive(f_ref_CurrentPath, "m_Mark");
	m_Mark = std::make_shared_reflect<classMark>();
	m_Success = false;
	
	//m_vec_ReturnArgs = [];
	//m_idx_vec_ReturnArgs = 0;

#ifndef OSI_MEM_APP
	ac_Push(m_Success, f_ref_CurrentPath + g_ref_Div + "m_Success");
#endif
}

classFunction::classFunction()
{
	std::string f_ref_CurrentPath = "classFunction::classFunction";
	m_vec_String = "";
	
	m_Type = 0;
	m_Status = 0;

	m_Name = "";
	m_Hash = "";
	m_String = "";

	//>?
	//m_Level = [];
	//m_vec_Code = [];
	
	m_vec_Insta.clear();
	m_idx_vec_Insta = 0;
	
	m_vec_CodeLineStorage.clear();
	m_idx_vec_CodeLineStorage = 0;
	
	m_vec_CodeLineStorageFlag.clear();
	m_idx_vec_CodeLineStorageFlag = 0;

	ag_StatusLive(f_ref_CurrentPath, "m_Mark");
	m_Mark = std::make_shared_reflect<classMark>();

#ifndef OSI_MEM_APP
	ac_Push(m_vec_String, f_ref_CurrentPath + g_ref_Div + "m_vec_String");
	ac_Push(m_Type, f_ref_CurrentPath + g_ref_Div + "m_Type");
	ac_Push(m_Status, f_ref_CurrentPath + g_ref_Div + "m_Status");
	ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
	ac_Push(m_Hash, f_ref_CurrentPath + g_ref_Div + "m_Hash");
	ac_Push(m_String, f_ref_CurrentPath + g_ref_Div + "m_String");
	ac_Push(m_idx_vec_Insta, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_Insta");
	ac_Push(m_idx_vec_CodeLineStorage, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_CodeLineStorage");
	ac_Push(m_vec_CodeLineStorageFlag, f_ref_CurrentPath + g_ref_Div + "m_vec_CodeLineStorageFlag");
	ac_Push(m_idx_vec_CodeLineStorageFlag, f_ref_CurrentPath + g_ref_Div + "m_idx_vec_CodeLineStorageFlag");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acReset", (void(ecom_base::*)(void))&classMark::acReset);
#endif
}

void classFunction::acInsertAuthority(shared_ptr<classElement> f_Element, int f_Index)
{
	//generate mebbe linked lists of input control output data for each class name and then
	//call insertAuthority
}

std::shared_ptr<classMark> classFunction::acTestElement(shared_ptr<classElement> f_Element, int f_Index)
{
	std::string f_ref_CurrentPath = "classFunction::acTestElement";
	ag_StatusLive(f_ref_CurrentPath, "m_Mark");
	std::shared_ptr<classMark> f_Mark = std::make_shared_reflect<classMark>();
	
	//test element and producers return results
	//if(f_Element->m_Type == 
	//}
	//var f_Input = 
	
	return f_Mark;
}

std::string classTarget_JScript::ac_takeMeasurement(shared_ptr<classElement> f_Vertex)
{

	return "abeebc";
}

std::string classTarget_ESL_Script::ac_takeMeasurement(shared_ptr<classElement> f_Vertex)
{

	return "abeebc";
}

std::string classTarget_Ecom::ac_takeMeasurement(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth)
{
	std::string f_CharAry;
	f_CharAry.clear();

	int f_EcoinPrimeMsMax = 27;
	int f_EcoinControlMsMax = 15;
	int f_EcoinDigitMsMax = 10;

	bool f_Upper = true;

	bool f_PrimeControl = true;
	bool f_PrimeDigit = false;
	
	bool f_ScanMeasure = true;
	while(f_ScanMeasure == true)
		{
		if(f_PrimeControl == true) //prime measure
			{
			int f_PrimeValue = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, f_EcoinPrimeMsMax, 0, 3);

			if((f_PrimeValue >= 0) && (f_PrimeValue <= 25))
				{
				if(f_Upper == true)
					{
					f_CharAry.push_back((char)('A' + f_PrimeValue));
					}
				else
					{
					f_CharAry.push_back((char)('a' + f_PrimeValue));
					}
				}
			else if(f_PrimeValue == f_EcoinPrimeMsMax)
				{
				if(f_Upper == true)
					{
					f_Upper = false;
					}
				else
					{
					f_Upper = true;
					}
				}
			else if(f_PrimeValue == f_EcoinPrimeMsMax - 1)
				{
				f_PrimeControl = false;
				f_PrimeDigit = false;
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak(); //add debug message
				}
#endif
			}
		else //control method
			{
			if(f_PrimeDigit == false)
				{
				int f_ControlValue = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, f_EcoinControlMsMax, 0, 3);

				if((f_ControlValue >= 0) && (f_ControlValue <= 13))
					{
					if(f_ControlValue == 0)
						{
						f_CharAry.push_back((char)'_');
						}
					else if(f_ControlValue == 1)
						{
						f_CharAry.push_back((char)'-');
						}
					else if(f_ControlValue == 2)
						{
						f_CharAry.push_back((char)'>');
						}
					else if(f_ControlValue == 3)
						{
						f_CharAry.push_back((char)':');
						}
					else if(f_ControlValue == 4)
						{
						f_CharAry.push_back((char)'|');
						}
					else if(f_ControlValue == 5)
						{
						f_CharAry.push_back((char)'[');
						}
					else if(f_ControlValue == 6)
						{
						f_CharAry.push_back((char)']');
						}
					else if(f_ControlValue == 7)
						{
						f_CharAry.push_back((char)'*');
						}
					else if(f_ControlValue == 8)
						{
						f_CharAry.push_back((char)'.');
						}
					else if(f_ControlValue == 9)
						{
						f_CharAry.push_back((char)' ');
						}
					else if(f_ControlValue == 10)
						{
						f_CharAry.push_back((char)'<');
						}
					else if(f_ControlValue == 11)
						{
						f_CharAry.push_back((char)'X');
						}
					else if(f_ControlValue == 12)
						{
						f_CharAry.push_back((char)'X');
						}
					else if(f_ControlValue == 13)
						{
						f_CharAry.push_back((char)'X');
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak(); //add debug message
						}
#endif
					}
				else if(f_ControlValue == f_EcoinControlMsMax - 1)
					{
					f_PrimeControl = false;
					f_PrimeDigit = true;
					}
				else if(f_ControlValue == f_EcoinControlMsMax) //'all stop'
					{
					f_ScanMeasure = false;
					}
				}
			else
				{
				int f_DigitValue = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, f_EcoinDigitMsMax, 0, 3);

				if((f_DigitValue >= 0) && (f_DigitValue <= 9))
					{
					f_CharAry.push_back((char)('0' + f_DigitValue));
					}
				else if(f_DigitValue == f_EcoinDigitMsMax)
					{
					f_PrimeControl = true;
					f_PrimeDigit = false;
					}
#ifdef ECOIN_DEBUG_BREAKS
				else
					{
					__debugbreak(); //add debug message
					}
#endif
				}
			}
		}

	return f_CharAry;
}

std::string classTarget_Ecom::ac_takeMeasurement_DefaultValue(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth)
{
	std::string f_CharAry;
	f_CharAry.clear();

	bool f_ScanDef = true;
	while(f_ScanDef == true)
		{
		int f_LetterType = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 8, 0, 3);

		if(f_LetterType == 0)
			{
			int f_Letter = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 26, 0, 3);

			f_CharAry.push_back((char)(f_Letter + 'a'));
			}
		else if(f_LetterType == 1)
			{
			int f_Letter = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 26, 0, 3);

			f_CharAry.push_back((char)(f_Letter + 'A'));
			}
		else if(f_LetterType == 7)
			{
			int f_Letter = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 10, 0, 3);

			f_CharAry.push_back((char)(f_Letter + '0'));
			}
		else if(f_LetterType == 2)
			{
			f_CharAry.push_back('_');
			}
		else if(f_LetterType == 3)
			{
			f_CharAry.push_back('=');
			}
		else if(f_LetterType == 4)
			{
			f_CharAry.push_back('"');
			}
		else if(f_LetterType == 5)
			{
			f_CharAry.push_back('-');
			}
		else if(f_LetterType == 6)
			{
			f_CharAry.push_back('.');
			}
		else if(f_LetterType == 8)
			{
			f_CharAry.push_back(',');
			}
		else
			{
			//... '\' do nothing
			__debugbreak();
			}

		f_ScanDef = ac_takeMeasurementBLTV1(-1, -1, 0, -1, 0);
		}

	return f_CharAry;
}

std::string classTarget_Ecom::ac_takeMeasureKey(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth)
{
	std::string f_StringResult;
		
	for(int f_XYZ = 0; f_XYZ < 27; f_XYZ++)
		{
		int f_KEY_TEXT_TYPE = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 2, 0, 3);
		
		switch(f_KEY_TEXT_TYPE)
			{
			case ECOIN_KEYTEXTTYPEB58_NUM:
				{
				int f_SelectF = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 9, 0, 3);

				char f_Char = '0' + f_SelectF;

				f_StringResult.push_back(f_Char);
				}break;

			case ECOIN_KEYTEXTTYPEB58_UPP:
				{
				int f_SelectF = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 26, 0, 3);

				char f_Char = 'A' + f_SelectF;

				f_StringResult.push_back(f_Char);
				}break;

			case ECOIN_KEYTEXTTYPEB58_LOW:
				{
				int f_SelectF = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 26, 0, 3);

				char f_Char = 'a' + f_SelectF;

				f_StringResult.push_back(f_Char);
				}break;
			}
		}

	return f_StringResult;
}

std::string classLMap::ac_takeMeasurement(shared_ptr<classElement> f_Vertex)
{
	std::string f_CharAry;
	f_CharAry.clear();

#if 0
	int f_EcoinSpecMax = 17;
		
	bool f_ScanMeasure = true;
	while(f_ScanMeasure == true)
		{
		int f_CharValue = ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, f_EcoinSpecMax, 0, 3);
		
		if((f_CharValue >= 0) && (f_CharValue <= 9))
			{
			f_CharAry += '0' + f_CharValue;
			}
		else if(f_CharValue == 11) //win conditions Upper Alpha
			{
			int f_Value = ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 26, 0, 3);

			f_CharAry += 'A' + f_Value;
			}
		else if(f_CharValue == 12) //win conditions Lower Alpha
			{
			int f_Value = ac_takeMeasurementINTV1(-1, -1, -1, -1, 0, 26, 0, 3);

			f_CharAry += 'a' + f_Value;
			}
		else if(f_CharValue == 13)
			{
			f_CharAry += '_';
			}
		else if(f_CharValue == 14)
			{
			f_CharAry += '-';
			}
		else if(f_CharValue == 15)
			{
			f_CharAry += '>';
			}
		else if(f_CharValue == 16)
			{
			f_CharAry += '.';
			}
		else if(f_CharValue == 17)
			{
			f_ScanMeasure = false;
			}
		else
			{
			//throw;; //add debug message
			}
		}
#endif

	return f_CharAry;
}

//element level specify schema
int classTarget_JScript::ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	std::string f_ref_CurrentPath = "classTarget_JScript::ac_takeMeasurementINTV1";
	int m_Depth = f_Depth + 1;
	m_Depth--;
	
	f_Cap = 0;
	
	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt]->m_X, f_Vertex->vec_Vertex[f_HighestInt]->m_Y, f_Vertex->vec_Vertex[f_HighestInt]->m_Z);

#ifdef OSI_MEMORY_BIVECTOR_REF
			ag_StatusLive(f_ref_CurrentPath, "f_Vec");
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#else
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#endif

			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * SCP_LEN_AMP;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * SCP_LEN_AMP;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * SCP_LEN_AMP;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			m_SchemaRef[m_SchemaTop]->acBoundaryRanging();

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * ((int)(f_EndRange) - f_StartRange));

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			int f_Int = (int)(f_FloatA) + f_StartRange;

			return f_Int;
			}
		else if(m_SchemaTop == 1)
			{
			
			}
		else if(m_SchemaTop == 2)
			{
			
			}
		}

	return 1;
}

//element level specify schema
int classTarget_ESL_Script::ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	std::string f_ref_CurrentPath = "classTarget_ESL_Script::ac_takeMeasurementINTV1";
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;

	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt]->m_X, f_Vertex->vec_Vertex[f_HighestInt]->m_Y, f_Vertex->vec_Vertex[f_HighestInt]->m_Z);

#ifdef OSI_MEMORY_BIVECTOR_REF
			ag_StatusLive(f_ref_CurrentPath, "f_Vec");
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#else
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#endif

			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * SCP_LEN_AMP;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * SCP_LEN_AMP;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * SCP_LEN_AMP;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			m_SchemaRef[m_SchemaTop]->acBoundaryRanging();

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = (f_Theta * ((int)(f_EndRange)-f_StartRange));

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			int f_Int = (int)(f_FloatA) + f_StartRange;

			return f_Int;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1;
}

//element level specify schema
float classTarget_ESL_Script::ac_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	std::string f_ref_CurrentPath = "classTarget_ESL_Script::ac_takeMeasurementFLTV1";
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;

	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt]->m_X, f_Vertex->vec_Vertex[f_HighestInt]->m_Y, f_Vertex->vec_Vertex[f_HighestInt]->m_Z);

#ifdef OSI_MEMORY_BIVECTOR_REF
			ag_StatusLive(f_ref_CurrentPath, "f_Vec");
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#else
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#endif

			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * SCP_LEN_AMP;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * SCP_LEN_AMP;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * SCP_LEN_AMP;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			m_SchemaRef[m_SchemaTop]->acBoundaryRanging();

			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			float f_RangeVal = f_Theta * (f_EndRange - f_StartRange);

			if(f_RangeVal < 0.0)
				{
				f_RangeVal = f_RangeVal * -1;
				}

			float f_FloatA = f_RangeVal - (f_WeightRangetoStart / 2);

			float f_FloatB = f_FloatA + f_StartRange;

			int f_IntegerConv = (int)(f_FloatB);

			return f_FloatB;
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

//element level specify schema
bool classTarget_ESL_Script::ac_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	std::string f_ref_CurrentPath = "classTarget_ESL_Script::ac_takeMeasurementBLTV1";
	int m_Depth = f_Depth + 1;
	m_Depth--;
	f_Cap = 0;

	if(m_Depth >= 1)
		{
		if(m_SchemaTop == 0)
			{		//All distance test
			//obtain highest index of 8
			float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

			float f_HighestTheta = tan(f_HighestFloat);

			float f_HighestRangeVal = (f_HighestTheta * 8.0);

			if(f_HighestRangeVal < 0.0f)
				{
				f_HighestRangeVal = f_HighestRangeVal * -1.0f;
				}

			int f_HighestInt = (int)(f_HighestRangeVal);

			if(f_HighestInt > 7)
				{
				f_HighestInt = 7;
				}

			if(f_HighestInt < 0)
				{
				f_HighestInt = 0;
				}

			Cube::BiVector f_MeshVertex(f_Vertex->vec_Vertex[f_HighestInt]->m_X, f_Vertex->vec_Vertex[f_HighestInt]->m_Y, f_Vertex->vec_Vertex[f_HighestInt]->m_Z);

#ifdef OSI_MEMORY_BIVECTOR_REF
			ag_StatusLive(f_ref_CurrentPath, "f_Vec");
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#else
			std::shared_ptr<BiVector> f_Vec = std::make_shared<BiVector>();
#endif

			f_Vec->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_MeshVertex.m_X) * SCP_LEN_AMP;
			f_Vec->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_MeshVertex.m_Y) * SCP_LEN_AMP;
			f_Vec->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_MeshVertex.m_Z) * SCP_LEN_AMP;

			m_SchemaRef[m_SchemaTop]->m_X = f_Vec->m_X;
			m_SchemaRef[m_SchemaTop]->m_Y = f_Vec->m_Y;
			m_SchemaRef[m_SchemaTop]->m_Z = f_Vec->m_Z;

			m_SchemaRef[m_SchemaTop]->acBoundaryRanging();
				
			float f_Float = f_Vec->acDot();

			float f_Theta = sin(f_Float);

			if(f_Theta > 0.0f)
				{
				return true;
				}
			else
				{
				return false;
				}
			}
		else if(m_SchemaTop == 1)
			{
			//appeasement
			}
		else if(m_SchemaTop == 2)
			{
			//appeasement
			}
		}

	return 1.0f;
}

//element level specify schema
int classTarget_Ecom::ac_takeMeasurementINTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Cap)  // scale resolution 1-3
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::ac_takeMeasurementINTV1";

	//Element Index
	int f_ElementIndex = ag_Pull_gen_Element(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, f_StartRange, f_EndRange, f_WeightRangetoStart);

	//Select Element
	std::shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[f_ElementIndex];

	//naturalize ranges
	f_EndRange++;

	//obtain highest index of 8
	float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

	float f_HighestTheta = tan(f_HighestFloat);

	float f_HighestRangeVal = (f_HighestTheta * 8.0f);

	if(f_HighestRangeVal < 0.0f)
		{
		f_HighestRangeVal = f_HighestRangeVal * -1.0f;
		}

	int f_HighestInt = (int)(f_HighestRangeVal);

	if(f_HighestInt > 7)
		{
		f_HighestInt = 7;
		}

	if(f_HighestInt < 0)
		{
		f_HighestInt = 0;
		}

	m_SchemaRef[m_SchemaTop]->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_Element->vec_Vertex[f_HighestInt]->m_X) * SCP_LEN_AMP;
	m_SchemaRef[m_SchemaTop]->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_Element->vec_Vertex[f_HighestInt]->m_Y) * SCP_LEN_AMP;
	m_SchemaRef[m_SchemaTop]->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_Element->vec_Vertex[f_HighestInt]->m_Z) * SCP_LEN_AMP;

	m_SchemaRef[m_SchemaTop]->acLargeBoundaryRanging();

	float f_Float = m_SchemaRef[m_SchemaTop]->acDot();

	float f_Theta = sin(f_Float);

	float f_RangeVal = (f_Theta * ((float)(f_EndRange) - (float)f_StartRange));

	if(f_RangeVal < 0.0)
		{
		f_RangeVal = f_RangeVal * -1.0f;
		}

	float f_FloatA = f_RangeVal - ((float)f_WeightRangetoStart / 2.0f);

	int f_Int = (int)(f_FloatA) + f_StartRange;

	//win conditions!
	return f_Int;
}

int classLMap::ac_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_OCSCP_ThreadIndex)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_takeMeasurementINTV1";
#endif

	//All distance test
	//obtain highest index of 8 Vertices
	float f_HighestFloat = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;

	float f_HighestTheta = tan(f_HighestFloat);

	float f_HighestRangeVal = (f_HighestTheta * 8.0f);

	if(f_HighestRangeVal < 0.0f)
		{
		f_HighestRangeVal = f_HighestRangeVal * -1.0f;
		}

	int f_HighestInt = (int)(f_HighestRangeVal);

	if(f_HighestInt > 7)
		{
		f_HighestInt = 7;
		}

	if(f_HighestInt < 0)
		{
		f_HighestInt = 0;
		}

	m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_X * f_Vertex->vec_Vertex[f_HighestInt]->m_X) * SCP_LEN_AMP;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y * f_Vertex->vec_Vertex[f_HighestInt]->m_Y) * SCP_LEN_AMP;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z * f_Vertex->vec_Vertex[f_HighestInt]->m_Z) * SCP_LEN_AMP;

	m_SchemaRef[f_OCSCP_ThreadIndex]->acLargeBoundaryRanging();

	float f_Float = m_SchemaRef[f_OCSCP_ThreadIndex]->acDot();

	float f_Theta = sin(f_Float);

	float f_RangeVal = (f_Theta * ((float)(f_EndRange) - (float)f_StartRange));

	if(f_RangeVal < 0.0f)
		{
		f_RangeVal = f_RangeVal * -1.0f;
		}

	float f_FloatA = f_RangeVal - ((float)f_WeightRangetoStart / 2.0f);

	int f_Int = (int)(f_FloatA);

	f_Int += f_StartRange;

	//win conditions!
	return (int)(f_FloatA);
}

int ag_Pull_gen_Element(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart)
{
	g_ElementDivisorInt[f_OCSCP_ThreadIndex]++;

	if(g_ElementDivisorInt[f_OCSCP_ThreadIndex] > g_CountLM)
		{
		g_ElementDivisorInt[f_OCSCP_ThreadIndex] = 1;

		g_ElementDivisor[f_OCSCP_ThreadIndex]++;
		}

	return g_ElementDivisor[f_OCSCP_ThreadIndex];
}

void LMeasure::acClear(void)
{
	m_LMType = -1;
	m_Measurement.clear();
	m_MeasurementINTV1 = 0;
	m_MeasurementFLTV1 = 0.0f;
	m_MeasurementBLTV1 = false;
	m_MeasurementINTS = 0;

	m_StartRange = 0;
	m_EndRange = 0;
	m_WeightRangetoStart = 0;
	m_Depth = 0;
	m_Cap = 0;
	m_RangeWidth = 0;
	m_Boundary = 0;
	m_Notable = true;
	m_isInsertID = false;
	m_isOwnerID = false;
}

LMeasure::LMeasure(std::string f_Measurement)
{
	std::string f_ref_CurrentPath = "LMeasure::LMeasure";

	acClear();

	m_LMType = LMTYPE_Measurement;
	m_Measurement = f_Measurement;

#ifndef OSI_MEM_APP
	ac_Push(m_LMType, f_ref_CurrentPath + g_ref_Div + "m_LMType");
	ac_Push(m_Measurement, f_ref_CurrentPath + g_ref_Div + "m_Measurement");
	ac_Push(m_MeasurementINTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTV1");
	ac_Push(m_MeasurementFLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementFLTV1");
	ac_Push(m_MeasurementBLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementBLTV1");
	ac_Push(m_MeasurementINTS, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTS");
	ac_Push(m_StartRange, f_ref_CurrentPath + g_ref_Div + "m_StartRange");
	ac_Push(m_EndRange, f_ref_CurrentPath + g_ref_Div + "m_EndRange");
	ac_Push(m_WeightRangetoStart, f_ref_CurrentPath + g_ref_Div + "m_WeightRangetoStart");
	ac_Push(m_Depth, f_ref_CurrentPath + g_ref_Div + "m_Depth");
	ac_Push(m_Cap, f_ref_CurrentPath + g_ref_Div + "m_Cap");
	ac_Push(m_RangeWidth, f_ref_CurrentPath + g_ref_Div + "m_RangeWidth");
	ac_Push(m_Boundary, f_ref_CurrentPath + g_ref_Div + "m_Boundary");
	ac_Push(m_Notable, f_ref_CurrentPath + g_ref_Div + "m_Notable");
	ac_Push(m_isInsertID, f_ref_CurrentPath + g_ref_Div + "m_isInsertID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

LMeasure::LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_MeasurementINTV1)
{
	std::string f_ref_CurrentPath = "LMeasure::LMeasure";

	acClear();

	m_LMType = LMTYPE_MeasurementINTV1;
	m_MeasurementINTV1 = f_MeasurementINTV1;

	m_StartRange = f_StartRange;
	m_EndRange = f_EndRange;
	m_WeightRangetoStart = f_WeightRangetoStart;
	m_Depth = f_Depth;
	m_Cap = f_Cap;

#ifndef OSI_MEM_APP
	ac_Push(m_LMType, f_ref_CurrentPath + g_ref_Div + "m_LMType");
	ac_Push(m_Measurement, f_ref_CurrentPath + g_ref_Div + "m_Measurement");
	ac_Push(m_MeasurementINTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTV1");
	ac_Push(m_MeasurementFLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementFLTV1");
	ac_Push(m_MeasurementBLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementBLTV1");
	ac_Push(m_MeasurementINTS, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTS");
	ac_Push(m_StartRange, f_ref_CurrentPath + g_ref_Div + "m_StartRange");
	ac_Push(m_EndRange, f_ref_CurrentPath + g_ref_Div + "m_EndRange");
	ac_Push(m_WeightRangetoStart, f_ref_CurrentPath + g_ref_Div + "m_WeightRangetoStart");
	ac_Push(m_Depth, f_ref_CurrentPath + g_ref_Div + "m_Depth");
	ac_Push(m_Cap, f_ref_CurrentPath + g_ref_Div + "m_Cap");
	ac_Push(m_RangeWidth, f_ref_CurrentPath + g_ref_Div + "m_RangeWidth");
	ac_Push(m_Boundary, f_ref_CurrentPath + g_ref_Div + "m_Boundary");
	ac_Push(m_Notable, f_ref_CurrentPath + g_ref_Div + "m_Notable");
	ac_Push(m_isInsertID, f_ref_CurrentPath + g_ref_Div + "m_isInsertID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

LMeasure::LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_MeasurementFLTV1)
{
	std::string f_ref_CurrentPath = "LMeasure::LMeasure";

	acClear();

	m_LMType = LMTYPE_MeasurementFLTV1;
	m_MeasurementFLTV1 = f_MeasurementFLTV1;

	m_StartRange = f_StartRange;
	m_EndRange = f_EndRange;
	m_WeightRangetoStart = f_WeightRangetoStart;
	m_Depth = f_Depth;
	m_Cap = f_Cap;

#ifndef OSI_MEM_APP
	ac_Push(m_LMType, f_ref_CurrentPath + g_ref_Div + "m_LMType");
	ac_Push(m_Measurement, f_ref_CurrentPath + g_ref_Div + "m_Measurement");
	ac_Push(m_MeasurementINTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTV1");
	ac_Push(m_MeasurementFLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementFLTV1");
	ac_Push(m_MeasurementBLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementBLTV1");
	ac_Push(m_MeasurementINTS, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTS");
	ac_Push(m_StartRange, f_ref_CurrentPath + g_ref_Div + "m_StartRange");
	ac_Push(m_EndRange, f_ref_CurrentPath + g_ref_Div + "m_EndRange");
	ac_Push(m_WeightRangetoStart, f_ref_CurrentPath + g_ref_Div + "m_WeightRangetoStart");
	ac_Push(m_Depth, f_ref_CurrentPath + g_ref_Div + "m_Depth");
	ac_Push(m_Cap, f_ref_CurrentPath + g_ref_Div + "m_Cap");
	ac_Push(m_RangeWidth, f_ref_CurrentPath + g_ref_Div + "m_RangeWidth");
	ac_Push(m_Boundary, f_ref_CurrentPath + g_ref_Div + "m_Boundary");
	ac_Push(m_Notable, f_ref_CurrentPath + g_ref_Div + "m_Notable");
	ac_Push(m_isInsertID, f_ref_CurrentPath + g_ref_Div + "m_isInsertID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

LMeasure::LMeasure(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, float f_Boundary, float f_MeasurementFLTV5)
{
	std::string f_ref_CurrentPath = "LMeasure::LMeasure";

	acClear();

	m_LMType = LMTYPE_MeasurementFLTV5_LB;
	m_MeasurementFLTV1 = f_MeasurementFLTV5;

	m_StartRange = f_StartRange;
	m_EndRange = f_EndRange;
	m_WeightRangetoStart = f_WeightRangetoStart;
	m_Depth = f_Depth;
	m_Cap = f_Cap;
	m_Boundary = f_Boundary;

#ifndef OSI_MEM_APP
	ac_Push(m_LMType, f_ref_CurrentPath + g_ref_Div + "m_LMType");
	ac_Push(m_Measurement, f_ref_CurrentPath + g_ref_Div + "m_Measurement");
	ac_Push(m_MeasurementINTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTV1");
	ac_Push(m_MeasurementFLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementFLTV1");
	ac_Push(m_MeasurementBLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementBLTV1");
	ac_Push(m_MeasurementINTS, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTS");
	ac_Push(m_StartRange, f_ref_CurrentPath + g_ref_Div + "m_StartRange");
	ac_Push(m_EndRange, f_ref_CurrentPath + g_ref_Div + "m_EndRange");
	ac_Push(m_WeightRangetoStart, f_ref_CurrentPath + g_ref_Div + "m_WeightRangetoStart");
	ac_Push(m_Depth, f_ref_CurrentPath + g_ref_Div + "m_Depth");
	ac_Push(m_Cap, f_ref_CurrentPath + g_ref_Div + "m_Cap");
	ac_Push(m_RangeWidth, f_ref_CurrentPath + g_ref_Div + "m_RangeWidth");
	ac_Push(m_Boundary, f_ref_CurrentPath + g_ref_Div + "m_Boundary");
	ac_Push(m_Notable, f_ref_CurrentPath + g_ref_Div + "m_Notable");
	ac_Push(m_isInsertID, f_ref_CurrentPath + g_ref_Div + "m_isInsertID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

LMeasure::LMeasure(int f_Depth, int f_Cap, bool f_MeasurementBLTV1)
{
	std::string f_ref_CurrentPath = "LMeasure::LMeasure";

	acClear();

	m_LMType = LMTYPE_MeasurementBLTV1;
	m_MeasurementBLTV1 = f_MeasurementBLTV1;

	m_Depth = f_Depth;
	m_Cap = f_Cap;

	m_StartRange = -1;
	m_EndRange = -1;
	m_WeightRangetoStart = -1;

#ifndef OSI_MEM_APP
	ac_Push(m_LMType, f_ref_CurrentPath + g_ref_Div + "m_LMType");
	ac_Push(m_Measurement, f_ref_CurrentPath + g_ref_Div + "m_Measurement");
	ac_Push(m_MeasurementINTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTV1");
	ac_Push(m_MeasurementFLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementFLTV1");
	ac_Push(m_MeasurementBLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementBLTV1");
	ac_Push(m_MeasurementINTS, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTS");
	ac_Push(m_StartRange, f_ref_CurrentPath + g_ref_Div + "m_StartRange");
	ac_Push(m_EndRange, f_ref_CurrentPath + g_ref_Div + "m_EndRange");
	ac_Push(m_WeightRangetoStart, f_ref_CurrentPath + g_ref_Div + "m_WeightRangetoStart");
	ac_Push(m_Depth, f_ref_CurrentPath + g_ref_Div + "m_Depth");
	ac_Push(m_Cap, f_ref_CurrentPath + g_ref_Div + "m_Cap");
	ac_Push(m_RangeWidth, f_ref_CurrentPath + g_ref_Div + "m_RangeWidth");
	ac_Push(m_Boundary, f_ref_CurrentPath + g_ref_Div + "m_Boundary");
	ac_Push(m_Notable, f_ref_CurrentPath + g_ref_Div + "m_Notable");
	ac_Push(m_isInsertID, f_ref_CurrentPath + g_ref_Div + "m_isInsertID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

LMeasure::LMeasure(int f_RangeWidth, int f_WeightRangetoStart, int f_MeasurementINTS)
{
	std::string f_ref_CurrentPath = "LMeasure::LMeasure";

	acClear();

	m_LMType = LMTYPE_MeasurementBLTV1;
	m_MeasurementINTS = f_MeasurementINTS;

	m_RangeWidth = f_RangeWidth;
	m_WeightRangetoStart = f_WeightRangetoStart;

#ifndef OSI_MEM_APP
	ac_Push(m_LMType, f_ref_CurrentPath + g_ref_Div + "m_LMType");
	ac_Push(m_Measurement, f_ref_CurrentPath + g_ref_Div + "m_Measurement");
	ac_Push(m_MeasurementINTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTV1");
	ac_Push(m_MeasurementFLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementFLTV1");
	ac_Push(m_MeasurementBLTV1, f_ref_CurrentPath + g_ref_Div + "m_MeasurementBLTV1");
	ac_Push(m_MeasurementINTS, f_ref_CurrentPath + g_ref_Div + "m_MeasurementINTS");
	ac_Push(m_StartRange, f_ref_CurrentPath + g_ref_Div + "m_StartRange");
	ac_Push(m_EndRange, f_ref_CurrentPath + g_ref_Div + "m_EndRange");
	ac_Push(m_WeightRangetoStart, f_ref_CurrentPath + g_ref_Div + "m_WeightRangetoStart");
	ac_Push(m_Depth, f_ref_CurrentPath + g_ref_Div + "m_Depth");
	ac_Push(m_Cap, f_ref_CurrentPath + g_ref_Div + "m_Cap");
	ac_Push(m_RangeWidth, f_ref_CurrentPath + g_ref_Div + "m_RangeWidth");
	ac_Push(m_Boundary, f_ref_CurrentPath + g_ref_Div + "m_Boundary");
	ac_Push(m_Notable, f_ref_CurrentPath + g_ref_Div + "m_Notable");
	ac_Push(m_isInsertID, f_ref_CurrentPath + g_ref_Div + "m_isInsertID");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acResetLine", (void(ecom_base::*)(void))&classTarget_Ecom::acResetLine);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acPrepare_Lense", (void(ecom_base::*)(void))&classTarget_Ecom::acPrepare_Lense);
#endif
}

#if 0
	//ECOIN CONTROL MEASURES
	0-9 x
	_ x : 10
	- x : 11
	> x : 12
	: x : 13
	| x : 14
	[ x : 15
	] x : 16
	* x : 17
	. x : 18
  ' ' x : 19
	< x : 20
	  x Empty1 : 21
	  x Empty2 : 22
	  x Empty3 : 23
#endif

#if 0
std::string classLMap::ac_recordMeasurement(std::string f_RecordResult, int f_ElementID, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	bool f_HoldonElement = true;

	std::string f_CharAry;
	f_CharAry.clear();

	int f_EcoinControlMsMax = 25;
	int f_EcoinPrimeMsMax = 27;

	bool f_Upper = true;
	bool f_PrimeControl = true;

	if(f_RecordResult.length() == 0) //default empty
		{
		//prime measure send control measure
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

		f_PrimeControl = false;

		//control measure send 'All Stop'
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax, f_ElementID);

		return f_CharAry;
		}

	for(int f_Jet = 0; f_Jet < f_RecordResult.length(); f_Jet++)
		{
		char f_c = f_RecordResult.at(f_Jet);

		if(isupper(f_c) == 1)
			{
			//primecontrol measure
			if(f_PrimeControl == false)
				{
				//Control measure
				if(f_HoldonElement == false)
					{
					f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
					}
				else
					{
					f_HoldonElement = false;
					}

				ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax - 1, f_ElementID);

				f_PrimeControl = true;
				}

			if(f_Upper == false) //Lower -> Upper
				{
				if(f_HoldonElement == false)
					{
					f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
					}
				else
					{
					f_HoldonElement = false;
					}

				ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax, f_ElementID);

				f_Upper = true;
				}

			if(f_HoldonElement == false)
				{
				f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
				}
			else
				{
				f_HoldonElement = false;
				}

			int f_LetterCode = ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_c - 'A', f_ElementID);

			f_CharAry.push_back((char)(f_LetterCode + 'A'));
			}
		else
			{
			if((f_c >= 'a') && (f_c <= 'z'))
				{
				//primecontrol measure
				if(f_PrimeControl == false)
					{
					//Control measure
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax - 1, f_ElementID);

					f_PrimeControl = true;
					}

				if(f_Upper == true) //Upper -> Lower
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax, f_ElementID);

					f_Upper = false;
					}

				//lowercase measure
				if(f_HoldonElement == false)
					{
					f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
					}
				else
					{
					f_HoldonElement = false;
					}

				int f_LetterCode = ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_c - 'a', f_ElementID);

				f_CharAry.push_back((char)(f_LetterCode + 'a'));
				}
			else
				{
				//primecontrol measure
				if(f_PrimeControl == true)
					{
					//Control measure
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

					f_PrimeControl = false;
					}

				//Control measure
				if((f_c >= '0') && (f_c <= '9'))	//win conditions number
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_c - '0', f_ElementID);

					f_CharAry.push_back((char)(f_LetterChar + '0'));
					}
				else if(f_c == '_')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 10, f_ElementID);

					f_CharAry.push_back('_');
					}
				else if(f_c == '-')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 11, f_ElementID);

					f_CharAry.push_back('-');
					}
				else if(f_c == '>')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 12, f_ElementID);

					f_CharAry.push_back('>');
					}
				else if(f_c == ':')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 13, f_ElementID);

					f_CharAry.push_back(':');
					}
				else if(f_c == '|')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 14, f_ElementID);

					f_CharAry.push_back('|');
					}
				else if(f_c == '[')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 15, f_ElementID);

					f_CharAry.push_back('[');
					}
				else if(f_c == ']')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 16, f_ElementID);

					f_CharAry.push_back(']');
					}
				else if(f_c == '*')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 17, f_ElementID);

					f_CharAry.push_back('*');
					}
				else if(f_c == '.')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 18, f_ElementID);

					f_CharAry.push_back('.');
					}
				else if(f_c == ' ')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 19, f_ElementID);

					f_CharAry.push_back(' ');
					}
				else if(f_c == '<')
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 20, f_ElementID);

					f_CharAry.push_back('<');
					}
#ifdef ECOIN_SPECIAL_CHAR_APPENDIX
				else if(f_c == '?') //Activate Empty 1
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 21, f_ElementID);

					f_CharAry.push_back('.');
					}
				else if(f_c == '?') //Activate Empty 2
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 22, f_ElementID);

					f_CharAry.push_back('.');
					}
				else if(f_c == '?') //Activate Empty 2
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 23, f_ElementID);

					f_CharAry.push_back('.');
					}
#endif
#if 0
#ifdef ECOIN_DEBUG_BREAKS
				else
					{
					__debugbreak();
					}
#endif
#endif
				}
			}
		}

	//primecontrol measure
	if(f_PrimeControl == true)
		{
		//Control measure
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

		f_PrimeControl = false;
		}

	//control measure send 'All Stop'
	if(f_HoldonElement == false)
		{
		f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		}
	else
		{
		f_HoldonElement = false;
		}

	ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax, f_ElementID); //end cap

	return f_CharAry;
}
#endif

std::string classLMap::ac_recordMeasurement(std::string f_RecordResult, int f_ElementID, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	bool f_HoldonElement = true;

	std::string f_CharAry;
	f_CharAry.clear();

	int f_EcoinPrimeMsMax = 27;
	int f_EcoinControlMsMax = 15;
	int f_EcoinDigitMsMax = 10;

	bool f_Upper = true;

	bool f_PrimeControl = true;
	bool f_PrimeDigit = false;

	if(f_RecordResult.length() == 0) //default empty
		{
		//prime measure send control measure
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

		f_PrimeControl = false;

		//control measure send 'All Stop'
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax, f_ElementID);

		return f_CharAry;
		}

	for(int f_Jet = 0; f_Jet < f_RecordResult.length(); f_Jet++)
		{
		char f_c = f_RecordResult.at(f_Jet);

		if(isupper(f_c) == 1)
			{
			//primecontrol measure [code]
			if(f_PrimeControl == false)
				{
				if(f_PrimeDigit == true)
					{
					//Digit measure
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_EcoinDigitMsMax, f_ElementID);

					f_PrimeDigit = false;
					}
				else
					{
					//Control measure
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax - 1, f_ElementID);

					//Control measure
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_EcoinDigitMsMax, f_ElementID);

					f_PrimeDigit = false;
					}

				//enforce prime == true
				f_PrimeControl = true;
				}

			if(f_Upper == false) //Lower -> Upper
				{
				if(f_HoldonElement == false)
					{
					f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
					}
				else
					{
					f_HoldonElement = false;
					}

				ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax, f_ElementID);

				f_Upper = true;
				}

			if(f_HoldonElement == false)
				{
				f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
				}
			else
				{
				f_HoldonElement = false;
				}

			int f_LetterCode = ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_c - 'A', f_ElementID);

			f_CharAry.push_back((char)(f_LetterCode + 'A'));
			}
		else
			{
			if((f_c >= 'a') && (f_c <= 'z'))
				{
				//primecontrol measure [code]
				if(f_PrimeControl == false)
					{
					if(f_PrimeDigit == true)
						{
						//Digit measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_EcoinDigitMsMax, f_ElementID);

						f_PrimeDigit = false;
						}
					else
						{
						//Control measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax - 1, f_ElementID);

						//Control measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_EcoinDigitMsMax, f_ElementID);

						f_PrimeDigit = false;
						}

					//enforce prime == true
					f_PrimeControl = true;
					}

				if(f_Upper == true) //Upper -> Lower
					{
					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax, f_ElementID);

					f_Upper = false;
					}

				//lowercase measure
				if(f_HoldonElement == false)
					{
					f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
					}
				else
					{
					f_HoldonElement = false;
					}

				int f_LetterCode = ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_c - 'a', f_ElementID);

				f_CharAry.push_back((char)(f_LetterCode + 'a'));
				}
			else
				{
				//Control measure
				if((f_c >= '0') && (f_c <= '9'))	//win conditions number
					{
					//primecontrol measure [code]
					if(f_PrimeControl == true)
						{
						//Prime measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

						f_PrimeControl = false;

						//Control measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax - 1, f_ElementID);

						f_PrimeDigit = true;
						}
					else
						{
						if(f_PrimeDigit == false) // in control
							{
							//Control measure
							if(f_HoldonElement == false)
								{
								f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
								}
							else
								{
								f_HoldonElement = false;
								}

							ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax, f_ElementID);

							f_PrimeDigit = true;
							}
						}

					if(f_HoldonElement == false)
						{
						f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
						}
					else
						{
						f_HoldonElement = false;
						}

					int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_c - '0', f_ElementID);

					f_CharAry.push_back((char)(f_LetterChar + '0'));
					}
				else
					{
					//primecontrol measure [code]
					if(f_PrimeControl == true)
						{
						//Prime measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

						f_PrimeControl = false;
						}
					
					if(f_PrimeDigit == true)
						{
						//Control measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_EcoinDigitMsMax, f_ElementID);

						f_PrimeDigit = false;

						//Prime measure
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

						f_PrimeControl = false;
						}

					if(f_c == '_')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 0, f_ElementID);

						f_CharAry.push_back('_');
						}
					else if(f_c == '-')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 1, f_ElementID);

						f_CharAry.push_back('-');
						}
					else if(f_c == '>')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 2, f_ElementID);

						f_CharAry.push_back('>');
						}
					else if(f_c == ':')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 3, f_ElementID);

						f_CharAry.push_back(':');
						}
					else if(f_c == '|')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 4, f_ElementID);

						f_CharAry.push_back('|');
						}
					else if(f_c == '[')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 5, f_ElementID);

						f_CharAry.push_back('[');
						}
					else if(f_c == ']')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 6, f_ElementID);

						f_CharAry.push_back(']');
						}
					else if(f_c == '*')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 7, f_ElementID);

						f_CharAry.push_back('*');
						}
					else if(f_c == '.')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 8, f_ElementID);

						f_CharAry.push_back('.');
						}
					else if(f_c == ' ')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 9, f_ElementID);

						f_CharAry.push_back(' ');
						}
					else if(f_c == '<')
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 10, f_ElementID);

						f_CharAry.push_back('<');
						}
#ifdef ECOIN_SPECIAL_CHAR_APPENDIX
					else if(f_c == '?') //Activate Empty 1
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 11, f_ElementID);

						f_CharAry.push_back('.');
						}
					else if(f_c == '?') //Activate Empty 2
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 12, f_ElementID);

						f_CharAry.push_back('.');
						}
					else if(f_c == '?') //Activate Empty 2
						{
						if(f_HoldonElement == false)
							{
							f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
							}
						else
							{
							f_HoldonElement = false;
							}

						int f_LetterChar = ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, 13, f_ElementID);

						f_CharAry.push_back('.');
						}
#endif
					}
				}
			}
		}

	if(f_PrimeDigit == true)
		{
		//Control measure
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3, 4, f_EcoinDigitMsMax, f_ElementID);

		f_PrimeDigit = false;
		f_PrimeControl = true;
		}

	//primecontrol measure
	if(f_PrimeControl == true)
		{
		//Control measure
		if(f_HoldonElement == false)
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
			}
		else
			{
			f_HoldonElement = false;
			}

		ac_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3, 4, f_EcoinPrimeMsMax - 1, f_ElementID);

		f_PrimeControl = false;
		}

	//control measure send 'All Stop'
	if(f_HoldonElement == false)
		{
		f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);
		}
	else
		{
		f_HoldonElement = false;
		}

	ac_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3, 4, f_EcoinControlMsMax, f_ElementID); //end cap

	return f_CharAry;
}

std::string classLMap::ac_recordMeasurement_DefaultValue(std::string f_RecordResult, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	int f_ElementIndex = 0;
	std::string f_DefaultValueStr = "";
	bool f_Scan = true;
	int f_Jet = 0;

	while(f_Scan == true)
		{
		char f_c = f_RecordResult.at(f_Jet);

		if(f_c == '_')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, -1, 2, f_ElementIndex);

			f_DefaultValueStr.push_back('_');
			}
		else if(f_c == '=')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, -1, 3, f_ElementIndex);

			f_DefaultValueStr.push_back('=');
			}
		else if(f_c == '"')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, -1, 4, f_ElementIndex);

			f_DefaultValueStr.push_back('"');
			}
		else if(f_c == '-')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, -1, 5, f_ElementIndex);

			f_DefaultValueStr.push_back('-');
			}
		else if(f_c == '.')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, -1, 6, f_ElementIndex);

			f_DefaultValueStr.push_back('.');
			}
		else if(isupper(f_c) == 1)
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, 1, 1, f_ElementIndex);

			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 26, 0, -1, 4, f_c - 'A', f_ElementIndex);

			f_DefaultValueStr.push_back(f_c);
			}
		else if((f_c >= 'a') && (f_c <= 'z'))
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, 0, 0, f_ElementIndex);

			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 26, 0, -1, 4, f_c - 'a', f_ElementIndex);

			f_DefaultValueStr.push_back(f_c);
			}
		else if((f_c >= '0') && (f_c <= '9'))
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, 0, 7, f_ElementIndex);

			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 10, 0, -1, 4, f_c - '0', f_ElementIndex);

			f_DefaultValueStr.push_back(f_c);
			}
		else if(f_c == ',')
			{
			f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 8, 0, -1, 0, 8, f_ElementIndex);

			f_DefaultValueStr.push_back(',');
			}
		else if(f_c == '\\')
			{
			//... '\' do nothing
#if 0
			__debugbreak();
#endif
			}
		else
			{
			//... '\' do nothing
			__debugbreak();
			}

		f_Jet++;

		f_ElementIndex = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

		f_Scan = ac_recordMeasurementBLTV1(0, 4, (f_Jet < f_RecordResult.length()) ? true : false, f_ElementIndex);
		}

	return f_DefaultValueStr;
}

//notice do not pull element in function above this one
std::string classLMap::ac_recordMeasureKey(std::string f_RecordResult, int f_ElementID, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	std::string f_StringResult = "";

	int f_IndexID = 2;

	for(int f_Jet = 0; f_Jet < 27; f_Jet++)
		{
		char f_c = f_RecordResult.at(f_Jet);

		if((f_c >= '0') && (f_c <= '9'))
			{
			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 2, 0, 3, 4, ECOIN_KEYTEXTTYPEB58_NUM, f_ElementID);

			ac_lastMeasurement(f_IndexID);

			int f_RC = (int)f_c - (int)'0';

			f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

			ac_recordMeasurementINTV1(0, 9, 0, 3, 4, f_RC, f_ElementID);

			ac_lastMeasurement(f_IndexID);
			}
		else
			{
			if(isupper(f_c) == 1)
				{
				f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementINTV1(0, 2, 0, 3, 4, ECOIN_KEYTEXTTYPEB58_UPP, f_ElementID);

				ac_lastMeasurement(f_IndexID);

				int f_RC = (int)f_c - (int)'A';

				f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementINTV1(0, 26, 0, 3, 4, f_RC, f_ElementID);

				ac_lastMeasurement(f_IndexID);
				}
			else
				{
				f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementINTV1(0, 2, 0, 3, 4, ECOIN_KEYTEXTTYPEB58_LOW, f_ElementID);

				ac_lastMeasurement(f_IndexID);

				int f_RC = (int)f_c - (int)'a';

				f_ElementID = acPull_gen_ElementID(f_StartAD, f_EndAD, f_ElementMax, f_Depth);

				ac_recordMeasurementINTV1(0, 26, 0, 3, 4, f_RC, f_ElementID);

				ac_lastMeasurement(f_IndexID);
				}
			}

		f_StringResult.push_back(f_c);
		}

	return f_StringResult;
}

int classLMap::ac_recordMeasurementINTV1(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Depth, int f_Cap, int f_RecordResult, int f_ElementID, bool f_Notable)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_recordMeasurementINTV1";
#endif

	//apply endrange inclusive
	f_EndRange++;

	//apply startrange inclusive
	f_RecordResult -= f_StartRange;

	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	ag_StatusLive(f_ref_CurrentPath, "f_Measure");

	shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(f_StartRange, f_EndRange, f_WeightRangetoStart, f_Depth, f_Cap, f_RecordResult);

	f_Measure->m_Notable = f_Notable;

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);

	f_RecordResult += f_StartRange;

	return f_RecordResult;
}

std::string classLMap::ac_recordMeasurementFLTV1(int f_ElementID, std::string f_extString)  // scale resolution 1-3
{
	std::string f_ResultStringPre = f_extString;
	std::string f_ResultString = "";

	int f_ClackCap = 0;
	bool f_Minus = false;

	if(f_ResultStringPre.at(0) == '-')
		{
		ac_recordMeasurementBLTV1(0, 4, true, f_ElementID);

		for(int f_Int = 1; f_Int < f_ResultStringPre.length(); f_Int++)
			{
			f_ResultString.push_back(f_ResultStringPre.at(f_Int));
			}

		f_Minus = true;
		}
	else
		{
		ac_recordMeasurementBLTV1(0, 4, false, f_ElementID);

		f_ResultString = f_ResultStringPre;
		}

	for(int f_Jet = 0; f_Jet < f_ResultString.length(); f_Jet++)
		{
		char f_c = f_ResultString.at(f_Jet);

		if(f_c == '.')
			{
			f_ClackCap = f_Jet;
			}
		}

	if(f_ClackCap <= 0)
		{
		f_ClackCap = 0;
		}

	if(f_ClackCap > 12)
		{
		f_ClackCap = 12;
		}

	f_ElementID = acPull_gen_ElementID(-1, -1, -1, -1);

	int f_ClackApp = ag_min(ag_max(f_ClackCap, 12), 1);

	int f_ClackLength = ac_recordMeasurementINTV1(1, 12, 0, 3, 1, f_ClackCap, f_ElementID);

	f_ElementID = acPull_gen_ElementID(-1, -1, -1, -1);

	int f_Length = ac_recordMeasurementINTV1(3, 18, 0, 3, 1, f_ResultString.length(), f_ElementID);

	int f_MinChar = '0';

	std::string f_RecordedResult = "";

	for(int f_Jet = 0; f_Jet < f_Length; f_Jet++)
		{
		char f_c = f_ResultString.at(f_Jet);

		if((f_Jet == f_ClackLength) || (f_c == '.'))
			{
			f_RecordedResult.push_back('.');
			}
		else
			{
			if(((f_c - f_MinChar) >= 0) && ((f_c - f_MinChar) < 10))
				{
				f_ElementID = acPull_gen_ElementID(-1, -1, -1, -1);

				int f_BigC = ac_recordMeasurementINTV1(0, 9, 0, 3, 1, (f_c - f_MinChar), f_ElementID);

				char f_BigChar = f_BigC + f_MinChar;

				f_RecordedResult.push_back(f_BigChar);
				}
			else
				{
#if 1
				//throw;; //add debug message floating serialization integer char out of bounds
#endif
				}
			}
		}

	std::string f_String = "";

	if(f_Minus == true)
		{
		f_String.push_back('-');

		for(int f_Int = 0; f_Int < f_RecordedResult.length(); f_Int++)
			{
			f_String.push_back(f_RecordedResult.at(f_Int));
			}
		}
	else
		{
		f_String = f_RecordedResult;
		}

#if 0
	return = atof(f_String.c_str());
#else
	return f_String;
#endif
}

void classLMap::ac_LikelyBreak(int f_IDX, int f_ElementID)
{
	if(f_IDX == 3095)
		{
		__debugbreak();
		}

	if(f_ElementID == 774)
		{
		__debugbreak();
		}
}

bool classLMap::ac_recordMeasurementBLTV1(int f_Depth, int f_Cap, bool f_RecordResult, int f_ElementID)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_recordMeasurementBLTV1";
#endif

#if 0
	ac_LikelyBreak(m_LMap->m_vec_Measure.size(), f_ElementID);
#endif

	//reference element index
	m_LMap->m_vec_ElementID.push_back(f_ElementID);

	ag_StatusLive(f_ref_CurrentPath, "f_Measure");

	shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(f_Depth, f_Cap, f_RecordResult);

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);

	return f_RecordResult;
}

//element level specify schema
float classTarget_Ecom::ac_takeMeasurementFLTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth)  // scale resolution 1-3
{
	bool f_Minus = ac_takeMeasurementBLTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 4);

	//uncorrected floating measurement
	int f_ClackCap = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 1, 12, 0, 4);

	int f_Length = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 3, 18, 0, 5);

	int f_MinChar = '0';

	std::string f_RecordedResult = "";

	for(int f_Jet = 0; f_Jet < f_Length; f_Jet++)
		{
		if(f_Jet == f_ClackCap)
			{
			f_RecordedResult.push_back('.');
			}
		else
			{
			int f_BigC = ac_takeMeasurementINTV1(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0, 9, 0, 4);

			char f_BigChar = f_BigC + f_MinChar;

			f_RecordedResult.push_back(f_BigChar);
			}
		}

	std::string f_String;

	if(f_Minus == true)
		{
		f_String.push_back('-');

		for(int f_Jet = 0; f_Jet < f_RecordedResult.length(); f_Jet++)
			{
			f_String.push_back(f_RecordedResult.at(f_Jet));
			}
		}
	else
		{
		f_String = f_RecordedResult;
		}

	float f_ResultFLT = atof(f_String.c_str());

	return f_ResultFLT;
}

float classLMap::ac_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	bool f_Minus = ac_takeMeasurementBLTV1(f_Vertex, 0, 1, 0);

	//uncorrected floating measurement
	int f_ClackCap = ac_takeMeasurementINTV1(f_Vertex, 1, 12, 0, 4, 0, 0);

	int f_Length = ac_takeMeasurementINTV1(f_Vertex, 3, 18, 0, 5, 0, 0);

	int f_MinChar = '0';

	std::string f_RecordedResult = "";

	for(int f_Jet = 0; f_Jet < f_Length; f_Jet++)
		{
		if(f_Jet == f_ClackCap)
			{
			f_RecordedResult.push_back('.');
			}
		else
			{
			int f_BigC = ac_takeMeasurementINTV1(f_Vertex, 0, 9, 0, 4, 0, 0);

			char f_BigChar = f_BigC + f_MinChar;

			f_RecordedResult.push_back(f_BigChar);
			}
		}

	std::string f_FinalString = "";

	if(f_Minus == true)
		{
		f_FinalString.push_back('-');

		for(int f_Jet = 0; f_Jet < f_RecordedResult.length(); f_Jet++)
			{
			f_FinalString.push_back(f_RecordedResult.at(f_Jet));
			}
		}
	else
		{
		f_FinalString = f_RecordedResult;
		}

	float f_ResultFLT = atof(f_FinalString.c_str());

	return f_ResultFLT;
}

//element level specify schema
bool classTarget_Ecom::ac_takeMeasurementBLTV1(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_Cap)  // scale resolution 1-3
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::ac_takeMeasurementBLTV1";

	std::shared_ptr<classElement> f_Element = m_Collection->m_vec_Element[ag_Pull_gen_Element(f_ElementStartAD, f_ElementEndAD, f_ElementMax, f_Depth, 0)];

	//All distance test
	//obtain highest index of 8
	float f_HighestFloat = m_SchemaRef[m_SchemaTop]->m_Y;

	float f_HighestTheta = tan(f_HighestFloat);

	float f_HighestRangeVal = (f_HighestTheta * 8.0);

	if(f_HighestRangeVal < 0.0f)
		{
		f_HighestRangeVal = f_HighestRangeVal * -1.0f;
		}

	int f_HighestInt = (int)(f_HighestRangeVal);

	if(f_HighestInt > 7)
		{
		f_HighestInt = 7;
		}

	if(f_HighestInt < 0)
		{
		f_HighestInt = 0;
		}

	m_SchemaRef[m_SchemaTop]->m_X = (m_SchemaRef[m_SchemaTop]->m_X * f_Element->vec_Vertex[f_HighestInt]->m_X) * SCP_LEN_AMP;
	m_SchemaRef[m_SchemaTop]->m_Y = (m_SchemaRef[m_SchemaTop]->m_Y * f_Element->vec_Vertex[f_HighestInt]->m_Y) * SCP_LEN_AMP;
	m_SchemaRef[m_SchemaTop]->m_Z = (m_SchemaRef[m_SchemaTop]->m_Z * f_Element->vec_Vertex[f_HighestInt]->m_Z) * SCP_LEN_AMP;

	m_SchemaRef[m_SchemaTop]->acLargeBoundaryRanging();

	float f_Float = m_SchemaRef[m_SchemaTop]->acDot();

	float f_Theta = sin(f_Float);

	if(f_Theta > 0.0f)
		{
		return true;
		}
	else
		{		
		return false;
		}
}

bool classLMap::ac_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_Depth, int f_Cap, int f_OCSCP_ThreadIndex)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_takeMeasurementBLTV1";
#endif

	//All distance test
	//obtain highest index of 8
	float f_HighestFloat = m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y;

	float f_HighestTheta = tan(f_HighestFloat);

	float f_HighestRangeVal = (f_HighestTheta * 8.0);

	if(f_HighestRangeVal < 0.0f)
		{
		f_HighestRangeVal = f_HighestRangeVal * -1.0f;
		}

	int f_HighestInt = (int)(f_HighestRangeVal);

	if(f_HighestInt > 7)
		{
		f_HighestInt = 7;
		}

	if(f_HighestInt < 0)
		{
		f_HighestInt = 0;
		}

	m_SchemaRef[f_OCSCP_ThreadIndex]->m_X = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_X * f_Vertex->vec_Vertex[f_HighestInt]->m_X) * SCP_LEN_AMP;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Y * f_Vertex->vec_Vertex[f_HighestInt]->m_Y) * SCP_LEN_AMP;
	m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z = (m_SchemaRef[f_OCSCP_ThreadIndex]->m_Z * f_Vertex->vec_Vertex[f_HighestInt]->m_Z) * SCP_LEN_AMP;

	m_SchemaRef[f_OCSCP_ThreadIndex]->acLargeBoundaryRanging();

	float f_Float = m_SchemaRef[f_OCSCP_ThreadIndex]->acDot();

	float f_Theta = sin(f_Float);

	if(f_Theta > 0.0f)
		{
		return true;
		}
	else
		{
		return false;
		}
}

std::string ag_NameStamp(std::string f_Measurement, int f_Type, int f_BitCount)
{
	std::string f_Result;
	f_Result.clear();

	g_FunctionStamp++;

	if(f_Type == COMPONENT_TYPE_VARINSTA)
		{
		std::string f_Char;
		f_Char.clear();
		f_Char = "Variable" + g_FunctionStamp + '-' + f_BitCount;
		f_Result += f_Char;
		}

	if(f_Type == COMPONENT_TYPE_FUNCTIONCALL)
		{
		std::string f_Char;
		f_Char.clear();
		f_Char = "FunctionCall" + g_FunctionStamp + '-' + f_BitCount;
		f_Result += f_Char;
		}

	return f_Result;
}

}