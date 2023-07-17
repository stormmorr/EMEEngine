/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Explosions-

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

//########  - EXPLOSIONS -  ########//

void Q_EFFCon::Explosion_ServerFrame(int Count)
	{
	if(Q_Explosion->Explosion[Count].Init == 0)
		{
		Q_Explosion->Explosion[Count].Init = 1;
		Q_Explosion->Explosion[Count].AirShkLive = 1;
		Q_Explosion->Explosion[Count].GrndShkLive = 1;

		Q_Explosion->Explosion[Count].AirShkScale = 0;
		Q_Explosion->Explosion[Count].AirShkAlpha = 255;
		Q_Explosion->Explosion[Count].GrndShkScale = 0;
		Q_Explosion->Explosion[Count].GrndShkAlpha = 255;
		Q_Explosion->Explosion[Count].BlastAlpha = 255;
		Q_Explosion->Explosion[Count].BlastMat = 0;

		Q_Explosion->Explosion[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_Explosion->Explosion[Count].LightColor.red = 255.0f;
		Q_Explosion->Explosion[Count].LightColor.green = 255.0f;
		Q_Explosion->Explosion[Count].LightColor.blue = 200.0f;
		Q_Explosion->Explosion[Count].LightColor.alpha = 255.0f;

		jet = 0;
		while(jet < Q_Explosion->Explosion[Count].ExpSize * 4.2)
			{
			Q_BSparks->BSparks[_->NomSparks].Pos = Q_Explosion->Explosion[Count].Pos;

			Q_BSparks->BSparks[_->NomSparks].TraVec = Q_Explosion->Explosion[Count].CollPlaneNormal;

			Q_BSparks->BSparks[_->NomSparks].TraVec.x += ((((float)rand() / 32767)-0.5))*4;
			Q_BSparks->BSparks[_->NomSparks].TraVec.y += (((((float)rand() / 32767)-0.5))+1.5);
			Q_BSparks->BSparks[_->NomSparks].TraVec.z += ((((float)rand() / 32767)-0.5))*4;

			Q_BSparks->BSparks[_->NomSparks].AlpFade = 255;
			Q_BSparks->BSparks[_->NomSparks].Timer = 0;
			Q_BSparks->BSparks[_->NomSparks].TimerGoal = ((((float)rand() / 32767)*2000)+500);

			Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[_->NomSparks].Pos, 1, &Q_BSparks->BSparks[_->NomSparks].TraVec, &Q_BSparks->BSparks[_->NomSparks].Pos);

			Q_BSparks->BSparks[_->NomSparks].Speed = 8;
			Q_BSparks->BSparks[_->NomSparks].Gravity = 0.1;

			Q_BSparks->BSparks[_->NomSparks].Bounce = 0;

			Q_BSparks->BSparks[_->NomSparks].SmokeTrail = 1;
			Q_BSparks->BSparks[_->NomSparks].Live = 1;

			_->NomSparks++;
			if(_->NomSparks > 499) _->NomSparks = 0;
			jet++;
			}

		player[g_Player]->CameraShake = 2;
		player[g_Player]->CamShkTIME = 6;

		aero = 0;
		while(aero < 14)
			{
			Q_Cloud->Cloud[_->NomCloud].CloudType = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Explosion->Explosion[Count].Pos;
			
			Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*200;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*200;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*200;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*85)+170;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.6;

			Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*5;

			Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
			aero++;
			}

		Q.RadialDamage(Q_Explosion->Explosion[Count].Team, Q_Explosion->Explosion[Count].AvID, Q_Explosion->Explosion[Count].ExpSize/2.5, Q_Explosion->Explosion[Count].ExpDMG, Q_Explosion->Explosion[Count].Pos, 0, TempVec1);

		////QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Explosion->Explosion[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		Qpo->Sound_Play(Medias->S_Explosion, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Explosion->Explosion[Count].Pos);
		}


	//###Air Shockwave
	if(Q_Explosion->Explosion[Count].AirShkLive == 1)
		{
		Qpo->Vec3d_Copy(&Q_Explosion->Explosion[Count].Pos, &Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Xform.Translation);
		//Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, Q_Explosion->Explosion[Count].AirShkScale,Q_Explosion->Explosion[Count].AirShkScale,Q_Explosion->Explosion[Count].AirShkScale);
		//Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, Q_Explosion->Explosion[Count].AirShkAlpha);

		/*if(Q_Explosion->Explosion[Count].AirShkScale + (0.3*_->TimeScale) < Q_Explosion->Explosion[Count].ExpSize) Q_Explosion->Explosion[Count].AirShkScale += 0.3*_->TimeScale;	//Perfectly parrallel with expandro is +0.1 here and +15 expandro
		else
			{
			Q_Explosion->Explosion[Count].AirShkScale = Q_Explosion->Explosion[Count].ExpSize;
			Q_Explosion->Explosion[Count].AirShkScale += ((((float)rand() / 32767)-0.5)*0.2)*_->TimeScale;
			}*/

		if(Q_Explosion->Explosion[Count].AirShkScale + (0.7*_->TimeScale) < Q_Explosion->Explosion[Count].ExpSize) Q_Explosion->Explosion[Count].AirShkScale += 0.7*_->TimeScale;	//Perfectly parrallel with expandro is +0.1 here and +15 expandro
		else
			{
			Q_Explosion->Explosion[Count].AirShkScale = Q_Explosion->Explosion[Count].ExpSize;
			Q_Explosion->Explosion[Count].AirShkScale += ((((float)rand() / 32767)-0.5)*0.2)*_->TimeScale;
			}

		if(Q_Explosion->Explosion[Count].AirShkScale > Q_Explosion->Explosion[Count].ExpSize/1.4)
			{
			/*if(Q_Explosion->Explosion[Count].AirShkAlpha - (10*_->TimeScale) > 0) Q_Explosion->Explosion[Count].AirShkAlpha -= 10*_->TimeScale;	//-50
			else
				{
				Q_Explosion->Explosion[Count].AirShkAlpha = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, 0,0,0);
				Q_Explosion->Explosion[Count].AirShkLive = 0;
				Qpo->Light_Remove(Q_Explosion->Explosion[Count].Light);
				}*/

			if(Q_Explosion->Explosion[Count].AirShkAlpha - (50*_->TimeScale) > 0) Q_Explosion->Explosion[Count].AirShkAlpha -= 50*_->TimeScale;	//-50
			else
				{
				Q_Explosion->Explosion[Count].AirShkAlpha = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, 0,0,0);
				//~~~~~Qpo->Avatar_ClearPose(Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Avatar, &Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Xform);
				Q_Explosion->Explosion[Count].AirShkLive = 0;
				Qpo->Light_Remove(Q_Explosion->Explosion[Count].Light);
				Q_Explosion->Explosion[Count].Init = 0;
				Q_Explosion->Explosion[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomExplosions - 1)
					{
					Q_Explosion->Explosion[K] = Q_Explosion->Explosion[K+1];
					K++;
					}

				_->NomExplosions--;
				}
			}

		Qpo->Light_SetAttr(Q_Explosion->Explosion[Count].Light, &Q_Explosion->Explosion[Count].Pos, &Q_Explosion->Explosion[Count].LightColor, Q_Explosion->Explosion[Count].AirShkAlpha * 350, true);

		if(Q_Explosion->Explosion[Count].BmpCountSP - 1 > 0) Q_Explosion->Explosion[Count].BmpCountSP--;
		else
			{
			Q_Explosion->Explosion[Count].BmpCountSP = 6;
			if(Q_Explosion->Explosion[Count].BmpCount + 1 < 14) Q_Explosion->Explosion[Count].BmpCount++;	//18
			else Q_Explosion->Explosion[Count].BmpCount = 0;
			}
		}


	//###Ground Shockwave
	if(Q_Explosion->Explosion[Count].GrndShkLive == 1 && 0)
		{
		Qpo->Transform_New(&Q_Explosion->Explosion[Count].AlignMatrix);	//OPTIMISE Calculate once only
		Qpo->Transform_GetIn(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].AligIn);
		//Q_Explosion->Explosion[Count].VecIn = Q_Explosion->Explosion[Count].Collision->Plane.Normal;
		//EDIT
		Q_Explosion->Explosion[Count].VecIn.x = 0;
		Q_Explosion->Explosion[Count].VecIn.y = 1;
		Q_Explosion->Explosion[Count].VecIn.z = 0;

		if(Q_Explosion->Explosion[Count].VecIn.x == 0 && Q_Explosion->Explosion[Count].VecIn.z == 0)
			{
			Q_Explosion->Explosion[Count].VecLeft.x = -1;
			Q_Explosion->Explosion[Count].VecLeft.y = 0;
			Q_Explosion->Explosion[Count].VecLeft.z = 0;
			}
		else
			{
			Qpo->Transform_New_YRotation(&rotmat, PI/2);
			Qpo->Transform_RotateVector(&rotmat, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VecLeft);
			Q_Explosion->Explosion[Count].VecLeft.y = 0;
			}
		Qpo->Vec3d_CrossProduct(&Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VecUp);
		Qpo->Transform_New_LeftUpIn(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VecIn);
		Q_Explosion->Explosion[Count].AlignMatrix.Translation = Q_Explosion->Explosion[Count].Pos;
		Qpo->Transform_New_ZRotation(&rotmat, (((float)rand() / 32767)*6)*_->TimeScale);
		Qpo->Transform_Multiply(&Q_Explosion->Explosion[Count].AlignMatrix, &rotmat, &Q_Explosion->Explosion[Count].AlignMatrix);
		Qpo->Transform_GetUp(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecUp);
		Qpo->Transform_GetLeft(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecLeft);
		Qpo->Transform_GetIn(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecIn);

		Q_Explosion->Explosion[Count].Type = QPOLY_TYPE_TRI;
		Q_Explosion->Explosion[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_Explosion->Explosion[Count].ScaleBIT = 1.0f;


		//if(Q_Explosion->Explosion[Count].GrndShkScale + (75*_->TimeScale) < Q_Explosion->Explosion[Count].ExpSize*285) Q_Explosion->Explosion[Count].GrndShkScale += (75*_->TimeScale);	//+45 500
		//else Q_Explosion->Explosion[Count].GrndShkScale = Q_Explosion->Explosion[Count].ExpSize*285;

		if(Q_Explosion->Explosion[Count].GrndShkScale + (150*_->TimeScale) < Q_Explosion->Explosion[Count].ExpSize*285) Q_Explosion->Explosion[Count].GrndShkScale += (150*_->TimeScale);	//+45 500
		else Q_Explosion->Explosion[Count].GrndShkScale = Q_Explosion->Explosion[Count].ExpSize*285;

		if(Q_Explosion->Explosion[Count].GrndShkScale > Q_Explosion->Explosion[Count].ExpSize*200)
			{
			/*if(Q_Explosion->Explosion[Count].GrndShkAlpha - (10*_->TimeScale) >= 0) Q_Explosion->Explosion[Count].GrndShkAlpha -= (10*_->TimeScale);	//-30
			else
				{
				Q_Explosion->Explosion[Count].GrndShkAlpha = 0;
				Q_Explosion->Explosion[Count].GrndShkLive = 0;
				}*/


			if(Q_Explosion->Explosion[Count].GrndShkAlpha - (50*_->TimeScale) >= 0) Q_Explosion->Explosion[Count].GrndShkAlpha -= (50*_->TimeScale);	//-30
			else
				{
				Q_Explosion->Explosion[Count].GrndShkAlpha = 0;
				Q_Explosion->Explosion[Count].GrndShkLive = 0;
				}
			}


		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, 0.15, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].Pos);//3

		Qpo->Light_SetAttr(Q_Explosion->Explosion[Count].Light, &Q_Explosion->Explosion[Count].Pos, &Q_Explosion->Explosion[Count].LightColor, Q_Explosion->Explosion[Count].AirShkAlpha*20, true);

			//##Flash Vertical##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertFU1);

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU1, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFU1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU1, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFU2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU2, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertFU3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU3, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFU4);


			//##Flash Horizontal##
				//LEFT VERT1
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, -Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertFD1);

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD1, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFD1);


				//LEFT VERT2
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD1, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFD2);


				//RIGHT VERT3
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD2, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertFD3);

				//RIGHT VERT4
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD3, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFD4);
	

			//##Flash Spinner##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertS1);

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS1, Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertS1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS1, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertS2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS2, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertS3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS3, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertS4);

		int a=0;
		while( a <= 2 )
			{
			int b=0;
			while( b <= 3 )
				{
				Q_Explosion->Explosion[Count].Lvert[a][b].a = Q_Explosion->Explosion[Count].GrndShkAlpha;//((rand() % 200) + 15);	//200
				Q_Explosion->Explosion[Count].Lvert[a][b].b = 255;//sunrise;	//100
				Q_Explosion->Explosion[Count].Lvert[a][b].g = 255;//Q_Explosion->Explosion[Count].Lvert[a][b].a;
				Q_Explosion->Explosion[Count].Lvert[a][b].r = 255;//((rand() % 200) + 5);	//100 //180
				b++;
				}
			a++;
			}

		//##Flash Vertical##

		Q_Explosion->Explosion[Count].Lvert[0][0].u = 0;
		Q_Explosion->Explosion[Count].Lvert[0][0].v = 1;
		Q_Explosion->Explosion[Count].Lvert[0][0].x = Q_Explosion->Explosion[Count].VertFU1.x;
		Q_Explosion->Explosion[Count].Lvert[0][0].y = Q_Explosion->Explosion[Count].VertFU1.y;
		Q_Explosion->Explosion[Count].Lvert[0][0].z = Q_Explosion->Explosion[Count].VertFU1.z;

		Q_Explosion->Explosion[Count].Lvert[0][1].u = 1;
		Q_Explosion->Explosion[Count].Lvert[0][1].v = 1;
		Q_Explosion->Explosion[Count].Lvert[0][1].x = Q_Explosion->Explosion[Count].VertFU2.x;
		Q_Explosion->Explosion[Count].Lvert[0][1].y = Q_Explosion->Explosion[Count].VertFU2.y;
		Q_Explosion->Explosion[Count].Lvert[0][1].z = Q_Explosion->Explosion[Count].VertFU2.z;

		Q_Explosion->Explosion[Count].Lvert[0][2].u = 1;
		Q_Explosion->Explosion[Count].Lvert[0][2].v = 0;
		Q_Explosion->Explosion[Count].Lvert[0][2].x = Q_Explosion->Explosion[Count].VertFU3.x;
		Q_Explosion->Explosion[Count].Lvert[0][2].y = Q_Explosion->Explosion[Count].VertFU3.y;
		Q_Explosion->Explosion[Count].Lvert[0][2].z = Q_Explosion->Explosion[Count].VertFU3.z;

		Q_Explosion->Explosion[Count].Lvert[0][3].u = 0;
		Q_Explosion->Explosion[Count].Lvert[0][3].v = 0;
		Q_Explosion->Explosion[Count].Lvert[0][3].x = Q_Explosion->Explosion[Count].VertFU4.x;
		Q_Explosion->Explosion[Count].Lvert[0][3].y = Q_Explosion->Explosion[Count].VertFU4.y;
		Q_Explosion->Explosion[Count].Lvert[0][3].z = Q_Explosion->Explosion[Count].VertFU4.z;



		//##Flash Horizontal##

		Q_Explosion->Explosion[Count].Lvert[1][0].u = 0;
		Q_Explosion->Explosion[Count].Lvert[1][0].v = 1;
		Q_Explosion->Explosion[Count].Lvert[1][0].x = Q_Explosion->Explosion[Count].VertFD1.x;
		Q_Explosion->Explosion[Count].Lvert[1][0].y = Q_Explosion->Explosion[Count].VertFD1.y;
		Q_Explosion->Explosion[Count].Lvert[1][0].z = Q_Explosion->Explosion[Count].VertFD1.z;

		Q_Explosion->Explosion[Count].Lvert[1][1].u = 1;
		Q_Explosion->Explosion[Count].Lvert[1][1].v = 1;
		Q_Explosion->Explosion[Count].Lvert[1][1].x = Q_Explosion->Explosion[Count].VertFD2.x;
		Q_Explosion->Explosion[Count].Lvert[1][1].y = Q_Explosion->Explosion[Count].VertFD2.y;
		Q_Explosion->Explosion[Count].Lvert[1][1].z = Q_Explosion->Explosion[Count].VertFD2.z;

		Q_Explosion->Explosion[Count].Lvert[1][2].u = 1;
		Q_Explosion->Explosion[Count].Lvert[1][2].v = 0;
		Q_Explosion->Explosion[Count].Lvert[1][2].x = Q_Explosion->Explosion[Count].VertFD3.x;
		Q_Explosion->Explosion[Count].Lvert[1][2].y = Q_Explosion->Explosion[Count].VertFD3.y;
		Q_Explosion->Explosion[Count].Lvert[1][2].z = Q_Explosion->Explosion[Count].VertFD3.z;

		Q_Explosion->Explosion[Count].Lvert[1][3].u = 0;
		Q_Explosion->Explosion[Count].Lvert[1][3].v = 0;
		Q_Explosion->Explosion[Count].Lvert[1][3].x = Q_Explosion->Explosion[Count].VertFD4.x;
		Q_Explosion->Explosion[Count].Lvert[1][3].y = Q_Explosion->Explosion[Count].VertFD4.y;
		Q_Explosion->Explosion[Count].Lvert[1][3].z = Q_Explosion->Explosion[Count].VertFD4.z;


		//##Flash Spinner##

		Q_Explosion->Explosion[Count].Lvert[2][0].u = 0;
		Q_Explosion->Explosion[Count].Lvert[2][0].v = 1;
		Q_Explosion->Explosion[Count].Lvert[2][0].x = Q_Explosion->Explosion[Count].VertS1.x;
		Q_Explosion->Explosion[Count].Lvert[2][0].y = Q_Explosion->Explosion[Count].VertS1.y;
		Q_Explosion->Explosion[Count].Lvert[2][0].z = Q_Explosion->Explosion[Count].VertS1.z;
			
		Q_Explosion->Explosion[Count].Lvert[2][1].u = 1;
		Q_Explosion->Explosion[Count].Lvert[2][1].v = 1;
		Q_Explosion->Explosion[Count].Lvert[2][1].x = Q_Explosion->Explosion[Count].VertS2.x;
		Q_Explosion->Explosion[Count].Lvert[2][1].y = Q_Explosion->Explosion[Count].VertS2.y;
		Q_Explosion->Explosion[Count].Lvert[2][1].z = Q_Explosion->Explosion[Count].VertS2.z;
			
		Q_Explosion->Explosion[Count].Lvert[2][2].u = 1;
		Q_Explosion->Explosion[Count].Lvert[2][2].v = 0;
		Q_Explosion->Explosion[Count].Lvert[2][2].x = Q_Explosion->Explosion[Count].VertS3.x;
		Q_Explosion->Explosion[Count].Lvert[2][2].y = Q_Explosion->Explosion[Count].VertS3.y;
		Q_Explosion->Explosion[Count].Lvert[2][2].z = Q_Explosion->Explosion[Count].VertS3.z;

		Q_Explosion->Explosion[Count].Lvert[2][3].u = 0;
		Q_Explosion->Explosion[Count].Lvert[2][3].v = 0;
		Q_Explosion->Explosion[Count].Lvert[2][3].x = Q_Explosion->Explosion[Count].VertS4.x;
		Q_Explosion->Explosion[Count].Lvert[2][3].y = Q_Explosion->Explosion[Count].VertS4.y;
		Q_Explosion->Explosion[Count].Lvert[2][3].z = Q_Explosion->Explosion[Count].VertS4.z;

		//Qpo->Poly_AddOnce(&Q_Explosion->Explosion[Count].Lvert[0][0], 4, Medias->BulHitFlash, Q_Explosion->Explosion[Count].Type, Q_Explosion->Explosion[Count].RenderFlags, Q_Explosion->Explosion[Count].ScaleBIT);
		//Qpo->Poly_AddOnce(&Q_Explosion->Explosion[Count].Lvert[1][0], 4, Medias->BulHitFlash, Q_Explosion->Explosion[Count].Type, Q_Explosion->Explosion[Count].RenderFlags, Q_Explosion->Explosion[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Explosion->Explosion[Count].Lvert[2][0], 4, Medias->EXPexpandro1, Q_Explosion->Explosion[Count].Type, Q_Explosion->Explosion[Count].RenderFlags, Q_Explosion->Explosion[Count].ScaleBIT);
		}
	}


