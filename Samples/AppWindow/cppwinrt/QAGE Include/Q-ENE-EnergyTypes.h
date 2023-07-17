/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	- Minor Component -Avatar When In Human Form-
		-Header File Classifications-
*/

#ifndef __Q_ENE_EnergyTypes__
#define __Q_ENE_EnergyTypes__

#include "Q-NET-ProtoMap.h"

namespace GVARS
{

class Q_SEnergyCLS		//*----Small Energy Attacks----*
{
public:
	QpoInstanceFlags	AvatarFlag[5];	//Actors used to show the energy
	int				NomActors;		//Number of Actors used

	int			AvID;
	
	float		Scale,ScaleInc,ScaleMax;				//Scale of the actors
	int			ScaleMode;
	int			Alpha,AlphaInc;							//Alpha value of the actors
	float		AlphaScale[5];							//Alpha Scale
	float		Speed,SpeedInc,SpeedScale[5],SpeedMax;	//Speed of the energy
	float		Accuracy;

	int			DisplayAlpha;
	int			DisplayColor;
	float		DisplayScale;

	float		RandomInput;

	QpoSound	Sound;

	int	TargetLock;
	int	TargetID;
	QpoVec3d	TargetVec;

	QpoLight		Light;						//Dynamic Light
	QpoVec3d		LightPos;					//Position of the light and the energy in world space
	QpoVec3d		LOldPos;					//Old position
	QpoColor		LightColor;					//Color of the light

	QpoTransform	Matrix,Matrix2,Matrix3;
	int			Init;
	float		Dist;

	float		AngleX,AngleY,AngleZ;

	int			ShotSpin;

	QpoVec3d		Left,Up,In;
	QpoVec3d		Up2,Right,RDown;
	QpoVec3d		HeadLeft;
	QpoVec3d		LeftVec,UpVec,ForVec;

	QpoVec3d		TargetVecSTR;
	QpoVec3d		ScanTurnVec;

	float		ScanTurnAngLR,ScanTurnAngUD;
	float		ScanDistLeft,ScanDistRight,ScanDistUp,ScanDistDown;

	float		AngYIncFactor,AngXIncFactor;

	//### Constants Passed Thru
	float		Const_TurnDull,Const_AngleInc;

	//Anti Multiple Hits System
	int			AntiMultHits[251];

	float		TrajDIST;

	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		CURRTraVec;			//Trajectory vector
	int			Live;			//Energy Live Switch   0 = OFF / 1 = ON
	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON
};


class Q_LEnergyCLS		//*----Large Energy Attacks----*
{
public:
	int			Team;
	int			HoldBack;
	QpoLight		Light;
	QpoVec3d		OldLightPos,NewLightPos;
	QpoVec3d		LightPos;
	QpoColor		Lightcolor;
	unsigned int	Bitmap;		//Bitmap to texture the particle

	int			BmpCount;
	int			BmpCountSP;
	float		BitmapRed,BitmapGreen,BitmapBlue;

	int			Power;
	float		Scale;
	int			ScaleGrow;
	QpoVec3d		TraVec;
	int			Speed;
	float		ScaleInc;
	float		SaveScale;
	int			EnergyLive;
	int			EnergyFire;
	int			Alpha;
	float		ScaleXSquash;
	float		ScaleYSquash;
	float		ScaleZSquash;
	int			ScaleXDir,ScaleYDir,ScaleZDir;
	float		EnergyRAD;
	float		EnergyDMG;

	QpoVec3d		CoronaVECIN,CoronaVECUP,CoronaVECLEFT;
	QpoVertex	CoronaLV[4];
	float		CoronaLENGTH;
	QpoTransform	CoronaMATRIX;
	QpoVec3d		CoronaVERT1,CoronaVERT2,CoronaVERT3,CoronaVERT4;
	QpoVec3d		CoronaMATV1,CoronaMATV2,CoronaMATV3,CoronaMATV4;
	QpoVec3d		CoronaMATVECIN;
	int			CoronaMATCNT;

	QpoInstanceFlags EnergyBall;

	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	int			AvID;
	int			Init;
	int			ON;

	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON

	QpoCollision	Collision;
	int				CollideFG;
};


class Q_ExplosionCLS		//*----Explosion----*
{
public:
	int			Bonenum;		//Number index of the bone hit
	int			Attbone;
	QpoTransform	AttboneXF;
	QpoVec3d		Reaction;		//Vector describing the bone translation required for the actors hit reaction

	QpoVec3d		CollPlaneNormal;

	int				BmpCountSP;
	int				BmpCount;

