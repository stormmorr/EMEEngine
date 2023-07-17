/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	- Minor Component -Avatar When In Human Form-
		-Header File Classifications-
*/

#ifndef __Q_CORE_Avatar__
#define __Q_CORE_Avatar__

#include <vector>

#define QNOMAI 405
#define UNS_MAX_PLS 4

namespace GVARS
{

	//*----Player and AI Flag Structures----*

class PlayerFlags
{
public:
	Q_UPDATE			NetUPDATE;
	Q_CharacterDATA		BFO;
	Q_CharacterDATA		CDATAS[UNS_MAX_PLS];
	Q_Cleric			Cleric;
	Q_Soldier			Soldier;
	Q_Ninja				Ninja;
	Q_EnergyArchitect	EnergyArchitect;
	QpoAvatarImage		NetImage;
	QpoInstanceFlags	Weapon;	// Weapon Actor
	QpoAvatarFlags		Shield;	// Shield Actor
	QpoAvatarFlags		Shadows[4]; // Actor Shadows
	int	ShadowAlpha[4];
	float ShadowScale[4];
	float ShadowScaleX[4];
	float ShadowScaleY[4];
	float ShadowScaleZ[4];
	int	ShadowVisibility;
	float ShadowEffect_Scale[50];
	int ShadowEffect_Scale_Counter;
	int ShadowEffect_Counter;
	int ShadowALPHA;
	Q_Jinks	Q_Jink;
	int Rank;
	int WeaponFire;
	QpoVec3d STRAngles;
	int	LEVEL;
	float LEVELFactor;
	int	AttackSoundTRIG;
	int	AttackSoundINITTRIG;
	float AttPoseInc;
	float	AvatarDMGSTORE[251];
	int		JinkSPECEFF;
	int		TrailINIT;
	int		TrailLINK;
	int		HitShield;
	float	CNTR1;
	float	CNTR2;
	float	CNTR3;
	float	CNTR4;
	float	CNTR5;
	float	CNTR6;
	float	CNTR7;
	int		WeaponDISPLAY;
	int		WeaponATTACHFLAG;
	int		SLOTINC;
	float	GravityAlter;
	int		MaxNomCharacters;

	float	QAEFF_CNTR01[50];
	float	QAEFF_CNTR02[50];
	float	QAEFF_CNTR03[50];
	float	QAEFF_CNTR04[50];
	float	QAEFF_CNTR05[50];
	float	QAEFF_CNTR06[50];
	float	QAEFF_CNTR07[50];
	float	QAEFF_CNTR08[50];
	float	QAEFF_CNTR09[50];
	float	QAEFF_CNTR10[50];

	float	QAEFF_ROTAMT[50];
	float	QAEFF_ROTAMT01[50];
	float	QAEFF_ROTAMT02[50];
	float	QAEFF_ROTAMT03[50];
	float	QAEFF_ROTAMT04[50];
	float	QAEFF_ROTAMT05[50];
	float	QAEFF_ROTAMT06[50];

	int		TestVALUE01;
	float	TestVALUE02,TestVALUE03,TestVALUE04,TestVALUE05,TestVALUE06,TestVALUE07,TestVALUE08,TestVALUE09,TestVALUE10;

	int			QA_EFF_TYPE;
	float		QA_EFF_INTENSITY;
	int			QA_ITEMREF;
	QpoTransform	QA_EFF_BONEMATRIX,QA_EFF_BONEMATRIX_MEM,QA_EFF_BONEMATRIX_STR;
	QpoTransform	QA_EFF_BONEMATRIX01;
	QpoVec3d		QA_EFF_TRAVEC;
	QpoVec3d		QA_EFF_MEMVEC;
	QpoVec3d		QA_EFF_MEMPOS;
	float		QA_EFF_MEMLENGTH,QA_EFF_MEMMOVE;
	int			QA_EFF_SWITCH;
	int			QA_EFF_COL00RED,QA_EFF_COL00GREEN,QA_EFF_COL00BLUE,QA_EFF_COL00ALPHA;
	int			QA_EFF_COL01RED,QA_EFF_COL01GREEN,QA_EFF_COL01BLUE,QA_EFF_COL01ALPHA;
	int			QA_EFF_COL02RED,QA_EFF_COL02GREEN,QA_EFF_COL02BLUE,QA_EFF_COL02ALPHA;
	int			QA_EFF_COL03RED,QA_EFF_COL03GREEN,QA_EFF_COL03BLUE,QA_EFF_COL03ALPHA;
	int			QA_EFF_COL04RED,QA_EFF_COL04GREEN,QA_EFF_COL04BLUE,QA_EFF_COL04ALPHA;

