/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Renzou Disc-

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

float i_Xrotate = 0;
float i_Yrotate = 0;
float i_Zrotate = 0;
int i_switch = 0;
int i_switch2 = 0;

using namespace GVARS;

namespace GVARS
{

	//########  - SMALL ENERGY ATTACKS -  ########//

void Q_EFFCon::SEnergy_Renzou_ServerFrame(int Count)
	{
	if(Q_SEnergy->SEnergy[Count].Init == 1)
		{
		helly = 0;
		while(helly < Q_SEnergy->SEnergy[Count].NomActors)
			{
#pragma message("Server engine is oblivious rendering matrices")
#if defined(WIN32)
#if 0 // QAGE_DESKTOP
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleY), 0.0f, 1.0f, 0.0f);
			glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleX), 1.0f, 0.0f, 0.0f);
			glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleZ), 0.0f, 0.0f, 1.0f);

			glGetFloatv(GL_MODELVIEW_MATRIX, Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform.Matrix.mf);
#endif
#endif

#if 1
			i_Yrotate += 0.085 * _->TimeScale;

			if(i_switch == 0)
				{
				if(i_Xrotate > ((PI/2)/2))
					{
					i_switch = 1;
					i_Xrotate = ((PI/2)/2);
					}
				else i_Xrotate += 0.001 * _->TimeScale;
				}
			else
				{
				if(i_Xrotate < -((PI/2)/2))
					{
					i_switch = 0;
					i_Xrotate = -((PI/2)/2);
					}
				else i_Xrotate -= 0.001 * _->TimeScale;
				}
#endif

#if 0
			if(i_switch2 == 0)
				{
				if(i_Zrotate > ((PI/2)/2))
					{
					i_switch2 = 1;
					i_Zrotate = ((PI/2)/2);
					}
				else i_Zrotate += 0.01 * _->TimeScale;
				}
			else
				{
				if(i_Zrotate < -((PI/2)/2))
					{
					i_switch2 = 0;
					i_Zrotate = -((PI/2)/2);
					}
				else i_Zrotate -= 0.01 * _->TimeScale;
				}
#endif

#if 0
			//glRotatef(radToDeg(i_Zrotate), 0.0f, 0.0f, 1.0f);
			glRotatef(radToDeg(i_Yrotate), 0.0f, 1.0f, 0.0f);

			glRotatef(radToDeg(i_Xrotate), 1.0f, 0.0f, 0.0f);

			glGetFloatv(GL_MODELVIEW_MATRIX, Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform.Matrix.mf);

			//Qpo->Transform_New(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform);
			//Qpo->Transform_RotateX(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform, i_Xrotate);
			//Qpo->Transform_RotateY(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform, i_Yrotate);

			
			//Qpo->Transform_RotateY(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform, i_Yrotate);

			//Qpo->Transform_New_XRotation(&AIfriendly, i_Xrotate);
			//Qpo->Transorm_Multiply(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform);
#endif

			helly++;
			}

#pragma message("Server engine is oblivious rendering matrices")
#if defined(WIN32)
#if 0 // QAGE_DESKTOP
		glLoadIdentity();

		glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleX), 1.0f, 0.0f, 0.0f);
		glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleY), 0.0f, 0.0f, 1.0f);
		//glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleZ), 0.0f, 1.0f, 0.0f);	//Flight Twist
		
		glGetFloatv(GL_MODELVIEW_MATRIX, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform.Matrix.mf);
#endif
#endif

		Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &Q_SEnergy->SEnergy[Count].TraVec);

#if 0
		Qpo->Camera_Set();

		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glDisable(GL_BLEND);								// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

		glColor3f(1.0f, 1.0f, 0.25f);	//RED
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x, Q_SEnergy->SEnergy[Count].LightPos.y, Q_SEnergy->SEnergy[Count].LightPos.z);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (Q_SEnergy->SEnergy[Count].TraVec.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (Q_SEnergy->SEnergy[Count].TraVec.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (Q_SEnergy->SEnergy[Count].TraVec.z * 250));
		//*glEnd();
#endif
		}

	if(Q_SEnergy->SEnergy[Count].Init == 0)
		{
		Q_SEnergy->SEnergy[Count].Init = 1;

		Q_SEnergy->SEnergy[Count].NomActors = 5;
		Q_SEnergy->SEnergy[Count].Scale = 0.01;
		Q_SEnergy->SEnergy[Count].ScaleMode = 0;
		Q_SEnergy->SEnergy[Count].Alpha = 0;
		Q_SEnergy->SEnergy[Count].AlphaInc = 50;
		Q_SEnergy->SEnergy[Count].AlphaScale[0] = 1;
		Q_SEnergy->SEnergy[Count].AlphaScale[1] = 0.9;
		Q_SEnergy->SEnergy[Count].AlphaScale[2] = 0.8;
		Q_SEnergy->SEnergy[Count].AlphaScale[3] = 0.6;
		Q_SEnergy->SEnergy[Count].AlphaScale[4] = 0.3;
		Q_SEnergy->SEnergy[Count].Speed = 0;

#if 1
		Q_SEnergy->SEnergy[Count].SpeedScale[0] = 0;
		Q_SEnergy->SEnergy[Count].SpeedScale[1] = 0.3;
		Q_SEnergy->SEnergy[Count].SpeedScale[2] = 0.6;
		Q_SEnergy->SEnergy[Count].SpeedScale[3] = 0.9;
		Q_SEnergy->SEnergy[Count].SpeedScale[4] = 1.2;
#endif

#if 0
		Q_SEnergy->SEnergy[Count].SpeedScale[0] = 0;
		Q_SEnergy->SEnergy[Count].SpeedScale[1] = 0.02;
		Q_SEnergy->SEnergy[Count].SpeedScale[2] = 0.05;
		Q_SEnergy->SEnergy[Count].SpeedScale[3] = 0.08;
		Q_SEnergy->SEnergy[Count].SpeedScale[4] = 0.12;
#endif

		Q_SEnergy->SEnergy[Count].LightColor.red = 255.0f;
		Q_SEnergy->SEnergy[Count].LightColor.green = 255.0f;
		Q_SEnergy->SEnergy[Count].LightColor.blue = 200.0f;
		Q_SEnergy->SEnergy[Count].LightColor.alpha = 255.0f;
		Q_SEnergy->SEnergy[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);

		jet=0;
		while(jet < Q_SEnergy->SEnergy[Count].NomActors)
			{
			Qpo->Mesh_SetScale(&Q_SEnergy->SEnergy[Count].AvatarFlag[jet], 0.01f,0.01f,0.01f);
			//Qpo->Avatar_SetLighting(&Q_SEnergy->SEnergy[Count].AvatarFlag[jet].Avatar, false, &goup, 0, 0, 0, 255, 255, 255, false, 0, NULL, false);
			Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].AvatarFlag[jet].Xform.Translation);
			jet++;
			}

		//RESET MULTIPLE HIT COUNTER
		Q_SEnergy->SEnergy[Count].AntiMultHits[250] = 0;
		jet=0;
		while(jet < _->NomAI)
			{
			Q_SEnergy->SEnergy[jet].AntiMultHits[jet] = 0;
			jet++;
			}

		/*//QpoSound3D_GetConfig(World,
			&player[g_Player]->ViewXForm,
			&Q_SEnergy->SEnergy[Count].LightPos,
			600.0f,
			2.0f,
			&Volume,
			&Pan,
			&Frequency);*/
		
		Q_SEnergy->SEnergy[Count].Sound = Qpo->Sound_Play(Medias->S_Renzou, _->Volume, _->Pan, _->S_TimeScale, true, &Q_SEnergy->SEnergy[Count].LightPos);

		helly = 0;
		while(helly < Q_SEnergy->SEnergy[Count].NomActors)
			{
			Qpo->Transform_GetLeft(&Q_SEnergy->SEnergy[Count].Matrix, &Q_SEnergy->SEnergy[Count].Left);
			Qpo->Transform_GetUp(&Q_SEnergy->SEnergy[Count].Matrix, &Q_SEnergy->SEnergy[Count].Up);
			Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].Matrix, &Q_SEnergy->SEnergy[Count].In);

			Qpo->Transform_New(&Q_SEnergy->SEnergy[Count].Matrix2);
			Qpo->Transform_GetUp(&Q_SEnergy->SEnergy[Count].Matrix2, &Q_SEnergy->SEnergy[Count].Up2);

			Q_SEnergy->SEnergy[Count].HeadLeft = Q_SEnergy->SEnergy[Count].Left;
			Q_SEnergy->SEnergy[Count].HeadLeft.y = Q_SEnergy->SEnergy[Count].Up2.y;
			Q_SEnergy->SEnergy[Count].Dist = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].HeadLeft, &Q_SEnergy->SEnergy[Count].Up2);


			//IMP MIGHT NEED TO MOVE THIS LINE DOWN TO BELOW ROTATEZ

			//### Get Matrix Direction Vectors
			Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].Matrix2, &Q_SEnergy->SEnergy[Count].CURRTraVec);
			Qpo->Transform_GetLeft(&Q_SEnergy->SEnergy[Count].Matrix2, &Q_SEnergy->SEnergy[Count].LeftVec);

			//### Stabilise Trajectories
			
			Qpo->Vec3d_Normalize(&Q_SEnergy->SEnergy[Count].TraVec);
			Q_SEnergy->SEnergy[Count].TraVec.y = 0;
			
			Qpo->Vec3d_Normalize(&Q_SEnergy->SEnergy[Count].CURRTraVec);
			Q_SEnergy->SEnergy[Count].CURRTraVec.y = 0;

			//### Find Opposite Length
			Q_SEnergy->SEnergy[Count].TrajDIST = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].CURRTraVec);
			Q_SEnergy->SEnergy[Count].TrajDIST /= 2;

			Q_SEnergy->SEnergy[Count].AngleY = asin( Q_SEnergy->SEnergy[Count].TrajDIST ) * 2;	//(PI/2);	//2

			//if(Q_SEnergy->SEnergy[Count].AngleY > 0.25) Q_SEnergy->SEnergy[Count].AngleY = 0.25;
			//if(Q_SEnergy->SEnergy[Count].AngleY < -0.25) Q_SEnergy->SEnergy[Count].AngleY = -0.25;

			//### Find distance between pure left and right to find turn direction
			Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].LeftVec, &Q_SEnergy->SEnergy[Count].Right);
			Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].Right);

			Q_SEnergy->SEnergy[Count].ScanDistLeft = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].LeftVec);
			Q_SEnergy->SEnergy[Count].ScanDistRight = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].Right);

			if(Q_SEnergy->SEnergy[Count].ScanDistLeft > Q_SEnergy->SEnergy[Count].ScanDistRight) Q_SEnergy->SEnergy[Count].AngleY *= -1;

			Q_SEnergy->SEnergy[Count].AngleX = 0;

			if(Q_SEnergy->SEnergy[Count].Dist < 0.4)
				{
				Q_SEnergy->SEnergy[Count].ShotSpin = 0;
				Q_SEnergy->SEnergy[Count].AngleZ = 0;
				}
			else
				{
				Q_SEnergy->SEnergy[Count].ShotSpin = 1;
				Q_SEnergy->SEnergy[Count].AngleZ = Q_SEnergy->SEnergy[Count].Dist;
				}

			if(Q_SEnergy->SEnergy[Count].AngleZ > PI * 2) Q_SEnergy->SEnergy[Count].AngleZ = Q_SEnergy->SEnergy[Count].AngleZ - (PI*2);
			if(Q_SEnergy->SEnergy[Count].AngleZ < 0) Q_SEnergy->SEnergy[Count].AngleZ = (PI*2) - Q_SEnergy->SEnergy[Count].AngleZ;

#pragma message("Server engine is oblivious rendering matrices")
#if defined(WIN32)
#if 0 // QAGE_DESKTOP
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleY), 0.0f, 1.0f, 0.0f);
			glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleX), 1.0f, 0.0f, 0.0f);
			glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleZ), 0.0f, 0.0f, 1.0f);

			glGetFloatv(GL_MODELVIEW_MATRIX, Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Viewform.Matrix.mf);
#endif
#endif

			helly++;
			}

