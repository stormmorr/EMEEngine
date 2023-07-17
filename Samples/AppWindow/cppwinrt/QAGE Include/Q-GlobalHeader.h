/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

		Header File Classifications
				Global Definitions

*/

#ifndef GLOBALHEADER_H
#define GLOBALHEADER_H

//--------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------

// SERVER EDIT
#if defined(WIN32)
//#include "windows.h"

#else
class pMesh;
typedef struct POINT
{
    long  x;
    long  y;
} POINT;
#endif

#ifndef QAGE_POINT
#include "../UnSRC/Utility/QSharedStruct.h"
#else
#include "../UnSRC/Utility/QSharedStruct-Point.h"
#endif

#include "Q-KeyDefinitions.h"

//--------------------------------------------------------------------
// DEFINES
//--------------------------------------------------------------------

namespace GVARS
{

#define PLAYER_HEIGHT  120.0f   // 140.0f
#define PLAYER_SPEED 7.5f // 3.25f // 2.3f // 4.0f // 10.0f // 3.0f // 6.0f

// Theses are used to make actors stand up
#define RAD (PI * 2.0f)
#define RAD34 (RAD * 0.75f)
#define RAD12 (RAD * 0.5f)
#define RAD14 (RAD * 0.25f)

#define ORTHONORMAL_TOLERANCE ((float)(0.001f))
#define ORTHOGONAL_TOLERANCE ((float)(0.001f))

//---------------------------------------------------------------------------

#define DllImport  __declspec( dllimport )
#define DllExport  __declspec( dllexport )

// Movement Defines
#define fab(a) (a > 0 ? a : -a)

#define Q_ABS(x)				( (x) < 0 ? (-(x)) : (x) )
#define Q_CLAMP(x,lo,hi)		( (x) < (lo) ? (lo) : ( (x) > (hi) ? (hi) : (x) ) )
#define Q_CLAMP8(x)			    Q_CLAMP(x,0,255)
#define Q_CLAMP16(x)			Q_CLAMP(x,0,65536)
#define Q_boolSAME(x,y)		    ( ( (x) && (y) ) || ( !(x) && !(y) ) )

#define Q_EPSILON				((float)0.000797f)
#define Q_FLOATS_EQUAL(x,y)	    ( Q_ABS((x) - (y)) < Q_EPSILON )
#define Q_FLOAT_ISZERO(x)		Q_FLOATS_EQUAL(x,0.0f)

#define	Q_PI					((float)3.14159265358979323846f)

inline float radToDeg(float a) { return (float)57.29577951308232286465 * a; };
inline float degToRad(float a) { return (float)a / (float)57.29577951308232286465; };

///////////////////////////
////// QAGE SETTINGS //////

#if 1
	#define QAGE_DEBUG
#endif

#if 0
	#define QAGE_MAIN
#endif

#if 0
	#define QAGEMODE_NOEFFECTS
#endif

#if 0
	#define QAGEMODE_NOLOGO
#endif

#if 0
	#define QAGEMODE_NOINTRO
#endif

