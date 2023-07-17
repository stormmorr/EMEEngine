/*

    m_PacketSocketInterfaceGbs - unServer packet input thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include <string>
#include <vector>
#include "PacketSocketInterface.h"

//#### Packet Socket Normal ###

PacketSocketInterface::PacketSocketInterface(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(PacketSocketInterface)
	SUPPORT_THREAD_NOTIFICATION
}

PacketSocketInterface::~PacketSocketInterface()
{
}

void PacketSocketInterface::Initialize(void)
{
	PP_STATE = 1;
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int PacketSocketInterface::ThreadHandler()
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

void PacketSocketInterface::Run(void)
{
	while(PP_STATE == 1)
		{
		//SDL_mutexP(m_mutex_unPeer);
		//*m_packet = m_unPeer->Receive();
		//SDL_mutexV(m_mutex_unPeer);

		if(m_packet != 0)
			{
			//SDL_mutexP(m_mutex_Packet);

			m_vec_Packet[0].m_vec_Packet.push_back(m_packet);

#ifdef UNS_PRINT_LVL
			printf("(Pkt)\n");
#endif
			
			//SDL_mutexV(m_mutex_Packet);
			}
		}
}