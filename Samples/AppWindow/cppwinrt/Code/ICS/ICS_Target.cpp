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

#include "Code/ICS/ICS_Target.h"
#include "Code/CLS/Target.h"
#include "Code/Cube/qcom.h"
#include "Code/Cube/predator.h"

#include <cctype>
#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace ecoin;

namespace ecoin
{

std::shared_ptr<ICS_CountControl> g_CountController;

float ag_ICS_Get_current_Target_Mark(int f_Type)
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

void ag_ICS_EcoinSecure_Break_Assert(int f_A, int f_B)
{
	if(f_A != f_B)
		{
		__debugbreak();
		}
}

template<class _Ty>
std::shared_ptr<_Ty> ag_ICS_reference_NameObject(std::string f_Name)
{
	return nullptr;
}

void classTarget::ac_ICS_Sync_fromHesh(std::shared_ptr<CubeHESH> f_Hesh)
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

bool classTarget::ac_ICS_Compare(std::shared_ptr<classTarget> f_Target, float f_QualityRank, float f_Grade, bool f_testVolumes)
{
	 /////////////////////
	// Prime Decision
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

	//CubeHESHGen(%i)QualityRank[%f]:Mark %f < Diff(%f) tVol=%i g_Boost(%f)\n", f_True, f_QualityRank, f_Target->m_Mark, f_Grade, f_testVolumes, g_CoolBoost

	return f_True;
}

float classTarget::ac_ICS_Match(std::shared_ptr<classTarget> f_Target)
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

void classTarget::ac_ICS_Gen_Humanoid(void)
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

void classTarget::ac_ICS_Gen_Vehicle_Ground(void)
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

void classTarget::ac_ICS_Load_from_TargetID(int f_TargetID)
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

		sprintf(elementquery, "SELECT id, volume FROM element WHERE targetid = %i", g_TargetID);

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
		sprintf(elindexquery, "SELECT elementid, resultid FROM elindex WHERE targetid = %i", g_TargetID);
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

void classTarget_Ecom::ac_ICS_Prepare_Lense(void)
{
	m_SchemaTop = 0;

	m_SchemaRef[0]->m_X = float(3.121113539F);
	m_SchemaRef[0]->m_Y = float(3.773584266F);
	m_SchemaRef[0]->m_Z = float(3.952468634F);
}

void classTarget_Ecom::ac_ICS_DecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

//###--- classLMap Additions ---###//

bool classLMap::ac_ICS_SaveLense(int f_OCSCP_ThreadIndex, int f_MeasureIndex, int f_DrawnIndex)
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

bool classLMap::ac_ICS_SaveLensesSoft(int f_OCSCP_ThreadIndex, int f_MeasureIndex, int f_DrawnIndex)
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

bool classLMap::ac_ICS_PrepareLense(int f_OCSCP_ThreadIndex, int f_MeasureIndex)
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

void classLMap::ac_ICS_PushLensePos(int f_OCSCP_ThreadIndex)
{
	m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X;
	m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y;
	m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z;
	m_PushMeasureIndex[f_OCSCP_ThreadIndex] = m_SchemaMeasureIndex[f_OCSCP_ThreadIndex];
}

void classLMap::ac_ICS_PopLensePos(int f_OCSCP_ThreadIndex)
{
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_X = m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_X;
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Y = m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Y;
	m_SaveSchemaRef[f_OCSCP_ThreadIndex]->m_Z = m_PushSchemaRef[f_OCSCP_ThreadIndex]->m_Z;
	m_SchemaMeasureIndex[f_OCSCP_ThreadIndex] = m_PushMeasureIndex[f_OCSCP_ThreadIndex];
}

void classLMap::ac_ICS_PrepareLense(int f_OCSCP_ThreadIndex)
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

bool classLMap::ac_ICS_PreCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex, int f_ElementMax)
{
	bool f_Success = true;

	int f_EndElementIndex = f_ElementMax;

	int f_MeasureIndex = 0;
	int f_EndMeasureIndex = g_CountLM * f_EndElementIndex;

	ac_ICS_PrepareLense(f_OCSCP_ThreadIndex);

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
					int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_OCSCP_ThreadIndex);

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
					bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);

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

int classLMap::ac_ICS_CalcLoadFinish(void)
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

bool classLMap::ac_ICS_CalcScanReady(int f_Result)
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

bool classLMap::ac_ICS_Patch_IntegerRanges(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex)
{
	std::string f_ref_CurrentPath = "classLMap::acPatch_IntegerRanges";

	int f_MeasureIndex = 0;

	if(ac_ICS_PrepareLense(f_OCSCP_ThreadIndex, f_MeasureIndex) == false)
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
			if(ac_ICS_SaveLensesSoft(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
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
				int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, 0, 3, 0, f_OCSCP_ThreadIndex);

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
				int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, 0, m_OwnerEndRangeNext, 0, f_OCSCP_ThreadIndex);

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
						int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_OCSCP_ThreadIndex);

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
							int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, 0, 10, 0, f_OCSCP_ThreadIndex);

							ag_StatusLive(f_ref_CurrentPath, "f_Measure");
							shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(0, 10, 0, 1, 1, f_MeasureInteger);

							f_Measure->m_isInsertID = true;

							m_LMap->ac_InsertNew_IDX(f_MeasureIndex, f_Measure);

							f_CorrectCount++;

							f_Last_is_Int = true;

							f_isLast_Insert = true;
							}
						else
							{
							bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);
						
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
							int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_OCSCP_ThreadIndex);

							f_LMeasure->m_MeasurementINTV1 = f_MeasureInteger;

							f_LMeasure->m_isInsertID = true;

							f_CorrectCount++;

							f_Last_is_Int = true;

							f_isLast_Insert = true;
							}
						else
							{
							bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);
						
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
						bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);
						
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
							bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);
						
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
							int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, 0, 9, 0, f_OCSCP_ThreadIndex);

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
						bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);

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
							bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);

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
							int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, 0, 9, 0, f_OCSCP_ThreadIndex);

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

void classLMap::ac_ICS_ClearAway(void)
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

