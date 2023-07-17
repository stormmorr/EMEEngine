/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Collision Detection-
	*/#include "pch.h"/*- Minor Component -Cup Blast -

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-CORE-Avatar.h"
#include "Q-WE-PntSprite.h"

using namespace GVARS;

namespace GVARS
{

	//##### CUP BLAST #####

void Q_COREFunctions::RadialDamage(int Team, int AvID, float ExpSize, float ExpDMG, QpoVec3d ExpPos, int DirFlag, QpoVec3d Direction)
{
	float Scale;

		//### Scale the Explosion
	Scale = ExpSize * 1.2;	//3.5

	if( (Team != player[g_Player]->Team) && (player[g_Player]->HB_Dead == 0) && (player[g_Player]->Cleric.ShieldAlpha == 0) )
		{
		//### Find Distance between Avatar and Explosion
		AvatarPos = playerAV[g_Player]->Xform.Translation;
		AvatarPos.y += 65;
		Qpo->Vec3d_Subtract(&AvatarPos, &ExpPos, &DistVec);
		AvatarDist = Qpo->Vec3d_Length(&DistVec);
		Qpo->Vec3d_Normalize(&DistVec);

		//##### Player Within Shield Test
		TESTShieldFLAG = 0;
		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if((Q_Forge->Forge[SCRAM].CharDATA.Class == 2) && (Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[SCRAM].Team == player[g_Player]->Team) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
					{
					TESTPosS = AvatarPos;
					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

					if((TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale)) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
						{
						TESTShieldFLAG = 1;
						}
					}
				}

			SCRAM++;
			}

		if(TESTShieldFLAG == 0)
			{
			if(AvatarDist < (500 * Scale) && AvatarDist > (300 * Scale))
				{	//### Standard Hit Reaction
					//## Reduce Health
				player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

				player[g_Player]->HB_Health -= ((20 * ExpDMG) + (Scale * 10)) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
				if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;

				//### Experience Storage
				Q_Forge->Forge[AvID].AvatarDMGSTORE[250] += ((20 * ExpDMG) + (Scale * 10)) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);

				if(player[g_Player]->HB_Health <= 0)
					{
					player[g_Player]->HB_Health = 0;

					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,&player[g_Player]->ViewXForm.Translation,600.0f,2.0f,&Volume,&Pan,&Frequency);

					//'AVATAR DEATH' SOUND
					Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos

					if(_->TimeHole == 0) { _->TimeHole = 4;
					_->TimeRotate = 1; }

					player[g_Player]->HB_Dead = 1;

					//### Add Experience to attacking AVATAR
					if((Q_Forge->Forge[AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
						{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AvID].CDATID].UnusedXP += Q_Forge->Forge[AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

					//##### Find KO Owner
					UniversalDMGSTR = 0;

					jet = 0;
					while(jet < _->NomAI)
						{
						if(Q_Forge->Forge[jet].LIVE == 1)
							{
							if(Q_Forge->Forge[jet].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000) > UniversalDMGSTR) DeliverKOID = jet;
							}
						jet++;
						}

					g_Sp = 0;

					//##### Check All Active Avatars for XP and KO's
					SCRAM = 0;
					while(SCRAM < _->NomAI)
						{
						if(Q_Forge->Forge[SCRAM].LIVE == 1)
							{
							if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{
								//### Add Experience to attacking AVATAR
								player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								//### Force Net player to update (Net Play Only)
								if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
								}

							if(DeliverKOID == SCRAM)
								{
								//### Create Item for attacking Avatar
								Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

								if(Q_Forge->Forge[SCRAM].DecFinger <= 50)
									{
									//### CREATE NEW ITEM
									if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0)
										{
										Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);

										Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
										}
									else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);
									}
								}
							}

						SCRAM++;
						}

					//####### DEACTIVATE ITEM ATTRIBUTES
					Q.DeactivateItems();

					ag_ApplyUpdate(g_Sp);

					//### Write out CHARDATA
					//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

					//####### REACTIVATE ITEM ATTRIBUTES
					Q.ActivateItems();
					}