	int		SpecLvlRESET;
	int		SNDTRIGEnergy;

	float	PrevUNUSEDXP;
	QInt	UpdateCHAR;
	Q_ItemRef	NewITEMREF;

	float	DecFinger;

	float	JINK3_PowerFactor;
	float	JINK3_WeaponFactor;

	float	PowerFlightDUSTCNT;
	float	PowerFlightPOWERF;
	float	PowerFlightRADIUS;

	int		MSG_XPON;
	int		MSG_XPInit;
	int		MSG_NomDigits;
	int		MSG_TESTDigits;
	float	MSG_XPScreenDIST;
	float	MSG_XPScreenDistINC;
	int		MSG_XPScreenDIR;
	float	MSG_XpInc;
	float	MSG_ItemQUAL;
	int		MSG_Digit[11];

	int		MSG_ITEMON;
	int		MSG_ITEMInit;
	float	MSG_ITEMScreenDIST;
	float	MSG_ITEMScreenDistINC;
	int		MSG_ITEMScreenDIR;
	Q_ItemRef	MSG_ItemREF;

	int WallRunSWITCH;

	QpoVec3d oldAPC,newAPC,INvectorAPC,UPvectorAPC,LEFTvectorAPC;

	QpoVec3d AnglesVec;

	int JSpiralCAM;

	int	JSSpikes;

	int	Team;

	QpoVec3d finalcolldet_oldpos;
	QpoVec3d finalcolldet_oldposCRT;
	QpoVec3d finalcolldet_Trans_CRT;

	int QformTeamCount;
	bool QformChk;
	std::vector<QpoVec3d> QformVecPos;
	std::vector<int> QformVecID;

	float	JinkBLAST;
	float	JB_Power;
	QpoVec3d	JB_Pos;
	QpoVec3d	JB_Origin;
	QpoVec3d	JB_TraVec;
	QpoVec3d	JB_PlaceVec;
	float	JB_Radius;
	float	JB_Speed;

	int		JinkRUSHCLOUD;
	float	JRC_Power;
	int		JRC_SKIP;
	QpoVec3d	JRC_Pos;
	QpoVec3d	JRC_Origin;
	QpoVec3d	JRC_TraVec;
	QpoVec3d	JRC_PlaceVec;
	float JRC_Radius;
	float JRC_Speed;
	QpoVec3d JRC_InVec;
	QpoVec3d JRC_InVecBack;

	int			ATTLightON;
	int			ATTCoronaMatt;
	int			ATTCoronaMattDIR;
	QpoColor	ATTLightColor;
	QpoLight	ATTLight;
	QpoVertex	ATTCoronaLvert;

	int	Flip;

	int AntiMultHits[355];
	int	AntiMultHitsSHIELD[355];

	float JinkSpecialON;

	int	ShadowsOn;
	float ShadowsAMT;

	int	PlayerMode;		//Mode 0 = Walking / 1 = Riding
	int VehicleAttach;

	QpoTransform ShadowMeM[50];
	float ShadowMeMPose[50];

	int EnergyWakeON;
	QpoVec3d EnergyWakeTraj;
	QpoVec3d EnergyWakePos;

	int	EnergyTargetLock;
	int	EnergyDisplayLock;
	int	EnergyDisplayAlpha;
	int	EnergyDisplayColor;
	float EnergyDisplayScale;
	PossibleTargetData PossEnergyTargets[50];
	float EnergyCloseDist;
	int	EnergyCloseID;
	int EnergyTargetLaserAlpha;
	int	NomEnergyTargets;
	int	EnergyTARGETIDSTR;
	int	EnergyCounter;

	float AvatarRotation;
	float NetRotation;

	int	EnergyLockID;

	int EnergySWITCHOFF;

	//Colldet Scanner items
	QpoVec3d	ScanVecTo;
	float		ScanTurnAng;
	float		ScanTurnAngSTR;
	float	ScanAvatarDist;

	PossibleTargetData TargetsPresent[150];
	int	NomTargetsPresent;

	int	CameraShake,CameraShakeINIT;
	int	CamShkCNT,CamShkTIME;
	float CamShakeIncX,CamShakeIncY,CamShakeIncZ;
	float CameraShakePOWER;

	int AttackPos;

	int EffectMeshID;

