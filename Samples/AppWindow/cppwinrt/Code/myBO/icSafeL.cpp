/*

	icSafeL - SafeL Database Layer
	Copyright OSIREM (C) 2007
	bitolyl.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code/Work/Schedular.h"
#include "Code/myBO/icSafeL.h"

using namespace ecoin;

std::shared_ptr<icSafeL> g_SafeL[3];

/*******************************
 * Implementation of icSafeL *
 *******************************/

/// Constructor.
icSafeL::icSafeL(int f_Layer_INDEX)
{
	m_LID = f_Layer_INDEX;

	std::string f_ref_CurrentPath = "icSafeL::icSafeL";

#ifndef OSI_MEM_APP
#ifdef REFLECT_WORK_EXT // Management SG // if STRING_LID_PRIVS_ADDED_YET //
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand", (bool(ecom_base::*)(const char*, int, bool, bool))&icSafeL::acSelectCommand, "Empty", 0, false, false);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand_PeerGraph", (bool(ecom_base::*)(const char*, int, bool, bool))&icSafeL::acSelectCommand_PeerGraph, "Empty", 0, false, false);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand_GlobalStorageWealth", (bool(ecom_base::*)(const char*, bool)) & icSafeL::acSelectCommand_GlobalStorageWealth, "Empty", false);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acCommand", (long(ecom_base::*)(const char*, int, bool, bool, bool)) & icSafeL::acCommand, "Empty", 0, false, false, false);
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "IssueSelectCommand", (bool(ecom_base::*)(const char*, int, bool, bool)) & icSafeL::IssueSelectCommand, "Empty", 0, false, false);

#pragma message("add variable cast _V7 / _V12 / _V20")
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "acSelectCommand_PeerGraphSelect", (bool(ecom_base::*)(const char*, int, bool, int, int, int))&icSafeL::acSelectCommand_PeerGraphSelect, "Empty" 0, false, 0, 0, 0);

#if 0
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "Insert", /*(ecom_base::ControllerMethod_void)*/(ecom_base::default_argument_slicer)&icSafeL::Insert); //requires ESL 'vector'
	make_lazy(f_ref_CurrentPath + g_ref_fun_Div + "Update", /*(ecom_base::ControllerMethod_void)*/(ecom_base::default_argument_slicer)&icSafeL::Update); //requires ESL 'vector'
#endif
#endif

	ac_Push(m_LID, f_ref_CurrentPath + g_ref_fun_Div + "m_LID");
#endif
}

/// Destructor.
icSafeL::~icSafeL(void)
{
	//.
}

bool icSafeL::Wallet_Connect(void)
{
	g_Schedular[m_LID]->m_ConnectionStage = ECOIN_STAGE_PREP;

	if(m_LID == 0)
		{
		g_Schedular[m_LID]->acNet_Client_Data_Wallet_Save();
		}

	return true;
}

void Connect_Main(void)
{
	g_Schedular[0]->m_ConnectionStage = ECOIN_STAGE_PREP;
	g_Schedular[1]->m_ConnectionStage = ECOIN_STAGE_PREP;
	g_Schedular[2]->m_ConnectionStage = ECOIN_STAGE_PREP;

	if(g_SafeL[0])
		{
		g_SafeL[0]->Connect();
		}

	if(g_SafeL[1])
		{
		g_SafeL[1]->Connect();
		}

	if(g_SafeL[2])
		{
		g_SafeL[2]->Connect();
		}

	g_Schedular[0]->m_ConnectionStage = ECOIN_STAGE_FIRST;
	g_Schedular[1]->m_ConnectionStage = ECOIN_STAGE_FIRST;
	g_Schedular[2]->m_ConnectionStage = ECOIN_STAGE_FIRST;

	if(g_SafeL[0])
		{
		g_SafeL[0]->Connect();
		}

	if(g_SafeL[1])
		{
		g_SafeL[1]->Connect();
		}

	if(g_SafeL[2])
		{
		g_SafeL[2]->Connect();
		}

	g_Schedular[0]->m_ConnectionStage = ECOIN_STAGE_CONNECTED;
	g_Schedular[1]->m_ConnectionStage = ECOIN_STAGE_CONNECTED;
	g_Schedular[2]->m_ConnectionStage = ECOIN_STAGE_CONNECTED;
}

