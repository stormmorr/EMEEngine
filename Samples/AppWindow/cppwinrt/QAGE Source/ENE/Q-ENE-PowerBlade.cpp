/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Power Blade-

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
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-PntSprite.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-WE-MeleeHits.h"

#pragma message("scan for scripting")

using namespace GVARS;

namespace GVARS
{

	//########  - SMALL ENERGY ATTACKS -  ########//

void Q_EFFCon::SEnergy_PowerBlade_ServerFrame(int Count)
	{
#if 0
	if(Q_PowerBlade->PowerBlade[Count].Init == 1)
		{
		helly = 0;
		while(helly < Q_PowerBlade->PowerBlade[Count].NomActors)
			{
			helly++;
			}

		//Q_PowerBlade->PowerBlade[Count].TraVec
		}

	if(Q_PowerBlade->PowerBlade[Count].Init == 0)
		{
		Q_PowerBlade->PowerBlade[Count].Init = 1;

		Q_PowerBlade->PowerBlade[Count].NomActors = 5;
		Q_PowerBlade->PowerBlade[Count].Scale = 0.01;
		Q_PowerBlade->PowerBlade[Count].ScaleMode = 0;
		Q_PowerBlade->PowerBlade[Count].Alpha = 0;
		Q_PowerBlade->PowerBlade[Count].AlphaInc = 50;
		Q_PowerBlade->PowerBlade[Count].AlphaScale[0] = 1;
		Q_PowerBlade->PowerBlade[Count].AlphaScale[1] = 0.9;
		Q_PowerBlade->PowerBlade[Count].AlphaScale[2] = 0.8;
		Q_PowerBlade->PowerBlade[Count].AlphaScale[3] = 0.6;
		Q_PowerBlade->PowerBlade[Count].AlphaScale[4] = 0.3;
		Q_PowerBlade->PowerBlade[Count].Speed = 0;

#if 1
		Q_PowerBlade->PowerBlade[Count].SpeedScale[0] = 0;
		Q_PowerBlade->PowerBlade[Count].SpeedScale[1] = 0.3;
		Q_PowerBlade->PowerBlade[Count].SpeedScale[2] = 0.6;
		Q_PowerBlade->PowerBlade[Count].SpeedScale[3] = 0.9;
		Q_PowerBlade->PowerBlade[Count].SpeedScale[4] = 1.2;
#endif

		Q_PowerBlade->PowerBlade[Count].LightColor.red = 255.0f;
		Q_PowerBlade->PowerBlade[Count].LightColor.green = 255.0f;
		Q_PowerBlade->PowerBlade[Count].LightColor.blue = 200.0f;
		Q_PowerBlade->PowerBlade[Count].LightColor.alpha = 255.0f;
		Q_PowerBlade->PowerBlade[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);

		jet=0;
		while(jet < Q_PowerBlade->PowerBlade[Count].NomActors)
			{
			Qpo->Mesh_SetScale(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[jet], 0.01f,0.01f,0.01f);
			//Qpo->Avatar_SetLighting(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[jet].Avatar, false, &goup, 0, 0, 0, 255, 255, 255, false, 0, NULL, false);
			Qpo->Vec3d_Copy(&Q_PowerBlade->PowerBlade[Count].LightPos, &Q_PowerBlade->PowerBlade[Count].AvatarFlag[jet].Xform.Translation);
			jet++;
			}

		//RESET MULTIPLE HIT COUNTER
		Q_PowerBlade->PowerBlade[Count].AntiMultHits[250] = 0;
		jet=0;
		while(jet < _->NomAI)
			{
			Q_PowerBlade->PowerBlade[jet].AntiMultHits[jet] = 0;
			jet++;
			}

		Q_PowerBlade->PowerBlade[Count].Sound = Qpo->Sound_Play(Medias->S_Renzou, _->Volume, _->Pan, _->S_TimeScale, true, &Q_PowerBlade->PowerBlade[Count].LightPos);

		helly = 0;
		while(helly < Q_PowerBlade->PowerBlade[Count].NomActors)
			{
			Qpo->Transform_GetLeft(&Q_PowerBlade->PowerBlade[Count].Matrix, &Q_PowerBlade->PowerBlade[Count].Left);
			Qpo->Transform_GetUp(&Q_PowerBlade->PowerBlade[Count].Matrix, &Q_PowerBlade->PowerBlade[Count].Up);
			Qpo->Transform_GetIn(&Q_PowerBlade->PowerBlade[Count].Matrix, &Q_PowerBlade->PowerBlade[Count].In);

			Qpo->Transform_New(&Q_PowerBlade->PowerBlade[Count].Matrix2);
			Qpo->Transform_GetUp(&Q_PowerBlade->PowerBlade[Count].Matrix2, &Q_PowerBlade->PowerBlade[Count].Up2);

			Q_PowerBlade->PowerBlade[Count].HeadLeft = Q_PowerBlade->PowerBlade[Count].Left;
			Q_PowerBlade->PowerBlade[Count].HeadLeft.y = Q_PowerBlade->PowerBlade[Count].Up2.y;
			Q_PowerBlade->PowerBlade[Count].Dist = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].HeadLeft, &Q_PowerBlade->PowerBlade[Count].Up2);

			//IMP MIGHT NEED TO MOVE THIS LINE DOWN TO BELOW ROTATEZ

			//### Get Matrix Direction Vectors
			Qpo->Transform_GetIn(&Q_PowerBlade->PowerBlade[Count].Matrix2, &Q_PowerBlade->PowerBlade[Count].CURRTraVec);
			Qpo->Transform_GetLeft(&Q_PowerBlade->PowerBlade[Count].Matrix2, &Q_PowerBlade->PowerBlade[Count].LeftVec);

			//### Stabilise Trajectories
			
			Qpo->Vec3d_Normalize(&Q_PowerBlade->PowerBlade[Count].TraVec);
			Q_PowerBlade->PowerBlade[Count].TraVec.y = 0;
			
			Qpo->Vec3d_Normalize(&Q_PowerBlade->PowerBlade[Count].CURRTraVec);
			Q_PowerBlade->PowerBlade[Count].CURRTraVec.y = 0;

			//### Find Opposite Length
			Q_PowerBlade->PowerBlade[Count].TrajDIST = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TraVec, &Q_PowerBlade->PowerBlade[Count].CURRTraVec);
			Q_PowerBlade->PowerBlade[Count].TrajDIST /= 2;

			Q_PowerBlade->PowerBlade[Count].AngleY = asin( Q_PowerBlade->PowerBlade[Count].TrajDIST ) * 2;	//(PI/2);	//2