  ////////////////////////////
 ////////  QAGE MOD  ////////

#if 0
	#define QAMOD_ORIG		//QAGE ORIGINAL
#endif

#if 1
	#define QAMOD_ARENA		//QAGE MODIFICATION "Quantum Angel Arena" or simply "Arena"
#endif

//-------------------------------------------------------------------
// QAGE DEFINITIONS
//-------------------------------------------------------------------

//#####==-- AVATAR MESH FACTORYDEFINITIONS
#define MFACT_AVATAR			0

//#####==-- ENERGY MESH FACTORY DEFINITIONS
#define MFACT_RENZOU			1
#define MFACT_SPIRITBOMB		2
#define MFACT_SHOCKWAVE			3

//#####==-- WEAPON MESH FACTORY DEFINITIONS
#define MFACT_WEP_AK47LOWQ		4
#define MFACT_WEP_AWPHIGHQ		5
#define MFACT_WEP_FAMASSVX		6
#define MFACT_WEP_G3LOWQUA		7
#define MFACT_WEP_INCAMKII		8
#define MFACT_WEP_L96A1LOW		9
#define MFACT_WEP_M4A1ACTR		10
#define MFACT_WEP_MINIGUN1		11
#define MFACT_WEP_PSG1LOWQ		12
#define MFACT_WEP_SPAS12LQ		13
#define MFACT_WEP_SWAT552X		14

//#####==-- WEAPON MESH FACTORY DEFINITIONS
#define MFACT_VEH_DUCATI998		15

//#####==-- MECH MESH FACTORY DEFINITIONS
#define MFACT_MECH_1			16

//FACTORY ACTIVE FLAGS
static int MFACT_WEP = 0;
extern int LOADED_FACTORY[17];

//###==-- QCH DEFINITIONS --==###

//#==-- POLY DEFS
#define QPOLY_POLY_ONCE			0
#define QPOLY_POLY_STAY			1

//#==-- TYPE DEFS
#define QPOLY_TYPE_PNT			0
#define QPOLY_TYPE_TRI			1
#define QPOLY_TYPE_GOR			2

//#==-- RENDER DEFS
#define QPOLY_REND_NO_OCCLUDE		0
#define QPOLY_REND_OCCLUDE_ON		1
#define QPOLY_REND_DEPTH_SORT		2

//-------------------------------------------------------------------
// AI MINDSTATES DEFINED
//-------------------------------------------------------------------

#define MIND_IDLE			0
#define MIND_ACTIVEINIT		1
#define MIND_ACTIVE			2
#define MIND_CHECKVISION	3
#define MIND_ATTACK			4
#define MIND_SEARCHTARGET	5
#define MIND_CRUNCHDECIDE	6
#define MIND_HANDATTK		7
#define MIND_LONGATTK		8
#define MIND_LOOK			9
#define MIND_CLERIC_HEAL	20

//-------------------------------------------------------------------
// AI MIND MODES DEFINED
//-------------------------------------------------------------------

#define MMODE_ATTACKPLAN		0
#define MMODE_CLOSE_AGGRESSION	1
#define MMODE_CLOSE_DEFENSE		2
#define MMODE_MID_AGGRESSION	3
#define MMODE_MID_DEFENSE		4

//-------------------------------------------------------------------
// DEFINE OPERATION MODES
//-------------------------------------------------------------------

#define FULLOP_MODE				0
#define EFFECTS_TESTING_MODE	1
#define AI_TESTING_MODE			2

//-------------------------------------------------------------------
// DEFINE KEY FUNCTIONS
//-------------------------------------------------------------------

#define	KEYSTATIC			0
#define	KEYDOWN				1
#define	KEYUP				2

//-------------------------------------------------------------------
// MEMORY EVENTS DEFINED
//-------------------------------------------------------------------

#define EVENT_AVATAR_SIGHTED		0
#define EVENT_AVATAR_LOSTBRIEFLY	1

///////////////////////////////////
// Avatar Scale Increment Factor //
///////////////////////////////////

#define AVSCALEINC 0.64f
#define HITREACT_SCALE_IMP 25.0f
#define RENZOU_SCALE_IMP 0.1f

//--------------------------------------------------------------------
// Special Entity structures
//--------------------------------------------------------------------

	#pragma warning( disable : 4068 )
	#pragma GE_Type("Actor1.ico")
	typedef struct MatterMine
	{
	#pragma GE_Published
	QpoVec3d Pos;
	QpoVec3d Ang;
	int Output;
	#pragma GE_Origin(Pos)
	} MatterMine;

	#pragma GE_Type("Player.ico")
	typedef struct Q_PlayerEntityDataL
	{
	#pragma GE_Published
	QpoVec3d Origin;
	QpoVec3d Ang;
	#pragma GE_Origin(Origin)
	} Q_PlayerEntityDataL;

