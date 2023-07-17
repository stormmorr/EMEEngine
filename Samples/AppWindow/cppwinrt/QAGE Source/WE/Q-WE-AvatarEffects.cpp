/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Effects Matrix Control For Avatar-

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
#include "Q-WE-EnergyMatrix.h"

using namespace GVARS;

namespace GVARS
{

void Q_COREFunctions::QAEFFcontrolAI(int AIcounter, int QA_EFF_TYPE, float QA_EFF_INTENSITY, int QA_EFF_COL00RED, int QA_EFF_COL00GREEN, int QA_EFF_COL00BLUE, int QA_EFF_COL00ALPHA)
{
#if 1
switch(QA_EFF_TYPE)
	{
	case 1:		//Medias->QAEFF01 --- WEAPON ACCURACY
		{
		if(Q_Forge->Forge[AIcounter].WeaponStatus > 1)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[1] += 1;
			Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[1] = 0;

			//Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Weapon, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

			if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[1] <= 5)
				{
				Q_Forge->Forge[AIcounter].QAEFF_CNTR02[1] = 33;
				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[1] = 0;
				}

			Q_Forge->Forge[AIcounter].QAEFF_CNTR02[1] -= (0.1f + (0.65f * (1.0f - (QA_EFF_INTENSITY / 10000.0f))));
			
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, Q_Forge->Forge[AIcounter].QAEFF_CNTR02[1], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

			if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[1] > (3 + (25 * (1 - (QA_EFF_INTENSITY / 10000.0f)))))
				{
				Q_Forge->Forge[AIcounter].QAEFF_CNTR01[1] = 0;

				jet=0;
				while((jet < 1) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 44;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 50;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[1];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[1];
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[1]);

					Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[1] += 0.628;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			else Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[1] += 0.628;
			}

		} break;


