/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Pin Effect Meshes-

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
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-ENE-EnergyTypes.h"

using namespace GVARS;

namespace GVARS
{

	//------******[  <RENDER PIN EFFECT MESHES>------[EFFECTS RENDERING COMPONENT]  ]******------
	
void Q_EFFCon::PinEffectMesh_ControlFrame(int Count)
	{
	switch(Q_PinEffectMesh->PinEffectMesh[Count].EffectType)
		{
		case 0:	//##### Carpet Single Face Effect
			{
			//##### Control Mesh Effects
			Q.PEF_CONTROL_FaceRippleMesh(Count);

			//##### Single Face No 1
			helly=0;

			while(helly < Q_PinEffectMesh->PinEffectMesh[Count].MaxNumY)
				{
				jet=0;
				while(jet < Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX)
					{
					//##### Active Cell
					//##### Material Count		TODO SET VALUES ELSEWHERE PROGRESSIVELY HERE
					//WATER
					//Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					//if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 136) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;

					Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] < 82) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 82;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 96) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 82;


					//########- Effect Progression		-interesting Ideas with sliding alpha values
					//##### Decrease Alpha Value - Increase Colour
					/*Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] -= 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] < 0)
						{
						Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] = 0;
						}*/

					//##### Alter Colour Values -
					/*Q_PinEffectMesh->PinEffectMesh[Count].Green += 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].Green > 255) Q_PinEffectMesh->PinEffectMesh[Count].Green = 255;
					Q_PinEffectMesh->PinEffectMesh[Count].Red += 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].Red > 255) Q_PinEffectMesh->PinEffectMesh[Count].Red = 255;*/


					//##### - ALPHA VALUES AND COLOUR  TODO at present individual tris around cell all the same
					int a=0;
					while( a <= 3 )
						{
						int b=0;
						while( b <= 2 )
							{
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].a = Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].b = Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].g = Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].r = Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly];
							b++;
							}
						a++;
						}
			

					//##### - FIRST TRI
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;


					//##### - SECOND TRI
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;
							
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
							
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;


					//##### - THIRD TRI
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;
							
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
							
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


					//##### - FOURTH TRI
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
							
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
							
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
					Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;


					if(Q_PinEffectMesh->PinEffectMesh[Count].CellLive[0][jet][helly] == 1)
						{
						int i = 0;
						while(i <= 3)
							{
							Qpo->Poly_AddOnce(&Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][i][0], 3, Medias->fire[Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]]/*Medias->Water[Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]]*/, Q_PinEffectMesh->PinEffectMesh[Count].PolyType, Q_PinEffectMesh->PinEffectMesh[Count].RenderFlags, 1.0f);
							i++;
							}
						}

					//Increment X  ->'jet'
					jet++;
					}

				//Increment Y  ->'helly'
				helly++;
				}

			} break;


		case 1:	//##### Ring PEF Mesh
			{

			//##### Control Mesh Effects
			Q.PEF_CONTROL_RingRippleMesh(Count);

			//##### Single Face No 1
			helly=0;
			while(helly < Q_PinEffectMesh->PinEffectMesh[Count].NoMLines)
				{
				jet=0;
				while(jet < Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX)
					{
					//##### Active Cell
					//##### Material Count		TODO SET VALUES ELSEWHERE PROGRESSIVELY HERE
					//WATER
					//Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					//if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 136) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;

					Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] < 82) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 82;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 96) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 82;


					//########- Effect Progression		-interesting Ideas with sliding alpha values
					//##### Decrease Alpha Value - Increase Colour
					Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] -= 55;	//9
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] < 0)
						{
						Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] = 0;
						Q_PinEffectMesh->PinEffectMesh[Count].CellLive[0][jet][helly] = 0;
						}

					//##### Alter Colour Values -
					/*Q_PinEffectMesh->PinEffectMesh[Count].Green += 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].Green > 255) Q_PinEffectMesh->PinEffectMesh[Count].Green = 255;
					Q_PinEffectMesh->PinEffectMesh[Count].Red += 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].Red > 255) Q_PinEffectMesh->PinEffectMesh[Count].Red = 255;*/


					//##### - ALPHA VALUES AND COLOUR  TODO at present individual tris around cell all the same
					int a=0;
					while( a <= 3 )
						{
						int b=0;
						while( b <= 2 )
							{
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].a = Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].b = Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].g = Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].r = Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly];
							b++;
							}
						a++;
						}
			
					if(helly != Q_PinEffectMesh->PinEffectMesh[Count].NoMLines - 1)
						{
						if(jet != Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX - 1)
							{
							//##### - FIRST TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;


							//##### - SECOND TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;


							//##### - THIRD TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


							//##### - FOURTH TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;
							}
						else	//Wrap Ends Together
							{
							//##### - FIRST TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].z;


							//##### - SECOND TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].z;


							//##### - THIRD TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


							//##### - FOURTH TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;
							}
						}


					if(Q_PinEffectMesh->PinEffectMesh[Count].CellLive[0][jet][helly] == 1)
						{
						int i = 0;
						while(i <= 3)
							{
							Qpo->Poly_AddOnce(&Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][i][0], 3, Medias->FlameSingle/*Medias->fire[Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]]/*Medias->Water[Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]]*/, Q_PinEffectMesh->PinEffectMesh[Count].PolyType, Q_PinEffectMesh->PinEffectMesh[Count].RenderFlags, 1.0f);
							i++;
							}
						}

					//Increment X  ->'jet'
					jet++;
					}

				//Increment Y  ->'helly'
				helly++;
				}

			} break;


		case 2:	//##### Spherical PEF Mesh
			{

			//##### Control Mesh Effects
			Q.PEF_CONTROL_RingShieldSphere(Count);

			//##### Single Face No 1
			helly=0;
			while(helly < Q_PinEffectMesh->PinEffectMesh[Count].NoMLines)
				{
				jet=0;
				while(jet < Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX)
					{
					//##### Active Cell
					//##### Material Count		TODO SET VALUES ELSEWHERE PROGRESSIVELY HERE
					//WATER
					//Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					//if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 136) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;

					Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] < 124) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 136) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;


					//########- Effect Progression		-interesting Ideas with sliding alpha values
					//##### Decrease Alpha Value - Increase Colour
					/*Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] -= 55;	//9
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] < 0)
						{
						Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] = 0;
						Q_PinEffectMesh->PinEffectMesh[Count].CellLive[0][jet][helly] = 0;
						}*/

					//##### Alter Colour Values -
					/*Q_PinEffectMesh->PinEffectMesh[Count].Green += 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].Green > 255) Q_PinEffectMesh->PinEffectMesh[Count].Green = 255;
					Q_PinEffectMesh->PinEffectMesh[Count].Red += 4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].Red > 255) Q_PinEffectMesh->PinEffectMesh[Count].Red = 255;*/


					//##### - ALPHA VALUES AND COLOUR  TODO at present individual tris around cell all the same
					int a=0;
					while( a <= 3 )
						{
						int b=0;
						while( b <= 2 )
							{
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].a = 120;//Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].b = Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].g = Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].r = Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly];
							b++;
							}
						a++;
						}
			
					if(helly != Q_PinEffectMesh->PinEffectMesh[Count].NoMLines - 1)
						{
						if(jet != Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX - 1)
							{
							//##### - FIRST TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;


							//##### - SECOND TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;


							//##### - THIRD TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


							//##### - FOURTH TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;
							}
						else	//Wrap Ends Together
							{
							//##### - FIRST TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].z;


							//##### - SECOND TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].z;


							//##### - THIRD TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


							//##### - FOURTH TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;
							}
						}


					if(Q_PinEffectMesh->PinEffectMesh[Count].CellLive[0][jet][helly] == 1)
						{
						int i = 0;
						while(i <= 3)
							{
							Qpo->Poly_AddOnce(&Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][i][0], 3, Medias->Water[Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]], Q_PinEffectMesh->PinEffectMesh[Count].PolyType, Q_PinEffectMesh->PinEffectMesh[Count].RenderFlags, 1.0f);
							i++;
							}
						}

					//Increment X  ->'jet'
					jet++;
					}

				//Increment Y  ->'helly'
				helly++;
				}

			} break;


		case 3:	//##### Energy Wake
			{

			//##### Control Mesh Effects
			Q.PEF_CONTROL_EnergyWake(Count);

			//##### Single Face No 1
			helly=0;
			while(helly < Q_PinEffectMesh->PinEffectMesh[Count].NoMLines)
				{
				//##### Decrease Alpha Value - Increase Colour
				if(Q_PinEffectMesh->PinEffectMesh[Count].LineReleased[0][helly] == 1)
					{
					Q_PinEffectMesh->PinEffectMesh[Count].LineAlpha[0][helly] -= 0.4;
					if(Q_PinEffectMesh->PinEffectMesh[Count].LineAlpha[0][helly] < 0) Q_PinEffectMesh->PinEffectMesh[Count].LineAlpha[0][helly] = 0;
					}

				jet=0;
				while(jet < Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX)
					{
					//##### Active Cell
					//##### Material Count		TODO SET VALUES ELSEWHERE PROGRESSIVELY HERE
					//WATER
					//Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					//if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 136) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;

					Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]++;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] < 82) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;
					if(Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] > 96) Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly] = 124;


					//########- Effect Progression		-interesting Ideas with sliding alpha values
					//##### Alter Colour Values -
					if(Q_PinEffectMesh->PinEffectMesh[Count].LineReleased[0][helly] == 1)
						{
						Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly] -= 3;
						if(Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly] < 0) Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly] = 0;
						Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly] -= 3;
						if(Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly] < 0) Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly] = 0;
						Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly] -= 3;
						if(Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly] < 0) Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly] = 0;
						Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly] = Q_PinEffectMesh->PinEffectMesh[Count].LineAlpha[0][helly];
						}



					//##### - ALPHA VALUES AND COLOUR  TODO at present individual tris around cell all the same
					int a=0;
					while( a <= 3 )
						{
						int b=0;
						while( b <= 2 )
							{
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].a = Q_PinEffectMesh->PinEffectMesh[Count].CellAlpha[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].b = Q_PinEffectMesh->PinEffectMesh[Count].CellBlue[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].g = Q_PinEffectMesh->PinEffectMesh[Count].CellGreen[0][jet][helly];
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][a][b].r = Q_PinEffectMesh->PinEffectMesh[Count].CellRed[0][jet][helly];
							b++;
							}
						a++;
						}
			
					if(helly != Q_PinEffectMesh->PinEffectMesh[Count].NoMLines - 1)
						{
						if(jet != Q_PinEffectMesh->PinEffectMesh[Count].MaxNumX - 1)
							{
							//##### - FIRST TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;


							//##### - SECOND TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;


							//##### - THIRD TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet+1][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


							//##### - FOURTH TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;
							}
						else	//Wrap Ends Together
							{
							//##### - FIRST TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;

							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][0][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].z;


							//##### - SECOND TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][1][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].z;


							//##### - THIRD TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][0][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][2][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;


							//##### - FOURTH TRI
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].u = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][0].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly+1].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].u = 0.5;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].v = 0;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].x = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].y = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][1].z = Q_PinEffectMesh->PinEffectMesh[Count].CellVert1[0][jet][helly].z;
									
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].u = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].v = 1;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].x = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].x;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].y = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].y;
							Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][3][2].z = Q_PinEffectMesh->PinEffectMesh[Count].BaseVert[0][jet][helly].z;
							}
						}


					if(Q_PinEffectMesh->PinEffectMesh[Count].CellLive[0][jet][helly] == 1)
						{
						int i = 0;
						while(i <= 3)
							{
							Qpo->Poly_AddOnce(&Q_PinEffectMesh->PinEffectMesh[Count].Lvert[0][jet][helly][i][0], 3, Medias->fire[Q_PinEffectMesh->PinEffectMesh[Count].CellMaterialCNT[0][jet][helly]], Q_PinEffectMesh->PinEffectMesh[Count].PolyType, Q_PinEffectMesh->PinEffectMesh[Count].RenderFlags, 1.0f);
							i++;
							}
						}

					//Increment X  ->'jet'
					jet++;
					}

				//Increment Y  ->'helly'
				helly++;
				}

			} break;

		//<-- Insert New Effect Types Here
		}
	}


