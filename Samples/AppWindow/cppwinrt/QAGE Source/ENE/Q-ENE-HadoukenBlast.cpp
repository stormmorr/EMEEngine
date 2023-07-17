/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Hadouken Blast-

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
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"

using namespace GVARS;

namespace GVARS
{

	//########  - LARGE ENERGY ATTACKS -  ########//

void Q_EFFCon::LEnergy_ServerFrame(int Count)
	{
	if(Q_LEnergy->LEnergy[Count].Init == 0 && Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		Q_LEnergy->LEnergy[Count].Init = 1;
		Q_LEnergy->LEnergy[Count].Power = 1;
		Q_LEnergy->LEnergy[Count].EnergyFire = 0;
		Q_LEnergy->LEnergy[Count].Scale = 0.01;
		Q_LEnergy->LEnergy[Count].ScaleInc = 0.005;
		Q_LEnergy->LEnergy[Count].ScaleGrow = 0;
		Q_LEnergy->LEnergy[Count].Speed = 3;
		Q_LEnergy->LEnergy[Count].Alpha = 170;
		//Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].Alpha);
		Q_LEnergy->LEnergy[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_LEnergy->LEnergy[Count].Lightcolor.red = 255;
		Q_LEnergy->LEnergy[Count].Lightcolor.green = 255;
		Q_LEnergy->LEnergy[Count].Lightcolor.blue = 190;
		Q_LEnergy->LEnergy[Count].Lightcolor.alpha = 255;

		//Init Flame Wake

		jet = 0;
		while(jet < 20)
			{
			//# Effect Type ## Hadouken Spike ##
			Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 1;

			//## Speed
			Q_HHSpike->HHSpike[_->NomSpikes].Speed = ((((float)rand() / 32767)*50)+50);

			//### Width
			Q_HHSpike->HHSpike[_->NomSpikes].Width = (((float)rand() / 32767)*15);

			//##### Alpha Level
			Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = (((float)rand() / 32767)*255);
			Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

			//###### Center Position
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_LEnergy->LEnergy[Count].LightPos;
			Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

			Q_HHSpike->HHSpike[_->NomSpikes].EnergyID = Count;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].IncX = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncY = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncZ = (((float)rand() / 32767)-0.5)*20;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.x = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.y = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.z = (((float)rand() / 32767)-0.5)*2;

			//######## Set Timers
			Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;

			//######### Make Live
			Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

			_->NomSpikes++;
			if(_->NomSpikes > 499) _->NomSpikes = 0;
			jet++;
			}

		jet = 0;
		while(jet < 65)
			{
			//# Effect Type ## Hadouken Spike ##
			Q_HHSpike->HHSpike[_->NomSpikes].SelFinger = (float)rand() / 32767;

			if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger < 0.7) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 5;
			if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger > 0.7) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 3;
			if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger > 0.9) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 6;

			//## Speed
			Q_HHSpike->HHSpike[_->NomSpikes].Speed = ((((float)rand() / 32767)*50)+50);

			//### Width
			Q_HHSpike->HHSpike[_->NomSpikes].Width = (((float)rand() / 32767)*15);

			//##### Alpha Level
			Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = (((float)rand() / 32767)*255);
			Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

			//###### Center Position
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_LEnergy->LEnergy[Count].LightPos;
			Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