	#pragma GE_Type("Actor1.ico")
	typedef struct Q_AvatarEntityDataL
	{
	#pragma GE_Published
	QpoVec3d Pos;
	QpoVec3d Ang;
	int Team;
	int	Type;
	int Role;
	int Rank;
	int Level;
	#pragma GE_Origin(Pos)
	} Q_AvatarEntityDataL;

//-------------------------------------------------------------------
// GLOBALS
//-------------------------------------------------------------------

typedef struct GlobalVariablesStruct
{
	int				CVar;
	int				AnimPointer;
	bool			GD;
	//SERVER EDIT
 	//MSG             Msg;
 	const char		*File;
 	FILE			*stream;
 	float			gama;
 	int				run;
 	int				pauseFLAG,reloadFLAG,ActivationFLAG,UpdateFLAG;
	int				screenx,screeny;
 	float			Volume;
 	float			Pan;
 	float			Frequency;
 	float			SoundFinger;
	float			AnimCounter;
 	float			WorldScale;
	QpoVec3d		SurgeryFocus;

	pMesh			*mesh;
	int				unilevel;
	QpoVec3d		Pos,pos;
	QpoVec3d		GenericLightPos;
	std::vector<std::string> StructureAString;
	std::vector<int> StructureAInt;

	int lbutton[QNOMPLAYER],lbuttonhold[QNOMPLAYER],rbutton[QNOMPLAYER],mwheelroll[QNOMPLAYER],mbutton[QNOMPLAYER],mwheel[QNOMPLAYER];

 	int	NomNetEffectControl,NomPlasma,NomCharacterDATA,NomPntSprite,NomPEFMesh,NomHSpark,NomHeal,NomWorldEntities,NomMelHit,NomMelHitPRPR,NomSEnergy,NomLEnergy,NomSEnergyPRPR,NomLEnergyPRPR,NomJinks;
	int NomCart,NomBullet,NomBulletPRPR,NomBulHit,NomBulHitPRPR,NomSpikes,NomPowerFlash,NomSparks,NomBlood,NomExplosions,NomExplosionsPRPR,NomCloud,NomAI,NomStartP,NomSpell,NomDecal,NomVaporTrails;
	int NomEnMatBlocks,NomQObject,NomBMSentry,NomBuilding, NomNetZoneENTITY,NomNNBots,NomRealisation;
	int NomPowerBlade;

	int TempNomPntSprite;

 	int MaxNomSEnergy,MaxNomLEnergy;
	int MaxNomPowerBlade;

 	int	NETNomWorldAvatars;
 	int	NETNomNetplayer;

	float TimeFactor;

 	int   TimeHoleDir;
 	int   TimeHole;
 	int   TimeInit;
 	int   TimeReset;
 	int   TimeRotate,TimePlayerLock;
 	int   TimeWaitReset;
 	int   JumpTimeInit;
 	int   JinkTime;

	int	 NNBOTadjust;
 	int	 NNBOTwrite;

	int MusicSWITCH,MusicDEPRESS;

	int GameLevel,Multipass;
	float ScannerLevelFactor,ScannerLevelDiff;
	int CharSelect,GameTypeSelect,LevelSelect,NetworkOption;

	int	 KnockOutFLAG;
 	int	 KnockOutINIT;
 	int	 KnockOutCNT;
 	int	 KnockOutTIMER;
 	int	 KnockOutHEIGHT;

	QpoVec3d Origin,Origon;

	QpoBox Box,KokBox;

	int		RADPRESS1,RADPRESS2;
 	float	RADSCALE;
 	QpoVec3d RADplayerPOS,RADavatarPOS;
 	QpoVec3d	RADavatarRADPOS;
 	float	RADavatarLENGTH,RADavatarRADLENGTH;
 	QpoVec3d RADnorthVEC,RADavatarRADVEC;
 	float	RADnorthREALRADX,RADavatarREALRADX;
 	float	RADnorthREALRADZ,RADavatarREALRADZ;
 	float	RADavatarREALSCALE;
 	QpoVec3d RADmatrixIN,RADmatrixUP,RADmatrixLEFT;
 	QpoTransform RADrotatematrix;

	float TimeScale;
 	float TimeScaleREAL;
 	float TimeScaleALTER;
 	float S_TimeScale;

	int		FRLfirst,FRLsecond;
 	float	FRLresult;
 	int		FRLREALfirst,FRLREALsecond;
 	float	FRLREALresult;
 	float	FRLtarget,FRLCurrtarget;
 	float	FRLpossibleT;
 	int		FRLID;
 	int		FRLON;
 	int		FRLswitch;
 	int		FRL_LIMIT;

	float			ANGELeditBitmapRed,ANGELeditBitmapGreen,ANGELeditBitmapBlue;
 	float			ANGELeditBitmapSRed,ANGELeditBitmapSGreen,ANGELeditBitmapSBlue;
 	int				ANGELeditBmpCount;
 	int				ANGELeditMAPNUM;
 	int				ANGELeditKEYPRESS1,ANGELeditKEYPRESS2,ANGELeditKEYPRESSM,ANGELeditKEYPRESST;
 	int				ANGELeditFF;

	PossibleTargetData LockInLeaderData;
 	PossibleTargetData LockInTargetData;

 	QpoEnvironmentOptions AvatarEnviro;

    std::vector<std::shared_ptr<SoundEffect>> m_vec_SoundEffect;
} GlobalVariablesStruct;

