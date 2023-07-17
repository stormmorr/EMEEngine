/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	- Minor Component -Avatar When In Human Form-
		-Header File Classifications-
*/

#ifndef __Q_OBJ_ObjectTypes__
#define __Q_OBJ_ObjectTypes__

//Testing
#include "Q-OBJ-Building.h"

namespace GVARS
{

class Q_ObjectCLS			//----== OBJECT ==----
{
public:
	QpoVec3d		Pos;
	float			Scale;
	float			StrengthBANK;
	float			StrengthMAX;
	QInt			CollisionTYPE;
	QInt			AvID;
	QInt			LIVE;
};

		//----== BUILD MODE ITEMS ==----

class Q_BMSentryCLS
{
public:
	QpoVec3d		Pos;
	int				ZoneID;
	int				QObjID;
	QpoVertex		ImageLvert;
	float			Range;
	float			Damage;
	float			Power;
	float			FireRate;
	float			Accuracy;
	QInt			BulletCNT;
	float			FireRateCNT[50];
	QInt			LIVE;
	int				ImmCNT;
};


class Q_Global_BMSentry
{
public:
	Q_BMSentryCLS BMSentry[10];
};

extern QSharedStruct<Q_Global_BMSentry> Q_BMSentry;

class Q_Global_QBuilding
{
public:
	Q_BuildingCLS Building[10];
};

extern QSharedStruct<Q_Global_QBuilding> Q_Building;

class Q_Global_Object
{
public:
	Q_ObjectCLS Object[151];
};

extern QSharedStruct<Q_Global_Object> Q_Object;

class Q_Global_DMG_Mask
{
public:
	std::vector<std::shared_ptr<VoxelDamageMask>> m_vec_VoxelDamageMask;
};

extern QSharedStruct<Q_Global_DMG_Mask> Q_VoxelDamage;

};//END namespace GVARS

#endif