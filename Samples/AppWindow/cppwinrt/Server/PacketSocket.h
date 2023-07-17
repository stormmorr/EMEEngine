/*

    m_PacketSocket - Networking Thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_PACKETSOCKET_H
#define UNS_PACKETSOCKET_H

#include "../UnSRC/Utility/RakNetMsgIdent.h"
#include "unsStringCompressor.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

#include "BitTransfer.h"
#include "GetTime.h"
#include "unsStringCompressor.h"

#include "Thread.h"

#include <vector>

#define UNS_PACKET_HEIGHT 2
#define UNS_PACKET_DEPTH 150

class PacketVectorSwing
{
public:
	PacketVectorSwing()
		{
		for(unsigned int i_Height = 0; i_Height < UNS_PACKET_HEIGHT; i_Height++)
			{
			std::vector<Packet*> i_VecPacket;
			i_VecPacket.resize(UNS_PACKET_DEPTH);
			m_Depth = UNS_PACKET_DEPTH;
			m_vec_Packet.push_back(i_VecPacket);
			m_Height++;
			}

		m_PlaceDepth = 0;
		m_PlaceHeight = 0;
		m_ReadDepth = 0;
		m_ReadHeight = 0;
		}
	~PacketVectorSwing() {};

	std::vector<std::vector<Packet*> > m_vec_Packet;

	unsigned int m_Depth;
	unsigned int m_Height;

	unsigned int m_ReadDepth;
	unsigned int m_ReadHeight;

	unsigned int m_PlaceDepth;
	unsigned int m_PlaceHeight;
};

class PacketSocket : public CThread
{
public:
	PacketSocket(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~PacketSocket();

	void Initialize( void );
	void Run();
	void Scan();

	int PP_STATE;

	Packet *m_packet;

protected:
	virtual	int ThreadHandler();
};

#endif