void icSafeL::Connect(void)
{
	if(m_LID == 0)
		{
		if(g_Schedular[m_LID]->m_ConnectionStage == ECOIN_STAGE_PREP)
			{
			g_Schedular[m_LID]->acNet_Client_Data_Prep();
			}
		else
			{
			g_Schedular[m_LID]->acNet_Client_Data();
			}
		}
	else if(m_LID == 1)
		{
		if(g_Schedular[m_LID]->m_ConnectionStage == ECOIN_STAGE_PREP)
			{
			g_Schedular[m_LID]->acNet_Client_Data_Gui_Prep();
			}
		else
			{
			g_Schedular[m_LID]->acNet_Client_Data_Gui();
			}
		}
	else
		{
		if(g_Schedular[m_LID]->m_ConnectionStage == ECOIN_STAGE_PREP)
			{
			g_Schedular[m_LID]->acNet_Client_Data_Angel_Prep();
			}
#ifndef QUANTUM_PUSH_THREADS
		else if(g_Schedular[m_LID]->m_ConnectionStage == ECOIN_STAGE_FIRST)
			{
			g_Schedular[m_LID]->acNet_Client_Mainstream_Angel();
			}
#else
		else
			{
			g_Schedular[m_LID]->acNet_Client_Data_Angel();
			}
#endif
		}
}

