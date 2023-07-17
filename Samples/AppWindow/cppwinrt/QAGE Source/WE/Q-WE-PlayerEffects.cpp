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

using namespace GVARS;

namespace GVARS
{

//##### -+ Effects Control Stage +- #####

void Q_COREFunctions::QAEFFcontrolPLAYER(int QA_EFF_TYPE, float QA_EFF_INTENSITY, int QA_EFF_COL00RED, int QA_EFF_COL00GREEN, int QA_EFF_COL00BLUE, int QA_EFF_COL00ALPHA)
{
	//QA_EFF_TYPE = rand() % 25;

	//printf("QA_EFF_TYPE %i\n", QA_EFF_TYPE);

	switch(QA_EFF_TYPE)
		{
		case 1:		//Medias->QAEFF01 --- WEAPON ACCURACY
			{
			if(player[g_Player]->WeaponStatus > 1)
				{
				player[g_Player]->QAEFF_CNTR01[1] += (1 * _->TimeScale);
				player[g_Player]->QAEFF_ROTAMT[1] = 0;

				//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->QA_EFF_BONEMATRIX);

				if(player[g_Player]->QAEFF_CNTR02[1] <= 5)
					{
					player[g_Player]->QAEFF_CNTR02[1] = 33;
					player[g_Player]->QAEFF_ROTAMT[1] = 0;
					}
				player[g_Player]->QAEFF_CNTR02[1] -= (0.1 + (0.65 * (1 - (QA_EFF_INTENSITY / 10000.0f))));

				Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
				Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, player[g_Player]->QAEFF_CNTR02[1], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

				if(player[g_Player]->QAEFF_CNTR01[1] > (3 + (25 * (1 - (QA_EFF_INTENSITY / 10000.0f)))))
					{
					player[g_Player]->QAEFF_CNTR01[1] = 0;

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
						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
						Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
						Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
						Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[1];
						Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[1];
						Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

						Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
							//Calculate Direction Vectors
						Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
						Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
						Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
						Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
						Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
						Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[1]);

						player[g_Player]->QAEFF_ROTAMT[1] += 0.628;

						Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
						Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}

					}
				else player[g_Player]->QAEFF_ROTAMT[1] += 0.628;
				}

			} break;


