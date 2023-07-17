/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAMSPAWN_H
#define QAMSPAWN_H

#include <vector>
#include <math.h>

#include "qamType.h"

#define QAM_SPAWN_TYPE_UPON_DISCOVERY 0
#define QAM_SPAWN_TYPE_TRIGGER 1
#define QAM_SPAWN_TYPE_START_ACTIVE 2

namespace ecoin
{

	class qamSpawn : public qamType
	{
	public:
		qamSpawn() : qamType(qamTYPE_Spawn) { acClear(); m_QamID = g_QamID; };
		qamSpawn(int f_ID);
		~qamSpawn() { acClear(); }

		void acClear(void)
			{
			m_NameGroup.clear();
			m_X = 0.0f;
			m_Y = 0.0f;
			m_Z = 0.0f;
			m_Xrot = 0.0f;
			m_Yrot = 0.0f;
			m_Zrot = 0.0f;
			m_Type = 1;
			m_Repeat = 1;
			m_QamLevel = 1;
			m_QamID = 1;
			m_ID = -1551;
			m_TriggerID = 0;
			m_CharID = 0;
			boosthealth = 100;
			boostconstitution = 100;
			boostdamage = 100;
			boostfocus = 100;
			boostjink = 100;
			mev_Spawn_Count = 0;
			m_Save = false;
			m_Updated = false;
			}

		void acPrep_Launch(void)
			{
			mev_Spawn_Count = 0;
			}

		void ac_Compute(void);

		void ac_Spawn(void);

		void ac_Save(void);

		int boosthealth;
		int boostconstitution;
		int boostdamage;
		int boostfocus;
		int boostjink;

		std::string m_NameGroup;

		float m_X;
		float m_Y;
		float m_Z;

		float m_Xrot;
		float m_Yrot;
		float m_Zrot;

		int m_Type;
		int m_Repeat;

		int mev_Spawn_Count;

		int m_TriggerID;
		int m_CharID;
		int m_Team;

		int m_QamLevel;
		int m_QamID;

		int m_ID;

		float m_Delay;

		bool m_Save;

		bool m_Updated;

		bool m_bool_Processed;
	};

};

#endif
