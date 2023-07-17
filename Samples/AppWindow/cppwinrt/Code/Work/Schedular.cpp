/*

Schedular - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Schedular.h"

using namespace ecoin;

namespace ecoin
{

#define COUNT_AMT 0

std::shared_ptr<Schedular> g_Schedular[3];

int g_QAccountID = 0;
int g_ShareID = 0;

Schedular::Schedular(int f_LID)
{
	m_LID = f_LID;

	m_Logon = false;
	m_Logon_Mainstream = false;
	m_WalletSave = false;
	m_SentMtx_ON = false;

	m_prev_State = -1;

	m_ClientSS = std::ag_Make_Smart_Pointer<SocketSet>();

	m_ClientSS->m_IP = "192.64.112.79";
	m_ClientSS->m_IP_Gui = "192.64.112.79";
	m_ClientSS->m_IP_Angel = "192.64.112.79";

	m_ClientSS->m_PORT = DEFAULT_PORT;
	m_ClientSS->m_PORT_Gui = DEFAULT_PORT_GUI;
	m_ClientSS->m_PORT_Angel = DEFAULT_PORT_ANGEL;

	m_ClientSS->m_BOARD = ONBOARDING_PORT;
	m_ClientSS->m_BOARD_Gui = ONBOARDING_PORT_GUI;
	m_ClientSS->m_BOARD_Angel = ONBOARDING_PORT_ANGEL;

	m_ClientSS->m_Mainstream_Angel = MAINSTREAM_PORT_ANGEL;

	m_ClientSS->m_WALLETSAVE_PORT = WALLETSAVE_PORT;

	switch(m_LID)
		{
		case 0:
			{
			m_MaxThreads = SCHEDULE_PRIMARY_MAX_THREAD;
			}break;

		case 1:
			{
			m_MaxThreads = SCHEDULE_PRIMARY_MAX_THREAD;
			}break;

		case 2:
			{
			m_MaxThreads = SCHEDULE_MAINSTREAM_MAX_THREAD;
			}break;
		}

	m_PushReceiveFgr = 0;

	m_ScanTimerMutex.lock();

	m_vec_ScanTimer.clear();

	m_ScanTimerMutex.unlock();

	//Additional
	acInitialState();

	m_Scan = true;

#ifndef OSI_MEM_APP
	std::string f_ref_CurrentPath = "Schedular::Schedular";

	ac_Push(m_Entrant, f_ref_CurrentPath + g_ref_Div + "m_Entrant");
#endif
}

void Schedular::acFeedPopulus(int f_Index)
{
	m_Mutex.lock();

	m_MutexLocked[f_Index] = SCH_LOCKED;

	m_Mutex.unlock();
}

void Schedular::acUnlockPopulus(int f_Index)
{
	m_Mutex.lock();

	m_MutexLocked[f_Index] = SCH_UNLOCKED;

	int f_Finger = 0;   // Last one exit scan = false
	bool f_Scan = false;

	while(f_Finger < (m_MaxThreads - 1))
		{
		if(m_MutexLocked[f_Finger] == SCH_LOCKED)
			{
			f_Scan = true;

			f_Finger = m_MaxThreads;
			}

		f_Finger++;
		}

	m_Scan = f_Scan;

	m_Mutex.unlock();
}

bool Schedular::acScan(void)
{
	bool f_Scan = false;

	m_Mutex.lock();

	f_Scan = m_Scan;

	m_Mutex.unlock();

	return f_Scan;
}

void Schedular::acCancel(void)
{
	m_Mutex.lock();

	m_Scan = false;

	m_Mutex.unlock();
}

bool Schedular::acPopulusIsFull(int f_CurrentThread)
{
#ifdef QUANTUM_PUSH_THREADS
	for(int f_XY = 0; f_XY < m_MaxThreads; f_XY++)
		{
		if(f_CurrentThread != f_XY)
			{
			m_Mutex.lock();

			if(m_MutexLocked[f_XY] == SCH_UNLOCKED)
				{
				m_Mutex.unlock();

				return false;
				}

			m_Mutex.unlock();
			}
		}
#else
	if(m_LID < 2)
		{
		for(int f_XY = 0; f_XY < m_MaxThreads; f_XY++)
			{
			if(f_CurrentThread != f_XY)
				{
				m_Mutex.lock();

				if(m_MutexLocked[f_XY] == SCH_UNLOCKED)
					{
					m_Mutex.unlock();

					return false;
					}

				m_Mutex.unlock();
				}
			}
		}
	else
		{
		for(int f_XY = ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_XY < m_MaxThreads; f_XY++)
			{
			if(f_CurrentThread != f_XY)
				{
				m_Mutex.lock();

				if(m_MutexLocked[f_XY] == SCH_UNLOCKED)
					{
					m_Mutex.unlock();

					return false;
					}

				m_Mutex.unlock();
				}
			}
		}
#endif

	return true;
}

bool Schedular::acPopulusIsEmpty(int f_CurrentThread)
{
#ifdef QUANTUM_PUSH_THREADS
	for(int f_XY = 0; f_XY < m_MaxThreads; f_XY++)
		{
		if(f_CurrentThread != f_XY)
			{
			m_Mutex.lock();

			if(m_MutexLocked[f_XY] == SCH_LOCKED)
				{
				m_Mutex.unlock();

				return false;
				}

			m_Mutex.unlock();
			}
		}
#else
	if(m_LID < 2)
		{
		for(int f_XY = 0; f_XY < m_MaxThreads; f_XY++)
			{
			if(f_CurrentThread != f_XY)
				{
				m_Mutex.lock();

				if(m_MutexLocked[f_XY] == SCH_LOCKED)
					{
					m_Mutex.unlock();

					return false;
					}

				m_Mutex.unlock();
				}
			}
		}
	else
		{
		for(int f_XY = ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_XY < m_MaxThreads; f_XY++)
			{
			if(f_CurrentThread != f_XY)
				{
				m_Mutex.lock();

				if(m_MutexLocked[f_XY] == SCH_LOCKED)
					{
					m_Mutex.unlock();

					return false;
					}

				m_Mutex.unlock();
				}
			}
		}
#endif

	return true;
}

bool Schedular::acPopulusOneIsFull(void)
{
	bool f_BoolResult = false;

	m_Mutex.lock();

	if(m_MutexLocked[0] == SCH_LOCKED)
		{
		f_BoolResult = true;
		}

	m_Mutex.unlock();

	return f_BoolResult;
}

bool Schedular::acPopulusThreeIsEmpty(void)
{
	bool f_BoolResult = false;

	m_Mutex.lock();

	if(m_MutexLocked[SCH_THREAD_EXT] == SCH_UNLOCKED)
		{
		f_BoolResult = true;
		}

	m_Mutex.unlock();

	return f_BoolResult;
}

bool Schedular::acPopulusOneIsEmpty(void)
{
	bool f_BoolResult = false;

	m_Mutex.lock();

	if(m_MutexLocked[0] == SCH_UNLOCKED)
		{
		f_BoolResult = true;
		}

	m_Mutex.unlock();

	return f_BoolResult;
}

bool Schedular::acPopulusThreeIsFull(void)
{
	bool f_BoolResult = false;

	m_Mutex.lock();

	if(m_MutexLocked[SCH_THREAD_EXT] == SCH_LOCKED)
		{
		f_BoolResult = true;
		}

	m_Mutex.unlock();

	return f_BoolResult;
}

void Schedular::acInitialState(void)
{
	for(int f_XY = 0; f_XY < m_MaxThreads; f_XY++)
		{
		m_MutexLocked[f_XY] = SCH_UNLOCKED;
		}
}

Schedular::~Schedular()
{
	acShutdown();

	WSACleanup();
}

void Schedular::acShutdown(bool f_MainMutex_Ext_ON)
{
#if 1
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }
#endif

	m_EntriesMtx.lock();

	//register entrant
	int f_EntCount = m_Entries.size();

	m_EntriesMtx.unlock();

	if(f_EntCount >= ECOIN_ENTRY_MAX)
		{
		f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
		}

	std::string f_String = "Xecoincd1:";
	f_String += "XXXXX";
	f_String += ":ecoincd1";

	char* f_EndCap = ag_ClearChar(32);
	::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
	std::string f_Result = f_String + f_EndCap;
	delete f_EndCap;

	int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)f_Result.length(), 0);

	for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
		{
		iResult = send(m_ClientSS->m_vec_Socket[f_Jet], (char*)f_Result.c_str(), (int)f_Result.length(), 0);
		}

	if(m_LID == 2)
		{
		int iResult_Mainstream = send(m_ClientSS->m_MainstreamSocket, (char*)f_Result.c_str(), (int)f_Result.length(), 0);
		}

	m_MainFrameScan = false;

	m_EntriesMtx.lock();
	m_Entries.clear();
	m_EntriesMtx.unlock();

	m_EntrantMtx.lock();
	m_Entrant.clear();
	m_EntrantMtx.unlock();

	m_PacketMutex.lock();
	m_vec_Packet.clear();
	m_PacketMutex.unlock();

	//Pause for exit
	while(m_MainExited == false)
		{
		//.... [pause]
		}

	if(m_LID == 2)
		{
		m_MainstreamFrameScan = false;

		m_MainstreamEntriesMtx.lock();
		m_Mainstream_Entries.clear();
		m_MainstreamEntriesMtx.unlock();

		m_MainstreamEntrantMtx.lock();
		m_Mainstream_Entrant.clear();
		m_MainstreamEntrantMtx.unlock();

		m_MainstreamPacketMutex.lock();
		m_vec_Mainstream.clear();
		m_MainstreamPacketMutex.unlock();

		//Pause for exit
		while(m_MainstreamExited == false)
			{
			//.... [pause]
			}
		}

	closesocket(m_ClientSS->m_Socket);

	for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
		{
		closesocket(m_ClientSS->m_vec_Socket[f_Jet]);
		}

	if(m_LID == 2)
		{
		closesocket(m_ClientSS->m_MainstreamSocket);
		}

#if 1
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }
#endif
}

bool Schedular::acScheduleUpdator(int f_CurrentThread)
{
	int f_State = SCHEDULE_UPDATE;
	int f_new_State = -1;

	//State Selection
	if(m_WalletSave == false) //....
		{
		if(m_Logon == false) // Base Stages
			{
			if(m_ConnectionStage == ECOIN_STAGE_PREP)
				{
				f_new_State = SCHEDULE_STATE_BASE_FIRST;
				}
			else
				{
				f_new_State = SCHEDULE_STATE_BASE_SECOND;
				}
			}
		else    // Connecting Stages
			{
			if(m_ConnectionStage == ECOIN_STAGE_PREP) // Socket One
				{
				f_new_State = SCHEDULE_STATE_CONNECTING_FIRST;
				}
			else  // Socket [1][2][3]
				{
				f_new_State = SCHEDULE_STATE_CONNECTING_SECOND;
				}
			}
		}
	else        // Wallet Server Save
		{
		if(m_Logon == false) // Base Stages
			{
			f_new_State = SCHEDULE_STATE_SAVING_WALLET;
			}
		else    // Connecting Stages
			{
			f_new_State = SCHEDULE_STATE_CONNECTING_WALLET;
			}
		}

	//On Polling Scan = true
	m_Mutex.lock();

	m_Scan = true;

	m_Mutex.unlock();

	std::shared_ptr<Scan_Timer> f_CurrentTimer = nullptr;

	//Previous State Override
	if(m_prev_State != f_new_State)
		{
		f_State = SCHEDULE_PAUSE_UPDATE_NORMAL;
		}
	else
		{
		if(m_vec_ScanTimer.size() > 0) //Extension Stage
			{
			//Scan Timer
			f_CurrentTimer = acCurrentTimer();

			//Set Timer
			time_t f_Time_t;
			::time(&f_Time_t);

			f_CurrentTimer->m_Mutex.lock();

			f_CurrentTimer->m_ScanTimer = f_Time_t + SCHEDULE_TIME_OUT_SECONDS;

			f_CurrentTimer->m_Mutex.unlock();
			}
		
		f_State = SCHEDULE_UPDATE_NORMAL;
		}
	
	if(f_State == SCHEDULE_PAUSE_UPDATE_NORMAL) // Pause for New All
		{
		//Pause Stage
		for(int f_XY = 0; f_XY < m_vec_ScanTimer.size(); f_XY++)
			{
			std::shared_ptr<Scan_Timer> f_Timer = m_vec_ScanTimer[f_XY];

			acCancel();

			if(f_Timer->m_Logon == false)
				{
				if(f_Timer->m_WalletSave == false)
					{
					if(f_Timer->m_ConnectionStage == ECOIN_STAGE_PREP)
						{
						while(acPopulusThreeIsEmpty() == false) {/**/}
						}
					else
						{
						while(acPopulusIsEmpty(f_CurrentThread) == false) {/**/}
						}
					}
				else    // Wallet Save Active....
					{
					while(acPopulusOneIsEmpty() == false) {/**/}
					}
				}
			else        // Connecting Stages
				{
				if(f_Timer->m_WalletSave == false)
					{
					if(f_Timer->m_ConnectionStage == ECOIN_STAGE_PREP)
						{
						while(acPopulusThreeIsEmpty() == false) {/**/}
						}
					else
						{
						while(acPopulusIsEmpty(f_CurrentThread) == false) {/**/}
						}
					}
				else    //Wallet Save Active....
					{
					while(acPopulusOneIsEmpty() == false) {/**/}
					}
				}
			}

		m_vec_ScanTimer.clear();

		f_CurrentTimer = acNewTimer();
		}

	//Win Conditions! Continue

	if(f_State >= SCHEDULE_UPDATE_NORMAL) // Thread Updator Main
		{
		m_Mutex.lock();

		if(m_Scan == true)
			{
			switch(m_LID)
				{
				case 0:
					{
					if(m_WalletSave == true)
						{
						if(acPopulusOneIsFull() == false)
							{
							if(m_MutexLocked[0] == SCH_UNLOCKED)
								{
								m_MutexLocked[0] = SCH_LOCKED;

								//data frame extension
								std::thread f_thread_Ext(&Schedular::DataFrameExt_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
								f_thread_Ext.detach();
#endif
								}
							}
						}
					else
						{
						if(m_ConnectionStage >= ECOIN_STAGE_FIRST)
							{
							for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
								{
								if(m_MutexLocked[f_Jet] == SCH_UNLOCKED)
									{
									m_MutexLocked[f_Jet] = SCH_LOCKED;

									std::thread f_thread_Data(&Schedular::DataFramePush_Org, this, f_CurrentTimer, f_Jet);

#ifdef SCH_THR_DETACH
									f_thread_Data.detach();
#endif
									}
								}

							if(m_MutexLocked[SCH_THREAD_COMBINER] == SCH_UNLOCKED)
								{
								m_MutexLocked[SCH_THREAD_COMBINER] = SCH_LOCKED;

								//single push combiner
								std::thread f_thread_Push_Ext(&Schedular::PushFrameCombiner_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
								f_thread_Push_Ext.detach();
#endif
								}
							}

						if(m_MutexLocked[SCH_THREAD_EXT] == SCH_UNLOCKED)
							{
							m_MutexLocked[SCH_THREAD_EXT] = SCH_LOCKED;

							//data frame extension
							std::thread f_thread_Ext(&Schedular::DataFrameExt_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
							f_thread_Ext.detach();
#endif
							}
						}
					}break;

				case 1:
					{
					if(m_ConnectionStage >= ECOIN_STAGE_FIRST)
						{
						for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
							{
							if(m_MutexLocked[f_Jet] == SCH_UNLOCKED)
								{
								m_MutexLocked[f_Jet] = SCH_LOCKED;

								std::thread f_thread_Data(&Schedular::DataFramePush_Org, this, f_CurrentTimer, f_Jet);

#ifdef SCH_THR_DETACH
								f_thread_Data.detach();
#endif
								}
							}

						if(m_MutexLocked[SCH_THREAD_COMBINER] == SCH_UNLOCKED)
							{
							m_MutexLocked[SCH_THREAD_COMBINER] = SCH_LOCKED;

							//single push combiner
							std::thread f_thread_Push_Ext(&Schedular::PushFrameCombiner_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
							f_thread_Push_Ext.detach();
#endif
							}
						}

					if(m_MutexLocked[SCH_THREAD_EXT] == SCH_UNLOCKED)
						{
						m_MutexLocked[SCH_THREAD_EXT] = SCH_LOCKED;

						//data frame extensiona
						std::thread f_thread_Ext(&Schedular::DataFrame_GuiExt_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
						f_thread_Ext.detach();
#endif
						}
					}break;

				case 2:
					{
					if(m_ConnectionStage >= ECOIN_STAGE_FIRST)
						{
#ifdef QUANTUM_PUSH_THREADS
						for(int f_Jet = 0; f_Jet < m_ClientSS->m_vec_Socket.size(); f_Jet++)
							{
							if(m_MutexLocked[f_Jet] == SCH_UNLOCKED)
								{
								m_MutexLocked[f_Jet] = SCH_LOCKED;

								std::thread f_thread_Data(&Schedular::DataFramePush_Org, this, f_CurrentTimer, f_Jet);

#ifdef SCH_THR_DETACH
								f_thread_Data.detach();
#endif
								}
							}

						if(m_MutexLocked[SCH_THREAD_COMBINER] == SCH_UNLOCKED)
							{
							m_MutexLocked[SCH_THREAD_COMBINER] = SCH_LOCKED;

							//single push combiner
							std::thread f_thread_Push_Ext(&Schedular::PushFrameCombiner_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
							f_thread_Push_Ext.detach();
#endif
							}
#endif
						}

					if(m_MutexLocked[SCH_THREAD_EXT] == SCH_UNLOCKED)
						{
						m_MutexLocked[SCH_THREAD_EXT] = SCH_LOCKED;

						//data frame extension
						std::thread f_thread_Ext(&Schedular::DataFrame_AngelExt_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
						f_thread_Ext.detach();
#endif
						}

#ifdef QUANTUM_MAINSTREAM
					if(m_MutexLocked[SCH_THREAD_MAINSTREAM] == SCH_UNLOCKED)
						{
						m_MutexLocked[SCH_THREAD_MAINSTREAM] = SCH_LOCKED;

						//mainstream frame extension
						std::thread f_thread_DataMainstream(&Schedular::DataFrameExt_Mainstream_Org, this, f_CurrentTimer);

#ifdef SCH_THR_DETACH
						f_thread_DataMainstream.detach();
#endif
						}
#endif
					}break;
				}
			}

		m_Mutex.unlock();
		}

	if(f_new_State != -1)
		{
		m_prev_State = f_new_State;
		}

	if(f_State >= SCHEDULE_UPDATE_NORMAL)
		{
		return true;
		}
	else
		{
		return false;
		}
}

std::shared_ptr<Scan_Timer> Schedular::acNewTimer(void)
{
	//Set Timer
	time_t f_Time_t;
	::time(&f_Time_t);
	
	std::shared_ptr<Scan_Timer> f_Timer = std::make_shared<Scan_Timer>(f_Time_t, m_LID, m_ConnectionStage, m_Logon, m_WalletSave);

	m_ScanTimerMutex.lock();

	m_vec_ScanTimer.push_back(f_Timer);

	m_ScanTimerMutex.unlock();

	return f_Timer;
}

std::shared_ptr<Scan_Timer> Schedular::acCurrentTimer(void)
{
	m_ScanTimerMutex.lock();

	if(m_vec_ScanTimer.size() > 0)
		{
		std::shared_ptr<Scan_Timer> f_Timer = m_vec_ScanTimer[m_vec_ScanTimer.size() - 1];

		m_ScanTimerMutex.unlock();

		return f_Timer;
		}

	m_ScanTimerMutex.unlock();

	return acNewTimer();
}

int Schedular::acNet_Client_Data(void)
{
	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		int iResult;
		struct addrinfo *resultx = NULL, *ptrx = NULL, hintsx;

		ZeroMemory(&hintsx, sizeof(hintsx));

		hintsx.ai_family = AF_UNSPEC;
		hintsx.ai_socktype = SOCK_STREAM;
		hintsx.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
		iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_BOARD.c_str(), &hintsx, &resultx);
#else
		iResult = getaddrinfo("localhost", m_ClientSS->m_BOARD.c_str(), &hintsx, &resultx);
#endif

		if(iResult != 0)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}

		// Attempt to connect to an address until one succeeds
		for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
			{
			// Create a SOCKET for connecting to server
			SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif  //add debug message
				}

			// Connect to server.
			iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
			if(iResult == SOCKET_ERROR)
				{
				closesocket(f_Socket);

				f_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif  //add debug message
				}
			else
				{
#ifdef SCHEDULAR_BLOCKING_ON
				struct timeval tv;

				tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

				int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

				if(h_OK != 0)
					{
					int f_ErrorCode = WSAGetLastError();

					char* f_Char = ag_ClearChar(512);
					sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
					winrt::hstring f_String = StrUsingStr(std::string(f_Char));
					OutputDebugString(f_String.c_str());
					delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //error stated within output debug window \/
#endif
					}
#else
#if 0			//Blocking Mode
				u_long iMode = 0;
#else			//Non Blocking Mode
				u_long iMode = 1;
#endif

				int h_OK = ioctlsocket(f_Socket, FIONBIO, &iMode);

				if(h_OK != NO_ERROR)
					{
					__debugbreak();
					}
#endif
				}

			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif //add debug message
				}
			else
				{
				m_ClientSS->m_vec_Socket.push_back(f_Socket);

				std::vector<std::shared_ptr<std::string>> f_vec_Str;

				m_vec_PushPacket.push_back(f_vec_Str);
				}

			break;
			}

		freeaddrinfo(resultx);
		}

	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		//Send Logon
		acSend_Logon((char*)g_Wallet->GetAdr().c_str(), 0, true, f_Jet + 1);
		}

	return 1;
}

