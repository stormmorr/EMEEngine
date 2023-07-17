/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.bitolyl.com/osirem bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Target.h"

using namespace ecoin;

namespace ecoin
{

classTarget::classTarget(CubeHESH* f_Hesh)
{
	m_Collection = new classCollection();
	m_Collection->acClear();

	for(int f_Count = 0; f_Count < f_Hesh->m_adIndex.size(); f_Count++)
		{
		classElement* f_Element = new classElement(f_Hesh->vec_Bicycle[f_Hesh->m_adIndex[f_Count]]);

		classResult* f_Result = f_Element->acStructuredAnalysis();

		if(f_Result->m_SurfToLegRatio > 0.17)
			{
			classSurface* f_Surface = new classSurface(f_Element);

			if(f_Result->m_LevelParent < 0)
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
				f_Result->m_Parent->m_vec_Element.push_back(f_Element);
				f_Result->m_Parent->m_vec_Surface.push_back(f_Surface);
				}
			}
		else
			{
			classLeg* f_Leg = new classLeg(f_Element);

			if(f_Result->m_LevelParent < 0)
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
				f_Result->m_Parent->m_vec_Element.push_back(f_Element);
				f_Result->m_Parent->m_vec_Leg.push_back(f_Leg);
				}
			}
		}

	for(int f_Count = 0; f_Count < f_Hesh->m_adIndex.size(); f_Count++)
		{
		classElement* f_Element = m_Collection->m_vec_Element[f_Count];

		for(int f_CountCollision = 0; f_CountCollision < f_Hesh->m_adIndex.size(); f_CountCollision++)
			{
			if(f_Count != f_CountCollision)
				{
				classElement* f_ElementCollide = m_Collection->m_vec_Element[f_CountCollision];
				
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

	for(int f_Count = 0; f_Count < f_Hesh->m_adIndex.size(); f_Count++)
		{
		classElement* f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_IsIn.size() == 1)
			{
			classElement* f_ParentElement = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]];

			f_ParentElement->m_vec_Element.push_back(f_Element);

			// Leg
			if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() >= 1)
				{
				f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
				}
			else // Surface
				{
				if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() == 0)
					{
					//Do nothing
					}
				else // Surface
					{
					if(f_Element->m_vec_Surface.size() >= 1)
						{
						f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
						}
					}
				}

			classResult* f_ParentResult = f_ParentElement->m_vec_Result[f_ParentElement->m_vec_Result.size() - 1];
			classResult* f_ElementResult = f_Element->m_vec_Result[f_ParentElement->m_vec_Result.size() - 1];

			for(int f_Coyu = 0; f_Coyu < 8; f_Coyu++)
				{
				f_ParentResult->m_vec_Corner.push_back(f_ElementResult->m_vec_Corner[f_Coyu]);
				}

			classJoint* f_Joint = new classJoint(f_ParentElement, f_Element);

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_ParentElement->m_vec_Joint.push_back(f_Joint);
			}
		else if(f_Element->m_vec_IsIn.size() > 1)
			{
			float f_Size = 0.0f;
			int f_Index = f_Count;
			if(f_Count == 0)
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[1]]->m_Volume;
				}
			else
				{
				f_Size = m_Collection->m_vec_Element[f_Element->m_vec_IsIn[0]]->m_Volume;
				}

			for(int f_CountSize = 0; f_CountSize < f_Hesh->m_adIndex.size(); f_CountSize++)
				{
				if(f_Count != f_CountSize)
					{
					classElement* f_SizeElement = m_Collection->m_vec_Element[f_CountSize];

					if(f_SizeElement->m_Volume < f_Size)
						{
						f_Size = f_SizeElement->m_Volume;
						f_Index = f_CountSize;
						}
					}
				}
			
			classElement* f_ParentElement = m_Collection->m_vec_Element[f_Index];

			f_ParentElement->m_vec_Element.push_back(f_Element);

			// Leg
			if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() >= 1)
				{
				f_ParentElement->m_vec_Leg.push_back(f_Element->m_vec_Leg[0]);
				}
			else // Surface
				{
				if(f_Element->m_vec_Surface.size() == 0 && f_Element->m_vec_Leg.size() == 0)
					{
					//Do nothing
					}
				else // Surface
					{
					if(f_Element->m_vec_Surface.size() >= 1)
						{
						f_ParentElement->m_vec_Surface.push_back(f_Element->m_vec_Surface[0]);
						}
					}
				}

			classResult* f_ParentResult = f_ParentElement->m_vec_Result[f_ParentElement->m_vec_Result.size() - 1];
			classResult* f_ElementResult = f_Element->m_vec_Result[f_ParentElement->m_vec_Result.size() - 1];

			for(int f_Coyu = 0; f_Coyu < 8; f_Coyu++)
				{
				f_ParentResult->m_vec_Corner.push_back(f_ElementResult->m_vec_Corner[f_Coyu]);
				}

			classJoint* f_Joint = new classJoint(f_ParentElement, f_Element);

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_ParentElement->m_vec_Joint.push_back(f_Joint);
			}
		}

	for(int f_Count = 0; f_Count < f_Hesh->m_adIndex.size(); f_Count++)
		{
		classElement* f_Element = m_Collection->m_vec_Element[f_Count];

		if(f_Element->m_vec_Collission.size() == 1)
			{
			classElement* f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[0]];

			classJoint* f_Joint;
			if(f_Element->m_Volume >= f_FriendlyElement->m_Volume)
				{
				f_Joint = new classJoint(f_Element, f_FriendlyElement);
				}
			else
				{
				f_Joint = new classJoint(f_FriendlyElement, f_Element);
				}

			f_Element->m_vec_Joint.push_back(f_Joint);
			f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
			}
		else if(f_Element->m_vec_Collission.size() > 1)
			{
			for(int f_CountElement = 0; f_CountElement < f_Element->m_vec_Collission.size(); f_CountElement++)
				{
				if(f_Count != f_CountElement)
					{
					classElement* f_FriendlyElement = m_Collection->m_vec_Element[f_Element->m_vec_Collission[f_CountElement]];

					classJoint* f_Joint;
					if(f_Element->m_Volume >= f_FriendlyElement->m_Volume)
						{
						f_Joint = new classJoint(f_Element, f_FriendlyElement);
						}
					else
						{
						f_Joint = new classJoint(f_FriendlyElement, f_Element);
						}

					f_Element->m_vec_Joint.push_back(f_Joint);
					f_FriendlyElement->m_vec_Joint.push_back(f_Joint);
					}
				}
			}
		}

	m_Mark = 0.0f;
}

