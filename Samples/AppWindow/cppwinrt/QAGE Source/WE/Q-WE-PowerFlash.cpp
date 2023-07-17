/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Power Flash-

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
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::PowerFlash_ControlFrame(int Count)
	{
	Q_PowerFlash->PowerFlash[Count].Timer += 2;

	Q_PowerFlash->PowerFlash[Count].Scale = 300;

	if(Q_PowerFlash->PowerFlash[Count].Speed - (2 * _->TimeScale) > 5) Q_PowerFlash->PowerFlash[Count].Speed -= (2 * _->TimeScale);
	else if(Q_PowerFlash->PowerFlash[Count].Speed != 0) Q_PowerFlash->PowerFlash[Count].Speed = 5;

	Q_PowerFlash->PowerFlash[Count].TraVec.y -= Q_PowerFlash->PowerFlash[Count].Gravity*_->TimeScale;

	Q_PowerFlash->PowerFlash[Count].OldPos = Q_PowerFlash->PowerFlash[Count].Pos;
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].Pos, Q_PowerFlash->PowerFlash[Count].Speed*_->TimeScale, &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].Pos);

	if(Qpo->Collision_RayTest(
		 NULL,
		 NULL,
		 &Q_PowerFlash->PowerFlash[Count].OldPos,
		 &Q_PowerFlash->PowerFlash[Count].Pos,
		 // GE_CONTENTS_CANNOT_OCCUPY
		 //GE_COLLIDE_MODELS /*| GE_COLLIDE_ACTORS*/,
		 0xffffffff, NULL, NULL,
		 &Q_PowerFlash->PowerFlash[Count].Collision))
		{
		Q_PowerFlash->PowerFlash[Count].Pos = Q_PowerFlash->PowerFlash[Count].OldPos;

		Q_PowerFlash->PowerFlash[Count].Speed = 0;

		/*if(Q_PowerFlash->PowerFlash[Count].Bounce < 2)	//2
			{
			Q_PowerFlash->PowerFlash[Count].TraVec = Q.PHY_BounceVector(Q_PowerFlash->PowerFlash[Count].TraVec, Q_PowerFlash->PowerFlash[Count].Collision.Plane.Normal);

			//BETTER
			Q_PowerFlash->PowerFlash[Count].Gravity = Q_PowerFlash->PowerFlash[Count].Gravity * 2;
			Q_PowerFlash->PowerFlash[Count].Speed = Q_PowerFlash->PowerFlash[Count].Speed / 1.5;
			Q_PowerFlash->PowerFlash[Count].Bounce++;
			}
		else
			{
			Q_PowerFlash->PowerFlash[Count].Live = 0;
			Q_PowerFlash->PowerFlash[Count].Pos.y = -255;

			//### Array Reorder
			K = Count;
			while(K < _->NomSparks - 1)
				{
				Q_PowerFlash->PowerFlash[K] = Q_PowerFlash->PowerFlash[K+1];
				K++;
				}

			_->NomSparks--;
			}*/
		}
	

	Q_PowerFlash->PowerFlash[Count].Type = QPOLY_TYPE_TRI;
	Q_PowerFlash->PowerFlash[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
	if(Q_PowerFlash->PowerFlash[Count].SmokeTrail == 0) Q_PowerFlash->PowerFlash[Count].ScaleBIT = 1.0f;
	else Q_PowerFlash->PowerFlash[Count].ScaleBIT = 0.09f;

	Qpo->Vec3d_Subtract(&player[g_Player]->ViewXForm.Translation, &Q_PowerFlash->PowerFlash[Count].Pos, &Q_PowerFlash->PowerFlash[Count].CameraVector);

	Qpo->Vec3d_CrossProduct(&Q_PowerFlash->PowerFlash[Count].CameraVector, &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VecUp);

	Qpo->Vec3d_Normalize(&Q_PowerFlash->PowerFlash[Count].VecUp);

	Q_PowerFlash->PowerFlash[Count].VecSTR = Q_PowerFlash->PowerFlash[Count].TraVec;
	Qpo->Vec3d_Normalize(&Q_PowerFlash->PowerFlash[Count].TraVec);

	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].Pos, -Q_PowerFlash->PowerFlash[Count].Scale/4, &Q_PowerFlash->PowerFlash[Count].VecUp, &Q_PowerFlash->PowerFlash[Count].VertF1);
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertF1, Q_PowerFlash->PowerFlash[Count].Scale/4, &Q_PowerFlash->PowerFlash[Count].VecUp, &Q_PowerFlash->PowerFlash[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertF2, -(Q_PowerFlash->PowerFlash[Count].Scale/6) + ((((float)rand() / 32767)*50)+5), &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertM1, Q_PowerFlash->PowerFlash[Count].Scale/4, &Q_PowerFlash->PowerFlash[Count].VecUp, &Q_PowerFlash->PowerFlash[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertM1, -Q_PowerFlash->PowerFlash[Count].Scale/4, &Q_PowerFlash->PowerFlash[Count].VecUp, &Q_PowerFlash->PowerFlash[Count].VertM2);

	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertM1, -Q_PowerFlash->PowerFlash[Count].Scale/4, &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VertM4);
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertM2, -Q_PowerFlash->PowerFlash[Count].Scale/4, &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VertM3);

	Q_PowerFlash->PowerFlash[Count].GravSTR = Q_PowerFlash->PowerFlash[Count].Gravity;
	Q_PowerFlash->PowerFlash[Count].TraVec = Q_PowerFlash->PowerFlash[Count].VecSTR;

	Q_PowerFlash->PowerFlash[Count].TraVec.y += (Q_PowerFlash->PowerFlash[Count].Gravity*_->TimeScale);
	Q_PowerFlash->PowerFlash[Count].TraLength = Qpo->Vec3d_Length(&Q_PowerFlash->PowerFlash[Count].TraVec);
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertM1, -((Q_PowerFlash->PowerFlash[Count].Speed*(Q_PowerFlash->PowerFlash[Count].TraLength))*_->TimeScale), &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertM2, -((Q_PowerFlash->PowerFlash[Count].Speed*(Q_PowerFlash->PowerFlash[Count].TraLength))*_->TimeScale), &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VertM2);

	Q_PowerFlash->PowerFlash[Count].Gravity = Q_PowerFlash->PowerFlash[Count].GravSTR;
	Q_PowerFlash->PowerFlash[Count].TraVec = Q_PowerFlash->PowerFlash[Count].VecSTR;

	Q_PowerFlash->PowerFlash[Count].TimerGoal = 0;

	if(Q_PowerFlash->PowerFlash[Count].Timer > Q_PowerFlash->PowerFlash[Count].TimerGoal) Q_PowerFlash->PowerFlash[Count].AlpFade -= (((float)rand() / 32767)*30) * _->TimeScale;	//3.5		//((((float)rand() / 32767)*10)+5);
	if(Q_PowerFlash->PowerFlash[Count].AlpFade <= 0)
		{
		Q_PowerFlash->PowerFlash[Count].AlpFade = 0;
		Q_PowerFlash->PowerFlash[Count].Live = 0;
		}

	int a=0;
	while( a <= 2 )
		{
		int b=0;
		while( b <= 3 )
			{
			Q_PowerFlash->PowerFlash[Count].Lvert[a][b].a = Q_PowerFlash->PowerFlash[Count].AlpFade;
			Q_PowerFlash->PowerFlash[Count].Lvert[a][b].b = Q_PowerFlash->PowerFlash[Count].EffBLUE;
			Q_PowerFlash->PowerFlash[Count].Lvert[a][b].g = Q_PowerFlash->PowerFlash[Count].EffGREEN;
			Q_PowerFlash->PowerFlash[Count].Lvert[a][b].r = Q_PowerFlash->PowerFlash[Count].EffRED;
			b++;
			}
		a++;
		}

	//## FRONT ##

	Q_PowerFlash->PowerFlash[Count].Lvert[0][0].u = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][0].v = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][0].x = Q_PowerFlash->PowerFlash[Count].VertF1.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][0].y = Q_PowerFlash->PowerFlash[Count].VertF1.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][0].z = Q_PowerFlash->PowerFlash[Count].VertF1.z;
				
	Q_PowerFlash->PowerFlash[Count].Lvert[0][1].u = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][1].v = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][1].x = Q_PowerFlash->PowerFlash[Count].VertF2.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][1].y = Q_PowerFlash->PowerFlash[Count].VertF2.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][1].z = Q_PowerFlash->PowerFlash[Count].VertF2.z;
				
	Q_PowerFlash->PowerFlash[Count].Lvert[0][2].u = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][2].v = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][2].x = Q_PowerFlash->PowerFlash[Count].VertM1.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][2].y = Q_PowerFlash->PowerFlash[Count].VertM1.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][2].z = Q_PowerFlash->PowerFlash[Count].VertM1.z;

	Q_PowerFlash->PowerFlash[Count].Lvert[0][3].u = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][3].v = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][3].x = Q_PowerFlash->PowerFlash[Count].VertM2.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][3].y = Q_PowerFlash->PowerFlash[Count].VertM2.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[0][3].z = Q_PowerFlash->PowerFlash[Count].VertM2.z;

	//## MIDDLE ##

	Q_PowerFlash->PowerFlash[Count].Lvert[1][0].u = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][0].v = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][0].x = Q_PowerFlash->PowerFlash[Count].VertM1.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][0].y = Q_PowerFlash->PowerFlash[Count].VertM1.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][0].z = Q_PowerFlash->PowerFlash[Count].VertM1.z;

	Q_PowerFlash->PowerFlash[Count].Lvert[1][1].u = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][1].v = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][1].x = Q_PowerFlash->PowerFlash[Count].VertM2.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][1].y = Q_PowerFlash->PowerFlash[Count].VertM2.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][1].z = Q_PowerFlash->PowerFlash[Count].VertM2.z;
				
	Q_PowerFlash->PowerFlash[Count].Lvert[1][2].u = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][2].v = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][2].x = Q_PowerFlash->PowerFlash[Count].VertM3.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][2].y = Q_PowerFlash->PowerFlash[Count].VertM3.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][2].z = Q_PowerFlash->PowerFlash[Count].VertM3.z;

	Q_PowerFlash->PowerFlash[Count].Lvert[1][3].u = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][3].v = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][3].x = Q_PowerFlash->PowerFlash[Count].VertM4.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][3].y = Q_PowerFlash->PowerFlash[Count].VertM4.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[1][3].z = Q_PowerFlash->PowerFlash[Count].VertM4.z;

	//## TAIL ##

	Q_PowerFlash->PowerFlash[Count].Lvert[2][0].u = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][0].v = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][0].x = Q_PowerFlash->PowerFlash[Count].VertM3.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][0].y = Q_PowerFlash->PowerFlash[Count].VertM3.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][0].z = Q_PowerFlash->PowerFlash[Count].VertM3.z;
				
	Q_PowerFlash->PowerFlash[Count].Lvert[2][1].u = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][1].v = 0;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][1].x = Q_PowerFlash->PowerFlash[Count].VertM4.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][1].y = Q_PowerFlash->PowerFlash[Count].VertM4.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][1].z = Q_PowerFlash->PowerFlash[Count].VertM4.z;
				
	Q_PowerFlash->PowerFlash[Count].Lvert[2][2].u = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][2].v = 1;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][2].x = Q_PowerFlash->PowerFlash[Count].VertB1.x;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][2].y = Q_PowerFlash->PowerFlash[Count].VertB1.y;
	Q_PowerFlash->PowerFlash[Count].Lvert[2][2].z = Q_PowerFlash->PowerFlash[Count].VertB1.z;

	//if(Q_PowerFlash->PowerFlash[Count].SmokeTrail == 0)
	//	{
	//Qpo->Poly_AddOnce(&Q_PowerFlash->PowerFlash[Count].Lvert[0][0], 4, Medias->flame[Q_PowerFlash->PowerFlash[Count].MatCNT], Q_PowerFlash->PowerFlash[Count].Type, Q_PowerFlash->PowerFlash[Count].RenderFlags, Q_PowerFlash->PowerFlash[Count].ScaleBIT);
	//Qpo->Poly_AddOnce(&Q_PowerFlash->PowerFlash[Count].Lvert[1][0], 4, Medias->flame[Q_PowerFlash->PowerFlash[Count].MatCNT], Q_PowerFlash->PowerFlash[Count].Type, Q_PowerFlash->PowerFlash[Count].RenderFlags, Q_PowerFlash->PowerFlash[Count].ScaleBIT);
	//Qpo->Poly_AddOnce(&Q_PowerFlash->PowerFlash[Count].Lvert[2][0], 3, Medias->flame[Q_PowerFlash->PowerFlash[Count].MatCNT], Q_PowerFlash->PowerFlash[Count].Type, Q_PowerFlash->PowerFlash[Count].RenderFlags, Q_PowerFlash->PowerFlash[Count].ScaleBIT);
	//	}
	//else
	//	{
		//Qpo->Poly_AddOnce(&Q_PowerFlash->PowerFlash[Count].Lvert[0][0], 1, Medias->radfire[Q_PowerFlash->PowerFlash[Count].MatCnt], QPOLY_TYPE_PNT, Q_PowerFlash->PowerFlash[Count].RenderFlags, Q_PowerFlash->PowerFlash[Count].ScaleBIT);
		//Qpo->Poly_AddOnce(&Q_PowerFlash->PowerFlash[Count].Lvert[1][0], 1, Medias->radfire[Q_PowerFlash->PowerFlash[Count].MatCnt], QPOLY_TYPE_PNT, Q_PowerFlash->PowerFlash[Count].RenderFlags, Q_PowerFlash->PowerFlash[Count].ScaleBIT);
		//Qpo->Poly_AddOnce(&Q_PowerFlash->PowerFlash[Count].Lvert[2][0], 1, Medias->radfire[Q_PowerFlash->PowerFlash[Count].MatCnt], QPOLY_TYPE_PNT, Q_PowerFlash->PowerFlash[Count].RenderFlags, Q_PowerFlash->PowerFlash[Count].ScaleBIT);
		
		//if(Q_PowerFlash->PowerFlash[Count].MatCnt+1 <= 15) Q_PowerFlash->PowerFlash[Count].MatCnt += 1;
		//else Q_PowerFlash->PowerFlash[Count].MatCnt = 10;
	//	}

	Q_PowerFlash->PowerFlash[Count].VertF1 = Q_PowerFlash->PowerFlash[Count].Pos;

	Qpo->Vec3d_AddScaled(&Q_PowerFlash->PowerFlash[Count].VertF1, -Q_PowerFlash->PowerFlash[Count].Speed * (Q_PowerFlash->PowerFlash[Count].Size/20), &Q_PowerFlash->PowerFlash[Count].TraVec, &Q_PowerFlash->PowerFlash[Count].VertM1);

	Q.ShowLine(&Q_PowerFlash->PowerFlash[Count].VertF1, &Q_PowerFlash->PowerFlash[Count].VertM1, &player[g_Player]->ViewXForm.Translation, Q_PowerFlash->PowerFlash[Count].Size, Medias->flame[Q_PowerFlash->PowerFlash[Count].MatCNT], Q_PowerFlash->PowerFlash[Count].AlpFade, 255, 255, 255, 0);

	player[g_Player]->ATTCoronaLvert.x = Q_PowerFlash->PowerFlash[Count].Pos.x;
	player[g_Player]->ATTCoronaLvert.y = Q_PowerFlash->PowerFlash[Count].Pos.y;
	player[g_Player]->ATTCoronaLvert.z = Q_PowerFlash->PowerFlash[Count].Pos.z;
	player[g_Player]->ATTCoronaLvert.r = 255;
	player[g_Player]->ATTCoronaLvert.g = 255;
	player[g_Player]->ATTCoronaLvert.b = 255;
	player[g_Player]->ATTCoronaLvert.a = Q_PowerFlash->PowerFlash[Count].AlpFade/3;

	Qpo->Poly_AddOnce(&player[g_Player]->ATTCoronaLvert, 1, Medias->SparkCorona[player[g_Player]->ATTCoronaMatt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.14);

	if(TIME > Q_PowerFlash->PowerFlash[Count].MatCNTtimer + 1)
		{
		if(Q_PowerFlash->PowerFlash[Count].MatCNT + 1 < 16)
			{
			Q_PowerFlash->PowerFlash[Count].MatCNT++;
			Q_PowerFlash->PowerFlash[Count].MatCNTtimer = TIME;
			}
		else Q_PowerFlash->PowerFlash[Count].MatCNT = 6;
		}
	}

};