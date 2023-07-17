/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 13/06/08
		Copyright - J M Lawlor

	- Major Component -Q-Network-
	*/#include "pch.h"/*- Minor Component -World Transmission-

*/

//*#include "../UnSRC/Utility/RakNetMsgIdent.h"
//*#include "RakNetworkFactory.h"
//*#include "RakPeerInterface.h"
//*#include "RakNetStatistics.h"
//*#include "RakNetTypes.h"
//*#include "../../Server/PacketSocketInterface.h"

//*#include "GetTime.h"
//*#include "../../Server/unsStringCompressor.h"

#include "../../Server/Thread.h"
#include "../../Server/UNSResource.h"

#include "QActiveFramewrk.h"

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include <stdlib.h>
#include <stdio.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-WE-PntSprite.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-WE-BulletSystem.h"
#include "Q-NET-ProtoMap.h"

#if 1
#define AVATAR_PHYSICS_ENABLE 1
#else
#define AVATAR_PHYSICS_ENABLE 0
#endif

//extern //SDL_mutex* m_mutex_Mesh;

using namespace GVARS;

namespace GVARS
{

Q_Network QNetwork;

//##### -+ World Transmission +- #####

void Q_Network::Initialize(void)
{
	m_Recording = false;
	m_Playing = false;
	m_TapeLoaded = false;
}

#if 0
Q_Network::Q_Network()
{
	m_Recording = false;
	m_Playing = false;
}
#endif

void Q_Network::CreateTapeBuffer(const char* i_Filename)
{
	if(m_Recording || m_Playing) printf("Q-Network...ERROR Close current tape first %s\n", i_Filename);
	else
		{
		std::string i_path = "TapeStorage\\";
		std::string i_ext = ".txt";
		std::string i_file = i_Filename;
		std::string i_filepath = i_path + i_file + i_ext;

		//##### - Open our Character Data File
		m_stream = fopen(i_filepath.c_str(), "w");

#pragma message("FIXME::: Saved filename to custom header")

		m_Recording = true;
		m_TapeLoaded = true;
		m_CurrTape = i_file;

		printf("Q-Network... Tape..[START] i_Filename %s\n", i_Filename);
		}
}

void Q_Network::FinalizeTapeBuffer(void)
{
	fclose(m_stream);

	m_Recording = false;

	printf("Q-Network [STOP] Recording saved to 'TapeStorage\\'\n");
}

void Q_Network::OpenTapeBuffer(const char* i_Filename)
{
	if(m_Recording || m_Playing) printf("Q-Network...ERROR Close current tape first %s\n", i_Filename);
	else
		{
		if(!m_TapeLoaded)
			{
			std::string i_path = "TapeStorage\\";
			std::string i_file = i_Filename;
			std::string i_filepath = i_path + i_file;

			m_stream = fopen(i_filepath.c_str(), "r");

			if(m_stream)
				{
				//////// Tape Player Inits ////////
				m_Playing = true;
				m_CurrTape = i_file;
				player[g_Player]->NetRotation = player[g_Player]->AvatarRotation;
				}
			else
				{
				printf("ERROR:::file not found %s\n", i_filepath.c_str());
				}
			}
		else
			{
			std::string i_path = "TapeStorage\\";
			std::string i_filepath = i_path + m_CurrTape;

			m_stream = fopen(i_filepath.c_str(), "r");

			if(m_stream)
				{
				//////// Tape Player Inits ////////
				m_Playing = true;
				player[g_Player]->NetRotation = player[g_Player]->AvatarRotation;
				}
			else
				{
				printf("ERROR:::file not found %s\n", i_filepath.c_str());
				}
			}

#pragma message("FIXME::: File Header with timescale declaration and other GVARS")
#pragma message("FIXME::: Saved filename to custom header")

		printf("Q-Network... Tape..[START] i_Filename %s\n", i_Filename);
		}
}

void Q_Network::CloseTapeBuffer(void)
{
	fclose(m_stream);

	m_Playing = false;

	printf("Q-Network Tape Playing [STOP]\n");
}

void Q_Network::TransmitWorld(float i_Time, int f_ClientVectorID)
{
	int f_Fill0 = 0;
	int f_Fill1 = 1;
	int f_Fill5 = -5;

	//BitTransfer_Data		Buffer;
	//QInt			Data[555000];

	//BitTransfer_Set(Data, 555000);

	//printf("unClient:::Q_Network::TransmitWorld()\n");

	//SET MESSAGE TYPE AND SERVER TIME
	//BitTransfer_FillByte(NETMGR_MSG_UPDATE_CLIENT_WORLD);			// Let client know its updating
	BitTransfer_FillFloat(i_Time);								// Current Time
	//BitTransfer_FillFloat(Client->ServerPingBack);			// Current Time

	//###### PREPARE Player Update  #####
	//#### Find Player Avatar
	//wb_helly=0;
	//while(Q_Netplayer->Netplayer[wb_helly].ID != NID)
	//	{ wb_helly++; }

	//### FILL BUFFER
	/***INU**BitTransfer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].AV.Xform.Translation);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Mposestate);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].EnergySWITCHOFF > 0)
		{
		Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].EnergySWITCHOFF--;
		BitTransfer_FillByte(205);
		}
	else BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Aposestate);

	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].attackon);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].WeaponStatus);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].NETMFlash);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Block);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].BlockHit);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].BlockHeight);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Crouch);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].HitReactScale);
	BitTransfer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].MoveReactVec);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].MoveReactSpeed);

	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].JINK3_PowerFactor);

	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].HB_Energy);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].HB_Health);

	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SpecLvlRESET);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SNDTRIGEnergy);
	
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].PlayerMode);

	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].idleposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].runposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].attposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].crohposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].jumpposecnt);

	BitTransfer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].WallRunCollision.Plane.Normal);

	Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SNDTRIGEnergy = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SpecLvlRESET = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].NETMFlash = 0;*/

	//### Set the Avatar Count
	int f_FF = 0;
	wb_jet=0;
	while(wb_jet < _->NomAI)
		{
		if(((Q_Forge->Forge[wb_jet].LIVE == 1) && (wb_jet != f_ClientVectorID)) && (Q_Forge->Forge[wb_jet].m_Own == 1)) f_FF++;
		wb_jet++;
		}
						//Plus Player Avatar
	BitTransfer_FillByte(f_FF + 1);

	//###### PREPARE SERVER'S Player Update  #####
	//#### Find Server Avatar
	//#### Prepare Server Player Update

	//### FILL BUFFER
	BitTransfer_FillFloat(playerAV[g_Player]->Xform.Translation.x);
	BitTransfer_FillFloat(playerAV[g_Player]->Xform.Translation.y);
	BitTransfer_FillFloat(playerAV[g_Player]->Xform.Translation.z);

	printf("SEND x %f y %f z %f\n", playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);

#pragma message("Full matrix transmission or partial quat makeup")
#if 1
	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &playerAV[g_Player]->Up);
	//BitTransfer_FillAngle(&playerAV[g_Player]->Up);

	m_transfer->acPushAlloc(playerAV[g_Player]->Up.x);
	m_transfer->acPushAlloc(playerAV[g_Player]->Up.y);
	m_transfer->acPushAlloc(playerAV[g_Player]->Up.z);

	BitTransfer_FillByte(player[g_Player]->Mposestate);

	if(player[g_Player]->EnergySWITCHOFF > 0)
		{
		player[g_Player]->EnergySWITCHOFF--;

		BitTransfer_FillByte(205);
		}
	else BitTransfer_FillByte(player[g_Player]->Aposestate);

	BitTransfer_FillByte(player[g_Player]->attackon);
	BitTransfer_FillByte(player[g_Player]->WeaponStatus);
	BitTransfer_FillByte(player[g_Player]->NETMFlash);
	BitTransfer_FillByte(player[g_Player]->Block);
	BitTransfer_FillByte(player[g_Player]->BlockHit);
	BitTransfer_FillByte(player[g_Player]->BlockHeight);
	BitTransfer_FillByte(player[g_Player]->Crouch);
	BitTransfer_FillFloat(player[g_Player]->HitReactScale);
	BitTransfer_FillFloat(player[g_Player]->MoveReactVec.x);
	BitTransfer_FillFloat(player[g_Player]->MoveReactVec.y);
	BitTransfer_FillFloat(player[g_Player]->MoveReactVec.z);
	BitTransfer_FillFloat(player[g_Player]->MoveReactSpeed);

	BitTransfer_FillFloat(player[g_Player]->JINK3_PowerFactor);

	BitTransfer_FillFloat(player[g_Player]->HB_Energy);
	BitTransfer_FillFloat(player[g_Player]->HB_Health);
	BitTransfer_FillFloat(player[g_Player]->HB_Armour);
	BitTransfer_FillFloat(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK);
	
	BitTransfer_FillByte(player[g_Player]->PlayerMode);

	BitTransfer_FillFloat(player[g_Player]->idleposecnt);
	BitTransfer_FillFloat(player[g_Player]->runposecnt);
	BitTransfer_FillFloat(player[g_Player]->attposecnt);
	BitTransfer_FillFloat(player[g_Player]->crohposecnt);
	BitTransfer_FillFloat(player[g_Player]->jumpposecnt);

	//***IMU***BitTransfer_FillAngle(&player[g_Player]->WallRunCollision.Plane.Normal);

	player[g_Player]->NETMFlash = 0;
#endif

	//######  - Other Worldly Avatars -  #####

	//#### Fill AI Avatars
	/*int i_AvatarCount = 0;
	wb_helly2=0;
	while(wb_helly2 < _->NomAI)
		{
		if((Q_Forge->Forge[wb_helly2].LIVE == 1) && (wb_helly2 != Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID)) QHost.PlayerUPDATE.AvatarCount++;
		wb_helly2++;
		}*/


	//### Set the Avatar Count
	//**INU**BitTransfer_FillInteger(_->NomAI - 1);

	//##### AVATAR UPDATE PREP LOOP
	wb_jet=0;
	while(wb_jet < _->NomAI)
		{
		if(((Q_Forge->Forge[wb_jet].LIVE == 1) && (wb_jet != f_ClientVectorID)) && (Q_Forge->Forge[wb_jet].m_Own == 1))
			{
			Q_Forge->Forge[wb_jet].NETMFlash = 0;

			//### FILL BUFFER
			BitTransfer_FillByte(wb_jet);
#pragma message("?")

			//###Get Player Data to Client
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].AV.Xform.Translation.x);				//Avatar Position
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].AV.Xform.Translation.y);				//Avatar Position
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].AV.Xform.Translation.z);				//Avatar Position

#pragma message("Full matrix transmission or partial quat makeup")

			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].Up.x);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].Up.y);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].Up.z);

			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].Mposestate);		//Avatar Move Pose State

			if(player[g_Player]->EnergySWITCHOFF > 0)
				{
				player[g_Player]->EnergySWITCHOFF--;

				BitTransfer_FillByte(205);
				}
			else BitTransfer_FillByte(Q_Forge->Forge[wb_jet].Aposestate);

			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].attackon);		//Avatar Attack Pose State
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].WeaponStatus);
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].NETMFlash);
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].Block);			//Avatar Attack Pose State
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].BlockHit);		//Avatar Attack Pose State
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].BlockHeight);
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].Crouch);			//Avatar Attack Pose State
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].HitReactScale);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].MoveReactVec.x);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].MoveReactVec.y);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].MoveReactVec.z);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].MoveReactSpeed);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].JINK3_PowerFactor);

			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].HB_Energy);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].HB_Health);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].HB_Armour);
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].CharDATA.BodySKILL.POWERBANK);
			
			BitTransfer_FillByte(Q_Forge->Forge[wb_jet].PlayerMode);

			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].idleposecnt);		//Avatar Idle Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].runposecnt);		//Avatar Run Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].attposecnt);		//Avatar Attack Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].crohposecnt);		//Avatar Attack Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[wb_jet].jumpposecnt);		//Avatar Attack Pose Counter

			//***IMU***BitTransfer_FillAngle(&Q_Forge->Forge[wb_jet].WallRunCollision.Plane.Normal);
			}

		wb_jet++;
		}

	//##### Update Damage to all Avatars

	BitTransfer_FillByte(_->NomAI);

	wb_helly = 0;
	while(wb_helly < _->NomAI)
		{
		BitTransfer_FillByte(Q_Forge->Forge[wb_helly].m_Own);
		BitTransfer_FillFloat(Q_Forge->Forge[wb_helly].HB_Armour);
		BitTransfer_FillFloat(Q_Forge->Forge[wb_helly].HB_Health);
		BitTransfer_FillFloat(Q_Forge->Forge[wb_helly].CharDATA.BodySKILL.POWERBANK);

		wb_helly++;
		}

	//##### - Control Hit Reactions for Avatars and Players
	//Count how many in reaction
	m_vec_HitReactionGB.clear();
	for(int f_Scan = 0; f_Scan < _->NomAI; f_Scan++)
		{
		if(Q_Forge->Forge[f_Scan].Aposestate == 26 ||
			Q_Forge->Forge[f_Scan].Aposestate == 28 ||
			Q_Forge->Forge[f_Scan].Aposestate == 30 ||
			Q_Forge->Forge[f_Scan].Aposestate == 51 ||
			Q_Forge->Forge[f_Scan].Aposestate == 90 ||
			Q_Forge->Forge[f_Scan].Aposestate == 91)
			{
			if(Q_Forge->Forge[f_Scan].HitReactionGB == 0)
				{
				Q_Forge->Forge[f_Scan].HitReactionGB = 1;
				m_vec_HitReactionGB.push_back(f_Scan);
				}
			}
		else
			{
			Q_Forge->Forge[f_Scan].HitReactionGB = 0;
			}
		}

	BitTransfer_FillByte(m_vec_HitReactionGB.size());

	for(int f_Scan = 0; f_Scan < m_vec_HitReactionGB.size(); f_Scan++)
		{
		BitTransfer_FillByte(f_Scan);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].AV.Xform.Translation.x);				//Avatar Position
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].AV.Xform.Translation.y);				//Avatar Position
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].AV.Xform.Translation.z);				//Avatar Position

#pragma message("Full matrix transmission or partial quat makeup")

		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].Up.x);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].Up.y);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].Up.z);

		BitTransfer_FillByte(Q_Forge->Forge[f_Scan].Aposestate);
		BitTransfer_FillByte(Q_Forge->Forge[f_Scan].attackon);
		BitTransfer_FillByte(Q_Forge->Forge[f_Scan].BlockHit);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].HitReactScale);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].MoveReactVec.x);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].MoveReactVec.y);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].MoveReactVec.z);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].MoveReactSpeed);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].attposecnt);		//Avatar Attack Pose Counter

		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].HB_Energy);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].HB_Health);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].HB_Armour);
		BitTransfer_FillFloat(Q_Forge->Forge[f_Scan].CharDATA.BodySKILL.POWERBANK);
		}


	//##### Prepare Q_Object->ObjectS
	BitTransfer_FillByte(_->NomQObject);

	wb_aero = 0;
	while(wb_aero < _->NomQObject)
		{
		BitTransfer_FillFloat(Q_Object->Object[wb_aero].StrengthBANK);
		
		wb_aero++;
		}

	
	//##### Prepare World Bullets
	m_Start = false;
	m_StartData = false;
	wb_aero = 0;
	while(wb_aero < _->NomBullet)
		{
		if(Q_Bullet->Bullet[wb_aero].NetFlag == 0)
			{
			bool f_Shot = false;
			if(Q_Bullet->Bullet[wb_aero].AvID == 250)
				{
				f_Shot = true;
				}
			else
				{
				if(Q_Forge->Forge[Q_Bullet->Bullet[wb_aero].AvID].m_Own == 1) f_Shot = true;
				}

			if(f_Shot)
				{
				if(m_Start == false)
					{
					m_Start = true;
					BitTransfer_FillByte(f_Fill1);
					}

				if(m_StartData == false)
					{
					m_StartData = true;
					BitTransfer_FillByte(_->NomBullet);
					}

				BitTransfer_FillByte(wb_aero);
				BitTransfer_FillByte(Q_Bullet->Bullet[wb_aero].Live);
				BitTransfer_FillByte(Q_Bullet->Bullet[wb_aero].AvID);
				BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].TrajVec);
				BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].WorldPos);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].Speed);
				BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].ORIGPos);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].ZSpin);
				/*BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][0]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][1]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][2]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][0]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][1]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][2]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][0]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][1]);
				BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][2]);*/
				BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Translation);
				BitTransfer_FillByte(Q_Bullet->Bullet[wb_aero].JDamageLVL);

				m_Start = false;
				}
			}

		wb_aero++;
		}

	if(m_Start == false)
		{
		m_Start = true;
		BitTransfer_FillByte(f_Fill0);
		}

	if(m_StartData == false)
		{
		m_StartData = true;
		BitTransfer_FillByte(_->NomBullet);
		}

#if 1
	//##### Prepare World Bullet Hits
	//___Clear Live Vector_________
	//ses_Q_BulletHit_Live.clear();
	m_Start = false;
	wb_aero = 0;
	while(wb_aero < _->NomBulHit)
		{
		//if(Q_BulletHit->BulletHit[wb_aero].Live == 1)
		//	{
			/*ses_Q_BulletHit_Live.push_back(Q_BulletHit->BulletHit[wb_aero].Live);

			if(wb_aero >= ses_Q_BulletHit_Live_STR.size())
				{
				for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
					{
					ses_Q_BulletHit_Live_STR.push_back(-5);
					}
				}

			if(ses_Q_BulletHit_Live_STR[wb_aero] == 0 && Q_BulletHit->BulletHit[wb_aero].Live == 1)
				{*/
				bool f_Hit = false;
				if(Q_BulletHit->BulletHit[wb_aero].AvID == 250) f_Hit = true;
				else if(Q_Forge->Forge[Q_BulletHit->BulletHit[wb_aero].AvID].m_Own == 1) f_Hit = true;

				if(f_Hit == true)
					{
					if(m_Start == false)
						{
						m_Start = true;
						BitTransfer_FillByte(f_Fill1);
						}

					BitTransfer_FillByte(wb_aero);
					BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].Live);
					BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].Init);
					BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].EffectType);
					BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].AvID);
					BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].AvatarHITID);

					BitTransfer_FillFloat(Q_BulletHit->BulletHit[wb_aero].BulletDMG);
					BitTransfer_FillFloat(Q_BulletHit->BulletHit[wb_aero].BulletPWR);

					BitTransfer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].Pos);
					BitTransfer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].BulletTraj);
					BitTransfer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].CollNormal);

					m_Start = false;
					}
				//}
			//}

		wb_aero++;
		}

	if(m_Start == false)
		{
		m_Start = true;
		BitTransfer_FillByte(f_Fill0);
		}

	//Storage Pusher
	//ses_Q_BulletHit_Live_STR.clear();
	//for(int xsf = 0; xsf < ses_Q_BulletHit_Live.size(); xsf++)
	//	{ ses_Q_BulletHit_Live_STR.push_back(ses_Q_BulletHit_Live[xsf]); }

	//##### Prepare World Melee Hits
	//Clear Live Vector
	//ses_Q_MeleeHit_Live.clear();
	m_Start = false;
	wb_aero = 0;
	while(wb_aero < _->NomMelHit)
		{
		/*ses_Q_MeleeHit_Live.push_back(Q_MeleeHit->MeleeHit[wb_aero].Live);

		if(wb_aero >= ses_Q_MeleeHit_Live_STR.size())
			{
			for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
				{
				ses_Q_MeleeHit_Live_STR.push_back(0);
				}
			}

		if(ses_Q_MeleeHit_Live_STR[wb_aero] == 0 && Q_MeleeHit->MeleeHit[wb_aero].Live == 1)
			{*/
			bool f_Hit = false;
			if(Q_MeleeHit->MeleeHit[wb_aero].AvID == 250) f_Hit = true;
			else if(Q_Forge->Forge[Q_MeleeHit->MeleeHit[wb_aero].AvID].m_Own == 1) f_Hit = true;

			if(f_Hit == true)
				{
				if(m_Start == false)
					{
					m_Start = true;
					BitTransfer_FillByte(f_Fill1);
					}

				BitTransfer_FillByte(wb_aero);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Live);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].HitTYPE);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].HitRESULT);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].AvID);

				BitTransfer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].Impact);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Bonenum);
				BitTransfer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].ReactionNorm);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].HitPowerPercent);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].BloodAmt);

				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.MaxRadius);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.StartFade);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Red);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Green);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Blue);

				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttackSTRENGTH);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttackSNAP);
		
				/*BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][0]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][1]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][2]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][0]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][1]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][2]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][0]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][1]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][2]);*/
				BitTransfer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Translation);

				m_Start = false;
				}
			//}

		wb_aero++;
		}

	if(m_Start == false)
		{
		m_Start = true;
		BitTransfer_FillByte(f_Fill0);
		}

	//Storage Pusher
	//ses_Q_MeleeHit_Live_STR.clear();
	//for(int xsf = 0; xsf < ses_Q_MeleeHit_Live.size(); xsf++)
	//	{ ses_Q_MeleeHit_Live_STR.push_back(ses_Q_MeleeHit_Live[xsf]); }

	//##### Prepare Small Energy
	m_Start = false;
	wb_aero = 0;
	while(wb_aero < _->NomSEnergy)
		{
		bool f_Hit = false;
		if(Q_SEnergy->SEnergy[wb_aero].AvID == 250) f_Hit = true;
		else if(Q_Forge->Forge[Q_SEnergy->SEnergy[wb_aero].AvID].m_Own == 1) f_Hit = true;

		if(f_Hit == true)
			{
			if(m_Start == false)
				{
				m_Start = true;
				BitTransfer_FillByte(f_Fill1);
				}

			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].Live);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].AvID);
			BitTransfer_FillAngle(&Q_SEnergy->SEnergy[wb_aero].LightPos);
			BitTransfer_FillAngle(&Q_SEnergy->SEnergy[wb_aero].TraVec);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].Speed);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].Scale);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].Alpha);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].TargetLock);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].TargetID);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleX);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleY);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleZ);

			m_Start = false;
			}

		wb_aero++;
		}

	if(m_Start == false)
		{
		m_Start = true;
		BitTransfer_FillByte(f_Fill0);
		}

	//Storage Pusher
	//ses_Q_BulletHit_Live_STR.clear();
	//for(int xsf = 0; xsf < ses_Q_BulletHit_Live.size(); xsf++)
	//	{ ses_Q_BulletHit_Live_STR.push_back(ses_Q_BulletHit_Live[xsf]); }

	//##### Prepare Large Energy
	//Clear Live Vector
	m_Start = false;
	wb_aero = 0;
	while(wb_aero < _->NomLEnergy)
		{
		bool f_Hit = false;
		if(Q_LEnergy->LEnergy[wb_aero].AvID == 250) f_Hit = true;
		else if(Q_Forge->Forge[Q_LEnergy->LEnergy[wb_aero].AvID].m_Own == 1) f_Hit = true;

		if(f_Hit == true)
			{
			if(m_Start == false)
				{
				m_Start = true;
				BitTransfer_FillByte(f_Fill1);
				}

			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].Live);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].AvID);
			BitTransfer_FillAngle(&Q_LEnergy->LEnergy[wb_aero].LightPos);
			BitTransfer_FillAngle(&Q_LEnergy->LEnergy[wb_aero].TraVec);
			BitTransfer_FillFloat(Q_LEnergy->LEnergy[wb_aero].Speed);
			BitTransfer_FillFloat(Q_LEnergy->LEnergy[wb_aero].Scale);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].Alpha);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].EnergyLive);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].EnergyFire);

			m_Start = false;
			}

		wb_aero++;
		}

	if(m_Start == false)
		{
		m_Start = true;
		BitTransfer_FillByte(f_Fill0);
		}

	//Storage Pusher
	//ses_Q_LEnergy_Live_STR.clear();
	//for(int xsf = 0; xsf < ses_Q_LEnergy_Live.size(); xsf++)
	//	{ ses_Q_LEnergy_Live_STR.push_back(ses_Q_LEnergy_Live[xsf]); }

	//##### Prepare World Explosions
	//Clear Live Vector
	//ses_Counter = 0;
	//ses_Q_Explosion_Live.clear();
	m_Start = false;
	wb_aero = 0;
	while(wb_aero < _->NomExplosions)
		{
		/*ses_Q_Explosion_Live.push_back(Q_Explosion->Explosion[wb_aero].Live);

		if(wb_aero >= ses_Q_LEnergy_Live_STR.size())
			{
			for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
				{
				ses_Q_LEnergy_Live_STR.push_back(0);
				}
			}*/

		//if(ses_Q_Explosion_Live_STR[wb_aero] == 0 && Q_Explosion->Explosion[wb_aero].Live == 1)
		//	{
		bool f_Hit = false;
		if(Q_Explosion->Explosion[wb_aero].AvID == 250) f_Hit = true;
		else if(Q_Forge->Forge[Q_Explosion->Explosion[wb_aero].AvID].m_Own == 1) f_Hit = true;

		if(f_Hit == true)
			{
			if(m_Start == false)
				{
				m_Start = true;
				BitTransfer_FillByte(f_Fill1);
				}

			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_Explosion->Explosion[wb_aero].Live);
			BitTransfer_FillByte(Q_Explosion->Explosion[wb_aero].AvID);
			BitTransfer_FillAngle(&Q_Explosion->Explosion[wb_aero].Pos);
			BitTransfer_FillFloat(Q_Explosion->Explosion[wb_aero].ExpSize);
			BitTransfer_FillByte(Q_Explosion->Explosion[wb_aero].LargeEnergyAvID);
			BitTransfer_FillAngle(&Q_Explosion->Explosion[wb_aero].CollPlaneNormal);

			m_Start = false;
			}

		wb_aero++;
		}

	if(m_Start == false)
		{
		m_Start = true;
		BitTransfer_FillByte(f_Fill0);
		}

	//Storage Pusher
	//ses_Q_Explosion_Live_STR.clear();
	//for(int xsf = 0; xsf < ses_Q_Explosion_Live.size(); xsf++)
	//	{ ses_Q_Explosion_Live_STR.push_back(ses_Q_Explosion_Live[xsf]); }

	//##### Prepare Cleric Heal Sparks
	/***IMU***BitTransfer_FillInteger(_->NomHSpark);

	wb_aero = 0;
	while(wb_aero < _->NomHSpark)
		{
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].Live);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].HTYPE);
		BitTransfer_FillAngle(&Q_HealSpark->HealSpark[wb_aero].Pos);
		BitTransfer_FillAngle(&Q_HealSpark->HealSpark[wb_aero].TraVec);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].Released);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].Absorbed);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].HealTarget);
		BitTransfer_FillFloat(Q_HealSpark->HealSpark[wb_aero].AlpFade);
		BitTransfer_FillFloat(Q_HealSpark->HealSpark[wb_aero].ScaleSTR);

		wb_aero++;
		}


	//##### Prepare Cleric Spells
	BitTransfer_FillInteger(_->NomSpell);

	wb_aero = 0;
	while(wb_aero < _->NomSpell)
		{
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Live);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].HealTarget);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].NumSpheres);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].LightPos);
		BitTransfer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].LightPow);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Absorbed);

		BitTransfer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Radius);
		BitTransfer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Radius);

		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].StartFade);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].StartFade);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Upvec);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Upvec);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Upvec);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Upvec);

		wb_aero++;
		}


	//##### Prepare Cleric Plasma
	BitTransfer_FillInteger(_->NomPlasma);

	wb_aero = 0;
	while(wb_aero < _->NomPlasma)
		{
		BitTransfer_FillByte(Q_ClericPlasma->ClericPlasma[wb_aero].Live);
		BitTransfer_FillAngle(&Q_ClericPlasma->ClericPlasma[wb_aero].Pos);
		BitTransfer_FillAngle(&Q_ClericPlasma->ClericPlasma[wb_aero].TraVec);
		BitTransfer_FillFloat(Q_ClericPlasma->ClericPlasma[wb_aero].Speed);
		BitTransfer_FillFloat(Q_ClericPlasma->ClericPlasma[wb_aero].Alpha);
		BitTransfer_FillByte(Q_ClericPlasma->ClericPlasma[wb_aero].PartType);
		wb_aero++;
		}


	//##### Prepare Net Effects Control
	BitTransfer_FillInteger(_->NomNetEffectControl);

	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		BitTransfer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].Live);
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Type == 0) BitTransfer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].Type);
		BitTransfer_FillAngle(&Q_NetEffectControl->NetEffectControl[wb_aero].Pos);
		BitTransfer_FillFloat(Q_NetEffectControl->NetEffectControl[wb_aero].Effintensity);
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Type == 1) BitTransfer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].AvID);
		
		wb_aero++;
		}


	//###### ---- Net Effects Control ---- ######
	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Live > 1)
			{	//#### COUNTER ####
			Q_NetEffectControl->NetEffectControl[wb_aero].Live--;
			}
		else
			{
			Q_NetEffectControl->NetEffectControl[wb_aero].Live = 0;

			if(Q_NetEffectControl->NetEffectControl[wb_aero].Type = 0)
				{
				//### Energy Array Reorder
				K = wb_aero;
				while(K < _->NomNetEffectControl - 1)
					{
					Q_NetEffectControl->NetEffectControl[K] = Q_NetEffectControl->NetEffectControl[K+1];
					K++;
					}
				}

			_->NomNetEffectControl--;
			}
		wb_aero++;
		}/***IMU***/

