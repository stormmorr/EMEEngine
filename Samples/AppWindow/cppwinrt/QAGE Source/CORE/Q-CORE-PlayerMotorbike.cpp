/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	*/#include "pch.h"/*- Minor Component -Player Mounted On Motorbike-

*/

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
#include "Q-ENE-EnergyTypes.h"
#include "Q-WE-BulletSystem.h"
#include "Q-AI-NNbot.h"

using namespace GVARS;

namespace GVARS
{

//##### -+ Motor Bike Control Core +- #####

void Q_COREFunctions::PLCoreMB(void)
{	
///**********************************************************************************************************
// View Rotation *******************************************************************************************

	// Get the pos of the mouse

	// Get Cursor Position conflicts with headers in OS specialisation
	//GetCursorPos(&temppos);

	// move the mouse to the center of the screen
	//*mpos.x = CWidth/2;
	//*mpos.y = CHeight/2;

	// Set Cursor Position conflicts with headers in OS specialisation
	//SetCursorPos(mpos.x,mpos.y);

	// Calculate the turning and up/down speed
	TURN_SPEED   = abs(temppos.x-mpos.x) * 0.002;
	UPDOWN_SPEED = abs(temppos.y-mpos.y) * 0.002;


	//### Spin the Player ###//
	if (temppos.x < mpos.x) //mouse left
		{
		player[g_Player]->Angles.y = player[g_Player]->Angles.y+(float)TURN_SPEED;
		if(player[g_Player]->Angles.y>(2*PI)) player[g_Player]->Angles.y=player[g_Player]->Angles.y-(PI*2);
		}

	if (temppos.x > mpos.x) //mouse right
		{
		player[g_Player]->Angles.y = player[g_Player]->Angles.y-(float)TURN_SPEED;
		if(player[g_Player]->Angles.y<0) player[g_Player]->Angles.y=(PI*2)+player[g_Player]->Angles.y;
		}

	if (temppos.y > mpos.y) //mouse down
		{
		player[g_Player]->Angles.x = player[g_Player]->Angles.x-(float)UPDOWN_SPEED;
		}

	if (temppos.y < mpos.y) //mouse up
		{
		player[g_Player]->Angles.x = player[g_Player]->Angles.x+(float)UPDOWN_SPEED;
		}

	// Make sure we arent looking too far up or down
	if (player[g_Player]->Angles.x>1.4) player[g_Player]->Angles.x = 1.4;
	if (player[g_Player]->Angles.x<-1.4) player[g_Player]->Angles.x =-1.4;


	//####### VEHICLE INPUT ########


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
			player[g_Player]->KL_LTFSpecLevel = 0;

			player[g_Player]->attposecnt = 0;
			player[g_Player]->Aposestate = 0;
			player[g_Player]->blendamount[0] = 0;
			player[g_Player]->blendamount[73] = 0;
			player[g_Player]->TrailsOn = 0;
			player[g_Player]->attackon = 0;
			player[g_Player]->ShadowsOn = 1;
			player[g_Player]->blendamount[0] = 0;

			/*QpoSound3D_GetConfig(World,
						&player[g_Player]->ViewXForm,
						&player[g_Player]->ViewXForm.Translation,
						600.0f,
						2.0f,
						&Volume,
						&Pan,
						&Frequency);*/

			//'Jink'
			Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos

			if(player[g_Player]->Vehicle.JINKrush == 1)
				{
				player[g_Player]->Vehicle.JINKrush = 0;
				player[g_Player]->WindWake = 0;
				}
			else if(player[g_Player]->Vehicle.JINKrush == 0)
				{
				player[g_Player]->Vehicle.JINKrush = 1;
				player[g_Player]->WindWake = 1;
				}
			}
		else
			{
			
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
			}
		}


	//##### --- SOLDIER CLASS JINK MOVES --- #####
	if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 1) && ((_->lbutton[g_Player] == 1 || _->mbutton[g_Player] == 1) && (player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28 && player[g_Player]->Aposestate != 30)))
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

				
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			else
				{
				
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			}


		if(player[g_Player]->KL_RTFSpecLevel > 2)		//### Triple Jink Power Upgrade
			{
			if(player[g_Player]->HB_Energy >= 350 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
				{
				player[g_Player]->HB_Energy -= 350 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
				player[g_Player]->HB_EnergyTimer = TIME;
				if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

				player[g_Player]->KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				player[g_Player]->Soldier.JDamageLVL = 3;

				
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

				
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			else
				{
				
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos
				}
			}


		if(player[g_Player]->KL_LTFSpecLevel > 2)		//### Triple Jink Power Upgrade
			{
			if(player[g_Player]->HB_Energy >= 250 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
				{
				player[g_Player]->HB_Energy -= 250 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
				player[g_Player]->HB_EnergyTimer = TIME;
				if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;

				player[g_Player]->KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				player[g_Player]->Soldier.JAccuracyLVL = 3;

				
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


		//########==---  GENERIC INPUT  ---==#########

	//### Weapon ZOOM
	if(KEY_PRESS_DOWN(QIN_CAPSLOCK) && (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE > 0))
		{
		if(player[g_Player]->WeaponZoomFACT < 1) player[g_Player]->WeaponZoomFACT += 0.1;
		else
			{
			player[g_Player]->WeaponZoomFACT = 1;
			player[g_Player]->WeaponZOOM = 1;
			}
		}
	else
		{
		if(player[g_Player]->WeaponZoomFACT > 0) player[g_Player]->WeaponZoomFACT -= 0.1;
		else
			{
			player[g_Player]->WeaponZoomFACT = 0;
			player[g_Player]->WeaponZOOM = 0;
			}
		}


	//*----Reset Positions / Heart Beat ~~~ single player and server only----*

	if(KEY_PRESS_DOWN(QIN_k))
		{
		helly = 0;
		while(helly < _->NomAI)
			{
			if(Q_Forge->Forge[helly].LIVE == 1)
				{
				Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].ORIGSTARTPOINT, &Q_Forge->Forge[helly].AV.Xform.Translation);

				Q_Forge->Forge[helly].AirJinkRotFG = 0;
				Q_Forge->Forge[helly].ROTATEMatrix = Q_Forge->Forge[helly].STOREMatrix;
				Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].AV.Xform.Translation, &Q_Forge->Forge[helly].ROTATEMatrix.Translation);
				Q_Forge->Forge[helly].AV.Xform = Q_Forge->Forge[helly].ROTATEMatrix;

				Q_Forge->Forge[helly].HB_Health = Q_Forge->Forge[helly].HB_MaxHealth;
				Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;
				Q_Forge->Forge[helly].HB_Dead = 0;
				Q_Forge->Forge[helly].HB_RecoverMode = 0;

				aero=0;
				while(aero < _->NomAI)
					{
					Q_Forge->Forge[helly].AvatarDMGSTORE[aero] = 0;
					aero++;
					}
				}
			
			helly++;
			}

		aero=0;
		while(aero < _->NomAI)
			{
			player[g_Player]->AvatarDMGSTORE[aero] = 0;
			aero++;
			}

		player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
		player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
		player[g_Player]->HB_Dead = 0;
		}


	//*----Player Reload (r)----*
	if((KEY_PRESS_DOWN(QIN_r)) && (player[g_Player]->WeaponStatus > 0))
		{
		player[g_Player]->WeaponStatus = 8;
		player[g_Player]->attposecnt = 0;
		player[g_Player]->blendamount[58] = 0;
		Q_Forge->Forge[0].Q_Brain.MeMBank[Q_Forge->Forge[0].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[0].Q_Brain.MeMBank[Q_Forge->Forge[0].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV[g_Player]->Xform.Translation;
		Q_Forge->Forge[0].Q_Brain.MeMBank[Q_Forge->Forge[0].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[0].Q_Brain.MeMBank[Q_Forge->Forge[0].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
		Q_Forge->Forge[1].Q_Brain.MeMBank[Q_Forge->Forge[1].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[1].Q_Brain.MeMBank[Q_Forge->Forge[1].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV[g_Player]->Xform.Translation;
		Q_Forge->Forge[1].Q_Brain.MeMBank[Q_Forge->Forge[1].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[1].Q_Brain.MeMBank[Q_Forge->Forge[1].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
		Q_Forge->Forge[2].Q_Brain.MeMBank[Q_Forge->Forge[2].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[2].Q_Brain.MeMBank[Q_Forge->Forge[2].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV[g_Player]->Xform.Translation;
		Q_Forge->Forge[2].Q_Brain.MeMBank[Q_Forge->Forge[2].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[2].Q_Brain.MeMBank[Q_Forge->Forge[2].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
		}


	/*if((KEY_PRESS_DOWN(QIN_p)) && (_->MusicDEPRESS == 0) && (_->MusicSWITCH != 1))
		{
		/*QpoSound3D_GetConfig(World,
							&player[g_Player]->ViewXForm,
							&player[g_Player]->ViewXForm.Translation,
							600.0f,
							2.0f,
							&Volume,
							&Pan,
							&Frequency);*/

			//'MUSAC'
		/*Qpo->Sound_Play(Medias->LoopingDef3, _->Volume, _->Pan, _->S_TimeScale, true, &player[g_Player]->RFistPos.Translation);
		_->MusicDEPRESS = 1;
		_->MusicSWITCH = 1;
		}*/

	//EDIT unsure About Sound Types
	/*if((KEY_PRESS_DOWN(QIN_p)) && (_->MusicDEPRESS == 0) && (_->MusicSWITCH != 2))
		{
		Qpo->Sound_Stop(SoundSys, &Medias->LoopingDef3);
		_->MusicSWITCH = 2;
		}*/

	if(!(KEY_PRESS_DOWN(QIN_p)))
		{
		_->MusicDEPRESS = 0;
		}


	//*----Camera Control----*

	if (KEY_PRESS_DOWN(QIN_HOME))
		{
		player[g_Player]->camrotdist -= 5;
		}

	if (KEY_PRESS_DOWN(QIN_END))
		{
		player[g_Player]->camrotdist += 5;
		}


	//*----Scanner----*

	if (KEY_PRESS_DOWN(QIN_F17) && player[g_Player]->Scan == 1 && player[g_Player]->ScanInit == 0)
		{
		player[g_Player]->ScanUP = 1;
		}

	if (KEY_PRESS_DOWN(QIN_F17) && player[g_Player]->ScanUP == 0)
		{
		player[g_Player]->Scan = 1;
		player[g_Player]->ScanInit = 1;
		player[g_Player]->ScanBitAlpha = 20;
		player[g_Player]->ScanBitHeight = -600;
		player[g_Player]->ScanBoneAlpha = 0;
		player[g_Player]->ScanBoxAlpha = 0;
		player[g_Player]->ScanBoxScale = 0;

		//##### INITIALISE VAPOR TRAILS
		/*Q_VaporTrail->VaporTrail[0].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[0].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[0].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[0].NomPoints = 0;
		Q_VaporTrail->VaporTrail[0].Live = 1;
		Q_VaporTrail->VaporTrail[1].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[1].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[1].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[1].NomPoints = 0;
		Q_VaporTrail->VaporTrail[1].Live = 1;
		Q_VaporTrail->VaporTrail[2].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[2].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[2].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[2].NomPoints = 0;
		Q_VaporTrail->VaporTrail[2].Live = 1;
		Q_VaporTrail->VaporTrail[3].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[3].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[3].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[3].NomPoints = 0;
		Q_VaporTrail->VaporTrail[3].Live = 1;
		Q_VaporTrail->VaporTrail[4].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[4].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[4].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[4].NomPoints = 0;
		Q_VaporTrail->VaporTrail[4].Live = 1;
		Q_VaporTrail->VaporTrail[5].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[5].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[5].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[5].NomPoints = 0;
		Q_VaporTrail->VaporTrail[5].Live = 1;
		Q_VaporTrail->VaporTrail[6].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[6].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[6].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[6].NomPoints = 0;
		Q_VaporTrail->VaporTrail[6].Live = 1;
		Q_VaporTrail->VaporTrail[7].StartWidth = 0.5;
		Q_VaporTrail->VaporTrail[7].WidthExpand = 0.5;
		Q_VaporTrail->VaporTrail[7].LifeOfPoint = 30;
		Q_VaporTrail->VaporTrail[7].NomPoints = 0;
		Q_VaporTrail->VaporTrail[7].Live = 1;
		_->NomVaporTrails = 8;

		ScanVec[0] = playerAV[g_Player]->Xform.Translation;
		ScanVec[1] = playerAV[g_Player]->Xform.Translation;
		ScanVec[2] = playerAV[g_Player]->Xform.Translation;
		ScanVec[3] = playerAV[g_Player]->Xform.Translation;
		ScanVec[4] = playerAV[g_Player]->Xform.Translation;
		ScanVec[5] = playerAV[g_Player]->Xform.Translation;
		ScanVec[6] = playerAV[g_Player]->Xform.Translation;
		ScanVec[7] = playerAV[g_Player]->Xform.Translation;*/
		}

	//*----Screen Shots (scr)----*

	if (KEY_PRESS_DOWN(QIN_PRINT))
		{
		if(ScreenCounter == 0) ScreenShot = "ScreenShots\\ScreenShot0.bluemp";
		if(ScreenCounter == 1) ScreenShot = "ScreenShots\\ScreenShot1.bluemp";
		if(ScreenCounter == 2) ScreenShot = "ScreenShots\\ScreenShot2.bluemp";
		if(ScreenCounter == 3) ScreenShot = "ScreenShots\\ScreenShot3.bluemp";
		if(ScreenCounter == 4) ScreenShot = "ScreenShots\\ScreenShot4.bluemp";
		if(ScreenCounter == 5) ScreenShot = "ScreenShots\\ScreenShot5.bluemp";
		if(ScreenCounter == 6) ScreenShot = "ScreenShots\\ScreenShot6.bluemp";
		if(ScreenCounter == 7) ScreenShot = "ScreenShots\\ScreenShot7.bluemp";
		if(ScreenCounter == 8) ScreenShot = "ScreenShots\\ScreenShot8.bluemp";
		if(ScreenCounter == 9) ScreenShot = "ScreenShots\\ScreenShot9.bluemp";
		if(ScreenCounter == 10) ScreenShot = "ScreenShots\\ScreenShot10.bluemp";
		if(ScreenCounter == 11) ScreenShot = "ScreenShots\\ScreenShot11.bluemp";
		if(ScreenCounter == 12) ScreenShot = "ScreenShots\\ScreenShot12.bluemp";
		if(ScreenCounter == 13) ScreenShot = "ScreenShots\\ScreenShot13.bluemp";
		if(ScreenCounter == 14) ScreenShot = "ScreenShots\\ScreenShot14.bluemp";
		if(ScreenCounter == 15) ScreenShot = "ScreenShots\\ScreenShot15.bluemp";
		if(ScreenCounter == 16) ScreenShot = "ScreenShots\\ScreenShot16.bluemp";
		if(ScreenCounter == 17) ScreenShot = "ScreenShots\\ScreenShot17.bluemp";
		if(ScreenCounter == 18) ScreenShot = "ScreenShots\\ScreenShot18.bluemp";
		if(ScreenCounter == 19) ScreenShot = "ScreenShots\\ScreenShot19.bluemp";
		if(ScreenCounter == 20) ScreenShot = "ScreenShots\\ScreenShot20.bluemp";
		if(ScreenCounter == 21) ScreenShot = "ScreenShots\\ScreenShot21.bluemp";
		if(ScreenCounter == 22) ScreenShot = "ScreenShots\\ScreenShot22.bluemp";
		if(ScreenCounter == 23) ScreenShot = "ScreenShots\\ScreenShot23.bluemp";
		if(ScreenCounter == 24) ScreenShot = "ScreenShots\\ScreenShot24.bluemp";
		if(ScreenCounter == 25) ScreenShot = "ScreenShots\\ScreenShot25.bluemp";
		if(ScreenCounter == 26) ScreenShot = "ScreenShots\\ScreenShot26.bluemp";
		if(ScreenCounter == 27) ScreenShot = "ScreenShots\\ScreenShot27.bluemp";
		if(ScreenCounter == 28) ScreenShot = "ScreenShots\\ScreenShot28.bluemp";
		if(ScreenCounter == 29) ScreenShot = "ScreenShots\\ScreenShot29.bluemp";
		if(ScreenCounter == 30) ScreenShot = "ScreenShots\\ScreenShot30.bluemp";
		if(ScreenCounter == 31) ScreenShot = "ScreenShots\\ScreenShot31.bluemp";
		if(ScreenCounter == 32) ScreenShot = "ScreenShots\\ScreenShot32.bluemp";
		if(ScreenCounter == 33) ScreenShot = "ScreenShots\\ScreenShot33.bluemp";
		if(ScreenCounter == 34) ScreenShot = "ScreenShots\\ScreenShot34.bluemp";
		if(ScreenCounter == 35) ScreenShot = "ScreenShots\\ScreenShot35.bluemp";
		if(ScreenCounter == 36) ScreenShot = "ScreenShots\\ScreenShot36.bluemp";
		if(ScreenCounter == 37) ScreenShot = "ScreenShots\\ScreenShot37.bluemp";
		if(ScreenCounter == 38) ScreenShot = "ScreenShots\\ScreenShot38.bluemp";
		if(ScreenCounter == 39) ScreenShot = "ScreenShots\\ScreenShot39.bluemp";
		if(ScreenCounter == 40) ScreenShot = "ScreenShots\\ScreenShot40.bluemp";
		if(ScreenCounter == 41) ScreenShot = "ScreenShots\\ScreenShot41.bluemp";
		if(ScreenCounter == 42) ScreenShot = "ScreenShots\\ScreenShot42.bluemp";
		if(ScreenCounter == 43) ScreenShot = "ScreenShots\\ScreenShot43.bluemp";
		if(ScreenCounter == 44) ScreenShot = "ScreenShots\\ScreenShot44.bluemp";
		if(ScreenCounter == 45) ScreenShot = "ScreenShots\\ScreenShot45.bluemp";
		if(ScreenCounter == 46) ScreenShot = "ScreenShots\\ScreenShot46.bluemp";
		if(ScreenCounter == 47) ScreenShot = "ScreenShots\\ScreenShot47.bluemp";
		if(ScreenCounter == 48) ScreenShot = "ScreenShots\\ScreenShot48.bluemp";
		if(ScreenCounter == 49) ScreenShot = "ScreenShots\\ScreenShot49.bluemp";
		if(ScreenCounter == 50) ScreenShot = "ScreenShots\\ScreenShot50.bluemp";

		if(ScreenCounter <= 50) Qpo->Engine_ScreenShot(ScreenShot);

		ScreenCounter++;
		}


	//*----Player Invisibility (i)----*

	if(KEY_PRESS_DOWN(QIN_i))
		{
		if(KeyDepress2 == 0)
			{
			if(player[g_Player]->FirstPerson == 1)
				{
				player[g_Player]->FirstPerson = 0;
				player[g_Player]->Invisible = 0;
				Qpo->Avatar_SetAlpha(&playerAV[g_Player]->Avatar, 255);
				}
			else
				{
				player[g_Player]->FirstPerson = 1;
				player[g_Player]->Invisible = 1;
				Qpo->Avatar_SetAlpha(&playerAV[g_Player]->Avatar, 100);
				}
			}

		KeyDepress2 = 1;
		}
	else KeyDepress2 = 0;


	//*----Time Altering----*

	if (KEY_PRESS_DOWN(QIN_UP))
		{
		_->TimeScaleALTER += 0.01;
		}

	if (KEY_PRESS_DOWN(QIN_DOWN))
		{
		_->TimeScaleALTER -= 0.01;
		}

	if (_->TimeScaleALTER <= 0)
		{
		_->TimeScaleALTER = 0.005;
		}

	if (KEY_PRESS_DOWN(QIN_DELETE))
		{
		_->TimeScaleALTER = 1;
		}


	//*----Radar Scale----*

	if(KEY_PRESS_DOWN(QIN_F11) && _->RADPRESS1 == 0)
		{
		_->RADSCALE /= 2;
		_->RADPRESS1 = 1;
		}
	else _->RADPRESS1 = 0;

	if(KEY_PRESS_DOWN(QIN_F12) && _->RADPRESS2 == 0)
		{
		_->RADSCALE *= 2;
		_->RADPRESS2 = 1;
		}
	else _->RADPRESS2 = 0;


	//*----Gamma Correction----*

	if (KEY_PRESS_DOWN(QIN_PLUS))
		{
		// Reset the gamma.
		_->gama += 0.1;
		Qpo->Engine_SetGamma(_->gama);
		
		// write our new gamma settings to a file
		//*stream = fopen("Config\\gamma.ini","w");
		//*fprintf(stream,"%f",gama);
		//*fclose(stream);
		}

	if (KEY_PRESS_DOWN(QIN_MINUS))
		{
		// reset the gama
		_->gama -= 0.1;
		Qpo->Engine_SetGamma(_->gama);
		
		// write our new gamma settings to a file
		//*stream = fopen("Config\\gamma.ini","w");
		//*fprintf(stream,"%f",gama);
		//*fclose(stream);
		}

	if (KEY_PRESS_DOWN(QIN_ASTERISK))
		{
		_->gama = 1.0;
		Qpo->Engine_SetGamma(_->gama);

		// write our new gamma settings to a file
		//*stream = fopen("Config\\gamma.ini","w");
		//*fprintf(stream,"%f",gama);
		//*fclose(stream);
		}


	//###### TEMPORARY QUIT KEY (SCROLL LOCK ######
	if(KEY_PRESS_DOWN(QIN_INSERT))
		{
		//PostMessage(FoundhWnd, WM_QUIT, 0, 0);

		_->run = 0;
		}


	//### RESET ZONING
	player[g_Player]->Vehicle.ZONING = 0;

	SCRAM=0;
	while(SCRAM < Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks)
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Active == 1)
			{
			//###### CHECKS TO FIND AVATARS WITHIN BLOCK
			//#### CHECK PLAYER WITHIN
			Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE01", &player[g_Player]->EnergyArchitect.CurrentPOSMAT);

			if(player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.x < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.x
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.x > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.x
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.y < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.y
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.y > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.y
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.z < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.z
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.z > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.z)
				{
				player[g_Player]->Vehicle.ZONING = 1;
				player[g_Player]->Vehicle.WithinZONE = SCRAM;

				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity != 1)
					{
					player[g_Player]->Vehicle.GravityAlter += ((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity - player[g_Player]->Vehicle.GravityAlter) / 5);
					}
				}
			}

		SCRAM++;
		}


	//### CAMERA MATRIX ###//

	if(player[g_Player]->WeaponZoomFACT != 1)
		{
		if(player[g_Player]->WeaponZoomFACT > 0)
			{
			//#### Standard Camera Matrix

			Qpo->Transform_New(&player[g_Player]->CamMatrix);
			Qpo->Transform_New(&player[g_Player]->Camrot);

			Qpo->Transform_New_XRotation(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
			Qpo->Transform_Multiply(&player[g_Player]->CamMatrix, &player[g_Player]->Camrot, &player[g_Player]->CamMatrix);
			Qpo->Transform_RotateY(&player[g_Player]->CamMatrix, player[g_Player]->Angles.y);

			Qpo->Transform_GetLeft(&player[g_Player]->CamMatrix, &player[g_Player]->CamLeft);
			Qpo->Transform_GetUp(&player[g_Player]->CamMatrix, &player[g_Player]->CamUp);
			Qpo->Transform_GetIn(&player[g_Player]->CamMatrix, &player[g_Player]->CamIn);

			//##### Bone Matrix

			//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->AttPos);
			Qpo->Transform_GetLeft(&player[g_Player]->AttPos, &player[g_Player]->AimVec);
			Qpo->Vec3d_Inverse(&player[g_Player]->AimVec);

			Qpo->Transform_New(&player[g_Player]->BonMatrix);
			Qpo->Transform_Orthonormalize(&player[g_Player]->AttPos);

			Qpo->Transform_New(&player[g_Player]->Camrot);
			Qpo->Transform_New_YRotation(&player[g_Player]->Camrot, -(PI/2));
			Qpo->Transform_Multiply(&player[g_Player]->BonMatrix, &player[g_Player]->AttPos, &player[g_Player]->BonMatrix);
			Qpo->Transform_Multiply(&player[g_Player]->BonMatrix, &player[g_Player]->Camrot, &player[g_Player]->BonMatrix);

			Qpo->Transform_GetLeft(&player[g_Player]->BonMatrix, &player[g_Player]->BonLeft);
			Qpo->Transform_GetUp(&player[g_Player]->BonMatrix, &player[g_Player]->BonUp);
			Qpo->Transform_GetIn(&player[g_Player]->BonMatrix, &player[g_Player]->BonIn);

			Qpo->Vec3d_Subtract(&player[g_Player]->BonLeft, &player[g_Player]->CamLeft, &player[g_Player]->BonLeft);
			Qpo->Vec3d_Subtract(&player[g_Player]->BonUp, &player[g_Player]->CamUp, &player[g_Player]->BonUp);
			Qpo->Vec3d_Subtract(&player[g_Player]->BonIn, &player[g_Player]->CamIn, &player[g_Player]->BonIn);

			player[g_Player]->BonLeft.x /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonLeft.y /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonLeft.z /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonUp.x /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonUp.y /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonUp.z /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonIn.x /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonIn.y /= 3 / (3 * player[g_Player]->WeaponZoomFACT);
			player[g_Player]->BonIn.z /= 3 / (3 * player[g_Player]->WeaponZoomFACT);

			Qpo->Vec3d_Add(&player[g_Player]->CamLeft, &player[g_Player]->BonLeft, &player[g_Player]->NewLeft);
			Qpo->Vec3d_Add(&player[g_Player]->CamUp, &player[g_Player]->BonUp, &player[g_Player]->NewUp);
			Qpo->Vec3d_Add(&player[g_Player]->CamIn, &player[g_Player]->BonIn, &player[g_Player]->NewIn);

			Qpo->Transform_New_LeftUpIn(&player[g_Player]->CamMatrix, &player[g_Player]->NewLeft, &player[g_Player]->NewUp, &player[g_Player]->NewIn);
			}
		else
			{
			Qpo->Transform_New(&player[g_Player]->CamMatrix);
			Qpo->Transform_New(&player[g_Player]->Camrot);

			Qpo->Transform_New_XRotation(&player[g_Player]->Camrot, player[g_Player]->Angles.x);
			Qpo->Transform_Multiply(&player[g_Player]->CamMatrix, &player[g_Player]->Camrot, &player[g_Player]->CamMatrix);
			Qpo->Transform_RotateY(&player[g_Player]->CamMatrix, player[g_Player]->Angles.y);
			}

		if(_->NomBullet!=0 && player[g_Player]->testef == 1) player[g_Player]->CamMatrix.Translation = Q_Bullet->Bullet[_->NomBullet-1].WorldPos;
		else
			{
			if(player[g_Player]->FirstPerson == 0)
				{
				Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->In);
				Qpo->Vec3d_Inverse(&player[g_Player]->In);
				Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &player[g_Player]->Left);
				Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->Up);
				player[g_Player]->CamMatrix.Translation = playerAV[g_Player]->Xform.Translation;

				Qpo->Vec3d_Add(&player[g_Player]->CamMatrix.Translation, &player[g_Player]->Vehicle.RotatePNTVEC,  &player[g_Player]->CamMatrix.Translation);

				if(player[g_Player]->Mech.ACTIVE == 0)
					{ player[g_Player]->CamMatrix.Translation.y = player[g_Player]->CamMatrix.Translation.y + (20 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)))); }
				else
					{ player[g_Player]->CamMatrix.Translation.y = player[g_Player]->CamMatrix.Translation.y + ((13 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE * 0.8333333) + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)))) * 2.7907); }

				player[g_Player]->oldpos = player[g_Player]->CamMatrix.Translation;

				if(player[g_Player]->Mech.ACTIVE == 0)
					{ player[g_Player]->CamMatrix.Translation.y = player[g_Player]->CamMatrix.Translation.y + (45 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)))); }
				else
					{ player[g_Player]->CamMatrix.Translation.y = player[g_Player]->CamMatrix.Translation.y + ((38 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE * 0.8333333) + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)))) * 2.7907); }

				player[g_Player]->newpos = player[g_Player]->CamMatrix.Translation;
				if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->oldpos, &player[g_Player]->newpos,/* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &player[g_Player]->Collision))
					{ player[g_Player]->CamMatrix.Translation = player[g_Player]->oldpos; }
				}
			else
				{
				player[g_Player]->CamMatrix.Translation = playerAV[g_Player]->Xform.Translation;
				player[g_Player]->CamMatrix.Translation.y = player[g_Player]->CamMatrix.Translation.y + (30 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE * 0.8333333) + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2))));
				player[g_Player]->oldpos = player[g_Player]->CamMatrix.Translation;
				player[g_Player]->CamMatrix.Translation.y = player[g_Player]->CamMatrix.Translation.y + (44 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE * 0.8333333) + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2))));
				player[g_Player]->newpos = player[g_Player]->CamMatrix.Translation;
				if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->oldpos, &player[g_Player]->newpos,/* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &player[g_Player]->Collision))
					{ player[g_Player]->CamMatrix.Translation = player[g_Player]->oldpos; }
				}
			}

		//### Camera Xforming ###//
		player[g_Player]->oldpos = player[g_Player]->CamMatrix.Translation;
		player[g_Player]->newpos = player[g_Player]->CamMatrix.Translation;
		Qpo->Transform_GetIn(&player[g_Player]->CamMatrix,&player[g_Player]->In);
		/*if(player[g_Player]->FirstPerson == 0)*/ Qpo->Vec3d_AddScaled(&player[g_Player]->oldpos,-player[g_Player]->camrotdist,&player[g_Player]->In,&player[g_Player]->newpos);

		if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->oldpos, &player[g_Player]->newpos,/* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &player[g_Player]->Collision))
			{
			//player[g_Player]->newpos = player[g_Player]->Collision.Impact;
			//Qpo->Vec3d_AddScaled(&player[g_Player]->oldpos, -(player[g_Player]->camrotdist * (player[g_Player]->Collision.Ratio * 0.87)), &player[g_Player]->In, &player[g_Player]->newpos);
			QpoVec3d f_ImpactVector(player[g_Player]->Collision.Impact.m_X, player[g_Player]->Collision.Impact.m_Y, player[g_Player]->Collision.Impact.m_Z);
			Qpo->Vec3d_AddScaled(&f_ImpactVector, 40, &player[g_Player]->In, &player[g_Player]->newpos);
			player[g_Player]->newpos.y -= 20;
			}

		player[g_Player]->CamMatrix.Translation = player[g_Player]->newpos;

		if(player[g_Player]->WeaponZoomFACT != 0)
			{
			//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->AttPos);
			Qpo->Transform_GetUp(&player[g_Player]->AttPos, &player[g_Player]->Up);
			Qpo->Transform_GetLeft(&player[g_Player]->AttPos, &player[g_Player]->AimVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, 4.5, &player[g_Player]->Up, &player[g_Player]->AttPos.Translation);

			Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, 6, &player[g_Player]->Up, &player[g_Player]->AttPos.Translation);
			Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, -28, &player[g_Player]->AimVec, &player[g_Player]->AttPos.Translation);

			Qpo->Vec3d_Subtract(&player[g_Player]->AttPos.Translation, &player[g_Player]->CamMatrix.Translation, &TempVec1);
			Qpo->Vec3d_Scale(&TempVec1, player[g_Player]->WeaponZoomFACT, &TempVec1);
			Qpo->Vec3d_Add(&player[g_Player]->CamMatrix.Translation, &TempVec1, &player[g_Player]->CamMatrix.Translation);
			}

		player[g_Player]->Xform = player[g_Player]->CamMatrix;
		player[g_Player]->ViewXForm = player[g_Player]->Xform;
		}
	else
		{
		//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->AttPos);
		Qpo->Transform_GetLeft(&player[g_Player]->AttPos, &player[g_Player]->AimVec);
		Qpo->Transform_GetUp(&player[g_Player]->AttPos, &player[g_Player]->Up);
		Qpo->Transform_GetIn(&player[g_Player]->AttPos, &player[g_Player]->In);
		Qpo->Vec3d_Inverse(&player[g_Player]->AimVec);

		Qpo->Transform_New(&player[g_Player]->CamMatrix);
		Qpo->Transform_Orthonormalize(&player[g_Player]->AttPos);

		Qpo->Transform_New(&player[g_Player]->Camrot);
		Qpo->Transform_New_YRotation(&player[g_Player]->Camrot, -(PI/2));
		Qpo->Transform_Multiply(&player[g_Player]->CamMatrix, &player[g_Player]->AttPos, &player[g_Player]->CamMatrix);
		Qpo->Transform_Multiply(&player[g_Player]->CamMatrix, &player[g_Player]->Camrot, &player[g_Player]->CamMatrix);

		player[g_Player]->CamMatrix.Translation = player[g_Player]->AttPos.Translation;

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE > 1)
			{ Qpo->Vec3d_AddScaled(&player[g_Player]->CamMatrix.Translation, 47, &player[g_Player]->AimVec, &player[g_Player]->CamMatrix.Translation); }
		else
			{
			Qpo->Vec3d_AddScaled(&player[g_Player]->CamMatrix.Translation, -player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeLOC.x, &player[g_Player]->In, &player[g_Player]->CamMatrix.Translation);
			Qpo->Vec3d_AddScaled(&player[g_Player]->CamMatrix.Translation, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeLOC.y, &player[g_Player]->Up, &player[g_Player]->CamMatrix.Translation);
			Qpo->Vec3d_AddScaled(&player[g_Player]->CamMatrix.Translation, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeLOC.z, &player[g_Player]->AimVec, &player[g_Player]->CamMatrix.Translation);
			}

		player[g_Player]->Xform = player[g_Player]->CamMatrix;
		player[g_Player]->ViewXForm = player[g_Player]->Xform;
		}

	if(player[g_Player]->CameraShake != 0)
		{
		//### Standard Shake
		if(player[g_Player]->CameraShake == 1)
			{
			if(player[g_Player]->CameraShakeINIT == 0)
				{
				player[g_Player]->CameraShakeINIT = 1;
				
				player[g_Player]->CamShakeIncX = ((((float)rand() / 32767)*40) - 20);
				if(player[g_Player]->CamShakeIncX > 0 && player[g_Player]->CamShakeIncX < 15) player[g_Player]->CamShakeIncX = 15;
				if(player[g_Player]->CamShakeIncX < 0 && player[g_Player]->CamShakeIncX > -15) player[g_Player]->CamShakeIncX = -15;
				player[g_Player]->CamShakeIncY = 0.6;
				player[g_Player]->CamShakeIncZ = ((((float)rand() / 32767)*40) - 20);
				if(player[g_Player]->CamShakeIncZ > 0 && player[g_Player]->CamShakeIncZ < 15) player[g_Player]->CamShakeIncZ = 15;
				if(player[g_Player]->CamShakeIncZ < 0 && player[g_Player]->CamShakeIncZ > -15) player[g_Player]->CamShakeIncZ = -15;
				}
			else
				{
				player[g_Player]->CamShakeIncX *= -0.4;
				player[g_Player]->CamShakeIncY *= -0.8;
				player[g_Player]->CamShakeIncZ *= -0.4;
				}

			player[g_Player]->CamShakeIncX += (((float)rand() / 32767)*5) - 2.5;
			player[g_Player]->CamShakeIncY += (((float)rand() / 32767)*5) - 2.5;
			player[g_Player]->CamShakeIncZ += (((float)rand() / 32767)*5) - 2.5;

			Qpo->Transform_New_XRotation(&player[g_Player]->Camrot, player[g_Player]->CamShakeIncX/1500);
			Qpo->Transform_Multiply(&player[g_Player]->ViewXForm, &player[g_Player]->Camrot, &player[g_Player]->ViewXForm);
			Qpo->Transform_RotateY(&player[g_Player]->ViewXForm, player[g_Player]->CamShakeIncY/1500);
			}

		//### Heavy Shake
		if(player[g_Player]->CameraShake == 2)
			{
			if(player[g_Player]->CameraShakeINIT == 0)
				{
				player[g_Player]->CameraShakeINIT = 1;
				
				player[g_Player]->CamShakeIncX = ((((float)rand() / 32767)*70) - 35);
				if(player[g_Player]->CamShakeIncX > 0 && player[g_Player]->CamShakeIncX < 35) player[g_Player]->CamShakeIncX = 35;
				if(player[g_Player]->CamShakeIncX < 0 && player[g_Player]->CamShakeIncX > -35) player[g_Player]->CamShakeIncX = -35;
				player[g_Player]->CamShakeIncY = 2;
				player[g_Player]->CamShakeIncZ = ((((float)rand() / 32767)*70) - 35);
				if(player[g_Player]->CamShakeIncZ > 0 && player[g_Player]->CamShakeIncZ < 35) player[g_Player]->CamShakeIncZ = 35;
				if(player[g_Player]->CamShakeIncZ < 0 && player[g_Player]->CamShakeIncZ > -35) player[g_Player]->CamShakeIncZ = -35;
				}
			else
				{
				player[g_Player]->CamShakeIncX *= -0.6;
				player[g_Player]->CamShakeIncY *= -0.95;
				player[g_Player]->CamShakeIncZ *= -0.6;
				}

			player[g_Player]->CamShakeIncX += (((float)rand() / 32767)*8) - 4;
			player[g_Player]->CamShakeIncY += (((float)rand() / 32767)*8) - 4;
			player[g_Player]->CamShakeIncZ += (((float)rand() / 32767)*8) - 4;

			Qpo->Transform_New_XRotation(&player[g_Player]->Camrot, player[g_Player]->CamShakeIncX/1000);
			Qpo->Transform_Multiply(&player[g_Player]->ViewXForm, &player[g_Player]->Camrot, &player[g_Player]->ViewXForm);
			Qpo->Transform_RotateY(&player[g_Player]->ViewXForm, player[g_Player]->CamShakeIncY/1000);
			}

		//### Heavy Shake
		if(player[g_Player]->CameraShake == 3)
			{
			if(player[g_Player]->CameraShakeINIT == 0)
				{
				player[g_Player]->CameraShakeINIT = 1;
				
				player[g_Player]->CamShakeIncX = ((((float)rand() / 32767) * (70 * (player[g_Player]->JINK3_PowerFactor/25))) - (35 * (player[g_Player]->JINK3_PowerFactor/25)));
				if(player[g_Player]->CamShakeIncX > 0 && player[g_Player]->CamShakeIncX < (35 * (player[g_Player]->JINK3_PowerFactor/25))) player[g_Player]->CamShakeIncX = (35 * (player[g_Player]->JINK3_PowerFactor/25));
				if(player[g_Player]->CamShakeIncX < 0 && player[g_Player]->CamShakeIncX > -(35 * (player[g_Player]->JINK3_PowerFactor/25))) player[g_Player]->CamShakeIncX = -(35 * (player[g_Player]->JINK3_PowerFactor/25));
				player[g_Player]->CamShakeIncY = 2;
				player[g_Player]->CamShakeIncZ = ((((float)rand() / 32767)*70) - (35 * (player[g_Player]->JINK3_PowerFactor/25)));
				if(player[g_Player]->CamShakeIncZ > 0 && player[g_Player]->CamShakeIncZ < (35 * (player[g_Player]->JINK3_PowerFactor/25))) player[g_Player]->CamShakeIncZ = (35 * (player[g_Player]->JINK3_PowerFactor/25));
				if(player[g_Player]->CamShakeIncZ < 0 && player[g_Player]->CamShakeIncZ > -(35 * (player[g_Player]->JINK3_PowerFactor/25))) player[g_Player]->CamShakeIncZ = -(35 * (player[g_Player]->JINK3_PowerFactor/25));
				}
			else
				{
				if(player[g_Player]->Mposestate != 16)
					{
					player[g_Player]->CamShakeIncX *= -0.6;
					player[g_Player]->CamShakeIncY *= -0.95;
					player[g_Player]->CamShakeIncZ *= -0.6;
					}
				else
					{
					player[g_Player]->CamShakeIncX *= -1 * (player[g_Player]->JINK3_PowerFactor/25);
					player[g_Player]->CamShakeIncY *= -1 * (player[g_Player]->JINK3_PowerFactor/25);
					player[g_Player]->CamShakeIncZ *= -1 * (player[g_Player]->JINK3_PowerFactor/25);
					}
				}

			player[g_Player]->CamShakeIncX += (((((float)rand() / 32767)*8) - 4) * (player[g_Player]->JINK3_PowerFactor/25));
			player[g_Player]->CamShakeIncY += (((((float)rand() / 32767)*8) - 4) * (player[g_Player]->JINK3_PowerFactor/25));
			player[g_Player]->CamShakeIncZ += (((((float)rand() / 32767)*8) - 4) * (player[g_Player]->JINK3_PowerFactor/25));

			Qpo->Transform_New_XRotation(&player[g_Player]->Camrot, player[g_Player]->CamShakeIncX/5000);
			Qpo->Transform_Multiply(&player[g_Player]->ViewXForm, &player[g_Player]->Camrot, &player[g_Player]->ViewXForm);
			Qpo->Transform_RotateY(&player[g_Player]->ViewXForm, player[g_Player]->CamShakeIncY/5000);
			}

		//### Shift Camera XForm
		player[g_Player]->ViewXForm.Translation.x += player[g_Player]->CamShakeIncX;
		player[g_Player]->ViewXForm.Translation.y += player[g_Player]->CamShakeIncY;
		player[g_Player]->ViewXForm.Translation.z += player[g_Player]->CamShakeIncZ;

		player[g_Player]->CamShkCNT++;
		if(player[g_Player]->CamShkCNT > player[g_Player]->CamShkTIME)
			{
			player[g_Player]->CameraShake = 0;
			player[g_Player]->CamShkCNT = 0;
			}
		}

	// Set our camera to the new xform
	Qpo->Camera_SetTransform(_->CVar, &player[g_Player]->ViewXForm, player[g_Player]->ViewXForm.Translation);

	//## Set FOV
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 1) Qpo->Camera_SetFOV(_->CVar, 2 - player[g_Player]->WeaponZoomFACT);
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 2) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.770)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 3) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.810)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 4) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.855)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 5) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.900)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 6) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.920)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 7) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.940)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 8) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.960)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 9) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.970)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 10) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.980)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 11) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.990)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 12) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.995)*2));
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE == 13) Qpo->Camera_SetFOV(_->CVar, 2 - ((player[g_Player]->WeaponZoomFACT*0.999)*2));

// View Rotation *******************************************************************************************
//**********************************************************************************************************


	//##### Keyboard Control
	//Temp Bike Tests
	if(KEY_PRESS_DOWN(QIN_f))
		{
		playerAV[g_Player]->Xform.Translation.x = 0;
		playerAV[g_Player]->Xform.Translation.y = 0;
		playerAV[g_Player]->Xform.Translation.z = 0;

		player[g_Player]->Vehicle.Phys_DownVelocity = 0;
		player[g_Player]->Vehicle.Phys_FSpinLift = 0;
		player[g_Player]->Vehicle.Phys_VerticalRotate = 0;

		Qpo->Transform_New(&playerAV[g_Player]->Xform);
		TempVec1.x = 1;
		TempVec1.y = 0;
		TempVec1.z = 0;
		TempVec2.x = 0;
		TempVec2.y = 0;
		TempVec2.z = 1;
		TempVec3.x = 0;
		TempVec3.y = -1;
		TempVec3.z = 0;
		player[g_Player]->Vehicle.STRVehicleUP.x = 0;
		player[g_Player]->Vehicle.STRVehicleUP.y = 0;
		player[g_Player]->Vehicle.STRVehicleUP.z = 1;
		Qpo->Transform_New_LeftUpIn(&playerAV[g_Player]->Xform, &TempVec1, &TempVec2, &TempVec3);
		Qpo->Transform_Orthonormalize(&playerAV[g_Player]->Xform);
		}


	//### Accelerator Down
	if(_->mbutton[g_Player])
		{
		if(player[g_Player]->Vehicle.JINKrush == 0)
			{
			player[g_Player]->Vehicle.Phys_Power += 0.67 * _->TimeScale;
			if(player[g_Player]->Vehicle.Phys_Power > 20) player[g_Player]->Vehicle.Phys_Power = 20;
			}

		if(player[g_Player]->Vehicle.JINKrush == 1)
			{
			player[g_Player]->Vehicle.Phys_Power += 3 * _->TimeScale;
			if(player[g_Player]->Vehicle.Phys_Power > 100) player[g_Player]->Vehicle.Phys_Power = 100;
			}

		player[g_Player]->Vehicle.Gear_Power += 0.08 * _->TimeScale;

		if(player[g_Player]->Vehicle.Gear_Power > 1)
			{
			if(player[g_Player]->Vehicle.Gear_Number < 5)
				{
				player[g_Player]->Vehicle.Gear_Number++;
				player[g_Player]->Vehicle.Gear_Power = 0.3;
				}
			}

		if(player[g_Player]->Vehicle.SOUNDFLAGPower == 0)
			{
			player[g_Player]->Vehicle.SOUNDFLAGPower = 1;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBPower, _->Volume, _->Pan, _->S_TimeScale*player[g_Player]->Vehicle.Gear_Power, false, &player[g_Player]->RFistPos.Translation);
			}


		player[g_Player]->Vehicle.SOUNDCNTpower++;

		if(player[g_Player]->Vehicle.SOUNDCNTpower > ((1-(player[g_Player]->Vehicle.Phys_Power/20))*20))
			{
			player[g_Player]->Vehicle.SOUNDCNTpower = 0;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

		//if(QpoSound_SoundIsPlaying(SoundSys, player[g_Player]->Vehicle.SOUNDpowerdown1) == false)
		//	{
			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBLoopPower, _->Volume, _->Pan, _->S_TimeScale*player[g_Player]->Vehicle.Gear_Power, false, &player[g_Player]->RFistPos.Translation);
			//}

		//if(QpoSound_SoundIsPlaying(SoundSys, player[g_Player]->Vehicle.SOUNDpowerdown2) == false)
		//	{
			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBLoopPower2, _->Volume, _->Pan, _->S_TimeScale*player[g_Player]->Vehicle.Gear_Power, false, &player[g_Player]->RFistPos.Translation);
		//	}

		//if(QpoSound_SoundIsPlaying(SoundSys, player[g_Player]->Vehicle.SOUNDpowerdown3) == false)
		//	{
			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBLoopPower3, _->Volume, _->Pan, _->S_TimeScale*player[g_Player]->Vehicle.Gear_Power, false, &player[g_Player]->RFistPos.Translation);
			}
		//	}
		}
	else
		{
		player[g_Player]->Vehicle.SOUNDFLAGPower = 0;
		player[g_Player]->Vehicle.Phys_Power -= 2 * _->TimeScale;
		if(player[g_Player]->Vehicle.Phys_Power < 0) player[g_Player]->Vehicle.Phys_Power = 0;

		player[g_Player]->Vehicle.Gear_Power -= 0.03 * _->TimeScale;

		if(player[g_Player]->Vehicle.Gear_Power < 0)
			{
			player[g_Player]->Vehicle.Gear_Number = 0;
			player[g_Player]->Vehicle.Gear_Power = 0;
			}
		}


	//### Braking
	if(_->rbutton[g_Player])
		{
		player[g_Player]->Vehicle.Phys_Brake += 0.06 * _->TimeScale;
		if(player[g_Player]->Vehicle.Phys_Brake > 5) player[g_Player]->Vehicle.Phys_Brake = 5;
		}
	else
		{
		player[g_Player]->Vehicle.Phys_Brake -= 10 * _->TimeScale;
		if(player[g_Player]->Vehicle.Phys_Brake < 0) player[g_Player]->Vehicle.Phys_Brake = 0;
		}


	if(KEY_PRESS_DOWN(QIN_z)) //##### Super Lean Turning
		{
		if(player[g_Player]->Vehicle.Phys_TurnMULT + 0.2 <= 3.1) player[g_Player]->Vehicle.Phys_TurnMULT += 0.2;
		else player[g_Player]->Vehicle.Phys_TurnMULT = 3.1;
		}
	else
		{
		if(player[g_Player]->Vehicle.Phys_TurnMULT - 0.2 >= 1.35) player[g_Player]->Vehicle.Phys_TurnMULT -= 0.2;
		else player[g_Player]->Vehicle.Phys_TurnMULT = 1.35;
		}


	if(KEY_DOWN_a())
		{
		if(player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt + 0.025 <= 0.67) player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt += 0.025;
		else player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0.67;

		if(player[g_Player]->Vehicle.Phys_FrictionAMT > 1 && ((player[g_Player]->Vehicle.Phys_Velocity < 0.2 && player[g_Player]->Vehicle.Phys_Power > 10 && player[g_Player]->Vehicle.Phys_Brake > 3)))
			{
			player[g_Player]->Vehicle.Angles.y += 0.075;
			player[g_Player]->Vehicle.Phys_TurnLean = 0;
			}
		}

	if(KEY_DOWN_d())
		{
		if(player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt - 0.025 >= 0) player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt -= 0.025;
		else player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt = 0;

		if(player[g_Player]->Vehicle.Phys_FrictionAMT > 1 && ((player[g_Player]->Vehicle.Phys_Velocity < 0.2 && player[g_Player]->Vehicle.Phys_Power > 10 && player[g_Player]->Vehicle.Phys_Brake > 3)))
			{
			player[g_Player]->Vehicle.Angles.y -= 0.075;
			player[g_Player]->Vehicle.Phys_TurnLean = 0;
			}
		}

	if(!KEY_DOWN_a() && !KEY_DOWN_d())
		{
		player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt += (0.335 - player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt) / 3;
		}


	if(KEY_PRESS_DOWN(QIN_KP1))
		{
		player[g_Player]->Vehicle.AttachTempVEC.x -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP2))
		{
		player[g_Player]->Vehicle.AttachTempVEC.x += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP3))
		{
		player[g_Player]->Vehicle.AttachTempVEC.y -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP4))
		{
		player[g_Player]->Vehicle.AttachTempVEC.y += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP5))
		{
		player[g_Player]->Vehicle.AttachTempVEC.z -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP6))
		{
		player[g_Player]->Vehicle.AttachTempVEC.z += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_1))
		{
		player[g_Player]->Vehicle.AttachTempROTX -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_2))
		{
		player[g_Player]->Vehicle.AttachTempROTX += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_3))
		{
		player[g_Player]->Vehicle.AttachTempROTY -= 1;
		}

	if(KEY_PRESS_DOWN(QIN_4))
		{
		player[g_Player]->Vehicle.AttachTempROTY += 1;
		}

	if(KEY_PRESS_DOWN(QIN_5))
		{
		player[g_Player]->Vehicle.AttachTempROTZ -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_6))
		{
		player[g_Player]->Vehicle.AttachTempROTZ += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_7))
		{
		player[g_Player]->Vehicle.Const_WheelSettleSpin -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_8))
		{
		player[g_Player]->Vehicle.Const_WheelSettleSpin += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_9))
		{
		player[g_Player]->Vehicle.Const_WheelSettleDVel -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_0))
		{
		player[g_Player]->Vehicle.Const_WheelSettleDVel += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_LEFT))
		{
		player[g_Player]->Vehicle.Const_SpringLimit -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_RIGHT))
		{
		player[g_Player]->Vehicle.Const_SpringLimit += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_DOWN))
		{
		player[g_Player]->Vehicle.Const_SpringAbsorbVel -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_UP))
		{
		player[g_Player]->Vehicle.Const_SpringAbsorbVel += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_HOME))
		{
		player[g_Player]->Vehicle.Const_ForceFactor -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_END))
		{
		player[g_Player]->Vehicle.Const_ForceFactor += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_INSERT))
		{
		player[g_Player]->Vehicle.Const_SpringAbsorbSpin -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_DELETE))
		{
		player[g_Player]->Vehicle.Const_SpringAbsorbSpin += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_z))
		{
		player[g_Player]->Vehicle.Const_LightTouchFactor -= 0.005;
		}

	if(KEY_PRESS_DOWN(QIN_CAPSLOCK))
		{
		player[g_Player]->Vehicle.Const_LightTouchFactor += 0.005;
		}


	if(KEY_PRESS_DOWN(QIN_F1))
		{
		player[g_Player]->Vehicle.Const_MiddleCOGDISTX -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_F2))
		{
		player[g_Player]->Vehicle.Const_MiddleCOGDISTX += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_F3))
		{
		player[g_Player]->Vehicle.Const_MiddleCOGDISTY -= 0.1;
		}

	if(KEY_PRESS_DOWN(QIN_F4))
		{
		player[g_Player]->Vehicle.Const_MiddleCOGDISTY += 0.1;
		}

	if(KEY_PRESS_DOWN(QIN_F5))
		{
		player[g_Player]->Vehicle.Const_MiddleCOGDISTZ -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_F6))
		{
		player[g_Player]->Vehicle.Const_MiddleCOGDISTZ += 0.01;
		}

	if(player[g_Player]->Vehicle.Const_MiddleCOGDISTZ > 0.67) player[g_Player]->Vehicle.Const_MiddleCOGDISTZ = 0.67;
	if(player[g_Player]->Vehicle.Const_MiddleCOGDISTZ < 0) player[g_Player]->Vehicle.Const_MiddleCOGDISTZ = 0;


	if(KEY_PRESS_DOWN(QIN_LEFT))
		{
		player[g_Player]->Vehicle.Temp_Rotation -= 0.1;
		}

	if(KEY_PRESS_DOWN(QIN_RIGHT))
		{
		player[g_Player]->Vehicle.Temp_Rotation += 0.1;
		}


	//### - Weight Shifting
	if(KEY_DOWN_w())
		{
		player[g_Player]->Mposestate = 1;
		player[g_Player]->blendamount[110] = 0;
		player[g_Player]->blendamount[112] = 0;

		/*if(player[g_Player]->Vehicle.Phys_Velocity > 1 && (!(player[g_Player]->Vehicle.Phys_FWheelTOUCH == 1 && player[g_Player]->Vehicle.Phys_RWheelTOUCH == 1) || ((player[g_Player]->Vehicle.Phys_FWheelTOUCH == 1 && player[g_Player]->Vehicle.Phys_RWheelTOUCH == 1) && _->rbutton[g_Player])))
			{
			
			}*/
		}

	/*if(KEY_DOWN_s())
		{
		player[g_Player]->Mposestate = 2;
		player[g_Player]->blendamount[110] = 0;
		player[g_Player]->blendamount[111] = 0;

		if(player[g_Player]->Vehicle.Phys_Velocity > 1)
			{
			if(player[g_Player]->Vehicle.Phys_WheelieLIFT + 0.025 <= 0.785) player[g_Player]->Vehicle.Phys_WheelieLIFT += 0.025;
			else player[g_Player]->Vehicle.Phys_WheelieLIFT = 0.785;
			}
		else
			{
			if(player[g_Player]->Vehicle.Phys_WheelieLIFT - 0.025 >= 0) player[g_Player]->Vehicle.Phys_WheelieLIFT -= 0.025;
			else player[g_Player]->Vehicle.Phys_WheelieLIFT = 0;
			}
		}
	else
		{
		if(player[g_Player]->Vehicle.Phys_WheelieLIFT - 0.025 >= 0) player[g_Player]->Vehicle.Phys_WheelieLIFT -= 0.025;
		else player[g_Player]->Vehicle.Phys_WheelieLIFT = 0;
		}*/


	if(KEY_DOWN_s())	//### BIKE WHEELIE ###
		{
		player[g_Player]->Mposestate = 2;
		player[g_Player]->blendamount[110] = 0;
		player[g_Player]->blendamount[111] = 0;

		if(player[g_Player]->Vehicle.Phys_Velocity > 1 && !(player[g_Player]->Vehicle.Phys_FWheelTOUCH == 1 && player[g_Player]->Vehicle.Phys_RWheelTOUCH == 1))
			{
			Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->Vehicle.Phys_TurnMotionVec);
			if(player[g_Player]->Vehicle.Phys_TurnMotionAMT < 20) player[g_Player]->Vehicle.Phys_TurnMotionAMT += 1;
			}
		}
	else { if(player[g_Player]->Vehicle.Phys_TurnMotionAMT > 0) player[g_Player]->Vehicle.Phys_TurnMotionAMT -= 1; }


	if(!KEY_DOWN_w() && !KEY_DOWN_s())
		{
		player[g_Player]->Mposestate = 0;
		player[g_Player]->blendamount[111] = 0;
		player[g_Player]->blendamount[112] = 0;

		player[g_Player]->Vehicle.SOUNDCNTloop++;

		if(player[g_Player]->Vehicle.SOUNDCNTloop > 10)
			{
			player[g_Player]->Vehicle.SOUNDCNTloop = 0;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBStartLoop, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
			}
		}


	//##### -  MotorCycle Physics  - #####

	//## Standard Acceleration
	if(player[g_Player]->Vehicle.Phys_RWheelTOUCH == 1 || 1)
		{
		if(player[g_Player]->Mposestate != 2)
			{
			if(player[g_Player]->Vehicle.Phys_Velocity < player[g_Player]->Vehicle.Const_MaxSpeed) player[g_Player]->Vehicle.Phys_Velocity += (player[g_Player]->Vehicle.Phys_Power / player[g_Player]->Vehicle.Const_Weight) / (((player[g_Player]->Vehicle.Phys_FrictionAMT - 1) / 4) + 1);
			}
		else if(player[g_Player]->Vehicle.Phys_Velocity < player[g_Player]->Vehicle.Const_MaxSpeed) player[g_Player]->Vehicle.Phys_Velocity += ((player[g_Player]->Vehicle.Phys_Power / player[g_Player]->Vehicle.Const_Weight)*2) / (((player[g_Player]->Vehicle.Phys_FrictionAMT - 1) / 4) + 1);
		}
	//TODO weight becomes 0 when not touching ground

	if(player[g_Player]->Vehicle.Phys_FWheelTOUCH == 1 || 1)
		{
		player[g_Player]->Vehicle.Phys_Velocity -= player[g_Player]->Vehicle.Phys_Brake / (((player[g_Player]->Vehicle.Phys_FrictionAMT - 1) / 4) + 1);
		}

	if(player[g_Player]->Mposestate == 1) player[g_Player]->Vehicle.Phys_Velocity -= 0.005 * player[g_Player]->Vehicle.Phys_Velocity;
	else player[g_Player]->Vehicle.Phys_Velocity -= 0.02 * player[g_Player]->Vehicle.Phys_Velocity;

	if(player[g_Player]->Vehicle.Phys_Velocity < 0) player[g_Player]->Vehicle.Phys_Velocity = 0;


	//##### Actual Re-allignment

	//### Set Vectors
	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->Vehicle.Model.Up);
	Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->Vehicle.Model.In);
	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &player[g_Player]->Vehicle.Model.Left);

	player[g_Player]->Vehicle.Down.x = 0;
	player[g_Player]->Vehicle.Down.y = -1;
	player[g_Player]->Vehicle.Down.z = 0;

	//##### CALCULATE FORWARD VECTOR
	//### Front Wheel Collision
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE08", &player[g_Player]->Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE05", &player[g_Player]->Vehicle.RWheelMatrix);

	player[g_Player]->Vehicle.Model.OldPos = player[g_Player]->Vehicle.RWheelMatrix.Translation;
	player[g_Player]->Vehicle.Model.NewPos = player[g_Player]->Vehicle.RWheelMatrix.Translation;
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.NewPos, player[g_Player]->Vehicle.Const_SpringLimit+(player[g_Player]->Vehicle.Const_SpringLimit/15), &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.Model.NewPos);

	/*if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.Model.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, *//* 0xffffffff, NULL, NULL, &player[g_Player]->Vehicle.FCollision))
		{
		TempVec2 = player[g_Player]->Vehicle.Model.Left;
		Qpo->Vec3d_Inverse(&TempVec2);

		Qpo->Vec3d_CrossProduct(&player[g_Player]->Vehicle.FCollision.Plane.Normal, &TempVec2, &TempVec1);

		player[g_Player]->Vehicle.Phys_ForwardMotionVec.x += TempVec1.x / player[g_Player]->Vehicle.Phys_FrictionAMT;
		player[g_Player]->Vehicle.Phys_ForwardMotionVec.y += TempVec1.y / player[g_Player]->Vehicle.Phys_FrictionAMT;
		player[g_Player]->Vehicle.Phys_ForwardMotionVec.z += TempVec1.z / player[g_Player]->Vehicle.Phys_FrictionAMT;

		Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.Phys_ForwardMotionVec);
		}*/


	//##### =======-----  FRICTION SYSTEM -----======= ######

	//#### Calculate - Friction Causes -

	//## Turning ##
	if(player[g_Player]->Vehicle.Phys_TurnMULT > 1.35 && player[g_Player]->Vehicle.Phys_Velocity > player[g_Player]->Vehicle.Const_FRICMinSlide)
		{
		Tempfloat = (player[g_Player]->Vehicle.Phys_TurnMULT - 1.35) * (((player[g_Player]->Vehicle.Phys_Velocity - player[g_Player]->Vehicle.Const_FRICMinSlide) / (player[g_Player]->Vehicle.Const_MaxSpeed / 2)) + 1);
		if(Tempfloat > 0) player[g_Player]->Vehicle.Phys_FrictionSTR -= Tempfloat;
		}
	else	//##### ---- Power Down Slide Restoration ---- #####
		{
		player[g_Player]->Vehicle.Phys_FrictionSTR += ((1 - (player[g_Player]->Vehicle.Phys_Power / 20))* 0.25) / player[g_Player]->Vehicle.Phys_FrictionAMT;
		}


	//## Drive ##
	if(player[g_Player]->Vehicle.Phys_Velocity < 0.2 && player[g_Player]->Vehicle.Phys_Power > 4 && player[g_Player]->Vehicle.Phys_Brake > 2)
		{
		player[g_Player]->Vehicle.Phys_FrictionSTR -= 3;
		player[g_Player]->Vehicle.Phys_Velocity = 0;
		}


	//## Power Wheel spin ##
	if(player[g_Player]->Vehicle.Phys_Power > (player[g_Player]->Vehicle.Phys_Velocity * 2))
		{
		player[g_Player]->Vehicle.Phys_FrictionSTR -= 3.2;
		}


	//## Brake ##
	if(player[g_Player]->Vehicle.Phys_Velocity * player[g_Player]->Vehicle.Phys_Brake > 25)
		{
		player[g_Player]->Vehicle.Phys_FrictionSTR -= 4;
		}


	//#######======---- INITIAL POP ----======#######
	if(player[g_Player]->Vehicle.Phys_FrictionSTR > 5 && player[g_Player]->Vehicle.Phys_FrictionSTR < 8)
		{
		player[g_Player]->Vehicle.Phys_FrictionAMT = 2;
		}


	//### LIMITS ###
	if(player[g_Player]->Vehicle.Phys_FrictionSTR > 20)
		{
		player[g_Player]->Vehicle.Phys_FrictionSTR = 15;
		}

	if(player[g_Player]->Vehicle.Phys_FrictionSTR < -10)
		{
		player[g_Player]->Vehicle.Phys_FrictionSTR = -10;
		}


	//#######======---- FRICTION GROW ----======#######
	if(player[g_Player]->Vehicle.Phys_FrictionSTR >= 5)
		{
		player[g_Player]->Vehicle.Phys_FrictionAMT = 1;
		}

	if(player[g_Player]->Vehicle.Phys_FrictionSTR >= 0 && player[g_Player]->Vehicle.Phys_FrictionSTR < 5)
		{
		player[g_Player]->Vehicle.Phys_FrictionAMT = (((1 - ((player[g_Player]->Vehicle.Phys_FrictionSTR - 2) / 3)) * 2.5) + 1);
		}

	if(player[g_Player]->Vehicle.Phys_FrictionSTR < 0)
		{
		if(player[g_Player]->Vehicle.Phys_FrictionAMT < 6) player[g_Player]->Vehicle.Phys_FrictionAMT += 0.2;
		else player[g_Player]->Vehicle.Phys_FrictionAMT = 6;
		}


	//#######======---- FRICTION RESTORE ----======#######
	if(player[g_Player]->Vehicle.Phys_FrictionSTR < 8) player[g_Player]->Vehicle.Phys_FrictionSTR += 2;
	else player[g_Player]->Vehicle.Phys_FrictionSTR = 8;


	//##### +++ EFFECTS +++ #####

	if(player[g_Player]->Vehicle.Phys_FrictionAMT > 1)
		{
		player[g_Player]->Vehicle.SOUNDCNTskid++;

		if(player[g_Player]->Vehicle.SOUNDCNTskid > (5 * (1 - (player[g_Player]->Vehicle.Phys_FrictionAMT / 10))))
			{
			player[g_Player]->Vehicle.SOUNDCNTskid = 0;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBSkid, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

			//### Rear Spring Restoration
			player[g_Player]->Vehicle.Model.OldPos = player[g_Player]->Vehicle.RWheelMatrix.Translation;
			player[g_Player]->Vehicle.Model.NewPos = player[g_Player]->Vehicle.RWheelMatrix.Translation;
			Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.NewPos, player[g_Player]->Vehicle.Const_SpringLimit * 1.5, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.Model.NewPos);

			if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.Model.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &player[g_Player]->Vehicle.Collision))
				{
				//#### ADD Medias->DECAL
				QpoVec3d f_ImpactPoint(player[g_Player]->Vehicle.Collision.Impact.m_X, player[g_Player]->Vehicle.Collision.Impact.m_Y, player[g_Player]->Vehicle.Collision.Impact.m_Z);
				Q.AddDecal(f_ImpactPoint, player[g_Player]->Vehicle.Collision.Plane.Normal, 13, 2);

				jet=0;
				while(jet < (30 * (player[g_Player]->Vehicle.Phys_FrictionAMT / 10)))
					{
					//#### Smoke Blast
					Q_Cloud->Cloud[_->NomCloud].CloudType = 7;
					Q_Cloud->Cloud[_->NomCloud].CloudPos.acSet(player[g_Player]->Vehicle.Collision.Impact.m_X, player[g_Player]->Vehicle.Collision.Impact.m_Y, player[g_Player]->Vehicle.Collision.Impact.m_Z);
					Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+175;
					Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.25;	//0.33;
					Q_Cloud->Cloud[_->NomCloud].CloudTraVec = player[g_Player]->Vehicle.Model.Up;
					Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += 0.15;
					Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + (player[g_Player]->Vehicle.Phys_Power/5);
					Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;
					Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

					_->NomCloud++;
					if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
					jet++;
					}
				}
			}
		}


	//## Find CENTER OF GRAVITY
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE01", &player[g_Player]->Vehicle.COGMatrix);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.COGMatrix.Translation, 14, &player[g_Player]->Vehicle.Model.Up, &player[g_Player]->Vehicle.COGMatrix.Translation);
	//player[g_Player]->Vehicle.COGMatrix.Translation = playerAV[g_Player]->Xform.Translation;


	//## Build Force Direction Vector
	Qpo->Vec3d_New(&player[g_Player]->Vehicle.Phys_ForceDirection);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Phys_ForceDirection, -player[g_Player]->Vehicle.Phys_Velocity * _->TimeScale, &player[g_Player]->Vehicle.Model.Up, &player[g_Player]->Vehicle.Phys_ForceDirection);
	player[g_Player]->Vehicle.Phys_ForceDirection.y += player[g_Player]->Vehicle.Phys_DownVelocity * _->TimeScale;

	//### Build Force Factor
	player[g_Player]->Vehicle.Phys_ForceDirectionLength = Qpo->Vec3d_Length(&player[g_Player]->Vehicle.Phys_ForceDirection);
	player[g_Player]->Vehicle.Phys_ForceFactor = (player[g_Player]->Vehicle.Phys_ForceDirectionLength / player[g_Player]->Vehicle.Const_ForceFactor) + 1;

	//## Build Actual Force Vector
	player[g_Player]->Vehicle.Phys_ActualForceDirection = player[g_Player]->Vehicle.Phys_ForceDirection;
	Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.Phys_ActualForceDirection);
	Qpo->Vec3d_Scale(&player[g_Player]->Vehicle.Phys_ActualForceDirection, 35.5, &player[g_Player]->Vehicle.Phys_ActualForceDirection);
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.Phys_ActualForceDirection, &player[g_Player]->Vehicle.COGMatrix.Translation, &player[g_Player]->Vehicle.Phys_ActualForceDirection);

	//## Find Weight Distribution
	player[g_Player]->Vehicle.Phys_DistF = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Vehicle.Phys_ActualForceDirection, &player[g_Player]->Vehicle.FWheelMatrix.Translation);
	player[g_Player]->Vehicle.Phys_DistR = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Vehicle.Phys_ActualForceDirection, &player[g_Player]->Vehicle.RWheelMatrix.Translation);
	player[g_Player]->Vehicle.Phys_FWeightDistFactor = ( player[g_Player]->Vehicle.Phys_DistR / player[g_Player]->Vehicle.Phys_DistF ) / 35;
	player[g_Player]->Vehicle.Phys_RWeightDistFactor = ( player[g_Player]->Vehicle.Phys_DistF / player[g_Player]->Vehicle.Phys_DistR ) / 35;


	//####### Apply Vehicle Gravity
	//player[g_Player]->Vehicle.Phys_DownVelocity -= 0.5 * (( player[g_Player]->Vehicle.Const_FWeight + player[g_Player]->Vehicle.Const_RWeight) / 1.5);



	//##### ===== BEGIN FINAL VEHICLE PHYSICS ===== #####

	//### Store Old Wheel Positions
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE08", &player[g_Player]->Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE05", &player[g_Player]->Vehicle.RWheelMatrix);
	player[g_Player]->Vehicle.FWheelPOSSTR = player[g_Player]->Vehicle.FWheelMatrix.Translation;
	player[g_Player]->Vehicle.RWheelPOSSTR = player[g_Player]->Vehicle.RWheelMatrix.Translation;
	player[g_Player]->Vehicle.STR_Phys_FWheelBendPoseCnt = player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt;
	player[g_Player]->Vehicle.STR_Phys_RWheelBendPoseCnt = player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt;
	//#### FIND VEHICLE CENTER
	player[g_Player]->Vehicle.OLDCENTRALANGLEVEC = playerAV[g_Player]->Xform.Translation;
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.OLDCENTRALANGLEVEC, &player[g_Player]->Vehicle.RotatePNTVEC,  &player[g_Player]->Vehicle.OLDCENTRALANGLEVEC);

	//######### CALC FORCE VECS FOR WHEEL COLLISIONS
	Qpo->Vec3d_New(&player[g_Player]->Vehicle.FWheelFORCEVEC);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelFORCEVEC, -player[g_Player]->Vehicle.Phys_Velocity * _->TimeScale, &player[g_Player]->Vehicle.Phys_ForwardMotionVec, &player[g_Player]->Vehicle.FWheelFORCEVEC);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelFORCEVEC, -player[g_Player]->Vehicle.Phys_TurnMotionAMT * _->TimeScale, &player[g_Player]->Vehicle.Phys_TurnMotionVec, &player[g_Player]->Vehicle.FWheelFORCEVEC);
	player[g_Player]->Vehicle.FWheelFORCEVEC.y += player[g_Player]->Vehicle.Phys_DownVelocity * _->TimeScale;

	Qpo->Vec3d_New(&player[g_Player]->Vehicle.RWheelFORCEVEC);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.RWheelFORCEVEC, -player[g_Player]->Vehicle.Phys_Velocity * _->TimeScale, &player[g_Player]->Vehicle.Phys_ForwardMotionVec, &player[g_Player]->Vehicle.RWheelFORCEVEC);
	player[g_Player]->Vehicle.RWheelFORCEVEC.y += player[g_Player]->Vehicle.Phys_DownVelocity * _->TimeScale;

	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->In);
	player[g_Player]->Vehicle.Model.OldPos = player[g_Player]->Vehicle.FWheelMatrix.Translation;
	player[g_Player]->Vehicle.Model.NewPos = player[g_Player]->Vehicle.FWheelMatrix.Translation;
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.NewPos, 1, &player[g_Player]->Vehicle.FWheelFORCEVEC, &player[g_Player]->Vehicle.Model.NewPos);

	if(Qpo->Collision_RayTest(&player[g_Player]->Mins, &player[g_Player]->Maxs, &player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.Model.NewPos, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_ACTORS,*/ 0xffffffff, NULL, NULL, &player[g_Player]->Vehicle.ACollision))
		{	//### Loop to check all AI locations for first proximity check
		if(player[g_Player]->Vehicle.ACollision.Avatar != 0)
			{
			if(player[g_Player]->Vehicle.ACollision.m_AvatarID != 250)
				{
				SCRAM = player[g_Player]->Vehicle.ACollision.m_AvatarID;

				if(Q_Forge->Forge[SCRAM].LIVE == 1)
					{
					if( (Q_Forge->Forge[SCRAM].Team != player[g_Player]->Team) && (Q_Forge->Forge[SCRAM].HB_Dead == 0) && (Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha == 0) )
						{
						//### Find Distance between Avatar and Explosion
						AvatarPos = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
						AvatarPos.y += 65;
						QpoVec3d f_ImpactVector(player[g_Player]->Vehicle.ACollision.Impact.m_X, player[g_Player]->Vehicle.ACollision.Impact.m_Y, player[g_Player]->Vehicle.ACollision.Impact.m_Z);
						Qpo->Vec3d_Subtract(&AvatarPos, &f_ImpactVector, &DistVec);
						AvatarDist = Qpo->Vec3d_Length(&DistVec);
						Qpo->Vec3d_Normalize(&DistVec);

									//## Reduce Health
						Q_Forge->Forge[SCRAM].HB_ReduceOld = Q_Forge->Forge[SCRAM].HB_Health;

						Q_Forge->Forge[SCRAM].HB_Health -= ((100 * 3) + (player[g_Player]->Vehicle.Phys_Velocity * 4)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 100)) + 0.75);
						if(Q_Forge->Forge[SCRAM].HB_Health < 0) Q_Forge->Forge[SCRAM].HB_Health = 0;

						//### Experience Storage
						player[g_Player]->AvatarDMGSTORE[SCRAM] += ((100 * 3) + (player[g_Player]->Vehicle.Phys_Velocity)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 100)) + 0.75);

						//#### Avatar DEATH
						if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
							{
							Q_Forge->Forge[SCRAM].HB_Health = 0;

							

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

							if(_->TimeHole == 0)
							{ _->TimeHole = 4;	_->TimeRotate = 1; }

							Q_Forge->Forge[SCRAM].HB_Dead = 1;

							if((player[g_Player]->AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
								{
								//### Add Experience to attacking AVATAR
								player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

								player[g_Player]->MSG_XPON = 1;
								player[g_Player]->MSG_XPInit = 0;
								player[g_Player]->MSG_XPScreenDIST = 0;
								player[g_Player]->MSG_XPScreenDistINC = 50;
								player[g_Player]->MSG_XPScreenDIR = 0;
								player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);
								}

							//##### Find KO Owner
							UniversalDMGSTR = 0;
							
							if(player[g_Player]->AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

							jet = 0;
							while(jet < _->NomAI)
								{
								if(Q_Forge->Forge[jet].LIVE == 1)
									{
									if(Q_Forge->Forge[jet].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
									}
								jet++;
								}

							if(DeliverKOID == 250)
								{
								//### Create Item for attacking Avatar
								player[g_Player]->DecFinger = ((float)rand() / 32767) * 6;

								if((player[g_Player]->DecFinger <= 100 * (Q_Forge->Forge[SCRAM].CharDATA.Level/1000)))
									{
									player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[SCRAM].CharDATA.Level);
									player[g_Player]->MSG_ITEMON = 1;
									player[g_Player]->MSG_ITEMInit = 0;
									player[g_Player]->MSG_ITEMScreenDIST = 800;
									player[g_Player]->MSG_ITEMScreenDistINC = 17;
									player[g_Player]->MSG_ITEMScreenDIR = 0;
									}

								//SET Knockout
								_->KnockOutFLAG = 1;
								_->KnockOutTIMER = 0;
								_->KnockOutCNT = 0;
								_->KnockOutINIT = 0;
								_->KnockOutHEIGHT = 0;

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								//### Write out CHARDATA
								Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

								//####### REACTIVATE ITEM ATTRIBUTES
								Q.ActivateItems();
								}
							}

						Q_Forge->Forge[SCRAM].HB_HReduceON = 1;

						Q_Forge->Forge[SCRAM].HB_ReduceHInc = 10;
						Q_Forge->Forge[SCRAM].HB_ReduceHeight = 573;
						Q_Forge->Forge[SCRAM].HB_ReduceRectColor.red = 255;//100 + ( 155 * ( HitType / 10 ) );
						Q_Forge->Forge[SCRAM].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[SCRAM].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[SCRAM].HB_ReduceRectColor.alpha = 255;

						if(&Q_Forge->Forge[SCRAM].Shadows[1].Avatar != 0)
							{
							Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[SCRAM].Shadows[1].Xform.Translation);
							Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[SCRAM].Shadows[2].Xform.Translation);
							Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[SCRAM].Shadows[3].Xform.Translation);
							Qpo->Avatar_ClearPose(Q_Forge->Forge[SCRAM].Shadows[1].Avatar, &Q_Forge->Forge[SCRAM].Shadows[1].Xform);
							Qpo->Avatar_ClearPose(Q_Forge->Forge[SCRAM].Shadows[2].Avatar, &Q_Forge->Forge[SCRAM].Shadows[2].Xform);
							Qpo->Avatar_ClearPose(Q_Forge->Forge[SCRAM].Shadows[3].Avatar, &Q_Forge->Forge[SCRAM].Shadows[3].Xform);
							}

						Q_Forge->Forge[SCRAM].HitReactScale = 0.05;
												
						Q_Forge->Forge[SCRAM].MoveReactVec = DistVec;
						if(Q_Forge->Forge[SCRAM].MoveReactVec.y < 0) Q_Forge->Forge[SCRAM].MoveReactVec.y = 0;

						Q_Forge->Forge[SCRAM].MoveReactSpeed = 4 + (player[g_Player]->Vehicle.Phys_Velocity/5);

							//## Reset Hit Wall
						Q_Forge->Forge[SCRAM].HitWall = 0;
												
						if(Q_Forge->Forge[SCRAM].Aposestate != 91)
							{
							Q_Forge->Forge[SCRAM].Aposestate = 91;
							Q_Forge->Forge[SCRAM].attackon = 1;
							Q_Forge->Forge[SCRAM].attposecnt = 0;
							Q_Forge->Forge[SCRAM].CrunchTimer = 0;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						else
							{	//Reset DownSpeed
							Q_Forge->Forge[SCRAM].DownSpeed = 2;
							Q_Forge->Forge[SCRAM].CrunchTimer = 0;
							Q_Forge->Forge[SCRAM].attposecnt = 0.47;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						}
					}
				}
			}
		}


	//####### PLACE WHEELS
	//### Front Wheel
	player[g_Player]->Vehicle.Model.OldPos = player[g_Player]->Vehicle.FWheelPOSSTR;
	player[g_Player]->Vehicle.FWheelNEWPOS = player[g_Player]->Vehicle.FWheelPOSSTR;
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.FWheelNEWPOS, &player[g_Player]->Vehicle.FWheelFORCEVEC, &player[g_Player]->Vehicle.FWheelNEWPOS);
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.FWheelFORCEVEC, &player[g_Player]->Vehicle.Model.OldPos);
	//Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.OldPos, player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.OldPos, -50, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelNEWPOS, player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.FWheelNEWPOS);

	if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.FWheelNEWPOS, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &player[g_Player]->Vehicle.FCollision))
		{
		player[g_Player]->Vehicle.Phys_FWheelTOUCH = 1;

		player[g_Player]->Vehicle.FWheelTESET = player[g_Player]->Vehicle.FWheelNEWPOS;
		QpoVec3d f_ImpactVector(player[g_Player]->Vehicle.FCollision.Impact.m_X, player[g_Player]->Vehicle.FCollision.Impact.m_Y, player[g_Player]->Vehicle.FCollision.Impact.m_Z);
		player[g_Player]->Vehicle.FWheelNEWPOS = f_ImpactVector;

		//Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelTESET, player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.FWheelTESET);

		//#### TEMP
		//player[g_Player]->Vehicle.Phys_DownVelocity = 0;

		//##### CALCULATE CRUNCH DISTANCE
		player[g_Player]->Vehicle.FWheelCompressionDIST = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Vehicle.FWheelTESET, &f_ImpactVector);

			//### Full Compression	TODO ADD BOUNCE VECTORS AND SPIN
		if(player[g_Player]->Vehicle.FWheelCompressionDIST > player[g_Player]->Vehicle.Const_SpringCrunchMAX)
			{
			player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt = 0.67;
			}
		else//### Minor Compression
			{
			player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt = (0.335 + ((player[g_Player]->Vehicle.FWheelCompressionDIST / 15) * 0.335));
			}
		}
	else
		{
		player[g_Player]->Vehicle.Phys_FWheelTOUCH = 0;

		if((player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt - 0.05) >= 0) player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt -= 0.05;
		else player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt = 0;
		}

	//player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt = player[g_Player]->Vehicle.Const_MiddleCOGDISTZ;

	player[g_Player]->Vehicle.Phys_FSpringStrength = player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt * player[g_Player]->Vehicle.Const_SpringPower;

	//### Rear Wheel
	player[g_Player]->Vehicle.Model.OldPos = player[g_Player]->Vehicle.RWheelPOSSTR;
	player[g_Player]->Vehicle.RWheelNEWPOS = player[g_Player]->Vehicle.RWheelPOSSTR;
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.RWheelNEWPOS, &player[g_Player]->Vehicle.RWheelFORCEVEC, &player[g_Player]->Vehicle.RWheelNEWPOS);
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.RWheelFORCEVEC, &player[g_Player]->Vehicle.Model.OldPos);
	//Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.OldPos, player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.OldPos, -50, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.RWheelNEWPOS, player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.RWheelNEWPOS);

	if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.RWheelNEWPOS, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &player[g_Player]->Vehicle.RCollision))
		{
		player[g_Player]->Vehicle.Phys_RWheelTOUCH = 1;

		player[g_Player]->Vehicle.RWheelTESET = player[g_Player]->Vehicle.RWheelNEWPOS;
		QpoVec3d f_ImpactVector(player[g_Player]->Vehicle.RCollision.Impact.m_X, player[g_Player]->Vehicle.RCollision.Impact.m_Y, player[g_Player]->Vehicle.RCollision.Impact.m_Z);
		player[g_Player]->Vehicle.RWheelNEWPOS = f_ImpactVector;

		//Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.RWheelTESET, player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.RWheelTESET);

		//#### TEMP
		//player[g_Player]->Vehicle.Phys_DownVelocity = 0;

			TempVec2 = player[g_Player]->Vehicle.Model.Left;
			Qpo->Vec3d_Inverse(&TempVec2);

			Qpo->Vec3d_CrossProduct(&player[g_Player]->Vehicle.FCollision.Plane.Normal, &TempVec2, &TempVec1);

			player[g_Player]->Vehicle.Phys_ForwardMotionVec.x += TempVec1.x / player[g_Player]->Vehicle.Phys_FrictionAMT;
			player[g_Player]->Vehicle.Phys_ForwardMotionVec.y += TempVec1.y / player[g_Player]->Vehicle.Phys_FrictionAMT;
			player[g_Player]->Vehicle.Phys_ForwardMotionVec.z += TempVec1.z / player[g_Player]->Vehicle.Phys_FrictionAMT;

			Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.Phys_ForwardMotionVec);

		//##### CALCULATE CRUNCH DISTANCE
		player[g_Player]->Vehicle.RWheelCompressionDIST = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Vehicle.RWheelTESET, &f_ImpactVector);

			//### Full Compression	TODO ADD BOUNCE VECTORS AND SPIN
		if(player[g_Player]->Vehicle.RWheelCompressionDIST > player[g_Player]->Vehicle.Const_SpringCrunchMAX)
			{
			player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt = 0.67;
			}
		else//### Minor Compression
			{
			player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt = (0.335 + ((player[g_Player]->Vehicle.RWheelCompressionDIST / 15) * 0.335));
			}
		}
	else
		{
		player[g_Player]->Vehicle.Phys_RWheelTOUCH = 0;

		if((player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt - 0.05) >= 0) player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt -= 0.05;
		else player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt = 0;
		}

	player[g_Player]->Vehicle.Phys_RSpringStrength = player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt * player[g_Player]->Vehicle.Const_SpringPower;

	//player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt = player[g_Player]->Vehicle.Const_MiddleCOGDISTZ;


	//##### VAPOR TRAILS

	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE08", &player[g_Player]->Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE05", &player[g_Player]->Vehicle.RWheelMatrix);


	if(player[g_Player]->Vehicle.JINKrush == 1)
		{
		ColourSTART.red = 50;
		ColourSTART.green = 255;
		ColourSTART.blue = 50;
		ColourSTART.alpha = 50;
		ColourEND.red = 50;
		ColourEND.green = 255;
		ColourEND.blue = 0;
		ColourEND.alpha = 0;

		TempVec1 = player[g_Player]->Vehicle.RWheelMatrix.Translation;
		TempVec2 = player[g_Player]->Vehicle.RWheelMatrix.Translation;

		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &TempVec3);
		Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->Vehicle.Model.Up);
		Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &player[g_Player]->Vehicle.Model.Left);
		//Qpo->Vec3d_Inverse(&TempVec3);

		Qpo->Vec3d_AddScaled(&TempVec1, -22, &player[g_Player]->Vehicle.Model.Up, &TempVec1);
		Qpo->Vec3d_AddScaled(&TempVec2, -22, &player[g_Player]->Vehicle.Model.Up, &TempVec2);

		Qpo->Vec3d_AddScaled(&TempVec1, 17, &player[g_Player]->Vehicle.Model.Left, &TempVec1);
		Qpo->Vec3d_AddScaled(&TempVec2, -17, &player[g_Player]->Vehicle.Model.Left, &TempVec2);

		if(Q_VaporTrail->VaporTrail[0].NomPoints <= 998) Q.AddTrailPNT(0, TempVec1, ColourSTART, ColourEND, TempVec3, 0);
		if(Q_VaporTrail->VaporTrail[1].NomPoints <= 998) Q.AddTrailPNT(1, TempVec2, ColourSTART, ColourEND, TempVec3, 0);
		}
	else
		{
		Q_VaporTrail->VaporTrail[0].NomPoints = 0;
		Q_VaporTrail->VaporTrail[1].NomPoints = 0;
		}


	TempVec1 = playerAV[g_Player]->Xform.Translation;
	TempVec2 = playerAV[g_Player]->Xform.Translation;

	Qpo->Vec3d_AddScaled(&TempVec1, 40, &TempVec3, &TempVec1);
	Qpo->Vec3d_AddScaled(&TempVec1, -35, &player[g_Player]->Vehicle.Model.Up, &TempVec1);
	Qpo->Vec3d_AddScaled(&TempVec1, -4, &player[g_Player]->Vehicle.Model.Left, &TempVec1);

	Qpo->Vec3d_AddScaled(&TempVec2, 40, &TempVec3, &TempVec2);
	Qpo->Vec3d_AddScaled(&TempVec2, -35, &player[g_Player]->Vehicle.Model.Up, &TempVec2);
	Qpo->Vec3d_AddScaled(&TempVec2, 4, &player[g_Player]->Vehicle.Model.Left, &TempVec2);


	//##### SMOKE GEN
	jet=0;
	while(jet < 1)
		{
		Q_Cloud->Cloud[_->NomCloud].CloudType = 10;

		Q_Cloud->Cloud[_->NomCloud].CloudPos = TempVec1;

		Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*100)+100;
		Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.02;

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec = TempVec3;

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*0.2;
		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.2) + 0.5;
		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*0.2;

		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*((player[g_Player]->Vehicle.Phys_Power/10) + 1);

		Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

		Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

		_->NomCloud++;
		if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
		jet++;
		}

	jet=0;
	while(jet < 1)
		{
		Q_Cloud->Cloud[_->NomCloud].CloudType = 10;

		Q_Cloud->Cloud[_->NomCloud].CloudPos = TempVec2;

		Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*100)+100;
		Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.02;

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec = TempVec3;

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*0.2;
		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*0.2) + 0.5;
		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*0.2;

		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*((player[g_Player]->Vehicle.Phys_Power/10) + 1);

		Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

		Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

		_->NomCloud++;
		if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
		jet++;
		}


	//########====--- LOCATE VEHICLE ---====########

	//##### Vehicle Posing

	//### Calculate Vehicle Pose Counters

	//## Calc Wheel Rotation
	player[g_Player]->Vehicle.FWheelSpinPoseCnt += player[g_Player]->Vehicle.Phys_Velocity / 200;
	while(player[g_Player]->Vehicle.FWheelSpinPoseCnt > 0.67)
		{
		player[g_Player]->Vehicle.FWheelSpinPoseCnt = player[g_Player]->Vehicle.FWheelSpinPoseCnt - 0.67;
		}

	if(player[g_Player]->Vehicle.Phys_FrictionAMT == 1)
		{ player[g_Player]->Vehicle.RWheelSpinPoseCnt += player[g_Player]->Vehicle.Phys_Velocity / 200; }
	else { player[g_Player]->Vehicle.RWheelSpinPoseCnt += player[g_Player]->Vehicle.Phys_Power / 75; }

	while(player[g_Player]->Vehicle.RWheelSpinPoseCnt > 0.67)
		{
		player[g_Player]->Vehicle.RWheelSpinPoseCnt = player[g_Player]->Vehicle.RWheelSpinPoseCnt - 0.67;
		}

	Qpo->Avatar_ClearPose(player[g_Player]->Vehicle.Model.Avatar, &player[g_Player]->Vehicle.Model.Xform);
	Qpo->Avatar_SetScale(&player[g_Player]->Vehicle.Model.Avatar, 1.2f,1.2f,1.2f);

	//## Set Wheel Turn
	Qpo->Avatar_SetPosePM(player[g_Player]->Vehicle.Model.Avatar, player[g_Player]->Vehicle.Model.Motion[3], player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt, NULL);

	//## Set Wheel Scale
	Qpo->Avatar_SetPosePM(player[g_Player]->Vehicle.Model.Avatar, player[g_Player]->Vehicle.Model.Motion[1], player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt, NULL);
	Qpo->Avatar_SetPosePM(player[g_Player]->Vehicle.Model.Avatar, player[g_Player]->Vehicle.Model.Motion[4], player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt, NULL);

	//## Set Wheel Rotation
	Qpo->Avatar_SetPosePM(player[g_Player]->Vehicle.Model.Avatar, player[g_Player]->Vehicle.Model.Motion[0], player[g_Player]->Vehicle.RWheelSpinPoseCnt, NULL);
	Qpo->Avatar_SetPosePM(player[g_Player]->Vehicle.Model.Avatar, player[g_Player]->Vehicle.Model.Motion[2], player[g_Player]->Vehicle.FWheelSpinPoseCnt, NULL);

	//NEW WHEEL POSITIONS
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE08", &player[g_Player]->Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE05", &player[g_Player]->Vehicle.RWheelMatrix);


	//####### Apply Vehicle Gravity
	if(player[g_Player]->Vehicle.Phys_FWheelTOUCH == 0 || player[g_Player]->Vehicle.Phys_RWheelTOUCH == 0 /*&& KEY_PRESS_DOWN(QIN_TAB)*/)
		{
		player[g_Player]->Vehicle.Phys_DownVelocity -= (((0.5 * (( player[g_Player]->Vehicle.Const_FWeight + player[g_Player]->Vehicle.Const_RWeight) / 1.5)) / player[g_Player]->Vehicle.GravityAlter) * _->TimeScale);
		}
	else
		{
		player[g_Player]->Vehicle.Phys_DownVelocity = 0;
		}


	//###### COLLISION DETECTION INITIAL
	player[g_Player]->Vehicle.Model.OldPos = playerAV[g_Player]->Xform.Translation;
	player[g_Player]->Vehicle.Model.NewPos = playerAV[g_Player]->Xform.Translation;

	player[g_Player]->Vehicle.Model.OldPos.y += 50;
	player[g_Player]->Vehicle.Model.NewPos.y += 50;

	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.NewPos, -60, &player[g_Player]->Vehicle.Phys_ForwardMotionVec, &player[g_Player]->Vehicle.Model.NewPos);
																									//EDIT Removed Collision detection with actors
	if(Qpo->Collision_RayTest(NULL, NULL, &player[g_Player]->Vehicle.Model.OldPos, &player[g_Player]->Vehicle.Model.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &playerAV[g_Player]->Collision))
		{
		QpoVec3d f_ImpactVector(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
		player[g_Player]->Vehicle.CollCRUNCH = Qpo->Vec3d_DistanceBetween(&f_ImpactVector, &player[g_Player]->Vehicle.Model.NewPos);

		Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.NewPos, player[g_Player]->Vehicle.CollCRUNCH, &playerAV[g_Player]->Collision.Plane.Normal, &player[g_Player]->Vehicle.Model.NewPos);
		Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.Model.NewPos, 60, &player[g_Player]->Vehicle.Phys_ForwardMotionVec, &player[g_Player]->Vehicle.Model.NewPos);

		if(player[g_Player]->Vehicle.CollCRUNCH > 20) player[g_Player]->Vehicle.RapidDismount = 1;

		player[g_Player]->Vehicle.Model.NewPos.y -= 50;

		playerAV[g_Player]->Xform.Translation = player[g_Player]->Vehicle.Model.NewPos;
		}


	//#### Replace New Positions
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelNEWPOS, -player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.FWheelNEWPOS);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.RWheelNEWPOS, -player[g_Player]->Vehicle.Const_SpringLimit, &player[g_Player]->Vehicle.Down, &player[g_Player]->Vehicle.RWheelNEWPOS);

	//if(player[g_Player]->Vehicle.Phys_FWheelTOUCH == 1 && player[g_Player]->Vehicle.Phys_RWheelTOUCH == 1 )
	//	{
	//#### BUILD OLD PERFECT POSITIONS
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelPOSSTR, (1 - (player[g_Player]->Vehicle.STR_Phys_FWheelBendPoseCnt / 0.67)) - 0.5, &player[g_Player]->Vehicle.ConstVec_FCrunch, &player[g_Player]->Vehicle.FWheelOLDPERFECTPOS);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.RWheelPOSSTR, (1 - (player[g_Player]->Vehicle.STR_Phys_RWheelBendPoseCnt / 0.67)) - 0.5, &player[g_Player]->Vehicle.ConstVec_RCrunch, &player[g_Player]->Vehicle.RWheelOLDPERFECTPOS);

	//#### BUILD NEW PERFECT POSITIONS
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.FWheelNEWPOS, (1 - (player[g_Player]->Vehicle.Phys_FWheelBendPoseCnt / 0.67)) - 0.5, &player[g_Player]->Vehicle.ConstVec_FCrunch, &player[g_Player]->Vehicle.FWheelPERFECTPOS);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.RWheelNEWPOS, (1 - (player[g_Player]->Vehicle.Phys_RWheelBendPoseCnt / 0.67)) - 0.5, &player[g_Player]->Vehicle.ConstVec_RCrunch, &player[g_Player]->Vehicle.RWheelPERFECTPOS);

	//#### FIND VEHICLE CENTER
	player[g_Player]->Vehicle.CENTRALANGLEVEC = playerAV[g_Player]->Xform.Translation;
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.CENTRALANGLEVEC, &player[g_Player]->Vehicle.RotatePNTVEC, &player[g_Player]->Vehicle.CENTRALANGLEVEC);

	Qpo->Vec3d_Subtract(&player[g_Player]->Vehicle.FWheelPERFECTPOS, &player[g_Player]->Vehicle.RWheelPERFECTPOS, &player[g_Player]->Vehicle.NEWVehicleUP);
	Qpo->Vec3d_Subtract(&player[g_Player]->Vehicle.FWheelOLDPERFECTPOS, &player[g_Player]->Vehicle.RWheelOLDPERFECTPOS, &player[g_Player]->Vehicle.OLDVehicleUP);
	Qpo->Vec3d_Inverse(&player[g_Player]->Vehicle.NEWVehicleUP);
	Qpo->Vec3d_Inverse(&player[g_Player]->Vehicle.OLDVehicleUP);
	Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.NEWVehicleUP);
	Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.OLDVehicleUP);

	//#### BUILD WANTED ROTATION VECTORS
	Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->Vehicle.Model.Up);
	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &player[g_Player]->Vehicle.Model.Left);


	//#### FIND true LIFT INCREMENT
	Qpo->Transform_New(&player[g_Player]->Vehicle.VehicMatrix);

	Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.VehicMatrix, player[g_Player]->Vehicle.Phys_TurnLean);

	Qpo->Transform_New_YRotation(&player[g_Player]->Vehicle.RotateMatrix, player[g_Player]->Vehicle.Angles.y);
	Qpo->Transform_Multiply(&player[g_Player]->Vehicle.RotateMatrix, &player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.VehicMatrix);

	Qpo->Transform_GetLeft(&player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.Model.Left);

	//## SET INTERSECT LINES
	player[g_Player]->Vehicle.CalcLINEP1 = player[g_Player]->Vehicle.OLDVehicleUP;
	player[g_Player]->Vehicle.CalcLINEP2 = player[g_Player]->Vehicle.OLDVehicleUP;
	player[g_Player]->Vehicle.CalcLINEP3 = player[g_Player]->Vehicle.NEWVehicleUP;
	player[g_Player]->Vehicle.CalcLINEP4 = player[g_Player]->Vehicle.NEWVehicleUP;

	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.CalcLINEP1, -50, &player[g_Player]->Vehicle.Model.Left, &player[g_Player]->Vehicle.CalcLINEP1);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.CalcLINEP2, 50, &player[g_Player]->Vehicle.Model.Left, &player[g_Player]->Vehicle.CalcLINEP2);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.CalcLINEP3, -0.01, &player[g_Player]->Vehicle.NEWVehicleUP, &player[g_Player]->Vehicle.CalcLINEP3);

	Tempint1 = Q.Q_LineLineintersect(player[g_Player]->Vehicle.CalcLINEP1, player[g_Player]->Vehicle.CalcLINEP2, player[g_Player]->Vehicle.CalcLINEP3, player[g_Player]->Vehicle.CalcLINEP4, &player[g_Player]->Vehicle.CalcRESA, &player[g_Player]->Vehicle.CalcRESB);

	//Qpo->Vec3d_Subtract(&player[g_Player]->Vehicle.NEWVehicleUP, &player[g_Player]->Vehicle.CalcRESA, &player[g_Player]->Vehicle.VehicleRUDDERINC);
	Qpo->Vec3d_Subtract(&player[g_Player]->Vehicle.NEWVehicleUP, &player[g_Player]->Vehicle.OLDVehicleUP, &player[g_Player]->Vehicle.VehicleRUDDERINC);

	player[g_Player]->Vehicle.VehicleRUDDERINC.x = 0;
	player[g_Player]->Vehicle.VehicleRUDDERINC.z = 0;


	/*Qpo->Transform_GetUp(&player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.Model.Left);

	//## SET INTERSECT LINES
	player[g_Player]->Vehicle.CalcLINEP1 = player[g_Player]->Vehicle.NEWVehicleUP;
	player[g_Player]->Vehicle.CalcLINEP2 = player[g_Player]->Vehicle.NEWVehicleUP;
	player[g_Player]->Vehicle.CalcLINEP3 = player[g_Player]->Vehicle.OLDVehicleUP;
	player[g_Player]->Vehicle.CalcLINEP4 = player[g_Player]->Vehicle.OLDVehicleUP;

	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.CalcLINEP1, -5, &player[g_Player]->Vehicle.Model.Left, &player[g_Player]->Vehicle.CalcLINEP1);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.CalcLINEP2, 5, &player[g_Player]->Vehicle.Model.Left, &player[g_Player]->Vehicle.CalcLINEP2);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.CalcLINEP3, -0.01, &player[g_Player]->Vehicle.OLDVehicleUP, &player[g_Player]->Vehicle.CalcLINEP3);

	Tempint1 = Q.Q_LineLineintersect(player[g_Player]->Vehicle.CalcLINEP1, player[g_Player]->Vehicle.CalcLINEP2, player[g_Player]->Vehicle.CalcLINEP3, player[g_Player]->Vehicle.CalcLINEP4, &player[g_Player]->Vehicle.CalcRESA, &player[g_Player]->Vehicle.CalcRESB);

	Qpo->Vec3d_Subtract(&player[g_Player]->Vehicle.NEWVehicleUP, &player[g_Player]->Vehicle.CalcRESA, &player[g_Player]->Vehicle.VehicleRUDDERINC);*/


	//#### PREPARE VEHICLE MATRIX POSITION
	Qpo->Transform_New(&player[g_Player]->Vehicle.VehicMatrix);
	player[g_Player]->Vehicle.VehicMatrix.Translation = playerAV[g_Player]->Xform.Translation;


	//#### RESET AND BUILD PLAYACT MATRIX
	Qpo->Transform_New(&playerAV[g_Player]->Xform);
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, -(PI/2));
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, PI);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, player[g_Player]->Vehicle.Phys_TurnLean);
	Qpo->Transform_New_YRotation(&player[g_Player]->Vehicle.RotateMatrix, player[g_Player]->Vehicle.Angles.y);
	Qpo->Transform_Multiply(&player[g_Player]->Vehicle.RotateMatrix, &playerAV[g_Player]->Xform, &playerAV[g_Player]->Xform);

	//#### FIND MOVE BACK VECTOR
	Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Origin, &player[g_Player]->Vehicle.RotatePNTVEC);
	playerAV[g_Player]->Xform.Translation = player[g_Player]->Vehicle.VehicMatrix.Translation;
	Qpo->Vec3d_Add(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Vehicle.RotatePNTVEC, &playerAV[g_Player]->Xform.Translation);
	Qpo->Vec3d_Inverse(&player[g_Player]->Vehicle.RotatePNTVEC);


	//#### ADDAGE OF LIFT INCREMENT
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.VehicleIMAGETORUDDERVECSTR, &player[g_Player]->Vehicle.VehicleRUDDERINC, &player[g_Player]->Vehicle.VehicleIMAGETORUDDERVECSTR);

	//######-- ROTATE IMAGE TO RUDDER VECTOR --########
	Qpo->Transform_New(&player[g_Player]->Vehicle.VehicMatrix);

	/*Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.VehicMatrix, player[g_Player]->Vehicle.Phys_TurnLean - player[g_Player]->Vehicle.Phys_TurnLeanSTR);

	Qpo->Transform_New_YRotation(&player[g_Player]->Vehicle.RotateMatrix, player[g_Player]->Vehicle.Angles.y - player[g_Player]->Vehicle.AnglesSTR.y);
	Qpo->Transform_Multiply(&player[g_Player]->Vehicle.RotateMatrix, &player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.VehicMatrix);*/

	Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.VehicMatrix, player[g_Player]->Vehicle.Phys_TurnLean);

	Qpo->Transform_New_YRotation(&player[g_Player]->Vehicle.RotateMatrix, player[g_Player]->Vehicle.Angles.y);
	Qpo->Transform_Multiply(&player[g_Player]->Vehicle.RotateMatrix, &player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.VehicMatrix);

	Qpo->Transform_RotateVector(&player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.VehicleIMAGETORUDDERVECSTR, &player[g_Player]->Vehicle.VehicleIMAGETORUDDERVEC);

	//#### STORE ANGLES AND LEAN
	player[g_Player]->Vehicle.Phys_TurnLeanSTR = player[g_Player]->Vehicle.Phys_TurnLean;
	player[g_Player]->Vehicle.AnglesSTR.y = player[g_Player]->Vehicle.Angles.y;

	//#### ADDAGE OF LIFT INCREMENT
	//Qpo->Vec3d_Add(&player[g_Player]->Vehicle.VehicleIMAGETORUDDERVEC, &player[g_Player]->Vehicle.VehicleRUDDERINC, &player[g_Player]->Vehicle.VehicleIMAGETORUDDERVEC);


	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->Vehicle.STRVehicleUP);
	Qpo->Vec3d_Add(&player[g_Player]->Vehicle.STRVehicleUP, &player[g_Player]->Vehicle.VehicleIMAGETORUDDERVEC, &player[g_Player]->Vehicle.STRVehicleUP);
	Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.STRVehicleUP);

	//Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &player[g_Player]->Vehicle.VehicleGETIN);
	//player[g_Player]->Vehicle.NEWVehicleUP = player[g_Player]->Vehicle.VehicleGETIN;

	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &player[g_Player]->Vehicle.NEWVehicleLEFT);

	//Qpo->Vec3d_Inverse(&player[g_Player]->Vehicle.NEWVehicleLEFT);
	Qpo->Vec3d_CrossProduct(&player[g_Player]->Vehicle.STRVehicleUP, &player[g_Player]->Vehicle.NEWVehicleLEFT, &player[g_Player]->Vehicle.NEWVehicleIN);
	Qpo->Vec3d_Inverse(&player[g_Player]->Vehicle.NEWVehicleIN);
	Qpo->Vec3d_Normalize(&player[g_Player]->Vehicle.NEWVehicleIN);

	//Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.STRVehicleUP, player[g_Player]->Vehicle.Const_MiddleCOGDISTX/5, &player[g_Player]->Vehicle.NEWVehicleIN, &player[g_Player]->Vehicle.STRVehicleUP);

	Qpo->Transform_New(&player[g_Player]->Vehicle.VehicMatrix);
	Qpo->Transform_New_LeftUpIn(&player[g_Player]->Vehicle.VehicMatrix, &player[g_Player]->Vehicle.NEWVehicleLEFT, &player[g_Player]->Vehicle.STRVehicleUP, &player[g_Player]->Vehicle.NEWVehicleIN);
	Qpo->Transform_Orthonormalize(&player[g_Player]->Vehicle.VehicMatrix);

	player[g_Player]->Vehicle.VehicMatrix.Translation = playerAV[g_Player]->Xform.Translation;
	playerAV[g_Player]->Xform = player[g_Player]->Vehicle.VehicMatrix;
	playerAV[g_Player]->Xform.Translation = player[g_Player]->Vehicle.VehicMatrix.Translation;

	//##### SET WHEELS TO NEW WHEEL POSITIONS
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE08", &player[g_Player]->Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE05", &player[g_Player]->Vehicle.RWheelMatrix);

	player[g_Player]->Vehicle.JDISTF = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Vehicle.FWheelNEWPOS, &player[g_Player]->Vehicle.FWheelPOSSTR);
	player[g_Player]->Vehicle.JDISTR = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Vehicle.RWheelNEWPOS, &player[g_Player]->Vehicle.RWheelPOSSTR);

	if(player[g_Player]->Vehicle.JDISTF > player[g_Player]->Vehicle.JDISTR || player[g_Player]->Vehicle.Phys_TurnMotionAMT > 0)
		{
		Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Vehicle.RWheelMatrix.Translation, &player[g_Player]->Vehicle.ToBASEPNTVEC);
		Qpo->Vec3d_Add(&player[g_Player]->Vehicle.RWheelNEWPOS, &player[g_Player]->Vehicle.ToBASEPNTVEC, &playerAV[g_Player]->Xform.Translation);
		}
	else
		{
		Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->Vehicle.FWheelMatrix.Translation, &player[g_Player]->Vehicle.ToBASEPNTVEC);
		Qpo->Vec3d_Add(&player[g_Player]->Vehicle.FWheelNEWPOS, &player[g_Player]->Vehicle.ToBASEPNTVEC, &playerAV[g_Player]->Xform.Translation);
		}


	//####### Vehicle Rotation

		//### Calc Horizontal Turn Angles
	player[g_Player]->Vehicle.Phys_Turn = player[g_Player]->Vehicle.Phys_FWheelTurnPoseCnt - 0.335;

	if(player[g_Player]->Vehicle.Phys_Velocity > 1.4)	//### In Motion
		{
		player[g_Player]->Vehicle.Phys_TurnLean = player[g_Player]->Vehicle.Phys_Turn * player[g_Player]->Vehicle.Phys_TurnMULT;	//3.6
		player[g_Player]->Vehicle.Angles.y += player[g_Player]->Vehicle.Phys_Turn / ((8 / player[g_Player]->Vehicle.Phys_TurnMULT)*1.35);
		}
	else	//### Still
		{
		player[g_Player]->Vehicle.Phys_TurnLean = (player[g_Player]->Vehicle.Phys_Turn - 0.1) * player[g_Player]->Vehicle.Phys_TurnMULT;	//1.35
		player[g_Player]->Vehicle.Angles.y += player[g_Player]->Vehicle.Phys_Turn / ((8 / player[g_Player]->Vehicle.Phys_TurnMULT)*1.35);	//4
		}


	TempVec1 = playerAV[g_Player]->Xform.Translation;
	TempVec1.y += 45;
	Qpo->Vec3d_AddScaled(&TempVec1, 60, &player[g_Player]->Vehicle.Phys_ForwardMotionVec, &TempVec1);


	//- END MotorCycle Physics -


	//####### VehicleMount and Idle #####
	
	if(player[g_Player]->WeaponStatus == 0 || 1)	//Idle Motion
		{
		//######- Vehicle In Motion -######

		if(player[g_Player]->Vehicle.Phys_Velocity > 1.4)
			{
			//## 'Standard Ride' and 'Bike Mount'
			if(player[g_Player]->Mposestate == 0)
				{
				Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 110, player[g_Player]->idleposecnt, &playerAV[g_Player]->Xform, 1);
			
				if(player[g_Player]->idleposecnt+(0.02*_->TimeScale)<0.335) player[g_Player]->idleposecnt += 0.02*_->TimeScale;		// < 0.67
				else player[g_Player]->idleposecnt=0.335;
				}

			//## 'Rush Ride'
			if(player[g_Player]->Mposestate == 1)
				{
				Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 111, player[g_Player]->idleposecnt, &playerAV[g_Player]->Xform, 1);
			
				if(player[g_Player]->idleposecnt+(0.04*_->TimeScale) < 0.4) player[g_Player]->idleposecnt += 0.04*_->TimeScale;
				else player[g_Player]->idleposecnt=0.27;
				}

			//## 'Wheelie Ride'
			if(player[g_Player]->Mposestate == 2)
				{
				Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 112, player[g_Player]->idleposecnt, &playerAV[g_Player]->Xform, 1);
			
				if(player[g_Player]->idleposecnt+(0.03*_->TimeScale) < 0.335) player[g_Player]->idleposecnt += 0.03*_->TimeScale;
				else player[g_Player]->idleposecnt=0.335;
				}

			//# Reset Idle Pose
			player[g_Player]->blendamount[113] = 0;
			}
		else	//######- Vehicle Stopped -######
			{
			Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 113, player[g_Player]->idleposecnt, &playerAV[g_Player]->Xform, 1);
			
			if(player[g_Player]->idleposecnt+(0.03*_->TimeScale) < 0.335) player[g_Player]->idleposecnt += 0.03*_->TimeScale;
			else player[g_Player]->idleposecnt=0.335;
			}
		}


	//### - Player Attachingness
	if(player[g_Player]->VehicleAttach == 0)
		{	//SUSPEND
		if(1/*player[g_Player]->idleposecnt > 0.15*/)
			{
			player[g_Player]->VehicleAttach = 1;

			Qpo->Vec3d_Copy(&player[g_Player]->Vehicle.Model.Xform.Translation, &playerAV[g_Player]->Xform.Translation);
			playerAV[g_Player]->Xform.Translation.y -= 30;

			Qpo->Avatar_BlendPose(playerAV[g_Player]->Avatar, 110, player[g_Player]->idleposecnt, &playerAV[g_Player]->Xform, 1);

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01", &player[g_Player]->Vehicle.AttachMat);
			Qpo->Transform_SetTranslation(&player[g_Player]->Vehicle.AttachMat, 0, 0, 0);

			player[g_Player]->Vehicle.AttachMat.Translation.x += -33.850327;
			player[g_Player]->Vehicle.AttachMat.Translation.y += 22.530058;
			player[g_Player]->Vehicle.AttachMat.Translation.z += 0;
			Qpo->Transform_RotateX(&player[g_Player]->Vehicle.AttachMat, 1.570797);
			Qpo->Transform_RotateY(&player[g_Player]->Vehicle.AttachMat, 2.809998);
			Qpo->Transform_RotateZ(&player[g_Player]->Vehicle.AttachMat, 0);

			//~##~Qpo->Avatar_Attach(&player[g_Player]->Vehicle.Model.Avatar, "BONE01", &playerAV[g_Player]->Avatar, "BIP01", &player[g_Player]->Vehicle.AttachMat);
			}
		}


	//### Init Head Lights
	if(player[g_Player]->Vehicle.HeadLightInit == 0)
		{
		player[g_Player]->Vehicle.HeadLightInit = 1;

		player[g_Player]->Vehicle.HeadLight = Qpo->Light_AddtoWorld(_->GenericLightPos);
		player[g_Player]->Vehicle.HeadLightEnd = Qpo->Light_AddtoWorld(_->GenericLightPos);
		player[g_Player]->Vehicle.NeonLight1 = Qpo->Light_AddtoWorld(_->GenericLightPos);

		player[g_Player]->Vehicle.HeadLColor.red = 255;
		player[g_Player]->Vehicle.HeadLColor.green = 255;
		player[g_Player]->Vehicle.HeadLColor.blue = 210;

		player[g_Player]->Vehicle.NeonLColor1.red = 255;
		player[g_Player]->Vehicle.NeonLColor1.green = 855;
		player[g_Player]->Vehicle.NeonLColor1.blue = 255;

		player[g_Player]->Vehicle.HeadLPower = 950;
		player[g_Player]->Vehicle.NeonLPower1 = 235;
		}


	//### Set Light Positions
	Qpo->Avatar_GetBoneTransform(&player[g_Player]->Vehicle.Model, "BONE01", &player[g_Player]->Vehicle.HeadLMat);

	player[g_Player]->Vehicle.HeadLPos = player[g_Player]->Vehicle.HeadLMat.Translation;
	player[g_Player]->Vehicle.NeonLPos1 = player[g_Player]->Vehicle.HeadLMat.Translation;

	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.HeadLPos, -35, &player[g_Player]->Vehicle.Model.Up, &player[g_Player]->Vehicle.HeadLPos);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.HeadLPos, -25, &player[g_Player]->Vehicle.Model.In, &player[g_Player]->Vehicle.HeadLPos);

	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.NeonLPos1, 10, &player[g_Player]->Vehicle.Model.Up, &player[g_Player]->Vehicle.NeonLPos1);
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.NeonLPos1, 15, &player[g_Player]->Vehicle.Model.In, &player[g_Player]->Vehicle.NeonLPos1);


	//### Extend Light Out
	Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.HeadLPos, -5000, &player[g_Player]->Vehicle.Model.Up, &player[g_Player]->Vehicle.HeadLENDPos);

	if(Qpo->Collision_RayTest(NULL,NULL, &player[g_Player]->Vehicle.HeadLPos, &player[g_Player]->Vehicle.HeadLENDPos, /*GE_CONTENTS_CANNOT_OCCUPY/* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &player[g_Player]->Vehicle.HeadLCollision))
		{
		QpoVec3d f_ImpactVector(player[g_Player]->Vehicle.HeadLCollision.Impact.m_X, player[g_Player]->Vehicle.HeadLCollision.Impact.m_Y, player[g_Player]->Vehicle.HeadLCollision.Impact.m_Z);
		player[g_Player]->Vehicle.HeadLENDPos = f_ImpactVector;
		Qpo->Vec3d_AddScaled(&player[g_Player]->Vehicle.HeadLENDPos, 50, &player[g_Player]->Vehicle.Model.Up, &player[g_Player]->Vehicle.HeadLENDPos);
		}


	//### Set Head Light Attribs
	Qpo->Light_SetAttr(player[g_Player]->Vehicle.HeadLight, &player[g_Player]->Vehicle.HeadLPos, &player[g_Player]->Vehicle.HeadLColor, player[g_Player]->Vehicle.HeadLPower/10, true);
	Qpo->Light_SetAttr(player[g_Player]->Vehicle.HeadLightEnd, &player[g_Player]->Vehicle.HeadLENDPos, &player[g_Player]->Vehicle.HeadLColor, player[g_Player]->Vehicle.HeadLPower, true);
	Qpo->Light_SetAttr(player[g_Player]->Vehicle.NeonLight1, &player[g_Player]->Vehicle.NeonLPos1, &player[g_Player]->Vehicle.NeonLColor1, player[g_Player]->Vehicle.NeonLPower1/3, true);


		//### DisMount
	if(KEY_PRESS_DOWN(QIN_SPACE) || player[g_Player]->attackon != 0 || player[g_Player]->Vehicle.RapidDismount == 1)
		{
		player[g_Player]->Vehicle.RapidDismount = 0;
		player[g_Player]->PlayerMode = 0;
		player[g_Player]->VehicleAttach = 0;
		Qpo->Avatar_Detach(&player[g_Player]->Vehicle.Model.Avatar);

		player[g_Player]->Vehicle.VehicMatrix.Translation = playerAV[g_Player]->Xform.Translation;

		player[g_Player]->ROTATEMatrix = player[g_Player]->STOREMatrix;
		Qpo->Transform_RotateY(&player[g_Player]->ROTATEMatrix, player[g_Player]->Angles.y);
		playerAV[g_Player]->Xform = player[g_Player]->ROTATEMatrix;
		playerAV[g_Player]->Xform.Translation = player[g_Player]->Vehicle.VehicMatrix.Translation;

		//#### Position vehicle
		Qpo->Transform_New(&player[g_Player]->Vehicle.Model.Xform);
		Qpo->Transform_New_LeftUpIn(&player[g_Player]->Vehicle.Model.Xform, &player[g_Player]->Vehicle.NEWVehicleLEFT, &player[g_Player]->Vehicle.STRVehicleUP, &player[g_Player]->Vehicle.NEWVehicleIN);
		Qpo->Transform_Orthonormalize(&player[g_Player]->Vehicle.Model.Xform);

		player[g_Player]->Vehicle.Model.Xform.Translation = player[g_Player]->Vehicle.VehicMatrix.Translation;
		player[g_Player]->Vehicle.Model.Xform.Translation.y += 27;

		//#### Player Hit reactions
		Qpo->Vec3d_Inverse(&player[g_Player]->Vehicle.Phys_ForwardMotionVec);
		player[g_Player]->MoveReactVec = player[g_Player]->Vehicle.Phys_ForwardMotionVec;
		player[g_Player]->MoveReactSpeed = (player[g_Player]->Vehicle.Phys_Velocity * _->TimeScale) / 2;

		//#### Player Hit reactions
		player[g_Player]->Vehicle.MoveReactVec = player[g_Player]->Vehicle.Phys_ForwardMotionVec;
		player[g_Player]->Vehicle.MoveReactSpeed = player[g_Player]->Vehicle.Phys_Velocity;
		}


	//##### Vehicle Weapon Usuage
	if(player[g_Player]->Aposestate == 20 || (player[g_Player]->WeaponStatus != 0 && player[g_Player]->attackon == 0))	//Weapon1
		{
		player[g_Player]->wepposecnt = player[g_Player]->attposecnt;	//Switch to wepposecnt if needed

		if(player[g_Player]->WeaponStatus == 1)	//Draw Weapon
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], player[g_Player]->attposecnt, NULL);
				}

			if(player[g_Player]->attposecnt >= 0.30) player[g_Player]->Backpack.Draw = 1;

			if(player[g_Player]->attposecnt + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness *(0.1*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75)) < 0.38) player[g_Player]->attposecnt += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness * 0.1*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75);	//0.05
			else
				{
				player[g_Player]->attposecnt = 0.38;
				player[g_Player]->WeaponStatus = 2;
				player[g_Player]->WeaponATTACHFLAG = 1;

				Qpo->Vec3d_Copy(&player[g_Player]->OAttPos.Translation, &player[g_Player]->Weapon.Xform.Translation);

				player[g_Player]->WepAttach = player[g_Player]->Weapon.Xform;
				Qpo->Transform_SetTranslation(&player[g_Player]->WepAttach, 0, 0, 0);

				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3)
					{
					player[g_Player]->WepAttach.Translation.x -= 9;
					player[g_Player]->WepAttach.Translation.y -= 4.6;
					player[g_Player]->WepAttach.Translation.z -= 1;

					Qpo->Transform_RotateX(&player[g_Player]->WepAttach, PI/2);
					Qpo->Transform_RotateY(&player[g_Player]->WepAttach, -(PI/4)-0.8);
					}

				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
					{
					player[g_Player]->WepAttach.Translation.x -= 9;
					player[g_Player]->WepAttach.Translation.y -= 4.6;
					player[g_Player]->WepAttach.Translation.z -= 1;

					//Qpo->Transform_RotateX(&player[g_Player]->WepAttach, PI/2);
					Qpo->Transform_RotateY(&player[g_Player]->WepAttach, -(PI/4)-0.8);
					}


				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF != 4 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF != 3)
					{
					player[g_Player]->WepAttach.Translation.x -= 0.5;
					player[g_Player]->WepAttach.Translation.y -= 3;
					player[g_Player]->WepAttach.Translation.z -= 1;

					Qpo->Transform_RotateX(&player[g_Player]->WepAttach, PI/2);
					Qpo->Transform_RotateY(&player[g_Player]->WepAttach, -(PI/4)-0.35);
					}

				////~##~Qpo->Avatar_Attach(&player[g_Player]->Weapon.Avatar, "BONE01", &playerAV[g_Player]->Avatar, "BIP01 R HAND", &player[g_Player]->WepAttach);
				}

			if(player[g_Player]->blendamount[25]+ (0.5*_->TimeScale) <=1) player[g_Player]->blendamount[25] += 0.5*_->TimeScale;
			}


		if(player[g_Player]->WeaponStatus == 2)	//Draw Weapon Part Two
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], player[g_Player]->attposecnt, NULL);
				}

			if(player[g_Player]->attposecnt + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness *(0.08*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75)) <= 1.0) player[g_Player]->attposecnt += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness * 0.08*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75);	//0.02
			else
				{
				player[g_Player]->WepAlpha = 255;
				player[g_Player]->attposecnt = 1.0;
				player[g_Player]->WeaponStatus = 3;
				}

			if(player[g_Player]->WepAlpha+40 <= 255) player[g_Player]->WepAlpha += 40;
			else player[g_Player]->WepAlpha = 255;

			Qpo->Mesh_SetAlpha(&player[g_Player]->Weapon, player[g_Player]->WepAlpha);
			}


		if(player[g_Player]->WeaponStatus == 3)	//Weapon On Shoulder
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], player[g_Player]->attposecnt, NULL);
				}

			if(_->lbutton[g_Player] == 1 && _->NetworkOption != 1)
				{
				player[g_Player]->WeaponStatus = 4;
				player[g_Player]->WepAlpha = 0;
				}

			if((KEY_PRESS_DOWN(QIN_TAB)) && _->NetworkOption != 1)
				{
				player[g_Player]->attposecnt = 1.0;
				player[g_Player]->WeaponStatus = 7;
				player[g_Player]->blendamount[25] = 0;
				}

			if(player[g_Player]->blendamount[25]+ (0.3*_->TimeScale) <=1) player[g_Player]->blendamount[25] += 0.3*_->TimeScale;
			}


		if(player[g_Player]->WeaponStatus == 4)	//Aim Weapon
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], player[g_Player]->attposecnt, NULL);
				}

			if(player[g_Player]->attposecnt + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness *(0.15*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75)) <= 2.27) player[g_Player]->attposecnt += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness * 0.15*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75);	//0.12	//0.08
			else
				{
				player[g_Player]->attposecnt = 2.27;
				player[g_Player]->WepIdle = 0;
				player[g_Player]->WeaponStatus = 5;
				player[g_Player]->blendamount[25]=0;
				player[g_Player]->WeaponFire = 0;
				}

			if(player[g_Player]->WepAlpha+5 <= 150) player[g_Player]->WepAlpha += 5;
			else player[g_Player]->WepAlpha = 95;		//Laser sight alpha value
			}


		if(player[g_Player]->WeaponStatus == 5)	//Fire Weapon
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[136], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[35], player[g_Player]->attposecnt, NULL);
				}

			Qpo->Transform_GetIn(&player[g_Player]->ViewXForm, &player[g_Player]->In);

			if(player[g_Player]->WeaponZoomFACT == 0)
				{
				if(!KEY_PRESS_DOWN(QIN_r)) player[g_Player]->attposecnt = ((player[g_Player]->In.y*-1.6)+0.4)-player[g_Player]->WeaponRecoil;
				}
			else
				{
				if(!KEY_PRESS_DOWN(QIN_r)) player[g_Player]->attposecnt = ((player[g_Player]->Angles.x*-1.6)+0.4)-player[g_Player]->WeaponRecoil;
				}

							//    V---  Adjust fire rate here	2 is FIRE , NOT , FIRE
			if(player[g_Player]->FireRate >= (1 - ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].FireRate / 5000)) * 36) player[g_Player]->FireRate = 0;
			else if(player[g_Player]->FireRate > 0) player[g_Player]->FireRate += 1 * _->TimeScale;

			if(((!(_->lbutton[g_Player]) && player[g_Player]->WeaponFire == 0) || _->NetworkOption == 1) /*|| (_->NetworkOption == 1*/) player[g_Player]->WepIdle++;
			else
				{
				player[g_Player]->WeaponFire = 0;
				player[g_Player]->WepIdle = 0;

				if(player[g_Player]->FireRate == 0)	//FIRE!
					{
					player[g_Player]->FireRate = 1;

					if(_->NetworkOption != 1)
						{
						player[g_Player]->MFlash = 1;
						player[g_Player]->NETMFlash = 1;
						}

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &player[g_Player]->OAttPos);
					player[g_Player]->OAttPos.Translation.z -= 0.2;	//6
					player[g_Player]->OAttPos.Translation.y -= 0.133;	//4
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &player[g_Player]->OAttPos);

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &player[g_Player]->OAttPos);
					player[g_Player]->OAttPos.Translation.z -= 0.2;
					player[g_Player]->OAttPos.Translation.y -= 0.133;
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &player[g_Player]->OAttPos);

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &player[g_Player]->OAttPos);
					player[g_Player]->OAttPos.Translation.z -= 0.2;
					player[g_Player]->OAttPos.Translation.y -= 0.133;
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &player[g_Player]->OAttPos);

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &player[g_Player]->OAttPos);
					player[g_Player]->OAttPos.Translation.z -= 0.2;
					player[g_Player]->OAttPos.Translation.y -= 0.133;
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &player[g_Player]->OAttPos);

					//Qpo->Avatar_GetJointTransform(player[g_Player]->Weapon.Avatar.Pose, 0, &player[g_Player]->AttPos);
					//player[g_Player]->OAttPos.Translation.z -= 0.2;
					//player[g_Player]->OAttPos.Translation.y -= 0.133;
					//Qpo->Avatar_SetJointTransform(player[g_Player]->Weapon.Avatar.Pose, 0, &player[g_Player]->OAttPos);

					//# Recoil
					if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
						{
						player[g_Player]->WeaponRecoil += 0.1 * ( (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].RecoilHeight / 5000) * 2) / 2);
						player[g_Player]->WeaponRecoil -= (player[g_Player]->WeaponRecoil * player[g_Player]->WeaponRecoil) * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover/2500)+0.1);
						if(player[g_Player]->WeaponRecoil < 0) player[g_Player]->WeaponRecoil = 0;
						}
					else
						{
						player[g_Player]->WeaponRecoil += 0.3 * ( (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].RecoilHeight / 5000) * 2) / 2);
						player[g_Player]->WeaponRecoil -= (player[g_Player]->WeaponRecoil * player[g_Player]->WeaponRecoil) * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover/2500)+0.1);
						if(player[g_Player]->WeaponRecoil < 0) player[g_Player]->WeaponRecoil = 0;
						//IMP ADDED STATEMENT
						}

					//### Movement Recoil
					//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->TempXForm1);
					Qpo->Transform_GetLeft(&player[g_Player]->TempXForm1, &player[g_Player]->In);

					player[g_Player]->MoveReactVec = player[g_Player]->In;
					if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
					player[g_Player]->MoveReactSpeed = 20 * ( (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].RecoilDistance / 5000) * 10) / 15);

					//# Ammo Check
					if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) player[g_Player]->WeaponAmmo -= 0.2 / (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Ammo / 5000) * 10);
					else player[g_Player]->WeaponAmmo -= 1 / (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Ammo / 5000) * 10);

					if(player[g_Player]->WeaponAmmo <= 0)
						{
						player[g_Player]->WeaponStatus = 8;
						player[g_Player]->attposecnt = 0;
						player[g_Player]->blendamount[58] = 0;
						}
					}
				}

			if(player[g_Player]->MFlash == 0)
				{
				if(player[g_Player]->WeaponRecoil - (0.03 * _->TimeScale * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover/5000)*3)+1)) >= 0) player[g_Player]->WeaponRecoil -= (0.03 * _->TimeScale * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover/5000)*2)+1));
				else player[g_Player]->WeaponRecoil = 0;
				}

			if(player[g_Player]->WepIdle >= 1000)
				{
				player[g_Player]->attposecnt = 3.30;
				player[g_Player]->WeaponStatus = 6;
				}

			if((KEY_PRESS_DOWN(QIN_TAB)) && _->NetworkOption != 1)
				{
				player[g_Player]->attposecnt = 1.0;
				player[g_Player]->WeaponStatus = 3;
				player[g_Player]->blendamount[25] = 0;
				}

			if(player[g_Player]->blendamount[25]+ (0.3*_->TimeScale) <=1) player[g_Player]->blendamount[25] += 0.3*_->TimeScale;
			}


		if(player[g_Player]->WeaponStatus == 6)	//Weapon To Shoulder
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], player[g_Player]->attposecnt, NULL);
				}

			if(player[g_Player]->attposecnt + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness *(0.02*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75)) <= 3.67) player[g_Player]->attposecnt += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness * 0.02*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75);
			else
				{
				player[g_Player]->attposecnt = 1.0;
				player[g_Player]->WeaponStatus = 3;
				}
			}


		if(player[g_Player]->WeaponStatus == 7)	//Holster Weapon
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], player[g_Player]->attposecnt, NULL);
				}

			if(player[g_Player]->attposecnt <= 0.35) player[g_Player]->Backpack.Draw = 1;

			if(player[g_Player]->attposecnt-(0.08*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75)*player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness) >= 0) player[g_Player]->attposecnt -= 0.08*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD/5000)*0.75)*player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness;
			else
				{
				player[g_Player]->WeaponStatus = 0;
				player[g_Player]->attposecnt = 0;
				player[g_Player]->Aposestate = 0;
				player[g_Player]->blendamount[25] = 0;
				player[g_Player]->blendamount[0] = 0;
				player[g_Player]->attackon = 0;
				player[g_Player]->WeaponATTACHFLAG = 0;
				//Qpo->Avatar_Detach(&player[g_Player]->Weapon.Avatar);
				Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Weapon.Xform.Translation);
				player[g_Player]->WepAlpha = 0;
				}

			if(player[g_Player]->WepAlpha-40 >= 0) player[g_Player]->WepAlpha -= 40;
			else player[g_Player]->WepAlpha = 0;

			Qpo->Mesh_SetAlpha(&player[g_Player]->Weapon, player[g_Player]->WepAlpha);
			}


		if(player[g_Player]->WeaponStatus == 8)	//Reload Weapon
			{
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[138], player[g_Player]->attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[125], player[g_Player]->attposecnt, NULL);
				}

			if(player[g_Player]->ReloadPos == 0)
				{
				player[g_Player]->ReloadPos++;
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'BOLT SLAP' SOUND
				Qpo->Sound_Play(Medias->S_RifleBoltOut[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].QAS_ReloadBoltOut], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
				}

			if(player[g_Player]->ReloadPos == 1)
				{
				if(player[g_Player]->attposecnt > 0.13)
					{
					player[g_Player]->ReloadPos++;
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'BOLT SLAP' SOUND
					Qpo->Sound_Play(Medias->S_RifleClipOut[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].QAS_ReloadClipOut], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
					}
				}

			if(player[g_Player]->ReloadPos == 2)
				{
				if(player[g_Player]->attposecnt > 0.69)
					{
					player[g_Player]->ReloadPos++;
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'BOLT SLAP' SOUND
					Qpo->Sound_Play(Medias->S_RifleClipIn[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].QAS_ReloadClipIn], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
					}
				}

			if(player[g_Player]->ReloadPos == 3)
				{
				if(player[g_Player]->attposecnt > 0.85)
					{
					player[g_Player]->ReloadPos++;
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'BOLT SLAP' SOUND
					Qpo->Sound_Play(Medias->S_RifleBoltIn[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].QAS_ReloadBoltIn], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
					}
				}

			if(player[g_Player]->attposecnt >= 0.4 && player[g_Player]->attposecnt < 0.7) player[g_Player]->Backpack.Draw = 1;

			if(player[g_Player]->attposecnt + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness *(0.02*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD/5000)*4)) <= 1.00) player[g_Player]->attposecnt += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness * 0.02*_->TimeScale*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD/5000)*4);	//0.05
			else
				{
				player[g_Player]->attposecnt = 2.27;
				player[g_Player]->WepIdle = 0;
				player[g_Player]->WeaponStatus = 5;
				player[g_Player]->blendamount[25]=0;
				player[g_Player]->WeaponAmmo = 32;
				player[g_Player]->ReloadPos = 0;
				}

			if(player[g_Player]->blendamount[58]+ (0.3*_->TimeScale) <=1) player[g_Player]->blendamount[58] += 0.3*_->TimeScale;
			else player[g_Player]->blendamount[58] = 1;
			}


		if(player[g_Player]->WeaponStatus != 0)
			{
			//##### Body Rotation
			player[g_Player]->BodyRotation = player[g_Player]->Angles.y - (player[g_Player]->Vehicle.Angles.y + (PI/4) + (PI/8));

			//Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[17], &player[g_Player]->TempXForm1);
			//Qpo->Transform_RotateX(&player[g_Player]->TempXForm1, player[g_Player]->BodyRotation/3);
			//Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[17], &player[g_Player]->TempXForm1);

			Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &player[g_Player]->TempXForm1);
			Qpo->Transform_RotateX(&player[g_Player]->TempXForm1, player[g_Player]->BodyRotation/2);
			Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &player[g_Player]->TempXForm1);

			Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &player[g_Player]->TempXForm1);
			Qpo->Transform_RotateX(&player[g_Player]->TempXForm1, player[g_Player]->BodyRotation/2);
			Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &player[g_Player]->TempXForm1);
			}


			//##### MAKE SURE TO RENDER WEAPON IN ALL CASES
		if(player[g_Player]->WeaponStatus != 0)
			{
			if(player[g_Player]->WeaponATTACHFLAG == 1)
				{
				Qpo->Avatar_SetBoneAttach(&player[g_Player]->Vehicle.Model.Avatar, "BONE01", &player[g_Player]->Vehicle.AttachMat);
				//Qpo->Avatar_SetBoneAttach(&player[g_Player]->Weapon.Avatar, "BONE01", &player[g_Player]->WepAttach);
				}

			//Qpo->Avatar_ClearPose(player[g_Player]->Weapon.Avatar, &player[g_Player]->Weapon.Xform);

			if(player[g_Player]->Mech.ACTIVE == 0)
				{
				Qpo->Mesh_SetScale(&player[g_Player]->Weapon, 1.2 + ((0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)) * 2.7907));
				}
			else
				{
				Qpo->Mesh_SetScale(&player[g_Player]->Weapon, 1.2 + ((0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)) * 2.7907));
				}
			}

		//Aim Weapon
		if(player[g_Player]->WeaponStatus == 4 || player[g_Player]->WeaponStatus == 5 && player[g_Player]->Mposestate != 23 && player[g_Player]->Mposestate != 24)
			{
			//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->AttPos);
			Qpo->Transform_GetLeft(&player[g_Player]->AttPos,&player[g_Player]->AimVec);
			Qpo->Transform_GetUp(&player[g_Player]->AttPos,&player[g_Player]->AimVecUp);
			Qpo->Transform_GetIn(&player[g_Player]->AttPos,&player[g_Player]->In);
			Qpo->Vec3d_Inverse(&player[g_Player]->AimVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].LaserLOC.z, &player[g_Player]->AimVec, &player[g_Player]->AttPos.Translation);			//1
			Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].LaserLOC.y, &player[g_Player]->AimVecUp, &player[g_Player]->AttPos.Translation);		//-4.5
			Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].LaserLOC.x, &player[g_Player]->In, &player[g_Player]->AttPos.Translation);		//-4.5
			Qpo->Vec3d_AddScaled(&player[g_Player]->AttPos.Translation, 2000, &player[g_Player]->AimVec, &player[g_Player]->OAttPos.Translation);

			if(Qpo->Collision_RayTest(
				 NULL,
				 NULL,
				 &player[g_Player]->AttPos.Translation, 
				 &player[g_Player]->OAttPos.Translation, 
				 // GE_CONTENTS_CANNOT_OCCUPY
				 /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
				 0xffffffff, NULL, NULL, 
				 &player[g_Player]->Collision))
				{
				// Set the new pos to the point of collision
				player[g_Player]->OAttPos.Translation.acSet(player[g_Player]->Collision.Impact.m_X, player[g_Player]->Collision.Impact.m_Y, player[g_Player]->Collision.Impact.m_Z);

				player[g_Player]->LaserLV.a = 130;
				player[g_Player]->LaserLV.r = 255;
				player[g_Player]->LaserLV.g = 255;			//alpha values and colour
				player[g_Player]->LaserLV.b = 255;
				player[g_Player]->LaserLV.x = player[g_Player]->Collision.Impact.m_X;
				player[g_Player]->LaserLV.y = player[g_Player]->Collision.Impact.m_Y;
				player[g_Player]->LaserLV.z = player[g_Player]->Collision.Impact.m_Z;

				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].LaserTYPE >= 2) Qpo->Poly_AddOnce(&player[g_Player]->LaserLV, 1, Medias->spec, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.04f);
				}

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].LaserTYPE >= 1) Q.ShowLine(&player[g_Player]->AttPos.Translation, &player[g_Player]->OAttPos.Translation, &player[g_Player]->ViewXForm.Translation, 0.6, Medias->LaserSight, player[g_Player]->WepAlpha, 255, 0, 0, 0);
			}


		//### CONDITIONAL WEAPON ATTACH ###
		if((player[g_Player]->WeaponStatus > 1) && (player[g_Player]->WeaponStatus != 7) && (player[g_Player]->WeaponATTACHFLAG == 0))
			{
			player[g_Player]->WeaponATTACHFLAG = 1;

			Qpo->Vec3d_Copy(&player[g_Player]->OAttPos.Translation, &player[g_Player]->Weapon.Xform.Translation);
			player[g_Player]->WepAttach = player[g_Player]->Weapon.Xform;
			Qpo->Transform_SetTranslation(&player[g_Player]->WepAttach, 0, 0, 0);

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3)
				{
				player[g_Player]->WepAttach.Translation.x -= 9;
				player[g_Player]->WepAttach.Translation.y -= 4.6;
				player[g_Player]->WepAttach.Translation.z -= 1;

				Qpo->Transform_RotateX(&player[g_Player]->WepAttach, PI/2);
				Qpo->Transform_RotateY(&player[g_Player]->WepAttach, -(PI/4)-0.8);
				}

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)
				{
				player[g_Player]->WepAttach.Translation.x -= 9;
				player[g_Player]->WepAttach.Translation.y -= 4.6;
				player[g_Player]->WepAttach.Translation.z -= 1;

				//Qpo->Transform_RotateX(&player[g_Player]->WepAttach, PI/2);
				Qpo->Transform_RotateY(&player[g_Player]->WepAttach, -(PI/4)-0.8);
				}

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF != 4 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF != 3)
				{
				player[g_Player]->WepAttach.Translation.x -= 0.5;
				player[g_Player]->WepAttach.Translation.y -= 3;
				player[g_Player]->WepAttach.Translation.z -= 1;

				Qpo->Transform_RotateX(&player[g_Player]->WepAttach, PI/2);
				Qpo->Transform_RotateY(&player[g_Player]->WepAttach, -(PI/4)-0.35);
				}

			////~##~Qpo->Avatar_Attach(&player[g_Player]->Weapon.Avatar, "BONE01", &playerAV[g_Player]->Avatar, "BIP01 R HAND", &player[g_Player]->WepAttach);
			}
		}


	if(KEY_PRESS_DOWN(QIN_TAB))	//****////WEAPON\\\\****
		{
		if(player[g_Player]->WeaponStatus == 0)
			{
			player[g_Player]->Aposestate = 20;
			player[g_Player]->attposecnt = 0;
			player[g_Player]->WeaponStatus = 1;

			player[g_Player]->WepAlpha = 0;
			Qpo->Mesh_SetAlpha(&player[g_Player]->Weapon, 0);
			}
		}

}

};