#pragma message("Server engine is oblivious rendering matrices")
#if defined(WIN32)
#if 0 // QAGE_DESKTOP
		glLoadIdentity();

		glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleX), 1.0f, 0.0f, 0.0f);
		glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleY), 0.0f, 0.0f, 1.0f);
		//glRotatef(radToDeg(Q_SEnergy->SEnergy[Count].AngleZ), 0.0f, 1.0f, 0.0f);	//Flight Twist

		glGetFloatv(GL_MODELVIEW_MATRIX, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform.Matrix.mf);
#endif
#endif

		Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &Q_SEnergy->SEnergy[Count].TraVec);
		}

		//Set Alpha
	if(Q_SEnergy->SEnergy[Count].Alpha + (Q_SEnergy->SEnergy[Count].AlphaInc*_->TimeScale) <= 255) Q_SEnergy->SEnergy[Count].Alpha += Q_SEnergy->SEnergy[Count].AlphaInc*_->TimeScale;
	else Q_SEnergy->SEnergy[Count].Alpha = 255;

		//Set Speed
	if(Q_SEnergy->SEnergy[Count].Speed + (Q_SEnergy->SEnergy[Count].SpeedInc*2*_->TimeScale) <= Q_SEnergy->SEnergy[Count].SpeedMax * 5) Q_SEnergy->SEnergy[Count].Speed += Q_SEnergy->SEnergy[Count].SpeedInc*_->TimeScale;
	else Q_SEnergy->SEnergy[Count].Speed = Q_SEnergy->SEnergy[Count].SpeedMax;

	//##### Scale Control #####
	if(Q_SEnergy->SEnergy[Count].ScaleMode == 0)
		{
		if(Q_SEnergy->SEnergy[Count].Scale + (Q_SEnergy->SEnergy[Count].ScaleInc*_->TimeScale) <= Q_SEnergy->SEnergy[Count].ScaleMax) Q_SEnergy->SEnergy[Count].Scale += Q_SEnergy->SEnergy[Count].ScaleInc*_->TimeScale;
		else
			{
			Q_SEnergy->SEnergy[Count].Scale = Q_SEnergy->SEnergy[Count].ScaleMax;
			Q_SEnergy->SEnergy[Count].ScaleMode = 1;
			}
		}
	else
		{
		Q_SEnergy->SEnergy[Count].RandomInput = ((((float)rand() / 32767) - 0.5) / 10) * _->TimeScale;
		Q_SEnergy->SEnergy[Count].Scale = Q_SEnergy->SEnergy[Count].ScaleMax + Q_SEnergy->SEnergy[Count].RandomInput;
		}

	if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
		{
		//#### Show Target Locks
		if(Q_SEnergy->SEnergy[Count].DisplayAlpha - 15 > 120) Q_SEnergy->SEnergy[Count].DisplayAlpha -= 15;
		else Q_SEnergy->SEnergy[Count].DisplayAlpha = 120;

		if(Q_SEnergy->SEnergy[Count].DisplayColor - 25 > 0) Q_SEnergy->SEnergy[Count].DisplayColor -= 25;
		else Q_SEnergy->SEnergy[Count].DisplayColor = 0;

		if(Q_SEnergy->SEnergy[Count].DisplayScale + 0.05 < 0.75) Q_SEnergy->SEnergy[Count].DisplayScale += 0.06;
		else Q_SEnergy->SEnergy[Count].DisplayScale = 0.75;
		
		if(Q_SEnergy->SEnergy[Count].AvID == 250)
			{
			player[g_Player]->LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
			player[g_Player]->LaserLV.r = 255;
			player[g_Player]->LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
			player[g_Player]->LaserLV.b = 0;
			player[g_Player]->LaserLV.x = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.x;
			player[g_Player]->LaserLV.y = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.y + 65;
			player[g_Player]->LaserLV.z = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.z;

			Qpo->Poly_AddOnce(&player[g_Player]->LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
			}
		else
			{
			if(Q_SEnergy->SEnergy[Count].TargetID == 250)
				{
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
				}
			else
				{
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.x = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.x;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.y = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.y + 65;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.z = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
				}
			}

		if(Q_SEnergy->SEnergy[Count].TargetID == 250)
			{
			Q_SEnergy->SEnergy[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
			//Q_SEnergy->SEnergy[Count].TargetVec.y += 65;
			Q_SEnergy->SEnergy[Count].TargetVec.y += 45;
			}
		else
			{
			Q_SEnergy->SEnergy[Count].TargetVec = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation;
			//Q_SEnergy->SEnergy[Count].TargetVec.y += 65;
			Q_SEnergy->SEnergy[Count].TargetVec.y += 45;
			}

		//### Build Ghost Matrix

		Qpo->Vec3d_Subtract(&Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].TargetVec);
		Qpo->Vec3d_Normalize(&Q_SEnergy->SEnergy[Count].TargetVec);
		Qpo->Vec3d_Scale(&Q_SEnergy->SEnergy[Count].TargetVec, 150, &Q_SEnergy->SEnergy[Count].TargetVec);

		Qpo->Transform_GetLeft(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &Q_SEnergy->SEnergy[Count].Left);
		Qpo->Transform_GetUp(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &Q_SEnergy->SEnergy[Count].Up);
		Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &Q_SEnergy->SEnergy[Count].ForVec);

#if 0
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glDisable(GL_BLEND);								// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

		QpoVec3d i_Vector;
		Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &i_Vector);
		Qpo->Camera_Set();
		glColor3f(1.0f, 0.0f, 0.0f);	//RED
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + 5, Q_SEnergy->SEnergy[Count].LightPos.y + 5, Q_SEnergy->SEnergy[Count].LightPos.z + 5);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();

		Qpo->Transform_GetLeft(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &i_Vector);
		Qpo->Camera_Set();
		glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + 5, Q_SEnergy->SEnergy[Count].LightPos.y + 5, Q_SEnergy->SEnergy[Count].LightPos.z + 5);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();

		Qpo->Transform_GetUp(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &i_Vector);
		Qpo->Camera_Set();
		glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + 5, Q_SEnergy->SEnergy[Count].LightPos.y + 5, Q_SEnergy->SEnergy[Count].LightPos.z + 5);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();
#endif

		Q_SEnergy->SEnergy[Count].LeftVec = Q_SEnergy->SEnergy[Count].Left;
		Q_SEnergy->SEnergy[Count].UpVec = Q_SEnergy->SEnergy[Count].Up;
		//Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].UpVec);

		Qpo->Vec3d_Scale(&Q_SEnergy->SEnergy[Count].ForVec, 150, &Q_SEnergy->SEnergy[Count].ForVec);
		Qpo->Vec3d_Scale(&Q_SEnergy->SEnergy[Count].LeftVec, 150, &Q_SEnergy->SEnergy[Count].LeftVec);
		Qpo->Vec3d_Scale(&Q_SEnergy->SEnergy[Count].UpVec, 150, &Q_SEnergy->SEnergy[Count].UpVec);

#if 1
		if(Q_SEnergy->SEnergy[Count].ShotSpin == 0)
			{
			Q_SEnergy->SEnergy[Count].AngleZ += 0.035 * _->TimeScale;
			}

		if(Q_SEnergy->SEnergy[Count].ShotSpin == 1)
			{
			Q_SEnergy->SEnergy[Count].AngleZ += 0.17 * _->TimeScale;
			}

		if(Q_SEnergy->SEnergy[Count].AngleZ > PI * 2) Q_SEnergy->SEnergy[Count].AngleZ = Q_SEnergy->SEnergy[Count].AngleZ - (PI*2);
		if(Q_SEnergy->SEnergy[Count].AngleZ < 0) Q_SEnergy->SEnergy[Count].AngleZ = (PI*2) - Q_SEnergy->SEnergy[Count].AngleZ;

		//### Renzou Actors are upright
		if( ((Q_SEnergy->SEnergy[Count].AngleZ > (PI + (PI/2))) && (Q_SEnergy->SEnergy[Count].AngleZ < (PI*2))) || ((Q_SEnergy->SEnergy[Count].AngleZ < (PI/2)) && (Q_SEnergy->SEnergy[Count].AngleZ > 0)) )
			{
			if( (Q_SEnergy->SEnergy[Count].AngleZ > (PI + (PI/2))) && (Q_SEnergy->SEnergy[Count].AngleZ < (PI*2)) )
				{
				Q_SEnergy->SEnergy[Count].AngYIncFactor = ((Q_SEnergy->SEnergy[Count].AngleZ - (PI + (PI/2))) / (PI/2)) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				Q_SEnergy->SEnergy[Count].AngXIncFactor = (1 - ((Q_SEnergy->SEnergy[Count].AngleZ - (PI + (PI/2))) / (PI/2))) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				}

			if( (Q_SEnergy->SEnergy[Count].AngleZ < (PI/2)) && (Q_SEnergy->SEnergy[Count].AngleZ > 0) )
				{
				Q_SEnergy->SEnergy[Count].AngYIncFactor = (1 - (Q_SEnergy->SEnergy[Count].AngleZ / (PI/2))) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				Q_SEnergy->SEnergy[Count].AngXIncFactor = (Q_SEnergy->SEnergy[Count].AngleZ / (PI/2)) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				}
			}
		else  //### Renzou Actors are up-side-down
			{
			if( (Q_SEnergy->SEnergy[Count].AngleZ > (PI/2)) && (Q_SEnergy->SEnergy[Count].AngleZ < PI) )
				{
				Q_SEnergy->SEnergy[Count].AngYIncFactor = ((Q_SEnergy->SEnergy[Count].AngleZ - (PI/2)) / (PI/2)) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				Q_SEnergy->SEnergy[Count].AngXIncFactor = (1- ((Q_SEnergy->SEnergy[Count].AngleZ - (PI/2)) / (PI/2))) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				}

			if( (Q_SEnergy->SEnergy[Count].AngleZ > PI) && (Q_SEnergy->SEnergy[Count].AngleZ < (PI + (PI/2))) )
				{
				Q_SEnergy->SEnergy[Count].AngYIncFactor = (1 - ((Q_SEnergy->SEnergy[Count].AngleZ) / (PI/2))) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				Q_SEnergy->SEnergy[Count].AngXIncFactor = ((Q_SEnergy->SEnergy[Count].AngleZ) / (PI/2)) * Q_SEnergy->SEnergy[Count].Const_AngleInc;
				}
			}
#endif
		//Q_SEnergy->SEnergy[Count].AngYIncFactor *= 5;

		//Work Out Turn Angles
		Q_SEnergy->SEnergy[Count].TargetVecSTR = Q_SEnergy->SEnergy[Count].TargetVec;