#if 0
	//##### Prepare Net Zone Increment
	ses_Counter = 0;

	wb_aero = 0;
	while(wb_aero < Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC)
		{
#ifdef SES_REPEATABILITY
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].AVID == 250)
			{
#endif
			ses_Counter++;
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].AVID);

			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Maxs);
			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Mins);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.CNT);

			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandMINS);
			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandMAXS);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandSTRENGTH);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_TimeScale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Gravity);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LifeINC);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_EnergyINC);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_intBoost);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_EnergyEff);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Height);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Weight);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Strength);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Quickness);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Dexterity);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Constitution);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_AggPower);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_DefPower);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RArmStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LArmStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RLegStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LLegStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RArmSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LArmSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RLegSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LLegSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPAccuracy);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPDrawSPD);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPReloadSPD);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPRecoilHR);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINKmovespeed);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINKpower);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINK3intensity);

			if(wb_aero >= Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
			}
#endif
		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//# Energy Reset
	Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC = 0;

	//##### Prepare Net Zone ENTITY Increment

	wb_aero = 0;
	while(wb_aero < _->NomNetZoneENTITY)
		{
#ifdef SES_REPEATABILITY
		if(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].AvID == 250)
			{
#endif
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_NetZoneENTITY->NetZoneENTITY[wb_aero].TYPE);
			BitTransfer_FillFloat(Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID);
			BitTransfer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].ZoneID);
			BitTransfer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID);
			BitTransfer_FillAngle(&Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].Pos);
			BitTransfer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].Range);
			BitTransfer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].Scale);
			BitTransfer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].StrengthMAX);
			BitTransfer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].CollisionTYPE);
			BitTransfer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].AvID);
			
			if(wb_aero >= _->NomNetZoneENTITY) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
			}
#endif
		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//# Energy Reset
	_->NomNetZoneENTITY = 0;
#endif

#if 0
	//### FRLs
	BitTransfer_FillFloat(_->FRLtarget);
	BitTransfer_FillByte(Q_Netplayer->Netplayer[wb_helly].FRLswitch);
#endif

#endif


	/*if (!geCSNetMgr_SendToClient(QHost.NMgr->CSNetMgr, NID, GE_true, QHost.NMgr->ServerToClientBuffer.Data, QHost.NMgr->ServerToClientBuffer.Pos))
		return GE_false;*/

#pragma message("Server engine command not found")
#if defined(WIN32)
	//flushall();
#endif
}


void Q_Network::ServerTransmitWorld(float i_Time)
{
#ifndef WIN32
	//int f_playerAvatarID;

	printf("unClient:::Q_Network::ServerTransmitWorld()\n");

	//SET MESSAGE TYPE AND SERVER TIME
	//BitTransfer_FillByte(NETMGR_MSG_UPDATE_CLIENT_WORLD);			// Let client know its updating
	BitTransfer_FillFloat(i_Time);								// Current Time
	//BitTransfer_FillFloat(Client->ServerPingBack);			// Current Time

	//###### PREPARE Player Update  #####
	//#### Find Player Avatar
	//wb_helly=0;
	//while(Q_Netplayer->Netplayer[wb_helly].ID != NID)
	//	{ wb_helly++; }

	//### FILL BUFFER
	/***INU**BitTransfer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].AV.Xform.Translation);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Mposestate);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].EnergySWITCHOFF > 0)
		{
		Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].EnergySWITCHOFF--;
		BitTransfer_FillByte(205);
		}
	else BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Aposestate);

	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].attackon);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].WeaponStatus);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].NETMFlash);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Block);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].BlockHit);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].BlockHeight);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].Crouch);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].HitReactScale);
	BitTransfer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].MoveReactVec);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].MoveReactSpeed);

	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].JINK3_PowerFactor);

	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].HB_Energy);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].HB_Health);

	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SpecLvlRESET);
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SNDTRIGEnergy);
	
	BitTransfer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].PlayerMode);

	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].idleposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].runposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].attposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].crohposecnt);
	BitTransfer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].jumpposecnt);

	BitTransfer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].WallRunCollision.Plane.Normal);

	Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SNDTRIGEnergy = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].SpecLvlRESET = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID].NETMFlash = 0;*/


	//###### PREPARE SERVER'S Player Update  #####
	//#### Find Server Avatar
	//#### Prepare Server Player Update

	//### FILL BUFFER
	/***IMU***BitTransfer_FillAngle(&playerAV[g_Player]->Xform.Translation);

#pragma message("Full matrix transmission or partial quat makeup")

	BitTransfer_FillAngle(&playerAV[g_Player]->Up);

	BitTransfer_FillByte(player[g_Player]->Mposestate);

	if(player[g_Player]->EnergySWITCHOFF > 0)
		{
		player[g_Player]->EnergySWITCHOFF--;

		BitTransfer_FillByte(205);
		}
	else BitTransfer_FillByte(player[g_Player]->Aposestate);

	BitTransfer_FillByte(player[g_Player]->attackon);
	BitTransfer_FillByte(player[g_Player]->WeaponStatus);
	BitTransfer_FillByte(player[g_Player]->NETMFlash);
	BitTransfer_FillByte(player[g_Player]->Block);
	BitTransfer_FillByte(player[g_Player]->BlockHit);
	BitTransfer_FillByte(player[g_Player]->BlockHeight);
	BitTransfer_FillByte(player[g_Player]->Crouch);
	BitTransfer_FillFloat(player[g_Player]->HitReactScale);
	BitTransfer_FillAngle(&player[g_Player]->MoveReactVec);
	BitTransfer_FillFloat(player[g_Player]->MoveReactSpeed);

	BitTransfer_FillFloat(player[g_Player]->JINK3_PowerFactor);

	BitTransfer_FillFloat(player[g_Player]->HB_Energy);
	BitTransfer_FillFloat(player[g_Player]->HB_Health);
	
	BitTransfer_FillByte(player[g_Player]->PlayerMode);

	BitTransfer_FillFloat(player[g_Player]->idleposecnt);
	BitTransfer_FillFloat(player[g_Player]->runposecnt);
	BitTransfer_FillFloat(player[g_Player]->attposecnt);
	BitTransfer_FillFloat(player[g_Player]->crohposecnt);
	BitTransfer_FillFloat(player[g_Player]->jumpposecnt);

	//***IMU***BitTransfer_FillAngle(&player[g_Player]->WallRunCollision.Plane.Normal);

	player[g_Player]->NETMFlash = 0;*/


	//######  - Other Worldly Avatars -  #####

	//#### Fill AI Avatars
	/*int i_AvatarCount = 0;
	wb_helly2=0;
	while(wb_helly2 < _->NomAI)
		{
		if((Q_Forge->Forge[wb_helly2].LIVE == 1) && (wb_helly2 != Q_Netplayer->Netplayer[wb_helly].LocalCONTROLID)) QHost.PlayerUPDATE.AvatarCount++;
		wb_helly2++;
		}*/

	/*if(g_map_ClientAvatarID.find(i_SysIndex) == g_map_ClientAvatarID.end())
		{
		printf("Serve Error:::ServerTransmitWorld::: Cannot find System index in g_map_ClientAvatarID\n");
		}
	else
		{
		g_mutex_AvatarID->ac_Sync();
		m_vec_IdentList = g_map_ClientAvatarID[i_SysIndex];
		g_mutex_AvatarID->ac_Free();

		m_mutexcc_AvatarId->ac_Fire();
		f_playerAvatarID = m_vec_IdentList->vec_Index[0];
		m_mutexcc_AvatarId->ac_Stop();
		}*/

	//### Set the Avatar Count
	BitTransfer_FillInteger(g_Domain[0].vec_entity_Avatar[0].size());

	//##### AVATAR UPDATE PREP LOOP
	wb_jet=0;
	while(wb_jet < g_Domain[0].vec_entity_Avatar[0].size())
		{
		if(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].LIVE == 1)
			{
			Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].NETMFlash = 0;

			//### FILL BUFFER
			BitTransfer_FillByte(g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID);
#pragma message("?")

			//###Get Player Data to Client
			BitTransfer_FillAngle(&Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].AV.Xform.Translation);				//Avatar Position

#pragma message("Full matrix transmission or partial quat makeup")

			BitTransfer_FillAngle(&Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Up);

			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Mposestate);		//Avatar Move Pose State

			if(player[g_Player]->EnergySWITCHOFF > 0)
				{
				player[g_Player]->EnergySWITCHOFF--;

				BitTransfer_FillByte(205);
				}
			else BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Aposestate);

			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].attackon);		//Avatar Attack Pose State
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].WeaponStatus);
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].NETMFlash);
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Block);			//Avatar Attack Pose State
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].BlockHit);		//Avatar Attack Pose State
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].BlockHeight);
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Crouch);			//Avatar Attack Pose State
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].HitReactScale);
			BitTransfer_FillAngle(&Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].MoveReactVec);
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].MoveReactSpeed);
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].JINK3_PowerFactor);

			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].HB_Energy);
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].HB_Health);
			
			BitTransfer_FillByte(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].PlayerMode);

			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].idleposecnt);		//Avatar Idle Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].runposecnt);		//Avatar Run Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].attposecnt);		//Avatar Attack Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].crohposecnt);		//Avatar Attack Pose Counter
			BitTransfer_FillFloat(Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].jumpposecnt);		//Avatar Attack Pose Counter

			//***IMU***BitTransfer_FillAngle(&Q_Forge->Forge[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].WallRunCollision.Plane.Normal);
			}

		wb_jet++;
		}

	//||| FIXME Transmit only updates here |||///
	//##### Prepare Q_Object->ObjectS
	BitTransfer_FillFloat(_->NomQObject);

	wb_aero = 0;
	while(wb_aero < _->NomQObject)
		{
		BitTransfer_FillFloat(Q_Object->Object[wb_aero].StrengthBANK);
		
		wb_aero++;
		}
	
	//##### Prepare World Bullets
	//Clear Live Vector
	ses_Q_Bullet_Live.clear();
	//ses_Counter = 0;

	wb_aero = 0;
	while(wb_aero < _->NomBullet)
		{
		ses_Q_Bullet_Live.push_back(Q_Bullet->Bullet[wb_aero].Live);

		if(wb_aero >= ses_Q_BulletHit_Live_STR.size())
			{
			for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
				{
				ses_Q_BulletHit_Live_STR.push_back(0);
				}
			}

		if(Q_Bullet->Bullet[wb_aero].Live != ses_Q_Bullet_Live_STR[wb_aero])
			{
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_Bullet->Bullet[wb_aero].Live);
			BitTransfer_FillByte(Q_Bullet->Bullet[wb_aero].AvID);
			BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].TrajVec);
			BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].WorldPos);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].Speed);
			BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].ORIGPos);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].ZSpin);
			/*BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][0]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][1]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][2]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][0]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][1]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][2]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][0]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][1]);
			BitTransfer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][2]);*/
			BitTransfer_FillAngle(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Translation);
			BitTransfer_FillByte(Q_Bullet->Bullet[wb_aero].JDamageLVL);

			if(wb_aero >= _->NomBullet) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
			}

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//Storage Pusher
	ses_Q_Bullet_Live_STR.clear();
	for(int xsf = 0; xsf < ses_Q_Bullet_Live.size(); xsf++)
		{ ses_Q_Bullet_Live_STR.push_back(ses_Q_Bullet_Live[xsf]); }

	//##### Prepare World Bullet Hits
	//Clear Live Vector
	//ses_Counter = 0;
	ses_Q_BulletHit_Live.clear();

	wb_aero = 0;
	while(wb_aero < _->NomBulHit)
		{
		ses_Q_BulletHit_Live.push_back(Q_BulletHit->BulletHit[wb_aero].Live);

		if(wb_aero >= ses_Q_BulletHit_Live_STR.size())
			{
			for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
				{
				ses_Q_BulletHit_Live_STR.push_back(0);
				}
			}

		if(ses_Q_BulletHit_Live_STR[wb_aero] == 0 && Q_BulletHit->BulletHit[wb_aero].Live == 1)
			{
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].Live);
			BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].Init);
			BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].EffectType);

			BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].AvID);
			BitTransfer_FillByte(Q_BulletHit->BulletHit[wb_aero].AvatarHITID);

			BitTransfer_FillFloat(Q_BulletHit->BulletHit[wb_aero].BulletDMG);
			BitTransfer_FillFloat(Q_BulletHit->BulletHit[wb_aero].BulletPWR);

			BitTransfer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].Pos);
			BitTransfer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].BulletTraj);
			BitTransfer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].CollNormal);

			if(wb_aero >= _->NomBulHit) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
			}

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//Storage Pusher
	ses_Q_BulletHit_Live_STR.clear();
	for(int xsf = 0; xsf < ses_Q_BulletHit_Live.size(); xsf++)
		{ ses_Q_BulletHit_Live_STR.push_back(ses_Q_BulletHit_Live[xsf]); }

	//##### Prepare World Melee Hits
	//Clear Live Vector
	//ses_Counter = 0;
	ses_Q_MeleeHit_Live.clear();

	wb_aero = 0;
	while(wb_aero < _->NomMelHit)
		{
		ses_Q_MeleeHit_Live.push_back(Q_MeleeHit->MeleeHit[wb_aero].Live);

		if(wb_aero >= ses_Q_MeleeHit_Live_STR.size())
			{
			for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
				{
				ses_Q_MeleeHit_Live_STR.push_back(0);
				}
			}

		if(ses_Q_MeleeHit_Live_STR[wb_aero] == 0 && Q_MeleeHit->MeleeHit[wb_aero].Live == 1)
			{
#ifdef SES_REPEATABILITY
			if(Q_MeleeHit->MeleeHit[wb_aero].AvID == 250)
				{
#endif
				BitTransfer_FillByte(wb_aero);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Live);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].HitTYPE);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].HitRESULT);

				BitTransfer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].Impact);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Bonenum);
				BitTransfer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].ReactionNorm);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].HitPowerPercent);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].AvID);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].BloodAmt);

				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.MaxRadius);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.StartFade);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Red);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Green);
				BitTransfer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Blue);

				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttackSTRENGTH);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttackSNAP);
		
				/*BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][0]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][1]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][2]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][0]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][1]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][2]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][0]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][1]);
				BitTransfer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][2]);*/
				BitTransfer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Translation);

				if(wb_aero >= _->NomBulHit) BitTransfer_FillByte(f_Fill0);
				else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
				}
#endif
			}

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//Storage Pusher
	ses_Q_MeleeHit_Live_STR.clear();
	for(int xsf = 0; xsf < ses_Q_MeleeHit_Live.size(); xsf++)
		{ ses_Q_MeleeHit_Live_STR.push_back(ses_Q_MeleeHit_Live[xsf]); }

	//##### Prepare Small Energy
	wb_aero = 0;
	while(wb_aero < _->NomSEnergy)
		{
#ifdef SES_REPEATABILITY
		if(Q_SEnergy->SEnergy[wb_aero].AvID == 250)
			{
#endif
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].Live);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].AvID);
			BitTransfer_FillAngle(&Q_SEnergy->SEnergy[wb_aero].LightPos);
			BitTransfer_FillAngle(&Q_SEnergy->SEnergy[wb_aero].TraVec);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].Speed);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].Scale);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].Alpha);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].TargetLock);
			BitTransfer_FillByte(Q_SEnergy->SEnergy[wb_aero].TargetID);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleX);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleY);
			BitTransfer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleZ);

			if(wb_aero >= _->NomSEnergy) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
			}
#endif

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//Storage Pusher
	ses_Q_BulletHit_Live_STR.clear();
	for(int xsf = 0; xsf < ses_Q_BulletHit_Live.size(); xsf++)
		{ ses_Q_BulletHit_Live_STR.push_back(ses_Q_BulletHit_Live[xsf]); }

	//##### Prepare Large Energy
	wb_aero = 0;
	while(wb_aero < _->NomLEnergy)
		{
#ifdef SES_REPEATABILITY
		if(Q_LEnergy->LEnergy[wb_aero].AvID == 250)
			{
#endif
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].Live);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].AvID);
			BitTransfer_FillAngle(&Q_LEnergy->LEnergy[wb_aero].LightPos);
			BitTransfer_FillAngle(&Q_LEnergy->LEnergy[wb_aero].TraVec);
			BitTransfer_FillFloat(Q_LEnergy->LEnergy[wb_aero].Speed);
			BitTransfer_FillFloat(Q_LEnergy->LEnergy[wb_aero].Scale);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].Alpha);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].EnergyLive);
			BitTransfer_FillByte(Q_LEnergy->LEnergy[wb_aero].EnergyFire);

			if(wb_aero >= _->NomLEnergy) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
			}
#endif

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//Storage Pusher
	ses_Q_LEnergy_Live_STR.clear();
	for(int xsf = 0; xsf < ses_Q_LEnergy_Live.size(); xsf++)
		{ ses_Q_LEnergy_Live_STR.push_back(ses_Q_LEnergy_Live[xsf]); }

	//##### Prepare World Explosions
	//Clear Live Vector
	ses_Counter = 0;
	ses_Q_Explosion_Live.clear();

	wb_aero = 0;
	while(wb_aero < _->NomExplosions)
		{
		ses_Q_Explosion_Live.push_back(Q_Explosion->Explosion[wb_aero].Live);

		if(wb_aero >= ses_Q_LEnergy_Live_STR.size())
			{
			for(int f_dime = 0; f_dime <= wb_aero; f_dime++)
				{
				ses_Q_LEnergy_Live_STR.push_back(0);
				}
			}

		if(ses_Q_Explosion_Live_STR[wb_aero] == 0 && Q_Explosion->Explosion[wb_aero].Live == 1)
			{
#ifdef SES_REPEATABILITY
			if(Q_Explosion->Explosion[wb_aero].AvID == 250)
				{
#endif
				BitTransfer_FillByte(wb_aero);
				BitTransfer_FillByte(Q_Explosion->Explosion[wb_aero].Live);
				BitTransfer_FillByte(Q_Explosion->Explosion[wb_aero].AvID);
				BitTransfer_FillAngle(&Q_Explosion->Explosion[wb_aero].Pos);
				BitTransfer_FillFloat(Q_Explosion->Explosion[wb_aero].ExpSize);
				BitTransfer_FillByte(Q_Explosion->Explosion[wb_aero].LargeEnergyAvID);
				BitTransfer_FillAngle(&Q_Explosion->Explosion[wb_aero].CollPlaneNormal);

				if(wb_aero >= _->NomExplosions) BitTransfer_FillByte(f_Fill0);
				else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
				}
#endif
			}

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//Storage Pusher
	ses_Q_Explosion_Live_STR.clear();
	for(int xsf = 0; xsf < ses_Q_Explosion_Live.size(); xsf++)
		{ ses_Q_Explosion_Live_STR.push_back(ses_Q_Explosion_Live[xsf]); }

	//##### Prepare Cleric Heal Sparks
	/***IMU***BitTransfer_FillInteger(_->NomHSpark);

	wb_aero = 0;
	while(wb_aero < _->NomHSpark)
		{
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].Live);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].HTYPE);
		BitTransfer_FillAngle(&Q_HealSpark->HealSpark[wb_aero].Pos);
		BitTransfer_FillAngle(&Q_HealSpark->HealSpark[wb_aero].TraVec);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].Released);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].Absorbed);
		BitTransfer_FillByte(Q_HealSpark->HealSpark[wb_aero].HealTarget);
		BitTransfer_FillFloat(Q_HealSpark->HealSpark[wb_aero].AlpFade);
		BitTransfer_FillFloat(Q_HealSpark->HealSpark[wb_aero].ScaleSTR);

		wb_aero++;
		}


	//##### Prepare Cleric Spells
	BitTransfer_FillInteger(_->NomSpell);

	wb_aero = 0;
	while(wb_aero < _->NomSpell)
		{
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Live);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].HealTarget);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].NumSpheres);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].LightPos);
		BitTransfer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].LightPow);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Absorbed);

		BitTransfer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Radius);
		BitTransfer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Radius);

		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].StartFade);
		BitTransfer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].StartFade);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Upvec);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Upvec);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Upvec);

		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Leftvec);
		BitTransfer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Upvec);

		wb_aero++;
		}


	//##### Prepare Cleric Plasma
	BitTransfer_FillInteger(_->NomPlasma);

	wb_aero = 0;
	while(wb_aero < _->NomPlasma)
		{
		BitTransfer_FillByte(Q_ClericPlasma->ClericPlasma[wb_aero].Live);
		BitTransfer_FillAngle(&Q_ClericPlasma->ClericPlasma[wb_aero].Pos);
		BitTransfer_FillAngle(&Q_ClericPlasma->ClericPlasma[wb_aero].TraVec);
		BitTransfer_FillFloat(Q_ClericPlasma->ClericPlasma[wb_aero].Speed);
		BitTransfer_FillFloat(Q_ClericPlasma->ClericPlasma[wb_aero].Alpha);
		BitTransfer_FillByte(Q_ClericPlasma->ClericPlasma[wb_aero].PartType);
		wb_aero++;
		}


	//##### Prepare Net Effects Control
	BitTransfer_FillInteger(_->NomNetEffectControl);

	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		BitTransfer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].Live);
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Type == 0) BitTransfer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].Type);
		BitTransfer_FillAngle(&Q_NetEffectControl->NetEffectControl[wb_aero].Pos);
		BitTransfer_FillFloat(Q_NetEffectControl->NetEffectControl[wb_aero].Effintensity);
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Type == 1) BitTransfer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].AvID);
		
		wb_aero++;
		}


	//###### ---- Net Effects Control ---- ######
	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Live > 1)
			{	//#### COUNTER ####
			Q_NetEffectControl->NetEffectControl[wb_aero].Live--;
			}
		else
			{
			Q_NetEffectControl->NetEffectControl[wb_aero].Live = 0;

			if(Q_NetEffectControl->NetEffectControl[wb_aero].Type = 0)
				{
				//### Energy Array Reorder
				K = wb_aero;
				while(K < _->NomNetEffectControl - 1)
					{
					Q_NetEffectControl->NetEffectControl[K] = Q_NetEffectControl->NetEffectControl[K+1];
					K++;
					}
				}

			_->NomNetEffectControl--;
			}
		wb_aero++;
		}/***IMU***/


	//##### Prepare Net Zone Increment

	wb_aero = 0;
	while(wb_aero < Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC)
		{
#ifdef SES_REPEATABILITY
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].AVID == 250)
			{
#endif
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].AVID);

			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Maxs);
			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Mins);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.CNT);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.TYPE);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.INT);
			BitTransfer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.ON);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Red);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Green);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Blue);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Alpha);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Scale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.TIMER);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.CNT);

			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandMINS);
			BitTransfer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandMAXS);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandSTRENGTH);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_TimeScale);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Gravity);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LifeINC);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_EnergyINC);

			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_intBoost);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_EnergyEff);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Height);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Weight);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Strength);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Quickness);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Dexterity);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Constitution);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_AggPower);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_DefPower);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RArmStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LArmStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RLegStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LLegStr);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RArmSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LArmSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RLegSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LLegSnap);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPAccuracy);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPDrawSPD);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPReloadSPD);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPRecoilHR);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINKmovespeed);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINKpower);
			BitTransfer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINK3intensity);
			
			if(wb_aero >= Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
			}
#endif

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//# Energy Reset
	Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC = 0;


	//##### Prepare Net Zone ENTITY Increment

	wb_aero = 0;
	while(wb_aero < _->NomNetZoneENTITY)
		{
#ifdef SES_REPEATABILITY
		if(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].AvID == 250)
			{
#endif
			BitTransfer_FillByte(wb_aero);
			BitTransfer_FillByte(Q_NetZoneENTITY->NetZoneENTITY[wb_aero].TYPE);
			BitTransfer_FillFloat(Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID);
			BitTransfer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].ZoneID);
			BitTransfer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID);
			BitTransfer_FillAngle(&Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].Pos);
			BitTransfer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].Range);
			BitTransfer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].Scale);
			BitTransfer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].StrengthMAX);
			BitTransfer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].CollisionTYPE);
			BitTransfer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].AvID);
			
			if(wb_aero >= _->NomNetZoneENTITY) BitTransfer_FillByte(f_Fill0);
			else BitTransfer_FillByte(1);
#ifdef SES_REPEATABILITY
			}
#endif

		wb_aero++;
		}

	if(wb_aero == 0) BitTransfer_FillByte(-5);

	//# Energy Reset
	_->NomNetZoneENTITY = 0;


	//### FRLs
	BitTransfer_FillFloat(_->FRLtarget);
	BitTransfer_FillByte(Q_Netplayer->Netplayer[wb_helly].FRLswitch);


	/*if (!geCSNetMgr_SendToClient(QHost.NMgr->CSNetMgr, NID, GE_true, QHost.NMgr->ServerToClientBuffer.Data, QHost.NMgr->ServerToClientBuffer.Pos))
		return GE_false;*/

#pragma message("Server engine command not found")
#if defined(WIN32)
	//flushall();