	case 2:		//Medias->QAEFF02 --- WEAPON DRAW SPEED
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[2] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[2] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 NECK", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[2] > 55)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[2] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 40;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 10 + (70 * (QA_EFF_INTENSITY / 10000.0f));
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedMAX = 1.5 + (6 * (QA_EFF_INTENSITY / 10000.0f));
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[2];
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[2]);
				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[2] += 0.314;
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);

				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		} break;


	case 3:		//Medias->QAEFF03 --- WEAPON RELOAD SPEED
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[3] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[3] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 NECK", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[3] > 55)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[3] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 40;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 10 + (70 * (QA_EFF_INTENSITY / 10000.0f));
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedMAX = 1.5 + (6 * (QA_EFF_INTENSITY / 10000.0f));
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[3];
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[3]);
				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[3] += 0.314;
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);

				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		} break;


	case 4:		//Medias->QAEFF04 --- WEAPON RECOIL HEIGHT RECOVER
		{
		if(Q_Forge->Forge[AIcounter].WeaponStatus > 1)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[4] += (1 * _->TimeScale);
			Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[4] = 0;

			//Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Weapon, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

			if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[4] >= 30) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[4] = 0;
			Q_Forge->Forge[AIcounter].QAEFF_CNTR02[4] += 1;
			
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[4], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

			if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[4] > (1 + (10 * (1 - (QA_EFF_INTENSITY / 10000.0f)))))
				{
				Q_Forge->Forge[AIcounter].QAEFF_CNTR01[4] = 0;

				jet=0;
				while((jet < (5 + (20 * (QA_EFF_INTENSITY / 10000.0f)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 42;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 20;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[4];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[4];
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[4]);

					Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[4] += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			}

		} break;


	case 5:		//Medias->QAEFF05 --- ENERGY EFFICIENCY
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[5] += 1 * _->TimeScale;
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[5] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 HEAD", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[5] > 55)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[5] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 25;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 10 + (70 * (QA_EFF_INTENSITY/250));
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedMAX = 1.5 + (6 * (QA_EFF_INTENSITY/250));
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += 2.5;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_PntSprite->PntSprite[_->NomPntSprite].Pos;
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[5];


				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[5]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[5] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		} break;


	case 8:		//Medias->QAEFF06 --- PHYSICAL STR BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR03[8] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[8] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR04[8] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR04[8] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR04[8] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR04[8] * _->TimeScale, &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR03[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR03[8] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 27;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR04[8];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[8];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);

				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[8]);
				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[8] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		Q_Forge->Forge[AIcounter].QAEFF_CNTR05[8] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[8] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR06[8] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR06[8] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR06[8] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR06[8] * _->TimeScale, &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR05[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR05[8] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 28;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR06[8];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[8];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[8]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[8] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		Q_Forge->Forge[AIcounter].QAEFF_CNTR07[8] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT05[8] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L THIGH", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR08[8] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR08[8] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR08[8] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR08[8] * _->TimeScale, &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR07[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR07[8] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 46;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR08[8];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT05[8];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);

				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT05[8]);
				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT05[8] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		Q_Forge->Forge[AIcounter].QAEFF_CNTR09[8] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT06[8] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R THIGH", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR10[8] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR10[8] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR10[8] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR10[8] * _->TimeScale, &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR09[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR09[8] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 47;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR10[8];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT06[8];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT06[8]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT06[8] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		} break;


	case 9:		//Medias->QAEFF07 --- QUICKNESS BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[9] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[9] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[9] >= 20) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[9] = -4;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[9] += (1 * _->TimeScale);
		
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, Q_Forge->Forge[AIcounter].QAEFF_CNTR02[9], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[9] > (14 - (6 * (QA_EFF_INTENSITY/500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[9] = 0;

			jet=0;
			while(jet < ((2 + (30 * (QA_EFF_INTENSITY/500))) * _->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 30;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 20;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[9];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].CoronaON = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].CoronaALPHADIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].CoronaALPHA = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[9];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[9]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[9] += (6.283 / (2 + (30 * (QA_EFF_INTENSITY/500))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		} break;


	case 10:	//Medias->QAEFF08 --- DEXTERITY BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[10] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[10] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[10] >= 20) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[10] = -4;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[10] += (1 * _->TimeScale);
		
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, Q_Forge->Forge[AIcounter].QAEFF_CNTR02[10], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[10] > 8)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[10] = 0;

			jet=0;
			while((jet < 10) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 34;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;	//20	//16
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[10];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[10];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);

				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[10]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[10] += 0.628;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		} break;


	case 11:	//Medias->QAEFF09 --- CONSTITUTION BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[11] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[11] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[11] >= 20) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[11] = -4;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[11] += (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, Q_Forge->Forge[AIcounter].QAEFF_CNTR02[11], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[11] > 3)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[11] = 0;

			jet=0;
			while((jet < 4) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = (0.003 + (0.095 * ((float)rand() / 32767)));
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 32;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (15 + (50 * (QA_EFF_INTENSITY/500)));
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[11];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[11];


				//EXPERIMENT HERE
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[11];
				//Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = 0;

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[11]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[11] += 1.257;
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		} break;


	case 12:	//Medias->QAEFF10 --- AGGRESSIVE POWER BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[12] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[12] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[12] >= 20) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[12] = -4;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[12] += (0.35 * _->TimeScale);
		
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, Q_Forge->Forge[AIcounter].QAEFF_CNTR02[12], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[12] = 0;

			jet=0;
			while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 36;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (10 + (40 * (QA_EFF_INTENSITY/500)));
				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha2 = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaDIR2 = 1;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[12];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[12];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[12]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			}

		Q_Forge->Forge[AIcounter].QAEFF_CNTR03[12] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[12] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR04[12] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR04[12] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR04[12] -= (0.35 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR04[12], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR03[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR03[12] = 0;

			jet=0;
			while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 37;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (10 + (40 * (QA_EFF_INTENSITY/500)));
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR04[12];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[12];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[12]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT01[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		Q_Forge->Forge[AIcounter].QAEFF_CNTR05[12] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[12] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR06[12] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR06[12] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR06[12] -= (0.35 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX01, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX01.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR06[12], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX01.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR05[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR05[12] = 0;

			jet=0;
			while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 38;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (10 + (40 * (QA_EFF_INTENSITY/500)));
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR06[12];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[12];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[12]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT02[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}


		Q_Forge->Forge[AIcounter].QAEFF_CNTR07[12] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT03[12] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L THIGH", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR08[12] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR08[12] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR08[12] -= (0.35 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR08[12], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR07[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR07[12] = 0;

			jet=0;
			while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 48;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (10 + (40 * (QA_EFF_INTENSITY/500)));
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR08[12];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT03[12];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT03[12]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT03[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}

		Q_Forge->Forge[AIcounter].QAEFF_CNTR09[12] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT04[12] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R THIGH", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR10[12] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR10[12] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR10[12] -= (0.35 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX01, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX01.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR10[12], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX01.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR09[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR09[12] = 0;

			jet=0;
			while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 49;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (10 + (40 * (QA_EFF_INTENSITY/500)));
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR10[12];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT04[12];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT04[12]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT04[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		} break;


	case 13:	//Medias->QAEFF11 --- DEFENSIVE POWER BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[13] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[13] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[13] >= 20) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[13] = -4;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[13] += (0.4 * _->TimeScale);
		
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, Q_Forge->Forge[AIcounter].QAEFF_CNTR02[13], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[13] > (30 - (8 * (QA_EFF_INTENSITY/500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[13] = 0;

			jet=0;
			while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 39;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 20;
				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha2 = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaDIR2 = 1;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[13];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[13];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[13]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[13] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		} break;


	case 14:	//Medias->QAEFF12 --- RIGHT ARM STRENGTH BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[14] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[14] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[14] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[14] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[14] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[14], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[14] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[14] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 28;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[14];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[14];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[14]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[14] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 15:	//Medias->QAEFF13 --- LEFT ARM STRENGTH BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[15] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[15] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[15] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[15] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[15] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[15], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[15] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[15] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 27;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[15];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[15];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[15]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[15] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 16:	//Medias->QAEFF14 --- RIGHT LEG STRENGTH BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[16] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[16] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[16] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[16] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[16] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[16], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[16] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[16] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 47;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[16];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[16];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[16]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[16] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 17:	//Medias->QAEFF15 --- LEFT LEG STRENGTH BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[17] += (1 * _->TimeScale);
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[17] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[17] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[17] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[17] -= (1 * _->TimeScale);
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[17], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[17] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[17] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 46;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[17];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[17];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[17]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[17] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 18:	//Medias->QAEFF16 --- RIGHT ARM DEXTERITY BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[18] += 1;
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[18] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[18] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[18] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[18] -= 1;
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[18], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[18] > 3)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[18] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 53;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[18] == 0) Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 2;
				else Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 23;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[18];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[18];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[18]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[18] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 19:	//Medias->QAEFF17 --- LEFT ARM DEXTERITY BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[19] += 1;
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[19] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[19] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[19] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[19] -= 1;
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[19], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[19] > 3)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[19] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 52;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[19] == 0) Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 2;
				else Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 23;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[19];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[19];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[19]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[19] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 20:	//Medias->QAEFF18 --- RIGHT LEG DEXTERITY BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[20] += 1;
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[20] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[20] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[20] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[20] -= 1;
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[20], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[20] > 3)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[20] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 55;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[20] == 0) Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 2;
				else Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 23;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[20];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[20];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[20]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[20] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 21:	//Medias->QAEFF19 --- LEFT LEG DEXTERITY BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[21] += 1;
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[21] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 L FOREARM", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[21] <= 0) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[21] = 20;
		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[21] -= 1;
	
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_Forge->Forge[AIcounter].In);
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, -Q_Forge->Forge[AIcounter].QAEFF_CNTR02[21], &Q_Forge->Forge[AIcounter].In, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation);

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[21] > 3)
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[21] = 0;

			jet=0;
			while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 54;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[21] == 0) Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 2;
				else Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 23;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[21];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[21];

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[21]);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[21] += 0.314;

				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;


	case 22:	//Medias->QAEFF20 --- JINK MOVESPEED
		{
		Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX_MEM = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX;
		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE1", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);

		Q_Forge->Forge[AIcounter].QA_EFF_MEMLENGTH = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX_MEM.Translation);

		Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation, &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX_MEM.Translation, &Q_Forge->Forge[AIcounter].QA_EFF_MEMVEC);

		if(Q_Forge->Forge[AIcounter].QA_EFF_MEMLENGTH > 1)
			{
			AIcounter=0;
			while(AIcounter < 5)
				{
				Q_Forge->Forge[AIcounter].QA_EFF_MEMPOS = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX_MEM.Translation;
				Q_Forge->Forge[AIcounter].QA_EFF_MEMMOVE = AIcounter / (Q_Forge->Forge[AIcounter].QA_EFF_MEMLENGTH / 50);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].QA_EFF_MEMPOS, Q_Forge->Forge[AIcounter].QA_EFF_MEMMOVE, &Q_Forge->Forge[AIcounter].QA_EFF_MEMVEC, &Q_Forge->Forge[AIcounter].QA_EFF_MEMPOS);

				jet=0;
				while((jet < ((QA_EFF_INTENSITY/50)*10)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 45;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = ((QA_EFF_INTENSITY/50)*120);
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = Q_Forge->Forge[AIcounter].QA_EFF_MEMLENGTH/3;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_MEMPOS;

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*20;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*30;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*20;

					Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].QA_EFF_MEMVEC);

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec = Q_Forge->Forge[AIcounter].QA_EFF_MEMVEC;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x += (((float)rand() / 32767)-0.5)*0.25;
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y += (((float)rand() / 32767)-0.5)*0.25;
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z += (((float)rand() / 32767)-0.5)*0.25;
					
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}

				AIcounter++;
				}
			}

		}break;


	case 25:	//Medias->QAEFF21 --- Intelligence BOOST
		{
		Q_Forge->Forge[AIcounter].QAEFF_CNTR01[25] += 1 * _->TimeScale;
		Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[25] = 0;

		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 HEAD", &Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX);
		Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation.y += 10;

		Q_Forge->Forge[AIcounter].QAEFF_CNTR02[25] += 1;
		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[25] > 15) Q_Forge->Forge[AIcounter].QAEFF_CNTR02[25] = 0;

		Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation.y -= Q_Forge->Forge[AIcounter].QAEFF_CNTR02[25];

		if(Q_Forge->Forge[AIcounter].QAEFF_CNTR01[25] > ((QA_EFF_INTENSITY/5000) * 10))
			{
			Q_Forge->Forge[AIcounter].QAEFF_CNTR01[25] = 0;

			jet=0;
			while((jet < (2 + (45 * (QA_EFF_INTENSITY/5000))) * _->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 23;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

				if(Q_Forge->Forge[AIcounter].QAEFF_CNTR02[25] == 0) Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 2;
				else Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 10 + (20 * (QA_EFF_INTENSITY/5000));
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = AIcounter;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
				Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;
				Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = Q_Forge->Forge[AIcounter].QAEFF_CNTR02[25];
				Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
				Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[25];
				Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

				Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[25] += (6.283 / (2 + (45 * (QA_EFF_INTENSITY/5000))));

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_Forge->Forge[AIcounter].QAEFF_ROTAMT[25]);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}
			}
		}break;

	}//END SWITCH
