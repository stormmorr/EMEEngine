/*

    m_PacketPump - Texture Management Library
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_PACKETPUMP_H
#define UNS_PACKETPUMP_H

#include "../UnSRC/Utility/RakNetMsgIdent.h"
#include "unStringCompressor.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

#include "BitTransfer.h"
#include "GetTime.h"
#include "unStringCompressor.h"

#include "Thread.h"

class PacketPump : public CThread
{
public:
	PacketPump(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~PacketPump();

	void Initialize(void);
	void Run();
	void Scan();

	unsigned char acPacketIdentifier(Packet *p);

	void ClientLogon(Packet *p);

	int acServerRecieveCharacterData(BitTransfer *i_BitTransfer);

	void acAvatarPlace(QpoVec3d i_Position, float i_Rotation, unsigned short i_SysIndex);

	Packet *m_packet;

	int m_ArchiveID;
	int m_CharacterID;
	int m_CharListID;
	unsigned int m_Index;

	QpoVec3d m_Position;
	float m_Turn;
	unsigned char m_RecieveCount;
	Uint32 m_AVcount;
	Uint32 m_CDATID;
	Uint32 m_BDATID;

	int PP_STATE;

protected:
	virtual	int ThreadHandler();
};

#endif