#if 0
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glDisable(GL_BLEND);								// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

		QpoVec3d i_Vector = Q_SEnergy->SEnergy[Count].TargetVec;
		Qpo->Camera_Set();
		glColor3f(1.0f, 0.0f, 1.0f);
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x, Q_SEnergy->SEnergy[Count].LightPos.y, Q_SEnergy->SEnergy[Count].LightPos.z);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();
#endif

		Q_SEnergy->SEnergy[Count].TargetVec.y = Q_SEnergy->SEnergy[Count].ForVec.y;
		Qpo->Vec3d_Subtract(&Q_SEnergy->SEnergy[Count].ForVec, &Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].ScanTurnVec);
		Q_SEnergy->SEnergy[Count].ScanTurnAngLR = Qpo->Vec3d_Length(&Q_SEnergy->SEnergy[Count].ScanTurnVec);
		Q_SEnergy->SEnergy[Count].ScanTurnAngLR /= ((Q_SEnergy->SEnergy[Count].Accuracy * 10000) * (Q_SEnergy->SEnergy[Count].Const_AngleInc - Q_SEnergy->SEnergy[Count].AngYIncFactor));	//500
		//Q_SEnergy->SEnergy[Count].ScanTurnAngLR = (Q_SEnergy->SEnergy[Count].ScanTurnAngLR / Q_SEnergy->SEnergy[Count].ScanTurnAngLR) * (Q_SEnergy->SEnergy[Count].Const_AngleInc - Q_SEnergy->SEnergy[Count].AngYIncFactor);

		//Work Out Up Down Angles
		Q_SEnergy->SEnergy[Count].TargetVec = Q_SEnergy->SEnergy[Count].TargetVecSTR;

		Q_SEnergy->SEnergy[Count].TargetVec.x = Q_SEnergy->SEnergy[Count].ForVec.x;
		Q_SEnergy->SEnergy[Count].TargetVec.z = Q_SEnergy->SEnergy[Count].ForVec.z;
		Qpo->Vec3d_Subtract(&Q_SEnergy->SEnergy[Count].ForVec, &Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].ScanTurnVec);
		Q_SEnergy->SEnergy[Count].ScanTurnAngUD = Qpo->Vec3d_Length(&Q_SEnergy->SEnergy[Count].ScanTurnVec);
		Q_SEnergy->SEnergy[Count].ScanTurnAngUD /= ((Q_SEnergy->SEnergy[Count].Accuracy * 10000) * (Q_SEnergy->SEnergy[Count].Const_AngleInc - Q_SEnergy->SEnergy[Count].AngXIncFactor));	//500
		//Q_SEnergy->SEnergy[Count].ScanTurnAngUD = (Q_SEnergy->SEnergy[Count].ScanTurnAngUD / Q_SEnergy->SEnergy[Count].ScanTurnAngUD) * (Q_SEnergy->SEnergy[Count].Const_AngleInc - Q_SEnergy->SEnergy[Count].AngXIncFactor);

		Q_SEnergy->SEnergy[Count].TargetVec = Q_SEnergy->SEnergy[Count].TargetVecSTR;
		
		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].LeftVec, &Q_SEnergy->SEnergy[Count].Right);
		Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].UpVec, &Q_SEnergy->SEnergy[Count].RDown);
		Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].Right);
		Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].RDown);

		Q_SEnergy->SEnergy[Count].ScanDistLeft = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].LeftVec);
		Q_SEnergy->SEnergy[Count].ScanDistRight = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].Right);
		Q_SEnergy->SEnergy[Count].ScanDistUp = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].UpVec);
		Q_SEnergy->SEnergy[Count].ScanDistDown = Qpo->Vec3d_DistanceBetween(&Q_SEnergy->SEnergy[Count].TargetVec, &Q_SEnergy->SEnergy[Count].RDown);

#if 0
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glDisable(GL_BLEND);								// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

		i_Vector = Q_SEnergy->SEnergy[Count].LeftVec;
		Qpo->Camera_Set();
		glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x, Q_SEnergy->SEnergy[Count].LightPos.y, Q_SEnergy->SEnergy[Count].LightPos.z);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();

		i_Vector = Q_SEnergy->SEnergy[Count].Right;
		Qpo->Camera_Set();
		glColor3f(1.0f, 0.0f, 0.0f);	//RED
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x, Q_SEnergy->SEnergy[Count].LightPos.y, Q_SEnergy->SEnergy[Count].LightPos.z);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();

		i_Vector = Q_SEnergy->SEnergy[Count].UpVec;
		Qpo->Camera_Set();
		glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x, Q_SEnergy->SEnergy[Count].LightPos.y, Q_SEnergy->SEnergy[Count].LightPos.z);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();

		i_Vector = Q_SEnergy->SEnergy[Count].RDown;
		Qpo->Camera_Set();
		glColor3f(1.0f, 0.0f, 1.0f);	//PURPLE
		//*glBegin(GL_LINES);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x, Q_SEnergy->SEnergy[Count].LightPos.y, Q_SEnergy->SEnergy[Count].LightPos.z);
		glVertex3f(Q_SEnergy->SEnergy[Count].LightPos.x + (i_Vector.x * 250), Q_SEnergy->SEnergy[Count].LightPos.y + (i_Vector.y * 250), Q_SEnergy->SEnergy[Count].LightPos.z + (i_Vector.z * 250));
		//*glEnd();
#endif

		if(Q_SEnergy->SEnergy[Count].ScanDistLeft > Q_SEnergy->SEnergy[Count].ScanDistRight) Q_SEnergy->SEnergy[Count].ScanTurnAngLR *= -1;
		if(Q_SEnergy->SEnergy[Count].ScanDistUp < Q_SEnergy->SEnergy[Count].ScanDistDown) Q_SEnergy->SEnergy[Count].ScanTurnAngUD *= -1;

		if(Q_SEnergy->SEnergy[Count].ScanTurnAngLR > Q_SEnergy->SEnergy[Count].Accuracy) Q_SEnergy->SEnergy[Count].ScanTurnAngLR = Q_SEnergy->SEnergy[Count].Accuracy;
		if(Q_SEnergy->SEnergy[Count].ScanTurnAngLR < -Q_SEnergy->SEnergy[Count].Accuracy) Q_SEnergy->SEnergy[Count].ScanTurnAngLR = -Q_SEnergy->SEnergy[Count].Accuracy;
		if(Q_SEnergy->SEnergy[Count].ScanTurnAngUD > Q_SEnergy->SEnergy[Count].Accuracy) Q_SEnergy->SEnergy[Count].ScanTurnAngUD = Q_SEnergy->SEnergy[Count].Accuracy;
		if(Q_SEnergy->SEnergy[Count].ScanTurnAngUD < -Q_SEnergy->SEnergy[Count].Accuracy) Q_SEnergy->SEnergy[Count].ScanTurnAngUD = -Q_SEnergy->SEnergy[Count].Accuracy;

#if 1
		Q_SEnergy->SEnergy[Count].AngleX += (Q_SEnergy->SEnergy[Count].ScanTurnAngUD * _->TimeScale);

		if(Q_SEnergy->SEnergy[Count].AngleX > PI*2) Q_SEnergy->SEnergy[Count].AngleX = Q_SEnergy->SEnergy[Count].AngleX - (PI*2);
		if(Q_SEnergy->SEnergy[Count].AngleX < 0) Q_SEnergy->SEnergy[Count].AngleX = (PI*2) - Q_SEnergy->SEnergy[Count].AngleX;
#endif

#if 0
		Q_SEnergy->SEnergy[Count].AngleX += 0.1 * _->TimeScale;
#endif

#if 1
		Q_SEnergy->SEnergy[Count].AngleY += (Q_SEnergy->SEnergy[Count].ScanTurnAngLR * _->TimeScale);

		if(Q_SEnergy->SEnergy[Count].AngleY > PI*2) Q_SEnergy->SEnergy[Count].AngleY = Q_SEnergy->SEnergy[Count].AngleY - (PI*2);
		if(Q_SEnergy->SEnergy[Count].AngleY < 0) Q_SEnergy->SEnergy[Count].AngleY = (PI*2) - Q_SEnergy->SEnergy[Count].AngleY;
