/*

    m_PacketPump - unServer packet reading thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "MasterOSI.h"
#include "UNSGlobalHeaderOSI.h"

using namespace RakNet;

PacketPump::PacketPump(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(PacketPump)
	SUPPORT_THREAD_NOTIFICATION
}

PacketPump::~PacketPump()
{
}

void PacketPump::Initialize(void)
{
	PP_STATE = 1;
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int PacketPump::ThreadHandler()
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

unsigned char PacketPump::acPacketIdentifier(Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[5]; //1 + 4
	else
		return (unsigned char) p->data[0];
}

void PacketPump::Run(void)
{
	while(PP_STATE > 0)
		{
		Scan();

#if defined(WIN32)
		Sleep(450);
#endif
		}
}

void PacketPump::Scan(void)
{
	SDL_mutexP(g_mutex_Packet);

	if(!((vec_Packet.m_ReadHeight == vec_Packet.m_ReadHeight) && (vec_Packet.m_ReadDepth >= vec_Packet.m_PlaceDepth)))
		{
		m_packet = vec_Packet.m_vec_Packet[vec_Packet.m_ReadHeight][vec_Packet.m_ReadDepth];
		vec_Packet.m_ReadDepth++;

		if(vec_Packet.m_ReadDepth >= UNS_PACKET_DEPTH)
			{
			vec_Packet.m_ReadDepth = 0;
			vec_Packet.m_ReadHeight++;
			if(vec_Packet.m_ReadHeight >= vec_Packet.m_Height)
				{
				vec_Packet.m_ReadHeight = 0;
				}
			}

		SDL_mutexV(g_mutex_Packet);

		unsigned char i_PacketIdentifier = acPacketIdentifier(m_packet);

		printf("i_PacketIdentifier %i\n", i_PacketIdentifier);

#ifdef PTRSTREAMS
		BitTransfer* i_BitTransfer = new BitTransfer(m_packet->data, m_packet->length, false);
#else
		BitTransfer i_BitTransfer(m_packet->data, m_packet->length, false);
#endif

		float i_TimeStamp = i_BitTransfer.acTimeStamp();
		unsigned char i_PacketIdent = i_BitTransfer.acTag();

		printf("unServer ::: Packet Recieve %i\n", i_PacketIdent);

		switch(i_PacketIdentifier)
			{
			case ID_NEW_INCOMING_CONNECTION:	//////FIME OPTIMISATIONS: All processing and memory allocation to master functions
				{
				printf("ID_CONNECTION_REQUEST_ACCEPTED from %s\n", m_packet->systemAddress.ToString());
				g_rakVoice.RequestVoiceChannel(m_packet->systemAddress);
				}break;

			/*case ID_NEW_INCOMING_CONNECTION:	//////FIME OPTIMISATIONS: All processing and memory allocation to master functions
				{
				printf("Interface Client Connect\n");

				unsigned int binAddress;
				unsigned short sysport;

#ifdef PTRSTREAMS
				i_BitTransfer->acRead(binAddress);
				i_BitTransfer->acRead(sysport);
#else
				i_BitTransfer.acRead(binAddress);
				i_BitTransfer.acRead(sysport);
#endif

				SystemAddress* sysAddress = new SystemAddress();
				sysAddress->binaryAddress = binAddress;
				sysAddress->port = 10000;

				g_map_SysAddress[ m_packet->systemIndex ] = sysAddress;

				SystemAddress sysAddressST = m_packet->systemAddress;
				sysAddressST.port = 10000;

				g_map_SysAddressST[ m_packet->systemIndex ] = &sysAddressST;
				}break;

			case ID_CLIENT_IDENT:
				{
				printf("unServer: ID_CLIENT_IDENT\n");
 
#pragma message("FIXME Class Optimise Variable Reciever")
				char* name = new char;
				char* password = new char;
				unsigned short i_ClientID;

				i_BitTransfer.acRead(i_ClientID);

#ifdef PTRSTREAMS
				g_unStringCompressor->DecodeString(name, UNS_LINE_MAX, i_BitTransfer);
				g_unStringCompressor->DecodeString(password, UNS_LINE_MAX, i_BitTransfer);
#else
				g_unStringCompressor->DecodeString(name, UNS_LINE_MAX, &i_BitTransfer);
				g_unStringCompressor->DecodeString(password, UNS_LINE_MAX, &i_BitTransfer);
#endif

				/////// Temporarily store client and password //////
				g_map_ClientName[m_packet->systemIndex] = name;
				g_map_ClientPassword[m_packet->systemIndex] = password;
				printf("unServerOsirus ::: user logon %s\n", name);

#ifdef USE_MYSQL
				sMaster->acRecieveClient(name, password);
				sMaster->acModPacket(m_packet);
#endif

#if 0
				/////// Send a Character Data Start Resource Request ///////
				UNSRequest *i_ResourceRequest = new UNSRequest;
				i_ResourceRequest->m_RequestType = UNS_RES_CHAR_START;

				i_ResourceRequest->timeStamp = i_TimeStamp;
				i_ResourceRequest->typeId = i_PacketIdent;

				i_ResourceRequest->m_SysAddress = m_packet->systemIndex;
				i_ResourceRequest->m_Count = 0;

				SDL_mutexP(g_mutex_Requests);
				g_UNSResRequest.push_back(i_ResourceRequest);
				SDL_mutexV(g_mutex_Requests);
#endif
				}break;*/

			case ID_DISCONNECTION_NOTIFICATION:
			case ID_CONNECTION_LOST:
				{
				//bool i_Success = g_Domain.acAvatarShutdownClient(m_packet->systemIndex);
				//if(i_Success) printf("REPORT:::Domain 'Default' client disconnects %i\n", m_packet->systemIndex);
				//else printf("ERROR:::Domain 'Default' cannot find and disconnect client %i\n", m_packet->systemIndex);
				}break;
			}
		}

	SDL_mutexV(g_mutex_Packet);
}

	//i_BitTransfer->acRead(m_ArchiveID);
	//### Send Mouse Bytes
	//i_BitTransfer->acRead(player->CDATA.CharDATA[m_Index].TEAM);
	//i_BitTransfer->acRead(player->CDATA.CharDATA[m_Index].Class);
	//i_BitTransfer->acRead(player->CDATA.CharDATA[m_Index].Level);
	//i_BitTransfer->acRead(player->CDATA.CharDATA[m_Index].AvatarSCALE);

#if 0
	//##### - Set ITEM Name
	g_unStringCompressor->DecodeString(player->CDATA.CharDATA[m_Index].ItemDATA[jet].Name, 256, i_BitTransfer);
#endif