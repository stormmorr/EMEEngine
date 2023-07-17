/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	- Minor Component -NNbot-
			-Header File Classifications-
*/

#ifndef __Q_AI_NNbot__
#define __Q_AI_NNbot__

namespace GVARS
{

class NNBOTrewardSTATSCLS
{
public:
	float		PlayerHealth;
	//float		PlayerEnergy;
	//float		PlayerArmour;

	float		AvatarHealth[25];
	//float		AvatarEnergy[25];
	//float		AvatarArmour[25];

	int			Items;
	int			AvatarItems[25];

	float		QObjectStrengthBANK[50];

	float		NNBotHealth[200];
	//float		NNBotEnergy[200];

	float		RewardAMT;
};


//*----Target DATA----*
class Q_TargetDATA
{
public:
	int		ID;
	int		Type;
	float	Dist;
};


class Q_NNDecision	//### Decision
{
public:
	float	FactorSTACK[10];
	float	StatusSTACK[50];
	float	Finger;
	float	Toe;
};


	//*----NN Bot Struct----*
class Q_NNBotCLS
{
public:
	int				LIVE;
	QpoVec3d		Pos;
	Q_TargetDATA	TargetDATA[250];
	int				NomTargetDATA;

	Q_NNDecision	Decisions;

	//### STATUS
	float			HB_Health;
	float			HB_Energy;

	int				Class;
	float			Level;
	float			UnusedXP;
	float			Skill[150];

	//### ATTRIBUTES
	float			NNBOT_NoWEP;

	float			NNBOT_TimeScale;
	float			NNBOT_Gravity;
	float			NNBOT_LifeINC;
	float			NNBOT_EnergyINC;

	float			NNBOT_IntBoost;
	float			NNBOT_EnergyEff;
	float			NNBOT_Height;
	float			NNBOT_Weight;
	float			NNBOT_Strength;
	float			NNBOT_Quickness;
	float			NNBOT_Dexterity;
	float			NNBOT_Constitution;
	float			NNBOT_AggPower;
	float			NNBOT_DefPower;
	float			NNBOT_RArmStr;
	float			NNBOT_LArmStr;
	float			NNBOT_RLegStr;
	float			NNBOT_LLegStr;
	float			NNBOT_RArmSnap;
	float			NNBOT_LArmSnap;
	float			NNBOT_RLegSnap;
	float			NNBOT_LLegSnap;
	float			NNBOT_WEPAccuracy;
	float			NNBOT_WEPDrawSPD;
	float			NNBOT_WEPReloadSPD;
	float			NNBOT_WEPRecoilHR;
	float			NNBOT_JINKmovespeed;
	float			NNBOT_JINKpower;
	float			NNBOT_JINK3intensity;

	Q_CLSClericSKILL		CLSClericSKILL[12];

	int			Corona;

	QpoVec3d	ScanVecTo;

	float		Aggression;
	float		Focus;

	QpoVertex	Lvert;			//Structure holding particles position in world space, alpha values and colour
	float		Scale;			//Scale
	int			AvID;
	float		Alpha,AlphaSTR;
	int			R,G,B,IR,IG,IB;
	float		Speed;
	float		SpeedMAX;
	float		TempDist;
	int			AlphaDIR;
	int			AlphaDIR2;
	QpoVec3d	PosSTR;			//Position vector in world space
	float		IncX,IncY,IncZ;	//Trajectory
	QpoVec3d	TraVec;			//Trajectory vector
	QpoVec3d	VecLeft,VecUp;	//Trajectory vector
	QpoVec3d	TempVec1;		//Trajectory vector
	QpoVec3d	Dest;			//Optional- Destination (world space)
	int			SpeedDIR;
	int			AlphaCNT;
	int			AlphaLOCK;
	int			ATTLightON;
	int			ATTCoronaMatt;
	int			ATTCoronaMattDIR;
	int			CoronaMatCntDIR;
	int			CoronaMatCnt;
	int			MATCNT;

	int			LinkON;
	int			LinkTARGET;
	int			LinkALPHADIR;
	float		LinkALPHA;

	QpoVec3d	TrajALTER;

	int			CoronaON;
	int			CoronaALPHADIR;
	float		CoronaALPHA;

	float		RotAMT;
	float		RotAMTSTR;

