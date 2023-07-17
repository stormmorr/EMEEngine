/*

    m_PacketStack - unServer packet output thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "Master.h"
#include "UNSGlobalHeader.h"

#if 0
#include <curl/curl.h>
#endif

using namespace RakNet;

	struct data {
    char trace_ascii; /* 1 or 0 */
  };
  
  static
  void dump(const char *text,
            FILE *stream, unsigned char *ptr, size_t size,
            char nohex)
  {
    size_t i;
    size_t c;
  
    unsigned int width=0x10;
  
    if(nohex)
      /* without the hex output, we can fit more on screen */
      width = 0x40;
  
    fprintf(stream, "%s, %zd bytes (0x%zx)\n", text, size, size);
  
    for(i=0; i<size; i+= width) {
  
      fprintf(stream, "%04zx: ", i);
  
      if(!nohex) {
        /* hex not disabled, show it */
        for(c = 0; c < width; c++)
          if(i+c < size)
            fprintf(stream, "%02x ", ptr[i+c]);
          else
            fputs("   ", stream);
      }
  
      for(c = 0; (c < width) && (i+c < size); c++) {
        /* check for 0D0A; if found, skip past and start a new line of output */
        if (nohex && (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
          i+=(c+2-width);
          break;
        }
        fprintf(stream, "%c",
                (ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.');
        /* check again for 0D0A, to avoid an extra \n if it's at width */
        if (nohex && (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
          i+=(c+3-width);
          break;
        }
      }
      fputc('\n', stream); /* newline */
    }
    fflush(stream);
  }
 
#if 0
  static
  int my_trace(CURL *handle, curl_infotype type,
              char *data, size_t size,
               void *userp)
  {
    struct data *config = (struct data *)userp;
    const char *text;
    (void)handle; /* prevent compiler warning */
  
    switch (type) {
    case CURLINFO_TEXT:
      fprintf(stderr, "== Info: %s", data);
    default: /* in case a new one is introduced to shock us */
      return 0;
  
    case CURLINFO_HEADER_OUT:
      text = "=> Send header";
      break;
    case CURLINFO_DATA_OUT:
      text = "=> Send data";
      break;
    case CURLINFO_SSL_DATA_OUT:
      text = "=> Send SSL data";
      break;
    case CURLINFO_HEADER_IN:
      text = "<= Recv header";
      break;
    case CURLINFO_DATA_IN:
      text = "<= Recv data";
      break;
    case CURLINFO_SSL_DATA_IN:
      text = "<= Recv SSL data";
      break;
    }
 
   dump(text, stderr, (unsigned char *)data, size, config->trace_ascii);
   return 0;
 }
#endif

PacketStack::PacketStack(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(PacketStack)
	SUPPORT_THREAD_NOTIFICATION

#if 0
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if(curl)
		{
		curl_easy_setopt(curl, CURLOPT_URL, "curl.haxx.se");
		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);
		}
#endif

#if 0
   CURL *curl;
   CURLcode res;
   struct data config;
 
   config.trace_ascii = 1; /* enable ascii tracing */
 
   curl = curl_easy_init();
   if(curl)
		{
		curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
		curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
 
		/* the DEBUGFUNCTION has no effect until we enable VERBOSE */
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
 
		curl_easy_setopt(curl, CURLOPT_URL, "curl.haxx.se");
		res = curl_easy_perform(curl);
 
		/* always cleanup */
		curl_easy_cleanup(curl);
		}
#endif
}

PacketStack::~PacketStack()
{
}

void PacketStack::Initialize(void)
{
  PP_STATE = 1;

  printf("Output Stack Initialization\n");
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int PacketStack::ThreadHandler()
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

unsigned char PacketStack::GetPacketIdentifier(Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	else
		return (unsigned char) p->data[0];
}

void PacketStack::Run(void)
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

void PacketStack::acSend(void)
{
	while(PP_STATE == 1)
		{
		SDL_mutexP(g_mutex_Requests);
		m_count = g_UNSResRequest.size() - 1;
		SDL_mutexV(g_mutex_Requests);

		if(m_count > -1)
			{
			SDL_mutexP(g_mutex_Requests);
			i_Request = g_UNSResRequest[m_count];
			g_UNSResRequest.pop_back();
			SDL_mutexV(g_mutex_Requests);

			switch(i_Request->m_RequestType)
				{
				case UNS_RES_LINE:
					{
					BitTransfer i_BitTransfer(UNS_RESOURCE_LINE);

					stringCompressor->EncodeString(g_DocumentBank->getDocument(0)->m_Content[i_Request->m_Address_S].c_str(), UNS_LINE_MAX, &i_BitTransfer);

#if 0
					SDL_mutexP(g_mutex_unPeer);
#endif

					g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddressST[i_Request->m_SysAddress], true);

					printf("SEND to CLIENT ::: UNS_RESOURCE_LINE\n");

#if 0
					SDL_mutexV(g_mutex_unPeer);
#endif
					} break;

				case UNS_RES_DATA:
					{
					for(unsigned int i_pack = 0; i_pack < i_Request->m_Address_E; i_pack++)
						{
						BitTransfer i_BitTransfer(UNS_RESOURCE_DATA);

						stringCompressor->EncodeString(g_DocumentBank->getDocument(0)->m_Content[i_Request->m_Address_S + i_pack].c_str(), UNS_LINE_MAX, &i_BitTransfer);

#if 0
						SDL_mutexP(g_mutex_unPeer);
#endif

						g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddressST[i_Request->m_SysAddress], true);

						printf("SEND to CLIENT ::: UNS_RESOURCE_DATA\n");

#if 0
						SDL_mutexV(g_mutex_unPeer);
#endif
						}
					} break;

				case UNS_RES_PAGE:
					{
					for(unsigned int i_pack = i_Request->m_Address_S; i_pack < i_Request->m_Address_E; i_pack++)
						{
						BitTransfer i_BitTransfer(UNS_RESOURCE_DATA);

						stringCompressor->EncodeString(g_DocumentBank->getDocument(0)->m_Content[i_pack].c_str(), UNS_LINE_MAX, &i_BitTransfer);

#if 0
						SDL_mutexP(g_mutex_unPeer);
#endif

						g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddressST[i_Request->m_SysAddress], true);

						printf("SEND to CLIENT ::: UNS_RESOURCE_PAGE\n");

#if 0
						SDL_mutexV(g_mutex_unPeer);
#endif
						}
					} break;

				case UNS_RES_CHAR_START:
					{
					BitTransfer i_BitTransfer(ID_SERVER_CHAR_START);

					i_BitTransfer.acPushAlloc(m_CDATA->NomCharacters);

#if 0
					SDL_mutexP(g_mutex_unPeer);
#endif

					g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddressST[i_Request->m_SysAddress], true);

					printf("SEND to CLIENT ::: UNS_RES_CHAR_START\n");

#if 0
					SDL_mutexV(g_mutex_unPeer);
#endif
					}break;

				case UNS_RES_CHAR:
					{
					if(i_Request->m_Count < m_CDATA->NomCharacters)
						{
						acServerSendCharacterData(i_Request->m_Count, *g_map_SysAddressST[i_Request->m_SysAddress]);
						i_Request->m_Count++;

						/////// Send a Character Data Resource Request ///////
						UNSRequest *i_ResourceRequest = new UNSRequest;
						i_ResourceRequest->m_RequestType = UNS_RES_CHAR;

						i_ResourceRequest->timeStamp = i_Request->timeStamp;
						i_ResourceRequest->typeId = i_Request->typeId;

						i_ResourceRequest->m_SysAddress = i_Request->m_SysAddress;
						i_ResourceRequest->m_Count = i_Request->m_Count;

						SDL_mutexP(g_mutex_Requests);
						g_UNSResRequest.push_back(i_ResourceRequest);
						SDL_mutexV(g_mutex_Requests);
						}
					else i_Request->m_Count = m_CDATA->NomCharacters;
					} break;
				}
			}
		}
}