	Q_HitFlash		HitFlash;		//HitFlash Struct
	Q_Expandro		Expandro;		//Expandro Struct
	//Q_Particle	Blood[100];		//Blood Struct
	int				BloodAmt;		//Amount of blood to spawn
	int				NumBlood;
	QpoVec3d		TraVec;			//Trajectory vector
	float			Length;
	QpoLight		Light;						//Dynamic Light
	QpoColor		LightColor;					//Color of the light
	int				LightPower;
	float			ExpSize;
	float			ExpDMG;
	int				DamageInit;
	int				Team;
	int				LargeEnergyAvID;
	int				AvID;

	QpoVertex	Lvert[24][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int	Bitmap;		//Bitmap to texture the particle
	float		ScaleBIT;			//Scale
	float		Scale;			//Scale
	float		AirShkScale;
	float		GrndShkScale;
	int			AirShkAlpha;
	int			GrndShkAlpha;
	int			BlastAlpha;
	float		ScaleSP;			//Scale
	QpoTransform	RoTMatrix;
	QpoVec3d		RMIN;
	QpoTransform	AlignMatrix;
	QpoVec3d		AligIn;
	float		AngleJP;
	int			AirShkMat;
	int			BlastMat;
	QpoVec3d		CloudPos[10];
	int			CloudAlpha[10];
	float		CloudScale[10];
	QpoVertex	CloudLVert[10];
	QpoVec3d		CloudTraVec[10];
	float		CloudSpeed[10];
	int			CloudInit;			//Initialisation flag 1 at start 0 after one pass
	int			CloudLive[10];
	
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		VertFU1;			//Position of the first vertex
	QpoVec3d		VertFU2;			//Position of the second vertex
	QpoVec3d		VertFU3;			//Position of the third vertex
	QpoVec3d		VertFU4;			//Position of the third vertex
	QpoVec3d		VertFD1;			//Position of the fourth vertex
	QpoVec3d		VertFD2;			//Position of the fourth vertex
	QpoVec3d		VertFD3;			//Position of the fourth vertex
	QpoVec3d		VertFD4;			//Position of the fourth vertex
	QpoVec3d		VertS1;				//Position of the fourth vertex
	QpoVec3d		VertS2;				//Position of the fourth vertex
	QpoVec3d		VertS3;				//Position of the fourth vertex
	QpoVec3d		VertS4;				//Position of the fourth vertex
	QpoVec3d		VertSP1,VertSP2,VertSP3,VertSP4,VertSP5,VertSP6,VertSP7,VertSP8;
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	QpoTransform	Roton;
	float		AlpFade;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing
	int			Init;			//Initialisation flag 1 at start 0 after one pass
	int			BlastLive;
	int			AirShkLive;
	int			GrndShkLive;
	int			Live;			//MeleeHit Live Switch   0 = OFF / 1 = ON
	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON
};


class Q_ClericPlasmaCLS		//*----Cleric Energy Spells----*
{
public:
	QpoVertex	Lvert;			//Structure holding particles position in world space, alpha values and colour
	int	Type;			//Type of poly.	Normally : QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	float		Scale;			//Scale
	int			PartType;		//Particle Type
	int			AvID;
	float		Alpha,Alpha2,AlphaSTR;
	int			R,G,B,IR,IG,IB;
	float		Speed;
	float		SpeedMAX;
	float		TempDist;
	int			AlphaDIR;
	int			AlphaDIR2;
	QpoVec3d		InitPos,Pos,PosSTR;			//Position vector in world space
	float		IncX,IncY,IncZ;	//Trajectory
	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		VecLeft,VecUp;	//Trajectory vector
	QpoVec3d		TempVec1;		//Trajectory vector
	QpoVec3d		Dest;			//Optional- Destination (world space)
	int			SpeedDIR;
	int			AlphaCNT;
	int			AlphaLOCK;
	int			ATTCoronaMatt;
	int			ATTCoronaMattDIR;
	int			CoronaMatCntDIR;
	int			CoronaMatCnt;
	float		RoTAMT;

	int			LinkON;
	int			LinkTARGET;
	int			LinkALPHADIR;
	float		LinkALPHA;

	int			HealTarget;
	float		LightPow;
	int			LightON;

	int			CoronaON;
	int			CoronaALPHADIR;
	float		CoronaALPHA;
	float		TIMER;

	float		PushOUT;
	float		HeightPos;
	QpoColor	LightColor;
	QpoLight	Light;
	QpoVertex	ATTCoronaLvert;
	float		CNTR;
	QpoVec3d	OldPos;
	QpoCollision Collision;
	int			Direction;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Particle Live Switch   0 = OFF / 1 = ON
	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON
};


class Q_ClericSpellCLS		//*----Cleric Energy Spells----*
{
public:
	int				Type;			//Type of energy Heal
	QpoVec3d			Pos;			//Type 0:	Cleric Heal
	QpoVec3d			StartPos,EndPos;
	