			//### Find distance between pure left and right to find turn direction
			Qpo->Vec3d_Copy(&Q_PowerBlade->PowerBlade[Count].LeftVec, &Q_PowerBlade->PowerBlade[Count].Right);
			Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].Right);

			Q_PowerBlade->PowerBlade[Count].ScanDistLeft = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TraVec, &Q_PowerBlade->PowerBlade[Count].LeftVec);
			Q_PowerBlade->PowerBlade[Count].ScanDistRight = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TraVec, &Q_PowerBlade->PowerBlade[Count].Right);

			if(Q_PowerBlade->PowerBlade[Count].ScanDistLeft > Q_PowerBlade->PowerBlade[Count].ScanDistRight) Q_PowerBlade->PowerBlade[Count].AngleY *= -1;

			Q_PowerBlade->PowerBlade[Count].AngleX = 0;

			if(Q_PowerBlade->PowerBlade[Count].Dist < 0.4)
				{
				Q_PowerBlade->PowerBlade[Count].ShotSpin = 0;
				Q_PowerBlade->PowerBlade[Count].AngleZ = 0;
				}
			else
				{
				Q_PowerBlade->PowerBlade[Count].ShotSpin = 1;
				Q_PowerBlade->PowerBlade[Count].AngleZ = Q_PowerBlade->PowerBlade[Count].Dist;
				}

			if(Q_PowerBlade->PowerBlade[Count].AngleZ > PI * 2) Q_PowerBlade->PowerBlade[Count].AngleZ = Q_PowerBlade->PowerBlade[Count].AngleZ - (PI*2);
			if(Q_PowerBlade->PowerBlade[Count].AngleZ < 0) Q_PowerBlade->PowerBlade[Count].AngleZ = (PI*2) - Q_PowerBlade->PowerBlade[Count].AngleZ;

#pragma message("Server engine is oblivious rendering matrices")
#if defined(WIN32)
#if 0 // QAGE_DESKTOP
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glRotatef(radToDeg(Q_PowerBlade->PowerBlade[Count].AngleY), 0.0f, 1.0f, 0.0f);
			glRotatef(radToDeg(Q_PowerBlade->PowerBlade[Count].AngleX), 1.0f, 0.0f, 0.0f);
			glRotatef(radToDeg(Q_PowerBlade->PowerBlade[Count].AngleZ), 0.0f, 0.0f, 1.0f);

			glGetFloatv(GL_MODELVIEW_MATRIX, Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly].Viewform.Matrix.mf);
#endif
#endif

			helly++;
			}

		}

		//Set Alpha
	if(Q_PowerBlade->PowerBlade[Count].Alpha + (Q_PowerBlade->PowerBlade[Count].AlphaInc*_->TimeScale) <= 255) Q_PowerBlade->PowerBlade[Count].Alpha += Q_PowerBlade->PowerBlade[Count].AlphaInc*_->TimeScale;
	else Q_PowerBlade->PowerBlade[Count].Alpha = 255;

		//Set Speed
	if(Q_PowerBlade->PowerBlade[Count].Speed + (Q_PowerBlade->PowerBlade[Count].SpeedInc*_->TimeScale) <= Q_PowerBlade->PowerBlade[Count].SpeedMax) Q_PowerBlade->PowerBlade[Count].Speed += Q_PowerBlade->PowerBlade[Count].SpeedInc*_->TimeScale;
	else Q_PowerBlade->PowerBlade[Count].Speed = Q_PowerBlade->PowerBlade[Count].SpeedMax;

	//##### Scale Control #####
	if(Q_PowerBlade->PowerBlade[Count].ScaleMode == 0)
		{
		if(Q_PowerBlade->PowerBlade[Count].Scale + (Q_PowerBlade->PowerBlade[Count].ScaleInc*_->TimeScale) <= Q_PowerBlade->PowerBlade[Count].ScaleMax) Q_PowerBlade->PowerBlade[Count].Scale += Q_PowerBlade->PowerBlade[Count].ScaleInc*_->TimeScale;
		else
			{
			Q_PowerBlade->PowerBlade[Count].Scale = Q_PowerBlade->PowerBlade[Count].ScaleMax;
			Q_PowerBlade->PowerBlade[Count].ScaleMode = 1;
			}
		}
	else
		{
		Q_PowerBlade->PowerBlade[Count].RandomInput = ((((float)rand() / 32767) - 0.5) / 10) * _->TimeScale;
		Q_PowerBlade->PowerBlade[Count].Scale = Q_PowerBlade->PowerBlade[Count].ScaleMax + Q_PowerBlade->PowerBlade[Count].RandomInput;
		}

	if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
		{
		//#### Show Target Locks
		if(Q_PowerBlade->PowerBlade[Count].DisplayAlpha - 15 > 120) Q_PowerBlade->PowerBlade[Count].DisplayAlpha -= 15;
		else Q_PowerBlade->PowerBlade[Count].DisplayAlpha = 120;

		if(Q_PowerBlade->PowerBlade[Count].DisplayColor - 25 > 0) Q_PowerBlade->PowerBlade[Count].DisplayColor -= 25;
		else Q_PowerBlade->PowerBlade[Count].DisplayColor = 0;

		if(Q_PowerBlade->PowerBlade[Count].DisplayScale + 0.05 < 0.75) Q_PowerBlade->PowerBlade[Count].DisplayScale += 0.06;
		else Q_PowerBlade->PowerBlade[Count].DisplayScale = 0.75;
		
		if(Q_PowerBlade->PowerBlade[Count].AvID == 250)
			{
			player[g_Player]->LaserLV.a = Q_PowerBlade->PowerBlade[Count].DisplayAlpha;
			player[g_Player]->LaserLV.r = 255;
			player[g_Player]->LaserLV.g = Q_PowerBlade->PowerBlade[Count].DisplayColor;
			player[g_Player]->LaserLV.b = 0;
			player[g_Player]->LaserLV.x = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.x;
			player[g_Player]->LaserLV.y = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.y + 65;
			player[g_Player]->LaserLV.z = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.z;

			Qpo->Poly_AddOnce(&player[g_Player]->LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_PowerBlade->PowerBlade[Count].DisplayScale);
			}
		else
			{
			if(Q_PowerBlade->PowerBlade[Count].TargetID == 250)
				{
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.a = Q_PowerBlade->PowerBlade[Count].DisplayAlpha;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.g = Q_PowerBlade->PowerBlade[Count].DisplayColor;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_PowerBlade->PowerBlade[Count].DisplayScale);
				}
			else
				{
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.a = Q_PowerBlade->PowerBlade[Count].DisplayAlpha;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.g = Q_PowerBlade->PowerBlade[Count].DisplayColor;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.x = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.x;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.y = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.y + 65;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.z = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_PowerBlade->PowerBlade[Count].DisplayScale);
				}
			}

		if(Q_PowerBlade->PowerBlade[Count].TargetID == 250)
			{
			Q_PowerBlade->PowerBlade[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
			//Q_PowerBlade->PowerBlade[Count].TargetVec.y += 65;
			Q_PowerBlade->PowerBlade[Count].TargetVec.y += 45;
			}
		else
			{
			Q_PowerBlade->PowerBlade[Count].TargetVec = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation;
			//Q_PowerBlade->PowerBlade[Count].TargetVec.y += 65;
			Q_PowerBlade->PowerBlade[Count].TargetVec.y += 45;
			}

		//### Build Ghost Matrix

		Qpo->Vec3d_Subtract(&Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].LightPos, &Q_PowerBlade->PowerBlade[Count].TargetVec);
		Qpo->Vec3d_Normalize(&Q_PowerBlade->PowerBlade[Count].TargetVec);
		Qpo->Vec3d_Scale(&Q_PowerBlade->PowerBlade[Count].TargetVec, 150, &Q_PowerBlade->PowerBlade[Count].TargetVec);

		Qpo->Transform_GetLeft(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform, &Q_PowerBlade->PowerBlade[Count].Left);
		Qpo->Transform_GetUp(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform, &Q_PowerBlade->PowerBlade[Count].Up);
		Qpo->Transform_GetIn(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform, &Q_PowerBlade->PowerBlade[Count].ForVec);

		Q_PowerBlade->PowerBlade[Count].LeftVec = Q_PowerBlade->PowerBlade[Count].Left;
		Q_PowerBlade->PowerBlade[Count].UpVec = Q_PowerBlade->PowerBlade[Count].Up;

