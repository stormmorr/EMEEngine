/*

    m_packetSocket - unServer packet input thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "MasterOSI.h"
#include "UNSGlobalHeaderOSI.h"

using namespace RakNet;

PacketSocket::PacketSocket(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(PacketSocket)
	SUPPORT_THREAD_NOTIFICATION
}

PacketSocket::~PacketSocket()
{
}

void PacketSocket::Initialize(void)
{
	PP_STATE = 1;
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int PacketSocket::ThreadHandler()
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

void PacketSocket::Run(void)
{
	while(PP_STATE == 1)
		{
#if defined(WIN32)
		Sleep(450);
#endif

		SDL_mutexP(g_mutex_unPeer);
		m_packet = g_unPeer->Receive();
		SDL_mutexV(g_mutex_unPeer);

		if(m_packet != 0)
			{
			SDL_mutexP(g_mutex_Packet);

			if(vec_Packet.m_PlaceDepth >= UNS_PACKET_DEPTH)
				{
				vec_Packet.m_PlaceDepth = 0;
				vec_Packet.m_PlaceHeight++;
				if(vec_Packet.m_PlaceHeight >= vec_Packet.m_Height)
					{
					vec_Packet.m_PlaceHeight = 0;
					}
				}

			vec_Packet.m_vec_Packet[vec_Packet.m_PlaceHeight][vec_Packet.m_PlaceDepth] = m_packet;
			vec_Packet.m_PlaceDepth++;

			SDL_mutexV(g_mutex_Packet);
			}
		}
}