				player[g_Player]->HB_HReduceON = 1;

				player[g_Player]->HB_ReduceHInc = 10;
				player[g_Player]->HB_ReduceHeight = 573;
				player[g_Player]->HB_ReduceRectColor.red = 255;//100 + ( 155 * ( HitType / 10 ) );
				player[g_Player]->HB_ReduceRectColor.green = 0;
				player[g_Player]->HB_ReduceRectColor.blue = 0;
				player[g_Player]->HB_ReduceRectColor.alpha = 255;

				if(&player[g_Player]->Shadows[1].Avatar != 0)
					{
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[1].Avatar, &player[g_Player]->Shadows[1].Xform);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[2].Avatar, &player[g_Player]->Shadows[2].Xform);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[3].Avatar, &player[g_Player]->Shadows[3].Xform);
					}

				player[g_Player]->HitReactScale = 0.05;
				
				if(DirFlag == 0) player[g_Player]->MoveReactVec = DistVec;
				else player[g_Player]->MoveReactVec = Direction;
				//if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;

				player[g_Player]->MoveReactSpeed = 2 + (Scale * 3);	//2 * 3

					//## Reset Hit Wall
				player[g_Player]->HitWall = 0;

				//#### Set Flames
				//player[g_Player]->FlameHit = 1;
										
				if(player[g_Player]->Aposestate != 28)
					{
					player[g_Player]->Aposestate = 28;
					player[g_Player]->attackon = 1;
					player[g_Player]->attposecnt = 0;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					}
				else
					{
					if(player[g_Player]->attposecnt >= 0.16) player[g_Player]->attposecnt = 0.16;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					}
				}

			if(AvatarDist < (300 * Scale) && AvatarDist > (100 * Scale))
				{	//### Fall Hit Reaction

					//## Reduce Health
				player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

				player[g_Player]->HB_Health -= ((50 * ExpDMG) + (Scale * 20)) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
				if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;

				//### Experience Storage
				Q_Forge->Forge[AvID].AvatarDMGSTORE[250] += ((50 * ExpDMG) + (Scale * 20)) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);

				if(player[g_Player]->HB_Health <= 0)
					{
					player[g_Player]->HB_Health = 0;

					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,&player[g_Player]->ViewXForm.Translation,600.0f,2.0f,&Volume,&Pan,&Frequency);

					//'AVATAR DEATH' SOUND
					Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos

					if(_->TimeHole == 0) { _->TimeHole = 4;
					_->TimeRotate = 1; }

					player[g_Player]->HB_Dead = 1;

					//### Add Experience to attacking AVATAR
					if((Q_Forge->Forge[AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
						{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AvID].CDATID].UnusedXP += Q_Forge->Forge[AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

					//##### Find KO Owner
					UniversalDMGSTR = 0;

					jet = 0;
					while(jet < _->NomAI)
						{
						if(Q_Forge->Forge[jet].LIVE == 1)
							{
							if(Q_Forge->Forge[jet].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000) > UniversalDMGSTR) DeliverKOID = jet;
							}
						jet++;
						}

					//##### Check All Active Avatars for XP and KO's
					SCRAM = 0;
					while(SCRAM < _->NomAI)
						{
						if(Q_Forge->Forge[SCRAM].LIVE == 1)
							{
							if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{
								//### Add Experience to attacking AVATAR
								player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								g_Sp = Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								//### Force Net player to update (Net Play Only)
								if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
								}

							if(DeliverKOID == SCRAM)
								{
								//### Create Item for attacking Avatar
								Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

								if(Q_Forge->Forge[SCRAM].DecFinger <= 50)
									{
									//### CREATE NEW ITEM
									if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0)
										{
										Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);

										Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
										}
									else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);
									}
								}
							}

						SCRAM++;
						}

					//####### DEACTIVATE ITEM ATTRIBUTES
					Q.DeactivateItems();

					ag_ApplyUpdate(g_Sp);

					//### Write out CHARDATA
					//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

					//####### REACTIVATE ITEM ATTRIBUTES
					Q.ActivateItems();
					}

				player[g_Player]->HB_HReduceON = 1;

				player[g_Player]->HB_ReduceHInc = 10;
				player[g_Player]->HB_ReduceHeight = 573;
				player[g_Player]->HB_ReduceRectColor.red = 255;//100 + ( 155 * ( HitType / 10 ) );
				player[g_Player]->HB_ReduceRectColor.green = 0;
				player[g_Player]->HB_ReduceRectColor.blue = 0;
				player[g_Player]->HB_ReduceRectColor.alpha = 255;

				if(&player[g_Player]->Shadows[1].Avatar != 0)
					{
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[1].Avatar, &player[g_Player]->Shadows[1].Xform);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[2].Avatar, &player[g_Player]->Shadows[2].Xform);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[3].Avatar, &player[g_Player]->Shadows[3].Xform);
					}

				player[g_Player]->HitReactScale = 0.05;
										
				if(DirFlag == 0) player[g_Player]->MoveReactVec = DistVec;
				else player[g_Player]->MoveReactVec = Direction;
				//if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;

				player[g_Player]->MoveReactSpeed = 8 + (Scale * 6); //6 * 3

					//## Reset Hit Wall
				player[g_Player]->HitWall = 0;

				//#### Set Flames
				//player[g_Player]->FlameHit = 1;
										
				if(player[g_Player]->Aposestate != 30)
					{
					player[g_Player]->Aposestate = 30;
					player[g_Player]->attackon = 1;
					player[g_Player]->attposecnt = 0;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					}
				else
					{
					if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					}
				}

			if(AvatarDist < (100 * Scale))
				{	//### Heavy Full Hit Reaction

					//## Reduce Health
				/*if(player[g_Player]->HB_HReduceON == 0)*/ player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

				player[g_Player]->HB_Health -= ((100 * ExpDMG) + (Scale * 40)) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
				if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;

				//### Experience Storage
				Q_Forge->Forge[AvID].AvatarDMGSTORE[250] += ((100 * ExpDMG) + (Scale * 40)) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);

				if(player[g_Player]->HB_Health <= 0)
					{
					player[g_Player]->HB_Health = 0;

					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,&player[g_Player]->ViewXForm.Translation,600.0f,2.0f,&Volume,&Pan,&Frequency);

					//'AVATAR DEATH' SOUND
					Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation); //campos

					if(_->TimeHole == 0) { _->TimeHole = 4;
					_->TimeRotate = 1; }

					player[g_Player]->HB_Dead = 1;

					//### Add Experience to attacking AVATAR
					if((Q_Forge->Forge[AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
						{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AvID].CDATID].UnusedXP += Q_Forge->Forge[AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

					//##### Find KO Owner
					UniversalDMGSTR = 0;

					jet = 0;
					while(jet < _->NomAI)
						{
						if(Q_Forge->Forge[jet].LIVE == 1)
							{
							if(Q_Forge->Forge[jet].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000) > UniversalDMGSTR) DeliverKOID = jet;
							}
						jet++;
						}

					g_Sp = 0;

					//##### Check All Active Avatars for XP and KO's
					SCRAM = 0;
					while(SCRAM < _->NomAI)
						{
						if(Q_Forge->Forge[SCRAM].LIVE == 1)
							{
							if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{
								//### Add Experience to attacking AVATAR
								player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								//### Force Net player to update (Net Play Only)
								if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
								}

							if(DeliverKOID == SCRAM)
								{
								//### Create Item for attacking Avatar
								Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

								if(Q_Forge->Forge[SCRAM].DecFinger <= 50)
									{
									//### CREATE NEW ITEM
									if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0)
										{
										Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);

										Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
										}
									else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);
									}
								}
							}

						SCRAM++;
						}

					//####### DEACTIVATE ITEM ATTRIBUTES
					Q.DeactivateItems();

					ag_ApplyUpdate(g_Sp);

					//### Write out CHARDATA
					//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

					//####### REACTIVATE ITEM ATTRIBUTES
					Q.ActivateItems();
					}


				player[g_Player]->HB_HReduceON = 1;

				player[g_Player]->HB_ReduceHInc = 10;
				player[g_Player]->HB_ReduceHeight = 573;
				player[g_Player]->HB_ReduceRectColor.red = 255;//100 + ( 155 * ( HitType / 10 ) );
				player[g_Player]->HB_ReduceRectColor.green = 0;
				player[g_Player]->HB_ReduceRectColor.blue = 0;
				player[g_Player]->HB_ReduceRectColor.alpha = 255;

				if(&player[g_Player]->Shadows[1].Avatar != 0)
					{
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
					Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[1].Avatar, &player[g_Player]->Shadows[1].Xform);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[2].Avatar, &player[g_Player]->Shadows[2].Xform);
					Qpo->Avatar_ClearPose(player[g_Player]->Shadows[3].Avatar, &player[g_Player]->Shadows[3].Xform);
					}

				player[g_Player]->HitReactScale = 0.05;
			
				if(DirFlag == 0) player[g_Player]->MoveReactVec = DistVec;
				else player[g_Player]->MoveReactVec = Direction;
				//if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;

				player[g_Player]->MoveReactSpeed = 14 + (Scale * 10);	//10 * 4

					//## Reset Hit Wall
				player[g_Player]->HitWall = 0;

				//#### Set Flames
				//splayer[g_Player]->FlameHit = 1;
										
				if(player[g_Player]->Aposestate != 51)
					{
					player[g_Player]->Aposestate = 51;
					player[g_Player]->attackon = 1;
					player[g_Player]->attposecnt = 0;
					player[g_Player]->CrunchTimer = 0;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					}
				else
					{
					player[g_Player]->DownSpeed = 2;	//Reset DownSpeed
					player[g_Player]->CrunchTimer = 0;
					player[g_Player]->attposecnt = 0.47;
					player[g_Player]->astackcnt = 0;
					player[g_Player]->astackrun = 0;
					}
				}
			}//END TESTShieldFLAG

		}//END player


		//### Loop to check all AI locations for first proximity check
	SCRAM = 0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if( (Q_Forge->Forge[SCRAM].Team != Team) && (Q_Forge->Forge[SCRAM].HB_Dead == 0) && (Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha == 0) )
				{
				//### Find Distance between Avatar and Explosion
				AvatarPos = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
				AvatarPos.y += 65;
				Qpo->Vec3d_Subtract(&AvatarPos, &ExpPos, &DistVec);
				AvatarDist = Qpo->Vec3d_Length(&DistVec);
				Qpo->Vec3d_Normalize(&DistVec);


				//##### Avatar Within Player Shield Test
				TESTShieldFLAG = 0;

				if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldAlpha > 0) && (player[g_Player]->Team == Q_Forge->Forge[SCRAM].Team) && (player[g_Player]->HB_Energy > 0))
					{
					TESTPosS = AvatarPos;
					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

					if((TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale)) && (player[g_Player]->HB_Energy > 0))
						{
						TESTShieldFLAG = 1;
						}
					}

				//### Avatar Within Avatar Shield
				jet2=0;
				while(jet2 < _->NomAI)
					{
					if(Q_Forge->Forge[jet2].LIVE == 1)
						{
						if((Q_Forge->Forge[jet2].CharDATA.Class == 2) && (Q_Forge->Forge[jet2].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[jet2].Team != Q_Forge->Forge[SCRAM].Team) && (Q_Forge->Forge[jet2].HB_Energy > 0))
							{
							TESTPosS = AvatarPos;
							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[jet2].Shield.Xform.Translation);

							if(TESTShieldDIST < (65 * Q_Forge->Forge[jet2].Cleric.ShieldScale))
								{
								TESTShieldFLAG = 1;
								}
							}
						}
					jet2++;
					}


				if(TESTShieldFLAG == 0)
					{
					if(AvatarDist < (500 * Scale) && AvatarDist > (300 * Scale))
						{	//### Standard Hit Reaction

							//## Reduce Health
						Q_Forge->Forge[SCRAM].HB_ReduceOld = Q_Forge->Forge[SCRAM].HB_Health;

						Q_Forge->Forge[SCRAM].HB_Health -= ((20 * ExpDMG) + (Scale * 10)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						if(Q_Forge->Forge[SCRAM].HB_Health < 0) Q_Forge->Forge[SCRAM].HB_Health = 0;

						//### Experience Storage
						if(AvID == 250) player[g_Player]->AvatarDMGSTORE[SCRAM] += ((20 * ExpDMG) + (Scale * 10)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						else Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] += ((20 * ExpDMG) + (Scale * 10)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);

						//#### Avatar DEATH
						if(AvID == 250)
							{
							if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
								{
								Q_Forge->Forge[SCRAM].HB_Health = 0;

								

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[SCRAM].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[SCRAM].AV.Xform.Translation);

									jet++;
									}

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
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if((player[g_Player]->DecFinger <= 50))
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
									}


								//##### Check All Active Avatars for XP and KO's
								SCRAMJET = 0;
								while(SCRAMJET < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAMJET].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAMJET].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == SCRAMJET)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[SCRAMJET].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[SCRAMJET].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);
												}
											}
										}

									SCRAMJET++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								//### Write out CHARDATA
								Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

								//####### REACTIVATE ITEM ATTRIBUTES
								Q.ActivateItems();
								}
							}
						else
							{
							if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
								{
								Q_Forge->Forge[SCRAM].HB_Health = 0;

								

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[SCRAM].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(AvID, Q_Forge->Forge[SCRAM].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AvID].CDATID].UnusedXP += Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

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
									Q_Forge->Forge[AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[AvID].DecFinger <= 50)
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
									}

								g_Sp = 0;

								//##### Check All Active Avatars for XP and KO's
								SCRAMJET = 0;
								while(SCRAMJET < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAMJET].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAMJET].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == SCRAMJET)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[SCRAMJET].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[SCRAMJET].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);
												}
											}
										}

									SCRAMJET++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

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
						
						if(DirFlag == 0) Q_Forge->Forge[SCRAM].MoveReactVec = DistVec;
						else Q_Forge->Forge[SCRAM].MoveReactVec = Direction;
						if(Q_Forge->Forge[SCRAM].MoveReactVec.y < 0) Q_Forge->Forge[SCRAM].MoveReactVec.y = 0;

						Q_Forge->Forge[SCRAM].MoveReactSpeed = 2 + (Scale * 3);

							//## Reset Hit Wall
						Q_Forge->Forge[SCRAM].HitWall = 0;

						if(Q_Forge->Forge[SCRAM].Aposestate != 28)
							{
							Q_Forge->Forge[SCRAM].Aposestate = 28;
							Q_Forge->Forge[SCRAM].attackon = 1;
							Q_Forge->Forge[SCRAM].attposecnt = 0;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						else
							{
							if(Q_Forge->Forge[SCRAM].attposecnt >= 0.16) Q_Forge->Forge[SCRAM].attposecnt = 0.16;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						}

					if(AvatarDist < (300 * Scale) && AvatarDist > (100 * Scale))
						{	//### Fall Hit Reaction

							//## Reduce Health
						Q_Forge->Forge[SCRAM].HB_ReduceOld = Q_Forge->Forge[SCRAM].HB_Health;

						Q_Forge->Forge[SCRAM].HB_Health -= ((50 * ExpDMG) + (Scale * 20)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						if(Q_Forge->Forge[SCRAM].HB_Health < 0) Q_Forge->Forge[SCRAM].HB_Health = 0;

						//### Experience Storage
						if(AvID == 250) player[g_Player]->AvatarDMGSTORE[SCRAM] += ((50 * ExpDMG) + (Scale * 20)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						else Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] += ((50 * ExpDMG) + (Scale * 20)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);

						//#### Avatar DEATH
						if(AvID == 250)
							{
							if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
								{
								Q_Forge->Forge[SCRAM].HB_Health = 0;

								

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[SCRAM].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(AvID, Q_Forge->Forge[SCRAM].AV.Xform.Translation);

									jet++;
									}

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
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if((player[g_Player]->DecFinger <= 50))
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
									}

								g_Sp = 0;

								//##### Check All Active Avatars for XP and KO's
								SCRAMJET = 0;
								while(SCRAMJET < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAMJET].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAMJET].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == SCRAMJET)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[SCRAMJET].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[SCRAMJET].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);
												}
											}
										}
									SCRAMJET++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

								//####### REACTIVATE ITEM ATTRIBUTES
								Q.ActivateItems();
								}
							}
						else
							{
							if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
								{
								Q_Forge->Forge[SCRAM].HB_Health = 0;

								

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[SCRAM].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(AvID, Q_Forge->Forge[SCRAM].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AvID].CDATID].UnusedXP += Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

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
									Q_Forge->Forge[AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[AvID].DecFinger <= 50)
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
									}

								g_Sp =

								//##### Check All Active Avatars for XP and KO's
								SCRAMJET = 0;
								while(SCRAMJET < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAMJET].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAMJET].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == SCRAMJET)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[SCRAMJET].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[SCRAMJET].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);
												}
											}
										}
									SCRAMJET++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

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
												
						if(DirFlag == 0) Q_Forge->Forge[SCRAM].MoveReactVec = DistVec;
						else Q_Forge->Forge[SCRAM].MoveReactVec = Direction;
						if(Q_Forge->Forge[SCRAM].MoveReactVec.y < 0) Q_Forge->Forge[SCRAM].MoveReactVec.y = 0;

						Q_Forge->Forge[SCRAM].MoveReactSpeed = 8 + (Scale * 6);

							//## Reset Hit Wall
						Q_Forge->Forge[SCRAM].HitWall = 0;
												
						if(Q_Forge->Forge[SCRAM].Aposestate != 90)
							{
							Q_Forge->Forge[SCRAM].Aposestate = 90;
							Q_Forge->Forge[SCRAM].attackon = 1;
							Q_Forge->Forge[SCRAM].attposecnt = 0;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						else
							{
							if(Q_Forge->Forge[SCRAM].attposecnt >= 2) Q_Forge->Forge[SCRAM].attposecnt = 2;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						}

					if(AvatarDist < (100 * Scale))
						{	//### Heavy Full Hit Reaction

							//## Reduce Health
						/*if(Q_Forge->Forge[SCRAM].HB_HReduceON == 0)*/ Q_Forge->Forge[SCRAM].HB_ReduceOld = Q_Forge->Forge[SCRAM].HB_Health;

						Q_Forge->Forge[SCRAM].HB_Health -= ((100 * ExpDMG) + (Scale * 40)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						if(Q_Forge->Forge[SCRAM].HB_Health < 0) Q_Forge->Forge[SCRAM].HB_Health = 0;

						//### Experience Storage
						if(AvID == 250) player[g_Player]->AvatarDMGSTORE[SCRAM] += ((100 * ExpDMG) + (Scale * 40)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						else Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] += ((100 * ExpDMG) + (Scale * 40)) * ((1 - (Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Constitution / 400)) + 0.75);

						//#### Avatar DEATH
						if(AvID == 250)
							{
							if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
								{
								Q_Forge->Forge[SCRAM].HB_Health = 0;

								

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[SCRAM].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(AvID, Q_Forge->Forge[SCRAM].AV.Xform.Translation);

									jet++;
									}

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
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if((player[g_Player]->DecFinger <= 50))
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
									}

								g_Sp = 0;


								//##### Check All Active Avatars for XP and KO's
								SCRAMJET = 0;
								while(SCRAMJET < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAMJET].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAMJET].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == SCRAMJET)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[SCRAMJET].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[SCRAMJET].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);
												}
											}
										}
									SCRAMJET++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

								//####### REACTIVATE ITEM ATTRIBUTES
								Q.ActivateItems();
								}
							}
						else
							{
							if(Q_Forge->Forge[SCRAM].HB_Health <= 0)
								{
								Q_Forge->Forge[SCRAM].HB_Health = 0;

								

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[SCRAM].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[SCRAM].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(AvID, Q_Forge->Forge[SCRAM].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AvID].CDATID].UnusedXP += Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[AvID].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

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
									Q_Forge->Forge[AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[AvID].DecFinger <= 50)
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
									}

								g_Sp = 0;

								//##### Check All Active Avatars for XP and KO's
								SCRAMJET = 0;
								while(SCRAMJET < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAMJET].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAMJET].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAMJET].AvatarDMGSTORE[SCRAM] * (10 * Q_Forge->Forge[SCRAM].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == SCRAMJET)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[SCRAMJET].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[SCRAMJET].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[SCRAMJET].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAMJET].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAMJET].CharDATA.CDataID,Q_Forge->Forge[SCRAM].CharDATA.Level);
												}
											}
										}
									SCRAMJET++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

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
												
						if(DirFlag == 0) Q_Forge->Forge[SCRAM].MoveReactVec = DistVec;
						else Q_Forge->Forge[SCRAM].MoveReactVec = Direction;
						if(Q_Forge->Forge[SCRAM].MoveReactVec.y < 0) Q_Forge->Forge[SCRAM].MoveReactVec.y = 0;

						Q_Forge->Forge[SCRAM].MoveReactSpeed = 14 + (Scale * 10);

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
							{
								//Reset DownSpeed
							Q_Forge->Forge[SCRAM].DownSpeed = 2;
							Q_Forge->Forge[SCRAM].CrunchTimer = 0;
							Q_Forge->Forge[SCRAM].attposecnt = 0.47;
							Q_Forge->Forge[SCRAM].astackcnt = 0;
							Q_Forge->Forge[SCRAM].astackrun = 0;
							}
						}
					}//END TESTShieldFLAG
				}
			}
		SCRAM++;
		}

	//###### Shield Slight Damage Check

	//##### Player Shield Test
	if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldAlpha > 0) && (player[g_Player]->HB_Energy > 0) && (Team != player[g_Player]->Team))
		{
		TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&ExpPos, &player[g_Player]->Shield.Xform.Translation);

		if(TESTShieldDIST < ((65 * player[g_Player]->Cleric.ShieldScale) + (65 * (ExpSize * 2.5))))
			{
			jet=0;
			while((jet < ((ExpSize * 100) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.3 + (6 * ExpSize));

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = ((float)rand() / 32767);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_AddScaled(&player[g_Player]->Shield.Xform.Translation, (65 * player[g_Player]->Cleric.ShieldScale), &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec, &Q_PntSprite->PntSprite[_->NomPntSprite].Pos);

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = -1;
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			player[g_Player]->HB_Energy -= ((ExpSize * 2.5) * ((((65 * player[g_Player]->Cleric.ShieldScale) + (65 * (ExpSize * 2.5)) - TESTShieldDIST) / 20))) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));

			Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Live = 10;
			Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Effintensity = ExpSize;
			Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Type = 1;
			Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].AvID = 250;
			_->NomNetEffectControl++;
			}
		}

	//##### AI shield Test
	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if((Q_Forge->Forge[SCRAM].CharDATA.Class == 2) && (Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[SCRAM].HB_Energy > 0) && (Team != Q_Forge->Forge[SCRAM].Team))
				{
				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&ExpPos, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

				if(TESTShieldDIST < ((65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale) + (65 * (ExpSize * 2.5))))
					{
					jet=0;
					while((jet < ((ExpSize * 100) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.3 + (6 * ExpSize));

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = ((float)rand() / 32767);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[SCRAM].Shield.Xform.Translation, (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale), &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec, &Q_PntSprite->PntSprite[_->NomPntSprite].Pos);

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = -1;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = 0;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}

					Q_Forge->Forge[SCRAM].HB_Energy -= ((ExpSize * 2.5) * ((((65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale) + (65 * (ExpSize * 2.5)) - TESTShieldDIST) / 20))) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));

					Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Live = 10;
					Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Effintensity = ExpSize;
					Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Type = 1;
					Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].AvID = SCRAM;
					_->NomNetEffectControl++;
					}
				}
			}

		SCRAM++;
		}

}

};