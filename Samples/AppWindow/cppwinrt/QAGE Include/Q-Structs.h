//********************************************************
//********************************************************
//**	Q-Structs.h										**
//**	Author	-Max Lawlor								**
//**													**
//**	Definitions of the structures used in			**
//**							Quantum Angel			**
//**							Copyright 2006			**
//********************************************************
//********************************************************

#ifndef QSTRUCTS_H
#define QSTRUCTS_H

//*#include "RakNetTypes.h"

//-------------------------------------------------------------------
// STRUCTURES
//-------------------------------------------------------------------

namespace GVARS
{

//*----Memory Pathway----*
class Q_MeMPathwayCLS
{
public:
	int		InputType;
	int		ControlType;
	int		OutputType;
	int		Active;
	float	TheoryLVL;
	float	InputRange;
	float	TimeTrail;

	float TDimension1;
	float TDimension2;
	float TDimension3;
	float TDimension4;
};

class Q_Particle		//*----Particle System----*
{
public:
	QpoVertex	Lvert;			//Structure holding particles position in world space, alpha values and colour
	int	Type;					//Type of poly.	Normally : QPOLY_TYPE_PNT
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
	QpoVec3d	InitPos,Pos,PosSTR;			//Position vector in world space
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
	QpoColor		ATTLightColor;
	QpoLight		ATTLight;
	QpoVertex		ATTCoronaLvert;
	float			CNTR;
	QpoVec3d		OldPos;
	QpoCollision	Collision;
	int				Direction;
	int				Count;			//Optional- Counter for timing
	int				Live;			//Particle Live Switch   0 = OFF / 1 = ON
};

struct Q_LightningCLS		//*----Particle System----*
{
public:
	QpoVertex	Lvert[500][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int Bitmap;		//Bitmap to texture the particle
	float		Scale;			//Scale
	int			Alpha;
	int			InitStream;		//Initially 0 counts up every time round
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		PosEnd;			//End of Bolt in world space
	QpoVec3d		TraVec;			//Trajectory
	QpoVec3d		VecSTR;
	float		Length;			//Length of bolt
	float		Width;			//Width of bolt
	int			LengNum;
	QpoVec3d		LengthVec;		//Length vector
	QpoVec3d		WidthVec;		//Width vector
	QpoVec3d		Vert1;			//Position of the first vertex
	QpoVec3d		Vert2;			//Position of the second vertex
	QpoVec3d		Vert3;			//Position of the third vertex
	QpoVec3d		Vert4;			//Position of the fourth vertex
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	QpoTransform	Roton;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
};

class Q_Expandro3D
{
public:
	QpoVertex	Lvert[4];			//Structure holding hitflash's position in world space, alpha values and colour
	float		Radius;			//Size of the ring
	float		MaxRadius;		//Maximum size the ring will expand to
	QpoVec3d		Forvec,Leftvec,Upvec;
	QpoVec3d		Vert1;			//Position of the first vertex
	QpoVec3d		Vert2;			//Position of the second vertex
	QpoVec3d		Vert3;			//Position of the third vertex
	QpoVec3d		Vert4;			//Position of the fourth vertex
	QpoVec3d		Pos;
	int			Red,Green,Blue;	//Colour of Ring
	int			MaterialCNT;		//Material reference
	int			Fade;
	int			StartFade;
	int			Init;
	int			Done;
	int			Live;
};

class Q_JinkCorona		//*----Pin Effect Mesh----*
{
public:
	int			EffectType;		//Type of Textured Tri Effect

	QpoVertex	Lvert[30][4];	//Vertices position, alpha values and colour
	int			PolyType;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;			//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	int			MaterialCNT[30];	//Material Counters
	float		ScaleBIT;							//Bitmap Scale
	float		Scale;							//Scale of Whole Effect

	QpoVec3d	VecIn,VecUp,VecLeft;
	QpoVec3d	CamLeft,CamUp,CamIn;
	QpoVec3d	ExpandVec;
	float		LengthDist,ExpandDist;

	QpoVec3d	CentralVert;			//Position in World Space
	QpoVec3d	CameraVert;
	QpoVec3d	CamtoCTRVec;

	QpoVec3d	VertTop[30];			//Position of the Top first vertex
	QpoVec3d	VertCam[30];			//Position of the Bottom fourth vertex
	int			NumTris;

	float			PushBrushCamDist;
	float			PushBrushDist;
	QpoVec3d		BrushVec;
	float			RotateAng;
	QpoTransform	RotateMatrix,CamRotMat,RotMat;

	float		Ut,Ub;
	float		Alpha;			//Effect Alpha Value
	int			AlphaDir;
	float		Red,Green,Blue;	//Effect Colour
	int			Count;			//Optional- Counter for timing
	int			Live;			//Live Switch   0 = OFF / 1 = ON
	int			Init;
};

class Q_Jinks		//*----Jinks----*
{
public:
	QpoVertex	Lvert[24][3];	//Vertices position, alpha values and colour
	int	Type;					//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int Bitmap;		//Bitmap to texture the particle
	float		ScaleBIT;		//Scale
	float		Scale;			//Scale
	float		ScaleSP;		//Scale
	QpoTransform	RoTMatrix;
	QpoTransform	RoTMatrix2;
	QpoVec3d		RMIN;
	QpoTransform	AlignMatrix;
	float		SpinValue,SpinValue2;
	float		SpinValueINC,SpinValueINC2;

	int			matmem1r,matmem1g,matmem1b;
	int			matmem2r,matmem2g,matmem2b;
	QpoTransform	LineStartXF,LineEndXF;
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		PosEnd;			//End of Bolt in world space
	float		Length;			//Length of bolt
	float		Width;			//Width of bolt
	float		LengNum;
	QpoVec3d		LengthVec;		//Length vector
	QpoVec3d		WidthVec;		//Width vector
	QpoVec3d		VertT1;			//Position of the first vertex
	QpoVec3d		VertT2;			//Position of the second vertex
	QpoVec3d		VertT3;			//Position of the third vertex
	QpoVec3d		VertB1;			//Position of the fourth vertex
	QpoVec3d		VertB2;			//Position of the fourth vertex
	QpoVec3d		VertB3;			//Position of the fourth vertex
	QpoVec3d		VertSP1,VertSP2,VertSP3,VertSP4,VertSP5,VertSP6,VertSP7,VertSP8;
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	QpoTransform	Roton;
	float		AlpFade;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	int			AvID;
	int			Init;
	int			ON;