#if 0
		Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].UpVec);
#endif

		Qpo->Vec3d_Scale(&Q_PowerBlade->PowerBlade[Count].ForVec, 150, &Q_PowerBlade->PowerBlade[Count].ForVec);
		Qpo->Vec3d_Scale(&Q_PowerBlade->PowerBlade[Count].LeftVec, 150, &Q_PowerBlade->PowerBlade[Count].LeftVec);
		Qpo->Vec3d_Scale(&Q_PowerBlade->PowerBlade[Count].UpVec, 150, &Q_PowerBlade->PowerBlade[Count].UpVec);

		if(Q_PowerBlade->PowerBlade[Count].ShotSpin == 0)
			{
			Q_PowerBlade->PowerBlade[Count].AngleZ += 0.035 * _->TimeScale;
			}

		if(Q_PowerBlade->PowerBlade[Count].ShotSpin == 1)
			{
			Q_PowerBlade->PowerBlade[Count].AngleZ += 0.17 * _->TimeScale;
			}

		if(Q_PowerBlade->PowerBlade[Count].AngleZ > PI * 2) Q_PowerBlade->PowerBlade[Count].AngleZ = Q_PowerBlade->PowerBlade[Count].AngleZ - (PI*2);
		if(Q_PowerBlade->PowerBlade[Count].AngleZ < 0) Q_PowerBlade->PowerBlade[Count].AngleZ = (PI*2) - Q_PowerBlade->PowerBlade[Count].AngleZ;

		//### Renzou Actors are upright
		if( ((Q_PowerBlade->PowerBlade[Count].AngleZ > (PI + (PI/2))) && (Q_PowerBlade->PowerBlade[Count].AngleZ < (PI*2))) || ((Q_PowerBlade->PowerBlade[Count].AngleZ < (PI/2)) && (Q_PowerBlade->PowerBlade[Count].AngleZ > 0)) )
			{
			if( (Q_PowerBlade->PowerBlade[Count].AngleZ > (PI + (PI/2))) && (Q_PowerBlade->PowerBlade[Count].AngleZ < (PI*2)) )
				{
				Q_PowerBlade->PowerBlade[Count].AngYIncFactor = ((Q_PowerBlade->PowerBlade[Count].AngleZ - (PI + (PI/2))) / (PI/2)) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				Q_PowerBlade->PowerBlade[Count].AngXIncFactor = (1 - ((Q_PowerBlade->PowerBlade[Count].AngleZ - (PI + (PI/2))) / (PI/2))) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				}

			if( (Q_PowerBlade->PowerBlade[Count].AngleZ < (PI/2)) && (Q_PowerBlade->PowerBlade[Count].AngleZ > 0) )
				{
				Q_PowerBlade->PowerBlade[Count].AngYIncFactor = (1 - (Q_PowerBlade->PowerBlade[Count].AngleZ / (PI/2))) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				Q_PowerBlade->PowerBlade[Count].AngXIncFactor = (Q_PowerBlade->PowerBlade[Count].AngleZ / (PI/2)) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				}
			}
		else  //### Renzou Actors are up-side-down
			{
			if( (Q_PowerBlade->PowerBlade[Count].AngleZ > (PI/2)) && (Q_PowerBlade->PowerBlade[Count].AngleZ < PI) )
				{
				Q_PowerBlade->PowerBlade[Count].AngYIncFactor = ((Q_PowerBlade->PowerBlade[Count].AngleZ - (PI/2)) / (PI/2)) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				Q_PowerBlade->PowerBlade[Count].AngXIncFactor = (1- ((Q_PowerBlade->PowerBlade[Count].AngleZ - (PI/2)) / (PI/2))) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				}

			if( (Q_PowerBlade->PowerBlade[Count].AngleZ > PI) && (Q_PowerBlade->PowerBlade[Count].AngleZ < (PI + (PI/2))) )
				{
				Q_PowerBlade->PowerBlade[Count].AngYIncFactor = (1 - ((Q_PowerBlade->PowerBlade[Count].AngleZ) / (PI/2))) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				Q_PowerBlade->PowerBlade[Count].AngXIncFactor = ((Q_PowerBlade->PowerBlade[Count].AngleZ) / (PI/2)) * Q_PowerBlade->PowerBlade[Count].Const_AngleInc;
				}
			}

		//Work Out Turn Angles
		Q_PowerBlade->PowerBlade[Count].TargetVecSTR = Q_PowerBlade->PowerBlade[Count].TargetVec;

		Q_PowerBlade->PowerBlade[Count].TargetVec.y = Q_PowerBlade->PowerBlade[Count].ForVec.y;
		Qpo->Vec3d_Subtract(&Q_PowerBlade->PowerBlade[Count].ForVec, &Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].ScanTurnVec);
		Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR = Qpo->Vec3d_Length(&Q_PowerBlade->PowerBlade[Count].ScanTurnVec);
		Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR /= ((Q_PowerBlade->PowerBlade[Count].Accuracy * 10000) * (Q_PowerBlade->PowerBlade[Count].Const_AngleInc - Q_PowerBlade->PowerBlade[Count].AngYIncFactor));	//500

		//Work Out Up Down Angles
		Q_PowerBlade->PowerBlade[Count].TargetVec = Q_PowerBlade->PowerBlade[Count].TargetVecSTR;

		Q_PowerBlade->PowerBlade[Count].TargetVec.x = Q_PowerBlade->PowerBlade[Count].ForVec.x;
		Q_PowerBlade->PowerBlade[Count].TargetVec.z = Q_PowerBlade->PowerBlade[Count].ForVec.z;
		Qpo->Vec3d_Subtract(&Q_PowerBlade->PowerBlade[Count].ForVec, &Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].ScanTurnVec);
		Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD = Qpo->Vec3d_Length(&Q_PowerBlade->PowerBlade[Count].ScanTurnVec);
		Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD /= ((Q_PowerBlade->PowerBlade[Count].Accuracy * 10000) * (Q_PowerBlade->PowerBlade[Count].Const_AngleInc - Q_PowerBlade->PowerBlade[Count].AngXIncFactor));	//500

		Q_PowerBlade->PowerBlade[Count].TargetVec = Q_PowerBlade->PowerBlade[Count].TargetVecSTR;
		
		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Vec3d_Copy(&Q_PowerBlade->PowerBlade[Count].LeftVec, &Q_PowerBlade->PowerBlade[Count].Right);
		Qpo->Vec3d_Copy(&Q_PowerBlade->PowerBlade[Count].UpVec, &Q_PowerBlade->PowerBlade[Count].RDown);
		Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].Right);
		Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].RDown);

		Q_PowerBlade->PowerBlade[Count].ScanDistLeft = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].LeftVec);
		Q_PowerBlade->PowerBlade[Count].ScanDistRight = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].Right);
		Q_PowerBlade->PowerBlade[Count].ScanDistUp = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].UpVec);
		Q_PowerBlade->PowerBlade[Count].ScanDistDown = Qpo->Vec3d_DistanceBetween(&Q_PowerBlade->PowerBlade[Count].TargetVec, &Q_PowerBlade->PowerBlade[Count].RDown);

		if(Q_PowerBlade->PowerBlade[Count].ScanDistLeft > Q_PowerBlade->PowerBlade[Count].ScanDistRight) Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR *= -1;
		if(Q_PowerBlade->PowerBlade[Count].ScanDistUp < Q_PowerBlade->PowerBlade[Count].ScanDistDown) Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD *= -1;

		if(Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR > Q_PowerBlade->PowerBlade[Count].Accuracy) Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR = Q_PowerBlade->PowerBlade[Count].Accuracy;
		if(Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR < -Q_PowerBlade->PowerBlade[Count].Accuracy) Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR = -Q_PowerBlade->PowerBlade[Count].Accuracy;
		if(Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD > Q_PowerBlade->PowerBlade[Count].Accuracy) Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD = Q_PowerBlade->PowerBlade[Count].Accuracy;
		if(Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD < -Q_PowerBlade->PowerBlade[Count].Accuracy) Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD = -Q_PowerBlade->PowerBlade[Count].Accuracy;