#endif
		}

	if(Q_SEnergy->SEnergy[Count].TargetLock == 2 && Q_SEnergy->SEnergy[Count].DisplayAlpha > 0)
		{
		//#### Show Target Locks
		if(Q_SEnergy->SEnergy[Count].DisplayAlpha - 20 > 0) Q_SEnergy->SEnergy[Count].DisplayAlpha -= 20;
		else Q_SEnergy->SEnergy[Count].DisplayAlpha = 0;

		if(Q_SEnergy->SEnergy[Count].DisplayColor - 25 > 0) Q_SEnergy->SEnergy[Count].DisplayColor -= 25;
		else Q_SEnergy->SEnergy[Count].DisplayColor = 0;

		if(Q_SEnergy->SEnergy[Count].DisplayScale + 0.05 < 0.01) Q_SEnergy->SEnergy[Count].DisplayScale += 0.01;
		else Q_SEnergy->SEnergy[Count].DisplayScale = 0.01;

		if(Q_SEnergy->SEnergy[Count].AvID == 250)
			{
			player[g_Player]->LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
			player[g_Player]->LaserLV.r = 255;
			player[g_Player]->LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
			player[g_Player]->LaserLV.b = 0;
			player[g_Player]->LaserLV.x = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.x;
			player[g_Player]->LaserLV.y = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.y + 65;
			player[g_Player]->LaserLV.z = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.z;

			Qpo->Poly_AddOnce(&player[g_Player]->LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
			}
		else
			{
			if(Q_SEnergy->SEnergy[Count].TargetID == 250)
				{
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
				}
			else
				{
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.x = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.x;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.y = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.y + 65;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.z = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
				}
			}
		}

	if(Q_SEnergy->SEnergy[Count].TargetLock == 2)
		{
		//Set Scale
		if(Q_SEnergy->SEnergy[Count].Scale - (0.05 * _->TimeScale) > 0) Q_SEnergy->SEnergy[Count].Scale -= (0.05 * _->TimeScale);
		else
			{
			Q_SEnergy->SEnergy[Count].Scale = 0;
			Q_SEnergy->SEnergy[Count].Live = 0;
			if(Q_SEnergy->SEnergy[Count].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[Count].Light);
			if(Q_SEnergy->SEnergy[Count].Sound != NULL) Qpo->Sound_Stop(Q_SEnergy->SEnergy[Count].Sound);

			helly = 0;
			while(helly < Q_SEnergy->SEnergy[Count].NomActors)
				{
				Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
				helly++;
				}

			//### Energy Array Reorder
			int K = Count;
			while(K < _->NomSEnergy - 1)
				{
				Q_SEnergy->SEnergy[K] = Q_SEnergy->SEnergy[K+1];
				K++;
				}

			_->NomSEnergy--;
			}
		}

		//Set Light Power and Move the Light
	Q_SEnergy->SEnergy[Count].LOldPos = Q_SEnergy->SEnergy[Count].LightPos;
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[Count].LightPos, Q_SEnergy->SEnergy[Count].Speed*_->TimeScale, &Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].LightPos);

	Qpo->Light_SetAttr(Q_SEnergy->SEnergy[Count].Light, &Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].LightColor, Q_SEnergy->SEnergy[Count].Scale * 150, false);

	helly = 0;
	while(helly < Q_SEnergy->SEnergy[Count].NomActors)
		{
		Qpo->Mesh_SetScale(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly], Q_SEnergy->SEnergy[Count].Scale, Q_SEnergy->SEnergy[Count].Scale, Q_SEnergy->SEnergy[Count].Scale);
		Qpo->Mesh_SetAlpha(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly], Q_SEnergy->SEnergy[Count].Alpha * Q_SEnergy->SEnergy[Count].AlphaScale[helly]);

		Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
		Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[Count].LightPos, -(Q_SEnergy->SEnergy[Count].Speed * Q_SEnergy->SEnergy[Count].SpeedScale[helly]), &Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
		helly++;
		}

	Q_SEnergy->SEnergy[Count].LOldPos = Q_SEnergy->SEnergy[Count].LightPos;
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[Count].LightPos, Q_SEnergy->SEnergy[Count].Speed*_->TimeScale, &Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].LightPos);

	Qpo->Sound_Modify(Q_SEnergy->SEnergy[Count].Sound, _->Volume, _->Pan, _->S_TimeScale, &Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].TraVec);

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
						TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
						TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
						while(TESTDist > 1)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Object->Object[SCRAM].Pos);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < Q_Object->Object[SCRAM].Scale)
								{
								//Set Player Enemy Display to correct enemy
								if(Q_SEnergy->SEnergy[Count].AvID == 250)
									{
									player[g_Player]->HB_LastAvatarHitID = (SCRAM + 1) * -1;
									}
								else
									{
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_LastAvatarHitID = (SCRAM + 1) * -1;
									}

								//### Block Hit Flash
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = TESTPosS;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;
								
								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On

								if(Q_SEnergy->SEnergy[Count].AvID == 250)
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3);				//Max Radius
									}
								else
									{
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 200 * ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);				//Max Radius
									}

								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 200;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 60;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 200;

									//Increment number of MeleeHits
								_->NomMelHit += 1;

								if(Q_SEnergy->SEnergy[Count].AvID == 250)
									{
									if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
										{
										if(Q_SEnergy->SEnergy[Count].TargetLock == 1) Q_SEnergy->SEnergy[Count].TargetLock = 2;
										Q_Object->Object[SCRAM].StrengthBANK -= (80*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3));
										}
									}
								else
									{
									if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
										{
										if(Q_SEnergy->SEnergy[Count].TargetLock == 1) Q_SEnergy->SEnergy[Count].TargetLock = 2;
										Q_Object->Object[SCRAM].StrengthBANK -= (80*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3));
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

	if(1)	//Player Fired Projectile
		{
#if 0
		printf("Trace true\n");
		//##### AVATAR SHIELD COLLIDE TEST
		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if((Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (player[g_Player]->Team != Q_Forge->Forge[SCRAM].Team) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
					{
					TESTDist = 100;
					TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
					TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
					while(TESTDist > 1)
						{
						Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

						TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

						TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

						if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
							{
							TESTPosS = TESTPosE;
							TESTDist = 0;

							jet=0;
							while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
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

							if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
								{
								if(Q_SEnergy->SEnergy[Count].TargetLock == 1) Q_SEnergy->SEnergy[Count].TargetLock = 2;
								Q_Forge->Forge[SCRAM].HB_Energy -= (80*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3)) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));
								}
							}
						}
					}
				}
			SCRAM++;
			}

		/*if(Qpo->Collision_RayTest_Avatar(
			&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Mins,
			&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Maxs,
			&Q_SEnergy->SEnergy[Count].LOldPos,
			&Q_SEnergy->SEnergy[Count].LightPos,
			// GE_CONTENTS_CANNOT_OCCUPY
			/* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS *//*
			0xffffffff, NULL, NULL,
			&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision))
			{
			/*if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != 0)
				{
				if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != playerAV[g_Player]->Avatar
				&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[0].Avatar		//**********
				&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[1].Avatar		//Here Set collide flags on actor creation and shorten the 'if'
				&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[2].Avatar		//******
				&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[3].Avatar
				&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[4].Avatar
				&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag != 251)
					{	//#####- Hit Avatar -#####*/

		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if(!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Mins.x) > (Q_SEnergy->SEnergy[Count].LightPos.x + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Maxs.x) < (Q_SEnergy->SEnergy[Count].LightPos.x - 10))) &&
				!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Mins.y) > (Q_SEnergy->SEnergy[Count].LightPos.y + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Maxs.y) < (Q_SEnergy->SEnergy[Count].LightPos.y - 10))) &&
				!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Mins.z) > (Q_SEnergy->SEnergy[Count].LightPos.z + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Maxs.z) < (Q_SEnergy->SEnergy[Count].LightPos.z - 10))))
					{
					Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag = SCRAM;
					Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
					Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y += 45;

					if(Q_SEnergy->SEnergy[Count].AntiMultHits[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] < 1)
						{
						Q_SEnergy->SEnergy[Count].AntiMultHits[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag]++;
				
							//##### Check Target Lock
						if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
							{ if(Q_SEnergy->SEnergy[Count].TargetID == Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag) Q_SEnergy->SEnergy[Count].TargetLock = 2; }

						//#### Energy Attack Power
						player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Power / 5000) * 10) + 1;
						player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER *= ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower / 100);

						//######## Aggressive to defensive power check
						if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].BlockHeight == 3)
							{
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK -= ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.ATTACKPOWER);

							if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK = 0;

							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.PBTIMER = TIME;
							}

						//### Check to Determine if Avatar is Blocking
						if((!(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].BlockHeight == 3) || (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK <= 0)) && (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Dead == 0))
							{
							//### Check if Avatar Is Deflecting
							if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].DeflectLethal == 1)
								{
								Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;						//Number index of the bone hit

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

								Q_SEnergy->SEnergy[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
								Q_SEnergy->SEnergy[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);

#if 0
								Q_SEnergy->SEnergy[Count].TargetLock = 2;
								Q_SEnergy->SEnergy[Count].Init = 3;
#endif
								Q_SEnergy->SEnergy[Count].TargetID = Q_SEnergy->SEnergy[Count].AvID;
								Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].TraVec);
								}//END Deflect
							else
								{
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

									//# Deduct Health
								player[g_Player]->HB_LastAvatarHitID = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag;
								/*if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_HReduceON == 0)*/ Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceOld = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Health;

										//Rework Needed here very messy , plus add a random factor
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Health -= 70*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
								if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Health < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Health = 0;

								//### Experience Storage
								player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] += 70*((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.Constitution / 400)) + 0.75);


								if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Health <= 0)
									{
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Health = 0;

									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 17;

									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_Dead = 1;

									if((player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10)) > 0)
										{
										//### Add Experience to attacking AVATAR
										player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10);

										player[g_Player]->MSG_XPON = 1;
										player[g_Player]->MSG_XPInit = 0;
										player[g_Player]->MSG_XPScreenDIST = 0;
										player[g_Player]->MSG_XPScreenDistINC = 50;
										player[g_Player]->MSG_XPScreenDIR = 0;
										player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10);
										}

									//##### Find KO Owner
									UniversalDMGSTR = 0;
									
									if(player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

									jet = 0;
									while(jet < _->NomAI)
										{
										if(Q_Forge->Forge[jet].LIVE == 1)
											{
											if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
											}
										jet++;
										}

									if(DeliverKOID == 250)
										{
										//### Create Item for attacking Avatar
										player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

										if(player[g_Player]->DecFinger <= 50)
											{
											player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level);
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
											if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10)) > 0)
												{
												//### Add Experience to attacking AVATAR
												player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10);

												g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level / 10);

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
														Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level);

														Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
														}
													else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.Level);
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



								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_HReduceON = 1;
								
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceHInc = 10;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceHeight = 573;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceRectColor.red = 255;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceRectColor.green = 0;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceRectColor.blue = 0;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HB_ReduceRectColor.alpha = 255;

								if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[1].Avatar != 0)
									{
									Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[1].Xform.Translation);
									Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[2].Xform.Translation);
									Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[3].Xform.Translation);
									Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[1].Avatar, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[1].Xform);
									Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[2].Avatar, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[2].Xform);
									Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[3].Avatar, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Shadows[3].Xform);
									}

								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3) * 20;

								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90

								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

								//###Hit Reactions
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HitReactScale = 0.025;	//0.05
								
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].MoveReactVec = Q_SEnergy->SEnergy[Count].TraVec;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

								player[g_Player]->HB_Energy += 10;
								if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = 200;
						
								//## Reset Hit Wall
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HitWall = 0;

								//## Hit Reaction Motions
								
								if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Aposestate != 30)	//Standard Hit Reactions
									{
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Aposestate = 30;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].attackon = 1;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].attposecnt = 0;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].astackcnt = 0;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].astackrun = 0;
									}
								else
									{
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].attposecnt = 2.08;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].attackon = 1;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].astackcnt = 0;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].astackrun = 0;
									}

								//Increment number of MeleeHits
								_->NomMelHit += 1;

								if((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK <= 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].BlockHeight == 3))
									{
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.DefPower / 100)) + 1);

									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].MoveReactSpeed = 4 * RENZOU_SCALE_IMP;

									//### Block Hit Flash

									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;

																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
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

								}//END Not Deflecting

							}//END Block Test
						else
							{
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.DefPower / 100)) + 1);

							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].Blocking = 1;
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].BlockHit = 1;
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].BlockHitFLAG = 1;
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].attposecnt = 0;
							Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].BlockHitID = _->NomMelHit;

							//### Block Hit Flash

							Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
							Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
							Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
							Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
																//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
							Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact;	//Point of impact in world space
							Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
							Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
							Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
							Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

							//Expandro3D Struct
							Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
							Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
							Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
							Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
							Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
							Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;

								//Increment number of MeleeHits
							_->NomMelHit += 1;
							}//END Block Test

						}//END Anti Multiple Hits

					}//END quick Actor check

				}//END Actor Not Null

#if 0
			if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar == 0)	//##### Hit Geometry
				{
				Q_SEnergy->SEnergy[Count].Live = 0;
				if(Q_SEnergy->SEnergy[Count].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[Count].Light);
				if(Q_SEnergy->SEnergy[Count].Sound != NULL) Qpo->Sound_Stop(Q_SEnergy->SEnergy[Count].Sound);

				helly = 0;
				while(helly < Q_SEnergy->SEnergy[Count].NomActors)
					{
					Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
					helly++;
					}

				//### Energy Array Reorder
				K = Count;
				while(K < _->NomSEnergy - 1)
					{
					Q_SEnergy->SEnergy[K] = Q_SEnergy->SEnergy[K+1];
					K++;
					}

				_->NomSEnergy--;
				}
#endif

#pragma message("FIXME Raypicking from DigiMass select actor to avatar pointers for collision tree")
			SCRAM++;
			}//END Collision

		}//END AvID
	else	//AI FIRED PROJECTILE
#endif
		{
		//PLAYER SHIELD CHECK
		if((player[g_Player]->Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].Team != player[g_Player]->Team) && (player[g_Player]->HB_Energy > 0))
			{
			TESTDist = 100;
			TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
			TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
			while(TESTDist > 1)
				{
				Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

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

					if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
						{
						if(Q_SEnergy->SEnergy[Count].TargetLock == 1) Q_SEnergy->SEnergy[Count].TargetLock = 2;
						player[g_Player]->HB_Energy -= (80*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3)) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));
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
				if((Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].Team != Q_Forge->Forge[SCRAM].Team) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
					{
					TESTDist = 100;
					TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
					TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
					while(TESTDist > 1)
						{
						Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

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

							if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
								{
								if(Q_SEnergy->SEnergy[Count].TargetLock == 1) Q_SEnergy->SEnergy[Count].TargetLock = 2;
								Q_Forge->Forge[SCRAM].HB_Energy -= (80*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3)) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));
								}
							}
						}
					}
				}
			SCRAM++;
			}