	int	SPACEKEYcnt;

	int	WindWake;
	int WindWakeJump;

	int JSHitTrigger;

	float BodyRotation;

	int NomTrailL;
	int	TrailFadeSpan[10][2];	//Fade out brush (Trails)

	int JumpDir;
	float JumpFactor;
	float JumpState;
	QpoVec3d JumpVec;

	int CleanHit;

	int SwitchTrailsFLAG;

	int			BackPBmpCnt;
	float		BackPRed,BackPGreen,BackPBlue;
	unsigned int BackPBitmap;

	float STRattposecnt,NEWattposecnt;

	int DmgBANK;

	int	AirBorn;
	int	AirBornSTR;

	int	BlockHitID;
	int ShkBlkINIT;
	int BlockHitFLAG;
	int BlockHitREACTSCALE;
	int FullBlock;

	int JinkSpecCnt;

	int TimeHoleFLAG;

	float ForwardSpeed; // Speed we are moving
	float PlayerHeight; // How tall are we?
	float PlayerSpeed; // How fast are we?
	float DownSpeed; // How fast are we?
	float SideSpeed;
	int JumpOff;
	int	JumpFG;
	int	AttackIdle;
	float camrotdist;
	QpoVec3d oldpos,OldPos;
	QpoVec3d newpos,NewPos;
	QpoTransform ViewXForm;
	QpoVec3d Angles;
	QpoVec3d trueAngles;
	QpoVec3d STOREAngles;
	QpoVec3d AJAngles;
	QpoVec3d InStore;
	QpoVec3d UpStore;
	QpoVec3d In;
	QpoVec3d Left;
	QpoVec3d Right;
	QpoVec3d Mins;
	QpoVec3d Maxs;
	QpoCollision Collision;
	QpoVec3d Up;
	float upspeed;
	QpoTransform Xform;
	QpoTransform CamMatrix;
	QpoTransform CamMatrixSTR;
	QpoTransform Camrot;
	QpoTransform RFistPos;
	QpoTransform RFistPosV;
	QpoTransform RFistPos2;
	QpoTransform RFootPos,LFootPos;
	QpoTransform LFistPos;
	QpoTransform LFistPosV;
	QpoTransform AttPos;		//Position of attacking limb
	QpoTransform OAttPos;		//Old position of attacking limb
	QpoTransform LimbPos;
	QpoTransform LimPosBox;
	QpoTransform Mellimpact;
	QpoTransform HeadPos;
	QpoTransform BonMatrix;
	QpoVec3d CamLeft,CamUp,CamIn;
	QpoVec3d BonLeft,BonUp,BonIn;
	QpoVec3d NewLeft,NewUp,NewIn;
	int mode;
	int Aposestate,Mposestate;
	int HitReactionGB;
	float idleposecnt;
	float idlespeed;
	int	idlemotion;
	float runposecnt;
	float jumpposecnt;
	float attposecnt;
	float attposeINC;
	float wepposecnt;
	float crohposecnt;
	QpoLight BodyLight;
	QpoColor BodyLightColor;
	int LitAdFlag;
	int HoldBack;

	QpoCollision WallRunCollision;
	int WallRun;
	int WallRunInit;
	int WallRunDir;
	float WallRunHeight;
	int WallRunHeightDir;
	QpoVec3d WallRunOldPos,WallRunNewPos;
	int WallRunDelay;
	QpoVec3d WallRunForward;
	QpoVec3d SurfaceIn,SurfaceLeft,SurfaceUp;
	float WallRunSave;
	int	WallRunSaveInit;
	QpoVec3d WallRunSavePos;
	QpoVec3d WallRunDiff;
	int WallRunTilt;
	int WallRunACTIV;

	int ReloadPos;

	int attackon;
	int attacking;
	int attackstack[7];
	int attackstackSPECIAL[7];
	int astackcntdir[5];
	int astackcnt;
	int astackrun;
	int attackhits;
	int attackhitReset;
	int	attackhitRcount;
	int	collide;
	int attackprog;
	int attcombo;

	int collideJK;
	int SpecialLOCK;

	int HitLethal;
	int	DeflectLethal;
	int	DeflectPower;

	int	Deft_InReact;
	float Deft_attposecnt;
	int	Deft_PoseState;
	float Deft_HitReactScale;

	float blendamount[150];
	int blendon;
	//int hitflashA,hitflashB,hitflashC,hitflashD,hitflashE;

