//********************************************************
//********************************************************
//**	Q-NetHeader.h									**
//**	Author	-Max Lawlor								**
//**													**
//**	Network Header file								**
//**								Copyright 2006		**
//********************************************************
//********************************************************


//===========================================================================
//	NETWORK STRUCTS
//===========================================================================

typedef	struct NetMgr						NetMgr;
typedef	struct Client_Client				Client_Client;


//===========================================================================
//	NETWORK DEFINES AND VARIABLES
//===========================================================================

//###### DEFINES
#define NETMGR_LOCAL_MSG_BUFFER_SIZE		1500000
#define NETMGR_VERSION_MAJOR				1	
#define NETMGR_VERSION_MINOR				0

#define HOST_BUTTON_JUMP				(1<<0)
#define HOST_BUTTON_LEFT				(1<<1)
#define HOST_BUTTON_RIGHT				(1<<2)
#define HOST_BUTTON_FIRE				(1<<3)


// Upper bounds for both client/server	(they must share the same number of players)
#define NETMGR_MAX_CLIENTS					8

#define NETMGR_MAX_PLAYERS					512

#define NETMGR_MAX_IP_ADDRESS				128

#define NETMGR_SINGLE_PLAYER_NETID			0xff		// For single player games
#define NETMGR_SPECIAL_BOT_NETID			-2			// For bots

#define HOST_DEMO_NONE				0
#define HOST_DEMO_PLAY				1
#define HOST_DEMO_RECORD			2

#define HOST_MODE_SINGLE_PLAYER		1		// Single player
#define HOST_MODE_SERVER_CLIENT		2		// Server with local client
#define HOST_MODE_SERVER_DEDICATED	3		// Server dedicated (no client)
#define HOST_MODE_CLIENT			4		// Client only...

#define HOST_MAX_DEMOS			10
#define MAX_DEMO_NAME_SIZE		64

//###### VARIABLES INIT
geCSNetMgr_NetSession	*SessionList;
geCSNetMgr_NetClient	GEClient;
//NetMgr					*NMgr;
char					TempString[64];
int32					NumSessions;

//###### VARIABLES CONTROL
//Buffer_Data				Buffer;
geCSNetMgr_NetID		ClientId;
geCSNetMgr_NetMsgType	MsgType;
geCSNetMgr_NetClient	*pGEClient;
int32					Time;
int32					TotalMsgBytes;
uint8					NomCharDATA;
uint8					_->NomAIAvatars;
uint8					TempUint8,TempUint8SPEC,TempUint8C;
geFloat					TempFloat;
//char					TempString[20];
geVec3d					TempAngle;


//######## Network Structs #########

//#### Buffer Struct
/*typedef struct
{
	int32	Size;			// Size of buffer in bytes
	int32	Pos;			// Current size/pos
	uint8	*Data;			// Pointer to data
} Buffer_Data;*/


//#### Net Manager Struct
typedef struct NetMgr
{
	NetMgr				*SelfCheck1;

	geCSNetMgr			*CSNetMgr;

	// Local loopback info
	geBoolean			UseLocalBuffers;

	uint8				ClientBuffer[NETMGR_LOCAL_MSG_BUFFER_SIZE];
	uint8				ServerBuffer[NETMGR_LOCAL_MSG_BUFFER_SIZE];

	Buffer_Data			ClientToServerBuffer;
	Buffer_Data			ServerToClientBuffer;

	NetMgr				*SelfCheck2;
} NetMgr;