	const char *Limb;
	QpoTransform	LimbMat;

	//Jink Fog
	QpoVec3d		JFogFront,JFogLeft,JFogBack,JFogRight;
	QpoVec3d		JFogIn,JFogPos;
	float		JFogSize,JFogLight,JFogVLight;
	int			JFogExist;
	int			FogON;
	int			FaceWidth,FaceHeight;

	//Jink Light
	QpoLight		Light;
	QpoColor		LightColor;

	Q_Expandro3D	Expandro,Expandro1,Expandro2;
	Q_JinkCorona	JCorona;
};

class Q_EnergyWakeCLS		//*----Limb Flames----*
{
public:
	QpoVertex	Lvert[16][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int Bitmap;		//Bitmap to texture the particle
	float		ScaleBIT;			//Scale
	float		Scale;			//Scale
	float		ScaleSP;			//Scale
	QpoTransform	RoTMatrix;
	QpoVec3d		RMIN;
	QpoTransform	AlignMatrix;

	int			matmem1r,matmem1g,matmem1b;
	int			matmem2r,matmem2g,matmem2b;
	QpoTransform	LineStartXF,LineEndXF;
	QpoVec3d		VecStart,VecEnd;	//Trajectory
	QpoVec3d		VecLeft,VecIn,VecUp,VecSTR;
	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		STRPos;			//Position in World Space
	QpoVec3d		PosEnd;			//End of Bolt in world space
	float		Length;			//Length of bolt
	float		Width;			//Width of bolt
	float		LengNum;
	QpoVec3d		LengthVec;		//Length vector
	QpoVec3d		WidthVec;		//Width vector
	QpoVec3d		VertFNT;			//Position of the first vertex
	QpoVec3d		VertT1;			//Position of the Top first vertex
	QpoVec3d		VertT2;			//Position of the Top second vertex
	QpoVec3d		VertT3;			//Position of the Top third vertex
	QpoVec3d		VertT4;			//Position of the Top fourth vertex
	QpoVec3d		VertT5;			//Position of the Top first vertex
	QpoVec3d		VertT6;			//Position of the Top second vertex
	QpoVec3d		VertT7;			//Position of the Top third vertex
	QpoVec3d		VertT8;			//Position of the Top fourth vertex
	QpoVec3d		VertB1;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB2;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB3;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB4;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB5;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB6;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB7;			//Position of the Bottom fourth vertex
	QpoVec3d		VertB8;			//Position of the Bottom fourth vertex
	
	float		MAINALPHA;
	int			ShiftFlag;
	int			Count;			//Optional- Counter for timing
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
	int			AvID;
	int			Init;
	int			ON;
	int			INIT;

	QpoVec3d		Traj;

	const char *Limb;
	int			MaterialCNT,MaterialCNT2;

	//Jink Fog
	QpoVec3d		JFogFront,JFogLeft,JFogBack,JFogRight;
	QpoVec3d		JFogIn,JFogPos;
	float		JFogSize,JFogLight,JFogVLight;
	int			JFogExist;
	int			FaceWidth,FaceHeight;

	Q_Expandro3D	Expandro;

};

class Q_SEnergys
{
public:
	QpoVec3d	LightPos;
	QpoVec3d	TraVec;		//OPTIMISE - MAY NOT NEED TRAVEC OVER NET
	float		Speed;
	float		Scale;
	int			Alpha;
	int			TargetLock;
	int			TargetID;
	float		AngleX,AngleY,AngleZ;
	int			Live;
};

class Q_LEnergys
{
public:
	QpoVec3d		LightPos;
	QpoVec3d		TraVec;		//OPTIMISE - MAY NOT NEED TRAVEC OVER NET
	float			Speed;
	float			Scale;
	int				Alpha;
	int				EnergyLive,EnergyFire;
	int				Live;
};

class Q_Explosions
{
public:
	int			Live;
	QpoVec3d	Pos;
	float		ExpSize;
	float		LargeEnergyAvID;
	QpoVec3d	CollPlaneNormal;
};

class Q_Backpack		//*----Camera Fade----*
{
public:
	QpoVertex	Lvert[9][4];	//Vertices position, alpha values and colour
	int	Type;			//Type of poly : QPOLY_TYPE_TRI / QPOLY_TYPE_GOR / QPOLY_TYPE_PNT
	Uint32		RenderFlags;	//Render flags : QPOLY_REND_DEPTH_SORT / QPOLY_REND_OCCLUDE_ON
	unsigned int Bitmap;		//Bitmap to texture the particle
	float		Scale;			//Scale
	int			Draw;			//Draw Weapon
	int			Matcount,MatcountDir;	//Material counter
	QpoTransform	PosMatrix;		//Position Matrix

	QpoVec3d		Pos;			//Position in World Space
	QpoVec3d		Forvec,Leftvec,Upvec;
	QpoVec3d		CPos;			//Camera Position in World Space
	QpoVec3d		CForvec,CLeftvec,CUpvec;

	QpoVec3d		Vert1;			//Position of the first vertex
	QpoVec3d		Vert2;			//Position of the second vertex
	QpoVec3d		Vert3;			//Position of the third vertex
	QpoVec3d		Vert4;			//Position of the fourth vertex
	QpoVec3d		BVert1;			//Position of the first vertex
	QpoVec3d		BVert2;			//Position of the second vertex
	QpoVec3d		BVert3;			//Position of the third vertex
	QpoVec3d		BVert4;			//Position of the fourth vertex
	QpoVec3d		CVert1;			//Position of the first vertex
	QpoVec3d		CVert2;			//Position of the second vertex
	QpoVec3d		CVert3;			//Position of the third vertex
	QpoVec3d		CVert4;			//Position of the fourth vertex
	QpoVec3d		Vertex;			//Optional- Destination (world space)
	int			AlpFade;
	int			FadeIO;			//Fade in or out	0 = Fade out / 1 = Fade in
	int			Live;			//Lightning Live Switch   0 = OFF / 1 = ON
};

class Q_NetEffectControlCLS		//*----Effects Control Struct----*
{
public:
	QInt			Live;
	QInt			Active;
	QpoVec3d			Pos;
	float			Effintensity;
	QInt			Type;
	QInt			AvID;
};

class Q_HealEnergyCLS		//*----Heal Energy Attacks----*
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