int Schedular::acNet_Client_Data_Wallet_Save(void)
{
	m_ClientSS->m_Socket = INVALID_SOCKET;

	WSADATA wsaData;
	struct addrinfo *resultx = NULL, *ptrx = NULL, hintsx;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(iResult != 0)
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	ZeroMemory(&hintsx, sizeof(hintsx));

	hintsx.ai_family = AF_UNSPEC;
	hintsx.ai_socktype = SOCK_STREAM;
	hintsx.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
	iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_WALLETSAVE_PORT.c_str(), &hintsx, &resultx);
#else
	iResult = getaddrinfo("localhost", m_ClientSS->m_WALLETSAVE_PORT.c_str(), &hintsx, &resultx);
#endif

	if(iResult != 0)
		{
		int f_ErrorCode = WSAGetLastError();

		char* f_Char = ag_ClearChar(512);
		sprintf(f_Char, "getaddrinfo ErrorCode == %i\n", f_ErrorCode);
		winrt::hstring f_String = StrUsingStr(std::string(f_Char));
		OutputDebugString(f_String.c_str());
		delete f_Char;

		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	// Attempt to connect to an address until one succeeds
	for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
		{
		// Create a SOCKET for connecting to server
		SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
		if(f_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}

		// Connect to server.
		iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(f_Socket);

			f_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}
		else
			{
#ifdef SCHEDULAR_BLOCKING_ON
			struct timeval tv;

			tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

			int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

			if(h_OK != 0)
				{
				int f_ErrorCode = WSAGetLastError();

				char* f_Char = ag_ClearChar(512);
				sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
				winrt::hstring f_String = StrUsingStr(std::string(f_Char));
				OutputDebugString(f_String.c_str());
				delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //error stated within output debug window \/
#endif
				}
#else
#if 0			//Blocking Mode
			u_long iMode = 0;
#else			//Non Blocking Mode
			u_long iMode = 1;
#endif

			int h_OK = ioctlsocket(f_Socket, FIONBIO, &iMode);

			if(h_OK != NO_ERROR)
				{
				__debugbreak();
				}
#endif
			}

		if(f_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif //add debug message
			}
		else
			{
			m_ClientSS->m_WalletSaveSocket = f_Socket;

			std::thread f_thread_DataDF(&Schedular::WalletSaveDataFrame_Org, this);

#ifdef SCH_THR_DETACH
			f_thread_DataDF.detach();
#endif
			}

		break;
		}

	freeaddrinfo(resultx);

	return 1;
}

void Schedular::acShutdown_WalletSave(bool f_MainMutex_Ext_ON)
{
#if 1
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }
#endif

	m_EntriesMtx.lock();

	//register entrant
	int f_EntCount = m_Entries.size();

	m_EntriesMtx.unlock();

	if(f_EntCount >= ECOIN_ENTRY_MAX)
		{
		f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
		}

	std::string f_String = "Xecoincd1:";
	f_String += "XXXXX";
	f_String += ":ecoincd1";

	char* f_EndCap = ag_ClearChar(32);
	::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
	std::string f_Result = f_String + f_EndCap;
	delete f_EndCap;

	int iResult = send(m_ClientSS->m_WalletSaveSocket, (char*)f_Result.c_str(), (int)f_Result.length(), 0);

	m_WalletSaveScan = false;

	m_EntriesMtx.lock();
	m_Entries.clear();
	m_EntriesMtx.unlock();

	m_PacketMutex.lock();
	m_vec_Packet.clear();
	m_PacketMutex.unlock();

	m_EntrantMtx.lock();
	m_Entrant.clear();
	m_EntrantMtx.unlock();

	while(m_WalletMainExited == false)
		{
		//.... [pause]
		}

	closesocket(m_ClientSS->m_WalletSaveSocket);

#if 1
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }
#endif
}

int Schedular::acNet_Client_Data_Prep(void)
{
	m_ClientSS->m_Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

#ifdef ECOIN_DEBUG_BREAKS
	if(iResult != 0)
		{
		__debugbreak();
		}
#endif  //add debug message

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
	iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_PORT.c_str(), &hints, &result);
#else
	iResult = getaddrinfo("localhost", m_ClientSS->m_PORT.c_str(), &hints, &result);