#if 1
		Q_PowerBlade->PowerBlade[Count].AngleX += (Q_PowerBlade->PowerBlade[Count].ScanTurnAngUD * _->TimeScale);

		if(Q_PowerBlade->PowerBlade[Count].AngleX > PI*2) Q_PowerBlade->PowerBlade[Count].AngleX = Q_PowerBlade->PowerBlade[Count].AngleX - (PI*2);
		if(Q_PowerBlade->PowerBlade[Count].AngleX < 0) Q_PowerBlade->PowerBlade[Count].AngleX = (PI*2) - Q_PowerBlade->PowerBlade[Count].AngleX;
#endif

#if 1
		Q_PowerBlade->PowerBlade[Count].AngleY += (Q_PowerBlade->PowerBlade[Count].ScanTurnAngLR * _->TimeScale);

		if(Q_PowerBlade->PowerBlade[Count].AngleY > PI*2) Q_PowerBlade->PowerBlade[Count].AngleY = Q_PowerBlade->PowerBlade[Count].AngleY - (PI*2);
		if(Q_PowerBlade->PowerBlade[Count].AngleY < 0) Q_PowerBlade->PowerBlade[Count].AngleY = (PI*2) - Q_PowerBlade->PowerBlade[Count].AngleY;
#endif
		}

	if(Q_PowerBlade->PowerBlade[Count].TargetLock == 2 && Q_PowerBlade->PowerBlade[Count].DisplayAlpha > 0)
		{
		//#### Show Target Locks
		if(Q_PowerBlade->PowerBlade[Count].DisplayAlpha - 20 > 0) Q_PowerBlade->PowerBlade[Count].DisplayAlpha -= 20;
		else Q_PowerBlade->PowerBlade[Count].DisplayAlpha = 0;

		if(Q_PowerBlade->PowerBlade[Count].DisplayColor - 25 > 0) Q_PowerBlade->PowerBlade[Count].DisplayColor -= 25;
		else Q_PowerBlade->PowerBlade[Count].DisplayColor = 0;

		if(Q_PowerBlade->PowerBlade[Count].DisplayScale + 0.05 < 0.01) Q_PowerBlade->PowerBlade[Count].DisplayScale += 0.01;
		else Q_PowerBlade->PowerBlade[Count].DisplayScale = 0.01;

		if(Q_PowerBlade->PowerBlade[Count].AvID == 250)
			{
			player[g_Player]->LaserLV.a = Q_PowerBlade->PowerBlade[Count].DisplayAlpha;
			player[g_Player]->LaserLV.r = 255;
			player[g_Player]->LaserLV.g = Q_PowerBlade->PowerBlade[Count].DisplayColor;
			player[g_Player]->LaserLV.b = 0;
			player[g_Player]->LaserLV.x = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.x;
			player[g_Player]->LaserLV.y = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.y + 65;
			player[g_Player]->LaserLV.z = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.z;

			Qpo->Poly_AddOnce(&player[g_Player]->LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_PowerBlade->PowerBlade[Count].DisplayScale);
			}
		else
			{
			if(Q_PowerBlade->PowerBlade[Count].TargetID == 250)
				{
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.a = Q_PowerBlade->PowerBlade[Count].DisplayAlpha;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.g = Q_PowerBlade->PowerBlade[Count].DisplayColor;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_PowerBlade->PowerBlade[Count].DisplayScale);
				}
			else
				{
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.a = Q_PowerBlade->PowerBlade[Count].DisplayAlpha;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.g = Q_PowerBlade->PowerBlade[Count].DisplayColor;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.x = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.x;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.y = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.y + 65;
				Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV.z = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].TargetID].AV.Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_PowerBlade->PowerBlade[Count].DisplayScale);
				}
			}
		}

	if(Q_PowerBlade->PowerBlade[Count].TargetLock == 2)
		{
		//Set Scale
		if(Q_PowerBlade->PowerBlade[Count].Scale - (0.05 * _->TimeScale) > 0) Q_PowerBlade->PowerBlade[Count].Scale -= (0.05 * _->TimeScale);
		else
			{
			Q_PowerBlade->PowerBlade[Count].Scale = 0;
			Q_PowerBlade->PowerBlade[Count].Live = 0;
			if(Q_PowerBlade->PowerBlade[Count].Light != NULL) Qpo->Light_Remove(Q_PowerBlade->PowerBlade[Count].Light);
			if(Q_PowerBlade->PowerBlade[Count].Sound != NULL) Qpo->Sound_Stop(Q_PowerBlade->PowerBlade[Count].Sound);

			helly = 0;
			while(helly < Q_PowerBlade->PowerBlade[Count].NomActors)
				{
				Qpo->Vec3d_Copy(&_->Origon, &Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly].Xform.Translation);
				helly++;
				}

			//### Energy Array Reorder
			K = Count;
			while(K < _->NomPowerBlade - 1)
				{
				Q_PowerBlade->PowerBlade[K] = Q_PowerBlade->PowerBlade[K+1];
				K++;
				}

			_->NomPowerBlade--;
			}
		}

		//Set Light Power and Move the Light
	Q_PowerBlade->PowerBlade[Count].LOldPos = Q_PowerBlade->PowerBlade[Count].LightPos;
	Qpo->Vec3d_AddScaled(&Q_PowerBlade->PowerBlade[Count].LightPos, Q_PowerBlade->PowerBlade[Count].Speed*_->TimeScale, &Q_PowerBlade->PowerBlade[Count].TraVec, &Q_PowerBlade->PowerBlade[Count].LightPos);

	Qpo->Light_SetAttr(Q_PowerBlade->PowerBlade[Count].Light, &Q_PowerBlade->PowerBlade[Count].LightPos, &Q_PowerBlade->PowerBlade[Count].LightColor, Q_PowerBlade->PowerBlade[Count].Scale * 150, false);

	helly = 0;
	while(helly < Q_PowerBlade->PowerBlade[Count].NomActors)
		{
		Qpo->Mesh_SetScale(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly], Q_PowerBlade->PowerBlade[Count].Scale, Q_PowerBlade->PowerBlade[Count].Scale, Q_PowerBlade->PowerBlade[Count].Scale);
		Qpo->Mesh_SetAlpha(&Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly], Q_PowerBlade->PowerBlade[Count].Alpha * Q_PowerBlade->PowerBlade[Count].AlphaScale[helly]);

		Qpo->Vec3d_Copy(&Q_PowerBlade->PowerBlade[Count].LightPos, &Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly].Xform.Translation);
		Qpo->Vec3d_AddScaled(&Q_PowerBlade->PowerBlade[Count].LightPos, -(Q_PowerBlade->PowerBlade[Count].Speed * Q_PowerBlade->PowerBlade[Count].SpeedScale[helly]), &Q_PowerBlade->PowerBlade[Count].TraVec, &Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly].Xform.Translation);
		helly++;
		}

	Q_PowerBlade->PowerBlade[Count].LOldPos = Q_PowerBlade->PowerBlade[Count].LightPos;
	Qpo->Vec3d_AddScaled(&Q_PowerBlade->PowerBlade[Count].LightPos, Q_PowerBlade->PowerBlade[Count].Speed*_->TimeScale, &Q_PowerBlade->PowerBlade[Count].TraVec, &Q_PowerBlade->PowerBlade[Count].LightPos);

	Qpo->Sound_Modify(Q_PowerBlade->PowerBlade[Count].Sound, _->Volume, _->Pan, _->S_TimeScale, &Q_PowerBlade->PowerBlade[Count].LightPos, &Q_PowerBlade->PowerBlade[Count].TraVec);

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
						TESTPosS = Q_PowerBlade->PowerBlade[Count].LOldPos;
						TESTPosE = Q_PowerBlade->PowerBlade[Count].LightPos;
						while(TESTDist > 1)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_PowerBlade->PowerBlade[Count].TraVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Object->Object[SCRAM].Pos);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < Q_Object->Object[SCRAM].Scale)
								{
								//Set Player Enemy Display to correct enemy
								if(Q_PowerBlade->PowerBlade[Count].AvID == 250)
									{
									player[g_Player]->HB_LastAvatarHitID = (SCRAM + 1) * -1;
									}
								else
									{
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_LastAvatarHitID = (SCRAM + 1) * -1;
									}

								//### Block Hit Flash
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = TESTPosS;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;
								
								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On

								if(Q_PowerBlade->PowerBlade[Count].AvID == 250)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3);				//Max Radius
									}
								else
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);				//Max Radius
									}

								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 200;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 60;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 200;

									//Increment number of MeleeHits
								_->NomMelHit += 1;

								if(Q_PowerBlade->PowerBlade[Count].AvID == 250)
									{
									if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
										{
										if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1) Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
										Q_Object->Object[SCRAM].StrengthBANK -= (80*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3));
										}
									}
								else
									{
									if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
										{
										if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1) Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
										Q_Object->Object[SCRAM].StrengthBANK -= (80*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3));
										}
									}

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

	if(1)
		{
		//PLAYER SHIELD CHECK
		if((player[g_Player]->Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].Team != player[g_Player]->Team) && (player[g_Player]->HB_Energy > 0))
			{
			TESTDist = 100;
			TESTPosS = Q_PowerBlade->PowerBlade[Count].LOldPos;
			TESTPosE = Q_PowerBlade->PowerBlade[Count].LightPos;
			while(TESTDist > 1)
				{
				Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_PowerBlade->PowerBlade[Count].TraVec, &TESTPosS);

				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

				TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

				if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
					{
					jet=0;
					while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						TESTPosS = TESTPosE;
						TESTDist = 0;

						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[helly].AvID;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}

					if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
						{
						if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1) Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
						player[g_Player]->HB_Energy -= (80*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3)) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));
						}
					}
				}
			}

		//### AVATAR SHIELD CHECK
		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if((Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].Team != Q_Forge->Forge[SCRAM].Team) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
					{
					TESTDist = 100;
					TESTPosS = Q_PowerBlade->PowerBlade[Count].LOldPos;
					TESTPosE = Q_PowerBlade->PowerBlade[Count].LightPos;
					while(TESTDist > 1)
						{
						Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_PowerBlade->PowerBlade[Count].TraVec, &TESTPosS);

						TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

						TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

						if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
							{
							jet=0;
							while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
								{
								TESTPosS = TESTPosE;
								TESTDist = 0;

								Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
								Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
								Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
								Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

								Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

								Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
								Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

								Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
								Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
								Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

								Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

								Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[helly].AvID;

								Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

								_->NomPntSprite++;
								jet++;
								}

							if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
								{
								if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1) Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
								Q_Forge->Forge[SCRAM].HB_Energy -= (80*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3)) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));
								}
							}
						}
					}
				}
			SCRAM++;
			}