	int energyinit[50];		//Energy attack initialise flag
	int energyfire[50];		//Energy attack fire flag
	int enerlight;				//TODO: struct energy attacks
	float enerscale;
	float scaleinc;
	int enerscalegrow;
	float enersavescale;
	float enerspeed;
	int energyPower;
	QpoVec3d energyTraj;
	int	LEnergyID;
	int EnergyInitialise;
	QpoVec3d EnergyOldPos,EnergyNewPos;

	int	EnergyReleased;

	QpoVec3d EnergyMins,EnergyMaxs;

	int	EnergyHand;

	int	WeaponStatus;
	QpoTransform WepAttach;
	QpoVec3d	MovVec;
	int	WepAlpha;
	int WepIdle;
	float FireRate;
	QpoVec3d AimVec,AimVecUp;
	float WeaponRecoil;
	float WeaponAmmo;
	int WeaponZOOM;
	float WeaponZoomFACT;
	int SysIndex;
	int NetAvatarID;

	int	QformONtaunt;

	float expandro;
	int testef;
	int wazirl;
	int wazcnt;

	QpoTransform TempXForm1,TempXForm2,TempXForm3,TempXForm4,TempXForm5;
	QpoVec3d TempVec1,TempVec2,TempVec3,TempVec4;
	float Tempfloat1;

	int TrailsOn;

	int Scan;		//Create Scanner Struct
	int ScanInit;
	int ScanBitHeight;
	int ScanBitAlpha;
	int ScanBoneAlpha;
	int ScanUP;
	float ScanBoxScale;
	float ScanBoxAlpha;
	QpoVec3d ScanBoxVec;

	int React;
	QpoVec3d MoveReactVec;
	float MoveReactSpeed;
	float ReactTurnAng;

	float ScanDistL,ScanDistR;

	int HitWall;
	QpoVec3d HitWallNormal;

	float HitReactScale;
	int	BulletHitCnt;
	int BulletHitCntTimer;

	int	MFlash;
	int	NETMFlash;

	int Blocking;
	int BlockHit;
	int Block;
	int BlockHeight;

	QpoVertex LaserLV;
	int	LaserAlpha;
	QpoVec3d LaserStr;

	int	KL_LeftToFor;
	int	KL_RightToFor;
	int	KL_ForToLeft;
	int	KL_ForToRight;
	int	KL_BlockToFor;
	int KL_LTFSpecLevel;
	int KL_RTFSpecLevel;
	int KL_FTLSpecLevel;
	int KL_FTRSpecLevel;
	int KL_BTFSpecLevel;
	int KL_Timer,KL_BTimer;
	int	KL_CLogC;
	int KL_CLogTimer;
	int KL_CSpecial;
	//int KL_KeyPRESSA;
	//int KL_KeyPRESSW;
	int	SpecialON;

	//int JumpMotion;
	float JumpPoseINC;
	int JumpAttFG;
	int	GravityON;
	int AirJinkLOGFT;
	int AirJinkRotFG;
	int	AirJinkInit;
	int	AirJinkPrep;

	int	MatCounter[10];

	int PlayerJinkID;

	int	JinkON;

	QpoTransform ROTATEMatrix,STOREMatrix;

	int	AJPushOffON;
	int	AJPushOffType;
	int TrailsCount;

	float HB_Health;
	float HB_STR_Health;
	float HB_MaxHealth;
	float HB_Armour;
	float HB_STR_Armour;
	float HB_MaxArmour;
	float HB_Energy;
	float HB_STR_Energy;
	float HB_MaxEnergy;
	float HB_STR_POWERBANK;
	float HB_HealthUND;
	int HB_HUNDDIR;
	int HB_LastAvatarHitID;
	int HB_LastAvatarHitIDSTORE;
	int HB_RecoverMode;
	int	HB_EnergyTimer;

	int HB_Dead;
	int HB_DeadTimer;
	int HB_DeadTimerC;
	int HB_DeadTimerPos;

	int HB_Lives;
	int HB_LiveResetSW;

	int HB_DmgSTORE;
	int HB_DmgSTORETimer;

	int HB_HReduceON;
	int	HB_ReduceOld;
	int HB_Reduce;
	float HB_ReduceHeight;
	float HB_ReduceHInc;
	QpoRect HB_ReduceRect,HB_ReduceRectFill;
	QpoColor HB_ReduceRectColor;
	QpoColor HB_FlashRectColor;
	float HB_HealthDiff;
	float HB_HealthHistory;

	int CrunchTimer;

	int BlowHeight;

