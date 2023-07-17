/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Cleric Plasma-

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
#include "Q-ENE-EnergyTypes.h"

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::ClericPlasma_ServerFrame(int Count)
	{
	switch(Q_ClericPlasma->ClericPlasma[Count].PartType)
		{
		case 0:
			{
			Q_ClericPlasma->ClericPlasma[Count].TIMER += _->TimeScale;

			Q_ClericPlasma->ClericPlasma[Count].CNTR += 1;
			Q_ClericPlasma->ClericPlasma[Count].RoTAMT = 0;

			if(Q_ClericPlasma->ClericPlasma[Count].CNTR > 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CNTR = -8;

				jet=0;
				while((jet < 15) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.019f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 55;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

					Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.393;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			if(Q_ClericPlasma->ClericPlasma[Count].AvID == 250)
				{
				if(Q_ClericPlasma->ClericPlasma[Count].Speed + ((15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Speed / 5000))) / 10) * _->TimeScale < (15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Speed / 5000)))) Q_ClericPlasma->ClericPlasma[Count].Speed += ((15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Speed / 5000))) / 10) * _->TimeScale;
				else Q_ClericPlasma->ClericPlasma[Count].Speed = (15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Speed / 5000)));
				}
			else
				{
				if(Q_ClericPlasma->ClericPlasma[Count].Speed + ((15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[2].Speed / 5000))) / 10) * _->TimeScale < (15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[2].Speed / 5000)))) Q_ClericPlasma->ClericPlasma[Count].Speed += ((15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[2].Speed / 5000))) / 10) * _->TimeScale;
				else Q_ClericPlasma->ClericPlasma[Count].Speed = (15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[2].Speed / 5000)));
				}

			Q_ClericPlasma->ClericPlasma[Count].OldPos = Q_ClericPlasma->ClericPlasma[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_ClericPlasma->ClericPlasma[Count].Pos, Q_ClericPlasma->ClericPlasma[Count].Speed*_->TimeScale, &Q_ClericPlasma->ClericPlasma[Count].TraVec, &Q_ClericPlasma->ClericPlasma[Count].Pos);

			Q.ShowLine(&Q_ClericPlasma->ClericPlasma[Count].Pos, &Q_ClericPlasma->ClericPlasma[Count].OldPos, &player[g_Player]->ViewXForm.Translation, 0.2 * 70, Medias->QAEFF03, Q_ClericPlasma->ClericPlasma[Count].Alpha, 255, 255, 255, 0);

			//##### Render Main Sprite

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->QAEFF01, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.155f);

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha/2.2;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->SparkCorona[Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.15);

			//### Increment Corona Material
			if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR == 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt++;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt > 3)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 3;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 1;
					}
				}
			else
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt--;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt < 0)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 0;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 0;
					}
				}

			if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
				{
				Q_ClericPlasma->ClericPlasma[Count].LightColor.red = 255.0f;
				Q_ClericPlasma->ClericPlasma[Count].LightColor.green = 35.0f;
				Q_ClericPlasma->ClericPlasma[Count].LightColor.blue = 255.0f;
				Q_ClericPlasma->ClericPlasma[Count].LightColor.alpha = 155.0f;

				Qpo->Light_SetAttr(Q_ClericPlasma->ClericPlasma[Count].Light, &Q_ClericPlasma->ClericPlasma[Count].Pos, &Q_ClericPlasma->ClericPlasma[Count].LightColor, 200, true);
				}

			if(Qpo->Collision_RayTest(
				 NULL,
				 NULL,
				 &Q_ClericPlasma->ClericPlasma[Count].OldPos,
				 &Q_ClericPlasma->ClericPlasma[Count].Pos,
				 // GE_CONTENTS_CANNOT_OCCUPY
				 /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
				 0xffffffff, NULL, NULL,
				 &Q_ClericPlasma->ClericPlasma[Count].Collision))
				{
				if(Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar != 0)
					{
					if(Q_ClericPlasma->ClericPlasma[Count].AvID == 250)
						{
						if(Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag == 250)
							{
							Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
							Q_ClericPlasma->ClericPlasma[Count].Live = 0;

							if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
								{
								Q_ClericPlasma->ClericPlasma[Count].LightON = 0;
								Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[Count].Light);
								}

							//### Array Reorder
							int K = Count;
							while(K < _->NomPlasma - 1)
								{
								Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
								K++;
								}

							_->NomPlasma--;

							jet=0;
							while((jet < 50) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
								{
								Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
								Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
								Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.095f;		//0.025f//0.002f
								Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

								Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

								Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 150;
								Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 1;
								Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

								Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

									//Calculate Direction Vectors
								Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
								Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								
								Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

								Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.1179;

								Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
								Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

								Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

								Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

								_->NomPntSprite++;
								jet++;
								}

							//##### Energy Gain
							player[g_Player]->HB_Energy += 25 + (550 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Potency / 5000));
							if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
							}
						else
							{
							Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
							Q_ClericPlasma->ClericPlasma[Count].Live = 0;

							if(Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag >= 0 && Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag < _->NomAI)
								{ Q_ClericPlasma->ClericPlasma[Count].HealTarget = Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag; }

							if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
								{
								Q_ClericPlasma->ClericPlasma[Count].LightON = 0;
								Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[Count].Light);
								}

							//### Array Reorder
							int K = Count;
							while(K < _->NomPlasma - 1)
								{
								Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
								K++;
								}

							_->NomPlasma--;

							jet=0;
							while((jet < 50) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
								{
								Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
								Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
								Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.095f;		//0.025f//0.002f
								Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

								Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

								Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 150;
								Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 1;
								Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

								Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

									//Calculate Direction Vectors
								Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
								Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								
								Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

								Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.1179;

								Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
								Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

								Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

								Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

								_->NomPntSprite++;
								jet++;
								}

							//##### Energy Gain
							Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_Energy += 25 + (550 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[2].Potency / 5000));
							if(Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_Energy > Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_MaxEnergy) Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_Energy = Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_MaxEnergy;
							}
						}
					else
						{
						if(Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag == 250)
							{
							Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
							Q_ClericPlasma->ClericPlasma[Count].Live = 0;

							if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
								{
								Q_ClericPlasma->ClericPlasma[Count].LightON = 0;
								Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[Count].Light);
								}

							//### Array Reorder
							int K = Count;
							while(K < _->NomPlasma - 1)
								{
								Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
								K++;
								}

							_->NomPlasma--;

							jet=0;
							while((jet < 50) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
								{
								Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
								Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
								Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.095f;		//0.025f//0.002f
								Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

								Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

								Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 150;
								Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 1;
								Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

								Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

									//Calculate Direction Vectors
								Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
								Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								
								Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

								Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.1179;

								Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
								Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

								Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

								Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

								_->NomPntSprite++;
								jet++;
								}

							//##### Energy Gain
							player[g_Player]->HB_Energy += 25 + (550 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[2].Potency / 5000));
							if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
							}
						else
							{
							Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
							Q_ClericPlasma->ClericPlasma[Count].Live = 0;

							if(Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag >= 0 && Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag < _->NomAI)
								{ Q_ClericPlasma->ClericPlasma[Count].HealTarget = Q_ClericPlasma->ClericPlasma[Count].Collision.Avatar.IDflag; }

							if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
								{
								Q_ClericPlasma->ClericPlasma[Count].LightON = 0;
								Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[Count].Light);
								}

							//### Array Reorder
							int K = Count;
							while(K < _->NomPlasma - 1)
								{
								Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
								K++;
								}

							_->NomPlasma--;

							jet=0;
							while((jet < 50) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
								{
								Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
								Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
								Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.095f;		//0.025f//0.002f
								Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

								Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
								Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

								Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 150;
								Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 1;
								Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
								Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

								Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

									//Calculate Direction Vectors
								Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
								Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
								
								Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

								Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.1179;

								Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
								Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
								Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

								Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

								Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

								_->NomPntSprite++;
								jet++;
								}

							//##### Energy Gain
							Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_Energy += 25 + (550 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[2].Potency / 5000));
							if(Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_Energy > Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_MaxEnergy) Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_Energy = Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].HealTarget].HB_MaxEnergy;
							}
						}
					}
				else	//Spark Impacts With Geometry
					{
					if(Q_ClericPlasma->ClericPlasma[Count].TIMER > 500)
						{
						Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
						Q_ClericPlasma->ClericPlasma[Count].Live = 0;

						if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
							{
							Q_ClericPlasma->ClericPlasma[Count].LightON = 0;
							Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[Count].Light);
							}

						//### Array Reorder
						int K = Count;
						while(K < _->NomPlasma - 1)
							{
							Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
							K++;
							}

						_->NomPlasma--;
						}
					else Q_ClericPlasma->ClericPlasma[Count].TraVec = Q.PHY_BounceVector(Q_ClericPlasma->ClericPlasma[Count].TraVec, Q_ClericPlasma->ClericPlasma[Count].Collision.Plane.Normal);
					}
				}
			}break;

		case 1:	//OFFENSIVE PLASMA
			{
			Q_ClericPlasma->ClericPlasma[Count].TIMER += _->TimeScale;

			Q_ClericPlasma->ClericPlasma[Count].CNTR += 1;
			Q_ClericPlasma->ClericPlasma[Count].RoTAMT = 0;

			if(Q_ClericPlasma->ClericPlasma[Count].CNTR > 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CNTR = -8;

				jet=0;
				while((jet < 15) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.019f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 55;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

					Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.393;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			if(Q_ClericPlasma->ClericPlasma[Count].AvID == 250)
				{
				if(Q_ClericPlasma->ClericPlasma[Count].Speed + ((15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[3].Speed / 5000))) / 10) * _->TimeScale < (15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[3].Speed / 5000)))) Q_ClericPlasma->ClericPlasma[Count].Speed += ((15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[3].Speed / 5000))) / 10) * _->TimeScale;
				else Q_ClericPlasma->ClericPlasma[Count].Speed = (15 + (250 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[3].Speed / 5000)));
				}
			else
				{
				if(Q_ClericPlasma->ClericPlasma[Count].Speed + ((15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[3].Speed / 5000))) / 10) * _->TimeScale < (15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[3].Speed / 5000)))) Q_ClericPlasma->ClericPlasma[Count].Speed += ((15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[3].Speed / 5000))) / 10) * _->TimeScale;
				else Q_ClericPlasma->ClericPlasma[Count].Speed = (15 + (250 * (Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].CharDATA.CLSClericSKILL[3].Speed / 5000)));
				}

			Q_ClericPlasma->ClericPlasma[Count].OldPos = Q_ClericPlasma->ClericPlasma[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_ClericPlasma->ClericPlasma[Count].Pos, Q_ClericPlasma->ClericPlasma[Count].Speed*_->TimeScale, &Q_ClericPlasma->ClericPlasma[Count].TraVec, &Q_ClericPlasma->ClericPlasma[Count].Pos);

			Q.ShowLine(&Q_ClericPlasma->ClericPlasma[Count].Pos, &Q_ClericPlasma->ClericPlasma[Count].OldPos, &player[g_Player]->ViewXForm.Translation, 0.2 * 70, Medias->QAEFF31, Q_ClericPlasma->ClericPlasma[Count].Alpha, 255, 255, 255, 0);

			//##### Render Main Sprite

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->QAEFF30, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.155f);

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha/2.2;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->EGrabCorona[Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt], QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.15);

			//### Increment Corona Material
			if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR == 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt++;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt > 3)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 3;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 1;
					}
				}
			else
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt--;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt < 0)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 0;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 0;
					}
				}


			//###### Heal Energy Cancellation
			SCRAM=0;
			while(SCRAM < _->NomHSpark)
				{
				if(Q_HealSpark->HealSpark[SCRAM].Live == 1)
					{


					if(Q_ClericPlasma->ClericPlasma[Count].AvID == 250)
						{
						if(Q_HealSpark->HealSpark[SCRAM].AvID != 250 || 1)
							{
							if(((Q_Forge->Forge[Q_HealSpark->HealSpark[SCRAM].AvID].Team != player[g_Player]->Team) || 1) && (Qpo->Vec3d_DistanceBetween(&Q_HealSpark->HealSpark[SCRAM].Pos, &Q_ClericPlasma->ClericPlasma[Count].Pos) < 50))
								{
								//### Kill Spark
								Q_HealSpark->HealSpark[SCRAM].Absorbed = 4;

								jet=0;
								while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[_->NomPlasma].Pos;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}

								jet=0;
								while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[SCRAM].Pos;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}
								}
							}
						}
					else
						{
						if(Q_HealSpark->HealSpark[SCRAM].AvID == 250 || 1)
							{
							if(((Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].Team != player[g_Player]->Team) || 1) && (Qpo->Vec3d_DistanceBetween(&Q_HealSpark->HealSpark[SCRAM].Pos, &Q_ClericPlasma->ClericPlasma[Count].Pos) < 50))
								{
								//### Kill Spark
								Q_HealSpark->HealSpark[SCRAM].Absorbed = 4;

								jet=0;
								while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[_->NomPlasma].Pos;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}

								jet=0;
								while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[SCRAM].Pos;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}
								}
							}
						else
							{
							if(((Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].Team != Q_Forge->Forge[Q_HealSpark->HealSpark[SCRAM].AvID].Team) || 1) && (Qpo->Vec3d_DistanceBetween(&Q_HealSpark->HealSpark[SCRAM].Pos, &Q_ClericPlasma->ClericPlasma[Count].Pos) < 50))
								{
								//### Kill Spark
								Q_HealSpark->HealSpark[SCRAM].Absorbed = 4;

								jet=0;
								while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[_->NomPlasma].Pos;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}

								jet=0;
								while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[SCRAM].Pos;

									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

									Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}
								}
							}
						}
					}

				SCRAM++;
				}


			//###### Plasma Energy Cancellation
			SCRAM=0;
			while(SCRAM < _->NomPlasma)
				{
				if(Q_ClericPlasma->ClericPlasma[SCRAM].Live == 1)
					{
					if(Q_ClericPlasma->ClericPlasma[Count].AvID == 250)
						{
						if(Q_ClericPlasma->ClericPlasma[SCRAM].AvID != 250)
							{
							if((Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[SCRAM].AvID].Team != player[g_Player]->Team) && (Qpo->Vec3d_DistanceBetween(&Q_ClericPlasma->ClericPlasma[SCRAM].Pos, &Q_ClericPlasma->ClericPlasma[Count].Pos) < 50))
								{
								if(Q_ClericPlasma->ClericPlasma[Count].Live == 1)
									{
									//### Stop Plasma
									Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
									Q_ClericPlasma->ClericPlasma[Count].Live = 0;

									//### Array Reorder
									int K = Count;
									while(K < _->NomPlasma - 1)
										{
										Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
										K++;
										}

									_->NomPlasma--;

									jet=0;
									while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[_->NomPlasma].Pos;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}
									}

								if(Q_ClericPlasma->ClericPlasma[SCRAM].Live == 1)
									{
									//### Stop Plasma
									Q_ClericPlasma->ClericPlasma[SCRAM].Alpha = 0;
									Q_ClericPlasma->ClericPlasma[SCRAM].Live = 0;

									if(Q_ClericPlasma->ClericPlasma[SCRAM].Light != NULL) Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[SCRAM].Light);
									Q_ClericPlasma->ClericPlasma[SCRAM].LightON = 0;

									//### Array Reorder
									int K = SCRAM;
									while(K < _->NomPlasma - 1)
										{
										Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
										K++;
										}

									_->NomPlasma--;

									jet=0;
									while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 80;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 180;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[SCRAM].Pos;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}
									}
								}
							}
						}
					else
						{
						if(Q_ClericPlasma->ClericPlasma[SCRAM].AvID == 250)
							{
							if((Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].Team != player[g_Player]->Team) && (Qpo->Vec3d_DistanceBetween(&Q_ClericPlasma->ClericPlasma[SCRAM].Pos, &Q_ClericPlasma->ClericPlasma[Count].Pos) < 50))
								{
								if(Q_ClericPlasma->ClericPlasma[Count].Live == 1)
									{
									//### Stop Plasma
									Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
									Q_ClericPlasma->ClericPlasma[Count].Live = 0;

									if(Q_ClericPlasma->ClericPlasma[SCRAM].Light != NULL) Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[SCRAM].Light);
									Q_ClericPlasma->ClericPlasma[SCRAM].LightON = 0;

									//### Array Reorder
									int K = Count;
									while(K < _->NomPlasma - 1)
										{
										Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
										K++;
										}

									_->NomPlasma--;

									jet=0;
									while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[_->NomPlasma].Pos;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}
									}

								if(Q_ClericPlasma->ClericPlasma[SCRAM].Live == 1)
									{
									//### Stop Plasma
									Q_ClericPlasma->ClericPlasma[SCRAM].Alpha = 0;
									Q_ClericPlasma->ClericPlasma[SCRAM].Live = 0;

									//### Array Reorder
									int K = SCRAM;
									while(K < _->NomPlasma - 1)
										{
										Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
										K++;
										}

									_->NomPlasma--;

									jet=0;
									while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 80;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 180;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[SCRAM].Pos;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}
									}
								}
							}
						else
							{
							if((Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[Count].AvID].Team != Q_Forge->Forge[Q_ClericPlasma->ClericPlasma[SCRAM].AvID].Team) && (Qpo->Vec3d_DistanceBetween(&Q_ClericPlasma->ClericPlasma[SCRAM].Pos, &Q_ClericPlasma->ClericPlasma[Count].Pos) < 50))
								{
								if(Q_ClericPlasma->ClericPlasma[Count].Live == 1)
									{
									//### Stop Plasma
									Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
									Q_ClericPlasma->ClericPlasma[Count].Live = 0;

									if(Q_ClericPlasma->ClericPlasma[SCRAM].Light != NULL) Qpo->Light_Remove(Q_ClericPlasma->ClericPlasma[SCRAM].Light);
									Q_ClericPlasma->ClericPlasma[SCRAM].LightON = 0;

									//### Array Reorder
									int K = Count;
									while(K < _->NomPlasma - 1)
										{
										Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
										K++;
										}

									_->NomPlasma--;

									jet=0;
									while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[_->NomPlasma].Pos;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}
									}

								if(Q_ClericPlasma->ClericPlasma[SCRAM].Live == 1)
									{
									//### Stop Plasma
									Q_ClericPlasma->ClericPlasma[SCRAM].Alpha = 0;
									Q_ClericPlasma->ClericPlasma[SCRAM].Live = 0;

									//### Array Reorder
									int K = SCRAM;
									while(K < _->NomPlasma - 1)
										{
										Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
										K++;
										}

									_->NomPlasma--;

									jet=0;
									while(jet < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
										{
										Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
										Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
										Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.065f;
										Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 58;

										Q_PntSprite->PntSprite[_->NomPntSprite].IR = 80;
										Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
										Q_PntSprite->PntSprite[_->NomPntSprite].IB = 180;

										Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
										Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[SCRAM].Pos;

										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
										Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
										Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

										Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[_->NomPlasma].AvID;

										Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

										_->NomPntSprite++;
										jet++;
										}
									}
								}
							}
						}
					}

				SCRAM++;
				}


			if(Qpo->Collision_RayTest(
				 NULL,
				 NULL,
				 &Q_ClericPlasma->ClericPlasma[Count].OldPos,
				 &Q_ClericPlasma->ClericPlasma[Count].Pos,
				 // GE_CONTENTS_CANNOT_OCCUPY
				 //GE_COLLIDE_MODELS,
				 0xffffffff, NULL, NULL,
				 &Q_ClericPlasma->ClericPlasma[Count].Collision))
				{
				if(Q_ClericPlasma->ClericPlasma[Count].TIMER > 500)
					{
					Q_ClericPlasma->ClericPlasma[Count].Alpha = 0;
					Q_ClericPlasma->ClericPlasma[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPlasma - 1)
						{
						Q_ClericPlasma->ClericPlasma[K] = Q_ClericPlasma->ClericPlasma[K+1];
						K++;
						}

					_->NomPlasma--;
					}
				else Q_ClericPlasma->ClericPlasma[Count].TraVec = Q.PHY_BounceVector(Q_ClericPlasma->ClericPlasma[Count].TraVec, Q_ClericPlasma->ClericPlasma[Count].Collision.Plane.Normal);
				}
			}break;

		}//End Switch
	}