	int			ChargeTimer;

	QpoVec3d		TargetVec;
	int			HealTarget;

	QpoVec3d		TraVec;			//Trajectory vector
	QpoVec3d		Dest;			//Optional- Destination (world space)
	int			Count;			//Optional- Counter for timing
	int			Live;			//Energy Live Switch   0 = OFF / 1 = ON
};

//----== ENERGY ZONES TECH ==----

class Q_MatrixBlock			//### Class Structure For 'MATRIX BLOCK'
{
public:
	QInt			Active;
	QInt			AVID;

	QpoVec3d			Maxs;
	QpoVec3d			Mins;

	Q_EffectObject	Smoke;

	Q_EffectObject	Effect[5];	//EFFECT MATRIX

	Q_EffectObject	Fog;

	Q_EffectObject	FogLight;

	QpoVec3d			ExpandMINS,ExpandMAXS;
	float			ExpandSTRENGTH;

	QpoVec3d			Core;
	QpoVec3d			MINS2Core;
	QpoVec3d			MAXS2Core;

	float			WallCNT;

	float			ZONEINC_NoWEP;

	float			ZONEINC_TimeScale;
	float			ZONEINC_Gravity;
	float			ZONEINC_LifeINC;
	float			ZONEINC_EnergyINC;

	float			ZONEINC_intBoost;
	float			ZONEINC_EnergyEff;
	float			ZONEINC_Height;
	float			ZONEINC_Weight;
	float			ZONEINC_Strength;
	float			ZONEINC_Quickness;
	float			ZONEINC_Dexterity;
	float			ZONEINC_Constitution;
	float			ZONEINC_AggPower;
	float			ZONEINC_DefPower;
	float			ZONEINC_RArmStr;
	float			ZONEINC_LArmStr;
	float			ZONEINC_RLegStr;
	float			ZONEINC_LLegStr;
	float			ZONEINC_RArmSnap;
	float			ZONEINC_LArmSnap;
	float			ZONEINC_RLegSnap;
	float			ZONEINC_LLegSnap;
	float			ZONEINC_WEPAccuracy;
	float			ZONEINC_WEPDrawSPD;
	float			ZONEINC_WEPReloadSPD;
	float			ZONEINC_WEPRecoilHR;
	float			ZONEINC_JINKmovespeed;
	float			ZONEINC_JINKpower;
	float			ZONEINC_JINK3intensity;
};

//#### ----  CLASS STRUCTURES  ---- ####

class Q_Cleric		//### Class Structure For 'CLERIC'
{
public:
	int		Ticker;
	int		TickerTIME;
	
	QpoTransform	BoneMatrix;
	QpoVec3d	BoneIn,BoneLeft;
	QpoVec3d	FlameStartPos,FlameEndPos;
	QpoVec3d	EffectPos;

	int		HSparkInit;
	int		HSparkID[50];
	int		SpellID[50];
	int		HSparkNOM;

	int		EffChargeTimer;

	int		MatCount;

	int		SpellPNTR;

	int		ShieldOn;
	int		ShieldGROW;
	int		ShieldCNT;
	int		ShieldMATCNT;
	float	ShieldAlpha;
	float	ShieldScale;
	QpoVec3d	ShieldPos;
	QpoVec3d	ShieldCenter;
	int		ShieldMeshID;
	int		ShieldMeshOn;

	unsigned int SBitmap;		//Bitmap to texture the particle
	float		SBitmapRed,SBitmapGreen,SBitmapBlue;
};

class Q_Ninja		//### Class Structure For 'CLERIC'
{
public:
	int		SpeedACT;
};

class Q_EnergyArchitect		//### Class Structure For 'ENERGY ARCHITECT'
{
public:
	int		AffectMatrixON;
	QpoVec3d	CurrentMINS;
	QpoVec3d	CurrentMAXS;
	QpoTransform CurrentPOSMAT;

	int		ZONING;
	int		ZONINGSTR;
	int		WithinZONE;
	int		WithinZONEAVID;
	int		ZoneCHECK;
	int		ZoneACTIVE;

	QpoColor	FogColour;
	QpoColor	FogLightColour;

	Q_EffectObject	Smoke;

	Q_EffectObject	Effect[5];	//EFFECT MATRIX

	Q_EffectObject	Fog;

	Q_EffectObject	FogLight;

	int				FogON;
	int				FogLightON;

	float			ExpandSTRENGTH;

	int				BuildMODEON;

	QpoFog			*Fogobj;
	QpoLight		FogLightobj;

	double			CurrentPOSX;
	double			CurrentPOSY;
	double			CurrentPOSZ;

	double			CurrentDTESTX;
	double			CurrentDTESTY;
	double			CurrentDTESTZ;

	float			ZONEINC_TimeScale;
	float			ZONEINC_Gravity;
	float			ZONEINC_LifeINC;
	float			ZONEINC_EnergyINC;

