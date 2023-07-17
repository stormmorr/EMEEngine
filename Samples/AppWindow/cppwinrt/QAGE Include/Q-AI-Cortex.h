/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	- Minor Component -Brain Functions-
			-Header File Classifications-

*/

#ifndef __Q_AI_Cortex__
#define __Q_AI_Cortex__

namespace GVARS
{

class Q_MeMDataEnemy	//### Data collected  about one Avatar
{
public:
	int		Visible;
	int		AV_ID;
	int		Team;
	int		Rank;
	int		MeMMindstate;
	int		Aposestate;
	int		Mposestate;
	int		attposecnt;
	int		attackon;
	int		WeaponStatus;
	int		Blocking;
	int		HitReaction;
	int		BlowHeight;
	int		HitLethal;
	int		BlockHit;

	QpoVec3d	Pos;
	QpoVec3d	Ang;
	QpoVec3d	VecTo;
	float ScanTurnAng;
	float ScanDist;

	float PowerLevel;
	int		Health;
	int		Power;
	int		Weapon;
};


class Q_CRDecide	//### Crunch Decision
{
public:
	int		F_RunA;
	int		F_Comm;
	int		F_Obtain;
	int		F_Power;
	int		F_LongR;
	int		F_Energy;
	int		F_Hand2H;
	int		F_AttPlan;
	int		F_Delay;
	int		F_GoCrazy;

	int		FactorSUM;
	int		Answer;
	int		Finger;

	int		Timer;
};


class Q_Decision	//### Data collected about one Avatar
{
public:
	int		ON;

	int		DelaySwitch;
	int		DelayTimeLock;
	int		DelayOn;

	int		F_Delay;
	int		F_Alpha;
	int		F_Beta;
	int		F_Gamma;
	int		F_Delta;
	int		F_Omega;
	
	int		NOM_Attack;
	int		NOM_Combo;
	int		NOM_Special;
	int		NOM_Move;

	int		SUM_Attack;
	int		SUM_Combo;
	int		SUM_Special;
	int		SUM_Move;

	int		INC_Search;

	int		F_Attack[100];
	int		F_Combo[100];
	int		F_Special[100];
	int		F_Move[100];

	int		FactorSUM;
	int		Answer;
	int		Finger;

	int		DecOverride;
	int		FingerOverride;
	int		FingerOverrideAnswer;

	int		OverrideTIMER;
};


class Q_Memory			//### Single Memory
{
public:
	int				Time;
	int				EventType;
	Q_MeMDataEnemy	AIsPresent[255];
	int				MeMLockID;
	int				MeMLockLeaderID;
	int				NomAIPresent;

		//Own Data
	int		MeMMindstate;
	int		TargetLOCKID;
	QpoVec3d	Pos;
	QpoVec3d	Angles;
	float PowerLevel;
	int		Health;
	int		Energy;
	int		Power;
	int		Weapon;
	int		TargetLOST;
	int		TargetWENTltr;
	int		TargetWENTutd;
};

};//END namespace GVARS

#endif