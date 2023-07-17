/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Flame Trails-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "math.h"
#include <stdlib.h>

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-Includes.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-CORE-Avatar.h"

using namespace GVARS;

namespace GVARS
{

	//##### -+ Flame Trails +- #####

void Q_COREFunctions::TrailLineCreate(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir)
{
	if(AvID == 250)
		{
		player[g_Player]->Trail[player[g_Player]->NomTrailL].LINK = player[g_Player]->TrailLINK;
		player[g_Player]->TrailLINK = 0;
		if(player[g_Player]->JinkSPECEFF == 0) player[g_Player]->Trail[player[g_Player]->NomTrailL].LINK = 10;

		player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum = LengNum;

		player[g_Player]->Trail[player[g_Player]->NomTrailL].Type = QPOLY_TYPE_TRI;
		player[g_Player]->Trail[player[g_Player]->NomTrailL].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		player[g_Player]->Trail[player[g_Player]->NomTrailL].Scale = 1.0f;
		player[g_Player]->Trail[player[g_Player]->NomTrailL].Live = 1;

		//### SET BITMAP POINTER
		if(BitmapPTR == 1)
			{
			player[g_Player]->Trail[player[g_Player]->NomTrailL].BitmapPTR = BitmapPTR;
			Red = 255;
			Green = 255;
			Blue = 255;
			}
		else
			{
			player[g_Player]->Trail[player[g_Player]->NomTrailL].BitmapPTR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailTYPE + 2;
			Red = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailRED;
			Green = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailGREEN;
			Blue = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailBLUE;
			}

			//Starting Horizontal Line Vector
		Qpo->Vec3d_Subtract(&PosStart, &player[g_Player]->Trail[player[g_Player]->NomTrailL].LineStartXF.Translation, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecStart);

			//Ending Horizontal Line Vector
		Qpo->Vec3d_Subtract(&PosEnd, &player[g_Player]->Trail[player[g_Player]->NomTrailL].LineEndXF.Translation, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecEnd);
			
			//Left Vertical Line Vector
		Qpo->Vec3d_Subtract(&player[g_Player]->Trail[player[g_Player]->NomTrailL].LineEndXF.Translation, &player[g_Player]->Trail[player[g_Player]->NomTrailL].LineStartXF.Translation, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft);

			//Right Vertical Line Vector
		Qpo->Vec3d_Subtract(&PosEnd, &PosStart, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight);

		player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthL = Qpo->Vec3d_Length(&player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft);
		player[g_Player]->Trail[player[g_Player]->NomTrailL].Width = player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthL / player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum;
		Qpo->Vec3d_Normalize(&player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft);
		Qpo->Vec3d_Scale(&player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft, player[g_Player]->Trail[player[g_Player]->NomTrailL].Width, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft);

		player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthR = Qpo->Vec3d_Length(&player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight);
		player[g_Player]->Trail[player[g_Player]->NomTrailL].Width = player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthR / player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum;
		Qpo->Vec3d_Normalize(&player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight);
		Qpo->Vec3d_Scale(&player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight, player[g_Player]->Trail[player[g_Player]->NomTrailL].Width, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight);

		Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE1", &BoneMat);
		player[g_Player]->Trail[player[g_Player]->NomTrailL].AvatarCENTER = BoneMat.Translation;
		player[g_Player]->Trail[player[g_Player]->NomTrailL].AvatarCENTER.y += ((((float)rand() / 32767)-0.5)*50);

		if(player[g_Player]->ATTCoronaMattDIR == 0)
			{
			player[g_Player]->ATTCoronaMatt++;
			if(player[g_Player]->ATTCoronaMatt > 3)
				{
				player[g_Player]->ATTCoronaMatt = 3;
				player[g_Player]->ATTCoronaMattDIR = 1;
				}
			}
		else
			{
			player[g_Player]->ATTCoronaMatt--;
			if(player[g_Player]->ATTCoronaMatt < 0)
				{
				player[g_Player]->ATTCoronaMatt = 0;
				player[g_Player]->ATTCoronaMattDIR = 0;
				}
			}

		//player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNumSTR = player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum;
		//if(player[g_Player]->JinkSpecialON == 1) player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum = player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum * 2;


		//##### Start Player Effects

		//#### Initialise Particles ####//
		/*jet=0;
		while(jet < (10*_->TimeScale) && player[g_Player]->JinkSpecialON > 0 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))	//3
			{
			Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
			Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
			Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;		//0.025f//0.002f
			Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 3;

			//Q_PntSprite->PntSprite[_->NomPntSprite].IR = 226;
			//Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
			//Q_PntSprite->PntSprite[_->NomPntSprite].IB = 170;

			Q_PntSprite->PntSprite[_->NomPntSprite].IR = Red;
			Q_PntSprite->PntSprite[_->NomPntSprite].IG = Green;
			Q_PntSprite->PntSprite[_->NomPntSprite].IB = Blue;

			Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
			Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos = PosStart;

			//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
			//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
			//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

			Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

			_->NomPntSprite++;
			jet++;
			}*/

		if(player[g_Player]->JinkSpecialON >= 0.5)
			{


			//if(player[g_Player]->JSSpikes == 0 && player[g_Player]->HitLethal == 1 && player[g_Player]->JinkSpecialON != 4)
			//	{
			//	player[g_Player]->JSSpikes = 1;

				/*jet = 0;
				while(jet < 150)
					{
					//# Effect Type ## Hadouken Spike ##
					Q_HHSpike->HHSpike[_->NomSpikes].SelFinger = (float)rand() / 32767;

					if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger < 0.85) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 5;
					if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger > 0.85) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 3;
					if(Q_HHSpike->HHSpike[_->NomSpikes].SelFinger > 0.92) Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 6;

					//## Speed
					Q_HHSpike->HHSpike[_->NomSpikes].Speed = ((((float)rand() / 32767)*50)+50);

					//### Width
					Q_HHSpike->HHSpike[_->NomSpikes].Width = (((float)rand() / 32767)*15);

					//##### Alpha Level
					Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = (((float)rand() / 32767)*255);
					Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

					//###### Center Position
					Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = player[g_Player]->AttPos.Translation;
					Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

					Q_HHSpike->HHSpike[_->NomSpikes].EnergyID = aero;

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
			//	}



			//CLOUD9
			/*jet=0;
			while(jet < 100)
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 9;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = player[g_Player]->AttPos.Translation;

				Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*25;
				Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*25;
				Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*25;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*60)+50;
				//Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015) + 0.003;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015) + 0.001;

				Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec = player[g_Player]->Trail[player[g_Player]->NomTrailL].VecStart;

				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*2;
				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.09) + 0.03;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}*/

			/*helly = 0;
			while(helly < 1 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE2", &BoneMat);

				//#### Initialise One Particle ####//
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.1f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].R = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].G = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].B = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = ((((float)rand() / 32767)*150)+30);
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->AttPos.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->AttPos.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].Direction = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				helly++;
				}*/

			/*jet=0;
			while(jet < (6*_->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))		//4	//12
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 6;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = Red;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Green;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = Blue;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = PosStart;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}*/

			/*jet = 0;
			while(jet < 5*_->TimeScale)	//1	//6
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 4;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = player[g_Player]->AttPos.Translation;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*90)+80;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.08)+0.02;

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x = (((float)rand() / 32767)-0.5) *4;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y = (((float)rand() / 32767)-0.5);
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z = (((float)rand() / 32767)-0.5) * 4;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767))+0.3)*5;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}*/


			//#### Alter Attack Light
			player[g_Player]->ATTLightColor.red = Red;
			player[g_Player]->ATTLightColor.green = Green;
			player[g_Player]->ATTLightColor.blue = Blue;
			player[g_Player]->ATTLightColor.alpha = 255;
			if(player[g_Player]->ATTLightON == 1) Qpo->Light_SetAttr(player[g_Player]->ATTLight, &player[g_Player]->AttPos.Translation, &player[g_Player]->ATTLightColor, 200, true);

			player[g_Player]->ATTCoronaLvert.x = player[g_Player]->AttPos.Translation.x;
			player[g_Player]->ATTCoronaLvert.y = player[g_Player]->AttPos.Translation.y;
			player[g_Player]->ATTCoronaLvert.z = player[g_Player]->AttPos.Translation.z;
			player[g_Player]->ATTCoronaLvert.r = 255;
			player[g_Player]->ATTCoronaLvert.g = 255;
			player[g_Player]->ATTCoronaLvert.b = 255;
			player[g_Player]->ATTCoronaLvert.a = 20;	//30

			//if(player[g_Player]->JinkSpecialON != 4) Qpo->Poly_AddOnce(&player[g_Player]->ATTCoronaLvert, 1, Medias->SparkCorona[player[g_Player]->ATTCoronaMatt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.25);


			player[g_Player]->ATTCoronaLvert.x = player[g_Player]->AttPos.Translation.x;
			player[g_Player]->ATTCoronaLvert.y = player[g_Player]->AttPos.Translation.y;
			player[g_Player]->ATTCoronaLvert.z = player[g_Player]->AttPos.Translation.z;
			player[g_Player]->ATTCoronaLvert.r = 255;
			player[g_Player]->ATTCoronaLvert.g = 255;
			player[g_Player]->ATTCoronaLvert.b = 255;
			player[g_Player]->ATTCoronaLvert.a = 25;	//10	//16

			//if(player[g_Player]->JinkSpecialON != 4) Qpo->Poly_AddOnce(&player[g_Player]->ATTCoronaLvert, 1, Medias->shineE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, 0.8 + (player[g_Player]->ATTCoronaMatt / 10));
			}
		else
			{
			/*jet=0;
			while(jet < (10*_->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))	//6
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 5;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = Red;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Green;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = Blue;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = PosStart;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}*/


			//CLOUD9
			/*jet=0;
			while(jet < 40)
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 9;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = player[g_Player]->AttPos.Translation;

				Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*25;
				Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*25;
				Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*25;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*60)+50;
				//Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015) + 0.003;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015) + 0.001;

				Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec = player[g_Player]->Trail[player[g_Player]->NomTrailL].VecStart;

				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*2;
				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.15) + 0.05;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}*/


			//#### Alter Attack Light
			player[g_Player]->ATTLightColor.red = Red;
			player[g_Player]->ATTLightColor.green = Green;
			player[g_Player]->ATTLightColor.blue = Blue;
			player[g_Player]->ATTLightColor.alpha = 255;
			if(player[g_Player]->ATTLightON == 1)Qpo->Light_SetAttr(player[g_Player]->ATTLight, &player[g_Player]->AttPos.Translation, &player[g_Player]->ATTLightColor, 100, true);

			player[g_Player]->ATTCoronaLvert.x = player[g_Player]->AttPos.Translation.x;
			player[g_Player]->ATTCoronaLvert.y = player[g_Player]->AttPos.Translation.y;
			player[g_Player]->ATTCoronaLvert.z = player[g_Player]->AttPos.Translation.z;
			player[g_Player]->ATTCoronaLvert.r = Red;
			player[g_Player]->ATTCoronaLvert.g = Green;
			player[g_Player]->ATTCoronaLvert.b = Blue;
			player[g_Player]->ATTCoronaLvert.a = 15;	//20

			//if(player[g_Player]->JinkSpecialON != 3) Qpo->Poly_AddOnce (World, &player[g_Player]->ATTCoronaLvert, 1, Medias->SparkCorona[player[g_Player]->ATTCoronaMatt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.09);
			}

		//#### End Effects

		helly = 0;
		while(helly < player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum)
			{
			if(helly == 0)
				{
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1 = PosStart;
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2 = player[g_Player]->Trail[player[g_Player]->NomTrailL].LineStartXF.Translation;

				Qpo->Vec3d_Add(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3);
				Qpo->Vec3d_Add(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4);

				player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert3 = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3;
				player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert4 = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4;
				}
			else
				{
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1 = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4;
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2 = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3;

				Qpo->Vec3d_Add(&player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert3, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecLeft, &player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert3);
				Qpo->Vec3d_Add(&player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert4, &player[g_Player]->Trail[player[g_Player]->NomTrailL].VecRight, &player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert4);

				player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3 = player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert3;
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4 = player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert4;
				}

			//Calculate Push Vector
			Qpo->Vec3d_Subtract(&player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert4, &player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert3, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec);
			Qpo->Vec3d_Subtract(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVecS);
			Qpo->Vec3d_Normalize(&player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVecS);


			if(player[g_Player]->JinkSPECEFF == 1 && player[g_Player]->HitLethal == 1 && 0)
				{
				SCRAM = 0;
				while(SCRAM < (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 20) * _->TimeScale)
					{
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos = player[g_Player]->Trail[player[g_Player]->NomTrailL].ORIGVert4;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec = player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.x += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.y += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.z += ((((float)rand() / 32767)-0.5)*0.25);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffRED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeRED;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffGREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeGREEN;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffBLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeBLUE;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeALPHA;

					//Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = 90;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Timer = 0;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TimerGoal = ((((float)rand() / 32767)*0.05*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10)+1)));

					Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos, 1, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos);
					
					/*Q_PowerFlash->PowerFlash[_->NomPowerFlash].Speed = (85*(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10)) - (20*(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10) * SCRAM);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Gravity = (0.1*(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10)) - (0.02*(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10) * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 75) - SCRAM));

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Size = (100*(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10)) - (18*(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10) * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 75) - SCRAM));*/

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Speed = 13*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 40)+3);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Gravity = 0.185;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Size = 20*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 40))+3;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Bounce = 0;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].MatCNT = 0;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Live = 1;

					_->NomPowerFlash++;
					if(_->NomPowerFlash > 1999) _->NomPowerFlash = 0;
					SCRAM++;
					}

				SCRAM = 0;
				while(SCRAM < (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 20) * _->TimeScale)
					{
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec = player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVecS;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.x += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.y += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.z += ((((float)rand() / 32767)-0.5)*0.25);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffRED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeRED;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffGREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeGREEN;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffBLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeBLUE;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.SpikeALPHA;

					//Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = 90;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Timer = 0;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TimerGoal = ((((float)rand() / 32767)*0.05*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 10)+1)));

					Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos, 1, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos);
					
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Speed = 13*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 40)+3);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Gravity = 0.185;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Size = 20*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower / 40))+3;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Bounce = 0;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].MatCNT = 0;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Live = 1;

					_->NomPowerFlash++;
					if(_->NomPowerFlash > 1999) _->NomPowerFlash = 0;
					SCRAM++;
					}
				}


			//#####  TRAIL ARC PREDICTION  #####

			//### Calculate Push out distance for Inner Edge
			
			if(helly < (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum / 2))
				{
				//#### Scale PushScale
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3) / 30;

				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = ((helly + 1) / (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum / 2)) * (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthL * 2);
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = sqrt(player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale) * player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3, player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3);
				if(helly == 0) Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1, player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVecS, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1);

				//#### Scale PushScale
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4) / 30;

				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = ((helly + 1) / (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum / 2)) * (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthR * 2);
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = sqrt(player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale) * player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4, player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4);
				if(helly == 0) Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2, player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVecS, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2);
				}
			else
				{
				//#### Scale PushScale
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3) / 30;

				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = ((5 - (helly - 5)) / (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum / 2)) * (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthL * 2);
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = sqrt(player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale) * player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3, player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3);

				//#### Scale PushScale
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor = Qpo->Vec3d_DistanceBetween(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4) / 30;

				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = ((5 - (helly - 5)) / (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengNum / 2)) * (player[g_Player]->Trail[player[g_Player]->NomTrailL].LengthR * 2);
				player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale = sqrt(player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale) * player[g_Player]->Trail[player[g_Player]->NomTrailL].PSfactor;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4, player[g_Player]->Trail[player[g_Player]->NomTrailL].PushScale, &player[g_Player]->Trail[player[g_Player]->NomTrailL].PushVec, &player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4);
				}


			player[g_Player]->Trail[player[g_Player]->NomTrailL].SectionLIVE[helly] = 1;

			if(helly == 0)
				{
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Ut = 0.1;
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Ub = 0;
				}
			else
				{
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Ut += 0.1;
				player[g_Player]->Trail[player[g_Player]->NomTrailL].Ub += 0.1;
				if(player[g_Player]->Trail[player[g_Player]->NomTrailL].Ut > 1)
					{
					player[g_Player]->Trail[player[g_Player]->NomTrailL].Ut = 0.1;
					player[g_Player]->Trail[player[g_Player]->NomTrailL].Ub = 0;
					}
				}

			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].a = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailALPHA;		//200
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].b = Blue;	//156
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].g = Green;	//195
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].r = Red;		//228
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].u = 1;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].v = player[g_Player]->Trail[player[g_Player]->NomTrailL].Ub;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].x = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1.x;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].y = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1.y;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][0].z = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert1.z;


			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].a = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailALPHA;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].b = Blue;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].g = Green;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].r = Red;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].u = 0;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].v = player[g_Player]->Trail[player[g_Player]->NomTrailL].Ub;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].x = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2.x;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].y = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2.y;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][1].z = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert2.z;


			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].a = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailALPHA;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].b = Blue;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].g = Green;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].r = Red;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].u = 0;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].v = player[g_Player]->Trail[player[g_Player]->NomTrailL].Ut;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].x = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3.x;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].y = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3.y;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][2].z = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert3.z;


			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].a = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.TrailALPHA;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].b = Blue;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].g = Green;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].r = Red;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].u = 1;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].v = player[g_Player]->Trail[player[g_Player]->NomTrailL].Ut;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].x = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4.x;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].y = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4.y;
			player[g_Player]->Trail[player[g_Player]->NomTrailL].Lvert[helly][3].z = player[g_Player]->Trail[player[g_Player]->NomTrailL].Vert4.z;

			helly++;
			}

		player[g_Player]->NomTrailL++;
		if(player[g_Player]->NomTrailL > 99) player[g_Player]->NomTrailL = 0;
		}
	else
		{
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LINK = Q_Forge->Forge[AvID].TrailLINK;
		Q_Forge->Forge[AvID].TrailLINK = 0;
		if(Q_Forge->Forge[AvID].JinkSPECEFF == 0) Q_Forge->Forge[AvID].Trail[player[g_Player]->NomTrailL].LINK = 10;

		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum = LengNum;

		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Type = QPOLY_TYPE_TRI;
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].BitmapPTR = BitmapPTR;
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Scale = 1.0f;
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Live = 1;

		//### SET BITMAP POINTER
		if(BitmapPTR == 1)
			{
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].BitmapPTR = BitmapPTR;
			Red = 255;
			Green = 255;
			Blue = 255;
			}
		else
			{
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].BitmapPTR = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailTYPE + 2;
			Red = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailRED;
			Green = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailGREEN;
			Blue = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailBLUE;
			}

			//Starting Horizontal Line Vector
		Qpo->Vec3d_Subtract(&PosStart, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LineStartXF.Translation, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecStart);

			//Ending Horizontal Line Vector
		Qpo->Vec3d_Subtract(&PosEnd, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LineEndXF.Translation, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecEnd);
			
			//Left Vertical Line Vector
		Qpo->Vec3d_Subtract(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LineEndXF.Translation, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LineStartXF.Translation, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft);

			//Right Vertical Line Vector
		Qpo->Vec3d_Subtract(&PosEnd, &PosStart, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight);

		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthL = Qpo->Vec3d_Length(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft);
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Width = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthL / Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum;
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft);
		Qpo->Vec3d_Scale(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Width, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft);

		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthR = Qpo->Vec3d_Length(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight);
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Width = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthR / Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum;
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight);
		Qpo->Vec3d_Scale(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Width, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight);

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AvID].AV, "BIP01 SPINE1", &BoneMat);
		Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].AvatarCENTER = BoneMat.Translation;
		//player[g_Player]->Trail[player[g_Player]->NomTrailL].AvatarCENTER.y += 55;

		//#### Initialise Particles ####//
		/*jet=0;
		while(jet < (10*_->TimeScale) && Q_Forge->Forge[AvID].JinkSpecialON > 0 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
			{
			Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
			Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
			Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;		//0.025f//0.002f
			Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 3;

			Q_PntSprite->PntSprite[_->NomPntSprite].IR = Red;
			Q_PntSprite->PntSprite[_->NomPntSprite].IG = Green;
			Q_PntSprite->PntSprite[_->NomPntSprite].IB = Blue;

			Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
			Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos = PosStart;

			//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
			//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
			//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

			Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

			_->NomPntSprite++;
			jet++;
			}*/

		if(Q_Forge->Forge[AvID].JinkSpecialON >= 0.5)
			{
			/*if(Q_Forge->Forge[AvID].JSSpikes == 0 && Q_Forge->Forge[AvID].HitLethal == 1)
				{
				Q_Forge->Forge[AvID].JSSpikes = 1;

				jet = 0;
				while(jet < 20)
					{
					//# Effect Type ## Hadouken Spike ##
					Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 4;

					//## Speed
					Q_HHSpike->HHSpike[_->NomSpikes].Speed = ((((float)rand() / 32767)*50)+50);

					//### Width
					Q_HHSpike->HHSpike[_->NomSpikes].Width = (((float)rand() / 32767)*15);

					//##### Alpha Level
					Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = (((float)rand() / 32767)*255);
					Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

					//###### Center Position
					Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = Q_Forge->Forge[AvID].AttPos.Translation;
					Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

					Q_HHSpike->HHSpike[_->NomSpikes].EnergyID = aero;

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

					//######### Set Identity
					Q_HHSpike->HHSpike[_->NomSpikes].AvID = AvID;

					//######### Make Live
					Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

					_->NomSpikes++;
					if(_->NomSpikes > 499) _->NomSpikes = 0;
					jet++;
					}
				}*/


			//CLOUD9
			/*jet=0;
			while(jet < 100)
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 9;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Forge->Forge[AvID].AttPos.Translation;

				Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*25;
				Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*25;
				Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*25;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*60)+50;
				//Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015) + 0.003;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015) + 0.001;

				Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec = Q_Forge->Forge[AvID].Trail[player[g_Player]->NomTrailL].VecStart;

				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*2;
				//Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.09) + 0.03;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}*/


			/*jet=0;
			while(jet < (8*_->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))		//4	//12
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 6;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = Red;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Green;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = Blue;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = PosStart;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}*/

			/*jet = 0;
			while(jet < 6*_->TimeScale)	//1	//6
				{
				Q_Cloud->Cloud[_->NomCloud].CloudType = 4;

				Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Forge->Forge[AvID].AttPos.Translation;

				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*90)+80;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.08)+0.02;

				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x = (((float)rand() / 32767)-0.5) *4;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y = (((float)rand() / 32767)-0.5);
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z = (((float)rand() / 32767)-0.5) * 4;

				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767))+0.3)*5;

				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}*/


			//#### Alter Attack Light
			Q_Forge->Forge[AvID].ATTLightColor.red = Red;
			Q_Forge->Forge[AvID].ATTLightColor.green = Green;
			Q_Forge->Forge[AvID].ATTLightColor.blue = Blue;
			Q_Forge->Forge[AvID].ATTLightColor.alpha = 255;
			if(Q_Forge->Forge[AIcount].ATTLightON == 1) Qpo->Light_SetAttr(Q_Forge->Forge[AvID].ATTLight, &Q_Forge->Forge[AvID].AttPos.Translation, &Q_Forge->Forge[AvID].ATTLightColor, 200, true);

			Q_Forge->Forge[AvID].ATTCoronaLvert.x = Q_Forge->Forge[AvID].AttPos.Translation.x;
			Q_Forge->Forge[AvID].ATTCoronaLvert.y = Q_Forge->Forge[AvID].AttPos.Translation.y;
			Q_Forge->Forge[AvID].ATTCoronaLvert.z = Q_Forge->Forge[AvID].AttPos.Translation.z;
			Q_Forge->Forge[AvID].ATTCoronaLvert.r = 255;
			Q_Forge->Forge[AvID].ATTCoronaLvert.g = 255;
			Q_Forge->Forge[AvID].ATTCoronaLvert.b = 255;
			Q_Forge->Forge[AvID].ATTCoronaLvert.a = 20;	//30

			//Qpo->Poly_AddOnce (World, &Q_Forge->Forge[AvID].ATTCoronaLvert, 1, Medias->SparkCorona[Q_Forge->Forge[AvID].ATTCoronaMatt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.25);


			Q_Forge->Forge[AvID].ATTCoronaLvert.x = Q_Forge->Forge[AvID].AttPos.Translation.x;
			Q_Forge->Forge[AvID].ATTCoronaLvert.y = Q_Forge->Forge[AvID].AttPos.Translation.y;
			Q_Forge->Forge[AvID].ATTCoronaLvert.z = Q_Forge->Forge[AvID].AttPos.Translation.z;
			Q_Forge->Forge[AvID].ATTCoronaLvert.r = 255;
			Q_Forge->Forge[AvID].ATTCoronaLvert.g = 255;
			Q_Forge->Forge[AvID].ATTCoronaLvert.b = 255;
			Q_Forge->Forge[AvID].ATTCoronaLvert.a = 10;	//16

			//Qpo->Poly_AddOnce (World, &Q_Forge->Forge[AvID].ATTCoronaLvert, 1, Medias->shineE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, 0.8 + (Q_Forge->Forge[AvID].ATTCoronaMatt / 10));
			}
		else
			{
			/*jet=0;
			while(jet < (10*_->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))	//6
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.03f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 5;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = Red;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Green;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = Blue;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = PosStart;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*12;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*12;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}*/

			//#### Alter Attack Light
			Q_Forge->Forge[AvID].ATTLightColor.red = Red;
			Q_Forge->Forge[AvID].ATTLightColor.green = Green;
			Q_Forge->Forge[AvID].ATTLightColor.blue = Blue;
			Q_Forge->Forge[AvID].ATTLightColor.alpha = 255;
			if(Q_Forge->Forge[AIcount].ATTLightON == 1) Qpo->Light_SetAttr(Q_Forge->Forge[AvID].ATTLight, &Q_Forge->Forge[AvID].AttPos.Translation, &Q_Forge->Forge[AvID].ATTLightColor, 100, true);

			Q_Forge->Forge[AvID].ATTCoronaLvert.x = Q_Forge->Forge[AvID].AttPos.Translation.x;
			Q_Forge->Forge[AvID].ATTCoronaLvert.y = Q_Forge->Forge[AvID].AttPos.Translation.y;
			Q_Forge->Forge[AvID].ATTCoronaLvert.z = Q_Forge->Forge[AvID].AttPos.Translation.z;
			Q_Forge->Forge[AvID].ATTCoronaLvert.r = Red;
			Q_Forge->Forge[AvID].ATTCoronaLvert.g = Green;
			Q_Forge->Forge[AvID].ATTCoronaLvert.b = Blue;
			Q_Forge->Forge[AvID].ATTCoronaLvert.a = 15;	//20

			//Qpo->Poly_AddOnce (World, &Q_Forge->Forge[AvID].ATTCoronaLvert, 1, Medias->SparkCorona[Q_Forge->Forge[AvID].ATTCoronaMatt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.09);
			}


		helly = 0;
		while(helly < Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum)
			{
			if(helly == 0)
				{
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1 = PosStart;
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LineStartXF.Translation;

				Qpo->Vec3d_Add(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3);
				Qpo->Vec3d_Add(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4);

				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert3 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3;
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert4 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4;
				}
			else
				{
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4;
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3;

				Qpo->Vec3d_Add(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert3, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecLeft, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert3);
				Qpo->Vec3d_Add(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert4, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].VecRight, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert4);

				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert3;
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4 = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert4;
				}

			//Calculate Push Vector
			Qpo->Vec3d_Subtract(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert4, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert3, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec);
			Qpo->Vec3d_Subtract(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVecS);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVecS);


			if(Q_Forge->Forge[AvID].JinkSPECEFF == 1 && Q_Forge->Forge[AvID].HitLethal == 1 && 0)
				{
				SCRAM = 0;
				while(SCRAM < (Q_Forge->Forge[AvID].CharDATA.BodySKILL.RELRawPower / 20) * _->TimeScale)
					{
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].ORIGVert4;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.x += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.y += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.z += ((((float)rand() / 32767)-0.5)*0.25);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffRED = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeRED;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffGREEN = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeGREEN;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffBLUE = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeBLUE;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeALPHA;

					//Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = 90;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Timer = 0;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TimerGoal = ((((float)rand() / 32767)*0.05*((Q_Forge->Forge[AvID].CharDATA.BodySKILL.RELRawPower / 10)+1)));

					Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos, 1, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos);
					
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Speed = 13*((Q_Forge->Forge[AIcount].CharDATA.BodySKILL.RELRawPower / 40)+3);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Gravity = 0.185;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Size = 20*((Q_Forge->Forge[AIcount].CharDATA.BodySKILL.RELRawPower / 40))+3;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Bounce = 0;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].MatCNT = 0;

					//Q_PowerFlash->PowerFlash[_->NomPowerFlash].SmokeTrail = 0;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Live = 1;

					_->NomPowerFlash++;
					if(_->NomPowerFlash > 1999) _->NomPowerFlash = 0;
					SCRAM++;
					}

				SCRAM = 0;
				while(SCRAM < (Q_Forge->Forge[AvID].CharDATA.BodySKILL.RELRawPower / 20) * _->TimeScale)
					{
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVecS;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.x += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.y += ((((float)rand() / 32767)-0.5)*0.25);
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec.z += ((((float)rand() / 32767)-0.5)*0.25);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffRED = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeRED;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffGREEN = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeGREEN;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].EffBLUE = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeBLUE;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.SpikeALPHA;

					//Q_PowerFlash->PowerFlash[_->NomPowerFlash].AlpFade = 90;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Timer = 0;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].TimerGoal = ((((float)rand() / 32767)*0.05*((Q_Forge->Forge[AvID].CharDATA.BodySKILL.RELRawPower / 10)+1)));

					Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos, 1, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].TraVec, &Q_PowerFlash->PowerFlash[_->NomPowerFlash].Pos);
					
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Speed = 13*((Q_Forge->Forge[AIcount].CharDATA.BodySKILL.RELRawPower / 40)+3);

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Gravity = 0.1;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Size = 20*((Q_Forge->Forge[AIcount].CharDATA.BodySKILL.RELRawPower / 40))+3;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Bounce = 0;

					Q_PowerFlash->PowerFlash[_->NomPowerFlash].MatCNT = 0;

					//Q_PowerFlash->PowerFlash[_->NomPowerFlash].SmokeTrail = 0;
					Q_PowerFlash->PowerFlash[_->NomPowerFlash].Live = 1;

					_->NomPowerFlash++;
					if(_->NomPowerFlash > 1999) _->NomPowerFlash = 0;
					SCRAM++;
					}
				}


			//#####  TRAIL ARC PREDICTION  #####

			//### Calculate Push out distance for Inner Edge
			
			if(helly < (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum / 2))
				{
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = ((helly + 1) / (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum / 2)) * (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthL * 2);
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = sqrt(Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale) * 1;

				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3);
				if(helly == 0) Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVecS, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1);

				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = ((helly + 1) / (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum / 2)) * (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthR * 2);
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = sqrt(Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale) * 1;

				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4);
				if(helly == 0) Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVecS, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2);
				}
			else
				{
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = ((5 - (helly - 5)) / (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum / 2)) * (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthL * 2);
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = sqrt(Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale) * 1;

				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3);

				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = ((5 - (helly - 5)) / (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengNum / 2)) * (Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].LengthR * 2);
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale = sqrt(Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale) * 1;

				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4, Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushScale, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].PushVec, &Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4);
				}


			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].SectionLIVE[helly] = 1;


			if(helly == 0)
				{
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ut = 0.1;
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ub = 0;
				}
			else
				{
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ut += 0.1;
				Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ub += 0.1;
				if(Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ut > 1)
					{
					Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ut = 0.1;
					Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Ub = 0;
					}
				}

			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].a = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailALPHA;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].b = Blue;		//156
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].g = Green;		//195
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].r = Red;		//228
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].u = 1;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].v = 0;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].x = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1.x;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].y = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1.y;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][0].z = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert1.z;


			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].a = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailALPHA;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].b = Blue;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].g = Green;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].r = Red;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].u = 0;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].v = 0;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].x = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2.x;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].y = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2.y;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][1].z = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert2.z;


			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].a = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailALPHA;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].b = Blue;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].g = Green;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].r = Red;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].u = 0;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].v = 1;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].x = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3.x;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].y = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3.y;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][2].z = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert3.z;


			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].a = Q_Forge->Forge[AvID].CharDATA.AngelEFFECTS.TrailALPHA;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].b = Blue;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].g = Green;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].r = Red;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].u = 1;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].v = 1;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].x = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4.x;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].y = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4.y;
			Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Lvert[helly][3].z = Q_Forge->Forge[AvID].Trail[Q_Forge->Forge[AvID].NomTrailL].Vert4.z;

			helly++;
			}

		Q_Forge->Forge[AvID].NomTrailL++;
		if(Q_Forge->Forge[AvID].NomTrailL > 99) Q_Forge->Forge[AvID].NomTrailL = 0;
		}
}

};