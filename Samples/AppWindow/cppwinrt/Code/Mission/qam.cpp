/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "qam.h"

#ifndef ECOIN

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"
#include "Q-WE-BulletSystem.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-CloudControl.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-NNbot.h"

#include "Q-NET-ProtoMap.h"

using namespace GVARS;
#endif

using namespace ecoin;

namespace ecoin
{

QAM* g_QAM = nullptr;

int g_QamID = 0;

QAM_NameGroup g_NameGroup[512];
int g_current_NameGroup = 0;

int g_QamStatus = 0;

std::vector<ecoin::QamRefList*> g_RefList;

QAM::QAM(int f_QamID)
{
	std::string f_ref_CurrentPath = "QAM::QAM";

	acClear();

	//g_VoxMuti.ac_Fire();

	m_qamid = f_QamID;
	m_LevelCurrent = 0;

	int f_Int = 1;

#if 0
	if(!g_SafeL[2])
		{
		ag_StatusLive(f_ref_CurrentPath, "g_SafeL[2]");
		g_SafeL[2] = std::make_shared_reflect<icSafeL>(2);
		g_SafeL[2]->Initialize();

		f_Int = g_SafeL[2]->Connect();
		printf("Connected to ecoin server...\n");
		}
#endif

	if(f_Int)
		{
		//Build the query
		char* f_qamquery = new char[250];
		sprintf(f_qamquery, "SELECT id, qaccountid, name, author, description, keywords, features, featid, price, levelcount FROM qam WHERE id = %i", f_QamID);

		mutex_qcomdb.lock();

		g_SafeL[2]->acSelectCommand(f_qamquery, false, false);

		delete[] f_qamquery;

		if(g_Schedular[2]->acEntrySize())
			{
			m_qaccountid = ::atoi(g_Schedular[2]->acEntry(0)[1].c_str());
			m_Name = g_Schedular[2]->acEntry(0)[2];
			m_Author = g_Schedular[2]->acEntry(0)[3];
			m_Description = g_Schedular[2]->acEntry(0)[4];
			m_Keywords = g_Schedular[2]->acEntry(0)[5];
			m_Features = g_Schedular[2]->acEntry(0)[6];
			m_FeaturedIndex = ::atoi(g_Schedular[2]->acEntry(0)[7].c_str());
			m_LevelCount = ::atoi(g_Schedular[2]->acEntry(0)[9].c_str());
			m_evalue = atof(g_Schedular[2]->acEntry(0)[8].c_str());
			m_ECN = g_Schedular[2]->acEntry(0)[8];
			}

		mutex_qcomdb.unlock();
		}

#if 0
	char* f_terrainquery = new char[250];
	sprintf(f_terrainquery, "SELECT id FROM qamterrain WHERE qamid = %i", m_qamid);
	g_SafeL[2]->acSelectCommand(f_terrainquery, false, false);
	delete[] f_terrainquery;

	int f_TerrainCount = g_Schedular[2]->acEntrySize();

	if(f_TerrainCount > 0)
		{
		int f_GrentIndex = g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1);

		for(int f_Count = 0; f_Count < f_TerrainCount; f_Count++)
			{
			std::string f_String = g_Schedular[2]->acEntryIndex(f_GrentIndex, f_Count)[0];
			int f_Int = ::atoi(f_String.c_str());
			m_vec_Terrain.push_back(new qamTerrain(f_Int));
			}
		}
#endif

	//g_VoxMuti.ac_Free();

	ac_LoadAll();

	g_QamStatus = QAM_STATUS_LOADED;

#ifndef OSI_MEM_APP
	ac_Push(m_LevelCount, f_ref_CurrentPath + g_ref_Div + "m_LevelCount");
	ac_Push(m_LevelCurrent, f_ref_CurrentPath + g_ref_Div + "m_LevelCurrent");
	ac_Push(m_qamid, f_ref_CurrentPath + g_ref_Div + "m_qamid");
	ac_Push(m_qaccountid, f_ref_CurrentPath + g_ref_Div + "m_qaccountid");