#endif

	if(iResult != 0)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
		// Create a SOCKET for connecting to server
		m_ClientSS->m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		
		if(m_ClientSS->m_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}

		// Connect to server.
		iResult = connect(m_ClientSS->m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(m_ClientSS->m_Socket);

			m_ClientSS->m_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}
		else
			{
#ifdef SCHEDULAR_BLOCKING_ON
			struct timeval tv;

			tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

			int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

			if(h_OK != 0)
				{
				int f_ErrorCode = WSAGetLastError();

				char* f_Char = ag_ClearChar(512);
				sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
				winrt::hstring f_String = StrUsingStr(std::string(f_Char));
				OutputDebugString(f_String.c_str());
				delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //error stated within output debug window \/
#endif
				}
#else
#if 0		//Blocking Mode
			u_long iMode = 0;
#else		//Non Blocking Mode
			u_long iMode = 1;
#endif

			int h_OK = ioctlsocket(m_ClientSS->m_Socket, FIONBIO, &iMode);

			if(h_OK != NO_ERROR)
				{
				__debugbreak();
				}
#endif

			std::thread f_thread_DataDF(&Schedular::DataFrame_Org, this);

#ifdef SCH_THR_DETACH
			f_thread_DataDF.detach();
#endif
			}

		break;
		}

	freeaddrinfo(result);

	if(m_ClientSS->m_Socket == INVALID_SOCKET)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	//Send Logon
	acSend_Logon((char*)g_Wallet->GetAdr().c_str(), 0, true, 0);

	return 1;
}

// Create a task that will be run on a background thread.
std::thread Schedular::DataFramePush(std::shared_ptr<Scan_Timer> f_Timer, int f_PushID)
{
	return std::thread([=] { DataFramePush_Org(f_Timer, f_PushID); });
}

void Schedular::DataFramePush_Org(std::shared_ptr<Scan_Timer> f_Timer, int f_PushID)
{
#ifdef ECOIN_DEBUG_BREAKS
	int f_LID = m_LID;
#endif

	// Create a SOCKET for connecting to server
	SOCKET f_Socket = m_ClientSS->m_vec_Socket[f_PushID];

	int iResult = 0;

	char* f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);

	bool f_Closing = acScan() ? false : true;

	while(f_Closing == false)
		{
		if(iResult > 0)
			{
			f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);
			}

		iResult = recv(f_Socket, f_recvbuff, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			std::shared_ptr<std::string> f_Message = std::make_shared<std::string>(f_recvbuff);

			char f_FirstCharacter = f_Message->at(0);

			if(f_FirstCharacter == 'K')
				{
				f_Closing = true;
				}
			else
				{
				m_PacketMutex.lock();

				m_vec_PushPacket[f_PushID].push_back(f_Message);

				m_PacketMutex.unlock();

				if(f_Closing == false)
					{
					f_Closing = acScheduleUpdator(f_PushID);
					}
				}

			delete f_recvbuff;
			}
		else
			{
			int f_CountdownSeconds = f_Timer->acCalc();

			if(f_CountdownSeconds <= 0)
				{
				acCancel();
				}
			}

		if(f_Closing == false)
			{
			f_Closing = acScan() ? false : true;
			}
		}

	if(iResult <= 0)
		{
		delete f_recvbuff;
		}

	acUnlockPopulus(f_PushID);
}

void Schedular::DataFrame_Org(void)
{
	m_MainExited = false;

#ifdef ECOIN_DEBUG_BREAKS
	int f_LID = m_LID;
#endif

	m_PacketMutex.lock();
	m_vec_Packet.clear();
	m_PacketMutex.unlock();

	int iResult = 0;

	char* f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);

	m_MainFrameScan = true;

	while(m_MainFrameScan == true)
		{
		if(iResult > 0)
			{
			f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);
			}

		iResult = recv(m_ClientSS->m_Socket, f_recvbuff, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			std::shared_ptr<std::string> f_RecievedString = std::make_shared<std::string>(f_recvbuff);

			acScheduleUpdator();

			m_PacketMutex.lock();

			m_vec_Packet.push_back(f_RecievedString);

			m_PacketMutex.unlock();

			delete f_recvbuff;
			}
		}

	if(iResult <= 0)
		{
		delete f_recvbuff;
		}

	m_MainExited = true;
}

void Schedular::DataFrame_Mainstream_Org(void)
{
	m_MainstreamExited = false;

#ifdef ECOIN_DEBUG_BREAKS
	int f_LID = m_LID;
#endif

	m_MainstreamPacketMutex.lock();
	m_vec_Mainstream.clear();
	m_MainstreamPacketMutex.unlock();

	int iResult = 0;

	char* f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);

	m_MainstreamFrameScan = true;

	while(m_MainstreamFrameScan == true)
		{
		if(iResult > 0)
			{
			f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);
			}

		iResult = recv(m_ClientSS->m_MainstreamSocket, f_recvbuff, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			std::shared_ptr<std::string> f_RecievedString = std::make_shared<std::string>(f_recvbuff);

			acScheduleUpdator();

			m_MainstreamPacketMutex.lock();

			m_vec_Mainstream.push_back(f_RecievedString);

			m_MainstreamPacketMutex.unlock();

			delete f_recvbuff;
			}
		}

	if(iResult <= 0)
		{
		delete f_recvbuff;
		}

	m_MainstreamExited = true;
}

void Schedular::WalletSaveDataFrame_Org(void)
{
	m_WalletMainExited = false;

#ifdef ECOIN_DEBUG_BREAKS
	int f_LID = m_LID;
#endif

	m_PacketMutex.lock();
	m_vec_Packet.clear();
	m_PacketMutex.unlock();

	int iResult = 0;

	char* f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);

	m_WalletSaveScan = true;

	while(m_WalletSaveScan == true)
		{
		if(iResult > 0)
			{
			f_recvbuff = ag_ClearChar(DEFAULT_BUFLEN);
			}

		iResult = recv(m_ClientSS->m_WalletSaveSocket, f_recvbuff, DEFAULT_BUFLEN, 0);

		if(iResult > 0)
			{
			std::shared_ptr<std::string> f_RecievedString = std::make_shared<std::string>(f_recvbuff);

			acScheduleUpdator();

			m_PacketMutex.lock();

			m_vec_Packet.push_back(f_RecievedString);

			m_PacketMutex.unlock();

			delete f_recvbuff;
			}
		}

	if(iResult <= 0)
		{
		delete f_recvbuff;
		}

	m_WalletMainExited = true;
}

std::thread Schedular::DataFrameExt(std::shared_ptr<Scan_Timer> f_Timer)
{
	return std::thread([=] { DataFrameExt_Org(f_Timer); });
}

void Schedular::DataFrameExt_Org(std::shared_ptr<Scan_Timer> f_Timer)
{
	bool f_Closing = acScan() ? false : true;

	while(f_Closing == false)
		{
		m_PacketMutex.lock();

		if(m_vec_Packet.size() > 0)
			{
			std::shared_ptr<std::string> f_current_Packet = m_vec_Packet[0];

			m_PacketMutex.unlock();

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

#if 0
							f_Startof = f_Count + COUNT_AMT;
#endif
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));

							f_Startof = f_Count + COUNT_AMT;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int(0);

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				std::string f_EndCap = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(f_EndCap.c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'F')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + 1;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int(0);

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				std::string f_EndCap = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(f_EndCap.c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'O')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				std::string f_EndCap = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(f_EndCap.c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'G')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_ModifEntry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'R')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;

				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;
				std::vector<std::string> f_vec_ElementC;
				std::vector<std::string> f_vec_ElementD;
				std::vector<std::string> f_vec_ElementE;
				std::vector<std::string> f_vec_ElementF;
				std::vector<std::string> f_vec_ElementG;
				std::vector<std::string> f_vec_ElementH;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementC.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementD.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementE.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementF.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementG.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementH.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);
				f_ModifEntry->push_back(f_vec_ElementC);
				f_ModifEntry->push_back(f_vec_ElementD);
				f_ModifEntry->push_back(f_vec_ElementE);
				f_ModifEntry->push_back(f_vec_ElementF);
				f_ModifEntry->push_back(f_vec_ElementG);
				f_ModifEntry->push_back(f_vec_ElementH);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_ModifEntry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'M')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_Entry->push_back(f_vec_Element);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				f_Closing = true;
				}

			m_PacketMutex.lock();

			if(m_vec_Packet.size() > 0)
				{
				//message pump reorder packet array
				for(int f_Int = 0; f_Int < m_vec_Packet.size() - 1; f_Int++)
					{
					m_vec_Packet[f_Int] = m_vec_Packet[f_Int + 1];
					}

				m_vec_Packet.pop_back();

				m_PacketMutex.unlock();

				m_EntriesMtx.lock();

				//conditional entry reorder
				if(m_Entries.size() >= ECOIN_ENTRY_MAX)
					{
					int f_FarIndex = (m_Entries.size() - ECOIN_ENTRY_DEPTH);

					m_EntrantMtx.lock();

					for(int f_Jet = (ECOIN_ENTRY_REFRESH_DEPTH - ECOIN_ENTRY_DEPTH); f_Jet < ECOIN_ENTRY_REFRESH_DEPTH; f_Jet++)
						{
						for(int f_Int = 0; f_Int < ECOIN_ENTRY_DEPTH; f_Int++)
							{
							m_Entries[f_Jet + f_Int] = m_Entries[f_FarIndex + f_Int];
							m_Entrant[f_Jet + f_Int] = m_Entrant[f_FarIndex + f_Int];
							}
						}

					int f_Entries_size = m_Entries.size();

					for(int f_Jet = ECOIN_ENTRY_REFRESH_DEPTH; f_Jet < f_Entries_size; f_Jet++)
						{
						m_Entrant.pop_back();
						m_Entries.pop_back();
						}

					m_EntrantMtx.unlock();
					}

				m_EntriesMtx.unlock();
				}
			}
		else
			{
			m_PacketMutex.unlock();

			int f_CountdownSeconds = f_Timer->acCalc();

			if(f_CountdownSeconds <= 0)
				{
				acCancel();
				}
			}

		if(f_Closing == false)
			{
			f_Closing = acScan() ? false : true;
			}
		}

	if(m_WalletSave == false)
		{
		acUnlockPopulus(SCH_THREAD_EXT);
		}
	else
		{
		acUnlockPopulus(0);
		}
}

std::thread Schedular::PushFrameCombiner(std::shared_ptr<Scan_Timer> f_Timer)
{
	return std::thread([=] { PushFrameCombiner_Org(f_Timer); });
}

