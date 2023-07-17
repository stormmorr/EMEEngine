/*

    icMaster - Unification Master Server
    Copyright OSIREM (C) 2007
	www.bitolyl.com/osirem  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef MASTER_H
#define MASTER_H

#include "Singleton.h"
#include "datatypes.h"
#include <string>
#include <vector>

#include "icSafeL.h"

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
//	void acModPacket(Packet* packet);

	bool SendCharDefs (unsigned int accID);

	void acLoadResources(void);

    unsigned int m_currentModel;

	void acFrame(void);
	void acShutdown(void);

	icSafeL* m_SafeL;

	void acResourceFrame(void);

#if 0
	UN::unMessageCore *m_unMessageCore;

	QAGE::QActiveFramewrk *QActiveFrameWork;
#endif

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
