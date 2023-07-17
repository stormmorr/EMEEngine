/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component - Q-Initializations -
		-Full Initialization for all external linking variables-

*/

//#### INCLUDE ENGINE SPECIFIC HEADERS
#include "pch.h"

#pragma message ("|^^^ GLOBAL VARIABLE INITIALISATIONS ^^^|")

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"
#include "Q-WE-BulletSystem.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-CloudControl.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-NNbot.h"

#include "cal3d.h"

#include "SDL_keyboard.h"

#pragma message ("|___ GLOBAL VARIABLE INITIALISATIONS ___|")

/////////////////////////////////////////////////////////////////////////////

using namespace GVARS;

namespace GVARS
{

//#####===--- GLOBAL VARIABLE INITIALISATIONS ---===#####

	QSharedStruct<GlobalVariablesStruct> _;

	QSharedStruct<MediaStruct> Medias;

	int LOADED_FACTORY[17];

	QpoVec3d		pos;
	int				Tempint;
	QpoTransform	BoneMat;
	QpoVec3d		qAxis[3];

	QpoVec3d		Origin;

	QpoVec3d		CartMins;
	QpoVec3d		CartMaxs;

	// Entity variables

	QpoLevelEntity				*Entity;
	QpoLevelEntity_EntitySet*	EntSet;
	Q_PlayerEntityDataL*		Q_PlayerEntityData;
	Q_AvatarEntityDataL*		Q_AvatarEntityData;

	// Wall sliding vars
	float Slide;
	unsigned long OldTimeGetTime;
	unsigned long NewTimeGetTime;
	time_t SysTime;
	char *timeline;

	float TIME = 0.0f;

	QpoLightInfo g_Light[NOM_LIGHT];
	int Q_Nom_Light = 0;
	int Q_Nom_Light_Orig = 0;

	int SHADOW,SHADOWX,SHADOWY,SHADOWZ,detcnt,pause,AVSLOT,AVATARCNT,SCRAM,SCRAMJET,helly,aero,jet,helly2,helly3,aero2,jet2,warp,trans;