	float			ZONEINC_intBoost;
	float			ZONEINC_EnergyEff;
	float			ZONEINC_Height;
	float			ZONEINC_Weight;
	float			ZONEINC_Strength;
	float			ZONEINC_Quickness;
	float			ZONEINC_Dexterity;
	float			ZONEINC_Constitution;
	float			ZONEINC_AggPower;
	float			ZONEINC_DefPower;
	float			ZONEINC_RArmStr;
	float			ZONEINC_LArmStr;
	float			ZONEINC_RLegStr;
	float			ZONEINC_LLegStr;
	float			ZONEINC_RArmSnap;
	float			ZONEINC_LArmSnap;
	float			ZONEINC_RLegSnap;
	float			ZONEINC_LLegSnap;
	float			ZONEINC_WEPAccuracy;
	float			ZONEINC_WEPDrawSPD;
	float			ZONEINC_WEPReloadSPD;
	float			ZONEINC_WEPRecoilHR;
	float			ZONEINC_JINKmovespeed;
	float			ZONEINC_JINKpower;
	float			ZONEINC_JINK3intensity;
};

class Q_Soldier		//### Class Structure For 'SOLDIER'
{
public:
	int		JDamageLVL;
	int		JDamageLVLCounter;
	int		JAccuracyLVL;
	int		JAccuracyLVLCounter;
};

//### NET INCREMENT OBJECTS
class Q_NetZoneENTITYCLS
{
public:
	int		TYPE;
	int		ID;
};

//*----Player and AI Entity Data Structures----*

class Q_PlayerEntityCLS
{
public:
	QpoVec3d	Pos;
	QpoVec3d Ang;
};

class Q_AvatarEntityCLS
{
public:
	QpoVec3d Pos;
	QpoVec3d Ang;
	int Team;
	int Type;
	int Role;
	int Rank;
	int	Live;
	int Level;
};

class PossibleTargetData			//### Possible Targets Data
{
public:
	int	AV_ID;
	float Distance;
	int Closest;
	int ClosestID;
	int ClosestAIPID;
	int AIPID;
	int Rank;
	QpoVec3d Position;
	QpoVec3d ScanVecTo;
	float	DistFromLaser;
	QpoVec3d TargetLaserPos;
};

class Q_HealSparks
{
public:
	int			Live;
	int			HTYPE;
	QpoVec3d	Pos;
	QpoVec3d	TraVec;
	int			Released;
	int			Absorbed;
	int			HealTarget;
	float		AlpFade;
	float		ScaleSTR;
};

class Q_ClericSpells
{
public:
	int			Live;
	int			NumSpheres;
	float		Radius[2];
	QpoVec3d	LightPos;
	float		LightPow;
	int			Absorbed;
	int			StartFade[2];
	QpoVec3d	Leftvec[5];
	QpoVec3d	Upvec[5];
	int			HealTarget;
};

class Q_ClericPlasmas
{
public:
	int			Live;
	QpoVec3d	Pos;
	QpoVec3d	TraVec;
	float		Speed;
	float		Alpha;
	int			PartType;
};

class Q_NetEffectControls
{
public:
	int			Live;
	int			Active;
	QpoVec3d	Pos;
	float		Effintensity;
	int			Type;
	int			AvID;
};

class Q_NetZoneINC
{
public:
	int				AVID;

	QpoVec3d		Maxs;
	QpoVec3d		Mins;

	Q_EffectObject	Smoke;

	Q_EffectObject	Effect[5];	//EFFECT MATRIX

	Q_EffectObject	Fog;

	Q_EffectObject	FogLight;

	QpoVec3d			ExpandMINS,ExpandMAXS;
	float			ExpandSTRENGTH;

	float			ZONEINC_TimeScale;
	float			ZONEINC_Gravity;
	float			ZONEINC_LifeINC;
	float			ZONEINC_EnergyINC;

	float			ZONEINC_intBoost;
	float			ZONEINC_EnergyEff;
	float			ZONEINC_Height;
	float			ZONEINC_Weight;
	float			ZONEINC_Strength;
	float			ZONEINC_Quickness;
	float			ZONEINC_Dexterity;
	float			ZONEINC_Constitution;
	float			ZONEINC_AggPower;
	float			ZONEINC_DefPower;
	float			ZONEINC_RArmStr;
	float			ZONEINC_LArmStr;
	float			ZONEINC_RLegStr;
	float			ZONEINC_LLegStr;
	float			ZONEINC_RArmSnap;
	float			ZONEINC_LArmSnap;
	float			ZONEINC_RLegSnap;
	float			ZONEINC_LLegSnap;
	float			ZONEINC_WEPAccuracy;
	float			ZONEINC_WEPDrawSPD;
	float			ZONEINC_WEPReloadSPD;
	float			ZONEINC_WEPRecoilHR;
	float			ZONEINC_JINKmovespeed;
	float			ZONEINC_JINKpower;
	float			ZONEINC_JINK3intensity;
};

class Q_NetZoneENTITYINC
{
public:
	int				TYPE;
	float			ID;
	float			ZoneID;
	float			QObjID;
	QpoVec3d		Pos;
	float			Range;
	float			Scale;
	float			StrengthMAX;
	int				CollisionTYPE;
	int				AvID;
};

class Q_Bullets
{
public:
	QInt		Live;
	QpoVec3d		TrajVec;
	QpoVec3d		WorldPos;
	QpoVec3d		ORIGPos;
	QInt		Speed;
	QInt		AvID;
	float		BulletDMG;
	float		BulletPWR;
	float		ZSpin;
	float		Gravity;
	float AX,AY,AZ;
	float BX,BY,BZ;
	float CX,CY,CZ;
	QpoVec3d Translation;
	QInt		JDamageLVL;
};

class Q_BulletHits
{
public:
	int				Live;
	int				Init;
	int				EffectType;
	int				AvatarHITID;
	int				AvID;

	float			BulletDMG;
	float			BulletPWR;

	QpoVec3d			BulletTraj;
	QpoVec3d			Pos;
	QpoVec3d			CollNormal;
};

//###### Q_Netplayer->Netplayer Melee Hits ######

class Q_MeleeHits
{
public:
	QpoVec3d	Impact;			//Point of impact in world space
	int			Bonenum;		//Number index of the bone hit
	QpoVec3d	ReactionNorm;	
	float		HitPowerPercent;
	int			BloodAmt;		//Amount of blood to spawn

	float		Radius;
	float		MaxRadius;
	float		StartFade;
	float		Red,Green,Blue;

	float		AX,AY,AZ;
	float		BX,BY,BZ;
	float		CX,CY,CZ;
	QpoVec3d	Translation;

	float		AttackSTRENGTH;
	float		AttackSNAP;

	int			HitTYPE;
	int			HitRESULT;
	int			Live;			//MeleeHit Live Switch   0 = OFF / 1 = ON
};

class Q_UPDATE
{
public:
	QpoVec3d			Pos;
	QpoVec3d			Angle;

	QInt			Mposestate;
	QInt			Aposestate;
	QInt			attackon;
	QInt			WeaponStatus;
	QInt			Block;
	QInt			BlockHit;
	QInt			BlockHeight;
	QInt			Crouch;
	float			HitReactScale;
	QpoVec3d		MoveReactVec;
	float			MoveReactSpeed;
	QInt			MFlash;
	float			JINK3_PowerFactor;

	float			HB_Health;
	float			HB_Energy;

	float			idleposecnt;
	float			runposecnt;
	float			attposecnt;
	float			crohposecnt;
	float			jumpposecnt;

	QpoVec3d		WallRunCollNormal;

	QInt			SpecLvlRESET;
	QInt			SNDTRIGEnergy;