#endif
#endif
}


void Q_Network::RecieveWorld(float Time, int f_ClientVectorID)
{
	float				DeltaTime, MoveTime;
	UInt16				ButtonBits;
	int					AvatarID;
	int					VECID;
	int					CDATAID;
	int					BDATAID;
	int					TEAM;
	int					ServerIdent;
	QpoVec3d			BufferCheck;

	//printf("ID_SERVER_WORLD recieve SERVER World\n");

	if(f_ClientVectorID >= m_HighVectorID) m_HighVectorID = f_ClientVectorID;

	//##Check Time
	m_transfer->acRead(MoveTime);

	//printf("MoveTime %f\n", MoveTime);

	//##### - Control Hit Reactions for Avatars and Players
	//How many in reaction
	m_vec_ServerHitReactionGB.clear();
	m_transfer->acRead(m_NomHitGB);

	for(int f_Scan = 0; f_Scan < m_NomHitGB; f_Scan++)
		{
		m_transfer->acRead(m_HitReactionGB);
		Q_Forge->Forge[m_HitReactionGB].HitReactionGB = 1;
		m_vec_ServerHitReactionGB.push_back(m_HitReactionGB);
		}

	//######  - Other Worldly Avatars -  #####

	//m_transfer->acRead(_->NETNomWorldAvatars);

	m_transfer->acRead(_->NETNomWorldAvatars);

#if 1
	printf("_->NETNomWorldAvatars %i ", _->NETNomWorldAvatars);
#endif

	if(_->NETNomWorldAvatars >= player[g_Player]->BFO.GamePlayersNom) //player[g_Player]->BFO.GameAvatarsMaxAmt)
		{
		//Un-Freeze Client
		player[g_Player]->BFO.GamePAUSE = false;
		}

	//##### Avatar Update Loop
	wb_helly=0;
	while(wb_helly < _->NETNomWorldAvatars)
		{
		//###### Get Avatars Q_Netplayer->Netplayer #####
		m_transfer->acRead(AvatarID);

		if(Q_Forge->Forge[AvatarID].m_Own == 0) Q_Forge->Forge[AvatarID].NetplayerFLAG = 1;
		else Q_Forge->Forge[AvatarID].NetplayerFLAG = 0;

		//Read in CDATA Vector DATA
		m_transfer->acRead(VECID);

		//Read in Character DATA
		m_transfer->acRead(CDATAID);

		//Read in Mesh DATA
		m_transfer->acRead(BDATAID);

		//Read in TEAM DATA
		m_transfer->acRead(TEAM);

#if 1
		printf("Q_Network::RecieveWorld::: AvatarID %i TEAM %i\n", AvatarID, TEAM);
#endif

#if 0
		int f_AvIDFL = AvatarID - 1;
		if(f_AvIDFL < 0) f_AvIDFL = _->NETNomWorldAvatars - 1;
		if(f_AvIDFL >= _->NETNomWorldAvatars) f_AvIDFL -= _->NETNomWorldAvatars;
#else
		int f_AvIDFL = AvatarID;
#endif

#if 0
		//SDL_mutexP(m_mutex_Mesh);
#endif
		if((AvatarID >= _->NomAI) || ((Q_Forge->Forge[AvatarID].LIVE == 0) && (AvatarID != f_ClientVectorID)))
			{
			acStartNetplayer(VECID, f_AvIDFL, CDATAID, BDATAID, TEAM);
			}
		else
			{
			if(Q_Forge->Forge[AvatarID].CharDATA.CDataID != CDATAID || Q_Forge->Forge[AvatarID].CharDATA.AvatarREF != BDATAID) acResetNetplayer(VECID, f_AvIDFL, CDATAID, BDATAID, TEAM);
			}
#if 0
		else acResetNetplayer(VECID, f_AvIDFL, CDATAID, BDATAID, TEAM);
		//SDL_mutexV(m_mutex_Mesh);
#endif

		printf("Q_Network::RecieveWorld::: VECID %i CDATAID %i BDATAID %i AvatarID %i f_ClientVectorID %i _->NomAI %i\n", VECID, CDATAID, BDATAID, AvatarID, f_ClientVectorID, _->NomAI);

		if(AvatarID != f_ClientVectorID)
			{
			Q_Forge->Forge[AvatarID].Team = TEAM;

			//### Read in Avatar Data from Server
			m_transfer->acRead(Q_Forge->Forge[AvatarID].AV.Xform.GhostTranslation.x);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].AV.Xform.GhostTranslation.y);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].AV.Xform.GhostTranslation.z);

#if 0
			printf("Q_Network::RecieveWorld::: Q_Forge[%i].GhostTranslation x %f y %f z %f\n", AvatarID, Q_Forge->Forge[AvatarID].AV.Xform.GhostTranslation.x, Q_Forge->Forge[AvatarID].AV.Xform.GhostTranslation.y, Q_Forge->Forge[AvatarID].AV.Xform.GhostTranslation.z);
			printf("Q_Network::RecieveWorld:::TWO Q_Forge[%i].Translation x %f y %f z %f\n", AvatarID, Q_Forge->Forge[AvatarID].AV.Xform.Translation.x, Q_Forge->Forge[AvatarID].AV.Xform.Translation.y, Q_Forge->Forge[AvatarID].AV.Xform.Translation.z);
#endif
			m_transfer->acRead(Q_Forge->Forge[AvatarID].AnglesVec.x);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].AnglesVec.y);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].AnglesVec.z);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].Mposestate);		//Avatar Move Pose State
			m_transfer->acRead(Int_Aposestate);		//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].attackon);		//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].WeaponStatus);
			m_transfer->acRead(Int_Mflash);
			if(Int_Mflash == 1 && Q_MFlash->MFlash[AvatarID].SkipFlag == 0) Q_Forge->Forge[AvatarID].MFlash = Int_Mflash;
			m_transfer->acRead(Q_Forge->Forge[AvatarID].Block);			//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].BlockHit);		//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].BlockHeight);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].Crouch);			//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].HitReactScale);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec.x);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec.y);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec.z);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactSpeed);

			m_transfer->acRead(Float_PowerFactor);

			if(Q_Forge->Forge[AvatarID].JINK3_PowerFactor != Float_PowerFactor)
				{
				Q.DeactivateItemsAI(AvatarID);
			
				Q_Forge->Forge[AvatarID].JINK3_PowerFactor = Float_PowerFactor;

				Q.ActivateItemsAI(AvatarID);
				}

			m_transfer->acRead(m_Energy);
			m_EnergyGAIN = m_Energy - Q_Forge->Forge[AvatarID].HB_STR_Energy;
			Q_Forge->Forge[AvatarID].HB_Energy += m_EnergyGAIN;
			Q_Forge->Forge[AvatarID].HB_STR_Energy = m_Energy;

			m_transfer->acRead(m_Health);
			m_HealthGAIN = m_Health - Q_Forge->Forge[AvatarID].HB_STR_Health;
			Q_Forge->Forge[AvatarID].HB_Health += m_HealthGAIN;
			Q_Forge->Forge[AvatarID].HB_STR_Health = m_Health;

			m_transfer->acRead(m_Armour);
			m_ArmourGAIN = m_Armour - Q_Forge->Forge[AvatarID].HB_STR_Armour;
			Q_Forge->Forge[AvatarID].HB_Armour += m_ArmourGAIN;
			Q_Forge->Forge[AvatarID].HB_STR_Armour = m_Armour;

			m_transfer->acRead(m_PowerBank);
			m_PowerBankGAIN = m_PowerBank - Q_Forge->Forge[AvatarID].HB_STR_POWERBANK;
			Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK += m_PowerBankGAIN;
			Q_Forge->Forge[AvatarID].HB_STR_POWERBANK = m_PowerBank;
			
			if((Q_Forge->Forge[AvatarID].HB_Health > 0) && (Float_Health <= 0))
				{
				Q_Forge->Forge[AvatarID].HB_Dead = 1;

				jet = 0;
				while(jet < 5)
					{
					Q.PlayerSpawnNNbot(Q_Forge->Forge[AvatarID].AV.Xform.Translation);

					jet++;
					}

				Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AvatarID].RFistPos.Translation);
				}

			Q_Forge->Forge[AvatarID].HB_Health = Float_Health;

			//### Limits - ###
			if(Q_Forge->Forge[AvatarID].HB_Health >= Q_Forge->Forge[AvatarID].HB_MaxHealth) Q_Forge->Forge[AvatarID].HB_Health = Q_Forge->Forge[AvatarID].HB_MaxHealth;
			if(Q_Forge->Forge[AvatarID].HB_Energy >= Q_Forge->Forge[AvatarID].HB_MaxEnergy) Q_Forge->Forge[AvatarID].HB_Energy = Q_Forge->Forge[AvatarID].HB_MaxEnergy;
			if(Q_Forge->Forge[AvatarID].HB_Armour >= Q_Forge->Forge[AvatarID].HB_MaxArmour) Q_Forge->Forge[AvatarID].HB_Armour = Q_Forge->Forge[AvatarID].HB_MaxArmour;
			if(Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK >= ((((float)Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK = ((((float)Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100);

			m_transfer->acRead(Q_Forge->Forge[AvatarID].PlayerMode);

			m_transfer->acRead(Q_Forge->Forge[AvatarID].idleposecnt);		//Avatar Idle Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].runposecnt);		//Avatar Run Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].attposecnt);		//Avatar Attack Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].crohposecnt);		//Avatar Attack Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].jumpposecnt);		//Avatar Attack Pose Counter

			if(Q_Forge->Forge[AvatarID].Aposestate != Int_Aposestate) Q_Forge->Forge[AvatarID].JinkInit = 0;
			else if(Q_Forge->Forge[AvatarID].attposecnt > 0.3 || Q_Forge->Forge[AvatarID].attposecnt == 0) Q_Forge->Forge[AvatarID].JinkInit = 1;

			//### Avatar Attack Pose State
			if(Int_Aposestate == 205) Q_Forge->Forge[AvatarID].EnergySWITCHOFF = 1;

			if(Q_Forge->Forge[AvatarID].EnergySWITCHOFF == 1)
				{
				Q_Forge->Forge[AvatarID].Aposestate = 205;
				Q_Forge->Forge[AvatarID].attackon = 1;
				}
			else Q_Forge->Forge[AvatarID].Aposestate = Int_Aposestate;

			//m_transfer->acRead(Q_Forge->Forge[AvatarID].WallRunCollision.Plane.Normal);

			/*Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*//*&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
			Q_Forge->Forge[AvatarID].TempVec1 = Q_Forge->Forge[AvatarID].AnglesVec;
			Q_Forge->Forge[AvatarID].TempVec1.y = 0;
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvatarID].TempVec1);
			Q_Forge->Forge[AvatarID].Up.y = 0;
			Q_Forge->Forge[AvatarID].ScanTurnAng = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Up);

			//### Check Distance between Pure Left and Right to work out direction of Turn
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Left);
			//Qpo->Transform_AvatarGetUp(/*ORIG GetIn*//*&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
			Qpo->Vec3d_Copy(&Q_Forge->Forge[AvatarID].Left, &Q_Forge->Forge[AvatarID].Right);
			Qpo->Vec3d_Inverse(&Q_Forge->Forge[AvatarID].Right);

			Q_Forge->Forge[AvatarID].ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Left);
			Q_Forge->Forge[AvatarID].ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Right);

			if(Q_Forge->Forge[AvatarID].ScanDistL > Q_Forge->Forge[AvatarID].ScanDistR) Q_Forge->Forge[AvatarID].ScanTurnAng *= -1;

			Q_Forge->Forge[AvatarID].trueAngles.y -= Q_Forge->Forge[AvatarID].ScanTurnAng / 3;

			Q_Forge->Forge[AvatarID].Angles.y -= Q_Forge->Forge[AvatarID].ScanTurnAng / 3;
			if(Q_Forge->Forge[AvatarID].Angles.y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.y = 0;
			if(Q_Forge->Forge[AvatarID].Angles.y < 0) Q_Forge->Forge[AvatarID].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&RotateMatrix, -(Q_Forge->Forge[AvatarID].ScanTurnAng / 3));
			Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &RotateMatrix, &Q_Forge->Forge[AvatarID].AV.Xform);*/

			//Q_Forge->Forge[AvatarID].AV.Xform.Matrix = Q_Forge->Forge[AvatarID].AV.STR_Xform.Matrix;

			//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AvatarID].AnglesChg.y);
			//Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);

			Q_Forge->Forge[AvatarID].AV.Xform.Matrix = Q_Forge->Forge[AvatarID].STOREMatrix.Matrix;

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AvatarID].QNetAngles.y);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);

			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].AV.Up);

			Q_Forge->Forge[AvatarID].AV.Up.y = 0;
			Q_Forge->Forge[AvatarID].AnglesVec.y = 0;

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[AvatarID].AV.Up, &Q_Forge->Forge[AvatarID].AnglesVec, &ScanTurnVec);
			Q_Forge->Forge[AvatarID].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
			Q_Forge->Forge[AvatarID].ScanTurnAng /= 3; //2

			//### Check Distance between Pure Left and Right to work out direction of Turn
			//QpoVec3d f_UPP, LeftToRightESCAN;
			//f_UPP.x = 0;
			//f_UPP.y = 1;
			//f_UPP.z = 0;
			//Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AvatarID].AnglesVec, &f_UPP, &LeftToRightESCAN);

			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AvatarID].AV.Xform, &qLeftToRightESCAN);

			qLeftToRightESCAN.y = 0;

			Qpo->Vec3d_Copy(&qLeftToRightESCAN, &Q_Forge->Forge[AvatarID].AV.Left);
			Qpo->Vec3d_Copy(&qLeftToRightESCAN, &Q_Forge->Forge[AvatarID].AV.Right);
			Qpo->Vec3d_Inverse(&Q_Forge->Forge[AvatarID].AV.Right);

			ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].AnglesVec, &Q_Forge->Forge[AvatarID].AV.Left);
			ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].AnglesVec, &Q_Forge->Forge[AvatarID].AV.Right);

#if 0
			TempVec2.x = Q_Forge->Forge[AvatarID].AV.Xform.Translation.z;
			TempVec2.x = Q_Forge->Forge[AvatarID].AV.Xform.Translation.y;
			TempVec2.x = Q_Forge->Forge[AvatarID].AV.Xform.Translation.z;

	Qpo->Camera_Set();
	glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AV.Left.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AV.Left.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AV.Left.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AV.Right.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AV.Right.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AV.Right.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AnglesVec.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AnglesVec.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AnglesVec.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 1.0f, 1.0f);	//BLUE
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (ScanTurnVec.x * 250), TempVec2.y + (ScanTurnVec.y * 250), TempVec2.z + (ScanTurnVec.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 1.0f);	//BLUE
	//*glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AV.Up.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AV.Up.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AV.Up.z * 250));
	//*glEnd();
#endif

			if(ScanDistL < ScanDistR) Q_Forge->Forge[AvatarID].ScanTurnAng *= -1;

			Q_Forge->Forge[AvatarID].trueAngles.y += Q_Forge->Forge[AvatarID].ScanTurnAng;

			Q_Forge->Forge[AvatarID].Angles.y += Q_Forge->Forge[AvatarID].ScanTurnAng;
			if(Q_Forge->Forge[AvatarID].Angles.y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.y -= (PI*2);
			if(Q_Forge->Forge[AvatarID].Angles.y < 0) Q_Forge->Forge[AvatarID].Angles.y = (PI*2) - Q_Forge->Forge[AvatarID].Angles.y;

			Q_Forge->Forge[AvatarID].QNetAngles.y += Q_Forge->Forge[AvatarID].ScanTurnAng;
			if(Q_Forge->Forge[AvatarID].QNetAngles.y > (PI*2)) Q_Forge->Forge[AvatarID].QNetAngles.y -= (PI*2);
			if(Q_Forge->Forge[AvatarID].QNetAngles.y < 0) Q_Forge->Forge[AvatarID].QNetAngles.y = (PI*2) - Q_Forge->Forge[AvatarID].QNetAngles.y;

			//Q_Forge->Forge[AvatarID].AnglesChg.y += Q_Forge->Forge[AvatarID].ScanTurnAng;
			//if(Q_Forge->Forge[AvatarID].AnglesChg.y > (PI*2)) Q_Forge->Forge[AvatarID].AnglesChg.y -= (PI*2);
			//if(Q_Forge->Forge[AvatarID].AnglesChg.y < 0) Q_Forge->Forge[AvatarID].AnglesChg.y += (PI*2);

			//Q_Forge->Forge[AvatarID].AV.Xform.Matrix = Q_Forge->Forge[AvatarID].AV.STR_Xform.Matrix;

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AvatarID].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);
			}
		else
			{	
			player[g_Player]->Team = TEAM;

				//Player in Hit Reactions
			if(Q_Forge->Forge[AvatarID].HitReactionGB == 1)
				{
				//### Get Player Data
				m_transfer->acRead(playerAV[g_Player]->Xform.Translation.x);				//Avatar Position
				m_transfer->acRead(playerAV[g_Player]->Xform.Translation.y);
				m_transfer->acRead(playerAV[g_Player]->Xform.Translation.z);

				//#### - Player Angle ####//
				m_transfer->acRead(player[g_Player]->AnglesVec.x);
				m_transfer->acRead(player[g_Player]->AnglesVec.y);
				m_transfer->acRead(player[g_Player]->AnglesVec.z);

				Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &playerAV[g_Player]->Up);
				Qpo->Vec3d_Inverse(&playerAV[g_Player]->Up);
				player[g_Player]->TempVec1 = player[g_Player]->AnglesVec;
				Qpo->Vec3d_Normalize(&player[g_Player]->TempVec1);
				player[g_Player]->TempVec1.y = 0;
				playerAV[g_Player]->Up.y = 0;
				player[g_Player]->ReactTurnAng = Qpo->Vec3d_DistanceBetween(&player[g_Player]->TempVec1, &playerAV[g_Player]->Up);

				//### Check Distance between Pure Left and Right to work out direction of Turn
				Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &playerAV[g_Player]->Left);
				Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&playerAV[g_Player]->Up);
				Qpo->Vec3d_Copy(&playerAV[g_Player]->Left, &playerAV[g_Player]->Right);
				Qpo->Vec3d_Inverse(&playerAV[g_Player]->Right);

				player[g_Player]->ScanDistL = Qpo->Vec3d_DistanceBetween(&player[g_Player]->TempVec1, &playerAV[g_Player]->Left);
				player[g_Player]->ScanDistR = Qpo->Vec3d_DistanceBetween(&player[g_Player]->TempVec1, &playerAV[g_Player]->Right);

				if(player[g_Player]->ScanDistL > player[g_Player]->ScanDistR) player[g_Player]->ReactTurnAng *= -1;

				player[g_Player]->trueAngles.y += player[g_Player]->ReactTurnAng / 3;

				player[g_Player]->AvatarRotation += player[g_Player]->ReactTurnAng / 3;
				if(player[g_Player]->AvatarRotation>(2*PI)) player[g_Player]->AvatarRotation=player[g_Player]->AvatarRotation-(PI*2);

				player[g_Player]->Angles.y += player[g_Player]->ReactTurnAng / 3;
				if(player[g_Player]->Angles.y > (PI*2)) player[g_Player]->Angles.y = 0;
				if(player[g_Player]->Angles.y < 0) player[g_Player]->Angles.y = (PI*2);

				Qpo->Transform_New_YRotation(&RotateMatrix, player[g_Player]->ReactTurnAng / 3);
				Qpo->Transform_Multiply(&playerAV[g_Player]->Xform, &RotateMatrix, &playerAV[g_Player]->Xform);

				m_transfer->acRead(player[g_Player]->Mposestate);		//Avatar Move Pose State
				m_transfer->acRead(player[g_Player]->Aposestate);		//Avatar Attack Pose State
				m_transfer->acRead(player[g_Player]->attackon);		//Avatar Attack Pose State
				m_transfer->acRead(player[g_Player]->WeaponStatus);
				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueINT);			//Avatar Attack Pose State
				m_transfer->acRead(player[g_Player]->BlockHit);		//Avatar Attack Pose State
				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueINT);			//Avatar Attack Pose State
				m_transfer->acRead(player[g_Player]->HitReactScale);
				m_transfer->acRead(player[g_Player]->MoveReactVec.x);
				m_transfer->acRead(player[g_Player]->MoveReactVec.y);
				m_transfer->acRead(player[g_Player]->MoveReactVec.z);
				m_transfer->acRead(player[g_Player]->MoveReactSpeed);
				m_transfer->acRead(m_ValueFLT);

				m_transfer->acRead(m_Energy);
				m_EnergyGAIN = m_Energy - player[g_Player]->HB_STR_Energy;
				player[g_Player]->HB_Energy += m_EnergyGAIN;
				player[g_Player]->HB_STR_Energy = m_Energy;

				m_transfer->acRead(m_Health);
				m_HealthGAIN = m_Health - player[g_Player]->HB_STR_Health;
				Float_Health += m_HealthGAIN;
				player[g_Player]->HB_STR_Health = m_Health;

				m_transfer->acRead(m_Armour);
				m_ArmourGAIN = m_Armour - player[g_Player]->HB_STR_Armour;
				player[g_Player]->HB_Armour += m_ArmourGAIN;
				player[g_Player]->HB_STR_Armour = m_Armour;

				m_transfer->acRead(m_PowerBank);
				m_PowerBankGAIN = m_PowerBank - player[g_Player]->HB_STR_POWERBANK;
				Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK += m_PowerBankGAIN;
				player[g_Player]->HB_STR_POWERBANK = m_PowerBank;
			
				if((player[g_Player]->HB_Health > 0) && (Float_Health <= 0))
					{
					player[g_Player]->HB_Dead = 1;

					jet = 0;
					while(jet < 5)
						{
						Q.PlayerSpawnNNbot(playerAV[g_Player]->Xform.Translation);

						jet++;
						}

					Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
					}

				player[g_Player]->HB_Health = Float_Health;

				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueFLT);		//Avatar Idle Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Run Pose Counter
				m_transfer->acRead(player[g_Player]->attposecnt);		//Avatar Attack Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Attack Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Attack Pose Counter
				}
			else
				{
				Q_Forge->Forge[AvatarID].LIVE = 0;

				//###Get Player Data to Client
				m_transfer->acRead(m_ValueQPO.x);				//Avatar Position
				m_transfer->acRead(m_ValueQPO.y);
				m_transfer->acRead(m_ValueQPO.z);
				m_transfer->acRead(m_ValueQPO.x);
				m_transfer->acRead(m_ValueQPO.y);
				m_transfer->acRead(m_ValueQPO.z);
				m_transfer->acRead(m_ValueINT);		//Avatar Move Pose State
				m_transfer->acRead(m_ValueINT);		//Avatar Attack Pose State
				m_transfer->acRead(m_ValueINT);		//Avatar Attack Pose State
				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueINT);			//Avatar Attack Pose State
				m_transfer->acRead(m_ValueINT);		//Avatar Attack Pose State
				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueINT);			//Avatar Attack Pose State
				m_transfer->acRead(m_ValueFLT);
				m_transfer->acRead(m_ValueQPO.x);
				m_transfer->acRead(m_ValueQPO.y);
				m_transfer->acRead(m_ValueQPO.z);
				m_transfer->acRead(m_ValueFLT);
				m_transfer->acRead(m_ValueFLT);

				m_transfer->acRead(m_Energy);
				m_EnergyGAIN = m_Energy - player[g_Player]->HB_STR_Energy;
				player[g_Player]->HB_Energy += m_EnergyGAIN;
				player[g_Player]->HB_STR_Energy = m_Energy;

				m_transfer->acRead(m_Health);
				m_HealthGAIN = m_Health - player[g_Player]->HB_STR_Health;
				Float_Health += m_HealthGAIN;
				player[g_Player]->HB_STR_Health = m_Health;

				m_transfer->acRead(m_Armour);
				m_ArmourGAIN = m_Armour - player[g_Player]->HB_STR_Armour;
				player[g_Player]->HB_Armour += m_ArmourGAIN;
				player[g_Player]->HB_STR_Armour = m_Armour;

				m_transfer->acRead(m_PowerBank);
				m_PowerBankGAIN = m_PowerBank - player[g_Player]->HB_STR_POWERBANK;
				Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK += m_PowerBankGAIN;
				player[g_Player]->HB_STR_POWERBANK = m_PowerBank;

				if((player[g_Player]->HB_Health > 0) && (Float_Health <= 0))
					{
					player[g_Player]->HB_Dead = 1;

					jet = 0;
					while(jet < 5)
						{
						Q.PlayerSpawnNNbot(playerAV[g_Player]->Xform.Translation);

						jet++;
						}

					Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
					}

				player[g_Player]->HB_Health = Float_Health;
				
				m_transfer->acRead(m_ValueINT);
				m_transfer->acRead(m_ValueFLT);		//Avatar Idle Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Run Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Attack Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Attack Pose Counter
				m_transfer->acRead(m_ValueFLT);		//Avatar Attack Pose Counter
				}
			}

		wb_helly++;
		}

	//##### Update Q_Object->ObjectS
	m_transfer->acRead(_->NomQObject);

	if(_->NomQObject > 25) _->NomQObject = 25;

	wb_aero = 0;
	while(wb_aero < _->NomQObject)
		{
		if(wb_aero >= 0 && wb_aero < 150) m_transfer->acRead(Q_Object->Object[wb_aero].StrengthBANK);
		
		wb_aero++;
		}


	//#### Update Bullets
	if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
	
	for(int f_Scan = 500; f_Scan < QAA_NET_ARRAY_MAX; f_Scan++)
		{
		Q_Bullet->Bullet[f_Scan].Live = 0;
		}

	m_transfer->acRead(m_VectorSelfID);
	m_transfer->acRead(m_NomBulletSTR);

	while(m_Recieve == 1)
		{
		if(!m_transfer->acRead(wb_aero)) m_Recieve = 0;			//Array Position
		else
			{
			if(wb_aero != -5 && wb_aero >= 0 && wb_aero < QAA_NET_ARRAY_MAX)
				{
				mf_DestID = wb_aero;
				Q_Bullet->Bullet[mf_DestID].NetFlag = 1;
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].Live);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AvID);		//Avatar Attack Pose State
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].TrajVec);	//Trajectory Vector
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].WorldPos);	//Avatar Move Pose State
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].Speed);		//Avatar Attack Pose State
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].ORIGPos);	//Avatar Attack Pose State
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].ZSpin);
				/*m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[0][0]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[0][1]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[0][2]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[1][0]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[1][1]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[1][2]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[2][0]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[2][1]);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[2][2]);*/
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Translation);
				m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].JDamageLVL);

				if(Q_Bullet->Bullet[mf_DestID].AvID == m_VectorSelfID) Q_Bullet->Bullet[mf_DestID].Live = 0;
				else _->NomBulletPRPR = mf_DestID + 1;

				if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
				}
			else m_Recieve = 0;
			}
		}