	QpoVec3d	Vert1,Vert2,Vert3,Vert1STR,Vert2STR,Vert3STR;
	QpoVertex	Lverts[5];

	float		QA_EFF_INTENSITY;

	float			PushOUT;
	float			HeightPos;
	QpoColor		CORLightColor;
	QpoLight		CORLight;
	QpoVertex		ATTCoronaLvert;
	float			CNTR;
	QpoVec3d		OldPos;
	QpoCollision	Collision;
	int				Direction;
	int				Count;			//Optional- Counter for timing
};


/*//####### NNBOT START ########

struct NNBOTrewardSTATS
{
	geFloat		PlayerHealth;
	//geFloat		PlayerEnergy;
	//geFloat		PlayerArmour;

	geFloat		AvatarHealth[25];
	//geFloat		AvatarEnergy[25];
	//geFloat		AvatarArmour[25];

	int			Items;
	int			AvatarItems[25];

	geFloat		QObjectStrengthBANK[50];

	geFloat		NNBotHealth[200];
	//geFloat		NNBotEnergy[200];

	geFloat		RewardAMT;
}
NNBOTrewardSTATS;

//*----Memory Pathway----*
typedef struct MeMPathway
{
	int		InputType;
	int		ControlType;
	int		OutputType;
	int		Active;
	geFloat	TheoryLVL;
	geFloat	InputRange;
	geFloat	TimeTrail;

	int		CodeSTAMP[100];

	geFloat TDimension1;
	geFloat TDimension2;
	geFloat TDimension3;
	geFloat TDimension4;
}
MeMPathway;

MeMPathway Q_MeMPathway[500];


typedef struct Q_NNSpiritANGEL	//### Decision
{
	geFloat		FactorSTACK[10];
	geFloat		StatusSTACK[50];
	geFloat		Finger;
	geFloat		Toe;

	Q_CHARDATA	CharDATA;
	Q_Brains	Q_Brain;

	Q_Decisions Decision;

	geFloat		StationTIMETABLE;
}
Q_NNSpiritANGEL;


//IMP Separate and ID tag All Brains

//LoopBack throught  -> Mem zip
//All relative Code USE CPU Multitask App why? find out if nessesary
//OSI Quirk Code heavy CPU for AI
//Take All Input Data SuperCompute Affects Pipe back

//Code LOD For High Graphics Situations

//Activity Priority Button
//Response Mesh Slider

//ADD link reward

//Link Wear Structure


typedef struct Q_NNDecision	//### Decision
{
	geFloat		FactorSTACK[10];
	geFloat		StatusSTACK[50];
	geFloat		Finger;
	geFloat		Toe;

	Q_NNSpiritANGEL		GoodANGEL;
	Q_NNSpiritANGEL		BadANGEL;

	Q_StationTIMETABLE	StationTIMETABLE;
}
Q_NNDecision;


MeMPathway Q_Assumption[500];


typedef struct AssumptionMATRIX
{
	int			KeyINPUT[NomKEYS];
	geFloat		MouseX;
	geFloat		MouseY;
}
AssumptionMATRIX;


typedef struct Q_NNInput
{
	int			KeyINPUT[NomKEYS];
	int			KeyBUTTON[Nombutton];
	geFloat		MouseX;
	geFloat		MouseY;
}
Q_NNInput;


typedef struct ArrayRECORDER
{
	int MemBITS[NomBITS];

	Record
}
ArrayRECORDER;


typedef struct ArrayRECORDER
{
	int MemBITS[NomBITS];

	Record
}
ArrayRECORDER;


MemoryZIP (with Qattr);


typedef struct Q_State	//### State
{
	geFloat		FactorSTACK[100];
	int			StatusSTACK[100];
	geVec3d		NueronPos;
	int			NueralLinkID[100];
	geVec3d		NueralLinkTYPE[100];
	geBitmap	Map;

	//### Various latched web and compool algorithyms
	Algorithyms	//Use to popularity mesh
	Reverse Tech

	//OPTIONAL
	geBody		VirtualSelf;
	geActor		VirtualAvatar;
	gePath		NueralPath;
	geMotion	NueralMotion;
	geXForm3d	Matrix[100];	//Matrix for general use
}
Q_State;


///*Link scrambler with fuzzy logic and DNA overlays


	//*----NN Bot Struct----*
struct Q_NNBot
{
	int				LIVE;
	geVec3d			Pos;
	Q_TargetDATA	TargetDATA[500];
	int				NomTargetDATA;

	//### INDIVIDUAL NNbot AI State
	Q_State			State[5000][5000][5000][5000];
	int				StateX,StateY,StateZ,StateDELTA;

	Q_NNDecision	Decisions;

	//### STATUS
	geFloat			HB_Health;
	geFloat			HB_Energy;

	int				Class;
	float			Level;
	float			UnusedXP;
	float			Skill[500];

	//### ATTRIBUTES
	float			NNBOT_NoWEP;

	float			NNBOT_TimeScale;
	float			NNBOT_Gravity;
	float			NNBOT_LifeINC;
	float			NNBOT_EnergyINC;

	float			NNBOT_IntBoost;
	float			NNBOT_EnergyEff;
	float			NNBOT_Height;
	float			NNBOT_Weight;
	float			NNBOT_Strength;
	float			NNBOT_Quickness;
	float			NNBOT_Dexterity;
	float			NNBOT_Constitution;
	float			NNBOT_AggPower;
	float			NNBOT_DefPower;
	float			NNBOT_RArmStr;
	float			NNBOT_LArmStr;
	float			NNBOT_RLegStr;
	float			NNBOT_LLegStr;
	float			NNBOT_RArmSnap;
	float			NNBOT_LArmSnap;
	float			NNBOT_RLegSnap;
	float			NNBOT_LLegSnap;
	float			NNBOT_WEPAccuracy;
	float			NNBOT_WEPDrawSPD;
	float			NNBOT_WEPReloadSPD;
	float			NNBOT_WEPRecoilHR;
	float			NNBOT_JINKmovespeed;
	float			NNBOT_JINKpower;
	float			NNBOT_JINK3intensity;

	struct Q_CLSClericSKILL		CLSClericSKILL[12];

	int				Corona;

	geVec3d			ScanVecTo;

	geFloat		Aggression;
	geFloat		Focus;

	GE_LVertex	Lvert;			//Structure holding particles position in world space, alpha values and colour
	geFloat		Scale;			//Scale
	int			AvID;
	geFloat		Alpha,AlphaSTR;
	int			R,G,B,IR,IG,IB;
	geFloat		Speed;
	geFloat		SpeedMAX;
	geFloat		TempDist;
	int			AlphaDIR;
	int			AlphaDIR2;
	geVec3d		PosSTR;			//Position vector in world space
	geFloat		IncX,IncY,IncZ;	//Trajectory
	geVec3d		TraVec;			//Trajectory vector
	geVec3d		VecLeft,VecUp;	//Trajectory vector
	geVec3d		TempVec1;		//Trajectory vector
	geVec3d		Dest;			//Optional- Destination (world space)
	int			SpeedDIR;
	int			AlphaCNT;
	int			AlphaLOCK;
	int			ATTLightON;
	int			ATTCoronaMatt;
	int			ATTCoronaMattDIR;
	int			CoronaMatCntDIR;
	int			CoronaMatCnt;
	int			MATCNT;

	int			LinkON;
	int			LinkTARGET;
	int			LinkALPHADIR;
	geFloat		LinkALPHA;

	geVec3d		TrajALTER;

	int			AvID;

	int			CoronaON;
	int			CoronaALPHADIR;
	geFloat		CoronaALPHA;

	geFloat		RotAMT;
	geFloat		RotAMTSTR;

	geVec3d		Vert1,Vert2,Vert3,Vert1STR,Vert2STR,Vert3STR;
	GE_LVertex	Lverts[5];

	float		QA_EFF_INTENSITY;

	geFloat		PushOUT;
	geFloat		HeightPos;
	GE_RGBA		CORLightColor;
	geLight		*CORLight;
	GE_LVertex	ATTCoronaLvert;
	geFloat		CNTR;
	geVec3d		OldPos;
	GE_Collision Collision;
	int			Direction;
	int			Count;			//Optional- Counter for timing
}
Q_NNBot[500];*/

extern QSharedStruct<NNBOTrewardSTATSCLS> NNBOTrewardSTATS;

class Q_Global_NNBot
{
public:
	Q_NNBotCLS NNBot[500];
};

extern QSharedStruct<Q_Global_NNBot> Q_NNBot;

};//END namespace GVARS

#endif