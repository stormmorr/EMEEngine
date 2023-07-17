/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Collision Detection-
	*/#include "pch.h"/*- Minor Component -Melee-

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
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-WE-PntSprite.h"

using namespace GVARS;

namespace GVARS
{

	//#########  MELEE COLLISION DETECTION  ##########//    REWRITE IN PROGRESS ON AI DETECTION - PORT OVER

void Q_COREFunctions::ColldetMelee(int bonenum, float attstt, float cutoff, float stroke, int HitType, int BlowHeight, int NumAttackHits)
	{
#if 0
	player[g_Player]->JinkRUSHCLOUD = 1;
	player[g_Player]->JRC_Power = (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower;
	player[g_Player]->JRC_Speed = 0.1*((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 100 );
#endif

	//INITIAL SHIELD HIT CHECK
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = 1.2;
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 0;

	//###### SWITCH OUT ATTACK SPECS
	switch(player[g_Player]->Aposestate)
		{
		case 65:	//RUSH ELBOW
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[1].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 22:	//LEAP SPIN KICK
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[2].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 31:	//RIGHT HEAVY KICK
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[5].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 58:	//SKY PUSH
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[7].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 61:	//TWIST KICK
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[8].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 32://FLAME UPPERCUT
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[10].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 35://VERY HEAVY KICK
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[11].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 76://JS RUSH UP
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[17].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 85://JS RUSH PUNCH
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[13].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 73://JS RUSH
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[14].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 64://POWER COMBO
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[19].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 75://Static Kick
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[20].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 57://JS FLAME UPPERCUT
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[22].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 25://HYPER KNEE FLEX
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[23].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 53://AIR DASH
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[25].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 56://SAKURA TRIBUTE
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[26].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 34://SPIN KICK FULL ROTATION
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[27].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;

		case 84://CYCLONE KICK
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[16].Power / 5000) * 15) + 1;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
			break;
		}

	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER *= ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower / 100);

	//##### ITEM ATTRIBUTE INCREMENT #####
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT == 1)
		{
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER += (float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower / 10);
		}

	//### Check for within player shield
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

	if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldAlpha > 0) && (player[g_Player]->Team != Q_Forge->Forge[AIflag].Team) && (player[g_Player]->HB_Energy > 0))
		{
		TESTPosS = Q_Forge->Forge[AIflag].AttPos.Translation;
		TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

		if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
			{
			if(_->NetworkOption != 1) player[g_Player]->HB_Energy -= (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER * 8) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));

			jet=0;
			while((jet < 14) && (_->NomPntSprite < Q_PNTSPRITE_MAX))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 12;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}
	}

	g_Player = 0;

	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if((Q_Forge->Forge[SCRAM].CharDATA.Class == 2) && (Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[SCRAM].Team != player[g_Player]->Team) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
				{
				TESTPosS = player[g_Player]->AttPos.Translation;
				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

				if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
					{
					//player[g_Player]->AntiMultHitsSHIELD[SCRAM]++;

					if(_->NetworkOption != 1) Q_Forge->Forge[SCRAM].HB_Energy -= (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER * 8) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));

					jet=0;
					while((jet < 3) && (_->NomPntSprite < Q_PNTSPRITE_MAX))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 12;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					}
				}
			}

		SCRAM++;
		}

	if(_->NetworkOption != 1)
		{
		//######===-- Q_Object->Object COLLISION DETECTION --===#######
		SCRAM=0;
		while(SCRAM < _->NomQObject)
			{
			if(Q_Object->Object[SCRAM].LIVE == 1 && Q_Object->Object[SCRAM].AvID != 250)
				{
				//### COLLISION CHECK
				if(Q_Object->Object[SCRAM].StrengthBANK > 0)
					{
					switch(Q_Object->Object[SCRAM].CollisionTYPE)
						{
						case 0:
							{
							TESTPosS = player[g_Player]->AttPos.Translation;
							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Object->Object[SCRAM].Pos);

							if(TESTShieldDIST < Q_Object->Object[SCRAM].Scale)
								{
								//Set Player Enemy Display to correct enemy
								player[g_Player]->HB_LastAvatarHitID = (SCRAM + 1) * -1;

								//### Block Hit Flash
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = player[g_Player]->AttPos.Translation;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
								Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((player[g_Player]->attposecnt - attstt) / ( cutoff - attstt ));
								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;
								
								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 200;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 60;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 200;

									//Increment number of MeleeHits
								_->NomMelHit += 1;

								Q_Object->Object[SCRAM].StrengthBANK -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER * 8;
								}

							}break;
						}
					}
				}

			SCRAM++;
			}

		for (unsigned int f_CountOtherPlayer = 0; f_CountOtherPlayer < g_PlayerNom; f_CountOtherPlayer++)
		{
		if(f_CountOtherPlayer != g_Player)
		{
		Qpo->Player_GetBoneBoxes(BoneDef[bonenum], &pCorner, &DX, &DY, &DZ, &ColldetBox);

		ColldetBox.Min = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Min);
		ColldetBox.Max = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Max);

		Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
		Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

		player[g_Player]->LimPosBox.Matrix = playerAV[g_Player]->Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
		coldetresult = playerAV[g_Player]->Xform.Matrix.multiply_rotation(pCorner);

		player[g_Player]->LimPosBox.Translation.x = coldetresult.x + playerAV[g_Player]->Xform.Translation.x;
		player[g_Player]->LimPosBox.Translation.y = coldetresult.y + playerAV[g_Player]->Xform.Translation.y;
		player[g_Player]->LimPosBox.Translation.z = coldetresult.z + playerAV[g_Player]->Xform.Translation.z;

		xScale = Qpo->Vec3d_Length(&DZ)/1.5;
		yScale = Qpo->Vec3d_Length(&DY)/1.5;
		zScale = Qpo->Vec3d_Length(&DX)/1.5;
		Qpo->Box_Set(&_->Box, xScale, yScale, zScale, &player[g_Player]->LimPosBox);

		//####  First Stage - Avatar Ext Bounding Box Check  ####//
#if 0
		if(Qpo->Collision_Avatar_Player_Intersect(AIflag))
