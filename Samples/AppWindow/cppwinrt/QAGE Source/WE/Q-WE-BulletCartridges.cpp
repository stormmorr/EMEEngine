/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Bullet Cartridges-

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
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-BulletSystem.h"

using namespace GVARS;

namespace GVARS
{

	//########- Cartridges -########

void Q_EFFCon::Cartridge_ControlFrame(int Count)
	{
	if(Q_Cartridge->Cartridge[Count].Live == 1) //MOVEMENT
		{
		//Apply Gravity
		Q_Cartridge->Cartridge[Count].TrajVec.y -= (Q_Cartridge->Cartridge[Count].Gravity / 25)*_->TimeScale;

		Q_Cartridge->Cartridge[Count].OldPos = Q_Cartridge->Cartridge[Count].WorldPos;
		
		//Move
		Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].WorldPos, Q_Cartridge->Cartridge[Count].Speed*_->TimeScale*5/*0.003*/, &Q_Cartridge->Cartridge[Count].TrajVec, &Q_Cartridge->Cartridge[Count].WorldPos);

		Qpo->Transform_New_XRotation(&rotmat, Q_Cartridge->Cartridge[Count].XSpin*_->TimeScale);
		Qpo->Transform_Multiply(&Q_Cartridge->Cartridge[Count].AlignMatrix, &rotmat, &Q_Cartridge->Cartridge[Count].AlignMatrix);

		Qpo->Transform_New_YRotation(&rotmat, Q_Cartridge->Cartridge[Count].YSpin*_->TimeScale);
		Qpo->Transform_Multiply(&Q_Cartridge->Cartridge[Count].AlignMatrix, &rotmat, &Q_Cartridge->Cartridge[Count].AlignMatrix);

		Qpo->Transform_New_ZRotation(&rotmat, Q_Cartridge->Cartridge[Count].ZSpin*_->TimeScale);
		Qpo->Transform_Multiply(&Q_Cartridge->Cartridge[Count].AlignMatrix, &rotmat, &Q_Cartridge->Cartridge[Count].AlignMatrix);