long icSafeL::acCommand(const char *cmd, int f_UI, bool f_End, bool f_Update, bool f_Mtx_Ext_ON)
{
	fflush (stdout);

	if(m_LID < 2)
		{
		if(f_Update == true)
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		else
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		}
	else
		{
		if(f_Update)
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		else
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD_Angel((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		}

	return true;
}

long icSafeL::acMainstreamCommand(const char *cmd, int f_UI, bool f_End, bool f_Update, bool f_Mtx_Ext_ON)
{
	fflush (stdout);

	if(m_LID == 2)
		{
		if(f_Update)
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD_Mainstream((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD_Mainstream((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		else
			{
			if(!g_Schedular[m_LID]->acSend_Query_CMD_Mainstream((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_CMD_Mainstream((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		}

	return true;
}

long icSafeL::acWallet_Command(const char *cmd, int f_UI, bool f_End, bool f_Update, bool f_Mtx_Ext_ON)
{
	fflush (stdout);

	if(m_LID < 2)
		{
		if(f_Update == true)
			{
			if(!g_Schedular[m_LID]->acSend_Query_Wallet_CMD((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_Wallet_CMD((char *)cmd, f_UI, f_End, true, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		else
			{
			if(!g_Schedular[m_LID]->acSend_Query_Wallet_CMD((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				fflush (stdout);

				//if it fails once try again as it should re-connect
				if(!g_Schedular[m_LID]->acSend_Query_Wallet_CMD((char *)cmd, f_UI, f_End, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
					{
					return false;
					}
				}
			}
		}

	return true;
}

bool icSafeL::acSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	IssueSelectCommand (cmd, f_UI, f_End, f_Mtx_Ext_ON);

	return true;
}

bool icSafeL::acMainstreamSelectCommand(const char* cmd, bool f_Mtx_Ext_ON)
{
	MainstreamIssueSelectCommand(cmd, f_Mtx_Ext_ON);

	return true;
}

bool icSafeL::acWallet_SelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	Wallet_IssueSelectCommand(cmd, f_UI, f_End, f_Mtx_Ext_ON);

	return true;
}

bool icSafeL::acKeepAliveCommand(const char* cmd, bool f_Mtx_Ext_ON)
{
	IssueKeepAliveCommand(cmd, f_Mtx_Ext_ON);

	return true;
}

bool icSafeL::acSelectCommand_PeerGraph(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	if(!g_Schedular[m_LID]->acSend_Query_PeerGraph((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))
		{
		if(!g_Schedular[m_LID]->acSend_Query_PeerGraph((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))
			{
			return false;
			}
		}

	return true;
}

bool icSafeL::acSelectCommand_PeerGraphSelect(const char* cmd, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_Mtx_Ext_ON)
{
	if(!g_Schedular[m_LID]->acSend_Query_PeerGraphSelect((char *)cmd, f_UI, f_End, f_ShareID, f_ShareOffset, f_PEER, f_Mtx_Ext_ON))
		{
		if(!g_Schedular[m_LID]->acSend_Query_PeerGraphSelect((char *)cmd, f_UI, f_End, f_ShareID, f_ShareOffset, f_PEER, f_Mtx_Ext_ON))
			{
			return false;
			}
		}

	return true;
}

bool icSafeL::acSelectCommand_GlobalStorageWealth(const char* cmd, bool f_Mtx_Ext_ON)
{
	if(!g_Schedular[m_LID]->acSend_Query_GlobalStorageWealth((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
		{
		//if command fails first time, try again - it should re-connect
		if(!g_Schedular[m_LID]->acSend_Query_GlobalStorageWealth((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			return false;
			}
		}

	return true;
}

bool icSafeL::IssueSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	if(m_LID < 2)
		{
		if(!g_Schedular[m_LID]->acSend_Query((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_Query((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}
	else
		{
		if(!g_Schedular[m_LID]->acSend_Query_Angel((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_Query_Angel((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}

	return true;
}

bool icSafeL::MainstreamIssueSelectCommand(const char* cmd, bool f_Mtx_Ext_ON)
{
	if(m_LID == 2)
		{
		if(!g_Schedular[m_LID]->acSend_Query_Mainstream((char *)cmd, 0, false, f_Mtx_Ext_ON))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_Query_Mainstream((char *)cmd, 0, false, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}

	return true;
}

bool icSafeL::Wallet_IssueSelectCommand(const char* cmd, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	if(m_LID < 2)
		{
		if(!g_Schedular[m_LID]->acSend_Wallet_Query((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_Wallet_Query((char *)cmd, f_UI, f_End, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}

	return true;
}

bool icSafeL::IssueKeepAliveCommand(const char* cmd, bool f_Mtx_Ext_ON)
{
	if(m_LID < 2)
		{
		if(!g_Schedular[m_LID]->acSend_KeepAlive((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_KeepAlive((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}
	else
		{
		if(!g_Schedular[m_LID]->acSend_KeepAlive_Angel((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
			{
			//if command fails first time, try again - it should re-connect
			if(!g_Schedular[m_LID]->acSend_KeepAlive_Angel((char *)cmd, f_Mtx_Ext_ON))// (connection, cmd, strlen (cmd)))
				{
				return false;
				}
			}
		}

	return true;
}

unsigned int icSafeL::Insert(const char *table, const char **fields, const char **values, int fieldcount, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[65535];
    int i;

	sprintf(cmd, "INSERT INTO %s (", table);

    for (i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ", ");
        strcat(cmd, fields[i]);
		}

	strcat(cmd, ") VALUES (");

    for(i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ",");
        if(values[i] != NULL)
			{
			strcat(cmd, "'");
            strcat(cmd, values[i]);
            strcat(cmd, "'");
			}
        else
			{
            strcat (cmd, "NULL");
			}
		}

    strcat(cmd, ")");

	//Do the SQL
    if(acCommand(cmd, f_UI, f_End, false, f_Mtx_Ext_ON) == -1)
        return 0;

    return atoi(g_Schedular[m_LID]->acEntry(0)[0].c_str());
}

unsigned int icSafeL::Mainstream_Insert(const char *table, const char **fields, const char **values, int fieldcount, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[65535];
    int i;

	sprintf(cmd, "INSERT INTO %s (", table);

    for (i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ", ");

        strcat(cmd, fields[i]);
		}

	strcat(cmd, ") VALUES (");

    for(i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ",");

        if(values[i] != NULL)
			{
			strcat(cmd, "'");
            strcat(cmd, values[i]);
            strcat(cmd, "'");
			}
        else
			{
            strcat (cmd, "NULL");
			}
		}

    strcat(cmd, ")");

	//Do the SQL
    if(acMainstreamCommand(cmd, f_UI, f_End, false, f_Mtx_Ext_ON) == -1)
        return 0;

    return atoi(g_Schedular[m_LID]->acEntry(0)[0].c_str());
}

unsigned int icSafeL::Wallet_Insert(const char *table, const char **fields, const char **values, int fieldcount, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[65535];
    int i;

	sprintf(cmd, "INSERT INTO %s (", table);

    for (i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ", ");
        strcat(cmd, fields[i]);
		}

	strcat(cmd, ") VALUES (");

    for(i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ",");
        if(values[i] != NULL)
			{
			strcat(cmd, "'");
            strcat(cmd, values[i]);
            strcat(cmd, "'");
			}
        else
			{
            strcat (cmd, "NULL");
			}
		}

    strcat(cmd, ")");

	//Do the SQL
    if(acWallet_Command(cmd, f_UI, f_End, false, f_Mtx_Ext_ON) == -1)
        return 0;

    return atoi(g_Schedular[m_LID]->acEntry(0)[0].c_str());
}

unsigned int icSafeL::InsertM(const char *table, const char **fields, std::shared_ptr<std::vector<std::string>> f_values, int fieldcount, int cubecount, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[155350];
    int i;

	sprintf(cmd, "INSERT INTO %s (", table);

    for(i = 0; i < fieldcount; i++)
		{
        if(i > 0) strcat(cmd, ", ");

        strcat(cmd, fields[i]);
		}

	strcat(cmd, ") VALUES (");

	int f_cs = 0;

    for(i = 0; i < fieldcount * cubecount; i++)
		{
		if((i > 0) && (f_cs > 0))
			{
			strcat(cmd, ",");
			}

        if(i < f_values->size())
			{
			strcat(cmd, "'");
            strcat(cmd, f_values->at(i).c_str());
            strcat(cmd, "'");
			}
        else
			{
            strcat(cmd, "NULL");
			}

		if(f_cs >= (fieldcount - 1))
			{
			f_cs = 0;

			if(i < ((fieldcount * cubecount) - 1))
				{
				strcat(cmd, "),(");
				}
			else
				{
				strcat(cmd, ");");
				}
			}
		else
			{
			f_cs++;
			}
		}

	//Do the SQL
	if(acCommand(cmd, f_UI, f_End, false, f_Mtx_Ext_ON) == -1)
		{
		return 0;
		}

	return 1;

    return atoi(g_Schedular[m_LID]->acEntry(0)[0].c_str());
}

bool icSafeL::Update(const char *table, const char **fields, const char **values, int fieldcount, const char *whereclause, int f_UI, bool f_End, bool f_Mtx_Ext_ON)
{
	char cmd[1000];
	int i;

	sprintf(cmd, "UPDATE %s SET ", table);

	for(i = 0; i < fieldcount; i++)
		{
		if (i > 0) strcat (cmd, ",");
		strcat (cmd, fields[i]);
		if(values[i] != "")
			{
			strcat(cmd, "='");
			strcat(cmd, values[i]); 
			strcat(cmd, "'");
			}
		else
			{
			strcat(cmd, "=NULL");
			}
		}

	strcat(cmd, " WHERE ");
	strcat(cmd, whereclause);

	if(acCommand(cmd, f_UI, f_End, true, f_Mtx_Ext_ON) == -1)
		{
		return false;
		}
	return true;
}

bool icSafeL::UpdateQuery(const char *f_querystring)
{
	return acCommand(f_querystring, 0, false, true, false);
}

void icSafeL::EscapeString(std::string& string, const char * data, unsigned long datalength)
{
  char* temp = (char*)malloc((datalength * 2) + 1);
  long templen = 0;// safel_real_escape_string(connection, temp, data, datalength);

#if 0
  string.empty();
#endif

  string.append(temp, templen);
  free(temp);
}