void PacketStack::acPrintCharData(void)
{
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	printf("acPrintCharData~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");

	for(int i_iter1 = 0; i_iter1 < m_CDATA->NomCharacters; i_iter1++)
		{
		for(int i_iter2 = 0; i_iter2 < m_CDATA->CharDATA[i_iter1].NomITEMS; i_iter2++)
			{
			printf("unServer trace item name %s\n", m_CDATA->CharDATA[i_iter1].ItemDATA[i_iter2].Name);
			}
		}

	printf("~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~\n");
}

unsigned int PacketStack::acGetResource(const char* i_Filename, unsigned short i_Flags)
{
	switch(i_Flags)
		{
		case UNS_GET_FILE:
			{
			////// Search for currently loaded resources
			if(g_map_Documents.find(i_Filename) == g_map_Documents.end())
				{
				////// Allocate A new Document
				unsigned int i_DocumentId = g_DocumentBank->m_Document.size();
				TumDocument* TDocument = new TumDocument(i_Filename, i_Filename);
				g_map_Documents[i_Filename] = i_DocumentId;

#if 0
				TDocument->hwnd = hwnd;
#endif

				TDocument->addBlocker("[FLASH]", 40);
				TDocument->addExtractor(".swf", 40, 0);

#if 0
				TDocument->Tumble();
				TDocument->PrintResults();
#endif

				g_DocumentBank = new unDocumentBank();
				g_DocumentBank->m_Document.push_back(new TumDocument(i_Filename, i_Filename));
				return i_DocumentId;
				}
			else return g_map_Documents[i_Filename];
			} break;

		case UNS_DOC_NET:
			{
			////// Search for currently loaded resources
			if(g_map_Documents.find(i_Filename) == g_map_Documents.end())
				{
				////// Allocate A new Document
				unsigned int i_DocumentId = g_DocumentBank->m_Document.size();
				TumDocument* TDocument = new TumDocument(i_Filename, i_Filename);
				g_map_Documents[i_Filename] = i_DocumentId;

#if 0
				TDocument->hwnd = hwnd;
#endif

				TDocument->addBlocker("[FLASH]", 40);
				TDocument->addExtractor(".swf", 40, 0);

#if 0
				TDocument->Tumble();
				TDocument->PrintResults();
#endif

				g_DocumentBank = new unDocumentBank();
				g_DocumentBank->m_Document.push_back(new TumDocument(i_Filename, i_Filename));
				return i_DocumentId;
				}
			else return g_map_Documents[i_Filename];
			} break;
		}
}

