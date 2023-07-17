/*

    UNSDomain.cpp - Domain Definition
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "../UnSRC/QServerFramewrk.h"

#include "../UnSRC/Utility/Singleton.h"
#include "../UnSRC/Utility/datatypes.h"
#include <string>
#include <vector>

#include "UNSDomain.h"
#include "UNSGlobalHeader.h"

#include "time.h"

#include "../UnSRC/Utility/RakNetMsgIdent.h"
#include "unsStringCompressor.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

#include "BitTransfer.h"
#include "GetTime.h"

using namespace RakNet;

unDomainRadial::unDomainRadial(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(unDomainRadial)
	SUPPORT_THREAD_NOTIFICATION

	m_Measure.m_Pos.x = UNS_DOMAIN_DEFAULT_X;
	m_Measure.m_Pos.y = UNS_DOMAIN_DEFAULT_Y;
	m_Measure.m_Pos.z = UNS_DOMAIN_DEFAULT_Z;

	m_Measure.m_Range = UNS_DOMAIN_DEFAULT_RANGE;

	m_TimeStart = 0;
	m_TimeEnd = 0;

	m_mutex_Dom_Avatar = SDL_CreateMutex();
	m_mutex_Dom_Refresh = SDL_CreateMutex();
	m_mutex_Dom_System = SDL_CreateMutex();

	m_mutexcc_Avatar = new unMutexCC();

	m_mutexcc_AvatarId = new unMutexCC();
	m_mutexcc_Refresh = new unMutexCC();

	m_RefreshCount = new int(0);

	vec_entity_Avatar = new std::vector<unEntAvatar*>;
	vec_entity_SysIndex = new std::vector<unsigned short>;
	vec_entity_SysAddress = new std::vector<SystemAddress*>;

	vec_avatar_Ident = new std::vector<unAvatarList*>;
	vec_RefreshList = new std::vector<unRefreshList*>;
}

unDomainRadial::unDomainRadial(std::vector<unEntAvatar*>* i_vec_entity_Avatar,
	std::vector<unsigned short>* i_vec_entity_SysIndex,
	std::vector<SystemAddress*>* i_vec_entity_SysAddress,
	std::vector<unAvatarList*>* i_vec_avatar_Ident,
	std::vector<unRefreshList*>* i_vec_RefreshList,
	SDL_mutex *i_mutex_Dom_Avatar,
	SDL_mutex *i_mutex_Dom_Refresh,
	SDL_mutex *i_mutex_Dom_System,
	unMutexCC* i_mutexcc_Avatar,
	unMutexCC* i_mutexcc_AvatarId,
	unMutexCC* i_mutexcc_Refresh,
	void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(unDomainRadial)
	SUPPORT_THREAD_NOTIFICATION

	m_Measure.m_Pos.x = UNS_DOMAIN_DEFAULT_X;
	m_Measure.m_Pos.y = UNS_DOMAIN_DEFAULT_Y;
	m_Measure.m_Pos.z = UNS_DOMAIN_DEFAULT_Z;

	m_Measure.m_Range = UNS_DOMAIN_DEFAULT_RANGE;

	m_TimeStart = 0;
	m_TimeEnd = 0;

	m_RefreshCount = new int(0);

	m_mutex_Dom_Avatar = i_mutex_Dom_Avatar;
	m_mutex_Dom_Refresh = m_mutex_Dom_Refresh;
	m_mutex_Dom_System = i_mutex_Dom_System;

	m_mutexcc_Avatar = i_mutexcc_Avatar;

	m_mutexcc_AvatarId = i_mutexcc_AvatarId;
	m_mutexcc_Refresh = i_mutexcc_Refresh;

	vec_entity_Avatar = i_vec_entity_Avatar;
	vec_entity_SysIndex = i_vec_entity_SysIndex;
	vec_entity_SysAddress = i_vec_entity_SysAddress;
	
	vec_avatar_Ident = i_vec_avatar_Ident;
	vec_RefreshList = i_vec_RefreshList;
}

unDomainRadial::~unDomainRadial()
{
}

void unDomainRadial::Initialize(void)
{
	PP_STATE = 1;

	acGenStacks();
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int unDomainRadial::ThreadHandler()
{
	bool bCanContinue = true;
	int nIncomingCommand;

	do
		{
		WaitForNotification(nIncomingCommand);

		switch (nIncomingCommand)
			{
			case CThread::CMD_INITIALIZE:
				Initialize();
				HandleCommandImmediately(CThread::CMD_RUN);
				break;

			case CThread::CMD_RUN:
#if 0
				Lock();
#endif
				Run();
#if 0
				Unlock();
#endif
				break;

			case CThread::CMD_PAUSE:
				SetActivityStatus(CThread::THREAD_PAUSED);
				break;

			case CThread::CMD_STOP:
				bCanContinue = false;
				break;

			default:
				break;
			};

		} while (bCanContinue);

	return 0;	// ... if Thread task completition OK
}

void unDomainRadial::Run(void)
{
	while(PP_STATE == 1)
		{
		acScan();
		
#if defined(WIN32)
		Sleep(450);
#endif
		}
}

void unDomainRadial::acGenStacks(void)
{
	unDomainStack* i_DomainStack = new unDomainStack();

	i_DomainStack->m_Measure = &m_Measure;
	i_DomainStack->vec_entity_Avatar = vec_entity_Avatar;
	i_DomainStack->vec_entity_SysIndex = vec_entity_SysIndex;
	i_DomainStack->vec_entity_SysAddress = vec_entity_SysAddress;
	i_DomainStack->vec_avatar_Ident = vec_avatar_Ident;
	i_DomainStack->vec_RefreshList = vec_RefreshList;
	i_DomainStack->m_RefreshCount = m_RefreshCount;
	i_DomainStack->m_mutex_Dom_Avatar = m_mutex_Dom_Avatar;
	i_DomainStack->m_mutex_Dom_Refresh = m_mutex_Dom_Refresh;
	i_DomainStack->m_mutex_Dom_System = m_mutex_Dom_System;
	i_DomainStack->m_mutexcc_Avatar = m_mutexcc_Avatar;
	i_DomainStack->m_mutexcc_AvatarId = m_mutexcc_AvatarId;
	i_DomainStack->m_mutexcc_Refresh = m_mutexcc_Refresh;
	i_DomainStack->Start();

	vec_DomainStack.push_back(i_DomainStack);
}

void unDomainRadial::acAvatarStartClient(QpoVec3d i_Position, float i_Rotation, unsigned short i_SysIndex, int i_BDATID, int CDATID)
{
	printf("unServerTrace entry function acAvatarStartClient\n");

	unEntAvatar* i_entity_Avatar = new unEntAvatar(i_Position, i_Rotation, i_BDATID, CDATID);

	i_entity_Avatar->m_Type = UNS_ENTITY_PLAYER;

	printf("unServerTrace i_entity_Avatar->m_Type = UNS_ENTITY_PLAYER\n");

	SDL_mutexP(m_mutex_Dom_Avatar);
	SDL_mutexP(m_mutex_Dom_System);

	printf("unServerTrace m_mutex_Dom_Avatar m_mutex_Dom_System\n");

	m_mutexcc_Avatar->ac_Fire();

	printf("unServerTrace m_mutexcc_Avatar->ac_Fire\n");

	vec_entity_Avatar[0].push_back(i_entity_Avatar);
	vec_entity_SysIndex[0].push_back(i_SysIndex);
	vec_entity_SysAddress[0].push_back(g_map_SysAddressST[i_SysIndex]);

	m_count = vec_entity_SysIndex[0].size();

	printf("unServerTrace vec_entity_SysIndex[0].size\n");

	m_mutexcc_Avatar->ac_Stop();

	printf("unServerTrace m_mutexcc_Avatar->ac_Stop()\n");

	SDL_mutexV(m_mutex_Dom_Avatar);
	SDL_mutexV(m_mutex_Dom_System);

	printf("unServerTrace SDL_mutexV(m_mutex_Dom_Avatar m_mutex_Dom_System)\n");

	SDL_mutexP(g_mutex_NomAvatar);
	m_VectorAvatarID = g_nom_Avatar;
	g_nom_Avatar++;
	SDL_mutexV(g_mutex_NomAvatar);

	printf("unServerTrace g_nom_Avatar++\n");

	if(g_map_ClientAvatarID.find(i_SysIndex) == g_map_ClientAvatarID.end())
		{
		m_vec_IdentList = new unAvatarList();

		m_vec_IdentList->vec_Index.push_back(m_VectorAvatarID);
		m_vec_IdentList->vec_TickStamp.push_back(0);

		m_mutexcc_AvatarId->ac_Fire();
		vec_avatar_Ident[0].push_back(m_vec_IdentList);
		m_mutexcc_AvatarId->ac_Stop();

		g_mutex_AvatarID->ac_Fire();
		g_map_ClientAvatarID[i_SysIndex] = m_vec_IdentList;
		g_mutex_AvatarID->ac_Stop();
		}
	else
		{
		g_mutex_AvatarID->ac_Sync();
		m_vec_IdentList = g_map_ClientAvatarID[i_SysIndex];
		g_mutex_AvatarID->ac_Free();

		m_mutexcc_AvatarId->ac_Fire();
		m_vec_IdentList->vec_Index.push_back(m_VectorAvatarID);
		m_vec_IdentList->vec_TickStamp.push_back(0);
		m_mutexcc_AvatarId->ac_Stop();
		}

	printf("unServerTrace g_map_ClientAvatarID.find(i_SysIndex)\n");

#if 0
	vec_swing_TimeSheet.m_mars.resize(m_count);
	vec_swing_TimeSheet.m_venus.resize(m_count);
#endif

	SDL_mutexP(m_mutex_Dom_Refresh);

#if 0
#if 0
	vec_refresh_Client[0].resize(m_count);
#else
	vec_refresh_Client[0].push_back(0);
#endif
#endif

	SDL_mutexV(m_mutex_Dom_Refresh);

	printf("unServerTrace SDL_mutexV m_mutex_Dom_Refresh\n");

#if 0
	vec_swing_TimeSheet.m_mars[m_count - 1].m_TickStamp = 0;
	vec_swing_TimeSheet.m_mars[m_count - 1].m_Index = m_count - 1;
#endif

	Continue();

	printf("unServerTrace Continue()\n");

#pragma message("WARNING:::Default set")
	unDomainAddress i_DomainAddress;
	i_DomainAddress.m_DomainID = 0;
	i_DomainAddress.m_ClientID = m_count - 1;

	SDL_mutexP(g_mutex_Domain);
	g_map_ClientDom[i_SysIndex] = i_DomainAddress;
	SDL_mutexV(g_mutex_Domain);

	printf("unServerTrace Exit\n");
}

void unDomainRadial::acAvatarStart(QpoVec3d i_Position, float i_Rotation, unsigned short i_SysIndex, int i_BDATID, int CDATID)
{
	printf("unServerTrace entry function acAvatarStartClient\n");

	unEntAvatar* i_entity_Avatar = new unEntAvatar(i_Position, i_Rotation, i_BDATID, CDATID);

	i_entity_Avatar->m_Type = UNS_ENTITY_AVATAR;

	printf("unServerTrace 1\n");

	SDL_mutexP(m_mutex_Dom_Avatar);
	SDL_mutexP(m_mutex_Dom_System);

	printf("unServerTrace 2\n");

	m_mutexcc_Avatar->ac_Fire();

	printf("unServerTrace 3\n");

	vec_entity_Avatar[0].push_back(i_entity_Avatar);
	vec_entity_SysIndex[0].push_back(i_SysIndex);
	vec_entity_SysAddress[0].push_back(g_map_SysAddressST[i_SysIndex]);

	m_count = vec_entity_SysIndex[0].size();

	printf("unServerTrace 4\n");

	m_mutexcc_Avatar->ac_Stop();

	printf("unServerTrace 5\n");

	SDL_mutexV(m_mutex_Dom_Avatar);
	SDL_mutexV(m_mutex_Dom_System);

	printf("unServerTrace 6\n");

	SDL_mutexP(g_mutex_NomAvatar);
	m_VectorAvatarID = g_nom_Avatar;
	g_nom_Avatar++;
	SDL_mutexV(g_mutex_NomAvatar);

	printf("unServerTrace 7\n");

	if(g_map_ClientAvatarID.find(i_SysIndex) == g_map_ClientAvatarID.end())
		{
		m_vec_IdentList = new unAvatarList;

		m_vec_IdentList->vec_Index.push_back(m_VectorAvatarID);
		m_vec_IdentList->vec_TickStamp.push_back(0);

		m_mutexcc_AvatarId->ac_Fire();
		vec_avatar_Ident[0].push_back(m_vec_IdentList);
		m_mutexcc_AvatarId->ac_Stop();

		g_mutex_AvatarID->ac_Fire();
		g_map_ClientAvatarID[i_SysIndex] = m_vec_IdentList;
		g_mutex_AvatarID->ac_Stop();
		}
	else
		{
		g_mutex_AvatarID->ac_Sync();
		m_vec_IdentList = g_map_ClientAvatarID[i_SysIndex];
		g_mutex_AvatarID->ac_Free();

		m_mutexcc_AvatarId->ac_Fire();
		m_vec_IdentList->vec_Index.push_back(m_VectorAvatarID);
		m_vec_IdentList->vec_TickStamp.push_back(0);
		m_mutexcc_AvatarId->ac_Stop();
		}

	printf("unServerTrace 8\n");

#if 0
	vec_swing_TimeSheet.m_mars.resize(m_count);
	vec_swing_TimeSheet.m_venus.resize(m_count);
#endif

	SDL_mutexP(m_mutex_Dom_Refresh);

#if 0
#if 0
	vec_refresh_Client[0].resize(m_count);
#else
	vec_refresh_Client[0].push_back(0);
#endif
#endif

	SDL_mutexV(m_mutex_Dom_Refresh);

#if 0
	vec_swing_TimeSheet.m_mars[m_count - 1].m_TickStamp = 0;
	vec_swing_TimeSheet.m_mars[m_count - 1].m_Index = m_count - 1;
#endif

	printf("unServerTrace 9\n");

	Continue();

#pragma message("WARNING:::Default set")
	unDomainAddress i_DomainAddress;
	i_DomainAddress.m_DomainID = 0;
	i_DomainAddress.m_ClientID = m_count - 1;

	SDL_mutexP(g_mutex_Domain);
	g_map_ClientDom[i_SysIndex] = i_DomainAddress;
	SDL_mutexV(g_mutex_Domain);

	printf("unServerTrace 10\n");
}

bool unDomainRadial::acAvatarShutdownClient(unsigned short i_SysIndex)
{
	unAvatarList *i_AvatarList;

	if(g_map_ClientAvatarID.find(i_SysIndex) == g_map_ClientAvatarID.end()) return false;
	else i_AvatarList = g_map_ClientAvatarID[i_SysIndex];

	SDL_mutexP(m_mutex_Dom_Avatar);
	SDL_mutexP(m_mutex_Dom_System);

	m_mutexcc_Avatar->ac_Fire();

	bool i_Present;
	unsigned int i_Counter = 0;
	for(unsigned int i_EntityID = 0; i_EntityID < vec_entity_Avatar[0].size(); i_EntityID++)
		{
		i_Present = true;
		for(unsigned int i_AvID = 0; i_AvID < i_AvatarList->vec_Index.size(); i_AvID++)
			{
			if(i_EntityID == i_AvatarList->vec_Index[i_AvID]) i_Present = false;
			}

		if(i_Present)
			{
			vec_entity_Avatar[0][0] = vec_entity_Avatar[0][0];
			vec_entity_SysIndex[0][0] = vec_entity_SysIndex[0][0];
			vec_entity_SysAddress[0][0] = vec_entity_SysAddress[0][0];
			i_Counter++;
			}
		else
			{
			SDL_mutexP(g_mutex_NomAvatar);
			g_nom_Avatar--;
			SDL_mutexV(g_mutex_NomAvatar);
			}
		}

	m_mutexcc_Avatar->ac_Stop();

	SDL_mutexV(m_mutex_Dom_Avatar);
	SDL_mutexV(m_mutex_Dom_System);

	delete i_AvatarList;
	g_map_ClientAvatarID.erase(i_SysIndex);

	SDL_mutexP(g_mutex_Domain);
	if(g_map_ClientDom.find(i_SysIndex) != g_map_ClientDom.end())
		{
		g_map_ClientDom.erase(i_SysIndex);
		}
	SDL_mutexV(g_mutex_Domain);

	SDL_mutexP(m_mutex_Dom_Avatar);
	if(vec_entity_Avatar[0].size() == 0) Pause();
	SDL_mutexV(m_mutex_Dom_Avatar);

	return true;
}

bool unDomainRadial::acAvatarShutdown(unsigned short i_SysIndex)
{
	unAvatarList *i_AvatarList;

	if(g_map_ClientAvatarID.find(i_SysIndex) == g_map_ClientAvatarID.end()) return false;
	else i_AvatarList = g_map_ClientAvatarID[i_SysIndex];

	SDL_mutexP(m_mutex_Dom_Avatar);
	SDL_mutexP(m_mutex_Dom_System);

	m_mutexcc_Avatar->ac_Fire();

	bool i_Present;
	unsigned int i_Counter = 0;
	for(unsigned int i_EntityID = 0; i_EntityID < vec_entity_Avatar[0].size(); i_EntityID++)
		{
		i_Present = true;
		for(unsigned int i_AvID = 0; i_AvID < i_AvatarList->vec_Index.size(); i_AvID++)
			{
			if(i_EntityID == i_AvatarList->vec_Index[i_AvID]) i_Present = false;
			}

		if(i_Present)
			{
			vec_entity_Avatar[0][0] = vec_entity_Avatar[0][0];
			vec_entity_SysIndex[0][0] = vec_entity_SysIndex[0][0];
			vec_entity_SysAddress[0][0] = vec_entity_SysAddress[0][0];
			i_Counter++;
			}
		else
			{
			SDL_mutexP(g_mutex_NomAvatar);
			g_nom_Avatar--;
			SDL_mutexV(g_mutex_NomAvatar);
			}
		}

	m_mutexcc_Avatar->ac_Stop();

	SDL_mutexV(m_mutex_Dom_Avatar);
	SDL_mutexV(m_mutex_Dom_System);

	delete i_AvatarList;
	g_map_ClientAvatarID.erase(i_SysIndex);

	SDL_mutexP(g_mutex_Domain);
	if(g_map_ClientDom.find(i_SysIndex) != g_map_ClientDom.end())
		{
		g_map_ClientDom.erase(i_SysIndex);
		}
	SDL_mutexV(g_mutex_Domain);

	SDL_mutexP(m_mutex_Dom_Avatar);
	if(vec_entity_Avatar[0].size() == 0) Pause();
	SDL_mutexV(m_mutex_Dom_Avatar);

	return true;
}

void unDomainRadial::acScan(void)
{
#if 1
	if(vec_entity_SysIndex[0].size() == 0) Pause();
#endif

#if 0
	m_Tick = GetTickCount();
#else
	m_Tick = clock();
#endif

#if 0
	m_ElapsedSeconds = (float)(m_Tick - m_LastTick) / 1000.0f;
	m_LastTick = tick;
	printf("m_ElapsedSeconds %f\n", m_ElapsedSeconds);
#endif

	g_mutex_AvatarID->ac_Sync();
	m_ListCount = vec_avatar_Ident[0].size();
	g_mutex_AvatarID->ac_Free();

	m_ListID = 0;
	while(m_ListID < m_ListCount)	// Avatar List
		{
		g_mutex_AvatarID->ac_Sync();

		m_AVID = 0;
		while(m_AVID < vec_avatar_Ident[0][m_ListID]->vec_Index.size())
			{
			if(m_Tick > vec_avatar_Ident[0][m_ListID]->vec_TickStamp[m_AVID] + UNS_DOMAIN_REFRESH)
				{
				m_RefreshList = new unRefreshList(vec_avatar_Ident[0][m_ListID]);

				m_mutexcc_Avatar->ac_Sync();

				for(int i_ListAVID = 0; i_ListAVID < vec_avatar_Ident[0][m_ListID]->vec_Index.size(); i_ListAVID++)
					{
					for(int i_AVID = 0; i_AVID < vec_entity_Avatar[0].size(); i_AVID++)
						{
						if(vec_avatar_Ident[0][m_ListID]->vec_Index[i_ListAVID] != i_AVID)
							{
							m_Distance = Qpo->Vec3d_DistanceBetween(&vec_entity_Avatar[0][vec_avatar_Ident[0][m_ListID]->vec_Index[i_ListAVID]]->m_Pos, &vec_entity_Avatar[0][i_AVID]->m_Pos);

							if(!vec_avatar_Ident[0][m_ListID]->acFindAvatar(i_AVID))
								{
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~


								//~~~~~~~~~~~~~~~~~~~~~~~~~~~

								m_Distance = Qpo->Vec3d_DistanceBetween(&vec_entity_Avatar[0][vec_avatar_Ident[0][m_ListID]->vec_Index[i_ListAVID]]->m_Pos, &vec_entity_Avatar[0][i_AVID]->m_Pos);

								if(m_Distance < 10000000)
									{
									m_RefreshList->acPushAvatar(i_AVID);
									}
								}
							}
						}
					}

				m_mutexcc_Avatar->ac_Free();

				m_mutexcc_Refresh->ac_Fire();
				vec_RefreshList[0].push_back(m_RefreshList);
				m_mutexcc_Refresh->ac_Stop();
				}

			m_AVID++;
			}

		g_mutex_AvatarID->ac_Free();

		m_ListID++;
		}
}

int unDomainRadial::acFind(unsigned short i_SysAddress)
{
	m_mutexcc_Refresh->ac_Sync();

	for(unsigned int i_ListID; i_ListID < vec_RefreshList[0].size(); i_ListID++)
		{
		if(i_SysAddress == vec_entity_SysIndex[0][vec_RefreshList[0][i_ListID]->m_SysAddress])
			{
			m_mutexcc_Refresh->ac_Free();
			return i_ListID;
			}
		}
	m_mutexcc_Refresh->ac_Free();
	return -1;
}

//#### unDomainStack ####//

unDomainStack::unDomainStack(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(unDomainStack)
	SUPPORT_THREAD_NOTIFICATION
}

unDomainStack::~unDomainStack()
{
}

void unDomainStack::Initialize(void)
{
	PP_STATE = 1;

	printf("unDomainStack Output Stack Initialization\n");
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int unDomainStack::ThreadHandler()
{
	bool bCanContinue = true;
	int nIncomingCommand;

	do
	{
		WaitForNotification(nIncomingCommand);

		switch (nIncomingCommand)
		{
		case CThread::CMD_INITIALIZE:
			Initialize();
			HandleCommandImmediately(CThread::CMD_RUN);
			break;

		case CThread::CMD_RUN:
			Lock();
			Run();
			Unlock();
			break;

		case CThread::CMD_PAUSE:
			SetActivityStatus(CThread::THREAD_PAUSED);
			break;

		case CThread::CMD_STOP:
			bCanContinue = false;
			break;

		default:
			break;
		};

	} while (bCanContinue);

	return 0;	// ... if Thread task completition OK
}

void unDomainStack::Run(void)
{
	while(PP_STATE == 1)
		{
#if defined(WIN32)
		Sleep(450);
#endif

		acSend();
#if 0
		for (int i=0; i < 5000; ++i) {	 /*PAUSE*/   }
