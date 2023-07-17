/*

Contract - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CONTRACT_H
#define CONTRACT_H

#include <WinSock2.h>

#include <vector>
#include <math.h>

#include "Code/Musion/Variable.h"
#include "Code/Musion/CodeLine.h"
#include "Code/Musion/Code.h"
#include "Code/Musion/System.h"
#include "Code/Musion/Function.h"
#include "Code/Musion/Class.h"

#include "Code/myBO/icSafeL.h"

#define DEFAULT_ADDR "192.64.112.79"
#define DEFAULT_ADDRM "192.64.112.79"

#define DEFAULT_PORT "5530"
#define DEFAULT_PORT_GUI "5531"
#define DEFAULT_PORT_ANGEL "5532"
#define MAINSTREAM_PORT_ANGEL "5632"

#define ONBOARDING_PORT "5430"
#define ONBOARDING_PORT_GUI "5431"
#define ONBOARDING_PORT_ANGEL "5432"

#define WALLETSAVE_PORT "5330"

#define SEND_DEFAULT_BUFLEN 9000
#define DEFAULT_BUFLEN 90000

#define ECOIN_PACKAGE_ROW_MAX 30
#define ECOIN_SEARCH_ROW_MAX 75

namespace Cube
{

	class Qcom_eslfunction;

};

namespace ecoin
{

	class ComputerAddr
	{
	public:
		std::string m_IP;
	};

	ComputerAddr g_YourAddr;

	class Contract_State
	{
	public:
		Contract_State()
			{
			m_Verify_DL = false;
			m_Verify_Reading = false;
			m_Verify_UnWrapped = false;
			m_Verify_UP = false;
			m_Verify_Sealed = false;
			}

		~Contract_State()
			{
			m_Verify_DL = false;
			m_Verify_Reading = false;
			m_Verify_UnWrapped = false;
			m_Verify_UP = false;
			m_Verify_Sealed = false;
			}

		 /////////////////////////
		// Verification States //
		bool m_Verify_DL;
		bool m_Verify_Reading;
		bool m_Verify_UnWrapped;
		bool m_Verify_UP;
		bool m_Verify_Sealed;
	};

	class unMutexCC : public ecom_base
	{
	public:
		unMutexCC()
			{
			mBlock = false;
			mFired = false;
			}
		~unMutexCC() {};
	
		bool mBlock;
		bool mFired;

		void ac_Fire(void)
			{
			while(mFired) { /*wait*/ }

			mFired = true;
			}

		void ac_Free(void)
			{
			mFired = false;
			}
	};

	class SocketSet
	{
	public:
		SocketSet() { m_Socket = 0; }
		~SocketSet() { m_Socket = 0; }

		std::string m_IP;
		std::string m_IP_Gui;
		std::string m_IP_Angel;

		std::string m_PORT;
		std::string m_PORT_Gui;
		std::string m_PORT_Angel;

		std::string m_BOARD;
		std::string m_BOARD_Gui;
		std::string m_BOARD_Angel;

		std::string m_Mainstream_Angel;

		std::string m_WALLETSAVE_PORT;

		SOCKET m_Socket;
		SOCKET m_MainstreamSocket;
		SOCKET m_WalletSaveSocket;

		std::vector<SOCKET> m_vec_Socket;

		char m_recvbuf[DEFAULT_BUFLEN];

		std::string m_Buffer;
	};

	class Contract : public ecom_base
	{
	public:
		Contract();
		Contract(std::string f_IN);
		Contract(std::shared_ptr<Cube::Qcom_eslfunction> f_IN);
		~Contract();

		bool acLoad_StrIn(std::string f_IN);

		//--- SCAN Function
		bool acScan_Lines(void);

		//-  SCANNING Function
		void acScan_LineDetect(std::string f_Line);

		//-  Unused Line Extractor
		bool acExtractLines(void);

		void acWork(void);

		void ac_ClearVars(void);

#ifdef ESL_LOAD_VARS
		void ac_LoadVars(void);
#endif

#ifdef ESL_VAR_BY_NAME_METHOD
		void ac_SetupVars(void);

		std::shared_ptr<Variable> ac_VarByName(std::shared_ptr<Variable> f_Variable);
#endif

		Contract_State m_State;

		uint m_Chk;
		bool m_Active;
		int m_ContractID;

		System* m_System;

		std::string m_Str_Command;

		std::vector<std::string> m_Line;

		std::shared_ptr<Function> m_Frame_Function;

		std::vector<std::shared_ptr<Function>> m_vec_Function;
		std::vector<std::shared_ptr<Class>> m_vec_Class;

		std::vector<std::shared_ptr<CodeLine>> m_vec_CodeLine;

		std::vector<std::shared_ptr<Variable>> m_vec_Variable_Store;
		std::vector<std::shared_ptr<ClassVar>> m_vec_ClassVar_Store;

		std::shared_ptr<ecoin::Function> m_entered_Function;
		std::shared_ptr<ecoin::Class> m_entered_Class;
	};

	extern std::vector<std::shared_ptr<Class>> g_Class;
	extern std::vector<std::shared_ptr<ClassVar>> g_ClassVar;

	extern std::vector<std::shared_ptr<Condition>> g_Condition;

	extern std::vector<std::shared_ptr<Function>> g_Function;
	extern std::vector<std::shared_ptr<Function>> g_systemFunction;

	extern std::vector<std::shared_ptr<Contract>> g_vec_CompileScope_Contract;
	extern std::vector<std::shared_ptr<Contract>> g_vec_OperatorScope_Contract;

	extern int g_ContractID; //async ????
};

#endif
