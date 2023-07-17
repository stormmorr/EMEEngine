/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Quantum Objects-
	*/#include "pch.h"/*- Minor Component -Sentry Guns-

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

using namespace GVARS;

namespace GVARS
{

	//####### TEMPORARY BUILD ITEMS

void Q_EFFCon::BMSentry_ControlFrame(int Count)	//##### SENTRY CONTROL
	{
	//#### EFFECTS DRAW SENTRY
	Q_BMSentry->BMSentry[Count].ImageLvert.x = Q_BMSentry->BMSentry[Count].Pos.x;
	Q_BMSentry->BMSentry[Count].ImageLvert.y = Q_BMSentry->BMSentry[Count].Pos.y;
	Q_BMSentry->BMSentry[Count].ImageLvert.z = Q_BMSentry->BMSentry[Count].Pos.z;
	Q_BMSentry->BMSentry[Count].ImageLvert.r = 255;
	Q_BMSentry->BMSentry[Count].ImageLvert.g = (55 + ((float)(Q_Object->Object[Q_BMSentry->BMSentry[Count].QObjID].StrengthBANK / Q_Object->Object[Q_BMSentry->BMSentry[Count].QObjID].StrengthMAX) * 200));
	Q_BMSentry->BMSentry[Count].ImageLvert.b = 255;
	Q_BMSentry->BMSentry[Count].ImageLvert.a = 200;

	Qpo->Poly_AddOnce(&Q_BMSentry->BMSentry[Count].ImageLvert, 1, Medias->QAEFF12, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT | QPOLY_REND_NO_OCCLUDE, 1.0f);

	//##### SENTRY BULLET EFFECTS
	if(_->NetworkOption != 1)
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID == 250)
			{
			jet=0;	//##### AI Check (AvID respective) for in range
			while(jet < _->NomAI)
				{
				TESTPosS = Q_Forge->Forge[jet].AV.Xform.Translation;
				TESTPosS.y += 60;
				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_BMSentry->BMSentry[Count].Pos);

				if((TESTShieldDIST < (Q_BMSentry->BMSentry[Count].Range * 8)) && Q_Forge->Forge[jet].HB_Dead == 0)
					{
					if(Q_BMSentry->BMSentry[Count].FireRateCNT[jet] >= (1 - ((float)Q_BMSentry->BMSentry[Count].FireRate / 5000)) * 36) Q_BMSentry->BMSentry[Count].FireRateCNT[jet] = 0;
					else if(Q_BMSentry->BMSentry[Count].FireRateCNT[jet] > 0) Q_BMSentry->BMSentry[Count].FireRateCNT[jet] += 1 * _->TimeScale;

					if(Q_BMSentry->BMSentry[Count].FireRateCNT[jet] == 0)	//FIRE!
						{
						Q_BMSentry->BMSentry[Count].FireRateCNT[jet] = 1;

						SCRAMJET = 0;
						while((SCRAMJET < Q_BMSentry->BMSentry[Count].BulletCNT) && (_->NomBullet < 14999))	//V-- Maximum bullet restriction
							{
							//Trajectory
							Q_Bullet->Bullet[_->NomBullet].WorldPos = Q_BMSentry->BMSentry[Count].Pos;
							Q_Bullet->Bullet[_->NomBullet].ORIGPos = Q_BMSentry->BMSentry[Count].Pos;
							Qpo->Vec3d_Subtract(&TESTPosS, &Q_BMSentry->BMSentry[Count].Pos, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
							Qpo->Vec3d_Normalize(&Q_Bullet->Bullet[_->NomBullet].TrajVec);
							Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[_->NomBullet].WorldPos, 4.5, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &Q_Bullet->Bullet[_->NomBullet].WorldPos);

							Q_Bullet->Bullet[_->NomBullet].TrajVec.x += ((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);
							Q_Bullet->Bullet[_->NomBullet].TrajVec.y += ((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);
							Q_Bullet->Bullet[_->NomBullet].TrajVec.z += ((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);

							if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x))
								{
								major = 1;
								if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y))
									major = 2;
								}
							else
								{
								if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x))
									major = 2;
								}
							
							if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x)==1.0f || fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y)==1.0f || fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z)==1.0f)
								{
								if ((major == 0 && Q_Bullet->Bullet[_->NomBullet].TrajVec.x > 0) || major == 1)
									{
										TempVec1.x = 0.0f;
										TempVec1.y = 0.0f;
										TempVec1.z = -1.0f;
									}
								else if (major == 0)
									{
										TempVec1.x = 0.0f;
										TempVec1.y = 0.0f;
										TempVec1.z = 1.0f;
									}
								else 
									{
										TempVec1.x = Q_Bullet->Bullet[_->NomBullet].TrajVec.z;
										TempVec1.y = 0.0f;
										TempVec1.z = 0.0f;
									}
								}
							else Qpo->Vec3d_CrossProduct(&qAxis[major], &Q_Bullet->Bullet[_->NomBullet].TrajVec, &TempVec1);

							Qpo->Vec3d_Normalize(&TempVec1);
							Qpo->Vec3d_CrossProduct(&Q_Bullet->Bullet[_->NomBullet].TrajVec, &TempVec1, &TempVec2);
							Qpo->Vec3d_Normalize(&TempVec2);
							
							Qpo->Vec3d_Inverse(&TempVec1);

							Qpo->Transform_New(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix);
							Qpo->Transform_New_LeftUpIn(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &TempVec1, &TempVec2, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
							Qpo->Transform_Orthonormalize(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

							Qpo->Transform_New_YRotation(&rotmat, PI);
							Qpo->Transform_Multiply(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &rotmat, &Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

							Q_Bullet->Bullet[_->NomBullet].AvID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID;

							//Spin
							Q_Bullet->Bullet[_->NomBullet].Xrot = 0;
							Q_Bullet->Bullet[_->NomBullet].Yrot = 0;
							Q_Bullet->Bullet[_->NomBullet].Zrot = 0;

							Q_Bullet->Bullet[_->NomBullet].BulletDMG = ((float)Q_BMSentry->BMSentry[Count].Damage / 5000) * 65;
							Q_Bullet->Bullet[_->NomBullet].BulletPWR = ((float)Q_BMSentry->BMSentry[Count].Power / 5000) * 65;

							Q_Bullet->Bullet[_->NomBullet].JDamageLVL = 0;

							Q_Bullet->Bullet[_->NomBullet].ZSpin = ((float)rand() / 32767)/3;

							Q_Bullet->Bullet[_->NomBullet].Gravity = 0.0001;

							Q_Bullet->Bullet[_->NomBullet].Scale = 0.5;
							Q_Bullet->Bullet[_->NomBullet].Speed = 250;

							Q_Bullet->Bullet[_->NomBullet].Live = 1;

							Q_Bullet->Bullet[_->NomBullet].NetFlag = 0;

							_->NomBullet++;

							//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BMSentry->BMSentry[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
							//'FIRE' SOUND

							Qpo->Sound_Play(Medias->S_RifleFire[7], _->Volume, _->Pan, _->S_TimeScale, false, &Q_BMSentry->BMSentry[Count].Pos);
							
							SCRAMJET++;
							}
						}
					}

				jet++;
				}
			}
		else
			{
			TESTPosS = playerAV[g_Player]->Xform.Translation;
			TESTPosS.y += 60;
			TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_BMSentry->BMSentry[Count].Pos);

			if((TESTShieldDIST < (Q_BMSentry->BMSentry[Count].Range * 8)) && player[g_Player]->HB_Dead == 0)
				{
				if(Q_BMSentry->BMSentry[Count].FireRateCNT[250] >= (1 - ((float)Q_BMSentry->BMSentry[Count].FireRate / 5000)) * 36) Q_BMSentry->BMSentry[Count].FireRateCNT[250] = 0;
				else if(Q_BMSentry->BMSentry[Count].FireRateCNT[250] > 0) Q_BMSentry->BMSentry[Count].FireRateCNT[250] += 1 * _->TimeScale;

				if(Q_BMSentry->BMSentry[Count].FireRateCNT[250] == 0)	//FIRE!
					{
					Q_BMSentry->BMSentry[Count].FireRateCNT[250] = 1;

					SCRAMJET = 0;
					while((SCRAMJET < Q_BMSentry->BMSentry[Count].BulletCNT) && (_->NomBullet < 14999))	//V-- Maximum bullet restriction
						{
						//Trajectory
						Q_Bullet->Bullet[_->NomBullet].WorldPos = Q_BMSentry->BMSentry[Count].Pos;
						Q_Bullet->Bullet[_->NomBullet].ORIGPos = Q_BMSentry->BMSentry[Count].Pos;
						Qpo->Vec3d_Subtract(&TESTPosS, &Q_BMSentry->BMSentry[Count].Pos, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
						Qpo->Vec3d_Normalize(&Q_Bullet->Bullet[_->NomBullet].TrajVec);
						Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[_->NomBullet].WorldPos, 4.5, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &Q_Bullet->Bullet[_->NomBullet].WorldPos);

						Q_Bullet->Bullet[_->NomBullet].TrajVec.x += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].CharDATA.WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);
						Q_Bullet->Bullet[_->NomBullet].TrajVec.y += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].CharDATA.WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);
						Q_Bullet->Bullet[_->NomBullet].TrajVec.z += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].CharDATA.WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);

						if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x))
							{
							major = 1;
							if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y))
								major = 2;
							}
						else
							{
							if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x))
								major = 2;
							}
						
						if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x)==1.0f || fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y)==1.0f || fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z)==1.0f)
							{
							if ((major == 0 && Q_Bullet->Bullet[_->NomBullet].TrajVec.x > 0) || major == 1)
								{
									TempVec1.x = 0.0f;
									TempVec1.y = 0.0f;
									TempVec1.z = -1.0f;
								}
							else if (major == 0)
								{
									TempVec1.x = 0.0f;
									TempVec1.y = 0.0f;
									TempVec1.z = 1.0f;
								}
							else 
								{
									TempVec1.x = Q_Bullet->Bullet[_->NomBullet].TrajVec.z;
									TempVec1.y = 0.0f;
									TempVec1.z = 0.0f;
								}
							}
						else Qpo->Vec3d_CrossProduct(&qAxis[major], &Q_Bullet->Bullet[_->NomBullet].TrajVec, &TempVec1);

						Qpo->Vec3d_CrossProduct(&Q_Bullet->Bullet[_->NomBullet].TrajVec, &TempVec1, &TempVec2);
						Qpo->Vec3d_Normalize(&TempVec2);
						Qpo->Vec3d_Normalize(&TempVec1);
						Qpo->Vec3d_Inverse(&TempVec1);

						Qpo->Transform_New(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix);
						Qpo->Transform_New_LeftUpIn(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &TempVec1, &TempVec2, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
						Qpo->Transform_Orthonormalize(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

						Qpo->Transform_New_YRotation(&rotmat, PI);
						Qpo->Transform_Multiply(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &rotmat, &Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

						Q_Bullet->Bullet[_->NomBullet].AvID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID;

						//Spin
						Q_Bullet->Bullet[_->NomBullet].Xrot = 0;
						Q_Bullet->Bullet[_->NomBullet].Yrot = 0;
						Q_Bullet->Bullet[_->NomBullet].Zrot = 0;

						Q_Bullet->Bullet[_->NomBullet].BulletDMG = ((float)Q_BMSentry->BMSentry[Count].Damage / 5000) * 65;
						Q_Bullet->Bullet[_->NomBullet].BulletPWR = ((float)Q_BMSentry->BMSentry[Count].Power / 5000) * 65;

						Q_Bullet->Bullet[_->NomBullet].JDamageLVL = 0;

						Q_Bullet->Bullet[_->NomBullet].ZSpin = ((float)rand() / 32767)/3;

						Q_Bullet->Bullet[_->NomBullet].Gravity = 0.0001;

						Q_Bullet->Bullet[_->NomBullet].Scale = 0.5;
						Q_Bullet->Bullet[_->NomBullet].Speed = 250;

						Q_Bullet->Bullet[_->NomBullet].Live = 1;

						Q_Bullet->Bullet[_->NomBullet].NetFlag = 0;

						_->NomBullet++;

						//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BMSentry->BMSentry[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
							//'FIRE' SOUND

						Qpo->Sound_Play(Medias->S_RifleFire[7], _->Volume, _->Pan, _->S_TimeScale, false, &Q_BMSentry->BMSentry[Count].Pos);
						
						SCRAMJET++;
						}
					}
				}

			jet=0;  //##### Player Check (AvID respective) for in range
			while(jet < _->NomAI)
				{
				if(jet != Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID && Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].Team != Q_Forge->Forge[jet].Team)
					{
					TESTPosS = Q_Forge->Forge[jet].AV.Xform.Translation;
					TESTPosS.y += 60;
					TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_BMSentry->BMSentry[Count].Pos);

					if((TESTShieldDIST < (Q_BMSentry->BMSentry[Count].Range * 8)) && Q_Forge->Forge[jet].HB_Dead == 0)
						{
						if(Q_BMSentry->BMSentry[Count].FireRateCNT[jet] >= (1 - ((float)Q_BMSentry->BMSentry[Count].FireRate / 5000)) * 36) Q_BMSentry->BMSentry[Count].FireRateCNT[jet] = 0;
						else if(Q_BMSentry->BMSentry[Count].FireRateCNT[jet] > 0) Q_BMSentry->BMSentry[Count].FireRateCNT[jet] += 1 * _->TimeScale;

						if(Q_BMSentry->BMSentry[Count].FireRateCNT[jet] == 0)	//FIRE!
							{
							Q_BMSentry->BMSentry[Count].FireRateCNT[jet] = 1;

							SCRAMJET = 0;
							while((SCRAMJET < Q_BMSentry->BMSentry[Count].BulletCNT) && (_->NomBullet < 14999))	//V-- Maximum bullet restriction
								{
								//Trajectory
								Q_Bullet->Bullet[_->NomBullet].WorldPos = Q_BMSentry->BMSentry[Count].Pos;
								Q_Bullet->Bullet[_->NomBullet].ORIGPos = Q_BMSentry->BMSentry[Count].Pos;
								Qpo->Vec3d_Subtract(&TESTPosS, &Q_BMSentry->BMSentry[Count].Pos, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
								Qpo->Vec3d_Normalize(&Q_Bullet->Bullet[_->NomBullet].TrajVec);
								Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[_->NomBullet].WorldPos, 4.5, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &Q_Bullet->Bullet[_->NomBullet].WorldPos);

								Q_Bullet->Bullet[_->NomBullet].TrajVec.x += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].CharDATA.WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);
								Q_Bullet->Bullet[_->NomBullet].TrajVec.y += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].CharDATA.WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);
								Q_Bullet->Bullet[_->NomBullet].TrajVec.z += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID].CharDATA.WeaponSKILL.Accuracy/5000)*500))*(((5000 - Q_BMSentry->BMSentry[Count].Accuracy) / 5000) * 3);

								if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x))
									{
									major = 1;
									if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y))
										major = 2;
									}
								else
									{
									if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z) > fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x))
										major = 2;
									}
								
								if(fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.x)==1.0f || fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.y)==1.0f || fab(Q_Bullet->Bullet[_->NomBullet].TrajVec.z)==1.0f)
									{
									if ((major == 0 && Q_Bullet->Bullet[_->NomBullet].TrajVec.x > 0) || major == 1)
										{
											TempVec1.x = 0.0f;
											TempVec1.y = 0.0f;
											TempVec1.z = -1.0f;
										}
									else if (major == 0)
										{
											TempVec1.x = 0.0f;
											TempVec1.y = 0.0f;
											TempVec1.z = 1.0f;
										}
									else 
										{
											TempVec1.x = Q_Bullet->Bullet[_->NomBullet].TrajVec.z;
											TempVec1.y = 0.0f;
											TempVec1.z = 0.0f;
										}
									}
								else Qpo->Vec3d_CrossProduct(&qAxis[major], &Q_Bullet->Bullet[_->NomBullet].TrajVec, &TempVec1);

								Qpo->Vec3d_CrossProduct(&Q_Bullet->Bullet[_->NomBullet].TrajVec, &TempVec1, &TempVec2);
								Qpo->Vec3d_Normalize(&TempVec2);
								Qpo->Vec3d_Normalize(&TempVec1);
								Qpo->Vec3d_Inverse(&TempVec1);

								Qpo->Transform_New(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix);
								Qpo->Transform_New_LeftUpIn(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &TempVec1, &TempVec2, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
								Qpo->Transform_Orthonormalize(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

								Qpo->Transform_New_YRotation(&rotmat, PI);
								Qpo->Transform_Multiply(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &rotmat, &Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

								Q_Bullet->Bullet[_->NomBullet].AvID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_BMSentry->BMSentry[Count].ZoneID].AVID;

								//Spin
								Q_Bullet->Bullet[_->NomBullet].Xrot = 0;
								Q_Bullet->Bullet[_->NomBullet].Yrot = 0;
								Q_Bullet->Bullet[_->NomBullet].Zrot = 0;

								Q_Bullet->Bullet[_->NomBullet].BulletDMG = ((float)Q_BMSentry->BMSentry[Count].Damage / 5000) * 65;
								Q_Bullet->Bullet[_->NomBullet].BulletPWR = ((float)Q_BMSentry->BMSentry[Count].Power / 5000) * 65;

								Q_Bullet->Bullet[_->NomBullet].JDamageLVL = 0;

								Q_Bullet->Bullet[_->NomBullet].ZSpin = ((float)rand() / 32767)/3;

								Q_Bullet->Bullet[_->NomBullet].Gravity = 0.0001;

								Q_Bullet->Bullet[_->NomBullet].Scale = 0.5;
								Q_Bullet->Bullet[_->NomBullet].Speed = 250;

								Q_Bullet->Bullet[_->NomBullet].Live = 1;

								Q_Bullet->Bullet[_->NomBullet].NetFlag = 0;

								_->NomBullet++;

								//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_BMSentry->BMSentry[Count].Pos, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
								//'FIRE' SOUND

								Qpo->Sound_Play(Medias->S_RifleFire[7], _->Volume, _->Pan, _->S_TimeScale, false, &Q_BMSentry->BMSentry[Count].Pos);

								SCRAMJET++;
								}
							}
						}
					}

				jet++;
				}
			}
		}

	//###-- Immunity Counter - The sentries come packaged for release immediatly, they are invincible for 1000 ticks
	Q_BMSentry->BMSentry[Count].ImmCNT--;
	if(Q_BMSentry->BMSentry[Count].ImmCNT < 0) Q_BMSentry->BMSentry[Count].ImmCNT = 0;

	//##### HANDLE OBJECT DESTRUCTION **************************************************
	if(Q_Object->Object[Q_BMSentry->BMSentry[Count].QObjID].StrengthBANK <= 0 && Q_BMSentry->BMSentry[Count].ImmCNT == 0)
		{
		Q_BMSentry->BMSentry[Count].LIVE = 0;
		}
	}

};