		case 2:		//Medias->QAEFF02 --- WEAPON DRAW SPEED
			{
			player[g_Player]->QAEFF_CNTR01[2] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[2] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 NECK", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR01[2] > 55)
				{
				player[g_Player]->QAEFF_CNTR01[2] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedMAX = 1.5 + (6 * (QA_EFF_INTENSITY / 10000.0f));
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += 2;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_PntSprite->PntSprite[_->NomPntSprite].Pos;
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[2];
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[2]);
					player[g_Player]->QAEFF_ROTAMT[2] += 0.314;
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
			player[g_Player]->QAEFF_CNTR01[3] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[3] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 NECK", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR01[3] > 55)
				{
				player[g_Player]->QAEFF_CNTR01[3] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedMAX = 1.5 + (6 * (QA_EFF_INTENSITY / 10000.0f));
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[3];
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[3]);
					player[g_Player]->QAEFF_ROTAMT[3] += 0.314;
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
			if(player[g_Player]->WeaponStatus > 1)
				{
				player[g_Player]->QAEFF_CNTR01[4] += (1 * _->TimeScale);
				player[g_Player]->QAEFF_ROTAMT[4] = 0;

				//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->QA_EFF_BONEMATRIX);

				if(player[g_Player]->QAEFF_CNTR02[4] >= 30) player[g_Player]->QAEFF_CNTR02[4] = 0;
				player[g_Player]->QAEFF_CNTR02[4] += 1;
			
				Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
				Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[4], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

				if(player[g_Player]->QAEFF_CNTR01[4] > (1 + (10 * (1 - (QA_EFF_INTENSITY / 10000.0f)))))
					{
					player[g_Player]->QAEFF_CNTR01[4] = 0;

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

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = (15 + (45 * (player[g_Player]->TestVALUE01/10000)));
						Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
						Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
						Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
						Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
						Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[4];
						Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[4];
						Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

						Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

							//Calculate Direction Vectors
						Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
						Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

						Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
						Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
						Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
						Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[4]);

						player[g_Player]->QAEFF_ROTAMT[4] += 0.314;

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
			player[g_Player]->QAEFF_CNTR01[5] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[5] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR01[5] > 55)
				{
				player[g_Player]->QAEFF_CNTR01[5] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedMAX = 1.5 + (6 * (QA_EFF_INTENSITY/250));
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += 2.5;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = Q_PntSprite->PntSprite[_->NomPntSprite].Pos;
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[5];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[5]);

					player[g_Player]->QAEFF_ROTAMT[5] += 0.314;

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
			player[g_Player]->QAEFF_CNTR03[8] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT01[8] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR04[8] <= 0) player[g_Player]->QAEFF_CNTR04[8] = 20;
			player[g_Player]->QAEFF_CNTR04[8] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR04[8], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR03[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR03[8] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR04[8];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT01[8];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);

					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT01[8]);
					player[g_Player]->QAEFF_ROTAMT01[8] += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			player[g_Player]->QAEFF_CNTR05[8] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT02[8] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR06[8] <= 0) player[g_Player]->QAEFF_CNTR06[8] = 20;
			player[g_Player]->QAEFF_CNTR06[8] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR06[8], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR05[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR05[8] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR06[8];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT02[8];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT02[8]);

					player[g_Player]->QAEFF_ROTAMT02[8] += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			player[g_Player]->QAEFF_CNTR07[8] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT05[8] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR08[8] <= 0) player[g_Player]->QAEFF_CNTR08[8] = 20;
			player[g_Player]->QAEFF_CNTR08[8] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR08[8], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR07[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR07[8] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR08[8];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT05[8];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);

					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT05[8]);
					player[g_Player]->QAEFF_ROTAMT05[8] += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			player[g_Player]->QAEFF_CNTR09[8] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT06[8] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR10[8] <= 0) player[g_Player]->QAEFF_CNTR10[8] = 20;
			player[g_Player]->QAEFF_CNTR10[8] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR10[8], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR09[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR09[8] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR10[8];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT06[8];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT06[8]);

					player[g_Player]->QAEFF_ROTAMT06[8] += 0.314;

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
			player[g_Player]->QAEFF_CNTR01[9] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[9] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			player[g_Player]->QAEFF_CNTR02[9] += (1 * _->TimeScale);
			if(player[g_Player]->QAEFF_CNTR02[9] >= 20) player[g_Player]->QAEFF_CNTR02[9] = -4;
		
			//Edit Up->In
			Qpo->Transform_GetIn(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, player[g_Player]->QAEFF_CNTR02[9], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[9] > (14 - (6 * (QA_EFF_INTENSITY/500))))
				{
				player[g_Player]->QAEFF_CNTR01[9] = 0;

				jet=0;
				while(jet < ((2 + (30 * (QA_EFF_INTENSITY/500))) * _->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 30;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 20;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[9];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].CoronaON = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].CoronaALPHADIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].CoronaALPHA = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[9];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors

					//Edit Y->Z
					//Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					//Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Transform_GetLeft(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					//Edit Y->Z
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[9]);

					player[g_Player]->QAEFF_ROTAMT[9] += (6.283 / (2 + (30 * (QA_EFF_INTENSITY/500))));

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
			player[g_Player]->QAEFF_CNTR01[10] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[10] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[10] >= 20) player[g_Player]->QAEFF_CNTR02[10] = -4;
			player[g_Player]->QAEFF_CNTR02[10] += (1 * _->TimeScale);
		
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, player[g_Player]->QAEFF_CNTR02[10], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[10] > 8)
				{
				player[g_Player]->QAEFF_CNTR01[10] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[10];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[10];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[10]);

					player[g_Player]->QAEFF_ROTAMT[10] += 0.571;

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
			player[g_Player]->QAEFF_CNTR03[8] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT01[8] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR04[8] <= 0) player[g_Player]->QAEFF_CNTR04[8] = 20;
			player[g_Player]->QAEFF_CNTR04[8] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetIn(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR04[8], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR03[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR03[8] = 0;

				jet=0;
				while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 32;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 35;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR04[8];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT01[8];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
					Qpo->Transform_New_ZRotation(&RotateMatrix, PI/2);

					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_ZRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT01[8]);
					player[g_Player]->QAEFF_ROTAMT01[8] += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetUp(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			} break;


		case 12:	//Medias->QAEFF10 --- AGGRESSIVE POWER BOOST
			{
			player[g_Player]->QAEFF_CNTR01[12] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[12] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[12] >= 20) player[g_Player]->QAEFF_CNTR02[12] = -4;
			player[g_Player]->QAEFF_CNTR02[12] += (0.35 * _->TimeScale);
		
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, player[g_Player]->QAEFF_CNTR02[12], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
				{
				player[g_Player]->QAEFF_CNTR01[12] = 0;

				jet=0;
				while((jet < (2 + (10 * (QA_EFF_INTENSITY/5000)))) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;
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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[12];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[12];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[12]);

					player[g_Player]->QAEFF_ROTAMT[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}

				}

			player[g_Player]->QAEFF_CNTR03[12] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT01[12] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR04[12] <= 0) player[g_Player]->QAEFF_CNTR04[12] = 20;
			player[g_Player]->QAEFF_CNTR04[12] -= (0.35 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR04[12], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR03[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
				{
				player[g_Player]->QAEFF_CNTR03[12] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR04[12];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT01[12];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT01[12]);

					player[g_Player]->QAEFF_ROTAMT01[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			player[g_Player]->QAEFF_CNTR05[12] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT02[12] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR06[12] <= 0) player[g_Player]->QAEFF_CNTR06[12] = 20;
			player[g_Player]->QAEFF_CNTR06[12] -= (0.35 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX01, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX01.Translation, -player[g_Player]->QAEFF_CNTR06[12], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX01.Translation);

			if(player[g_Player]->QAEFF_CNTR05[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
				{
				player[g_Player]->QAEFF_CNTR05[12] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR06[12];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT02[12];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT02[12]);

					player[g_Player]->QAEFF_ROTAMT02[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}


			player[g_Player]->QAEFF_CNTR07[12] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT03[12] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR08[12] <= 0) player[g_Player]->QAEFF_CNTR08[12] = 20;
			player[g_Player]->QAEFF_CNTR08[12] -= (0.35 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR08[12], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR07[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
				{
				player[g_Player]->QAEFF_CNTR07[12] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR08[12];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT03[12];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT03[12]);

					player[g_Player]->QAEFF_ROTAMT03[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			player[g_Player]->QAEFF_CNTR09[12] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT04[12] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR10[12] <= 0) player[g_Player]->QAEFF_CNTR10[12] = 20;
			player[g_Player]->QAEFF_CNTR10[12] -= (0.35 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX01, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX01.Translation, -player[g_Player]->QAEFF_CNTR10[12], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX01.Translation);

			if(player[g_Player]->QAEFF_CNTR09[12] > (20 - (8 * (QA_EFF_INTENSITY/5000))))
				{
				player[g_Player]->QAEFF_CNTR09[12] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR10[12];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT04[12];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT04[12]);

					player[g_Player]->QAEFF_ROTAMT04[12] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

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
			player[g_Player]->QAEFF_CNTR01[13] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[13] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[13] >= 20) player[g_Player]->QAEFF_CNTR02[13] = -4;
			player[g_Player]->QAEFF_CNTR02[13] += (0.4 * _->TimeScale);
		
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, player[g_Player]->QAEFF_CNTR02[13], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[13] > (30 - (8 * (QA_EFF_INTENSITY/500))))
				{
				player[g_Player]->QAEFF_CNTR01[13] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[13];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[13];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[13]);

					player[g_Player]->QAEFF_ROTAMT[13] += (6.283 / (2 + (10 * (QA_EFF_INTENSITY/5000))));

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
			player[g_Player]->QAEFF_CNTR01[14] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[14] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[14] <= 0) player[g_Player]->QAEFF_CNTR02[14] = 20;
			player[g_Player]->QAEFF_CNTR02[14] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[14], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[14] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR01[14] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[14];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[14];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[14]);

					player[g_Player]->QAEFF_ROTAMT[14] += 0.314;

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
			player[g_Player]->QAEFF_CNTR01[15] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[15] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[15] <= 0) player[g_Player]->QAEFF_CNTR02[15] = 20;
			player[g_Player]->QAEFF_CNTR02[15] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[15], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[15] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR01[15] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[15];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[15];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[15]);

					player[g_Player]->QAEFF_ROTAMT[15] += 0.314;

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
			player[g_Player]->QAEFF_CNTR01[16] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[16] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[16] <= 0) player[g_Player]->QAEFF_CNTR02[16] = 20;
			player[g_Player]->QAEFF_CNTR02[16] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[16], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[16] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR01[16] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[16];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[16];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[16]);

					player[g_Player]->QAEFF_ROTAMT[16] += 0.314;

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
			player[g_Player]->QAEFF_CNTR01[17] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[17] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[17] <= 0) player[g_Player]->QAEFF_CNTR02[17] = 20;
			player[g_Player]->QAEFF_CNTR02[17] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[17], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[17] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR01[17] = 0;

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
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[17];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[17];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[17]);

					player[g_Player]->QAEFF_ROTAMT[17] += 0.314;

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
			player[g_Player]->QAEFF_CNTR01[18] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[18] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[18] <= 0) player[g_Player]->QAEFF_CNTR02[18] = 20;
			player[g_Player]->QAEFF_CNTR02[18] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[18], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[18] > 8)
				{
				player[g_Player]->QAEFF_CNTR01[18] = 0;

				jet=0;
				while((jet < 10) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 53;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[18];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[18];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[18]);

					player[g_Player]->QAEFF_ROTAMT[18] += 0.628;

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
			player[g_Player]->QAEFF_CNTR01[19] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[19] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[19] <= 0) player[g_Player]->QAEFF_CNTR02[19] = 20;
			player[g_Player]->QAEFF_CNTR02[19] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[19], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[19] > 8)
				{
				player[g_Player]->QAEFF_CNTR01[19] = 0;

				jet=0;
				while((jet < 10) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 52;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[19];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[19];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[19]);

					player[g_Player]->QAEFF_ROTAMT[19] += 0.628;

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
			player[g_Player]->QAEFF_CNTR01[20] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[20] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[20] <= 0) player[g_Player]->QAEFF_CNTR02[20] = 20;
			player[g_Player]->QAEFF_CNTR02[20] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[20], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[20] > 8)
				{
				player[g_Player]->QAEFF_CNTR01[20] = 0;

				jet=0;
				while((jet < 10) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 55;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[20];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[20];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[20]);

					player[g_Player]->QAEFF_ROTAMT[20] += 0.628;

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
			player[g_Player]->QAEFF_CNTR01[21] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[21] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR02[21] <= 0) player[g_Player]->QAEFF_CNTR02[21] = 20;
			player[g_Player]->QAEFF_CNTR02[21] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR02[21], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR01[21] > 8)
				{
				player[g_Player]->QAEFF_CNTR01[21] = 0;

				jet=0;
				while((jet < 10) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 54;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[21];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[21];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[21]);

					player[g_Player]->QAEFF_ROTAMT[21] += 0.628;

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
	#if 0
			player[g_Player]->QA_EFF_BONEMATRIX_MEM = player[g_Player]->QA_EFF_BONEMATRIX_STR;
			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE1", &player[g_Player]->QA_EFF_BONEMATRIX_STR);

			player[g_Player]->QA_EFF_MEMLENGTH = Qpo->Vec3d_DistanceBetween(&player[g_Player]->QA_EFF_BONEMATRIX_STR.Translation, &player[g_Player]->QA_EFF_BONEMATRIX_MEM.Translation);

			Qpo->Vec3d_Subtract(&player[g_Player]->QA_EFF_BONEMATRIX_STR.Translation, &player[g_Player]->QA_EFF_BONEMATRIX_MEM.Translation, &player[g_Player]->QA_EFF_MEMVEC);

			if(player[g_Player]->QA_EFF_MEMLENGTH > 1)
				{
				SCRAMJET=0;
				while(SCRAMJET < 5)
					{
					player[g_Player]->QA_EFF_MEMPOS = player[g_Player]->QA_EFF_BONEMATRIX_MEM.Translation;
					player[g_Player]->QA_EFF_MEMMOVE = SCRAMJET / (player[g_Player]->QA_EFF_MEMLENGTH / 50);
					Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_MEMPOS, player[g_Player]->QA_EFF_MEMMOVE * _->TimeScale, &player[g_Player]->QA_EFF_MEMVEC, &player[g_Player]->QA_EFF_MEMPOS);

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
						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = player[g_Player]->QA_EFF_MEMLENGTH/3;
						Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_MEMPOS;

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*20;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*30;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*20;

						Qpo->Vec3d_Normalize(&player[g_Player]->QA_EFF_MEMVEC);

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec = player[g_Player]->QA_EFF_MEMVEC;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x += (((float)rand() / 32767)-0.5)*0.25;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y += (((float)rand() / 32767)-0.5)*0.25;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z += (((float)rand() / 32767)-0.5)*0.25;
					
						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}

					SCRAMJET++;
					}
				}
	#endif
			}break;


		case 25:	//Medias->QAEFF21 --- INTELLIGENCE BOOST
			{
			player[g_Player]->QAEFF_CNTR01[25] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT[25] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);
			player[g_Player]->QA_EFF_BONEMATRIX.Translation.y += 10;

			player[g_Player]->QAEFF_CNTR02[25] += (1 * _->TimeScale);
			if(player[g_Player]->QAEFF_CNTR02[25] > 15) player[g_Player]->QAEFF_CNTR02[25] = 0;

			player[g_Player]->QA_EFF_BONEMATRIX.Translation.y -= player[g_Player]->QAEFF_CNTR02[25];

			if(player[g_Player]->QAEFF_CNTR01[25] > ((QA_EFF_INTENSITY/5000) * 10))
				{
				player[g_Player]->QAEFF_CNTR01[25] = 0;

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

					if(player[g_Player]->QAEFF_CNTR02[25] == 0) Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 2;
					else Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 10 + (20 * (QA_EFF_INTENSITY/5000));
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR02[25];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT[25];
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
				
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					player[g_Player]->QAEFF_ROTAMT[25] += (6.283 / (2 + (45 * (QA_EFF_INTENSITY/5000))));

					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[25]);
					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			}break;

		case 26:	//Medias->QAEFF09 --- CONSTITUTION BOOST V2
			{
			player[g_Player]->QAEFF_CNTR03[8] += (1 * _->TimeScale);
			player[g_Player]->QAEFF_ROTAMT01[8] = 0;

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(player[g_Player]->QAEFF_CNTR04[8] <= 0) player[g_Player]->QAEFF_CNTR04[8] = 20;
			player[g_Player]->QAEFF_CNTR04[8] -= (1 * _->TimeScale);
	
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&player[g_Player]->QA_EFF_BONEMATRIX.Translation, -player[g_Player]->QAEFF_CNTR04[8], &player[g_Player]->In, &player[g_Player]->QA_EFF_BONEMATRIX.Translation);

			if(player[g_Player]->QAEFF_CNTR03[8] > (14 - (4 * (QA_EFF_INTENSITY / 500))))
				{
				player[g_Player]->QAEFF_CNTR03[8] = 0;

				jet=0;
				while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0195f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 32;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = QA_EFF_COL00RED;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = QA_EFF_COL00GREEN;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = QA_EFF_COL00BLUE;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 35;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaSTR = Q_PntSprite->PntSprite[_->NomPntSprite].Alpha;
					Q_PntSprite->PntSprite[_->NomPntSprite].AlphaLOCK = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
					Q_PntSprite->PntSprite[_->NomPntSprite].HeightPos = player[g_Player]->QAEFF_CNTR04[8];
					Q_PntSprite->PntSprite[_->NomPntSprite].PushOUT = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].QA_EFF_INTENSITY = QA_EFF_INTENSITY;
					Q_PntSprite->PntSprite[_->NomPntSprite].RotAMT = player[g_Player]->QAEFF_ROTAMT01[8];

					Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp);
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);

					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT01[8]);
					player[g_Player]->QAEFF_ROTAMT01[8] += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			} break;

		}//END SWITCH

}//CLOSE FUNCCALL


	//########  - Jink Rush Cloud Control -  ########

