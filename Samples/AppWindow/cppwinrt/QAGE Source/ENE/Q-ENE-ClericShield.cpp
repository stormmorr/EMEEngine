/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Cleric Shield-

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
#include "Q-WE-BulletSystem.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-WE-PntSprite.h"
#include "Q-Prototypes.h"
#include "Q-AI-NNbot.h"

using namespace GVARS;

namespace GVARS
{

	//########  - Player Shield Control -  ########//

void Q_COREFunctions::CONTROL_PlayerClericShieldControl(void)
	{
	if(player[g_Player]->Cleric.ShieldOn == 1)
		{
		if(player[g_Player]->HB_Energy > 0)
			{
			if(player[g_Player]->Cleric.ShieldAlpha + (15 * _->TimeScale) < 100) player[g_Player]->Cleric.ShieldAlpha += (15 * _->TimeScale);
			else player[g_Player]->Cleric.ShieldAlpha = 100;

			Qpo->Avatar_SetLighting(&player[g_Player]->Shield.Avatar,false,&goup,230,230,230,220,220,220,false,0,NULL,false);

			//### Check for avatars within shield
			jet=0;
			while(jet < _->NomAI /*&& player[g_Player]->Cleric.ShieldCNT > 1*/ && _->NetworkOption != 1)
				{
				if(Q_Forge->Forge[jet].LIVE == 1)
					{
					if(Q_Forge->Forge[jet].Team != player[g_Player]->Team)
						{
						TESTPosS = Q_Forge->Forge[jet].AV.Xform.Translation;
						TESTPosS.y += 60;
						TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

						Qpo->Vec3d_Subtract(&TESTPosS, &player[g_Player]->Shield.Xform.Translation, &TESTPosE);

						if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
							{
							TESTLength = Qpo->Vec3d_Length(&TESTPosE);
							Qpo->Vec3d_Normalize(&TESTPosE);
							Q_Forge->Forge[jet].MoveReactVec = TESTPosE;
							Q_Forge->Forge[jet].MoveReactSpeed = 65 * player[g_Player]->Cleric.ShieldScale - TESTLength;
							Q_Forge->Forge[jet].HitShield = 1;
							}
						}
					}
				jet++;
				}


			//### Check for NNBOTS Within shield
			jet=0;
			while(jet < _->NomNNBots && _->NetworkOption != 1)
				{
				if(Q_NNBot->NNBot[jet].LIVE == 1)
					{
					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&Q_NNBot->NNBot[jet].Pos, &player[g_Player]->Shield.Xform.Translation);

					Qpo->Vec3d_Subtract(&Q_NNBot->NNBot[jet].Pos, &player[g_Player]->Shield.Xform.Translation, &TESTPosE);

					if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
						{
						TESTLength = Qpo->Vec3d_Length(&TESTPosE);
						Qpo->Vec3d_Normalize(&TESTPosE);
						Q_NNBot->NNBot[jet].TraVec = TESTPosE;
						Q_NNBot->NNBot[jet].Direction = 0;
						Q_NNBot->NNBot[jet].Speed = 65 * player[g_Player]->Cleric.ShieldScale - TESTLength;
						}
					}

				jet++;
				}
			}
		else
			{
			if(player[g_Player]->Cleric.ShieldAlpha - (2 * _->TimeScale) > 15) player[g_Player]->Cleric.ShieldAlpha -= (2 * _->TimeScale);
			else
				{
				player[g_Player]->Cleric.ShieldAlpha = 15;

				player[g_Player]->Cleric.ShieldOn = 0;

				if(_->NetworkOption == 2) player[g_Player]->EnergySWITCHOFF = 1;
				if(_->NetworkOption == 1) player[g_Player]->EnergySWITCHOFF = 0;
				player[g_Player]->attposecnt = 0;
				player[g_Player]->Aposestate = 0;
				player[g_Player]->blendamount[85] = 0;
				player[g_Player]->attackon = 0;
				player[g_Player]->EnergyInitialise = 0;
				player[g_Player]->EnergyCounter = 0;

				//
					//'Jink'
				Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
				}

			Qpo->Avatar_SetLighting(&player[g_Player]->Shield.Avatar,false,&goup,255,50,50,255,50,50,false,0,NULL,false);
			}

		if(player[g_Player]->Cleric.ShieldGROW == 0)
			{
			if((player[g_Player]->Cleric.ShieldScale + (((0.1 + (((float)rand() / 32767) * 0.15)) * _->TimeScale) * (1 + ((10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)) * (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000))))) < (1 + ((10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)) * (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000))))) && (player[g_Player]->Cleric.ShieldGROW == 0)) player[g_Player]->Cleric.ShieldScale += (((0.1 + (((float)rand() / 32767) * 0.15)) * _->TimeScale) * (1 + ((10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)) * (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)))));
			else
				{
				player[g_Player]->Cleric.ShieldScale = (1 + ((10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)) * (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000))));

				if(player[g_Player]->Cleric.ShieldCNT < 2)
					{
					player[g_Player]->Cleric.ShieldCNT++;
					player[g_Player]->Cleric.ShieldAlpha = 20;
					player[g_Player]->Cleric.ShieldScale = ((float)rand() / 32767) * (1 + ((10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)) * (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000))));
					}
				else player[g_Player]->Cleric.ShieldGROW = 1;
				}
			}
		else
			{
			player[g_Player]->Cleric.ShieldScale = (1 + ((10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000)) * (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Potency/5000))));
			player[g_Player]->Cleric.ShieldScale += ((((float)rand() / 32767) - 0.5) * 0.1);
			}
		}
	else
		{
		if(player[g_Player]->Cleric.ShieldAlpha - (27 * _->TimeScale) >= 0) player[g_Player]->Cleric.ShieldAlpha += (27 * _->TimeScale);
		else player[g_Player]->Cleric.ShieldAlpha = 0;

		if(player[g_Player]->Cleric.ShieldScale - (0.5 * _->TimeScale) >= 0) player[g_Player]->Cleric.ShieldScale -= (0.5 * _->TimeScale);
		else
			{
			player[g_Player]->Cleric.ShieldScale = 0;
			player[g_Player]->Cleric.ShieldGROW = 0;
			}
		}

	if(player[g_Player]->Cleric.ShieldAlpha > 0)
		{
		//### Set Shield Position
		player[g_Player]->Shield.Xform.Translation = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->Shield.Xform.Translation.y += 60;

		//### Set Shield Alpha
		Qpo->Avatar_SetAlpha(&player[g_Player]->Shield.Avatar, player[g_Player]->Cleric.ShieldAlpha);

		//### Set Shield Scale
		Qpo->Avatar_SetScale(&player[g_Player]->Shield.Avatar, player[g_Player]->Cleric.ShieldScale,player[g_Player]->Cleric.ShieldScale,player[g_Player]->Cleric.ShieldScale);

		//### Shield Material Counters
		
		if(player[g_Player]->Cleric.ShieldCNT > 1)
			{
			if(player[g_Player]->Cleric.ShieldMATCNT + 1 < 11) player[g_Player]->Cleric.ShieldMATCNT++;
			else player[g_Player]->Cleric.ShieldMATCNT = 1;
			Qpo->Avatar_GetTex(&player[g_Player]->Shield.Avatar, player[g_Player]->Cleric.ShieldMATCNT, player[g_Player]->Cleric.SBitmap, &player[g_Player]->Cleric.SBitmapRed, &player[g_Player]->Cleric.SBitmapGreen, &player[g_Player]->Cleric.SBitmapBlue);
			Qpo->Avatar_SetTex(&player[g_Player]->Shield.Avatar, 0, player[g_Player]->Cleric.SBitmap, &player[g_Player]->Cleric.SBitmapRed, &player[g_Player]->Cleric.SBitmapGreen, &player[g_Player]->Cleric.SBitmapBlue);
			}

		//### Clear Shield Pose
		Qpo->Avatar_ClearPose(player[g_Player]->Shield.Avatar, &player[g_Player]->Shield.Xform);
		}
	else player[g_Player]->Shield.Xform.Translation = _->Origon;
	}