#if 1
		if(Qpo->Collision_RayTest_Avatar(
			&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Mins,
			&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Maxs,
			&Q_SEnergy->SEnergy[Count].LOldPos,
			&Q_SEnergy->SEnergy[Count].LightPos,
			// GE_CONTENTS_CANNOT_OCCUPY
			/* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
			0xffffffff, NULL, NULL,
			&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision, Q_SEnergy->SEnergy[Count].AvID))
				{
				if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_HitAvatar)
					{
					/*if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AV.Avatar
					&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[0].Avatar		//**********
					&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[1].Avatar		//Here Set collide flags on actor creation and shorten the 'if'
					&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[2].Avatar		//******
					&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[3].Avatar
					&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar != Q_SEnergy->SEnergy[Count].AvatarFlag[4].Avatar
					&& Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag != 251)*/
						if(1){
					
	#endif

	#if 0
					if(!(((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x) > (Q_SEnergy->SEnergy[Count].LightPos.x + 10)) || ((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x) < (Q_SEnergy->SEnergy[Count].LightPos.x - 10))) &&
					!(((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y) > (Q_SEnergy->SEnergy[Count].LightPos.y + 10)) || ((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y) < (Q_SEnergy->SEnergy[Count].LightPos.y - 10))) &&
					!(((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z) > (Q_SEnergy->SEnergy[Count].LightPos.z + 10)) || ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z) < (Q_SEnergy->SEnergy[Count].LightPos.z - 10))))
						{	//#####- Hit Avatar -#####
						Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag = 250;
						Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact = playerAV[g_Player]->Xform.Translation;
						Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y += 45;
	#endif

	#if 1
						if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID == -1 && Q_SEnergy->SEnergy[Count].AvID != 250)
							{
	#endif
							if(Q_SEnergy->SEnergy[Count].AntiMultHits[250] < 1)
								{
								Q_SEnergy->SEnergy[Count].AntiMultHits[250]++;
					
								//##### Check Target Lock
								if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
									{ if(Q_SEnergy->SEnergy[Count].TargetID == 250) Q_SEnergy->SEnergy[Count].TargetLock = 2; }

								//#### Energy Attack Power
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Power / 5000) * 10) + 1;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.AggPower / 100);

								//######## Aggressive to defensive power check
								if(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3)
									{
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.AggPower * (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER);

									if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = 0;

									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PBTIMER = TIME;
									}

								//### Check to Determine if Avatar is Blocking
								if((!(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3) || (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK <= 0)) && (player[g_Player]->HB_Dead == 0))
									{
									//### Check if Avatar Is Deflecting
									if(player[g_Player]->DeflectLethal == 1)
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
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
										Q_SEnergy->SEnergy[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
										Q_SEnergy->SEnergy[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);
#endif

#if 0
										Q_SEnergy->SEnergy[Count].TargetLock = 2;
										Q_SEnergy->SEnergy[Count].Init = 3;
#endif

										Q_SEnergy->SEnergy[Count].TargetID = Q_SEnergy->SEnergy[Count].AvID;
										Q_SEnergy->SEnergy[Count].AvID = 250;
										Q_SEnergy->SEnergy[Count].TargetLock = 1;
										Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].TraVec);
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

												Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
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
												Q_SEnergy->SEnergy[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
												Q_SEnergy->SEnergy[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);
	#endif

	#if 0
												Q_SEnergy->SEnergy[Count].TargetLock = 2;
												Q_SEnergy->SEnergy[Count].Init = 3;
	#endif

												Q_SEnergy->SEnergy[Count].TargetID = Q_SEnergy->SEnergy[Count].AvID;
												Q_SEnergy->SEnergy[Count].AvID = 250;
												Q_SEnergy->SEnergy[Count].TargetLock = 1;
												Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].TraVec);
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
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

												//# Deduct Health
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_LastAvatarHitID = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag;
											/*if(player[g_Player]->HB_HReduceON == 0)*/ player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

													//Rework Needed here very messy , plus add a random factor
											player[g_Player]->HB_Health -= 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
											if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;

											//#### Experience Storage
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[250] += 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);


											if(player[g_Player]->HB_Health <= 0)
												{
												player[g_Player]->HB_Health = 0;

												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 18;

												player[g_Player]->HB_Dead = 1;

												jet = 0;
												while(jet < 5)
													{
													Q.AISpawnNNbot(Q_SEnergy->SEnergy[Count].AvID, playerAV[g_Player]->Xform.Translation);

													jet++;
													}

												//### Add Experience to attacking AVATAR
												if((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
													{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_SEnergy->SEnergy[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }

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

												ag_ApplyUpdate(g_Sp);

												//### Write out CHARDATA
												//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

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

											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * 20;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											//###Hit Reactions
											player[g_Player]->HitReactScale = 0.025;	//0.05
											
											player[g_Player]->MoveReactVec = Q_SEnergy->SEnergy[Count].TraVec;
											player[g_Player]->MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_Energy += 10;
											if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_Energy > Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_MaxEnergy) Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_Energy = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_MaxEnergy;
									
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
												player[g_Player]->MoveReactSpeed = 4 * RENZOU_SCALE_IMP;

												//### Block Hit Flash

												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
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
									player[g_Player]->MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

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
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
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
									Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].TraVec);
									TraVecStore = Q_SEnergy->SEnergy[Count].TraVec;
									Qpo->Vec3d_Normalize(&TraVecStore);
									
									Addition.x = ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.y = ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.z = ((((float)rand() / 32767) * 1) -0.5) * 0.4;

									Qpo->Vec3d_Normalize(&Addition);
									Qpo->Vec3d_Subtract(&Addition, &TraVecStore, &Addition);
									Qpo->Vec3d_Scale(&Addition, 5, &Addition);

									Qpo->Vec3d_Add(&Q_SEnergy->SEnergy[Count].TraVec, &Addition, &Q_SEnergy->SEnergy[Count].TraVec);
									}//END Block Test

								}//END Anti Multiple hits

							}//END Playact Hit

							//#####- NON PLAYER AVATAR -#####


						//if(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID != -1)
						else
							{

						/*SCRAM=0;
						while(SCRAM < _->NomAI)
							{
							if(Q_Forge->Forge[SCRAM].LIVE == 1 && SCRAM != Q_SEnergy->SEnergy[Count].AvID)
								{
								if(!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Mins.x) > (Q_SEnergy->SEnergy[Count].LightPos.x + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Maxs.x) < (Q_SEnergy->SEnergy[Count].LightPos.x - 10))) &&
								!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Mins.y) > (Q_SEnergy->SEnergy[Count].LightPos.y + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Maxs.y) < (Q_SEnergy->SEnergy[Count].LightPos.y - 10))) &&
								!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Mins.z) > (Q_SEnergy->SEnergy[Count].LightPos.z + 10)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Maxs.z) < (Q_SEnergy->SEnergy[Count].LightPos.z - 10))))
									{
									Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Avatar.IDflag = SCRAM;
									Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact = Q_Forge->Forge[SCRAM].AV.Xform.Translation;
									Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y += 45;*/

							//### Hit New Avatar
							if(Q_SEnergy->SEnergy[Count].AntiMultHits[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] < 1 && (Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID != Q_SEnergy->SEnergy[Count].AvID))
								{
								Q_SEnergy->SEnergy[Count].AntiMultHits[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID]++;

								if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
									{ if(Q_SEnergy->SEnergy[Count].TargetID == Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID) Q_SEnergy->SEnergy[Count].TargetLock = 2; }



								//#### Energy Attack Power
								while(Q_SEnergy->SEnergy[Count].AvID > _->NomAI)
									{
									Q_SEnergy->SEnergy[Count].AvID = rand() % _->NomAI;
									}

								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Power / 5000) * 10) + 1;
								Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.AggPower / 100);

								//######## Aggressive to defensive power check
								if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHeight == 3)
									{
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.AggPower * (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.BodySKILL.ATTACKPOWER);

									if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK = 0;

									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.PBTIMER = TIME;
									}


								//### Check to Determine if Avatar is Blocking
								if((!(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHeight == 3) || (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK <= 0)) && (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Dead == 0))
									{
									//### Check if Avatar Is Deflecting
									if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].DeflectLethal == 1)
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
										Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
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
										Q_SEnergy->SEnergy[Count].TraVec.x = ((((float)rand() / 32767)-0.5)*2);
										Q_SEnergy->SEnergy[Count].TraVec.z = ((((float)rand() / 32767)-0.5)*2);
#endif

#if 0
										Q_SEnergy->SEnergy[Count].TargetLock = 2;
										Q_SEnergy->SEnergy[Count].Init = 3;
#endif

										Q_SEnergy->SEnergy[Count].TargetID = Q_SEnergy->SEnergy[Count].AvID;
										Q_SEnergy->SEnergy[Count].TargetLock = 1;
										Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].TraVec);
										}//END Deflect
									else
										{
										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);
										Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

											//# Deduct Health
										if(Q_SEnergy->SEnergy[Count].AvID < _->NomAI)
											{
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_LastAvatarHitID = Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID;
											}
										/*if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_HReduceON == 0)*/ Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceOld = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health;

												//Rework Needed here very messy , plus add a random factor
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health -= 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
										if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health = 0;

										//### Experience Storage
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] += 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Constitution / 400)) + 0.75);


										if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health <= 0)
											{
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Health = 0;

											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 17;

											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_Dead = 1;

											jet = 0;
											while(jet < 5)
												{
												Q.AISpawnNNbot(Q_SEnergy->SEnergy[Count].AvID, Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].AV.Xform.Translation);

												jet++;
												}

											//### Add XP to avatar
											if((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10)) > 0)
												{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_SEnergy->SEnergy[Count].AvID].CDATID].UnusedXP += Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10); }

											//##### Find KO Owner
											UniversalDMGSTR = 0;
											
											if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

											jet = 0;
											while(jet < _->NomAI)
												{
												if(Q_Forge->Forge[jet].LIVE == 1)
													{
													if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
													}
												jet++;
												}

											if(DeliverKOID == 250)
												{
												//### Create Item for attacking Avatar
												Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].DecFinger = ((float)rand() / 32767) * 100;

												if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].DecFinger <= 50 || 1)
													{
													player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level);
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
													if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10)) > 0)
														{
														//### Add Experience to attacking AVATAR
														player[g_Player]->BFO.CharDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10);

														g_Sp += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level / 10);

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
																Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level);

																Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																}
															else Q.CreateAvatarItem(Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.Level);
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

										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_HReduceON = 1;
										
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceHInc = 10;
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceHeight = 573;
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.red = 255;
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.green = 0;
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.blue = 0;
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HB_ReduceRectColor.alpha = 255;

										if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Avatar != 0)
											{
											Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[2].Xform.Translation);
											Qpo->Vec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[3].Xform.Translation);
											Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Avatar, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[1].Xform);
											Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[2].Avatar, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[2].Xform);
											Qpo->Avatar_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[3].Avatar, &Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Shadows[3].Xform);
											}

										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * 20;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

										//###Hit Reactions
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HitReactScale = 0.025;	//0.05
										
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactVec = Q_SEnergy->SEnergy[Count].TraVec;
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_Energy += 10;
										if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_Energy > Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_MaxEnergy) Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_Energy = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].HB_MaxEnergy;
								
										//## Reset Hit Wall
										Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HitWall = 0;

										//## Hit Reaction Motions
										
										if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Aposestate != 30)	//Standard Hit Reactions
											{
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Aposestate = 30;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].attackon = 1;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].attposecnt = 0;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].astackcnt = 0;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].astackrun = 0;
											}
										else
											{
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].attposecnt = 2.08;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].attackon = 1;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].astackcnt = 0;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].astackrun = 0;
											}

										//Increment number of MeleeHits
										_->NomMelHit += 1;

										if((Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK <= 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHeight == 3))
											{
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower / 100)) + 1);

											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactSpeed = 4 * RENZOU_SCALE_IMP;

											//### Block Hit Flash

											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																				//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
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
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower / 100)) + 1);

									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].Blocking = 1;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHit = 1;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHitFLAG = 1;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].attposecnt = 0;
									Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].BlockHitID = _->NomMelHit;

									//### Block Hit Flash

									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].Impact.acSet(Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_X, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Y, Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.Impact.m_Z);	//Point of impact in world space
									Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvatarFlag[0].Collision.m_AvatarID].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;

										//Increment number of MeleeHits
									_->NomMelHit += 1;

									QpoVec3d Addition,TraVecStore;
									Qpo->Vec3d_Inverse(&Q_SEnergy->SEnergy[Count].TraVec);
									TraVecStore = Q_SEnergy->SEnergy[Count].TraVec;
									Qpo->Vec3d_Normalize(&TraVecStore);
									
									Addition.x = ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.y = ((((float)rand() / 32767) * 1) -0.5) * 0.4;
									Addition.z = ((((float)rand() / 32767) * 1) -0.5) * 0.4;

									Qpo->Vec3d_Normalize(&Addition);
									Qpo->Vec3d_Subtract(&Addition, &TraVecStore, &Addition);
									Qpo->Vec3d_Scale(&Addition, 5, &Addition);

									Qpo->Vec3d_Add(&Q_SEnergy->SEnergy[Count].TraVec, &Addition, &Q_SEnergy->SEnergy[Count].TraVec);
									}//END Block Test

								}//END Anti Mult Hits

							}//END AI hits			***

						}//END quick actor check	***

					}//END Collision NULL
				else //##### Hit Geometry
					{
					Q_SEnergy->SEnergy[Count].Live = 0;
					if(Q_SEnergy->SEnergy[Count].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[Count].Light);
					if(Q_SEnergy->SEnergy[Count].Sound != NULL) Qpo->Sound_Stop(Q_SEnergy->SEnergy[Count].Sound);

					helly = 0;
					while(helly < Q_SEnergy->SEnergy[Count].NomActors)
						{
						Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
						helly++;
						}

					//### Energy Array Reorder
					int K = Count;
					while(K < _->NomSEnergy - 1)
						{
						Q_SEnergy->SEnergy[K] = Q_SEnergy->SEnergy[K+1];
						K++;
						}

					_->NomSEnergy--;
					}

				}

			}//END Collision

		}//END Else Origin
		
	Q_SEnergy->SEnergy[Count].LightPos = Q_SEnergy->SEnergy[Count].LOldPos;
	}


