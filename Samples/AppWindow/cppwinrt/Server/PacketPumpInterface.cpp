/*

    m_PacketPumpInterface - unServer packet reading thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include <string>
#include <vector>
#include <cstdio>
#include <conio.h>
#include "PacketPumpInterface.h"
#include "PacketSocketInterface.h"

#include "../UnSRC/QActiveFramewrk.h"

#include "UNSResource.h"

#include "../UnSRC/Utility/unConsole.h"
#include "../DigitalMass/Source/Geometry/unTrrCellSettings.h"

#pragma message ("-~~THE QUANTUM ANGEL CODEX~~-")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"
#include "Q-WE-BulletSystem.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-CloudControl.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-NNbot.h"

#if 1
#define AVATAR_PHYSICS_ENABLE 1
#else
#define AVATAR_PHYSICS_ENABLE 0
#endif

PacketPumpInterface::PacketPumpInterface(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(PacketPumpInterface)
	SUPPORT_THREAD_NOTIFICATION
}

PacketPumpInterface::~PacketPumpInterface()
{
}

void PacketPumpInterface::Initialize(void)
{
	//SDL_mutexP(m_mutex_State);
	m_PP_STATE = 1;
	//SDL_mutexV(m_mutex_State);

	m_acClientSendStart = false;
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int PacketPumpInterface::ThreadHandler()
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

unsigned char PacketPumpInterface::acPacketIdentifier(Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	else
		return (unsigned char) p->data[0];
}

void PacketPumpInterface::Run(void)
{
	while(m_PP_STATE > 0) Scan();
}

bool PacketPumpInterface::Scan(void)
{
	//SDL_mutexP(m_mutex_Packet);

	if(m_vec_Packet[0].m_vec_Packet.size() > 0)
		{
		m_packet = m_vec_Packet[0].m_vec_Packet[0];

#ifdef UNS_PRINT_LVL
		printf("[Packet(");
#endif

		for(unsigned int f_Sow = 1; f_Sow < m_vec_Packet[0].m_vec_Packet.size(); f_Sow++)
			{
			m_vec_Packet[0].m_vec_Packet[f_Sow - 1] = m_vec_Packet[0].m_vec_Packet[f_Sow];
			}

		m_vec_Packet[0].m_vec_Packet.pop_back();

		//SDL_mutexV(m_mutex_Packet);

		if(!m_packet) return false;

		unsigned char i_PacketIdentifier = acPacketIdentifier(m_packet);

#ifdef UNS_PRINT_LVL
		printf("%i)\n", i_PacketIdentifier);
#endif

#ifdef PTRSTREAMS
		BitTransfer* i_BitTransfer = new BitTransfer(m_packet->data, m_packet->length, false);
#else
		BitTransfer i_BitTransfer(m_packet->data, m_packet->length, false);
#endif

		float i_TimeStamp = i_BitTransfer.acTimeStamp();
		unsigned char i_PacketIdent = i_BitTransfer.acTag();

		//printf("unClient ::: Packet Recieve %i\n", i_PacketIdent);

		switch(i_PacketIdentifier)
			{
			case ID_SERVER_IDENT:
				{
				printf("unClient: ID_SERVER_IDENT\n");
				}break;

			case ID_CONNECTION_REQUEST_ACCEPTED:
				{
				printf("unClient: ID_CONNECTION_REQUEST_ACCEPTED\n");

				//*serveAddress = m_packet->systemAddress;
				
				if(m_PP_STATE == 1)
					{
					if(m_PP_MODE == 0) acNetLogon();
					if(m_PP_MODE == 1) acOSINetLogon();
					}
#if 1
				char message[2048];
				//*RakNetStatistics *rss;
				//*rss=m_unPeer->GetStatistics(m_unPeer->GetSystemAddressFromIndex(0));
				//*StatisticsToString(rss, message, 2);
				//*printf("%s", message);
				//*printf("Ping=%i\n", m_unPeer->GetAveragePing(m_unPeer->GetSystemAddressFromIndex(0)));
#endif
				}break;

			case ID_MODIFIED_PACKET:
				{
				printf("Packet: ID_MOT\n");
				}break;

			case ID_CONNECTION_LOST:
				{
				printf("USER ::: Lost Connection to unServer\n");
				}break;

			case ID_CONNECTION_ATTEMPT_FAILED:
				{
				printf("USER ::: Connection Attempt Failed\n");
				}break;

			case UNS_RESOURCE_LINE:
				{
				printf("USER ::: Resource Line Recieved\n");

				char* i_line = new char[UNS_LINE_MAX];

				//*stringCompressor->DecodeString(i_line, UNS_LINE_MAX, &i_BitTransfer);

				printf("%s\n", i_line);
				}break;

			case UNS_RESOURCE_DATA:
				{
				char* i_line = new char[UNS_LINE_MAX];

				//*stringCompressor->DecodeString(i_line, UNS_LINE_MAX, &i_BitTransfer);

				//*m_QActiveFramework->m_GUI->acPush(i_line);

				printf("%s\n", i_line);
				}break;

			case UNS_RESOURCE_PAGE:
				{
				char* i_line = new char[UNS_LINE_MAX];

				//*stringCompressor->DecodeString(i_line, UNS_LINE_MAX, &i_BitTransfer);

				printf("%s\n", i_line);
				}break;

			case ID_SERVER_CHAR_START:
				{
				//SDL_mutexP(m_mutex_State);
				m_PP_STATE_I = m_PP_STATE;
				//SDL_mutexV(m_mutex_State);

				if(m_PP_STATE_I < 2)
					{
					//SDL_mutexP(m_mutex_State);
					m_PP_STATE = 2;
					//SDL_mutexV(m_mutex_State);

					printf("unClient: ID_SERVER_CHAR_START\n");
					i_BitTransfer.acRead(player[g_Player]->MaxNomCharacters);

					BitTransfer i_BitSend(ID_CLIENT_CHAR_START);
 
					i_BitSend.acPushAlloc(player[g_Player]->BFO.NomCharacters);
					printf("Player NomCharacters %i\n", player[g_Player]->BFO.NomCharacters);

					//*m_unPeer->Send((const char*)i_BitSend.m_Data, i_BitSend.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);

					if(!acClientSendCharacterData())
						{
						printf("ERROR: Networking failed to send player character data\n");
						for(;;) {};
						}
					}
				}break;

			case ID_SERVER_CHAR_DATA:
				{
				printf("Packet: ID_SERVER_CHAR_DATA\n");

				unsigned int i_CharacterID = acClientRecieveCharacterData(&i_BitTransfer);
				if(m_IndexM >= player[g_Player]->CDATAS[m_VecID].NomCharacters) player[g_Player]->CDATAS[m_VecID].NomCharacters = m_IndexM + 1;
				printf("player[g_Player]->CDATAS[%i].NomCharacters++ %i\n", m_VecID, player[g_Player]->CDATAS[m_VecID].NomCharacters);

				int f_XTB = 0;
				for(int f_Array = 0; f_Array < player[g_Player]->BFO.GamePlayersNom; f_Array++)
					{
					f_XTB = f_XTB + player[g_Player]->CDATAS[f_Array].NomCharacters;
					}

				if(f_XTB >= player[g_Player]->MaxNomCharacters)
					{
					//SDL_mutexP(m_mutex_State);
					m_PP_STATE_I = m_PP_STATE;
					//SDL_mutexV(m_mutex_State);

					if(m_PP_STATE_I < 3)
						{
						//SDL_mutexP(m_mutex_State);
						m_PP_STATE = 3;
						//SDL_mutexV(m_mutex_State);

						if(!acClientSendStart())
							{
							printf("ERROR: Networking failed to send client start\n");
							}
						}
					}
				}break;

			case ID_CLIENT_CHAR_RECIEVED:
				{
				//SDL_mutexP(m_mutex_State);
				m_PP_STATE_I = m_PP_STATE;
				//SDL_mutexV(m_mutex_State);

				if(m_PP_STATE_I < 3)
					{
					//SDL_mutexP(m_mutex_State);
					m_PP_STATE = 3;
					//SDL_mutexV(m_mutex_State);

					if(!acClientSendStart())
						{
						printf("ERROR: Networking failed to send character data\n");
						}
					}

				}break;

			case ID_LOGIN_ERROR:
				{
				printf("ID_LOGIN_ERROR recieved\n");
				}break;

			case ID_SERVER_START:
				{
				//SDL_mutexP(m_mutex_State);
				m_PP_STATE_I = m_PP_STATE;
				//SDL_mutexV(m_mutex_State);

				if(m_PP_STATE_I <= 3)
					{
					//SDL_mutexP(m_mutex_State);
					m_PP_STATE = 4;
					//SDL_mutexV(m_mutex_State);

					printf("Packet: ID_SERVER_START\n");
					bool f_BoolNetAvatar;
					int f_NomAI;

					i_BitTransfer.acRead(m_ClientVectorID);

					i_BitTransfer.acRead(m_ClientAvatarID);

					i_BitTransfer.acRead(f_NomAI);

					printf("********\n");
					printf("********\n");
					printf("******** ID_SERVER_START::: _->NomAI %i m_ClientVectorID %i\n", f_NomAI, m_ClientVectorID);

					for(int i_AVID = 0; i_AVID < f_NomAI; i_AVID++)
						{
						i_BitTransfer.acRead(m_VectorID);
						i_BitTransfer.acRead(f_BoolNetAvatar);

						printf("ID_SERVER_START::: NomAI %i m_VectorID %i f_BoolNetAvatar %i\n", i_AVID, m_VectorID, f_BoolNetAvatar);

						i_BitTransfer.acRead(m_CDATID);
						i_BitTransfer.acRead(m_BDATID);
						i_BitTransfer.acRead(m_Team);

						//Q_Netplayer->Netplayer[_->NETNomNetplayer].ID = _->NomAI;
						//Q_Netplayer->Netplayer[_->NETNomNetplayer].Spawned = 0;
						//Q_Netplayer->Netplayer[_->NETNomNetplayer].SpawnREADY = 0;
						//Q_Netplayer->Netplayer[_->NETNomNetplayer].Live = 1;

#pragma message("Only functional for single avatar matches, any added AI avatars prob")
#if 1
						if(/*(f_BoolNetAvatar == false) &&*/ i_AVID != m_ClientVectorID)
							{
#if 0
							acStartNetplayer(m_Position, m_Turn, m_VectorID, m_CDATID, m_BDATID, m_Team, i_AVID);
#endif
							}
						else
							{
							player[g_Player]->NetAvatarID = i_AVID;
							Q_Forge->Forge[player[g_Player]->NetAvatarID].LIVE = 0;
							//player[g_Player]->SysIndex = f_SysIndex;
							//_->NomAI++;
							}