	QInt			PlayerMode;

	QInt			AvatarCount;
	QInt			AvID;

	Q_Bullets			Bullets[50];
	Q_BulletHits		BulletHits[50];
	Q_MeleeHits			MeleeHits[50];
	Q_SEnergys			SEnergys[50];
	Q_LEnergys			LEnergys[50];
	Q_Explosions		Explosions[50];
	Q_HealSparks		HealSparks[50];
	Q_ClericSpells		ClericSpells[50];
	Q_ClericPlasmas		ClericPlasmas[50];
	Q_NetEffectControls	NetEffectControls[50];
	Q_NetZoneINC		NetZONEINC[50];
	Q_NetZoneENTITYINC	NetZoneENTITYINC[50];

	int			NomBullet;
	int			NomBulHit;
	int			NomMelHit;
	int			NomSEnergy;
	int			NomLEnergy;
	int			NomExplosions;
	int			NomHSpark;
	int			NomSpell;
	int			NomPlasma;
	int			NomNetEffectControl;
	int			NomNetZonesINC;
	int			NomNetZoneENTITY;
	int			NomQObject;

	float			QObjectStrength;
	QInt			ServerCONTROLID;
	QInt			ReceivedIdFlag;
};

class Q_BodySKILL
{
public:
	float			Height;
	float			Weight;
	float			PhysicalStr;
	float			Quickness;
	float			Dexterity;
	float			Constitution;
	float			AggPower;
	float			DefPower;

	float			STOREAggPower;
	float			STOREDefPower;

	float			POWERBANK;
	float			PBTIMER;
	float			ATTACKPOWER;
	QInt			JINKATT;

	float			Intelligence;
	float			EnergyEff;

	float			RELQuickness;
	float			RELMoveSpeed;
	float			RELRawPower;
	float			RELEnergyEff;

	float			JINKINCmovespeed;
	float			JINKINCpower;
	float			JINKINC3intensity;

	float			LeftArmSTRENGTH,RightArmSTRENGTH;	//1 == Normal	-	10 == Ten Times more damage + 10 times more knockback
	float			LeftLegSTRENGTH,RightLegSTRENGTH;	//1 == Normal	-	10 == Ten Times more damage + 10 times more knockback
	float			LeftArmSNAP,RightArmSNAP;			//1 == Normal	-	10 Times more confusion
	float			LeftLegSNAP,RightLegSNAP;			//1 == Normal	-	10 Times more confusion
};

class Q_WeaponSKILL
{
public:
	float			Accuracy;				//70 == Normal Accuracy	-	700 == Ten Times More Accurate
	float			DrawSPD;				//1 == Normal Speed		-	10 == Ten Times Faster
	float			ReloadSPD;				//1 == Normal Speed		-	10 == Ten Times Faster
	float			RecoilHEIGHTrecover;	//2 == Normal			-   0.2 == recover 100 Times faster
};

class Q_AttackSKILL
{
public:
	float			Power;
	float			Damage;
	float			MoveSpeed;
	float			NumRotate;
	float			ExpRadius;
	float			Accuracy;
};

class Q_CLSClericSKILL
{
public:
	float			Cost;
	float			Potency;
	float			Amount;
	float			Speed;
	float			Duration;
	float			Accuracy;
};

class Q_SpellSLOT
{
public:
	float			QA_EFFECT_TYPE;
	float			QA_EFFECT_INTENSITY;
	QInt			QA_EFFECT_SWITCH;

	QInt			QA_EFFECT_COL00RED;
	QInt			QA_EFFECT_COL00GREEN;
	QInt			QA_EFFECT_COL00BLUE;
	QInt			QA_EFFECT_COL00ALPHA;

	QInt			QA_EFFECT_COL01RED;
	QInt			QA_EFFECT_COL01GREEN;
	QInt			QA_EFFECT_COL01BLUE;
	QInt			QA_EFFECT_COL01ALPHA;

	QInt			QA_EFFECT_COL02RED;
	QInt			QA_EFFECT_COL02GREEN;
	QInt			QA_EFFECT_COL02BLUE;
	QInt			QA_EFFECT_COL02ALPHA;

	QInt			QA_EFFECT_COL03RED;
	QInt			QA_EFFECT_COL03GREEN;
	QInt			QA_EFFECT_COL03BLUE;
	QInt			QA_EFFECT_COL03ALPHA;

	QInt			QA_EFFECT_COL04RED;
	QInt			QA_EFFECT_COL04GREEN;
	QInt			QA_EFFECT_COL04BLUE;
	QInt			QA_EFFECT_COL04ALPHA;

	float			QA_SPELLINC_IntBoost;
	float			QA_SPELLINC_EnergyEff;
	float			QA_SPELLINC_Height;
	float			QA_SPELLINC_Weight;
	float			QA_SPELLINC_Strength;
	float			QA_SPELLINC_Quickness;
	float			QA_SPELLINC_Dexterity;
	float			QA_SPELLINC_Constitution;
	float			QA_SPELLINC_AggPower;
	float			QA_SPELLINC_DefPower;
	float			QA_SPELLINC_RArmStr;
	float			QA_SPELLINC_LArmStr;
	float			QA_SPELLINC_RLegStr;
	float			QA_SPELLINC_LLegStr;
	float			QA_SPELLINC_RArmSnap;
	float			QA_SPELLINC_LArmSnap;
	float			QA_SPELLINC_RLegSnap;
	float			QA_SPELLINC_LLegSnap;
	float			QA_SPELLINC_WEPAccuracy;
	float			QA_SPELLINC_WEPDrawSPD;
	float			QA_SPELLINC_WEPReloadSPD;
	float			QA_SPELLINC_WEPRecoilHR;
	float			QA_SPELLINC_JINKmovespeed;
	float			QA_SPELLINC_JINKpower;
	float			QA_SPELLINC_JINK3intensity;

	QInt				LIVE;
};

class Q_SPELLS
{
public:
	std::string		Name;
	char			TempName[50];

	float			QualityLVL;

	QInt			AttributeID[10];

	float			QA_EFFECT_TYPE;
	float			QA_EFFECT_INTENSITY;
	QInt			QA_EFFECT_SWITCH;

	QInt			QA_EFFECT_COL00RED;
	QInt			QA_EFFECT_COL00GREEN;
	QInt			QA_EFFECT_COL00BLUE;
	QInt			QA_EFFECT_COL00ALPHA;