	bool g_LOAD;
	int g_optionsresult;
	int g_startcommand;
	bool g_QUITM;
	bool g_NetConnect;
	int KeyPRESS01,KeyPRESS02;
	float text1,text2,text3,text4,text5,text6,text7,text8,text9,text10,text11,text12,text13,text14,text15,text16,text17;  // <-- used for text out
	long  Textl;
	float testvalue1,testvalue2,testvalue3,testvalue4,testvalue5,testvalue6,testvalue7,testvalue8;
	float TempDist;
	float Tempfloat1;
	float SpinAmount;
	float TimeFactor;
	int   MatCount,ChanceFinger;
	float UniversalDMGSTR;
	int	  DeliverKOID;
	int	  press,pressN;
	int	  BeeP,BeeP2,i;
	int	  TOBE;
	int	  WEPCHECK;
	int	  NNBOTloop;
	int   ScreenCounter;
	const char * ScreenShot;
	QpoTransform CrunchMatrix,RotateMatrix,RotateMatrix2,RotateMatrix3,SaveMatrix;
	QpoVec3d CrunchIn,CrunchLeft,CrunchUp;
	int Tempint1,Tempint2;
	const char * TempChar1;
	float TestfloatALPHA1,TestfloatALPHA2,TestfloatALPHA3,TestfloatALPHA4,RotAMT;
	QpoVec3d ActorPos,PlayerPos;
	float ActorVisDist;
	int	 TextOutputTest;
	QpoVec3d TestArea,Pos2,Poser,Ange;
	QpoVec3d goup,poop,goup2,scanback,scanfront,bullold,bullnew,test;
	QpoTransform bullrot1,bullrot2,AIfriendly,Xrot90deg,rotmat;
	QpoExtBox fogbox,frogbox;
	QpoRect bmenu,textbox,TempRect1;
	QpoRect robunsel,robsel,mineunsel,minesel,enerbar;
	QpoVertex TVert;
	QpoColor fontcol;
	int			TESTShieldFLAG;
	float		TESTShieldDIST;
	float		TESTDist;
	float		TESTLength;
	QpoVec3d	TESTPosS;
	QpoVec3d	TESTPosE;
	QpoVec3d	WepDisplay;
	QpoVertex   *TestPYRO;
	QpoVertex   TestLVERT;
	QpoFont     *font1;
	QpoVertex   *mine,*pollie;
	QpoVertex   FVert;
	const char *BoneDef[50];
	int qBoneNum[50];
	QpoVec3d qCorner,qDX,qDY,qDZ;
	QpoVector pCorner,coldetresult;
	QpoBox Box;
	QpoVectorBox ColldetBox;
	float qxScale,qyScale,qzScale;
	QpoTransform bonepos;
	QpoBoneCollisionInfo BoneCollisionInfo;
	float chit,mvlength;
	QpoBody *LisaBody;
	QpoBody *Shibody;
	QpoMotionPath  *RPath;
	int  RMotion;
	QpoTransform ReactPos,ParentPos,qAttachment;
	int qParBone;
	int numparents;
	int child;
	const char *qBoneName;
	QpoTransform WorldXF,BoneXF;
	QpoVec3d WorldIn,BoneIn,BoneXFIn,SpinIn;
	QpoVec3d AxeStart,AxeEnd,AxeVec;
	QpoVec3d BoneMatrixX,BoneMatrixY,BoneMatrixZ;
	QpoVec3d WorldX,WorldY,WorldZ;
	QpoVec3d Shift;
	QpoTransform BoneMatrix;
	int BTbonenum;
	QpoVec3d Vectorn,Xv,Yv,Zv;
	QpoTransform Boneposs;
	float lengthvec;
	int timeoffset;
	QpoLight playerlight;
	int sunriseF;
	float sunrise;
	int count;
	float red,green,blue;
	QpoExtBox GBBox;
	QpoRect Brushrect,ItemBrushrect;
	QpoColor BrushRGBA;
	QpoVec3d BrushVec;
	QpoVec3d tempPOS,tempPOS2;
	int tempALPHA;
	int noot;
	int Temp;
	float shir,shig,shib;
	int	 nameplateno,nameplatedir;
	int MFlash;
	int aerop;
	int tempint1,tempint2;
	QpoFog	*Fogo;
	float TimeCounter;
	int	AIcount,AItempcnt;
	QpoVec3d TempVec1,TempVec2,TempVec3,TempVec4,TempVec6,TempVec7;
	QpoVec3d ScanVecTo,ScanTurnVec,ScanTurnVecAimer;
	float ScanObjAng,ScanDistL,ScanDistR,ScanAvatarDist;
	int		ScanID;
	int KeyDepress,KeyDepress2;
	int BrainLOOP,LoopON;
	float VisClipDist;
	float TriEffectUb,TriEffectUt;
	QpoBuffer_Data	SendBuffer;
	float tempForwardSpeed;
	QpoVec3d tempAngles;
	float NetTime;
	QInt	*BufferLoad;
	int		CharCounter;
	POINT temppos,tempposSTR,mpos;
	float TURN_SPEED;
	float UPDOWN_SPEED;
	float Tempfloat;
	bool TimeAlter;
	bool KeyCheck;
	int ApplicationFocus;

	//### Vapor Trails Variables

	QpoVec3d	qcross;
	int			NumQuads,major;
	float		Width1, Width2;
	QpoVec3d	Drift;
	QpoColor	ColourSTART,ColourEND;
	QpoVec3d	AvatarPos;
	QpoVec3d	DistVec;
	float		AvatarDist;
	QpoVec3d	TestVec1,TestVec2,TestVec3,TestVec4,TestVec5,TestVec6,TestVec7;

	//### TEMP CHAR-DATA