			Q_HHSpike->HHSpike[_->NomSpikes].EnergyID = Count;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].IncX = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncY = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncZ = (((float)rand() / 32767)-0.5)*20;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.x = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.y = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.z = (((float)rand() / 32767)-0.5)*2;

			//######## Set Timers
			Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;

			//######### Make Live
			Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

			_->NomSpikes++;
			if(_->NomSpikes > 499) _->NomSpikes = 0;
			jet++;
			}
		}


	if(Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		if(Q_LEnergy->LEnergy[Count].Power <= 30) player[g_Player]->LaserAlpha = (Q_LEnergy->LEnergy[Count].Power * 2) + 15;
		else player[g_Player]->LaserAlpha = 75;


		Q_LEnergy->LEnergy[Count].CoronaLENGTH = Qpo->Vec3d_DistanceBetween(&Q_LEnergy->LEnergy[Count].LightPos, &player[g_Player]->ViewXForm.Translation);

		Qpo->Transform_GetIn(&player[g_Player]->ViewXForm, &Q_LEnergy->LEnergy[Count].CoronaVECIN);
		Qpo->Transform_GetUp(&player[g_Player]->ViewXForm, &Q_LEnergy->LEnergy[Count].CoronaVECUP);
		Qpo->Vec3d_CrossProduct(&Q_LEnergy->LEnergy[Count].CoronaVECIN, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT);

		Qpo->Transform_New(&Q_LEnergy->LEnergy[Count].CoronaMATRIX);

		Q_LEnergy->LEnergy[Count].CoronaMATV1.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV1.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV1.z = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV2.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV2.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV2.z = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV3.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV3.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV3.z = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV4.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV4.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV4.z = 0;

		//### Matrix Vert 1
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, Q_LEnergy->LEnergy[Count].CoronaLENGTH/30);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV1, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV1);

		//### Matrix Vert 2
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, PI/2);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV2, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV2);

		//### Matrix Vert 1
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, PI/2);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV3, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV3);

		//### Matrix Vert 1
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, PI/2);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV4, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV4);


		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV1.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT1);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV2.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT2);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV4.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT4);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV3.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT3);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT1, Q_LEnergy->LEnergy[Count].CoronaMATV1.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT1);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT2, Q_LEnergy->LEnergy[Count].CoronaMATV2.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT2);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT4, Q_LEnergy->LEnergy[Count].CoronaMATV4.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT4);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT3, Q_LEnergy->LEnergy[Count].CoronaMATV3.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT3);


		Q_LEnergy->LEnergy[Count].CoronaLV[0].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].u = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].v = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].x = Q_LEnergy->LEnergy[Count].CoronaVERT1.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].y = Q_LEnergy->LEnergy[Count].CoronaVERT1.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].z = Q_LEnergy->LEnergy[Count].CoronaVERT1.z;

		Q_LEnergy->LEnergy[Count].CoronaLV[1].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].u = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].v = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].x = Q_LEnergy->LEnergy[Count].CoronaVERT2.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].y = Q_LEnergy->LEnergy[Count].CoronaVERT2.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].z = Q_LEnergy->LEnergy[Count].CoronaVERT2.z;

		Q_LEnergy->LEnergy[Count].CoronaLV[2].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].u = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].v = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].x = Q_LEnergy->LEnergy[Count].CoronaVERT3.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].y = Q_LEnergy->LEnergy[Count].CoronaVERT3.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].z = Q_LEnergy->LEnergy[Count].CoronaVERT3.z;

		Q_LEnergy->LEnergy[Count].CoronaLV[3].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].u = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].v = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].x = Q_LEnergy->LEnergy[Count].CoronaVERT4.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].y = Q_LEnergy->LEnergy[Count].CoronaVERT4.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].z = Q_LEnergy->LEnergy[Count].CoronaVERT4.z;

		Q_LEnergy->LEnergy[Count].CoronaMATCNT++;
		if(Q_LEnergy->LEnergy[Count].CoronaMATCNT < 0) Q_LEnergy->LEnergy[Count].CoronaMATCNT = 0;
		if(Q_LEnergy->LEnergy[Count].CoronaMATCNT > 25) Q_LEnergy->LEnergy[Count].CoronaMATCNT = 0;

		Qpo->Poly_AddOnce(&Q_LEnergy->LEnergy[Count].CoronaLV[0], 4, Medias->Star[Q_LEnergy->LEnergy[Count].CoronaMATCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);

		//Qpo->Poly_AddOnce(&Q_LEnergy->LEnergy[Count].CoronaLV[0], 4, Medias->shineE, QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);

		//Qpo->Light_SetAttr(Q_LEnergy->LEnergy[Count].Light, &Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].Lightcolor, Q_LEnergy->LEnergy[Count].Power + (((rand() % Q_LEnergy->LEnergy[Count].Power) / 5) - (Q_LEnergy->LEnergy[Count].Power / 10)), false);
		Qpo->Light_SetAttr(Q_LEnergy->LEnergy[Count].Light, &Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].Lightcolor, 15, false);
																																	  //500
	
		//Qpo->Mesh_GetTex(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].BmpCount, Q_LEnergy->LEnergy[Count].Bitmap, &Q_LEnergy->LEnergy[Count].BitmapRed, &Q_LEnergy->LEnergy[Count].BitmapGreen, &Q_LEnergy->LEnergy[Count].BitmapBlue);
		//Qpo->Mesh_GetTex(&Q_LEnergy->LEnergy[Count].EnergyBall, 0, Q_LEnergy->LEnergy[Count].Bitmap, &Q_LEnergy->LEnergy[Count].BitmapRed, &Q_LEnergy->LEnergy[Count].BitmapGreen, &Q_LEnergy->LEnergy[Count].BitmapBlue);

		if(Q_LEnergy->LEnergy[Count].BmpCountSP - 1 > 0) Q_LEnergy->LEnergy[Count].BmpCountSP--;
		else
			{
			Q_LEnergy->LEnergy[Count].BmpCountSP = 6;
			if(Q_LEnergy->LEnergy[Count].BmpCount + 1 < 14) Q_LEnergy->LEnergy[Count].BmpCount++;	//18
			else Q_LEnergy->LEnergy[Count].BmpCount = 0;
			}

		Qpo->Vec3d_Copy(&Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
		//Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].EnergyScale*Q_LEnergy->LEnergy[Count].EnergyScaleXSquash,Q_LEnergy->LEnergy[Count].EnergyScale*Q_LEnergy->LEnergy[Count].EnergyScaleYSquash,Q_LEnergy->LEnergy[Count].EnergyScale*Q_LEnergy->LEnergy[Count].EnergyScaleZSquash);
		Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].Scale,Q_LEnergy->LEnergy[Count].Scale,Q_LEnergy->LEnergy[Count].Scale);
		//EDIT************ Scale Altered

		Qpo->Transform_New_ZRotation(&AIfriendly, 0);
		Qpo->Transform_New_YRotation(&AIfriendly, 0.2);

		//~~##~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Count].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform);
		}


	if(Q_LEnergy->LEnergy[Count].EnergyFire == 0 && Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		if(Q_LEnergy->LEnergy[Count].Scale < 0.13 && Q_LEnergy->LEnergy[Count].ScaleGrow == 0)
			{
			Q_LEnergy->LEnergy[Count].Scale += Q_LEnergy->LEnergy[Count].ScaleInc;	//0.0008;	//0.008//0.05	************HERE*************
			Q_LEnergy->LEnergy[Count].ScaleInc -= 0.0005;
			Q_LEnergy->LEnergy[Count].SaveScale = Q_LEnergy->LEnergy[Count].Scale;	//Not Nessesary **********
			}
		else
			{
			Q_LEnergy->LEnergy[Count].Scale = Q_LEnergy->LEnergy[Count].SaveScale + ((((float)rand() / 32767) - 0.5) / 50);
			Q_LEnergy->LEnergy[Count].ScaleGrow = 1;
			}

		if(Q_LEnergy->LEnergy[Count].AvID == 250)
			{
			if(player[g_Player]->Aposestate != 50 && player[g_Player]->Aposestate != 78)
				{
				Qpo->Light_Remove(Q_LEnergy->LEnergy[Count].Light);
				Q_LEnergy->LEnergy[Count].Init = 0;
				Q_LEnergy->LEnergy[Count].Live = 0;
				Q_LEnergy->LEnergy[Count].EnergyLive = 0;
				Q_LEnergy->LEnergy[Count].EnergyFire = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, 0,0,0);
				//~~##~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Count].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform);

				//### Energy Array Reorder
				int K = Count;
				while(K < _->NomLEnergy - 1)
					{
					Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
					K++;
					}

				_->NomLEnergy--;
				}
			}
		else
			{
			if(Q_Forge->Forge[Q_LEnergy->LEnergy[Count].AvID].Aposestate != 50 && Q_Forge->Forge[Q_LEnergy->LEnergy[Count].AvID].Aposestate != 78)
				{
				Qpo->Light_Remove(Q_LEnergy->LEnergy[Count].Light);
				Q_LEnergy->LEnergy[Count].Init = 0;
				Q_LEnergy->LEnergy[Count].Live = 0;
				Q_LEnergy->LEnergy[Count].EnergyLive = 0;
				Q_LEnergy->LEnergy[Count].EnergyFire = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, 0,0,0);
				//~~##~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Count].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform);

				//### Energy Array Reorder
				int K = Count;
				while(K < _->NomLEnergy - 1)
					{
					Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
					K++;
					}

				_->NomLEnergy--;
				}
			}
		}
	else
		{
		if(Q_LEnergy->LEnergy[Count].EnergyLive == 1)
			{
			Q_LEnergy->LEnergy[Count].Alpha = 255;
			Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].Alpha);
			if(Q_LEnergy->LEnergy[Count].Scale < 0.19 && Q_LEnergy->LEnergy[Count].ScaleGrow == 0)
				{
				Q_LEnergy->LEnergy[Count].Scale += Q_LEnergy->LEnergy[Count].ScaleInc;	//0.0008;	//0.008//0.05	************HERE*************
				Q_LEnergy->LEnergy[Count].ScaleInc -= 0.00002;
				Q_LEnergy->LEnergy[Count].SaveScale = Q_LEnergy->LEnergy[Count].Scale;
				}
			else
				{
				Q_LEnergy->LEnergy[Count].Scale = Q_LEnergy->LEnergy[Count].SaveScale + ((((float)rand() / 32767) - 0.5) / 50);
				Q_LEnergy->LEnergy[Count].ScaleGrow = 1;
				}
			}

		if(Q_LEnergy->LEnergy[Count].ScaleXDir == 0)
			{
			Q_LEnergy->LEnergy[Count].ScaleXSquash += ((float)rand() / 32767)*0.1;	//0.05
			if(Q_LEnergy->LEnergy[Count].ScaleXSquash >= 1)
				{
				Q_LEnergy->LEnergy[Count].ScaleXSquash = 1;
				Q_LEnergy->LEnergy[Count].ScaleXDir = 1;
				}
			}

		if(Q_LEnergy->LEnergy[Count].ScaleXDir == 1)
			{
			Q_LEnergy->LEnergy[Count].ScaleXSquash -= ((float)rand() / 32767)*0.1;
			if(Q_LEnergy->LEnergy[Count].ScaleXSquash <= 0.3)
				{
				Q_LEnergy->LEnergy[Count].ScaleXSquash = 0.3;
				Q_LEnergy->LEnergy[Count].ScaleXDir = 0;
				}
			}


		Q_LEnergy->LEnergy[Count].ScaleYSquash = 1 - Q_LEnergy->LEnergy[Count].ScaleXSquash + 0.3;


		if(Q_LEnergy->LEnergy[Count].ScaleZDir == 0)
			{
			Q_LEnergy->LEnergy[Count].ScaleZSquash += ((float)rand() / 32767)*0.1;
			if(Q_LEnergy->LEnergy[Count].ScaleZSquash >= 1)
				{
				Q_LEnergy->LEnergy[Count].ScaleZSquash = 1;
				Q_LEnergy->LEnergy[Count].ScaleZDir = 1;
				}
			}

		if(Q_LEnergy->LEnergy[Count].ScaleZDir == 1)
			{
			Q_LEnergy->LEnergy[Count].ScaleZSquash -= ((float)rand() / 32767)*0.1;
			if(Q_LEnergy->LEnergy[Count].ScaleZSquash <= 0.2)
				{
				Q_LEnergy->LEnergy[Count].ScaleZSquash = 0.12;
				Q_LEnergy->LEnergy[Count].ScaleZDir = 0;
				}
			}
		}


	if(Q_LEnergy->LEnergy[Count].EnergyFire == 1 && Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		TESTShieldFLAG = 0;

		Q_LEnergy->LEnergy[Count].OldLightPos = Q_LEnergy->LEnergy[Count].LightPos;
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].Speed*_->TimeScale, &Q_LEnergy->LEnergy[Count].TraVec, &Q_LEnergy->LEnergy[Count].LightPos);

		if(Q_LEnergy->LEnergy[Count].Speed < 50) Q_LEnergy->LEnergy[Count].Speed *= 2;
		else Q_LEnergy->LEnergy[Count].Speed = 50;

		//##### PLAYER SHIELD COLLIDE TEST
		if((player[g_Player]->Cleric.ShieldAlpha > 0) && (Q_LEnergy->LEnergy[Count].AvID != 250) && (Q_LEnergy->LEnergy[Count].Live == 1) && (player[g_Player]->HB_Energy > 0))
			{
			if(Q_Forge->Forge[Q_LEnergy->LEnergy[Count].AvID].Team != player[g_Player]->Team)
				{
				TESTDist = 100;
				TESTPosS = Q_LEnergy->LEnergy[Count].OldLightPos;
				TESTPosE = Q_LEnergy->LEnergy[Count].LightPos;
				while(TESTDist > 1)
					{
					Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_LEnergy->LEnergy[Count].TraVec, &TESTPosS);

					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

					TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

					if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
						{
						TESTShieldFLAG = 1;

						jet=0;
						while((jet < (((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 145) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
							{
							Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
							Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
							Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
							Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

							Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
							Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
							Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

							Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
							Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.2 + (6 * (Q_LEnergy->LEnergy[Count].EnergyDMG/5000)));
							Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

							Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
							Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
							Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

							Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*15;
							Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*15;
							Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*15;

							Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

							Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

							_->NomPntSprite++;
							jet++;
							}

						player[g_Player]->HB_Energy -= (((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 250) + 35) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));

						Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Live = 10;
						Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Pos = TESTPosS;
						Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Effintensity = Q_LEnergy->LEnergy[Count].EnergyDMG;
						Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Type = 0;
						_->NomNetEffectControl++;

						Qpo->Light_Remove(Q_LEnergy->LEnergy[Count].Light);
						Q_LEnergy->LEnergy[Count].Init = 0;
						Q_LEnergy->LEnergy[Count].Live = 0;
						Q_LEnergy->LEnergy[Count].EnergyLive = 0;
						Q_LEnergy->LEnergy[Count].EnergyFire = 0;
						Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
						Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, 0,0,0);
						//~~##~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Count].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform);

						//### Energy Array Reorder
						int K = Count;
						while(K < _->NomLEnergy - 1)
							{
							Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
							K++;
							}

						_->NomLEnergy--;

						TESTPosS = TESTPosE;
						TESTDist = 0;
						}
					}
				}
			}

		//##### AVATAR SHIELD COLLIDE TEST

		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if(Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0 && (Q_LEnergy->LEnergy[Count].Live == 1) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
					{
					if(Q_LEnergy->LEnergy[Count].AvID == 250)
						{
						if(player[g_Player]->Team != Q_Forge->Forge[SCRAM].Team)
							{
							TESTDist = 100;
							TESTPosS = Q_LEnergy->LEnergy[Count].OldLightPos;
							TESTPosE = Q_LEnergy->LEnergy[Count].LightPos;
							while(TESTDist > 1)
								{
								Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_LEnergy->LEnergy[Count].TraVec, &TESTPosS);

								TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

								TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

								if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
									{
									TESTShieldFLAG = 1;

									jet=0;
									while((jet < (((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 145) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.2 + (6 * (Q_LEnergy->LEnergy[Count].EnergyDMG/5000)));
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*15;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*15;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*15;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = SCRAM;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}

									Q_Forge->Forge[SCRAM].HB_Energy -= (((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 250) + 35) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));

									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Live = 10;
									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Pos = TESTPosS;
									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Effintensity = Q_LEnergy->LEnergy[Count].EnergyDMG;
									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Type = 0;
									_->NomNetEffectControl++;

									Qpo->Light_Remove(Q_LEnergy->LEnergy[Count].Light);
									Q_LEnergy->LEnergy[Count].Init = 0;
									Q_LEnergy->LEnergy[Count].Live = 0;
									Q_LEnergy->LEnergy[Count].EnergyLive = 0;
									Q_LEnergy->LEnergy[Count].EnergyFire = 0;
									Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
									Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, 0,0,0);
									//~~##~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Count].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform);

									//### Energy Array Reorder
									int K = Count;
									while(K < _->NomLEnergy - 1)
										{
										Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
										K++;
										}

									_->NomLEnergy--;

									TESTPosS = TESTPosE;
									TESTDist = 0;
									}
								}
							}
						}
					else
						{
						if(Q_Forge->Forge[Q_LEnergy->LEnergy[Count].AvID].Team != Q_Forge->Forge[SCRAM].Team)
							{
							TESTDist = 100;
							TESTPosS = Q_LEnergy->LEnergy[Count].OldLightPos;
							TESTPosE = Q_LEnergy->LEnergy[Count].LightPos;
							while(TESTDist > 1)
								{
								Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_LEnergy->LEnergy[Count].TraVec, &TESTPosS);

								TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

								TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

								if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
									{
									TESTShieldFLAG = 1;

									jet=0;
									while((jet < (((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 145) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.2 + (6 * (Q_LEnergy->LEnergy[Count].EnergyDMG/5000)));
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*15;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*15;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*15;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = SCRAM;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}

									Q_Forge->Forge[SCRAM].HB_Energy -= ((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 250) + 35;

									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Live = 10;
									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Pos = TESTPosS;
									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Effintensity = Q_LEnergy->LEnergy[Count].EnergyDMG;
									Q_NetEffectControl->NetEffectControl[_->NomNetEffectControl].Type = 0;
									_->NomNetEffectControl++;

									Qpo->Light_Remove(Q_LEnergy->LEnergy[Count].Light);
									Q_LEnergy->LEnergy[Count].Init = 0;
									Q_LEnergy->LEnergy[Count].Live = 0;
									Q_LEnergy->LEnergy[Count].EnergyLive = 0;
									Q_LEnergy->LEnergy[Count].EnergyFire = 0;
									Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
									Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, 0,0,0);
									//~~##~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Count].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform);

									//### Energy Array Reorder
									int K = Count;
									while(K < _->NomLEnergy - 1)
										{
										Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
										K++;
										}

									_->NomLEnergy--;

									TESTPosS = TESTPosE;
									TESTDist = 0;
									}
								}
							}
						}
					}
				}
			SCRAM++;
			}


		//######===-- Q_Object->Object COLLISION DETECTION --===#######
		SCRAM=0;
		while(SCRAM < _->NomQObject)
			{
			if(Q_Object->Object[SCRAM].LIVE == 1)
				{
				//### COLLISION CHECK
				if(Q_Object->Object[SCRAM].StrengthBANK > 0)
					{
					switch(Q_Object->Object[SCRAM].CollisionTYPE)
						{
						case 0:
							{
							TESTDist = 100;
							TESTPosS = Q_LEnergy->LEnergy[Count].OldLightPos;
							TESTPosE = Q_LEnergy->LEnergy[Count].LightPos;
							while(TESTDist > 1)
								{
								Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_LEnergy->LEnergy[Count].TraVec, &TESTPosS);

								TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Object->Object[SCRAM].Pos);

								TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

								if(TESTShieldDIST < Q_Object->Object[SCRAM].Scale)
									{
									//Set Player Enemy Display to correct enemy
									if(Q_LEnergy->LEnergy[Count].AvID == 250)
										{
										player[g_Player]->HB_LastAvatarHitID = (SCRAM + 1) * -1;
										}
									else
										{
										Q_Forge->Forge[Q_LEnergy->LEnergy[Count].AvID].HB_LastAvatarHitID = (SCRAM + 1) * -1;
										}

									//### Block Hit Flash
									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = TESTPosS;	//Point of impact in world space
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_LEnergy->LEnergy[Count].EnergyBall.Xform;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;
									
									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 1000 * (Q_LEnergy->LEnergy[Count].EnergyDMG/5000);				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 200;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 60;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 200;

										//Increment number of MeleeHits
									_->NomMelHit += 1;

									Q_Object->Object[SCRAM].StrengthBANK -= (((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 750) + 100);

									TESTPosS = TESTPosE;
									TESTDist = 0;
									}
								}

							}break;
						}
					}
				}

			SCRAM++;
			}


		//#### REAL WORLD ACTORS AND MODELS COLLISION ####
		if(Qpo->Collision_RayTest_Avatar(
			&playerAV[g_Player]->Mins,
			&playerAV[g_Player]->Maxs,
			&Q_LEnergy->LEnergy[Count].OldLightPos,
			&Q_LEnergy->LEnergy[Count].LightPos,
			//*GE_CONTENTS_SOLID_CLIP,						//GE_CONTENTS_CANNOT_OCCUPY
			/* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
			0xffffffff, NULL, NULL,
			&Q_LEnergy->LEnergy[Count].Collision, Q_LEnergy->LEnergy[Count].AvID) && (Q_LEnergy->LEnergy[Count].Live == 1) && (TESTShieldFLAG == 0))
			{
			//### Reset Collide
			Q_LEnergy->LEnergy[Count].CollideFG = 0;

			//### Check for Team Collisions
			if(Q_LEnergy->LEnergy[Count].Collision.m_HitAvatar)
				{
				if(Q_LEnergy->LEnergy[Count].Collision.m_AvatarID == -1)
					{
					if(Q_LEnergy->LEnergy[Count].Team != player[g_Player]->Team)
						{ Q_LEnergy->LEnergy[Count].CollideFG = 2; }
					}
				else
					{
					if(Q_LEnergy->LEnergy[Count].Team != Q_Forge->Forge[Q_LEnergy->LEnergy[Count].Collision.m_AvatarID].Team)
						{ Q_LEnergy->LEnergy[Count].CollideFG = 2; }
					}
				}
			else
				{
				Q_LEnergy->LEnergy[Count].CollideFG = 1;
				}

			if(Q_LEnergy->LEnergy[Count].CollideFG > 0)
				{
				Qpo->Light_Remove(Q_LEnergy->LEnergy[Count].Light);
				Q_LEnergy->LEnergy[Count].Init = 0;
				Q_LEnergy->LEnergy[Count].Live = 0;
				Q_LEnergy->LEnergy[Count].EnergyLive = 0;
				Q_LEnergy->LEnergy[Count].EnergyFire = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, 0,0,0);
				Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[Count].EnergyBall, 0);

				//### Energy Array Reorder
				int K = Count;
				while(K < _->NomLEnergy - 1)
					{
					Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
					K++;
					}
				_->NomLEnergy--;

				Q_Explosion->Explosion[_->NomExplosions].LargeEnergyAvID = Count;
				Q_Explosion->Explosion[_->NomExplosions].AvID = Q_LEnergy->LEnergy[Count].AvID;
				Q_Explosion->Explosion[_->NomExplosions].CollPlaneNormal = Q_LEnergy->LEnergy[Count].Collision.Plane.Normal;			//Point of impact in world space
				Q_Explosion->Explosion[_->NomExplosions].Pos.acSet(Q_LEnergy->LEnergy[Count].Collision.Impact.m_X, Q_LEnergy->LEnergy[Count].Collision.Impact.m_Y, Q_LEnergy->LEnergy[Count].Collision.Impact.m_Z);
				Q_Explosion->Explosion[_->NomExplosions].Live = 1;
				Q_Explosion->Explosion[_->NomExplosions].Init = 0;
				Q_Explosion->Explosion[_->NomExplosions].BmpCountSP = 6;
				Q_Explosion->Explosion[_->NomExplosions].BmpCount = 0;
				Q_Explosion->Explosion[_->NomExplosions].ExpSize = ((((float)rand() / 32767) * 0.4 ) + 2 ) * (((Q_LEnergy->LEnergy[Count].EnergyRAD/5000)*2.8) + 0.65);	//0.5 -0.65
				Q_Explosion->Explosion[_->NomExplosions].ExpDMG = ((Q_LEnergy->LEnergy[Count].EnergyDMG/5000) * 13) + 3;	//0.5 -0.65
				Q_Explosion->Explosion[_->NomExplosions].Team = Q_LEnergy->LEnergy[Count].Team;
				_->NomExplosions++;

#if 0
				if(Q_LEnergy->LEnergy[Count].CollideFG == 1)
					{
					//#### Add a world decal
					Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].OldLightPos, 300, &Q_LEnergy->LEnergy[Count].TraVec, &Q_LEnergy->LEnergy[Count].LightPos);

					if(Qpo->Collision_RayTest(
						NULL,
						NULL,
						&Q_LEnergy->LEnergy[Count].OldLightPos,
						&Q_LEnergy->LEnergy[Count].LightPos,
						//GE_CONTENTS_SOLID_CLIP,						//GE_CONTENTS_CANNOT_OCCUPY
						/* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
						0xffffffff, NULL, NULL,
						&Q_LEnergy->LEnergy[Count].Collision))
						{
						Q.AddDecal(Q_LEnergy->LEnergy[Count].Collision.Impact, Q_LEnergy->LEnergy[Count].Collision.Plane.Normal, (18 * Q_Explosion->Explosion[_->NomExplosions-1].ExpSize), 1);
						}
					}
#endif
				}
			}
		}

	}//END ServerFrame


void Q_EFFCon::LEnergy_ClientFrame(int Count)
	{
	if(Q_LEnergy->LEnergy[Count].Init == 0 && Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		Q_LEnergy->LEnergy[Count].Init = 1;
		Q_LEnergy->LEnergy[Count].Power = 1;
		Q_LEnergy->LEnergy[Count].EnergyFire = 0;
		Q_LEnergy->LEnergy[Count].Scale = 0.01;
		Q_LEnergy->LEnergy[Count].ScaleInc = 0.005;
		Q_LEnergy->LEnergy[Count].ScaleGrow = 0;
		Q_LEnergy->LEnergy[Count].Speed = 3;
		Q_LEnergy->LEnergy[Count].Alpha = 170;
		Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].Alpha);
		Q_LEnergy->LEnergy[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_LEnergy->LEnergy[Count].Lightcolor.red = 255;
		Q_LEnergy->LEnergy[Count].Lightcolor.green = 255;
		Q_LEnergy->LEnergy[Count].Lightcolor.blue = 190;
		Q_LEnergy->LEnergy[Count].Lightcolor.alpha = 255;


		/*jet = 0;
		while(jet < 20)
			{
			//# Effect Type ## Hadouken Spike ##
			Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 1;

			//## Speed
			Q_HHSpike->HHSpike[_->NomSpikes].Speed = ((((float)rand() / 32767)*50)+50);

			//### Width
			Q_HHSpike->HHSpike[_->NomSpikes].Width = (((float)rand() / 32767)*15);

			//##### Alpha Level
			Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = (((float)rand() / 32767)*255);
			Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

			//###### Center Position
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_LEnergy->LEnergy[Count].LightPos;
			Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

			Q_HHSpike->HHSpike[_->NomSpikes].EnergyID = Count;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].IncX = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncY = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncZ = (((float)rand() / 32767)-0.5)*20;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.x = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.y = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.z = (((float)rand() / 32767)-0.5)*2;

			//######## Set Timers
			Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;

			//######### Make Live
			Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

			_->NomSpikes++;
			if(_->NomSpikes > 499) _->NomSpikes = 0;
			jet++;
			}*/

		/*jet = 0;
		while(jet < 65)
			{
			//# Effect Type ## Hadouken Spike ##
			Q_HHSpike->HHSpike[_->NomSpikes].SelFinger = (float)rand() / 32767;

			if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger < 0.7) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 5;
			if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger > 0.7) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 3;
			if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger > 0.9) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 6;

			//## Speed
			Q_HHSpike->HHSpike[_->NomSpikes].Speed = ((((float)rand() / 32767)*50)+50);

			//### Width
			Q_HHSpike->HHSpike[_->NomSpikes].Width = (((float)rand() / 32767)*15);

			//##### Alpha Level
			Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = (((float)rand() / 32767)*255);
			Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

			//###### Center Position
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_LEnergy->LEnergy[Count].LightPos;
			Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

			Q_HHSpike->HHSpike[_->NomSpikes].EnergyID = Count;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].IncX = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncY = (((float)rand() / 32767)-0.5)*20;
			Q_HHSpike->HHSpike[_->NomSpikes].IncZ = (((float)rand() / 32767)-0.5)*20;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.x = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.y = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].OutVec.z = (((float)rand() / 32767)-0.5)*2;

			//######## Set Timers
			Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;

			//######### Make Live
			Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

			_->NomSpikes++;
			if(_->NomSpikes > 499) _->NomSpikes = 0;
			jet++;
			}*/
		}


	if(Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		if(Q_LEnergy->LEnergy[Count].Power <= 30) Q_Forge->Forge[AIcount].LaserAlpha = (Q_LEnergy->LEnergy[Count].Power * 2) + 15;
		else Q_Forge->Forge[AIcount].LaserAlpha = 75;

		Q_LEnergy->LEnergy[Count].CoronaLENGTH = Qpo->Vec3d_DistanceBetween(&Q_LEnergy->LEnergy[Count].LightPos, &player[g_Player]->ViewXForm.Translation);

		Qpo->Transform_GetIn(&player[g_Player]->ViewXForm, &Q_LEnergy->LEnergy[Count].CoronaVECIN);
		Qpo->Transform_GetUp(&player[g_Player]->ViewXForm, &Q_LEnergy->LEnergy[Count].CoronaVECUP);
		Qpo->Vec3d_CrossProduct(&Q_LEnergy->LEnergy[Count].CoronaVECIN, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT);

		Qpo->Transform_New(&Q_LEnergy->LEnergy[Count].CoronaMATRIX);

		Q_LEnergy->LEnergy[Count].CoronaMATV1.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV1.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV1.z = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV2.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV2.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV2.z = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV3.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV3.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV3.z = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV4.x = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV4.y = 0;
		Q_LEnergy->LEnergy[Count].CoronaMATV4.z = 0;

		Qpo->Light_SetAttr(Q_LEnergy->LEnergy[Count].Light, &Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].Lightcolor, Q_LEnergy->LEnergy[Count].Alpha * 150, true);

		//### Matrix Vert 1
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, Q_LEnergy->LEnergy[Count].CoronaLENGTH/30);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV1, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV1);

		//### Matrix Vert 2
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, PI/2);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV2, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV2);

		//### Matrix Vert 1
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, PI/2);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV3, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV3);

		//### Matrix Vert 1
		Qpo->Transform_RotateY(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, PI/2);

		Qpo->Transform_GetIn(&Q_LEnergy->LEnergy[Count].CoronaMATRIX, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaMATV4, 240, &Q_LEnergy->LEnergy[Count].CoronaMATVECIN, &Q_LEnergy->LEnergy[Count].CoronaMATV4);


		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV1.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT1);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV2.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT2);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV4.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT4);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].CoronaMATV3.x, &Q_LEnergy->LEnergy[Count].CoronaVECLEFT, &Q_LEnergy->LEnergy[Count].CoronaVERT3);

		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT1, Q_LEnergy->LEnergy[Count].CoronaMATV1.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT1);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT2, Q_LEnergy->LEnergy[Count].CoronaMATV2.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT2);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT4, Q_LEnergy->LEnergy[Count].CoronaMATV4.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT4);
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].CoronaVERT3, Q_LEnergy->LEnergy[Count].CoronaMATV3.z, &Q_LEnergy->LEnergy[Count].CoronaVECUP, &Q_LEnergy->LEnergy[Count].CoronaVERT3);


		Q_LEnergy->LEnergy[Count].CoronaLV[0].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].u = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].v = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].x = Q_LEnergy->LEnergy[Count].CoronaVERT1.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].y = Q_LEnergy->LEnergy[Count].CoronaVERT1.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[0].z = Q_LEnergy->LEnergy[Count].CoronaVERT1.z;

		Q_LEnergy->LEnergy[Count].CoronaLV[1].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].u = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].v = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].x = Q_LEnergy->LEnergy[Count].CoronaVERT2.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].y = Q_LEnergy->LEnergy[Count].CoronaVERT2.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[1].z = Q_LEnergy->LEnergy[Count].CoronaVERT2.z;

		Q_LEnergy->LEnergy[Count].CoronaLV[2].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].u = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].v = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].x = Q_LEnergy->LEnergy[Count].CoronaVERT3.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].y = Q_LEnergy->LEnergy[Count].CoronaVERT3.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[2].z = Q_LEnergy->LEnergy[Count].CoronaVERT3.z;

		Q_LEnergy->LEnergy[Count].CoronaLV[3].a = 150;//(player[g_Player]->LaserAlpha*3) - 30;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].u = 1;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].v = 0;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].r = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].g = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].b = 255;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].x = Q_LEnergy->LEnergy[Count].CoronaVERT4.x;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].y = Q_LEnergy->LEnergy[Count].CoronaVERT4.y;
		Q_LEnergy->LEnergy[Count].CoronaLV[3].z = Q_LEnergy->LEnergy[Count].CoronaVERT4.z;

		Qpo->Poly_AddOnce(&Q_LEnergy->LEnergy[Count].CoronaLV[0], 4, Medias->shineE, QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, 1.0f);

		//Qpo->Light_SetAttr(Q_LEnergy->LEnergy[Count].Light, &Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].Lightcolor, Q_LEnergy->LEnergy[Count].Power + (((rand() % Q_LEnergy->LEnergy[Count].Power) / 5) - (Q_LEnergy->LEnergy[Count].Power / 10)), false);
		Qpo->Light_SetAttr(Q_LEnergy->LEnergy[Count].Light, &Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].Lightcolor, 600, false);
	
		//Qpo->Mesh_GetTex(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].BmpCount, Q_LEnergy->LEnergy[Count].Bitmap, &Q_LEnergy->LEnergy[Count].BitmapRed, &Q_LEnergy->LEnergy[Count].BitmapGreen, &Q_LEnergy->LEnergy[Count].BitmapBlue);
		//Qpo->Mesh_GetTex(&Q_LEnergy->LEnergy[Count].EnergyBall, 0, Q_LEnergy->LEnergy[Count].Bitmap, &Q_LEnergy->LEnergy[Count].BitmapRed, &Q_LEnergy->LEnergy[Count].BitmapGreen, &Q_LEnergy->LEnergy[Count].BitmapBlue);

		if(Q_LEnergy->LEnergy[Count].BmpCountSP - 1 > 0) Q_LEnergy->LEnergy[Count].BmpCountSP--;
		else
			{
			Q_LEnergy->LEnergy[Count].BmpCountSP = 6;
			if(Q_LEnergy->LEnergy[Count].BmpCount + 1 < 14) Q_LEnergy->LEnergy[Count].BmpCount++;	//18
			else Q_LEnergy->LEnergy[Count].BmpCount = 0;
			}

		//Qpo->Vec3d_Copy(&Q_LEnergy->LEnergy[Count].LightPos, &Q_LEnergy->LEnergy[Count].EnergyBall.Xform.Translation);
		//Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Count].EnergyBall, Q_LEnergy->LEnergy[Count].Scale,Q_LEnergy->LEnergy[Count].Scale,Q_LEnergy->LEnergy[Count].Scale);

		Qpo->Transform_New_ZRotation(&AIfriendly, 0);
		Qpo->Transform_New_YRotation(&AIfriendly, 0.2);
		}

	if(Q_LEnergy->LEnergy[Count].EnergyFire == 1 && Q_LEnergy->LEnergy[Count].EnergyLive == 1)
		{
		Q_LEnergy->LEnergy[Count].OldLightPos = Q_LEnergy->LEnergy[Count].LightPos;
		Qpo->Vec3d_AddScaled(&Q_LEnergy->LEnergy[Count].LightPos, Q_LEnergy->LEnergy[Count].Speed*_->TimeScale, &Q_LEnergy->LEnergy[Count].TraVec, &Q_LEnergy->LEnergy[Count].LightPos);
		}

	}//END ClientFrame

};