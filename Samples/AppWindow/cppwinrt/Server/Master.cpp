/*

    Master - Master g_unPeer Class Definition
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "Master.h"
#include "../UnSRC/Utility/unConsole.h"
#include "Q-NET-ProtoMap.h"
#include "UNSGlobalHeader.h"
#include "time.h"

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

	QNetwork.Initialize();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
#if 0
	DigiMass = new Digi::DigiMassCore();
	DigiMass->acInit(DIGI_ERROR_PRINT);
#endif

	//QActiveFrameWork = new QAGE::QActiveFramewrk();
	//QActiveFrameWork->acActiveInit();
}

Master::~Master()
{
}

void Master::Initialize(int width, int height, bool fullscreen)
{
	////// Load File Resources
	acLoadResources();

#if 0
	m_MySQL = new icMySQL;
	m_MySQL->Initialize();

#ifdef _WIN32    //assume remote connection for windows
	m_MySQL->Connect("62.44.82.8", "obi", "ttoObi1", "drupal", 10000);
#else
	m_MySQL->Connect("localhost", "root", "new", "drupal", 10000);
#endif
#endif

	char buffer[200];
	sprintf( buffer, "%s %s", title.c_str(), version.c_str() );
	SDL_WM_SetCaption( buffer, NULL );

	/// Set Mutex Locks
	g_mutex_Requests = SDL_CreateMutex();
	g_mutex_unPeer = SDL_CreateMutex();
	g_mutex_Packet = SDL_CreateMutex();
	g_mutex_Domain = SDL_CreateMutex();
	g_mutex_NomAvatar = SDL_CreateMutex();
	g_mutex_AvatarID = new unMutexCC();
	g_mutex_CharacterID = SDL_CreateMutex();

	SDL_mutexP(g_mutex_unPeer);
	// Pointers to the interfaces of our g_unPeer and client.
	// Note we can easily have both in the same program
	g_unPeer=RakNetworkFactory::GetRakPeerInterface();
	RakNetStatistics *rss;
	g_unPeer->SetIncomingPassword("Rumpelstiltskin", (int)strlen("Rumpelstiltskin"));
	g_unPeer->SetTimeoutTime(5000,UNASSIGNED_SYSTEM_ADDRESS);
	//PacketLogger packetLogger;
	//g_unPeer->AttachPlugin(&packetLogger);

	// Holds packets
	//Packet* p;

	// GetPacketIdentifier returns this
	//unsigned char packetIdentifier;

	// Record the first client that connects to us so we can pass it to the ping function
	SystemAddress clientID=UNASSIGNED_SYSTEM_ADDRESS;

	// Holds user data
	char portstring[30];

	//printf("This is a sample implementation of a text based chat g_unPeer.\n");
	//printf("Connect to the project 'Chat Example Client'.\n");
	//printf("Difficulty: Beginner\n\n");

	puts("Starting g_unPeer.");
	// Starting the g_unPeer is very simple.  2 players allowed.
	// 0 means we don't care about a connectionValidationInteger, and false
	// for low priority threads

	SocketDescriptor socketDescriptor(10000,0);
	bool b = g_unPeer->Startup(4, 30, &socketDescriptor, 1 );

	g_unPeer->SetMaximumIncomingConnections(5000);

	if(b) puts("g_unPeer started, waiting for connections.");
	else
		{ 
		puts("g_unPeer failed to start.  Terminating.");
		for(;;) {}
		}

	g_unPeer->SetOccasionalPing(true);
	g_unPeer->SetUnreliableTimeout(1000);

	unsStringCompressor::AddReference();

	DataStructures::List<RakNetSmartPtr<RakNetSocket> > sockets;
	g_unPeer->GetSockets(sockets);
	printf("Ports used by RakNet:\n");
	for (unsigned int i=0; i < sockets.Size(); i++)
		{
		printf("%i. %i\n", i+1, sockets[i]->boundAddress.port);
		}

	printf("Server IP is %s\n", g_unPeer->GetLocalIP(0));
	printf("Server GUID is %s\n", g_unPeer->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS).ToString());

	SDL_mutexV(g_mutex_unPeer);

	printf("Finished Initializing Raknet g_unPeer\n");

	/// Initialise any number of these threads
	m_PacketSocket.Start();
	m_PacketPump.Start();
	m_PacketStack.m_CDATA = &player->BFO;
	m_PacketStack.Start();

	SDL_mutexP(g_mutex_Domain);
	g_Domain.Start();
	SDL_mutexV(g_mutex_Domain);

#if 0
	QpoVec3d i_Position;
	i_Position.x = 0;
	i_Position.y = 0;
	i_Position.z = 0;

	g_Domain.acAvatarStartClient(i_Position, 0.7, 5, 1, 1);

	unMutexCC* testone = new unMutexCC();

	testone->ac_Fire();
	testone->ac_Stop();

	testone->ac_Sync();
	testone->ac_Free();

	for(;;) { printf("ung_unPeerTrace exit\n"); }
#endif

#ifdef SVR_MOD_WOFFLE
	//osiWoffle initialization
	printf("Woffle g_unPeer Initialization\n");
	m_unMessageCore = new UN::unMessageCore();

	m_unMessageCore->acStartProcessorContained("default", "default", "default");
#endif

	//// Enter Master Run Loop
	Run();
}

void Master::acLoadResources(void)
{
	printf("Loading File Resources\n");

	/////// Tumble Document
	TumDocument* TDocument = new TumDocument("EmptyDocument", "data//QoreResource//TestDocument.qore");

#if 0
	TDocument->hwnd = hwnd;
#endif

	TDocument->addBlocker("[FLASH]", 40);
	TDocument->addExtractor(".swf", 40, 0);

#if 0
	TDocument->Tumble();
	TDocument->PrintResults();
#endif

	g_DocumentBank = new unDocumentBank();
	g_DocumentBank->m_Document.push_back(TDocument);
}

void Master::Run()
{
#ifndef SVR_MOD_WOFFLE
	time = 0;
	time = SDL_GetTicks();

	while( 1 )
		{
		lastTime = time;
		time = SDL_GetTicks();
		if( time == 0 ) time = 1;
		deltaTime = time - lastTime;
#endif

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

#if 0	//Positioned for lighting
		if(QNetwork.m_Playing) QNetwork.PlayWorld(1.0f);
		//QActiveFrameWork->acQFrame();
#endif

#ifndef SVR_MOD_WOFFLE
		SDL_Event ev;
		while( SDL_PollEvent( &ev ) )
			{
			///// No Events
			}

		if ('q' == getchar()) break;
#else
		GraphBuilder &builder = m_unMessageCore->m_RexaryFacade.getGraphBuilder();

		printf("Woffle g_unPeer loaded, %s online, type 'q' to quit\n", m_unMessageCore->m_botName.c_str());

		string input;
		cout << "User> ";

		//Get input from the user from the keyboard
		while(true)
			{
			getline(cin, input); 
		
			if(input == "q")
				{
				break;
				}
			else //The user gave an input to the bot
				{
				StringPimpl response = builder.getResponse(input.c_str());
			
				//Print out what Rebecca says.
				cout << 			m_unMessageCore->m_botName.c_str() << " says: " << response.c_str() << endl;
				}

			cout << "User> ";
			}
#endif
#ifndef SVR_MOD_WOFFLE
		}
#endif

	//g_unPeer Shutdown
	g_unPeer->Shutdown(300);
	RakNetworkFactory::DestroyRakPeerInterface(g_unPeer);
}

bool Master::SendCharDefs (unsigned int accID)
{
	char query[1000];
	unsigned int acc_id = 0;
	sprintf (query, "SELECT open_slots FROM accounts where id = %d", accID);

	// Get the open slots
	unsigned short openSlots = m_MySQL->GetScalar (query); 

	//celOneParameterBlock datatmp;
	//datatmp.SetParameterDef (tto_network_openslots, "openslots");
	//datatmp.GetParameter (0).Set (openSlots);

	//pcnetwork->SendUpdate ("open_slots", &datatmp);

	// Get character definitions
	char querynew[1000];
	sprintf (querynew, "SELECT id, firstname, secondname, strength, endurance, constitution, wisdom, intellect, agility, copper, slot_number, guild_id FROM characters WHERE account_id = %d and char_type < 255", accID);

	icMySQLResultSet* results = m_MySQL->acSelectCommand (querynew);

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
	icMySQLResultSet* result = m_MySQL->acSelectCommand (query);
    icDatabaseRecord row = result->NextRecord ();

    if (row.IsValid ())
		{
		acc_id = atoi (row[0]);
		printf("ung_unPeer Login Complete\n");
		}
    else
		{
		printf("Username and password combination not found in database for '%s'!\n", i_name);
		}
}

void Master::acModPacket(Packet* packet)
{
	BitTransfer i_BitTransfer(ID_CLIENT_MSG);

	//g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddress[packet->systemIndex], true);
}