#endif
}//CLOSE FUNCCALL


void Q_COREFunctions::ActivateItems(void)
{
	//###- ACTIVATE ITEMS
	int AIcounter=0;
	while(AIcounter < 4)
		{
		if(AIcounter == 0) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR;

		if(AIcounter == 1) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR;

		if(AIcounter == 2) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR;

		if(AIcounter == 3) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON;

		if(player[g_Player]->QA_ITEMREF >= 0 && player[g_Player]->QA_ITEMREF < 150)
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_IntBoost * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Height * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Weight * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Strength * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Quickness * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Constitution * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_AggPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_DefPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed += (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_JINKmovespeed * player[g_Player]->JINK3_PowerFactor) / 10;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_JINKpower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_JINK3intensity * player[g_Player]->JINK3_PowerFactor;
			}

		AIcounter++;
		}


	//###- ACTIVATE MECH ITEM
	if(player[g_Player]->Mech.ACTIVE == 1)
		{
		player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH;

		if(player[g_Player]->QA_ITEMREF >= 0 && player[g_Player]->QA_ITEMREF < 150)
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_IntBoost * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Height * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Weight * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Strength * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Quickness * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Constitution * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_AggPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_DefPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed += (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_JINKmovespeed * player[g_Player]->JINK3_PowerFactor) / 10;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_JINKpower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_JINK3intensity * player[g_Player]->JINK3_PowerFactor;
			}
		}


	//###- ACTIVATE SPELLS
	AIcounter=0;
	while(AIcounter < 3)
		{
		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].LIVE == 1)
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_IntBoost * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Height * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Weight * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Strength * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Quickness * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Constitution * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_AggPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_DefPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed += (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_JINKmovespeed * player[g_Player]->JINK3_PowerFactor) / 6.5;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_JINKpower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity += player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_JINK3intensity * player[g_Player]->JINK3_PowerFactor;
			}

		AIcounter++;
		}


	//###- ACTIVATE ZONE
	if(player[g_Player]->EnergyArchitect.ZONING == 1)
		{
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_intBoost * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Height * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Weight * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Strength * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Quickness * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Constitution * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_AggPower * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_DefPower * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_JINKmovespeed * player[g_Player]->JINK3_PowerFactor) / 15;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_JINKpower * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity += Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_JINK3intensity * player[g_Player]->JINK3_PowerFactor;
		}

	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence = 5;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower = 100;

	//Out of Bounds Adjust
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower < 5) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower = 5;
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower > 100) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower = 100;

	//#### RESET SCALE AND LIGHTING
	if(player[g_Player]->Mech.ACTIVE == 0)
		{
		Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[1].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[2].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[3].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		}
	else
		{
		Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[1].Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[2].Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[3].Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		}

	//##### Set Attack Speed relative to size

	if(player[g_Player]->Mech.ACTIVE == 0)
		{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = (0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8)) / (1 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2))); }
	else
		{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = (0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8)) / ((1 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2))) * 2.7907); }

	//#### SPEED RESTRICTIONS
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness > 1.9) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 1.9;

	player[g_Player]->Mins.x = -(25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	player[g_Player]->Mins.y = -(45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	player[g_Player]->Mins.z = -(25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	player[g_Player]->Maxs.x = (25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	player[g_Player]->Maxs.y = (45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	player[g_Player]->Maxs.z = (25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->Mins.x = -(20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	playerAV[g_Player]->Mins.y = -(45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	playerAV[g_Player]->Mins.z = -(20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	playerAV[g_Player]->Maxs.x = (20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	playerAV[g_Player]->Maxs.y = (45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	playerAV[g_Player]->Maxs.z = (20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	fogbox.Min.x = playerAV[g_Player]->Mins.x;
	fogbox.Min.y = playerAV[g_Player]->Mins.y;
	fogbox.Min.z = playerAV[g_Player]->Mins.z;
	fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	fogbox.Max.z = playerAV[g_Player]->Maxs.z;

	Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	Qpo->Avatar_SetExtBox(&playerAV[g_Player]->Avatar, &fogbox, "BIP01");

	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);

	//###- Assign Weapon Avatar - ###//
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON < 150)
		{
		player[g_Player]->Weapon.Avatar = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF;
		}

	if(player[g_Player]->Weapon.Avatar <= 0 || player[g_Player]->Weapon.Avatar > 12) player[g_Player]->Weapon.Avatar = 12;
	}


void Q_COREFunctions::DeactivateItems(void)
	{
	//###- DEACTIVATE ITEMS
	int AIcounter=0;

	while(AIcounter < 4)
		{
		if(AIcounter == 0) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR;

		if(AIcounter == 1) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR;

		if(AIcounter == 2) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR;

		if(AIcounter == 3) player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON;

		if(player[g_Player]->QA_ITEMREF >= 0 && player[g_Player]->QA_ITEMREF < 150)
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_IntBoost * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Height * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Weight * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Strength * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Quickness * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Constitution * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_AggPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_DefPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed = 0;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower = 0;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity = 0;
			}

		AIcounter++;
		}

	if(player[g_Player]->Mech.ACTIVE != 0)
		{
		player[g_Player]->QA_ITEMREF = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrMECH;

		if(player[g_Player]->QA_ITEMREF >= 0 && player[g_Player]->QA_ITEMREF < 150)
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_IntBoost * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Height * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Weight * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Strength * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Quickness * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_Constitution * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_AggPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_DefPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed = 0;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower = 0;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity = 0;
			}
		}


	//###- DEACTIVATE SPELLS
	AIcounter=0;
	while(AIcounter < 3)
		{
		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].LIVE == 1)
			{
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_IntBoost * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Height * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Weight * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Strength * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Quickness * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_Constitution * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_AggPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_DefPower * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover -= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[AIcounter].QA_SPELLINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed = 0;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower = 0;
			player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity = 0;
			}

		AIcounter++;
		}


	//###- DEACTIVATE ZONE
	if(player[g_Player]->EnergyArchitect.ZONING == 1)
		{
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_intBoost * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_EnergyEff * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Height * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Weight * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Strength * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Quickness * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Dexterity * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Constitution * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_AggPower * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_DefPower * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RArmStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LArmStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RLegStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LLegStr * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RArmSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LArmSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_RLegSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_LLegSnap * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPAccuracy * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPDrawSPD * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPReloadSPD * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_WEPRecoilHR * player[g_Player]->JINK3_PowerFactor;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed = 0;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower = 0;
		player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity = 0;
		}


	//#### RESET SCALE AND LIGHTING
	if(player[g_Player]->Mech.ACTIVE == 0)
		{
		Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[1].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[2].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[3].Avatar, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		}

	if(player[g_Player]->Mech.ACTIVE == 1)
		{
		Qpo->Avatar_SetScale(&playerAV[g_Player]->Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[1].Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[2].Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&player[g_Player]->Shadows[3].Avatar, 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)),0.43 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
		}

	//##### Set Attack Speed relative to size
	if(player[g_Player]->Mech.ACTIVE == 0)
		{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = (0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8)) / (1 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2))); }
	else
		{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = (0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8)) / ((1 + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2))) * 2.7907); }

	//#### SPEED RESTRICTIONS
	if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness > 1.9) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 1.9;

	player[g_Player]->Mins.x = -(25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	player[g_Player]->Mins.y = -(45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	player[g_Player]->Mins.z = -(25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	player[g_Player]->Maxs.x = (25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	player[g_Player]->Maxs.y = (45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	player[g_Player]->Maxs.z = (25 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	playerAV[g_Player]->Mins.x = -(20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	playerAV[g_Player]->Mins.y = -(45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	playerAV[g_Player]->Mins.z = -(20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	playerAV[g_Player]->Maxs.x = (20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	playerAV[g_Player]->Maxs.y = (45 + (15*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));
	playerAV[g_Player]->Maxs.z = (20 + (10*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2)));

	fogbox.Min.x = playerAV[g_Player]->Mins.x;
	fogbox.Min.y = playerAV[g_Player]->Mins.y;
	fogbox.Min.z = playerAV[g_Player]->Mins.z;
	fogbox.Max.x = playerAV[g_Player]->Maxs.x;
	fogbox.Max.y = playerAV[g_Player]->Maxs.y;
	fogbox.Max.z = playerAV[g_Player]->Maxs.z;

	Qpo->Avatar_SetExtBox(&playerAV[g_Player]->Avatar, &fogbox, "BIP01");

	//####### RELATIVE ATTACK SPEED
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELQuickness = 0.2 + (((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELEnergyEff = 1 + ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff / 6000);
	}


void Q_COREFunctions::ActivateItemsAI(int AIcounter)
	{
	//###- ACTIVATE ITEMSe
	int AIr = 0;
	while(AIr < 4)
		{
		if(AIr == 0) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrHEADARMOUR;

		if(AIr == 1) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrUPPERARMOUR;

		if(AIr == 2) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrLOWERARMOUR;

		if(AIr == 3) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON;

		if(Q_Forge->Forge[AIcounter].QA_ITEMREF >= 0 && Q_Forge->Forge[AIcounter].QA_ITEMREF < 150)
			{
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_IntBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed += (Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_JINKmovespeed * Q_Forge->Forge[AIcounter].JINK3_PowerFactor) / 10;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_JINKpower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_JINK3intensity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			}

		AIr++;
		}

	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE != 0)
		{
		Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrMECH;

		if(Q_Forge->Forge[AIcounter].QA_ITEMREF >= 0 && Q_Forge->Forge[AIcounter].QA_ITEMREF < 150)
			{
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_IntBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed += (Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_JINKmovespeed * Q_Forge->Forge[AIcounter].JINK3_PowerFactor) / 10;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_JINKpower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity += Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_JINK3intensity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			}
		}

	//###- ACTIVATE SPELLS
	AIr = 0;
	while(AIr < 3)
		{
		if(Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].LIVE == 1)
			{
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_IntBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed += (Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_JINKmovespeed * Q_Forge->Forge[AIcounter].JINK3_PowerFactor) / 10;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_JINKpower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity += Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_JINK3intensity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			}

		AIr++;
		}


	//###- ACTIVATE ZONE
	if(Q_Forge->Forge[AIcounter].EnergyArchitect.ZONING == 1)
		{
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_intBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_JINKmovespeed * Q_Forge->Forge[AIcounter].JINK3_PowerFactor) / 15;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_JINKpower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity += Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_JINK3intensity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		}

	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence = 5;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower = 100;

	//Out of Bounds Adjust
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower < 5) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower = 5;
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower > 100) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower = 100;

	//#### RESET SCALE AND LIGHTING
	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 0)
		{
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].AV.Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[1].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[2].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[3].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		}

	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 1)
		{
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].AV.Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[1].Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[2].Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[3].Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		}

	//##### Set Attack Speed relative to size
	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 0)
		{ Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = (0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8)) / (1 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2))); }
	else
		{ Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = (0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8)) / ((1 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2))) * 2.7907); }

	//#### SPEED RESTRICTIONS
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness > 1.9) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = 1.9;


	//#### RESET SCALE AND LIGHTING
	Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].AV.Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[1].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[2].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[3].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

	Q_Forge->Forge[AIcounter].AV.Mins.x = -(20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our Q_Forge->Forge[AIcounter] which is used for
	Q_Forge->Forge[AIcounter].AV.Mins.y = -(45 + (15*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	Q_Forge->Forge[AIcounter].AV.Mins.z = -(20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].AV.Maxs.x = (20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].AV.Maxs.y = (45 + (15*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].AV.Maxs.z = (20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

	fogbox.Min.x = Q_Forge->Forge[AIcounter].AV.Mins.x;
	fogbox.Min.y = Q_Forge->Forge[AIcounter].AV.Mins.y;
	fogbox.Min.z = Q_Forge->Forge[AIcounter].AV.Mins.z;
	fogbox.Max.x = Q_Forge->Forge[AIcounter].AV.Maxs.x;
	fogbox.Max.y = Q_Forge->Forge[AIcounter].AV.Maxs.y;
	fogbox.Max.z = Q_Forge->Forge[AIcounter].AV.Maxs.z;

	Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].AV.Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)),Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Qpo->Avatar_SetExtBox(&Q_Forge->Forge[AIcounter].AV.Avatar, &fogbox, "BIP01");

	//####### RELATIVE ATTACK SPEED
	Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff / 6000);

	if(Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON >= 0 && Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON < 150)
		{
		Q_Forge->Forge[AIcounter].Weapon.Avatar = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF;
		}

	if(Q_Forge->Forge[AIcounter].Weapon.Avatar <= 0 || Q_Forge->Forge[AIcounter].Weapon.Avatar > 12) Q_Forge->Forge[AIcounter].Weapon.Avatar = 12;
	}