	ac_Push(m_Name, f_ref_CurrentPath + g_ref_Div + "m_Name");
	ac_Push(m_Description, f_ref_CurrentPath + g_ref_Div + "m_Description");
	ac_Push(m_Author, f_ref_CurrentPath + g_ref_Div + "m_Author");
	ac_Push(m_Keywords, f_ref_CurrentPath + g_ref_Div + "m_Keywords");
	ac_Push(m_Features, f_ref_CurrentPath + g_ref_Div + "m_Features");

	ac_Push(m_FeaturedIndex, f_ref_CurrentPath + g_ref_Div + "m_FeaturedIndex");
	ac_Push(m_evalue, f_ref_CurrentPath + g_ref_Div + "m_evalue");
	ac_Push(m_ECN, f_ref_CurrentPath + g_ref_Div + "m_ECN");
	ac_Push(m_Save, f_ref_CurrentPath + g_ref_Div + "m_Save");

	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acClear", (void(ecom_base::*)(void))&QAM::acClear);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_Save", (bool(ecom_base::*)(void))&QAM::ac_Save);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_LoadAll", (bool(ecom_base::*)(void))&QAM::ac_LoadAll);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "ac_SaveAll", (bool(ecom_base::*)(void))&QAM::ac_SaveAll);
#endif
}

QAM* ag_LoadBrief(int f_QamID)
{
	QAM* f_QAM = new QAM();
	f_QAM->acClear();

	//g_VoxMuti.ac_Fire();

	f_QAM->m_qamid = f_QamID;
	f_QAM->m_LevelCurrent = 0;

	//Build the query
	char* f_qamquery = new char[250];
	sprintf(f_qamquery, "SELECT id, qaccountid, name, author, description, keywords, features, featid, price, levelcount FROM qam WHERE id = %i", f_QamID);

	mutex_qcomdb.lock();

	g_SafeL[2]->acSelectCommand(f_qamquery, false, false);

	delete[] f_qamquery;

	if(g_Schedular[2]->acEntrySize())
		{
		f_QAM->m_qaccountid = ::atoi(g_Schedular[2]->acEntry(0)[1].c_str());
		f_QAM->m_Name = g_Schedular[2]->acEntry(0)[2];
		f_QAM->m_Author = g_Schedular[2]->acEntry(0)[3];
		f_QAM->m_Description = g_Schedular[2]->acEntry(0)[4];
		f_QAM->m_Keywords = g_Schedular[2]->acEntry(0)[5];
		f_QAM->m_Features = g_Schedular[2]->acEntry(0)[6];
		f_QAM->m_FeaturedIndex = ::atoi(g_Schedular[2]->acEntry(0)[7].c_str());
		f_QAM->m_LevelCount = ::atoi(g_Schedular[2]->acEntry(0)[9].c_str());
		f_QAM->m_evalue = atof(g_Schedular[2]->acEntry(0)[8].c_str());
		f_QAM->m_ECN = g_Schedular[2]->acEntry(0)[8];
		}

	//g_VoxMuti.ac_Free();

	mutex_qcomdb.unlock();

	return f_QAM;
}