		if(Qpo->Collision_RayTest_Avatar(
			 &CartMins,
			 &CartMaxs,
			 &Q_Cartridge->Cartridge[Count].OldPos,
			 &Q_Cartridge->Cartridge[Count].WorldPos,
			 0xffffffff, NULL, NULL,
			 &Q_Cartridge->Cartridge[Count].Collision, Q_Cartridge->Cartridge[Count].AvID))
			{
			if(Q_Cartridge->Cartridge[Count].FloorBounce == 0)
				{
				Q_Cartridge->Cartridge[Count].WorldPos = Q_Cartridge->Cartridge[Count].OldPos;
				Q_Cartridge->Cartridge[Count].TrajVec = Q.PHY_BounceVector(Q_Cartridge->Cartridge[Count].TrajVec, Q_Cartridge->Cartridge[Count].Collision.Plane.Normal);
				Q_Cartridge->Cartridge[Count].Gravity = Q_Cartridge->Cartridge[Count].Gravity * 2;
				Q_Cartridge->Cartridge[Count].FloorBounce = 1;
				}
			else
				{
				Q_Cartridge->Cartridge[Count].WorldPos.acSet(Q_Cartridge->Cartridge[Count].Collision.Impact.m_X, Q_Cartridge->Cartridge[Count].Collision.Impact.m_Y, Q_Cartridge->Cartridge[Count].Collision.Impact.m_Z);
				Q_Cartridge->Cartridge[Count].Live = 0;
				}
			}
		}	//END MOVEMENT


	Q_Cartridge->Cartridge[Count].AlignMatrix.Translation = Q_Cartridge->Cartridge[Count].WorldPos;

	Q_Cartridge->Cartridge[Count].Pos = Q_Cartridge->Cartridge[Count].AlignMatrix.Translation;


	Qpo->Transform_GetUp(&Q_Cartridge->Cartridge[Count].AlignMatrix, &Q_Cartridge->Cartridge[Count].VecUp);
	Qpo->Transform_GetLeft(&Q_Cartridge->Cartridge[Count].AlignMatrix, &Q_Cartridge->Cartridge[Count].VecLeft);
	Qpo->Transform_GetIn(&Q_Cartridge->Cartridge[Count].AlignMatrix, &Q_Cartridge->Cartridge[Count].VecIn);

	//DRAW CARTRIDGE

	//Q_Cartridge->Cartridge[Count].Bitmap = Medias->jinko;	//Medias->expandro1; //Medias->cart1; //Medias->trail2
	Q_Cartridge->Cartridge[Count].Type = QPOLY_TYPE_TRI; //QPOLY_TYPE_GOR;		//QPOLY_TYPE_TRI; //QPOLY_TYPE_GOR;
	Q_Cartridge->Cartridge[Count].RenderFlags = QPOLY_REND_DEPTH_SORT;
	Q_Cartridge->Cartridge[Count].ScaleBIT = 1.0f;

	//Compensate for pivot
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, -Q_Cartridge->Cartridge[Count].Scale*2, &Q_Cartridge->Cartridge[Count].VecIn, &Q_Cartridge->Cartridge[Count].Pos);	//1.1

	//##Back Verts##
			//BACK VERT1
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, Q_Cartridge->Cartridge[Count].Scale/1.105, &Q_Cartridge->Cartridge[Count].VecUp, &Q_Cartridge->Cartridge[Count].VertB1);	//1.1

			//BACK VERT2
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, Q_Cartridge->Cartridge[Count].Scale/6, &Q_Cartridge->Cartridge[Count].VecUp, &Q_Cartridge->Cartridge[Count].VertB2);

	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertB2, -Q_Cartridge->Cartridge[Count].Scale*0.89, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertB2);

	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, -Q_Cartridge->Cartridge[Count].Scale, &Q_Cartridge->Cartridge[Count].VecUp, &Q_Cartridge->Cartridge[Count].VertB3);

			//BACK VERT4
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertB3, Q_Cartridge->Cartridge[Count].Scale/1.62, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertB4);	//1.75

			//BACK VERT3
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertB3, -Q_Cartridge->Cartridge[Count].Scale/1.62, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertB3);

			//BACK VERT5
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertB2, (Q_Cartridge->Cartridge[Count].Scale*2)*0.89, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertB5);


	//OTF FIX
	Qpo->Vec3d_Subtract(&Q_Cartridge->Cartridge[Count].VertB3, &Q_Cartridge->Cartridge[Count].Pos, &Q_Cartridge->Cartridge[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertB3, -0.23, &Q_Cartridge->Cartridge[Count].VecSTR, &Q_Cartridge->Cartridge[Count].VertB3);	//0.2106
	Qpo->Vec3d_Subtract(&Q_Cartridge->Cartridge[Count].VertB4, &Q_Cartridge->Cartridge[Count].Pos, &Q_Cartridge->Cartridge[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertB4, -0.23, &Q_Cartridge->Cartridge[Count].VecSTR, &Q_Cartridge->Cartridge[Count].VertB4);


	//##Front Verts##
			//FRONT VERT1
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, Q_Cartridge->Cartridge[Count].Scale*4, &Q_Cartridge->Cartridge[Count].VecIn, &Q_Cartridge->Cartridge[Count].Pos);

	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, Q_Cartridge->Cartridge[Count].Scale/1.105, &Q_Cartridge->Cartridge[Count].VecUp, &Q_Cartridge->Cartridge[Count].VertF1);	//1.1

			//FRONT VERT2
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, Q_Cartridge->Cartridge[Count].Scale/6, &Q_Cartridge->Cartridge[Count].VecUp, &Q_Cartridge->Cartridge[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertF2, -Q_Cartridge->Cartridge[Count].Scale*0.89, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, -Q_Cartridge->Cartridge[Count].Scale, &Q_Cartridge->Cartridge[Count].VecUp, &Q_Cartridge->Cartridge[Count].VertF3);

			//FRONT VERT4
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertF3, Q_Cartridge->Cartridge[Count].Scale/1.62, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertF4);	//1.75

			//FRONT VERT3
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertF3, -Q_Cartridge->Cartridge[Count].Scale/1.62, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertF3);

			//FRONT VERT5
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertF2, (Q_Cartridge->Cartridge[Count].Scale*2)*0.89, &Q_Cartridge->Cartridge[Count].VecLeft, &Q_Cartridge->Cartridge[Count].VertF5);


	Qpo->Vec3d_Subtract(&Q_Cartridge->Cartridge[Count].VertF3, &Q_Cartridge->Cartridge[Count].Pos, &Q_Cartridge->Cartridge[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertF3, -0.23, &Q_Cartridge->Cartridge[Count].VecSTR, &Q_Cartridge->Cartridge[Count].VertF3);	//0.2106
	Qpo->Vec3d_Subtract(&Q_Cartridge->Cartridge[Count].VertF4, &Q_Cartridge->Cartridge[Count].Pos, &Q_Cartridge->Cartridge[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].VertF4, -0.23, &Q_Cartridge->Cartridge[Count].VecSTR, &Q_Cartridge->Cartridge[Count].VertF4);


	//##Front Point##
			//FRONT POINT
	Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[Count].Pos, Q_Cartridge->Cartridge[Count].Scale*2.67, &Q_Cartridge->Cartridge[Count].VecIn, &Q_Cartridge->Cartridge[Count].VertFP);


	int a=0;
	while( a <= 12 )
		{
		int b=0;
		while( b <= 3 )
			{
			Q_Cartridge->Cartridge[Count].Lvert[a][b].a = 255;//((rand() % 200) + 15);	//200
			Q_Cartridge->Cartridge[Count].Lvert[a][b].b = 80;//sunrise;	//100
			Q_Cartridge->Cartridge[Count].Lvert[a][b].g = 160;//Q_Cartridge->Cartridge[Count].Lvert[a][b].a;
			Q_Cartridge->Cartridge[Count].Lvert[a][b].r = 160;//((rand() % 200) + 5);	//100 //180
			b++;
			}
		a++;
		}

	a=3;
	while( a <= 7 )
		{
		int b=0;
		while( b <= 1 )
			{
			Q_Cartridge->Cartridge[Count].Lvert[a][b].a = 255;//((rand() % 200) + 15);	//200
			Q_Cartridge->Cartridge[Count].Lvert[a][b].b = 20;//sunrise;	//100
			Q_Cartridge->Cartridge[Count].Lvert[a][b].g = 90;//Q_Cartridge->Cartridge[Count].Lvert[a][b].a;
			Q_Cartridge->Cartridge[Count].Lvert[a][b].r = 90;//((rand() % 200) + 5);	//100 //180
			b++;
			}
		a++;
		}


	//## Back Tris ##

	Q_Cartridge->Cartridge[Count].Lvert[0][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[0][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[0][0].x = Q_Cartridge->Cartridge[Count].VertB1.x;
	Q_Cartridge->Cartridge[Count].Lvert[0][0].y = Q_Cartridge->Cartridge[Count].VertB1.y;
	Q_Cartridge->Cartridge[Count].Lvert[0][0].z = Q_Cartridge->Cartridge[Count].VertB1.z;
	Q_Cartridge->Cartridge[Count].Lvert[0][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[0][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[0][1].x = Q_Cartridge->Cartridge[Count].VertB2.x;
	Q_Cartridge->Cartridge[Count].Lvert[0][1].y = Q_Cartridge->Cartridge[Count].VertB2.y;
	Q_Cartridge->Cartridge[Count].Lvert[0][1].z = Q_Cartridge->Cartridge[Count].VertB2.z;
	Q_Cartridge->Cartridge[Count].Lvert[0][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[0][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[0][2].x = Q_Cartridge->Cartridge[Count].VertB3.x;
	Q_Cartridge->Cartridge[Count].Lvert[0][2].y = Q_Cartridge->Cartridge[Count].VertB3.y;
	Q_Cartridge->Cartridge[Count].Lvert[0][2].z = Q_Cartridge->Cartridge[Count].VertB3.z;


	Q_Cartridge->Cartridge[Count].Lvert[1][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[1][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[1][0].x = Q_Cartridge->Cartridge[Count].VertB3.x;
	Q_Cartridge->Cartridge[Count].Lvert[1][0].y = Q_Cartridge->Cartridge[Count].VertB3.y;
	Q_Cartridge->Cartridge[Count].Lvert[1][0].z = Q_Cartridge->Cartridge[Count].VertB3.z;
	Q_Cartridge->Cartridge[Count].Lvert[1][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[1][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[1][1].x = Q_Cartridge->Cartridge[Count].VertB4.x;
	Q_Cartridge->Cartridge[Count].Lvert[1][1].y = Q_Cartridge->Cartridge[Count].VertB4.y;
	Q_Cartridge->Cartridge[Count].Lvert[1][1].z = Q_Cartridge->Cartridge[Count].VertB4.z;
	Q_Cartridge->Cartridge[Count].Lvert[1][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[1][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[1][2].x = Q_Cartridge->Cartridge[Count].VertB1.x;
	Q_Cartridge->Cartridge[Count].Lvert[1][2].y = Q_Cartridge->Cartridge[Count].VertB1.y;
	Q_Cartridge->Cartridge[Count].Lvert[1][2].z = Q_Cartridge->Cartridge[Count].VertB1.z;


	Q_Cartridge->Cartridge[Count].Lvert[2][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[2][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[2][0].x = Q_Cartridge->Cartridge[Count].VertB4.x;
	Q_Cartridge->Cartridge[Count].Lvert[2][0].y = Q_Cartridge->Cartridge[Count].VertB4.y;
	Q_Cartridge->Cartridge[Count].Lvert[2][0].z = Q_Cartridge->Cartridge[Count].VertB4.z;
	Q_Cartridge->Cartridge[Count].Lvert[2][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[2][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[2][1].x = Q_Cartridge->Cartridge[Count].VertB5.x;
	Q_Cartridge->Cartridge[Count].Lvert[2][1].y = Q_Cartridge->Cartridge[Count].VertB5.y;
	Q_Cartridge->Cartridge[Count].Lvert[2][1].z = Q_Cartridge->Cartridge[Count].VertB5.z;
	Q_Cartridge->Cartridge[Count].Lvert[2][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[2][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[2][2].x = Q_Cartridge->Cartridge[Count].VertB1.x;
	Q_Cartridge->Cartridge[Count].Lvert[2][2].y = Q_Cartridge->Cartridge[Count].VertB1.y;
	Q_Cartridge->Cartridge[Count].Lvert[2][2].z = Q_Cartridge->Cartridge[Count].VertB1.z;


	//## Side Strips ##

	//Strip1
	Q_Cartridge->Cartridge[Count].Lvert[3][0].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[3][0].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[3][0].x = Q_Cartridge->Cartridge[Count].VertB1.x;
	Q_Cartridge->Cartridge[Count].Lvert[3][0].y = Q_Cartridge->Cartridge[Count].VertB1.y;
	Q_Cartridge->Cartridge[Count].Lvert[3][0].z = Q_Cartridge->Cartridge[Count].VertB1.z;
	Q_Cartridge->Cartridge[Count].Lvert[3][1].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[3][1].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[3][1].x = Q_Cartridge->Cartridge[Count].VertB2.x;
	Q_Cartridge->Cartridge[Count].Lvert[3][1].y = Q_Cartridge->Cartridge[Count].VertB2.y;
	Q_Cartridge->Cartridge[Count].Lvert[3][1].z = Q_Cartridge->Cartridge[Count].VertB2.z;
	Q_Cartridge->Cartridge[Count].Lvert[3][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[3][2].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[3][2].x = Q_Cartridge->Cartridge[Count].VertF2.x;
	Q_Cartridge->Cartridge[Count].Lvert[3][2].y = Q_Cartridge->Cartridge[Count].VertF2.y;
	Q_Cartridge->Cartridge[Count].Lvert[3][2].z = Q_Cartridge->Cartridge[Count].VertF2.z;
	Q_Cartridge->Cartridge[Count].Lvert[3][3].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[3][3].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[3][3].x = Q_Cartridge->Cartridge[Count].VertF1.x;
	Q_Cartridge->Cartridge[Count].Lvert[3][3].y = Q_Cartridge->Cartridge[Count].VertF1.y;
	Q_Cartridge->Cartridge[Count].Lvert[3][3].z = Q_Cartridge->Cartridge[Count].VertF1.z;


	//Strip2
	Q_Cartridge->Cartridge[Count].Lvert[4][0].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[4][0].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[4][0].x = Q_Cartridge->Cartridge[Count].VertB2.x;
	Q_Cartridge->Cartridge[Count].Lvert[4][0].y = Q_Cartridge->Cartridge[Count].VertB2.y;
	Q_Cartridge->Cartridge[Count].Lvert[4][0].z = Q_Cartridge->Cartridge[Count].VertB2.z;
	Q_Cartridge->Cartridge[Count].Lvert[4][1].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[4][1].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[4][1].x = Q_Cartridge->Cartridge[Count].VertB3.x;
	Q_Cartridge->Cartridge[Count].Lvert[4][1].y = Q_Cartridge->Cartridge[Count].VertB3.y;
	Q_Cartridge->Cartridge[Count].Lvert[4][1].z = Q_Cartridge->Cartridge[Count].VertB3.z;
	Q_Cartridge->Cartridge[Count].Lvert[4][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[4][2].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[4][2].x = Q_Cartridge->Cartridge[Count].VertF3.x;
	Q_Cartridge->Cartridge[Count].Lvert[4][2].y = Q_Cartridge->Cartridge[Count].VertF3.y;
	Q_Cartridge->Cartridge[Count].Lvert[4][2].z = Q_Cartridge->Cartridge[Count].VertF3.z;
	Q_Cartridge->Cartridge[Count].Lvert[4][3].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[4][3].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[4][3].x = Q_Cartridge->Cartridge[Count].VertF2.x;
	Q_Cartridge->Cartridge[Count].Lvert[4][3].y = Q_Cartridge->Cartridge[Count].VertF2.y;
	Q_Cartridge->Cartridge[Count].Lvert[4][3].z = Q_Cartridge->Cartridge[Count].VertF2.z;


	//Strip3
	Q_Cartridge->Cartridge[Count].Lvert[5][0].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[5][0].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[5][0].x = Q_Cartridge->Cartridge[Count].VertB3.x;
	Q_Cartridge->Cartridge[Count].Lvert[5][0].y = Q_Cartridge->Cartridge[Count].VertB3.y;
	Q_Cartridge->Cartridge[Count].Lvert[5][0].z = Q_Cartridge->Cartridge[Count].VertB3.z;
	Q_Cartridge->Cartridge[Count].Lvert[5][1].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[5][1].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[5][1].x = Q_Cartridge->Cartridge[Count].VertB4.x;
	Q_Cartridge->Cartridge[Count].Lvert[5][1].y = Q_Cartridge->Cartridge[Count].VertB4.y;
	Q_Cartridge->Cartridge[Count].Lvert[5][1].z = Q_Cartridge->Cartridge[Count].VertB4.z;
	Q_Cartridge->Cartridge[Count].Lvert[5][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[5][2].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[5][2].x = Q_Cartridge->Cartridge[Count].VertF4.x;
	Q_Cartridge->Cartridge[Count].Lvert[5][2].y = Q_Cartridge->Cartridge[Count].VertF4.y;
	Q_Cartridge->Cartridge[Count].Lvert[5][2].z = Q_Cartridge->Cartridge[Count].VertF4.z;
	Q_Cartridge->Cartridge[Count].Lvert[5][3].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[5][3].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[5][3].x = Q_Cartridge->Cartridge[Count].VertF3.x;
	Q_Cartridge->Cartridge[Count].Lvert[5][3].y = Q_Cartridge->Cartridge[Count].VertF3.y;
	Q_Cartridge->Cartridge[Count].Lvert[5][3].z = Q_Cartridge->Cartridge[Count].VertF3.z;


	//Strip4
	Q_Cartridge->Cartridge[Count].Lvert[6][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[6][0].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[6][0].x = Q_Cartridge->Cartridge[Count].VertB4.x;
	Q_Cartridge->Cartridge[Count].Lvert[6][0].y = Q_Cartridge->Cartridge[Count].VertB4.y;
	Q_Cartridge->Cartridge[Count].Lvert[6][0].z = Q_Cartridge->Cartridge[Count].VertB4.z;
	Q_Cartridge->Cartridge[Count].Lvert[6][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[6][1].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[6][1].x = Q_Cartridge->Cartridge[Count].VertB5.x;
	Q_Cartridge->Cartridge[Count].Lvert[6][1].y = Q_Cartridge->Cartridge[Count].VertB5.y;
	Q_Cartridge->Cartridge[Count].Lvert[6][1].z = Q_Cartridge->Cartridge[Count].VertB5.z;
	Q_Cartridge->Cartridge[Count].Lvert[6][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[6][2].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[6][2].x = Q_Cartridge->Cartridge[Count].VertF5.x;
	Q_Cartridge->Cartridge[Count].Lvert[6][2].y = Q_Cartridge->Cartridge[Count].VertF5.y;
	Q_Cartridge->Cartridge[Count].Lvert[6][2].z = Q_Cartridge->Cartridge[Count].VertF5.z;
	Q_Cartridge->Cartridge[Count].Lvert[6][3].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[6][3].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[6][3].x = Q_Cartridge->Cartridge[Count].VertF4.x;
	Q_Cartridge->Cartridge[Count].Lvert[6][3].y = Q_Cartridge->Cartridge[Count].VertF4.y;
	Q_Cartridge->Cartridge[Count].Lvert[6][3].z = Q_Cartridge->Cartridge[Count].VertF4.z;


	//Strip5
	Q_Cartridge->Cartridge[Count].Lvert[7][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[7][0].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[7][0].x = Q_Cartridge->Cartridge[Count].VertB5.x;
	Q_Cartridge->Cartridge[Count].Lvert[7][0].y = Q_Cartridge->Cartridge[Count].VertB5.y;
	Q_Cartridge->Cartridge[Count].Lvert[7][0].z = Q_Cartridge->Cartridge[Count].VertB5.z;
	Q_Cartridge->Cartridge[Count].Lvert[7][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[7][1].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[7][1].x = Q_Cartridge->Cartridge[Count].VertB1.x;
	Q_Cartridge->Cartridge[Count].Lvert[7][1].y = Q_Cartridge->Cartridge[Count].VertB1.y;
	Q_Cartridge->Cartridge[Count].Lvert[7][1].z = Q_Cartridge->Cartridge[Count].VertB1.z;
	Q_Cartridge->Cartridge[Count].Lvert[7][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[7][2].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[7][2].x = Q_Cartridge->Cartridge[Count].VertF1.x;
	Q_Cartridge->Cartridge[Count].Lvert[7][2].y = Q_Cartridge->Cartridge[Count].VertF1.y;
	Q_Cartridge->Cartridge[Count].Lvert[7][2].z = Q_Cartridge->Cartridge[Count].VertF1.z;
	Q_Cartridge->Cartridge[Count].Lvert[7][3].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[7][3].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[7][3].x = Q_Cartridge->Cartridge[Count].VertF5.x;
	Q_Cartridge->Cartridge[Count].Lvert[7][3].y = Q_Cartridge->Cartridge[Count].VertF5.y;
	Q_Cartridge->Cartridge[Count].Lvert[7][3].z = Q_Cartridge->Cartridge[Count].VertF5.z;


	//## Front Tris ##

	Q_Cartridge->Cartridge[Count].Lvert[8][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[8][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[8][0].x = Q_Cartridge->Cartridge[Count].VertF1.x;
	Q_Cartridge->Cartridge[Count].Lvert[8][0].y = Q_Cartridge->Cartridge[Count].VertF1.y;
	Q_Cartridge->Cartridge[Count].Lvert[8][0].z = Q_Cartridge->Cartridge[Count].VertF1.z;
	Q_Cartridge->Cartridge[Count].Lvert[8][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[8][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[8][1].x = Q_Cartridge->Cartridge[Count].VertF2.x;
	Q_Cartridge->Cartridge[Count].Lvert[8][1].y = Q_Cartridge->Cartridge[Count].VertF2.y;
	Q_Cartridge->Cartridge[Count].Lvert[8][1].z = Q_Cartridge->Cartridge[Count].VertF2.z;
	Q_Cartridge->Cartridge[Count].Lvert[8][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[8][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[8][2].x = Q_Cartridge->Cartridge[Count].VertFP.x;
	Q_Cartridge->Cartridge[Count].Lvert[8][2].y = Q_Cartridge->Cartridge[Count].VertFP.y;
	Q_Cartridge->Cartridge[Count].Lvert[8][2].z = Q_Cartridge->Cartridge[Count].VertFP.z;


	Q_Cartridge->Cartridge[Count].Lvert[9][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[9][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[9][0].x = Q_Cartridge->Cartridge[Count].VertF2.x;
	Q_Cartridge->Cartridge[Count].Lvert[9][0].y = Q_Cartridge->Cartridge[Count].VertF2.y;
	Q_Cartridge->Cartridge[Count].Lvert[9][0].z = Q_Cartridge->Cartridge[Count].VertF2.z;
	Q_Cartridge->Cartridge[Count].Lvert[9][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[9][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[9][1].x = Q_Cartridge->Cartridge[Count].VertF3.x;
	Q_Cartridge->Cartridge[Count].Lvert[9][1].y = Q_Cartridge->Cartridge[Count].VertF3.y;
	Q_Cartridge->Cartridge[Count].Lvert[9][1].z = Q_Cartridge->Cartridge[Count].VertF3.z;
	Q_Cartridge->Cartridge[Count].Lvert[9][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[9][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[9][2].x = Q_Cartridge->Cartridge[Count].VertFP.x;
	Q_Cartridge->Cartridge[Count].Lvert[9][2].y = Q_Cartridge->Cartridge[Count].VertFP.y;
	Q_Cartridge->Cartridge[Count].Lvert[9][2].z = Q_Cartridge->Cartridge[Count].VertFP.z;


	Q_Cartridge->Cartridge[Count].Lvert[10][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[10][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[10][0].x = Q_Cartridge->Cartridge[Count].VertF3.x;
	Q_Cartridge->Cartridge[Count].Lvert[10][0].y = Q_Cartridge->Cartridge[Count].VertF3.y;
	Q_Cartridge->Cartridge[Count].Lvert[10][0].z = Q_Cartridge->Cartridge[Count].VertF3.z;
	Q_Cartridge->Cartridge[Count].Lvert[10][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[10][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[10][1].x = Q_Cartridge->Cartridge[Count].VertF4.x;
	Q_Cartridge->Cartridge[Count].Lvert[10][1].y = Q_Cartridge->Cartridge[Count].VertF4.y;
	Q_Cartridge->Cartridge[Count].Lvert[10][1].z = Q_Cartridge->Cartridge[Count].VertF4.z;
	Q_Cartridge->Cartridge[Count].Lvert[10][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[10][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[10][2].x = Q_Cartridge->Cartridge[Count].VertFP.x;
	Q_Cartridge->Cartridge[Count].Lvert[10][2].y = Q_Cartridge->Cartridge[Count].VertFP.y;
	Q_Cartridge->Cartridge[Count].Lvert[10][2].z = Q_Cartridge->Cartridge[Count].VertFP.z;


	Q_Cartridge->Cartridge[Count].Lvert[11][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[11][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[11][0].x = Q_Cartridge->Cartridge[Count].VertF4.x;
	Q_Cartridge->Cartridge[Count].Lvert[11][0].y = Q_Cartridge->Cartridge[Count].VertF4.y;
	Q_Cartridge->Cartridge[Count].Lvert[11][0].z = Q_Cartridge->Cartridge[Count].VertF4.z;
	Q_Cartridge->Cartridge[Count].Lvert[11][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[11][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[11][1].x = Q_Cartridge->Cartridge[Count].VertF5.x;
	Q_Cartridge->Cartridge[Count].Lvert[11][1].y = Q_Cartridge->Cartridge[Count].VertF5.y;
	Q_Cartridge->Cartridge[Count].Lvert[11][1].z = Q_Cartridge->Cartridge[Count].VertF5.z;
	Q_Cartridge->Cartridge[Count].Lvert[11][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[11][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[11][2].x = Q_Cartridge->Cartridge[Count].VertFP.x;
	Q_Cartridge->Cartridge[Count].Lvert[11][2].y = Q_Cartridge->Cartridge[Count].VertFP.y;
	Q_Cartridge->Cartridge[Count].Lvert[11][2].z = Q_Cartridge->Cartridge[Count].VertFP.z;


	Q_Cartridge->Cartridge[Count].Lvert[12][0].u = 0;
	Q_Cartridge->Cartridge[Count].Lvert[12][0].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[12][0].x = Q_Cartridge->Cartridge[Count].VertF5.x;
	Q_Cartridge->Cartridge[Count].Lvert[12][0].y = Q_Cartridge->Cartridge[Count].VertF5.y;
	Q_Cartridge->Cartridge[Count].Lvert[12][0].z = Q_Cartridge->Cartridge[Count].VertF5.z;
	Q_Cartridge->Cartridge[Count].Lvert[12][1].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[12][1].v = 1;
	Q_Cartridge->Cartridge[Count].Lvert[12][1].x = Q_Cartridge->Cartridge[Count].VertF1.x;
	Q_Cartridge->Cartridge[Count].Lvert[12][1].y = Q_Cartridge->Cartridge[Count].VertF1.y;
	Q_Cartridge->Cartridge[Count].Lvert[12][1].z = Q_Cartridge->Cartridge[Count].VertF1.z;
	Q_Cartridge->Cartridge[Count].Lvert[12][2].u = 1;
	Q_Cartridge->Cartridge[Count].Lvert[12][2].v = 0;
	Q_Cartridge->Cartridge[Count].Lvert[12][2].x = Q_Cartridge->Cartridge[Count].VertFP.x;
	Q_Cartridge->Cartridge[Count].Lvert[12][2].y = Q_Cartridge->Cartridge[Count].VertFP.y;
	Q_Cartridge->Cartridge[Count].Lvert[12][2].z = Q_Cartridge->Cartridge[Count].VertFP.z;


	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[0][0], 3, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[1][0], 3, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[2][0], 3, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);

	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[3][0], 4, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[4][0], 4, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[5][0], 4, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[6][0], 4, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Cartridge->Cartridge[Count].Lvert[7][0], 4, Medias->cart1, Q_Cartridge->Cartridge[Count].Type, Q_Cartridge->Cartridge[Count].RenderFlags, Q_Cartridge->Cartridge[Count].ScaleBIT);
	}

};