void classTarget::acPrintStats(void)
{
	printf("classTarget Statistics");

}

bool classTarget::acCompare(classTarget* f_Target, float f_QualityRank, float f_Grade, bool f_testVolumes)
{
	 /////////////////////
	//Prime Decision
	bool f_True = true;
	if(m_Collection->m_vec_Element.size() < f_Target->m_Collection->m_vec_Element.size())
		{
		f_Target->m_Mark = 0.0f;

		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			classElement* f_Element = m_Collection->m_vec_Element[f_Count];
			classElement* f_TestElement = f_Target->m_Collection->m_vec_Element[f_Count];

			f_Target->m_Mark += f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);
			}
		}
	else
		{
		f_Target->m_Mark = 0.0f;

		for(int f_Count = 0; f_Count < m_Collection->m_vec_Element.size(); f_Count++)
			{
			float f_fakeMark = 0.0f;

			classElement* f_Element = m_Collection->m_vec_Element[f_Count];
			classElement* f_TestElement = f_Target->m_Collection->m_vec_Element[0];

			float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);
			f_fakeMark = f_Mark;

			for(int f_Cam = 0; f_Cam < f_Target->m_Collection->m_vec_Element.size(); f_Cam++)
				{
				classElement* f_Element = m_Collection->m_vec_Element[f_Count];
				classElement* f_TestElement = f_Target->m_Collection->m_vec_Element[f_Cam];

				float f_Mark = f_Element->acCompare(f_TestElement, f_QualityRank, f_testVolumes);
				if(f_Mark < f_fakeMark)
					{
					f_fakeMark = f_Mark;
					}
				}

			f_Target->m_Mark += f_fakeMark;
			}
		}

	if(f_Target->m_Mark <= f_Grade)
		{
		f_True = true;
		}
	else
		{
		f_True = false;
		}

	printf("CubeHESHGen(%i)QualityRank[%f]:Mark %f < Diff(%f)tVol=%i\n", f_True, f_QualityRank, f_Target->m_Mark, f_Grade, f_testVolumes);

	return f_True;
}