void QAM::ac_LoadAll(void)
{
	//g_VoxMuti.ac_Fire();

	char* f_terrainquery = new char[250];
	sprintf(f_terrainquery, "SELECT id FROM qamterrain WHERE qamid=%i", m_qamid);

	mutex_qcomdb.lock();

	g_SafeL[2]->acSelectCommand(f_terrainquery, false, false);
	delete[] f_terrainquery;

	int f_TerrainCount = g_Schedular[2]->acEntrySize();

	if(f_TerrainCount > 0)
		{
		int f_GrentIndex = g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1);
		for(int f_Count = 0; f_Count < f_TerrainCount; f_Count++)
			{
			std::string f_String = g_Schedular[2]->acEntryIndex(f_GrentIndex, f_Count)[0];
			int f_Int = ::atoi(f_String.c_str());
			m_vec_Terrain.push_back(new qamTerrain(f_Int));
			}
		}

	char* f_triggerquery = new char[250];
	sprintf(f_triggerquery, "SELECT id FROM qamtrigger WHERE qamid=%i", m_qamid);
	g_SafeL[2]->acSelectCommand(f_triggerquery, false, false);
	delete[] f_triggerquery;

	int f_TriggerCount = g_Schedular[2]->acEntrySize();

	if(f_TriggerCount > 0)
		{
		int f_GrentIndex = g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1);
		for(int f_Count = 0; f_Count < f_TriggerCount; f_Count++)
			{
			qamTrigger* f_Trigger = new qamTrigger(::atoi(g_Schedular[2]->acEntryIndex(f_GrentIndex, f_Count)[0].c_str()));
				
			m_vec_Trigger.push_back(f_Trigger);
			}
		}

	char* f_spawnquery = new char[250];
	sprintf(f_spawnquery, "SELECT id FROM qamspawn WHERE qamid=%i", m_qamid);
	g_SafeL[2]->acSelectCommand(f_spawnquery, false, false);
	delete[] f_spawnquery;

	int f_SpawnCount = g_Schedular[2]->acEntrySize();

	if(f_SpawnCount > 0)
		{
		int f_GrentIndex = g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1);
		for(int f_Count = 0; f_Count < f_SpawnCount; f_Count++)
			{
			qamSpawn* f_Spawn = new qamSpawn(::atoi(g_Schedular[2]->acEntryIndex(f_GrentIndex, f_Count)[0].c_str()));
				
			m_vec_Spawn.push_back(f_Spawn);
			}
		}

#if 0
	char* f_eventquery = new char[250];
	sprintf(f_eventquery, "SELECT id FROM qamevent WHERE qamid=%i", m_qamid);
	g_SafeL[2]->acSelectCommand(f_eventquery, false, false);
	delete[] f_eventquery;

	int f_EventCount = g_Schedular[2]->acEntrySize();

	if(f_EventCount > 0)
		{
		int f_GrentIndex = g_Schedular[2]->ac_GetEntry(g_Schedular[2]->m_Entries.size() - 1);
		for(int f_Count = 0; f_Count < f_EventCount; f_Count++)
			{
			qamEvent* f_Event = new qamEvent(::atoi(g_Schedular[2]->acEntryIndex(f_GrentIndex, f_Count)[0].c_str()));

			m_vec_Event.push_back(f_Event);
			}
		}
#endif

	mutex_qcomdb.unlock();

#if 0
	g_VoxMuti.ac_Free();
#endif
}

void QAM::ac_SaveAll(void)
{
	int f_TerrainCount = m_vec_Terrain.size();

	if(f_TerrainCount > 0)
		{
		for(int f_Count = 0; f_Count < f_TerrainCount; f_Count++)
			{
			qamTerrain* f_Terrain = m_vec_Terrain[f_Count];

			f_Terrain->ac_Save();
			}
		}
}

void QAM::acClear(void)
{
	m_vec_Trigger.clear();
	m_vec_Spawn.clear();
	m_vec_Event.clear();
	m_LevelCount = 1;
	m_LevelCurrent = 0;
	m_qamid = -1551;
	m_qaccountid = g_QAccountID;
	m_Name.clear();
	m_Description.clear();
	m_Author.clear();
	m_Keywords.clear();
	m_Features.clear();
	m_FeaturedIndex = 5;
	m_evalue = 0.0f;
	m_ECN.clear();
	m_Save = false;
}

void QAM::acPrep_Launch(void)
{
	for(int f_Jet = 0; f_Jet < m_vec_Trigger.size(); f_Jet++)
		{
		m_vec_Trigger[f_Jet]->acClear();
		}

	for(int f_Jet = 0; f_Jet < m_vec_Spawn.size(); f_Jet++)
		{
		m_vec_Spawn[f_Jet]->acPrep_Launch();
		}

	for(int f_Jet = 0; f_Jet < m_vec_Event.size(); f_Jet++)
		{
		m_vec_Event[f_Jet]->acClear();
		}

	m_LevelCurrent = 0;
}

