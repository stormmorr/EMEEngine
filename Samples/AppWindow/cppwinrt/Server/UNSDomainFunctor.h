/*

    UNSDomainStack.h - Domain output thread
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of Ragecomm and/or the original author. Ragecomm and
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef UNS_DOMAINSTACK_H
#define UNS_DOMAINSTACK_H

#include "../UnSRC/Utility/RakNetMsgIdent.h"
#include "unsStringCompressor.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

#include "BitTransfer.h"
#include "GetTime.h"

#include "Thread.h"

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include <vector>

#include "UNSEntity.h"
#include "UNSResource.h"

class unDomainFunctor : public CThread
{
public:
	unDomainFunctor(void* pOwnerObject = NULL, icThreadData *pData = 0);
	virtual ~unDomainFunctor();

	void Initialize(void);
	void Run(void);
	void acBuild(void);

public:
	RadMeasure* m_Measure;
	std::vector<unEntAvatar*>* vec_entity_Avatar;
	std::vector<unsigned short>* vec_entity_SysIndex;
	std::vector<SystemAddress*>* vec_entity_SysAddress;
	std::vector<int>* vec_refresh_Client;

	SDL_mutex *m_mutex_Entity;

	int *m_RefreshCount;

private:
	int m_count;
	int m_AVcount;
	float m_Distance;
	unEntAvatar* i_Entity;

protected:
	virtual	int ThreadHandler();
	int PP_STATE;
	int m_Iter;
};

#endif