#endif
						}

					printf("********\n");
					printf("********\n");
					printf("******** ID_SERVER_START::: player[g_Player]->NetAvatarID %i\n", player[g_Player]->NetAvatarID);

					//##### SEND FIRST START CLIENT WORLD PACKET #####//
					QNetwork.m_transfer = new BitTransfer(ID_CLIENT_WORLD);
					//*QNetwork.TransmitWorld(RakNet::GetTime(), m_ClientAvatarID);

					//*m_unPeer->Send((const char*)QNetwork.m_transfer->m_Data, QNetwork.m_transfer->acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
					}
				else
					{
					printf("ERROR:::Networking ASSERTION STATE 3:::ID_SERVER_START packetpumpinterface in state %i\n", m_PP_STATE_I);
					}

				}break;

			case ID_SERVER_JOIN:
				{
#if 0
				//SDL_mutexP(m_mutex_State);
				m_PP_STATE_I = m_PP_STATE;
				//SDL_mutexV(m_mutex_State);

				bool f_BoolNetAvatar;
				int f_NomAI;

				if(m_PP_STATE_I == 3 || m_PP_STATE_I == 4 || m_PP_STATE_I == 5)
					{
					//SDL_mutexP(m_mutex_State);
					m_PP_STATE = 5;
					//SDL_mutexV(m_mutex_State);

					i_BitTransfer.acRead(f_NomAI);

					printf("Packet: ID_SERVER_JOIN _->NomAI %i\n", f_NomAI);

					for(int i_AVID = 0; i_AVID < f_NomAI; i_AVID++)
						{
						i_BitTransfer.acRead(m_VectorID);

						printf("ID_SERVER_JOIN Avatar ID %i m_VectorID %i\n", i_AVID, m_VectorID);

						i_BitTransfer.acRead(m_CDATID);
						i_BitTransfer.acRead(m_BDATID);
						i_BitTransfer.acRead(m_Team);

						if(m_VectorID != m_ClientVectorID)
							{
#if 1
							acStartNetplayer(m_Position, m_Turn, m_VectorID, m_CDATID, m_BDATID, m_Team, i_AVID);
#endif
							}
						}
					}
				else
					{
					printf("ERROR:::Networking ASSERTION STATE 3 | 4 | 5 :::ID_SERVER_JOIN PPinterface in state %i\n", m_PP_STATE_I);
					printf("BYPASS JOIN PACKET ... Continue ... \n");
					}
#endif

				//##### SEND FIRST START CLIENT WORLD PACKET #####//
				QNetwork.m_transfer = new BitTransfer(ID_CLIENT_WORLD);
				//*QNetwork.TransmitWorld(RakNet::GetTime(), m_ClientAvatarID);

				//*m_unPeer->Send((const char*)QNetwork.m_transfer->m_Data, QNetwork.m_transfer->acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
				}break;

			case ID_SERVER_WORLD:
				{
				//SDL_mutexP(m_mutex_State);
				m_PP_STATE_I = m_PP_STATE;
				//SDL_mutexV(m_mutex_State);

#if 1
				printf("Packet: ID_SERVER_WORLD\n");
#endif

				if(m_PP_STATE_I >= 4)
					{
					float f_Time = 0;
					//SDL_mutexP(m_mutex_Packet);

					QNetwork.m_transfer = &i_BitTransfer;
					QNetwork.RecieveWorld(f_Time, m_ClientAvatarID);

					//SDL_mutexV(m_mutex_Packet);

#if 0
					QNetwork.m_transfer = new BitTransfer(ID_CLIENT_WORLD);
					QNetwork.TransmitWorld(RakNet::GetTime(), m_ClientAvatarID);

					m_unPeer->Send((const char*)QNetwork.m_transfer->m_Data, QNetwork.m_transfer->acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
#endif
					}

				}break;

			case ID_SERVER_AMATCH:
				{
				printf("unClient: ID_SERVER_ARENA_MATCH\n");

				//*i_BitTransfer.acRead(player[g_Player]->BFO.GameServerAddress);

				i_BitTransfer.acRead(player[g_Player]->BFO.GameMap);

				i_BitTransfer.acRead(player[g_Player]->Team);

				i_BitTransfer.acRead(player[g_Player]->BFO.GamePlayersNom);

				printf("player[g_Player]->BFO.GamePlayersNom %i\n", player[g_Player]->BFO.GamePlayersNom);

				player[g_Player]->BFO.GameAvatarsMaxAmt = 0;

				for(int f_FF = 0; f_FF < player[g_Player]->BFO.GamePlayersNom; f_FF++)
					{
					int f_PushOne = 0;
					i_BitTransfer.acRead(f_PushOne);
					printf("player[g_Player]->BFO.vec_PlayersNom[%i] %i\n", f_FF, f_PushOne);
					player[g_Player]->BFO.vec_PlayersNom.push_back(f_PushOne);
					player[g_Player]->BFO.GameAvatarsMaxAmt += f_PushOne + 1;
					}

				printf("GO GAME! Team %i\n", player[g_Player]->Team);

				//###- Close Connection -###//
				printf("unClient: Disconnect from OsiStage reconnect unServer QA Arena Server\n");
				//*m_unPeer->CloseConnection(serveAddress, true);

				//*m_QActiveFramework->acNetConnectQAA();//*player[g_Player]->BFO.GameServerAddress);
				}
			}
		}

	//SDL_mutexV(m_mutex_Packet);

	return true;
}

bool PacketPumpInterface::acNetLogon(void)
{
#pragma message("FIXME:Optimize")
	const char *i_Name = "Mellodi";
	const char *i_Password = "intprop18";

	printf("unClient:::acNetLogon\n");

	BitTransfer i_BitTransfer(ID_CLIENT_IDENT);

	//*i_BitTransfer.acPushAlloc(clientAddress.port);

	//*stringCompressor->EncodeString(i_Name, UNS_LINE_MAX, &i_BitTransfer);
	//*stringCompressor->EncodeString(i_Password, UNS_LINE_MAX, &i_BitTransfer);

	//###--- Match Information for unServer ---##//

	i_BitTransfer.acPushAlloc(player[g_Player]->BFO.GameMap);

	i_BitTransfer.acPushAlloc(player[g_Player]->Team);

	i_BitTransfer.acPushAlloc(player[g_Player]->BFO.GamePlayersNom);

	//RakNet::RakString f_Name = i_Name;
	//RakNet::RakString f_Password = i_Password;

	//int useTimeStamp;
	//long timeStamp;
	//int typeId;

	//useTimeStamp = ID_TIMESTAMP;
	//timeStamp = RakNet::GetTime();
	//typeId = UNS_REQUEST_LINE;

	//int DATA_CHUNK_SIZE = 120;

	//BitStream *i_BitStream = new RakNet::BitStream(DATA_CHUNK_SIZE);

	//i_BitStream->WriteBits( (const unsigned char *)&useTimeStamp, sizeof(int), true );
	//i_BitStream->WriteBits( (const unsigned char *)&timeStamp, sizeof(long), true );
	//i_BitStream->WriteBits( (const unsigned char *)&typeId, sizeof(int), true );

	//i_BitStream->Serialize(f_Name, i_BitStream);
	//i_BitStream->Serialize(f_Password, i_BitStream);

	//m_unPeer->Send(i_BitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);

	//if(!m_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize() + 1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false))
	//	{
	//	printf("ERROR: Networking failed to send client identification\n");
	//	return false;
	//	}
	//else printf("unClient:::acNetLogon:::Identification packet sent\n");

	/*while(true)
	{
	if (kbhit())
		{
			char message[2048];
			// Notice what is not here: something to keep our network running.  It's
			// fine to block on gets or anything we want
			// Because the network engine was painstakingly written using threads.
			gets(message);

			if (strcmp(message, "quit")==0)
			{
				puts("Quitting.");
			}

			if (strcmp(message, "stat")==0)
			{
				
				RakNetStatistics *rss;
				rss=m_unPeer->GetStatistics(m_unPeer->GetSystemAddressFromIndex(0));
				StatisticsToString(rss, message, 2);
				printf("%s", message);
				printf("Ping=%i\n", m_unPeer->GetAveragePing(m_unPeer->GetSystemAddressFromIndex(0)));
			}

			if (strcmp(message, "disconnect")==0)
			{
				printf("Enter index to disconnect: ");
				char str[32];
				gets(str);
				if (str[0]==0)
					strcpy(str,"0");
				int index = atoi(str);
				m_unPeer->CloseConnection(m_unPeer->GetSystemAddressFromIndex(index),true);
				printf("Disconnecting.\n");
			}

			if (strcmp(message, "shutdown")==0)
			{
				m_unPeer->Shutdown(100);
				printf("Shutdown.\n");
			}

			if (strcmp(message, "ping")==0)
			{
				if (m_unPeer->GetSystemAddressFromIndex(0)!=UNASSIGNED_SYSTEM_ADDRESS)
					m_unPeer->Ping(m_unPeer->GetSystemAddressFromIndex(0));
			}

			if (strcmp(message, "getlastping")==0)
			{
				if (m_unPeer->GetSystemAddressFromIndex(0)!=UNASSIGNED_SYSTEM_ADDRESS)
					printf("Last ping is %i\n", m_unPeer->GetLastPing(m_unPeer->GetSystemAddressFromIndex(0)));
			}*/

			// message is the data to send
			// strlen(message)+1 is to send the null terminator
			// HIGH_PRIORITY doesn't actually matter here because we don't use any other priority
			// RELIABLE_ORDERED means make sure the message arrives in the right order
			//m_unPeer->Send(message, (int) strlen(message)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, false);
			//m_unPeer->Send(i_BitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, false);
			//*m_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
		//}
	//}

	return true;
}

bool PacketPumpInterface::acOSINetLogon(void)
{
#pragma message("FIXME:Optimize")
	const char *i_Name = "Mellodi";
	const char *i_Password = "intprop18";

	printf("unClient:::acNetLogon\n");

	BitTransfer i_BitTransfer(ID_CLIENT_IDENT);

	//*i_BitTransfer.acPushAlloc(clientAddress.port);

	//*stringCompressor->EncodeString(i_Name, UNS_LINE_MAX, &i_BitTransfer);
	//*stringCompressor->EncodeString(i_Password, UNS_LINE_MAX, &i_BitTransfer);
	
	//*m_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);

	BitTransfer i_BitTransferOSI(ID_ARENA_PLAYER);

	//*stringCompressor->EncodeString(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Name.c_str(), UNS_LINE_MAX, &i_BitTransferOSI);
	
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.NomAvatars);
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.GameTypeSelect);
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.GameMap);

	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.m_GameWagerITP);
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.m_GameID_ITP);

	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.m_UsernameITP);
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.m_PasswordITP);
	i_BitTransferOSI.acPushAlloc(player[g_Player]->BFO.m_Region);

	//*i_BitTransferOSI.acPushAlloc(clientAddress.port);

	//*return m_unPeer->Send((const char*)i_BitTransferOSI.m_Data, i_BitTransferOSI.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
	return true;
}

bool PacketPumpInterface::acClientSendStart(void)
{
	if(!m_acClientSendStart)
		{
		m_acClientSendStart = true;
		printf("unClient:::acClientSendStart()\n");
		BitTransfer i_BitTransfer(ID_CLIENT_START);

		printf("CDATAID %i BDATAID %i TEAM %i\n", player[g_Player]->BFO.CurrCHAR, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF, player[g_Player]->Team);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CurrCHAR);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF);
		i_BitTransfer.acPushAlloc(player[g_Player]->Team);

		/*int f_Tick = 0;
		for(unsigned int f_index = 0; f_index < _->NomAI; f_index++)
			{
			if(Q_Forge->Forge[f_index].LIVE == 1 && Q_Forge->Forge[f_index].m_Own == 1)
				{
				f_Tick++;
				}
			}

		i_BitTransfer.acPushAlloc(f_Tick);

		for(unsigned int f_index = 0; f_index < _->NomAI; f_index++)
			{
			if(Q_Forge->Forge[f_index].LIVE == 1 && Q_Forge->Forge[f_index].m_Own == 1)
				{
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.AVATARDATA[helly].CDATID);
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.AVATARDATA[helly].BDATID);
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.AVATARDATA[helly].TEAM);
				}
			}*/

		int f_Tick = 0;
		for(unsigned int f_index = 0; f_index < _->NomAI; f_index++)
			{
			if(player[g_Player]->BFO.AVATARDATA[helly].LIVE == 1)
				{
				f_Tick++;
				}
			}

		i_BitTransfer.acPushAlloc(f_Tick);

		for(unsigned int f_index = 0; f_index < _->NomAI; f_index++)
			{
			if(player[g_Player]->BFO.AVATARDATA[helly].LIVE == 1)
				{
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.AVATARDATA[helly].CDATID);
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.AVATARDATA[helly].BDATID);
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.AVATARDATA[helly].TEAM);
				}
			}

		//return m_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
		return true;
		}

	return false;
}

