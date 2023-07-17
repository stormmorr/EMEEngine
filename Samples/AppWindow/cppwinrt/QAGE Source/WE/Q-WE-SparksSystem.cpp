/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*//*- Minor Component -Sparks System-

*/

#include "pch.h"

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
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

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::Spark_SparkFrame(int Count)
{
	Q_BSparks->BSparks[Count].Timer++;

	if(Q_BSparks->BSparks[Count].SmokeTrail == 0) Q_BSparks->BSparks[Count].Scale = 2.5;
	else
		{
		Q_BSparks->BSparks[Count].Scale = 80;	//55

		jet=0;
		while(jet < 2)	//3
			{
			Q_Cloud->Cloud[_->NomCloud].CloudType = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_BSparks->BSparks[Count].Pos;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*155)+50;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.1;

			Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*2) + 2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

			//Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*6;
			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*3;

			Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
			jet++;
			}


		jet=0;
		while(jet < 2)
			{
			//FLAME CLOUD
			Q_Cloud->Cloud[_->NomCloud].CloudType = 8;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_BSparks->BSparks[Count].Pos;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*145);
			Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.35) * (0.05+(1-(Q_BSparks->BSparks[Count].Speed/100)));
			//Q_Cloud->Cloud[_->NomCloud].CloudScale = (((float)rand() / 32767)*0.15) * (0.235+(1-(Q_BSparks->BSparks[Count].Speed/100)));

			if((((float)rand() / 32767)-0.5) > 0)
				{
				//RED CLOUD
				Q_Cloud->Cloud[_->NomCloud].CloudRed = (((float)rand() / 32767)*45) + 250;
				Q_Cloud->Cloud[_->NomCloud].CloudGreen = 200;
				Q_Cloud->Cloud[_->NomCloud].CloudBlue = 200;
				}
			else
				{
				//YELLOW CLOUD
				Q_Cloud->Cloud[_->NomCloud].CloudRed = (((float)rand() / 32767)*45) + 250;
				Q_Cloud->Cloud[_->NomCloud].CloudGreen = (((float)rand() / 32767)*45) + 250;
				Q_Cloud->Cloud[_->NomCloud].CloudBlue = 200;
				}

			Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += ((((float)rand() / 32767)-0.5)*2) + 1;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

			Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*25;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*25;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*25;

			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*4;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
			jet++;
			}
		}
		

	Q_BSparks->BSparks[Count].TraVec.y -= Q_BSparks->BSparks[Count].Gravity*_->TimeScale;

	Q_BSparks->BSparks[Count].OldPos = Q_BSparks->BSparks[Count].Pos;
	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].Pos, Q_BSparks->BSparks[Count].Speed*_->TimeScale, &Q_BSparks->BSparks[Count].TraVec, &Q_BSparks->BSparks[Count].Pos);


	if(Qpo->Collision_RayTest(
		 NULL,
		 NULL,
		 &Q_BSparks->BSparks[Count].OldPos,
		 &Q_BSparks->BSparks[Count].Pos,
		 // GE_CONTENTS_CANNOT_OCCUPY
		 /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
		 0xffffffff, NULL, NULL,
		 &Q_BSparks->BSparks[Count].Collision))
		{
		Q_BSparks->BSparks[Count].Pos = Q_BSparks->BSparks[Count].OldPos;


		if(Q_BSparks->BSparks[Count].Bounce < 2)	//2
			{
			Q_BSparks->BSparks[Count].TraVec = Q.PHY_BounceVector(Q_BSparks->BSparks[Count].TraVec, Q_BSparks->BSparks[Count].Collision.Plane.Normal);

			//BETTER
			Q_BSparks->BSparks[Count].Gravity = Q_BSparks->BSparks[Count].Gravity * 2;
			Q_BSparks->BSparks[Count].Speed = Q_BSparks->BSparks[Count].Speed / 1.5;
			Q_BSparks->BSparks[Count].Bounce++;
			}
		else
			{
			Q_BSparks->BSparks[Count].Live = 0;
			Q_BSparks->BSparks[Count].Pos.y = -255;

			//### Array Reorder
			int K = Count;
			while(K < _->NomSparks - 1)
				{
				Q_BSparks->BSparks[K] = Q_BSparks->BSparks[K+1];
				K++;
				}

			_->NomSparks--;
			}
		}
	

	Q_BSparks->BSparks[Count].Type = QPOLY_TYPE_TRI;
	Q_BSparks->BSparks[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
	if(Q_BSparks->BSparks[Count].SmokeTrail == 0) Q_BSparks->BSparks[Count].ScaleBIT = 1.0f;
	else Q_BSparks->BSparks[Count].ScaleBIT = 0.09f;

	Qpo->Vec3d_Subtract(&player[g_Player]->ViewXForm.Translation, &Q_BSparks->BSparks[Count].Pos, &Q_BSparks->BSparks[Count].CameraVector);

	Qpo->Vec3d_CrossProduct(&Q_BSparks->BSparks[Count].CameraVector, &Q_BSparks->BSparks[Count].TraVec, &Q_BSparks->BSparks[Count].VecUp);

	Qpo->Vec3d_Normalize(&Q_BSparks->BSparks[Count].VecUp);

	Q_BSparks->BSparks[Count].VecSTR = Q_BSparks->BSparks[Count].TraVec;
	Qpo->Vec3d_Normalize(&Q_BSparks->BSparks[Count].TraVec);

	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].Pos, -Q_BSparks->BSparks[Count].Scale/16, &Q_BSparks->BSparks[Count].VecUp, &Q_BSparks->BSparks[Count].VertF1);
	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].VertF1, Q_BSparks->BSparks[Count].Scale/8, &Q_BSparks->BSparks[Count].VecUp, &Q_BSparks->BSparks[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].VertF2, -Q_BSparks->BSparks[Count].Scale/8, &Q_BSparks->BSparks[Count].TraVec, &Q_BSparks->BSparks[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].VertM1, Q_BSparks->BSparks[Count].Scale/16, &Q_BSparks->BSparks[Count].VecUp, &Q_BSparks->BSparks[Count].VertM1);
	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].VertM1, -Q_BSparks->BSparks[Count].Scale/4, &Q_BSparks->BSparks[Count].VecUp, &Q_BSparks->BSparks[Count].VertM2);

	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].VertM1, -Q_BSparks->BSparks[Count].Scale/4, &Q_BSparks->BSparks[Count].TraVec, &Q_BSparks->BSparks[Count].VertM4);
	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].VertM2, -Q_BSparks->BSparks[Count].Scale/4, &Q_BSparks->BSparks[Count].TraVec, &Q_BSparks->BSparks[Count].VertM3);

	Q_BSparks->BSparks[Count].GravSTR = Q_BSparks->BSparks[Count].Gravity;
	Q_BSparks->BSparks[Count].TraVec = Q_BSparks->BSparks[Count].VecSTR;

	Q_BSparks->BSparks[Count].TraVec.y += (Q_BSparks->BSparks[Count].Gravity*_->TimeScale);
	Q_BSparks->BSparks[Count].TraLength = Qpo->Vec3d_Length(&Q_BSparks->BSparks[Count].TraVec);
	Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[Count].Pos, -((Q_BSparks->BSparks[Count].Speed*(Q_BSparks->BSparks[Count].TraLength*1))*_->TimeScale), &Q_BSparks->BSparks[Count].TraVec, &Q_BSparks->BSparks[Count].VertB1);

	Q_BSparks->BSparks[Count].Gravity = Q_BSparks->BSparks[Count].GravSTR;
	Q_BSparks->BSparks[Count].TraVec = Q_BSparks->BSparks[Count].VecSTR;

	if(Q_BSparks->BSparks[Count].Timer > Q_BSparks->BSparks[Count].TimerGoal) Q_BSparks->BSparks[Count].AlpFade -= 10;//((((float)rand() / 32767)*10)+5);
	if(Q_BSparks->BSparks[Count].AlpFade <= 0)
		{
		Q_BSparks->BSparks[Count].AlpFade = 0;
		Q_BSparks->BSparks[Count].Live = 0;
		}

	int a=0;
	while( a <= 2 )
		{
		int b=0;
		while( b <= 3 )
			{
			Q_BSparks->BSparks[Count].Lvert[a][b].a = Q_BSparks->BSparks[Count].AlpFade;
			Q_BSparks->BSparks[Count].Lvert[a][b].b = 255;
			Q_BSparks->BSparks[Count].Lvert[a][b].g = 255;
			Q_BSparks->BSparks[Count].Lvert[a][b].r = 255;
			b++;
			}
		a++;
		}

	//## FRONT ##

	Q_BSparks->BSparks[Count].Lvert[0][0].u = 0;
	Q_BSparks->BSparks[Count].Lvert[0][0].v = 1;
	Q_BSparks->BSparks[Count].Lvert[0][0].x = Q_BSparks->BSparks[Count].VertF1.x;
	Q_BSparks->BSparks[Count].Lvert[0][0].y = Q_BSparks->BSparks[Count].VertF1.y;
	Q_BSparks->BSparks[Count].Lvert[0][0].z = Q_BSparks->BSparks[Count].VertF1.z;
				
	Q_BSparks->BSparks[Count].Lvert[0][1].u = 1;
	Q_BSparks->BSparks[Count].Lvert[0][1].v = 1;
	Q_BSparks->BSparks[Count].Lvert[0][1].x = Q_BSparks->BSparks[Count].VertF2.x;
	Q_BSparks->BSparks[Count].Lvert[0][1].y = Q_BSparks->BSparks[Count].VertF2.y;
	Q_BSparks->BSparks[Count].Lvert[0][1].z = Q_BSparks->BSparks[Count].VertF2.z;
				
	Q_BSparks->BSparks[Count].Lvert[0][2].u = 1;
	Q_BSparks->BSparks[Count].Lvert[0][2].v = 0;
	Q_BSparks->BSparks[Count].Lvert[0][2].x = Q_BSparks->BSparks[Count].VertM1.x;
	Q_BSparks->BSparks[Count].Lvert[0][2].y = Q_BSparks->BSparks[Count].VertM1.y;
	Q_BSparks->BSparks[Count].Lvert[0][2].z = Q_BSparks->BSparks[Count].VertM1.z;

	Q_BSparks->BSparks[Count].Lvert[0][3].u = 0;
	Q_BSparks->BSparks[Count].Lvert[0][3].v = 0;
	Q_BSparks->BSparks[Count].Lvert[0][3].x = Q_BSparks->BSparks[Count].VertM2.x;
	Q_BSparks->BSparks[Count].Lvert[0][3].y = Q_BSparks->BSparks[Count].VertM2.y;
	Q_BSparks->BSparks[Count].Lvert[0][3].z = Q_BSparks->BSparks[Count].VertM2.z;

	//## MIDDLE ##

	Q_BSparks->BSparks[Count].Lvert[1][0].u = 0;
	Q_BSparks->BSparks[Count].Lvert[1][0].v = 1;
	Q_BSparks->BSparks[Count].Lvert[1][0].x = Q_BSparks->BSparks[Count].VertM1.x;
	Q_BSparks->BSparks[Count].Lvert[1][0].y = Q_BSparks->BSparks[Count].VertM1.y;
	Q_BSparks->BSparks[Count].Lvert[1][0].z = Q_BSparks->BSparks[Count].VertM1.z;

	Q_BSparks->BSparks[Count].Lvert[1][1].u = 0;
	Q_BSparks->BSparks[Count].Lvert[1][1].v = 0;
	Q_BSparks->BSparks[Count].Lvert[1][1].x = Q_BSparks->BSparks[Count].VertM2.x;
	Q_BSparks->BSparks[Count].Lvert[1][1].y = Q_BSparks->BSparks[Count].VertM2.y;
	Q_BSparks->BSparks[Count].Lvert[1][1].z = Q_BSparks->BSparks[Count].VertM2.z;
				
	Q_BSparks->BSparks[Count].Lvert[1][2].u = 1;
	Q_BSparks->BSparks[Count].Lvert[1][2].v = 0;
	Q_BSparks->BSparks[Count].Lvert[1][2].x = Q_BSparks->BSparks[Count].VertM3.x;
	Q_BSparks->BSparks[Count].Lvert[1][2].y = Q_BSparks->BSparks[Count].VertM3.y;
	Q_BSparks->BSparks[Count].Lvert[1][2].z = Q_BSparks->BSparks[Count].VertM3.z;

	Q_BSparks->BSparks[Count].Lvert[1][3].u = 1;
	Q_BSparks->BSparks[Count].Lvert[1][3].v = 1;
	Q_BSparks->BSparks[Count].Lvert[1][3].x = Q_BSparks->BSparks[Count].VertM4.x;
	Q_BSparks->BSparks[Count].Lvert[1][3].y = Q_BSparks->BSparks[Count].VertM4.y;
	Q_BSparks->BSparks[Count].Lvert[1][3].z = Q_BSparks->BSparks[Count].VertM4.z;

	//## TAIL ##

	Q_BSparks->BSparks[Count].Lvert[2][0].u = 0;
	Q_BSparks->BSparks[Count].Lvert[2][0].v = 0;
	Q_BSparks->BSparks[Count].Lvert[2][0].x = Q_BSparks->BSparks[Count].VertM3.x;
	Q_BSparks->BSparks[Count].Lvert[2][0].y = Q_BSparks->BSparks[Count].VertM3.y;
	Q_BSparks->BSparks[Count].Lvert[2][0].z = Q_BSparks->BSparks[Count].VertM3.z;
				
	Q_BSparks->BSparks[Count].Lvert[2][1].u = 0;
	Q_BSparks->BSparks[Count].Lvert[2][1].v = 1;
	Q_BSparks->BSparks[Count].Lvert[2][1].x = Q_BSparks->BSparks[Count].VertM4.x;
	Q_BSparks->BSparks[Count].Lvert[2][1].y = Q_BSparks->BSparks[Count].VertM4.y;
	Q_BSparks->BSparks[Count].Lvert[2][1].z = Q_BSparks->BSparks[Count].VertM4.z;
				
	Q_BSparks->BSparks[Count].Lvert[2][2].u = 1;
	Q_BSparks->BSparks[Count].Lvert[2][2].v = 0.5;
	Q_BSparks->BSparks[Count].Lvert[2][2].x = Q_BSparks->BSparks[Count].VertB1.x;
	Q_BSparks->BSparks[Count].Lvert[2][2].y = Q_BSparks->BSparks[Count].VertB1.y;
	Q_BSparks->BSparks[Count].Lvert[2][2].z = Q_BSparks->BSparks[Count].VertB1.z;

	if(Q_BSparks->BSparks[Count].SmokeTrail == 0)
		{
		Qpo->Poly_AddOnce(&Q_BSparks->BSparks[Count].Lvert[0][0], 4, Medias->Spark, Q_BSparks->BSparks[Count].Type, Q_BSparks->BSparks[Count].RenderFlags, Q_BSparks->BSparks[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_BSparks->BSparks[Count].Lvert[1][0], 4, Medias->Sparkmid, Q_BSparks->BSparks[Count].Type, Q_BSparks->BSparks[Count].RenderFlags, Q_BSparks->BSparks[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_BSparks->BSparks[Count].Lvert[2][0], 3, Medias->Sparktail, Q_BSparks->BSparks[Count].Type, Q_BSparks->BSparks[Count].RenderFlags, Q_BSparks->BSparks[Count].ScaleBIT);
		}
}

};//END NAMESPACE GVARS
