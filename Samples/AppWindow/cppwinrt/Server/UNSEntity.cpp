/*

    UNSEntity.h - Entity Layer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "UNSDomain.h"

unEntAvatar::unEntAvatar()
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Pos.z = 0;
	m_Rotation = 0;
	m_QuanPass = 0;
	m_STATE = 0;
}

unEntAvatar::unEntAvatar(QpoVec3d i_Position, float i_Rotation, int i_BDATID, int CDATID)
{
	m_Pos.x = i_Position.x;
	m_Pos.y = i_Position.y;
	m_Pos.z = i_Position.z;
	m_Rotation = i_Rotation;
	m_QuanPass = 0;
	m_STATE = 0;
}

unEntAvatar::unEntAvatar(QpoVec3d i_Position, float i_Rotation, int i_STATE, int i_BDATID, int CDATID)
{
	m_Pos.x = i_Position.x;
	m_Pos.y = i_Position.y;
	m_Pos.z = i_Position.z;
	m_Rotation = i_Rotation;
	m_QuanPass = 0;
	m_STATE = i_STATE;
}

unEntAvatar::~unEntAvatar()
{
}