/*

	QBuilding - QAGE Buildings ingame
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef Q_BUILDING_H
#define Q_BUILDING_H

#include "../UnSRC/QActiveFramewrk.h"

#include "../UnSRC/Utility/Singleton.h"
#include "../UnSRC/Utility/datatypes.h"
#include <string>
#include <vector>
#include "time.h"

	//====____ Q-Building ____====//

class Q_BuildingCLS
{
public:
	Q_BuildingCLS();
	~Q_BuildingCLS();

public:
	int LIVE;

	//-POSITIONING-//
	QpoVec3d Pos;
	int m_inZone;
	int m_QObjectID;
	float Range;

	//-TYPE-//
	int m_BuildingType;

	//-OWNER-//
	int AVID;
	int Team;

	//- Graphics -//
	QpoVertex ImageLvert;
	int	m_TexID;

	//- Variables -//
	float m_Potency;

	//-OTHER-//
	int ImmCNT;
};

#endif
