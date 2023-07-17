/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	- Minor Component -Fighter Brain-
			-Header File Classifications-

*/

#ifndef __Q_AI_Brain__
#define __Q_AI_Brain__

namespace GVARS
{

	//*----Class Structures----*

class Q_CLSCleric			//### Class Structure For 'CLERIC'
{
public:
	int		Ticker;
	int		TickerTIME;
	int		GlanceSW;
	int		GlanceMeM;
	int		GlanceNoM;
	
	int		HealCue[10];
	int		HealCueNoM;
	int		HealTarget;
	int		HSparkInit;
	int		HSparkID[50];
	int		HSparkNOM;
	
	QpoTransform	BoneMatrix;
	QpoVec3d	BoneIn,BoneLeft;
	QpoVec3d	FlameStartPos,FlameEndPos;
	QpoVec3d	EffectPos;

	int		EffChargeTimer;

	int		MatCount;

	int		ShieldOn;
	QpoVec3d	ShieldPos;
	QpoVec3d	ShieldCenter;
	int		ShieldMeshID;
	int		ShieldMeshOn;
};

class Q_Brains
{
public:
	int			MindState;
	int			MindMODE;
	int			LocationState;
	int			VisionCHK;
	int			StateMemory;
	int			idlecnt;

	float		Aggression;
	float		Focus;
	int			FocusON;

	Q_Memory	MeMBank[100];
	int			MeMcount;
	int			MeMcurrent;
	int			MeMLock;

	int			TargetLOCK;
	int			TargetLOCKID;
	int			TargetSIGHT;
	int			TargetSPOTTED;
	int			TargetLOSTtimer;
	int			TargetHIDEtimer;
	int			PERFECTTENtimer;
	int			TargetLOSTcountON;
	int			TargetLOSTcounter;
	int			TargetLOST;
	int			TargetWENTltr;
	int			TargetWENTutd;
	int			TargetFIND;
	int			TargetLEADER;
	int			ATTMmemID;
	int			ATTposON;
	int			ATTinitiated;

	int			TargetLightLOCK;
	int			TargetLightLOST;
	std::vector<int> TargetLightFOUND;

	Q_CLSCleric	CLSCleric;

	int			HeadSearch;
	QpoVec3d		HeadAngles;
	int			HeadDir;

	int			MoveEncount;
	int			MoveSide;

	int			MoveTimeLock;
	int			MoveDirect;
	int			MoveFinger;

	int			PREFinger;

	//### One Chance cancellers
	float		SpecialFinger;
	int			SpecialSTOP;
	int			RunAttSTOP;
	int			ComboCancelSTOP;
	int			DeflectSTOP;
	int			CollDetSTOP;
	int			EnergySTOP;
	int			STOPCNT;
	int			HitSTOPCNT;
	int			CollSTOPCNT;

	//### Mode Control Flags
	int			MODERETURN_H2H;
	bool		WeaponDrawPrime;
	int			WeaponDrawCounter;

	//### Attacking Controls
	int			HoldBack;

	//### Testing Variables
	int			TestKEY1;
	int			TestKEY2;
	int			TestKEY3;
	int			TestKEY1DOWN;
	int			TestKEY2DOWN;
	int			TestKEY3DOWN;

	Q_CRDecide	CRDecide;
	Q_Decision	Decision;
};

};//END namespace GVARS

#endif