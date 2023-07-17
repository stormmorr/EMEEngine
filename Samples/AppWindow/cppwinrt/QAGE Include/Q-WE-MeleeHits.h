/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	- Minor Component -Melee Hits System-
		-Header File Classifications-

*/

#ifndef __Q_WE_MeleeHits__
#define __Q_WE_MeleeHits__

#include "Q-NET-ProtoMap.h"

namespace GVARS
{

class Q_MeleeHitCLS
{
public:
	QpoVec3d		Impact;			//Point of impact in world space
	int			Bonenum;		//Number index of the bone hit
	QpoTransform	AttboneXF;		//Matrix of attacking bone
	QpoVec3d		Reaction;		//Vector describing the bone translation required for the actors hit reaction
	QpoVec3d		ReactionNorm;
	float		HitPowerPercent;
	int			AvID;

	float		AttackSTRENGTH;
	float		AttackSNAP;
	
	QpoLight		Light;				//Dynamic Light
	QpoColor		LightColor;			//Color of the light

	Q_Expandro3D	Expandro3D;		//Expandro3D Struct
	int				BloodAmt;		//Amount of blood to spawn
	QpoVec3d			TraVec;			//Trajectory vector
	float			SpikeAMT;

	int			HitTYPE;
	int			HitRESULT;
	int			INIT;
	int			Live;			//MeleeHit Live Switch   0 = OFF / 1 = ON

	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON

	//#### FUNCTION PROTOTYPES
	void ControlServer(void);
	void ControlClient(void);
};


class Q_Global_MeleeHit
{
public:
	Q_MeleeHitCLS MeleeHit[2500];
};

extern QSharedStruct<Q_Global_MeleeHit> Q_MeleeHit;


};//END namespace GVARS

#endif