void Q_EFFCon::Explosion_ClientFrame(int Count)
	{
	if(Q_Explosion->Explosion[Count].Init == 0)
		{
		Q_Explosion->Explosion[Count].Init = 1;
		Q_Explosion->Explosion[Count].AirShkLive = 1;
		Q_Explosion->Explosion[Count].GrndShkLive = 1;

		Q_Explosion->Explosion[Count].AirShkScale = 0;
		Q_Explosion->Explosion[Count].AirShkAlpha = 255;
		Q_Explosion->Explosion[Count].GrndShkScale = 0;
		Q_Explosion->Explosion[Count].GrndShkAlpha = 255;
		Q_Explosion->Explosion[Count].BlastAlpha = 255;
		Q_Explosion->Explosion[Count].BlastMat = 0;

		Q_Explosion->Explosion[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_Explosion->Explosion[Count].LightColor.red = 255.0f;
		Q_Explosion->Explosion[Count].LightColor.green = 255.0f;
		Q_Explosion->Explosion[Count].LightColor.blue = 200.0f;
		Q_Explosion->Explosion[Count].LightColor.alpha = 255.0f;

		//Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.m_Alpha = 0;

		jet = 0;
		while(jet < Q_Explosion->Explosion[Count].ExpSize * 4.2)
			{
			Q_BSparks->BSparks[_->NomSparks].Pos = Q_Explosion->Explosion[Count].Pos;

			Q_BSparks->BSparks[_->NomSparks].TraVec = Q_Explosion->Explosion[Count].CollPlaneNormal;

			Q_BSparks->BSparks[_->NomSparks].TraVec.x += ((((float)rand() / 32767)-0.5))*4;
			Q_BSparks->BSparks[_->NomSparks].TraVec.y += (((((float)rand() / 32767)-0.5))+1.5);
			Q_BSparks->BSparks[_->NomSparks].TraVec.z += ((((float)rand() / 32767)-0.5))*4;

			Q_BSparks->BSparks[_->NomSparks].AlpFade = 255;
			Q_BSparks->BSparks[_->NomSparks].Timer = 0;
			Q_BSparks->BSparks[_->NomSparks].TimerGoal = ((((float)rand() / 32767)*2000)+500);

			Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[_->NomSparks].Pos, 1, &Q_BSparks->BSparks[_->NomSparks].TraVec, &Q_BSparks->BSparks[_->NomSparks].Pos);

			Q_BSparks->BSparks[_->NomSparks].Speed = 8;
			Q_BSparks->BSparks[_->NomSparks].Gravity = 0.1;

			Q_BSparks->BSparks[_->NomSparks].Bounce = 0;

			Q_BSparks->BSparks[_->NomSparks].SmokeTrail = 1;
			Q_BSparks->BSparks[_->NomSparks].Live = 1;

			_->NomSparks++;
			if(_->NomSparks > 499) _->NomSparks = 0;
			jet++;
			}

		//player[g_Player]->CameraShake = 2;
		//player[g_Player]->CamShkTIME = 6;

		aero = 0;
		while(aero < 14)
			{
			Q_Cloud->Cloud[_->NomCloud].CloudType = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Explosion->Explosion[Count].Pos;
			
			Q_Cloud->Cloud[_->NomCloud].CloudPos.x += (((float)rand() / 32767)-0.5)*200;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.y += (((float)rand() / 32767)-0.5)*200;
			Q_Cloud->Cloud[_->NomCloud].CloudPos.z += (((float)rand() / 32767)-0.5)*200;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*85)+170;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.6;

			Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += (((float)rand() / 32767)-0.5)*2;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*2;

			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)-0.5)*5;

			Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
			aero++;
			}

		Qpo->Collision_Make_DMG_Blast_Mask(BiVector(Q_Explosion->Explosion[Count].Pos.x, Q_Explosion->Explosion[Count].Pos.y, Q_Explosion->Explosion[Count].Pos.z), Q_Explosion->Explosion[Count].ExpDMG, max(1.17f - (((Q_Explosion->Explosion[Count].ExpDMG * Q_Explosion->Explosion[Count].ExpSize) + 0.17f) / 14.0f), 0.01f), Q_Explosion->Explosion[Count].ExpSize / 13.5f); //swk

		Qpo->Sound_Play(Medias->S_Explosion, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Explosion->Explosion[Count].Pos);
		}


	//###Air Shockwave
	if(Q_Explosion->Explosion[Count].AirShkLive == 1)
		{
		Qpo->Vec3d_Copy(&Q_Explosion->Explosion[Count].Pos, &Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Xform.Translation);
		//Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, Q_Explosion->Explosion[Count].AirShkScale,Q_Explosion->Explosion[Count].AirShkScale,Q_Explosion->Explosion[Count].AirShkScale);
		//Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, Q_Explosion->Explosion[Count].AirShkAlpha);

		if(Q_Explosion->Explosion[Count].AirShkScale + (0.7*_->TimeScale) < Q_Explosion->Explosion[Count].ExpSize) Q_Explosion->Explosion[Count].AirShkScale += 0.7*_->TimeScale;	//Perfectly parrallel with expandro is +0.1 here and +15 expandro
		else
			{
			Q_Explosion->Explosion[Count].AirShkScale = Q_Explosion->Explosion[Count].ExpSize;
			Q_Explosion->Explosion[Count].AirShkScale += ((((float)rand() / 32767)-0.5)*0.2)*_->TimeScale;
			}

		if(Q_Explosion->Explosion[Count].AirShkScale > Q_Explosion->Explosion[Count].ExpSize/1.4)
			{
			if(Q_Explosion->Explosion[Count].AirShkAlpha - (35*_->TimeScale) > 0) Q_Explosion->Explosion[Count].AirShkAlpha -= 35*_->TimeScale;	//-50
			else
				{
				Q_Explosion->Explosion[Count].AirShkAlpha = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall.Xform.Translation);
				//Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[Q_Explosion->Explosion[Count].LargeEnergyAvID].EnergyBall, 0,0,0);
				Q_Explosion->Explosion[Count].AirShkLive = 0;
				Qpo->Light_Remove(Q_Explosion->Explosion[Count].Light);
				Q_Explosion->Explosion[Count].Live = 0;

				/*//### Array Reorder
				K = Count;
				while(K < _->NomExplosions - 1)
					{
					Q_Explosion->Explosion[K] = Q_Explosion->Explosion[K+1];
					K++;
					}

				_->NomExplosions--;*/
				}
			}

		Qpo->Light_SetAttr(Q_Explosion->Explosion[Count].Light, &Q_Explosion->Explosion[Count].Pos, &Q_Explosion->Explosion[Count].LightColor, Q_Explosion->Explosion[Count].AirShkAlpha * 350, true);

		if(Q_Explosion->Explosion[Count].BmpCountSP - 1 > 0) Q_Explosion->Explosion[Count].BmpCountSP--;
		else
			{
			Q_Explosion->Explosion[Count].BmpCountSP = 6;
			if(Q_Explosion->Explosion[Count].BmpCount + 1 < 14) Q_Explosion->Explosion[Count].BmpCount++;	//18
			else Q_Explosion->Explosion[Count].BmpCount = 0;
			}
		}


	//###Ground Shockwave
	if(Q_Explosion->Explosion[Count].GrndShkLive == 1 && 0)
		{
		Qpo->Transform_New(&Q_Explosion->Explosion[Count].AlignMatrix);	//OPTIMISE Calculate once only
		Qpo->Transform_GetIn(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].AligIn);
		//Q_Explosion->Explosion[Count].VecIn = Q_Explosion->Explosion[Count].Collision->Plane.Normal;
		//EDIT
		Q_Explosion->Explosion[Count].VecIn.x = 0;
		Q_Explosion->Explosion[Count].VecIn.y = 1;
		Q_Explosion->Explosion[Count].VecIn.z = 0;

		if(Q_Explosion->Explosion[Count].VecIn.x == 0 && Q_Explosion->Explosion[Count].VecIn.z == 0)
			{
			Q_Explosion->Explosion[Count].VecLeft.x = -1;
			Q_Explosion->Explosion[Count].VecLeft.y = 0;
			Q_Explosion->Explosion[Count].VecLeft.z = 0;
			}
		else
			{
			Qpo->Transform_New_YRotation(&rotmat, PI/2);
			Qpo->Transform_RotateVector(&rotmat, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VecLeft);
			Q_Explosion->Explosion[Count].VecLeft.y = 0;
			}
		Qpo->Vec3d_CrossProduct(&Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VecUp);
		Qpo->Transform_New_LeftUpIn(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VecIn);
		Q_Explosion->Explosion[Count].AlignMatrix.Translation = Q_Explosion->Explosion[Count].Pos;
		Qpo->Transform_New_ZRotation(&rotmat, (((float)rand() / 32767)*6)*_->TimeScale);
		Qpo->Transform_Multiply(&Q_Explosion->Explosion[Count].AlignMatrix, &rotmat, &Q_Explosion->Explosion[Count].AlignMatrix);
		Qpo->Transform_GetUp(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecUp);
		Qpo->Transform_GetLeft(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecLeft);
		Qpo->Transform_GetIn(&Q_Explosion->Explosion[Count].AlignMatrix, &Q_Explosion->Explosion[Count].VecIn);

		Q_Explosion->Explosion[Count].Type = QPOLY_TYPE_TRI;
		Q_Explosion->Explosion[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_Explosion->Explosion[Count].ScaleBIT = 1.0f;

		if(Q_Explosion->Explosion[Count].GrndShkScale + (150*_->TimeScale) < Q_Explosion->Explosion[Count].ExpSize*285) Q_Explosion->Explosion[Count].GrndShkScale += (150*_->TimeScale);	//+45 500
		else Q_Explosion->Explosion[Count].GrndShkScale = Q_Explosion->Explosion[Count].ExpSize*285;

		if(Q_Explosion->Explosion[Count].GrndShkScale > Q_Explosion->Explosion[Count].ExpSize*200)
			{
			if(Q_Explosion->Explosion[Count].GrndShkAlpha - (50*_->TimeScale) >= 0) Q_Explosion->Explosion[Count].GrndShkAlpha -= (50*_->TimeScale);	//-30
			else
				{
				Q_Explosion->Explosion[Count].GrndShkAlpha = 0;
				Q_Explosion->Explosion[Count].GrndShkLive = 0;
				}
			}

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, 0.15, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].Pos);//3

		Qpo->Light_SetAttr(Q_Explosion->Explosion[Count].Light, &Q_Explosion->Explosion[Count].Pos, &Q_Explosion->Explosion[Count].LightColor, Q_Explosion->Explosion[Count].AirShkAlpha*20, true);

			//##Flash Vertical##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertFU1);

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU1, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFU1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU1, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFU2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU2, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertFU3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFU3, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFU4);


			//##Flash Horizontal##
				//LEFT VERT1
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, -Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertFD1);

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD1, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFD1);


				//LEFT VERT2
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD1, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFD2);


				//RIGHT VERT3
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD2, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertFD3);

				//RIGHT VERT4
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertFD3, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecIn, &Q_Explosion->Explosion[Count].VertFD4);
	

			//##Flash Spinner##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].Pos, Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertS1);

		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS1, Q_Explosion->Explosion[Count].GrndShkScale/2, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertS1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS1, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertS2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS2, -Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecUp, &Q_Explosion->Explosion[Count].VertS3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_Explosion->Explosion[Count].VertS3, Q_Explosion->Explosion[Count].GrndShkScale, &Q_Explosion->Explosion[Count].VecLeft, &Q_Explosion->Explosion[Count].VertS4);

		int a = 0;
		while( a <= 2 )
			{
			int b = 0;
			while( b <= 3 )
				{
				Q_Explosion->Explosion[Count].Lvert[a][b].a = Q_Explosion->Explosion[Count].GrndShkAlpha;//((rand() % 200) + 15);	//200
				Q_Explosion->Explosion[Count].Lvert[a][b].b = 255;//sunrise;	//100
				Q_Explosion->Explosion[Count].Lvert[a][b].g = 255;//Q_Explosion->Explosion[Count].Lvert[a][b].a;
				Q_Explosion->Explosion[Count].Lvert[a][b].r = 255;//((rand() % 200) + 5);	//100 //180

				b++;
				}

			a++;
			}

		//## Flash Vertical ##

		Q_Explosion->Explosion[Count].Lvert[0][0].u = 0;
		Q_Explosion->Explosion[Count].Lvert[0][0].v = 1;
		Q_Explosion->Explosion[Count].Lvert[0][0].x = Q_Explosion->Explosion[Count].VertFU1.x;
		Q_Explosion->Explosion[Count].Lvert[0][0].y = Q_Explosion->Explosion[Count].VertFU1.y;
		Q_Explosion->Explosion[Count].Lvert[0][0].z = Q_Explosion->Explosion[Count].VertFU1.z;

		Q_Explosion->Explosion[Count].Lvert[0][1].u = 1;
		Q_Explosion->Explosion[Count].Lvert[0][1].v = 1;
		Q_Explosion->Explosion[Count].Lvert[0][1].x = Q_Explosion->Explosion[Count].VertFU2.x;
		Q_Explosion->Explosion[Count].Lvert[0][1].y = Q_Explosion->Explosion[Count].VertFU2.y;
		Q_Explosion->Explosion[Count].Lvert[0][1].z = Q_Explosion->Explosion[Count].VertFU2.z;

		Q_Explosion->Explosion[Count].Lvert[0][2].u = 1;
		Q_Explosion->Explosion[Count].Lvert[0][2].v = 0;
		Q_Explosion->Explosion[Count].Lvert[0][2].x = Q_Explosion->Explosion[Count].VertFU3.x;
		Q_Explosion->Explosion[Count].Lvert[0][2].y = Q_Explosion->Explosion[Count].VertFU3.y;
		Q_Explosion->Explosion[Count].Lvert[0][2].z = Q_Explosion->Explosion[Count].VertFU3.z;

		Q_Explosion->Explosion[Count].Lvert[0][3].u = 0;
		Q_Explosion->Explosion[Count].Lvert[0][3].v = 0;
		Q_Explosion->Explosion[Count].Lvert[0][3].x = Q_Explosion->Explosion[Count].VertFU4.x;
		Q_Explosion->Explosion[Count].Lvert[0][3].y = Q_Explosion->Explosion[Count].VertFU4.y;
		Q_Explosion->Explosion[Count].Lvert[0][3].z = Q_Explosion->Explosion[Count].VertFU4.z;



		//##Flash Horizontal##

		Q_Explosion->Explosion[Count].Lvert[1][0].u = 0;
		Q_Explosion->Explosion[Count].Lvert[1][0].v = 1;
		Q_Explosion->Explosion[Count].Lvert[1][0].x = Q_Explosion->Explosion[Count].VertFD1.x;
		Q_Explosion->Explosion[Count].Lvert[1][0].y = Q_Explosion->Explosion[Count].VertFD1.y;
		Q_Explosion->Explosion[Count].Lvert[1][0].z = Q_Explosion->Explosion[Count].VertFD1.z;

		Q_Explosion->Explosion[Count].Lvert[1][1].u = 1;
		Q_Explosion->Explosion[Count].Lvert[1][1].v = 1;
		Q_Explosion->Explosion[Count].Lvert[1][1].x = Q_Explosion->Explosion[Count].VertFD2.x;
		Q_Explosion->Explosion[Count].Lvert[1][1].y = Q_Explosion->Explosion[Count].VertFD2.y;
		Q_Explosion->Explosion[Count].Lvert[1][1].z = Q_Explosion->Explosion[Count].VertFD2.z;

		Q_Explosion->Explosion[Count].Lvert[1][2].u = 1;
		Q_Explosion->Explosion[Count].Lvert[1][2].v = 0;
		Q_Explosion->Explosion[Count].Lvert[1][2].x = Q_Explosion->Explosion[Count].VertFD3.x;
		Q_Explosion->Explosion[Count].Lvert[1][2].y = Q_Explosion->Explosion[Count].VertFD3.y;
		Q_Explosion->Explosion[Count].Lvert[1][2].z = Q_Explosion->Explosion[Count].VertFD3.z;

		Q_Explosion->Explosion[Count].Lvert[1][3].u = 0;
		Q_Explosion->Explosion[Count].Lvert[1][3].v = 0;
		Q_Explosion->Explosion[Count].Lvert[1][3].x = Q_Explosion->Explosion[Count].VertFD4.x;
		Q_Explosion->Explosion[Count].Lvert[1][3].y = Q_Explosion->Explosion[Count].VertFD4.y;
		Q_Explosion->Explosion[Count].Lvert[1][3].z = Q_Explosion->Explosion[Count].VertFD4.z;


		//##Flash Spinner##

		Q_Explosion->Explosion[Count].Lvert[2][0].u = 0;
		Q_Explosion->Explosion[Count].Lvert[2][0].v = 1;
		Q_Explosion->Explosion[Count].Lvert[2][0].x = Q_Explosion->Explosion[Count].VertS1.x;
		Q_Explosion->Explosion[Count].Lvert[2][0].y = Q_Explosion->Explosion[Count].VertS1.y;
		Q_Explosion->Explosion[Count].Lvert[2][0].z = Q_Explosion->Explosion[Count].VertS1.z;

		Q_Explosion->Explosion[Count].Lvert[2][1].u = 1;
		Q_Explosion->Explosion[Count].Lvert[2][1].v = 1;
		Q_Explosion->Explosion[Count].Lvert[2][1].x = Q_Explosion->Explosion[Count].VertS2.x;
		Q_Explosion->Explosion[Count].Lvert[2][1].y = Q_Explosion->Explosion[Count].VertS2.y;
		Q_Explosion->Explosion[Count].Lvert[2][1].z = Q_Explosion->Explosion[Count].VertS2.z;

		Q_Explosion->Explosion[Count].Lvert[2][2].u = 1;
		Q_Explosion->Explosion[Count].Lvert[2][2].v = 0;
		Q_Explosion->Explosion[Count].Lvert[2][2].x = Q_Explosion->Explosion[Count].VertS3.x;
		Q_Explosion->Explosion[Count].Lvert[2][2].y = Q_Explosion->Explosion[Count].VertS3.y;
		Q_Explosion->Explosion[Count].Lvert[2][2].z = Q_Explosion->Explosion[Count].VertS3.z;

		Q_Explosion->Explosion[Count].Lvert[2][3].u = 0;
		Q_Explosion->Explosion[Count].Lvert[2][3].v = 0;
		Q_Explosion->Explosion[Count].Lvert[2][3].x = Q_Explosion->Explosion[Count].VertS4.x;
		Q_Explosion->Explosion[Count].Lvert[2][3].y = Q_Explosion->Explosion[Count].VertS4.y;
		Q_Explosion->Explosion[Count].Lvert[2][3].z = Q_Explosion->Explosion[Count].VertS4.z;

		//Qpo->Poly_AddOnce(&Q_Explosion->Explosion[Count].Lvert[0][0], 4, Medias->BulHitFlash, Q_Explosion->Explosion[Count].Type, Q_Explosion->Explosion[Count].RenderFlags, Q_Explosion->Explosion[Count].ScaleBIT);
		//Qpo->Poly_AddOnce(&Q_Explosion->Explosion[Count].Lvert[1][0], 4, Medias->BulHitFlash, Q_Explosion->Explosion[Count].Type, Q_Explosion->Explosion[Count].RenderFlags, Q_Explosion->Explosion[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Explosion->Explosion[Count].Lvert[2][0], 4, Medias->EXPexpandro1, Q_Explosion->Explosion[Count].Type, Q_Explosion->Explosion[Count].RenderFlags, Q_Explosion->Explosion[Count].ScaleBIT);
		}
	}

};