bool PacketStack::acServerSendCharacterData(unsigned int i_Character, SystemAddress i_Address)
{
	BitTransfer i_BitTransfer(ID_SERVER_CHAR_DATA, BT_CHAR_DATA);

	i_BitTransfer.acPushAlloc(i_Character);

#if 0
	stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].AvatarREF, 12, &i_BitTransfer);
	stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].ShadowREF, 12, &i_BitTransfer);
#endif

	//### Send Mouse Bytes
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].TEAM);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Class);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Level);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AvatarSCALE);

	//### Send Key Bytes
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].UnusedXP);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.EnergyEff);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftArmSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightArmSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftLegSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightLegSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftArmSNAP);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightArmSNAP);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftLegSNAP);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightLegSNAP);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Height);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Weight);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.PhysicalStr);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Quickness);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Dexterity);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Constitution);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.AggPower);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.DefPower);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.Accuracy);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.DrawSPD);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.ReloadSPD);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.RecoilHEIGHTrecover);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailALPHA);
	
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkALPHA);
	
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamALPHA);
	
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeALPHA);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[0]);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[1]);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[2]);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[3]);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrWEAPON);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrHEADARMOUR);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrUPPERARMOUR);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrLOWERARMOUR);

	//######### -  ITEM DATA LOOP  - #########

	//### Number of Items
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].NomITEMS);

	jet=0;
	while(jet < m_CDATA->CharDATA[i_Character].NomITEMS)
		{
#if 0
		//##### - Set ITEM Name
		stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Name, 10, &i_BitTransfer);
#endif

		//##### - Set Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Type);

		//##### - Set Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ItemREF);

#if 0
		if(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Type == 0)
			{
			//##### - Set Character Item Actor Reference
			stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ItemActorREF, 15, &i_BitTransfer);
			}
