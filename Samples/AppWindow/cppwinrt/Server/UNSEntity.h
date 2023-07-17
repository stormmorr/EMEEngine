/*

    UNSEntity.h - Entity Layer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_ENTITY_H
#define UNS_ENTITY_H

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

#define UNS_ENTITY_PLAYER 0
#define UNS_ENTITY_AVATAR 1
#define UNS_ENTITY_NNBOT 2

class unEntAvatar
{
public:
	unEntAvatar();
	unEntAvatar(QpoVec3d i_Position, float i_Rotation, int i_BDATID, int CDATID);
	unEntAvatar(QpoVec3d i_Position, float i_Rotation, int i_STATE, int i_BDATID, int CDATID);
	virtual ~unEntAvatar();

public:
	QpoVec3d m_Pos;
	float m_Rotation;
	float m_QuanPass;
	int m_CDATID;
	int m_BDATID;

	int m_Type;
	int m_STATE;
};

#endif