	QInt			QA_EFFECT_COL01RED;
	QInt			QA_EFFECT_COL01GREEN;
	QInt			QA_EFFECT_COL01BLUE;
	QInt			QA_EFFECT_COL01ALPHA;

	QInt			QA_EFFECT_COL02RED;
	QInt			QA_EFFECT_COL02GREEN;
	QInt			QA_EFFECT_COL02BLUE;
	QInt			QA_EFFECT_COL02ALPHA;

	QInt			QA_EFFECT_COL03RED;
	QInt			QA_EFFECT_COL03GREEN;
	QInt			QA_EFFECT_COL03BLUE;
	QInt			QA_EFFECT_COL03ALPHA;

	QInt			QA_EFFECT_COL04RED;
	QInt			QA_EFFECT_COL04GREEN;
	QInt			QA_EFFECT_COL04BLUE;
	QInt			QA_EFFECT_COL04ALPHA;

	float			QA_SPELLINC_IntBoost;
	float			QA_SPELLINC_EnergyEff;
	float			QA_SPELLINC_Height;
	float			QA_SPELLINC_Weight;
	float			QA_SPELLINC_Strength;
	float			QA_SPELLINC_Quickness;
	float			QA_SPELLINC_Dexterity;
	float			QA_SPELLINC_Constitution;
	float			QA_SPELLINC_AggPower;
	float			QA_SPELLINC_DefPower;
	float			QA_SPELLINC_RArmStr;
	float			QA_SPELLINC_LArmStr;
	float			QA_SPELLINC_RLegStr;
	float			QA_SPELLINC_LLegStr;
	float			QA_SPELLINC_RArmSnap;
	float			QA_SPELLINC_LArmSnap;
	float			QA_SPELLINC_RLegSnap;
	float			QA_SPELLINC_LLegSnap;
	float			QA_SPELLINC_WEPAccuracy;
	float			QA_SPELLINC_WEPDrawSPD;
	float			QA_SPELLINC_WEPReloadSPD;
	float			QA_SPELLINC_WEPRecoilHR;
	float			QA_SPELLINC_JINKmovespeed;
	float			QA_SPELLINC_JINKpower;
	float			QA_SPELLINC_JINK3intensity;
};

class Q_AngelEFF
{
public:
	QInt			TrailTYPE;
	float			TrailRED,TrailGREEN,TrailBLUE,TrailALPHA;			
	QInt			JinkTYPE;
	float			JinkRED,JinkGREEN,JinkBLUE,JinkALPHA;
	QInt			SteamTYPE;
	float			SteamRED,SteamGREEN,SteamBLUE,SteamALPHA;
	QInt			SpikeTYPE;
	float			SpikeRED,SpikeGREEN,SpikeBLUE,SpikeALPHA;
};

class Q_AngelEDIT
{
public:
	float			RED[38];
	float			GREEN[38];
	float			BLUE[38];
	QInt			ANGELEDITFLAG;
};

class Q_CHARDATA
{
public:
	int				Live;
	int				CharID;
	std::string		Name;
	char			Temp[1];
	char			NameTemp[50];

	int				AvatarREF;
	int				ShadowREF;
	std::string		AvatarREFstr;
	std::string		ShadowREFstr;

	int				m_VecID;

	int				State;
	int				ArchiveID;
	QInt			TEAM;
	QInt			Class;
	float			Level;
	float			AvatarSCALE;

	float			UnusedXP;

	QInt			NomITEMS;
	QInt			CurrITEM;
	QInt			NomSpells;
	QInt			CurrSpell;
	QInt			CurrSPELLSELL;

	QInt			CurrWEAPON;
	QInt			CurrHEADARMOUR;
	QInt			CurrUPPERARMOUR;
	QInt			CurrLOWERARMOUR;
	QInt			CurrVEHICLE;
	QInt			CurrMECH;
	QInt			CurrZCAPTURE;
	QInt			CurrZSENTRY;
	QInt			CurrZMINE;
	QInt			CurrZANOMALY;

	QInt			SpellContainerID[5];

	QInt			CDataID;
	QInt			BDataID;

	Q_BodySKILL			BodySKILL;
	Q_WeaponSKILL		WeaponSKILL;
	Q_AttackSKILL		AttackSKILL[30];
	Q_ITEMDATA			ItemDATA[151];
	Q_SpellSLOT			SpellSLOT[10];
	Q_AngelEFF			AngelEFFECTS;
	Q_AngelEDIT			AngelCOLOURS;
	Q_SPELLS			Spells[51];
	Q_CLSClericSKILL	CLSClericSKILL[12];
};

class Q_AVATARS
{
public:
	QInt			LIVE;
	QInt			AVATARID;
	QInt			CDATID;
	unsigned int	BDATID;
	QInt			TEAM;
	QInt			NETAVATAR;
};

class Q_Options
{
public:
	QInt			RadarON;
	QInt			FrameratelimiterON;
	QInt			ClienttimeON;
};

class Q_CharacterDATA
{
public:
	Q_CharacterDATA()
		{
		for(int f_Nt = 0; f_Nt < 35; f_Nt++)
			{
			CharDATA[f_Nt].Live = 0;
			}
		}

	unsigned int	NomCharacters;
	unsigned int	MaxNomCharacters;
	unsigned int	SaveNomCharacters;
	unsigned int	CurrNET;
	int				BDATID;

	//###- Avatar Data - ###//
	QInt			CurrCHAR;
	QInt			CurrSELL;
	Q_CHARDATA		CharDATA[35];
	QInt			NomAvatars;
	QInt			NomNetAvatars;
	QInt			CurrAVATAR;
	Q_AVATARS		AVATARDATA[150];
	unsigned int	NetAvatarID[150];

	//### Game Options - ###//
	Q_Options		GAMEOPTIONS;
	int				GameTypeSelect;
	int				GameMap;
	int				GamePlayersNom;
	int				GameAvatarsMaxAmt;
	//*SystemAddress	GameServerAddress;
	bool			GamePAUSE;
	std::vector<int> vec_PlayersNom;