void Q_COREFunctions::PlayerJinkRushCloud(void)
{
	//#### TEMP
	if(player[g_Player]->attackon == 0) player[g_Player]->JinkRUSHCLOUD = 0;

	Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE2", &BoneMat);
	Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &BoneMat);
	//Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->JRC_InVecBack);

	QpoVec3d JRC_UpVecBack;

	Qpo->Transform_GetLeft(&BoneMat,&player[g_Player]->JRC_InVecBack);
	Qpo->Transform_GetUp(&BoneMat,&JRC_UpVecBack);
	player[g_Player]->JRC_InVec = player[g_Player]->JRC_InVecBack;
	Qpo->Vec3d_Inverse(&player[g_Player]->JRC_InVec);

	helly=0;
	//while(helly < (player[g_Player]->JRC_Power * 10))
	while(helly < (player[g_Player]->JRC_Power * 5))
		{
		//Set Radius
		player[g_Player]->JRC_Radius = 30;

		player[g_Player]->JRC_Origin = BoneMat.Translation;
		player[g_Player]->JRC_Pos = BoneMat.Translation;
		//Qpo->Vec3d_AddScaled(&player[g_Player]->JRC_Pos, 10, &player[g_Player]->JRC_InVec, &player[g_Player]->JRC_Pos);
		Qpo->Vec3d_AddScaled(&player[g_Player]->JRC_Pos, 3, &player[g_Player]->JRC_InVec, &player[g_Player]->JRC_Pos);
		Qpo->Vec3d_AddScaled(&player[g_Player]->JRC_Pos, 3, &JRC_UpVecBack, &player[g_Player]->JRC_Pos);

		//#### Locate The Cloud
		player[g_Player]->JRC_PlaceVec.x = (((float)rand() / 32767)-0.5)*2;
		player[g_Player]->JRC_PlaceVec.z = (((float)rand() / 32767)-0.5)*2;
		player[g_Player]->JRC_PlaceVec.y = (((float)rand() / 32767)-0.5)*2;

		Qpo->Vec3d_Normalize(&player[g_Player]->JRC_PlaceVec);

		player[g_Player]->JRC_SKIP = 0;

		if(Qpo->Vec3d_DistanceBetween(&player[g_Player]->JRC_PlaceVec, &player[g_Player]->JRC_InVec) < 1.24	//0.9
			|| Qpo->Vec3d_DistanceBetween(&player[g_Player]->JRC_PlaceVec, &player[g_Player]->JRC_InVecBack) < 1.25)
			{ player[g_Player]->JRC_SKIP = 1; }

		if(player[g_Player]->JRC_SKIP == 0)
			{
			Qpo->Vec3d_AddScaled(&player[g_Player]->JRC_Pos, player[g_Player]->JRC_Radius, &player[g_Player]->JRC_PlaceVec, &player[g_Player]->JRC_Pos);

			//##### Find Trajectory
			Qpo->Vec3d_Subtract(&player[g_Player]->JRC_Pos, &player[g_Player]->JRC_Origin, &player[g_Player]->JRC_TraVec);

			//##### Register the Cloud
			Q_Cloud->Cloud[_->NomCloud].CloudType = 7;

			Q_Cloud->Cloud[_->NomCloud].CloudPos = player[g_Player]->JRC_Pos;

			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*25)+230;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.17;

			Q_Cloud->Cloud[_->NomCloud].CloudTraVec = player[g_Player]->JRC_TraVec;

			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.025) + (player[g_Player]->JRC_Speed);

			Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
			}

		helly++;
		}
}


