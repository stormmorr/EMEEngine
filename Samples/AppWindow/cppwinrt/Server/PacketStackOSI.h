/*

    m_PacketStack - Texture Management Library
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_PACKETSTACK_H
#define UNS_PACKETSTACK_H

#include "../UnSRC/Utility/RakNetMsgIdent.h"
#include "unStringCompressor.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

#include "BitTransfer.h"
#include "GetTime.h"

#include "Thread.h"

#include "UNSResource.h"

class PacketStack : public CThread
{
public:
	PacketStack(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~PacketStack();

	void Initialize(void);
	void Run(void);
	void acSend(void);

	unsigned char GetPacketIdentifier(Packet *p);
	unsigned int acGetResource(const char* i_Filename, unsigned short i_Flags);

	void ClientLogon(Packet *p);

	bool acServerSendCharacterData(unsigned int i_Character, SystemAddress i_Address);
	unsigned int acClientRecieveCharacterData(BitTransfer *i_BitPacket);
	bool acSizeServerCharacterData(unsigned int i_Character);

	int PP_STATE;

	void acPrintCharData(void);

	Q_CharacterDATA *m_CDATA;

private:
	int m_count;
	UNSRequest* i_Request;

protected:
	virtual	int ThreadHandler();
};

#endif