	QpoTransform	BoneMatrix;
	QpoVec3d		BoneIn,BoneLeft;
	float		Scale,ScaleInc,ScaleMax;				//Scale of the actors
	int			Alpha,AlphaInc;							//Alpha value of the actors
	float		AlphaScale[5];							//Alpha Scale
	float		Speed,SpeedInc,SpeedScale[5],SpeedMax;	//Speed of the energy
	int			MatCount;
	int			TimerCNT;

	int			LightInit;
	QpoLight	Light;						//Dynamic Light
	int			LightPow,LightInc,LightMax;	//Power of the dynamic light
	QpoVec3d	LightPos;					//Position of the light and the energy in world space
	QpoVec3d	LOldPos;					//Old position
	QpoColor	LightColor;					//Color of the light
	float		LightSpeed;
	int			HSparkInit;

	float		AvatarLightR,AvatarLightG,AvatarLightB;
	float		AvatarINCR,AvatarINCG,AvatarINCB;
	float		LightRedFULL,LightGreenFULL,LightBlueFULL;

	int			Released;
	int			Absorbed;

	Q_Expandro3D	Sphere[10];
	QpoTransform	SphereMatrix;
	int			NumSpheres;

	int			ChargeTimer;

	QpoVec3d		TargetVec;
	int			HealTarget;
	int			AvID;
	int			LightON;

	QpoVec3d		Upvec,Leftvec;
	float		Radius;
	float		StartFade;

	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		Dest;			//Optional- Destination (world space)
	int			Count;			//Optional- Counter for timing
	int			Live;			//Energy Live Switch   0 = OFF / 1 = ON
	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON
};


class Q_SEnergyCLSnew		//*----Small Energy Attacks----*
{
public:
	QpoAvatarFlags	ActorFlag;	//Actors used to show the energy
	int				NomActors;		//Number of Actors used

	int			AvID;
	
	float		Scale,ScaleInc,ScaleMax;				//Scale of the actors
	int			ScaleMode;
	int			Alpha,AlphaInc;							//Alpha value of the actors
	float		AlphaScale[5];							//Alpha Scale
	float		Speed,SpeedInc,SpeedScale[5],SpeedMax;	//Speed of the energy
	float		Accuracy;

	int			DisplayAlpha;
	int			DisplayColor;
	float		DisplayScale;

	float		RandomInput;

	QpoSound	Sound;

	int	TargetLock;
	int	TargetID;
	QpoVec3d	TargetVec;

	QpoLight		Light;						//Dynamic Light
	QpoVec3d		LightPos;					//Position of the light and the energy in world space
	QpoVec3d		LOldPos;					//Old position
	QpoColor		LightColor;					//Color of the light

	QpoTransform	Matrix,Matrix2,Matrix3;
	int			Init;
	float		Dist;

	float		AngleX,AngleY,AngleZ;

	int			ShotSpin;

	QpoVec3d		Left,Up,In;
	QpoVec3d		Up2,Right,RDown;
	QpoVec3d		HeadLeft;
	QpoVec3d		LeftVec,UpVec,ForVec;

	QpoVec3d		TargetVecSTR;
	QpoVec3d		ScanTurnVec;

	float		ScanTurnAngLR,ScanTurnAngUD;
	float		ScanDistLeft,ScanDistRight,ScanDistUp,ScanDistDown;

	float		AngYIncFactor,AngXIncFactor;

	//### Constants Passed Thru
	float		Const_TurnDull,Const_AngleInc;

	//Anti Multiple Hits System
	int			AntiMultHits[251];

	float		TrajDIST;

	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		CURRTraVec;			//Trajectory vector
	int			Live;			//Energy Live Switch   0 = OFF / 1 = ON
	int			NetFlag;		//Network Spawn Switch   0 = OFF / 1 = ON
};

class Q_Global_SEnergy
{
public:
	Q_SEnergyCLS SEnergy[QAA_NET_ARRAY_MAX];
};

extern QSharedStruct<Q_Global_SEnergy> Q_SEnergy;

class Q_Global_PowerBlade
{
public:
	Q_SEnergyCLS PowerBlade[50];
};

extern QSharedStruct<Q_Global_PowerBlade> Q_PowerBlade;

class Q_Global_LEnergy
{
public:
	Q_LEnergyCLS LEnergy[QAA_NET_ARRAY_MAX];
};

extern QSharedStruct<Q_Global_LEnergy> Q_LEnergy;

class Q_Global_Explosion
{
public:
	Q_ExplosionCLS Explosion[QAA_NET_ARRAY_MAX];
};

extern QSharedStruct<Q_Global_Explosion> Q_Explosion;

class Q_Global_ClericPlasma
{
public:
	Q_ClericPlasmaCLS ClericPlasma[500];
};

extern QSharedStruct<Q_Global_ClericPlasma> Q_ClericPlasma;

class Q_Global_ClericSpell
{
public:
	Q_ClericSpellCLS ClericSpell[500];
};

extern QSharedStruct<Q_Global_ClericSpell> Q_ClericSpell;

};//END namespace GVARS

#endif