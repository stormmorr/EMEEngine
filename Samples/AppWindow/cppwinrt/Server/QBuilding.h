/*

	QBuilding - QAGE Buildings ingame
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QBUILDING_H
#define QBUILDING_H

#include "../UnSRC/QServerFramewrk.h"

#include "../UnSRC/Utility/Singleton.h"
#include "../UnSRC/Utility/datatypes.h"
#include <string>
#include <vector>

#include "icMySQL.h"
#include "PacketSocket.h"
#include "PacketPump.h"
#include "PacketStack.h"

class QBuilding
{
public:
	QBuilding();
	~QBuilding();

public:
	QpoVec3d m_Position;
	int m_inZone;
	QObject m_QObject;
	int m_BuildingType;

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

#if 0
	UN::unMessageCore *unMessageCore;
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