void Q_COREFunctions::PEF_CONTROL_EnergyWake(int MeshID)
	{
	//##### Single Face No 1
	helly = 0;
	while(helly < Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines)
		{
		//### Check For Line Stability
		if(Q_PinEffectMesh->PinEffectMesh[MeshID].LineReleased[0][helly] == 0)
			{
			//Q_PinEffectMesh->PinEffectMesh[MeshID].Distance = Qpo->Vec3d_DistanceBetween(&Q_PinEffectMesh->PinEffectMesh[MeshID].WakeStartPos, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][0][helly]);
			//### Determine if line should be released
			//if(Q_PinEffectMesh->PinEffectMesh[MeshID].Distance > 60)

			Q_PinEffectMesh->PinEffectMesh[MeshID].LineTimer[0][helly]++;

			if(Q_PinEffectMesh->PinEffectMesh[MeshID].LineTimer[0][helly] > 35)
				{
				Q_PinEffectMesh->PinEffectMesh[MeshID].LineReleased[0][helly] = 1;
				}
			else
				{
				Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], Q_LEnergy->LEnergy[0].Speed*_->TimeScale, &Q_LEnergy->LEnergy[0].TraVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly]);

				jet=0;
				while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
					{
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], Q_LEnergy->LEnergy[0].Speed*_->TimeScale, &Q_LEnergy->LEnergy[0].TraVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], Q_LEnergy->LEnergy[0].Speed*_->TimeScale, &Q_LEnergy->LEnergy[0].TraVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);

					//##### Active Base Vert
					Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
					//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], ((float)rand() / 32767)*0.05, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], -Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].FlowDir, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);

					//###### Spherize the Vert
					Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, Q_PinEffectMesh->PinEffectMesh[MeshID].SphereRadius, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);

					//##### Active Cell
					Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], -Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].FlowDir, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);

					//###### Spherize the Vert
					Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, Q_PinEffectMesh->PinEffectMesh[MeshID].SphereRadius, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);

					Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], ((float)rand() / 32767)*0.5, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);

					
					//Increment X  ->'jet'
					jet++;
					}

				//## Update Movement Variables
				Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly] *= 1.15;
				Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly] += 7;
				}
			}
		/*else	Separated Lines (Released)
			{

			}*/

		helly++;
		}
	}


