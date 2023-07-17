/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Melee Hits System-

*/

	//##### Hit Types ######//
	//# 0  - Simple Block  #//
	//# 1  - Block Crush   #//
	//# 2  - Shock Block   #//
	//# 3  - Deflect       #//
	//# 5  - Normal Hit    #//
	//# 10 - Mid Hit       #//
	//# 11 - Mid Hit Spec  #//
	//# 20 - Heavy Hit     #//
	//######################//

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::MeleeHit_ControlServer(int Count)
	{
	//### Attack Light
	if(Q_MeleeHit->MeleeHit[Count].INIT == 0)
		{
		Q_MeleeHit->MeleeHit[Count].INIT = 1;

		//##### HIT RESULTS
		switch(Q_MeleeHit->MeleeHit[Count].HitRESULT)
			{
			case 0:		//Block Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitB1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 20:	//Shock Block Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitB1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_ShkBlock, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 1:		//Avatar Normal Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1AV, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 2:		//Avatar FallHead Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1AV, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 3:		//Avatar Ultra Blow
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_UltraBlowMALE, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1AV, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 4:		//Player Normal Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 5:		//Player FallHead Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 6:		//Player Ultra Blow
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_UltraBlowFEMALE, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 7:		//Renzou Impact
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_RenzouImpact, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 8:		//Deflect
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_DefBlock, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 9:		//Block break
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_BrkBlock, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 10:	//Avatar DEATH
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;

			case 11:	//Player DEATH
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;

			case 17:	//Avatar DEATH BY RENZOU
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_RenzouImpact, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;

			case 18:	//Player DEATH BY RENZOU
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_RenzouImpact, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;
			}

		//##### CLEAN NET EFFICIENCY
		Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius *= Q_MeleeHit->MeleeHit[Count].AttackSTRENGTH;

		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 0)
			{
			Q_MeleeHit->MeleeHit[Count].LightColor.red = 255.0f;
			Q_MeleeHit->MeleeHit[Count].LightColor.green = 255.0f;
			Q_MeleeHit->MeleeHit[Count].LightColor.blue = 255.0f;
			Q_MeleeHit->MeleeHit[Count].LightColor.alpha = 155.0f;
			}
		else
			{
			if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1)
				{
				Q_MeleeHit->MeleeHit[Count].LightColor.red = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.green = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.blue = 160.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.alpha = 200.0f;
				}
			else
				{
				Q_MeleeHit->MeleeHit[Count].LightColor.red = 255.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.green = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.blue = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.alpha = 255.0f;
				}
			}

		Q_MeleeHit->MeleeHit[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);

		if(Q_MeleeHit->MeleeHit[Count].BloodAmt > 25) Q_MeleeHit->MeleeHit[Count].BloodAmt = 25;

		//### Blood
		//## Blood Sparks
		if(Q_MeleeHit->MeleeHit[Count].BloodAmt > 0)
			{
			helly = 0;								// 4
			while((helly < Q_MeleeHit->MeleeHit[Count].BloodAmt) && (_->NomBlood < 498))
				{
				Q_BBlood->BBlood[_->NomBlood].Pos = Q_MeleeHit->MeleeHit[Count].Impact;

				Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

				Q_BBlood->BBlood[_->NomBlood].TraVec = Q_MeleeHit->MeleeHit[Count].ReactionNorm;

				Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);
				Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.5; //0.1	//((rand() % 10)/100);
				Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);	//((rand() % 10)/100);

				Q_BBlood->BBlood[_->NomBlood].Speed = 6;

				Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

				Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

				Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
				Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
				Q_BBlood->BBlood[_->NomBlood].Live = 1;

				_->NomBlood++;
				helly++;
				}
			}

		//## Blood Clouds
		jet = 0;							///// 2
		while((jet < (Q_MeleeHit->MeleeHit[Count].BloodAmt)) && (_->NomCloud < (Q_Cloud->m_ArrayMx - Q_MeleeHit->MeleeHit[Count].BloodAmt)))
			{
			Q_Cloud->Cloud[_->NomCloud].CloudType = 1;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_MeleeHit->MeleeHit[Count].Impact;
				
			Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*2;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*55)+200;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = 0.1;

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec = TempVec1;

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*0.2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*0.2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*0.2;

			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767)-0.5)*2)+2.5;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			jet++;
			}

		//###### -  Heavy Hits  - ######
		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 20)
			{
			Q_MeleeHit->MeleeHit[Count].SpikeAMT = Q_MeleeHit->MeleeHit[Count].BloodAmt / 10;

			if(Q_MeleeHit->MeleeHit[Count].SpikeAMT < 3) Q_MeleeHit->MeleeHit[Count].SpikeAMT = 3;
			if(Q_MeleeHit->MeleeHit[Count].SpikeAMT > 45) Q_MeleeHit->MeleeHit[Count].SpikeAMT = 45;

			jet = 0;
			while((jet < (Q_MeleeHit->MeleeHit[Count].SpikeAMT * 3)) && (_->NomSpikes < 498))
				{
				//# Effect Type
				Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 0;

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
				Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_MeleeHit->MeleeHit[Count].Impact;

				//####### Create Trajectory Vector From Random Numbers
				Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
				Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
				Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

				//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[_->NomSpikes].CenterPos, 5 + (Q_MeleeHit->MeleeHit[Count].SpikeAMT / 5), &Q_HHSpike->HHSpike[_->NomSpikes].TraVec, &Q_HHSpike->HHSpike[_->NomSpikes].FrontPos);
				//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[_->NomSpikes].CenterPos, (5 + (Q_MeleeHit->MeleeHit[Count].SpikeAMT / 5)) + (Q_MeleeHit->MeleeHit[Count].SpikeAMT / 1.5), &Q_HHSpike->HHSpike[_->NomSpikes].TraVec, &Q_HHSpike->HHSpike[_->NomSpikes].TailPos);

				//######## Set Timers
				Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
				Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

				//######### Make Live
				Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

				_->NomSpikes++;
				jet++;
				}
			}

		//###### -  Mid Hits  - ######
		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 11)
			{
			jet = 0;
			while(jet < 6 && (_->NomCloud < (Q_Cloud->m_ArrayMx - 2)))
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 4;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_MeleeHit->MeleeHit[Count].Impact;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*120)+135;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.2)+0.025;

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x = (((float)rand() / 32767)-0.5) * 2;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y = (((float)rand() / 32767) * 3) + 0.8;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z = (((float)rand() / 32767)-0.5) * 2;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767))+0.3)*5;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				jet++;
				}
			}
		}


	//###### -  EXPANDRO3D  - ######

	Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT = (( Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius / Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius ) * 31 ) + 11;
	if(Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT > 42) Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT = 42;
	if(Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT < 11) Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT = 11;

	if(Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius > 0 && (((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3) && Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius < Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius) || ((Q_MeleeHit->MeleeHit[Count].HitTYPE == 0 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 2 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 3) && Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius < (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/1.4)) || (Q_MeleeHit->MeleeHit[Count].HitTYPE == 1 && Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius > 0)))
		{
		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1)
			{
			Qpo->Transform_New_XRotation(&rotmat, 0.5*_->TimeScale);
			Qpo->Transform_Multiply(&Q_MeleeHit->MeleeHit[Count].AttboneXF, &rotmat, &Q_MeleeHit->MeleeHit[Count].AttboneXF);
			}

		Qpo->Transform_GetIn(&Q_MeleeHit->MeleeHit[Count].AttboneXF,&Q_MeleeHit->MeleeHit[Count].Expandro3D.Leftvec);
		Qpo->Transform_GetLeft(&Q_MeleeHit->MeleeHit[Count].AttboneXF,&Q_MeleeHit->MeleeHit[Count].Expandro3D.Forvec);
		Qpo->Transform_GetUp(&Q_MeleeHit->MeleeHit[Count].AttboneXF,&Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec);

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1 = Q_MeleeHit->MeleeHit[Count].Impact;

		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1);
						//Distance to the Left of the player
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Leftvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1);

						//Distance to the Right of the player from the left
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, -Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius * 2, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Leftvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2, -Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius * 2, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, -Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius * 2, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4);

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].u = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].v = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].u = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].v = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].u = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].v = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].u = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].v = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;

		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1 && Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade < 160)
			{
			Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade += 40;
			Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade += 40;
			}

		if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3))
			{
			if((Q_MeleeHit->MeleeHit[Count].HitTYPE == 10 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 11))	//#### Normal Hit
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->PulsarMid[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius += (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/10); //EDIT//*_->TimeScale;
				}
			else								//#### Mid Hit
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->Pulsar[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius += (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/15); //EDIT//*_->TimeScale;
				}
			}
		else									//#### Block Hit
			{
			if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1)
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->EXPexpandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius -= (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/20); //EDIT//*_->TimeScale;
				}
			else
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->expandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius += (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/20); //EDIT//*_->TimeScale;
				}
			}

		if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3)) Qpo->Light_SetAttr(Q_MeleeHit->MeleeHit[Count].Light, &Q_MeleeHit->MeleeHit[Count].Impact, &Q_MeleeHit->MeleeHit[Count].LightColor, Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius - Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius, false);
		else Qpo->Light_SetAttr(Q_MeleeHit->MeleeHit[Count].Light, &Q_MeleeHit->MeleeHit[Count].Impact, &Q_MeleeHit->MeleeHit[Count].LightColor, (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius - Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius)*5, false);
		}
	else
		{
		if(Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade - (10*_->TimeScale) >= 0)
			{
			if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 10 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 11))	//#### Normal Hit
				{
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade -= 10*_->TimeScale;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade -= 10*_->TimeScale;
				}
			else								//#### Mid Hit
				{
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade -= 23*_->TimeScale;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade -= 23*_->TimeScale;
				}

			if(Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade >= 0)
				{
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3))
					{
					if((Q_MeleeHit->MeleeHit[Count].HitTYPE == 10 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 11)) Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->PulsarMid[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
					else Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->Pulsar[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
					}
				else Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->expandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
				}
			}
		else
			{
			Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius = 301;
			Q_MeleeHit->MeleeHit[Count].Live = 0;

			//Q_MeleeHit->MeleeHit[Count].HitTYPE = 0;

			Qpo->Light_Remove(Q_MeleeHit->MeleeHit[Count].Light);

			if(g_optionsresult == 2 || g_optionsresult == 3)
				{						//### Array Reorder
				int K = Count;
				while(K < 499 && K < _->NomMelHit - 1)
					{
					Q_MeleeHit->MeleeHit[K] = Q_MeleeHit->MeleeHit[K+1];
					K++;
					}

				_->NomMelHit--;
				}
			else
				{
				int K = Count;
				while(K < _->NomMelHit - 1)
					{
					Q_MeleeHit->MeleeHit[K] = Q_MeleeHit->MeleeHit[K+1];
					K++;
					}

				_->NomMelHit--;
				}
			}
		}


	//### Shock Block Flash
	if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 2)
		{
		jet = 0;
		while(jet < 8)	//10
			{
			//Set these vec3ds at lightning init
			Q_Lightning->Lightning[0].Pos = Q_MeleeHit->MeleeHit[Count].Impact;

			Q_Lightning->Lightning[0].TraVec.x = (((float)rand() / 32767) * 2 ) - 1;
			Q_Lightning->Lightning[0].TraVec.y = (((float)rand() / 32767) * 2 ) - 1;	// <---Maybe not this
			Q_Lightning->Lightning[0].TraVec.z = (((float)rand() / 32767) * 2 ) - 1;

			Q_Lightning->Lightning[0].LengNum = (rand() % 5) + 1;	//(rand() % 10) + 1;


			Q_Lightning->Lightning[0].Type = QPOLY_TYPE_TRI;
			Q_Lightning->Lightning[0].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
			Q_Lightning->Lightning[0].Bitmap = Medias->lightning;
			Q_Lightning->Lightning[0].Scale = 1.0f;

			Q_Lightning->Lightning[0].Count = 0;
			Q_Lightning->Lightning[0].Live = 1;


			//Q_Lightning->Lightning run process
			helly = 0;
			while(helly < (Q_Lightning->Lightning[0].LengNum + 1))
				{
				Q_Lightning->Lightning[0].TraVec.x += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.y += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.z += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;

				Q_Lightning->Lightning[0].Length = (((float)rand() / 32767) * 7) + 0.3;	//(rand() % 60) + 50;
				if(helly == 0) Q_Lightning->Lightning[0].Width = 0.2;	//0.2
				else Q_Lightning->Lightning[0].Width = (((float)rand() / 32767) * 0.1) + 0.02;	//0.06	//(rand() % 10) + 1;

				Qpo->Transform_New(&Q_Lightning->Lightning[0].Roton);
				Qpo->Transform_RotateY(&Q_Lightning->Lightning[0].Roton, 1.5708);
				Qpo->Transform_RotateVector(&Q_Lightning->Lightning[0].Roton, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].WidthVec);
				Qpo->Vec3d_Scale(&Q_Lightning->Lightning[0].WidthVec, Q_Lightning->Lightning[0].Width, &Q_Lightning->Lightning[0].WidthVec);

				if(helly == 0) Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert1);
				else Q_Lightning->Lightning[0].Vert1 = Q_Lightning->Lightning[0].Vert4;
				if(helly == 0) Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert2);
				else Q_Lightning->Lightning[0].Vert2 = Q_Lightning->Lightning[0].Vert3;

				//Rescale Width ???

				Qpo->Vec3d_AddScaled(&Q_Lightning->Lightning[0].Pos, Q_Lightning->Lightning[0].Length, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].PosEnd);

				Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert3);
				Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert4);

				Q_Lightning->Lightning[0].Pos = Q_Lightning->Lightning[0].PosEnd;


				Q_Lightning->Lightning[0].Lvert[helly][0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][0].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][0].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][0].x = Q_Lightning->Lightning[0].Vert1.x;
				Q_Lightning->Lightning[0].Lvert[helly][0].y = Q_Lightning->Lightning[0].Vert1.y;
				Q_Lightning->Lightning[0].Lvert[helly][0].z = Q_Lightning->Lightning[0].Vert1.z;


				Q_Lightning->Lightning[0].Lvert[helly][1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][1].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].x = Q_Lightning->Lightning[0].Vert2.x;
				Q_Lightning->Lightning[0].Lvert[helly][1].y = Q_Lightning->Lightning[0].Vert2.y;
				Q_Lightning->Lightning[0].Lvert[helly][1].z = Q_Lightning->Lightning[0].Vert2.z;


				Q_Lightning->Lightning[0].Lvert[helly][2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][2].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][2].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][2].x = Q_Lightning->Lightning[0].Vert3.x;
				Q_Lightning->Lightning[0].Lvert[helly][2].y = Q_Lightning->Lightning[0].Vert3.y;
				Q_Lightning->Lightning[0].Lvert[helly][2].z = Q_Lightning->Lightning[0].Vert3.z;


				Q_Lightning->Lightning[0].Lvert[helly][3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][3].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].x = Q_Lightning->Lightning[0].Vert4.x;
				Q_Lightning->Lightning[0].Lvert[helly][3].y = Q_Lightning->Lightning[0].Vert4.y;
				Q_Lightning->Lightning[0].Lvert[helly][3].z = Q_Lightning->Lightning[0].Vert4.z;

				Qpo->Poly_AddOnce(&Q_Lightning->Lightning[0].Lvert[helly][0], 4, Q_Lightning->Lightning[0].Bitmap, Q_Lightning->Lightning[0].Type, Q_Lightning->Lightning[0].RenderFlags, Q_Lightning->Lightning[0].Scale);

				helly += 1;
				}
			jet += 1;
			}
		}

	if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 3)
		{
		jet = 0;
		while(jet < 12)
			{
			//Set these vec3ds at lightning init
			Q_Lightning->Lightning[0].Pos = Q_MeleeHit->MeleeHit[Count].Impact;

			Q_Lightning->Lightning[0].TraVec.x = (((float)rand() / 32767) * 2 ) - 1;
			Q_Lightning->Lightning[0].TraVec.y = (((float)rand() / 32767) * 2 ) - 1;	// <---Maybe not this
			Q_Lightning->Lightning[0].TraVec.z = (((float)rand() / 32767) * 2 ) - 1;

			Q_Lightning->Lightning[0].LengNum = (rand() % 7) + 1;	//(rand() % 10) + 1;


			Q_Lightning->Lightning[0].Type = QPOLY_TYPE_TRI;
			Q_Lightning->Lightning[0].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
			Q_Lightning->Lightning[0].Bitmap = Medias->lightning;
			Q_Lightning->Lightning[0].Scale = 1.0f;

			Q_Lightning->Lightning[0].Count = 0;
			Q_Lightning->Lightning[0].Live = 1;


			//Q_Lightning->Lightning run process
			helly = 0;
			while(helly < (Q_Lightning->Lightning[0].LengNum + 1))
				{
				Q_Lightning->Lightning[0].TraVec.x += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.y += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.z += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;

				Q_Lightning->Lightning[0].Length = (((float)rand() / 32767) * 7) + 0.3;	//(rand() % 60) + 50;
				if(helly == 0) Q_Lightning->Lightning[0].Width = 0.2;	//0.2
				else Q_Lightning->Lightning[0].Width = (((float)rand() / 32767) * 0.1) + 0.02;	//0.06	//(rand() % 10) + 1;

				Qpo->Transform_New(&Q_Lightning->Lightning[0].Roton);
				Qpo->Transform_RotateY(&Q_Lightning->Lightning[0].Roton, 1.5708);
				Qpo->Transform_RotateVector(&Q_Lightning->Lightning[0].Roton, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].WidthVec);
				Qpo->Vec3d_Scale(&Q_Lightning->Lightning[0].WidthVec, Q_Lightning->Lightning[0].Width, &Q_Lightning->Lightning[0].WidthVec);

				if(helly == 0) Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert1);
				else Q_Lightning->Lightning[0].Vert1 = Q_Lightning->Lightning[0].Vert4;
				if(helly == 0) Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert2);
				else Q_Lightning->Lightning[0].Vert2 = Q_Lightning->Lightning[0].Vert3;

				//Rescale Width ???

				Qpo->Vec3d_AddScaled(&Q_Lightning->Lightning[0].Pos, Q_Lightning->Lightning[0].Length, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].PosEnd);

				Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert3);
				Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert4);

				Q_Lightning->Lightning[0].Pos = Q_Lightning->Lightning[0].PosEnd;


				Q_Lightning->Lightning[0].Lvert[helly][0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][0].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][0].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][0].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][0].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][0].x = Q_Lightning->Lightning[0].Vert1.x;
				Q_Lightning->Lightning[0].Lvert[helly][0].y = Q_Lightning->Lightning[0].Vert1.y;
				Q_Lightning->Lightning[0].Lvert[helly][0].z = Q_Lightning->Lightning[0].Vert1.z;


				Q_Lightning->Lightning[0].Lvert[helly][1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][1].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][1].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][1].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].x = Q_Lightning->Lightning[0].Vert2.x;
				Q_Lightning->Lightning[0].Lvert[helly][1].y = Q_Lightning->Lightning[0].Vert2.y;
				Q_Lightning->Lightning[0].Lvert[helly][1].z = Q_Lightning->Lightning[0].Vert2.z;


				Q_Lightning->Lightning[0].Lvert[helly][2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][2].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][2].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][2].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][2].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][2].x = Q_Lightning->Lightning[0].Vert3.x;
				Q_Lightning->Lightning[0].Lvert[helly][2].y = Q_Lightning->Lightning[0].Vert3.y;
				Q_Lightning->Lightning[0].Lvert[helly][2].z = Q_Lightning->Lightning[0].Vert3.z;


				Q_Lightning->Lightning[0].Lvert[helly][3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][3].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][3].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][3].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].x = Q_Lightning->Lightning[0].Vert4.x;
				Q_Lightning->Lightning[0].Lvert[helly][3].y = Q_Lightning->Lightning[0].Vert4.y;
				Q_Lightning->Lightning[0].Lvert[helly][3].z = Q_Lightning->Lightning[0].Vert4.z;

				Qpo->Poly_AddOnce(&Q_Lightning->Lightning[0].Lvert[helly][0], 4, Q_Lightning->Lightning[0].Bitmap, Q_Lightning->Lightning[0].Type, Q_Lightning->Lightning[0].RenderFlags, Q_Lightning->Lightning[0].Scale);

				helly += 1;
				}
			jet += 1;
			}
		}
	}


