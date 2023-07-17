/*

Function - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <vector>

#include "../Musion/MuType.h"
#include "../Musion/Variable.h"
#include "../Musion/Function.h"

#include "Code/myBO/icSafeL.h"

#include "Contract.h"

#if 0
#define SCHEDULAR_VERBOSE 1
#endif

#if 0
#define SCHEDULAR_BLOCKING_ON 1
#endif

#if 1
#define SCH_THR_DETACH
#endif

#if 0
#define QUANTUM_PUSH_THREADS 1
#endif

#if 1
#define QUANTUM_MAINSTREAM
#endif

#if 0
#define SCHEDULAR_LOCAL_MODE 1
#endif

namespace winrt
{
	using namespace Windows;
	using namespace Windows::ApplicationModel::Core;
	using namespace Windows::Foundation;
	using namespace Windows::Foundation::Numerics;
	using namespace Windows::Foundation::Collections;
	using namespace Windows::UI;
	using namespace Windows::UI::Core;
	using namespace Windows::UI::Composition;
	using namespace Windows::UI::Xaml;
	using namespace Windows::UI::Xaml::Hosting;
	using namespace Windows::UI::Xaml::Navigation;
	using namespace Windows::UI::ViewManagement;
	using namespace Windows::UI::WindowManagement;
	using namespace Windows::UI::WindowManagement::Preview;
};

#define SCHEDULAR_MTX_OFF 0
#define SCHEDULAR_LISTEN_MTX_ON 1
#define SCHEDULAR_GATHER_MTX_ON 2
#define SCHEDULAR_RESULT_MTX_OFF 3

#define ECOIN_ENTRY_DEPTH 5
#define ECOIN_ENTRY_MAX 100
#define ECOIN_ENTRY_REFRESH_DEPTH (ECOIN_ENTRY_MAX / 5)
#define ECOIN_ENTRY_REFRESH_MINUS (ECOIN_ENTRY_MAX - ECOIN_ENTRY_REFRESH_DEPTH)

#define ECOIN_STAGE_PREP 0
#define ECOIN_STAGE_FIRST 1
#define ECOIN_STAGE_CONNECTED 5

#define ECOIN_ELEMENT_PUSH_THREAD_COUNT 3
#define SCHEDULE_PRIMARY_THREAD_COUNT 2
#define SCHEDULE_MAINSTREAM_THREAD_COUNT 3

#define SCHEDULE_PRIMARY_MAX_THREAD ECOIN_ELEMENT_PUSH_THREAD_COUNT + SCHEDULE_PRIMARY_THREAD_COUNT
#define SCHEDULE_MAINSTREAM_MAX_THREAD ECOIN_ELEMENT_PUSH_THREAD_COUNT + SCHEDULE_MAINSTREAM_THREAD_COUNT

#define SCH_THREAD_EXT ECOIN_ELEMENT_PUSH_THREAD_COUNT
#define SCH_THREAD_COMBINER ECOIN_ELEMENT_PUSH_THREAD_COUNT + 1
#define SCH_THREAD_MAINSTREAM ECOIN_ELEMENT_PUSH_THREAD_COUNT + 2

#define SCHEDULE_TIME_OUT_SECONDS 130
#define SCHEDULE_MILLI_MUL 1000
#define SCHEDULE_THREAD_GRACE 10
#define SOL_TCP 2  // socket options TCP level

#define SCHEDULE_END_CHARACTER '@'

namespace ecoin
{

typedef struct Scan_Timer
{
	Scan_Timer(int f_Time, int f_LID, int f_ConnectionStage, bool f_Logon, bool f_WalletSave)
		{
		m_CountdownSecs = SCHEDULE_TIME_OUT_SECONDS;
		m_ScanTimer = f_Time + SCHEDULE_TIME_OUT_SECONDS;
		m_ConnectionStage = f_ConnectionStage;
		m_LID = f_LID;
		m_Logon = f_Logon;
		m_WalletSave = f_WalletSave;
		};

	int acCalc(void)
		{
		//Set Timer
		time_t f_Time_t;
		::time(&f_Time_t);

		m_Mutex.lock();

		int f_CountSeconds = m_ScanTimer - f_Time_t;

		m_CountdownSecs = f_CountSeconds;

		m_Mutex.unlock();

		return f_CountSeconds;
		}

	bool acConclude(void)
		{
		int f_Countdown = acCalc();

		return f_Countdown <= 0 ? true : false;
		}

	int m_ScanTimer;
	int m_CountdownSecs;
	
	bool m_WalletSave;
	bool m_Logon;

	int m_ConnectionStage;
	int m_LID;

	std::shared_mutex m_Mutex;
};

class Schedular : public ecom_base
{
	public:
		Schedular(int f_LID);
		~Schedular();

		void acShutdown(bool f_MainMutex_Ext_ON = false);
		void acShutdown_WalletSave(bool f_MainMutex_Ext_ON = false);

		bool acSend_Query(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
		bool acSend_Wallet_Query(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
		bool acSend_KeepAlive(char* f_Char, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_Angel(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_Mainstream(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
		bool acSend_KeepAlive_Angel(char* f_Char, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_PeerGraph(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_PeerGraphSelect(char* f_Char, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_GlobalStorageWealth(char* f_Char, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update = false, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_CMD_Angel(char* f_Char, int f_UI, bool f_End, bool f_Update = false, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_CMD_Mainstream(char* f_Char, int f_UI, bool f_End, bool f_Update = false, bool f_MainMutex_Ext_ON = false);
		bool acSend_Query_Wallet_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update = false, bool f_MainMutex_Ext_ON = false);
		bool acSend_Logon(char* f_Char, int f_UI, bool f_End, int f_Index, bool f_MainMutex_Ext_ON = false);
		bool acSend_Logon_Mainstream(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON = false);

		int acNet_Client_Data(void);
		int acNet_Client_Data_Gui(void);
		int acNet_Client_Data_Angel(void);
		int acNet_Client_Data_Prep(void);
		int acNet_Client_Data_Gui_Prep(void);
		int acNet_Client_Data_Angel_Prep(void);
		int acNet_Client_Data_Wallet_Save(void);
		int acNet_Client_Mainstream_Angel(void);

		int ac_GetEntry(int f_EntryIdx);

		std::thread DataFramePush(std::shared_ptr<Scan_Timer> f_Timer, int f_PushID);
		std::thread DataFrameExt(std::shared_ptr<Scan_Timer> f_Timer);
		std::thread DataFrame_GuiExt(std::shared_ptr<Scan_Timer> f_Timer);
		std::thread DataFrame_AngelExt(std::shared_ptr<Scan_Timer> f_Timer);
		std::thread DataFrameExt_Mainstream(std::shared_ptr<Scan_Timer> f_Timer);
		std::thread PushFrameCombiner(std::shared_ptr<Scan_Timer> f_Timer);

		void DataFrame_Org(void);
		void DataFrame_Mainstream_Org(void);
		void WalletSaveDataFrame_Org(void);

		void DataFramePush_Org(std::shared_ptr<Scan_Timer> f_Timer, int f_PushID);
		void DataFrameExt_Org(std::shared_ptr<Scan_Timer> f_Timer);
		void DataFrameExt_Mainstream_Org(std::shared_ptr<Scan_Timer> f_Timer);
		void DataFrame_GuiExt_Org(std::shared_ptr<Scan_Timer> f_Timer);
		void DataFrame_AngelExt_Org(std::shared_ptr<Scan_Timer> f_Timer);
		void PushFrameCombiner_Org(std::shared_ptr<Scan_Timer> f_Timer);

		bool acScheduleUpdator(int f_CurrentThread = -1);

		void acLogin(std::string f_Username, std::string f_Password);
		void acRegister(std::string f_Username, std::string f_Password, std::string f_Email);

		std::shared_ptr<Scan_Timer> acNewTimer(void);
		std::shared_ptr<Scan_Timer> acCurrentTimer(void);

		bool acPopulusIsFull(int f_CurrentThread = -1);
		bool acPopulusIsEmpty(int f_CurrentThread = -1);
		bool acPopulusOneIsFull(void);
		bool acPopulusThreeIsFull(void);
		bool acPopulusOneIsEmpty(void);
		bool acPopulusThreeIsEmpty(void);

		void acFeedPopulus(int f_Index);
		void acUnlockPopulus(int f_Index);

		void acInitialState(void);

		bool acScan(void);
		void acCancel(void);

		std::vector<std::string> acEntry(int f_Index);
		std::vector<std::string> acEntryIndex(int f_ArrayIndex, int f_Index);
		std::shared_ptr<std::vector<std::vector<std::string>>> acEntryPtr(void);
		int acEntrySize(void);

		std::vector<std::string> acMSEntry(int f_Index);
		std::vector<std::string> acMSEntryIndex(int f_ArrayIndex, int f_Index);
		std::shared_ptr<std::vector<std::vector<std::string>>> acMSEntryPtr(void);
		int acMSEntrySize(void);

		std::vector<std::shared_ptr<Scan_Timer>> m_vec_ScanTimer;

		std::Smart_Ptr<SocketSet> m_ClientSS;

		bool m_Scan;
		bool m_MainFrameScan;
		bool m_MainstreamFrameScan;
		bool m_WalletSaveScan;
		bool m_WalletSave;
		bool m_WalletMainExited;
		bool m_MainExited;
		bool m_MainstreamExited;
		bool m_Logon;
		bool m_Logon_Mainstream;

		int m_PushReceiveFgr;

		int m_prev_State;
		int m_MaxThreads;

		int m_LID;
		int m_ConnectionStage;

		int m_MutexLocked[SCHEDULE_MAINSTREAM_MAX_THREAD];

		std::vector<std::shared_ptr<std::vector<std::vector<std::string>>>> m_Entries;
		std::vector<int> m_Entrant;
		std::vector<std::shared_ptr<std::string>> m_vec_Packet;

		std::vector<std::shared_ptr<std::vector<std::vector<std::string>>>> m_Mainstream_Entries;
		std::vector<int> m_Mainstream_Entrant;
		std::vector<std::shared_ptr<std::string>> m_vec_Mainstream;

		std::shared_ptr<std::vector<std::vector<std::string>>> m_PushResult_Entry;
		std::vector<std::vector<std::shared_ptr<std::string>>> m_vec_PushPacket;

		bool m_SentMtx_ON;

		std::shared_mutex m_Mutex;
		std::shared_mutex m_MainMutex;
		std::shared_mutex m_SentMtx;

		std::shared_mutex m_EntriesMtx;
		std::shared_mutex m_EntrantMtx;
		std::shared_mutex m_MainstreamEntriesMtx;
		std::shared_mutex m_MainstreamEntrantMtx;

		std::shared_mutex m_ScanTimerMutex;
		std::shared_mutex m_PacketMutex;
		std::shared_mutex m_MainstreamPacketMutex;
};

extern void ag_KeepAlive(void);

extern std::shared_ptr<Schedular> g_Schedular[3];

extern std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy, int iResult);
extern std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy);
extern std::string agsc_ReadElement_Sock_V15(char* f_Charpntr, int* f_Cy, int iResult, bool f_isLastof = false);

extern int g_QAccountID;
extern int g_ShareID;

#define Schedular_MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define Schedular_FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#define SCH_UNLOCKED 0
#define SCH_LOCKED 1

#define SCHEDULE_UPDATE 0
#define SCHEDULE_UPDATE_NORMAL 1
#define SCHEDULE_PAUSE_UPDATE_NORMAL 2

#define SCHEDULE_STATE_BASE_FIRST 0
#define SCHEDULE_STATE_BASE_SECOND 1
#define SCHEDULE_STATE_CONNECTING_FIRST 3
#define SCHEDULE_STATE_CONNECTING_SECOND 4
#define SCHEDULE_STATE_CONNECTING_WALLET 5
#define SCHEDULE_STATE_SAVING_WALLET 6

};

#endif