void Q_COREFunctions::DeactivateItemsAI(int AIcounter)
	{
	//###- DEACTIVATE ITEMS
	int AIr=0;
	while(AIr < 4)
		{
		if(AIr == 0) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrHEADARMOUR;

		if(AIr == 1) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrUPPERARMOUR;

		if(AIr == 2) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrLOWERARMOUR;

		if(AIr == 3) Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON;

		if(Q_Forge->Forge[AIcounter].QA_ITEMREF >= 0 && Q_Forge->Forge[AIcounter].QA_ITEMREF < 150)
			{
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_IntBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed = 0;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower = 0;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity = 0;
			}

		AIr++;
		}

	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE != 0)
		{
		Q_Forge->Forge[AIcounter].QA_ITEMREF = Q_Forge->Forge[AIcounter].CharDATA.CurrMECH;

		if(Q_Forge->Forge[AIcounter].QA_ITEMREF >= 0 && Q_Forge->Forge[AIcounter].QA_ITEMREF < 150)
			{
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[player[g_Player]->QA_ITEMREF].QA_ITEMINC_IntBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover -= Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].QA_ITEMREF].QA_ITEMINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed = 0;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower = 0;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity = 0;
			}
		}

	//###- DEACTIVATE SPELLS
	AIr = 0;
	while(AIr < 3)
		{
		if(Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].LIVE == 1)
			{
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_IntBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover -= Q_Forge->Forge[AIcounter].CharDATA.SpellSLOT[AIr].QA_SPELLINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed = 0;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower = 0;
			Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity = 0;
			}

		AIr++;
		}


	//###- ACTIVATE ZONE
	if(Q_Forge->Forge[AIcounter].EnergyArchitect.ZONING == 1)
		{
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_intBoost * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_EnergyEff * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Height * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Weight * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Strength * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Quickness * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Dexterity * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_Constitution * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_AggPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_DefPower * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LArmStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LLegStr * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LArmSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_RLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_LLegSnap * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPAccuracy * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPDrawSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPReloadSPD * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover -= Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].ZONEINC_WEPRecoilHR * Q_Forge->Forge[AIcounter].JINK3_PowerFactor;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed = 0;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower = 0;
		Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity = 0;
		}

	//#### RESET SCALE AND LIGHTING
	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 0)
		{
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].AV.Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[1].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[2].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[3].Avatar, Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		}

	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 1)
		{
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].AV.Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[1].Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[2].Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		Qpo->Avatar_SetScale(&Q_Forge->Forge[AIcounter].Shadows[3].Avatar, 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)), 0.43 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
		}

	//##### Set Attack Speed relative to size
	if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 0)
		{ Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = (0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8)) / (1 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2))); }
	else
		{ Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = (0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8)) / ((1 + (0.16*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2))) * 2.7907); }

	//#### SPEED RESTRICTIONS
	if(Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness > 1.9) Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = 1.9;

	Q_Forge->Forge[AIcounter].AV.Mins.x = -(20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //Mins/Maxs set up the bounding box around our player which is used for
	Q_Forge->Forge[AIcounter].AV.Mins.y = -(45 + (15*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));    //collision Detect purposes. It tells it when we are colliding.
	Q_Forge->Forge[AIcounter].AV.Mins.z = -(20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].AV.Maxs.x = (20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].AV.Maxs.y = (45 + (15*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));
	Q_Forge->Forge[AIcounter].AV.Maxs.z = (20 + (10*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight/100)-0.5)*2)));

	fogbox.Min.x = Q_Forge->Forge[AIcounter].AV.Mins.x;
	fogbox.Min.y = Q_Forge->Forge[AIcounter].AV.Mins.y;
	fogbox.Min.z = Q_Forge->Forge[AIcounter].AV.Mins.z;
	fogbox.Max.x = Q_Forge->Forge[AIcounter].AV.Maxs.x;
	fogbox.Max.y = Q_Forge->Forge[AIcounter].AV.Maxs.y;
	fogbox.Max.z = Q_Forge->Forge[AIcounter].AV.Maxs.z;

	Qpo->Avatar_SetExtBox(&Q_Forge->Forge[AIcounter].AV.Avatar, &fogbox, "BIP01");

	//####### RELATIVE ATTACK SPEED
	Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELQuickness = 0.2 + (((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness / 100) * 0.8);

	//####### RELATIVE ENERGY EFFICIENCY
	Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff = 1 + ((float)Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff / 6000);
	}


	//##### AI Jink Blast Control

