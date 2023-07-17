/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Avatar WindWake-

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

//#####- AI WIND WAKE -#####

void Q_EFFCon::WindWake_AvatarFrame(int Count)
	{
	if(Q_Forge->Forge[Count].WindWake == 1)
		{
		Q_WindWake->WindWake[Count].MAINALPHA += 15*_->TimeScale;
		if((Q_WindWake->WindWake[Count].MAINALPHA > Q_WindWake->WindWake[Count].AlphaMAX) && Q_WindWake->WindWake[Count].AlphaMAX != 0) Q_WindWake->WindWake[Count].MAINALPHA = Q_WindWake->WindWake[Count].AlphaMAX;
		}
	else
		{
		Q_WindWake->WindWake[Count].MAINALPHA -= 6*_->TimeScale; //15
		if(Q_WindWake->WindWake[Count].MAINALPHA < 0) Q_WindWake->WindWake[Count].MAINALPHA = 0;
		}


	if(Q_WindWake->WindWake[Count].MAINALPHA > 0)
		{
		//#### Default Values for standard JUMP
		Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
		Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 72.5;
		Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 143;
		Q_WindWake->WindWake[Count].AlphaMAX = 45;

		//### Change Scale and center point depending on attack type
		if(Q_Forge->Forge[Count].Aposestate == 24)	//Jump Kick
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 65;	//82.5
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 125;
			Q_WindWake->WindWake[Count].AlphaMAX = 35;
			}

		if(Q_Forge->Forge[Count].Aposestate == 22)	//Leap Spin Kick
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 160;
			Q_WindWake->WindWake[Count].AlphaMAX = 40;
			}

		if(Q_Forge->Forge[Count].Aposestate == 76) // JSRush UP
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 87.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 115;
			Q_WindWake->WindWake[Count].AlphaMAX = 50;
			}

		if(Q_Forge->Forge[Count].Aposestate == 74)	//JSRush Punch
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 140;
			Q_WindWake->WindWake[Count].AlphaMAX = 40;
			}

		if(Q_Forge->Forge[Count].Aposestate == 73)	//JSRUSH
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 150;
			Q_WindWake->WindWake[Count].AlphaMAX = 90;
			}

		if(Q_Forge->Forge[Count].Aposestate == 61)	//Twist Kick
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 150;
			Q_WindWake->WindWake[Count].AlphaMAX = 40;
			}

		if(Q_Forge->Forge[Count].Aposestate == 65)	//Rush Elbow
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 57.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 105;
			Q_WindWake->WindWake[Count].AlphaMAX = 80;
			}

		if(Q_Forge->Forge[Count].Aposestate == 84)	//Overhead Pinwheel
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 67.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 115;
			Q_WindWake->WindWake[Count].AlphaMAX = 65;
			}

		if(Q_Forge->Forge[Count].Aposestate == 81)	//Spin Out Left
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 140;
			Q_WindWake->WindWake[Count].AlphaMAX = 40;
			}

		if(Q_Forge->Forge[Count].Mposestate == 26)	//Roll Forward
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 52.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 100;
			Q_WindWake->WindWake[Count].AlphaMAX = 30;
			}

		if(Q_Forge->Forge[Count].Mposestate == 28)	//Roll Left
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 52.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 100;
			Q_WindWake->WindWake[Count].AlphaMAX = 25;
			}

		if(Q_Forge->Forge[Count].Mposestate == 29)	//Roll Right
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 52.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 100;
			Q_WindWake->WindWake[Count].AlphaMAX = 25;
			}

		if(Q_Forge->Forge[Count].Mposestate == 8)	//BackFlip
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 60;	//82.5
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[Count].AlphaMAX = 45;
			}

		if(Q_Forge->Forge[Count].Mposestate == 23)	//Cartwheel Left
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[Count].AlphaMAX = 30;
			}

		if(Q_Forge->Forge[Count].Mposestate == 24)	//Cartwheel Right
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 145;
			Q_WindWake->WindWake[Count].AlphaMAX = 30;
			}

		if(Q_Forge->Forge[Count].Mposestate == 15)	//Air Rush Forward
			{
			Q_WindWake->WindWake[Count].Pos = Q_Forge->Forge[Count].AV.Xform.Translation;
			Q_WindWake->WindWake[Count].Pos.y += (75 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 82.5;
			Q_WindWake->WindWake[Count].Scale = (100 * (((Q_Forge->Forge[Count].CharDATA.BodySKILL.Height/100)-0.5)*1)) + 125;
			Q_WindWake->WindWake[Count].AlphaMAX = 65;
			}

		///////// BALANCE
		Q_WindWake->WindWake[Count].Scale /= 1.8;

		//#### Revert to WindWake Memory
		if(Q_Forge->Forge[Count].WindWake == 0)
			{
			Q_WindWake->WindWake[Count].Pos = Q_WindWake->WindWake[Count].MeMPos;
			Q_WindWake->WindWake[Count].Scale = Q_WindWake->WindWake[Count].MeMScale;
			Q_WindWake->WindWake[Count].AlphaMAX = Q_WindWake->WindWake[Count].MeMAlphaMAX;
			}

		if(Q_Forge->Forge[Count].INvectorAPC.x == 0 && Q_Forge->Forge[Count].INvectorAPC.y == 0 && Q_Forge->Forge[Count].INvectorAPC.z == 0) Q_Forge->Forge[Count].INvectorAPC = Q_WindWake->WindWake[Count].MeMINvectorAPC;


		//##### Calculate Direction Vectors
		Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
		Qpo->Transform_RotateVector(&RotateMatrix, &Q_Forge->Forge[Count].INvectorAPC, &Q_Forge->Forge[Count].LEFTvectorAPC);
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[Count].LEFTvectorAPC);
		Q_Forge->Forge[Count].LEFTvectorAPC.y = 0;

		Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[Count].LEFTvectorAPC, &Q_Forge->Forge[Count].INvectorAPC, &Q_Forge->Forge[Count].UPvectorAPC);
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[Count].UPvectorAPC);

		if(Q_Forge->Forge[Count].INvectorAPC.y != 1)
			{
			Q_WindWake->WindWake[Count].VecIn = Q_Forge->Forge[Count].INvectorAPC;
			Q_WindWake->WindWake[Count].VecUp = Q_Forge->Forge[Count].UPvectorAPC;
			Q_WindWake->WindWake[Count].VecLeft = Q_Forge->Forge[Count].LEFTvectorAPC;
			}
		else
			{
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[Count].AV.Xform, &Q_WindWake->WindWake[Count].VecUp);
			Qpo->Vec3d_Inverse(&Q_WindWake->WindWake[Count].VecUp);
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[Count].AV.Xform, &Q_WindWake->WindWake[Count].VecLeft);
			Q_WindWake->WindWake[Count].VecIn.x = 0;
			Q_WindWake->WindWake[Count].VecIn.y = 1;
			Q_WindWake->WindWake[Count].VecIn.z = 0;
			}

		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, 45, &Q_WindWake->WindWake[Count].VecIn, &Q_WindWake->WindWake[Count].Pos);
		Q_WindWake->WindWake[Count].STRPos = Q_WindWake->WindWake[Count].Pos;

		Q_WindWake->WindWake[Count].Type = QPOLY_TYPE_TRI;
		Q_WindWake->WindWake[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_WindWake->WindWake[Count].ScaleBIT = 1.0f;
		//END INIT

		if(Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkTYPE == 0)
			{
			Q_WindWake->WindWake[Count].MaterialCNT++;
			if(Q_WindWake->WindWake[Count].MaterialCNT < 124) Q_WindWake->WindWake[Count].MaterialCNT = 124;
			if(Q_WindWake->WindWake[Count].MaterialCNT > 136) Q_WindWake->WindWake[Count].MaterialCNT = 124;
			}

		if(Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkTYPE == 1)
			{
			Q_WindWake->WindWake[Count].MaterialCNT++;
			if(Q_WindWake->WindWake[Count].MaterialCNT < 82) Q_WindWake->WindWake[Count].MaterialCNT = 82;
			if(Q_WindWake->WindWake[Count].MaterialCNT > 96) Q_WindWake->WindWake[Count].MaterialCNT = 82;
			}


		//####### Store WindWake Memory
		if(Q_Forge->Forge[Count].WindWake == 1)
			{
			Q_WindWake->WindWake[Count].MeMPos = Q_WindWake->WindWake[Count].Pos;
			Q_WindWake->WindWake[Count].MeMScale = Q_WindWake->WindWake[Count].Scale;
			Q_WindWake->WindWake[Count].MeMAlphaMAX = Q_WindWake->WindWake[Count].AlphaMAX;

			Q_WindWake->WindWake[Count].MeMINvectorAPC = Q_Forge->Forge[Count].INvectorAPC;

			Q_WindWake->WindWake[Count].MeMJinkSpecialON = Q_Forge->Forge[Count].JinkSpecialON;
			}


			//### FRONT VERT
		Q_WindWake->WindWake[Count].VertFNT = Q_WindWake->WindWake[Count].STRPos;


			//### Shift Back for second ring					//15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/20, &Q_WindWake->WindWake[Count].VecIn, &Q_WindWake->WindWake[Count].Pos);


			//##### RING TWO
					//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/8, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM1);

					//TOP VERT15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM15);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM15, -Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM15);

					//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM2);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM2, -Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM2);

					//TOP VERT25
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM25);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM25, -Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM25);

					//TOP VERT3
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/8, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM3);

					//TOP VERT35
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM35);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM35, -Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM35);

					//TOP VERT4
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM4);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM4, -Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM4);

					//TOP VERT45
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM45);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM45, -Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM45);

					//TOP VERT5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/8, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM5);

					//TOP VERT55
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM55);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM55, Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM55);

					//TOP VERT6
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM6);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM6, Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM6);

					//TOP VERT65
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM65);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM65, Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM65);

					//TOP VERT7
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/8, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM7);

					//TOP VERT75
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM75);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM75, Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM75);

					//TOP VERT8
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM8);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM8, Q_WindWake->WindWake[Count].Scale/11.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM8);

					//TOP VERT85
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/9, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertM85);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertM85, Q_WindWake->WindWake[Count].Scale/14.75, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertM85);



			//### Shift Back for first ring					//4   11
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/5, &Q_WindWake->WindWake[Count].VecIn, &Q_WindWake->WindWake[Count].Pos);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].STRPos, -Q_WindWake->WindWake[Count].Scale/5, &Q_WindWake->WindWake[Count].VecIn, &Q_WindWake->WindWake[Count].STRPos);
		
		
			//##### RING ONE
					//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT1);

					//TOP VERT15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT15);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT15, -Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT15);

					//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT2);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT2, -Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT2);

					//TOP VERT25
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT25);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT25, -Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT25);

					//TOP VERT3
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT3);

					//TOP VERT35
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT35);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT35, -Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT35);

					//TOP VERT4
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT4);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT4, -Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT4);

					//TOP VERT45
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT45);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT45, -Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT45);

					//TOP VERT5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT5);

					//TOP VERT55
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT55);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT55, Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT55);

					//TOP VERT6
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT6);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT6, Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT6);

					//TOP VERT65
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT65);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT65, Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT65);

					//TOP VERT7
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT7);

					//TOP VERT75
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT75);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT75, Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT75);

					//TOP VERT8
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT8);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT8, Q_WindWake->WindWake[Count].Scale/4, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT8);

					//TOP VERT85
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3.15, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertT85);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertT85, Q_WindWake->WindWake[Count].Scale/11, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertT85);


			//### Shift Back for second ring				// 3 <- V GOOD         3.5	4.5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3.35, &Q_WindWake->WindWake[Count].VecIn, &Q_WindWake->WindWake[Count].Pos);


			//##### RING TWO
					//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/2.7, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB1);

					//TOP VERT15
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB15);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB15, -Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB15);

					//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB2);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB2, -Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB2);

					//TOP VERT25
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB25);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB25, -Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB25);

					//TOP VERT3
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/2.7, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB3);

					//TOP VERT35
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB35);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB35, -Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB35);

					//TOP VERT4
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB4);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB4, -Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB4);

					//TOP VERT45
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB45);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB45, -Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB45);

					//TOP VERT5
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/2.7, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB5);

					//TOP VERT55
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB55);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB55, Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB55);

					//TOP VERT6
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB6);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB6, Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB6);

					//TOP VERT65
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, -Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB65);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB65, Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB65);

					//TOP VERT7
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/2.7, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB7);

					//TOP VERT75
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB75);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB75, Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB75);

					//TOP VERT8
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB8);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB8, Q_WindWake->WindWake[Count].Scale/3.5, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB8);

					//TOP VERT85
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].Pos, Q_WindWake->WindWake[Count].Scale/3, &Q_WindWake->WindWake[Count].VecUp, &Q_WindWake->WindWake[Count].VertB85);
		Qpo->Vec3d_AddScaled(&Q_WindWake->WindWake[Count].VertB85, Q_WindWake->WindWake[Count].Scale/8.2, &Q_WindWake->WindWake[Count].VecLeft, &Q_WindWake->WindWake[Count].VertB85);


				int a=0;
				while( a <= 47 )
					{
					int b=0;
					while( b <= 3 )
						{
						if(Q_Forge->Forge[Count].WindWake == 1)
							{
							if(Q_Forge->Forge[Count].JinkSpecialON < 1)
								{
								Q_WindWake->WindWake[Count].Lvert[a][b].a = Q_WindWake->WindWake[Count].MAINALPHA / 3;
								Q_WindWake->WindWake[Count].Lvert[a][b].b = 255;
								Q_WindWake->WindWake[Count].Lvert[a][b].g = 255;
								Q_WindWake->WindWake[Count].Lvert[a][b].r = 255;
								}
							else
								{
								Q_WindWake->WindWake[Count].Lvert[a][b].a = Q_WindWake->WindWake[Count].MAINALPHA / 3;
								Q_WindWake->WindWake[Count].Lvert[a][b].b = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkBLUE;	//135
								Q_WindWake->WindWake[Count].Lvert[a][b].g = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkGREEN;
								Q_WindWake->WindWake[Count].Lvert[a][b].r = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkRED;
								}
							}
						else
							{
							if(Q_WindWake->WindWake[Count].MeMJinkSpecialON < 1)
								{
								Q_WindWake->WindWake[Count].Lvert[a][b].a = Q_WindWake->WindWake[Count].MAINALPHA / 3;
								Q_WindWake->WindWake[Count].Lvert[a][b].b = 255;
								Q_WindWake->WindWake[Count].Lvert[a][b].g = 255;
								Q_WindWake->WindWake[Count].Lvert[a][b].r = 255;
								}
							else
								{
								Q_WindWake->WindWake[Count].Lvert[a][b].a = Q_WindWake->WindWake[Count].MAINALPHA / 3;
								Q_WindWake->WindWake[Count].Lvert[a][b].b = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkBLUE;	//135
								Q_WindWake->WindWake[Count].Lvert[a][b].g = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkGREEN;
								Q_WindWake->WindWake[Count].Lvert[a][b].r = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkRED;
								}
							}
						b++;
						}
					a++;
					}


					//##### - FRONT CUP

					Q_WindWake->WindWake[Count].Lvert[0][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[0][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[0][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[0][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[0][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[0][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[0][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[0][1].x = Q_WindWake->WindWake[Count].VertM15.x;
					Q_WindWake->WindWake[Count].Lvert[0][1].y = Q_WindWake->WindWake[Count].VertM15.y;
					Q_WindWake->WindWake[Count].Lvert[0][1].z = Q_WindWake->WindWake[Count].VertM15.z;

					
					Q_WindWake->WindWake[Count].Lvert[0][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[0][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[0][2].x = Q_WindWake->WindWake[Count].VertM1.x;
					Q_WindWake->WindWake[Count].Lvert[0][2].y = Q_WindWake->WindWake[Count].VertM1.y;
					Q_WindWake->WindWake[Count].Lvert[0][2].z = Q_WindWake->WindWake[Count].VertM1.z;


					Q_WindWake->WindWake[Count].Lvert[1][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[1][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[1][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[1][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[1][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[1][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[1][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[1][1].x = Q_WindWake->WindWake[Count].VertM25.x;
					Q_WindWake->WindWake[Count].Lvert[1][1].y = Q_WindWake->WindWake[Count].VertM25.y;
					Q_WindWake->WindWake[Count].Lvert[1][1].z = Q_WindWake->WindWake[Count].VertM25.z;

							
					Q_WindWake->WindWake[Count].Lvert[1][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[1][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[1][2].x = Q_WindWake->WindWake[Count].VertM2.x;
					Q_WindWake->WindWake[Count].Lvert[1][2].y = Q_WindWake->WindWake[Count].VertM2.y;
					Q_WindWake->WindWake[Count].Lvert[1][2].z = Q_WindWake->WindWake[Count].VertM2.z;


					Q_WindWake->WindWake[Count].Lvert[2][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[2][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[2][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[2][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[2][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[2][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[2][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[2][1].x = Q_WindWake->WindWake[Count].VertM35.x;
					Q_WindWake->WindWake[Count].Lvert[2][1].y = Q_WindWake->WindWake[Count].VertM35.y;
					Q_WindWake->WindWake[Count].Lvert[2][1].z = Q_WindWake->WindWake[Count].VertM35.z;

							
					Q_WindWake->WindWake[Count].Lvert[2][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[2][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[2][2].x = Q_WindWake->WindWake[Count].VertM3.x;
					Q_WindWake->WindWake[Count].Lvert[2][2].y = Q_WindWake->WindWake[Count].VertM3.y;
					Q_WindWake->WindWake[Count].Lvert[2][2].z = Q_WindWake->WindWake[Count].VertM3.z;


					Q_WindWake->WindWake[Count].Lvert[3][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[3][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[3][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[3][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[3][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[3][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[3][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[3][1].x = Q_WindWake->WindWake[Count].VertM45.x;
					Q_WindWake->WindWake[Count].Lvert[3][1].y = Q_WindWake->WindWake[Count].VertM45.y;
					Q_WindWake->WindWake[Count].Lvert[3][1].z = Q_WindWake->WindWake[Count].VertM45.z;

							
					Q_WindWake->WindWake[Count].Lvert[3][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[3][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[3][2].x = Q_WindWake->WindWake[Count].VertM4.x;
					Q_WindWake->WindWake[Count].Lvert[3][2].y = Q_WindWake->WindWake[Count].VertM4.y;
					Q_WindWake->WindWake[Count].Lvert[3][2].z = Q_WindWake->WindWake[Count].VertM4.z;


					Q_WindWake->WindWake[Count].Lvert[4][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[4][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[4][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[4][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[4][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[4][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[4][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[4][1].x = Q_WindWake->WindWake[Count].VertM55.x;
					Q_WindWake->WindWake[Count].Lvert[4][1].y = Q_WindWake->WindWake[Count].VertM55.y;
					Q_WindWake->WindWake[Count].Lvert[4][1].z = Q_WindWake->WindWake[Count].VertM55.z;

							
					Q_WindWake->WindWake[Count].Lvert[4][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[4][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[4][2].x = Q_WindWake->WindWake[Count].VertM5.x;
					Q_WindWake->WindWake[Count].Lvert[4][2].y = Q_WindWake->WindWake[Count].VertM5.y;
					Q_WindWake->WindWake[Count].Lvert[4][2].z = Q_WindWake->WindWake[Count].VertM5.z;


					Q_WindWake->WindWake[Count].Lvert[5][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[5][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[5][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[5][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[5][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[5][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[5][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[5][1].x = Q_WindWake->WindWake[Count].VertM65.x;
					Q_WindWake->WindWake[Count].Lvert[5][1].y = Q_WindWake->WindWake[Count].VertM65.y;
					Q_WindWake->WindWake[Count].Lvert[5][1].z = Q_WindWake->WindWake[Count].VertM65.z;

							
					Q_WindWake->WindWake[Count].Lvert[5][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[5][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[5][2].x = Q_WindWake->WindWake[Count].VertM6.x;
					Q_WindWake->WindWake[Count].Lvert[5][2].y = Q_WindWake->WindWake[Count].VertM6.y;
					Q_WindWake->WindWake[Count].Lvert[5][2].z = Q_WindWake->WindWake[Count].VertM6.z;


					Q_WindWake->WindWake[Count].Lvert[6][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[6][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[6][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[6][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[6][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[6][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[6][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[6][1].x = Q_WindWake->WindWake[Count].VertM75.x;
					Q_WindWake->WindWake[Count].Lvert[6][1].y = Q_WindWake->WindWake[Count].VertM75.y;
					Q_WindWake->WindWake[Count].Lvert[6][1].z = Q_WindWake->WindWake[Count].VertM75.z;

							
					Q_WindWake->WindWake[Count].Lvert[6][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[6][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[6][2].x = Q_WindWake->WindWake[Count].VertM7.x;
					Q_WindWake->WindWake[Count].Lvert[6][2].y = Q_WindWake->WindWake[Count].VertM7.y;
					Q_WindWake->WindWake[Count].Lvert[6][2].z = Q_WindWake->WindWake[Count].VertM7.z;


					Q_WindWake->WindWake[Count].Lvert[7][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[7][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[7][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[7][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[7][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[7][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[7][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[7][1].x = Q_WindWake->WindWake[Count].VertM85.x;
					Q_WindWake->WindWake[Count].Lvert[7][1].y = Q_WindWake->WindWake[Count].VertM85.y;
					Q_WindWake->WindWake[Count].Lvert[7][1].z = Q_WindWake->WindWake[Count].VertM85.z;

							
					Q_WindWake->WindWake[Count].Lvert[7][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[7][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[7][2].x = Q_WindWake->WindWake[Count].VertM8.x;
					Q_WindWake->WindWake[Count].Lvert[7][2].y = Q_WindWake->WindWake[Count].VertM8.y;
					Q_WindWake->WindWake[Count].Lvert[7][2].z = Q_WindWake->WindWake[Count].VertM8.z;


					Q_WindWake->WindWake[Count].Lvert[8][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[8][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[8][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[8][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[8][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[8][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[8][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[8][1].x = Q_WindWake->WindWake[Count].VertM2.x;
					Q_WindWake->WindWake[Count].Lvert[8][1].y = Q_WindWake->WindWake[Count].VertM2.y;
					Q_WindWake->WindWake[Count].Lvert[8][1].z = Q_WindWake->WindWake[Count].VertM2.z;

					
					Q_WindWake->WindWake[Count].Lvert[8][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[8][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[8][2].x = Q_WindWake->WindWake[Count].VertM15.x;
					Q_WindWake->WindWake[Count].Lvert[8][2].y = Q_WindWake->WindWake[Count].VertM15.y;
					Q_WindWake->WindWake[Count].Lvert[8][2].z = Q_WindWake->WindWake[Count].VertM15.z;


					Q_WindWake->WindWake[Count].Lvert[9][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[9][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[9][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[9][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[9][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[9][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[9][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[9][1].x = Q_WindWake->WindWake[Count].VertM3.x;
					Q_WindWake->WindWake[Count].Lvert[9][1].y = Q_WindWake->WindWake[Count].VertM3.y;
					Q_WindWake->WindWake[Count].Lvert[9][1].z = Q_WindWake->WindWake[Count].VertM3.z;

							
					Q_WindWake->WindWake[Count].Lvert[9][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[9][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[9][2].x = Q_WindWake->WindWake[Count].VertM25.x;
					Q_WindWake->WindWake[Count].Lvert[9][2].y = Q_WindWake->WindWake[Count].VertM25.y;
					Q_WindWake->WindWake[Count].Lvert[9][2].z = Q_WindWake->WindWake[Count].VertM25.z;


					Q_WindWake->WindWake[Count].Lvert[10][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[10][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[10][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[10][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[10][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[10][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[10][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[10][1].x = Q_WindWake->WindWake[Count].VertM4.x;
					Q_WindWake->WindWake[Count].Lvert[10][1].y = Q_WindWake->WindWake[Count].VertM4.y;
					Q_WindWake->WindWake[Count].Lvert[10][1].z = Q_WindWake->WindWake[Count].VertM4.z;

							
					Q_WindWake->WindWake[Count].Lvert[10][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[10][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[10][2].x = Q_WindWake->WindWake[Count].VertM35.x;
					Q_WindWake->WindWake[Count].Lvert[10][2].y = Q_WindWake->WindWake[Count].VertM35.y;
					Q_WindWake->WindWake[Count].Lvert[10][2].z = Q_WindWake->WindWake[Count].VertM35.z;


					Q_WindWake->WindWake[Count].Lvert[11][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[11][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[11][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[11][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[11][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[11][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[11][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[11][1].x = Q_WindWake->WindWake[Count].VertM5.x;
					Q_WindWake->WindWake[Count].Lvert[11][1].y = Q_WindWake->WindWake[Count].VertM5.y;
					Q_WindWake->WindWake[Count].Lvert[11][1].z = Q_WindWake->WindWake[Count].VertM5.z;

							
					Q_WindWake->WindWake[Count].Lvert[11][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[11][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[11][2].x = Q_WindWake->WindWake[Count].VertM45.x;
					Q_WindWake->WindWake[Count].Lvert[11][2].y = Q_WindWake->WindWake[Count].VertM45.y;
					Q_WindWake->WindWake[Count].Lvert[11][2].z = Q_WindWake->WindWake[Count].VertM45.z;


					Q_WindWake->WindWake[Count].Lvert[12][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[12][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[12][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[12][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[12][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[12][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[12][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[12][1].x = Q_WindWake->WindWake[Count].VertM6.x;
					Q_WindWake->WindWake[Count].Lvert[12][1].y = Q_WindWake->WindWake[Count].VertM6.y;
					Q_WindWake->WindWake[Count].Lvert[12][1].z = Q_WindWake->WindWake[Count].VertM6.z;

							
					Q_WindWake->WindWake[Count].Lvert[12][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[12][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[12][2].x = Q_WindWake->WindWake[Count].VertM55.x;
					Q_WindWake->WindWake[Count].Lvert[12][2].y = Q_WindWake->WindWake[Count].VertM55.y;
					Q_WindWake->WindWake[Count].Lvert[12][2].z = Q_WindWake->WindWake[Count].VertM55.z;


					Q_WindWake->WindWake[Count].Lvert[13][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[13][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[13][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[13][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[13][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[13][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[13][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[13][1].x = Q_WindWake->WindWake[Count].VertM7.x;
					Q_WindWake->WindWake[Count].Lvert[13][1].y = Q_WindWake->WindWake[Count].VertM7.y;
					Q_WindWake->WindWake[Count].Lvert[13][1].z = Q_WindWake->WindWake[Count].VertM7.z;

							
					Q_WindWake->WindWake[Count].Lvert[13][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[13][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[13][2].x = Q_WindWake->WindWake[Count].VertM65.x;
					Q_WindWake->WindWake[Count].Lvert[13][2].y = Q_WindWake->WindWake[Count].VertM65.y;
					Q_WindWake->WindWake[Count].Lvert[13][2].z = Q_WindWake->WindWake[Count].VertM65.z;


					Q_WindWake->WindWake[Count].Lvert[14][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[14][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[14][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[14][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[14][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[14][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[14][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[14][1].x = Q_WindWake->WindWake[Count].VertM8.x;
					Q_WindWake->WindWake[Count].Lvert[14][1].y = Q_WindWake->WindWake[Count].VertM8.y;
					Q_WindWake->WindWake[Count].Lvert[14][1].z = Q_WindWake->WindWake[Count].VertM8.z;

							
					Q_WindWake->WindWake[Count].Lvert[14][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[14][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[14][2].x = Q_WindWake->WindWake[Count].VertM75.x;
					Q_WindWake->WindWake[Count].Lvert[14][2].y = Q_WindWake->WindWake[Count].VertM75.y;
					Q_WindWake->WindWake[Count].Lvert[14][2].z = Q_WindWake->WindWake[Count].VertM75.z;


					Q_WindWake->WindWake[Count].Lvert[15][0].u = 0.5;
					Q_WindWake->WindWake[Count].Lvert[15][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[15][0].x = Q_WindWake->WindWake[Count].VertFNT.x;
					Q_WindWake->WindWake[Count].Lvert[15][0].y = Q_WindWake->WindWake[Count].VertFNT.y;
					Q_WindWake->WindWake[Count].Lvert[15][0].z = Q_WindWake->WindWake[Count].VertFNT.z;

							
					Q_WindWake->WindWake[Count].Lvert[15][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[15][1].v = 1;
					Q_WindWake->WindWake[Count].Lvert[15][1].x = Q_WindWake->WindWake[Count].VertM1.x;
					Q_WindWake->WindWake[Count].Lvert[15][1].y = Q_WindWake->WindWake[Count].VertM1.y;
					Q_WindWake->WindWake[Count].Lvert[15][1].z = Q_WindWake->WindWake[Count].VertM1.z;

							
					Q_WindWake->WindWake[Count].Lvert[15][2].u = 0;
					Q_WindWake->WindWake[Count].Lvert[15][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[15][2].x = Q_WindWake->WindWake[Count].VertM85.x;
					Q_WindWake->WindWake[Count].Lvert[15][2].y = Q_WindWake->WindWake[Count].VertM85.y;
					Q_WindWake->WindWake[Count].Lvert[15][2].z = Q_WindWake->WindWake[Count].VertM85.z;


					//##### - SOLID RING ONE

					Q_WindWake->WindWake[Count].Lvert[16][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[16][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[16][0].x = Q_WindWake->WindWake[Count].VertM1.x;
					Q_WindWake->WindWake[Count].Lvert[16][0].y = Q_WindWake->WindWake[Count].VertM1.y;
					Q_WindWake->WindWake[Count].Lvert[16][0].z = Q_WindWake->WindWake[Count].VertM1.z;

					
					Q_WindWake->WindWake[Count].Lvert[16][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[16][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[16][1].x = Q_WindWake->WindWake[Count].VertM15.x;
					Q_WindWake->WindWake[Count].Lvert[16][1].y = Q_WindWake->WindWake[Count].VertM15.y;
					Q_WindWake->WindWake[Count].Lvert[16][1].z = Q_WindWake->WindWake[Count].VertM15.z;

							
					Q_WindWake->WindWake[Count].Lvert[16][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[16][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[16][2].x = Q_WindWake->WindWake[Count].VertT15.x;
					Q_WindWake->WindWake[Count].Lvert[16][2].y = Q_WindWake->WindWake[Count].VertT15.y;
					Q_WindWake->WindWake[Count].Lvert[16][2].z = Q_WindWake->WindWake[Count].VertT15.z;


					Q_WindWake->WindWake[Count].Lvert[16][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[16][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[16][3].x = Q_WindWake->WindWake[Count].VertT1.x;
					Q_WindWake->WindWake[Count].Lvert[16][3].y = Q_WindWake->WindWake[Count].VertT1.y;
					Q_WindWake->WindWake[Count].Lvert[16][3].z = Q_WindWake->WindWake[Count].VertT1.z;


					Q_WindWake->WindWake[Count].Lvert[17][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[17][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[17][0].x = Q_WindWake->WindWake[Count].VertM15.x;
					Q_WindWake->WindWake[Count].Lvert[17][0].y = Q_WindWake->WindWake[Count].VertM15.y;
					Q_WindWake->WindWake[Count].Lvert[17][0].z = Q_WindWake->WindWake[Count].VertM15.z;

							
					Q_WindWake->WindWake[Count].Lvert[17][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[17][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[17][1].x = Q_WindWake->WindWake[Count].VertM2.x;
					Q_WindWake->WindWake[Count].Lvert[17][1].y = Q_WindWake->WindWake[Count].VertM2.y;
					Q_WindWake->WindWake[Count].Lvert[17][1].z = Q_WindWake->WindWake[Count].VertM2.z;

							
					Q_WindWake->WindWake[Count].Lvert[17][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[17][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[17][2].x = Q_WindWake->WindWake[Count].VertT2.x;
					Q_WindWake->WindWake[Count].Lvert[17][2].y = Q_WindWake->WindWake[Count].VertT2.y;
					Q_WindWake->WindWake[Count].Lvert[17][2].z = Q_WindWake->WindWake[Count].VertT2.z;


					Q_WindWake->WindWake[Count].Lvert[17][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[17][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[17][3].x = Q_WindWake->WindWake[Count].VertT15.x;
					Q_WindWake->WindWake[Count].Lvert[17][3].y = Q_WindWake->WindWake[Count].VertT15.y;
					Q_WindWake->WindWake[Count].Lvert[17][3].z = Q_WindWake->WindWake[Count].VertT15.z;



					Q_WindWake->WindWake[Count].Lvert[18][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[18][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[18][0].x = Q_WindWake->WindWake[Count].VertM2.x;
					Q_WindWake->WindWake[Count].Lvert[18][0].y = Q_WindWake->WindWake[Count].VertM2.y;
					Q_WindWake->WindWake[Count].Lvert[18][0].z = Q_WindWake->WindWake[Count].VertM2.z;

							
					Q_WindWake->WindWake[Count].Lvert[18][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[18][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[18][1].x = Q_WindWake->WindWake[Count].VertM25.x;
					Q_WindWake->WindWake[Count].Lvert[18][1].y = Q_WindWake->WindWake[Count].VertM25.y;
					Q_WindWake->WindWake[Count].Lvert[18][1].z = Q_WindWake->WindWake[Count].VertM25.z;

							
					Q_WindWake->WindWake[Count].Lvert[18][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[18][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[18][2].x = Q_WindWake->WindWake[Count].VertT25.x;
					Q_WindWake->WindWake[Count].Lvert[18][2].y = Q_WindWake->WindWake[Count].VertT25.y;
					Q_WindWake->WindWake[Count].Lvert[18][2].z = Q_WindWake->WindWake[Count].VertT25.z;


					Q_WindWake->WindWake[Count].Lvert[18][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[18][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[18][3].x = Q_WindWake->WindWake[Count].VertT2.x;
					Q_WindWake->WindWake[Count].Lvert[18][3].y = Q_WindWake->WindWake[Count].VertT2.y;
					Q_WindWake->WindWake[Count].Lvert[18][3].z = Q_WindWake->WindWake[Count].VertT2.z;



					Q_WindWake->WindWake[Count].Lvert[19][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[19][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[19][0].x = Q_WindWake->WindWake[Count].VertM25.x;
					Q_WindWake->WindWake[Count].Lvert[19][0].y = Q_WindWake->WindWake[Count].VertM25.y;
					Q_WindWake->WindWake[Count].Lvert[19][0].z = Q_WindWake->WindWake[Count].VertM25.z;

							
					Q_WindWake->WindWake[Count].Lvert[19][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[19][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[19][1].x = Q_WindWake->WindWake[Count].VertM3.x;
					Q_WindWake->WindWake[Count].Lvert[19][1].y = Q_WindWake->WindWake[Count].VertM3.y;
					Q_WindWake->WindWake[Count].Lvert[19][1].z = Q_WindWake->WindWake[Count].VertM3.z;

							
					Q_WindWake->WindWake[Count].Lvert[19][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[19][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[19][2].x = Q_WindWake->WindWake[Count].VertT3.x;
					Q_WindWake->WindWake[Count].Lvert[19][2].y = Q_WindWake->WindWake[Count].VertT3.y;
					Q_WindWake->WindWake[Count].Lvert[19][2].z = Q_WindWake->WindWake[Count].VertT3.z;


					Q_WindWake->WindWake[Count].Lvert[19][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[19][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[19][3].x = Q_WindWake->WindWake[Count].VertT25.x;
					Q_WindWake->WindWake[Count].Lvert[19][3].y = Q_WindWake->WindWake[Count].VertT25.y;
					Q_WindWake->WindWake[Count].Lvert[19][3].z = Q_WindWake->WindWake[Count].VertT25.z;


					Q_WindWake->WindWake[Count].Lvert[20][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[20][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[20][0].x = Q_WindWake->WindWake[Count].VertM3.x;
					Q_WindWake->WindWake[Count].Lvert[20][0].y = Q_WindWake->WindWake[Count].VertM3.y;
					Q_WindWake->WindWake[Count].Lvert[20][0].z = Q_WindWake->WindWake[Count].VertM3.z;

							
					Q_WindWake->WindWake[Count].Lvert[20][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[20][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[20][1].x = Q_WindWake->WindWake[Count].VertM35.x;
					Q_WindWake->WindWake[Count].Lvert[20][1].y = Q_WindWake->WindWake[Count].VertM35.y;
					Q_WindWake->WindWake[Count].Lvert[20][1].z = Q_WindWake->WindWake[Count].VertM35.z;

							
					Q_WindWake->WindWake[Count].Lvert[20][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[20][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[20][2].x = Q_WindWake->WindWake[Count].VertT35.x;
					Q_WindWake->WindWake[Count].Lvert[20][2].y = Q_WindWake->WindWake[Count].VertT35.y;
					Q_WindWake->WindWake[Count].Lvert[20][2].z = Q_WindWake->WindWake[Count].VertT35.z;


					Q_WindWake->WindWake[Count].Lvert[20][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[20][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[20][3].x = Q_WindWake->WindWake[Count].VertT3.x;
					Q_WindWake->WindWake[Count].Lvert[20][3].y = Q_WindWake->WindWake[Count].VertT3.y;
					Q_WindWake->WindWake[Count].Lvert[20][3].z = Q_WindWake->WindWake[Count].VertT3.z;


					Q_WindWake->WindWake[Count].Lvert[21][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[21][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[21][0].x = Q_WindWake->WindWake[Count].VertM35.x;
					Q_WindWake->WindWake[Count].Lvert[21][0].y = Q_WindWake->WindWake[Count].VertM35.y;
					Q_WindWake->WindWake[Count].Lvert[21][0].z = Q_WindWake->WindWake[Count].VertM35.z;

							
					Q_WindWake->WindWake[Count].Lvert[21][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[21][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[21][1].x = Q_WindWake->WindWake[Count].VertM4.x;
					Q_WindWake->WindWake[Count].Lvert[21][1].y = Q_WindWake->WindWake[Count].VertM4.y;
					Q_WindWake->WindWake[Count].Lvert[21][1].z = Q_WindWake->WindWake[Count].VertM4.z;

							
					Q_WindWake->WindWake[Count].Lvert[21][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[21][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[21][2].x = Q_WindWake->WindWake[Count].VertT4.x;
					Q_WindWake->WindWake[Count].Lvert[21][2].y = Q_WindWake->WindWake[Count].VertT4.y;
					Q_WindWake->WindWake[Count].Lvert[21][2].z = Q_WindWake->WindWake[Count].VertT4.z;


					Q_WindWake->WindWake[Count].Lvert[21][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[21][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[21][3].x = Q_WindWake->WindWake[Count].VertT35.x;
					Q_WindWake->WindWake[Count].Lvert[21][3].y = Q_WindWake->WindWake[Count].VertT35.y;
					Q_WindWake->WindWake[Count].Lvert[21][3].z = Q_WindWake->WindWake[Count].VertT35.z;


					Q_WindWake->WindWake[Count].Lvert[22][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[22][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[22][0].x = Q_WindWake->WindWake[Count].VertM4.x;
					Q_WindWake->WindWake[Count].Lvert[22][0].y = Q_WindWake->WindWake[Count].VertM4.y;
					Q_WindWake->WindWake[Count].Lvert[22][0].z = Q_WindWake->WindWake[Count].VertM4.z;

							
					Q_WindWake->WindWake[Count].Lvert[22][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[22][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[22][1].x = Q_WindWake->WindWake[Count].VertM45.x;
					Q_WindWake->WindWake[Count].Lvert[22][1].y = Q_WindWake->WindWake[Count].VertM45.y;
					Q_WindWake->WindWake[Count].Lvert[22][1].z = Q_WindWake->WindWake[Count].VertM45.z;

							
					Q_WindWake->WindWake[Count].Lvert[22][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[22][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[22][2].x = Q_WindWake->WindWake[Count].VertT45.x;
					Q_WindWake->WindWake[Count].Lvert[22][2].y = Q_WindWake->WindWake[Count].VertT45.y;
					Q_WindWake->WindWake[Count].Lvert[22][2].z = Q_WindWake->WindWake[Count].VertT45.z;


					Q_WindWake->WindWake[Count].Lvert[22][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[22][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[22][3].x = Q_WindWake->WindWake[Count].VertT4.x;
					Q_WindWake->WindWake[Count].Lvert[22][3].y = Q_WindWake->WindWake[Count].VertT4.y;
					Q_WindWake->WindWake[Count].Lvert[22][3].z = Q_WindWake->WindWake[Count].VertT4.z;



					Q_WindWake->WindWake[Count].Lvert[23][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[23][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[23][0].x = Q_WindWake->WindWake[Count].VertM45.x;
					Q_WindWake->WindWake[Count].Lvert[23][0].y = Q_WindWake->WindWake[Count].VertM45.y;
					Q_WindWake->WindWake[Count].Lvert[23][0].z = Q_WindWake->WindWake[Count].VertM45.z;

							
					Q_WindWake->WindWake[Count].Lvert[23][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[23][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[23][1].x = Q_WindWake->WindWake[Count].VertM5.x;
					Q_WindWake->WindWake[Count].Lvert[23][1].y = Q_WindWake->WindWake[Count].VertM5.y;
					Q_WindWake->WindWake[Count].Lvert[23][1].z = Q_WindWake->WindWake[Count].VertM5.z;

							
					Q_WindWake->WindWake[Count].Lvert[23][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[23][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[23][2].x = Q_WindWake->WindWake[Count].VertT5.x;
					Q_WindWake->WindWake[Count].Lvert[23][2].y = Q_WindWake->WindWake[Count].VertT5.y;
					Q_WindWake->WindWake[Count].Lvert[23][2].z = Q_WindWake->WindWake[Count].VertT5.z;


					Q_WindWake->WindWake[Count].Lvert[23][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[23][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[23][3].x = Q_WindWake->WindWake[Count].VertT45.x;
					Q_WindWake->WindWake[Count].Lvert[23][3].y = Q_WindWake->WindWake[Count].VertT45.y;
					Q_WindWake->WindWake[Count].Lvert[23][3].z = Q_WindWake->WindWake[Count].VertT45.z;


					Q_WindWake->WindWake[Count].Lvert[24][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[24][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[24][0].x = Q_WindWake->WindWake[Count].VertM5.x;
					Q_WindWake->WindWake[Count].Lvert[24][0].y = Q_WindWake->WindWake[Count].VertM5.y;
					Q_WindWake->WindWake[Count].Lvert[24][0].z = Q_WindWake->WindWake[Count].VertM5.z;

					
					Q_WindWake->WindWake[Count].Lvert[24][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[24][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[24][1].x = Q_WindWake->WindWake[Count].VertM55.x;
					Q_WindWake->WindWake[Count].Lvert[24][1].y = Q_WindWake->WindWake[Count].VertM55.y;
					Q_WindWake->WindWake[Count].Lvert[24][1].z = Q_WindWake->WindWake[Count].VertM55.z;

							
					Q_WindWake->WindWake[Count].Lvert[24][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[24][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[24][2].x = Q_WindWake->WindWake[Count].VertT55.x;
					Q_WindWake->WindWake[Count].Lvert[24][2].y = Q_WindWake->WindWake[Count].VertT55.y;
					Q_WindWake->WindWake[Count].Lvert[24][2].z = Q_WindWake->WindWake[Count].VertT55.z;


					Q_WindWake->WindWake[Count].Lvert[24][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[24][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[24][3].x = Q_WindWake->WindWake[Count].VertT5.x;
					Q_WindWake->WindWake[Count].Lvert[24][3].y = Q_WindWake->WindWake[Count].VertT5.y;
					Q_WindWake->WindWake[Count].Lvert[24][3].z = Q_WindWake->WindWake[Count].VertT5.z;


					Q_WindWake->WindWake[Count].Lvert[25][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[25][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[25][0].x = Q_WindWake->WindWake[Count].VertM55.x;
					Q_WindWake->WindWake[Count].Lvert[25][0].y = Q_WindWake->WindWake[Count].VertM55.y;
					Q_WindWake->WindWake[Count].Lvert[25][0].z = Q_WindWake->WindWake[Count].VertM55.z;

							
					Q_WindWake->WindWake[Count].Lvert[25][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[25][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[25][1].x = Q_WindWake->WindWake[Count].VertM6.x;
					Q_WindWake->WindWake[Count].Lvert[25][1].y = Q_WindWake->WindWake[Count].VertM6.y;
					Q_WindWake->WindWake[Count].Lvert[25][1].z = Q_WindWake->WindWake[Count].VertM6.z;

							
					Q_WindWake->WindWake[Count].Lvert[25][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[25][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[25][2].x = Q_WindWake->WindWake[Count].VertT6.x;
					Q_WindWake->WindWake[Count].Lvert[25][2].y = Q_WindWake->WindWake[Count].VertT6.y;
					Q_WindWake->WindWake[Count].Lvert[25][2].z = Q_WindWake->WindWake[Count].VertT6.z;


					Q_WindWake->WindWake[Count].Lvert[25][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[25][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[25][3].x = Q_WindWake->WindWake[Count].VertT55.x;
					Q_WindWake->WindWake[Count].Lvert[25][3].y = Q_WindWake->WindWake[Count].VertT55.y;
					Q_WindWake->WindWake[Count].Lvert[25][3].z = Q_WindWake->WindWake[Count].VertT55.z;


					Q_WindWake->WindWake[Count].Lvert[26][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[26][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[26][0].x = Q_WindWake->WindWake[Count].VertM6.x;
					Q_WindWake->WindWake[Count].Lvert[26][0].y = Q_WindWake->WindWake[Count].VertM6.y;
					Q_WindWake->WindWake[Count].Lvert[26][0].z = Q_WindWake->WindWake[Count].VertM6.z;

							
					Q_WindWake->WindWake[Count].Lvert[26][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[26][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[26][1].x = Q_WindWake->WindWake[Count].VertM65.x;
					Q_WindWake->WindWake[Count].Lvert[26][1].y = Q_WindWake->WindWake[Count].VertM65.y;
					Q_WindWake->WindWake[Count].Lvert[26][1].z = Q_WindWake->WindWake[Count].VertM65.z;

							
					Q_WindWake->WindWake[Count].Lvert[26][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[26][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[26][2].x = Q_WindWake->WindWake[Count].VertT65.x;
					Q_WindWake->WindWake[Count].Lvert[26][2].y = Q_WindWake->WindWake[Count].VertT65.y;
					Q_WindWake->WindWake[Count].Lvert[26][2].z = Q_WindWake->WindWake[Count].VertT65.z;


					Q_WindWake->WindWake[Count].Lvert[26][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[26][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[26][3].x = Q_WindWake->WindWake[Count].VertT6.x;
					Q_WindWake->WindWake[Count].Lvert[26][3].y = Q_WindWake->WindWake[Count].VertT6.y;
					Q_WindWake->WindWake[Count].Lvert[26][3].z = Q_WindWake->WindWake[Count].VertT6.z;


					Q_WindWake->WindWake[Count].Lvert[27][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[27][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[27][0].x = Q_WindWake->WindWake[Count].VertM65.x;
					Q_WindWake->WindWake[Count].Lvert[27][0].y = Q_WindWake->WindWake[Count].VertM65.y;
					Q_WindWake->WindWake[Count].Lvert[27][0].z = Q_WindWake->WindWake[Count].VertM65.z;

							
					Q_WindWake->WindWake[Count].Lvert[27][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[27][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[27][1].x = Q_WindWake->WindWake[Count].VertM7.x;
					Q_WindWake->WindWake[Count].Lvert[27][1].y = Q_WindWake->WindWake[Count].VertM7.y;
					Q_WindWake->WindWake[Count].Lvert[27][1].z = Q_WindWake->WindWake[Count].VertM7.z;

							
					Q_WindWake->WindWake[Count].Lvert[27][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[27][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[27][2].x = Q_WindWake->WindWake[Count].VertT7.x;
					Q_WindWake->WindWake[Count].Lvert[27][2].y = Q_WindWake->WindWake[Count].VertT7.y;
					Q_WindWake->WindWake[Count].Lvert[27][2].z = Q_WindWake->WindWake[Count].VertT7.z;


					Q_WindWake->WindWake[Count].Lvert[27][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[27][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[27][3].x = Q_WindWake->WindWake[Count].VertT65.x;
					Q_WindWake->WindWake[Count].Lvert[27][3].y = Q_WindWake->WindWake[Count].VertT65.y;
					Q_WindWake->WindWake[Count].Lvert[27][3].z = Q_WindWake->WindWake[Count].VertT65.z;


					Q_WindWake->WindWake[Count].Lvert[28][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[28][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[28][0].x = Q_WindWake->WindWake[Count].VertM7.x;
					Q_WindWake->WindWake[Count].Lvert[28][0].y = Q_WindWake->WindWake[Count].VertM7.y;
					Q_WindWake->WindWake[Count].Lvert[28][0].z = Q_WindWake->WindWake[Count].VertM7.z;

							
					Q_WindWake->WindWake[Count].Lvert[28][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[28][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[28][1].x = Q_WindWake->WindWake[Count].VertM75.x;
					Q_WindWake->WindWake[Count].Lvert[28][1].y = Q_WindWake->WindWake[Count].VertM75.y;
					Q_WindWake->WindWake[Count].Lvert[28][1].z = Q_WindWake->WindWake[Count].VertM75.z;

							
					Q_WindWake->WindWake[Count].Lvert[28][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[28][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[28][2].x = Q_WindWake->WindWake[Count].VertT75.x;
					Q_WindWake->WindWake[Count].Lvert[28][2].y = Q_WindWake->WindWake[Count].VertT75.y;
					Q_WindWake->WindWake[Count].Lvert[28][2].z = Q_WindWake->WindWake[Count].VertT75.z;


					Q_WindWake->WindWake[Count].Lvert[28][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[28][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[28][3].x = Q_WindWake->WindWake[Count].VertT7.x;
					Q_WindWake->WindWake[Count].Lvert[28][3].y = Q_WindWake->WindWake[Count].VertT7.y;
					Q_WindWake->WindWake[Count].Lvert[28][3].z = Q_WindWake->WindWake[Count].VertT7.z;


					Q_WindWake->WindWake[Count].Lvert[29][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[29][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[29][0].x = Q_WindWake->WindWake[Count].VertM75.x;
					Q_WindWake->WindWake[Count].Lvert[29][0].y = Q_WindWake->WindWake[Count].VertM75.y;
					Q_WindWake->WindWake[Count].Lvert[29][0].z = Q_WindWake->WindWake[Count].VertM75.z;

							
					Q_WindWake->WindWake[Count].Lvert[29][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[29][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[29][1].x = Q_WindWake->WindWake[Count].VertM8.x;
					Q_WindWake->WindWake[Count].Lvert[29][1].y = Q_WindWake->WindWake[Count].VertM8.y;
					Q_WindWake->WindWake[Count].Lvert[29][1].z = Q_WindWake->WindWake[Count].VertM8.z;

							
					Q_WindWake->WindWake[Count].Lvert[29][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[29][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[29][2].x = Q_WindWake->WindWake[Count].VertT8.x;
					Q_WindWake->WindWake[Count].Lvert[29][2].y = Q_WindWake->WindWake[Count].VertT8.y;
					Q_WindWake->WindWake[Count].Lvert[29][2].z = Q_WindWake->WindWake[Count].VertT8.z;


					Q_WindWake->WindWake[Count].Lvert[29][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[29][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[29][3].x = Q_WindWake->WindWake[Count].VertT75.x;
					Q_WindWake->WindWake[Count].Lvert[29][3].y = Q_WindWake->WindWake[Count].VertT75.y;
					Q_WindWake->WindWake[Count].Lvert[29][3].z = Q_WindWake->WindWake[Count].VertT75.z;


					Q_WindWake->WindWake[Count].Lvert[30][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[30][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[30][0].x = Q_WindWake->WindWake[Count].VertM8.x;
					Q_WindWake->WindWake[Count].Lvert[30][0].y = Q_WindWake->WindWake[Count].VertM8.y;
					Q_WindWake->WindWake[Count].Lvert[30][0].z = Q_WindWake->WindWake[Count].VertM8.z;

							
					Q_WindWake->WindWake[Count].Lvert[30][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[30][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[30][1].x = Q_WindWake->WindWake[Count].VertM85.x;
					Q_WindWake->WindWake[Count].Lvert[30][1].y = Q_WindWake->WindWake[Count].VertM85.y;
					Q_WindWake->WindWake[Count].Lvert[30][1].z = Q_WindWake->WindWake[Count].VertM85.z;

							
					Q_WindWake->WindWake[Count].Lvert[30][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[30][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[30][2].x = Q_WindWake->WindWake[Count].VertT85.x;
					Q_WindWake->WindWake[Count].Lvert[30][2].y = Q_WindWake->WindWake[Count].VertT85.y;
					Q_WindWake->WindWake[Count].Lvert[30][2].z = Q_WindWake->WindWake[Count].VertT85.z;


					Q_WindWake->WindWake[Count].Lvert[30][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[30][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[30][3].x = Q_WindWake->WindWake[Count].VertT8.x;
					Q_WindWake->WindWake[Count].Lvert[30][3].y = Q_WindWake->WindWake[Count].VertT8.y;
					Q_WindWake->WindWake[Count].Lvert[30][3].z = Q_WindWake->WindWake[Count].VertT8.z;


					Q_WindWake->WindWake[Count].Lvert[31][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[31][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[31][0].x = Q_WindWake->WindWake[Count].VertM85.x;
					Q_WindWake->WindWake[Count].Lvert[31][0].y = Q_WindWake->WindWake[Count].VertM85.y;
					Q_WindWake->WindWake[Count].Lvert[31][0].z = Q_WindWake->WindWake[Count].VertM85.z;

							
					Q_WindWake->WindWake[Count].Lvert[31][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[31][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[31][1].x = Q_WindWake->WindWake[Count].VertM1.x;
					Q_WindWake->WindWake[Count].Lvert[31][1].y = Q_WindWake->WindWake[Count].VertM1.y;
					Q_WindWake->WindWake[Count].Lvert[31][1].z = Q_WindWake->WindWake[Count].VertM1.z;

							
					Q_WindWake->WindWake[Count].Lvert[31][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[31][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[31][2].x = Q_WindWake->WindWake[Count].VertT1.x;
					Q_WindWake->WindWake[Count].Lvert[31][2].y = Q_WindWake->WindWake[Count].VertT1.y;
					Q_WindWake->WindWake[Count].Lvert[31][2].z = Q_WindWake->WindWake[Count].VertT1.z;


					Q_WindWake->WindWake[Count].Lvert[31][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[31][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[31][3].x = Q_WindWake->WindWake[Count].VertT85.x;
					Q_WindWake->WindWake[Count].Lvert[31][3].y = Q_WindWake->WindWake[Count].VertT85.y;
					Q_WindWake->WindWake[Count].Lvert[31][3].z = Q_WindWake->WindWake[Count].VertT85.z;


					//##### - SOLID RING TWO

					Q_WindWake->WindWake[Count].Lvert[32][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[32][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[32][0].x = Q_WindWake->WindWake[Count].VertT1.x;
					Q_WindWake->WindWake[Count].Lvert[32][0].y = Q_WindWake->WindWake[Count].VertT1.y;
					Q_WindWake->WindWake[Count].Lvert[32][0].z = Q_WindWake->WindWake[Count].VertT1.z;

					
					Q_WindWake->WindWake[Count].Lvert[32][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[32][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[32][1].x = Q_WindWake->WindWake[Count].VertT15.x;
					Q_WindWake->WindWake[Count].Lvert[32][1].y = Q_WindWake->WindWake[Count].VertT15.y;
					Q_WindWake->WindWake[Count].Lvert[32][1].z = Q_WindWake->WindWake[Count].VertT15.z;

							
					Q_WindWake->WindWake[Count].Lvert[32][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[32][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[32][2].x = Q_WindWake->WindWake[Count].VertB15.x;
					Q_WindWake->WindWake[Count].Lvert[32][2].y = Q_WindWake->WindWake[Count].VertB15.y;
					Q_WindWake->WindWake[Count].Lvert[32][2].z = Q_WindWake->WindWake[Count].VertB15.z;


					Q_WindWake->WindWake[Count].Lvert[32][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[32][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[32][3].x = Q_WindWake->WindWake[Count].VertB1.x;
					Q_WindWake->WindWake[Count].Lvert[32][3].y = Q_WindWake->WindWake[Count].VertB1.y;
					Q_WindWake->WindWake[Count].Lvert[32][3].z = Q_WindWake->WindWake[Count].VertB1.z;


					Q_WindWake->WindWake[Count].Lvert[33][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[33][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[33][0].x = Q_WindWake->WindWake[Count].VertT15.x;
					Q_WindWake->WindWake[Count].Lvert[33][0].y = Q_WindWake->WindWake[Count].VertT15.y;
					Q_WindWake->WindWake[Count].Lvert[33][0].z = Q_WindWake->WindWake[Count].VertT15.z;

							
					Q_WindWake->WindWake[Count].Lvert[33][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[33][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[33][1].x = Q_WindWake->WindWake[Count].VertT2.x;
					Q_WindWake->WindWake[Count].Lvert[33][1].y = Q_WindWake->WindWake[Count].VertT2.y;
					Q_WindWake->WindWake[Count].Lvert[33][1].z = Q_WindWake->WindWake[Count].VertT2.z;

							
					Q_WindWake->WindWake[Count].Lvert[33][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[33][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[33][2].x = Q_WindWake->WindWake[Count].VertB2.x;
					Q_WindWake->WindWake[Count].Lvert[33][2].y = Q_WindWake->WindWake[Count].VertB2.y;
					Q_WindWake->WindWake[Count].Lvert[33][2].z = Q_WindWake->WindWake[Count].VertB2.z;


					Q_WindWake->WindWake[Count].Lvert[33][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[33][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[33][3].x = Q_WindWake->WindWake[Count].VertB15.x;
					Q_WindWake->WindWake[Count].Lvert[33][3].y = Q_WindWake->WindWake[Count].VertB15.y;
					Q_WindWake->WindWake[Count].Lvert[33][3].z = Q_WindWake->WindWake[Count].VertB15.z;


					Q_WindWake->WindWake[Count].Lvert[34][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[34][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[34][0].x = Q_WindWake->WindWake[Count].VertT2.x;
					Q_WindWake->WindWake[Count].Lvert[34][0].y = Q_WindWake->WindWake[Count].VertT2.y;
					Q_WindWake->WindWake[Count].Lvert[34][0].z = Q_WindWake->WindWake[Count].VertT2.z;

							
					Q_WindWake->WindWake[Count].Lvert[34][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[34][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[34][1].x = Q_WindWake->WindWake[Count].VertT25.x;
					Q_WindWake->WindWake[Count].Lvert[34][1].y = Q_WindWake->WindWake[Count].VertT25.y;
					Q_WindWake->WindWake[Count].Lvert[34][1].z = Q_WindWake->WindWake[Count].VertT25.z;

							
					Q_WindWake->WindWake[Count].Lvert[34][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[34][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[34][2].x = Q_WindWake->WindWake[Count].VertB25.x;
					Q_WindWake->WindWake[Count].Lvert[34][2].y = Q_WindWake->WindWake[Count].VertB25.y;
					Q_WindWake->WindWake[Count].Lvert[34][2].z = Q_WindWake->WindWake[Count].VertB25.z;


					Q_WindWake->WindWake[Count].Lvert[34][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[34][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[34][3].x = Q_WindWake->WindWake[Count].VertB2.x;
					Q_WindWake->WindWake[Count].Lvert[34][3].y = Q_WindWake->WindWake[Count].VertB2.y;
					Q_WindWake->WindWake[Count].Lvert[34][3].z = Q_WindWake->WindWake[Count].VertB2.z;



					Q_WindWake->WindWake[Count].Lvert[35][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[35][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[35][0].x = Q_WindWake->WindWake[Count].VertT25.x;
					Q_WindWake->WindWake[Count].Lvert[35][0].y = Q_WindWake->WindWake[Count].VertT25.y;
					Q_WindWake->WindWake[Count].Lvert[35][0].z = Q_WindWake->WindWake[Count].VertT25.z;

							
					Q_WindWake->WindWake[Count].Lvert[35][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[35][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[35][1].x = Q_WindWake->WindWake[Count].VertT3.x;
					Q_WindWake->WindWake[Count].Lvert[35][1].y = Q_WindWake->WindWake[Count].VertT3.y;
					Q_WindWake->WindWake[Count].Lvert[35][1].z = Q_WindWake->WindWake[Count].VertT3.z;

							
					Q_WindWake->WindWake[Count].Lvert[35][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[35][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[35][2].x = Q_WindWake->WindWake[Count].VertB3.x;
					Q_WindWake->WindWake[Count].Lvert[35][2].y = Q_WindWake->WindWake[Count].VertB3.y;
					Q_WindWake->WindWake[Count].Lvert[35][2].z = Q_WindWake->WindWake[Count].VertB3.z;


					Q_WindWake->WindWake[Count].Lvert[35][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[35][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[35][3].x = Q_WindWake->WindWake[Count].VertB25.x;
					Q_WindWake->WindWake[Count].Lvert[35][3].y = Q_WindWake->WindWake[Count].VertB25.y;
					Q_WindWake->WindWake[Count].Lvert[35][3].z = Q_WindWake->WindWake[Count].VertB25.z;


					Q_WindWake->WindWake[Count].Lvert[36][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[36][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[36][0].x = Q_WindWake->WindWake[Count].VertT3.x;
					Q_WindWake->WindWake[Count].Lvert[36][0].y = Q_WindWake->WindWake[Count].VertT3.y;
					Q_WindWake->WindWake[Count].Lvert[36][0].z = Q_WindWake->WindWake[Count].VertT3.z;

							
					Q_WindWake->WindWake[Count].Lvert[36][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[36][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[36][1].x = Q_WindWake->WindWake[Count].VertT35.x;
					Q_WindWake->WindWake[Count].Lvert[36][1].y = Q_WindWake->WindWake[Count].VertT35.y;
					Q_WindWake->WindWake[Count].Lvert[36][1].z = Q_WindWake->WindWake[Count].VertT35.z;

							
					Q_WindWake->WindWake[Count].Lvert[36][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[36][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[36][2].x = Q_WindWake->WindWake[Count].VertB35.x;
					Q_WindWake->WindWake[Count].Lvert[36][2].y = Q_WindWake->WindWake[Count].VertB35.y;
					Q_WindWake->WindWake[Count].Lvert[36][2].z = Q_WindWake->WindWake[Count].VertB35.z;


					Q_WindWake->WindWake[Count].Lvert[36][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[36][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[36][3].x = Q_WindWake->WindWake[Count].VertB3.x;
					Q_WindWake->WindWake[Count].Lvert[36][3].y = Q_WindWake->WindWake[Count].VertB3.y;
					Q_WindWake->WindWake[Count].Lvert[36][3].z = Q_WindWake->WindWake[Count].VertB3.z;


					Q_WindWake->WindWake[Count].Lvert[37][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[37][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[37][0].x = Q_WindWake->WindWake[Count].VertT35.x;
					Q_WindWake->WindWake[Count].Lvert[37][0].y = Q_WindWake->WindWake[Count].VertT35.y;
					Q_WindWake->WindWake[Count].Lvert[37][0].z = Q_WindWake->WindWake[Count].VertT35.z;

							
					Q_WindWake->WindWake[Count].Lvert[37][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[37][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[37][1].x = Q_WindWake->WindWake[Count].VertT4.x;
					Q_WindWake->WindWake[Count].Lvert[37][1].y = Q_WindWake->WindWake[Count].VertT4.y;
					Q_WindWake->WindWake[Count].Lvert[37][1].z = Q_WindWake->WindWake[Count].VertT4.z;

							
					Q_WindWake->WindWake[Count].Lvert[37][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[37][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[37][2].x = Q_WindWake->WindWake[Count].VertB4.x;
					Q_WindWake->WindWake[Count].Lvert[37][2].y = Q_WindWake->WindWake[Count].VertB4.y;
					Q_WindWake->WindWake[Count].Lvert[37][2].z = Q_WindWake->WindWake[Count].VertB4.z;


					Q_WindWake->WindWake[Count].Lvert[37][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[37][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[37][3].x = Q_WindWake->WindWake[Count].VertB35.x;
					Q_WindWake->WindWake[Count].Lvert[37][3].y = Q_WindWake->WindWake[Count].VertB35.y;
					Q_WindWake->WindWake[Count].Lvert[37][3].z = Q_WindWake->WindWake[Count].VertB35.z;


					Q_WindWake->WindWake[Count].Lvert[38][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[38][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[38][0].x = Q_WindWake->WindWake[Count].VertT4.x;
					Q_WindWake->WindWake[Count].Lvert[38][0].y = Q_WindWake->WindWake[Count].VertT4.y;
					Q_WindWake->WindWake[Count].Lvert[38][0].z = Q_WindWake->WindWake[Count].VertT4.z;

							
					Q_WindWake->WindWake[Count].Lvert[38][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[38][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[38][1].x = Q_WindWake->WindWake[Count].VertT45.x;
					Q_WindWake->WindWake[Count].Lvert[38][1].y = Q_WindWake->WindWake[Count].VertT45.y;
					Q_WindWake->WindWake[Count].Lvert[38][1].z = Q_WindWake->WindWake[Count].VertT45.z;

							
					Q_WindWake->WindWake[Count].Lvert[38][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[38][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[38][2].x = Q_WindWake->WindWake[Count].VertB45.x;
					Q_WindWake->WindWake[Count].Lvert[38][2].y = Q_WindWake->WindWake[Count].VertB45.y;
					Q_WindWake->WindWake[Count].Lvert[38][2].z = Q_WindWake->WindWake[Count].VertB45.z;


					Q_WindWake->WindWake[Count].Lvert[38][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[38][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[38][3].x = Q_WindWake->WindWake[Count].VertB4.x;
					Q_WindWake->WindWake[Count].Lvert[38][3].y = Q_WindWake->WindWake[Count].VertB4.y;
					Q_WindWake->WindWake[Count].Lvert[38][3].z = Q_WindWake->WindWake[Count].VertB4.z;


					Q_WindWake->WindWake[Count].Lvert[39][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[39][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[39][0].x = Q_WindWake->WindWake[Count].VertT45.x;
					Q_WindWake->WindWake[Count].Lvert[39][0].y = Q_WindWake->WindWake[Count].VertT45.y;
					Q_WindWake->WindWake[Count].Lvert[39][0].z = Q_WindWake->WindWake[Count].VertT45.z;

							
					Q_WindWake->WindWake[Count].Lvert[39][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[39][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[39][1].x = Q_WindWake->WindWake[Count].VertT5.x;
					Q_WindWake->WindWake[Count].Lvert[39][1].y = Q_WindWake->WindWake[Count].VertT5.y;
					Q_WindWake->WindWake[Count].Lvert[39][1].z = Q_WindWake->WindWake[Count].VertT5.z;

							
					Q_WindWake->WindWake[Count].Lvert[39][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[39][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[39][2].x = Q_WindWake->WindWake[Count].VertB5.x;
					Q_WindWake->WindWake[Count].Lvert[39][2].y = Q_WindWake->WindWake[Count].VertB5.y;
					Q_WindWake->WindWake[Count].Lvert[39][2].z = Q_WindWake->WindWake[Count].VertB5.z;


					Q_WindWake->WindWake[Count].Lvert[39][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[39][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[39][3].x = Q_WindWake->WindWake[Count].VertB45.x;
					Q_WindWake->WindWake[Count].Lvert[39][3].y = Q_WindWake->WindWake[Count].VertB45.y;
					Q_WindWake->WindWake[Count].Lvert[39][3].z = Q_WindWake->WindWake[Count].VertB45.z;


					Q_WindWake->WindWake[Count].Lvert[40][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[40][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[40][0].x = Q_WindWake->WindWake[Count].VertT5.x;
					Q_WindWake->WindWake[Count].Lvert[40][0].y = Q_WindWake->WindWake[Count].VertT5.y;
					Q_WindWake->WindWake[Count].Lvert[40][0].z = Q_WindWake->WindWake[Count].VertT5.z;

					
					Q_WindWake->WindWake[Count].Lvert[40][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[40][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[40][1].x = Q_WindWake->WindWake[Count].VertT55.x;
					Q_WindWake->WindWake[Count].Lvert[40][1].y = Q_WindWake->WindWake[Count].VertT55.y;
					Q_WindWake->WindWake[Count].Lvert[40][1].z = Q_WindWake->WindWake[Count].VertT55.z;

							
					Q_WindWake->WindWake[Count].Lvert[40][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[40][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[40][2].x = Q_WindWake->WindWake[Count].VertB55.x;
					Q_WindWake->WindWake[Count].Lvert[40][2].y = Q_WindWake->WindWake[Count].VertB55.y;
					Q_WindWake->WindWake[Count].Lvert[40][2].z = Q_WindWake->WindWake[Count].VertB55.z;


					Q_WindWake->WindWake[Count].Lvert[40][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[40][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[40][3].x = Q_WindWake->WindWake[Count].VertB5.x;
					Q_WindWake->WindWake[Count].Lvert[40][3].y = Q_WindWake->WindWake[Count].VertB5.y;
					Q_WindWake->WindWake[Count].Lvert[40][3].z = Q_WindWake->WindWake[Count].VertB5.z;


					Q_WindWake->WindWake[Count].Lvert[41][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[41][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[41][0].x = Q_WindWake->WindWake[Count].VertT55.x;
					Q_WindWake->WindWake[Count].Lvert[41][0].y = Q_WindWake->WindWake[Count].VertT55.y;
					Q_WindWake->WindWake[Count].Lvert[41][0].z = Q_WindWake->WindWake[Count].VertT55.z;

							
					Q_WindWake->WindWake[Count].Lvert[41][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[41][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[41][1].x = Q_WindWake->WindWake[Count].VertT6.x;
					Q_WindWake->WindWake[Count].Lvert[41][1].y = Q_WindWake->WindWake[Count].VertT6.y;
					Q_WindWake->WindWake[Count].Lvert[41][1].z = Q_WindWake->WindWake[Count].VertT6.z;

							
					Q_WindWake->WindWake[Count].Lvert[41][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[41][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[41][2].x = Q_WindWake->WindWake[Count].VertB6.x;
					Q_WindWake->WindWake[Count].Lvert[41][2].y = Q_WindWake->WindWake[Count].VertB6.y;
					Q_WindWake->WindWake[Count].Lvert[41][2].z = Q_WindWake->WindWake[Count].VertB6.z;


					Q_WindWake->WindWake[Count].Lvert[41][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[41][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[41][3].x = Q_WindWake->WindWake[Count].VertB55.x;
					Q_WindWake->WindWake[Count].Lvert[41][3].y = Q_WindWake->WindWake[Count].VertB55.y;
					Q_WindWake->WindWake[Count].Lvert[41][3].z = Q_WindWake->WindWake[Count].VertB55.z;


					Q_WindWake->WindWake[Count].Lvert[42][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[42][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[42][0].x = Q_WindWake->WindWake[Count].VertT6.x;
					Q_WindWake->WindWake[Count].Lvert[42][0].y = Q_WindWake->WindWake[Count].VertT6.y;
					Q_WindWake->WindWake[Count].Lvert[42][0].z = Q_WindWake->WindWake[Count].VertT6.z;

							
					Q_WindWake->WindWake[Count].Lvert[42][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[42][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[42][1].x = Q_WindWake->WindWake[Count].VertT65.x;
					Q_WindWake->WindWake[Count].Lvert[42][1].y = Q_WindWake->WindWake[Count].VertT65.y;
					Q_WindWake->WindWake[Count].Lvert[42][1].z = Q_WindWake->WindWake[Count].VertT65.z;

							
					Q_WindWake->WindWake[Count].Lvert[42][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[42][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[42][2].x = Q_WindWake->WindWake[Count].VertB65.x;
					Q_WindWake->WindWake[Count].Lvert[42][2].y = Q_WindWake->WindWake[Count].VertB65.y;
					Q_WindWake->WindWake[Count].Lvert[42][2].z = Q_WindWake->WindWake[Count].VertB65.z;


					Q_WindWake->WindWake[Count].Lvert[42][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[42][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[42][3].x = Q_WindWake->WindWake[Count].VertB6.x;
					Q_WindWake->WindWake[Count].Lvert[42][3].y = Q_WindWake->WindWake[Count].VertB6.y;
					Q_WindWake->WindWake[Count].Lvert[42][3].z = Q_WindWake->WindWake[Count].VertB6.z;


					Q_WindWake->WindWake[Count].Lvert[43][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[43][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[43][0].x = Q_WindWake->WindWake[Count].VertT65.x;
					Q_WindWake->WindWake[Count].Lvert[43][0].y = Q_WindWake->WindWake[Count].VertT65.y;
					Q_WindWake->WindWake[Count].Lvert[43][0].z = Q_WindWake->WindWake[Count].VertT65.z;

							
					Q_WindWake->WindWake[Count].Lvert[43][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[43][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[43][1].x = Q_WindWake->WindWake[Count].VertT7.x;
					Q_WindWake->WindWake[Count].Lvert[43][1].y = Q_WindWake->WindWake[Count].VertT7.y;
					Q_WindWake->WindWake[Count].Lvert[43][1].z = Q_WindWake->WindWake[Count].VertT7.z;

							
					Q_WindWake->WindWake[Count].Lvert[43][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[43][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[43][2].x = Q_WindWake->WindWake[Count].VertB7.x;
					Q_WindWake->WindWake[Count].Lvert[43][2].y = Q_WindWake->WindWake[Count].VertB7.y;
					Q_WindWake->WindWake[Count].Lvert[43][2].z = Q_WindWake->WindWake[Count].VertB7.z;


					Q_WindWake->WindWake[Count].Lvert[43][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[43][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[43][3].x = Q_WindWake->WindWake[Count].VertB65.x;
					Q_WindWake->WindWake[Count].Lvert[43][3].y = Q_WindWake->WindWake[Count].VertB65.y;
					Q_WindWake->WindWake[Count].Lvert[43][3].z = Q_WindWake->WindWake[Count].VertB65.z;


					Q_WindWake->WindWake[Count].Lvert[44][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[44][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[44][0].x = Q_WindWake->WindWake[Count].VertT7.x;
					Q_WindWake->WindWake[Count].Lvert[44][0].y = Q_WindWake->WindWake[Count].VertT7.y;
					Q_WindWake->WindWake[Count].Lvert[44][0].z = Q_WindWake->WindWake[Count].VertT7.z;

							
					Q_WindWake->WindWake[Count].Lvert[44][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[44][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[44][1].x = Q_WindWake->WindWake[Count].VertT75.x;
					Q_WindWake->WindWake[Count].Lvert[44][1].y = Q_WindWake->WindWake[Count].VertT75.y;
					Q_WindWake->WindWake[Count].Lvert[44][1].z = Q_WindWake->WindWake[Count].VertT75.z;

							
					Q_WindWake->WindWake[Count].Lvert[44][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[44][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[44][2].x = Q_WindWake->WindWake[Count].VertB75.x;
					Q_WindWake->WindWake[Count].Lvert[44][2].y = Q_WindWake->WindWake[Count].VertB75.y;
					Q_WindWake->WindWake[Count].Lvert[44][2].z = Q_WindWake->WindWake[Count].VertB75.z;


					Q_WindWake->WindWake[Count].Lvert[44][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[44][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[44][3].x = Q_WindWake->WindWake[Count].VertB7.x;
					Q_WindWake->WindWake[Count].Lvert[44][3].y = Q_WindWake->WindWake[Count].VertB7.y;
					Q_WindWake->WindWake[Count].Lvert[44][3].z = Q_WindWake->WindWake[Count].VertB7.z;


					Q_WindWake->WindWake[Count].Lvert[45][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[45][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[45][0].x = Q_WindWake->WindWake[Count].VertT75.x;
					Q_WindWake->WindWake[Count].Lvert[45][0].y = Q_WindWake->WindWake[Count].VertT75.y;
					Q_WindWake->WindWake[Count].Lvert[45][0].z = Q_WindWake->WindWake[Count].VertT75.z;

							
					Q_WindWake->WindWake[Count].Lvert[45][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[45][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[45][1].x = Q_WindWake->WindWake[Count].VertT8.x;
					Q_WindWake->WindWake[Count].Lvert[45][1].y = Q_WindWake->WindWake[Count].VertT8.y;
					Q_WindWake->WindWake[Count].Lvert[45][1].z = Q_WindWake->WindWake[Count].VertT8.z;

							
					Q_WindWake->WindWake[Count].Lvert[45][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[45][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[45][2].x = Q_WindWake->WindWake[Count].VertB8.x;
					Q_WindWake->WindWake[Count].Lvert[45][2].y = Q_WindWake->WindWake[Count].VertB8.y;
					Q_WindWake->WindWake[Count].Lvert[45][2].z = Q_WindWake->WindWake[Count].VertB8.z;


					Q_WindWake->WindWake[Count].Lvert[45][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[45][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[45][3].x = Q_WindWake->WindWake[Count].VertB75.x;
					Q_WindWake->WindWake[Count].Lvert[45][3].y = Q_WindWake->WindWake[Count].VertB75.y;
					Q_WindWake->WindWake[Count].Lvert[45][3].z = Q_WindWake->WindWake[Count].VertB75.z;


					Q_WindWake->WindWake[Count].Lvert[46][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[46][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[46][0].x = Q_WindWake->WindWake[Count].VertT8.x;
					Q_WindWake->WindWake[Count].Lvert[46][0].y = Q_WindWake->WindWake[Count].VertT8.y;
					Q_WindWake->WindWake[Count].Lvert[46][0].z = Q_WindWake->WindWake[Count].VertT8.z;

							
					Q_WindWake->WindWake[Count].Lvert[46][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[46][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[46][1].x = Q_WindWake->WindWake[Count].VertT85.x;
					Q_WindWake->WindWake[Count].Lvert[46][1].y = Q_WindWake->WindWake[Count].VertT85.y;
					Q_WindWake->WindWake[Count].Lvert[46][1].z = Q_WindWake->WindWake[Count].VertT85.z;


					Q_WindWake->WindWake[Count].Lvert[46][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[46][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[46][2].x = Q_WindWake->WindWake[Count].VertB85.x;
					Q_WindWake->WindWake[Count].Lvert[46][2].y = Q_WindWake->WindWake[Count].VertB85.y;
					Q_WindWake->WindWake[Count].Lvert[46][2].z = Q_WindWake->WindWake[Count].VertB85.z;


					Q_WindWake->WindWake[Count].Lvert[46][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[46][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[46][3].x = Q_WindWake->WindWake[Count].VertB8.x;
					Q_WindWake->WindWake[Count].Lvert[46][3].y = Q_WindWake->WindWake[Count].VertB8.y;
					Q_WindWake->WindWake[Count].Lvert[46][3].z = Q_WindWake->WindWake[Count].VertB8.z;


					Q_WindWake->WindWake[Count].Lvert[47][0].u = 0;
					Q_WindWake->WindWake[Count].Lvert[47][0].v = 0;
					Q_WindWake->WindWake[Count].Lvert[47][0].x = Q_WindWake->WindWake[Count].VertT85.x;
					Q_WindWake->WindWake[Count].Lvert[47][0].y = Q_WindWake->WindWake[Count].VertT85.y;
					Q_WindWake->WindWake[Count].Lvert[47][0].z = Q_WindWake->WindWake[Count].VertT85.z;


					Q_WindWake->WindWake[Count].Lvert[47][1].u = 1;
					Q_WindWake->WindWake[Count].Lvert[47][1].v = 0;
					Q_WindWake->WindWake[Count].Lvert[47][1].x = Q_WindWake->WindWake[Count].VertT1.x;
					Q_WindWake->WindWake[Count].Lvert[47][1].y = Q_WindWake->WindWake[Count].VertT1.y;
					Q_WindWake->WindWake[Count].Lvert[47][1].z = Q_WindWake->WindWake[Count].VertT1.z;


					Q_WindWake->WindWake[Count].Lvert[47][2].u = 1;
					Q_WindWake->WindWake[Count].Lvert[47][2].v = 1;
					Q_WindWake->WindWake[Count].Lvert[47][2].x = Q_WindWake->WindWake[Count].VertB1.x;
					Q_WindWake->WindWake[Count].Lvert[47][2].y = Q_WindWake->WindWake[Count].VertB1.y;
					Q_WindWake->WindWake[Count].Lvert[47][2].z = Q_WindWake->WindWake[Count].VertB1.z;


					Q_WindWake->WindWake[Count].Lvert[47][3].u = 0;
					Q_WindWake->WindWake[Count].Lvert[47][3].v = 1;
					Q_WindWake->WindWake[Count].Lvert[47][3].x = Q_WindWake->WindWake[Count].VertB85.x;
					Q_WindWake->WindWake[Count].Lvert[47][3].y = Q_WindWake->WindWake[Count].VertB85.y;
					Q_WindWake->WindWake[Count].Lvert[47][3].z = Q_WindWake->WindWake[Count].VertB85.z;


		if(Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkTYPE == 0)
			{
			int i = 0;
			while(i <= 15)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[Count].Lvert[i][0], 3, Medias->Water[Q_WindWake->WindWake[Count].MaterialCNT], Q_WindWake->WindWake[Count].Type, Q_WindWake->WindWake[Count].RenderFlags, 1.0f);
				i++;
				}

			i = 16;
			while(i <= 47)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[Count].Lvert[i][0], 4, Medias->Water[Q_WindWake->WindWake[Count].MaterialCNT], Q_WindWake->WindWake[Count].Type, Q_WindWake->WindWake[Count].RenderFlags, 1.0f);
				i++;
				}
			}

		if(Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkTYPE == 1)
			{
			int i = 0;
			while(i <= 15)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[Count].Lvert[i][0], 3, Medias->fire[Q_WindWake->WindWake[Count].MaterialCNT], Q_WindWake->WindWake[Count].Type, Q_WindWake->WindWake[Count].RenderFlags, 1.0f);
				i++;
				}

			i = 16;
			while(i <= 47)
				{
				Qpo->Poly_AddOnce(&Q_WindWake->WindWake[Count].Lvert[i][0], 4, Medias->fire[Q_WindWake->WindWake[Count].MaterialCNT], Q_WindWake->WindWake[Count].Type, Q_WindWake->WindWake[Count].RenderFlags, 1.0f);
				i++;
				}
			}


		//###### Initialise one Textured Tri Effect - WindWake Ring Trail - Static
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Live = 1;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].EffectType = 1;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].PosB = Q_WindWake->WindWake[Count].Pos;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Pos = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].STRPos;

		if(Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkTYPE == 0)
			{ Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].EffectType = 1; }

		if(Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkTYPE == 1)
			{ Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].EffectType = 4; }

		//#### Set Back facing verts
		if(Q_Forge->Forge[Count].NomTriEffect != 0)
			{
			//#### Set front verts
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT1 = Q_WindWake->WindWake[Count].VertB1;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT15 = Q_WindWake->WindWake[Count].VertB15;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT2 = Q_WindWake->WindWake[Count].VertB2;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT25 = Q_WindWake->WindWake[Count].VertB25;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT3 = Q_WindWake->WindWake[Count].VertB3;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT35 = Q_WindWake->WindWake[Count].VertB35;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT4 = Q_WindWake->WindWake[Count].VertB4;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT45 = Q_WindWake->WindWake[Count].VertB45;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT5 = Q_WindWake->WindWake[Count].VertB5;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT55 = Q_WindWake->WindWake[Count].VertB55;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT6 = Q_WindWake->WindWake[Count].VertB6;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT65 = Q_WindWake->WindWake[Count].VertB65;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT7 = Q_WindWake->WindWake[Count].VertB7;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT75 = Q_WindWake->WindWake[Count].VertB75;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT8 = Q_WindWake->WindWake[Count].VertB8;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT85 = Q_WindWake->WindWake[Count].VertB85;

			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB1 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT1;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB15 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT15;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB2 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT2;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB25 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT25;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB3 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT3;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB35 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT35;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB4 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT4;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB45 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT45;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB5 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT5;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB55 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT55;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB6 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT6;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB65 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT65;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB7 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT7;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB75 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT75;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB8 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT8;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB85 = Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect-1].VertT85;
			}
		else
			{
			//#### Set front verts
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT1 = Q_WindWake->WindWake[Count].VertT1;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT15 = Q_WindWake->WindWake[Count].VertT15;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT2 = Q_WindWake->WindWake[Count].VertT2;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT25 = Q_WindWake->WindWake[Count].VertT25;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT3 = Q_WindWake->WindWake[Count].VertT3;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT35 = Q_WindWake->WindWake[Count].VertT35;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT4 = Q_WindWake->WindWake[Count].VertT4;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT45 = Q_WindWake->WindWake[Count].VertT45;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT5 = Q_WindWake->WindWake[Count].VertT5;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT55 = Q_WindWake->WindWake[Count].VertT55;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT6 = Q_WindWake->WindWake[Count].VertT6;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT65 = Q_WindWake->WindWake[Count].VertT65;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT7 = Q_WindWake->WindWake[Count].VertT7;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT75 = Q_WindWake->WindWake[Count].VertT75;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT8 = Q_WindWake->WindWake[Count].VertT8;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertT85 = Q_WindWake->WindWake[Count].VertT85;

			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB1 = Q_WindWake->WindWake[Count].VertB1;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB15 = Q_WindWake->WindWake[Count].VertB15;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB2 = Q_WindWake->WindWake[Count].VertB2;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB25 = Q_WindWake->WindWake[Count].VertB25;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB3 = Q_WindWake->WindWake[Count].VertB3;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB35 = Q_WindWake->WindWake[Count].VertB35;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB4 = Q_WindWake->WindWake[Count].VertB4;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB45 = Q_WindWake->WindWake[Count].VertB45;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB5 = Q_WindWake->WindWake[Count].VertB5;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB55 = Q_WindWake->WindWake[Count].VertB55;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB6 = Q_WindWake->WindWake[Count].VertB6;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB65 = Q_WindWake->WindWake[Count].VertB65;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB7 = Q_WindWake->WindWake[Count].VertB7;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB75 = Q_WindWake->WindWake[Count].VertB75;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB8 = Q_WindWake->WindWake[Count].VertB8;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VertB85 = Q_WindWake->WindWake[Count].VertB85;
			}


		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VecIn = Q_WindWake->WindWake[Count].VecIn;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VecUp = Q_WindWake->WindWake[Count].VecUp;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].VecLeft = Q_WindWake->WindWake[Count].VecLeft;

		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].MaterialCNT = Q_WindWake->WindWake[Count].MaterialCNT;

		if(Q_Forge->Forge[Count].JinkSpecialON < 1)
			{
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Red = 255;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Green = 255;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Blue = 255;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Alpha = Q_WindWake->WindWake[Count].MAINALPHA / 3;
			}
		else
			{
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Alpha = Q_WindWake->WindWake[Count].MAINALPHA / 3;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Red = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkRED;	//135
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Green = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkGREEN;
			Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Blue = Q_Forge->Forge[Count].CharDATA.AngelEFFECTS.JinkBLUE;
			}

		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].LengthDist = 3;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].ExpandDist = 0.01;

		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].PolyType = QPOLY_TYPE_TRI;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].RenderFlags = QPOLY_REND_DEPTH_SORT;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].ScaleBIT = 1.0f;

		if(Q_Forge->Forge[Count].NomTriEffect == 0)
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

		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Ut = TriEffectUt;
		Q_Forge->Forge[Count].Q_TexTriEffect[Q_Forge->Forge[Count].NomTriEffect].Ub = TriEffectUb;

		Q_Forge->Forge[Count].NomTriEffect++;
		if(Q_Forge->Forge[Count].NomTriEffect > 299) Q_Forge->Forge[Count].NomTriEffect = 0;
		}
	}

};