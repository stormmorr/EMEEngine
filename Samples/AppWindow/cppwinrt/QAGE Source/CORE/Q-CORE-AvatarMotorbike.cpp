/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Core Control Component-
	*/#include "pch.h"/*- Minor Component -Avatar Mounted On Motorbike-

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

void Q_COREFunctions::AICoreMB(int AIcounter)
{	
///**********************************************************************************************************
// View Rotation *******************************************************************************************

	//####### VEHICLE INPUT ########


	//##### JSRUSH
	if(Q_Forge->Forge[AIcounter].KL_LTFSpecLevel == 2)
		{
		if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
			{
			Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
			Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
			if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

			Q_Forge->Forge[AIcounter].astackcnt = 0;
			Q_Forge->Forge[AIcounter].astackrun = 0;
			Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
			Q_Forge->Forge[AIcounter].KL_LTFSpecLevel = 0;

			Q_Forge->Forge[AIcounter].attposecnt = 0;
			Q_Forge->Forge[AIcounter].Aposestate = 0;
			Q_Forge->Forge[AIcounter].blendamount[0] = 0;
			Q_Forge->Forge[AIcounter].blendamount[73] = 0;
			Q_Forge->Forge[AIcounter].TrailsOn = 0;
			Q_Forge->Forge[AIcounter].attackon = 0;
			Q_Forge->Forge[AIcounter].ShadowsOn = 1;
			Q_Forge->Forge[AIcounter].blendamount[0] = 0;

			/*QpoSound3D_GetConfig(World,
						&Q_Forge->Forge[AIcounter].ViewXForm,
						&Q_Forge->Forge[AIcounter].ViewXForm.Translation,
						600.0f,
						2.0f,
						&Volume,
						&Pan,
						&Frequency);*/

			//'Jink'
			Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);

			if(Q_Forge->Forge[AIcounter].Vehicle.JINKrush == 1)
				{
				Q_Forge->Forge[AIcounter].Vehicle.JINKrush = 0;
				Q_Forge->Forge[AIcounter].WindWake = 0;
				}
			else if(Q_Forge->Forge[AIcounter].Vehicle.JINKrush == 0)
				{
				Q_Forge->Forge[AIcounter].Vehicle.JINKrush = 1;
				Q_Forge->Forge[AIcounter].WindWake = 1;
				}
			}
		else
			{
			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
			}
		}


	//##### --- SOLDIER CLASS JINK MOVES --- #####
	if((Q_Forge->Forge[AIcounter].CharDATA.Class == 1) && ((_->lbutton[g_Player] == 1 || _->mbutton[g_Player] == 1) && (Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30)))
		{
		//### Damage Upgrades
		if(Q_Forge->Forge[AIcounter].KL_RTFSpecLevel == 1)		//### Single Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 1;

				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			else
				{
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			}


		if(Q_Forge->Forge[AIcounter].KL_RTFSpecLevel == 2)		//### Double Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 130 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 130 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 2;

				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			else
				{
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			}


		if(Q_Forge->Forge[AIcounter].KL_RTFSpecLevel > 2)		//### Triple Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 350 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 350 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 3;

				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			else
				{
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			}


		//### Accuracy Upgrades
		if(Q_Forge->Forge[AIcounter].KL_LTFSpecLevel == 1)		//### Single Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 20 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 20 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 1;

				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			else
				{
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			}


		if(Q_Forge->Forge[AIcounter].KL_LTFSpecLevel == 2)		//### Double Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 75 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 75 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 2;

				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			else
				{
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			}


		if(Q_Forge->Forge[AIcounter].KL_LTFSpecLevel > 2)		//### Triple Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 250 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 250 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 3;

				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			else
				{
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink Ready'
				Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}
			}

		}//End SOLDIER JINKS


		//########==---  GENERIC INPUT  ---==#########


	//### RESET ZONING
	Q_Forge->Forge[AIcounter].Vehicle.ZONING = 0;

	SCRAM=0;
	while(SCRAM < Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks)
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Active == 1)
			{
			//###### CHECKS TO FIND AVATARS WITHIN BLOCK
			//#### CHECK PLAYER WITHIN
			Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE01", &Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT);

			if(Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.x < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.x
			&& Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.x > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.x
			&& Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.y < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.y
			&& Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.y > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.y
			&& Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.z < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.z
			&& Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.z > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.z)
				{
				Q_Forge->Forge[AIcounter].Vehicle.ZONING = 1;
				Q_Forge->Forge[AIcounter].Vehicle.WithinZONE = SCRAM;

				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity != 1)
					{
					Q_Forge->Forge[AIcounter].Vehicle.GravityAlter += ((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity - Q_Forge->Forge[AIcounter].Vehicle.GravityAlter) / 5);
					}
				}
			}

		SCRAM++;
		}


