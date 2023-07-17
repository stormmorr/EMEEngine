/*

    m_PacketSocket - Networking Thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_PACKETSOCKETINTERFACE_H
#define UNS_PACKETSOCKETINTERFACE_H

//*#include "../UnSRC/Utility/RakNetMsgIdent.h"
//*#include "unsStringCompressor.h"
//*#include "RakNetworkFactory.h"
//*#include "RakPeerInterface.h"
//*#include "RakNetTypes.h"

#include "BitTransfer.h"
//*#include "GetTime.h"
//*#include "unsStringCompressor.h"

#include "Thread.h"

struct Packet
{
	// This is now in the systemAddress struct and is used for lookups automatically
	/// Server only - this is the index into the player array that this systemAddress maps to
	//	SystemIndex systemIndex;

	/// The system that send this packet.
	//*SystemAddress systemAddress;

	/// A unique identifier for the system that sent this packet, regardless of IP address (internal / external / remote system)
	/// Only valid once a connection has been established (ID_CONNECTION_REQUEST_ACCEPTED, or ID_NEW_INCOMING_CONNECTION)
	/// Until that time, will be UNASSIGNED_RAKNET_GUID
	//*RakNetGUID guid;

	/// The length of the data in bytes
	unsigned int length;

	/// The length of the data in bits
	//*BitSize_t bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};

#define UNS_PACKET_HEIGHT 2
#define UNS_PACKET_DEPTH 150

#define UNS_PRINT_LVL 1

class PacketVectorSwing
{
public:
	std::vector<Packet*> m_vec_Packet;
};

class PacketSocketInterface : public CThread
{
public:
	PacketSocketInterface(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~PacketSocketInterface();

	void Initialize( void );
	void Run();
	void Scan();

	int PP_STATE;

	//*RakPeerInterface* m_unPeer;

	PacketVectorSwing* m_vec_Packet;

	Packet* m_packet;

	//SDL_mutex* m_mutex_unPeer;
	//SDL_mutex* m_mutex_Packet;

protected:
	virtual	int ThreadHandler();
};

#endif