#endif

		//##### - Set Item Scale Factor
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ItemScaleFACT);

		//##### - Set Item Quality Level
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QualLVL);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Power);

		//##### - Get Item Ammo
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Ammo);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].RecoilHeight);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].RecoilDistance);

		//##### - Get Item Fire Rate
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FireRate);

		//##### - Get Item Accuracy
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Accuracy);

		//##### - Set Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].BulletCNT);

		//##### - Set Item Scope Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeTYPE);

		//##### - Set Item Scope Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeLOC.x);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeLOC.y);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeLOC.z);

		//##### - Set Item Laser Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserTYPE);

		//##### - Set Item Laser Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserLOC.x);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserLOC.y);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserLOC.z);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_Fire);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadBoltOut);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadBoltIn);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadClipOut);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadClipIn);

		//##### - Get Item Armour
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ArmourFACTOR);

		//##### - Get Item Armour
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ArmourAMOUNT);

		//##### - Get Item Armour
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ArmourREGEN);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ExpandSTRENGTH);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_NoWEP);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_TimeScale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Gravity);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LifeINC);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_EnergyINC);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_EnergyEff);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Height);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Weight);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Strength);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Quickness);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Dexterity);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Constitution);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_AggPower);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_DefPower);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RArmStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LArmStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RLegStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LLegStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPAccuracy);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPDrawSPD);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPReloadSPD);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPRecoilHR);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_JINKmovespeed);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_JINKpower);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_JINK3intensity);

		jet++;
		}

	//#### ACTIVE SPELLS
	jet=0;
	while(jet < 3)
		{
		//##### - Get Item QA Effect Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_TYPE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_INTENSITY);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_SWITCH);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04ALPHA);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_EnergyEff);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Height);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Weight);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Strength);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Quickness);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Dexterity);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Constitution);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_AggPower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_DefPower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPAccuracy);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPDrawSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPReloadSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPRecoilHR);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_JINKmovespeed);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_JINKpower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_JINK3intensity);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].LIVE);

		jet++;
		}

	//######### -  Physical Attacks SPEC DATA LOOP  - #########

	jet=0;
	while(jet < 30)
		{
		//##### - Get Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].Power);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].MoveSpeed);

		//##### - Get Item Ammo
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].NumRotate);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].ExpRadius);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].Accuracy);

		jet++;
		}

	//######### -  Cleric Class Skills LOOP  - #########

	jet=0;
	while(jet < 12)
		{
		//##### - Get Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Cost);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Potency);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Amount);

		//##### - Get Item Ammo
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Speed);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Duration);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  SPELL DATA LOOP  - #########

	//### Number of Spells
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].NomSpells);

	jet=0;
	while(jet < m_CDATA->CharDATA[i_Character].NomSpells)
		{
		//##### - Get Spell Quality
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QualityLVL);

		//##### - Set Spell Attribute IDs
		SHADOW=0;
		while(SHADOW < 10)
			{
			i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].AttributeID[SHADOW]);
			SHADOW++;
			}

		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_TYPE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_INTENSITY);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_SWITCH);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_IntBoost);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_EnergyEff);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Height);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Weight);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Strength);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Quickness);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Dexterity);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Constitution);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_AggPower);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_DefPower);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RArmStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LArmStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RLegStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LLegStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LLegSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPAccuracy);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPDrawSPD);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPReloadSPD);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPRecoilHR);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_JINKmovespeed);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_JINKpower);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_JINK3intensity);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LLegSnap);
		jet++;
		}


	//#### SEND ANGEL COLOUR EDIT
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.ANGELEDITFLAG);

	jet2=0;
	while(jet2 < 38)
		{
		//##### - Get Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.RED[jet2]);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.GREEN[jet2]);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.BLUE[jet2]);

		jet2++;
		}

	g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, i_Address, true);

	return 1;
}