void Schedular::PushFrameCombiner_Org(std::shared_ptr<Scan_Timer> f_Timer)
{
#ifdef ECOIN_DEBUG_BREAKS
	int f_LID = m_LID;
#endif

	int f_currentPosition_FieldIDX = 0;
	int f_currentPosition_RecordIDX = 0;
	int f_currentPosition_Field_Count = 0;
	int f_proPosition_FieldIDX = 0;
	int f_proPosition_RecordIDX = 0;
	std::string f_proPosition_Incomplete_FC;
	std::string f_proPosition_Incomplete_MS;
	bool f_onFieldCount = false;

	std::shared_ptr<std::vector<std::string>> f_svec_Element = nullptr;

	std::vector<int> f_vec_StartNew;

	f_vec_StartNew.clear();

	m_PacketMutex.lock();

	for(int f_Jet = 0; f_Jet < m_vec_PushPacket.size(); f_Jet++)
		{
		f_vec_StartNew.push_back(0);
		}

	m_PacketMutex.unlock();

	m_PushResult_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

	int f_StartIDX = 0;
	int f_EndIDX = 0;
	int f_CountIDX = 0;

	std::string f_Prefix;
	std::string f_PreStartIDX;
	std::string f_PreEndIDX;
	std::string f_PreCountIDX;
	std::string f_PreSuffix;
	std::string f_String;

	int f_headMode = 0;
	bool f_Pref = false;
	bool f_EndFound = false;
	int f_Result_Non_Count = 0;
	bool f_ResultFound = false;
	bool f_Closing = false;

	while(f_Closing == false)
		{
		m_PacketMutex.lock();

		if((m_vec_PushPacket[m_PushReceiveFgr].size() > 0) && (f_ResultFound == false))
			{
			f_Result_Non_Count = 0;

			m_PushReceiveFgr = 0;

			f_ResultFound = true;
			}

		if(f_ResultFound == true)
			{
			if(m_vec_PushPacket[m_PushReceiveFgr].size() > 0)
				{
				m_PacketMutex.unlock();

				std::shared_ptr<std::string> f_current_Packet = m_vec_PushPacket[m_PushReceiveFgr][0];

				if(f_current_Packet->at(0) == 'F')
					{
					int iResult = f_current_Packet->length();

						////////////
					   // Buffer
					  //
					 //
					std::string f_Prefix;
					std::string f_String;

					int f_headMode = 0;
					int f_Startof = 0;
					bool f_Pref = false;
					for(int f_Count = 1; f_Count < iResult; f_Count++)
						{
						if(f_current_Packet->at(f_Count) == ':')
							{
							f_headMode++;

							if(f_headMode == 1)
								{
								f_Pref = true;

								f_Startof = f_Count + 1;
								}
							}
						else
							{
							if(f_headMode == 0)
								{
								f_Prefix.push_back(f_current_Packet->at(f_Count));
								}
							}

						if((f_headMode >= 1) && (f_Pref == false))
							{
							f_String.push_back(f_current_Packet->at(f_Count));
							}

						f_Pref = false;
						}

					iResult = iResult - f_Startof;

					int* f_Cy = new int(0);

					int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

					std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

					if(f_RecordCount > 0)
						{
						for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
							{
							std::vector<std::string> f_vec_Element;

							int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

							for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
								{
								f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
								}

							f_Entry->push_back(f_vec_Element);
							}
						}
					else
						{
						std::vector<std::string> f_vec_Element;

						f_vec_Element.push_back(std::string("0"));

						f_Entry->push_back(f_vec_Element);
						}

					m_EntriesMtx.lock();
					m_Entries.push_back(f_Entry);
					m_EntriesMtx.unlock();

					m_EntrantMtx.lock();
					m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
					m_EntrantMtx.unlock();

					m_PacketMutex.lock();

					for(int f_XY = 0; f_XY < m_vec_PushPacket[m_PushReceiveFgr].size() - 1; f_XY++)
						{
						m_vec_PushPacket[m_PushReceiveFgr][f_XY] = m_vec_PushPacket[m_PushReceiveFgr][f_XY + 1];
						}

					m_vec_PushPacket[m_PushReceiveFgr].pop_back();

					m_PacketMutex.unlock();
					}
				else
					{
					int f_StartNew = f_vec_StartNew[m_PushReceiveFgr];

					if(f_StartNew < 0)
						{
						f_StartNew = 0;
						}

					int iResult = f_current_Packet->length();

					if(iResult > DEFAULT_BUFLEN)
						{
						iResult = DEFAULT_BUFLEN;
						}

					if((f_current_Packet->at(f_StartNew) == 'E') && (f_proPosition_RecordIDX == 0))
						{
						  /////////////////////////////////
						 // Element Procedure
						// START 'E' PACKAGE [0-30]
						f_Prefix.clear();
						f_PreStartIDX.clear();
						f_PreEndIDX.clear();
						f_PreCountIDX.clear();
						f_PreSuffix.clear();

						f_headMode = 0;

						f_Pref = false;

						f_StartNew++;
						}

					//clear string
					f_String.clear();
					f_EndFound = false;
				
					   /////////////////////////////////////
					  // Push MultiPart-Message Combiner
					 // Element Procedure
					// PRODUCE 'E' PACKAGE [X-30]
					for(int f_Count = f_StartNew; f_Count < iResult; f_Count++)
						{
						char f_CharC = f_current_Packet->at(f_Count);

						if(f_Pref == false)
							{
							if(f_CharC == ':')
								{
								f_headMode++;
								}
							else if(((f_CharC >= '0') && (f_CharC <= '9')) || ((f_CharC >= 'a') && (f_CharC <= 'z')) || ((f_CharC >= 'A') && (f_CharC <= 'Z')))
								{
								switch(f_headMode)
									{
									case 0:
										{
										f_Prefix.push_back(f_CharC);
										}break;

									case 1:
										{
										f_PreStartIDX.push_back(f_CharC);
										}break;

									case 2:
										{
										f_PreEndIDX.push_back(f_CharC);
										}break;

									case 3:
										{
										f_PreCountIDX.push_back(f_CharC);
										}break;

									case 4:
										{
										f_PreSuffix.push_back(f_CharC);
										}break;

									default:
										{
										f_String.push_back(f_CharC);

										f_Pref = true;
										}
									}
								}
							else
								{
								throw;
								}
							}
						else
							{
							if(f_CharC == '#')
								{
								if(f_Count >= iResult - 1)
									{
									f_StartNew = iResult;

									f_Count = iResult;

									iResult = f_String.length();

									f_EndFound = true;
									}
								else
									{
									f_StartNew = f_Count + 1;

									f_Count = iResult;
									}
								}
							else if(f_CharC == ':')
								{
								f_String.push_back(f_CharC);
								}
							else if(f_CharC == '-')
								{
								f_String.push_back(f_CharC);
								}
							else if(f_CharC == '.')
								{
								f_String.push_back(f_CharC);
								}
							else if((f_CharC >= '0') && (f_CharC <= '9'))
								{
								f_String.push_back(f_CharC);
								}
							else if((f_CharC >= 'a') && (f_CharC <= 'z'))
								{
								f_String.push_back(f_CharC);
								}
							else if((f_CharC >= 'A') && (f_CharC <= 'Z'))
								{
								f_String.push_back(f_CharC);
								}
							else
								{
								throw;
								}
							}

						if((f_Count == iResult - 1) && (f_EndFound == false))
							{
							f_StartNew = iResult;

							f_Count = iResult;

							iResult = f_String.length();
							}
						}

					f_StartIDX = ::atoi(f_PreStartIDX.c_str());
					f_EndIDX = ::atoi(f_PreEndIDX.c_str());
					f_CountIDX = ::atoi(f_PreCountIDX.c_str());

					int* f_Cy = new int;

					*(f_Cy) = 0;

					if(m_PushResult_Entry->size() != f_CountIDX)
						{
						m_PushResult_Entry->resize(f_CountIDX);
						}

					int f_FieldCount = 0;
					int f_RecordCount = f_EndIDX - f_StartIDX;
			
					bool f_OnLine = true;

					int f_CycleStart = 0;
					int f_CycleEnd = f_RecordCount;

					if(f_proPosition_RecordIDX > 0)
						{
						f_currentPosition_RecordIDX = f_proPosition_RecordIDX;

						f_CycleStart = f_proPosition_RecordIDX;
						f_CycleEnd = f_EndIDX;
						}
					else
						{
						f_CycleStart += f_StartIDX;
						f_CycleEnd = f_EndIDX;
						}

					if(f_RecordCount > 0)
						{
						for(int f_RecCount = f_CycleStart; (f_RecCount < f_CycleEnd) && (f_OnLine == true); f_RecCount++)
							{
							std::shared_ptr<std::vector<std::string>> f_vec_Element = std::make_shared<std::vector<std::string>>();

							bool f_isLastof = false;

							if(f_proPosition_FieldIDX == 0)
								{
								std::string f_StringCount = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

								if(f_StringCount.at(f_StringCount.length() - 1) != '&')
									{
									f_FieldCount = ::atoi(f_StringCount.c_str());

									f_currentPosition_FieldIDX = 0;
									f_currentPosition_Field_Count = f_FieldCount;

									for(int f_FldCount = 0; (f_FldCount < f_FieldCount) && (f_OnLine == true); f_FldCount++)
										{
										if((f_RecCount >= (f_CycleEnd - 1)) && (f_FldCount >= (f_FieldCount - 1)))
											{
											f_isLastof = true;
											}

										std::string f_StringField = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

										if(f_StringField.at(f_StringField.length() - 1) != '&')
											{
											f_vec_Element->push_back(f_StringField);

											f_currentPosition_FieldIDX++;
											}
										else
											{
											if(f_StringField.at(f_StringField.length() - 2) == '&')
												{
												f_OnLine = false;

												f_proPosition_Incomplete_MS.clear();

												for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
													{
													char f_C = f_StringField.at(f_Jet);

													if(f_C == ':')
														{
														f_Jet = f_StringField.length();
														}
													else
														{
														if(f_C != '&')
															{
															f_proPosition_Incomplete_MS.push_back(f_C);
															}
														}
													}

												f_vec_Element->push_back(f_proPosition_Incomplete_MS);

												f_proPosition_Incomplete_MS.clear();

												f_currentPosition_FieldIDX++;

												f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
												f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

												f_svec_Element = f_vec_Element;
												}
											else
												{
												f_OnLine = false;

												f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
												f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

												f_proPosition_Incomplete_MS.clear();

												for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
													{
													char f_C = f_StringField.at(f_Jet);

													if(f_C == ':')
														{
														f_Jet = f_StringField.length();
														}
													else
														{
														if(f_C != '&')
															{
															f_proPosition_Incomplete_MS.push_back(f_C);
															}
														}
													}

												f_svec_Element = f_vec_Element;
												}
											}
										}

									if((f_vec_Element->size() == f_FieldCount) && (f_OnLine == true))
										{
										int f_AdIndex = ::atoi(f_vec_Element->at(f_vec_Element->size() - 4).c_str());

										if(m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount)
											{
											f_AdIndex = f_RecCount;
											}
							
#ifdef ECOIN_DEBUG_BREAKS
										if((m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount) || (f_AdIndex < 0) || (f_AdIndex >= m_PushResult_Entry->size()))
											{
											__debugbreak();
											}
										else
											{
#endif

											if((f_AdIndex >= 0) && (f_AdIndex < f_CountIDX))
												{
												for(int f_XYZ = 0; f_XYZ < f_vec_Element->size(); f_XYZ++)
													{
													m_PushResult_Entry->at(f_AdIndex).push_back(f_vec_Element->at(f_XYZ));
													}

												f_currentPosition_RecordIDX = f_AdIndex + 1;

												f_proPosition_FieldIDX = 0;
												f_proPosition_RecordIDX = 0;

												f_svec_Element = nullptr;
												}
#ifdef ECOIN_DEBUG_BREAKS
											}
#endif
										}
									}
								else
									{
									if(f_StringCount.at(f_StringCount.length() - 2) == '&')
										{
										f_OnLine = false;

										f_proPosition_Incomplete_FC.clear();

										for(int f_Jet = 0; f_Jet < f_StringCount.length(); f_Jet++)
											{
											char f_C = f_StringCount.at(f_Jet);

											if(f_C == ':')
												{
												f_Jet = f_StringCount.length();
												}
											else
												{
												if(f_C != '&')
													{
													f_proPosition_Incomplete_FC.push_back(f_C);
													}
												}
											}

										f_FieldCount = ::atoi(f_proPosition_Incomplete_FC.c_str());

										f_proPosition_Incomplete_FC.clear();

										f_currentPosition_FieldIDX = 0;
										f_currentPosition_Field_Count = f_FieldCount;

										f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
										f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

										f_svec_Element = f_vec_Element;
										}
									else
										{
										f_OnLine = false;

										f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
										f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

										f_proPosition_Incomplete_FC.clear();

										for(int f_Jet = 0; f_Jet < f_StringCount.length(); f_Jet++)
											{
											char f_C = f_StringCount.at(f_Jet);

											if(f_C != '&')
												{
												f_proPosition_Incomplete_FC.push_back(f_C);
												}
											}

										f_svec_Element = f_vec_Element;
										}
									}
								}
							else
								{
								f_FieldCount = f_currentPosition_Field_Count;

								if(f_proPosition_Incomplete_FC.length() > 0)
									{
									std::string f_StringFieldCount = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

									if(f_StringFieldCount.length() > 0)
										{
										if(f_StringFieldCount.at(f_StringFieldCount.length() - 1) != '&')
											{
											std::string f_newFieldCount = f_proPosition_Incomplete_FC + f_StringFieldCount;

											f_FieldCount = ::atoi(f_newFieldCount.c_str());

											f_proPosition_Incomplete_MS.clear();
											f_proPosition_Incomplete_FC.clear();

											f_currentPosition_FieldIDX = 0;

											f_proPosition_FieldIDX = 0;
											f_proPosition_RecordIDX = 0;
											}
										else
											{
											if(f_StringFieldCount.at(f_StringFieldCount.length() - 2) == '&')
												{
												f_OnLine = false;

												f_proPosition_Incomplete_FC.clear();

												for(int f_Jet = 0; f_Jet < f_StringFieldCount.length(); f_Jet++)
													{
													char f_C = f_StringFieldCount.at(f_Jet);

													if(f_C == ':')
														{
														f_Jet = f_StringFieldCount.length();
														}
													else
														{
														if(f_C != '&')
															{
															f_proPosition_Incomplete_FC.push_back(f_C);
															}
														}
													}

												f_proPosition_Incomplete_MS.clear();
												f_proPosition_Incomplete_FC.clear();

												f_currentPosition_FieldIDX = 0;

												f_proPosition_FieldIDX = 0;
												f_proPosition_RecordIDX = 0;
												}
											else
												{
												f_OnLine = false;

												f_proPosition_FieldIDX = 0;
												f_proPosition_RecordIDX = 0;

												f_proPosition_Incomplete_FC.clear();

												for(int f_Jet = 0; f_Jet < f_StringFieldCount.length(); f_Jet++)
													{
													char f_C = f_StringFieldCount.at(f_Jet);

													if(f_C == ':')
														{
														f_Jet = f_StringFieldCount.length();
														}
													else
														{
														if(f_C != '&')
															{
															f_proPosition_Incomplete_MS.push_back(f_C);
															}
														}
													}
												}
											}
										}
									else
										{
										f_FieldCount = ::atoi(f_proPosition_Incomplete_FC.c_str());

										f_proPosition_Incomplete_MS.clear();
										f_proPosition_Incomplete_FC.clear();

										f_currentPosition_FieldIDX = 0;

										f_proPosition_FieldIDX = 0;
										f_proPosition_RecordIDX = 0;
										}
									}

								f_currentPosition_FieldIDX = f_proPosition_FieldIDX;

								for(int f_FldCount = f_proPosition_FieldIDX; (f_FldCount < f_FieldCount) && (f_OnLine == true); f_FldCount++)
									{
									if((f_RecCount >= (f_CycleEnd - 1)) && (f_FldCount >= (f_FieldCount - 1)))
										{
										f_isLastof = true;
										}

									std::string f_StringField = agsc_ReadElement_Sock_V15((char*)f_String.c_str(), f_Cy, iResult, f_isLastof);

									if(f_StringField.length() > 0)
										{
										if(f_StringField.at(f_StringField.length() - 1) != '&')
											{
											f_svec_Element->push_back(f_proPosition_Incomplete_MS + f_StringField);

											f_proPosition_Incomplete_MS.clear();
											f_proPosition_Incomplete_FC.clear();

											f_currentPosition_FieldIDX++;

											f_proPosition_FieldIDX = 0;
											f_proPosition_RecordIDX = 0;
											}
										else
											{
											if(f_StringField.at(f_StringField.length() - 1) != '&')
												{
												f_OnLine = false;

												f_svec_Element->push_back(f_proPosition_Incomplete_MS + f_StringField);

												f_proPosition_Incomplete_MS.clear();

												for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
													{
													char f_C = f_StringField.at(f_Jet);

													if(f_C == ':')
														{
														f_Jet = f_StringField.length();
														}
													else
														{
														if(f_C != '&')
															{
															f_proPosition_Incomplete_MS.push_back(f_C);
															}
														}
													}

												f_svec_Element->push_back(f_proPosition_Incomplete_MS);

												f_proPosition_Incomplete_MS.clear();
												f_proPosition_Incomplete_FC.clear();

												f_currentPosition_FieldIDX++;

												f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
												f_proPosition_RecordIDX = f_currentPosition_RecordIDX;
												}
											else
												{
												f_OnLine = false;

												f_proPosition_FieldIDX = f_currentPosition_FieldIDX;
												f_proPosition_RecordIDX = f_currentPosition_RecordIDX;

												f_proPosition_Incomplete_MS.clear();
												f_proPosition_Incomplete_FC.clear();

												for(int f_Jet = 0; f_Jet < f_StringField.length(); f_Jet++)
													{
													char f_C = f_StringField.at(f_Jet);

													if(f_C == ':')
														{
														f_Jet = f_StringField.length();
														}
													else
														{
														if(f_C != '&')
															{
															f_proPosition_Incomplete_MS.push_back(f_C);
															}
														}
													}
												}
											}
										}
									else
										{
										f_svec_Element->push_back(f_proPosition_Incomplete_MS);

										f_proPosition_Incomplete_MS.clear();
										f_proPosition_Incomplete_FC.clear();

										f_currentPosition_FieldIDX++;

										f_proPosition_FieldIDX = 0;
										f_proPosition_RecordIDX = 0;
										}
									}

								if((f_svec_Element->size() == f_FieldCount) && (f_OnLine == true))
									{
									int f_AdIndex = ::atoi(f_svec_Element.get()->at(f_svec_Element->size() - 4).c_str());

									if(m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount)
										{
										f_AdIndex = f_RecCount;
										}
							
#ifdef ECOIN_DEBUG_BREAKS
									if((m_PushResult_Entry->at(f_AdIndex).size() >= f_FieldCount) || (f_AdIndex < 0) || (f_AdIndex >= m_PushResult_Entry->size()))
										{
										__debugbreak();
										}
									else
										{
#endif

										if((f_AdIndex >= 0) && (f_AdIndex < f_CountIDX))
											{
											for(int f_XYZ = 0; f_XYZ < f_svec_Element->size(); f_XYZ++)
												{
												m_PushResult_Entry->at(f_AdIndex).push_back(f_svec_Element->at(f_XYZ));
												}

											f_currentPosition_RecordIDX = f_AdIndex + 1;

											f_proPosition_FieldIDX = 0;
											f_proPosition_RecordIDX = 0;

											f_svec_Element = nullptr;
											}
#ifdef ECOIN_DEBUG_BREAKS
										}
#endif
									}
								}
							}
						}
					else
						{
						std::vector<std::string> f_vec_Element;

						f_vec_Element.push_back(std::string("0"));
					
						m_PushResult_Entry->at(0).push_back(f_vec_Element[0]);

						f_proPosition_FieldIDX = 0;
						f_proPosition_RecordIDX = 0;
						f_currentPosition_RecordIDX = 0;
						f_currentPosition_FieldIDX = 0;

						f_svec_Element = nullptr;

						f_OnLine = true;
						}

					if((f_OnLine == true) && (f_EndFound == false))
						{
						f_vec_StartNew[m_PushReceiveFgr] = f_StartNew;

						m_PushReceiveFgr++;

						if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
							{
							m_PushReceiveFgr = 0;
							}
						}
					else
						{
						if(f_EndFound == false)
							{
							m_PacketMutex.lock();

							for(int f_XY = 0; f_XY < m_vec_PushPacket[m_PushReceiveFgr].size() - 1; f_XY++)
								{
								m_vec_PushPacket[m_PushReceiveFgr][f_XY] = m_vec_PushPacket[m_PushReceiveFgr][f_XY + 1];
								}

							m_vec_PushPacket[m_PushReceiveFgr].pop_back();

							m_PacketMutex.unlock();

							f_vec_StartNew[m_PushReceiveFgr] = 0;
							}
						else
							{
							m_PacketMutex.lock();

							for(int f_XY = 0; f_XY < m_vec_PushPacket[m_PushReceiveFgr].size() - 1; f_XY++)
								{
								m_vec_PushPacket[m_PushReceiveFgr][f_XY] = m_vec_PushPacket[m_PushReceiveFgr][f_XY + 1];
								}

							m_vec_PushPacket[m_PushReceiveFgr].pop_back();

							m_PacketMutex.unlock();

							f_vec_StartNew[m_PushReceiveFgr] = 0;
					
							m_PushReceiveFgr++;

							if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
								{
								m_PushReceiveFgr = 0;
								}
							}
						}

					//count determine win conditions
					bool f_FullUp = true;

					for(int f_Jet = 0; f_Jet < f_CountIDX; f_Jet++)
						{
						if(m_PushResult_Entry->at(f_Jet).size() != f_FieldCount)
							{
							f_FullUp = false;
							}
						}

					if(f_FullUp == true) //win conditions!
						{
						m_EntriesMtx.lock();
						m_Entries.push_back(m_PushResult_Entry);
						m_EntriesMtx.unlock();

						m_PushResult_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

						m_PushReceiveFgr = 0;

						int f_PossibleEntrant = ::atoi(f_PreSuffix.c_str());

						if(f_PossibleEntrant > ECOIN_ENTRY_MAX)
							{
							f_PossibleEntrant = f_PossibleEntrant - ECOIN_ENTRY_REFRESH_DEPTH;
							}

						m_Entrant.push_back(f_PossibleEntrant);

						m_PacketMutex.lock();

						for(int f_XY = 0; f_XY < m_vec_PushPacket.size(); f_XY++)
							{
							m_vec_PushPacket[f_XY].clear();

							f_vec_StartNew[f_XY] = 0;
							}

						m_PacketMutex.unlock();
						}

					delete f_Cy;
					}
				}
			else
				{
				m_PacketMutex.unlock();

				f_Result_Non_Count++;

				if(f_Result_Non_Count >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
					{
					f_ResultFound = false;

					m_PushReceiveFgr = 0;
					}
				else
					{
					m_PushReceiveFgr++;

					if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
						{
						m_PushReceiveFgr = 0;
						}
					}
				}
			}
		else
			{
			m_PacketMutex.unlock();

			m_PushReceiveFgr++;

			if(m_PushReceiveFgr >= ECOIN_ELEMENT_PUSH_THREAD_COUNT)
				{
				m_PushReceiveFgr = 0;
				}
			}
			
		if(f_Closing == false)
			{
			f_Closing = acScan() ? false : true;
			}
		}

	acUnlockPopulus(SCH_THREAD_COMBINER);
}

int Schedular::acNet_Client_Data_Gui(void)
{
	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		struct addrinfo *resultx = NULL, *ptrx = NULL, hintsx;

		ZeroMemory(&hintsx, sizeof(hintsx));

		hintsx.ai_family = AF_UNSPEC;
		hintsx.ai_socktype = SOCK_STREAM;
		hintsx.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
		int iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_BOARD_Gui.c_str(), &hintsx, &resultx);
#else
		int iResult = getaddrinfo("localhost", m_ClientSS->m_BOARD_Gui.c_str(), &hintsx, &resultx);
#endif

		if(iResult != 0)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}

		// Attempt to connect to an address until one succeeds
		for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
			{
			// Create a SOCKET for connecting to server
			SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif  //add debug message
				}

			// Connect to server.
			iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
			if(iResult == SOCKET_ERROR)
				{
				closesocket(f_Socket);

				f_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif
				}
			else
				{
#ifdef SCHEDULAR_BLOCKING_ON
				struct timeval tv;

				tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

				int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

				if(h_OK != 0)
					{
					int f_ErrorCode = WSAGetLastError();

					char* f_Char = ag_ClearChar(512);
					sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
					winrt::hstring f_String = StrUsingStr(std::string(f_Char));
					OutputDebugString(f_String.c_str());
					delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //error stated within output debug window \/
#endif
					}
#else
#if 0			//Blocking Mode
				u_long iMode = 0;
#else			//Non Blocking Mode
				u_long iMode = 1;
#endif

				int h_OK = ioctlsocket(f_Socket, FIONBIO, &iMode);

				if(h_OK != NO_ERROR)
					{
					__debugbreak();
					}
#endif
				}

			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif
				}
			else
				{
				m_ClientSS->m_vec_Socket.push_back(f_Socket);

				std::vector<std::shared_ptr<std::string>> f_vec_Str;

				m_vec_PushPacket.push_back(f_vec_Str);
				}

			break;
			}

		freeaddrinfo(resultx);
		}

	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		//Send Logon
		acSend_Logon((char*)g_Wallet->GetAdr().c_str(), 0, true, f_Jet + 1);
		}

	return 1;
}