void Q_COREFunctions::AvatarJinkBlast(int AIcounter)
	{
	Q_Forge->Forge[AIcounter].JinkBLAST -= 2;

	helly=0;
	while(helly < (Q_Forge->Forge[AIcounter].JB_Power / 14))
		{
		//Set Radius
		Q_Forge->Forge[AIcounter].JB_Radius = 50;

		Q_Forge->Forge[AIcounter].JB_Origin = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		Q_Forge->Forge[AIcounter].JB_Pos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		Q_Forge->Forge[AIcounter].JB_Pos.y += 5;

		//#### Locate The Cloud
		Q_Forge->Forge[AIcounter].JB_PlaceVec.x = (((float)rand() / 32767)-0.5)*2;
		Q_Forge->Forge[AIcounter].JB_PlaceVec.z = (((float)rand() / 32767)-0.5)*2;
		Q_Forge->Forge[AIcounter].JB_PlaceVec.y = 0;

		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].JB_PlaceVec);

		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].JB_Pos, Q_Forge->Forge[AIcounter].JB_Radius, &Q_Forge->Forge[AIcounter].JB_PlaceVec, &Q_Forge->Forge[AIcounter].JB_Pos);

		//##### Find Trajectory
		Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].JB_Pos, &Q_Forge->Forge[AIcounter].JB_Origin, &Q_Forge->Forge[AIcounter].JB_TraVec);

		//##### Register the Cloud
		Q_Cloud->Cloud[_->NomCloud].CloudType = 7;

		Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Forge->Forge[AIcounter].JB_Pos;

		Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+170;
		Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.23;

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec = Q_Forge->Forge[AIcounter].JB_TraVec;

		//Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.15) + 0.05;
		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + Q_Forge->Forge[AIcounter].JB_Speed;

		Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

		Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

		_->NomCloud++;
		if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);

		helly++;
		}
	}