#if 1
	//#### Update Bullet Hits
	if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

	/*for(int f_Scan = 500; f_Scan < 2500; f_Scan++)
		{
		Q_BulletHit->BulletHit[f_Scan].Live = 0;
		}*/

	while(m_Recieve == 1)
		{
		m_transfer->acRead(wb_aero);
		
		if(wb_aero != -5 && wb_aero >= 0 && wb_aero < QAA_NET_ARRAY_MAX)
			{
			mf_DestID = wb_aero;
			
			Q_BulletHit->BulletHit[mf_DestID].NetFlag = 1;
			
			int f_Live = Q_BulletHit->BulletHit[mf_DestID].Live;
			
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].Live);
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].Init);
			
			if(f_Live == 0 && Q_BulletHit->BulletHit[mf_DestID].Live == 1)
				{
				Q_BulletHit->BulletHit[mf_DestID].Init = 0;
				}
			else
				{
				Q_BulletHit->BulletHit[mf_DestID].Init = 1;
				}

			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].EffectType);
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].AvID);
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].AvatarHITID);

			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].BulletDMG);
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].BulletPWR);

			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].Pos);
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].BulletTraj);
			m_transfer->acRead(Q_BulletHit->BulletHit[mf_DestID].CollNormal);
			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			if(Q_BulletHit->BulletHit[mf_DestID].AvID == m_VectorSelfID) Q_Bullet->Bullet[mf_DestID].Live = 0;
			else _->NomBulHitPRPR = mf_DestID + 1;
			}
		else m_Recieve = 0;
		}

	/*m_transfer->acRead(player[g_Player]->NetUPDATE.NomBulHit);

	if(player[g_Player]->NetUPDATE.NomBulHit < _->NomBulHit)
		{
		wb_aero = player[g_Player]->NetUPDATE.NomBulHit;
		while(wb_aero < _->NomBulHit)
			{
			Q_BulletHit->BulletHit[wb_aero].Scale = 1;
			Q_BulletHit->BulletHit[wb_aero].Live = 0;
			Q_BulletHit->BulletHit[wb_aero].Init = 0;
			wb_aero++;
			}
		}

	_->NomBulHit = player[g_Player]->NetUPDATE.NomBulHit;*/

	//MessageBox(NULL,"Melee Hits  \n","ERROR",MB_OK);

	//#### Update Melee Hits
	if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
	
	/*for(int f_Scan = 500; f_Scan < 2500; f_Scan++)
		{
		Q_MeleeHit->MeleeHit[f_Scan].Live = 0;
		}*/

	while(m_Recieve == 1)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5 && wb_aero >= 0 && wb_aero < QAA_NET_ARRAY_MAX)
			{
			//printf("melee hit ! aero %i\n", wb_aero);
			mf_DestID = wb_aero;
			Q_MeleeHit->MeleeHit[mf_DestID].NetFlag = 1;

			int f_Live = Q_MeleeHit->MeleeHit[mf_DestID].Live;

			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Live);
			
			if(f_Live == 0 && Q_MeleeHit->MeleeHit[mf_DestID].Live == 1)
				{
				Q_MeleeHit->MeleeHit[mf_DestID].INIT = 0;
				//printf("melee hit %i INIT SET\n", wb_aero);
				}
			else
				{
				Q_MeleeHit->MeleeHit[mf_DestID].INIT = 1;
				}

			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].HitTYPE);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].HitRESULT);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AvID);

			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Impact);
			//printf("melee hit %i Q_MeleeHit->MeleeHit[mf_DestID].Impact %f %f %f\n", wb_aero, Q_MeleeHit->MeleeHit[mf_DestID].Impact.m_X, Q_MeleeHit->MeleeHit[mf_DestID].Impact.m_Y, Q_MeleeHit->MeleeHit[mf_DestID].Impact.m_Z);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Bonenum);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].ReactionNorm);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].HitPowerPercent);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].BloodAmt);
			//printf("melee hit %i BloodAmt %i\n", Q_MeleeHit->MeleeHit[mf_DestID].BloodAmt);

			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Expandro3D.Radius);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Expandro3D.MaxRadius);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Expandro3D.StartFade);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Expandro3D.Red);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Expandro3D.Green);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].Expandro3D.Blue);

			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttackSTRENGTH);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttackSNAP);

			/*m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[0][0]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[0][1]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[0][2]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[1][0]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[1][1]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[1][2]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[2][0]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[2][1]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Matrix.m[2][2]);*/
			m_transfer->acRead(Q_MeleeHit->MeleeHit[mf_DestID].AttboneXF.Translation);
			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
			
			if(Q_MeleeHit->MeleeHit[mf_DestID].AvID == m_VectorSelfID) Q_MeleeHit->MeleeHit[mf_DestID].Live = 0;
			else _->NomMelHitPRPR = mf_DestID + 1;
			}
		else m_Recieve = 0;
		}

#if 0
	if(player[g_Player]->NetUPDATE.NomMelHit < _->NomMelHit)
		{
		wb_aero = player[g_Player]->NetUPDATE.NomMelHit;
		while(wb_aero < _->NomMelHit)
			{
			Q_MeleeHit->MeleeHit[wb_aero].Live = 0;
			Q_MeleeHit->MeleeHit[wb_aero].INIT = 0;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius = 301;
			Qpo->Light_Remove(Q_MeleeHit->MeleeHit[wb_aero].Light);
			wb_aero++;
			}
		}
#endif

	//##### Update Small Energy
	if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
	
	/*for(int f_Scan = 500; f_Scan < 2500; f_Scan++)
		{
		Q_SEnergy->SEnergy[f_Scan].Live = 0;
		}*/

	while(m_Recieve == 1)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5 && wb_aero >= 0 && wb_aero < QAA_NET_ARRAY_MAX)
			{
			mf_DestID = wb_aero;
			Q_SEnergy->SEnergy[mf_DestID].NetFlag = 1;

			int f_Live = Q_SEnergy->SEnergy[mf_DestID].Live;

			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].Live);

			if(f_Live == 0 && Q_SEnergy->SEnergy[mf_DestID].Live == 1)
				{
				Q_SEnergy->SEnergy[mf_DestID].Init = 0;
				}
			else
				{
				Q_SEnergy->SEnergy[mf_DestID].Init = 1;
				}

			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].LightPos);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].TraVec);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].Speed);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].Scale);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].Alpha);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].TargetLock);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].TargetID);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].AngleX);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].AngleY);
			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].AngleZ);
			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
			
			if(Q_SEnergy->SEnergy[mf_DestID].AvID == m_VectorSelfID) Q_SEnergy->SEnergy[mf_DestID].Live = 0;
			else _->NomSEnergyPRPR = mf_DestID + 1;
			}
		else m_Recieve = 0;
		}

	/*m_transfer->acRead(player[g_Player]->NetUPDATE.NomSEnergy);

	if(player[g_Player]->NetUPDATE.NomSEnergy < _->NomSEnergy)
		{
		g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID = _->NomSEnergy - 1;
		while(g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID >= player[g_Player]->NetUPDATE.NomSEnergy)
			{
			Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Live = 0;
			if(Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Light);
			//if(Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Sound != NULL) geSound_StopSound(SoundSys, Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].Sound);

			wb_helly = 0;
			while(wb_helly < Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].NomActors)
				{
				Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID].AvatarFlag[wb_helly].Xform.Translation);
				wb_helly++;
				}

			g_Domain[0].vec_entity_Avatar[0][wb_jet]->m_AvatarID--;
			}
		}

	_->NomSEnergy = player[g_Player]->NetUPDATE.NomSEnergy;*/

	//MessageBox(NULL,"Large Energy  \n","ERROR",MB_OK);

	//##### Update Large Energy
	if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
	
	/*for(int f_Scan = 500; f_Scan < 2500; f_Scan++)
		{
		Q_LEnergy->LEnergy[f_Scan].Live = 0;
		}*/

	while(m_Recieve == 1)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5 && wb_aero >= 0 && wb_aero < QAA_NET_ARRAY_MAX)
			{
			mf_DestID = wb_aero;
			Q_LEnergy->LEnergy[mf_DestID].NetFlag = 1;

			int f_Live = Q_LEnergy->LEnergy[mf_DestID].Live;

			m_transfer->acRead(Q_SEnergy->SEnergy[mf_DestID].Live);

			if(f_Live == 0 && Q_LEnergy->LEnergy[mf_DestID].Live == 1)
				{
				Q_LEnergy->LEnergy[mf_DestID].Init = 0;
				}
			else
				{
				Q_LEnergy->LEnergy[mf_DestID].Init = 1;
				}

			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].LightPos);
			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].TraVec);
			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].Speed);
			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].Scale);
			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].Alpha);
			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].EnergyLive);
			m_transfer->acRead(Q_LEnergy->LEnergy[mf_DestID].EnergyFire);
			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;			
			
			if(Q_LEnergy->LEnergy[mf_DestID].AvID == m_VectorSelfID) Q_LEnergy->LEnergy[mf_DestID].Live = 0;
			else _->NomLEnergyPRPR = mf_DestID + 1;
			}
		else m_Recieve = 0;
		}

	/*m_transfer->acRead(player[g_Player]->NetUPDATE.NomLEnergy);

	if(player[g_Player]->NetUPDATE.NomLEnergy < _->NomLEnergy)
		{
		wb_jet = _->NomLEnergy - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomLEnergy)
			{
			Qpo->Light_Remove(Q_LEnergy->LEnergy[wb_jet].Light);
			Q_LEnergy->LEnergy[wb_jet].Init = 0;
			Q_LEnergy->LEnergy[wb_jet].Live = 0;
			Q_LEnergy->LEnergy[wb_jet].EnergyLive = 0;
			Q_LEnergy->LEnergy[wb_jet].EnergyFire = 0;
			Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[wb_jet].EnergyBall.Xform.Translation);
			Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[wb_jet].EnergyBall, 0,0,0);

			wb_jet--;
			}
		}

	_->NomLEnergy = player[g_Player]->NetUPDATE.NomLEnergy;*/

	//MessageBox(NULL,"World Explosions  \n","ERROR",MB_OK);

	//##### Update World Explosions
	if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
	
	/*for(int f_Scan = 500; f_Scan < 2500; f_Scan++)
		{
		Q_Explosion->Explosion[f_Scan].Live = 0;
		}*/

	while(m_Recieve == 1)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5 && wb_aero >= 0 && wb_aero < QAA_NET_ARRAY_MAX)
			{
			mf_DestID = wb_aero;
			Q_Explosion->Explosion[mf_DestID].NetFlag = 1;

			int f_Live = Q_Explosion->Explosion[mf_DestID].Live;

			m_transfer->acRead(Q_Explosion->Explosion[mf_DestID].Live);

			if(f_Live == 0 && Q_Explosion->Explosion[mf_DestID].Live == 1)
				{
				Q_Explosion->Explosion[mf_DestID].Init = 0;
				}
			else
				{
				Q_Explosion->Explosion[mf_DestID].Init = 1;
				}

			m_transfer->acRead(Q_Explosion->Explosion[mf_DestID].Pos);
			m_transfer->acRead(Q_Explosion->Explosion[mf_DestID].ExpSize);
			m_transfer->acRead(Q_Explosion->Explosion[mf_DestID].LargeEnergyAvID);
			m_transfer->acRead(Q_Explosion->Explosion[mf_DestID].CollPlaneNormal);

			if(Q_Explosion->Explosion[mf_DestID].AvID == m_VectorSelfID) Q_Explosion->Explosion[mf_DestID].Live = 0;
			else _->NomExplosionsPRPR = mf_DestID + 1;
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(player[g_Player]->NetUPDATE.NomExplosions);

	//if(player[g_Player]->NetUPDATE.NomExplosions >= _->NomExplosions)
	//	{ _->NomExplosions = player[g_Player]->NetUPDATE.NomExplosions; }

	//MessageBox(NULL,"Cleric Heal  \n","ERROR",MB_OK);

	//##### Update Cleric Heal Energy
	/***IMU***m_transfer->acRead(player[g_Player]->NetUPDATE.NomHSpark);

	if(player[g_Player]->NetUPDATE.NomHSpark < _->NomHSpark)
		{
		wb_jet = _->NomHSpark - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomHSpark)
			{
			Q_HealSpark->HealSpark[wb_jet].Live = 0;
			if(Q_HealSpark->HealSpark[wb_jet].Light != NULL) Qpo->Light_Remove(Q_HealSpark->HealSpark[wb_jet].Light);
			Q_HealSpark->HealSpark[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomHSpark = player[g_Player]->NetUPDATE.NomHSpark;

	wb_aero = 0;
	while(wb_aero < _->NomHSpark)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HTYPE);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Pos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].TraVec);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Released);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Absorbed);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].AlpFade);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].ScaleSTR);

		if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live == 1)
			{
			Q_HealSpark->HealSpark[wb_aero].Live = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live;
			Q_HealSpark->HealSpark[wb_aero].HTYPE = player[g_Player]->NetUPDATE.HealSparks[wb_aero].HTYPE;
			Q_HealSpark->HealSpark[wb_aero].Pos = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Pos;
			Q_HealSpark->HealSpark[wb_aero].TraVec = player[g_Player]->NetUPDATE.HealSparks[wb_aero].TraVec;
			Q_HealSpark->HealSpark[wb_aero].Released = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Released;
			Q_HealSpark->HealSpark[wb_aero].Absorbed = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Absorbed;

			Q_HealSpark->HealSpark[wb_aero].HealTarget = player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget;
			if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_HealSpark->HealSpark[wb_aero].HealTarget = 250;
			if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget == 250) Q_HealSpark->HealSpark[wb_aero].HealTarget = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			Q_HealSpark->HealSpark[wb_aero].AlpFade = player[g_Player]->NetUPDATE.HealSparks[wb_aero].AlpFade;
			Q_HealSpark->HealSpark[wb_aero].ScaleSTR = player[g_Player]->NetUPDATE.HealSparks[wb_aero].ScaleSTR;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Spells  \n","ERROR",MB_OK);

	//##### Update Cleric Spells
	m_transfer->acRead(player[g_Player]->NetUPDATE.NomSpell);

	if(player[g_Player]->NetUPDATE.NomSpell < _->NomSpell)
		{
		wb_jet = _->NomSpell - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomSpell)
			{
			Q_ClericSpell->ClericSpell[wb_jet].Live = 0;
			if(Q_ClericSpell->ClericSpell[wb_jet].Light != NULL) Qpo->Light_Remove(Q_ClericSpell->ClericSpell[wb_jet].Light);
			Q_ClericSpell->ClericSpell[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomSpell = player[g_Player]->NetUPDATE.NomSpell;

	wb_aero = 0;
	while(wb_aero < _->NomSpell)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].NumSpheres);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPow);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Absorbed);
		
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[0]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[1]);
		
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[0]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[1]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[0]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[0]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[1]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[1]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[2]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[2]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[3]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[3]);


		if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live == 1)
			{
			Q_ClericSpell->ClericSpell[wb_aero].Live = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live;
			Q_ClericSpell->ClericSpell[wb_aero].NumSpheres = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].NumSpheres;

			Q_ClericSpell->ClericSpell[wb_aero].HealTarget = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget;
			if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_ClericSpell->ClericSpell[wb_aero].HealTarget = 250;
			if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget == 250) Q_ClericSpell->ClericSpell[wb_aero].HealTarget = Q_Netplayer->Netplayer[0].LocalCONTROLID;
			
			Q_ClericSpell->ClericSpell[wb_aero].LightPos = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPos;
			Q_ClericSpell->ClericSpell[wb_aero].LightPow = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPow;
			Q_ClericSpell->ClericSpell[wb_aero].Absorbed = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Absorbed;
			
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Radius = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Radius = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].StartFade = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].StartFade = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[0];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[1];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[2];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[2];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[3];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[3];
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Plasma  \n","ERROR",MB_OK);

	//##### Update Cleric Plasma
	m_transfer->acRead(player[g_Player]->NetUPDATE.NomPlasma);

	if(player[g_Player]->NetUPDATE.NomPlasma < _->NomPlasma)
		{
		wb_jet = _->NomPlasma - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomPlasma)
			{
			Q_ClericPlasma->ClericPlasma[wb_jet].Live = 0;
			if(Q_ClericPlasma->ClericPlasma[wb_jet].Light != NULL) Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[wb_jet].Light);
			Q_ClericPlasma->ClericPlasma[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomPlasma = player[g_Player]->NetUPDATE.NomPlasma;

	wb_aero = 0;
	while(wb_aero < _->NomPlasma)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Pos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].TraVec);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Speed);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Alpha);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].PartType);

		if(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live == 1)
			{
			Q_ClericPlasma->ClericPlasma[wb_aero].Live = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live;
			Q_ClericPlasma->ClericPlasma[wb_aero].Pos = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Pos;
			Q_ClericPlasma->ClericPlasma[wb_aero].TraVec = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].TraVec;
			Q_ClericPlasma->ClericPlasma[wb_aero].Speed = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Speed;
			Q_ClericPlasma->ClericPlasma[wb_aero].Alpha = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Alpha;
			Q_ClericPlasma->ClericPlasma[wb_aero].PartType = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].PartType;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Net Effects Control  \n","ERROR",MB_OK);

	//##### Update Net Effects Control
	m_transfer->acRead(player[g_Player]->NetUPDATE.NomNetEffectControl);

	_->NomNetEffectControl = player[g_Player]->NetUPDATE.NomNetEffectControl;

	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type);
		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type == 0) m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Pos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Effintensity);
		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type == 1) m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].AvID);

		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live > Q_NetEffectControl->NetEffectControl[wb_aero].Live)
			{ Q_NetEffectControl->NetEffectControl[wb_aero].Active = 1; }

		Q_NetEffectControl->NetEffectControl[wb_aero].Live = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live;
		Q_NetEffectControl->NetEffectControl[wb_aero].Type = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type;
		Q_NetEffectControl->NetEffectControl[wb_aero].Pos = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Pos;
		Q_NetEffectControl->NetEffectControl[wb_aero].Effintensity = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Effintensity;
		Q_NetEffectControl->NetEffectControl[wb_aero].AvID = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].AvID;

		wb_aero++;
		}*/

#if 0
	//##### Update Net Zone Increment
	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].AVID);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Maxs);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Mins);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMINS);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMAXS);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandSTRENGTH);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_TimeScale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Gravity);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LifeINC);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyINC);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_intBoost);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyEff);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Height);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Weight);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Strength);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Quickness);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Dexterity);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Constitution);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_AggPower);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_DefPower);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPAccuracy);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPDrawSPD);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPReloadSPD);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPRecoilHR);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKmovespeed);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKpower);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINK3intensity);


			//====---- AQUIRE ZONE ----====
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].AVID;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Mins;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Maxs;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMINS;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMAXS;

			//### FIND CORE
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
			Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
			Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

			//### EXPAND OUTWARDS MINS AND MAXS
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
			Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
			Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
			Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
			Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandSTRENGTH;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4];

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_TimeScale;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Gravity;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LifeINC;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyINC;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_intBoost;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyEff;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Height;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Weight;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Strength;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Quickness;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Dexterity;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Constitution;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_AggPower;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_DefPower;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPAccuracy;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPDrawSPD;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPReloadSPD;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPRecoilHR;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKmovespeed;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKpower;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINK3intensity;

			Corner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
			DX = TempVec1;
			DX.y = 0;
			DX.z = 0;
			DY = TempVec1;
			DY.x = 0;
			DY.z = 0;
			DZ = TempVec1;
			DZ.y = 0;
			DZ.x = 0;
			//Q.DrawOrientedBoundBox(&Corner, &DX, &DY, &DZ);

			//if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998) Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;

			//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
			//geSound_PlaySoundDef(SoundSys, Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, GE_false);

			if(wb_aero >= Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks && wb_aero < 9997)
				{
				Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks = wb_aero + 1;
				}
			}
		else m_Recieve = 0;
		}


	//##### Update Net Zone ENTITY Increment
	
	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ID);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ZoneID);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].QObjID);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Range);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].StrengthMAX);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].CollisionTYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].AvID);

			switch(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].TYPE)
				{
				case 0:
					{
					//====----- SENTRY BUILD ------====

					if(_->NomBMSentry < 148)
						{
						Q_BMSentry->BMSentry[_->NomBMSentry].Pos = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos;
						Q_BMSentry->BMSentry[_->NomBMSentry].ZoneID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ZoneID;
						Q_BMSentry->BMSentry[_->NomBMSentry].QObjID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].QObjID;
						Q_BMSentry->BMSentry[_->NomBMSentry].Range = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Range;
						Q_BMSentry->BMSentry[_->NomBMSentry].LIVE = 1;

						_->NomBMSentry++;
						}

					//#### INITIALISE THE Q_Object->Object TO HOUSE THE SENTRY

					if(_->NomQObject < 148)
						{
						Q_Object->Object[_->NomQObject].Pos = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos;
						Q_Object->Object[_->NomQObject].Scale = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Scale;
						Q_Object->Object[_->NomQObject].StrengthMAX = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].StrengthMAX;
						Q_Object->Object[_->NomQObject].StrengthBANK = Q_Object->Object[_->NomQObject].StrengthMAX;
						Q_Object->Object[_->NomQObject].CollisionTYPE = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].CollisionTYPE;
						Q_Object->Object[_->NomQObject].AvID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].AvID;
						Q_Object->Object[_->NomQObject].LIVE = 1;

						_->NomQObject++;
						}

					//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
							//'Jink Ready'
					//geSound_PlaySoundDef(SoundSys, Medias->S_Build, _->Volume, _->Pan, _->S_TimeScale, GE_false);
					}break;
				}

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
			}
		else m_Recieve = 0;
		}
#endif

#if 0
	//FRLs
	m_transfer->acRead(_->FRLtarget);
	m_transfer->acRead(_->FRLON);
	//_->FRLON = 0;
#endif

#endif
}