	//### InterPlay Options ###//
	float m_GameWagerITP;
	int m_GameID_ITP;
	std::string m_UsernameITP;
	std::string m_PasswordITP;
	std::string m_Region;
};

class Q_StartPointsCLS
{
public:
	QpoVec3d			Pos;
	QpoVec3d			Ang;
	int					Team;
	QpoVec3d			ORIGPos;
	float				Push;
	QpoVec3d			TempVec;
	QpoVec3d			VecRight;
};

class Q_ANGELeditMAPCLS
{
public:
	char			MAPNAME[20];
	int				MAPPOINTER;
};

	//*----Vehicle Struct----*
class Q_Vehicle
{
public:
	QpoAvatarFlags Model;	// Vehicles Avatar
	QpoTransform AttachMat;
	QpoVec3d Angles;
	QpoVec3d AnglesSTR;

	//IMPORTANT *********** REMOVE THIS NOW
	QpoVec3d	AttachTempVEC;
	float		AttachTempROTX,AttachTempROTY,AttachTempROTZ;

	int			VaporID;

	QpoSound	SOUNDengineidle;
	QpoSound	SOUNDpowerdown1,SOUNDpowerdown2,SOUNDpowerdown3;

	int	SOUNDFLAGPower;
	int	SOUNDCNTskid;
	int	SOUNDCNTpower;
	int	SOUNDCNTloop;

	float	CollCRUNCH;
	int		RapidDismount;

	int		ZONING;
	int		WithinZONE;
	float	GravityAlter;

	float		MoveReactSpeed;
	QpoVec3d	MoveReactVec;

	//Vectors
	QpoVec3d	Down;

	float	Gear_Power;
	float	Gear_Number;

	//Wheel Bone Matrices
	QpoTransform FWheelMatrix;
	QpoTransform RWheelMatrix;

	QpoVec3d	FWheelPOSSTR;
	QpoVec3d	RWheelPOSSTR;
	QpoVec3d	FWheelNEWPOS;
	QpoVec3d	RWheelNEWPOS;

	QpoTransform RotateMatrix;
	QpoTransform VehicMatrix;
	QpoTransform COGMatrix;

	QpoVec3d	WheelIN,WheelUP,WheelRIGHT;
	QpoVec3d	CenterPOS;

	float		ScanTurnAng;
	QpoVec3d	ForVEC,BackVEC;
	float		ScanDistL,ScanDistR;

	QpoVec3d	ToBASEPNTVEC;
	QpoVec3d	RotatePNTVEC;

	QpoVec3d	CENTRALANGLEVEC;
	QpoVec3d	OLDCENTRALANGLEVEC;
	QpoVec3d	CURRENTWHEELPERFECT;

	QpoVec3d	NEWVehicleUP,NEWVehicleIN,NEWVehicleLEFT;
	QpoVec3d	OLDVehicleIN,OLDVehicleUP;
	QpoVec3d	STRVehicleUP;
	QpoVec3d	VehicleIMAGETORUDDERVEC;
	QpoVec3d	VehicleIMAGETORUDDERVECSTR;
	QpoVec3d	VehicleRUDDERINC;

	float	ANGLELENGTH;

	QpoVec3d	CalcLINEP1,CalcLINEP2,CalcLINEP3,CalcLINEP4,CalcRESA,CalcRESB;
	float		TrigDISTO,TrigDISTH,NewROTINC;

	float	JDISTF,JDISTR;

	int		JINKrush;

	//Motion Counters
	float	FWheelSpinPoseCnt;
	float	RWheelSpinPoseCnt;
	QpoVec3d	FWheelFORCEVEC;
	QpoVec3d	RWheelFORCEVEC;
	QpoVec3d	FWheelPERFECTPOS;
	QpoVec3d	RWheelPERFECTPOS;
	QpoVec3d	FWheelOLDPERFECTPOS;
	QpoVec3d	RWheelOLDPERFECTPOS;
	QpoVec3d	FWheelCURRENTPERFECTPOS;
	QpoVec3d	RWheelCURRENTPERFECTPOS;
	QpoVec3d	FWheelTESET;
	QpoVec3d	RWheelTESET;
	float Phys_FWheelBendPoseCnt;
	float Phys_RWheelBendPoseCnt;
	float STR_Phys_FWheelBendPoseCnt;
	float STR_Phys_RWheelBendPoseCnt;
	float Phys_FWheelTurnPoseCnt;
	float FWheelCompressionDIST;
	float RWheelCompressionDIST;

	//Physics Control Elements
	float Phys_Velocity;
	float Phys_TurnMotionAMT;
	float Phys_Power;
	float Phys_Brake;
	float Phys_Turn;
	float Phys_TurnLean;
	float Phys_TurnLeanSTR;
	float Phys_TurnMULT;
	float Phys_FSpringStrength;
	float Phys_RSpringStrength;
	float Phys_FSpinLift;
	float Phys_RSpinLift;
	float Phys_VerticalRotate;

	float Phys_FrictionAMT;
	float Phys_FrictionSTR;

	QpoVec3d Phys_ForceDirection;
	QpoVec3d Phys_ActualForceDirection;
	QpoVec3d Phys_ForwardMotionVec;
	QpoVec3d Phys_TurnMotionVec;
	float Phys_ForceDirectionLength;
	float Phys_ForceFactor;
	float Phys_DistF;
	float Phys_DistR;
	float	Phys_FWeightDistFactor;
	float	Phys_RWeightDistFactor;

	//Vehicle Constants
	float	Const_SpinCancel;
	float	Const_SpringLift;
	float	Const_SpringPower;
	float Const_Weight;
	float	Const_FWeight;
	float	Const_RWeight;
	float	Const_WheelSettleSpin;
	float	Const_WheelSettleDVel;
	float	Const_SpringLimit;
	float	Const_DownVelCancel;
	float	Const_ForceFactor;
	float	Const_SpringAbsorbVel;
	float	Const_SpringAbsorbSpin;
	float Const_LightTouchFactor;
	float	Const_MaxSpeed;

	float	Const_MiddleCOGDISTX;
	float	Const_MiddleCOGDISTY;
	float	Const_MiddleCOGDISTZ;
	float	Const_SpringCrunchMAX;
	float	Const_SpringCompDist;

	float	Temp_Rotation;
	//LATEST^^^^^^

	QpoVec3d	ConstVec_FCrunch;
	QpoVec3d	ConstVec_RCrunch;

	float	Const_FRICMinSlide;

