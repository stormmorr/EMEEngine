/*

    Master - Master Server Class Definition
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

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

	title = "Unification Server";
	version = "v0.00.015";

	QNetwork.Initialize();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
#if 0
	DigiMass = new Digi::DigiMassCore();
	DigiMass->acInit(DIGI_ERROR_PRINT);
#endif

#if 0
	unMessageCore = new UN::unMessageCore();
#endif

	QActiveFrameWork = new QAGE::QActiveFramewrk();
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

	SDL_mutexP(g_mutex_Domain);
	unDomainRadial* i_Domain = new unDomainRadial();
	SDL_mutexV(g_mutex_Domain);

	// Start RakNet Engine
	SDL_mutexP(g_mutex_unPeer);
	g_unPeer = RakNetworkFactory::GetRakPeerInterface();
	unStringCompressor::AddReference();
	g_unPeer->Startup(MAX_CONNECTIONS_ALLOWED, 30, &SocketDescriptor(10000,0), 1);
	g_unPeer->SetMaximumIncomingConnections(MAX_CONNECTIONS_ALLOWED);
	SDL_mutexV(g_mutex_unPeer);

	printf("Starting Raknet Server\n");

	/// Initialise any number of these threads
	m_PacketSocket.Start();
	m_PacketPump.Start();
	m_PacketStack.m_CDATA = &player->CDATA;
	m_PacketStack.Start();

	g_Domain.Start();

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

	for(;;) { printf("unServerTrace exit\n"); }
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
	time = 0;
	time = SDL_GetTicks();

	while( 1 )
		{
		lastTime = time;
		time = SDL_GetTicks();
		if( time == 0 ) time = 1;
		deltaTime = time - lastTime;

		SDL_Event ev;
		while( SDL_PollEvent( &ev ) )
			{
			///// No Events
			}

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

		if ('q' == getchar()) break;
		}

	//Server Shutdown
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
		printf("unServer Login Complete\n");
		}
    else
		{
		printf("Username and password combination not found in database for '%s'!\n", i_name);
		}
}

void Master::acModPacket(Packet* packet)
{
	BitTransfer i_BitTransfer(ID_CLIENT_MSG);

	g_unPeer->Send((const char*)i_BitTransfer.m_Data, i_BitTransfer.acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *g_map_SysAddress[packet->systemIndex], true);
}