bool PacketPumpInterface::acClientSendCharacterData(int i_Archive)
{
	printf("unClient:::acClientSendCharacterData()\n");

	for(int f_AVIDent = 0; f_AVIDent < player[g_Player]->BFO.NomCharacters; f_AVIDent++)
		{
		BitTransfer i_BitTransfer(ID_CLIENT_CHAR_DATA, BT_CHAR_DATA);

		i_BitTransfer.acPushAlloc(f_AVIDent);

	#if 0
		stringCompressor->EncodeString(player[g_Player]->BFO.CharDATA[f_AVIDent].AvatarREF, 256, &i_BitTransfer);
		stringCompressor->EncodeString(player[g_Player]->BFO.CharDATA[f_AVIDent].ShadowREF, 256, &i_BitTransfer);
	#else
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AvatarREF);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ShadowREF);
	#endif

		//### Send Mouse Bytes
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].TEAM);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Class);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Level);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AvatarSCALE);

		//### Send Key Bytes
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].UnusedXP);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.EnergyEff);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.LeftArmSTRENGTH);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.RightArmSTRENGTH);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.LeftLegSTRENGTH);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.RightLegSTRENGTH);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.LeftArmSNAP);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.RightArmSNAP);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.LeftLegSNAP);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.RightLegSNAP);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.Height);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.Weight);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.PhysicalStr);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.Quickness);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.Dexterity);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.Constitution);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.AggPower);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].BodySKILL.DefPower);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].WeaponSKILL.Accuracy);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].WeaponSKILL.DrawSPD);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].WeaponSKILL.ReloadSPD);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].WeaponSKILL.RecoilHEIGHTrecover);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.TrailTYPE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.TrailRED);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.TrailGREEN);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.TrailBLUE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.TrailALPHA);
	
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.JinkTYPE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.JinkRED);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.JinkGREEN);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.JinkBLUE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.JinkALPHA);
	
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SteamTYPE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SteamRED);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SteamGREEN);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SteamBLUE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SteamALPHA);
	
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SpikeTYPE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SpikeRED);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SpikeGREEN);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SpikeBLUE);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelEFFECTS.SpikeALPHA);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellContainerID[0]);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellContainerID[1]);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellContainerID[2]);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellContainerID[3]);

		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CurrWEAPON);
		//i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CurrHEADARMOUR);
		i_BitTransfer.acPushAlloc(4);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CurrUPPERARMOUR);
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CurrLOWERARMOUR);

		//######### -  ITEM DATA LOOP  - #########

		//### Number of Items
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].NomITEMS);

		jet=0;
		while(jet < player[g_Player]->BFO.CharDATA[f_AVIDent].NomITEMS)
			{
	#if 1
			//##### - Set ITEM Name
			//*stringCompressor->EncodeString(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Name, 256, &i_BitTransfer);
	#endif

			//##### - Set Item Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Type);

			//##### - Set Item Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ItemREF);

	#if 1
			if(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Type == 0)
				{
				//##### - Set Character Item Actor Reference
				//*stringCompressor->EncodeString(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ItemActorREF, 256, &i_BitTransfer);
				}
	#endif

			//##### - Set Item Scale Factor
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ItemScaleFACT);

			//##### - Set Item Quality Level
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QualLVL);

			//##### - Get Item Damage
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Damage);

			//##### - Get Item Power
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Power);

			//##### - Get Item Ammo
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Ammo);

			//##### - Get Item Recoil
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].RecoilHeight);

			//##### - Get Item Recoil
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].RecoilDistance);

			//##### - Get Item Fire Rate
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FireRate);

			//##### - Get Item Accuracy
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Accuracy);

			//##### - Set Item Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].BulletCNT);

			//##### - Set Item Scope Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ScopeTYPE);

			//##### - Set Item Scope Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ScopeLOC.x);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ScopeLOC.y);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ScopeLOC.z);

			//##### - Set Item Laser Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].LaserTYPE);

			//##### - Set Item Laser Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].LaserLOC.x);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].LaserLOC.y);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].LaserLOC.z);

			//##### - Set Item Sound
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QAS_Fire);

			//##### - Set Item Sound
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QAS_ReloadBoltOut);

			//##### - Set Item Sound
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QAS_ReloadBoltIn);

			//##### - Set Item Sound
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QAS_ReloadClipOut);

			//##### - Set Item Sound
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QAS_ReloadClipIn);

			//##### - Get Item Armour
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ArmourFACTOR);

			//##### - Get Item Armour
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ArmourAMOUNT);

			//##### - Get Item Armour
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ArmourREGEN);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Smoke.CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[0].CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[1].CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[2].CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[3].CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Effect[4].CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].Fog.CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.TYPE);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.INT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.ON);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.Red);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.Green);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.Blue);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.Alpha);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.Scale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.TIMER);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].FogLight.CNT);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].ExpandSTRENGTH);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_NoWEP);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_TimeScale);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Gravity);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_LifeINC);

			//##### - Set Item Attribute
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_EnergyINC);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_IntBoost);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_EnergyEff);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Height);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Weight);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Strength);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Quickness);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Dexterity);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_Constitution);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_AggPower);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_DefPower);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_RArmStr);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_LArmStr);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_RLegStr);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_LLegStr);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_RArmSnap);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_LArmSnap);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_RLegSnap);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_LLegSnap);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_WEPAccuracy);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_WEPDrawSPD);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_WEPReloadSPD);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_WEPRecoilHR);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_JINKmovespeed);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_JINKpower);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].ItemDATA[jet].QA_ITEMINC_JINK3intensity);

			jet++;
			}

		//#### ACTIVE SPELLS
		jet=0;
		while(jet < 3)
			{
			//##### - Get Item QA Effect Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_TYPE);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_INTENSITY);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_SWITCH);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL00RED);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL00GREEN);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL00BLUE);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL00ALPHA);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL01RED);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL01GREEN);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL01BLUE);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL01ALPHA);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL02RED);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL02GREEN);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL02BLUE);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL02ALPHA);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL03RED);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL03GREEN);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL03BLUE);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL03ALPHA);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL04RED);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL04GREEN);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL04BLUE);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_EFFECT_COL04ALPHA);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_IntBoost);

			//##### - Get Item Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_EnergyEff);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_Height);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_Weight);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_Strength);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_Quickness);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_Dexterity);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_Constitution);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_AggPower);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_DefPower);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_RArmStr);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_LArmStr);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_RLegStr);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_LLegStr);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_RArmSnap);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_LArmSnap);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_RLegSnap);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_LLegSnap);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_WEPAccuracy);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_WEPDrawSPD);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_WEPReloadSPD);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_WEPRecoilHR);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_JINKmovespeed);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_JINKpower);

			//##### - Get SPELL Attributes
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].QA_SPELLINC_JINK3intensity);

			//##### - Set Item QA Effect Intensity
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].SpellSLOT[jet].LIVE);

			jet++;
			}

		//######### -  Physical Attacks SPEC DATA LOOP  - #########

		jet=0;
		while(jet < 30)
			{
			//##### - Get Item Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AttackSKILL[jet].Power);

			//##### - Get Item Damage
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AttackSKILL[jet].Damage);

			//##### - Get Item Power
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AttackSKILL[jet].MoveSpeed);

			//##### - Get Item Ammo
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AttackSKILL[jet].NumRotate);

			//##### - Get Item Recoil
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AttackSKILL[jet].ExpRadius);

			//##### - Get Item Recoil
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AttackSKILL[jet].Accuracy);

			jet++;
			}


		//######### -  Cleric Class Skills LOOP  - #########

		jet=0;
		while(jet < 12)
			{
			//##### - Get Item Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CLSClericSKILL[jet].Cost);

			//##### - Get Item Damage
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CLSClericSKILL[jet].Potency);

			//##### - Get Item Power
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CLSClericSKILL[jet].Amount);

			//##### - Get Item Ammo
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CLSClericSKILL[jet].Speed);

			//##### - Get Item Recoil
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CLSClericSKILL[jet].Duration);

			//##### - Get Item Recoil
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].CLSClericSKILL[jet].Accuracy);

			jet++;
			}


		//######### -  SPELL DATA LOOP  - #########

		//### Number of Spells
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].NomSpells);

		jet=0;
		while(jet < player[g_Player]->BFO.CharDATA[f_AVIDent].NomSpells)
			{
			//##### - Get Spell Quality
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QualityLVL);

			//##### - Set Spell Attribute IDs
			SHADOW=0;
			while(SHADOW < 10)
				{
				i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].AttributeID[SHADOW]);
				SHADOW++;
				}

			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_TYPE);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_INTENSITY);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_SWITCH);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL00RED);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL00GREEN);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL00BLUE);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL00ALPHA);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL01RED);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL01GREEN);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL01BLUE);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL01ALPHA);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL02RED);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL02GREEN);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL02BLUE);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL02ALPHA);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL03RED);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL03GREEN);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL03BLUE);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL03ALPHA);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL04RED);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL04GREEN);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL04BLUE);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_EFFECT_COL04ALPHA);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_IntBoost);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_EnergyEff);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_Height);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_Weight);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_Strength);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_Quickness);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_Dexterity);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_Constitution);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_AggPower);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_DefPower);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_RArmStr);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_LArmStr);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_RLegStr);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_LLegStr);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_RArmSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_LArmSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_RLegSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_LLegSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_WEPAccuracy);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_WEPDrawSPD);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_WEPReloadSPD);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_WEPRecoilHR);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_JINKmovespeed);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_JINKpower);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_JINK3intensity);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_RArmSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_LArmSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_RLegSnap);
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].Spells[jet].QA_SPELLINC_LLegSnap);
			jet++;
			}


		//#### SEND ANGEL COLOUR EDIT
		i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelCOLOURS.ANGELEDITFLAG);

		jet2=0;
		while(jet2 < 38)
			{
			//##### - Get Item Type
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelCOLOURS.RED[jet2]);

			//##### - Get Item Damage
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelCOLOURS.GREEN[jet2]);

			//##### - Get Item Power
			i_BitTransfer.acPushAlloc(player[g_Player]->BFO.CharDATA[f_AVIDent].AngelCOLOURS.BLUE[jet2]);

			jet2++;
			}


		//*m_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);
		printf("send\n");
		}

	printf("exit\n");

	return true;
}