	int RunningCount;
	int Running;

	int FirstPerson;

	int	CrouchInit;
	int	Crouch;

	int HealInit;
	int JinkInit;

	int	Invisible;

	int NomTriEffect;

	int	StepTimer;

	Q_Expandro3D AJPushOff;
	Q_Backpack Backpack;
	Q_TrailLineCLS	Trail[100];
	Q_TexTriEffectCLS Q_TexTriEffect[300];
	Q_Vehicle Vehicle;
	Q_Mech Mech;
};

class AIFlags
{
public:
	int	LIVE;
	int	NetplayerFLAG;
	int	m_Own;
	Q_UPDATE			NetUPDATE;
	Q_CHARDATA			CharDATA;
	Q_Cleric			Cleric;
	Q_Soldier			Soldier;
	Q_Ninja				Ninja;
	Q_EnergyArchitect	EnergyArchitect;
	QpoAvatarImage		NetImage;
	QpoAvatarFlags		AV;			// Body Actor
	QpoInstanceFlags	Weapon;	// Weapon Actor
	QpoAvatarFlags		Shield;		// Shield Actor
	QpoAvatarFlags		Shadows[4];	// Actor Shadows
	Q_Jinks	 Q_Jink;
	Q_Brains Q_Brain;	// AI Brain
	Q_Hearts  Q_Heart;
	PossibleTargetData TargetsPresent[150];
	PossibleTargetData FriendlyPresent[150];
	PossibleTargetData FriendlyMatrix[150];
	int	NomTargetsPresent;
	int	NomFriendlyPresent;
	QpoExtBox Extenbox;
	Q_Vehicle Vehicle;
	int		HB_DeadTimer;
	int		HSparkInit;
	int		StepTimer;

	int		HitShield;
	float	GravityAlter;

	int		TrailINIT;
	int		TrailLINK;
	int		SLOTINC;

	QpoVec3d AimVecUp;

	float	PowerFlightDUSTCNT;
	float	PowerFlightPOWERF;
	float	PowerFlightRADIUS;

	float	CNTR1;
	float	CNTR2;
	float	CNTR3;
	float	CNTR4;
	float	CNTR5;
	float	CNTR6;
	float	CNTR7;

	int		Updated;

	int		AVDATID;
	int		WeaponATTACHFLAG;
	int		WeaponDISPLAY;

	float	QAEFF_CNTR01[50];
	float	QAEFF_CNTR02[50];
	float	QAEFF_CNTR03[50];
	float	QAEFF_CNTR04[50];
	float	QAEFF_CNTR05[50];
	float	QAEFF_CNTR06[50];
	float	QAEFF_CNTR07[50];
	float	QAEFF_CNTR08[50];
	float	QAEFF_CNTR09[50];
	float	QAEFF_CNTR10[50];

	float	QAEFF_ROTAMT[50];
	float	QAEFF_ROTAMT01[50];
	float	QAEFF_ROTAMT02[50];
	float	QAEFF_ROTAMT03[50];
	float	QAEFF_ROTAMT04[50];
	float	QAEFF_ROTAMT05[50];
	float	QAEFF_ROTAMT06[50];

	int		TestVALUE01;
	float	TestVALUE02,TestVALUE03,TestVALUE04,TestVALUE05,TestVALUE06,TestVALUE07,TestVALUE08,TestVALUE09,TestVALUE10;

	int			QA_EFF_TYPE;
	float		QA_EFF_INTENSITY;
	int			QA_ITEMREF;
	QpoTransform	QA_EFF_BONEMATRIX,QA_EFF_BONEMATRIX_MEM,QA_EFF_BONEMATRIX_STR;
	QpoTransform	QA_EFF_BONEMATRIX01;
	QpoVec3d		QA_EFF_TRAVEC;
	QpoVec3d		QA_EFF_MEMVEC;
	QpoVec3d		QA_EFF_MEMPOS;
	float		QA_EFF_MEMLENGTH,QA_EFF_MEMMOVE;
	int			QA_EFF_SWITCH;
	int			QA_EFF_COL00RED,QA_EFF_COL00GREEN,QA_EFF_COL00BLUE,QA_EFF_COL00ALPHA;
	int			QA_EFF_COL01RED,QA_EFF_COL01GREEN,QA_EFF_COL01BLUE,QA_EFF_COL01ALPHA;
	int			QA_EFF_COL02RED,QA_EFF_COL02GREEN,QA_EFF_COL02BLUE,QA_EFF_COL02ALPHA;
	int			QA_EFF_COL03RED,QA_EFF_COL03GREEN,QA_EFF_COL03BLUE,QA_EFF_COL03ALPHA;
	int			QA_EFF_COL04RED,QA_EFF_COL04GREEN,QA_EFF_COL04BLUE,QA_EFF_COL04ALPHA;

