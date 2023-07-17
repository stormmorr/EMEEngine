/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "qam.h"

using namespace ecoin;

namespace ecoin
{

qamTrigger::qamTrigger(int f_ID) : qamType(MuTYPE_Code)
{
	std::string f_ref_CurrentPath = "qamTrigger::qamTrigger";

	acClear();
	m_ParentTriggerID = -1;
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
		char* f_eventquery = new char[250];
		sprintf(f_eventquery, "SELECT id, x, y, z, qorder, qtype, qrepeat, conditions, qamlevel, qamid, namegroup FROM qamtrigger WHERE id=%i", f_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->acSelectCommand(f_eventquery, false, false);
		delete[] f_eventquery;

		if(g_Schedular[2]->acEntrySize())
			{
			m_X = atof(g_Schedular[2]->acEntry(0)[1].c_str());
			m_Y = atof(g_Schedular[2]->acEntry(0)[2].c_str());
			m_Z = atof(g_Schedular[2]->acEntry(0)[3].c_str());

			m_Order = ::atoi(g_Schedular[2]->acEntry(0)[4].c_str());
			m_Type = ::atoi(g_Schedular[2]->acEntry(0)[5].c_str());
			m_Repeat = ::atoi(g_Schedular[2]->acEntry(0)[6].c_str());

			m_Condition = g_Schedular[2]->acEntry(0)[7].c_str();

			m_QamLevel = ::atoi(g_Schedular[2]->acEntry(0)[8].c_str());
			m_QamID = ::atoi(g_Schedular[2]->acEntry(0)[9].c_str());
			m_NameGroup = g_Schedular[2]->acEntry(0)[10];
			}

		mutex_qcomdb.unlock();
		}
}

bool qamTrigger::ac_Process_Condition(void)
{
	while(m_Int_At < m_Condition.length())
		{
		Condition_Element* f_CE = ac_Process_Condition_Element();

		f_CE->m_qamPosition = 1;
		
		m_vec_ConElem.push_back(f_CE);
		}

	m_bool_Processed = true;

	return true;
}

Condition_Element* qamTrigger::ac_Process_Condition_Element(void)
	{
	Condition_Element* f_Con = new Condition_Element();
	bool f_ScanGroup = true;
	while(f_ScanGroup)
		{
		std::string f_NameGroup;
		bool f_Scan = true;
		while(f_Scan == true)
			{
			char f_charAT = m_Condition.at(m_Int_At);

			if(f_charAT != '-')
				{
				f_NameGroup.push_back(f_charAT);
				}
			else
				{
				f_Scan = false;
				}

			m_Int_At++;
			if(m_Int_At >= m_Condition.length())
				{
				f_Scan = false;
				}
			}

		std::string f_string_Index;
		f_Scan = true;
		while(f_Scan == true)
			{
			char f_charAT = m_Condition.at(m_Int_At);

			if(f_charAT != ':' &&
			   f_charAT != '=')
				{
				f_string_Index.push_back(f_charAT);
				}
			else
				{
				f_Scan = false;

				if(f_charAT == '=')
					{
					f_ScanGroup = false;
					}
				}

			m_Int_At++;
			if(m_Int_At >= m_Condition.length())
				{
				f_Scan = false;
				}
			}

		f_Con->add_NameGroup(f_NameGroup, ::atoi(f_string_Index.c_str()));
		}

	if(m_Int_At >= m_Condition.length())
		{
		return f_Con;
		}

	char f_char_At = m_Condition.at(m_Int_At);

	m_Int_At++;
	if(m_Int_At >= m_Condition.length())
		{
		return f_Con;
		}

	switch(f_char_At)
		{
		case 'I':
			{
			char f_char2_At = m_Condition.at(m_Int_At);

			m_Int_At++;
			if(m_Int_At >= m_Condition.length())
				{
				return f_Con;
				}

			std::string f_string_Value;
			bool f_Scan = true;
			while(f_Scan == true)
				{
				char f_charAT1 = m_Condition.at(m_Int_At);

				if(f_charAT1 != ':')
					{
					f_string_Value.push_back(f_charAT1);
					}
				else
					{
					f_Scan = false;
					}

				m_Int_At++;
				if(m_Int_At >= m_Condition.length())
					{
					f_Scan = false;
					}
				}

			int f_Integer = ::atoi(f_string_Value.c_str());

			f_Con->add_Integer(f_Integer, f_char2_At);
			}break;

		case 'F':
			{
			char f_char2_At = m_Condition.at(m_Int_At);

			m_Int_At++;
			if(m_Int_At >= m_Condition.length())
				{
				return f_Con;
				}

			std::string f_string_Value;
			bool f_Scan = true;
			while(f_Scan == true)
				{
				char f_charAT1 = m_Condition.at(m_Int_At);

				if(f_charAT1 != ':')
					{
					f_string_Value.push_back(f_charAT1);
					}
				else
					{
					f_Scan = false;
					}

				m_Int_At++;
				if(m_Int_At >= m_Condition.length())
					{
					f_Scan = false;
					}
				}

			int f_Float = ::atoi(f_string_Value.c_str());

			f_Con->add_Float(f_Float, f_char2_At);
			}break;

		case ':':
			{
			return f_Con;
			}break;
		}

	return f_Con;
}

void qamTrigger::ac_Compute(void)
{
	if(!m_bool_Processed)
		{
		ac_Process_Condition();
		}

	if(m_vec_ConElem.size() > 0)
		{
		m_Trigger = false;
		for(int f_Int = 0; f_Int < m_vec_ConElem.size(); f_Int++)
			{
			Condition_Element* f_CE = m_vec_ConElem[f_Int];

			//Internal to QAM
			if(f_CE->m_qamPosition == 1)
				{
				m_Trigger = g_QAM->ac_Search_NameGroup(f_CE);
				}
			else//Internal to QAGE
				{
				m_Trigger = g_QAM->ac_MapVar(f_CE);
				}
			}
		}
}

};