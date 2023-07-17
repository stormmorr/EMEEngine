/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Effects Matrix Control For Player-

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
#include "Q-ENE-EnergyTypes.h"

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::ClericSpell_ServerFrame(int Count)
	{
	Count=0;
	while(Count < Q_ClericSpell->ClericSpell[Count].NumSpheres)
		{
		//Rotate GOOD
		//Qpo->Transform_New_XRotation(&rotmat, 0.05);
		//Qpo->Transform_Multiply(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &rotmat, &Q_ClericSpell->ClericSpell[Count].SphereMatrix);

		//Qpo->Transform_New_YRotation(&rotmat, (float)Count/15);
		//Qpo->Transform_Multiply(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &rotmat, &Q_ClericSpell->ClericSpell[Count].SphereMatrix);
		

		//Rotate
		//Qpo->Transform_New_XRotation(&rotmat, 0.01);	//0.01 X
		//Qpo->Transform_Multiply(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &rotmat, &Q_ClericSpell->ClericSpell[Count].SphereMatrix);

		if((Q_ClericSpell->ClericSpell[Count].NumSpheres == 1) || ((Count == 0) && (Q_ClericSpell->ClericSpell[Count].Absorbed > 0)))
			{
			//Qpo->Transform_New_ZRotation(&rotmat, 0.09);
			//Qpo->Transform_Multiply(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &rotmat, &Q_ClericSpell->ClericSpell[Count].SphereMatrix);
			Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1 = Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos;

			Qpo->Transform_New_XRotation(&rotmat, 0.05);
			Qpo->Transform_Multiply(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &rotmat, &Q_ClericSpell->ClericSpell[Count].SphereMatrix);
			}
		else
			{
			Qpo->Transform_New_ZRotation(&rotmat, (float)Count/2);
			Qpo->Transform_Multiply(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &rotmat, &Q_ClericSpell->ClericSpell[Count].SphereMatrix);
			Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1 = Q_ClericSpell->ClericSpell[Count].LightPos;
			}

		Qpo->Transform_GetIn(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Leftvec);
		Qpo->Transform_GetUp(&Q_ClericSpell->ClericSpell[Count].SphereMatrix, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Upvec);

		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Upvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1);
						//Distance to the Left of the player
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Leftvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1);

						//Distance to the Right of the player from the left
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, -Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius * 2, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Leftvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2, -Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius * 2, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Upvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, -Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius * 2, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Upvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4);

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].u = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].v = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1.z;

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].u = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].v = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2.z;

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].u = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].v = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3.z;

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].u = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].v = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4.z;

		Qpo->Poly_AddOnce(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0], 4, Medias->HealSphere, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);
		
		if(Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius < Q_ClericSpell->ClericSpell[Count].Sphere[Count].MaxRadius) Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius += ((Q_ClericSpell->ClericSpell[Count].Sphere[Count].MaxRadius / (Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius + 3)  ) / 3 ) * _->TimeScale;
		//}
	//else
		//{
		//if(Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade - (10*_->TimeScale) >= 0) Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade -= 10*_->TimeScale;
		//else
		//	{
		//	Q_ClericSpell->ClericSpell[Count].Sphere[Count].Radius = 301;
		//	Q_MeleeHit->MeleeHit[Count].Live = 0;
		//	Qpo->Light_Remove(Q_MeleeHit->MeleeHit[Count].Light);
		//	}
		//if(Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade >= 0)
		//	{
		//	Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade;
		//	Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade;
		//	Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade;
		//	Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].a = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Fade;
		//	if(Q_MeleeHit->MeleeHit[Count].BlockHit == 0) Qpo->Poly_AddOnce(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0], 4, Medias->Pulsar[Q_ClericSpell->ClericSpell[Count].Sphere[Count].MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_OCCLUDE_ON, Q_ClericSpell->ClericSpell[Count].Sphere[Count].Scale);
		//	else Qpo->Poly_AddOnce(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0], 4, Medias->expandro1, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, Q_ClericSpell->ClericSpell[Count].Sphere[Count].Scale);
		//	}
		//}
	

		Count++;
		}

	if(Q_ClericSpell->ClericSpell[Count].Released == 1 && Q_ClericSpell->ClericSpell[Count].Absorbed == 0)
		{
		if(Q_ClericSpell->ClericSpell[Count].HealTarget == 250)
			{
			Q_ClericSpell->ClericSpell[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].TargetVec.y += 65;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].TargetVec = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].AV.Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].TargetVec.y += 65;
			}

		Qpo->Vec3d_Subtract(&Q_ClericSpell->ClericSpell[Count].TargetVec, &Q_ClericSpell->ClericSpell[Count].LightPos, &Q_ClericSpell->ClericSpell[Count].TargetVec);
		Q_ClericSpell->ClericSpell[Count].LightSpeed = ( Qpo->Vec3d_Length(&Q_ClericSpell->ClericSpell[Count].TargetVec) / 5 ) + 8;

		if(Qpo->Vec3d_Length(&Q_ClericSpell->ClericSpell[Count].TargetVec) < 20)
			{
			Q_ClericSpell->ClericSpell[Count].Absorbed = 1;
			Q_ClericSpell->ClericSpell[Count].LightPow = 200;
			}

		Qpo->Vec3d_Normalize(&Q_ClericSpell->ClericSpell[Count].TargetVec);
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].LightPos, Q_ClericSpell->ClericSpell[Count].LightSpeed * _->TimeScale, &Q_ClericSpell->ClericSpell[Count].TargetVec, &Q_ClericSpell->ClericSpell[Count].LightPos);
		}

	if(Q_ClericSpell->ClericSpell[Count].Absorbed == 1)
		{
		if(Q_ClericSpell->ClericSpell[Count].HealTarget == 250)
			{
			Q_ClericSpell->ClericSpell[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].TargetVec.y += 65;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].TargetVec = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].AV.Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].TargetVec.y += 65;
			}

		Q_ClericSpell->ClericSpell[Count].LightPos = Q_ClericSpell->ClericSpell[Count].TargetVec;

		if(Q_ClericSpell->ClericSpell[Count].LightPow < 700)
			{
			Q_ClericSpell->ClericSpell[Count].LightPow += 200;
			
			//##### Insert Effect Here
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].Absorbed = 2;
			
			//##### ACTIVATE SPELL

			if(Q_ClericSpell->ClericSpell[Count].AvID == 250)
				{

				if(Q_ClericSpell->ClericSpell[Count].HealTarget == 250)
					{
					Q.DeactivateItems();

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].LIVE = 1;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_TYPE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_INTENSITY;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_SWITCH;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_IntBoost;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_EnergyEff;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Height;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Weight;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Strength;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Quickness;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Dexterity;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Constitution;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_AggPower;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_DefPower;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RArmStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LArmStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RLegStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LLegStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RArmSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LArmSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RLegSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LLegSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPAccuracy;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPDrawSPD;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPReloadSPD;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPRecoilHR;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINKmovespeed;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINKpower;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINK3intensity;

					player[g_Player]->SLOTINC++;
					if(player[g_Player]->SLOTINC > 2) player[g_Player]->SLOTINC = 0;

					//### Write out CHARDATA
					Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

					Q.ActivateItems();

					jet=0;
					while(jet < _->NETNomNetplayer)
						{
						Q_Netplayer->Netplayer[jet].UpdateCHAR = 3;
						jet++;
						}
					}
				else
					{
					Q.DeactivateItemsAI(Q_ClericSpell->ClericSpell[Count].HealTarget);

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].LIVE = 1;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_TYPE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_INTENSITY;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_SWITCH;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_IntBoost;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_EnergyEff;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Height;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Weight;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Strength;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Quickness;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Dexterity;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Constitution;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_AggPower;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_DefPower;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RArmStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LArmStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RLegStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LLegStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RArmSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LArmSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RLegSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LLegSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPAccuracy;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPDrawSPD;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPReloadSPD;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPRecoilHR;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINKmovespeed;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINKpower;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINK3intensity;


					if(Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].NetplayerFLAG == 0)
						{
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].LIVE = 1;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_TYPE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_INTENSITY;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_SWITCH;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL00ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL01ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL02ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL03ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_EFFECT_COL04ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_IntBoost;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_EnergyEff;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Height;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Weight;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Strength;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Quickness;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Dexterity;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_Constitution;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_AggPower;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_DefPower;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RArmStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LArmStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RLegStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LLegStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RArmSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LArmSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_RLegSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_LLegSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPAccuracy;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPDrawSPD;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPReloadSPD;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_WEPRecoilHR;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINKmovespeed;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINKpower;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Spells[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellContainerID[player[g_Player]->Cleric.SpellPNTR]].QA_SPELLINC_JINK3intensity;
						}

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC++;
					if(Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC > 2) Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC = 0;


					Q.ActivateItemsAI(Q_ClericSpell->ClericSpell[Count].HealTarget);

					jet=0;
					while(jet < _->NETNomNetplayer)
						{
						Q_Netplayer->Netplayer[jet].UpdateCHAR = 3;
						jet++;
						}
					}
				}//END ACTORID == 250
			else
				{
				if(Q_ClericSpell->ClericSpell[Count].HealTarget == 250)
					{
					Q.DeactivateItems();

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].LIVE = 1;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_TYPE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_TYPE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_INTENSITY = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_INTENSITY;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_SWITCH = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_SWITCH;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL00ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL01ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL02ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL03ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04RED;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04GREEN;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04BLUE;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_EFFECT_COL04ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04ALPHA;

					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_IntBoost = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_IntBoost;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_EnergyEff = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_EnergyEff;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Height = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Height;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Weight = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Weight;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Strength = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Strength;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Quickness = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Quickness;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Dexterity = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Dexterity;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_Constitution = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Constitution;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_AggPower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_AggPower;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_DefPower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_DefPower;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RArmStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RArmStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LArmStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LArmStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RLegStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RLegStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LLegStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LLegStr;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RArmSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RArmSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LArmSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LArmSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_RLegSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RLegSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_LLegSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LLegSnap;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPAccuracy = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPAccuracy;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPDrawSPD = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPDrawSPD;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPReloadSPD = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPReloadSPD;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_WEPRecoilHR = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPRecoilHR;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_JINKmovespeed = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINKmovespeed;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_JINKpower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINKpower;
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[player[g_Player]->SLOTINC].QA_SPELLINC_JINK3intensity = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINK3intensity;

					player[g_Player]->SLOTINC++;
					if(player[g_Player]->SLOTINC > 2) player[g_Player]->SLOTINC = 0;

					//### Write out CHARDATA
					Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

					Q.ActivateItems();

					jet=0;
					while(jet < _->NETNomNetplayer)
						{
						Q_Netplayer->Netplayer[jet].UpdateCHAR = 3;
						jet++;
						}
					}
				else
					{
					Q.DeactivateItemsAI(Q_ClericSpell->ClericSpell[Count].HealTarget);

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].LIVE = 1;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_TYPE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_TYPE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_INTENSITY = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_INTENSITY;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_SWITCH = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_SWITCH;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04RED;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04GREEN;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04BLUE;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04ALPHA;

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_IntBoost = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_IntBoost;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_EnergyEff = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_EnergyEff;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Height = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Height;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Weight = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Weight;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Strength = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Strength;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Quickness = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Quickness;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Dexterity = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Dexterity;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Constitution = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Constitution;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_AggPower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_AggPower;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_DefPower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_DefPower;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RArmStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LArmStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RLegStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LLegStr;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RArmSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LArmSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RLegSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LLegSnap;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPAccuracy = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPAccuracy;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPDrawSPD = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPDrawSPD;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPReloadSPD = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPReloadSPD;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPRecoilHR = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPRecoilHR;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKmovespeed = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINKmovespeed;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKpower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINKpower;
					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINK3intensity = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINK3intensity;


					if(Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].NetplayerFLAG == 0)
						{
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].LIVE = 1;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_TYPE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_TYPE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_INTENSITY = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_INTENSITY;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_SWITCH = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_SWITCH;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL00ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL00ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL01ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL01ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL02ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL02ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL03ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL03ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04RED = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04RED;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04GREEN = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04GREEN;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04BLUE = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04BLUE;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_EFFECT_COL04ALPHA = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_EFFECT_COL04ALPHA;

						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_IntBoost = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_IntBoost;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_EnergyEff = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_EnergyEff;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Height = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Height;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Weight = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Weight;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Strength = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Strength;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Quickness = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Quickness;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Dexterity = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Dexterity;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_Constitution = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_Constitution;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_AggPower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_AggPower;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_DefPower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_DefPower;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RArmStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LArmStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RLegStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegStr = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LLegStr;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RArmSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RArmSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LArmSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LArmSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_RLegSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_RLegSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_LLegSnap = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_LLegSnap;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPAccuracy = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPAccuracy;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPDrawSPD = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPDrawSPD;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPReloadSPD = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPReloadSPD;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_WEPRecoilHR = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_WEPRecoilHR;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKmovespeed = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINKmovespeed;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINKpower = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINKpower;
						player[g_Player]->BFO.CharDATA[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].CharDATA.CDataID].SpellSLOT[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC].QA_SPELLINC_JINK3intensity = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.Spells[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].CharDATA.SpellContainerID[Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].Cleric.SpellPNTR]].QA_SPELLINC_JINK3intensity;
						}

					Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC++;
					if(Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC > 2) Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].SLOTINC = 0;


					Q.ActivateItemsAI(Q_ClericSpell->ClericSpell[Count].HealTarget);

					jet=0;
					while(jet < _->NETNomNetplayer)
						{
						Q_Netplayer->Netplayer[jet].UpdateCHAR = 3;
						jet++;
						}
					}
				}//END ACTORID != 250

			}
		}

	if(Q_ClericSpell->ClericSpell[Count].Absorbed == 2)
		{
		if(Q_ClericSpell->ClericSpell[Count].AvID == 250)
			{
			Q_ClericSpell->ClericSpell[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].TargetVec.y += 65;
			Qpo->Vec3d_Subtract(&Q_ClericSpell->ClericSpell[Count].TargetVec, &Q_ClericSpell->ClericSpell[Count].LightPos, &Q_ClericSpell->ClericSpell[Count].TargetVec);
			Q_ClericSpell->ClericSpell[Count].LightSpeed = ( Qpo->Vec3d_Length(&Q_ClericSpell->ClericSpell[Count].TargetVec) / 5 ) + 8;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].TargetVec = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].AvID].AV.Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].TargetVec.y += 65;
			Qpo->Vec3d_Subtract(&Q_ClericSpell->ClericSpell[Count].TargetVec, &Q_ClericSpell->ClericSpell[Count].LightPos, &Q_ClericSpell->ClericSpell[Count].TargetVec);
			Q_ClericSpell->ClericSpell[Count].LightSpeed = ( Qpo->Vec3d_Length(&Q_ClericSpell->ClericSpell[Count].TargetVec) / 5 ) + 8;
			}

		if(Qpo->Vec3d_Length(&Q_ClericSpell->ClericSpell[Count].TargetVec) < 20)
			{
			Q_ClericSpell->ClericSpell[Count].Absorbed = 3;
			Q_ClericSpell->ClericSpell[Count].LightPow = 200;
			if(Q_ClericSpell->ClericSpell[Count].LightON == 1) Qpo->Light_Remove(Q_ClericSpell->ClericSpell[Count].Light);
			Q_ClericSpell->ClericSpell[Count].LightInit = 0;
			Q_ClericSpell->ClericSpell[Count].LightON = 0;
			Q_ClericSpell->ClericSpell[Count].NumSpheres = 1;
			}

		Qpo->Vec3d_Normalize(&Q_ClericSpell->ClericSpell[Count].TargetVec);
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].LightPos, Q_ClericSpell->ClericSpell[Count].LightSpeed * _->TimeScale, &Q_ClericSpell->ClericSpell[Count].TargetVec, &Q_ClericSpell->ClericSpell[Count].LightPos);
		}

	if(Q_ClericSpell->ClericSpell[Count].NumSpheres == 1)
		{
		if(Q_ClericSpell->ClericSpell[Count].Sphere[0].StartFade - 5 > 25) Q_ClericSpell->ClericSpell[Count].Sphere[0].StartFade -= 5;
		else Q_ClericSpell->ClericSpell[Count].Sphere[0].StartFade = 25;

		//#### INCREMENT TIMER
		Q_ClericSpell->ClericSpell[Count].TimerCNT -= _->TimeScale;

		if(Q_ClericSpell->ClericSpell[Count].TimerCNT <= 0)
			{
			Q_ClericSpell->ClericSpell[Count].Live = 0;

			//### Array Reorder
			int K = Count;
			while(K < _->NomSpell - 1)
				{
				Q_ClericSpell->ClericSpell[K] = Q_ClericSpell->ClericSpell[K+1];
				K++;
				}

			_->NomSpell--;
			}
		}
	else
		{
		if(Q_ClericSpell->ClericSpell[Count].Sphere[0].StartFade < 125) Q_ClericSpell->ClericSpell[Count].Sphere[0].StartFade += 10;
		if(Q_ClericSpell->ClericSpell[Count].Sphere[1].StartFade < 125) Q_ClericSpell->ClericSpell[Count].Sphere[1].StartFade += 10;
		if(Q_ClericSpell->ClericSpell[Count].Sphere[2].StartFade < 125) Q_ClericSpell->ClericSpell[Count].Sphere[2].StartFade += 10;
		if(Q_ClericSpell->ClericSpell[Count].Sphere[3].StartFade < 125) Q_ClericSpell->ClericSpell[Count].Sphere[3].StartFade += 10;
		}

	if(Q_ClericSpell->ClericSpell[Count].Absorbed > 0)
		{
		if(Q_ClericSpell->ClericSpell[Count].HealTarget == 250)
			{
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos = playerAV[g_Player]->Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos.y += 65;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].AV.Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos.y += 65;
			}
		}

	if(Q_ClericSpell->ClericSpell[Count].LightON == 1) Qpo->Light_SetAttr(Q_ClericSpell->ClericSpell[Count].Light, &Q_ClericSpell->ClericSpell[Count].LightPos, &Q_ClericSpell->ClericSpell[Count].LightColor, 200, true);
		

	if(KEY_PRESS_DOWN(QIN_F5))
		{
		if(Q_ClericSpell->ClericSpell[Count].LightON == 1) Qpo->Light_Remove(Q_ClericSpell->ClericSpell[Count].Light);
		Q_ClericSpell->ClericSpell[Count].LightInit = 0;
		Q_ClericSpell->ClericSpell[Count].Live = 0;
		Q_ClericSpell->ClericSpell[Count].Absorbed = 0;

		//### Energy Array Reorder
		int K = Count;
		while(K < _->NomSpell - 1)
			{
			Q_ClericSpell->ClericSpell[K] = Q_ClericSpell->ClericSpell[K+1];
			K++;
			}

		_->NomSpell--;
		}
	}


