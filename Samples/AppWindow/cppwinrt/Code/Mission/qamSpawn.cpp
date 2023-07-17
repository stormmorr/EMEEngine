/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Include/Cube.h"

#include "qam.h"

#if 0
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
#endif

using namespace ecoin;

namespace ecoin
{

qamSpawn::qamSpawn(int f_ID) : qamType(qamTYPE_Spawn)
{
	std::string f_ref_CurrentPath = "qamSpawn::qamSpawn";

	acClear();

	m_ID = f_ID;

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
		char* f_spawnquery = new char[250];
		sprintf(f_spawnquery, "SELECT id, x, y, z, qtype, qrepeat, triggerid, charid, boosthealth, boostconstitution, boostdamage, boostfocus, boostjink, qamlevel, qamid, namegroup, team, xrot, yrot, zrot FROM qamspawn WHERE id=%i", f_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->acSelectCommand(f_spawnquery, false, false);
		delete[] f_spawnquery;

		if(g_Schedular[2]->acEntrySize())
			{
			m_X = atof(g_Schedular[2]->acEntry(0)[1].c_str());
			m_Y = atof(g_Schedular[2]->acEntry(0)[2].c_str());
			m_Z = atof(g_Schedular[2]->acEntry(0)[3].c_str());

			m_Type = ::atoi(g_Schedular[2]->acEntry(0)[4].c_str());
			m_Repeat = ::atoi(g_Schedular[2]->acEntry(0)[5].c_str());

			m_TriggerID = ::atoi(g_Schedular[2]->acEntry(0)[6].c_str());
			m_CharID = ::atoi(g_Schedular[2]->acEntry(0)[7].c_str());

			boosthealth = ::atoi(g_Schedular[2]->acEntry(0)[8].c_str());
			boostconstitution = ::atoi(g_Schedular[2]->acEntry(0)[9].c_str());
			boostdamage = ::atoi(g_Schedular[2]->acEntry(0)[10].c_str());
			boostfocus = ::atoi(g_Schedular[2]->acEntry(0)[11].c_str());
			boostjink = ::atoi(g_Schedular[2]->acEntry(0)[12].c_str());

			m_QamLevel = ::atoi(g_Schedular[2]->acEntry(0)[8].c_str());
			m_QamID = ::atoi(g_Schedular[2]->acEntry(0)[9].c_str());
			m_NameGroup = g_Schedular[2]->acEntry(0)[10];

			m_Team = ::atoi(g_Schedular[2]->acEntry(0)[16].c_str());

			m_Xrot = atof(g_Schedular[2]->acEntry(0)[17].c_str());
			m_Yrot = atof(g_Schedular[2]->acEntry(0)[18].c_str());
			m_Zrot = atof(g_Schedular[2]->acEntry(0)[19].c_str());
			}

		mutex_qcomdb.unlock();
		}
}

void qamSpawn::ac_Compute(void)
{
	if(mev_Spawn_Count < m_Repeat)
		{
		if(m_Type == QAM_SPAWN_TYPE_UPON_DISCOVERY)
			{
			Cube::BiVector f_Central(m_X, m_Y, m_Z);
			Cube::BiVector f_ForceVec = f_Central;// -Cube::BiVector(player[0]->Xform.Translation.x, player[0]->Xform.Translation.y, player[0]->Xform.Translation.z);

			float f_ForceFac = f_ForceVec.acLength();

			///////////////////
			// Sphere Test
			//
			if(f_ForceFac <= 65.5f)
				{
				ac_Spawn();
				}
			}
		else if(m_Type == QAM_SPAWN_TYPE_TRIGGER)
			{
			for(int f_Int = 0; f_Int < g_QAM->m_vec_Trigger.size(); f_Int++)
				{
				qamTrigger* f_Trigger = g_QAM->m_vec_Trigger[f_Int];

				if(f_Trigger->m_ID == m_TriggerID)
					{
					ac_Spawn();
					}
				}
			}
		else if(m_Type == QAM_SPAWN_TYPE_START_ACTIVE)
			{
			for(int f_Int = 0; f_Int < m_Repeat; f_Int++)
				{
				ac_Spawn();
				}
			}
		}
}

void qamSpawn::ac_Spawn(void)
{
	/*SPAWN AVATAR*/
	//acSpawnAvatar(0, m_CharID, player[0]->BFO.CharDATA[m_CharID].BDataID, m_Team, QpoVec3d(m_X, m_Y, m_Z), -1, 0, false);

	mev_Spawn_Count++;
}

void qamSpawn::ac_Save(void)
{
	std::string f_ref_CurrentPath = "qamSpawn::ac_Save";

	if(m_ID == -1551)
		{
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
			char* f_spawnfield[19];
			char* f_spawnvalue[19];

			for(int f_Count = 0; f_Count < 19; f_Count++)
				{
				f_spawnfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_spawnvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			sprintf(f_spawnfield[0], "x");
			sprintf(f_spawnfield[1], "y");
			sprintf(f_spawnfield[2], "z");
			sprintf(f_spawnfield[3], "xrot");
			sprintf(f_spawnfield[4], "yrot");
			sprintf(f_spawnfield[5], "zrot");
			sprintf(f_spawnfield[6], "namegroup");
			sprintf(f_spawnfield[7], "qrepeat");
			sprintf(f_spawnfield[8], "qtype");
			sprintf(f_spawnfield[9], "triggerid");
			sprintf(f_spawnfield[10], "charid");
			sprintf(f_spawnfield[11], "boosthealth");
			sprintf(f_spawnfield[12], "boostconstitution");
			sprintf(f_spawnfield[13], "boostdamage");
			sprintf(f_spawnfield[14], "boostfocus");
			sprintf(f_spawnfield[15], "boostjink");
			sprintf(f_spawnfield[16], "qamlevel");
			sprintf(f_spawnfield[17], "qamid");
			sprintf(f_spawnfield[18], "team");
			
			sprintf(f_spawnvalue[0], "%f", m_X);
			sprintf(f_spawnvalue[1], "%f", m_Y);
			sprintf(f_spawnvalue[2], "%f", m_Z);
			sprintf(f_spawnvalue[3], "%f", m_Xrot);
			sprintf(f_spawnvalue[4], "%f", m_Yrot);
			sprintf(f_spawnvalue[5], "%f", m_Zrot);
			sprintf(f_spawnvalue[6], "%s", m_NameGroup.c_str());
			sprintf(f_spawnvalue[7], "%i", m_Repeat);
			sprintf(f_spawnvalue[8], "%i", m_Type);
			sprintf(f_spawnvalue[9], "%i", m_TriggerID);
			sprintf(f_spawnvalue[10], "%i", m_CharID);
			sprintf(f_spawnvalue[11], "%i", boosthealth);
			sprintf(f_spawnvalue[12], "%i", boostconstitution);
			sprintf(f_spawnvalue[13], "%i", boostdamage);
			sprintf(f_spawnvalue[14], "%i", boostfocus);
			sprintf(f_spawnvalue[15], "%i", boostjink);
			sprintf(f_spawnvalue[16], "%i", m_QamLevel);
			sprintf(f_spawnvalue[17], "%i", m_QamID);
			sprintf(f_spawnvalue[18], "%i", m_Team);

			int f_spawnUniqueID = g_SafeL[2]->Insert("qamspawn", (const char **)f_spawnfield, (const char **)f_spawnvalue, 19, false, false);

			m_ID = f_spawnUniqueID;
			}
		}
	else
		{
		if(m_Save)
			{
			char* f_spawnfield[19];
			char* f_spawnvalue[19];
			char* f_spawnwhere[1];

			for (int f_Count = 0; f_Count < 19; f_Count++)
				{
				f_spawnfield[f_Count] = (char*)malloc(sizeof(char) * 512);
				f_spawnvalue[f_Count] = (char*)malloc(sizeof(char) * 512);
				}

			f_spawnwhere[0] = (char*)malloc(sizeof(char) * 512);

			sprintf(f_spawnfield[0], "x");
			sprintf(f_spawnfield[1], "y");
			sprintf(f_spawnfield[2], "z");
			sprintf(f_spawnfield[3], "xrot");
			sprintf(f_spawnfield[4], "yrot");
			sprintf(f_spawnfield[5], "zrot");
			sprintf(f_spawnfield[6], "namegroup");
			sprintf(f_spawnfield[7], "repeat");
			sprintf(f_spawnfield[8], "type");
			sprintf(f_spawnfield[9], "triggerid");
			sprintf(f_spawnfield[10], "charid");
			sprintf(f_spawnfield[11], "boosthealth");
			sprintf(f_spawnfield[12], "boostconstitution");
			sprintf(f_spawnfield[13], "boostdamage");
			sprintf(f_spawnfield[14], "boostfocus");
			sprintf(f_spawnfield[15], "boostjink");
			sprintf(f_spawnfield[16], "qamlevel");
			sprintf(f_spawnfield[17], "qamid");
			sprintf(f_spawnfield[18], "team");

			sprintf(f_spawnvalue[0], "%f", m_X);
			sprintf(f_spawnvalue[1], "%f", m_Y);
			sprintf(f_spawnvalue[2], "%f", m_Z);
			sprintf(f_spawnvalue[3], "%f", m_Xrot);
			sprintf(f_spawnvalue[4], "%f", m_Yrot);
			sprintf(f_spawnvalue[5], "%f", m_Zrot);
			sprintf(f_spawnvalue[6], "%s", m_NameGroup.c_str());
			sprintf(f_spawnvalue[7], "%i", m_Repeat);
			sprintf(f_spawnvalue[8], "%i", m_Type);
			sprintf(f_spawnvalue[9], "%i", m_TriggerID);
			sprintf(f_spawnvalue[10], "%i", m_CharID);
			sprintf(f_spawnvalue[11], "%i", boosthealth);
			sprintf(f_spawnvalue[12], "%i", boostconstitution);
			sprintf(f_spawnvalue[13], "%i", boostdamage);
			sprintf(f_spawnvalue[14], "%i", boostfocus);
			sprintf(f_spawnvalue[15], "%i", boostjink);
			sprintf(f_spawnvalue[16], "%i", m_QamLevel);
			sprintf(f_spawnvalue[17], "%i", m_QamID);
			sprintf(f_spawnvalue[18], "%i", m_Team);

			sprintf(f_spawnwhere[0], "id = %i", m_ID);

			g_SafeL[2]->Update("qamspawn", (const char **)f_spawnfield, (const char **)f_spawnvalue, 19, f_spawnwhere[0], false, false);

			m_Save = false;
			}
		}
}

};