	extern QSharedStruct<GlobalVariablesStruct> _;

	extern QpoVec3d Origin;
	extern QpoTransform BoneMat;
	extern int SHADOW,SHADOWX,SHADOWY,SHADOWZ,detcnt,AVSLOT,AVATARCNT,SCRAM,SCRAMJET,helly,aero,jet,helly2,helly3,aero2,jet2,warp,trans;
 	extern int Tempint;
	extern int pause;
	extern QpoVec3d qAxis[3];

	extern QpoVec3d CartMins;
	extern QpoVec3d CartMaxs;

	// Entity variables
 	extern QpoLevelEntity *Entity;
 	extern QpoLevelEntity_EntitySet* EntSet;
 	extern Q_PlayerEntityDataL* Q_PlayerEntityData;
 	extern Q_AvatarEntityDataL* Q_AvatarEntityData;

	// Wall sliding vars
 	extern float Slide;
 	extern unsigned long OldTimeGetTime;
 	extern unsigned long NewTimeGetTime;
 	extern time_t SysTime;
 	extern char *timeline;
	extern QpoLightInfo g_Light[NOM_LIGHT];
	extern int Q_Nom_Light;
	extern int Q_Nom_Light_Orig;

	//**********************************************************************************************************
	//GLOBALS***************************************************************************************************
				//FIXME - Convert all variables to 32 bit data, like int32, as it is faster
	extern bool	 g_LOAD;
	extern int   g_optionsresult;
	extern int   g_startcommand;
	extern bool  g_QUITM;
	extern bool  g_NetConnect;
	extern int	 KeyPRESS01,KeyPRESS02;
 	extern float text1,text2,text3,text4,text5,text6,text7,text8,text9,text10,text11,text12,text13,text14,text15,text16,text17;
 	extern long  Textl;
 	extern float testvalue1,testvalue2,testvalue3,testvalue4,testvalue5,testvalue6,testvalue7,testvalue8;
 	extern float TIME;
 	extern float TempDist;
 	extern float Tempfloat1;
 	extern float SpinAmount;
 	
 	extern int   MatCount,ChanceFinger;
 	extern float UniversalDMGSTR;
 	extern int	 DeliverKOID;
 	extern int	 press,pressN;
 	extern int	 BeeP,BeeP2;
 	extern int	 TOBE;
 	extern int	 WEPCHECK;
 	
