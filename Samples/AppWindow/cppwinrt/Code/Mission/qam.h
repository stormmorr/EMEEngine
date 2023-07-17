/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAM_H
#define QAM_H

#include <vector>
#include <math.h>

#include "qamType.h"
#include "qamTerrain.h"
#include "qamTrigger.h"
#include "qamVariable.h"
#include "qamFunction.h"
#include "qamSpawn.h"
#include "qamEvent.h"
#include "qamSystem.h"

#define QAM_STATUS_NULL 0
#define QAM_STATUS_LOADED 1
#define QAM_STATUS_REFRESHED 2
#define QAM_STATUS_STARTED 3
#define QAM_STATUS_PAUSED 4
#define QAM_STATUS_COMPLETE_WIN 5
#define QAM_STATUS_COMPLETE_LOSE 6

namespace ecoin
{
	class QAM_NameGroup
	{
	public:
		QAM_NameGroup() { acClear(); };
		QAM_NameGroup(int f_QamID);
		~QAM_NameGroup() { acClear(); };

		void acClear(void)
			{
			m_NameGroup.clear();
			m_NameGroup = "default ";
			m_Index = 0;
			m_currentOrder = 0;
			}

		std::string m_NameGroup;
		int m_Index;
		int m_currentOrder;
	};

	extern QAM_NameGroup g_NameGroup[512];
	extern int g_current_NameGroup;

	class QAM : public qamType
	{
	public:
		QAM() : qamType(qamTYPE_QAM) { acClear(); };
		QAM(int f_QamID);
		~QAM() { acClear(); };

		void acClear(void);

		void ac_LoadAll(void);
		void ac_SaveAll(void);

		void ac_Save(void);

		bool ac_Frame(void);

		void ac_Load_Triggers(void);
		void ac_Load_Spawn(void);
		void ac_Load_Events(void);

		void acPrep_Launch(void);

		bool ac_Search_NameGroup(Condition_Element* f_CE);
		bool ac_MapVar(Condition_Element* f_CE);

		void ac_Command_NameGroup(Command_Element* f_CE);
		void ac_MapVar_Command(Command_Element* f_CE);

		std::vector<qamTrigger*> m_vec_Trigger;
		std::vector<qamTerrain*> m_vec_Terrain;

		std::vector<qamSpawn*> m_vec_Spawn;
		std::vector<qamEvent*> m_vec_Event;

		std::vector<qamVariable*> m_vec_Variable;
		std::vector<qamFunction*> m_vec_Function;

		int m_LevelCount;
		int m_LevelCurrent;
		int m_qamid;
		int m_qaccountid;
		std::string m_Name;
		std::string m_Description;
		std::string m_Author;
		std::string m_Keywords;
		std::string m_Features;
		int m_FeaturedIndex;
		float m_evalue;
		std::string m_ECN;
		bool m_Save;
	};

	extern QAM* g_QAM;

	extern QAM* ag_LoadBrief(int f_QamID);

	extern int g_QamID;

	extern int g_QamStatus;

	class QamRefList
	{
	public:
		QamRefList()
			{
			acClear();
			}

		QamRefList(int f_qamType, int f_TriggerID)
			{
			acClear();

			acGatherReferences(f_qamType, f_TriggerID);
			}

		~QamRefList()
			{
			acClear();
			}

		void acClear()
			{
			m_vec_Spawn.clear();
			m_vec_Event.clear();
			m_vec_Function.clear();
			//m_vec_Variable.clear();
			m_vec_Trigger.clear();
			}

		int acSize()
			{
			int f_Count = 0;

			f_Count += m_vec_Spawn.size();
			f_Count += m_vec_Event.size();
			f_Count += m_vec_Function.size();
			//f_Count += m_vec_Variable.size();
			f_Count += m_vec_Trigger.size();

			return f_Count;
			}

		void acGatherReferences(int f_qamTYPE, int f_ID);

		std::vector<qamSpawn*> m_vec_Spawn;
		std::vector<qamEvent*> m_vec_Event;
		std::vector<qamFunction*> m_vec_Function;
		std::vector<std::shared_ptr<Variable>> m_vec_Variable;
		std::vector<qamTrigger*> m_vec_Trigger;
	};

	extern std::vector<ecoin::QamRefList*> g_RefList;

};

#endif