unsigned int PacketStack::acClientRecieveCharacterData(BitTransfer *i_BitPacket)
{
	unsigned int i_Index;

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("acClientRecieveCharacterData~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	BitTransfer i_BitTransfer(i_BitPacket->m_Data, i_BitPacket->acSize(), false);

	i_BitTransfer.acRead(i_Index);
	player->BFO.CharDATA[i_Index].State = 1;

	printf("i_Index~~~~~%i\n", i_Index);

	//stringCompressor->DecodeString(player->BFO.CharDATA[i_Index].AvatarREF, 12, &i_BitTransfer);
	stringCompressor->DecodeString(player->BFO.CharDATA[i_Index].ShadowREF, 12, &i_BitTransfer);

	//### Send Mouse Bytes
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].TEAM);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Class);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Level);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AvatarSCALE);

	//### Send Key Bytes
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].UnusedXP);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.EnergyEff);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.LeftArmSTRENGTH);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.RightArmSTRENGTH);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.LeftLegSTRENGTH);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.RightLegSTRENGTH);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.LeftArmSNAP);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.RightArmSNAP);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.LeftLegSNAP);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.RightLegSNAP);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.Height);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.Weight);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.PhysicalStr);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.Quickness);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.Dexterity);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.Constitution);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.AggPower);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].BodySKILL.DefPower);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].WeaponSKILL.Accuracy);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].WeaponSKILL.DrawSPD);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].WeaponSKILL.ReloadSPD);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].WeaponSKILL.RecoilHEIGHTrecover);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.TrailTYPE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.TrailRED);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.TrailGREEN);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.TrailBLUE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.TrailALPHA);
	
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.JinkTYPE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.JinkRED);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.JinkGREEN);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.JinkBLUE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.JinkALPHA);
	
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SteamTYPE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SteamRED);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SteamGREEN);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SteamBLUE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SteamALPHA);
	
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SpikeTYPE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SpikeRED);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SpikeGREEN);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SpikeBLUE);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelEFFECTS.SpikeALPHA);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellContainerID[0]);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellContainerID[1]);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellContainerID[2]);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellContainerID[3]);

	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CurrWEAPON);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CurrHEADARMOUR);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CurrUPPERARMOUR);
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CurrLOWERARMOUR);

	//######### -  ITEM DATA LOOP  - #########

	//### Number of Items
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].NomITEMS);

	printf("player->BFO.CharDATA[i_Index].NomITEMS %i\n", player->BFO.CharDATA[i_Index].NomITEMS);

	jet=0;
	while(jet < player->BFO.CharDATA[i_Index].NomITEMS)
		{
		//##### - Set ITEM Name
		stringCompressor->DecodeString(player->BFO.CharDATA[i_Index].ItemDATA[jet].Name, 10, &i_BitTransfer);

		printf("unServer trace decoded %s\n", player->BFO.CharDATA[i_Index].ItemDATA[jet].Name);

		//##### - Set Item Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Type);

		printf("unServer trace recieved %i\n", player->BFO.CharDATA[i_Index].ItemDATA[jet].Type);



		//##### - Set Item Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ItemREF);


		if(player->BFO.CharDATA[i_Index].ItemDATA[jet].Type == 0)
			{
			//##### - Set Character Item Actor Reference
			stringCompressor->DecodeString(player->BFO.CharDATA[i_Index].ItemDATA[jet].ItemActorREF, 15, &i_BitTransfer);
			}

		//##### - Set Item Scale Factor
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ItemScaleFACT);

		//##### - Set Item Quality Level
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QualLVL);

		//##### - Get Item Damage
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Power);

		//##### - Get Item Ammo
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Ammo);

		//##### - Get Item Recoil
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].RecoilHeight);

		//##### - Get Item Recoil
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].RecoilDistance);

		//##### - Get Item Fire Rate
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FireRate);

		//##### - Get Item Accuracy
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Accuracy);

		//##### - Set Item Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].BulletCNT);

		//##### - Set Item Scope Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ScopeTYPE);

		//##### - Set Item Scope Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ScopeLOC.x);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ScopeLOC.y);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ScopeLOC.z);

		//##### - Set Item Laser Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].LaserTYPE);

		//##### - Set Item Laser Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].LaserLOC.x);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].LaserLOC.y);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].LaserLOC.z);

		//##### - Set Item Sound
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QAS_Fire);

		//##### - Set Item Sound
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QAS_ReloadBoltOut);

		//##### - Set Item Sound
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QAS_ReloadBoltIn);

		//##### - Set Item Sound
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QAS_ReloadClipOut);

		//##### - Set Item Sound
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QAS_ReloadClipIn);

		//##### - Get Item Armour
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ArmourFACTOR);

		//##### - Get Item Armour
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ArmourAMOUNT);

		//##### - Get Item Armour
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ArmourREGEN);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Smoke.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[0].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[1].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[2].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[3].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Effect[4].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].Fog.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].FogLight.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].ExpandSTRENGTH);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_NoWEP);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_TimeScale);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Gravity);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_LifeINC);

		//##### - Set Item Attribute
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_EnergyINC);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_EnergyEff);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Height);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Weight);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Strength);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Quickness);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Dexterity);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_Constitution);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_AggPower);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_DefPower);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_RArmStr);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_LArmStr);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_RLegStr);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_LLegStr);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_RArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_LArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_RLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_LLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_WEPAccuracy);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_WEPDrawSPD);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_WEPReloadSPD);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_WEPRecoilHR);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_JINKmovespeed);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_JINKpower);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].ItemDATA[jet].QA_ITEMINC_JINK3intensity);

		jet++;
		}