//########  - Jink Blast Cloud Control -  ########

void Q_COREFunctions::PlayerJinkBlast(void)
{
	player[g_Player]->JinkBLAST -= 2;

	helly=0;
	while(helly < (player[g_Player]->JB_Power / 14))
		{
		//Set Radius
		player[g_Player]->JB_Radius = 50;

		player[g_Player]->JB_Origin = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->JB_Pos = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->JB_Pos.y += 5;

		//#### Locate The Cloud
		player[g_Player]->JB_PlaceVec.x = (((float)rand() / 32767)-0.5)*2;
		player[g_Player]->JB_PlaceVec.z = (((float)rand() / 32767)-0.5)*2;
		player[g_Player]->JB_PlaceVec.y = 0;

		Qpo->Vec3d_Normalize(&player[g_Player]->JB_PlaceVec);

		Qpo->Vec3d_AddScaled(&player[g_Player]->JB_Pos, player[g_Player]->JB_Radius, &player[g_Player]->JB_PlaceVec, &player[g_Player]->JB_Pos);

		//##### Find Trajectory
		Qpo->Vec3d_Subtract(&player[g_Player]->JB_Pos, &player[g_Player]->JB_Origin, &player[g_Player]->JB_TraVec);

		//##### Register the Cloud
		Q_Cloud->Cloud[_->NomCloud].CloudType = 7;

		Q_Cloud->Cloud[_->NomCloud].CloudPos = player[g_Player]->JB_Pos;

		Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+170;
		Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.23;

		Q_Cloud->Cloud[_->NomCloud].CloudTraVec = player[g_Player]->JB_TraVec;

		//Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.15) + 0.05;
		Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + player[g_Player]->JB_Speed;

		Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

		Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

		_->NomCloud++;
		if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);

		helly++;
		}
}


