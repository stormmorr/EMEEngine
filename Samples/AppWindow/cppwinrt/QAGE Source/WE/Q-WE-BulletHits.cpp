/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Bullet Hits System-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "math.h"
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

#define BHIT_SCALE_IMP 1.25

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::BulletHit_ControlServer(int Count)
	{
	if(Q_BulletHit->BulletHit[Count].Init == 0)
		{
		Q_BulletHit->BulletHit[Count].Init = 1;

		//###### Bullet effects
#if 0
		printf("BulletPWR %f BulletDMG %f JDamageLVL %i\n", Q_BulletHit->BulletHit[Count].BulletPWR, Q_BulletHit->BulletHit[Count].BulletDMG, Q_BulletHit->BulletHit[Count].JDamageLVL);
#endif

		if(Q_BulletHit->BulletHit[Count].BulletPWR > 10.5 || Q_BulletHit->BulletHit[Count].JDamageLVL != 0)
			{
			jet = 0;
			while(jet < sqrt(Q_BulletHit->BulletHit[Count].BulletPWR / 85))
				{
				Q_BSparks->BSparks[_->NomSparks].Pos = Q_BulletHit->BulletHit[Count].Pos;

				Q_BSparks->BSparks[_->NomSparks].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

				Q_BSparks->BSparks[_->NomSparks].TraVec.x += ((((float)rand() / 32767)-0.5))*0.3;
				Q_BSparks->BSparks[_->NomSparks].TraVec.y += ((((float)rand() / 32767)-0.5))*0.3;
				Q_BSparks->BSparks[_->NomSparks].TraVec.z += ((((float)rand() / 32767)-0.5))*0.3;

				Q_BSparks->BSparks[_->NomSparks].AlpFade = 255;
				Q_BSparks->BSparks[_->NomSparks].Timer = 0;
				Q_BSparks->BSparks[_->NomSparks].TimerGoal = ((((float)rand() / 32767)*2000)+500);

				Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[_->NomSparks].Pos, 1, &Q_BSparks->BSparks[_->NomSparks].TraVec, &Q_BSparks->BSparks[_->NomSparks].Pos);

				Q_BSparks->BSparks[_->NomSparks].Speed = 100;
				Q_BSparks->BSparks[_->NomSparks].Gravity = 0.1;

				Q_BSparks->BSparks[_->NomSparks].Bounce = 1;

				Q_BSparks->BSparks[_->NomSparks].SmokeTrail = 1;
				Q_BSparks->BSparks[_->NomSparks].Live = 1;

				_->NomSparks++;
				if(_->NomSparks > 499) _->NomSparks = 0;
				jet++;
				}


			jet=0;
			while(jet < sqrt(Q_BulletHit->BulletHit[Count].BulletPWR*5))
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 0;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_BulletHit->BulletHit[Count].Pos;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*200)+55;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*(Q_BulletHit->BulletHit[Count].BulletPWR/100);

				Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*(10*Q_BulletHit->BulletHit[Count].BulletPWR/10);
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*(10*Q_BulletHit->BulletHit[Count].BulletPWR/10)) + 2;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*(10*Q_BulletHit->BulletHit[Count].BulletPWR/10);

#if 0
				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*6;
#else
				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*3;
#endif

				Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}

			if(Q_BulletHit->BulletHit[Count].AvID == -1)
				{ Q.RadialDamage(player[g_Player]->Team, Q_BulletHit->BulletHit[Count].AvID, Q_BulletHit->BulletHit[Count].BulletPWR/145, Q_BulletHit->BulletHit[Count].BulletDMG/25, Q_BulletHit->BulletHit[Count].Pos, 0, TempVec1); }
			else { Q.RadialDamage(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].Team, Q_BulletHit->BulletHit[Count].AvID, Q_BulletHit->BulletHit[Count].BulletPWR/145, Q_BulletHit->BulletHit[Count].BulletDMG/25, Q_BulletHit->BulletHit[Count].Pos, 0, TempVec1); }

			Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, 15, &Q_BulletHit->BulletHit[Count].CollNormal, &TempVec1);

			Qpo->Sound_Play(Medias->S_Explosion3000, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			}

		Q_BulletHit->BulletHit[Count].ScaleDir = 0;
		Q_BulletHit->BulletHit[Count].AlpFade = 255;

		if(Q_BulletHit->BulletHit[Count].EffectType == 0 || (Q_BulletHit->BulletHit[Count].AvID == -1 && Q_BulletHit->BulletHit[Count].AvatarHITID == 250))
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 18 * BHIT_SCALE_IMP;
			Q_BulletHit->BulletHit[Count].BloodAmt = 0;
			Q_BulletHit->BulletHit[Count].EffectType = 0;

			int a=0;
			while( a <= 2 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}

				//SPARKS
			helly = 0;
			while(helly < 3 && (_->NomSparks < 498))
				{
				Q_BSparks->BSparks[_->NomSparks].Pos = Q_BulletHit->BulletHit[Count].Pos;

				Q_BSparks->BSparks[_->NomSparks].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

				Q_BSparks->BSparks[_->NomSparks].TraVec.x += ((((float)rand() / 32767)-0.5));
				Q_BSparks->BSparks[_->NomSparks].TraVec.y += ((((float)rand() / 32767)-0.5))+0.1;
				Q_BSparks->BSparks[_->NomSparks].TraVec.z += ((((float)rand() / 32767)-0.5));

				Q_BSparks->BSparks[_->NomSparks].AlpFade = 255;
				Q_BSparks->BSparks[_->NomSparks].Timer = 0;
				Q_BSparks->BSparks[_->NomSparks].TimerGoal = ((((float)rand() / 32767)*30)+10);

				Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[_->NomSparks].Pos, 1, &Q_BSparks->BSparks[_->NomSparks].TraVec, &Q_BSparks->BSparks[_->NomSparks].Pos);
				
				Q_BSparks->BSparks[_->NomSparks].Speed = 8;

				Q_BSparks->BSparks[_->NomSparks].Gravity = 0.12;

				Q_BSparks->BSparks[_->NomSparks].Bounce = 0;

				Q_BSparks->BSparks[_->NomSparks].SmokeTrail = 0;
				Q_BSparks->BSparks[_->NomSparks].Live = 1;

				_->NomSparks++;
				helly++;
				}

			TempVec1 = Q_BulletHit->BulletHit[Count].Pos;

			//Move Sound away from the wall
			Qpo->Vec3d_AddScaled(&TempVec1, 7, &Q_BulletHit->BulletHit[Count].CollNormal, &TempVec1);

				//'Bullet Hit Sound'
			_->SoundFinger = ((float)rand() / 32767)*4;
			if(_->SoundFinger <= 1) Qpo->Sound_Play(Medias->S_Hitwall1, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 1 && _->SoundFinger <= 2) Qpo->Sound_Play(Medias->S_Hitwall2, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 2 && _->SoundFinger <= 3) Qpo->Sound_Play(Medias->S_Hitwall3, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 3 && _->SoundFinger <= 4) Qpo->Sound_Play(Medias->S_Hitwall4, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);

#if 0		//#### Add a world decal
			if(Q_BulletHit->BulletHit[Count].BulletPWR < 15) _->GD = Q.AddDecal(Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].CollNormal, 8, 0);
			if(Q_BulletHit->BulletHit[Count].BulletPWR > 15 && Q_BulletHit->BulletHit[Count].BulletPWR < 5) _->GD = Q.AddDecal(Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].CollNormal, 8, 3);
			if(Q_BulletHit->BulletHit[Count].BulletPWR > 45.5 && Q_BulletHit->BulletHit[Count].BulletPWR < 7) _->GD = Q.AddDecal(Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].CollNormal, 8, 2);
			if(Q_BulletHit->BulletHit[Count].BulletPWR > 57) _->GD = Q.AddDecal(Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].CollNormal, 8, 1);