void QAM::ac_Save(void)
{
	if(m_qamid == -1551)
		{
		char* f_qamfield[9];
		char* f_qamvalue[9];

		for(int f_Count = 0; f_Count < 9; f_Count++)
			{
			f_qamfield[f_Count] = (char*)malloc(sizeof(char) * 512);
			f_qamvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
			}

		sprintf(f_qamfield[0], "qaccountid");
		sprintf(f_qamfield[1], "name");
		sprintf(f_qamfield[2], "author");
		sprintf(f_qamfield[3], "description");
		sprintf(f_qamfield[4], "keywords");
		sprintf(f_qamfield[5], "features");
		sprintf(f_qamfield[6], "featid");
		sprintf(f_qamfield[7], "levelcount");
		sprintf(f_qamfield[8], "price");

		sprintf(f_qamvalue[0], "%i", g_QAccountID);
		sprintf(f_qamvalue[3], "%s", m_Description.c_str());
		sprintf(f_qamvalue[4], "%s", m_Keywords.c_str());
		sprintf(f_qamvalue[5], "%s", m_Features.c_str());
		sprintf(f_qamvalue[6], "%i", m_FeaturedIndex);
		sprintf(f_qamvalue[7], "%i", m_LevelCount);
		sprintf(f_qamvalue[8], "%f", m_evalue);

		  ////////////////
		 //
		// default
		if(m_Save == false)
			{
			sprintf(f_qamvalue[1], "QMission");

#ifdef UNIFICATION
			sprintf(f_qamvalue[2], "%s", g_QA_Username.c_str());
#else
			sprintf(f_qamvalue[2], "%s", "ECOMCLIENT");
#endif
			}
		else
			{
			sprintf(f_qamvalue[1], "%s", m_Name.c_str());
			sprintf(f_qamvalue[2], "%s", m_Author.c_str());
			}

#if 0
		mutex_qcomdb.lock();
#endif

		int f_QamUniqueID = g_SafeL[2]->Insert("qam", (const char **)f_qamfield, (const char **)f_qamvalue, 9, false, false);

		for(int f_Count = 0; f_Count < 9; f_Count++)
			{
			free(f_qamfield[f_Count]);
			free(f_qamvalue[f_Count]);
			}

#if 0
		mutex_qcomdb.unlock();
#endif

		m_qamid = f_QamUniqueID;
		}
	else
		{
		if(m_Save)
			{
			char* f_qamfield[9];
			char* f_qamvalue[9];
			char* f_qamwhere[1];

			for(int f_Count = 0; f_Count < 9; f_Count++)
				{
				f_qamfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_qamvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_qamwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_qamfield[0], "qaccountid");
			sprintf(f_qamfield[1], "name");
			sprintf(f_qamfield[2], "author");
			sprintf(f_qamfield[3], "description");
			sprintf(f_qamfield[4], "keywords");
			sprintf(f_qamfield[5], "features");
			sprintf(f_qamfield[6], "featid");
			sprintf(f_qamfield[7], "levelcount");
			sprintf(f_qamfield[8], "price");

			  ////////////////
			 //
			// skip
			sprintf(f_qamvalue[1], "%s", m_Name.c_str());
			sprintf(f_qamvalue[2], "%s", m_Author.c_str());
			sprintf(f_qamvalue[0], "%i", g_QAccountID);
			sprintf(f_qamvalue[3], "%s", m_Description.c_str());
			sprintf(f_qamvalue[4], "%s", m_Keywords.c_str());
			sprintf(f_qamvalue[5], "%s", m_Features.c_str());
			sprintf(f_qamvalue[6], "%i", m_FeaturedIndex);
			sprintf(f_qamvalue[7], "%i", m_LevelCount);
			sprintf(f_qamvalue[8], "%f", m_evalue);

			sprintf(f_qamwhere[0], "id = %i", m_qamid);

#if 0
			mutex_qcomdb.lock();
#endif

			g_SafeL[2]->Update("qam", (const char **)f_qamfield, (const char **)f_qamvalue, 1, f_qamwhere[0], false, false);

#if 0
			mutex_qcomdb.unlock();
#endif

			for(int f_Count = 0; f_Count < 9; f_Count++)
				{
				free(f_qamfield[f_Count]);
				free(f_qamvalue[f_Count]);
				}

			free(f_qamwhere[0]);

			m_Save = false;
			}
		}
}