void Q_COREFunctions::AvatarJumpEffect(int AIcounter)
	{
	if(Q_Forge->Forge[AIcounter].AJPushOff.Init == 0)
		{
		Q_Forge->Forge[AIcounter].AJPushOff.Init = 1;

		Q_Forge->Forge[AIcounter].AJPushOff.StartFade = 145;
		Q_Forge->Forge[AIcounter].AJPushOff.Radius = 0;

		Q_Forge->Forge[AIcounter].AJPushOff.Pos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		Q_Forge->Forge[AIcounter].AJPushOff.Pos.y += 10;
		

		if(Q_Forge->Forge[AIcounter].AJPushOffType == 0)
			{
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AJPushOff.Leftvec);
			Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AJPushOff.Forvec);
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AJPushOff.Upvec);
			}


		if(Q_Forge->Forge[AIcounter].AJPushOffType == 1)
			{
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AJPushOff.Leftvec);
			Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AJPushOff.Forvec);
			Qpo->Transform_AvatarGetLeft(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AJPushOff.Upvec);

			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AJPushOff.Pos, -45, &Q_Forge->Forge[AIcounter].AJPushOff.Forvec, &Q_Forge->Forge[AIcounter].AJPushOff.Pos);
			}
		}


	if(Q_Forge->Forge[AIcounter].AJPushOff.StartFade > 0)	//250
		{
		Q_Forge->Forge[AIcounter].AJPushOff.Vert1 = Q_Forge->Forge[AIcounter].AJPushOff.Pos;


		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AJPushOff.Vert1, Q_Forge->Forge[AIcounter].AJPushOff.Radius, &Q_Forge->Forge[AIcounter].AJPushOff.Upvec, &Q_Forge->Forge[AIcounter].AJPushOff.Vert1);
								//Distance to the Left of the Q_Forge->Forge[AIcounter]
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AJPushOff.Vert1, Q_Forge->Forge[AIcounter].AJPushOff.Radius, &Q_Forge->Forge[AIcounter].AJPushOff.Leftvec, &Q_Forge->Forge[AIcounter].AJPushOff.Vert1);

						//Distance to the Right of the Q_Forge->Forge[AIcounter] from the left
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AJPushOff.Vert1, -Q_Forge->Forge[AIcounter].AJPushOff.Radius * 2, &Q_Forge->Forge[AIcounter].AJPushOff.Leftvec, &Q_Forge->Forge[AIcounter].AJPushOff.Vert2);

						//Distance to the Top of the Q_Forge->Forge[AIcounter]
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AJPushOff.Vert2, -Q_Forge->Forge[AIcounter].AJPushOff.Radius * 2, &Q_Forge->Forge[AIcounter].AJPushOff.Upvec, &Q_Forge->Forge[AIcounter].AJPushOff.Vert3);

						//Distance to the Top of the Q_Forge->Forge[AIcounter]
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AJPushOff.Vert1, -Q_Forge->Forge[AIcounter].AJPushOff.Radius * 2, &Q_Forge->Forge[AIcounter].AJPushOff.Upvec, &Q_Forge->Forge[AIcounter].AJPushOff.Vert4);

		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].a = Q_Forge->Forge[AIcounter].AJPushOff.StartFade;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].b = 255;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].g = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].r = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].u = 0;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].v = 0;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].x = Q_Forge->Forge[AIcounter].AJPushOff.Vert1.x;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].y = Q_Forge->Forge[AIcounter].AJPushOff.Vert1.y;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0].z = Q_Forge->Forge[AIcounter].AJPushOff.Vert1.z;

		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].a = Q_Forge->Forge[AIcounter].AJPushOff.StartFade;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].b = 255;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].g = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].r = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].u = 1;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].v = 0;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].x = Q_Forge->Forge[AIcounter].AJPushOff.Vert2.x;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].y = Q_Forge->Forge[AIcounter].AJPushOff.Vert2.y;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[1].z = Q_Forge->Forge[AIcounter].AJPushOff.Vert2.z;

		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].a = Q_Forge->Forge[AIcounter].AJPushOff.StartFade;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].b = 255;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].g = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].r = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].u = 1;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].v = 1;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].x = Q_Forge->Forge[AIcounter].AJPushOff.Vert3.x;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].y = Q_Forge->Forge[AIcounter].AJPushOff.Vert3.y;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[2].z = Q_Forge->Forge[AIcounter].AJPushOff.Vert3.z;

		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].a = Q_Forge->Forge[AIcounter].AJPushOff.StartFade;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].b = 255;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].g = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].r = 120;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].u = 0;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].v = 1;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].x = Q_Forge->Forge[AIcounter].AJPushOff.Vert4.x;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].y = Q_Forge->Forge[AIcounter].AJPushOff.Vert4.y;
		Q_Forge->Forge[AIcounter].AJPushOff.Lvert[3].z = Q_Forge->Forge[AIcounter].AJPushOff.Vert4.z;

			
		if(Q_Forge->Forge[AIcounter].AJPushOff.Radius < 200) Q_Forge->Forge[AIcounter].AJPushOff.Radius += (200/10);	//30

		if(Q_Forge->Forge[AIcounter].AJPushOff.Radius >= 100) Q_Forge->Forge[AIcounter].AJPushOff.StartFade -= 30;
			
		Q_Forge->Forge[AIcounter].AJPushOff.MaterialCNT = (( Q_Forge->Forge[AIcounter].AJPushOff.Radius / 200 ) * 31 ) + 11;
		if(Q_Forge->Forge[AIcounter].AJPushOff.MaterialCNT > 42) Q_Forge->Forge[AIcounter].AJPushOff.MaterialCNT = 42;
		if(Q_Forge->Forge[AIcounter].AJPushOff.MaterialCNT < 11) Q_Forge->Forge[AIcounter].AJPushOff.MaterialCNT = 11;

		//FROZEN TO BE FIXED
		Qpo->Poly_AddOnce(&Q_Forge->Forge[AIcounter].AJPushOff.Lvert[0], 4, Medias->PulsarMid[Q_Forge->Forge[AIcounter].AJPushOff.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, 1.0f);
		}
	else
		{
		Q_Forge->Forge[AIcounter].AJPushOffON = 0;
		Q_Forge->Forge[AIcounter].AJPushOff.Init = 0;
		Q_Forge->Forge[AIcounter].AJPushOff.Done = 0;
		}
	}


	//####### AI POWER FLIGHT EFFECTS CONTROL #######

