/*

    Master - Master Server Class Definition
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "MasterOSI.h"
#include "../UnSRC/Utility/unConsole.h"
#include "Q-NET-ProtoMap.h"
#include "UNSGlobalHeaderOSI.h"
#include "time.h"

#include "portaudio.h"

#include "../Deps/RakNet-3.3/DependentExtensions/RakVoice.h"
#include "RakNetStatistics.h"

#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;

// Reads and writes per second of the sound data
// Speex only supports these 3 values
#define SAMPLE_RATE  (8000)
//#define SAMPLE_RATE  (16000)
//#define SAMPLE_RATE  (32000)

// I think one buffer has to be full (of samples) before you hear the sound.
// So higher frames per buffer means that there will be a larger latency before you hear the sound
// However, it would lock and unlock the buffer more often, hindering performance.
#define FRAMES_PER_BUFFER  (2048 / (32000 / SAMPLE_RATE))

bool mute = false;

PortAudioStream *stream;
PaError err;

// inputBuffer and outputBuffer is an array of SAMPLE of count framesPerBuffer
// A sample is one unit of sound.
// The sample rate is the number of sound samples taken per second
// I think one frame is a set of samples equal to the number of channels.  I'm not sure though or how that sample is arranged.
static int PACallback( void *inputBuffer, void *outputBuffer,
						  unsigned long framesPerBuffer,
						  PaTimestamp outTime, void *userData )
{

	if (inputBuffer && !mute)
		{
		// TODO - if the input data is mostly silence, don't send and save the bandwidth.

#ifndef _TEST_LOOPBACK
		unsigned i;

		for (i=0; i < g_unPeer->GetMaximumNumberOfPeers(); i++)
			{
			g_rakVoice.SendFrame(g_unPeer->GetSystemAddressFromIndex(i), inputBuffer);
			}
#else
		g_rakVoice.SendFrame(UNASSIGNED_SYSTEM_ADDRESS, inputBuffer);
#endif
		}

	g_rakVoice.ReceiveFrame(outputBuffer);

	return 0;
}

Master::Master(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(PacketPump)
	SUPPORT_THREAD_NOTIFICATION
}

Master* Master::s_instance = 0;
Master* Master::instance()
{
  return s_instance;
}

Master::~Master()
{
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int Master::ThreadHandler()
{
	bool bCanContinue = true;
	int nIncomingCommand;

	do
		{
		WaitForNotification(nIncomingCommand);

		switch (nIncomingCommand)
			{
			case CThread::CMD_INITIALIZE:
				Initialize(0, 0, true);
				HandleCommandImmediately(CThread::CMD_RUN);
				break;

			case CThread::CMD_RUN:
#if 0
				Lock();
#endif
				Run();
#if 0
				Unlock();
#endif
				break;

			case CThread::CMD_PAUSE:
				SetActivityStatus(CThread::THREAD_PAUSED);
				break;

			case CThread::CMD_STOP:
				bCanContinue = false;
				break;

			default:
				break;
			};

		} while (bCanContinue);

	return 0;	// ... if Thread task completition OK
}

void Master::Initialize( int width, int height, bool fullscreen )
{
	m_STATE = 1;

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
	QActiveFrameWork->acActiveInit();

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
	//unDomainRadial* i_Domain = new unDomainRadial();
	SDL_mutexV(g_mutex_Domain);

	// Start RakNet Engine
	SDL_mutexP(g_mutex_unPeer);
	g_unPeer = RakNetworkFactory::GetRakPeerInterface();
	unStringCompressor::AddReference();
	g_unPeer->Startup(MAX_CONNECTIONS_ALLOWED, 30, &SocketDescriptor(10000,0), 1);
	g_unPeer->SetMaximumIncomingConnections(MAX_CONNECTIONS_ALLOWED);
	g_unPeer->AttachPlugin(&g_rakVoice);
	g_rakVoice.Init(SAMPLE_RATE, FRAMES_PER_BUFFER*sizeof(SAMPLE));
	SDL_mutexV(g_mutex_unPeer);

	err = Pa_Initialize();
	if( err != paNoError ) paError();

	err = Pa_OpenStream(
		&stream,
		Pa_GetDefaultInputDeviceID(),
		1, // Num channels, whatever the fuck that means
		PA_SAMPLE_TYPE,
		NULL,
		Pa_GetDefaultOutputDeviceID(),
		1, // Num channels
		PA_SAMPLE_TYPE,
		NULL,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,            /* frames per buffer */
		0,               /* number of buffers, if zero then use default minimum */
		0, /* paDitherOff, // flags */
		PACallback,
		0 );

	if(err != paNoError) paError();

	err = Pa_StartStream( stream );

	if(err != paNoError) paError();

	printf("Raknet Server Online\n");

	/// Initialise any number of these threads
	m_PacketSocket.Start();
	m_PacketPump.Start();
	m_PacketStack.m_CDATA = &player->CDATA;
	m_PacketStack.Start();

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
}

void Master::paError(void)
{
	Pa_Terminate();
	fprintf( stderr, "An error occured while using the portaudio stream\n" );
	fprintf( stderr, "Error number: %d\n", err );
	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
	for(;;) {}
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

	//g_DocumentBank = new unDocumentBank();
	//g_DocumentBank->m_Document.push_back(TDocument);
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