bool QAM::ac_Frame(void)
{
	bool f_Result = true;

	for(int f_Int = 0; f_Int < m_vec_Trigger.size(); f_Int++)
		{
		qamTrigger* f_Trigger = m_vec_Trigger[f_Int];

		f_Trigger->ac_Compute();
		}

	for(int f_Int = 0; f_Int < m_vec_Spawn.size(); f_Int++)
		{
		qamSpawn* f_Spawn = m_vec_Spawn[f_Int];

		f_Spawn->ac_Compute();
		}

	for(int f_Int = 0; f_Int < m_vec_Event.size(); f_Int++)
		{
		qamEvent* f_Event = m_vec_Event[f_Int];

		f_Event->ac_Compute();
		}

	return f_Result;
}

bool QAM::ac_Search_NameGroup(Condition_Element* f_CE)
{
	bool f_bool_Result = false;
	return f_bool_Result;
}

bool QAM::ac_MapVar(Condition_Element* f_CE)
{
	bool f_bool_Result = false;

	if(f_CE->m_vec_NameGroup[0].compare("player"))
		{	//Integer
		if(f_CE->m_vec_Int.size() > 0)
			{
			switch(f_CE->m_vec_Condition[0])
				{
				case '>':
					{
					if(f_CE->m_vec_NameGroup[0].compare("HB_Health"))
						{
						//if(player[f_CE->m_vec_Index[0]]->HB_Health > f_CE->m_vec_Int[0])
						//	{
						//	f_bool_Result = true;
						//	}
						}
					}
				}
			}
		}

	return f_bool_Result;
}

void QAM::ac_Command_NameGroup(Command_Element* f_CE)
{
	bool f_bool_Result = false;
}

void QAM::ac_MapVar_Command(Command_Element* f_CE)
{
	bool f_bool_Result = false;
}

void QamRefList::acGatherReferences(int f_qamTYPE, int f_ID)
{
	acClear();

	int f_GlyphCount = 0;

	switch(f_qamTYPE)
		{
		case qamTYPE_Trigger:	//TEST for trigger id
			{
			for(int f_Int = 0; f_Int < g_QAM->m_vec_Spawn.size(); f_Int++)
				{
				qamSpawn* f_Qtk = g_QAM->m_vec_Spawn[f_Int];

				if(f_Qtk->m_TriggerID == f_ID)
					{
					m_vec_Spawn.push_back(f_Qtk);
					}
				}

			for(int f_Int = 0; f_Int < g_QAM->m_vec_Event.size(); f_Int++)
				{
				qamEvent* f_Qtk = g_QAM->m_vec_Event[f_Int];

				if(f_Qtk->m_TriggerID == f_ID)
					{
					m_vec_Event.push_back(f_Qtk);
					}
				}

			for(int f_Int = 0; f_Int < g_QAM->m_vec_Function.size(); f_Int++)
				{
				qamFunction* f_Qtk = g_QAM->m_vec_Function[f_Int];

				//if(f_Qtk->m_TriggerID == f_ID)
				//	{
				//	m_vec_Function.push_back(f_Qtk);
				//	}
				}

			for(int f_Int = 0; f_Int < g_QAM->m_vec_Variable.size(); f_Int++)
				{
				qamVariable* f_Qtk = g_QAM->m_vec_Variable[f_Int];

				//if(f_Qtk->m_TriggerID == f_ID)
				//	{
				//	m_vec_Variable.push_back(f_Qtk);
				//	}
				}

			for(int f_Int = 0; f_Int < g_QAM->m_vec_Trigger.size(); f_Int++)
				{
				qamTrigger* f_Qtk = g_QAM->m_vec_Trigger[f_Int];

				if(f_Qtk->m_ParentTriggerID == f_ID)
					{
					m_vec_Trigger.push_back(f_Qtk);
					}
				}
			}break;
		}
}

};