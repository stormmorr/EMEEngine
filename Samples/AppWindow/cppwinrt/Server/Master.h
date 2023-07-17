/*

    icMaster - Unification Master Server
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef MASTER_H
#define MASTER_H

#include "../UnSRC/QServerFramewrk.h"

#include "../UnSRC/Utility/Singleton.h"
#include "../UnSRC/Utility/datatypes.h"
#include "../UnSRC/Process/unMessageCore.h"
#include <string>
#include <vector>

#include "icMySQL.h"
#include "PacketSocket.h"
#include "PacketPump.h"
#include "PacketStack.h"

//Mode Selection
#if 0
#define SVR_MOD_WOFFLE 1
#endif

class Master
{
public:
	Master();
	~Master();

public:
	static volatile bool stopEvent;

	void Initialize( int Width, int Height, bool Fullscreen );
	void Run();

	// Time elapsed in the frame
	float GetFrameTime() { return (float)deltaTime; }

	void acRecieveClient (const char* i_name, const char* i_password);
	void acModPacket(Packet* packet);

	bool SendCharDefs (unsigned int accID);

	void acLoadResources(void);

    unsigned int m_currentModel;

	PacketSocket m_PacketSocket;
	PacketPump m_PacketPump;
	PacketStack m_PacketStack;

	icMySQL* m_MySQL;

	void acResourceFrame(void);

#if 1
	UN::unMessageCore *m_unMessageCore;
#endif

	QAGE::QActiveFramewrk *QActiveFrameWork;

	static Master* instance();

private:
	std::string title;
	std::string version;

	UInt32 time;
	UInt32 lastTime;
	UInt32 deltaTime;

	unsigned int m_lastTick;

	static Master* s_instance;
};

#endif