#endif

		if(Qpo->Player_Player_ExtBox_intersect(f_CountOtherPlayer))
			{
			detcnt = 0;
			while(detcnt < 21)	//####  Second Stage - Bone Ext Bounding Box Check  ####//
				{
				Qpo->Player_GetBoneBoundingBox(BoneDef[detcnt], &pCorner, &DX, &DY, &DZ);

				Qpo->Transform_New_LeftUpIn(&bonepos, &DY, &DX, &DZ);
				Qpo->Transform_Orthonormalize(&bonepos);

				bonepos.Matrix = playerAV[g_Player]->Xform.Matrix * bonepos.Matrix;
				coldetresult = playerAV[g_Player]->Xform.Matrix.multiply_rotation(pCorner);

				bonepos.Translation.x = coldetresult.x + playerAV[g_Player]->Xform.Translation.x;
				bonepos.Translation.y = coldetresult.y + playerAV[g_Player]->Xform.Translation.y;
				bonepos.Translation.z = coldetresult.z + playerAV[g_Player]->Xform.Translation.z;

				xScale = Qpo->Vec3d_Length(&DZ)/1.5;
				yScale = Qpo->Vec3d_Length(&DY)/1.5;
				zScale = Qpo->Vec3d_Length(&DX)/1.5;
				Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &bonepos);
				
				//### Anti Multiple Hits System / Team Checks
				if(Q_Forge->Forge[AIflag].AntiMultHits[250] < NumAttackHits && Q_Forge->Forge[AIflag].Team != player[g_Player]->Team)
					{
					//### Filter Out unused bones
					if(!(detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16 && player[g_Player]->Aposestate != 21)
						   && !(player[g_Player]->Aposestate == 21 && ( detcnt == 1 || detcnt == 3 || detcnt == 6 || detcnt == 12
						   || detcnt == 15 || detcnt == 16 || detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16)))
						{
						if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &_->Box) || (( Q_Forge->Forge[AIflag].attposecnt > ( stroke - 0.15 )) && ( Q_Forge->Forge[AIflag].attposecnt < ( stroke + 0.15 )) ))
							{	//COLLISION
							//### Dodge Checks
							if(!(player[g_Player]->HB_Dead == 1) && !(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 1 && BlowHeight == 3) && !(player[g_Player]->CrouchInit == 1 && BlowHeight == 3) && !(player[g_Player]->AirBorn == 1 && BlowHeight == 1) && !(player[g_Player]->Flip == 1 && BlowHeight == 1) && !(player[g_Player]->HB_RecoverMode == 2 && (BlowHeight == 2 || BlowHeight == 3)))
								{
								//>>>---  Possible Hit On Avatar, Update Hits  ---<<<
								Q_Forge->Forge[AIflag].attackhits++;

								//>>>---  Definate Hit On Avatar, Update Hits  ---<<<
								Q_Forge->Forge[AIflag].AntiMultHits[250]++;

								Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = 1.2;	//0.2
								Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 0;

								//###### SWITCH OUT ATTACK SPECS
								switch(Q_Forge->Forge[AIflag].Aposestate)
									{
									case 65:	//RUSH ELBOW
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[1].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 22:	//LEAP SPIN KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[2].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 31:	//RIGHT HEAVY KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[5].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 58:	//SKY PUSH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[7].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 61:	//TWIST KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[8].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 32://FLAME UPPERCUT
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[10].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 35://VERY HEAVY KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[11].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 76://JS RUSH UP
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[17].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 85://JS RUSH PUNCH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[13].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 73://JS RUSH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[14].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 64://POWER COMBO
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[19].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 75://Static Kick
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[20].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 57://JS FLAME UPPERCUT
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[22].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 25://HYPER KNEE FLEX
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[23].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 53://AIR DASH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[25].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 56://SAKURA TRIBUTE
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[26].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 34://SPIN KICK FULL ROTATION
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[27].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 84://CYCLONE KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[16].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;
									}

								Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower / 100);

								//##### ITEM ATTRIBUTE INCREMENT #####
								if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 1)
									{
									Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER += (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKINCpower / 100);
									}

								//######## Aggressive to defensive power check
								if((player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == BlowHeight) || (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3 && BlowHeight == 2))
									{
									if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower + (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.PhysicalStr) * (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER;
									else player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK -= (((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower + (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.PhysicalStr) * (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER)/2;

									if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = 0;

									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PBTIMER = TIME;
									}

								//###### Set Limb Strengths
								//Left Arm
								if(bonenum == 5 || bonenum == 4)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftArmSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftArmSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								//Right Arm
								if(bonenum == 14 || bonenum == 13)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightArmSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightArmSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								//Left Leg
								if(bonenum == 3 || bonenum == 1)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftLegSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftLegSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								//Right Leg
								if(bonenum == 10 || bonenum == 12)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightLegSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightLegSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								///////- BALANCE EDIT -////////
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH /= 10;
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP /= 2;

								//##### Player Blocking
								if(((player[g_Player]->Block == 0 || (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight != BlowHeight)) && !(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3 && BlowHeight == 2)) || (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0))
									{
									if(player[g_Player]->DeflectLethal == 1 && Q_Forge->Forge[AIflag].JinkSpecialON < 1)
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_Forge->Forge[AIflag].JinkSpecialON;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
										Qpo->Avatar_GetBoneTransform(&playerAV[f_CountOtherPlayer], BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;

										//### Register Deflect Power
										if(player[g_Player]->DeflectPower == 0) Q_Forge->Forge[AIflag].HitReactScale = 0.03*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness*0.5)+0.5)*((1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELRawPower/35))+0.6);
										else Q_Forge->Forge[AIflag].HitReactScale = 0.01*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness*0.5)+0.5)*((1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELRawPower/35))+0.6);

										Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
										Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);
										Qpo->Vec3d_Inverse(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

										Q_Forge->Forge[AIflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										Q_Forge->Forge[AIflag].MoveReactVec.y = 0;
										Q_Forge->Forge[AIflag].MoveReactSpeed = 5.5;

										Q_Forge->Forge[AIflag].Aposestate = 28;
										Q_Forge->Forge[AIflag].attackon = 1;
										Q_Forge->Forge[AIflag].attposecnt = 0;

										Q_Forge->Forge[AIflag].astackcnt = 0;
										Q_Forge->Forge[AIflag].astackrun = 0;

										_->NomMelHit++;
										}
									else
										{
										//CALCULATE HIT REACTIONS
										// Vector to move by (world-space)
										Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
										lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										//XXXXXXXXXXXXX
										//Manually calculate the LOCAL X axis vector in WORLD - SPACE!!
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Shift.x = 10;
										Shift.y = 0;
										Shift.z = 0;
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixX);

											//Move Joint back into place
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,-10,0,0);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//YYYYYYYYYYYYYYYY
										//Manually calculate the LOCAL Y axis vector in WORLD - SPACE!!
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Shift.x = 0;
										Shift.y = 10;
										Shift.z = 0;
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixY);

											//Move Joint back into place
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,0,-10,0);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//ZZZZZZZZZZZZZZ
										//Manually calculate the LOCAL Z axis vector in WORLD - SPACE!!
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Shift.x = 0;
										Shift.y = 0;
										Shift.z = 10;
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixZ);

											//Move Joint back into place
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,0,0,-10);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//Clear Bone Matrix
										Qpo->Transform_New(&BoneMatrix);

										Qpo->Vec3d_Inverse(&BoneMatrixX);

										//Build the bone matrix
										Qpo->Transform_New_LeftUpIn(&BoneMatrix, &BoneMatrixX, &BoneMatrixY, &BoneMatrixZ);

										Qpo->Transform_Orthonormalize(&BoneMatrix);

										Qpo->Body_GetBone(LisaBody, BoneNum[detcnt], &BoneName, &Attachment, &ParBone);
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, ParBone, &Q_Forge->Forge[AIflag].TempXForm2);
										BoneMatrix.Translation.x = Q_Forge->Forge[AIflag].TempXForm2.Translation.x;
										BoneMatrix.Translation.y = Q_Forge->Forge[AIflag].TempXForm2.Translation.y;
										BoneMatrix.Translation.z = Q_Forge->Forge[AIflag].TempXForm2.Translation.z;

										//Transform the reaction vector by the transpose of the bone matrix
										Qpo->Transform_TransposeVector(&BoneMatrix, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										// Scale the vector to make the reaction more visible for testing
										Qpo->Vec3d_Scale(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, lengthvec, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										// Get the local xform of the bone
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										// Translate the bone's xform by the altered vector	
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_Forge->Forge[AIflag].TempXForm1.Translation); 

										// Set the local bone xform to the new location
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//Reset Reaction vector
										Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										//Not sure if this Normalising is fun here for Supposed Power hits
										Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

											//~~Setup a Melee Hit Struct

										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
										if(((( Q_Forge->Forge[AIflag].attposecnt > ( stroke - 0.1 ) ) && ( Q_Forge->Forge[AIflag].attposecnt < ( stroke + 0.1 ))))) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;
										if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent < 0.75) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;

											//# Deduct Health
										Q_Forge->Forge[AIflag].HB_LastAvatarHitID = AItempcnt;
										/*if(player[g_Player]->HB_HReduceON == 0)*/ player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;


												//Rework Needed here very messy , plus add a random factor
										//### Take Health and Give Energy to wounded Avatar
										player[g_Player]->HB_Energy += 6;

										player[g_Player]->HB_HealthHistory = player[g_Player]->HB_Health;

										if(HitType == 20)
											{
											player[g_Player]->HB_Health -= (80 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 50 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 20;

											player[g_Player]->HB_DmgSTORE += ((80 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 50) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 25;
											}

										if(HitType == 13)
											{
											player[g_Player]->HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
											}

										if(HitType == 12)
											{
											player[g_Player]->HB_Health -= (30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 5;

											//player[g_Player]->HB_DmgSTORE += ((30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
											}

										if(HitType == 11)
											{
											player[g_Player]->HB_Health -= (70 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 5;

											//player[g_Player]->HB_DmgSTORE += ((30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
											}

										if(HitType == 10)
											{
											player[g_Player]->HB_Health -= (50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 10;

											player[g_Player]->HB_DmgSTORE += ((50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 40) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
											}

										if(HitType == 9)
											{
											player[g_Player]->HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
											}

										if(HitType == 8)
											{
											player[g_Player]->HB_Health -= (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
											}

										if(HitType == 7)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
											}

										if(HitType == 6)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
											}

										if(HitType == 5)
											{
											player[g_Player]->HB_Health -= (20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 4;

											player[g_Player]->HB_DmgSTORE += ((20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 4)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 4;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 3)
											{
											player[g_Player]->HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 2)
											{
											player[g_Player]->HB_Health -= (35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 2;

											player[g_Player]->HB_DmgSTORE += ((35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
											}

										if(HitType == 1)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 1;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 0)
											{
											player[g_Player]->HB_Health -= (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 1;

											player[g_Player]->HB_DmgSTORE += ((8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 3;
											}

										//### Add damage to Experience store
										player[g_Player]->HB_HealthDiff = player[g_Player]->HB_HealthHistory - player[g_Player]->HB_Health;
										playerAV[f_CountOtherPlayer]atarDMGSTORE[250] += player[g_Player]->HB_HealthDiff;

										if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

										if(player[g_Player]->HB_Health <= 0)
											{
											player[g_Player]->HB_Health = 0;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 11;

											player[g_Player]->HB_Dead = 1;

											//### Add Experience to attacking AVATAR
											if((playerAV[f_CountOtherPlayer]atarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
												{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AIflag].CDATID].UnusedXP += playerAV[f_CountOtherPlayer]atarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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

														//### Force Net player to update (Net Play Only)
														if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
														}

													if(DeliverKOID == SCRAM)
														{
														//### Create Item for attacking Avatar
														Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

														if(Q_Forge->Forge[SCRAM].DecFinger <= 50 || 1)
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

											//### Write out CHARDATA
											Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

											//####### REACTIVATE ITEM ATTRIBUTES
											Q.ActivateItems();
											}

										player[g_Player]->HB_HReduceON = 1;
										player[g_Player]->HB_ReduceHInc = 10;
										player[g_Player]->HB_ReduceHeight = 573;
										player[g_Player]->HB_ReduceRectColor.red = 255;
										player[g_Player]->HB_ReduceRectColor.green = 0;
										player[g_Player]->HB_ReduceRectColor.blue = 0;
										player[g_Player]->HB_ReduceRectColor.alpha = 255;

										if(player[g_Player]->Shadows[1].Avatar != 0)
											{
											Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
											Qpo->Avatar_ClearPose(player[g_Player]->Shadows[1].Avatar, &player[g_Player]->Shadows[1].Xform);
											Qpo->Avatar_ClearPose(player[g_Player]->Shadows[2].Avatar, &player[g_Player]->Shadows[2].Xform);
											Qpo->Avatar_ClearPose(player[g_Player]->Shadows[3].Avatar, &player[g_Player]->Shadows[3].Xform);
											}

										if(HitType == 0)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;	//0.04

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 1)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.05 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 2;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 2)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.05 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 4;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 3)	//Standard Hit Up into Air Slightly
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 1;
											player[g_Player]->MoveReactVec.x /= 3;
											player[g_Player]->MoveReactVec.z /= 3;
											player[g_Player]->MoveReactSpeed = 8.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//5.2	//6 V-Good

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}


										if(HitType == 13)	//Standard Hit Up into Air Slightly
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 1;
											player[g_Player]->MoveReactVec.x /= 3;
											player[g_Player]->MoveReactVec.z /= 3;
											player[g_Player]->MoveReactSpeed = 8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}


										if(HitType == 4)	//Spin Kick Full Rotation
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;	
											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 5)	//Combo 1 Heavy KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}
											
											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											if(player[g_Player]->MoveReactVec.y > 0.1) player[g_Player]->MoveReactVec.y = 0.1;
											if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 6)	//Combo 1 Heavy KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 7)	//Hit Up into Air Dramatically
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}
											
											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 1;
											player[g_Player]->MoveReactSpeed = 6.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//6 V-Good

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 8)	//Combo 2 Steady Kicks
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											Qpo->Vec3d_New(&player[g_Player]->MoveReactVec);
											
											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 9)	//Heavy KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);	//250			//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 255;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											if(player[g_Player]->HitReactScale != 0)
												{
												player[g_Player]->HitReactScale /= 1.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
												}
											else player[g_Player]->HitReactScale = 0.025 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 9;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;	
											player[g_Player]->MoveReactSpeed = 6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//4.5

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 10)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											player[g_Player]->HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 5;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;

											//##### Camera Shake For Super Hits
											player[g_Player]->CameraShake = 1;
											player[g_Player]->CamShkTIME = 4;
											}


										if(HitType == 11)	//Combo extern No KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.01 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 12)	//JSRush Combo
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.01 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 20)	//Ultra Blow
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											player[g_Player]->HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
												}

											Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactSpeed = 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//15

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 2;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;

											//##### Camera Shake For Super Hits
											player[g_Player]->CameraShake = 1;
											player[g_Player]->CamShkTIME = 4;
											}

										// Assign Heavy Hits
										if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

										//#####- Hit Reaction Motions -#####
										if(player[g_Player]->HB_DmgSTORE >= 135)
											{
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HB_RecoverMode = 1;
											player[g_Player]->HB_DmgSTORE = 0;		//### Reset Damage Storage
											}

										// Turn On for AI Timeholes
										if(player[g_Player]->Aposestate == 17 || player[g_Player]->Aposestate == 22 || player[g_Player]->Aposestate == 25 || player[g_Player]->Aposestate == 31 || player[g_Player]->Aposestate == 33 || player[g_Player]->Aposestate == 35 || player[g_Player]->Aposestate == 40 || player[g_Player]->Aposestate == 45) _->TimeHole = 1;
										if(player[g_Player]->Aposestate == 10 || player[g_Player]->Aposestate == 21 || player[g_Player]->Aposestate == 24 || player[g_Player]->Aposestate == 34 || player[g_Player]->Aposestate == 39) _->TimeHole = 2;
										if(player[g_Player]->Aposestate == 13 || player[g_Player]->Aposestate == 41 || player[g_Player]->Aposestate == 44 || player[g_Player]->Aposestate == 32) _->TimeHole = 3;

										if(HitType == 10 || HitType == 20)
											{
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 91)
													{
													player[g_Player]->Aposestate = 91;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->CrunchTimer = 0;

													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{	//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->CrunchTimer = 0;

													player[g_Player]->attposecnt = 0.47;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													{	//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->CrunchTimer = 0;

													player[g_Player]->attposecnt = 0.47;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 6; }

											if(player[g_Player]->HB_DmgSTORE >= 135)
												{
												player[g_Player]->HB_RecoverMode = 1;
												player[g_Player]->HB_DmgSTORE = 0;		//### Reset Damage Storage
												}
											}

										//Increment number of MeleeHits
										_->NomMelHit += 1;

										detcnt = 22;

										if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0) && ((player[g_Player]->Block == 1 && (player[g_Player]->BlockHeight == BlowHeight)) || (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3 && BlowHeight == 2)))
											{
											//### Block Hit Flash
											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																				//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
											Qpo->Avatar_GetBoneTransform(&playerAV[f_CountOtherPlayer], BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 160;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 0;

												// Vector to move by (world-space)
											//Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
											//lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
											//Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
											//player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
											//player[g_Player]->MoveReactSpeed = 5;	//5.4;

												//Increment number of MeleeHits
											_->NomMelHit += 1;

											detcnt = 22;

											//##### RESET POWERBANK
											//player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2);
											}

										}//END Else/Deflect (true HIT)

									}//END Block
								else				//-- BLOCK --
									{
									//##### Vector to move by (world-space)
									Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
									lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
									Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;

									if(HitType == 0)
										{
										//player[g_Player]->HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
										player[g_Player]->HitReactScale = 0.09 * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (0.1 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 1)
										{
										player[g_Player]->HitReactScale = (0.032 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 2)
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 3)	//Standard Hit Up into Air Slightly
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 1;
										player[g_Player]->MoveReactVec.x /= 3;
										player[g_Player]->MoveReactVec.z /= 3;
										player[g_Player]->MoveReactSpeed = (5.2 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 13)	//Standard Hit Up into Air Slightly
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 1;
										player[g_Player]->MoveReactVec.x /= 3;
										player[g_Player]->MoveReactVec.z /= 3;
										player[g_Player]->MoveReactSpeed = (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
													
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 4)
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 5)	//Combo 1 Heavy KnockBack
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										if(player[g_Player]->MoveReactVec.y > 0.1) player[g_Player]->MoveReactVec.y = 0.1;
										if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 6)	//Combo 1 Heavy KnockBack
										{
										player[g_Player]->HitReactScale = (0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactSpeed = (4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 7)	//Hit Up into Air Dramatically
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.x /= 1.85;
										player[g_Player]->MoveReactVec.z /= 1.85;
										player[g_Player]->MoveReactVec.y = 1;

										player[g_Player]->MoveReactSpeed = (14 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 8)	//Combo 2 Steady Kicks
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										Qpo->Vec3d_New(&player[g_Player]->MoveReactVec);
										
										player[g_Player]->MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 9)	//Heavy KnockBack
										{
										player[g_Player]->HitReactScale = (0.075 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactSpeed = (6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 10)
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactSpeed = (13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 11)	//Combo extern No KnockBack
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 12)	//JSRush Combo
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 20)	//Ultra Blow
										{
										player[g_Player]->HitReactScale = (0.0035 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
										player[g_Player]->MoveReactSpeed = (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									//Assign Shock Block Flash
									if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;

									player[g_Player]->Aposestate = 18;
									player[g_Player]->BlockHit = 1;
									player[g_Player]->BlockHitFLAG = 1;
									player[g_Player]->attposecnt = 0;
									player[g_Player]->BlockHitID = _->NomMelHit;

									//### Block Hit Flash
									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
									Qpo->Avatar_GetBoneTransform(&playerAV[f_CountOtherPlayer], BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;

										// Vector to move by (world-space)
									/*player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
									player[g_Player]->MoveReactSpeed = 5;	//5.4;*/

										//Increment number of MeleeHits
									_->NomMelHit += 1;

									detcnt = 22;
									}//END Else/Block

								}//END Dodge

							}//END OBB

						}//END BF

					}//END AntiMultHits

				detcnt += 1;
				}
			}
		}
		}
		g_Player = 0;

		//####  First Stage - Avatar Ext Bounding Box Check  ####//
		//***********
		Qpo->Player_GetBoneBoxes(BoneDef[bonenum], &pCorner, &DX, &DY, &DZ, &ColldetBox);

		ColldetBox.Min = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Min);
		ColldetBox.Max = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Max);

		Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
		Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

		player[g_Player]->LimPosBox.Matrix = playerAV[g_Player]->Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
		coldetresult = playerAV[g_Player]->Xform.Matrix.multiply_rotation(pCorner);

		player[g_Player]->LimPosBox.Translation.x = coldetresult.x + playerAV[g_Player]->Xform.Translation.x;
		player[g_Player]->LimPosBox.Translation.y = coldetresult.y + playerAV[g_Player]->Xform.Translation.y;
		player[g_Player]->LimPosBox.Translation.z = coldetresult.z + playerAV[g_Player]->Xform.Translation.z;

		xScale = Qpo->Vec3d_Length(&DZ)/1.5;
		yScale = Qpo->Vec3d_Length(&DY)/1.5;
		zScale = Qpo->Vec3d_Length(&DX)/1.5;
		Qpo->Box_Set(&_->Box, xScale, yScale, zScale, &player[g_Player]->LimPosBox);

		AItempcnt = 0;
		while(AItempcnt < _->NomAI)
			{
			if(Q_Forge->Forge[AItempcnt].LIVE == 1)
				{
				if(Q_Forge->Forge[AItempcnt].Team != player[g_Player]->Team)
					{
					//if(Qpo->Collision_Player_Intersect(AItempcnt))
					if(Qpo->Player_ExtBox_intersect(AItempcnt))
						{
						detcnt = 0;		//22
						while(detcnt < 21)	//####  Second Stage - Bone Ext Bounding Box Check  ####//
							{
							Qpo->Avatar_GetBoneBoundingBox(AItempcnt, BoneDef[detcnt], &pCorner, &DX, &DY, &DZ);

							Qpo->Transform_New_LeftUpIn(&bonepos, &DY, &DX, &DZ);
							Qpo->Transform_Orthonormalize(&bonepos);

							bonepos.Matrix = Q_Forge->Forge[AItempcnt].AV.Xform.Matrix * bonepos.Matrix;
							coldetresult = Q_Forge->Forge[AItempcnt].AV.Xform.Matrix.multiply_rotation(pCorner);

							bonepos.Translation.x = coldetresult.x + Q_Forge->Forge[AItempcnt].AV.Xform.Translation.x;
							bonepos.Translation.y = coldetresult.y + Q_Forge->Forge[AItempcnt].AV.Xform.Translation.y;
							bonepos.Translation.z = coldetresult.z + Q_Forge->Forge[AItempcnt].AV.Xform.Translation.z;

							xScale = Qpo->Vec3d_Length(&DZ)/1.5;
							yScale = Qpo->Vec3d_Length(&DY)/1.5;
							zScale = Qpo->Vec3d_Length(&DX)/1.5;
							Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &bonepos);

							//### Anti Multiple Hits System
							if(player[g_Player]->AntiMultHits[AItempcnt] < NumAttackHits)
								{
								//### Filter Out Unused Bones
								if(!((detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16) && player[g_Player]->Aposestate != 21)
										&& !(player[g_Player]->Aposestate == 21 && ( detcnt == 1 || detcnt == 3 || detcnt == 6 || detcnt == 12
										|| detcnt == 15 || detcnt == 16 || detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16)))
									{
									//if(geBox_DetectCollisionBetween(&_->KokBox, &_->Box) || ((( player[g_Player]->attposecnt > ( stroke - 0.1 ) ) && ( player[g_Player]->attposecnt < ( stroke + 0.1 ))) && QpoExtBox_intersection(&bonebox1, &bonebox2, &boneboxR )))
									if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &_->Box) || ( ( player[g_Player]->attposecnt > ( stroke - 0.15 )) && ( player[g_Player]->attposecnt < ( stroke + 0.15 )) ))
										{	//COLLISION
										//### Dodge Checks
										if(!(Q_Forge->Forge[AItempcnt].HB_Dead == 1) && !(Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 1 && BlowHeight == 3) && !(Q_Forge->Forge[AItempcnt].CrouchInit == 1 && BlowHeight == 3) && !(Q_Forge->Forge[AItempcnt].AirBorn == 1 && BlowHeight == 1) && !(Q_Forge->Forge[AItempcnt].Flip == 1 && BlowHeight == 1) && !(Q_Forge->Forge[AItempcnt].HB_RecoverMode == 2 && (BlowHeight == 2 || BlowHeight == 3)))
											{
											//>>>---  Possible Hit On Avatar, Update Hits  ---<<<
											player[g_Player]->attackhits++;

											//>>>---  Definate Hit On Avatar, Update Hits  ---<<<
											player[g_Player]->AntiMultHits[AItempcnt]++;

											player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = 1.2;	//0.2
											player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 0;

											//###### SWITCH OUT ATTACK SPECS
											switch(player[g_Player]->Aposestate)
												{
												case 65:	//RUSH ELBOW
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[1].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 22:	//LEAP SPIN KICK
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[2].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 31:	//RIGHT HEAVY KICK
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[5].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 58:	//SKY PUSH
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[7].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 61:	//TWIST KICK
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[8].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 32://FLAME UPPERCUT
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[10].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 35://VERY HEAVY KICK
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[11].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 76://JS RUSH UP
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[17].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 85://JS RUSH PUNCH
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[13].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 73://JS RUSH
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[14].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 64://POWER COMBO
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[19].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 75://Static Kick
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[20].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 57://JS FLAME UPPERCUT
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[22].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 25://HYPER KNEE FLEX
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[23].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 53://AIR DASH
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[25].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 56://SAKURA TRIBUTE
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[26].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 34://SPIN KICK FULL ROTATION
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[27].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;

												case 84://CYCLONE KICK
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[16].Power / 5000) * 15) + 1;
													player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT = 1;
													break;
												}

											player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER *= ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower / 100);

											//##### ITEM ATTRIBUTE INCREMENT #####
											if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT == 1)
												{
												player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER += (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower / 10);
												}

											//######## Aggressive to defensive power check
											if((Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == BlowHeight) || (Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 3 && BlowHeight == 2))
												{
												if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKATT == 0) Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK -= (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr) * (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER);
												else Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK -= (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr) * (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER)/2;

												if(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK = 0;

												Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.PBTIMER = TIME;
												}

											//##### SET LIMB STRENGTHS

											//Left Arm
											if(bonenum == 5 || bonenum == 4)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											//Right Arm
											if(bonenum == 14 || bonenum == 13)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											//Left Leg
											if(bonenum == 3 || bonenum == 1)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											//Right Leg
											if(bonenum == 10 || bonenum == 12)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											///////- BALANCE EDIT -////////
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH /= 10;
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP /= 2;

											//### Check to Determine if Avatar is Blocking
											if(((Q_Forge->Forge[AItempcnt].Block == 0 || (Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight != BlowHeight)) && !(Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 3 && BlowHeight == 2)) || (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK <= 0))
												{
												//### Check if Avatar Is Deflecting
												if(Q_Forge->Forge[AItempcnt].DeflectLethal == 1 && player[g_Player]->JinkSpecialON < 1)
													{
													Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = 250;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																						//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
													Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = player[g_Player]->AttPos.Translation;	//Point of impact in world space
													Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
													Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
													
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((player[g_Player]->attposecnt - attstt) / ( cutoff - attstt ));

													Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

													//Expandro3D Struct
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
													
													//### Register Deflect Power
													if(Q_Forge->Forge[AItempcnt].DeflectPower == 0) player[g_Player]->HitReactScale = (0.03*((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELQuickness*0.5)+0.5))*((1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower/35))+0.6);
													else player[g_Player]->HitReactScale = 0.01*((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELQuickness*0.5)+0.5)*((1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower/35))+0.6);

													Qpo->Vec3d_Subtract(&player[g_Player]->AttPos.Translation, &player[g_Player]->OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);
													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);
													Qpo->Vec3d_Inverse(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

													player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													player[g_Player]->MoveReactVec.y = 0;
													player[g_Player]->MoveReactSpeed = 5.5;

													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;

													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;

													_->NomMelHit++;
													}
												else	//#####-  true HIT  -#####
													{
													//CALCULATE HIT REACTIONS
													// Vector to move by (world-space)
													Qpo->Vec3d_Subtract(&player[g_Player]->AttPos.Translation, &player[g_Player]->OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
													lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													//XXXXXXXXXXXXX
													//Manually calculate the LOCAL X axis vector in WORLD - SPACE!!
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &player[g_Player]->TempXForm2);
													AxeStart = player[g_Player]->TempXForm2.Translation;
													Shift.x = 10;
													Shift.y = 0;
													Shift.z = 0;
													Qpo->Vec3d_Add(&player[g_Player]->TempXForm1.Translation, &Shift, &player[g_Player]->TempXForm1.Translation);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &player[g_Player]->TempXForm2);
													AxeEnd = player[g_Player]->TempXForm2.Translation;
													Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixX);

														//Move Joint back into place
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Transform_Translate(&player[g_Player]->TempXForm1,-10,0,0);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);

													//YYYYYYYYYYYYYYYY
													//Manually calculate the LOCAL Y axis vector in WORLD - SPACE!!
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &player[g_Player]->TempXForm2);
													AxeStart = player[g_Player]->TempXForm2.Translation;
													Shift.x = 0;
													Shift.y = 10;
													Shift.z = 0;
													Qpo->Vec3d_Add(&player[g_Player]->TempXForm1.Translation, &Shift, &player[g_Player]->TempXForm1.Translation);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &player[g_Player]->TempXForm2);
													AxeEnd = player[g_Player]->TempXForm2.Translation;
													Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixY);

														//Move Joint back into place
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Transform_Translate(&player[g_Player]->TempXForm1,0,-10,0);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);

													//ZZZZZZZZZZZZZZ
													//Manually calculate the LOCAL Z axis vector in WORLD - SPACE!!
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &player[g_Player]->TempXForm2);
													AxeStart = player[g_Player]->TempXForm2.Translation;
													Shift.x = 0;
													Shift.y = 0;
													Shift.z = 10;
													Qpo->Vec3d_Add(&player[g_Player]->TempXForm1.Translation, &Shift, &player[g_Player]->TempXForm1.Translation);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &player[g_Player]->TempXForm2);
													AxeEnd = player[g_Player]->TempXForm2.Translation;
													Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixZ);

														//Move Joint back into place
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);
													Qpo->Transform_Translate(&player[g_Player]->TempXForm1,0,0,-10);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);


													//Clear Bone Matrix
													Qpo->Transform_New(&BoneMatrix);

													Qpo->Vec3d_Inverse(&BoneMatrixX);

													//Build the bone matrix
													Qpo->Transform_New_LeftUpIn(&BoneMatrix, &BoneMatrixX, &BoneMatrixY, &BoneMatrixZ);

													Qpo->Transform_Orthonormalize(&BoneMatrix);

													Qpo->Body_GetBone(LisaBody, BoneNum[detcnt], &BoneName, &Attachment, &ParBone);
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, ParBone, &player[g_Player]->TempXForm2);
													BoneMatrix.Translation.x = player[g_Player]->TempXForm2.Translation.x;
													BoneMatrix.Translation.y = player[g_Player]->TempXForm2.Translation.y;
													BoneMatrix.Translation.z = player[g_Player]->TempXForm2.Translation.z;


													//Transform the reaction vector by the transpose of the bone matrix
													Qpo->Transform_TransposeVector(&BoneMatrix, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													// Scale the vector to make the reaction more visible for testing
													Qpo->Vec3d_Scale(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, lengthvec, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													// Get the local xform of the bone
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);

													// Translate the bone's xform by the altered vector	
													Qpo->Vec3d_Add(&player[g_Player]->TempXForm1.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &player[g_Player]->TempXForm1.Translation); 

													// Set the local bone xform to the new location
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &player[g_Player]->TempXForm1);

													//Reset Reaction vector
													Qpo->Vec3d_Subtract(&player[g_Player]->AttPos.Translation, &player[g_Player]->OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													//Not sure if this Normalising is fun here for Supposed Power hits
													Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

														//~~Setup a Melee Hit Struct

													Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
													Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = player[g_Player]->AttPos.Translation;	//Point of impact in world space
													Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
													Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
													
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((player[g_Player]->attposecnt - attstt) / ( cutoff - attstt ));
													if(((( player[g_Player]->attposecnt > ( stroke - 0.1 ) ) && ( player[g_Player]->attposecnt < ( stroke + 0.1 ))))) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;
													if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent < 0.75) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;

														//# Deduct Health
													player[g_Player]->HB_LastAvatarHitID = AItempcnt;
													/*if(Q_Forge->Forge[AItempcnt].HB_HReduceON == 0)*/ Q_Forge->Forge[AItempcnt].HB_ReduceOld = Q_Forge->Forge[AItempcnt].HB_Health;

															//Rework Needed here very messy , plus add a random factor
													//### Take Health and Give Energy to wounded Avatar
													Q_Forge->Forge[AItempcnt].HB_Energy += 6;

													Q_Forge->Forge[AItempcnt].HB_HealthHistory = Q_Forge->Forge[AItempcnt].HB_Health;

													if(HitType == 20)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (120 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 80 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 20;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((100 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 70) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 25;
														}

													if(HitType == 13)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 10;
														}

													if(HitType == 12)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 5;

														//Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 15;
														}

													if(HitType == 11)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (70 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 5;

														//Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 15;
														}

													if(HitType == 10)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 10;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 40) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 15;
														}

													if(HitType == 9)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 30 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 10;
														}

													if(HitType == 8)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 6;
														}

													if(HitType == 7)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 6;
														}

													if(HitType == 6)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 6;
														}

													if(HitType == 5)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 4;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														}

													if(HitType == 4)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (2 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 2;

														//Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														}

													if(HitType == 3)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														}

													if(HitType == 2)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 2;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 10;
														}

													if(HitType == 1)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 1;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														}

													if(HitType == 0)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 1;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 3;
														}

													//### Add damage to Experience store
													Q_Forge->Forge[AItempcnt].HB_HealthDiff = Q_Forge->Forge[AItempcnt].HB_HealthHistory - Q_Forge->Forge[AItempcnt].HB_Health;
													player[g_Player]->AvatarDMGSTORE[AItempcnt] += Q_Forge->Forge[AItempcnt].HB_HealthDiff;

													if(Q_Forge->Forge[AItempcnt].HB_Energy > Q_Forge->Forge[AItempcnt].HB_MaxEnergy) Q_Forge->Forge[AItempcnt].HB_Energy = Q_Forge->Forge[AItempcnt].HB_MaxEnergy;

													if(Q_Forge->Forge[AItempcnt].HB_Health <= 0)
														{
														Q_Forge->Forge[AItempcnt].HB_Health = 0;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

														Q_Forge->Forge[AItempcnt].HB_Dead = 1;

														jet = 0;
														while(jet < 5)
															{
															Q.PlayerSpawnNNbot(Q_Forge->Forge[AItempcnt].AV.Xform.Translation);

															jet++;
															}

														if((player[g_Player]->AvatarDMGSTORE[AItempcnt] * (Q_Forge->Forge[AItempcnt].CharDATA.Level / 10)) > 0)
															{
															//### Add Experience to attacking AVATAR
															player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[AItempcnt] * (Q_Forge->Forge[AItempcnt].CharDATA.Level / 10);

															player[g_Player]->MSG_XPON = 1;
															player[g_Player]->MSG_XPInit = 0;
															player[g_Player]->MSG_XPScreenDIST = 0;
															player[g_Player]->MSG_XPScreenDistINC = 50;
															player[g_Player]->MSG_XPScreenDIR = 0;
															player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10);
															}

														//##### Find KO Owner
														UniversalDMGSTR = 0;
														
														if(player[g_Player]->AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

														jet = 0;
														while(jet < _->NomAI)
															{
															if(Q_Forge->Forge[jet].LIVE == 1)
																{
																if(Q_Forge->Forge[jet].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
																}
															jet++;
															}

														if(DeliverKOID == 250)
															{
															//### Create Item for attacking Avatar
															player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

															if(player[g_Player]->DecFinger <= 50 || 1)
																{
																player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[AItempcnt].CharDATA.Level);
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
														SCRAM = 0;
														while(SCRAM < _->NomAI)
															{
															if(Q_Forge->Forge[SCRAM].LIVE == 1)
																{
																if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10)) > 0)
																	{
																	//### Add Experience to attacking AVATAR
																	player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10);

																	//### Force Net player to update (Net Play Only)
																	if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
																	}

																if(DeliverKOID == SCRAM)
																	{
																	//### Create Item for attacking Avatar
																	Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

																	if(Q_Forge->Forge[SCRAM].DecFinger <= 50 || 1)
																		{
																		//### CREATE NEW ITEM
																		if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0)
																			{
																			Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[AItempcnt].CharDATA.Level);

																			Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																			}
																		else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID, Q_Forge->Forge[AItempcnt].CharDATA.Level);
																		}
																	}
																}
															SCRAM++;
															}

														//####### DEACTIVATE ITEM ATTRIBUTES
														Q.DeactivateItems();

														//### Write out CHARDATA
														Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

														//####### REACTIVATE ITEM ATTRIBUTES
														Q.ActivateItems();
														}


													Q_Forge->Forge[AItempcnt].HB_HReduceON = 1;
													
													Q_Forge->Forge[AItempcnt].HB_ReduceHInc = 10;
													Q_Forge->Forge[AItempcnt].HB_ReduceHeight = 573;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.red = 255;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.green = 0;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.blue = 0;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.alpha = 255;

													if(Q_Forge->Forge[AItempcnt].Shadows[1].Avatar != 0)
														{
														Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AItempcnt].Shadows[1].Xform.Translation);
														Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AItempcnt].Shadows[2].Xform.Translation);
														Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AItempcnt].Shadows[3].Xform.Translation);
														Qpo->Avatar_ClearPose(Q_Forge->Forge[AItempcnt].Shadows[1].Avatar, &Q_Forge->Forge[AItempcnt].Shadows[1].Xform);
														Qpo->Avatar_ClearPose(Q_Forge->Forge[AItempcnt].Shadows[2].Avatar, &Q_Forge->Forge[AItempcnt].Shadows[2].Xform);
														Qpo->Avatar_ClearPose(Q_Forge->Forge[AItempcnt].Shadows[3].Avatar, &Q_Forge->Forge[AItempcnt].Shadows[3].Xform);
														}

													if(HitType == 0)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((50*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+20) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 60;	//EDIT********
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														//Q_Forge->Forge[AItempcnt].HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														Q_Forge->Forge[AItempcnt].HitReactScale = 0.09;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0.1 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 1)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((70*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+30) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 70;	//EDIT********
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.032 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 2;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}


													if(HitType == 2)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(player[g_Player]->JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}


														//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 6;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}


													if(HitType == 3)	//Standard Hit Up into Air Slightly
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(player[g_Player]->JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}


														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
														Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 8.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 7;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 13)	//Standard Hit Up into Air Slightly
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(player[g_Player]->JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
														Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));
																						//13.2
														player[g_Player]->HB_Energy += 7;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 4)	//Spin Kick Full Rotation Small Hits
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 5)	//Combo 1 Heavy KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														if(Q_Forge->Forge[AItempcnt].MoveReactVec.y > 0.1) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0.1;
														if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 6)	//Combo 1 Heavy KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 7)	//Hit Up into Air Dramatically
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(player[g_Player]->JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}
														
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 1.85;
														Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 1.85;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;

														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 14 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 7;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 8)	//Combo 2 Steady Kicks
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Qpo->Vec3d_New(&Q_Forge->Forge[AItempcnt].MoveReactVec);
														
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 9)	//Heavy KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);	//250			//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 255;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 255;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 255;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														if(Q_Forge->Forge[AItempcnt].HitReactScale != 0)
															{
															Q_Forge->Forge[AItempcnt].HitReactScale /= 1.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
															}
														else Q_Forge->Forge[AItempcnt].HitReactScale = 0.025 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
																							//0.075
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 9;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 10)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;	
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));	//15

														player[g_Player]->HB_Energy += 5;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

														//##### Camera Shake For Super Hits
														player[g_Player]->CameraShake = 1;
														player[g_Player]->CamShkTIME = 4;
														}

													if(HitType == 11)	//Combo extern No KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 12)	//JSRush Combo
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														player[g_Player]->HB_Energy += 1;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
														}

													if(HitType == 20)	//Ultra Blow
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));	//30

														player[g_Player]->HB_Energy += 2;
														if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

														//##### Camera Shake For Super Hits
														player[g_Player]->CameraShake = 2;
														player[g_Player]->CamShkTIME = 6;
														}

													// Assign Heavy Hits
													if(player[g_Player]->JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

													//## Reset Hit Wall
													Q_Forge->Forge[AItempcnt].HitWall = 0;

													//#####- Hit Reaction Motions -#####
													if(Q_Forge->Forge[AItempcnt].HB_DmgSTORE >= 135)
														{
														if(player[g_Player]->JinkSpecialON >= 1)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HB_RecoverMode = 1;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORE = 0;		//### Reset Damage Storage
														}

													if(HitType == 10 || HitType == 20)
														{
														if(player[g_Player]->JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 91)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 91;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{	//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.47;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 51)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 51;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{	//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.47;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 3; }
														}

													//Increment number of MeleeHits
													_->NomMelHit += 1;

													detcnt = 22;

													//###### Check for break through hit
													if((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK <= 0) && ((Q_Forge->Forge[AItempcnt].Block == 1 && (Q_Forge->Forge[AItempcnt].BlockHeight == BlowHeight)) || (Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 3 && BlowHeight == 2)))
														{
														//Set Player Enemy Display to correct enemy
														player[g_Player]->HB_LastAvatarHitID = AItempcnt;

														//### Block Hit Flash
														Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
														Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
														Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																							//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
														Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = player[g_Player]->AttPos.Translation;	//Point of impact in world space
														Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
														Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
														Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((player[g_Player]->attposecnt - attstt) / ( cutoff - attstt ));
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 0;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 160;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 0;

															//Increment number of MeleeHits
														_->NomMelHit += 1;
														detcnt = 22;
														}
													}//END-Else/Deflect (true HIT)

												}//END Block Check
											else					//>--BLOCKED--<
												{
												//##### Vector to move by (world-space)
												Qpo->Vec3d_Subtract(&player[g_Player]->AttPos.Translation, &player[g_Player]->OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
												Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
												Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;


												if(HitType == 0)
													{
													//###Hit Reactions
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0.1 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}

												if(HitType == 1)
													{
													//###Hit Reactions
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.032 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}


												if(HitType == 2)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}


												if(HitType == 3)	//Standard Hit Up into Air Slightly
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
													Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (5.2 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}


												if(HitType == 13)	//Standard Hit Up into Air Slightly
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
													Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
																					//11
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}


												if(HitType == 4)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}

												if(HitType == 5)	//Combo 1 Heavy KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													if(Q_Forge->Forge[AItempcnt].MoveReactVec.y > 0.1) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0.1;
													if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 6)	//Combo 1 Heavy KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 7)	//Hit Up into Air Dramatically
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 1.85;
													Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 1.85;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;

													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (14 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 8)	//Combo 2 Steady Kicks
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Qpo->Vec3d_New(&Q_Forge->Forge[AItempcnt].MoveReactVec);
													
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 9)	//Heavy KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.075 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 10)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 11)	//Combo extern No KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 12)	//JSRush Combo
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 20)	//Ultra Blow
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.0035 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												//Assign Shock Block Flash
												if(player[g_Player]->JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;

												//### Block hit flag
												Q_Forge->Forge[AItempcnt].Block = 1;
												Q_Forge->Forge[AItempcnt].BlockHitFLAG = 1;
												Q_Forge->Forge[AItempcnt].attposecnt = 0;
												Q_Forge->Forge[AItempcnt].BlockHitID = _->NomMelHit;

												//Set Player Enemy Display to correct enemy
												player[g_Player]->HB_LastAvatarHitID = AItempcnt;

												//### Block Hit Flash
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = player[g_Player]->AttPos.Translation;	//Point of impact in world space
												Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
												Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((player[g_Player]->attposecnt - attstt) / ( cutoff - attstt ));
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

												//Expandro3D Struct
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;

												/*Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
												Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;

												Q_Forge->Forge[AItempcnt].MoveReactSpeed = 3;*/

													//Increment number of MeleeHits
												_->NomMelHit += 1;

												detcnt = 22;
												}//END Else/Block
											}//END Dodge
										}//END OBB
									}//END BoneFilter
								}//END AntiMultHits
							detcnt += 1;
							}
						}
					}
				}
			AItempcnt++;
			}
		}
	}


	//### AI COLLISION DETECTION ###