#if 1
		if(Qpo->Collision_RayTest_Avatar(
			&Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Mins,
			&Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Maxs,
			&Q_PowerBlade->PowerBlade[Count].LOldPos,
			&Q_PowerBlade->PowerBlade[Count].LightPos,
			// GE_CONTENTS_CANNOT_OCCUPY
			/* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
			0xffffffff, NULL, NULL,
			&Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision, Q_PowerBlade->PowerBlade[Count].AvID))
				{
				if(Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_HitAvatar)
					{
					/*if(Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar != Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AV.Avatar
					&& Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar != Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Avatar		//**********
					&& Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar != Q_PowerBlade->PowerBlade[Count].AvatarFlag[1].Avatar		//Here Set collide flags on actor creation and shorten the 'if'
					&& Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar != Q_PowerBlade->PowerBlade[Count].AvatarFlag[2].Avatar		//******
					&& Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar != Q_PowerBlade->PowerBlade[Count].AvatarFlag[3].Avatar
					&& Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar != Q_PowerBlade->PowerBlade[Count].AvatarFlag[4].Avatar
					&& Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar.IDflag != 251)*/
						if(1){
					
	#endif

	#if 0
					if(!(((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x) > (Q_PowerBlade->PowerBlade[Count].LightPos.x + 10)) || ((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x) < (Q_PowerBlade->PowerBlade[Count].LightPos.x - 10))) &&
					!(((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y) > (Q_PowerBlade->PowerBlade[Count].LightPos.y + 10)) || ((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y) < (Q_PowerBlade->PowerBlade[Count].LightPos.y - 10))) &&
					!(((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z) > (Q_PowerBlade->PowerBlade[Count].LightPos.z + 10)) || ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z) < (Q_PowerBlade->PowerBlade[Count].LightPos.z - 10))))
						{	//#####- Hit Avatar -#####
						Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar.IDflag = 250;
						Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact = playerAV[g_Player]->Xform.Translation;
						Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact.m_Y += 45;
	#endif

	#if 1
						if(Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID == -1 && Q_PowerBlade->PowerBlade[Count].AvID != 250)
							{
	#endif
							if(Q_PowerBlade->PowerBlade[Count].AntiMultHits[250] < 1)
								{
								Q_PowerBlade->PowerBlade[Count].AntiMultHits[250]++;
					
								//##### Check Target Lock
								if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
									{ if(Q_PowerBlade->PowerBlade[Count].TargetID == 250) Q_PowerBlade->PowerBlade[Count].TargetLock = 2; }

								//#### Energy Attack Power
								Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Power / 5000) * 10) + 1;
								Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.AggPower / 100);

								//######## Aggressive to defensive power check
								if(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3)
									{
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.AggPower * (float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER);

									if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = 0;

									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PBTIMER = TIME;
									}

								//### Check to Determine if Avatar is Blocking
								if((!(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3) || (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0)) && (player[g_Player]->HB_Dead == 0))
									{
									//### Check if Avatar Is Deflecting
									if(player[g_Player]->DeflectLethal == 1)
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_PowerBlade->PowerBlade[Count].AvID;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100;				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

										_->NomMelHit++;

#if 0
										Q_PowerBlade->PowerBlade[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
										Q_PowerBlade->PowerBlade[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);
#endif

#if 0
										Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
										Q_PowerBlade->PowerBlade[Count].Init = 3;
#endif

										Q_PowerBlade->PowerBlade[Count].TargetID = Q_PowerBlade->PowerBlade[Count].AvID;
										Q_PowerBlade->PowerBlade[Count].AvID = 250;
										Q_PowerBlade->PowerBlade[Count].TargetLock = 1;
										Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].TraVec);
										}//END DEFLECT
									else
										{	/// Testing Attack Auto Deflect ///
										if(player[g_Player]->attackon)
											{
											if(player[g_Player]->HB_Energy >= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff)
												{
												player[g_Player]->HB_Energy -= 35 / player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff;
												player[g_Player]->HB_EnergyTimer = TIME;

												/*if(player[g_Player]->Aposestate == 26 || player[g_Player]->Aposestate == 28)
													{
													player[g_Player]->DeflectPower = 0;
													player[g_Player]->Deft_InReact = 1;
													player[g_Player]->Deft_PoseState = player[g_Player]->Aposestate;
													player[g_Player]->Deft_attposecnt = player[g_Player]->attposecnt;
													player[g_Player]->Deft_HitReactScale = player[g_Player]->HitReactScale;
													}
												else player[g_Player]->DeflectPower = 1;*/

												//player[g_Player]->DeflectPower = 0;
												player[g_Player]->Deft_InReact = 2;
												player[g_Player]->Deft_PoseState = player[g_Player]->Aposestate;
												player[g_Player]->Deft_attposecnt = player[g_Player]->attposecnt;
												player[g_Player]->Deft_HitReactScale = player[g_Player]->HitReactScale;

												//###Cancellation
												player[g_Player]->astackcnt = 0;
												player[g_Player]->astackrun = 0;
												player[g_Player]->astackcntdir[0] = 0;

												player[g_Player]->Block = 0;
												player[g_Player]->Blocking = 0;
												player[g_Player]->BlockHeight = 0;

												player[g_Player]->attackstack[player[g_Player]->astackcnt] = 63;
												player[g_Player]->KL_BTFSpecLevel = 0;

												player[g_Player]->attposecnt = 0;
												player[g_Player]->Aposestate = 0;
												player[g_Player]->blendamount[0] = 0;
												player[g_Player]->blendamount[98] = 0;
												player[g_Player]->TrailsOn = 0;
												player[g_Player]->attackon = 0;

												player[g_Player]->astackcntdir[0]++;
												player[g_Player]->astackcnt++;

												Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation);
												Qpo->Sound_Play(Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[g_Player]->Xform.Translation);

												Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_PowerBlade->PowerBlade[Count].AvID;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;

												Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

												//Expandro3D Struct
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.1;					//Switch 0 = Off !0 = On
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 175;				//Max Radius
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 255;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 255;

												_->NomMelHit++;

	#if 0
												Q_PowerBlade->PowerBlade[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
												Q_PowerBlade->PowerBlade[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);
	#endif

	#if 0
												Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
												Q_PowerBlade->PowerBlade[Count].Init = 3;
	#endif

												Q_PowerBlade->PowerBlade[Count].TargetID = Q_PowerBlade->PowerBlade[Count].AvID;
												Q_PowerBlade->PowerBlade[Count].AvID = 250;
												Q_PowerBlade->PowerBlade[Count].TargetLock = 1;
												Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].TraVec);
												}
											else
												{
												Qpo->Sound_Play(Medias->S_KeyLogError, _->Volume, _->Pan, _->S_TimeScale, false, &playerAV[0]->Xform.Translation); //campos
												}
											}
										else
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 20;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

												//# Deduct Health
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_LastAvatarHitID = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar.IDflag;
											/*if(player[g_Player]->HB_HReduceON == 0)*/ player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

													//Rework Needed here very messy , plus add a random factor
											player[g_Player]->HB_Health -= 70*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;

											//#### Experience Storage
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[250] += 70*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);


											if(player[g_Player]->HB_Health <= 0)
												{
												player[g_Player]->HB_Health = 0;

												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 18;

												player[g_Player]->HB_Dead = 1;

												jet = 0;
												while(jet < 5)
													{
													Q.AISpawnNNbot(Q_PowerBlade->PowerBlade[Count].AvID, playerAV[g_Player]->Xform.Translation);

													jet++;
													}

												//### Add Experience to attacking AVATAR
												if((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
													{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_PowerBlade->PowerBlade[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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

											if(&player[g_Player]->Shadows[1].Avatar != 0)
												{
												Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].Xform.Translation);
												Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].Xform.Translation);
												Qpo->Vec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].Xform.Translation);
												Qpo->Avatar_ClearPose(player[g_Player]->Shadows[1].Avatar, &player[g_Player]->Shadows[1].Xform);
												Qpo->Avatar_ClearPose(player[g_Player]->Shadows[2].Avatar, &player[g_Player]->Shadows[2].Xform);
												Qpo->Avatar_ClearPose(player[g_Player]->Shadows[3].Avatar, &player[g_Player]->Shadows[3].Xform);
												}

											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * 20;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											//###Hit Reactions
											player[g_Player]->HitReactScale = 0.025;	//0.05
											
											player[g_Player]->MoveReactVec = Q_PowerBlade->PowerBlade[Count].TraVec;
											player[g_Player]->MoveReactSpeed = 6;

											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_Energy += 10;
											if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_Energy > Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_MaxEnergy) Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_Energy = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_MaxEnergy;
									
											//## Reset Hit Wall
											player[g_Player]->HitWall = 0;

											//## Hit Reaction Motions
											
											if(player[g_Player]->Aposestate != 30)	//Standard Hit Reactions
												{
												player[g_Player]->Aposestate = 30;
												player[g_Player]->attackon = 1;
												player[g_Player]->attposecnt = 0;
												player[g_Player]->astackcnt = 0;
												player[g_Player]->astackrun = 0;
												}
											else
												{
												player[g_Player]->attposecnt = 2.08;
												player[g_Player]->astackcnt = 0;
												player[g_Player]->astackrun = 0;
												}

											//Increment number of MeleeHits
											_->NomMelHit += 1;

											if((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0) && (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3))
												{
												player[g_Player]->HitReactScale = 0.0035 * ((1 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 1);

												player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
												player[g_Player]->MoveReactSpeed = 4;

												//### Block Hit Flash

												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
												Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
												Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

												//Expandro3D Struct
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60;				//Max Radius
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 160;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 0;

													//Increment number of MeleeHits
												_->NomMelHit += 1;
												}//END Powerbank zeroed

											}//END Else Deflect

										}

									}//END Block
								else
									{
									player[g_Player]->HitReactScale = 0.0035 * ((1 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 100)) + 1);

									player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
									player[g_Player]->MoveReactSpeed = 6;

									player[g_Player]->Blocking = 1;
									player[g_Player]->BlockHit = 1;
									player[g_Player]->BlockHitFLAG = 1;
									player[g_Player]->attposecnt = 0;
									player[g_Player]->BlockHitID = _->NomMelHit;

									//### Block Hit Flash
									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;										
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
									Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;

										//Increment number of MeleeHits
									_->NomMelHit += 1;

									QpoVec3d Addition,TraVecStore;
									Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].TraVec);
									TraVecStore = Q_PowerBlade->PowerBlade[Count].TraVec;
									Qpo->Vec3d_Normalize(&TraVecStore);
									
									Addition.x += ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.y += ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.z += ((((float)rand() / 32767) * 1) -0.5) * 0.4;

									Qpo->Vec3d_Normalize(&Addition);
									Qpo->Vec3d_Subtract(&Addition, &TraVecStore, &Addition);
									Qpo->Vec3d_Scale(&Addition, 5, &Addition);

									Qpo->Vec3d_Add(&Q_PowerBlade->PowerBlade[Count].TraVec, &Addition, &Q_PowerBlade->PowerBlade[Count].TraVec);
									}//END Block Test

								}//END Anti Multiple hits

							}//END Playact Hit

							//#####- NON PLAYER AVATAR -#####


						//if(Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID != -1)
						else
							{

						/*SCRAM=0;
						while(SCRAM < _->NomAI)
							{
							if(Q_Forge->Forge[SCRAM].LIVE == 1 && SCRAM != Q_PowerBlade->PowerBlade[Count].AvID)
								{
								if(!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Mins.x) > (Q_PowerBlade->PowerBlade[Count].LightPos.x + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Maxs.x) < (Q_PowerBlade->PowerBlade[Count].LightPos.x - 10))) &&
								!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Mins.y) > (Q_PowerBlade->PowerBlade[Count].LightPos.y + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Maxs.y) < (Q_PowerBlade->PowerBlade[Count].LightPos.y - 10))) &&
								!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Mins.z) > (Q_PowerBlade->PowerBlade[Count].LightPos.z + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Maxs.z) < (Q_PowerBlade->PowerBlade[Count].LightPos.z - 10))))
									{
									Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Avatar.IDflag = SCRAM;
									Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
									Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact.m_Y += 45;*/

							//### Hit New Avatar
							if(Q_PowerBlade->PowerBlade[Count].AntiMultHits[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] < 1 && (Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID != Q_PowerBlade->PowerBlade[Count].AvID))
								{
								Q_PowerBlade->PowerBlade[Count].AntiMultHits[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID]++;

								if(Q_PowerBlade->PowerBlade[Count].TargetLock == 1)
									{ if(Q_PowerBlade->PowerBlade[Count].TargetID == Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID) Q_PowerBlade->PowerBlade[Count].TargetLock = 2; }



								//#### Energy Attack Power
								Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Power / 5000) * 10) + 1;
								Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.AggPower / 100);

								//######## Aggressive to defensive power check
								if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Block == 1 && Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHeight == 3)
									{
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.AggPower * (float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER);

									if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK = 0;

									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.PBTIMER = TIME;
									}


								//### Check to Determine if Avatar is Blocking
								if((!(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Block == 1 && Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHeight == 3) || (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK <= 0)) && (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Dead == 0))
									{
									//### Check if Avatar Is Deflecting
									if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].DeflectLethal == 1)
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_PowerBlade->PowerBlade[Count].AvID;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;

										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100;				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

										_->NomMelHit++;