unsigned int PacketPumpInterface::acClientRecieveCharacterData(BitTransfer *i_BitTransfer)
{
	printf("acClientRecieveCharacterData\n");

	i_BitTransfer->acRead(m_VecID);
	i_BitTransfer->acRead(m_IndexM);

	if(m_VecID < 0 || m_VecID >= UNS_MAX_PLS || m_IndexM < 0 || m_IndexM >= 35)
		return 0;

#if 0
	stringCompressor->DecodeString(player[g_Player]->CDATAS[f_VecID].CharDATA[m_IndexM].AvatarREF, 12, i_BitTransfer);
	stringCompressor->DecodeString(player[g_Player]->CDATAS[f_VecID].CharDATA[m_IndexM].ShadowREF, 12, i_BitTransfer);
#else
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AvatarREF);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ShadowREF);
#endif

	//### Send Mouse Bytes
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].TEAM);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Class);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Level);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AvatarSCALE);

	//### Send Key Bytes
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].UnusedXP);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.EnergyEff);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.LeftArmSTRENGTH);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.RightArmSTRENGTH);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.LeftLegSTRENGTH);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.RightLegSTRENGTH);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.LeftArmSNAP);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.RightArmSNAP);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.LeftLegSNAP);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.RightLegSNAP);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.Height);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.Weight);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.PhysicalStr);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.Quickness);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.Dexterity);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.Constitution);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.AggPower);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].BodySKILL.DefPower);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].WeaponSKILL.Accuracy);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].WeaponSKILL.DrawSPD);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].WeaponSKILL.ReloadSPD);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].WeaponSKILL.RecoilHEIGHTrecover);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.TrailTYPE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.TrailRED);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.TrailGREEN);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.TrailBLUE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.TrailALPHA);
	
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.JinkTYPE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.JinkRED);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.JinkGREEN);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.JinkBLUE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.JinkALPHA);
	
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SteamTYPE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SteamRED);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SteamGREEN);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SteamBLUE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SteamALPHA);
	
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SpikeTYPE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SpikeRED);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SpikeGREEN);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SpikeBLUE);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelEFFECTS.SpikeALPHA);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellContainerID[0]);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellContainerID[1]);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellContainerID[2]);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellContainerID[3]);

	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CurrWEAPON);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CurrHEADARMOUR);
	printf("player[g_Player]->CDATAS[%i].CharDATA[%i].CurrHEADARMOUR %i\n", m_VecID, m_IndexM, player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CurrHEADARMOUR);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CurrUPPERARMOUR);
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CurrLOWERARMOUR);

	//######### -  ITEM DATA LOOP  - #########

	//### Number of Items
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].NomITEMS);

	jet=0;
	while(jet < player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].NomITEMS)
		{
#if 1
		//##### - Set ITEM Name
		//*stringCompressor->DecodeString(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Name, 10, i_BitTransfer);
#endif

		//##### - Set Item Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Type);

		//##### - Set Item Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ItemREF);

#if 1
		if(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Type == 0)
			{
			//##### - Set Character Item Actor Reference
			//*stringCompressor->DecodeString(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ItemActorREF, 15, i_BitTransfer);
			}
#endif

		//##### - Set Item Scale Factor
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ItemScaleFACT);

		//##### - Set Item Quality Level
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QualLVL);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Power);

		//##### - Get Item Ammo
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Ammo);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].RecoilHeight);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].RecoilDistance);

		//##### - Get Item Fire Rate
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FireRate);

		//##### - Get Item Accuracy
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Accuracy);

		//##### - Set Item Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].BulletCNT);

		//##### - Set Item Scope Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ScopeTYPE);

		//##### - Set Item Scope Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ScopeLOC.x);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ScopeLOC.y);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ScopeLOC.z);

		//##### - Set Item Laser Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].LaserTYPE);

		//##### - Set Item Laser Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].LaserLOC.x);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].LaserLOC.y);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].LaserLOC.z);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QAS_Fire);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QAS_ReloadBoltOut);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QAS_ReloadBoltIn);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QAS_ReloadClipOut);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QAS_ReloadClipIn);

		//##### - Get Item Armour
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ArmourFACTOR);

		//##### - Get Item Armour
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ArmourAMOUNT);

		//##### - Get Item Armour
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ArmourREGEN);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Smoke.CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[0].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[1].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[2].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[3].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Effect[4].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].Fog.CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].FogLight.CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].ExpandSTRENGTH);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_NoWEP);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_TimeScale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Gravity);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_LifeINC);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_EnergyINC);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_EnergyEff);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Height);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Weight);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Strength);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Quickness);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Dexterity);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_Constitution);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_AggPower);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_DefPower);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_RArmStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_LArmStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_RLegStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_LLegStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_RArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_LArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_RLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_LLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_WEPAccuracy);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_WEPDrawSPD);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_WEPReloadSPD);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_WEPRecoilHR);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_JINKmovespeed);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_JINKpower);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].ItemDATA[jet].QA_ITEMINC_JINK3intensity);

		jet++;
		}

	//#### ACTIVE SPELLS
	jet=0;
	while(jet < 3)
		{
		//##### - Get Item QA Effect Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_TYPE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_INTENSITY);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_SWITCH);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL00RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL00GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL00BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL00ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL01RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL01GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL01BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL01ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL02RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL02GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL02BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL02ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL03RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL03GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL03BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL03ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL04RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL04GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL04BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_EFFECT_COL04ALPHA);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_EnergyEff);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_Height);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_Weight);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_Strength);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_Quickness);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_Dexterity);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_Constitution);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_AggPower);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_DefPower);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_RArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_LArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_RLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_LLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_RArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_LArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_RLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_LLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_WEPAccuracy);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_WEPDrawSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_WEPReloadSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_WEPRecoilHR);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_JINKmovespeed);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_JINKpower);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].QA_SPELLINC_JINK3intensity);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].SpellSLOT[jet].LIVE);

		jet++;
		}

	//######### -  Physical Attacks SPEC DATA LOOP  - #########

	jet=0;
	while(jet < 30)
		{
		//##### - Get Item Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AttackSKILL[jet].Power);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AttackSKILL[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AttackSKILL[jet].MoveSpeed);

		//##### - Get Item Ammo
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AttackSKILL[jet].NumRotate);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AttackSKILL[jet].ExpRadius);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AttackSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  Cleric Class Skills LOOP  - #########

	jet=0;
	while(jet < 12)
		{
		//##### - Get Item Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CLSClericSKILL[jet].Cost);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CLSClericSKILL[jet].Potency);

		//##### - Get Item Power
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CLSClericSKILL[jet].Amount);

		//##### - Get Item Ammo
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CLSClericSKILL[jet].Speed);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CLSClericSKILL[jet].Duration);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].CLSClericSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  SPELL DATA LOOP  - #########

	//### Number of Spells
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].NomSpells);

	jet=0;
	while(jet < player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].NomSpells)
		{
		//##### - Get Spell Quality
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QualityLVL);

		//##### - Set Spell Attribute IDs
		SHADOW=0;
		while(SHADOW < 10)
			{
			i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].AttributeID[SHADOW]);
			SHADOW++;
			}

		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_TYPE);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_INTENSITY);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_SWITCH);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL00RED);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL00GREEN);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL00BLUE);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL00ALPHA);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL01RED);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL01GREEN);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL01BLUE);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL01ALPHA);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL02RED);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL02GREEN);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL02BLUE);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL02ALPHA);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL03RED);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL03GREEN);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL03BLUE);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL03ALPHA);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL04RED);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL04GREEN);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL04BLUE);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_EFFECT_COL04ALPHA);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_IntBoost);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_EnergyEff);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_Height);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_Weight);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_Strength);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_Quickness);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_Dexterity);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_Constitution);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_AggPower);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_DefPower);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_RArmStr);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_LArmStr);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_RLegStr);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_LLegStr);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_LLegSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_WEPAccuracy);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_WEPDrawSPD);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_WEPReloadSPD);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_WEPRecoilHR);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_JINKmovespeed);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_JINKpower);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_JINK3intensity);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].Spells[jet].QA_SPELLINC_LLegSnap);
		jet++;
		}


	//#### SEND ANGEL COLOUR EDIT
	i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelCOLOURS.ANGELEDITFLAG);

	jet2=0;
	while(jet2 < 38)
		{
		//##### - Get Item Type
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelCOLOURS.RED[jet2]);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelCOLOURS.GREEN[jet2]);

		//##### - Get Item Power
		i_BitTransfer->acRead(player[g_Player]->CDATAS[m_VecID].CharDATA[m_IndexM].AngelCOLOURS.BLUE[jet2]);

		jet2++;
		}

	return m_Index;
}


//###### START PLAYERS #######

bool PacketPumpInterface::acStartNetplayer(QpoVec3d i_Position, QpoVec3d i_Angles, int f_VecID, unsigned int i_CDATID, unsigned int i_BDATID, unsigned int i_Team, int i_SysIndex)
{
	if(Q_Forge->Forge[i_SysIndex].LIVE == 1 && Q_Forge->Forge[i_SysIndex].HB_Lives > 0)
		{
		return false;
		}
	else m_AVSLOT = i_SysIndex;

	printf("acStartNetplayer %i i_Position x %f y %f z %f\n", m_AVSLOT, i_Position.x, i_Position.y, i_Position.z);

	//Q_Forge->Forge[m_AVSLOT].m_Own = 0;
	Q_Forge->Forge[m_AVSLOT].LIVE = 1;
	Q_Forge->Forge[m_AVSLOT].HB_DeadTimer = 500;

	Q_Forge->Forge[m_AVSLOT].HB_Lives = 5;
	Q_Forge->Forge[m_AVSLOT].HB_LiveResetSW = 1;

	if(i_CDATID >= player[g_Player]->CDATAS[f_VecID].NomCharacters)
		{
		printf("ERROR:::acStartNetplayer:::f_VecID %i i_CDATID %i too high to be realistically used in function %i\n", f_VecID, i_CDATID, player[g_Player]->CDATAS[f_VecID].NomCharacters);
		i_CDATID = 0;
		for(;;) { }
		}

	if(i_BDATID >= m_QActiveFramework->meshShellTemplates.size())
		{
		printf("ERROR:::acStartNetplayer::: i_BDATID %i too high to be realistically used in function %i\n", i_BDATID, m_QActiveFramework->meshShellTemplates.size());
		i_BDATID = 0;
		for(;;) { }
		}

	Q_Forge->Forge[m_AVSLOT].CharDATA = player[g_Player]->CDATAS[f_VecID].CharDATA[i_CDATID];

	Q_Forge->Forge[m_AVSLOT].upspeed = -15;
	Q_Forge->Forge[m_AVSLOT].Mins.x = -30.f;
	Q_Forge->Forge[m_AVSLOT].Mins.y = -45.f;
	Q_Forge->Forge[m_AVSLOT].Mins.z = -30.f;
	Q_Forge->Forge[m_AVSLOT].Maxs.x = 30.f;
	Q_Forge->Forge[m_AVSLOT].Maxs.y = 45.f;
	Q_Forge->Forge[m_AVSLOT].Maxs.z = 30.f;

	Q_Forge->Forge[m_AVSLOT].PlayerSpeed = PLAYER_SPEED;

	Q_Forge->Forge[m_AVSLOT].GravityAlter = 1;

	Q_Forge->Forge[m_AVSLOT].NetMoveScale = 1;

	//Fill Weapon Ammo
	Q_Forge->Forge[m_AVSLOT].WeaponAmmo = 32;

	Q_Forge->Forge[m_AVSLOT].HB_Illumination = 255;
	Q_Forge->Forge[m_AVSLOT].HB_Dead = 0;

	//Body and Mind
	Q_Forge->Forge[m_AVSLOT].Q_Heart.HeartIncrement = 0;
	Q_Forge->Forge[m_AVSLOT].Q_Heart.PulseRate = 1;
	Q_Forge->Forge[m_AVSLOT].Q_Brain.Aggression = 70;

	Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID = i_BDATID;
	Q_Forge->Forge[m_AVSLOT].AVDATID = AVSLOT;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].AVATARID = AVSLOT;
	//Q_Forge->Forge[m_AVSLOT].NetplayerFLAG = 1;

	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].BDATID = i_BDATID;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].CDATID = i_CDATID;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].LIVE = 1;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].NETAVATAR = 1;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].TEAM = i_Team;

	//#### Set Role
	Q_Forge->Forge[m_AVSLOT].SysIndex = i_SysIndex;
	Q_Forge->Forge[m_AVSLOT].Team = i_Team;
	Q_Forge->Forge[m_AVSLOT].Role = 0;
	Q_Forge->Forge[m_AVSLOT].Rank = 1;
	Q_Forge->Forge[m_AVSLOT].LEVEL = Q_Forge->Forge[m_AVSLOT].CharDATA.Level;

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh = new unAvatar();

	if(Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF > 11 || Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF < 0) Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF = 0;

	//if(AVATAR_PHYSICS_ENABLE) m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh, Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID);
	//else m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID]->clone_struct(Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh);

	/*Q_Forge->Forge[m_AVSLOT].Xform.Translation.x = 0;
	Q_Forge->Forge[m_AVSLOT].Xform.Translation.y = 0;
	Q_Forge->Forge[m_AVSLOT].Xform.Translation.z = 0;
	Q_Forge->Forge[m_AVSLOT].Xform.Matrix.load_identity();

	//##### Starting position
	Ange.y = i_Angles.y + (PI);
	if(Ange.y > (2*PI)) Ange.y = Ange.y - (PI*2);
	if(Ange.y < 0) Ange.y = (PI*2) - Ange.y;
	Ange.x = (PI/2);
	Ange.z = 0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&Q_Forge->Forge[m_AVSLOT].Xform, Ange.x);
	Qpo->Transform_RotateY(&Q_Forge->Forge[m_AVSLOT].Xform, Ange.z);
	Qpo->Transform_RotateZ(&Q_Forge->Forge[m_AVSLOT].Xform, Ange.y);

	Q_Forge->Forge[m_AVSLOT].STOREMatrix = Q_Forge->Forge[m_AVSLOT].Xform;

	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.x = 0;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.y = 0;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.z = 0;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Matrix.load_identity();

	// Set the actor's angle
	Qpo->Transform_RotateX(&Q_Forge->Forge[m_AVSLOT].AV.Xform, Ange.x);		//Update Avatar's starting facing direction
	Qpo->Transform_RotateY(&Q_Forge->Forge[m_AVSLOT].AV.Xform, Ange.z);
	Qpo->Transform_RotateZ(&Q_Forge->Forge[m_AVSLOT].AV.Xform, Ange.y);

	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.x = i_Position.x;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.y = i_Position.y;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.z = i_Position.z;

	Q_Forge->Forge[m_AVSLOT].Angles.y = i_Angles.y;
	Q_Forge->Forge[m_AVSLOT].trueAngles.y = i_Angles.y;
	Q_Forge->Forge[m_AVSLOT].STOREAngles.y = i_Angles.y;*/