#endif
		}
}

void unDomainStack::acSend(void)
{
	while(PP_STATE == 1)
		{
		m_mutexcc_Refresh->ac_Sync();
		m_count = vec_RefreshList[0].size() - 1;
		m_mutexcc_Refresh->ac_Free();

		if(m_count > -1)
			{
			m_mutexcc_Refresh->ac_Sync();
			m_RefreshList = vec_RefreshList[0][m_count];
			m_RefCount = m_RefreshList->vec_AvatarIndex.size();
			m_AvatarCount = m_RefreshList->m_List->vec_Index.size();
			m_AvatarTotal = m_RefCount + m_AvatarCount;
			m_mutexcc_Refresh->ac_Free();

			m_mutexcc_Refresh->ac_Fire();
			vec_RefreshList[0].pop_back();
			m_mutexcc_Refresh->ac_Stop();

			BitTransfer i_BitTransfer(ID_SERVER_DATA);

			// Write Avatar Positions
			m_mutexcc_AvatarId->ac_Sync();

			m_AvatarList = m_RefreshList->m_List;

#if 0
			i_BitTransfer.acPushAlloc(m_AvatarList->vec_Index.size() - 1);
#endif

			m_mutexcc_Avatar->ac_Sync();

			m_SystemAddress = vec_entity_SysAddress[0][m_AvatarList->vec_Index[0]];

			for(int i_IdentAVID = 0; i_IdentAVID < m_AvatarList->vec_Index.size(); i_IdentAVID++)
				{
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_AvatarList->vec_Index[i_IdentAVID]]->m_Pos.x);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_AvatarList->vec_Index[i_IdentAVID]]->m_Pos.y);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_AvatarList->vec_Index[i_IdentAVID]]->m_Pos.z);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_AvatarList->vec_Index[i_IdentAVID]]->m_Rotation);
				}

			i_BitTransfer.acPushAlloc(m_RefreshList->vec_AvatarIndex.size());

			for(int i_RefreshAVID = 0; i_RefreshAVID < m_RefreshList->vec_AvatarIndex.size(); i_RefreshAVID++)
				{
#pragma message("FIXTHIS:::Keep its refresh list")
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_RefreshList->vec_AvatarIndex[i_RefreshAVID]]->m_CDATID);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_RefreshList->vec_AvatarIndex[i_RefreshAVID]]->m_BDATID);

				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_RefreshList->vec_AvatarIndex[i_RefreshAVID]]->m_Pos.x);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_RefreshList->vec_AvatarIndex[i_RefreshAVID]]->m_Pos.y);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_RefreshList->vec_AvatarIndex[i_RefreshAVID]]->m_Pos.z);
				i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][m_RefreshList->vec_AvatarIndex[i_RefreshAVID]]->m_Rotation);
				}

			m_mutexcc_Avatar->ac_Free();
			m_mutexcc_AvatarId->ac_Free();

#if 0
			SDL_mutexP(g_mutex_unPeer);
#endif

#if 1
			g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *m_SystemAddress, true);
#endif

#if 0
			printf("SEND to CLIENT ::: ID_SERVER_DATA\n");
#endif

#if 0
			SDL_mutexV(g_mutex_unPeer);
#endif
			}
		}
}

#if 0
vec_entity_Avatar[0][i_iter]->m_QuanPass += (1 / (m_Distance * UNS_DOMAIN_GRANULARITY));

if(vec_entity_Avatar[0][i_iter]->m_QuanPass > 5.5)
	{
	i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][i_iter]->m_Pos.x);
	i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][i_iter]->m_Pos.y);
	i_BitTransfer.acPushAlloc(vec_entity_Avatar[0][i_iter]->m_Pos.z);
	m_AVcount++;

	vec_entity_Avatar[0][i_iter]->m_QuanPass = 0;
	}
#endif
