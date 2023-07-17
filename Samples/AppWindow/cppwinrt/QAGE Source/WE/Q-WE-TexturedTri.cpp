/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Textured Tri Effect-

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

//------******[  <TEXTURED TRI>------[EFFECTS CONTROL COMPONENT]  ]******------

void Q_EFFCon::TexTriEffect_PlayerFrame(int Count)
	{
	switch(player[g_Player]->Q_TexTriEffect[Count].EffectType)
		{
		case 0:	//WindWake Ring Trail
			{
			if(Count != player[g_Player]->NomTriEffect - 1)
				{
				player[g_Player]->Q_TexTriEffect[Count].VertT1 = player[g_Player]->Q_TexTriEffect[Count+1].VertB1;
				player[g_Player]->Q_TexTriEffect[Count].VertT2 = player[g_Player]->Q_TexTriEffect[Count+1].VertB2;
				player[g_Player]->Q_TexTriEffect[Count].VertT3 = player[g_Player]->Q_TexTriEffect[Count+1].VertB3;
				player[g_Player]->Q_TexTriEffect[Count].VertT4 = player[g_Player]->Q_TexTriEffect[Count+1].VertB4;
				player[g_Player]->Q_TexTriEffect[Count].VertT5 = player[g_Player]->Q_TexTriEffect[Count+1].VertB5;
				player[g_Player]->Q_TexTriEffect[Count].VertT6 = player[g_Player]->Q_TexTriEffect[Count+1].VertB6;
				player[g_Player]->Q_TexTriEffect[Count].VertT7 = player[g_Player]->Q_TexTriEffect[Count+1].VertB7;
				player[g_Player]->Q_TexTriEffect[Count].VertT8 = player[g_Player]->Q_TexTriEffect[Count+1].VertB8;
				player[g_Player]->Q_TexTriEffect[Count].Pos = player[g_Player]->Q_TexTriEffect[Count+1].Pos;
				}

			player[g_Player]->Q_TexTriEffect[Count].VertB1 = player[g_Player]->Q_TexTriEffect[Count].VertT1;
			player[g_Player]->Q_TexTriEffect[Count].VertB2 = player[g_Player]->Q_TexTriEffect[Count].VertT2;
			player[g_Player]->Q_TexTriEffect[Count].VertB3 = player[g_Player]->Q_TexTriEffect[Count].VertT3;
			player[g_Player]->Q_TexTriEffect[Count].VertB4 = player[g_Player]->Q_TexTriEffect[Count].VertT4;
			player[g_Player]->Q_TexTriEffect[Count].VertB5 = player[g_Player]->Q_TexTriEffect[Count].VertT5;
			player[g_Player]->Q_TexTriEffect[Count].VertB6 = player[g_Player]->Q_TexTriEffect[Count].VertT6;
			player[g_Player]->Q_TexTriEffect[Count].VertB7 = player[g_Player]->Q_TexTriEffect[Count].VertT7;
			player[g_Player]->Q_TexTriEffect[Count].VertB8 = player[g_Player]->Q_TexTriEffect[Count].VertT8;


			//##### Material Count
			player[g_Player]->Q_TexTriEffect[Count].MaterialCNT++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT > 136) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 124;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			player[g_Player]->Q_TexTriEffect[Count].Alpha -= 4;
			if(player[g_Player]->Q_TexTriEffect[Count].Alpha < 0)
				{
				player[g_Player]->Q_TexTriEffect[Count].Alpha = 0;
				player[g_Player]->Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < player[g_Player]->NomTriEffect - 1)
					{
					player[g_Player]->Q_TexTriEffect[K] = player[g_Player]->Q_TexTriEffect[K+1];
					K++;
					}

				player[g_Player]->NomTriEffect--;
				}

			player[g_Player]->Q_TexTriEffect[Count].Green += 4;
			if(player[g_Player]->Q_TexTriEffect[Count].Green > 255) player[g_Player]->Q_TexTriEffect[Count].Green = 255;
			player[g_Player]->Q_TexTriEffect[Count].Red += 4;
			if(player[g_Player]->Q_TexTriEffect[Count].Red > 255) player[g_Player]->Q_TexTriEffect[Count].Red = 255;


			//##### Move Bottom Verts of Trail Back and Out
			player[g_Player]->Q_TexTriEffect[Count].LengthDist += 0.05;
			player[g_Player]->Q_TexTriEffect[Count].ExpandDist += 0.004;

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB1, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB2, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB3, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB4, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB5, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB6, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB7, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB8, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB8);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 7 )
				{
				int b=0;
				while( b <= 3 )
					{
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].a = player[g_Player]->Q_TexTriEffect[Count].Alpha;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].b = player[g_Player]->Q_TexTriEffect[Count].Blue;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].g = player[g_Player]->Q_TexTriEffect[Count].Green;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].r = player[g_Player]->Q_TexTriEffect[Count].Red;
					b++;
					}
				a++;
				}


			//##### - SOLID RING VERTS

			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

			
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

			
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT5.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB5.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT5.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT6.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB6.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB5.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT6.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT7.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB7.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB6.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT7.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT8.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB8.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB7.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT8.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].u = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].u = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB8.z;


			if(player[g_Player]->Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 7)
					{
					Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->Water[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT],  player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;


		case 1:	//WindWake Ring Trail [Static Non Correctional]
			{
			if(Count != player[g_Player]->NomTriEffect - 1)
				{
				player[g_Player]->Q_TexTriEffect[Count].VertT1 = player[g_Player]->Q_TexTriEffect[Count+1].VertB1;
				player[g_Player]->Q_TexTriEffect[Count].VertT2 = player[g_Player]->Q_TexTriEffect[Count+1].VertB2;
				player[g_Player]->Q_TexTriEffect[Count].VertT3 = player[g_Player]->Q_TexTriEffect[Count+1].VertB3;
				player[g_Player]->Q_TexTriEffect[Count].VertT4 = player[g_Player]->Q_TexTriEffect[Count+1].VertB4;
				player[g_Player]->Q_TexTriEffect[Count].VertT5 = player[g_Player]->Q_TexTriEffect[Count+1].VertB5;
				player[g_Player]->Q_TexTriEffect[Count].VertT6 = player[g_Player]->Q_TexTriEffect[Count+1].VertB6;
				player[g_Player]->Q_TexTriEffect[Count].VertT7 = player[g_Player]->Q_TexTriEffect[Count+1].VertB7;
				player[g_Player]->Q_TexTriEffect[Count].VertT8 = player[g_Player]->Q_TexTriEffect[Count+1].VertB8;
				player[g_Player]->Q_TexTriEffect[Count].VertT15 = player[g_Player]->Q_TexTriEffect[Count+1].VertB15;
				player[g_Player]->Q_TexTriEffect[Count].VertT25 = player[g_Player]->Q_TexTriEffect[Count+1].VertB25;
				player[g_Player]->Q_TexTriEffect[Count].VertT35 = player[g_Player]->Q_TexTriEffect[Count+1].VertB35;
				player[g_Player]->Q_TexTriEffect[Count].VertT45 = player[g_Player]->Q_TexTriEffect[Count+1].VertB45;
				player[g_Player]->Q_TexTriEffect[Count].VertT55 = player[g_Player]->Q_TexTriEffect[Count+1].VertB55;
				player[g_Player]->Q_TexTriEffect[Count].VertT65 = player[g_Player]->Q_TexTriEffect[Count+1].VertB65;
				player[g_Player]->Q_TexTriEffect[Count].VertT75 = player[g_Player]->Q_TexTriEffect[Count+1].VertB75;
				player[g_Player]->Q_TexTriEffect[Count].VertT85 = player[g_Player]->Q_TexTriEffect[Count+1].VertB85;
				}


			//##### Material Count
			player[g_Player]->Q_TexTriEffect[Count].MaterialCNT++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT < 124) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 124;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT > 136) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 124;

			/*player[g_Player]->Q_TexTriEffect[Count].MaterialCNT++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT < 82) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT > 96) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;*/


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			player[g_Player]->Q_TexTriEffect[Count].Alpha -= 6;
			if(player[g_Player]->Q_TexTriEffect[Count].Alpha < 0)
				{
				player[g_Player]->Q_TexTriEffect[Count].Alpha = 0;
				player[g_Player]->Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < player[g_Player]->NomTriEffect - 1)
					{
					player[g_Player]->Q_TexTriEffect[K] = player[g_Player]->Q_TexTriEffect[K+1];
					K++;
					}

				player[g_Player]->NomTriEffect--;
				}

			if(player[g_Player]->Q_TexTriEffect[Count].Green > 80)
				{
				player[g_Player]->Q_TexTriEffect[Count].Red += 3*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Red > 255) player[g_Player]->Q_TexTriEffect[Count].Red = 255;
				player[g_Player]->Q_TexTriEffect[Count].Green += 3*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Green > 255) player[g_Player]->Q_TexTriEffect[Count].Green = 255;
				}
			else
				{
				player[g_Player]->Q_TexTriEffect[Count].Red -= 10*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Red < 0) player[g_Player]->Q_TexTriEffect[Count].Red = 0;
				player[g_Player]->Q_TexTriEffect[Count].Green -= 10*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Green < 0) player[g_Player]->Q_TexTriEffect[Count].Green = 0;
				player[g_Player]->Q_TexTriEffect[Count].Blue -= 10*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Blue < 0) player[g_Player]->Q_TexTriEffect[Count].Blue = 0;
				}


			//##### Move Bottom Verts of Trail Back and Out
			//player[g_Player]->Q_TexTriEffect[Count].LengthDist += 0.05;
			player[g_Player]->Q_TexTriEffect[Count].ExpandDist += 0.004;

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB1, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB2, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB3, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB4, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB5, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB6, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB7, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB8, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB8);


			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB15, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB15, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB15);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB25, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB25, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB25);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB35, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB35, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB35);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB45, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB45, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB45);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB55, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB55, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB55);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB65, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB65, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB65);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB75, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB75, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB75);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB85, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB85, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB85);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 15 )
				{
				int b=0;
				while( b <= 3 )
					{
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].a = player[g_Player]->Q_TexTriEffect[Count].Alpha;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].b = player[g_Player]->Q_TexTriEffect[Count].Blue;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].g = player[g_Player]->Q_TexTriEffect[Count].Green;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].r = player[g_Player]->Q_TexTriEffect[Count].Red;
					b++;
					}
				a++;
				}


			//##### - SOLID RING VERTS

			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

			
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT15.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB15.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT15.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB15.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT25.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB25.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT25.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB25.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT35.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB35.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT35.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB35.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT45.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB45.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT45.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT5.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB5.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB45.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT5.z;

			
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT55.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB55.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB5.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT55.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT6.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB6.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB55.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT6.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT65.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB65.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB6.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT65.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT7.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB7.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB65.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT7.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT75.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB75.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB7.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT75.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT8.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB8.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB75.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT8.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT85.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB85.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB8.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT85.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB85.z;


			if(player[g_Player]->Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 15)
					{
					Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->Water[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT],  player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;


		case 2:	//##### Flame Trails
			{
			if(Count != player[g_Player]->NomTriEffect - 1)
				{
				player[g_Player]->Q_TexTriEffect[Count].VertT1 = player[g_Player]->Q_TexTriEffect[Count+1].VertB1;
				player[g_Player]->Q_TexTriEffect[Count].VertT2 = player[g_Player]->Q_TexTriEffect[Count+1].VertB2;
				player[g_Player]->Q_TexTriEffect[Count].VertT3 = player[g_Player]->Q_TexTriEffect[Count+1].VertB3;
				player[g_Player]->Q_TexTriEffect[Count].VertT4 = player[g_Player]->Q_TexTriEffect[Count+1].VertB4;
				}


			//##### Material Count  Set this
				//Fire
			player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2 < 124) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2 = 124;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2 > 136) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2 = 124;

				//Energy
			player[g_Player]->Q_TexTriEffect[Count].MaterialCNT++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT < 82) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT > 96) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			player[g_Player]->Q_TexTriEffect[Count].Alpha -= 30;	//80
			if(player[g_Player]->Q_TexTriEffect[Count].Alpha < 0)
				{
				player[g_Player]->Q_TexTriEffect[Count].Alpha = 0;
				player[g_Player]->Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < player[g_Player]->NomTriEffect - 1)
					{
					player[g_Player]->Q_TexTriEffect[K] = player[g_Player]->Q_TexTriEffect[K+1];
					K++;
					}

				player[g_Player]->NomTriEffect--;
				}


			/*if(player[g_Player]->Aposestate != 59)
				{
				player[g_Player]->Q_TexTriEffect[Count].Green += 3*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Green > 255) player[g_Player]->Q_TexTriEffect[Count].Green = 255;
				player[g_Player]->Q_TexTriEffect[Count].Red += 3*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Red > 255) player[g_Player]->Q_TexTriEffect[Count].Red = 255;
				}
			else
				{
				player[g_Player]->Q_TexTriEffect[Count].Green -= 20*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Green < 0) player[g_Player]->Q_TexTriEffect[Count].Green = 0;
				player[g_Player]->Q_TexTriEffect[Count].Red -= 20*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Red < 0) player[g_Player]->Q_TexTriEffect[Count].Red = 0;
				player[g_Player]->Q_TexTriEffect[Count].Blue -= 20*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Blue < 0) player[g_Player]->Q_TexTriEffect[Count].Blue = 0;
				}*/


			//##### Move Bottom Verts of Trail Back and Out
			player[g_Player]->Q_TexTriEffect[Count].ExpandDist *= 5;

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB1, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB2, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB3, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB4, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB4);


			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertT1, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertT1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT1, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertT1);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertT2, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertT2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT2, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertT2);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertT3, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertT3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT3, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertT3);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertT4, &player[g_Player]->Q_TexTriEffect[Count].Pos, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertT4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertT4, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertT4);


				int a=0;
				while( a <= 4 )
					{
					int b=0;
					while( b <= 3 )
						{
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].a = player[g_Player]->Q_TexTriEffect[Count].Alpha;
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].b = 255;
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].g = 255;
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].r = 255;
						b++;
						}
					a++;
					}


				a=5;
				while( a <= 8 )
					{
					int b=0;
					while( b <= 3 )
						{
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].a = player[g_Player]->Q_TexTriEffect[Count].Alpha/6;
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].b = 255;
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].g = 255;
						player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].r = 255;
						b++;
						}
					a++;
					}


				//##### - START CAP	- FLAMES
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].u = 0.5;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;


				//##### - END CAP - FLAMES
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].u = 0.5;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


				//##### - BOTTOM CAP - FLAMES
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].v = 0.1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].v = 0.1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


				//##### - FRONT FLAT PANEL - FLAMES
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


				//##### - BACK FLAT PANEL - FLAMES
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;



				//##### - START CAP	- ENERGY
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].u = 0.5;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;


				//##### - END CAP - ENERGY
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].u = 0.5;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


				//##### - FRONT FLAT PANEL - ENERGY
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


				//##### - BACK FLAT PANEL - ENERGY
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].u = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;
								
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].v = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;

				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].u = 1;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].v = 0;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
				player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			if(player[g_Player]->Q_TexTriEffect[Count].Live == 1)
				{
				//FLAMES
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0], 3, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0], 3, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0], 4, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0], 4, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0], 4, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);

				//ENERGY
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0], 3, Medias->Water[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0], 3, Medias->Water[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0], 4, Medias->Water[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0], 4, Medias->Water[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT2], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
				}

			} break;


		case 3:	//Flame Ring Trail [Static Non Correctional]
			{
			if(Count != player[g_Player]->NomTriEffect - 1)
				{
				player[g_Player]->Q_TexTriEffect[Count].VertT1 = player[g_Player]->Q_TexTriEffect[Count+1].VertB1;
				player[g_Player]->Q_TexTriEffect[Count].VertT2 = player[g_Player]->Q_TexTriEffect[Count+1].VertB2;
				player[g_Player]->Q_TexTriEffect[Count].VertT3 = player[g_Player]->Q_TexTriEffect[Count+1].VertB3;
				player[g_Player]->Q_TexTriEffect[Count].VertT4 = player[g_Player]->Q_TexTriEffect[Count+1].VertB4;
				player[g_Player]->Q_TexTriEffect[Count].VertT5 = player[g_Player]->Q_TexTriEffect[Count+1].VertB5;
				player[g_Player]->Q_TexTriEffect[Count].VertT6 = player[g_Player]->Q_TexTriEffect[Count+1].VertB6;
				player[g_Player]->Q_TexTriEffect[Count].VertT7 = player[g_Player]->Q_TexTriEffect[Count+1].VertB7;
				player[g_Player]->Q_TexTriEffect[Count].VertT8 = player[g_Player]->Q_TexTriEffect[Count+1].VertB8;
				//player[g_Player]->Q_TexTriEffect[Count].Pos = player[g_Player]->Q_TexTriEffect[Count+1].Pos;
				}

			//player[g_Player]->Q_TexTriEffect[Count].VertB1 = player[g_Player]->Q_TexTriEffect[Count].VertT1;
			//player[g_Player]->Q_TexTriEffect[Count].VertB2 = player[g_Player]->Q_TexTriEffect[Count].VertT2;
			//player[g_Player]->Q_TexTriEffect[Count].VertB3 = player[g_Player]->Q_TexTriEffect[Count].VertT3;
			//player[g_Player]->Q_TexTriEffect[Count].VertB4 = player[g_Player]->Q_TexTriEffect[Count].VertT4;
			//player[g_Player]->Q_TexTriEffect[Count].VertB5 = player[g_Player]->Q_TexTriEffect[Count].VertT5;
			//player[g_Player]->Q_TexTriEffect[Count].VertB6 = player[g_Player]->Q_TexTriEffect[Count].VertT6;
			//player[g_Player]->Q_TexTriEffect[Count].VertB7 = player[g_Player]->Q_TexTriEffect[Count].VertT7;
			//player[g_Player]->Q_TexTriEffect[Count].VertB8 = player[g_Player]->Q_TexTriEffect[Count].VertT8;


			//##### Material Count
			player[g_Player]->Q_TexTriEffect[Count].MaterialCNT++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT < 82) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT > 96) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			player[g_Player]->Q_TexTriEffect[Count].Alpha -= 6;
			if(player[g_Player]->Q_TexTriEffect[Count].Alpha < 0)
				{
				player[g_Player]->Q_TexTriEffect[Count].Alpha = 0;
				player[g_Player]->Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < player[g_Player]->NomTriEffect - 1)
					{
					player[g_Player]->Q_TexTriEffect[K] = player[g_Player]->Q_TexTriEffect[K+1];
					K++;
					}

				player[g_Player]->NomTriEffect--;
				}

			
			player[g_Player]->Q_TexTriEffect[Count].Green += 3*_->TimeScale;
			if(player[g_Player]->Q_TexTriEffect[Count].Green > 255) player[g_Player]->Q_TexTriEffect[Count].Green = 255;
			player[g_Player]->Q_TexTriEffect[Count].Red += 3*_->TimeScale;
			if(player[g_Player]->Q_TexTriEffect[Count].Red > 255) player[g_Player]->Q_TexTriEffect[Count].Red = 255;
			


			//##### Move Bottom Verts of Trail Back and Out
			//player[g_Player]->Q_TexTriEffect[Count].LengthDist += 0.05;
			player[g_Player]->Q_TexTriEffect[Count].ExpandDist += 0.02;	//0.004

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB1, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB2, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB3, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB4, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB5, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB6, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB7, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB8, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB8);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 15 )
				{
				int b=0;
				while( b <= 3 )
					{
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].a = player[g_Player]->Q_TexTriEffect[Count].Alpha;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].b = player[g_Player]->Q_TexTriEffect[Count].Blue;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].g = player[g_Player]->Q_TexTriEffect[Count].Green;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].r = player[g_Player]->Q_TexTriEffect[Count].Red;
					b++;
					}
				a++;
				}


			//##### - SOLID RING TWO

			Q_WindWake->WindWake[Count].Lvert[0][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[0][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[0][0].x = Q_WindWake->WindWake[Count].VertT1.x;
			Q_WindWake->WindWake[Count].Lvert[0][0].y = Q_WindWake->WindWake[Count].VertT1.y;
			Q_WindWake->WindWake[Count].Lvert[0][0].z = Q_WindWake->WindWake[Count].VertT1.z;

			
			Q_WindWake->WindWake[Count].Lvert[0][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[0][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[0][1].x = Q_WindWake->WindWake[Count].VertT15.x;
			Q_WindWake->WindWake[Count].Lvert[0][1].y = Q_WindWake->WindWake[Count].VertT15.y;
			Q_WindWake->WindWake[Count].Lvert[0][1].z = Q_WindWake->WindWake[Count].VertT15.z;

					
			Q_WindWake->WindWake[Count].Lvert[0][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[0][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[0][2].x = Q_WindWake->WindWake[Count].VertB15.x;
			Q_WindWake->WindWake[Count].Lvert[0][2].y = Q_WindWake->WindWake[Count].VertB15.y;
			Q_WindWake->WindWake[Count].Lvert[0][2].z = Q_WindWake->WindWake[Count].VertB15.z;


			Q_WindWake->WindWake[Count].Lvert[0][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[0][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[0][3].x = Q_WindWake->WindWake[Count].VertB1.x;
			Q_WindWake->WindWake[Count].Lvert[0][3].y = Q_WindWake->WindWake[Count].VertB1.y;
			Q_WindWake->WindWake[Count].Lvert[0][3].z = Q_WindWake->WindWake[Count].VertB1.z;


			Q_WindWake->WindWake[Count].Lvert[1][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[1][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[1][0].x = Q_WindWake->WindWake[Count].VertT15.x;
			Q_WindWake->WindWake[Count].Lvert[1][0].y = Q_WindWake->WindWake[Count].VertT15.y;
			Q_WindWake->WindWake[Count].Lvert[1][0].z = Q_WindWake->WindWake[Count].VertT15.z;

					
			Q_WindWake->WindWake[Count].Lvert[1][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[1][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[1][1].x = Q_WindWake->WindWake[Count].VertT2.x;
			Q_WindWake->WindWake[Count].Lvert[1][1].y = Q_WindWake->WindWake[Count].VertT2.y;
			Q_WindWake->WindWake[Count].Lvert[1][1].z = Q_WindWake->WindWake[Count].VertT2.z;

					
			Q_WindWake->WindWake[Count].Lvert[1][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[1][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[1][2].x = Q_WindWake->WindWake[Count].VertB2.x;
			Q_WindWake->WindWake[Count].Lvert[1][2].y = Q_WindWake->WindWake[Count].VertB2.y;
			Q_WindWake->WindWake[Count].Lvert[1][2].z = Q_WindWake->WindWake[Count].VertB2.z;


			Q_WindWake->WindWake[Count].Lvert[1][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[1][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[1][3].x = Q_WindWake->WindWake[Count].VertB15.x;
			Q_WindWake->WindWake[Count].Lvert[1][3].y = Q_WindWake->WindWake[Count].VertB15.y;
			Q_WindWake->WindWake[Count].Lvert[1][3].z = Q_WindWake->WindWake[Count].VertB15.z;


			Q_WindWake->WindWake[Count].Lvert[2][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[2][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[2][0].x = Q_WindWake->WindWake[Count].VertT2.x;
			Q_WindWake->WindWake[Count].Lvert[2][0].y = Q_WindWake->WindWake[Count].VertT2.y;
			Q_WindWake->WindWake[Count].Lvert[2][0].z = Q_WindWake->WindWake[Count].VertT2.z;

					
			Q_WindWake->WindWake[Count].Lvert[2][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[2][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[2][1].x = Q_WindWake->WindWake[Count].VertT25.x;
			Q_WindWake->WindWake[Count].Lvert[2][1].y = Q_WindWake->WindWake[Count].VertT25.y;
			Q_WindWake->WindWake[Count].Lvert[2][1].z = Q_WindWake->WindWake[Count].VertT25.z;

					
			Q_WindWake->WindWake[Count].Lvert[2][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[2][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[2][2].x = Q_WindWake->WindWake[Count].VertB25.x;
			Q_WindWake->WindWake[Count].Lvert[2][2].y = Q_WindWake->WindWake[Count].VertB25.y;
			Q_WindWake->WindWake[Count].Lvert[2][2].z = Q_WindWake->WindWake[Count].VertB25.z;


			Q_WindWake->WindWake[Count].Lvert[2][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[2][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[2][3].x = Q_WindWake->WindWake[Count].VertB2.x;
			Q_WindWake->WindWake[Count].Lvert[2][3].y = Q_WindWake->WindWake[Count].VertB2.y;
			Q_WindWake->WindWake[Count].Lvert[2][3].z = Q_WindWake->WindWake[Count].VertB2.z;



			Q_WindWake->WindWake[Count].Lvert[3][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[3][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[3][0].x = Q_WindWake->WindWake[Count].VertT25.x;
			Q_WindWake->WindWake[Count].Lvert[3][0].y = Q_WindWake->WindWake[Count].VertT25.y;
			Q_WindWake->WindWake[Count].Lvert[3][0].z = Q_WindWake->WindWake[Count].VertT25.z;

					
			Q_WindWake->WindWake[Count].Lvert[3][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[3][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[3][1].x = Q_WindWake->WindWake[Count].VertT3.x;
			Q_WindWake->WindWake[Count].Lvert[3][1].y = Q_WindWake->WindWake[Count].VertT3.y;
			Q_WindWake->WindWake[Count].Lvert[3][1].z = Q_WindWake->WindWake[Count].VertT3.z;

					
			Q_WindWake->WindWake[Count].Lvert[3][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[3][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[3][2].x = Q_WindWake->WindWake[Count].VertB3.x;
			Q_WindWake->WindWake[Count].Lvert[3][2].y = Q_WindWake->WindWake[Count].VertB3.y;
			Q_WindWake->WindWake[Count].Lvert[3][2].z = Q_WindWake->WindWake[Count].VertB3.z;


			Q_WindWake->WindWake[Count].Lvert[3][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[3][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[3][3].x = Q_WindWake->WindWake[Count].VertB25.x;
			Q_WindWake->WindWake[Count].Lvert[3][3].y = Q_WindWake->WindWake[Count].VertB25.y;
			Q_WindWake->WindWake[Count].Lvert[3][3].z = Q_WindWake->WindWake[Count].VertB25.z;


			Q_WindWake->WindWake[Count].Lvert[4][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[4][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[4][0].x = Q_WindWake->WindWake[Count].VertT3.x;
			Q_WindWake->WindWake[Count].Lvert[4][0].y = Q_WindWake->WindWake[Count].VertT3.y;
			Q_WindWake->WindWake[Count].Lvert[4][0].z = Q_WindWake->WindWake[Count].VertT3.z;

					
			Q_WindWake->WindWake[Count].Lvert[4][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[4][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[4][1].x = Q_WindWake->WindWake[Count].VertT35.x;
			Q_WindWake->WindWake[Count].Lvert[4][1].y = Q_WindWake->WindWake[Count].VertT35.y;
			Q_WindWake->WindWake[Count].Lvert[4][1].z = Q_WindWake->WindWake[Count].VertT35.z;

					
			Q_WindWake->WindWake[Count].Lvert[4][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[4][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[4][2].x = Q_WindWake->WindWake[Count].VertB35.x;
			Q_WindWake->WindWake[Count].Lvert[4][2].y = Q_WindWake->WindWake[Count].VertB35.y;
			Q_WindWake->WindWake[Count].Lvert[4][2].z = Q_WindWake->WindWake[Count].VertB35.z;


			Q_WindWake->WindWake[Count].Lvert[4][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[4][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[4][3].x = Q_WindWake->WindWake[Count].VertB3.x;
			Q_WindWake->WindWake[Count].Lvert[4][3].y = Q_WindWake->WindWake[Count].VertB3.y;
			Q_WindWake->WindWake[Count].Lvert[4][3].z = Q_WindWake->WindWake[Count].VertB3.z;


			Q_WindWake->WindWake[Count].Lvert[5][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[5][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[5][0].x = Q_WindWake->WindWake[Count].VertT35.x;
			Q_WindWake->WindWake[Count].Lvert[5][0].y = Q_WindWake->WindWake[Count].VertT35.y;
			Q_WindWake->WindWake[Count].Lvert[5][0].z = Q_WindWake->WindWake[Count].VertT35.z;

					
			Q_WindWake->WindWake[Count].Lvert[5][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[5][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[5][1].x = Q_WindWake->WindWake[Count].VertT4.x;
			Q_WindWake->WindWake[Count].Lvert[5][1].y = Q_WindWake->WindWake[Count].VertT4.y;
			Q_WindWake->WindWake[Count].Lvert[5][1].z = Q_WindWake->WindWake[Count].VertT4.z;

					
			Q_WindWake->WindWake[Count].Lvert[5][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[5][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[5][2].x = Q_WindWake->WindWake[Count].VertB4.x;
			Q_WindWake->WindWake[Count].Lvert[5][2].y = Q_WindWake->WindWake[Count].VertB4.y;
			Q_WindWake->WindWake[Count].Lvert[5][2].z = Q_WindWake->WindWake[Count].VertB4.z;


			Q_WindWake->WindWake[Count].Lvert[5][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[5][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[5][3].x = Q_WindWake->WindWake[Count].VertB35.x;
			Q_WindWake->WindWake[Count].Lvert[5][3].y = Q_WindWake->WindWake[Count].VertB35.y;
			Q_WindWake->WindWake[Count].Lvert[5][3].z = Q_WindWake->WindWake[Count].VertB35.z;


			Q_WindWake->WindWake[Count].Lvert[6][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[6][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[6][0].x = Q_WindWake->WindWake[Count].VertT4.x;
			Q_WindWake->WindWake[Count].Lvert[6][0].y = Q_WindWake->WindWake[Count].VertT4.y;
			Q_WindWake->WindWake[Count].Lvert[6][0].z = Q_WindWake->WindWake[Count].VertT4.z;

					
			Q_WindWake->WindWake[Count].Lvert[6][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[6][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[6][1].x = Q_WindWake->WindWake[Count].VertT45.x;
			Q_WindWake->WindWake[Count].Lvert[6][1].y = Q_WindWake->WindWake[Count].VertT45.y;
			Q_WindWake->WindWake[Count].Lvert[6][1].z = Q_WindWake->WindWake[Count].VertT45.z;

					
			Q_WindWake->WindWake[Count].Lvert[6][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[6][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[6][2].x = Q_WindWake->WindWake[Count].VertB45.x;
			Q_WindWake->WindWake[Count].Lvert[6][2].y = Q_WindWake->WindWake[Count].VertB45.y;
			Q_WindWake->WindWake[Count].Lvert[6][2].z = Q_WindWake->WindWake[Count].VertB45.z;


			Q_WindWake->WindWake[Count].Lvert[6][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[6][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[6][3].x = Q_WindWake->WindWake[Count].VertB4.x;
			Q_WindWake->WindWake[Count].Lvert[6][3].y = Q_WindWake->WindWake[Count].VertB4.y;
			Q_WindWake->WindWake[Count].Lvert[6][3].z = Q_WindWake->WindWake[Count].VertB4.z;


			Q_WindWake->WindWake[Count].Lvert[7][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[7][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[7][0].x = Q_WindWake->WindWake[Count].VertT45.x;
			Q_WindWake->WindWake[Count].Lvert[7][0].y = Q_WindWake->WindWake[Count].VertT45.y;
			Q_WindWake->WindWake[Count].Lvert[7][0].z = Q_WindWake->WindWake[Count].VertT45.z;

					
			Q_WindWake->WindWake[Count].Lvert[7][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[7][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[7][1].x = Q_WindWake->WindWake[Count].VertT5.x;
			Q_WindWake->WindWake[Count].Lvert[7][1].y = Q_WindWake->WindWake[Count].VertT5.y;
			Q_WindWake->WindWake[Count].Lvert[7][1].z = Q_WindWake->WindWake[Count].VertT5.z;

					
			Q_WindWake->WindWake[Count].Lvert[7][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[7][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[7][2].x = Q_WindWake->WindWake[Count].VertB5.x;
			Q_WindWake->WindWake[Count].Lvert[7][2].y = Q_WindWake->WindWake[Count].VertB5.y;
			Q_WindWake->WindWake[Count].Lvert[7][2].z = Q_WindWake->WindWake[Count].VertB5.z;


			Q_WindWake->WindWake[Count].Lvert[7][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[7][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[7][3].x = Q_WindWake->WindWake[Count].VertB45.x;
			Q_WindWake->WindWake[Count].Lvert[7][3].y = Q_WindWake->WindWake[Count].VertB45.y;
			Q_WindWake->WindWake[Count].Lvert[7][3].z = Q_WindWake->WindWake[Count].VertB45.z;


			Q_WindWake->WindWake[Count].Lvert[8][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[8][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[8][0].x = Q_WindWake->WindWake[Count].VertT5.x;
			Q_WindWake->WindWake[Count].Lvert[8][0].y = Q_WindWake->WindWake[Count].VertT5.y;
			Q_WindWake->WindWake[Count].Lvert[8][0].z = Q_WindWake->WindWake[Count].VertT5.z;

			
			Q_WindWake->WindWake[Count].Lvert[8][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[8][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[8][1].x = Q_WindWake->WindWake[Count].VertT55.x;
			Q_WindWake->WindWake[Count].Lvert[8][1].y = Q_WindWake->WindWake[Count].VertT55.y;
			Q_WindWake->WindWake[Count].Lvert[8][1].z = Q_WindWake->WindWake[Count].VertT55.z;

					
			Q_WindWake->WindWake[Count].Lvert[8][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[8][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[8][2].x = Q_WindWake->WindWake[Count].VertB55.x;
			Q_WindWake->WindWake[Count].Lvert[8][2].y = Q_WindWake->WindWake[Count].VertB55.y;
			Q_WindWake->WindWake[Count].Lvert[8][2].z = Q_WindWake->WindWake[Count].VertB55.z;


			Q_WindWake->WindWake[Count].Lvert[8][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[8][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[8][3].x = Q_WindWake->WindWake[Count].VertB5.x;
			Q_WindWake->WindWake[Count].Lvert[8][3].y = Q_WindWake->WindWake[Count].VertB5.y;
			Q_WindWake->WindWake[Count].Lvert[8][3].z = Q_WindWake->WindWake[Count].VertB5.z;


			Q_WindWake->WindWake[Count].Lvert[9][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[9][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[9][0].x = Q_WindWake->WindWake[Count].VertT55.x;
			Q_WindWake->WindWake[Count].Lvert[9][0].y = Q_WindWake->WindWake[Count].VertT55.y;
			Q_WindWake->WindWake[Count].Lvert[9][0].z = Q_WindWake->WindWake[Count].VertT55.z;

					
			Q_WindWake->WindWake[Count].Lvert[9][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[9][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[9][1].x = Q_WindWake->WindWake[Count].VertT6.x;
			Q_WindWake->WindWake[Count].Lvert[9][1].y = Q_WindWake->WindWake[Count].VertT6.y;
			Q_WindWake->WindWake[Count].Lvert[9][1].z = Q_WindWake->WindWake[Count].VertT6.z;

					
			Q_WindWake->WindWake[Count].Lvert[9][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[9][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[9][2].x = Q_WindWake->WindWake[Count].VertB6.x;
			Q_WindWake->WindWake[Count].Lvert[9][2].y = Q_WindWake->WindWake[Count].VertB6.y;
			Q_WindWake->WindWake[Count].Lvert[9][2].z = Q_WindWake->WindWake[Count].VertB6.z;


			Q_WindWake->WindWake[Count].Lvert[9][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[9][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[9][3].x = Q_WindWake->WindWake[Count].VertB55.x;
			Q_WindWake->WindWake[Count].Lvert[9][3].y = Q_WindWake->WindWake[Count].VertB55.y;
			Q_WindWake->WindWake[Count].Lvert[9][3].z = Q_WindWake->WindWake[Count].VertB55.z;


			Q_WindWake->WindWake[Count].Lvert[10][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[10][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[10][0].x = Q_WindWake->WindWake[Count].VertT6.x;
			Q_WindWake->WindWake[Count].Lvert[10][0].y = Q_WindWake->WindWake[Count].VertT6.y;
			Q_WindWake->WindWake[Count].Lvert[10][0].z = Q_WindWake->WindWake[Count].VertT6.z;

					
			Q_WindWake->WindWake[Count].Lvert[10][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[10][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[10][1].x = Q_WindWake->WindWake[Count].VertT65.x;
			Q_WindWake->WindWake[Count].Lvert[10][1].y = Q_WindWake->WindWake[Count].VertT65.y;
			Q_WindWake->WindWake[Count].Lvert[10][1].z = Q_WindWake->WindWake[Count].VertT65.z;

					
			Q_WindWake->WindWake[Count].Lvert[10][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[10][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[10][2].x = Q_WindWake->WindWake[Count].VertB65.x;
			Q_WindWake->WindWake[Count].Lvert[10][2].y = Q_WindWake->WindWake[Count].VertB65.y;
			Q_WindWake->WindWake[Count].Lvert[10][2].z = Q_WindWake->WindWake[Count].VertB65.z;


			Q_WindWake->WindWake[Count].Lvert[10][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[10][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[10][3].x = Q_WindWake->WindWake[Count].VertB6.x;
			Q_WindWake->WindWake[Count].Lvert[10][3].y = Q_WindWake->WindWake[Count].VertB6.y;
			Q_WindWake->WindWake[Count].Lvert[10][3].z = Q_WindWake->WindWake[Count].VertB6.z;


			Q_WindWake->WindWake[Count].Lvert[11][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[11][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[11][0].x = Q_WindWake->WindWake[Count].VertT65.x;
			Q_WindWake->WindWake[Count].Lvert[11][0].y = Q_WindWake->WindWake[Count].VertT65.y;
			Q_WindWake->WindWake[Count].Lvert[11][0].z = Q_WindWake->WindWake[Count].VertT65.z;

					
			Q_WindWake->WindWake[Count].Lvert[11][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[11][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[11][1].x = Q_WindWake->WindWake[Count].VertT7.x;
			Q_WindWake->WindWake[Count].Lvert[11][1].y = Q_WindWake->WindWake[Count].VertT7.y;
			Q_WindWake->WindWake[Count].Lvert[11][1].z = Q_WindWake->WindWake[Count].VertT7.z;

					
			Q_WindWake->WindWake[Count].Lvert[11][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[11][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[11][2].x = Q_WindWake->WindWake[Count].VertB7.x;
			Q_WindWake->WindWake[Count].Lvert[11][2].y = Q_WindWake->WindWake[Count].VertB7.y;
			Q_WindWake->WindWake[Count].Lvert[11][2].z = Q_WindWake->WindWake[Count].VertB7.z;


			Q_WindWake->WindWake[Count].Lvert[11][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[11][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[11][3].x = Q_WindWake->WindWake[Count].VertB65.x;
			Q_WindWake->WindWake[Count].Lvert[11][3].y = Q_WindWake->WindWake[Count].VertB65.y;
			Q_WindWake->WindWake[Count].Lvert[11][3].z = Q_WindWake->WindWake[Count].VertB65.z;


			Q_WindWake->WindWake[Count].Lvert[12][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[12][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[12][0].x = Q_WindWake->WindWake[Count].VertT7.x;
			Q_WindWake->WindWake[Count].Lvert[12][0].y = Q_WindWake->WindWake[Count].VertT7.y;
			Q_WindWake->WindWake[Count].Lvert[12][0].z = Q_WindWake->WindWake[Count].VertT7.z;

					
			Q_WindWake->WindWake[Count].Lvert[12][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[12][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[12][1].x = Q_WindWake->WindWake[Count].VertT75.x;
			Q_WindWake->WindWake[Count].Lvert[12][1].y = Q_WindWake->WindWake[Count].VertT75.y;
			Q_WindWake->WindWake[Count].Lvert[12][1].z = Q_WindWake->WindWake[Count].VertT75.z;

					
			Q_WindWake->WindWake[Count].Lvert[12][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[12][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[12][2].x = Q_WindWake->WindWake[Count].VertB75.x;
			Q_WindWake->WindWake[Count].Lvert[12][2].y = Q_WindWake->WindWake[Count].VertB75.y;
			Q_WindWake->WindWake[Count].Lvert[12][2].z = Q_WindWake->WindWake[Count].VertB75.z;


			Q_WindWake->WindWake[Count].Lvert[12][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[12][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[12][3].x = Q_WindWake->WindWake[Count].VertB7.x;
			Q_WindWake->WindWake[Count].Lvert[12][3].y = Q_WindWake->WindWake[Count].VertB7.y;
			Q_WindWake->WindWake[Count].Lvert[13][3].z = Q_WindWake->WindWake[Count].VertB7.z;


			Q_WindWake->WindWake[Count].Lvert[13][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[13][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[13][0].x = Q_WindWake->WindWake[Count].VertT75.x;
			Q_WindWake->WindWake[Count].Lvert[13][0].y = Q_WindWake->WindWake[Count].VertT75.y;
			Q_WindWake->WindWake[Count].Lvert[13][0].z = Q_WindWake->WindWake[Count].VertT75.z;

					
			Q_WindWake->WindWake[Count].Lvert[13][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[13][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[13][1].x = Q_WindWake->WindWake[Count].VertT8.x;
			Q_WindWake->WindWake[Count].Lvert[13][1].y = Q_WindWake->WindWake[Count].VertT8.y;
			Q_WindWake->WindWake[Count].Lvert[13][1].z = Q_WindWake->WindWake[Count].VertT8.z;

					
			Q_WindWake->WindWake[Count].Lvert[13][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[13][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[13][2].x = Q_WindWake->WindWake[Count].VertB8.x;
			Q_WindWake->WindWake[Count].Lvert[13][2].y = Q_WindWake->WindWake[Count].VertB8.y;
			Q_WindWake->WindWake[Count].Lvert[13][2].z = Q_WindWake->WindWake[Count].VertB8.z;


			Q_WindWake->WindWake[Count].Lvert[13][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[13][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[13][3].x = Q_WindWake->WindWake[Count].VertB75.x;
			Q_WindWake->WindWake[Count].Lvert[13][3].y = Q_WindWake->WindWake[Count].VertB75.y;
			Q_WindWake->WindWake[Count].Lvert[13][3].z = Q_WindWake->WindWake[Count].VertB75.z;


			Q_WindWake->WindWake[Count].Lvert[14][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[14][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[14][0].x = Q_WindWake->WindWake[Count].VertT8.x;
			Q_WindWake->WindWake[Count].Lvert[14][0].y = Q_WindWake->WindWake[Count].VertT8.y;
			Q_WindWake->WindWake[Count].Lvert[14][0].z = Q_WindWake->WindWake[Count].VertT8.z;

					
			Q_WindWake->WindWake[Count].Lvert[14][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[14][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[14][1].x = Q_WindWake->WindWake[Count].VertT85.x;
			Q_WindWake->WindWake[Count].Lvert[14][1].y = Q_WindWake->WindWake[Count].VertT85.y;
			Q_WindWake->WindWake[Count].Lvert[14][1].z = Q_WindWake->WindWake[Count].VertT85.z;


			Q_WindWake->WindWake[Count].Lvert[14][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[14][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[14][2].x = Q_WindWake->WindWake[Count].VertB85.x;
			Q_WindWake->WindWake[Count].Lvert[14][2].y = Q_WindWake->WindWake[Count].VertB85.y;
			Q_WindWake->WindWake[Count].Lvert[14][2].z = Q_WindWake->WindWake[Count].VertB85.z;


			Q_WindWake->WindWake[Count].Lvert[14][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[14][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[14][3].x = Q_WindWake->WindWake[Count].VertB8.x;
			Q_WindWake->WindWake[Count].Lvert[14][3].y = Q_WindWake->WindWake[Count].VertB8.y;
			Q_WindWake->WindWake[Count].Lvert[14][3].z = Q_WindWake->WindWake[Count].VertB8.z;


			Q_WindWake->WindWake[Count].Lvert[15][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[15][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[15][0].x = Q_WindWake->WindWake[Count].VertT85.x;
			Q_WindWake->WindWake[Count].Lvert[15][0].y = Q_WindWake->WindWake[Count].VertT85.y;
			Q_WindWake->WindWake[Count].Lvert[15][0].z = Q_WindWake->WindWake[Count].VertT85.z;


			Q_WindWake->WindWake[Count].Lvert[15][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[15][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[15][1].x = Q_WindWake->WindWake[Count].VertT1.x;
			Q_WindWake->WindWake[Count].Lvert[15][1].y = Q_WindWake->WindWake[Count].VertT1.y;
			Q_WindWake->WindWake[Count].Lvert[15][1].z = Q_WindWake->WindWake[Count].VertT1.z;


			Q_WindWake->WindWake[Count].Lvert[15][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[15][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[15][2].x = Q_WindWake->WindWake[Count].VertB1.x;
			Q_WindWake->WindWake[Count].Lvert[15][2].y = Q_WindWake->WindWake[Count].VertB1.y;
			Q_WindWake->WindWake[Count].Lvert[15][2].z = Q_WindWake->WindWake[Count].VertB1.z;


			Q_WindWake->WindWake[Count].Lvert[15][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[15][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[15][3].x = Q_WindWake->WindWake[Count].VertB85.x;
			Q_WindWake->WindWake[Count].Lvert[15][3].y = Q_WindWake->WindWake[Count].VertB85.y;
			Q_WindWake->WindWake[Count].Lvert[15][3].z = Q_WindWake->WindWake[Count].VertB85.z;


			if(player[g_Player]->Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 15)
					{
					Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;


		case 4:	//WindWake Ring Trail [Static Non Correctional]
			{
			if(Count != player[g_Player]->NomTriEffect - 1)
				{
				player[g_Player]->Q_TexTriEffect[Count].VertT1 = player[g_Player]->Q_TexTriEffect[Count+1].VertB1;
				player[g_Player]->Q_TexTriEffect[Count].VertT2 = player[g_Player]->Q_TexTriEffect[Count+1].VertB2;
				player[g_Player]->Q_TexTriEffect[Count].VertT3 = player[g_Player]->Q_TexTriEffect[Count+1].VertB3;
				player[g_Player]->Q_TexTriEffect[Count].VertT4 = player[g_Player]->Q_TexTriEffect[Count+1].VertB4;
				player[g_Player]->Q_TexTriEffect[Count].VertT5 = player[g_Player]->Q_TexTriEffect[Count+1].VertB5;
				player[g_Player]->Q_TexTriEffect[Count].VertT6 = player[g_Player]->Q_TexTriEffect[Count+1].VertB6;
				player[g_Player]->Q_TexTriEffect[Count].VertT7 = player[g_Player]->Q_TexTriEffect[Count+1].VertB7;
				player[g_Player]->Q_TexTriEffect[Count].VertT8 = player[g_Player]->Q_TexTriEffect[Count+1].VertB8;
				player[g_Player]->Q_TexTriEffect[Count].VertT15 = player[g_Player]->Q_TexTriEffect[Count+1].VertB15;
				player[g_Player]->Q_TexTriEffect[Count].VertT25 = player[g_Player]->Q_TexTriEffect[Count+1].VertB25;
				player[g_Player]->Q_TexTriEffect[Count].VertT35 = player[g_Player]->Q_TexTriEffect[Count+1].VertB35;
				player[g_Player]->Q_TexTriEffect[Count].VertT45 = player[g_Player]->Q_TexTriEffect[Count+1].VertB45;
				player[g_Player]->Q_TexTriEffect[Count].VertT55 = player[g_Player]->Q_TexTriEffect[Count+1].VertB55;
				player[g_Player]->Q_TexTriEffect[Count].VertT65 = player[g_Player]->Q_TexTriEffect[Count+1].VertB65;
				player[g_Player]->Q_TexTriEffect[Count].VertT75 = player[g_Player]->Q_TexTriEffect[Count+1].VertB75;
				player[g_Player]->Q_TexTriEffect[Count].VertT85 = player[g_Player]->Q_TexTriEffect[Count+1].VertB85;
				}


			player[g_Player]->Q_TexTriEffect[Count].MaterialCNT++;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT < 82) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;
			if(player[g_Player]->Q_TexTriEffect[Count].MaterialCNT > 96) player[g_Player]->Q_TexTriEffect[Count].MaterialCNT = 82;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			player[g_Player]->Q_TexTriEffect[Count].Alpha -= 6;
			if(player[g_Player]->Q_TexTriEffect[Count].Alpha < 0)
				{
				player[g_Player]->Q_TexTriEffect[Count].Alpha = 0;
				player[g_Player]->Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < player[g_Player]->NomTriEffect - 1)
					{
					player[g_Player]->Q_TexTriEffect[K] = player[g_Player]->Q_TexTriEffect[K+1];
					K++;
					}

				player[g_Player]->NomTriEffect--;
				}

			if(player[g_Player]->Q_TexTriEffect[Count].Green > 80)
				{
				player[g_Player]->Q_TexTriEffect[Count].Red += 3*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Red > 255) player[g_Player]->Q_TexTriEffect[Count].Red = 255;
				player[g_Player]->Q_TexTriEffect[Count].Green += 3*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Green > 255) player[g_Player]->Q_TexTriEffect[Count].Green = 255;
				}
			else
				{
				player[g_Player]->Q_TexTriEffect[Count].Red -= 10*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Red < 0) player[g_Player]->Q_TexTriEffect[Count].Red = 0;
				player[g_Player]->Q_TexTriEffect[Count].Green -= 10*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Green < 0) player[g_Player]->Q_TexTriEffect[Count].Green = 0;
				player[g_Player]->Q_TexTriEffect[Count].Blue -= 10*_->TimeScale;
				if(player[g_Player]->Q_TexTriEffect[Count].Blue < 0) player[g_Player]->Q_TexTriEffect[Count].Blue = 0;
				}


			//##### Move Bottom Verts of Trail Back and Out
			//player[g_Player]->Q_TexTriEffect[Count].LengthDist += 0.05;
			player[g_Player]->Q_TexTriEffect[Count].ExpandDist += 0.004;

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB1, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB2, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB3, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB4, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB5, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB6, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB7, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB8, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB8);


			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB15, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB1, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB15, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB15);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB25, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB2, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB25, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB25);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB35, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB3, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB35, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB35);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB45, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB4, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB45, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB45);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB55, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB5, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB55, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB55);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB65, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB6, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB65, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB65);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB75, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB7, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB75, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB75);

			Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[Count].VertB85, &player[g_Player]->Q_TexTriEffect[Count].PosB, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB8, -player[g_Player]->Q_TexTriEffect[Count].LengthDist, &player[g_Player]->Q_TexTriEffect[Count].VecIn, &player[g_Player]->Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[Count].VertB85, player[g_Player]->Q_TexTriEffect[Count].ExpandDist, &player[g_Player]->Q_TexTriEffect[Count].ExpandVec, &player[g_Player]->Q_TexTriEffect[Count].VertB85);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 15 )
				{
				int b=0;
				while( b <= 3 )
					{
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].a = player[g_Player]->Q_TexTriEffect[Count].Alpha;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].b = player[g_Player]->Q_TexTriEffect[Count].Blue;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].g = player[g_Player]->Q_TexTriEffect[Count].Green;
					player[g_Player]->Q_TexTriEffect[Count].Lvert[a][b].r = player[g_Player]->Q_TexTriEffect[Count].Red;
					b++;
					}
				a++;
				}


			//##### - SOLID RING VERTS

			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;

			
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT15.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB15.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[0][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT15.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB15.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB15.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[1][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB15.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT2.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT25.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB25.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB2.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB2.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[2][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB2.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT25.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB25.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB25.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[3][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB25.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT3.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT35.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB35.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB3.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB3.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[4][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB3.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT35.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB35.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB35.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[5][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB35.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT4.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT45.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB45.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB4.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB4.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[6][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB4.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT45.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT5.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB5.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB45.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB45.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[7][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB45.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT5.z;

			
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT55.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB55.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB5.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB5.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[8][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB5.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT55.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT6.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB6.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB55.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB55.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[9][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB55.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT6.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT65.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB65.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB6.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB6.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[10][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB6.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT65.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT7.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB7.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB65.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB65.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[11][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB65.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT7.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT75.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB75.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB7.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB7.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[12][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB7.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT75.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT8.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB8.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB75.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB75.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[13][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB75.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT8.z;

					
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT85.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB85.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB8.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB8.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[14][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB8.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].x = player[g_Player]->Q_TexTriEffect[Count].VertT85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].y = player[g_Player]->Q_TexTriEffect[Count].VertT85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][0].z = player[g_Player]->Q_TexTriEffect[Count].VertT85.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].v = player[g_Player]->Q_TexTriEffect[Count].Ub;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].x = player[g_Player]->Q_TexTriEffect[Count].VertT1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].y = player[g_Player]->Q_TexTriEffect[Count].VertT1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][1].z = player[g_Player]->Q_TexTriEffect[Count].VertT1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].u = 1;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].x = player[g_Player]->Q_TexTriEffect[Count].VertB1.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].y = player[g_Player]->Q_TexTriEffect[Count].VertB1.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][2].z = player[g_Player]->Q_TexTriEffect[Count].VertB1.z;


			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].u = 0;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].v = player[g_Player]->Q_TexTriEffect[Count].Ut;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].x = player[g_Player]->Q_TexTriEffect[Count].VertB85.x;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].y = player[g_Player]->Q_TexTriEffect[Count].VertB85.y;
			player[g_Player]->Q_TexTriEffect[Count].Lvert[15][3].z = player[g_Player]->Q_TexTriEffect[Count].VertB85.z;


			if(player[g_Player]->Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 15)
					{
					Qpo->Poly_AddOnce(&player[g_Player]->Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->fire[player[g_Player]->Q_TexTriEffect[Count].MaterialCNT], player[g_Player]->Q_TexTriEffect[Count].PolyType, player[g_Player]->Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;

		}
	}


void Q_EFFCon::TexTriEffect_AvatarFrame(int Avatar, int Count)
	{
	switch(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].EffectType)
		{
		case 0:	//WindWake Ring Trail
			{
			if(Count != Q_Forge->Forge[Avatar].NomTriEffect - 1)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB1;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB2;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB3;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB4;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB5;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB6;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB7;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB8;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].Pos;
				}

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8;


			//##### Material Count
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT++;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT > 136) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 124;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha -= 4;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha < 0)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < Q_Forge->Forge[Avatar].NomTriEffect - 1)
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[K] = Q_Forge->Forge[Avatar].Q_TexTriEffect[K+1];
					K++;
					}

				Q_Forge->Forge[Avatar].NomTriEffect--;
				}

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green += 4;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green = 255;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red += 4;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red = 255;


			//##### Move Bottom Verts of Trail Back and Out
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist += 0.05;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist += 0.004;

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 7 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].a = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].b = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].g = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].r = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red;
					b++;
					}
				a++;
				}


			//##### - SOLID RING VERTS

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;

			
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;

			
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].u = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.z;


			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 7)
					{
					Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->Water[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;


		case 1:	//WindWake Ring Trail [Static Non Correctional]
			{
			if(Count != Q_Forge->Forge[Avatar].NomTriEffect - 1)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB1;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB2;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB3;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB4;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB5;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB6;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB7;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB8;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB15;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB25;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB35;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB45;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB55;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB65;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB75;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB85;
				}


			//##### Material Count
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT++;
			//if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT < 124) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 124;
			//if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT > 136) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 124;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT++;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT < 82) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 82;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT > 96) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 82;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha -= 6;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha < 0)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < Q_Forge->Forge[Avatar].NomTriEffect - 1)
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[K] = Q_Forge->Forge[Avatar].Q_TexTriEffect[K+1];
					K++;
					}

				Q_Forge->Forge[Avatar].NomTriEffect--;
				}

			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green > 80)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red += 3*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red = 255;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green += 3*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green = 255;
				}
			else
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red -= 10*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red < 0) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green -= 10*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green < 0) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue -= 10*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue < 0) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue = 0;
				}


			//##### Move Bottom Verts of Trail Back and Out
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist += 0.05;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist += 0.004;

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);


			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 15 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].a = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].b = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].g = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].r = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red;

					b++;
					}
				a++;
				}


			//##### - SOLID RING VERTS

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;

			
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT15.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB15.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT25.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB25.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT35.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB35.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT45.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB45.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5.z;

			
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT55.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[9][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB55.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[10][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT65.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[11][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB65.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[12][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT75.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[13][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB75.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8.z;

					
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[14][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][0].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT85.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][1].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][1].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ub;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][2].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;


			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][3].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][3].v = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Ut;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[15][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB85.z;


			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 15)
					{
					Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;

		case 2:	//##### Flame Trails
			{
			if(Count != Q_Forge->Forge[Avatar].NomTriEffect - 1)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB1;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB2;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB3;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB4;
				}

			//##### Material Count  Set this
				//Fire
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2++;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2 < 124) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2 = 124;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2 > 136) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2 = 124;

				//Energy
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT++;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT < 82) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 82;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT > 96) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 82;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha -= 30;	//80
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha < 0)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < Q_Forge->Forge[Avatar].NomTriEffect - 1)
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[K] = Q_Forge->Forge[Avatar].Q_TexTriEffect[K+1];
					K++;
					}

				Q_Forge->Forge[Avatar].NomTriEffect--;
				}


			/*if(Q_Forge->Forge[Avatar].Aposestate != 59)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green += 3*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green = 255;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red += 3*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red = 255;
				}
			else
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green -= 20*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green < 0) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red -= 20*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red < 0) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue -= 20*_->TimeScale;
				if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue < 0) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue = 0;
				}*/


			//##### Move Bottom Verts of Trail Back and Out
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist *= 5;

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);


			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4);


			int a=0;
			while( a <= 4 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].a = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].b = 255;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].g = 255;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}


			a=5;
			while( a <= 8 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].a = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha/6;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].b = 255;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].g = 255;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}


			//##### - START CAP	- FLAMES
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].u = 0.5;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;


			//##### - END CAP - FLAMES
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].u = 0.5;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			//##### - BOTTOM CAP - FLAMES
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].v = 0.1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].v = 0.1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;


			//##### - FRONT FLAT PANEL - FLAMES
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			//##### - BACK FLAT PANEL - FLAMES
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;



			//##### - START CAP	- ENERGY
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].u = 0.5;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;


			//##### - END CAP - ENERGY
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].u = 0.5;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			//##### - FRONT FLAT PANEL - ENERGY
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3.z;


			//##### - BACK FLAT PANEL - ENERGY
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].u = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][1].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4.z;
								
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].v = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][2].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4.z;

			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].u = 1;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].v = 0;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].x = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.x;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].y = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.y;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][3].z = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1.z;

			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live == 1)
				{
				//FLAMES
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[0][0], 3, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[1][0], 3, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[2][0], 4, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[3][0], 4, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[4][0], 4, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);

				//ENERGY
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[5][0], 3, Medias->Water[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[6][0], 3, Medias->Water[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[7][0], 4, Medias->Water[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[8][0], 4, Medias->Water[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT2], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
				}

			} break;

		case 3:	//Flame Ring Trail [Static Non Correctional]
			{
			if(Count != Q_Forge->Forge[Avatar].NomTriEffect - 1)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB1;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB2;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB3;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB4;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB5;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB6;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB7;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].VertB8;
				//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Pos = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count+1].Pos;
				}

			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT1;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT2;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT3;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT4;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT5;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT6;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT7;
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8 = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertT8;


			//##### Material Count
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT++;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT < 82) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 82;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT > 96) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT = 82;


			//########- Effect Progression
			//##### Decrease Alpha Value - Increase Colour
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha -= 6;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha < 0)
				{
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha = 0;
				Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < Q_Forge->Forge[Avatar].NomTriEffect - 1)
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[K] = Q_Forge->Forge[Avatar].Q_TexTriEffect[K+1];
					K++;
					}

				Q_Forge->Forge[Avatar].NomTriEffect--;
				}

			
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green += 3*_->TimeScale;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green = 255;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red += 3*_->TimeScale;
			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red > 255) Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red = 255;
			


			//##### Move Bottom Verts of Trail Back and Out
			//Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist += 0.05;
			Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist += 0.02;	//0.004

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB1);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB2);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB3);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB4);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB5);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB6);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB7);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PosB, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec);
			//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, -Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].LengthDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VecIn, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandDist, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].ExpandVec, &Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].VertB8);


			//##### - ALPHA VALUES AND COLOUR
			int a=0;
			while( a <= 15 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].a = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Alpha;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].b = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Blue;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].g = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Green;
					Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[a][b].r = Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Red;
					b++;
					}
				a++;
				}


			//##### - SOLID RING TWO

			Q_WindWake->WindWake[Count].Lvert[0][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[0][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[0][0].x = Q_WindWake->WindWake[Count].VertT1.x;
			Q_WindWake->WindWake[Count].Lvert[0][0].y = Q_WindWake->WindWake[Count].VertT1.y;
			Q_WindWake->WindWake[Count].Lvert[0][0].z = Q_WindWake->WindWake[Count].VertT1.z;

			
			Q_WindWake->WindWake[Count].Lvert[0][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[0][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[0][1].x = Q_WindWake->WindWake[Count].VertT15.x;
			Q_WindWake->WindWake[Count].Lvert[0][1].y = Q_WindWake->WindWake[Count].VertT15.y;
			Q_WindWake->WindWake[Count].Lvert[0][1].z = Q_WindWake->WindWake[Count].VertT15.z;

					
			Q_WindWake->WindWake[Count].Lvert[0][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[0][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[0][2].x = Q_WindWake->WindWake[Count].VertB15.x;
			Q_WindWake->WindWake[Count].Lvert[0][2].y = Q_WindWake->WindWake[Count].VertB15.y;
			Q_WindWake->WindWake[Count].Lvert[0][2].z = Q_WindWake->WindWake[Count].VertB15.z;


			Q_WindWake->WindWake[Count].Lvert[0][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[0][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[0][3].x = Q_WindWake->WindWake[Count].VertB1.x;
			Q_WindWake->WindWake[Count].Lvert[0][3].y = Q_WindWake->WindWake[Count].VertB1.y;
			Q_WindWake->WindWake[Count].Lvert[0][3].z = Q_WindWake->WindWake[Count].VertB1.z;


			Q_WindWake->WindWake[Count].Lvert[1][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[1][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[1][0].x = Q_WindWake->WindWake[Count].VertT15.x;
			Q_WindWake->WindWake[Count].Lvert[1][0].y = Q_WindWake->WindWake[Count].VertT15.y;
			Q_WindWake->WindWake[Count].Lvert[1][0].z = Q_WindWake->WindWake[Count].VertT15.z;

					
			Q_WindWake->WindWake[Count].Lvert[1][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[1][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[1][1].x = Q_WindWake->WindWake[Count].VertT2.x;
			Q_WindWake->WindWake[Count].Lvert[1][1].y = Q_WindWake->WindWake[Count].VertT2.y;
			Q_WindWake->WindWake[Count].Lvert[1][1].z = Q_WindWake->WindWake[Count].VertT2.z;

					
			Q_WindWake->WindWake[Count].Lvert[1][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[1][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[1][2].x = Q_WindWake->WindWake[Count].VertB2.x;
			Q_WindWake->WindWake[Count].Lvert[1][2].y = Q_WindWake->WindWake[Count].VertB2.y;
			Q_WindWake->WindWake[Count].Lvert[1][2].z = Q_WindWake->WindWake[Count].VertB2.z;


			Q_WindWake->WindWake[Count].Lvert[1][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[1][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[1][3].x = Q_WindWake->WindWake[Count].VertB15.x;
			Q_WindWake->WindWake[Count].Lvert[1][3].y = Q_WindWake->WindWake[Count].VertB15.y;
			Q_WindWake->WindWake[Count].Lvert[1][3].z = Q_WindWake->WindWake[Count].VertB15.z;


			Q_WindWake->WindWake[Count].Lvert[2][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[2][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[2][0].x = Q_WindWake->WindWake[Count].VertT2.x;
			Q_WindWake->WindWake[Count].Lvert[2][0].y = Q_WindWake->WindWake[Count].VertT2.y;
			Q_WindWake->WindWake[Count].Lvert[2][0].z = Q_WindWake->WindWake[Count].VertT2.z;

					
			Q_WindWake->WindWake[Count].Lvert[2][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[2][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[2][1].x = Q_WindWake->WindWake[Count].VertT25.x;
			Q_WindWake->WindWake[Count].Lvert[2][1].y = Q_WindWake->WindWake[Count].VertT25.y;
			Q_WindWake->WindWake[Count].Lvert[2][1].z = Q_WindWake->WindWake[Count].VertT25.z;

					
			Q_WindWake->WindWake[Count].Lvert[2][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[2][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[2][2].x = Q_WindWake->WindWake[Count].VertB25.x;
			Q_WindWake->WindWake[Count].Lvert[2][2].y = Q_WindWake->WindWake[Count].VertB25.y;
			Q_WindWake->WindWake[Count].Lvert[2][2].z = Q_WindWake->WindWake[Count].VertB25.z;


			Q_WindWake->WindWake[Count].Lvert[2][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[2][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[2][3].x = Q_WindWake->WindWake[Count].VertB2.x;
			Q_WindWake->WindWake[Count].Lvert[2][3].y = Q_WindWake->WindWake[Count].VertB2.y;
			Q_WindWake->WindWake[Count].Lvert[2][3].z = Q_WindWake->WindWake[Count].VertB2.z;



			Q_WindWake->WindWake[Count].Lvert[3][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[3][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[3][0].x = Q_WindWake->WindWake[Count].VertT25.x;
			Q_WindWake->WindWake[Count].Lvert[3][0].y = Q_WindWake->WindWake[Count].VertT25.y;
			Q_WindWake->WindWake[Count].Lvert[3][0].z = Q_WindWake->WindWake[Count].VertT25.z;

					
			Q_WindWake->WindWake[Count].Lvert[3][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[3][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[3][1].x = Q_WindWake->WindWake[Count].VertT3.x;
			Q_WindWake->WindWake[Count].Lvert[3][1].y = Q_WindWake->WindWake[Count].VertT3.y;
			Q_WindWake->WindWake[Count].Lvert[3][1].z = Q_WindWake->WindWake[Count].VertT3.z;

					
			Q_WindWake->WindWake[Count].Lvert[3][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[3][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[3][2].x = Q_WindWake->WindWake[Count].VertB3.x;
			Q_WindWake->WindWake[Count].Lvert[3][2].y = Q_WindWake->WindWake[Count].VertB3.y;
			Q_WindWake->WindWake[Count].Lvert[3][2].z = Q_WindWake->WindWake[Count].VertB3.z;


			Q_WindWake->WindWake[Count].Lvert[3][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[3][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[3][3].x = Q_WindWake->WindWake[Count].VertB25.x;
			Q_WindWake->WindWake[Count].Lvert[3][3].y = Q_WindWake->WindWake[Count].VertB25.y;
			Q_WindWake->WindWake[Count].Lvert[3][3].z = Q_WindWake->WindWake[Count].VertB25.z;


			Q_WindWake->WindWake[Count].Lvert[4][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[4][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[4][0].x = Q_WindWake->WindWake[Count].VertT3.x;
			Q_WindWake->WindWake[Count].Lvert[4][0].y = Q_WindWake->WindWake[Count].VertT3.y;
			Q_WindWake->WindWake[Count].Lvert[4][0].z = Q_WindWake->WindWake[Count].VertT3.z;

					
			Q_WindWake->WindWake[Count].Lvert[4][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[4][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[4][1].x = Q_WindWake->WindWake[Count].VertT35.x;
			Q_WindWake->WindWake[Count].Lvert[4][1].y = Q_WindWake->WindWake[Count].VertT35.y;
			Q_WindWake->WindWake[Count].Lvert[4][1].z = Q_WindWake->WindWake[Count].VertT35.z;

					
			Q_WindWake->WindWake[Count].Lvert[4][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[4][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[4][2].x = Q_WindWake->WindWake[Count].VertB35.x;
			Q_WindWake->WindWake[Count].Lvert[4][2].y = Q_WindWake->WindWake[Count].VertB35.y;
			Q_WindWake->WindWake[Count].Lvert[4][2].z = Q_WindWake->WindWake[Count].VertB35.z;


			Q_WindWake->WindWake[Count].Lvert[4][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[4][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[4][3].x = Q_WindWake->WindWake[Count].VertB3.x;
			Q_WindWake->WindWake[Count].Lvert[4][3].y = Q_WindWake->WindWake[Count].VertB3.y;
			Q_WindWake->WindWake[Count].Lvert[4][3].z = Q_WindWake->WindWake[Count].VertB3.z;


			Q_WindWake->WindWake[Count].Lvert[5][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[5][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[5][0].x = Q_WindWake->WindWake[Count].VertT35.x;
			Q_WindWake->WindWake[Count].Lvert[5][0].y = Q_WindWake->WindWake[Count].VertT35.y;
			Q_WindWake->WindWake[Count].Lvert[5][0].z = Q_WindWake->WindWake[Count].VertT35.z;

					
			Q_WindWake->WindWake[Count].Lvert[5][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[5][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[5][1].x = Q_WindWake->WindWake[Count].VertT4.x;
			Q_WindWake->WindWake[Count].Lvert[5][1].y = Q_WindWake->WindWake[Count].VertT4.y;
			Q_WindWake->WindWake[Count].Lvert[5][1].z = Q_WindWake->WindWake[Count].VertT4.z;

					
			Q_WindWake->WindWake[Count].Lvert[5][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[5][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[5][2].x = Q_WindWake->WindWake[Count].VertB4.x;
			Q_WindWake->WindWake[Count].Lvert[5][2].y = Q_WindWake->WindWake[Count].VertB4.y;
			Q_WindWake->WindWake[Count].Lvert[5][2].z = Q_WindWake->WindWake[Count].VertB4.z;


			Q_WindWake->WindWake[Count].Lvert[5][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[5][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[5][3].x = Q_WindWake->WindWake[Count].VertB35.x;
			Q_WindWake->WindWake[Count].Lvert[5][3].y = Q_WindWake->WindWake[Count].VertB35.y;
			Q_WindWake->WindWake[Count].Lvert[5][3].z = Q_WindWake->WindWake[Count].VertB35.z;


			Q_WindWake->WindWake[Count].Lvert[6][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[6][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[6][0].x = Q_WindWake->WindWake[Count].VertT4.x;
			Q_WindWake->WindWake[Count].Lvert[6][0].y = Q_WindWake->WindWake[Count].VertT4.y;
			Q_WindWake->WindWake[Count].Lvert[6][0].z = Q_WindWake->WindWake[Count].VertT4.z;

					
			Q_WindWake->WindWake[Count].Lvert[6][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[6][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[6][1].x = Q_WindWake->WindWake[Count].VertT45.x;
			Q_WindWake->WindWake[Count].Lvert[6][1].y = Q_WindWake->WindWake[Count].VertT45.y;
			Q_WindWake->WindWake[Count].Lvert[6][1].z = Q_WindWake->WindWake[Count].VertT45.z;

					
			Q_WindWake->WindWake[Count].Lvert[6][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[6][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[6][2].x = Q_WindWake->WindWake[Count].VertB45.x;
			Q_WindWake->WindWake[Count].Lvert[6][2].y = Q_WindWake->WindWake[Count].VertB45.y;
			Q_WindWake->WindWake[Count].Lvert[6][2].z = Q_WindWake->WindWake[Count].VertB45.z;


			Q_WindWake->WindWake[Count].Lvert[6][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[6][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[6][3].x = Q_WindWake->WindWake[Count].VertB4.x;
			Q_WindWake->WindWake[Count].Lvert[6][3].y = Q_WindWake->WindWake[Count].VertB4.y;
			Q_WindWake->WindWake[Count].Lvert[6][3].z = Q_WindWake->WindWake[Count].VertB4.z;


			Q_WindWake->WindWake[Count].Lvert[7][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[7][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[7][0].x = Q_WindWake->WindWake[Count].VertT45.x;
			Q_WindWake->WindWake[Count].Lvert[7][0].y = Q_WindWake->WindWake[Count].VertT45.y;
			Q_WindWake->WindWake[Count].Lvert[7][0].z = Q_WindWake->WindWake[Count].VertT45.z;

					
			Q_WindWake->WindWake[Count].Lvert[7][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[7][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[7][1].x = Q_WindWake->WindWake[Count].VertT5.x;
			Q_WindWake->WindWake[Count].Lvert[7][1].y = Q_WindWake->WindWake[Count].VertT5.y;
			Q_WindWake->WindWake[Count].Lvert[7][1].z = Q_WindWake->WindWake[Count].VertT5.z;

					
			Q_WindWake->WindWake[Count].Lvert[7][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[7][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[7][2].x = Q_WindWake->WindWake[Count].VertB5.x;
			Q_WindWake->WindWake[Count].Lvert[7][2].y = Q_WindWake->WindWake[Count].VertB5.y;
			Q_WindWake->WindWake[Count].Lvert[7][2].z = Q_WindWake->WindWake[Count].VertB5.z;


			Q_WindWake->WindWake[Count].Lvert[7][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[7][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[7][3].x = Q_WindWake->WindWake[Count].VertB45.x;
			Q_WindWake->WindWake[Count].Lvert[7][3].y = Q_WindWake->WindWake[Count].VertB45.y;
			Q_WindWake->WindWake[Count].Lvert[7][3].z = Q_WindWake->WindWake[Count].VertB45.z;


			Q_WindWake->WindWake[Count].Lvert[8][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[8][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[8][0].x = Q_WindWake->WindWake[Count].VertT5.x;
			Q_WindWake->WindWake[Count].Lvert[8][0].y = Q_WindWake->WindWake[Count].VertT5.y;
			Q_WindWake->WindWake[Count].Lvert[8][0].z = Q_WindWake->WindWake[Count].VertT5.z;

			
			Q_WindWake->WindWake[Count].Lvert[8][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[8][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[8][1].x = Q_WindWake->WindWake[Count].VertT55.x;
			Q_WindWake->WindWake[Count].Lvert[8][1].y = Q_WindWake->WindWake[Count].VertT55.y;
			Q_WindWake->WindWake[Count].Lvert[8][1].z = Q_WindWake->WindWake[Count].VertT55.z;

					
			Q_WindWake->WindWake[Count].Lvert[8][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[8][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[8][2].x = Q_WindWake->WindWake[Count].VertB55.x;
			Q_WindWake->WindWake[Count].Lvert[8][2].y = Q_WindWake->WindWake[Count].VertB55.y;
			Q_WindWake->WindWake[Count].Lvert[8][2].z = Q_WindWake->WindWake[Count].VertB55.z;


			Q_WindWake->WindWake[Count].Lvert[8][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[8][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[8][3].x = Q_WindWake->WindWake[Count].VertB5.x;
			Q_WindWake->WindWake[Count].Lvert[8][3].y = Q_WindWake->WindWake[Count].VertB5.y;
			Q_WindWake->WindWake[Count].Lvert[8][3].z = Q_WindWake->WindWake[Count].VertB5.z;


			Q_WindWake->WindWake[Count].Lvert[9][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[9][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[9][0].x = Q_WindWake->WindWake[Count].VertT55.x;
			Q_WindWake->WindWake[Count].Lvert[9][0].y = Q_WindWake->WindWake[Count].VertT55.y;
			Q_WindWake->WindWake[Count].Lvert[9][0].z = Q_WindWake->WindWake[Count].VertT55.z;

					
			Q_WindWake->WindWake[Count].Lvert[9][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[9][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[9][1].x = Q_WindWake->WindWake[Count].VertT6.x;
			Q_WindWake->WindWake[Count].Lvert[9][1].y = Q_WindWake->WindWake[Count].VertT6.y;
			Q_WindWake->WindWake[Count].Lvert[9][1].z = Q_WindWake->WindWake[Count].VertT6.z;

					
			Q_WindWake->WindWake[Count].Lvert[9][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[9][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[9][2].x = Q_WindWake->WindWake[Count].VertB6.x;
			Q_WindWake->WindWake[Count].Lvert[9][2].y = Q_WindWake->WindWake[Count].VertB6.y;
			Q_WindWake->WindWake[Count].Lvert[9][2].z = Q_WindWake->WindWake[Count].VertB6.z;


			Q_WindWake->WindWake[Count].Lvert[9][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[9][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[9][3].x = Q_WindWake->WindWake[Count].VertB55.x;
			Q_WindWake->WindWake[Count].Lvert[9][3].y = Q_WindWake->WindWake[Count].VertB55.y;
			Q_WindWake->WindWake[Count].Lvert[9][3].z = Q_WindWake->WindWake[Count].VertB55.z;


			Q_WindWake->WindWake[Count].Lvert[10][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[10][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[10][0].x = Q_WindWake->WindWake[Count].VertT6.x;
			Q_WindWake->WindWake[Count].Lvert[10][0].y = Q_WindWake->WindWake[Count].VertT6.y;
			Q_WindWake->WindWake[Count].Lvert[10][0].z = Q_WindWake->WindWake[Count].VertT6.z;

					
			Q_WindWake->WindWake[Count].Lvert[10][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[10][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[10][1].x = Q_WindWake->WindWake[Count].VertT65.x;
			Q_WindWake->WindWake[Count].Lvert[10][1].y = Q_WindWake->WindWake[Count].VertT65.y;
			Q_WindWake->WindWake[Count].Lvert[10][1].z = Q_WindWake->WindWake[Count].VertT65.z;

					
			Q_WindWake->WindWake[Count].Lvert[10][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[10][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[10][2].x = Q_WindWake->WindWake[Count].VertB65.x;
			Q_WindWake->WindWake[Count].Lvert[10][2].y = Q_WindWake->WindWake[Count].VertB65.y;
			Q_WindWake->WindWake[Count].Lvert[10][2].z = Q_WindWake->WindWake[Count].VertB65.z;


			Q_WindWake->WindWake[Count].Lvert[10][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[10][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[10][3].x = Q_WindWake->WindWake[Count].VertB6.x;
			Q_WindWake->WindWake[Count].Lvert[10][3].y = Q_WindWake->WindWake[Count].VertB6.y;
			Q_WindWake->WindWake[Count].Lvert[10][3].z = Q_WindWake->WindWake[Count].VertB6.z;


			Q_WindWake->WindWake[Count].Lvert[11][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[11][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[11][0].x = Q_WindWake->WindWake[Count].VertT65.x;
			Q_WindWake->WindWake[Count].Lvert[11][0].y = Q_WindWake->WindWake[Count].VertT65.y;
			Q_WindWake->WindWake[Count].Lvert[11][0].z = Q_WindWake->WindWake[Count].VertT65.z;

					
			Q_WindWake->WindWake[Count].Lvert[11][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[11][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[11][1].x = Q_WindWake->WindWake[Count].VertT7.x;
			Q_WindWake->WindWake[Count].Lvert[11][1].y = Q_WindWake->WindWake[Count].VertT7.y;
			Q_WindWake->WindWake[Count].Lvert[11][1].z = Q_WindWake->WindWake[Count].VertT7.z;

					
			Q_WindWake->WindWake[Count].Lvert[11][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[11][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[11][2].x = Q_WindWake->WindWake[Count].VertB7.x;
			Q_WindWake->WindWake[Count].Lvert[11][2].y = Q_WindWake->WindWake[Count].VertB7.y;
			Q_WindWake->WindWake[Count].Lvert[11][2].z = Q_WindWake->WindWake[Count].VertB7.z;


			Q_WindWake->WindWake[Count].Lvert[11][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[11][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[11][3].x = Q_WindWake->WindWake[Count].VertB65.x;
			Q_WindWake->WindWake[Count].Lvert[11][3].y = Q_WindWake->WindWake[Count].VertB65.y;
			Q_WindWake->WindWake[Count].Lvert[11][3].z = Q_WindWake->WindWake[Count].VertB65.z;


			Q_WindWake->WindWake[Count].Lvert[12][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[12][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[12][0].x = Q_WindWake->WindWake[Count].VertT7.x;
			Q_WindWake->WindWake[Count].Lvert[12][0].y = Q_WindWake->WindWake[Count].VertT7.y;
			Q_WindWake->WindWake[Count].Lvert[12][0].z = Q_WindWake->WindWake[Count].VertT7.z;

					
			Q_WindWake->WindWake[Count].Lvert[12][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[12][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[12][1].x = Q_WindWake->WindWake[Count].VertT75.x;
			Q_WindWake->WindWake[Count].Lvert[12][1].y = Q_WindWake->WindWake[Count].VertT75.y;
			Q_WindWake->WindWake[Count].Lvert[12][1].z = Q_WindWake->WindWake[Count].VertT75.z;

					
			Q_WindWake->WindWake[Count].Lvert[12][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[12][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[12][2].x = Q_WindWake->WindWake[Count].VertB75.x;
			Q_WindWake->WindWake[Count].Lvert[12][2].y = Q_WindWake->WindWake[Count].VertB75.y;
			Q_WindWake->WindWake[Count].Lvert[12][2].z = Q_WindWake->WindWake[Count].VertB75.z;


			Q_WindWake->WindWake[Count].Lvert[12][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[12][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[12][3].x = Q_WindWake->WindWake[Count].VertB7.x;
			Q_WindWake->WindWake[Count].Lvert[12][3].y = Q_WindWake->WindWake[Count].VertB7.y;
			Q_WindWake->WindWake[Count].Lvert[13][3].z = Q_WindWake->WindWake[Count].VertB7.z;


			Q_WindWake->WindWake[Count].Lvert[13][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[13][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[13][0].x = Q_WindWake->WindWake[Count].VertT75.x;
			Q_WindWake->WindWake[Count].Lvert[13][0].y = Q_WindWake->WindWake[Count].VertT75.y;
			Q_WindWake->WindWake[Count].Lvert[13][0].z = Q_WindWake->WindWake[Count].VertT75.z;

					
			Q_WindWake->WindWake[Count].Lvert[13][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[13][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[13][1].x = Q_WindWake->WindWake[Count].VertT8.x;
			Q_WindWake->WindWake[Count].Lvert[13][1].y = Q_WindWake->WindWake[Count].VertT8.y;
			Q_WindWake->WindWake[Count].Lvert[13][1].z = Q_WindWake->WindWake[Count].VertT8.z;

					
			Q_WindWake->WindWake[Count].Lvert[13][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[13][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[13][2].x = Q_WindWake->WindWake[Count].VertB8.x;
			Q_WindWake->WindWake[Count].Lvert[13][2].y = Q_WindWake->WindWake[Count].VertB8.y;
			Q_WindWake->WindWake[Count].Lvert[13][2].z = Q_WindWake->WindWake[Count].VertB8.z;


			Q_WindWake->WindWake[Count].Lvert[13][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[13][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[13][3].x = Q_WindWake->WindWake[Count].VertB75.x;
			Q_WindWake->WindWake[Count].Lvert[13][3].y = Q_WindWake->WindWake[Count].VertB75.y;
			Q_WindWake->WindWake[Count].Lvert[13][3].z = Q_WindWake->WindWake[Count].VertB75.z;


			Q_WindWake->WindWake[Count].Lvert[14][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[14][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[14][0].x = Q_WindWake->WindWake[Count].VertT8.x;
			Q_WindWake->WindWake[Count].Lvert[14][0].y = Q_WindWake->WindWake[Count].VertT8.y;
			Q_WindWake->WindWake[Count].Lvert[14][0].z = Q_WindWake->WindWake[Count].VertT8.z;

					
			Q_WindWake->WindWake[Count].Lvert[14][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[14][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[14][1].x = Q_WindWake->WindWake[Count].VertT85.x;
			Q_WindWake->WindWake[Count].Lvert[14][1].y = Q_WindWake->WindWake[Count].VertT85.y;
			Q_WindWake->WindWake[Count].Lvert[14][1].z = Q_WindWake->WindWake[Count].VertT85.z;


			Q_WindWake->WindWake[Count].Lvert[14][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[14][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[14][2].x = Q_WindWake->WindWake[Count].VertB85.x;
			Q_WindWake->WindWake[Count].Lvert[14][2].y = Q_WindWake->WindWake[Count].VertB85.y;
			Q_WindWake->WindWake[Count].Lvert[14][2].z = Q_WindWake->WindWake[Count].VertB85.z;


			Q_WindWake->WindWake[Count].Lvert[14][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[14][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[14][3].x = Q_WindWake->WindWake[Count].VertB8.x;
			Q_WindWake->WindWake[Count].Lvert[14][3].y = Q_WindWake->WindWake[Count].VertB8.y;
			Q_WindWake->WindWake[Count].Lvert[14][3].z = Q_WindWake->WindWake[Count].VertB8.z;


			Q_WindWake->WindWake[Count].Lvert[15][0].u = 0;
			Q_WindWake->WindWake[Count].Lvert[15][0].v = 0;
			Q_WindWake->WindWake[Count].Lvert[15][0].x = Q_WindWake->WindWake[Count].VertT85.x;
			Q_WindWake->WindWake[Count].Lvert[15][0].y = Q_WindWake->WindWake[Count].VertT85.y;
			Q_WindWake->WindWake[Count].Lvert[15][0].z = Q_WindWake->WindWake[Count].VertT85.z;


			Q_WindWake->WindWake[Count].Lvert[15][1].u = 1;
			Q_WindWake->WindWake[Count].Lvert[15][1].v = 0;
			Q_WindWake->WindWake[Count].Lvert[15][1].x = Q_WindWake->WindWake[Count].VertT1.x;
			Q_WindWake->WindWake[Count].Lvert[15][1].y = Q_WindWake->WindWake[Count].VertT1.y;
			Q_WindWake->WindWake[Count].Lvert[15][1].z = Q_WindWake->WindWake[Count].VertT1.z;


			Q_WindWake->WindWake[Count].Lvert[15][2].u = 1;
			Q_WindWake->WindWake[Count].Lvert[15][2].v = 1;
			Q_WindWake->WindWake[Count].Lvert[15][2].x = Q_WindWake->WindWake[Count].VertB1.x;
			Q_WindWake->WindWake[Count].Lvert[15][2].y = Q_WindWake->WindWake[Count].VertB1.y;
			Q_WindWake->WindWake[Count].Lvert[15][2].z = Q_WindWake->WindWake[Count].VertB1.z;


			Q_WindWake->WindWake[Count].Lvert[15][3].u = 0;
			Q_WindWake->WindWake[Count].Lvert[15][3].v = 1;
			Q_WindWake->WindWake[Count].Lvert[15][3].x = Q_WindWake->WindWake[Count].VertB85.x;
			Q_WindWake->WindWake[Count].Lvert[15][3].y = Q_WindWake->WindWake[Count].VertB85.y;
			Q_WindWake->WindWake[Count].Lvert[15][3].z = Q_WindWake->WindWake[Count].VertB85.z;

			if(Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Live == 1)
				{
				int i = 0;
				while(i <= 15)
					{
					Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].Lvert[i][0], 4, Medias->fire[Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].MaterialCNT], Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].PolyType, Q_Forge->Forge[Avatar].Q_TexTriEffect[Count].RenderFlags, 1.0f);
					i++;
					}
				}

			} break;

		}

	}//END Live

};