#if 1
	//#### ACTIVE SPELLS
	jet=0;
	while(jet < 3)
		{
		//##### - Get Item QA Effect Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_TYPE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_INTENSITY);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_SWITCH);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL00RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL00GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL00BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL00ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL01RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL01GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL01BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL01ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL02RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL02GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL02BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL02ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL03RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL03GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL03BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL03ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL04RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL04GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL04BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_EFFECT_COL04ALPHA);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_EnergyEff);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_Height);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_Weight);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_Strength);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_Quickness);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_Dexterity);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_Constitution);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_AggPower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_DefPower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_RArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_LArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_RLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_LLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_RArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_LArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_RLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_LLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_WEPAccuracy);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_WEPDrawSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_WEPReloadSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_WEPRecoilHR);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_JINKmovespeed);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_JINKpower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].QA_SPELLINC_JINK3intensity);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].SpellSLOT[jet].LIVE);

		jet++;
		}

	//######### -  Physical Attacks SPEC DATA LOOP  - #########

	jet=0;
	while(jet < 30)
		{
		//##### - Get Item Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AttackSKILL[jet].Power);

		//##### - Get Item Damage
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AttackSKILL[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AttackSKILL[jet].MoveSpeed);

		//##### - Get Item Ammo
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AttackSKILL[jet].NumRotate);

		//##### - Get Item Recoil
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AttackSKILL[jet].ExpRadius);

		//##### - Get Item Recoil
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AttackSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  Cleric Class Skills LOOP  - #########

	jet=0;
	while(jet < 12)
		{
		//##### - Get Item Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CLSClericSKILL[jet].Cost);

		//##### - Get Item Damage
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CLSClericSKILL[jet].Potency);

		//##### - Get Item Power
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CLSClericSKILL[jet].Amount);

		//##### - Get Item Ammo
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CLSClericSKILL[jet].Speed);

		//##### - Get Item Recoil
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CLSClericSKILL[jet].Duration);

		//##### - Get Item Recoil
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].CLSClericSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  SPELL DATA LOOP  - #########

	//### Number of Spells
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].NomSpells);

	jet=0;
	while(jet < player->BFO.CharDATA[i_Index].NomSpells)
		{
		//##### - Get Spell Quality
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QualityLVL);

		//##### - Set Spell Attribute IDs
		SHADOW=0;
		while(SHADOW < 10)
			{
			i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].AttributeID[SHADOW]);
			SHADOW++;
			}

		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_TYPE);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_INTENSITY);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_SWITCH);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL00RED);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL00GREEN);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL00BLUE);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL00ALPHA);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL01RED);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL01GREEN);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL01BLUE);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL01ALPHA);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL02RED);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL02GREEN);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL02BLUE);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL02ALPHA);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL03RED);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL03GREEN);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL03BLUE);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL03ALPHA);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL04RED);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL04GREEN);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL04BLUE);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_EFFECT_COL04ALPHA);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_IntBoost);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_EnergyEff);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_Height);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_Weight);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_Strength);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_Quickness);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_Dexterity);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_Constitution);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_AggPower);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_DefPower);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_RArmStr);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_LArmStr);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_RLegStr);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_LLegStr);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_LLegSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_WEPAccuracy);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_WEPDrawSPD);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_WEPReloadSPD);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_WEPRecoilHR);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_JINKmovespeed);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_JINKpower);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_JINK3intensity);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].Spells[jet].QA_SPELLINC_LLegSnap);
		jet++;
		}


	//#### SEND ANGEL COLOUR EDIT
	i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelCOLOURS.ANGELEDITFLAG);

	jet2=0;
	while(jet2 < 38)
		{
		//##### - Get Item Type
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelCOLOURS.RED[jet2]);

		//##### - Get Item Damage
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelCOLOURS.GREEN[jet2]);

		//##### - Get Item Power
		i_BitTransfer.acRead(player->BFO.CharDATA[i_Index].AngelCOLOURS.BLUE[jet2]);

		jet2++;
		}