void Q_EFFCon::ClericSpell_ClientFrame(int Count)
	{
	if(Q_ClericSpell->ClericSpell[Count].LightON == 0)
		{
		Q_ClericSpell->ClericSpell[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_ClericSpell->ClericSpell[Count].LightColor.red = 255;
		Q_ClericSpell->ClericSpell[Count].LightColor.green = 255;
		Q_ClericSpell->ClericSpell[Count].LightColor.blue = 255;
		Q_ClericSpell->ClericSpell[Count].LightON = 1;
		}

	Count=0;
	while(Count < Q_ClericSpell->ClericSpell[Count].NumSpheres)
		{
		if((Q_ClericSpell->ClericSpell[Count].NumSpheres == 1) || ((Count == 0) && (Q_ClericSpell->ClericSpell[Count].Absorbed > 0)))
			{
			Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1 = Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1 = Q_ClericSpell->ClericSpell[Count].LightPos;
			}

		if(Q_ClericSpell->ClericSpell[Count].NumSpheres == 1)
			{
			Q_ClericSpell->ClericSpell[Count].Upvec = Q_ClericSpell->ClericSpell[Count].Sphere[0].Upvec;
			Q_ClericSpell->ClericSpell[Count].Leftvec = Q_ClericSpell->ClericSpell[Count].Sphere[0].Leftvec;
			Q_ClericSpell->ClericSpell[Count].Radius = Q_ClericSpell->ClericSpell[Count].Sphere[0].Radius;
			Q_ClericSpell->ClericSpell[Count].StartFade = Q_ClericSpell->ClericSpell[Count].Sphere[0].StartFade;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].Upvec = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Upvec;
			Q_ClericSpell->ClericSpell[Count].Leftvec = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Leftvec;
			Q_ClericSpell->ClericSpell[Count].Radius = Q_ClericSpell->ClericSpell[Count].Sphere[1].Radius;
			Q_ClericSpell->ClericSpell[Count].StartFade = Q_ClericSpell->ClericSpell[Count].Sphere[1].StartFade;
			}

		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, Q_ClericSpell->ClericSpell[Count].Radius, &Q_ClericSpell->ClericSpell[Count].Upvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1);
						//Distance to the Left of the player
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, Q_ClericSpell->ClericSpell[Count].Radius, &Q_ClericSpell->ClericSpell[Count].Leftvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1);

						//Distance to the Right of the player from the left
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, -Q_ClericSpell->ClericSpell[Count].Radius * 2, &Q_ClericSpell->ClericSpell[Count].Leftvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2, -Q_ClericSpell->ClericSpell[Count].Radius * 2, &Q_ClericSpell->ClericSpell[Count].Upvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1, -Q_ClericSpell->ClericSpell[Count].Radius * 2, &Q_ClericSpell->ClericSpell[Count].Upvec, &Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4);

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].a = Q_ClericSpell->ClericSpell[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].u = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].v = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert1.z;

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].a = Q_ClericSpell->ClericSpell[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].u = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].v = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[1].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert2.z;

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].a = Q_ClericSpell->ClericSpell[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].u = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].v = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[2].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert3.z;

		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].a = Q_ClericSpell->ClericSpell[Count].StartFade;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].b = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].g = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].r = 255;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].u = 0;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].v = 1;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].x = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4.x;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].y = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4.y;
		Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[3].z = Q_ClericSpell->ClericSpell[Count].Sphere[Count].Vert4.z;

		Qpo->Poly_AddOnce(&Q_ClericSpell->ClericSpell[Count].Sphere[Count].Lvert[0], 4, Medias->HealSphere, QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);

		Count++;
		}

	if(Q_ClericSpell->ClericSpell[Count].Absorbed > 0)
		{
		if(Q_ClericSpell->ClericSpell[Count].HealTarget == 250)
			{
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos = playerAV[g_Player]->Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos.y += 65;
			}
		else
			{
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos = Q_Forge->Forge[Q_ClericSpell->ClericSpell[Count].HealTarget].AV.Xform.Translation;
			Q_ClericSpell->ClericSpell[Count].Sphere[0].Pos.y += 65;
			}
		}

	if(Q_ClericSpell->ClericSpell[Count].NumSpheres == 1)
		{
		Q_ClericSpell->ClericSpell[Count].LightPow = 200;
		if(Q_ClericSpell->ClericSpell[Count].LightON == 1) Qpo->Light_Remove(Q_ClericSpell->ClericSpell[Count].Light);
		Q_ClericSpell->ClericSpell[Count].LightInit = 0;
		Q_ClericSpell->ClericSpell[Count].LightON = 0;
		}

	if(Q_ClericSpell->ClericSpell[Count].LightON == 1) Qpo->Light_SetAttr(Q_ClericSpell->ClericSpell[Count].Light, &Q_ClericSpell->ClericSpell[Count].LightPos, &Q_ClericSpell->ClericSpell[Count].LightColor, 200, true);
	}

};