void Q_COREFunctions::CONTROL_AvatarClericShieldControl(int SCRAMr)
	{
	if(Q_Forge->Forge[SCRAMr].Cleric.ShieldOn == 1)
		{
		if(Q_Forge->Forge[SCRAMr].HB_Energy > 0)
			{
			if(Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha + (15 * _->TimeScale) < 100) Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha += (15 * _->TimeScale);
			else Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha = 100;

			Qpo->Avatar_SetLighting(&Q_Forge->Forge[SCRAMr].Shield.Avatar,false,&goup,230,230,230,220,220,220,false,0,NULL,false);

			//### Check for player within shield
			if((player[g_Player]->Team != Q_Forge->Forge[SCRAMr].Team && _->NetworkOption != 1) /*&& (Q_Forge->Forge[SCRAMr].Cleric.ShieldCNT > 1)*/)
				{
				TESTPosS = playerAV[g_Player]->Xform.Translation;
				TESTPosS.y += 60;
				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAMr].Shield.Xform.Translation);

				Qpo->Vec3d_Subtract(&TESTPosS, &Q_Forge->Forge[SCRAMr].Shield.Xform.Translation, &TESTPosE);

				if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAMr].Cleric.ShieldScale))
					{
					TESTLength = Qpo->Vec3d_Length(&TESTPosE);
					Qpo->Vec3d_Normalize(&TESTPosE);
					player[g_Player]->MoveReactVec = TESTPosE;
					player[g_Player]->MoveReactSpeed = 65 * Q_Forge->Forge[SCRAMr].Cleric.ShieldScale - TESTLength;
					player[g_Player]->HitShield = 1;
					}
				}

			//### Check for avatars within shield
			jet=0;
			while(jet < _->NomAI /*&& Q_Forge->Forge[SCRAMr].Cleric.ShieldCNT > 1*/ && _->NetworkOption != 1)
				{
				if(Q_Forge->Forge[jet].LIVE == 1)
					{
					if(Q_Forge->Forge[jet].Team != Q_Forge->Forge[SCRAMr].Team)
						{
						TESTPosS = Q_Forge->Forge[jet].AV.Xform.Translation;
						TESTPosS.y += 60;
						TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAMr].Shield.Xform.Translation);

						Qpo->Vec3d_Subtract(&TESTPosS, &Q_Forge->Forge[SCRAMr].Shield.Xform.Translation, &TESTPosE);

						if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAMr].Cleric.ShieldScale))
							{
							TESTLength = Qpo->Vec3d_Length(&TESTPosE);
							Qpo->Vec3d_Normalize(&TESTPosE);
							Q_Forge->Forge[jet].MoveReactVec = TESTPosE;
							Q_Forge->Forge[jet].MoveReactSpeed = 65 * Q_Forge->Forge[SCRAMr].Cleric.ShieldScale - TESTLength;
							Q_Forge->Forge[jet].HitShield = 1;
							}
						}
					}
				jet++;
				}


			//### Check for NNBOTS Within shield
			jet=0;
			while(jet < _->NomNNBots && _->NetworkOption != 1)
				{
				if(Q_NNBot->NNBot[jet].LIVE == 1)
					{
					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&Q_NNBot->NNBot[jet].Pos, &Q_Forge->Forge[SCRAMr].Shield.Xform.Translation);

					Qpo->Vec3d_Subtract(&Q_NNBot->NNBot[jet].Pos, &Q_Forge->Forge[SCRAMr].Shield.Xform.Translation, &TESTPosE);

					if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAMr].Cleric.ShieldScale))
						{
						TESTLength = Qpo->Vec3d_Length(&TESTPosE);
						Qpo->Vec3d_Normalize(&TESTPosE);
						Q_NNBot->NNBot[jet].TraVec = TESTPosE;
						Q_NNBot->NNBot[jet].Direction = 0;
						Q_NNBot->NNBot[jet].Speed = 65 * Q_Forge->Forge[SCRAMr].Cleric.ShieldScale - TESTLength;
						}
					}

				jet++;
				}
			}
		else
			{
			if(Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha - (2 * _->TimeScale) > 15) Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha -= (2 * _->TimeScale);
			else
				{
				Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha = 15;

				Q_Forge->Forge[AIcount].Cleric.ShieldOn = 0;

				if(_->NetworkOption == 2) Q_Forge->Forge[AIcount].EnergySWITCHOFF = 1;
				if(_->NetworkOption == 1) Q_Forge->Forge[AIcount].EnergySWITCHOFF = 0;
				Q_Forge->Forge[AIcount].attposecnt = 0;
				Q_Forge->Forge[AIcount].Aposestate = 0;
				Q_Forge->Forge[AIcount].blendamount[85] = 0;
				Q_Forge->Forge[AIcount].attackon = 0;
				Q_Forge->Forge[AIcount].EnergyInitialise = 0;
				Q_Forge->Forge[AIcount].EnergyCounter = 0;

				////QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcount].AttPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcount].AttPos.Translation);
				}


			Qpo->Avatar_SetLighting(&Q_Forge->Forge[SCRAMr].Shield.Avatar,false,&goup,255,70,70,220,60,60,false,0,NULL,false);
			}

		if(Q_Forge->Forge[SCRAMr].Cleric.ShieldGROW == 0)
			{
			if((Q_Forge->Forge[SCRAMr].Cleric.ShieldScale + (((0.1 + (((float)rand() / 32767) * 0.15)) * _->TimeScale) * (1 + ((10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)) * (10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000))))) < (1 + ((10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)) * (10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000))))) && (Q_Forge->Forge[SCRAMr].Cleric.ShieldGROW == 0)) Q_Forge->Forge[SCRAMr].Cleric.ShieldScale += (((0.1 + (((float)rand() / 32767) * 0.15)) * _->TimeScale) * (1 + ((10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)) * (10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)))));
			else
				{
				Q_Forge->Forge[SCRAMr].Cleric.ShieldScale = (1 + ((10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)) * (10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000))));

				if(Q_Forge->Forge[SCRAMr].Cleric.ShieldCNT < 2)
					{
					Q_Forge->Forge[SCRAMr].Cleric.ShieldCNT++;
					Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha = 20;
					Q_Forge->Forge[SCRAMr].Cleric.ShieldScale = ((float)rand() / 32767) * (1 + ((10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)) * (10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000))));
					}
				else Q_Forge->Forge[SCRAMr].Cleric.ShieldGROW = 1;
				}
			}
		else
			{
			Q_Forge->Forge[SCRAMr].Cleric.ShieldScale = (1 + ((10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000)) * (10 * (Q_Forge->Forge[SCRAMr].CharDATA.CLSClericSKILL[7].Potency/5000))));
			Q_Forge->Forge[SCRAMr].Cleric.ShieldScale += ((((float)rand() / 32767) - 0.5) * 0.1);
			}
		}
	else
		{
		if(Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha - (27 * _->TimeScale) >= 0) Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha += (27 * _->TimeScale);
		else Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha = 0;

		if(Q_Forge->Forge[SCRAMr].Cleric.ShieldScale - (0.5 * _->TimeScale) >= 0) Q_Forge->Forge[SCRAMr].Cleric.ShieldScale -= (0.5 * _->TimeScale);
		else
			{
			Q_Forge->Forge[SCRAMr].Cleric.ShieldScale = 0;
			Q_Forge->Forge[SCRAMr].Cleric.ShieldGROW = 0;
			}
		}

	if(Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha > 0)
		{
		//### Set Shield Position
		Q_Forge->Forge[SCRAMr].Shield.Xform.Translation = Q_Forge->Forge[SCRAMr].AV.Xform.Translation;
		Q_Forge->Forge[SCRAMr].Shield.Xform.Translation.y += 60;

		//### Set Shield Alpha
		Qpo->Avatar_SetAlpha(&Q_Forge->Forge[SCRAMr].Shield.Avatar, Q_Forge->Forge[SCRAMr].Cleric.ShieldAlpha);

		//### Set Shield Scale
		Qpo->Avatar_SetScale(&Q_Forge->Forge[SCRAMr].Shield.Avatar, Q_Forge->Forge[SCRAMr].Cleric.ShieldScale,Q_Forge->Forge[SCRAMr].Cleric.ShieldScale,Q_Forge->Forge[SCRAMr].Cleric.ShieldScale);

		//### Shield Material Counters
		if(Q_Forge->Forge[SCRAMr].Cleric.ShieldCNT > 1)
			{
			if(Q_Forge->Forge[SCRAMr].Cleric.ShieldMATCNT + 1 < 11) Q_Forge->Forge[SCRAMr].Cleric.ShieldMATCNT++;
			else Q_Forge->Forge[SCRAMr].Cleric.ShieldMATCNT = 1;
			Qpo->Avatar_GetTex(&Q_Forge->Forge[SCRAMr].Shield.Avatar, Q_Forge->Forge[SCRAMr].Cleric.ShieldMATCNT, Q_Forge->Forge[SCRAMr].Cleric.SBitmap, &Q_Forge->Forge[SCRAMr].Cleric.SBitmapRed, &Q_Forge->Forge[SCRAMr].Cleric.SBitmapGreen, &Q_Forge->Forge[SCRAMr].Cleric.SBitmapBlue);
			Qpo->Avatar_SetTex(&Q_Forge->Forge[SCRAMr].Shield.Avatar, 0, Q_Forge->Forge[SCRAMr].Cleric.SBitmap, &Q_Forge->Forge[SCRAMr].Cleric.SBitmapRed, &Q_Forge->Forge[SCRAMr].Cleric.SBitmapGreen, &Q_Forge->Forge[SCRAMr].Cleric.SBitmapBlue);
			}

		//### Clear Shield Pose
		Qpo->Avatar_ClearPose(Q_Forge->Forge[SCRAMr].Shield.Avatar, &Q_Forge->Forge[SCRAMr].Shield.Xform);
		}
	else Q_Forge->Forge[SCRAMr].Shield.Xform.Translation = _->Origon;
	}

};