	float	JINK3_PowerFactor;
	float	JINK3_WeaponFactor;

	float	DecFinger;

	int	NetPID;

	int	JinkSPECEFF;

	int TrailsCount;
	QpoVec3d OldPos,NewPos,StrPos;
	int StrPosCounter;
	int WallRunSWITCH;
	int	SNDTRIGEnergy;

	int HitSlump;

	float AvatarDMGSTORE[251];

	QpoTransform ROTATEMatrix,STOREMatrix;

	int	JSSpikes;

	int	TestValue1,TestValue2;

	int ReloadPos;

	int	AJPushOffON;
	int	AJPushOffType;

	//int	JumpMotion;
	float	JumpPoseINC;
	int		JumpAttFG;
	int	GravityON;
	int AirJinkLOGFT;
	int AirJinkRotFG;
	int	AirJinkInit;

	float		JinkBLAST;
	float		JB_Power;
	QpoVec3d	JB_Pos;
	QpoVec3d	JB_Origin;
	QpoVec3d	JB_TraVec;
	QpoVec3d	JB_PlaceVec;
	float		JB_Radius;
	float		JB_Speed;
	float		NetMoveScale;

	QpoVec3d	StorePosition;

	int			ATTLightON;
	int			ATTCoronaMatt;
	int			ATTCoronaMattDIR;
	QpoColor	ATTLightColor;
	QpoLight	ATTLight;
	QpoVertex	ATTCoronaLvert;

	QpoVec3d EnergyMins,EnergyMaxs;

	QpoVec3d oldAPC,newAPC,INvectorAPC,UPvectorAPC,LEFTvectorAPC;

	int	SwitchTrailsFLAG,JSHitTrigger;
	float CleanHit;

	QpoVec3d ORIGSTARTPOINT;

	int	collideJK;

	float attposeINC;

	float STRattposecnt,NEWattposecnt;

	QpoVec3d LaserStr;

	int SpecialLOCK;

	QpoVec3d STRAngles;

	int	LaserAlpha;

	int FirstPerson;

	int	SPACEKEYcnt;

	int	PlayerJinkID;

	int RunningCount;

	int	KL_LeftToFor;
	int	KL_RightToFor;
	int	KL_ForToLeft;
	int	KL_ForToRight;
	int	KL_BlockToFor;
	int KL_LTFSpecLevel;
	int KL_RTFSpecLevel;
	int KL_FTLSpecLevel;
	int KL_FTRSpecLevel;
	int KL_BTFSpecLevel;
	int KL_Timer,KL_BTimer;
	int	KL_CLogC;
	int KL_CLogTimer;
	int KL_CSpecial;

	int	SpecLvlRESET;

	int PlayerMode;

	float AttPoseInc;
	int	AttackSoundTRIG;
	int	AttackSoundINITTRIG;

	int	WindWake;
	int WindWakeJump;
	int	AttackPos;
	int	Flip;

	int AntiMultHits[261];
	int	AntiMultHitsSHIELD[261];

	float JinkSpecialON;
	int	ShadowBmpCount;
	unsigned int ShadowBitmap;
	float ShadowBitmapRed,ShadowBitmapBlue,ShadowBitmapGreen;

	int	ShadowAlpha[4];
	float ShadowScale[4];
	float ShadowScaleX[4];
	float ShadowScaleY[4];
	float ShadowScaleZ[4];
	int ShadowALPHA;

	QpoTransform ShadowMeM[50];
	float ShadowMeMPose[50];

	int NomTrailL;
	int	TrailFadeSpan[10][2];	//Fade out brush (Trails)

	int	AirBorn;
	int	AirBornSTR;

	int Running;
	int	HoldBack;

	int SysIndex;
	int	Team;
	int	Role;
	int Rank;
	int LEVEL;
	float LEVELFactor;

	int QformON;

	int	BlockHitID;
	int ShkBlkINIT;
	int BlockHitFLAG;
	int BlockHitREACTSCALE;
	int FullBlock;

	int JinkInit;
	int	JinkID;

	int	DeflectLethal;
	int	DeflectPower;