void Q_EFFCon::SEnergy_Renzou_ClientFrame(int Count)
	{
	//########  - CLIENT PHANTOM SMALL ENERGY ATTACKS -  ########//

	if(Q_SEnergy->SEnergy[Count].Init == 0)
		{
		Q_SEnergy->SEnergy[Count].Init = 1;

		Q_SEnergy->SEnergy[Count].NomActors = 5;
		Q_SEnergy->SEnergy[Count].Scale = 0.01;
		Q_SEnergy->SEnergy[Count].ScaleMode = 0;
		Q_SEnergy->SEnergy[Count].Alpha = 0;
		Q_SEnergy->SEnergy[Count].AlphaInc = 50;
		Q_SEnergy->SEnergy[Count].AlphaScale[0] = 1;
		Q_SEnergy->SEnergy[Count].AlphaScale[1] = 0.9;
		Q_SEnergy->SEnergy[Count].AlphaScale[2] = 0.8;
		Q_SEnergy->SEnergy[Count].AlphaScale[3] = 0.6;
		Q_SEnergy->SEnergy[Count].AlphaScale[4] = 0.3;
		Q_SEnergy->SEnergy[Count].Speed = 0;
		Q_SEnergy->SEnergy[Count].SpeedScale[0] = 0;
		Q_SEnergy->SEnergy[Count].SpeedScale[1] = 0.3;
		Q_SEnergy->SEnergy[Count].SpeedScale[2] = 0.6;
		Q_SEnergy->SEnergy[Count].SpeedScale[3] = 0.9;
		Q_SEnergy->SEnergy[Count].SpeedScale[4] = 1.2;
		Q_SEnergy->SEnergy[Count].LightColor.red = 255.0f;
		Q_SEnergy->SEnergy[Count].LightColor.green = 255.0f;
		Q_SEnergy->SEnergy[Count].LightColor.blue = 200.0f;
		Q_SEnergy->SEnergy[Count].LightColor.alpha = 255.0f;
		Q_SEnergy->SEnergy[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);

		jet=0;
		while(jet < Q_SEnergy->SEnergy[Count].NomActors)
			{
			Qpo->Mesh_SetScale(&Q_SEnergy->SEnergy[Count].AvatarFlag[jet], 0.01f,0.01f,0.01f);
			//Qpo->Avatar_SetLighting(&Q_SEnergy->SEnergy[Count].AvatarFlag[jet].Avatar, false, &goup, 0, 0, 0, 255, 255, 255, false, 0, NULL, false);
			Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].AvatarFlag[jet].Xform.Translation);
			jet++;
			}

		//RESET MULTIPLE HIT COUNTER
		Q_SEnergy->SEnergy[Count].AntiMultHits[250] = 0;
		jet=0;
		while(jet < _->NomAI)
			{
			Q_SEnergy->SEnergy[jet].AntiMultHits[jet] = 0;
			jet++;
			}

		/*//QpoSound3D_GetConfig(World,
			&player[g_Player]->ViewXForm,
			&Q_SEnergy->SEnergy[Count].LightPos,
			600.0f,
			2.0f,
			&Volume,
			&Pan,
			&Frequency);*/
		
		Q_SEnergy->SEnergy[Count].Sound = Qpo->Sound_Play(Medias->S_Renzou, _->Volume, _->Pan, _->S_TimeScale, true, &Q_SEnergy->SEnergy[Count].LightPos);
		}

	helly = 0;
	while(helly < Q_SEnergy->SEnergy[Count].NomActors)
		{
		Qpo->Transform_New(&Q_SEnergy->SEnergy[Count].Matrix2);

		Qpo->Transform_RotateZ(&Q_SEnergy->SEnergy[Count].Matrix2, Q_SEnergy->SEnergy[Count].AngleZ);
		Qpo->Transform_RotateX(&Q_SEnergy->SEnergy[Count].Matrix2, Q_SEnergy->SEnergy[Count].AngleX);
		Qpo->Transform_RotateY(&Q_SEnergy->SEnergy[Count].Matrix2, Q_SEnergy->SEnergy[Count].AngleY);

		Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform = Q_SEnergy->SEnergy[Count].Matrix2;

		helly++;
		}

	Qpo->Transform_GetIn(&Q_SEnergy->SEnergy[Count].AvatarFlag[0].Xform, &Q_SEnergy->SEnergy[Count].TraVec);


	if(Q_SEnergy->SEnergy[Count].TargetLock == 1)
		{
		//#### Show Target Locks
		if(Q_SEnergy->SEnergy[Count].DisplayAlpha - 15 > 120) Q_SEnergy->SEnergy[Count].DisplayAlpha -= 15;
		else Q_SEnergy->SEnergy[Count].DisplayAlpha = 120;

		if(Q_SEnergy->SEnergy[Count].DisplayColor - 25 > 0) Q_SEnergy->SEnergy[Count].DisplayColor -= 25;
		else Q_SEnergy->SEnergy[Count].DisplayColor = 0;

		if(Q_SEnergy->SEnergy[Count].DisplayScale + 0.05 < 0.75) Q_SEnergy->SEnergy[Count].DisplayScale += 0.06;
		else Q_SEnergy->SEnergy[Count].DisplayScale = 0.75;
		
		if(Q_SEnergy->SEnergy[Count].AvID == 250)
			{
			player[g_Player]->LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
			player[g_Player]->LaserLV.r = 255;
			player[g_Player]->LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
			player[g_Player]->LaserLV.b = 0;
			player[g_Player]->LaserLV.x = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.x;
			player[g_Player]->LaserLV.y = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.y + 65;
			player[g_Player]->LaserLV.z = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.z;

			Qpo->Poly_AddOnce(&player[g_Player]->LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
			}
		else
			{
			if(Q_SEnergy->SEnergy[Count].TargetID == 250)
				{
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
				}
			else
				{
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.a = Q_SEnergy->SEnergy[Count].DisplayAlpha;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.r = 255;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.g = Q_SEnergy->SEnergy[Count].DisplayColor;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.b = 0;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.x = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.x;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.y = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.y + 65;
				Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV.z = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation.z;

				Qpo->Poly_AddOnce(&Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_SEnergy->SEnergy[Count].DisplayScale);
				}
			}

		if(Q_SEnergy->SEnergy[Count].TargetID == 250)
			{
			Q_SEnergy->SEnergy[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
			Q_SEnergy->SEnergy[Count].TargetVec.y += 65;
			}
		else
			{
			Q_SEnergy->SEnergy[Count].TargetVec = Q_Forge->Forge[Q_SEnergy->SEnergy[Count].TargetID].AV.Xform.Translation;
			Q_SEnergy->SEnergy[Count].TargetVec.y += 65;
			}
		}

		//Set Light Power and Move the Light
	Q_SEnergy->SEnergy[Count].LOldPos = Q_SEnergy->SEnergy[Count].LightPos;
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[Count].LightPos, Q_SEnergy->SEnergy[Count].Speed*_->TimeScale, &Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].LightPos);

	Qpo->Light_SetAttr(Q_SEnergy->SEnergy[Count].Light, &Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].LightColor, Q_SEnergy->SEnergy[Count].Scale * 150, false);

	helly = 0;
	while(helly < Q_SEnergy->SEnergy[Count].NomActors)
		{
		Qpo->Mesh_SetScale(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly], Q_SEnergy->SEnergy[Count].Scale, Q_SEnergy->SEnergy[Count].Scale, Q_SEnergy->SEnergy[Count].Scale);
		Qpo->Mesh_SetAlpha(&Q_SEnergy->SEnergy[Count].AvatarFlag[helly], Q_SEnergy->SEnergy[Count].Alpha * Q_SEnergy->SEnergy[Count].AlphaScale[helly]);

		Qpo->Vec3d_Copy(&Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
		Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[Count].LightPos, -(Q_SEnergy->SEnergy[Count].Speed * Q_SEnergy->SEnergy[Count].SpeedScale[helly]), &Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].AvatarFlag[helly].Xform.Translation);
		helly++;
		}

	/*//QpoSound3D_GetConfig(World,
				&player[g_Player]->ViewXForm,
				&Q_SEnergy->SEnergy[Count].LightPos,
				600.0f,
				2.0f,
				&Volume,
				&Pan,
				&Frequency);*/

	Q_SEnergy->SEnergy[Count].LOldPos = Q_SEnergy->SEnergy[Count].LightPos;
	Qpo->Vec3d_AddScaled(&Q_SEnergy->SEnergy[Count].LightPos, Q_SEnergy->SEnergy[Count].Speed*_->TimeScale, &Q_SEnergy->SEnergy[Count].TraVec, &Q_SEnergy->SEnergy[Count].LightPos);

	Qpo->Sound_Modify(Q_SEnergy->SEnergy[Count].Sound, _->Volume, _->Pan, _->Frequency, &Q_SEnergy->SEnergy[Count].LightPos, &Q_SEnergy->SEnergy[Count].TraVec);

	if(Q_SEnergy->SEnergy[Count].AvID == 250)	//Player Fired Projectile
		{
		//##### AVATAR SHIELD COLLIDE TEST
		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if(Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0)
					{
					if(player[g_Player]->Team != Q_Forge->Forge[SCRAM].Team)
						{
						TESTDist = 100;
						TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
						TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
						while(TESTDist > 1)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
								{
								if(Q_Forge->Forge[SCRAM].HB_Energy > 0)
									{
									TESTPosS = TESTPosE;
									TESTDist = 0;

									jet=0;
									while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
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
									}
								}
							}
						}
					}
				}
			SCRAM++;
			}
		}
	else
		{
		//PLAYER SHIELD CHECK
		if(player[g_Player]->Cleric.ShieldAlpha > 0)
			{
			if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].Team != player[g_Player]->Team)
				{
				TESTDist = 100;
				TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
				TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
				while(TESTDist > 1)
					{
					Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

					TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

					if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
						{
						if(player[g_Player]->HB_Energy > 0)
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
							}
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
				if(Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0)
					{
					if(Q_Forge->Forge[Q_SEnergy->SEnergy[Count].AvID].Team != Q_Forge->Forge[SCRAM].Team)
						{
						TESTDist = 100;
						TESTPosS = Q_SEnergy->SEnergy[Count].LOldPos;
						TESTPosE = Q_SEnergy->SEnergy[Count].LightPos;
						while(TESTDist > 1)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_SEnergy->SEnergy[Count].TraVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
								{
								if(Q_Forge->Forge[SCRAM].HB_Energy > 0)
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
									}
								}
							}
						}
					}
				}
			SCRAM++;
			}
		}

	Q_SEnergy->SEnergy[Count].LightPos = Q_SEnergy->SEnergy[Count].LOldPos;
	}

};

