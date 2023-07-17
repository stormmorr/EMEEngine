/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Player WindWake-

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

using namespace GVARS;

namespace GVARS
{

//#####- PLAYER WIND WAKE -#####

void Q_EFFCon::WindWake_PlayerFrame(void)
	{
	if(player[g_Player]->WindWake == 1)
		{
		Q_WindWake->WindWake[250].MAINALPHA += 15*_->TimeScale;
		if((Q_WindWake->WindWake[250].MAINALPHA > Q_WindWake->WindWake[250].AlphaMAX) && Q_WindWake->WindWake[250].AlphaMAX != 0) Q_WindWake->WindWake[250].MAINALPHA = Q_WindWake->WindWake[250].AlphaMAX;
		}
	else
		{
		Q_WindWake->WindWake[250].MAINALPHA -= 6*_->TimeScale;	//15
		if(Q_WindWake->WindWake[250].MAINALPHA < 0) Q_WindWake->WindWake[250].MAINALPHA = 0;
		}


	if(Q_WindWake->WindWake[250].MAINALPHA > 0)	//ORIG 75
		{								//ORIG 100
		//#### Default Values for standard JUMP
		Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
		Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 47.5;	//72.5
		Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 143;
		Q_WindWake->WindWake[250].AlphaMAX = 45;

		//### Change Scale and center point depending on attack type
		if(player[g_Player]->Aposestate == 24)	//Jump Kick
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 45;	//65 //82.5
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 125;
			Q_WindWake->WindWake[250].AlphaMAX = 35;
			}

		if(player[g_Player]->Aposestate == 22)	//Leap Spin Kick
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 57.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 160;
			Q_WindWake->WindWake[250].AlphaMAX = 40;
			}