void Q_Network::ServerRecieveWorld(float Time, unsigned short i_SysIndex)
{
#ifndef WIN32
	float				DeltaTime, MoveTime;
	UInt16				ButtonBits;
	int					AvatarID;
	int					ServerIdent;
	QpoVec3d			BufferCheck;

	//##Check Time
	m_transfer->acRead(MoveTime);
	
	//###### Update Player #####
	//###Get Player Data to Client
	/***IMU***m_transfer->acRead(playerAV[g_Player]->Xform.Translation);
	m_transfer->acRead(player[g_Player]->Mposestate);
	m_transfer->acRead(Int_Aposestate);
	m_transfer->acRead(player[g_Player]->attackon);
	m_transfer->acRead(player[g_Player]->WeaponStatus);
	m_transfer->acRead(Int_Mflash);
	if(Int_Mflash > 0 && Q_MFlash->MFlash[250].SkipFlag == 0) player[g_Player]->MFlash = Int_Mflash;
	m_transfer->acRead(player[g_Player]->Block);
	m_transfer->acRead(player[g_Player]->BlockHit);
	m_transfer->acRead(player[g_Player]->BlockHeight);
	m_transfer->acRead(player[g_Player]->Crouch);
	m_transfer->acRead(player[g_Player]->HitReactScale);
	m_transfer->acRead(player[g_Player]->MoveReactVec);
	m_transfer->acRead(player[g_Player]->MoveReactSpeed);

	m_transfer->acRead(Float_PowerFactor);

	if(player[g_Player]->JINK3_PowerFactor != Float_PowerFactor)
		{
		Q.DeactivateItems();
		
		player[g_Player]->JINK3_PowerFactor = Float_PowerFactor;

		Q.ActivateItems();
		}

	m_transfer->acRead(player[g_Player]->HB_Energy);
	m_transfer->acRead(Float_Health);

	if(player[g_Player]->HB_Health - Float_Health > 8)
		{
		player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

		player[g_Player]->HB_HReduceON = 1;
		player[g_Player]->HB_ReduceHInc = 10;
		player[g_Player]->HB_ReduceHeight = 573;
		player[g_Player]->HB_ReduceRectColor.red = 255;
		player[g_Player]->HB_ReduceRectColor.green = 0;
		player[g_Player]->HB_ReduceRectColor.blue = 0;
		player[g_Player]->HB_ReduceRectColor.alpha = 255;
		}

	if((player[g_Player]->HB_Health > 0) && (Float_Health <= 0))
		{
		//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//geSound_PlaySoundDef(SoundSys, Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, GE_false);
		}

	player[g_Player]->HB_Health = Float_Health;

	m_transfer->acRead(Int_SpecLvlRESET);

	if(Int_SpecLvlRESET != 0 && player[g_Player]->SpecLvlRESET == 0) player[g_Player]->SpecLvlRESET = Int_SpecLvlRESET;
	
	/*if(player[g_Player]->SNDTRIGEnergy == 0)*//***IMU*** m_transfer->acRead(player[g_Player]->SNDTRIGEnergy);
	//else m_transfer->acRead(m_ValueINT);

	m_transfer->acRead(player[g_Player]->PlayerMode);

	m_transfer->acRead(player[g_Player]->idleposecnt);
	m_transfer->acRead(player[g_Player]->runposecnt);
	m_transfer->acRead(player[g_Player]->attposecnt);
	m_transfer->acRead(player[g_Player]->crohposecnt);
	m_transfer->acRead(player[g_Player]->jumpposecnt);

	if(player[g_Player]->Aposestate != Int_Aposestate) player[g_Player]->JinkInit = 0;
	else if(player[g_Player]->attposecnt > 0.3 || player[g_Player]->attposecnt == 0) player[g_Player]->JinkInit = 1;

	if(Int_Aposestate == 205) player[g_Player]->EnergySWITCHOFF = 1;
	if(player[g_Player]->EnergySWITCHOFF == 1)
		{
		player[g_Player]->Aposestate = 205;
		player[g_Player]->attackon = 1;
		}
	else player[g_Player]->Aposestate = Int_Aposestate;

	m_transfer->acRead(player[g_Player]->WallRunCollision.Plane.Normal);*/


	//###### Update ServerPlayer #####
	//###Get Server Player Data to Client
	/***IMU***m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform.Translation);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AnglesVec);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Mposestate);
	m_transfer->acRead(Int_Aposestate);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].attackon);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].WeaponStatus);
	m_transfer->acRead(Int_Mflash);
	if(Int_Mflash == 1 && Q_MFlash->MFlash[Q_Netplayer->Netplayer[0].LocalCONTROLID].SkipFlag == 0) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].MFlash = Int_Mflash;
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Block);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].BlockHit);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].BlockHeight);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Crouch);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HitReactScale);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].MoveReactVec);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].MoveReactSpeed);

	m_transfer->acRead(Float_PowerFactor);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].JINK3_PowerFactor != Float_PowerFactor)
		{
		Q.DeactivateItemsAI(Q_Netplayer->Netplayer[0].LocalCONTROLID);
		
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].JINK3_PowerFactor = Float_PowerFactor;

		Q.ActivateItemsAI(Q_Netplayer->Netplayer[0].LocalCONTROLID);
		}

	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_Energy);
	m_transfer->acRead(Float_Health);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_Health - Float_Health > 8)
		{
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceOld = Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_Health;

		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_HReduceON = 1;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceHInc = 10;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceHeight = 573;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceRectColor.red = 255;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceRectColor.green = 0;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceRectColor.blue = 0;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_ReduceRectColor.alpha = 255;
		}

	if((Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_Health > 0) && (Float_Health <= 0))
		{
		//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//geSound_PlaySoundDef(SoundSys, Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, GE_false);
		}

	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].HB_Health = Float_Health;
	
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].PlayerMode);

	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].idleposecnt);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].runposecnt);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].attposecnt);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].crohposecnt);
	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].jumpposecnt);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Aposestate != Int_Aposestate) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].JinkInit = 0;
	else if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].attposecnt > 0.3 || Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].attposecnt == 0) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].JinkInit = 1;

	if(Int_Aposestate == 205) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].EnergySWITCHOFF = 1;
	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].EnergySWITCHOFF == 1)
		{
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Aposestate = 205;
		Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].attackon = 1;
		}
	else Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Aposestate = Int_Aposestate;

	m_transfer->acRead(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].WallRunCollision.Plane.Normal);

	Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Up);
	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].TempVec1 = Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AnglesVec;
	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].TempVec1.y = 0;
	Qpo->Vec3d_Normalize(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].TempVec1);
	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Up.y = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].TempVec1, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Up);

	//### Check Distance between Pure Left and Right to work out direction of Turn
	Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Left);
	Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Up);
	Qpo->Vec3d_Copy(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Left, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Right);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Right);

	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].TempVec1, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Left);
	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].TempVec1, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Right);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanDistL > Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanDistR) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng *= -1;

	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].trueAngles.y += Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng / 3;

	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.y += Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng / 3;
	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.y > (PI*2)) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.y = 0;
	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.y < 0) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.y = (PI*2);

	Qpo->Transform_New_YRotation(&RotateMatrix, Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng / 3);
	Qpo->Transform_Multiply(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform, &RotateMatrix, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform);

	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].LIVE = 1;*/

	/*//### UPDATE SERVER ANGLES
	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng = player[g_Player]->NetUPDATE.Angle.Y - Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y;
	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y > (PI*2)) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y = 0;
	if(Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y < 0) Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y = (PI*2);

	Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y = Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Angles.Y + Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng;

	geXForm3d_SetZRotation(&AIfriendly, Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].ScanTurnAng);
	Qpo->Transform_Multiply(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform, &AIfriendly, &Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].AV.Xform);*/


	//######  - Other Worldly Avatars -  #####

	//m_transfer->acRead(_->NETNomWorldAvatars);

	//##### Avatar Update Loop
	//wb_helly=0;
	//while(wb_helly < _->NETNomWorldAvatars)
	//	{
		//###### Get Avatars Q_Netplayer->Netplayer #####
		//m_transfer->acRead(AvatarID);

		if(g_map_ClientAvatarID.find(i_SysIndex) == g_map_ClientAvatarID.end())
			{
			printf("Serve Error:::ServerRecieveWorld::: Cannot find System index in g_map_ClientAvatarID\n");
			}
		else
			{
			g_mutex_AvatarID->ac_Sync();
			g_Domain[0].m_vec_IdentList = g_map_ClientAvatarID[i_SysIndex];
			g_mutex_AvatarID->ac_Free();

			g_Domain[0].m_mutexcc_AvatarId->ac_Fire();
			AvatarID = g_Domain[0].m_vec_IdentList->vec_Index[0];
			g_Domain[0].m_mutexcc_AvatarId->ac_Stop();
			}

		//###Get Player Data to Client
		m_transfer->acRead(Q_Forge->Forge[AvatarID].AV.Xform.Translation);				//Avatar Position
		m_transfer->acRead(Q_Forge->Forge[AvatarID].AnglesVec);
		m_transfer->acRead(Q_Forge->Forge[AvatarID].Mposestate);		//Avatar Move Pose State
		m_transfer->acRead(Int_Aposestate);		//Avatar Attack Pose State
		m_transfer->acRead(Q_Forge->Forge[AvatarID].attackon);		//Avatar Attack Pose State
		m_transfer->acRead(Q_Forge->Forge[AvatarID].WeaponStatus);
		m_transfer->acRead(Int_Mflash);
		if(Int_Mflash == 1 && Q_MFlash->MFlash[AvatarID].SkipFlag == 0) Q_Forge->Forge[AvatarID].MFlash = Int_Mflash;
		m_transfer->acRead(Q_Forge->Forge[AvatarID].Block);			//Avatar Attack Pose State
		m_transfer->acRead(Q_Forge->Forge[AvatarID].BlockHit);		//Avatar Attack Pose State
		m_transfer->acRead(Q_Forge->Forge[AvatarID].BlockHeight);
		m_transfer->acRead(Q_Forge->Forge[AvatarID].Crouch);			//Avatar Attack Pose State
		m_transfer->acRead(Q_Forge->Forge[AvatarID].HitReactScale);
		m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec);
		m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactSpeed);

		m_transfer->acRead(Float_PowerFactor);

		if(Q_Forge->Forge[AvatarID].JINK3_PowerFactor != Float_PowerFactor)
			{
			Q.DeactivateItemsAI(AvatarID);
			
			Q_Forge->Forge[AvatarID].JINK3_PowerFactor = Float_PowerFactor;

			Q.ActivateItemsAI(AvatarID);
			}

		m_transfer->acRead(Q_Forge->Forge[AvatarID].HB_Energy);
		m_transfer->acRead(Float_Health);

		if(Q_Forge->Forge[AvatarID].HB_Health - Float_Health > 8)
			{
			Q_Forge->Forge[AvatarID].HB_ReduceOld = Q_Forge->Forge[AvatarID].HB_Health;

			Q_Forge->Forge[AvatarID].HB_HReduceON = 1;
			Q_Forge->Forge[AvatarID].HB_ReduceHInc = 10;
			Q_Forge->Forge[AvatarID].HB_ReduceHeight = 573;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.red = 255;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.green = 0;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.blue = 0;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.alpha = 255;
			}

		if((Q_Forge->Forge[AvatarID].HB_Health > 0) && (Float_Health <= 0))
			{
			//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AvatarID].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
			//geSound_PlaySoundDef(SoundSys, Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, GE_false);
			}

		Q_Forge->Forge[AvatarID].HB_Health = Float_Health;

		m_transfer->acRead(Q_Forge->Forge[AvatarID].PlayerMode);

		m_transfer->acRead(Q_Forge->Forge[AvatarID].idleposecnt);		//Avatar Idle Pose Counter
		m_transfer->acRead(Q_Forge->Forge[AvatarID].runposecnt);		//Avatar Run Pose Counter
		m_transfer->acRead(Q_Forge->Forge[AvatarID].attposecnt);		//Avatar Attack Pose Counter
		m_transfer->acRead(Q_Forge->Forge[AvatarID].crohposecnt);		//Avatar Attack Pose Counter
		m_transfer->acRead(Q_Forge->Forge[AvatarID].jumpposecnt);		//Avatar Attack Pose Counter

		if(Q_Forge->Forge[AvatarID].Aposestate != Int_Aposestate) Q_Forge->Forge[AvatarID].JinkInit = 0;
		else if(Q_Forge->Forge[AvatarID].attposecnt > 0.3 || Q_Forge->Forge[AvatarID].attposecnt == 0) Q_Forge->Forge[AvatarID].JinkInit = 1;

		//### Avatar Attack Pose State
		if(Int_Aposestate == 205) Q_Forge->Forge[AvatarID].EnergySWITCHOFF = 1;
		if(Q_Forge->Forge[AvatarID].EnergySWITCHOFF == 1)
			{
			Q_Forge->Forge[AvatarID].Aposestate = 205;
			Q_Forge->Forge[AvatarID].attackon = 1;
			}
		else Q_Forge->Forge[AvatarID].Aposestate = Int_Aposestate;

		m_transfer->acRead(Q_Forge->Forge[AvatarID].WallRunCollision.Plane.Normal);

		Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
		Q_Forge->Forge[AvatarID].TempVec1 = Q_Forge->Forge[AvatarID].AnglesVec;
		Q_Forge->Forge[AvatarID].TempVec1.y = 0;
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvatarID].TempVec1);
		Q_Forge->Forge[AvatarID].Up.y = 0;
		Q_Forge->Forge[AvatarID].ScanTurnAng = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Up);

		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Left);
		Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
		Qpo->Vec3d_Copy(&Q_Forge->Forge[AvatarID].Left, &Q_Forge->Forge[AvatarID].Right);
		Qpo->Vec3d_Inverse(&Q_Forge->Forge[AvatarID].Right);

		Q_Forge->Forge[AvatarID].ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Left);
		Q_Forge->Forge[AvatarID].ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Right);

		if(Q_Forge->Forge[AvatarID].ScanDistL > Q_Forge->Forge[AvatarID].ScanDistR) Q_Forge->Forge[AvatarID].ScanTurnAng *= -1;

		Q_Forge->Forge[AvatarID].trueAngles.y += Q_Forge->Forge[AvatarID].ScanTurnAng / 3;

		Q_Forge->Forge[AvatarID].Angles.y += Q_Forge->Forge[AvatarID].ScanTurnAng / 3;
		if(Q_Forge->Forge[AvatarID].Angles.y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.y = 0;
		if(Q_Forge->Forge[AvatarID].Angles.y < 0) Q_Forge->Forge[AvatarID].Angles.y = (PI*2);

		Qpo->Transform_New_YRotation(&RotateMatrix, Q_Forge->Forge[AvatarID].ScanTurnAng / 3);
		Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &RotateMatrix, &Q_Forge->Forge[AvatarID].AV.Xform);

		//### UPDATE AVATAR ANGLES
		/*Q_Forge->Forge[AvatarID].ScanTurnAng = Q_Forge->Forge[AvatarID].NetUPDATE.Angle.Y - Q_Forge->Forge[AvatarID].Angles.Y;
		if(Q_Forge->Forge[AvatarID].Angles.Y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.Y = 0;
		if(Q_Forge->Forge[AvatarID].Angles.Y < 0) Q_Forge->Forge[AvatarID].Angles.Y = (PI*2);

		Q_Forge->Forge[AvatarID].Angles.Y = Q_Forge->Forge[_->Multipass].Angles.Y + Q_Forge->Forge[AvatarID].ScanTurnAng;

		geXForm3d_SetZRotation(&AIfriendly, Q_Forge->Forge[AvatarID].ScanTurnAng);
		Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);*/

	//	wb_helly++;
	//	}


	//MessageBox(NULL,"Update 1 Bullets \n","ERROR",MB_OK);


	//##### Update Q_Object->ObjectS
	m_transfer->acRead(_->NomQObject);

	wb_aero = 0;
	while(wb_aero < _->NomQObject)
		{
		m_transfer->acRead(Q_Object->Object[wb_aero].StrengthBANK);
		
		wb_aero++;
		}


	//#### Update Bullets
	m_Recieve = 1;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);								//Array Position

		if(wb_aero != -5)
			{
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AvID);		//Avatar Attack Pose State

			Q_Bullet->Bullet[wb_aero].AvID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].Live);		//Live
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].TrajVec);	//Trajectory Vector
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].WorldPos);	//Avatar Move Pose State
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].Speed);		//Avatar Attack Pose State
		
			//if(player[g_Player]->NetUPDATE.Bullets[wb_aero].AvID == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_Bullet->Bullet[wb_aero].AvID = 250;
			//if(player[g_Player]->NetUPDATE.Bullets[wb_aero].AvID == 250) Q_Bullet->Bullet[wb_aero].AvID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].ORIGPos);	//Avatar Attack Pose State
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].ZSpin);
			/*m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][0]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][1]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][2]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][0]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][1]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][2]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][0]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][1]);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][2]);*/
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].AlignMatrix.Translation);
			m_transfer->acRead(Q_Bullet->Bullet[wb_aero].JDamageLVL);

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			if(wb_aero >= _->NomBullet)
				{
				_->NomBullet = wb_aero + 1;
				}
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(_->NomBullet);

	//MessageBox(NULL,"BulHits  \n","ERROR",MB_OK);


	//#### Update Bullet Hits
	m_Recieve = 1;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].Live);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].Init);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].EffectType);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].AvID);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].AvatarHITID);

			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR);

			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].Pos);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj);
			m_transfer->acRead(Q_BulletHit->BulletHit[_->NomBulHit].CollNormal);

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			_->NomBulHit++;
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(player[g_Player]->NetUPDATE.NomBulHit);

	/*if(player[g_Player]->NetUPDATE.NomBulHit < _->NomBulHit)
		{
		wb_aero = player[g_Player]->NetUPDATE.NomBulHit;
		while(wb_aero < _->NomBulHit)
			{
			Q_BulletHit->BulletHit[wb_aero].Scale = 1;
			Q_BulletHit->BulletHit[wb_aero].Live = 0;
			Q_BulletHit->BulletHit[wb_aero].Init = 0;
			wb_aero++;
			}
		}*/

	//_->NomBulHit = player[g_Player]->NetUPDATE.NomBulHit;

	//MessageBox(NULL,"Melee Hits  \n","ERROR",MB_OK);

	//#### Update Melee Hits
	m_Recieve = true;
	while(m_Recieve == 1)
		{
		m_transfer->acRead(wb_aero);
		
		if(wb_aero != -5)
			{
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Live);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT);

			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Impact);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt);

			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue);

			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP);

			/*m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[0][0]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[0][1]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[0][2]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[1][0]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[1][1]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[1][2]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[2][0]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[2][1]);
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Matrix.m[2][2]);*/
			m_transfer->acRead(Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Translation);

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			_->NomMelHit++;
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(player[g_Player]->NetUPDATE.NomMelHit);

#if 0
	if(player[g_Player]->NetUPDATE.NomMelHit < _->NomMelHit)
		{
		wb_aero = player[g_Player]->NetUPDATE.NomMelHit;
		while(wb_aero < _->NomMelHit)
			{
			Q_MeleeHit->MeleeHit[wb_aero].Live = 0;
			Q_MeleeHit->MeleeHit[wb_aero].INIT = 0;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius = 301;
			Qpo->Light_Remove(Q_MeleeHit->MeleeHit[wb_aero].Light);
			wb_aero++;
			}
		}
#endif

	//_->NomMelHit = player[g_Player]->NetUPDATE.NomMelHit;

	//MessageBox(NULL,"Small Energy  \n","ERROR",MB_OK);

	//##### Update Small Energy
	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].Live);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].AvID);

			Q_SEnergy->SEnergy[wb_aero].AvID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].LightPos);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].TraVec);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].Speed);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].Scale);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].Alpha);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].TargetLock);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].TargetID);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].AngleX);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].AngleY);
			m_transfer->acRead(Q_SEnergy->SEnergy[wb_aero].AngleZ);

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			if(wb_aero >= _->NomSEnergy)
				{
				_->NomSEnergy = wb_aero + 1;
				}
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(player[g_Player]->NetUPDATE.NomSEnergy);

	/*if(player[g_Player]->NetUPDATE.NomSEnergy < _->NomSEnergy)
		{
		wb_jet = _->NomSEnergy - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomSEnergy)
			{
			Q_SEnergy->SEnergy[wb_jet].Live = 0;
			if(Q_SEnergy->SEnergy[wb_jet].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[wb_jet].Light);
			//if(Q_SEnergy->SEnergy[wb_jet].Sound != NULL) geSound_StopSound(SoundSys, Q_SEnergy->SEnergy[wb_jet].Sound);

			wb_helly = 0;
			while(wb_helly < Q_SEnergy->SEnergy[wb_jet].NomActors)
				{
				Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[wb_jet].AvatarFlag[wb_helly].Xform.Translation);
				wb_helly++;
				}

			wb_jet--;
			}
		}*/

	//_->NomSEnergy = player[g_Player]->NetUPDATE.NomSEnergy;

	//MessageBox(NULL,"Large Energy  \n","ERROR",MB_OK);

	//##### Update Large Energy
	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].Live);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].LightPos);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].TraVec);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].Speed);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].Scale);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].Alpha);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].EnergyLive);
			m_transfer->acRead(Q_LEnergy->LEnergy[wb_aero].EnergyFire);

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			if(wb_aero >= _->NomSEnergy)
				{
				_->NomSEnergy = wb_aero + 1;
				}
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(player[g_Player]->NetUPDATE.NomLEnergy);

	/*if(player[g_Player]->NetUPDATE.NomLEnergy < _->NomLEnergy)
		{
		wb_jet = _->NomLEnergy - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomLEnergy)
			{
			Qpo->Light_Remove(Q_LEnergy->LEnergy[wb_jet].Light);
			Q_LEnergy->LEnergy[wb_jet].Init = 0;
			Q_LEnergy->LEnergy[wb_jet].Live = 0;
			Q_LEnergy->LEnergy[wb_jet].EnergyLive = 0;
			Q_LEnergy->LEnergy[wb_jet].EnergyFire = 0;
			Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[wb_jet].EnergyBall.Xform.Translation);
			Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[wb_jet].EnergyBall, 0,0,0);

			wb_jet--;
			}
		}*/

	//_->NomLEnergy = player[g_Player]->NetUPDATE.NomLEnergy;

	//MessageBox(NULL,"World Explosions  \n","ERROR",MB_OK);

	//##### Update World Explosions
	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);
		
		if(wb_aero != -5)
			{
			m_transfer->acRead(Q_Explosion->Explosion[_->NomExplosions].Live);
			m_transfer->acRead(Q_Explosion->Explosion[_->NomExplosions].Pos);
			m_transfer->acRead(Q_Explosion->Explosion[_->NomExplosions].ExpSize);
			m_transfer->acRead(Q_Explosion->Explosion[_->NomExplosions].LargeEnergyAvID);
			m_transfer->acRead(Q_Explosion->Explosion[_->NomExplosions].CollPlaneNormal);

			if(Q_Explosion->Explosion[_->NomExplosions].Live == 1)
				{
				if(Q_Explosion->Explosion[_->NomExplosions].Live == 0) Q_Explosion->Explosion[_->NomExplosions].Init = 0;
				Q_Explosion->Explosion[_->NomExplosions].Live = Q_Explosion->Explosion[_->NomExplosions].Live;
				Q_Explosion->Explosion[_->NomExplosions].Pos = Q_Explosion->Explosion[_->NomExplosions].Pos;
				Q_Explosion->Explosion[_->NomExplosions].ExpSize = Q_Explosion->Explosion[_->NomExplosions].ExpSize;
				Q_Explosion->Explosion[_->NomExplosions].LargeEnergyAvID = Q_Explosion->Explosion[_->NomExplosions].LargeEnergyAvID;
				Q_Explosion->Explosion[_->NomExplosions].CollPlaneNormal = Q_Explosion->Explosion[_->NomExplosions].CollPlaneNormal;
				}

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;

			_->NomExplosions++;
			}
		else m_Recieve = 0;
		}

	//m_transfer->acRead(player[g_Player]->NetUPDATE.NomExplosions);

	//if(player[g_Player]->NetUPDATE.NomExplosions >= _->NomExplosions)
	//	{ _->NomExplosions = player[g_Player]->NetUPDATE.NomExplosions; }

	//MessageBox(NULL,"Cleric Heal  \n","ERROR",MB_OK);

	//##### Update Cleric Heal Energy
	/***IMU***m_transfer->acRead(player[g_Player]->NetUPDATE.NomHSpark);

	if(player[g_Player]->NetUPDATE.NomHSpark < _->NomHSpark)
		{
		wb_jet = _->NomHSpark - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomHSpark)
			{
			Q_HealSpark->HealSpark[wb_jet].Live = 0;
			if(Q_HealSpark->HealSpark[wb_jet].Light != NULL) Qpo->Light_Remove(Q_HealSpark->HealSpark[wb_jet].Light);
			Q_HealSpark->HealSpark[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomHSpark = player[g_Player]->NetUPDATE.NomHSpark;

	wb_aero = 0;
	while(wb_aero < _->NomHSpark)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HTYPE);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Pos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].TraVec);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Released);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Absorbed);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].AlpFade);
		m_transfer->acRead(player[g_Player]->NetUPDATE.HealSparks[wb_aero].ScaleSTR);

		if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live == 1)
			{
			Q_HealSpark->HealSpark[wb_aero].Live = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live;
			Q_HealSpark->HealSpark[wb_aero].HTYPE = player[g_Player]->NetUPDATE.HealSparks[wb_aero].HTYPE;
			Q_HealSpark->HealSpark[wb_aero].Pos = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Pos;
			Q_HealSpark->HealSpark[wb_aero].TraVec = player[g_Player]->NetUPDATE.HealSparks[wb_aero].TraVec;
			Q_HealSpark->HealSpark[wb_aero].Released = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Released;
			Q_HealSpark->HealSpark[wb_aero].Absorbed = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Absorbed;

			Q_HealSpark->HealSpark[wb_aero].HealTarget = player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget;
			if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_HealSpark->HealSpark[wb_aero].HealTarget = 250;
			if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget == 250) Q_HealSpark->HealSpark[wb_aero].HealTarget = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			Q_HealSpark->HealSpark[wb_aero].AlpFade = player[g_Player]->NetUPDATE.HealSparks[wb_aero].AlpFade;
			Q_HealSpark->HealSpark[wb_aero].ScaleSTR = player[g_Player]->NetUPDATE.HealSparks[wb_aero].ScaleSTR;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Spells  \n","ERROR",MB_OK);

	//##### Update Cleric Spells
	m_transfer->acRead(player[g_Player]->NetUPDATE.NomSpell);

	if(player[g_Player]->NetUPDATE.NomSpell < _->NomSpell)
		{
		wb_jet = _->NomSpell - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomSpell)
			{
			Q_ClericSpell->ClericSpell[wb_jet].Live = 0;
			if(Q_ClericSpell->ClericSpell[wb_jet].Light != NULL) Qpo->Light_Remove(Q_ClericSpell->ClericSpell[wb_jet].Light);
			Q_ClericSpell->ClericSpell[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomSpell = player[g_Player]->NetUPDATE.NomSpell;

	wb_aero = 0;
	while(wb_aero < _->NomSpell)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].NumSpheres);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPow);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Absorbed);
		
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[0]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[1]);
		
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[0]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[1]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[0]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[0]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[1]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[1]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[2]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[2]);

		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[3]);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[3]);


		if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live == 1)
			{
			Q_ClericSpell->ClericSpell[wb_aero].Live = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live;
			Q_ClericSpell->ClericSpell[wb_aero].NumSpheres = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].NumSpheres;

			Q_ClericSpell->ClericSpell[wb_aero].HealTarget = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget;
			if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_ClericSpell->ClericSpell[wb_aero].HealTarget = 250;
			if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget == 250) Q_ClericSpell->ClericSpell[wb_aero].HealTarget = Q_Netplayer->Netplayer[0].LocalCONTROLID;
			
			Q_ClericSpell->ClericSpell[wb_aero].LightPos = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPos;
			Q_ClericSpell->ClericSpell[wb_aero].LightPow = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPow;
			Q_ClericSpell->ClericSpell[wb_aero].Absorbed = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Absorbed;
			
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Radius = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Radius = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].StartFade = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].StartFade = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[0];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[1];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[2];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[2];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[3];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[3];
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Plasma  \n","ERROR",MB_OK);

	//##### Update Cleric Plasma
	m_transfer->acRead(player[g_Player]->NetUPDATE.NomPlasma);

	if(player[g_Player]->NetUPDATE.NomPlasma < _->NomPlasma)
		{
		wb_jet = _->NomPlasma - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomPlasma)
			{
			Q_ClericPlasma->ClericPlasma[wb_jet].Live = 0;
			if(Q_ClericPlasma->ClericPlasma[wb_jet].Light != NULL) Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[wb_jet].Light);
			Q_ClericPlasma->ClericPlasma[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomPlasma = player[g_Player]->NetUPDATE.NomPlasma;

	wb_aero = 0;
	while(wb_aero < _->NomPlasma)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Pos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].TraVec);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Speed);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Alpha);
		m_transfer->acRead(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].PartType);

		if(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live == 1)
			{
			Q_ClericPlasma->ClericPlasma[wb_aero].Live = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live;
			Q_ClericPlasma->ClericPlasma[wb_aero].Pos = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Pos;
			Q_ClericPlasma->ClericPlasma[wb_aero].TraVec = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].TraVec;
			Q_ClericPlasma->ClericPlasma[wb_aero].Speed = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Speed;
			Q_ClericPlasma->ClericPlasma[wb_aero].Alpha = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Alpha;
			Q_ClericPlasma->ClericPlasma[wb_aero].PartType = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].PartType;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Net Effects Control  \n","ERROR",MB_OK);

	//##### Update Net Effects Control
	m_transfer->acRead(player[g_Player]->NetUPDATE.NomNetEffectControl);

	_->NomNetEffectControl = player[g_Player]->NetUPDATE.NomNetEffectControl;

	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live);
		m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type);
		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type == 0) m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Pos);
		m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Effintensity);
		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type == 1) m_transfer->acRead(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].AvID);

		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live > Q_NetEffectControl->NetEffectControl[wb_aero].Live)
			{ Q_NetEffectControl->NetEffectControl[wb_aero].Active = 1; }

		Q_NetEffectControl->NetEffectControl[wb_aero].Live = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live;
		Q_NetEffectControl->NetEffectControl[wb_aero].Type = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type;
		Q_NetEffectControl->NetEffectControl[wb_aero].Pos = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Pos;
		Q_NetEffectControl->NetEffectControl[wb_aero].Effintensity = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Effintensity;
		Q_NetEffectControl->NetEffectControl[wb_aero].AvID = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].AvID;

		wb_aero++;
		}*/


	//##### Update Net Zone Increment

	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].AVID);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Maxs);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Mins);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.INT);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.ON);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Red);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Green);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Blue);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Alpha);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.TIMER);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.CNT);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMINS);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMAXS);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandSTRENGTH);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_TimeScale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Gravity);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LifeINC);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyINC);

			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_intBoost);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyEff);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Height);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Weight);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Strength);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Quickness);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Dexterity);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Constitution);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_AggPower);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_DefPower);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegStr);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegSnap);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPAccuracy);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPDrawSPD);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPReloadSPD);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPRecoilHR);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKmovespeed);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKpower);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINK3intensity);


			//====---- AQUIRE ZONE ----====
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].AVID;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Mins;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Maxs;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMINS;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMAXS;

			//### FIND CORE
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
			Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
			Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

			//### EXPAND OUTWARDS MINS AND MAXS
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
			Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
			Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
			Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
			Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandSTRENGTH;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3];
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4];

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_TimeScale;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Gravity;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LifeINC;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyINC;

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_intBoost;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyEff;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Height;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Weight;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Strength;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Quickness;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Dexterity;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Constitution;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_AggPower;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_DefPower;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegStr;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegSnap;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPAccuracy;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPDrawSPD;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPReloadSPD;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPRecoilHR;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKmovespeed;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKpower;
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINK3intensity;

			Corner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
			DX = TempVec1;
			DX.y = 0;
			DX.z = 0;
			DY = TempVec1;
			DY.x = 0;
			DY.z = 0;
			DZ = TempVec1;
			DZ.y = 0;
			DZ.x = 0;
			//Q.DrawOrientedBoundBox(&Corner, &DX, &DY, &DZ);

			//if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998) Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;

			//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
			//geSound_PlaySoundDef(SoundSys, Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, GE_false);
			
			if(wb_aero >= Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks && wb_aero < 9997)
				{
				Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks = wb_aero + 1;
				}
			}
		else m_Recieve = 0;
		}


	//##### Update Net Zone ENTITY Increment

	m_Recieve = true;
	while(m_Recieve)
		{
		m_transfer->acRead(wb_aero);

		if(wb_aero != -5)
			{
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].TYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ID);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ZoneID);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].QObjID);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Range);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Scale);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].StrengthMAX);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].CollisionTYPE);
			m_transfer->acRead(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].AvID);

			switch(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].TYPE)
				{
				case 0:
					{
					//====----- SENTRY BUILD ------====

					if(_->NomBMSentry < 148)
						{
						Q_BMSentry->BMSentry[_->NomBMSentry].Pos = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos;
						Q_BMSentry->BMSentry[_->NomBMSentry].ZoneID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ZoneID;
						Q_BMSentry->BMSentry[_->NomBMSentry].QObjID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].QObjID;
						Q_BMSentry->BMSentry[_->NomBMSentry].Range = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Range;
						Q_BMSentry->BMSentry[_->NomBMSentry].LIVE = 1;

						_->NomBMSentry++;
						}

					//#### INITIALISE THE Q_Object->Object TO HOUSE THE SENTRY

					if(_->NomQObject < 148)
						{
						Q_Object->Object[_->NomQObject].Pos = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos;
						Q_Object->Object[_->NomQObject].Scale = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Scale;
						Q_Object->Object[_->NomQObject].StrengthMAX = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].StrengthMAX;
						Q_Object->Object[_->NomQObject].StrengthBANK = Q_Object->Object[_->NomQObject].StrengthMAX;
						Q_Object->Object[_->NomQObject].CollisionTYPE = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].CollisionTYPE;
						Q_Object->Object[_->NomQObject].AvID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].AvID;
						Q_Object->Object[_->NomQObject].LIVE = 1;

						_->NomQObject++;
						}

					//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
							//'Jink Ready'
					//geSound_PlaySoundDef(SoundSys, Medias->S_Build, _->Volume, _->Pan, _->S_TimeScale, GE_false);
					}break;
				}

			if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
			}
		else m_Recieve = 0;
		}

	//FRLs
	m_transfer->acRead(_->FRLtarget);
	m_transfer->acRead(_->FRLON);
	//_->FRLON = 0;