	QInt			TEMP_CurrCHAR;
	QInt			TEMP_NomAvatars;
	Q_AVATARS		TEMP_AVATARDATA[50];
	QInt			TEMP_playerTEAM;
	char			TEMP_PlayerWEP[21],TEMP_AvatarWEP[50][21];
	char			TEMP_PlayerACT[21],TEMP_PlayerSACT[21],TEMP_AvatarACT[50][21],TEMP_AvatarSACT[50][21];
	int				TEMP_AvatarCLASS[50];
	int				STRcompare;
	Q_AngelEDIT		TEMP_AngelCOLOURS;
	int				MechKEYPRESS;
	int				ScanKEYPRESS;
	int				EnMatX,EnMatY,EnMatZ;
	int				EnMatX2,EnMatY2,EnMatZ2;
	QpoAvExtBox		bonebox,bonebox1,bonebox2,bonebox3,boneboxR;

		 // ~Object loading counters~

	int				TEXcounter = 0;
	int				MESHcounter = 0;

	QpoVec3d			qLeftToRightESCAN;
	QpoVec3d			qEnemyLeft,qEnemyRight,qEnemyUp,qEnemyDown,qEnemy,qEyes;
	int					qTargetFound;

	QpoCollision		qRayTraceCOLL;

	//######- SUB SYSTEM GLOBALS -######

	std::map< const char * , int > m_StructureA;

	//######- QAGE GLOBALS -######

	QSharedStruct<QpoAvatarFlags>			playerAV[QNOMPLAYER];

	QSharedStruct<PlayerFlags>				player[QNOMPLAYER];

	QSharedStruct<Q_Global_Update_Pending>  playerU[QNOMPLAYER];

	QSharedStruct<PlayerFlags>				playerSTR[QNOMPLAYER];

	QSharedStruct<Q_Global_AIFlags>			Q_Forge;

	QSharedStruct<NNBOTrewardSTATSCLS>		NNBOTrewardSTATS;

	QSharedStruct<Q_Global_NNBot>			Q_NNBot;

	QSharedStruct<Q_Global_PntSprite>		Q_PntSprite;

	QSharedStruct<Q_Global_SEnergy>			Q_SEnergy;

	QSharedStruct<Q_Global_PowerBlade>		Q_PowerBlade;

	QSharedStruct<Q_Global_LEnergy>			Q_LEnergy;

	QSharedStruct<Q_Global_Explosion>		Q_Explosion;

	QSharedStruct<Q_Global_ClericPlasma>	Q_ClericPlasma;

	QSharedStruct<Q_Global_ClericSpell>		Q_ClericSpell;


	QSharedStruct<Q_Global_BMSentry> Q_BMSentry;

	QSharedStruct<Q_Global_QBuilding> Q_Building;

	QSharedStruct<Q_Global_Object> Q_Object;

	QSharedStruct<Q_Global_DMG_Mask> Q_VoxelDamage;


		 // ~From Q-Structs.h~

	QSharedStruct<Q_Global_MeMPathway> Q_MeMPathway;

	QSharedStruct<Q_Global_Lightning> Q_Lightning;

	QSharedStruct<Q_Global_EnergyWake> Q_EnergyWake;

	QSharedStruct<Q_Global_NetEffectControl> Q_NetEffectControl;

	QSharedStruct<Q_Global_HealEnergy> Q_HealEnergy;

	QSharedStruct<Q_Global_NetZoneENTITY> Q_NetZoneENTITY;

	QSharedStruct<Q_Global_StartPoints> Q_StartPoints;

	QSharedStruct<Q_Global_ANGELeditMAP> Q_ANGELeditMAP;

	QSharedStruct<Q_Global_AvatarEntity> Q_AvatarEntity;

	QSharedStruct<Q_Global_Netplayer> Q_Netplayer;

	QSharedStruct<Q_Global_PlayerEntity> Q_PlayerEntity;

			 // ~From Q-WE-BulletSystem.h~

	QSharedStruct<Q_Global_Bullet> Q_Bullet;

	QSharedStruct<Q_Global_BulletHit> Q_BulletHit;

	QSharedStruct<Q_Global_Cartridge> Q_Cartridge;

	QSharedStruct<Q_Global_MFlash> Q_MFlash;


	QSharedStruct<Q_Global_Cloud> Q_Cloud;