int Schedular::acNet_Client_Data_Gui_Prep(void)
{
	m_ClientSS->m_Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

#ifdef ECOIN_DEBUG_BREAKS
	if(iResult != 0)
		{
		__debugbreak();
		}
#endif

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
	iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_PORT_Gui.c_str(), &hints, &result);
#else
	iResult = getaddrinfo("localhost", m_ClientSS->m_PORT_Gui.c_str(), &hints, &result);
#endif

	if(iResult != 0)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	SOCKET f_Socket;

	// Attempt to connect to an address until one succeeds
	for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
		// Create a SOCKET for connecting to server
		f_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		
		if(f_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}

		// Connect to server.
		iResult = connect(f_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(f_Socket);

			f_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif
			}
		else //ECN::SocketSet connection established
			{
#ifdef SCHEDULAR_BLOCKING_ON
			struct timeval tv;

			tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

			int h_OK = setsockopt(f_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

			if(h_OK != 0)
				{
				int f_ErrorCode = WSAGetLastError();

				char* f_Char = ag_ClearChar(512);
				sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
				winrt::hstring f_String = StrUsingStr(std::string(f_Char));
				OutputDebugString(f_String.c_str());
				delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //error stated within output debug window \/
#endif
				}
#else
#if 0		//Blocking Mode
			u_long iMode = 0;
#else		//Non Blocking Mode
			u_long iMode = 1;
#endif

			int h_OK = ioctlsocket(f_Socket, FIONBIO, &iMode);

			if(h_OK != NO_ERROR)
				{
				__debugbreak();
				}
#endif

			std::thread f_thread_Data(&Schedular::DataFrame_Org, this);

#ifdef SCH_THR_DETACH
			f_thread_Data.detach();
#endif
			}

		break;
		}

	freeaddrinfo(result);

	if(f_Socket == INVALID_SOCKET)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}
	else
		{
		m_ClientSS->m_Socket = f_Socket;
		}

	//Send Logon
	acSend_Logon((char*)g_Wallet->GetAdr().c_str(), 0, true, 0);

	return 1;
}

std::thread Schedular::DataFrame_GuiExt(std::shared_ptr<Scan_Timer> f_Timer)
{
	return std::thread([=] { DataFrame_GuiExt_Org(f_Timer); });
}

