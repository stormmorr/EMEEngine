/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Energy Systems-
	*/#include "pch.h"/*- Minor Component -Cleric Heal Sparks-

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

	//########  - 3D Heal Sparks System -  ########//

void Q_EFFCon::HSpark_ServerFrame(int Count)
	{
	switch(Q_HealSpark->HealSpark[Count].HTYPE)
		{
		case 0:	//Heal Sparks
			{
			if(Q_HealSpark->HealSpark[Count].Released == 1)
				{
				//#### Show Target Locks
				if(Q_HealSpark->HealSpark[Count].DisplayAlpha - 5 > 10) Q_HealSpark->HealSpark[Count].DisplayAlpha -= 5;
				else Q_HealSpark->HealSpark[Count].DisplayAlpha = 10;

				if(Q_HealSpark->HealSpark[Count].DisplayColor - 25 > 0) Q_HealSpark->HealSpark[Count].DisplayColor -= 25;
				else Q_HealSpark->HealSpark[Count].DisplayColor = 0;

				if(Q_HealSpark->HealSpark[Count].DisplayScale + 0.05 < 0.5) Q_HealSpark->HealSpark[Count].DisplayScale += 0.06;
				else Q_HealSpark->HealSpark[Count].DisplayScale = 0.5;

				if(Q_HealSpark->HealSpark[Count].Absorbed == 0)
					{
					if(Q_HealSpark->HealSpark[Count].ScaleSTR + 1 < 33) Q_HealSpark->HealSpark[Count].ScaleSTR += 1;
					else Q_HealSpark->HealSpark[Count].ScaleSTR = 33;
					}
				
				if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}
				else
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}

				if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{
					Q_HealSpark->HealSpark[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
					Q_HealSpark->HealSpark[Count].TargetVec.y += 65;
					}
				else
					{
					Q_HealSpark->HealSpark[Count].TargetVec = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation;
					Q_HealSpark->HealSpark[Count].TargetVec.y += 65;
					}

				Qpo->Vec3d_Subtract(&Q_HealSpark->HealSpark[Count].TargetVec, &Q_HealSpark->HealSpark[Count].Pos, &Q_HealSpark->HealSpark[Count].TargetVec);
				Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].TargetVec);

				if(Q_HealSpark->HealSpark[Count].AvID == 250)
					{
					Q_HealSpark->HealSpark[Count].TraVec.x += ( ( Q_HealSpark->HealSpark[Count].TargetVec.x - Q_HealSpark->HealSpark[Count].TraVec.x ) / (1.3 + (13 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Accuracy / 5000))))) *_->TimeScale;
					Q_HealSpark->HealSpark[Count].TraVec.y += ( ( Q_HealSpark->HealSpark[Count].TargetVec.y - Q_HealSpark->HealSpark[Count].TraVec.y ) / (1.7 + (31.2 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Accuracy / 5000))))) *_->TimeScale;
					Q_HealSpark->HealSpark[Count].TraVec.z += ( ( Q_HealSpark->HealSpark[Count].TargetVec.z - Q_HealSpark->HealSpark[Count].TraVec.z ) / (1.3 + (13 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Accuracy / 5000))))) *_->TimeScale;
					Q_HealSpark->HealSpark[Count].TraVec.y += Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale;
					}
				else
					{
					Q_HealSpark->HealSpark[Count].TraVec.x += ( ( Q_HealSpark->HealSpark[Count].TargetVec.x - Q_HealSpark->HealSpark[Count].TraVec.x ) / (1.3 + (13 * (1 - (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[1].Accuracy / 5000))))) *_->TimeScale;	//9
					Q_HealSpark->HealSpark[Count].TraVec.y += ( ( Q_HealSpark->HealSpark[Count].TargetVec.y - Q_HealSpark->HealSpark[Count].TraVec.y ) / (1.7 + (31.2 * (1 - (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[1].Accuracy / 5000))))) *_->TimeScale;	//18
					Q_HealSpark->HealSpark[Count].TraVec.z += ( ( Q_HealSpark->HealSpark[Count].TargetVec.z - Q_HealSpark->HealSpark[Count].TraVec.z ) / (1.3 + (13 * (1 - (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[1].Accuracy / 5000))))) *_->TimeScale;	//9
					Q_HealSpark->HealSpark[Count].TraVec.y += Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale;
					}

				Q_HealSpark->HealSpark[Count].OldPos = Q_HealSpark->HealSpark[Count].Pos;
				if(Q_HealSpark->HealSpark[Count].Absorbed == 0) Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Speed*_->TimeScale, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].Pos);

				//Apply Gravity
				Q_HealSpark->HealSpark[Count].DownSpeed -= Q_HealSpark->HealSpark[Count].Gravity*_->TimeScale;
				}
			else
				{
				if(Q_HealSpark->HealSpark[Count].AvID == 250)
					{
					warp = 0;
					SHADOW = 0;
					while(SHADOW < player[g_Player]->Cleric.HSparkNOM)
						{
						if(player[g_Player]->Cleric.HSparkID[SHADOW] == Count) warp++;
						SHADOW++;
						}

					if(player[g_Player]->Aposestate != 200 || warp == 0) Q_HealSpark->HealSpark[Count].Released = 1;
					}
				else
					{
					if((Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Aposestate != 200) || ((Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[0] != Count) && (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[1] != Count) && (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[2] != Count)))
						{ Q_HealSpark->HealSpark[Count].Released = 1; }

					warp = 0;
					SHADOW = 0;
					while(SHADOW < Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkNOM)
						{
						if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[SHADOW] == Count) warp++;
						SHADOW++;
						}

					if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Aposestate != 200 || warp == 0) Q_HealSpark->HealSpark[Count].Released = 1;
					}
				}

			if(Q_HealSpark->HealSpark[Count].Absorbed > 0)
				{
				if(Q_HealSpark->HealSpark[Count].Absorbed == 1)
					{
					Q_HealSpark->HealSpark[Count].Absorbed = 2;
					Q_HealSpark->HealSpark[Count].AvatarLightB = 100;
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed > 0 && Q_HealSpark->HealSpark[Count].Absorbed < 3)
					{
					Q_HealSpark->HealSpark[Count].AvatarINCB += 20;

					//### Explode the Heal Spark
					if(Q_HealSpark->HealSpark[Count].AlpFade <= 0 && Q_HealSpark->HealSpark[Count].LightON == 1)
						{
						Q_HealSpark->HealSpark[Count].AlpFade = 0;
						Q_HealSpark->HealSpark[Count].LightON = 0;
						Qpo->Light_Remove(Q_HealSpark->HealSpark[Count].Light);
						}
					else
						{
						Q_HealSpark->HealSpark[Count].ScaleSTR += 10;
						Q_HealSpark->HealSpark[Count].AlpFade -= 25;
						}

					if(Q_HealSpark->HealSpark[Count].AvID == 250)
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
							{
							player[g_Player]->HB_Health += 15 + (500 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Potency / 5000));
							if(player[g_Player]->HB_Health > player[g_Player]->HB_MaxHealth) player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
							}
						else
							{
							Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Health += 15 + (500 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[1].Potency / 5000));
							if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Health > Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_MaxHealth) Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Health = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_MaxHealth;
							}
						}
					else
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
							{
							player[g_Player]->HB_Health += 15 + (500 * (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[1].Potency / 5000));
							if(player[g_Player]->HB_Health > player[g_Player]->HB_MaxHealth) player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
							}
						else
							{
							Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Health += 15 + (500 * (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[1].Potency / 5000));
							if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Health > Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_MaxHealth) Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Health = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_MaxHealth;
							}
						}

					if(Q_HealSpark->HealSpark[Count].AvatarINCB > 255 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = 255;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 1;
						}

					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{
						Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					else
						{
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					
					if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 1)
						{
						Q_HealSpark->HealSpark[Count].Absorbed = 3;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 3)
					{
					if((Q_HealSpark->HealSpark[Count].AvatarINCB < Q_HealSpark->HealSpark[Count].AvatarLightB) && (Q_HealSpark->HealSpark[Count].LightBlueFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = Q_HealSpark->HealSpark[Count].AvatarLightB;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCB -= 20;


					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{
						Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					else
						{
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					
					if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
							{
							Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true);
							}
						else
							{
							Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true);
							}

						//Live to Zero need to reorder array here
						Q_HealSpark->HealSpark[Count].Live = 0;
						if(Q_HealSpark->HealSpark[Count].LightON == 1) Qpo->Light_Remove(Q_HealSpark->HealSpark[Count].Light);
						Q_HealSpark->HealSpark[Count].LightON = 0;

						//### Array Reorder
						int K = Count;
						while(K < _->NomHSpark - 1)
							{
							Q_HealSpark->HealSpark[K] = Q_HealSpark->HealSpark[K+1];
							K++;
							}

						_->NomHSpark--;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 4)
					{
					if(Q_HealSpark->HealSpark[Count].AlpFade <= 0 && Q_HealSpark->HealSpark[Count].LightON == 1)
						{
						Q_HealSpark->HealSpark[Count].AlpFade = 0;
						Q_HealSpark->HealSpark[Count].LightON = 0;
						Qpo->Light_Remove(Q_HealSpark->HealSpark[Count].Light);
						Q_HealSpark->HealSpark[Count].Absorbed = 5;
						}
					else
						{
						Q_HealSpark->HealSpark[Count].ScaleSTR += 10;
						Q_HealSpark->HealSpark[Count].AlpFade -= 25;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 5)
					{
					//Live to Zero need to reorder array here
					Q_HealSpark->HealSpark[Count].Live = 0;
					if(Q_HealSpark->HealSpark[Count].LightON == 1) Qpo->Light_Remove(Q_HealSpark->HealSpark[Count].Light);
					Q_HealSpark->HealSpark[Count].LightON = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomHSpark - 1)
						{
						Q_HealSpark->HealSpark[K] = Q_HealSpark->HealSpark[K+1];
						K++;
						}

					_->NomHSpark--;
					}
				}

			Q_HealSpark->HealSpark[Count].CNTR += _->TimeScale;

			if(Q_HealSpark->HealSpark[Count].CNTR > 1)
				{
				Q_HealSpark->HealSpark[Count].CNTR = 0;

				jet=0;
				while(jet < 2 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.015f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 57;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			if(Q_HealSpark->HealSpark[Count].LightON == 1) Qpo->Light_SetAttr(Q_HealSpark->HealSpark[Count].Light, &Q_HealSpark->HealSpark[Count].Pos, &Q_HealSpark->HealSpark[Count].LightColor, 100, true);
			}break;

		case 1:	//Energy Grab Sparks
			{
			if(Q_HealSpark->HealSpark[Count].Released == 1)
				{
				//#### Show Target Locks
				if(Q_HealSpark->HealSpark[Count].DisplayAlpha - 5 > 10) Q_HealSpark->HealSpark[Count].DisplayAlpha -= 5;
				else Q_HealSpark->HealSpark[Count].DisplayAlpha = 10;

				if(Q_HealSpark->HealSpark[Count].DisplayColor - 25 > 0) Q_HealSpark->HealSpark[Count].DisplayColor -= 25;
				else Q_HealSpark->HealSpark[Count].DisplayColor = 0;

				if(Q_HealSpark->HealSpark[Count].DisplayScale + 0.05 < 0.5) Q_HealSpark->HealSpark[Count].DisplayScale += 0.06;
				else Q_HealSpark->HealSpark[Count].DisplayScale = 0.9;

				if(Q_HealSpark->HealSpark[Count].Absorbed == 0)
					{
					if(Q_HealSpark->HealSpark[Count].ScaleSTR + 1 < 33) Q_HealSpark->HealSpark[Count].ScaleSTR += 1;
					else Q_HealSpark->HealSpark[Count].ScaleSTR = 33;
					}
				
				if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}
				else
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}


				if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{
					Q_HealSpark->HealSpark[Count].TargetVec = playerAV[g_Player]->Xform.Translation;
					Q_HealSpark->HealSpark[Count].TargetVec.y += 65;
					}
				else
					{
					Q_HealSpark->HealSpark[Count].TargetVec = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation;
					Q_HealSpark->HealSpark[Count].TargetVec.y += 65;
					}

				Qpo->Vec3d_Subtract(&Q_HealSpark->HealSpark[Count].TargetVec, &Q_HealSpark->HealSpark[Count].Pos, &Q_HealSpark->HealSpark[Count].TargetVec);
				Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].TargetVec);

				if(Q_HealSpark->HealSpark[Count].AvID == 250)
					{
					Q_HealSpark->HealSpark[Count].TraVec.x += ( ( Q_HealSpark->HealSpark[Count].TargetVec.x - Q_HealSpark->HealSpark[Count].TraVec.x ) / (1.3 + (13 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[0].Accuracy / 5000))))) *_->TimeScale;
					Q_HealSpark->HealSpark[Count].TraVec.y += ( ( Q_HealSpark->HealSpark[Count].TargetVec.y - Q_HealSpark->HealSpark[Count].TraVec.y ) / (1.7 + (31.2 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[0].Accuracy / 5000))))) *_->TimeScale;
					Q_HealSpark->HealSpark[Count].TraVec.z += ( ( Q_HealSpark->HealSpark[Count].TargetVec.z - Q_HealSpark->HealSpark[Count].TraVec.z ) / (1.3 + (13 * (1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[0].Accuracy / 5000))))) *_->TimeScale;
					Q_HealSpark->HealSpark[Count].TraVec.y += Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale;
					}
				else
					{
					Q_HealSpark->HealSpark[Count].TraVec.x += ( ( Q_HealSpark->HealSpark[Count].TargetVec.x - Q_HealSpark->HealSpark[Count].TraVec.x ) / (1.3 + (13 * (1 - (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Accuracy / 5000))))) *_->TimeScale;	//9
					Q_HealSpark->HealSpark[Count].TraVec.y += ( ( Q_HealSpark->HealSpark[Count].TargetVec.y - Q_HealSpark->HealSpark[Count].TraVec.y ) / (1.7 + (31.2 * (1 - (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Accuracy / 5000))))) *_->TimeScale;	//18
					Q_HealSpark->HealSpark[Count].TraVec.z += ( ( Q_HealSpark->HealSpark[Count].TargetVec.z - Q_HealSpark->HealSpark[Count].TraVec.z ) / (1.3 + (13 * (1 - (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Accuracy / 5000))))) *_->TimeScale;	//9
					Q_HealSpark->HealSpark[Count].TraVec.y += Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale;
					}

				Q_HealSpark->HealSpark[Count].OldPos = Q_HealSpark->HealSpark[Count].Pos;
				if(Q_HealSpark->HealSpark[Count].Absorbed == 0) Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Speed*_->TimeScale, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].Pos);

				//Apply Gravity
				Q_HealSpark->HealSpark[Count].DownSpeed -= Q_HealSpark->HealSpark[Count].Gravity*_->TimeScale;
				}
			else
				{
				if(Q_HealSpark->HealSpark[Count].AvID == 250)
					{
					warp = 0;
					SHADOW = 0;
					while(SHADOW < player[g_Player]->Cleric.HSparkNOM)
						{
						if(player[g_Player]->Cleric.HSparkID[SHADOW] == Count) warp++;
						SHADOW++;
						}

					if(player[g_Player]->Aposestate != 202 || warp == 0) Q_HealSpark->HealSpark[Count].Released = 1;
					}
				else
					{
					if((Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Aposestate != 200) || ((Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[0] != Count) && (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[1] != Count) && (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[2] != Count)))
						{ Q_HealSpark->HealSpark[Count].Released = 1; }

					warp = 0;
					SHADOW = 0;
					while(SHADOW < Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkNOM)
						{
						if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Cleric.HSparkID[SHADOW] == Count) warp++;
						SHADOW++;
						}

					if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].Aposestate != 202 || warp == 0) Q_HealSpark->HealSpark[Count].Released = 1;
					}
				}

			if(Q_HealSpark->HealSpark[Count].Absorbed > 0)
				{
				if(Q_HealSpark->HealSpark[Count].Absorbed == 1)
					{
					Q_HealSpark->HealSpark[Count].Absorbed = 2;
					Q_HealSpark->HealSpark[Count].AvatarLightR = 190;
					Q_HealSpark->HealSpark[Count].AvatarLightG = 145;
					Q_HealSpark->HealSpark[Count].AvatarLightB = 100;
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed > 0 && Q_HealSpark->HealSpark[Count].Absorbed < 3)
					{
					Q_HealSpark->HealSpark[Count].AvatarINCR -= 20;
					Q_HealSpark->HealSpark[Count].AvatarINCG -= 20;
					Q_HealSpark->HealSpark[Count].AvatarINCB -= 20;
					
					//### Explode the Heal Spark
					if(Q_HealSpark->HealSpark[Count].AlpFade <= 0)
						{
						Q_HealSpark->HealSpark[Count].AlpFade = 0;
						}
					else
						{
						Q_HealSpark->HealSpark[Count].ScaleSTR += 10;
						Q_HealSpark->HealSpark[Count].AlpFade -= 25;
						}

					//#### SPARK FUNCTIONALITY
					if(Q_HealSpark->HealSpark[Count].AvID == 250)
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget != 250)
							{
							player[g_Player]->HB_Energy += 15 + (350 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[0].Potency / 5000));
							if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

							Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Energy -= 15 + (350 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[0].Potency / 5000));
							if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Energy < 0) Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Energy = 0;
							}
						}
					else
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
							{
							Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_Energy += 15 + (350 * (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Potency / 5000));
							if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_Energy > Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_MaxEnergy) Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_Energy = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_MaxEnergy;

							player[g_Player]->HB_Energy -= 15 + (350 * (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Potency / 5000));
							if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;
							}
						else
							{
							Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_Energy += 15 + (350 * (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Potency / 5000));
							if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_Energy > Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_MaxEnergy) Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_Energy = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].HB_MaxEnergy;

							Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Energy -= 15 + (350 * (Q_Forge->Forge[Q_HealSpark->HealSpark[Count].AvID].CharDATA.CLSClericSKILL[0].Potency / 5000));
							if(Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Energy < 0) Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].HB_Energy = 0;
							}
						}

					if(Q_HealSpark->HealSpark[Count].AvatarINCR < 70 && Q_HealSpark->HealSpark[Count].LightRedFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCR = 70;
						Q_HealSpark->HealSpark[Count].LightRedFULL = 1;
						}
					if(Q_HealSpark->HealSpark[Count].AvatarINCG < 70 && Q_HealSpark->HealSpark[Count].LightGreenFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCG = 70;
						Q_HealSpark->HealSpark[Count].LightGreenFULL = 1;
						}
					
					if(Q_HealSpark->HealSpark[Count].AvatarINCB < 70 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = 70;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 1;
						}

					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{ Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					else { Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					
					if(Q_HealSpark->HealSpark[Count].LightRedFULL == 1 && Q_HealSpark->HealSpark[Count].LightGreenFULL == 1 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 1)
						{
						Q_HealSpark->HealSpark[Count].Absorbed = 3;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 3)
					{
					if((Q_HealSpark->HealSpark[Count].AvatarINCR > Q_HealSpark->HealSpark[Count].AvatarLightR) && (Q_HealSpark->HealSpark[Count].LightRedFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCR = Q_HealSpark->HealSpark[Count].AvatarLightR;
						Q_HealSpark->HealSpark[Count].LightRedFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightRedFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCR += 20;

					if((Q_HealSpark->HealSpark[Count].AvatarINCG > Q_HealSpark->HealSpark[Count].AvatarLightG) && (Q_HealSpark->HealSpark[Count].LightGreenFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCG = Q_HealSpark->HealSpark[Count].AvatarLightG;
						Q_HealSpark->HealSpark[Count].LightGreenFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightGreenFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCG += 20;

					if((Q_HealSpark->HealSpark[Count].AvatarINCB > Q_HealSpark->HealSpark[Count].AvatarLightB) && (Q_HealSpark->HealSpark[Count].LightBlueFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = Q_HealSpark->HealSpark[Count].AvatarLightB;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCB += 20;


					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{ Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					else { Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					
					if(Q_HealSpark->HealSpark[Count].LightRedFULL == 0 && Q_HealSpark->HealSpark[Count].LightGreenFULL == 0 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
							{ Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarLightR,Q_HealSpark->HealSpark[Count].AvatarLightG,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true); }
						else { Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarLightR,Q_HealSpark->HealSpark[Count].AvatarLightG,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true); }

						//Live to Zero need to reorder array here
						Q_HealSpark->HealSpark[Count].Live = 0;
						
						//### Array Reorder
						int K = Count;
						while(K < _->NomHSpark - 1)
							{
							Q_HealSpark->HealSpark[K] = Q_HealSpark->HealSpark[K+1];
							K++;
							}

						_->NomHSpark--;
						}
					}


				if(Q_HealSpark->HealSpark[Count].Absorbed == 4)
					{
					if(Q_HealSpark->HealSpark[Count].AlpFade <= 0)
						{
						Q_HealSpark->HealSpark[Count].AlpFade = 0;
						Q_HealSpark->HealSpark[Count].Absorbed = 5;
						}
					else
						{
						Q_HealSpark->HealSpark[Count].ScaleSTR += 10;
						Q_HealSpark->HealSpark[Count].AlpFade -= 25;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 5)
					{
					//Live to Zero need to reorder array here
					Q_HealSpark->HealSpark[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomHSpark - 1)
						{
						Q_HealSpark->HealSpark[K] = Q_HealSpark->HealSpark[K+1];
						K++;
						}

					_->NomHSpark--;
					}
				}

			Q_HealSpark->HealSpark[Count].CNTR += _->TimeScale;

			if(Q_HealSpark->HealSpark[Count].CNTR > 1)
				{
				Q_HealSpark->HealSpark[Count].CNTR = 0;

				jet=0;
				while(jet < 2 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.015f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 57;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			}break;
		}


	if(Qpo->Collision_RayTest(
		 NULL,
		 NULL,
		 &Q_HealSpark->HealSpark[Count].OldPos,
		 &Q_HealSpark->HealSpark[Count].Pos,
		 // GE_CONTENTS_CANNOT_OCCUPY
		 /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */
		 0xffffffff, NULL, NULL,
		 &Q_HealSpark->HealSpark[Count].Collision) && Q_HealSpark->HealSpark[Count].Absorbed == 0)
		{
		Q_HealSpark->HealSpark[Count].Pos = Q_HealSpark->HealSpark[Count].OldPos;

		if((Q_HealSpark->HealSpark[Count].Collision.m_HitAvatar != false) && (Q_HealSpark->HealSpark[Count].Collision.m_AvatarID == Q_HealSpark->HealSpark[Count].HealTarget))
			{
			Q_HealSpark->HealSpark[Count].Absorbed = 1;
			}
		else	//Spark Impacts With Geometry
			{
			Q_HealSpark->HealSpark[Count].TraVec = Q.PHY_BounceVector(Q_HealSpark->HealSpark[Count].TraVec, Q_HealSpark->HealSpark[Count].Collision.Plane.Normal);

			Q_HealSpark->HealSpark[Count].TraVec.x += ((((float)rand() / 32767)*2)-1);
			Q_HealSpark->HealSpark[Count].TraVec.y += ((((float)rand() / 32767)*2)-1);
			Q_HealSpark->HealSpark[Count].TraVec.z += ((((float)rand() / 32767)*2)-1);

			//BETTER
			Q_HealSpark->HealSpark[Count].DownSpeed = 0;
			}
		}
	

	//### Spark Drawing Scale
	
	Q_HealSpark->HealSpark[Count].Scale = Q_HealSpark->HealSpark[Count].ScaleSTR;
	Q_HealSpark->HealSpark[Count].ScaleBIT = 0.15f;	//0.2

	//Calculate Direction Vectors
	Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
	Qpo->Transform_RotateVector(&RotateMatrix, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VecLeft);
	Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].VecLeft);
	Q_HealSpark->HealSpark[Count].VecLeft.y = 0;

	Qpo->Vec3d_CrossProduct(&Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VecUp);
	Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].VecUp);

	Q_HealSpark->HealSpark[Count].VecSTR = Q_HealSpark->HealSpark[Count].TraVec;
	Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].TraVec);

	//Front Vert
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/17, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VertF1);

	//Ball Verts
	//Standard Left Up down
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB1);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB2);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB2, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB2);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB3);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB4);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB4, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB4);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB5);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB6);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB6, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB6);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB7);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB8);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB8, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB8);

	//### Twist Tail Points round
	Q_HealSpark->HealSpark[Count].VecSTR = Q_HealSpark->HealSpark[Count].TraVec;
	Q_HealSpark->HealSpark[Count].DownSpeedSTR = Q_HealSpark->HealSpark[Count].DownSpeed;

	Q_HealSpark->HealSpark[Count].TraVec.y += (Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale);
	Q_HealSpark->HealSpark[Count].TraLength = Qpo->Vec3d_Length(&Q_HealSpark->HealSpark[Count].TraVec);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -((Q_HealSpark->HealSpark[Count].Speed*(Q_HealSpark->HealSpark[Count].TraLength*1))*_->TimeScale), &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].PosBrush);

	Q_HealSpark->HealSpark[Count].TraVec = Q_HealSpark->HealSpark[Count].VecSTR;
	Q_HealSpark->HealSpark[Count].DownSpeed = Q_HealSpark->HealSpark[Count].DownSpeedSTR;

	//Shift back for tail verts  ##WORKS BUT FROZEN
	//Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/2.6, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].PosBrush);

	//### Reduce Scale for tail verts
	Q_HealSpark->HealSpark[Count].Scale /= 3;

	//Tail Verts
	//Standard Left Up down
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT1);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT2);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT2, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT2);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT3);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT4);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT4, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT4);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT5);


	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT6);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT6, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT6);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT7);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT8);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT8, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT8);

	//Shift back for End Vert
	//Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/2, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VertE1);

	//### Twist End Point round
	Q_HealSpark->HealSpark[Count].VecSTR = Q_HealSpark->HealSpark[Count].TraVec;
	Q_HealSpark->HealSpark[Count].DownSpeedSTR = Q_HealSpark->HealSpark[Count].DownSpeed;

	Q_HealSpark->HealSpark[Count].TraVec.y += (Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale);
	Q_HealSpark->HealSpark[Count].TraLength = Qpo->Vec3d_Length(&Q_HealSpark->HealSpark[Count].TraVec);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -((Q_HealSpark->HealSpark[Count].Speed*(Q_HealSpark->HealSpark[Count].TraLength*2.4))*_->TimeScale), &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VertE1);

	Q_HealSpark->HealSpark[Count].TraVec = Q_HealSpark->HealSpark[Count].VecSTR;
	Q_HealSpark->HealSpark[Count].DownSpeed = Q_HealSpark->HealSpark[Count].DownSpeedSTR;

	if(Q_HealSpark->HealSpark[Count].Absorbed == 0)
		{
		if(Q_HealSpark->HealSpark[Count].FadeDir == 0)
			{
			Q_HealSpark->HealSpark[Count].AlpFade -= 40;//((((float)rand() / 32767)*10)+5);
			if(Q_HealSpark->HealSpark[Count].AlpFade <= 170)
				{
				Q_HealSpark->HealSpark[Count].AlpFade = 170;
				Q_HealSpark->HealSpark[Count].FadeDir = 1;
				}
			}

		if(Q_HealSpark->HealSpark[Count].FadeDir == 1)
			{
			Q_HealSpark->HealSpark[Count].AlpFade += 40;//((((float)rand() / 32767)*10)+5);
			if(Q_HealSpark->HealSpark[Count].AlpFade >= 255)
				{
				Q_HealSpark->HealSpark[Count].AlpFade = 255;
				Q_HealSpark->HealSpark[Count].FadeDir = 0;
				}
			}
		}


		int a=0;
		while( a <= 23 )
			{
			int b=0;
			while( b <= 3 )
				{
				Q_HealSpark->HealSpark[Count].Lvert[a][b].a = Q_HealSpark->HealSpark[Count].AlpFade;
				Q_HealSpark->HealSpark[Count].Lvert[a][b].b = 255;
				Q_HealSpark->HealSpark[Count].Lvert[a][b].g = 225;
				Q_HealSpark->HealSpark[Count].Lvert[a][b].r = 225;
				b++;
				}
			a++;
			}

		//Set Corona
		Q_HealSpark->HealSpark[Count].Lvert[24][0].a = Q_HealSpark->HealSpark[Count].AlpFade/2.2;
		Q_HealSpark->HealSpark[Count].Lvert[24][0].b = 255;
		Q_HealSpark->HealSpark[Count].Lvert[24][0].g = 255;
		Q_HealSpark->HealSpark[Count].Lvert[24][0].r = 255;

			//First Ring
			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[0][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[0][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].z = Q_HealSpark->HealSpark[Count].VertB1.z;

			Q_HealSpark->HealSpark[Count].Lvert[0][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].z = Q_HealSpark->HealSpark[Count].VertB2.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[1][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[1][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].z = Q_HealSpark->HealSpark[Count].VertB2.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[1][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].z = Q_HealSpark->HealSpark[Count].VertB3.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[2][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[2][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].z = Q_HealSpark->HealSpark[Count].VertB3.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[2][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].z = Q_HealSpark->HealSpark[Count].VertB4.z;


			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[3][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[3][1].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].z = Q_HealSpark->HealSpark[Count].VertB4.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[3][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].z = Q_HealSpark->HealSpark[Count].VertB5.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[4][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[4][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].z = Q_HealSpark->HealSpark[Count].VertB5.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[4][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].z = Q_HealSpark->HealSpark[Count].VertB6.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[5][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;

			Q_HealSpark->HealSpark[Count].Lvert[5][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].z = Q_HealSpark->HealSpark[Count].VertB6.z;

			Q_HealSpark->HealSpark[Count].Lvert[5][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].z = Q_HealSpark->HealSpark[Count].VertB7.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[6][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;

			Q_HealSpark->HealSpark[Count].Lvert[6][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].z = Q_HealSpark->HealSpark[Count].VertB7.z;

			Q_HealSpark->HealSpark[Count].Lvert[6][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].z = Q_HealSpark->HealSpark[Count].VertB8.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[7][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;

			Q_HealSpark->HealSpark[Count].Lvert[7][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].z = Q_HealSpark->HealSpark[Count].VertB8.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[7][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].z = Q_HealSpark->HealSpark[Count].VertB1.z;


		//### Next Ring
			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[8][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].z = Q_HealSpark->HealSpark[Count].VertB1.z;

			Q_HealSpark->HealSpark[Count].Lvert[8][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].z = Q_HealSpark->HealSpark[Count].VertT1.z;

			Q_HealSpark->HealSpark[Count].Lvert[8][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].z = Q_HealSpark->HealSpark[Count].VertT2.z;

			Q_HealSpark->HealSpark[Count].Lvert[8][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].z = Q_HealSpark->HealSpark[Count].VertB2.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[9][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].z = Q_HealSpark->HealSpark[Count].VertB2.z;

			Q_HealSpark->HealSpark[Count].Lvert[9][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].z = Q_HealSpark->HealSpark[Count].VertT2.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[9][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].z = Q_HealSpark->HealSpark[Count].VertT3.z;

			Q_HealSpark->HealSpark[Count].Lvert[9][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].z = Q_HealSpark->HealSpark[Count].VertB3.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[10][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].z = Q_HealSpark->HealSpark[Count].VertB3.z;

			Q_HealSpark->HealSpark[Count].Lvert[10][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].z = Q_HealSpark->HealSpark[Count].VertT3.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[10][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[10][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].z = Q_HealSpark->HealSpark[Count].VertB4.z;


			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[11][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].z = Q_HealSpark->HealSpark[Count].VertB4.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[11][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[11][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].z = Q_HealSpark->HealSpark[Count].VertT5.z;

			Q_HealSpark->HealSpark[Count].Lvert[11][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].z = Q_HealSpark->HealSpark[Count].VertB5.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[12][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].z = Q_HealSpark->HealSpark[Count].VertB5.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[12][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].z = Q_HealSpark->HealSpark[Count].VertT5.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[12][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].z = Q_HealSpark->HealSpark[Count].VertT6.z;

			Q_HealSpark->HealSpark[Count].Lvert[12][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].z = Q_HealSpark->HealSpark[Count].VertB6.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[13][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].z = Q_HealSpark->HealSpark[Count].VertB6.z;

			Q_HealSpark->HealSpark[Count].Lvert[13][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].z = Q_HealSpark->HealSpark[Count].VertT6.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[13][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].z = Q_HealSpark->HealSpark[Count].VertT7.z;

			Q_HealSpark->HealSpark[Count].Lvert[13][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].z = Q_HealSpark->HealSpark[Count].VertB7.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[14][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].z = Q_HealSpark->HealSpark[Count].VertB7.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[14][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].z = Q_HealSpark->HealSpark[Count].VertT7.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[14][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].z = Q_HealSpark->HealSpark[Count].VertT8.z;

			Q_HealSpark->HealSpark[Count].Lvert[14][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].z = Q_HealSpark->HealSpark[Count].VertB8.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[15][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].z = Q_HealSpark->HealSpark[Count].VertB8.z;

			Q_HealSpark->HealSpark[Count].Lvert[15][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].z = Q_HealSpark->HealSpark[Count].VertT8.z;

			Q_HealSpark->HealSpark[Count].Lvert[15][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].z = Q_HealSpark->HealSpark[Count].VertT1.z;

			Q_HealSpark->HealSpark[Count].Lvert[15][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].z = Q_HealSpark->HealSpark[Count].VertB1.z;


		//Tail End
			//END Ring
			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[16][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[16][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].z = Q_HealSpark->HealSpark[Count].VertT1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[16][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].z = Q_HealSpark->HealSpark[Count].VertT2.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[17][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[17][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].z = Q_HealSpark->HealSpark[Count].VertT2.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[17][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].z = Q_HealSpark->HealSpark[Count].VertT3.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[18][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[18][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[18][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].z = Q_HealSpark->HealSpark[Count].VertT3.z;


			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[19][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[19][1].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[19][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].z = Q_HealSpark->HealSpark[Count].VertT5.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[20][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[20][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].z = Q_HealSpark->HealSpark[Count].VertT6.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[20][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].z = Q_HealSpark->HealSpark[Count].VertT5.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[21][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[21][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].z = Q_HealSpark->HealSpark[Count].VertT7.z;

			Q_HealSpark->HealSpark[Count].Lvert[21][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].z = Q_HealSpark->HealSpark[Count].VertT6.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[22][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[22][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].z = Q_HealSpark->HealSpark[Count].VertT8.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[22][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].z = Q_HealSpark->HealSpark[Count].VertT7.z;

			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[23][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[23][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].z = Q_HealSpark->HealSpark[Count].VertT1.z;

			Q_HealSpark->HealSpark[Count].Lvert[23][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].z = Q_HealSpark->HealSpark[Count].VertT8.z;


			//## CORONA ##
			Q_HealSpark->HealSpark[Count].Lvert[24][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].x = Q_HealSpark->HealSpark[Count].Pos.x;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].y = Q_HealSpark->HealSpark[Count].Pos.y;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].z = Q_HealSpark->HealSpark[Count].Pos.z;


		switch(Q_HealSpark->HealSpark[Count].HTYPE)
			{
			case 0:
				{
				if(Q_HealSpark->HealSpark[Count].AlpFade > 0)
					{
					int i = 0;
					while(i <= 7)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->HealSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 8;
					while(i <= 15)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 4, Medias->HealSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 15;
					while(i <= 23)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->RanSpark, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[24][0], 1, Medias->SparkCorona[Q_HealSpark->HealSpark[Count].CoronaMatCnt], QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT * (Q_HealSpark->HealSpark[Count].ScaleSTR / 33));
					}


				//### Increment Corona Material
				if(Q_HealSpark->HealSpark[Count].CoronaMatCntDIR == 0)
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt++;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt > 3)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 3;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt--;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt < 0)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 0;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 0;
						}
					}
				}break;


			case 1:
				{
				if(Q_HealSpark->HealSpark[Count].AlpFade > 0)
					{
					int i = 0;
					while(i <= 7)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->EGrabSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 8;
					while(i <= 15)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 4, Medias->EGrabSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 15;
					while(i <= 23)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->RanSpark, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[24][0], 1, Medias->EGrabCorona[Q_HealSpark->HealSpark[Count].CoronaMatCnt], QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT * (Q_HealSpark->HealSpark[Count].ScaleSTR / 33));
					}


				//### Increment Corona Material
				if(Q_HealSpark->HealSpark[Count].CoronaMatCntDIR == 0)
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt++;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt > 3)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 3;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt--;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt < 0)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 0;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 0;
						}
					}
				}break;
			}
		}
	}


void Q_EFFCon::HSpark_ClientFrame(int Count)
	{
	switch(Q_HealSpark->HealSpark[Count].HTYPE)
		{
		case 0:	//Heal Sparks
			{
			if(Q_HealSpark->HealSpark[Count].LightON == 0)
				{
				Q_HealSpark->HealSpark[Count].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
				Q_HealSpark->HealSpark[Count].LightColor.red = 255;
				Q_HealSpark->HealSpark[Count].LightColor.green = 255;
				Q_HealSpark->HealSpark[Count].LightColor.blue = 255;
				Q_HealSpark->HealSpark[Count].LightON = 1;

				SCRAM=0;
				while(SCRAM < 15 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.015f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 57;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					SCRAM++;
					}
				}

			if(Q_HealSpark->HealSpark[Count].Released == 1)
				{
				//#### Show Target Locks
				if(Q_HealSpark->HealSpark[Count].DisplayAlpha - 5 > 10) Q_HealSpark->HealSpark[Count].DisplayAlpha -= 5;
				else Q_HealSpark->HealSpark[Count].DisplayAlpha = 10;

				if(Q_HealSpark->HealSpark[Count].DisplayColor - 25 > 0) Q_HealSpark->HealSpark[Count].DisplayColor -= 25;
				else Q_HealSpark->HealSpark[Count].DisplayColor = 0;

				if(Q_HealSpark->HealSpark[Count].DisplayScale + 0.05 < 0.5) Q_HealSpark->HealSpark[Count].DisplayScale += 0.06;
				else Q_HealSpark->HealSpark[Count].DisplayScale = 0.5;

				if(Q_HealSpark->HealSpark[Count].Absorbed == 0)
					{
					if(Q_HealSpark->HealSpark[Count].ScaleSTR + 1 < 33) Q_HealSpark->HealSpark[Count].ScaleSTR += 1;
					else Q_HealSpark->HealSpark[Count].ScaleSTR = 33;
					}
				
				if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}
				else
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}
				}
			

			if(Q_HealSpark->HealSpark[Count].Absorbed > 0)
				{
				if(Q_HealSpark->HealSpark[Count].Absorbed == 1)
					{
					Q_HealSpark->HealSpark[Count].Absorbed = 2;
					Q_HealSpark->HealSpark[Count].AvatarLightB = 100;
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed > 0 && Q_HealSpark->HealSpark[Count].Absorbed < 3)
					{
					Q_HealSpark->HealSpark[Count].AvatarINCB += 20;

					//### Explode the Heal Spark
					if(Q_HealSpark->HealSpark[Count].AlpFade <= 0 && Q_HealSpark->HealSpark[Count].LightON == 1)
						{
						Q_HealSpark->HealSpark[Count].AlpFade = 0;
						Q_HealSpark->HealSpark[Count].LightON = 0;
						Qpo->Light_Remove(Q_HealSpark->HealSpark[Count].Light);
						}
					else
						{
						Q_HealSpark->HealSpark[Count].ScaleSTR += 10;
						Q_HealSpark->HealSpark[Count].AlpFade -= 25;
						}

					if(Q_HealSpark->HealSpark[Count].AvatarINCB > 255 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = 255;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 1;
						}

					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{
						Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					else
						{
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					
					if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 1)
						{
						Q_HealSpark->HealSpark[Count].Absorbed = 3;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 3)
					{
					if((Q_HealSpark->HealSpark[Count].AvatarINCB < Q_HealSpark->HealSpark[Count].AvatarLightB) && (Q_HealSpark->HealSpark[Count].LightBlueFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = Q_HealSpark->HealSpark[Count].AvatarLightB;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCB -= 20;


					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{
						Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					else
						{
						Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true);
						}
					
					if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
							{
							Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true);
							}
						else
							{
							Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,190,145,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true);
							}
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 5)
					{
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
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					}
				}

			Q_HealSpark->HealSpark[Count].CNTR += _->TimeScale;

			if(Q_HealSpark->HealSpark[Count].CNTR > 1)
				{
				Q_HealSpark->HealSpark[Count].CNTR = 0;

				jet=0;
				while(jet < 2 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.015f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 57;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			if(Q_HealSpark->HealSpark[Count].LightON == 1) Qpo->Light_SetAttr(Q_HealSpark->HealSpark[Count].Light, &Q_HealSpark->HealSpark[Count].Pos, &Q_HealSpark->HealSpark[Count].LightColor, 100, true);
			}break;

		case 1:	//Energy Grab Sparks
			{
			if(Q_HealSpark->HealSpark[Count].Released == 1)
				{
				//#### Show Target Locks
				if(Q_HealSpark->HealSpark[Count].DisplayAlpha - 5 > 10) Q_HealSpark->HealSpark[Count].DisplayAlpha -= 5;
				else Q_HealSpark->HealSpark[Count].DisplayAlpha = 10;

				if(Q_HealSpark->HealSpark[Count].DisplayColor - 25 > 0) Q_HealSpark->HealSpark[Count].DisplayColor -= 25;
				else Q_HealSpark->HealSpark[Count].DisplayColor = 0;

				if(Q_HealSpark->HealSpark[Count].DisplayScale + 0.05 < 0.5) Q_HealSpark->HealSpark[Count].DisplayScale += 0.06;
				else Q_HealSpark->HealSpark[Count].DisplayScale = 0.9;

				if(Q_HealSpark->HealSpark[Count].Absorbed == 0)
					{
					if(Q_HealSpark->HealSpark[Count].ScaleSTR + 1 < 33) Q_HealSpark->HealSpark[Count].ScaleSTR += 1;
					else Q_HealSpark->HealSpark[Count].ScaleSTR = 33;
					}
				
				if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = playerAV[g_Player]->Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = playerAV[g_Player]->Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = playerAV[g_Player]->Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}
				else
					{
					Q_HealSpark->HealSpark[Count].LaserLV.a = Q_HealSpark->HealSpark[Count].DisplayAlpha;
					Q_HealSpark->HealSpark[Count].LaserLV.r = 0;
					Q_HealSpark->HealSpark[Count].LaserLV.g = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.b = 255;
					Q_HealSpark->HealSpark[Count].LaserLV.x = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.x;
					Q_HealSpark->HealSpark[Count].LaserLV.y = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.y + 65;
					Q_HealSpark->HealSpark[Count].LaserLV.z = Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Xform.Translation.z;

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].LaserLV, 1, Medias->reticuleE, QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, Q_HealSpark->HealSpark[Count].DisplayScale);
					}
				}

			if(Q_HealSpark->HealSpark[Count].Absorbed > 0)
				{
				if(Q_HealSpark->HealSpark[Count].Absorbed == 1)
					{
					Q_HealSpark->HealSpark[Count].Absorbed = 2;
					Q_HealSpark->HealSpark[Count].AvatarLightR = 190;
					Q_HealSpark->HealSpark[Count].AvatarLightG = 145;
					Q_HealSpark->HealSpark[Count].AvatarLightB = 100;
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed > 0 && Q_HealSpark->HealSpark[Count].Absorbed < 3)
					{
					Q_HealSpark->HealSpark[Count].AvatarINCR -= 20;
					Q_HealSpark->HealSpark[Count].AvatarINCG -= 20;
					Q_HealSpark->HealSpark[Count].AvatarINCB -= 20;
					
					//### Explode the Heal Spark
					if(Q_HealSpark->HealSpark[Count].AlpFade <= 0)
						{
						Q_HealSpark->HealSpark[Count].AlpFade = 0;
						}
					else
						{
						Q_HealSpark->HealSpark[Count].ScaleSTR += 10;
						Q_HealSpark->HealSpark[Count].AlpFade -= 25;
						}

					if(Q_HealSpark->HealSpark[Count].AvatarINCR < 70 && Q_HealSpark->HealSpark[Count].LightRedFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCR = 70;
						Q_HealSpark->HealSpark[Count].LightRedFULL = 1;
						}
					if(Q_HealSpark->HealSpark[Count].AvatarINCG < 70 && Q_HealSpark->HealSpark[Count].LightGreenFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCG = 70;
						Q_HealSpark->HealSpark[Count].LightGreenFULL = 1;
						}
					
					if(Q_HealSpark->HealSpark[Count].AvatarINCB < 70 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = 70;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 1;
						}

					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{ Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					else { Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					
					if(Q_HealSpark->HealSpark[Count].LightRedFULL == 1 && Q_HealSpark->HealSpark[Count].LightGreenFULL == 1 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 1)
						{
						Q_HealSpark->HealSpark[Count].Absorbed = 3;
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 3)
					{
					if((Q_HealSpark->HealSpark[Count].AvatarINCR > Q_HealSpark->HealSpark[Count].AvatarLightR) && (Q_HealSpark->HealSpark[Count].LightRedFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCR = Q_HealSpark->HealSpark[Count].AvatarLightR;
						Q_HealSpark->HealSpark[Count].LightRedFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightRedFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCR += 20;

					if((Q_HealSpark->HealSpark[Count].AvatarINCG > Q_HealSpark->HealSpark[Count].AvatarLightG) && (Q_HealSpark->HealSpark[Count].LightGreenFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCG = Q_HealSpark->HealSpark[Count].AvatarLightG;
						Q_HealSpark->HealSpark[Count].LightGreenFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightGreenFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCG += 20;

					if((Q_HealSpark->HealSpark[Count].AvatarINCB > Q_HealSpark->HealSpark[Count].AvatarLightB) && (Q_HealSpark->HealSpark[Count].LightBlueFULL == 1))
						{
						Q_HealSpark->HealSpark[Count].AvatarINCB = Q_HealSpark->HealSpark[Count].AvatarLightB;
						Q_HealSpark->HealSpark[Count].LightBlueFULL = 0;
						}
					else if(Q_HealSpark->HealSpark[Count].LightBlueFULL == 1) Q_HealSpark->HealSpark[Count].AvatarINCB += 20;


					if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
					{ Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					else { Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarINCR,Q_HealSpark->HealSpark[Count].AvatarINCG,Q_HealSpark->HealSpark[Count].AvatarINCB,false,8,NULL,true); }
					
					if(Q_HealSpark->HealSpark[Count].LightRedFULL == 0 && Q_HealSpark->HealSpark[Count].LightGreenFULL == 0 && Q_HealSpark->HealSpark[Count].LightBlueFULL == 0)
						{
						if(Q_HealSpark->HealSpark[Count].HealTarget == 250)
						{ Qpo->Avatar_SetLighting(&playerAV[g_Player]->Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarLightR,Q_HealSpark->HealSpark[Count].AvatarLightG,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true); }
						else { Qpo->Avatar_SetLighting(&Q_Forge->Forge[Q_HealSpark->HealSpark[Count].HealTarget].AV.Avatar,true,&goup,200,200,200,Q_HealSpark->HealSpark[Count].AvatarLightR,Q_HealSpark->HealSpark[Count].AvatarLightG,Q_HealSpark->HealSpark[Count].AvatarLightB,false,8,NULL,true); }
						}
					}

				if(Q_HealSpark->HealSpark[Count].Absorbed == 5)
					{
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
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					}
				}

			Q_HealSpark->HealSpark[Count].CNTR += _->TimeScale;

			if(Q_HealSpark->HealSpark[Count].CNTR > 1)
				{
				Q_HealSpark->HealSpark[Count].CNTR = 0;

				jet=0;
				while(jet < 2 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.015f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 57;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 0;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_HealSpark->HealSpark[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_HealSpark->HealSpark[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			}break;
		}
	

	//### Spark Drawing Scale
	
	Q_HealSpark->HealSpark[Count].Scale = Q_HealSpark->HealSpark[Count].ScaleSTR;
	Q_HealSpark->HealSpark[Count].ScaleBIT = 0.15f;	//0.2

	//Calculate Direction Vectors
	Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
	Qpo->Transform_RotateVector(&RotateMatrix, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VecLeft);
	Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].VecLeft);
	Q_HealSpark->HealSpark[Count].VecLeft.y = 0;

	Qpo->Vec3d_CrossProduct(&Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VecUp);
	Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].VecUp);

	Q_HealSpark->HealSpark[Count].VecSTR = Q_HealSpark->HealSpark[Count].TraVec;
	Qpo->Vec3d_Normalize(&Q_HealSpark->HealSpark[Count].TraVec);

	//Front Vert
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/17, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VertF1);

	//Ball Verts
	//Standard Left Up down
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB1);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB2);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB2, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB2);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB3);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB4);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB4, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB4);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB5);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB6);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB6, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB6);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/8, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB7);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertB8);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertB8, -Q_HealSpark->HealSpark[Count].Scale/12, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertB8);

	//### Twist Tail Points round
	Q_HealSpark->HealSpark[Count].VecSTR = Q_HealSpark->HealSpark[Count].TraVec;
	Q_HealSpark->HealSpark[Count].DownSpeedSTR = Q_HealSpark->HealSpark[Count].DownSpeed;

	Q_HealSpark->HealSpark[Count].TraVec.y += (Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale);
	Q_HealSpark->HealSpark[Count].TraLength = Qpo->Vec3d_Length(&Q_HealSpark->HealSpark[Count].TraVec);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -((Q_HealSpark->HealSpark[Count].Speed*(Q_HealSpark->HealSpark[Count].TraLength*1))*_->TimeScale), &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].PosBrush);

	Q_HealSpark->HealSpark[Count].TraVec = Q_HealSpark->HealSpark[Count].VecSTR;
	Q_HealSpark->HealSpark[Count].DownSpeed = Q_HealSpark->HealSpark[Count].DownSpeedSTR;

	//Shift back for tail verts  ##WORKS BUT FROZEN
	//Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -Q_HealSpark->HealSpark[Count].Scale/2.6, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].PosBrush);

	//### Reduce Scale for tail verts
	Q_HealSpark->HealSpark[Count].Scale /= 3;

	//Tail Verts
	//Standard Left Up down
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT1);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT2);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT2, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT2);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT3);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT4);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT4, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT4);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT5);


	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT6);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT6, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT6);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/24, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT7);

	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecUp, &Q_HealSpark->HealSpark[Count].VertT8);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].VertT8, -Q_HealSpark->HealSpark[Count].Scale/36, &Q_HealSpark->HealSpark[Count].VecLeft, &Q_HealSpark->HealSpark[Count].VertT8);

	//Shift back for End Vert
	//Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].PosBrush, -Q_HealSpark->HealSpark[Count].Scale/2, &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VertE1);

	//### Twist End Point round
	Q_HealSpark->HealSpark[Count].VecSTR = Q_HealSpark->HealSpark[Count].TraVec;
	Q_HealSpark->HealSpark[Count].DownSpeedSTR = Q_HealSpark->HealSpark[Count].DownSpeed;

	Q_HealSpark->HealSpark[Count].TraVec.y += (Q_HealSpark->HealSpark[Count].DownSpeed*_->TimeScale);
	Q_HealSpark->HealSpark[Count].TraLength = Qpo->Vec3d_Length(&Q_HealSpark->HealSpark[Count].TraVec);
	Qpo->Vec3d_AddScaled(&Q_HealSpark->HealSpark[Count].Pos, -((Q_HealSpark->HealSpark[Count].Speed*(Q_HealSpark->HealSpark[Count].TraLength*2.4))*_->TimeScale), &Q_HealSpark->HealSpark[Count].TraVec, &Q_HealSpark->HealSpark[Count].VertE1);

	Q_HealSpark->HealSpark[Count].TraVec = Q_HealSpark->HealSpark[Count].VecSTR;
	Q_HealSpark->HealSpark[Count].DownSpeed = Q_HealSpark->HealSpark[Count].DownSpeedSTR;

	if(Q_HealSpark->HealSpark[Count].Absorbed == 0)
		{
		if(Q_HealSpark->HealSpark[Count].FadeDir == 0)
			{
			Q_HealSpark->HealSpark[Count].AlpFade -= 40;//((((float)rand() / 32767)*10)+5);
			if(Q_HealSpark->HealSpark[Count].AlpFade <= 170)
				{
				Q_HealSpark->HealSpark[Count].AlpFade = 170;
				Q_HealSpark->HealSpark[Count].FadeDir = 1;
				}
			}

		if(Q_HealSpark->HealSpark[Count].FadeDir == 1)
			{
			Q_HealSpark->HealSpark[Count].AlpFade += 40;//((((float)rand() / 32767)*10)+5);
			if(Q_HealSpark->HealSpark[Count].AlpFade >= 255)
				{
				Q_HealSpark->HealSpark[Count].AlpFade = 255;
				Q_HealSpark->HealSpark[Count].FadeDir = 0;
				}
			}
		}
	

		int a=0;
		while( a <= 23 )
			{
			int b=0;
			while( b <= 3 )
				{
				Q_HealSpark->HealSpark[Count].Lvert[a][b].a = Q_HealSpark->HealSpark[Count].AlpFade;
				Q_HealSpark->HealSpark[Count].Lvert[a][b].b = 255;
				Q_HealSpark->HealSpark[Count].Lvert[a][b].g = 225;
				Q_HealSpark->HealSpark[Count].Lvert[a][b].r = 225;
				b++;
				}
			a++;
			}

		//Set Corona
		Q_HealSpark->HealSpark[Count].Lvert[24][0].a = Q_HealSpark->HealSpark[Count].AlpFade/2.2;
		Q_HealSpark->HealSpark[Count].Lvert[24][0].b = 255;
		Q_HealSpark->HealSpark[Count].Lvert[24][0].g = 255;
		Q_HealSpark->HealSpark[Count].Lvert[24][0].r = 255;

			//First Ring
			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[0][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[0][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[0][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[0][1].z = Q_HealSpark->HealSpark[Count].VertB1.z;

			Q_HealSpark->HealSpark[Count].Lvert[0][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[0][2].z = Q_HealSpark->HealSpark[Count].VertB2.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[1][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[1][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[1][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[1][1].z = Q_HealSpark->HealSpark[Count].VertB2.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[1][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[1][2].z = Q_HealSpark->HealSpark[Count].VertB3.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[2][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[2][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[2][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[2][1].z = Q_HealSpark->HealSpark[Count].VertB3.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[2][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[2][2].z = Q_HealSpark->HealSpark[Count].VertB4.z;


			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[3][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[3][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[3][1].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[3][1].z = Q_HealSpark->HealSpark[Count].VertB4.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[3][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[3][2].z = Q_HealSpark->HealSpark[Count].VertB5.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[4][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[4][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[4][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[4][1].z = Q_HealSpark->HealSpark[Count].VertB5.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[4][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[4][2].z = Q_HealSpark->HealSpark[Count].VertB6.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[5][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[5][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;

			Q_HealSpark->HealSpark[Count].Lvert[5][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[5][1].z = Q_HealSpark->HealSpark[Count].VertB6.z;

			Q_HealSpark->HealSpark[Count].Lvert[5][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[5][2].z = Q_HealSpark->HealSpark[Count].VertB7.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[6][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[6][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;

			Q_HealSpark->HealSpark[Count].Lvert[6][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[6][1].z = Q_HealSpark->HealSpark[Count].VertB7.z;

			Q_HealSpark->HealSpark[Count].Lvert[6][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[6][2].z = Q_HealSpark->HealSpark[Count].VertB8.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[7][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].x = Q_HealSpark->HealSpark[Count].VertF1.x;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].y = Q_HealSpark->HealSpark[Count].VertF1.y;
			Q_HealSpark->HealSpark[Count].Lvert[7][0].z = Q_HealSpark->HealSpark[Count].VertF1.z;

			Q_HealSpark->HealSpark[Count].Lvert[7][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[7][1].z = Q_HealSpark->HealSpark[Count].VertB8.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[7][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[7][2].z = Q_HealSpark->HealSpark[Count].VertB1.z;


		//### Next Ring
			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[8][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][0].z = Q_HealSpark->HealSpark[Count].VertB1.z;

			Q_HealSpark->HealSpark[Count].Lvert[8][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][1].z = Q_HealSpark->HealSpark[Count].VertT1.z;

			Q_HealSpark->HealSpark[Count].Lvert[8][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][2].z = Q_HealSpark->HealSpark[Count].VertT2.z;

			Q_HealSpark->HealSpark[Count].Lvert[8][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[8][3].z = Q_HealSpark->HealSpark[Count].VertB2.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[9][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].x = Q_HealSpark->HealSpark[Count].VertB2.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].y = Q_HealSpark->HealSpark[Count].VertB2.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][0].z = Q_HealSpark->HealSpark[Count].VertB2.z;

			Q_HealSpark->HealSpark[Count].Lvert[9][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][1].z = Q_HealSpark->HealSpark[Count].VertT2.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[9][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][2].z = Q_HealSpark->HealSpark[Count].VertT3.z;

			Q_HealSpark->HealSpark[Count].Lvert[9][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[9][3].z = Q_HealSpark->HealSpark[Count].VertB3.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[10][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].x = Q_HealSpark->HealSpark[Count].VertB3.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].y = Q_HealSpark->HealSpark[Count].VertB3.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][0].z = Q_HealSpark->HealSpark[Count].VertB3.z;

			Q_HealSpark->HealSpark[Count].Lvert[10][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][1].z = Q_HealSpark->HealSpark[Count].VertT3.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[10][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][2].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[10][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[10][3].z = Q_HealSpark->HealSpark[Count].VertB4.z;


			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[11][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].x = Q_HealSpark->HealSpark[Count].VertB4.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].y = Q_HealSpark->HealSpark[Count].VertB4.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][0].z = Q_HealSpark->HealSpark[Count].VertB4.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[11][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][1].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[11][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][2].z = Q_HealSpark->HealSpark[Count].VertT5.z;

			Q_HealSpark->HealSpark[Count].Lvert[11][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[11][3].z = Q_HealSpark->HealSpark[Count].VertB5.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[12][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].x = Q_HealSpark->HealSpark[Count].VertB5.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].y = Q_HealSpark->HealSpark[Count].VertB5.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][0].z = Q_HealSpark->HealSpark[Count].VertB5.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[12][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][1].z = Q_HealSpark->HealSpark[Count].VertT5.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[12][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][2].z = Q_HealSpark->HealSpark[Count].VertT6.z;

			Q_HealSpark->HealSpark[Count].Lvert[12][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[12][3].z = Q_HealSpark->HealSpark[Count].VertB6.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[13][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].x = Q_HealSpark->HealSpark[Count].VertB6.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].y = Q_HealSpark->HealSpark[Count].VertB6.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][0].z = Q_HealSpark->HealSpark[Count].VertB6.z;

			Q_HealSpark->HealSpark[Count].Lvert[13][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][1].z = Q_HealSpark->HealSpark[Count].VertT6.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[13][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][2].z = Q_HealSpark->HealSpark[Count].VertT7.z;

			Q_HealSpark->HealSpark[Count].Lvert[13][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[13][3].z = Q_HealSpark->HealSpark[Count].VertB7.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[14][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].x = Q_HealSpark->HealSpark[Count].VertB7.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].y = Q_HealSpark->HealSpark[Count].VertB7.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][0].z = Q_HealSpark->HealSpark[Count].VertB7.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[14][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][1].z = Q_HealSpark->HealSpark[Count].VertT7.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[14][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][2].z = Q_HealSpark->HealSpark[Count].VertT8.z;

			Q_HealSpark->HealSpark[Count].Lvert[14][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[14][3].z = Q_HealSpark->HealSpark[Count].VertB8.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[15][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].x = Q_HealSpark->HealSpark[Count].VertB8.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].y = Q_HealSpark->HealSpark[Count].VertB8.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][0].z = Q_HealSpark->HealSpark[Count].VertB8.z;

			Q_HealSpark->HealSpark[Count].Lvert[15][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][1].z = Q_HealSpark->HealSpark[Count].VertT8.z;

			Q_HealSpark->HealSpark[Count].Lvert[15][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][2].z = Q_HealSpark->HealSpark[Count].VertT1.z;

			Q_HealSpark->HealSpark[Count].Lvert[15][3].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].x = Q_HealSpark->HealSpark[Count].VertB1.x;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].y = Q_HealSpark->HealSpark[Count].VertB1.y;
			Q_HealSpark->HealSpark[Count].Lvert[15][3].z = Q_HealSpark->HealSpark[Count].VertB1.z;


		//Tail End
			//END Ring
			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[16][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[16][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[16][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[16][1].z = Q_HealSpark->HealSpark[Count].VertT1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[16][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[16][2].z = Q_HealSpark->HealSpark[Count].VertT2.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[17][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[17][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[17][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].x = Q_HealSpark->HealSpark[Count].VertT2.x;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].y = Q_HealSpark->HealSpark[Count].VertT2.y;
			Q_HealSpark->HealSpark[Count].Lvert[17][1].z = Q_HealSpark->HealSpark[Count].VertT2.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[17][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[17][2].z = Q_HealSpark->HealSpark[Count].VertT3.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[18][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[18][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[18][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[18][1].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[18][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].x = Q_HealSpark->HealSpark[Count].VertT3.x;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].y = Q_HealSpark->HealSpark[Count].VertT3.y;
			Q_HealSpark->HealSpark[Count].Lvert[18][2].z = Q_HealSpark->HealSpark[Count].VertT3.z;


			//## FRONT ##
			Q_HealSpark->HealSpark[Count].Lvert[19][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[19][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[19][1].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].x = Q_HealSpark->HealSpark[Count].VertT4.x;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].y = Q_HealSpark->HealSpark[Count].VertT4.y;
			Q_HealSpark->HealSpark[Count].Lvert[19][1].z = Q_HealSpark->HealSpark[Count].VertT4.z;

			Q_HealSpark->HealSpark[Count].Lvert[19][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[19][2].z = Q_HealSpark->HealSpark[Count].VertT5.z;


			//## MIDDLE ##
			Q_HealSpark->HealSpark[Count].Lvert[20][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].v = 1;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[20][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[20][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[20][1].z = Q_HealSpark->HealSpark[Count].VertT6.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[20][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].x = Q_HealSpark->HealSpark[Count].VertT5.x;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].y = Q_HealSpark->HealSpark[Count].VertT5.y;
			Q_HealSpark->HealSpark[Count].Lvert[20][2].z = Q_HealSpark->HealSpark[Count].VertT5.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[21][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[21][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[21][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[21][1].z = Q_HealSpark->HealSpark[Count].VertT7.z;

			Q_HealSpark->HealSpark[Count].Lvert[21][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].x = Q_HealSpark->HealSpark[Count].VertT6.x;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].y = Q_HealSpark->HealSpark[Count].VertT6.y;
			Q_HealSpark->HealSpark[Count].Lvert[21][2].z = Q_HealSpark->HealSpark[Count].VertT6.z;


			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[22][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[22][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[22][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[22][1].z = Q_HealSpark->HealSpark[Count].VertT8.z;
				
			Q_HealSpark->HealSpark[Count].Lvert[22][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].x = Q_HealSpark->HealSpark[Count].VertT7.x;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].y = Q_HealSpark->HealSpark[Count].VertT7.y;
			Q_HealSpark->HealSpark[Count].Lvert[22][2].z = Q_HealSpark->HealSpark[Count].VertT7.z;

			//## TAIL ##
			Q_HealSpark->HealSpark[Count].Lvert[23][0].u = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].x = Q_HealSpark->HealSpark[Count].VertE1.x;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].y = Q_HealSpark->HealSpark[Count].VertE1.y;
			Q_HealSpark->HealSpark[Count].Lvert[23][0].z = Q_HealSpark->HealSpark[Count].VertE1.z;

			Q_HealSpark->HealSpark[Count].Lvert[23][1].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].x = Q_HealSpark->HealSpark[Count].VertT1.x;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].y = Q_HealSpark->HealSpark[Count].VertT1.y;
			Q_HealSpark->HealSpark[Count].Lvert[23][1].z = Q_HealSpark->HealSpark[Count].VertT1.z;

			Q_HealSpark->HealSpark[Count].Lvert[23][2].u = 1;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].v = 0.5;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].x = Q_HealSpark->HealSpark[Count].VertT8.x;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].y = Q_HealSpark->HealSpark[Count].VertT8.y;
			Q_HealSpark->HealSpark[Count].Lvert[23][2].z = Q_HealSpark->HealSpark[Count].VertT8.z;


			//## CORONA ##
			Q_HealSpark->HealSpark[Count].Lvert[24][0].u = 0;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].v = 0;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].x = Q_HealSpark->HealSpark[Count].Pos.x;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].y = Q_HealSpark->HealSpark[Count].Pos.y;
			Q_HealSpark->HealSpark[Count].Lvert[24][0].z = Q_HealSpark->HealSpark[Count].Pos.z;


		switch(Q_HealSpark->HealSpark[Count].HTYPE)
			{
			case 0:
				{
				if(Q_HealSpark->HealSpark[Count].AlpFade > 0)
					{
					int i = 0;
					while(i <= 7)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->HealSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 8;
					while(i <= 15)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 4, Medias->HealSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 15;
					while(i <= 23)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->RanSpark, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[24][0], 1, Medias->SparkCorona[Q_HealSpark->HealSpark[Count].CoronaMatCnt], QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT * (Q_HealSpark->HealSpark[Count].ScaleSTR / 33));
					}


				//### Increment Corona Material
				if(Q_HealSpark->HealSpark[Count].CoronaMatCntDIR == 0)
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt++;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt > 3)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 3;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt--;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt < 0)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 0;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 0;
						}
					}
				}break;


			case 1:
				{
				if(Q_HealSpark->HealSpark[Count].AlpFade > 0)
					{
					int i = 0;
					while(i <= 7)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->EGrabSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 8;
					while(i <= 15)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 4, Medias->EGrabSparktail, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					i = 15;
					while(i <= 23)
						{
						Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[i][0], 3, Medias->RanSpark, QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT);
						i++;
						}

					Qpo->Poly_AddOnce(&Q_HealSpark->HealSpark[Count].Lvert[24][0], 1, Medias->EGrabCorona[Q_HealSpark->HealSpark[Count].CoronaMatCnt], QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, Q_HealSpark->HealSpark[Count].ScaleBIT * (Q_HealSpark->HealSpark[Count].ScaleSTR / 33));
					}


				//### Increment Corona Material
				if(Q_HealSpark->HealSpark[Count].CoronaMatCntDIR == 0)
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt++;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt > 3)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 3;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_HealSpark->HealSpark[Count].CoronaMatCnt--;
					if(Q_HealSpark->HealSpark[Count].CoronaMatCnt < 0)
						{
						Q_HealSpark->HealSpark[Count].CoronaMatCnt = 0;
						Q_HealSpark->HealSpark[Count].CoronaMatCntDIR = 0;
						}
					}
				}break;
			}
	};