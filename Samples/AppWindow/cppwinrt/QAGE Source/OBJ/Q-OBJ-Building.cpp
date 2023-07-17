/*

    QBuilding - QBuilding Server Class Definition
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

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
#include "Q-OBJ-ObjectTypes.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-BulletSystem.h"

#include "Q-OBJ-Building.h"

#include "Q-NET-ProtoMap.h"

Q_BuildingCLS::Q_BuildingCLS()
{
}

Q_BuildingCLS::~Q_BuildingCLS()
{
}

void Q_EFFCon::Building_ControlFrame(int Count)	//##### SENTRY CONTROL
	{
	//#### EFFECTS DRAW BUILDING ####//
	switch(Q_Building->Building[Count].m_BuildingType)
		{
		case 0:
			{
			Q_Building->Building[Count].ImageLvert.x = Q_Building->Building[Count].Pos.x;
			Q_Building->Building[Count].ImageLvert.y = Q_Building->Building[Count].Pos.y;
			Q_Building->Building[Count].ImageLvert.z = Q_Building->Building[Count].Pos.z;
			Q_Building->Building[Count].ImageLvert.r = 255;
			Q_Building->Building[Count].ImageLvert.g = (55 + ((float)(Q_Object->Object[Q_Building->Building[Count].m_QObjectID].StrengthBANK / Q_Object->Object[Q_Building->Building[Count].m_QObjectID].StrengthMAX) * 200));
			Q_Building->Building[Count].ImageLvert.b = 255;
			Q_Building->Building[Count].ImageLvert.a = 200;

			Qpo->Poly_AddOnce(&Q_Building->Building[Count].ImageLvert, 1, Medias->QAEFF09, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT | QPOLY_REND_NO_OCCLUDE, 1.0f);
			}break;
		}

	//#### COLLISION DETECTION ####//
	//###-- Immunity Counter - The sentries come packaged for release immediatly, they are invincible for 1000 ticks
	Q_Building->Building[Count].ImmCNT--;
	if(Q_Building->Building[Count].ImmCNT < 0) Q_Building->Building[Count].ImmCNT = 0;

	//##### HANDLE OBJECT DESTRUCTION **************************************************
	if(Q_Object->Object[Q_Building->Building[Count].m_QObjectID].StrengthBANK <= 0 && Q_Building->Building[Count].ImmCNT == 0)
		{
		Q_Building->Building[Count].LIVE = 0;
		}

	//#### BUILDING PROCESS ####//
	//#### EFFECTS DRAW BUILDING ####//
	switch(Q_Building->Building[Count].m_BuildingType)
		{
		case 0:
			{
			if(player[g_Player]->HB_Dead == 0)
				{
				if(player[g_Player]->Team == Q_Building->Building[Count].Team)
					{
					TESTPosS = playerAV[g_Player]->Xform.Translation;
					TESTPosS.y += 60;
					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Building->Building[Count].Pos);

					if(TESTShieldDIST < (Q_Building->Building[Count].Range * 2))
						{
						if(player[g_Player]->HB_Energy < player[g_Player]->HB_MaxEnergy)
							{
							player[g_Player]->HB_Energy += (Q_Building->Building[Count].m_Potency / 1000) + 1;

							if(_->NomMelHit < 300)
								{
								QpoVec3d f_VecTo;
								float f_Length;

								Qpo->Vec3d_Subtract(&TESTPosS, &Q_Building->Building[Count].Pos, &f_VecTo);
								f_Length = Qpo->Vec3d_Length(&f_VecTo);
								Qpo->Vec3d_Normalize(&f_VecTo);
								Qpo->Vec3d_AddScaled(&Q_Building->Building[Count].Pos, ((float)rand() / 32767) * f_Length, &f_VecTo, &Q_MeleeHit->MeleeHit[_->NomMelHit].Impact);

								Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = 250;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = (Q_Building->Building[Count].m_Potency / 1000) + 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = (Q_Building->Building[Count].m_Potency / 1000) + 1;
								//Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
								//Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = (Q_Building->Building[Count].m_Potency / 5000) + 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/20) * 0;

								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;

								Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.x = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y = -1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.z = 0;
								Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

								_->NomMelHit++;
								}

							if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
							}
						}
					}
				}

			helly=0;
			while(helly < _->NomAI)
				{
				if(Q_Forge->Forge[helly].LIVE == 1 && Q_Forge->Forge[helly].HB_Dead == 0)
					{
					if(Q_Forge->Forge[helly].Team == Q_Building->Building[Count].Team)
						{
						TESTPosS = Q_Forge->Forge[helly].AV.Xform.Translation;
						TESTPosS.y += 60;
						TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Building->Building[Count].Pos);

						if(TESTShieldDIST < (Q_Building->Building[Count].Range * 2))
							{
							if(Q_Forge->Forge[helly].HB_Energy < Q_Forge->Forge[helly].HB_MaxEnergy)
								{
								Q_Forge->Forge[helly].HB_Energy += (Q_Building->Building[Count].m_Potency / 1000) + 1;

								if(_->NomMelHit < 300)
									{
									QpoVec3d f_VecTo;
									float f_Length;

									Qpo->Vec3d_Subtract(&TESTPosS, &Q_Building->Building[Count].Pos, &f_VecTo);
									f_Length = Qpo->Vec3d_Length(&f_VecTo);
									Qpo->Vec3d_Normalize(&f_VecTo);
									Qpo->Vec3d_AddScaled(&Q_Building->Building[Count].Pos, ((float)rand() / 32767) * f_Length, &f_VecTo, &Q_MeleeHit->MeleeHit[_->NomMelHit].Impact);

									Q_MeleeHit->MeleeHit[_->NomMelHit].AvID = helly;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 8;
																		//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH = (Q_Building->Building[Count].m_Potency / 1000) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSNAP = (Q_Building->Building[Count].m_Potency / 1000) + 1;
									//Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = Q_Forge->Forge[AIflag].AttPos.Translation;	//Point of impact in world space
									Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
									//Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIflag].AV, BoneDef[bonenum], &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
									Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = (Q_Building->Building[Count].m_Potency / 5000) + 1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = (Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/20) * 0;

									//Expandro3D Struct
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 0.01;					//Switch 0 = Off !0 = On
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 100 * ((Q_MeleeHit->MeleeHit[_->NomMelHit].AttackSTRENGTH/8)+1);				//Max Radius
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 200;

									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 150;
									Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 150;

									Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 3;

									Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.x = 0;
									Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.y = -1;
									Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm.z = 0;
									Qpo->Vec3d_Normalize(&Q_MeleeHit->MeleeHit[_->NomMelHit].ReactionNorm);

									_->NomMelHit++;
									}

								if(Q_Forge->Forge[helly].HB_Energy > Q_Forge->Forge[helly].HB_MaxEnergy) Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;
								}
							}
						}
					}

				helly++;
				}
			}break;
		}
	}