 	extern int	 NNBOTloop;
 	extern int   ScreenCounter;
 	extern const char *ScreenShot;
 	extern QpoTransform CrunchMatrix,RotateMatrix,RotateMatrix2,RotateMatrix3,SaveMatrix;
 	extern QpoVec3d CrunchIn,CrunchLeft,CrunchUp;
 	
 	extern int Tempint1,Tempint2;
 	extern const char *TempChar1;
 	
 	extern float TestfloatALPHA1,TestfloatALPHA2,TestfloatALPHA3,TestfloatALPHA4,RotAMT;
 	
 	extern QpoVec3d ActorPos,PlayerPos;
 	extern float ActorVisDist;
 	
 	extern int	 TextOutputTest;
 	extern QpoVec3d TestArea,Pos2,Poser,Ange;
 	extern QpoVec3d goup,poop,goup2,scanback,scanfront,bullold,bullnew,test;
 	extern QpoTransform bullrot1,bullrot2,AIfriendly,Xrot90deg,rotmat;
 	extern QpoExtBox fogbox,frogbox;
 	extern QpoRect bmenu,textbox,TempRect1;
 	extern QpoRect robunsel,robsel,mineunsel,minesel,enerbar;
 	extern QpoVertex TVert;
 	extern QpoColor fontcol;
 	extern int			TESTShieldFLAG;
 	extern float		TESTShieldDIST;
 	extern float		TESTDist;
 	extern float		TESTLength;
 	extern QpoVec3d		TESTPosS;
 	extern QpoVec3d		TESTPosE;
 	extern QpoVec3d		WepDisplay;
 	extern QpoVertex    *TestPYRO;
 	extern QpoVertex    TestLVERT;
 	extern QpoFont      *font1;
 	extern QpoVertex    *mine,*pollie;
 	extern QpoVertex    FVert;
 	extern const char *BoneDef[50];
 	extern int qBoneNum[50];
 	extern QpoVec3d qCorner,qDX,qDY,qDZ;
	extern QpoVector pCorner,coldetresult;
	
	extern QpoVectorBox ColldetBox;
 	extern float qxScale,qyScale,qzScale;
 	extern QpoTransform bonepos;
 	extern QpoBoneCollisionInfo	BoneCollisionInfo;
 	extern float chit,mvlength;
 	extern QpoBody *LisaBody;
 	extern QpoBody *Shibody;
 	extern QpoMotionPath  *RPath;
 	extern int  RMotion;
 	extern QpoTransform	ReactPos,ParentPos,qAttachment;
 	extern int qParBone;
 	extern int numparents;
 	extern int child;
 	extern const char *qBoneName;
 	extern QpoTransform WorldXF,BoneXF;
 	extern QpoVec3d WorldIn,BoneIn,BoneXFIn,SpinIn;
 	extern QpoVec3d AxeStart,AxeEnd,AxeVec;
 	extern QpoVec3d BoneMatrixX,BoneMatrixY,BoneMatrixZ;
 	extern QpoVec3d WorldX,WorldY,WorldZ;
 	extern QpoVec3d Shift;
 	extern QpoTransform BoneMatrix;
 	extern int BTbonenum;
 	extern QpoVec3d Vectorn,Xv,Yv,Zv;
 	extern QpoTransform Boneposs;
 	extern float lengthvec;
 	
 	extern int timeoffset;
 	extern QpoLight playerlight;
 	extern int sunriseF;
 	extern float sunrise;
 	extern int count;
 	extern float qred,qgreen,qblue;
 	extern QpoExtBox GBBox;
 	extern QpoRect qBrushrect,ItemBrushrect;
 	extern QpoColor BrushRGBA;
 	extern QpoVec3d BrushVec;
 	extern QpoVec3d tempPOS,tempPOS2;
 	extern int tempALPHA;
 	extern int noot;
 	extern int Temp;
 	extern float shir,shig,shib;
 	extern int	 nameplateno,nameplatedir;
 	
