/*

    m_PacketPumpInterface - Networking Thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_PACKETPUMPINTERFACE_H
#define UNS_PACKETPUMPINTERFACE_H

//*#include "../UnSRC/Utility/RakNetMsgIdent.h"
//*#include "RakNetworkFactory.h"
//*#include "RakPeerInterface.h"
//*#include "RakNetStatistics.h"
//*#include "RakNetTypes.h"
#include "PacketSocketInterface.h"

#include "BitTransfer.h"
//*#include "BitStream.h"
//*#include "GetTime.h"
//*#include "unsStringCompressor.h"

#include "Thread.h"

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

namespace QAGE { class QActiveFramewrk; }

class PacketPumpInterface : public CThread
{
public:
	PacketPumpInterface(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~PacketPumpInterface();

	void Initialize( void );
	void Run();
	bool Scan();

	unsigned char acPacketIdentifier(Packet *p);

	void ClientLogon(Packet *p);

	bool acNetLogon(void);
	bool acOSINetLogon(void);

	void acServerRecieveCharacterData(BitTransfer *i_BitTransfer);

	bool acClientSendStart(void);
	bool acClientSendCharacterData(int i_Archive = 0);
	unsigned int acClientRecieveCharacterData(BitTransfer *i_BitTransfer);

	bool acStartNetplayer(QpoVec3d i_Position, QpoVec3d i_Angles, int f_VecID, unsigned int i_CDATID, unsigned int i_BDATID, unsigned int i_Team, int i_SysIndex);
	void acStartAvatarAI(int AIcounter, int Team);

	//*RakPeerInterface* m_unPeer;

	PacketVectorSwing* m_vec_Packet;

	//SDL_mutex* m_mutex_unPeer;
	//SDL_mutex* m_mutex_Packet;
	//SDL_mutex* m_mutex_State;

	//*SystemAddress serveAddress;
	//*SystemAddress clientAddress;

	Packet *m_packet;

	int m_RecieveCount;
	int m_ArchiveID;
	int m_AVcount;
	int m_AvCount;
	unsigned int m_Index;
	float m_Turning;
	unsigned int m_AVSLOT;
	int m_CDATID;
	int m_BDATID;
	int m_PP_STATE_I;
	int m_AvatarID;
	int m_VectorID;
	bool m_acClientSendStart;
	int m_ClientVectorID;
	int m_ClientAvatarID;

	int m_VecID;
	int m_IndexM;

	int m_PP_MODE;
	int m_PP_STATE;
	QpoVec3d m_Position;
	QpoVec3d m_Turn;
	unsigned int m_Team;

	QAGE::QActiveFramewrk* m_QActiveFramework;

protected:
	virtual	int ThreadHandler();
};

#endif