void Q_EFFCon::ClericPlasma_ClientFrame(int Count)
	{
	switch(Q_ClericPlasma->ClericPlasma[Count].PartType)
		{
		case 0:
			{
			if(Q_ClericPlasma->ClericPlasma[Count].LightON == 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
				Q_ClericPlasma->ClericPlasma[Count].LightON = 1;
				}

			Q_ClericPlasma->ClericPlasma[Count].CNTR += 1;
			Q_ClericPlasma->ClericPlasma[Count].RoTAMT = 0;

			if(Q_ClericPlasma->ClericPlasma[Count].CNTR > 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CNTR = -8;

				jet=0;
				while((jet < 15) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.019f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 55;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

					Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.393;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_ClericPlasma->ClericPlasma[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			Q_ClericPlasma->ClericPlasma[Count].OldPos = Q_ClericPlasma->ClericPlasma[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_ClericPlasma->ClericPlasma[Count].Pos, -Q_ClericPlasma->ClericPlasma[Count].Speed*_->TimeScale, &Q_ClericPlasma->ClericPlasma[Count].TraVec, &Q_ClericPlasma->ClericPlasma[Count].Pos);

			Q.ShowLine(&Q_ClericPlasma->ClericPlasma[Count].Pos, &Q_ClericPlasma->ClericPlasma[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_ClericPlasma->ClericPlasma[Count].Scale * 70, Medias->QAEFF03, Q_ClericPlasma->ClericPlasma[Count].Alpha, 255, 255, 255, 0);

			//##### Render Main Sprite

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->QAEFF01, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.155f);

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha/2.2;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->SparkCorona[Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_ClericPlasma->ClericPlasma[Count].RenderFlags, 0.15);

			//### Increment Corona Material
			if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR == 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt++;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt > 3)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 3;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 1;
					}
				}
			else
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt--;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt < 0)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 0;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 0;
					}
				}

			if(Q_ClericPlasma->ClericPlasma[Count].LightON == 1)
				{
				Q_ClericPlasma->ClericPlasma[_->NomPlasma].LightColor.red = 255.0f;
				Q_ClericPlasma->ClericPlasma[_->NomPlasma].LightColor.green = 35.0f;
				Q_ClericPlasma->ClericPlasma[_->NomPlasma].LightColor.blue = 255.0f;
				Q_ClericPlasma->ClericPlasma[_->NomPlasma].LightColor.alpha = 155.0f;

				Qpo->Light_SetAttr(Q_ClericPlasma->ClericPlasma[Count].Light, &Q_ClericPlasma->ClericPlasma[Count].Pos, &Q_ClericPlasma->ClericPlasma[Count].LightColor, 200, true);
				}
			}break; //End Friendly Plasma

		case 1:	//OFFENSIVE PLASMA
			{
			Q_ClericPlasma->ClericPlasma[Count].TIMER += _->TimeScale;

			Q_ClericPlasma->ClericPlasma[Count].CNTR += 1;
			Q_ClericPlasma->ClericPlasma[Count].RoTAMT = 0;

			if(Q_ClericPlasma->ClericPlasma[Count].CNTR > 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CNTR = -8;

				jet=0;
				while((jet < 15) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.019f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 55;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_ClericPlasma->ClericPlasma[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_ClericPlasma->ClericPlasma[Count].TraVec;

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, Q_ClericPlasma->ClericPlasma[Count].RoTAMT);

					Q_ClericPlasma->ClericPlasma[Count].RoTAMT += 0.393;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			if(Q_ClericPlasma->ClericPlasma[Count].Speed + 15 *_->TimeScale < 160) Q_ClericPlasma->ClericPlasma[Count].Speed += 15 * _->TimeScale;
			else Q_ClericPlasma->ClericPlasma[Count].Speed = 160;

			Q_ClericPlasma->ClericPlasma[Count].OldPos = Q_ClericPlasma->ClericPlasma[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_ClericPlasma->ClericPlasma[Count].Pos, Q_ClericPlasma->ClericPlasma[Count].Speed*_->TimeScale, &Q_ClericPlasma->ClericPlasma[Count].TraVec, &Q_ClericPlasma->ClericPlasma[Count].Pos);

			Q.ShowLine(&Q_ClericPlasma->ClericPlasma[Count].Pos, &Q_ClericPlasma->ClericPlasma[Count].OldPos, &player[g_Player]->ViewXForm.Translation, 0.2 * 70, Medias->QAEFF31, Q_ClericPlasma->ClericPlasma[Count].Alpha, 255, 255, 255, 0);

			//##### Render Main Sprite

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->QAEFF30, QPOLY_TYPE_PNT, QPOLY_REND_NO_OCCLUDE, 0.155f);

			Q_ClericPlasma->ClericPlasma[Count].Lvert.x = Q_ClericPlasma->ClericPlasma[Count].Pos.x;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.y = Q_ClericPlasma->ClericPlasma[Count].Pos.y;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.z = Q_ClericPlasma->ClericPlasma[Count].Pos.z;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.r = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.g = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.b = 255;
			Q_ClericPlasma->ClericPlasma[Count].Lvert.a = Q_ClericPlasma->ClericPlasma[Count].Alpha/2.2;

			Qpo->Poly_AddOnce(&Q_ClericPlasma->ClericPlasma[Count].Lvert, 1, Medias->EGrabCorona[Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_ClericPlasma->ClericPlasma[Count].RenderFlags, 0.15);

			//### Increment Corona Material
			if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR == 0)
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt++;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt > 3)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 3;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 1;
					}
				}
			else
				{
				Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt--;
				if(Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt < 0)
					{
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCnt = 0;
					Q_ClericPlasma->ClericPlasma[Count].CoronaMatCntDIR = 0;
					}
				}

			}break;

		}
	}
};