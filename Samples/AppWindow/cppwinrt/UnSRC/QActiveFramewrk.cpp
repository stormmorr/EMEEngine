/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- QAGE MAIN ENTRY FILE-

*/

#include "pch.h"
#include <cassert>
#include <iostream>

#include "QActiveFramewrk.h"
#include "Physics/Timing.h"

#if 0
#include "Utility/SenseMatrix.h"
UN::SenseMatrix f_SenseMatrix;
#endif

#if 1
#define AVATAR_PHYSICS_ENABLE 1
#else
#define AVATAR_PHYSICS_ENABLE 0
#endif

#if 0
#define QAGE_OPMOD_B 1
#endif

#if 1
#define QAGE_OPMOD_SAFE 1
#endif

extern QAGE::QActiveFramewrk *QActiveFrameWork;

//Original Main
extern std::string meshfile1;	// geometry file

 //p3dscene3
extern std::string meshfile2;	// geometry file

 //Heknoblock
extern std::string meshfile3;	// geometry file

 //Faction_Meat
extern std::string meshfile4;	// geometry file

 //Play_Pen
extern std::string meshfile5;	// geometry file

 //Gas_Factory
extern std::string meshfile6;	// geometry file

HANDLE CreateFileMappingA()
{
	HANDLE f_go = new int();
	return f_go;
}

namespace QAGE
{

QActiveFramewrk* QActiveFramewrk::s_instance = 0;
QActiveFramewrk* QActiveFramewrk::instance()
{
	return s_instance;
}

QActiveFramewrk::QActiveFramewrk() :
m_trrCursorActive(false),
m_trrToolCutter(0),
m_trrToolLevel(0),
m_trrToolRaise(0),
m_trrToolSmooth(0),	//FIXME move to game init
m_trrUpdate(1),
m_trrCursorType(0),
m_trrCursorAlpha(0),
m_PP_STATE(0),
m_trrToolScale(200),
gMouseDepth(150),
gPickStay(false),
m_NetStart(false)
{
	assert(s_instance == 0);
	s_instance = this;

	m_BuildLight.m_ON = false;

#if 0
	trrcursor = new unPointLocator();

	acBanner();
#endif

	m_NomDataMesh = 0;
	m_NomDataBodyMesh = 0;

	mMaxDist = 0;

#if 0
	m_QSpawnPntController = new QSpawnPntController();
#endif
}

QActiveFramewrk::~QActiveFramewrk()
{
	s_instance = 0;
}

void QActiveFramewrk::acBanner(void)
{
#if 0
	unConsoleAttribute(CONSOLE_MSG);
	printf("QAGE:::...Quantum Angel Gaming Engine v3.4.0.0\n");
	printf("Copyright OSIREM (C) 2007 osirem.com\n");
	printf("UNIFICATION:::...Graphics Server Engine... Starting QActiveFrameWork\n");
	printf("Quantum Angel Arena...QA_Arena v2.3.0.0... qage.org\n");
	unConsoleAttribute(CONSOLE_INIT);
#endif

	//##### Unification Console #####//
#if 0
	pString str1;
	str1.format("Quantum Angel Gaming Engine v1.00.00");
	g_unConsole_vec_str.push_back(str1.getbuf());
	g_unC_vec_ind.push_back(g_unCoutcnt);
	g_unCoutcnt++;
	pString str2;
	str2.format("     unConsole output moderate");
	g_unConsole_vec_str.push_back(str2.getbuf());
	g_unC_vec_ind.push_back(g_unCoutcnt);
	g_unCoutcnt++;
	pString str3;
	str3.format("     copyright 2006 OSIREM Ltd - www.osirem.com");
	g_unConsole_vec_str.push_back(str3.getbuf());
	g_unC_vec_ind.push_back(g_unCoutcnt);
	g_unCoutcnt++;
#endif
	//##### Unification Console #####//
}

bool QActiveFramewrk::acActiveInit(void)
{
	_->FRLfirst = 0;

	m_texturebank = new unTextureBank;

#ifndef QAGEMODE_NOLOGO
	m_texturebank->acInit();
#endif

#ifndef QAGEMODE_NOLOGO
	g_LOAD = false;
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	/// QAGE Initialisation
#if 1
	acQAInit();
#else
#ifdef QAGE_OPMOD_SAFE
	if(!acAmpInit())
		{
		//*unConsoleAttribute(CONSOLE_ERROR);
		printf("ERROR:::acAmpInit - return not reached.\n");
		//*unConsoleAttribute(CONSOLE_INIT);
		for(;;) {}
		}
#else
	acRecieveInit();
#endif
#endif

#if 0
	if(!e_CTrueRandom->Initialize()) printf("Q-Active FrameWork:::ERROR:::TrueRandom failed to initialize\n");
#else

		//Seed the random generator with the time
#if defined(WIN32)
	time_t f_time;
	time(&f_time);
	srand(f_time);
#else
	srand( (unsigned)time(NULL) );
#endif

#endif

	return true;
}

void QActiveFramewrk::acShutdown()
{
	int f_iter;
	for(f_iter = 0; f_iter < meshBank.size(); f_iter++)
		{
		meshBank[f_iter]->acShutdown();
		}

#if 0
	for(f_iter = 0; f_iter < meshTemplates.size(); f_iter++)
		{
		meshTemplates[f_iter]->acShutdown();
		}
#endif

	for(f_iter = 0; f_iter < meshShellTemplates.size(); f_iter++)
		{
#if 0
		meshShellTemplates[f_iter]->acShutdown();
#endif
		}

	for(f_iter = 0; f_iter < meshstaticTemplates.size(); f_iter++)
		{
		meshstaticTemplates[f_iter]->acShutdown();
		}

	for(f_iter = 0; f_iter < meshVehicleTemplates.size(); f_iter++)
		{
		meshVehicleTemplates[f_iter]->acShutdown();
		}

}

void QActiveFramewrk::acRenderFrame(void)
{
	if(!g_LOAD) g_render->clear();

#if 0
    acGameEventsFrame();
#endif

	if(!g_LOAD) g_render->end_draw();
}

void QActiveFramewrk::acQAInit(void)
{
#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	
	/////// Load Character Data ///////
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

#if 0
		Q.LoadCharacterDataLegacy();
#endif

		/////// Prepare Character Data ///////
#if 1
		Q.StartCharacterData();
#endif

#if 0
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight = 70;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height = 70;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower = 100;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower = 50;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution = 50;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity = 50;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff = 10050;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence = 10050;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr = 150;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness = 100;
#endif

		player[g_Player]->QformChk = false;

		// Trail Fade Vars *****************************************************************************************
		//**********************************************************************************************************

		player[g_Player]->TrailFadeSpan[0][0] = 0;
		player[g_Player]->TrailFadeSpan[1][0] = 0;
		player[g_Player]->TrailFadeSpan[2][0] = 0;
		player[g_Player]->TrailFadeSpan[3][0] = 0;
		player[g_Player]->TrailFadeSpan[4][0] = 0;
		player[g_Player]->TrailFadeSpan[5][0] = 0;
		player[g_Player]->TrailFadeSpan[6][0] = 0;
		player[g_Player]->TrailFadeSpan[7][0] = 0;
		player[g_Player]->TrailFadeSpan[8][0] = 0;
		player[g_Player]->TrailFadeSpan[9][0] = 0;
		player[g_Player]->TrailFadeSpan[0][1] = 0;
		player[g_Player]->TrailFadeSpan[1][1] = 1;
		player[g_Player]->TrailFadeSpan[2][1] = 2;
		player[g_Player]->TrailFadeSpan[3][1] = 3;
		player[g_Player]->TrailFadeSpan[4][1] = 4;
		player[g_Player]->TrailFadeSpan[5][1] = 5;
		player[g_Player]->TrailFadeSpan[6][1] = 6;
		player[g_Player]->TrailFadeSpan[7][1] = 7;
		player[g_Player]->TrailFadeSpan[8][1] = 8;
		player[g_Player]->TrailFadeSpan[9][1] = 9;

		player[g_Player]->BFO.CurrCHAR = 0;

		player[g_Player]->Mposestate = 0;
		player[g_Player]->idlemotion = 0;
		player[g_Player]->AirJinkRotFG = 0;
		}

	g_Player = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	_->Volume = 1.0f;
	
	_->screenx = g_Width;
    _->screeny = g_Height;
	mpos.x = _->screenx/2;
	mpos.y = _->screeny/2;

	_->Origin.x = 0;
	_->Origin.y = 0;
	_->Origin.z = 0;

	_->GenericLightPos.x = 0;
	_->GenericLightPos.y = -250;
	_->GenericLightPos.z = 0;

	//### LOAD INTRO
	_->GameTypeSelect = 1;

	LOADED_FACTORY[4] = 0;
	LOADED_FACTORY[5] = 0;
	LOADED_FACTORY[6] = 0;
	LOADED_FACTORY[7] = 0;
	LOADED_FACTORY[8] = 0;
	LOADED_FACTORY[9] = 0;
	LOADED_FACTORY[10] = 0;
	LOADED_FACTORY[11] = 0;
	LOADED_FACTORY[12] = 0;
	LOADED_FACTORY[13] = 0;
	LOADED_FACTORY[14] = 0;

// Define Bone Names / Numbers *****************************************************************************
//**********************************************************************************************************
								//OPTIMISE  Remove bones not needed
	BoneDef[0] = "BIP01 HEAD";
	BoneDef[1] = "BIP01 L CALF";
	BoneDef[2] = "BIP01 L CLAVICLE";
	BoneDef[3] = "BIP01 L FOOT";
	BoneDef[4] = "BIP01 L FOREARM";
	BoneDef[5] = "BIP01 L HAND";
	BoneDef[6] = "BIP01 L THIGH";
	BoneDef[7] = "BIP01 L UPPERARM";
	BoneDef[8] = "BIP01 NECK";
	BoneDef[9] = "BIP01 PELVIS";
	BoneDef[10] = "BIP01 R CALF";
	BoneDef[11] = "BIP01 R CLAVICLE";
	BoneDef[12] = "BIP01 R FOOT";
	BoneDef[13] = "BIP01 R FOREARM";
	BoneDef[14] = "BIP01 R HAND";
	BoneDef[15] = "BIP01 R THIGH";
	BoneDef[16] = "BIP01 R UPPERARM";
	BoneDef[17] = "BIP01 SPINE";
	BoneDef[18] = "BIP01 SPINE1";
	BoneDef[19] = "BIP01 SPINE2";
	//BoneDef[20] = "BIP01 SPINE3";
	BoneDef[20] = "BIP01 SPINE2";
	
	Q.StructureAInitialize();

	qBoneNum[0] = 8;			//THIS NEEDS CHECKING <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	qBoneNum[1] = 48;
	qBoneNum[2] = 9;
	qBoneNum[3] = 49;
	qBoneNum[4] = 11;
	qBoneNum[5] = 12;
	qBoneNum[6] = 47;
	qBoneNum[7] = 10;
	qBoneNum[8] = 7;
	qBoneNum[9] = 2;		//<-May be 1 or 0
	qBoneNum[10] = 52;
	qBoneNum[11] = 28;
	qBoneNum[12] = 53;
	qBoneNum[13] = 30;
	qBoneNum[14] = 31;
	qBoneNum[15] = 51;
	qBoneNum[16] = 29;
	qBoneNum[17] = 3;
	qBoneNum[18] = 4;
	qBoneNum[19] = 5;
	//qBoneNum[20] = 6;
	qBoneNum[20] = 5;

// Define Angel Edit Pointer *******************************************************************************
//**********************************************************************************************************

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[0].MAPNAME, "Hair");
	Q_ANGELeditMAP->ANGELeditMAP[0].MAPPOINTER = 3;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[1].MAPNAME, "Shoulders");
	Q_ANGELeditMAP->ANGELeditMAP[1].MAPPOINTER = 30;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[2].MAPNAME, "Face");
	Q_ANGELeditMAP->ANGELeditMAP[2].MAPPOINTER = 4;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[3].MAPNAME, "Left Ear");
	Q_ANGELeditMAP->ANGELeditMAP[3].MAPPOINTER = 5;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[4].MAPNAME, "Right Ear");
	Q_ANGELeditMAP->ANGELeditMAP[4].MAPPOINTER = 0;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[5].MAPNAME, "Nose");
	Q_ANGELeditMAP->ANGELeditMAP[5].MAPPOINTER = 10;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[6].MAPNAME, "Mouth");
	Q_ANGELeditMAP->ANGELeditMAP[6].MAPPOINTER = 11;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[7].MAPNAME, "Left Eye Socket");
	Q_ANGELeditMAP->ANGELeditMAP[7].MAPPOINTER = 7;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[8].MAPNAME, "Left Eye");
	Q_ANGELeditMAP->ANGELeditMAP[8].MAPPOINTER = 6;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[9].MAPNAME, "Right Eye Socket");
	Q_ANGELeditMAP->ANGELeditMAP[9].MAPPOINTER = 9;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[10].MAPNAME, "Right Eye");
	Q_ANGELeditMAP->ANGELeditMAP[10].MAPPOINTER = 8;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[11].MAPNAME, "Neck");
	Q_ANGELeditMAP->ANGELeditMAP[11].MAPPOINTER = 12;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[12].MAPNAME, "Left Hand");
	Q_ANGELeditMAP->ANGELeditMAP[12].MAPPOINTER = 15;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[13].MAPNAME, "Butt Skin");
	Q_ANGELeditMAP->ANGELeditMAP[13].MAPPOINTER = 33;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[14].MAPNAME, "BackPack");
	Q_ANGELeditMAP->ANGELeditMAP[14].MAPPOINTER = 25;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[15].MAPNAME, "Boot Tongues");
	Q_ANGELeditMAP->ANGELeditMAP[15].MAPPOINTER = 26;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[16].MAPNAME, "Boot Soles");
	Q_ANGELeditMAP->ANGELeditMAP[16].MAPPOINTER = 27;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[17].MAPNAME, "Left Arm");
	Q_ANGELeditMAP->ANGELeditMAP[17].MAPPOINTER = 13;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[18].MAPNAME, "Right Hand");
	Q_ANGELeditMAP->ANGELeditMAP[18].MAPPOINTER = 17;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[19].MAPNAME, "Left Forearm");
	Q_ANGELeditMAP->ANGELeditMAP[19].MAPPOINTER = 14;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[20].MAPNAME, "Right Forearm");
	Q_ANGELeditMAP->ANGELeditMAP[20].MAPPOINTER = 1;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[21].MAPNAME, "Right Arm");
	Q_ANGELeditMAP->ANGELeditMAP[21].MAPPOINTER = 16;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[22].MAPNAME, "Left Boot");
	Q_ANGELeditMAP->ANGELeditMAP[22].MAPPOINTER = 19;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[23].MAPNAME, "Left Calf");
	Q_ANGELeditMAP->ANGELeditMAP[23].MAPPOINTER = 18;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[24].MAPNAME, "Left Thigh Band");
	Q_ANGELeditMAP->ANGELeditMAP[24].MAPPOINTER = 32;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[25].MAPNAME, "Collar");
	Q_ANGELeditMAP->ANGELeditMAP[25].MAPPOINTER = 34;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[26].MAPNAME, "Chest");
	Q_ANGELeditMAP->ANGELeditMAP[26].MAPPOINTER = 23;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[27].MAPNAME, "Stomach");
	Q_ANGELeditMAP->ANGELeditMAP[27].MAPPOINTER = 24;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[28].MAPNAME, "Right Boot");
	Q_ANGELeditMAP->ANGELeditMAP[28].MAPPOINTER = 20;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[29].MAPNAME, "Right Calf");
	Q_ANGELeditMAP->ANGELeditMAP[29].MAPPOINTER = 2;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[30].MAPNAME, "Left Thigh");
	Q_ANGELeditMAP->ANGELeditMAP[30].MAPPOINTER = 21;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[31].MAPNAME, "Right Thigh");
	Q_ANGELeditMAP->ANGELeditMAP[31].MAPPOINTER = 22;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[32].MAPNAME, "Head Aerials");
	Q_ANGELeditMAP->ANGELeditMAP[32].MAPPOINTER = 28;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[33].MAPNAME, "Right Thigh Band");
	Q_ANGELeditMAP->ANGELeditMAP[33].MAPPOINTER = 31;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[34].MAPNAME, "Boot Front");
	Q_ANGELeditMAP->ANGELeditMAP[34].MAPPOINTER = 29;

// Bitmap init *********************************************************************************************
//**********************************************************************************************************

	//#### TEXTURE SETUP
#ifndef QAGEMODE_NOEFFECTS
	Q.InitTextures();
#endif
	
#if 0
	Q.BlatTextures();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	time_t f_time2;
	time(&f_time2);

	g_starttime = f_time2;

//**********************************************************************************************************
//**********************************************************************************************************

	::Qpo->Transform_New_XRotation(&Xrot90deg, -(PI/2));

// Setup World / Load entities *****************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

	//### Load Player Start Point

	//### TODO Create Level Far clip distance Entity ###
	VisClipDist	= 2000;

	_->NomAI = 0;
	
#if 1
	_->NetworkOption = 0;
#else
	_->NetworkOption = 2;
#endif
	
#pragma message ("SET - _->NomAI, CURRCHAR, _->NetworkOption")
#pragma message ("FIXME: Fake Library Data")

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

	player[g_Player]->BFO.GAMEOPTIONS.FrameratelimiterON = 1;

	_->FRL_LIMIT = 15;

	for(int i = 0; i < _->NomAI; i++)
		{
		player[g_Player]->BFO.AVATARDATA[i].LIVE = 1;
		}

//**********************************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

// Setup the player ########################################################################################
//##########################################################################################################
//##########################################################################################################

	// Setup the player specific flags
	player[g_Player]->PlayerHeight = PLAYER_HEIGHT;
	player[g_Player]->PlayerSpeed = PLAYER_SPEED;
	player[g_Player]->ForwardSpeed = 0;
	player[g_Player]->upspeed = -15;
	player[g_Player]->camrotdist = 1000;
	player[g_Player]->GravityAlter = 1;
	player[g_Player]->AirJinkPrep = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 0
	Q.WriteMeMPathways();
#endif

#if 0
	Q.ReadMeMPathways();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//#### ENERGY MATRIX SETUP
	Q_EnergyMatrix->EnergyMatrix.GlobalSCALE = 100;

	player[g_Player]->EnergyArchitect.ExpandSTRENGTH = 1.15;
	TestfloatALPHA1 = 7.149;
	TestfloatALPHA2 = 1.15;

	_->WorldScale = 1;

	player[g_Player]->Invisible = 0;

	player[g_Player]->Team = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].TEAM;

	//Player Level
	player[g_Player]->LEVEL = 1;

	//Fill Weapon Ammo
	player[g_Player]->WeaponAmmo = 32;
	
	player[g_Player]->Mins.x = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
    player[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    player[g_Player]->Mins.z = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.x = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.z = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->upspeed = 0;

	playerAV[g_Player]->Mins.x = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
    playerAV[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    playerAV[g_Player]->Mins.z = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.x = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.z = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//ACTOR SETUP AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	
	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);

	player[g_Player]->HB_Armour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	player[g_Player]->HB_MaxArmour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	player[g_Player]->HB_MaxHealth = 1000 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/100)*0.6)+0.4);
	player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;

	//player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

	player[g_Player]->JINK3_PowerFactor = 1;
	}

	g_Player = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 0
	"Avatar/Lisa.cfg"
	"Avatar/MellodiData.cfg"
	"Avatar/AssassinData.cfg"
	"Avatar/ShortSkirtBikini.cfg"
	"Avatar/ShortSkirtBikiniData.cfg"
	"Avatar/TemplateData.cfg"
#endif

	unMesh *f_mesh = new unMesh();

	if(!f_mesh->acCreate("Assets/Avatar/Lisa.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);

#if 0
	f_mesh = new unMesh();

	if(!f_mesh->acCreate("Assets/Avatar/Lisa.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);
#endif

	f_mesh = new unMesh();

	if(!f_mesh->acCreate("Assets/Avatar/Mellodi.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}


	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);

	f_mesh = new unMesh();

	if(!f_mesh->acCreate("Assets/Avatar/Assassin.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}


	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);

#if 0
	f_mesh = new unMesh();

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtBikini.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}


	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);
#endif

#if 1
	f_mesh = new unMesh();

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtBikini.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}


	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);
#endif

#if 0
	if(!f_mesh->acCreate("Assets/Avatar/Template.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}


	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);
#endif

	f_mesh = new unMesh();
	
	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtGloves.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshBank.push_back(f_mesh);

#if 0
	unMeshStatic *f_MeshStatic = new unMeshStatic();

	if(!f_MeshStatic->onCreate("Assets/Mesh/Energy/Renzou.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_MeshStatic);
#endif

#if 0	// Swat552X
	unMeshStatic *f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/Swat552X.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// famassvX
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/famassvX.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// IncaMKII
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/IncaMKII.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// MiniGun
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/MiniGun1.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// M4A1actr
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/M4A1actr.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// Swat552X
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/Swat552X.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// MiniGun
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/ak47lowq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// psg1lowq
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/psg1lowq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// spas12lq
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/spas12lq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// g3lowqua
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/g3lowqua.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// l96a1low
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/l96a1low.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// w_awp10
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/w_awp10.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0	// Weapon Test
	unMeshStatic *f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/w_awp10.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/FordGT40.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif

#if 0
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/Ducati.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//#### RENZOU
	aero=0;
	while(aero < 150)
		{
		helly=0;
		while(helly < 5)
			{
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Avatar = 0;

			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.x = 1;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.y = 1;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.z = 1;

			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.x = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.y = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.z = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.x = 20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.y = 20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.z = 20.f;

#if 0
			Qpo->Avatar_SetScale(&Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Avatar, 4, 4, 4);
#endif

			Qpo->Vec3d_Copy(&_->Origin, &Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Xform.Translation);

#if 0
#ifndef QAGEMODE_NOINTRO
			acNamePlateUpdate();
#endif
#endif
			helly++;
			}

		Q_SEnergy->SEnergy[aero].Const_TurnDull = 2500;
		//Q_SEnergy->SEnergy[aero].Const_TurnDull = 50000;

		Q_SEnergy->SEnergy[aero].Const_AngleInc = 0.2;
		//Q_SEnergy->SEnergy[aero].Const_AngleInc = 1;

#if 0
#ifndef QAGEMODE_NOINTRO
		acNamePlateUpdate();
#endif
#endif

#if 1	//Small Energy Switch
		_->MaxNomSEnergy++;
#endif

		aero++;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	
#if 1
	if(1)	//Hadouken
		{
		aero=1;
		while(aero < (_->NomAI * 2))	//aero < (_->NomAI) <--- History
			{
			Q_LEnergy->LEnergy[aero].EnergyBall.Avatar = 0;

			Q_LEnergy->LEnergy[aero].EnergyBall.Mins.x = -20.f;
			Q_LEnergy->LEnergy[aero].EnergyBall.Mins.y = -20.f;
			Q_LEnergy->LEnergy[aero].EnergyBall.Mins.z = -20.f;
			Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.x = 20.f;
			Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.y = 20.f;
			Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.z = 20.f;

			Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[aero].EnergyBall, 40, 40, 40);

			Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[aero].EnergyBall, 150);

			Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation);

#ifndef QAGEMODE_NOINTRO
			acNamePlateUpdate();
#endif

			_->MaxNomLEnergy++;
			aero++;
			}
		}
#endif

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

#pragma message ("FIXME:::Start Player Start Position")
	playerAV[g_Player]->Avatar.Mesh = new unAvatar();

	if(AVATAR_PHYSICS_ENABLE) meshBank[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh);
	else meshBank[0]->clone_struct(playerAV[g_Player]->Avatar.Mesh);

#if defined(ENABLE_NX_PHYSICS)
#if 0
	playerAV[g_Player]->Avatar.Mesh->addClothAttachment(meshTemplates[0]->m_Cloth[0], 0, 0, 0);
#endif
#endif

	playerAV[g_Player]->Xform.Translation.x = AV_START_X;
	playerAV[g_Player]->Xform.Translation.y = AV_START_Y;
	playerAV[g_Player]->Xform.Translation.z = AV_START_Z;

	playerAV[g_Player]->Xform.Matrix.load_identity();

	player[g_Player]->KL_Timer = 0;
	player[g_Player]->KL_BTimer = 0;

	player[g_Player]->WeaponStatus = 0;

	//##### Starting position
	Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
	//Ange.y=-(PI/2);//Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
	Ange.y = PI; // Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);

	if(Ange.y > (2.0f * PI)) Ange.y = Ange.y - (PI*2);
	Ange.x = -(PI / 2.0f);
	Ange.z = 0.0f;

	// Set the actor's angle
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, Ange.x);
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, Ange.y);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Ange.z);

#if 0
	QpoTransform f_Transform;

	Qpo->Transform_New(&f_Transform);

	f_Transform.Matrix.load_identity();

	player[g_Player]->ViewXForm = f_Transform;
#else
	player[g_Player]->ViewXForm.Matrix.mf[0] = player[g_Player]->Xform.Matrix.mf[0];
	player[g_Player]->ViewXForm.Matrix.mf[1] = player[g_Player]->Xform.Matrix.mf[1];
	player[g_Player]->ViewXForm.Matrix.mf[2] = player[g_Player]->Xform.Matrix.mf[2];
	player[g_Player]->ViewXForm.Matrix.mf[3] = player[g_Player]->Xform.Matrix.mf[3];

	player[g_Player]->ViewXForm.Matrix.mf[4] = player[g_Player]->Xform.Matrix.mf[4];
	player[g_Player]->ViewXForm.Matrix.mf[5] = player[g_Player]->Xform.Matrix.mf[5];
	player[g_Player]->ViewXForm.Matrix.mf[6] = player[g_Player]->Xform.Matrix.mf[6];
	player[g_Player]->ViewXForm.Matrix.mf[7] = player[g_Player]->Xform.Matrix.mf[7];

	player[g_Player]->ViewXForm.Matrix.mf[8] = player[g_Player]->Xform.Matrix.mf[8];
	player[g_Player]->ViewXForm.Matrix.mf[9] = player[g_Player]->Xform.Matrix.mf[9];
	player[g_Player]->ViewXForm.Matrix.mf[10] = player[g_Player]->Xform.Matrix.mf[10];
	player[g_Player]->ViewXForm.Matrix.mf[11] = player[g_Player]->Xform.Matrix.mf[11];

	player[g_Player]->ViewXForm.Matrix.mf[12] = player[g_Player]->Xform.Matrix.mf[12];
	player[g_Player]->ViewXForm.Matrix.mf[13] = player[g_Player]->Xform.Matrix.mf[13];
	player[g_Player]->ViewXForm.Matrix.mf[14] = player[g_Player]->Xform.Matrix.mf[14];
	player[g_Player]->ViewXForm.Matrix.mf[15] = player[g_Player]->Xform.Matrix.mf[15];

	player[g_Player]->ViewXForm.Translation.x = player[g_Player]->Xform.Translation.x;
	player[g_Player]->ViewXForm.Translation.y = player[g_Player]->Xform.Translation.y;
	player[g_Player]->ViewXForm.Translation.z = player[g_Player]->Xform.Translation.z;
#endif

	player[g_Player]->STOREMatrix = playerAV[g_Player]->Xform;

	playerAV[g_Player]->VecTo.x = -1.0f;
	playerAV[g_Player]->VecTo.y = 0.0f;
	playerAV[g_Player]->VecTo.z = 0.0f;

	playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

	//#### RESET SPELLS
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[3].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[4].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[5].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[6].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[7].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[8].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[9].LIVE = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

									//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
	Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

#if 0
	//##### Starting position
	Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=0;
	Ange.z=0;

	// Set the actor's angle DISALLOWED DUE TO MISMATCHED XFORMS
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, Ange.x);
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, Ange.y);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Ange.z);
#endif

	// Set the actor to its position
#if 0
	Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[player[g_Player]->Team].Pos, &playerAV[g_Player]->Xform.Translation);
#endif

	player[g_Player]->Angles.x = -1.05;
	player[g_Player]->Angles.y = 0.0f; // PI; // Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	player[g_Player]->trueAngles.y = 0.0f; // PI; // Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;

	fogbox.Min.x = playerAV[g_Player]->Mins.x;
	fogbox.Min.y = playerAV[g_Player]->Mins.y;
	fogbox.Min.z = playerAV[g_Player]->Mins.z;
	fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	fogbox.Max.z = playerAV[g_Player]->Maxs.z;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	player[g_Player]->idlespeed = 0.1;

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->STOREMatrix.Translation);

	playerAV[g_Player]->Avatar.IDflag = 250;

	player[g_Player]->AttackSoundTRIG = 0;

	//### Load Player Weapon
	player[g_Player]->Weapon.Avatar = 1;

	player[g_Player]->Weapon.Scale.x = 1;
	player[g_Player]->Weapon.Scale.y = 1;
	player[g_Player]->Weapon.Scale.z = 1;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

#if 0
	Qpo->Avatar_SetScale(player[g_Player]->Weapon.Avatar, 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

#if 0
	Ange.x=-(PI/2);
	Ange.y=PI;
	Ange.z=0;

	Qpo->Transform_RotateX(&player[g_Player]->Weapon.Xform, Ange.x);
	Qpo->Transform_RotateY(&player[g_Player]->Weapon.Xform, Ange.y);
	Qpo->Transform_RotateZ(&player[g_Player]->Weapon.Xform, Ange.z);
#endif

	Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Weapon.Xform.Translation);

	Qpo->Mesh_SetAlpha(&player[g_Player]->Weapon, 0);

	player[g_Player]->WeaponDISPLAY = 0;

#if 0
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
		{
		if(LOADED_FACTORY[3])	//FACTORY ALREADY LOADED
			{
			Avatar_Load_MESH(&player[g_Player]->Shield.Avatar, MFACT_SHOCKWAVE, ShieldREG, MapSector, csVector3(6,0,0));
			}
		else					//FACTORY NOT LOADED
			{
			Avatar_Load_FACTORY(&player[g_Player]->Shield.Avatar, MFACT_SHOCKWAVE, ShieldREG, MapSector, csVector3(0,-6,0), "C:/Projects Base/Q-A-G-E/data/Meshes", "ShockWave.cal3d", "EnergySHIELD");
			LOADED_FACTORY[3] = 1;
			}

		player[g_Player]->Shield.TXform = player[g_Player]->Shield.Avatar.spritewrapper->GetMovable()->GetTransform();
		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shield.Xform.Translation);

		player[g_Player]->Shield.Mins.x = -500.f;
		player[g_Player]->Shield.Mins.y = -500.f;
		player[g_Player]->Shield.Mins.z = -500.f;
		player[g_Player]->Shield.Maxs.x = 500.f;
		player[g_Player]->Shield.Maxs.y = 500.f;
		player[g_Player]->Shield.Maxs.z = 500.f;

		fogbox.Min.x = player[g_Player]->Shield.Mins.x;
		fogbox.Min.y = player[g_Player]->Shield.Mins.y;
		fogbox.Min.z = player[g_Player]->Shield.Mins.z;
		fogbox.Max.x = player[g_Player]->Shield.Maxs.x;
		fogbox.Max.y = player[g_Player]->Shield.Maxs.y;
		fogbox.Max.z = player[g_Player]->Shield.Maxs.z;

		//Qpo->Avatar_SetScale(player[g_Player]->Shield.Avatar, 0.65f,0.65f,0.65f);

		//Qpo->Avatar_SetAlpha(&player[g_Player]->Shield.Avatar, 150);

		//C++EDIT //C++EDIT poActor_SetExtBox(player[g_Player]->Shield.Avatar, &fogbox, NULL);

		player[g_Player]->Shield.Avatar.IDflag = 251;
		}
#endif

	//### Load Player Shadows
	helly = 0;
	while(helly <= 2)
		{
		helly++;

		player[g_Player]->Shadows[helly].Avatar.Mesh = new unAvatar();
		meshBank[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);

		player[g_Player]->Shadows[helly].Xform.Translation.x = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.y = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.z = 0;
		player[g_Player]->Shadows[helly].Xform.Matrix.load_identity();

		//##### Starting position
		Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
		//Ange.y=-(PI/2);//Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
		Ange.y = 0.0f;// Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
		if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
		Ange.x=-(PI/2);
		Ange.z=0;

		// Set the actor's angle
		Qpo->Transform_RotateX(&player[g_Player]->Shadows[helly].Xform, Ange.x);
		Qpo->Transform_RotateY(&player[g_Player]->Shadows[helly].Xform, Ange.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Shadows[helly].Xform, Ange.z);

#if 1
										//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[helly].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

		player[g_Player]->Shadows[helly].Mins.x = -20.f;
		player[g_Player]->Shadows[helly].Mins.y = -20.f;
		player[g_Player]->Shadows[helly].Mins.z = -20.f;
		player[g_Player]->Shadows[helly].Maxs.x = 20.f;
		player[g_Player]->Shadows[helly].Maxs.y = 20.f;
		player[g_Player]->Shadows[helly].Maxs.z = 20.f;

		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[helly].Xform.Translation);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shadows[helly].Avatar, 255/(helly+1));

		player[g_Player]->Shadows[helly].Avatar.IDflag = 250;
		}

	player[g_Player]->ShadowALPHA = 240;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//##### SPAWN EFFECTS
#if 0
	jet = 0;
	while(jet < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 750) _->NomSpikes = 0;

		jet++;
		}
#endif
#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItems();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 0
	//##### Load Player Vehicle
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrVEHICLE != 250 && 0)
		{
		if(LOADED_FACTORY[3])	//FACTORY ALREADY LOADED
			{
			Avatar_Load_MESH(&player[g_Player]->Vehicle.Model.Avatar, MFACT_VEH_DUCATI998, VehicleREG, MapSector, csVector3(6,0,0));
			}
		else					//FACTORY NOT LOADED
			{
			Avatar_Load_FACTORY(&player[g_Player]->Vehicle.Model.Avatar, MFACT_VEH_DUCATI998, VehicleREG, MapSector, csVector3(0,-6,0), "C:/Projects Base/Q-A-G-E/data/Meshes", "Ducati998.cal3d", "VehicleDUCATI998");
			LOADED_FACTORY[3] = 1;
			}

		player[g_Player]->Vehicle.Model.TXform = player[g_Player]->Vehicle.Model.Avatar.spritewrapper->GetMovable()->GetTransform();
		Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Vehicle.Model.Xform.Translation);

		player[g_Player]->Vehicle.Model.Mins.x = -20.f;
		player[g_Player]->Vehicle.Model.Mins.y = -20.f;
		player[g_Player]->Vehicle.Model.Mins.z = -20.f;
		player[g_Player]->Vehicle.Model.Maxs.x = 20.f;
		player[g_Player]->Vehicle.Model.Maxs.y = 20.f;
		player[g_Player]->Vehicle.Model.Maxs.z = 20.f;

		/*player[g_Player]->Vehicle.Model.Motion[0] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelSpin" );
		player[g_Player]->Vehicle.Model.Motion[1] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelScale" );
		player[g_Player]->Vehicle.Model.Motion[2] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelSpin" );
		player[g_Player]->Vehicle.Model.Motion[3] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelTurn" );
		player[g_Player]->Vehicle.Model.Motion[4] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelScale" );*/
		
		/*Ange.y=PI;
		if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
		Ange.x=-(PI/2);
		Ange.z=0;

		Qpo->Transform_RotateX(&player[g_Player]->Vehicle.Model.Xform, Ange.x);
		Qpo->Transform_RotateY(&player[g_Player]->Vehicle.Model.Xform, Ange.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.Model.Xform, Ange.z);*/

		//Qpo->Avatar_SetScale(player[g_Player]->Vehicle.Model.Avatar, 1.2f,1.2f,1.2f);

		player[g_Player]->Vehicle.Model.Avatar.IDflag = 250;

		//### Physics Setup
		player[g_Player]->Vehicle.Const_Weight = 8;	//Ten Q_Kgs
		player[g_Player]->Vehicle.Const_FWeight = 2;	//1.5
		player[g_Player]->Vehicle.Const_RWeight = 2;	//1.5
		player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0.335;

		player[g_Player]->Vehicle.Const_SpinCancel = 0.25;	//1.8
		player[g_Player]->Vehicle.Const_SpringLift = 7.5;	//2.5  1.23
		player[g_Player]->Vehicle.Const_SpringPower = 4;
		player[g_Player]->Vehicle.Const_WheelSettleSpin = 5;
		player[g_Player]->Vehicle.Const_WheelSettleDVel = 3.5;
		player[g_Player]->Vehicle.Const_SpringLimit = 14.5;
		player[g_Player]->Vehicle.Const_DownVelCancel = 3;
		player[g_Player]->Vehicle.Const_ForceFactor = 50;	//5
		player[g_Player]->Vehicle.Const_SpringAbsorbVel = 6.6;
		player[g_Player]->Vehicle.Const_SpringAbsorbSpin = 1.15;
		player[g_Player]->Vehicle.Const_LightTouchFactor = 1.15;
		player[g_Player]->Vehicle.Const_MaxSpeed = 100;

		player[g_Player]->Vehicle.Const_SpringCrunchMAX = 15;
		//player[g_Player]->Vehicle.Const_MiddleCOGDIST = -31;
		//player[g_Player]->Vehicle.Const_SpringCompDist = 20;

		player[g_Player]->Vehicle.Const_FRICMinSlide = 15;

		//#### BUILD CRUNCH UP VECS
		player[g_Player]->Vehicle.ConstVec_FCrunch.x = 1.071;
		player[g_Player]->Vehicle.ConstVec_FCrunch.y = 7.887;
		player[g_Player]->Vehicle.ConstVec_FCrunch.z = 3.893;

		player[g_Player]->Vehicle.ConstVec_RCrunch.x = 1.102;
		player[g_Player]->Vehicle.ConstVec_RCrunch.y = 8.116;
		player[g_Player]->Vehicle.ConstVec_RCrunch.z = 1.521;

		player[g_Player]->Vehicle.GravityAlter = 1;
		}
#endif


#if 0
	//##### Load Player Mech
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH != 250 && 0)
		{
		if(LOADED_FACTORY[3])	//FACTORY ALREADY LOADED
			{
			Avatar_Load_MESH(&player[g_Player]->Mech.Model.Avatar, MFACT_MECH_1, MechREG, MapSector, csVector3(6,0,0));
			}
		else					//FACTORY NOT LOADED
			{
			Avatar_Load_FACTORY(&player[g_Player]->Mech.Model.Avatar, MFACT_MECH_1, MechREG, MapSector, csVector3(0,-6,0), "C:/Projects Base/Q-A-G-E/data/Meshes", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrVEHICLE].ItemActorREF, "Mech1");
			LOADED_FACTORY[16] = 1;
			}

		player[g_Player]->Mech.Model.TXform = player[g_Player]->Mech.Model.Avatar.spritewrapper->GetMovable()->GetTransform();
		//Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Mech.Model.Xform.Translation);
		Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Mech.Model.Xform.Translation);

		player[g_Player]->Mech.Model.Mins.x = -200.f;
		player[g_Player]->Mech.Model.Mins.y = -200.f;
		player[g_Player]->Mech.Model.Mins.z = -200.f;
		player[g_Player]->Mech.Model.Maxs.x = 200.f;
		player[g_Player]->Mech.Model.Maxs.y = 200.f;
		player[g_Player]->Mech.Model.Maxs.z = 200.f;

		//Qpo->Avatar_SetScale(player[g_Player]->Mech.Model.Avatar, 0.43 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Height)/100)-0.5)*2)), 0.43 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Weight)/100)-0.5)*2)), 0.43 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Weight)/100)-0.5)*2)));

		/*Ange.y=PI;
		if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
		Ange.x=-(PI/2);
		Ange.z=0;

		Qpo->Transform_RotateX(&player[g_Player]->Mech.Model.Xform, Ange.x);
		Qpo->Transform_RotateY(&player[g_Player]->Mech.Model.Xform, Ange.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Mech.Model.Xform, Ange.z);*/

		player[g_Player]->Mech.Model.Avatar.IDflag = 250;

		helly = 0;
		while(helly <= 2)
			{
			helly++;

			Avatar_Load_MESH(&player[g_Player]->Mech.Shadows[helly].Avatar, MFACT_MECH_1, MechREG, MapSector, csVector3(6,0,0));

			player[g_Player]->Mech.Shadows[helly].TXform = player[g_Player]->Mech.Shadows[helly].Avatar.spritewrapper->GetMovable()->GetTransform();
			Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Mech.Shadows[helly].Xform.Translation);

			player[g_Player]->Mech.Shadows[helly].Mins.x = -200.f;
			player[g_Player]->Mech.Shadows[helly].Mins.y = -200.f;
			player[g_Player]->Mech.Shadows[helly].Mins.z = -200.f;
			player[g_Player]->Mech.Shadows[helly].Maxs.x = 200.f;
			player[g_Player]->Mech.Shadows[helly].Maxs.y = 200.f;
			player[g_Player]->Mech.Shadows[helly].Maxs.z = 200.f;

			//Qpo->Avatar_SetScale(player[g_Player]->Mech.Shadows[helly].Avatar, 0.01,0.01,0.01);

			/*Ange.y=PI;
			if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
			Ange.x=-(PI/2);
			Ange.z=0;

			Qpo->Transform_RotateX(&player[g_Player]->Mech.Shadows[helly].Xform, Ange.x);
			Qpo->Transform_RotateY(&player[g_Player]->Mech.Shadows[helly].Xform, Ange.y);
			Qpo->Transform_RotateZ(&player[g_Player]->Mech.Shadows[helly].Xform, Ange.z);*/

			player[g_Player]->Mech.Shadows[helly].Avatar.IDflag = 250;
			}

		//### Physics Setup
		}
#endif

#if 0
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight = 15;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP = 1;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH = 1;

	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower);
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH );

	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower );
	printf("%f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity );

	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class = 0;
#endif

	switch(g_Player)
		{
		case 0:
			{
			player[g_Player]->Team = QTEAM_P0;
			}break;
		case 1:
			{
			player[g_Player]->Team = QTEAM_P1;
			}break;
		}

	// get the skeleton we need to update
	QunSkeleton* pSkeleton = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton();

	pSkeleton->clearState();
	}

	g_Player = 0;
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#ifndef QAGEMODE_NOINTRO
  acNamePlateUpdate();
#endif

//## SETUP AI ##############################################################################################
//##########################################################################################################
//##########################################################################################################

// AI setup AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIA
//AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIA
//AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIA

	if(_->NetworkOption != 1)
		{
		CharCounter = 0;
		helly = 0;
		while(helly < _->NomAI)
			{
			if(player[g_Player]->BFO.AVATARDATA[helly].LIVE == 1)
				{
				Q_Forge->Forge[helly].LIVE = 1;

#pragma message("FIXME: Q_Netplayer->NetplayerFLAG set with library info pass on startup")
				Q_Forge->Forge[helly].NetplayerFLAG = 0;

				Q_Forge->Forge[helly].AV.upspeed = -15;

				Q_Forge->Forge[helly].AV.Mins.x = -(20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
				Q_Forge->Forge[helly].AV.Mins.y = -(45 + (30*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
				Q_Forge->Forge[helly].AV.Mins.z = -(20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.x = (20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.y = (45 + (30*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.z = (20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

				Q_Forge->Forge[helly].PlayerSpeed = PLAYER_SPEED;

				Q_Forge->Forge[helly].GravityAlter = 1;

				// Fill Weapon Ammo
				Q_Forge->Forge[helly].WeaponAmmo = 32;
				Q_Forge->Forge[helly].HB_Illumination = 255;
				Q_Forge->Forge[helly].HB_Dead = 0;

				// Body and Mind
				Q_Forge->Forge[helly].Q_Heart.HeartIncrement = 0;
				Q_Forge->Forge[helly].Q_Heart.PulseRate = 1;
				Q_Forge->Forge[helly].Q_Brain.Aggression = 70;

				//###### AVATAR SELECTION
				//### Obtain Correct Character Data for Avatar
				Q_Forge->Forge[helly].CharDATA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[helly].CDATID];
				Q_Forge->Forge[helly].CharDATA.BDataID = player[g_Player]->BFO.AVATARDATA[helly].BDATID;
				Q_Forge->Forge[helly].CharDATA.TEAM = player[g_Player]->BFO.AVATARDATA[helly].TEAM;
				Q_Forge->Forge[helly].Team = player[g_Player]->BFO.AVATARDATA[helly].TEAM;
				Q_Forge->Forge[helly].AVDATID = helly;
				player[g_Player]->BFO.AVATARDATA[helly].AVATARID = helly;
				
				//#### Set Role
				Q_Forge->Forge[helly].Role = 0;
				Q_Forge->Forge[helly].Rank = 1;
				Q_Forge->Forge[helly].LEVEL = Q_Forge->Forge[helly].CharDATA.Level;

				#pragma message ("FIXME:::Start AI Start Position and initial pose")
				Q_Forge->Forge[helly].AV.Avatar.Mesh = new unAvatar();

				if(AVATAR_PHYSICS_ENABLE)	meshBank[Q_Forge->Forge[helly].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[helly].AV.Avatar.Mesh);
				else meshBank[0]->clone_struct(Q_Forge->Forge[helly].AV.Avatar.Mesh);

				Q_Forge->Forge[helly].Xform.Translation.x = 0;
				Q_Forge->Forge[helly].Xform.Translation.y = 0;
				Q_Forge->Forge[helly].Xform.Translation.z = 0;
				Q_Forge->Forge[helly].Xform.Matrix.load_identity();

				//##### Starting position
				Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
				//Ange.y=-(PI/2);//Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
				Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
				if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
				Ange.x=-(PI/2);
				Ange.z=0;

				// Set the actor's angle
				Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Xform, Ange.x);
				Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Xform, Ange.y);
				Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Xform, Ange.z);

				Q_Forge->Forge[helly].STOREMatrix = Q_Forge->Forge[helly].Xform;
				Q_Forge->Forge[helly].ROTATEMatrix = Q_Forge->Forge[helly].Xform;

#if 1
				Qpo->Avatar_SetScale(&Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

				Q_Forge->Forge[helly].idlespeed = 0.1;

				if(Q_Forge->Forge[helly].LEVEL > 1000) Q_Forge->Forge[helly].LEVELFactor = 1;
				else Q_Forge->Forge[helly].LEVELFactor = (((float)Q_Forge->Forge[helly].LEVEL + 1) / 1000);


				Q_Forge->Forge[helly].HB_MaxHealth = 1000 * (((Q_Forge->Forge[helly].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
				Q_Forge->Forge[helly].HB_Health = Q_Forge->Forge[helly].HB_MaxHealth;

				Q_Forge->Forge[helly].HB_MaxEnergy = 500;
				Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;

				Q_Forge->Forge[helly].HB_Armour = ((float)(Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
				Q_Forge->Forge[helly].HB_MaxArmour = ((float)(Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

				Q_Forge->Forge[helly].JINK3_PowerFactor = 1;

				//#### RESET SPELLS
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[3].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[4].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[5].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[6].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[7].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[8].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[9].LIVE = 0;

				//ACTOR SETUP AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
				
				//####### RELATIVE ATTACK SPEED
				Q_Forge->Forge[helly].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[helly].CharDATA.BodySKILL.Quickness / 100) * 0.8);

				//####### RELATIVE ENERGY EFFICIENCY
				Q_Forge->Forge[helly].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[helly].CharDATA.BodySKILL.EnergyEff / 6000);

				Q_Forge->Forge[helly].AV.Avatar.Visible = true;

#if 0
				Q_Forge->Forge[helly].AV.Motion[0] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle" );
				Q_Forge->Forge[helly].AV.Motion[1] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Walk" );
				Q_Forge->Forge[helly].AV.Motion[2] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Run" );
				Q_Forge->Forge[helly].AV.Motion[3] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Sidestep" );
				Q_Forge->Forge[helly].AV.Motion[4] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Jump" );
				Q_Forge->Forge[helly].AV.Motion[5] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LLPunch" );
				Q_Forge->Forge[helly].AV.Motion[6] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RLPunch" );
				Q_Forge->Forge[helly].AV.Motion[7] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RHPunch2" );	//RHPunch
				Q_Forge->Forge[helly].AV.Motion[8] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RMKick" );
				Q_Forge->Forge[helly].AV.Motion[9] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LMPunch" );	//LSPunch needs a home
				Q_Forge->Forge[helly].AV.Motion[10] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RMPunch" );
				Q_Forge->Forge[helly].AV.Motion[12] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WalkL" );
				Q_Forge->Forge[helly].AV.Motion[13] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WalkR" );
				Q_Forge->Forge[helly].AV.Motion[14] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunL" );
				Q_Forge->Forge[helly].AV.Motion[15] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunR" );
				Q_Forge->Forge[helly].AV.Motion[16] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SidestepL" );
				Q_Forge->Forge[helly].AV.Motion[17] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SidestepR" );
				Q_Forge->Forge[helly].AV.Motion[18] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Renzou" );		//TODO: Combine these two
				Q_Forge->Forge[helly].AV.Motion[19] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouE" );		//TODO: into one
				Q_Forge->Forge[helly].AV.Motion[20] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RSPunch" );
				Q_Forge->Forge[helly].AV.Motion[21] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Uppercut" );	//Uppercut
				Q_Forge->Forge[helly].AV.Motion[22] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HBlock" );
				Q_Forge->Forge[helly].AV.Motion[23] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle2" );
				Q_Forge->Forge[helly].AV.Motion[24] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouR" );
				Q_Forge->Forge[helly].AV.Motion[25] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon1" );
				Q_Forge->Forge[helly].AV.Motion[26] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunWep1L" );
				Q_Forge->Forge[helly].AV.Motion[27] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunWep1R" );
				Q_Forge->Forge[helly].AV.Motion[28] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep1" );
				Q_Forge->Forge[helly].AV.Motion[29] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AXKick" );
				Q_Forge->Forge[helly].AV.Motion[30] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SPKick" );
				Q_Forge->Forge[helly].AV.Motion[31] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpL" );
				Q_Forge->Forge[helly].AV.Motion[32] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpR" );
				Q_Forge->Forge[helly].AV.Motion[33] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Cartwheel" );
				Q_Forge->Forge[helly].AV.Motion[34] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon1UPP" );
				Q_Forge->Forge[helly].AV.Motion[35] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep1UPP" );
				Q_Forge->Forge[helly].AV.Motion[36] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CartWep1" );
				Q_Forge->Forge[helly].AV.Motion[37] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle3" );
				Q_Forge->Forge[helly].AV.Motion[38] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouL" );
				Q_Forge->Forge[helly].AV.Motion[39] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoldDash" );
				Q_Forge->Forge[helly].AV.Motion[40] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Knee" );
				Q_Forge->Forge[helly].AV.Motion[41] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpKick" );
				Q_Forge->Forge[helly].AV.Motion[42] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Wave" );
				Q_Forge->Forge[helly].AV.Motion[43] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HitStom" );
				Q_Forge->Forge[helly].AV.Motion[44] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HitUpper" );
				Q_Forge->Forge[helly].AV.Motion[45] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSpiral" );
				Q_Forge->Forge[helly].AV.Motion[46] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "DodgeL" );
				Q_Forge->Forge[helly].AV.Motion[47] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FKick" );
				Q_Forge->Forge[helly].AV.Motion[48] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunBack" );
				Q_Forge->Forge[helly].AV.Motion[53] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FallHead" );
				Q_Forge->Forge[helly].AV.Motion[54] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RHKick" );
				Q_Forge->Forge[helly].AV.Motion[55] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FlameUpperCut" );
				Q_Forge->Forge[helly].AV.Motion[56] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HBlockHit" );
				Q_Forge->Forge[helly].AV.Motion[57] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BackFlip" );
				Q_Forge->Forge[helly].AV.Motion[58] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload" );
				Q_Forge->Forge[helly].AV.Motion[59] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinKickFull" );
				Q_Forge->Forge[helly].AV.Motion[60] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Crouch" );
				Q_Forge->Forge[helly].AV.Motion[61] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CrouchL" );
				Q_Forge->Forge[helly].AV.Motion[62] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CrouchR" );
				Q_Forge->Forge[helly].AV.Motion[67] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "VHKick" );
				Q_Forge->Forge[helly].AV.Motion[68] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Entro" );
				Q_Forge->Forge[helly].AV.Motion[69] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwinDragon1" );
				Q_Forge->Forge[helly].AV.Motion[70] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwinDragon2" );
				Q_Forge->Forge[helly].AV.Motion[71] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Golrekka" );
				Q_Forge->Forge[helly].AV.Motion[72] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SkyPush" );
				Q_Forge->Forge[helly].AV.Motion[73] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Lowtro" );
				Q_Forge->Forge[helly].AV.Motion[74] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Lowkick" );
				Q_Forge->Forge[helly].AV.Motion[75] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Legsweep" );
				Q_Forge->Forge[helly].AV.Motion[76] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Crunch" );
				Q_Forge->Forge[helly].AV.Motion[77] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Hitwall" );
				Q_Forge->Forge[helly].AV.Motion[78] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AttFlip" );
				Q_Forge->Forge[helly].AV.Motion[79] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttP" );
				Q_Forge->Forge[helly].AV.Motion[80] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowPunchL" );
				Q_Forge->Forge[helly].AV.Motion[81] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowPunchR" );
				Q_Forge->Forge[helly].AV.Motion[82] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LBlock" );
				Q_Forge->Forge[helly].AV.Motion[83] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LBlockHit" );
				Q_Forge->Forge[helly].AV.Motion[84] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Hadouken" );
				Q_Forge->Forge[helly].AV.Motion[85] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HadoukenAir" );
				Q_Forge->Forge[helly].AV.Motion[86] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AirDash" );
				Q_Forge->Forge[helly].AV.Motion[87] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoverKick" );
				Q_Forge->Forge[helly].AV.Motion[88] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollF" );
				Q_Forge->Forge[helly].AV.Motion[89] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Taunt1" );
				Q_Forge->Forge[helly].AV.Motion[90] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Sakurat" );
				Q_Forge->Forge[helly].AV.Motion[91] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BrollyT" );
				Q_Forge->Forge[helly].AV.Motion[92] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PCombo1" );
				Q_Forge->Forge[helly].AV.Motion[93] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpiralDown" );
				Q_Forge->Forge[helly].AV.Motion[94] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSpiralOver" );
				Q_Forge->Forge[helly].AV.Motion[95] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmall" );
				Q_Forge->Forge[helly].AV.Motion[96] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwistKick" );
				Q_Forge->Forge[helly].AV.Motion[97] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BackFLipAtt" );
				Q_Forge->Forge[helly].AV.Motion[98] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Deflect" );
				Q_Forge->Forge[helly].AV.Motion[99] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmallL" );
				Q_Forge->Forge[helly].AV.Motion[100] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmallR" );
				Q_Forge->Forge[helly].AV.Motion[101] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PCombo2" );
				Q_Forge->Forge[helly].AV.Motion[102] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RushElbow" );
				Q_Forge->Forge[helly].AV.Motion[103] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoldBarge" );
				Q_Forge->Forge[helly].AV.Motion[104] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "DoubleStrike" );
				Q_Forge->Forge[helly].AV.Motion[105] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowLunge" );
				Q_Forge->Forge[helly].AV.Motion[106] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SideChop" );
				Q_Forge->Forge[helly].AV.Motion[107] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinChop" );
				Q_Forge->Forge[helly].AV.Motion[108] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollLowL" );
				Q_Forge->Forge[helly].AV.Motion[109] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollLowR" );
				//VEHICLE MOTIONS UNUSED
				//Q_Forge->Forge[helly].AV.Motion[110] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeMount" );
				//Q_Forge->Forge[helly].AV.Motion[111] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeRush" );
				//Q_Forge->Forge[helly].AV.Motion[112] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeWheelie" );
				//Q_Forge->Forge[helly].AV.Motion[113] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeIdle" );
				Q_Forge->Forge[helly].AV.Motion[114] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouP" );
				Q_Forge->Forge[helly].AV.Motion[115] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouPR" );
				Q_Forge->Forge[helly].AV.Motion[116] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AttFlipE" );
				Q_Forge->Forge[helly].AV.Motion[117] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HandSlap" );
				Q_Forge->Forge[helly].AV.Motion[118] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSH" );
				Q_Forge->Forge[helly].AV.Motion[119] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHPUNCH" );
				Q_Forge->Forge[helly].AV.Motion[120] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHBG" );
				Q_Forge->Forge[helly].AV.Motion[121] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHKICK" );
				Q_Forge->Forge[helly].AV.Motion[122] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "StaticKick" );
				Q_Forge->Forge[helly].AV.Motion[123] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttK" );
				Q_Forge->Forge[helly].AV.Motion[124] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RDoubleKick" );
				Q_Forge->Forge[helly].AV.Motion[125] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReloadUPP" );
				Q_Forge->Forge[helly].AV.Motion[126] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttK" );
				Q_Forge->Forge[helly].AV.Motion[127] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PowerBomb" );
				Q_Forge->Forge[helly].AV.Motion[128] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LeapDownStrike" );
				Q_Forge->Forge[helly].AV.Motion[129] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RSPINSTRIKE" );
				Q_Forge->Forge[helly].AV.Motion[130] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinoutLeft" );
				Q_Forge->Forge[helly].AV.Motion[131] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "OverheadPinwheel" );
				Q_Forge->Forge[helly].AV.Motion[132] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LeapDownFist" );
				Q_Forge->Forge[helly].AV.Motion[140] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LookRight" );

				if(Q_Forge->Forge[helly].CharDATA.Class == 2)
					{
					Q_Forge->Forge[helly].AV.Motion[63] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Glance" );
					Q_Forge->Forge[helly].AV.Motion[65] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HealUPP" );
					Q_Forge->Forge[helly].AV.Motion[66] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Heal" );
					}

				Q_Forge->Forge[helly].AV.Motion[133] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon2" );
				Q_Forge->Forge[helly].AV.Motion[134] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon2UPP" );
				Q_Forge->Forge[helly].AV.Motion[135] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep2" );
				Q_Forge->Forge[helly].AV.Motion[136] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep2UPP" );
				Q_Forge->Forge[helly].AV.Motion[137] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload2" );
				Q_Forge->Forge[helly].AV.Motion[138] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload2UPP" );
#endif

				//##### ATTENTION REQUIRED
#if 0
				Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
				Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
#endif

#if 0
				//Lighting
				if(Q_AvatarEntity->AvatarEntity[helly].Team == 0)	//Friendly AI
					{
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 0)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 1)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 2)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
					}

				if(Q_AvatarEntity->AvatarEntity[helly].Team == 1)	//Enemy AI
					{
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 0) 
						{
						//Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&poop,255,180,180,220,220,220,false,8,NULL,true);
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
						}
					}
#endif

				//Starting Rotation
				Ange.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y + (PI);
				if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
				Ange.x=-(PI/2);
				Ange.z=0;

				// Set the actor's angle
				Qpo->Transform_RotateX(&Q_Forge->Forge[helly].AV.Xform, Ange.x);		//Update Avatar's starting facing direction
				Qpo->Transform_RotateY(&Q_Forge->Forge[helly].AV.Xform, Ange.y);
				Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].AV.Xform, Ange.z);

				Q_Forge->Forge[helly].Angles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
				Q_Forge->Forge[helly].trueAngles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
				Q_Forge->Forge[helly].STOREAngles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;

#if 0
				if(Q_Forge->Forge[helly].CharDATA.Class == 2)
					{
					Q_Forge->Forge[helly].Shield.Mins.x = -500.f;
					Q_Forge->Forge[helly].Shield.Mins.y = -500.f;
					Q_Forge->Forge[helly].Shield.Mins.z = -500.f;
					Q_Forge->Forge[helly].Shield.Maxs.x = 500.f;
					Q_Forge->Forge[helly].Shield.Maxs.y = 500.f;
					Q_Forge->Forge[helly].Shield.Maxs.z = 500.f;

					Gamesystem->Avatar_Load(Q_Forge->Forge[helly].Shield.Xform, "Actors\\ShockWave.act");
					//*Q_Forge->Forge[helly].Shield.AvatarDef = egen3d_FullAccess_ActorDef();
					//*Q_Forge->Forge[helly].Shield.Avatar = egen3d_FullAccess_Actor();
					//*Q_Forge->Forge[helly].Shield.Xform = egen3d_FullAccess_ActorXform();

					//Qpo->Avatar_SetScale(Q_Forge->Forge[helly].Shield.Avatar, 0.65f,0.65f,0.65f);
					//C++EDIT poWorld_AddActor(World, Q_Forge->Forge[helly].Shield.Avatar, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE, 0xffffffff);
					Qpo->Avatar_SetAlpha(&Q_Forge->Forge[helly].Shield.Avatar, 40);

					fogbox.Min.x = Q_Forge->Forge[helly].Shield.Mins.x;
					fogbox.Min.y = Q_Forge->Forge[helly].Shield.Mins.y;
					fogbox.Min.z = Q_Forge->Forge[helly].Shield.Mins.z;
					fogbox.Max.x = Q_Forge->Forge[helly].Shield.Maxs.x;
					fogbox.Max.y = Q_Forge->Forge[helly].Shield.Maxs.y;
					fogbox.Max.z = Q_Forge->Forge[helly].Shield.Maxs.z;
					
					//C++EDIT //C++EDIT poActor_SetExtBox(Q_Forge->Forge[helly].Shield.Avatar, &fogbox, NULL);

					Qpo->Avatar_ClearPose(Q_Forge->Forge[helly].Shield.Avatar, &Q_Forge->Forge[helly].Shield.Xform);
					Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].Shield.Avatar, false, &goup, 0, 0, 0, 255, 255, 255, false, 0, NULL, false);
					Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[helly].Shield.Xform.Translation);

					Q_Forge->Forge[helly].Shield.Avatar.IDflag = 251;
					}
#endif

				//### Load Fighter Shadows
				Q_Forge->Forge[helly].ShadowsOn = false;
				Q_Forge->Forge[helly].ShadowALPHA = 240;

				aero = 0;
				while(aero <= 2)
					{
					aero++;
					Q_Forge->Forge[helly].Shadows[aero].Avatar.Mesh = new unAvatar();
					meshBank[0]->clone_struct(Q_Forge->Forge[helly].Shadows[aero].Avatar.Mesh);

					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.x = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.y = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.z = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Matrix.load_identity();

					//##### Starting position
					Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
					//Ange.y=-(PI/2);//Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
					Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
					if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
					Ange.x=-(PI/2);
					Ange.z=0;

					// Set the actor's angle
					Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.x);
					Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.y);
					Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.z);

					Q_Forge->Forge[helly].Shadows[aero].Mins.x = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Mins.y = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Mins.z = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.x = 20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.y = 20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.z = 20.f;

					Q_Forge->Forge[helly].Shadows[aero].Avatar.Visible = true;

#if 0
					Q_Forge->Forge[helly].Shadows[aero].Motion[0] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Idle" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[1] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Walk" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[2] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Run" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[3] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Sidestep" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[4] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Jump" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[5] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LLPunch" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[6] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RLPunch" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[7] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RHPunch2" );	//RHPunch
					Q_Forge->Forge[helly].Shadows[aero].Motion[8] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RMKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[9] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LMPunch" );	//LSPunch needs a home
					Q_Forge->Forge[helly].Shadows[aero].Motion[10] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RMPunch" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[11] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LLPunchA" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[12] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "WalkL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[13] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "WalkR" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[14] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RunL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[15] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RunR" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[16] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "SidestepL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[17] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "SidestepR" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[18] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Renzou" );		//TODO: Combine these two
					Q_Forge->Forge[helly].Shadows[aero].Motion[19] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RenzouE" );		//TODO: into one
					Q_Forge->Forge[helly].Shadows[aero].Motion[20] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RSPunch" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[21] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Uppercut" );	//Uppercut
					Q_Forge->Forge[helly].Shadows[aero].Motion[22] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HBlock" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[23] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Idle2" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[24] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RenzouR" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[25] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Weapon1" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[26] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RunWep1L" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[27] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RunWep1R" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[28] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AimWep1" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[29] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AXKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[30] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "SPKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[31] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JumpL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[32] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JumpR" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[33] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Cartwheel" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[34] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Weapon1UPP" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[35] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AimWep1UPP" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[36] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "CartWep1" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[37] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Idle3" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[38] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RenzouL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[39] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HoldDash" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[40] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Knee" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[41] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JumpKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[42] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Wave" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[43] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HitStom" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[44] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HitUpper" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[45] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JumpSpiral" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[46] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "DodgeL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[47] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "FKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[48] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AirJink" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[49] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RunBack" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[50] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AirRushFront" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[51] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HitStorm" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[52] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RapidKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[53] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "FallHead" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[54] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RHKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[55] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "FlameUpperCut" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[56] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HBlockHit" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[57] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "BackFlip" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[58] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "WeaponReload" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[59] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "SpinKickFull" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[60] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Crouch" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[61] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "CrouchL" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[62] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "CrouchR" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[63] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LLPunchUPP" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[64] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RLPunchUPP" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[65] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LMPunchUPP" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[66] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LMKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[67] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "VHKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[71] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Golrekka" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[72] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "SkyPush" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[76] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Crunch" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[77] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Hitwall" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[78] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AttFlip" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[84] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Hadouken" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[85] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HadoukenAir" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[86] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "AirDash" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[87] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "HoverKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[88] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RollF" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[90] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "Sakurat" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[91] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "BrollyT" );
					//Q_Forge->Forge[helly].Shadows[aero].Motion[92] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "PCombo1" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[96] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "TwistKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[101] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "PCombo2" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[102] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "RushElbow" );

					Q_Forge->Forge[helly].Shadows[aero].Motion[118] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JSRUSH" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[119] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JSRUSHPUNCH" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[120] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JSRUSHBG" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[121] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "JSRUSHKICK" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[122] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "StaticKick" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[127] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "PowerBomb" );

					Q_Forge->Forge[helly].Shadows[aero].Motion[128] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LeapDownStrike" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[129] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "CartwheelAtt" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[130] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "SpinoutLeft" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[131] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "OverheadPinwheel" );
					Q_Forge->Forge[helly].Shadows[aero].Motion[132] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].Shadows[aero].AvatarDef, "LeapDownFist" );
#endif

					Ange.x=-(PI/2);
					Ange.y=PI;
					Ange.z=0;

					Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.x);
					Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.y);
					Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.z);
					Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[helly].Shadows[aero].Xform.Translation);

					Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].Shadows[aero].Avatar,true,&goup,255,255,255,255,255,255,false,0,NULL,true);

					Qpo->Avatar_ClearPose(Q_Forge->Forge[helly].Shadows[aero].Avatar, &Q_Forge->Forge[helly].Shadows[aero].Xform);

					Qpo->Avatar_SetAlpha(&Q_Forge->Forge[helly].Shadows[aero].Avatar, 255/(aero+1));

					Q_Forge->Forge[helly].Shadows[aero].Avatar.IDflag = helly;

					if(Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.ANGELEDITFLAG == 1)
						{
						//##### ANGEL COLOUR EDIT
						int K=0;
						while(K < 38)
							{
							Qpo->Avatar_GetTex(&Q_Forge->Forge[helly].Shadows[aero].Avatar, K, Medias->ANGELeditBitmap, &_->ANGELeditBitmapRed, &_->ANGELeditBitmapGreen, &_->ANGELeditBitmapBlue);
							Qpo->Avatar_SetTex(&Q_Forge->Forge[helly].Shadows[aero].Avatar, K, Medias->ANGELeditBitmap, &Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.RED[K], &Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.GREEN[K], &Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.BLUE[K]);
							K++;
							}
						}
					}

				//#### Set Up Trail Flags
				Q_Forge->Forge[helly].TrailFadeSpan[0][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[1][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[2][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[3][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[4][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[5][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[6][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[7][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[8][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[9][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[0][1] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[1][1] = 1;
				Q_Forge->Forge[helly].TrailFadeSpan[2][1] = 2;
				Q_Forge->Forge[helly].TrailFadeSpan[3][1] = 3;
				Q_Forge->Forge[helly].TrailFadeSpan[4][1] = 4;
				Q_Forge->Forge[helly].TrailFadeSpan[5][1] = 5;
				Q_Forge->Forge[helly].TrailFadeSpan[6][1] = 6;
				Q_Forge->Forge[helly].TrailFadeSpan[7][1] = 7;
				Q_Forge->Forge[helly].TrailFadeSpan[8][1] = 8;
				Q_Forge->Forge[helly].TrailFadeSpan[9][1] = 9;

				//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#if 0
#ifndef QAGEMODE_NOINTRO
				acNamePlateUpdate();
#endif
#endif

				//####### ACTIVATE ITEM ATTRIBUTES
				Q.ActivateItemsAI(helly);

#if 1			//#### RESET SCALE AND LIGHTING
				Qpo->Avatar_SetScale(&Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

#if 0
#ifndef QAGEMODE_NOINTRO
				acNamePlateUpdate();
#endif
#endif

				if(Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.ANGELEDITFLAG == 1)
					{
					//##### ANGEL COLOUR EDIT
					int K=0;
					while(K < 38)
						{
						Qpo->Avatar_GetTex(&Q_Forge->Forge[helly].AV.Avatar, K, Medias->ANGELeditBitmap, &_->ANGELeditBitmapRed, &_->ANGELeditBitmapGreen, &_->ANGELeditBitmapBlue);
						Qpo->Avatar_SetTex(&Q_Forge->Forge[helly].AV.Avatar, K, Medias->ANGELeditBitmap, &Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.RED[K], &Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.GREEN[K], &Q_Forge->Forge[helly].CharDATA.AngelCOLOURS.BLUE[K]);
						K++;
						}
					}
				}

			helly++;
			}
		}

//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//#### SOUND SETUP

#ifdef QAGE_SOUND
	Q.InitSounds();
#endif
}


void QActiveFramewrk::acDataInit(void)
{
#ifdef QAGE_DEBUG
	//*unConsoleAttribute(CONSOLE_INIT);
#endif

#ifdef BOOST32
	shared_memory_object::remove("UnificationSPC");

	m_unSegment = new managed_shared_memory(open_or_create, "UnificationSPC", UN_SEGMENT_DEFAULT_SIZE * 500);	//15250 5250 2250 250
#endif

#if 0 //QAGE_DESKTOP
	glewInit();
#endif

#if 1
	// ### 0
	acGenerateDataMesh("Avatar/Lisa.cfg");
#endif

#if 1
#if 1
	// ### 1
	acGenerateDataMesh("Avatar/MellodiData.cfg");

	// ### 2
	acGenerateDataMesh("Avatar/AssassinData.cfg");

	// ### 3
	acGenerateDataMesh("Avatar/ShortSkirtAlterData.cfg");

#if 1 // ### 4
	acGenerateDataMesh("Avatar/ShortSkirtData.cfg");
#endif

	// ### 5
	acGenerateDataMesh("Avatar/ShortSkirtBikiniData.cfg");

	// ### 6
	acGenerateDataMesh("Avatar/TemplateData.cfg");

	// ### 7
	acGenerateDataMesh("Avatar/250TemplateData.cfg");

	// ### 8
	acGenerateDataMesh("Avatar/250TemplateClothesData.cfg");
	
	// ### 9
	acGenerateDataMesh("Avatar/SoldierNewData.cfg");

	// ### 10
	acGenerateDataMesh("Avatar/CommanderData.cfg");

	// ### 11
	acGenerateDataMesh("Avatar/ShortSkirtGlovesData.cfg");
#endif
#endif

	// Body Mesh
	//acGenerateDataBodyMesh("Avatar/ShortSkirtBikiniData.cfg");


#if 0
	acGenerateDataMesh("Avatar/TemplateShell.cfg");
	acGenerateDataMesh("Avatar/250TemplateShell.cfg");
	acGenerateDataMesh("Avatar/ShortSkirtShell.cfg");
	acGenerateDataMesh("Avatar/ShortSkirtBikiniShell.cfg");
	acGenerateDataMesh("Avatar/MelloditheTempShell.cfg");
#endif

	//###### Data Generation
#if 0
	unMeshStatic *f_MeshStatic = new unMeshStatic();

	if(!f_MeshStatic->onCreate("Assets/Mesh/Energy/Renzou.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_MeshStatic);
#endif

#if 0	// Weapon Test
	unMeshStatic *f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/w_awp10.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/FordGT40.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif

#if 0
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/Ducati.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif
}

bool QActiveFramewrk::acAmpMesh(void)
{
#if 0
	/////- AMP Load Meshes -/////
	m_unSegment = NULL;
	m_unSegment = new managed_shared_memory(open_only, "UnificationSPC");

	if(!m_unSegment)
		{
		//*unConsoleAttribute(CONSOLE_ERROR);
		printf("Memory has become corrupted, dont worry too much, just close unDataServer and start again before reloading\n");
		for(;;) {}
		}

#if 1
	unShellMesh *f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/LisaShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	f_mesh->acMake();

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);
#endif

#ifndef QAGE_OPMOD_B

	f_mesh = new unShellMesh();

	if(!f_mesh->acCreate("Assets/Avatar/MellodiShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

	if(!f_mesh->acCreate("Assets/Avatar/AssassinShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtAlterShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtBikiniShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/TemplateShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/250TemplateShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);


	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/250TemplateClothesShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/SoldierNewShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/CommanderShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtGlovesShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);
#endif

#if 0
	digiShellMesh* f_digimesh = new digiShellMesh();

	if(!f_digimesh->acCreate("Assets/Avatar/ShortSkirtGlovesShell.cfg"))
		{
		std::cerr << "ERROR::: unBodyMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	f_digimesh->acMake();

	if(!f_digimesh->acInit(0))
		{
		std::cerr << "ERROR::: unBodyMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshdigiShellTemplates.push_back(f_digimesh);
#endif

#if 1
	unMeshStatic *f_MeshStatic = new unMeshStatic();

	if(!f_MeshStatic->onCreate("Assets/Mesh/Energy/Renzou.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_MeshStatic);
#endif

#if 1	// Swat552X
	unMeshStatic *f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/Swat552X.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// famassvX
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/famassvX.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// IncaMKII
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/MiniGun1.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// MiniGun
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/MiniGun1.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// M4A1actr
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/M4A1actr.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// Swat552X
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/Swat552X.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// MiniGun
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/ak47lowq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// psg1lowq
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/psg1lowq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// spas12lq
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/spas12lq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// g3lowqua
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/g3lowqua.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// l96a1low
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/l96a1low.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// w_awp10
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/w_awp10.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/FordGT40.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif

#if 0
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/Ducati.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
#endif

	return true;
}

bool QActiveFramewrk::acAmpInit(void)
{
#if 0
#if 1
	/////// Prepare Character Data ///////
	Q.StartCharacterData();
#else
	
	/////// Load Character Data ///////
	Q.LoadCharacterData();
#endif
#endif
	
#if 0
	////// Reset Character Data to Factory Defaults //////
	Q.ResetCharacterData();
#endif

	//// LEGACY Start Points - [Deprecated] ////
	for(int f_Scan = 0; f_Scan < 50; f_Scan++)
		{
		Q_StartPoints->StartPoints[f_Scan].Team = f_Scan;

		Q_StartPoints->StartPoints[f_Scan].Pos.x = 0;
		Q_StartPoints->StartPoints[f_Scan].Pos.y = 0;
		Q_StartPoints->StartPoints[f_Scan].Pos.z = 0;

		Q_StartPoints->StartPoints[f_Scan].Ang.x = 0;
		Q_StartPoints->StartPoints[f_Scan].Ang.y = 0;
		Q_StartPoints->StartPoints[f_Scan].Ang.z = 0;

		Q_StartPoints->StartPoints[f_Scan].ORIGPos.x = 0;
		Q_StartPoints->StartPoints[f_Scan].ORIGPos.y = 0;
		Q_StartPoints->StartPoints[f_Scan].ORIGPos.z = 0;
		
		Q_StartPoints->StartPoints[f_Scan].VecRight.x = 1;
		Q_StartPoints->StartPoints[f_Scan].VecRight.y = 0;
		Q_StartPoints->StartPoints[f_Scan].VecRight.z = 0;
		}

	_->screenx = 800;
    _->screeny = 600;
	mpos.x = _->screenx/2;
	mpos.y = _->screeny/2;

	_->Origin.x = 0;
	_->Origin.y = 0;
	_->Origin.z = 0;

	_->GenericLightPos.x = 0;
	_->GenericLightPos.y = -250;
	_->GenericLightPos.z = 0;

	player[g_Player]->QformChk = false;

#if 0
	for(int f_array = 0; f_array < 150000; f_array++)
		{
		Q_Bullet->Bullet[f_array].Live = 0;
		}
#endif
	
		//Seed the random generator with the time
#if defined(WIN32)
	time_t f_time;
	time(&f_time);
	srand(f_time);
#else
	srand( (unsigned)time(NULL) );
#endif

	//### LOAD INTRO

	LOADED_FACTORY[4] = 0;
	LOADED_FACTORY[5] = 0;
	LOADED_FACTORY[6] = 0;
	LOADED_FACTORY[7] = 0;
	LOADED_FACTORY[8] = 0;
	LOADED_FACTORY[9] = 0;
	LOADED_FACTORY[10] = 0;
	LOADED_FACTORY[11] = 0;
	LOADED_FACTORY[12] = 0;
	LOADED_FACTORY[13] = 0;
	LOADED_FACTORY[14] = 0;

// Define Bone Names / Numbers *****************************************************************************
//**********************************************************************************************************
								//OPTIMISE  Remove bones not needed
	BoneDef[0] = "BIP01 HEAD";
	BoneDef[1] = "BIP01 L CALF";
	BoneDef[2] = "BIP01 L CLAVICLE";
	BoneDef[3] = "BIP01 L FOOT";
	BoneDef[4] = "BIP01 L FOREARM";
	BoneDef[5] = "BIP01 L HAND";
	BoneDef[6] = "BIP01 L THIGH";
	BoneDef[7] = "BIP01 L UPPERARM";
	BoneDef[8] = "BIP01 NECK";
	BoneDef[9] = "BIP01 PELVIS";
	BoneDef[10] = "BIP01 R CALF";
	BoneDef[11] = "BIP01 R CLAVICLE";
	BoneDef[12] = "BIP01 R FOOT";
	BoneDef[13] = "BIP01 R FOREARM";
	BoneDef[14] = "BIP01 R HAND";
	BoneDef[15] = "BIP01 R THIGH";
	BoneDef[16] = "BIP01 R UPPERARM";
	BoneDef[17] = "BIP01 SPINE";
	BoneDef[18] = "BIP01 SPINE1";
	BoneDef[19] = "BIP01 SPINE2";
	//BoneDef[20] = "BIP01 SPINE3";
	BoneDef[20] = "BIP01 SPINE2";

	Q.StructureAInitialize();
	
	qBoneNum[0] = 8;			//THIS NEEDS CHECKING <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	qBoneNum[1] = 48;
	qBoneNum[2] = 9;
	qBoneNum[3] = 49;
	qBoneNum[4] = 11;
	qBoneNum[5] = 12;
	qBoneNum[6] = 47;
	qBoneNum[7] = 10;
	qBoneNum[8] = 7;
	qBoneNum[9] = 2;		//<-May be 1 or 0
	qBoneNum[10] = 52;
	qBoneNum[11] = 28;
	qBoneNum[12] = 53;
	qBoneNum[13] = 30;
	qBoneNum[14] = 31;
	qBoneNum[15] = 51;
	qBoneNum[16] = 29;
	qBoneNum[17] = 3;
	qBoneNum[18] = 4;
	qBoneNum[19] = 5;
	//qBoneNum[20] = 6;
	qBoneNum[20] = 5;

// Define Angel Edit Pointer *******************************************************************************
//**********************************************************************************************************

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[0].MAPNAME, "Hair");
	Q_ANGELeditMAP->ANGELeditMAP[0].MAPPOINTER = 3;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[1].MAPNAME, "Shoulders");
	Q_ANGELeditMAP->ANGELeditMAP[1].MAPPOINTER = 30;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[2].MAPNAME, "Face");
	Q_ANGELeditMAP->ANGELeditMAP[2].MAPPOINTER = 4;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[3].MAPNAME, "Left Ear");
	Q_ANGELeditMAP->ANGELeditMAP[3].MAPPOINTER = 5;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[4].MAPNAME, "Right Ear");
	Q_ANGELeditMAP->ANGELeditMAP[4].MAPPOINTER = 0;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[5].MAPNAME, "Nose");
	Q_ANGELeditMAP->ANGELeditMAP[5].MAPPOINTER = 10;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[6].MAPNAME, "Mouth");
	Q_ANGELeditMAP->ANGELeditMAP[6].MAPPOINTER = 11;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[7].MAPNAME, "Left Eye Socket");
	Q_ANGELeditMAP->ANGELeditMAP[7].MAPPOINTER = 7;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[8].MAPNAME, "Left Eye");
	Q_ANGELeditMAP->ANGELeditMAP[8].MAPPOINTER = 6;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[9].MAPNAME, "Right Eye Socket");
	Q_ANGELeditMAP->ANGELeditMAP[9].MAPPOINTER = 9;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[10].MAPNAME, "Right Eye");
	Q_ANGELeditMAP->ANGELeditMAP[10].MAPPOINTER = 8;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[11].MAPNAME, "Neck");
	Q_ANGELeditMAP->ANGELeditMAP[11].MAPPOINTER = 12;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[12].MAPNAME, "Left Hand");
	Q_ANGELeditMAP->ANGELeditMAP[12].MAPPOINTER = 15;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[13].MAPNAME, "Butt Skin");
	Q_ANGELeditMAP->ANGELeditMAP[13].MAPPOINTER = 33;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[14].MAPNAME, "BackPack");
	Q_ANGELeditMAP->ANGELeditMAP[14].MAPPOINTER = 25;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[15].MAPNAME, "Boot Tongues");
	Q_ANGELeditMAP->ANGELeditMAP[15].MAPPOINTER = 26;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[16].MAPNAME, "Boot Soles");
	Q_ANGELeditMAP->ANGELeditMAP[16].MAPPOINTER = 27;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[17].MAPNAME, "Left Arm");
	Q_ANGELeditMAP->ANGELeditMAP[17].MAPPOINTER = 13;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[18].MAPNAME, "Right Hand");
	Q_ANGELeditMAP->ANGELeditMAP[18].MAPPOINTER = 17;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[19].MAPNAME, "Left Forearm");
	Q_ANGELeditMAP->ANGELeditMAP[19].MAPPOINTER = 14;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[20].MAPNAME, "Right Forearm");
	Q_ANGELeditMAP->ANGELeditMAP[20].MAPPOINTER = 1;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[21].MAPNAME, "Right Arm");
	Q_ANGELeditMAP->ANGELeditMAP[21].MAPPOINTER = 16;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[22].MAPNAME, "Left Boot");
	Q_ANGELeditMAP->ANGELeditMAP[22].MAPPOINTER = 19;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[23].MAPNAME, "Left Calf");
	Q_ANGELeditMAP->ANGELeditMAP[23].MAPPOINTER = 18;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[24].MAPNAME, "Left Thigh Band");
	Q_ANGELeditMAP->ANGELeditMAP[24].MAPPOINTER = 32;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[25].MAPNAME, "Collar");
	Q_ANGELeditMAP->ANGELeditMAP[25].MAPPOINTER = 34;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[26].MAPNAME, "Chest");
	Q_ANGELeditMAP->ANGELeditMAP[26].MAPPOINTER = 23;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[27].MAPNAME, "Stomach");
	Q_ANGELeditMAP->ANGELeditMAP[27].MAPPOINTER = 24;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[28].MAPNAME, "Right Boot");
	Q_ANGELeditMAP->ANGELeditMAP[28].MAPPOINTER = 20;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[29].MAPNAME, "Right Calf");
	Q_ANGELeditMAP->ANGELeditMAP[29].MAPPOINTER = 2;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[30].MAPNAME, "Left Thigh");
	Q_ANGELeditMAP->ANGELeditMAP[30].MAPPOINTER = 21;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[31].MAPNAME, "Right Thigh");
	Q_ANGELeditMAP->ANGELeditMAP[31].MAPPOINTER = 22;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[32].MAPNAME, "Head Aerials");
	Q_ANGELeditMAP->ANGELeditMAP[32].MAPPOINTER = 28;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[33].MAPNAME, "Right Thigh Band");
	Q_ANGELeditMAP->ANGELeditMAP[33].MAPPOINTER = 31;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[34].MAPNAME, "Boot Front");
	Q_ANGELeditMAP->ANGELeditMAP[34].MAPPOINTER = 29;

// Trail Fade Vars *****************************************************************************************
//**********************************************************************************************************

	player[g_Player]->TrailFadeSpan[0][0] = 0;
	player[g_Player]->TrailFadeSpan[1][0] = 0;
	player[g_Player]->TrailFadeSpan[2][0] = 0;
	player[g_Player]->TrailFadeSpan[3][0] = 0;
	player[g_Player]->TrailFadeSpan[4][0] = 0;
	player[g_Player]->TrailFadeSpan[5][0] = 0;
	player[g_Player]->TrailFadeSpan[6][0] = 0;
	player[g_Player]->TrailFadeSpan[7][0] = 0;
	player[g_Player]->TrailFadeSpan[8][0] = 0;
	player[g_Player]->TrailFadeSpan[9][0] = 0;
	player[g_Player]->TrailFadeSpan[0][1] = 0;
	player[g_Player]->TrailFadeSpan[1][1] = 1;
	player[g_Player]->TrailFadeSpan[2][1] = 2;
	player[g_Player]->TrailFadeSpan[3][1] = 3;
	player[g_Player]->TrailFadeSpan[4][1] = 4;
	player[g_Player]->TrailFadeSpan[5][1] = 5;
	player[g_Player]->TrailFadeSpan[6][1] = 6;
	player[g_Player]->TrailFadeSpan[7][1] = 7;
	player[g_Player]->TrailFadeSpan[8][1] = 8;
	player[g_Player]->TrailFadeSpan[9][1] = 9;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

// Bitmap init *********************************************************************************************
//**********************************************************************************************************

	//#### TEXTURE SETUP
	
#ifndef QAGEMODE_NOEFFECTS
	Q.InitTextures();
#endif

#if 0
	Q.BlatTextures();
#endif

	//#### SOUND SETUP

#if 1
	Q.InitSounds();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

//**********************************************************************************************************
//**********************************************************************************************************

	Qpo->Transform_New_XRotation(&Xrot90deg, -(PI/2));

// Setup World / Load entities *****************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

	//### Load Player Start Point

	//### TODO Create Level Far clip distance Entity ###
	VisClipDist	= 2000;
	
#pragma message ("SET - _->NomAI, CURRCHAR, _->NetworkOption")
#pragma message ("FIXME: Fake Library Data")

	player[g_Player]->BFO.GAMEOPTIONS.FrameratelimiterON = 1;

#if 1
	_->FRL_LIMIT = 60;
#endif

//**********************************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

// Setup the player ########################################################################################
//##########################################################################################################
//##########################################################################################################

	#pragma message ("Lighting Table")

	// Setup the player specific flags
	player[g_Player]->PlayerHeight = PLAYER_HEIGHT;
	player[g_Player]->PlayerSpeed = PLAYER_SPEED;
	player[g_Player]->ForwardSpeed = 0;
	player[g_Player]->upspeed = -15;
	player[g_Player]->camrotdist = 1000;
	player[g_Player]->GravityAlter = 1;
	player[g_Player]->AirJinkPrep = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 0
	Q.WriteMeMPathways();
#endif

#if 0
	Q.ReadMeMPathways();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//#### ENERGY MATRIX SETUP

	Q_EnergyMatrix->EnergyMatrix.GlobalSCALE = 100;

	player[g_Player]->EnergyArchitect.ExpandSTRENGTH = 1.15;
	TestfloatALPHA1 = 7.149;
	TestfloatALPHA2 = 1.15;

	_->WorldScale = 1;

	player[g_Player]->Invisible = 0;

	player[g_Player]->Team = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].TEAM;

	//Fill Weapon Ammo
	player[g_Player]->WeaponAmmo = 32;

	player[g_Player]->Mins.x = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	player[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    player[g_Player]->Mins.z = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.x = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    player[g_Player]->Maxs.z = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->upspeed = 0;

	playerAV[g_Player]->Mins.x = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
    playerAV[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    playerAV[g_Player]->Mins.z = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.x = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.z = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//ACTOR SETUP AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);

	player[g_Player]->HB_Armour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	player[g_Player]->HB_MaxArmour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	player[g_Player]->HB_MaxHealth = 1000 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/100)*0.6)+0.4);
	player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;

	//player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

	player[g_Player]->HB_Dead = 0;

	player[g_Player]->JINK3_PowerFactor = 1;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	player[g_Player]->HB_LastAvatarHitID = -1;

	/////- AMP Load Meshes -/////
	if(!acAmpMesh())
		{
		//unConsoleAttribute(CONSOLE_ERROR);
		//printf("ERROR:::acAmpMesh - return not reached.\n");
		//unConsoleAttribute(CONSOLE_INIT);
		}

	//#### RENZOU
	aero=0;
	while(aero < 150)
		{
		helly=0;
		while(helly < 5)
			{
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Avatar = 0;

			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.x = 1;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.y = 1;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.z = 1;

			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.x = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.y = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.z = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.x = 20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.y = 20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.z = 20.f;

			Qpo->Vec3d_Copy(&_->Origin, &Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Xform.Translation);

#if 0
#ifndef QAGEMODE_NOINTRO
			acNamePlateUpdate();
#endif
#endif
			helly++;
			}

#if 0
		Q_SEnergy->SEnergy[aero].Const_TurnDull = 2500;
#endif

		Q_SEnergy->SEnergy[aero].Const_TurnDull = 50000;

#if 0
		Q_SEnergy->SEnergy[aero].Const_AngleInc = 0.2;
#endif

		Q_SEnergy->SEnergy[aero].Const_AngleInc = 1;

#if 0
#ifndef QAGEMODE_NOINTRO
		acNamePlateUpdate();
#endif
#endif

		_->MaxNomSEnergy++;

		aero++;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	aero=0;
	while(aero < 25)	//aero < (_->NomAI) <--- History
		{
		Q_LEnergy->LEnergy[aero].Live = 0;

		Q_LEnergy->LEnergy[aero].EnergyBall.Avatar = 0;

		Q_LEnergy->LEnergy[aero].EnergyBall.Mins.x = -20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Mins.y = -20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Mins.z = -20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.x = 20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.y = 20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.z = 20.f;

#if 1
		Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[aero].EnergyBall, 40, 40, 40);
		Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[aero].EnergyBall, 0);
#endif

		Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation);

#if 0
#ifndef QAGEMODE_NOINTRO
		acNamePlateUpdate();
#endif
#endif

		_->MaxNomLEnergy++;
		aero++;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//############ - Player Inititialisation - #############

	playerAV[g_Player]->Avatar.Mesh = new unAvatar();

	player[g_Player]->BFO.BDATID = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF;

	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class = 0;

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF > 11 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF = 0;

#if 1
	//if(AVATAR_PHYSICS_ENABLE) meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF);
	//else meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct(playerAV[g_Player]->Avatar.Mesh);
#else
	if(AVATAR_PHYSICS_ENABLE) meshdigiShellTemplates[f_PlayerID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, f_PlayerID);
	else meshdigiShellTemplates[f_PlayerID]->clone_struct(playerAV[g_Player]->Avatar.Mesh);
#endif

#if defined(ENABLE_NX_PHYSICS)
#if 0
	playerAV[g_Player]->Avatar.Mesh->addClothAttachment(meshShellTemplates[0]->m_Cloth[0], 0, 0, 0);
#endif
#endif

	playerAV[g_Player]->Xform.Translation.x = 0;
	playerAV[g_Player]->Xform.Translation.y = 350;
	playerAV[g_Player]->Xform.Translation.z = 0;

	playerAV[g_Player]->Xform.Matrix.load_identity();

	player[g_Player]->HB_DeadTimerC = 1500;

	playerAV[g_Player]->CollisionCount = 0;

	//##### Starting position
	Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
	Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); 
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, Ange.x);
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, Ange.y);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Ange.z);

	player[g_Player]->STOREMatrix = playerAV[g_Player]->Xform;

	//#### RESET SPELLS
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[3].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[4].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[5].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[6].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[7].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[8].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[9].LIVE = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 1
									//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
	Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	#pragma message ("Add Actor SCALE")

	// Set the actor to its position
	Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[player[g_Player]->Team].Pos, &playerAV[g_Player]->Xform.Translation);

	player[g_Player]->Angles.x = -1.05;
	player[g_Player]->Angles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	player[g_Player]->trueAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	//player[g_Player]->STOREAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;

	fogbox.Min.x = playerAV[g_Player]->Mins.x;
	fogbox.Min.y = playerAV[g_Player]->Mins.y;
	fogbox.Min.z = playerAV[g_Player]->Mins.z;
	fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	fogbox.Max.z = playerAV[g_Player]->Maxs.z;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	player[g_Player]->idlespeed = 0.1;

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->STOREMatrix.Translation);

	playerAV[g_Player]->Avatar.IDflag = 250;

	player[g_Player]->AttackSoundTRIG = 0;

	//### Load Player Weapon
	player[g_Player]->Weapon.Avatar = 1;

	player[g_Player]->Weapon.Scale.x = 1;
	player[g_Player]->Weapon.Scale.y = 1;
	player[g_Player]->Weapon.Scale.z = 1;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	#pragma message ("Add Weapon SCALE")
#if 0
	Qpo->Avatar_SetScale(&player[g_Player]->Weapon.Avatar, 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Weapon.Xform.Translation);

	player[g_Player]->WeaponDISPLAY = 0;

	player[g_Player]->QformONtaunt = 1;

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
		{
		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shield.Xform.Translation);

		player[g_Player]->Shield.Mins.x = -500.f;
		player[g_Player]->Shield.Mins.y = -500.f;
		player[g_Player]->Shield.Mins.z = -500.f;
		player[g_Player]->Shield.Maxs.x = 500.f;
		player[g_Player]->Shield.Maxs.y = 500.f;
		player[g_Player]->Shield.Maxs.z = 500.f;

		fogbox.Min.x = player[g_Player]->Shield.Mins.x;
		fogbox.Min.y = player[g_Player]->Shield.Mins.y;
		fogbox.Min.z = player[g_Player]->Shield.Mins.z;
		fogbox.Max.x = player[g_Player]->Shield.Maxs.x;
		fogbox.Max.y = player[g_Player]->Shield.Maxs.y;
		fogbox.Max.z = player[g_Player]->Shield.Maxs.z;

#if 0
		QpoActor_SetScale(player[g_Player]->Shield.Avatar, 0.65f,0.65f,0.65f);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shield.Avatar, 150);
#endif

		player[g_Player]->Shield.Avatar.IDflag = 251;
		}

	//### Load Player Shadows
	helly = 0;
	while(helly <= 2)
		{
		helly++;

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF > 11 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF = 0;

		//player[g_Player]->Shadows[helly].Avatar.Mesh = new unAvatar();
		//meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);

		player[g_Player]->Shadows[helly].Xform.Translation.x = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.y = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.z = 0;
		player[g_Player]->Shadows[helly].Xform.Matrix.load_identity();

		//##### Starting position
		Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
		Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
		if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
		Ange.x=-(PI/2);
		Ange.z=0;

		// Set the actor's angle
		Qpo->Transform_RotateX(&player[g_Player]->Shadows[helly].Xform, Ange.x);
		Qpo->Transform_RotateY(&player[g_Player]->Shadows[helly].Xform, Ange.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Shadows[helly].Xform, Ange.z);

#if 0
										//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
		poActor_SetScale(player[g_Player]->Shadows[helly].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

		player[g_Player]->Shadows[helly].Mins.x = -20.f;
		player[g_Player]->Shadows[helly].Mins.y = -20.f;
		player[g_Player]->Shadows[helly].Mins.z = -20.f;
		player[g_Player]->Shadows[helly].Maxs.x = 20.f;
		player[g_Player]->Shadows[helly].Maxs.y = 20.f;
		player[g_Player]->Shadows[helly].Maxs.z = 20.f;

		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[helly].Xform.Translation);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shadows[helly].Avatar, 255/(helly+1));

		player[g_Player]->Shadows[helly].Avatar.IDflag = 250;
		}

	player[g_Player]->ShadowALPHA = 240;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//##### SPAWN EFFECTS
#if 1
	jet = 0;
	while(jet < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 750) _->NomSpikes = 0;

		jet++;
		}
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItems();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Vehicle.Model.Xform.Translation);

	player[g_Player]->Vehicle.Model.Mins.x = -20.f;
	player[g_Player]->Vehicle.Model.Mins.y = -20.f;
	player[g_Player]->Vehicle.Model.Mins.z = -20.f;
	player[g_Player]->Vehicle.Model.Maxs.x = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.y = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.z = 20.f;

#if 0
	player[g_Player]->Vehicle.Model.Motion[0] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelSpin" );
	player[g_Player]->Vehicle.Model.Motion[1] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelScale" );
	player[g_Player]->Vehicle.Model.Motion[2] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelSpin" );
	player[g_Player]->Vehicle.Model.Motion[3] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelTurn" );
	player[g_Player]->Vehicle.Model.Motion[4] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelScale" );

	Ange.y=PI;
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	Qpo->Transform_RotateX(&player[g_Player]->Vehicle.Model.Xform, Ange.x);
	Qpo->Transform_RotateY(&player[g_Player]->Vehicle.Model.Xform, Ange.y);
	Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.Model.Xform, Ange.z);

	QpoActor_SetScale(player[g_Player]->Vehicle.Model.Avatar, 1.2f,1.2f,1.2f);
#endif

	player[g_Player]->Vehicle.Model.Avatar.IDflag = 250;

	//### Physics Setup
	player[g_Player]->Vehicle.Const_Weight = 8;	//Ten Q_Kgs
	player[g_Player]->Vehicle.Const_FWeight = 2;	//1.5
	player[g_Player]->Vehicle.Const_RWeight = 2;	//1.5
	player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0.335;

	player[g_Player]->Vehicle.Const_SpinCancel = 0.25;	//1.8
	player[g_Player]->Vehicle.Const_SpringLift = 7.5;	//2.5  1.23
	player[g_Player]->Vehicle.Const_SpringPower = 4;
	player[g_Player]->Vehicle.Const_WheelSettleSpin = 5;
	player[g_Player]->Vehicle.Const_WheelSettleDVel = 3.5;
	player[g_Player]->Vehicle.Const_SpringLimit = 14.5;
	player[g_Player]->Vehicle.Const_DownVelCancel = 3;
	player[g_Player]->Vehicle.Const_ForceFactor = 50;	//5
	player[g_Player]->Vehicle.Const_SpringAbsorbVel = 6.6;
	player[g_Player]->Vehicle.Const_SpringAbsorbSpin = 1.15;
	player[g_Player]->Vehicle.Const_LightTouchFactor = 1.15;
	player[g_Player]->Vehicle.Const_MaxSpeed = 100;

	player[g_Player]->Vehicle.Const_SpringCrunchMAX = 15;
	//player[g_Player]->Vehicle.Const_MiddleCOGDIST = -31;
	//player[g_Player]->Vehicle.Const_SpringCompDist = 20;

	player[g_Player]->Vehicle.Const_FRICMinSlide = 15;

	//#### BUILD CRUNCH UP VECS
	player[g_Player]->Vehicle.ConstVec_FCrunch.x = 1.071;
	player[g_Player]->Vehicle.ConstVec_FCrunch.y = 7.887;
	player[g_Player]->Vehicle.ConstVec_FCrunch.z = 3.893;

	player[g_Player]->Vehicle.ConstVec_RCrunch.x = 1.102;
	player[g_Player]->Vehicle.ConstVec_RCrunch.y = 8.116;
	player[g_Player]->Vehicle.ConstVec_RCrunch.z = 1.521;

	player[g_Player]->Vehicle.GravityAlter = 1;

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#if 0
	//##### - Switch to Air Jink - #####
	player[g_Player]->JumpPoseINC = 0.06;
	player[g_Player]->jumpposecnt = 0.33;
	player[g_Player]->blendamount[48] = 0.1;
	player[g_Player]->AirJinkRotFG = 0;
	player[g_Player]->AirJinkInit = 0;

	player[g_Player]->attposecnt = 0;
	player[g_Player]->Aposestate = 0;
	player[g_Player]->blendamount[0] = 0;
	player[g_Player]->blendamount[45] = 0;
	player[g_Player]->attackon = 0;
	player[g_Player]->astackcnt = 0;
	player[g_Player]->astackrun = 0;
	player[g_Player]->astackcntdir[0] = 0;
	player[g_Player]->AttackPos = 0;
	player[g_Player]->TimeHoleFLAG = 0;
	player[g_Player]->JinkSpecialON = 0;
	player[g_Player]->JinkInit = 0;
	player[g_Player]->Q_Jink.ON = 0;
	player[g_Player]->DownSpeed = 0.5 * ((0.5 * player[g_Player]->GravityAlter) + (0.8 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 500)));

		//# Spin Player Back
	player[g_Player]->AirJinkRotFG = 0;
	player[g_Player]->ROTATEMatrix = player[g_Player]->STOREMatrix;
	player[g_Player]->AJAngles.y = player[g_Player]->trueAngles.y - player[g_Player]->STOREAngles.y;
	if(player[g_Player]->AJAngles.y > (2*PI)) player[g_Player]->AJAngles.y = player[g_Player]->AJAngles.y-(PI*2);
	if(player[g_Player]->AJAngles.y < 0) player[g_Player]->AJAngles.y = (PI*2) + player[g_Player]->AJAngles.y;
	Qpo->Transform_New_YRotation(&AIfriendly, player[g_Player]->AJAngles.y);	/// Originaly -
	Qpo->Transform_Multiply(&player[g_Player]->ROTATEMatrix, &AIfriendly, &player[g_Player]->ROTATEMatrix);
	QpoVec3d i_Vector = playerAV[g_Player]->Xform.Translation;
	playerAV[g_Player]->Xform = player[g_Player]->ROTATEMatrix;
	playerAV[g_Player]->Xform.Translation = i_Vector;

	player[g_Player]->Mposestate = 14;
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//*m_GUI->m_mode++;

	return true;
}

bool QActiveFramewrk::acStartInit(void)
{
#if 0
#ifdef QAMOD_ARENA
#if 1
	g_optionsresult = Q.ShowCharacterDialog();
#else
	g_optionsresult = 1;
	player[g_Player]->BFO.GameTypeSelect = 1;
#endif
#endif

#ifdef QAMOD_ARENA
		//###- QUIT -###//
	if(g_optionsresult < 1)
		{
		render_free();

#if 0 //QAGE_DESKTOP
		PostQuitMessage(0);
#endif

		g_QUITM = true;
		}
	else
#if 0
	if(1)
		{
		g_optionsresult = 1;
		player[g_Player]->BFO.GameTypeSelect = 1;
#else
		{
#endif
			//###- SINGLE PLAYER -###//
		if(g_optionsresult == 1)
			{
			if(player[g_Player]->BFO.GameTypeSelect == 1)
				{
				_->NomAI = 0;
				_->NetworkOption = 0;
				}
			else
				{
				if(player[g_Player]->BFO.GameTypeSelect == 0)
					{
					_->NomAI = player[g_Player]->BFO.NomAvatars;
					_->NetworkOption = 0;
					}
				}
			}
		else
			{
				//###- SPECTATING -###//
			if(g_optionsresult == 2)
				{
				if(player[g_Player]->BFO.GameTypeSelect == 1)
					{
					_->NomAI = 0;
					_->NetworkOption = 0;
					}
				else
					{
					if(player[g_Player]->BFO.GameTypeSelect == 0)
						{
						_->NomAI = player[g_Player]->BFO.NomAvatars;
						_->NetworkOption = 0;
						}
					}
				}
			else
				{
					//###- BEST_FIT MATCH-MAKING -###//
				if(g_optionsresult == 3)
					{
					if(player[g_Player]->BFO.GameTypeSelect == 1)
						{
						_->NomAI = 0;
						//player[g_Player]->BFO.CurrCHAR = 0;
						_->NetworkOption = 0;
						}
					else
						{
						if(player[g_Player]->BFO.GameTypeSelect == 0)
							{
							_->NomAI = player[g_Player]->BFO.NomAvatars;
							_->NetworkOption = 0;

							//*unsStringCompressor::AddReference();
							printf("Connecting to OSI Staging Server\n");

							//----- Connect to 'Unification QAGE Server'
							int i_clientPort = 10000;	//60007 10000
							Q_PlacementMarker->m_Count += 15;
							i_clientPort += Q_PlacementMarker->m_Count;

							printf("client port %i/n", i_clientPort);

							//*SocketDescriptor socketDescriptor(i_clientPort,0);

#if 1
							//*clientAddress.SetBinaryAddress("192.168.1.102");
#else
							clientAddress.SetBinaryAddress("localhost");
#endif

							//*clientAddress.port = i_clientPort;

							//*unPeer->Startup(1, 30, &socketDescriptor, 1);
							//*unPeer->SetOccasionalPing(true);

							bool Success = false;

#if 0
#if 0
							Success = unPeer->Connect("87.106.104.248", 10555, 0, 0);
#else
							Success = unPeer->Connect("localhost", 10358, "fractal18", (int) strlen("fractal18"));
#endif
#else
							//*Success = unPeer->Connect("82.165.16.114", 1858, "", 0);
#endif

							if(Success) printf("Connected to OSI Staging Server\n");
							else
								{
								printf("ERROR: Cannot connect to server\n");
								}

#if 0
#if 1
							serveAddress.SetBinaryAddress("87.106.104.248");
							printf("serveAddress.SetBinaryAddress 87.106.104.248\n");
#else
							serveAddress.SetBinaryAddress("localhost");
							printf("serveAddress.SetBinaryAddress = 'localhost'\n");
#endif
#else
							//*serveAddress.SetBinaryAddress("82.165.16.114");
							printf("serveAddress.SetBinaryAddress 82.16.165.114\n");
#endif

							//*serveAddress.port = 1855;

							///// Set the internal packet pump state
							if(m_PP_STATE == 0)
								{
								m_PP_STATE = 1;

								//m_mutex_unPeer = SDL_CreateMutex();
								//m_mutex_Packet = SDL_CreateMutex();
								//m_mutex_Request = SDL_CreateMutex();
								//m_mutex_State = SDL_CreateMutex();

								vec_Packet = new PacketVectorSwing();

								//*m_PacketSocket.m_unPeer = unPeer;
								m_PacketSocket.m_vec_Packet = vec_Packet;
								//m_PacketSocket.m_mutex_unPeer = m_mutex_unPeer;
								//m_PacketSocket.m_mutex_Packet = m_mutex_Packet;
								m_PacketSocket.Start();

								//*m_PacketPump.m_unPeer = unPeer;
								m_PacketPump.m_vec_Packet = vec_Packet;
								//m_PacketPump.m_mutex_unPeer = m_mutex_unPeer;
								//m_PacketPump.m_mutex_Packet = m_mutex_Packet;
								//m_PacketPump.m_mutex_State = m_mutex_State;
								m_PacketPump.m_QActiveFramework = this;
								QNetwork.m_QActiveFramework = this;
								//*m_PacketPump.serveAddress = serveAddress;
								//*m_PacketPump.clientAddress = clientAddress;
								m_PacketPump.Start();

								//*m_PacketStack.m_unPeer = unPeer;
								//m_PacketStack.m_mutex_unPeer = m_mutex_unPeer;
								//m_PacketStack.m_mutex_Request = m_mutex_Request;
								//m_PacketStack.m_UNSResRequest = &m_UNSResRequest;
								//m_PacketStack.m_DocumentBank = m_DocumentBank;
								//m_PacketStack.m_map_Documents = &m_map_Documents;
								//*m_PacketStack.serveAddress = serveAddress;
								//*m_PacketStack.clientAddress = clientAddress;
								m_PacketStack.Start();

								m_NetStart = true;
								}

							// Set the Packet Pump MODE
							m_PacketPump.m_PP_MODE = 1;
							}

						////////- Set the Network Option Flag -////////
						//_->NetworkOption = 1;

						player[g_Player]->BFO.GamePAUSE = true;

						//int m_PP_STATE_I;

						////SDL_mutexP(m_mutex_State);
						//m_PP_STATE_I = m_PP_STATE;
						////SDL_mutexV(m_mutex_State);

						while(player[g_Player]->BFO.GamePAUSE/* || m_PP_STATE_I < 3*/) //g_NetConnect
							{
							/////////- PAUSE -/////////

							////SDL_mutexP(m_mutex_State);
							//m_PP_STATE_I = m_PP_STATE;
							////SDL_mutexV(m_mutex_State);

							//if(m_PP_STATE_I == 5 || (player[g_Player]->BFO.GamePAUSE == false && (m_PP_STATE_I == 3 || m_PP_STATE_I == 4)))
							//	{
							//	m_PP_STATE_I = 10;

							//	//SDL_mutexP(m_mutex_State);
							//	m_PP_STATE = 10;	//STATE '10' GO GAME!
							//	//SDL_mutexV(m_mutex_State);

							//	player[g_Player]->BFO.GamePAUSE = false;
							//	}

							/////////- PAUSE -/////////
							}
						}
					}
				}
			}
		}
#endif
//## SETUP PLAYER ##########################################################################################
//##########################################################################################################
//##########################################################################################################

#else
	_->NomAI = 0;
	player[g_Player]->BFO.CurrCHAR = 0;
	_->NetworkOption = 0;
#endif

	if(g_optionsresult != 3) player[g_Player]->Team = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].TEAM;

	//Fill Weapon Ammo
	player[g_Player]->WeaponAmmo = 32;

	player[g_Player]->Mins.x = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	player[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    player[g_Player]->Mins.z = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.x = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    player[g_Player]->Maxs.z = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->upspeed = 0;

	playerAV[g_Player]->Mins.x = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
    playerAV[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    playerAV[g_Player]->Mins.z = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.x = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.z = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//ACTOR SETUP AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);

	player[g_Player]->HB_Armour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	player[g_Player]->HB_MaxArmour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	player[g_Player]->HB_MaxHealth = 1000 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/100)*0.6)+0.4);
	player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;

	//player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

	player[g_Player]->HB_Dead = 0;

	player[g_Player]->JINK3_PowerFactor = 1;

	//############ - Player Inititialisation - #############
	delete playerAV[g_Player]->Avatar.Mesh;
	playerAV[g_Player]->Avatar.Mesh = new unAvatar();

	player[g_Player]->BFO.BDATID = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF;

	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class = 0;

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF > 11 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF = 0;

#if 1
	//if(AVATAR_PHYSICS_ENABLE) meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF);
	//else meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct(playerAV[g_Player]->Avatar.Mesh);
#else
	if(AVATAR_PHYSICS_ENABLE) meshdigiShellTemplates[f_PlayerID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, f_PlayerID);
	else meshdigiShellTemplates[f_PlayerID]->clone_struct(playerAV[g_Player]->Avatar.Mesh);
#endif

#if defined(ENABLE_NX_PHYSICS)
#if 0
	playerAV[g_Player]->Avatar.Mesh->addClothAttachment(meshShellTemplates[0]->m_Cloth[0], 0, 0, 0);
#endif
#endif

	player[g_Player]->HB_DeadTimerC = 1500;

	playerAV[g_Player]->CollisionCount = 0;

	//##### Starting position
	/*Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
	Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); 
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, Ange.x);
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, Ange.y);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Ange.z);*/

	//player[g_Player]->STOREMatrix = playerAV[g_Player]->Xform;

	//#### RESET SPELLS
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[3].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[4].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[5].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[6].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[7].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[8].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[9].LIVE = 0;

	// Set the actor to its position
	Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[player[g_Player]->Team].Pos, &playerAV[g_Player]->Xform.Translation);

	//player[g_Player]->Angles.x = -1.05;
	//player[g_Player]->Angles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	//player[g_Player]->trueAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	////player[g_Player]->STOREAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;

	fogbox.Min.x = playerAV[g_Player]->Mins.x;
	fogbox.Min.y = playerAV[g_Player]->Mins.y;
	fogbox.Min.z = playerAV[g_Player]->Mins.z;
	fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	fogbox.Max.z = playerAV[g_Player]->Maxs.z;

	player[g_Player]->idlespeed = 0.1;

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->STOREMatrix.Translation);

	playerAV[g_Player]->Avatar.IDflag = 250;

	player[g_Player]->AttackSoundTRIG = 0;

	//### Load Player Weapon
	player[g_Player]->Weapon.Avatar = 1;

	player[g_Player]->Weapon.Scale.x = 1;
	player[g_Player]->Weapon.Scale.y = 1;
	player[g_Player]->Weapon.Scale.z = 1;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	#pragma message ("Add Weapon SCALE")
#if 0
	Qpo->Avatar_SetScale(player[g_Player]->Weapon.Avatar, 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Weapon.Xform.Translation);

	player[g_Player]->WeaponDISPLAY = 0;

	player[g_Player]->QformONtaunt = 1;

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
		{
		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shield.Xform.Translation);

		player[g_Player]->Shield.Mins.x = -500.f;
		player[g_Player]->Shield.Mins.y = -500.f;
		player[g_Player]->Shield.Mins.z = -500.f;
		player[g_Player]->Shield.Maxs.x = 500.f;
		player[g_Player]->Shield.Maxs.y = 500.f;
		player[g_Player]->Shield.Maxs.z = 500.f;

		fogbox.Min.x = player[g_Player]->Shield.Mins.x;
		fogbox.Min.y = player[g_Player]->Shield.Mins.y;
		fogbox.Min.z = player[g_Player]->Shield.Mins.z;
		fogbox.Max.x = player[g_Player]->Shield.Maxs.x;
		fogbox.Max.y = player[g_Player]->Shield.Maxs.y;
		fogbox.Max.z = player[g_Player]->Shield.Maxs.z;

#if 0
		QpoActor_SetScale(player[g_Player]->Shield.Avatar, 0.65f,0.65f,0.65f);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shield.Avatar, 150);
#endif

		player[g_Player]->Shield.Avatar.IDflag = 251;
		}

	//### Load Player Shadows
	helly = 0;
	while(helly <= 2)
		{
		helly++;

		delete player[g_Player]->Shadows[helly].Avatar.Mesh;

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF > 11 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF = 0;

		//player[g_Player]->Shadows[helly].Avatar.Mesh = new unAvatar();
		//meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);

		player[g_Player]->Shadows[helly].Xform.Translation.x = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.y = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.z = 0;
		player[g_Player]->Shadows[helly].Xform.Matrix.load_identity();

		//##### Starting position
		Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
		Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
		if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
		Ange.x=-(PI/2);
		Ange.z=0;

		// Set the actor's angle
		Qpo->Transform_RotateX(&player[g_Player]->Shadows[helly].Xform, Ange.x);
		Qpo->Transform_RotateY(&player[g_Player]->Shadows[helly].Xform, Ange.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Shadows[helly].Xform, Ange.z);

#if 0
										//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
		poActor_SetScale(player[g_Player]->Shadows[helly].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

		player[g_Player]->Shadows[helly].Mins.x = -20.f;
		player[g_Player]->Shadows[helly].Mins.y = -20.f;
		player[g_Player]->Shadows[helly].Mins.z = -20.f;
		player[g_Player]->Shadows[helly].Maxs.x = 20.f;
		player[g_Player]->Shadows[helly].Maxs.y = 20.f;
		player[g_Player]->Shadows[helly].Maxs.z = 20.f;

		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[helly].Xform.Translation);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shadows[helly].Avatar, 255/(helly+1));

		player[g_Player]->Shadows[helly].Avatar.IDflag = 250;
		}

	player[g_Player]->ShadowALPHA = 240;

	//##### SPAWN EFFECTS
#if 1
	jet = 0;
	while(jet < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 750) _->NomSpikes = 0;

		jet++;
		}
#endif

#ifdef USE_CAPSULES
	if(player[g_Player]->WeaponStatus == 0) player[g_Player]->CamMatrix.Translation.y = playerAV[g_Player]->Xform.Translation.y + 20 + 25;
	else player[g_Player]->CamMatrix.Translation.y = playerAV[g_Player]->Xform.Translation.y + 20 + 25 + 30;

	player[g_Player]->CamMatrix.Translation.y *= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));

	PxMat33 f_GlobalPose;
	f_GlobalPose.createIdentity();
	PxMat33 f_LocalPose;
	f_LocalPose.createIdentity();

	g_ForgeBoxPlayer = DigiMass->acCreateBox(physx::PxVec3(0, 0, 0), 50 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 20 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 50, -1);
	g_PlayerForgeBoxxed = true;
#endif

	Q.ActivateItems();

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Vehicle.Model.Xform.Translation);

	player[g_Player]->Vehicle.Model.Mins.x = -20.f;
	player[g_Player]->Vehicle.Model.Mins.y = -20.f;
	player[g_Player]->Vehicle.Model.Mins.z = -20.f;
	player[g_Player]->Vehicle.Model.Maxs.x = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.y = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.z = 20.f;

#if 0
	player[g_Player]->Vehicle.Model.Motion[0] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelSpin" );
	player[g_Player]->Vehicle.Model.Motion[1] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelScale" );
	player[g_Player]->Vehicle.Model.Motion[2] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelSpin" );
	player[g_Player]->Vehicle.Model.Motion[3] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelTurn" );
	player[g_Player]->Vehicle.Model.Motion[4] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelScale" );

	Ange.y=PI;
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	Qpo->Transform_RotateX(&player[g_Player]->Vehicle.Model.Xform, Ange.x);
	Qpo->Transform_RotateY(&player[g_Player]->Vehicle.Model.Xform, Ange.y);
	Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.Model.Xform, Ange.z);

	QpoActor_SetScale(player[g_Player]->Vehicle.Model.Avatar, 1.2f,1.2f,1.2f);
#endif

	player[g_Player]->Vehicle.Model.Avatar.IDflag = 250;

	//### Physics Setup
	player[g_Player]->Vehicle.Const_Weight = 8;	//Ten Q_Kgs
	player[g_Player]->Vehicle.Const_FWeight = 2;	//1.5
	player[g_Player]->Vehicle.Const_RWeight = 2;	//1.5
	player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0.335;

	player[g_Player]->Vehicle.Const_SpinCancel = 0.25;	//1.8
	player[g_Player]->Vehicle.Const_SpringLift = 7.5;	//2.5  1.23
	player[g_Player]->Vehicle.Const_SpringPower = 4;
	player[g_Player]->Vehicle.Const_WheelSettleSpin = 5;
	player[g_Player]->Vehicle.Const_WheelSettleDVel = 3.5;
	player[g_Player]->Vehicle.Const_SpringLimit = 14.5;
	player[g_Player]->Vehicle.Const_DownVelCancel = 3;
	player[g_Player]->Vehicle.Const_ForceFactor = 50;	//5
	player[g_Player]->Vehicle.Const_SpringAbsorbVel = 6.6;
	player[g_Player]->Vehicle.Const_SpringAbsorbSpin = 1.15;
	player[g_Player]->Vehicle.Const_LightTouchFactor = 1.15;
	player[g_Player]->Vehicle.Const_MaxSpeed = 100;

	player[g_Player]->Vehicle.Const_SpringCrunchMAX = 15;
	//player[g_Player]->Vehicle.Const_MiddleCOGDIST = -31;
	//player[g_Player]->Vehicle.Const_SpringCompDist = 20;

	player[g_Player]->Vehicle.Const_FRICMinSlide = 15;

	//#### BUILD CRUNCH UP VECS
	player[g_Player]->Vehicle.ConstVec_FCrunch.x = 1.071;
	player[g_Player]->Vehicle.ConstVec_FCrunch.y = 7.887;
	player[g_Player]->Vehicle.ConstVec_FCrunch.z = 3.893;

	player[g_Player]->Vehicle.ConstVec_RCrunch.x = 1.102;
	player[g_Player]->Vehicle.ConstVec_RCrunch.y = 8.116;
	player[g_Player]->Vehicle.ConstVec_RCrunch.z = 1.521;

	player[g_Player]->Vehicle.GravityAlter = 1;

//## SETUP PLAYER ##########################################################################################
//##########################################################################################################
//##########################################################################################################

//## SETUP AI ##############################################################################################
//##########################################################################################################
//##########################################################################################################

// AI setup AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIA
//AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIA
//AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIA

#if 0
	//Increment all avatars by all game real players
	if(g_optionsresult == 3)
		{
		//#### Verify NomAvatars
		printf("=====================================\n");
		printf("=====================================\n");
		printf("==== player[g_Player]->BFO.NomAvatars %i ====\n", player[g_Player]->BFO.NomAvatars);
		printf("=====================================\n");
		printf("=====================================\n");

		_->NomAI = 0;
		int f_StartAI = 0;
		int f_StartAVID = -5;

		//Increment all avatars by all game AI players
		for(int f_BBB = 0; f_BBB < player[g_Player]->BFO.GamePlayersNom; f_BBB++)
			{
			printf("f_BBB %i m_PacketPump.m_ClientVectorID %i player[g_Player]->BFO.GamePlayersNom %i\n", f_BBB, m_PacketPump.m_ClientVectorID, player[g_Player]->BFO.GamePlayersNom);
			if(f_BBB == m_PacketPump.m_ClientVectorID)
				{
				Q_Forge->Forge[f_StartAI].LIVE = 0;		//Player Character
				Q_Forge->Forge[f_StartAI].m_Own = 0;
				Q_Forge->Forge[f_StartAI].NetplayerFLAG = 1;

				for(int f_GoAvatar = 0; f_GoAvatar < player[g_Player]->BFO.NomAvatars; f_GoAvatar++)
					{
					player[g_Player]->BFO.AVATARDATA[f_StartAI + f_GoAvatar + 1] = player[g_Player]->BFO.AVATARDATA[f_StartAI + f_GoAvatar];			
					}
				player[g_Player]->BFO.AVATARDATA[f_StartAI].LIVE = 0;

				printf("PlayerCH f_StartAI %i\n", f_StartAI);
				f_StartAI++;
				_->NomAI++;
				f_StartAVID = f_StartAI;

				for(int f_BBBlayers = 0; f_BBBlayers < player[g_Player]->BFO.vec_PlayersNom[f_BBB]; f_BBBlayers++)
					{
					Q_Forge->Forge[f_StartAI].LIVE = 0;
					Q_Forge->Forge[f_StartAI].m_Own = 1;
					Q_Forge->Forge[f_StartAI].NetplayerFLAG = 0;

					printf("INC = 1 f_StartAI %i\n", f_StartAI);
					f_StartAI++;
					_->NomAI++;
					}

				//f_BBB = player[g_Player]->BFO.GamePlayersNom;
				}
			else
				{
				Q_Forge->Forge[f_StartAI].LIVE = 0;		//Player Character
				Q_Forge->Forge[f_StartAI].m_Own = 0;
				Q_Forge->Forge[f_StartAI].NetplayerFLAG = 1;

				if(f_StartAVID == -5)
					{
					for(int f_GoAvatar = 0; f_GoAvatar < player[g_Player]->BFO.NomAvatars; f_GoAvatar++)
						{
						player[g_Player]->BFO.AVATARDATA[f_StartAI + f_GoAvatar + 1] = player[g_Player]->BFO.AVATARDATA[f_StartAI + f_GoAvatar];			
						}
					player[g_Player]->BFO.AVATARDATA[f_StartAI].LIVE = 0;
					}

				printf("WebCH f_StartAI %i\n", f_StartAI);
				f_StartAI++;
				_->NomAI++;

				for(int f_BBBlayers = 0; f_BBBlayers < player[g_Player]->BFO.vec_PlayersNom[f_BBB]; f_BBBlayers++)
					{
					Q_Forge->Forge[f_StartAI].LIVE = 0;
					Q_Forge->Forge[f_StartAI].m_Own = 0;
					Q_Forge->Forge[f_StartAI].NetplayerFLAG = 1;

					if(f_StartAVID == -5)
						{
						for(int f_GoAvatar = 0; f_GoAvatar < player[g_Player]->BFO.NomAvatars; f_GoAvatar++)
							{
							player[g_Player]->BFO.AVATARDATA[f_StartAI + f_GoAvatar + 1] = player[g_Player]->BFO.AVATARDATA[f_StartAI + f_GoAvatar];			
							}
						player[g_Player]->BFO.AVATARDATA[f_StartAI].LIVE = 0;
						}

					printf("INC = 0 f_StartAI %i\n", f_StartAI);
					f_StartAI++;
					_->NomAI++;
					}
				}
			}

		if(player[g_Player]->BFO.GameAvatarsMaxAmt != f_StartAI)
			{
			printf("ERROR GameAvatarsMaxAmt %i Not equal to f_StartAI %i,... FATAL\n", player[g_Player]->BFO.GameAvatarsMaxAmt, f_StartAI);
			for(;;) {}
			}
		}
	else	//Singleplayer owns all
		{
		for(i = 0; i < _->NomAI; i++)
			{
			Q_Forge->Forge[i].m_Own = 1;
			}
		}

	for(i = 0; i < _->NomAI; i++)
		{
		player[g_Player]->BFO.AVATARDATA[i].LIVE = 1;
		}

	printf("*****************************************************\n");
	printf("*****************************************************\n");
	printf("*****************************************************\n");
	printf("f_nomai %i\n", _->NomAI);
	for(int f_nomai = 0; f_nomai < _->NomAI; f_nomai++)
		{
		printf("%i ", Q_Forge->Forge[f_nomai].m_Own);
		}
	printf("*****************************************************\n");
	printf("*****************************************************\n");
	printf("*****************************************************\n");

	//###########=- SET ALL AI AVATARS -=#############
	if(_->NetworkOption != 1)
		{
		CharCounter = 0;
		helly = 0;
		while(helly < _->NomAI)
			{
			if(player[g_Player]->BFO.AVATARDATA[helly].LIVE == 1)
				{
				if(Q_Forge->Forge[helly].m_Own == 1) Q_Forge->Forge[helly].NetplayerFLAG = 0;
				else Q_Forge->Forge[helly].NetplayerFLAG = 1;

				Q_Forge->Forge[helly].AV.upspeed = -15;
				Q_Forge->Forge[helly].AV.Mins.x = -(20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
				Q_Forge->Forge[helly].AV.Mins.y = -(45 + (30*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
				Q_Forge->Forge[helly].AV.Mins.z = -(20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.x = (20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.y = (45 + (30*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.z = (20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

				Q_Forge->Forge[helly].PlayerSpeed = PLAYER_SPEED;

				Q_Forge->Forge[helly].GravityAlter = 1;

				//Fill Weapon Ammo
				Q_Forge->Forge[helly].WeaponAmmo = 32;

				Q_Forge->Forge[helly].HB_Illumination = 255;
				Q_Forge->Forge[helly].HB_Dead = 0;

				Q_Forge->Forge[helly].HB_DeadTimer = 500;
				Q_Forge->Forge[helly].HB_Lives = 5;
				Q_Forge->Forge[helly].HB_LiveResetSW = 1;

				//Body and Mind
				Q_Forge->Forge[helly].Q_Heart.HeartIncrement = 0;
				Q_Forge->Forge[helly].Q_Heart.PulseRate = 1;
				Q_Forge->Forge[helly].Q_Brain.Aggression = 70;

				//###### AVATAR SELECTION
				//### Obtain Correct Character Data for Avatar
				if(Q_Forge->Forge[helly].m_Own == 1)
					{
					Q_Forge->Forge[helly].CharDATA.CDataID = player[g_Player]->BFO.AVATARDATA[helly].CDATID;
					Q_Forge->Forge[helly].CharDATA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[helly].CDATID];
					Q_Forge->Forge[helly].CharDATA.BDataID = player[g_Player]->BFO.AVATARDATA[helly].BDATID;
					Q_Forge->Forge[helly].CharDATA.TEAM = player[g_Player]->BFO.AVATARDATA[helly].TEAM;
					Q_Forge->Forge[helly].Team = player[g_Player]->BFO.AVATARDATA[helly].TEAM;
					Q_Forge->Forge[helly].AVDATID = helly;
					player[g_Player]->BFO.AVATARDATA[helly].AVATARID = helly;
					}

				if(Q_Forge->Forge[helly].Team >= 50) Q_Forge->Forge[helly].Team = 50;
				
				//#### Set Role€
				Q_Forge->Forge[helly].Role = 0;
				Q_Forge->Forge[helly].Rank = 1;
				Q_Forge->Forge[helly].LEVEL = Q_Forge->Forge[helly].CharDATA.Level;

				#pragma message ("FIXME:::Start AI Start Position and initial pose")
				Q_Forge->Forge[helly].AV.Avatar.Mesh = new unAvatar();

#ifdef QAGE_OPMOD_B
				Q_Forge->Forge[helly].CharDATA.BDataID = 0;
#endif

				if(Q_Forge->Forge[helly].CharDATA.AvatarREF > 11 || Q_Forge->Forge[helly].CharDATA.AvatarREF < 0) Q_Forge->Forge[helly].CharDATA.AvatarREF = 0;

				//if(AVATAR_PHYSICS_ENABLE) meshShellTemplates[Q_Forge->Forge[helly].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[helly].AV.Avatar.Mesh, Q_Forge->Forge[helly].CharDATA.BDataID);
				//else meshShellTemplates[Q_Forge->Forge[helly].CharDATA.AvatarREF]->clone_struct(Q_Forge->Forge[helly].AV.Avatar.Mesh);

				/*Q_Forge->Forge[helly].Xform.Translation.x = 0;
				Q_Forge->Forge[helly].Xform.Translation.y = 0;
				Q_Forge->Forge[helly].Xform.Translation.z = 0;
				Q_Forge->Forge[helly].Xform.Matrix.load_identity();

				//##### Starting position
				Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
				//Ange.y=-(PI/2);//Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
				Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
				if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
				Ange.x=-(PI/2);
				Ange.z=0;

				// Set the actor's angle
				Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Xform, Ange.x);
				Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Xform, Ange.y);
				Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Xform, Ange.z);

				Q_Forge->Forge[helly].STOREMatrix = Q_Forge->Forge[helly].Xform;*/

#if 0
				QpoActor_SetScale(Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

				Q_Forge->Forge[helly].idlespeed = 0.1;

				if(Q_Forge->Forge[helly].LEVEL > 1000) Q_Forge->Forge[helly].LEVELFactor = 1;
				else Q_Forge->Forge[helly].LEVELFactor = (((float)Q_Forge->Forge[helly].LEVEL + 1) / 1000);

				Q_Forge->Forge[helly].HB_MaxHealth = 1000 * (((Q_Forge->Forge[helly].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
				Q_Forge->Forge[helly].HB_Health = Q_Forge->Forge[helly].HB_MaxHealth;

				Q_Forge->Forge[helly].HB_MaxEnergy = 500;
				Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;

				if(Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR < 0 || Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrHEADARMOUR %i Out of range\n", helly, Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR);
				else if(Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR < 0 || Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrUPPERARMOUR %i Out of range\n", helly, Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR);
				else if(Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR < 0 || Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrLOWERARMOUR %i Out of range\n", helly, Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR);
				else Q_Forge->Forge[helly].HB_MaxArmour = ((float)(Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
				Q_Forge->Forge[helly].HB_Armour = Q_Forge->Forge[helly].HB_MaxArmour;

				Q_Forge->Forge[helly].JINK3_PowerFactor = 1;

				//#### RESET SPELLS
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[3].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[4].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[5].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[6].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[7].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[8].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[9].LIVE = 0;

				//####### RELATIVE ATTACK SPEED
				Q_Forge->Forge[helly].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[helly].CharDATA.BodySKILL.Quickness / 100) * 0.8);

				//####### RELATIVE ENERGY EFFICIENCY
				Q_Forge->Forge[helly].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[helly].CharDATA.BodySKILL.EnergyEff / 6000);

				Q_Forge->Forge[helly].AV.Avatar.Visible = true;

				Q_Forge->Forge[helly].AV.Avatar.IDflag = helly;

#if 0
				Q_Forge->Forge[helly].AV.Motion[0] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle" );
				Q_Forge->Forge[helly].AV.Motion[1] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Walk" );
				Q_Forge->Forge[helly].AV.Motion[2] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Run" );
				Q_Forge->Forge[helly].AV.Motion[3] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Sidestep" );
				Q_Forge->Forge[helly].AV.Motion[4] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Jump" );
				Q_Forge->Forge[helly].AV.Motion[5] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LLPunch" );
				Q_Forge->Forge[helly].AV.Motion[6] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RLPunch" );
				Q_Forge->Forge[helly].AV.Motion[7] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RHPunch2" );	//RHPunch
				Q_Forge->Forge[helly].AV.Motion[8] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RMKick" );
				Q_Forge->Forge[helly].AV.Motion[9] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LMPunch" );	//LSPunch needs a home
				Q_Forge->Forge[helly].AV.Motion[10] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RMPunch" );
				Q_Forge->Forge[helly].AV.Motion[12] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WalkL" );
				Q_Forge->Forge[helly].AV.Motion[13] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WalkR" );
				Q_Forge->Forge[helly].AV.Motion[14] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunL" );
				Q_Forge->Forge[helly].AV.Motion[15] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunR" );
				Q_Forge->Forge[helly].AV.Motion[16] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SidestepL" );
				Q_Forge->Forge[helly].AV.Motion[17] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SidestepR" );
				Q_Forge->Forge[helly].AV.Motion[18] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Renzou" );		//TODO: Combine these two
				Q_Forge->Forge[helly].AV.Motion[19] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouE" );		//TODO: into one
				Q_Forge->Forge[helly].AV.Motion[20] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RSPunch" );
				Q_Forge->Forge[helly].AV.Motion[21] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Uppercut" );	//Uppercut
				Q_Forge->Forge[helly].AV.Motion[22] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HBlock" );
				Q_Forge->Forge[helly].AV.Motion[23] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle2" );
				Q_Forge->Forge[helly].AV.Motion[24] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouR" );
				Q_Forge->Forge[helly].AV.Motion[25] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon1" );
				Q_Forge->Forge[helly].AV.Motion[26] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunWep1L" );
				Q_Forge->Forge[helly].AV.Motion[27] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunWep1R" );
				Q_Forge->Forge[helly].AV.Motion[28] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep1" );
				Q_Forge->Forge[helly].AV.Motion[29] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AXKick" );
				Q_Forge->Forge[helly].AV.Motion[30] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SPKick" );
				Q_Forge->Forge[helly].AV.Motion[31] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpL" );
				Q_Forge->Forge[helly].AV.Motion[32] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpR" );
				Q_Forge->Forge[helly].AV.Motion[33] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Cartwheel" );
				Q_Forge->Forge[helly].AV.Motion[34] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon1UPP" );
				Q_Forge->Forge[helly].AV.Motion[35] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep1UPP" );
				Q_Forge->Forge[helly].AV.Motion[36] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CartWep1" );
				Q_Forge->Forge[helly].AV.Motion[37] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle3" );
				Q_Forge->Forge[helly].AV.Motion[38] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouL" );
				Q_Forge->Forge[helly].AV.Motion[39] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoldDash" );
				Q_Forge->Forge[helly].AV.Motion[40] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Knee" );
				Q_Forge->Forge[helly].AV.Motion[41] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpKick" );
				Q_Forge->Forge[helly].AV.Motion[42] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Wave" );
				Q_Forge->Forge[helly].AV.Motion[43] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HitStom" );
				Q_Forge->Forge[helly].AV.Motion[44] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HitUpper" );
				Q_Forge->Forge[helly].AV.Motion[45] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSpiral" );
				Q_Forge->Forge[helly].AV.Motion[46] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "DodgeL" );
				Q_Forge->Forge[helly].AV.Motion[47] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FKick" );
				Q_Forge->Forge[helly].AV.Motion[48] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunBack" );
				Q_Forge->Forge[helly].AV.Motion[53] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FallHead" );
				Q_Forge->Forge[helly].AV.Motion[54] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RHKick" );
				Q_Forge->Forge[helly].AV.Motion[55] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FlameUpperCut" );
				Q_Forge->Forge[helly].AV.Motion[56] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HBlockHit" );
				Q_Forge->Forge[helly].AV.Motion[57] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BackFlip" );
				Q_Forge->Forge[helly].AV.Motion[58] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload" );
				Q_Forge->Forge[helly].AV.Motion[59] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinKickFull" );
				Q_Forge->Forge[helly].AV.Motion[60] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Crouch" );
				Q_Forge->Forge[helly].AV.Motion[61] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CrouchL" );
				Q_Forge->Forge[helly].AV.Motion[62] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CrouchR" );
				Q_Forge->Forge[helly].AV.Motion[67] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "VHKick" );
				Q_Forge->Forge[helly].AV.Motion[68] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Entro" );
				Q_Forge->Forge[helly].AV.Motion[69] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwinDragon1" );
				Q_Forge->Forge[helly].AV.Motion[70] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwinDragon2" );
				Q_Forge->Forge[helly].AV.Motion[71] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Golrekka" );
				Q_Forge->Forge[helly].AV.Motion[72] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SkyPush" );
				Q_Forge->Forge[helly].AV.Motion[73] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Lowtro" );
				Q_Forge->Forge[helly].AV.Motion[74] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Lowkick" );
				Q_Forge->Forge[helly].AV.Motion[75] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Legsweep" );
				Q_Forge->Forge[helly].AV.Motion[76] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Crunch" );
				Q_Forge->Forge[helly].AV.Motion[77] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Hitwall" );
				Q_Forge->Forge[helly].AV.Motion[78] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AttFlip" );
				Q_Forge->Forge[helly].AV.Motion[79] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttP" );
				Q_Forge->Forge[helly].AV.Motion[80] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowPunchL" );
				Q_Forge->Forge[helly].AV.Motion[81] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowPunchR" );
				Q_Forge->Forge[helly].AV.Motion[82] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LBlock" );
				Q_Forge->Forge[helly].AV.Motion[83] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LBlockHit" );
				Q_Forge->Forge[helly].AV.Motion[84] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Hadouken" );
				Q_Forge->Forge[helly].AV.Motion[85] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HadoukenAir" );
				Q_Forge->Forge[helly].AV.Motion[86] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AirDash" );
				Q_Forge->Forge[helly].AV.Motion[87] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoverKick" );
				Q_Forge->Forge[helly].AV.Motion[88] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollF" );
				Q_Forge->Forge[helly].AV.Motion[89] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Taunt1" );
				Q_Forge->Forge[helly].AV.Motion[90] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Sakurat" );
				Q_Forge->Forge[helly].AV.Motion[91] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BrollyT" );
				Q_Forge->Forge[helly].AV.Motion[92] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PCombo1" );
				Q_Forge->Forge[helly].AV.Motion[93] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpiralDown" );
				Q_Forge->Forge[helly].AV.Motion[94] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSpiralOver" );
				Q_Forge->Forge[helly].AV.Motion[95] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmall" );
				Q_Forge->Forge[helly].AV.Motion[96] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwistKick" );
				Q_Forge->Forge[helly].AV.Motion[97] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BackFLipAtt" );
				Q_Forge->Forge[helly].AV.Motion[98] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Deflect" );
				Q_Forge->Forge[helly].AV.Motion[99] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmallL" );
				Q_Forge->Forge[helly].AV.Motion[100] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmallR" );
				Q_Forge->Forge[helly].AV.Motion[101] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PCombo2" );
				Q_Forge->Forge[helly].AV.Motion[102] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RushElbow" );
				Q_Forge->Forge[helly].AV.Motion[103] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoldBarge" );
				Q_Forge->Forge[helly].AV.Motion[104] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "DoubleStrike" );
				Q_Forge->Forge[helly].AV.Motion[105] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowLunge" );
				Q_Forge->Forge[helly].AV.Motion[106] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SideChop" );
				Q_Forge->Forge[helly].AV.Motion[107] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinChop" );
				Q_Forge->Forge[helly].AV.Motion[108] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollLowL" );
				Q_Forge->Forge[helly].AV.Motion[109] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollLowR" );
				//VEHICLE MOTIONS UNUSED
				//Q_Forge->Forge[helly].AV.Motion[110] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeMount" );
				//Q_Forge->Forge[helly].AV.Motion[111] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeRush" );
				//Q_Forge->Forge[helly].AV.Motion[112] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeWheelie" );
				//Q_Forge->Forge[helly].AV.Motion[113] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeIdle" );
				Q_Forge->Forge[helly].AV.Motion[114] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouP" );
				Q_Forge->Forge[helly].AV.Motion[115] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouPR" );
				Q_Forge->Forge[helly].AV.Motion[116] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AttFlipE" );
				Q_Forge->Forge[helly].AV.Motion[117] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HandSlap" );
				Q_Forge->Forge[helly].AV.Motion[118] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSH" );
				Q_Forge->Forge[helly].AV.Motion[119] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHPUNCH" );
				Q_Forge->Forge[helly].AV.Motion[120] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHBG" );
				Q_Forge->Forge[helly].AV.Motion[121] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHKICK" );
				Q_Forge->Forge[helly].AV.Motion[122] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "StaticKick" );
				Q_Forge->Forge[helly].AV.Motion[123] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttK" );
				Q_Forge->Forge[helly].AV.Motion[124] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RDoubleKick" );
				Q_Forge->Forge[helly].AV.Motion[125] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReloadUPP" );
				Q_Forge->Forge[helly].AV.Motion[126] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttK" );
				Q_Forge->Forge[helly].AV.Motion[127] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PowerBomb" );
				Q_Forge->Forge[helly].AV.Motion[128] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LeapDownStrike" );
				Q_Forge->Forge[helly].AV.Motion[129] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RSPINSTRIKE" );
				Q_Forge->Forge[helly].AV.Motion[130] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinoutLeft" );
				Q_Forge->Forge[helly].AV.Motion[131] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "OverheadPinwheel" );
				Q_Forge->Forge[helly].AV.Motion[132] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LeapDownFist" );
				Q_Forge->Forge[helly].AV.Motion[140] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LookRight" );

				if(Q_Forge->Forge[helly].CharDATA.Class == 2)
					{
					Q_Forge->Forge[helly].AV.Motion[63] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Glance" );
					Q_Forge->Forge[helly].AV.Motion[65] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HealUPP" );
					Q_Forge->Forge[helly].AV.Motion[66] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Heal" );
					}

				Q_Forge->Forge[helly].AV.Motion[133] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon2" );
				Q_Forge->Forge[helly].AV.Motion[134] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon2UPP" );
				Q_Forge->Forge[helly].AV.Motion[135] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep2" );
				Q_Forge->Forge[helly].AV.Motion[136] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep2UPP" );
				Q_Forge->Forge[helly].AV.Motion[137] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload2" );
				Q_Forge->Forge[helly].AV.Motion[138] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload2UPP" );
#endif

				//##### ATTENTION REQUIRED
#if 0
				Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
#endif

				Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);

#if 0
				//Lighting
				if(Q_AvatarEntity->AvatarEntity[helly].Team == 0)	//Friendly AI
					{
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 0)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 1)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 2)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
					}

				if(Q_AvatarEntity->AvatarEntity[helly].Team == 1)	//Enemy AI
					{
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 0) 
						{
#if 0
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&poop,255,180,180,220,220,220,false,8,NULL,true);
#endif

						Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
						}
					}
#endif

				//Starting Position Note: possibly not needed
				if(Q_Forge->Forge[helly].m_Own == 1) Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Pos, &Q_Forge->Forge[helly].AV.Xform.Translation);

				//Starting Rotation
				if(Q_Forge->Forge[helly].m_Own == 1) Ange.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y + (PI);
				else Ange.y = PI;
				if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
				Ange.x=-(PI/2);
				Ange.z=0;

				// Set the actor's angle
				Qpo->Transform_RotateX(&Q_Forge->Forge[helly].AV.Xform, Ange.x);		//Update Avatar's starting facing direction
				Qpo->Transform_RotateY(&Q_Forge->Forge[helly].AV.Xform, Ange.y);
				Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].AV.Xform, Ange.z);

				Q_Forge->Forge[helly].STOREMatrix = Q_Forge->Forge[helly].AV.Xform;

				if(Q_Forge->Forge[helly].m_Own == 1)
					{
					Q_Forge->Forge[helly].Angles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
					Q_Forge->Forge[helly].trueAngles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
					Q_Forge->Forge[helly].STOREAngles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
					}
				else
					{
					Q_Forge->Forge[helly].Angles.y = 0;
					Q_Forge->Forge[helly].trueAngles.y = 0;
					Q_Forge->Forge[helly].STOREAngles.y = 0;
					}

#if 0
				//m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec.y = 0;

				//Begin Transforming for Camera
				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[helly].AV.Xform, &Q_Forge->Forge[helly].AV.Up);

				Qpo->Vec3d_Subtract(&Q_Forge->Forge[helly].AV.Up, &m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec, &ScanTurnVec);
				Q_Forge->Forge[helly].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);

				//### Check Distance between Pure Left and Right to work out direction of Turn
				Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[helly].AV.Xform, &Q_Forge->Forge[helly].AV.Left);

				Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].AV.Left, &Q_Forge->Forge[helly].AV.Right);
				Qpo->Vec3d_Inverse(&Q_Forge->Forge[helly].AV.Right);

				ScanDistL = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec, &Q_Forge->Forge[helly].AV.Left);
				ScanDistR = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec, &Q_Forge->Forge[helly].AV.Right);

#if 0
				Qpo->Camera_Set();
				glColor3f(1.0f, 0.0f, 0.0f);	//RED
				//*glBegin(GL_LINES);
				glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
				glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Left.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Left.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Left.z * 250));
				//*glEnd();
#endif

#if 0
				Qpo->Camera_Set();
				glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
				//*glBegin(GL_LINES);
				glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
				glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Right.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Right.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Right.z * 250));
				//*glEnd();
#endif

#if 0
				Qpo->Camera_Set();
				glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
				//*glBegin(GL_LINES);
				glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
				glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].ScanVecTo.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].ScanVecTo.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].ScanVecTo.z * 250));
				//*glEnd();
#endif
#if 0
				if(ScanDistL < ScanDistR) Q_Forge->Forge[helly].ScanTurnAng *= -1;

				Q_Forge->Forge[helly].trueAngles.y = Q_Forge->Forge[helly].ScanTurnAng;

				Q_Forge->Forge[helly].Angles.y = Q_Forge->Forge[helly].ScanTurnAng;
				if(Q_Forge->Forge[helly].Angles.y > (PI*2)) Q_Forge->Forge[helly].Angles.y = 0;
				if(Q_Forge->Forge[helly].Angles.y < 0) Q_Forge->Forge[helly].Angles.y = (PI*2);

				Q_Forge->Forge[helly].STOREAngles.y = Q_Forge->Forge[helly].ScanTurnAng;

				//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[helly].ScanTurnAng);
				//Qpo->Transform_Multiply(&Q_Forge->Forge[helly].AV.Xform, &AIfriendly, &Q_Forge->Forge[helly].AV.Xform);

				//Q_Forge->Forge[helly].Xform.Matrix.load_identity();
				Q_Forge->Forge[helly].Xform.Translation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].Xform.Translation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].Xform.Translation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;
				Q_Forge->Forge[helly].Xform.GhostTranslation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].Xform.GhostTranslation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].Xform.GhostTranslation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;

				//Q_Forge->Forge[helly].AV.Xform.Matrix.load_identity();
				Q_Forge->Forge[helly].AV.Xform.Translation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].AV.Xform.Translation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].AV.Xform.Translation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;
				Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;
#endif
#endif

				//### Load Player Weapon
				Q_Forge->Forge[helly].Weapon.Avatar = 1;

				Q_Forge->Forge[helly].Weapon.Scale.x = 1;
				Q_Forge->Forge[helly].Weapon.Scale.y = 1;
				Q_Forge->Forge[helly].Weapon.Scale.z = 1;

				Q_Forge->Forge[helly].Weapon.Mins.x = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.y = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.z = -20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.x = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.y = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.z = 20.f;

				Q_Forge->Forge[helly].Weapon.Mins.x = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.y = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.z = -20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.x = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.y = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.z = 20.f;

				Q_Forge->Forge[helly].Weapon.Visible = true;

				Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[helly].Weapon.Xform.Translation);

				Qpo->Mesh_SetAlpha(&Q_Forge->Forge[helly].Weapon, 0);

				Q_Forge->Forge[helly].WeaponDISPLAY = 0;

				if(Q_Forge->Forge[helly].CharDATA.Class == 2)
					{
					Q_Forge->Forge[helly].Shield.Mins.x = -500.f;
					Q_Forge->Forge[helly].Shield.Mins.y = -500.f;
					Q_Forge->Forge[helly].Shield.Mins.z = -500.f;
					Q_Forge->Forge[helly].Shield.Maxs.x = 500.f;
					Q_Forge->Forge[helly].Shield.Maxs.y = 500.f;
					Q_Forge->Forge[helly].Shield.Maxs.z = 500.f;

					Qpo->Avatar_SetAlpha(&Q_Forge->Forge[helly].Shield.Avatar, 40);

					fogbox.Min.x = Q_Forge->Forge[helly].Shield.Mins.x;
					fogbox.Min.y = Q_Forge->Forge[helly].Shield.Mins.y;
					fogbox.Min.z = Q_Forge->Forge[helly].Shield.Mins.z;
					fogbox.Max.x = Q_Forge->Forge[helly].Shield.Maxs.x;
					fogbox.Max.y = Q_Forge->Forge[helly].Shield.Maxs.y;
					fogbox.Max.z = Q_Forge->Forge[helly].Shield.Maxs.z;

					Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[helly].Shield.Xform.Translation);

					Q_Forge->Forge[helly].Shield.Avatar.IDflag = 251;
					}

				//### Load Fighter Shadows

				Q_Forge->Forge[helly].ShadowsOn = false;
				Q_Forge->Forge[helly].ShadowALPHA = 240;

				if(player[g_Player]->WeaponStatus == 0) player[g_Player]->CamMatrix.Translation.y = Q_Forge->Forge[helly].Xform.Translation.y + 20 + 25;
				else player[g_Player]->CamMatrix.Translation.y = Q_Forge->Forge[helly].Xform.Translation.y + 20 + 25 + 30;

#ifdef USE_CAPSULES
				player[g_Player]->CamMatrix.Translation.y *= Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2));

				PxMat33 f_GlobalPose;
				f_GlobalPose.createIdentity();
				PxMat33 f_LocalPose;
				f_LocalPose.createIdentity();

				g_ForgeBox[helly] = DigiMass->acCreateBox(physx::PxVec3(0, 0, 0), 50 * Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), 20 * Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), 50, helly);
#endif

				aero = 0;
				while(aero <= 2)
					{
					aero++;

					if(Q_Forge->Forge[helly].CharDATA.ShadowREF > 11 || Q_Forge->Forge[helly].CharDATA.ShadowREF < 0) Q_Forge->Forge[helly].CharDATA.ShadowREF = 0;

					//Q_Forge->Forge[helly].Shadows[aero].Avatar.Mesh = new unAvatar();
					//meshShellTemplates[Q_Forge->Forge[helly].CharDATA.ShadowREF]->clone_struct(Q_Forge->Forge[helly].Shadows[aero].Avatar.Mesh);

					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.x = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.y = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.z = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Matrix.load_identity();

					//##### Starting position
					Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
					Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
					if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
					Ange.x=-(PI/2);
					Ange.z=0;

					// Set the actor's angle
					Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.x);
					Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.y);
					Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.z);

					Q_Forge->Forge[helly].Shadows[aero].Mins.x = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Mins.y = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Mins.z = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.x = 20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.y = 20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.z = 20.f;

#if 0
					QpoActor_SetScale(Q_Forge->Forge[helly].Shadows[aero].Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

					Q_Forge->Forge[helly].Shadows[aero].Avatar.Visible = true;

					Qpo->Avatar_SetAlpha(&Q_Forge->Forge[helly].Shadows[aero].Avatar, 255/(aero+1));

					Q_Forge->Forge[helly].Shadows[aero].Avatar.IDflag = helly;
					}

				//#### Set Up Trail Flags
				Q_Forge->Forge[helly].TrailFadeSpan[0][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[1][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[2][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[3][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[4][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[5][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[6][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[7][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[8][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[9][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[0][1] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[1][1] = 1;
				Q_Forge->Forge[helly].TrailFadeSpan[2][1] = 2;
				Q_Forge->Forge[helly].TrailFadeSpan[3][1] = 3;
				Q_Forge->Forge[helly].TrailFadeSpan[4][1] = 4;
				Q_Forge->Forge[helly].TrailFadeSpan[5][1] = 5;
				Q_Forge->Forge[helly].TrailFadeSpan[6][1] = 6;
				Q_Forge->Forge[helly].TrailFadeSpan[7][1] = 7;
				Q_Forge->Forge[helly].TrailFadeSpan[8][1] = 8;
				Q_Forge->Forge[helly].TrailFadeSpan[9][1] = 9;

#ifndef QAGEMODE_NOINTRO
				acNamePlateUpdate();
#endif

				//####### ACTIVATE ITEM ATTRIBUTES
				Q.ActivateItemsAI(helly);

#if 0
				//#### RESET SCALE AND LIGHTING
				QpoActor_SetScale(Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

#ifndef QAGEMODE_NOINTRO
				acNamePlateUpdate();
#endif

#if 1
				Q_Forge->Forge[helly].Q_Brain.MindState = MIND_ACTIVEINIT;
#endif

				Q_Forge->Forge[helly].LIVE = 1;
				}

			helly++;
			}
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//Teams!
	helly = 0;
	while(helly < _->NomAI)
		{
		if(Q_Forge->Forge[helly].LIVE == 1 && Q_Forge->Forge[helly].Team == 0) Q_Forge->Forge[helly].Team = player[g_Player]->Team;

		helly++;
		}
#endif

//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA

#if 0
	bool f_STR_Map = false;

	if(g_optionsresult == 3)
		{
		if(!player[g_Player]->BFO.GamePAUSE) f_STR_Map = true;
		}
	else f_STR_Map = true;

	if(!g_render) exit(-1);

	if(f_STR_Map)
		{
		for(i = 0; i < g_render->model.num; i++)
			//g_render->model.buf[i]->reset();

		//_->mesh->reset();
		//delete _->mesh;

		if(g_optionsresult == 3)
			{
			printf("GameMap:::AMATCH::: Starting ID %i\n", player[g_Player]->BFO.GameMap);
			}
		else printf("GameMap:::S_Player Starting ID %i\n", player[g_Player]->BFO.GameMap);

#if 1
		switch(player[g_Player]->BFO.GameMap)
			{
			case 2:
				//_->mesh	= g_render->load_mesh(meshfile1, 8.0f);
				break;
			case 0:
				//_->mesh	= g_render->load_mesh(meshfile2, 8.0f);
				break;
			case 5:
				//_->mesh	= g_render->load_mesh(meshfile3, 8.0f);
				break;
			case 4:
				//_->mesh	= g_render->load_mesh(meshfile4, 8.0f);
				break;
			case 3:
				//_->mesh	= g_render->load_mesh(meshfile5, 8.0f);
				break;
			case 1:
				//_->mesh	= g_render->load_mesh(meshfile6, 8.0f);
				break;
			}
#else
		_->mesh	= g_render->load_mesh(meshfile3, 8.0f);
#endif
	

		for(int f_gap = 0; f_gap < _->mesh->ncam; f_gap++)
			{
			//_->mesh->cam[f_gap].pos.y += 705;
			}

#if 1
		if(g_optionsresult == 3)
			{
			printf("GameMap:::AMATCH::: BEGIN Piping into DigiMass for Physics\n");
			}
		else printf("GameMap:::BEGIN Piping into DigiMass for Physics\n");

		//*QActiveFrameWork->DigiMass->acMeshPipe(_->mesh);

		if(g_optionsresult == 3)
			{
			printf("GameMap:::AMATCH::: SUCCESS Finished Piping Physics.\n");
			}
		else printf("GameMap:::S_Player SUCCESS Finished Piping Physics.\n");
#endif

		//g_romanager->m_active_root.add((pRenderObject*)_->mesh);

		g_startcommand = 2;
		}
#endif

	return true;
}

void QActiveFramewrk::acRecieveInit(void)
{
#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	

#if 1
	/////// Prepare Character Data ///////
	Q.StartCharacterData();
#else
	/////// Load Character Data ///////
	Q.LoadCharacterData();
#endif

#if 0
	////// Reset Character Data to Factory Defaults //////
	Q.ResetCharacterData();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	
	_->screenx = 800;
    _->screeny = 600;
	mpos.x = _->screenx/2;
	mpos.y = _->screeny/2;

	_->Origin.x = 0;
	_->Origin.y = 0;
	_->Origin.z = 0;

	_->GenericLightPos.x = 0;
	_->GenericLightPos.y = -250;
	_->GenericLightPos.z = 0;

	player[g_Player]->QformChk = false;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	
		//Seed the random generator with the time
#if defined(WIN32)
	//srand( (unsigned)getElapsedTime() );
	time_t f_time;
	time(&f_time);
	srand(f_time);
#else
	srand( (unsigned)time(NULL) );
#endif

	//### LOAD INTRO

	//_->GameTypeSelect = 1;
	
	//player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON = 42;

	LOADED_FACTORY[4] = 0;
	LOADED_FACTORY[5] = 0;
	LOADED_FACTORY[6] = 0;
	LOADED_FACTORY[7] = 0;
	LOADED_FACTORY[8] = 0;
	LOADED_FACTORY[9] = 0;
	LOADED_FACTORY[10] = 0;
	LOADED_FACTORY[11] = 0;
	LOADED_FACTORY[12] = 0;
	LOADED_FACTORY[13] = 0;
	LOADED_FACTORY[14] = 0;
	
// Define Bone Names / Numbers *****************************************************************************
//**********************************************************************************************************
								//OPTIMISE  Remove bones not needed
	BoneDef[0] = "BIP01 HEAD";
	BoneDef[1] = "BIP01 L CALF";
	BoneDef[2] = "BIP01 L CLAVICLE";
	BoneDef[3] = "BIP01 L FOOT";
	BoneDef[4] = "BIP01 L FOREARM";
	BoneDef[5] = "BIP01 L HAND";
	BoneDef[6] = "BIP01 L THIGH";
	BoneDef[7] = "BIP01 L UPPERARM";
	BoneDef[8] = "BIP01 NECK";
	BoneDef[9] = "BIP01 PELVIS";
	BoneDef[10] = "BIP01 R CALF";
	BoneDef[11] = "BIP01 R CLAVICLE";
	BoneDef[12] = "BIP01 R FOOT";
	BoneDef[13] = "BIP01 R FOREARM";
	BoneDef[14] = "BIP01 R HAND";
	BoneDef[15] = "BIP01 R THIGH";
	BoneDef[16] = "BIP01 R UPPERARM";
	BoneDef[17] = "BIP01 SPINE";
	BoneDef[18] = "BIP01 SPINE1";
	BoneDef[19] = "BIP01 SPINE2";
	//BoneDef[20] = "BIP01 SPINE3";
	BoneDef[20] = "BIP01 SPINE2";
	
	Q.StructureAInitialize();
	
	qBoneNum[0] = 8;			//THIS NEEDS CHECKING <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	qBoneNum[1] = 48;
	qBoneNum[2] = 9;
	qBoneNum[3] = 49;
	qBoneNum[4] = 11;
	qBoneNum[5] = 12;
	qBoneNum[6] = 47;
	qBoneNum[7] = 10;
	qBoneNum[8] = 7;
	qBoneNum[9] = 2;		//<-May be 1 or 0
	qBoneNum[10] = 52;
	qBoneNum[11] = 28;
	qBoneNum[12] = 53;
	qBoneNum[13] = 30;
	qBoneNum[14] = 31;
	qBoneNum[15] = 51;
	qBoneNum[16] = 29;
	qBoneNum[17] = 3;
	qBoneNum[18] = 4;
	qBoneNum[19] = 5;
	//qBoneNum[20] = 6;
	qBoneNum[20] = 5;

// Define Angel Edit Pointer *******************************************************************************
//**********************************************************************************************************
	
	sprintf(Q_ANGELeditMAP->ANGELeditMAP[0].MAPNAME, "Hair");
	Q_ANGELeditMAP->ANGELeditMAP[0].MAPPOINTER = 3;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[1].MAPNAME, "Shoulders");
	Q_ANGELeditMAP->ANGELeditMAP[1].MAPPOINTER = 30;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[2].MAPNAME, "Face");
	Q_ANGELeditMAP->ANGELeditMAP[2].MAPPOINTER = 4;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[3].MAPNAME, "Left Ear");
	Q_ANGELeditMAP->ANGELeditMAP[3].MAPPOINTER = 5;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[4].MAPNAME, "Right Ear");
	Q_ANGELeditMAP->ANGELeditMAP[4].MAPPOINTER = 0;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[5].MAPNAME, "Nose");
	Q_ANGELeditMAP->ANGELeditMAP[5].MAPPOINTER = 10;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[6].MAPNAME, "Mouth");
	Q_ANGELeditMAP->ANGELeditMAP[6].MAPPOINTER = 11;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[7].MAPNAME, "Left Eye Socket");
	Q_ANGELeditMAP->ANGELeditMAP[7].MAPPOINTER = 7;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[8].MAPNAME, "Left Eye");
	Q_ANGELeditMAP->ANGELeditMAP[8].MAPPOINTER = 6;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[9].MAPNAME, "Right Eye Socket");
	Q_ANGELeditMAP->ANGELeditMAP[9].MAPPOINTER = 9;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[10].MAPNAME, "Right Eye");
	Q_ANGELeditMAP->ANGELeditMAP[10].MAPPOINTER = 8;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[11].MAPNAME, "Neck");
	Q_ANGELeditMAP->ANGELeditMAP[11].MAPPOINTER = 12;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[12].MAPNAME, "Left Hand");
	Q_ANGELeditMAP->ANGELeditMAP[12].MAPPOINTER = 15;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[13].MAPNAME, "Butt Skin");
	Q_ANGELeditMAP->ANGELeditMAP[13].MAPPOINTER = 33;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[14].MAPNAME, "BackPack");
	Q_ANGELeditMAP->ANGELeditMAP[14].MAPPOINTER = 25;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[15].MAPNAME, "Boot Tongues");
	Q_ANGELeditMAP->ANGELeditMAP[15].MAPPOINTER = 26;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[16].MAPNAME, "Boot Soles");
	Q_ANGELeditMAP->ANGELeditMAP[16].MAPPOINTER = 27;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[17].MAPNAME, "Left Arm");
	Q_ANGELeditMAP->ANGELeditMAP[17].MAPPOINTER = 13;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[18].MAPNAME, "Right Hand");
	Q_ANGELeditMAP->ANGELeditMAP[18].MAPPOINTER = 17;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[19].MAPNAME, "Left Forearm");
	Q_ANGELeditMAP->ANGELeditMAP[19].MAPPOINTER = 14;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[20].MAPNAME, "Right Forearm");
	Q_ANGELeditMAP->ANGELeditMAP[20].MAPPOINTER = 1;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[21].MAPNAME, "Right Arm");
	Q_ANGELeditMAP->ANGELeditMAP[21].MAPPOINTER = 16;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[22].MAPNAME, "Left Boot");
	Q_ANGELeditMAP->ANGELeditMAP[22].MAPPOINTER = 19;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[23].MAPNAME, "Left Calf");
	Q_ANGELeditMAP->ANGELeditMAP[23].MAPPOINTER = 18;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[24].MAPNAME, "Left Thigh Band");
	Q_ANGELeditMAP->ANGELeditMAP[24].MAPPOINTER = 32;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[25].MAPNAME, "Collar");
	Q_ANGELeditMAP->ANGELeditMAP[25].MAPPOINTER = 34;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[26].MAPNAME, "Chest");
	Q_ANGELeditMAP->ANGELeditMAP[26].MAPPOINTER = 23;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[27].MAPNAME, "Stomach");
	Q_ANGELeditMAP->ANGELeditMAP[27].MAPPOINTER = 24;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[28].MAPNAME, "Right Boot");
	Q_ANGELeditMAP->ANGELeditMAP[28].MAPPOINTER = 20;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[29].MAPNAME, "Right Calf");
	Q_ANGELeditMAP->ANGELeditMAP[29].MAPPOINTER = 2;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[30].MAPNAME, "Left Thigh");
	Q_ANGELeditMAP->ANGELeditMAP[30].MAPPOINTER = 21;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[31].MAPNAME, "Right Thigh");
	Q_ANGELeditMAP->ANGELeditMAP[31].MAPPOINTER = 22;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[32].MAPNAME, "Head Aerials");
	Q_ANGELeditMAP->ANGELeditMAP[32].MAPPOINTER = 28;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[33].MAPNAME, "Right Thigh Band");
	Q_ANGELeditMAP->ANGELeditMAP[33].MAPPOINTER = 31;

	sprintf(Q_ANGELeditMAP->ANGELeditMAP[34].MAPNAME, "Boot Front");
	Q_ANGELeditMAP->ANGELeditMAP[34].MAPPOINTER = 29;

#if 0
	15
	18
	32
#endif

// Trail Fade Vars *****************************************************************************************
//**********************************************************************************************************

	player[g_Player]->TrailFadeSpan[0][0] = 0;
	player[g_Player]->TrailFadeSpan[1][0] = 0;
	player[g_Player]->TrailFadeSpan[2][0] = 0;
	player[g_Player]->TrailFadeSpan[3][0] = 0;
	player[g_Player]->TrailFadeSpan[4][0] = 0;
	player[g_Player]->TrailFadeSpan[5][0] = 0;
	player[g_Player]->TrailFadeSpan[6][0] = 0;
	player[g_Player]->TrailFadeSpan[7][0] = 0;
	player[g_Player]->TrailFadeSpan[8][0] = 0;
	player[g_Player]->TrailFadeSpan[9][0] = 0;
	player[g_Player]->TrailFadeSpan[0][1] = 0;
	player[g_Player]->TrailFadeSpan[1][1] = 1;
	player[g_Player]->TrailFadeSpan[2][1] = 2;
	player[g_Player]->TrailFadeSpan[3][1] = 3;
	player[g_Player]->TrailFadeSpan[4][1] = 4;
	player[g_Player]->TrailFadeSpan[5][1] = 5;
	player[g_Player]->TrailFadeSpan[6][1] = 6;
	player[g_Player]->TrailFadeSpan[7][1] = 7;
	player[g_Player]->TrailFadeSpan[8][1] = 8;
	player[g_Player]->TrailFadeSpan[9][1] = 9;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

// Bitmap init *********************************************************************************************
//**********************************************************************************************************

	//#### TEXTURE SETUP

#ifndef QAGEMODE_NOEFFECTS
#if 1
	Q.InitTextures();
#endif
#endif

#if 0
	Q.BlatTextures();
#endif

	//#### SOUND SETUP
#if 1
	Q.InitSounds();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//while(true) { printf("unTrace\n"); };

//**********************************************************************************************************
//**********************************************************************************************************

	Qpo->Transform_New_XRotation(&Xrot90deg, -(PI/2));

// Setup World / Load entities *****************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

	//### Load Player Start Point
	//### TODO Create Level Far clip distance Entity ###
	VisClipDist	= 2000;
	
#pragma message ("SET - _->NomAI, CURRCHAR, _->NetworkOption")
#pragma message ("FIXME: Fake Library Data")

	player[g_Player]->BFO.GAMEOPTIONS.FrameratelimiterON = 1;
#if 0
	_->FRL_LIMIT = 55;
#endif

#if 1
	_->FRL_LIMIT = 100;
#endif

//**********************************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

// Setup the player ########################################################################################
//##########################################################################################################
//##########################################################################################################

	#pragma message ("Lighting Table")
	
	// Setup the player specific flags
	player[g_Player]->PlayerHeight = PLAYER_HEIGHT;
	player[g_Player]->PlayerSpeed = PLAYER_SPEED;
	player[g_Player]->ForwardSpeed = 0;
	player[g_Player]->upspeed = -15;
	player[g_Player]->camrotdist = 1000;
	player[g_Player]->GravityAlter = 1;
	player[g_Player]->AirJinkPrep = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 0
	Q.WriteMeMPathways();
#endif

#if 0
	Q.ReadMeMPathways();
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif
	
	g_startcommand = 0;

#ifdef QAMOD_ARENA
#if 1
	g_optionsresult = Q.ShowCharacterDialog();
#else
	g_optionsresult = 1;
	player[g_Player]->BFO.GameTypeSelect = 1;
#endif
#endif

#if 0
#ifdef QAMOD_ARENA
		//###- QUIT -###//
	//if(g_optionsresult < 1)
	//	{
		//render_free();
		//PostQuitMessage(0);
		//g_QUITM = true;
	//	}
	//else
	if(1)
		{
			//###- SINGLE PLAYER -###//
		if(g_optionsresult == 1)
			{
			if(player[g_Player]->BFO.GameTypeSelect == 1)
				{
				_->NomAI = 0;
				_->NetworkOption = 0;
				}
			else
				{
				if(player[g_Player]->BFO.GameTypeSelect == 0)
					{
					_->NomAI = player[g_Player]->BFO.NomAvatars;
					_->NetworkOption = 0;
					}
				}
			}
		else
			{
				//###- SPECTATING -###//
			if(g_optionsresult == 2)
				{
				if(player[g_Player]->BFO.GameTypeSelect == 1)
					{
					_->NomAI = 0;
					_->NetworkOption = 0;
					}
				else
					{
					if(player[g_Player]->BFO.GameTypeSelect == 0)
						{
						_->NomAI = player[g_Player]->BFO.NomAvatars;
						_->NetworkOption = 0;
						}
					}
				}
			else
				{
					//###- BEST_FIT MATCH-MAKING -###//
				if(g_optionsresult == 3)
					{
					if(player[g_Player]->BFO.GameTypeSelect == 1)
						{
						_->NomAI = 0;
						//player[g_Player]->BFO.CurrCHAR = 0;
						_->NetworkOption = 0;
						}
					else
						{
						if(player[g_Player]->BFO.GameTypeSelect == 0)
							{
							_->NomAI = player[g_Player]->BFO.NomAvatars;
							_->NetworkOption = 0;

							//*unsStringCompressor::AddReference();
							printf("Connecting to OSI Staging Server\n");

							//----- Connect to 'Unification QAGE Server'
							int i_clientPort = 10000;	//60007 10000
							Q_PlacementMarker->m_Count += 15;
							i_clientPort += Q_PlacementMarker->m_Count;

							printf("client port %i/n", i_clientPort);

							//*SocketDescriptor socketDescriptor(i_clientPort,0);

#if 1
							//*clientAddress.SetBinaryAddress("192.168.1.102");
#else
							clientAddress.SetBinaryAddress("localhost");
#endif

							//*clientAddress.port = i_clientPort;

							//*unPeer->Startup(1, 30, &socketDescriptor, 1);
							//*unPeer->SetOccasionalPing(true);

							bool Success = false;

#if 0
#if 0
							Success = unPeer->Connect("87.106.104.248", 10555, 0, 0);
#else
							Success = unPeer->Connect("localhost", 10358, "fractal18", (int) strlen("fractal18"));
#endif
#else
							//*Success = unPeer->Connect("82.165.16.114", 1843, "", 0);
#endif

							if(Success) printf("Connected to OSI Staging Server\n");
							else
								{
								printf("ERROR: Cannot connect to server\n");
								}

#if 0
#if 1
							serveAddress.SetBinaryAddress("87.106.104.248");
							printf("serveAddress.SetBinaryAddress 87.106.104.248\n");
#else
							serveAddress.SetBinaryAddress("localhost");
							printf("serveAddress.SetBinaryAddress = 'localhost'\n");
#endif
#else
							//*serveAddress.SetBinaryAddress("82.165.16.114");
							printf("serveAddress.SetBinaryAddress 82.16.165.114\n");
#endif

							//*serveAddress.port = 1843;

							///// Set the internal packet pump state
							if(m_PP_STATE == 0)
								{
								m_PP_STATE = 1;

								//m_mutex_unPeer = SDL_CreateMutex();
								//m_mutex_Packet = SDL_CreateMutex();
								//m_mutex_Request = SDL_CreateMutex();
								//m_mutex_State = SDL_CreateMutex();

								vec_Packet = new PacketVectorSwing();
#if 0
								//*m_PacketSocket.m_unPeer = unPeer;
								m_PacketSocket.m_vec_Packet = vec_Packet;
								m_PacketSocket.m_mutex_unPeer = m_mutex_unPeer;
								m_PacketSocket.m_mutex_Packet = m_mutex_Packet;
								m_PacketSocket.Start();

								//*m_PacketPump.m_unPeer = unPeer;
								m_PacketPump.m_vec_Packet = vec_Packet;
								m_PacketPump.m_mutex_unPeer = m_mutex_unPeer;
								m_PacketPump.m_mutex_Packet = m_mutex_Packet;
								m_PacketPump.m_mutex_State = m_mutex_State;
								m_PacketPump.m_QActiveFramework = this;
								QNetwork.m_QActiveFramework = this;
								//*m_PacketPump.serveAddress = serveAddress;
								//*m_PacketPump.clientAddress = clientAddress;
								m_PacketPump.Start();

								//*m_PacketStack.m_unPeer = unPeer;
								m_PacketStack.m_mutex_unPeer = m_mutex_unPeer;
								m_PacketStack.m_mutex_Request = m_mutex_Request;
								m_PacketStack.m_UNSResRequest = &m_UNSResRequest;
								m_PacketStack.m_DocumentBank = m_DocumentBank;
								m_PacketStack.m_map_Documents = &m_map_Documents;
								//*m_PacketStack.serveAddress = serveAddress;
								//*m_PacketStack.clientAddress = clientAddress;
								m_PacketStack.Start();
#endif
								m_NetStart = true;
								}

							// Set the Packet Pump MODE
							m_PacketPump.m_PP_MODE = 1;
							}

						player[g_Player]->BFO.GamePAUSE = true;

						while(player[g_Player]->BFO.GamePAUSE)
							{
							//Pause
							}
						}
					}
				}
			}
		}
#endif
#else
	_->NomAI = 0;
	player[g_Player]->BFO.CurrCHAR = 0;
	_->NetworkOption = 0;
#endif

	for(int i = 0; i < _->NomAI; i++)
		{
		player[g_Player]->BFO.AVATARDATA[i].LIVE = 1;
		}

	//#### ENERGY MATRIX SETUP

	Q_EnergyMatrix->EnergyMatrix.GlobalSCALE = 100;

	player[g_Player]->EnergyArchitect.ExpandSTRENGTH = 1.15;
	TestfloatALPHA1 = 7.149;
	TestfloatALPHA2 = 1.15;

	_->WorldScale = 1;

	player[g_Player]->Invisible = 0;

	player[g_Player]->Team = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].TEAM;

	//Player Level
	player[g_Player]->LEVEL = 1;

	//Fill Weapon Ammo
	player[g_Player]->WeaponAmmo = 32;

	player[g_Player]->Mins.x = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	player[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    player[g_Player]->Mins.z = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.x = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    player[g_Player]->Maxs.z = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->upspeed = 0;

	playerAV[g_Player]->Mins.x = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
    playerAV[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    playerAV[g_Player]->Mins.z = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.x = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.z = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//ACTOR SETUP AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);

	player[g_Player]->HB_Armour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	player[g_Player]->HB_MaxArmour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	player[g_Player]->HB_MaxHealth = 1000 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/100)*0.6)+0.4);
	player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;

	//player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

	player[g_Player]->HB_Dead = 0;

	player[g_Player]->JINK3_PowerFactor = 1;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//m_unSegment = new managed_shared_memory(open_only, "UnificationSPC");
#if 0
#if 1
	unShellMesh *f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/LisaShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	f_mesh->acMake();

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);
#endif

#ifndef QAGE_OPMOD_B

	f_mesh = new unShellMesh();

	if(!f_mesh->acCreate("Assets/Avatar/MellodiShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

	if(!f_mesh->acCreate("Assets/Avatar/AssassinShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtAlterShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtBikiniShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/TemplateShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/250TemplateShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);


	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/250TemplateClothesShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/SoldierNewShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/CommanderShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);

	f_mesh = new unShellMesh();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	if(!f_mesh->acCreate("Assets/Avatar/ShortSkirtGlovesShell.cfg"))
		{
		std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshShellTemplates[0]->acTransferAnim(f_mesh);

	if(!f_mesh->acInit())
		{
		std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshShellTemplates.push_back(f_mesh);
#endif

#if 0
	digiShellMesh* f_digimesh = new digiShellMesh();

	if(!f_digimesh->acCreate("Assets/Avatar/ShortSkirtGlovesShell.cfg"))
		{
		std::cerr << "ERROR::: unBodyMesh ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	f_digimesh->acMake();

	if(!f_digimesh->acInit(0))
		{
		std::cerr << "ERROR::: unBodyMesh ::: Initialization failed." << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	meshdigiShellTemplates.push_back(f_digimesh);
#endif
#endif

#if 1
	unMeshStatic *f_MeshStatic = new unMeshStatic();

	if(!f_MeshStatic->onCreate("Assets/Mesh/Energy/Renzou.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_MeshStatic);
#endif

#if 1	// Swat552X
	unMeshStatic *f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/Swat552X.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// famassvX
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/famassvX.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// IncaMKII
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/IncaMKII.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// MiniGun
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/MiniGun1.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// M4A1actr
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/M4A1actr.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// Swat552X
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/Swat552X.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// MiniGun
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/ak47lowq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// psg1lowq
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/psg1lowq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// spas12lq
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/spas12lq.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// g3lowqua
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/g3lowqua.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// l96a1low
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/l96a1low.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 1	// w_awp10
	f_WeaponMesh = new unMeshStatic();

	if(!f_WeaponMesh->onCreate("Assets/Mesh/Weapon/w_awp10.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshstaticTemplates.push_back(f_WeaponMesh);
#endif

#if 0
#if 1
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/FordGT40.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif
#endif

#if 0
	unMeshStatic *f_VehicleMesh = new unMeshStatic();

	if(!f_VehicleMesh->onCreate("Assets/Mesh/Vehicle/Ducati.cfg"))
		{
		std::cerr << "ERROR::: unMeshStatic ::: Failed to load" << std::endl;
		while(1) { /* Infinite Loop */ }// return -1;
		}

	meshVehicleTemplates.push_back(f_VehicleMesh);
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//#### RENZOU
	aero=0;
	while(aero < 150)
		{
		helly=0;
		while(helly < 5)
			{
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Avatar = 0;

			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.x = 1;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.y = 1;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Scale.z = 1;

			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.x = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.y = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Mins.z = -20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.x = 20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.y = 20.f;
			Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Maxs.z = 20.f;

			//Qpo->Avatar_SetScale(&Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Avatar, 4, 4, 4);

			Qpo->Vec3d_Copy(&_->Origin, &Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Xform.Translation);

#if 0
#ifndef QAGEMODE_NOINTRO
			acNamePlateUpdate();
#endif
#endif
			helly++;
			}

#if 0
		Q_SEnergy->SEnergy[aero].Const_TurnDull = 2500;
#endif

		Q_SEnergy->SEnergy[aero].Const_TurnDull = 50000;

#if 0
		Q_SEnergy->SEnergy[aero].Const_AngleInc = 0.2;
#endif

		Q_SEnergy->SEnergy[aero].Const_AngleInc = 1;

#if 0
#ifndef QAGEMODE_NOINTRO
		acNamePlateUpdate();
#endif
#endif

		_->MaxNomSEnergy++;

		aero++;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	aero=0;
	while(aero < 25)	//aero < (_->NomAI) <--- History
		{
		Q_LEnergy->LEnergy[aero].Live = 0;

		Q_LEnergy->LEnergy[aero].EnergyBall.Avatar = 0;

		Q_LEnergy->LEnergy[aero].EnergyBall.Mins.x = -20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Mins.y = -20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Mins.z = -20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.x = 20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.y = 20.f;
		Q_LEnergy->LEnergy[aero].EnergyBall.Maxs.z = 20.f;

#if 1
		Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[aero].EnergyBall, 40, 40, 40);
		Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[aero].EnergyBall, 0);
#endif

		Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation);

#if 0
#ifndef QAGEMODE_NOINTRO
		acNamePlateUpdate();
#endif
#endif

		_->MaxNomLEnergy++;
		aero++;
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#pragma message ("FIXME:::Start Player Start Position and initial pose")

	playerAV[g_Player]->Avatar.Mesh = new unAvatar();

	int f_PlayerID = 0;
	player[g_Player]->BFO.BDATID = f_PlayerID;

#if 0
	printf("AggPower %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower);
	printf("DefPower %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower );
	printf("Constitution %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution );
	printf("Dexterity %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity );
	printf("EnergyEff %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff );
	printf("Height %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height );
	printf("PhysicalStr %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr );
	printf("Weight %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight );
	printf("LeftArmSNAP %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP );
	printf("LeftArmSTRENGTH %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH );
	printf("LeftLegSNAP %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP );
	printf("LeftLegSTRENGTH %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH );
	printf("RightArmSNAP %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP );
	printf("RightArmSTRENGTH %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH );
	printf("RightLegSNAP %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP );
	printf("RightLegSTRENGTH %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH );

	printf("JINKINCpower %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower );
	printf("JINKINC3intensity %f\n", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity );

	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class = 0;
#endif

#if 1
	//if(AVATAR_PHYSICS_ENABLE) meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, f_PlayerID);
	//else meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarREF]->clone_struct(playerAV[g_Player]->Avatar.Mesh);
#else
	if(AVATAR_PHYSICS_ENABLE) meshdigiShellTemplates[f_PlayerID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, f_PlayerID);
	else meshdigiShellTemplates[f_PlayerID]->clone_struct(playerAV[g_Player]->Avatar.Mesh);
#endif

#if defined(ENABLE_NX_PHYSICS)
#if 0
	playerAV[g_Player]->Avatar.Mesh->addClothAttachment(meshShellTemplates[0]->m_Cloth[0], 0, 0, 0);
#endif
#endif

	playerAV[g_Player]->Xform.Translation.x = 0;
	playerAV[g_Player]->Xform.Translation.y = 350;
	playerAV[g_Player]->Xform.Translation.z = 0;

	playerAV[g_Player]->Xform.Matrix.load_identity();

	player[g_Player]->HB_DeadTimerC = 1500;

	playerAV[g_Player]->CollisionCount = 0;

	//##### Starting position
	Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
	Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); 
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, Ange.x);
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, Ange.y);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Ange.z);

	player[g_Player]->STOREMatrix = playerAV[g_Player]->Xform;

	//#### RESET SPELLS
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[3].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[4].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[5].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[6].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[7].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[8].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[9].LIVE = 0;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

#if 1
									//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
	Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	#pragma message ("Add Actor SCALE")

	// Set the actor to its position
	Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[player[g_Player]->Team].Pos, &playerAV[g_Player]->Xform.Translation);

	player[g_Player]->Angles.x = -1.05;
	player[g_Player]->Angles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	player[g_Player]->trueAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	//player[g_Player]->STOREAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;

	fogbox.Min.x = playerAV[g_Player]->Mins.x;
	fogbox.Min.y = playerAV[g_Player]->Mins.y;
	fogbox.Min.z = playerAV[g_Player]->Mins.z;
	fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	fogbox.Max.z = playerAV[g_Player]->Maxs.z;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	player[g_Player]->idlespeed = 0.1;

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->STOREMatrix.Translation);

	playerAV[g_Player]->Avatar.IDflag = 250;

	player[g_Player]->AttackSoundTRIG = 0;

	//### Load Player Weapon
	player[g_Player]->Weapon.Avatar = 1;

	player[g_Player]->Weapon.Scale.x = 1;
	player[g_Player]->Weapon.Scale.y = 1;
	player[g_Player]->Weapon.Scale.z = 1;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	#pragma message ("Add Weapon SCALE")
#if 0
	Qpo->Avatar_SetScale(&player[g_Player]->Weapon.Avatar, 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Weapon.Xform.Translation);

	player[g_Player]->WeaponDISPLAY = 0;

	player[g_Player]->QformONtaunt = 1;

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
		{
		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shield.Xform.Translation);

		player[g_Player]->Shield.Mins.x = -500.f;
		player[g_Player]->Shield.Mins.y = -500.f;
		player[g_Player]->Shield.Mins.z = -500.f;
		player[g_Player]->Shield.Maxs.x = 500.f;
		player[g_Player]->Shield.Maxs.y = 500.f;
		player[g_Player]->Shield.Maxs.z = 500.f;

		fogbox.Min.x = player[g_Player]->Shield.Mins.x;
		fogbox.Min.y = player[g_Player]->Shield.Mins.y;
		fogbox.Min.z = player[g_Player]->Shield.Mins.z;
		fogbox.Max.x = player[g_Player]->Shield.Maxs.x;
		fogbox.Max.y = player[g_Player]->Shield.Maxs.y;
		fogbox.Max.z = player[g_Player]->Shield.Maxs.z;

#if 0
		QpoActor_SetScale(player[g_Player]->Shield.Avatar, 0.65f,0.65f,0.65f);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shield.Avatar, 150);
#endif

		player[g_Player]->Shield.Avatar.IDflag = 251;
		}

	//### Load Player Shadows
	helly = 0;
	while(helly <= 2)
		{
		helly++;

		player[g_Player]->Shadows[helly].Avatar.Mesh = new unAvatar();
		//meshShellTemplates[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ShadowREF]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);

		player[g_Player]->Shadows[helly].Xform.Translation.x = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.y = 0;
		player[g_Player]->Shadows[helly].Xform.Translation.z = 0;
		player[g_Player]->Shadows[helly].Xform.Matrix.load_identity();

		//##### Starting position
		Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
		Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
		if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
		Ange.x=-(PI/2);
		Ange.z=0;

		// Set the actor's angle
		Qpo->Transform_RotateX(&player[g_Player]->Shadows[helly].Xform, Ange.x);
		Qpo->Transform_RotateY(&player[g_Player]->Shadows[helly].Xform, Ange.y);
		Qpo->Transform_RotateZ(&player[g_Player]->Shadows[helly].Xform, Ange.z);

#if 0
										//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
		poActor_SetScale(player[g_Player]->Shadows[helly].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

		player[g_Player]->Shadows[helly].Mins.x = -20.f;
		player[g_Player]->Shadows[helly].Mins.y = -20.f;
		player[g_Player]->Shadows[helly].Mins.z = -20.f;
		player[g_Player]->Shadows[helly].Maxs.x = 20.f;
		player[g_Player]->Shadows[helly].Maxs.y = 20.f;
		player[g_Player]->Shadows[helly].Maxs.z = 20.f;

		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[helly].Xform.Translation);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shadows[helly].Avatar, 255/(helly+1));

		player[g_Player]->Shadows[helly].Avatar.IDflag = 250;
		}

	player[g_Player]->ShadowALPHA = 240;

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//##### SPAWN EFFECTS
#if 0
	jet = 0;
	while(jet < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 750) _->NomSpikes = 0;

		jet++;
		}
#endif

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItems();

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Vehicle.Model.Xform.Translation);

	player[g_Player]->Vehicle.Model.Mins.x = -20.f;
	player[g_Player]->Vehicle.Model.Mins.y = -20.f;
	player[g_Player]->Vehicle.Model.Mins.z = -20.f;
	player[g_Player]->Vehicle.Model.Maxs.x = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.y = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.z = 20.f;

#if 0
	player[g_Player]->Vehicle.Model.Motion[0] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelSpin" );
	player[g_Player]->Vehicle.Model.Motion[1] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "RWheelScale" );
	player[g_Player]->Vehicle.Model.Motion[2] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelSpin" );
	player[g_Player]->Vehicle.Model.Motion[3] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelTurn" );
	player[g_Player]->Vehicle.Model.Motion[4] = Qpo->Avatar_GetMotionByName(player[g_Player]->Vehicle.Model.AvatarDef, "FWheelScale" );

	Ange.y=PI;
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	Qpo->Transform_RotateX(&player[g_Player]->Vehicle.Model.Xform, Ange.x);
	Qpo->Transform_RotateY(&player[g_Player]->Vehicle.Model.Xform, Ange.y);
	Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.Model.Xform, Ange.z);

	QpoActor_SetScale(player[g_Player]->Vehicle.Model.Avatar, 1.2f,1.2f,1.2f);
#endif

	player[g_Player]->Vehicle.Model.Avatar.IDflag = 250;

	//### Physics Setup
	player[g_Player]->Vehicle.Const_Weight = 8;	//Ten Q_Kgs
	player[g_Player]->Vehicle.Const_FWeight = 2;	//1.5
	player[g_Player]->Vehicle.Const_RWeight = 2;	//1.5
	player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0.335;

	player[g_Player]->Vehicle.Const_SpinCancel = 0.25;	//1.8
	player[g_Player]->Vehicle.Const_SpringLift = 7.5;	//2.5  1.23
	player[g_Player]->Vehicle.Const_SpringPower = 4;
	player[g_Player]->Vehicle.Const_WheelSettleSpin = 5;
	player[g_Player]->Vehicle.Const_WheelSettleDVel = 3.5;
	player[g_Player]->Vehicle.Const_SpringLimit = 14.5;
	player[g_Player]->Vehicle.Const_DownVelCancel = 3;
	player[g_Player]->Vehicle.Const_ForceFactor = 50;	//5
	player[g_Player]->Vehicle.Const_SpringAbsorbVel = 6.6;
	player[g_Player]->Vehicle.Const_SpringAbsorbSpin = 1.15;
	player[g_Player]->Vehicle.Const_LightTouchFactor = 1.15;
	player[g_Player]->Vehicle.Const_MaxSpeed = 100;

	player[g_Player]->Vehicle.Const_SpringCrunchMAX = 15;
	//player[g_Player]->Vehicle.Const_MiddleCOGDIST = -31;
	//player[g_Player]->Vehicle.Const_SpringCompDist = 20;

	player[g_Player]->Vehicle.Const_FRICMinSlide = 15;

	//#### BUILD CRUNCH UP VECS
	player[g_Player]->Vehicle.ConstVec_FCrunch.x = 1.071;
	player[g_Player]->Vehicle.ConstVec_FCrunch.y = 7.887;
	player[g_Player]->Vehicle.ConstVec_FCrunch.z = 3.893;

	player[g_Player]->Vehicle.ConstVec_RCrunch.x = 1.102;
	player[g_Player]->Vehicle.ConstVec_RCrunch.y = 8.116;
	player[g_Player]->Vehicle.ConstVec_RCrunch.z = 1.521;

	player[g_Player]->Vehicle.GravityAlter = 1;

#if 0
	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Mech.Model.Xform.Translation);

#if 0
	Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Mech.Model.Xform.Translation);
#endif

	player[g_Player]->Mech.Model.Mins.x = -200.f;
	player[g_Player]->Mech.Model.Mins.y = -200.f;
	player[g_Player]->Mech.Model.Mins.z = -200.f;
	player[g_Player]->Mech.Model.Maxs.x = 200.f;
	player[g_Player]->Mech.Model.Maxs.y = 200.f;
	player[g_Player]->Mech.Model.Maxs.z = 200.f;

#if 0
	QpoActor_SetScale(player[g_Player]->Mech.Model.Avatar, 0.43 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Height)/100)-0.5)*2)), 0.43 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Weight)/100)-0.5)*2)), 0.43 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Weight)/100)-0.5)*2)));
#endif

	player[g_Player]->Mech.Model.Avatar.IDflag = 250;

	helly = 0;
	while(helly <= 2)
		{
		helly++;

		Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Mech.Shadows[helly].Xform.Translation);

		player[g_Player]->Mech.Shadows[helly].Mins.x = -200.f;
		player[g_Player]->Mech.Shadows[helly].Mins.y = -200.f;
		player[g_Player]->Mech.Shadows[helly].Mins.z = -200.f;
		player[g_Player]->Mech.Shadows[helly].Maxs.x = 200.f;
		player[g_Player]->Mech.Shadows[helly].Maxs.y = 200.f;
		player[g_Player]->Mech.Shadows[helly].Maxs.z = 200.f;

		QpoActor_SetScale(player[g_Player]->Mech.Shadows[helly].Avatar, 0.01,0.01,0.01);

		player[g_Player]->Mech.Shadows[helly].Avatar.IDflag = 250;
		}
#endif

	//###= First initial jump =###//
	//player[g_Player]->JumpDir = 0;
	//Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->JumpVec);

	//if(KEY_DOWN_w()) player[g_Player]->JumpDir = 1;	//Forward Jump
	//if(KEY_DOWN_s() && (KEY_DOWN_a() || KEY_DOWN_d())) player[g_Player]->JumpDir = 2;	//Backwards Jump

	//player[g_Player]->jumpposecnt = 0;
	//player[g_Player]->Mposestate = 12;
	//player[g_Player]->JumpFG = 0;

	/*if(player[g_Player]->AirBorn || player[g_Player]->Aposestate == 73)
		{
		if(player[g_Player]->JumpState != 1)
			{
			player[g_Player]->JumpFactor = 2;
			player[g_Player]->JumpState = 3;
			}
		else
			{
			player[g_Player]->JumpFactor = 1;
			player[g_Player]->JumpState = 1;
			}
		}
	else
		{*/
		//player[g_Player]->JumpFactor = 1;
		//player[g_Player]->JumpState = 1;
		//}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

#ifndef QAGEMODE_NOINTRO
  acNamePlateUpdate();
#endif

//## SETUP AI ##############################################################################################
//##########################################################################################################
//##########################################################################################################

// AI setup AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIA
//AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIA
//AIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIAIA

	if(_->NetworkOption != 1)
		{
		CharCounter = 0;
		helly = 0;
		while(helly < _->NomAI)
			{
			if(player[g_Player]->BFO.AVATARDATA[helly].LIVE == 1)
				{
				Q_Forge->Forge[helly].LIVE = 1;

				Q_Forge->Forge[helly].NetplayerFLAG = 0;

				Q_Forge->Forge[helly].AV.upspeed = -15;
				Q_Forge->Forge[helly].AV.Mins.x = -(20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
				Q_Forge->Forge[helly].AV.Mins.y = -(45 + (30*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
				Q_Forge->Forge[helly].AV.Mins.z = -(20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.x = (20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.y = (45 + (30*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)));
				Q_Forge->Forge[helly].AV.Maxs.z = (20 + (20*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

				Q_Forge->Forge[helly].PlayerSpeed = PLAYER_SPEED;

				Q_Forge->Forge[helly].GravityAlter = 1;

				//Fill Weapon Ammo
				Q_Forge->Forge[helly].WeaponAmmo = 32;

				Q_Forge->Forge[helly].HB_Illumination = 255;
				Q_Forge->Forge[helly].HB_Dead = 0;

				Q_Forge->Forge[helly].HB_DeadTimer = 500;
				Q_Forge->Forge[helly].HB_Lives = 5;
				Q_Forge->Forge[helly].HB_LiveResetSW = 1;

				//Body and Mind
				Q_Forge->Forge[helly].Q_Heart.HeartIncrement = 0;
				Q_Forge->Forge[helly].Q_Heart.PulseRate = 1;
				Q_Forge->Forge[helly].Q_Brain.Aggression = 70;

				//###### AVATAR SELECTION
				//### Obtain Correct Character Data for Avatar
				Q_Forge->Forge[helly].CharDATA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[helly].CDATID];
				Q_Forge->Forge[helly].CharDATA.BDataID = player[g_Player]->BFO.AVATARDATA[helly].BDATID;
				Q_Forge->Forge[helly].CharDATA.TEAM = player[g_Player]->BFO.AVATARDATA[helly].TEAM;
				Q_Forge->Forge[helly].Team = player[g_Player]->BFO.AVATARDATA[helly].TEAM;
				Q_Forge->Forge[helly].AVDATID = helly;
				player[g_Player]->BFO.AVATARDATA[helly].AVATARID = helly;
				
				//#### Set Role€
				Q_Forge->Forge[helly].Role = 0;
				Q_Forge->Forge[helly].Rank = 1;
				Q_Forge->Forge[helly].LEVEL = Q_Forge->Forge[helly].CharDATA.Level;

				#pragma message ("FIXME:::Start AI Start Position and initial pose")
				Q_Forge->Forge[helly].AV.Avatar.Mesh = new unAvatar();

#ifdef QAGE_OPMOD_B
				Q_Forge->Forge[helly].CharDATA.BDataID = 0;
#endif

				//if(AVATAR_PHYSICS_ENABLE) meshShellTemplates[Q_Forge->Forge[helly].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[helly].AV.Avatar.Mesh, Q_Forge->Forge[helly].CharDATA.BDataID);
				//else meshShellTemplates[Q_Forge->Forge[helly].CharDATA.AvatarREF]->clone_struct(Q_Forge->Forge[helly].AV.Avatar.Mesh);

				/*Q_Forge->Forge[helly].Xform.Translation.x = 0;
				Q_Forge->Forge[helly].Xform.Translation.y = 0;
				Q_Forge->Forge[helly].Xform.Translation.z = 0;
				Q_Forge->Forge[helly].Xform.Matrix.load_identity();

				//##### Starting position
				Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
				//Ange.y=-(PI/2);//Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
				Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); //Q_PlayerEntity->PlayerEntity.Ang.Y;//+(PI/2);
				if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
				Ange.x=-(PI/2);
				Ange.z=0;

				// Set the actor's angle
				Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Xform, Ange.x);
				Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Xform, Ange.y);
				Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Xform, Ange.z);

				Q_Forge->Forge[helly].STOREMatrix = Q_Forge->Forge[helly].Xform;*/

#if 0
				QpoActor_SetScale(Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

				Q_Forge->Forge[helly].idlespeed = 0.1;

				if(Q_Forge->Forge[helly].LEVEL > 1000) Q_Forge->Forge[helly].LEVELFactor = 1;
				else Q_Forge->Forge[helly].LEVELFactor = (((float)Q_Forge->Forge[helly].LEVEL + 1) / 1000);

				Q_Forge->Forge[helly].HB_MaxHealth = 1000 * (((Q_Forge->Forge[helly].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
				Q_Forge->Forge[helly].HB_Health = Q_Forge->Forge[helly].HB_MaxHealth;

				Q_Forge->Forge[helly].HB_MaxEnergy = 500;
				Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;

				Q_Forge->Forge[helly].HB_Armour = ((float)(Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
				Q_Forge->Forge[helly].HB_MaxArmour = ((float)(Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

				Q_Forge->Forge[helly].JINK3_PowerFactor = 1;

				//#### RESET SPELLS
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[3].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[4].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[5].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[6].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[7].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[8].LIVE = 0;
				Q_Forge->Forge[helly].CharDATA.SpellSLOT[9].LIVE = 0;

				//####### RELATIVE ATTACK SPEED
				Q_Forge->Forge[helly].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[helly].CharDATA.BodySKILL.Quickness / 100) * 0.8);

				//####### RELATIVE ENERGY EFFICIENCY
				Q_Forge->Forge[helly].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[helly].CharDATA.BodySKILL.EnergyEff / 6000);

				Q_Forge->Forge[helly].AV.Avatar.Visible = true;

				Q_Forge->Forge[helly].AV.Avatar.IDflag = helly;

#if 0
				Q_Forge->Forge[helly].AV.Motion[0] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle" );
				Q_Forge->Forge[helly].AV.Motion[1] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Walk" );
				Q_Forge->Forge[helly].AV.Motion[2] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Run" );
				Q_Forge->Forge[helly].AV.Motion[3] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Sidestep" );
				Q_Forge->Forge[helly].AV.Motion[4] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Jump" );
				Q_Forge->Forge[helly].AV.Motion[5] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LLPunch" );
				Q_Forge->Forge[helly].AV.Motion[6] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RLPunch" );
				Q_Forge->Forge[helly].AV.Motion[7] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RHPunch2" );	//RHPunch
				Q_Forge->Forge[helly].AV.Motion[8] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RMKick" );
				Q_Forge->Forge[helly].AV.Motion[9] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LMPunch" );	//LSPunch needs a home
				Q_Forge->Forge[helly].AV.Motion[10] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RMPunch" );
				Q_Forge->Forge[helly].AV.Motion[12] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WalkL" );
				Q_Forge->Forge[helly].AV.Motion[13] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WalkR" );
				Q_Forge->Forge[helly].AV.Motion[14] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunL" );
				Q_Forge->Forge[helly].AV.Motion[15] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunR" );
				Q_Forge->Forge[helly].AV.Motion[16] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SidestepL" );
				Q_Forge->Forge[helly].AV.Motion[17] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SidestepR" );
				Q_Forge->Forge[helly].AV.Motion[18] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Renzou" );		//TODO: Combine these two
				Q_Forge->Forge[helly].AV.Motion[19] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouE" );		//TODO: into one
				Q_Forge->Forge[helly].AV.Motion[20] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RSPunch" );
				Q_Forge->Forge[helly].AV.Motion[21] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Uppercut" );	//Uppercut
				Q_Forge->Forge[helly].AV.Motion[22] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HBlock" );
				Q_Forge->Forge[helly].AV.Motion[23] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle2" );
				Q_Forge->Forge[helly].AV.Motion[24] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouR" );
				Q_Forge->Forge[helly].AV.Motion[25] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon1" );
				Q_Forge->Forge[helly].AV.Motion[26] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunWep1L" );
				Q_Forge->Forge[helly].AV.Motion[27] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunWep1R" );
				Q_Forge->Forge[helly].AV.Motion[28] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep1" );
				Q_Forge->Forge[helly].AV.Motion[29] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AXKick" );
				Q_Forge->Forge[helly].AV.Motion[30] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SPKick" );
				Q_Forge->Forge[helly].AV.Motion[31] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpL" );
				Q_Forge->Forge[helly].AV.Motion[32] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpR" );
				Q_Forge->Forge[helly].AV.Motion[33] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Cartwheel" );
				Q_Forge->Forge[helly].AV.Motion[34] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon1UPP" );
				Q_Forge->Forge[helly].AV.Motion[35] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep1UPP" );
				Q_Forge->Forge[helly].AV.Motion[36] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CartWep1" );
				Q_Forge->Forge[helly].AV.Motion[37] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Idle3" );
				Q_Forge->Forge[helly].AV.Motion[38] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouL" );
				Q_Forge->Forge[helly].AV.Motion[39] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoldDash" );
				Q_Forge->Forge[helly].AV.Motion[40] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Knee" );
				Q_Forge->Forge[helly].AV.Motion[41] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpKick" );
				Q_Forge->Forge[helly].AV.Motion[42] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Wave" );
				Q_Forge->Forge[helly].AV.Motion[43] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HitStom" );
				Q_Forge->Forge[helly].AV.Motion[44] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HitUpper" );
				Q_Forge->Forge[helly].AV.Motion[45] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSpiral" );
				Q_Forge->Forge[helly].AV.Motion[46] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "DodgeL" );
				Q_Forge->Forge[helly].AV.Motion[47] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FKick" );
				Q_Forge->Forge[helly].AV.Motion[48] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunBack" );
				Q_Forge->Forge[helly].AV.Motion[53] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FallHead" );
				Q_Forge->Forge[helly].AV.Motion[54] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RHKick" );
				Q_Forge->Forge[helly].AV.Motion[55] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "FlameUpperCut" );
				Q_Forge->Forge[helly].AV.Motion[56] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HBlockHit" );
				Q_Forge->Forge[helly].AV.Motion[57] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BackFlip" );
				Q_Forge->Forge[helly].AV.Motion[58] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload" );
				Q_Forge->Forge[helly].AV.Motion[59] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinKickFull" );
				Q_Forge->Forge[helly].AV.Motion[60] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Crouch" );
				Q_Forge->Forge[helly].AV.Motion[61] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CrouchL" );
				Q_Forge->Forge[helly].AV.Motion[62] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "CrouchR" );
				Q_Forge->Forge[helly].AV.Motion[67] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "VHKick" );
				Q_Forge->Forge[helly].AV.Motion[68] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Entro" );
				Q_Forge->Forge[helly].AV.Motion[69] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwinDragon1" );
				Q_Forge->Forge[helly].AV.Motion[70] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwinDragon2" );
				Q_Forge->Forge[helly].AV.Motion[71] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Golrekka" );
				Q_Forge->Forge[helly].AV.Motion[72] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SkyPush" );
				Q_Forge->Forge[helly].AV.Motion[73] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Lowtro" );
				Q_Forge->Forge[helly].AV.Motion[74] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Lowkick" );
				Q_Forge->Forge[helly].AV.Motion[75] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Legsweep" );
				Q_Forge->Forge[helly].AV.Motion[76] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Crunch" );
				Q_Forge->Forge[helly].AV.Motion[77] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Hitwall" );
				Q_Forge->Forge[helly].AV.Motion[78] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AttFlip" );
				Q_Forge->Forge[helly].AV.Motion[79] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttP" );
				Q_Forge->Forge[helly].AV.Motion[80] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowPunchL" );
				Q_Forge->Forge[helly].AV.Motion[81] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowPunchR" );
				Q_Forge->Forge[helly].AV.Motion[82] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LBlock" );
				Q_Forge->Forge[helly].AV.Motion[83] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LBlockHit" );
				Q_Forge->Forge[helly].AV.Motion[84] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Hadouken" );
				Q_Forge->Forge[helly].AV.Motion[85] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HadoukenAir" );
				Q_Forge->Forge[helly].AV.Motion[86] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AirDash" );
				Q_Forge->Forge[helly].AV.Motion[87] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoverKick" );
				Q_Forge->Forge[helly].AV.Motion[88] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollF" );
				Q_Forge->Forge[helly].AV.Motion[89] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Taunt1" );
				Q_Forge->Forge[helly].AV.Motion[90] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Sakurat" );
				Q_Forge->Forge[helly].AV.Motion[91] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BrollyT" );
				Q_Forge->Forge[helly].AV.Motion[92] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PCombo1" );
				Q_Forge->Forge[helly].AV.Motion[93] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpiralDown" );
				Q_Forge->Forge[helly].AV.Motion[94] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSpiralOver" );
				Q_Forge->Forge[helly].AV.Motion[95] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmall" );
				Q_Forge->Forge[helly].AV.Motion[96] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "TwistKick" );
				Q_Forge->Forge[helly].AV.Motion[97] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BackFLipAtt" );
				Q_Forge->Forge[helly].AV.Motion[98] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Deflect" );
				Q_Forge->Forge[helly].AV.Motion[99] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmallL" );
				Q_Forge->Forge[helly].AV.Motion[100] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JumpSmallR" );
				Q_Forge->Forge[helly].AV.Motion[101] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PCombo2" );
				Q_Forge->Forge[helly].AV.Motion[102] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RushElbow" );
				Q_Forge->Forge[helly].AV.Motion[103] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HoldBarge" );
				Q_Forge->Forge[helly].AV.Motion[104] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "DoubleStrike" );
				Q_Forge->Forge[helly].AV.Motion[105] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LowLunge" );
				Q_Forge->Forge[helly].AV.Motion[106] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SideChop" );
				Q_Forge->Forge[helly].AV.Motion[107] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinChop" );
				Q_Forge->Forge[helly].AV.Motion[108] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollLowL" );
				Q_Forge->Forge[helly].AV.Motion[109] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RollLowR" );
				//VEHICLE MOTIONS UNUSED
				//Q_Forge->Forge[helly].AV.Motion[110] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeMount" );
				//Q_Forge->Forge[helly].AV.Motion[111] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeRush" );
				//Q_Forge->Forge[helly].AV.Motion[112] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeWheelie" );
				//Q_Forge->Forge[helly].AV.Motion[113] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "BikeIdle" );
				Q_Forge->Forge[helly].AV.Motion[114] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouP" );
				Q_Forge->Forge[helly].AV.Motion[115] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RenzouPR" );
				Q_Forge->Forge[helly].AV.Motion[116] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AttFlipE" );
				Q_Forge->Forge[helly].AV.Motion[117] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HandSlap" );
				Q_Forge->Forge[helly].AV.Motion[118] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSH" );
				Q_Forge->Forge[helly].AV.Motion[119] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHPUNCH" );
				Q_Forge->Forge[helly].AV.Motion[120] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHBG" );
				Q_Forge->Forge[helly].AV.Motion[121] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "JSRUSHKICK" );
				Q_Forge->Forge[helly].AV.Motion[122] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "StaticKick" );
				Q_Forge->Forge[helly].AV.Motion[123] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttK" );
				Q_Forge->Forge[helly].AV.Motion[124] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RDoubleKick" );
				Q_Forge->Forge[helly].AV.Motion[125] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReloadUPP" );
				Q_Forge->Forge[helly].AV.Motion[126] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RunAttK" );
				Q_Forge->Forge[helly].AV.Motion[127] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "PowerBomb" );
				Q_Forge->Forge[helly].AV.Motion[128] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LeapDownStrike" );
				Q_Forge->Forge[helly].AV.Motion[129] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "RSPINSTRIKE" );
				Q_Forge->Forge[helly].AV.Motion[130] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "SpinoutLeft" );
				Q_Forge->Forge[helly].AV.Motion[131] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "OverheadPinwheel" );
				Q_Forge->Forge[helly].AV.Motion[132] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LeapDownFist" );
				Q_Forge->Forge[helly].AV.Motion[140] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "LookRight" );

				if(Q_Forge->Forge[helly].CharDATA.Class == 2)
					{
					Q_Forge->Forge[helly].AV.Motion[63] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Glance" );
					Q_Forge->Forge[helly].AV.Motion[65] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "HealUPP" );
					Q_Forge->Forge[helly].AV.Motion[66] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Heal" );
					}

				Q_Forge->Forge[helly].AV.Motion[133] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon2" );
				Q_Forge->Forge[helly].AV.Motion[134] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "Weapon2UPP" );
				Q_Forge->Forge[helly].AV.Motion[135] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep2" );
				Q_Forge->Forge[helly].AV.Motion[136] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "AimWep2UPP" );
				Q_Forge->Forge[helly].AV.Motion[137] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload2" );
				Q_Forge->Forge[helly].AV.Motion[138] = Qpo->Avatar_GetMotionByName(Q_Forge->Forge[helly].AV.AvatarDef, "WeaponReload2UPP" );
#endif

				//##### ATTENTION REQUIRED
#if 0
				Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
#endif

				Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);

#if 0
				//Lighting
				if(Q_AvatarEntity->AvatarEntity[helly].Team == 0)	//Friendly AI
					{
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 0)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 1)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 2)	Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,200,200,230,175,155,false,8,NULL,true);
					}

				if(Q_AvatarEntity->AvatarEntity[helly].Team == 1)	//Enemy AI
					{
					if(Q_AvatarEntity->AvatarEntity[helly].Type == 0) 
						{
#if 0
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&poop,255,180,180,220,220,220,false,8,NULL,true);
#endif

						Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);
						}
					}
#endif

				//Starting Position Note: possibly not needed
				Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Pos, &Q_Forge->Forge[helly].AV.Xform.Translation);



				//Starting Rotation
				Ange.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y + (PI);
				if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
				Ange.x=-(PI/2);
				Ange.z=0;

				// Set the actor's angle
				Qpo->Transform_RotateX(&Q_Forge->Forge[helly].AV.Xform, Ange.x);		//Update Avatar's starting facing direction
				Qpo->Transform_RotateY(&Q_Forge->Forge[helly].AV.Xform, Ange.y);
				Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].AV.Xform, Ange.z);

				Q_Forge->Forge[helly].STOREMatrix = Q_Forge->Forge[helly].AV.Xform;

				Q_Forge->Forge[helly].Angles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
				Q_Forge->Forge[helly].trueAngles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;
				Q_Forge->Forge[helly].STOREAngles.y = Q_StartPoints->StartPoints[Q_Forge->Forge[helly].Team].Ang.y;

#if 0
				//m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec.y = 0;

				//Begin Transforming for Camera
				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[helly].AV.Xform, &Q_Forge->Forge[helly].AV.Up);

				Qpo->Vec3d_Subtract(&Q_Forge->Forge[helly].AV.Up, &m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec, &ScanTurnVec);
				Q_Forge->Forge[helly].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);

				//### Check Distance between Pure Left and Right to work out direction of Turn
				Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[helly].AV.Xform, &Q_Forge->Forge[helly].AV.Left);

				Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].AV.Left, &Q_Forge->Forge[helly].AV.Right);
				Qpo->Vec3d_Inverse(&Q_Forge->Forge[helly].AV.Right);

				ScanDistL = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec, &Q_Forge->Forge[helly].AV.Left);
				ScanDistR = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_RotationVec, &Q_Forge->Forge[helly].AV.Right);

#if 0
				Qpo->Camera_Set();
				glColor3f(1.0f, 0.0f, 0.0f);	//RED
				//*glBegin(GL_LINES);
				glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
				glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Left.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Left.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Left.z * 250));
				//*glEnd();
#endif

#if 0
				Qpo->Camera_Set();
				glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
				//*glBegin(GL_LINES);
				glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
				glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Right.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Right.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Right.z * 250));
				//*glEnd();
#endif

#if 0
				Qpo->Camera_Set();
				glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
				//*glBegin(GL_LINES);
				glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
				glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].ScanVecTo.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].ScanVecTo.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].ScanVecTo.z * 250));
				//*glEnd();
#endif
#if 0
				if(ScanDistL < ScanDistR) Q_Forge->Forge[helly].ScanTurnAng *= -1;

				Q_Forge->Forge[helly].trueAngles.y = Q_Forge->Forge[helly].ScanTurnAng;

				Q_Forge->Forge[helly].Angles.y = Q_Forge->Forge[helly].ScanTurnAng;
				if(Q_Forge->Forge[helly].Angles.y > (PI*2)) Q_Forge->Forge[helly].Angles.y = 0;
				if(Q_Forge->Forge[helly].Angles.y < 0) Q_Forge->Forge[helly].Angles.y = (PI*2);

				Q_Forge->Forge[helly].STOREAngles.y = Q_Forge->Forge[helly].ScanTurnAng;

				//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[helly].ScanTurnAng);
				//Qpo->Transform_Multiply(&Q_Forge->Forge[helly].AV.Xform, &AIfriendly, &Q_Forge->Forge[helly].AV.Xform);

				//Q_Forge->Forge[helly].Xform.Matrix.load_identity();
				Q_Forge->Forge[helly].Xform.Translation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].Xform.Translation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].Xform.Translation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;
				Q_Forge->Forge[helly].Xform.GhostTranslation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].Xform.GhostTranslation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].Xform.GhostTranslation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;

				//Q_Forge->Forge[helly].AV.Xform.Matrix.load_identity();
				Q_Forge->Forge[helly].AV.Xform.Translation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].AV.Xform.Translation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].AV.Xform.Translation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;
				Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.x;
				Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.y;
				Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[helly].Team]->m_CellCenter.z;
#endif
#endif

				//### Load Player Weapon
				Q_Forge->Forge[helly].Weapon.Avatar = 1;

				Q_Forge->Forge[helly].Weapon.Scale.x = 1;
				Q_Forge->Forge[helly].Weapon.Scale.y = 1;
				Q_Forge->Forge[helly].Weapon.Scale.z = 1;

				Q_Forge->Forge[helly].Weapon.Mins.x = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.y = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.z = -20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.x = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.y = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.z = 20.f;

				Q_Forge->Forge[helly].Weapon.Mins.x = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.y = -20.f;
				Q_Forge->Forge[helly].Weapon.Mins.z = -20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.x = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.y = 20.f;
				Q_Forge->Forge[helly].Weapon.Maxs.z = 20.f;

				Q_Forge->Forge[helly].Weapon.Visible = true;

				Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[helly].Weapon.Xform.Translation);

				Qpo->Mesh_SetAlpha(&Q_Forge->Forge[helly].Weapon, 0);

				Q_Forge->Forge[helly].WeaponDISPLAY = 0;

				if(Q_Forge->Forge[helly].CharDATA.Class == 2)
					{
					Q_Forge->Forge[helly].Shield.Mins.x = -500.f;
					Q_Forge->Forge[helly].Shield.Mins.y = -500.f;
					Q_Forge->Forge[helly].Shield.Mins.z = -500.f;
					Q_Forge->Forge[helly].Shield.Maxs.x = 500.f;
					Q_Forge->Forge[helly].Shield.Maxs.y = 500.f;
					Q_Forge->Forge[helly].Shield.Maxs.z = 500.f;

					Qpo->Avatar_SetAlpha(&Q_Forge->Forge[helly].Shield.Avatar, 40);

					fogbox.Min.x = Q_Forge->Forge[helly].Shield.Mins.x;
					fogbox.Min.y = Q_Forge->Forge[helly].Shield.Mins.y;
					fogbox.Min.z = Q_Forge->Forge[helly].Shield.Mins.z;
					fogbox.Max.x = Q_Forge->Forge[helly].Shield.Maxs.x;
					fogbox.Max.y = Q_Forge->Forge[helly].Shield.Maxs.y;
					fogbox.Max.z = Q_Forge->Forge[helly].Shield.Maxs.z;

					Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[helly].Shield.Xform.Translation);

					Q_Forge->Forge[helly].Shield.Avatar.IDflag = 251;
					}

				//### Load Fighter Shadows

				Q_Forge->Forge[helly].ShadowsOn = false;
				Q_Forge->Forge[helly].ShadowALPHA = 240;

				aero = 0;
				while(aero <= 2)
					{
					aero++;

					//Q_Forge->Forge[helly].Shadows[aero].Avatar.Mesh = new unAvatar();
					//meshShellTemplates[Q_Forge->Forge[helly].CharDATA.ShadowREF]->clone_struct(Q_Forge->Forge[helly].Shadows[aero].Avatar.Mesh);

					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.x = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.y = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Translation.z = 0;
					Q_Forge->Forge[helly].Shadows[aero].Xform.Matrix.load_identity();

					//##### Starting position
					Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
					Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
					if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
					Ange.x=-(PI/2);
					Ange.z=0;

					// Set the actor's angle
					Qpo->Transform_RotateX(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.x);
					Qpo->Transform_RotateY(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.y);
					Qpo->Transform_RotateZ(&Q_Forge->Forge[helly].Shadows[aero].Xform, Ange.z);

					Q_Forge->Forge[helly].Shadows[aero].Mins.x = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Mins.y = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Mins.z = -20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.x = 20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.y = 20.f;
					Q_Forge->Forge[helly].Shadows[aero].Maxs.z = 20.f;

#if 0
					QpoActor_SetScale(Q_Forge->Forge[helly].Shadows[aero].Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

					Q_Forge->Forge[helly].Shadows[aero].Avatar.Visible = true;

					Qpo->Avatar_SetAlpha(&Q_Forge->Forge[helly].Shadows[aero].Avatar, 255/(aero+1));

					Q_Forge->Forge[helly].Shadows[aero].Avatar.IDflag = helly;
					}

				//#### Set Up Trail Flags
				Q_Forge->Forge[helly].TrailFadeSpan[0][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[1][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[2][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[3][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[4][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[5][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[6][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[7][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[8][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[9][0] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[0][1] = 0;
				Q_Forge->Forge[helly].TrailFadeSpan[1][1] = 1;
				Q_Forge->Forge[helly].TrailFadeSpan[2][1] = 2;
				Q_Forge->Forge[helly].TrailFadeSpan[3][1] = 3;
				Q_Forge->Forge[helly].TrailFadeSpan[4][1] = 4;
				Q_Forge->Forge[helly].TrailFadeSpan[5][1] = 5;
				Q_Forge->Forge[helly].TrailFadeSpan[6][1] = 6;
				Q_Forge->Forge[helly].TrailFadeSpan[7][1] = 7;
				Q_Forge->Forge[helly].TrailFadeSpan[8][1] = 8;
				Q_Forge->Forge[helly].TrailFadeSpan[9][1] = 9;

#ifndef QAGEMODE_NOINTRO
				acNamePlateUpdate();
#endif

				//####### ACTIVATE ITEM ATTRIBUTES
				Q.ActivateItemsAI(helly);

#if 0
				//#### RESET SCALE AND LIGHTING
				QpoActor_SetScale(Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

#ifndef QAGEMODE_NOINTRO
				acNamePlateUpdate();
#endif

#if 1
				Q_Forge->Forge[helly].Q_Brain.MindState = MIND_ACTIVEINIT;
#endif
				}

			helly++;
			}
		}

#ifndef QAGEMODE_NOINTRO
	acNamePlateUpdate();
#endif

//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA

	//*m_GUI->m_mode++;
}

void QActiveFramewrk::acNamePlateUpdate(void)
{
#ifndef QAGEMODE_NOLOGO
	if(!g_LOAD)
		{
		//*m_GUI->vecpane[1]->vectext[0].m_texlist++;
		//*if(m_GUI->vecpane[1]->vectext[0].m_texlist > 10) m_GUI->vecpane[1]->vectext[0].m_texlist = 1;
		acRenderFrame();
		}
#endif
}

//-------------------------------------------------------------------
// Main
//-------------------------------------------------------------------

void QActiveFramewrk::acQFrame(void)
{
	//#####===--  FRAME TIME COUNTERS  --===#####

	//##### FRAME RATE LIMITER #####

	//############### CALCULATE 'ACTUAL' FRAME TIMING #########
	//#### Obtain Current system time
	//### Assign Second Time
	time_t f_time;
	time(&f_time);

	int f_timeDiff = f_time - _->FRLfirst;

	if(f_timeDiff >= 1) //Every second
		{
		//### Calculate Frame Rate result
		_->FRLresult = (float)_->FRL_LIMIT / (float)_->FRLsecond;

		//### Assign first Time
		_->FRLfirst = f_time;
		
		//############### CALCULATE 'ACTUAL' FRAME TIMING ##############
		//###### Number of loops since program start ######

		TIME += _->TimeScale * 250.0f;

		if(TIME > FLT_MAX - 2000.0f)
			{
			TIME -= FLT_MAX - 2000.0f;
			}

		//##### -----  COMPLEX TIME CONTROL  ----- #####

		//### Speed Limiter
		if(player[0]->BFO.GAMEOPTIONS.FrameratelimiterON == 1)
			{
			_->TimeScaleREAL = _->FRLresult;

			if(_->TimeScaleREAL > 1) _->TimeScaleREAL = 1;
			}
		}

	g_frame_count++;

	if(f_timeDiff >= 1)
		{
		g_curfps = g_frame_count;

		g_frame_count = 0;
		}

	float f_XYZ = (60.0f - (float)g_curfps);

	// Timescale Value Set
	float f_AmountPlus = TIMESCALE_DEFAULT;

	f_AmountPlus += (f_XYZ / 60.0f); //120.0f //30.0f ?

	_->TimeScale = ag_max(ag_min(f_AmountPlus, 0.001f), 3.00f);


//**********************************************************************************************************

//PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
//PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
// Player Control PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP


	int f_Player = g_Player;

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		//##### -+ Input Stages +- #####
		if(_->NetworkOption != 1) 
			{
			switch(g_MouseMode[g_Player])
				{
				case UN_MOUSE_SPIN_MOUSE:
					{
					Q.Input();
					}break;

				case UN_MOUSE_PUSH_MOUSE:
					{
					Q.Input();
					}break;

				case UN_MOUSE_PUSH_KEY:
					{
					Q.InputPK();
					}break;

				case UN_MOUSE_SPIN_KEY:
					{
					Q.InputPK();
					}break;
				}
			}


		//##### -+ Player Control Core +- #####

		if(_->NetworkOption != 2)
			{
			switch(player[g_Player]->PlayerMode)
				{
				case 0:
					{
					switch(g_MouseMode[g_Player])
						{
						case UN_MOUSE_SPIN_MOUSE:
							{
							Q.PLCore();
							}break;

						case UN_MOUSE_PUSH_MOUSE:
							{
							Q.PLCore_PushMouse();
							}break;

						case UN_MOUSE_PUSH_KEY:
							{
							Q.PLCore_PushKey();
							}break;

						case UN_MOUSE_SPIN_KEY:
							{
							Q.PLCore_PushMouse();
							}break;
						}
					}break;

				case 1:
					{
					Q.PLCoreMB();
					}break;
				}
			}

		g_Player = f_Player;


// Player Control PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
//PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPs
//PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
// AI Control AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA


		//### Test For Avatar Death
		helly = 0;
		while(helly < _->NomAI)
			{
			if(Q_Forge->Forge[helly].LIVE == 1)
				{
				if(Q_Forge->Forge[helly].HB_Dead == 1)
					{
					if(Q_Forge->Forge[helly].Aposestate != 30)
						{
						Q_Forge->Forge[helly].Aposestate = 30;
						Q_Forge->Forge[helly].attackon = 1;
						}

					if(Q_Forge->Forge[helly].HB_Illumination - 2 > 0)
						{
						Q_Forge->Forge[helly].HB_Illumination -= 2;

						Qpo->Avatar_SetLighting(&Q_Forge->Forge[helly].AV.Avatar,true,&goup,230,220,220,Q_Forge->Forge[helly].HB_Illumination,Q_Forge->Forge[helly].HB_Illumination,Q_Forge->Forge[helly].HB_Illumination,false,8,NULL,true);
						}
					else Q_Forge->Forge[helly].HB_Illumination = 0;
					}
				else
					{
					if(Q_Forge->Forge[helly].HB_Illumination + 2 < 255)
						{
						Q_Forge->Forge[helly].HB_Illumination += 2;
						}
					}
				}
			helly++;
			}


		//AI Loop Control
		AIcount = 0;
		while(AIcount < _->NomAI)
			{
			if(AIcount < QNOMAI + 10)
				{
				if((Q_Forge->Forge[AIcount].NetplayerFLAG == 0) && (_->NetworkOption != 1))
					{
					//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA
					// AI Brain AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIE

					Q_Forge->Forge[AIcount].CharDATA.Class = 0;

					if(Q_Forge->Forge[AIcount].Aposestate != 26 &&
						Q_Forge->Forge[AIcount].Aposestate != 28 &&
						Q_Forge->Forge[AIcount].Aposestate != 30 &&
						Q_Forge->Forge[AIcount].Aposestate != 90 &&
						Q_Forge->Forge[AIcount].Aposestate != 91 &&
						Q_Forge->Forge[AIcount].Aposestate != 51)
						{
						switch(Q_Forge->Forge[AIcount].CharDATA.Class)
							{
							case 0:
								{
								Q.AIFighterHeart(AIcount);
								} break;

							case 1:
								{
								Q.AIFighterBrain(AIcount);
								} break;

							case 2:
								{
								Q.AIClericBrain(AIcount);
								} break;

							case 3:
								{
#if 0
								Q.AISoldierBrain(AIcount);
#endif
								} break;
							}
						}

					// Enemy AI Brain AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIE
					//AIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEAIEA

					//##### -+ Avatar Control Core +- #####
					if(_->NetworkOption != 2)
						{
						switch(Q_Forge->Forge[AIcount].PlayerMode)
							{
							case 0:
								{
								Q.AICore(AIcount);
								}break;

							case 1:
								{
								Q.AICoreMB(AIcount);
								}break;
							}
						}
					}
				else	//ELSE Q_Netplayer->Netplayer
					{
					//##### -+ Avatar Control Core +- #####
					if(_->NetworkOption != 2)
						{
						if(AIcount < _->NomAI && AIcount < QNOMAI + 10)
							{
							switch(Q_Forge->Forge[AIcount].PlayerMode)
								{
								case 0:
									{
									Q.AICore(AIcount);
									}break;

								case 1:
									{
									Q.AICoreMB(AIcount);
									}break;
								}
							}
						}
					}
				}	//END AI

			AIcount++;
			}			//@@@@@@@@@@ - END OF AI CYCLE - @@@@@@@@@@@*/
		}//END QamStatus < 1
}


// AI Control AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW


void QActiveFramewrk::acWorldFrame(void)
{
	//- NEURAL NETWORK ROBOT Control Frame -//
#if 0
	Q.NNbotCONTROL();
#endif

	Q.World_Event_Engine();

	//###-- Viewform Alterations --###//
#if 0
	float f_PlayerValue = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));

	playerAV[g_Player]->Viewform.mf[0] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[1] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[2] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[3] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[4] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[5] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[6] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[7] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[8] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[9] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[10] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[11] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[12] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[13] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[14] *= f_PlayerValue;
	playerAV[g_Player]->Viewform.mf[15] *= f_PlayerValue;

	for(int f_K = 0; f_K < _->NomAI; f_K++)
		{
		if(Q_Forge->Forge[f_K].LIVE == 1)
			{
			float f_PlayerValue = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));

			playerAV[g_Player]->Viewform.mf[0] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[1] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[2] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[3] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[4] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[5] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[6] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[7] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[8] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[9] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[10] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[11] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[12] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[13] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[14] *= f_PlayerValue;
			playerAV[g_Player]->Viewform.mf[15] *= f_PlayerValue;
			}
		}
#endif

//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
//WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

	//BUILD SCREEN - PAUSE	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%>>--
	/*if(player[g_Player]->mode==1)
		{

		bmenu.xmin = 0;
		bmenu.ymin = 350;
		bmenu.xmax = 600;
		bmenu.ymax = 350;

		//Release the mouse
		ShowCursor(true);


		//Drop down the window
		while(bmenu.ymax>0)
			{		

			SetupFrame();

				//Draw top panel
			/*Qpo->Tex_Blit(Medias->toppanel,NULL,0,0);
			Qpo->Tex_Blit(icon,&robunsel,6,6);
			enerbar.xmax = ((float)aifriend[0].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,6,32);
			Qpo->Tex_Blit(icon,&robunsel,42,6);
			enerbar.xmax = ((float)aifriend[1].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,42,32);
			Qpo->Tex_Blit(icon,&robunsel,78,6);
			enerbar.xmax = ((float)aifriend[2].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,78,32);
			Qpo->Tex_Blit(icon,&robunsel,114,6);
			enerbar.xmax = ((float)aifriend[3].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,114,32);

				//Drop the menu
			Qpo->Tex_Blit(Medias->buildm,&bmenu,100,42);
			Gamesystem->FinishFrame();

			bmenu.ymin = bmenu.ymin - ((bmenu.Top/10)+3);

			if(bmenu.Top<0) bmenu.ymin = 0;*//*
			}

		//*****###-Construct the Construct LOOP-###*****

		pause = 1;

		while(pause==1)
			{

			// begin the scene
			SetupFrame();

			/*Draw top panel
			Qpo->Tex_Blit(Medias->toppanel,NULL,0,0);
			Qpo->Tex_Blit(icon,&robunsel,6,6);
			enerbar.xmax = ((float)aifriend[0].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,6,32);
			Qpo->Tex_Blit(icon,&robunsel,42,6);
			enerbar.xmax = ((float)aifriend[1].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,42,32);
			Qpo->Tex_Blit(icon,&robunsel,78,6);
			enerbar.xmax = ((float)aifriend[2].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,78,32);
			Qpo->Tex_Blit(icon,&robunsel,114,6);
			enerbar.xmax = ((float)aifriend[3].energy / 150 ) * 30;
			Qpo->Tex_Blit(icon,&enerbar,114,32);

			//Draw menu
			Qpo->Tex_Blit(Medias->buildm,&bmenu,100,42);

			textbox.xmin = 112;
			textbox.xmax = 155;
			textbox.ymin = 57;
			textbox.ymax = 75;
			QpoFont_DrawText(font1, "Structures", &textbox, &fontcol, GE_FONT_WORDWRAP, NULL);

			Qpo->Tex_Blit(icon,&mineunsel,200,100);

			//##Text##

			textbox.xmin = 112;
			textbox.xmax = 250;
			textbox.ymin = 57;
			textbox.ymax = 250;

			//QpoFont_DrawText(font1, "Structures", &textbox, &fontcol, GE_FONT_WORDWRAP, NULL);*//*

			//Gamesystem->FinishFrame();

			//Menu exit keys
			if (KEY_PRESS_DOWN(QIN_m))
				{
				player[g_Player]->mode = 0;
				pause = 0;
				ShowCursor(false);
				}			
			}
		}

		//*Determine position of 3d build cursor*
		/*scanback = player_flags.ViewXForm.Translation;
		scanfront = player_flags.ViewXForm.Translation;
		Qpo->Transform_GetIn(&player_flags.ViewXForm,&player_flags.In);
		Qpo->Vec3d_AddScaled(&scanback, 3000, &player_flags.In, &scanfront); //<-Cursor length

		// Scan
		if(Qpo->Collision_RayTest(
					 NULL,
					 NULL,
					 &scanback, 
					 &scanfront, 
					 // GE_CONTENTS_CANNOT_OCCUPY						//GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
					 // GE_COLLIDE_ALL,								////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
					 0xffffffff, NULL, NULL, 
					 &player_flags.Collision))
			{

			if(player_flags.Collision.Impact.m_X>wurld.minepos[0].x-200 &&
				player_flags.Collision.Impact.m_X<wurld.minepos[0].x+200 &&
				player_flags.Collision.Impact.m_Y>wurld.minepos[0].y-200 &&
				player_flags.Collision.Impact.m_Y<wurld.minepos[0].y+200 &&
				player_flags.Collision.Impact.m_Z>wurld.minepos[0].z-200 &&
				player_flags.Collision.Impact.m_Z<wurld.minepos[0].z+200)

				{

				FVert.alpha = 255;
				FVERT[0].blue = 255;
				FVERT[0].green = 255;
				FVERT[0].red = 255;
				FVert.u = 0;
				FVert.v = 0;
				FVert.x = wurld.minepos[0].x;
				FVert.y = wurld.minepos[0].y;
				FVert.z = wurld.minepos[0].z;

				pollie = Qpo->Poly_AddOnce(&FVert, 1, Medias->mmine, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 1.0f);

				}

			}

		if(firsttime1==0)
			{
			firsttime1=1;

			FVert.alpha = 255;
			FVERT[0].blue = 255;
			FVERT[0].green = 255;
			FVERT[0].red = 255;
			FVert.u = 0;
			FVert.v = 0;
			FVert.x = wurld.minepos[0].x;
			FVert.y = wurld.minepos[0].y;
			FVert.z = wurld.minepos[0].z;

			pollie = Qpo->Poly_Add (World, &FVert, 1, Medias->mmine, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 1.0f);
			}

		}*//*

//**********************************************************************************************************
//**********************************************************************************************************
// MAIN RENDER AND HUD DRAWING *****************************************************************************

	if (DisplayInfo == true)
		{
		//*egen3d_FPS(true);
		}

	//### Player Visibility Checks
	if(player[g_Player]->ShadowsOn == false)
		{
		aero=0;
		while(aero <= 2)
			{
			aero++;
			//*geWorld_SetQpoAvatar(World, player[g_Player]->Shadows[aero].Avatar, GE_ACTOR_COLLIDE);
			player[g_Player]->Shadows[aero].AV.Visible = false;
			}
		}
	else
		{
		aero=0;
		while(aero <= 2)
			{
			aero++;
			//*geWorld_SetQpoAvatar(World, player[g_Player]->Shadows[aero].Avatar, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE);
			player[g_Player]->Shadows[aero].AV.Visible = true;
			}
		}

	//### Visibility Checks Actor in range and not behind geometry
	PlayerPos = player[g_Player]->ViewXForm.Translation;

	helly=0;
	while(helly < _->NomAI)
		{
		if(Q_Forge->Forge[helly].LIVE == 1)
			{
			ActorPos = Q_Forge->Forge[helly].AV.Xform.Translation;

			Qpo->Vec3d_Subtract(&PlayerPos, &ActorPos, &SubResult);
			ActorVisDist = Qpo->Vec3d_Length(&SubResult);


			if(Q_Forge->Forge[helly].ShadowsOn == false)
				{
				aero=0;
				while(aero <= 2)
					{
					aero++;
					//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].Shadows[aero].Avatar, GE_ACTOR_COLLIDE);
					Q_Forge->Forge[helly].Shadows[aero].AV.Visible = false;
					}
				}
			else
				{
				aero=0;
				while(aero <= 2)
					{
					aero++;
					//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].Shadows[aero].Avatar, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE);
					Q_Forge->Forge[helly].Shadows[aero].AV.Visible = true;
					}
				}

			if((ActorVisDist <= (VisClipDist*2)) && (Q_Forge->Forge[helly].AV.Avatar.Visible == false))
				{
				//## Actor Visibility
				//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].AV.Avatar, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE);
				Q_Forge->Forge[helly].AV.Avatar.Visible = true;

				//## Weapon Visibility
				//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].Weapon.Avatar, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE);
				Q_Forge->Forge[helly].Weapon.Avatar.Visible = true;

				//## Shadow Visibility
				if(Q_Forge->Forge[helly].ShadowsOn == true)
					{
					aero=0;
					while(aero <= 2)
						{
						aero++;
						//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].Shadows[aero].Avatar, GE_ACTOR_RENDER_ALWAYS | GE_ACTOR_COLLIDE);
						Q_Forge->Forge[helly].Shadows[aero].AV.Visible = true;
						}
					}
				}

			if((ActorVisDist > (VisClipDist*2)) && (Q_Forge->Forge[helly].AV.Avatar.Visible == true))
				{
				//## Actor Visibility
				//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].AV.Avatar, GE_ACTOR_COLLIDE);
				Q_Forge->Forge[helly].AV.Avatar.Visible = false;

				//## Weapon Visibility
				//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].Weapon.Avatar, GE_ACTOR_COLLIDE);
				Q_Forge->Forge[helly].Weapon.Avatar.Visible = false;

				//## Shadow Visibility
				aero=0;
				while(aero <= 2)
					{
					aero++;
					//*geWorld_SetQpoAvatar(World, Q_Forge->Forge[helly].Shadows[aero].Avatar, GE_ACTOR_COLLIDE);
					Q_Forge->Forge[helly].Shadows[aero].AV.Visible = false;
					}
				}
			}

		helly++;
		}*/

	//#### RESET Frame Limiter Targets
	//_->FRLtarget = 0;
	_->FRLpossibleT = 0;
	//_->FRLON = 0;

	//Process a network frame
	if(_->NetworkOption == 1)
		{
		//###### SEARCH PLAYERS #######
		//Q_SearchPlayers();

		//QNETWORKClientFrame(QHost.Client,Time);
		}

	if(_->NetworkOption == 2)
		{
		//###### SEARCH PLAYERS #######
		//Q_SearchPlayers();

		//###### PROCESS FRAME #######
		//QNETWORKHostFrame();
		}

//**********************************************************************************************************
// Text out ************************************************************************************************

	//Emergency Lasers
	/*Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_SEnergy->SEnergy[0].Matrix);

	Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[0].Matrix, &Q_SEnergy->SEnergy[0].TraVec);
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[0].Matrix.Translation, 200, &Q_SEnergy->SEnergy[0].TraVec, &Q_SEnergy->SEnergy[0].TraVec);
	//Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[0].TraVec);
	//Q_SEnergy->SEnergy[_->NomSEnergy].TraVec.y += 0.25;

	Q.ShowLine(&Q_SEnergy->SEnergy[0].Matrix.Translation, &Q_SEnergy->SEnergy[0].TraVec, &player[g_Player]->ViewXForm.Translation, 2, Medias->LaserSight, 125, 255, 0, 0, 1);

	Qpo->Transform_GetUp(&Q_SEnergy->SEnergy[0].Matrix, &Q_SEnergy->SEnergy[0].TraVec);
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[0].Matrix.Translation, 200, &Q_SEnergy->SEnergy[0].TraVec, &Q_SEnergy->SEnergy[0].TraVec);
	Q.ShowLine(&Q_SEnergy->SEnergy[0].Matrix.Translation, &Q_SEnergy->SEnergy[0].TraVec, &player[g_Player]->ViewXForm.Translation, 2, Medias->LaserSight, 125, 0, 255, 0, 1);

	Qpo->Transform_GetLeft(&Q_SEnergy->SEnergy[0].Matrix, &Q_SEnergy->SEnergy[0].TraVec);
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[0].Matrix.Translation, 200, &Q_SEnergy->SEnergy[0].TraVec, &Q_SEnergy->SEnergy[0].TraVec);
	Q.ShowLine(&Q_SEnergy->SEnergy[0].Matrix.Translation, &Q_SEnergy->SEnergy[0].TraVec, &player[g_Player]->ViewXForm.Translation, 2, Medias->LaserSight, 125, 0, 0, 255, 1);*//*

	//Emergency Textout
	//if(TextON == 1)
	//time( &SysTime );
	
   /*_ftime( &timebuffer );
   timeline = ctime( & ( timebuffer.time ) );

   sprintf( buffer, "The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20] );*//*

	//if(_->NetworkOption == 2)
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
		{
		hdc = GetDC(hWnd);
		old_fcolor = SetTextColor(hdc, RGB(0,255,0));
		old_bcolor = SetBkColor(hdc, RGB(0,0,0));
		old_tmode = SetBkMode(hdc, OPAQUE);

		text1 = player[g_Player]->TestVALUE01;
		text2 = player[g_Player]->TestVALUE02;
		text3 = player[g_Player]->TestVALUE02;
		text4 = Q_Netplayer->Netplayer[0].ID;
		if((Q_Netplayer->Netplayer[0].UpdateCHAR > text5) || (KEY_PRESS_DOWN(QIN_F1))) text5 = Q_Netplayer->Netplayer[0].UpdateCHAR;
		text6 = Q_Netplayer->Netplayer[1].Live;
		text7 = Q_Netplayer->Netplayer[1].ID;
		if((Q_Netplayer->Netplayer[1].UpdateCHAR > text8) || (KEY_PRESS_DOWN(QIN_F1))) text8 = Q_Netplayer->Netplayer[1].UpdateCHAR;
		text9 = Q_Netplayer->Netplayer[2].Live;
		text10 = Q_Netplayer->Netplayer[2].ID;
		if((Q_Netplayer->Netplayer[2].UpdateCHAR > text11) || (KEY_PRESS_DOWN(QIN_F1))) text11 = Q_Netplayer->Netplayer[2].UpdateCHAR;
		/*text6 = player[g_Player]->TestVALUE06;
		text7 = player[g_Player]->TestVALUE07;
		text8 = player[g_Player]->TestVALUE08;
		text9 = player[g_Player]->TestVALUE09;
		text10 = player[g_Player]->TestVALUE10;
		text11 = player[g_Player]->Vehicle.Const_WheelSettleDVel;
		text12 = player[g_Player]->Vehicle.Const_SpringLimit;
		text13 = player[g_Player]->Vehicle.Const_SpringAbsorbVel;
		text14 = player[g_Player]->Vehicle.Const_ForceFactor;
		text15 = player[g_Player]->Vehicle.Const_SpringAbsorbSpin;
		text16 = player[g_Player]->Vehicle.Phys_ForceFactor;
		text17 = player[g_Player]->Vehicle.Const_LightTouchFactor;*/
		
		/*sprintf(buffer, "*- TEST VALUES -*");
		//*TextOut(hdc, 100,23, buffer ,strlen(buffer));
		sprintf(buffer, "Spell: %f  ", text1);
		//*TextOut(hdc, 20,36, buffer ,strlen(buffer));
		sprintf(buffer, "intensity: %f  ", text2);
		//*TextOut(hdc, 20,49, buffer ,strlen(buffer));*/

		/*sprintf(buffer, "");
		//*TextOut(hdc, 100,23, buffer ,strlen(buffer));
		sprintf(buffer, "", text1);
		//*TextOut(hdc, 20,36, buffer ,strlen(buffer));
		sprintf(buffer, "", text2);
		//*TextOut(hdc, 20,49, buffer ,strlen(buffer));

		//sprintf(buffer, "OptionsCOUNT: %f  ", text3);
		////*TextOut(hdc, 20,66, buffer ,strlen(buffer));


		//Qpo->GUI_Printf(20,79, "Mirrors: %f", player[g_Player]->TestVALUE01);
		//Qpo->GUI_Printf(20,92, "Mirrors: %f", player[g_Player]->TestVALUE01);


		/*sprintf(buffer, "Q_Netplayer->Netplayer[0].ID: %f  ", text4);
		//*TextOut(hdc, 20,79, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[0].UpdateCHAR: %f  ", text5);
		//*TextOut(hdc, 20,92, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[1].Live: %f  ", text6);
		//*TextOut(hdc, 20,105, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[1].ID: %f  ", text7);
		//*TextOut(hdc, 20,118, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[1].UpdateCHAR: %f  ", text8);
		//*TextOut(hdc, 20,131, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[2].Live: %f  ", text9);
		//*TextOut(hdc, 20,144, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[2].ID: %f  ", text10);
		//*TextOut(hdc, 20,157, buffer ,strlen(buffer));
		sprintf(buffer, "Q_Netplayer->Netplayer[2].UpdateCHAR: %f  ", text11);
		//*TextOut(hdc, 20,170, buffer ,strlen(buffer));
		/*sprintf(buffer, "Const_SpringLimit %f  ", text12);
		//*TextOut(hdc, 20,183, buffer ,strlen(buffer));
		sprintf(buffer, "Const_SpringAbsorbVel %f  ", text13);
		//*TextOut(hdc, 20,196, buffer ,strlen(buffer));
		sprintf(buffer, "Const_ForceFactor %f  ", text14);
		//*TextOut(hdc, 20,209, buffer ,strlen(buffer));
		sprintf(buffer, "Const_SpringAbsorbSpin %f  ", text15);
		//*TextOut(hdc, 20,222, buffer ,strlen(buffer));
		sprintf(buffer, "Phys_ForceFactor %f  ", text16);
		//*TextOut(hdc, 20,235, buffer ,strlen(buffer));
		sprintf(buffer, "Const_LightTouchFactor %f  ", text17);
		//*TextOut(hdc, 20,248, buffer ,strlen(buffer));*//*
		}

	if(KEY_PRESS_DOWN(QIN_F6))
		{
		hdc = GetDC(hWnd);
		old_fcolor = SetTextColor(hdc, RGB(0,255,0));
		old_bcolor = SetBkColor(hdc, RGB(0,0,0));
		old_tmode = SetBkMode(hdc, OPAQUE);

		text1 = player[g_Player]->Vehicle.AttachTempVEC.x;
		text2 = player[g_Player]->Vehicle.AttachTempVEC.y;
		text3 = player[g_Player]->Vehicle.AttachTempVEC.z;
		text4 = player[g_Player]->Vehicle.AttachTempROTX;
		text5 = player[g_Player]->Vehicle.AttachTempROTY;
		text6 = player[g_Player]->Vehicle.AttachTempROTZ;
		text7 = player[g_Player]->Vehicle.Const_MiddleCOGDISTX;
		text8 = player[g_Player]->Vehicle.Const_MiddleCOGDISTY;
		text9 = player[g_Player]->Vehicle.Const_MiddleCOGDISTZ;
		/*text11 = player[g_Player]->Vehicle.Const_WheelSettleDVel;
		text12 = player[g_Player]->Vehicle.Const_SpringLimit;
		text13 = player[g_Player]->Vehicle.Const_SpringAbsorbVel;
		text14 = player[g_Player]->Vehicle.Const_ForceFactor;
		text15 = player[g_Player]->Vehicle.Const_SpringAbsorbSpin;
		text16 = player[g_Player]->Vehicle.Phys_ForceFactor;
		text17 = player[g_Player]->Vehicle.Const_LightTouchFactor;*/
		
		/*sprintf(buffer, "*- TEST VALUES -*");
		//*TextOut(hdc, 100,23, buffer ,strlen(buffer));
		sprintf(buffer, "AttachTempVEC.x: %f  ", text1);
		//*TextOut(hdc, 20,36, buffer ,strlen(buffer));
		sprintf(buffer, "AttachTempVEC.y: %f  ", text2);
		//*TextOut(hdc, 20,49, buffer ,strlen(buffer));
		sprintf(buffer, "AttachTempVEC.z: %f  ", text3);
		//*TextOut(hdc, 20,66, buffer ,strlen(buffer));
		sprintf(buffer, "AttachTempROTX: %f  ", text4);
		//*TextOut(hdc, 20,79, buffer ,strlen(buffer));
		sprintf(buffer, "AttachTempROTY: %f  ", text5);
		//*TextOut(hdc, 20,92, buffer ,strlen(buffer));
		sprintf(buffer, "AttachTempROTZ: %f  ", text6);
		//*TextOut(hdc, 20,105, buffer ,strlen(buffer));*/
		
		/*Qpo->GUI_Printf(100,23, "*- TEST VALUES -*");
		Qpo->GUI_Printf(20,36, "ExpandSTRENGTH: %f", TestfloatALPHA1);
		Qpo->GUI_Printf(20,49, "ExpandCUTOFF: %f", TestfloatALPHA2);
		Qpo->GUI_Printf(20,66, "SpritesLIMIT: %f", TestfloatALPHA3);
		Qpo->GUI_Printf(20,79, "CloudsLIMIT: %f", TestfloatALPHA4);

		Qpo->GUI_Printf(20,92, "PowerFactor: %f", player[g_Player]->JINK3_PowerFactor);
		Qpo->GUI_Printf(20,105, "PowerFactor: %f", player[g_Player]->JINK3_WeaponFactor);

		Qpo->GUI_Printf(20,118, "Constitution: %f", player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution);

		//Qpo->GUI_Printf(20,131, "Const_MiddleCOGDISTY: %f", player[g_Player]->Vehicle.Const_MiddleCOGDISTY);
		//Qpo->GUI_Printf(20,144, "Const_MiddleCOGDISTZ: %f", player[g_Player]->Vehicle.Const_MiddleCOGDISTZ);
		//Qpo->GUI_Printf(20,157, "player[g_Player]->Vehicle.NewROTINC: %f", player[g_Player]->Vehicle.NewROTINC);
		//Qpo->GUI_Printf(20,170, "FWheelPOS.y: %f", TestVec1.y);
		//Qpo->GUI_Printf(20,183, "FWheelPOS.z: %f", TestVec1.z);
		//Qpo->GUI_Printf(20,196, "RWheelPOS.x: %f", TestVec2.x);
		//Qpo->GUI_Printf(20,209, "RWheelPOS.y: %f", TestVec2.y);
		//Qpo->GUI_Printf(20,222, "RWheelPOS.z: %f", TestVec2.z);

		/*sprintf(buffer, "", text3);
		//*TextOut(hdc, 20,66, buffer ,strlen(buffer));
		/*sprintf(buffer, "BLUE: %f  ", text4);
		//*TextOut(hdc, 20,79, buffer ,strlen(buffer));
		/*sprintf(buffer, "attposecnt: %f  ", text5);
		//*TextOut(hdc, 20,92, buffer ,strlen(buffer));
		/*sprintf(buffer, "TestVALUE06: %f  ", text6);
		//*TextOut(hdc, 20,105, buffer ,strlen(buffer));
		sprintf(buffer, "TestVALUE07: %f  ", text7);
		//*TextOut(hdc, 20,118, buffer ,strlen(buffer));
		sprintf(buffer, "TestVALUE08: %f  ", text8);
		//*TextOut(hdc, 20,131, buffer ,strlen(buffer));
		sprintf(buffer, "TestVALUE09: %f  ", text9);
		//*TextOut(hdc, 20,144, buffer ,strlen(buffer));
		sprintf(buffer, "TestVALUE010: %f  ", text10);
		//*TextOut(hdc, 20,157, buffer ,strlen(buffer));
		/*sprintf(buffer, "Const_WheelSettleDVel %f  ", text11);
		//*TextOut(hdc, 20,170, buffer ,strlen(buffer));
		sprintf(buffer, "Const_SpringLimit %f  ", text12);
		//*TextOut(hdc, 20,183, buffer ,strlen(buffer));
		sprintf(buffer, "Const_SpringAbsorbVel %f  ", text13);
		//*TextOut(hdc, 20,196, buffer ,strlen(buffer));
		sprintf(buffer, "Const_ForceFactor %f  ", text14);
		//*TextOut(hdc, 20,209, buffer ,strlen(buffer));
		sprintf(buffer, "Const_SpringAbsorbSpin %f  ", text15);
		//*TextOut(hdc, 20,222, buffer ,strlen(buffer));
		sprintf(buffer, "Phys_ForceFactor %f  ", text16);
		//*TextOut(hdc, 20,235, buffer ,strlen(buffer));
		sprintf(buffer, "Const_LightTouchFactor %f  ", text17);
		//*TextOut(hdc, 20,248, buffer ,strlen(buffer));*//*
		}*/

	if(_->ANGELeditFF == 1)
		{
		//INCREASE MAP NUMBER
		if(KEY_PRESS_DOWN(QIN_KP6))
			{
			if(_->ANGELeditKEYPRESS1 == 0)
				{
				_->ANGELeditKEYPRESS1 = 1;
				if((_->ANGELeditMAPNUM + 1) < 35) _->ANGELeditMAPNUM++;
				}
			}
		else _->ANGELeditKEYPRESS1 = 0;

		//DECREASE MAP NUMBER
		if(KEY_PRESS_DOWN(QIN_KP4))
			{
			if(_->ANGELeditKEYPRESS2 == 0)
				{
				_->ANGELeditKEYPRESS2 = 1;
				if((_->ANGELeditMAPNUM - 1) >= 0) _->ANGELeditMAPNUM--;
				}
			}
		else _->ANGELeditKEYPRESS2 = 0;


		//#### TOGGLE COLOUR EDIT ON/OFF
		if(KEY_PRESS_DOWN(QIN_KP0))
			{
			if(_->ANGELeditKEYPRESST == 0)
				{
				_->ANGELeditKEYPRESST = 1;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.ANGELEDITFLAG == 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.ANGELEDITFLAG = 1;
				else
					{
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.ANGELEDITFLAG = 0;

					int K=0;
					while(K < 38)
						{
						Qpo->Avatar_GetTex(&playerAV[g_Player]->Avatar, K, Medias->ANGELeditBitmap, &_->ANGELeditBitmapSRed, &_->ANGELeditBitmapSGreen, &_->ANGELeditBitmapSBlue);
						Qpo->Avatar_SetTex(&playerAV[g_Player]->Avatar, K, Medias->ANGELeditBitmap, &TEMP_AngelCOLOURS.RED[K], &TEMP_AngelCOLOURS.GREEN[K], &TEMP_AngelCOLOURS.BLUE[K]);
						K++;
						}

					warp=0;
					while(warp <= 2)
						{
						warp++;
						K=0;
						while(K < 38)
							{
							Qpo->Avatar_GetTex(&player[g_Player]->Shadows[warp].Avatar, K, Medias->ANGELeditBitmap, &_->ANGELeditBitmapSRed, &_->ANGELeditBitmapSGreen, &_->ANGELeditBitmapSBlue);
							Qpo->Avatar_SetTex(&player[g_Player]->Shadows[warp].Avatar, K, Medias->ANGELeditBitmap, &TEMP_AngelCOLOURS.RED[K], &TEMP_AngelCOLOURS.GREEN[K], &TEMP_AngelCOLOURS.BLUE[K]);
							K++;
							}
						}
					}
				}
			}
		else _->ANGELeditKEYPRESST = 0;


		//PAINT MAP
		if(KEY_PRESS_DOWN(QIN_KP5))
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER] = _->ANGELeditBitmapRed;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER] = _->ANGELeditBitmapGreen;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER] = _->ANGELeditBitmapBlue;

			Qpo->Avatar_GetTex(&playerAV[g_Player]->Avatar, Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER, Medias->ANGELeditBitmap, &_->ANGELeditBitmapSRed, &_->ANGELeditBitmapSGreen, &_->ANGELeditBitmapSBlue);
			Qpo->Avatar_SetTex(&playerAV[g_Player]->Avatar, Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER, Medias->ANGELeditBitmap, &player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER], &player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER], &player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER]);

			warp=0;
			while(warp <= 2)
				{
				warp++;
				Qpo->Avatar_GetTex(&player[g_Player]->Shadows[warp].Avatar, Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER, Medias->ANGELeditBitmap, &_->ANGELeditBitmapSRed, &_->ANGELeditBitmapSGreen, &_->ANGELeditBitmapSBlue);
				Qpo->Avatar_SetTex(&player[g_Player]->Shadows[warp].Avatar, Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER, Medias->ANGELeditBitmap, &player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER], &player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER], &player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER]);
				}
			}

		if(KEY_PRESS_DOWN(QIN_KP7))
			{
			_->ANGELeditBitmapRed += 1;
			}

		if(KEY_PRESS_DOWN(QIN_KP1))
			{
			_->ANGELeditBitmapRed -= 1;
			}

		if(KEY_PRESS_DOWN(QIN_KP8))
			{
			_->ANGELeditBitmapGreen += 1;
			}

		if(KEY_PRESS_DOWN(QIN_KP2))
			{
			_->ANGELeditBitmapGreen -= 1;
			}

		if(KEY_PRESS_DOWN(QIN_KP9))
			{
			_->ANGELeditBitmapBlue += 1;
			}

		if(KEY_PRESS_DOWN(QIN_KP3))
			{
			_->ANGELeditBitmapBlue -= 1;
			}

		if(KEY_PRESS_DOWN(QIN_PLUS))
			{
			for(int f_iter = 0; f_iter < 36; f_iter++)
				{
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[f_iter] = 0;
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[f_iter] = 0;
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[f_iter] = 0;
				}
			}

		if(KEY_PRESS_DOWN(QIN_MINUS))
			{
			for(int f_iter = 0; f_iter < 36; f_iter++)
				{
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[f_iter] = rand() % 255;
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[f_iter] = rand() % 255;
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[f_iter] = rand() % 255;
				}
			}

		if(KEY_PRESS_DOWN(QIN_DIVIDE))
			{
			_->ANGELeditBitmapRed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER];
			_->ANGELeditBitmapGreen = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER];
			_->ANGELeditBitmapBlue = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[Q_ANGELeditMAP->ANGELeditMAP[_->ANGELeditMAPNUM].MAPPOINTER];
			}
		}

//**********************************************************************************************************
//**********************************************************************************************************

// Drawing Bitmaps *****************************************************************************************
//**********************************************************************************************************

#if 0
	//Qpo->Tex_BlitAlpha(Medias->BlackOut, 0, 0, 800, 600, sunrise/2, 1.0f, 1.0f);

	//#### Player Scope
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE > 1)
		{
		if(player[g_Player]->WeaponZoomFACT > 0)
			{
			Qpo->Tex_BlitAlpha(Medias->Scope, 0, 0, 800, 600, player[g_Player]->WeaponZoomFACT*255, 1.0f, 1.0f,255,255,255);
			}
		}

	//DAMAGE Flash
	if(player[g_Player]->HB_HReduceON == 1)
		{
		if(player[g_Player]->HB_ReduceRectColor.alpha == 255) player[g_Player]->HB_FlashRectColor.alpha = 255;
		player[g_Player]->HB_FlashRectColor.red = 235;
		player[g_Player]->HB_FlashRectColor.green = 0;
		player[g_Player]->HB_FlashRectColor.blue = 0;
		player[g_Player]->HB_FlashRectColor.alpha -= 51;

		player[g_Player]->HB_ReduceRectFill.xmin = 0;
		player[g_Player]->HB_ReduceRectFill.xmax = 800;
		player[g_Player]->HB_ReduceRectFill.ymin = 0;
		player[g_Player]->HB_ReduceRectFill.ymax = 600;
		if(player[g_Player]->HB_FlashRectColor.alpha > 0) Qpo->Draw_FillRect(&player[g_Player]->HB_ReduceRectFill, &player[g_Player]->HB_FlashRectColor);
		}

	//## Bullet Counter
	if(player[g_Player]->WeaponStatus != 0)
		{
		Brushrect.xmin = 0;
		Brushrect.xmax = 34;
		Brushrect.ymin = 0 + ( 256 - ( player[g_Player]->WeaponAmmo * 8 ));
		Brushrect.ymax = 256;
		Qpo->Tex_Blit(Medias->BulletCount,&Brushrect,0,240 + ( 256 - ( player[g_Player]->WeaponAmmo * 8 )));
		}

		//HUD Bottom
	Brushrect.xmin = 0;
	Brushrect.xmax = 66;
	Brushrect.ymin = 0;
	Brushrect.ymax = 105;
	Qpo->Tex_Blit(Medias->hudbottom1,&Brushrect,0,495);

	Brushrect.xmin = 67;
	Brushrect.xmax = 132;
	Brushrect.ymin = 0;
	Brushrect.ymax = 105;
	Qpo->Tex_Blit(Medias->hudbottom1,&Brushrect,734,495);

	//Qpo->Tex_BlitAlpha(Medias->hudbottom2, 66, 556, 334, 44, 120.0f, 1.0f, 1.0f,255,255,255);
	//Qpo->Tex_BlitAlpha(Medias->hudbottom3, 400, 556, 334, 44, 120.0f, 1.0f, 1.0f,255,255,255);

	Qpo->Tex_BlitAlpha(Medias->hudbottom2, 66, 584, 334, 16, 120.0f, 1.0f, 1.0f,255,255,255);
	Qpo->Tex_BlitAlpha(Medias->hudbottom3, 400, 584, 334, 16, 120.0f, 1.0f, 1.0f,255,255,255);


	//####### Player Radar
	//### Draw Radar
	if(player[g_Player]->BFO.GAMEOPTIONS.RadarON == 1)
		{
		Qpo->Tex_BlitAlpha(Medias->hudRadar, 544, 0, 256, 256, 80.0f, 1.0f, 1.0f,255,255,255);

		//### Place AI Avatars
		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				//#### Find Player in World Space
				_->RADplayerPOS = playerAV[g_Player]->Xform.Translation;
				_->RADplayerPOS.y = 0;

				//#### Find Avatar in World Space
				_->RADavatarPOS = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
				_->RADavatarPOS.y = 0;

				//#### Find Avatar Position
				Qpo->Vec3d_Subtract(&_->RADavatarPOS, &_->RADplayerPOS, &_->RADavatarRADVEC);

				_->RADavatarRADLENGTH = Qpo->Vec3d_Length(&_->RADavatarRADVEC);

				if(_->RADavatarRADLENGTH / _->RADSCALE > 128)
					{
					_->RADavatarRADLENGTH = 128;
					Qpo->Vec3d_Normalize(&_->RADavatarRADVEC);
					Qpo->Vec3d_Scale(&_->RADavatarRADVEC, _->RADavatarRADLENGTH, &_->RADavatarRADVEC);	//Radar SIZE EDIT
					}
				else
					{
					Qpo->Vec3d_Normalize(&_->RADavatarRADVEC);
					Qpo->Vec3d_Scale(&_->RADavatarRADVEC, _->RADavatarRADLENGTH / _->RADSCALE, &_->RADavatarRADVEC);	//Radar SIZE EDIT
					}

				_->RADmatrixIN = _->RADavatarRADVEC;
				_->RADmatrixUP.x = 0;
				_->RADmatrixUP.y = 1;
				_->RADmatrixUP.z = 0;
				
				Qpo->Vec3d_CrossProduct(&_->RADmatrixIN, &_->RADmatrixUP, &_->RADmatrixLEFT);
				Qpo->Transform_New_LeftUpIn(&_->RADrotatematrix, &_->RADmatrixLEFT, &_->RADmatrixUP, &_->RADmatrixIN);
				Qpo->Transform_RotateY(&_->RADrotatematrix, -player[g_Player]->Angles.y);
				Qpo->Transform_GetIn(&_->RADrotatematrix, &_->RADavatarRADVEC);

				_->RADavatarREALRADX = 672;
				_->RADavatarREALRADZ = 129;

				_->RADavatarREALRADX += _->RADavatarRADVEC.x;
				_->RADavatarREALRADZ += _->RADavatarRADVEC.z;

				if(Q_Forge->Forge[SCRAM].CharDATA.Class == 0 || Q_Forge->Forge[SCRAM].CharDATA.Class == 2)
					{ _->RADavatarREALSCALE = Q_Forge->Forge[SCRAM].JINK3_PowerFactor / 5; }

				if(Q_Forge->Forge[SCRAM].CharDATA.Class == 1)
					{ _->RADavatarREALSCALE = Q_Forge->Forge[SCRAM].JINK3_WeaponFactor / 5; }

				if(Q_Forge->Forge[SCRAM].Team != player[g_Player]->Team)
					{
					Qpo->Tex_BlitAlpha(Medias->RADspritesF[Q_Forge->Forge[SCRAM].CharDATA.Class], _->RADavatarREALRADX - (5 * _->RADavatarREALSCALE), _->RADavatarREALRADZ - (5 * _->RADavatarREALSCALE), 11 * _->RADavatarREALSCALE, 11 * _->RADavatarREALSCALE, 80.0f, 1.0f, 1.0f , 255*((float)Q_Forge->Forge[SCRAM].HB_Health/(float)Q_Forge->Forge[SCRAM].HB_MaxHealth), 255*((float)Q_Forge->Forge[SCRAM].HB_Health/(float)Q_Forge->Forge[SCRAM].HB_MaxHealth), 255*((float)Q_Forge->Forge[SCRAM].HB_Health/(float)Q_Forge->Forge[SCRAM].HB_MaxHealth));
					}
				else
					{
					Qpo->Tex_BlitAlpha(Medias->RADspritesE[Q_Forge->Forge[SCRAM].CharDATA.Class], _->RADavatarREALRADX - (5 * _->RADavatarREALSCALE), _->RADavatarREALRADZ - (5 * _->RADavatarREALSCALE), 11 * _->RADavatarREALSCALE, 11 * _->RADavatarREALSCALE, 80.0f, 1.0f, 1.0f , 255*((float)Q_Forge->Forge[SCRAM].HB_Health/(float)Q_Forge->Forge[SCRAM].HB_MaxHealth), 255*((float)Q_Forge->Forge[SCRAM].HB_Health/(float)Q_Forge->Forge[SCRAM].HB_MaxHealth), 255*((float)Q_Forge->Forge[SCRAM].HB_Health/(float)Q_Forge->Forge[SCRAM].HB_MaxHealth));
					}
				}
			SCRAM++;
			}
		}

		//### Health Bars
	/*Brushrect.xmin = 334 - ( 334 * ( (float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth ) );
	Brushrect.xmax = 334;//334 * ( (float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth );
	Brushrect.ymin = 14;
	Brushrect.ymax = 40;*/

	/*BrushVec.x = 1;
	BrushVec.y = 0;
	BrushVec.z = 0;

	BrushRGBA.red = 255;
	BrushRGBA.green = 255;
	BrushRGBA.blue = 255;
	BrushRGBA.alpha = 255;*/

	/*geEngine_DrawAlphaBitmap(Engine,
							Medias->HealthLeft,
							&BrushVec,
							NULL,			// if null, uses full screen
							&Brushrect,		// pixels in the "camera" view
							&Brushrect,			// percent of the "camera" view
							140,
							&BrushRGBA);*/

	//Qpo->Tex_Blit(Medias->HealthLeft,&Brushrect,66 + ( 334 - ( 334 * ( (float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth ) ) ),573);

	/*if((334-(334*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth))) < 263)
		{
		Qpo->Tex_BlitAlpha(Medias->HealthLeft, 66 + (334-(334*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth))), 589, 334*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), 11, 255.0f, ((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), 1.0f , 255, 255*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), 255*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth));
		Qpo->Tex_BlitAlpha(Medias->HealthLeftEXT, 329, 589, 71, 11, 255.0f, 1.0f, 1.0f , 255, 255*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), 255*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth));
		}
	else
		{
		Qpo->Tex_BlitAlpha(Medias->HealthLeft, 66 + (334-(334*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth))), 589, 334*((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), 11, 255.0f, ((float)player[g_Player]->HB_Health/(float)player[g_Player]->HB_MaxHealth), 1.0f , 255, player[g_Player]->HB_HealthUND, player[g_Player]->HB_HealthUND);
		
		if(player[g_Player]->HB_HUNDDIR == 0)
			{
			if(player[g_Player]->HB_HealthUND + 25 <= 255) player[g_Player]->HB_HealthUND += 25;
			else
				{
				player[g_Player]->HB_HealthUND = 255;
				player[g_Player]->HB_HUNDDIR = 1;
				}
			}
		else
			{
			if(player[g_Player]->HB_HealthUND - 25 >= 0) player[g_Player]->HB_HealthUND -= 25;
			else
				{
				player[g_Player]->HB_HealthUND = 0;
				player[g_Player]->HB_HUNDDIR = 0;
				}
			}
		}
	

	/*Brushrect.xmin = 0;//334 - ( 334 * ( (float)Q_Forge->Forge[0].HB_Health / (float)Q_Forge->Forge[0].HB_MaxHealth ) );
	Brushrect.xmax = 334 * ( (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth );
	Brushrect.ymin = 14;
	Brushrect.ymax = 40;*/

	/*BrushRGBA.red = 255;
	BrushRGBA.green = 255;
	BrushRGBA.blue = 255;
	BrushRGBA.alpha = 255;*/

	/*geEngine_DrawAlphaBitmap(Engine,
							Medias->HealthRight,
							&BrushVec,
							NULL,			// if null, uses full screen
							&Brushrect,		// pixels in the "camera" view
							&Brushrect,			// percent of the "camera" view
							140,
							&BrushRGBA);*/

	//Qpo->Tex_Blit( Medias->HealthRight, &Brushrect, 400, 573);

	//Qpo->Tex_BlitAlpha(Medias->HealthLeft, 400, 589, 334, 11, 220.0f, ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth), 1.0f , 255, ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth), ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth));

	/*if(player[g_Player]->HB_LastAvatarHitID >= 0)
		{
		Qpo->Tex_BlitAlpha(Medias->HealthRight, 400, 589, 334*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth), 11, 255.0f, ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth), 1.0f , 255, 255*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth), 255*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth));

		Qpo->Tex_BlitAlpha(Medias->EnergyBarRight, 490 + (244-(244*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy))), 584, 244*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy), 6, 255.0f, ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy), 1.0f , 170+(85*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy)), 100+(155*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy)), 170+(85*((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy/(float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy)));
		}
	else
		{
		Qpo->Tex_BlitAlpha(Medias->HealthRight, 400, 589, 334*((float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthBANK/(float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthMAX), 11, 255.0f, ((float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthBANK/(float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthMAX), 1.0f , 255, 255*((float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthBANK/(float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthMAX), 255*((float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthBANK/(float)Q_Object->Object[((player[g_Player]->HB_LastAvatarHitID * -1) - 1)].StrengthMAX));
		}

		//### Energy Bars
	/*Brushrect.xmin = 244 - ( 244 * ( (float)player[g_Player]->HB_Energy / (float)player[g_Player]->HB_MaxEnergy ) );
	Brushrect.xmax = 244;//334 * ( (float)player[g_Player]->HB_Energy / (float)player[g_Player]->HB_MaxEnergy );
	Brushrect.ymin = 9;
	Brushrect.ymax = 14;
	Qpo->Tex_Blit(Medias->HealthLeft,&Brushrect,66 + ( 244 - ( 244 * ( (float)player[g_Player]->HB_Energy / (float)player[g_Player]->HB_MaxEnergy ) ) ),563);

	Brushrect.xmin = 90;//334 - ( 334 * ( (float)Q_Forge->Forge[0].HB_Energy / (float)Q_Forge->Forge[0].HB_MaxEnergy ) );
	Brushrect.xmax = 244 * ( (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Energy / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxEnergy );
	Brushrect.ymin = 9;
	Brushrect.ymax = 14;
	Qpo->Tex_Blit( Medias->HealthRight, &Brushrect, 490, 563);*//*

	Qpo->Tex_BlitAlpha(Medias->EnergyBarLeft, 66, 584, 244*((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy), 6, 255.0f, ((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy), 1.0f , 170+(85*((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy)), 100+(155*((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy)), 170+(85*((float)player[g_Player]->HB_Energy/(float)player[g_Player]->HB_MaxEnergy)));



	//#### PLAYER XP Medias->MESSAGES
	if(player[g_Player]->MSG_XPON == 1)
		{
		//if(player[g_Player]->MSG_XPInit == 0)
		//	{//INIT
		//	player[g_Player]->MSG_XPInit = 1;
			player[g_Player]->MSG_TESTDigits = 0;
			player[g_Player]->MSG_NomDigits = 0;

			Q.DigitizeNumber(player[g_Player]->MSG_XpInc);
		//	}//END INIT

		if(player[g_Player]->MSG_XPScreenDIST + player[g_Player]->MSG_XPScreenDistINC < 800)
			{
			player[g_Player]->MSG_XPScreenDIST += player[g_Player]->MSG_XPScreenDistINC;

			if(player[g_Player]->MSG_XPScreenDIR == 0)
				{
				if(player[g_Player]->MSG_XPScreenDistINC - 4 > 1) player[g_Player]->MSG_XPScreenDistINC -= 4;
				else { player[g_Player]->MSG_XPScreenDIR = 1; }	//3
				}

			if(player[g_Player]->MSG_XPScreenDIR == 1)
				{ player[g_Player]->MSG_XPScreenDistINC += 0.45; }	//2

			//### DISPLAY NUMBER
			SCRAM = 0;
			while(SCRAM < player[g_Player]->MSG_NomDigits)
				{
				Brushrect.xmin = 0; Brushrect.xmax = 32; Brushrect.ymin = 0; Brushrect.ymax = 40;
				Qpo->Tex_Blit( FONT[player[g_Player]->MSG_Digit[SCRAM]], &Brushrect, player[g_Player]->MSG_XPScreenDIST + (32 * SCRAM), 450);
				SCRAM++;
				}

			//### DISPLAY Medias->MESSAGES
			Brushrect.xmin = 0; Brushrect.xmax = 72; Brushrect.ymin = 0; Brushrect.ymax = 37;
			Qpo->Tex_Blit( Medias->MESSAGES, &Brushrect, player[g_Player]->MSG_XPScreenDIST + (32 * player[g_Player]->MSG_NomDigits), 450);
			}
		else
			{
			player[g_Player]->MSG_XPON = 0;
			player[g_Player]->MSG_XPScreenDIST = 0;
			player[g_Player]->MSG_XPScreenDistINC = 50;
			player[g_Player]->MSG_XPScreenDIR = 0;
			player[g_Player]->MSG_XPInit = 0;
			}
		}


	//#### PLAYER ITEM Medias->MESSAGES
	if(player[g_Player]->MSG_ITEMON == 1)
		{
		if(player[g_Player]->MSG_ITEMInit == 0)
			{//INIT
			player[g_Player]->MSG_ITEMInit = 1;

			ItemBrushrect.xmin = 0;

			if(player[g_Player]->MSG_ItemREF.RefNUM == 0)
				{
				ItemBrushrect.xmax = 90;
				ItemBrushrect.ymin = 300;
				ItemBrushrect.ymax = 325;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 1)
				{
				ItemBrushrect.xmax = 135;
				ItemBrushrect.ymin = 80;
				ItemBrushrect.ymax = 106;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 2)
				{
				ItemBrushrect.xmax = 130;
				ItemBrushrect.ymin = 133;
				ItemBrushrect.ymax = 159;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 3)
				{
				ItemBrushrect.xmax = 300;
				ItemBrushrect.ymin = 159;
				ItemBrushrect.ymax = 188;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 4)   //MINIGUN
				{
				ItemBrushrect.xmax = 160;
				ItemBrushrect.ymin = 325;
				ItemBrushrect.ymax = 354;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 5)
				{
				ItemBrushrect.xmax = 90;
				ItemBrushrect.ymin = 188;
				ItemBrushrect.ymax = 215;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 6)
				{
				ItemBrushrect.xmax = 145;
				ItemBrushrect.ymin = 106;
				ItemBrushrect.ymax = 133;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 7)	//AK47
				{
				ItemBrushrect.xmax = 96;
				ItemBrushrect.ymin = 354;
				ItemBrushrect.ymax = 380;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 8)	//PSG
				{
				ItemBrushrect.xmax = 102;
				ItemBrushrect.ymin = 380;
				ItemBrushrect.ymax = 408;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 9) //SPAS
				{
				ItemBrushrect.xmax = 132;
				ItemBrushrect.ymin = 408;
				ItemBrushrect.ymax = 436;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 10) //G3
				{
				ItemBrushrect.xmax = 52;
				ItemBrushrect.ymin = 436;
				ItemBrushrect.ymax = 464;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 11) //l96a1low
				{
				ItemBrushrect.xmax = 94;
				ItemBrushrect.ymin = 464;
				ItemBrushrect.ymax = 492;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 12) //awphighq
				{
				ItemBrushrect.xmax = 82;
				ItemBrushrect.ymin = 492;
				ItemBrushrect.ymax = 520;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 101)
				{
				ItemBrushrect.xmax = 225;
				ItemBrushrect.ymin = 215;
				ItemBrushrect.ymax = 243;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 102)
				{
				ItemBrushrect.xmax = 235;
				ItemBrushrect.ymin = 243;
				ItemBrushrect.ymax = 274;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 103)
				{
				ItemBrushrect.xmax = 240;
				ItemBrushrect.ymin = 274;
				ItemBrushrect.ymax = 300;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 121)	//mech
				{
				ItemBrushrect.xmax = 110;
				ItemBrushrect.ymin = 520;
				ItemBrushrect.ymax = 548;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 120)	//Vehicle
				{
				ItemBrushrect.xmax = 140;
				ItemBrushrect.ymin = 548;
				ItemBrushrect.ymax = 579;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 150)	//Zcapture
				{
				ItemBrushrect.xmax = 170;
				ItemBrushrect.ymin = 579;
				ItemBrushrect.ymax = 611;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 151)	//Zmine
				{
				ItemBrushrect.xmax = 120;
				ItemBrushrect.ymin = 611;
				ItemBrushrect.ymax = 640;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 152)	//Zmine
				{
				ItemBrushrect.xmax = 145;
				ItemBrushrect.ymin = 640;
				ItemBrushrect.ymax = 675;
				}

			if(player[g_Player]->MSG_ItemREF.RefNUM == 153)	//ZAnomaly
				{
				ItemBrushrect.xmax = 180;
				ItemBrushrect.ymin = 675;
				ItemBrushrect.ymax = 710;
				}

			}//END INIT

		if(player[g_Player]->MSG_ITEMScreenDIST + player[g_Player]->MSG_ITEMScreenDistINC > 0)
			{
			player[g_Player]->MSG_ITEMScreenDIST -= player[g_Player]->MSG_ITEMScreenDistINC;

			if(player[g_Player]->MSG_ITEMScreenDIR == 0)
				{
				if(player[g_Player]->MSG_ITEMScreenDistINC - 0.23 > 1) player[g_Player]->MSG_ITEMScreenDistINC -= 0.23;
				else { player[g_Player]->MSG_ITEMScreenDIR = 1; }
				}

			if(player[g_Player]->MSG_ITEMScreenDIR == 1)
				{ player[g_Player]->MSG_ITEMScreenDistINC += 0.09; }

			//### DISPLAY THE WORD ITEM
			Brushrect.xmin = 0; Brushrect.xmax = 150; Brushrect.ymin = 40; Brushrect.ymax = 80;
			Qpo->Tex_Blit( Medias->MESSAGES, &Brushrect, player[g_Player]->MSG_ITEMScreenDIST, 500);

			//### DISPLAY ITEM MESSAGE
			Qpo->Tex_Blit( Medias->MESSAGES, &ItemBrushrect, player[g_Player]->MSG_ITEMScreenDIST + 150, 510);

			//##### QUALITY
			player[g_Player]->MSG_TESTDigits = 0;
			player[g_Player]->MSG_NomDigits = 0;

			if(player[g_Player]->MSG_ItemREF.Quality > 0 && player[g_Player]->MSG_ItemREF.Quality <= 0.1) player[g_Player]->MSG_ItemQUAL = 1;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.1 && player[g_Player]->MSG_ItemREF.Quality <= 0.2) player[g_Player]->MSG_ItemQUAL = 2;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.2 && player[g_Player]->MSG_ItemREF.Quality <= 0.3) player[g_Player]->MSG_ItemQUAL = 3;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.3 && player[g_Player]->MSG_ItemREF.Quality <= 0.4) player[g_Player]->MSG_ItemQUAL = 4;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.4 && player[g_Player]->MSG_ItemREF.Quality <= 0.5) player[g_Player]->MSG_ItemQUAL = 5;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.5 && player[g_Player]->MSG_ItemREF.Quality <= 0.6) player[g_Player]->MSG_ItemQUAL = 6;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.6 && player[g_Player]->MSG_ItemREF.Quality <= 0.7) player[g_Player]->MSG_ItemQUAL = 7;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.7 && player[g_Player]->MSG_ItemREF.Quality <= 0.8) player[g_Player]->MSG_ItemQUAL = 8;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.8 && player[g_Player]->MSG_ItemREF.Quality <= 0.9) player[g_Player]->MSG_ItemQUAL = 9;
			if(player[g_Player]->MSG_ItemREF.Quality > 0.9 && player[g_Player]->MSG_ItemREF.Quality <= 1) player[g_Player]->MSG_ItemQUAL = 10;

			Q.DigitizeNumber(player[g_Player]->MSG_ItemQUAL);

			//### DISPLAY THE WORD QUALITY
			Brushrect.xmin = 154; Brushrect.xmax = 250; Brushrect.ymin = 60; Brushrect.ymax = 80;
			Qpo->Tex_Blit( Medias->MESSAGES, &Brushrect, player[g_Player]->MSG_ITEMScreenDIST + 150, 550);

			//### DISPLAY NUMBER
			SCRAM = 0;
			while(SCRAM < player[g_Player]->MSG_NomDigits)
				{
				Brushrect.xmin = 0; Brushrect.xmax = 32; Brushrect.ymin = 0; Brushrect.ymax = 40;
				Qpo->Tex_Blit( FONT[player[g_Player]->MSG_Digit[SCRAM]], &Brushrect, player[g_Player]->MSG_ITEMScreenDIST + (255 + (32 * SCRAM)), 550);
				SCRAM++;
				}
			}
		else
			{
			player[g_Player]->MSG_ITEMON = 0;
			player[g_Player]->MSG_ITEMScreenDIST = 0;
			player[g_Player]->MSG_ITEMScreenDistINC = 17;
			player[g_Player]->MSG_ITEMScreenDIR = 0;
			player[g_Player]->MSG_ITEMInit = 0;
			}
		}


	//## Knock Out Bitmap
	if(_->KnockOutFLAG == 1)
		{
		//#### Initialise Particles ####//
		/*jet=0;
		while(jet < 5 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
			{
			Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
			Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
			Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;
			Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 4;

			Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
			Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
			Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

			Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
			Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 7;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->ViewXForm.Translation;

			Qpo->Transform_GetIn(&player[g_Player]->ViewXForm, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

			Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x += (((float)rand() / 32767)-0.5)*0.2;
			Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y += (((float)rand() / 32767)-0.5)*0.2;
			Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z += (((float)rand() / 32767)-0.5)*0.2;

			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

			Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

			_->NomPntSprite++;
			jet++;
			}*//*

		Qpo->Tex_BlitAlpha(Medias->KObit[_->KnockOutCNT], 0, 125+((350-_->KnockOutHEIGHT)/2), 800, _->KnockOutHEIGHT, 255.0f, 1.0f, 1.0f,255,255,255);

		_->KnockOutTIMER++;

		if(_->KnockOutINIT == 0)
			{
			if(_->KnockOutHEIGHT + 45 < 350) _->KnockOutHEIGHT += 45;
			else _->KnockOutHEIGHT = 350;

			if(_->KnockOutTIMER > 5)
				{
				_->KnockOutCNT++;
				_->KnockOutINIT = 1;
				_->KnockOutTIMER = 0;
				}
			}
		else
			{
			if(_->KnockOutINIT == 1)
				{
				if(_->KnockOutTIMER >= 10)
					{
					_->KnockOutCNT++;
					_->KnockOutINIT = 2;
					_->KnockOutTIMER = 0;
					}
				}

			if(_->KnockOutINIT == 2)
				{
				if(_->KnockOutHEIGHT - 25 > 0) _->KnockOutHEIGHT -= 25;
				else
					{
					_->KnockOutHEIGHT = 0;
					_->KnockOutCNT = 0;
					_->KnockOutFLAG = 0;
					_->KnockOutINIT = 0;
					}

				_->KnockOutTIMER = 0;
				_->KnockOutCNT++;
				if(_->KnockOutCNT > 11) _->KnockOutCNT = 11;
				}
			}
		}

	//## Health Reduction

	if(player[g_Player]->HB_HReduceON == 1)
		{
		//# Create Energy Loss Rect

		//player[g_Player]->HB_ReduceRect.xmin = 334 - ( 334 * ( (float)player[g_Player]->HB_ReduceOld / (float)player[g_Player]->HB_MaxHealth ) );
		if(player[g_Player]->HB_ReduceHInc >= 0) player[g_Player]->HB_ReduceRect.xmin = (334 - (334 * ((float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth))) - (( (334 - (334 * ((float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth))) - (334 - (334 * ((float)player[g_Player]->HB_ReduceOld / (float)player[g_Player]->HB_MaxHealth))) ) * (player[g_Player]->HB_ReduceHInc/10) );
		else player[g_Player]->HB_ReduceRect.xmin = 334 - (334 * ((float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth));

		player[g_Player]->HB_ReduceRect.xmax = 334 - (334 * ((float)player[g_Player]->HB_Health / (float)player[g_Player]->HB_MaxHealth));
		player[g_Player]->HB_ReduceRect.ymin = 14;
		player[g_Player]->HB_ReduceRect.ymax = 40;

		player[g_Player]->HB_ReduceRectFill.xmin = 66 + player[g_Player]->HB_ReduceRect.xmin;
		player[g_Player]->HB_ReduceRectFill.xmax = 66 + player[g_Player]->HB_ReduceRect.xmax;
		player[g_Player]->HB_ReduceRectFill.ymin = 573 - ( player[g_Player]->HB_ReduceHInc * 4 );	//* 2
		player[g_Player]->HB_ReduceRectFill.ymax = 600;

		if(player[g_Player]->HB_ReduceRectFill.ymin > 600) player[g_Player]->HB_HReduceON = 0;


		Qpo->Draw_FillRect(&player[g_Player]->HB_ReduceRectFill, &player[g_Player]->HB_ReduceRectColor);

		player[g_Player]->HB_ReduceRectColor.alpha -= 10;


		player[g_Player]->HB_ReduceHInc -= 0.7;
		player[g_Player]->HB_ReduceHeight -= (float)player[g_Player]->HB_ReduceHInc;

		if(player[g_Player]->HB_ReduceHeight < 600) Qpo->Tex_Blit(Medias->HealthLeft,&player[g_Player]->HB_ReduceRect, 67 + player[g_Player]->HB_ReduceRect.xmin , player[g_Player]->HB_ReduceHeight);
		}


	if(Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_HReduceON == 1)
		{
		//# Create Energy Loss Rect

		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmin = 334 * ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth);

		//Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmax = 334 * ( (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceOld / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth );

		if(Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHInc >= 0) Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmax = (334 * ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth)) + (( (334 * ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceOld / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth)) - (334 * ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth)) ) * (Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHInc/10) );
		else Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmax = (334 * ((float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_Health / (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_MaxHealth));

		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.ymin = 14;
		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.ymax = 40;

		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectFill.xmin = 400 + Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmin;
		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectFill.xmax = 400 + Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmax;
		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectFill.ymin = 573 - ( Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHInc * 4 );	// * 2
		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectFill.ymax = 600;

		if(Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectFill.ymin > 600) Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_HReduceON = 0;


		if(Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectColor.alpha >= 0) Qpo->Draw_FillRect(&Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectFill, &Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectColor);
		else Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_HReduceON = 0;

		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRectColor.alpha -= 10;


		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHInc -= 0.7;
		Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHeight -= (float)Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHInc;

		if(Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHeight < 600) Qpo->Tex_Blit(Medias->HealthRight,&Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect, 401 + Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceRect.xmin , Q_Forge->Forge[player[g_Player]->HB_LastAvatarHitID].HB_ReduceHeight);
		}
	

	if(player[g_Player]->Q_Jink.Live == 1 && player[g_Player]->Q_Jink.FaceWidth < 580)
		{
		//Qpo->Tex_BlitAlpha(Face, 0, 600-player[g_Player]->Q_Jink.FaceHeight, player[g_Player]->Q_Jink.FaceWidth, player[g_Player]->Q_Jink.FaceHeight, 300-(player[g_Player]->Q_Jink.FaceWidth/2), 1.0f, 1.0f);
		}	//FROZEN LOOKS BAD


		//Scanner

	if(player[g_Player]->Scan == 1)
		{
		Qpo->Tex_BlitAlpha(Scanner, 0, player[g_Player]->ScanBitHeight, 800, 600, player[g_Player]->ScanBitAlpha, 1.0f, 1.0f,255,255,255);
		}*/

	// End Frame
#endif

// AVATAR AI RESPAWN LIVES *********************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1 && Q_Forge->Forge[SCRAM].HB_Dead == 1)
			{
			if(Q_Forge->Forge[SCRAM].Aposestate != 30)
				{
				Q_Forge->Forge[SCRAM].Aposestate = 30;
				Q_Forge->Forge[SCRAM].attackon = 1;
				//Q_Forge->Forge[SCRAM].attposecnt = 0;
				//Q_Forge->Forge[SCRAM].astackcnt = 0;
				//Q_Forge->Forge[SCRAM].astackrun = 0;
				}

			if(Q_Forge->Forge[SCRAM].HB_DeadTimer <= 0)
				{
				if(Q_Forge->Forge[SCRAM].HB_LiveResetSW == 1)
					{
					Q_Forge->Forge[SCRAM].HB_LiveResetSW = 0;

					if(Q_Forge->Forge[SCRAM].HB_Lives > 0)
						{
						///RESPAWN AVATAR///
						Q_Forge->Forge[SCRAM].HB_Lives--;

						acRespawnAvatar(SCRAM);
						}
					}
				}
			}

		SCRAM++;
		}


//**********************************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

	//Reset mouse clicks and Key Logger
	#pragma message("externalize mouse limbs")
	// convert to limbs

	_->lbutton[g_Player]=0;
	_->rbutton[g_Player]=0;
	_->mbutton[g_Player]=0;
	_->mwheelroll[g_Player]=0;
};

void QActiveFramewrk::acNetFrame(void)
{
#if 0
	if(m_NetStart)
		{
		//SDL_mutexP(m_mutex_State);
#if 1
		if(m_PacketPump.m_PP_STATE >= 4)
			{
			m_PacketStack.m_SendWait++;
			if(m_PacketStack.m_SendWait >= 10)
				{
				m_PacketStack.m_SendWait = 0;

				//SDL_mutexP(m_mutex_Packet);

				//*QNetwork.m_transfer = new BitTransfer(ID_CLIENT_WORLD);
				//*QNetwork.TransmitWorld(RakNet::GetTime(), m_PacketPump.m_ClientAvatarID);

				//*m_PacketStack.m_unPeer->Send((const char*)QNetwork.m_transfer->m_Data, QNetwork.m_transfer->acSize(), HIGH_PRIORITY, RELIABLE_ORDERED, 0, serveAddress, false);

				//printf("SEND to SERVER ::: ID_CLIENT_WORLD\n");
				//SDL_mutexV(m_mutex_Packet);
				}
			}
#endif
		//SDL_mutexV(m_mutex_State);

#ifdef QAMOD_ARENA
		if(g_optionsresult == 2 || g_optionsresult == 3)
			{
			helly=0;
			while(helly < _->NomAI)
				{
				if(Q_Forge->Forge[helly].LIVE == 1)
					{
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x > 5000) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x = 5000;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y > 5000) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y = 5000;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z > 5000) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z = 5000;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x < -5000) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x = -5000;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y < -5000) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y = -5000;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z < -5000) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z = -5000;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.x > 5000) Q_Forge->Forge[helly].AV.Xform.Translation.x = 5000;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.y > 5000) Q_Forge->Forge[helly].AV.Xform.Translation.y = 5000;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.z > 5000) Q_Forge->Forge[helly].AV.Xform.Translation.z = 5000;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.x < -5000) Q_Forge->Forge[helly].AV.Xform.Translation.x = -5000;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.y < -5000) Q_Forge->Forge[helly].AV.Xform.Translation.y = -5000;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.z < -5000) Q_Forge->Forge[helly].AV.Xform.Translation.z = -5000;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x != Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x = 0;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y != Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y = 0;
					if(Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z != Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z) Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z = 0;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.x != Q_Forge->Forge[helly].AV.Xform.Translation.x) Q_Forge->Forge[helly].AV.Xform.Translation.x = 0;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.y != Q_Forge->Forge[helly].AV.Xform.Translation.y) Q_Forge->Forge[helly].AV.Xform.Translation.y = 0;
					if(Q_Forge->Forge[helly].AV.Xform.Translation.z != Q_Forge->Forge[helly].AV.Xform.Translation.z) Q_Forge->Forge[helly].AV.Xform.Translation.z = 0;
					Q_Forge->Forge[helly].AV.Xform.Translation.x += (Q_Forge->Forge[helly].AV.Xform.GhostTranslation.x - Q_Forge->Forge[helly].AV.Xform.Translation.x) / 10;
					Q_Forge->Forge[helly].AV.Xform.Translation.y += (Q_Forge->Forge[helly].AV.Xform.GhostTranslation.y - Q_Forge->Forge[helly].AV.Xform.Translation.y) / 10;
					Q_Forge->Forge[helly].AV.Xform.Translation.z += (Q_Forge->Forge[helly].AV.Xform.GhostTranslation.z - Q_Forge->Forge[helly].AV.Xform.Translation.z) / 10;
					}

				helly++;
				}
			}
#endif
		}
#endif
}

/////// STATIC INLINE //////

void QActiveFramewrk::acGenerateDataMesh(const char *f_Filename)
{
	//*unDataMesh *f_mesh = new unDataMesh();

	//*printf("Begin:::unDataMesh %i\n", m_NomDataMesh);

	//*if(!f_mesh->acCreate(f_Filename))
	//*	{
	//*	std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
	//*	while(1) { /* Infinite Loop */ }// return -1;
	//*	}

	//*if(!f_mesh->acInit(m_NomDataMesh))
	//*	{
	//*	std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
	//*	while(1) { /* Infinite Loop */ }// return -1;
	//*	}

	//*m_NomDataMesh = f_mesh->acMake();

	//*meshTemplates.push_back(f_mesh);
};

void QActiveFramewrk::acGenerateDataBodyMesh(const char *f_Filename)
{
	//*digiDataMesh *f_mesh = new digiDataMesh();

	printf("Begin:::digiDataMesh %i\n", m_NomDataMesh);

	//*if(!f_mesh->acCreate(f_Filename))
	//*	{
	//*	std::cerr << "ERROR::: unMesh ::: Failed to load" << std::endl;
	//*	while(1) { /* Infinite Loop */ }// return -1;
	//*	}

	//*if(!f_mesh->acInit(m_NomDataMesh))
	//*	{
	//*	std::cerr << "ERROR::: unMesh ::: Initialization failed." << std::endl;
	//*	while(1) { /* Infinite Loop */ }// return -1;
	//*	}

	//*m_NomDataMesh = f_mesh->acMake();

	//*bodymeshTemplates.push_back(f_mesh);
};

bool QActiveFramewrk::acSpawnAvatar(int f_Index, int f_CharID, int f_BDataID, int f_Team, QpoVec3d f_Position, int f_BoneStructure, int f_SpawnPnt, bool level)
{

	int f_NOMAI = QNOMAI;

	if(level)
		{
		f_NOMAI = QNOMAI;
		}
	else
		{
		f_NOMAI = 405;
		}
		

#if 0
	bool f_IncNomAI = true;
	if(_->NomAI >= f_NOMAI)
		{
		int f_Count = 0;
		bool f_Live = true;
		while(f_Live)
			{
			if(Q_Forge->Forge[f_Count].LIVE == 0 || (Q_Forge->Forge[f_Count].HB_Dead == 1 /*&& Q_Forge->Forge[f_Count].HB_DeadTimer <= 0/* && Q_Forge->Forge[f_Count].HB_Lives > 0*/)) f_Live = false;
			else f_Count++;
			if(f_Count >= f_NOMAI) return false;
			}

		f_Index = f_Count;
		f_IncNomAI = false;

		delete Q_Forge->Forge[f_Index].AV.Avatar.Mesh;

		aero = 0;
		while (aero <= 2)
			{
			aero++;

			delete Q_Forge->Forge[f_Index].Shadows[aero].Avatar.Mesh;
			}
		}
	else
		{
		f_Index = _->NomAI;
		f_IncNomAI = true;
		}
#endif

	f_Index = _->NomAI;
	bool f_IncNomAI = true;

	if(f_Index >= f_NOMAI) return false;

#if 0
	m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_ForgeAVID.push_back(f_Index);
#endif

	Q_Forge->Forge[f_Index].HB_DeadTimer = 500;
	Q_Forge->Forge[f_Index].HB_Lives = 0;
	Q_Forge->Forge[f_Index].HB_LiveResetSW = 1;

	Q_Forge->Forge[f_Index].NetplayerFLAG = 0;

	Q_Forge->Forge[f_Index].AV.upspeed = -15;
	Q_Forge->Forge[f_Index].AV.Mins.x = -25.f;
	Q_Forge->Forge[f_Index].AV.Mins.y = -45.f;
	Q_Forge->Forge[f_Index].AV.Mins.z = -25.f;
	Q_Forge->Forge[f_Index].AV.Maxs.x = 25.f;
	Q_Forge->Forge[f_Index].AV.Maxs.y = 45.f;
	Q_Forge->Forge[f_Index].AV.Maxs.z = 25.f;

	Q_Forge->Forge[f_Index].PlayerSpeed = PLAYER_SPEED;

	Q_Forge->Forge[f_Index].GravityAlter = 1;

	//Fill Weapon Ammo
	Q_Forge->Forge[f_Index].WeaponAmmo = 32;

	Q_Forge->Forge[f_Index].HB_Illumination = 255;
	Q_Forge->Forge[f_Index].HB_Dead = 0;
	Q_Forge->Forge[f_Index].HB_KillerTeam = 0;

	//Body and Mind
	Q_Forge->Forge[f_Index].Q_Heart.HeartIncrement = 0;
	Q_Forge->Forge[f_Index].Q_Heart.PulseRate = 1;
	Q_Forge->Forge[f_Index].Q_Brain.Aggression = 70;

	//###### AVATAR SELECTION
	//### Obtain Correct Character Data for Avatar
	Q_Forge->Forge[f_Index].CharDATA = player[g_Player]->BFO.CharDATA[f_CharID];

	Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.ANGELEDITFLAG = 1;

	for(int f_mapa = 0; f_mapa < 38; f_mapa++)
		{
		Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.RED[f_mapa] = 255;
		Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.GREEN[f_mapa] = 255;
		Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.BLUE[f_mapa] = 255;
		}

#if 0
	if(f_BDataID == 0 ||
	   f_BDataID == 1 ||
	   f_BDataID == 2 ||
	   f_BDataID == 9 ||
	   f_BDataID == 10)
		{
		if(m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_Team == 0)
			{
			for(int f_map = 0; f_map < 38; f_map++)
				{
				if(f_map != 2 && f_map != 3 && f_map != 4 && f_map != 5 && f_map != 6 && f_map != 7 && f_map != 8 && f_map != 9 && f_map != 10 && f_map != 11 &&
				   f_map != 17 && f_map != 19 && f_map != 20 && f_map != 21 && f_map != 22 && f_map != 23 && f_map != 28 && f_map != 29 && f_map != 30 && f_map != 31)
					{
					Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.RED[f_map] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[f_map];
					Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.GREEN[f_map] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[f_map];
					Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.BLUE[f_map] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO
						.CurrCHAR].AngelCOLOURS.BLUE[f_map];
					}
				}

			}
		else

			
		
		
		{
			for(int f_map = 0; f_map < 38; f_map++)
				{
				if(f_map != 2 && f_map != 3 && f_map != 4 && f_map != 5 && f_map != 6 && f_map != 7 && f_map != 8 && f_map != 9 && f_map != 10 && f_map != 11 &&
				   f_map != 17 && f_map != 19 && f_map != 20 && f_map != 21 && f_map != 22 && f_map != 23 && f_map != 28 && f_map != 29 && f_map != 30 && f_map != 31)
					{
					Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.RED[f_map] = m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_TeamColorsRED[f_map];
					Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.GREEN[f_map] = m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_TeamColorsGREEN[f_map];
					Q_Forge->Forge[f_Index].CharDATA.AngelCOLOURS.BLUE[f_map] = m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_TeamColorsBLUE[f_map];
					}
				}
			}
		}
#endif

	if(f_BDataID > 10) f_BDataID = 10;

	Q_Forge->Forge[f_Index].CharDATA.CDataID = f_CharID;
	Q_Forge->Forge[f_Index].CharDATA.BDataID = f_BDataID;
	Q_Forge->Forge[f_Index].CharDATA.TEAM = f_Team;
	Q_Forge->Forge[f_Index].Team = f_Team;
	Q_Forge->Forge[f_Index].AVDATID = f_Index;
	player[g_Player]->BFO.AVATARDATA[f_Index].AVATARID = f_Index;
	
	//#### Set Role
	Q_Forge->Forge[f_Index].Role = 0;
	Q_Forge->Forge[f_Index].Rank = 1;
	Q_Forge->Forge[f_Index].LEVEL = Q_Forge->Forge[f_Index].CharDATA.Level;

	#pragma message ("FIXME:::Start AI Start Position and initial pose")
	Q_Forge->Forge[f_Index].AV.Avatar.Mesh = new unAvatar();

	if(Q_Forge->Forge[f_Index].CharDATA.AvatarREF > 11 || Q_Forge->Forge[f_Index].CharDATA.AvatarREF < 0) Q_Forge->Forge[f_Index].CharDATA.AvatarREF = 0;

	Q_Forge->Forge[f_Index].CharDATA.AvatarREF = f_BDataID;
#if 0
	meshShellTemplates[Q_Forge->Forge[f_Index].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[f_Index].AV.Avatar.Mesh, Q_Forge->Forge[helly].CharDATA.BDataID);
#else
	meshBank[f_BDataID]->clone_struct_physics(Q_Forge->Forge[f_Index].AV.Avatar.Mesh);
#endif

#if 0
	if(f_BoneStructure > 0) Q_Forge->Forge[f_Index].AV.Avatar.Mesh->m_BoneStructure = f_BoneStructure;
#endif

#if 0
	QpoActor_SetScale(Q_Forge->Forge[f_Index].AV.Avatar, Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

	Q_Forge->Forge[f_Index].idlespeed = 0.1;

	if(Q_Forge->Forge[f_Index].LEVEL > 1000) Q_Forge->Forge[f_Index].LEVELFactor = 1;
	else Q_Forge->Forge[f_Index].LEVELFactor = (((float)Q_Forge->Forge[f_Index].LEVEL + 1) / 1000);

	Q_Forge->Forge[f_Index].HB_MaxHealth = 1000 * (((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
	Q_Forge->Forge[f_Index].HB_Health = Q_Forge->Forge[f_Index].HB_MaxHealth;

	Q_Forge->Forge[f_Index].HB_MaxEnergy = 500;
	Q_Forge->Forge[f_Index].HB_Energy = Q_Forge->Forge[f_Index].HB_MaxEnergy;

	Q_Forge->Forge[f_Index].HB_Armour = ((float)(Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	Q_Forge->Forge[f_Index].HB_MaxArmour = ((float)(Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	Q_Forge->Forge[f_Index].JINK3_PowerFactor = 1;

	Q_Forge->Forge[f_Index].KL_Timer = 0;
	Q_Forge->Forge[f_Index].KL_BTimer = 0;

	Q_Forge->Forge[f_Index].WeaponStatus = 0;

	//#### RESET SPELLS
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[0].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[1].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[2].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[3].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[4].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[5].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[6].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[7].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[8].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[9].LIVE = 0;

	//####### RELATIVE ATTACK SPEED
	Q_Forge->Forge[f_Index].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[f_Index].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[f_Index].CharDATA.BodySKILL.EnergyEff / 6000);

	Q_Forge->Forge[f_Index].AV.Avatar.Visible = true;

	Q_Forge->Forge[f_Index].AV.Avatar.IDflag = f_Index;

	Qpo->Avatar_SetLighting(&Q_Forge->Forge[f_Index].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);

	//### Load Player Weapon
	Q_Forge->Forge[f_Index].Weapon.Avatar = 1;

	Q_Forge->Forge[f_Index].Weapon.Scale.x = 1;
	Q_Forge->Forge[f_Index].Weapon.Scale.y = 1;
	Q_Forge->Forge[f_Index].Weapon.Scale.z = 1;

	Q_Forge->Forge[f_Index].Weapon.Mins.x = -20.f;
	Q_Forge->Forge[f_Index].Weapon.Mins.y = -20.f;
	Q_Forge->Forge[f_Index].Weapon.Mins.z = -20.f;
	Q_Forge->Forge[f_Index].Weapon.Maxs.x = 20.f;
	Q_Forge->Forge[f_Index].Weapon.Maxs.y = 20.f;
	Q_Forge->Forge[f_Index].Weapon.Maxs.z = 20.f;

	Q_Forge->Forge[f_Index].Weapon.Mins.x = -20.f;
	Q_Forge->Forge[f_Index].Weapon.Mins.y = -20.f;
	Q_Forge->Forge[f_Index].Weapon.Mins.z = -20.f;
	Q_Forge->Forge[f_Index].Weapon.Maxs.x = 20.f;
	Q_Forge->Forge[f_Index].Weapon.Maxs.y = 20.f;
	Q_Forge->Forge[f_Index].Weapon.Maxs.z = 20.f;

	Q_Forge->Forge[f_Index].Weapon.Visible = true;

	Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[f_Index].Weapon.Xform.Translation);

	Qpo->Mesh_SetAlpha(&Q_Forge->Forge[f_Index].Weapon, 0);

	Q_Forge->Forge[f_Index].WeaponDISPLAY = 0;

	if(Q_Forge->Forge[f_Index].CharDATA.Class == 2)
		{
		Q_Forge->Forge[f_Index].Shield.Mins.x = -500.f;
		Q_Forge->Forge[f_Index].Shield.Mins.y = -500.f;
		Q_Forge->Forge[f_Index].Shield.Mins.z = -500.f;
		Q_Forge->Forge[f_Index].Shield.Maxs.x = 500.f;
		Q_Forge->Forge[f_Index].Shield.Maxs.y = 500.f;
		Q_Forge->Forge[f_Index].Shield.Maxs.z = 500.f;

		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[f_Index].Shield.Avatar, 40);

		fogbox.Min.x = Q_Forge->Forge[f_Index].Shield.Mins.x;
		fogbox.Min.y = Q_Forge->Forge[f_Index].Shield.Mins.y;
		fogbox.Min.z = Q_Forge->Forge[f_Index].Shield.Mins.z;
		fogbox.Max.x = Q_Forge->Forge[f_Index].Shield.Maxs.x;
		fogbox.Max.y = Q_Forge->Forge[f_Index].Shield.Maxs.y;
		fogbox.Max.z = Q_Forge->Forge[f_Index].Shield.Maxs.z;

		Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[f_Index].Shield.Xform.Translation);

		Q_Forge->Forge[f_Index].Shield.Avatar.IDflag = 251;
		}

	Qpo->Avatar_SetScale(&Q_Forge->Forge[f_Index].AV.Avatar, Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

	//### Load Fighter Shadows
	Q_Forge->Forge[f_Index].ShadowsOn = false;
	Q_Forge->Forge[f_Index].ShadowALPHA = 240;

	aero = 0;
	while(aero <= 2)
		{
		aero++;

		Q_Forge->Forge[f_Index].Shadows[aero].Avatar.Mesh = new unAvatar();

		if(Q_Forge->Forge[f_Index].CharDATA.ShadowREF > 11 || Q_Forge->Forge[f_Index].CharDATA.ShadowREF < 0) Q_Forge->Forge[f_Index].CharDATA.ShadowREF = 0;

		Q_Forge->Forge[f_Index].CharDATA.ShadowREF = f_BDataID;

#if 0
		meshShellTemplates[Q_Forge->Forge[f_Index].CharDATA.ShadowREF]->clone_struct(Q_Forge->Forge[f_Index].Shadows[aero].Avatar.Mesh);
#else
		meshBank[f_BDataID]->clone_struct_physics(Q_Forge->Forge[f_Index].Shadows[aero].Avatar.Mesh);
#endif

		Q_Forge->Forge[f_Index].Shadows[aero].Xform.Translation.x = 0;
		Q_Forge->Forge[f_Index].Shadows[aero].Xform.Translation.y = 0;
		Q_Forge->Forge[f_Index].Shadows[aero].Xform.Translation.z = 0;

		Q_Forge->Forge[f_Index].Shadows[aero].Mins.x = -20.f;
		Q_Forge->Forge[f_Index].Shadows[aero].Mins.y = -20.f;
		Q_Forge->Forge[f_Index].Shadows[aero].Mins.z = -20.f;
		Q_Forge->Forge[f_Index].Shadows[aero].Maxs.x = 20.f;
		Q_Forge->Forge[f_Index].Shadows[aero].Maxs.y = 20.f;
		Q_Forge->Forge[f_Index].Shadows[aero].Maxs.z = 20.f;

#if 0
		QpoActor_SetScale(Q_Forge->Forge[f_Index].Shadows[aero].Avatar, Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

		Q_Forge->Forge[f_Index].Shadows[aero].Avatar.Visible = true;

		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[f_Index].Shadows[aero].Avatar, 255/(aero+1));

		Q_Forge->Forge[f_Index].Shadows[aero].Avatar.IDflag = f_Index;
		}

	//#### Set Up Trail Flags
	Q_Forge->Forge[f_Index].TrailFadeSpan[0][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[1][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[2][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[3][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[4][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[5][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[6][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[7][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[8][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[9][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[0][1] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[1][1] = 1;
	Q_Forge->Forge[f_Index].TrailFadeSpan[2][1] = 2;
	Q_Forge->Forge[f_Index].TrailFadeSpan[3][1] = 3;
	Q_Forge->Forge[f_Index].TrailFadeSpan[4][1] = 4;
	Q_Forge->Forge[f_Index].TrailFadeSpan[5][1] = 5;
	Q_Forge->Forge[f_Index].TrailFadeSpan[6][1] = 6;
	Q_Forge->Forge[f_Index].TrailFadeSpan[7][1] = 7;
	Q_Forge->Forge[f_Index].TrailFadeSpan[8][1] = 8;
	Q_Forge->Forge[f_Index].TrailFadeSpan[9][1] = 9;

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItemsAI(f_Index);

	//##### Starting position
	/*Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0;
	Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI);
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&Q_Forge->Forge[f_Index].Xform, Ange.x);
	Qpo->Transform_RotateY(&Q_Forge->Forge[f_Index].Xform, Ange.y);
	Qpo->Transform_RotateZ(&Q_Forge->Forge[f_Index].Xform, Ange.z);*/

	//Starting Rotation
	Ange.y = PI;
	if(Ange.y > (2 * PI)) Ange.y = Ange.y - (PI * 2);
	Ange.x = -(PI / 2);
	Ange.z = 0.0f;

	// Set the actor's angle
	if(f_IncNomAI == true)
		{
		Q_Forge->Forge[f_Index].AV.Xform.Matrix.load_identity();
		Qpo->Transform_RotateX(&Q_Forge->Forge[f_Index].AV.Xform, Ange.x);		//Update Avatar's starting facing direction
		Qpo->Transform_RotateY(&Q_Forge->Forge[f_Index].AV.Xform, Ange.y);
		Qpo->Transform_RotateZ(&Q_Forge->Forge[f_Index].AV.Xform, Ange.z);
		}

	Q_Forge->Forge[f_Index].STOREMatrix = Q_Forge->Forge[f_Index].Xform;

#if 0
	m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_RotationVec.y = 0;

	//Begin Transforming for Camera
	Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[f_Index].AV.Xform, &Q_Forge->Forge[f_Index].AV.Up);

	Qpo->Vec3d_Subtract(&Q_Forge->Forge[f_Index].AV.Up, &m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_RotationVec, &ScanTurnVec);
	Q_Forge->Forge[f_Index].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);

	//### Check Distance between Pure Left and Right to work out direction of Turn
	Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[f_Index].AV.Xform, &Q_Forge->Forge[f_Index].AV.Left);

	Qpo->Vec3d_Copy(&Q_Forge->Forge[f_Index].AV.Left, &Q_Forge->Forge[f_Index].AV.Right);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[f_Index].AV.Right);

	ScanDistL = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_RotationVec, &Q_Forge->Forge[f_Index].AV.Left);
	ScanDistR = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[f_SpawnPnt]->m_RotationVec, &Q_Forge->Forge[f_Index].AV.Right);

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 0.0f);	//RED
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Left.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Left.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Left.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Right.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Right.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Right.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].ScanVecTo.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].ScanVecTo.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].ScanVecTo.z * 250));
	//*glEnd();
#endif

	if(ScanDistL < ScanDistR) Q_Forge->Forge[f_Index].ScanTurnAng *= -1;

	Q_Forge->Forge[f_Index].trueAngles.y = Q_Forge->Forge[f_Index].ScanTurnAng;

	Q_Forge->Forge[f_Index].Angles.y = Q_Forge->Forge[f_Index].ScanTurnAng;
	if(Q_Forge->Forge[f_Index].Angles.y > (PI*2)) Q_Forge->Forge[f_Index].Angles.y = 0;
	if(Q_Forge->Forge[f_Index].Angles.y < 0) Q_Forge->Forge[f_Index].Angles.y = (PI*2);

	Q_Forge->Forge[f_Index].STOREAngles.y = Q_Forge->Forge[f_Index].ScanTurnAng;
#endif
	//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[f_Index].ScanTurnAng);
	//Qpo->Transform_Multiply(&Q_Forge->Forge[f_Index].AV.Xform, &AIfriendly, &Q_Forge->Forge[f_Index].AV.Xform);

	//Q_Forge->Forge[f_Index].Xform.Matrix.load_identity();
	Q_Forge->Forge[f_Index].Xform.Translation.x = f_Position.x;
	Q_Forge->Forge[f_Index].Xform.Translation.y = f_Position.y;
	Q_Forge->Forge[f_Index].Xform.Translation.z = f_Position.z;
	Q_Forge->Forge[f_Index].Xform.GhostTranslation.x = f_Position.x;
	Q_Forge->Forge[f_Index].Xform.GhostTranslation.y = f_Position.y;
	Q_Forge->Forge[f_Index].Xform.GhostTranslation.z = f_Position.z;

	//Q_Forge->Forge[f_Index].AV.Xform.Matrix.load_identity();
	Q_Forge->Forge[f_Index].AV.Xform.Translation.x = f_Position.x;
	Q_Forge->Forge[f_Index].AV.Xform.Translation.y = f_Position.y;
	Q_Forge->Forge[f_Index].AV.Xform.Translation.z = f_Position.z;
	Q_Forge->Forge[f_Index].AV.Xform.GhostTranslation.x = f_Position.x;
	Q_Forge->Forge[f_Index].AV.Xform.GhostTranslation.y = f_Position.y;
	Q_Forge->Forge[f_Index].AV.Xform.GhostTranslation.z = f_Position.z;

	if(f_IncNomAI) _->NomAI = _->NomAI + 1;

#if 1
	//#### RESET SCALE AND LIGHTING
	Qpo->Avatar_SetScale(&Q_Forge->Forge[f_Index].AV.Avatar, Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

#if 1
	Q_Forge->Forge[f_Index].Q_Brain.MindState = MIND_ACTIVEINIT;
#endif

	if(player[g_Player]->WeaponStatus == 0) player[g_Player]->CamMatrix.Translation.y = Q_Forge->Forge[f_Index].Xform.Translation.y + 20 + 25;
	else player[g_Player]->CamMatrix.Translation.y = Q_Forge->Forge[f_Index].Xform.Translation.y + 20 + 25 + 30;

#ifdef USE_CAPSULES
	player[g_Player]->CamMatrix.Translation.y *= Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2));

	PxMat33 f_GlobalPose;
	f_GlobalPose.createIdentity();
	PxMat33 f_LocalPose;
	f_LocalPose.createIdentity();

	g_ForgeBox[f_Index] = DigiMass->acCreateBox(physx::PxVec3(0, 0, 0), 50 * Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)), 20 * Q_Forge->Forge[f_Index].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)), 50, f_Index);
#endif

	//Make Live Avatar
	Q_Forge->Forge[f_Index].LIVE = 1;

	//##### SPAWN EFFECTS
	jet = 0;
	while(jet < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_Forge->Forge[f_Index].AV.Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 750) _->NomSpikes = 0;

		jet++;
		}

	//##### Unification Console #####//
	//pString str1;
	//str1.format("Spawn Avatar %f %f %f NomAI %i\n", f_Position.x, f_Position.y, f_Position.z, _->NomAI);
	//g_unConsole_vec_str.push_back(str1.getbuf());
	//g_unC_vec_ind.push_back(g_unCoutcnt);
	//g_unCoutcnt++;
	//##### Unification Console #####//

	return true;
};

QSpawnPoint::QSpawnPoint(int f_Team)
{
	m_Team = f_Team;
	m_Count = 0;

	m_CountSPD = 1;

	player[g_Player]->HB_DeadTimerPos = 0;

#if 0
	m_CountLimit = (((float)rand() / 32767) * 1350) + 300;
#else
	m_CountLimit = (((float)rand() / 32767) * 1500) + 1500;
#endif

	m_SpawnLimit = 5;

	for(int f_int = 0; f_int < 38; f_int++)
		{
		m_TeamColorsRED[f_int] = (((float)rand() / 32767) * 255) * 2;
		m_TeamColorsGREEN[f_int] = (((float)rand() / 32767) * 255) * 2;
		m_TeamColorsBLUE[f_int] = (((float)rand() / 32767) * 255) * 2;
		}

	for(int f_int = 0; f_int < 500; f_int++)
		{
		m_AVTEAM[f_int] = 0;
		}
};

void QSpawnPntController::acSpawnFrame(void)
{
	/////---- Iterate Through Spawn Points ----/////
	for(int f_count = 0; f_count < m_SpawnPoint.size(); f_count++)
		{
		/// Check for destroyed team change
		if(m_SpawnPoint[f_count]->m_ForgeAVID.size() > 0)
			{
			bool f_AllDead = true;
			for(int f_cnt = 0; f_cnt < m_SpawnPoint[f_count]->m_ForgeAVID.size(); f_cnt++)
				{
				if(Q_Forge->Forge[m_SpawnPoint[f_count]->m_ForgeAVID[f_cnt]].LIVE == 1) f_AllDead = false;
				}

			if(f_AllDead)
				{
				for(int f_cnt = 0; f_cnt < m_SpawnPoint[f_count]->m_ForgeAVID.size(); f_cnt++)
					{
					m_SpawnPoint[f_count]->m_AVTEAM[Q_Forge->Forge[m_SpawnPoint[f_count]->m_ForgeAVID[f_cnt]].HB_KillerTeam]++;
					}

				int f_LargestCnt = -1;
				int f_LargestID = -1;
				for(int f_int = 0; f_int < 500; f_int++)
					{
					if((m_SpawnPoint[f_count]->m_AVTEAM[f_int] > f_LargestCnt) && (f_int != 0))
						{
						f_LargestCnt = m_SpawnPoint[f_count]->m_AVTEAM[f_int];
						f_LargestID = f_int;
						}
					}

				if(f_LargestID > -1)
					{
					m_SpawnPoint[f_count]->m_Team = f_LargestID;
					printf("TEAM %i CAPTURED SPAWN POINT %i\n", f_LargestID, f_count);
					printf("TEAM %i CAPTURED SPAWN POINT %i\n", f_LargestID, f_count);
					printf("TEAM %i CAPTURED SPAWN POINT %i\n", f_LargestID, f_count);
					printf("TEAM %i CAPTURED SPAWN POINT %i\n", f_LargestID, f_count);
					printf("TEAM %i CAPTURED SPAWN POINT %i\n", f_LargestID, f_count);
					}
				}
			}

		m_SpawnPoint[f_count]->m_Count += m_SpawnPoint[f_count]->m_CountSPD;
		if(m_SpawnPoint[f_count]->m_Count > m_SpawnPoint[f_count]->m_CountLimit)
			{
			if(m_SpawnPoint[f_count]->m_ForgeAVID.size() < m_SpawnPoint[f_count]->m_SpawnLimit)
				{
				m_SpawnPoint[f_count]->m_Count = 0;

				QpoVec3d f_Position = m_SpawnPoint[f_count]->m_CellCenter;

				f_Position.x += (((float)rand() / 32767) * 200) - 100;
				f_Position.y += 0;
				f_Position.z += (((float)rand() / 32767) * 200) - 100;

				int bfinger = rand() % 10;
				int cfinger = (rand() % 4) + 1;

				int f_count_f = 0;
				
				f_count_f = _->NomAI;

				for(unsigned int f_index = 0; f_index < _->NomAI; f_index++)
					{
					if(Q_Forge->Forge[f_index].HB_Dead == 1)
						{
						f_count_f = f_index;
						f_index = _->NomAI;
						}
					}

				int f_TempTeam = m_SpawnPoint[f_count]->m_Team;
				if (!f_TempTeam) f_TempTeam = (rand() % 3) + 1;

				QActiveFrameWork->acSpawnAvatar(f_count_f, cfinger, bfinger, f_TempTeam, f_Position, 0, f_count);

				printf("SpawnPnt %i Team %i Spawn %i %f %f %f\n", f_count, m_SpawnPoint[f_count]->m_Team, f_count, f_Position.x, f_Position.y, f_Position.z);
				}
			else
				{
				m_SpawnPoint[f_count]->m_CountSPD *= 1.5;
				m_SpawnPoint[f_count]->m_SpawnLimit *= 3;
				}
			}
		}
}

void QActiveFramewrk::acRespawnAvatar(int f_Index)
{
	Q_Forge->Forge[f_Index].LIVE = 1;

	Q_Forge->Forge[f_Index].NetplayerFLAG = 0;

	Q_Forge->Forge[f_Index].AV.upspeed = -15;
	Q_Forge->Forge[f_Index].AV.Mins.x = -(20 + (20*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	Q_Forge->Forge[f_Index].AV.Mins.y = -(45 + (30*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	Q_Forge->Forge[f_Index].AV.Mins.z = -(20 + (20*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[f_Index].AV.Maxs.x = (20 + (20*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[f_Index].AV.Maxs.y = (45 + (30*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Height/100)-0.5)*2)));
	Q_Forge->Forge[f_Index].AV.Maxs.z = (20 + (20*(((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

	Q_Forge->Forge[f_Index].PlayerSpeed = PLAYER_SPEED;

	Q_Forge->Forge[f_Index].GravityAlter = 1;

	//Fill Weapon Ammo
	Q_Forge->Forge[f_Index].WeaponAmmo = 32;

	Q_Forge->Forge[f_Index].HB_Illumination = 255;
	Q_Forge->Forge[f_Index].HB_Dead = 0;

	Q_Forge->Forge[f_Index].HB_DeadTimer = 500;
	Q_Forge->Forge[f_Index].HB_LiveResetSW = 1;

	//Body and Mind
	Q_Forge->Forge[f_Index].Q_Heart.HeartIncrement = 0;
	Q_Forge->Forge[f_Index].Q_Heart.PulseRate = 1;
	Q_Forge->Forge[f_Index].Q_Brain.Aggression = 70;

	Q_Forge->Forge[f_Index].idlespeed = 0.1;

	Q_Forge->Forge[f_Index].HB_MaxHealth = 1000 * (((Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
	Q_Forge->Forge[f_Index].HB_Health = Q_Forge->Forge[f_Index].HB_MaxHealth;

	Q_Forge->Forge[f_Index].HB_MaxEnergy = 500;
	Q_Forge->Forge[f_Index].HB_Energy = Q_Forge->Forge[f_Index].HB_MaxEnergy;

	Q_Forge->Forge[f_Index].HB_Armour = ((float)(Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	Q_Forge->Forge[f_Index].HB_MaxArmour = ((float)(Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[f_Index].CharDATA.ItemDATA[Q_Forge->Forge[f_Index].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	Q_Forge->Forge[f_Index].JINK3_PowerFactor = 1;

	//#### RESET SPELLS
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[0].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[1].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[2].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[3].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[4].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[5].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[6].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[7].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[8].LIVE = 0;
	Q_Forge->Forge[f_Index].CharDATA.SpellSLOT[9].LIVE = 0;

	//####### RELATIVE ATTACK SPEED
	Q_Forge->Forge[f_Index].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[f_Index].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[f_Index].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[f_Index].CharDATA.BodySKILL.EnergyEff / 6000);

	Q_Forge->Forge[f_Index].AV.Avatar.Visible = true;

	Q_Forge->Forge[f_Index].AV.Avatar.IDflag = f_Index;

	//m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_RotationVec.y = 0;

	//Begin Transforming for Camera
	//Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[f_Index].AV.Xform, &Q_Forge->Forge[f_Index].AV.Up);

	//Qpo->Vec3d_Subtract(&Q_Forge->Forge[f_Index].AV.Up, &m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_RotationVec, &ScanTurnVec);
	//Q_Forge->Forge[f_Index].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);

	//### Check Distance between Pure Left and Right to work out direction of Turn
	/*Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[f_Index].AV.Xform, &Q_Forge->Forge[f_Index].AV.Left);

	Qpo->Vec3d_Copy(&Q_Forge->Forge[f_Index].AV.Left, &Q_Forge->Forge[f_Index].AV.Right);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[f_Index].AV.Right);

	ScanDistL = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_RotationVec, &Q_Forge->Forge[f_Index].AV.Left);
	ScanDistR = Qpo->Vec3d_DistanceBetween(&m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_RotationVec, &Q_Forge->Forge[f_Index].AV.Right);*/

	Q_Forge->Forge[f_Index].ScanTurnAng = (((float)rand() / 32767) - (float)0.5f) * (PI * 2) * 2;

	if(ScanDistL < ScanDistR) Q_Forge->Forge[f_Index].ScanTurnAng *= -1;

	Q_Forge->Forge[f_Index].trueAngles.y = Q_Forge->Forge[f_Index].ScanTurnAng;

	Q_Forge->Forge[f_Index].Angles.y = Q_Forge->Forge[f_Index].ScanTurnAng;
	if(Q_Forge->Forge[f_Index].Angles.y > (PI*2)) Q_Forge->Forge[f_Index].Angles.y = 0;
	if(Q_Forge->Forge[f_Index].Angles.y < 0) Q_Forge->Forge[f_Index].Angles.y = (PI*2);

	Q_Forge->Forge[f_Index].STOREAngles.y = Q_Forge->Forge[f_Index].ScanTurnAng;

	/*Q_Forge->Forge[f_Index].Xform.Translation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.x;
	Q_Forge->Forge[f_Index].Xform.Translation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.y;
	Q_Forge->Forge[f_Index].Xform.Translation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.z;
	Q_Forge->Forge[f_Index].Xform.GhostTranslation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.x;
	Q_Forge->Forge[f_Index].Xform.GhostTranslation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.y;
	Q_Forge->Forge[f_Index].Xform.GhostTranslation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.z;

	Q_Forge->Forge[f_Index].AV.Xform.Translation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.x;
	Q_Forge->Forge[f_Index].AV.Xform.Translation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.y;
	Q_Forge->Forge[f_Index].AV.Xform.Translation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.z;
	Q_Forge->Forge[f_Index].AV.Xform.GhostTranslation.x = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.x;
	Q_Forge->Forge[f_Index].AV.Xform.GhostTranslation.y = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.y;
	Q_Forge->Forge[f_Index].AV.Xform.GhostTranslation.z = m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_CellCenter.z;*/

	//#### Set Up Trail Flags
	Q_Forge->Forge[f_Index].TrailFadeSpan[0][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[1][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[2][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[3][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[4][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[5][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[6][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[7][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[8][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[9][0] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[0][1] = 0;
	Q_Forge->Forge[f_Index].TrailFadeSpan[1][1] = 1;
	Q_Forge->Forge[f_Index].TrailFadeSpan[2][1] = 2;
	Q_Forge->Forge[f_Index].TrailFadeSpan[3][1] = 3;
	Q_Forge->Forge[f_Index].TrailFadeSpan[4][1] = 4;
	Q_Forge->Forge[f_Index].TrailFadeSpan[5][1] = 5;
	Q_Forge->Forge[f_Index].TrailFadeSpan[6][1] = 6;
	Q_Forge->Forge[f_Index].TrailFadeSpan[7][1] = 7;
	Q_Forge->Forge[f_Index].TrailFadeSpan[8][1] = 8;
	Q_Forge->Forge[f_Index].TrailFadeSpan[9][1] = 9;

#if 0
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[f_Index].AV.Xform.Translation, (((float)rand() / 32767) - 0.5) * 1600, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_StRotationVec, &Q_Forge->Forge[f_Index].AV.Xform.Translation);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[f_Index].AV.Xform.Translation, (((float)rand() / 32767) - 0.5) * 600, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[f_Index].Team]->m_RotationVec, &Q_Forge->Forge[f_Index].AV.Xform.Translation);
#else
	Q_Forge->Forge[f_Index].AV.Xform.Translation.x += (((float)rand() / 32767) - 0.5) * 600;
	Q_Forge->Forge[f_Index].AV.Xform.Translation.z += (((float)rand() / 32767) - 0.5) * 600;
#endif

	Q_Forge->Forge[helly].Q_Brain.TargetLOSTcountON = false;

	Q_Forge->Forge[helly].Q_Brain.WeaponDrawPrime = true;
	Q_Forge->Forge[helly].Q_Brain.WeaponDrawCounter = 0;

	Qpo->Avatar_SetScale(&Q_Forge->Forge[helly].AV.Avatar, Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[helly].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[helly].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
}

void QActiveFramewrk::acRespawnPlayer(void)
{
	// Respawn Player
	player[g_Player]->TrailFadeSpan[0][0] = 0;
	player[g_Player]->TrailFadeSpan[1][0] = 0;
	player[g_Player]->TrailFadeSpan[2][0] = 0;
	player[g_Player]->TrailFadeSpan[3][0] = 0;
	player[g_Player]->TrailFadeSpan[4][0] = 0;
	player[g_Player]->TrailFadeSpan[5][0] = 0;
	player[g_Player]->TrailFadeSpan[6][0] = 0;
	player[g_Player]->TrailFadeSpan[7][0] = 0;
	player[g_Player]->TrailFadeSpan[8][0] = 0;
	player[g_Player]->TrailFadeSpan[9][0] = 0;
	player[g_Player]->TrailFadeSpan[0][1] = 0;
	player[g_Player]->TrailFadeSpan[1][1] = 1;
	player[g_Player]->TrailFadeSpan[2][1] = 2;
	player[g_Player]->TrailFadeSpan[3][1] = 3;
	player[g_Player]->TrailFadeSpan[4][1] = 4;
	player[g_Player]->TrailFadeSpan[5][1] = 5;
	player[g_Player]->TrailFadeSpan[6][1] = 6;
	player[g_Player]->TrailFadeSpan[7][1] = 7;
	player[g_Player]->TrailFadeSpan[8][1] = 8;
	player[g_Player]->TrailFadeSpan[9][1] = 9;

	// Setup the player specific flags
	player[g_Player]->ForwardSpeed = 0;
	player[g_Player]->upspeed = -15;
	player[g_Player]->camrotdist = 1000;
	player[g_Player]->GravityAlter = 1;
	player[g_Player]->AirJinkPrep = 0;

	//#### ENERGY MATRIX SETUP

	Q_EnergyMatrix->EnergyMatrix.GlobalSCALE = 100;

	player[g_Player]->EnergyArchitect.ExpandSTRENGTH = 1.15;
	TestfloatALPHA1 = 7.149;
	TestfloatALPHA2 = 1.15;

	_->WorldScale = 1;

	player[g_Player]->Invisible = 0;

	//Player Level
	player[g_Player]->LEVEL = 1;

	//Fill Weapon Ammo
	player[g_Player]->WeaponAmmo = 32;

	player[g_Player]->Mins.x = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	player[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    player[g_Player]->Mins.z = -(25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.x = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    player[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    player[g_Player]->Maxs.z = (25 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->upspeed = 0;

	playerAV[g_Player]->Mins.x = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
    playerAV[g_Player]->Mins.y = -(45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
    playerAV[g_Player]->Mins.z = -(20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.x = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.y = (45 + (30*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
    playerAV[g_Player]->Maxs.z = (20 + (20*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);

	player[g_Player]->HB_Armour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	player[g_Player]->HB_MaxArmour = ((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	player[g_Player]->HB_MaxHealth = 1000 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/100)*0.6)+0.4);
	player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;

	player[g_Player]->HB_MaxEnergy = 500;
	player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

	player[g_Player]->JINK3_PowerFactor = 1;

	player[g_Player]->HB_Dead = 0;
	player[g_Player]->HB_DeadTimerC = 1500;

	playerAV[g_Player]->CollisionCount = 0;

	//##### Starting position
	/*Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y = 0; 
	Ange.y=Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + (PI); 
	if(Ange.y>(2*PI)) Ange.y = Ange.y - (PI*2);
	Ange.x=-(PI/2);
	Ange.z=0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, Ange.x);
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, Ange.y);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Ange.z);

	player[g_Player]->STOREMatrix = playerAV[g_Player]->Xform;*/

	//#### RESET SPELLS
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[3].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[4].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[5].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[6].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[7].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[8].LIVE = 0;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[9].LIVE = 0;

#if 1
									//SCALE VALUES HEIGHT,WEIGHT,WEIGHT
	Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	#pragma message ("Add Actor SCALE")

	// Set the actor to its position
	//Qpo->Vec3d_Copy(&Q_StartPoints->StartPoints[player[g_Player]->Team].Pos, &playerAV[g_Player]->Xform.Translation);

	//player[g_Player]->Angles.x = -1.05;
	//player[g_Player]->Angles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	//player[g_Player]->trueAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;
	//player[g_Player]->STOREAngles.y = Q_StartPoints->StartPoints[player[g_Player]->Team].Ang.y + PI;

	//fogbox.Min.x = playerAV[g_Player]->Mins.x;
	//fogbox.Min.y = playerAV[g_Player]->Mins.y;
	//fogbox.Min.z = playerAV[g_Player]->Mins.z;
	//fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	//fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	//fogbox.Max.z = playerAV[g_Player]->Maxs.z;

	player[g_Player]->idlespeed = 0.1;

	//Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->STOREMatrix.Translation);

	playerAV[g_Player]->Avatar.IDflag = 250;

	player[g_Player]->AttackSoundTRIG = 0;

	//### Load Player Weapon
	player[g_Player]->Weapon.Avatar = 1;

	player[g_Player]->Weapon.Scale.x = 1;
	player[g_Player]->Weapon.Scale.y = 1;
	player[g_Player]->Weapon.Scale.z = 1;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	player[g_Player]->Weapon.Mins.x = -20.f;
	player[g_Player]->Weapon.Mins.y = -20.f;
	player[g_Player]->Weapon.Mins.z = -20.f;
	player[g_Player]->Weapon.Maxs.x = 20.f;
	player[g_Player]->Weapon.Maxs.y = 20.f;
	player[g_Player]->Weapon.Maxs.z = 20.f;

	#pragma message ("Add Weapon SCALE")
#if 0
	Qpo->Avatar_SetScale(&player[g_Player]->Weapon.Avatar, 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 1.2 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
#endif

	//Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Weapon.Xform.Translation);

	player[g_Player]->WeaponDISPLAY = 0;

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
		{
		Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shield.Xform.Translation);

		player[g_Player]->Shield.Mins.x = -500.f;
		player[g_Player]->Shield.Mins.y = -500.f;
		player[g_Player]->Shield.Mins.z = -500.f;
		player[g_Player]->Shield.Maxs.x = 500.f;
		player[g_Player]->Shield.Maxs.y = 500.f;
		player[g_Player]->Shield.Maxs.z = 500.f;

		fogbox.Min.x = player[g_Player]->Shield.Mins.x;
		fogbox.Min.y = player[g_Player]->Shield.Mins.y;
		fogbox.Min.z = player[g_Player]->Shield.Mins.z;
		fogbox.Max.x = player[g_Player]->Shield.Maxs.x;
		fogbox.Max.y = player[g_Player]->Shield.Maxs.y;
		fogbox.Max.z = player[g_Player]->Shield.Maxs.z;

#if 0
		QpoActor_SetScale(player[g_Player]->Shield.Avatar, 0.65f,0.65f,0.65f);

		Qpo->Avatar_SetAlpha(&player[g_Player]->Shield.Avatar, 150);
#endif

		player[g_Player]->Shield.Avatar.IDflag = 251;
		}

	//##### SPAWN EFFECTS
#if 1
	jet = 0;
	while(jet < 25)
		{
		//# Effect Type
		Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 2;

		//## Speed
		Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

		//### Width
		Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

		//#### Gravity
		Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

		//##### Alpha Level
		Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

		//###### Center Position
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
		Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
		Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

		//####### Create Trajectory Vector From Random Numbers
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
		Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

		//######## Set Timers
		Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
		Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

		//######### Make Live
		Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

		_->NomSpikes++;
		if(_->NomSpikes > 750) _->NomSpikes = 0;

		jet++;
		}
#endif

	Qpo->Vec3d_Copy(&_->Origin, &player[g_Player]->Vehicle.Model.Xform.Translation);

	player[g_Player]->Vehicle.Model.Mins.x = -20.f;
	player[g_Player]->Vehicle.Model.Mins.y = -20.f;
	player[g_Player]->Vehicle.Model.Mins.z = -20.f;
	player[g_Player]->Vehicle.Model.Maxs.x = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.y = 20.f;
	player[g_Player]->Vehicle.Model.Maxs.z = 20.f;

	player[g_Player]->Vehicle.Model.Avatar.IDflag = 250;

	//### Physics Setup
	player[g_Player]->Vehicle.Const_Weight = 8;	//Ten Q_Kgs
	player[g_Player]->Vehicle.Const_FWeight = 2;	//1.5
	player[g_Player]->Vehicle.Const_RWeight = 2;	//1.5
	player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0.335;

	player[g_Player]->Vehicle.Const_SpinCancel = 0.25;	//1.8
	player[g_Player]->Vehicle.Const_SpringLift = 7.5;	//2.5  1.23
	player[g_Player]->Vehicle.Const_SpringPower = 4;
	player[g_Player]->Vehicle.Const_WheelSettleSpin = 5;
	player[g_Player]->Vehicle.Const_WheelSettleDVel = 3.5;
	player[g_Player]->Vehicle.Const_SpringLimit = 14.5;
	player[g_Player]->Vehicle.Const_DownVelCancel = 3;
	player[g_Player]->Vehicle.Const_ForceFactor = 50;	//5
	player[g_Player]->Vehicle.Const_SpringAbsorbVel = 6.6;
	player[g_Player]->Vehicle.Const_SpringAbsorbSpin = 1.15;
	player[g_Player]->Vehicle.Const_LightTouchFactor = 1.15;
	player[g_Player]->Vehicle.Const_MaxSpeed = 100;

	player[g_Player]->Vehicle.Const_SpringCrunchMAX = 15;
	//player[g_Player]->Vehicle.Const_MiddleCOGDIST = -31;
	//player[g_Player]->Vehicle.Const_SpringCompDist = 20;

	player[g_Player]->Vehicle.Const_FRICMinSlide = 15;

	//#### BUILD CRUNCH UP VECS
	player[g_Player]->Vehicle.ConstVec_FCrunch.x = 1.071;
	player[g_Player]->Vehicle.ConstVec_FCrunch.y = 7.887;
	player[g_Player]->Vehicle.ConstVec_FCrunch.z = 3.893;

	player[g_Player]->Vehicle.ConstVec_RCrunch.x = 1.102;
	player[g_Player]->Vehicle.ConstVec_RCrunch.y = 8.116;
	player[g_Player]->Vehicle.ConstVec_RCrunch.z = 1.521;

	player[g_Player]->Vehicle.GravityAlter = 1;

#if 0
	if(player[g_Player]->Team >= QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.size())
		player[g_Player]->Team = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.size() - 1;

	playerAV[g_Player]->Xform.Translation.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.x;
	playerAV[g_Player]->Xform.Translation.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.y;
	playerAV[g_Player]->Xform.Translation.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.z;

	player[g_Player]->finalcolldet_oldpos.x = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.x;
	player[g_Player]->finalcolldet_oldpos.y = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.y;
	player[g_Player]->finalcolldet_oldpos.z = QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_CellCenter.z;

	//Begin Transforming for Camera
	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &playerAV[g_Player]->Up);

	QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec.y = 0;

	Qpo->Vec3d_Subtract(&playerAV[g_Player]->Up, &QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec, &ScanTurnVec);
	Ange.y = Qpo->Vec3d_Length(&ScanTurnVec);

	//### Check Distance between Pure Left and Right to work out direction of Turn
	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &playerAV[g_Player]->Left);

	Qpo->Vec3d_Copy(&playerAV[g_Player]->Left, &playerAV[g_Player]->Right);
	Qpo->Vec3d_Inverse(&playerAV[g_Player]->Right);

	ScanDistL = Qpo->Vec3d_DistanceBetween(&QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec, &playerAV[g_Player]->Left);
	ScanDistR = Qpo->Vec3d_DistanceBetween(&QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint[player[g_Player]->Team]->m_RotationVec, &playerAV[g_Player]->Right);

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 0.0f);	//RED
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Left.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Left.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Left.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].AV.Right.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].AV.Right.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].AV.Right.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AIcounter].ScanVecTo.x * 250), TempVec2.y + (Q_Forge->Forge[AIcounter].ScanVecTo.y * 250), TempVec2.z + (Q_Forge->Forge[AIcounter].ScanVecTo.z * 250));
	//*glEnd();
#endif

	/*if(ScanDistL < ScanDistR) Ange.y *= -1;

	player[g_Player]->trueAngles.y = Ange.y + (PI - (PI/2));

	player[g_Player]->Angles.y = Ange.y + (PI - (PI/2));
	if(player[g_Player]->Angles.y > (PI*2)) player[g_Player]->Angles.y = 0;
	if(player[g_Player]->Angles.y < 0) player[g_Player]->Angles.y = (PI*2);

	player[g_Player]->STOREAngles.y = Ange.y + (PI - (PI/2));*/

		if(ScanDistL < ScanDistR) Ange.y *= -1;

		player[g_Player]->trueAngles.y = Ange.y + PI;

		player[g_Player]->Angles.y = Ange.y + PI;
		if(player[g_Player]->Angles.y > (PI*2)) player[g_Player]->Angles.y = 0;
		if(player[g_Player]->Angles.y < 0) player[g_Player]->Angles.y = (PI*2);
#endif
		//player[g_Player]->STOREAngles.y = Ange.y + PI;

	//Qpo->Transform_New_YRotation(&AIfriendly, Ange.y);
	//Qpo->Transform_Multiply(&playerAV[g_Player]->Xform, &AIfriendly, &playerAV[g_Player]->Xform);
}

};