//#### Jump Special Effects
void Q_COREFunctions::PlayerJumpEffect(void)
{
	if(player[g_Player]->AJPushOff.Init == 0)
		{
		player[g_Player]->AJPushOff.Init = 1;

		player[g_Player]->AJPushOff.StartFade = 145;
		player[g_Player]->AJPushOff.Radius = 0;

		player[g_Player]->AJPushOff.Pos = playerAV[g_Player]->Xform.Translation;
		player[g_Player]->AJPushOff.Pos.y += 10.0f;
		
		if(player[g_Player]->AJPushOffType == 0)
			{
			Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&player[g_Player]->AJPushOff.Leftvec);
			Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->AJPushOff.Forvec);
			Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->AJPushOff.Upvec);
			}

		if(player[g_Player]->AJPushOffType == 1)
			{
			Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&player[g_Player]->AJPushOff.Leftvec);
			Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->AJPushOff.Forvec);
			Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->AJPushOff.Upvec);

			Qpo->Vec3d_AddScaled(&player[g_Player]->AJPushOff.Pos, -45.0f, &player[g_Player]->AJPushOff.Forvec, &player[g_Player]->AJPushOff.Pos);
			}
		}

	if(player[g_Player]->AJPushOff.StartFade > 0)	//250
		{
		player[g_Player]->AJPushOff.Vert1 = player[g_Player]->AJPushOff.Pos;


		Qpo->Vec3d_AddScaled(&player[g_Player]->AJPushOff.Vert1, player[g_Player]->AJPushOff.Radius, &player[g_Player]->AJPushOff.Upvec, &player[g_Player]->AJPushOff.Vert1);
								//Distance to the Left of the player
		Qpo->Vec3d_AddScaled(&player[g_Player]->AJPushOff.Vert1, player[g_Player]->AJPushOff.Radius, &player[g_Player]->AJPushOff.Leftvec, &player[g_Player]->AJPushOff.Vert1);

						//Distance to the Right of the player from the left
		Qpo->Vec3d_AddScaled(&player[g_Player]->AJPushOff.Vert1, -player[g_Player]->AJPushOff.Radius * 2, &player[g_Player]->AJPushOff.Leftvec, &player[g_Player]->AJPushOff.Vert2);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&player[g_Player]->AJPushOff.Vert2, -player[g_Player]->AJPushOff.Radius * 2, &player[g_Player]->AJPushOff.Upvec, &player[g_Player]->AJPushOff.Vert3);

						//Distance to the Top of the player
		Qpo->Vec3d_AddScaled(&player[g_Player]->AJPushOff.Vert1, -player[g_Player]->AJPushOff.Radius * 2, &player[g_Player]->AJPushOff.Upvec, &player[g_Player]->AJPushOff.Vert4);

		player[g_Player]->AJPushOff.Lvert[0].a = player[g_Player]->AJPushOff.StartFade;
		player[g_Player]->AJPushOff.Lvert[0].b = 255;
		player[g_Player]->AJPushOff.Lvert[0].g = 120;
		player[g_Player]->AJPushOff.Lvert[0].r = 120;
		player[g_Player]->AJPushOff.Lvert[0].u = 0;
		player[g_Player]->AJPushOff.Lvert[0].v = 0;
		player[g_Player]->AJPushOff.Lvert[0].x = player[g_Player]->AJPushOff.Vert1.x;
		player[g_Player]->AJPushOff.Lvert[0].y = player[g_Player]->AJPushOff.Vert1.y;
		player[g_Player]->AJPushOff.Lvert[0].z = player[g_Player]->AJPushOff.Vert1.z;

		player[g_Player]->AJPushOff.Lvert[1].a = player[g_Player]->AJPushOff.StartFade;
		player[g_Player]->AJPushOff.Lvert[1].b = 255;
		player[g_Player]->AJPushOff.Lvert[1].g = 120;
		player[g_Player]->AJPushOff.Lvert[1].r = 120;
		player[g_Player]->AJPushOff.Lvert[1].u = 1;
		player[g_Player]->AJPushOff.Lvert[1].v = 0;
		player[g_Player]->AJPushOff.Lvert[1].x = player[g_Player]->AJPushOff.Vert2.x;
		player[g_Player]->AJPushOff.Lvert[1].y = player[g_Player]->AJPushOff.Vert2.y;
		player[g_Player]->AJPushOff.Lvert[1].z = player[g_Player]->AJPushOff.Vert2.z;

		player[g_Player]->AJPushOff.Lvert[2].a = player[g_Player]->AJPushOff.StartFade;
		player[g_Player]->AJPushOff.Lvert[2].b = 255;
		player[g_Player]->AJPushOff.Lvert[2].g = 120;
		player[g_Player]->AJPushOff.Lvert[2].r = 120;
		player[g_Player]->AJPushOff.Lvert[2].u = 1;
		player[g_Player]->AJPushOff.Lvert[2].v = 1;
		player[g_Player]->AJPushOff.Lvert[2].x = player[g_Player]->AJPushOff.Vert3.x;
		player[g_Player]->AJPushOff.Lvert[2].y = player[g_Player]->AJPushOff.Vert3.y;
		player[g_Player]->AJPushOff.Lvert[2].z = player[g_Player]->AJPushOff.Vert3.z;

		player[g_Player]->AJPushOff.Lvert[3].a = player[g_Player]->AJPushOff.StartFade;
		player[g_Player]->AJPushOff.Lvert[3].b = 255;
		player[g_Player]->AJPushOff.Lvert[3].g = 120;
		player[g_Player]->AJPushOff.Lvert[3].r = 120;
		player[g_Player]->AJPushOff.Lvert[3].u = 0;
		player[g_Player]->AJPushOff.Lvert[3].v = 1;
		player[g_Player]->AJPushOff.Lvert[3].x = player[g_Player]->AJPushOff.Vert4.x;
		player[g_Player]->AJPushOff.Lvert[3].y = player[g_Player]->AJPushOff.Vert4.y;
		player[g_Player]->AJPushOff.Lvert[3].z = player[g_Player]->AJPushOff.Vert4.z;

		if(player[g_Player]->AJPushOff.Radius < 200) player[g_Player]->AJPushOff.Radius += (200/10);	//30

		if(player[g_Player]->AJPushOff.Radius >= 100) player[g_Player]->AJPushOff.StartFade -= 30;

		player[g_Player]->AJPushOff.MaterialCNT = (( player[g_Player]->AJPushOff.Radius / 200 ) * 31 ) + 11;
		if(player[g_Player]->AJPushOff.MaterialCNT > 42) player[g_Player]->AJPushOff.MaterialCNT = 42;
		if(player[g_Player]->AJPushOff.MaterialCNT < 11) player[g_Player]->AJPushOff.MaterialCNT = 11;

		//FROZEN TO BE FIXED
		Qpo->Poly_AddOnce(&player[g_Player]->AJPushOff.Lvert[0], 4, Medias->PulsarMid[player[g_Player]->AJPushOff.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, 1.0f);
		}
	else
		{
		player[g_Player]->AJPushOffON = 0;
		player[g_Player]->AJPushOff.Init = 0;
		player[g_Player]->AJPushOff.Done = 0;
		}
}