	QSharedStruct<Q_Global_EnergyMatrix> Q_EnergyMatrix;

	QSharedStruct<Q_Global_MeleeHit> Q_MeleeHit;

			// ~From Q-WE-WorldEffects.h~

	QSharedStruct<Q_Global_BBlood> Q_BBlood;

	QSharedStruct<Q_Global_PowerFlash> Q_PowerFlash;

	QSharedStruct<Q_Global_Spike> Q_HHSpike;

	QSharedStruct<Q_Global_HSpark> Q_HealSpark;

	QSharedStruct<Q_Global_Spark> Q_BSparks;

	QSharedStruct<Q_Global_VaporTrail> Q_VaporTrail;

	QSharedStruct<Q_Global_WindWake> Q_WindWake;

	QSharedStruct<Q_Global_PinEffectMesh> Q_PinEffectMesh;

	QSharedStruct<Q_Global_Decal> Q_Decal;

#if defined(WIN32)
#if 0
	int KEY_DOWNe(int QIN_code)
		{
		if(ApplicationFocus)
			{
			const Uint8 *keystate = SDL_GetKeyboardState(NULL);
			if(keystate[QIN_code]) return true;
			else return false;
			}
		else return false;
		}

	int KEY_UPe(int QIN_code)
		{
		if(ApplicationFocus)
			{
			const Uint8 *keystate = SDL_GetKeyboardState(NULL);
			if(keystate[QIN_code]) return false;
			else return true;
			}
		else return false;
		}
	using namespace Windows::UI::Core;
	using namespace Windows::System;
	int KEY_DOWN_we(void)
		{
		return 1;
		}

	int KEY_DOWN_se(void)
		{
		if(ApplicationFocus)
			{
#if 0 //QAGE_DESKTOP
			if((GetAsyncKeyState(QIN_DOWN) & 0x8000) ? 1 : 0) return 1;
			if((GetAsyncKeyState(QIN_s) & 0x8000) ? 1 : 0) return 1;
#else
			const Uint8 *keystate = SDL_GetKeyboardState(NULL);
			if (keystate[QIN_s]) return true;
			else if (keystate[QIN_DOWN]) return true;
			else return false;
#endif
			}
		else return 0;
		}

	int KEY_DOWN_ae(void)
		{
		if(ApplicationFocus)
			{
#if 0 //QAGE_DESKTOP
			if((GetAsyncKeyState(QIN_LEFT) & 0x8000) ? 1 : 0) return 1;
			if((GetAsyncKeyState(QIN_a) & 0x8000) ? 1 : 0) return 1;
#else
			const Uint8 *keystate = SDL_GetKeyboardState(NULL);
			if (keystate[QIN_a]) return true;
			else if (keystate[QIN_LEFT]) return true;
			else return false;
#endif
			}
		else return 0;
		}

	int KEY_DOWN_de(void)
		{
		if(ApplicationFocus)
			{
#if 0 //QAGE_DESKTOP
			if((GetAsyncKeyState(QIN_RIGHT) & 0x8000) ? 1 : 0) return 1;
			if((GetAsyncKeyState(QIN_d) & 0x8000) ? 1 : 0) return 1;
#else
			const Uint8 *keystate = SDL_GetKeyboardState(NULL);
			if (keystate[QIN_d]) return true;
			else if (keystate[QIN_RIGHT]) return true;
			else return false;
#endif
			}
		else return 0;
		}
#endif
#endif

	void ag_ApplyUpdate(float f_Sp)
	{
		playerU[0]->m_UpdateReady = true;
		playerU[0]->m_UpdateDisplay = true;
		playerU[0]->m_ItemUpdate = true;
		playerU[0]->m_CharUpdate = true;
		//TX

		if(f_Sp > 0.0f)
			{
			float f_MiniSp = f_Sp / 5000.0f;
			playerU[0]->m_TXUpdate = true;
			playerU[0]->m_TXAmt = f_MiniSp * (50.0f / g_Wallet->m_Reward);
			}
		//f_Sp
	}


	QSharedStruct<PlacementMarker> Q_PlacementMarker;

};