//------******[  <RIPPLE EXPAND AND DROP DOWN RING PEF MESH>------[EFFECTS CONTROL ROUTINES]  ]******------

void Q_COREFunctions::PEF_CONTROL_RingRippleMesh(int MeshID)
	{
	//##### Single Face No 1
	helly = 0;
	while(helly < Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines)
		{
		jet=0;
		while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
			{
			//##### Active Base Vert
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], ((float)rand() / 32767)*0.05, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].y -= ((float)rand() / 32767)*1;
			//##### Active Cell
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], ((float)rand() / 32767)*0.05, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].y -= ((float)rand() / 32767)*1;
			//Increment X  ->'jet'

			//## Update Movement Variables
			Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly] += 0.02 + ((float)rand() / 32767)*0.2 - 0.1;
			jet++;
			}

		helly++;
		}



	//Pass increment downstream
	/*helly=0;
	helly = Q_PinEffectMesh->PinEffectMeshQ_PinEffectMesh->PinEffectMesh[MeshID].BaseXINC[0][jet][helly];
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].y += Q_PinEffectMesh->PinEffectMesh[MeshID].BaseYINC[0][jet][helly];
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].z += Q_PinEffectMesh->PinEffectMesh[MeshID].BaseZINC[0][jet][helly];

			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseXINC[0][jet][helly] += (((float)rand() / 32767)*4)-2;
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseYINC[0][jet][helly] += (((float)rand() / 32767)*4)-2;
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseZINC[0][jet][helly] += (((float)rand() / 32767)*4)-2;

			//##### Active Cell
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], ((float)rand() / 32767)*0.05, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].y -= ((float)rand() / 32767)*0.2;

			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].x += Q_PinEffectMesh->PinEffectMesh[MeshID].CellXINC[0][jet][helly];
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].y += Q_PinEffectMesh->PinEffectMesh[MeshID].CellYINC[0][jet][helly];
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].z += Q_PinEffectMesh->PinEffectMesh[MeshID].CellZINC[0][jet][helly];

			Q_PinEffectMesh->PinEffectMesh[MeshID].CellXINC[0][jet][helly] += (((float)rand() / 32767)*4)-2;
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellYINC[0][jet][helly] += (((float)rand() / 32767)*4)-2;
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellZINC[0][jet][helly] += (((float)rand() / 32767)*4)-2;

			//## Update Movement Variables
			Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly] += 0.02 + (((float)rand() / 32767)*0.6) - 0.2;
			//Increment X  ->'jet'
			jet++;
			}

		helly++;
		}



	//Pass increment downstream
	/*helly=0;
	helly = Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumY - 2;
	while(helly > 0)
		{
		//Frozen
		//Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly] = Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly-1];

		jet=0;
		while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
			{
			//Hack - Change Vert values manually
			//##### Active Base Vert
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].x = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly-1].x;
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].x = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly-1].z;
			//##### Active Cell
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].x = Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly-1].x;
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].x = Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly-1].z;
			//Increment X  ->'jet'
			jet++;
			}

		helly--;
		}


		//Update this stream increment
	Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][0] = sin(Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng) * 5;
	Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng += 0.5;	//0.1
	if(Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng > 2 * PI) Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng = 0;*/
	}