#endif

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	return i_Index;
}

bool PacketStack::acSizeServerCharacterData(unsigned int i_Character)
{
	BitTemplate i_BitTransfer(ID_SERVER_CHAR_DATA);

	i_BitTransfer.acPushAlloc(i_Character);

	//#########  - FILL SEND BUFFER -  #########

	//stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].AvatarREF, 12, &i_BitTransfer);
	//stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].ShadowREF, 12, &i_BitTransfer);

	printf("unServer trace i_Character %i AvatarREF %s\n", i_Character, player->BFO.CharDATA[i_Character].AvatarREF);
	printf("unServer trace i_Character %i ShadowREF %s\n", i_Character, player->BFO.CharDATA[i_Character].ShadowREF);

	//### Send Mouse Bytes
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].TEAM);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Class);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Level);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AvatarSCALE);

	printf("unServer trace i_Character %i TEAM %i\n", i_Character, player->BFO.CharDATA[i_Character].TEAM);
	printf("unServer trace i_Character %i Class %i\n", i_Character, player->BFO.CharDATA[i_Character].Class);
	printf("unServer trace i_Character %i Level %f\n", i_Character, player->BFO.CharDATA[i_Character].Level);
	printf("unServer trace i_Character %i AvatarSCALE %f\n", i_Character, player->BFO.CharDATA[i_Character].AvatarSCALE);

	//### Send Key Bytes
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].UnusedXP);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.EnergyEff);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftArmSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightArmSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftLegSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightLegSTRENGTH);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftArmSNAP);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightArmSNAP);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.LeftLegSNAP);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.RightLegSNAP);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Height);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Weight);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.PhysicalStr);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Quickness);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Dexterity);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.Constitution);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.AggPower);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].BodySKILL.DefPower);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.Accuracy);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.DrawSPD);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.ReloadSPD);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].WeaponSKILL.RecoilHEIGHTrecover);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.TrailALPHA);
	
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.JinkALPHA);
	
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SteamALPHA);
	
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeTYPE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeRED);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeGREEN);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeBLUE);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelEFFECTS.SpikeALPHA);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[0]);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[1]);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[2]);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellContainerID[3]);

	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrWEAPON);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrHEADARMOUR);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrUPPERARMOUR);
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CurrLOWERARMOUR);

	//######### -  ITEM DATA LOOP  - #########

	//### Number of Items
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].NomITEMS);

	printf("m_CDATA->CharDATA[i_Index].NomITEMS %i\n", m_CDATA->CharDATA[i_Character].NomITEMS);

	jet=0;
	while(jet < m_CDATA->CharDATA[i_Character].NomITEMS)
		{
		printf("unServer trace encoding %s\n", m_CDATA->CharDATA[i_Character].ItemDATA[jet].Name);

		//##### - Set ITEM Name
		//stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Name, 10, &i_BitTransfer);


		//##### - Set Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Type);

		printf("unServer trace send %i\n", m_CDATA->CharDATA[i_Character].ItemDATA[jet].Type);

#if 1
		//##### - Set Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ItemREF);


		if(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Type == 0)
			{
			//##### - Set Character Item Actor Reference
			//stringCompressor->EncodeString(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ItemActorREF, 15, &i_BitTransfer);
			}


		//##### - Set Item Scale Factor
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ItemScaleFACT);

		//##### - Set Item Quality Level
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QualLVL);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Power);

		//##### - Get Item Ammo
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Ammo);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].RecoilHeight);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].RecoilDistance);

		//##### - Get Item Fire Rate
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FireRate);

		//##### - Get Item Accuracy
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Accuracy);

		//##### - Set Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].BulletCNT);

		//##### - Set Item Scope Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeTYPE);

		//##### - Set Item Scope Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeLOC.x);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeLOC.y);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ScopeLOC.z);

		//##### - Set Item Laser Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserTYPE);

		//##### - Set Item Laser Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserLOC.x);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserLOC.y);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].LaserLOC.z);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_Fire);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadBoltOut);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadBoltIn);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadClipOut);

		//##### - Set Item Sound
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QAS_ReloadClipIn);

		//##### - Get Item Armour
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ArmourFACTOR);

		//##### - Get Item Armour
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ArmourAMOUNT);

		//##### - Get Item Armour
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ArmourREGEN);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Smoke.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[0].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[1].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[2].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[3].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Effect[4].CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].Fog.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.TYPE);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.INT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.ON);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Red);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Green);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Blue);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Alpha);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.Scale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.TIMER);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].FogLight.CNT);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].ExpandSTRENGTH);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_NoWEP);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_TimeScale);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Gravity);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LifeINC);

		//##### - Set Item Attribute
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_EnergyINC);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_EnergyEff);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Height);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Weight);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Strength);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Quickness);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Dexterity);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_Constitution);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_AggPower);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_DefPower);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RArmStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LArmStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RLegStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LLegStr);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LArmSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_RLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_LLegSnap);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPAccuracy);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPDrawSPD);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPReloadSPD);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_WEPRecoilHR);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_JINKmovespeed);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_JINKpower);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].ItemDATA[jet].QA_ITEMINC_JINK3intensity);
#endif

		jet++;
		}

