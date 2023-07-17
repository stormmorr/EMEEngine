/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Blood System-

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

void Q_EFFCon::Spark_BloodFrame(int Count)
	{
	Q_BBlood->BBlood[Count].Scale = 25; //6;		//2.5

	Q_BBlood->BBlood[Count].TraVec.y -= Q_BBlood->BBlood[Count].Gravity;	//- _->TimeScale
														//\/ _->TimeScale
	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].Pos, Q_BBlood->BBlood[Count].Speed, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].Pos);
				
	Q_BBlood->BBlood[Count].AlpFade -= (((float)rand() / 32767)*4 + 1) *_->TimeScale; //(((float)rand() / 32767)*20 + 10) *_->TimeScale;

	if(Q_BBlood->BBlood[Count].Pos.y < -250)
		{
		Q_BBlood->BBlood[Count].Live = 0;
		Q_BBlood->BBlood[Count].Pos.y = -255;

		//### Array Reorder
		int K = Count;
		while(K < _->NomBlood - 1)
			{
			Q_BBlood->BBlood[K] = Q_BBlood->BBlood[K+1];
			K++;
			}

		_->NomBlood--;
		}


	if(Q_BBlood->BBlood[Count].SmokeTrail == 1 && Q_BBlood->BBlood[Count].CloudTimer == 3)
		{
		Q_BBlood->BBlood[Count].CloudTimer = 0;
		Q_Cloud->Cloud[_->NomCloud].CloudType = 1;

		//Q_Cloud->Cloud[_->NomCloud].CloudBitmap = Medias->CloudBlood;

		Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_BBlood->BBlood[Count].Pos;

		Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*0.5;
		Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*0.5;
		Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*0.5;

		Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*55)+50;
		Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.015)+0.005;

		Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*0.1;
		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*0.1;
		Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*0.1;

		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((((float)rand() / 32767)-0.5)*0.3)+0.1;

		Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

		_->NomCloud++;
		if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
		}
	else Q_BBlood->BBlood[Count].CloudTimer++;

	Q_BBlood->BBlood[Count].Type = QPOLY_TYPE_GOR;
	Q_BBlood->BBlood[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
	Q_BBlood->BBlood[Count].ScaleBIT = 1.0f;


	Qpo->Vec3d_Subtract(&player[g_Player]->ViewXForm.Translation, &Q_BBlood->BBlood[Count].Pos, &Q_BBlood->BBlood[Count].CameraVector);

	Qpo->Vec3d_CrossProduct(&Q_BBlood->BBlood[Count].CameraVector, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].VecUp);

	Qpo->Vec3d_Normalize(&Q_BBlood->BBlood[Count].VecUp);
	Q_BBlood->BBlood[Count].VecSTR = Q_BBlood->BBlood[Count].TraVec;
	Qpo->Vec3d_Normalize(&Q_BBlood->BBlood[Count].TraVec);


	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].Pos, -Q_BBlood->BBlood[Count].Scale/16, &Q_BBlood->BBlood[Count].VecUp, &Q_BBlood->BBlood[Count].VertF1);
	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].VertF1, Q_BBlood->BBlood[Count].Scale/8, &Q_BBlood->BBlood[Count].VecUp, &Q_BBlood->BBlood[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].VertF2, -Q_BBlood->BBlood[Count].Scale/8, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].VertM1, Q_BBlood->BBlood[Count].Scale/16, &Q_BBlood->BBlood[Count].VecUp, &Q_BBlood->BBlood[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].VertM1, -Q_BBlood->BBlood[Count].Scale/4, &Q_BBlood->BBlood[Count].VecUp, &Q_BBlood->BBlood[Count].VertM2);

	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].VertM1, -Q_BBlood->BBlood[Count].Scale/4, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].VertM4);
	Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].VertM2, -Q_BBlood->BBlood[Count].Scale/4, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].VertM3);

	Q_BBlood->BBlood[Count].GravSTR = Q_BBlood->BBlood[Count].Gravity;

	if(Q_BBlood->BBlood[Count].Bounce == 5)
		{
		Q_BBlood->BBlood[Count].TraVec.y += (Q_BBlood->BBlood[Count].Gravity*_->TimeScale)*Q_BBlood->BBlood[Count].TraVec.y;
		Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].Pos, -(Q_BBlood->BBlood[Count].Speed*_->TimeScale)*4, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].VertB1);
		}
	else Qpo->Vec3d_AddScaled(&Q_BBlood->BBlood[Count].Pos, -Q_BBlood->BBlood[Count].Scale*2, &Q_BBlood->BBlood[Count].TraVec, &Q_BBlood->BBlood[Count].VertB1);

	Q_BBlood->BBlood[Count].Gravity = Q_BBlood->BBlood[Count].GravSTR;
	Q_BBlood->BBlood[Count].TraVec = Q_BBlood->BBlood[Count].VecSTR;


	if(Q_BBlood->BBlood[Count].EffectType == 1)
		{
		int a=0;
		while( a <= 2 )
			{
			int b=0;
			while( b <= 3 )
				{
				Q_BBlood->BBlood[Count].Lvert[a][b].a = Q_BBlood->BBlood[Count].AlpFade/1.75;	//210
				Q_BBlood->BBlood[Count].Lvert[a][b].b = 65;
				Q_BBlood->BBlood[Count].Lvert[a][b].g = 65;
				Q_BBlood->BBlood[Count].Lvert[a][b].r = 65;
				b++;
				}
			a++;
			}
		}
	else
		{
		int a=0;
		while( a <= 2 )
			{
			int b=0;
			while( b <= 3 )
				{
				Q_BBlood->BBlood[Count].Lvert[a][b].a = Q_BBlood->BBlood[Count].AlpFade;	//210
				Q_BBlood->BBlood[Count].Lvert[a][b].b = 0;
				Q_BBlood->BBlood[Count].Lvert[a][b].g = 0;
				Q_BBlood->BBlood[Count].Lvert[a][b].r = 210;
				b++;
				}
			a++;
			}
		}

	//## FRONT ##

	Q_BBlood->BBlood[Count].Lvert[0][0].u = 0;
	Q_BBlood->BBlood[Count].Lvert[0][0].v = 1;
	Q_BBlood->BBlood[Count].Lvert[0][0].x = Q_BBlood->BBlood[Count].VertF1.x;
	Q_BBlood->BBlood[Count].Lvert[0][0].y = Q_BBlood->BBlood[Count].VertF1.y;
	Q_BBlood->BBlood[Count].Lvert[0][0].z = Q_BBlood->BBlood[Count].VertF1.z;
	Q_BBlood->BBlood[Count].Lvert[0][1].u = 1;
	Q_BBlood->BBlood[Count].Lvert[0][1].v = 1;
	Q_BBlood->BBlood[Count].Lvert[0][1].x = Q_BBlood->BBlood[Count].VertF2.x;
	Q_BBlood->BBlood[Count].Lvert[0][1].y = Q_BBlood->BBlood[Count].VertF2.y;
	Q_BBlood->BBlood[Count].Lvert[0][1].z = Q_BBlood->BBlood[Count].VertF2.z;
	Q_BBlood->BBlood[Count].Lvert[0][2].u = 1;
	Q_BBlood->BBlood[Count].Lvert[0][2].v = 0;
	Q_BBlood->BBlood[Count].Lvert[0][2].x = Q_BBlood->BBlood[Count].VertM1.x;
	Q_BBlood->BBlood[Count].Lvert[0][2].y = Q_BBlood->BBlood[Count].VertM1.y;
	Q_BBlood->BBlood[Count].Lvert[0][2].z = Q_BBlood->BBlood[Count].VertM1.z;
	Q_BBlood->BBlood[Count].Lvert[0][3].u = 0;
	Q_BBlood->BBlood[Count].Lvert[0][3].v = 0;
	Q_BBlood->BBlood[Count].Lvert[0][3].x = Q_BBlood->BBlood[Count].VertM2.x;
	Q_BBlood->BBlood[Count].Lvert[0][3].y = Q_BBlood->BBlood[Count].VertM2.y;
	Q_BBlood->BBlood[Count].Lvert[0][3].z = Q_BBlood->BBlood[Count].VertM2.z;

	//## MIDDLE ##

	Q_BBlood->BBlood[Count].Lvert[1][0].u = 0;
	Q_BBlood->BBlood[Count].Lvert[1][0].v = 1;
	Q_BBlood->BBlood[Count].Lvert[1][0].x = Q_BBlood->BBlood[Count].VertM1.x;
	Q_BBlood->BBlood[Count].Lvert[1][0].y = Q_BBlood->BBlood[Count].VertM1.y;
	Q_BBlood->BBlood[Count].Lvert[1][0].z = Q_BBlood->BBlood[Count].VertM1.z;
	Q_BBlood->BBlood[Count].Lvert[1][1].u = 0;
	Q_BBlood->BBlood[Count].Lvert[1][1].v = 0;
	Q_BBlood->BBlood[Count].Lvert[1][1].x = Q_BBlood->BBlood[Count].VertM2.x;
	Q_BBlood->BBlood[Count].Lvert[1][1].y = Q_BBlood->BBlood[Count].VertM2.y;
	Q_BBlood->BBlood[Count].Lvert[1][1].z = Q_BBlood->BBlood[Count].VertM2.z;
	Q_BBlood->BBlood[Count].Lvert[1][2].u = 1;
	Q_BBlood->BBlood[Count].Lvert[1][2].v = 0;
	Q_BBlood->BBlood[Count].Lvert[1][2].x = Q_BBlood->BBlood[Count].VertM3.x;
	Q_BBlood->BBlood[Count].Lvert[1][2].y = Q_BBlood->BBlood[Count].VertM3.y;
	Q_BBlood->BBlood[Count].Lvert[1][2].z = Q_BBlood->BBlood[Count].VertM3.z;
	Q_BBlood->BBlood[Count].Lvert[1][3].u = 1;
	Q_BBlood->BBlood[Count].Lvert[1][3].v = 1;
	Q_BBlood->BBlood[Count].Lvert[1][3].x = Q_BBlood->BBlood[Count].VertM4.x;
	Q_BBlood->BBlood[Count].Lvert[1][3].y = Q_BBlood->BBlood[Count].VertM4.y;
	Q_BBlood->BBlood[Count].Lvert[1][3].z = Q_BBlood->BBlood[Count].VertM4.z;

	//## TAIL ##

	Q_BBlood->BBlood[Count].Lvert[2][0].u = 0;
	Q_BBlood->BBlood[Count].Lvert[2][0].v = 0;
	Q_BBlood->BBlood[Count].Lvert[2][0].x = Q_BBlood->BBlood[Count].VertM3.x;
	Q_BBlood->BBlood[Count].Lvert[2][0].y = Q_BBlood->BBlood[Count].VertM3.y;
	Q_BBlood->BBlood[Count].Lvert[2][0].z = Q_BBlood->BBlood[Count].VertM3.z;
	Q_BBlood->BBlood[Count].Lvert[2][1].u = 0;
	Q_BBlood->BBlood[Count].Lvert[2][1].v = 1;
	Q_BBlood->BBlood[Count].Lvert[2][1].x = Q_BBlood->BBlood[Count].VertM4.x;
	Q_BBlood->BBlood[Count].Lvert[2][1].y = Q_BBlood->BBlood[Count].VertM4.y;
	Q_BBlood->BBlood[Count].Lvert[2][1].z = Q_BBlood->BBlood[Count].VertM4.z;
	Q_BBlood->BBlood[Count].Lvert[2][2].u = 1;
	Q_BBlood->BBlood[Count].Lvert[2][2].v = 0.5;
	Q_BBlood->BBlood[Count].Lvert[2][2].x = Q_BBlood->BBlood[Count].VertB1.x;
	Q_BBlood->BBlood[Count].Lvert[2][2].y = Q_BBlood->BBlood[Count].VertB1.y;
	Q_BBlood->BBlood[Count].Lvert[2][2].z = Q_BBlood->BBlood[Count].VertB1.z;


	if(Q_BBlood->BBlood[Count].EffectType == 1)
		{
		Qpo->Poly_AddOnce(&Q_BBlood->BBlood[Count].Lvert[0][0], 4, Medias->Spark, Q_BBlood->BBlood[Count].Type, Q_BBlood->BBlood[Count].RenderFlags, Q_BBlood->BBlood[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_BBlood->BBlood[Count].Lvert[1][0], 4, Medias->Sparkmid, Q_BBlood->BBlood[Count].Type, Q_BBlood->BBlood[Count].RenderFlags, Q_BBlood->BBlood[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_BBlood->BBlood[Count].Lvert[2][0], 3, Medias->Sparktail, Q_BBlood->BBlood[Count].Type, Q_BBlood->BBlood[Count].RenderFlags, Q_BBlood->BBlood[Count].ScaleBIT);
		}
	}

};