void Schedular::DataFrame_GuiExt_Org(std::shared_ptr<Scan_Timer> f_Timer)
{
	bool f_Closing = acScan() ? false : true;

	while(f_Closing == false)
		{
		m_PacketMutex.lock();

		if(m_vec_Packet.size() > 0)
			{
			std::shared_ptr<std::string> f_current_Packet = m_vec_Packet[0];

			m_PacketMutex.unlock();

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

#if 0
							f_Startof = f_Count + COUNT_AMT;
#endif
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));

							f_Startof = f_Count + COUNT_AMT;
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'F')
				{
				int iResult = f_current_Packet->length();

					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + 1;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int(0);

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				std::string f_EndCap = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(f_EndCap.c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'G')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_ModifEntry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'R')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_ModifEntry = std::make_shared<std::vector<std::vector<std::string>>>();

				for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
					f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

					f_ModifEntry->push_back(f_vec_Element);
					}

				std::vector<std::string> f_vec_ElementA;
				std::vector<std::string> f_vec_ElementB;
				std::vector<std::string> f_vec_ElementC;
				std::vector<std::string> f_vec_ElementD;
				std::vector<std::string> f_vec_ElementE;
				std::vector<std::string> f_vec_ElementF;
				std::vector<std::string> f_vec_ElementG;
				std::vector<std::string> f_vec_ElementH;

				f_vec_ElementA.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementB.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementC.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementD.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementE.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementF.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementG.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_vec_ElementH.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));

				f_ModifEntry->push_back(f_vec_ElementA);
				f_ModifEntry->push_back(f_vec_ElementB);
				f_ModifEntry->push_back(f_vec_ElementC);
				f_ModifEntry->push_back(f_vec_ElementD);
				f_ModifEntry->push_back(f_vec_ElementE);
				f_ModifEntry->push_back(f_vec_ElementF);
				f_ModifEntry->push_back(f_vec_ElementG);
				f_ModifEntry->push_back(f_vec_ElementH);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_ModifEntry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'M')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + COUNT_AMT;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
				f_Entry->push_back(f_vec_Element);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				f_Closing = true;
				}

			m_PacketMutex.lock();

			if(m_vec_Packet.size() > 0)
				{
				//message pump reorder packet array
				for(int f_Int = 0; f_Int < m_vec_Packet.size() - 1; f_Int++)
					{
					m_vec_Packet[f_Int] = m_vec_Packet[f_Int + 1];
					}

				m_vec_Packet.pop_back();

				m_PacketMutex.unlock();
			
				m_EntriesMtx.lock();

				//conditional entry reorder
				//[101]
				if(m_Entries.size() > ECOIN_ENTRY_MAX)
					{
					//[15]
					int f_Index = (ECOIN_ENTRY_REFRESH_DEPTH - ECOIN_ENTRY_DEPTH);

					//[96]
					int f_FarIndexSize = (m_Entries.size() - ECOIN_ENTRY_DEPTH);

					m_EntrantMtx.lock();

					//[0, 1, 2, 3, 4]
					for(int f_Int = 0; f_Int < ECOIN_ENTRY_DEPTH; f_Int++)
						{
						m_Entries[f_Index + f_Int] = m_Entries[f_FarIndexSize + f_Int];
						m_Entrant[f_Index + f_Int] = m_Entrant[f_FarIndexSize + f_Int];
						}

					//[101]
					int f_Entries_size = m_Entries.size();

					for(int f_JetPop = ECOIN_ENTRY_REFRESH_DEPTH; f_JetPop < f_Entries_size; f_JetPop++)
						{
						m_Entrant.pop_back();
						m_Entries.pop_back();
						}

					m_EntrantMtx.unlock();
					}

				m_EntriesMtx.unlock();
				}
			}
		else
			{
			m_PacketMutex.unlock();

			int f_CountdownSeconds = f_Timer->acCalc();

			if(f_CountdownSeconds <= 0)
				{
				acCancel();
				}
			}

		if(f_Closing == false)
			{
			f_Closing = acScan() ? false : true;
			}
		}

	acUnlockPopulus(SCH_THREAD_EXT);
}

int Schedular::acNet_Client_Data_Angel_Prep(void)
{
	m_ClientSS->m_Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	WSADATA wsaData;

	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if(iResult != 0)
		{
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
	iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_PORT_Angel.c_str(), &hints, &result);
#else
	iResult = getaddrinfo("localhost", m_ClientSS->m_PORT_Angel.c_str(), &hints, &result);
#endif

	if(iResult != 0)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	// Attempt to connect to an address until one succeeds
	for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
		// Create a SOCKET for connecting to server
		m_ClientSS->m_Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		
		if(m_ClientSS->m_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}

		// Connect to server.
		iResult = connect(m_ClientSS->m_Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(m_ClientSS->m_Socket);

			m_ClientSS->m_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}
		else
			{
#ifdef SCHEDULAR_BLOCKING_ON
			struct timeval tv;

			tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

			int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

			if(h_OK != 0)
				{
				int f_ErrorCode = WSAGetLastError();

				char* f_Char = ag_ClearChar(512);
				sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
				winrt::hstring f_String = StrUsingStr(std::string(f_Char));
				OutputDebugString(f_String.c_str());
				delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //error stated within output debug window \/
#endif
				}
#else
#if 0			//Blocking Mode
			u_long iMode = 0;
#else			//Non Blocking Mode
			u_long iMode = 1;
#endif

			int h_OK = ioctlsocket(m_ClientSS->m_Socket, FIONBIO, &iMode);

			if(h_OK != NO_ERROR)
				{
				__debugbreak();
				}
#endif

			std::thread f_thread_DataDF(&Schedular::DataFrame_Org, this);

#ifdef SCH_THR_DETACH
			f_thread_DataDF.detach();
#endif
			}

		break;
		}

	freeaddrinfo(result);

	if(m_ClientSS->m_Socket == INVALID_SOCKET)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	acSend_Logon((char*)g_Wallet->GetAdr().c_str(), 0, true, 0);

	return 1;
}

int Schedular::acNet_Client_Data_Angel(void)
{
	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		struct addrinfo *resultx = NULL, *ptrx = NULL, hintsx;

		ZeroMemory(&hintsx, sizeof(hintsx));

		hintsx.ai_family = AF_UNSPEC;
		hintsx.ai_socktype = SOCK_STREAM;
		hintsx.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
		int iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_BOARD_Angel.c_str(), &hintsx, &resultx);
#else
		int iResult = getaddrinfo("localhost", m_ClientSS->m_BOARD_Angel.c_str(), &hintsx, &resultx);
#endif

		if(iResult != 0)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}

		// Attempt to connect to an address until one succeeds
		for(ptrx = resultx; ptrx != NULL; ptrx = ptrx->ai_next)
			{
			// Create a SOCKET for connecting to server
			SOCKET f_Socket = socket(ptrx->ai_family, ptrx->ai_socktype, ptrx->ai_protocol);
		
			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif			//add debug message
				}

			// Connect to server.
			iResult = connect(f_Socket, ptrx->ai_addr, (int)ptrx->ai_addrlen);
		
			if(iResult == SOCKET_ERROR)
				{
				closesocket(f_Socket);

				f_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif			//add debug message
				}
			else
				{
#ifdef SCHEDULAR_BLOCKING_ON
				struct timeval tv;

				tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

				int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

				if(h_OK != 0)
					{
					int f_ErrorCode = WSAGetLastError();

					char* f_Char = ag_ClearChar(512);
					sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
					winrt::hstring f_String = StrUsingStr(std::string(f_Char));
					OutputDebugString(f_String.c_str());
					delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //error stated within output debug window \/
#endif
					}
#else
#if 0			//Blocking Mode
				u_long iMode = 0;
#else			//Non Blocking Mode
				u_long iMode = 1;
#endif

				int h_OK = ioctlsocket(m_ClientSS->m_Socket, FIONBIO, &iMode);

				if(h_OK != NO_ERROR)
					{
					__debugbreak();
					}
#endif
				}

			if(f_Socket == INVALID_SOCKET)
				{
				WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif			//add debug message
				}
			else
				{
				m_ClientSS->m_vec_Socket.push_back(f_Socket);

				std::vector<std::shared_ptr<std::string>> f_vec_Str;

				m_vec_PushPacket.push_back(f_vec_Str);
				}

			break;
			}

		freeaddrinfo(resultx);
		}

	for(int f_Jet = 0; f_Jet < ECOIN_ELEMENT_PUSH_THREAD_COUNT; f_Jet++)
		{
		//Send Logon
		acSend_Logon((char*)g_Wallet->GetAdr().c_str(), 0, true, f_Jet + 1);
		}

	return 1;
}

int Schedular::acNet_Client_Mainstream_Angel(void)
{
	struct addrinfo *resultmainx = NULL, *ptrmainx = NULL, hintsmainx;

	ZeroMemory(&hintsmainx, sizeof(hintsmainx));

	hintsmainx.ai_family = AF_UNSPEC;
	hintsmainx.ai_socktype = SOCK_STREAM;
	hintsmainx.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
#ifndef SCHEDULAR_LOCAL_MODE
	int iResult = getaddrinfo(m_ClientSS->m_IP.c_str(), m_ClientSS->m_Mainstream_Angel.c_str(), &hintsmainx, &resultmainx);
#else
	int iResult = getaddrinfo("localhost", m_ClientSS->m_Mainstream_Angel.c_str(), &hintsmainx, &resultmainx);
#endif

	if(iResult != 0)
		{
		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif  //add debug message
		}

	// Attempt to connect to an address until one succeeds
	for(ptrmainx = resultmainx; ptrmainx != NULL; ptrmainx = ptrmainx->ai_next)
		{
		// Create a SOCKET for connecting to server
		SOCKET f_Socket = socket(ptrmainx->ai_family, ptrmainx->ai_socktype, ptrmainx->ai_protocol);
		
		if(f_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}

		// Connect to server.
		iResult = connect(f_Socket, ptrmainx->ai_addr, (int)ptrmainx->ai_addrlen);
		
		if(iResult == SOCKET_ERROR)
			{
			closesocket(f_Socket);

			f_Socket = INVALID_SOCKET;

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif  //add debug message
			}
		else
			{
#ifdef SCHEDULAR_BLOCKING_ON
			struct timeval tv;

			tv.tv_sec = SCHEDULE_TIME_OUT_SECONDS * SCHEDULE_MILLI_MUL;

			int h_OK = setsockopt(m_ClientSS->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval));

			if(h_OK != 0)
				{
				int f_ErrorCode = WSAGetLastError();

				char* f_Char = ag_ClearChar(512);
				sprintf(f_Char, "setsockopt ErrorCode == %i\n", f_ErrorCode);
				winrt::hstring f_String = StrUsingStr(std::string(f_Char));
				OutputDebugString(f_String.c_str());
				delete f_Char;

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //error stated within output debug window \/
#endif
				}
#else
#if 0			//Blocking Mode
			u_long iMode = 0;
#else			//Non Blocking Mode
			u_long iMode = 1;
#endif

			int h_OK = ioctlsocket(f_Socket, FIONBIO, &iMode);

			if(h_OK != NO_ERROR)
				{
				__debugbreak();
				}
#endif
			}

		if(f_Socket == INVALID_SOCKET)
			{
			WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
			__debugbreak();
#endif		//add debug message
			}
		else
			{
			m_ClientSS->m_MainstreamSocket = f_Socket;

			std::thread f_thread_DataMS(&Schedular::DataFrame_Mainstream_Org, this);

#ifdef SCH_THR_DETACH
			f_thread_DataMS.detach();
#endif
			}

		break;
		}

	freeaddrinfo(resultmainx);

	//Send Logon
	acSend_Logon_Mainstream((char*)g_Wallet->GetAdr().c_str(), 0, true);

	return 1;
}

std::thread Schedular::DataFrame_AngelExt(std::shared_ptr<Scan_Timer> f_Timer)
{
	return std::thread([=] { DataFrame_AngelExt_Org(f_Timer); });
}

void Schedular::DataFrameExt_Mainstream_Org(std::shared_ptr<Scan_Timer> f_Timer)
{
	bool f_Closing = acScan() ? false : true;

	while(f_Closing == false)
		{
		m_MainstreamPacketMutex.lock();

		if(m_vec_Mainstream.size() > 0)
			{
			std::shared_ptr<std::string> f_current_Packet = m_vec_Mainstream[0];

			m_MainstreamPacketMutex.unlock();

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_MainstreamEntriesMtx.lock();
				m_Mainstream_Entries.push_back(f_Entry);
				m_MainstreamEntriesMtx.unlock();

				m_MainstreamEntrantMtx.lock();
				m_Mainstream_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
				m_MainstreamEntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'F')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + 1;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int(0);

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_MainstreamEntriesMtx.lock();
				m_Mainstream_Entries.push_back(f_Entry);
				m_MainstreamEntriesMtx.unlock();

				std::string f_EndCap = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_MainstreamEntrantMtx.lock();
				m_Mainstream_Entrant.push_back(::atoi(f_EndCap.c_str()));
				m_MainstreamEntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'M')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
				f_Entry->push_back(f_vec_Element);

				m_MainstreamEntriesMtx.lock();
				m_Mainstream_Entries.push_back(f_Entry);
				m_MainstreamEntriesMtx.unlock();

				m_MainstreamEntrantMtx.lock();
				m_Mainstream_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
				m_MainstreamEntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'A')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				g_QAccountID = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				//////////////////////////////////////////////////////
				//WARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWARNING
				//ADD THIS
				//g_qa_Radar = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str();
				//g_qa_ClientTime = 0;
				//g_qa_FrameRateLimiter = 0;
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				f_Closing = true;
				}

			m_MainstreamPacketMutex.lock();

			if(m_vec_Mainstream.size() > 0)
				{
				//message pump reorder packet array
				for(int f_Int = 0; f_Int < m_vec_Mainstream.size() - 1; f_Int++)
					{
					m_vec_Mainstream[f_Int] = m_vec_Mainstream[f_Int + 1];
					}

				m_vec_Mainstream.pop_back();

				m_MainstreamPacketMutex.unlock();

				m_MainstreamEntriesMtx.lock();

				//conditional entry reorder
				if(m_Mainstream_Entries.size() > ECOIN_ENTRY_MAX)
					{
					int f_FarIndex = (m_Mainstream_Entries.size() - ECOIN_ENTRY_DEPTH);

					m_MainstreamEntrantMtx.lock();

					for(int f_Jet = (ECOIN_ENTRY_REFRESH_DEPTH - ECOIN_ENTRY_DEPTH); f_Jet < ECOIN_ENTRY_REFRESH_DEPTH; f_Jet++)
						{
						for(int f_Int = 0; f_Int < ECOIN_ENTRY_DEPTH; f_Int++)
							{
							m_Mainstream_Entries[f_Jet + f_Int] = m_Mainstream_Entries[f_FarIndex + f_Int];
							m_Mainstream_Entrant[f_Jet + f_Int] = m_Mainstream_Entrant[f_FarIndex + f_Int];
							}
						}

					int f_Mainstream_Entries_size = m_Entries.size();

					for(int f_Jet = ECOIN_ENTRY_REFRESH_DEPTH; f_Jet < f_Mainstream_Entries_size; f_Jet++)
						{
						m_Mainstream_Entrant.pop_back();
						m_Mainstream_Entries.pop_back();
						}

					m_MainstreamEntrantMtx.unlock();
					}

				m_MainstreamEntriesMtx.unlock();
				}
			}
		else
			{
			m_MainstreamPacketMutex.unlock();

			int f_CountdownSeconds = f_Timer->acCalc();

			if(f_CountdownSeconds <= 0)
				{
				acCancel();
				}
			}

		if(f_Closing == false)
			{
			f_Closing = acScan() ? false : true;
			}
		}

	acUnlockPopulus(SCH_THREAD_MAINSTREAM);
}