void classLMap::ac_ICS_Clear(void)
{
	acClearAway();

	m_LMap->acClear();

	m_GlobalScope = false;
	m_Mark = 0.0f;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classLMap::ac_ICS_MakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_index_Insta, int f_index_Function, std::string f_LineString, int f_LineStartIndex, int f_TypeGiven, bool f_FullDefinition)
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
			ac_ICS_recordMeasurementBLTV1(true); //has system

			f_TypeAndNameResult += "Sys%%";
			}
		else
			{
			ac_ICS_recordMeasurementBLTV1(false); //has no system

			if(f_c == 'V')
				{
				ac_ICS_recordMeasurementBLTV1(true); //has var

				f_TypeAndNameResult += "Var%%";
				}
			else
				{
				ac_ICS_recordMeasurementBLTV1(false); //has var

				if(f_c == 'C')
					{
					ac_ICS_recordMeasurementBLTV1(true); //has classvar

					f_TypeAndNameResult += "ClassVar%%";

					isClassVar = true;
					}
				else
					{
					ac_ICS_recordMeasurementBLTV1(false); //has no system
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
				ac_ICS_recordMeasurementBLTV1(true);

				f_TypeAndNameResult += "float&&";
				}
			else
				{
				ac_ICS_recordMeasurementBLTV1(false);

				if(f_Spec_Three[1] == true)
					{
					ac_ICS_recordMeasurementBLTV1(true);

					f_TypeAndNameResult += "int&&";
					}
				else
					{
					ac_ICS_recordMeasurementBLTV1(false);

					ac_ICS_recordMeasurementBLTV1(true);

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
		f_TypeAndNameResult += ac_ICS_recordMeasurement(f_morfarray[f_LineStartIndex + 1][0]);

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

bool classTarget_Ecom::ac_ICS_Factorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt)
{
	int f_Finger = ac_ICS_takeMeasurementINTV1(1, f_ProbabilityExt, 0, 3);

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

bool classLMap::ac_ICS_Factorise(bool f_Answer, int f_AboveLine, int f_ProbabilityExt, int f_StartAD, int f_EndAD, int f_ElementMax, int f_Depth)
{
	/*int f_Finger = ac_ICS_takeMeasurementINTV1(1, f_ProbabilityExt, 3, 3);

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

bool classTarget_Ecom::ac_ICS_FactorStrengthVar(int f_Type)
{
	return ac_ICS_takeMeasurementBLTV1(0);
}

bool classTarget_Ecom::ac_ICS_FactorStrengthVarString(int f_Type)
{
	return ac_ICS_takeMeasurementBLTV1(0);
}

#if 1
bool classLMap::ac_ICS_RecordStrengthVar(int f_Type, std::string f_LineString, float f_RecordResult, int f_ElementID, bool f_isRandom)
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

bool classLMap::ac_ICS_RecordStrengthVar(int f_Type, std::string f_LineString, int f_RecordResult, int f_ElementID, bool f_isRandom)
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

bool classLMap::ac_ICS_RecordStrengthVarString(int f_Type, std::string f_LineString, std::string f_RecordResult, int f_ElementID)
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

bool classLMap::ac_ICS_RecordStrength(int f_Type, std::string f_LineString, int f_ElementID)
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

int classLMap::ac_ICS_RecordLine(std::string f_LineString)
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
#endif

bool classTarget_Ecom::ac_ICS_FactorStrength(int f_Type)
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
			if(acFactorise(true, 4, 5, ) == true)
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
		if(acFactorise(true, 5, 6, ) == true)
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
			
		if(acFactorise(true, 9, 10, ) == true)
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

	return ac_ICS_takeMeasurementBLTV1(2);
}

bool classTarget_Ecom::ac_ICS_FactorStrengthAff(int f_Type, std::shared_ptr<classFunction> f_Function)
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
			if(ac_ICS_Factorise(true, 4, 5) == true)
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
		if(ac_ICS_Factorise(true, 5, 6) == true)
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
			
		if(ac_ICS_Factorise(true, 9, 10) == true)
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

std::string classTarget_Ecom::ac_ICS_Gen_genline_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_RecLine = "";

	int f_LineType = ac_ICS_takeMeasurementINTV1(0, 2, 0, 3);

	if(f_LineType == 0)
		{
		f_RecLine += "Complete ";

		std::string f_LineCompleteName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineCompleteName + " ";

		std::string f_LineClassName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineClassName + " ";

		std::string f_LineName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineName + " ";

		std::string f_LineDefaultValue = ac_ICS_takeMeasurement_DefaultValue();

		f_RecLine += f_LineDefaultValue + " ";

		int f_LineSHRIDX = ac_ICS_takeMeasurementINTS();

		int f_LineELEIDX = ac_ICS_takeMeasurementINTS();

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_ICS_takeMeasurementBLTV1(-1) == true)
			{
			std::string f_LineComment = ac_ICS_takeMeasurement();

			f_RecLine += f_LineComment;
			}
		}
	else if(f_LineType == 1)
		{
		f_RecLine += "Insert ";

		std::string f_LineClassName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineClassName + " ";

		std::string f_LineName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineName + " ";

		std::string f_LineDefaultValue = ac_ICS_takeMeasurement_DefaultValue();

		f_RecLine += f_LineDefaultValue + " ";

		int f_LineSHRIDX = ac_ICS_takeMeasurementINTS();

		int f_LineELEIDX = ac_ICS_takeMeasurementINTS();

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_ICS_takeMeasurementBLTV1(-1) == true)
			{
			std::string f_LineComment = ac_ICS_takeMeasurement();

			f_RecLine += f_LineComment;
			}
		}
	else if(f_LineType == 2)
		{
		f_RecLine += "Delete ";

		std::string f_LineDeleteName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineDeleteName + " ";

		std::string f_LineClassName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineClassName + " ";

		std::string f_LineName = ac_ICS_takeMeasurement();

		f_RecLine += f_LineName + " ";

		std::string f_LineDefaultValue = ac_ICS_takeMeasurement_DefaultValue();

		f_RecLine += f_LineDefaultValue + " ";

		int f_LineSHRIDX = ac_ICS_takeMeasurementINTS();

		int f_LineELEIDX = ac_ICS_takeMeasurementINTS();

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_ICS_takeMeasurementBLTV1(-1) == true)
			{
			std::string f_LineComment = ac_ICS_takeMeasurement();

			f_RecLine += f_LineComment;
			}
		}

	return f_RecLine;
}

std::string classLMap::ac_ICS_Gen_genline_FromEcom(std::shared_ptr<Qcom> f_Save_Com, int f_StartAD, int f_EndAD, std::shared_ptr<classTarget_Ecom> f_Target)
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
		//save line type
		ac_ICS_recordMeasurementINTV1(0, 2, 0, 0);

		f_RecLine += "Complete ";

		//packet to complete name
		std::string f_Name = f_vec_Package[1];

		std::string f_LineCompleteName = ac_ICS_recordMeasurement(f_Name);

		f_RecLine += f_LineCompleteName + " ";

		//classname
		std::string f_LineClassName = ac_ICS_recordMeasurement(f_vec_Package[2]);

		f_RecLine += f_LineClassName + " ";

		//insert name
		std::string f_LineName = ac_ICS_recordMeasurement(f_vec_Package[3]);

		f_RecLine += f_LineName + " ";

		//default value notice no prepull element
		std::string f_LineDefaultValue = ac_ICS_recordMeasurement_DefaultValue(f_vec_Package[4]);

		f_RecLine += f_LineDefaultValue + " ";

		//ShareID
		int f_LineSHRIDX = ac_ICS_recordMeasurementINTS(::atoi(f_vec_Package[5].c_str()));

		//ElementID
		int f_LineELEIDX = ac_ICS_recordMeasurementINTS(::atoi(f_vec_Package[6].c_str()));

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_ICS_recordMeasurementBLTV1((f_vec_Package.size() >= 8) ? true : false) == true)
			{
			//comment
			std::string f_LineComment = ac_ICS_recordMeasurement(f_vec_Package[7]);

			f_RecLine += f_LineComment;
			}
		}
	else if(f_vec_Package[0].compare("Insert") == 0)
		{
		//save line type
		ac_ICS_recordMeasurementINTV1(0, 2, 0, 1);

		f_RecLine += "Insert ";

		//classname
		std::string f_LineClassName = ac_ICS_recordMeasurement(f_vec_Package[1]);

		f_RecLine += f_LineClassName + " ";

		//insert name
		std::string f_LineName = ac_ICS_recordMeasurement(f_vec_Package[2]);

		f_RecLine += f_LineName + " ";

		//default value notice no prepull element
		std::string f_LineDefaultValue = ac_ICS_recordMeasurement_DefaultValue(f_vec_Package[3]);

		f_RecLine += f_LineDefaultValue + " ";

		//ShareID
		int f_LineSHRIDX = ac_ICS_recordMeasurementINTS(::atoi(f_vec_Package[4].c_str()));

		//ElementID
		int f_LineELEIDX = ac_ICS_recordMeasurementINTS(::atoi(f_vec_Package[5].c_str()));

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_ICS_recordMeasurementBLTV1((f_vec_Package.size() >= 7) ? true : false) == true)
			{
			//comment
			std::string f_LineComment = ac_ICS_recordMeasurement(f_vec_Package[6]);

			f_RecLine += f_LineComment;
			}
		}
	else if(f_vec_Package[0].compare("Delete") == 0)
		{
		//save line type
		ac_ICS_recordMeasurementINTV1(0, 2, 0, 2);

		f_RecLine += "Delete ";

		//packet to delete name
		std::string f_Name = f_vec_Package[1];

		//delete this package name
		std::string f_LineCompleteName = ac_ICS_recordMeasurement(f_Name);

		f_RecLine += f_LineCompleteName + " ";

		//classname
		std::string f_LineClassName = ac_ICS_recordMeasurement(f_vec_Package[2]);

		f_RecLine += f_LineClassName + " ";

		//insert name
		std::string f_LineName = ac_ICS_recordMeasurement(f_vec_Package[3]);

		f_RecLine += f_LineName + " ";

		//default value notice no prepull element
		std::string f_LineDefaultValue = ac_ICS_recordMeasurement_DefaultValue(f_vec_Package[4]);

		f_RecLine += f_LineDefaultValue + " ";

		//ShareID
		int f_LineSHRIDX = ac_ICS_recordMeasurementINTS(::atoi(f_vec_Package[5].c_str()));

		//ElementID
		int f_LineELEIDX = ac_ICS_recordMeasurementINTS(::atoi(f_vec_Package[6].c_str()));

		char* f_Char = ag_ClearChar(255);

		sprintf(f_Char, "%i %i ", f_LineSHRIDX, f_LineELEIDX);

		f_RecLine += f_Char;

		delete f_Char;

		if(ac_ICS_recordMeasurementBLTV1((f_vec_Package.size() >= 8) ? true : false) == true)
			{
			//comment
			std::string f_LineComment = ac_ICS_recordMeasurement(f_vec_Package[7]);

			f_RecLine += f_LineComment;
			}
		}

	return f_RecLine;
}

int classTarget_Ecom::ac_ICS_takeMeasurementINTS(void)
{
	std::string f_Result = "";

	if(ac_ICS_takeMeasurementBLTV1(1) == true)
		{
		f_Result.push_back('-');
		}

	bool f_Scan = true;
	while(f_Scan == true)
		{
		int f_CharInt = ac_ICS_takeMeasurementINTV1(0, 9, 0, 0);

		f_Result.push_back((char)(f_CharInt + '0'));

		//continue check
		f_Scan = ac_ICS_takeMeasurementBLTV1(4);
		}

	return ::atoi(f_Result.c_str());
}

int classLMap::ac_ICS_takeMeasurementINTS(shared_ptr<classElement> f_Vertex)
{
	std::string f_Result = "";

	if(ac_ICS_takeMeasurementBLTV1(f_Vertex, 0) == true)
		{
		f_Result.push_back('-');
		}

	bool f_Scan = true;

	while(f_Scan == true)
		{
		int f_CharInt = ac_ICS_takeMeasurementINTV1(f_Vertex, 0, 9, 0, 0);

		f_Result.push_back((char)(f_CharInt + '0'));

		//continue check
		f_Scan = ac_ICS_takeMeasurementBLTV1(f_Vertex, 0);
		}

	return ::atoi(f_Result.c_str());
}

void classLMap::ac_ICS_lastMeasurement(int f_IndexID)
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

int classLMap::ac_ICS_recordMeasurementINTS(int f_RecordResult, bool f_isIndexID)
{
	std::string f_ref_CurrentPath = "classLMap::ac_ICS_recordMeasurementINTS";

	//on position ignore all INTS changes in lensemap
	int f_IndexID = 1;

	char* f_Char = ag_ClearChar(255);

	sprintf(f_Char, "%i", f_RecordResult);

	std::string f_StringResult = f_Char;
	std::string f_StringResultChars = "";

	bool f_Minus = ac_ICS_recordMeasurementBLTV1((f_StringResult.at(0) == '-') ? true : false);

	ac_ICS_lastMeasurement(f_IndexID);

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
			int f_RecResultInt = ac_ICS_recordMeasurementINTV1(0, 9, 0, f_CharInt);

			ac_ICS_lastMeasurement(f_IndexID);

			f_StringResultChars.push_back((char)(f_RecResultInt + '0'));
			}

		f_On = ac_ICS_recordMeasurementBLTV1((f_Jet == (f_StringResult.length() - 1)) ? false : true);

		ac_ICS_lastMeasurement(f_IndexID);

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

std::shared_ptr<Qcom_genScript> classTarget_Ecom::ac_ICS_Gen_gen_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_gen_FromHesh";

	ag_StatusLive(f_ref_CurrentPath, "f_Measure");
	std::shared_ptr<Qcom_genScript> f_gen = std::make_shared_reflect<Qcom_genScript>();

	std::string f_VarNameA = ac_ICS_takeMeasurement();

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
	bool f_ScanLines = true;
	while(f_ScanLines == true)
		{
		f_ScanLines = ac_ICS_takeMeasurementBLTV1(1);

		if(f_ScanLines == true)
			{
			std::string f_String = ac_ICS_Gen_genline_FromHesh(f_Hesh, f_Target);

			f_gen->m_vec_InitLine.push_back(f_String);
			f_gen->m_vec_InitLineOrdered.push_back(f_String);
			}
		}

	return f_gen;
}

std::shared_ptr<Qcom_genScript> classLMap::ac_ICS_Gen_gen_FromEcom(std::shared_ptr<Qcom> f_Save_Com, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_gen_FromEcom";

	ag_StatusLive(f_ref_CurrentPath, "f_gen");
	std::shared_ptr<Qcom_genScript> f_gen = std::make_shared_reflect<Qcom_genScript>();

	std::string f_VarNameA = ac_ICS_recordMeasurement(f_Save_Com->m_genScript->m_name);

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
		f_ScanLines = ac_ICS_recordMeasurementBLTV1((f_XY < f_Save_Com->m_genScript->m_vec_InitLineOrdered.size()) ? true : false);

		if(f_ScanLines == true)
			{
			std::string f_String = ac_ICS_Gen_genline_FromEcom(f_Save_Com, f_XY, f_Save_Com->m_genScript->m_vec_InitLineOrdered.size(), f_Target);

			f_gen->m_vec_InitLine.push_back(f_String);
			f_gen->m_vec_InitLineOrdered.push_back(f_String);

			f_XY++;
			}
		}

	return f_gen;
}

ICS_LibraryID::ICS_LibraryID(std::shared_ptr<Cube::CubeHESH> f_Hesh)
{
	m_TimeCheckPoint = 0;
	m_HighPrecisionTime = 0;

	m_Resultant = std::ag_Make_Smart_Pointer<ICS_Resultant>();

	int f_CurrentBicycleInt = 0;

	std::shared_ptr<Cube::CubeBicycle> f_Bicycle = f_Hesh->vec_Bicycle[f_CurrentBicycleInt];

	f_CurrentBicycleInt++;

	int f_CurrentVertexInt = 0;

	std::shared_ptr<BiVector> f_Position = f_Bicycle->vec_Vertex[f_CurrentVertexInt];

	f_CurrentVertexInt++;

	m_TimeCheckPoint = f_Position->acInteger(); //[LOAD] m_TimeCheckPoint

	f_Position = f_Bicycle->vec_Vertex[f_CurrentVertexInt];

	f_Position->m_Mode = 0;

	bool f_Scan = true;
	while(f_Scan == true)
		{
		int f_HighPrecisionTime = f_Position->acInteger();

		f_CurrentVertexInt++;

		if(f_CurrentVertexInt >= 8)
			{
			if(f_CurrentBicycleInt >= f_Hesh->vec_Bicycle.size())
				{
#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //Add Debug Message
#endif

				f_Scan = false;

				f_CurrentBicycleInt--;
				}
			else
				{
				f_Bicycle = f_Hesh->vec_Bicycle[f_CurrentBicycleInt];
				}

			f_CurrentBicycleInt++;
			f_CurrentVertexInt = 0;
			}

		//Draw New Vector
		f_Position = f_Bicycle->vec_Vertex[f_CurrentVertexInt];

		f_Position->m_Mode = 0;

		if(f_HighPrecisionTime != ICS_INTEGER_STACK)
			{
			f_Scan = false;
			}

		m_HighPrecisionTime += f_HighPrecisionTime; //[LOAD] m_HighPrecisionTime
		}

	  ///////////////
	 // RESULTANT //
	///////////////

	std::string f_StringResultant = "";

	f_Scan = true;
	while(f_Scan == true)
		{
		char f_Character = f_Position->ac_CharValue();

		if(f_Character != 'E')
			{
			f_StringResultant.push_back(f_Character);
			}
		else
			{
			f_Scan = false;
			}

		if((f_Character == 'E') || (f_Position->m_Mode >= 2))
			{
			f_CurrentVertexInt++;

			if(f_CurrentVertexInt >= 8)
				{
				f_CurrentBicycleInt++;

				if(f_CurrentBicycleInt >= f_Hesh->vec_Bicycle.size())
					{
#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //Add Debug Message
#endif

					f_Scan = false;

					f_CurrentBicycleInt--;
					}
				else
					{
					f_Bicycle = f_Hesh->vec_Bicycle[f_CurrentBicycleInt];
					}

				f_CurrentBicycleInt++;
				f_CurrentVertexInt = 0;
				}

			//Draw New Vector
			f_Position = f_Bicycle->vec_Vertex[f_CurrentVertexInt];

			f_Position->m_Mode = 0;
			}
		}

	m_Resultant->m_FLR = atof(f_StringResultant.c_str()); //[LOAD] m_Resultant->m_FLR

	std::string f_StringXLength = "";

	f_Scan = true;
	while(f_Scan == true)
		{
		char f_Character = f_Position->ac_CharValue();

		if(f_Character != 'E')
			{
			f_StringXLength.push_back(f_Character);
			}
		else
			{
			f_Scan = false;
			}

		if((f_Character == 'E') || (f_Position->m_Mode >= 2))
			{
			f_CurrentVertexInt++;

			if(f_CurrentVertexInt >= 8)
				{
				f_CurrentBicycleInt++;

				if(f_CurrentBicycleInt >= f_Hesh->vec_Bicycle.size())
					{
#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //Add Debug Message
#endif

					f_Scan = false;

					f_CurrentBicycleInt--;
					}
				else
					{
					f_Bicycle = f_Hesh->vec_Bicycle[f_CurrentBicycleInt];
					}

				f_CurrentBicycleInt++;
				f_CurrentVertexInt = 0;
				}

			//Draw New Vector
			f_Position = f_Bicycle->vec_Vertex[f_CurrentVertexInt];

			f_Position->m_Mode = 0;
			}
		}

	m_Resultant->m_FinalXLength = atof(f_StringXLength.c_str()); //[LOAD] m_Resultant->m_FinalXLength
}

std::shared_ptr<Qcom> classTarget_Ecom::ac_ICS_Gen_com_FromHesh(std::Smart_Ptr<ICS_Mainstream> f_Mainstream, std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_FromHesh";

	// Instantiate Library ID
	m_LibraryID = std::ag_Make_Smart_Pointer<ICS_LibraryID>(f_Hesh);

	m_LibraryID->m_MainstreamID = f_Mainstream->m_MainstreamID;

	f_Mainstream->acStartStream(m_LibraryID);

	// Plus Mainstream
	m_LibraryID->m_Resultant->acConnectMainstream(f_Mainstream);

	// Position m_Pos File Position
	f_Mainstream->acPositionLocation(m_LibraryID);

	if(ac_ICS_takeMeasurementBLTV1() == true)
		{
		ag_StatusLive(f_ref_CurrentPath, "f_com");
		std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

		f_com->m_ID = -1551;

		if(ac_ICS_takeMeasurementBLTV1() == true)
			{
			f_com->m_ID = ac_ICS_takeMeasurementINTS();
			}

		std::string f_VarNameA = ac_ICS_takeMeasurement();

		f_com->m_birthcomid = ac_ICS_takeMeasurementINTS();

		f_com->m_BossLVLMin = ac_ICS_takeMeasurementFLTV1();

		f_com->m_position->m_X = ac_ICS_takeMeasurementFLTV1();
		f_com->m_position->m_Y = ac_ICS_takeMeasurementFLTV1();

		f_com->m_Cost = ac_ICS_takeMeasurementFLTV1();

		f_com->m_name = f_VarNameA;

		f_com->m_owner = ac_ICS_takeMeasureKey();

		if(ac_ICS_takeMeasurementBLTV1() == true)
			{
			f_com->m_description = ac_ICS_takeMeasurement();
			}

		f_com->m_parentcomid = ac_ICS_takeMeasurementINTS();

		f_com->m_VoteScore = ac_ICS_takeMeasurementINTS();

		f_com->m_rebuild = true;
		f_com->m_Save = false;

		 ///////////////////////////
		// Generation Script Gen //
		if(ac_ICS_takeMeasurementBLTV1() == true)
			{
			f_com->m_genScript = ac_ICS_Gen_gen_FromHesh(f_Hesh, f_com, f_Target);

			g_QcomManager->m_vec_GenScript.push_back(f_com->m_genScript);
			}

		// Insert Change Element restriction or other share entirely at this point
		if(ac_ICS_takeMeasurementBLTV1() == true)
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromHesh(f_Hesh, f_com, f_Target);

			f_com->m_Frame_ESLFunction = f_Function;

			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}

		bool f_ScanFunc = true;
		while(f_ScanFunc == true)
			{
			f_ScanFunc = ac_ICS_takeMeasurementBLTV1();

			if(f_ScanFunc == true)
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromHesh(f_Hesh, f_com, f_Target);

				f_com->m_vec_ESLFunction.push_back(f_Function);

				g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
				}
			}
		
#ifdef ESL_CIRCUIT_APPENDIX
		bool f_ScanInput = true;
		while(f_ScanInput == true)
			{
			f_ScanInput = ac_ICS_takeMeasurementBLTV1();

			if(f_ScanInput == true)
				{
				std::shared_ptr<QcomInput> f_COM_Input = ac_ICS_Gen_com_input_FromHesh(f_Hesh, f_com, f_Target);

				if(ac_ICS_takeMeasurementBLTV1() == true)
					{
					if(ac_ICS_takeMeasurementBLTV1() == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromHesh(f_Hesh, f_com, f_Target);

						f_Function->m_ComID = f_com->m_ID;
						f_Function->m_owner = f_com->m_owner;

						f_COM_Input->m_InputFunction = f_Function;
						f_COM_Input->m_InputfunctionID = f_Function->m_ID;

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
			f_ScanOutput = ac_ICS_takeMeasurementBLTV1();

			if(f_ScanOutput == true)
				{
				std::shared_ptr<QcomOutput> f_COM_Output = ac_ICS_Gen_com_output_FromHesh(f_Hesh, f_com, f_Target);

				if(ac_ICS_takeMeasurementBLTV1() == true)
					{
					if(ac_ICS_takeMeasurementBLTV1() == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromHesh(f_Hesh, f_com, f_Target);

						f_Function->m_ComID = f_com->m_ID;
						f_Function->m_owner = f_com->m_owner;

						f_COM_Output->m_OutputFunction = f_Function;
						f_COM_Output->m_OutputfunctionID = f_Function->m_ID;

						g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
						}
					}

				f_com->m_vec_Output.push_back(f_COM_Output);
				g_QcomManager->m_vec_Output.push_back(f_COM_Output);
				}
			}
#else
		ac_ICS_takeMeasurementBLTV1(-1);
		ac_ICS_takeMeasurementBLTV1(-1);
#endif

		//f_com->acWire(f_Hesh, 0, f_Hesh->vec_Bicycle.size());

		//Insert Change Element restriction or other share entirely at this point
		bool f_ScanCom = true;
		while(f_ScanCom == true)
			{
			f_ScanCom = ac_ICS_takeMeasurementBLTV1();

			if(f_ScanCom == true)
				{
				std::shared_ptr<Qcom> f_com_B = ac_ICS_Gen_com_FromHesh(f_Mainstream, f_Hesh, f_Target);

				f_com->m_vec_Qcom.push_back(f_com_B);

				g_QcomManager->m_vec_Qcom.push_back(f_com_B);
				}
			}

		return f_com;
		}
	else  //else comid structure build
		{ //obtain qcom db index
		int f_ComID = ac_ICS_takeMeasurementINTS();

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

std::shared_ptr<QcomInput> classTarget_Ecom::ac_ICS_Gen_com_input_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_input_FromHesh";

	ag_StatusLive(f_ref_CurrentPath, "f_comInput");
	std::shared_ptr<QcomInput> f_comInput = std::make_shared_reflect<QcomInput>();

	std::string f_VarNameA = ac_ICS_takeMeasurement();

	f_comInput->m_position->m_X = ac_ICS_takeMeasurementFLTV1();
	f_comInput->m_position->m_Y = ac_ICS_takeMeasurementFLTV1();

	f_comInput->m_ID = ac_ICS_takeMeasurementINTS();

	f_comInput->m_name = f_VarNameA;
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

std::shared_ptr<QcomOutput> classTarget_Ecom::ac_ICS_Gen_com_output_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acGen_com_output_FromHesh";

	ag_StatusLive(f_ref_CurrentPath, "f_comOutput");
	std::shared_ptr<QcomOutput> f_comOutput = std::make_shared_reflect<QcomOutput>();

	std::string f_VarNameA = ac_ICS_takeMeasurement();

	f_comOutput->m_position->m_X = ac_ICS_takeMeasurementFLTV1();
	f_comOutput->m_position->m_Y = ac_ICS_takeMeasurementFLTV1();

	f_comOutput->m_ID = ac_ICS_takeMeasurementINTS();

	f_comOutput->m_name = f_VarNameA;
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

std::string classLMap::ac_ICS_LenseMapHash(void)
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

std::shared_ptr<Qcom> classLMap::ac_ICS_Gen_com_FromEcom(std::shared_ptr<Qcom> f_Save_Com, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_FromEcom";

	int f_ComID = -1551;

	if(ac_ICS_recordMeasurementBLTV1(true) == true)
		{
		if(f_Save_Com->m_ID > 0)
			{
			ac_ICS_recordMeasurementBLTV1(true);

			// obtain qcom db index
			f_ComID = ac_ICS_recordMeasurementINTS(f_Save_Com->m_ID, true);
			}
		else
			{
			ac_ICS_recordMeasurementBLTV1(false);
			}

		ag_StatusLive(f_ref_CurrentPath, "f_com", true);
		std::shared_ptr<Qcom> f_com = std::make_shared_reflect<Qcom>();

		f_com->m_ID = f_ComID;

		std::string f_VarNameA = ac_ICS_recordMeasurement(f_Save_Com->m_name);

		f_com->m_birthcomid = ac_ICS_recordMeasurementINTS(f_Save_Com->m_birthcomid, true);

		std::string f_Boss_String = ag_StrUsingFloat(g_BossLVLMin);

		std::string f_BossStr = ac_ICS_recordMeasurementFLTV1(f_Boss_String);
		f_com->m_BossLVLMin = atof(f_BossStr.c_str());

		std::string f_X_String = ag_StrUsingFloat(f_Save_Com->m_position->m_X);

		std::string f_X_Str = ac_ICS_recordMeasurementFLTV1(f_X_String);
		f_com->m_position->m_X = atof(f_X_Str.c_str());

		std::string f_Y_String = ag_StrUsingFloat(f_Save_Com->m_position->m_Y);

		std::string f_Y_Str = ac_ICS_recordMeasurementFLTV1(f_Y_String);
		f_com->m_position->m_Y = atof(f_Y_Str.c_str());

		std::string f_CostString = ag_StrUsingFloat(f_Save_Com->m_Cost);

		std::string f_Cost_Str = ac_ICS_recordMeasurementFLTV1(f_CostString);
		f_com->m_Cost = atof(f_Cost_Str.c_str());

		f_com->m_name = f_VarNameA;

		// notice: no element pull prior to measure key
		f_com->m_owner = ac_ICS_recordMeasureKey(f_Save_Com->m_owner);

		if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_description.length() > 0) ? true : false) == true)
			{
			f_com->m_description = ac_ICS_recordMeasurement(f_Save_Com->m_description);
			}

		f_com->m_parentcomid = ac_ICS_recordMeasurementINTS(f_Save_Com->m_parentcomid);

		f_com->m_rebuild = true;
		f_com->m_Save = true;

		f_com->m_VoteScore = ac_ICS_recordMeasurementINTS(f_Save_Com->m_VoteScore);

		 ///////////////////////////
		// Generation Script Gen //
		if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_genScript != nullptr) ? true : false) == true)
			{
			f_com->m_genScript = ac_ICS_Gen_gen_FromEcom(f_Save_Com, f_Target);

			g_QcomManager->m_vec_GenScript.push_back(f_com->m_genScript);
			}

		if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_Frame_ESLFunction != nullptr) ? true : false) == true)
			{
			std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromEcom(f_Save_Com->m_Frame_ESLFunction, f_Save_Com, f_Target);

			f_com->m_Frame_ESLFunction = f_Function;

			g_QcomManager->m_vec_ESLFunction.push_back(f_Function);
			}

		//Insert Change Element restriction or other share entirely at this point
		int f_XY = 0;
		bool f_ScanFunc = true;
		while(f_ScanFunc == true)
			{
			f_ScanFunc = ac_ICS_recordMeasurementBLTV1((f_XY < f_Save_Com->m_vec_ESLFunction.size()) ? true : false);

			if(f_ScanFunc == true)
				{
				std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromEcom(f_Save_Com->m_vec_ESLFunction[f_XY], f_Save_Com, f_Target);
			
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
			f_ScanInput = ac_ICS_recordMeasurementBLTV1((f_Helly < f_Save_Com->m_vec_Input.size()) ? true : false);

			if(f_ScanInput == true)
				{ //levels of element selection range
				std::shared_ptr<QcomInput> f_COM_Input = ac_ICS_Gen_com_input_FromEcom(f_Save_Com->m_vec_Input[f_Helly], f_Save_Com, f_Target, f_WireContractOverride);

				if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction != nullptr) ? true : false) == true)
					{
					if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction->m_vec_InitLineOrdered.size() > 0) ? true : false) == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromEcom(f_Save_Com->m_vec_Input[f_Helly]->m_InputFunction, f_Save_Com, f_Target);

						f_Function->m_ComID = f_Save_Com->m_ID;
						f_Function->m_owner = f_Save_Com->m_owner;

						f_COM_Input->m_InputfunctionID = f_Function->m_ID;
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
			f_ScanOutput = ac_ICS_recordMeasurementBLTV1((f_Helly < f_Save_Com->m_vec_Output.size()) ? true : false);

			if(f_ScanOutput == true)
				{ //levels of element selection range
				std::shared_ptr<QcomOutput> f_COM_Output = ac_ICS_Gen_com_output_FromEcom(f_Save_Com->m_vec_Output[f_Helly], f_Save_Com, f_Target, f_WireContractOverride);

				if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction != nullptr) ? true : false) == true)
					{
					if(ac_ICS_recordMeasurementBLTV1((f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction->m_vec_InitLineOrdered.size() > 0) ? true : false) == true)
						{
						std::shared_ptr<Qcom_eslfunction> f_Function = ac_ICS_Gen_com_function_FromEcom(f_Save_Com->m_vec_Output[f_Helly]->m_OutputFunction, f_Save_Com, f_Target);

						f_Function->m_ComID = f_Save_Com->m_ID;
						f_Function->m_owner = f_Save_Com->m_owner;

						f_COM_Output->m_OutputfunctionID = f_Function->m_ID;
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
		f_ElementIndex = ac_ICS_Pull_gen_ElementID();

		ac_ICS_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);

		f_ElementIndex = ac_ICS_Pull_gen_ElementID();

		ac_ICS_recordMeasurementBLTV1(1, 1, false, f_ElementIndex);
#endif

#if 0
		f_com->acWire(f_Hesh, 0, f_ElementMax);
#endif

		//Insert Change Element restriction or other share entirely at this point
		f_XY = 0;
		bool f_ScanCom = true;
		while(f_ScanCom == true)
			{
			f_ScanCom = ac_ICS_recordMeasurementBLTV1((f_XY < f_Save_Com->m_vec_Qcom.size()) ? true : false);

			if(f_ScanCom == true)
				{
				std::shared_ptr<Qcom> f_Add_Com = ac_ICS_Gen_com_FromEcom(f_Save_Com->m_vec_Qcom[f_XY], f_Target);

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
		//obtain qcom db index
		f_ComID = ac_ICS_recordMeasurementINTS(f_Save_Com->m_ID);

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

std::shared_ptr<QcomInput> classLMap::ac_ICS_Gen_com_input_FromEcom(std::shared_ptr<QcomInput> f_Save_Input, std::shared_ptr<Qcom> f_Save_Com, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_input_FromEcom";

	ag_StatusLive(f_ref_CurrentPath, "f_comInput");
	std::shared_ptr<QcomInput> f_comInput = std::make_shared_reflect<QcomInput>();
	
	std::string f_VarNameA = ac_ICS_recordMeasurement(f_Save_Input->m_name);

	std::string f_Pos_X_String = ag_StrUsingFloat(f_Save_Input->m_position->m_X);
	std::string f_PosXStr = ac_ICS_recordMeasurementFLTV1(f_Pos_X_String);
	f_comInput->m_position->m_X = atof(f_PosXStr.c_str());

	std::string f_Pos_Y_String = ag_StrUsingFloat(f_Save_Input->m_position->m_Y);
	std::string f_PosYStr = ac_ICS_recordMeasurementFLTV1(f_Pos_Y_String);
	f_comInput->m_position->m_Y = atof(f_PosYStr.c_str());

	f_comInput->m_ID = ac_ICS_recordMeasurementINTS(f_Save_Input->m_ID);

	f_comInput->m_name = f_VarNameA;
	f_comInput->m_birthcomid = f_Save_Com->m_birthcomid;
	f_comInput->m_ComID = f_Save_Com->m_ID;
	f_comInput->m_QamID = f_Save_Com->m_QamID;
	f_comInput->m_QamLevel = f_Save_Com->m_QamLevel;
	f_comInput->m_owner = f_Save_Com->m_owner;
	f_comInput->m_description = f_Save_Input->m_description;
	f_comInput->m_InputfunctionID = f_Save_Input->m_InputfunctionID;
	f_comInput->m_rebuild = true;
	f_comInput->m_Save = true;

	return f_comInput;
}

std::shared_ptr<QcomOutput> classLMap::ac_ICS_Gen_com_output_FromEcom(std::shared_ptr<QcomOutput> f_Save_Output, std::shared_ptr<Qcom> f_Save_Com, std::shared_ptr<classTarget_Ecom> f_Target, int f_WireContractOverride)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_output_FromEcom";

	ag_StatusLive(f_ref_CurrentPath, "f_comOutput");
	std::shared_ptr<QcomOutput> f_comOutput = std::make_shared_reflect<QcomOutput>();

	std::string f_VarNameA = ac_ICS_recordMeasurement(f_Save_Output->m_name);

	std::string f_Pos_X_String = ag_StrUsingFloat(f_Save_Output->m_position->m_X);
	std::string f_PosXStr = ac_ICS_recordMeasurementFLTV1(f_Pos_X_String);
	f_Save_Output->m_position->m_X = atof(f_PosXStr.c_str());

	std::string f_Pos_Y_String = ag_StrUsingFloat(f_Save_Output->m_position->m_Y);
	std::string f_PosYStr = ac_ICS_recordMeasurementFLTV1(f_Pos_Y_String);
	f_Save_Output->m_position->m_Y = atof(f_PosYStr.c_str());

	f_comOutput->m_ID = ac_ICS_recordMeasurementINTS(f_Save_Output->m_ID);

	f_comOutput->m_name = f_VarNameA;
	f_comOutput->m_birthcomid = f_Save_Com->m_birthcomid;
	f_comOutput->m_ComID = f_Save_Com->m_ID;
	f_comOutput->m_QamID = f_Save_Com->m_QamID;
	f_comOutput->m_QamLevel = f_Save_Com->m_QamLevel;
	f_comOutput->m_owner = f_Save_Com->m_owner;
	f_comOutput->m_description = f_Save_Output->m_description;
	f_comOutput->m_OutputfunctionID = f_Save_Output->m_OutputfunctionID;
	f_comOutput->m_rebuild = true;
	f_comOutput->m_Save = true;

	return f_comOutput;
}

//fixme: add three ways lazy bear approach to changing variable insta names
std::string classTarget_Ecom::ac_ICS_MakeUnison(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_index_Insta, int f_index_Function)
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
std::string classTarget_Ecom::ac_ICS_MakeUnisonType(shared_ptr<classTarget_Ecom> f_Target, std::string f_Name, int f_BitCount, int f_INSTA, int f_index_Insta, int f_index_Function, int f_TypeGiven, bool f_FullDefinition)
{
	std::string f_ref_CurrentPath = "classTarget_Ecom::acMakeUnisonType";

	std::string f_TypeAndNameResult;
	f_TypeAndNameResult.clear();

	bool isClassVar = false;

	if(f_FullDefinition == true)
		{
		if(ac_ICS_takeMeasurementBLTV1(1))
			{	//Sys
			f_TypeAndNameResult += "Sys%%";
			}
		else
			{
			if(ac_ICS_takeMeasurementBLTV1(1))
				{	//Var
				f_TypeAndNameResult += "Var%%";
				}
			else
				{
				if(ac_ICS_takeMeasurementBLTV1(1))
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
			if(ac_ICS_takeMeasurementBLTV1(1) == true)
				{
				f_TypeAndNameResult += "float&&";
				}
			else if(ac_ICS_takeMeasurementBLTV1(1) == true)
				{
				f_TypeAndNameResult += "int&&";
				}
			else if(ac_ICS_takeMeasurementBLTV1(1) == true)
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
		std::string f_ClassVarType = ac_ICS_takeMeasurement();

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

std::shared_ptr<Qcom_eslfunction> classTarget_Ecom::ac_ICS_Gen_com_function_FromHesh(std::shared_ptr<CubeHESH> f_Hesh, std::shared_ptr<Qcom> f_Com, std::shared_ptr<classTarget_Ecom> f_Target)
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

	int f_ConsensusID = ac_ICS_takeMeasurementINTS();

	int f_FunctionType = ac_ICS_takeMeasurementINTV1(0, FuncExec_Total, 0, 3);

	int f_LineCount = 0;

	ag_StatusLive(f_ref_CurrentPath, "f_Function");
	std::shared_ptr<classFunction> f_Function = std::make_shared_reflect<classFunction>();

	f_Function->m_Type = f_FunctionType;

	if(ac_ICS_takeMeasurementBLTV1(2) == true)
		{
		return f_Function->acConvert(f_Com);
		}

	if(f_ConsensusID != ECOIN_CONSENSUS_ID)
		{
		return f_Function->acConvert(f_Com);
		}

	int f_FunctionID = ac_ICS_takeMeasurementINTS();

	if(ac_ICS_takeMeasurementBLTV1(2) == true)
		{
		std::string f_ClassNameA = ac_ICS_takeMeasurement();
		std::string f_ClassNameB = ac_ICS_takeMeasurement();

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

	if(ac_ICS_takeMeasurementBLTV1(2) == true)
		{
		f_Function->m_vec_String += ac_ICS_Gen_Var_fromHesh();
		}

	if(ac_ICS_takeMeasurementBLTV1(2) == true)
		{
		std::string f_FunctionNameA = ac_ICS_takeMeasurement();
		std::string f_FunctionNameB = ac_ICS_takeMeasurement();

		std::string f_StringEL = "FuncDef%%" + f_FunctionNameA + "&*" + f_FunctionNameB + "%%";

		f_Function->m_Name = f_FunctionNameB;

		ag_StatusLive(f_ref_CurrentPath, "f_InstaVs");
		std::shared_ptr<classInsta> f_InstaVs = std::make_shared_reflect<classInsta>(f_StringEL, ESL_INSTA_TYPE_FUNC_DEF);

		f_Function->m_vec_Insta.push_back(f_InstaVs);
		f_Function->m_idx_vec_Insta++;

		bool f_argScan = true;
		while(f_argScan == true)
			{
			f_argScan = ac_ICS_takeMeasurementBLTV1(-1);

			if(f_argScan == true)
				{
				std::string f_ArgParam = ac_ICS_Gen_Var_fromHesh();

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
				
		int f_InstaType = ac_ICS_takeMeasurementINTV1(0, ESL_INSTA_TYPE_COUNT, 0, 3);

		if(f_InstaType == ESL_INSTA_TYPE_VAR_DEF) //un
			{
			std::string f_StringB = ac_ICS_Gen_Var_fromHesh();

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
			std::string f_StringB = ac_ICS_Gen_Var_fromHesh();

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
			std::string f_StringVarA = ac_ICS_Gen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaA");
			std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringVarA, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaA);
			f_Function->m_idx_vec_Insta++;

			int f_FingerCount = ac_ICS_takeMeasurementINTV1(0, 5, 0, 3);

			std::string f_Name = ac_ICS_takeMeasurement();

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

			std::string f_StringVarB = ac_ICS_Gen_Var_fromHesh();

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
			std::string f_StringVarA = ac_ICS_Gen_Var_fromHesh();

			std::string f_StringAB = "";

			ag_StatusLive(f_ref_CurrentPath, "f_StringVarA");
			std::shared_ptr<classInsta> f_InstaA = std::make_shared_reflect<classInsta>(f_StringVarA, ESL_INSTA_TYPE_VAR_SYS_DEF_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaA);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVarA;

			int f_FingerCount = ac_ICS_takeMeasurementINTV1(0, 9, 0, 3);

			//operator take
			std::string f_StringABCF = "Opr%%";

			std::string f_Name = ac_ICS_takeMeasurement();

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

			if(ac_ICS_takeMeasurementBLTV1(1) == true)
				{
				//Place RHS
				std::string f_StringVarB = ac_ICS_Gen_Var_fromHesh();

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
			std::string f_forName = ac_ICS_takeMeasurement();

			std::string f_StringF = "For%% " + f_forName + "%%";

			std::string f_StringAB = "";

			//Place Var 1
			std::string f_StringVar1 = ac_ICS_Gen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB1");
			std::shared_ptr<classInsta> f_InstaB1 = std::make_shared_reflect<classInsta>(f_StringVar1, ESL_INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB1);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVar1;

			//Place Var 2
			std::string f_StringVar2 = ac_ICS_Gen_Var_fromHesh();

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB");
			std::shared_ptr<classInsta> f_InstaB2 = std::make_shared_reflect<classInsta>(f_StringVar2, ESL_INSTA_TYPE_VAR_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB2);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringVar2;

			//Place Var 3
			std::string f_StringVar3 = ac_ICS_Gen_Var_fromHesh();

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
			bool f_returnarg = ac_ICS_takeMeasurementBLTV1(-1); //has return arg

			std::string f_StringAB = "";

			if(f_returnarg == true)
				{
				//Place Var 1
				std::string f_StringReturnVar = ac_ICS_Gen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaR");
				std::shared_ptr<classInsta> f_InstaR = std::make_shared_reflect<classInsta>(f_StringReturnVar, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaR);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringReturnVar;
				}
				
			std::string f_FunctionName1 = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_FunctionName2 = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_FunctionString = "Fcn%%" + f_FunctionName1 + "&*" + f_FunctionName2 + "%%";

			ag_StatusLive(f_ref_CurrentPath, "f_InstaB");
			std::shared_ptr<classInsta> f_InstaB = std::make_shared_reflect<classInsta>(f_FunctionString, ESL_INSTA_TYPE_FUNC_CALL);

			f_Function->m_vec_Insta.push_back(f_InstaB);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_FunctionString;

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_ICS_takeMeasurementBLTV1(1);

				if(m_arguScan == true)
					{
					//Place Argument Var
					std::string f_StringArgVar = ac_ICS_Gen_Var_fromHesh();

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
			bool f_returnarg = ac_ICS_takeMeasurementBLTV1(-1); //has return arg

			std::string f_StringAB = "";

			if(f_returnarg == true)
				{
				//Place Var 1
				std::string f_StringReturnVar = ac_ICS_Gen_Var_fromHesh();

				ag_StatusLive(f_ref_CurrentPath, "f_InstaR");
				std::shared_ptr<classInsta> f_InstaR = std::make_shared_reflect<classInsta>(f_StringReturnVar, ESL_INSTA_TYPE_VAR_CALL);

				f_Function->m_vec_Insta.push_back(f_InstaR);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringReturnVar;
				}

			std::string f_FunctionDefName1 = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_FunctionDefName2 = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_StringEB = "FuncDef%%" + f_FunctionDefName1 + "&*" + f_FunctionDefName2 + "%%";

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringEB, ESL_INSTA_TYPE_FUNC_DEF);
				
			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			f_StringAB += f_StringEB;

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_ICS_takeMeasurementBLTV1(1);

				if(m_arguScan == true)
					{
					//Place Argument Var
					std::string f_StringArgVar = ac_ICS_Gen_Var_fromHesh();

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
			std::string f_ClassStartName = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_ClassStartName2 = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_FUNC_CALL, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

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
			std::string f_ClassVarType = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_CLASSVAR_DEF, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);
			std::string f_ClassVarName = ac_ICS_MakeUnison(f_Target, ac_ICS_takeMeasurement(), 1, ESL_INSTA_TYPE_CLASSVAR_DEF, f_Function->m_idx_vec_Insta + 1, m_idx_vec_Function);

			std::string f_StringAB = "ClassVar%%" + f_ClassVarType + "&$" + f_ClassVarName + "%%";

			if(ac_ICS_takeMeasurementBLTV1(1) == true) // has reflection
				{
				std::string f_ReflectionVar1 = ac_ICS_takeMeasurement();
				std::string f_ReflectionVar2 = ac_ICS_takeMeasurement();

				f_StringAB += f_ReflectionVar1 + "#?" + f_ReflectionVar2 + "#?";
				}

			ag_StatusLive(f_ref_CurrentPath, "f_Insta");
			std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAB, ESL_INSTA_TYPE_CLASSVAR_DEF);
				
			f_Function->m_vec_Insta.push_back(f_Insta);
			f_Function->m_idx_vec_Insta++;

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_ICS_takeMeasurementBLTV1(1);

				if(m_arguScan == true)
					{
					//Place Argument Var
					std::string f_StringArgVar = ac_ICS_Gen_Var_fromHesh();

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

			if(ac_ICS_takeMeasurementBLTV1(7) == true)
				{
				//Place Argument Var
				std::string f_StringArgVar = ac_ICS_Gen_Var_fromHesh();

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

			if(ac_ICS_takeMeasurementBLTV1(7))
				{
				//Place Argument Var
				std::string f_StringArgVar = ac_ICS_Gen_Var_fromHesh();

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

		m_functionScan = ac_ICS_takeMeasurementBLTV1(7);

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

	f_func->m_ID = f_FunctionID;

	return f_func;
}

void classLMap::ac_ICS_DecFactor(int f_Type)
{
	m_Factor[f_Type]->m_Use--;
}

void classTarget_Ecom::ac_ICS_ResetLine(void)
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

void classLMap::ac_ICS_ResetLine(void)
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

std::string classLMap::ac_ICS_Gen_Var_fromEcom(int f_Prec_Type, bool f_Value_Given_Bool, std::string f_Var_Type_String, std::string f_Var_Name_String, std::string f_Var_Value_String)
{
	int f_SIndex_Typ = f_Prec_Type;
	bool f_SValueOn = f_Value_Given_Bool;
	std::string f_ValueString = f_Var_Value_String;

	//[0] - VarName
	std::string f_NameString = ac_ICS_recordMeasurement(f_Var_Name_String);
	std::string f_VarName = f_NameString;
	std::string f_StringA = "";

	//[1] - ValueOn
	f_SValueOn = ac_ICS_recordMeasurementBLTV1(f_SValueOn);

	int f_VarType = agFind_VarType_from_Precision(agFind_Precision(f_Var_Type_String));

	//Transient Check
	if(f_VarType >= MuVar_ClassVar_Class)
		{
		f_SIndex_Typ = ESL_MORF_TYPE_CLSVAR;
		}

	//Varso...!
	if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ESL_MORF_TYPE_VAR, f_SIndex_Typ)) == true)
		{
		//Float Parameter
		if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_FLOAT, f_VarType)) == true)
			{
			if(f_SValueOn == true)
				{
				char f_Char[150];
				FillChar(f_Char, 150);

				sprintf(f_Char, "%s", ac_ICS_recordMeasurementFLTV1(f_ValueString).c_str());

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
			if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_INT, f_VarType)) == true)
				{
				if(f_SValueOn == true)
					{
					char f_Char[150];
					FillChar(f_Char, 150);

					int f_ValueNr = ::atoi(f_ValueString.c_str());

					sprintf(f_Char, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

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
				if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_STRING, f_VarType)) == true)
					{
					if(f_SValueOn == true)
						{
						char f_Char[150];
						FillChar(f_Char, 150);

						std::string f_ValueNr = f_ValueString;

						sprintf(f_Char, "%s", ac_ICS_recordMeasurement(f_ValueNr).c_str());

						f_StringA += "Var%%string&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_StringA += "Var%%string&&" + f_VarName + "%%";
						}
					}
				else
					{
					//String Parameter
					if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_UINT, f_VarType)) == true)
						{
						if(f_SValueOn == true)
							{
							char f_Char[150];
							FillChar(f_Char, 150);

							int f_ValueNr = ::atoi(f_ValueString.c_str());

							sprintf(f_Char, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

							f_StringA += "Var%%uint&&" + f_VarName + "%%" + f_Char + "&%";
							}
						else
							{
							f_StringA += "Var%%uint&&" + f_VarName + "%%";
							}
						}
					else
						{
						//String Parameter
						if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_CHAR, f_VarType)) == true)
							{
							if(f_SValueOn == true)
								{
								char f_Char[150];
								FillChar(f_Char, 150);

								int f_ValueNr = ::atoi(f_ValueString.c_str());

								sprintf(f_Char, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

								f_StringA += "Var%%char&&" + f_VarName + "%%" + f_Char + "&%";
								}
							else
								{
								f_StringA += "Var%char&&" + f_VarName + "%%";
								}
							}
						else
							{
							//String Parameter
							if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_UCHAR, f_VarType)) == true)
								{
								if(f_SValueOn == true)
									{
									char f_Char[150];
									FillChar(f_Char, 150);

									int f_ValueNr = ::atoi(f_ValueString.c_str());

									sprintf(f_Char, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

									f_StringA += "Var%%uchar&&" + f_VarName + "%%" + f_Char + "&%";
									}
								else
									{
									f_StringA += "Var%%uchar&&" + f_VarName + "%%";
									}
								}
							else
								{
								//String Parameter
								if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_DOUBLE, f_VarType)) == true)
									{
									if(f_SValueOn == true)
										{
										char f_Char[150];
										FillChar(f_Char, 150);

										std::string f_ValueNr = f_ValueString;

										sprintf(f_Char, "%s", ac_ICS_recordMeasurementFLTV1(f_ValueString).c_str());

										f_StringA += "Var%%double&&" + f_VarName + "%%" + f_Char + "&%";
										}
									else
										{
										f_StringA += "Var%double&&" + f_VarName + "%%";
										}
									}
								else
									{
									//String Parameter
									if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_BOOL, f_VarType)) == true)
										{
										if(f_SValueOn == true)
											{
											char f_Char[150];
											FillChar(f_Char, 150);

											bool f_ValueNr = ::atoi(f_ValueString.c_str());

											sprintf(f_Char, "%i", ac_ICS_recordMeasurementBLTV1(f_ValueNr));

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
		if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ESL_MORF_TYPE_SYS, f_SIndex_Typ)) == true)
			{
			//Float Parameter
			if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_FLOAT, f_VarType)) == true)
				{
				if(f_SValueOn == true)
					{
					char f_Char1[150];
					FillChar(f_Char1, 150);

					float f_ValueNr = atof(f_ValueString.c_str());

					sprintf(f_Char1, "%s", ac_ICS_recordMeasurementFLTV1(f_ValueString).c_str());

					f_StringA += "Sys%%float&&" + f_VarName + "%%" + f_Char1 + "&%";
					}
				else
					{
					f_StringA += "Sys%%float&&" + f_VarName + "%%";
					}
				}
			else //INT SYS
				{
				//Int Parameter
				if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_INT, f_VarType)) == true)
					{
					if(f_SValueOn == true)
						{
						char f_Char2[150];
						FillChar(f_Char2, 150);

						int f_ValueNr = ::atoi(f_ValueString.c_str());
						
						sprintf(f_Char2, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

						f_StringA += "Sys%%int&&" + f_VarName + "%%" + f_Char2 + "&%";
						}
					else
						{
						f_StringA += "Sys%%int&&" + f_VarName + "%%";
						}
					}
				else
					{
					//String Parameter
					if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_STRING, f_VarType)) == true)
						{
						if(f_SValueOn == true)
							{
							char f_Char3[150];
							FillChar(f_Char3, 150);

							std::string f_ValueNr = f_ValueString;

							sprintf(f_Char3, "%s", ac_ICS_recordMeasurement(f_ValueNr).c_str());

							f_StringA += "Sys%%string&&" + f_VarName + "%%" + f_Char3 + "&%";
							}
						else
							{
							f_StringA += "Sys%%string&&" + f_VarName + "%%";
							}
						}
					else
						{
						//UInt Parameter
						if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_UINT, f_VarType)) == true)
							{
							if(f_SValueOn == true)
								{
								char f_Char4[150];
								FillChar(f_Char4, 150);

								int f_ValueNr = ::atoi(f_ValueString.c_str());
						
								sprintf(f_Char4, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

								f_StringA += "Sys%%uint&&" + f_VarName + "%%" + f_Char4 + "&%";
								}
							else
								{
								f_StringA += "Sys%%uint&&" + f_VarName + "%%";
								}
							}
						else
							{
							//String Parameter
							if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_CHAR, f_VarType)) == true)
								{
								if(f_SValueOn == true)
									{
									char f_Char5[150];
									FillChar(f_Char5, 150);

									int f_ValueNr = ::atoi(f_ValueString.c_str());

									sprintf(f_Char5, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

									f_StringA += "Sys%%char&&" + f_VarName + "%%" + f_Char5 + "&%";
									}
								else
									{
									f_StringA += "Sys%%char&&" + f_VarName + "%%";
									}
								}
							else
								{
								//String Parameter
								if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_UCHAR, f_VarType)) == true)
									{
									if(f_SValueOn == true)
										{
										char f_Char6[150];
										FillChar(f_Char6, 150);

										int f_ValueNr = ::atoi(f_ValueString.c_str());

										sprintf(f_Char6, "%i", ac_ICS_recordMeasurementINTS(f_ValueNr));

										f_StringA += "Sys%%uchar&&" + f_VarName + "%%" + f_Char6 + "&%";
										}
									else
										{
										f_StringA += "Sys%%uchar&&" + f_VarName + "%%";
										}
									}
								else
									{
									//Double Parameter
									if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_DOUBLE, f_VarType)) == true)
										{
										if(f_SValueOn == true)
											{
											char f_Char7[150];
											FillChar(f_Char7, 150);

											float f_ValueNr = atof(f_ValueString.c_str());
						
											sprintf(f_Char7, "%s", ac_ICS_recordMeasurementFLTV1(f_ValueString).c_str());

											f_StringA += "Sys%%double&&" + f_VarName + "%%" + f_Char7 + "&%";
											}
										else
											{
											f_StringA += "Sys%%double&&" + f_VarName + "%%";
											}
										}
									else
										{
										//String Parameter
										if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ECN_VAR_BOOL, f_VarType)) == true)
											{
											if(f_SValueOn == true)
												{
												char f_Char8[150];
												FillChar(f_Char8, 150);

												bool f_ValueNr = ::atoi(f_ValueString.c_str());

												sprintf(f_Char8, "%i", ac_ICS_recordMeasurementBLTV1(f_ValueNr));

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
			{ // classVar Singles
			if(ac_ICS_recordMeasurementBLTV1(ac_ext_Typing_isEqual(ESL_MORF_TYPE_CLSVAR, f_SIndex_Typ)) == true)
				{
				std::string f_TypeString = ac_ICS_recordMeasurement(f_Var_Type_String);

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

std::string classTarget_Ecom::ac_ICS_Gen_Var_fromHesh(void)
{	
	//[0] - VarName
	std::string f_NameString = ac_ICS_takeMeasurement();

	std::string f_VarName = f_NameString;

	//[1] - ValueOn
	bool f_SValueOn = ac_ICS_takeMeasurementBLTV1(-1);

	std::string f_StringA = "";

	//[2] - Varso
	if(ac_ICS_takeMeasurementBLTV1(-1))
		{
		char f_Char[150];

		FillChar(f_Char, 150);

		//Float Parameter
		if(ac_ICS_takeMeasurementBLTV1(-1) == true)
			{
			if(f_SValueOn == true)
				{
				sprintf(f_Char, "%f", ac_ICS_takeMeasurementFLTV1());

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
			if(ac_ICS_takeMeasurementBLTV1(-1) == true)
				{
				if(f_SValueOn == true)
					{
					sprintf(f_Char, "%i", ac_ICS_takeMeasurementINTS());

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
				if(ac_ICS_takeMeasurementBLTV1(-1) == true)
					{
					if(f_SValueOn == true)
						{
						sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
					if(ac_ICS_takeMeasurementBLTV1(-1) == true)
						{
						if(f_SValueOn == true)
							{
							sprintf(f_Char, "%i", ac_ICS_takeMeasurementINTS());

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
						if(ac_ICS_takeMeasurementBLTV1(-1) == true)
							{
							if(f_SValueOn == true)
								{
								sprintf(f_Char, "%i", ac_ICS_takeMeasurementINTS());

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
							if(ac_ICS_takeMeasurementBLTV1(-1) == true)
								{
								if(f_SValueOn == true)
									{
									sprintf(f_Char, "%i", ac_ICS_takeMeasurementINTS());

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
								if(ac_ICS_takeMeasurementBLTV1(-1) == true)
									{
									if(f_SValueOn == true)
										{
										sprintf(f_Char, "%f", ac_ICS_takeMeasurementFLTV1());

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
									if(ac_ICS_takeMeasurementBLTV1(-1) == true)
										{
										if(f_SValueOn == true)
											{
											sprintf(f_Char, "%i", ac_ICS_takeMeasurementBLTV1(-1));

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
		if(ac_ICS_takeMeasurementBLTV1(-1) == true)
			{
			char f_Char[150];
			FillChar(f_Char, 150);

			//Float Parameter
			if(ac_ICS_takeMeasurementBLTV1(-1) == true)
				{
				if(f_SValueOn == true)
					{
					sprintf(f_Char, "%f", ac_ICS_takeMeasurementFLTV1());

					f_StringA += "Sys%%float&&" + f_VarName + "%%" + f_Char + "&%";
					}
				else
					{
					f_StringA += "Sys%%float&&" + f_VarName + "%%";
					}
				}
			else
				{//Int Parameter
				if(ac_ICS_takeMeasurementBLTV1(-1) == true)
					{
					if(f_SValueOn == true)
						{
						sprintf(f_Char, "%i", ac_ICS_takeMeasurementINTS());

						f_StringA += "Sys%%int&&" + f_VarName + "%%" + f_Char + "&%";
						}
					else
						{
						f_StringA += "Sys%%int&&" + f_VarName + "%%" + f_Char + "&%";
						}
					}
				else
					{//String Parameter
					if(ac_ICS_takeMeasurementBLTV1(-1) == true)
						{
						sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
						if(ac_ICS_takeMeasurementBLTV1(-1) == true)
							{
							sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
							if(ac_ICS_takeMeasurementBLTV1(-1) == true)
								{
								sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
								if(ac_ICS_takeMeasurementBLTV1(-1) == true)
									{
									sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
									if(ac_ICS_takeMeasurementBLTV1(-1) == true)
										{
										sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
										if(ac_ICS_takeMeasurementBLTV1(-1) == true)
											{
											sprintf(f_Char, "%s", ac_ICS_takeMeasurement().c_str());

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
			{ // classVar Singles
			if(ac_ICS_takeMeasurementBLTV1(-1))
				{
				std::string f_TypeString = ac_ICS_takeMeasurement();

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

std::shared_ptr<Qcom_eslfunction> classLMap::ac_ICS_Gen_com_function_FromEcom(std::shared_ptr<Qcom_eslfunction> f_Save_Com_Function, std::shared_ptr<Qcom> f_Save_Com, std::shared_ptr<classTarget_Ecom> f_Target)
{
	std::string f_ref_CurrentPath = "classLMap::acGen_com_function_FromEcom";

	//add here save check consensus id as part of dependency loading
	int f_ConcensusID = ac_ICS_recordMeasurementINTS(ECOIN_CONSENSUS_ID);

	//Functionality typing re-execution time, FIXME: add miner destiny
	int f_FunctionType = ac_ICS_recordMeasurementINTV1(0, FuncExec_Total, 0, FuncExec_System_Load);

	ag_StatusLive(f_ref_CurrentPath, "f_Function");
	std::shared_ptr<classFunction> f_Function = std::make_shared_reflect<classFunction>();

	f_Function->m_Type = f_FunctionType;

	int f_StartLineCount = f_Save_Com_Function->m_vec_InitLineOrdered.size();
	int f_LineCount = f_StartLineCount - 1;
	int f_LineIndexCount = 0;

	//empty converted and exit
	if(ac_ICS_recordMeasurementBLTV1((f_Save_Com_Function->m_vec_InitLineOrdered.size() <= 0) ? true : false) == true)
		{
		std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert(f_Save_Com);

		return f_func;
		}

	int f_FunctionID = ac_ICS_recordMeasurementINTS(f_Save_Com_Function->m_ID);

	std::string f_StartLine = f_Save_Com_Function->m_vec_InitLineOrdered[0];

	std::vector<std::vector<std::string>> f_StartMorf = ac_ext_eslLine_morf_array(f_StartLine);

	//includes class def
	if(ac_ICS_recordMeasurementBLTV1((f_StartMorf[0][0].compare("ClassStart") == 0) || (f_StartMorf[0][0].compare("Class") == 0) || (f_StartMorf[0][0].compare("ClassDef") == 0) ? true : false) == true)
		{ //first line class definition
		std::string f_ClassStartName1 = ac_ICS_recordMeasurement(f_StartMorf[1][0]);

		std::string f_ClassStartName2 = ac_ICS_recordMeasurement(f_StartMorf[2][0]);

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

	ac_ICS_recordMeasurementBLTV1((f_LineTypeVK < 3) ? true : false); //returning cvar

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

		std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeVK, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

		f_Function->m_vec_String += f_StringAdd;
		}

	//include function def
	if(ac_ICS_recordMeasurementBLTV1(((f_StartFunctionMorf[f_Rarg_IDX][0].compare("Fus") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("Def") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("FuncDef") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("Function") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("FuncStart") == 0) ||
										(f_StartFunctionMorf[f_Rarg_IDX][0].compare("FunctionStart") == 0)) ? true : false) == true)
		{ //second line class definition
		std::string f_FunctionDefClassName = ac_ICS_recordMeasurement(f_StartFunctionMorf[1][0]);

		std::string f_FunctionDefName = ac_ICS_recordMeasurement(f_StartFunctionMorf[2][0]);

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
			f_argScan = ac_ICS_recordMeasurementBLTV1((f_Int < f_ArgumentCount) ? true : false);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_SIndex_Typ, f_vec_SingleVCVS_Number[f_Int], f_TypeString, f_NameString, f_ValueString);

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

		int f_LineType = ac_ICS_recordMeasurementINTV1(0, ESL_INSTA_TYPE_COUNT, 0, f_LineInstaType);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeVA, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_PositionSlider += 1;

			f_StringAB += "Cond%%";

			int f_FingerCount = ac_ICS_recordMeasurementINTV1(0, 5, 0, agFind_ConType(f_morfarray[f_PositionSlider][0]));

			f_PositionSlider += 1;

			std::string f_Name = ac_ICS_recordMeasurement(f_morfarray[f_PositionSlider][0]);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

			int f_FingerCount = ac_ICS_recordMeasurementINTV1(0, 9, 0, f_OperType);

			f_PositionSlider += 1;

			std::string f_Name = ac_ICS_recordMeasurement(f_morfarray[f_PositionSlider][0]);

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

			if(ac_ICS_recordMeasurementBLTV1((f_PositionSlider < f_morfarray.size()) ? true : false) == true)
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

					std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

			std::string f_forName = ac_ICS_recordMeasurement(f_morfarray[f_OffsetInt][0]);
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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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
				ac_ICS_recordMeasurementBLTV1(true); //has return arg

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}
			else
				{
				ac_ICS_recordMeasurementBLTV1(false); //has no return arg
				}

			f_OffsetIntArg = f_OffsetIntReturn;

			f_OffsetIntArg++;

			std::string f_FunctionType1 = ac_ICS_recordMeasurement(f_morfarray[f_OffsetIntArg][0]);

			f_OffsetIntArg++;

			std::string f_FunctionName2 = ac_ICS_recordMeasurement(f_morfarray[f_OffsetIntArg][0]);

			f_OffsetIntArg++;

			f_StringAB += "Fcn%%" + f_FunctionType1 + "&*" + f_FunctionName2 + "%%";

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_ICS_recordMeasurementBLTV1((f_OffsetIntArg < f_morfarray.size()) ? true : false); //has arg

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

						std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

			ac_ICS_recordMeasurementBLTV1((f_LineTypeV < 3) ? true : false); //has return arg

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

				std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

				ag_StatusLive(f_ref_CurrentPath, "f_Insta");
				std::shared_ptr<classInsta> f_Insta = std::make_shared_reflect<classInsta>(f_StringAdd, ESL_INSTA_TYPE_VAR_DEF);

				f_Function->m_vec_Insta.push_back(f_Insta);
				f_Function->m_idx_vec_Insta++;

				f_StringAB += f_StringAdd;
				}

			f_OffsetIntArg = f_ReturnIntArg;

			f_OffsetIntArg++;

			std::string f_FunctionDefClassName = ac_ICS_recordMeasurement(f_morfarray[f_OffsetIntArg][0]);

			f_OffsetIntArg++;

			std::string f_FunctionDefName = ac_ICS_recordMeasurement(f_morfarray[f_OffsetIntArg][0]);

			f_OffsetIntArg++;

			f_StringAB += "FuncDef%%" + f_FunctionDefClassName + "&*" + f_FunctionDefName + "%%";

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_ICS_recordMeasurementBLTV1((f_OffsetIntArg < f_morfarray.size()) ? true : false); //has arg

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

						std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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

			std::string f_ClassDefNameSpace = ac_ICS_recordMeasurement(f_morfarray[1][0]);

			std::string f_ClassDefName = ac_ICS_recordMeasurement(f_morfarray[2][0]);

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

			std::string f_FunctionClassVarType = ac_ICS_recordMeasurement(f_morfarray[1][0]);

			std::string f_FunctionClassVarName = ac_ICS_recordMeasurement(f_morfarray[2][0]);

			std::string f_StringAB = "ClassVar%%" + f_FunctionClassVarType + "&$" + f_FunctionClassVarName + "%%";

			int f_OffsetIntArg = 3;

			bool f_isLength = (f_OffsetIntArg < f_morfarray.size()) ? true : false;

			if(f_isLength == true)
				{
				bool f_isVar = ag_CVar_Check(f_morfarray[f_OffsetIntArg][1]);

				if(f_isVar == false)
					{
					//reflection class var init def
					ac_ICS_recordMeasurementBLTV1(true); //has reflection

					std::string f_FunctionReflectionVarName1 = ac_ICS_recordMeasurement(f_morfarray[f_OffsetIntArg][0]);

					f_OffsetIntArg++;

					std::string f_FunctionReflectionVarName2 = ac_ICS_recordMeasurement(f_morfarray[f_OffsetIntArg][0]);

					f_OffsetIntArg++;

					f_StringAB += f_FunctionReflectionVarName1 + "#?" + f_FunctionReflectionVarName2 + "#?";
					}
				else // is a CVar!
					{
					//lass var init def
					ac_ICS_recordMeasurementBLTV1(false);
					}
				}
			else
				{
				//lass var init def - length 0 no arg stage
				ac_ICS_recordMeasurementBLTV1(false);
				}

			m_arguScan = true;
			while(m_arguScan == true)
				{
				m_arguScan = ac_ICS_recordMeasurementBLTV1((f_OffsetIntArg < f_morfarray.size()) ? true : false); //has arg

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

						std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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
				ac_ICS_recordMeasurementBLTV1(true); //has var arg

				std::string f_ClassTypeName = ac_ICS_recordMeasurement(f_morfarray[1][0]);

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
				ac_ICS_recordMeasurementBLTV1(false); //FALSE has var arg

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

			bool f_arguScan = ac_ICS_recordMeasurementBLTV1((f_OffsetIntArg < f_morfarray.size()) ? true : false); //has arg

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

					std::string f_StringAdd = ac_ICS_Gen_Var_fromEcom(f_LineTypeV, f_HasNumber, f_TypeString, f_NameString, f_ValueString);

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
			f_ExtraLines = ac_ICS_recordMeasurementBLTV1(false);
			}
		else
			{
			f_ExtraLines = ac_ICS_recordMeasurementBLTV1(true);
			}

		if(f_ExtraLines == false)
			{
			f_Scan = false;
			}
		}

		//end of script
	f_Function->m_vec_String.pop_back(); // '/n'

	std::shared_ptr<Qcom_eslfunction> f_func = f_Function->acConvert(f_Save_Com);

	f_func->m_ID = f_FunctionID;

#ifdef ECOIN_DEBUG_BREAKS
	ag_ICS_EcoinSecure_Break_Assert(f_func->m_vec_InitLineOrdered.size(), f_LineIndexCount);
#endif

	return f_func;
}



int classLMap::ac_ICS_Compute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex, int f_ThreadElementIndex, int f_HowManyOnce)
{
	bool f_Success = true;

	int f_CorrectCount = 0;

	int f_StartElementIndex = f_ThreadElementIndex;
	int f_EndElementIndex = f_ThreadElementIndex + f_HowManyOnce;

	int f_MeasureIndex = g_CountLM * f_StartElementIndex;
	int f_EndMeasureIndex = g_CountLM * f_EndElementIndex;

	if(ac_ICS_PrepareLense(f_OCSCP_ThreadIndex, f_MeasureIndex) == false)
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
						if(ac_ICS_SaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
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
								int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_OCSCP_ThreadIndex);

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

								sprintf(f_Char, "%i - %i | %i - %i-%i\n", f_MeasureInteger, f_LMeasure->m_EndRange, f_LMeasure->m_MeasurementINTV1, f_LMeasure->m_EndRange, f_Success);

								g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

								g_Wallet->m_vec_ComputeText[m_IDX] += f_Char;

								g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

								delete f_Char;

								}break;

							case LMTYPE_MeasurementBLTV1:
								{
								bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);

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

								sprintf(f_Char, "%i - %s | %i - %s-%i\n", f_MeasureBoolean, "true", f_LMeasure->m_MeasurementBLTV1, "true", f_Success);

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

			sprintf(f_CharX, "%i All Correct Measures\n%i Measures %i Elements\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size());

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ComputeText[m_IDX] += f_CharX;

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

			delete f_CharX;
			}
		else
			{
			char* f_CharX = ag_ClearChar(256);

			sprintf(f_CharX, "%i Correct Measures False\n%i Measures %i Elements\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size());

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
						if(ac_ICS_SaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
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
								int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_OCSCP_ThreadIndex);

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
								bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);

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
						if(ac_ICS_SaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
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
						
						if(ac_ICS_SaveLense(f_OCSCP_ThreadIndex, f_MeasureIndex, f_DrawnElements) == false)
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

bool classLMap::ac_ICS_FinalCompute(std::shared_ptr<classCollection> f_Collection, int f_OCSCP_ThreadIndex)
{
	bool f_Success = true;
	int f_CorrectCount = 0;

	ac_ICS_PrepareLense(f_OCSCP_ThreadIndex);

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
							int f_MeasureInteger = ac_ICS_takeMeasurementINTV1(f_Element, f_LMeasure->m_StartRange, f_LMeasure->m_EndRange, f_LMeasure->m_WeightRangetoStart, f_OCSCP_ThreadIndex);

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

							sprintf(f_Char, "%i - %i | %i - %i-%i\n", f_MeasureInteger, f_LMeasure->m_EndRange, f_LMeasure->m_MeasurementINTV1, f_LMeasure->m_EndRange, f_Success);

							g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

							g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_Char;

							g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

							delete f_Char;

							}break;

						case LMTYPE_MeasurementBLTV1:
							{
							bool f_MeasureBoolean = ac_ICS_takeMeasurementBLTV1(f_Element, f_OCSCP_ThreadIndex);

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

							sprintf(f_Char, "%i - %s | %i - %s-%i\n", f_MeasureBoolean, "true", f_LMeasure->m_MeasurementBLTV1, "true", f_Success);

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

					sprintf(f_CharX, "%i 'All Good' Correct True\n%i Measures %i Elements On ElementsMAX[%i]\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size(), m_ADMAX);

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

			sprintf(f_CharX, "%i 'All Good' Correct True\n%i Measures %i Elements On ElementsMAX[%i]\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size(), m_ADMAX);

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->lock();

			g_Wallet->m_vec_ComputeText_Lowton[m_IDX] += f_CharX;

			g_Wallet->m_vec_Async_Gui_Muti[m_IDX]->unlock();

			delete f_CharX;
			}
		else
			{
			char* f_CharX = ag_ClearChar(256);

			sprintf(f_CharX, "%i Correct Measures LoadCom(0) False\n%i Measures %i Elements On ElementsMAX[%i]\n", f_CorrectCount, m_LMap->m_vec_Measure.size(), f_Collection->m_vec_Element.size(), m_ADMAX);

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

std::string classTarget_Ecom::ac_ICS_takeMeasurement(void)
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
			int f_PrimeValue = ac_ICS_takeMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, 3);

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
				int f_ControlValue = ac_ICS_takeMeasurementINTV1(0, f_EcoinControlMsMax, 0, 3);

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
				int f_DigitValue = ac_ICS_takeMeasurementINTV1(0, f_EcoinDigitMsMax, 0, 3);

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

std::string classTarget_Ecom::ac_ICS_takeMeasurement_DefaultValue(void)
{
	std::string f_CharAry;
	f_CharAry.clear();

	bool f_ScanDef = true;
	while(f_ScanDef == true)
		{
		int f_LetterType = ac_ICS_takeMeasurementINTV1(0, 8, 0, 3);

		if(f_LetterType == 0)
			{
			int f_Letter = ac_ICS_takeMeasurementINTV1(0, 26, 0, 3);

			f_CharAry.push_back((char)(f_Letter + 'a'));
			}
		else if(f_LetterType == 1)
			{
			int f_Letter = ac_ICS_takeMeasurementINTV1(0, 26, 0, 3);

			f_CharAry.push_back((char)(f_Letter + 'A'));
			}
		else if(f_LetterType == 7)
			{
			int f_Letter = ac_ICS_takeMeasurementINTV1(0, 10, 0, 3);

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

		f_ScanDef = ac_ICS_takeMeasurementBLTV1(0);
		}

	return f_CharAry;
}

std::string classTarget_Ecom::ac_ICS_takeMeasureKey()
{
	std::string f_StringResult;
		
	for(int f_XYZ = 0; f_XYZ < 27; f_XYZ++)
		{
		int f_KEY_TEXT_TYPE = ac_ICS_takeMeasurementINTV1(0, 2, 0, 3);
		
		switch(f_KEY_TEXT_TYPE)
			{
			case ECOIN_KEYTEXTTYPEB58_NUM:
				{
				int f_SelectF = ac_ICS_takeMeasurementINTV1(0, 9, 0, 3);

				char f_Char = '0' + f_SelectF;

				f_StringResult.push_back(f_Char);
				}break;

			case ECOIN_KEYTEXTTYPEB58_UPP:
				{
				int f_SelectF = ac_ICS_takeMeasurementINTV1(0, 26, 0, 3);

				char f_Char = 'A' + f_SelectF;

				f_StringResult.push_back(f_Char);
				}break;

			case ECOIN_KEYTEXTTYPEB58_LOW:
				{
				int f_SelectF = ac_ICS_takeMeasurementINTV1(0, 26, 0, 3);

				char f_Char = 'a' + f_SelectF;

				f_StringResult.push_back(f_Char);
				}break;
			}
		}

	return f_StringResult;
}

std::string classLMap::ac_ICS_takeMeasurement(shared_ptr<classElement> f_Vertex)
{
	std::string f_CharAry;
	f_CharAry.clear();

#if 0
	int f_EcoinSpecMax = 17;
		
	bool f_ScanMeasure = true;
	while(f_ScanMeasure == true)
		{
		int f_CharValue = ac_ICS_takeMeasurementINTV1(0, f_EcoinSpecMax, 0, 3);
		
		if((f_CharValue >= 0) && (f_CharValue <= 9))
			{
			f_CharAry += '0' + f_CharValue;
			}
		else if(f_CharValue == 11) //win conditions Upper Alpha
			{
			int f_Value = ac_ICS_takeMeasurementINTV1(0, 26, 0, 3);

			f_CharAry += 'A' + f_Value;
			}
		else if(f_CharValue == 12) //win conditions Lower Alpha
			{
			int f_Value = ac_ICS_takeMeasurementINTV1(0, 26, 0, 3);

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
int classTarget_Ecom::ac_ICS_takeMeasurementINTV1(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_Cap)  // scale resolution 1-3
{
	//naturalize ranges
	f_EndRange++;

	return m_LibraryID->m_Resultant->acReceive_INTV1(f_StartRange, f_EndRange);
}

int classLMap::ac_ICS_takeMeasurementINTV1(shared_ptr<classElement> f_Vertex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_OCSCP_ThreadIndex)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_ICS_takeMeasurementINTV1";
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

	float f_Float = 0.0f;

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

int ag_ICS_Pull_gen_Element(int f_ElementStartAD, int f_ElementEndAD, int f_ElementMax, int f_Depth, int f_OCSCP_ThreadIndex, int f_StartRange, int f_EndRange, int f_WeightRangetoStart)
{
	g_ElementDivisorInt[f_OCSCP_ThreadIndex]++;

	if(g_ElementDivisorInt[f_OCSCP_ThreadIndex] > g_CountLM)
		{
		g_ElementDivisorInt[f_OCSCP_ThreadIndex] = 1;

		g_ElementDivisor[f_OCSCP_ThreadIndex]++;
		}

	return g_ElementDivisor[f_OCSCP_ThreadIndex];
}

std::string classLMap::ac_ICS_recordMeasurement(std::string f_RecordResult)
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
		ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_EcoinPrimeMsMax - 1);

		f_PrimeControl = false;

		//control measure send 'All Stop'
		ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, f_EcoinControlMsMax);

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
				ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, f_EcoinControlMsMax - 1);

				f_PrimeControl = true;
				}

			if(f_Upper == false) //Lower -> Upper
				{
				ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_EcoinPrimeMsMax);

				f_Upper = true;
				}

			int f_LetterCode = ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_c - 'A');

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
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, f_EcoinControlMsMax - 1);

					f_PrimeControl = true;
					}

				if(f_Upper == true) //Upper -> Lower
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_EcoinPrimeMsMax);

					f_Upper = false;
					}

				//lowercase measure
				int f_LetterCode = ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_c - 'a');

				f_CharAry.push_back((char)(f_LetterCode + 'a'));
				}
			else
				{
				//primecontrol measure
				if(f_PrimeControl == true)
					{
					//Control measure
					ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_EcoinPrimeMsMax - 1);

					f_PrimeControl = false;
					}

				//Control measure
				if((f_c >= '0') && (f_c <= '9'))	//win conditions number
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, f_c - '0');

					f_CharAry.push_back((char)(f_LetterChar + '0'));
					}
				else if(f_c == '_')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 10);

					f_CharAry.push_back('_');
					}
				else if(f_c == '-')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 11);

					f_CharAry.push_back('-');
					}
				else if(f_c == '>')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 12);

					f_CharAry.push_back('>');
					}
				else if(f_c == ':')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 13);

					f_CharAry.push_back(':');
					}
				else if(f_c == '|')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 14);

					f_CharAry.push_back('|');
					}
				else if(f_c == '[')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 15);

					f_CharAry.push_back('[');
					}
				else if(f_c == ']')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 16);

					f_CharAry.push_back(']');
					}
				else if(f_c == '*')
					{
					ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 17);

					f_CharAry.push_back('*');
					}
				else if(f_c == '.')
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 18);

					f_CharAry.push_back('.');
					}
				else if(f_c == ' ')
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 19);

					f_CharAry.push_back(' ');
					}
				else if(f_c == '<')
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 20);

					f_CharAry.push_back('<');
					}
#ifdef ECOIN_SPECIAL_CHAR_APPENDIX
				else if(f_c == '?') //Activate Empty 1
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 21);

					f_CharAry.push_back('.');
					}
				else if(f_c == '?') //Activate Empty 2
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 22);

					f_CharAry.push_back('.');
					}
				else if(f_c == '?') //Activate Empty 2
					{
					int f_LetterChar = ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, 23);

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
		ac_ICS_recordMeasurementINTV1(0, f_EcoinPrimeMsMax, 0, f_EcoinPrimeMsMax - 1);

		f_PrimeControl = false;
		}

	//control measure send 'All Stop'
	ac_ICS_recordMeasurementINTV1(0, f_EcoinControlMsMax, 0, f_EcoinControlMsMax); //end cap

	return f_CharAry;
}

std::string classLMap::ac_ICS_recordMeasurement_DefaultValue(std::string f_RecordResult)
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
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 2);

			f_DefaultValueStr.push_back('_');
			}
		else if(f_c == '=')
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 3);

			f_DefaultValueStr.push_back('=');
			}
		else if(f_c == '"')
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 4);

			f_DefaultValueStr.push_back('"');
			}
		else if(f_c == '-')
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 5);

			f_DefaultValueStr.push_back('-');
			}
		else if(f_c == '.')
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 6);

			f_DefaultValueStr.push_back('.');
			}
		else if(isupper(f_c) == 1)
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 1);

			ac_ICS_recordMeasurementINTV1(0, 26, 0, f_c - 'A');

			f_DefaultValueStr.push_back(f_c);
			}
		else if((f_c >= 'a') && (f_c <= 'z'))
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 0);

			ac_ICS_recordMeasurementINTV1(0, 26, 0, f_c - 'a');

			f_DefaultValueStr.push_back(f_c);
			}
		else if((f_c >= '0') && (f_c <= '9'))
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 7);

			ac_ICS_recordMeasurementINTV1(0, 10, 0, f_c - '0');

			f_DefaultValueStr.push_back(f_c);
			}
		else if(f_c == ',')
			{
			ac_ICS_recordMeasurementINTV1(0, 8, 0, 8);

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

		f_Scan = ac_ICS_recordMeasurementBLTV1((f_Jet < f_RecordResult.length()) ? true : false);
		}

	return f_DefaultValueStr;
}

//notice do not pull element in function above this one
std::string classLMap::ac_ICS_recordMeasureKey(std::string f_RecordResult)
{
	std::string f_StringResult = "";

	int f_IndexID = 2;

	for(int f_Jet = 0; f_Jet < 27; f_Jet++)
		{
		char f_c = f_RecordResult.at(f_Jet);

		if((f_c >= '0') && (f_c <= '9'))
			{
			ac_ICS_recordMeasurementINTV1(0, 2, 0, ECOIN_KEYTEXTTYPEB58_NUM);

			ac_ICS_lastMeasurement(f_IndexID);

			int f_RC = (int)f_c - (int)'0';

			ac_ICS_recordMeasurementINTV1(0, 9, 0, f_RC);

			ac_ICS_lastMeasurement(f_IndexID);
			}
		else
			{
			if(isupper(f_c) == 1)
				{
				ac_ICS_recordMeasurementINTV1(0, 2, 0, ECOIN_KEYTEXTTYPEB58_UPP);

				ac_ICS_lastMeasurement(f_IndexID);

				int f_RC = (int)f_c - (int)'A';

				ac_ICS_recordMeasurementINTV1(0, 26, 0, f_RC);

				ac_ICS_lastMeasurement(f_IndexID);
				}
			else
				{
				ac_ICS_recordMeasurementINTV1(0, 2, 0, ECOIN_KEYTEXTTYPEB58_LOW);

				ac_ICS_lastMeasurement(f_IndexID);

				int f_RC = (int)f_c - (int)'a';

				ac_ICS_recordMeasurementINTV1(0, 26, 0, f_RC);

				ac_ICS_lastMeasurement(f_IndexID);
				}
			}

		f_StringResult.push_back(f_c);
		}

	return f_StringResult;
}

int classLMap::ac_ICS_recordMeasurementINTV1(int f_StartRange, int f_EndRange, int f_WeightRangetoStart, int f_RecordResult, bool f_Notable)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_ICS_recordMeasurementINTV1";
#endif

	//apply endrange inclusive
	f_EndRange++;

	//apply startrange inclusive
	f_RecordResult -= f_StartRange;

	ag_StatusLive(f_ref_CurrentPath, "f_Measure");

	shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(f_StartRange, f_EndRange, f_WeightRangetoStart, 1, 1, f_RecordResult);

	f_Measure->m_Notable = f_Notable;

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);

	f_RecordResult += f_StartRange;

	return f_RecordResult;
}

std::string classLMap::ac_ICS_recordMeasurementFLTV1(std::string f_extString)  // scale resolution 1-3
{
	std::string f_ResultStringPre = f_extString;
	std::string f_ResultString = "";

	int f_ClackCap = 0;
	bool f_Minus = false;

	if(f_ResultStringPre.at(0) == '-')
		{
		ac_ICS_recordMeasurementBLTV1(true);

		for(int f_Int = 1; f_Int < f_ResultStringPre.length(); f_Int++)
			{
			f_ResultString.push_back(f_ResultStringPre.at(f_Int));
			}

		f_Minus = true;
		}
	else
		{
		ac_ICS_recordMeasurementBLTV1(false);

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

	int f_ClackApp = ag_min(ag_max(f_ClackCap, 12), 1);

	int f_ClackLength = ac_ICS_recordMeasurementINTV1(1, 12, 0, f_ClackCap);

	int f_Length = ac_ICS_recordMeasurementINTV1(3, 18, 0, f_ResultString.length());

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
				int f_BigC = ac_ICS_recordMeasurementINTV1(0, 9, 0, (f_c - f_MinChar));

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

bool classLMap::ac_ICS_recordMeasurementBLTV1(bool f_RecordResult)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_ICS_recordMeasurementBLTV1";
#endif

#if 0
	ac_LikelyBreak(m_LMap->m_vec_Measure.size(), f_ElementID);
#endif

	ag_StatusLive(f_ref_CurrentPath, "f_Measure");
	shared_ptr<LMeasure> f_Measure = make_shared_reflect<LMeasure>(1, 1, f_RecordResult);

	//save lense recording
	m_LMap->m_vec_Measure.push_back(f_Measure);

	return f_RecordResult;
}

//element level specify schema
float classTarget_Ecom::ac_ICS_takeMeasurementFLTV1(void)  // scale resolution 1-3
{
	bool f_Minus = ac_ICS_takeMeasurementBLTV1(4);

	//uncorrected floating measurement
	int f_ClackCap = ac_ICS_takeMeasurementINTV1(1, 12, 0, 4);

	int f_Length = ac_ICS_takeMeasurementINTV1(3, 18, 0, 5);

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
			int f_BigC = ac_ICS_takeMeasurementINTV1(0, 9, 0, 4);

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

float classLMap::ac_ICS_takeMeasurementFLTV1(shared_ptr<classElement> f_Vertex, float f_StartRange, float f_EndRange, float f_WeightRangetoStart)  // scale resolution 1-3
{
	bool f_Minus = ac_ICS_takeMeasurementBLTV1(f_Vertex, 0);

	//uncorrected floating measurement
	int f_ClackCap = ac_ICS_takeMeasurementINTV1(f_Vertex, 1, 12, 0, 0);

	int f_Length = ac_ICS_takeMeasurementINTV1(f_Vertex, 3, 18, 0, 0);

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
			int f_BigC = ac_ICS_takeMeasurementINTV1(f_Vertex, 0, 9, 0, 0);

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

std::Smart_Ptr<ICS_Mainstream> ag_MainstreamNew(void)
{
	std::Smart_Ptr<ICS_Mainstream> f_Mainstream = std::ag_Make_Smart_Pointer<ICS_Mainstream>();

	f_Mainstream->m_owner = g_Wallet->GetAdr().c_str();

	f_Mainstream->acSaveCloud();

	return f_Mainstream;
}

std::Smart_Ptr<ICS_Mainstream> ag_RequestMainstream(int f_TimeCheckPoint, int f_MainstreamID)
{
	char* mainstreamquery = (char*)malloc(sizeof(char) * 2048);

	::sprintf(mainstreamquery, "SELECT id, maxcheckpoint, owner, quadrantscale, depthscale, tunscale, datakey FROM mainstream WHERE id = %i", f_MainstreamID);

	g_SafeL[2]->acMainstreamSelectCommand(mainstreamquery);

	int f_MainstreamCount = 0;

	if(g_Schedular[2]->acMSEntry(0)[0].at(0) != '0')
		{
		f_MainstreamCount = g_Schedular[2]->acMSEntrySize();
		}

	if(f_MainstreamCount == 1)
		{
		int f_MaxCheckPoint = atoi(g_Schedular[2]->acMSEntry(0)[1].c_str());
		std::string f_owner = g_Schedular[2]->acMSEntry(0)[2];
		float f_QuadrantScale = atof(g_Schedular[2]->acMSEntry(0)[3].c_str());
		float f_DepthScale = atof(g_Schedular[2]->acMSEntry(0)[4].c_str());
		float f_TunScale = atof(g_Schedular[2]->acMSEntry(0)[5].c_str());
		std::string f_DataKeyString = g_Schedular[2]->acMSEntry(0)[6];

		std::Smart_Ptr<ICS_CheckPointPassword> f_CP_Password = std::ag_Make_Smart_Pointer<ICS_CheckPointPassword>(f_DataKeyString);

		std::Smart_Ptr<ICS_Mainstream> f_Mainstream = std::ag_Make_Smart_Pointer<ICS_Mainstream>(f_TimeCheckPoint, f_QuadrantScale, f_DepthScale, f_TunScale, f_CP_Password);

		f_Mainstream->m_MaxCheckPoint = f_MaxCheckPoint;
		f_Mainstream->m_owner = f_owner;
		f_Mainstream->m_MainstreamID = f_MainstreamID;

		return f_Mainstream;
		}

#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

	return nullptr;
}

std::string ICS_Mainstream::acHash(void)
{
	CubeHASH_originstring f_CubeHashRecv;

	f_CubeHashRecv.acPushInt(m_MaxCheckPoint);
	f_CubeHashRecv.acPushString(m_owner);
	f_CubeHashRecv.acPushFloat(m_QuadrantScale);
	f_CubeHashRecv.acPushInt(m_DepthScaleDivision);
	f_CubeHashRecv.acPushInt(m_TunScaleDivision);
	f_CubeHashRecv.acPushString(m_CP_Password->m_PrintString);

	std::string f_InputHash = f_CubeHashRecv.acGetInput();

	g_hasha.init(); //reset hasher state
	g_hasha.process(f_InputHash.begin(), f_InputHash.end());
	g_hasha.finish();
	picosha2::get_hash_hex_string(g_hasha, f_CubeHashRecv.m_str_Input);

	return f_CubeHashRecv.m_str_Input;
}

void ICS_Mainstream::acSaveCloud(void)
{
	std::string f_str_Input = acHash();

	  ///////////////////
	 // Save in Cloud
	//
	char* g_mainstreamfield[7];
	char* g_mainstreamvalue[7];

	for(int f_Count = 0; f_Count < 7; f_Count++)
		{
		g_mainstreamfield[f_Count] = (char*)malloc(sizeof(char) * 512);
		g_mainstreamvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
		}

	::sprintf(g_mainstreamfield[0], "maxcheckpoint");
	::sprintf(g_mainstreamfield[1], "owner");
	::sprintf(g_mainstreamfield[2], "quadrantscale");
	::sprintf(g_mainstreamfield[3], "depthscale");
	::sprintf(g_mainstreamfield[4], "tunscale");
	::sprintf(g_mainstreamfield[5], "datakey");
	::sprintf(g_mainstreamfield[6], "hash");

	::sprintf(g_mainstreamvalue[0], "%i", 0);
	::sprintf(g_mainstreamvalue[1], "%s", g_Wallet->GetAdr().c_str());
	::sprintf(g_mainstreamvalue[2], "%f", m_QuadrantScale);
	::sprintf(g_mainstreamvalue[3], "%i", m_DepthScaleDivision);
	::sprintf(g_mainstreamvalue[4], "%i", m_TunScaleDivision);
	::sprintf(g_mainstreamvalue[5], "%s", m_CP_Password->m_PrintString.c_str());
	::sprintf(g_mainstreamvalue[6], "%s", f_str_Input.c_str());

	g_SafeL[2]->Mainstream_Insert("mainstream", (const char**)g_mainstreamfield, (const char**)g_mainstreamvalue, 7, false, false);

	for(int f_Count = 0; f_Count < 7; f_Count++)
		{
		free(g_mainstreamfield[f_Count]);
		free(g_mainstreamvalue[f_Count]);
		}

	char f_query[256];

	sprintf(f_query, "SELECT id FROM mainstream WHERE hash = '%s'", f_str_Input.c_str());

	g_SafeL[0]->acSelectCommand(f_query, false, false);

	int f_LCount = 0;
		
	if(g_Schedular[0]->acEntry(0)[0].at(0) == '0')
		{
		f_LCount = 0;
		}
	else
		{
		f_LCount = g_Schedular[0]->acEntrySize();
		}

	//ECN::Stat:::
	if(f_LCount == 1)
		{
		m_MainstreamID = atoi(g_Schedular[0]->acEntry(0)[0].c_str());
		}

#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif //add debug message
}

void ICS_Mainstream::acPrepare(int f_TimeCheckPoint, float f_QuadrantScale, bool f_Compress, int f_DepthScaleDivision, int f_TunScaleDivision)
{
	g_CountController = std::make_shared<ICS_CountControl>(ICS_SIZE_LOWER_BOUND, ICS_SIZE_UPPER_BOUND, f_TimeCheckPoint, f_QuadrantScale, m_CP_Password->acMixFactor());

	if(f_Compress == true)
		{
		g_CountController->m_Start_Quadrant = (float)f_TimeCheckPoint * f_QuadrantScale;
		g_CountController->m_Tun_Quadrant = ((float)f_TimeCheckPoint + 1.0f) * f_QuadrantScale;
		}
	else
		{
		g_CountController->m_Tun_Quadrant = (float)f_TimeCheckPoint * f_QuadrantScale;
		g_CountController->m_Start_Quadrant = ((float)f_TimeCheckPoint + 1.0f) * f_QuadrantScale;
		}

	m_QuadrantScale = f_QuadrantScale;

	m_DepthScaleDivision = f_DepthScaleDivision;
	m_TunScaleDivision = f_TunScaleDivision;

	// Start Vectors
	m_StartNearGround = std::make_shared<BiVector>(g_CountController->m_Start_Quadrant, ICS_MAINHEIGHTSTART, 0.0f);
	m_StartFarGround = std::make_shared<BiVector>(g_CountController->m_Start_Quadrant, ICS_MAINHEIGHTSTART, ICS_MAINSCALE);

	m_Pos = std::make_shared<BiVector>(g_CountController->m_Start_Quadrant, 0.0f, (m_StartFarGround->m_Z - m_StartNearGround->m_Z) * 0.5f);

	// Mainstream Start Point
	m_WritePosition = std::make_shared<BiVector>(m_StartNearGround->m_X, m_StartNearGround->m_Y, m_StartNearGround->m_Z);

	m_SphereIndex = 0;
}

ICS_Mainstream::ICS_Mainstream()
{
	m_MainstreamID = 0;
	m_TimeCheckPoint = 0;

	m_CP_Password = std::ag_Make_Smart_Pointer<ICS_CheckPointPassword>(true);

	acPrepare(0, ICS_DEFAULT_QUADRANT_SIZE, true);

	acStartSpheres();

	m_StartTime = 0;
}

ICS_Mainstream::ICS_Mainstream(float f_QuadrantScale)
{
	m_MainstreamID = 0;
	m_TimeCheckPoint = 0;

	m_CP_Password = std::ag_Make_Smart_Pointer<ICS_CheckPointPassword>(true);

	float f_TunDivFloat = ((f_QuadrantScale - ICS_MAINSCALE) / ICS_MAINSCALE) + 1.0f;

	int f_TunDivInt = (int)f_TunDivFloat * ICS_MAINDIV;

	acPrepare(0, f_QuadrantScale, true, ICS_MAINSCALE / (float)(ICS_MAINDIV + 1), (float)ICS_MAINDIV * (float)(f_TunDivInt + 1));

	acStartSpheres();

	m_StartTime = 0;
}

ICS_Mainstream::ICS_Mainstream(int f_TimeCheckPoint, float f_QuadrantScale, bool f_Compress)
{
	m_MainstreamID = 0;
	m_TimeCheckPoint = f_TimeCheckPoint;

	m_CP_Password = std::ag_Make_Smart_Pointer<ICS_CheckPointPassword>();

	float f_TunDivFloat = ((f_QuadrantScale - ICS_MAINSCALE) / ICS_MAINSCALE) + 1.0f;

	int f_TunDivInt = (int)f_TunDivFloat * ICS_MAINDIV;

	acPrepare(f_TimeCheckPoint, f_QuadrantScale, f_Compress, ICS_MAINSCALE / (float)(ICS_MAINDIV + 1), (float)ICS_MAINDIV * (float)(f_TunDivInt + 1));

	acStartSpheres();

#ifdef ICS_LONG_POINT_TIME
	std::chrono::seconds f_Seconds(ICS_TIMECHECKPOINT_SECONDS * f_TimeCheckPoint);

	std::chrono::nanoseconds f_NanoSeconds(f_Seconds);

	m_StartTime = f_NanoSeconds.count();
#else
	m_StartTime = 0;
#endif
}

ICS_Mainstream::ICS_Mainstream(int f_TimeCheckPoint, float f_QuadrantScale, float f_DepthScale, float f_TunScale, std::Smart_Ptr<ICS_CheckPointPassword> f_CP_Password)
{
	m_MainstreamID = 0;
	m_TimeCheckPoint = f_TimeCheckPoint;

	//Save Password
	m_CP_Password = f_CP_Password;

	acPrepare(f_TimeCheckPoint, f_QuadrantScale, false, f_DepthScale, f_TunScale);

	acStartSpheres();

#ifdef ICS_LONG_POINT_TIME
	std::chrono::seconds f_Seconds(ICS_TIMECHECKPOINT_SECONDS * f_TimeCheckPoint);

	std::chrono::nanoseconds f_NanoSeconds(f_Seconds);

	m_StartTime = f_NanoSeconds.count();
#else
	m_StartTime = 0;
#endif
}

void ICS_Mainstream::acStartSpheres(void)
{
	for(int f_SphereTun = 0; f_SphereTun < m_TunScaleDivision; f_SphereTun++)
		{
		m_WritePosition->m_X = ((f_SphereTun + 1) / (m_TunScaleDivision + 2)) * m_QuadrantScale;

		for(int f_SphereDepth = 0; f_SphereDepth < m_DepthScaleDivision; f_SphereDepth++)
			{
			m_WritePosition->m_Y = ICS_MAINHEIGHTSTART;
			m_WritePosition->m_Z = ((f_SphereDepth + 1) / (m_DepthScaleDivision + 2)) * ICS_MAINSCALE;

			std::shared_ptr<ICS_Sphere> f_Sphere = std::make_shared<ICS_Sphere>(m_WritePosition, ICS_SPHERE_DEFAULT);

			f_Sphere->acSize();

			f_Sphere->acMove();

			m_vec_Sphere.push_back(f_Sphere);
			}
		}
}

void ICS_Mainstream::acStartStream(std::Smart_Ptr<ICS_LibraryID> f_LibraryID)
{
	m_Pos->m_X = f_LibraryID->m_Resultant->m_FinalXLength;

#ifdef ICS_LONG_POINT_TIME
	long long f_CombinedLength = m_StartTime + f_LibraryID->m_HighPrecisionTime;
#else
	long long f_CombinedLength = f_LibraryID->m_HighPrecisionTime;
#endif

	if(f_CombinedLength > 0)
		{
		for(int f_SphereIndex = 0; f_SphereIndex < m_vec_Sphere.size(); f_SphereIndex++)
			{
			std::shared_ptr<ICS_Sphere> f_Sphere = m_vec_Sphere[f_SphereIndex];

			f_Sphere->acTravel(f_CombinedLength);
			}
		}
}

void ICS_Mainstream::acPositionLocation(std::Smart_Ptr<ICS_LibraryID> f_LibraryID)
{
	m_Pos->m_X = f_LibraryID->m_Resultant->m_FinalXLength;
}

void Compressor(std::shared_ptr<Qcom> f_com)
{
	std::string f_ref_CurrentPath = g_ref_delegate_start + "Compressor::Compressor";

	// auto begin = std::chrono::high_resolution_clock::now();

	// time_point

	// code to benchmark

	//auto end = std::chrono::high_resolution_clock::now();

	//std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

	std::shared_ptr<classTarget_Ecom> f_classTarget_Ecom = std::make_shared<classTarget_Ecom>();

	g_classLMap = std::make_shared<classLMap>(g_Wallet->m_current_IDX);

	std::shared_ptr<Qcom> f_c = g_classLMap->ac_ICS_Gen_com_FromEcom(f_com, f_classTarget_Ecom);

	  /////////////////
	 // Compression //
	/////////////////

	std::Smart_Ptr<ICS_Mainstream> f_Mainstream = ag_MainstreamNew();

#if 0
	std::shared_ptr<CubeHESH> f_Hesh = g_classLMap->ac_ICS_Gen_hesh_com(f_Mainstream);
#else
	std::Smart_Ptr<ICS_LibraryID> f_LibraryID = g_classLMap->acGen_LibraryID(f_Mainstream);

	std::shared_ptr<Cube::CubeHESH> f_Hesh = f_LibraryID->acSaveHesh();
#endif

	f_Hesh->acSaveCloud(f_com->m_name, f_com->m_ID);

	  ////////////////////
	 // Un-Compression //
	////////////////////

	std::shared_ptr<classTarget_Ecom> f_EcomTarget_A = std::make_shared<classTarget_Ecom>();
	std::shared_ptr<classTarget_Ecom> f_EcomTarget_B = std::make_shared<classTarget_Ecom>();

																				// mebbe time check point forward
	std::Smart_Ptr<ICS_Mainstream> f_Compression_Mainstream = ag_RequestMainstream(0, f_Mainstream->m_MainstreamID);

	std::shared_ptr<Qcom> f_com_C = f_EcomTarget_A->ac_ICS_Gen_com_FromHesh(f_Compression_Mainstream, f_Hesh, f_EcomTarget_B);

	int f_Uncompressed_Com_ID = f_com_C->m_ID;

	int X = 1;
}

void ICS_Mainstream::acPlay_Until(long long f_HighPrecisionTime)
{
	for(int f_XY = 0; f_XY < m_vec_Sphere.size(); f_XY++)
		{
		std::shared_ptr<ICS_Sphere> f_Sphere = m_vec_Sphere[f_XY];

		f_Sphere->acTravel(f_HighPrecisionTime);
		}
}

float ICS_Mainstream::acProvideConnection(void)
{
	std::shared_ptr<ICS_Sphere> f_Sphere = m_vec_Sphere[m_SphereIndex];

	m_SphereIndex++;

	if(m_SphereIndex >= m_vec_Sphere.size())
		{
		m_SphereIndex = 0;
		}

	BiVector f_DistVector(m_Pos->m_X - f_Sphere->m_Center->m_X, m_Pos->m_Y - f_Sphere->m_Center->m_Y, m_Pos->m_Z - f_Sphere->m_Center->m_Z);

	float f_Magnitude = f_DistVector.acLength() * ICS_MAGNITUDE;

	return frac(sin(f_Magnitude));
}

double ICS_Mainstream::acProvideConnectionDouble(void)
{
	std::shared_ptr<ICS_Sphere> f_Sphere = m_vec_Sphere[m_SphereIndex];

	m_SphereIndex++;

	if(m_SphereIndex >= m_vec_Sphere.size())
		{
		m_SphereIndex = 0;
		}

	BiVector f_DistVector(m_Pos->m_X - f_Sphere->m_Center->m_X, m_Pos->m_Y - f_Sphere->m_Center->m_Y, m_Pos->m_Z - f_Sphere->m_Center->m_Z);

	double f_MagnitudeDouble = f_DistVector.acLength() * ICS_MAGNITUDE_DOUBLE;

	return frac(sin(f_MagnitudeDouble));
}

void ICS_Resultant::acRegisterFrame(void)
{
	if(m_FLR > ICS_COMPLETE)
		{
		m_FLR -= ICS_COMPLETE;
		}
	else if(m_FLR < 0.0f)
		{
		m_FLR += ICS_COMPLETE;
		}
}

void ICS_Resultant::acForwardFrameOn(void)
{
	double f_ResultFactor = m_Mainstream->acProvideConnectionDouble() * ICS_FRAME;

	m_FLR += f_ResultFactor;

	acRegisterFrame();
}

void ICS_Resultant::acForwardFrameOff(void)
{
	double f_ResultFactor = m_Mainstream->acProvideConnectionDouble() * ICS_FRAME;

	m_FLR -= f_ResultFactor;

	acRegisterFrame();
}

void ICS_Resultant::acBLTV1(bool f_Measurement)
{
	acForwardFrameOn();

	double f_MainstreamResult = m_Mainstream->acProvideConnectionDouble();

	m_Mainstream->m_Pos->m_X += ICS_ADVANCE;

	if(m_Mainstream->m_Pos->m_X >= m_Mainstream->m_QuadrantScale)
		{
		m_Mainstream->m_Pos->m_X = 0.0f;
		}

	m_FinalXLength = m_Mainstream->m_Pos->m_X;

	double f_Aggreget = (m_FLR + f_MainstreamResult);

	m_FLR += f_Aggreget;

	acRegisterFrame();
}

void ICS_Resultant::acINTV1(int f_StartRange, int f_EndRange, int f_Result)
{
	acForwardFrameOn();

	double f_MainstreamResult = m_Mainstream->acProvideConnectionDouble() * f_EndRange;

	m_Mainstream->m_Pos->m_X += ICS_ADVANCE;

	if(m_Mainstream->m_Pos->m_X >= m_Mainstream->m_QuadrantScale)
		{
		m_Mainstream->m_Pos->m_X = 0.0f;
		}

	m_FinalXLength = m_Mainstream->m_Pos->m_X;

	double f_FLR = (m_FLR / 28.0f) * f_EndRange;

	double f_Aggreget = (double)f_StartRange + ((m_FLR + f_MainstreamResult) * 0.5f);

	m_FLR += f_Aggreget;

	acRegisterFrame();
}

bool ICS_Resultant::acReceive_BLTV1(void)
{
	double f_MainstreamResult = m_Mainstream->acProvideConnectionDouble();

	m_Mainstream->m_Pos->m_X -= ICS_ADVANCE;

	if(m_Mainstream->m_Pos->m_X < 0.0f)
		{
		m_Mainstream->m_Pos->m_X = m_Mainstream->m_QuadrantScale;
		}

	double f_Aggreget = (m_FLR + f_MainstreamResult);

	acForwardFrameOff();

	//Measurement
	if(f_Aggreget >= 1.0f)
		{
		return true;
		}
	else
		{
		return false;
		}
}

int ICS_Resultant::acReceive_INTV1(int f_StartRange, int f_EndRange)
{
	double f_MainstreamResult = m_Mainstream->acProvideConnectionDouble();

	m_Mainstream->m_Pos->m_X -= ICS_ADVANCE;

	if(m_Mainstream->m_Pos->m_X < 0.0f)
		{
		m_Mainstream->m_Pos->m_X = m_Mainstream->m_QuadrantScale;
		}

	double f_FLR_Conv = (m_FLR / 28.0f) * (double)f_EndRange;

	double f_Aggreget = (f_FLR_Conv + f_MainstreamResult) * 0.5f;

	int f_IntResult = (int)f_Aggreget + f_StartRange;

	acForwardFrameOff();

	//Measurement
	return f_IntResult;
}

std::Smart_Ptr<ICS_LibraryID> classLMap::acGen_LibraryID(std::Smart_Ptr<ICS_Mainstream> f_Mainstream)
{
	std::Smart_Ptr<ICS_LibraryID> f_LibraryID = std::ag_Make_Smart_Pointer<ICS_LibraryID>();

	f_LibraryID->m_MainstreamID = f_Mainstream->m_MainstreamID;

	f_Mainstream->acStartStream(f_LibraryID);

	f_LibraryID->m_Resultant->acConnectMainstream(f_Mainstream);

	for(int f_XY = 0; f_XY < m_LMap->m_vec_Measure.size(); f_XY++)
		{
		std::shared_ptr<LMeasure> f_Measure = m_LMap->m_vec_Measure[f_XY];

		//Boolean Measure
		if(f_Measure->m_LMType == LMTYPE_MeasurementBLTV1)
			{
			f_LibraryID->m_Resultant->acBLTV1(f_Measure->m_MeasurementBLTV1);
			}
		else //Integer Measure
			{
			f_LibraryID->m_Resultant->acINTV1(f_Measure->m_StartRange, f_Measure->m_EndRange, f_Measure->m_MeasurementINTV1);
			}
		}

	return f_LibraryID;
}

std::shared_ptr<Cube::CubeHESH> classLMap::ac_ICS_Gen_hesh_com(std::Smart_Ptr<ICS_Mainstream> f_Mainstream)
{
	std::Smart_Ptr<ICS_LibraryID> f_LibraryID = acGen_LibraryID(f_Mainstream);

	std::shared_ptr<Cube::CubeHESH> f_Hesh = f_LibraryID->acSaveHesh();

	//win conditions!
	return f_Hesh;
}

std::shared_ptr<Cube::CubeHESH> ICS_LibraryID::acSaveHesh(void)
{
	std::shared_ptr<Cube::CubeHESH> f_Hesh = std::make_shared<Cube::CubeHESH>(1, 1, 1, 1);

	std::shared_ptr<Cube::CubeBicycle> f_Bicycle = std::make_shared<Cube::CubeBicycle>();
	f_Hesh->vec_Bicycle.push_back(f_Bicycle);

	f_Hesh->m_bckblue = random();
	f_Hesh->m_bckred = random();
	f_Hesh->m_bckgreen = random();

	int f_IndexValue = m_TimeCheckPoint;

	std::shared_ptr<BiVector> f_Position = std::make_shared<BiVector>(true);
	f_Bicycle->vec_Vertex.push_back(f_Position);
	f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

	f_Position->acIntegerPosition(f_IndexValue); // [SAVE] m_TimeCheckPoint

	long long f_HighPrecisionTime = m_HighPrecisionTime;

	bool f_Scan = true;
	while(f_Scan == true)
		{
		int f_LoadInteger = 0;

		if(f_HighPrecisionTime > ICS_INTEGER_STACK_HIGH)
			{
			f_LoadInteger = ICS_INTEGER_STACK_HIGH;

			f_HighPrecisionTime -= f_LoadInteger;
			}
		else
			{
			f_LoadInteger = f_HighPrecisionTime; // [SAVE] m_HighPrecisionTime

			f_Scan = false;
			}

		std::shared_ptr<BiVector> f_Position_B = std::make_shared<BiVector>(true);
		f_Bicycle->vec_Vertex.push_back(f_Position_B);
		f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

		f_Position_B->acIntegerPosition(f_LoadInteger);

		if(f_Bicycle->vec_Vertex.size() >= 8)
			{
			f_Bicycle = std::make_shared<Cube::CubeBicycle>();
			f_Hesh->vec_Bicycle.push_back(f_Bicycle);
			}

#if 0
		//EOF Long Long
		if(f_Scan == false)
			{
			std::shared_ptr<BiVector> f_Position_C = std::make_shared<BiVector>(ICS_FLOAT_MAX);
			f_Bicycle->vec_Vertex.push_back(f_Position_C);
			f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

			if(f_Bicycle->vec_Vertex.size() >= 8)
				{
				f_Bicycle = std::make_shared<Cube::CubeBicycle>();
				f_Hesh->vec_Bicycle.push_back(f_Bicycle);
				}
			}
#endif
		}

	  ///////////////
	 // Resultant //
	///////////////

	char f_CharArray[32];
	sprintf(f_CharArray, "%f", m_Resultant->m_FLR); // [SAVE] m_Resultant->m_FLR

	std::string f_CharString = f_CharArray;

	int f_CharLength = f_CharString.length();

	//Double Save
	std::shared_ptr<BiVector> f_Position_R = std::make_shared<BiVector>(true);
	f_Bicycle->vec_Vertex.push_back(f_Position_R);
	f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

	if(f_Bicycle->vec_Vertex.size() >= 8)
		{
		f_Bicycle = std::make_shared<Cube::CubeBicycle>();
		f_Hesh->vec_Bicycle.push_back(f_Bicycle);
		}

	for(int f_XY = 0; f_XY < f_CharLength; f_XY++)
		{
		char f_Char = f_CharArray[f_XY];

		if(f_Char == '.')
			{
			f_Position_R->ac_ValueSet(ICS_RESULTANT_POINT);
			}
		else
			{
			float f_FloatResult = (ICS_RESULTANT_FACTOR * (f_Char - '0')) - ICS_FLOAT;

			if((f_FloatResult > -1.0f) && (f_FloatResult < 0.0f))
				{
				f_FloatResult += ICS_FLOAT_MID_SECOND;
				}
			else if(f_FloatResult >= 0.0f)
				{
				f_FloatResult += ICS_FLOAT_MID_FIRST;
				}

			f_Position_R->ac_ValueSet(f_FloatResult);
			}

		if(f_Position_R->m_Mode >= 3)
			{
			f_Position_R = std::make_shared<BiVector>(true);
			f_Bicycle->vec_Vertex.push_back(f_Position_R);
			f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

			if(f_Bicycle->vec_Vertex.size() >= 8)
				{
				f_Bicycle = std::make_shared<Cube::CubeBicycle>();
				f_Hesh->vec_Bicycle.push_back(f_Bicycle);
				}
			}

		//EOF Double
		if(f_XY == f_CharLength - 1)
			{
			f_Position_R->ac_ValueSet(ICS_RESULTANT_MAX);
			}
		}

	char f_CharArrayFloat[32];
	sprintf(f_CharArrayFloat, "%f", m_Resultant->m_FinalXLength); // [SAVE] m_Resultant->m_FinalXLength

	std::string f_CharStringFloat = f_CharArrayFloat;

	int f_CharLengthFloat = f_CharStringFloat.length();

	//Double Save
	std::shared_ptr<BiVector> f_Position_F = std::make_shared<BiVector>(true);
	f_Bicycle->vec_Vertex.push_back(f_Position_F);
	f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

	if(f_Bicycle->vec_Vertex.size() >= 8)
		{
		f_Bicycle = std::make_shared<Cube::CubeBicycle>();
		f_Hesh->vec_Bicycle.push_back(f_Bicycle);
		}

	for(int f_XY = 0; f_XY < f_CharLengthFloat; f_XY++)
		{
		char f_Char = f_CharArrayFloat[f_XY];

		if(f_Char == '.')
			{
			f_Position_F->ac_ValueSet(ICS_RESULTANT_POINT);
			}
		else
			{
			float f_FloatResult = (ICS_RESULTANT_FACTOR * (f_Char - '0')) - ICS_FLOAT;

			if((f_FloatResult > -1.0f) && (f_FloatResult < 0.0f))
				{
				f_FloatResult += ICS_FLOAT_MID_SECOND;
				}
			else if(f_FloatResult >= 0.0f)
				{
				f_FloatResult += ICS_FLOAT_MID_FIRST;
				}

			f_Position_F->ac_ValueSet(f_FloatResult);
			}

		if(f_Position_F->m_Mode >= 3)
			{
			f_Position_F = std::make_shared<BiVector>(true);
			f_Bicycle->vec_Vertex.push_back(f_Position_F);
			f_Bicycle->vec_Color.push_back(std::make_shared<BiVector>(random(), random(), random()));

			if(f_Bicycle->vec_Vertex.size() >= 8)
				{
				f_Bicycle = std::make_shared<Cube::CubeBicycle>();
				f_Hesh->vec_Bicycle.push_back(f_Bicycle);
				}
			}

		//EOF Float
		if(f_XY == f_CharLengthFloat - 1)
			{
			f_Position_F->ac_ValueSet(ICS_RESULTANT_MAX);
			}
		}

	//win conditions!
	return f_Hesh;
}

//element level specify schema
bool classTarget_Ecom::ac_ICS_takeMeasurementBLTV1(int f_Cap)  // scale resolution 1-3
{
	return m_LibraryID->m_Resultant->acReceive_BLTV1();
}

bool classLMap::ac_ICS_takeMeasurementBLTV1(shared_ptr<classElement> f_Vertex, int f_OCSCP_ThreadIndex)  // scale resolution 1-3
{
#ifdef SCP_REFLECT
	std::string f_ref_CurrentPath = "classLMap::ac_ICS_takeMeasurementBLTV1";
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

std::string ag_ICS_NameStamp(std::string f_Measurement, int f_Type, int f_BitCount)
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