void classTarget::acGen_Humanoid(void)
{
	classElement* f_Head = new classElement(0.35f);
	classElement* f_Torso = new classElement(1.0f);
	classElement* f_Pelvis = new classElement(0.45f);
	classElement* f_RightArm = new classElement(0.35f);
	classElement* f_LeftArm = new classElement(0.35f);
	classElement* f_RightLeg = new classElement(0.55f);
	classElement* f_LeftLeg = new classElement(0.55f);

	f_Head->m_vec_Element.push_back(f_Head);
	f_Torso->m_vec_Element.push_back(f_Head);
	f_Pelvis->m_vec_Element.push_back(f_Head);
	f_RightArm->m_vec_Element.push_back(f_Head);
	f_LeftArm->m_vec_Element.push_back(f_Head);
	f_RightLeg->m_vec_Element.push_back(f_Head);
	f_LeftLeg->m_vec_Element.push_back(f_Head);

	f_Head->m_vec_Leg.push_back(new classLeg(f_Head));
	f_Torso->m_vec_Leg.push_back(new classLeg(f_Torso));
	f_Pelvis->m_vec_Leg.push_back(new classLeg(f_Pelvis));
	f_RightArm->m_vec_Leg.push_back(new classLeg(f_RightArm));
	f_LeftArm->m_vec_Leg.push_back(new classLeg(f_LeftArm));
	f_RightLeg->m_vec_Leg.push_back(new classLeg(f_RightLeg));
	f_LeftLeg->m_vec_Leg.push_back(new classLeg(f_LeftLeg));

	f_Head->m_Index = 0;
	m_Collection->m_vec_Element.push_back(f_Head);
	f_Torso->m_Index = 1;
	m_Collection->m_vec_Element.push_back(f_Torso);
	f_Pelvis->m_Index = 2;
	m_Collection->m_vec_Element.push_back(f_Pelvis);
	f_RightArm->m_Index = 3;
	m_Collection->m_vec_Element.push_back(f_RightArm);
	f_LeftArm->m_Index = 4;
	m_Collection->m_vec_Element.push_back(f_LeftArm);
	f_RightLeg->m_Index = 5;
	m_Collection->m_vec_Element.push_back(f_RightLeg);
	f_LeftLeg->m_Index = 6;
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

	m_Mark = 0.0f;
}

void classTarget::acGen_Vehicle_Ground(void)
{
	classElement* f_Base = new classElement(3.35f);
	classElement* f_Front = new classElement(1.0f);
	classElement* f_Rear = new classElement(1.45f);
	classElement* f_Top = new classElement(2.35f);
	classElement* f_LeftFrontTire = new classElement(0.35f);
	classElement* f_RightFrontTire = new classElement(0.35f);
	classElement* f_LeftRearTire = new classElement(0.35f);
	classElement* f_RightRearTire = new classElement(0.35f);

	f_Base->m_vec_Leg.push_back(new classLeg(f_Base));
	f_Front->m_vec_Leg.push_back(new classLeg(f_Front));
	f_Rear->m_vec_Leg.push_back(new classLeg(f_Rear));
	f_Top->m_vec_Leg.push_back(new classLeg(f_Top));
	f_LeftFrontTire->m_vec_Leg.push_back(new classLeg(f_LeftFrontTire));
	f_RightFrontTire->m_vec_Leg.push_back(new classLeg(f_RightFrontTire));
	f_LeftRearTire->m_vec_Leg.push_back(new classLeg(f_LeftRearTire));
	f_RightRearTire->m_vec_Leg.push_back(new classLeg(f_RightRearTire));

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
	Cube::g_Count_Muti.ac_Fire();
	Cube::g_Other_Muti.ac_Fire();
	Cube::g_Share_Muti.ac_Fire();

	int f_Int = 1;
	if(!g_SafeL)
		{
		g_SafeL = new icSafeL;
		g_SafeL->Initialize();

		f_Int = g_SafeL->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		}

	  ////////////////
	 // targets
	//
	if(f_TargetID > 0)
		{
		g_TargetID = f_TargetID;
		printf("ECN::Loading Target ID = %i", g_TargetID);

		char* elementquery;
		elementquery = (char*)malloc(sizeof(char) * 1024);

		sprintf(elementquery, "SELECT id, volume FROM element WHERE targetid = %i", g_TargetID);
		g_SafeL->acSelectCommand(elementquery, false, false);

		int f_eleCount = g_Entries[ag_GetEntry(g_Entries.size() - 1)].size();

		for(int f_EleID = 0; f_EleID < f_eleCount; f_EleID++)
			{
			classElement* f_NewElement = new classElement((float)atof(g_Entries[ag_GetEntry(g_Entries.size() - 1)][f_EleID][1].c_str()));
			f_NewElement->m_vec_Leg.push_back(new classLeg(f_NewElement));
			f_NewElement->m_Index = f_EleID;
			m_Collection->m_vec_Element.push_back(f_NewElement);
			}

		char* elindexquery;
		elindexquery = (char*)malloc(sizeof(char) * 1024);

		sprintf(elindexquery, "SELECT elementid, resultid FROM elindex WHERE targetid = %i", g_TargetID);
		g_SafeL->acSelectCommand(elindexquery, false, false);
		int f_elindexCount = g_Entries[ag_GetEntry(g_Entries.size() - 1)].size();

		for(int f_ElindexID = 0; f_ElindexID < f_elindexCount; f_ElindexID++)
			{
			classElement* f_Element = m_Collection->m_vec_Element[atoi(g_Entries[ag_GetEntry(g_Entries.size() - 1)][f_ElindexID][0].c_str())];
			classElement* f_AElement = m_Collection->m_vec_Element[atoi(g_Entries[ag_GetEntry(g_Entries.size() - 1)][f_ElindexID][1].c_str())];
			
			f_Element->m_vec_Element.push_back(f_AElement);
			f_Element->m_vec_Leg.push_back(f_AElement->m_vec_Leg[0]);
			}

		m_Mark = 0.0f;
		}

	Cube::g_Count_Muti.ac_Free();
	Cube::g_Other_Muti.ac_Free();
	Cube::g_Share_Muti.ac_Free();
}