	int	Deft_InReact;
	float Deft_attposecnt;
	int	Deft_PoseState;
	float Deft_HitReactScale;

	int DmgBANK;
	int CrunchTimer;
	int HitLethal;
	int EnemyPoseState;

	int ForwardSpeed; // Speed we are moving
	int PlayerHeight; // How tall are we?
	int PlayerSpeed; // How fast are we?
	float DownSpeed; // How fast are we?
	float SideSpeed;
	int JumpOff;
	int	JumpFG;
	int	JumpDir;
	QpoVec3d JumpVec;
	float JumpFactor;

	int	AttackIdle;
	float camrotdist;
	QpoVec3d oldpos;
	QpoVec3d newpos;
	QpoTransform ViewXForm;
	QpoVec3d Angles;
	QpoVec3d AnglesChg;
	QpoVec3d NetAngles;
	QpoVec3d trueAngles;
	QpoVec3d STOREAngles;
	QpoVec3d AJAngles;
	QpoVec3d AnglesVec;
	QpoVec3d QNetAngles;
	QpoVec3d In;
	QpoVec3d Left;
	QpoVec3d Right;
	QpoVec3d Mins;
	QpoVec3d Maxs;
	QpoCollision Collision;
	QpoVec3d Up;
	float upspeed;
	QpoTransform Xform;
	QpoTransform CamMatrix;
	QpoTransform Camrot;
	QpoTransform RFistPos;
	QpoTransform RFistPosV;
	QpoTransform RFistPos2;
	QpoTransform LFistPos;
	QpoTransform RFootPos,LFootPos;
	QpoTransform AttPos;		//Position of attacking limb
	QpoTransform OAttPos;		//Old position of attacking limb
	QpoTransform LimbPos;
	QpoTransform LimPosBox;
	QpoTransform Mellimpact;
	int mode;
	int Aposestate,Mposestate;
	int HitReactionGB;
	float idleposecnt;
	float idlespeed;
	int	idlemotion;
	float runposecnt;
	float jumpposecnt;
	float attposecnt;
	float wepposecnt;
	float shieldposecnt;
	QpoLight BodyLight;
	QpoColor BodyLightColor;
	int LitAdFlag;
	QpoTransform HeadPos;
	int HitWall;
	QpoVec3d HitWallNormal;
	float ReactTurnAng,ScanDistL,ScanDistR;

	bool ShadowsOn;
	float ShadowsAMT;

	int attackon;
	int attacking;
	int attackstack[7];
	int attackstackSPECIAL[7];
	int astackcntdir[5];
	int astackcnt;
	int astackrun;
	int attackhits;
	int attackhitReset;
	int	attackhitRcount;
	int	collide;
	int attackprog;
	int attcombo;

	int HealInit;

	float blendamount[150];
	int blendon;
	//int hitflashA,hitflashB,hitflashC,hitflashD,hitflashE;

	int TimeHoleFLAG;

	int energyinit[50];		//Energy attack initialise flag
	int energyfire[50];		//Energy attack fire flag
	int enerlight;				//TODO: struct energy attacks
	float enerscale;
	float scaleinc;
	int enerscalegrow;
	float enersavescale;
	float enerspeed;

	int	EnergyTargetLock;
	int	EnergyDisplayLock;
	int	EnergyDisplayAlpha;
	int	EnergyDisplayColor;
	float EnergyDisplayScale;
	PossibleTargetData PossEnergyTargets[50];
	float EnergyCloseDist;
	int	EnergyCloseID;
	int EnergyTargetLaserAlpha;
	int	NomEnergyTargets;
	int	EnergyTARGETIDSTR;
	int	EnergyCounter;

	int EnergySWITCHOFF;

	int	LEnergyID;
	int EnergyInitialise;
	QpoVec3d EnergyOldPos,EnergyNewPos;

	float ActorRotation;

	int	EnergyLockID;

	int	EnergyReleased;

	int	EnergyHand;

	int	WeaponStatus;
	int WeaponAIM;
	int WeaponHolster;
	int WeaponDrawn;
	QpoTransform WepAttach;
	QpoVec3d MovVec;
	int	WepAlpha;
	int WepIdle;
	float FireRate;
	QpoVec3d AimVec;
	int WeaponAmmo;
	float WeaponAimer;
	float WeaponRecoil;
	float crohposecnt;
	int CrouchInit;
	int Crouch;

	int	FireRated;
	int	FireRateTimer;

	float expandro;
	int testef;
	int wazirl;
	int wazcnt;