#endif
}

void Q_Network::RecordWorld(float i_Time)
{
	Buffer_FillFloat(i_Time);

	//### FILL BUFFER
	Buffer_FillAngle(&playerAV[g_Player]->Xform.Translation);
	Buffer_FillFloat(player[g_Player]->AvatarRotation);
	Buffer_FillByte(player[g_Player]->Mposestate);
	Buffer_FillByte(player[g_Player]->Aposestate);
	Buffer_FillByte(player[g_Player]->attackon);
	Buffer_FillByte(player[g_Player]->WeaponStatus);
	Buffer_FillByte(player[g_Player]->NETMFlash);
	Buffer_FillByte(player[g_Player]->Block);
	Buffer_FillByte(player[g_Player]->BlockHit);
	Buffer_FillByte(player[g_Player]->BlockHeight);
	Buffer_FillByte(player[g_Player]->Crouch);
	Buffer_FillFloat(player[g_Player]->HitReactScale);
	Buffer_FillAngle(&player[g_Player]->MoveReactVec);
	Buffer_FillFloat(player[g_Player]->MoveReactSpeed);

	Buffer_FillFloat(player[g_Player]->JINK3_PowerFactor);

	Buffer_FillFloat(player[g_Player]->HB_Energy);
	Buffer_FillFloat(player[g_Player]->HB_Health);

	Buffer_FillByte(player[g_Player]->SpecLvlRESET);
	Buffer_FillByte(player[g_Player]->SNDTRIGEnergy);
	
	Buffer_FillByte(player[g_Player]->PlayerMode);

	Buffer_FillFloat(player[g_Player]->idleposecnt);
	Buffer_FillFloat(player[g_Player]->runposecnt);
	Buffer_FillFloat(player[g_Player]->attposecnt);
	Buffer_FillFloat(player[g_Player]->crohposecnt);
	Buffer_FillFloat(player[g_Player]->jumpposecnt);

	Buffer_FillAngle(&player[g_Player]->WallRunCollision.Plane.Normal);

	//######  - Other Worldly Avatars -  #####

	//### Set the Avatar Count
	Buffer_FillInteger(_->NomAI);

	//##### AVATAR UPDATE PREP LOOP
	wb_jet=0;
	while(wb_jet < _->NomAI)
		{
		Q_Forge->Forge[wb_jet].NETMFlash = 0;

		//### FILL BUFFER
		Buffer_FillByte(wb_jet);
		#pragma message("?")

		//###Get Player Data to Client
		Buffer_FillAngle(&Q_Forge->Forge[wb_jet].AV.Xform.Translation);				//Avatar Position

#pragma message("Full matrix transmission or partial quat makeup")

		Buffer_FillAngle(&Q_Forge->Forge[wb_jet].Up);

		Buffer_FillByte(Q_Forge->Forge[wb_jet].Mposestate);		//Avatar Move Pose State

		if(player[g_Player]->EnergySWITCHOFF > 0)
			{
			player[g_Player]->EnergySWITCHOFF--;

			Buffer_FillByte(205);
			}
		else Buffer_FillByte(Q_Forge->Forge[wb_jet].Aposestate);

		Buffer_FillByte(Q_Forge->Forge[wb_jet].attackon);		//Avatar Attack Pose State
		Buffer_FillByte(Q_Forge->Forge[wb_jet].WeaponStatus);
		Buffer_FillByte(Q_Forge->Forge[wb_jet].NETMFlash);
		Buffer_FillByte(Q_Forge->Forge[wb_jet].Block);			//Avatar Attack Pose State
		Buffer_FillByte(Q_Forge->Forge[wb_jet].BlockHit);		//Avatar Attack Pose State
		Buffer_FillByte(Q_Forge->Forge[wb_jet].BlockHeight);
		Buffer_FillByte(Q_Forge->Forge[wb_jet].Crouch);			//Avatar Attack Pose State
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].HitReactScale);
		Buffer_FillAngle(&Q_Forge->Forge[wb_jet].MoveReactVec);
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].MoveReactSpeed);
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].JINK3_PowerFactor);

		Buffer_FillFloat(Q_Forge->Forge[wb_jet].HB_Energy);
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].HB_Health);
		
		Buffer_FillByte(Q_Forge->Forge[wb_jet].PlayerMode);

		Buffer_FillFloat(Q_Forge->Forge[wb_jet].idleposecnt);		//Avatar Idle Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].runposecnt);		//Avatar Run Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].attposecnt);		//Avatar Attack Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].crohposecnt);		//Avatar Attack Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[wb_jet].jumpposecnt);		//Avatar Attack Pose Counter

		Buffer_FillAngle(&Q_Forge->Forge[wb_jet].WallRunCollision.Plane.Normal);

		wb_jet++;
		}

#if 0
	//##### Prepare Q_Object->ObjectS
	Buffer_FillFloat(_->NomQObject);

	wb_aero = 0;
	while(wb_aero < _->NomQObject)
		{
		Buffer_FillFloat(Q_Object->Object[wb_aero].StrengthBANK);
		
		wb_aero++;
		}


	//##### Prepare World Bullets
	Buffer_FillInteger(_->NomBullet);

	wb_aero = 0;
	while(wb_aero < _->NomBullet)
		{
		Buffer_FillByte(Q_Bullet->Bullet[wb_aero].Live);
		Buffer_FillAngle(&Q_Bullet->Bullet[wb_aero].TrajVec);
		Buffer_FillAngle(&Q_Bullet->Bullet[wb_aero].WorldPos);		//Avatar Move Pose State
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].Speed);		//Avatar Attack Pose State
		Buffer_FillByte(Q_Bullet->Bullet[wb_aero].AvID);		//Avatar Attack Pose State
		Buffer_FillAngle(&Q_Bullet->Bullet[wb_aero].ORIGPos);		//Avatar Attack Pose State
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].ZSpin);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][0]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][1]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][2]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][0]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][1]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][2]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][0]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][1]);
		Buffer_FillFloat(Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][2]);
		Buffer_FillAngle(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Translation);
		Buffer_FillByte(Q_Bullet->Bullet[wb_aero].JDamageLVL);

		wb_aero++;
		}


	//##### Prepare World Bullet Hits
	Buffer_FillInteger(_->NomBulHit);

	wb_aero = 0;
	while(wb_aero < _->NomBulHit)
		{
		Buffer_FillByte(Q_BulletHit->BulletHit[wb_aero].Live);
		Buffer_FillByte(Q_BulletHit->BulletHit[wb_aero].Init);
		Buffer_FillByte(Q_BulletHit->BulletHit[wb_aero].EffectType);
		Buffer_FillByte(Q_BulletHit->BulletHit[wb_aero].AvID);
		Buffer_FillByte(Q_BulletHit->BulletHit[wb_aero].AvatarHITID);

		Buffer_FillFloat(Q_BulletHit->BulletHit[wb_aero].BulletDMG);
		Buffer_FillFloat(Q_BulletHit->BulletHit[wb_aero].BulletPWR);

		Buffer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].Pos);
		Buffer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].BulletTraj);
		Buffer_FillAngle(&Q_BulletHit->BulletHit[wb_aero].CollNormal);

		wb_aero++;
		}


	//##### Prepare World Melee Hits
	Buffer_FillInteger(_->NomMelHit);

	wb_aero = 0;
	while(wb_aero < _->NomMelHit)
		{
		Buffer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Live);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].HitTYPE);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].HitRESULT);

		Buffer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].Impact);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].Bonenum);
		Buffer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].ReactionNorm);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].HitPowerPercent);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[wb_aero].BloodAmt);

		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.MaxRadius);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.StartFade);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Red);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Green);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Blue);

		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttackSTRENGTH);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttackSNAP);
		
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][0]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][1]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][2]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][0]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][1]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][2]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][0]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][1]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][2]);
		Buffer_FillAngle(&Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Translation);

		wb_aero++;
		}


	//##### Prepare Small Energy
	Buffer_FillInteger(_->NomSEnergy);

	wb_aero = 0;
	while(wb_aero < _->NomSEnergy)
		{
		Buffer_FillByte(Q_SEnergy->SEnergy[wb_aero].Live);
		Buffer_FillAngle(&Q_SEnergy->SEnergy[wb_aero].LightPos);
		Buffer_FillAngle(&Q_SEnergy->SEnergy[wb_aero].TraVec);
		Buffer_FillFloat(Q_SEnergy->SEnergy[wb_aero].Speed);
		Buffer_FillFloat(Q_SEnergy->SEnergy[wb_aero].Scale);
		Buffer_FillByte(Q_SEnergy->SEnergy[wb_aero].Alpha);
		Buffer_FillByte(Q_SEnergy->SEnergy[wb_aero].TargetLock);
		Buffer_FillByte(Q_SEnergy->SEnergy[wb_aero].TargetID);
		Buffer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleX);
		Buffer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleY);
		Buffer_FillFloat(Q_SEnergy->SEnergy[wb_aero].AngleZ);

		wb_aero++;
		}


	//##### Prepare Large Energy
	Buffer_FillInteger(_->NomLEnergy);

	wb_aero = 0;
	while(wb_aero < _->NomLEnergy)
		{
		Buffer_FillByte(Q_LEnergy->LEnergy[wb_aero].Live);
		Buffer_FillAngle(&Q_LEnergy->LEnergy[wb_aero].LightPos);
		Buffer_FillAngle(&Q_LEnergy->LEnergy[wb_aero].TraVec);
		Buffer_FillFloat(Q_LEnergy->LEnergy[wb_aero].Speed);
		Buffer_FillFloat(Q_LEnergy->LEnergy[wb_aero].Scale);
		Buffer_FillByte(Q_LEnergy->LEnergy[wb_aero].Alpha);
		Buffer_FillByte(Q_LEnergy->LEnergy[wb_aero].EnergyLive);
		Buffer_FillByte(Q_LEnergy->LEnergy[wb_aero].EnergyFire);

		wb_aero++;
		}


	//##### Prepare World Explosions
	Buffer_FillInteger(_->NomExplosions);

	wb_aero = 0;
	while(wb_aero < _->NomExplosions)
		{
		Buffer_FillByte(Q_Explosion->Explosion[wb_aero].Live);
		Buffer_FillAngle(&Q_Explosion->Explosion[wb_aero].Pos);
		Buffer_FillFloat(Q_Explosion->Explosion[wb_aero].ExpSize);
		Buffer_FillByte(Q_Explosion->Explosion[wb_aero].LargeEnergyAvID);
		Buffer_FillAngle(&Q_Explosion->Explosion[wb_aero].CollPlaneNormal);

		wb_aero++;
		}


	//##### Prepare Cleric Heal Sparks
	Buffer_FillInteger(_->NomHSpark);

	wb_aero = 0;
	while(wb_aero < _->NomHSpark)
		{
		Buffer_FillByte(Q_HealSpark->HealSpark[wb_aero].Live);
		Buffer_FillByte(Q_HealSpark->HealSpark[wb_aero].HTYPE);
		Buffer_FillAngle(&Q_HealSpark->HealSpark[wb_aero].Pos);
		Buffer_FillAngle(&Q_HealSpark->HealSpark[wb_aero].TraVec);
		Buffer_FillByte(Q_HealSpark->HealSpark[wb_aero].Released);
		Buffer_FillByte(Q_HealSpark->HealSpark[wb_aero].Absorbed);
		Buffer_FillByte(Q_HealSpark->HealSpark[wb_aero].HealTarget);
		Buffer_FillFloat(Q_HealSpark->HealSpark[wb_aero].AlpFade);
		Buffer_FillFloat(Q_HealSpark->HealSpark[wb_aero].ScaleSTR);

		wb_aero++;
		}


	//##### Prepare Cleric Spells
	Buffer_FillInteger(_->NomSpell);

	wb_aero = 0;
	while(wb_aero < _->NomSpell)
		{
		Buffer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Live);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].HealTarget);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].NumSpheres);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].LightPos);
		Buffer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].LightPow);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Absorbed);

		Buffer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Radius);
		Buffer_FillFloat(Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Radius);

		Buffer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].StartFade);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].StartFade);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Upvec);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Upvec);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Upvec);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Upvec);

		wb_aero++;
		}


	//##### Prepare Cleric Plasma
	Buffer_FillInteger(_->NomPlasma);

	wb_aero = 0;
	while(wb_aero < _->NomPlasma)
		{
		Buffer_FillByte(Q_ClericPlasma->ClericPlasma[wb_aero].Live);
		Buffer_FillAngle(&Q_ClericPlasma->ClericPlasma[wb_aero].Pos);
		Buffer_FillAngle(&Q_ClericPlasma->ClericPlasma[wb_aero].TraVec);
		Buffer_FillFloat(Q_ClericPlasma->ClericPlasma[wb_aero].Speed);
		Buffer_FillFloat(Q_ClericPlasma->ClericPlasma[wb_aero].Alpha);
		Buffer_FillByte(Q_ClericPlasma->ClericPlasma[wb_aero].PartType);
		wb_aero++;
		}


	//##### Prepare Net Effects Control
	Buffer_FillInteger(_->NomNetEffectControl);

	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		Buffer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].Live);
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Type == 0) Buffer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].Type);
		Buffer_FillAngle(&Q_NetEffectControl->NetEffectControl[wb_aero].Pos);
		Buffer_FillFloat(Q_NetEffectControl->NetEffectControl[wb_aero].Effintensity);
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Type == 1) Buffer_FillByte(Q_NetEffectControl->NetEffectControl[wb_aero].AvID);
		
		wb_aero++;
		}


	//###### ---- Net Effects Control ---- ######
	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		if(Q_NetEffectControl->NetEffectControl[wb_aero].Live > 1)
			{	//#### COUNTER ####
			Q_NetEffectControl->NetEffectControl[wb_aero].Live--;
			}
		else
			{
			Q_NetEffectControl->NetEffectControl[wb_aero].Live = 0;

			if(Q_NetEffectControl->NetEffectControl[wb_aero].Type = 0)
				{
				//### Energy Array Reorder
				K = wb_aero;
				while(K < _->NomNetEffectControl - 1)
					{
					Q_NetEffectControl->NetEffectControl[K] = Q_NetEffectControl->NetEffectControl[K+1];
					K++;
					}
				}

			_->NomNetEffectControl--;
			}
		wb_aero++;
		}


	//##### Prepare Net Zone Increment
	Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC);

	wb_aero = 0;
	while(wb_aero < Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC)
		{
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].AVID);

		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Maxs);
		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Mins);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Smoke.CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[0].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[1].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[2].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[3].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Effect[4].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].Fog.CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].FogLight.CNT);

		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandMINS);
		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandMAXS);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ExpandSTRENGTH);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_TimeScale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Gravity);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LifeINC);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_EnergyINC);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_intBoost);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_EnergyEff);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Height);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Weight);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Strength);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Quickness);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Dexterity);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_Constitution);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_AggPower);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_DefPower);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RArmStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LArmStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RLegStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LLegStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RArmSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LArmSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_RLegSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_LLegSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPAccuracy);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPDrawSPD);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPReloadSPD);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_WEPRecoilHR);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINKmovespeed);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINKpower);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[wb_aero]].ZONEINC_JINK3intensity);

		wb_aero++;
		}

	//# Energy Reset
	Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC = 0;


	//##### Prepare Net Zone ENTITY Increment
	Buffer_FillInteger(_->NomNetZoneENTITY);

	wb_aero = 0;
	while(wb_aero < _->NomNetZoneENTITY)
		{
		Buffer_FillByte(Q_NetZoneENTITY->NetZoneENTITY[wb_aero].TYPE);
		Buffer_FillFloat(Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID);
		Buffer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].ZoneID);
		Buffer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID);
		Buffer_FillAngle(&Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].Pos);
		Buffer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].Range);
		Buffer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].Scale);
		Buffer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].StrengthMAX);
		Buffer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].CollisionTYPE);
		Buffer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[wb_aero].ID].QObjID].AvID);

		wb_aero++;
		}

	//# Energy Reset
	_->NomNetZoneENTITY = 0;


	//### FRLs
	Buffer_FillFloat(_->FRLtarget);
	Buffer_FillByte(Q_Netplayer->Netplayer[wb_helly].FRLswitch);
#endif


	/*if (!geCSNetMgr_SendToClient(QHost.NMgr->CSNetMgr, NID, GE_true, QHost.NMgr->ServerToClientBuffer.Data, QHost.NMgr->ServerToClientBuffer.Pos))
		return GE_false;*/
}


void Q_Network::PlayWorld(float Time)
{
	float				DeltaTime, MoveTime;
	int					AvatarID;
	QpoVec3d			BufferVec;
	float				Bufferfloat;
	int					Bufferint;

	//##Check Time
	Buffer_GetFloat(&MoveTime);

#if 1
	//###### Update Player #####
	//###Get Player Data to Client
	Buffer_GetAngle(&playerAV[g_Player]->Xform.Translation);
	Buffer_GetFloat(&player[g_Player]->NetRotation);
	Buffer_GetByte(&player[g_Player]->Mposestate);
	Buffer_GetByte(&Int_Aposestate);
	Buffer_GetByte(&player[g_Player]->attackon);
	Buffer_GetByte(&player[g_Player]->WeaponStatus);
	Buffer_GetByte(&Int_Mflash);
	if(Int_Mflash > 0 && Q_MFlash->MFlash[250].SkipFlag == 0) player[g_Player]->MFlash = Int_Mflash;
	Buffer_GetByte(&player[g_Player]->Block);
	Buffer_GetByte(&player[g_Player]->BlockHit);
	Buffer_GetByte(&player[g_Player]->BlockHeight);
	Buffer_GetByte(&player[g_Player]->Crouch);
	Buffer_GetFloat(&player[g_Player]->HitReactScale);
	Buffer_GetAngle(&player[g_Player]->MoveReactVec);
	Buffer_GetFloat(&player[g_Player]->MoveReactSpeed);
	Buffer_GetFloat(&Float_PowerFactor);

	if(player[g_Player]->JINK3_PowerFactor != Float_PowerFactor)
		{
		Q.DeactivateItems();
		
		player[g_Player]->JINK3_PowerFactor = Float_PowerFactor;

		Q.ActivateItems();
		}

	Buffer_GetFloat(&player[g_Player]->HB_Energy);
	Buffer_GetFloat(&Float_Health);

	if(player[g_Player]->HB_Health - Float_Health > 8)
		{
		player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

		player[g_Player]->HB_HReduceON = 1;
		player[g_Player]->HB_ReduceHInc = 10;
		player[g_Player]->HB_ReduceHeight = 573;
		player[g_Player]->HB_ReduceRectColor.red = 255;
		player[g_Player]->HB_ReduceRectColor.green = 0;
		player[g_Player]->HB_ReduceRectColor.blue = 0;
		player[g_Player]->HB_ReduceRectColor.alpha = 255;
		}

	if((player[g_Player]->HB_Health > 0) && (Float_Health <= 0))
		{
		//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//geSound_PlaySoundDef(SoundSys, Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, GE_false);
		}

	player[g_Player]->HB_Health = Float_Health;

	Buffer_GetByte(&Int_SpecLvlRESET);

	if(Int_SpecLvlRESET != 0 && player[g_Player]->SpecLvlRESET == 0) player[g_Player]->SpecLvlRESET = Int_SpecLvlRESET;
	
	/*if(player[g_Player]->SNDTRIGEnergy == 0)*/ Buffer_GetByte(&player[g_Player]->SNDTRIGEnergy);
	//else Buffer_GetByteDiscard();

	Buffer_GetByte(&player[g_Player]->PlayerMode);

	Buffer_GetFloat(&player[g_Player]->idleposecnt);
	Buffer_GetFloat(&player[g_Player]->runposecnt);
	Buffer_GetFloat(&player[g_Player]->attposecnt);
	Buffer_GetFloat(&player[g_Player]->crohposecnt);
	Buffer_GetFloat(&player[g_Player]->jumpposecnt);

	if(player[g_Player]->Aposestate != Int_Aposestate) player[g_Player]->JinkInit = 0;
	else if(player[g_Player]->attposecnt > 0.3 || player[g_Player]->attposecnt == 0) player[g_Player]->JinkInit = 1;

	if(Int_Aposestate == 205) player[g_Player]->EnergySWITCHOFF = 1;
	if(player[g_Player]->EnergySWITCHOFF == 1)
		{
		player[g_Player]->Aposestate = 205;
		player[g_Player]->attackon = 1;
		}
	else player[g_Player]->Aposestate = Int_Aposestate;

	Buffer_GetAngle(&player[g_Player]->WallRunCollision.Plane.Normal);
#endif

#if 0
	Buffer_GetAngle(&BufferVec);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetAngle(&BufferVec);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetByte(&Bufferint);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetFloat(&Bufferfloat);
	Buffer_GetAngle(&BufferVec);
#endif

	//######  - Other Worldly Avatars -  #####
	Buffer_GetByte(&_->NETNomWorldAvatars);

	//##### Avatar Update Loop
	wb_helly=0;
	while(wb_helly < _->NETNomWorldAvatars)
		{
		//###### Get Avatars Q_Netplayer->Netplayer #####
		Buffer_GetByte(&AvatarID);

		//###Get Player Data to Client
		Buffer_GetAngle(&Q_Forge->Forge[AvatarID].AV.Xform.Translation);				//Avatar Position
		Buffer_GetAngle(&Q_Forge->Forge[AvatarID].AnglesVec);
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].Mposestate);		//Avatar Move Pose State
		Buffer_GetByte(&Int_Aposestate);		//Avatar Attack Pose State
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].attackon);		//Avatar Attack Pose State
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].WeaponStatus);
		Buffer_GetByte(&Int_Mflash);
		if(Int_Mflash == 1 && Q_MFlash->MFlash[AvatarID].SkipFlag == 0) Q_Forge->Forge[AvatarID].MFlash = Int_Mflash;
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].Block);			//Avatar Attack Pose State
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].BlockHit);		//Avatar Attack Pose State
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].BlockHeight);
		Buffer_GetByte(&Q_Forge->Forge[AvatarID].Crouch);			//Avatar Attack Pose State
		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].HitReactScale);
		Buffer_GetAngle(&Q_Forge->Forge[AvatarID].MoveReactVec);
		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].MoveReactSpeed);

		Buffer_GetFloat(&Float_PowerFactor);

		if(Q_Forge->Forge[AvatarID].JINK3_PowerFactor != Float_PowerFactor)
			{
			Q.DeactivateItemsAI(AvatarID);
			
			Q_Forge->Forge[AvatarID].JINK3_PowerFactor = Float_PowerFactor;

			Q.ActivateItemsAI(AvatarID);
			}

		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].HB_Energy);
		Buffer_GetFloat(&Float_Health);

		if(Q_Forge->Forge[AvatarID].HB_Health - Float_Health > 8)
			{
			Q_Forge->Forge[AvatarID].HB_ReduceOld = Q_Forge->Forge[AvatarID].HB_Health;

			Q_Forge->Forge[AvatarID].HB_HReduceON = 1;
			Q_Forge->Forge[AvatarID].HB_ReduceHInc = 10;
			Q_Forge->Forge[AvatarID].HB_ReduceHeight = 573;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.red = 255;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.green = 0;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.blue = 0;
			Q_Forge->Forge[AvatarID].HB_ReduceRectColor.alpha = 255;
			}

		if((Q_Forge->Forge[AvatarID].HB_Health > 0) && (Float_Health <= 0))
			{
			//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AvatarID].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
			//geSound_PlaySoundDef(SoundSys, Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, GE_false);
			}

		Q_Forge->Forge[AvatarID].HB_Health = Float_Health;

		Buffer_GetByte(&Q_Forge->Forge[AvatarID].PlayerMode);

		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].idleposecnt);		//Avatar Idle Pose Counter
		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].runposecnt);		//Avatar Run Pose Counter
		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].attposecnt);		//Avatar Attack Pose Counter
		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].crohposecnt);		//Avatar Attack Pose Counter
		Buffer_GetFloat(&Q_Forge->Forge[AvatarID].jumpposecnt);		//Avatar Attack Pose Counter

		if(Q_Forge->Forge[AvatarID].Aposestate != Int_Aposestate) Q_Forge->Forge[AvatarID].JinkInit = 0;
		else if(Q_Forge->Forge[AvatarID].attposecnt > 0.3 || Q_Forge->Forge[AvatarID].attposecnt == 0) Q_Forge->Forge[AvatarID].JinkInit = 1;

		//### Avatar Attack Pose State
		if(Int_Aposestate == 205) Q_Forge->Forge[AvatarID].EnergySWITCHOFF = 1;
		if(Q_Forge->Forge[AvatarID].EnergySWITCHOFF == 1)
			{
			Q_Forge->Forge[AvatarID].Aposestate = 205;
			Q_Forge->Forge[AvatarID].attackon = 1;
			}
		else Q_Forge->Forge[AvatarID].Aposestate = Int_Aposestate;

		Buffer_GetAngle(&Q_Forge->Forge[AvatarID].WallRunCollision.Plane.Normal);

		Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
		Q_Forge->Forge[AvatarID].TempVec1 = Q_Forge->Forge[AvatarID].AnglesVec;
		Q_Forge->Forge[AvatarID].TempVec1.y = 0;
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvatarID].TempVec1);
		Q_Forge->Forge[AvatarID].Up.y = 0;
		Q_Forge->Forge[AvatarID].ScanTurnAng = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Up);

		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Left);
		Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
		Qpo->Vec3d_Copy(&Q_Forge->Forge[AvatarID].Left, &Q_Forge->Forge[AvatarID].Right);
		Qpo->Vec3d_Inverse(&Q_Forge->Forge[AvatarID].Right);

		Q_Forge->Forge[AvatarID].ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Left);
		Q_Forge->Forge[AvatarID].ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Right);

		if(Q_Forge->Forge[AvatarID].ScanDistL > Q_Forge->Forge[AvatarID].ScanDistR) Q_Forge->Forge[AvatarID].ScanTurnAng *= -1;

		Q_Forge->Forge[AvatarID].trueAngles.y += Q_Forge->Forge[AvatarID].ScanTurnAng / 3;

		Q_Forge->Forge[AvatarID].Angles.y += Q_Forge->Forge[AvatarID].ScanTurnAng / 3;
		if(Q_Forge->Forge[AvatarID].Angles.y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.y = 0;
		if(Q_Forge->Forge[AvatarID].Angles.y < 0) Q_Forge->Forge[AvatarID].Angles.y = (PI*2);

		Qpo->Transform_New_YRotation(&RotateMatrix, Q_Forge->Forge[AvatarID].ScanTurnAng / 3);
		Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &RotateMatrix, &Q_Forge->Forge[AvatarID].AV.Xform);

		//### UPDATE AVATAR ANGLES
		/*Q_Forge->Forge[AvatarID].ScanTurnAng = Q_Forge->Forge[AvatarID].NetUPDATE.Angle.Y - Q_Forge->Forge[AvatarID].Angles.Y;
		if(Q_Forge->Forge[AvatarID].Angles.Y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.Y = 0;
		if(Q_Forge->Forge[AvatarID].Angles.Y < 0) Q_Forge->Forge[AvatarID].Angles.Y = (PI*2);

		Q_Forge->Forge[AvatarID].Angles.Y = Q_Forge->Forge[_->Multipass].Angles.Y + Q_Forge->Forge[AvatarID].ScanTurnAng;

		geXForm3d_SetZRotation(&AIfriendly, Q_Forge->Forge[AvatarID].ScanTurnAng);
		Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);*/

		wb_helly++;
		}


	//MessageBox(NULL,"Update 1 Bullets \n","ERROR",MB_OK);