//####### POWER FLIGHT EFFECTS CONTROL #######

void Q_COREFunctions::CONTROL_PlayerPowerFlight(void)
{
	//#### Increment DUST
	if((player[g_Player]->Mposestate == 16 || player[g_Player]->Mposestate == 15) || (player[g_Player]->Mposestate == 14 && player[g_Player]->attackon == 1) && (player[g_Player]->Aposestate != 200) && (player[g_Player]->Aposestate != 201) && (player[g_Player]->Aposestate != 202) && (player[g_Player]->Aposestate != 203) && (player[g_Player]->Aposestate != 204) && (player[g_Player]->Aposestate != 208))
		{
		if(player[g_Player]->PowerFlightDUSTCNT < 100) player[g_Player]->PowerFlightDUSTCNT += 20 * _->TimeScale;
		else player[g_Player]->PowerFlightDUSTCNT = 100;
		}

	//########  - Dust Cloud Control -  ########

	if(player[g_Player]->PowerFlightDUSTCNT > 0)
		{
		player[g_Player]->PowerFlightDUSTCNT -= 10;

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 0)
			{
			player[g_Player]->PowerFlightPOWERF = (((1 - (player[g_Player]->JINK3_PowerFactor/50)) * 1000) + 1);
			}

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 1)
			{
			player[g_Player]->PowerFlightPOWERF = (((1 - (player[g_Player]->JINK3_WeaponFactor/50)) * 1000) + 1);
			}

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
			{
			player[g_Player]->PowerFlightPOWERF = (((1 - (player[g_Player]->JINK3_PowerFactor/50)) * 1000) + 1);
			}

		if(player[g_Player]->PowerFlightPOWERF < 0) player[g_Player]->PowerFlightPOWERF *= -1;
		if(player[g_Player]->PowerFlightPOWERF == 0) player[g_Player]->PowerFlightPOWERF = 1;

		//##### Extend Vec Down to Ground
		Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&player[g_Player]->Up);
		
		playerAV[g_Player]->OldPos = playerAV[g_Player]->Xform.Translation;
		playerAV[g_Player]->NewPos = playerAV[g_Player]->Xform.Translation;
		playerAV[g_Player]->OldPos.y += 20 + (50*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
		playerAV[g_Player]->NewPos.y += 20 + (50*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));

		Qpo->Vec3d_AddScaled(&playerAV[g_Player]->NewPos, ((player[g_Player]->JINK3_PowerFactor * -7) + 100), &player[g_Player]->Up, &playerAV[g_Player]->NewPos);

		if(Qpo->Collision_RayTest(NULL, NULL, &playerAV[g_Player]->OldPos, &playerAV[g_Player]->NewPos, /*GE_CONTENTS_SOLID_CLIP, GE_COLLIDE_MODELS,*/ 0xffffffff, NULL, NULL, &playerAV[g_Player]->Collision))
			{
			QpoVec3d f_ImpactVector(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
			player[g_Player]->PowerFlightRADIUS = ((player[g_Player]->JINK3_PowerFactor * 7) + 100) - Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->OldPos, &f_ImpactVector);

			helly=0;
			while(helly < (((player[g_Player]->PowerFlightDUSTCNT / player[g_Player]->PowerFlightPOWERF) * 100) * _->TimeScale))
				{
				//#### Locate The Cloud
				player[g_Player]->JB_PlaceVec.x = (((float)rand() / 32767)-0.5)*2;
				player[g_Player]->JB_PlaceVec.z = (((float)rand() / 32767)-0.5)*2;
				player[g_Player]->JB_PlaceVec.y = 0;
				Qpo->Vec3d_Normalize(&player[g_Player]->JB_PlaceVec);

				player[g_Player]->JB_Origin.acSet(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
				Q_Cloud->Cloud[_->NomCloud].CloudPos.acSet(playerAV[g_Player]->Collision.Impact.m_X, playerAV[g_Player]->Collision.Impact.m_Y, playerAV[g_Player]->Collision.Impact.m_Z);
				Q_Cloud->Cloud[_->NomCloud].CloudPos.y += 5;
				//Qpo->Vec3d_AddScaled(&Q_Cloud->Cloud[_->NomCloud].CloudPos, player[g_Player]->PowerFlightRADIUS, &player[g_Player]->JB_PlaceVec, &Q_Cloud->Cloud[_->NomCloud].CloudPos);

				//##### Find Trajectory
				//Qpo->Vec3d_Subtract(&Q_Cloud->Cloud[_->NomCloud].CloudPos, &player[g_Player]->JB_Origin, &Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

				//##### Register the Cloud
				Q_Cloud->Cloud[_->NomCloud].CloudType = 7;
				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+170;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.75;	//0.23
				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + (player[g_Player]->JINK3_PowerFactor * 0.01);
				Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;
				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);

				helly++;
				}
			}
		}
}