		//Gravity
	float Phys_DownVelocity;		
	float Phys_RDownForce;
	float Phys_RWheelBend;
	int		Phys_RWheelTOUCH;
	float Phys_FDownForce;
	float Phys_FWheelBend;
	int		Phys_FWheelTOUCH;
	float Phys_WheelieLIFT;

	int			Phys_PlaneLock;
	int			Phys_PlaneLSituation;
	QpoPlane	Phys_Plane;
	bool	Phys_Planebool;

	//## Collision
	QpoCollision	Collision;
	QpoCollision	FCollision;
	QpoCollision	RCollision;
	QpoCollision	ACollision;

	//### Init Head Lights
	int				HeadLightInit;
	QpoLight		HeadLight,HeadLightEnd,NeonLight1;
	QpoTransform	HeadLMat;
	QpoVec3d		HeadLPos,HeadLENDPos;
	QpoColor		HeadLColor;
	float			HeadLPower;
	QpoVec3d		NeonLPos1;
	QpoColor		NeonLColor1;
	float			NeonLPower1;
	QpoCollision	HeadLCollision;

	float DownSpeed;
	int	Drop;
};

	//*----MECH Struct----*

class Q_Mech
{
public:
	QpoAvatarFlags Model;	// Mech's Avatar
	QpoAvatarFlags ModelSTR;
	QpoAvatarFlags Shadows[4];
	QpoAvatarFlags ShadowsSTR[4];
	QpoVec3d Angles;
	int	ACTIVE;
};

	//*----Texture Structures----*

class LoadTextureSTATS
{
public:
	const char * FileName;
	char		 Name[20];
	int			 TextureID;

};

static struct
{
	bool verbose;
	bool dither;
	bool paletted;
	bool truecolor;
	int scaleX, scaleY;
	int displayW, displayH;
	int mipmap;
	bool transp;
	bool applykey;
	int outputmode;
	float hmscale;
	bool info;
	bool stripalpha;
	bool addalpha;
	int sharpen;
	bool mipmaps;
} TToption = {false,false,false,false,0,0,79,24,-1,false,false,0,1/500.0f,false,false,false,0,false};

	//*----Mouse and Keyboard Control Structures----*

class Q_Mouse
{
public:
	QInt		NORLeftButton;
	QInt		SYSLeftButton;

	QInt		NORMiddButton;
	QInt		SYSMiddButton;

	QInt		NORRightButton;
	QInt		SYSRightButton;

	QInt		NORMouseWheel;
};

class Q_ClickLog
{
public:
	QInt			KL_BTFSpecLevel;
	QInt			KL_LTFSpecLevel;
	QInt			KL_RTFSpecLevel;
	QInt			KL_FTLSpecLevel;
	QInt			KL_FTRSpecLevel;
};

class Q_Key
{
public:
	QInt			NORkeyW;
	QInt			NORkeyS;
	QInt			NORkeyA;
	QInt			NORkeyD;

	QInt			NORkeyTAB;
	QInt			NORkeySHIFT;
	QInt			NORkeySPACE;

	QInt			NORkeyZ;
	QInt			NORkeyQ;
	QInt			NORkeyE;
	QInt			NORkeyF;
	QInt			NORkeyR;

	QInt			NORkeyH;
};

class Q_ControlSET
{
public:
	Q_Mouse		Mouse;
	Q_Key		Key;
	QpoVec3d		AvatarAngle;
	QpoVec3d		AnglesVec;
	QpoVec3d		ViewVec;
	QInt		EnergyTARGET;
	Q_ClickLog	CLog;
};

class Q_NetplayerCLS
{
public:
	QInt			LocalCONTROLID;
	int				ID;
	QInt			FRLswitch;
	int				Spawned;
	int				SpawnREADY;
	QInt			UpdateCHAR;
	Q_ItemRef		NewITEMREF;
	int				Activated;
	Q_ControlSET	ControlSET;
	Q_CHARDATA		CharDATA;
	int				Live;
};


class Q_Global_MeMPathway
{
public:
	Q_MeMPathwayCLS MeMPathway[350];
};

extern QSharedStruct<Q_Global_MeMPathway> Q_MeMPathway;

class Q_Global_Lightning
{
public:
	Q_LightningCLS Lightning[75];
};

extern QSharedStruct<Q_Global_Lightning> Q_Lightning;

class Q_Global_EnergyWake
{
public:
	Q_EnergyWakeCLS EnergyWake[150];
};

extern QSharedStruct<Q_Global_EnergyWake> Q_EnergyWake;

class Q_Global_NetEffectControl
{
public:
	Q_NetEffectControlCLS NetEffectControl[10];
};

extern QSharedStruct<Q_Global_NetEffectControl> Q_NetEffectControl;

class Q_Global_HealEnergy
{
public:
	Q_HealEnergyCLS HealEnergy[50];
};

extern QSharedStruct<Q_Global_HealEnergy> Q_HealEnergy;

class Q_Global_NetZoneENTITY
{
public:
	Q_NetZoneENTITYCLS NetZoneENTITY[75];
};

extern QSharedStruct<Q_Global_NetZoneENTITY> Q_NetZoneENTITY;

class Q_Global_StartPoints
{
public:
	Q_StartPointsCLS StartPoints[50];
};

extern QSharedStruct<Q_Global_StartPoints> Q_StartPoints;

class Q_Global_ANGELeditMAP
{
public:
	Q_ANGELeditMAPCLS ANGELeditMAP[35];
};

extern QSharedStruct<Q_Global_ANGELeditMAP> Q_ANGELeditMAP;

class Q_Global_AvatarEntity
{
public:
	Q_AvatarEntityCLS AvatarEntity[50];
};

extern QSharedStruct<Q_Global_AvatarEntity> Q_AvatarEntity;

class Q_Global_Netplayer
{
public:
	Q_NetplayerCLS Netplayer[7];
};

extern QSharedStruct<Q_Global_Netplayer> Q_Netplayer;

class Q_Global_PlayerEntity
{
public:
	Q_PlayerEntityCLS PlayerEntity;
};

extern QSharedStruct<Q_Global_PlayerEntity> Q_PlayerEntity;


};

//-------------------------------------------------------------------
// STRUCTURES DEFINITIONS  /END
//-------------------------------------------------------------------

#pragma message ("###  Defining Quantum Structures  [Q-Structs.h]")

#endif