#if 0
	QpoActor_SetScale(Q_Forge->Forge[m_AVSLOT].AV.Avatar, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

	Q_Forge->Forge[m_AVSLOT].idlespeed = 0.1;

	if(Q_Forge->Forge[m_AVSLOT].LEVEL > 1000) Q_Forge->Forge[m_AVSLOT].LEVELFactor = 1;
	else Q_Forge->Forge[m_AVSLOT].LEVELFactor = (((float)Q_Forge->Forge[m_AVSLOT].LEVEL + 1) / 1000);

	Q_Forge->Forge[m_AVSLOT].HB_MaxHealth = 500 * (((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
	Q_Forge->Forge[m_AVSLOT].HB_Health = Q_Forge->Forge[m_AVSLOT].HB_MaxHealth;

	Q_Forge->Forge[m_AVSLOT].HB_MaxEnergy = 500;
	Q_Forge->Forge[m_AVSLOT].HB_Energy = Q_Forge->Forge[m_AVSLOT].HB_MaxEnergy;

	Q_Forge->Forge[m_AVSLOT].HB_Armour = ((float)(Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	Q_Forge->Forge[m_AVSLOT].HB_MaxArmour = ((float)(Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	Q_Forge->Forge[m_AVSLOT].JINK3_PowerFactor = 1;

	//#### RESET SPELLS
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[0].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[1].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[2].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[3].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[4].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[5].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[6].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[7].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[8].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[9].LIVE = 0;

	//####### RELATIVE MOVEMENT SPEED
	Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.EnergyEff / 6000);

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.Visible = true;

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.IDflag = AVSLOT;

	Qpo->Avatar_SetLighting(&Q_Forge->Forge[m_AVSLOT].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);

	//Q_Forge->Forge[m_AVSLOT].Angles.y = Ange.y;
	//Q_Forge->Forge[m_AVSLOT].trueAngles.y = Ange.y;
	//Q_Forge->Forge[m_AVSLOT].STOREAngles.y = Ange.y;

	Q_Forge->Forge[m_AVSLOT].Extenbox.Min.x = Q_Forge->Forge[m_AVSLOT].Mins.x;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Min.y = Q_Forge->Forge[m_AVSLOT].Mins.y;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Min.z = Q_Forge->Forge[m_AVSLOT].Mins.z;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Max.x = Q_Forge->Forge[m_AVSLOT].Maxs.x;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Max.y = Q_Forge->Forge[m_AVSLOT].Maxs.y;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Max.z = Q_Forge->Forge[m_AVSLOT].Maxs.z;
		
		//### Load Player Weapon
	Q_Forge->Forge[m_AVSLOT].Weapon.Avatar = 1;

	Q_Forge->Forge[m_AVSLOT].Weapon.Scale.x = 1;
	Q_Forge->Forge[m_AVSLOT].Weapon.Scale.y = 1;
	Q_Forge->Forge[m_AVSLOT].Weapon.Scale.z = 1;

	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.x = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.y = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.z = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.x = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.y = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.z = 20.f;

	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.x = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.y = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.z = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.x = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.y = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.z = 20.f;

	Q_Forge->Forge[m_AVSLOT].Weapon.Visible = true;

	Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[m_AVSLOT].Weapon.Xform.Translation);

	Qpo->Mesh_SetAlpha(&Q_Forge->Forge[m_AVSLOT].Weapon, 0);

	Q_Forge->Forge[m_AVSLOT].WeaponDISPLAY = 0;

	if(Q_Forge->Forge[m_AVSLOT].CharDATA.Class == 2)
		{
		Q_Forge->Forge[m_AVSLOT].Shield.Mins.x = -500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Mins.y = -500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Mins.z = -500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Maxs.x = 500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Maxs.y = 500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Maxs.z = 500.f;

		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[m_AVSLOT].Shield.Avatar, 40);

		fogbox.Min.x = Q_Forge->Forge[m_AVSLOT].Shield.Mins.x;
		fogbox.Min.y = Q_Forge->Forge[m_AVSLOT].Shield.Mins.y;
		fogbox.Min.z = Q_Forge->Forge[m_AVSLOT].Shield.Mins.z;
		fogbox.Max.x = Q_Forge->Forge[m_AVSLOT].Shield.Maxs.x;
		fogbox.Max.y = Q_Forge->Forge[m_AVSLOT].Shield.Maxs.y;
		fogbox.Max.z = Q_Forge->Forge[m_AVSLOT].Shield.Maxs.z;

		Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[m_AVSLOT].Shield.Xform.Translation);

		Q_Forge->Forge[m_AVSLOT].Shield.Avatar.IDflag = 251;
		}

	//### Load Fighter Shadows

	Q_Forge->Forge[m_AVSLOT].ShadowsOn = false;
	Q_Forge->Forge[m_AVSLOT].ShadowALPHA = 240;

	aero = 0;
	while(aero <= 2)
		{
		aero++;

		if(Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF > 11 || Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF < 0) Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF = 0;

		//Q_Forge->Forge[m_AVSLOT].Shadows[aero].Avatar.Mesh = new unAvatar();
		//m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF]->clone_struct(Q_Forge->Forge[m_AVSLOT].Shadows[aero].Avatar.Mesh);

		/*Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform.Translation.x = 0;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform.Translation.y = 0;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform.Translation.z = 0;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform.Matrix.load_identity();

		//##### Starting position
		Ange.y = i_Angles.y + (PI);
		if(Ange.y > (2*PI)) Ange.y = Ange.y - (PI*2);
		if(Ange.y < 0) Ange.y = (PI*2) - Ange.y;
		Ange.x = -(PI/2);
		Ange.z = 0;

		// Set the actor's angle
		Qpo->Transform_RotateX(&Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform, Ange.x);
		Qpo->Transform_RotateY(&Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform, Ange.y);
		Qpo->Transform_RotateZ(&Q_Forge->Forge[m_AVSLOT].Shadows[aero].Xform, Ange.z);*/

		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Mins.x = -20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Mins.y = -20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Mins.z = -20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Maxs.x = 20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Maxs.y = 20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Maxs.z = 20.f;

#if 0
		QpoActor_SetScale(Q_Forge->Forge[m_AVSLOT].Shadows[aero].Avatar, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Avatar.Visible = true;

		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[m_AVSLOT].Shadows[aero].Avatar, 255/(aero+1));

		Q_Forge->Forge[m_AVSLOT].Shadows[aero].Avatar.IDflag = helly;
		}

	//#### Set Up Trail Flags
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[0][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[1][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[2][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[3][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[4][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[5][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[6][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[7][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[8][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[9][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[0][1] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[1][1] = 1;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[2][1] = 2;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[3][1] = 3;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[4][1] = 4;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[5][1] = 5;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[6][1] = 6;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[7][1] = 7;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[8][1] = 8;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[9][1] = 9;

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItemsAI(helly);

#if 0
	//#### RESET SCALE AND LIGHTING
	QpoActor_SetScale(Q_Forge->Forge[m_AVSLOT].AV.Avatar, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

	SCRAM = 0;
	while(SCRAM < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 499) _->NomSpikes = 0;

		SCRAM++;
		}

	//#### Set Turning ####
	//m_Turning = i_Angles.y - Q_Forge->Forge[m_AVSLOT].Angles.y;
 
	//Qpo->Transform_New_YRotation(&AIfriendly, m_Turning);
	//Qpo->Transform_Multiply(&Q_Forge->Forge[m_AVSLOT].AV.Xform, &AIfriendly, &Q_Forge->Forge[m_AVSLOT].AV.Xform);

	if(i_SysIndex >= _->NomAI) _->NomAI = i_SysIndex + 1;

	return true;
}


//###### START PLAYERS #######

void PacketPumpInterface::acStartAvatarAI(int AIcounter, int Team)
{
#if 0
	//########## Setup Multiplayer Avatars ##########

	//###### TEST AVATAR SELECT

	Q_Forge->Forge[AIcounter].LIVE = 1;
	Q_Forge->Forge[AIcounter].AV.upspeed = -15;
	Q_Forge->Forge[AIcounter].AV.ModelCounter = 0;
	Q_Forge->Forge[AIcounter].AV.Mins.X = -25.f;
	Q_Forge->Forge[AIcounter].AV.Mins.Y = -45.f;
	Q_Forge->Forge[AIcounter].AV.Mins.Z = -25.f;
	Q_Forge->Forge[AIcounter].AV.Maxs.X = 25.f;
	Q_Forge->Forge[AIcounter].AV.Maxs.Y = 45.f;
	Q_Forge->Forge[AIcounter].AV.Maxs.Z = 25.f;

	Q_Forge->Forge[AIcounter].PlayerSpeed = PLAYER_SPEED;

	//Fill Weapon Ammo
	Q_Forge->Forge[AIcounter].WeaponAmmo = 32;

	Q_Forge->Forge[AIcounter].HB_Illumination = 255;
	Q_Forge->Forge[AIcounter].HB_Dead = 0;

	Q_Forge->Forge[AIcounter].Q_Brain.Aggression = 70;

	Q_Forge->Forge[AIcounter].Role = 0;
	Q_Forge->Forge[AIcounter].Rank = 1;
	Q_Forge->Forge[AIcounter].LEVEL = Q_Forge->Forge[AIcounter].CharDATA.Level;

	//###### AVATAR SELECTION

	egen3d_LoadActor(Q_Forge->Forge[AIcounter].AV.ActorXform, Q_Forge->Forge[AIcounter].CharDATA.ActorREF);
	//egen3d_LoadActor(Q_Forge->Forge[AIcounter].AV.ActorXform, "Actors\\LisaVARI.act");
	Q_Forge->Forge[AIcounter].AV.ActorDef = egen3d_FullAccess_ActorDef();
	Q_Forge->Forge[AIcounter].AV.Actor = egen3d_FullAccess_Actor();
	Q_Forge->Forge[AIcounter].AV.ActorXform = egen3d_FullAccess_ActorXform();

	geActor_SetScale(Q_Forge->Forge[AIcounter].AV.Actor, Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].idlespeed = 0.1;

	if(Q_Forge->Forge[AIcounter].LEVEL > 1000) Q_Forge->Forge[AIcounter].LEVELFactor = 1;
	else Q_Forge->Forge[AIcounter].LEVELFactor = (((float)Q_Forge->Forge[AIcounter].LEVEL + 1) / 1000);


	Q_Forge->Forge[AIcounter].HB_MaxHealth = 4650 * (((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
	Q_Forge->Forge[AIcounter].HB_Health = Q_Forge->Forge[AIcounter].HB_MaxHealth;

	Q_Forge->Forge[AIcounter].HB_MaxEnergy = 500;
	Q_Forge->Forge[AIcounter].HB_Energy = Q_Forge->Forge[AIcounter].HB_MaxEnergy;

	Q_Forge->Forge[AIcounter].HB_Armour = ((float)(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	Q_Forge->Forge[AIcounter].HB_MaxArmour = ((float)(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	Q_Forge->Forge[AIcounter].JINK3_PowerFactor = 1;

	Q_Forge->Forge[AIcounter].GravityAlter = 1;

	//ACTOR SETUP AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	
	//####### RELATIVE ATTACK SPEED
	Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff / 6000);


	geWorld_AddActor(World, Q_Forge->Forge[AIcounter].AV.Actor, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE, 0x00000001);
	Q_Forge->Forge[AIcounter].AV.Actor->Visible = GE_TRUE;

	//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);

	Q_Forge->Forge[AIcounter].AV.Motion[0] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Idle" );
	Q_Forge->Forge[AIcounter].AV.Motion[1] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Walk" );
	Q_Forge->Forge[AIcounter].AV.Motion[2] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Run" );
	Q_Forge->Forge[AIcounter].AV.Motion[3] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Sidestep" );
	Q_Forge->Forge[AIcounter].AV.Motion[4] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Jump" );
	Q_Forge->Forge[AIcounter].AV.Motion[5] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LLPunch" );
	Q_Forge->Forge[AIcounter].AV.Motion[6] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RLPunch" );
	Q_Forge->Forge[AIcounter].AV.Motion[7] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RHPunch2" );	//RHPunch
	Q_Forge->Forge[AIcounter].AV.Motion[8] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RMKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[9] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LMPunch" );	//LSPunch needs a home
	Q_Forge->Forge[AIcounter].AV.Motion[10] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RMPunch" );
	Q_Forge->Forge[AIcounter].AV.Motion[12] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "WalkL" );
	Q_Forge->Forge[AIcounter].AV.Motion[13] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "WalkR" );
	Q_Forge->Forge[AIcounter].AV.Motion[14] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunL" );
	Q_Forge->Forge[AIcounter].AV.Motion[15] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunR" );
	Q_Forge->Forge[AIcounter].AV.Motion[16] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SidestepL" );
	Q_Forge->Forge[AIcounter].AV.Motion[17] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SidestepR" );
	Q_Forge->Forge[AIcounter].AV.Motion[18] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Renzou" );		//TODO: Combine these two
	Q_Forge->Forge[AIcounter].AV.Motion[19] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RenzouE" );		//TODO: Into one
	Q_Forge->Forge[AIcounter].AV.Motion[20] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RSPunch" );
	Q_Forge->Forge[AIcounter].AV.Motion[21] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Uppercut" );	//Uppercut
	Q_Forge->Forge[AIcounter].AV.Motion[22] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HBlock" );
	Q_Forge->Forge[AIcounter].AV.Motion[23] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Idle2" );
	Q_Forge->Forge[AIcounter].AV.Motion[24] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RenzouR" );
	Q_Forge->Forge[AIcounter].AV.Motion[25] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Weapon1" );
	Q_Forge->Forge[AIcounter].AV.Motion[26] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunWep1L" );
	Q_Forge->Forge[AIcounter].AV.Motion[27] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunWep1R" );
	Q_Forge->Forge[AIcounter].AV.Motion[28] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AimWep1" );
	Q_Forge->Forge[AIcounter].AV.Motion[29] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AXKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[30] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SPKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[31] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpL" );
	Q_Forge->Forge[AIcounter].AV.Motion[32] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpR" );
	Q_Forge->Forge[AIcounter].AV.Motion[33] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Cartwheel" );
	Q_Forge->Forge[AIcounter].AV.Motion[34] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Weapon1UPP" );
	Q_Forge->Forge[AIcounter].AV.Motion[35] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AimWep1UPP" );
	Q_Forge->Forge[AIcounter].AV.Motion[36] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "CartWep1" );
	Q_Forge->Forge[AIcounter].AV.Motion[37] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Idle3" );
	Q_Forge->Forge[AIcounter].AV.Motion[38] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RenzouL" );
	Q_Forge->Forge[AIcounter].AV.Motion[39] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HoldDash" );
	Q_Forge->Forge[AIcounter].AV.Motion[40] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Knee" );
	Q_Forge->Forge[AIcounter].AV.Motion[41] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[42] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Wave" );
	Q_Forge->Forge[AIcounter].AV.Motion[43] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HitStom" );
	Q_Forge->Forge[AIcounter].AV.Motion[44] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HitUpper" );
	Q_Forge->Forge[AIcounter].AV.Motion[45] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpSpiral" );
	Q_Forge->Forge[AIcounter].AV.Motion[46] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "DodgeL" );
	Q_Forge->Forge[AIcounter].AV.Motion[47] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "FKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[48] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunBack" );
	Q_Forge->Forge[AIcounter].AV.Motion[53] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "FallHead" );
	Q_Forge->Forge[AIcounter].AV.Motion[54] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RHKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[55] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "FlameUpperCut" );
	Q_Forge->Forge[AIcounter].AV.Motion[56] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HBlockHit" );
	Q_Forge->Forge[AIcounter].AV.Motion[57] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BackFlip" );
	Q_Forge->Forge[AIcounter].AV.Motion[58] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "WeaponReload" );
	Q_Forge->Forge[AIcounter].AV.Motion[59] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SpinKickFull" );
	Q_Forge->Forge[AIcounter].AV.Motion[60] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Crouch" );
	Q_Forge->Forge[AIcounter].AV.Motion[61] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "CrouchL" );
	Q_Forge->Forge[AIcounter].AV.Motion[62] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "CrouchR" );
	Q_Forge->Forge[AIcounter].AV.Motion[67] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "VHKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[68] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Entro" );
	Q_Forge->Forge[AIcounter].AV.Motion[69] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "TwinDragon1" );
	Q_Forge->Forge[AIcounter].AV.Motion[70] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "TwinDragon2" );
	Q_Forge->Forge[AIcounter].AV.Motion[71] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Golrekka" );
	Q_Forge->Forge[AIcounter].AV.Motion[72] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SkyPush" );
	Q_Forge->Forge[AIcounter].AV.Motion[73] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Lowtro" );
	Q_Forge->Forge[AIcounter].AV.Motion[74] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Lowkick" );
	Q_Forge->Forge[AIcounter].AV.Motion[75] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Legsweep" );
	Q_Forge->Forge[AIcounter].AV.Motion[76] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Crunch" );
	Q_Forge->Forge[AIcounter].AV.Motion[77] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Hitwall" );
	Q_Forge->Forge[AIcounter].AV.Motion[78] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AttFlip" );
	Q_Forge->Forge[AIcounter].AV.Motion[79] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunAttP" );
	Q_Forge->Forge[AIcounter].AV.Motion[80] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LowPunchL" );
	Q_Forge->Forge[AIcounter].AV.Motion[81] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LowPunchR" );
	Q_Forge->Forge[AIcounter].AV.Motion[82] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LBlock" );
	Q_Forge->Forge[AIcounter].AV.Motion[83] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LBlockHit" );
	Q_Forge->Forge[AIcounter].AV.Motion[84] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Hadouken" );
	Q_Forge->Forge[AIcounter].AV.Motion[85] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HadoukenAir" );
	Q_Forge->Forge[AIcounter].AV.Motion[86] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AirDash" );
	Q_Forge->Forge[AIcounter].AV.Motion[87] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HoverKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[88] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RollF" );
	Q_Forge->Forge[AIcounter].AV.Motion[89] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Taunt1" );
	Q_Forge->Forge[AIcounter].AV.Motion[90] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Sakurat" );
	Q_Forge->Forge[AIcounter].AV.Motion[91] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BrollyT" );
	Q_Forge->Forge[AIcounter].AV.Motion[92] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "PCombo1" );
	Q_Forge->Forge[AIcounter].AV.Motion[93] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SpiralDown" );
	Q_Forge->Forge[AIcounter].AV.Motion[94] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpSpiralOver" );
	Q_Forge->Forge[AIcounter].AV.Motion[95] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpSmall" );
	Q_Forge->Forge[AIcounter].AV.Motion[96] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "TwistKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[97] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BackFLipAtt" );
	Q_Forge->Forge[AIcounter].AV.Motion[98] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Deflect" );
	Q_Forge->Forge[AIcounter].AV.Motion[99] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpSmallL" );
	Q_Forge->Forge[AIcounter].AV.Motion[100] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JumpSmallR" );
	Q_Forge->Forge[AIcounter].AV.Motion[101] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "PCombo2" );
	Q_Forge->Forge[AIcounter].AV.Motion[102] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RushElbow" );
	Q_Forge->Forge[AIcounter].AV.Motion[103] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HoldBarge" );
	Q_Forge->Forge[AIcounter].AV.Motion[104] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "DoubleStrike" );
	Q_Forge->Forge[AIcounter].AV.Motion[105] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LowLunge" );
	Q_Forge->Forge[AIcounter].AV.Motion[106] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SideChop" );
	Q_Forge->Forge[AIcounter].AV.Motion[107] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SpinChop" );
	Q_Forge->Forge[AIcounter].AV.Motion[108] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RollLowL" );
	Q_Forge->Forge[AIcounter].AV.Motion[109] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RollLowR" );
	//VEHICLE MOTIONS UNUSED
	//Q_Forge->Forge[AIcounter].AV.Motion[110] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BikeMount" );
	//Q_Forge->Forge[AIcounter].AV.Motion[111] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BikeRush" );
	//Q_Forge->Forge[AIcounter].AV.Motion[112] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BikeWheelie" );
	//Q_Forge->Forge[AIcounter].AV.Motion[113] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "BikeIdle" );
	Q_Forge->Forge[AIcounter].AV.Motion[114] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RenzouP" );
	Q_Forge->Forge[AIcounter].AV.Motion[115] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RenzouPR" );
	Q_Forge->Forge[AIcounter].AV.Motion[116] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AttFlipE" );
	Q_Forge->Forge[AIcounter].AV.Motion[117] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HandSlap" );
	Q_Forge->Forge[AIcounter].AV.Motion[118] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JSRUSH" );
	Q_Forge->Forge[AIcounter].AV.Motion[119] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JSRUSHPUNCH" );
	Q_Forge->Forge[AIcounter].AV.Motion[120] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JSRUSHBG" );
	Q_Forge->Forge[AIcounter].AV.Motion[121] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "JSRUSHKICK" );
	Q_Forge->Forge[AIcounter].AV.Motion[122] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "StaticKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[123] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunAttK" );
	Q_Forge->Forge[AIcounter].AV.Motion[124] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RDoubleKick" );
	Q_Forge->Forge[AIcounter].AV.Motion[125] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "WeaponReloadUPP" );
	Q_Forge->Forge[AIcounter].AV.Motion[126] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RunAttK" );
	Q_Forge->Forge[AIcounter].AV.Motion[127] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "PowerBomb" );
	Q_Forge->Forge[AIcounter].AV.Motion[128] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LeapDownStrike" );
	Q_Forge->Forge[AIcounter].AV.Motion[129] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "RSPINSTRIKE" );
	Q_Forge->Forge[AIcounter].AV.Motion[130] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "SpinoutLeft" );
	Q_Forge->Forge[AIcounter].AV.Motion[131] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "OverheadPinwheel" );
	Q_Forge->Forge[AIcounter].AV.Motion[132] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LeapDownFist" );
	Q_Forge->Forge[AIcounter].AV.Motion[140] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "LookRight" );

	if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
		{
		Q_Forge->Forge[AIcounter].AV.Motion[63] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Glance" );
		Q_Forge->Forge[AIcounter].AV.Motion[65] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "HealUPP" );
		Q_Forge->Forge[AIcounter].AV.Motion[66] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Heal" );
		}

	Q_Forge->Forge[AIcounter].AV.Motion[133] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Weapon2" );
	Q_Forge->Forge[AIcounter].AV.Motion[134] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "Weapon2UPP" );
	Q_Forge->Forge[AIcounter].AV.Motion[135] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AimWep2" );
	Q_Forge->Forge[AIcounter].AV.Motion[136] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "AimWep2UPP" );
	Q_Forge->Forge[AIcounter].AV.Motion[137] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "WeaponReload2" );
	Q_Forge->Forge[AIcounter].AV.Motion[138] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].AV.ActorDef, "WeaponReload2UPP" );

	//##### ATTENTION REQUIRED
	//geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&goup,230,200,200,230,175,155,GE_FALSE,8,NULL,GE_TRUE);
	geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&goup,200,200,200,190,145,100,GE_FALSE,8,NULL,GE_TRUE);

	//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);

	//Lighting
	/*if(AvatarEntity[AIcounter].Team == 0)	//Friendly AI
		{
		if(AvatarEntity[AIcounter].Type == 0)	geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&goup,200,200,200,190,145,100,GE_FALSE,8,NULL,GE_TRUE);
		if(AvatarEntity[AIcounter].Type == 1)	geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&goup,230,200,200,230,175,155,GE_FALSE,8,NULL,GE_TRUE);
		if(AvatarEntity[AIcounter].Type == 2)	geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&goup,230,200,200,230,175,155,GE_FALSE,8,NULL,GE_TRUE);
		}

	if(AvatarEntity[AIcounter].Team == 1)	//Enemy AI
		{
		if(AvatarEntity[AIcounter].Type == 0) 
			{
			//geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&poop,255,180,180,220,220,220,GE_FALSE,8,NULL,GE_TRUE);
			geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,&goup,200,200,200,190,145,100,GE_FALSE,8,NULL,GE_TRUE);
			}
		}*/

	//Shadows
	//geActor_SetShadow(Q_Forge->Forge[AIcounter].AV.Actor,GE_TRUE,30.0,shadow,NULL);

	//Starting Rotation
	Ange.Y = Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Ang.Y + (PI);
	if(Ange.Y>(2*PI)) Ange.Y = Ange.Y - (PI*2);

	Ange.X=-(PI/2);
	Ange.Z=0;

	// Set the actor's angle
	geXForm3d_RotateX(&Q_Forge->Forge[AIcounter].AV.ActorXform, Ange.X);		//Update Avatar's starting facing direction
	geXForm3d_RotateY(&Q_Forge->Forge[AIcounter].AV.ActorXform, Ange.Y);
	geXForm3d_RotateZ(&Q_Forge->Forge[AIcounter].AV.ActorXform, Ange.Z);

	Q_Forge->Forge[AIcounter].Angles.Y = Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Ang.y;
	Q_Forge->Forge[AIcounter].TRUEAngles.Y = Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Ang.y;
	Q_Forge->Forge[AIcounter].STOREAngles.Y = Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Ang.y;


	//ATTENTION START POINT CONTROL	***********************************************

	geXForm3d_GetIn(&Q_Forge->Forge[AIcounter].AV.ActorXform,&Q_Forge->Forge[AIcounter].In);

	Q_StartPoints[Q_Forge->Forge[AIcounter].Team].TempVec.X = 0;
	Q_StartPoints[Q_Forge->Forge[AIcounter].Team].TempVec.Y = 1;
	Q_StartPoints[Q_Forge->Forge[AIcounter].Team].TempVec.Z = 0;

	geVec3d_CrossProduct(&Q_Forge->Forge[AIcounter].In, &Q_StartPoints[Q_Forge->Forge[AIcounter].Team].TempVec, &Q_StartPoints[Q_Forge->Forge[AIcounter].Team].VecRight);
	geVec3d_Normalize(&Q_StartPoints[Q_Forge->Forge[AIcounter].Team].VecRight);

	Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Push += 40;
	if(Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Push > 300) Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Push = 0;

	geVec3d_MA(&Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Pos, Q_StartPoints[Q_Forge->Forge[AIcounter].Team].Push, &Q_StartPoints[Q_Forge->Forge[AIcounter].Team].VecRight, &Q_Forge->Forge[AIcounter].AV.ActorXform.Translation);

	//###### Set the actor to its position
	geVec3d_Copy(&Q_Forge->Forge[AIcounter].AV.ActorXform.Translation, &Q_Forge->Forge[AIcounter].ORIGSTARTPOINT);

	//*****************************************************************************


	geActor_ClearPose(Q_Forge->Forge[AIcounter].AV.Actor, &Q_Forge->Forge[AIcounter].AV.ActorXform);


	Q_Forge->Forge[AIcounter].Extenbox.Min.X = Q_Forge->Forge[AIcounter].AV.Mins.x;
	Q_Forge->Forge[AIcounter].Extenbox.Min.Y = Q_Forge->Forge[AIcounter].AV.Mins.y;
	Q_Forge->Forge[AIcounter].Extenbox.Min.Z = Q_Forge->Forge[AIcounter].AV.Mins.z;
	Q_Forge->Forge[AIcounter].Extenbox.Max.X = Q_Forge->Forge[AIcounter].AV.Maxs.x;
	Q_Forge->Forge[AIcounter].Extenbox.Max.Y = Q_Forge->Forge[AIcounter].AV.Maxs.y;
	Q_Forge->Forge[AIcounter].Extenbox.Max.Z = Q_Forge->Forge[AIcounter].AV.Maxs.z;
	
	geActor_SetExtBox(Q_Forge->Forge[AIcounter].AV.Actor, &Q_Forge->Forge[AIcounter].Extenbox, "BIP01");

	// Get body of actor
	//LisaBody = geActor_GetBody(Q_Forge->Forge[AIcounter].AV.ActorDef);

	geActor_SetEnvironOptions(Q_Forge->Forge[AIcounter].AV.Actor, &ActorEnviro );

	geActor_SetStaticLightingOptions( Q_Forge->Forge[AIcounter].AV.Actor, GE_TRUE, GE_TRUE, 10 );

	Q_Forge->Forge[AIcounter].STOREMatrix = Q_Forge->Forge[AIcounter].AV.ActorXform;
	geVec3d_Copy(&Origin, &Q_Forge->Forge[AIcounter].STOREMatrix.Translation);

	Q_Forge->Forge[AIcounter].AV.Actor->IDflag = AIcounter;

	Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;

	//### Load Avatar Weapon

	if(1)
		{
		egen3d_LoadActor(Q_Forge->Forge[AIcounter].Weapon.ActorXform, Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemActorREF);
		//egen3d_LoadActor(Q_Forge->Forge[AIcounter].Weapon.ActorXform, "Actors\\w_sg5520.act");

		Q_Forge->Forge[AIcounter].Weapon.Mins.X = -20.f;
		Q_Forge->Forge[AIcounter].Weapon.Mins.Y = -20.f;
		Q_Forge->Forge[AIcounter].Weapon.Mins.Z = -20.f;
		Q_Forge->Forge[AIcounter].Weapon.Maxs.X = 20.f;
		Q_Forge->Forge[AIcounter].Weapon.Maxs.Y = 20.f;
		Q_Forge->Forge[AIcounter].Weapon.Maxs.Z = 20.f;

		Q_Forge->Forge[AIcounter].Weapon.ActorDef = egen3d_FullAccess_ActorDef();
		Q_Forge->Forge[AIcounter].Weapon.Actor = egen3d_FullAccess_Actor();
		Q_Forge->Forge[AIcounter].Weapon.ActorXform = egen3d_FullAccess_ActorXform();

		geActor_SetScale(Q_Forge->Forge[AIcounter].Weapon.Actor, 1.2 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 1.2 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 1.2 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		geWorld_AddActor(World, Q_Forge->Forge[AIcounter].Weapon.Actor, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE, 0xffffffff);
		Q_Forge->Forge[AIcounter].Weapon.Actor->Visible = GE_TRUE;

		//Poser.X=400;
		//Poser.Y=-150;		//Create Weapon Rack Somewhere
		//Poser.Z=-0;

		Ange.X=-(PI/2);
		Ange.Y=PI;
		Ange.Z=0;

		geXForm3d_RotateX(&Q_Forge->Forge[AIcounter].Weapon.ActorXform, Ange.X);
		geXForm3d_RotateY(&Q_Forge->Forge[AIcounter].Weapon.ActorXform, Ange.Y);
		geXForm3d_RotateZ(&Q_Forge->Forge[AIcounter].Weapon.ActorXform, Ange.Z);
		geVec3d_Copy(&Origon, &Q_Forge->Forge[AIcounter].Weapon.ActorXform.Translation);

		geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].Weapon.Actor,GE_TRUE,&goup,255,255,255,170,170,170,GE_FALSE,0,NULL,GE_TRUE);
		geActor_ClearPose(Q_Forge->Forge[AIcounter].Weapon.Actor, &Q_Forge->Forge[AIcounter].Weapon.ActorXform);

		geActor_SetAlpha(Q_Forge->Forge[AIcounter].Weapon.Actor, 0);
		}

	//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);

	if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
		{
		Q_Forge->Forge[AIcounter].Shield.Mins.X = -500.f;
		Q_Forge->Forge[AIcounter].Shield.Mins.Y = -500.f;
		Q_Forge->Forge[AIcounter].Shield.Mins.Z = -500.f;
		Q_Forge->Forge[AIcounter].Shield.Maxs.X = 500.f;
		Q_Forge->Forge[AIcounter].Shield.Maxs.Y = 500.f;
		Q_Forge->Forge[AIcounter].Shield.Maxs.Z = 500.f;

		egen3d_LoadActor(Q_Forge->Forge[AIcounter].Shield.ActorXform, "Actors\\ShockWave.act");
		Q_Forge->Forge[AIcounter].Shield.ActorDef = egen3d_FullAccess_ActorDef();
		Q_Forge->Forge[AIcounter].Shield.Actor = egen3d_FullAccess_Actor();
		Q_Forge->Forge[AIcounter].Shield.ActorXform = egen3d_FullAccess_ActorXform();

		geActor_SetScale(Q_Forge->Forge[AIcounter].Shield.Actor, 0.65f,0.65f,0.65f);
		geWorld_AddActor(World, Q_Forge->Forge[AIcounter].Shield.Actor, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE, 0x00000001);
		geActor_SetAlpha(Q_Forge->Forge[AIcounter].Shield.Actor, 40);

		fogbox.Min.X = Q_Forge->Forge[AIcounter].Shield.Mins.x;
		fogbox.Min.Y = Q_Forge->Forge[AIcounter].Shield.Mins.y;
		fogbox.Min.Z = Q_Forge->Forge[AIcounter].Shield.Mins.z;
		fogbox.Max.X = Q_Forge->Forge[AIcounter].Shield.Maxs.x;
		fogbox.Max.Y = Q_Forge->Forge[AIcounter].Shield.Maxs.y;
		fogbox.Max.Z = Q_Forge->Forge[AIcounter].Shield.Maxs.z;

		geActor_ClearPose(Q_Forge->Forge[AIcounter].Shield.Actor, &Q_Forge->Forge[AIcounter].Shield.ActorXform);
		geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].Shield.Actor, GE_FALSE, &goup, 0, 0, 0, 255, 255, 255, GE_FALSE, 0, NULL, GE_FALSE);
		geVec3d_Copy(&Origon, &Q_Forge->Forge[AIcounter].Shield.ActorXform.Translation);
		
		geActor_SetExtBox(Q_Forge->Forge[AIcounter].Shield.Actor, &fogbox, NULL);

		Q_Forge->Forge[AIcounter].Shield.Actor->IDflag = 251;
		}

	//### Load Fighter Shadows

	Q_Forge->Forge[AIcounter].ShadowsOn = GE_FALSE;

	Q_Forge->Forge[AIcounter].ShadowALPHA = 240;

	//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);


	warp = 0;
	while(warp <= 2)
		{
		warp++;

		egen3d_LoadActor(Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform, Q_Forge->Forge[AIcounter].CharDATA.ShadowREF);
		//egen3d_LoadActor(Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform, "Actors\\LisaVARS.act");

		Q_Forge->Forge[AIcounter].Shadows[warp].Mins.X = -20.f;
		Q_Forge->Forge[AIcounter].Shadows[warp].Mins.Y = -20.f;
		Q_Forge->Forge[AIcounter].Shadows[warp].Mins.Z = -20.f;
		Q_Forge->Forge[AIcounter].Shadows[warp].Maxs.X = 20.f;
		Q_Forge->Forge[AIcounter].Shadows[warp].Maxs.Y = 20.f;
		Q_Forge->Forge[AIcounter].Shadows[warp].Maxs.Z = 20.f;

		Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef = egen3d_FullAccess_ActorDef();
		Q_Forge->Forge[AIcounter].Shadows[warp].Actor = egen3d_FullAccess_Actor();
		Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform = egen3d_FullAccess_ActorXform();

		geActor_SetScale(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

		geWorld_AddActor(World, Q_Forge->Forge[AIcounter].Shadows[warp].Actor, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE, 0xffffffff);
		Q_Forge->Forge[AIcounter].Shadows[warp].Actor->Visible = GE_TRUE;

		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[0] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Idle" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[1] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Walk" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[2] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Run" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[3] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Sidestep" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[4] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Jump" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[5] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LLPunch" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[6] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RLPunch" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[7] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RHPunch2" );	//RHPunch
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[8] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RMKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[9] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LMPunch" );	//LSPunch needs a home
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[10] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RMPunch" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[11] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LLPunchA" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[12] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "WalkL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[13] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "WalkR" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[14] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RunL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[15] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RunR" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[16] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "SidestepL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[17] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "SidestepR" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[18] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Renzou" );		//TODO: Combine these two
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[19] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RenzouE" );		//TODO: Into one
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[20] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RSPunch" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[21] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Uppercut" );	//Uppercut
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[22] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HBlock" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[23] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Idle2" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[24] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RenzouR" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[25] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Weapon1" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[26] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RunWep1L" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[27] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RunWep1R" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[28] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AimWep1" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[29] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AXKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[30] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "SPKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[31] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JumpL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[32] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JumpR" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[33] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Cartwheel" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[34] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Weapon1UPP" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[35] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AimWep1UPP" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[36] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "CartWep1" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[37] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Idle3" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[38] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RenzouL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[39] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HoldDash" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[40] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Knee" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[41] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JumpKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[42] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Wave" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[43] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HitStom" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[44] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HitUpper" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[45] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JumpSpiral" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[46] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "DodgeL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[47] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "FKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[48] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AirJink" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[49] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RunBack" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[50] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AirRushFront" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[51] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HitStorm" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[52] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RapidKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[53] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "FallHead" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[54] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RHKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[55] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "FlameUpperCut" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[56] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HBlockHit" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[57] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "BackFlip" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[58] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "WeaponReload" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[59] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "SpinKickFull" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[60] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Crouch" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[61] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "CrouchL" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[62] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "CrouchR" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[63] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LLPunchUPP" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[64] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RLPunchUPP" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[65] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LMPunchUPP" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[66] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LMKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[67] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "VHKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[71] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Golrekka" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[72] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "SkyPush" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[76] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Crunch" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[77] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Hitwall" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[78] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AttFlip" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[84] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Hadouken" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[85] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HadoukenAir" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[86] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "AirDash" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[87] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "HoverKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[88] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RollF" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[90] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "Sakurat" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[91] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "BrollyT" );
		//Q_Forge->Forge[AIcounter].Shadows[warp].Motion[92] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "PCombo1" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[96] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "TwistKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[101] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "PCombo2" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[102] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "RushElbow" );

		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[118] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JSRUSH" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[119] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JSRUSHPUNCH" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[120] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JSRUSHBG" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[121] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "JSRUSHKICK" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[122] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "StaticKick" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[127] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "PowerBomb" );

		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[128] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LeapDownStrike" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[129] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "CartwheelAtt" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[130] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "SpinoutLeft" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[131] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "OverheadPinwheel" );
		Q_Forge->Forge[AIcounter].Shadows[warp].Motion[132] = geActor_GetMotionByName(Q_Forge->Forge[AIcounter].Shadows[warp].ActorDef, "LeapDownFist" );

		Ange.X=-(PI/2);
		Ange.Y=PI;
		Ange.Z=0;

		geXForm3d_RotateX(&Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform, Ange.X);
		geXForm3d_RotateY(&Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform, Ange.Y);
		geXForm3d_RotateZ(&Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform, Ange.Z);
		geVec3d_Copy(&Origon, &Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform.Translation);

		//geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].Shadows[warp].Actor,GE_TRUE,&goup,255/((warp+1)/2),255/((warp+1)/2),255/((warp+1)/2),255/((warp+1)/2),255/((warp+1)/2),255/((warp+1)/2),GE_FALSE,0,NULL,GE_TRUE);
		geActor_SetLightingOptions(Q_Forge->Forge[AIcounter].Shadows[warp].Actor,GE_TRUE,&goup,255,255,255,255,255,255,GE_FALSE,0,NULL,GE_TRUE);
		geActor_SetEnvironOptions(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, &ActorEnviro );

		geActor_ClearPose(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, &Q_Forge->Forge[AIcounter].Shadows[warp].ActorXform);

		//geActor_SetAlpha(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, 150/(warp+1));
		geActor_SetAlpha(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, 255/(warp+1));

		Q_Forge->Forge[AIcounter].Shadows[warp].Actor->IDflag = AIcounter;

		if(Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.ANGELEDITFLAG == 1)
			{
			//##### ANGEL COLOUR EDIT
			K=0;
			while(K < 38)
				{
				geActor_GetMaterial(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, K, &ANGELeditBitmap, &ANGELeditBitmapRed, &ANGELeditBitmapGreen, &ANGELeditBitmapBlue);
				geActor_SetMaterial(Q_Forge->Forge[AIcounter].Shadows[warp].Actor, K, ANGELeditBitmap, Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.RED[K], Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.GREEN[K], Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.BLUE[K]);
				K++;
				}
			}
		}

	//#### Set Up Trail Flags
	Q_Forge->Forge[AIcounter].TrailFadeSpan[0][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[1][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[2][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[3][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[4][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[5][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[6][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[7][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[8][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[9][0] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[0][1] = 0;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[1][1] = 1;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[2][1] = 2;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[3][1] = 3;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[4][1] = 4;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[5][1] = 5;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[6][1] = 6;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[7][1] = 7;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[8][1] = 8;
	Q_Forge->Forge[AIcounter].TrailFadeSpan[9][1] = 9;

	//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

	NamePlateUpdate();

	//####### ACTIVATE ITEM ATTRIBUTES
	Q_ActivateItemsAI(AIcounter);

	//#### RESET SCALE AND LIGHTING
	geActor_SetScale(Q_Forge->Forge[AIcounter].AV.Actor, Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.ActorSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

	NamePlateUpdate();

	if(Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.ANGELEDITFLAG == 1)
		{
		//##### ANGEL COLOUR EDIT
		K=0;
		while(K < 38)
			{
			geActor_GetMaterial(Q_Forge->Forge[AIcounter].AV.Actor, K, &ANGELeditBitmap, &ANGELeditBitmapRed, &ANGELeditBitmapGreen, &ANGELeditBitmapBlue);
			geActor_SetMaterial(Q_Forge->Forge[AIcounter].AV.Actor, K, ANGELeditBitmap, Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.RED[K], Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.GREEN[K], Q_Forge->Forge[AIcounter].CharDATA.AngelCOLOURS.BLUE[K]);
			K++;
			}
		}

	//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

	SCRAM = 0;
	while(SCRAM < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_Forge->Forge[AIcounter].AV.ActorXform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.Y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.X = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.Y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.Z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 499) _->NomSpikes = 0;

		SCRAM++;
		}

	//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);

	//#### Small Energy Attacks
	warp=0;
	while(warp < 2)
		{
		SCRAM=0;
		while(SCRAM < 5)
			{
			egen3d_LoadActor(Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].ActorXform, "Actors\\Renzou.act");

			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Mins.X = -20.f;
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Mins.Y = -20.f;
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Mins.Z = -20.f;
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Maxs.X = 20.f;
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Maxs.Y = 20.f;
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Maxs.Z = 20.f;

			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].ActorDef = egen3d_FullAccess_ActorDef();
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Actor = egen3d_FullAccess_Actor();
			Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].ActorXform = egen3d_FullAccess_ActorXform();

			geActor_SetScale(Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Actor, 0.1f,0.1f,0.1f);
			geWorld_AddActor(World, Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Actor, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE , 0xffffffff);
			geVec3d_Copy(&Origin, &Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].ActorXform.Translation);

			geActor_ClearPose(Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].Actor, &Q_SEnergy[MaxNomSEnergy].ActorFlag[SCRAM].ActorXform);
			NamePlateUpdate();
			SCRAM++;
			}

		Q_SEnergy[MaxNomSEnergy].Const_TurnDull = 2500;
		Q_SEnergy[MaxNomSEnergy].Const_AngleInc = 0.2;

		MaxNomSEnergy++;
		warp++;

		//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);
		}

	//Hadouken
	warp=0;
	while(warp < 2)
		{
		egen3d_LoadActor(Q_LEnergy[MaxNomLEnergy].EnergyBall.ActorXform, "Actors\\SpiritBomb.act");

		Q_LEnergy[MaxNomLEnergy].EnergyBall.Mins.X = -20.f;
		Q_LEnergy[MaxNomLEnergy].EnergyBall.Mins.Y = -20.f;
		Q_LEnergy[MaxNomLEnergy].EnergyBall.Mins.Z = -20.f;
		Q_LEnergy[MaxNomLEnergy].EnergyBall.Maxs.X = 20.f;
		Q_LEnergy[MaxNomLEnergy].EnergyBall.Maxs.Y = 20.f;
		Q_LEnergy[MaxNomLEnergy].EnergyBall.Maxs.Z = 20.f;

		Q_LEnergy[MaxNomLEnergy].EnergyBall.ActorDef = egen3d_FullAccess_ActorDef();
		Q_LEnergy[MaxNomLEnergy].EnergyBall.Actor = egen3d_FullAccess_Actor();
		Q_LEnergy[MaxNomLEnergy].EnergyBall.ActorXform = egen3d_FullAccess_ActorXform();

		geActor_SetScale(Q_LEnergy[MaxNomLEnergy].EnergyBall.Actor, 0.01f,0.01f,0.01f);
		geWorld_AddActor(World, Q_LEnergy[MaxNomLEnergy].EnergyBall.Actor, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE, 0xffffffff);
		geActor_SetAlpha(Q_LEnergy[MaxNomLEnergy].EnergyBall.Actor, 150);

		Ange.X=-(PI/2);
		geXForm3d_RotateX(&Q_LEnergy[MaxNomLEnergy].EnergyBall.ActorXform, Ange.X);

		geActor_ClearPose(Q_LEnergy[MaxNomLEnergy].EnergyBall.Actor, &Q_LEnergy[MaxNomLEnergy].EnergyBall.ActorXform);
		geActor_SetLightingOptions(Q_LEnergy[MaxNomLEnergy].EnergyBall.Actor, GE_FALSE, &goup, 0, 0, 0, 255, 255, 255, GE_FALSE, 0, NULL, GE_FALSE);
		geVec3d_Copy(&Origon, &Q_LEnergy[MaxNomLEnergy].EnergyBall.ActorXform.Translation);

		MaxNomLEnergy++;
		warp++;

		//if(NetworkOption == 1) QNETWORKClientHALFFrame(QHost.Client,Time);
		}

	if(AIcounter >= NomAI) NomAI++;
#endif
}