#if 1
	//#### ACTIVE SPELLS
	jet=0;
	while(jet < 3)
		{
		//##### - Get Item QA Effect Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_TYPE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_INTENSITY);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_SWITCH);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL00ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL01ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL02ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL03ALPHA);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04RED);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04GREEN);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04BLUE);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_EFFECT_COL04ALPHA);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_IntBoost);

		//##### - Get Item Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_EnergyEff);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Height);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Weight);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Strength);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Quickness);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Dexterity);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_Constitution);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_AggPower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_DefPower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LArmStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LLegStr);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LArmSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_RLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_LLegSnap);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPAccuracy);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPDrawSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPReloadSPD);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_WEPRecoilHR);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_JINKmovespeed);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_JINKpower);

		//##### - Get SPELL Attributes
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].QA_SPELLINC_JINK3intensity);

		//##### - Set Item QA Effect Intensity
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].SpellSLOT[jet].LIVE);

		jet++;
		}

	//######### -  Physical Attacks SPEC DATA LOOP  - #########

	jet=0;
	while(jet < 30)
		{
		//##### - Get Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].Power);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].Damage);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].MoveSpeed);

		//##### - Get Item Ammo
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].NumRotate);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].ExpRadius);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AttackSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  Cleric Class Skills LOOP  - #########

	jet=0;
	while(jet < 12)
		{
		//##### - Get Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Cost);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Potency);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Amount);

		//##### - Get Item Ammo
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Speed);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Duration);

		//##### - Get Item Recoil
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].CLSClericSKILL[jet].Accuracy);

		jet++;
		}


	//######### -  SPELL DATA LOOP  - #########

	//### Number of Spells
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].NomSpells);

	jet=0;
	while(jet < m_CDATA->CharDATA[i_Character].NomSpells)
		{
		//##### - Get Spell Quality
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QualityLVL);

		//##### - Set Spell Attribute IDs
		SHADOW=0;
		while(SHADOW < 10)
			{
			i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].AttributeID[SHADOW]);
			SHADOW++;
			}

		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_TYPE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_INTENSITY);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_SWITCH);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL00ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL01ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL02ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL03ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04RED);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04GREEN);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04BLUE);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_EFFECT_COL04ALPHA);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_IntBoost);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_EnergyEff);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Height);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Weight);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Strength);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Quickness);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Dexterity);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_Constitution);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_AggPower);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_DefPower);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RArmStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LArmStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RLegStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LLegStr);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LLegSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPAccuracy);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPDrawSPD);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPReloadSPD);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_WEPRecoilHR);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_JINKmovespeed);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_JINKpower);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_JINK3intensity);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LArmSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_RLegSnap);
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].Spells[jet].QA_SPELLINC_LLegSnap);
		jet++;
		}


	//#### SEND ANGEL COLOUR EDIT
	i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.ANGELEDITFLAG);

	jet2=0;
	while(jet2 < 38)
		{
		//##### - Get Item Type
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.RED[jet2]);

		//##### - Get Item Damage
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.GREEN[jet2]);

		//##### - Get Item Power
		i_BitTransfer.acPushAlloc(m_CDATA->CharDATA[i_Character].AngelCOLOURS.BLUE[jet2]);

		jet2++;
		}
#endif

	printf("BitTemplate acSize %i acSizeBits %i\n", i_BitTransfer.acSize(), i_BitTransfer.acSizeBits());

	for(;;){};

	return 1;
}