#if 0
			if(geWorld_Collision(World,
						&Q_SEnergy->SEnergy[aero].ActorFlag[0].Mins,
						&Q_SEnergy->SEnergy[aero].ActorFlag[0].Maxs,
						&Q_SEnergy->SEnergy[aero].LOldPos,
						&Q_SEnergy->SEnergy[aero].LightPos,
						GE_CONTENTS_CANNOT_OCCUPY,
						GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
						0xffffffff, NULL, NULL,
						&Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision))
						{
						if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != NULL)
							{
							if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != playact.Actor
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[0].Actor		//**********
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[1].Actor		//Here Set collide flags on actor creation and shorten the 'if'
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[2].Actor		//******
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[3].Actor
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[4].Actor
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag != 251)
								{	//#####- Hit Avatar -#####
								if(Q_SEnergy->SEnergy[aero].AntiMultHits[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] < 1)
									{
									Q_SEnergy->SEnergy[aero].AntiMultHits[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag]++;
							
										//##### Check Target Lock
									if(Q_SEnergy->SEnergy[aero].TargetLock == 1)
										{ if(Q_SEnergy->SEnergy[aero].TargetID == Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag) Q_SEnergy->SEnergy[aero].TargetLock = 2; }

									//#### Energy Attack Power
									player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.ATTACKPOWER = ((player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].AttackSKILL[28].Power / 5000) * 10) + 1;
									player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.ATTACKPOWER *= ((float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.AggPower / 100);

									//######## Aggressive to defensive power check
									if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHeight == 3)
										{
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK -= ((float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.AggPower * (float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.ATTACKPOWER);

										if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK = 0;

										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.PBTIMER = TIME;
										}

									//### Check to Determine if Avatar is Blocking
									if((!(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHeight == 3) || (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK <= 0)) && (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Dead == 0))
										{
										//### Check if Avatar Is Deflecting
										if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].DeflectLethal == 1)
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																				//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;						//Number index of the bone hit

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

											Q_SEnergy->SEnergy[aero].TraVec.X = ((((float)rand() / 32767)-0.5)*2);
											Q_SEnergy->SEnergy[aero].TraVec.Z = ((((float)rand() / 32767)-0.5)*2);

											Q_SEnergy->SEnergy[aero].TargetLock = 2;
											Q_SEnergy->SEnergy[aero].Init = 3;
											}//END Deflect
										else
											{
											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
											Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[aero].ActorFlag[0].ActorXform;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

												//# Deduct Health
											player[g_Player]->HB_LastAvatarHitID = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag;
											/*if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_HReduceON == 0)*/ Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceOld = Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health;

													//Rework Needed here very messy , plus add a random factor
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health -= 70*((player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
											if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health = 0;

											//### Experience Storage
											player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] += 70*((player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Constitution / 400)) + 0.75);


											if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health <= 0)
												{
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health = 0;

												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 17;

												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Dead = 1;

												if((player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10)) > 0)
													{
													//### Add Experience to attacking AVATAR
													player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10);

													player[g_Player]->MSG_XPON = 1;
													player[g_Player]->MSG_XPInit = 0;
													player[g_Player]->MSG_XPScreenDIST = 0;
													player[g_Player]->MSG_XPScreenDistINC = 50;
													player[g_Player]->MSG_XPScreenDIR = 0;
													player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10);
													}

												//##### Find KO Owner
												UniversalDMGSTR = 0;
												
												if(player[g_Player]->AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

												jet = 0;
												while(jet < _->NomAI)
													{
													if(Q_Forge->Forge[jet].LIVE == 1)
														{
														if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
														}
													jet++;
													}

												if(DeliverKOID == 250)
													{
													//### Create Item for attacking Avatar
													player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

													if(player[g_Player]->DecFinger <= 50)
														{
														player[g_Player]->MSG_ItemREF = Q_CreatePlayerItem(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level);
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
														if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10)) > 0)
															{
															//### Add Experience to attacking AVATAR
															player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10);

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
																	Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q_CreateAvatarItem(player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level);

																	Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																	}
																else Q_CreateAvatarItem(player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level);
																}
															}
														}
													SCRAM++;
													}


												//####### DEACTIVATE ITEM ATTRIBUTES
												Q_DeactivateItems();

												//### Write out CHARDATA
												WriteNEWCharacterData(player[g_Player]->CDATA);

												//####### REACTIVATE ITEM ATTRIBUTES
												Q_ActivateItems();
												}



											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_HReduceON = 1;
											
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceHInc = 10;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceHeight = 573;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.r = 255;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.g = 0;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.b = 0;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.a = 255;

											if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].Actor != NULL)
												{
												geVec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].ActorXform.Translation);
												geVec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[2].ActorXform.Translation);
												geVec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[3].ActorXform.Translation);
												geActor_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].Actor, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].ActorXform);
												geActor_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[2].Actor, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[2].ActorXform);
												geActor_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[3].Actor, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[3].ActorXform);
												}

											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].AttackSKILL[28].Damage/3500)+0.3) * 20;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90

											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

											//###Hit Reactions
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitReactScale = 0.025;	//0.05
											
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactVec = Q_SEnergy->SEnergy[aero].TraVec;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

											player[g_Player]->HB_Energy += 10;
											if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = 200;
									
											//## Reset Hit Wall
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitWall = 0;

											//## Hit Reaction Motions
											
											if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Aposestate != 30)	//Standard Hit Reactions
												{
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Aposestate = 30;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attackon = 1;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attposecnt = 0;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackcnt = 0;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackrun = 0;
												}
											else
												{
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attposecnt = 2.08;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attackon = 1;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackcnt = 0;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackrun = 0;
												}

											//Increment number of MeleeHits
											_->NomMelHit += 1;

											if((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK <= 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHeight == 3))
												{
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower / 100)) + 1);

												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactSpeed = 4 * RENZOU_SCALE_IMP;

												//### Block Hit Flash

												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;

																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
												geActor_GetBoneTransform(playact.Actor, "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
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

											}//END Not Deflecting

										}//END Block Test
									else
										{
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower / 100)) + 1);

										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Blocking = 1;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHit = 1;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHitFLAG = 1;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attposecnt = 0;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHitID = _->NomMelHit;

										//### Block Hit Flash

										Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 2;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
																			//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
										Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
										geActor_GetBoneTransform(playact.Actor, "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
										Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
										Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
										Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

										//Expandro3D Struct
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
										Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;

											//Increment number of MeleeHits
										_->NomMelHit += 1;
										}//END Block Test

									}//END Anti Multiple Hits

								}//END quick Actor check

							}//END Actor Not Null
							
						if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor == NULL)	//##### Hit Geometry
							{
							Q_SEnergy->SEnergy[aero].Live = 0;
							if(Q_SEnergy->SEnergy[aero].Light != NULL) geWorld_RemoveLight(World, Q_SEnergy->SEnergy[aero].Light);
							if(Q_SEnergy->SEnergy[aero].Sound != NULL) geSound_StopSound(SoundSys, Q_SEnergy->SEnergy[aero].Sound);

							helly = 0;
							while(helly < Q_SEnergy->SEnergy[aero].NomActors)
								{
								geVec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[aero].ActorFlag[helly].ActorXform.Translation);
								geActor_ClearPose(Q_SEnergy->SEnergy[aero].ActorFlag[helly].Actor, &Q_SEnergy->SEnergy[aero].ActorFlag[helly].ActorXform);
								helly++;
								}

							//### Energy Array Reorder
							K = aero;
							while(K < _->NomSEnergy - 1)
								{
								Q_SEnergy->SEnergy[K] = Q_SEnergy->SEnergy[K+1];
								K++;
								}

							_->NomSEnergy--;
							}

						}//END Collision

					}//END ActorID
				else	//AI FIRED PROJECTILE
					{
					//PLAYER SHIELD CHECK
					if((player[g_Player]->Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].Team != player[g_Player]->Team) && (player[g_Player]->HB_Energy > 0))
						{
						TESTDist = 100;
						TESTPosS = Q_SEnergy->SEnergy[aero].LOldPos;
						TESTPosE = Q_SEnergy->SEnergy[aero].LightPos;
						while(TESTDist > 1)
							{
							geVec3d_MA(&TESTPosS, 1, &Q_SEnergy->SEnergy[aero].TraVec, &TESTPosS);

							TESTShieldDIST = geVec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.ActorXform.Translation);

							TESTDist = geVec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
								{
								jet=0;
								while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									TESTPosS = TESTPosE;
									TESTDist = 0;

									Q_PntSprite->PntSprite[_->NomPntSprite].Type = GE_TEXTURED_POINT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags =	GE_RENDER_DO_NOT_OCCLUDE_OTHERS;		//GE_RENDER_DEPTH_SORT_BF
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.X = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.Y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.Z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.X += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.Y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.Z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].ActorID = Q_PntSprite->PntSprite[helly].ActorID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}

								if(Q_SEnergy->SEnergy[aero].TargetLock == 1)
									{
									if(Q_SEnergy->SEnergy[aero].TargetLock == 1) Q_SEnergy->SEnergy[aero].TargetLock = 2;
									player[g_Player]->HB_Energy -= (80*((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3)) / (10 * (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].CLSClericSKILL[7].Duration/5000));
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
							if((Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].Team != Q_Forge->Forge[SCRAM].Team) && (Q_Forge->Forge[SCRAM].HB_Energy > 0))
								{
								TESTDist = 100;
								TESTPosS = Q_SEnergy->SEnergy[aero].LOldPos;
								TESTPosE = Q_SEnergy->SEnergy[aero].LightPos;
								while(TESTDist > 1)
									{
									geVec3d_MA(&TESTPosS, 1, &Q_SEnergy->SEnergy[aero].TraVec, &TESTPosS);

									TESTShieldDIST = geVec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.ActorXform.Translation);

									TESTDist = geVec3d_DistanceBetween(&TESTPosS, &TESTPosE);

									if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
										{
										jet=0;
										while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
											{
											TESTPosS = TESTPosE;
											TESTDist = 0;

											Q_PntSprite->PntSprite[_->NomPntSprite].Type = GE_TEXTURED_POINT;
											Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags =	GE_RENDER_DO_NOT_OCCLUDE_OTHERS;		//GE_RENDER_DEPTH_SORT_BF
											Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
											Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

											Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
											Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
											Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

											Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
											Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
											Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TESTPosS;

											Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.X = (((float)rand() / 32767)-0.5);
											Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.Y = (((float)rand() / 32767)-0.5);
											Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.Z = (((float)rand() / 32767)-0.5);

											Q_PntSprite->PntSprite[_->NomPntSprite].Pos.X += (((float)rand() / 32767)-0.5)*1;
											Q_PntSprite->PntSprite[_->NomPntSprite].Pos.Y += (((float)rand() / 32767)-0.5)*1;
											Q_PntSprite->PntSprite[_->NomPntSprite].Pos.Z += (((float)rand() / 32767)-0.5)*1;

											Q_PntSprite->PntSprite[_->NomPntSprite].ActorID = Q_PntSprite->PntSprite[helly].ActorID;

											Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

											_->NomPntSprite++;
											jet++;
											}

										if(Q_SEnergy->SEnergy[aero].TargetLock == 1)
											{
											if(Q_SEnergy->SEnergy[aero].TargetLock == 1) Q_SEnergy->SEnergy[aero].TargetLock = 2;
											Q_Forge->Forge[SCRAM].HB_Energy -= (80*((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3)) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));
											}
										}
									}
								}
							}
						SCRAM++;
						}


					if(geWorld_Collision(World,
						&Q_SEnergy->SEnergy[aero].ActorFlag[0].Mins,
						&Q_SEnergy->SEnergy[aero].ActorFlag[0].Maxs,
						&Q_SEnergy->SEnergy[aero].LOldPos,
						&Q_SEnergy->SEnergy[aero].LightPos,
						GE_CONTENTS_CANNOT_OCCUPY,
						GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
						0xffffffff, NULL, NULL,
						&Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision))
						{
						if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != NULL)
							{
							if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].Avatar.Actor
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[0].Actor		//**********
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[1].Actor		//Here Set collide flags on actor creation and shorten the 'if'
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[2].Actor		//******
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[3].Actor
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != Q_SEnergy->SEnergy[aero].ActorFlag[4].Actor
							&& Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag != 251)
								{	//#####- Hit Avatar -#####
								if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor == playact.Actor)
									{
									if(Q_SEnergy->SEnergy[aero].AntiMultHits[250] < 1)
										{
										Q_SEnergy->SEnergy[aero].AntiMultHits[250]++;
							
										//##### Check Target Lock
										if(Q_SEnergy->SEnergy[aero].TargetLock == 1)
											{ if(Q_SEnergy->SEnergy[aero].TargetID == 250) Q_SEnergy->SEnergy[aero].TargetLock = 2; }

										//#### Energy Attack Power
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Power / 5000) * 10) + 1;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.AggPower / 100);

										//######## Aggressive to defensive power check
										if(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3)
											{
											player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.AggPower * (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.ATTACKPOWER);

											if(player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK < 0) player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK = 0;

											player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.PBTIMER = TIME;
											}

										//### Check to Determine if Avatar is Blocking
										if((!(player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3) || (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK <= 0)) && (player[g_Player]->HB_Dead == 0))
											{
											//### Check if Avatar Is Deflecting
											if(player[g_Player]->DeflectLethal == 1)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[aero].ActorFlag[0].ActorXform;
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

												Q_SEnergy->SEnergy[aero].TraVec.X = ((((float)rand() / 32767)-0.5)*2);
												Q_SEnergy->SEnergy[aero].TraVec.Z = ((((float)rand() / 32767)-0.5)*2);

												Q_SEnergy->SEnergy[aero].TargetLock = 2;
												Q_SEnergy->SEnergy[aero].Init = 3;
												}//END DEFLECT
											else
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[aero].ActorFlag[0].ActorXform;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

													//# Deduct Health
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_LastAvatarHitID = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag;
												/*if(player[g_Player]->HB_HReduceON == 0)*/ player[g_Player]->HB_ReduceOld = player[g_Player]->HB_Health;

														//Rework Needed here very messy , plus add a random factor
												player[g_Player]->HB_Health -= 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
												if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;

												//#### Experience Storage
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[250] += 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);


												if(player[g_Player]->HB_Health <= 0)
													{
													player[g_Player]->HB_Health = 0;

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 18;

													player[g_Player]->HB_Dead = 1;

													//### Add Experience to attacking AVATAR
													if((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[250] * (10 * player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level / 1000)) > 0)
														{ player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->AVATARDATA[Q_SEnergy->SEnergy[aero].ActorID].CDATID].UnusedXP += Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[250] * (10 * player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level / 1000); }

													//##### Find KO Owner
													UniversalDMGSTR = 0;

													jet = 0;
													while(jet < _->NomAI)
														{
														if(Q_Forge->Forge[jet].LIVE == 1)
															{
															if(Q_Forge->Forge[jet].AvatarDMGSTORE[250] * (10 * player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level / 1000) > UniversalDMGSTR) DeliverKOID = jet;
															}
														jet++;
														}

													//##### Check All Active Avatars for XP and KO's
													SCRAM = 0;
													while(SCRAM < _->NomAI)
														{
														if(Q_Forge->Forge[SCRAM].LIVE == 1)
															{
															if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level / 1000)) > 0)
																{
																//### Add Experience to attacking AVATAR
																player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[250] * (10 * player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level / 1000);

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
																		Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q_CreateAvatarItem(player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level);

																		Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																		}
																	else Q_CreateAvatarItem(player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID,player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].Level);
																	}
																}
															}
														SCRAM++;
														}

													//####### DEACTIVATE ITEM ATTRIBUTES
													Q_DeactivateItems();

													//### Write out CHARDATA
													WriteNEWCharacterData(player[g_Player]->CDATA);

													//####### REACTIVATE ITEM ATTRIBUTES
													Q_ActivateItems();
													}


												player[g_Player]->HB_HReduceON = 1;
												
												player[g_Player]->HB_ReduceHInc = 10;
												player[g_Player]->HB_ReduceHeight = 573;
												player[g_Player]->HB_ReduceRectColor.r = 255;
												player[g_Player]->HB_ReduceRectColor.g = 0;
												player[g_Player]->HB_ReduceRectColor.b = 0;
												player[g_Player]->HB_ReduceRectColor.a = 255;

												if(&player[g_Player]->Shadows[1].Actor != NULL)
													{
													geVec3d_Copy(&_->Origon, &player[g_Player]->Shadows[1].ActorXform.Translation);
													geVec3d_Copy(&_->Origon, &player[g_Player]->Shadows[2].ActorXform.Translation);
													geVec3d_Copy(&_->Origon, &player[g_Player]->Shadows[3].ActorXform.Translation);
													geActor_ClearPose(&player[g_Player]->Shadows[1].Actor, &player[g_Player]->Shadows[1].ActorXform);
													geActor_ClearPose(&player[g_Player]->Shadows[2].Actor, &player[g_Player]->Shadows[2].ActorXform);
													geActor_ClearPose(&player[g_Player]->Shadows[3].Actor, &player[g_Player]->Shadows[3].ActorXform);
													}

												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * 20;

												//Expandro3D Struct
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

												//###Hit Reactions
												player[g_Player]->HitReactScale = 0.025;	//0.05
												
												player[g_Player]->MoveReactVec = Q_SEnergy->SEnergy[aero].TraVec;
												player[g_Player]->MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_Energy += 10;
												if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_Energy > Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_MaxEnergy) Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_Energy = Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_MaxEnergy;
										
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

												if((player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK <= 0) && (player[g_Player]->Block == 1 && player[g_Player]->BlockHeight == 3))
													{
													player[g_Player]->HitReactScale = 0.0035 * ((1 * (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.DefPower / 100)) + 1);

													player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													player[g_Player]->MoveReactSpeed = 4 * RENZOU_SCALE_IMP;

													//### Block Hit Flash

													Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																						//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
													Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
													geActor_GetBoneTransform(playact.Actor, "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
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

											}//END Block
										else
											{
											player[g_Player]->HitReactScale = 0.0035 * ((1 * (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.DefPower / 100)) + 1);

											player[g_Player]->MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											player[g_Player]->MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

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
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
											geActor_GetBoneTransform(playact.Actor, "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.POWERBANK / ((((float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->CurrCHAR].BodySKILL.Dexterity) * 2) + 100)) * 255;

												//Increment number of MeleeHits
											_->NomMelHit += 1;
											}//END Block Test

										}//END Anti Multiple hits

									}//END Playact Hit

									//#####- NON PLAYER AVATAR -#####
								if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor != playact.Actor)
									{

									//### Hit New Avatar
									if(Q_SEnergy->SEnergy[aero].AntiMultHits[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] < 1)
										{
										Q_SEnergy->SEnergy[aero].AntiMultHits[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag]++;

										if(Q_SEnergy->SEnergy[aero].TargetLock == 1)
											{ if(Q_SEnergy->SEnergy[aero].TargetID == Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag) Q_SEnergy->SEnergy[aero].TargetLock = 2; }

										//#### Energy Attack Power
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.ATTACKPOWER = ((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Power / 5000) * 10) + 1;
										Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.ATTACKPOWER *= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.AggPower / 100);

										//######## Aggressive to defensive power check
										if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHeight == 3)
											{
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK -= ((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.AggPower * (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.BodySKILL.ATTACKPOWER);

											if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK = 0;

											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.PBTIMER = TIME;
											}


										//### Check to Determine if Avatar is Blocking
										if((!(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHeight == 3) || (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK <= 0)) && (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Dead == 0))
											{
											//### Check if Avatar Is Deflecting
											if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].DeflectLethal == 1)
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = Q_SEnergy->SEnergy[Count].AvID;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																					//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[aero].ActorFlag[0].ActorXform;
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

												Q_SEnergy->SEnergy[aero].TraVec.X = ((((float)rand() / 32767)-0.5)*2);
												Q_SEnergy->SEnergy[aero].TraVec.Z = ((((float)rand() / 32767)-0.5)*2);

												Q_SEnergy->SEnergy[aero].TargetLock = 2;
												Q_SEnergy->SEnergy[aero].Init = 3;
												}//END Deflect
											else
												{
												Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
												Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 11;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 7;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;
												Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_SEnergy->SEnergy[aero].ActorFlag[0].ActorXform;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
												Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;

													//# Deduct Health
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_LastAvatarHitID = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag;
												/*if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_HReduceON == 0)*/ Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceOld = Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health;

														//Rework Needed here very messy , plus add a random factor
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health -= 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
												if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health < 0) Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health = 0;

												//### Experience Storage
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] += 70*((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * ((1 - (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Constitution / 400)) + 0.75);


												if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health <= 0)
													{
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Health = 0;

													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 17;

													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_Dead = 1;

													//### Add XP to avatar
													if((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10)) > 0)
														{ player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->AVATARDATA[Q_SEnergy->SEnergy[aero].ActorID].CDATID].UnusedXP += Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10); }

													//##### Find KO Owner
													UniversalDMGSTR = 0;
													
													if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

													jet = 0;
													while(jet < _->NomAI)
														{
														if(Q_Forge->Forge[jet].LIVE == 1)
															{
															if(Q_Forge->Forge[jet].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
															}
														jet++;
														}

													if(DeliverKOID == 250)
														{
														//### Create Item for attacking Avatar
														Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].DecFinger = ((float)rand() / 32767) * 100;

														if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].DecFinger <= 50 || 1)
															{
															player[g_Player]->MSG_ItemREF = Q_CreatePlayerItem(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level);
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
															if((Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10)) > 0)
																{
																//### Add Experience to attacking AVATAR
																player[g_Player]->CDATA->CharDATA[player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[SCRAM].AvatarDMGSTORE[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag] * (10 * Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level / 10);

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
																		Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].NewITEMREF = Q_CreateAvatarItem(player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level);

																		Q_Netplayer->Netplayer[Q_Forge->Forge[SCRAM].NetPID].UpdateCHAR = 2;
																		}
																	else Q_CreateAvatarItem(player[g_Player]->CDATA->AVATARDATA[Q_Forge->Forge[SCRAM].CharDATA.CDataID,Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.Level);
																	}
																}
															}
														SCRAM++;
														}

													//####### DEACTIVATE ITEM ATTRIBUTES
													Q_DeactivateItems();

													//### Write out CHARDATA
													WriteNEWCharacterData(player[g_Player]->CDATA);

													//####### REACTIVATE ITEM ATTRIBUTES
													Q_ActivateItems();
													}

												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_HReduceON = 1;
												
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceHInc = 10;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceHeight = 573;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.r = 255;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.g = 0;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.b = 0;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HB_ReduceRectColor.a = 255;

												if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].Actor != NULL)
													{
													geVec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].ActorXform.Translation);
													geVec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[2].ActorXform.Translation);
													geVec3d_Copy(&_->Origon, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[3].ActorXform.Translation);
													geActor_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].Actor, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[1].ActorXform);
													geActor_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[2].Actor, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[2].ActorXform);
													geActor_ClearPose(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[3].Actor, &Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Shadows[3].ActorXform);
													}

												Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = ((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3) * 20;

												//Expandro3D Struct
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 350 * ((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].CharDATA.AttackSKILL[28].Damage/3500)+0.3);	//150				//Max Radius
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 120;	//90
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;
												Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (100*Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent)+155;

												//###Hit Reactions
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitReactScale = 0.025;	//0.05
												
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactVec = Q_SEnergy->SEnergy[aero].TraVec;
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_Energy += 10;
												if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_Energy > Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_MaxEnergy) Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_Energy = Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorID].HB_MaxEnergy;
										
												//## Reset Hit Wall
												Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitWall = 0;

												//## Hit Reaction Motions
												
												if(Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Aposestate != 30)	//Standard Hit Reactions
													{
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Aposestate = 30;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attackon = 1;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attposecnt = 0;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackcnt = 0;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackrun = 0;
													}
												else
													{
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attposecnt = 2.08;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attackon = 1;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackcnt = 0;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].astackrun = 0;
													}

												//Increment number of MeleeHits
												_->NomMelHit += 1;

												if((Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK <= 0) && (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Block == 1 && Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHeight == 3))
													{
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower / 100)) + 1);

													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
													Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactSpeed = 4 * RENZOU_SCALE_IMP;

													//### Block Hit Flash

													Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
													Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																						//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
													Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
													geActor_GetBoneTransform(playact.Actor, "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
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
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].HitReactScale = 0.0035 * ((1 * (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower / 100)) + 1);

											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactVec = Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].MoveReactSpeed = 6 * RENZOU_SCALE_IMP;

											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].Blocking = 1;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHit = 1;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHitFLAG = 1;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].attposecnt = 0;
											Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].BlockHitID = _->NomMelHit;

											//### Block Hit Flash

											Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 20;
																				//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
											Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Impact;	//Point of impact in world space
											geActor_GetBoneTransform(playact.Actor, "BIP01 HEAD", &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
											Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = 0;
											Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
											Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;

											//Expandro3D Struct
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 80;				//Max Radius
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 100;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;
											Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = (Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.POWERBANK / ((((float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor->IDflag].CharDATA.BodySKILL.Dexterity) * 2) + 100)) * 255;

												//Increment number of MeleeHits
											_->NomMelHit += 1;
											}//END Block Test

										}//END Anti Mult Hits

									}//END AI hits

								}//END quick actor check

							}//END Collision NULL

						if(Q_SEnergy->SEnergy[aero].ActorFlag[0].Collision.Actor == NULL)	//##### Hit Geometry
							{
							Q_SEnergy->SEnergy[aero].Live = 0;
							if(Q_SEnergy->SEnergy[aero].Light != NULL) geWorld_RemoveLight(World, Q_SEnergy->SEnergy[aero].Light);
							if(Q_SEnergy->SEnergy[aero].Sound != NULL) geSound_StopSound(SoundSys, Q_SEnergy->SEnergy[aero].Sound);

							helly = 0;
							while(helly < Q_SEnergy->SEnergy[aero].NomActors)
								{
								geVec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[aero].ActorFlag[helly].ActorXform.Translation);
								geActor_ClearPose(Q_SEnergy->SEnergy[aero].ActorFlag[helly].Actor, &Q_SEnergy->SEnergy[aero].ActorFlag[helly].ActorXform);
								helly++;
								}

							//### Energy Array Reorder
							K = aero;
							while(K < _->NomSEnergy - 1)
								{
								Q_SEnergy->SEnergy[K] = Q_SEnergy->SEnergy[K+1];
								K++;
								}

							_->NomSEnergy--;
							}

						}//END Collision

					}//END Else Origin
					
				Q_SEnergy->SEnergy[aero].LightPos = Q_SEnergy->SEnergy[aero].LOldPos;
				}
			aero++;
			}
		}
	}
#endif