		if(player[g_Player]->Aposestate == 76) // JSRush UP
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 62.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 115;
			Q_WindWake->WindWake[250].AlphaMAX = 50;
			}

		if(player[g_Player]->Aposestate == 74)	//JSRush Punch
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 57.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 140;
			Q_WindWake->WindWake[250].AlphaMAX = 40;
			}

		if(player[g_Player]->Aposestate == 73)	//JSRUSH
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 57.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 150;
			Q_WindWake->WindWake[250].AlphaMAX = 25;	//90
			}

		if(player[g_Player]->Aposestate == 61)	//Twist Kick
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 57.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 150;
			Q_WindWake->WindWake[250].AlphaMAX = 40;
			}

		if(player[g_Player]->Aposestate == 65)	//Rush Elbow
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 32.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 105;
			Q_WindWake->WindWake[250].AlphaMAX = 80;
			}

		if(player[g_Player]->Aposestate == 84)	//Overhead Pinwheel
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 42.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 115;
			Q_WindWake->WindWake[250].AlphaMAX = 65;
			}

		if(player[g_Player]->Aposestate == 81)	//Spin Out Left
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 57.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 140;
			Q_WindWake->WindWake[250].AlphaMAX = 40;
			}

		if(player[g_Player]->Mposestate == 26)	//Roll Forward
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 27.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 100;
			Q_WindWake->WindWake[250].AlphaMAX = 30;
			}

		if(player[g_Player]->Mposestate == 28)	//Roll Left
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 27.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 100;
			Q_WindWake->WindWake[250].AlphaMAX = 25;
			}

		if(player[g_Player]->Mposestate == 29)	//Roll Right
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 27.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 100;
			Q_WindWake->WindWake[250].AlphaMAX = 25;
			}

		if(player[g_Player]->Mposestate == 8)	//BackFlip
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 35;	//82.5
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[250].AlphaMAX = 45;
			}

		if(player[g_Player]->Mposestate == 23)	//Cartwheel Left
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 32.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[250].AlphaMAX = 30;
			}

		if(player[g_Player]->Mposestate == 24)	//Cartwheel Right
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 32.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[250].AlphaMAX = 30;
			}

		if(player[g_Player]->Mposestate == 15)	//Air Rush Forward
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 32.5;
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 125;
			Q_WindWake->WindWake[250].AlphaMAX = 65;
			}

		if(player[g_Player]->Vehicle.JINKrush == 1)	//Vehicle JSRush
			{
			Q_WindWake->WindWake[250].Pos = playerAV[g_Player]->Xform.Translation;
			Q_WindWake->WindWake[250].Pos.y += (10 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 35;	//82.5
			Q_WindWake->WindWake[250].Scale = (25 * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[250].AlphaMAX = 45;
			}

		//#### Revert to WindWake Memory
		if(player[g_Player]->WindWake == 0)
			{
			Q_WindWake->WindWake[250].Pos = Q_WindWake->WindWake[250].MeMPos;	//82.5
			Q_WindWake->WindWake[250].Scale = Q_WindWake->WindWake[250].MeMScale;
			Q_WindWake->WindWake[250].AlphaMAX = Q_WindWake->WindWake[250].MeMAlphaMAX;
			}

		if((player[g_Player]->INvectorAPC.x == 0 && player[g_Player]->INvectorAPC.y == 0 && player[g_Player]->INvectorAPC.z == 0) || (player[g_Player]->INvectorAPC.x < 0.025 && player[g_Player]->INvectorAPC.y < 0.025 && player[g_Player]->INvectorAPC.z < 0.025)) player[g_Player]->INvectorAPC = Q_WindWake->WindWake[250].MeMINvectorAPC;


		//##### Calculate Direction Vectors
		Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
		Qpo->Transform_RotateVector(&RotateMatrix, &player[g_Player]->INvectorAPC, &player[g_Player]->LEFTvectorAPC);
		player[g_Player]->LEFTvectorAPC.y = 0;
		Qpo->Vec3d_Normalize(&player[g_Player]->LEFTvectorAPC);

		Qpo->Vec3d_CrossProduct(&player[g_Player]->LEFTvectorAPC, &player[g_Player]->INvectorAPC, &player[g_Player]->UPvectorAPC);
		Qpo->Vec3d_Normalize(&player[g_Player]->UPvectorAPC);

		if(player[g_Player]->INvectorAPC.y != 1)
			{
			Q_WindWake->WindWake[250].VecIn = player[g_Player]->INvectorAPC;
			Q_WindWake->WindWake[250].VecUp = player[g_Player]->UPvectorAPC;
			Q_WindWake->WindWake[250].VecLeft = player[g_Player]->LEFTvectorAPC;
			}
		else
			{
			Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &Q_WindWake->WindWake[250].VecUp);
			Qpo->Vec3d_Inverse(&Q_WindWake->WindWake[250].VecUp);
			Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &Q_WindWake->WindWake[250].VecLeft);
			Q_WindWake->WindWake[250].VecIn.x = 0;
			Q_WindWake->WindWake[250].VecIn.y = 1;
			Q_WindWake->WindWake[250].VecIn.z = 0;
			}

		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, 45, &Q_WindWake->WindWake[250].VecIn, &Q_WindWake->WindWake[250].Pos);
		Q_WindWake->WindWake[250].STRPos = Q_WindWake->WindWake[250].Pos;

		Q_WindWake->WindWake[250].Type = QPOLY_TYPE_TRI;
		Q_WindWake->WindWake[250].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_WindWake->WindWake[250].ScaleBIT = 1.0f;
		//END INIT

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkTYPE == 0)
			{
			Q_WindWake->WindWake[250].MaterialCNT--;
			if(Q_WindWake->WindWake[250].MaterialCNT < 124) Q_WindWake->WindWake[250].MaterialCNT = 136;
			if(Q_WindWake->WindWake[250].MaterialCNT > 136) Q_WindWake->WindWake[250].MaterialCNT = 124;
			}

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkTYPE == 1)
			{
			Q_WindWake->WindWake[250].MaterialCNT--;
			if(Q_WindWake->WindWake[250].MaterialCNT < 82) Q_WindWake->WindWake[250].MaterialCNT = 96;
			if(Q_WindWake->WindWake[250].MaterialCNT > 96) Q_WindWake->WindWake[250].MaterialCNT = 82;
			}

		//####### Store WindWake Memory
		if(player[g_Player]->WindWake == 1)
			{
			Q_WindWake->WindWake[250].MeMPos = Q_WindWake->WindWake[250].Pos;
			Q_WindWake->WindWake[250].MeMScale = Q_WindWake->WindWake[250].Scale;
			Q_WindWake->WindWake[250].MeMAlphaMAX = Q_WindWake->WindWake[250].AlphaMAX;

			Q_WindWake->WindWake[250].MeMINvectorAPC = player[g_Player]->INvectorAPC;

			Q_WindWake->WindWake[250].MeMJinkSpecialON = player[g_Player]->JinkSpecialON;
			}


			//### FRONT VERT
		Q_WindWake->WindWake[250].VertFNT = Q_WindWake->WindWake[250].STRPos;


			//### Shift Back for second ring					//15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/20, &Q_WindWake->WindWake[250].VecIn, &Q_WindWake->WindWake[250].Pos);


			//##### RING TWO
					//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/8, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM1);

					//TOP VERT15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM15);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM15, -Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM15);

					//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM2);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM2, -Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM2);

					//TOP VERT25
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM25);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM25, -Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM25);

					//TOP VERT3
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/8, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM3);

					//TOP VERT35
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM35);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM35, -Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM35);

					//TOP VERT4
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM4);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM4, -Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM4);

					//TOP VERT45
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM45);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM45, -Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM45);

					//TOP VERT5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/8, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM5);

					//TOP VERT55
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM55);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM55, Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM55);

					//TOP VERT6
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM6);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM6, Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM6);

					//TOP VERT65
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM65);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM65, Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM65);

					//TOP VERT7
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/8, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM7);

					//TOP VERT75
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM75);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM75, Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM75);

					//TOP VERT8
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM8);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM8, Q_WindWake->WindWake[250].Scale/11.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM8);

					//TOP VERT85
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/9, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertM85);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertM85, Q_WindWake->WindWake[250].Scale/14.75, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertM85);



			//### Shift Back for first ring					//4   11
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/5, &Q_WindWake->WindWake[250].VecIn, &Q_WindWake->WindWake[250].Pos);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].STRPos, -Q_WindWake->WindWake[250].Scale/5, &Q_WindWake->WindWake[250].VecIn, &Q_WindWake->WindWake[250].STRPos);
		
		
			//##### RING ONE
					//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT1);

					//TOP VERT15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT15);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT15, -Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT15);

					//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT2);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT2, -Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT2);

					//TOP VERT25
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT25);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT25, -Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT25);

					//TOP VERT3
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT3);

					//TOP VERT35
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT35);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT35, -Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT35);

					//TOP VERT4
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT4);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT4, -Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT4);

					//TOP VERT45
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT45);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT45, -Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT45);

					//TOP VERT5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT5);

					//TOP VERT55
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT55);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT55, Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT55);

					//TOP VERT6
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT6);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT6, Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT6);

					//TOP VERT65
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT65);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT65, Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT65);

					//TOP VERT7
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT7);

					//TOP VERT75
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT75);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT75, Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT75);

					//TOP VERT8
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT8);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT8, Q_WindWake->WindWake[250].Scale/4, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT8);

					//TOP VERT85
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3.15, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertT85);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertT85, Q_WindWake->WindWake[250].Scale/11, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertT85);


			//### Shift Back for second ring				// 3 <- V GOOD         3.5	4.5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3.35, &Q_WindWake->WindWake[250].VecIn, &Q_WindWake->WindWake[250].Pos);


			//##### RING TWO
					//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/2.7, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB1);

					//TOP VERT15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB15);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB15, -Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB15);

					//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB2);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB2, -Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB2);

					//TOP VERT25
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB25);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB25, -Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB25);

					//TOP VERT3
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/2.7, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB3);

					//TOP VERT35
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB35);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB35, -Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB35);

					//TOP VERT4
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB4);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB4, -Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB4);

					//TOP VERT45
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB45);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB45, -Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB45);

					//TOP VERT5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/2.7, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB5);

					//TOP VERT55
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB55);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB55, Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB55);

					//TOP VERT6
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB6);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB6, Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB6);

					//TOP VERT65
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, -Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB65);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB65, Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB65);

					//TOP VERT7
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/2.7, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB7);

					//TOP VERT75
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB75);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB75, Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB75);

					//TOP VERT8
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB8);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB8, Q_WindWake->WindWake[250].Scale/3.5, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB8);

					//TOP VERT85
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].Pos, Q_WindWake->WindWake[250].Scale/3, &Q_WindWake->WindWake[250].VecUp, &Q_WindWake->WindWake[250].VertB85);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[250].VertB85, Q_WindWake->WindWake[250].Scale/8.2, &Q_WindWake->WindWake[250].VecLeft, &Q_WindWake->WindWake[250].VertB85);


				int a=0;
				while( a <= 47 )
					{
					int b=0;
					while( b <= 3 )
						{
						if(player[g_Player]->WindWake == 1)
							{
							if(player[g_Player]->JinkSpecialON < 1 || 1)
								{
								Q_WindWake->WindWake[250].Lvert[a][b].a = Q_WindWake->WindWake[250].MAINALPHA;
								Q_WindWake->WindWake[250].Lvert[a][b].b = 255;
								Q_WindWake->WindWake[250].Lvert[a][b].g = 255;
								Q_WindWake->WindWake[250].Lvert[a][b].r = 255;
								}
							else
								{
								Q_WindWake->WindWake[250].Lvert[a][b].a = Q_WindWake->WindWake[250].MAINALPHA;
								Q_WindWake->WindWake[250].Lvert[a][b].b = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkBLUE;
								Q_WindWake->WindWake[250].Lvert[a][b].g = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkGREEN;
								Q_WindWake->WindWake[250].Lvert[a][b].r = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkRED;
								}
							}
						else
							{
							if(Q_WindWake->WindWake[250].MeMJinkSpecialON < 1 || 1)
								{
								Q_WindWake->WindWake[250].Lvert[a][b].a = Q_WindWake->WindWake[250].MAINALPHA;
								Q_WindWake->WindWake[250].Lvert[a][b].b = 255;
								Q_WindWake->WindWake[250].Lvert[a][b].g = 255;
								Q_WindWake->WindWake[250].Lvert[a][b].r = 255;
								}
							else
								{
								Q_WindWake->WindWake[250].Lvert[a][b].a = Q_WindWake->WindWake[250].MAINALPHA;
								Q_WindWake->WindWake[250].Lvert[a][b].b = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkBLUE;
								Q_WindWake->WindWake[250].Lvert[a][b].g = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkGREEN;
								Q_WindWake->WindWake[250].Lvert[a][b].r = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkRED;
								}
							}
						b++;
						}
					a++;
					}


					//##### - FRONT CUP

					Q_WindWake->WindWake[250].Lvert[0][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[0][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[0][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[0][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[0][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[0][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[0][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[0][1].x = Q_WindWake->WindWake[250].VertM15.x;
					Q_WindWake->WindWake[250].Lvert[0][1].y = Q_WindWake->WindWake[250].VertM15.y;
					Q_WindWake->WindWake[250].Lvert[0][1].z = Q_WindWake->WindWake[250].VertM15.z;

					
					Q_WindWake->WindWake[250].Lvert[0][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[0][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[0][2].x = Q_WindWake->WindWake[250].VertM1.x;
					Q_WindWake->WindWake[250].Lvert[0][2].y = Q_WindWake->WindWake[250].VertM1.y;
					Q_WindWake->WindWake[250].Lvert[0][2].z = Q_WindWake->WindWake[250].VertM1.z;


					Q_WindWake->WindWake[250].Lvert[1][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[1][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[1][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[1][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[1][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[1][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[1][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[1][1].x = Q_WindWake->WindWake[250].VertM25.x;
					Q_WindWake->WindWake[250].Lvert[1][1].y = Q_WindWake->WindWake[250].VertM25.y;
					Q_WindWake->WindWake[250].Lvert[1][1].z = Q_WindWake->WindWake[250].VertM25.z;

							
					Q_WindWake->WindWake[250].Lvert[1][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[1][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[1][2].x = Q_WindWake->WindWake[250].VertM2.x;
					Q_WindWake->WindWake[250].Lvert[1][2].y = Q_WindWake->WindWake[250].VertM2.y;
					Q_WindWake->WindWake[250].Lvert[1][2].z = Q_WindWake->WindWake[250].VertM2.z;


					Q_WindWake->WindWake[250].Lvert[2][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[2][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[2][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[2][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[2][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[2][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[2][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[2][1].x = Q_WindWake->WindWake[250].VertM35.x;
					Q_WindWake->WindWake[250].Lvert[2][1].y = Q_WindWake->WindWake[250].VertM35.y;
					Q_WindWake->WindWake[250].Lvert[2][1].z = Q_WindWake->WindWake[250].VertM35.z;

							
					Q_WindWake->WindWake[250].Lvert[2][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[2][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[2][2].x = Q_WindWake->WindWake[250].VertM3.x;
					Q_WindWake->WindWake[250].Lvert[2][2].y = Q_WindWake->WindWake[250].VertM3.y;
					Q_WindWake->WindWake[250].Lvert[2][2].z = Q_WindWake->WindWake[250].VertM3.z;


					Q_WindWake->WindWake[250].Lvert[3][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[3][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[3][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[3][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[3][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[3][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[3][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[3][1].x = Q_WindWake->WindWake[250].VertM45.x;
					Q_WindWake->WindWake[250].Lvert[3][1].y = Q_WindWake->WindWake[250].VertM45.y;
					Q_WindWake->WindWake[250].Lvert[3][1].z = Q_WindWake->WindWake[250].VertM45.z;

							
					Q_WindWake->WindWake[250].Lvert[3][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[3][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[3][2].x = Q_WindWake->WindWake[250].VertM4.x;
					Q_WindWake->WindWake[250].Lvert[3][2].y = Q_WindWake->WindWake[250].VertM4.y;
					Q_WindWake->WindWake[250].Lvert[3][2].z = Q_WindWake->WindWake[250].VertM4.z;


					Q_WindWake->WindWake[250].Lvert[4][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[4][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[4][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[4][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[4][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[4][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[4][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[4][1].x = Q_WindWake->WindWake[250].VertM55.x;
					Q_WindWake->WindWake[250].Lvert[4][1].y = Q_WindWake->WindWake[250].VertM55.y;
					Q_WindWake->WindWake[250].Lvert[4][1].z = Q_WindWake->WindWake[250].VertM55.z;

							
					Q_WindWake->WindWake[250].Lvert[4][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[4][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[4][2].x = Q_WindWake->WindWake[250].VertM5.x;
					Q_WindWake->WindWake[250].Lvert[4][2].y = Q_WindWake->WindWake[250].VertM5.y;
					Q_WindWake->WindWake[250].Lvert[4][2].z = Q_WindWake->WindWake[250].VertM5.z;


					Q_WindWake->WindWake[250].Lvert[5][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[5][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[5][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[5][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[5][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[5][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[5][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[5][1].x = Q_WindWake->WindWake[250].VertM65.x;
					Q_WindWake->WindWake[250].Lvert[5][1].y = Q_WindWake->WindWake[250].VertM65.y;
					Q_WindWake->WindWake[250].Lvert[5][1].z = Q_WindWake->WindWake[250].VertM65.z;

							
					Q_WindWake->WindWake[250].Lvert[5][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[5][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[5][2].x = Q_WindWake->WindWake[250].VertM6.x;
					Q_WindWake->WindWake[250].Lvert[5][2].y = Q_WindWake->WindWake[250].VertM6.y;
					Q_WindWake->WindWake[250].Lvert[5][2].z = Q_WindWake->WindWake[250].VertM6.z;


					Q_WindWake->WindWake[250].Lvert[6][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[6][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[6][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[6][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[6][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[6][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[6][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[6][1].x = Q_WindWake->WindWake[250].VertM75.x;
					Q_WindWake->WindWake[250].Lvert[6][1].y = Q_WindWake->WindWake[250].VertM75.y;
					Q_WindWake->WindWake[250].Lvert[6][1].z = Q_WindWake->WindWake[250].VertM75.z;

							
					Q_WindWake->WindWake[250].Lvert[6][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[6][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[6][2].x = Q_WindWake->WindWake[250].VertM7.x;
					Q_WindWake->WindWake[250].Lvert[6][2].y = Q_WindWake->WindWake[250].VertM7.y;
					Q_WindWake->WindWake[250].Lvert[6][2].z = Q_WindWake->WindWake[250].VertM7.z;


					Q_WindWake->WindWake[250].Lvert[7][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[7][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[7][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[7][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[7][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[7][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[7][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[7][1].x = Q_WindWake->WindWake[250].VertM85.x;
					Q_WindWake->WindWake[250].Lvert[7][1].y = Q_WindWake->WindWake[250].VertM85.y;
					Q_WindWake->WindWake[250].Lvert[7][1].z = Q_WindWake->WindWake[250].VertM85.z;

							
					Q_WindWake->WindWake[250].Lvert[7][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[7][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[7][2].x = Q_WindWake->WindWake[250].VertM8.x;
					Q_WindWake->WindWake[250].Lvert[7][2].y = Q_WindWake->WindWake[250].VertM8.y;
					Q_WindWake->WindWake[250].Lvert[7][2].z = Q_WindWake->WindWake[250].VertM8.z;


					Q_WindWake->WindWake[250].Lvert[8][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[8][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[8][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[8][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[8][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[8][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[8][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[8][1].x = Q_WindWake->WindWake[250].VertM2.x;
					Q_WindWake->WindWake[250].Lvert[8][1].y = Q_WindWake->WindWake[250].VertM2.y;
					Q_WindWake->WindWake[250].Lvert[8][1].z = Q_WindWake->WindWake[250].VertM2.z;

					
					Q_WindWake->WindWake[250].Lvert[8][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[8][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[8][2].x = Q_WindWake->WindWake[250].VertM15.x;
					Q_WindWake->WindWake[250].Lvert[8][2].y = Q_WindWake->WindWake[250].VertM15.y;
					Q_WindWake->WindWake[250].Lvert[8][2].z = Q_WindWake->WindWake[250].VertM15.z;


					Q_WindWake->WindWake[250].Lvert[9][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[9][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[9][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[9][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[9][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[9][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[9][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[9][1].x = Q_WindWake->WindWake[250].VertM3.x;
					Q_WindWake->WindWake[250].Lvert[9][1].y = Q_WindWake->WindWake[250].VertM3.y;
					Q_WindWake->WindWake[250].Lvert[9][1].z = Q_WindWake->WindWake[250].VertM3.z;

							
					Q_WindWake->WindWake[250].Lvert[9][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[9][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[9][2].x = Q_WindWake->WindWake[250].VertM25.x;
					Q_WindWake->WindWake[250].Lvert[9][2].y = Q_WindWake->WindWake[250].VertM25.y;
					Q_WindWake->WindWake[250].Lvert[9][2].z = Q_WindWake->WindWake[250].VertM25.z;


					Q_WindWake->WindWake[250].Lvert[10][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[10][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[10][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[10][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[10][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[10][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[10][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[10][1].x = Q_WindWake->WindWake[250].VertM4.x;
					Q_WindWake->WindWake[250].Lvert[10][1].y = Q_WindWake->WindWake[250].VertM4.y;
					Q_WindWake->WindWake[250].Lvert[10][1].z = Q_WindWake->WindWake[250].VertM4.z;

							
					Q_WindWake->WindWake[250].Lvert[10][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[10][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[10][2].x = Q_WindWake->WindWake[250].VertM35.x;
					Q_WindWake->WindWake[250].Lvert[10][2].y = Q_WindWake->WindWake[250].VertM35.y;
					Q_WindWake->WindWake[250].Lvert[10][2].z = Q_WindWake->WindWake[250].VertM35.z;


					Q_WindWake->WindWake[250].Lvert[11][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[11][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[11][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[11][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[11][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[11][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[11][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[11][1].x = Q_WindWake->WindWake[250].VertM5.x;
					Q_WindWake->WindWake[250].Lvert[11][1].y = Q_WindWake->WindWake[250].VertM5.y;
					Q_WindWake->WindWake[250].Lvert[11][1].z = Q_WindWake->WindWake[250].VertM5.z;

							
					Q_WindWake->WindWake[250].Lvert[11][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[11][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[11][2].x = Q_WindWake->WindWake[250].VertM45.x;
					Q_WindWake->WindWake[250].Lvert[11][2].y = Q_WindWake->WindWake[250].VertM45.y;
					Q_WindWake->WindWake[250].Lvert[11][2].z = Q_WindWake->WindWake[250].VertM45.z;


					Q_WindWake->WindWake[250].Lvert[12][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[12][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[12][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[12][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[12][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[12][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[12][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[12][1].x = Q_WindWake->WindWake[250].VertM6.x;
					Q_WindWake->WindWake[250].Lvert[12][1].y = Q_WindWake->WindWake[250].VertM6.y;
					Q_WindWake->WindWake[250].Lvert[12][1].z = Q_WindWake->WindWake[250].VertM6.z;

							
					Q_WindWake->WindWake[250].Lvert[12][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[12][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[12][2].x = Q_WindWake->WindWake[250].VertM55.x;
					Q_WindWake->WindWake[250].Lvert[12][2].y = Q_WindWake->WindWake[250].VertM55.y;
					Q_WindWake->WindWake[250].Lvert[12][2].z = Q_WindWake->WindWake[250].VertM55.z;


					Q_WindWake->WindWake[250].Lvert[13][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[13][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[13][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[13][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[13][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[13][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[13][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[13][1].x = Q_WindWake->WindWake[250].VertM7.x;
					Q_WindWake->WindWake[250].Lvert[13][1].y = Q_WindWake->WindWake[250].VertM7.y;
					Q_WindWake->WindWake[250].Lvert[13][1].z = Q_WindWake->WindWake[250].VertM7.z;

							
					Q_WindWake->WindWake[250].Lvert[13][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[13][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[13][2].x = Q_WindWake->WindWake[250].VertM65.x;
					Q_WindWake->WindWake[250].Lvert[13][2].y = Q_WindWake->WindWake[250].VertM65.y;
					Q_WindWake->WindWake[250].Lvert[13][2].z = Q_WindWake->WindWake[250].VertM65.z;


					Q_WindWake->WindWake[250].Lvert[14][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[14][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[14][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[14][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[14][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[14][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[14][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[14][1].x = Q_WindWake->WindWake[250].VertM8.x;
					Q_WindWake->WindWake[250].Lvert[14][1].y = Q_WindWake->WindWake[250].VertM8.y;
					Q_WindWake->WindWake[250].Lvert[14][1].z = Q_WindWake->WindWake[250].VertM8.z;

							
					Q_WindWake->WindWake[250].Lvert[14][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[14][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[14][2].x = Q_WindWake->WindWake[250].VertM75.x;
					Q_WindWake->WindWake[250].Lvert[14][2].y = Q_WindWake->WindWake[250].VertM75.y;
					Q_WindWake->WindWake[250].Lvert[14][2].z = Q_WindWake->WindWake[250].VertM75.z;


					Q_WindWake->WindWake[250].Lvert[15][0].u = 0.5;
					Q_WindWake->WindWake[250].Lvert[15][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[15][0].x = Q_WindWake->WindWake[250].VertFNT.x;
					Q_WindWake->WindWake[250].Lvert[15][0].y = Q_WindWake->WindWake[250].VertFNT.y;
					Q_WindWake->WindWake[250].Lvert[15][0].z = Q_WindWake->WindWake[250].VertFNT.z;

							
					Q_WindWake->WindWake[250].Lvert[15][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[15][1].v = 1;
					Q_WindWake->WindWake[250].Lvert[15][1].x = Q_WindWake->WindWake[250].VertM1.x;
					Q_WindWake->WindWake[250].Lvert[15][1].y = Q_WindWake->WindWake[250].VertM1.y;
					Q_WindWake->WindWake[250].Lvert[15][1].z = Q_WindWake->WindWake[250].VertM1.z;

							
					Q_WindWake->WindWake[250].Lvert[15][2].u = 0;
					Q_WindWake->WindWake[250].Lvert[15][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[15][2].x = Q_WindWake->WindWake[250].VertM85.x;
					Q_WindWake->WindWake[250].Lvert[15][2].y = Q_WindWake->WindWake[250].VertM85.y;
					Q_WindWake->WindWake[250].Lvert[15][2].z = Q_WindWake->WindWake[250].VertM85.z;


					//##### - SOLID RING ONE

					Q_WindWake->WindWake[250].Lvert[16][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[16][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[16][0].x = Q_WindWake->WindWake[250].VertM1.x;
					Q_WindWake->WindWake[250].Lvert[16][0].y = Q_WindWake->WindWake[250].VertM1.y;
					Q_WindWake->WindWake[250].Lvert[16][0].z = Q_WindWake->WindWake[250].VertM1.z;

					
					Q_WindWake->WindWake[250].Lvert[16][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[16][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[16][1].x = Q_WindWake->WindWake[250].VertM15.x;
					Q_WindWake->WindWake[250].Lvert[16][1].y = Q_WindWake->WindWake[250].VertM15.y;
					Q_WindWake->WindWake[250].Lvert[16][1].z = Q_WindWake->WindWake[250].VertM15.z;

							
					Q_WindWake->WindWake[250].Lvert[16][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[16][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[16][2].x = Q_WindWake->WindWake[250].VertT15.x;
					Q_WindWake->WindWake[250].Lvert[16][2].y = Q_WindWake->WindWake[250].VertT15.y;
					Q_WindWake->WindWake[250].Lvert[16][2].z = Q_WindWake->WindWake[250].VertT15.z;


					Q_WindWake->WindWake[250].Lvert[16][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[16][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[16][3].x = Q_WindWake->WindWake[250].VertT1.x;
					Q_WindWake->WindWake[250].Lvert[16][3].y = Q_WindWake->WindWake[250].VertT1.y;
					Q_WindWake->WindWake[250].Lvert[16][3].z = Q_WindWake->WindWake[250].VertT1.z;


					Q_WindWake->WindWake[250].Lvert[17][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[17][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[17][0].x = Q_WindWake->WindWake[250].VertM15.x;
					Q_WindWake->WindWake[250].Lvert[17][0].y = Q_WindWake->WindWake[250].VertM15.y;
					Q_WindWake->WindWake[250].Lvert[17][0].z = Q_WindWake->WindWake[250].VertM15.z;

							
					Q_WindWake->WindWake[250].Lvert[17][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[17][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[17][1].x = Q_WindWake->WindWake[250].VertM2.x;
					Q_WindWake->WindWake[250].Lvert[17][1].y = Q_WindWake->WindWake[250].VertM2.y;
					Q_WindWake->WindWake[250].Lvert[17][1].z = Q_WindWake->WindWake[250].VertM2.z;

							
					Q_WindWake->WindWake[250].Lvert[17][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[17][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[17][2].x = Q_WindWake->WindWake[250].VertT2.x;
					Q_WindWake->WindWake[250].Lvert[17][2].y = Q_WindWake->WindWake[250].VertT2.y;
					Q_WindWake->WindWake[250].Lvert[17][2].z = Q_WindWake->WindWake[250].VertT2.z;


					Q_WindWake->WindWake[250].Lvert[17][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[17][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[17][3].x = Q_WindWake->WindWake[250].VertT15.x;
					Q_WindWake->WindWake[250].Lvert[17][3].y = Q_WindWake->WindWake[250].VertT15.y;
					Q_WindWake->WindWake[250].Lvert[17][3].z = Q_WindWake->WindWake[250].VertT15.z;



					Q_WindWake->WindWake[250].Lvert[18][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[18][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[18][0].x = Q_WindWake->WindWake[250].VertM2.x;
					Q_WindWake->WindWake[250].Lvert[18][0].y = Q_WindWake->WindWake[250].VertM2.y;
					Q_WindWake->WindWake[250].Lvert[18][0].z = Q_WindWake->WindWake[250].VertM2.z;

							
					Q_WindWake->WindWake[250].Lvert[18][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[18][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[18][1].x = Q_WindWake->WindWake[250].VertM25.x;
					Q_WindWake->WindWake[250].Lvert[18][1].y = Q_WindWake->WindWake[250].VertM25.y;
					Q_WindWake->WindWake[250].Lvert[18][1].z = Q_WindWake->WindWake[250].VertM25.z;

							
					Q_WindWake->WindWake[250].Lvert[18][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[18][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[18][2].x = Q_WindWake->WindWake[250].VertT25.x;
					Q_WindWake->WindWake[250].Lvert[18][2].y = Q_WindWake->WindWake[250].VertT25.y;
					Q_WindWake->WindWake[250].Lvert[18][2].z = Q_WindWake->WindWake[250].VertT25.z;


					Q_WindWake->WindWake[250].Lvert[18][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[18][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[18][3].x = Q_WindWake->WindWake[250].VertT2.x;
					Q_WindWake->WindWake[250].Lvert[18][3].y = Q_WindWake->WindWake[250].VertT2.y;
					Q_WindWake->WindWake[250].Lvert[18][3].z = Q_WindWake->WindWake[250].VertT2.z;



					Q_WindWake->WindWake[250].Lvert[19][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[19][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[19][0].x = Q_WindWake->WindWake[250].VertM25.x;
					Q_WindWake->WindWake[250].Lvert[19][0].y = Q_WindWake->WindWake[250].VertM25.y;
					Q_WindWake->WindWake[250].Lvert[19][0].z = Q_WindWake->WindWake[250].VertM25.z;

							
					Q_WindWake->WindWake[250].Lvert[19][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[19][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[19][1].x = Q_WindWake->WindWake[250].VertM3.x;
					Q_WindWake->WindWake[250].Lvert[19][1].y = Q_WindWake->WindWake[250].VertM3.y;
					Q_WindWake->WindWake[250].Lvert[19][1].z = Q_WindWake->WindWake[250].VertM3.z;

							
					Q_WindWake->WindWake[250].Lvert[19][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[19][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[19][2].x = Q_WindWake->WindWake[250].VertT3.x;
					Q_WindWake->WindWake[250].Lvert[19][2].y = Q_WindWake->WindWake[250].VertT3.y;
					Q_WindWake->WindWake[250].Lvert[19][2].z = Q_WindWake->WindWake[250].VertT3.z;


					Q_WindWake->WindWake[250].Lvert[19][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[19][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[19][3].x = Q_WindWake->WindWake[250].VertT25.x;
					Q_WindWake->WindWake[250].Lvert[19][3].y = Q_WindWake->WindWake[250].VertT25.y;
					Q_WindWake->WindWake[250].Lvert[19][3].z = Q_WindWake->WindWake[250].VertT25.z;


					Q_WindWake->WindWake[250].Lvert[20][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[20][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[20][0].x = Q_WindWake->WindWake[250].VertM3.x;
					Q_WindWake->WindWake[250].Lvert[20][0].y = Q_WindWake->WindWake[250].VertM3.y;
					Q_WindWake->WindWake[250].Lvert[20][0].z = Q_WindWake->WindWake[250].VertM3.z;

							
					Q_WindWake->WindWake[250].Lvert[20][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[20][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[20][1].x = Q_WindWake->WindWake[250].VertM35.x;
					Q_WindWake->WindWake[250].Lvert[20][1].y = Q_WindWake->WindWake[250].VertM35.y;
					Q_WindWake->WindWake[250].Lvert[20][1].z = Q_WindWake->WindWake[250].VertM35.z;

							
					Q_WindWake->WindWake[250].Lvert[20][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[20][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[20][2].x = Q_WindWake->WindWake[250].VertT35.x;
					Q_WindWake->WindWake[250].Lvert[20][2].y = Q_WindWake->WindWake[250].VertT35.y;
					Q_WindWake->WindWake[250].Lvert[20][2].z = Q_WindWake->WindWake[250].VertT35.z;


					Q_WindWake->WindWake[250].Lvert[20][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[20][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[20][3].x = Q_WindWake->WindWake[250].VertT3.x;
					Q_WindWake->WindWake[250].Lvert[20][3].y = Q_WindWake->WindWake[250].VertT3.y;
					Q_WindWake->WindWake[250].Lvert[20][3].z = Q_WindWake->WindWake[250].VertT3.z;


					Q_WindWake->WindWake[250].Lvert[21][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[21][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[21][0].x = Q_WindWake->WindWake[250].VertM35.x;
					Q_WindWake->WindWake[250].Lvert[21][0].y = Q_WindWake->WindWake[250].VertM35.y;
					Q_WindWake->WindWake[250].Lvert[21][0].z = Q_WindWake->WindWake[250].VertM35.z;

							
					Q_WindWake->WindWake[250].Lvert[21][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[21][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[21][1].x = Q_WindWake->WindWake[250].VertM4.x;
					Q_WindWake->WindWake[250].Lvert[21][1].y = Q_WindWake->WindWake[250].VertM4.y;
					Q_WindWake->WindWake[250].Lvert[21][1].z = Q_WindWake->WindWake[250].VertM4.z;

							
					Q_WindWake->WindWake[250].Lvert[21][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[21][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[21][2].x = Q_WindWake->WindWake[250].VertT4.x;
					Q_WindWake->WindWake[250].Lvert[21][2].y = Q_WindWake->WindWake[250].VertT4.y;
					Q_WindWake->WindWake[250].Lvert[21][2].z = Q_WindWake->WindWake[250].VertT4.z;


					Q_WindWake->WindWake[250].Lvert[21][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[21][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[21][3].x = Q_WindWake->WindWake[250].VertT35.x;
					Q_WindWake->WindWake[250].Lvert[21][3].y = Q_WindWake->WindWake[250].VertT35.y;
					Q_WindWake->WindWake[250].Lvert[21][3].z = Q_WindWake->WindWake[250].VertT35.z;


					Q_WindWake->WindWake[250].Lvert[22][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[22][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[22][0].x = Q_WindWake->WindWake[250].VertM4.x;
					Q_WindWake->WindWake[250].Lvert[22][0].y = Q_WindWake->WindWake[250].VertM4.y;
					Q_WindWake->WindWake[250].Lvert[22][0].z = Q_WindWake->WindWake[250].VertM4.z;

							
					Q_WindWake->WindWake[250].Lvert[22][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[22][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[22][1].x = Q_WindWake->WindWake[250].VertM45.x;
					Q_WindWake->WindWake[250].Lvert[22][1].y = Q_WindWake->WindWake[250].VertM45.y;
					Q_WindWake->WindWake[250].Lvert[22][1].z = Q_WindWake->WindWake[250].VertM45.z;

							
					Q_WindWake->WindWake[250].Lvert[22][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[22][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[22][2].x = Q_WindWake->WindWake[250].VertT45.x;
					Q_WindWake->WindWake[250].Lvert[22][2].y = Q_WindWake->WindWake[250].VertT45.y;
					Q_WindWake->WindWake[250].Lvert[22][2].z = Q_WindWake->WindWake[250].VertT45.z;


					Q_WindWake->WindWake[250].Lvert[22][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[22][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[22][3].x = Q_WindWake->WindWake[250].VertT4.x;
					Q_WindWake->WindWake[250].Lvert[22][3].y = Q_WindWake->WindWake[250].VertT4.y;
					Q_WindWake->WindWake[250].Lvert[22][3].z = Q_WindWake->WindWake[250].VertT4.z;



					Q_WindWake->WindWake[250].Lvert[23][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[23][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[23][0].x = Q_WindWake->WindWake[250].VertM45.x;
					Q_WindWake->WindWake[250].Lvert[23][0].y = Q_WindWake->WindWake[250].VertM45.y;
					Q_WindWake->WindWake[250].Lvert[23][0].z = Q_WindWake->WindWake[250].VertM45.z;

							
					Q_WindWake->WindWake[250].Lvert[23][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[23][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[23][1].x = Q_WindWake->WindWake[250].VertM5.x;
					Q_WindWake->WindWake[250].Lvert[23][1].y = Q_WindWake->WindWake[250].VertM5.y;
					Q_WindWake->WindWake[250].Lvert[23][1].z = Q_WindWake->WindWake[250].VertM5.z;

							
					Q_WindWake->WindWake[250].Lvert[23][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[23][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[23][2].x = Q_WindWake->WindWake[250].VertT5.x;
					Q_WindWake->WindWake[250].Lvert[23][2].y = Q_WindWake->WindWake[250].VertT5.y;
					Q_WindWake->WindWake[250].Lvert[23][2].z = Q_WindWake->WindWake[250].VertT5.z;


					Q_WindWake->WindWake[250].Lvert[23][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[23][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[23][3].x = Q_WindWake->WindWake[250].VertT45.x;
					Q_WindWake->WindWake[250].Lvert[23][3].y = Q_WindWake->WindWake[250].VertT45.y;
					Q_WindWake->WindWake[250].Lvert[23][3].z = Q_WindWake->WindWake[250].VertT45.z;


					Q_WindWake->WindWake[250].Lvert[24][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[24][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[24][0].x = Q_WindWake->WindWake[250].VertM5.x;
					Q_WindWake->WindWake[250].Lvert[24][0].y = Q_WindWake->WindWake[250].VertM5.y;
					Q_WindWake->WindWake[250].Lvert[24][0].z = Q_WindWake->WindWake[250].VertM5.z;

					
					Q_WindWake->WindWake[250].Lvert[24][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[24][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[24][1].x = Q_WindWake->WindWake[250].VertM55.x;
					Q_WindWake->WindWake[250].Lvert[24][1].y = Q_WindWake->WindWake[250].VertM55.y;
					Q_WindWake->WindWake[250].Lvert[24][1].z = Q_WindWake->WindWake[250].VertM55.z;

							
					Q_WindWake->WindWake[250].Lvert[24][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[24][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[24][2].x = Q_WindWake->WindWake[250].VertT55.x;
					Q_WindWake->WindWake[250].Lvert[24][2].y = Q_WindWake->WindWake[250].VertT55.y;
					Q_WindWake->WindWake[250].Lvert[24][2].z = Q_WindWake->WindWake[250].VertT55.z;


					Q_WindWake->WindWake[250].Lvert[24][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[24][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[24][3].x = Q_WindWake->WindWake[250].VertT5.x;
					Q_WindWake->WindWake[250].Lvert[24][3].y = Q_WindWake->WindWake[250].VertT5.y;
					Q_WindWake->WindWake[250].Lvert[24][3].z = Q_WindWake->WindWake[250].VertT5.z;


					Q_WindWake->WindWake[250].Lvert[25][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[25][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[25][0].x = Q_WindWake->WindWake[250].VertM55.x;
					Q_WindWake->WindWake[250].Lvert[25][0].y = Q_WindWake->WindWake[250].VertM55.y;
					Q_WindWake->WindWake[250].Lvert[25][0].z = Q_WindWake->WindWake[250].VertM55.z;

							
					Q_WindWake->WindWake[250].Lvert[25][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[25][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[25][1].x = Q_WindWake->WindWake[250].VertM6.x;
					Q_WindWake->WindWake[250].Lvert[25][1].y = Q_WindWake->WindWake[250].VertM6.y;
					Q_WindWake->WindWake[250].Lvert[25][1].z = Q_WindWake->WindWake[250].VertM6.z;

							
					Q_WindWake->WindWake[250].Lvert[25][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[25][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[25][2].x = Q_WindWake->WindWake[250].VertT6.x;
					Q_WindWake->WindWake[250].Lvert[25][2].y = Q_WindWake->WindWake[250].VertT6.y;
					Q_WindWake->WindWake[250].Lvert[25][2].z = Q_WindWake->WindWake[250].VertT6.z;


					Q_WindWake->WindWake[250].Lvert[25][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[25][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[25][3].x = Q_WindWake->WindWake[250].VertT55.x;
					Q_WindWake->WindWake[250].Lvert[25][3].y = Q_WindWake->WindWake[250].VertT55.y;
					Q_WindWake->WindWake[250].Lvert[25][3].z = Q_WindWake->WindWake[250].VertT55.z;


					Q_WindWake->WindWake[250].Lvert[26][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[26][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[26][0].x = Q_WindWake->WindWake[250].VertM6.x;
					Q_WindWake->WindWake[250].Lvert[26][0].y = Q_WindWake->WindWake[250].VertM6.y;
					Q_WindWake->WindWake[250].Lvert[26][0].z = Q_WindWake->WindWake[250].VertM6.z;

							
					Q_WindWake->WindWake[250].Lvert[26][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[26][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[26][1].x = Q_WindWake->WindWake[250].VertM65.x;
					Q_WindWake->WindWake[250].Lvert[26][1].y = Q_WindWake->WindWake[250].VertM65.y;
					Q_WindWake->WindWake[250].Lvert[26][1].z = Q_WindWake->WindWake[250].VertM65.z;

							
					Q_WindWake->WindWake[250].Lvert[26][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[26][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[26][2].x = Q_WindWake->WindWake[250].VertT65.x;
					Q_WindWake->WindWake[250].Lvert[26][2].y = Q_WindWake->WindWake[250].VertT65.y;
					Q_WindWake->WindWake[250].Lvert[26][2].z = Q_WindWake->WindWake[250].VertT65.z;


					Q_WindWake->WindWake[250].Lvert[26][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[26][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[26][3].x = Q_WindWake->WindWake[250].VertT6.x;
					Q_WindWake->WindWake[250].Lvert[26][3].y = Q_WindWake->WindWake[250].VertT6.y;
					Q_WindWake->WindWake[250].Lvert[26][3].z = Q_WindWake->WindWake[250].VertT6.z;


					Q_WindWake->WindWake[250].Lvert[27][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[27][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[27][0].x = Q_WindWake->WindWake[250].VertM65.x;
					Q_WindWake->WindWake[250].Lvert[27][0].y = Q_WindWake->WindWake[250].VertM65.y;
					Q_WindWake->WindWake[250].Lvert[27][0].z = Q_WindWake->WindWake[250].VertM65.z;

							
					Q_WindWake->WindWake[250].Lvert[27][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[27][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[27][1].x = Q_WindWake->WindWake[250].VertM7.x;
					Q_WindWake->WindWake[250].Lvert[27][1].y = Q_WindWake->WindWake[250].VertM7.y;
					Q_WindWake->WindWake[250].Lvert[27][1].z = Q_WindWake->WindWake[250].VertM7.z;

							
					Q_WindWake->WindWake[250].Lvert[27][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[27][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[27][2].x = Q_WindWake->WindWake[250].VertT7.x;
					Q_WindWake->WindWake[250].Lvert[27][2].y = Q_WindWake->WindWake[250].VertT7.y;
					Q_WindWake->WindWake[250].Lvert[27][2].z = Q_WindWake->WindWake[250].VertT7.z;


					Q_WindWake->WindWake[250].Lvert[27][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[27][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[27][3].x = Q_WindWake->WindWake[250].VertT65.x;
					Q_WindWake->WindWake[250].Lvert[27][3].y = Q_WindWake->WindWake[250].VertT65.y;
					Q_WindWake->WindWake[250].Lvert[27][3].z = Q_WindWake->WindWake[250].VertT65.z;


					Q_WindWake->WindWake[250].Lvert[28][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[28][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[28][0].x = Q_WindWake->WindWake[250].VertM7.x;
					Q_WindWake->WindWake[250].Lvert[28][0].y = Q_WindWake->WindWake[250].VertM7.y;
					Q_WindWake->WindWake[250].Lvert[28][0].z = Q_WindWake->WindWake[250].VertM7.z;

							
					Q_WindWake->WindWake[250].Lvert[28][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[28][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[28][1].x = Q_WindWake->WindWake[250].VertM75.x;
					Q_WindWake->WindWake[250].Lvert[28][1].y = Q_WindWake->WindWake[250].VertM75.y;
					Q_WindWake->WindWake[250].Lvert[28][1].z = Q_WindWake->WindWake[250].VertM75.z;

							
					Q_WindWake->WindWake[250].Lvert[28][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[28][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[28][2].x = Q_WindWake->WindWake[250].VertT75.x;
					Q_WindWake->WindWake[250].Lvert[28][2].y = Q_WindWake->WindWake[250].VertT75.y;
					Q_WindWake->WindWake[250].Lvert[28][2].z = Q_WindWake->WindWake[250].VertT75.z;


					Q_WindWake->WindWake[250].Lvert[28][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[28][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[28][3].x = Q_WindWake->WindWake[250].VertT7.x;
					Q_WindWake->WindWake[250].Lvert[28][3].y = Q_WindWake->WindWake[250].VertT7.y;
					Q_WindWake->WindWake[250].Lvert[28][3].z = Q_WindWake->WindWake[250].VertT7.z;


					Q_WindWake->WindWake[250].Lvert[29][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[29][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[29][0].x = Q_WindWake->WindWake[250].VertM75.x;
					Q_WindWake->WindWake[250].Lvert[29][0].y = Q_WindWake->WindWake[250].VertM75.y;
					Q_WindWake->WindWake[250].Lvert[29][0].z = Q_WindWake->WindWake[250].VertM75.z;

							
					Q_WindWake->WindWake[250].Lvert[29][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[29][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[29][1].x = Q_WindWake->WindWake[250].VertM8.x;
					Q_WindWake->WindWake[250].Lvert[29][1].y = Q_WindWake->WindWake[250].VertM8.y;
					Q_WindWake->WindWake[250].Lvert[29][1].z = Q_WindWake->WindWake[250].VertM8.z;

							
					Q_WindWake->WindWake[250].Lvert[29][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[29][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[29][2].x = Q_WindWake->WindWake[250].VertT8.x;
					Q_WindWake->WindWake[250].Lvert[29][2].y = Q_WindWake->WindWake[250].VertT8.y;
					Q_WindWake->WindWake[250].Lvert[29][2].z = Q_WindWake->WindWake[250].VertT8.z;


					Q_WindWake->WindWake[250].Lvert[29][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[29][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[29][3].x = Q_WindWake->WindWake[250].VertT75.x;
					Q_WindWake->WindWake[250].Lvert[29][3].y = Q_WindWake->WindWake[250].VertT75.y;
					Q_WindWake->WindWake[250].Lvert[29][3].z = Q_WindWake->WindWake[250].VertT75.z;


					Q_WindWake->WindWake[250].Lvert[30][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[30][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[30][0].x = Q_WindWake->WindWake[250].VertM8.x;
					Q_WindWake->WindWake[250].Lvert[30][0].y = Q_WindWake->WindWake[250].VertM8.y;
					Q_WindWake->WindWake[250].Lvert[30][0].z = Q_WindWake->WindWake[250].VertM8.z;

							
					Q_WindWake->WindWake[250].Lvert[30][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[30][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[30][1].x = Q_WindWake->WindWake[250].VertM85.x;
					Q_WindWake->WindWake[250].Lvert[30][1].y = Q_WindWake->WindWake[250].VertM85.y;
					Q_WindWake->WindWake[250].Lvert[30][1].z = Q_WindWake->WindWake[250].VertM85.z;

							
					Q_WindWake->WindWake[250].Lvert[30][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[30][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[30][2].x = Q_WindWake->WindWake[250].VertT85.x;
					Q_WindWake->WindWake[250].Lvert[30][2].y = Q_WindWake->WindWake[250].VertT85.y;
					Q_WindWake->WindWake[250].Lvert[30][2].z = Q_WindWake->WindWake[250].VertT85.z;


					Q_WindWake->WindWake[250].Lvert[30][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[30][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[30][3].x = Q_WindWake->WindWake[250].VertT8.x;
					Q_WindWake->WindWake[250].Lvert[30][3].y = Q_WindWake->WindWake[250].VertT8.y;
					Q_WindWake->WindWake[250].Lvert[30][3].z = Q_WindWake->WindWake[250].VertT8.z;


					Q_WindWake->WindWake[250].Lvert[31][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[31][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[31][0].x = Q_WindWake->WindWake[250].VertM85.x;
					Q_WindWake->WindWake[250].Lvert[31][0].y = Q_WindWake->WindWake[250].VertM85.y;
					Q_WindWake->WindWake[250].Lvert[31][0].z = Q_WindWake->WindWake[250].VertM85.z;

							
					Q_WindWake->WindWake[250].Lvert[31][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[31][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[31][1].x = Q_WindWake->WindWake[250].VertM1.x;
					Q_WindWake->WindWake[250].Lvert[31][1].y = Q_WindWake->WindWake[250].VertM1.y;
					Q_WindWake->WindWake[250].Lvert[31][1].z = Q_WindWake->WindWake[250].VertM1.z;

							
					Q_WindWake->WindWake[250].Lvert[31][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[31][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[31][2].x = Q_WindWake->WindWake[250].VertT1.x;
					Q_WindWake->WindWake[250].Lvert[31][2].y = Q_WindWake->WindWake[250].VertT1.y;
					Q_WindWake->WindWake[250].Lvert[31][2].z = Q_WindWake->WindWake[250].VertT1.z;


					Q_WindWake->WindWake[250].Lvert[31][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[31][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[31][3].x = Q_WindWake->WindWake[250].VertT85.x;
					Q_WindWake->WindWake[250].Lvert[31][3].y = Q_WindWake->WindWake[250].VertT85.y;
					Q_WindWake->WindWake[250].Lvert[31][3].z = Q_WindWake->WindWake[250].VertT85.z;


					//##### - SOLID RING TWO

					Q_WindWake->WindWake[250].Lvert[32][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[32][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[32][0].x = Q_WindWake->WindWake[250].VertT1.x;
					Q_WindWake->WindWake[250].Lvert[32][0].y = Q_WindWake->WindWake[250].VertT1.y;
					Q_WindWake->WindWake[250].Lvert[32][0].z = Q_WindWake->WindWake[250].VertT1.z;

					
					Q_WindWake->WindWake[250].Lvert[32][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[32][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[32][1].x = Q_WindWake->WindWake[250].VertT15.x;
					Q_WindWake->WindWake[250].Lvert[32][1].y = Q_WindWake->WindWake[250].VertT15.y;
					Q_WindWake->WindWake[250].Lvert[32][1].z = Q_WindWake->WindWake[250].VertT15.z;

							
					Q_WindWake->WindWake[250].Lvert[32][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[32][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[32][2].x = Q_WindWake->WindWake[250].VertB15.x;
					Q_WindWake->WindWake[250].Lvert[32][2].y = Q_WindWake->WindWake[250].VertB15.y;
					Q_WindWake->WindWake[250].Lvert[32][2].z = Q_WindWake->WindWake[250].VertB15.z;


					Q_WindWake->WindWake[250].Lvert[32][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[32][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[32][3].x = Q_WindWake->WindWake[250].VertB1.x;
					Q_WindWake->WindWake[250].Lvert[32][3].y = Q_WindWake->WindWake[250].VertB1.y;
					Q_WindWake->WindWake[250].Lvert[32][3].z = Q_WindWake->WindWake[250].VertB1.z;


					Q_WindWake->WindWake[250].Lvert[33][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[33][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[33][0].x = Q_WindWake->WindWake[250].VertT15.x;
					Q_WindWake->WindWake[250].Lvert[33][0].y = Q_WindWake->WindWake[250].VertT15.y;
					Q_WindWake->WindWake[250].Lvert[33][0].z = Q_WindWake->WindWake[250].VertT15.z;

							
					Q_WindWake->WindWake[250].Lvert[33][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[33][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[33][1].x = Q_WindWake->WindWake[250].VertT2.x;
					Q_WindWake->WindWake[250].Lvert[33][1].y = Q_WindWake->WindWake[250].VertT2.y;
					Q_WindWake->WindWake[250].Lvert[33][1].z = Q_WindWake->WindWake[250].VertT2.z;

							
					Q_WindWake->WindWake[250].Lvert[33][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[33][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[33][2].x = Q_WindWake->WindWake[250].VertB2.x;
					Q_WindWake->WindWake[250].Lvert[33][2].y = Q_WindWake->WindWake[250].VertB2.y;
					Q_WindWake->WindWake[250].Lvert[33][2].z = Q_WindWake->WindWake[250].VertB2.z;


					Q_WindWake->WindWake[250].Lvert[33][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[33][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[33][3].x = Q_WindWake->WindWake[250].VertB15.x;
					Q_WindWake->WindWake[250].Lvert[33][3].y = Q_WindWake->WindWake[250].VertB15.y;
					Q_WindWake->WindWake[250].Lvert[33][3].z = Q_WindWake->WindWake[250].VertB15.z;


					Q_WindWake->WindWake[250].Lvert[34][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[34][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[34][0].x = Q_WindWake->WindWake[250].VertT2.x;
					Q_WindWake->WindWake[250].Lvert[34][0].y = Q_WindWake->WindWake[250].VertT2.y;
					Q_WindWake->WindWake[250].Lvert[34][0].z = Q_WindWake->WindWake[250].VertT2.z;

							
					Q_WindWake->WindWake[250].Lvert[34][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[34][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[34][1].x = Q_WindWake->WindWake[250].VertT25.x;
					Q_WindWake->WindWake[250].Lvert[34][1].y = Q_WindWake->WindWake[250].VertT25.y;
					Q_WindWake->WindWake[250].Lvert[34][1].z = Q_WindWake->WindWake[250].VertT25.z;

							
					Q_WindWake->WindWake[250].Lvert[34][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[34][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[34][2].x = Q_WindWake->WindWake[250].VertB25.x;
					Q_WindWake->WindWake[250].Lvert[34][2].y = Q_WindWake->WindWake[250].VertB25.y;
					Q_WindWake->WindWake[250].Lvert[34][2].z = Q_WindWake->WindWake[250].VertB25.z;


					Q_WindWake->WindWake[250].Lvert[34][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[34][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[34][3].x = Q_WindWake->WindWake[250].VertB2.x;
					Q_WindWake->WindWake[250].Lvert[34][3].y = Q_WindWake->WindWake[250].VertB2.y;
					Q_WindWake->WindWake[250].Lvert[34][3].z = Q_WindWake->WindWake[250].VertB2.z;



					Q_WindWake->WindWake[250].Lvert[35][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[35][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[35][0].x = Q_WindWake->WindWake[250].VertT25.x;
					Q_WindWake->WindWake[250].Lvert[35][0].y = Q_WindWake->WindWake[250].VertT25.y;
					Q_WindWake->WindWake[250].Lvert[35][0].z = Q_WindWake->WindWake[250].VertT25.z;

							
					Q_WindWake->WindWake[250].Lvert[35][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[35][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[35][1].x = Q_WindWake->WindWake[250].VertT3.x;
					Q_WindWake->WindWake[250].Lvert[35][1].y = Q_WindWake->WindWake[250].VertT3.y;
					Q_WindWake->WindWake[250].Lvert[35][1].z = Q_WindWake->WindWake[250].VertT3.z;

							
					Q_WindWake->WindWake[250].Lvert[35][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[35][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[35][2].x = Q_WindWake->WindWake[250].VertB3.x;
					Q_WindWake->WindWake[250].Lvert[35][2].y = Q_WindWake->WindWake[250].VertB3.y;
					Q_WindWake->WindWake[250].Lvert[35][2].z = Q_WindWake->WindWake[250].VertB3.z;


					Q_WindWake->WindWake[250].Lvert[35][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[35][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[35][3].x = Q_WindWake->WindWake[250].VertB25.x;
					Q_WindWake->WindWake[250].Lvert[35][3].y = Q_WindWake->WindWake[250].VertB25.y;
					Q_WindWake->WindWake[250].Lvert[35][3].z = Q_WindWake->WindWake[250].VertB25.z;


					Q_WindWake->WindWake[250].Lvert[36][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[36][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[36][0].x = Q_WindWake->WindWake[250].VertT3.x;
					Q_WindWake->WindWake[250].Lvert[36][0].y = Q_WindWake->WindWake[250].VertT3.y;
					Q_WindWake->WindWake[250].Lvert[36][0].z = Q_WindWake->WindWake[250].VertT3.z;

							
					Q_WindWake->WindWake[250].Lvert[36][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[36][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[36][1].x = Q_WindWake->WindWake[250].VertT35.x;
					Q_WindWake->WindWake[250].Lvert[36][1].y = Q_WindWake->WindWake[250].VertT35.y;
					Q_WindWake->WindWake[250].Lvert[36][1].z = Q_WindWake->WindWake[250].VertT35.z;

							
					Q_WindWake->WindWake[250].Lvert[36][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[36][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[36][2].x = Q_WindWake->WindWake[250].VertB35.x;
					Q_WindWake->WindWake[250].Lvert[36][2].y = Q_WindWake->WindWake[250].VertB35.y;
					Q_WindWake->WindWake[250].Lvert[36][2].z = Q_WindWake->WindWake[250].VertB35.z;


					Q_WindWake->WindWake[250].Lvert[36][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[36][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[36][3].x = Q_WindWake->WindWake[250].VertB3.x;
					Q_WindWake->WindWake[250].Lvert[36][3].y = Q_WindWake->WindWake[250].VertB3.y;
					Q_WindWake->WindWake[250].Lvert[36][3].z = Q_WindWake->WindWake[250].VertB3.z;


					Q_WindWake->WindWake[250].Lvert[37][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[37][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[37][0].x = Q_WindWake->WindWake[250].VertT35.x;
					Q_WindWake->WindWake[250].Lvert[37][0].y = Q_WindWake->WindWake[250].VertT35.y;
					Q_WindWake->WindWake[250].Lvert[37][0].z = Q_WindWake->WindWake[250].VertT35.z;

							
					Q_WindWake->WindWake[250].Lvert[37][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[37][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[37][1].x = Q_WindWake->WindWake[250].VertT4.x;
					Q_WindWake->WindWake[250].Lvert[37][1].y = Q_WindWake->WindWake[250].VertT4.y;
					Q_WindWake->WindWake[250].Lvert[37][1].z = Q_WindWake->WindWake[250].VertT4.z;

							
					Q_WindWake->WindWake[250].Lvert[37][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[37][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[37][2].x = Q_WindWake->WindWake[250].VertB4.x;
					Q_WindWake->WindWake[250].Lvert[37][2].y = Q_WindWake->WindWake[250].VertB4.y;
					Q_WindWake->WindWake[250].Lvert[37][2].z = Q_WindWake->WindWake[250].VertB4.z;


					Q_WindWake->WindWake[250].Lvert[37][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[37][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[37][3].x = Q_WindWake->WindWake[250].VertB35.x;
					Q_WindWake->WindWake[250].Lvert[37][3].y = Q_WindWake->WindWake[250].VertB35.y;
					Q_WindWake->WindWake[250].Lvert[37][3].z = Q_WindWake->WindWake[250].VertB35.z;


					Q_WindWake->WindWake[250].Lvert[38][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[38][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[38][0].x = Q_WindWake->WindWake[250].VertT4.x;
					Q_WindWake->WindWake[250].Lvert[38][0].y = Q_WindWake->WindWake[250].VertT4.y;
					Q_WindWake->WindWake[250].Lvert[38][0].z = Q_WindWake->WindWake[250].VertT4.z;

							
					Q_WindWake->WindWake[250].Lvert[38][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[38][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[38][1].x = Q_WindWake->WindWake[250].VertT45.x;
					Q_WindWake->WindWake[250].Lvert[38][1].y = Q_WindWake->WindWake[250].VertT45.y;
					Q_WindWake->WindWake[250].Lvert[38][1].z = Q_WindWake->WindWake[250].VertT45.z;

							
					Q_WindWake->WindWake[250].Lvert[38][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[38][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[38][2].x = Q_WindWake->WindWake[250].VertB45.x;
					Q_WindWake->WindWake[250].Lvert[38][2].y = Q_WindWake->WindWake[250].VertB45.y;
					Q_WindWake->WindWake[250].Lvert[38][2].z = Q_WindWake->WindWake[250].VertB45.z;


					Q_WindWake->WindWake[250].Lvert[38][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[38][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[38][3].x = Q_WindWake->WindWake[250].VertB4.x;
					Q_WindWake->WindWake[250].Lvert[38][3].y = Q_WindWake->WindWake[250].VertB4.y;
					Q_WindWake->WindWake[250].Lvert[38][3].z = Q_WindWake->WindWake[250].VertB4.z;


					Q_WindWake->WindWake[250].Lvert[39][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[39][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[39][0].x = Q_WindWake->WindWake[250].VertT45.x;
					Q_WindWake->WindWake[250].Lvert[39][0].y = Q_WindWake->WindWake[250].VertT45.y;
					Q_WindWake->WindWake[250].Lvert[39][0].z = Q_WindWake->WindWake[250].VertT45.z;

							
					Q_WindWake->WindWake[250].Lvert[39][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[39][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[39][1].x = Q_WindWake->WindWake[250].VertT5.x;
					Q_WindWake->WindWake[250].Lvert[39][1].y = Q_WindWake->WindWake[250].VertT5.y;
					Q_WindWake->WindWake[250].Lvert[39][1].z = Q_WindWake->WindWake[250].VertT5.z;

							
					Q_WindWake->WindWake[250].Lvert[39][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[39][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[39][2].x = Q_WindWake->WindWake[250].VertB5.x;
					Q_WindWake->WindWake[250].Lvert[39][2].y = Q_WindWake->WindWake[250].VertB5.y;
					Q_WindWake->WindWake[250].Lvert[39][2].z = Q_WindWake->WindWake[250].VertB5.z;


					Q_WindWake->WindWake[250].Lvert[39][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[39][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[39][3].x = Q_WindWake->WindWake[250].VertB45.x;
					Q_WindWake->WindWake[250].Lvert[39][3].y = Q_WindWake->WindWake[250].VertB45.y;
					Q_WindWake->WindWake[250].Lvert[39][3].z = Q_WindWake->WindWake[250].VertB45.z;


					Q_WindWake->WindWake[250].Lvert[40][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[40][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[40][0].x = Q_WindWake->WindWake[250].VertT5.x;
					Q_WindWake->WindWake[250].Lvert[40][0].y = Q_WindWake->WindWake[250].VertT5.y;
					Q_WindWake->WindWake[250].Lvert[40][0].z = Q_WindWake->WindWake[250].VertT5.z;

					
					Q_WindWake->WindWake[250].Lvert[40][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[40][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[40][1].x = Q_WindWake->WindWake[250].VertT55.x;
					Q_WindWake->WindWake[250].Lvert[40][1].y = Q_WindWake->WindWake[250].VertT55.y;
					Q_WindWake->WindWake[250].Lvert[40][1].z = Q_WindWake->WindWake[250].VertT55.z;

							
					Q_WindWake->WindWake[250].Lvert[40][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[40][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[40][2].x = Q_WindWake->WindWake[250].VertB55.x;
					Q_WindWake->WindWake[250].Lvert[40][2].y = Q_WindWake->WindWake[250].VertB55.y;
					Q_WindWake->WindWake[250].Lvert[40][2].z = Q_WindWake->WindWake[250].VertB55.z;


					Q_WindWake->WindWake[250].Lvert[40][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[40][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[40][3].x = Q_WindWake->WindWake[250].VertB5.x;
					Q_WindWake->WindWake[250].Lvert[40][3].y = Q_WindWake->WindWake[250].VertB5.y;
					Q_WindWake->WindWake[250].Lvert[40][3].z = Q_WindWake->WindWake[250].VertB5.z;


					Q_WindWake->WindWake[250].Lvert[41][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[41][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[41][0].x = Q_WindWake->WindWake[250].VertT55.x;
					Q_WindWake->WindWake[250].Lvert[41][0].y = Q_WindWake->WindWake[250].VertT55.y;
					Q_WindWake->WindWake[250].Lvert[41][0].z = Q_WindWake->WindWake[250].VertT55.z;

							
					Q_WindWake->WindWake[250].Lvert[41][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[41][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[41][1].x = Q_WindWake->WindWake[250].VertT6.x;
					Q_WindWake->WindWake[250].Lvert[41][1].y = Q_WindWake->WindWake[250].VertT6.y;
					Q_WindWake->WindWake[250].Lvert[41][1].z = Q_WindWake->WindWake[250].VertT6.z;

							
					Q_WindWake->WindWake[250].Lvert[41][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[41][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[41][2].x = Q_WindWake->WindWake[250].VertB6.x;
					Q_WindWake->WindWake[250].Lvert[41][2].y = Q_WindWake->WindWake[250].VertB6.y;
					Q_WindWake->WindWake[250].Lvert[41][2].z = Q_WindWake->WindWake[250].VertB6.z;


					Q_WindWake->WindWake[250].Lvert[41][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[41][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[41][3].x = Q_WindWake->WindWake[250].VertB55.x;
					Q_WindWake->WindWake[250].Lvert[41][3].y = Q_WindWake->WindWake[250].VertB55.y;
					Q_WindWake->WindWake[250].Lvert[41][3].z = Q_WindWake->WindWake[250].VertB55.z;


					Q_WindWake->WindWake[250].Lvert[42][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[42][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[42][0].x = Q_WindWake->WindWake[250].VertT6.x;
					Q_WindWake->WindWake[250].Lvert[42][0].y = Q_WindWake->WindWake[250].VertT6.y;
					Q_WindWake->WindWake[250].Lvert[42][0].z = Q_WindWake->WindWake[250].VertT6.z;

							
					Q_WindWake->WindWake[250].Lvert[42][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[42][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[42][1].x = Q_WindWake->WindWake[250].VertT65.x;
					Q_WindWake->WindWake[250].Lvert[42][1].y = Q_WindWake->WindWake[250].VertT65.y;
					Q_WindWake->WindWake[250].Lvert[42][1].z = Q_WindWake->WindWake[250].VertT65.z;

							
					Q_WindWake->WindWake[250].Lvert[42][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[42][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[42][2].x = Q_WindWake->WindWake[250].VertB65.x;
					Q_WindWake->WindWake[250].Lvert[42][2].y = Q_WindWake->WindWake[250].VertB65.y;
					Q_WindWake->WindWake[250].Lvert[42][2].z = Q_WindWake->WindWake[250].VertB65.z;


					Q_WindWake->WindWake[250].Lvert[42][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[42][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[42][3].x = Q_WindWake->WindWake[250].VertB6.x;
					Q_WindWake->WindWake[250].Lvert[42][3].y = Q_WindWake->WindWake[250].VertB6.y;
					Q_WindWake->WindWake[250].Lvert[42][3].z = Q_WindWake->WindWake[250].VertB6.z;


					Q_WindWake->WindWake[250].Lvert[43][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[43][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[43][0].x = Q_WindWake->WindWake[250].VertT65.x;
					Q_WindWake->WindWake[250].Lvert[43][0].y = Q_WindWake->WindWake[250].VertT65.y;
					Q_WindWake->WindWake[250].Lvert[43][0].z = Q_WindWake->WindWake[250].VertT65.z;

							
					Q_WindWake->WindWake[250].Lvert[43][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[43][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[43][1].x = Q_WindWake->WindWake[250].VertT7.x;
					Q_WindWake->WindWake[250].Lvert[43][1].y = Q_WindWake->WindWake[250].VertT7.y;
					Q_WindWake->WindWake[250].Lvert[43][1].z = Q_WindWake->WindWake[250].VertT7.z;

							
					Q_WindWake->WindWake[250].Lvert[43][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[43][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[43][2].x = Q_WindWake->WindWake[250].VertB7.x;
					Q_WindWake->WindWake[250].Lvert[43][2].y = Q_WindWake->WindWake[250].VertB7.y;
					Q_WindWake->WindWake[250].Lvert[43][2].z = Q_WindWake->WindWake[250].VertB7.z;


					Q_WindWake->WindWake[250].Lvert[43][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[43][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[43][3].x = Q_WindWake->WindWake[250].VertB65.x;
					Q_WindWake->WindWake[250].Lvert[43][3].y = Q_WindWake->WindWake[250].VertB65.y;
					Q_WindWake->WindWake[250].Lvert[43][3].z = Q_WindWake->WindWake[250].VertB65.z;


					Q_WindWake->WindWake[250].Lvert[44][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[44][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[44][0].x = Q_WindWake->WindWake[250].VertT7.x;
					Q_WindWake->WindWake[250].Lvert[44][0].y = Q_WindWake->WindWake[250].VertT7.y;
					Q_WindWake->WindWake[250].Lvert[44][0].z = Q_WindWake->WindWake[250].VertT7.z;

							
					Q_WindWake->WindWake[250].Lvert[44][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[44][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[44][1].x = Q_WindWake->WindWake[250].VertT75.x;
					Q_WindWake->WindWake[250].Lvert[44][1].y = Q_WindWake->WindWake[250].VertT75.y;
					Q_WindWake->WindWake[250].Lvert[44][1].z = Q_WindWake->WindWake[250].VertT75.z;

							
					Q_WindWake->WindWake[250].Lvert[44][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[44][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[44][2].x = Q_WindWake->WindWake[250].VertB75.x;
					Q_WindWake->WindWake[250].Lvert[44][2].y = Q_WindWake->WindWake[250].VertB75.y;
					Q_WindWake->WindWake[250].Lvert[44][2].z = Q_WindWake->WindWake[250].VertB75.z;


					Q_WindWake->WindWake[250].Lvert[44][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[44][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[44][3].x = Q_WindWake->WindWake[250].VertB7.x;
					Q_WindWake->WindWake[250].Lvert[44][3].y = Q_WindWake->WindWake[250].VertB7.y;
					Q_WindWake->WindWake[250].Lvert[44][3].z = Q_WindWake->WindWake[250].VertB7.z;


					Q_WindWake->WindWake[250].Lvert[45][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[45][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[45][0].x = Q_WindWake->WindWake[250].VertT75.x;
					Q_WindWake->WindWake[250].Lvert[45][0].y = Q_WindWake->WindWake[250].VertT75.y;
					Q_WindWake->WindWake[250].Lvert[45][0].z = Q_WindWake->WindWake[250].VertT75.z;

							
					Q_WindWake->WindWake[250].Lvert[45][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[45][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[45][1].x = Q_WindWake->WindWake[250].VertT8.x;
					Q_WindWake->WindWake[250].Lvert[45][1].y = Q_WindWake->WindWake[250].VertT8.y;
					Q_WindWake->WindWake[250].Lvert[45][1].z = Q_WindWake->WindWake[250].VertT8.z;

							
					Q_WindWake->WindWake[250].Lvert[45][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[45][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[45][2].x = Q_WindWake->WindWake[250].VertB8.x;
					Q_WindWake->WindWake[250].Lvert[45][2].y = Q_WindWake->WindWake[250].VertB8.y;
					Q_WindWake->WindWake[250].Lvert[45][2].z = Q_WindWake->WindWake[250].VertB8.z;


					Q_WindWake->WindWake[250].Lvert[45][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[45][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[45][3].x = Q_WindWake->WindWake[250].VertB75.x;
					Q_WindWake->WindWake[250].Lvert[45][3].y = Q_WindWake->WindWake[250].VertB75.y;
					Q_WindWake->WindWake[250].Lvert[45][3].z = Q_WindWake->WindWake[250].VertB75.z;


					Q_WindWake->WindWake[250].Lvert[46][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[46][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[46][0].x = Q_WindWake->WindWake[250].VertT8.x;
					Q_WindWake->WindWake[250].Lvert[46][0].y = Q_WindWake->WindWake[250].VertT8.y;
					Q_WindWake->WindWake[250].Lvert[46][0].z = Q_WindWake->WindWake[250].VertT8.z;

							
					Q_WindWake->WindWake[250].Lvert[46][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[46][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[46][1].x = Q_WindWake->WindWake[250].VertT85.x;
					Q_WindWake->WindWake[250].Lvert[46][1].y = Q_WindWake->WindWake[250].VertT85.y;
					Q_WindWake->WindWake[250].Lvert[46][1].z = Q_WindWake->WindWake[250].VertT85.z;


					Q_WindWake->WindWake[250].Lvert[46][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[46][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[46][2].x = Q_WindWake->WindWake[250].VertB85.x;
					Q_WindWake->WindWake[250].Lvert[46][2].y = Q_WindWake->WindWake[250].VertB85.y;
					Q_WindWake->WindWake[250].Lvert[46][2].z = Q_WindWake->WindWake[250].VertB85.z;


					Q_WindWake->WindWake[250].Lvert[46][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[46][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[46][3].x = Q_WindWake->WindWake[250].VertB8.x;
					Q_WindWake->WindWake[250].Lvert[46][3].y = Q_WindWake->WindWake[250].VertB8.y;
					Q_WindWake->WindWake[250].Lvert[46][3].z = Q_WindWake->WindWake[250].VertB8.z;


					Q_WindWake->WindWake[250].Lvert[47][0].u = 0;
					Q_WindWake->WindWake[250].Lvert[47][0].v = 0;
					Q_WindWake->WindWake[250].Lvert[47][0].x = Q_WindWake->WindWake[250].VertT85.x;
					Q_WindWake->WindWake[250].Lvert[47][0].y = Q_WindWake->WindWake[250].VertT85.y;
					Q_WindWake->WindWake[250].Lvert[47][0].z = Q_WindWake->WindWake[250].VertT85.z;


					Q_WindWake->WindWake[250].Lvert[47][1].u = 1;
					Q_WindWake->WindWake[250].Lvert[47][1].v = 0;
					Q_WindWake->WindWake[250].Lvert[47][1].x = Q_WindWake->WindWake[250].VertT1.x;
					Q_WindWake->WindWake[250].Lvert[47][1].y = Q_WindWake->WindWake[250].VertT1.y;
					Q_WindWake->WindWake[250].Lvert[47][1].z = Q_WindWake->WindWake[250].VertT1.z;


					Q_WindWake->WindWake[250].Lvert[47][2].u = 1;
					Q_WindWake->WindWake[250].Lvert[47][2].v = 1;
					Q_WindWake->WindWake[250].Lvert[47][2].x = Q_WindWake->WindWake[250].VertB1.x;
					Q_WindWake->WindWake[250].Lvert[47][2].y = Q_WindWake->WindWake[250].VertB1.y;
					Q_WindWake->WindWake[250].Lvert[47][2].z = Q_WindWake->WindWake[250].VertB1.z;


					Q_WindWake->WindWake[250].Lvert[47][3].u = 0;
					Q_WindWake->WindWake[250].Lvert[47][3].v = 1;
					Q_WindWake->WindWake[250].Lvert[47][3].x = Q_WindWake->WindWake[250].VertB85.x;
					Q_WindWake->WindWake[250].Lvert[47][3].y = Q_WindWake->WindWake[250].VertB85.y;
					Q_WindWake->WindWake[250].Lvert[47][3].z = Q_WindWake->WindWake[250].VertB85.z;



		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkTYPE == 0)
			{
			int i = 0;
			while(i <= 15)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[250].Lvert[i][0], 3, Medias->Water[Q_WindWake->WindWake[250].MaterialCNT], Q_WindWake->WindWake[250].Type, Q_WindWake->WindWake[250].RenderFlags, 1.0f);
				i++;
				}

			i = 16;
			while(i <= 47)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[250].Lvert[i][0], 4, Medias->Water[Q_WindWake->WindWake[250].MaterialCNT], Q_WindWake->WindWake[250].Type, Q_WindWake->WindWake[250].RenderFlags, 1.0f);
				i++;
				}
			}

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkTYPE == 1)
			{
			int i = 0;
			while(i <= 15)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[250].Lvert[i][0], 3, Medias->fire[Q_WindWake->WindWake[250].MaterialCNT], Q_WindWake->WindWake[250].Type, Q_WindWake->WindWake[250].RenderFlags, 1.0f);
				i++;
				}

			i = 16;
			while(i <= 47)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[250].Lvert[i][0], 4, Medias->fire[Q_WindWake->WindWake[250].MaterialCNT], Q_WindWake->WindWake[250].Type, Q_WindWake->WindWake[250].RenderFlags, 1.0f);
				i++;
				}
			}


		//###### Initialise one Textured Tri Effect - WindWake Ring Trail - Static
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Live = 1;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].PosB = Q_WindWake->WindWake[250].Pos;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Pos = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].STRPos;

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkTYPE == 0)
			{ player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].EffectType = 1; }

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkTYPE == 1)
			{ player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].EffectType = 4; }

		//#### Set Back facing verts
		if(player[g_Player]->NomTriEffect != 0)
			{
			//#### Set front verts
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1 = Q_WindWake->WindWake[250].VertB1;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT15 = Q_WindWake->WindWake[250].VertB15;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT2 = Q_WindWake->WindWake[250].VertB2;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT25 = Q_WindWake->WindWake[250].VertB25;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT3 = Q_WindWake->WindWake[250].VertB3;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT35 = Q_WindWake->WindWake[250].VertB35;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT4 = Q_WindWake->WindWake[250].VertB4;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT45 = Q_WindWake->WindWake[250].VertB45;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT5 = Q_WindWake->WindWake[250].VertB5;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT55 = Q_WindWake->WindWake[250].VertB55;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT6 = Q_WindWake->WindWake[250].VertB6;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT65 = Q_WindWake->WindWake[250].VertB65;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT7 = Q_WindWake->WindWake[250].VertB7;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT75 = Q_WindWake->WindWake[250].VertB75;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT8 = Q_WindWake->WindWake[250].VertB8;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT85 = Q_WindWake->WindWake[250].VertB85;

			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB1 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT1;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB15 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT15;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB2 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT2;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB25 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT25;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB3 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT3;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB35 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT35;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB4 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT4;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB45 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT45;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB5 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT5;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB55 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT55;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB6 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT6;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB65 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT65;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB7 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT7;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB75 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT75;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB8 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT8;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB85 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT85;
			}
		else
			{
			//#### Set front verts
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1 = Q_WindWake->WindWake[250].VertT1;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT15 = Q_WindWake->WindWake[250].VertT15;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT2 = Q_WindWake->WindWake[250].VertT2;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT25 = Q_WindWake->WindWake[250].VertT25;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT3 = Q_WindWake->WindWake[250].VertT3;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT35 = Q_WindWake->WindWake[250].VertT35;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT4 = Q_WindWake->WindWake[250].VertT4;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT45 = Q_WindWake->WindWake[250].VertT45;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT5 = Q_WindWake->WindWake[250].VertT5;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT55 = Q_WindWake->WindWake[250].VertT55;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT6 = Q_WindWake->WindWake[250].VertT6;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT65 = Q_WindWake->WindWake[250].VertT65;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT7 = Q_WindWake->WindWake[250].VertT7;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT75 = Q_WindWake->WindWake[250].VertT75;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT8 = Q_WindWake->WindWake[250].VertT8;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT85 = Q_WindWake->WindWake[250].VertT85;

			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB1 = Q_WindWake->WindWake[250].VertB1;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB15 = Q_WindWake->WindWake[250].VertB15;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB2 = Q_WindWake->WindWake[250].VertB2;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB25 = Q_WindWake->WindWake[250].VertB25;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB3 = Q_WindWake->WindWake[250].VertB3;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB35 = Q_WindWake->WindWake[250].VertB35;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB4 = Q_WindWake->WindWake[250].VertB4;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB45 = Q_WindWake->WindWake[250].VertB45;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB5 = Q_WindWake->WindWake[250].VertB5;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB55 = Q_WindWake->WindWake[250].VertB55;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB6 = Q_WindWake->WindWake[250].VertB6;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB65 = Q_WindWake->WindWake[250].VertB65;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB7 = Q_WindWake->WindWake[250].VertB7;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB75 = Q_WindWake->WindWake[250].VertB75;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB8 = Q_WindWake->WindWake[250].VertB8;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB85 = Q_WindWake->WindWake[250].VertB85;
			}


		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecIn = Q_WindWake->WindWake[250].VecIn;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUp = Q_WindWake->WindWake[250].VecUp;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeft = Q_WindWake->WindWake[250].VecLeft;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT = Q_WindWake->WindWake[250].MaterialCNT;

		if(player[g_Player]->JinkSpecialON < 1 || 1)
			{
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Red = 255;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Green = 255;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Blue = 255;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Alpha = Q_WindWake->WindWake[250].MAINALPHA;
			}
		else
			{
			//player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Alpha = Q_WindWake->WindWake[250].MAINALPHA/2;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Alpha = Q_WindWake->WindWake[250].MAINALPHA;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Red = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkRED;	//135
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Green = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkGREEN;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Blue = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelEFFECTS.JinkBLUE;
			}

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].LengthDist = 3;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].ExpandDist = 0.01;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].PolyType = QPOLY_TYPE_TRI;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].RenderFlags = QPOLY_REND_DEPTH_SORT;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].ScaleBIT = 1.0f;

		if(player[g_Player]->NomTriEffect == 0)
			{
			TriEffectUt = 0.1;
			TriEffectUb = 0;
			}
		else
			{
			TriEffectUt += 0.1;
			TriEffectUb += 0.1;
			if(TriEffectUt > 1)
				{
				TriEffectUt = 0.1;
				TriEffectUb = 0;
				}
			}

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Ut = TriEffectUt;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Ub = TriEffectUb;

		player[g_Player]->NomTriEffect++;
		if(player[g_Player]->NomTriEffect > 299) player[g_Player]->NomTriEffect = 0;
		}
	}

};