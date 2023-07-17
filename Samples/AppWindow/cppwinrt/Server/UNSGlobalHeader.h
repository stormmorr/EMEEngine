/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

		Header File Classifications
				Global Definitions

*/

#ifndef UNS_GLOBALHEADER_H
#define UNS_GLOBALHEADER_H

//--------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------

#include "../UnSRC/Gui/TumDocument.h"
#include "UNSResource.h"
#include "UNSDomain.h"
#include "PacketSocketInterface.h"

//*#include "RakNetTypes.h"
#include <SDL_mutex.h>
#include <map>

//--------------------------------------------------------------------
// DEFINES
//--------------------------------------------------------------------

 	extern unDocumentBank *g_DocumentBank;

	extern std::vector<UNSRequest*> g_UNSResRequest;

	extern SDL_mutex* g_mutex_Requests;
	extern SDL_mutex* g_mutex_unPeer;
	extern SDL_mutex* g_mutex_Packet;
	extern SDL_mutex* g_mutex_Domain;
	extern SDL_mutex* g_mutex_NomAvatar;
	extern unMutexCC* g_mutex_AvatarID;
	extern SDL_mutex* g_mutex_CharacterID;

	//////// System Address Map
	//*extern std::map<unsigned short, SystemAddress*> g_map_SysAddress;
	//*extern std::map<unsigned short, SystemAddress*> g_map_SysAddressST;
	extern std::map<unsigned short, unDomainAddress> g_map_ClientDom;
	extern std::map<unsigned short, unAvatarList*> g_map_ClientAvatarID;
	extern std::map<unsigned short, std::vector<int>*> g_map_ClientCharacterID;

	extern std::map<unsigned short, std::string> g_map_ClientName;
	extern std::map<unsigned short, std::string> g_map_ClientPassword;

	extern std::map<const char*, unsigned int> g_map_Documents;
	extern std::map<const char*, unsigned int>::iterator g_map_DocIterator;

	extern PacketVectorSwing vec_Packet;

	//*extern RakPeerInterface* g_unPeer;

	extern unDomainRadial g_Domain;

	extern int g_nom_Avatar;

//-------------------------------------------------------------------
// GLOBALS		/END
//-------------------------------------------------------------------

#pragma message ("UNS Global Variables  [UNSGlobalHeader.h]")

#endif