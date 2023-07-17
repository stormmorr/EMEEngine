/*

    UNSDomainStack.h - Domain output thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_DOMAINSTACK_H
#define UNS_DOMAINSTACK_H

#include "../UnSRC/Utility/RakNetMsgIdent.h"
//*#include "unsStringCompressor.h"
//*#include "RakNetworkFactory.h"
//*#include "RakPeerInterface.h"
//*#include "RakNetTypes.h"

#include "BitTransfer.h"
//*#include "GetTime.h"

#include "Thread.h"

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include <vector>

#include "UNSEntity.h"
#include "UNSResource.h"

#define UNS_STATE_START 0
#define UNS_STATE_PLAY 1

class unDomainStack : public CThread
{
public:
	unDomainStack(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~unDomainStack();

	void Initialize(void);
	void Run(void);
	void acSend(void);

	unsigned int acClientRefresh(unsigned int i_Index);

public:
	RadMeasure* m_Measure;
	std::vector<unEntAvatar*>* vec_entity_Avatar;
	std::vector<unsigned short>* vec_entity_SysIndex;
	//*std::vector<SystemAddress*>* vec_entity_SysAddress;
	
	std::vector<unAvatarList*>* vec_avatar_Ident;
	std::vector<unRefreshList*>* vec_RefreshList;

	SDL_mutex *m_mutex_Dom_Avatar;
	SDL_mutex *m_mutex_Dom_Refresh;
	SDL_mutex *m_mutex_Dom_System;

	unMutexCC* m_mutexcc_Avatar;

	unMutexCC* m_mutexcc_AvatarId;
	unMutexCC* m_mutexcc_Refresh;

	//exstraineous? nessesary? to be decided ;>
	int *m_RefreshCount;

private:
	int m_count;
	int m_AVcount;
	float m_Distance;
	int m_RefCount;
	int m_AvatarCount;
	int m_AvatarTotal;

	unEntAvatar* i_Entity;

	unRefreshList* m_RefreshList;
	unAvatarList* m_AvatarList;

	//*SystemAddress* m_SystemAddress;

protected:
	virtual	int ThreadHandler();
	int PP_STATE;
	int m_Iter;
};

#endif