void Q_COREFunctions::PEF_CONTROL_RingShieldSphere(int MeshID)
	{
	//##### Single Face No 1
	helly = 0;
	while(helly < Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines)
		{
		jet=0;
		while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
			{
			//##### Active Base Vert
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
			//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], ((float)rand() / 32767)*0.05, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].y -= Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly];
			
			//###### Spherize the Vert
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, Q_PinEffectMesh->PinEffectMesh[MeshID].SphereRadius, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly]);

			//##### Active Cell
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].y -= Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly];
			
			//###### Spherize the Vert
			Qpo->Vec3d_Subtract(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], &Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_Normalize(&Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].EffCenter, Q_PinEffectMesh->PinEffectMesh[MeshID].SphereRadius, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);

			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly], ((float)rand() / 32767)*0.5, &Q_PinEffectMesh->PinEffectMesh[MeshID].PointerVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly]);

			
			//Increment X  ->'jet'
			jet++;
			}

		//## Update Movement Variables
		Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly] *= 1.1;
		Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[helly] += 0.5;

		helly++;
		}
	}


//------******[  <PEF MESH UNDULATE>------[EFFECTS CONTROL ROUTINES]  ]******------

void Q_COREFunctions::PEF_CONTROL_FaceRippleMesh(int MeshID)
	{
	//##### Single Face No 1
	jet=0;
	while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
		{
		//##### Active Base Vert
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][0].y += Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][0];
		//##### Active Cell
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][0].y += Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][0] * 2;
		//Increment X  ->'jet'
		jet++;
		}


	//Pass increment downstream
	//helly=0;
	helly = Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumY - 2;
	while(helly > 0)
		{
		//Frozen
		//Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly] = Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][helly-1];

		jet=0;
		while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
			{
			//Hack - Change Vert values manually
			//##### Active Base Vert
			Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly].y = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][helly-1].y;
			//##### Active Cell
			Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly].y = Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][helly-1].y;
			//Increment X  ->'jet'
			jet++;
			}

		helly--;
		}


		//Update this stream increment
	Q_PinEffectMesh->PinEffectMesh[MeshID].LineMoveIncZ[0][0] = sin(Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng) * 5;
	Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng += 0.5;	//0.1
	if(Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng > 2 * PI) Q_PinEffectMesh->PinEffectMesh[MeshID].EffectMoveAng = 0;
	}