#if 0
	//##### Update Q_Object->ObjectS
	Buffer_GetInteger(&_->NomQObject);

	wb_aero = 0;
	while(wb_aero < _->NomQObject)
		{
		Buffer_GetFloat(&Q_Object->Object[wb_aero].StrengthBANK);
		
		wb_aero++;
		}


	//#### Update Bullets
	Buffer_GetInteger(&_->NomBullet);

	wb_aero = 0;
	while(wb_aero < _->NomBullet)
		{
		Buffer_GetByte(&Q_Bullet->Bullet[wb_aero].Live);				//Avatar Position
		Buffer_GetAngle(&Q_Bullet->Bullet[wb_aero].TrajVec);
		Buffer_GetAngle(&Q_Bullet->Bullet[wb_aero].WorldPos);		//Avatar Move Pose State
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].Speed);		//Avatar Attack Pose State
		Buffer_GetByte(&Q_Bullet->Bullet[wb_aero].AvID);		//Avatar Attack Pose State

		if(player[g_Player]->NetUPDATE.Bullets[wb_aero].AvID == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_Bullet->Bullet[wb_aero].AvID = 250;
		if(player[g_Player]->NetUPDATE.Bullets[wb_aero].AvID == 250) Q_Bullet->Bullet[wb_aero].AvID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

		Buffer_GetAngle(&Q_Bullet->Bullet[wb_aero].ORIGPos);		//Avatar Attack Pose State
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].ZSpin);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][0]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][1]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[0][2]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][0]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][1]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[1][2]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][0]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][1]);
		Buffer_GetFloat(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Matrix.m[2][2]);
		Buffer_GetAngle(&Q_Bullet->Bullet[wb_aero].AlignMatrix.Translation);
		Buffer_GetByte(&Q_Bullet->Bullet[wb_aero].JDamageLVL);

		wb_aero++;
		}


	//MessageBox(NULL,"BulHits  \n","ERROR",MB_OK);


	//#### Update Bullet Hits
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomBulHit);

	if(player[g_Player]->NetUPDATE.NomBulHit < _->NomBulHit)
		{
		wb_aero = player[g_Player]->NetUPDATE.NomBulHit;
		while(wb_aero < _->NomBulHit)
			{
			Q_BulletHit->BulletHit[wb_aero].Scale = 1;
			Q_BulletHit->BulletHit[wb_aero].Live = 0;
			Q_BulletHit->BulletHit[wb_aero].Init = 0;
			wb_aero++;
			}
		}

	_->NomBulHit = player[g_Player]->NetUPDATE.NomBulHit;

	wb_aero = 0;
	while(wb_aero < player[g_Player]->NetUPDATE.NomBulHit)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].Live);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].Init);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].EffectType);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvID);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvatarHITID);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].BulletDMG);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].BulletPWR);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].Pos);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].BulletTraj);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.BulletHits[wb_aero].CollNormal);

		if(player[g_Player]->NetUPDATE.BulletHits[wb_aero].Live == 1 && player[g_Player]->NetUPDATE.BulletHits[wb_aero].Init == 1)
			{
			if(Q_BulletHit->BulletHit[wb_aero].Live == 0) Q_BulletHit->BulletHit[wb_aero].Init = 0;
			Q_BulletHit->BulletHit[wb_aero].Live = player[g_Player]->NetUPDATE.BulletHits[wb_aero].Live;
			Q_BulletHit->BulletHit[wb_aero].EffectType = player[g_Player]->NetUPDATE.BulletHits[wb_aero].EffectType;

			Q_BulletHit->BulletHit[wb_aero].AvID = player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvID;
			if(player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvID == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_BulletHit->BulletHit[wb_aero].AvID = 250;
			if(player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvID == 250) Q_BulletHit->BulletHit[wb_aero].AvID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			Q_BulletHit->BulletHit[wb_aero].AvatarHITID = player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvatarHITID;
			if(player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvatarHITID == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_BulletHit->BulletHit[wb_aero].AvatarHITID = 250;
			if(player[g_Player]->NetUPDATE.BulletHits[wb_aero].AvatarHITID == 250) Q_BulletHit->BulletHit[wb_aero].AvatarHITID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			Q_BulletHit->BulletHit[wb_aero].BulletDMG = player[g_Player]->NetUPDATE.BulletHits[wb_aero].BulletDMG;
			Q_BulletHit->BulletHit[wb_aero].BulletPWR = player[g_Player]->NetUPDATE.BulletHits[wb_aero].BulletPWR;

			Q_BulletHit->BulletHit[wb_aero].Pos = player[g_Player]->NetUPDATE.BulletHits[wb_aero].Pos;
			Q_BulletHit->BulletHit[wb_aero].BulletTraj = player[g_Player]->NetUPDATE.BulletHits[wb_aero].BulletTraj;
			Q_BulletHit->BulletHit[wb_aero].CollNormal = player[g_Player]->NetUPDATE.BulletHits[wb_aero].CollNormal;
			}

		wb_aero++;
		}


	//MessageBox(NULL,"Melee Hits  \n","ERROR",MB_OK);


	//#### Update Melee Hits
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomMelHit);

#if 0
	if(player[g_Player]->NetUPDATE.NomMelHit < _->NomMelHit)
		{
		wb_aero = player[g_Player]->NetUPDATE.NomMelHit;
		while(wb_aero < _->NomMelHit)
			{
			Q_MeleeHit->MeleeHit[wb_aero].Live = 0;
			Q_MeleeHit->MeleeHit[wb_aero].INIT = 0;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius = 301;
			Qpo->Light_Remove(Q_MeleeHit->MeleeHit[wb_aero].Light);
			wb_aero++;
			}
		}
#endif

	_->NomMelHit = player[g_Player]->NetUPDATE.NomMelHit;

	wb_aero = 0;
	while(wb_aero < player[g_Player]->NetUPDATE.NomMelHit)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Live);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].HitTYPE);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].HitRESULT);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Impact);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Bonenum);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].ReactionNorm);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].HitPowerPercent);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BloodAmt);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Radius);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].MaxRadius);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].StartFade);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Blue);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AttackSTRENGTH);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AttackSNAP);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AX);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AY);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AZ);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BX);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BY);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BZ);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].CX);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].CY);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].CZ);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Translation);

		if(player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Live == 1)
			{
			if(Q_MeleeHit->MeleeHit[wb_aero].Live == 0) Q_MeleeHit->MeleeHit[wb_aero].INIT = 0;

			Q_MeleeHit->MeleeHit[wb_aero].Live = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Live;
			Q_MeleeHit->MeleeHit[wb_aero].HitTYPE = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].HitTYPE;
			Q_MeleeHit->MeleeHit[wb_aero].HitRESULT = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].HitRESULT;

			Q_MeleeHit->MeleeHit[wb_aero].Impact = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Impact;
			Q_MeleeHit->MeleeHit[wb_aero].Bonenum = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Bonenum;
			Q_MeleeHit->MeleeHit[wb_aero].ReactionNorm = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].ReactionNorm;
			Q_MeleeHit->MeleeHit[wb_aero].HitPowerPercent = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].HitPowerPercent;
			Q_MeleeHit->MeleeHit[wb_aero].BloodAmt = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BloodAmt;

			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Radius = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Radius;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.MaxRadius = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].MaxRadius;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.StartFade = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].StartFade;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Red = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Red;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Green = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Green;
			Q_MeleeHit->MeleeHit[wb_aero].Expandro3D.Blue = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Blue;

			Q_MeleeHit->MeleeHit[wb_aero].AttackSTRENGTH = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AttackSTRENGTH;
			Q_MeleeHit->MeleeHit[wb_aero].AttackSNAP = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AttackSNAP;

			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][0] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AX;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][1] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AY;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[0][2] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].AZ;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][0] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BX;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][1] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BY;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[1][2] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].BZ;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][0] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].CX;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][1] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].CY;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Matrix.m[2][2] = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].CZ;
			Q_MeleeHit->MeleeHit[wb_aero].AttboneXF.Translation = player[g_Player]->NetUPDATE.MeleeHits[wb_aero].Translation; 
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Small Energy  \n","ERROR",MB_OK);


	//##### Update Small Energy
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomSEnergy);

	if(player[g_Player]->NetUPDATE.NomSEnergy < _->NomSEnergy)
		{
		wb_jet = _->NomSEnergy - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomSEnergy)
			{
			Q_SEnergy->SEnergy[wb_jet].Live = 0;
			if(Q_SEnergy->SEnergy[wb_jet].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[wb_jet].Light);
			//if(Q_SEnergy->SEnergy[wb_jet].Sound != NULL) geSound_StopSound(SoundSys, Q_SEnergy->SEnergy[wb_jet].Sound);

			wb_helly = 0;
			while(wb_helly < Q_SEnergy->SEnergy[wb_jet].NomActors)
				{
				Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[wb_jet].AvatarFlag[wb_helly].Xform.Translation);
				wb_helly++;
				}

			wb_jet--;
			}
		}

	_->NomSEnergy = player[g_Player]->NetUPDATE.NomSEnergy;

	wb_aero = 0;
	while(wb_aero < _->NomSEnergy)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].Live);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].LightPos);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].TraVec);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].Speed);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].Scale);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].Alpha);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].TargetLock);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].TargetID);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].AngleX);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].AngleY);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.SEnergys[wb_aero].AngleZ);

		if(player[g_Player]->NetUPDATE.SEnergys[wb_aero].Live == 1)
			{
			if(Q_SEnergy->SEnergy[wb_aero].Live == 0) Q_SEnergy->SEnergy[wb_aero].Init = 0;
			Q_SEnergy->SEnergy[wb_aero].Live = player[g_Player]->NetUPDATE.SEnergys[wb_aero].Live;
			Q_SEnergy->SEnergy[wb_aero].LightPos = player[g_Player]->NetUPDATE.SEnergys[wb_aero].LightPos;
			Q_SEnergy->SEnergy[wb_aero].TraVec = player[g_Player]->NetUPDATE.SEnergys[wb_aero].TraVec;
			Q_SEnergy->SEnergy[wb_aero].Speed = player[g_Player]->NetUPDATE.SEnergys[wb_aero].Speed;
			Q_SEnergy->SEnergy[wb_aero].Scale = player[g_Player]->NetUPDATE.SEnergys[wb_aero].Scale;
			Q_SEnergy->SEnergy[wb_aero].Alpha = player[g_Player]->NetUPDATE.SEnergys[wb_aero].Alpha;
			Q_SEnergy->SEnergy[wb_aero].TargetLock = player[g_Player]->NetUPDATE.SEnergys[wb_aero].TargetLock;

			Q_SEnergy->SEnergy[wb_aero].TargetID = player[g_Player]->NetUPDATE.SEnergys[wb_aero].TargetID;
			if(player[g_Player]->NetUPDATE.SEnergys[wb_aero].TargetID == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_SEnergy->SEnergy[wb_aero].TargetID = 250;
			if(player[g_Player]->NetUPDATE.SEnergys[wb_aero].TargetID == 250) Q_SEnergy->SEnergy[wb_aero].TargetID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			Q_SEnergy->SEnergy[wb_aero].AngleX = player[g_Player]->NetUPDATE.SEnergys[wb_aero].AngleX;
			Q_SEnergy->SEnergy[wb_aero].AngleY = player[g_Player]->NetUPDATE.SEnergys[wb_aero].AngleY;
			Q_SEnergy->SEnergy[wb_aero].AngleZ = player[g_Player]->NetUPDATE.SEnergys[wb_aero].AngleZ;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Large Energy  \n","ERROR",MB_OK);

	//##### Update Large Energy
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomLEnergy);

	if(player[g_Player]->NetUPDATE.NomLEnergy < _->NomLEnergy)
		{
		wb_jet = _->NomLEnergy - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomLEnergy)
			{
			Qpo->Light_Remove(Q_LEnergy->LEnergy[wb_jet].Light);
			Q_LEnergy->LEnergy[wb_jet].Init = 0;
			Q_LEnergy->LEnergy[wb_jet].Live = 0;
			Q_LEnergy->LEnergy[wb_jet].EnergyLive = 0;
			Q_LEnergy->LEnergy[wb_jet].EnergyFire = 0;
			Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[wb_jet].EnergyBall.Xform.Translation);
			Qpo->Avatar_SetScale(&Q_LEnergy->LEnergy[wb_jet].EnergyBall.Avatar, 0,0,0);

			wb_jet--;
			}
		}

	_->NomLEnergy = player[g_Player]->NetUPDATE.NomLEnergy;

	wb_aero = 0;
	while(wb_aero < _->NomLEnergy)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].Live);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].LightPos);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].TraVec);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].Speed);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].Scale);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].Alpha);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].EnergyLive);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.LEnergys[wb_aero].EnergyFire);

		if(player[g_Player]->NetUPDATE.LEnergys[wb_aero].Live == 1)
			{
			if(Q_LEnergy->LEnergy[wb_aero].Live == 0) Q_LEnergy->LEnergy[wb_aero].Init = 0;
			Q_LEnergy->LEnergy[wb_aero].Live = player[g_Player]->NetUPDATE.LEnergys[wb_aero].Live;
			Q_LEnergy->LEnergy[wb_aero].LightPos = player[g_Player]->NetUPDATE.LEnergys[wb_aero].LightPos;
			Q_LEnergy->LEnergy[wb_aero].TraVec = player[g_Player]->NetUPDATE.LEnergys[wb_aero].TraVec;
			Q_LEnergy->LEnergy[wb_aero].Speed = player[g_Player]->NetUPDATE.LEnergys[wb_aero].Speed;
			Q_LEnergy->LEnergy[wb_aero].Scale = player[g_Player]->NetUPDATE.LEnergys[wb_aero].Scale;
			Q_LEnergy->LEnergy[wb_aero].Alpha = player[g_Player]->NetUPDATE.LEnergys[wb_aero].Alpha;
			Q_LEnergy->LEnergy[wb_aero].EnergyLive = player[g_Player]->NetUPDATE.LEnergys[wb_aero].EnergyLive;
			Q_LEnergy->LEnergy[wb_aero].EnergyFire = player[g_Player]->NetUPDATE.LEnergys[wb_aero].EnergyFire;
			}
		wb_aero++;
		}

	//MessageBox(NULL,"World Explosions  \n","ERROR",MB_OK);

	//##### Update World Explosions
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomExplosions);

	if(player[g_Player]->NetUPDATE.NomExplosions >= _->NomExplosions)
		{ _->NomExplosions = player[g_Player]->NetUPDATE.NomExplosions; }

	wb_aero = 0;
	while(wb_aero < player[g_Player]->NetUPDATE.NomExplosions)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.Explosions[wb_aero].Live);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.Explosions[wb_aero].Pos);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.Explosions[wb_aero].ExpSize);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.Explosions[wb_aero].LargeEnergyAvID);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.Explosions[wb_aero].CollPlaneNormal);

		if(player[g_Player]->NetUPDATE.Explosions[wb_aero].Live == 1)
			{
			if(Q_Explosion->Explosion[wb_aero].Live == 0) Q_Explosion->Explosion[wb_aero].Init = 0;
			Q_Explosion->Explosion[wb_aero].Live = player[g_Player]->NetUPDATE.Explosions[wb_aero].Live;
			Q_Explosion->Explosion[wb_aero].Pos = player[g_Player]->NetUPDATE.Explosions[wb_aero].Pos;
			Q_Explosion->Explosion[wb_aero].ExpSize = player[g_Player]->NetUPDATE.Explosions[wb_aero].ExpSize;
			Q_Explosion->Explosion[wb_aero].LargeEnergyAvID = player[g_Player]->NetUPDATE.Explosions[wb_aero].LargeEnergyAvID;
			Q_Explosion->Explosion[wb_aero].CollPlaneNormal = player[g_Player]->NetUPDATE.Explosions[wb_aero].CollPlaneNormal;
			}
		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Heal  \n","ERROR",MB_OK);

	//##### Update Cleric Heal Energy
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomHSpark);

	if(player[g_Player]->NetUPDATE.NomHSpark < _->NomHSpark)
		{
		wb_jet = _->NomHSpark - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomHSpark)
			{
			Q_HealSpark->HealSpark[wb_jet].Live = 0;
			if(Q_HealSpark->HealSpark[wb_jet].Light != NULL) Qpo->Light_Remove(Q_HealSpark->HealSpark[wb_jet].Light);
			Q_HealSpark->HealSpark[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomHSpark = player[g_Player]->NetUPDATE.NomHSpark;

	wb_aero = 0;
	while(wb_aero < _->NomHSpark)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].HTYPE);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].Pos);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].TraVec);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].Released);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].Absorbed);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].AlpFade);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.HealSparks[wb_aero].ScaleSTR);

		if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live == 1)
			{
			Q_HealSpark->HealSpark[wb_aero].Live = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Live;
			Q_HealSpark->HealSpark[wb_aero].HTYPE = player[g_Player]->NetUPDATE.HealSparks[wb_aero].HTYPE;
			Q_HealSpark->HealSpark[wb_aero].Pos = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Pos;
			Q_HealSpark->HealSpark[wb_aero].TraVec = player[g_Player]->NetUPDATE.HealSparks[wb_aero].TraVec;
			Q_HealSpark->HealSpark[wb_aero].Released = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Released;
			Q_HealSpark->HealSpark[wb_aero].Absorbed = player[g_Player]->NetUPDATE.HealSparks[wb_aero].Absorbed;

			Q_HealSpark->HealSpark[wb_aero].HealTarget = player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget;
			if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_HealSpark->HealSpark[wb_aero].HealTarget = 250;
			if(player[g_Player]->NetUPDATE.HealSparks[wb_aero].HealTarget == 250) Q_HealSpark->HealSpark[wb_aero].HealTarget = Q_Netplayer->Netplayer[0].LocalCONTROLID;

			Q_HealSpark->HealSpark[wb_aero].AlpFade = player[g_Player]->NetUPDATE.HealSparks[wb_aero].AlpFade;
			Q_HealSpark->HealSpark[wb_aero].ScaleSTR = player[g_Player]->NetUPDATE.HealSparks[wb_aero].ScaleSTR;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Spells  \n","ERROR",MB_OK);

	//##### Update Cleric Spells
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomSpell);

	if(player[g_Player]->NetUPDATE.NomSpell < _->NomSpell)
		{
		wb_jet = _->NomSpell - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomSpell)
			{
			Q_ClericSpell->ClericSpell[wb_jet].Live = 0;
			if(Q_ClericSpell->ClericSpell[wb_jet].Light != NULL) Qpo->Light_Remove(Q_ClericSpell->ClericSpell[wb_jet].Light);
			Q_ClericSpell->ClericSpell[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomSpell = player[g_Player]->NetUPDATE.NomSpell;

	wb_aero = 0;
	while(wb_aero < _->NomSpell)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].NumSpheres);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPos);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPow);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Absorbed);
		
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[0]);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[1]);
		
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[0]);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[1]);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[0]);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[0]);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[1]);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[1]);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[2]);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[2]);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[3]);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[3]);


		if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live == 1)
			{
			Q_ClericSpell->ClericSpell[wb_aero].Live = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Live;
			Q_ClericSpell->ClericSpell[wb_aero].NumSpheres = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].NumSpheres;

			Q_ClericSpell->ClericSpell[wb_aero].HealTarget = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget;
			if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget == player[g_Player]->NetUPDATE.ServerCONTROLID) Q_ClericSpell->ClericSpell[wb_aero].HealTarget = 250;
			if(player[g_Player]->NetUPDATE.ClericSpells[wb_aero].HealTarget == 250) Q_ClericSpell->ClericSpell[wb_aero].HealTarget = Q_Netplayer->Netplayer[0].LocalCONTROLID;
			
			Q_ClericSpell->ClericSpell[wb_aero].LightPos = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPos;
			Q_ClericSpell->ClericSpell[wb_aero].LightPow = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].LightPow;
			Q_ClericSpell->ClericSpell[wb_aero].Absorbed = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Absorbed;
			
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Radius = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Radius = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Radius[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].StartFade = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].StartFade = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].StartFade[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[0];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[0].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[0];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[1];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[1].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[1];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[2];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[2].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[2];

			Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Leftvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Leftvec[3];
			Q_ClericSpell->ClericSpell[wb_aero].Sphere[3].Upvec = player[g_Player]->NetUPDATE.ClericSpells[wb_aero].Upvec[3];
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Cleric Plasma  \n","ERROR",MB_OK);

	//##### Update Cleric Plasma
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomPlasma);

	if(player[g_Player]->NetUPDATE.NomPlasma < _->NomPlasma)
		{
		wb_jet = _->NomPlasma - 1;
		while(wb_jet >= player[g_Player]->NetUPDATE.NomPlasma)
			{
			Q_ClericPlasma->ClericPlasma[wb_jet].Live = 0;
			if(Q_ClericPlasma->ClericPlasma[wb_jet].Light != NULL) Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[wb_jet].Light);
			Q_ClericPlasma->ClericPlasma[wb_jet].LightON = 0;
			wb_jet--;
			}
		}

	_->NomPlasma = player[g_Player]->NetUPDATE.NomPlasma;

	wb_aero = 0;
	while(wb_aero < _->NomPlasma)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Pos);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].TraVec);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Speed);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Alpha);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].PartType);

		if(player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live == 1)
			{
			Q_ClericPlasma->ClericPlasma[wb_aero].Live = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Live;
			Q_ClericPlasma->ClericPlasma[wb_aero].Pos = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Pos;
			Q_ClericPlasma->ClericPlasma[wb_aero].TraVec = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].TraVec;
			Q_ClericPlasma->ClericPlasma[wb_aero].Speed = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Speed;
			Q_ClericPlasma->ClericPlasma[wb_aero].Alpha = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].Alpha;
			Q_ClericPlasma->ClericPlasma[wb_aero].PartType = player[g_Player]->NetUPDATE.ClericPlasmas[wb_aero].PartType;
			}

		wb_aero++;
		}

	//MessageBox(NULL,"Net Effects Control  \n","ERROR",MB_OK);

	//##### Update Net Effects Control
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomNetEffectControl);

	_->NomNetEffectControl = player[g_Player]->NetUPDATE.NomNetEffectControl;

	wb_aero = 0;
	while(wb_aero < _->NomNetEffectControl)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type);
		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type == 0) Buffer_GetAngle(&player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Pos);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Effintensity);
		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type == 1) Buffer_GetByte(&player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].AvID);

		if(player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live > Q_NetEffectControl->NetEffectControl[wb_aero].Live)
			{ Q_NetEffectControl->NetEffectControl[wb_aero].Active = 1; }

		Q_NetEffectControl->NetEffectControl[wb_aero].Live = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Live;
		Q_NetEffectControl->NetEffectControl[wb_aero].Type = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Type;
		Q_NetEffectControl->NetEffectControl[wb_aero].Pos = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Pos;
		Q_NetEffectControl->NetEffectControl[wb_aero].Effintensity = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].Effintensity;
		Q_NetEffectControl->NetEffectControl[wb_aero].AvID = player[g_Player]->NetUPDATE.NetEffectControls[wb_aero].AvID;

		wb_aero++;
		}


	//##### Update Net Zone Increment
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomNetZonesINC);

	wb_aero = 0;
	while(wb_aero < player[g_Player]->NetUPDATE.NomNetZonesINC)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].AVID);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Maxs);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Mins);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke.CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0].CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1].CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2].CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3].CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4].CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog.CNT);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.INT);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.ON);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Red);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Green);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Blue);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Alpha);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.TIMER);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight.CNT);

		Buffer_GetAngle(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMINS);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMAXS);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandSTRENGTH);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_TimeScale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Gravity);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LifeINC);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyINC);

		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_intBoost);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyEff);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Height);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Weight);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Strength);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Quickness);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Dexterity);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Constitution);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_AggPower);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_DefPower);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmStr);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmStr);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegStr);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegStr);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmSnap);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmSnap);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegSnap);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegSnap);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPAccuracy);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPDrawSPD);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPReloadSPD);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPRecoilHR);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKmovespeed);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKpower);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINK3intensity);


		//====---- AQUIRE ZONE ----====
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].AVID;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Mins;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Maxs;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMINS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandMAXS;

		//### FIND CORE
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
		Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
		Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

		//### EXPAND OUTWARDS MINS AND MAXS
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
		Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
		Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
		Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
		Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ExpandSTRENGTH;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Smoke;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[0];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[1];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[2];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[3];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Effect[4];

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].Fog;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].FogLight;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_TimeScale;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Gravity;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LifeINC;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyINC;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_intBoost;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_EnergyEff;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Height;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Weight;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Strength;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Quickness;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Dexterity;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_Constitution;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_AggPower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_DefPower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RArmSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LArmSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_RLegSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_LLegSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPAccuracy;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPDrawSPD;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPReloadSPD;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_WEPRecoilHR;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKmovespeed;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINKpower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = player[g_Player]->NetUPDATE.NetZONEINC[wb_aero].ZONEINC_JINK3intensity;

		Corner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
		DX = TempVec1;
		DX.y = 0;
		DX.z = 0;
		DY = TempVec1;
		DY.x = 0;
		DY.z = 0;
		DZ = TempVec1;
		DZ.y = 0;
		DZ.x = 0;
		Q.DrawOrientedBoundBox(&Corner, &DX, &DY, &DZ);

		if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998) Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;

		//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//geSound_PlaySoundDef(SoundSys, Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, GE_false);

		wb_aero++;
		}


	//##### Update Net Zone ENTITY Increment
	Buffer_GetFloat(&player[g_Player]->NetUPDATE.NomNetZoneENTITY);

	wb_aero = 0;
	while(wb_aero < player[g_Player]->NetUPDATE.NomNetZoneENTITY)
		{
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].TYPE);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ID);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ZoneID);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].QObjID);
		Buffer_GetAngle(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Range);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Scale);
		Buffer_GetFloat(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].StrengthMAX);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].CollisionTYPE);
		Buffer_GetByte(&player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].AvID);

		switch(player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].TYPE)
			{
			case 0:
				{
				//====----- SENTRY BUILD ------====

				if(_->NomBMSentry < 148)
					{
					Q_BMSentry->BMSentry[_->NomBMSentry].Pos = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos;
					Q_BMSentry->BMSentry[_->NomBMSentry].ZoneID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].ZoneID;
					Q_BMSentry->BMSentry[_->NomBMSentry].QObjID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].QObjID;
					Q_BMSentry->BMSentry[_->NomBMSentry].Range = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Range;
					Q_BMSentry->BMSentry[_->NomBMSentry].LIVE = 1;

					_->NomBMSentry++;
					}

				//#### INITIALISE THE Q_Object->Object TO HOUSE THE SENTRY

				if(_->NomQObject < 148)
					{
					Q_Object->Object[_->NomQObject].Pos = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos;
					Q_Object->Object[_->NomQObject].Scale = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Scale;
					Q_Object->Object[_->NomQObject].StrengthMAX = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].StrengthMAX;
					Q_Object->Object[_->NomQObject].StrengthBANK = Q_Object->Object[_->NomQObject].StrengthMAX;
					Q_Object->Object[_->NomQObject].CollisionTYPE = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].CollisionTYPE;
					Q_Object->Object[_->NomQObject].AvID = player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].AvID;
					Q_Object->Object[_->NomQObject].LIVE = 1;

					_->NomQObject++;
					}

				//geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->NetUPDATE.NetZoneENTITYINC[wb_aero].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
				//geSound_PlaySoundDef(SoundSys, Medias->S_Build, _->Volume, _->Pan, _->S_TimeScale, GE_false);
				}break;
			}
		wb_aero++;
		}


	//MessageBox(NULL,"Update Success 1  \n","ERROR",MB_OK);


	//FRLs
	Buffer_GetFloat(&_->FRLtarget);
	Buffer_GetByte(&_->FRLON);
	//_->FRLON = 0;