void Q_COREFunctions::CONTROL_PlayerGraphicsControl(void)
{
	//########  - Avatar Graphics Control -  ########//
	if(_->CharSelect == 1)
		{
		if(player[g_Player]->BackPBmpCnt < 38) player[g_Player]->BackPBmpCnt = 38;

		//### Player Scrolling Bitmaps
		if(player[g_Player]->BackPBmpCnt < 46)
			{
			Qpo->Avatar_GetTex(&playerAV[g_Player]->Avatar, player[g_Player]->BackPBmpCnt, player[g_Player]->BackPBitmap, &player[g_Player]->BackPRed, &player[g_Player]->BackPGreen, &player[g_Player]->BackPBlue);
			Qpo->Avatar_SetTex(&playerAV[g_Player]->Avatar, 27, player[g_Player]->BackPBitmap, &player[g_Player]->BackPRed, &player[g_Player]->BackPGreen, &player[g_Player]->BackPBlue);
			}
								//  \/----- Orig 46
		if(player[g_Player]->BackPBmpCnt + 1 < 80) player[g_Player]->BackPBmpCnt++;
		else player[g_Player]->BackPBmpCnt = 38;
		}

	//########  - 3D Star BackPack Item -  ########//

	if(player[g_Player]->Backpack.Draw == 1)
		{
		Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 SPINE3", &player[g_Player]->Backpack.PosMatrix);		//"BIP01 PELVIS"
		Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&player[g_Player]->Backpack.Leftvec);
		Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->Backpack.Upvec);

		Qpo->Vec3d_AddScaled(&player[g_Player]->Backpack.PosMatrix.Translation, -3, &player[g_Player]->Backpack.Upvec, &player[g_Player]->Backpack.PosMatrix.Translation);

		player[g_Player]->Backpack.Vert1 = player[g_Player]->Backpack.PosMatrix.Translation;


		Qpo->Vec3d_AddScaled(&player[g_Player]->Backpack.Vert1, -5, &player[g_Player]->Backpack.Upvec, &player[g_Player]->Backpack.Vert1);
		Qpo->Vec3d_AddScaled(&player[g_Player]->Backpack.Vert1, 200, &player[g_Player]->Backpack.Leftvec, &player[g_Player]->Backpack.Vert1);
		Qpo->Vec3d_AddScaled(&player[g_Player]->Backpack.Vert1, -400, &player[g_Player]->Backpack.Leftvec, &player[g_Player]->Backpack.Vert2);
		Qpo->Vec3d_AddScaled(&player[g_Player]->Backpack.Vert2, 6, &player[g_Player]->Backpack.Upvec, &player[g_Player]->Backpack.Vert3);
		Qpo->Vec3d_AddScaled(&player[g_Player]->Backpack.Vert1, 6, &player[g_Player]->Backpack.Upvec, &player[g_Player]->Backpack.Vert4);

		player[g_Player]->Backpack.Lvert[0][0].a = 255;
		player[g_Player]->Backpack.Lvert[0][0].b = 255;
		player[g_Player]->Backpack.Lvert[0][0].g = 255;
		player[g_Player]->Backpack.Lvert[0][0].r = 255;
		player[g_Player]->Backpack.Lvert[0][0].u = 0;
		player[g_Player]->Backpack.Lvert[0][0].v = 0;
		player[g_Player]->Backpack.Lvert[0][0].x = player[g_Player]->Backpack.Vert1.x;
		player[g_Player]->Backpack.Lvert[0][0].y = player[g_Player]->Backpack.Vert1.y;
		player[g_Player]->Backpack.Lvert[0][0].z = player[g_Player]->Backpack.Vert1.z;
		player[g_Player]->Backpack.Lvert[0][1].a = 255;
		player[g_Player]->Backpack.Lvert[0][1].b = 255;
		player[g_Player]->Backpack.Lvert[0][1].g = 255;
		player[g_Player]->Backpack.Lvert[0][1].r = 255;
		player[g_Player]->Backpack.Lvert[0][1].u = 1;
		player[g_Player]->Backpack.Lvert[0][1].v = 0;
		player[g_Player]->Backpack.Lvert[0][1].x = player[g_Player]->Backpack.Vert2.x;
		player[g_Player]->Backpack.Lvert[0][1].y = player[g_Player]->Backpack.Vert2.y;
		player[g_Player]->Backpack.Lvert[0][1].z = player[g_Player]->Backpack.Vert2.z;
		player[g_Player]->Backpack.Lvert[0][2].a = 255;
		player[g_Player]->Backpack.Lvert[0][2].b = 255;
		player[g_Player]->Backpack.Lvert[0][2].g = 255;
		player[g_Player]->Backpack.Lvert[0][2].r = 255;
		player[g_Player]->Backpack.Lvert[0][2].u = 1;
		player[g_Player]->Backpack.Lvert[0][2].v = 1;
		player[g_Player]->Backpack.Lvert[0][2].x = player[g_Player]->Backpack.Vert3.x;
		player[g_Player]->Backpack.Lvert[0][2].y = player[g_Player]->Backpack.Vert3.y;
		player[g_Player]->Backpack.Lvert[0][2].z = player[g_Player]->Backpack.Vert3.z;
		player[g_Player]->Backpack.Lvert[0][3].a = 255;
		player[g_Player]->Backpack.Lvert[0][3].b = 255;
		player[g_Player]->Backpack.Lvert[0][3].g = 255;
		player[g_Player]->Backpack.Lvert[0][3].r = 255;
		player[g_Player]->Backpack.Lvert[0][3].u = 0;
		player[g_Player]->Backpack.Lvert[0][3].v = 1;
		player[g_Player]->Backpack.Lvert[0][3].x = player[g_Player]->Backpack.Vert4.x;
		player[g_Player]->Backpack.Lvert[0][3].y = player[g_Player]->Backpack.Vert4.y;
		player[g_Player]->Backpack.Lvert[0][3].z = player[g_Player]->Backpack.Vert4.z;

		Qpo->Poly_AddOnce(&player[g_Player]->Backpack.Lvert[0][0], 4, Medias->special4[player[g_Player]->Backpack.Matcount], QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, 1.0f);
		player[g_Player]->Backpack.Lvert[0][0].x = player[g_Player]->Backpack.PosMatrix.Translation.x;
		player[g_Player]->Backpack.Lvert[0][0].y = player[g_Player]->Backpack.PosMatrix.Translation.y;
		player[g_Player]->Backpack.Lvert[0][0].z = player[g_Player]->Backpack.PosMatrix.Translation.z;
		Qpo->Poly_AddOnce(&player[g_Player]->Backpack.Lvert[0][0], 1, Medias->special4[player[g_Player]->Backpack.Matcount], QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.1f);

		if(player[g_Player]->Backpack.MatcountDir == 0)
			{
			if(player[g_Player]->Backpack.Matcount + 2 < 12)
				{
				player[g_Player]->Backpack.Matcount += 2;
				}
			else
				{
				player[g_Player]->Backpack.MatcountDir = 1;
				}
			}
		else
			{
			if(player[g_Player]->Backpack.Matcount - 2 > 0)
				{
				player[g_Player]->Backpack.Matcount -= 2;
				}
			else
				{
				player[g_Player]->Backpack.MatcountDir = 0;
				player[g_Player]->Backpack.Draw = 0;
				}
			}
		}
}

};