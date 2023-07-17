/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Control Device Inputs-
	*//*- Minor Component -Player Inputs-

*/

#include "pch.h"

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

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

using namespace GVARS;

namespace GVARS
{

bool g_ButtonDWN0[2];
bool g_ButtonDWN1[2];
int g_Ticker = 0;

//##### -+ Input Stages +- #####

void Q_COREFunctions::InputPK(void)
	{
	  ////////////
	 // Push
	//
	klpress_a_pul[g_Player] = false;
	klpress_w_pul[g_Player] = false;
	klpress_s_pul[g_Player] = false;
	klpress_d_pul[g_Player] = false;

	bool f_Sunk = false;
	bool f_Stick = false;

	if(KEY_DOWN_PCX_w()/* && klpress_w_dwn[g_Player] == false*/)
		{
		klpress_w_dwn[g_Player] = true;

		//Code
		klpress_w_pul[g_Player] = true;

		f_Sunk = true;
		}
	else
		{
		klpress_w_dwn[g_Player] = false;
		}

	if(KEY_DOWN_PCX_a()/* && klpress_a_dwn[g_Player] == false*/)
		{
		klpress_a_dwn[g_Player] = true;

		//Code
		klpress_a_pul[g_Player] = true;

		f_Sunk = true;
		}
	else
		{
		klpress_a_dwn[g_Player] = false;
		}

	if(KEY_DOWN_PCX_s()/* && klpress_s_dwn[g_Player] == false*/)
		{
		klpress_s_dwn[g_Player] = true;

		//Code
		klpress_s_pul[g_Player] = true;

		f_Sunk = true;
		}
	else
		{
		klpress_s_dwn[g_Player] = false;
		}

	if(KEY_DOWN_PCX_d()/* && klpress_d_dwn[g_Player] == false*/)
		{
		klpress_d_dwn[g_Player] = true;

		//Code
		klpress_d_pul[g_Player] = true;

		f_Sunk = true;
		}
	else
		{
		klpress_d_dwn[g_Player] = false;
		}

	//playerAV[g_Player]->VecTo
	QpoVec3d f_VectorIn;

	// In
	if(klpress_w_pul[g_Player] && !klpress_a_pul[g_Player] && !klpress_s_pul[g_Player] && !klpress_d_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = 0.0f;
		playerAV[g_Player]->VecTo.y = 0.0f;
		playerAV[g_Player]->VecTo.z = 1.0f;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_IN;
		}

	// Out
	if(klpress_s_pul[g_Player] && !klpress_a_pul[g_Player] && !klpress_w_pul[g_Player] && !klpress_d_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = 0.0f;
		playerAV[g_Player]->VecTo.y = 0.0f;
		playerAV[g_Player]->VecTo.z = -1.0f;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_OUT;
		}

	// Left
	if(klpress_a_pul[g_Player] && !klpress_w_pul[g_Player] && !klpress_s_pul[g_Player] && !klpress_d_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = -1.0f;
		playerAV[g_Player]->VecTo.y = 0.0f;
		playerAV[g_Player]->VecTo.z = 0.0f;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_LEFT;
		}

	// Right
	if(klpress_d_pul[g_Player] && !klpress_a_pul[g_Player] && !klpress_s_pul[g_Player] && !klpress_w_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = 1.0f;
		playerAV[g_Player]->VecTo.y = 0.0f;
		playerAV[g_Player]->VecTo.z = 0.0f;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_RIGHT;
		}

	  //////////////////
	 // Mid - Angles //
	// In - Right
	if(klpress_w_pul[g_Player] && klpress_d_pul[g_Player] && !klpress_s_pul[g_Player] && !klpress_a_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = 0.70710677; // 2.0f;
		playerAV[g_Player]->VecTo.y = 0;
		playerAV[g_Player]->VecTo.z = 0.70710677; // 12.0f; // 10.0f ?

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_IN_RIGHT;
		}

	// In - Left
	if(klpress_w_pul[g_Player] && klpress_a_pul[g_Player] && !klpress_s_pul[g_Player] && !klpress_d_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = -0.70710677;
		playerAV[g_Player]->VecTo.y = 0;
		playerAV[g_Player]->VecTo.z = 0.70710677;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_IN_LEFT;
		}

	// Out - Right
	if(klpress_s_pul[g_Player] && klpress_d_pul[g_Player] && !klpress_a_pul[g_Player] && !klpress_w_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = 0.70710677;
		playerAV[g_Player]->VecTo.y = 0;
		playerAV[g_Player]->VecTo.z = -0.70710677;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_OUT_RIGHT;
		}

	// Out - Left
	if(klpress_a_pul[g_Player] && klpress_s_pul[g_Player] && !klpress_d_pul[g_Player] && !klpress_w_pul[g_Player])
		{
		playerAV[g_Player]->VecTo.x = -0.70710677;
		playerAV[g_Player]->VecTo.y = 0;
		playerAV[g_Player]->VecTo.z = -0.70710677;

		playerAV[g_Player]->VecToAngle = playerAV[g_Player]->VecTo;

		kldirection[g_Player] = UN_MOUSE_OUT_LEFT;
		}

	QpoVec3d f_Diff;
	float f_Length = ATTLOCKON_MAX;
	bool f_Touch = false;
	QpoVec3d f_VecLockOn;

	for(int f_Count = 0; f_Count < _->NomAI; f_Count++)
		{
		if(Q_Forge->Forge[f_Count].LIVE)
			{
			if(Q_Forge->Forge[f_Count].Team != player[g_Player]->Team)
				{
				if(Q_Forge->Forge[f_Count].HB_Dead == 0)
					{
					Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[f_Count].AV.Xform.Translation, &f_Diff);

					float f_AvatarLength = Qpo->Vec3d_Length(&f_Diff);

					if(f_AvatarLength < f_Length)
						{
						f_Length = f_AvatarLength;
						f_Touch = true;

						f_VecLockOn.x = (Q_Forge->Forge[f_Count].AV.Xform.Translation.x - playerAV[g_Player]->Xform.Translation.x) * 0.25;
						f_VecLockOn.y = 0;
						f_VecLockOn.z = (Q_Forge->Forge[f_Count].AV.Xform.Translation.z - playerAV[g_Player]->Xform.Translation.z) * 0.25;
						}
					}
				}
			}
		}

	if(player[0]->Team != player[1]->Team)
		{
		if(g_Player == 0) // Player 1
			{
			if(player[1]->HB_Dead == 0)
				{
				Qpo->Vec3d_Subtract(&playerAV[0]->Xform.Translation, &playerAV[1]->Xform.Translation, &f_Diff);

				float f_AvatarLength = Qpo->Vec3d_Length(&f_Diff);

				if(f_AvatarLength < f_Length)
					{
					f_Length = f_AvatarLength;
					f_Touch = true;

					f_VecLockOn.x = (playerAV[1]->Xform.Translation.x - playerAV[0]->Xform.Translation.x) * 0.25;
					f_VecLockOn.y = 0;
					f_VecLockOn.z = (playerAV[1]->Xform.Translation.z - playerAV[0]->Xform.Translation.z) * 0.25;
					}
				}
			}
		else if(g_Player == 1) // Player 2
			{
			if(player[0]->HB_Dead == 0)
				{
				Qpo->Vec3d_Subtract(&playerAV[1]->Xform.Translation, &playerAV[0]->Xform.Translation, &f_Diff);

				float f_AvatarLength = Qpo->Vec3d_Length(&f_Diff);

				if(f_AvatarLength < f_Length)
					{
					f_Length = f_AvatarLength;
					f_Touch = true;

					f_VecLockOn.x = (playerAV[0]->Xform.Translation.x - playerAV[1]->Xform.Translation.x) * 0.25;
					f_VecLockOn.y = 0;
					f_VecLockOn.z = (playerAV[0]->Xform.Translation.z - playerAV[1]->Xform.Translation.z) * 0.25;
					}
				}
			}
		}

	if((f_Touch == true) && (player[g_Player]->attackon == 1) && (player[g_Player]->HB_Dead == 0) && (f_Sunk == false))
		{
		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->In);
		player[g_Player]->In.y = 0.0f;
		Qpo->Vec3d_Normalize(&player[g_Player]->In);
		Qpo->Vec3d_Normalize(&f_VecLockOn);
		Qpo->Vec3d_Subtract(&f_VecLockOn, &player[g_Player]->In, &f_VectorIn);
		f_VectorIn.y = 0.0f;

		player[g_Player]->ScanTurnAng = Qpo->Vec3d_Length(&f_VectorIn);
		player[g_Player]->ScanTurnAng = asin(player[g_Player]->ScanTurnAng / 2);

		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Transform_AvatarGetRight(&playerAV[g_Player]->Xform, /*ORIG GetUP*/ &player[g_Player]->Right);
		player[g_Player]->Right.y = 0.0f;
		Qpo->Vec3d_Normalize(&player[g_Player]->Right);
		Qpo->Vec3d_Copy(&player[g_Player]->Right, &player[g_Player]->Left);
		Qpo->Vec3d_Inverse(&player[g_Player]->Left);

		Qpo->Vec3d_Normalize(&playerAV[g_Player]->VecTo);
		Qpo->Vec3d_Normalize(&playerAV[g_Player]->VecToAngle);

		ScanDistL = Qpo->Vec3d_DistanceBetween(&f_VecLockOn, &player[g_Player]->Left);
		ScanDistR = Qpo->Vec3d_DistanceBetween(&f_VecLockOn, &player[g_Player]->Right);

		if(ScanDistL < ScanDistR) player[g_Player]->ScanTurnAng *= -1;

		player[g_Player]->Angles.y += (float)player[g_Player]->ScanTurnAng;
		player[g_Player]->STRAngles.y -= (float)player[g_Player]->ScanTurnAng;
		player[g_Player]->trueAngles.y += (float)player[g_Player]->ScanTurnAng;

		TURN_SPEED = player[g_Player]->ScanTurnAng;
		UPDOWN_SPEED = 0;

		//### Spin the Player and its Avatar ###//
		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2 && ( player[g_Player]->WeaponStatus == 4 || player[g_Player]->WeaponStatus == 5 || player[g_Player]->WeaponStatus == 6 ))
			{
			TURN_SPEED /= 2.5;
			UPDOWN_SPEED /= 2.5;
			}

		if(player[g_Player]->AirJinkRotFG == 0)
			{
			Qpo->Transform_New_YRotation(&AIfriendly, TURN_SPEED);	/// Originaly -
			Qpo->Transform_Multiply(&playerAV[g_Player]->Xform, &AIfriendly, &playerAV[g_Player]->Xform);

			player[g_Player]->AvatarRotation += TURN_SPEED;
			}

		f_Stick = true;
		f_Sunk = true;
		}

	tempposSTR = mpos;
	
	if(f_Stick == false) // Player Angles
		{
		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->In);
		player[g_Player]->In.y = 0.0f;
		playerAV[g_Player]->VecTo.y = 0.0f;
		playerAV[g_Player]->VecToAngle.y = 0.0f;
		Qpo->Vec3d_Normalize(&playerAV[g_Player]->VecToAngle);
		Qpo->Vec3d_Normalize(&playerAV[g_Player]->VecTo);
		Qpo->Vec3d_Normalize(&player[g_Player]->In);

		Qpo->Vec3d_Subtract(&playerAV[g_Player]->VecToAngle, &player[g_Player]->In, &f_VectorIn);
		f_VectorIn.y = 0.0f;

		player[g_Player]->ScanTurnAng = Qpo->Vec3d_Length(&f_VectorIn);
		player[g_Player]->ScanTurnAng = asin(player[g_Player]->ScanTurnAng / 2);

		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Transform_AvatarGetRight(&playerAV[g_Player]->Xform, /*ORIG GetUP*/ &player[g_Player]->Right);
		player[g_Player]->Right.y = 0.0f;
		Qpo->Vec3d_Normalize(&player[g_Player]->Right);
		Qpo->Vec3d_Copy(&player[g_Player]->Right, &player[g_Player]->Left);
		Qpo->Vec3d_Inverse(&player[g_Player]->Left);

		ScanDistL = Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->VecToAngle, &player[g_Player]->Left);
		ScanDistR = Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->VecToAngle, &player[g_Player]->Right);

		if(ScanDistL < ScanDistR) player[g_Player]->ScanTurnAng *= -1;

		TURN_SPEED = player[g_Player]->ScanTurnAng;
		UPDOWN_SPEED = 0;

		if(f_Sunk)
			{
			player[g_Player]->Angles.y += (float)TURN_SPEED;
			player[g_Player]->STRAngles.y -= (float)TURN_SPEED;
			player[g_Player]->trueAngles.y += (float)TURN_SPEED;

			//### Spin the Player and its Avatar ###//
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2 && ( player[g_Player]->WeaponStatus == 4 || player[g_Player]->WeaponStatus == 5 || player[g_Player]->WeaponStatus == 6 ))
				{
				TURN_SPEED /= 2.5;
				UPDOWN_SPEED /= 2.5;
				}

			if(player[g_Player]->AirJinkRotFG == 0)
				{
				Qpo->Transform_New_YRotation(&AIfriendly, TURN_SPEED);	/// Originaly -
				Qpo->Transform_Multiply(&playerAV[g_Player]->Xform, &AIfriendly, &playerAV[g_Player]->Xform);

				player[g_Player]->AvatarRotation += TURN_SPEED;
				}
			}
		}

	if(!KEY_PRESS_DOWN(QIN_1))
		{
		g_ButtonDWN0[g_Player] = false;
		}

	if(!KEY_PRESS_DOWN(QIN_2))
		{
		g_ButtonDWN1[g_Player] = false;
		}

	//**********************************************************************************************************
	//**********************************************************************************************************
	// KEYBOARD AND MOUSE INPUT ********************************************************************************

	//#### NNbOT Reward System

	_->NNBOTadjust = 0;