	QpoTransform TempXForm1,TempXForm2,TempXForm3,TempXForm4,TempXForm5;
	QpoVec3d TempVec1,TempVec2,TempVec3,TempVec4;

	int TrailsOn;

	int Scan;		//Create Scanner Struct
	int ScanInit;
	int ScanBitHeight;
	int ScanBitAlpha;
	int ScanBoneAlpha;
	int ScanUP;
	float ScanBoxScale;
	float ScanBoxAlpha;
	QpoVec3d ScanBoxVec;

	float ScanTurnAng,ScanTurnAngAimer,ScanAvatarDist;
	QpoVec3d ScanVecTo,ScanVecToAimer;

	int	MatCounter[10];

	int BlowHeight;

	int React;
	QpoVec3d MoveReactVec;
	float MoveReactSpeed;

	float HitReactScale;
	int	BulletHitCnt;
	int BulletHitCntTimer;

	QpoVertex LaserLV;

	int Blocking;
	int BlockHit;
	int BlockInit;
	int Block;
	int BlockHeight;
	int BlockHeightMeM;

	int	DrawWeapon;
	int WeaponFire;

	int MFlash;
	int NETMFlash;

	float HB_Health;
	float HB_STR_Health;
	float HB_MaxHealth;
	float HB_Armour;
	float HB_STR_Armour;
	float HB_MaxArmour;
	float HB_Energy;
	float HB_STR_Energy;
	float HB_MaxEnergy;
	float HB_STR_POWERBANK;
	int HB_LastAvatarHitID;
	int HB_RecoverMode;
	int HB_Dead;
	int HB_Illumination;
	int HB_EnergyTimer;
	int HB_KillerTeam;
	int HB_Lives;
	int HB_LiveResetSW;

	int VehicleAttach;

	int HB_DmgSTORE;
	int HB_DmgSTORETimer;

	int HB_HReduceON;
	int	HB_ReduceOld;
	int HB_Reduce;
	float HB_ReduceHeight;
	float HB_ReduceHInc;
	QpoRect HB_ReduceRect,HB_ReduceRectFill;
	QpoColor HB_ReduceRectColor;
	float HB_HealthDiff;
	float HB_HealthHistory;

	QpoCollision WallRunCollision;
	int WallRun;
	int WallRunInit;
	int WallRunDir;
	float WallRunHeight;
	int WallRunHeightDir;
	QpoVec3d WallRunOldPos,WallRunNewPos;
	int WallRunDelay;
	QpoVec3d WallRunForward;
	QpoVec3d SurfaceIn,SurfaceLeft,SurfaceUp;
	float WallRunSave;
	int	WallRunSaveInit;
	QpoVec3d WallRunSavePos;
	QpoVec3d WallRunDiff;
	int WallRunTilt;
	int WallRunACTIV;

	float BodyRotation;

	int NomTriEffect;

	Q_Mech Mech;
	Q_TexTriEffectCLS Q_TexTriEffect[300];
	Q_Expandro3D AJPushOff;
	Q_Backpack Backpack;
	Q_TrailLineCLS Trail[100];
};

class Q_Global_AIFlags
{
public:
	AIFlags Forge[QNOMAI];
};

class Q_Global_Update_Pending
{
public:
	Q_Global_Update_Pending()
		{
		acClear();
		}

	void acClear(void)
		{
		m_UpdateReady = false;
		m_UpdateDisplay = false;
		m_CharUpdate = false;
		m_CharEffectsUpdate = false;
		m_CharAttacksUpdate = false;
		m_CharSkillUpdate = false;
		m_ItemUpdate = false;
		m_TXUpdate = false;
		m_CharEditUpdate = false;
		}

	bool m_UpdateReady;
	bool m_UpdateDisplay;
	bool m_CharUpdate;
	bool m_CharEffectsUpdate;
	bool m_CharAttacksUpdate;
	bool m_CharSkillUpdate;
	bool m_CharEditUpdate;
	bool m_ItemUpdate;
	bool m_TXUpdate;

	float m_TXAmt;
};

extern void ag_ApplyUpdate(float f_Sp);

extern QSharedStruct<Q_Global_Update_Pending> playerU[QNOMPLAYER];

extern QSharedStruct<PlayerFlags> player[QNOMPLAYER];

extern QSharedStruct<PlayerFlags> playerSTR[QNOMPLAYER];

extern QSharedStruct<Q_Global_AIFlags> Q_Forge;

};//END namespace GVARS

#endif