std::thread Schedular::DataFrameExt_Mainstream(std::shared_ptr<Scan_Timer> f_Timer)
{
	return std::thread([=] { DataFrameExt_Mainstream_Org(f_Timer); });
}

void Schedular::DataFrame_AngelExt_Org(std::shared_ptr<Scan_Timer> f_Timer)
{
	bool f_Closing = acScan() ? false : true;

	while(f_Closing == false)
		{
		m_PacketMutex.lock();

		if(m_vec_Packet.size() > 0)
			{
			std::shared_ptr<std::string> f_current_Packet = m_vec_Packet[0];

			m_PacketMutex.unlock();

			int iResult = f_current_Packet->length();

			if(f_current_Packet->at(0) == 'D')
				{
				   ////////////
				  // Buffer
				 //
				//
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'F')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_Prefix;
				std::string f_String;

				int f_headMode = 0;
				int f_Startof = 0;
				bool f_Pref = false;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					if(f_current_Packet->at(f_Count) == ':')
						{
						f_headMode++;

						if(f_headMode == 1)
							{
							f_Pref = true;

							f_Startof = f_Count + 1;
							}
						}
					else
						{
						if(f_headMode == 0)
							{
							f_Prefix.push_back(f_current_Packet->at(f_Count));
							}
						}

					if((f_headMode >= 1) && (f_Pref == false))
						{
						f_String.push_back(f_current_Packet->at(f_Count));
						}

					f_Pref = false;
					}

				iResult = iResult - f_Startof;

				int* f_Cy = new int(0);

				int f_RecordCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();

				if(f_RecordCount > 0)
					{
					for(int f_RecCount = 0; f_RecCount < f_RecordCount; f_RecCount++)
						{
						std::vector<std::string> f_vec_Element;

						int f_FieldCount = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult).c_str());

						for(int f_FldCount = 0; f_FldCount < f_FieldCount; f_FldCount++)
							{
							f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult));
							}

						f_Entry->push_back(f_vec_Element);
						}
					}
				else
					{
					std::vector<std::string> f_vec_Element;

					f_vec_Element.push_back(std::string("0"));

					f_Entry->push_back(f_vec_Element);
					}

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				std::string f_EndCap = agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy, iResult);

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(f_EndCap.c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'M')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				std::shared_ptr<std::vector<std::vector<std::string>>> f_Entry = std::make_shared<std::vector<std::vector<std::string>>>();
				std::vector<std::string> f_vec_Element;

				f_vec_Element.push_back(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy));
				f_Entry->push_back(f_vec_Element);

				m_EntriesMtx.lock();
				m_Entries.push_back(f_Entry);
				m_EntriesMtx.unlock();

				m_EntrantMtx.lock();
				m_Entrant.push_back(::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str()));
				m_EntrantMtx.unlock();
				}
			else if(f_current_Packet->at(0) == 'A')
				{
					////////////
				   // Buffer
				  //
				 //
				std::string f_String;
				for(int f_Count = 1; f_Count < iResult; f_Count++)
					{
					f_String.push_back(f_current_Packet->at(f_Count));
					}

				int* f_Cy = new int;
				*(f_Cy) = 0;

				g_QAccountID = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str(), f_Cy).c_str());

				//////////////////////////////////////////////////////
				//WARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWARNING
				//ADD THIS
				//g_qa_Radar = ::atoi(agsc_ReadElement_Sock((char*)f_String.c_str();
				//g_qa_ClientTime = 0;
				//g_qa_FrameRateLimiter = 0;
				}
			else if(f_current_Packet->at(0) == 'K')
				{
				f_Closing = true;
				}

			m_PacketMutex.lock();

			if(m_vec_Packet.size() > 0)
				{
				//message pump reorder packet array
				for(int f_Int = 0; f_Int < m_vec_Packet.size() - 1; f_Int++)
					{
					m_vec_Packet[f_Int] = m_vec_Packet[f_Int + 1];
					}

				m_vec_Packet.pop_back();

				m_PacketMutex.unlock();

				m_EntriesMtx.lock();

				//conditional entry reorder
				if(m_Entries.size() > ECOIN_ENTRY_MAX)
					{
					int f_FarIndex = (m_Entries.size() - ECOIN_ENTRY_DEPTH);

					m_EntrantMtx.lock();

					for(int f_Jet = (ECOIN_ENTRY_REFRESH_DEPTH - ECOIN_ENTRY_DEPTH); f_Jet < ECOIN_ENTRY_REFRESH_DEPTH; f_Jet++)
						{
						for(int f_Int = 0; f_Int < ECOIN_ENTRY_DEPTH; f_Int++)
							{
							m_Entries[f_Jet + f_Int] = m_Entries[f_FarIndex + f_Int];
							m_Entrant[f_Jet + f_Int] = m_Entrant[f_FarIndex + f_Int];
							}
						}

					int f_Entries_size = m_Entries.size();

					for(int f_Jet = ECOIN_ENTRY_REFRESH_DEPTH; f_Jet < f_Entries_size; f_Jet++)
						{
						m_Entrant.pop_back();
						m_Entries.pop_back();
						}

					m_EntrantMtx.unlock();
					}

				m_EntriesMtx.unlock();
				}
			}
		else
			{
			m_PacketMutex.unlock();

			int f_CountdownSeconds = f_Timer->acCalc();

			if(f_CountdownSeconds <= 0)
				{
				acCancel();
				}
			}

		if(f_Closing == false)
			{
			f_Closing = acScan() ? false : true;
			}
		}

	acUnlockPopulus(SCH_THREAD_EXT);
}

std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy, int iResult)
{
	bool f_Scan = true;
	char f_A[4];

	std::string f_Res = "";

	if((*(f_Cy) + 4) >= iResult)
		{
		return "";
		}

	f_A[0] = f_Charpntr[*(f_Cy)];
	f_A[1] = f_Charpntr[*(f_Cy) + 1];
	f_A[2] = f_Charpntr[*(f_Cy) + 2];
	f_A[3] = f_Charpntr[*(f_Cy) + 3];

	*(f_Cy) += 4;

	if (f_A[0] == ':' &&
		f_A[1] == ':' &&
		f_A[2] == ':' &&
		f_A[3] == ':')
		{
		return "";
		}
	else
		{
		if(f_A[0] != ':')
			{
			f_Res.push_back(f_A[0]);
			}
		}

	while(f_Scan)
		{
		if((*(f_Cy) + 1) >= iResult)
			{
			return "";
			}

		f_A[0] = f_A[1];
		f_A[1] = f_A[2];
		f_A[2] = f_A[3];
		f_A[3] = f_Charpntr[*(f_Cy)];

		*(f_Cy) += 1;

		if (f_A[0] == ':' &&
			f_A[1] == ':' &&
			f_A[2] == ':' &&
			f_A[3] == ':')
			{
			f_Scan = false;
			}
		else
			{
			if(f_A[0] != ':')
				{
				f_Res.push_back(f_A[0]);
				}
			}
		}

	return f_Res;
}

std::string agsc_ReadElement_Sock(char* f_Charpntr, int* f_Cy)
{
	bool f_Scan = true;
	char f_A[4];

	std::string f_Res = "";

	f_A[0] = f_Charpntr[*(f_Cy)];
	f_A[1] = f_Charpntr[*(f_Cy) + 1];
	f_A[2] = f_Charpntr[*(f_Cy) + 2];
	f_A[3] = f_Charpntr[*(f_Cy) + 3];

	*(f_Cy) += 4;

	if (f_A[0] == ':' &&
		f_A[1] == ':' &&
		f_A[2] == ':' &&
		f_A[3] == ':')
		{
		return "";
		}
	else
		{
		if(f_A[0] != ':')
			{
			f_Res.push_back(f_A[0]);
			}
		}

	while(f_Scan == true)
		{
		f_A[0] = f_A[1];
		f_A[1] = f_A[2];
		f_A[2] = f_A[3];
		f_A[3] = f_Charpntr[*(f_Cy)];

		*(f_Cy) += 1;

		if (f_A[0] == ':' &&
			f_A[1] == ':' &&
			f_A[2] == ':' &&
			f_A[3] == ':')
			{
			f_Scan = false;
			}
		else
			{
			if(f_A[0] != ':')
				{
				f_Res.push_back(f_A[0]);
				}
			}
		}

	return f_Res;
}

std::string agsc_ReadElement_Sock_V15(char* f_Charpntr, int* f_Cy, int iResult, bool f_isLastof)
{
	bool f_Scan = true;
	char f_A[4];

	std::string f_Res = "";

	//added beef to the read socket
	std::string f_ReturnString = "";

	for(int f_Jet = 0; f_Jet < 4; f_Jet++)
		{
		int f_S = *(f_Cy) + f_Jet;

		if(f_S < iResult)
			{
			f_ReturnString.push_back(f_Charpntr[f_S]);
			}
		else
			{
			f_ReturnString.push_back('&');

			*(f_Cy) += f_Jet;

			return f_ReturnString;
			}
		}

	f_ReturnString.clear();

	f_A[0] = f_Charpntr[*(f_Cy)];
	f_A[1] = f_Charpntr[*(f_Cy)+ 1];
	f_A[2] = f_Charpntr[*(f_Cy)+ 2];
	f_A[3] = f_Charpntr[*(f_Cy)+ 3];

	*(f_Cy) += 4;

	if(f_A[0] == ':' &&
		f_A[1] == ':' &&
		f_A[2] == ':' &&
		f_A[3] == ':')
		{
		return std::string("");
		}
	else
		{
		if(f_A[0] != ':')
			{
			f_Res.push_back(f_A[0]);
			}
		}

	while(f_Scan == true)
		{
		f_A[0] = f_A[1];
		f_A[1] = f_A[2];
		f_A[2] = f_A[3];
		f_A[3] = f_Charpntr[*(f_Cy)];

		*(f_Cy) += 1;

		if( f_A[0] == ':' &&
			f_A[1] == ':' &&
			f_A[2] == ':' &&
			f_A[3] == ':')
			{
			if((*(f_Cy) >= iResult) && (f_isLastof == false))
				{
				f_Res += "&&";

				return f_Res;
				}

			f_Scan = false;
			}
		else
			{
			if(f_A[0] != ':')
				{
				f_Res.push_back(f_A[0]);
				}

			if(*(f_Cy) >= iResult)
				{
				if(f_A[1] != ':')
					{
					f_Res.push_back(f_A[1]);
					}

				if(f_A[2] != ':')
					{
					f_Res.push_back(f_A[2]);
					}

				if(f_A[3] != ':')
					{
					f_Res.push_back(f_A[3]);
					}

				if( f_A[0] == ':' ||
					f_A[1] == ':' ||
					f_A[2] == ':' ||
					f_A[3] == ':')
					{
					f_Res += "&&";

					return f_Res;
					}

				f_Res.push_back('&');

				return f_Res;
				}
			}
		}

	return f_Res;
}