#if 0
	if(KEY_DOWN_PK(QIN_1))	//1
		{
		_->NNBOTadjust = 1;

		
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale/5, false, &player[g_Player]->ViewXForm.Translation);
		}

	if(KEY_DOWN_PK(QIN_2))	//2
		{
		_->NNBOTadjust = 2;

		
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale/5, false, &player[g_Player]->ViewXForm.Translation);
		}

	if(KEY_DOWN_PK(QIN_3))	//3
		{
		_->NNBOTadjust = 3;

		
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale/5, false, &player[g_Player]->ViewXForm.Translation);
		}

	if(KEY_DOWN_PK(QIN_4))	//4
		{
		_->NNBOTadjust = 4;

		
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale/5, false, &player[g_Player]->ViewXForm.Translation);
		}

	if(KEY_DOWN_PK(QIN_5))	//5
		{
		_->NNBOTadjust = 5;

		
		Qpo->Sound_Play(Medias->S_KeyLog, _->Volume, _->Pan, _->S_TimeScale/5, false, &player[g_Player]->ViewXForm.Translation);
		}
#endif

	//#### ACTIVATE ANGEL COLOUR EDIT MODE
	if(KEY_DOWN_PK(QIN_F9))
		{
		if(_->ANGELeditKEYPRESSM == 0)
			{
			_->ANGELeditKEYPRESSM = 1;
			if(_->ANGELeditFF == 0)
				{
				_->ANGELeditFF = 1;

#pragma message("Server engine is oblivious to rendering variables")
#if defined(WIN32)
				g_render->infoedit = true;
#endif
				}
			else
				{
				_->ANGELeditFF = 0;
#pragma message("Server engine is oblivious to rendering variables")
#if defined(WIN32)
				g_render->infoedit = false;
#endif
				}
			}
		}
	else _->ANGELeditKEYPRESSM = 0;

	//*----KeyBoard INput Stage One----*

	//### Click Logger - For Special Attacks
	if(KEY_DOWN_LOCK(QIN_2))
		{
		player[g_Player]->KL_CLogC++;
		player[g_Player]->KL_CLogTimer = TIME;
		}

	if(player[g_Player]->KL_CLogC >= 3)
		{
		player[g_Player]->KL_CSpecial = 1;
		}
	else player[g_Player]->KL_CSpecial = 0;


		//# Reset for Click Logger
	if(TIME > player[g_Player]->KL_CLogTimer + 10) player[g_Player]->KL_CLogC = 0;


	//### Key Logger - For Air Jink
	if((player[g_Player]->Mposestate == 14) && KEY_DOWN_PK_w()) //_->mwheelroll[g_Player] == 1)
		{
		player[g_Player]->AirJinkLOGFT++;
		}

	if(player[g_Player]->AirJinkLOGFT > 2)
		{
		player[g_Player]->AirJinkLOGFT = 0;

		if(player[g_Player]->Mposestate == 14)
			{
			player[g_Player]->jumpposecnt = 0;
			player[g_Player]->blendamount[48] = 0;
			player[g_Player]->blendamount[0] = 0;
			player[g_Player]->Mposestate = 15;
			player[g_Player]->TrailsCount = 0;
			player[g_Player]->GravityON = 1;
			}
		}

	//START PLAYER MODE - WALKING
	if(player[g_Player]->PlayerMode == 0)
		{
		//*----Mouse Input----*
		// 
		//##### --- ENERGY ARCHITECT BUILD MODE --- #####
		if(player[g_Player]->KL_RTFSpecLevel > 5 && player[g_Player]->EnergyArchitect.BuildMODEON == 0 && player[g_Player]->Mposestate != 16)	//Build mode activation
			{
			helly = 0;
			while(helly < 30 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))	//TODO ADD CRYSTAL SKILL HERE
				{
				Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator->(), "BIP01 SPINE2", &BoneMat);

				//#### Initialise One Particle ####//
				
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.535f;										//1.135//0.1//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 2;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 200;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 28;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = BoneMat.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = BoneMat.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].Direction = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				helly++;
				}

			player[g_Player]->KL_RTFSpecLevel = 0;

			player[g_Player]->Q_Jink.Live = 1;
			player[g_Player]->Q_Jink.ON = 1;
			player[g_Player]->Q_Jink.Init = 0;
			player[g_Player]->Q_Jink.Limb = "BIP01 HEAD";
			player[g_Player]->Q_Jink.FogON = 1;

			
							//'Jink Ready'
			Qpo->Sound_Play(Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos

			player[g_Player]->EnergyArchitect.BuildMODEON = 1;
			}


		//#####	SENTRY BUILD build sentry
		if(KEY_DOWN_PK(QIN_1) && player[g_Player]->KL_LTFSpecLevel == 1 && player[g_Player]->WeaponStatus == 0 && player[g_Player]->EnergyArchitect.BuildMODEON == 1)	//****////BUILD\\\\****
			{
			player[g_Player]->KL_LTFSpecLevel = 0;
			player[g_Player]->EnergyArchitect.BuildMODEON = 0;

			if(player[g_Player]->EnergyArchitect.ZONING == 1 && player[g_Player]->Mposestate != 16 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY != 250)
				{
				//#### INITIALISE ONE SENTRY OBJECT IN THE CORE OF THE CURRENT ZONE

				//### FIND CORE
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core);
				Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core);
				Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core);

				if(_->NomBMSentry < 148)
					{
					Q_BMSentry->BMSentry[_->NomBMSentry].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core;
					Q_BMSentry->BMSentry[_->NomBMSentry].ZoneID = player[g_Player]->EnergyArchitect.WithinZONE;
					Q_BMSentry->BMSentry[_->NomBMSentry].QObjID = _->NomQObject;
					Q_BMSentry->BMSentry[_->NomBMSentry].Range = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].ExpandSTRENGTH;
					Q_BMSentry->BMSentry[_->NomBMSentry].Damage = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].Damage;
					Q_BMSentry->BMSentry[_->NomBMSentry].Power = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].Power;
					Q_BMSentry->BMSentry[_->NomBMSentry].FireRate = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].FireRate;
					Q_BMSentry->BMSentry[_->NomBMSentry].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].Accuracy;
					Q_BMSentry->BMSentry[_->NomBMSentry].BulletCNT = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].BulletCNT;
					Q_BMSentry->BMSentry[_->NomBMSentry].ImmCNT = 1000;

					Q_BMSentry->BMSentry[_->NomBMSentry].LIVE = 1;

					if(_->NetworkOption == 2)
						{
						Q_NetZoneENTITY->NetZoneENTITY[_->NomNetZoneENTITY].TYPE = 0;
						Q_NetZoneENTITY->NetZoneENTITY[_->NomNetZoneENTITY].ID = _->NomBMSentry;
						_->NomNetZoneENTITY++;
						}

					_->NomBMSentry++;
					}

				//#### INITIALISE THE Q_Object->Object TO HOUSE THE SENTRY

				if(_->NomQObject < 148)
					{
					Q_Object->Object[_->NomQObject].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core;
					Q_Object->Object[_->NomQObject].Scale = 65;
					Q_Object->Object[_->NomQObject].StrengthMAX = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].ArmourAMOUNT;
					Q_Object->Object[_->NomQObject].StrengthBANK = Q_Object->Object[_->NomQObject].StrengthMAX;
					Q_Object->Object[_->NomQObject].CollisionTYPE = 0;
					Q_Object->Object[_->NomQObject].AvID = 250;
					Q_Object->Object[_->NomQObject].LIVE = 1;

					_->NomQObject++;
					}
				
								//'Jink Ready'
				Qpo->Sound_Play(Medias->S_Build, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			else
				{
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			}

		//#####	Energy Pylon ####//
		if(player[g_Player]->KL_LTFSpecLevel == 1 && player[g_Player]->WeaponStatus == 0 && player[g_Player]->EnergyArchitect.BuildMODEON == 1)	//****////BUILD\\\\****
			{
			player[g_Player]->KL_LTFSpecLevel = 0;
			player[g_Player]->EnergyArchitect.BuildMODEON = 0;

			if(player[g_Player]->EnergyArchitect.ZONING == 1 && player[g_Player]->Mposestate != 16 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY != 250)
				{
				//#### INITIALISE ONE ENERGY PYLON OBJECT IN THE CORE OF THE CURRENT ZONE

				//### FIND CORE
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core);
				Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core);
				Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core);

				if(_->NomBMSentry < 148)
					{
					Q_Building->Building[_->NomBuilding].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core;
					Q_Building->Building[_->NomBuilding].m_inZone = player[g_Player]->EnergyArchitect.WithinZONE;
					Q_Building->Building[_->NomBuilding].m_QObjectID = _->NomQObject;
					Q_Building->Building[_->NomBuilding].Range = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].ExpandSTRENGTH;
					Q_Building->Building[_->NomBuilding].m_BuildingType = 0;	//Energy Pylon
					Q_Building->Building[_->NomBuilding].AVID = -1;
					Q_Building->Building[_->NomBuilding].Team = player[g_Player]->Team;
					Q_Building->Building[_->NomBuilding].m_Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence;
					Q_Building->Building[_->NomBuilding].ImmCNT = 1000;

					Q_Building->Building[_->NomBuilding].LIVE = 1;

					if(_->NetworkOption == 2)
						{
						Q_NetZoneENTITY->NetZoneENTITY[_->NomNetZoneENTITY].TYPE = 0;
						Q_NetZoneENTITY->NetZoneENTITY[_->NomNetZoneENTITY].ID = _->NomBuilding;
						_->NomNetZoneENTITY++;
						}

					_->NomBuilding++;
					}

				//#### INITIALISE THE Q_Object->Object TO HOUSE THE SENTRY

				if(_->NomQObject < 148)
					{
					Q_Object->Object[_->NomQObject].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].Core;
					Q_Object->Object[_->NomQObject].Scale = 65;
					Q_Object->Object[_->NomQObject].StrengthMAX = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZSENTRY].ArmourAMOUNT;
					Q_Object->Object[_->NomQObject].StrengthBANK = Q_Object->Object[_->NomQObject].StrengthMAX;
					Q_Object->Object[_->NomQObject].CollisionTYPE = 0;
					Q_Object->Object[_->NomQObject].AvID = 250;
					Q_Object->Object[_->NomQObject].LIVE = 1;

					_->NomQObject++;
					}
				
								//'Jink Ready'
				Qpo->Sound_Play(Medias->S_Build, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			else
				{
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			}


		if(player[g_Player]->KL_BTFSpecLevel == 1 && player[g_Player]->Aposestate != 30 && player[g_Player]->Aposestate != 51 && player[g_Player]->Aposestate != 52 && player[g_Player]->Mposestate != 16)		//### Deflect Attack
			{
			if(player[g_Player]->HB_Energy >= 20 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
				{
				player[g_Player]->HB_Energy -= 20 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
				player[g_Player]->HB_EnergyTimer = TIME;


				if(player[g_Player]->attackon)
					{
#if 0
					player[g_Player]->DeflectPower = 0;
#endif

					player[g_Player]->Deft_InReact = 1;
					player[g_Player]->Deft_PoseState = player[g_Player]->Aposestate;
					player[g_Player]->Deft_attposecnt = player[g_Player]->attposecnt;
					player[g_Player]->Deft_HitReactScale = player[g_Player]->HitReactScale;
					}

				//###Cancellation
				player[g_Player]->astackcnt = 0;
				player[g_Player]->astackrun = 0;
				player[g_Player]->astackcntdir[0] = 0;

				player[g_Player]->Block = 0;
				player[g_Player]->Blocking = 0;
				player[g_Player]->BlockHeight = 0;

				player[g_Player]->attackstack[player[g_Player]->astackcnt] = 63;
				player[g_Player]->KL_BTFSpecLevel = 0;

				player[g_Player]->attposecnt = 0;
				player[g_Player]->Aposestate = 0;
				player[g_Player]->blendamount[0] = 0;
				player[g_Player]->blendamount[98] = 0;
				player[g_Player]->TrailsOn = 0;
				player[g_Player]->attackon = 0;

				player[g_Player]->astackcntdir[0]++;
				player[g_Player]->astackcnt++;

					//'Jink'		TODO NEW SOUND
				//Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation);
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation);
				}
			else
				{
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			}


		//##### Jink status Control
		if(player[g_Player]->Aposestate == 85 || player[g_Player]->Aposestate == 86 || player[g_Player]->Aposestate == 87)
			{
			if(KEY_DOWN_LOCK(QIN_1))
				{
				player[g_Player]->Aposestate = 86;
				}

			if(KEY_DOWN_LOCK(QIN_2))
				{
				player[g_Player]->Aposestate = 87;
				}
			}


			//##### Mouse Activated Attacks
		if(KEY_DOWN_LOCK(QIN_1) && player[g_Player]->WeaponStatus == 0 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30 && player[g_Player]->Mposestate != 16) && player[g_Player]->EnergyArchitect.BuildMODEON == 0)	//****////PUNCHS\\\\****
			{
			if(g_ButtonDWN0[g_Player] == false)
				{
				g_ButtonDWN0[g_Player] = true;

				if(player[g_Player]->astackcnt <= 6)
					{
					if(!KEY_DOWN_PK(QIN_z))
						{
						noot=0;

						if(KEY_DOWN_PC_w())	//FORWARD ATTACKS
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

							if(player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1) //AirBorn
								{
								if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
								if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
								if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
								if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
								if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
								if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
								if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 83;

								player[g_Player]->blendamount[4]=0;
								player[g_Player]->AJPushOffON = 0;
								player[g_Player]->Running = 0;
								//player[g_Player]->AirBorn = 0;
								player[g_Player]->TimeHoleFLAG = 0;
								}
							else
								{
								if(player[g_Player]->Running == 1) //Running
									{
									player[g_Player]->Running = 0;
									player[g_Player]->RunningCount = 0;
									if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 46;
									}
								else
									{
									if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
									if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 8;
									if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
									if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 67;
									if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 67;
									if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 67;
									if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 67;
									}
								}

							player[g_Player]->astackcntdir[0]++;
							}
						else noot++;

						if(KEY_DOWN_PK(QIN_SHIFT))	//BACKWARD ATTACKS
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

							if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 17;
							if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
							if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 71;
							if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 71;
							if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 17;
							if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 71;
							if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 17;

							player[g_Player]->astackcntdir[0]++;
							}
						else noot++;

						if(KEY_DOWN_PC_a())	//LEFT ATTACKS
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

							if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 69;
							if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
							if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
							if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 69;
							if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;
							if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;
							if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;

							player[g_Player]->astackcntdir[0]++;
							}
						else noot++;

						if(KEY_DOWN_PC_d())	//RIGHT ATTACKS
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

							if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 70;
							if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 70;
							if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;
							if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;
							if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;
							if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 10;
							if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 70;

							player[g_Player]->astackcntdir[0]++;
							}
						else noot++;

						if(noot == 4)		//STILL ATTACKS
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 1;

							if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 8;
							if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
							if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 12;
							if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 13;
							if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 9;
							if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 8;
							if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 67;

							player[g_Player]->astackcntdir[0]++;
							}

						player[g_Player]->attackstackSPECIAL[player[g_Player]->astackcnt] = 0;
						}
					else		//Low Attacks
						{
						if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

						if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 48;
						if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 47;
						if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 68;
						if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 68;
						if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 48;
						if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 47;
						if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 68;

						player[g_Player]->astackcntdir[0]++;
						player[g_Player]->attackstackSPECIAL[player[g_Player]->astackcnt] = 0;
						}


					if(player[g_Player]->KL_RTFSpecLevel == 1)		//### SkyPush
						{
						if(player[g_Player]->HB_Energy >= 25 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 25 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 58;
							player[g_Player]->KL_RTFSpecLevel = 0;

							//Q_Jink Cancelator
							player[g_Player]->Q_Jink.ON = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[72] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					if(player[g_Player]->KL_FTRSpecLevel == 1)		//### Flame Uppercut
						{
						if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff )
							{
							player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 32;
							player[g_Player]->KL_LTFSpecLevel = 0;

							//Q_Jink Cancelator
							player[g_Player]->Q_Jink.ON = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[7] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}

					if(player[g_Player]->KL_RTFSpecLevel == 2)		//### P - Combo - 2
						{
						if(player[g_Player]->HB_Energy >= 175 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 175 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 64;
							player[g_Player]->KL_RTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[7] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					if(player[g_Player]->KL_FTLSpecLevel == 2)		//### CYCLONE KICK
						{
						if(player[g_Player]->HB_Energy >= 200 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 200 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 84;
							player[g_Player]->KL_FTLSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[131] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					if(player[g_Player]->KL_LTFSpecLevel == 2)		//### JS RUSH PUNCH
						{
						if(player[g_Player]->HB_Energy >= 175 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 175 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 85;
							player[g_Player]->KL_LTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[74] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}

#if 0
					if(player[g_Player]->KL_FTLSpecLevel == 1)		//### Air Dash to ground
						{
						if(player[g_Player]->HB_Energy >= 30 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 30 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 53;
							player[g_Player]->KL_FTLSpecLevel = 0;

							//Q_Jink Cancelator
							player[g_Player]->Q_Jink.ON = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->JumpFG = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[86] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

							player[g_Player]->blendamount[4]=0;
							player[g_Player]->AJPushOffON = 0;
							player[g_Player]->Running = 0;
							//player[g_Player]->AirBorn = 0;
							player[g_Player]->TimeHoleFLAG = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}
#endif

					if(player[g_Player]->KL_FTRSpecLevel == 2)		//Jink Special Flame Uppercut
						{
						if(player[g_Player]->HB_Energy >= 240 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 240 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 57;
							player[g_Player]->KL_LTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[55] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					if(player[g_Player]->KL_LTFSpecLevel == 1)		//Rush Elbow
						{
						if(player[g_Player]->HB_Energy >= 30 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 30 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 65;
							player[g_Player]->KL_LTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[102] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

								//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}

					player[g_Player]->astackcnt++;
					}
				}
			}

			//was KEY_DOWN_LOCK
		if(KEY_DOWN_LOCK(QIN_2) && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30 && player[g_Player]->Mposestate != 16))	//****////KICKS\\\\****
			{
			if(g_ButtonDWN1[g_Player] == false)
				{
				g_ButtonDWN1[g_Player] = true;
			
				jet = 0;
				helly = 0;
				while(helly < 6)
					{
					if(player[g_Player]->attackstack[helly] == 79)
						{
						jet = 1;
						break;
						}
					if(player[g_Player]->attackstack[helly] == 29)
						{
						jet = 1;
						break;
						}
					if(player[g_Player]->attackstack[helly] == 80)
						{
						jet = 1;
						break;
						}
					if(player[g_Player]->attackstack[helly] == 81)
						{
						jet = 1;
						break;
						}
					if(player[g_Player]->attackstack[helly] == 40)
						{
						jet = 1;
						break;
						}
					helly++;
					}

				if(jet == 1)
					{
					if(!KEY_DOWN_PK(QIN_z))	//Not Low
						{
						player[g_Player]->attackstack[helly] = 40;							//STILL ATTACKS
						if(KEY_DOWN_PK_w()) player[g_Player]->attackstack[helly] = 79;		//FORWARD ATTACKS
						if(KEY_DOWN_PK(QIN_SHIFT)) player[g_Player]->attackstack[helly] = 29;		//BACKWARD
						if(KEY_DOWN_PK_a()) player[g_Player]->attackstack[helly] = 81;		//LEFT ATTACKS
						if(KEY_DOWN_PK_d()) player[g_Player]->attackstack[helly] = 80;		//RIGHT ATTACKS
						}
					else
						{
						player[g_Player]->attackstack[helly] = 44;
						}
					}

				 ////////////////////////////////////////
				// Attack Stacks attackstacks

				if(player[g_Player]->astackcnt < 6)
					{
					if(player[g_Player]->WeaponStatus == 0)
						{
						if(!KEY_DOWN_PK(QIN_z))		//Check for low attack
							{
							noot=0;

							if(KEY_DOWN_PC_w())	//FORWARD ATTACKS
								{
								if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

								if(player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1) //AirBorn
									{
									if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
									if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
									if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
									if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
									if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
									if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
									if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;

									player[g_Player]->blendamount[4]=0;
									player[g_Player]->AJPushOffON = 0;
									player[g_Player]->Running = 0;
									//player[g_Player]->AirBorn = 0;
									player[g_Player]->TimeHoleFLAG = 0;
									}
								else
									{
									if(player[g_Player]->Running == 1) //Running
										{
										player[g_Player]->Running = 0;
										player[g_Player]->RunningCount = 0;
										if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
										}
									else
										{
										if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 27;
										if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 21;
										if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;
										if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 79;
										if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 79;
										if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 79;
										if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 79;
										}
									}

								player[g_Player]->astackcntdir[0]++;
								}
							else noot++;

							if(KEY_DOWN_PK(QIN_SHIFT))	//BACKWARD ATTACKS
								{
								if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

								if(player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1) //AirBorn
									{
									if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 45;
									if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 45;
									if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 45;
									if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 29;
									if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 29;
									if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 29;
									if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 29;

									player[g_Player]->blendamount[4]=0;
									player[g_Player]->AJPushOffON = 0;
									player[g_Player]->Running = 0;
									//player[g_Player]->AirBorn = 0;
									player[g_Player]->TimeHoleFLAG = 0;
									}
								else
									{
									if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 37;
									if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 37;
									if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 37;
									if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 29;
									if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 29;
									if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 37;
									if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 37;
									}

								player[g_Player]->astackcntdir[0]++;
								}
							else noot++;

							if(KEY_DOWN_PC_a())	//LEFT ATTACKS
								{
								if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

								if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;
								if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;
								if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 81;
								if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 81;
								if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 81;
								if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;
								if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;

								player[g_Player]->astackcntdir[0]++;
								}
							else noot++;

							if(KEY_DOWN_PC_d())	//RIGHT ATTACKS
								{
								if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

								if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 11;
								if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 21;
								if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 40;
								if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 80;
								if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 80;
								if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 40;
								if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 21;

								player[g_Player]->astackcntdir[0]++;
								}
							else noot++;

							if(noot == 4)		//STILL ATTACKS
								{
								if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 1;

								if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 11;	//EDIT 37
								if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 38;
								if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 39;
								if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 40;
								if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 40;
								if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;
								if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 33;

								player[g_Player]->astackcntdir[0]++;
								//if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;
								}

							player[g_Player]->attackstackSPECIAL[player[g_Player]->astackcnt] = 0;
							}
						else		//Low Attacks
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

							if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 43;
							if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 72;
							if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
							if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
							if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 72;
							if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 72;
							if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;

							if(KEY_DOWN_PK(QIN_SHIFT))	//BACKWARD ATTACKS
								{
								if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 44;
								}

							player[g_Player]->astackcntdir[0]++;

							player[g_Player]->attackstackSPECIAL[player[g_Player]->astackcnt] = 0;
							}

						} //END Weapon Check
					else
						{
						if(KEY_DOWN_PC_w())	//FORWARD ATTACKS
							{
							if(player[g_Player]->astackcntdir[0] > 6) player[g_Player]->astackcntdir[0] = 0;

							if(player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1) //AirBorn
								{
								if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
								if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
								if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
								if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
								if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
								if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;
								if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 24;

								player[g_Player]->blendamount[4]=0;
								player[g_Player]->AJPushOffON = 0;
								player[g_Player]->Running = 0;
								//player[g_Player]->AirBorn = 0;
								player[g_Player]->TimeHoleFLAG = 0;
								}
							else
								{
								if(player[g_Player]->Running == 1) //Running
									{
									player[g_Player]->Running = 0;
									player[g_Player]->RunningCount = 0;
									if(player[g_Player]->astackcntdir[0] == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									if(player[g_Player]->astackcntdir[0] == 1) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									if(player[g_Player]->astackcntdir[0] == 2) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									if(player[g_Player]->astackcntdir[0] == 3) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									if(player[g_Player]->astackcntdir[0] == 4) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									if(player[g_Player]->astackcntdir[0] == 5) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									if(player[g_Player]->astackcntdir[0] == 6) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 77;
									}
								}
							}
						}


					//### Knee to mid air
					if(player[g_Player]->KL_FTRSpecLevel == 2 && player[g_Player]->AirBorn == 0)	//Hyper Knee Flex
						{
						if(player[g_Player]->HB_Energy >= 40 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 40 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 25;
							player[g_Player]->KL_FTRSpecLevel = 0;

							//Q_Jink Cancelator
							player[g_Player]->Q_Jink.ON = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[40] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}

					//##### JSRUSH
					if(player[g_Player]->KL_LTFSpecLevel == 2)
						{
						if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 73;
							player[g_Player]->KL_LTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[73] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->blendamount[0] = 0;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//##### JSRUSHUP
					if(player[g_Player]->KL_FTLSpecLevel > 1)
						{
						if(player[g_Player]->HB_Energy >= 40 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 40 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							if(player[g_Player]->Aposestate != 76)
								{
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								player[g_Player]->astackcntdir[0] = 0;
								player[g_Player]->attackstack[player[g_Player]->astackcnt] = 76;
								player[g_Player]->KL_FTLSpecLevel = 0;

								player[g_Player]->attposecnt = 0;
								player[g_Player]->Aposestate = 0;
								player[g_Player]->blendamount[0] = 0;
								player[g_Player]->blendamount[73] = 0;
								player[g_Player]->TrailsOn = 0;
								player[g_Player]->attackon = 0;
								player[g_Player]->ShadowsOn = 1;
								player[g_Player]->blendamount[0] = 0;
								player[g_Player]->AirJinkPrep = 3;
								}
							else player[g_Player]->AttackPos = 0;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//### VHKICK
					if(player[g_Player]->KL_FTRSpecLevel == 1)
						{
						if(player[g_Player]->HB_Energy >= 45 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 45 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 35;
							player[g_Player]->KL_FTRSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[55] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//### Sakurat
					if(player[g_Player]->KL_FTRSpecLevel == 2 && (player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1))
						{
						if(player[g_Player]->HB_Energy >= 150 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 150 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 56;
							player[g_Player]->KL_FTRSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[55] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;
							player[g_Player]->DownSpeed = 0;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
							
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//### RHKick
					if(player[g_Player]->KL_FTLSpecLevel == 1)
						{
						if(player[g_Player]->HB_Energy >= 30 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 30 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 31;
							player[g_Player]->KL_FTLSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[31] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
							
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//Leap Spin Kick
					if(player[g_Player]->KL_LTFSpecLevel == 1)
						{
						if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 22;
							player[g_Player]->KL_LTFSpecLevel = 0;

							//Q_Jink Cancelator
							player[g_Player]->Q_Jink.ON = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[30] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
							
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//### Static Kick
					if(player[g_Player]->KL_RTFSpecLevel > 1 && player[g_Player]->AirBorn == 0 && player[g_Player]->WallRun == 0)
						{
						if(player[g_Player]->HB_Energy >= 200 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 200 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 75;
							player[g_Player]->KL_RTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[122] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
							
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//### Spin Kick Full Rotation
					if(player[g_Player]->KL_RTFSpecLevel > 1 && (player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1))
						{
						if(player[g_Player]->HB_Energy >= 170 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 170 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 34;
							player[g_Player]->KL_RTFSpecLevel = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[34] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}


					//### Twist Kick
					if(player[g_Player]->KL_RTFSpecLevel == 1)
						{
						if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
							{
							player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
							player[g_Player]->HB_EnergyTimer = TIME;
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							player[g_Player]->astackcntdir[0] = 0;
							player[g_Player]->attackstack[player[g_Player]->astackcnt] = 61;
							player[g_Player]->KL_RTFSpecLevel = 0;

							//Q_Jink Cancelator
							player[g_Player]->Q_Jink.ON = 0;

							player[g_Player]->attposecnt = 0;
							player[g_Player]->Aposestate = 0;
							player[g_Player]->blendamount[0] = 0;
							player[g_Player]->blendamount[7] = 0;
							player[g_Player]->TrailsOn = 0;
							player[g_Player]->attackon = 0;
							player[g_Player]->ShadowsOn = 1;

							//'Jink'
							Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						else
							{
								//'Jink Ready'
							Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
							}
						}

					player[g_Player]->astackcnt++;
					}
				}
			}


			//****////ENERGY\\\\****
		if(_->mbutton[g_Player] == 1 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30 && player[g_Player]->Mposestate != 16))
			{
			if(player[g_Player]->astackcnt < 6)
				{
				noot=0;
				if(player[g_Player]->Aposestate == 45 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0)		//Att Flip Energy Renzou's
					{
					if(player[g_Player]->HB_Energy >= 80 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= 80 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->KL_LTFSpecLevel = 0;
						player[g_Player]->KL_RTFSpecLevel = 0;
						player[g_Player]->KL_FTLSpecLevel = 0;
						player[g_Player]->KL_FTRSpecLevel = 0;
						player[g_Player]->Aposestate = 93;
						player[g_Player]->EnergyDisplayLock = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

						//'Jink'
						Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_LTFSpecLevel == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0)		//Renzou
					{
					if((player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff) && (_->NomSEnergy < _->MaxNomSEnergy))
						{
						player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 19;
						player[g_Player]->KL_LTFSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[7] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->EnergyDisplayLock = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_LTFSpecLevel == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)		//Cleric Heal
					{
					if(player[g_Player]->HB_Energy >= (15 + (100 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= (15 + (100 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 200;
						player[g_Player]->KL_LTFSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[7] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->blendamount[0] = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_RTFSpecLevel == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)		//Cleric Plasma
					{
					if(player[g_Player]->HB_Energy >= (20 + (150 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= (20 + (150 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->KL_RTFSpecLevel = 0;

						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[7] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

						player[g_Player]->Aposestate = 204;
						player[g_Player]->attackon = 1;
						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attposecnt = 1.39;
						player[g_Player]->attackprog = 0;
						player[g_Player]->collide = 0;
						player[g_Player]->AttackSoundTRIG = 0;
						player[g_Player]->AttackSoundINITTRIG = 0;
						player[g_Player]->AttackPos = 0;
						player[g_Player]->attackhitRcount = 0;

						player[g_Player]->EnergyDisplayLock = 0;
						player[g_Player]->EnergyDisplayAlpha = 80;
						player[g_Player]->EnergyDisplayColor = 255;
						player[g_Player]->EnergyDisplayScale = 0.22;
						player[g_Player]->EnergyTargetLock = 0;
						player[g_Player]->EnergyLockID = 0;
						player[g_Player]->EnergyCloseDist = 0;
						player[g_Player]->EnergyCloseID = 0;
						player[g_Player]->EnergyTargetLaserAlpha = 0;
						player[g_Player]->EnergyInitialise = 0;
						//player[g_Player]->AirBorn = 0;

						//### CANCELLATION
						player[g_Player]->Cleric.HSparkInit = 0;
						player[g_Player]->JinkSpecialON = 0;
						player[g_Player]->DeflectLethal = 0;
						player[g_Player]->HitLethal = 0;
						player[g_Player]->JinkInit = 0;
						player[g_Player]->HoldBack = 0;
						player[g_Player]->Flip = 0;
						player[g_Player]->HB_DmgSTORE = 0;
						player[g_Player]->WindWake = 0;
						player[g_Player]->TrailINIT = 0;

						if(player[g_Player]->Mposestate != 13 && player[g_Player]->Aposestate != 24)
							{
							_->TimePlayerLock = 0;
							player[g_Player]->JSpiralCAM = 0;
							}
							
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_FTRSpecLevel == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)		//Cleric Offensive Plasma
					{
					if(player[g_Player]->HB_Energy >= (20 + (150 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[3].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= (20 + (150 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[3].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->KL_FTRSpecLevel = 0;

						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[7] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

						player[g_Player]->Aposestate = 207;
						player[g_Player]->attackon = 1;
						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attposecnt = 1.39;
						player[g_Player]->attackprog = 0;
						player[g_Player]->collide = 0;
						player[g_Player]->AttackSoundTRIG = 0;
						player[g_Player]->AttackSoundINITTRIG = 0;
						player[g_Player]->AttackPos = 0;
						player[g_Player]->attackhitRcount = 0;

						player[g_Player]->EnergyDisplayLock = 0;
						player[g_Player]->EnergyDisplayAlpha = 80;
						player[g_Player]->EnergyDisplayColor = 255;
						player[g_Player]->EnergyDisplayScale = 0.22;
						player[g_Player]->EnergyTargetLock = 0;
						player[g_Player]->EnergyLockID = 0;
						player[g_Player]->EnergyCloseDist = 0;
						player[g_Player]->EnergyCloseID = 0;
						player[g_Player]->EnergyTargetLaserAlpha = 0;
						player[g_Player]->EnergyInitialise = 0;
						//player[g_Player]->AirBorn = 0;

						//### CANCELLATION
						player[g_Player]->Cleric.HSparkInit = 0;
						player[g_Player]->JinkSpecialON = 0;
						player[g_Player]->DeflectLethal = 0;
						player[g_Player]->HitLethal = 0;
						player[g_Player]->JinkInit = 0;
						player[g_Player]->HoldBack = 0;
						player[g_Player]->Flip = 0;
						player[g_Player]->HB_DmgSTORE = 0;
						player[g_Player]->WindWake = 0;
						player[g_Player]->TrailINIT = 0;

						if(player[g_Player]->Mposestate != 13 && player[g_Player]->Aposestate != 24)
							{
							_->TimePlayerLock = 0;
							player[g_Player]->JSpiralCAM = 0;
							}
							
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_FTLSpecLevel == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)		//Cleric Energy Grab
					{
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					player[g_Player]->astackcntdir[0] = 0;
					player[g_Player]->attackstack[player[g_Player]->astackcnt] = 202;
					player[g_Player]->KL_FTLSpecLevel = 0;

					player[g_Player]->attposecnt = 0;
					player[g_Player]->Aposestate = 0;
					player[g_Player]->blendamount[0] = 0;
					player[g_Player]->blendamount[7] = 0;
					player[g_Player]->TrailsOn = 0;
					player[g_Player]->attackon = 0;
					player[g_Player]->blendamount[0] = 0;

					//Q_Jink Cancelator
					player[g_Player]->Q_Jink.ON = 0;

					//'Jink Ready'
					Qpo->Sound_Play(Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}


				if(((player[g_Player]->KL_LTFSpecLevel == 3) || (player[g_Player]->KL_FTLSpecLevel == 3) || (player[g_Player]->KL_RTFSpecLevel == 3) || (player[g_Player]->KL_FTRSpecLevel == 3)) && (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2))		//Cleric Buff Spell 01
					{
					if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 203;

						if(player[g_Player]->KL_LTFSpecLevel == 3) player[g_Player]->Cleric.SpellPNTR = 0;
						if(player[g_Player]->KL_FTLSpecLevel == 3) player[g_Player]->Cleric.SpellPNTR = 1;
						if(player[g_Player]->KL_RTFSpecLevel == 3) player[g_Player]->Cleric.SpellPNTR = 2;
						if(player[g_Player]->KL_FTRSpecLevel == 3) player[g_Player]->Cleric.SpellPNTR = 3;

						player[g_Player]->KL_LTFSpecLevel = 0;
						player[g_Player]->KL_FTLSpecLevel = 0;
						player[g_Player]->KL_RTFSpecLevel = 0;
						player[g_Player]->KL_FTRSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[7] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->blendamount[0] = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

						Qpo->Sound_Play(Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos//'Jink Ready'
						}
					else
						{
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos//'Jink Ready'
						}
					}

				if(player[g_Player]->KL_LTFSpecLevel == 2 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0)		//Hadou-Ken
					{
					if((player[g_Player]->HB_Energy >= 140 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff) && (_->NomLEnergy < _->MaxNomLEnergy))
						{
						player[g_Player]->HB_Energy -= 140 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 50;		//209 self implosion //50
						player[g_Player]->KL_LTFSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[84] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//'Jink'
						Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_FTRSpecLevel == 2 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)		//Cleric Shield
					{
					if(player[g_Player]->HB_Energy >= (30 + (250 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= (30 + (250 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Cost / 5000)))) / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						if(player[g_Player]->Cleric.ShieldOn == 0) player[g_Player]->attackstack[player[g_Player]->astackcnt] = 201;
						else player[g_Player]->attackstack[player[g_Player]->astackcnt] = 205;
						player[g_Player]->KL_FTRSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[85] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//'Jink'
						Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_FTLSpecLevel == 2 && (player[g_Player]->AirBorn == 1 || player[g_Player]->WallRun == 1) && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0)		//Power-Bomb
					{
					if((player[g_Player]->HB_Energy >= 110 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff) && (_->NomLEnergy < _->MaxNomLEnergy))
						{
						player[g_Player]->HB_Energy -= 110 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 78;
						player[g_Player]->KL_FTLSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[127] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//'Jink'
						Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}


				if(player[g_Player]->KL_FTLSpecLevel == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0)		//Brolly Tribute
					{
					if(player[g_Player]->HB_Energy >= 110 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
						{
						player[g_Player]->HB_Energy -= 110 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
						player[g_Player]->HB_EnergyTimer = TIME;
						if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 60;
						player[g_Player]->KL_LTFSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[91] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

						//'Jink'
						Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					else
						{
							//'Jink Ready'
						Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
						}
					}

				player[g_Player]->astackcnt++;
				}
			}


		if(((player[g_Player]->KL_RTFSpecLevel == 3 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0 && player[g_Player]->WeaponStatus == 0) || (player[g_Player]->KL_RTFSpecLevel == 5 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 1 && player[g_Player]->WeaponStatus > 0)))	//Fighter Power Up Activation
			{
			if(player[g_Player]->Mposestate == 14)
				{
				if(player[g_Player]->HB_Energy >= 100 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->KL_RTFSpecLevel = 0;

					player[g_Player]->HB_Energy -= 100 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->Mposestate = 16;

					//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}
			else
				{
				if(player[g_Player]->Mposestate == 16)	//### Power up cancellation
					{
					player[g_Player]->KL_RTFSpecLevel = 0;
					player[g_Player]->Mposestate = 14;

						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
					if(player[g_Player]->astackcnt < 6)
						{
						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attackstack[player[g_Player]->astackcnt] = 206;
						player[g_Player]->KL_RTFSpecLevel = 0;

						player[g_Player]->attposecnt = 0;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->blendamount[19] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;
						player[g_Player]->ShadowsOn = 1;
						player[g_Player]->blendamount[0] = 0;

						//Q_Jink Cancelator
						player[g_Player]->Q_Jink.ON = 0;

						//if(player[g_Player]->Ninja.SpeedACT == 1) player[g_Player]->Ninja.SpeedACT = 0;
						//else if(player[g_Player]->Ninja.SpeedACT == 0) player[g_Player]->Ninja.SpeedACT = 1;

						//if(player[g_Player]->EnergyArchitect.AffectMatrixON == 1) player[g_Player]->EnergyArchitect.AffectMatrixON = 0;
						//else if(player[g_Player]->EnergyArchitect.AffectMatrixON == 0) player[g_Player]->EnergyArchitect.AffectMatrixON = 1;

						player[g_Player]->astackcnt++;
						}
					}
				}
			}


		if((player[g_Player]->KL_RTFSpecLevel == 4 || player[g_Player]->KL_FTRSpecLevel == 4) && player[g_Player]->astackcnt < 6)	//ZONE AFFECT SWITCH
			{
			player[g_Player]->astackcnt = 0;
			player[g_Player]->astackrun = 0;
			player[g_Player]->astackcntdir[0] = 0;
			player[g_Player]->attackstack[player[g_Player]->astackcnt] = 206;
			player[g_Player]->KL_RTFSpecLevel = 0;

			player[g_Player]->attposecnt = 0;
			player[g_Player]->Aposestate = 0;
			player[g_Player]->blendamount[0] = 0;
			player[g_Player]->blendamount[19] = 0;
			player[g_Player]->TrailsOn = 0;
			player[g_Player]->attackon = 0;
			player[g_Player]->ShadowsOn = 1;
			player[g_Player]->blendamount[0] = 0;

			//Q_Jink Cancelator
			player[g_Player]->Q_Jink.ON = 0;

			//if(player[g_Player]->Ninja.SpeedACT == 1) player[g_Player]->Ninja.SpeedACT = 0;
			//else if(player[g_Player]->Ninja.SpeedACT == 0) player[g_Player]->Ninja.SpeedACT = 1;

			if(player[g_Player]->EnergyArchitect.AffectMatrixON == 1) player[g_Player]->EnergyArchitect.AffectMatrixON = 0;
			else if(player[g_Player]->EnergyArchitect.AffectMatrixON == 0) player[g_Player]->EnergyArchitect.AffectMatrixON = 1;

			player[g_Player]->astackcnt++;
			}

		//##### --- SOLDIER CLASS JINK MOVES --- #####
		//if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 1) && ((KEY_PRESS_DOWN(QIN_1) || _->mbutton[g_Player] == 1) && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30)))
		if((player[g_Player]->WeaponStatus > 0) && ((KEY_DOWN_LOCK(QIN_1) || _->mbutton[g_Player] == 1) && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30)))
			{
			//### Damage Upgrades
			if(player[g_Player]->KL_RTFSpecLevel == 1)		//### Single Jink Power Upgrade
				{
				if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->KL_RTFSpecLevel = 0;

					//#### Upgrade Shot Damage
					player[g_Player]->Soldier.JDamageLVL = 1;

					player[g_Player]->Soldier.JDamageLVLCounter = 0;

						//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}


			if(player[g_Player]->KL_RTFSpecLevel == 2)		//### Double Jink Power Upgrade
				{
				if(player[g_Player]->HB_Energy >= 130 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->HB_Energy -= 130 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->KL_RTFSpecLevel = 0;

					//#### Upgrade Shot Damage
					player[g_Player]->Soldier.JDamageLVL = 2;

					player[g_Player]->Soldier.JDamageLVLCounter = 0;

						//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}


			if(player[g_Player]->KL_RTFSpecLevel == 3)		//### Triple Jink Power Upgrade
				{
				if(player[g_Player]->HB_Energy >= 350 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->HB_Energy -= 350 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->KL_RTFSpecLevel = 0;

					//#### Upgrade Shot Damage
					player[g_Player]->Soldier.JDamageLVL = 3;

					player[g_Player]->Soldier.JDamageLVLCounter = 0;

						//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}


			//### Accuracy Upgrades
			if(player[g_Player]->KL_LTFSpecLevel == 1)		//### Single Jink Power Upgrade
				{
				if(player[g_Player]->HB_Energy >= 20 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->HB_Energy -= 20 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->KL_LTFSpecLevel = 0;

					//#### Upgrade Shot Damage
					player[g_Player]->Soldier.JAccuracyLVL = 1;

					player[g_Player]->Soldier.JAccuracyLVLCounter = 0;

						//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}


			if(player[g_Player]->KL_LTFSpecLevel == 2)		//### Double Jink Power Upgrade
				{
				if(player[g_Player]->HB_Energy >= 75 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->HB_Energy -= 75 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->KL_LTFSpecLevel = 0;

					//#### Upgrade Shot Damage
					player[g_Player]->Soldier.JAccuracyLVL = 2;

					player[g_Player]->Soldier.JAccuracyLVLCounter = 0;

						//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}


			if(player[g_Player]->KL_LTFSpecLevel == 3)		//### Triple Jink Accuracy Upgrade
				{
				if(player[g_Player]->HB_Energy >= 250 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
					{
					player[g_Player]->HB_Energy -= 250 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
					player[g_Player]->HB_EnergyTimer = TIME;
					if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

					player[g_Player]->KL_LTFSpecLevel = 0;

					//#### Upgrade Shot Damage
					player[g_Player]->Soldier.JAccuracyLVL = 3;

					player[g_Player]->Soldier.JAccuracyLVLCounter = 0;

						//'Jink'
					Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				else
					{
						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}

			}//End SOLDIER JINKS


		//###- Speed Adjustments -###

		//### Player
		if(player[g_Player]->Aposestate == 26 || player[g_Player]->Aposestate == 28 || player[g_Player]->Aposestate == 30 || player[g_Player]->Mposestate == 26 || player[g_Player]->Mposestate == 8 || (player[g_Player]->Mposestate == 11 || player[g_Player]->Mposestate == 12 || player[g_Player]->Mposestate == 13 || player[g_Player]->Mposestate == 14 || player[g_Player]->Mposestate == 15 || player[g_Player]->Mposestate == 16) || player[g_Player]->Mposestate == 8 || player[g_Player]->Mposestate == 26 || KEY_DOWN_PK(QIN_z)) player[g_Player]->PlayerSpeed = 0;
		else
			{											//5
			if(player[g_Player]->attackon == 1) player[g_Player]->PlayerSpeed = 14 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELMoveSpeed;

			if(player[g_Player]->Block == 1)
				{
				if(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 1) player[g_Player]->PlayerSpeed = 0;
				if(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3) player[g_Player]->PlayerSpeed = 0.15f * PLAYER_SPEED;	//2.5
				}
			else player[g_Player]->PlayerSpeed = PLAYER_SPEED;
			}


		//###- PLAYER RAMP COLLDET

		//## Get Avatar In Vec
		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &playerAV[g_Player]->In);
		Qpo->Vec3d_Normalize(&playerAV[g_Player]->In);

		//STORE AIRBORN STATUS FOR LANDINGS
		player[g_Player]->AirBornSTR = player[g_Player]->AirBorn;

		playerAV[g_Player]->OldPos = playerAV[g_Player]->Xform.Translation;
		//@@@playerAV[g_Player]->OldPos.y -= (VoxelGrid::BLOCK_RENDER_SIZE * 2.0f);
		playerAV[g_Player]->NewPos = playerAV[g_Player]->OldPos; //Player Position Origin

		Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, player[g_Player]->MoveReactSpeed * HITREACT_SCALE_IMP * _->TimeScale, &player[g_Player]->MoveReactVec, &playerAV[g_Player]->NewPos);

		// Conditionally Apply Gravity
		if(g_EngineMode == QEngineMode::QEngine_World)
			{
			playerAV[g_Player]->NewPos.y += player[g_Player]->DownSpeed * _->TimeScale;
			}
		
		//COLLISION DETECTION >>>

#if 0
		player[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->OldPos = playerAV[g_Player]->Xform.Translation;

		player[g_Player]->OldPos.y += 50;
		player[g_Player]->NewPos.y += 50;

		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&playerAV[g_Player]->Up);
		Qpo->Vec3d_AddScaled(&player[g_Player]->OldPos, 20, &playerAV[g_Player]->Up, &player[g_Player]->NewPos);

		// This does collision detection
		if(player[g_Player]->WallRun == 0)
			{
			if(Qpo->Collision_RayTest(
							 NULL,//&playerAV[g_Player]->Mins,
							 NULL,//&playerAV[g_Player]->Maxs,
							 &player[g_Player]->OldPos,
							 &player[g_Player]->NewPos,
							 // GE_CONTENTS_CANNOT_OCCUPY                //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
							 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
							 0xffffffff, NULL, NULL,
							 &player[g_Player]->WallRunCollision))
					{
					if((player[g_Player]->attackon == 0 || (player[g_Player]->attackon == 1 && ((player[g_Player]->Aposestate == 24) || (player[g_Player]->Aposestate == 73) || (player[g_Player]->Aposestate == 76) || (player[g_Player]->Aposestate == 53)))) && player[g_Player]->WallRunDelay == 0 && player[g_Player]->Aposestate != 51 && player[g_Player]->Aposestate != 52 && player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 30 && !_->mbutton[g_Player] && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16)
						{
						if((player[g_Player]->WallRunCollision.Plane.Normal.x == 1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0) || (player[g_Player]->WallRunCollision.Plane.Normal.x == -1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0)
							|| (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == 1) || (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == -1))
							{
							_->TimeHole = 1;
							_->TimeRotate = 1;
							player[g_Player]->NewPos = player[g_Player]->WallRunCollision.Impact;
							player[g_Player]->WallRun = 1;
							player[g_Player]->Mposestate = 9;
							_->TimePlayerLock = 0;
							if(player[g_Player]->Aposestate != 20)	player[g_Player]->attackon = 0;
							player[g_Player]->WallRunDelay = 15;
							player[g_Player]->StepTimer = 0;
							}
						}
					}
			}

		player[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->OldPos = playerAV[g_Player]->Xform.Translation;

		player[g_Player]->OldPos.y += 50;
		player[g_Player]->NewPos.y += 50;

		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&playerAV[g_Player]->Up);
		Qpo->Vec3d_AddScaled(&player[g_Player]->OldPos, 20, &playerAV[g_Player]->Up, &player[g_Player]->NewPos);

		// This does collision detection
		if(player[g_Player]->WallRun == 0)
			{
			if(Qpo->Collision_RayTest(
							 NULL,//&playerAV[g_Player]->Mins,
							 NULL,//&playerAV[g_Player]->Maxs,
							 &player[g_Player]->OldPos,
							 &player[g_Player]->NewPos,
							 // GE_CONTENTS_CANNOT_OCCUPY                //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
							 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
							 0xffffffff, NULL, NULL,
							 &player[g_Player]->WallRunCollision))
					{
					if((player[g_Player]->attackon == 0 || (player[g_Player]->attackon == 1 && ((player[g_Player]->Aposestate == 24) || (player[g_Player]->Aposestate == 73) || (player[g_Player]->Aposestate == 76) || (player[g_Player]->Aposestate == 53)))) && player[g_Player]->WallRunDelay == 0 && player[g_Player]->Aposestate != 51 && player[g_Player]->Aposestate != 52 && player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 30 && !_->mbutton[g_Player] && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16)
						{
						if((player[g_Player]->WallRunCollision.Plane.Normal.x == 1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0) || (player[g_Player]->WallRunCollision.Plane.Normal.x == -1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0)
							|| (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == 1) || (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == -1))
							{
							_->TimeHole = 1;
							_->TimeRotate = 1;
							player[g_Player]->NewPos = player[g_Player]->WallRunCollision.Impact;
							player[g_Player]->WallRun = 1;
							player[g_Player]->Mposestate = 9;
							_->TimePlayerLock = 0;
							player[g_Player]->WallRunDelay = 15;
							if(player[g_Player]->Aposestate != 20)	player[g_Player]->attackon = 0;
							player[g_Player]->StepTimer = 0;
							}
						}
					}
			}


		//### Forward Looking Coll Det for wall running etc

		player[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->OldPos = playerAV[g_Player]->Xform.Translation;

		player[g_Player]->OldPos.y += 50;
		player[g_Player]->NewPos.y += 50;

		Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&playerAV[g_Player]->Left);
		Qpo->Vec3d_Inverse(&playerAV[g_Player]->Left);
		Qpo->Vec3d_AddScaled(&player[g_Player]->OldPos, -20, &playerAV[g_Player]->Left, &player[g_Player]->NewPos);

		// This does collision detection
		if(player[g_Player]->WallRun == 0)
			{
			if(Qpo->Collision_RayTest(
							 NULL,//&playerAV[g_Player]->Mins,
							 NULL,//&playerAV[g_Player]->Maxs,
							 &player[g_Player]->OldPos,
							 &player[g_Player]->NewPos,
							 // GE_CONTENTS_CANNOT_OCCUPY                //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
							 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
							 0xffffffff, NULL, NULL,
							 &player[g_Player]->WallRunCollision))
					{
					if((player[g_Player]->attackon == 0 || (player[g_Player]->attackon == 1 && ((player[g_Player]->Aposestate == 24) || (player[g_Player]->Aposestate == 73) || (player[g_Player]->Aposestate == 76) || (player[g_Player]->Aposestate == 53)))) && player[g_Player]->WallRunDelay == 0 && player[g_Player]->Aposestate != 51 && player[g_Player]->Aposestate != 52 && player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 30 && !_->mbutton[g_Player] && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16)
						{
						if((player[g_Player]->WallRunCollision.Plane.Normal.x == 1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0) || (player[g_Player]->WallRunCollision.Plane.Normal.x == -1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0)
							|| (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == 1) || (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == -1))
							{
							_->TimeHole = 1;
							_->TimeRotate = 1;
							player[g_Player]->NewPos = player[g_Player]->WallRunCollision.Impact;
							player[g_Player]->WallRun = 1;
							player[g_Player]->Mposestate = 9;
							_->TimePlayerLock = 0;
							if(player[g_Player]->Aposestate != 20)	player[g_Player]->attackon = 0;
							player[g_Player]->WallRunDelay = 15;
							player[g_Player]->StepTimer = 0;
							}
						}
					}
			}

		player[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->OldPos = playerAV[g_Player]->Xform.Translation;

		player[g_Player]->OldPos.y += 50;
		player[g_Player]->NewPos.y += 50;

		Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&playerAV[g_Player]->Left);
		Qpo->Vec3d_Inverse(&playerAV[g_Player]->Left);
		Qpo->Vec3d_AddScaled(&player[g_Player]->OldPos, 20, &playerAV[g_Player]->Left, &player[g_Player]->NewPos);

		// This does collision detection
		if(player[g_Player]->WallRun == 0)
			{
			if(Qpo->Collision_RayTest(
							 NULL,//&playerAV[g_Player]->Mins,
							 NULL,//&playerAV[g_Player]->Maxs,
							 &player[g_Player]->OldPos,
							 &player[g_Player]->NewPos,
							 // GE_CONTENTS_CANNOT_OCCUPY                //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
							 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
							 0xffffffff, NULL, NULL,
							 &player[g_Player]->WallRunCollision))
					{
					if((player[g_Player]->attackon == 0 || (player[g_Player]->attackon == 1 && ((player[g_Player]->Aposestate == 24) || (player[g_Player]->Aposestate == 73) || (player[g_Player]->Aposestate == 76) || (player[g_Player]->Aposestate == 53)))) && player[g_Player]->WallRunDelay == 0 && player[g_Player]->Aposestate != 51 && player[g_Player]->Aposestate != 52 && player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 30 && !_->mbutton[g_Player] && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16)
						{
						if((player[g_Player]->WallRunCollision.Plane.Normal.x == 1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0) || (player[g_Player]->WallRunCollision.Plane.Normal.x == -1 && player[g_Player]->WallRunCollision.Plane.Normal.z == 0)
							|| (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == 1) || (player[g_Player]->WallRunCollision.Plane.Normal.x == 0 && player[g_Player]->WallRunCollision.Plane.Normal.z == -1))
							{
							_->TimeHole = 1;
							_->TimeRotate = 1;
							player[g_Player]->NewPos = player[g_Player]->WallRunCollision.Impact;
							player[g_Player]->WallRun = 1;
							player[g_Player]->Mposestate = 9;
							_->TimePlayerLock = 0;
							player[g_Player]->WallRunDelay = 15;
							if(player[g_Player]->Aposestate != 20)	player[g_Player]->attackon = 0;
							player[g_Player]->StepTimer = 0;
							}
						}
					}
			}

#endif


		//#### Cancel AirJink Status for Wall Run
		if(player[g_Player]->Mposestate == 9 && player[g_Player]->AirJinkRotFG == 1)
			{
			_->TimeScale = 1;
			player[g_Player]->AirJinkRotFG = 0;
			player[g_Player]->AirJinkInit = 0;
			player[g_Player]->ROTATEMatrix = player[g_Player]->STOREMatrix;
			Qpo->Transform_RotateY(&player[g_Player]->ROTATEMatrix, player[g_Player]->Angles.y);
			Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->ROTATEMatrix.Translation);
			playerAV[g_Player]->Xform = player[g_Player]->ROTATEMatrix;
			}


		if(player[g_Player]->Running == 1) player[g_Player]->WallRunDelay = 0;

		if(player[g_Player]->WallRunDelay > 0 && player[g_Player]->WallRun == 0)
			{
			player[g_Player]->WallRunDelay--;
			if(player[g_Player]->WallRunDelay < 0) player[g_Player]->WallRunDelay = 0;
			}

		//if(player[g_Player]->WallRunplayer[g_Player]->WallRunDelay = 0;


		player[g_Player]->ForwardSpeed = 0;		// reset our forward speed

		if(KEY_DOWN_PK_a() && (player[g_Player]->attackon == 0) /*&& !KEY_DOWN_PK(QIN_MBUTTON)*/ && 0)
			{
			if (KEY_DOWN_PK(QIN_LSHIFT) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4) && player[g_Player]->WeaponStatus != 0) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldOn == 1))) player[g_Player]->ForwardSpeed = (player[g_Player]->PlayerSpeed/4)*_->TimeScale;		//Slow Sidestep Left
			else player[g_Player]->ForwardSpeed = (player[g_Player]->PlayerSpeed/1.5)*_->TimeScale;							//Sidestep Left

			if(((player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 9 && player[g_Player]->Mposestate != 5 && !KEY_DOWN_PK_w() && !KEY_DOWN_PK(QIN_SHIFT)) || (player[g_Player]->Mposestate != 5 && KEY_DOWN_PK(QIN_LSHIFT))) && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 8)	//Dependent Movement mode switch
				{
				player[g_Player]->runposecnt = 0.08;
				player[g_Player]->Mposestate = 5;
				player[g_Player]->blendamount[0] = 0; //Optimise me pls
				player[g_Player]->blendamount[1] = 0; //Optimise me pls
				player[g_Player]->blendamount[2] = 0; //Optimise me pls
				player[g_Player]->blendamount[3] = 0; //Optimise me pls
				player[g_Player]->idleposecnt = 0;
				player[g_Player]->StepTimer = 0;
				}


			Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&playerAV[g_Player]->Left);

			if(player[g_Player]->Ninja.SpeedACT == 1)
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, ((player[g_Player]->ForwardSpeed * 4.0f) + 30.0f) * _->TimeScale, &playerAV[g_Player]->Left, &playerAV[g_Player]->NewPos);
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->OldPos, player[g_Player]->ForwardSpeed * _->TimeScale, &playerAV[g_Player]->Left, &playerAV[g_Player]->OldPos);
				}
			else
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, (player[g_Player]->ForwardSpeed + 30.0f) * _->TimeScale, &playerAV[g_Player]->Left, &playerAV[g_Player]->NewPos);
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->OldPos, (player[g_Player]->ForwardSpeed / 4) * _->TimeScale, &playerAV[g_Player]->Left, &playerAV[g_Player]->OldPos);
				}

			playerAV[g_Player]->OldPos.y += 50;
			playerAV[g_Player]->NewPos.y += 50;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL,//&playerAV[g_Player]->Mins, 
						 NULL,//&playerAV[g_Player]->Maxs, 
						 &playerAV[g_Player]->OldPos, 
						 &playerAV[g_Player]->NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
						 0xffffffff, NULL, NULL, 
						 &playerAV[g_Player]->Collision))
				{
				// Set the new pos to the point of collision
#if 0			// 1
				playerAV[g_Player]->NewPos.acSet(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
#endif
				// 2
				playerAV[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;

				player[g_Player]->collide = 1;
				}

			playerAV[g_Player]->OldPos.y -= 50;
			playerAV[g_Player]->NewPos.y -= 50;
			}


		if(KEY_DOWN_PK_d() && (player[g_Player]->attackon == 0) /*&& !KEY_DOWN_PK(QIN_MBUTTON)*/ && 0)		//Sidestep Right
			{
			if (KEY_DOWN_PK(QIN_LSHIFT) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4) && player[g_Player]->WeaponStatus != 0) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldOn == 1))) player[g_Player]->ForwardSpeed = (player[g_Player]->PlayerSpeed/4)*_->TimeScale;		//Slow Sidestep Right
			else player[g_Player]->ForwardSpeed = (player[g_Player]->PlayerSpeed/1.5)*_->TimeScale;						//Sidestep Right

			if(((player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 9 && player[g_Player]->Mposestate != 6 && !KEY_DOWN_PK_w() && !KEY_DOWN_PK(QIN_SHIFT)) || (player[g_Player]->Mposestate != 6 && KEY_DOWN_PK(QIN_LSHIFT))) && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 8)	//Dependent Movement mode switch
				{
				player[g_Player]->runposecnt = 0.4;
				player[g_Player]->Mposestate = 6;
				player[g_Player]->blendamount[0] = 0; //Optimise me pls
				player[g_Player]->blendamount[1] = 0; //Optimise me pls
				player[g_Player]->blendamount[2] = 0; //Optimise me pls
				player[g_Player]->blendamount[3] = 0; //Optimise me pls
				player[g_Player]->idleposecnt = 0;
				player[g_Player]->StepTimer = 0;
				}

			Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&playerAV[g_Player]->Left);

			if(player[g_Player]->Ninja.SpeedACT == 1)
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, ((player[g_Player]->ForwardSpeed * -4.0f) - 30.0f) * _->TimeScale, &playerAV[g_Player]->Left, &playerAV[g_Player]->NewPos);
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->OldPos, -(player[g_Player]->ForwardSpeed * _->TimeScale), &playerAV[g_Player]->Left, &playerAV[g_Player]->OldPos);
				}
			else
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, -((player[g_Player]->ForwardSpeed - 30.0f) * _->TimeScale), &playerAV[g_Player]->Left, &playerAV[g_Player]->NewPos);
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->OldPos, -((player[g_Player]->ForwardSpeed / 4.0f) * _->TimeScale), &playerAV[g_Player]->Left, &playerAV[g_Player]->OldPos);
				}

			playerAV[g_Player]->OldPos.y += 50;
			playerAV[g_Player]->NewPos.y += 50;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL,//&playerAV[g_Player]->Mins, 
						 NULL,//&playerAV[g_Player]->Maxs, 
						 &playerAV[g_Player]->OldPos, 
						 &playerAV[g_Player]->NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
						 0xffffffff, NULL, NULL, 
						 &playerAV[g_Player]->Collision))
				{
				// Set the new pos to the point of collision
#if 0			// 1
				playerAV[g_Player]->NewPos.acSet(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
#endif
				// 2
				playerAV[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;

				player[g_Player]->collide = 1;
				}
			else
				{
				playerAV[g_Player]->NewPos.y -= 50;
				}

			playerAV[g_Player]->OldPos.y -= 50;
			}

		if(KEY_DOWN_PK_w() /*&& !KEY_DOWN_PK(QIN_MBUTTON)*/)
			{
			//player[g_Player]->WindWake = 1;
			if (KEY_DOWN_PK(QIN_LSHIFT) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4) && player[g_Player]->WeaponStatus != 0) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldOn == 1)))
				{
				player[g_Player]->ForwardSpeed = (player[g_Player]->PlayerSpeed / 4.0f) * _->TimeScale;  //Walk Forwards

				if(player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 9 && player[g_Player]->Mposestate != 1 && !KEY_DOWN_PK_a() && !KEY_DOWN_PK_d() && player[g_Player]->Mposestate != 8 && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 8)	//Movement mode switch
					{
					player[g_Player]->Mposestate = 1;
					player[g_Player]->blendamount[0] = 0; //Optimise me pls
					player[g_Player]->blendamount[1] = 0; //Optimise me pls
					player[g_Player]->blendamount[2] = 0; //Optimise me pls
					player[g_Player]->blendamount[3] = 0; //Optimise me pls
					player[g_Player]->runposecnt = 0;
					player[g_Player]->idleposecnt = 0;
					player[g_Player]->StepTimer = 0;
					}
				}
			else
				{
				player[g_Player]->ForwardSpeed = player[g_Player]->PlayerSpeed; // *_->TimeScale;  //Run Forwards
				
				if(player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 9 && player[g_Player]->Mposestate != 3 && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 8 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 8)	//Movement mode switch
					{
					player[g_Player]->Mposestate = 3;
					player[g_Player]->blendamount[0] = 0; //Optimise me pls
					player[g_Player]->blendamount[1] = 0; //Optimise me pls
					player[g_Player]->blendamount[2] = 0; //Optimise me pls
					player[g_Player]->blendamount[3] = 0; //Optimise me pls
					player[g_Player]->runposecnt = 0;
					player[g_Player]->idleposecnt = 0;
					player[g_Player]->StepTimer = 0;
					}
				}

			//Forward Player Angle
			if(player[g_Player]->Ninja.SpeedACT == 1)
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, player[g_Player]->ForwardSpeed * _->TimeScale, &playerAV[g_Player]->VecTo, &playerAV[g_Player]->NewPos);
				}
			else
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, player[g_Player]->ForwardSpeed * _->TimeScale, &playerAV[g_Player]->VecTo, &playerAV[g_Player]->NewPos);
				}

#if 0
			playerAV[g_Player]->OldPos.y += 50;
			playerAV[g_Player]->NewPos.y += 50;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL,//&playerAV[g_Player]->Mins, 
						 NULL,//&playerAV[g_Player]->Maxs, 
						 &playerAV[g_Player]->OldPos, 
						 &playerAV[g_Player]->NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
						 0xffffffff, NULL, NULL, 
						 &playerAV[g_Player]->Collision))
				{
				// Set the new pos to the point of collision
#if 0			// 1
				playerAV[g_Player]->NewPos.acSet(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
#endif
				// 2
				playerAV[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;

				player[g_Player]->collide = 1;
				}
			else
				{
				playerAV[g_Player]->NewPos.y -= 50;
				}

			playerAV[g_Player]->OldPos.y -= 50;
#endif
			}
		else player[g_Player]->WindWake = 0;



		if(KEY_DOWN_PK(QIN_SHIFT) /*&& !KEY_DOWN_PK(QIN_MBUTTON)*/)
			{
			if(KEY_DOWN_PK(QIN_LSHIFT) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4) && player[g_Player]->WeaponStatus != 0) || ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldOn == 1)))
				{
				player[g_Player]->ForwardSpeed = -(player[g_Player]->PlayerSpeed/4)*_->TimeScale;  //Walk Backwards

				if(player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 9 && player[g_Player]->Mposestate != 2 && !KEY_DOWN_PK_a() && !KEY_DOWN_PK_d() && player[g_Player]->Mposestate != 8 && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 8)	//Movement mode switch
					{
					player[g_Player]->Mposestate = 2;
					player[g_Player]->blendamount[0] = 0; //Optimise me pls
					player[g_Player]->blendamount[1] = 0; //Optimise me pls
					player[g_Player]->blendamount[2] = 0; //Optimise me pls
					player[g_Player]->blendamount[3] = 0; //Optimise me pls
					player[g_Player]->runposecnt = 0;
					player[g_Player]->idleposecnt = 0;
					player[g_Player]->StepTimer = 0;
					}
				}
			else
				{
				player[g_Player]->ForwardSpeed = -player[g_Player]->PlayerSpeed*_->TimeScale;  //Run Backwards

				if(player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 9 && player[g_Player]->Mposestate != 4 && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 8 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 8)	//Movement mode switch
					{
					player[g_Player]->Mposestate = 4;
					player[g_Player]->blendamount[0] = 0; //Optimise me pls
					player[g_Player]->blendamount[1] = 0; //Optimise me pls
					player[g_Player]->blendamount[2] = 0; //Optimise me pls
					player[g_Player]->blendamount[3] = 0; //Optimise me pls
					player[g_Player]->runposecnt = 0;
					player[g_Player]->idleposecnt = 0;
					player[g_Player]->StepTimer = 0;
					}
				}


			if(player[g_Player]->Ninja.SpeedACT == 1)
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, player[g_Player]->ForwardSpeed * _->TimeScale, &playerAV[g_Player]->VecTo, &playerAV[g_Player]->NewPos);
				}
			else
				{
				Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, player[g_Player]->ForwardSpeed * _->TimeScale, &playerAV[g_Player]->VecTo, &playerAV[g_Player]->NewPos);
				}

#if 0
			playerAV[g_Player]->OldPos.y += 50.0f;
			playerAV[g_Player]->NewPos.y += 50.0f;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL,//&playerAV[g_Player]->Mins, 
						 NULL,//&playerAV[g_Player]->Maxs, 
						 &playerAV[g_Player]->OldPos, 
						 &playerAV[g_Player]->NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
						 0xffffffff, NULL, NULL, 
						 &playerAV[g_Player]->Collision))
				{
				// Set the new pos to the point of collision
#if 0			// 1
				playerAV[g_Player]->NewPos.acSet(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
#endif
				// 2
				playerAV[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;

				player[g_Player]->collide = 1;
				}
			else
				{
				playerAV[g_Player]->NewPos.y -= 50;
				}

			playerAV[g_Player]->OldPos.y -= 50;
#endif

			// Power move cancel
			if(KEY_DOWN_PK_a() && KEY_DOWN_PK_d())
				{
				if(player[g_Player]->Aposestate == 73 || player[g_Player]->Aposestate == 76 || player[g_Player]->Aposestate == 64 || player[g_Player]->Aposestate == 75 || player[g_Player]->Aposestate == 25 || player[g_Player]->Aposestate == 53 || player[g_Player]->Aposestate == 56 || player[g_Player]->Aposestate == 34 || player[g_Player]->Aposestate == 84 || player[g_Player]->Aposestate == 80)
					{
					player[g_Player]->Aposestate = 0;
					player[g_Player]->attackon = 0;
					player[g_Player]->attposecnt = 0;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;

					if(player[g_Player]->ShadowsOn == 1)
						{
						player[g_Player]->ShadowsOn = 0;
						Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
						Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
						Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
						}

					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}
			}

		//Attack Lock on Acceleration
		if(_->mwheelroll[g_Player] == 1 && player[g_Player]->attackon == 1)
			{
			float i_Distance = 0;
			float i_StrDist = 1000;
			QpoVec3d i_Target, i_TargetVec;

			AItempcnt = 0;
			while(AItempcnt < _->NomAI)
				{
				if(Q_Forge->Forge[AItempcnt].LIVE == 1)
					{
					if(Q_Forge->Forge[AItempcnt].Team != player[g_Player]->Team)
						{
						if(Q_Forge->Forge[AItempcnt].HB_Dead == 0)
							{
							i_Distance = Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[AItempcnt].AV.Xform.Translation);

							if(i_Distance < i_StrDist)
								{
								i_StrDist = i_Distance;
								i_Target = Q_Forge->Forge[AItempcnt].AV.Xform.Translation;
								}
							}
						}
					}
				
				AItempcnt++;
				}

			Qpo->Vec3d_Subtract(&i_Target, &playerAV[g_Player]->Xform.Translation, &i_TargetVec);
			Qpo->Vec3d_Normalize(&i_TargetVec);

			Qpo->Vec3d_AddScaled(&playerAV[g_Player]->Xform.Translation, i_StrDist / 7, &i_TargetVec, &playerAV[g_Player]->Xform.Translation);
			}

		//Wall run Cancel
		if((KEY_DOWN_PK(QIN_SPACE) || KEY_DOWN_PK(QIN_q) || KEY_DOWN_PK(QIN_e) || (KEY_DOWN_PK(QIN_z) && KEY_DOWN_PK_a()) || (KEY_DOWN_PK(QIN_z) && KEY_DOWN_PK_d()) || (KEY_DOWN_PK(QIN_z) && KEY_DOWN_PK_w()) || (KEY_DOWN_PK(QIN_z) && KEY_DOWN_PK(QIN_SHIFT))) && player[g_Player]->Mposestate == 9 && KEY_DOWN_PK(QIN_MBUTTON)) player[g_Player]->WallRunSWITCH = 1;

		//###--- JUMP ---###
		if(KEY_DOWN_PK(QIN_SPACE) /*&& player[g_Player]->Mposestate != 9*/ && player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 8 && player[g_Player]->Mposestate != 16)
			{
			player[g_Player]->SPACEKEYcnt++;

			if(KEY_DOWN_PK(QIN_SHIFT) && !(KEY_DOWN_PK_a() || KEY_DOWN_PK_d()))	//### Spiral Over Enemy Jump
				{
				if(player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16)
					{
					player[g_Player]->JumpDir = 0;

					player[g_Player]->JumpVec = playerAV[g_Player]->VecTo;

					player[g_Player]->jumpposecnt = 0;
					player[g_Player]->Mposestate = 13;
					player[g_Player]->JumpFG = 0;

					if(player[g_Player]->AirBorn || player[g_Player]->Aposestate == 73)
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
				}
			else
				{
				if(player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16)	//### Forward First Jump
					{
					player[g_Player]->JumpDir = 0;

					player[g_Player]->JumpVec = playerAV[g_Player]->VecTo;

					if(KEY_DOWN_PK_w()) player[g_Player]->JumpDir = 1;	//Forward Jump
					if(KEY_DOWN_PK(QIN_SHIFT) && (KEY_DOWN_PK_a() || KEY_DOWN_PK_d())) player[g_Player]->JumpDir = 2;	//Backwards Jump
					
					player[g_Player]->jumpposecnt = 0;
					player[g_Player]->Mposestate = 11;
					player[g_Player]->JumpFG = 0;

					if(player[g_Player]->AirBorn || player[g_Player]->Aposestate == 73)
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
					{		//### Forward Second Jump
					if(player[g_Player]->Mposestate == 11 && ((player[g_Player]->SPACEKEYcnt > 8) || (player[g_Player]->SPACEKEYcnt == 1)))
						{
						player[g_Player]->JumpDir = 0;

						player[g_Player]->JumpVec = playerAV[g_Player]->VecTo;

						if(KEY_DOWN_PK_w()) player[g_Player]->JumpDir = 1;	//Forward Jump
						if(KEY_DOWN_PK(QIN_SHIFT) && (KEY_DOWN_PK_a() || KEY_DOWN_PK_d())) player[g_Player]->JumpDir = 2;	//Backwards Jump

						player[g_Player]->jumpposecnt = 0;
						player[g_Player]->Mposestate = 12;
						player[g_Player]->JumpFG = 0;

						if(player[g_Player]->AirBorn || player[g_Player]->Aposestate == 73)
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
							{
							player[g_Player]->JumpFactor = 1;
							player[g_Player]->JumpState = 1;
							}
						}
					}
				}
			}
		else player[g_Player]->SPACEKEYcnt = 0;


		if (KEY_DOWN_PK(QIN_q) && KEY_DOWN_PK(QIN_z) /*&& player[g_Player]->Mposestate != 9*/ && player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 16 && player[g_Player]->BlockHit == 0 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30))		//ROLL LOW LEFT
			{
			player[g_Player]->Mposestate = 28;
			player[g_Player]->runposecnt = 0;
			player[g_Player]->SideSpeed = 0;
			player[g_Player]->JumpOff = 0;
			}

		if (KEY_DOWN_PK(QIN_e) && KEY_DOWN_PK(QIN_z) /*&& player[g_Player]->Mposestate != 9*/ && player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 16 && player[g_Player]->BlockHit == 0 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30))		//ROLL LOW RIGHT
			{
			player[g_Player]->Mposestate = 29;
			player[g_Player]->runposecnt = 0;
			player[g_Player]->SideSpeed = 0;
			player[g_Player]->JumpOff = 0;
			}


		if (KEY_DOWN_PK(QIN_q) /*&& player[g_Player]->Mposestate != 9*/ && player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 16 && player[g_Player]->BlockHit == 0 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30))		//CARTWHEEL LEFT
			{
			player[g_Player]->Mposestate = 23;
			player[g_Player]->runposecnt = 0;
			player[g_Player]->SideSpeed = 0;
			player[g_Player]->JumpOff = 0;
			}

		if (KEY_DOWN_PK(QIN_e) /*&& player[g_Player]->Mposestate != 9*/ && player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 16 && player[g_Player]->BlockHit == 0 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30))		//CARTWHEEL RIGHT
			{
			player[g_Player]->Mposestate = 24;
			player[g_Player]->runposecnt = 1.67;
			player[g_Player]->SideSpeed = 0;
			player[g_Player]->JumpOff = 0;
			}


		if (KEY_DOWN_PK(QIN_z) && player[g_Player]->Mposestate != 25 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 16 && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30))		//DODGE LEFT / ROLL FORWARD
			{
			if (KEY_DOWN_PK_a() && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->BlockHit == 0)		//ROLL LOW LEFT
				{
				player[g_Player]->Mposestate = 28;
				player[g_Player]->runposecnt = 0;
				player[g_Player]->SideSpeed = 0;
				player[g_Player]->JumpOff = 0;
				}

			if (KEY_DOWN_PK_d() && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->BlockHit == 0)		//ROLL LOW RIGHT
				{
				player[g_Player]->Mposestate = 29;
				player[g_Player]->runposecnt = 0;
				player[g_Player]->SideSpeed = 0;
				player[g_Player]->JumpOff = 0;
				}

			if (KEY_DOWN_PK_w() && player[g_Player]->Mposestate != 8 && player[g_Player]->BlockHit == 0)
				{
				player[g_Player]->Mposestate = 26;
				player[g_Player]->runposecnt = 0;
				player[g_Player]->Aposestate = 0;
				player[g_Player]->attackon = 0;
				player[g_Player]->attposecnt = 0;
				}

			if(KEY_DOWN_PK(QIN_SHIFT) && player[g_Player]->BlockHit == 0)	//Pressing Back So Backflip
				{
				if(player[g_Player]->Mposestate != 8 && player[g_Player]->Aposestate != 62 )
					{
					player[g_Player]->Mposestate = 8;
					player[g_Player]->runposecnt = 0;

					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					player[g_Player]->astackcntdir[0] = 0;
					player[g_Player]->attposecnt = 0;
					player[g_Player]->Aposestate = 0;
					player[g_Player]->blendamount[0] = 0;
					player[g_Player]->TrailsOn = 0;
					player[g_Player]->attackon = 0;
					}
				else
					{
					if(player[g_Player]->runposecnt >= 1.02)
						{
						player[g_Player]->runposecnt = 0.14;
						player[g_Player]->blendamount[57] = 0.5;
						}

					if(KEY_DOWN_LOCK(QIN_2))
						{
						player[g_Player]->astackcnt = 0;
						player[g_Player]->astackrun = 0;
						player[g_Player]->astackcntdir[0] = 0;
						player[g_Player]->attposecnt = player[g_Player]->runposecnt;
						player[g_Player]->Aposestate = 0;
						player[g_Player]->blendamount[0] = 0;
						player[g_Player]->TrailsOn = 0;
						player[g_Player]->attackon = 0;

						//player[g_Player]->Mposestate = 0;
						player[g_Player]->runposecnt = 0;
						player[g_Player]->Aposestate = 62;
						player[g_Player]->attackon = 1;
						player[g_Player]->attposecnt = 0;
						player[g_Player]->attackhits = 0;
						player[g_Player]->attackprog = 0;
						player[g_Player]->collide = 0;
						player[g_Player]->AttackSoundTRIG = 0;
						}
					}
				}
			}


		if(KEY_DOWN_PK(QIN_TAB) && player[g_Player]->WeaponStatus == 0 && !(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0 && player[g_Player]->Mposestate == 16))	//****////WEAPON\\\\****
			{
			player[g_Player]->Aposestate = 20;
			player[g_Player]->attposecnt = 0;
			player[g_Player]->WeaponStatus = 1;
			player[g_Player]->attackon = 0;

			player[g_Player]->WepAlpha = 0;
			Qpo->Mesh_SetAlpha(&player[g_Player]->Weapon, 0);
			}


		if(KEY_DOWN_PK(QIN_h))	//player mounts a vehicle
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrVEHICLE != 250 && player[g_Player]->Mech.ACTIVE == 0)
				{
				if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Vehicle.Model.Xform.Translation) < 100)
					{
					//##### Mount Vehicle
					player[g_Player]->PlayerMode = 1;
					player[g_Player]->idleposecnt = 0;
					player[g_Player]->Mposestate = 0;

					//##### INITIALISE A VAPOR TRAIL FOR ROCKET
					Q_VaporTrail->VaporTrail[0].StartWidth = 6;
					Q_VaporTrail->VaporTrail[0].WidthExpand = 2.5;
					Q_VaporTrail->VaporTrail[0].LifeOfPoint = 30;
					Q_VaporTrail->VaporTrail[0].NomPoints = 0;
					Q_VaporTrail->VaporTrail[0].Live = 1;
					Q_VaporTrail->VaporTrail[1].StartWidth = 6;
					Q_VaporTrail->VaporTrail[1].WidthExpand = 2.5;
					Q_VaporTrail->VaporTrail[1].LifeOfPoint = 30;
					Q_VaporTrail->VaporTrail[1].NomPoints = 0;
					Q_VaporTrail->VaporTrail[1].Live = 1;
					_->NomVaporTrails = 2;

					player[g_Player]->Vehicle.STRVehicleUP.x = 0;
					player[g_Player]->Vehicle.STRVehicleUP.y = 0;
					player[g_Player]->Vehicle.STRVehicleUP.z = 1;

						//'Jink Ready'
					Qpo->Sound_Play(Medias->S_VehMBStart, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
					}
				}


			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH != 250)
				{
				if(MechKEYPRESS == 0)
					{
					if(player[g_Player]->Mech.ACTIVE == 1)	//DISMOUNT MECH
						{
						player[g_Player]->Mech.ACTIVE = 2;

						//##### Dis-Mount Mech
						Q.DeactivateItems();

						player[g_Player]->Mech.ACTIVE = 0;

						player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE = 1.2;

						player[g_Player]->Mech.Model.Avatar = playerAV[g_Player]->Avatar;
						player[g_Player]->Mech.Model.AvatarDef = playerAV[g_Player]->AvatarDef;
						player[g_Player]->Mech.Model.Xform = playerAV[g_Player]->Xform;
						
						playerAV[g_Player]->Avatar = player[g_Player]->Mech.ModelSTR.Avatar;
						playerAV[g_Player]->AvatarDef = player[g_Player]->Mech.ModelSTR.AvatarDef;
						playerAV[g_Player]->Xform = player[g_Player]->Mech.Model.Xform;

						helly = 0;
						while(helly <= 2)
							{
							helly++;
							player[g_Player]->Mech.Shadows[helly].Avatar = player[g_Player]->Shadows[helly].Avatar;
							player[g_Player]->Mech.Shadows[helly].AvatarDef = player[g_Player]->Shadows[helly].AvatarDef;
							player[g_Player]->Mech.Shadows[helly].Xform = player[g_Player]->Shadows[helly].Xform;

							player[g_Player]->Shadows[helly].Avatar = player[g_Player]->Mech.ShadowsSTR[helly].Avatar;
							player[g_Player]->Shadows[helly].AvatarDef = player[g_Player]->Mech.ShadowsSTR[helly].AvatarDef;
							player[g_Player]->Shadows[helly].Xform = player[g_Player]->Mech.ShadowsSTR[helly].Xform;
							}

						//### Activate All player items
						Q.ActivateItems();
						}
					else
						{
						TempVec1 = player[g_Player]->Mech.Model.Xform.Translation;
						TempVec1.y += 100 + (0.16*((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH].QA_ITEMINC_Height)/100)-0.5)*2));

						if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &TempVec1) < 150)
							{
							//##### Mount Mech
							Q.DeactivateItems();

							player[g_Player]->Mech.ACTIVE = 1;

							player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE = 0.43;
							
							player[g_Player]->Mech.ModelSTR.Avatar = playerAV[g_Player]->Avatar;
							player[g_Player]->Mech.ModelSTR.AvatarDef = playerAV[g_Player]->AvatarDef;
							player[g_Player]->Mech.ModelSTR.Xform = playerAV[g_Player]->Xform;

							playerAV[g_Player]->Avatar = player[g_Player]->Mech.Model.Avatar;
							playerAV[g_Player]->AvatarDef = player[g_Player]->Mech.Model.AvatarDef;
							playerAV[g_Player]->Xform = player[g_Player]->Mech.Model.Xform;

							helly = 0;
							while(helly <= 2)
								{
								helly++;
								player[g_Player]->Mech.ShadowsSTR[helly].Avatar = player[g_Player]->Shadows[helly].Avatar;
								player[g_Player]->Mech.ShadowsSTR[helly].AvatarDef = player[g_Player]->Shadows[helly].AvatarDef;
								player[g_Player]->Mech.ShadowsSTR[helly].Xform = player[g_Player]->Shadows[helly].Xform;

								player[g_Player]->Shadows[helly].Avatar = player[g_Player]->Mech.Shadows[helly].Avatar;
								player[g_Player]->Shadows[helly].AvatarDef = player[g_Player]->Mech.Shadows[helly].AvatarDef;
								player[g_Player]->Shadows[helly].Xform = player[g_Player]->Mech.Shadows[helly].Xform;
								}

							//### Activate All player items
							Q.ActivateItems();
							}
						}
					}

				MechKEYPRESS = 1;
				}
			}
		else MechKEYPRESS = 0;


		//### Taunt
		if(KEY_DOWN_PK(QIN_RETURN) && player[g_Player]->Mposestate != 51)	//Taunt
			{
			player[g_Player]->Mposestate = 51;
			player[g_Player]->runposecnt = 0;

			if(player[g_Player]->QformONtaunt <= 0) player[g_Player]->QformONtaunt = 1;
			else if(player[g_Player]->QformONtaunt >= 1) player[g_Player]->QformONtaunt = 0;
			}


		//Idle Posestate		THIS IS NOT GOOD REWORK \/\/\/\/\/\/\/\/
		if(player[g_Player]->Mposestate != 51 && player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 27 && player[g_Player]->Mposestate != 9 && player[g_Player]->ForwardSpeed == 0 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 25 && !(KEY_DOWN_PK(QIN_z)) && player[g_Player]->Mposestate != 0 && (player[g_Player]->Mposestate != 10 && player[g_Player]->Mposestate != 11 && player[g_Player]->Mposestate != 12 && player[g_Player]->Mposestate != 13 && player[g_Player]->Mposestate != 14 && player[g_Player]->Mposestate != 15 && player[g_Player]->Mposestate != 16) && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24 && player[g_Player]->Mposestate != 8)
			{
			player[g_Player]->Mposestate = 0;
			player[g_Player]->blendamount[0] = 0; //Optimise me please
			player[g_Player]->blendamount[1] = 0; //Optimise me pls
			player[g_Player]->blendamount[2] = 0; //Optimise me pls
			player[g_Player]->blendamount[3] = 0; //Optimise me pls
			player[g_Player]->runposecnt = 0;
			player[g_Player]->idleposecnt = 0;
			}


		//###-  Blocking  -###
		if(KEY_DOWN_PK(QIN_SHIFT) && !KEY_DOWN_PK(QIN_SPACE) && player[g_Player]->WeaponStatus == 0 && player[g_Player]->attackon == 0 && player[g_Player]->Mposestate != 8 && player[g_Player]->Mposestate != 16)
			{
			if(KEY_DOWN_PK(QIN_z))
				{
				if(player[g_Player]->BlockHeight != 1) player[g_Player]->attposecnt = 0;
				player[g_Player]->BlockHeight = 1;
				}
			else
				{
				if(player[g_Player]->BlockHeight != 3) player[g_Player]->attposecnt = 0;
				player[g_Player]->BlockHeight = 3;
				}

			player[g_Player]->Blocking = 1;
			player[g_Player]->Block = 1;
			}
		else
			{
			if(player[g_Player]->BlockHit == 0 && (player[g_Player]->CrouchInit == 0 || (player[g_Player]->CrouchInit == 1 && !((KEY_DOWN_PK(QIN_z) && player[g_Player]->attackon == 0) || player[g_Player]->attackstackSPECIAL[player[g_Player]->astackrun - 1] == 1))))
				{
				player[g_Player]->Blocking = 0;
				player[g_Player]->Block = 0;
				}
			}

		//##### RESET CROUCH

		//Crouch Hard Coded
		if(player[g_Player]->Mposestate != 28 && player[g_Player]->Mposestate != 29 && player[g_Player]->Mposestate != 26 && player[g_Player]->Mposestate != 8 && player[g_Player]->Mposestate != 16)
			{
			if((KEY_DOWN_PK(QIN_z) && player[g_Player]->attackon == 0) || player[g_Player]->attackstackSPECIAL[player[g_Player]->astackrun - 1] == 1)
				{
				if(player[g_Player]->CrouchInit == 0)
					{
					player[g_Player]->CrouchInit = 1;
					player[g_Player]->crohposecnt = 0;
					}

				player[g_Player]->Crouch = 1;
				Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 60, player[g_Player]->crohposecnt, &playerAV[g_Player]->Xform, player[g_Player]->blendamount[60]);
				if(player[g_Player]->crohposecnt + (0.08*_->TimeScale) < 0.335)	player[g_Player]->crohposecnt += 0.08*_->TimeScale;
				else player[g_Player]->crohposecnt = 0.335;

				if(player[g_Player]->blendamount[60]+(0.3*_->TimeScale)<=1) player[g_Player]->blendamount[60] += 0.3*_->TimeScale;
				}
			else
				{
				player[g_Player]->Crouch = 0;

				if(player[g_Player]->CrouchInit == 1 && player[g_Player]->attackon == 0)
					{
					Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 60, player[g_Player]->crohposecnt, &playerAV[g_Player]->Xform, player[g_Player]->blendamount[60]);
					if(player[g_Player]->crohposecnt + (0.08*_->TimeScale) <= 0.67) player[g_Player]->crohposecnt += 0.08*_->TimeScale;
					else player[g_Player]->CrouchInit = 0;
					}
				}
			}
		else
			{
			player[g_Player]->Crouch = 0;

			if(player[g_Player]->CrouchInit == 1 && player[g_Player]->attackon == 0)
				{
				Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 60, player[g_Player]->crohposecnt, &playerAV[g_Player]->Xform, player[g_Player]->blendamount[60]);
				if(player[g_Player]->crohposecnt + (0.08*_->TimeScale) <= 0.67) player[g_Player]->crohposecnt += 0.08*_->TimeScale;
				else player[g_Player]->CrouchInit = 0;
				}
			}


		//##### Q_Netplayer->Netplayer Movement Scale #####

		//*----Build Control----*

		/*if (KEY_DOWN_PK(QIN_b))
			{
			//####player[g_Player]->mode = 1;		//Buildmode
			}*/

		}//END Player Mode Temporarily

	}

};