void Q_COREFunctions::ColldetMeleeAI(int bonenum, float attstt, float cutoff, float stroke, int HitType, int BlowHeight, int NumAttackHits, int AIflag)
	{
	//INITIAL SHIELD HIT CHECK
	Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = 1.2;	//0.2
	Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 0;

	//###### SWITCH OUT ATTACK SPECS
	switch(Q_Forge->Forge[AIflag].Aposestate)
		{
		case 65:	//RUSH ELBOW
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[1].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 22:	//LEAP SPIN KICK
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[2].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 31:	//RIGHT HEAVY KICK
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[5].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 58:	//SKY PUSH
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[7].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 61:	//TWIST KICK
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[8].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 32://FLAME UPPERCUT
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[10].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 35://VERY HEAVY KICK
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[11].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 76://JS RUSH UP
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[17].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 85://JS RUSH PUNCH
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[13].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 73://JS RUSH
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[14].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 64://POWER COMBO
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[19].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 75://Static Kick
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[20].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 57://JS FLAME UPPERCUT
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[22].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 25://HYPER KNEE FLEX
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[23].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 53://AIR DASH
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[25].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 56://SAKURA TRIBUTE
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[26].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 34://SPIN KICK FULL ROTATION
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[27].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;

		case 84://CYCLONE KICK
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[16].Power / 5000) * 15) + 1;
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
			break;
		}

	Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower / 100);

	//##### ITEM ATTRIBUTE INCREMENT #####
	if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 1)
		{
		Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER += (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKINCpower / 10);
		}

	//### Check for within player shield
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

	if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2) && (player[g_Player]->Cleric.ShieldAlpha > 0) && (player[g_Player]->Team != Q_Forge->Forge[AIflag].Team) && (player[g_Player]->HB_Energy > 0))
		{
		TESTPosS = Q_Forge->Forge[AIflag].AttPos.Translation;
		TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

		if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
			{
			if(_->NetworkOption != 1) player[g_Player]->HB_Energy -= (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER * 8) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));

			jet=0;
			while((jet < 14) && (_->NomPntSprite < Q_PNTSPRITE_MAX))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 12;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}
	}

	g_Player = 0;

	if(_->NetworkOption != 1)
		{
		//######===-- Q_Object->Object COLLISION DETECTION --===#######
		SCRAM=0;
		while(SCRAM < _->NomQObject)
			{
			if(Q_Object->Object[SCRAM].LIVE == 1 && Q_Object->Object[SCRAM].AvID != AIflag)
				{
				//### COLLISION CHECK
				if(Q_Object->Object[SCRAM].StrengthBANK > 0)
					{
					switch(Q_Object->Object[SCRAM].CollisionTYPE)
						{
						case 0:
							{
							TESTPosS = Q_Forge->Forge[AIflag].AttPos.Translation;
							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Object->Object[SCRAM].Pos);

							if(TESTShieldDIST < Q_Object->Object[SCRAM].Scale)
								{
								//Set Player Enemy Display to correct enemy
								Q_Forge->Forge[AIflag].HB_LastAvatarHitID = (SCRAM + 1) * -1;

								//### Block Hit Flash
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
								Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;
								
								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 200;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 60;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 200;

									//Increment number of MeleeHits
								_->NomMelHit += 1;

								Q_Object->Object[SCRAM].StrengthBANK -= Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER * 8;
								}

							}break;
						}
					}
				}

			SCRAM++;
			}

		for (unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		Qpo->Avatar_GetBoneBoxes(AIflag, BoneDef[bonenum], &pCorner, &DX, &DY, &DZ, &ColldetBox);

		ColldetBox.Min = Q_Forge->Forge[AIflag].AV.Xform.Matrix.multiply_rotation(ColldetBox.Min);
		ColldetBox.Max = Q_Forge->Forge[AIflag].AV.Xform.Matrix.multiply_rotation(ColldetBox.Max);

		Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
		Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

		player[g_Player]->LimPosBox.Matrix = Q_Forge->Forge[AIflag].AV.Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
		coldetresult = Q_Forge->Forge[AIflag].AV.Xform.Matrix.multiply_rotation(pCorner);

		player[g_Player]->LimPosBox.Translation.x = coldetresult.x + Q_Forge->Forge[AIflag].AV.Xform.Translation.x;
		player[g_Player]->LimPosBox.Translation.y = coldetresult.y + Q_Forge->Forge[AIflag].AV.Xform.Translation.y;
		player[g_Player]->LimPosBox.Translation.z = coldetresult.z + Q_Forge->Forge[AIflag].AV.Xform.Translation.z;

		xScale = Qpo->Vec3d_Length(&DZ)/1.5;
		yScale = Qpo->Vec3d_Length(&DY)/1.5;
		zScale = Qpo->Vec3d_Length(&DX)/1.5;
		Qpo->Box_Set(&_->Box, xScale, yScale, zScale, &player[g_Player]->LimPosBox);

		//####  First Stage - Avatar Ext Bounding Box Check  ####//
#if 0
		if(Qpo->Collision_Avatar_Player_Intersect(AIflag))
#endif
#if 1
		if(Qpo->Avatar_Player_ExtBox_intersect(AIflag))
#endif
			{
			detcnt = 0;
			while(detcnt < 21)	//####  Second Stage - Bone Ext Bounding Box Check  ####//
				{
				Qpo->Player_GetBoneBoundingBox(BoneDef[detcnt], &pCorner, &DX, &DY, &DZ);

				Qpo->Transform_New_LeftUpIn(&bonepos, &DY, &DX, &DZ);
				Qpo->Transform_Orthonormalize(&bonepos);

				bonepos.Matrix = playerAV[g_Player]->Xform.Matrix * bonepos.Matrix;
				coldetresult = playerAV[g_Player]->Xform.Matrix.multiply_rotation(pCorner);

				bonepos.Translation.x = coldetresult.x + playerAV[g_Player]->Xform.Translation.x;
				bonepos.Translation.y = coldetresult.y + playerAV[g_Player]->Xform.Translation.y;
				bonepos.Translation.z = coldetresult.z + playerAV[g_Player]->Xform.Translation.z;

				xScale = Qpo->Vec3d_Length(&DZ)/1.5;
				yScale = Qpo->Vec3d_Length(&DY)/1.5;
				zScale = Qpo->Vec3d_Length(&DX)/1.5;
				Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &bonepos);
				
				//### Anti Multiple Hits System / Team Checks
				if(Q_Forge->Forge[AIflag].AntiMultHits[250] < NumAttackHits && Q_Forge->Forge[AIflag].Team != player[g_Player]->Team)
					{
					//### Filter Out unused bones
					if(!(detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16 && player[g_Player]->Aposestate != 21)
						   && !(player[g_Player]->Aposestate == 21 && ( detcnt == 1 || detcnt == 3 || detcnt == 6 || detcnt == 12
						   || detcnt == 15 || detcnt == 16 || detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16)))
						{
						if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &_->Box) || (( Q_Forge->Forge[AIflag].attposecnt > ( stroke - 0.15 )) && ( Q_Forge->Forge[AIflag].attposecnt < ( stroke + 0.15 )) ))
							{	//COLLISION
							//### Dodge Checks
							if(!(player[g_Player]->HB_Dead == 1) && !(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 1 && BlowHeight == 3) && !(player[g_Player]->CrouchInit == 1 && BlowHeight == 3) && !(player[g_Player]->AirBorn == 1 && BlowHeight == 1) && !(player[g_Player]->Flip == 1 && BlowHeight == 1) && !(player[g_Player]->HB_RecoverMode == 2 && (BlowHeight == 2 || BlowHeight == 3)))
								{
								//>>>---  Possible Hit On Avatar, Update Hits  ---<<<
								Q_Forge->Forge[AIflag].attackhits++;

								//>>>---  Definate Hit On Avatar, Update Hits  ---<<<
								Q_Forge->Forge[AIflag].AntiMultHits[250]++;

								Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = 1.2;	//0.2
								Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 0;

								//###### SWITCH OUT ATTACK SPECS
								switch(Q_Forge->Forge[AIflag].Aposestate)
									{
									case 65:	//RUSH ELBOW
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[1].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 22:	//LEAP SPIN KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[2].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 31:	//RIGHT HEAVY KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[5].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 58:	//SKY PUSH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[7].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 61:	//TWIST KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[8].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 32://FLAME UPPERCUT
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[10].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 35://VERY HEAVY KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[11].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 76://JS RUSH UP
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[17].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 85://JS RUSH PUNCH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[13].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 73://JS RUSH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[14].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 64://POWER COMBO
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[19].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 75://Static Kick
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[20].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 57://JS FLAME UPPERCUT
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[22].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 25://HYPER KNEE FLEX
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[23].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 53://AIR DASH
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[25].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 56://SAKURA TRIBUTE
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[26].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 34://SPIN KICK FULL ROTATION
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[27].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;

									case 84://CYCLONE KICK
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[16].Power / 5000) * 15) + 1;
										Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
										break;
									}

								Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower / 100);

								//##### ITEM ATTRIBUTE INCREMENT #####
								if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 1)
									{
									Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER += (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKINCpower / 100);
									}

								//######## Aggressive to defensive power check
								if((player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == BlowHeight) || (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3 && BlowHeight == 2))
									{
									if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower + (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.PhysicalStr) * (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER;
									else player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK -= (((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower + (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.PhysicalStr) * (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER)/2;

									if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = 0;

									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PBTIMER = TIME;
									}

								//###### Set Limb Strengths
								//Left Arm
								if(bonenum == 5 || bonenum == 4)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftArmSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftArmSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								//Right Arm
								if(bonenum == 14 || bonenum == 13)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightArmSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightArmSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								//Left Leg
								if(bonenum == 3 || bonenum == 1)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftLegSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftLegSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								//Right Leg
								if(bonenum == 10 || bonenum == 12)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightLegSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightLegSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
									}

								///////- BALANCE EDIT -////////
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH /= 10;
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP /= 2;

								//##### Player Blocking
								if(((player[g_Player]->Block == 0 || (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight != BlowHeight)) && !(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3 && BlowHeight == 2)) || (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0))
									{
									if(player[g_Player]->DeflectLethal == 1 && Q_Forge->Forge[AIflag].JinkSpecialON < 1)
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_Forge->Forge[AIflag].JinkSpecialON;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
										Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;

										//### Register Deflect Power
										if(player[g_Player]->DeflectPower == 0) Q_Forge->Forge[AIflag].HitReactScale = 0.03*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness*0.5)+0.5)*((1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELRawPower/35))+0.6);
										else Q_Forge->Forge[AIflag].HitReactScale = 0.01*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness*0.5)+0.5)*((1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELRawPower/35))+0.6);

										Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
										Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);
										Qpo->Vec3d_Inverse(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

										Q_Forge->Forge[AIflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										Q_Forge->Forge[AIflag].MoveReactVec.y = 0;
										Q_Forge->Forge[AIflag].MoveReactSpeed = 5.5;

										Q_Forge->Forge[AIflag].Aposestate = 28;
										Q_Forge->Forge[AIflag].attackon = 1;
										Q_Forge->Forge[AIflag].attposecnt = 0;

										Q_Forge->Forge[AIflag].astackcnt = 0;
										Q_Forge->Forge[AIflag].astackrun = 0;

										_->NomMelHit++;
										}
									else
										{
										//CALCULATE HIT REACTIONS
										// Vector to move by (world-space)
										Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
										lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										//XXXXXXXXXXXXX
										//Manually calculate the LOCAL X axis vector in WORLD - SPACE!!
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Shift.x = 10;
										Shift.y = 0;
										Shift.z = 0;
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixX);

											//Move Joint back into place
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,-10,0,0);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//YYYYYYYYYYYYYYYY
										//Manually calculate the LOCAL Y axis vector in WORLD - SPACE!!
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Shift.x = 0;
										Shift.y = 10;
										Shift.z = 0;
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixY);

											//Move Joint back into place
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,0,-10,0);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//ZZZZZZZZZZZZZZ
										//Manually calculate the LOCAL Z axis vector in WORLD - SPACE!!
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Shift.x = 0;
										Shift.y = 0;
										Shift.z = 10;
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
										AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
										Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixZ);

											//Move Joint back into place
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
										Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,0,0,-10);
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//Clear Bone Matrix
										Qpo->Transform_New(&BoneMatrix);

										Qpo->Vec3d_Inverse(&BoneMatrixX);

										//Build the bone matrix
										Qpo->Transform_New_LeftUpIn(&BoneMatrix, &BoneMatrixX, &BoneMatrixY, &BoneMatrixZ);

										Qpo->Transform_Orthonormalize(&BoneMatrix);

										Qpo->Body_GetBone(LisaBody, BoneNum[detcnt], &BoneName, &Attachment, &ParBone);
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, ParBone, &Q_Forge->Forge[AIflag].TempXForm2);
										BoneMatrix.Translation.x = Q_Forge->Forge[AIflag].TempXForm2.Translation.x;
										BoneMatrix.Translation.y = Q_Forge->Forge[AIflag].TempXForm2.Translation.y;
										BoneMatrix.Translation.z = Q_Forge->Forge[AIflag].TempXForm2.Translation.z;

										//Transform the reaction vector by the transpose of the bone matrix
										Qpo->Transform_TransposeVector(&BoneMatrix, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										// Scale the vector to make the reaction more visible for testing
										Qpo->Vec3d_Scale(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, lengthvec, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										// Get the local xform of the bone
										Qpo->Avatar_GetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										// Translate the bone's xform by the altered vector	
										Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_Forge->Forge[AIflag].TempXForm1.Translation); 

										// Set the local bone xform to the new location
										Qpo->Avatar_SetJointTransform(playerAV[g_Player]->Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

										//Reset Reaction vector
										Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

										//Not sure if this Normalising is fun here for Supposed Power hits
										Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
										Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

											//~~Setup a Melee Hit Struct

										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
										Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
										if(((( Q_Forge->Forge[AIflag].attposecnt > ( stroke - 0.1 ) ) && ( Q_Forge->Forge[AIflag].attposecnt < ( stroke + 0.1 ))))) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;
										if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent < 0.75) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;

											//# Deduct Health
										Q_Forge->Forge[AIflag].HB_LastAvatarHitID = AItempcnt;
										/*if(player[g_Player]->HB_HReduceON == 0)*/ player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;


												//Rework Needed here very messy , plus add a random factor
										//### Take Health and Give Energy to wounded Avatar
										player[g_Player]->HB_Energy += 6;

										player[g_Player]->HB_HealthHistory = player[g_Player]->HB_Health;

										if(HitType == 20)
											{
											player[g_Player]->HB_Health -= (80 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 50 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 20;

											player[g_Player]->HB_DmgSTORE += ((80 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 50) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 25;
											}

										if(HitType == 13)
											{
											player[g_Player]->HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
											}

										if(HitType == 12)
											{
											player[g_Player]->HB_Health -= (30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 5;

											//player[g_Player]->HB_DmgSTORE += ((30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
											}

										if(HitType == 11)
											{
											player[g_Player]->HB_Health -= (70 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 5;

											//player[g_Player]->HB_DmgSTORE += ((30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
											}

										if(HitType == 10)
											{
											player[g_Player]->HB_Health -= (50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 10;

											player[g_Player]->HB_DmgSTORE += ((50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 40) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
											}

										if(HitType == 9)
											{
											player[g_Player]->HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
											}

										if(HitType == 8)
											{
											player[g_Player]->HB_Health -= (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
											}

										if(HitType == 7)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
											}

										if(HitType == 6)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
											}

										if(HitType == 5)
											{
											player[g_Player]->HB_Health -= (20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 4;

											player[g_Player]->HB_DmgSTORE += ((20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 4)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 4;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 3)
											{
											player[g_Player]->HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 3;

											player[g_Player]->HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 2)
											{
											player[g_Player]->HB_Health -= (35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 2;

											player[g_Player]->HB_DmgSTORE += ((35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
											}

										if(HitType == 1)
											{
											player[g_Player]->HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 1;

											player[g_Player]->HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
											}

										if(HitType == 0)
											{
											player[g_Player]->HB_Health -= (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											player[g_Player]->HB_Energy += 1;

											player[g_Player]->HB_DmgSTORE += ((8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
											player[g_Player]->HB_DmgSTORETimer = TIME;

											Q_Forge->Forge[AIflag].Q_Brain.Aggression += 3;
											}

										//### Add damage to Experience store
										player[g_Player]->HB_HealthDiff = player[g_Player]->HB_HealthHistory - player[g_Player]->HB_Health;
										Q_Forge->Forge[AIflag].AvatarDMGSTORE[250] += player[g_Player]->HB_HealthDiff;

										if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

										if(player[g_Player]->HB_Health <= 0)
											{
											player[g_Player]->HB_Health = 0;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 11;

											player[g_Player]->HB_Dead = 1;

											//### Add Experience to attacking AVATAR
											if((Q_Forge->Forge[AIflag].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
												{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AIflag].CDATID].UnusedXP += Q_Forge->Forge[AIflag].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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

														//### Force Net player to update (Net Play Only)
														if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
														}

													if(DeliverKOID == SCRAM)
														{
														//### Create Item for attacking Avatar
														Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

														if(Q_Forge->Forge[SCRAM].DecFinger <= 50 || 1)
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

											//### Write out CHARDATA
											Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

											//####### REACTIVATE ITEM ATTRIBUTES
											Q.ActivateItems();
											}

										player[g_Player]->HB_HReduceON = 1;
										player[g_Player]->HB_ReduceHInc = 10;
										player[g_Player]->HB_ReduceHeight = 573;
										player[g_Player]->HB_ReduceRectColor.red = 255;
										player[g_Player]->HB_ReduceRectColor.green = 0;
										player[g_Player]->HB_ReduceRectColor.blue = 0;
										player[g_Player]->HB_ReduceRectColor.alpha = 255;

										if(player[g_Player]->Shadows[1].Avatar != 0)
											{
											Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
											Qpo->Avatar_ClearPose(player[g_Player]->Shadows[1].Avatar, &player[g_Player]->Shadows[1].Xform);
											Qpo->Avatar_ClearPose(player[g_Player]->Shadows[2].Avatar, &player[g_Player]->Shadows[2].Xform);
											Qpo->Avatar_ClearPose(player[g_Player]->Shadows[3].Avatar, &player[g_Player]->Shadows[3].Xform);
											}

										if(HitType == 0)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;	//0.04

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 1)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.05 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 2;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 2)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.05 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 4;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 3)	//Standard Hit Up into Air Slightly
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 1;
											player[g_Player]->MoveReactVec.x /= 3;
											player[g_Player]->MoveReactVec.z /= 3;
											player[g_Player]->MoveReactSpeed = 8.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//5.2	//6 V-Good

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}


										if(HitType == 13)	//Standard Hit Up into Air Slightly
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 1;
											player[g_Player]->MoveReactVec.x /= 3;
											player[g_Player]->MoveReactVec.z /= 3;
											player[g_Player]->MoveReactSpeed = 8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}


										if(HitType == 4)	//Spin Kick Full Rotation
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;	
											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 5)	//Combo 1 Heavy KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}
											
											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											if(player[g_Player]->MoveReactVec.y > 0.1) player[g_Player]->MoveReactVec.y = 0.1;
											if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 6)	//Combo 1 Heavy KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 7)	//Hit Up into Air Dramatically
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
												}
											
											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 1;
											player[g_Player]->MoveReactSpeed = 6.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//6 V-Good

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 8)	//Combo 2 Steady Kicks
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											Qpo->Vec3d_New(&player[g_Player]->MoveReactVec);
											
											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 9)	//Heavy KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);	//250			//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 255;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											if(player[g_Player]->HitReactScale != 0)
												{
												player[g_Player]->HitReactScale /= 1.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
												}
											else player[g_Player]->HitReactScale = 0.025 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 9;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;	
											player[g_Player]->MoveReactSpeed = 6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//4.5

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 10)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											player[g_Player]->HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 5;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;

											//##### Camera Shake For Super Hits
											player[g_Player]->CameraShake = 1;
											player[g_Player]->CamShkTIME = 4;
											}


										if(HitType == 11)	//Combo extern No KnockBack
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.01 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
											
											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 12)	//JSRush Combo
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
											
											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
												{
												if(player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 28;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}
											else
												{
												if(player[g_Player]->Aposestate != 26)	//Standard Hit Reactions
													{
													player[g_Player]->Aposestate = 26;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->attposecnt = 0.16;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}

												//'Hit Sound'
												if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
													{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 4; }
												}

											player[g_Player]->HitReactScale = 0.01 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												}

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactVec.y = 0;
											if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
											player[g_Player]->MoveReactSpeed = 7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
											}

										if(HitType == 20)	//Ultra Blow
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

											//###Hit Reactions
											player[g_Player]->HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

											if(detcnt == 0)		//Head Hit
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
												}

											Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactSpeed = 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100))));	//15

											Q_Forge->Forge[AIflag].HB_Energy += 15 * 2;
											if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;

											//##### Camera Shake For Super Hits
											player[g_Player]->CameraShake = 1;
											player[g_Player]->CamShkTIME = 4;
											}

										// Assign Heavy Hits
										if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

										//#####- Hit Reaction Motions -#####
										if(player[g_Player]->HB_DmgSTORE >= 135)
											{
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1)
												{
												if(player[g_Player]->Aposestate != 90)
													{
													player[g_Player]->Aposestate = 90;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{
													if(player[g_Player]->attposecnt >= 2) player[g_Player]->attposecnt = 2;
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 5; }

											player[g_Player]->HB_RecoverMode = 1;
											player[g_Player]->HB_DmgSTORE = 0;		//### Reset Damage Storage
											}

										// Turn On for AI Timeholes
										if(player[g_Player]->Aposestate == 17 || player[g_Player]->Aposestate == 22 || player[g_Player]->Aposestate == 25 || player[g_Player]->Aposestate == 31 || player[g_Player]->Aposestate == 33 || player[g_Player]->Aposestate == 35 || player[g_Player]->Aposestate == 40 || player[g_Player]->Aposestate == 45) _->TimeHole = 1;
										if(player[g_Player]->Aposestate == 10 || player[g_Player]->Aposestate == 21 || player[g_Player]->Aposestate == 24 || player[g_Player]->Aposestate == 34 || player[g_Player]->Aposestate == 39) _->TimeHole = 2;
										if(player[g_Player]->Aposestate == 13 || player[g_Player]->Aposestate == 41 || player[g_Player]->Aposestate == 44 || player[g_Player]->Aposestate == 32) _->TimeHole = 3;

										if(HitType == 10 || HitType == 20)
											{
											if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
												{
												if(player[g_Player]->Aposestate != 91)
													{
													player[g_Player]->Aposestate = 91;
													player[g_Player]->attackon = 1;
													player[g_Player]->attposecnt = 0;
													player[g_Player]->CrunchTimer = 0;

													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												else
													{	//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->CrunchTimer = 0;

													player[g_Player]->attposecnt = 0.47;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}
											else
												{
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
													{	//Reset DownSpeed
													player[g_Player]->DownSpeed = 2;
													player[g_Player]->CrunchTimer = 0;

													player[g_Player]->attposecnt = 0.47;
													player[g_Player]->astackcnt = 0;
													player[g_Player]->astackrun = 0;
													}
												}

											//'Hit Sound'
											if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
												{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 6; }

											if(player[g_Player]->HB_DmgSTORE >= 135)
												{
												player[g_Player]->HB_RecoverMode = 1;
												player[g_Player]->HB_DmgSTORE = 0;		//### Reset Damage Storage
												}
											}

										//Increment number of MeleeHits
										_->NomMelHit += 1;

										detcnt = 22;

										if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0) && ((player[g_Player]->Block == 1 && (player[g_Player]->BlockHeight == BlowHeight)) || (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3 && BlowHeight == 2)))
											{
											//### Block Hit Flash
											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																				//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
											Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 160;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 0;

												// Vector to move by (world-space)
											//Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
											//lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
											//Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
											//player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
											//player[g_Player]->MoveReactSpeed = 5;	//5.4;

												//Increment number of MeleeHits
											_->NomMelHit += 1;

											detcnt = 22;

											//##### RESET POWERBANK
											//player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2);
											}

										}//END Else/Deflect (true HIT)

									}//END Block
								else				//-- BLOCK --
									{
									//##### Vector to move by (world-space)
									Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
									lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
									Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;

									if(HitType == 0)
										{
										//player[g_Player]->HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
										player[g_Player]->HitReactScale = 0.09 * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (0.1 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 1)
										{
										player[g_Player]->HitReactScale = (0.032 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 2)
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 3)	//Standard Hit Up into Air Slightly
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 1;
										player[g_Player]->MoveReactVec.x /= 3;
										player[g_Player]->MoveReactVec.z /= 3;
										player[g_Player]->MoveReactSpeed = (5.2 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 13)	//Standard Hit Up into Air Slightly
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 1;
										player[g_Player]->MoveReactVec.x /= 3;
										player[g_Player]->MoveReactVec.z /= 3;
										player[g_Player]->MoveReactSpeed = (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
													
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 4)
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
										}

									if(HitType == 5)	//Combo 1 Heavy KnockBack
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										if(player[g_Player]->MoveReactVec.y > 0.1) player[g_Player]->MoveReactVec.y = 0.1;
										if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 6)	//Combo 1 Heavy KnockBack
										{
										player[g_Player]->HitReactScale = (0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactSpeed = (4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 7)	//Hit Up into Air Dramatically
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.x /= 1.85;
										player[g_Player]->MoveReactVec.z /= 1.85;
										player[g_Player]->MoveReactVec.y = 1;

										player[g_Player]->MoveReactSpeed = (14 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 8)	//Combo 2 Steady Kicks
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										Qpo->Vec3d_New(&player[g_Player]->MoveReactVec);
										
										player[g_Player]->MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 9)	//Heavy KnockBack
										{
										player[g_Player]->HitReactScale = (0.075 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactSpeed = (6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 10)
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactSpeed = (13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 11)	//Combo extern No KnockBack
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 12)	//JSRush Combo
										{
										player[g_Player]->HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										player[g_Player]->MoveReactVec.y = 0;
										if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
										player[g_Player]->MoveReactSpeed = (7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									if(HitType == 20)	//Ultra Blow
										{
										player[g_Player]->HitReactScale = (0.0035 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2);

										player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
										player[g_Player]->MoveReactSpeed = (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 2.5);

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										}

									//Assign Shock Block Flash
									if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;

									player[g_Player]->Aposestate = 18;
									player[g_Player]->BlockHit = 1;
									player[g_Player]->BlockHitFLAG = 1;
									player[g_Player]->attposecnt = 0;
									player[g_Player]->BlockHitID = _->NomMelHit;

									//### Block Hit Flash
									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
									Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;

										// Vector to move by (world-space)
									/*player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
									player[g_Player]->MoveReactSpeed = 5;	//5.4;*/

										//Increment number of MeleeHits
									_->NomMelHit += 1;

									detcnt = 22;
									}//END Else/Block

								}//END Dodge

							}//END OBB

						}//END BF

					}//END AntiMultHits

				detcnt += 1;
				}
			}
		}

	g_Player = 0;
	}

	AItempcnt = 0;
	while(AItempcnt < _->NomAI)
		{
		if(Q_Forge->Forge[AItempcnt].LIVE == 1)
			{
			//#### INITIAL SHIELD CHECK
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = 1.2;	//0.2
			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 0;

			//###### SWITCH OUT ATTACK SPECS
			switch(Q_Forge->Forge[AIflag].Aposestate)
				{
				case 65:	//RUSH ELBOW
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[1].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 22:	//LEAP SPIN KICK
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[2].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 31:	//RIGHT HEAVY KICK
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[5].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 58:	//SKY PUSH
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[7].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 61:	//TWIST KICK
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[8].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 32://FLAME UPPERCUT
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[10].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 35://VERY HEAVY KICK
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[11].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 76://JS RUSH UP
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[17].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 85://JS RUSH PUNCH
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[13].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 73://JS RUSH
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[14].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 64://POWER COMBO
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[19].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 75://Static Kick
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[20].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 57://JS FLAME UPPERCUT
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[22].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 25://HYPER KNEE FLEX
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[23].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 53://AIR DASH
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[25].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 56://SAKURA TRIBUTE
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[26].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 34://SPIN KICK FULL ROTATION
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[27].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;

				case 84://CYCLONE KICK
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[16].Power / 5000) * 15) + 1;
					Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
					break;
				}

			Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower / 100);

			//##### ITEM ATTRIBUTE INCREMENT #####
			if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 1)
				{
				Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER += (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKINCpower / 10);
				}


			//### Check for avatar within shield
			if((Q_Forge->Forge[AItempcnt].CharDATA.Class == 2) && (Q_Forge->Forge[AItempcnt].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[AItempcnt].Team != Q_Forge->Forge[AIflag].Team) && (Q_Forge->Forge[AItempcnt].HB_Energy > 0))
				{
				TESTPosS = Q_Forge->Forge[AIflag].AttPos.Translation;
				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[AItempcnt].Shield.Xform.Translation);

				if(TESTShieldDIST < (65 * Q_Forge->Forge[AItempcnt].Cleric.ShieldScale))
					{
					//Q_Forge->Forge[AIflag].AntiMultHitsSHIELD[AItempcnt]++;

					if(_->NetworkOption != 1) Q_Forge->Forge[AItempcnt].HB_Energy -= (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER * 8) / (10 * (Q_Forge->Forge[AItempcnt].CharDATA.CLSClericSKILL[7].Duration/5000));

					jet=0;
					while((jet < 14) && (_->NomPntSprite < Q_PNTSPRITE_MAX))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 12;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					}
				}


			if(_->NetworkOption != 1)
				{
				if((AItempcnt != AIflag) && (Q_Forge->Forge[AItempcnt].Team != Q_Forge->Forge[AIflag].Team))
					{
					//####  First Stage - Avatar Ext Bounding Box Check  ####//
#if 0
					if(Qpo->Collision_Avatar_Intersect(AIflag, AItempcnt))
#endif
#if 1
					if(Qpo->Avatar_ExtBox_intersect(AIflag, AItempcnt))
#endif
						{
						detcnt = 0;
						while(detcnt < 21)	//####  Second Stage - Bone Ext Bounding Box Check  ####//
							{
							Qpo->Avatar_GetBoneBoundingBox(AItempcnt, BoneDef[detcnt], &pCorner, &DX, &DY, &DZ);

							Qpo->Transform_New_LeftUpIn(&bonepos, &DY, &DX, &DZ);
							Qpo->Transform_Orthonormalize(&bonepos);

							bonepos.Matrix = Q_Forge->Forge[AItempcnt].AV.Xform.Matrix * bonepos.Matrix;
							coldetresult = Q_Forge->Forge[AItempcnt].AV.Xform.Matrix.multiply_rotation(pCorner);

							bonepos.Translation.x = coldetresult.x + Q_Forge->Forge[AItempcnt].AV.Xform.Translation.x;
							bonepos.Translation.y = coldetresult.y + Q_Forge->Forge[AItempcnt].AV.Xform.Translation.y;
							bonepos.Translation.z = coldetresult.z + Q_Forge->Forge[AItempcnt].AV.Xform.Translation.z;

							xScale = Qpo->Vec3d_Length(&DZ)/1.5;
							yScale = Qpo->Vec3d_Length(&DY)/1.5;
							zScale = Qpo->Vec3d_Length(&DX)/1.5;
							Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &bonepos);

							//### Anti Multiple Hits System
							if(Q_Forge->Forge[AIflag].AntiMultHits[AItempcnt] < NumAttackHits)
								{
								//### Bone Filter
								if(!(detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16 && Q_Forge->Forge[AItempcnt].Aposestate != 21)
										&& !(Q_Forge->Forge[AItempcnt].Aposestate == 21 && ( detcnt == 1 || detcnt == 3 || detcnt == 6 || detcnt == 12
										|| detcnt == 15 || detcnt == 16 || detcnt == 4 || detcnt == 5 || detcnt == 7 || detcnt == 13 || detcnt == 14 || detcnt == 16)))
									{
									if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &_->Box) || (( Q_Forge->Forge[AIflag].attposecnt > ( stroke - 0.15 )) && ( Q_Forge->Forge[AIflag].attposecnt < ( stroke + 0.15 )) ))
										{	//COLLISION
										//### Dodge Checks
										if(!(Q_Forge->Forge[AItempcnt].HB_Dead == 1) && !(Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 1 && BlowHeight == 3) && !(Q_Forge->Forge[AItempcnt].CrouchInit == 1 && BlowHeight == 3) && !((Q_Forge->Forge[AItempcnt].AirBorn == 1 && BlowHeight == 1) || (Q_Forge->Forge[AItempcnt].Flip == 1 && BlowHeight == 1)) && !(Q_Forge->Forge[AItempcnt].HB_RecoverMode == 2 && (BlowHeight == 2 || BlowHeight == 3)))
											{

											//>>>---  Possible Hit On Avatar, Update Hits  ---<<<
											Q_Forge->Forge[AIflag].attackhits++;

											//>>>---  Definate Hit On Avatar, Update Hits  ---<<<
											Q_Forge->Forge[AIflag].AntiMultHits[AItempcnt]++;

											Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = 1.2;	//0.2
											Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 0;

											//###### SWITCH OUT ATTACK SPECS
											switch(Q_Forge->Forge[AIflag].Aposestate)
												{
												case 65:	//RUSH ELBOW
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[1].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 22:	//LEAP SPIN KICK
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[2].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 31:	//RIGHT HEAVY KICK
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[5].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 58:	//SKY PUSH
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[7].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 61:	//TWIST KICK
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[8].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 32://FLAME UPPERCUT
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[10].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 35://VERY HEAVY KICK
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[11].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 76://JS RUSH UP
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[17].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 85://JS RUSH PUNCH
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[13].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 73://JS RUSH
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[14].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 64://POWER COMBO
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[19].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 75://Static Kick
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[20].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 57://JS FLAME UPPERCUT
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[22].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 25://HYPER KNEE FLEX
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[23].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 53://AIR DASH
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[25].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 56://SAKURA TRIBUTE
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[26].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 34://SPIN KICK FULL ROTATION
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[27].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;

												case 84://CYCLONE KICK
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[AIflag].CharDATA.AttackSKILL[16].Power / 5000) * 15) + 1;
													Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT = 1;
													break;
												}

											Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower / 100);

											//##### ITEM ATTRIBUTE INCREMENT #####
											if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 1)
												{
												Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER += (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKINCpower / 10);
												}

											//######## Aggressive to defensive power check
											if((Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == BlowHeight) || (Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 3 && BlowHeight == 2))
												{
												if(Q_Forge->Forge[AIflag].CharDATA.BodySKILL.JINKATT == 0) Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower + (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.PhysicalStr) * (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER;
												else Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK -= (((float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.AggPower + (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.PhysicalStr) * (float)Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER)/2;

												if(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK = 0;

												Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.PBTIMER = TIME;
												}

											//SET LIMB STRENGTHS
											//Left Arm
											if(bonenum == 5 || bonenum == 4)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftArmSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftArmSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											//Right Arm
											if(bonenum == 14 || bonenum == 13)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightArmSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightArmSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											//Left Leg
											if(bonenum == 3 || bonenum == 1)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftLegSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.LeftLegSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											//Right Leg
											if(bonenum == 10 || bonenum == 12)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightLegSTRENGTH * Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER) / 4) + 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = ((Q_Forge->Forge[AIflag].CharDATA.BodySKILL.RightLegSNAP * (Q_Forge->Forge[AIflag].CharDATA.BodySKILL.ATTACKPOWER / 3.5)) / 6) + 1;
												}

											///////- BALANCE EDIT -////////
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH /= 10;
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP /= 2;

											//### Test For Avatar Blocking				//Not good create blocking flag for player
											if(((Q_Forge->Forge[AItempcnt].Block == 0 || (Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight != BlowHeight)) && !(Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 3 && BlowHeight == 2)) || (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK <= 0))
												{
												//### Test For Avatar Deflecting
												if(Q_Forge->Forge[AItempcnt].DeflectLethal == 1 && Q_Forge->Forge[AIflag].JinkSpecialON < 1)
													{
													Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_Forge->Forge[AIflag].JinkSpecialON;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																						//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
													Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = player[g_Player]->AttPos.Translation;	//Point of impact in world space
													Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
													Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

													//Expandro3D Struct
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
													Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;
													
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;

													Q_Forge->Forge[AIflag].HitReactScale = 0.01;

													//### Register Deflect Power
													if(Q_Forge->Forge[AItempcnt].DeflectPower == 0) Q_Forge->Forge[AIflag].HitReactScale = 0.03*((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELQuickness*0.5)+0.5)*((1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELRawPower/35))+0.6);
													else Q_Forge->Forge[AIflag].HitReactScale = 0.01*((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELQuickness*0.5)+0.5)*((1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.RELRawPower/35))+0.6);

													Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
													Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);
													Qpo->Vec3d_Inverse(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

													Q_Forge->Forge[AIflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AIflag].MoveReactVec.y = 0;
													Q_Forge->Forge[AIflag].MoveReactSpeed = 5.5;

													Q_Forge->Forge[AIflag].Aposestate = 28;
													Q_Forge->Forge[AIflag].attackon = 1;
													Q_Forge->Forge[AIflag].attposecnt = 0;

													Q_Forge->Forge[AIflag].astackcnt = 0;
													Q_Forge->Forge[AIflag].astackrun = 0;

													_->NomMelHit++;
													}
												else
													{
													//CALCULATE HIT REACTIONS
													// Vector to move by (world-space)
													Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
													lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													//XXXXXXXXXXXXX
													//Manually calculate the LOCAL X axis vector in WORLD - SPACE!!
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
													AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
													Shift.x = 10;
													Shift.y = 0;
													Shift.z = 0;
													Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
													AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
													Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixX);

														//Move Joint back into place
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,-10,0,0);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

													//YYYYYYYYYYYYYYYY
													//Manually calculate the LOCAL Y axis vector in WORLD - SPACE!!
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
													AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
													Shift.x = 0;
													Shift.y = 10;
													Shift.z = 0;
													Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
													AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
													Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixY);

														//Move Joint back into place
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,0,-10,0);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

													//ZZZZZZZZZZZZZZ
													//Manually calculate the LOCAL Z axis vector in WORLD - SPACE!!
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
													AxeStart = Q_Forge->Forge[AIflag].TempXForm2.Translation;
													Shift.x = 0;
													Shift.y = 0;
													Shift.z = 10;
													Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Shift, &Q_Forge->Forge[AIflag].TempXForm1.Translation);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[detcnt], &Q_Forge->Forge[AIflag].TempXForm2);
													AxeEnd = Q_Forge->Forge[AIflag].TempXForm2.Translation;
													Qpo->Vec3d_Subtract(&AxeEnd, &AxeStart, &BoneMatrixZ);

														//Move Joint back into place
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);
													Qpo->Transform_Translate(&Q_Forge->Forge[AIflag].TempXForm1,0,0,-10);
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

													//Clear Bone Matrix
													Qpo->Transform_New(&BoneMatrix);

													Qpo->Vec3d_Inverse(&BoneMatrixX);

													//Build the bone matrix
													Qpo->Transform_New_LeftUpIn(&BoneMatrix, &BoneMatrixX, &BoneMatrixY, &BoneMatrixZ);

													Qpo->Transform_Orthonormalize(&BoneMatrix);

													Qpo->Body_GetBone(LisaBody, BoneNum[detcnt], &BoneName, &Attachment, &ParBone);
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, ParBone, &Q_Forge->Forge[AIflag].TempXForm2);
													BoneMatrix.Translation.x = Q_Forge->Forge[AIflag].TempXForm2.Translation.x;
													BoneMatrix.Translation.y = Q_Forge->Forge[AIflag].TempXForm2.Translation.y;
													BoneMatrix.Translation.z = Q_Forge->Forge[AIflag].TempXForm2.Translation.z;

													//Transform the reaction vector by the transpose of the bone matrix
													Qpo->Transform_TransposeVector(&BoneMatrix, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													// Scale the vector to make the reaction more visible for testing
													Qpo->Vec3d_Scale(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, lengthvec, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													// Get the local xform of the bone
													Qpo->Avatar_GetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

													// Translate the bone's xform by the altered vector	
													Qpo->Vec3d_Add(&Q_Forge->Forge[AIflag].TempXForm1.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction, &Q_Forge->Forge[AIflag].TempXForm1.Translation); 

													// Set the local bone xform to the new location
													Qpo->Avatar_SetJointTransform(Q_Forge->Forge[AItempcnt].AV.Avatar.Pose, BoneNum[detcnt], &Q_Forge->Forge[AIflag].TempXForm1);

													//Reset Reaction vector
													Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

													//Not sure if this Normalising is fun here for Supposed Power hits
													Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
													Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

														//~~Setup a Melee Hit Struct
													Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
													Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
													Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
													Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AItempcnt].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
													if(((( Q_Forge->Forge[AIflag].attposecnt > ( stroke - 0.1 ) ) && ( Q_Forge->Forge[AIflag].attposecnt < ( stroke + 0.1 ))))) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;
													if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent < 0.75) Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 0.75;

														//# Deduct Health
													Q_Forge->Forge[AIflag].HB_LastAvatarHitID = AItempcnt;
													/*if(Q_Forge->Forge[AItempcnt].HB_HReduceON == 0)*/ Q_Forge->Forge[AItempcnt].HB_ReduceOld = Q_Forge->Forge[AItempcnt].HB_Health;

															//Rework Needed here very messy , plus add a random factor
													//### Take Health and Give Energy to wounded Avatar

													Q_Forge->Forge[AItempcnt].HB_Energy += 6;

													//### Add damage to Experience store
													player[g_Player]->HB_HealthHistory = player[g_Player]->HB_Health;

													if(HitType == 20)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (80 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 50 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 20;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((80 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 50) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 25;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 25;
														}

													if(HitType == 13)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 10;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
														}

													if(HitType == 12)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (30 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 5;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 15;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
														}

													if(HitType == 11)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (70 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 5;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 15;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
														}

													if(HitType == 10)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 40 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 10;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((50 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 40) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 15;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 15;
														}

													if(HitType == 9)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 10;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
														}

													if(HitType == 8)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((25 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 6;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
														}

													if(HitType == 7)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 6;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
														}

													if(HitType == 6)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 6;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 6;
														}

													if(HitType == 5)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 20 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 4;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((20 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 20) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
														}

													if(HitType == 4)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 4;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
														}

													if(HitType == 3)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 3;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((40 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
														}

													if(HitType == 2)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 2;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((35 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 10) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 10;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 10;
														}

													if(HitType == 1)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 1;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((15 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 5;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 5;
														}

													if(HitType == 0)
														{
														Q_Forge->Forge[AItempcnt].HB_Health -= (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Health -= 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * ((1 - (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
														Q_Forge->Forge[AItempcnt].HB_Energy += 1;

														Q_Forge->Forge[AItempcnt].HB_DmgSTORE += ((8 * Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent) + 5) * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORETimer = TIME;

														Q_Forge->Forge[AItempcnt].Q_Brain.Aggression -= 3;
														Q_Forge->Forge[AIflag].Q_Brain.Aggression += 3;
														}

													//### Add damage to Experience store
													Q_Forge->Forge[AItempcnt].HB_HealthDiff = Q_Forge->Forge[AItempcnt].HB_HealthHistory - Q_Forge->Forge[AItempcnt].HB_Health;
													Q_Forge->Forge[AIflag].AvatarDMGSTORE[AItempcnt] += Q_Forge->Forge[AItempcnt].HB_HealthDiff;

													if(Q_Forge->Forge[AItempcnt].HB_Energy > Q_Forge->Forge[AItempcnt].HB_MaxEnergy) Q_Forge->Forge[AItempcnt].HB_Energy = Q_Forge->Forge[AItempcnt].HB_MaxEnergy;

													if(Q_Forge->Forge[AItempcnt].HB_Health <= 0)
														{
														Q_Forge->Forge[AItempcnt].HB_Health = 0;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

														Q_Forge->Forge[AItempcnt].HB_Dead = 1;

														jet = 0;
														while(jet < 5)
															{
															Q.AISpawnNNbot(AIflag, Q_Forge->Forge[AItempcnt].AV.Xform.Translation);

															jet++;
															}

														//### Add XP to avatar
														if((Q_Forge->Forge[AIflag].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10)) > 0)
															{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[AIflag].CDATID].UnusedXP += Q_Forge->Forge[AIflag].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10); }

														//##### Find KO Owner
														UniversalDMGSTR = 0;
														
														if(Q_Forge->Forge[AIflag].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

														jet = 0;
														while(jet < _->NomAI)
															{
															if(Q_Forge->Forge[jet].LIVE == 1)
																{
																if(Q_Forge->Forge[jet].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
																}
															jet++;
															}

														if(DeliverKOID == 250)
															{
															//### Create Item for attacking Avatar
															Q_Forge->Forge[AIflag].DecFinger = ((float)rand() / 32767) * 100;

															if(Q_Forge->Forge[AIflag].DecFinger <= 50 || 1)
																{
																player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[AItempcnt].CharDATA.Level);
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
														SCRAM = 0;
														while(SCRAM < _->NomAI)
															{
															if(Q_Forge->Forge[SCRAM].LIVE == 1)
																{
																if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10)) > 0)
																	{
																	//### Add Experience to attacking AVATAR
																	player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[AItempcnt] * (10 * Q_Forge->Forge[AItempcnt].CharDATA.Level / 10);

																	//### Force Net player to update (Net Play Only)
																	if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 1;
																	}


																if(DeliverKOID == SCRAM)
																	{
																	//### Create Item for attacking Avatar
																	Q_Forge->Forge[SCRAM].DecFinger = ((float)rand() / 32767) * 100;

																	if(Q_Forge->Forge[SCRAM].DecFinger <= 50 || 1)
																		{
																		//### CREATE NEW ITEM
																		if(Q_Forge->Forge[SCRAM].NetplayerFLAG == 1 && 0)
																			{
																			Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[AItempcnt].CharDATA.Level);

																			Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																			}
																		else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[AItempcnt].CharDATA.Level);
																		}
																	}
																}

															SCRAM++;
															}

														//####### DEACTIVATE ITEM ATTRIBUTES
														Q.DeactivateItems();

														//### Write out CHARDATA
														Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

														//####### REACTIVATE ITEM ATTRIBUTES
														Q.ActivateItems();
														}

													Q_Forge->Forge[AItempcnt].HB_HReduceON = 1;

													Q_Forge->Forge[AItempcnt].HB_ReduceHInc = 10;
													Q_Forge->Forge[AItempcnt].HB_ReduceHeight = 573;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.red = 255;//100 + ( 155 * ( HitType / 10 ) );
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.green = 0;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.blue = 0;
													Q_Forge->Forge[AItempcnt].HB_ReduceRectColor.alpha = 255;

													if(Q_Forge->Forge[AItempcnt].Shadows[1].Avatar != 0)
														{
														Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AItempcnt].Shadows[1].Xform.Translation);
														Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AItempcnt].Shadows[2].Xform.Translation);
														Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[AItempcnt].Shadows[3].Xform.Translation);
														Qpo->Avatar_ClearPose(Q_Forge->Forge[AItempcnt].Shadows[1].Avatar, &Q_Forge->Forge[AItempcnt].Shadows[1].Xform);
														Qpo->Avatar_ClearPose(Q_Forge->Forge[AItempcnt].Shadows[2].Avatar, &Q_Forge->Forge[AItempcnt].Shadows[2].Xform);
														Qpo->Avatar_ClearPose(Q_Forge->Forge[AItempcnt].Shadows[3].Avatar, &Q_Forge->Forge[AItempcnt].Shadows[3].Xform);
														}

													if(HitType == 0)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 1)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 2;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.05 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}
														
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 2;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}


													if(HitType == 2)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.05 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}
														
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 4;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 3)	//Standard Hit Up into Air Slightly
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}
														
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
														Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 8.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));	//6 V-Good

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 13)	//Standard Hit Up into Air Slightly
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
														Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 4)	//Spin Kick Full Rotation
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0;

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 5)	//Combo 1 Heavy KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}
														
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														if(Q_Forge->Forge[AItempcnt].MoveReactVec.y > 0.1) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0.1;
														if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 6)	//Combo 1 Heavy KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 7)	//Hit Up into Air Dramatically
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 90;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 90)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 90;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.003 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 10;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 110;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 6.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));	//6 V-Good

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 7;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 8)	//Combo 2 Steady Kicks
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 3;
															
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Qpo->Vec3d_New(&Q_Forge->Forge[AItempcnt].MoveReactVec);
														
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0;

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 9)	//Heavy KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 6;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);	//250			//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 255;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 255;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 255;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														if(Q_Forge->Forge[AItempcnt].HitReactScale != 0)
															{
															Q_Forge->Forge[AItempcnt].HitReactScale /= 1.7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
															}
														else Q_Forge->Forge[AItempcnt].HitReactScale = 0.025 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 9;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));	//4.5

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 10)
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 5;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 11)	//Combo extern No KnockBack
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 5;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.01 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
														
														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 0;

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 12)	//JSRush Combo
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 5;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = ((100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+40) * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 80;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+55;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														//###Hit Reactions
														if(detcnt == 0 || detcnt == 7 || detcnt == 8 || detcnt == 11 || detcnt == 16 || detcnt == 19 || detcnt == 20)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 28)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 28;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 26)	//Standard Hit Reactions
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 26;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.16;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}

																//'Hit Sound'
															if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
																{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 1; }
															}

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.01 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 4;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
															}

														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 1;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													if(HitType == 20)	//Ultra Blow
														{
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 15;
														
														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 300 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 155;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 155;

														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

														Q_Forge->Forge[AItempcnt].HitReactScale = 0.001 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;

														if(detcnt == 0)		//Head Hit
															{
															Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 20;
															Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 140;
															}

														Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
														
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 10 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH * (0.3+(0.8*(1-(Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Weight/100))));

														Q_Forge->Forge[AIflag].HB_Energy += 15 * 2;
														if(Q_Forge->Forge[AIflag].HB_Energy > Q_Forge->Forge[AIflag].HB_MaxEnergy) Q_Forge->Forge[AIflag].HB_Energy = Q_Forge->Forge[AIflag].HB_MaxEnergy;
														}

													// Assign Heavy Hits
													if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;

													//## Reset Hit Wall
													Q_Forge->Forge[AItempcnt].HitWall = 0;

													//#####- Hit Reaction Motions -#####
													if(Q_Forge->Forge[AItempcnt].HB_DmgSTORE >= 135)
														{
														if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 30)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 30;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{
																if(Q_Forge->Forge[AItempcnt].attposecnt >= 2) Q_Forge->Forge[AItempcnt].attposecnt = 2;
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 2; }

														Q_Forge->Forge[AItempcnt].HB_RecoverMode = 1;
														Q_Forge->Forge[AItempcnt].HB_DmgSTORE = 0;		//### Reset Damage Storage
														}

													if(HitType == 10 || HitType == 20)
														{
														if(Q_Forge->Forge[AIflag].JinkSpecialON >= 0.5)
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 91)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 91;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{	//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.47;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}
														else
															{
															if(Q_Forge->Forge[AItempcnt].Aposestate != 51)
																{
																Q_Forge->Forge[AItempcnt].Aposestate = 51;
																Q_Forge->Forge[AItempcnt].attackon = 1;
																Q_Forge->Forge[AItempcnt].attposecnt = 0;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															else
																{	//Reset DownSpeed
																Q_Forge->Forge[AItempcnt].DownSpeed = 2;
																Q_Forge->Forge[AItempcnt].CrunchTimer = 0;
																Q_Forge->Forge[AItempcnt].attposecnt = 0.47;
																Q_Forge->Forge[AItempcnt].astackcnt = 0;
																Q_Forge->Forge[AItempcnt].astackrun = 0;
																}
															}

															//'Hit Sound'
														if(Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT != 10)
															{ Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 3; }
														}

													//Increment number of MeleeHits
													_->NomMelHit += 1;

													detcnt = 22;

													if((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK <= 0) && ((Q_Forge->Forge[AItempcnt].Block == 1 && (Q_Forge->Forge[AItempcnt].BlockHeight == BlowHeight)) || (Q_Forge->Forge[AItempcnt].Block == 1 && Q_Forge->Forge[AItempcnt].BlockHeight == 3 && BlowHeight == 2)))
														{
														/*Q_Forge->Forge[AItempcnt].Blocking = 1;
														Q_Forge->Forge[AItempcnt].BlockHit = 1;
														Q_Forge->Forge[AItempcnt].BlockHitFLAG = 1;
														Q_Forge->Forge[AItempcnt].attposecnt = 0;
														Q_Forge->Forge[AItempcnt].BlockHitID = _->NomMelHit;*/

														//### Block Hit Flash

														Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
														Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
														Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
														Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																							//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
														Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
														Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
														Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
														Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
														Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

														//Expandro3D Struct
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 0;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 160;
														Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 0;

															// Vector to move by (world-space)
														Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
														lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
														Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
														
														Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
														Q_Forge->Forge[AItempcnt].MoveReactSpeed = 5;	//5.4;

															//Increment number of MeleeHits
														_->NomMelHit += 1;

														detcnt = 22;

														//##### RESET POWERBANK
														//Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK = ((Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2);
														}

													}//END-Else/Deflect	 (true HIT)

												}//END-Else/Block
											else
												{					//>--  BLOCK  --<<
													// Vector to move by (world-space)
												Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIflag].AttPos.Translation, &Q_Forge->Forge[AIflag].OAttPos.Translation, &Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
												lengthvec = Qpo->Vec3d_Length(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);
												Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction);

												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 0;

												if(HitType == 0)
													{
													//Q_Forge->Forge[AItempcnt].HitReactScale = 0.09 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP;
													Q_Forge->Forge[AItempcnt].HitReactScale = 0.09 * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0.1 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}

												if(HitType == 1)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.032 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}

												if(HitType == 2)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}

												if(HitType == 3)	//Standard Hit Up into Air Slightly
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
													Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (5.2 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 13)	//Standard Hit Up into Air Slightly
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;
													Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 3;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (8 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 4)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
													}

												if(HitType == 5)	//Combo 1 Heavy KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													if(Q_Forge->Forge[AItempcnt].MoveReactVec.y > 0.1) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0.1;
													if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (11 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 6)	//Combo 1 Heavy KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.009 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (4.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 7)	//Hit Up into Air Dramatically
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.x /= 1.85;
													Q_Forge->Forge[AItempcnt].MoveReactVec.z /= 1.85;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 1;

													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (14 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 8)	//Combo 2 Steady Kicks
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Qpo->Vec3d_New(&Q_Forge->Forge[AItempcnt].MoveReactVec);
													
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 9)	//Heavy KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.075 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (6.5 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 10)
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (13 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 11)	//Combo extern No KnockBack
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (0 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 12)	//JSRush Combo
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.005 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													if(Q_Forge->Forge[AItempcnt].MoveReactVec.y < 0) Q_Forge->Forge[AItempcnt].MoveReactVec.y = 0;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (7 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												if(HitType == 20)	//Ultra Blow
													{
													Q_Forge->Forge[AItempcnt].HitReactScale = (0.0035 / Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP) * ((1 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y += 0.05;
													Q_Forge->Forge[AItempcnt].MoveReactSpeed = (25 * Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) / ((2 * (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower / 100)) + 2.5);

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
													}

												//Assign Shock Block Flash
												if(Q_Forge->Forge[AIflag].JinkSpecialON >= 1) Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;

												Q_Forge->Forge[AItempcnt].Blocking = 1;
												Q_Forge->Forge[AItempcnt].BlockHit = 1;
												Q_Forge->Forge[AItempcnt].BlockHitFLAG = 1;
												Q_Forge->Forge[AItempcnt].attposecnt = 0;
												Q_Forge->Forge[AItempcnt].BlockHitID = _->NomMelHit;

												//### Block Hit Flash

												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
												Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
												Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = ((Q_Forge->Forge[AIflag].attposecnt - attstt) / ( cutoff - attstt ));
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH) * 0;

												//Expandro3D Struct
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[AItempcnt].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
												
												/*Q_Forge->Forge[AItempcnt].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].Reaction;
												Q_Forge->Forge[AItempcnt].MoveReactSpeed = 5;	//5.4;*/

													//Increment number of MeleeHits
												_->NomMelHit += 1;

												detcnt = 22;
												}//END-Else/Block
											}//END Dodge
										}//END OBB
									}//END BoneFilter
								}//END AntiMultHits
							detcnt += 1;
							}
						}
					}
				}
			}
		AItempcnt++;
		}
	}//END IF NOT Q_Netplayer->Netplayer

};