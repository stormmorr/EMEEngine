/*

    Master - Master g_unPeer Class Definition
    Copyright OSIREM (C) 2007
	www.bitolyl.com/osirem  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/
#include "pch.h"
#include "Master.h"
//#include "../UnSRC/Utility/unConsole.h"

Master* Master::s_instance = 0;
Master* Master::instance()
{
  return s_instance;
}

Master::Master()
{
	assert(s_instance == 0);
	s_instance = this;

	title = "Unification g_unPeer";
	version = "v0.00.015";
}

Master::~Master()
{
}

void Master::acShutdown(void)
{
}

void Master::Initialize(int width, int height, bool fullscreen)
{
	////// Load File Resources
#if 0
	acLoadResources();
#endif

	m_SafeL = new icSafeL(0);
	m_SafeL->Initialize();

    //assume remote connection for windows
	m_SafeL->Connect("bitcoin-office.com", "root", "IntegerProperty18", "globalscapedb", 3306);

	/// Set Mutex Locks
	//g_mutex_Requests = SDL_CreateMutex();
	//g_mutex_AvatarID = new unMutexCC();

	//SDL_mutexP(g_mutex_unPeer);

	//// Enter Master Run Loop
	Run();
}

void Master::acLoadResources(void)
{
	printf("Loading File Resources\n");

	/////// Tumble Document
	//TumDocument* TDocument = new TumDocument("EmptyDocument", "data//QoreResource//TestDocument.qore");

#if 0
	TDocument->hwnd = hwnd;
#endif

	//TDocument->addBlocker("[FLASH]", 40);
	//TDocument->addExtractor(".swf", 40, 0);

#if 0
	TDocument->Tumble();
	TDocument->PrintResults();
#endif

	//g_DocumentBank = new unDocumentBank();
	//g_DocumentBank->m_Document.push_back(TDocument);
}

void Master::Run()
{
	//time = 0;
	//time = SDL_GetTicks();

	while( 1 )
		{
		//lastTime = time;
		//time = SDL_GetTicks();
		//if( time == 0 ) time = 1;
		//deltaTime = time - lastTime;

#if 0
		unsigned int tick;

#if 0
		tick = GetTickCount();
#else
		tick = clock();
#endif	

		// calculate the amount of elapsed seconds
		float elapsedSeconds;
		elapsedSeconds = (float)(tick - m_lastTick) / 1000.0f;

		m_lastTick = tick;

#if 1
		printf("elapsedSeconds %f\n", elapsedSeconds);
#endif
#endif

		//SDL_Event ev;
		//while( SDL_PollEvent( &ev ) )
		//	{
			///// No Events
		//	}

		//if ('q' == getchar()) break;
		//Get input from the user from the keyboard
		while(true)
			{
			//getline(cin, input); 
			}
		}

	//g_unPeer Shutdown
	acShutdown();
}

bool Master::SendCharDefs (unsigned int accID)
{
	char query[1000];
	unsigned int acc_id = 0;
	sprintf (query, "SELECT open_slots FROM accounts where id = %d", accID);

	// Get the open slots
	unsigned short openSlots = m_SafeL->GetScalar (query);

	//celOneParameterBlock datatmp;
	//datatmp.SetParameterDef (tto_network_openslots, "openslots");
	//datatmp.GetParameter (0).Set (openSlots);

	//pcnetwork->SendUpdate ("open_slots", &datatmp);

	// Get character definitions
	char querynew[1000];
	sprintf (querynew, "SELECT id, firstname, secondname, strength, endurance, constitution, wisdom, intellect, agility, copper, slot_number, guild_id FROM characters WHERE account_id = %d and char_type < 255", accID);

	//m_SafeL->acSelectCommand (querynew, false, false);

	//pcnetwork->SendUpdate ("char_defs", results);

	return true;
}

void Master::acRecieveClient(const char* i_name, const char* i_password)
{
	printf ("%s is to accessing an account\n", i_name);

    char IP_Address[22];
    IP_Address[0] = 0;

    //Build the query
    char query[1000];
    unsigned int acc_id = 0;
    sprintf (query, "SELECT uid FROM drupalusers WHERE name = '%s' AND pass = MD5('%s')", i_name, i_password);

    //Run the query
	//m_SafeL->acSelectCommand (query);

    if (1)
		{
		//acc_id = atoi (row[0]);
		printf("ung_unPeer Login Complete\n");
		}
    else
		{
		printf("Username and password combination not found in database for '%s'!\n", i_name);
		}
}

/*void Master::acModPacket(Packet* packet)
{
	BitTransfer i_BitTransfer(ID_CLIENT_MSG);

	//g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddress[packet->systemIndex], true);
}*/
