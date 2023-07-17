/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -World Effects Control-

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
#include "Q-WE-WorldEffects.h"

float WindSTR = 0;
QpoVec3d Wind;

using namespace GVARS;

namespace GVARS
{

//########  - VAPOR TRAILS CONTROL VAPOR SYSTEM -  ########//

void Q_EFFCon::VaporTrail_ControlFrame(int Count)
	{
	SCRAM = 0;
	while(SCRAM < Q_VaporTrail->VaporTrail[Count].NomPoints)
		{
		switch(Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TYPE)
			{
			case 0:
				{
				//#### Increase timer
				Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed += (float)(_->TimeScale)*0.2;

				//##### Set Width
				Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed * Q_VaporTrail->VaporTrail[Count].WidthExpand) + Q_VaporTrail->VaporTrail[Count].StartWidth;

				//###### Drift Point
				Qpo->Vec3d_AddScaled(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos, Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].DriftSTR, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].DriftVec, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos);

				//###### Apply Wind
				Qpo->Vec3d_AddScaled(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos, WindSTR, &Wind, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos);

				if (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed > Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint && Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint > 0)
					{
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Live = 0;

					//### Array Reorder
					int K = SCRAM;
					while(K < Q_VaporTrail->VaporTrail[Count].NomPoints - 1)
						{
						Q_VaporTrail->VaporTrail[Count].TrailPoint[K] = Q_VaporTrail->VaporTrail[Count].TrailPoint[K+1];
						K++;
						}

					Q_VaporTrail->VaporTrail[Count].NomPoints--;

					if(Q_VaporTrail->VaporTrail[Count].NomPoints <= 0)
						{
						Q_VaporTrail->VaporTrail[Count].Live = 0;

						//### Array Reorder
						K = Count;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;
						}
					}


				//##### DRAW LASERS QUAD AND ENDCAPS
				if(SCRAM < Q_VaporTrail->VaporTrail[Count].NomPoints - 1)
					{
					Qpo->Vec3d_Subtract(&player[g_Player]->ViewXForm.Translation, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].CameraVector);
					Qpo->Vec3d_Subtract(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM+1].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LaserVector);
					Qpo->Vec3d_CrossProduct(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].CameraVector, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LaserVector, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight);
					Qpo->Vec3d_Copy(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft);
					Qpo->Vec3d_Inverse(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft);
					Qpo->Vec3d_Normalize(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight);
					Qpo->Vec3d_Normalize(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft);	
					Qpo->Vec3d_Scale(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft, Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft);
					Qpo->Vec3d_Scale(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight,Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight);
					Qpo->Vec3d_Add(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM+1].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndLeft);
					Qpo->Vec3d_Add(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM+1].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndRight);
					Qpo->Vec3d_Add(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft);
					Qpo->Vec3d_Add(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight, &Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight);
					
					for(int i=0; i < 4; i++)
						{
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[i].r = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.red - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.red) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.red;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[i].g = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.green - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.green) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.green;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[i].b = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.blue - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.blue) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.blue;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[i].a = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.alpha - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.alpha) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.alpha;
						}
					
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft.x;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft.y;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft.z;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight.x;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight.y;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight.z;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndRight.x;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndRight.y;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndRight.z;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndLeft.x;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndLeft.y;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndLeft.z;

					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].u = 0.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].v = 1.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].u = 1.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].v = 1.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].u = 1.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].v = 0.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].u = 0.0f;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].v = 0.0f;

					Qpo->Poly_AddOnce(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0], 4, Medias->VaporLINE, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);

					if(SCRAM > 0)
						{
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM-1].EndLeft.x;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM-1].EndLeft.y;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM-1].EndLeft.z;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM-1].EndRight.x;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM-1].EndRight.y;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[1].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM-1].EndRight.z;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight.x;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight.y;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[2].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartRight.z;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft.x;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft.y;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[3].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartLeft.z;

						Qpo->Poly_AddOnce(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0], 4, Medias->VaporLINE, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
						}
					else
						{		//##### DRAW START POINT
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].r = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.red - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.red) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.red;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].g = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.green - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.green) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.green;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].b = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.blue - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.blue) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.blue;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].a = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.alpha - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.alpha) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.alpha;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos.x;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos.y;
						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos.z;

						Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width2 = 2.0f/16*(Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width);
						Qpo->Poly_AddOnce(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0], 1, Medias->VaporCAP, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT | QPOLY_REND_NO_OCCLUDE, Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width2/7);
						}
					}
				else
					{		//##### DRAW END POINT
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].r = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.red - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.red) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.red;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].g = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.green - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.green) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.green;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].b = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.blue - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.blue) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.blue;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].a = (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].TimeElapsed / Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LifeOfPoint) * (Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].EndColor.alpha - Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.alpha) + Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].StartColor.alpha;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].x = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos.x;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].y = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos.y;
					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0].z = Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Pos.z;

					Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width2 = 2.0f/16*(Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width);
					Qpo->Poly_AddOnce(&Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].LVerts[0], 1, Medias->VaporCAP, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT | QPOLY_REND_NO_OCCLUDE, Q_VaporTrail->VaporTrail[Count].TrailPoint[SCRAM].Width2/7);
					}

				}break;

			}//END SWITCH

		SCRAM++;
		}

	}//END VAPOR TRAIL


void Q_COREFunctions::AddTrailPNT(int ParentTRAIL, QpoVec3d Pos, QpoColor Color1, QpoColor Color2, QpoVec3d DriftVec, int Type)
	{
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].Pos = Pos;					//Position in World Space
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].StartColor = Color1;
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].EndColor = Color2;
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].DriftVec = DriftVec;				
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].DriftSTR = 1.2;
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].TimeElapsed = 0;					//Optional- Counter for timing
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].LifeOfPoint = Q_VaporTrail->VaporTrail[ParentTRAIL].LifeOfPoint;					//Life of Point
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].TYPE = Type;					//Type of Trail
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].Live = 1;
	Q_VaporTrail->VaporTrail[ParentTRAIL].TrailPoint[Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints].ParentID = ParentTRAIL;
	if(Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints < 499) Q_VaporTrail->VaporTrail[ParentTRAIL].NomPoints++;
	}

};