void classTarget::acSaveCloud(std::string f_Name)
{
	Cube::g_Count_Muti.ac_Fire();
	Cube::g_Other_Muti.ac_Fire();
	Cube::g_Share_Muti.ac_Fire();

	int f_Int = 1;
	if(!g_SafeL)
		{
		g_SafeL = new icSafeL;
		g_SafeL->Initialize();

		f_Int = g_SafeL->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);
		}

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

	sprintf(g_targetfield[0], "name");
	sprintf(g_targetfield[1], "difficulty");
	sprintf(g_targetfield[2], "bckred");
	sprintf(g_targetfield[3], "bckgreen");
	sprintf(g_targetfield[4], "bckblue");

	sprintf(g_targetvalue[0], "%s", f_Name.c_str());
	sprintf(g_targetvalue[1], "%f", 89.75);
	sprintf(g_targetvalue[2], "%f", Cube::random());
	sprintf(g_targetvalue[3], "%f", Cube::random());
	sprintf(g_targetvalue[4], "%f", Cube::random());

	int f_TargetID = g_SafeL->Insert("target", (const char **)g_targetfield, (const char **)g_targetvalue, 5, false, false);

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

		sprintf(g_elementfield[0], "description");
		sprintf(g_elementfield[1], "targetid");
		sprintf(g_elementfield[2], "vert1x");
		sprintf(g_elementfield[3], "vert1y");
		sprintf(g_elementfield[4], "vert1z");
		sprintf(g_elementfield[5], "volume");

		sprintf(g_elementvalue[0], "%s", "Body Part");
		sprintf(g_elementvalue[1], "%i", f_TargetID);
		sprintf(g_elementvalue[2], "%f", 0.0f);
		sprintf(g_elementvalue[3], "%f", 0.0f);
		sprintf(g_elementvalue[4], "%f", 0.0f);
		sprintf(g_elementvalue[5], "%f", m_Collection->m_vec_Element[f_ElementID]->m_Volume);

		g_SafeL->Insert("element", (const char **)g_elementfield, (const char **)g_elementvalue, 6, false, false);
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

			sprintf(g_elindexfield[0], "targetid");
			sprintf(g_elindexfield[1], "elementid");
			sprintf(g_elindexfield[2], "resultid");

			sprintf(g_elindexvalue[0], "%i", f_TargetID);
			sprintf(g_elindexvalue[1], "%i", m_Collection->m_vec_Element[f_ElementID2]->m_Index);
			sprintf(g_elindexvalue[2], "%i", m_Collection->m_vec_Element[f_ElementID2]->m_vec_Element[f_ElementID3]->m_Index);

			g_SafeL->Insert("elindex", (const char **)g_elindexfield, (const char **)g_elindexvalue, 3, false, false);
			}
		}

	Cube::g_Count_Muti.ac_Free();
	Cube::g_Other_Muti.ac_Free();
	Cube::g_Share_Muti.ac_Free();
}

};