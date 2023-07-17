/*

    m_PacketStack - unServer packet output thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "Master.h"
#include "UNSGlobalHeaderOSI.h"

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

					g_unStringCompressor->EncodeString(g_DocumentBank->getDocument(0)->m_Content[i_Request->m_Address_S].c_str(), UNS_LINE_MAX, &i_BitTransfer);

#if 0
					SDL_mutexP(g_mutex_unPeer);
#endif

					g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddressST[i_Request->m_SysAddress], true);

					printf("SEND to CLIENT ::: UNS_RESOURCE_LINE\n");

#if 0
					SDL_mutexV(g_mutex_unPeer);
#endif
					} break;
				}
			}
		}
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