void Q_COREFunctions::PEF_ADDLINE_TubePEFMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp, int MeshID)
	{
	//##### Init Variables
	Q_PinEffectMesh->PinEffectMesh[MeshID].StartPos = StartPos;
	Q_PinEffectMesh->PinEffectMesh[MeshID].Posfloater = StartPos;
	Q_PinEffectMesh->PinEffectMesh[MeshID].RingScale = Scale;

	Q_PinEffectMesh->PinEffectMesh[MeshID].VecIn = VecIn;
	Q_PinEffectMesh->PinEffectMesh[MeshID].VecRight = VecRight;
	Q_PinEffectMesh->PinEffectMesh[MeshID].VecUp = VecUp;

	Q_PinEffectMesh->PinEffectMesh[MeshID].PushBrushDist = Scale;

	Q_PinEffectMesh->PinEffectMesh[MeshID].RotateAng = 0;

	Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = StartPos;
	Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 0;

	Q_PinEffectMesh->PinEffectMesh[MeshID].LineReleased[0][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 0;

	Q_PinEffectMesh->PinEffectMesh[MeshID].LineAlpha[0][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 150;
	Q_PinEffectMesh->PinEffectMesh[MeshID].LineTimer[0][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 0;

	//##### Setup 1 Face
	jet=0;

	//Set The Base Verts for the X Axis
	while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
		{	//||Active Cell||
		Qpo->Transform_New_ZRotation(&Q_PinEffectMesh->PinEffectMesh[MeshID].RotateMatrix, Q_PinEffectMesh->PinEffectMesh[MeshID].RotateAng);
		Q_PinEffectMesh->PinEffectMesh[MeshID].RotateAng += 0.524;		//0.314
		Qpo->Vec3d_New(&Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
		Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec, Q_PinEffectMesh->PinEffectMesh[MeshID].PushBrushDist, &Q_PinEffectMesh->PinEffectMesh[MeshID].VecUp, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
		Qpo->Transform_RotateVector(&Q_PinEffectMesh->PinEffectMesh[MeshID].RotateMatrix, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
		Qpo->Vec3d_Add(&Q_PinEffectMesh->PinEffectMesh[MeshID].StartPos, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
 
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec;

		//Store Base Verts Starting Position
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVertSTR[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];
			
		//Set CellVert1 X and Y
		//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].Posfloater, (Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale / 2), &Q_PinEffectMesh->PinEffectMesh[MeshID].VecIn, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines]);
		//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines], ((Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale * (float)jet) + (Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale / 2)), &Q_PinEffectMesh->PinEffectMesh[MeshID].VecRight, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines]);

		//Set CellVert1 Z
		//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines], (Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale / 4), &Q_PinEffectMesh->PinEffectMesh[MeshID].VecUp, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines]);

		Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];

		//Store Cell Verts Starting Position
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1STR[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];
			
		//Set Cell to Live position
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellLive[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 1;

		Q_PinEffectMesh->PinEffectMesh[MeshID].CellAlpha[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].LineAlpha[0][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellRed[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 255;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellBlue[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 255;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellGreen[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 255;

		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseXINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseYINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseZINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;

		Q_PinEffectMesh->PinEffectMesh[MeshID].CellXINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellYINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellZINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;

		jet++;
		}	//||Active Cell||

	Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines++;
	}


void Q_COREFunctions::PEF_ADDLINE_RingPEFMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp, int MeshID)
	{
	//##### Init Variables
	Q_PinEffectMesh->PinEffectMesh[MeshID].StartPos = StartPos;
	Q_PinEffectMesh->PinEffectMesh[MeshID].Posfloater = StartPos;
	Q_PinEffectMesh->PinEffectMesh[MeshID].RingScale = Scale;

	Q_PinEffectMesh->PinEffectMesh[MeshID].VecIn = VecIn;
	Q_PinEffectMesh->PinEffectMesh[MeshID].VecRight = VecRight;
	Q_PinEffectMesh->PinEffectMesh[MeshID].VecUp = VecUp;

	Q_PinEffectMesh->PinEffectMesh[MeshID].PushBrushDist = Scale;

	Q_PinEffectMesh->PinEffectMesh[MeshID].RotateAng = 0;

	Q_PinEffectMesh->PinEffectMesh[MeshID].LineCenter[Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = StartPos;
	Q_PinEffectMesh->PinEffectMesh[MeshID].ExpandAMT[Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 0;


	//##### Setup 1 Face
	jet=0;

	//Set The Base Verts for the X Axis
	while(jet < Q_PinEffectMesh->PinEffectMesh[MeshID].MaxNumX)
		{	//||Active Cell||

		Qpo->Transform_New_YRotation(&Q_PinEffectMesh->PinEffectMesh[MeshID].RotateMatrix, Q_PinEffectMesh->PinEffectMesh[MeshID].RotateAng);
		Q_PinEffectMesh->PinEffectMesh[MeshID].RotateAng += 0.524;		//0.314
		Qpo->Vec3d_New(&Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
		Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec, Q_PinEffectMesh->PinEffectMesh[MeshID].PushBrushDist, &Q_PinEffectMesh->PinEffectMesh[MeshID].VecRight, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
		Qpo->Transform_RotateVector(&Q_PinEffectMesh->PinEffectMesh[MeshID].RotateMatrix, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);
		Qpo->Vec3d_Add(&Q_PinEffectMesh->PinEffectMesh[MeshID].StartPos, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec, &Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec);

		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].BrushVec;

		//Store Base Verts Starting Position
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVertSTR[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];
			
		//Set CellVert1 X and Y
		//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].Posfloater, (Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale / 2), &Q_PinEffectMesh->PinEffectMesh[MeshID].VecIn, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines]);
		//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines], ((Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale * (float)jet) + (Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale / 2)), &Q_PinEffectMesh->PinEffectMesh[MeshID].VecRight, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines]);

		//Set CellVert1 Z
		//Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines], (Q_PinEffectMesh->PinEffectMesh[MeshID].EffectScale / 4), &Q_PinEffectMesh->PinEffectMesh[MeshID].VecUp, &Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines]);

		Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];

		//Store Cell Verts Starting Position
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1STR[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Q_PinEffectMesh->PinEffectMesh[MeshID].CellVert1[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines];
			
		//Set Cell to Live position
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellLive[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 1;

		Q_PinEffectMesh->PinEffectMesh[MeshID].CellAlpha[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 240;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellRed[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = 255;
		Tempint1 = (rand() % 100) + 155;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellBlue[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Tempint1;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellGreen[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = Tempint1;

		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseXINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseYINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].BaseZINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;

		Q_PinEffectMesh->PinEffectMesh[MeshID].CellXINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellYINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;
		Q_PinEffectMesh->PinEffectMesh[MeshID].CellZINC[0][jet][Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines] = (((float)rand() / 32767)*4)-2;

		jet++;
		}	//||Active Cell||

	Q_PinEffectMesh->PinEffectMesh[MeshID].NoMLines++;
	}


void Q_COREFunctions::PEF_CREATE_RingPEFMesh(QpoVec3d StartPos, float Scale, int EffType)
	{
	//Init Flat Carpet
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectType = EffType;	//Type 0 Carpet Effect
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].BaseShape = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale = Scale;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Origin = StartPos;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].StartPos = StartPos;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumX = 20;	//Number Of X plotted Cells
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumY = 20;	//Number Of Y plotted Cells

	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectAlpha = 150;						//Effect Alpha Value
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectRed = 180;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectGreen = 180;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectBlue = 180;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectLive = 1;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].LineMoveIncZ[0][0] = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectMoveAng = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].RotateAng = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].NoMLines = 0;

	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].PolyType = QPOLY_TYPE_TRI;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].RenderFlags = QPOLY_REND_DEPTH_SORT;

	_->NomPEFMesh++;
	}


void Q_COREFunctions::PEF_CREATE_SpherePEFMesh(QpoVec3d StartPos, QpoVec3d Center, float Radius, int EffType)
	{
	//Init Flat Carpet
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectType = EffType;	//Type 0 Carpet Effect
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].BaseShape = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Origin = StartPos;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].StartPos = StartPos;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumX = 12;	//Number Of X plotted Cells
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumY = 12;	//Number Of Y plotted Cells

	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectAlpha = 90;						//Effect Alpha Value
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectRed = 255;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectGreen = 255;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectBlue = 255;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectLive = 1;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].LineMoveIncZ[0][0] = 1;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectMoveAng = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].RotateAng = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].NoMLines = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].SphereRadius = Radius;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffCenter = Center;


	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].PolyType = QPOLY_TYPE_TRI;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].RenderFlags = QPOLY_REND_DEPTH_SORT;

	_->NomPEFMesh++;
	}