void Q_COREFunctions::CONTROL_AvatarPowerFlight(int AIcounter)
	{
	//#### Increment DUST
	if((Q_Forge->Forge[AIcounter].Mposestate == 16 || Q_Forge->Forge[AIcounter].Mposestate == 15) || (Q_Forge->Forge[AIcounter].Mposestate == 14 && Q_Forge->Forge[AIcounter].attackon == 1) && (Q_Forge->Forge[AIcounter].Aposestate != 200) && (Q_Forge->Forge[AIcounter].Aposestate != 201) && (Q_Forge->Forge[AIcounter].Aposestate != 202) && (Q_Forge->Forge[AIcounter].Aposestate != 203) && (Q_Forge->Forge[AIcounter].Aposestate != 204) && (Q_Forge->Forge[AIcounter].Aposestate != 208))
		{
		if(Q_Forge->Forge[AIcounter].PowerFlightDUSTCNT < 100) Q_Forge->Forge[AIcounter].PowerFlightDUSTCNT += 20 * _->TimeScale;
		else Q_Forge->Forge[AIcounter].PowerFlightDUSTCNT = 100;
		}

	//########  - Dust Cloud Control -  ########

	if(Q_Forge->Forge[AIcounter].PowerFlightDUSTCNT > 0)
		{
		Q_Forge->Forge[AIcounter].PowerFlightDUSTCNT -= 10;

		if(Q_Forge->Forge[AIcounter].CharDATA.Class == 0)
			{
			Q_Forge->Forge[AIcounter].PowerFlightPOWERF = (((1 - (Q_Forge->Forge[AIcounter].JINK3_PowerFactor/50)) * 1000) + 1);
			}

		if(Q_Forge->Forge[AIcounter].CharDATA.Class == 1)
			{
			Q_Forge->Forge[AIcounter].PowerFlightPOWERF = (((1 - (Q_Forge->Forge[AIcounter].JINK3_WeaponFactor/50)) * 1000) + 1);
			}

		if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
			{
			Q_Forge->Forge[AIcounter].PowerFlightPOWERF = (((1 - (Q_Forge->Forge[AIcounter].JINK3_PowerFactor/50)) * 1000) + 1);
			}


		//##### Extend Vec Down to Ground
		Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].Up);

		Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		Q_Forge->Forge[AIcounter].AV.OldPos.y += 20 + (50*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2));
		Q_Forge->Forge[AIcounter].AV.NewPos.y += 20 + (50*(((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height/100)-0.5)*2));

		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, ((Q_Forge->Forge[AIcounter].JINK3_PowerFactor * -7) + 100), &Q_Forge->Forge[AIcounter].Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

		if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
			{
			QpoVec3d f_ImpactVector(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
			Q_Forge->Forge[AIcounter].PowerFlightRADIUS = ((Q_Forge->Forge[AIcounter].JINK3_PowerFactor * 7) + 100) - Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].AV.OldPos, &f_ImpactVector);

			helly=0;
			while(helly < (((Q_Forge->Forge[AIcounter].PowerFlightDUSTCNT / Q_Forge->Forge[AIcounter].PowerFlightPOWERF) * 100) * _->TimeScale))
				{
				//#### Locate The Cloud
				Q_Forge->Forge[AIcounter].JB_PlaceVec.x = (((float)rand() / 32767)-0.5)*2;
				Q_Forge->Forge[AIcounter].JB_PlaceVec.z = (((float)rand() / 32767)-0.5)*2;
				Q_Forge->Forge[AIcounter].JB_PlaceVec.y = 0;
				Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].JB_PlaceVec);

				Q_Forge->Forge[AIcounter].JB_Origin.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
				Q_Cloud->Cloud[_->NomCloud].CloudPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
				Q_Cloud->Cloud[_->NomCloud].CloudPos.y += 5;
				//Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[_->NomCloud].CloudPos, Q_Forge->Forge[AIcounter].PowerFlightRADIUS, &Q_Forge->Forge[AIcounter].JB_PlaceVec, &Q_Cloud->Cloud[_->NomCloud].CloudPos);

				//##### Find Trajectory
				//Qpo->Vec3d_Subtract(&Q_Cloud->Cloud[_->NomCloud].CloudPos, &Q_Forge->Forge[AIcounter].JB_Origin, &Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

				//##### Register the Cloud
				Q_Cloud->Cloud[_->NomCloud].CloudType = 7;
				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+170;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.75;	//0.23
				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + (Q_Forge->Forge[AIcounter].JINK3_PowerFactor * 0.01);
				Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;
				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);

				helly++;
				}
			}
		}
	}
};