 	extern int aerop;
 	extern int tempint1,tempint2;
 	
 	extern QpoFog *Fogo;
 	extern float TimeCounter;
 	extern int AIcount,AItempcnt;
 	extern QpoVec3d TempVec1,TempVec2,TempVec3,TempVec4,TempVec6,TempVec7;
 	extern QpoVec3d ScanVecTo,ScanTurnVec,ScanTurnVecAimer;
 	extern float ScanObjAng,ScanDistL,ScanDistR,ScanAvatarDist;
 	extern int ScanID;
 	extern int KeyDepress,KeyDepress2;
 	extern int BrainLOOP,LoopON;
 	extern float VisClipDist;
 	extern float TriEffectUb,TriEffectUt;
 	extern QpoBuffer_Data SendBuffer;
 	extern float tempForwardSpeed;
 	extern QpoVec3d tempAngles;
 	extern float NetTime;
 	extern unsigned long DataSize;
 	extern QInt	*BufferLoad;
 	extern int CharCounter;
 	extern POINT temppos,tempposSTR,mpos;
 	extern float TURN_SPEED;
 	extern float UPDOWN_SPEED;
 	extern float Tempfloat;
	extern QpoVec3d CameraPOS;
	extern QpoVec3d CameraINC;
	extern bool TimeAlter;
	extern bool KeyCheck;
	extern int ApplicationFocus;

	//### Vapor Trails Variables
	extern QpoVec3d	qcross;
 	extern int		NumQuads,major;
 	extern float	Width1, Width2;
 	extern QpoVec3d	Drift;
 	extern QpoColor	ColourSTART,ColourEND;
	extern QpoVec3d	AvatarPos;
	extern QpoVec3d	DistVec;
 	extern float	AvatarDist;
 	extern QpoVec3d	TestVec1,TestVec2,TestVec3,TestVec4,TestVec5,TestVec6,TestVec7;
 	
		 // ~Object loading counters~
	extern int TEXcounter;
	extern int MESHcounter;

	//### TEMP CHAR-DATA
 	extern QInt			TEMP_CurrCHAR;
 	extern QInt			TEMP_NomAvatars;
 	extern Q_AVATARS	TEMP_AVATARDATA[50];
 	extern QInt			TEMP_playerTEAM;
 	extern char			TEMP_PlayerWEP[21],TEMP_AvatarWEP[50][21];
 	extern char			TEMP_PlayerACT[21],TEMP_PlayerSACT[21],TEMP_AvatarACT[50][21],TEMP_AvatarSACT[50][21];
 	extern int			TEMP_AvatarCLASS[50];
 	extern int			STRcompare;
 	
 	extern Q_AngelEDIT		TEMP_AngelCOLOURS;
 	extern int				MechKEYPRESS;
 	extern int				ScanKEYPRESS;
 	extern int				EnMatX,EnMatY,EnMatZ;
 	extern int				EnMatX2,EnMatY2,EnMatZ2;
	extern QpoAvExtBox		bonebox,bonebox1,bonebox2,bonebox3,boneboxR;

	//#### NNBOT VARS
 	extern QpoVec3d			qLeftToRightESCAN;
 	extern QpoVec3d			qEnemyLeft,qEnemyRight,qEnemyUp,qEnemyDown,qEnemy,qEyes;
 	extern int				qTargetFound;
 	extern QpoCollision		qRayTraceCOLL;

	//######- QAGE GLOBALS -######

	extern QSharedStruct<QpoAvatarFlags> playerAV[QNOMPLAYER];
	extern QSharedStruct<PlacementMarker> Q_PlacementMarker;
};

//**********************************************************************************************************
//**********************************************************************************************************

//-------------------------------------------------------------------
// GLOBALS		/END
//-------------------------------------------------------------------

#pragma message ("###  Global Variables  [Q-GlobalHeader.h]")

#endif