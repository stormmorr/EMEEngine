/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"
#include "Code/Musion/Code.h"
#include "qam.h"

using namespace ecoin;

namespace ecoin
{

qamEvent::qamEvent(int f_ID) : qamType(MuTYPE_Code)
{
	std::string f_ref_CurrentPath = "qamEvent::qamEvent";

	acStartClear();
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
		char* f_eventquery = new char[250];
		sprintf(f_eventquery, "SELECT id, triggerid, command FROM qamevent WHERE id=%i", f_ID);

		mutex_qcomdb.lock();

		g_SafeL[2]->acSelectCommand(f_eventquery, false, false);
		delete[] f_eventquery;

		if(g_Schedular[2]->acEntrySize())
			{
			m_TriggerID = ::atoi(g_Schedular[2]->acEntry(0)[0].c_str());
			m_Command = g_Schedular[2]->acEntry(0)[1].c_str();
			}

		mutex_qcomdb.unlock();
		}
}

bool qamEvent::ac_Process_Command(void)
{
	while(m_Int_At < m_Command.length())
		{
		Command_Element* f_CE = ac_Process_Command_Element();

		f_CE->m_qamPosition = 1;
		
		m_vec_ComElem.push_back(f_CE);
		}

	m_bool_Processed = true;

	return true;
}

Command_Element* qamEvent::ac_Process_Command_Element(void)
	{
	Command_Element* f_Con = new Command_Element();
	bool f_ScanGroup = true;
	while(f_ScanGroup)
		{
		std::string f_NameGroup;
		bool f_Scan = true;
		while(f_Scan == true)
			{
			char f_charAT = m_Command.at(m_Int_At);

			if(f_charAT != '-')
				{
				f_NameGroup.push_back(f_charAT);
				}
			else
				{
				f_Scan = false;
				}

			m_Int_At++;
			if(m_Int_At >= m_Command.length())
				{
				f_Scan = false;
				}
			}

		std::string f_string_Index;
		f_Scan = true;
		while(f_Scan == true)
			{
			char f_charAT = m_Command.at(m_Int_At);

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
			if(m_Int_At >= m_Command.length())
				{
				f_Scan = false;
				}
			}

		f_Con->add_NameGroup(f_NameGroup, ::atoi(f_string_Index.c_str()));
		}

	if(m_Int_At >= m_Command.length())
		{
		return f_Con;
		}

	char f_char_At = m_Command.at(m_Int_At);

	m_Int_At++;
	if(m_Int_At >= m_Command.length())
		{
		return f_Con;
		}

	switch(f_char_At)
		{
		case 'I':
			{
			char f_char2_At = m_Command.at(m_Int_At);

			m_Int_At++;
			if(m_Int_At >= m_Command.length())
				{
				return f_Con;
				}

			std::string f_string_Value;
			bool f_Scan = true;
			while(f_Scan == true)
				{
				char f_charAT1 = m_Command.at(m_Int_At);

				if(f_charAT1 != ':')
					{
					f_string_Value.push_back(f_charAT1);
					}
				else
					{
					f_Scan = false;
					}

				m_Int_At++;
				if(m_Int_At >= m_Command.length())
					{
					f_Scan = false;
					}
				}

			int f_Integer = ::atoi(f_string_Value.c_str());

			f_Con->add_Integer(f_Integer, f_char2_At);
			}break;

		case 'F':
			{
			char f_char2_At = m_Command.at(m_Int_At);

			m_Int_At++;
			if(m_Int_At >= m_Command.length())
				{
				return f_Con;
				}

			std::string f_string_Value;
			bool f_Scan = true;
			while(f_Scan == true)
				{
				char f_charAT1 = m_Command.at(m_Int_At);

				if(f_charAT1 != ':')
					{
					f_string_Value.push_back(f_charAT1);
					}
				else
					{
					f_Scan = false;
					}

				m_Int_At++;
				if(m_Int_At >= m_Command.length())
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

bool qamEvent::ac_Compute(void)
{
	if(!m_bool_Processed)
		{
		ac_Process_Command();
		}

	if(m_vec_ComElem.size() <= 0)
		{
		return false;
		}

	bool f_Trigger = false;
	for(int f_Int = 0; f_Int < m_vec_ComElem.size(); f_Int++)
		{
		Command_Element* f_CE = m_vec_ComElem[f_Int];

		//Internal to QAM
		if(f_CE->m_qamPosition == 1)
			{
			g_QAM->ac_Command_NameGroup(f_CE);
			}
		else//Internal to QAGE
			{
			g_QAM->ac_MapVar_Command(f_CE);
			}
		}

	return f_Trigger;
}

};