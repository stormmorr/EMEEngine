/*

    m_PacketStackInterface - Texture Management Library
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_PacketStackInterface_H
#define UNS_PacketStackInterface_H

#include "../UnSRC/Utility/RakNetMsgIdent.h"
//*#include "unsStringCompressor.h"
//*#include "RakNetworkFactory.h"
//*#include "RakPeerInterface.h"
//*#include "RakNetTypes.h"

#include "BitTransfer.h"
//*#include "GetTime.h"

#include "Thread.h"

#include "UNSResource.h"
#include "../UnSRC/Gui/TumDocument.h"

#include <map>

class PacketStackInterface : public CThread
{
public:
	PacketStackInterface(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~PacketStackInterface();

	void Initialize(void);
	void Run(void);
	void acSend(void);

	unsigned char acPacketIdentifier(Packet *p);
	unsigned int acGetResource(const char* i_Filename, unsigned short i_Flags);

	void ClientLogon(Packet *p);

	void acClientSendData(void);
	void acClientSendCharacterData(unsigned int i_Character);//*, SystemAddress i_Address);
	void acClientSendWorld(void);

	int PP_STATE;

	//*RakPeerInterface* m_unPeer;

	std::vector<UNSRequest*>* m_UNSResRequest;

	unDocumentBank *m_DocumentBank;
	std::map<const char*, unsigned int>* m_map_Documents;

	//SDL_mutex* m_mutex_unPeer;
	//SDL_mutex* m_mutex_Request;

	//*SystemAddress serveAddress;
	//*SystemAddress clientAddress;

	int m_SendWait;

private:
	int m_count;
	int m_AVcount;
	UNSRequest* i_Request;

protected:
	virtual	int ThreadHandler();
};

#endif