#endif
			}


		if(Q_BulletHit->BulletHit[Count].EffectType == 100)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 13 * BHIT_SCALE_IMP;
			Q_BulletHit->BulletHit[Count].BloodAmt = 0;
			Q_BulletHit->BulletHit[Count].EffectType = 100;

			int a=0;
			while( a <= 2 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}

				//SPARKS
			jet=0;
			while((jet < 8) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_BulletHit->BulletHit[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_BulletHit->BulletHit[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			TempVec1 = Q_BulletHit->BulletHit[Count].Pos;

			//Move Sound away from the wall
			Qpo->Vec3d_AddScaled(&TempVec1, 7, &Q_BulletHit->BulletHit[Count].CollNormal, &TempVec1);

				//'Bullet Hit Sound'
			_->SoundFinger = ((float)rand() / 32767)*4;
			if(_->SoundFinger <= 1) Qpo->Sound_Play(Medias->S_Hitwall1, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 1 && _->SoundFinger <= 2) Qpo->Sound_Play(Medias->S_Hitwall2, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 2 && _->SoundFinger <= 3) Qpo->Sound_Play(Medias->S_Hitwall3, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 3 && _->SoundFinger <= 4) Qpo->Sound_Play(Medias->S_Hitwall4, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			}


		if(Q_BulletHit->BulletHit[Count].EffectType == 1 || Q_BulletHit->BulletHit[Count].EffectType == 4 || Q_BulletHit->BulletHit[Count].EffectType == 7)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 18 * BHIT_SCALE_IMP;

			if(Q_BulletHit->BulletHit[Count].AvatarHITID == 250)
				{
				int f_ArmourFactor = 1000;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR < 150)
					{
					f_ArmourFactor = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR;
					}

				if(((player[g_Player]->HB_Armour - (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					player[g_Player]->BulletHitCnt += 4;
					Q_BulletHit->BulletHit[Count].EffectType = 4;
					}

				player[g_Player]->BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 3 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				player[g_Player]->HB_Armour -= (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((player[g_Player]->HB_Armour > 0) && (player[g_Player]->HB_Armour + (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 7)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 7;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = 250;

				/*if(player[g_Player]->BulletHitCnt >= 35 || (player[g_Player]->HB_Health <= 0))
					{
					player[g_Player]->MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(player[g_Player]->HB_Armour <= 0 || (player[g_Player]->HB_Health <= 0))
						{
						player[g_Player]->BulletHitCnt = 0;
						player[g_Player]->Aposestate = 30;
						}
					}
				else player[g_Player]->MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				player[g_Player]->MoveReactVec = TempVec1;
				if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) player[g_Player]->HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
						//## Hit Reaction Motions
						if(player[g_Player]->Aposestate != 30)
							{
							if(player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28)		//Standard Hit Upper Reactions
								{
								player[g_Player]->Aposestate = 26;
								player[g_Player]->attackon = 1;
								player[g_Player]->attposecnt = 0;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							else
								{
								player[g_Player]->attposecnt = 0.16;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							player[g_Player]->Aposestate = 30;
							player[g_Player]->attackon = 1;
							player[g_Player]->attposecnt = 0;
							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							}*/

						//## Reduce Health
						player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;
						player[g_Player]->HB_Health += player[g_Player]->HB_Armour;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] -= player[g_Player]->HB_Armour;

						player[g_Player]->HB_ReduceRectColor.red = 255;
						player[g_Player]->HB_ReduceRectColor.green = 0;
						player[g_Player]->HB_ReduceRectColor.blue = 0;
						player[g_Player]->HB_ReduceRectColor.alpha = 255;

						player[g_Player]->HB_ReduceHInc = 10;
						player[g_Player]->HB_ReduceHeight = 573;

						player[g_Player]->HB_HReduceON = 1;

						if(player[g_Player]->HB_Health <= 0)
							{
							player[g_Player]->HB_Health = 0;

							/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
										&player[g_Player]->ViewXForm.Translation,
										600.0f,
										2.0f,
										&Volume,
										&Pan,
										&Frequency);*/

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

							player[g_Player]->HB_Dead = 1;

							//### Add Experience to attacking AVATAR
							if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0 && (_->NomBlood < 498))
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt)
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(player[g_Player]->HB_Armour < 0) player[g_Player]->HB_Armour = 0;
				}
			else
				{
				int f_ArmourFactor = 1000;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrLOWERARMOUR >= 0 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrLOWERARMOUR < 150)
					{
					f_ArmourFactor = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrLOWERARMOUR;
					}

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour - (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt += 4;
					Q_BulletHit->BulletHit[Count].EffectType = 4;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 3 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour -= (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour + (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 7)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 7;
					}

				if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt >= 35 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
						{
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
						}
					}
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec = TempVec1;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y = 0;
				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
								//## Hit Reaction Motions
						if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 30)
							{
							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 26 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 28)	//Standard Hit Reactions
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 26;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							else
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0.16;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
							}*/


						//## Reduce Health
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceOld = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;
						else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.red = 255;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.alpha = 255;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHInc = 10;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHeight = 574;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_HReduceON = 1;

						if(Q_BulletHit->BulletHit[Count].AvID == -1)
							{
							player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;
								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						else
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_BulletHit->BulletHit[Count].AvID, Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))	//1		//8		//25
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour = 0;
				}
			}

		if(Q_BulletHit->BulletHit[Count].EffectType == 2 || Q_BulletHit->BulletHit[Count].EffectType == 5 || Q_BulletHit->BulletHit[Count].EffectType == 8)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 22 * BHIT_SCALE_IMP;

			if(Q_BulletHit->BulletHit[Count].AvatarHITID == 250)
				{
				int f_ArmourFactor = 1000;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR < 150)
					{
					f_ArmourFactor = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR;
					}

				if(((player[g_Player]->HB_Armour - (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					player[g_Player]->BulletHitCnt += 6;
					Q_BulletHit->BulletHit[Count].EffectType = 5;
					}

				player[g_Player]->BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 6 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				player[g_Player]->HB_Armour -= (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((player[g_Player]->HB_Armour <= 0) && (player[g_Player]->HB_Armour + (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 8;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = 250;

				/*if(player[g_Player]->BulletHitCnt >= 35 || (player[g_Player]->HB_Health <= 0))
					{
					player[g_Player]->MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(player[g_Player]->HB_Armour <= 0 || (player[g_Player]->HB_Health <= 0))
						{
						player[g_Player]->BulletHitCnt = 0;
						player[g_Player]->Aposestate = 30;
						}
					}
				else player[g_Player]->MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				player[g_Player]->MoveReactVec = TempVec1;
				if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) player[g_Player]->HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
									//## Hit Reaction Motions
						if(player[g_Player]->Aposestate != 30)
							{
							if(player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
								{
								player[g_Player]->Aposestate = 28;
								player[g_Player]->attackon = 1;
								player[g_Player]->attposecnt = 0;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							else
								{
								player[g_Player]->attposecnt = 0.16;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							player[g_Player]->Aposestate = 30;
							player[g_Player]->attackon = 1;
							player[g_Player]->attposecnt = 0;
							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							}*/


						//## Reduce Health
						player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;
						player[g_Player]->HB_Health += player[g_Player]->HB_Armour;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] -= player[g_Player]->HB_Armour;

						player[g_Player]->HB_ReduceRectColor.red = 255;
						player[g_Player]->HB_ReduceRectColor.green = 0;
						player[g_Player]->HB_ReduceRectColor.blue = 0;
						player[g_Player]->HB_ReduceRectColor.alpha = 255;

						player[g_Player]->HB_ReduceHInc = 10;
						player[g_Player]->HB_ReduceHeight = 573;

						player[g_Player]->HB_HReduceON = 1;

						if(player[g_Player]->HB_Health <= 0)
							{
							player[g_Player]->HB_Health = 0;

							/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
										&player[g_Player]->ViewXForm.Translation,
										600.0f,
										2.0f,
										&Volume,
										&Pan,
										&Frequency);*/

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

							player[g_Player]->HB_Dead = 1;

							//### Add Experience to attacking AVATAR
							if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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
								if(Q_Forge->Forge[jet].LIVE == 1)
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
						}


					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(player[g_Player]->HB_Armour < 0) player[g_Player]->HB_Armour = 0;
				}
			else
				{
				int f_ArmourFactor = 1000;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrUPPERARMOUR >= 0 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrUPPERARMOUR < 150)
					{
					f_ArmourFactor = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrUPPERARMOUR;
					}

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour - (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt += 4;
					Q_BulletHit->BulletHit[Count].EffectType = 5;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 6 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour -= (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour + (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 8;
					}

				if(Q_BulletHit->BulletHit[Count].AvID == 250) player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;
					else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt >= 35 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
						{
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
						}
					}
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec = TempVec1;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y = 0;
				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
							//## Hit Reaction Motions
						if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 30)
							{
							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 26 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 28)	//Standard Hit Reactions
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 28;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							else
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0.16;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
							}*/


						//## Reduce Health
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceOld = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;
						else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.red = 255;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.alpha = 255;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHInc = 10;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHeight = 574;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_HReduceON = 1;

						if(Q_BulletHit->BulletHit[Count].AvID == -1)
							{
							player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;
								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						else
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_BulletHit->BulletHit[Count].AvID, Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))	//1		//8		//25
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour = 0;
				}
			}

		if(Q_BulletHit->BulletHit[Count].EffectType == 3 || Q_BulletHit->BulletHit[Count].EffectType == 6 || Q_BulletHit->BulletHit[Count].EffectType == 9)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 27 * BHIT_SCALE_IMP;

			if(Q_BulletHit->BulletHit[Count].AvatarHITID == 250)
				{
				int f_ArmourFactor = 1000;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR < 150)
					{
					f_ArmourFactor = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR;
					}

				if(((player[g_Player]->HB_Armour - (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					player[g_Player]->BulletHitCnt += 8;
					Q_BulletHit->BulletHit[Count].EffectType = 6;
					}

				player[g_Player]->BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 12 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				player[g_Player]->HB_Armour -= (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((player[g_Player]->HB_Armour <= 0) && (player[g_Player]->HB_Armour + (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 9;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(player[g_Player]->BulletHitCnt >= 35 || (player[g_Player]->HB_Health <= 0))
					{
					player[g_Player]->MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(player[g_Player]->HB_Armour <= 0 || (player[g_Player]->HB_Health <= 0))
						{
						player[g_Player]->BulletHitCnt = 0;
						player[g_Player]->Aposestate = 30;
						}
					}
				else player[g_Player]->MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				player[g_Player]->MoveReactVec = TempVec1;
				if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) player[g_Player]->HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
							//## Hit Reaction Motions
						if(player[g_Player]->Aposestate != 30)
							{
							if(player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
								{
								player[g_Player]->Aposestate = 28;
								player[g_Player]->attackon = 1;
								player[g_Player]->attposecnt = 0;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							else
								{
								player[g_Player]->attposecnt = 0.16;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							player[g_Player]->Aposestate = 30;
							player[g_Player]->attackon = 1;
							player[g_Player]->attposecnt = 0;
							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							}*/


						//## Reduce Health
						player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;
						player[g_Player]->HB_Health += player[g_Player]->HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] -= player[g_Player]->HB_Armour;

						player[g_Player]->HB_ReduceRectColor.red = 255;
						player[g_Player]->HB_ReduceRectColor.green = 0;
						player[g_Player]->HB_ReduceRectColor.blue = 0;
						player[g_Player]->HB_ReduceRectColor.alpha = 255;

						player[g_Player]->HB_ReduceHInc = 10;
						player[g_Player]->HB_ReduceHeight = 573;

						player[g_Player]->HB_HReduceON = 1;

						if(player[g_Player]->HB_Health <= 0)
							{
							player[g_Player]->HB_Health = 0;

							/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
										&player[g_Player]->ViewXForm.Translation,
										600.0f,
										2.0f,
										&Volume,
										&Pan,
										&Frequency);*/

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

							player[g_Player]->HB_Dead = 1;

							//### Add Experience to attacking AVATAR
							if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(player[g_Player]->HB_Armour < 0) player[g_Player]->HB_Armour = 0;
				}
			else
				{
				int f_ArmourFactor = 1000;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrHEADARMOUR >= 0 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrHEADARMOUR < 150)
					{
					f_ArmourFactor = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrHEADARMOUR;
					}

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour - (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt += 8;
					Q_BulletHit->BulletHit[Count].EffectType = 6;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 12 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour -= (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour + (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 9;
					}

				if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt >= 35 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
						{
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
						}
					}
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec = TempVec1;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y = 0;
				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 5) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 5) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
							//## Hit Reaction Motions
						if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 30)
							{
							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 26 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 28)	//Standard Hit Reactions
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 28;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							else
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0.16;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
							}*/


						//## Reduce Health
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceOld = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;
						else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.red = 255;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.alpha = 255;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHInc = 10;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHeight = 574;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_HReduceON = 1;

						if(Q_BulletHit->BulletHit[Count].AvID == -1)
							{
							player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;
								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						else
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_BulletHit->BulletHit[Count].AvID, Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))	//1		//8		//25
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Gray Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour = 0;
				}

			}

		}//END INIT


	Qpo->Transform_New(&Q_BulletHit->BulletHit[Count].AlignMatrix);
	Qpo->Transform_GetIn(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].AligIn);
	
	Q_BulletHit->BulletHit[Count].VecIn = Q_BulletHit->BulletHit[Count].CollNormal;

	if(Q_BulletHit->BulletHit[Count].VecIn.x == 0 && Q_BulletHit->BulletHit[Count].VecIn.z == 0)
		{
		Q_BulletHit->BulletHit[Count].VecLeft.x = -1;
		Q_BulletHit->BulletHit[Count].VecLeft.y = 0;
		Q_BulletHit->BulletHit[Count].VecLeft.z = 0;
		}
	else
		{				// Y
		Qpo->Transform_New_ZRotation(&rotmat, PI/2);
		Qpo->Transform_RotateVector(&rotmat, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VecLeft);
		//Q_BulletHit->BulletHit[Count].VecLeft.y = 0;
		}

	Qpo->Vec3d_CrossProduct(&Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VecUp);


	Qpo->Transform_New_LeftUpIn(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VecUp);
	Q_BulletHit->BulletHit[Count].AlignMatrix.Translation = Q_BulletHit->BulletHit[Count].Pos;
					// Z
	Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)*6);
	Qpo->Transform_Multiply(&Q_BulletHit->BulletHit[Count].AlignMatrix, &rotmat, &Q_BulletHit->BulletHit[Count].AlignMatrix);

	Qpo->Transform_GetUp(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecUp);
	Qpo->Transform_GetLeft(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecLeft);
	Qpo->Transform_GetIn(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecIn);

	Q_BulletHit->BulletHit[Count].Type = QPOLY_TYPE_TRI;
	Q_BulletHit->BulletHit[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
	Q_BulletHit->BulletHit[Count].ScaleBIT = 1.0f;
	//END INIT

	if(Q_BulletHit->BulletHit[Count].Scale - 2 > 2) Q_BulletHit->BulletHit[Count].Scale -= 2;
	else
		{
		Q_BulletHit->BulletHit[Count].Scale = 1;
		Q_BulletHit->BulletHit[Count].Live = 0;
		Q_BulletHit->BulletHit[Count].Init = 0;

		//### Array Reorder
		if(g_optionsresult == 2 || g_optionsresult == 3)
			{						//### Array Reorder
			int K = Count;
			while(K < 499 && K < _->NomBulHit - 1)
				{
				Q_BulletHit->BulletHit[K] = Q_BulletHit->BulletHit[K+1];
				K++;
				}

			_->NomBulHit--;
			}
		else
			{
			int K = Count;
			while(K < _->NomBulHit - 1)
				{
				Q_BulletHit->BulletHit[K] = Q_BulletHit->BulletHit[K+1];
				K++;
				}

			_->NomBulHit--;
			}
		}

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, 0.3, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].Pos);//3


		//##Flash Vertical##
			//TOP VERT1
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertFU1);

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU1, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFU1);

			//TOP VERT2
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU1, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFU2);


			//BOTTOM VERT3
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU2, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertFU3);

			//BOTTOM VERT4
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU3, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFU4);


		//##Flash Horizontal##
			//LEFT VERT1
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, -Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertFD1);

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD1, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFD1);


			//LEFT VERT2
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD1, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFD2);


			//RIGHT VERT3
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD2, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertFD3);

			//RIGHT VERT4
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD3, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFD4);


		//##Flash Spinner##
			//TOP VERT1
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertS1);

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS1, Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertS1);

			//TOP VERT2
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS1, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertS2);


			//BOTTOM VERT3
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS2, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertS3);

			//BOTTOM VERT4
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS3, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertS4);


	//##Flash Vertical##

	Q_BulletHit->BulletHit[Count].Lvert[0][0].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].x = Q_BulletHit->BulletHit[Count].VertFU1.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].y = Q_BulletHit->BulletHit[Count].VertFU1.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].z = Q_BulletHit->BulletHit[Count].VertFU1.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[0][1].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].x = Q_BulletHit->BulletHit[Count].VertFU2.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].y = Q_BulletHit->BulletHit[Count].VertFU2.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].z = Q_BulletHit->BulletHit[Count].VertFU2.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[0][2].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].x = Q_BulletHit->BulletHit[Count].VertFU3.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].y = Q_BulletHit->BulletHit[Count].VertFU3.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].z = Q_BulletHit->BulletHit[Count].VertFU3.z;


	Q_BulletHit->BulletHit[Count].Lvert[0][3].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].x = Q_BulletHit->BulletHit[Count].VertFU4.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].y = Q_BulletHit->BulletHit[Count].VertFU4.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].z = Q_BulletHit->BulletHit[Count].VertFU4.z;



	//##Flash Horizontal##

	Q_BulletHit->BulletHit[Count].Lvert[1][0].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].x = Q_BulletHit->BulletHit[Count].VertFD1.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].y = Q_BulletHit->BulletHit[Count].VertFD1.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].z = Q_BulletHit->BulletHit[Count].VertFD1.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[1][1].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].x = Q_BulletHit->BulletHit[Count].VertFD2.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].y = Q_BulletHit->BulletHit[Count].VertFD2.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].z = Q_BulletHit->BulletHit[Count].VertFD2.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[1][2].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].x = Q_BulletHit->BulletHit[Count].VertFD3.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].y = Q_BulletHit->BulletHit[Count].VertFD3.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].z = Q_BulletHit->BulletHit[Count].VertFD3.z;


	Q_BulletHit->BulletHit[Count].Lvert[1][3].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].x = Q_BulletHit->BulletHit[Count].VertFD4.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].y = Q_BulletHit->BulletHit[Count].VertFD4.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].z = Q_BulletHit->BulletHit[Count].VertFD4.z;


	//##Flash Spinner##

	Q_BulletHit->BulletHit[Count].Lvert[2][0].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].x = Q_BulletHit->BulletHit[Count].VertS1.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].y = Q_BulletHit->BulletHit[Count].VertS1.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].z = Q_BulletHit->BulletHit[Count].VertS1.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[2][1].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].x = Q_BulletHit->BulletHit[Count].VertS2.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].y = Q_BulletHit->BulletHit[Count].VertS2.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].z = Q_BulletHit->BulletHit[Count].VertS2.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[2][2].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].x = Q_BulletHit->BulletHit[Count].VertS3.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].y = Q_BulletHit->BulletHit[Count].VertS3.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].z = Q_BulletHit->BulletHit[Count].VertS3.z;


	Q_BulletHit->BulletHit[Count].Lvert[2][3].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].x = Q_BulletHit->BulletHit[Count].VertS4.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].y = Q_BulletHit->BulletHit[Count].VertS4.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].z = Q_BulletHit->BulletHit[Count].VertS4.z;


	Qpo->Poly_AddOnce(&Q_BulletHit->BulletHit[Count].Lvert[0][0], 4, Medias->BulHitFlash, Q_BulletHit->BulletHit[Count].Type, Q_BulletHit->BulletHit[Count].RenderFlags, Q_BulletHit->BulletHit[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_BulletHit->BulletHit[Count].Lvert[1][0], 4, Medias->BulHitFlash, Q_BulletHit->BulletHit[Count].Type, Q_BulletHit->BulletHit[Count].RenderFlags, Q_BulletHit->BulletHit[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_BulletHit->BulletHit[Count].Lvert[2][0], 4, Medias->BulHitFlashSpin, Q_BulletHit->BulletHit[Count].Type, Q_BulletHit->BulletHit[Count].RenderFlags, Q_BulletHit->BulletHit[Count].ScaleBIT);
	};


void Q_EFFCon::BulletHit_ControlClient(int Count)
	{
	if(Q_BulletHit->BulletHit[Count].Init == 0)
		{
		Q_BulletHit->BulletHit[Count].Init = 1;

		Q_BulletHit->BulletHit[Count].ScaleDir = 0;
		Q_BulletHit->BulletHit[Count].AlpFade = 255;

		if(Q_BulletHit->BulletHit[Count].EffectType == 0 || (Q_BulletHit->BulletHit[Count].AvID == 250 && Q_BulletHit->BulletHit[Count].AvatarHITID == 250))
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 18;
			Q_BulletHit->BulletHit[Count].BloodAmt = 0;
			Q_BulletHit->BulletHit[Count].EffectType = 0;

			int a=0;
			while( a <= 2 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}

				//SPARKS
			helly = 0;
			while(helly < 3 && (_->NomSparks < 498))
				{
				Q_BSparks->BSparks[_->NomSparks].Pos = Q_BulletHit->BulletHit[Count].Pos;

				Q_BSparks->BSparks[_->NomSparks].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

				Q_BSparks->BSparks[_->NomSparks].TraVec.x += ((((float)rand() / 32767)-0.5));
				Q_BSparks->BSparks[_->NomSparks].TraVec.y += ((((float)rand() / 32767)-0.5))+0.1;
				Q_BSparks->BSparks[_->NomSparks].TraVec.z += ((((float)rand() / 32767)-0.5));

				Q_BSparks->BSparks[_->NomSparks].AlpFade = 255;
				Q_BSparks->BSparks[_->NomSparks].Timer = 0;
				Q_BSparks->BSparks[_->NomSparks].TimerGoal = ((((float)rand() / 32767)*30)+10);

				Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[_->NomSparks].Pos, 1, &Q_BSparks->BSparks[_->NomSparks].TraVec, &Q_BSparks->BSparks[_->NomSparks].Pos);
				
				Q_BSparks->BSparks[_->NomSparks].Speed = 8;

				Q_BSparks->BSparks[_->NomSparks].Gravity = 0.12;

				Q_BSparks->BSparks[_->NomSparks].Bounce = 0;

				Q_BSparks->BSparks[_->NomSparks].SmokeTrail = 0;
				Q_BSparks->BSparks[_->NomSparks].Live = 1;

				_->NomSparks++;
				helly++;
				}

			TempVec1 = Q_BulletHit->BulletHit[Count].Pos;

			//Move Sound away from the wall
			Qpo->Vec3d_AddScaled(&TempVec1, 7, &Q_BulletHit->BulletHit[Count].CollNormal, &TempVec1);

				//'Bullet Hit Sound'
			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);

			_->SoundFinger = ((float)rand() / 32767)*4;
			if(_->SoundFinger <= 1) Qpo->Sound_Play(Medias->S_Hitwall1, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 1 && _->SoundFinger <= 2) Qpo->Sound_Play(Medias->S_Hitwall2, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 2 && _->SoundFinger <= 3) Qpo->Sound_Play(Medias->S_Hitwall3, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 3 && _->SoundFinger <= 4) Qpo->Sound_Play(Medias->S_Hitwall4, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			}


		if(Q_BulletHit->BulletHit[Count].EffectType == 100)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 13;
			Q_BulletHit->BulletHit[Count].BloodAmt = 0;
			Q_BulletHit->BulletHit[Count].EffectType = 100;

			int a=0;
			while( a <= 2 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 255;
					Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}

				//SPARKS
			jet=0;
			while((jet < 8) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_BulletHit->BulletHit[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_BulletHit->BulletHit[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			TempVec1 = Q_BulletHit->BulletHit[Count].Pos;

			//Move Sound away from the wall
			Qpo->Vec3d_AddScaled(&TempVec1, 7, &Q_BulletHit->BulletHit[Count].CollNormal, &TempVec1);

				//'Bullet Hit Sound'
			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &TempVec1, 600.0f, 2.0f, &Volume, &Pan, &Frequency);

			_->SoundFinger = ((float)rand() / 32767)*4;
			if(_->SoundFinger <= 1) Qpo->Sound_Play(Medias->S_Hitwall1, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 1 && _->SoundFinger <= 2) Qpo->Sound_Play(Medias->S_Hitwall2, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 2 && _->SoundFinger <= 3) Qpo->Sound_Play(Medias->S_Hitwall3, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			if(_->SoundFinger > 3 && _->SoundFinger <= 4) Qpo->Sound_Play(Medias->S_Hitwall4, _->Volume, _->Pan, _->S_TimeScale, false, &TempVec1);
			}


		if(Q_BulletHit->BulletHit[Count].EffectType == 1 || Q_BulletHit->BulletHit[Count].EffectType == 4 || Q_BulletHit->BulletHit[Count].EffectType == 7)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 18;

			if(Q_BulletHit->BulletHit[Count].AvatarHITID == 250)
				{
				int f_ArmourFactor = 1000;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR < 150)
					{
					f_ArmourFactor = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR;
					}

				if(((player[g_Player]->HB_Armour - (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					player[g_Player]->BulletHitCnt += 4;
					Q_BulletHit->BulletHit[Count].EffectType = 4;
					}

				player[g_Player]->BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 3 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				player[g_Player]->HB_Armour -= (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((player[g_Player]->HB_Armour <= 0) && (player[g_Player]->HB_Armour + (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 7)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 7;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = 250;

				/*if(player[g_Player]->BulletHitCnt >= 35 || (player[g_Player]->HB_Health <= 0))
					{
					player[g_Player]->MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(player[g_Player]->HB_Armour <= 0 || (player[g_Player]->HB_Health <= 0))
						{
						player[g_Player]->BulletHitCnt = 0;
						player[g_Player]->Aposestate = 30;
						}
					}
				else player[g_Player]->MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				player[g_Player]->MoveReactVec = TempVec1;
				if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) player[g_Player]->HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
						//## Hit Reaction Motions
						if(player[g_Player]->Aposestate != 30)
							{
							if(player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28)		//Standard Hit Upper Reactions
								{
								player[g_Player]->Aposestate = 26;
								player[g_Player]->attackon = 1;
								player[g_Player]->attposecnt = 0;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							else
								{
								player[g_Player]->attposecnt = 0.16;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							player[g_Player]->Aposestate = 30;
							player[g_Player]->attackon = 1;
							player[g_Player]->attposecnt = 0;
							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							}*/

						//## Reduce Health
						player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;
						player[g_Player]->HB_Health += player[g_Player]->HB_Armour;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] -= player[g_Player]->HB_Armour;

						player[g_Player]->HB_ReduceRectColor.red = 255;
						player[g_Player]->HB_ReduceRectColor.green = 0;
						player[g_Player]->HB_ReduceRectColor.blue = 0;
						player[g_Player]->HB_ReduceRectColor.alpha = 255;

						player[g_Player]->HB_ReduceHInc = 10;
						player[g_Player]->HB_ReduceHeight = 573;

						player[g_Player]->HB_HReduceON = 1;

						if(player[g_Player]->HB_Health <= 0)
							{
							player[g_Player]->HB_Health = 0;

							/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
										&player[g_Player]->ViewXForm.Translation,
										600.0f,
										2.0f,
										&Volume,
										&Pan,
										&Frequency);*/

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

							player[g_Player]->HB_Dead = 1;

							//### Add Experience to attacking AVATAR
							if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0 && (_->NomBlood < 498))
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt)
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(player[g_Player]->HB_Armour < 0) player[g_Player]->HB_Armour = 0;
				}
			else
				{
				int f_ArmourFactor = 1000;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrLOWERARMOUR >= 0 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrLOWERARMOUR < 150)
					{
					f_ArmourFactor = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrLOWERARMOUR;
					}

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour - (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt += 4;
					Q_BulletHit->BulletHit[Count].EffectType = 4;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 3 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour -= (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour + (((25 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 7)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 7;
					}

				if(Q_BulletHit->BulletHit[Count].AvID == 250) player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;
					else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt >= 35 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
						{
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
						}
					}
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec = TempVec1;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y = 0;
				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
								//## Hit Reaction Motions
						if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 30)
							{
							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 26 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 28)	//Standard Hit Reactions
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 26;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							else
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0.16;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
							}*/


						//## Reduce Health
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceOld = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;
						else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.red = 255;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.alpha = 255;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHInc = 10;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHeight = 574;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_HReduceON = 1;

						if(Q_BulletHit->BulletHit[Count].AvID == -1)
							{
							player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;
								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						else
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_BulletHit->BulletHit[Count].AvID, Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))	//1		//8		//25
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour = 0;
				}
			}

		if(Q_BulletHit->BulletHit[Count].EffectType == 2 || Q_BulletHit->BulletHit[Count].EffectType == 5 || Q_BulletHit->BulletHit[Count].EffectType == 8)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 22;

			if(Q_BulletHit->BulletHit[Count].AvatarHITID == 250)
				{
				int f_ArmourFactor = 1000;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR < 150)
					{
					f_ArmourFactor = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR;
					}

				if(((player[g_Player]->HB_Armour - (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					player[g_Player]->BulletHitCnt += 6;
					Q_BulletHit->BulletHit[Count].EffectType = 5;
					}

				player[g_Player]->BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 6 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				player[g_Player]->HB_Armour -= (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((player[g_Player]->HB_Armour <= 0) && (player[g_Player]->HB_Armour + (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 8;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = 250;

				/*if(player[g_Player]->BulletHitCnt >= 35 || (player[g_Player]->HB_Health <= 0))
					{
					player[g_Player]->MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(player[g_Player]->HB_Armour <= 0 || (player[g_Player]->HB_Health <= 0))
						{
						player[g_Player]->BulletHitCnt = 0;
						player[g_Player]->Aposestate = 30;
						}
					}
				else player[g_Player]->MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				player[g_Player]->MoveReactVec = TempVec1;
				if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) player[g_Player]->HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
									//## Hit Reaction Motions
						if(player[g_Player]->Aposestate != 30)
							{
							if(player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
								{
								player[g_Player]->Aposestate = 28;
								player[g_Player]->attackon = 1;
								player[g_Player]->attposecnt = 0;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							else
								{
								player[g_Player]->attposecnt = 0.16;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							player[g_Player]->Aposestate = 30;
							player[g_Player]->attackon = 1;
							player[g_Player]->attposecnt = 0;
							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							}*/


						//## Reduce Health
						player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;
						player[g_Player]->HB_Health += player[g_Player]->HB_Armour;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] -= player[g_Player]->HB_Armour;

						player[g_Player]->HB_ReduceRectColor.red = 255;
						player[g_Player]->HB_ReduceRectColor.green = 0;
						player[g_Player]->HB_ReduceRectColor.blue = 0;
						player[g_Player]->HB_ReduceRectColor.alpha = 255;

						player[g_Player]->HB_ReduceHInc = 10;
						player[g_Player]->HB_ReduceHeight = 573;

						player[g_Player]->HB_HReduceON = 1;

						if(player[g_Player]->HB_Health <= 0)
							{
							player[g_Player]->HB_Health = 0;

							/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
										&player[g_Player]->ViewXForm.Translation,
										600.0f,
										2.0f,
										&Volume,
										&Pan,
										&Frequency);*/

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

							player[g_Player]->HB_Dead = 1;

							//### Add Experience to attacking AVATAR
							if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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
								if(Q_Forge->Forge[jet].LIVE == 1)
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
						}


					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(player[g_Player]->HB_Armour < 0) player[g_Player]->HB_Armour = 0;
				}
			else
				{
				int f_ArmourFactor = 1000;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrUPPERARMOUR >= 0 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrUPPERARMOUR < 150)
					{
					f_ArmourFactor = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrUPPERARMOUR;
					}

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour - (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt += 4;
					Q_BulletHit->BulletHit[Count].EffectType = 5;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 6 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour -= (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour + (((37 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 8;
					}

				if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;
					else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt >= 35 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
						{
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
						}
					}
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec = TempVec1;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y = 0;
				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
							//## Hit Reaction Motions
						if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 30)
							{
							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 26 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 28)	//Standard Hit Reactions
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 28;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							else
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0.16;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
							}*/


						//## Reduce Health
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceOld = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;
						else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.red = 255;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.alpha = 255;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHInc = 10;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHeight = 574;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_HReduceON = 1;

						if(Q_BulletHit->BulletHit[Count].AvID == -1)
							{
							player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;
								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						else
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_BulletHit->BulletHit[Count].AvID, Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))	//1		//8		//25
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour = 0;
				}
			}

		if(Q_BulletHit->BulletHit[Count].EffectType == 3 || Q_BulletHit->BulletHit[Count].EffectType == 6 || Q_BulletHit->BulletHit[Count].EffectType == 9)
			{
			Q_BulletHit->BulletHit[Count].Scale = (sqrt(Q_BulletHit->BulletHit[Count].BulletPWR)) * 27;

			if(Q_BulletHit->BulletHit[Count].AvatarHITID == 250)
				{
				int f_ArmourFactor = 1000;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR < 150)
					{
					f_ArmourFactor = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR;
					}

				if(((player[g_Player]->HB_Armour - (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					player[g_Player]->BulletHitCnt += 8;
					Q_BulletHit->BulletHit[Count].EffectType = 6;
					}

				player[g_Player]->BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 12 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				player[g_Player]->HB_Armour -= (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((player[g_Player]->HB_Armour <= 0) && (player[g_Player]->HB_Armour + (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 9;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(player[g_Player]->BulletHitCnt >= 35 || (player[g_Player]->HB_Health <= 0))
					{
					player[g_Player]->MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(player[g_Player]->HB_Armour <= 0 || (player[g_Player]->HB_Health <= 0))
						{
						player[g_Player]->BulletHitCnt = 0;
						player[g_Player]->Aposestate = 30;
						}
					}
				else player[g_Player]->MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				player[g_Player]->MoveReactVec = TempVec1;
				if(player[g_Player]->MoveReactVec.y < 0) player[g_Player]->MoveReactVec.y = 0;
				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) player[g_Player]->HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((player[g_Player]->HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
							//## Hit Reaction Motions
						if(player[g_Player]->Aposestate != 30)
							{
							if(player[g_Player]->Aposestate != 26 && player[g_Player]->Aposestate != 28)	//Standard Hit Reactions
								{
								player[g_Player]->Aposestate = 28;
								player[g_Player]->attackon = 1;
								player[g_Player]->attposecnt = 0;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							else
								{
								player[g_Player]->attposecnt = 0.16;
								player[g_Player]->astackcnt = 0;
								player[g_Player]->astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							player[g_Player]->Aposestate = 30;
							player[g_Player]->attackon = 1;
							player[g_Player]->attposecnt = 0;
							player[g_Player]->astackcnt = 0;
							player[g_Player]->astackrun = 0;
							}*/


						//## Reduce Health
						player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;
						player[g_Player]->HB_Health += player[g_Player]->HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] -= player[g_Player]->HB_Armour;

						player[g_Player]->HB_ReduceRectColor.red = 255;
						player[g_Player]->HB_ReduceRectColor.green = 0;
						player[g_Player]->HB_ReduceRectColor.blue = 0;
						player[g_Player]->HB_ReduceRectColor.alpha = 255;

						player[g_Player]->HB_ReduceHInc = 10;
						player[g_Player]->HB_ReduceHeight = 573;

						player[g_Player]->HB_HReduceON = 1;

						if(player[g_Player]->HB_Health <= 0)
							{
							player[g_Player]->HB_Health = 0;

							/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
										&player[g_Player]->ViewXForm.Translation,
										600.0f,
										2.0f,
										&Volume,
										&Pan,
										&Frequency);*/

							//'AVATAR DEATH' SOUND
							Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);

							player[g_Player]->HB_Dead = 1;

							//### Add Experience to attacking AVATAR
							if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(player[g_Player]->HB_Armour < 0) player[g_Player]->HB_Armour = 0;
				}
			else
				{
				int f_ArmourFactor = 1000;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrHEADARMOUR >= 0 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrHEADARMOUR < 150)
					{
					f_ArmourFactor = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.CurrHEADARMOUR;
					}

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour - (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / ( (((float)f_ArmourFactor / 5000) * 2.5) )) <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt += 8;
					Q_BulletHit->BulletHit[Count].EffectType = 6;
					}

				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCntTimer = TIME;
				Q_BulletHit->BulletHit[Count].BloodAmt = 12 * (Q_BulletHit->BulletHit[Count].BulletDMG / 5);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour -= (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5));

				if((((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour + (((60 * Q_BulletHit->BulletHit[Count].BulletDMG) * ((1 - (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.BodySKILL.Constitution / 400)) + 0.75)) / (((float)f_ArmourFactor / 5000) * 2.5)) > 0)) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 6)))
					{
					//ARMOUR BLOOD
					helly = 0;
					while(helly < 22 && (_->NomBlood < 498))
						{
						Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

						Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

						Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

						Q_BBlood->BBlood[_->NomBlood].TraVec.x = (((float)rand() / 32767)-0.5)*0.5;
						Q_BBlood->BBlood[_->NomBlood].TraVec.y = (((float)rand() / 32767)-0.5)+1;
						Q_BBlood->BBlood[_->NomBlood].TraVec.z = (((float)rand() / 32767)-0.5)*0.5;
						
						Q_BBlood->BBlood[_->NomBlood].Speed = 15 * ((Q_BulletHit->BulletHit[Count].BulletPWR / 2.5) + 0.2);

						Q_BBlood->BBlood[_->NomBlood].Gravity = 0.035;

						Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
						Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
						Q_BBlood->BBlood[_->NomBlood].Live = 1;

						_->NomBlood++;
						helly++;
						}

					Q_BulletHit->BulletHit[Count].EffectType = 9;
					}

				if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

				/*if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt >= 35 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
					{
					Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 6 * Q_BulletHit->BulletHit[Count].BulletPWR;
					if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0 || (Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0))
						{
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].BulletHitCnt = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
						}
					}
				else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactSpeed = 3 * Q_BulletHit->BulletHit[Count].BulletPWR;*/

				TempVec1 = Q_BulletHit->BulletHit[Count].BulletTraj;
				Qpo->Vec3d_Normalize(&TempVec1);
				Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec = TempVec1;
				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].MoveReactVec.y = 0;
				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4))) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HitReactScale = 0.04 * (((1 - (Q_BulletHit->BulletHit[Count].BulletPWR / 10)) + 0.5) * 1.5);

				if(((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour <= 0) && !((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType < 4))) || ((_->NetworkOption == 1) && (Q_BulletHit->BulletHit[Count].EffectType >= 4)))
					{
					if(_->NetworkOption != 1)
						{
							//## Hit Reaction Motions
						if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 30)
							{
							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 26 && Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate != 28)	//Standard Hit Reactions
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 28;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							else
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0.16;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
								}
							}
						/*else								//Fall Hit Reactions
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].Aposestate = 30;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attackon = 1;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].attposecnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackcnt = 0;
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].astackrun = 0;
							}*/


						//## Reduce Health
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceOld = Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						if(Q_BulletHit->BulletHit[Count].AvID == -1) player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;
						else Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] -= Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.red = 255;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.green = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.blue = 0;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceRectColor.alpha = 255;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHInc = 10;
						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_ReduceHeight = 574;

						Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_HReduceON = 1;

						if(Q_BulletHit->BulletHit[Count].AvID == -1)
							{
							player[g_Player]->HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;
								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 10;

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						else
							{
							Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].HB_LastAvatarHitID = Q_BulletHit->BulletHit[Count].AvatarHITID;

							if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health <= 0)
								{
								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Health = 0;

								/*QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,
											&player[g_Player]->ViewXForm.Translation,
											600.0f,
											2.0f,
											&Volume,
											&Pan,
											&Frequency);*/

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].RFistPos.Translation);

								Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_BulletHit->BulletHit[Count].AvID, Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_BulletHit->BulletHit[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

									if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvID].DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
								SCRAM = 0;
								while(SCRAM < _->NomAI)
									{
									if(Q_Forge->Forge[SCRAM].LIVE == 1)
										{
										if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_BulletHit->BulletHit[Count].AvatarHITID] * (10 * Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level / 10);

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
													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].CharDATA.Level);
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
							}
						}

					//BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Red Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 0;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 255;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHit, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}
				else
					{
					//ARMOUR BLOOD
					if(Q_BulletHit->BulletHit[Count].BloodAmt > 0)
						{
						helly = 0;
						while(helly < Q_BulletHit->BulletHit[Count].BloodAmt && (_->NomBlood < 498))	//1		//8		//25
							{
							Q_BBlood->BBlood[_->NomBlood].Pos = Q_BulletHit->BulletHit[Count].Pos;

							Q_BBlood->BBlood[_->NomBlood].EffectType = 1;

							Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

							Q_BBlood->BBlood[_->NomBlood].TraVec = Q_BulletHit->BulletHit[Count].CollNormal;

							Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.1;	//((rand() % 10)/100);
							Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
							
							Q_BBlood->BBlood[_->NomBlood].Speed = 6 * (((Q_BulletHit->BulletHit[Count].BulletDMG / 3) + 0.2) + ((Q_BulletHit->BulletHit[Count].BulletPWR / 3) + 0.2));

							Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

							Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
							Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 0;
							Q_BBlood->BBlood[_->NomBlood].Live = 1;

							_->NomBlood++;
							helly++;
							}
						}

					int a=0;	//# Black Flash
					while( a <= 2 )
						{
						int b=0;
						while( b <= 3 )
							{
							Q_BulletHit->BulletHit[Count].Lvert[a][b].a = Q_BulletHit->BulletHit[Count].AlpFade/1.25;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].b = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].g = 65;
							Q_BulletHit->BulletHit[Count].Lvert[a][b].r = 65;
							b++;
							}
						a++;
						}

						//'Bullet Hit Sound'
					//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BulletHit->BulletHit[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					Qpo->Sound_Play(Medias->S_BulletHitArmour, _->Volume, _->Pan, _->S_TimeScale, false, &Q_BulletHit->BulletHit[Count].Pos);
					}

				if(Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour < 0) Q_Forge->Forge[Q_BulletHit->BulletHit[Count].AvatarHITID].HB_Armour = 0;
				}

			}

		}//END INIT


	Qpo->Transform_New(&Q_BulletHit->BulletHit[Count].AlignMatrix);
	Qpo->Transform_GetIn(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].AligIn);
	
	Q_BulletHit->BulletHit[Count].VecIn = Q_BulletHit->BulletHit[Count].CollNormal;

	if(Q_BulletHit->BulletHit[Count].VecIn.x == 0 && Q_BulletHit->BulletHit[Count].VecIn.z == 0)
		{
		Q_BulletHit->BulletHit[Count].VecLeft.x = -1;
		Q_BulletHit->BulletHit[Count].VecLeft.y = 0;
		Q_BulletHit->BulletHit[Count].VecLeft.z = 0;
		}
	else
		{
		Qpo->Transform_New_ZRotation(&rotmat, PI/2);
		Qpo->Transform_RotateVector(&rotmat, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VecLeft);
		Q_BulletHit->BulletHit[Count].VecLeft.y = 0;
		}

	Qpo->Vec3d_CrossProduct(&Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VecUp);

	Qpo->Transform_New_LeftUpIn(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VecIn);
	Q_BulletHit->BulletHit[Count].AlignMatrix.Translation = Q_BulletHit->BulletHit[Count].Pos;

	Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)*6);
	Qpo->Transform_Multiply(&Q_BulletHit->BulletHit[Count].AlignMatrix, &rotmat, &Q_BulletHit->BulletHit[Count].AlignMatrix);

	Qpo->Transform_GetUp(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecUp);
	Qpo->Transform_GetLeft(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecLeft);
	Qpo->Transform_GetIn(&Q_BulletHit->BulletHit[Count].AlignMatrix, &Q_BulletHit->BulletHit[Count].VecIn);

	Q_BulletHit->BulletHit[Count].Type = QPOLY_TYPE_TRI;
	Q_BulletHit->BulletHit[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
	Q_BulletHit->BulletHit[Count].ScaleBIT = 1.0f;
	//END INIT

	if(Q_BulletHit->BulletHit[Count].Scale - 2 > 2) Q_BulletHit->BulletHit[Count].Scale -= 2;
	else
		{
		Q_BulletHit->BulletHit[Count].Scale = 1;
		Q_BulletHit->BulletHit[Count].Live = 0;
		Q_BulletHit->BulletHit[Count].Init = 0;

		//### Array Reorder
		/*K = Count;
		while(K < _->NomBulHit - 1)
			{
			Q_BulletHit->BulletHit[K] = Q_BulletHit->BulletHit[K+1];
			K++;
			}

		_->NomBulHit--;*/

#pragma message("FIXME- Jump Tables Goto or else bridge for [-0].Live == 0");
		}

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, 0.3, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].Pos);//3


		//##Flash Vertical##
			//TOP VERT1
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertFU1);

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU1, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFU1);

			//TOP VERT2
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU1, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFU2);


			//BOTTOM VERT3
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU2, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertFU3);

			//BOTTOM VERT4
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFU3, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFU4);


		//##Flash Horizontal##
			//LEFT VERT1
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, -Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertFD1);

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD1, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFD1);


			//LEFT VERT2
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD1, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFD2);


			//RIGHT VERT3
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD2, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertFD3);

			//RIGHT VERT4
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertFD3, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecIn, &Q_BulletHit->BulletHit[Count].VertFD4);


		//##Flash Spinner##
			//TOP VERT1
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].Pos, Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertS1);

	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS1, Q_BulletHit->BulletHit[Count].Scale/2, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertS1);

			//TOP VERT2
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS1, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertS2);


			//BOTTOM VERT3
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS2, -Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecUp, &Q_BulletHit->BulletHit[Count].VertS3);

			//BOTTOM VERT4
	Qpo->Vec3d_AddScaled(&Q_BulletHit->BulletHit[Count].VertS3, Q_BulletHit->BulletHit[Count].Scale, &Q_BulletHit->BulletHit[Count].VecLeft, &Q_BulletHit->BulletHit[Count].VertS4);


	//##Flash Vertical##

	Q_BulletHit->BulletHit[Count].Lvert[0][0].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].x = Q_BulletHit->BulletHit[Count].VertFU1.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].y = Q_BulletHit->BulletHit[Count].VertFU1.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][0].z = Q_BulletHit->BulletHit[Count].VertFU1.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[0][1].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].x = Q_BulletHit->BulletHit[Count].VertFU2.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].y = Q_BulletHit->BulletHit[Count].VertFU2.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][1].z = Q_BulletHit->BulletHit[Count].VertFU2.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[0][2].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].x = Q_BulletHit->BulletHit[Count].VertFU3.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].y = Q_BulletHit->BulletHit[Count].VertFU3.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][2].z = Q_BulletHit->BulletHit[Count].VertFU3.z;


	Q_BulletHit->BulletHit[Count].Lvert[0][3].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].x = Q_BulletHit->BulletHit[Count].VertFU4.x;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].y = Q_BulletHit->BulletHit[Count].VertFU4.y;
	Q_BulletHit->BulletHit[Count].Lvert[0][3].z = Q_BulletHit->BulletHit[Count].VertFU4.z;



	//##Flash Horizontal##

	Q_BulletHit->BulletHit[Count].Lvert[1][0].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].x = Q_BulletHit->BulletHit[Count].VertFD1.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].y = Q_BulletHit->BulletHit[Count].VertFD1.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][0].z = Q_BulletHit->BulletHit[Count].VertFD1.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[1][1].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].x = Q_BulletHit->BulletHit[Count].VertFD2.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].y = Q_BulletHit->BulletHit[Count].VertFD2.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][1].z = Q_BulletHit->BulletHit[Count].VertFD2.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[1][2].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].x = Q_BulletHit->BulletHit[Count].VertFD3.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].y = Q_BulletHit->BulletHit[Count].VertFD3.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][2].z = Q_BulletHit->BulletHit[Count].VertFD3.z;


	Q_BulletHit->BulletHit[Count].Lvert[1][3].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].x = Q_BulletHit->BulletHit[Count].VertFD4.x;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].y = Q_BulletHit->BulletHit[Count].VertFD4.y;
	Q_BulletHit->BulletHit[Count].Lvert[1][3].z = Q_BulletHit->BulletHit[Count].VertFD4.z;


	//##Flash Spinner##

	Q_BulletHit->BulletHit[Count].Lvert[2][0].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].x = Q_BulletHit->BulletHit[Count].VertS1.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].y = Q_BulletHit->BulletHit[Count].VertS1.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][0].z = Q_BulletHit->BulletHit[Count].VertS1.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[2][1].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].v = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].x = Q_BulletHit->BulletHit[Count].VertS2.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].y = Q_BulletHit->BulletHit[Count].VertS2.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][1].z = Q_BulletHit->BulletHit[Count].VertS2.z;

		
	Q_BulletHit->BulletHit[Count].Lvert[2][2].u = 1;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].x = Q_BulletHit->BulletHit[Count].VertS3.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].y = Q_BulletHit->BulletHit[Count].VertS3.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][2].z = Q_BulletHit->BulletHit[Count].VertS3.z;


	Q_BulletHit->BulletHit[Count].Lvert[2][3].u = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].v = 0;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].x = Q_BulletHit->BulletHit[Count].VertS4.x;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].y = Q_BulletHit->BulletHit[Count].VertS4.y;
	Q_BulletHit->BulletHit[Count].Lvert[2][3].z = Q_BulletHit->BulletHit[Count].VertS4.z;


	Qpo->Poly_AddOnce(&Q_BulletHit->BulletHit[Count].Lvert[0][0], 4, Medias->BulHitFlash, Q_BulletHit->BulletHit[Count].Type, Q_BulletHit->BulletHit[Count].RenderFlags, Q_BulletHit->BulletHit[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_BulletHit->BulletHit[Count].Lvert[1][0], 4, Medias->BulHitFlash, Q_BulletHit->BulletHit[Count].Type, Q_BulletHit->BulletHit[Count].RenderFlags, Q_BulletHit->BulletHit[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_BulletHit->BulletHit[Count].Lvert[2][0], 4, Medias->BulHitFlashSpin, Q_BulletHit->BulletHit[Count].Type, Q_BulletHit->BulletHit[Count].RenderFlags, Q_BulletHit->BulletHit[Count].ScaleBIT);
	};//END ControlClient

};//END namespace GVARS