bool Schedular::acSend_Query_PeerGraph(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Pecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(32);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			char* f_popsuffix = ag_ClearChar(32);
			::sprintf(f_popsuffix, ":%i", g_ShareID);

			f_Result += f_popsuffix;
			delete f_popsuffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan12 = true;
			while(f_Scan12 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan12 = false;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_PeerGraphSelect(char* f_Char, int f_UI, bool f_End, int f_ShareID, int f_ShareOffset, int f_PEER, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Hecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			char* f_popsuffix = ag_ClearChar(32);
			::sprintf(f_popsuffix, ":%i", f_ShareID);
			f_Result += f_popsuffix;
			delete f_popsuffix;

			char* f_pop2suffix = ag_ClearChar(32);
			::sprintf(f_pop2suffix, ":%i", f_ShareOffset);
			f_Result += f_pop2suffix;
			delete f_pop2suffix;
			 
			char* f_pop3suffix = ag_ClearChar(32);
			::sprintf(f_pop3suffix, ":%i", f_PEER);
			f_Result += f_pop3suffix;
			delete f_pop3suffix;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan13 = true;
			while(f_Scan13 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan13 = false;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_GlobalStorageWealth(char* f_Char, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "W:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			//Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan14 = true;
			while(f_Scan14 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan14 = false;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Secoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan15 = true;
			while(f_Scan15 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan15 = false;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Wallet_Query(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Secoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_WalletSaveSocket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_WalletSaveSocket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan15 = true;
			while(f_Scan15 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan15 = false;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Logon(char* f_Char, int f_UI, bool f_End, int f_Index, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	m_Logon = true;

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Fecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			if(f_Index == 0)
				{
				int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

				if(iResult == SOCKET_ERROR)
					{
					closesocket(m_ClientSS->m_Socket);

					WSACleanup();

					/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

					m_SentMtx_ON = false;
					m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak();
#endif

					return false;
					}
				}
			else
				{
				int iResult = send(m_ClientSS->m_vec_Socket[f_Index - 1], (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

				if(iResult == SOCKET_ERROR)
					{
					closesocket(m_ClientSS->m_vec_Socket[f_Index - 1]);

					WSACleanup();

					/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

					m_SentMtx_ON = false;
					m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak();
#endif

					return false;
					}
				}

			bool f_Scan15 = true;
			while(f_Scan15 == true)
				{
				m_EntriesMtx.lock();

				if(m_Entries.size() > 0)
					{
					if(m_Entries.size() >= f_Index + 1)
						{
						int f_Resultant = ::atoi(m_Entries[m_Entries.size() - 1]->at(0)[0].c_str());

						if(f_Resultant == 0)
							{
							f_Scan15 = false;
							}
						}
					}

				m_EntriesMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			m_Logon = false;

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntriesMtx.lock();

				if(m_Entries.size() > 0)
					{
					if(m_Entries.size() >= f_Index + 1)
						{
						int f_Resultant = ::atoi(m_Entries[m_Entries.size() - 1]->at(0)[0].c_str());

						if(f_Resultant == 0)
							{
							int f_X = 1;
							}
						}
					}

				m_EntriesMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	m_Logon = false;

	return true;
}

bool Schedular::acSend_Logon_Mainstream(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	m_Logon_Mainstream = true;

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Fecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_MainstreamEntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Mainstream_Entries.size();

			m_MainstreamEntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_MainstreamSocket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_MainstreamSocket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan15 = true;
			while(f_Scan15 == true)
				{
				m_MainstreamEntriesMtx.lock();

				if(m_Mainstream_Entries.size() > 0)
					{
					int f_Resultant = ::atoi(m_Mainstream_Entries[m_Mainstream_Entries.size() - 1]->at(0)[0].c_str());

					if(f_Resultant == 0)
						{
						f_Scan15 = false;
						}
					}

				m_MainstreamEntriesMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			m_Logon_Mainstream = false;

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_MainstreamEntriesMtx.lock();

				if(m_Mainstream_Entries.size() > 0)
					{
					int f_Resultant = ::atoi(m_Mainstream_Entries[m_Mainstream_Entries.size() - 1]->at(0)[0].c_str());

					if(f_Resultant == 0)
						{
						int f_X = 1;
						}
					}

				m_MainstreamEntriesMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	m_Logon_Mainstream = false;

	return true;
}

bool Schedular::acSend_KeepAlive(char* f_Char, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Kecoincd1:";
			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_Angel(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "S";
			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(32);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan16 = true;
			while(f_Scan16 == true)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan16 = false;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_Mainstream(char* f_Char, int f_UI, bool f_End, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "S";
			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_MainstreamEntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Mainstream_Entries.size();

			m_MainstreamEntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_MainstreamSocket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_MainstreamSocket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			bool f_Scan16 = true;
			while(f_Scan16 == true)
				{
				m_MainstreamEntrantMtx.lock();

				if(m_Mainstream_Entrant.size() > 0)
					{
					if(m_Mainstream_Entrant.size() == (f_EntCount + 1))
						{
						f_Scan16 = false;
						}
					}

				m_MainstreamEntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_MainstreamEntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Mainstream_Entries.size();

			m_MainstreamEntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_MainstreamEntrantMtx.lock();

				if(m_Mainstream_Entrant.size() > 0)
					{
					if(m_Mainstream_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_MainstreamEntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_KeepAlive_Angel(char* f_Char, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "K";
			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			// Send an initial buffer
			int iResultMS = send(m_ClientSS->m_MainstreamSocket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResultMS == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_MainstreamSocket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Mecoincd1:";

			if(f_Update == true)
				{
				f_String = "Uecoincd1:";
				}

			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			if(f_Update == false)
				{
				bool f_Scan17 = true;
				while(f_Scan17 == true)
					{
					m_EntrantMtx.lock();

					if(m_Entrant.size() > 0)
						{
						if(m_Entrant.size() == (f_EntCount + 1))
							{
							f_Scan17 = false;
							}
						}

					m_EntrantMtx.unlock();

					acScheduleUpdator();
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_Wallet_CMD(char* f_Char, int f_UI, bool f_End, bool f_Update, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "Mecoincd1:";

			if(f_Update == true)
				{
				f_String = "Uecoincd1:";
				}

			f_String += f_Char;
			f_String += ":ecoincd1";

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_WalletSaveSocket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_WalletSaveSocket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			if(f_Update == false)
				{
				bool f_Scan17 = true;
				while(f_Scan17 == true)
					{
					m_EntrantMtx.lock();

					if(m_Entrant.size() > 0)
						{
						if(m_Entrant.size() == (f_EntCount + 1))
							{
							f_Scan17 = false;
							}
						}

					m_EntrantMtx.unlock();

					acScheduleUpdator();
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD_Angel(char* f_Char, int f_UI, bool f_End, bool f_Update, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;
	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "M";

			if(f_Update == true)
				{
				f_String = "U";
				}

			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(64);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_Socket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_Socket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			if(f_Update == false)
				{
				bool f_Scan18 = true;
				while(f_Scan18 == true)
					{
					m_EntrantMtx.lock();

					if(m_Entrant.size() > 0)
						{
						if(m_Entrant.size() == (f_EntCount + 1))
							{
							f_Scan18 = false;
							}
						}

					m_EntrantMtx.unlock();

					acScheduleUpdator();
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_EntrantMtx.lock();

				if(m_Entrant.size() > 0)
					{
					if(m_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_EntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

bool Schedular::acSend_Query_CMD_Mainstream(char* f_Char, int f_UI, bool f_End, bool f_Update, bool f_MainMutex_Ext_ON)
{
	/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.lock(); }

	acScheduleUpdator();

	bool f_Fill = false;

	while(f_Fill == false)
		{
		if(g_ConnectedECD == true)
			{
			std::string f_String = "M";

			if(f_Update == true)
				{
				f_String = "U";
				}

			f_String += f_Char;

			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_MainstreamEntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Mainstream_Entries.size();

			m_MainstreamEntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			char* f_EndCap = ag_ClearChar(32);
			::sprintf(f_EndCap, ":%i%c", f_EntCount, SCHEDULE_END_CHARACTER);
			std::string f_Result = f_String + f_EndCap;
			delete f_EndCap;

			// Send an initial buffer
			int iResult = send(m_ClientSS->m_MainstreamSocket, (char*)f_Result.c_str(), (int)strlen((char*)f_Result.c_str()), 0);

			if(iResult == SOCKET_ERROR)
				{
				closesocket(m_ClientSS->m_MainstreamSocket);

				WSACleanup();

				/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

				m_SentMtx_ON = false;
				m_SentMtx.unlock();

#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak();
#endif

				return false;
				}

			if(f_Update == false)
				{
				bool f_Scan18 = true;
				while(f_Scan18 == true)
					{
					m_MainstreamEntrantMtx.lock();

					if(m_Mainstream_Entrant.size() > 0)
						{
						if(m_Mainstream_Entrant.size() == (f_EntCount + 1))
							{
							f_Scan18 = false;
							}
						}

					m_MainstreamEntrantMtx.unlock();

					acScheduleUpdator();
					}
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();

			f_Fill = true;

			/*__debugbreak();*/ if(f_MainMutex_Ext_ON == false) { m_MainMutex.unlock(); }

			return true;
			}
		else
			{
			m_SentMtx.lock();
			m_SentMtx_ON = true;

			m_EntriesMtx.lock();

			//register entrant
			int f_EntCount = m_Entries.size();

			m_EntriesMtx.unlock();

			if(f_EntCount >= ECOIN_ENTRY_MAX)
				{
				f_EntCount = (f_EntCount - ECOIN_ENTRY_REFRESH_MINUS) - 1;
				}

			while(g_ConnectedECD == false)
				{
				m_MainstreamEntrantMtx.lock();

				if(m_Mainstream_Entrant.size() > 0)
					{
					if(m_Mainstream_Entrant.size() == (f_EntCount + 1))
						{
						int f_X = 1;
						}
					}

				m_MainstreamEntrantMtx.unlock();

				acScheduleUpdator();
				}

			m_SentMtx_ON = false;
			m_SentMtx.unlock();
			}
		}

	return true;
}

int Schedular::ac_GetEntry(int f_EntryIdx)
{
	m_EntriesMtx.lock();

	if(f_EntryIdx >= m_Entries.size())
		{
		f_EntryIdx = m_Entries.size() - 1;
		}

	m_EntriesMtx.unlock();

	if(f_EntryIdx < 0)
		{
		throw;
		}
	else
		{
		return f_EntryIdx;
		}

	return 0;
}

void Schedular::acLogin(std::string f_Username, std::string f_Password)
{
	acScheduleUpdator();

	std::string f_BufferSend = "O";
	f_BufferSend = f_BufferSend + f_Username + ":";
	f_BufferSend = f_BufferSend + f_Password + ":";

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, f_BufferSend.c_str(), (int)strlen(f_BufferSend.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);

		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}
}

void Schedular::acRegister(std::string f_Username, std::string f_Password, std::string f_Email)
{
	acScheduleUpdator();

	std::string f_BufferSend = "R";
	f_BufferSend = f_BufferSend + f_Username + ":";
	f_BufferSend = f_BufferSend + f_Password + ":";
	f_BufferSend = f_BufferSend + f_Email + ":";

	// Send an initial buffer
	int iResult = send(m_ClientSS->m_Socket, f_BufferSend.c_str(), (int)strlen(f_BufferSend.c_str()), 0);

	if(iResult == SOCKET_ERROR)
		{
		closesocket(m_ClientSS->m_Socket);

		WSACleanup();

#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}
}

std::vector<std::string> Schedular::acEntry(int f_Index)
{
	std::vector<std::string> f_Entries;

	m_EntriesMtx.lock();

	f_Entries = m_Entries[m_Entries.size() - 1]->at(f_Index);

	m_EntriesMtx.unlock();

	return f_Entries;
}

std::vector<std::string> Schedular::acEntryIndex(int f_ArrayIndex, int f_Index)
{
	std::vector<std::string> f_Entries;

	m_EntriesMtx.lock();

	f_Entries = m_Entries[f_ArrayIndex]->at(f_Index);

	m_EntriesMtx.unlock();

	return f_Entries;
}

std::shared_ptr<std::vector<std::vector<std::string>>> Schedular::acEntryPtr(void)
{
	std::shared_ptr<std::vector<std::vector<std::string>>> f_Ptr;

	m_EntriesMtx.lock();

	f_Ptr = m_Entries[m_Entries.size() - 1];

	m_EntriesMtx.unlock();

	return f_Ptr;
}

int Schedular::acEntrySize(void)
{
	int f_Size = 0;

	m_EntriesMtx.lock();

	f_Size = m_Entries[m_Entries.size() - 1]->size();

	m_EntriesMtx.unlock();

	return f_Size;
}

std::vector<std::string> Schedular::acMSEntry(int f_Index)
{
	std::vector<std::string> f_Entries;

	m_MainstreamEntriesMtx.lock();

	f_Entries = m_Mainstream_Entries[m_Mainstream_Entries.size() - 1]->at(f_Index);

	m_MainstreamEntriesMtx.unlock();

	return f_Entries;
}

std::vector<std::string> Schedular::acMSEntryIndex(int f_ArrayIndex, int f_Index)
{
	std::vector<std::string> f_Entries;

	m_MainstreamEntriesMtx.lock();

	f_Entries = m_Mainstream_Entries[f_ArrayIndex]->at(f_Index);

	m_MainstreamEntriesMtx.unlock();

	return f_Entries;
}

std::shared_ptr<std::vector<std::vector<std::string>>> Schedular::acMSEntryPtr(void)
{
	std::shared_ptr<std::vector<std::vector<std::string>>> f_Ptr;

	m_MainstreamEntriesMtx.lock();

	f_Ptr = m_Mainstream_Entries[m_Mainstream_Entries.size() - 1];

	m_MainstreamEntriesMtx.unlock();

	return f_Ptr;
}

int Schedular::acMSEntrySize(void)
{
	int f_Size = 0;

	m_MainstreamEntriesMtx.lock();

	f_Size = m_Mainstream_Entries[m_Mainstream_Entries.size() - 1]->size();

	m_MainstreamEntriesMtx.unlock();

	return f_Size;
}

void ag_KeepAlive(void)
{
	//Send Keep Alive Messages
	g_Schedular[0]->acSend_KeepAlive("UploadServerConnectionKeepAlive", false);
	g_Schedular[1]->acSend_KeepAlive("ReceiveServerConnectionKeepAlive", false);
	g_Schedular[2]->acSend_KeepAlive_Angel("QuantumServerConnectionKeepAlive", false);
}

};