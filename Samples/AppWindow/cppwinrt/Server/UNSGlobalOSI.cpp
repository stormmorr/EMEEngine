/*

	Unification Server Global Initialization

	DATE - 11/05/07
		Copyright - J M Lawlor

*/

#pragma message ("|^^^ GLOBAL VARIABLE INITIALISATIONS ^^^|")

#include "UNSGlobalHeaderOSI.h"
#include <SDL_mutex.h>

//#####===--- GLOBAL VARIABLE INITIALISATIONS ---===#####

	unDocumentBank *g_DocumentBank;

	std::vector<UNSRequest*> g_UNSResRequest;

	RakVoice g_rakVoice;

	SDL_mutex *g_mutex_Requests;
	SDL_mutex *g_mutex_unPeer;
	SDL_mutex *g_mutex_Packet;
	SDL_mutex *g_mutex_Domain;
	SDL_mutex *g_mutex_NomAvatar;
	unMutexCC *g_mutex_AvatarID;
	SDL_mutex *g_mutex_CharacterID;

	//////// System Address Map
	std::map<unsigned short, SystemAddress*> g_map_SysAddress;
	std::map<unsigned short, SystemAddress*> g_map_SysAddressST;
	//std::map<unsigned short, unDomainAddress> g_map_ClientDom;
	//std::map<unsigned short, unAvatarList*> g_map_ClientAvatarID;
	std::map<unsigned short, std::vector<int>*> g_map_ClientCharacterID;

	std::map<unsigned short, std::string> g_map_ClientName;
	std::map<unsigned short, std::string> g_map_ClientPassword;

	std::map<const char*, unsigned int> g_map_Documents;
	std::map<const char*, unsigned int>::iterator g_map_DocIterator;

	PacketVectorSwing vec_Packet;

	RakPeerInterface* g_unPeer;

	//unDomainRadial g_Domain;

	int g_nom_Avatar;