#if 0
										Q_PowerBlade->PowerBlade[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
										Q_PowerBlade->PowerBlade[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);
#endif

#if 0
										Q_PowerBlade->PowerBlade[Count].TargetLock = 2;
										Q_PowerBlade->PowerBlade[Count].Init = 3;
#endif

										Q_PowerBlade->PowerBlade[Count].TargetID = Q_PowerBlade->PowerBlade[Count].AvID;
										Q_PowerBlade->PowerBlade[Count].TargetLock = 1;
										Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].TraVec);
										}//END Deflect
									else
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;
										Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Xform;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

											//# Deduct Health
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_LastAvatarHitID = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID;
										/*if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_HReduceON == 0)*/ Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceOld = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health;

												//Rework Needed here very messy , plus add a random factor
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health -= 70*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
										if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health < 0) Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health = 0;

										//### Experience Storage
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] += 70*((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Constitution / 400)) + 0.75);


										if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health <= 0)
											{
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health = 0;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 17;

											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Dead = 1;

											jet = 0;
											while(jet < 5)
												{
												Q.AISpawnNNbot(Q_PowerBlade->PowerBlade[Count].AvID, Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].AV.Xform.Translation);

												jet++;
												}

											//### Add XP to avatar
											if((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10)) > 0)
												{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_PowerBlade->PowerBlade[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10); }

											//##### Find KO Owner
											UniversalDMGSTR = 0;
											
											if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

											jet = 0;
											while(jet < _->NomAI)
												{
												if(Q_Forge->Forge[jet].LIVE == 1)
													{
													if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
													}
												jet++;
												}

											if(DeliverKOID == 250)
												{
												//### Create Item for attacking Avatar
												Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

												if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].DecFinger <= 50)
													{
													player[g_Player]->MSG_ItemREF = Q.New_New_CreatePlayerItem(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level);
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
													if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10)) > 0)
														{
														//### Add Experience to attacking AVATAR
														player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10);

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
																Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level);

																Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																}
															else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level);
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

										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_HReduceON = 1;
										
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceHInc = 10;
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceHeight = 573;
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.red = 255;
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.green = 0;
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.blue = 0;
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.alpha = 255;

										if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Avatar != 0)
											{
											Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[2].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[3].Xform.Translation);
											Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Avatar, &Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Xform);
											Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[2].Avatar, &Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[2].Xform);
											Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[3].Avatar, &Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[3].Xform);
											}

										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * 20;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

										//###Hit Reactions
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HitReactScale = 0.025;	//0.05
										
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactVec = Q_PowerBlade->PowerBlade[Count].TraVec;
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactSpeed = 6;

										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_Energy += 10;
										if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_Energy > Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_MaxEnergy) Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_Energy = Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvID].HB_MaxEnergy;
								
										//## Reset Hit Wall
										Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HitWall = 0;

										//## Hit Reaction Motions
										
										if(Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Aposestate != 30)	//Standard Hit Reactions
											{
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Aposestate = 30;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].attackon = 1;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].attposecnt = 0;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].astackcnt = 0;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].astackrun = 0;
											}
										else
											{
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].attposecnt = 2.08;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].attackon = 1;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].astackcnt = 0;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].astackrun = 0;
											}

										//Increment number of MeleeHits
										_->NomMelHit += 1;

										if((Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK <= 0) && (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Block == 1 && Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHeight == 3))
											{
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower / 100)) + 1);

											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactSpeed = 4;

											//### Block Hit Flash

											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																				//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
											Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 60;				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 160;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 0;

												//Increment number of MeleeHits
											_->NomMelHit += 1;
											}//END Powerbank zeroed

										}//END Else Deflect

									}//END Block Test
								else
									{
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower / 100)) + 1);

									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactSpeed = 6;

									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].Blocking = 1;
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHit = 1;
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHitFLAG = 1;
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].attposecnt = 0;
									Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHitID = _->NomMelHit;

									//### Block Hit Flash

									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
									Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_PowerBlade->PowerBlade[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;

										//Increment number of MeleeHits
									_->NomMelHit += 1;

									QpoVec3d Addition,TraVecStore;
									Qpo->Vec3d_Inverse(&Q_PowerBlade->PowerBlade[Count].TraVec);
									TraVecStore = Q_PowerBlade->PowerBlade[Count].TraVec;
									Qpo->Vec3d_Normalize(&TraVecStore);
									
									Addition.x += ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.y += ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.z += ((((float)rand() / 32767) * 1) -0.5) * 0.4;

									Qpo->Vec3d_Normalize(&Addition);
									Qpo->Vec3d_Subtract(&Addition, &TraVecStore, &Addition);
									Qpo->Vec3d_Scale(&Addition, 5, &Addition);

									Qpo->Vec3d_Add(&Q_PowerBlade->PowerBlade[Count].TraVec, &Addition, &Q_PowerBlade->PowerBlade[Count].TraVec);
									}//END Block Test

								}//END Anti Mult Hits

							}//END AI hits			***

						}//END quick actor check	***

					}//END Collision NULL
				else //##### Hit Geometry
					{
					Q_PowerBlade->PowerBlade[Count].Live = 0;
					if(Q_PowerBlade->PowerBlade[Count].Light != NULL) Qpo->Light_Remove(Q_PowerBlade->PowerBlade[Count].Light);
					if(Q_PowerBlade->PowerBlade[Count].Sound != NULL) Qpo->Sound_Stop(Q_PowerBlade->PowerBlade[Count].Sound);

					helly = 0;
					while(helly < Q_PowerBlade->PowerBlade[Count].NomActors)
						{
						Qpo->Vec3d_Copy(&_->Origon, &Q_PowerBlade->PowerBlade[Count].AvatarFlag[helly].Xform.Translation);
						helly++;
						}

					//### Energy Array Reorder
					K = Count;
					while(K < _->NomPowerBlade - 1)
						{
						Q_PowerBlade->PowerBlade[K] = Q_PowerBlade->PowerBlade[K+1];
						K++;
						}

					_->NomPowerBlade--;
					}

				}

			}//END Collision

		}//END Else Origin
		
	Q_PowerBlade->PowerBlade[Count].LightPos = Q_PowerBlade->PowerBlade[Count].LOldPos;
#endif
	}

void Q_EFFCon::SEnergy_PowerBlade_ClientFrame(int Count)
	{

	}

};