/*

    m_PacketPump - unServer packet reading thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "Master.h"
#include "UNSGlobalHeader.h"

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
		//Sleep(450);
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
				printf("QAGE Client Connect\n");

				unsigned int binAddress;
				unsigned short sysport;

#ifdef PTRSTREAMS
				i_BitTransfer->acRead(binAddress);
				i_BitTransfer->acRead(sysport);
#else
				i_BitTransfer.acRead(binAddress);
				i_BitTransfer.acRead(sysport);
#endif

				SystemAddress sysAddressST = m_packet->systemAddress;

				//sysAddressST.port = 15555;

				printf("m_packet->systemAddress(sysport) = %i\n", sysAddressST.port);

				g_map_SysAddressST[ m_packet->systemAddress.systemIndex ] = &sysAddressST;

				SystemAddress* sysAddress = new SystemAddress();
				sysAddress->binaryAddress = sysAddressST.binaryAddress;
				sysAddress->port = sysAddressST.port;

				//sysAddress->port = 15555;

				printf("i_BitTransfer.acRead(sysport) = %i\n", sysport);

				g_map_SysAddress[ m_packet->systemAddress.systemIndex ] = sysAddress;
				}break;

			case ID_CLIENT_IDENT:
				{
				printf("unServer: ID_CLIENT_IDENT\n");
 
#pragma message("FIXME Class Optimise Variable Reciever")
				char* name = new char;
				char* password = new char;
				unsigned short i_ClientID;

				i_BitTransfer.acRead(i_ClientID);

				printf("i_ClientID ::: %i\n", i_ClientID);

				//BitTransfer f_BitTransfer(ID_CLIENT_IDENT);

				//stringCompressor->EncodeString(name, UNS_LINE_MAX, &f_BitTransfer);
				//stringCompressor->EncodeString(password, UNS_LINE_MAX, &f_BitTransfer);

#ifdef PTRSTREAMS
				stringCompressor->DecodeString(name, UNS_LINE_MAX, i_BitTransfer);
				stringCompressor->DecodeString(password, UNS_LINE_MAX, i_BitTransfer);
#else
				stringCompressor->DecodeString(name, UNS_LINE_MAX, &i_BitTransfer);
				printf("unServer ::: user logon %s\n", name);
				stringCompressor->DecodeString(password, UNS_LINE_MAX, &i_BitTransfer);
#endif

				/////// Temporarily store client and password //////
				g_map_ClientName[m_packet->systemAddress.systemIndex] = name;
				g_map_ClientPassword[m_packet->systemAddress.systemIndex] = password;
				

#ifdef USE_MYSQL
				sMaster->acRecieveClient(name, password);
				sMaster->acModPacket(m_packet);
#endif

#if 1
				/////// Send a Character Data Start Resource Request ///////
				UNSRequest *i_ResourceRequest = new UNSRequest;
				i_ResourceRequest->m_RequestType = UNS_RES_CHAR_START;

				i_ResourceRequest->timeStamp = i_TimeStamp;
				i_ResourceRequest->typeId = i_PacketIdent;

				i_ResourceRequest->m_SysAddress = m_packet->systemAddress.systemIndex;
				i_ResourceRequest->m_Count = 0;

				SDL_mutexP(g_mutex_Requests);
				g_UNSResRequest.push_back(i_ResourceRequest);
				SDL_mutexV(g_mutex_Requests);
#endif
				}break;

			case ID_CLIENT_CHAR_START:
				{
				i_BitTransfer.acRead(m_CharListID);
				printf("unServer trace m_CharListID %i\n", m_CharListID);

				std::vector<int>* i_VectorCharacterID;

				SDL_mutexP(g_mutex_CharacterID);
				if(g_map_ClientCharacterID.find(m_packet->systemAddress.systemIndex) == g_map_ClientCharacterID.end())
					{
					i_VectorCharacterID = new std::vector<int>;

					for(int i_CharID = 0; i_CharID < m_CharListID; i_CharID++)
						{
						i_VectorCharacterID[0].push_back(-50);
						printf("unServer trace PUSH %i\n", i_CharID);
						}

					g_map_ClientCharacterID[m_packet->systemAddress.systemIndex] = i_VectorCharacterID;
					}
				else
					{
					i_VectorCharacterID = g_map_ClientCharacterID[m_packet->systemAddress.systemIndex];

					for(int i_CharID = 0; i_CharID < m_CharListID; i_CharID++)
						{
						i_VectorCharacterID[0].push_back(-50);
						printf("unServer trace PUSH %i\n", i_CharID);
						}
					}
				SDL_mutexV(g_mutex_CharacterID);

				/////// Send a Character Data Resource Request ///////
				UNSRequest *i_ResourceRequest = new UNSRequest;
				i_ResourceRequest->m_RequestType = UNS_RES_CHAR;

				i_ResourceRequest->timeStamp = i_TimeStamp;
				i_ResourceRequest->typeId = i_PacketIdent;

				i_ResourceRequest->m_SysAddress = m_packet->systemAddress.systemIndex;
				i_ResourceRequest->m_Count = 0;

				SDL_mutexP(g_mutex_Requests);
				g_UNSResRequest.push_back(i_ResourceRequest);
				SDL_mutexV(g_mutex_Requests);
				}break;

			case ID_CLIENT_START:
				{
				printf("unServer: ID_CLIENT_START\n");
				i_BitTransfer.acRead(m_CDATID);
				i_BitTransfer.acRead(m_BDATID);
				i_BitTransfer.acRead(m_Position.x);
				i_BitTransfer.acRead(m_Position.y);
				i_BitTransfer.acRead(m_Position.z);
				i_BitTransfer.acRead(m_Turn);
				i_BitTransfer.acRead(m_AVcount);

				// Temp turing, active event updates
				g_Domain.acAvatarStartClient(m_Position, m_Turn, m_packet->systemAddress.systemIndex, m_CDATID, m_BDATID);

				for(unsigned int i_AVID = 0; i_AVID < m_AVcount; i_AVID++)
					{
					i_BitTransfer.acRead(m_CDATID);
					i_BitTransfer.acRead(m_BDATID);
					i_BitTransfer.acRead(m_Position.x);
					i_BitTransfer.acRead(m_Position.y);
					i_BitTransfer.acRead(m_Position.z);
					i_BitTransfer.acRead(m_Turn);

					g_Domain.acAvatarStart(m_Position, m_Turn, m_packet->systemAddress.systemIndex, m_CDATID, m_BDATID);
					}
				}break;

			case ID_MODIFIED_PACKET:
				{
				printf("Packet: ID_MOT\n");
				}break;

			case UNS_REQUEST_LINE:
				{
#pragma message("FIXME Class Optimise Variable Reciever")
				char* i_Filename = new char[UNS_LINE_MAX];
				unsigned int i_Address;

				i_BitTransfer.acRead(i_Address);

#ifdef PTRSTREAMS
				stringCompressor->DecodeString(i_Filename, UNS_LINE_MAX, i_BitTransfer);
#else
				stringCompressor->DecodeString(i_Filename, UNS_LINE_MAX, &i_BitTransfer);
#endif

				UNSRequest *i_ResourceRequest = new UNSRequest;
				i_ResourceRequest->m_RequestType = UNS_RES_LINE;
				i_ResourceRequest->timeStamp = i_TimeStamp;
				i_ResourceRequest->typeId = i_PacketIdent;
				i_ResourceRequest->m_Filename = i_Filename;
				i_ResourceRequest->m_Address_S = i_Address;
				i_ResourceRequest->m_SysAddress = m_packet->systemAddress.systemIndex;

#pragma message("FIXME Mutex locks")
				SDL_mutexP(g_mutex_Requests);
				g_UNSResRequest.push_back(i_ResourceRequest);
				SDL_mutexV(g_mutex_Requests);

				printf("unServer ::: UNS_Request_Open_Resource \n");
				}break;

			case UNS_REQUEST_DATA:
				{
#pragma message("FIXME Class Optimise Variable Reciever")
				char* i_Filename = new char[UNS_LINE_MAX];
				unsigned int i_Address_S;
				unsigned int i_Address_E;

				i_BitTransfer.acRead(i_Address_S);
				i_BitTransfer.acRead(i_Address_E);

#ifdef PTRSTREAMS
				stringCompressor->DecodeString(i_Filename, UNS_LINE_MAX, i_BitTransfer);
#else
				stringCompressor->DecodeString(i_Filename, UNS_LINE_MAX, &i_BitTransfer);
#endif

				UNSRequest *i_ResourceRequest = new UNSRequest;
				i_ResourceRequest->m_RequestType = UNS_RES_DATA;
				i_ResourceRequest->timeStamp = i_TimeStamp;
				i_ResourceRequest->typeId = i_PacketIdent;
				i_ResourceRequest->m_Filename = i_Filename;
				i_ResourceRequest->m_Address_S = i_Address_S;
				i_ResourceRequest->m_Address_E = i_Address_E;
				i_ResourceRequest->m_SysAddress = m_packet->systemAddress.systemIndex;

#pragma message("FIXME Mutex locks")
				SDL_mutexP(g_mutex_Requests);
				g_UNSResRequest.push_back(i_ResourceRequest);
				SDL_mutexV(g_mutex_Requests);

				printf("unServer ::: UNS_Request_Open_Resource \n");
				}break;

			case UNS_REQUEST_PAGE:
				{
#pragma message("FIXME Class Optimise Variable Reciever")
				char* i_Filename = new char[UNS_LINE_MAX];
				unsigned int i_Address_S;
				unsigned int i_Address_E;

				i_BitTransfer.acRead(i_Address_S);
				i_BitTransfer.acRead(i_Address_E);

#ifdef PTRSTREAMS
				stringCompressor->DecodeString(i_Filename, UNS_LINE_MAX, i_BitTransfer);
#else
				stringCompressor->DecodeString(i_Filename, UNS_LINE_MAX, &i_BitTransfer);
#endif

				UNSRequest *i_ResourceRequest = new UNSRequest;
				i_ResourceRequest->m_RequestType = UNS_RES_PAGE;
				i_ResourceRequest->timeStamp = i_TimeStamp;
				i_ResourceRequest->typeId = i_PacketIdent;
				i_ResourceRequest->m_Filename = i_Filename;
				i_ResourceRequest->m_Address_S = i_Address_S;
				i_ResourceRequest->m_Address_E = i_Address_E;
				i_ResourceRequest->m_SysAddress = m_packet->systemAddress.systemIndex;

#pragma message("FIXME Mutex locks")
				SDL_mutexP(g_mutex_Requests);
				g_UNSResRequest.push_back(i_ResourceRequest);
				SDL_mutexV(g_mutex_Requests);

				printf("unServer ::: UNS_Request_Open_Resource \n");
				}break;

			case ID_CLIENT_DATA:
				{
				unAvatarList* i_VectorAvatarID;

				g_mutex_AvatarID->ac_Sync();
				i_VectorAvatarID = g_map_ClientAvatarID[m_packet->systemAddress.systemIndex];
				g_mutex_AvatarID->ac_Free();

				i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[0]].AV.Xform.Translation.x);
				i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[0]].AV.Xform.Translation.y);
				i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[0]].AV.Xform.Translation.z);
				i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[0]].Angles.y);

				for(unsigned int i_AVID = 0; i_AVID < i_VectorAvatarID[0].vec_Index.size(); i_AVID++)
					{
					i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[i_AVID]].AV.Xform.Translation.x);
					i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[i_AVID]].AV.Xform.Translation.y);
					i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[i_AVID]].AV.Xform.Translation.z);
					i_BitTransfer.acRead(Q_Forge->Forge[i_VectorAvatarID[0].vec_Index[i_AVID]].Angles.y);
					}
				}break;

			case ID_CLIENT_CHAR_DATA:
				{
				i_BitTransfer.acRead(m_CharListID);

				printf("unServer trace %i\n", m_CharListID);

				std::vector<int>* i_VectorCharacterID;

				SDL_mutexP(g_mutex_CharacterID);
				if(g_map_ClientCharacterID.find(m_packet->systemAddress.systemIndex) == g_map_ClientCharacterID.end())
					{
					SDL_mutexV(g_mutex_CharacterID);
					}
				else
					{
					i_VectorCharacterID = g_map_ClientCharacterID[m_packet->systemAddress.systemIndex];

					i_VectorCharacterID[0][m_CharListID] = acServerRecieveCharacterData(&i_BitTransfer);

					SDL_mutexV(g_mutex_CharacterID);

					//#### State Change Test ####
					if(m_CharListID == i_VectorCharacterID[0].size() - 1)
						{
						BitTransfer i_BitTransferClient(ID_CLIENT_CHAR_RECIEVED);

						g_unPeer->Send((const char*)i_BitTransferClient.m_Data, i_BitTransferClient.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddressST[m_packet->systemAddress.systemIndex], true);
						}
					}
				}break;

			case ID_DISCONNECTION_NOTIFICATION:
			case ID_CONNECTION_LOST:
				{
				bool i_Success = g_Domain.acAvatarShutdownClient(m_packet->systemAddress.systemIndex);
				if(i_Success) printf("REPORT:::Domain 'Default' client disconnects %i\n", m_packet->systemAddress.systemIndex);
				else printf("ERROR:::Domain 'Default' cannot find and disconnect client or client never fully connected %i\n", m_packet->systemAddress.systemIndex);
				}break;
			}
		}

	SDL_mutexV(g_mutex_Packet);
}

void PacketPump::acAvatarPlace(QpoVec3d i_Position, float i_Rotation, unsigned short i_SysIndex)
{
	SDL_mutexP(g_mutex_Domain);
	g_Domain.acAvatarStart(i_Position, i_Rotation, i_SysIndex, 0, 0);
	SDL_mutexV(g_mutex_Domain);

	//#### Radial Start Packet
	//#### Infuse packet priority/lod algorithym
}

int PacketPump::acServerRecieveCharacterData(BitTransfer *i_BitTransfer)
{
	i_BitTransfer->acRead(m_ArchiveID);

	if(m_ArchiveID == -50) m_Index = player->BFO.NomCharacters;
	else
		{
		m_Index = m_ArchiveID;
		player->BFO.CharDATA[m_Index].ArchiveID = m_ArchiveID;
		}

#if 0
	stringCompressor->DecodeString(player->BFO.CharDATA[m_Index].AvatarREF, 256, i_BitTransfer);
	stringCompressor->DecodeString(player->BFO.CharDATA[m_Index].ShadowREF, 256, i_BitTransfer);
#endif

	//### Send Mouse Bytes
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].TEAM);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Class);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Level);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AvatarSCALE);

	//### Send Key Bytes
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].UnusedXP);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.EnergyEff);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.LeftArmSTRENGTH);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.RightArmSTRENGTH);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.LeftLegSTRENGTH);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.RightLegSTRENGTH);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.LeftArmSNAP);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.RightArmSNAP);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.LeftLegSNAP);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.RightLegSNAP);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.Height);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.Weight);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.PhysicalStr);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.Quickness);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.Dexterity);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.Constitution);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.AggPower);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].BodySKILL.DefPower);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].WeaponSKILL.Accuracy);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].WeaponSKILL.DrawSPD);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].WeaponSKILL.ReloadSPD);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].WeaponSKILL.RecoilHEIGHTrecover);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.TrailTYPE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.TrailRED);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.TrailGREEN);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.TrailBLUE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.TrailALPHA);
	
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.JinkTYPE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.JinkRED);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.JinkGREEN);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.JinkBLUE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.JinkALPHA);
	
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SteamTYPE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SteamRED);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SteamGREEN);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SteamBLUE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SteamALPHA);
	
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SpikeTYPE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SpikeRED);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SpikeGREEN);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SpikeBLUE);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelEFFECTS.SpikeALPHA);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellContainerID[0]);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellContainerID[1]);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellContainerID[2]);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellContainerID[3]);

	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CurrWEAPON);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CurrHEADARMOUR);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CurrUPPERARMOUR);
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CurrLOWERARMOUR);

	//######### -  ITEM DATA LOOP  - #########

	//### Number of Items
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].NomITEMS);

	jet=0;
	while(jet < player->BFO.CharDATA[m_Index].NomITEMS)
		{
#if 0
		//##### - Set ITEM Name
		stringCompressor->DecodeString(player->BFO.CharDATA[m_Index].ItemDATA[jet].Name, 256, i_BitTransfer);
#endif

		//##### - Set Item Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Type);

		//##### - Set Item Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ItemREF);

#if 0
		if(player->BFO.CharDATA[m_Index].ItemDATA[jet].Type == 0)
			{
			//##### - Set Character Item Actor Reference
			stringCompressor->DecodeString(player->BFO.CharDATA[m_Index].ItemDATA[jet].ItemActorREF, 256, i_BitTransfer);
			}
#endif

		//##### - Set Item Scale Factor
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ItemScaleFACT);

		//##### - Set Item Quality Level
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QualLVL);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Power);

		//##### - Get Item Ammo
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Ammo);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].RecoilHeight);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].RecoilDistance);

		//##### - Get Item Fire Rate
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FireRate);

		//##### - Get Item Accuracy
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Accuracy);

		//##### - Set Item Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].BulletCNT);

		//##### - Set Item Scope Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ScopeTYPE);

		//##### - Set Item Scope Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ScopeLOC.x);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ScopeLOC.y);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ScopeLOC.z);

		//##### - Set Item Laser Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].LaserTYPE);

		//##### - Set Item Laser Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].LaserLOC.x);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].LaserLOC.y);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].LaserLOC.z);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QAS_Fire);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QAS_ReloadBoltOut);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QAS_ReloadBoltIn);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QAS_ReloadClipOut);

		//##### - Set Item Sound
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QAS_ReloadClipIn);

		//##### - Get Item Armour
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ArmourFACTOR);

		//##### - Get Item Armour
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ArmourAMOUNT);

		//##### - Get Item Armour
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ArmourREGEN);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Smoke.CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[0].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[1].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[2].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[3].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Effect[4].CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].Fog.CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.INT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.ON);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.Red);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.Green);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.Blue);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.Scale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].FogLight.CNT);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].ExpandSTRENGTH);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_NoWEP);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_TimeScale);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Gravity);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_LifeINC);

		//##### - Set Item Attribute
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_EnergyINC);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_EnergyEff);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Height);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Weight);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Strength);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Quickness);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Dexterity);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_Constitution);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_AggPower);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_DefPower);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_RArmStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_LArmStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_RLegStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_LLegStr);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_RArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_LArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_RLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_LLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_WEPAccuracy);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_WEPDrawSPD);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_WEPReloadSPD);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_WEPRecoilHR);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_JINKmovespeed);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_JINKpower);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].ItemDATA[jet].QA_ITEMINC_JINK3intensity);

		jet++;
		}

	//#### ACTIVE SPELLS
	jet=0;
	while(jet < 3)
		{
		//##### - Get Item QA Effect Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_TYPE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_INTENSITY);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_SWITCH);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL00RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL00GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL00BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL00ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL01RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL01GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL01BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL01ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL02RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL02GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL02BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL02ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL03RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL03GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL03BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL03ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL04RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL04GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL04BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_EFFECT_COL04ALPHA);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_EnergyEff);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_Height);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_Weight);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_Strength);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_Quickness);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_Dexterity);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_Constitution);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_AggPower);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_DefPower);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_RArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_LArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_RLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_LLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_RArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_LArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_RLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_LLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_WEPAccuracy);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_WEPDrawSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_WEPReloadSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_WEPRecoilHR);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_JINKmovespeed);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_JINKpower);

		//##### - Get SPELL Attributes
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].QA_SPELLINC_JINK3intensity);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].SpellSLOT[jet].LIVE);

		jet++;
		}

	//######### -  Physical Attacks SPEC DATA LOOP  - #########

	jet=0;
	while(jet < 30)
		{
		//##### - Get Item Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AttackSKILL[jet].Power);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AttackSKILL[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AttackSKILL[jet].MoveSpeed);

		//##### - Get Item Ammo
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AttackSKILL[jet].NumRotate);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AttackSKILL[jet].ExpRadius);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AttackSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  Cleric Class Skills LOOP  - #########

	jet=0;
	while(jet < 12)
		{
		//##### - Get Item Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CLSClericSKILL[jet].Cost);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CLSClericSKILL[jet].Potency);

		//##### - Get Item Power
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CLSClericSKILL[jet].Amount);

		//##### - Get Item Ammo
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CLSClericSKILL[jet].Speed);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CLSClericSKILL[jet].Duration);

		//##### - Get Item Recoil
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].CLSClericSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  SPELL DATA LOOP  - #########
	//### Number of Spells
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].NomSpells);

	jet=0;
	while(jet < player->BFO.CharDATA[m_Index].NomSpells)
		{
		//##### - Get Spell Quality
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QualityLVL);

		//##### - Set Spell Attribute IDs
		SHADOW=0;
		while(SHADOW < 10)
			{
			i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].AttributeID[SHADOW]);
			SHADOW++;
			}

		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_TYPE);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_INTENSITY);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_SWITCH);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL00RED);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL00GREEN);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL00BLUE);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL00ALPHA);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL01RED);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL01GREEN);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL01BLUE);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL01ALPHA);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL02RED);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL02GREEN);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL02BLUE);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL02ALPHA);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL03RED);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL03GREEN);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL03BLUE);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL03ALPHA);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL04RED);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL04GREEN);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL04BLUE);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_EFFECT_COL04ALPHA);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_IntBoost);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_EnergyEff);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_Height);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_Weight);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_Strength);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_Quickness);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_Dexterity);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_Constitution);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_AggPower);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_DefPower);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_RArmStr);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_LArmStr);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_RLegStr);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_LLegStr);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_LLegSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_WEPAccuracy);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_WEPDrawSPD);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_WEPReloadSPD);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_WEPRecoilHR);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_JINKmovespeed);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_JINKpower);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_JINK3intensity);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].Spells[jet].QA_SPELLINC_LLegSnap);
		jet++;
		}


	//#### SEND ANGEL COLOUR EDIT
	i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelCOLOURS.ANGELEDITFLAG);

	jet2=0;
	while(jet2 < 38)
		{
		//##### - Get Item Type
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelCOLOURS.RED[jet2]);

		//##### - Get Item Damage
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelCOLOURS.GREEN[jet2]);

		//##### - Get Item Power
		i_BitTransfer->acRead(player->BFO.CharDATA[m_Index].AngelCOLOURS.BLUE[jet2]);

		jet2++;
		}

	return m_Index;
}