// View Rotation *******************************************************************************************
//**********************************************************************************************************


	//##### Keyboard Control
	//Temp Bike Tests
	if(KEY_PRESS_DOWN(QIN_f))
		{
		playerAV[g_Player]->Xform.Translation.x = 0;
		playerAV[g_Player]->Xform.Translation.y = 0;
		playerAV[g_Player]->Xform.Translation.z = 0;

		Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity = 0;
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FSpinLift = 0;
		Q_Forge->Forge[AIcounter].Vehicle.Phys_VerticalRotate = 0;

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
		Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP.x = 0;
		Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP.y = 0;
		Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP.z = 1;
		Qpo->Transform_New_LeftUpIn(&playerAV[g_Player]->Xform, &TempVec1, &TempVec2, &TempVec3);
		Qpo->Transform_Orthonormalize(&playerAV[g_Player]->Xform);
		}


	//### Accelerator Down
	if(_->mbutton[g_Player])
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.JINKrush == 0)
			{
			Q_Forge->Forge[AIcounter].Vehicle.Phys_Power += 0.67 * _->TimeScale;
			if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Power > 20) Q_Forge->Forge[AIcounter].Vehicle.Phys_Power = 20;
			}

		if(Q_Forge->Forge[AIcounter].Vehicle.JINKrush == 1)
			{
			Q_Forge->Forge[AIcounter].Vehicle.Phys_Power += 3 * _->TimeScale;
			if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Power > 100) Q_Forge->Forge[AIcounter].Vehicle.Phys_Power = 100;
			}

		Q_Forge->Forge[AIcounter].Vehicle.Gear_Power += 0.08 * _->TimeScale;

		if(Q_Forge->Forge[AIcounter].Vehicle.Gear_Power > 1)
			{
			if(Q_Forge->Forge[AIcounter].Vehicle.Gear_Number < 5)
				{
				Q_Forge->Forge[AIcounter].Vehicle.Gear_Number++;
				Q_Forge->Forge[AIcounter].Vehicle.Gear_Power = 0.3;
				}
			}

		if(Q_Forge->Forge[AIcounter].Vehicle.SOUNDFLAGPower == 0)
			{
			Q_Forge->Forge[AIcounter].Vehicle.SOUNDFLAGPower = 1;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBPower, _->Volume, _->Pan, _->S_TimeScale*Q_Forge->Forge[AIcounter].Vehicle.Gear_Power, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
			}


		Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTpower++;

		if(Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTpower > ((1-(Q_Forge->Forge[AIcounter].Vehicle.Phys_Power/20))*20))
			{
			Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTpower = 0;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

		//if(QpoSound_SoundIsPlaying(SoundSys, Q_Forge->Forge[AIcounter].Vehicle.SOUNDpowerdown1) == false)
		//	{
			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBLoopPower, _->Volume, _->Pan, _->S_TimeScale*Q_Forge->Forge[AIcounter].Vehicle.Gear_Power, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
			//}

		//if(QpoSound_SoundIsPlaying(SoundSys, Q_Forge->Forge[AIcounter].Vehicle.SOUNDpowerdown2) == false)
		//	{
			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBLoopPower2, _->Volume, _->Pan, _->S_TimeScale*Q_Forge->Forge[AIcounter].Vehicle.Gear_Power, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
		//	}

		//if(QpoSound_SoundIsPlaying(SoundSys, Q_Forge->Forge[AIcounter].Vehicle.SOUNDpowerdown3) == false)
		//	{
			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBLoopPower3, _->Volume, _->Pan, _->S_TimeScale*Q_Forge->Forge[AIcounter].Vehicle.Gear_Power, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
			}
		//	}
		}
	else
		{
		Q_Forge->Forge[AIcounter].Vehicle.SOUNDFLAGPower = 0;
		Q_Forge->Forge[AIcounter].Vehicle.Phys_Power -= 2 * _->TimeScale;
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Power < 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_Power = 0;

		Q_Forge->Forge[AIcounter].Vehicle.Gear_Power -= 0.03 * _->TimeScale;

		if(Q_Forge->Forge[AIcounter].Vehicle.Gear_Power < 0)
			{
			Q_Forge->Forge[AIcounter].Vehicle.Gear_Number = 0;
			Q_Forge->Forge[AIcounter].Vehicle.Gear_Power = 0;
			}
		}


	//### Braking
	if(_->rbutton[g_Player])
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake += 0.06 * _->TimeScale;
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake > 5) Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake = 5;
		}
	else
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake -= 10 * _->TimeScale;
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake < 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake = 0;
		}


	if(KEY_PRESS_DOWN(QIN_z)) //##### Super Lean Turning
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT + 0.2 <= 3.1) Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT += 0.2;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT = 3.1;
		}
	else
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT - 0.2 >= 1.35) Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT -= 0.2;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT = 1.35;
		}


	if(KEY_DOWN_a())
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt + 0.025 <= 0.67) Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt += 0.025;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt = 0.67;

		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT > 1 && ((Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity < 0.2 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Power > 10 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake > 3)))
			{
			Q_Forge->Forge[AIcounter].Vehicle.Angles.y += 0.075;
			Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean = 0;
			}
		}

	if(KEY_DOWN_d())
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt - 0.025 >= 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt -= 0.025;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt = 0;

		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT > 1 && ((Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity < 0.2 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Power > 10 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake > 3)))
			{
			Q_Forge->Forge[AIcounter].Vehicle.Angles.y -= 0.075;
			Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean = 0;
			}
		}

	if(!KEY_DOWN_a() && !KEY_DOWN_d())
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt += (0.335 - Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt) / 3;
		}


	if(KEY_PRESS_DOWN(QIN_KP1))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempVEC.x -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP2))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempVEC.x += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP3))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempVEC.y -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP4))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempVEC.y += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP5))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempVEC.z -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_KP6))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempVEC.z += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_1))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempROTX -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_2))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempROTX += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_3))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempROTY -= 1;
		}

	if(KEY_PRESS_DOWN(QIN_4))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempROTY += 1;
		}

	if(KEY_PRESS_DOWN(QIN_5))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempROTZ -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_6))
		{
		Q_Forge->Forge[AIcounter].Vehicle.AttachTempROTZ += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_7))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_WheelSettleSpin -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_8))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_WheelSettleSpin += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_9))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_WheelSettleDVel -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_0))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_WheelSettleDVel += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_LEFT))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_RIGHT))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_DOWN))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_SpringAbsorbVel -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_UP))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_SpringAbsorbVel += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_HOME))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_ForceFactor -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_END))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_ForceFactor += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_INSERT))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_SpringAbsorbSpin -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_DELETE))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_SpringAbsorbSpin += 0.01;
		}


	if(KEY_PRESS_DOWN(QIN_z))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_LightTouchFactor -= 0.005;
		}

	if(KEY_PRESS_DOWN(QIN_CAPSLOCK))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_LightTouchFactor += 0.005;
		}


	if(KEY_PRESS_DOWN(QIN_F1))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTX -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_F2))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTX += 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_F3))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTY -= 0.1;
		}

	if(KEY_PRESS_DOWN(QIN_F4))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTY += 0.1;
		}

	if(KEY_PRESS_DOWN(QIN_F5))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ -= 0.01;
		}

	if(KEY_PRESS_DOWN(QIN_F6))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ += 0.01;
		}

	if(Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ > 0.67) Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ = 0.67;
	if(Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ < 0) Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ = 0;


	if(KEY_PRESS_DOWN(QIN_LEFT))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Temp_Rotation -= 0.1;
		}

	if(KEY_PRESS_DOWN(QIN_RIGHT))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Temp_Rotation += 0.1;
		}


	//### - Weight Shifting
	if(KEY_DOWN_w())
		{
		Q_Forge->Forge[AIcounter].Mposestate = 1;
		Q_Forge->Forge[AIcounter].blendamount[110] = 0;
		Q_Forge->Forge[AIcounter].blendamount[112] = 0;

		/*if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity > 1 && (!(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH == 1 && Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH == 1) || ((Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH == 1 && Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH == 1) && _->rbutton[g_Player])))
			{
			
			}*/
		}

	/*if(KEY_DOWN_s())
		{
		Q_Forge->Forge[AIcounter].Mposestate = 2;
		Q_Forge->Forge[AIcounter].blendamount[110] = 0;
		Q_Forge->Forge[AIcounter].blendamount[111] = 0;

		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity > 1)
			{
			if(Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT + 0.025 <= 0.785) Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT += 0.025;
			else Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT = 0.785;
			}
		else
			{
			if(Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT - 0.025 >= 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT -= 0.025;
			else Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT = 0;
			}
		}
	else
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT - 0.025 >= 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT -= 0.025;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_WheelieLIFT = 0;
		}*/


	if(KEY_DOWN_s())	//### BIKE WHEELIE ###
		{
		Q_Forge->Forge[AIcounter].Mposestate = 2;
		Q_Forge->Forge[AIcounter].blendamount[110] = 0;
		Q_Forge->Forge[AIcounter].blendamount[111] = 0;

		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity > 1 && !(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH == 1 && Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH == 1))
			{
			Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionVec);
			if(Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionAMT < 20) Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionAMT += 1;
			}
		}
	else { if(Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionAMT > 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionAMT -= 1; }


	if(!KEY_DOWN_w() && !KEY_DOWN_s())
		{
		Q_Forge->Forge[AIcounter].Mposestate = 0;
		Q_Forge->Forge[AIcounter].blendamount[111] = 0;
		Q_Forge->Forge[AIcounter].blendamount[112] = 0;

		Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTloop++;

		if(Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTloop > 10)
			{
			Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTloop = 0;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBStartLoop, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
			}
		}


	//##### -  MotorCycle Physics  - #####

	//## Standard Acceleration
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH == 1 || 1)
		{
		if(Q_Forge->Forge[AIcounter].Mposestate != 2)
			{
			if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity < Q_Forge->Forge[AIcounter].Vehicle.Const_MaxSpeed) Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity += (Q_Forge->Forge[AIcounter].Vehicle.Phys_Power / Q_Forge->Forge[AIcounter].Vehicle.Const_Weight) / (((Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT - 1) / 4) + 1);
			}
		else if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity < Q_Forge->Forge[AIcounter].Vehicle.Const_MaxSpeed) Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity += ((Q_Forge->Forge[AIcounter].Vehicle.Phys_Power / Q_Forge->Forge[AIcounter].Vehicle.Const_Weight)*2) / (((Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT - 1) / 4) + 1);
		}
	//TODO weight becomes 0 when not touching ground

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH == 1 || 1)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity -= Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake / (((Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT - 1) / 4) + 1);
		}

	if(Q_Forge->Forge[AIcounter].Mposestate == 1) Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity -= 0.005 * Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity;
	else Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity -= 0.02 * Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity;

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity < 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity = 0;


	//##### Actual Re-allignment

	//### Set Vectors
	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &Q_Forge->Forge[AIcounter].Vehicle.Model.Up);
	Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&Q_Forge->Forge[AIcounter].Vehicle.Model.In);
	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &Q_Forge->Forge[AIcounter].Vehicle.Model.Left);

	Q_Forge->Forge[AIcounter].Vehicle.Down.x = 0;
	Q_Forge->Forge[AIcounter].Vehicle.Down.y = -1;
	Q_Forge->Forge[AIcounter].Vehicle.Down.z = 0;

	//##### CALCULATE FORWARD VECTOR
	//### Front Wheel Collision
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE08", &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE05", &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix);

	Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;
	Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit+(Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit/15), &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);

	/*if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, *//* 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.FCollision))
		{
		TempVec2 = Q_Forge->Forge[AIcounter].Vehicle.Model.Left;
		Qpo->Vec3d_Inverse(&TempVec2);

		Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AIcounter].Vehicle.FCollision.Plane.Normal, &TempVec2, &TempVec1);

		Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec.x += TempVec1.x / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;
		Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec.y += TempVec1.y / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;
		Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec.z += TempVec1.z / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;

		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec);
		}*/


	//##### =======-----  FRICTION SYSTEM -----======= ######

	//#### Calculate - Friction Causes -

	//## Turning ##
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT > 1.35 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity > Q_Forge->Forge[AIcounter].Vehicle.Const_FRICMinSlide)
		{
		Tempfloat = (Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT - 1.35) * (((Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity - Q_Forge->Forge[AIcounter].Vehicle.Const_FRICMinSlide) / (Q_Forge->Forge[AIcounter].Vehicle.Const_MaxSpeed / 2)) + 1);
		if(Tempfloat > 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR -= Tempfloat;
		}
	else	//##### ---- Power Down Slide Restoration ---- #####
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR += ((1 - (Q_Forge->Forge[AIcounter].Vehicle.Phys_Power / 20))* 0.25) / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;
		}


	//## Drive ##
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity < 0.2 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Power > 4 && Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake > 2)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR -= 3;
		Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity = 0;
		}


	//## Power Wheel spin ##
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Power > (Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * 2))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR -= 3.2;
		}


	//## Brake ##
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * Q_Forge->Forge[AIcounter].Vehicle.Phys_Brake > 25)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR -= 4;
		}


	//#######======---- INITIAL POP ----======#######
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR > 5 && Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR < 8)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT = 2;
		}


	//### LIMITS ###
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR > 20)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR = 15;
		}

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR < -10)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR = -10;
		}


	//#######======---- FRICTION GROW ----======#######
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR >= 5)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT = 1;
		}

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR >= 0 && Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR < 5)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT = (((1 - ((Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR - 2) / 3)) * 2.5) + 1);
		}

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR < 0)
		{
		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT < 6) Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT += 0.2;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT = 6;
		}


	//#######======---- FRICTION RESTORE ----======#######
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR < 8) Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR += 2;
	else Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionSTR = 8;


	//##### +++ EFFECTS +++ #####

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT > 1)
		{
		Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTskid++;

		if(Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTskid > (5 * (1 - (Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT / 10))))
			{
			Q_Forge->Forge[AIcounter].Vehicle.SOUNDCNTskid = 0;

			TempVec1 = playerAV[g_Player]->Xform.Translation;

			TempVec1.y += 100;

			//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink Ready'
			Qpo->Sound_Play(Medias->S_VehMBSkid, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);

			//### Rear Spring Restoration
			Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;
			Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit * 1.5, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);

			if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.Collision))
				{
				//#### ADD Medias->DECAL
				QpoVec3d f_ImpactPoint(Q_Forge->Forge[AIcounter].Vehicle.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.Collision.Impact.m_Z);
				Q.AddDecal(f_ImpactPoint, Q_Forge->Forge[AIcounter].Vehicle.Collision.Plane.Normal, 13, 2);

				jet=0;
				while(jet < (30 * (Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT / 10)))
					{
					//#### Smoke Blast
					Q_Cloud->Cloud[_->NomCloud].CloudType = 7;
					Q_Cloud->Cloud[_->NomCloud].CloudPos.acSet(Q_Forge->Forge[AIcounter].Vehicle.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.Collision.Impact.m_Z);
					Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+175;
					Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.25;	//0.33;
					Q_Cloud->Cloud[_->NomCloud].CloudTraVec = Q_Forge->Forge[AIcounter].Vehicle.Model.Up;
					Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += 0.15;
					Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + (Q_Forge->Forge[AIcounter].Vehicle.Phys_Power/5);
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
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE01", &Q_Forge->Forge[AIcounter].Vehicle.COGMatrix);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.COGMatrix.Translation, 14, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &Q_Forge->Forge[AIcounter].Vehicle.COGMatrix.Translation);
	//Q_Forge->Forge[AIcounter].Vehicle.COGMatrix.Translation = playerAV[g_Player]->Xform.Translation;


	//## Build Force Direction Vector
	Qpo->Vec3d_New(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirection);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirection, -Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * _->TimeScale, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirection);
	Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirection.y += Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity * _->TimeScale;

	//### Build Force Factor
	Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirectionLength = Qpo->Vec3d_Length(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirection);
	Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceFactor = (Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirectionLength / Q_Forge->Forge[AIcounter].Vehicle.Const_ForceFactor) + 1;

	//## Build Actual Force Vector
	Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection = Q_Forge->Forge[AIcounter].Vehicle.Phys_ForceDirection;
	Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection);
	Qpo->Vec3d_Scale(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection, 35.5, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection);
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection, &Q_Forge->Forge[AIcounter].Vehicle.COGMatrix.Translation, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection);

	//## Find Weight Distribution
	Q_Forge->Forge[AIcounter].Vehicle.Phys_DistF = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection, &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix.Translation);
	Q_Forge->Forge[AIcounter].Vehicle.Phys_DistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ActualForceDirection, &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation);
	Q_Forge->Forge[AIcounter].Vehicle.Phys_FWeightDistFactor = ( Q_Forge->Forge[AIcounter].Vehicle.Phys_DistR / Q_Forge->Forge[AIcounter].Vehicle.Phys_DistF ) / 35;
	Q_Forge->Forge[AIcounter].Vehicle.Phys_RWeightDistFactor = ( Q_Forge->Forge[AIcounter].Vehicle.Phys_DistF / Q_Forge->Forge[AIcounter].Vehicle.Phys_DistR ) / 35;


	//####### Apply Vehicle Gravity
	//Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity -= 0.5 * (( Q_Forge->Forge[AIcounter].Vehicle.Const_FWeight + Q_Forge->Forge[AIcounter].Vehicle.Const_RWeight) / 1.5);



	//##### ===== BEGIN FINAL VEHICLE PHYSICS ===== #####

	//### Store Old Wheel Positions
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE08", &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE05", &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix);
	Q_Forge->Forge[AIcounter].Vehicle.FWheelPOSSTR = Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix.Translation;
	Q_Forge->Forge[AIcounter].Vehicle.RWheelPOSSTR = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;
	Q_Forge->Forge[AIcounter].Vehicle.STR_Phys_FWheelBendPoseCnt = Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt;
	Q_Forge->Forge[AIcounter].Vehicle.STR_Phys_RWheelBendPoseCnt = Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt;
	//#### FIND VEHICLE CENTER
	Q_Forge->Forge[AIcounter].Vehicle.OLDCENTRALANGLEVEC = playerAV[g_Player]->Xform.Translation;
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.OLDCENTRALANGLEVEC, &Q_Forge->Forge[AIcounter].Vehicle.RotatePNTVEC,  &Q_Forge->Forge[AIcounter].Vehicle.OLDCENTRALANGLEVEC);

	//######### CALC FORCE VECS FOR WHEEL COLLISIONS
	Qpo->Vec3d_New(&Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC, -Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * _->TimeScale, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec, &Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC, -Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionAMT * _->TimeScale, &Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionVec, &Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC);
	Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC.y += Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity * _->TimeScale;

	Qpo->Vec3d_New(&Q_Forge->Forge[AIcounter].Vehicle.RWheelFORCEVEC);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.RWheelFORCEVEC, -Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * _->TimeScale, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec, &Q_Forge->Forge[AIcounter].Vehicle.RWheelFORCEVEC);
	Q_Forge->Forge[AIcounter].Vehicle.RWheelFORCEVEC.y += Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity * _->TimeScale;

	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &Q_Forge->Forge[AIcounter].In);
	Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos = Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix.Translation;
	Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos = Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix.Translation;
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, 1, &Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);

	if(Qpo->Collision_RayTest(&Q_Forge->Forge[AIcounter].Mins, &Q_Forge->Forge[AIcounter].Maxs, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_ACTORS,*/ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.ACollision))
		{	//### Loop to check all AI locations for first proximity check
		if(Q_Forge->Forge[AIcounter].Vehicle.ACollision.Avatar != 0)
			{
			if(Q_Forge->Forge[AIcounter].Vehicle.ACollision.Avatar.IDflag != 250)
				{
				SCRAM = Q_Forge->Forge[AIcounter].Vehicle.ACollision.Avatar.IDflag;

				if(Q_Forge->Forge[SCRAM].LIVE == 1)
					{
					if( (Q_Forge->Forge[SCRAM].Team != Q_Forge->Forge[AIcounter].Team) && (Q_Forge->Forge[SCRAM].HB_Dead == 0) && (Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha == 0) )
						{
						//### Find Distance between Avatar and Explosion
						AvatarPos = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
						AvatarPos.y += 65;
						QpoVec3d f_PVO(Q_Forge->Forge[AIcounter].Vehicle.ACollision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.ACollision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.ACollision.Impact.m_Z);
						Qpo->Vec3d_Subtract(&AvatarPos, &f_PVO, &DistVec);
						AvatarDist = Qpo->Vec3d_Length(&DistVec);
						Qpo->Vec3d_Normalize(&DistVec);

									//## Reduce Health
						Q_Forge->Forge[SCRAM].HB_ReduceOld = Q_Forge->Forge[SCRAM].HB_Health;

						Q_Forge->Forge[SCRAM].HB_Health -= ((100 * 3) + (Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * 4)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 100)) + 0.75);
						if(Q_Forge->Forge[SCRAM].HB_Health < 0) Q_Forge->Forge[SCRAM].HB_Health = 0;

						//### Experience Storage
						Q_Forge->Forge[AIcounter].AvatarDMGSTORE[SCRAM] += ((100 * 3) + (Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 100)) + 0.75);

						//#### Avatar DEATH
						if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
							{
							Q_Forge->Forge[SCRAM].HB_Health = 0;

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);

							if(_->TimeHole == 0)
							{ _->TimeHole = 4;	_->TimeRotate = 1; }

							Q_Forge->Forge[SCRAM].HB_Dead = 1;

							if((Q_Forge->Forge[AIcounter].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
								{
								//### Add Experience to attacking AVATAR
								
								}

							//##### Find KO Owner
							UniversalDMGSTR = 0;
							
							if(Q_Forge->Forge[AIcounter].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

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
								Q_Forge->Forge[AIcounter].DecFinger = ((float)rand() / 32767) * 6;

								if((Q_Forge->Forge[AIcounter].DecFinger <= 100 * (Q_Forge->Forge[SCRAM].CharDATA.Level/1000)))
									{
									
									}

								//SET Knockout
								_->KnockOutFLAG = 1;
								_->KnockOutTIMER = 0;
								_->KnockOutCNT = 0;
								_->KnockOutINIT = 0;
								_->KnockOutHEIGHT = 0;

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								

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

						Q_Forge->Forge[SCRAM].MoveReactSpeed = 4 + (Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity/5);

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
	Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos = Q_Forge->Forge[AIcounter].Vehicle.FWheelPOSSTR;
	Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS = Q_Forge->Forge[AIcounter].Vehicle.FWheelPOSSTR;
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, &Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC, &Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS);
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.FWheelFORCEVEC, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos);
	//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, -50, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS);

	if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.FCollision))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH = 1;

		Q_Forge->Forge[AIcounter].Vehicle.FWheelTESET = Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS;
		Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS.acSet(Q_Forge->Forge[AIcounter].Vehicle.FCollision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.FCollision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.FCollision.Impact.m_Z);

		//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelTESET, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.FWheelTESET);

		//#### TEMP
		//Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity = 0;

		//##### CALCULATE CRUNCH DISTANCE
		QpoVec3d f_ImpactVector(Q_Forge->Forge[AIcounter].Vehicle.FCollision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.FCollision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.FCollision.Impact.m_Z);
		Q_Forge->Forge[AIcounter].Vehicle.FWheelCompressionDIST = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].Vehicle.FWheelTESET, &f_ImpactVector);

			//### Full Compression	TODO ADD BOUNCE VECTORS AND SPIN
		if(Q_Forge->Forge[AIcounter].Vehicle.FWheelCompressionDIST > Q_Forge->Forge[AIcounter].Vehicle.Const_SpringCrunchMAX)
			{
			Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt = 0.67;
			}
		else//### Minor Compression
			{
			Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt = (0.335 + ((Q_Forge->Forge[AIcounter].Vehicle.FWheelCompressionDIST / 15) * 0.335));
			}
		}
	else
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH = 0;

		if((Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt - 0.05) >= 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt -= 0.05;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt = 0;
		}

	//Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt = Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ;

	Q_Forge->Forge[AIcounter].Vehicle.Phys_FSpringStrength = Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt * Q_Forge->Forge[AIcounter].Vehicle.Const_SpringPower;

	//### Rear Wheel
	Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos = Q_Forge->Forge[AIcounter].Vehicle.RWheelPOSSTR;
	Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS = Q_Forge->Forge[AIcounter].Vehicle.RWheelPOSSTR;
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, &Q_Forge->Forge[AIcounter].Vehicle.RWheelFORCEVEC, &Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS);
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.RWheelFORCEVEC, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos);
	//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, -50, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS);

	if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.RCollision))
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH = 1;

		Q_Forge->Forge[AIcounter].Vehicle.RWheelTESET = Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS;
		Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS.acSet(Q_Forge->Forge[AIcounter].Vehicle.RCollision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.RCollision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.RCollision.Impact.m_Z);

		//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.RWheelTESET, Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.RWheelTESET);

		//#### TEMP
		//Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity = 0;

			TempVec2 = Q_Forge->Forge[AIcounter].Vehicle.Model.Left;
			Qpo->Vec3d_Inverse(&TempVec2);

			Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AIcounter].Vehicle.FCollision.Plane.Normal, &TempVec2, &TempVec1);

			Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec.x += TempVec1.x / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;
			Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec.y += TempVec1.y / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;
			Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec.z += TempVec1.z / Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT;

			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec);

		//##### CALCULATE CRUNCH DISTANCE
		QpoVec3d f_ImpactVector(Q_Forge->Forge[AIcounter].Vehicle.RCollision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.RCollision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.RCollision.Impact.m_Z);
		Q_Forge->Forge[AIcounter].Vehicle.RWheelCompressionDIST = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].Vehicle.RWheelTESET, &f_ImpactVector);

			//### Full Compression	TODO ADD BOUNCE VECTORS AND SPIN
		if(Q_Forge->Forge[AIcounter].Vehicle.RWheelCompressionDIST > Q_Forge->Forge[AIcounter].Vehicle.Const_SpringCrunchMAX)
			{
			Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt = 0.67;
			}
		else//### Minor Compression
			{
			Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt = (0.335 + ((Q_Forge->Forge[AIcounter].Vehicle.RWheelCompressionDIST / 15) * 0.335));
			}
		}
	else
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH = 0;

		if((Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt - 0.05) >= 0) Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt -= 0.05;
		else Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt = 0;
		}

	Q_Forge->Forge[AIcounter].Vehicle.Phys_RSpringStrength = Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt * Q_Forge->Forge[AIcounter].Vehicle.Const_SpringPower;

	//Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt = Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTZ;


	//##### VAPOR TRAILS

	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE08", &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE05", &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix);


	if(Q_Forge->Forge[AIcounter].Vehicle.JINKrush == 1)
		{
		ColourSTART.red = 50;
		ColourSTART.green = 255;
		ColourSTART.blue = 50;
		ColourSTART.alpha = 50;
		ColourEND.red = 50;
		ColourEND.green = 255;
		ColourEND.blue = 0;
		ColourEND.alpha = 0;

		TempVec1 = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;
		TempVec2 = Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation;

		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &TempVec3);
		Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&Q_Forge->Forge[AIcounter].Vehicle.Model.Up);
		Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &Q_Forge->Forge[AIcounter].Vehicle.Model.Left);
		//Qpo->Vec3d_Inverse(&TempVec3);

		Qpo->Vec3d_AddScaled(&TempVec1, -22, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &TempVec1);
		Qpo->Vec3d_AddScaled(&TempVec2, -22, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &TempVec2);

		Qpo->Vec3d_AddScaled(&TempVec1, 17, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &TempVec1);
		Qpo->Vec3d_AddScaled(&TempVec2, -17, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &TempVec2);

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
	Qpo->Vec3d_AddScaled(&TempVec1, -35, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &TempVec1);
	Qpo->Vec3d_AddScaled(&TempVec1, -4, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &TempVec1);

	Qpo->Vec3d_AddScaled(&TempVec2, 40, &TempVec3, &TempVec2);
	Qpo->Vec3d_AddScaled(&TempVec2, -35, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &TempVec2);
	Qpo->Vec3d_AddScaled(&TempVec2, 4, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &TempVec2);


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

		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*((Q_Forge->Forge[AIcounter].Vehicle.Phys_Power/10) + 1);

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

		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*((Q_Forge->Forge[AIcounter].Vehicle.Phys_Power/10) + 1);

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
	Q_Forge->Forge[AIcounter].Vehicle.FWheelSpinPoseCnt += Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity / 200;
	while(Q_Forge->Forge[AIcounter].Vehicle.FWheelSpinPoseCnt > 0.67)
		{
		Q_Forge->Forge[AIcounter].Vehicle.FWheelSpinPoseCnt = Q_Forge->Forge[AIcounter].Vehicle.FWheelSpinPoseCnt - 0.67;
		}

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FrictionAMT == 1)
		{ Q_Forge->Forge[AIcounter].Vehicle.RWheelSpinPoseCnt += Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity / 200; }
	else { Q_Forge->Forge[AIcounter].Vehicle.RWheelSpinPoseCnt += Q_Forge->Forge[AIcounter].Vehicle.Phys_Power / 75; }

	while(Q_Forge->Forge[AIcounter].Vehicle.RWheelSpinPoseCnt > 0.67)
		{
		Q_Forge->Forge[AIcounter].Vehicle.RWheelSpinPoseCnt = Q_Forge->Forge[AIcounter].Vehicle.RWheelSpinPoseCnt - 0.67;
		}

	Qpo->Avatar_ClearPose(Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, &Q_Forge->Forge[AIcounter].Vehicle.Model.Xform);
	Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, 1.2f,1.2f,1.2f);

	//## Set Wheel Turn
	Qpo->Avatar_SetPosePM(Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, Q_Forge->Forge[AIcounter].Vehicle.Model.Motion[3], Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt, NULL);

	//## Set Wheel Scale
	Qpo->Avatar_SetPosePM(Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, Q_Forge->Forge[AIcounter].Vehicle.Model.Motion[1], Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt, NULL);
	Qpo->Avatar_SetPosePM(Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, Q_Forge->Forge[AIcounter].Vehicle.Model.Motion[4], Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt, NULL);

	//## Set Wheel Rotation
	Qpo->Avatar_SetPosePM(Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, Q_Forge->Forge[AIcounter].Vehicle.Model.Motion[0], Q_Forge->Forge[AIcounter].Vehicle.RWheelSpinPoseCnt, NULL);
	Qpo->Avatar_SetPosePM(Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, Q_Forge->Forge[AIcounter].Vehicle.Model.Motion[2], Q_Forge->Forge[AIcounter].Vehicle.FWheelSpinPoseCnt, NULL);

	//NEW WHEEL POSITIONS
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE08", &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE05", &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix);


	//####### Apply Vehicle Gravity
	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH == 0 || Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH == 0 /*&& KEY_PRESS_DOWN(QIN_TAB)*/)
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity -= (((0.5 * (( Q_Forge->Forge[AIcounter].Vehicle.Const_FWeight + Q_Forge->Forge[AIcounter].Vehicle.Const_RWeight) / 1.5)) / Q_Forge->Forge[AIcounter].Vehicle.GravityAlter) * _->TimeScale);
		}
	else
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_DownVelocity = 0;
		}


	//###### COLLISION DETECTION INITIAL
	Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos = playerAV[g_Player]->Xform.Translation;
	Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos = playerAV[g_Player]->Xform.Translation;

	Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos.y += 50;
	Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos.y += 50;

	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, -60, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);
																									//EDIT Removed Collision detection with actors
	if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.Model.OldPos, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &playerAV[g_Player]->Collision))
		{
		QpoVec3d f_ImpactPoint(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Z);
		Q_Forge->Forge[AIcounter].Vehicle.CollCRUNCH = Qpo->Vec3d_DistanceBetween(&f_ImpactPoint, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);

		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, Q_Forge->Forge[AIcounter].Vehicle.CollCRUNCH, &playerAV[g_Player]->Collision.Plane.Normal, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos, 60, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec, &Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos);

		if(Q_Forge->Forge[AIcounter].Vehicle.CollCRUNCH > 20) Q_Forge->Forge[AIcounter].Vehicle.RapidDismount = 1;

		Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos.y -= 50;

		playerAV[g_Player]->Xform.Translation = Q_Forge->Forge[AIcounter].Vehicle.Model.NewPos;
		}


	//#### Replace New Positions
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, -Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, -Q_Forge->Forge[AIcounter].Vehicle.Const_SpringLimit, &Q_Forge->Forge[AIcounter].Vehicle.Down, &Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS);

	//if(Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTOUCH == 1 && Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelTOUCH == 1 )
	//	{
	//#### BUILD OLD PERFECT POSITIONS
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelPOSSTR, (1 - (Q_Forge->Forge[AIcounter].Vehicle.STR_Phys_FWheelBendPoseCnt / 0.67)) - 0.5, &Q_Forge->Forge[AIcounter].Vehicle.ConstVec_FCrunch, &Q_Forge->Forge[AIcounter].Vehicle.FWheelOLDPERFECTPOS);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.RWheelPOSSTR, (1 - (Q_Forge->Forge[AIcounter].Vehicle.STR_Phys_RWheelBendPoseCnt / 0.67)) - 0.5, &Q_Forge->Forge[AIcounter].Vehicle.ConstVec_RCrunch, &Q_Forge->Forge[AIcounter].Vehicle.RWheelOLDPERFECTPOS);

	//#### BUILD NEW PERFECT POSITIONS
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, (1 - (Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelBendPoseCnt / 0.67)) - 0.5, &Q_Forge->Forge[AIcounter].Vehicle.ConstVec_FCrunch, &Q_Forge->Forge[AIcounter].Vehicle.FWheelPERFECTPOS);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, (1 - (Q_Forge->Forge[AIcounter].Vehicle.Phys_RWheelBendPoseCnt / 0.67)) - 0.5, &Q_Forge->Forge[AIcounter].Vehicle.ConstVec_RCrunch, &Q_Forge->Forge[AIcounter].Vehicle.RWheelPERFECTPOS);

	//#### FIND VEHICLE CENTER
	Q_Forge->Forge[AIcounter].Vehicle.CENTRALANGLEVEC = playerAV[g_Player]->Xform.Translation;
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.CENTRALANGLEVEC, &Q_Forge->Forge[AIcounter].Vehicle.RotatePNTVEC, &Q_Forge->Forge[AIcounter].Vehicle.CENTRALANGLEVEC);

	Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Vehicle.FWheelPERFECTPOS, &Q_Forge->Forge[AIcounter].Vehicle.RWheelPERFECTPOS, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP);
	Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Vehicle.FWheelOLDPERFECTPOS, &Q_Forge->Forge[AIcounter].Vehicle.RWheelOLDPERFECTPOS, &Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP);
	Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP);
	Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP);

	//#### BUILD WANTED ROTATION VECTORS
	Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&Q_Forge->Forge[AIcounter].Vehicle.Model.Up);
	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &Q_Forge->Forge[AIcounter].Vehicle.Model.Left);


	//#### FIND true LIFT INCREMENT
	Qpo->Transform_New(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);

	Qpo->Transform_RotateZ(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean);

	Qpo->Transform_New_YRotation(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, Q_Forge->Forge[AIcounter].Vehicle.Angles.y);
	Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);

	Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left);

	//## SET INTERSECT LINES
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1 = Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP;
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2 = Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP;
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3 = Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP;
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP4 = Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP;

	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1, -50, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2, 50, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3, -0.01, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3);

	Tempint1 = Q.Q_LineLineintersect(Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1, Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2, Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3, Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP4, &Q_Forge->Forge[AIcounter].Vehicle.CalcRESA, &Q_Forge->Forge[AIcounter].Vehicle.CalcRESB);

	//Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.CalcRESA, &Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC);
	Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC);

	Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC.x = 0;
	Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC.z = 0;


	/*Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left);

	//## SET INTERSECT LINES
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1 = Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP;
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2 = Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP;
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3 = Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP;
	Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP4 = Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP;

	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1, -5, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2, 5, &Q_Forge->Forge[AIcounter].Vehicle.Model.Left, &Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3, -0.01, &Q_Forge->Forge[AIcounter].Vehicle.OLDVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3);

	Tempint1 = Q.Q_LineLineintersect(Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP1, Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP2, Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP3, Q_Forge->Forge[AIcounter].Vehicle.CalcLINEP4, &Q_Forge->Forge[AIcounter].Vehicle.CalcRESA, &Q_Forge->Forge[AIcounter].Vehicle.CalcRESB);

	Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.CalcRESA, &Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC);*/


	//#### PREPARE VEHICLE MATRIX POSITION
	Qpo->Transform_New(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);
	Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation = playerAV[g_Player]->Xform.Translation;


	//#### RESET AND BUILD PLAYACT MATRIX
	Qpo->Transform_New(&playerAV[g_Player]->Xform);
	Qpo->Transform_RotateX(&playerAV[g_Player]->Xform, -(PI/2));
	Qpo->Transform_RotateY(&playerAV[g_Player]->Xform, PI);
	Qpo->Transform_RotateZ(&playerAV[g_Player]->Xform, Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean);
	Qpo->Transform_New_YRotation(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, Q_Forge->Forge[AIcounter].Vehicle.Angles.y);
	Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, &playerAV[g_Player]->Xform, &playerAV[g_Player]->Xform);

	//#### FIND MOVE BACK VECTOR
	Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &_->Origin, &Q_Forge->Forge[AIcounter].Vehicle.RotatePNTVEC);
	playerAV[g_Player]->Xform.Translation = Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation;
	Qpo->Vec3d_Add(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[AIcounter].Vehicle.RotatePNTVEC, &playerAV[g_Player]->Xform.Translation);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Vehicle.RotatePNTVEC);


	//#### ADDAGE OF LIFT INCREMENT
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVECSTR, &Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC, &Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVECSTR);

	//######-- ROTATE IMAGE TO RUDDER VECTOR --########
	Qpo->Transform_New(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);

	/*Qpo->Transform_RotateZ(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean - Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLeanSTR);

	Qpo->Transform_New_YRotation(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, Q_Forge->Forge[AIcounter].Vehicle.Angles.y - Q_Forge->Forge[AIcounter].Vehicle.AnglesSTR.y);
	Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);*/

	Qpo->Transform_RotateZ(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean);

	Qpo->Transform_New_YRotation(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, Q_Forge->Forge[AIcounter].Vehicle.Angles.y);
	Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].Vehicle.RotateMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);

	Qpo->Transform_RotateVector(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVECSTR, &Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVEC);

	//#### STORE ANGLES AND LEAN
	Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLeanSTR = Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean;
	Q_Forge->Forge[AIcounter].Vehicle.AnglesSTR.y = Q_Forge->Forge[AIcounter].Vehicle.Angles.y;

	//#### ADDAGE OF LIFT INCREMENT
	//Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVEC, &Q_Forge->Forge[AIcounter].Vehicle.VehicleRUDDERINC, &Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVEC);


	Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP);
	Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.VehicleIMAGETORUDDERVEC, &Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP);
	Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP);

	//Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &Q_Forge->Forge[AIcounter].Vehicle.VehicleGETIN);
	//Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleUP = Q_Forge->Forge[AIcounter].Vehicle.VehicleGETIN;

	Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleLEFT);

	//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleLEFT);
	Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleLEFT, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleIN);
	Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleIN);
	Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleIN);

	//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP, Q_Forge->Forge[AIcounter].Vehicle.Const_MiddleCOGDISTX/5, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleIN, &Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP);

	Qpo->Transform_New(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);
	Qpo->Transform_New_LeftUpIn(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleLEFT, &Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleIN);
	Qpo->Transform_Orthonormalize(&Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix);

	Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation = playerAV[g_Player]->Xform.Translation;
	playerAV[g_Player]->Xform = Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix;
	playerAV[g_Player]->Xform.Translation = Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation;

	//##### SET WHEELS TO NEW WHEEL POSITIONS
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE08", &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix);
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE05", &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix);

	Q_Forge->Forge[AIcounter].Vehicle.JDISTF = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, &Q_Forge->Forge[AIcounter].Vehicle.FWheelPOSSTR);
	Q_Forge->Forge[AIcounter].Vehicle.JDISTR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, &Q_Forge->Forge[AIcounter].Vehicle.RWheelPOSSTR);

	if(Q_Forge->Forge[AIcounter].Vehicle.JDISTF > Q_Forge->Forge[AIcounter].Vehicle.JDISTR || Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMotionAMT > 0)
		{
		Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[AIcounter].Vehicle.RWheelMatrix.Translation, &Q_Forge->Forge[AIcounter].Vehicle.ToBASEPNTVEC);
		Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.RWheelNEWPOS, &Q_Forge->Forge[AIcounter].Vehicle.ToBASEPNTVEC, &playerAV[g_Player]->Xform.Translation);
		}
	else
		{
		Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[AIcounter].Vehicle.FWheelMatrix.Translation, &Q_Forge->Forge[AIcounter].Vehicle.ToBASEPNTVEC);
		Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].Vehicle.FWheelNEWPOS, &Q_Forge->Forge[AIcounter].Vehicle.ToBASEPNTVEC, &playerAV[g_Player]->Xform.Translation);
		}


	//####### Vehicle Rotation

		//### Calc Horizontal Turn Angles
	Q_Forge->Forge[AIcounter].Vehicle.Phys_Turn = Q_Forge->Forge[AIcounter].Vehicle.Phys_FWheelTurnPoseCnt - 0.335;

	if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity > 1.4)	//### In Motion
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean = Q_Forge->Forge[AIcounter].Vehicle.Phys_Turn * Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT;	//3.6
		Q_Forge->Forge[AIcounter].Vehicle.Angles.y += Q_Forge->Forge[AIcounter].Vehicle.Phys_Turn / ((8 / Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT)*1.35);
		}
	else	//### Still
		{
		Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnLean = (Q_Forge->Forge[AIcounter].Vehicle.Phys_Turn - 0.1) * Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT;	//1.35
		Q_Forge->Forge[AIcounter].Vehicle.Angles.y += Q_Forge->Forge[AIcounter].Vehicle.Phys_Turn / ((8 / Q_Forge->Forge[AIcounter].Vehicle.Phys_TurnMULT)*1.35);	//4
		}


	TempVec1 = playerAV[g_Player]->Xform.Translation;
	TempVec1.y += 45;
	Qpo->Vec3d_AddScaled(&TempVec1, 60, &Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec, &TempVec1);


	//- END MotorCycle Physics -


	//####### VehicleMount and Idle #####
	
	if(Q_Forge->Forge[AIcounter].WeaponStatus == 0 || 1)	//Idle Motion
		{
		//######- Vehicle In Motion -######

		if(Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity > 1.4)
			{
			//## 'Standard Ride' and 'Bike Mount'
			if(Q_Forge->Forge[AIcounter].Mposestate == 0)
				{
				Qpo->Avatar_BlendPose(Q_Forge->Forge[AIcounter].AV.Avatar, 110, Q_Forge->Forge[AIcounter].idleposecnt, &playerAV[g_Player]->Xform, 1);
			
				if(Q_Forge->Forge[AIcounter].idleposecnt+(0.02*_->TimeScale)<0.335) Q_Forge->Forge[AIcounter].idleposecnt += 0.02*_->TimeScale;		// < 0.67
				else Q_Forge->Forge[AIcounter].idleposecnt=0.335;
				}

			//## 'Rush Ride'
			if(Q_Forge->Forge[AIcounter].Mposestate == 1)
				{
				Qpo->Avatar_BlendPose(Q_Forge->Forge[AIcounter].AV.Avatar, 111, Q_Forge->Forge[AIcounter].idleposecnt, &playerAV[g_Player]->Xform, 1);
			
				if(Q_Forge->Forge[AIcounter].idleposecnt+(0.04*_->TimeScale) < 0.4) Q_Forge->Forge[AIcounter].idleposecnt += 0.04*_->TimeScale;
				else Q_Forge->Forge[AIcounter].idleposecnt=0.27;
				}

			//## 'Wheelie Ride'
			if(Q_Forge->Forge[AIcounter].Mposestate == 2)
				{
				Qpo->Avatar_BlendPose(Q_Forge->Forge[AIcounter].AV.Avatar, 112, Q_Forge->Forge[AIcounter].idleposecnt, &playerAV[g_Player]->Xform, 1);
			
				if(Q_Forge->Forge[AIcounter].idleposecnt+(0.03*_->TimeScale) < 0.335) Q_Forge->Forge[AIcounter].idleposecnt += 0.03*_->TimeScale;
				else Q_Forge->Forge[AIcounter].idleposecnt=0.335;
				}

			//# Reset Idle Pose
			Q_Forge->Forge[AIcounter].blendamount[113] = 0;
			}
		else	//######- Vehicle Stopped -######
			{
			Qpo->Avatar_BlendPose(Q_Forge->Forge[AIcounter].AV.Avatar, 113, Q_Forge->Forge[AIcounter].idleposecnt, &playerAV[g_Player]->Xform, 1);
			
			if(Q_Forge->Forge[AIcounter].idleposecnt+(0.03*_->TimeScale) < 0.335) Q_Forge->Forge[AIcounter].idleposecnt += 0.03*_->TimeScale;
			else Q_Forge->Forge[AIcounter].idleposecnt=0.335;
			}
		}


	//### - Player Attachingness
	if(Q_Forge->Forge[AIcounter].VehicleAttach == 0)
		{	//SUSPEND
		if(1/*Q_Forge->Forge[AIcounter].idleposecnt > 0.15*/)
			{
			Q_Forge->Forge[AIcounter].VehicleAttach = 1;

			Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].Vehicle.Model.Xform.Translation, &playerAV[g_Player]->Xform.Translation);
			playerAV[g_Player]->Xform.Translation.y -= 30;

			Qpo->Avatar_BlendPose(Q_Forge->Forge[AIcounter].AV.Avatar, 110, Q_Forge->Forge[AIcounter].idleposecnt, &playerAV[g_Player]->Xform, 1);

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01", &Q_Forge->Forge[AIcounter].Vehicle.AttachMat);
			Qpo->Transform_SetTranslation(&Q_Forge->Forge[AIcounter].Vehicle.AttachMat, 0, 0, 0);

			Q_Forge->Forge[AIcounter].Vehicle.AttachMat.Translation.x += -33.850327;
			Q_Forge->Forge[AIcounter].Vehicle.AttachMat.Translation.y += 22.530058;
			Q_Forge->Forge[AIcounter].Vehicle.AttachMat.Translation.z += 0;
			Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].Vehicle.AttachMat, 1.570797);
			Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].Vehicle.AttachMat, 2.809998);
			Qpo->Transform_RotateZ(&Q_Forge->Forge[AIcounter].Vehicle.AttachMat, 0);

			//~##~Qpo->Avatar_Attach(&Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, "BONE01", &playerAV[g_Player]->Avatar, "BIP01", &Q_Forge->Forge[AIcounter].Vehicle.AttachMat);
			}
		}


	//### Init Head Lights
	if(Q_Forge->Forge[AIcounter].Vehicle.HeadLightInit == 0)
		{
		Q_Forge->Forge[AIcounter].Vehicle.HeadLightInit = 1;

		Q_Forge->Forge[AIcounter].Vehicle.HeadLight = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_Forge->Forge[AIcounter].Vehicle.HeadLightEnd = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_Forge->Forge[AIcounter].Vehicle.NeonLight1 = Qpo->Light_AddtoWorld(_->GenericLightPos);

		Q_Forge->Forge[AIcounter].Vehicle.HeadLColor.red = 255;
		Q_Forge->Forge[AIcounter].Vehicle.HeadLColor.green = 255;
		Q_Forge->Forge[AIcounter].Vehicle.HeadLColor.blue = 210;

		Q_Forge->Forge[AIcounter].Vehicle.NeonLColor1.red = 255;
		Q_Forge->Forge[AIcounter].Vehicle.NeonLColor1.green = 855;
		Q_Forge->Forge[AIcounter].Vehicle.NeonLColor1.blue = 255;

		Q_Forge->Forge[AIcounter].Vehicle.HeadLPower = 950;
		Q_Forge->Forge[AIcounter].Vehicle.NeonLPower1 = 235;
		}


	//### Set Light Positions
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Vehicle.Model, "BONE01", &Q_Forge->Forge[AIcounter].Vehicle.HeadLMat);

	Q_Forge->Forge[AIcounter].Vehicle.HeadLPos = Q_Forge->Forge[AIcounter].Vehicle.HeadLMat.Translation;
	Q_Forge->Forge[AIcounter].Vehicle.NeonLPos1 = Q_Forge->Forge[AIcounter].Vehicle.HeadLMat.Translation;

	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.HeadLPos, -35, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &Q_Forge->Forge[AIcounter].Vehicle.HeadLPos);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.HeadLPos, -25, &Q_Forge->Forge[AIcounter].Vehicle.Model.In, &Q_Forge->Forge[AIcounter].Vehicle.HeadLPos);

	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.NeonLPos1, 10, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &Q_Forge->Forge[AIcounter].Vehicle.NeonLPos1);
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.NeonLPos1, 15, &Q_Forge->Forge[AIcounter].Vehicle.Model.In, &Q_Forge->Forge[AIcounter].Vehicle.NeonLPos1);


	//### Extend Light Out
	Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.HeadLPos, -5000, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &Q_Forge->Forge[AIcounter].Vehicle.HeadLENDPos);

	if(Qpo->Collision_RayTest(NULL,NULL, &Q_Forge->Forge[AIcounter].Vehicle.HeadLPos, &Q_Forge->Forge[AIcounter].Vehicle.HeadLENDPos, /*GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].Vehicle.HeadLCollision))
		{
		Q_Forge->Forge[AIcounter].Vehicle.HeadLENDPos.acSet(Q_Forge->Forge[AIcounter].Vehicle.HeadLCollision.Impact.m_X, Q_Forge->Forge[AIcounter].Vehicle.HeadLCollision.Impact.m_Y, Q_Forge->Forge[AIcounter].Vehicle.HeadLCollision.Impact.m_Z);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Vehicle.HeadLENDPos, 50, &Q_Forge->Forge[AIcounter].Vehicle.Model.Up, &Q_Forge->Forge[AIcounter].Vehicle.HeadLENDPos);
		}


	//### Set Head Light Attribs
	Qpo->Light_SetAttr(Q_Forge->Forge[AIcounter].Vehicle.HeadLight, &Q_Forge->Forge[AIcounter].Vehicle.HeadLPos, &Q_Forge->Forge[AIcounter].Vehicle.HeadLColor, Q_Forge->Forge[AIcounter].Vehicle.HeadLPower/10, true);
	Qpo->Light_SetAttr(Q_Forge->Forge[AIcounter].Vehicle.HeadLightEnd, &Q_Forge->Forge[AIcounter].Vehicle.HeadLENDPos, &Q_Forge->Forge[AIcounter].Vehicle.HeadLColor, Q_Forge->Forge[AIcounter].Vehicle.HeadLPower, true);
	Qpo->Light_SetAttr(Q_Forge->Forge[AIcounter].Vehicle.NeonLight1, &Q_Forge->Forge[AIcounter].Vehicle.NeonLPos1, &Q_Forge->Forge[AIcounter].Vehicle.NeonLColor1, Q_Forge->Forge[AIcounter].Vehicle.NeonLPower1/3, true);


		//### DisMount
	if(KEY_PRESS_DOWN(QIN_SPACE) || Q_Forge->Forge[AIcounter].attackon != 0 || Q_Forge->Forge[AIcounter].Vehicle.RapidDismount == 1)
		{
		Q_Forge->Forge[AIcounter].Vehicle.RapidDismount = 0;
		Q_Forge->Forge[AIcounter].PlayerMode = 0;
		Q_Forge->Forge[AIcounter].VehicleAttach = 0;
		Qpo->Avatar_Detach(&Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar);

		Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation = playerAV[g_Player]->Xform.Translation;

		Q_Forge->Forge[AIcounter].ROTATEMatrix = Q_Forge->Forge[AIcounter].STOREMatrix;
		Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].ROTATEMatrix, Q_Forge->Forge[AIcounter].Angles.y);
		playerAV[g_Player]->Xform = Q_Forge->Forge[AIcounter].ROTATEMatrix;
		playerAV[g_Player]->Xform.Translation = Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation;

		//#### Position vehicle
		Qpo->Transform_New(&Q_Forge->Forge[AIcounter].Vehicle.Model.Xform);
		Qpo->Transform_New_LeftUpIn(&Q_Forge->Forge[AIcounter].Vehicle.Model.Xform, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleLEFT, &Q_Forge->Forge[AIcounter].Vehicle.STRVehicleUP, &Q_Forge->Forge[AIcounter].Vehicle.NEWVehicleIN);
		Qpo->Transform_Orthonormalize(&Q_Forge->Forge[AIcounter].Vehicle.Model.Xform);

		Q_Forge->Forge[AIcounter].Vehicle.Model.Xform.Translation = Q_Forge->Forge[AIcounter].Vehicle.VehicMatrix.Translation;
		Q_Forge->Forge[AIcounter].Vehicle.Model.Xform.Translation.y += 27;

		//#### Player Hit reactions
		Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec);
		Q_Forge->Forge[AIcounter].MoveReactVec = Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec;
		Q_Forge->Forge[AIcounter].MoveReactSpeed = (Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity * _->TimeScale) / 2;

		//#### Player Hit reactions
		Q_Forge->Forge[AIcounter].Vehicle.MoveReactVec = Q_Forge->Forge[AIcounter].Vehicle.Phys_ForwardMotionVec;
		Q_Forge->Forge[AIcounter].Vehicle.MoveReactSpeed = Q_Forge->Forge[AIcounter].Vehicle.Phys_Velocity;
		}


	//##### Vehicle Weapon Usuage
	if(Q_Forge->Forge[AIcounter].Aposestate == 20 || (Q_Forge->Forge[AIcounter].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].attackon == 0))	//Weapon1
		{
		Q_Forge->Forge[AIcounter].wepposecnt = Q_Forge->Forge[AIcounter].attposecnt;	//Switch to wepposecnt if needed

		if(Q_Forge->Forge[AIcounter].WeaponStatus == 1)	//Draw Weapon
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(Q_Forge->Forge[AIcounter].attposecnt >= 0.30) Q_Forge->Forge[AIcounter].Backpack.Draw = 1;

			if(Q_Forge->Forge[AIcounter].attposecnt + Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness *(0.1*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75)) < 0.38) Q_Forge->Forge[AIcounter].attposecnt += Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness * 0.1*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75);	//0.05
			else
				{
				Q_Forge->Forge[AIcounter].attposecnt = 0.38;
				Q_Forge->Forge[AIcounter].WeaponStatus = 2;
				Q_Forge->Forge[AIcounter].WeaponATTACHFLAG = 1;

				Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].OAttPos.Translation, &Q_Forge->Forge[AIcounter].Weapon.Xform.Translation);

				Q_Forge->Forge[AIcounter].WepAttach = Q_Forge->Forge[AIcounter].Weapon.Xform;
				Qpo->Transform_SetTranslation(&Q_Forge->Forge[AIcounter].WepAttach, 0, 0, 0);

				if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3)
					{
					Q_Forge->Forge[AIcounter].WepAttach.Translation.x -= 9;
					Q_Forge->Forge[AIcounter].WepAttach.Translation.y -= 4.6;
					Q_Forge->Forge[AIcounter].WepAttach.Translation.z -= 1;

					Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].WepAttach, PI/2);
					Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].WepAttach, -(PI/4)-0.8);
					}

				if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
					{
					Q_Forge->Forge[AIcounter].WepAttach.Translation.x -= 9;
					Q_Forge->Forge[AIcounter].WepAttach.Translation.y -= 4.6;
					Q_Forge->Forge[AIcounter].WepAttach.Translation.z -= 1;

					//Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].WepAttach, PI/2);
					Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].WepAttach, -(PI/4)-0.8);
					}


				if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF != 4 && Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF != 3)
					{
					Q_Forge->Forge[AIcounter].WepAttach.Translation.x -= 0.5;
					Q_Forge->Forge[AIcounter].WepAttach.Translation.y -= 3;
					Q_Forge->Forge[AIcounter].WepAttach.Translation.z -= 1;

					Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].WepAttach, PI/2);
					Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].WepAttach, -(PI/4)-0.35);
					}

				//~##~Qpo->Avatar_Attach(&Q_Forge->Forge[AIcounter].Weapon.Avatar, "BONE01", &playerAV[g_Player]->Avatar, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].WepAttach);
				}

			if(Q_Forge->Forge[AIcounter].blendamount[25]+ (0.5*_->TimeScale) <=1) Q_Forge->Forge[AIcounter].blendamount[25] += 0.5*_->TimeScale;
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 2)	//Draw Weapon Part Two
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(Q_Forge->Forge[AIcounter].attposecnt + Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness *(0.08*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75)) <= 1.0) Q_Forge->Forge[AIcounter].attposecnt += Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness * 0.08*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75);	//0.02
			else
				{
				Q_Forge->Forge[AIcounter].WepAlpha = 255;
				Q_Forge->Forge[AIcounter].attposecnt = 1.0;
				Q_Forge->Forge[AIcounter].WeaponStatus = 3;
				}

			if(Q_Forge->Forge[AIcounter].WepAlpha+40 <= 255) Q_Forge->Forge[AIcounter].WepAlpha += 40;
			else Q_Forge->Forge[AIcounter].WepAlpha = 255;

			Qpo->Mesh_SetAlpha(&Q_Forge->Forge[AIcounter].Weapon, Q_Forge->Forge[AIcounter].WepAlpha);
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 3)	//Weapon On Shoulder
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(_->lbutton[g_Player] == 1 && _->NetworkOption != 1)
				{
				Q_Forge->Forge[AIcounter].WeaponStatus = 4;
				Q_Forge->Forge[AIcounter].WepAlpha = 0;
				}

			if((KEY_PRESS_DOWN(QIN_TAB)) && _->NetworkOption != 1)
				{
				Q_Forge->Forge[AIcounter].attposecnt = 1.0;
				Q_Forge->Forge[AIcounter].WeaponStatus = 7;
				Q_Forge->Forge[AIcounter].blendamount[25] = 0;
				}

			if(Q_Forge->Forge[AIcounter].blendamount[25]+ (0.3*_->TimeScale) <=1) Q_Forge->Forge[AIcounter].blendamount[25] += 0.3*_->TimeScale;
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 4)	//Aim Weapon
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(Q_Forge->Forge[AIcounter].attposecnt + Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness *(0.15*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75)) <= 2.27) Q_Forge->Forge[AIcounter].attposecnt += Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness * 0.15*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75);	//0.12	//0.08
			else
				{
				Q_Forge->Forge[AIcounter].attposecnt = 2.27;
				Q_Forge->Forge[AIcounter].WepIdle = 0;
				Q_Forge->Forge[AIcounter].WeaponStatus = 5;
				Q_Forge->Forge[AIcounter].blendamount[25]=0;
				Q_Forge->Forge[AIcounter].WeaponFire = 0;
				}

			if(Q_Forge->Forge[AIcounter].WepAlpha+5 <= 150) Q_Forge->Forge[AIcounter].WepAlpha += 5;
			else Q_Forge->Forge[AIcounter].WepAlpha = 95;		//Laser sight alpha value
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 5)	//Fire Weapon
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[136], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[35], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].In);

			
				if(!KEY_PRESS_DOWN(QIN_r)) Q_Forge->Forge[AIcounter].attposecnt = ((Q_Forge->Forge[AIcounter].In.y*-1.6)+0.4)-Q_Forge->Forge[AIcounter].WeaponRecoil;
			

							//    V---  Adjust fire rate here	2 is FIRE , NOT , FIRE
			if(Q_Forge->Forge[AIcounter].FireRate >= (1 - ((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].FireRate / 5000)) * 36) Q_Forge->Forge[AIcounter].FireRate = 0;
			else if(Q_Forge->Forge[AIcounter].FireRate > 0) Q_Forge->Forge[AIcounter].FireRate += 1 * _->TimeScale;

			if(((!(_->lbutton[g_Player]) && Q_Forge->Forge[AIcounter].WeaponFire == 0) || _->NetworkOption == 1) /*|| (_->NetworkOption == 1*/) Q_Forge->Forge[AIcounter].WepIdle++;
			else
				{
				Q_Forge->Forge[AIcounter].WeaponFire = 0;
				Q_Forge->Forge[AIcounter].WepIdle = 0;

				if(Q_Forge->Forge[AIcounter].FireRate == 0)	//FIRE!
					{
					Q_Forge->Forge[AIcounter].FireRate = 1;

					if(_->NetworkOption != 1)
						{
						Q_Forge->Forge[AIcounter].MFlash = 1;
						Q_Forge->Forge[AIcounter].NETMFlash = 1;
						}

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &Q_Forge->Forge[AIcounter].OAttPos);
					Q_Forge->Forge[AIcounter].OAttPos.Translation.z -= 0.2;	//6
					Q_Forge->Forge[AIcounter].OAttPos.Translation.y -= 0.133;	//4
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &Q_Forge->Forge[AIcounter].OAttPos);

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &Q_Forge->Forge[AIcounter].OAttPos);
					Q_Forge->Forge[AIcounter].OAttPos.Translation.z -= 0.2;
					Q_Forge->Forge[AIcounter].OAttPos.Translation.y -= 0.133;
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &Q_Forge->Forge[AIcounter].OAttPos);

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &Q_Forge->Forge[AIcounter].OAttPos);
					Q_Forge->Forge[AIcounter].OAttPos.Translation.z -= 0.2;
					Q_Forge->Forge[AIcounter].OAttPos.Translation.y -= 0.133;
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &Q_Forge->Forge[AIcounter].OAttPos);

					Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &Q_Forge->Forge[AIcounter].OAttPos);
					Q_Forge->Forge[AIcounter].OAttPos.Translation.z -= 0.2;
					Q_Forge->Forge[AIcounter].OAttPos.Translation.y -= 0.133;
					Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[20], &Q_Forge->Forge[AIcounter].OAttPos);

					//Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AIcounter].Weapon.Avatar.Pose, 0, &Q_Forge->Forge[AIcounter].AttPos);
					Q_Forge->Forge[AIcounter].OAttPos.Translation.z -= 0.2;
					Q_Forge->Forge[AIcounter].OAttPos.Translation.y -= 0.133;
					//Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AIcounter].Weapon.Avatar.Pose, 0, &Q_Forge->Forge[AIcounter].OAttPos);

					//# Recoil
					if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
						{
						Q_Forge->Forge[AIcounter].WeaponRecoil += 0.1 * ( (((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].RecoilHeight / 5000) * 2) / 2);
						Q_Forge->Forge[AIcounter].WeaponRecoil -= (Q_Forge->Forge[AIcounter].WeaponRecoil * Q_Forge->Forge[AIcounter].WeaponRecoil) * ((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover/2500)+0.1);
						if(Q_Forge->Forge[AIcounter].WeaponRecoil < 0) Q_Forge->Forge[AIcounter].WeaponRecoil = 0;
						}
					else
						{
						Q_Forge->Forge[AIcounter].WeaponRecoil += 0.3 * ( (((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].RecoilHeight / 5000) * 2) / 2);
						Q_Forge->Forge[AIcounter].WeaponRecoil -= (Q_Forge->Forge[AIcounter].WeaponRecoil * Q_Forge->Forge[AIcounter].WeaponRecoil) * ((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover/2500)+0.1);
						if(Q_Forge->Forge[AIcounter].WeaponRecoil < 0) Q_Forge->Forge[AIcounter].WeaponRecoil = 0;
						//IMP ADDED STATEMENT
						}

					//### Movement Recoil
					Qpo->Avatar_GetWeaponTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].TempXForm1);
					Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Forge->Forge[AIcounter].In);

					Q_Forge->Forge[AIcounter].MoveReactVec = Q_Forge->Forge[AIcounter].In;
					if(Q_Forge->Forge[AIcounter].MoveReactVec.y < 0) Q_Forge->Forge[AIcounter].MoveReactVec.y = 0;
					Q_Forge->Forge[AIcounter].MoveReactSpeed = 20 * ( (((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].RecoilDistance / 5000) * 10) / 15);

					//# Ammo Check
					if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2) Q_Forge->Forge[AIcounter].WeaponAmmo -= 0.2 / (((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Ammo / 5000) * 10);
					else Q_Forge->Forge[AIcounter].WeaponAmmo -= 1 / (((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Ammo / 5000) * 10);

					if(Q_Forge->Forge[AIcounter].WeaponAmmo <= 0)
						{
						Q_Forge->Forge[AIcounter].WeaponStatus = 8;
						Q_Forge->Forge[AIcounter].attposecnt = 0;
						Q_Forge->Forge[AIcounter].blendamount[58] = 0;
						}
					}
				}

			if(Q_Forge->Forge[AIcounter].MFlash == 0)
				{
				if(Q_Forge->Forge[AIcounter].WeaponRecoil - (0.03 * _->TimeScale * (((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover/5000)*3)+1)) >= 0) Q_Forge->Forge[AIcounter].WeaponRecoil -= (0.03 * _->TimeScale * (((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover/5000)*2)+1));
				else Q_Forge->Forge[AIcounter].WeaponRecoil = 0;
				}

			if(Q_Forge->Forge[AIcounter].WepIdle >= 1000)
				{
				Q_Forge->Forge[AIcounter].attposecnt = 3.30;
				Q_Forge->Forge[AIcounter].WeaponStatus = 6;
				}

			if((KEY_PRESS_DOWN(QIN_TAB)) && _->NetworkOption != 1)
				{
				Q_Forge->Forge[AIcounter].attposecnt = 1.0;
				Q_Forge->Forge[AIcounter].WeaponStatus = 3;
				Q_Forge->Forge[AIcounter].blendamount[25] = 0;
				}

			if(Q_Forge->Forge[AIcounter].blendamount[25]+ (0.3*_->TimeScale) <=1) Q_Forge->Forge[AIcounter].blendamount[25] += 0.3*_->TimeScale;
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 6)	//Weapon To Shoulder
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(Q_Forge->Forge[AIcounter].attposecnt + Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness *(0.02*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75)) <= 3.67) Q_Forge->Forge[AIcounter].attposecnt += Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness * 0.02*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75);
			else
				{
				Q_Forge->Forge[AIcounter].attposecnt = 1.0;
				Q_Forge->Forge[AIcounter].WeaponStatus = 3;
				}
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 7)	//Holster Weapon
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[134], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[34], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(Q_Forge->Forge[AIcounter].attposecnt <= 0.35) Q_Forge->Forge[AIcounter].Backpack.Draw = 1;

			if(Q_Forge->Forge[AIcounter].attposecnt-(0.08*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75)*Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness) >= 0) Q_Forge->Forge[AIcounter].attposecnt -= 0.08*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD/5000)*0.75)*Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness;
			else
				{
				Q_Forge->Forge[AIcounter].WeaponStatus = 0;
				Q_Forge->Forge[AIcounter].attposecnt = 0;
				Q_Forge->Forge[AIcounter].Aposestate = 0;
				Q_Forge->Forge[AIcounter].blendamount[25] = 0;
				Q_Forge->Forge[AIcounter].blendamount[0] = 0;
				Q_Forge->Forge[AIcounter].attackon = 0;
				Q_Forge->Forge[AIcounter].WeaponATTACHFLAG = 0;
				//Qpo->Avatar_Detach(&Q_Forge->Forge[AIcounter].Weapon.Avatar);
				Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AIcounter].Weapon.Xform.Translation);
				Q_Forge->Forge[AIcounter].WepAlpha = 0;
				}

			if(Q_Forge->Forge[AIcounter].WepAlpha-40 >= 0) Q_Forge->Forge[AIcounter].WepAlpha -= 40;
			else Q_Forge->Forge[AIcounter].WepAlpha = 0;

			Qpo->Mesh_SetAlpha(&Q_Forge->Forge[AIcounter].Weapon, Q_Forge->Forge[AIcounter].WepAlpha);
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus == 8)	//Reload Weapon
			{
			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[138], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}
			else
				{
				Qpo->Avatar_SetPosePM(playerAV[g_Player]->Avatar, playerAV[g_Player]->Motion[125], Q_Forge->Forge[AIcounter].attposecnt, NULL);
				}

			if(Q_Forge->Forge[AIcounter].ReloadPos == 0)
				{
				Q_Forge->Forge[AIcounter].ReloadPos++;
				//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'BOLT SLAP' SOUND
				Qpo->Sound_Play(Medias->S_RifleBoltOut[Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].QAS_ReloadBoltOut], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
				}

			if(Q_Forge->Forge[AIcounter].ReloadPos == 1)
				{
				if(Q_Forge->Forge[AIcounter].attposecnt > 0.13)
					{
					Q_Forge->Forge[AIcounter].ReloadPos++;
					//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'BOLT SLAP' SOUND
					Qpo->Sound_Play(Medias->S_RifleClipOut[Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].QAS_ReloadClipOut], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
					}
				}

			if(Q_Forge->Forge[AIcounter].ReloadPos == 2)
				{
				if(Q_Forge->Forge[AIcounter].attposecnt > 0.69)
					{
					Q_Forge->Forge[AIcounter].ReloadPos++;
					//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'BOLT SLAP' SOUND
					Qpo->Sound_Play(Medias->S_RifleClipIn[Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].QAS_ReloadClipIn], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
					}
				}

			if(Q_Forge->Forge[AIcounter].ReloadPos == 3)
				{
				if(Q_Forge->Forge[AIcounter].attposecnt > 0.85)
					{
					Q_Forge->Forge[AIcounter].ReloadPos++;
					//QpoSound3D_GetConfig(World, &Q_Forge->Forge[AIcounter].ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'BOLT SLAP' SOUND
					Qpo->Sound_Play(Medias->S_RifleBoltIn[Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].QAS_ReloadBoltIn], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
					}
				}

			if(Q_Forge->Forge[AIcounter].attposecnt >= 0.4 && Q_Forge->Forge[AIcounter].attposecnt < 0.7) Q_Forge->Forge[AIcounter].Backpack.Draw = 1;

			if(Q_Forge->Forge[AIcounter].attposecnt + Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness *(0.02*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD/5000)*4)) <= 1.00) Q_Forge->Forge[AIcounter].attposecnt += Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness * 0.02*_->TimeScale*((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD/5000)*4);	//0.05
			else
				{
				Q_Forge->Forge[AIcounter].attposecnt = 2.27;
				Q_Forge->Forge[AIcounter].WepIdle = 0;
				Q_Forge->Forge[AIcounter].WeaponStatus = 5;
				Q_Forge->Forge[AIcounter].blendamount[25]=0;
				Q_Forge->Forge[AIcounter].WeaponAmmo = 32;
				Q_Forge->Forge[AIcounter].ReloadPos = 0;
				}

			if(Q_Forge->Forge[AIcounter].blendamount[58]+ (0.3*_->TimeScale) <=1) Q_Forge->Forge[AIcounter].blendamount[58] += 0.3*_->TimeScale;
			else Q_Forge->Forge[AIcounter].blendamount[58] = 1;
			}


		if(Q_Forge->Forge[AIcounter].WeaponStatus != 0)
			{
			//##### Body Rotation
			Q_Forge->Forge[AIcounter].BodyRotation = Q_Forge->Forge[AIcounter].Angles.y - (Q_Forge->Forge[AIcounter].Vehicle.Angles.y + (PI/4) + (PI/8));

			//Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[17], &Q_Forge->Forge[AIcounter].TempXForm1);
			//Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].TempXForm1, Q_Forge->Forge[AIcounter].BodyRotation/3);
			//Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[17], &Q_Forge->Forge[AIcounter].TempXForm1);

			Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &Q_Forge->Forge[AIcounter].TempXForm1);
			Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].TempXForm1, Q_Forge->Forge[AIcounter].BodyRotation/2);
			Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[18], &Q_Forge->Forge[AIcounter].TempXForm1);

			Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &Q_Forge->Forge[AIcounter].TempXForm1);
			Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].TempXForm1, Q_Forge->Forge[AIcounter].BodyRotation/2);
			Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, qBoneNum[19], &Q_Forge->Forge[AIcounter].TempXForm1);
			}


			//##### MAKE SURE TO RENDER WEAPON IN ALL CASES
		if(Q_Forge->Forge[AIcounter].WeaponStatus != 0)
			{
			if(Q_Forge->Forge[AIcounter].WeaponATTACHFLAG == 1)
				{
				//Qpo->Avatar_SetBoneAttach(&Q_Forge->Forge[AIcounter].Vehicle.Model.Avatar, "BONE01", &Q_Forge->Forge[AIcounter].Vehicle.AttachMat);
				//Qpo->Avatar_SetBoneAttach(&Q_Forge->Forge[AIcounter].Weapon.Avatar, "BONE01", &Q_Forge->Forge[AIcounter].WepAttach);
				}

			//Qpo->Avatar_ClearPose(Q_Forge->Forge[AIcounter].Weapon.Avatar, &Q_Forge->Forge[AIcounter].Weapon.Xform);

			if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 0)
				{
				Qpo->Mesh_SetScale(&Q_Forge->Forge[AIcounter].Weapon, 1.2 + ((0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)) * 2.7907));
				}
			else
				{
				Qpo->Mesh_SetScale(&Q_Forge->Forge[AIcounter].Weapon, 1.2 + ((0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)) * 2.7907), 1.2 + ((0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)) * 2.7907));
				}
			}

		//Aim Weapon
		if(Q_Forge->Forge[AIcounter].WeaponStatus == 4 || Q_Forge->Forge[AIcounter].WeaponStatus == 5 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24)
			{
			Qpo->Avatar_GetWeaponTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].AttPos);
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AttPos,&Q_Forge->Forge[AIcounter].AimVec);
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AttPos,&Q_Forge->Forge[AIcounter].AimVecUp);
			Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AttPos,&Q_Forge->Forge[AIcounter].In);
			Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AimVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AttPos.Translation, Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].LaserLOC.z, &Q_Forge->Forge[AIcounter].AimVec, &Q_Forge->Forge[AIcounter].AttPos.Translation);			//1
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AttPos.Translation, Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].LaserLOC.y, &Q_Forge->Forge[AIcounter].AimVecUp, &Q_Forge->Forge[AIcounter].AttPos.Translation);		//-4.5
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AttPos.Translation, Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].LaserLOC.x, &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].AttPos.Translation);		//-4.5
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AttPos.Translation, 2000, &Q_Forge->Forge[AIcounter].AimVec, &Q_Forge->Forge[AIcounter].OAttPos.Translation);

			if(Qpo->Collision_RayTest(
				 NULL,
				 NULL,
				 &Q_Forge->Forge[AIcounter].AttPos.Translation, 
				 &Q_Forge->Forge[AIcounter].OAttPos.Translation, 
				 // GE_CONTENTS_CANNOT_OCCUPY
				 /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
				 0xffffffff, NULL, NULL, 
				 &Q_Forge->Forge[AIcounter].Collision))
				{
				// Set the new pos to the point of collision
				Q_Forge->Forge[AIcounter].OAttPos.Translation.acSet(Q_Forge->Forge[AIcounter].Collision.Impact.m_X, Q_Forge->Forge[AIcounter].Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].Collision.Impact.m_Z);

				Q_Forge->Forge[AIcounter].LaserLV.a = 130;
				Q_Forge->Forge[AIcounter].LaserLV.r = 255;
				Q_Forge->Forge[AIcounter].LaserLV.g = 255;			//alpha values and colour
				Q_Forge->Forge[AIcounter].LaserLV.b = 255;
				Q_Forge->Forge[AIcounter].LaserLV.x = Q_Forge->Forge[AIcounter].Collision.Impact.m_X;
				Q_Forge->Forge[AIcounter].LaserLV.y = Q_Forge->Forge[AIcounter].Collision.Impact.m_Y;
				Q_Forge->Forge[AIcounter].LaserLV.z = Q_Forge->Forge[AIcounter].Collision.Impact.m_Z;
				if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].LaserTYPE >= 2) Qpo->Poly_AddOnce(&Q_Forge->Forge[AIcounter].LaserLV, 1, Medias->spec, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.04f);
				}

			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].LaserTYPE >= 1) Q.ShowLine(&Q_Forge->Forge[AIcounter].AttPos.Translation, &Q_Forge->Forge[AIcounter].OAttPos.Translation, &Q_Forge->Forge[AIcounter].ViewXForm.Translation, 0.6, Medias->LaserSight, Q_Forge->Forge[AIcounter].WepAlpha, 255, 0, 0, 0);
			}


		//### CONDITIONAL WEAPON ATTACH ###
		if((Q_Forge->Forge[AIcounter].WeaponStatus > 1) && (Q_Forge->Forge[AIcounter].WeaponStatus != 7) && (Q_Forge->Forge[AIcounter].WeaponATTACHFLAG == 0))
			{
			Q_Forge->Forge[AIcounter].WeaponATTACHFLAG = 1;

			Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].OAttPos.Translation, &Q_Forge->Forge[AIcounter].Weapon.Xform.Translation);
			Q_Forge->Forge[AIcounter].WepAttach = Q_Forge->Forge[AIcounter].Weapon.Xform;
			Qpo->Transform_SetTranslation(&Q_Forge->Forge[AIcounter].WepAttach, 0, 0, 0);

			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3)
				{
				Q_Forge->Forge[AIcounter].WepAttach.Translation.x -= 9;
				Q_Forge->Forge[AIcounter].WepAttach.Translation.y -= 4.6;
				Q_Forge->Forge[AIcounter].WepAttach.Translation.z -= 1;

				Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].WepAttach, PI/2);
				Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].WepAttach, -(PI/4)-0.8);
				}

			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)
				{
				Q_Forge->Forge[AIcounter].WepAttach.Translation.x -= 9;
				Q_Forge->Forge[AIcounter].WepAttach.Translation.y -= 4.6;
				Q_Forge->Forge[AIcounter].WepAttach.Translation.z -= 1;

				//Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].WepAttach, PI/2);
				Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].WepAttach, -(PI/4)-0.8);
				}

			if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF != 4 && Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF != 3)
				{
				Q_Forge->Forge[AIcounter].WepAttach.Translation.x -= 0.5;
				Q_Forge->Forge[AIcounter].WepAttach.Translation.y -= 3;
				Q_Forge->Forge[AIcounter].WepAttach.Translation.z -= 1;

				Qpo->Transform_RotateX(&Q_Forge->Forge[AIcounter].WepAttach, PI/2);
				Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].WepAttach, -(PI/4)-0.35);
				}

			//~##~Qpo->Avatar_Attach(&Q_Forge->Forge[AIcounter].Weapon.Avatar, "BONE01", &playerAV[g_Player]->Avatar, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].WepAttach);
			}
		}


	if(KEY_PRESS_DOWN(QIN_TAB))	//****////WEAPON\\\\****
		{
		if(Q_Forge->Forge[AIcounter].WeaponStatus == 0)
			{
			Q_Forge->Forge[AIcounter].Aposestate = 20;
			Q_Forge->Forge[AIcounter].attposecnt = 0;
			Q_Forge->Forge[AIcounter].WeaponStatus = 1;

			Q_Forge->Forge[AIcounter].WepAlpha = 0;
			Qpo->Mesh_SetAlpha(&Q_Forge->Forge[AIcounter].Weapon, 0);
			}
		}

}

};