void Q_EFFCon::MeleeHit_ControlClient(int Count)
	{
	//### Attack Light
	if(Q_MeleeHit->MeleeHit[Count].INIT == 0)
		{
		Q_MeleeHit->MeleeHit[Count].INIT = 1;

		//##### HIT RESULTS
		switch(Q_MeleeHit->MeleeHit[Count].HitRESULT)
			{
			case 0:		//Block Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitB1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 20:	//Shock Block Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitB1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_ShkBlock, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 1:		//Avatar Normal Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1AV, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 2:		//Avatar FallHead Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1AV, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 3:		//Avatar Ultra Blow
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_UltraBlowMALE, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1AV, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 4:		//Player Normal Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 5:		//Player FallHead Hit
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 6:		//Player Ultra Blow
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_UltraBlowFEMALE, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfH1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_HitSelfN1, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 7:		//Renzou Impact
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_RenzouImpact, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 8:		//Deflect
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_DefBlock, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 9:		//Block break
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_BrkBlock, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);
				} break;

			case 10:	//Avatar DEATH
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;

			case 11:	//Player DEATH
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;

			case 17:	//Avatar DEATH BY RENZOU
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_RenzouImpact, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;

			case 18:	//Player DEATH BY RENZOU
				{
				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Impact, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_RenzouImpact, _->Volume, _->Pan, _->S_TimeScale, false, &Q_MeleeHit->MeleeHit[Count].Impact);

				if(_->TimeHole == 0)
					{ _->TimeHole = 4; _->TimeRotate = 1;	}
				} break;
			}

		//##### CLEAN NET EFFICIENCY
		Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius *= Q_MeleeHit->MeleeHit[Count].AttackSTRENGTH;

		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 0)
			{
			Q_MeleeHit->MeleeHit[Count].LightColor.red = 255.0f;
			Q_MeleeHit->MeleeHit[Count].LightColor.green = 255.0f;
			Q_MeleeHit->MeleeHit[Count].LightColor.blue = 255.0f;
			Q_MeleeHit->MeleeHit[Count].LightColor.alpha = 155.0f;
			}
		else
			{
			if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1)
				{
				Q_MeleeHit->MeleeHit[Count].LightColor.red = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.green = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.blue = 160.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.alpha = 200.0f;
				}
			else
				{
				Q_MeleeHit->MeleeHit[Count].LightColor.red = 255.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.green = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.blue = 0.0f;
				Q_MeleeHit->MeleeHit[Count].LightColor.alpha = 255.0f;
				}
			}

		Q_MeleeHit->MeleeHit[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);

		if(Q_MeleeHit->MeleeHit[Count].BloodAmt > 25) Q_MeleeHit->MeleeHit[Count].BloodAmt = 25;

		//### Blood
		//## Blood Sparks
		if(Q_MeleeHit->MeleeHit[Count].BloodAmt > 0)
			{
			helly = 0;
			while((helly < Q_MeleeHit->MeleeHit[Count].BloodAmt / 6) && (_->NomBlood < 498))
				{
				Q_BBlood->BBlood[_->NomBlood].Pos = Q_MeleeHit->MeleeHit[Count].Impact;

				Q_BBlood->BBlood[_->NomBlood].AlpFade = 210;

				Q_BBlood->BBlood[_->NomBlood].TraVec = Q_MeleeHit->MeleeHit[Count].ReactionNorm;

				Q_BBlood->BBlood[_->NomBlood].TraVec.x += ((((float)rand() / 32767)/2)-0.25);
				Q_BBlood->BBlood[_->NomBlood].TraVec.y += ((((float)rand() / 32767)/2)-0.25)+0.5;
				Q_BBlood->BBlood[_->NomBlood].TraVec.z += ((((float)rand() / 32767)/2)-0.25);

				Q_BBlood->BBlood[_->NomBlood].Speed = 6;

				Q_BBlood->BBlood[_->NomBlood].Gravity = 0.08;

				Q_BBlood->BBlood[_->NomBlood].EffectType = 0;

				Q_BBlood->BBlood[_->NomBlood].Bounce = 0;
				Q_BBlood->BBlood[_->NomBlood].SmokeTrail = 1;
				Q_BBlood->BBlood[_->NomBlood].Live = 1;

				_->NomBlood++;
				helly++;
				}
			}

		//## Blood Clouds
		jet = 0;
		while((jet < (Q_MeleeHit->MeleeHit[Count].BloodAmt / 5)) && (Q_Cloud->m_ArrayMx - Q_MeleeHit->MeleeHit[Count].BloodAmt / 5))
			{
			Q_Cloud->Cloud[_->NomCloud].CloudType = 1;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_MeleeHit->MeleeHit[Count].Impact;
				
			Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*2;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*55)+200;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = 0.1;

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec = TempVec1;

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*0.2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*0.2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*0.2;

			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767)-0.5)*2)+2.5;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			jet++;
			}

		//###### -  Heavy Hits  - ######
		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 20)
			{
			Q_MeleeHit->MeleeHit[Count].SpikeAMT = Q_MeleeHit->MeleeHit[Count].BloodAmt / 10;

			if(Q_MeleeHit->MeleeHit[Count].SpikeAMT < 3) Q_MeleeHit->MeleeHit[Count].SpikeAMT = 3;
			if(Q_MeleeHit->MeleeHit[Count].SpikeAMT > 45) Q_MeleeHit->MeleeHit[Count].SpikeAMT = 45;

			jet = 0;
			while(jet < Q_MeleeHit->MeleeHit[Count].SpikeAMT && (_->NomSpikes < 498))
				{
				//# Effect Type
				Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 0;

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
				Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_MeleeHit->MeleeHit[Count].Impact;

				//####### Create Trajectory Vector From Random Numbers
				Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
				Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
				Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

				//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[_->NomSpikes].CenterPos, 5 + (Q_MeleeHit->MeleeHit[Count].SpikeAMT / 5), &Q_HHSpike->HHSpike[_->NomSpikes].TraVec, &Q_HHSpike->HHSpike[_->NomSpikes].FrontPos);
				//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[_->NomSpikes].CenterPos, (5 + (Q_MeleeHit->MeleeHit[Count].SpikeAMT / 5)) + (Q_MeleeHit->MeleeHit[Count].SpikeAMT / 1.5), &Q_HHSpike->HHSpike[_->NomSpikes].TraVec, &Q_HHSpike->HHSpike[_->NomSpikes].TailPos);

				//######## Set Timers
				Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
				Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

				//######### Make Live
				Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

				_->NomSpikes++;
				jet++;
				}
			}

		//###### -  Mid Hits  - ######
		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 11)
			{
			jet = 0;
			while((jet < 6) && (Q_Cloud->m_ArrayMx - 2))
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 4;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_MeleeHit->MeleeHit[Count].Impact;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*120)+135;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.2)+0.025;

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x = (((float)rand() / 32767)-0.5) * 2;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y = (((float)rand() / 32767) * 3) + 0.8;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z = (((float)rand() / 32767)-0.5) * 2;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767))+0.3)*5;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				jet++;
				}
			}
		}


	//###### -  Q_MeleeHit->MeleeHit[Count].Expandro3D  - ######

	Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT = (( Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius / Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius ) * 31 ) + 11;
	if(Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT > 42) Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT = 42;
	if(Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT < 11) Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT = 11;

	if(Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius > 0 && (((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3) && Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius < Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius) || ((Q_MeleeHit->MeleeHit[Count].HitTYPE == 0 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 2 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 3) && Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius < (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/1.4)) || (Q_MeleeHit->MeleeHit[Count].HitTYPE == 1 && Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius > 0)))
		{
		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1)
			{
			Qpo->Transform_New_XRotation(&rotmat, 0.5*_->TimeScale);
			Qpo->Transform_Multiply(&Q_MeleeHit->MeleeHit[Count].AttboneXF, &rotmat, &Q_MeleeHit->MeleeHit[Count].AttboneXF);
			}

		Qpo->Transform_GetIn(&Q_MeleeHit->MeleeHit[Count].AttboneXF,&Q_MeleeHit->MeleeHit[Count].Expandro3D.Leftvec);
		Qpo->Transform_GetLeft(&Q_MeleeHit->MeleeHit[Count].AttboneXF,&Q_MeleeHit->MeleeHit[Count].Expandro3D.Forvec);
		Qpo->Transform_GetUp(&Q_MeleeHit->MeleeHit[Count].AttboneXF,&Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec);

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1 = Q_MeleeHit->MeleeHit[Count].Impact;

		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1);
						//Distance to the Left of the player
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Leftvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1);

						//Distance to the Right of the player from the left
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, -Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius * 2, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Leftvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2, -Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius * 2, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1, -Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius * 2, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Upvec, &Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4);

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].u = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].v = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert1.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].u = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].v = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert2.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].u = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].v = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert3.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].b = Q_MeleeHit->MeleeHit[Count].Expandro3D.Blue;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].g = Q_MeleeHit->MeleeHit[Count].Expandro3D.Green;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].r = Q_MeleeHit->MeleeHit[Count].Expandro3D.Red;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].u = 0;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].v = 1;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].x = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4.x;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].y = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4.y;
		Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].z = Q_MeleeHit->MeleeHit[Count].Expandro3D.Vert4.z;

		Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;

		if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1 && Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade < 160)
			{
			Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade += 40;
			Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade += 40;
			}

		if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3))
			{
			if((Q_MeleeHit->MeleeHit[Count].HitTYPE == 10 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 11))	//#### Normal Hit
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->PulsarMid[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius += (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/10); //EDIT//*_->TimeScale;
				}
			else								//#### Mid Hit
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->Pulsar[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius += (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/15); //EDIT//*_->TimeScale;
				}
			}
		else									//#### Block Hit
			{
			if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 1)
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->EXPexpandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius -= (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/20); //EDIT//*_->TimeScale;
				}
			else
				{
				Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->expandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius += (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius/20); //EDIT//*_->TimeScale;
				}
			}

		if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3)) Qpo->Light_SetAttr(Q_MeleeHit->MeleeHit[Count].Light, &Q_MeleeHit->MeleeHit[Count].Impact, &Q_MeleeHit->MeleeHit[Count].LightColor, Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius - Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius, false);
		else Qpo->Light_SetAttr(Q_MeleeHit->MeleeHit[Count].Light, &Q_MeleeHit->MeleeHit[Count].Impact, &Q_MeleeHit->MeleeHit[Count].LightColor, (Q_MeleeHit->MeleeHit[Count].Expandro3D.MaxRadius - Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius)*5, false);
		}
	else
		{
		if(Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade - (10*_->TimeScale) >= 0)
			{
			if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 10 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 11))	//#### Normal Hit
				{
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade -= 10*_->TimeScale;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade -= 10*_->TimeScale;
				}
			else								//#### Mid Hit
				{
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade -= 23*_->TimeScale;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade -= 23*_->TimeScale;
				}

			if(Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade >= 0)
				{
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.Fade;
				if((Q_MeleeHit->MeleeHit[Count].HitTYPE != 0 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 1 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 2 && Q_MeleeHit->MeleeHit[Count].HitTYPE != 3))
					{
					if((Q_MeleeHit->MeleeHit[Count].HitTYPE == 10 || Q_MeleeHit->MeleeHit[Count].HitTYPE == 11)) Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->PulsarMid[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
					else Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->Pulsar[Q_MeleeHit->MeleeHit[Count].Expandro3D.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);
					}
				else Qpo->Poly_AddOnce(&Q_MeleeHit->MeleeHit[Count].Expandro3D.Lvert[0], 4, Medias->expandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
				}
			}
		else
			{
			Q_MeleeHit->MeleeHit[Count].Expandro3D.Radius = 301;
			Q_MeleeHit->MeleeHit[Count].Live = 0;

			Qpo->Light_Remove(Q_MeleeHit->MeleeHit[Count].Light);

			/*### Array Reorder
			int K = aero;
			while(K < _->NomMelHit - 1)
				{
				Q_MeleeHit->MeleeHit[K] = Q_MeleeHit->MeleeHit[K+1];
				K++;
				}

			_->NomMelHit--;*/
			}
		}

	//### Shock Block Flash
	if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 2)
		{
		jet = 0;
		while(jet < 8)	//10
			{
			//Set these vec3ds at lightning init
			Q_Lightning->Lightning[0].Pos = Q_MeleeHit->MeleeHit[Count].Impact;

			Q_Lightning->Lightning[0].TraVec.x = (((float)rand() / 32767) * 2 ) - 1;
			Q_Lightning->Lightning[0].TraVec.y = (((float)rand() / 32767) * 2 ) - 1;	// <---Maybe not this
			Q_Lightning->Lightning[0].TraVec.z = (((float)rand() / 32767) * 2 ) - 1;

			Q_Lightning->Lightning[0].LengNum = (rand() % 5) + 1;	//(rand() % 10) + 1;


			Q_Lightning->Lightning[0].Type = QPOLY_TYPE_TRI;
			Q_Lightning->Lightning[0].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
			Q_Lightning->Lightning[0].Bitmap = Medias->lightning;
			Q_Lightning->Lightning[0].Scale = 1.0f;

			Q_Lightning->Lightning[0].Count = 0;
			Q_Lightning->Lightning[0].Live = 1;


			//Q_Lightning->Lightning run process
			helly = 0;
			while(helly < (Q_Lightning->Lightning[0].LengNum + 1))
				{
				Q_Lightning->Lightning[0].TraVec.x += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.y += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.z += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;

				Q_Lightning->Lightning[0].Length = (((float)rand() / 32767) * 7) + 0.3;	//(rand() % 60) + 50;
				if(helly == 0) Q_Lightning->Lightning[0].Width = 0.2;	//0.2
				else Q_Lightning->Lightning[0].Width = (((float)rand() / 32767) * 0.1) + 0.02;	//0.06	//(rand() % 10) + 1;

				Qpo->Transform_New(&Q_Lightning->Lightning[0].Roton);
				Qpo->Transform_RotateY(&Q_Lightning->Lightning[0].Roton, 1.5708);
				Qpo->Transform_RotateVector(&Q_Lightning->Lightning[0].Roton, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].WidthVec);
				Qpo->Vec3d_Scale(&Q_Lightning->Lightning[0].WidthVec, Q_Lightning->Lightning[0].Width, &Q_Lightning->Lightning[0].WidthVec);

				if(helly == 0) Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert1);
				else Q_Lightning->Lightning[0].Vert1 = Q_Lightning->Lightning[0].Vert4;
				if(helly == 0) Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert2);
				else Q_Lightning->Lightning[0].Vert2 = Q_Lightning->Lightning[0].Vert3;

				//Rescale Width ???

				Qpo->Vec3d_AddScaled(&Q_Lightning->Lightning[0].Pos, Q_Lightning->Lightning[0].Length, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].PosEnd);

				Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert3);
				Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert4);

				Q_Lightning->Lightning[0].Pos = Q_Lightning->Lightning[0].PosEnd;


				Q_Lightning->Lightning[0].Lvert[helly][0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][0].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][0].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][0].x = Q_Lightning->Lightning[0].Vert1.x;
				Q_Lightning->Lightning[0].Lvert[helly][0].y = Q_Lightning->Lightning[0].Vert1.y;
				Q_Lightning->Lightning[0].Lvert[helly][0].z = Q_Lightning->Lightning[0].Vert1.z;


				Q_Lightning->Lightning[0].Lvert[helly][1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][1].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].x = Q_Lightning->Lightning[0].Vert2.x;
				Q_Lightning->Lightning[0].Lvert[helly][1].y = Q_Lightning->Lightning[0].Vert2.y;
				Q_Lightning->Lightning[0].Lvert[helly][1].z = Q_Lightning->Lightning[0].Vert2.z;


				Q_Lightning->Lightning[0].Lvert[helly][2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][2].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][2].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][2].x = Q_Lightning->Lightning[0].Vert3.x;
				Q_Lightning->Lightning[0].Lvert[helly][2].y = Q_Lightning->Lightning[0].Vert3.y;
				Q_Lightning->Lightning[0].Lvert[helly][2].z = Q_Lightning->Lightning[0].Vert3.z;


				Q_Lightning->Lightning[0].Lvert[helly][3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][3].b = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].g = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].x = Q_Lightning->Lightning[0].Vert4.x;
				Q_Lightning->Lightning[0].Lvert[helly][3].y = Q_Lightning->Lightning[0].Vert4.y;
				Q_Lightning->Lightning[0].Lvert[helly][3].z = Q_Lightning->Lightning[0].Vert4.z;

				Qpo->Poly_AddOnce(&Q_Lightning->Lightning[0].Lvert[helly][0], 4, Q_Lightning->Lightning[0].Bitmap, Q_Lightning->Lightning[0].Type, Q_Lightning->Lightning[0].RenderFlags, Q_Lightning->Lightning[0].Scale);

				helly += 1;
				}
			jet += 1;
			}
		}

	if(Q_MeleeHit->MeleeHit[Count].HitTYPE == 3)
		{
		jet = 0;
		while(jet < 12)
			{
			//Set these vec3ds at lightning init
			Q_Lightning->Lightning[0].Pos = Q_MeleeHit->MeleeHit[Count].Impact;

			Q_Lightning->Lightning[0].TraVec.x = (((float)rand() / 32767) * 2 ) - 1;
			Q_Lightning->Lightning[0].TraVec.y = (((float)rand() / 32767) * 2 ) - 1;	// <---Maybe not this
			Q_Lightning->Lightning[0].TraVec.z = (((float)rand() / 32767) * 2 ) - 1;

			Q_Lightning->Lightning[0].LengNum = (rand() % 7) + 1;	//(rand() % 10) + 1;


			Q_Lightning->Lightning[0].Type = QPOLY_TYPE_TRI;
			Q_Lightning->Lightning[0].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
			Q_Lightning->Lightning[0].Bitmap = Medias->lightning;
			Q_Lightning->Lightning[0].Scale = 1.0f;

			Q_Lightning->Lightning[0].Count = 0;
			Q_Lightning->Lightning[0].Live = 1;


			//Q_Lightning->Lightning run process
			helly = 0;
			while(helly < (Q_Lightning->Lightning[0].LengNum + 1))
				{
				Q_Lightning->Lightning[0].TraVec.x += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.y += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;
				Q_Lightning->Lightning[0].TraVec.z += (((float)rand() / 32767) * 2 ) - 1;	//(((float)rand() / 32767)) - 0.5;

				Q_Lightning->Lightning[0].Length = (((float)rand() / 32767) * 7) + 0.3;	//(rand() % 60) + 50;
				if(helly == 0) Q_Lightning->Lightning[0].Width = 0.2;	//0.2
				else Q_Lightning->Lightning[0].Width = (((float)rand() / 32767) * 0.1) + 0.02;	//0.06	//(rand() % 10) + 1;

				Qpo->Transform_New(&Q_Lightning->Lightning[0].Roton);
				Qpo->Transform_RotateY(&Q_Lightning->Lightning[0].Roton, 1.5708);
				Qpo->Transform_RotateVector(&Q_Lightning->Lightning[0].Roton, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].WidthVec);
				Qpo->Vec3d_Scale(&Q_Lightning->Lightning[0].WidthVec, Q_Lightning->Lightning[0].Width, &Q_Lightning->Lightning[0].WidthVec);

				if(helly == 0) Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert1);
				else Q_Lightning->Lightning[0].Vert1 = Q_Lightning->Lightning[0].Vert4;
				if(helly == 0) Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].Pos, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert2);
				else Q_Lightning->Lightning[0].Vert2 = Q_Lightning->Lightning[0].Vert3;

				//Rescale Width ???

				Qpo->Vec3d_AddScaled(&Q_Lightning->Lightning[0].Pos, Q_Lightning->Lightning[0].Length, &Q_Lightning->Lightning[0].TraVec, &Q_Lightning->Lightning[0].PosEnd);

				Qpo->Vec3d_Add(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert3);
				Qpo->Vec3d_Subtract(&Q_Lightning->Lightning[0].PosEnd, &Q_Lightning->Lightning[0].WidthVec, &Q_Lightning->Lightning[0].Vert4);

				Q_Lightning->Lightning[0].Pos = Q_Lightning->Lightning[0].PosEnd;


				Q_Lightning->Lightning[0].Lvert[helly][0].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][0].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][0].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][0].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][0].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][0].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][0].x = Q_Lightning->Lightning[0].Vert1.x;
				Q_Lightning->Lightning[0].Lvert[helly][0].y = Q_Lightning->Lightning[0].Vert1.y;
				Q_Lightning->Lightning[0].Lvert[helly][0].z = Q_Lightning->Lightning[0].Vert1.z;


				Q_Lightning->Lightning[0].Lvert[helly][1].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][1].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][1].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][1].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][1].u = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][1].x = Q_Lightning->Lightning[0].Vert2.x;
				Q_Lightning->Lightning[0].Lvert[helly][1].y = Q_Lightning->Lightning[0].Vert2.y;
				Q_Lightning->Lightning[0].Lvert[helly][1].z = Q_Lightning->Lightning[0].Vert2.z;


				Q_Lightning->Lightning[0].Lvert[helly][2].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][2].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][2].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][2].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][2].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][2].v = 1;
				Q_Lightning->Lightning[0].Lvert[helly][2].x = Q_Lightning->Lightning[0].Vert3.x;
				Q_Lightning->Lightning[0].Lvert[helly][2].y = Q_Lightning->Lightning[0].Vert3.y;
				Q_Lightning->Lightning[0].Lvert[helly][2].z = Q_Lightning->Lightning[0].Vert3.z;


				Q_Lightning->Lightning[0].Lvert[helly][3].a = Q_MeleeHit->MeleeHit[Count].Expandro3D.StartFade;
				Q_Lightning->Lightning[0].Lvert[helly][3].b = 95;
				Q_Lightning->Lightning[0].Lvert[helly][3].g = 95;
				Q_Lightning->Lightning[0].Lvert[helly][3].r = 255;
				Q_Lightning->Lightning[0].Lvert[helly][3].u = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].v = 0;
				Q_Lightning->Lightning[0].Lvert[helly][3].x = Q_Lightning->Lightning[0].Vert4.x;
				Q_Lightning->Lightning[0].Lvert[helly][3].y = Q_Lightning->Lightning[0].Vert4.y;
				Q_Lightning->Lightning[0].Lvert[helly][3].z = Q_Lightning->Lightning[0].Vert4.z;

				Qpo->Poly_AddOnce(&Q_Lightning->Lightning[0].Lvert[helly][0], 4, Q_Lightning->Lightning[0].Bitmap, Q_Lightning->Lightning[0].Type, Q_Lightning->Lightning[0].RenderFlags, Q_Lightning->Lightning[0].Scale);

				helly += 1;
				}
			jet += 1;
			}
		}
	};//END ControlClient

};