//------******[  <PIN EFFECT MESH>------[EFFECTS INITIALISATION ROUTINES]  ]******------

void Q_COREFunctions::PEF_CREATE_PinEffectMesh(QpoVec3d StartPos, float Scale, QpoVec3d VecIn, QpoVec3d VecRight, QpoVec3d VecUp)
	{
	//Init Flat Carpet
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectType = 0;	//Type 0 Carpet Effect
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].BaseShape = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale = Scale;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Origin = StartPos;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].StartPos = StartPos;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecIn = VecIn;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecRight = VecRight;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecUp = VecUp;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumX = 20;	//Number Of X plotted Cells
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumY = 20;	//Number Of Y plotted Cells

	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectAlpha = 150;						//Effect Alpha Value
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectRed = 180;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectGreen = 180;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectBlue = 180;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectLive = 1;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].LineMoveIncZ[0][0] = 0;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectMoveAng = 0;

	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].PolyType = QPOLY_TYPE_TRI;
	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].RenderFlags = QPOLY_REND_DEPTH_SORT;


	//Init 1 Face
	helly=0;

	Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Posfloater = Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].StartPos;

	while(helly <= Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumY)
		{
		jet=0;

		//Move the floating position pointer up the Y Axis
		Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].StartPos, Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale * (float)helly, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecIn, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Posfloater);

		//Set The Base Verts for the X Axis
		while(jet <= Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].MaxNumX)
			{	//||Active Cell||
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Posfloater, Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale * (float)jet, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecRight, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].BaseVert[0][jet][helly]);

			//Store Base Verts Starting Position
			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].BaseVertSTR[0][jet][helly] = Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].BaseVert[0][jet][helly];
			
			//Set CellVert1 X and Y
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].Posfloater, (Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale / 2), &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecIn, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1[0][jet][helly]);
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1[0][jet][helly], ((Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale * (float)jet) + (Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale / 2)), &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecRight, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1[0][jet][helly]);

			//Set CellVert1 Z
			Qpo->Vec3d_AddScaled(&Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1[0][jet][helly], (Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].EffectScale / 4), &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].VecUp, &Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1[0][jet][helly]);

			//Store Cell Verts Starting Position
			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1STR[0][jet][helly] = Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellVert1[0][jet][helly];
			
			//Set Cell to Live position
			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellLive[0][jet][helly] = 1;

			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellAlpha[0][jet][helly] = 150;
			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellRed[0][jet][helly] = 180;
			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellBlue[0][jet][helly] = 180;
			Q_PinEffectMesh->PinEffectMesh[_->NomPEFMesh].CellGreen[0][jet][helly] = 180;
			jet++;
			}	//||Active Cell||

		helly++;
		}

	_->NomPEFMesh++;
	}

};