//CLIENT CLIENT
typedef struct Client_Client
{
	Client_Client		*Self1;
	//HWND				hWnd;

	//VidMode				VidMode;
	//Client_Mode			Mode;
	geEngine			*Engine;
	NetMgr				*NMgr;
	//GameMgr				*GMgr;

	//Client_StatusBar	StatusBar;

	NetMgr_NetState		NetState;
	geBoolean			MultiPlayer;			// == GE_true if the client is in a multi player game

	geCSNetMgr_NetClient	geClient;			// Info about us as a client (NetId, Name, etc...)

	int32				ViewPlayer;
	//geXForm3d			ViewXForm;

	float				Time;
	float				Ping;						// Current ping info from server
	float				NetTime;
	geBoolean			NetTimeGood;				// Last net time was recent...
	float				OldNetTime;
	float				TempTime;
	float				ServerPingBack;				// Time stamp from server, -1 if no time from server this frame

	//GenVSI_CMove		Move;						// Current move intentions

	float				ForwardSpeed;				// Forward/Back speed
	float				UpwardSpeed;				// Forward/Back speed
	geVec3d				Angles;						// Orientation
	uint16				ButtonBits;					// Current pressed buttons...

	//Client_Move			*LastMove;
	//Client_Move			*MoveStack;

	//GPlayer				Players[NETMGR_MAX_PLAYERS];
	//GPlayer				TempPlayers[CLIENT_MAX_TEMP_PLAYERS];		// For pre-prediction
	//Fx_Player			TempFxPlayers[CLIENT_MAX_TEMP_PLAYERS];

	// Fx Players NOTE - That Players index into FxPlayers using there index nbumber (Player - Client->Players)
	//Fx_Player			FxPlayers[NETMGR_MAX_PLAYERS];

	// Proc adresses
	//void				*ProcIndex[CLIENT_MAX_PROC_INDEX];

	// Scores, Health, etc about all clients connected from server
	//Client_ClientInfo	ClientInfo[NETMGR_MAX_CLIENTS];
	int32				ClientIndex;	// Index in list above where our info is stored...

	//uint16				Inventory[MAX_PLAYER_ITEMS];
	uint16				CurrentWeapon;
	uint16				OldWeapon;

	//uint16				OldInventory[MAX_PLAYER_ITEMS];

	//Server_Client		ServerClient;
	int32				ClientPlayer;

	//Client_Demo			Demo;					// Demo related info

	float				NextSend;

	//GenVSI				GenVSI;

	Client_Client		*Self2;
} Client_Client;


typedef struct Server_Client
{
	geBoolean			Active;

	geBoolean			Spawned;						// GE_true if this player has been spawned for the current world...

	geCSNetMgr_NetID	NetID;

	NetMgr_NetState		NetState;						// Current net state (Connected, etc)
	geBoolean			NetStateConfirmed[NETMGR_MAX_NET_STATES];

	//GPlayer				*Player;						// Player for this client

	// Data sent by client for intended move
	float				OldMoveTime;

	float				MoveTime;
	float				ForwardSpeed;					// Forward/Back speed
	geVec3d				Angles;							// Orientation
	uint16				ButtonBits;						// Buttons currently pressed for this frame

	geVec3d				Pos;							// Where the client currently thinks he is...

	//GenVSI_CMove		Move;

	// Some proprietary client info
	char				Name[64];					
	int32				Score;
	int32				Health;

	int32				NumPings;
	float				Pings[10];
	float				Ping;

	//geBoolean			InventoryHas[MAX_PLAYER_ITEMS];	// If player has item
	//uint16				Inventory[MAX_PLAYER_ITEMS];	// Amount of item

	int16				CurrentWeapon;					
	float				NextWeaponTime;

	geVec3d				GunOffset;

	// Bit set for each variable that needs to be sent over net for this client
	// Up to 16 are allowed now...
	//uint16				SendFlags[NETMGR_MAX_PLAYERS];	
	float				NextUpdate;			// Next time this client needs an update
} Server_Client;

typedef struct Server_Server
{
	Client_Client	*Client;

	//GenVSI			GenVSI;					// Genesis Vertual System Interface object (GenVSI)
	//GameMgr			*GMgr;					// Game Manager object (GameMgr)
	NetMgr			*NMgr;					// NetMgr

	float			NextUpdate;

	Server_Client	Clients[NETMGR_MAX_CLIENTS];
	//GPlayer			SvPlayers[NETMGR_MAX_PLAYERS];

	// Proc adresses
	//oid			*ProcIndex[SERVER_MAX_PROC_INDEX];

	int32			NumTotalPlayers;

	int32			NumClassSpawns;
	//Server_CSpawn	ClassSpawns[MAX_SERVER_CLASS_SPAWNS];

	// NOTE - The host allways loads the world, the server just keeps track of it...
	char					WorldName[128];					// Current level name
	geBoolean				ChangeWorldRequest;				// == GE_true if clients need update
	//GenVSI_NewWorldCB		*NewWorldCB;
	//GenVSI_ShutdownWorldCB	*ShutdownWorldCB1;				// Current world to be freed
	//GenVSI_ShutdownWorldCB	*ShutdownWorldCB2;				// World to be freed on request

	int32			ViewPlayer;							 

	//Server_NetStat	NetStats;

} Server_Server;


struct QHost
{
	NetMgr			*NMgr;					// NetMgr
	Server_Server	*Server;					//Server
	Client_Client	*Client;					//Server

	int32			Time;
	int32			ID;
	int32			Mode;
	char			ClientName;
	char			IPAddress;

	//Update Preparation
	Q_UPDATE		ServerPlayerUPDATE;
	Q_UPDATE		PlayerUPDATE;
	Q_UPDATE		AvatarUPDATE[25];

	//Temp Control Set
	Q_ControlSET	ControlSET;
} QHost;