#endif

	//MessageBox(NULL,"Update Success 2  \n","ERROR",MB_OK);
}

bool Q_Network::acStartNetplayer(int f_VecID, int f_AvatarID, int f_CDATAID, int f_BDATAID, int f_TEAM)
{
	printf("f_BDATAID %i\n", f_BDATAID);
	printf("f_BDATAID %i\n", f_BDATAID);
	printf("f_BDATAID %i\n", f_BDATAID);
	printf("f_BDATAID %i\n", f_BDATAID);
	printf("f_BDATAID %i\n", f_BDATAID);
	printf("f_BDATAID %i\n", f_BDATAID);

	int m_AVSLOT;
	
	if(Q_Forge->Forge[f_AvatarID].LIVE == 1 && Q_Forge->Forge[f_AvatarID].HB_Lives > 0)
		{
		return false;
		}
	else m_AVSLOT = f_AvatarID;

	QpoVec3d i_Position;
	QpoVec3d i_Angles;

	i_Position.x = 0;
	i_Position.y = 0;
	i_Position.z = 0;

	i_Angles.x = 0;
	i_Angles.y = 0;
	i_Angles.z = 0;

	printf("acStartNetplayer %i\n", m_AVSLOT);

	if(f_CDATAID >= player[g_Player]->CDATAS[f_VecID].NomCharacters)
		{
		f_CDATAID = 0;
		printf("ERROR:::acStartNetplayer::: f_CDATAID too high to be realistically used in function\n");
		}

	if(f_BDATAID >= m_QActiveFramework->meshShellTemplates.size())
		{
		f_BDATAID = 0;
		printf("ERROR:::acStartNetplayer::: f_BDATAID too high to be realistically used in function\n");
		}

	//Q_Forge->Forge[m_AVSLOT].m_Own = 0;
	Q_Forge->Forge[m_AVSLOT].HB_Lives = 5;
	Q_Forge->Forge[m_AVSLOT].HB_LiveResetSW = 1;

	//###--- Set CHARDATA for Avatar ---###//
	Q_Forge->Forge[m_AVSLOT].CharDATA = player[g_Player]->CDATAS[f_VecID].CharDATA[f_CDATAID];

	Q_Forge->Forge[m_AVSLOT].CharDATA.m_VecID = f_VecID;
	Q_Forge->Forge[m_AVSLOT].CharDATA.CDataID = f_CDATAID;

	Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID = f_BDATAID;
	Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF = f_BDATAID;
	Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF = f_BDATAID;

	Q_Forge->Forge[m_AVSLOT].upspeed = -15;
	Q_Forge->Forge[m_AVSLOT].Mins.x = -30.f;
	Q_Forge->Forge[m_AVSLOT].Mins.y = -45.f;
	Q_Forge->Forge[m_AVSLOT].Mins.z = -30.f;
	Q_Forge->Forge[m_AVSLOT].Maxs.x = 30.f;
	Q_Forge->Forge[m_AVSLOT].Maxs.y = 45.f;
	Q_Forge->Forge[m_AVSLOT].Maxs.z = 30.f;

	Q_Forge->Forge[m_AVSLOT].PlayerSpeed = PLAYER_SPEED;

	Q_Forge->Forge[m_AVSLOT].GravityAlter = 1;

	Q_Forge->Forge[m_AVSLOT].NetMoveScale = 1;

	//Fill Weapon Ammo
	Q_Forge->Forge[m_AVSLOT].WeaponAmmo = 32;

	Q_Forge->Forge[m_AVSLOT].HB_Illumination = 255;
	Q_Forge->Forge[m_AVSLOT].HB_Dead = 0;

	//Body and Mind
	Q_Forge->Forge[m_AVSLOT].Q_Heart.HeartIncrement = 0;
	Q_Forge->Forge[m_AVSLOT].Q_Heart.PulseRate = 1;
	Q_Forge->Forge[m_AVSLOT].Q_Brain.Aggression = 70;

	Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID = f_BDATAID;
	Q_Forge->Forge[m_AVSLOT].AVDATID = AVSLOT;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].AVATARID = AVSLOT;
	//Q_Forge->Forge[m_AVSLOT].NetplayerFLAG = 1;

	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].BDATID = f_BDATAID;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].CDATID = f_CDATAID;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].LIVE = 1;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].NETAVATAR = 1;
	player[g_Player]->BFO.AVATARDATA[m_AVSLOT].TEAM = f_TEAM;

	//#### Set Role
	Q_Forge->Forge[m_AVSLOT].CharDATA.TEAM = f_TEAM;
	Q_Forge->Forge[m_AVSLOT].Team = f_TEAM;

	Q_Forge->Forge[m_AVSLOT].Role = 0;
	Q_Forge->Forge[m_AVSLOT].Rank = 1;
	Q_Forge->Forge[m_AVSLOT].LEVEL = Q_Forge->Forge[m_AVSLOT].CharDATA.Level;

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh = new unAvatar();

	if(Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF > 11 || Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF < 0) Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF = 0;

	//if(AVATAR_PHYSICS_ENABLE) m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	//else m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF]->clone_struct(Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh);

	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);
	printf("Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF %i\n", Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF);

	/*Q_Forge->Forge[m_AVSLOT].Xform.Translation.x = 0;
	Q_Forge->Forge[m_AVSLOT].Xform.Translation.y = 0;
	Q_Forge->Forge[m_AVSLOT].Xform.Translation.z = 0;
	Q_Forge->Forge[m_AVSLOT].Xform.Matrix.load_identity();

	//##### Starting position
	Ange.y = i_Angles.y + (PI);
	if(Ange.y > (2*PI)) Ange.y = Ange.y - (PI*2);
	if(Ange.y < 0) Ange.y = (PI*2) - Ange.y;
	Ange.x = (PI/2);
	Ange.z = 0;

	// Set the actor's angle
	Qpo->Transform_RotateX(&Q_Forge->Forge[m_AVSLOT].Xform, Ange.x);
	Qpo->Transform_RotateY(&Q_Forge->Forge[m_AVSLOT].Xform, Ange.z);
	Qpo->Transform_RotateZ(&Q_Forge->Forge[m_AVSLOT].Xform, Ange.y);

	Q_Forge->Forge[m_AVSLOT].STOREMatrix = Q_Forge->Forge[m_AVSLOT].Xform;

	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.x = 0;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.y = 0;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.z = 0;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Matrix.load_identity();

	// Set the actor's angle
	Qpo->Transform_RotateX(&Q_Forge->Forge[m_AVSLOT].AV.Xform, Ange.x);		//Update Avatar's starting facing direction
	Qpo->Transform_RotateY(&Q_Forge->Forge[m_AVSLOT].AV.Xform, Ange.z);
	Qpo->Transform_RotateZ(&Q_Forge->Forge[m_AVSLOT].AV.Xform, Ange.y);

	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.x = i_Position.x;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.y = i_Position.y;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.z = i_Position.z;

	Q_Forge->Forge[m_AVSLOT].Angles.y = i_Angles.y;
	Q_Forge->Forge[m_AVSLOT].trueAngles.y = i_Angles.y;
	Q_Forge->Forge[m_AVSLOT].STOREAngles.y = i_Angles.y;*/

#if 0
	QpoActor_SetScale(Q_Forge->Forge[m_AVSLOT].AV.Avatar, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

	Q_Forge->Forge[m_AVSLOT].idlespeed = 0.1;

	if(Q_Forge->Forge[m_AVSLOT].LEVEL > 1000) Q_Forge->Forge[m_AVSLOT].LEVELFactor = 1;
	else Q_Forge->Forge[m_AVSLOT].LEVELFactor = (((float)Q_Forge->Forge[m_AVSLOT].LEVEL + 1) / 1000);

	Q_Forge->Forge[m_AVSLOT].HB_MaxHealth = 500 * (((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
	Q_Forge->Forge[m_AVSLOT].HB_Health = Q_Forge->Forge[m_AVSLOT].HB_MaxHealth;

	Q_Forge->Forge[m_AVSLOT].HB_MaxEnergy = 500;
	Q_Forge->Forge[m_AVSLOT].HB_Energy = Q_Forge->Forge[m_AVSLOT].HB_MaxEnergy;
	
	if(Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR < 0 || Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrHEADARMOUR %i Out of range\n", m_AVSLOT, Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR);
	else if(Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR < 0 || Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrUPPERARMOUR %i Out of range\n", m_AVSLOT, Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR);
	else if(Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR < 0 || Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrLOWERARMOUR %i Out of range\n", m_AVSLOT, Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR);
	else Q_Forge->Forge[m_AVSLOT].HB_MaxArmour = ((float)(Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);
	Q_Forge->Forge[m_AVSLOT].HB_Armour = Q_Forge->Forge[m_AVSLOT].HB_MaxArmour;

	Q_Forge->Forge[m_AVSLOT].JINK3_PowerFactor = 1;

	//#### RESET SPELLS
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[0].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[1].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[2].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[3].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[4].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[5].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[6].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[7].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[8].LIVE = 0;
	Q_Forge->Forge[m_AVSLOT].CharDATA.SpellSLOT[9].LIVE = 0;

	//####### RELATIVE MOVEMENT SPEED
	Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.EnergyEff / 6000);

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.Visible = true;

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.IDflag = AVSLOT;

	Qpo->Avatar_SetLighting(&Q_Forge->Forge[m_AVSLOT].AV.Avatar,true,&goup,200,200,200,190,145,100,false,8,NULL,true);

	//Q_Forge->Forge[m_AVSLOT].Angles.y = Ange.y;
	//Q_Forge->Forge[m_AVSLOT].trueAngles.y = Ange.y;
	//Q_Forge->Forge[m_AVSLOT].STOREAngles.y = Ange.y;

	Q_Forge->Forge[m_AVSLOT].Extenbox.Min.x = Q_Forge->Forge[m_AVSLOT].Mins.x;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Min.y = Q_Forge->Forge[m_AVSLOT].Mins.y;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Min.z = Q_Forge->Forge[m_AVSLOT].Mins.z;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Max.x = Q_Forge->Forge[m_AVSLOT].Maxs.x;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Max.y = Q_Forge->Forge[m_AVSLOT].Maxs.y;
	Q_Forge->Forge[m_AVSLOT].Extenbox.Max.z = Q_Forge->Forge[m_AVSLOT].Maxs.z;
		
		//### Load Player Weapon
	Q_Forge->Forge[m_AVSLOT].Weapon.Avatar = 1;

	Q_Forge->Forge[m_AVSLOT].Weapon.Scale.x = 1;
	Q_Forge->Forge[m_AVSLOT].Weapon.Scale.y = 1;
	Q_Forge->Forge[m_AVSLOT].Weapon.Scale.z = 1;

	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.x = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.y = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.z = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.x = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.y = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.z = 20.f;

	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.x = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.y = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Mins.z = -20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.x = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.y = 20.f;
	Q_Forge->Forge[m_AVSLOT].Weapon.Maxs.z = 20.f;

	Q_Forge->Forge[m_AVSLOT].Weapon.Visible = true;

	Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[m_AVSLOT].Weapon.Xform.Translation);

	Qpo->Mesh_SetAlpha(&Q_Forge->Forge[m_AVSLOT].Weapon, 0);

	Q_Forge->Forge[m_AVSLOT].WeaponDISPLAY = 0;

	if(Q_Forge->Forge[m_AVSLOT].CharDATA.Class == 2)
		{
		Q_Forge->Forge[m_AVSLOT].Shield.Mins.x = -500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Mins.y = -500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Mins.z = -500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Maxs.x = 500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Maxs.y = 500.f;
		Q_Forge->Forge[m_AVSLOT].Shield.Maxs.z = 500.f;

		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[m_AVSLOT].Shield.Avatar, 40);

		fogbox.Min.x = Q_Forge->Forge[m_AVSLOT].Shield.Mins.x;
		fogbox.Min.y = Q_Forge->Forge[m_AVSLOT].Shield.Mins.y;
		fogbox.Min.z = Q_Forge->Forge[m_AVSLOT].Shield.Mins.z;
		fogbox.Max.x = Q_Forge->Forge[m_AVSLOT].Shield.Maxs.x;
		fogbox.Max.y = Q_Forge->Forge[m_AVSLOT].Shield.Maxs.y;
		fogbox.Max.z = Q_Forge->Forge[m_AVSLOT].Shield.Maxs.z;

		Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[m_AVSLOT].Shield.Xform.Translation);

		Q_Forge->Forge[m_AVSLOT].Shield.Avatar.IDflag = 251;
		}

	//### Load Fighter Shadows

	Q_Forge->Forge[m_AVSLOT].ShadowsOn = false;
	Q_Forge->Forge[m_AVSLOT].ShadowALPHA = 240;

	wb_aero = 0;
	while(wb_aero <= 2)
		{
		wb_aero++;

		if(Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF > 11 || Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF < 0) Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF = 0;

		//Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.Mesh = new unAvatar();
		//m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF]->clone_struct(Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.Mesh);

		/*Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform.Translation.x = 0;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform.Translation.y = 0;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform.Translation.z = 0;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform.Matrix.load_identity();

		//##### Starting position
		Ange.y = i_Angles.y + (PI);
		if(Ange.y > (2*PI)) Ange.y = Ange.y - (PI*2);
		if(Ange.y < 0) Ange.y = (PI*2) - Ange.y;
		Ange.x = -(PI/2);
		Ange.z = 0;

		// Set the actor's angle
		Qpo->Transform_RotateX(&Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform, Ange.x);
		Qpo->Transform_RotateY(&Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform, Ange.y);
		Qpo->Transform_RotateZ(&Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Xform, Ange.z);*/

		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Mins.x = -20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Mins.y = -20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Mins.z = -20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Maxs.x = 20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Maxs.y = 20.f;
		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Maxs.z = 20.f;

#if 0
		QpoActor_SetScale(Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.Visible = true;

		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar, 255/(wb_aero+1));

		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.IDflag = wb_helly;
		}

	//#### Set Up Trail Flags
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[0][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[1][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[2][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[3][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[4][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[5][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[6][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[7][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[8][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[9][0] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[0][1] = 0;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[1][1] = 1;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[2][1] = 2;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[3][1] = 3;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[4][1] = 4;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[5][1] = 5;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[6][1] = 6;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[7][1] = 7;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[8][1] = 8;
	Q_Forge->Forge[m_AVSLOT].TrailFadeSpan[9][1] = 9;

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItemsAI(wb_helly);

#if 0
	//#### RESET SCALE AND LIGHTING
	QpoActor_SetScale(Q_Forge->Forge[m_AVSLOT].AV.Avatar, Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
#endif

	SCRAM = 0;
	while(SCRAM < 25)
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
		Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation;
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
		if(_->NomSpikes > 499) _->NomSpikes = 0;

		SCRAM++;
		}

	Q_Forge->Forge[m_AVSLOT].LIVE = 1;
	Q_Forge->Forge[m_AVSLOT].HB_DeadTimer = 500;

	//Begin Transforming for Camera
	//Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[m_AVSLOT].AV.Xform, &Q_Forge->Forge[m_AVSLOT].AV.Up);

	/*Qpo->Vec3d_Subtract(&Q_Forge->Forge[m_AVSLOT].AV.Up, &m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_RotationVec, &ScanTurnVec);
	Q_Forge->Forge[m_AVSLOT].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);

	//### Check Distance between Pure Left and Right to work out direction of Turn
	Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[m_AVSLOT].AV.Xform, &Q_Forge->Forge[m_AVSLOT].AV.Left);

	Qpo->Vec3d_Copy(&Q_Forge->Forge[m_AVSLOT].AV.Left, &Q_Forge->Forge[m_AVSLOT].AV.Right);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[m_AVSLOT].AV.Right);

	ScanDistL = Qpo->Vec3d_DistanceBetween(&m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_RotationVec, &Q_Forge->Forge[m_AVSLOT].AV.Left);
	ScanDistR = Qpo->Vec3d_DistanceBetween(&m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_RotationVec, &Q_Forge->Forge[m_AVSLOT].AV.Right);

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

	if(ScanDistL < ScanDistR) Q_Forge->Forge[m_AVSLOT].ScanTurnAng *= -1;

	Q_Forge->Forge[m_AVSLOT].trueAngles.y = Q_Forge->Forge[m_AVSLOT].ScanTurnAng;

	Q_Forge->Forge[m_AVSLOT].Angles.y = Q_Forge->Forge[m_AVSLOT].ScanTurnAng;
	if(Q_Forge->Forge[m_AVSLOT].Angles.y > (PI*2)) Q_Forge->Forge[m_AVSLOT].Angles.y = 0;
	if(Q_Forge->Forge[m_AVSLOT].Angles.y < 0) Q_Forge->Forge[m_AVSLOT].Angles.y = (PI*2);

	Q_Forge->Forge[m_AVSLOT].STOREAngles.y = Q_Forge->Forge[m_AVSLOT].ScanTurnAng;*/

	//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[m_AVSLOT].ScanTurnAng);
	//Qpo->Transform_Multiply(&Q_Forge->Forge[m_AVSLOT].AV.Xform, &AIfriendly, &Q_Forge->Forge[m_AVSLOT].AV.Xform);

	//Q_Forge->Forge[m_AVSLOT].Xform.Matrix.load_identity();
	/*Q_Forge->Forge[m_AVSLOT].Xform.Translation.x = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.x;
	Q_Forge->Forge[m_AVSLOT].Xform.Translation.y = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.y;
	Q_Forge->Forge[m_AVSLOT].Xform.Translation.z = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.z;
	Q_Forge->Forge[m_AVSLOT].Xform.GhostTranslation.x = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.x;
	Q_Forge->Forge[m_AVSLOT].Xform.GhostTranslation.y = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.y;
	Q_Forge->Forge[m_AVSLOT].Xform.GhostTranslation.z = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.z;

	//Q_Forge->Forge[m_AVSLOT].AV.Xform.Matrix.load_identity();
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.x = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.x;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.y = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.y;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.Translation.z = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.z;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.GhostTranslation.x = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.x;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.GhostTranslation.y = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.y;
	Q_Forge->Forge[m_AVSLOT].AV.Xform.GhostTranslation.z = m_QActiveFramework->m_QSpawnPntController->m_SpawnPoint[Q_Forge->Forge[m_AVSLOT].Team]->m_CellCenter.z;*/

	//if(m_AVnom) _->NomAI++;

	if(f_AvatarID >= _->NomAI) _->NomAI = f_AvatarID + 1;

	return true;
}

bool Q_Network::acResetNetplayer(int f_VecID, int f_AvatarID, int f_CDATAID, int f_BDATAID, int f_TEAM)
{
	int m_AVSLOT;
	
	m_AVSLOT = f_AvatarID;

	printf("acResetNetplayer %i\n", m_AVSLOT);

	if(f_CDATAID >= player[g_Player]->CDATAS[f_VecID].NomCharacters)
		{
		f_CDATAID = 0;
		printf("ERROR:::acStartNetplayer::: f_CDATAID too high to be realistically used in function\n");
		}

	if(f_BDATAID >= m_QActiveFramework->meshShellTemplates.size())
		{
		f_BDATAID = 0;
		printf("ERROR:::acStartNetplayer::: f_BDATAID too high to be realistically used in function\n");
		}

	//###--- Set CHARDATA for Avatar ---###//
	Q_Forge->Forge[m_AVSLOT].CharDATA = player[g_Player]->CDATAS[f_VecID].CharDATA[f_CDATAID];

	Q_Forge->Forge[m_AVSLOT].CharDATA.m_VecID = f_VecID;
	Q_Forge->Forge[m_AVSLOT].CharDATA.CDataID = f_CDATAID;

	Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID = f_BDATAID;
	Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF = f_BDATAID;
	Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF = f_BDATAID;

	Q_Forge->Forge[m_AVSLOT].AVDATID = AVSLOT;
	player[g_Player]->CDATAS[f_VecID].AVATARDATA[m_AVSLOT].AVATARID = AVSLOT;

	player[g_Player]->CDATAS[f_VecID].AVATARDATA[m_AVSLOT].BDATID = f_BDATAID;
	player[g_Player]->CDATAS[f_VecID].AVATARDATA[m_AVSLOT].CDATID = f_CDATAID;
	player[g_Player]->CDATAS[f_VecID].AVATARDATA[m_AVSLOT].LIVE = 1;
	player[g_Player]->CDATAS[f_VecID].AVATARDATA[m_AVSLOT].NETAVATAR = 1;
	player[g_Player]->CDATAS[f_VecID].AVATARDATA[m_AVSLOT].TEAM = f_TEAM;

	//#### Set Role
	Q_Forge->Forge[m_AVSLOT].CharDATA.TEAM = f_TEAM;
	Q_Forge->Forge[m_AVSLOT].Team = f_TEAM;

	Q_Forge->Forge[m_AVSLOT].Role = 0;
	Q_Forge->Forge[m_AVSLOT].Rank = 1;
	Q_Forge->Forge[m_AVSLOT].LEVEL = Q_Forge->Forge[m_AVSLOT].CharDATA.Level;

	delete Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh;

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh = new unAvatar();

	if(Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF > 11 || Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF < 0) Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF = 0;

	//if(AVATAR_PHYSICS_ENABLE) m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF]->clone_struct_physics(Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh, Q_Forge->Forge[m_AVSLOT].CharDATA.BDataID);
	//else m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.AvatarREF]->clone_struct(Q_Forge->Forge[m_AVSLOT].AV.Avatar.Mesh);

	if(Q_Forge->Forge[m_AVSLOT].LEVEL > 1000) Q_Forge->Forge[m_AVSLOT].LEVELFactor = 1;
	else Q_Forge->Forge[m_AVSLOT].LEVELFactor = (((float)Q_Forge->Forge[m_AVSLOT].LEVEL + 1) / 1000);

	Q_Forge->Forge[m_AVSLOT].HB_MaxHealth = 500 * (((Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Constitution/100)*0.6)+0.4);
	
	if(Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR < 0 || Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrHEADARMOUR %i Out of range\n", m_AVSLOT, Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR);
	else if(Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR < 0 || Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrUPPERARMOUR %i Out of range\n", m_AVSLOT, Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR);
	else if(Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR < 0 || Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR >= 150) printf("Q_Forge->Forge[%i].CharDATA.CurrLOWERARMOUR %i Out of range\n", m_AVSLOT, Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR);
	else Q_Forge->Forge[m_AVSLOT].HB_MaxArmour = ((float)(Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrHEADARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrUPPERARMOUR].ArmourAMOUNT / 5000) * 250) + ((Q_Forge->Forge[m_AVSLOT].CharDATA.ItemDATA[Q_Forge->Forge[m_AVSLOT].CharDATA.CurrLOWERARMOUR].ArmourAMOUNT / 5000) * 250);

	//####### RELATIVE MOVEMENT SPEED
	Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[m_AVSLOT].CharDATA.BodySKILL.EnergyEff / 6000);

	Q_Forge->Forge[m_AVSLOT].AV.Avatar.Visible = true;

	//### Load Fighter Shadows

	Q_Forge->Forge[m_AVSLOT].ShadowsOn = false;
	Q_Forge->Forge[m_AVSLOT].ShadowALPHA = 240;

	wb_aero = 0;
	while(wb_aero <= 2)
		{
		wb_aero++;

		if(Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF > 11 || Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF < 0) Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF = 0;

		delete Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.Mesh;

		//Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.Mesh = new unAvatar();
		//m_QActiveFramework->meshShellTemplates[Q_Forge->Forge[m_AVSLOT].CharDATA.ShadowREF]->clone_struct(Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.Mesh);

		Q_Forge->Forge[m_AVSLOT].Shadows[wb_aero].Avatar.IDflag = m_AVSLOT;
		}

	if(Q_Forge->Forge[m_AVSLOT].LIVE == 1)
		{
		//####### DE-ACTIVATE ITEM ATTRIBUTES
		Q.DeactivateItemsAI(wb_helly);
		}

	//####### ACTIVATE ITEM ATTRIBUTES
	Q.ActivateItemsAI(wb_helly);

	Q_Forge->Forge[m_AVSLOT].LIVE = 1;

	if(m_AVSLOT >= _->NomAI) _->NomAI = m_AVSLOT + 1;

	return true;
}

};