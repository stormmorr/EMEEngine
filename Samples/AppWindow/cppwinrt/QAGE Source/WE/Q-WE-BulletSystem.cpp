/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Bullet System-

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
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-WE-BulletSystem.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-WE-PntSprite.h"
#include "Q-WE-MeleeHits.h"

using namespace GVARS;

namespace GVARS
{

bool Q_EFFCon::Bullet_ServerFrame(int Count)
	{
	//Apply Gravity
	Q_Bullet->Bullet[Count].TrajVec.y -= Q_Bullet->Bullet[Count].Gravity*_->TimeScale;
	
	//Move
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].WorldPos, Q_Bullet->Bullet[Count].Speed*_->TimeScale, &Q_Bullet->Bullet[Count].TrajVec, &Q_Bullet->Bullet[Count].NewPos);

	//######===-- Q_Object->Object COLLISION DETECTION --===#######
	SCRAM=0;
	while(SCRAM < _->NomQObject)
		{
		if(Q_Object->Object[SCRAM].LIVE == 1 && Q_Object->Object[SCRAM].AvID != Q_Bullet->Bullet[Count].AvID)
			{
			//### COLLISION CHECK
			if(Q_Object->Object[SCRAM].StrengthBANK > 0)
				{
				switch(Q_Object->Object[SCRAM].CollisionTYPE)
					{
					case 0:
						{
						TESTDist = 100;
						TESTPosS = Q_Bullet->Bullet[Count].WorldPos;
						TESTPosE = Q_Bullet->Bullet[Count].NewPos;
						while(TESTDist > 1)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 1, &Q_Bullet->Bullet[Count].TrajVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Object->Object[SCRAM].Pos);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < Q_Object->Object[SCRAM].Scale)
								{
								//Set Player Enemy Display to correct enemy
								if(Q_Bullet->Bullet[Count].AvID == 250)
									{
									player[g_Player]->HB_LastAvatarHitID = (SCRAM + 1) * -1;
									}
								else
									{
									Q_Forge->Forge[Q_Bullet->Bullet[Count].AvID].HB_LastAvatarHitID = (SCRAM + 1) * -1;
									}

								//### Block Hit Flash
								Q_MeleeHit->MeleeHit[_->NomMelHit].Live = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].INIT = 0;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitTYPE = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].HitRESULT = 9;
																	//VVVVVV-----?? Change this 'impact point' to Bone hit translation maybe ??
								Q_MeleeHit->MeleeHit[_->NomMelHit].Impact = TESTPosS;	//Point of impact in world space
								Q_MeleeHit->MeleeHit[_->NomMelHit].Bonenum = detcnt;						//Number index of the bone hit
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF = Q_Bullet->Bullet[Count].AlignMatrix;

								Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Translation = Origin;
								Qpo->Transform_New_YRotation(&rotmat, (PI/2));
								Qpo->Transform_Multiply(&Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF, &rotmat, &Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF);
								Q_MeleeHit->MeleeHit[_->NomMelHit].AttboneXF.Translation = Q_Bullet->Bullet[Count].AlignMatrix.Translation;

								Q_MeleeHit->MeleeHit[_->NomMelHit].HitPowerPercent = 1;
								Q_MeleeHit->MeleeHit[_->NomMelHit].BloodAmt = 0;
								
								//Expandro3D Struct
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Radius = 60;					//Switch 0 = Off !0 = On
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.MaxRadius = 500 * (Q_Bullet->Bullet[Count].BulletDMG / 5);				//Max Radius
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.StartFade = 5;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Red = 255;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Blue = 60;
								Q_MeleeHit->MeleeHit[_->NomMelHit].Expandro3D.Green = 60;

									//Increment number of MeleeHits
								_->NomMelHit += 1;

								/*Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
								Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
								Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 0;

								Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
								Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
								Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
								Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
								Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].Collision.Plane.Normal;
								Q_BulletHit->BulletHit[_->NomBulHit].Pos = Q_Bullet->Bullet[Count].Collision.Impact;

								_->NomBulHit++;
								if(_->NomBulHit > 499) _->NomBulHit = 0;*/

								Q_Object->Object[SCRAM].StrengthBANK -= (Q_Bullet->Bullet[Count].BulletDMG / 10);

								TESTPosS = TESTPosE;
								TESTDist = 0;
								}
							}

						}break;
					}
				}
			}

		SCRAM++;
		}


	//##### PLAYER SHIELD COLLIDE TEST
	if((player[g_Player]->Cleric.ShieldAlpha > 0) && (Q_Bullet->Bullet[Count].AvID != 250) && (Q_Bullet->Bullet[Count].Live == 1))
		{
		if(Q_Forge->Forge[Q_Bullet->Bullet[Count].AvID].Team != player[g_Player]->Team)
			{
			TESTDist = 100;
			TESTPosS = Q_Bullet->Bullet[Count].WorldPos;
			TESTPosE = Q_Bullet->Bullet[Count].NewPos;
			while(TESTDist > 10.5)
				{
				Qpo->Vec3d_AddScaled(&TESTPosS, 10, &Q_Bullet->Bullet[Count].TrajVec, &TESTPosS);

				TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &player[g_Player]->Shield.Xform.Translation);

				TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

				if(TESTShieldDIST < (65 * player[g_Player]->Cleric.ShieldScale))
					{
					if(player[g_Player]->HB_Energy > 0)
						{
						//## Set the new pos to the point of collision
						Q_Bullet->Bullet[Count].NewPos = TESTPosS;
						TESTPosS = TESTPosE;
						TESTDist = 0;
						Q_Bullet->Bullet[Count].Live = 0;

						player[g_Player]->HB_Energy -= (Q_Bullet->Bullet[Count].BulletDMG / 5) / (10 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[7].Duration/5000));

						if(_->NomBulHit >= 499 || _->NomBulHit < 0) _->NomBulHit = 0;
						Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
						Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
						Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 100;
						Q_BulletHit->BulletHit[_->NomBulHit].JDamageLVL = Q_Bullet->Bullet[Count].JDamageLVL;
						Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
						Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
						Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
						Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
						Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].TrajVec;
						Qpo->Vec3d_Inverse(&Q_BulletHit->BulletHit[_->NomBulHit].CollNormal);
						Q_BulletHit->BulletHit[_->NomBulHit].Pos = TESTPosS;

						_->NomBulHit++;
						
						/*//+---=VAPOR TRAIL=---+
						if(Q_Bullet->Bullet[Count].JDamageLVL == 3)
							{
							Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

							//### Array Reorder
							K = Q_Bullet->Bullet[Count].VaporID1;
							while(K < _->NomVaporTrails - 1)
								{
								Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
								K++;
								}

							_->NomVaporTrails--;
							}

						if(Q_Bullet->Bullet[Count].Scale > 5)
							{
							Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

							//### Array Reorder
							K = Q_Bullet->Bullet[Count].VaporID1;
							while(K < _->NomVaporTrails - 1)
								{
								Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
								K++;
								}

							_->NomVaporTrails--;

							Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID2].Live = 0;

							//### Array Reorder
							K = Q_Bullet->Bullet[Count].VaporID2;
							while(K < _->NomVaporTrails - 1)
								{
								Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
								K++;
								}

							_->NomVaporTrails--;

							Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID3].Live = 0;

							//### Array Reorder
							K = Q_Bullet->Bullet[Count].VaporID3;
							while(K < _->NomVaporTrails - 1)
								{
								Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
								K++;
								}

							_->NomVaporTrails--;
							}*/

#if 1
						if(g_optionsresult == 2 || g_optionsresult == 3)
							{						//### Array Reorder
							int K = Count;
							while(K < 499 && K < _->NomBullet - 1)
								{
								Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
								K++;
								}

							_->NomBullet--;
							}
						else
							{
							int K = Count;
							while(K < _->NomBullet - 1)
								{
								Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
								K++;
								}

							_->NomBullet--;
							}
#endif
						}
					}
				}
			}
		}

	//##### AVATAR SHIELD COLLIDE TEST
	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].Cleric.ShieldAlpha > 0 && (Q_Bullet->Bullet[Count].Live == 1))
				{
				if(Q_Bullet->Bullet[Count].AvID == 250)
					{
					if(player[g_Player]->Team != Q_Forge->Forge[SCRAM].Team)
						{
						TESTDist = 100;
						TESTPosS = Q_Bullet->Bullet[Count].WorldPos;
						TESTPosE = Q_Bullet->Bullet[Count].NewPos;
						while(TESTDist > 10.5)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 10, &Q_Bullet->Bullet[Count].TrajVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
								{
								if(Q_Forge->Forge[SCRAM].HB_Energy > 0)
									{
									//## Set the new pos to the point of collision
									Q_Bullet->Bullet[Count].NewPos = TESTPosS;
									TESTPosS = TESTPosE;
									TESTDist = 0;
									Q_Bullet->Bullet[Count].Live = 0;

									Q_Forge->Forge[SCRAM].HB_Energy -= (Q_Bullet->Bullet[Count].BulletDMG / 5) / (10 * (Q_Forge->Forge[SCRAM].CharDATA.CLSClericSKILL[7].Duration/5000));

									if(_->NomBulHit >= 499 || _->NomBulHit < 0) _->NomBulHit = 0;
									Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
									Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
									Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 100;
									Q_BulletHit->BulletHit[_->NomBulHit].JDamageLVL = Q_Bullet->Bullet[Count].JDamageLVL;
									Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
									Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
									Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
									Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
									Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].TrajVec;
									Qpo->Vec3d_Inverse(&Q_BulletHit->BulletHit[_->NomBulHit].CollNormal);
									Q_BulletHit->BulletHit[_->NomBulHit].Pos = TESTPosS;

									_->NomBulHit++;
									
									/*//+---=VAPOR TRAIL=---+
									if(Q_Bullet->Bullet[Count].JDamageLVL == 3)
										{
										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID1;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;
										}

									if(Q_Bullet->Bullet[Count].Scale > 5)
										{
										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID1;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;

										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID2].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID2;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;

										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID3].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID3;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;
										}*/

#if 1
									if(g_optionsresult == 2 || g_optionsresult == 3)
										{						//### Array Reorder
										int K = Count;
										while(K < 499 && K < _->NomBullet - 1)
											{
											Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
											K++;
											}

										_->NomBullet--;
										}
									else
										{
										int K = Count;
										while(K < _->NomBullet - 1)
											{
											Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
											K++;
											}

										_->NomBullet--;
										}
#endif
									}
								}
							}
						}
					}
				else
					{
					if(Q_Forge->Forge[Q_Bullet->Bullet[Count].AvID].Team != Q_Forge->Forge[SCRAM].Team)
						{
						TESTDist = 100;
						TESTPosS = Q_Bullet->Bullet[Count].WorldPos;
						TESTPosE = Q_Bullet->Bullet[Count].NewPos;
						while(TESTDist > 10.5)
							{
							Qpo->Vec3d_AddScaled(&TESTPosS, 10, &Q_Bullet->Bullet[Count].TrajVec, &TESTPosS);

							TESTShieldDIST = Qpo->Vec3d_DistanceBetween(&TESTPosS, &Q_Forge->Forge[SCRAM].Shield.Xform.Translation);

							TESTDist = Qpo->Vec3d_DistanceBetween(&TESTPosS, &TESTPosE);

							if(TESTShieldDIST < (65 * Q_Forge->Forge[SCRAM].Cleric.ShieldScale))
								{
								if(Q_Forge->Forge[SCRAM].HB_Energy > 0)
									{
									//## Set the new pos to the point of collision
									Q_Bullet->Bullet[Count].NewPos = TESTPosS;
									TESTPosS = TESTPosE;
									TESTDist = 0;
									Q_Bullet->Bullet[Count].Live = 0;

									Q_Forge->Forge[SCRAM].HB_Energy -= Q_Bullet->Bullet[Count].BulletDMG / 5;

									if(_->NomBulHit >= 499 || _->NomBulHit < 0) _->NomBulHit = 0;
									Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
									Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
									Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 100;
									Q_BulletHit->BulletHit[_->NomBulHit].JDamageLVL = Q_Bullet->Bullet[Count].JDamageLVL;
									Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
									Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
									Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
									Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
									Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].TrajVec;
									Qpo->Vec3d_Inverse(&Q_BulletHit->BulletHit[_->NomBulHit].CollNormal);
									Q_BulletHit->BulletHit[_->NomBulHit].Pos = TESTPosS;

									_->NomBulHit++;
									
									//+---=VAPOR TRAIL=---+
									/*if(Q_Bullet->Bullet[Count].JDamageLVL == 3)
										{
										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID1;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;
										}

									if(Q_Bullet->Bullet[Count].Scale > 5)
										{
										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID1;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;

										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID2].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID2;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;

										Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID3].Live = 0;

										//### Array Reorder
										K = Q_Bullet->Bullet[Count].VaporID3;
										while(K < _->NomVaporTrails - 1)
											{
											Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
											K++;
											}

										_->NomVaporTrails--;
										}*/

#if 1
									if(g_optionsresult == 2 || g_optionsresult == 3)
										{						//### Array Reorder
										int K = Count;
										while(K < 499 && K < _->NomBullet - 1)
											{
											Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
											K++;
											}

										_->NomBullet--;
										}
									else
										{
										int K = Count;
										while(K < _->NomBullet - 1)
											{
											Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
											K++;
											}

										_->NomBullet--;
										}
#endif
									}
								}
							}
						}
					}
				}
			}
		SCRAM++;
		}

	if(Qpo->Collision_RayTest_Avatar(
		&playerAV[g_Player]->Mins,
		&playerAV[g_Player]->Maxs,
		 &Q_Bullet->Bullet[Count].WorldPos,
		 &Q_Bullet->Bullet[Count].NewPos,
		 0xffffffff, NULL, NULL,
		 &Q_Bullet->Bullet[Count].Collision, Q_Bullet->Bullet[Count].AvID) && (Q_Bullet->Bullet[Count].Live == 1))
		{
		//###-- Avatar Collide Test --###
		/*Q_Bullet->Bullet[Count].Collision.m_HitAvatar = false;
		if(!(((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Mins.x) > (Q_Bullet->Bullet[Count].Collision.Impact.m_X + 25)) || ((playerAV[g_Player]->Xform.Translation.x + playerAV[g_Player]->Maxs.x) < (Q_Bullet->Bullet[Count].Collision.Impact.m_X - 25))) &&
		!(((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Mins.y) > (Q_Bullet->Bullet[Count].Collision.Impact.m_Y + 25)) || ((playerAV[g_Player]->Xform.Translation.y + playerAV[g_Player]->Maxs.y) < (Q_Bullet->Bullet[Count].Collision.Impact.m_Y - 25))) &&
		!(((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Mins.z) > (Q_Bullet->Bullet[Count].Collision.Impact.m_Z + 25)) || ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Maxs.z) < (Q_Bullet->Bullet[Count].Collision.Impact.m_Z - 25))))
			{
			Q_Bullet->Bullet[Count].Collision.m_AvatarID = -1;
			Q_Bullet->Bullet[Count].Collision.Avatar.IDflag = -1;
			Q_Bullet->Bullet[Count].Collision.m_HitAvatar = true;
			}

		SCRAM=0;
		while(SCRAM < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAM].LIVE == 1)
				{
				if(!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Mins.x) > (Q_Bullet->Bullet[Count].Collision.Impact.m_X + 25)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.x + Q_Forge->Forge[SCRAM].AV.Maxs.x) < (Q_Bullet->Bullet[Count].Collision.Impact.m_X - 25))) &&
				!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Mins.y) > (Q_Bullet->Bullet[Count].Collision.Impact.m_Y + 25)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.y + Q_Forge->Forge[SCRAM].AV.Maxs.y) < (Q_Bullet->Bullet[Count].Collision.Impact.m_Y - 25))) &&
				!(((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Mins.z) > (Q_Bullet->Bullet[Count].Collision.Impact.m_Z + 25)) || ((Q_Forge->Forge[SCRAM].AV.Xform.Translation.z + Q_Forge->Forge[SCRAM].AV.Maxs.z) < (Q_Bullet->Bullet[Count].Collision.Impact.m_Z - 25))))
					{
					Q_Bullet->Bullet[Count].Collision.m_AvatarID = SCRAM;
					Q_Bullet->Bullet[Count].Collision.Avatar.IDflag = SCRAM;
					Q_Bullet->Bullet[Count].Collision.m_HitAvatar = true;
					}
				}
			SCRAM++;
			}*/

		if(Q_Bullet->Bullet[Count].Collision.m_HitAvatar)
			{
			if(Q_Bullet->Bullet[Count].Collision.m_AvatarID == -1)	//# Player Hit
				{
				//## Hit Reactions
				if(player[g_Player]->Aposestate != 30 && player[g_Player]->HB_RecoverMode < 2 && player[g_Player]->HB_Dead == 0)
					{
					//### Set Actor hit index
					Q_BulletHit->BulletHit[_->NomBulHit].AvatarHITID = 250;

					//## Set the new pos to the point of collision
					Q_Bullet->Bullet[Count].NewPos.acSet(Q_Bullet->Bullet[Count].Collision.Impact.m_X, Q_Bullet->Bullet[Count].Collision.Impact.m_Y, Q_Bullet->Bullet[Count].Collision.Impact.m_Z);
					Q_Bullet->Bullet[Count].Live = 0;

					if(Q_Bullet->Bullet[Count].NewPos.y > (playerAV[g_Player]->Xform.Translation.y + 35))	//82 Head
						{
						Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 3;
						}
					else
						{
						if(Q_Bullet->Bullet[Count].NewPos.y > (playerAV[g_Player]->Xform.Translation.y + 17))	//69 //Torso / legs
							{
							Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 2;
							}
						else
							{
							Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 1;
							}
						}

					if(_->NomBulHit >= 499 || _->NomBulHit < 0) _->NomBulHit = 0;
					Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
					Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
					Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
					Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
					Q_BulletHit->BulletHit[_->NomBulHit].JDamageLVL = Q_Bullet->Bullet[Count].JDamageLVL;
					Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
					Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
					Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].Collision.Plane.Normal;
					Q_BulletHit->BulletHit[_->NomBulHit].Pos.acSet(Q_Bullet->Bullet[Count].Collision.Impact.m_X, Q_Bullet->Bullet[Count].Collision.Impact.m_Y, Q_Bullet->Bullet[Count].Collision.Impact.m_Z);

					_->NomBulHit++;
					
					//+---=VAPOR TRAIL=---+
					/*if(Q_Bullet->Bullet[Count].JDamageLVL == 3)
						{
						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID1;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;
						}

					if(Q_Bullet->Bullet[Count].Scale > 5)
						{
						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID1;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;

						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID2].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID2;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;

						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID3].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID3;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;
						}*/

#if 1
					if(g_optionsresult == 2 || g_optionsresult == 3)
						{						//### Array Reorder
						int K = Count;
						while(K < 499 && K < _->NomBullet - 1)
							{
							Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
							K++;
							}

						_->NomBullet--;
						}
					else
						{
						int K = Count;
						while(K < _->NomBullet - 1)
							{
							Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
							K++;
							}

						_->NomBullet--;
						}
#endif

					return false;
					}
				}
			else
				{
				//## Hit Reactions
				if(Q_Forge->Forge[Q_Bullet->Bullet[Count].Collision.Avatar.IDflag].Aposestate != 30 && Q_Forge->Forge[Q_Bullet->Bullet[Count].Collision.Avatar.IDflag].HB_RecoverMode < 2 && Q_Forge->Forge[Q_Bullet->Bullet[Count].Collision.Avatar.IDflag].HB_Dead == 0)
					{
					//### Set Actor hit index
					Q_BulletHit->BulletHit[_->NomBulHit].AvatarHITID = Q_Bullet->Bullet[Count].Collision.Avatar.IDflag;

					// Set the new pos to the point of collision
					Q_Bullet->Bullet[Count].NewPos.acSet(Q_Bullet->Bullet[Count].Collision.Impact.m_X, Q_Bullet->Bullet[Count].Collision.Impact.m_Y, Q_Bullet->Bullet[Count].Collision.Impact.m_Z);
					Q_Bullet->Bullet[Count].Live = 0;

					if(Q_Bullet->Bullet[Count].NewPos.y > (Q_Forge->Forge[Q_Bullet->Bullet[Count].Collision.Avatar.IDflag].AV.Xform.Translation.y + 35))	//82 //Head
						{
						Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 3;
						}
					else
						{
						if(Q_Bullet->Bullet[Count].NewPos.y > (Q_Forge->Forge[Q_Bullet->Bullet[Count].Collision.Avatar.IDflag].AV.Xform.Translation.y + 17))	//40 //Head
							{
							Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 2;
							}
						else
							{
							Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 1;
							}
						}

					if(_->NomBulHit >= 499 || _->NomBulHit < 0) _->NomBulHit = 0;
					Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
					Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
					Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 1;
					Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
					Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
					Q_BulletHit->BulletHit[_->NomBulHit].JDamageLVL = Q_Bullet->Bullet[Count].JDamageLVL;
					Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
					Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
					Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].Collision.Plane.Normal;
					Q_BulletHit->BulletHit[_->NomBulHit].Pos.acSet(Q_Bullet->Bullet[Count].Collision.Impact.m_X, Q_Bullet->Bullet[Count].Collision.Impact.m_Y, Q_Bullet->Bullet[Count].Collision.Impact.m_Z);

					_->NomBulHit++;
					
					//+---=VAPOR TRAIL=---+
					/*if(Q_Bullet->Bullet[Count].JDamageLVL == 3)
						{
						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID1;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;
						}

					if(Q_Bullet->Bullet[Count].Scale > 5)
						{
						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID1;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;

						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID2].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID2;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;

						Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID3].Live = 0;

						//### Array Reorder
						K = Q_Bullet->Bullet[Count].VaporID3;
						while(K < _->NomVaporTrails - 1)
							{
							Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
							K++;
							}

						_->NomVaporTrails--;
						}*/

#if 1
					if(g_optionsresult == 2 || g_optionsresult == 3)
						{						//### Array Reorder
						int K = Count;
						while(K < 499 && K < _->NomBullet - 1)
							{
							Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
							K++;
							}

						_->NomBullet--;
						}
					else
						{
						int K = Count;
						while(K < _->NomBullet - 1)
							{
							Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
							K++;
							}

						_->NomBullet--;
						}
#endif				
					return false;
					}
				}
			}
		else
			{
			//## Set the new pos to the point of collision
			Q_Bullet->Bullet[Count].NewPos.acSet(Q_Bullet->Bullet[Count].Collision.Impact.m_X, Q_Bullet->Bullet[Count].Collision.Impact.m_Y, Q_Bullet->Bullet[Count].Collision.Impact.m_Z);
			Q_Bullet->Bullet[Count].Live = 0;

			if(_->NomBulHit >= 499 || _->NomBulHit < 0) _->NomBulHit = 0;
			Q_BulletHit->BulletHit[_->NomBulHit].Live = 1;
			Q_BulletHit->BulletHit[_->NomBulHit].Init = 0;
			Q_BulletHit->BulletHit[_->NomBulHit].EffectType = 0;
			Q_BulletHit->BulletHit[_->NomBulHit].JDamageLVL = Q_Bullet->Bullet[Count].JDamageLVL;
			Q_BulletHit->BulletHit[_->NomBulHit].BulletDMG = Q_Bullet->Bullet[Count].BulletDMG;
			Q_BulletHit->BulletHit[_->NomBulHit].BulletPWR = Q_Bullet->Bullet[Count].BulletPWR;
			Q_BulletHit->BulletHit[_->NomBulHit].AvID = Q_Bullet->Bullet[Count].AvID;
			Q_BulletHit->BulletHit[_->NomBulHit].BulletTraj = Q_Bullet->Bullet[Count].TrajVec;
			Q_BulletHit->BulletHit[_->NomBulHit].CollNormal = Q_Bullet->Bullet[Count].Collision.Plane.Normal;
			Q_BulletHit->BulletHit[_->NomBulHit].Pos.acSet(Q_Bullet->Bullet[Count].Collision.Impact.m_X, Q_Bullet->Bullet[Count].Collision.Impact.m_Y, Q_Bullet->Bullet[Count].Collision.Impact.m_Z);

			_->NomBulHit++;
			
			//+---=VAPOR TRAIL=---+
			/*if(Q_Bullet->Bullet[Count].JDamageLVL == 3)
				{
				Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

				//### Array Reorder
				K = Q_Bullet->Bullet[Count].VaporID1;
				while(K < _->NomVaporTrails - 1)
					{
					Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
					K++;
					}

				_->NomVaporTrails--;
				}

			if(Q_Bullet->Bullet[Count].Scale > 5)
				{
				Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].Live = 0;

				//### Array Reorder
				K = Q_Bullet->Bullet[Count].VaporID1;
				while(K < _->NomVaporTrails - 1)
					{
					Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
					K++;
					}

				_->NomVaporTrails--;

				Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID2].Live = 0;

				//### Array Reorder
				K = Q_Bullet->Bullet[Count].VaporID2;
				while(K < _->NomVaporTrails - 1)
					{
					Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
					K++;
					}

				_->NomVaporTrails--;

				Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID3].Live = 0;

				//### Array Reorder
				K = Q_Bullet->Bullet[Count].VaporID3;
				while(K < _->NomVaporTrails - 1)
					{
					Q_VaporTrail->VaporTrail[K] = Q_VaporTrail->VaporTrail[K+1];
					K++;
					}

				_->NomVaporTrails--;
				}*/

#if 1
			if(g_optionsresult == 2 || g_optionsresult == 3)
				{						//### Array Reorder
				int K = Count;
				while(K < 499 && K < _->NomBullet - 1)
					{
					Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
					K++;
					}

				_->NomBullet--;
				}
			else
				{
				int K = Count;
				while(K < _->NomBullet - 1)
					{
					Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
					K++;
					}

				_->NomBullet--;
				}
#endif
			return false;
			}
		}

	if(Q_Bullet->Bullet[Count].Live == 1)
		{
		//## Bullet Trails
		if(Q_Bullet->Bullet[Count].JDamageLVL == 0)
			{
			if(_->TimeScale > 0.25)
				{
				//## Bullet Trails
				if(Qpo->Vec3d_DistanceBetween(&Q_Bullet->Bullet[Count].NewPos, &Q_Bullet->Bullet[Count].ORIGPos) < Q_Bullet->Bullet[Count].Speed)
					{
					Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].ORIGPos;
					Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
					}
				else
					{
					Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].NewPos;
					Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
					Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].TrailEnd, -Q_Bullet->Bullet[Count].Speed, &Q_Bullet->Bullet[Count].TrajVec, &Q_Bullet->Bullet[Count].TrailStart);
					}

				if(Q_Bullet->Bullet[Count].Live == 0)
					{
					Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
					Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 0.55, Medias->BulletTrail, 30, 255, 255, 220, 0);
					}
				else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 0.55, Medias->BulletTrail, 70, 255, 255, 220, 0);
				}
			else
				{
				//Particle ejjector LVL02
				player[g_Player]->QAEFF_CNTR01[0] += 1;
				player[g_Player]->QAEFF_ROTAMT[0] = 0;

				TempVec1 = Q_Bullet->Bullet[Count].WorldPos;

				if(player[g_Player]->QAEFF_CNTR01[0] > 2)
					{
					player[g_Player]->QAEFF_CNTR01[0] = 0;

					jet=0;
					while((jet < 15) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.02f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 26;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.35;
						Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TempVec1;

						Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_Bullet->Bullet[Count].TrajVec;

							//Calculate Direction Vectors  previously Y
						Qpo->Transform_New_ZRotation(&RotateMatrix, PI/2);
						Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

						Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

						Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[0]);

						player[g_Player]->QAEFF_ROTAMT[0] += 0.42;

						Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);

						Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[helly].AvID;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					}
				}
			}
		else
			{
			//## Bullet Trails
			if(Qpo->Vec3d_DistanceBetween(&Q_Bullet->Bullet[Count].NewPos, &Q_Bullet->Bullet[Count].ORIGPos) < Q_Bullet->Bullet[Count].Speed)
				{
				Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].ORIGPos;
				Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
				}
			else
				{
				Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].NewPos;
				Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
				Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].TrailEnd, -Q_Bullet->Bullet[Count].Speed, &Q_Bullet->Bullet[Count].TrajVec, &Q_Bullet->Bullet[Count].TrailStart);
				}

			switch(Q_Bullet->Bullet[Count].JDamageLVL)
				{
				case 1:
					{
					if(Q_Bullet->Bullet[Count].Live == 0)
						{
						Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
						Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 3, Medias->QAEFF29, 30, 255, 255, 255, 0);
						}
					else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 3, Medias->QAEFF29, 90, 255, 255, 255, 0);

					//##### Render Main Sprite
					Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].WorldPos.x;
					Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].WorldPos.y;
					Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].WorldPos.z;
					Q_Bullet->Bullet[Count].Lvert[0][0].r = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].g = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].b = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].a = 90;

					Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 1, Medias->QAEFF28, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.2f);
					}break;

				case 2:
					{
					if(Q_Bullet->Bullet[Count].Live == 0)
						{
						Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
						Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 5, Medias->QAEFF29, 50, 255, 255, 255, 0);
						}
					else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 5, Medias->QAEFF29, 135, 255, 255, 255, 0);

					//##### Render Main Sprite
					Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].WorldPos.x;
					Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].WorldPos.y;
					Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].WorldPos.z;
					Q_Bullet->Bullet[Count].Lvert[0][0].r = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].g = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].b = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].a = 135;

					Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 1, Medias->QAEFF28, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.35f);
					}break;

				case 3:
					{
					if(Q_Bullet->Bullet[Count].Live == 0)
						{
						Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
						Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 10, Medias->QAEFF29, 100, 255, 255, 255, 0);
						}
					else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 10, Medias->QAEFF29, 200, 255, 255, 255, 0);

					//##### Render Main Sprite
					Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].WorldPos.x;
					Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].WorldPos.y;
					Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].WorldPos.z;
					Q_Bullet->Bullet[Count].Lvert[0][0].r = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].g = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].b = 255;
					Q_Bullet->Bullet[Count].Lvert[0][0].a = 200;

					Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 1, Medias->QAEFF28, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.5f);
					}break;
				}
			}


		Q_Bullet->Bullet[Count].WorldPos = Q_Bullet->Bullet[Count].NewPos;

		//Spin Bullet
		//Q_Bullet->Bullet[Count].Zrot += Q_Bullet->Bullet[Count].ZSpin*_->TimeScale;

		//Qpo->Transform_New_YRotation(&rotmat, Q_Bullet->Bullet[Count].Zrot);
		//Qpo->Transform_Multiply(&Q_Bullet->Bullet[Count].AlignMatrix, &rotmat, &Q_Bullet->Bullet[Count].AlignMatrix);

		Q_Bullet->Bullet[Count].AlignMatrix.Translation = Q_Bullet->Bullet[Count].WorldPos;

		Q_Bullet->Bullet[Count].Pos = Q_Bullet->Bullet[Count].AlignMatrix.Translation;

		Qpo->Transform_GetUp(&Q_Bullet->Bullet[Count].AlignMatrix, &Q_Bullet->Bullet[Count].VecUp);
		Qpo->Transform_GetLeft(&Q_Bullet->Bullet[Count].AlignMatrix, &Q_Bullet->Bullet[Count].VecLeft);
		Qpo->Transform_GetIn(&Q_Bullet->Bullet[Count].AlignMatrix, &Q_Bullet->Bullet[Count].VecIn);


		//##### Jink Damage single vapor
		if(Q_Bullet->Bullet[Count].JDamageLVL == 3 || Q_Bullet->Bullet[Count].BulletPWR > 45.5)
			{
			ColourSTART.red = 255;
			ColourSTART.green = 255;
			ColourSTART.blue = 255;
			ColourSTART.alpha = 055;
			ColourEND.red = 255;
			ColourEND.green = 255;
			ColourEND.blue = 255;
			ColourEND.alpha = 0;
			QpoVec3d Wind;
			Wind.x = 1;
			Wind.y = 0;
			Wind.z = 0;
			if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID1, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, Wind, 0);
			}


		//+---=VAPOR TRAIL=---+
		if(Q_Bullet->Bullet[Count].JDamageLVL == 4)
			{
			ColourSTART.red = 255;
			ColourSTART.green = 255;
			ColourSTART.blue = 255;
			ColourSTART.alpha = 45;
			ColourEND.red = 255;
			ColourEND.green = 255;
			ColourEND.blue = 255;
			ColourEND.alpha = 0;

			TempVec1 = Q_Bullet->Bullet[Count].Pos;
			TempVec2 = Q_Bullet->Bullet[Count].Pos;

			TempVec1.x += ((((float)rand() / 32767)-0.5)*2 + 1);
			TempVec1.y += ((((float)rand() / 32767)-0.5)*2 + 1);
			TempVec1.z += ((((float)rand() / 32767)-0.5)*2 + 1);

			Qpo->Vec3d_Subtract(&TempVec1, &TempVec2, &TempVec2);
			
			if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID1, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, TempVec2, 0);


			ColourSTART.red = 255;
			ColourSTART.green = 255;
			ColourSTART.blue = 255;
			ColourSTART.alpha = 45;
			ColourEND.red = 255;
			ColourEND.green = 255;
			ColourEND.blue = 255;
			ColourEND.alpha = 0;

			TempVec1 = Q_Bullet->Bullet[Count].Pos;
			TempVec2 = Q_Bullet->Bullet[Count].Pos;

			TempVec1.x += ((((float)rand() / 32767)-0.5)*2 + 1);
			TempVec1.y += ((((float)rand() / 32767)-0.5)*2 + 1);
			TempVec1.z += ((((float)rand() / 32767)-0.5)*2 + 1);

			Qpo->Vec3d_Subtract(&TempVec1, &TempVec2, &TempVec2);
			
			if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID2, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, TempVec2, 0);

			ColourSTART.red = 255;
			ColourSTART.green = 255;
			ColourSTART.blue = 255;
			ColourSTART.alpha = 45;
			ColourEND.red = 255;
			ColourEND.green = 255;
			ColourEND.blue = 255;
			ColourEND.alpha = 0;

			TempVec1 = Q_Bullet->Bullet[Count].Pos;
			TempVec2 = Q_Bullet->Bullet[Count].Pos;

			TempVec1.x += ((((float)rand() / 32767)-0.5)*2 + 1);
			TempVec1.y += ((((float)rand() / 32767)-0.5)*2 + 1);
			TempVec1.z += ((((float)rand() / 32767)-0.5)*2 + 1);

			Qpo->Vec3d_Subtract(&TempVec1, &TempVec2, &TempVec2);
			
			if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID3, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, TempVec2, 0);

			//ROCKET DRIVE

			TempVec1 = Q_Bullet->Bullet[Count].Pos;
			TempVec2 = Q_Bullet->Bullet[Count].Pos;

			Qpo->Vec3d_AddScaled(&TempVec2, -90, &Q_Bullet->Bullet[Count].TrajVec, &TempVec2);	//1.1

			Q_Bullet->Bullet[Count].RDriveMATCNT++;
			if(Q_Bullet->Bullet[Count].RDriveMATCNT < 0) Q_Bullet->Bullet[Count].RDriveMATCNT = 0;
			if(Q_Bullet->Bullet[Count].RDriveMATCNT > 9) Q_Bullet->Bullet[Count].RDriveMATCNT = 0;

			Q.ShowLine(&TempVec2, &TempVec1, &player[g_Player]->ViewXForm.Translation, 20, Medias->Rocket[Q_Bullet->Bullet[Count].RDriveMATCNT], 255, 255, 255, 255, 0);

			TempVec1 = Q_Bullet->Bullet[Count].TrajVec;
			Qpo->Vec3d_Inverse(&TempVec1);

			jet=0;
			while(jet < 3)
				{
				//#### Smoke Blast
				Q_Cloud->Cloud[_->NomCloud].CloudType = 10;
				Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Bullet->Bullet[Count].Pos;
				Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+175;
				Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.35;	//0.33;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec = TempVec1;
				Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += 0.35;
				Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + 0.5;
				Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;
				Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

				_->NomCloud++;
				if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
				jet++;
				}
			}

		//+---=====DRAW BULLET=====---+

		Q_Bullet->Bullet[Count].Type = QPOLY_TYPE_GOR;
		Q_Bullet->Bullet[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_Bullet->Bullet[Count].ScaleBIT = 1.0f;

		//Compensate for pivot
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, -Q_Bullet->Bullet[Count].Scale*2, &Q_Bullet->Bullet[Count].VecIn, &Q_Bullet->Bullet[Count].Pos);	//1.1

		//##Back Verts##
				//BACK VERT1
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/1.105, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertB1);	//1.1

				//BACK VERT2
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/6, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertB2);

		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB2, -Q_Bullet->Bullet[Count].Scale*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB2);

		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, -Q_Bullet->Bullet[Count].Scale, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertB3);

				//BACK VERT4
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB3, Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB4);	//1.75

				//BACK VERT3
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB3, -Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB3);

				//BACK VERT5
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB2, (Q_Bullet->Bullet[Count].Scale*2)*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB5);


		//OTF FIX
		Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertB3, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB3, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertB3);	//0.2106
		Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertB4, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB4, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertB4);


		//##Front Verts##
				//FRONT VERT1
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale*4, &Q_Bullet->Bullet[Count].VecIn, &Q_Bullet->Bullet[Count].Pos);

		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/1.105, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertF1);	//1.1

				//FRONT VERT2
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/6, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertF2);

		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF2, -Q_Bullet->Bullet[Count].Scale*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF2);

		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, -Q_Bullet->Bullet[Count].Scale, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertF3);

				//FRONT VERT4
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF3, Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF4);	//1.75

				//FRONT VERT3
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF3, -Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF3);

				//FRONT VERT5
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF2, (Q_Bullet->Bullet[Count].Scale*2)*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF5);


		Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertF3, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF3, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertF3);	//0.2106
		Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertF4, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF4, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertF4);

		//##Front Point##
				//FRONT POINT
		Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale*2.67, &Q_Bullet->Bullet[Count].VecIn, &Q_Bullet->Bullet[Count].VertFP);

		int a=0;
		while( a <= 12 )
			{
			int b=0;
			while( b <= 3 )
				{
				Q_Bullet->Bullet[Count].Lvert[a][b].a = 255;
				Q_Bullet->Bullet[Count].Lvert[a][b].b = 80;
				Q_Bullet->Bullet[Count].Lvert[a][b].g = 160;
				Q_Bullet->Bullet[Count].Lvert[a][b].r = 160;
				b++;
				}
			a++;
			}

		a=3;
		while( a <= 7 )
			{
			int b=0;
			while( b <= 1 )
				{
				Q_Bullet->Bullet[Count].Lvert[a][b].a = 255;
				Q_Bullet->Bullet[Count].Lvert[a][b].b = 20;
				Q_Bullet->Bullet[Count].Lvert[a][b].g = 90;
				Q_Bullet->Bullet[Count].Lvert[a][b].r = 90;
				b++;
				}
			a++;
			}

		//## Back Tris ##

		Q_Bullet->Bullet[Count].Lvert[0][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[0][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].VertB1.x;
		Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].VertB1.y;
		Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].VertB1.z;
		Q_Bullet->Bullet[Count].Lvert[0][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[0][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[0][1].x = Q_Bullet->Bullet[Count].VertB2.x;
		Q_Bullet->Bullet[Count].Lvert[0][1].y = Q_Bullet->Bullet[Count].VertB2.y;
		Q_Bullet->Bullet[Count].Lvert[0][1].z = Q_Bullet->Bullet[Count].VertB2.z;
		Q_Bullet->Bullet[Count].Lvert[0][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[0][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[0][2].x = Q_Bullet->Bullet[Count].VertB3.x;
		Q_Bullet->Bullet[Count].Lvert[0][2].y = Q_Bullet->Bullet[Count].VertB3.y;
		Q_Bullet->Bullet[Count].Lvert[0][2].z = Q_Bullet->Bullet[Count].VertB3.z;


		Q_Bullet->Bullet[Count].Lvert[1][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[1][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[1][0].x = Q_Bullet->Bullet[Count].VertB3.x;
		Q_Bullet->Bullet[Count].Lvert[1][0].y = Q_Bullet->Bullet[Count].VertB3.y;
		Q_Bullet->Bullet[Count].Lvert[1][0].z = Q_Bullet->Bullet[Count].VertB3.z;
		Q_Bullet->Bullet[Count].Lvert[1][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[1][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[1][1].x = Q_Bullet->Bullet[Count].VertB4.x;
		Q_Bullet->Bullet[Count].Lvert[1][1].y = Q_Bullet->Bullet[Count].VertB4.y;
		Q_Bullet->Bullet[Count].Lvert[1][1].z = Q_Bullet->Bullet[Count].VertB4.z;
		Q_Bullet->Bullet[Count].Lvert[1][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[1][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[1][2].x = Q_Bullet->Bullet[Count].VertB1.x;
		Q_Bullet->Bullet[Count].Lvert[1][2].y = Q_Bullet->Bullet[Count].VertB1.y;
		Q_Bullet->Bullet[Count].Lvert[1][2].z = Q_Bullet->Bullet[Count].VertB1.z;


		Q_Bullet->Bullet[Count].Lvert[2][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[2][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[2][0].x = Q_Bullet->Bullet[Count].VertB4.x;
		Q_Bullet->Bullet[Count].Lvert[2][0].y = Q_Bullet->Bullet[Count].VertB4.y;
		Q_Bullet->Bullet[Count].Lvert[2][0].z = Q_Bullet->Bullet[Count].VertB4.z;
		Q_Bullet->Bullet[Count].Lvert[2][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[2][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[2][1].x = Q_Bullet->Bullet[Count].VertB5.x;
		Q_Bullet->Bullet[Count].Lvert[2][1].y = Q_Bullet->Bullet[Count].VertB5.y;
		Q_Bullet->Bullet[Count].Lvert[2][1].z = Q_Bullet->Bullet[Count].VertB5.z;
		Q_Bullet->Bullet[Count].Lvert[2][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[2][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[2][2].x = Q_Bullet->Bullet[Count].VertB1.x;
		Q_Bullet->Bullet[Count].Lvert[2][2].y = Q_Bullet->Bullet[Count].VertB1.y;
		Q_Bullet->Bullet[Count].Lvert[2][2].z = Q_Bullet->Bullet[Count].VertB1.z;


		//## Side Strips ##

		//Strip1
		Q_Bullet->Bullet[Count].Lvert[3][0].u = 1;
		Q_Bullet->Bullet[Count].Lvert[3][0].v = 0;
		Q_Bullet->Bullet[Count].Lvert[3][0].x = Q_Bullet->Bullet[Count].VertB1.x;
		Q_Bullet->Bullet[Count].Lvert[3][0].y = Q_Bullet->Bullet[Count].VertB1.y;
		Q_Bullet->Bullet[Count].Lvert[3][0].z = Q_Bullet->Bullet[Count].VertB1.z;
		Q_Bullet->Bullet[Count].Lvert[3][1].u = 0;
		Q_Bullet->Bullet[Count].Lvert[3][1].v = 0;
		Q_Bullet->Bullet[Count].Lvert[3][1].x = Q_Bullet->Bullet[Count].VertB2.x;
		Q_Bullet->Bullet[Count].Lvert[3][1].y = Q_Bullet->Bullet[Count].VertB2.y;
		Q_Bullet->Bullet[Count].Lvert[3][1].z = Q_Bullet->Bullet[Count].VertB2.z;
		Q_Bullet->Bullet[Count].Lvert[3][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[3][2].v = 1;
		Q_Bullet->Bullet[Count].Lvert[3][2].x = Q_Bullet->Bullet[Count].VertF2.x;
		Q_Bullet->Bullet[Count].Lvert[3][2].y = Q_Bullet->Bullet[Count].VertF2.y;
		Q_Bullet->Bullet[Count].Lvert[3][2].z = Q_Bullet->Bullet[Count].VertF2.z;
		Q_Bullet->Bullet[Count].Lvert[3][3].u = 1;
		Q_Bullet->Bullet[Count].Lvert[3][3].v = 1;
		Q_Bullet->Bullet[Count].Lvert[3][3].x = Q_Bullet->Bullet[Count].VertF1.x;
		Q_Bullet->Bullet[Count].Lvert[3][3].y = Q_Bullet->Bullet[Count].VertF1.y;
		Q_Bullet->Bullet[Count].Lvert[3][3].z = Q_Bullet->Bullet[Count].VertF1.z;


		//Strip2
		Q_Bullet->Bullet[Count].Lvert[4][0].u = 1;
		Q_Bullet->Bullet[Count].Lvert[4][0].v = 0;
		Q_Bullet->Bullet[Count].Lvert[4][0].x = Q_Bullet->Bullet[Count].VertB2.x;
		Q_Bullet->Bullet[Count].Lvert[4][0].y = Q_Bullet->Bullet[Count].VertB2.y;
		Q_Bullet->Bullet[Count].Lvert[4][0].z = Q_Bullet->Bullet[Count].VertB2.z;
		Q_Bullet->Bullet[Count].Lvert[4][1].u = 0;
		Q_Bullet->Bullet[Count].Lvert[4][1].v = 0;
		Q_Bullet->Bullet[Count].Lvert[4][1].x = Q_Bullet->Bullet[Count].VertB3.x;
		Q_Bullet->Bullet[Count].Lvert[4][1].y = Q_Bullet->Bullet[Count].VertB3.y;
		Q_Bullet->Bullet[Count].Lvert[4][1].z = Q_Bullet->Bullet[Count].VertB3.z;
		Q_Bullet->Bullet[Count].Lvert[4][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[4][2].v = 1;
		Q_Bullet->Bullet[Count].Lvert[4][2].x = Q_Bullet->Bullet[Count].VertF3.x;
		Q_Bullet->Bullet[Count].Lvert[4][2].y = Q_Bullet->Bullet[Count].VertF3.y;
		Q_Bullet->Bullet[Count].Lvert[4][2].z = Q_Bullet->Bullet[Count].VertF3.z;
		Q_Bullet->Bullet[Count].Lvert[4][3].u = 1;
		Q_Bullet->Bullet[Count].Lvert[4][3].v = 1;
		Q_Bullet->Bullet[Count].Lvert[4][3].x = Q_Bullet->Bullet[Count].VertF2.x;
		Q_Bullet->Bullet[Count].Lvert[4][3].y = Q_Bullet->Bullet[Count].VertF2.y;
		Q_Bullet->Bullet[Count].Lvert[4][3].z = Q_Bullet->Bullet[Count].VertF2.z;


		//Strip3
		Q_Bullet->Bullet[Count].Lvert[5][0].u = 1;
		Q_Bullet->Bullet[Count].Lvert[5][0].v = 0;
		Q_Bullet->Bullet[Count].Lvert[5][0].x = Q_Bullet->Bullet[Count].VertB3.x;
		Q_Bullet->Bullet[Count].Lvert[5][0].y = Q_Bullet->Bullet[Count].VertB3.y;
		Q_Bullet->Bullet[Count].Lvert[5][0].z = Q_Bullet->Bullet[Count].VertB3.z;
		Q_Bullet->Bullet[Count].Lvert[5][1].u = 0;
		Q_Bullet->Bullet[Count].Lvert[5][1].v = 0;
		Q_Bullet->Bullet[Count].Lvert[5][1].x = Q_Bullet->Bullet[Count].VertB4.x;
		Q_Bullet->Bullet[Count].Lvert[5][1].y = Q_Bullet->Bullet[Count].VertB4.y;
		Q_Bullet->Bullet[Count].Lvert[5][1].z = Q_Bullet->Bullet[Count].VertB4.z;
		Q_Bullet->Bullet[Count].Lvert[5][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[5][2].v = 1;
		Q_Bullet->Bullet[Count].Lvert[5][2].x = Q_Bullet->Bullet[Count].VertF4.x;
		Q_Bullet->Bullet[Count].Lvert[5][2].y = Q_Bullet->Bullet[Count].VertF4.y;
		Q_Bullet->Bullet[Count].Lvert[5][2].z = Q_Bullet->Bullet[Count].VertF4.z;
		Q_Bullet->Bullet[Count].Lvert[5][3].u = 1;
		Q_Bullet->Bullet[Count].Lvert[5][3].v = 1;
		Q_Bullet->Bullet[Count].Lvert[5][3].x = Q_Bullet->Bullet[Count].VertF3.x;
		Q_Bullet->Bullet[Count].Lvert[5][3].y = Q_Bullet->Bullet[Count].VertF3.y;
		Q_Bullet->Bullet[Count].Lvert[5][3].z = Q_Bullet->Bullet[Count].VertF3.z;


		//Strip4
		Q_Bullet->Bullet[Count].Lvert[6][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[6][0].v = 0;
		Q_Bullet->Bullet[Count].Lvert[6][0].x = Q_Bullet->Bullet[Count].VertB4.x;
		Q_Bullet->Bullet[Count].Lvert[6][0].y = Q_Bullet->Bullet[Count].VertB4.y;
		Q_Bullet->Bullet[Count].Lvert[6][0].z = Q_Bullet->Bullet[Count].VertB4.z;
		Q_Bullet->Bullet[Count].Lvert[6][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[6][1].v = 0;
		Q_Bullet->Bullet[Count].Lvert[6][1].x = Q_Bullet->Bullet[Count].VertB5.x;
		Q_Bullet->Bullet[Count].Lvert[6][1].y = Q_Bullet->Bullet[Count].VertB5.y;
		Q_Bullet->Bullet[Count].Lvert[6][1].z = Q_Bullet->Bullet[Count].VertB5.z;
		Q_Bullet->Bullet[Count].Lvert[6][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[6][2].v = 1;
		Q_Bullet->Bullet[Count].Lvert[6][2].x = Q_Bullet->Bullet[Count].VertF5.x;
		Q_Bullet->Bullet[Count].Lvert[6][2].y = Q_Bullet->Bullet[Count].VertF5.y;
		Q_Bullet->Bullet[Count].Lvert[6][2].z = Q_Bullet->Bullet[Count].VertF5.z;
		Q_Bullet->Bullet[Count].Lvert[6][3].u = 1;
		Q_Bullet->Bullet[Count].Lvert[6][3].v = 1;
		Q_Bullet->Bullet[Count].Lvert[6][3].x = Q_Bullet->Bullet[Count].VertF4.x;
		Q_Bullet->Bullet[Count].Lvert[6][3].y = Q_Bullet->Bullet[Count].VertF4.y;
		Q_Bullet->Bullet[Count].Lvert[6][3].z = Q_Bullet->Bullet[Count].VertF4.z;


		//Strip5
		Q_Bullet->Bullet[Count].Lvert[7][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[7][0].v = 0;
		Q_Bullet->Bullet[Count].Lvert[7][0].x = Q_Bullet->Bullet[Count].VertB5.x;
		Q_Bullet->Bullet[Count].Lvert[7][0].y = Q_Bullet->Bullet[Count].VertB5.y;
		Q_Bullet->Bullet[Count].Lvert[7][0].z = Q_Bullet->Bullet[Count].VertB5.z;
		Q_Bullet->Bullet[Count].Lvert[7][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[7][1].v = 0;
		Q_Bullet->Bullet[Count].Lvert[7][1].x = Q_Bullet->Bullet[Count].VertB1.x;
		Q_Bullet->Bullet[Count].Lvert[7][1].y = Q_Bullet->Bullet[Count].VertB1.y;
		Q_Bullet->Bullet[Count].Lvert[7][1].z = Q_Bullet->Bullet[Count].VertB1.z;
		Q_Bullet->Bullet[Count].Lvert[7][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[7][2].v = 1;
		Q_Bullet->Bullet[Count].Lvert[7][2].x = Q_Bullet->Bullet[Count].VertF1.x;
		Q_Bullet->Bullet[Count].Lvert[7][2].y = Q_Bullet->Bullet[Count].VertF1.y;
		Q_Bullet->Bullet[Count].Lvert[7][2].z = Q_Bullet->Bullet[Count].VertF1.z;
		Q_Bullet->Bullet[Count].Lvert[7][3].u = 1;
		Q_Bullet->Bullet[Count].Lvert[7][3].v = 1;
		Q_Bullet->Bullet[Count].Lvert[7][3].x = Q_Bullet->Bullet[Count].VertF5.x;
		Q_Bullet->Bullet[Count].Lvert[7][3].y = Q_Bullet->Bullet[Count].VertF5.y;
		Q_Bullet->Bullet[Count].Lvert[7][3].z = Q_Bullet->Bullet[Count].VertF5.z;


		//## Front Tris ##

		Q_Bullet->Bullet[Count].Lvert[8][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[8][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[8][0].x = Q_Bullet->Bullet[Count].VertF1.x;
		Q_Bullet->Bullet[Count].Lvert[8][0].y = Q_Bullet->Bullet[Count].VertF1.y;
		Q_Bullet->Bullet[Count].Lvert[8][0].z = Q_Bullet->Bullet[Count].VertF1.z;
		Q_Bullet->Bullet[Count].Lvert[8][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[8][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[8][1].x = Q_Bullet->Bullet[Count].VertF2.x;
		Q_Bullet->Bullet[Count].Lvert[8][1].y = Q_Bullet->Bullet[Count].VertF2.y;
		Q_Bullet->Bullet[Count].Lvert[8][1].z = Q_Bullet->Bullet[Count].VertF2.z;
		Q_Bullet->Bullet[Count].Lvert[8][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[8][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[8][2].x = Q_Bullet->Bullet[Count].VertFP.x;
		Q_Bullet->Bullet[Count].Lvert[8][2].y = Q_Bullet->Bullet[Count].VertFP.y;
		Q_Bullet->Bullet[Count].Lvert[8][2].z = Q_Bullet->Bullet[Count].VertFP.z;


		Q_Bullet->Bullet[Count].Lvert[9][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[9][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[9][0].x = Q_Bullet->Bullet[Count].VertF2.x;
		Q_Bullet->Bullet[Count].Lvert[9][0].y = Q_Bullet->Bullet[Count].VertF2.y;
		Q_Bullet->Bullet[Count].Lvert[9][0].z = Q_Bullet->Bullet[Count].VertF2.z;
		Q_Bullet->Bullet[Count].Lvert[9][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[9][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[9][1].x = Q_Bullet->Bullet[Count].VertF3.x;
		Q_Bullet->Bullet[Count].Lvert[9][1].y = Q_Bullet->Bullet[Count].VertF3.y;
		Q_Bullet->Bullet[Count].Lvert[9][1].z = Q_Bullet->Bullet[Count].VertF3.z;
		Q_Bullet->Bullet[Count].Lvert[9][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[9][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[9][2].x = Q_Bullet->Bullet[Count].VertFP.x;
		Q_Bullet->Bullet[Count].Lvert[9][2].y = Q_Bullet->Bullet[Count].VertFP.y;
		Q_Bullet->Bullet[Count].Lvert[9][2].z = Q_Bullet->Bullet[Count].VertFP.z;


		Q_Bullet->Bullet[Count].Lvert[10][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[10][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[10][0].x = Q_Bullet->Bullet[Count].VertF3.x;
		Q_Bullet->Bullet[Count].Lvert[10][0].y = Q_Bullet->Bullet[Count].VertF3.y;
		Q_Bullet->Bullet[Count].Lvert[10][0].z = Q_Bullet->Bullet[Count].VertF3.z;
		Q_Bullet->Bullet[Count].Lvert[10][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[10][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[10][1].x = Q_Bullet->Bullet[Count].VertF4.x;
		Q_Bullet->Bullet[Count].Lvert[10][1].y = Q_Bullet->Bullet[Count].VertF4.y;
		Q_Bullet->Bullet[Count].Lvert[10][1].z = Q_Bullet->Bullet[Count].VertF4.z;
		Q_Bullet->Bullet[Count].Lvert[10][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[10][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[10][2].x = Q_Bullet->Bullet[Count].VertFP.x;
		Q_Bullet->Bullet[Count].Lvert[10][2].y = Q_Bullet->Bullet[Count].VertFP.y;
		Q_Bullet->Bullet[Count].Lvert[10][2].z = Q_Bullet->Bullet[Count].VertFP.z;


		Q_Bullet->Bullet[Count].Lvert[11][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[11][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[11][0].x = Q_Bullet->Bullet[Count].VertF4.x;
		Q_Bullet->Bullet[Count].Lvert[11][0].y = Q_Bullet->Bullet[Count].VertF4.y;
		Q_Bullet->Bullet[Count].Lvert[11][0].z = Q_Bullet->Bullet[Count].VertF4.z;
		Q_Bullet->Bullet[Count].Lvert[11][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[11][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[11][1].x = Q_Bullet->Bullet[Count].VertF5.x;
		Q_Bullet->Bullet[Count].Lvert[11][1].y = Q_Bullet->Bullet[Count].VertF5.y;
		Q_Bullet->Bullet[Count].Lvert[11][1].z = Q_Bullet->Bullet[Count].VertF5.z;
		Q_Bullet->Bullet[Count].Lvert[11][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[11][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[11][2].x = Q_Bullet->Bullet[Count].VertFP.x;
		Q_Bullet->Bullet[Count].Lvert[11][2].y = Q_Bullet->Bullet[Count].VertFP.y;
		Q_Bullet->Bullet[Count].Lvert[11][2].z = Q_Bullet->Bullet[Count].VertFP.z;


		Q_Bullet->Bullet[Count].Lvert[12][0].u = 0;
		Q_Bullet->Bullet[Count].Lvert[12][0].v = 1;
		Q_Bullet->Bullet[Count].Lvert[12][0].x = Q_Bullet->Bullet[Count].VertF5.x;
		Q_Bullet->Bullet[Count].Lvert[12][0].y = Q_Bullet->Bullet[Count].VertF5.y;
		Q_Bullet->Bullet[Count].Lvert[12][0].z = Q_Bullet->Bullet[Count].VertF5.z;
		Q_Bullet->Bullet[Count].Lvert[12][1].u = 1;
		Q_Bullet->Bullet[Count].Lvert[12][1].v = 1;
		Q_Bullet->Bullet[Count].Lvert[12][1].x = Q_Bullet->Bullet[Count].VertF1.x;
		Q_Bullet->Bullet[Count].Lvert[12][1].y = Q_Bullet->Bullet[Count].VertF1.y;
		Q_Bullet->Bullet[Count].Lvert[12][1].z = Q_Bullet->Bullet[Count].VertF1.z;
		Q_Bullet->Bullet[Count].Lvert[12][2].u = 1;
		Q_Bullet->Bullet[Count].Lvert[12][2].v = 0;
		Q_Bullet->Bullet[Count].Lvert[12][2].x = Q_Bullet->Bullet[Count].VertFP.x;
		Q_Bullet->Bullet[Count].Lvert[12][2].y = Q_Bullet->Bullet[Count].VertFP.y;
		Q_Bullet->Bullet[Count].Lvert[12][2].z = Q_Bullet->Bullet[Count].VertFP.z;


		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[1][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[2][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);

		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[3][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[4][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[5][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[6][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[7][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);

		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[8][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[9][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[10][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[11][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[12][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
		}

	return true;
	}


bool Q_EFFCon::Bullet_ClientFrame(int Count)
{
#if 1
	//Apply Gravity
	Q_Bullet->Bullet[Count].TrajVec.y -= Q_Bullet->Bullet[Count].Gravity*_->TimeScale;
	
	//Move
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].WorldPos, Q_Bullet->Bullet[Count].Speed*_->TimeScale, &Q_Bullet->Bullet[Count].TrajVec, &Q_Bullet->Bullet[Count].NewPos);
#endif

#if 0
	Q_Bullet->Bullet[Count].NewPos = Q_Bullet->Bullet[Count].WorldPos;
#endif

	//## Bullet Trails
	if(Q_Bullet->Bullet[Count].JDamageLVL == 0)
		{
		if(_->TimeScale > 0.65)
			{
			//## Bullet Trails
			if(Qpo->Vec3d_DistanceBetween(&Q_Bullet->Bullet[Count].NewPos, &Q_Bullet->Bullet[Count].ORIGPos) < Q_Bullet->Bullet[Count].Speed)
				{
				Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].ORIGPos;
				Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
				}
			else
				{
				Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].NewPos;
				Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
				Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].TrailEnd, -Q_Bullet->Bullet[Count].Speed, &Q_Bullet->Bullet[Count].TrajVec, &Q_Bullet->Bullet[Count].TrailStart);
				}

			if(Q_Bullet->Bullet[Count].Live == 0)
				{
				Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
				Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 0.55, Medias->BulletTrail, 30, 255, 255, 220, 0);
				}
			else 
				{
				Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 0.55, Medias->BulletTrail, 70, 255, 255, 220, 0);
				printf("Q_Bullet->Bullet[Count].TrailEnd %f %f %f\n", Q_Bullet->Bullet[Count].TrailEnd.x, Q_Bullet->Bullet[Count].TrailEnd.y, Q_Bullet->Bullet[Count].TrailEnd.z);
				}
			}
		else
			{
			//Particle ejjector LVL02
			player[g_Player]->QAEFF_CNTR01[0] += 1;
			player[g_Player]->QAEFF_ROTAMT[0] = 0;

			TempVec1 = Q_Bullet->Bullet[Count].WorldPos;

			if(player[g_Player]->QAEFF_CNTR01[0] > 2)
				{
				player[g_Player]->QAEFF_CNTR01[0] = 0;

				jet=0;
				while((jet < 15) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.02f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 26;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 30;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.35;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TempVec1;

					Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_Bullet->Bullet[Count].TrajVec;

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);

					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Transform_New_YRotation(&RotateMatrix3, player[g_Player]->QAEFF_ROTAMT[0]);

					player[g_Player]->QAEFF_ROTAMT[0] += 0.42;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);

					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[helly].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}
			}
		}
	else
		{
		//## Bullet Trails
		if(Qpo->Vec3d_DistanceBetween(&Q_Bullet->Bullet[Count].NewPos, &Q_Bullet->Bullet[Count].ORIGPos) < Q_Bullet->Bullet[Count].Speed)
			{
			Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].ORIGPos;
			Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
			}
		else
			{
			Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].NewPos;
			Q_Bullet->Bullet[Count].TrailEnd = Q_Bullet->Bullet[Count].NewPos;
			Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].TrailEnd, -Q_Bullet->Bullet[Count].Speed, &Q_Bullet->Bullet[Count].TrajVec, &Q_Bullet->Bullet[Count].TrailStart);
			}

		switch(Q_Bullet->Bullet[Count].JDamageLVL)
			{
			case 1:
				{
				if(Q_Bullet->Bullet[Count].Live == 0)
					{
					Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
					Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 3, Medias->QAEFF29, 30, 255, 255, 255, 0);
					}
				else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 3, Medias->QAEFF29, 90, 255, 255, 255, 0);

				//##### Render Main Sprite
				Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].WorldPos.x;
				Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].WorldPos.y;
				Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].WorldPos.z;
				Q_Bullet->Bullet[Count].Lvert[0][0].r = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].g = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].b = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].a = 90;

				Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 1, Medias->QAEFF28, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.2f);
				}break;

			case 2:
				{
				if(Q_Bullet->Bullet[Count].Live == 0)
					{
					Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
					Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 5, Medias->QAEFF29, 50, 255, 255, 255, 0);
					}
				else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 5, Medias->QAEFF29, 135, 255, 255, 255, 0);

				//##### Render Main Sprite
				Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].WorldPos.x;
				Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].WorldPos.y;
				Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].WorldPos.z;
				Q_Bullet->Bullet[Count].Lvert[0][0].r = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].g = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].b = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].a = 135;

				Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 1, Medias->QAEFF28, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.35f);
				}break;

			case 3:
				{
				if(Q_Bullet->Bullet[Count].Live == 0)
					{
					Q_Bullet->Bullet[Count].TrailStart = Q_Bullet->Bullet[Count].WorldPos;
					Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 10, Medias->QAEFF29, 100, 255, 255, 255, 0);
					}
				else Q.ShowLine(&Q_Bullet->Bullet[Count].TrailEnd, &Q_Bullet->Bullet[Count].TrailStart, &player[g_Player]->ViewXForm.Translation, 10, Medias->QAEFF29, 200, 255, 255, 255, 0);

				//##### Render Main Sprite
				Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].WorldPos.x;
				Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].WorldPos.y;
				Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].WorldPos.z;
				Q_Bullet->Bullet[Count].Lvert[0][0].r = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].g = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].b = 255;
				Q_Bullet->Bullet[Count].Lvert[0][0].a = 200;

				Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 1, Medias->QAEFF28, QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.5f);
				}break;
			}
		}


	Q_Bullet->Bullet[Count].WorldPos = Q_Bullet->Bullet[Count].NewPos;

	//Spin Bullet
	Q_Bullet->Bullet[Count].Zrot += Q_Bullet->Bullet[Count].ZSpin*_->TimeScale;

	Qpo->Transform_New_ZRotation(&rotmat, Q_Bullet->Bullet[Count].Zrot);
	Qpo->Transform_Multiply(&Q_Bullet->Bullet[Count].AlignMatrix, &rotmat, &Q_Bullet->Bullet[Count].AlignMatrix);

	Q_Bullet->Bullet[Count].AlignMatrix.Translation = Q_Bullet->Bullet[Count].WorldPos;

	Q_Bullet->Bullet[Count].Pos = Q_Bullet->Bullet[Count].AlignMatrix.Translation;

	Qpo->Transform_GetUp(&Q_Bullet->Bullet[Count].AlignMatrix, &Q_Bullet->Bullet[Count].VecUp);
	Qpo->Transform_GetLeft(&Q_Bullet->Bullet[Count].AlignMatrix, &Q_Bullet->Bullet[Count].VecLeft);
	Qpo->Transform_GetIn(&Q_Bullet->Bullet[Count].AlignMatrix, &Q_Bullet->Bullet[Count].VecIn);


	//##### Jink Damage single vapor
	if(Q_Bullet->Bullet[Count].JDamageLVL == 3 || Q_Bullet->Bullet[Count].BulletPWR > 45.5)
		{
		ColourSTART.red = 255;
		ColourSTART.green = 255;
		ColourSTART.blue = 255;
		ColourSTART.alpha = 055;
		ColourEND.red = 255;
		ColourEND.green = 255;
		ColourEND.blue = 255;
		ColourEND.alpha = 0;
		QpoVec3d Wind;
		Wind.x = 1;
		Wind.y = 0;
		Wind.z = 0;
		if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID1, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, Wind, 0);
		}


	//+---=VAPOR TRAIL=---+
	if(Q_Bullet->Bullet[Count].JDamageLVL == 4)
		{
		ColourSTART.red = 255;
		ColourSTART.green = 255;
		ColourSTART.blue = 255;
		ColourSTART.alpha = 45;
		ColourEND.red = 255;
		ColourEND.green = 255;
		ColourEND.blue = 255;
		ColourEND.alpha = 0;

		TempVec1 = Q_Bullet->Bullet[Count].Pos;
		TempVec2 = Q_Bullet->Bullet[Count].Pos;

		TempVec1.x += ((((float)rand() / 32767)-0.5)*2 + 1);
		TempVec1.y += ((((float)rand() / 32767)-0.5)*2 + 1);
		TempVec1.z += ((((float)rand() / 32767)-0.5)*2 + 1);

		Qpo->Vec3d_Subtract(&TempVec1, &TempVec2, &TempVec2);
		
		if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID1, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, TempVec2, 0);


		ColourSTART.red = 255;
		ColourSTART.green = 255;
		ColourSTART.blue = 255;
		ColourSTART.alpha = 45;
		ColourEND.red = 255;
		ColourEND.green = 255;
		ColourEND.blue = 255;
		ColourEND.alpha = 0;

		TempVec1 = Q_Bullet->Bullet[Count].Pos;
		TempVec2 = Q_Bullet->Bullet[Count].Pos;

		TempVec1.x += ((((float)rand() / 32767)-0.5)*2 + 1);
		TempVec1.y += ((((float)rand() / 32767)-0.5)*2 + 1);
		TempVec1.z += ((((float)rand() / 32767)-0.5)*2 + 1);

		Qpo->Vec3d_Subtract(&TempVec1, &TempVec2, &TempVec2);
		
		if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID2, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, TempVec2, 0);


		ColourSTART.red = 255;
		ColourSTART.green = 255;
		ColourSTART.blue = 255;
		ColourSTART.alpha = 45;
		ColourEND.red = 255;
		ColourEND.green = 255;
		ColourEND.blue = 255;
		ColourEND.alpha = 0;

		TempVec1 = Q_Bullet->Bullet[Count].Pos;
		TempVec2 = Q_Bullet->Bullet[Count].Pos;

		TempVec1.x += ((((float)rand() / 32767)-0.5)*2 + 1);
		TempVec1.y += ((((float)rand() / 32767)-0.5)*2 + 1);
		TempVec1.z += ((((float)rand() / 32767)-0.5)*2 + 1);

		Qpo->Vec3d_Subtract(&TempVec1, &TempVec2, &TempVec2);
		
		if(Q_VaporTrail->VaporTrail[Q_Bullet->Bullet[Count].VaporID1].NomPoints <= 998) Q.AddTrailPNT(Q_Bullet->Bullet[Count].VaporID3, Q_Bullet->Bullet[Count].Pos, ColourSTART, ColourEND, TempVec2, 0);

		//ROCKET DRIVE

		TempVec1 = Q_Bullet->Bullet[Count].Pos;
		TempVec2 = Q_Bullet->Bullet[Count].Pos;

		Qpo->Vec3d_AddScaled(&TempVec2, -90, &Q_Bullet->Bullet[Count].TrajVec, &TempVec2);	//1.1

		Q_Bullet->Bullet[Count].RDriveMATCNT++;
		if(Q_Bullet->Bullet[Count].RDriveMATCNT < 0) Q_Bullet->Bullet[Count].RDriveMATCNT = 0;
		if(Q_Bullet->Bullet[Count].RDriveMATCNT > 9) Q_Bullet->Bullet[Count].RDriveMATCNT = 0;

		Q.ShowLine(&TempVec2, &TempVec1, &player[g_Player]->ViewXForm.Translation, 20, Medias->Rocket[Q_Bullet->Bullet[Count].RDriveMATCNT], 255, 255, 255, 255, 0);

		TempVec1 = Q_Bullet->Bullet[Count].TrajVec;
		Qpo->Vec3d_Inverse(&TempVec1);

		jet=0;
		while(jet < 3)
			{
			//#### Smoke Blast
			Q_Cloud->Cloud[_->NomCloud].CloudType = 10;
			Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_Bullet->Bullet[Count].Pos;
			Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*80)+175;
			Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*0.35;	//0.33;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec = TempVec1;
			Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += 0.35;
			Q_Cloud->Cloud[_->NomCloud].CloudSpeed = (((float)rand() / 32767)*0.03) + 0.5;
			Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;
			Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

			_->NomCloud++;
			if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
			jet++;
			}
		}


	//DRAW BULLET

	Q_Bullet->Bullet[Count].Type = QPOLY_TYPE_GOR;
	Q_Bullet->Bullet[Count].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
	Q_Bullet->Bullet[Count].ScaleBIT = 1.0f;

	Q_Bullet->Bullet[Count].Scale = 0.5;

	//Compensate for pivot
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, -Q_Bullet->Bullet[Count].Scale*2, &Q_Bullet->Bullet[Count].VecIn, &Q_Bullet->Bullet[Count].Pos);	//1.1

	//##Back Verts##
			//BACK VERT1
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/1.105, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertB1);	//1.1

			//BACK VERT2
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/6, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertB2);

	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB2, -Q_Bullet->Bullet[Count].Scale*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB2);

	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, -Q_Bullet->Bullet[Count].Scale, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertB3);

			//BACK VERT4
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB3, Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB4);	//1.75

			//BACK VERT3
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB3, -Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB3);

			//BACK VERT5
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB2, (Q_Bullet->Bullet[Count].Scale*2)*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertB5);


	//OTF FIX
	Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertB3, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB3, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertB3);	//0.2106
	Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertB4, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertB4, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertB4);


	//##Front Verts##
			//FRONT VERT1
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale*4, &Q_Bullet->Bullet[Count].VecIn, &Q_Bullet->Bullet[Count].Pos);

	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/1.105, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertF1);	//1.1

			//FRONT VERT2
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale/6, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF2, -Q_Bullet->Bullet[Count].Scale*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF2);

	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, -Q_Bullet->Bullet[Count].Scale, &Q_Bullet->Bullet[Count].VecUp, &Q_Bullet->Bullet[Count].VertF3);

			//FRONT VERT4
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF3, Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF4);	//1.75

			//FRONT VERT3
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF3, -Q_Bullet->Bullet[Count].Scale/1.62, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF3);

			//FRONT VERT5
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF2, (Q_Bullet->Bullet[Count].Scale*2)*0.89, &Q_Bullet->Bullet[Count].VecLeft, &Q_Bullet->Bullet[Count].VertF5);


	Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertF3, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF3, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertF3);	//0.2106
	Qpo->Vec3d_Subtract(&Q_Bullet->Bullet[Count].VertF4, &Q_Bullet->Bullet[Count].Pos, &Q_Bullet->Bullet[Count].VecSTR);
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].VertF4, -0.23, &Q_Bullet->Bullet[Count].VecSTR, &Q_Bullet->Bullet[Count].VertF4);


	//##Front Point##
			//FRONT POINT
	Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[Count].Pos, Q_Bullet->Bullet[Count].Scale*2.67, &Q_Bullet->Bullet[Count].VecIn, &Q_Bullet->Bullet[Count].VertFP);


	int a=0;
	while( a <= 12 )
		{
		int b=0;
		while( b <= 3 )
			{
			Q_Bullet->Bullet[Count].Lvert[a][b].a = 255;
			Q_Bullet->Bullet[Count].Lvert[a][b].b = 80;
			Q_Bullet->Bullet[Count].Lvert[a][b].g = 160;
			Q_Bullet->Bullet[Count].Lvert[a][b].r = 160;
			b++;
			}
		a++;
		}

	a=3;
	while( a <= 7 )
		{
		int b=0;
		while( b <= 1 )
			{
			Q_Bullet->Bullet[Count].Lvert[a][b].a = 255;
			Q_Bullet->Bullet[Count].Lvert[a][b].b = 20;
			Q_Bullet->Bullet[Count].Lvert[a][b].g = 90;
			Q_Bullet->Bullet[Count].Lvert[a][b].r = 90;
			b++;
			}
		a++;
		}

	//## Back Tris ##

	Q_Bullet->Bullet[Count].Lvert[0][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[0][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[0][0].x = Q_Bullet->Bullet[Count].VertB1.x;
	Q_Bullet->Bullet[Count].Lvert[0][0].y = Q_Bullet->Bullet[Count].VertB1.y;
	Q_Bullet->Bullet[Count].Lvert[0][0].z = Q_Bullet->Bullet[Count].VertB1.z;
	Q_Bullet->Bullet[Count].Lvert[0][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[0][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[0][1].x = Q_Bullet->Bullet[Count].VertB2.x;
	Q_Bullet->Bullet[Count].Lvert[0][1].y = Q_Bullet->Bullet[Count].VertB2.y;
	Q_Bullet->Bullet[Count].Lvert[0][1].z = Q_Bullet->Bullet[Count].VertB2.z;
	Q_Bullet->Bullet[Count].Lvert[0][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[0][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[0][2].x = Q_Bullet->Bullet[Count].VertB3.x;
	Q_Bullet->Bullet[Count].Lvert[0][2].y = Q_Bullet->Bullet[Count].VertB3.y;
	Q_Bullet->Bullet[Count].Lvert[0][2].z = Q_Bullet->Bullet[Count].VertB3.z;


	Q_Bullet->Bullet[Count].Lvert[1][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[1][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[1][0].x = Q_Bullet->Bullet[Count].VertB3.x;
	Q_Bullet->Bullet[Count].Lvert[1][0].y = Q_Bullet->Bullet[Count].VertB3.y;
	Q_Bullet->Bullet[Count].Lvert[1][0].z = Q_Bullet->Bullet[Count].VertB3.z;
	Q_Bullet->Bullet[Count].Lvert[1][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[1][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[1][1].x = Q_Bullet->Bullet[Count].VertB4.x;
	Q_Bullet->Bullet[Count].Lvert[1][1].y = Q_Bullet->Bullet[Count].VertB4.y;
	Q_Bullet->Bullet[Count].Lvert[1][1].z = Q_Bullet->Bullet[Count].VertB4.z;
	Q_Bullet->Bullet[Count].Lvert[1][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[1][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[1][2].x = Q_Bullet->Bullet[Count].VertB1.x;
	Q_Bullet->Bullet[Count].Lvert[1][2].y = Q_Bullet->Bullet[Count].VertB1.y;
	Q_Bullet->Bullet[Count].Lvert[1][2].z = Q_Bullet->Bullet[Count].VertB1.z;


	Q_Bullet->Bullet[Count].Lvert[2][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[2][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[2][0].x = Q_Bullet->Bullet[Count].VertB4.x;
	Q_Bullet->Bullet[Count].Lvert[2][0].y = Q_Bullet->Bullet[Count].VertB4.y;
	Q_Bullet->Bullet[Count].Lvert[2][0].z = Q_Bullet->Bullet[Count].VertB4.z;
	Q_Bullet->Bullet[Count].Lvert[2][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[2][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[2][1].x = Q_Bullet->Bullet[Count].VertB5.x;
	Q_Bullet->Bullet[Count].Lvert[2][1].y = Q_Bullet->Bullet[Count].VertB5.y;
	Q_Bullet->Bullet[Count].Lvert[2][1].z = Q_Bullet->Bullet[Count].VertB5.z;
	Q_Bullet->Bullet[Count].Lvert[2][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[2][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[2][2].x = Q_Bullet->Bullet[Count].VertB1.x;
	Q_Bullet->Bullet[Count].Lvert[2][2].y = Q_Bullet->Bullet[Count].VertB1.y;
	Q_Bullet->Bullet[Count].Lvert[2][2].z = Q_Bullet->Bullet[Count].VertB1.z;


	//## Side Strips ##

	//Strip1
	Q_Bullet->Bullet[Count].Lvert[3][0].u = 1;
	Q_Bullet->Bullet[Count].Lvert[3][0].v = 0;
	Q_Bullet->Bullet[Count].Lvert[3][0].x = Q_Bullet->Bullet[Count].VertB1.x;
	Q_Bullet->Bullet[Count].Lvert[3][0].y = Q_Bullet->Bullet[Count].VertB1.y;
	Q_Bullet->Bullet[Count].Lvert[3][0].z = Q_Bullet->Bullet[Count].VertB1.z;
	Q_Bullet->Bullet[Count].Lvert[3][1].u = 0;
	Q_Bullet->Bullet[Count].Lvert[3][1].v = 0;
	Q_Bullet->Bullet[Count].Lvert[3][1].x = Q_Bullet->Bullet[Count].VertB2.x;
	Q_Bullet->Bullet[Count].Lvert[3][1].y = Q_Bullet->Bullet[Count].VertB2.y;
	Q_Bullet->Bullet[Count].Lvert[3][1].z = Q_Bullet->Bullet[Count].VertB2.z;
	Q_Bullet->Bullet[Count].Lvert[3][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[3][2].v = 1;
	Q_Bullet->Bullet[Count].Lvert[3][2].x = Q_Bullet->Bullet[Count].VertF2.x;
	Q_Bullet->Bullet[Count].Lvert[3][2].y = Q_Bullet->Bullet[Count].VertF2.y;
	Q_Bullet->Bullet[Count].Lvert[3][2].z = Q_Bullet->Bullet[Count].VertF2.z;
	Q_Bullet->Bullet[Count].Lvert[3][3].u = 1;
	Q_Bullet->Bullet[Count].Lvert[3][3].v = 1;
	Q_Bullet->Bullet[Count].Lvert[3][3].x = Q_Bullet->Bullet[Count].VertF1.x;
	Q_Bullet->Bullet[Count].Lvert[3][3].y = Q_Bullet->Bullet[Count].VertF1.y;
	Q_Bullet->Bullet[Count].Lvert[3][3].z = Q_Bullet->Bullet[Count].VertF1.z;


	//Strip2
	Q_Bullet->Bullet[Count].Lvert[4][0].u = 1;
	Q_Bullet->Bullet[Count].Lvert[4][0].v = 0;
	Q_Bullet->Bullet[Count].Lvert[4][0].x = Q_Bullet->Bullet[Count].VertB2.x;
	Q_Bullet->Bullet[Count].Lvert[4][0].y = Q_Bullet->Bullet[Count].VertB2.y;
	Q_Bullet->Bullet[Count].Lvert[4][0].z = Q_Bullet->Bullet[Count].VertB2.z;
	Q_Bullet->Bullet[Count].Lvert[4][1].u = 0;
	Q_Bullet->Bullet[Count].Lvert[4][1].v = 0;
	Q_Bullet->Bullet[Count].Lvert[4][1].x = Q_Bullet->Bullet[Count].VertB3.x;
	Q_Bullet->Bullet[Count].Lvert[4][1].y = Q_Bullet->Bullet[Count].VertB3.y;
	Q_Bullet->Bullet[Count].Lvert[4][1].z = Q_Bullet->Bullet[Count].VertB3.z;
	Q_Bullet->Bullet[Count].Lvert[4][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[4][2].v = 1;
	Q_Bullet->Bullet[Count].Lvert[4][2].x = Q_Bullet->Bullet[Count].VertF3.x;
	Q_Bullet->Bullet[Count].Lvert[4][2].y = Q_Bullet->Bullet[Count].VertF3.y;
	Q_Bullet->Bullet[Count].Lvert[4][2].z = Q_Bullet->Bullet[Count].VertF3.z;
	Q_Bullet->Bullet[Count].Lvert[4][3].u = 1;
	Q_Bullet->Bullet[Count].Lvert[4][3].v = 1;
	Q_Bullet->Bullet[Count].Lvert[4][3].x = Q_Bullet->Bullet[Count].VertF2.x;
	Q_Bullet->Bullet[Count].Lvert[4][3].y = Q_Bullet->Bullet[Count].VertF2.y;
	Q_Bullet->Bullet[Count].Lvert[4][3].z = Q_Bullet->Bullet[Count].VertF2.z;


	//Strip3
	Q_Bullet->Bullet[Count].Lvert[5][0].u = 1;
	Q_Bullet->Bullet[Count].Lvert[5][0].v = 0;
	Q_Bullet->Bullet[Count].Lvert[5][0].x = Q_Bullet->Bullet[Count].VertB3.x;
	Q_Bullet->Bullet[Count].Lvert[5][0].y = Q_Bullet->Bullet[Count].VertB3.y;
	Q_Bullet->Bullet[Count].Lvert[5][0].z = Q_Bullet->Bullet[Count].VertB3.z;
	Q_Bullet->Bullet[Count].Lvert[5][1].u = 0;
	Q_Bullet->Bullet[Count].Lvert[5][1].v = 0;
	Q_Bullet->Bullet[Count].Lvert[5][1].x = Q_Bullet->Bullet[Count].VertB4.x;
	Q_Bullet->Bullet[Count].Lvert[5][1].y = Q_Bullet->Bullet[Count].VertB4.y;
	Q_Bullet->Bullet[Count].Lvert[5][1].z = Q_Bullet->Bullet[Count].VertB4.z;
	Q_Bullet->Bullet[Count].Lvert[5][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[5][2].v = 1;
	Q_Bullet->Bullet[Count].Lvert[5][2].x = Q_Bullet->Bullet[Count].VertF4.x;
	Q_Bullet->Bullet[Count].Lvert[5][2].y = Q_Bullet->Bullet[Count].VertF4.y;
	Q_Bullet->Bullet[Count].Lvert[5][2].z = Q_Bullet->Bullet[Count].VertF4.z;
	Q_Bullet->Bullet[Count].Lvert[5][3].u = 1;
	Q_Bullet->Bullet[Count].Lvert[5][3].v = 1;
	Q_Bullet->Bullet[Count].Lvert[5][3].x = Q_Bullet->Bullet[Count].VertF3.x;
	Q_Bullet->Bullet[Count].Lvert[5][3].y = Q_Bullet->Bullet[Count].VertF3.y;
	Q_Bullet->Bullet[Count].Lvert[5][3].z = Q_Bullet->Bullet[Count].VertF3.z;


	//Strip4
	Q_Bullet->Bullet[Count].Lvert[6][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[6][0].v = 0;
	Q_Bullet->Bullet[Count].Lvert[6][0].x = Q_Bullet->Bullet[Count].VertB4.x;
	Q_Bullet->Bullet[Count].Lvert[6][0].y = Q_Bullet->Bullet[Count].VertB4.y;
	Q_Bullet->Bullet[Count].Lvert[6][0].z = Q_Bullet->Bullet[Count].VertB4.z;
	Q_Bullet->Bullet[Count].Lvert[6][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[6][1].v = 0;
	Q_Bullet->Bullet[Count].Lvert[6][1].x = Q_Bullet->Bullet[Count].VertB5.x;
	Q_Bullet->Bullet[Count].Lvert[6][1].y = Q_Bullet->Bullet[Count].VertB5.y;
	Q_Bullet->Bullet[Count].Lvert[6][1].z = Q_Bullet->Bullet[Count].VertB5.z;
	Q_Bullet->Bullet[Count].Lvert[6][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[6][2].v = 1;
	Q_Bullet->Bullet[Count].Lvert[6][2].x = Q_Bullet->Bullet[Count].VertF5.x;
	Q_Bullet->Bullet[Count].Lvert[6][2].y = Q_Bullet->Bullet[Count].VertF5.y;
	Q_Bullet->Bullet[Count].Lvert[6][2].z = Q_Bullet->Bullet[Count].VertF5.z;
	Q_Bullet->Bullet[Count].Lvert[6][3].u = 1;
	Q_Bullet->Bullet[Count].Lvert[6][3].v = 1;
	Q_Bullet->Bullet[Count].Lvert[6][3].x = Q_Bullet->Bullet[Count].VertF4.x;
	Q_Bullet->Bullet[Count].Lvert[6][3].y = Q_Bullet->Bullet[Count].VertF4.y;
	Q_Bullet->Bullet[Count].Lvert[6][3].z = Q_Bullet->Bullet[Count].VertF4.z;


	//Strip5
	Q_Bullet->Bullet[Count].Lvert[7][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[7][0].v = 0;
	Q_Bullet->Bullet[Count].Lvert[7][0].x = Q_Bullet->Bullet[Count].VertB5.x;
	Q_Bullet->Bullet[Count].Lvert[7][0].y = Q_Bullet->Bullet[Count].VertB5.y;
	Q_Bullet->Bullet[Count].Lvert[7][0].z = Q_Bullet->Bullet[Count].VertB5.z;
	Q_Bullet->Bullet[Count].Lvert[7][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[7][1].v = 0;
	Q_Bullet->Bullet[Count].Lvert[7][1].x = Q_Bullet->Bullet[Count].VertB1.x;
	Q_Bullet->Bullet[Count].Lvert[7][1].y = Q_Bullet->Bullet[Count].VertB1.y;
	Q_Bullet->Bullet[Count].Lvert[7][1].z = Q_Bullet->Bullet[Count].VertB1.z;
	Q_Bullet->Bullet[Count].Lvert[7][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[7][2].v = 1;
	Q_Bullet->Bullet[Count].Lvert[7][2].x = Q_Bullet->Bullet[Count].VertF1.x;
	Q_Bullet->Bullet[Count].Lvert[7][2].y = Q_Bullet->Bullet[Count].VertF1.y;
	Q_Bullet->Bullet[Count].Lvert[7][2].z = Q_Bullet->Bullet[Count].VertF1.z;
	Q_Bullet->Bullet[Count].Lvert[7][3].u = 1;
	Q_Bullet->Bullet[Count].Lvert[7][3].v = 1;
	Q_Bullet->Bullet[Count].Lvert[7][3].x = Q_Bullet->Bullet[Count].VertF5.x;
	Q_Bullet->Bullet[Count].Lvert[7][3].y = Q_Bullet->Bullet[Count].VertF5.y;
	Q_Bullet->Bullet[Count].Lvert[7][3].z = Q_Bullet->Bullet[Count].VertF5.z;


	//## Front Tris ##

	Q_Bullet->Bullet[Count].Lvert[8][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[8][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[8][0].x = Q_Bullet->Bullet[Count].VertF1.x;
	Q_Bullet->Bullet[Count].Lvert[8][0].y = Q_Bullet->Bullet[Count].VertF1.y;
	Q_Bullet->Bullet[Count].Lvert[8][0].z = Q_Bullet->Bullet[Count].VertF1.z;
	Q_Bullet->Bullet[Count].Lvert[8][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[8][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[8][1].x = Q_Bullet->Bullet[Count].VertF2.x;
	Q_Bullet->Bullet[Count].Lvert[8][1].y = Q_Bullet->Bullet[Count].VertF2.y;
	Q_Bullet->Bullet[Count].Lvert[8][1].z = Q_Bullet->Bullet[Count].VertF2.z;
	Q_Bullet->Bullet[Count].Lvert[8][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[8][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[8][2].x = Q_Bullet->Bullet[Count].VertFP.x;
	Q_Bullet->Bullet[Count].Lvert[8][2].y = Q_Bullet->Bullet[Count].VertFP.y;
	Q_Bullet->Bullet[Count].Lvert[8][2].z = Q_Bullet->Bullet[Count].VertFP.z;


	Q_Bullet->Bullet[Count].Lvert[9][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[9][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[9][0].x = Q_Bullet->Bullet[Count].VertF2.x;
	Q_Bullet->Bullet[Count].Lvert[9][0].y = Q_Bullet->Bullet[Count].VertF2.y;
	Q_Bullet->Bullet[Count].Lvert[9][0].z = Q_Bullet->Bullet[Count].VertF2.z;
	Q_Bullet->Bullet[Count].Lvert[9][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[9][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[9][1].x = Q_Bullet->Bullet[Count].VertF3.x;
	Q_Bullet->Bullet[Count].Lvert[9][1].y = Q_Bullet->Bullet[Count].VertF3.y;
	Q_Bullet->Bullet[Count].Lvert[9][1].z = Q_Bullet->Bullet[Count].VertF3.z;
	Q_Bullet->Bullet[Count].Lvert[9][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[9][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[9][2].x = Q_Bullet->Bullet[Count].VertFP.x;
	Q_Bullet->Bullet[Count].Lvert[9][2].y = Q_Bullet->Bullet[Count].VertFP.y;
	Q_Bullet->Bullet[Count].Lvert[9][2].z = Q_Bullet->Bullet[Count].VertFP.z;


	Q_Bullet->Bullet[Count].Lvert[10][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[10][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[10][0].x = Q_Bullet->Bullet[Count].VertF3.x;
	Q_Bullet->Bullet[Count].Lvert[10][0].y = Q_Bullet->Bullet[Count].VertF3.y;
	Q_Bullet->Bullet[Count].Lvert[10][0].z = Q_Bullet->Bullet[Count].VertF3.z;
	Q_Bullet->Bullet[Count].Lvert[10][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[10][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[10][1].x = Q_Bullet->Bullet[Count].VertF4.x;
	Q_Bullet->Bullet[Count].Lvert[10][1].y = Q_Bullet->Bullet[Count].VertF4.y;
	Q_Bullet->Bullet[Count].Lvert[10][1].z = Q_Bullet->Bullet[Count].VertF4.z;
	Q_Bullet->Bullet[Count].Lvert[10][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[10][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[10][2].x = Q_Bullet->Bullet[Count].VertFP.x;
	Q_Bullet->Bullet[Count].Lvert[10][2].y = Q_Bullet->Bullet[Count].VertFP.y;
	Q_Bullet->Bullet[Count].Lvert[10][2].z = Q_Bullet->Bullet[Count].VertFP.z;


	Q_Bullet->Bullet[Count].Lvert[11][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[11][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[11][0].x = Q_Bullet->Bullet[Count].VertF4.x;
	Q_Bullet->Bullet[Count].Lvert[11][0].y = Q_Bullet->Bullet[Count].VertF4.y;
	Q_Bullet->Bullet[Count].Lvert[11][0].z = Q_Bullet->Bullet[Count].VertF4.z;
	Q_Bullet->Bullet[Count].Lvert[11][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[11][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[11][1].x = Q_Bullet->Bullet[Count].VertF5.x;
	Q_Bullet->Bullet[Count].Lvert[11][1].y = Q_Bullet->Bullet[Count].VertF5.y;
	Q_Bullet->Bullet[Count].Lvert[11][1].z = Q_Bullet->Bullet[Count].VertF5.z;
	Q_Bullet->Bullet[Count].Lvert[11][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[11][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[11][2].x = Q_Bullet->Bullet[Count].VertFP.x;
	Q_Bullet->Bullet[Count].Lvert[11][2].y = Q_Bullet->Bullet[Count].VertFP.y;
	Q_Bullet->Bullet[Count].Lvert[11][2].z = Q_Bullet->Bullet[Count].VertFP.z;


	Q_Bullet->Bullet[Count].Lvert[12][0].u = 0;
	Q_Bullet->Bullet[Count].Lvert[12][0].v = 1;
	Q_Bullet->Bullet[Count].Lvert[12][0].x = Q_Bullet->Bullet[Count].VertF5.x;
	Q_Bullet->Bullet[Count].Lvert[12][0].y = Q_Bullet->Bullet[Count].VertF5.y;
	Q_Bullet->Bullet[Count].Lvert[12][0].z = Q_Bullet->Bullet[Count].VertF5.z;
	Q_Bullet->Bullet[Count].Lvert[12][1].u = 1;
	Q_Bullet->Bullet[Count].Lvert[12][1].v = 1;
	Q_Bullet->Bullet[Count].Lvert[12][1].x = Q_Bullet->Bullet[Count].VertF1.x;
	Q_Bullet->Bullet[Count].Lvert[12][1].y = Q_Bullet->Bullet[Count].VertF1.y;
	Q_Bullet->Bullet[Count].Lvert[12][1].z = Q_Bullet->Bullet[Count].VertF1.z;
	Q_Bullet->Bullet[Count].Lvert[12][2].u = 1;
	Q_Bullet->Bullet[Count].Lvert[12][2].v = 0;
	Q_Bullet->Bullet[Count].Lvert[12][2].x = Q_Bullet->Bullet[Count].VertFP.x;
	Q_Bullet->Bullet[Count].Lvert[12][2].y = Q_Bullet->Bullet[Count].VertFP.y;
	Q_Bullet->Bullet[Count].Lvert[12][2].z = Q_Bullet->Bullet[Count].VertFP.z;


	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[0][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[1][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[2][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);

	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[3][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[4][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[5][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[6][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[7][0], 4, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);

	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[8][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[9][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[10][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[11][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);
	Qpo->Poly_AddOnce(&Q_Bullet->Bullet[Count].Lvert[12][0], 3, NULL, Q_Bullet->Bullet[Count].Type, Q_Bullet->Bullet[Count].RenderFlags, Q_Bullet->Bullet[Count].ScaleBIT);

	return true;
}

};