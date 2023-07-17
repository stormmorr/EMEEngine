/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -WEE Control Script-

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
#include "Q-ENE-EnergyTypes.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-BulletSystem.h"

#include "Q-WE-ShellATypes.h"

#include "Q-ShellAPrototypes.h"

#include "../../UnSRC/QActiveFramewrk.h"

extern QAGE::QActiveFramewrk* QActiveFrameWork;

using namespace GVARS;

namespace GVARS
{

void Q_COREFunctions::World_Event_Engine(void)
	{
	if(g_NetConnect)
		{
		_->NetworkOption = 1;
		}

			   /*********************************************************
		---------------<<{{{{[ WORLD EVENT ENGINE ]}}}}>>---------------
		   *********************************************************/

	//####### ALL SPECIAL EFFECTS

	//########  - Player TRAIL LINES Trails System Trail System Trails Control-  ########//

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		//***********
		Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPos);
		Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L HAND", &player[g_Player]->LFistPos);

		Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV, true);
		Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 L HAND", &player[g_Player]->LFistPosV, true);

		if(player[g_Player]->NomTrailL > 0)
			{
			helly = 0;
			while(helly < player[g_Player]->NomTrailL)
				{
				if(player[g_Player]->Trail[helly].Live == 1)
					{
					Q_EFFControl.TrailLine_PlayerFrame(helly);
					}
				helly++;
				}
			}
		}


	SCRAM = 0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].NomTrailL > 0)
				{
				helly = 0;
				while(helly < Q_Forge->Forge[SCRAM].NomTrailL)
					{
					if(Q_Forge->Forge[SCRAM].Trail[helly].Live == 1)
						{
						Q_EFFControl.TrailLine_AvatarFrame(SCRAM, helly);
						}
					helly++;
					}
				}
			}
		SCRAM++;
		}


	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		Q.CONTROL_PlayerPowerFlight();
		}

	SCRAM = 0;
	while(SCRAM < _->NomAI)
		{
		Q.CONTROL_AvatarPowerFlight(SCRAM);
		SCRAM++;
		}


	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(player[g_Player]->AJPushOffON == 1 && player[g_Player]->AJPushOff.Done == 0)	//## Push Off Expandro
			{
			Q.PlayerJumpEffect();
			}
		}

	SCRAM = 0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].AJPushOffON == 1 && Q_Forge->Forge[SCRAM].AJPushOff.Done == 0)	//## Push Off Expandro
				{
				Q.AvatarJumpEffect(SCRAM);
				}
			}
		SCRAM++;
		}

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(player[g_Player]->JinkBLAST > 0)
			{
			Q.PlayerJinkBlast();
			}
		}


	jet=0;
	while(jet < _->NomAI)
		{
		if(Q_Forge->Forge[jet].LIVE == 1)
			{
			if(Q_Forge->Forge[jet].JinkBLAST > 0)
				{
				Q.AvatarJinkBlast(jet);
				}
			}
		jet++;
		}


	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(player[g_Player]->JinkRUSHCLOUD == 1)
			{
			Q.PlayerJinkRushCloud();
			}
		}

	
	//##### MATRIX ALTERATIONS

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;
		
		if(_->NetworkOption != 1)
			{
			if(player[g_Player]->EnergyArchitect.AffectMatrixON == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE != 250)
				{
				Q_EnergyMatrix->EnergyMatrix.PlayerAffectMatrix();
				}
			}
		}


	//avatar loop check
	if(_->NetworkOption != 1)
		{
		SCRAMJET=0;
		while(SCRAMJET < _->NomAI)
			{
			if(Q_Forge->Forge[SCRAMJET].EnergyArchitect.AffectMatrixON == 1 && Q_Forge->Forge[SCRAMJET].CharDATA.CurrZCAPTURE != 250)
				{
				Q_EnergyMatrix->EnergyMatrix.AvatarAffectMatrix(SCRAMJET);
				}
			SCRAMJET++;
			}
		}

	//##### ENERGY MATRIX CONTROL

	Q_EnergyMatrix->EnergyMatrix.ZoneControl();

	Q_EnergyMatrix->EnergyMatrix.ZoneExitCheck();

	Q_EnergyMatrix->EnergyMatrix.TimeScaleReset();

	if(_->NomVaporTrails > 0)
		{
		aero = 0;
		while(aero < _->NomVaporTrails)
			{
			if(Q_VaporTrail->VaporTrail[aero].Live == 1)
				{
				Q_EFFControl.VaporTrail_ControlFrame(aero);
				}
			aero++;
			}
		}


	//#### Q_Sentry Frames ####//
	if(_->NomBMSentry > 0)
		{
		SCRAM=0;
		while(SCRAM < _->NomBMSentry)
			{
			if(Q_BMSentry->BMSentry[SCRAM].LIVE == 1)
				{
				Q_EFFControl.BMSentry_ControlFrame(SCRAM);
				}
			SCRAM++;
			}
		}

	//#### Q_Building Frames ####//
	if(_->NomBuilding > 0)
		{
		SCRAM=0;
		while(SCRAM < _->NomBuilding)
			{
			if(Q_Building->Building[SCRAM].LIVE == 1)
				{
				Q_EFFControl.Building_ControlFrame(SCRAM);
				}

			SCRAM++;
			}
		}

	//#### Q_VoxelDamage Frames ####//
	if(Q_VoxelDamage->m_vec_VoxelDamageMask.size() > 0)
		{
		SCRAM=0;
		while(SCRAM < Q_VoxelDamage->m_vec_VoxelDamageMask.size())
			{
			std::shared_ptr<VoxelDamageMask> f_DMG_Mask = Q_VoxelDamage->m_vec_VoxelDamageMask[SCRAM];

			if(f_DMG_Mask->acSimulateFrame(_->TimeScale) == true)
				{
				for(int f_XY = SCRAM; f_XY < Q_VoxelDamage->m_vec_VoxelDamageMask.size() - 1; f_XY++)
					{
					Q_VoxelDamage->m_vec_VoxelDamageMask[f_XY] = Q_VoxelDamage->m_vec_VoxelDamageMask[f_XY + 1];
					}

				Q_VoxelDamage->m_vec_VoxelDamageMask.pop_back();
				}
			else
				{
				SCRAM++;
				}
			}
		}


	//########  - CLERIC PLASMA ENERGY TRANSFER CONTROL -  ########//
#if 0
	if(_->NetworkOption != 1)
		{
		if(_->NomPlasma > 0)
			{
			aero = 0;
			while(aero < _->NomPlasma)
				{
				if(Q_ClericPlasma->ClericPlasma[aero].Live == 1)
					{
					Q_EFFControl.ClericPlasma_ServerFrame(aero);
					}//End Live
				aero++;
				}
			}
		}
	else		//#### Phantom Cleric Plasma
		{
		if(_->NomPlasma > 0)
			{
			aero = 0;
			while(aero < _->NomPlasma)
				{
				if(Q_ClericPlasma->ClericPlasma[aero].Live == 1)
					{
					Q_EFFControl.ClericPlasma_ClientFrame(aero);
					}
				aero++;
				}
			}
		}
#endif

	//##### Point Sprite MANAGEMENT

	Q.PntSpriteManagement();

#if 0 //WORLD EVENT ENGINE - Point Sprite Control
	if(_->NomPntSprite > 0)
		{
		_->TempNomPntSprite = _->NomPntSprite;
		helly = 0;
		while(helly < _->TempNomPntSprite)
			{
			if(Q_PntSprite->PntSprite[helly].Live == 1)
				{
				Q_EFFControl.PntSprite_ControlFrame(helly);
				}
			helly++;
			}
		}
#else
	_->NomPntSprite = 0;
#endif

	//WORLD EVENT ENGINE - Melee Hits System

	if((_->NomMelHitPRPR > 0) || (_->NomMelHit > 0))
		{
		int f_MeleeNom;
		if(_->NomMelHitPRPR > _->NomMelHit) f_MeleeNom = _->NomMelHitPRPR;
		else f_MeleeNom = _->NomMelHit;

		aero = 0;
		while(aero < f_MeleeNom)
			{
			if(aero >= 0 && aero < 2500)
				{
				if(Q_MeleeHit->MeleeHit[aero].Live == 1)		//HIT is live
					{
					if(Q_MeleeHit->MeleeHit[aero].NetFlag == 0)
						{
						Q_EFFControl.MeleeHit_ControlServer(aero);
						}
					else
						{
						Q_EFFControl.MeleeHit_ControlClient(aero);
						}
					}
				}

			aero++;
			}
		}

	//###### BULLET HITS ######
#if 1
	if(_->NomBulHitPRPR > 0 || _->NomBulHit > 0)
		{
		int f_BulHitNom;
		if(_->NomBulHitPRPR > _->NomBulHit) f_BulHitNom = _->NomBulHitPRPR;
		else f_BulHitNom = _->NomBulHit;

		aero = 0;
		while(aero < f_BulHitNom)
			{
			if(aero >= 0 && aero < 2500)
				{
				if(Q_BulletHit->BulletHit[aero].Live == 1)		//HIT is live
					{
					if(Q_BulletHit->BulletHit[aero].NetFlag == 0)
						{
						Q_EFFControl.BulletHit_ControlServer(aero);
						}
					else
						{
						Q_EFFControl.BulletHit_ControlClient(aero);
						}
					}
				}
			aero++;
			}
		}
#endif

	//#### SMALL ENERGY ATTACKS
#if 1
	if(_->NomSEnergyPRPR > 0 || _->NomSEnergy > 0)
		{
		int f_SEnergyNom;
		if(_->NomSEnergyPRPR > _->NomSEnergy) f_SEnergyNom = _->NomSEnergyPRPR;
		else f_SEnergyNom = _->NomSEnergy;

		aero = 0;
		while(aero < f_SEnergyNom)
			{					// _->MaxNomSEnergy
			if(aero >= 0 && aero < 2500)	//Attack is live
				{
				if(Q_SEnergy->SEnergy[aero].Live == 1)
					{
					if(Q_SEnergy->SEnergy[aero].NetFlag == 0)
						{
						Q_EFFControl.SEnergy_Renzou_ServerFrame(aero);
						}
					else
						{
						Q_EFFControl.SEnergy_Renzou_ClientFrame(aero);
						}
					}
				}
			aero++;
			}
		}
#endif

	//#### POWER BLADE ATTACKS
#if 0
	if(_->NetworkOption != 1)
		{
		if(_->NomPowerBlade > 0)
			{
			aero = 0;
			while(aero < _->NomPowerBlade)
				{
				if(Q_PowerBlade->PowerBlade[aero].Live == 1 && aero < _->MaxNomPowerBlade)	//Attack is live
					{
					Q_EFFControl.SEnergy_PowerBlade_ServerFrame(aero);
					}
				aero++;
				}
			}
		}
	else
		{
		if(_->NomPowerBlade > 0)
			{
			aero = 0;
			while(aero < _->NomPowerBlade)
				{
				if(Q_PowerBlade->PowerBlade[aero].Live == 1 && aero < _->MaxNomPowerBlade)	//Attack is live
					{
					Q_EFFControl.SEnergy_PowerBlade_ClientFrame(aero);
					}
				aero++;
				}
			}
		}
#endif

#if 0
	//#### VALID POINTERS
	if(NomValidPointer > 0)
		{
		aero = 0;
		while(aero < NomValidPointer)
			{
			if(Q_ValidPointer->ValidPointer[aero].Live == 1 && aero < MaxNomValidPointer)	//Attack is live
				{
				//Q_ShellA.ValidPointer_Frame(aero);
				}
			aero++;
			}
		}

	//##### SMALL ENERGY MANAGEMENT
	if(_->NomSEnergy >= _->MaxNomSEnergy) _->NomSEnergy = _->MaxNomSEnergy;
#endif

#if 1
	aero = 0;
	while(aero < _->NomSEnergy)
		{
		if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &Q_SEnergy->SEnergy[aero].LightPos) > 1000)
			{
			Q_SEnergy->SEnergy[aero].Live = 0;
			if(Q_SEnergy->SEnergy[aero].Light != NULL) Qpo->Light_Remove(Q_SEnergy->SEnergy[aero].Light);
			if(Q_SEnergy->SEnergy[aero].Sound != NULL) Qpo->Sound_Stop(Q_SEnergy->SEnergy[aero].Sound);

			helly = 0;
			while(helly < Q_SEnergy->SEnergy[aero].NomActors)
				{
				Qpo->Vec3d_Copy(&_->Origon, &Q_SEnergy->SEnergy[aero].AvatarFlag[helly].Xform.Translation);
				helly++;
				}

			//### Energy Array Reorder
			int K = aero;
			while(K < _->NomSEnergy - 1)
				{
				Q_SEnergy->SEnergy[K] = Q_SEnergy->SEnergy[K+1];
				K++;
				}

			_->NomSEnergy--;
			}

		aero++;
		}
#endif

	//######## HADOUKEN BLAST #######
#if 1
	if(_->NomLEnergyPRPR > 0 || _->NomLEnergy > 0)
		{
		int f_LEnergyNom;
		if(_->NomLEnergyPRPR > _->NomSEnergy) f_LEnergyNom = _->NomLEnergyPRPR;
		else f_LEnergyNom = _->NomLEnergy;

		aero = 0;
		while(aero < f_LEnergyNom)
			{
			if(aero >= 0 && aero < 2500)
				{
				if(Q_LEnergy->LEnergy[aero].Live == 1)	//Attack is live
					{
					if(Q_LEnergy->LEnergy[aero].NetFlag == 0)
						{
						Q_EFFControl.LEnergy_ServerFrame(aero);
						}
					else
						{
						Q_EFFControl.LEnergy_ClientFrame(aero);
						}
					}
				}//END areo range chk
			aero++;
			}//END Aero
		}//END _->NomLEnergy
#endif

		//##### LARGE ENERGY MANAGEMENT
#if 1
	if(_->NetworkOption != 1)
		{
		aero = 0;
		while(aero < _->NomLEnergy)
			{
			if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation) > 5000)
				{
				Qpo->Light_Remove(Q_LEnergy->LEnergy[aero].Light);
				Q_LEnergy->LEnergy[aero].Init = 0;
				Q_LEnergy->LEnergy[aero].Live = 0;
				Q_LEnergy->LEnergy[aero].EnergyLive = 0;
				Q_LEnergy->LEnergy[aero].EnergyFire = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[aero].EnergyBall, 0,0,0);
				Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[aero].EnergyBall, 0);

				//### Energy Array Reorder
				int K = aero;
				while(K < _->NomLEnergy - 1)
					{
					Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
					K++;
					}

				_->NomLEnergy--;
				}

			aero++;
			}
		}
	else
		{
		aero = 0;
		while(aero < _->NomLEnergy)
			{
			if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation) > 5000)
				{
				Qpo->Light_Remove(Q_LEnergy->LEnergy[aero].Light);
				Q_LEnergy->LEnergy[aero].Init = 0;
				Q_LEnergy->LEnergy[aero].Live = 0;
				Q_LEnergy->LEnergy[aero].EnergyLive = 0;
				Q_LEnergy->LEnergy[aero].EnergyFire = 0;
				Qpo->Vec3d_Copy(&_->Origon, &Q_LEnergy->LEnergy[aero].EnergyBall.Xform.Translation);
				Qpo->Mesh_SetScale(&Q_LEnergy->LEnergy[aero].EnergyBall, 0,0,0);
				Qpo->Mesh_SetAlpha(&Q_LEnergy->LEnergy[aero].EnergyBall, 0);

				//### Energy Array Reorder
				int K = aero;
				while(K < _->NomLEnergy - 1)
					{
					Q_LEnergy->LEnergy[K] = Q_LEnergy->LEnergy[K+1];
					K++;
					}

				_->NomLEnergy--;
				}

			aero++;
			}
		}
#endif

	//########  - EXPLOSIONS -  ########//
#if 1
	if(_->NomExplosionsPRPR > 0 || _->NomExplosions > 0)
		{
		int f_ExplosionsNom;
		if(_->NomExplosionsPRPR > _->NomExplosions) f_ExplosionsNom = _->NomExplosionsPRPR;
		else f_ExplosionsNom = _->NomExplosions;

		aero = 0;
		while(aero < f_ExplosionsNom)
			{
			if(aero >= 0 && aero < 2500)
				{
				if(Q_Explosion->Explosion[aero].Live == 1)
					{
					if(Q_Explosion->Explosion[aero].NetFlag == 0)
						{
						Q_EFFControl.Explosion_ServerFrame(aero);
						}
					else
						{
						Q_EFFControl.Explosion_ClientFrame(aero);
						}
					} //~LIVE
				}
			aero++;
			}
		}
#endif

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		
		//#### Player Muzzle Flash
		Q.CONTROL_PlayerMuzzleFlash();
		}

#if 1
	//#### BULLET CARTRIDGES
	if(_->NomCart > 0)
		{
		aero = 0;
		while(aero < _->NomCart)
			{
			if(Q_Cartridge->Cartridge[aero].Live == 1) //MOVEMENT
				{
				Q_EFFControl.Cartridge_ControlFrame(aero);
				}
			aero++;
			}
		}
#else
	_->NomCart = 0;
#endif

	//##### CLOUD MANAGEMENT
#if 1
	if(_->NomCloud > 0)
		{
		aero = 0;
		while(aero < _->NomCloud)
			{
			if(aero < Q_Cloud->m_ArrayMx)
				{
				if(Q_Cloud->Cloud[aero].CloudLive == 1)
					{
					Q_EFFControl.Cloud_ControlFrame(aero);
					}//~LIVE
				}

			aero++;
			}
		}
#else
	_->NomCloud = 0;
#endif

	Q.CloudManagement();


	//########  - 3D Sparks System -  ########//
#if 1
	if(_->NomSparks > 0)
		{
		helly = 0;
		while(helly < _->NomSparks)
			{
			if(Q_BSparks->BSparks[helly].Live == 1)
				{
				Q_EFFControl.Spark_SparkFrame(helly);
				}
			helly += 1;
			}
		}
#else
	_->NomSparks = 0;
#endif


	//########  - 3D Power Flash System -  ########//
#if 1
	if(_->NomPowerFlash > 0)
		{
		helly = 0;
		while(helly < _->NomPowerFlash)
			{
			if(Q_PowerFlash->PowerFlash[helly].Live == 1)
				{
				Q_EFFControl.PowerFlash_ControlFrame(helly);
				}
			helly += 1;
			}
		}
#else
	_->NomPowerFlash = 0;
#endif

		//########  - 3D Heal Sparks System -  ########//
#if 1
	if(_->NetworkOption != 1)
		{
		if(_->NomHSpark > 0)
			{
			helly = 0;
			while(helly < _->NomHSpark)
				{
				if(Q_HealSpark->HealSpark[helly].Live == 1)
					{
					Q_EFFControl.HSpark_ServerFrame(helly);
					}
				helly++;
				}
			}
		}
	else	//##### Phantom Client Heal Sparks
		{
		if(_->NomHSpark > 0)
			{
			helly = 0;
			while(helly < _->NomHSpark)
				{
				if(Q_HealSpark->HealSpark[helly].Live == 1)
					{
					Q_EFFControl.HSpark_ClientFrame(helly);
					}
				helly++;
				}
			}
		}
#else
	_->NomHSpark = 0;
#endif

	//########  - Spike System -  ########//
#if 1
	if(_->NomSpikes > 0)
		{
		helly = 0;
		while(helly < _->NomSpikes)
			{
			if(Q_HHSpike->HHSpike[helly].Live == 1)
				{
				Q_EFFControl.Spike_ControlFrame(helly);
				}
			helly++;
			}
		}
#endif

	//####- SINGLE PLAYER AND SERVER BULLET SYSTEM -####

#ifdef USE_CAPSULES
	//###-- Apply Capsule to all players and AI --###//
	//___Player Capsule
	if(QAGE::g_PlayerForgeBoxxed == true)
		{
		if(player[g_Player]->WeaponStatus == 0) player[g_Player]->CamMatrix.Translation.y = playerAV[g_Player]->Xform.Translation.y + 20 + 25;
		else player[g_Player]->CamMatrix.Translation.y = playerAV[g_Player]->Xform.Translation.y + 20 + 25 + 30;
		player[g_Player]->CamMatrix.Translation.y *= player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (0.16*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));

		PxTransform f_Transform = g_ForgeBoxplayer[g_Player]->getGlobalPose();
		f_Transform.p = PxVec3(playerAV[g_Player]->Xform.Translation.x, player[g_Player]->CamMatrix.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		g_ForgeBoxplayer[g_Player]->setGlobalPose(f_Transform, true);

		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);
		glColor3f(0.0f, 1.0f, 0.0f);
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);
		QActiveFrameWork->DigiMass->acRenderBox(g_ForgeBoxPlayer, 135, 50);
		}

	//___Avatar Capsule
	for(int hellyjet = 0; hellyjet < _->NomAI; hellyjet++)
		{
		if(Q_Forge->Forge[hellyjet].LIVE == 1 && Q_Forge->Forge[hellyjet].HB_Dead == 0)
			{
			if(Q_Forge->Forge[hellyjet].WeaponStatus == 0) player[g_Player]->CamMatrix.Translation.y = Q_Forge->Forge[hellyjet].AV.Xform.Translation.y + 20 + 25;
			else player[g_Player]->CamMatrix.Translation.y = Q_Forge->Forge[hellyjet].AV.Xform.Translation.y + 20 + 25 + 30;
			player[g_Player]->CamMatrix.Translation.y *= Q_Forge->Forge[hellyjet].CharDATA.AvatarSCALE + (0.16*(((Q_Forge->Forge[hellyjet].CharDATA.BodySKILL.Height/100)-0.5)*2));

			PxTransform f_Transform = g_ForgeBox[hellyjet]->getGlobalPose();
			f_Transform.p = PxVec3(Q_Forge->Forge[hellyjet].AV.Xform.Translation.x, player[g_Player]->CamMatrix.Translation.y, Q_Forge->Forge[hellyjet].AV.Xform.Translation.z);
			g_ForgeBox[hellyjet]->setGlobalPose(f_Transform, true);
			PxTransform f_TransformG = g_ForgeBox[hellyjet]->getGlobalPose();
			printf("hellyjet %i f_TransformG.p %f %f %f\n", hellyjet, f_TransformG.p.x, f_TransformG.p.y, f_TransformG.p.z);

			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);
			glColor3f(0.0f, 1.0f, 0.0f);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
			glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
			glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
			glEnable(GL_TEXTURE_2D);
			QActiveFrameWork->DigiMass->acRenderBox(g_ForgeBox[hellyjet], 135, 50);
			}
		}
#endif

#if 1
	if(_->NomBulletPRPR > 0 || _->NomBullet > 0)
		{
		int f_BulletNom;
		if(_->NomBulletPRPR > _->NomBullet) f_BulletNom = _->NomBulletPRPR;
		else f_BulletNom = _->NomBullet;

		aero = 0;
		while(aero < f_BulletNom)
			{
			if(aero >= 0 && aero < 150000)
				{
				if(Q_Bullet->Bullet[aero].Live == 1) //MOVEMENT
					{
					if(Q_Bullet->Bullet[aero].NetFlag == 0)
						{
						Q_EFFControl.Bullet_ServerFrame(aero);
						}
					else
						{
						Q_EFFControl.Bullet_ClientFrame(aero);
						}
					}
				}
			aero++;
			}
		}
#endif

#ifdef USE_CAPSULES
	//###-- Apply Capsule to all players and AI --###//
	//___Player Capsule
	if(QAGE::g_PlayerForgeBoxxed == true)
		{
		PxTransform f_Transform = g_ForgeBoxplayer[g_Player]->getGlobalPose();
		f_Transform.p = PxVec3(20000, 20000, 20000);
		g_ForgeBoxplayer[g_Player]->setGlobalPose(f_Transform, true);
		}

	//___Player Capsule
	for(int hellyjet = 0; hellyjet < _->NomAI; hellyjet++)
		{
		if(Q_Forge->Forge[hellyjet].LIVE == 1)
			{
			PxTransform f_Transform = g_ForgeBox[hellyjet]->getGlobalPose();
			f_Transform.p = PxVec3(20000, 20000, 20000);
			g_ForgeBox[hellyjet]->setGlobalPose(f_Transform, true);
			}
		}
#endif

#if 1
	if(_->NetworkOption != 1)
		{
		aero = 0;
		while(aero < _->NomBullet)
			{
			if(Q_Bullet->Bullet[aero].Live == 1) //MOVEMENT
				{
				if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &Q_Bullet->Bullet[aero].WorldPos) > 10000)
					{
					Q_Bullet->Bullet[aero].Live = 0;

					//### Array Reorder
					int K = aero;
					while(K < _->NomBullet - 1)
						{
						Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
						K++;
						}

					_->NomBullet--;
					}
				}

			aero++;
			}
		}
	else
		{
		aero = 0;
		while(aero < _->NomBullet)
			{
			if(Q_Bullet->Bullet[aero].Live == 1) //MOVEMENT
				{
				if(Qpo->Vec3d_DistanceBetween(&playerAV[g_Player]->Xform.Translation, &Q_Bullet->Bullet[aero].WorldPos) > 10000)
					{
					Q_Bullet->Bullet[aero].Live = 0;

					//### Array Reorder
					int K = aero;
					while(K < _->NomBullet - 1)
						{
						Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
						K++;
						}

					_->NomBullet--;
					}
				}

			aero++;
			}
		}
#endif

	//########  - 3D Blood System -  ########//
#if 1
	if(_->NomBlood > 0)
		{
		helly = 0;
		while(helly < _->NomBlood)
			{
			if(Q_BBlood->BBlood[helly].Live == 1)
				{
				Q_EFFControl.Spark_BloodFrame(helly);
				}
			helly++;
			}
		}
#else
	_->NomBlood = 0;
#endif

	//####===---  PLAYER GRAPHICS CONTROL ---===####
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		Q.CONTROL_PlayerGraphicsControl();
		}

	//### Level Manipulation
	helly=0;
	while(helly < _->NomAI)
		{
		if(Q_Forge->Forge[helly].LIVE == 1)
			{
			if(Q_Forge->Forge[helly].LEVEL > 1000) Q_Forge->Forge[helly].LEVELFactor = 1;
			else Q_Forge->Forge[helly].LEVELFactor = (((float)Q_Forge->Forge[helly].LEVEL + 1) / 1000);
			}

		helly++;
		}


	//######## ---[ QUANTUM ANGEL EFFECT MATRIX ]--- ########
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		SCRAM=0;
		while(SCRAM < 7)
			{
#if 0
			if(SCRAM == 0)	//ITEM HEAD ARMOUR
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].ON;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].Red;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].Green;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].Blue;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].Alpha;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[1].Red;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[1].Green;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[1].Blue;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[1].Alpha;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[2].Red;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[2].Green;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[2].Blue;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[2].Alpha;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[3].Red;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[3].Green;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[3].Blue;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[3].Alpha;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[4].Red;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[4].Green;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[4].Blue;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[4].Alpha;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].INT * player[g_Player]->JINK3_PowerFactor;
				}
#endif

			if(SCRAM == 0)	//ITEM HEAD ARMOUR
				{
				player[g_Player]->QA_EFF_SWITCH = 1;

				player[g_Player]->QA_EFF_COL00RED = 255;
				player[g_Player]->QA_EFF_COL00GREEN = 255;
				player[g_Player]->QA_EFF_COL00BLUE = 255;
				player[g_Player]->QA_EFF_COL00ALPHA = 255;

				player[g_Player]->QA_EFF_COL01RED = 255;
				player[g_Player]->QA_EFF_COL01GREEN = 255;
				player[g_Player]->QA_EFF_COL01BLUE = 255;
				player[g_Player]->QA_EFF_COL01ALPHA = 255;

				player[g_Player]->QA_EFF_COL02RED = 255;
				player[g_Player]->QA_EFF_COL02GREEN = 255;
				player[g_Player]->QA_EFF_COL02BLUE = 255;
				player[g_Player]->QA_EFF_COL02ALPHA = 255;

				player[g_Player]->QA_EFF_COL03RED = 255;
				player[g_Player]->QA_EFF_COL03GREEN = 255;
				player[g_Player]->QA_EFF_COL03BLUE = 255;
				player[g_Player]->QA_EFF_COL03ALPHA = 255;

				player[g_Player]->QA_EFF_COL04RED = 255;
				player[g_Player]->QA_EFF_COL04GREEN = 255;
				player[g_Player]->QA_EFF_COL04BLUE = 255;
				player[g_Player]->QA_EFF_COL04ALPHA = 255;

				player[g_Player]->QA_EFF_TYPE = 9;

				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR < 150)
					{
					player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].Effect[0].INT * player[g_Player]->JINK3_PowerFactor;
					}
				}

			if(SCRAM == 1 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR < 150)	//ITEM UPPER ARMOUR
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].ON;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].Red;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].Green;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].Blue;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].Alpha;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[1].Red;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[1].Green;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[1].Blue;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[1].Alpha;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[2].Red;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[2].Green;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[2].Blue;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[2].Alpha;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[3].Red;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[3].Green;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[3].Blue;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[3].Alpha;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[4].Red;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[4].Green;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[4].Blue;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[4].Alpha;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].Effect[0].INT * player[g_Player]->JINK3_PowerFactor;
				}

			if(SCRAM == 2 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR < 150)	//ITEM LOWER ARMOUR
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].ON;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].Red;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].Green;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].Blue;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].Alpha;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[1].Red;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[1].Green;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[1].Blue;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[1].Alpha;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[2].Red;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[2].Green;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[2].Blue;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[2].Alpha;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[3].Red;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[3].Green;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[3].Blue;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[3].Alpha;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[4].Red;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[4].Green;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[4].Blue;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[4].Alpha;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].Effect[0].INT * player[g_Player]->JINK3_PowerFactor;
				}

			if(SCRAM == 3)	//SPELL SLOT 1
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_SWITCH;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].LIVE == 0) player[g_Player]->QA_EFF_SWITCH = 0;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL00RED;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL00GREEN;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL00BLUE;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL00ALPHA;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL01RED;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL01GREEN;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL01BLUE;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL01ALPHA;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL02RED;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL02GREEN;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL02BLUE;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL02ALPHA;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL03RED;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL03GREEN;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL03BLUE;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL03ALPHA;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL04RED;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL04GREEN;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL04BLUE;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_COL04ALPHA;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[0].QA_EFFECT_INTENSITY * player[g_Player]->JINK3_PowerFactor;
				}

			if(SCRAM == 4)	//SPELL SLOT 2
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_SWITCH;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].LIVE == 0) player[g_Player]->QA_EFF_SWITCH = 0;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL00RED;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL00GREEN;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL00BLUE;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL00ALPHA;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL01RED;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL01GREEN;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL01BLUE;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL01ALPHA;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL02RED;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL02GREEN;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL02BLUE;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL02ALPHA;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL03RED;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL03GREEN;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL03BLUE;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL03ALPHA;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL04RED;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL04GREEN;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL04BLUE;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_COL04ALPHA;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[1].QA_EFFECT_INTENSITY * player[g_Player]->JINK3_PowerFactor;
				}

			if(SCRAM == 5)	//SPELL SLOT 3
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_SWITCH;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].LIVE == 0) player[g_Player]->QA_EFF_SWITCH = 0;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL00RED;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL00GREEN;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL00BLUE;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL00ALPHA;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL01RED;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL01GREEN;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL01BLUE;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL01ALPHA;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL02RED;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL02GREEN;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL02BLUE;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL02ALPHA;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL03RED;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL03GREEN;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL03BLUE;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL03ALPHA;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL04RED;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL04GREEN;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL04BLUE;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_COL04ALPHA;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].SpellSLOT[2].QA_EFFECT_INTENSITY * player[g_Player]->JINK3_PowerFactor;
				}

			if(SCRAM == 6 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON >= 0 && player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON < 150)	//ITEM CURRENT WEAPON
				{
				player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].ON;

				player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Red;
				player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Green;
				player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Blue;
				player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Alpha;

				player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Red;
				player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Green;
				player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Blue;
				player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Alpha;

				player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Red;
				player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Green;
				player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Blue;
				player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Alpha;

				player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Red;
				player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Green;
				player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Blue;
				player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Alpha;

				player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Red;
				player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Green;
				player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Blue;
				player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Alpha;

				player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].TYPE;
				player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].INT * player[g_Player]->JINK3_PowerFactor;
				}

			if(player[g_Player]->QA_EFF_SWITCH == 1)
				{
				Q.QAEFFcontrolPLAYER(player[g_Player]->QA_EFF_TYPE, player[g_Player]->QA_EFF_INTENSITY, player[g_Player]->QA_EFF_COL00RED, player[g_Player]->QA_EFF_COL00GREEN, player[g_Player]->QA_EFF_COL00BLUE, player[g_Player]->QA_EFF_COL00ALPHA);
				}

			SCRAM++;
			}
		}


	helly=0;
	while(helly < _->NomAI)
		{
		if(Q_Forge->Forge[helly].LIVE == 1)
			{
			SCRAM=0;
			while(SCRAM < 7)
				{
				if(SCRAM == 0 && Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR >= 0 && Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR < 150)
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].ON;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].Red;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].Green;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[1].Red;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[1].Green;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[1].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[1].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[2].Red;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[2].Green;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[2].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[2].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[3].Red;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[3].Green;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[3].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[3].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[4].Red;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[4].Green;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[4].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[4].Alpha;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrHEADARMOUR].Effect[0].INT * Q_Forge->Forge[helly].JINK3_PowerFactor;

					Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[helly].AV, "BIP01 HEAD", &Q_Forge->Forge[helly].QA_EFF_BONEMATRIX);
					}

				if(SCRAM == 1 && Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR >= 0 && Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR < 150)
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].ON;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].Red;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].Green;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[1].Red;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[1].Green;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[1].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[1].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[2].Red;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[2].Green;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[2].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[2].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[3].Red;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[3].Green;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[3].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[3].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[4].Red;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[4].Green;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[4].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[4].Alpha;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrUPPERARMOUR].Effect[0].INT * Q_Forge->Forge[helly].JINK3_PowerFactor;

					Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[helly].AV, "BIP01 L FOREARM", &Q_Forge->Forge[helly].QA_EFF_BONEMATRIX);
					Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[helly].AV, "BIP01 R FOREARM", &Q_Forge->Forge[helly].QA_EFF_BONEMATRIX01);
					}

				if(SCRAM == 2 && Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR >= 0 && Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR < 150)
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].ON;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].Red;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].Green;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[1].Red;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[1].Green;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[1].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[1].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[2].Red;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[2].Green;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[2].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[2].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[3].Red;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[3].Green;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[3].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[3].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[4].Red;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[4].Green;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[4].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[4].Alpha;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrLOWERARMOUR].Effect[0].INT * Q_Forge->Forge[helly].JINK3_PowerFactor;

					Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[helly].AV, "BIP01", &Q_Forge->Forge[helly].QA_EFF_BONEMATRIX);
					}

				if(SCRAM == 3)	//SPELL SLOT 1
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_SWITCH;
					if(Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].LIVE == 0) Q_Forge->Forge[helly].QA_EFF_SWITCH = 0;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL00RED;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL00GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL00BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL00ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL01RED;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL01GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL01BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL01ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL02RED;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL02GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL02BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL02ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL03RED;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL03GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL03BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL03ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL04RED;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL04GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL04BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_COL04ALPHA;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.SpellSLOT[0].QA_EFFECT_INTENSITY * Q_Forge->Forge[helly].JINK3_PowerFactor;
					}

				if(SCRAM == 4)	//SPELL SLOT 2
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_SWITCH;
					if(Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].LIVE == 0) Q_Forge->Forge[helly].QA_EFF_SWITCH = 0;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL00RED;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL00GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL00BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL00ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL01RED;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL01GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL01BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL01ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL02RED;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL02GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL02BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL02ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL03RED;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL03GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL03BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL03ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL04RED;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL04GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL04BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_COL04ALPHA;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_INTENSITY * Q_Forge->Forge[helly].JINK3_PowerFactor;
					}

				if(SCRAM == 5)	//SPELL SLOT 3
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].QA_EFFECT_SWITCH;
					if(Q_Forge->Forge[helly].CharDATA.SpellSLOT[1].LIVE == 0) Q_Forge->Forge[helly].QA_EFF_SWITCH = 0;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL00RED;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL00GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL00BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL00ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL01RED;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL01GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL01BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL01ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL02RED;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL02GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL02BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL02ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL03RED;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL03GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL03BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL03ALPHA;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL04RED;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL04GREEN;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL04BLUE;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_COL04ALPHA;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.SpellSLOT[2].QA_EFFECT_INTENSITY * Q_Forge->Forge[helly].JINK3_PowerFactor;
					}

				if(SCRAM == 6 && Q_Forge->Forge[helly].CharDATA.CurrWEAPON >= 0 && Q_Forge->Forge[helly].CharDATA.CurrWEAPON < 150)
					{
					Q_Forge->Forge[helly].QA_EFF_SWITCH = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].ON;

					Q_Forge->Forge[helly].QA_EFF_COL00RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].Red;
					Q_Forge->Forge[helly].QA_EFF_COL00GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].Green;
					Q_Forge->Forge[helly].QA_EFF_COL00BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL00ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL01RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[1].Red;
					Q_Forge->Forge[helly].QA_EFF_COL01GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[1].Green;
					Q_Forge->Forge[helly].QA_EFF_COL01BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[1].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL01ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[1].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL02RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[2].Red;
					Q_Forge->Forge[helly].QA_EFF_COL02GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[2].Green;
					Q_Forge->Forge[helly].QA_EFF_COL02BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[2].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL02ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[2].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL03RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[3].Red;
					Q_Forge->Forge[helly].QA_EFF_COL03GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[3].Green;
					Q_Forge->Forge[helly].QA_EFF_COL03BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[3].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL03ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[3].Alpha;

					Q_Forge->Forge[helly].QA_EFF_COL04RED = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[4].Red;
					Q_Forge->Forge[helly].QA_EFF_COL04GREEN = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[4].Green;
					Q_Forge->Forge[helly].QA_EFF_COL04BLUE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[4].Blue;
					Q_Forge->Forge[helly].QA_EFF_COL04ALPHA = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[4].Alpha;

					Q_Forge->Forge[helly].QA_EFF_TYPE = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].TYPE;
					Q_Forge->Forge[helly].QA_EFF_INTENSITY = Q_Forge->Forge[helly].CharDATA.ItemDATA[Q_Forge->Forge[helly].CharDATA.CurrWEAPON].Effect[0].INT * Q_Forge->Forge[helly].JINK3_PowerFactor;

					Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[helly].AV, "BIP01", &Q_Forge->Forge[helly].QA_EFF_BONEMATRIX);
					}

				if(Q_Forge->Forge[helly].QA_EFF_SWITCH == 1)
					{
					Q.QAEFFcontrolAI(helly, Q_Forge->Forge[helly].QA_EFF_TYPE, Q_Forge->Forge[helly].QA_EFF_INTENSITY, Q_Forge->Forge[helly].QA_EFF_COL00RED, Q_Forge->Forge[helly].QA_EFF_COL00GREEN, Q_Forge->Forge[helly].QA_EFF_COL00BLUE, Q_Forge->Forge[helly].QA_EFF_COL00ALPHA);
					}

				SCRAM++;
				}
			}
		helly++;
		}

	//########  - Player Shield Control -  ########//
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
			{
			Q.CONTROL_PlayerClericShieldControl();
			}
		}
	

	//########  - Avatar Shield Control -  ########//

	SCRAM = 0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].CharDATA.Class == 2)
				{
				Q.CONTROL_AvatarClericShieldControl(SCRAM);
				}
			}

		SCRAM++;
		}


	//########  - NET EFFECTS CONTROL -  #########
	SCRAM = 0;
	while(SCRAM < _->NomNetEffectControl)
		{
		if(Q_NetEffectControl->NetEffectControl[SCRAM].Active == 1)
			{
			Q_NetEffectControl->NetEffectControl[SCRAM].Active = 0;

			switch(Q_NetEffectControl->NetEffectControl[SCRAM].Type)
				{
				case 0:
					{
					jet=0;
					while((jet < (((Q_NetEffectControl->NetEffectControl[SCRAM].Effintensity/5000) * 145) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.2 + (6 * (Q_NetEffectControl->NetEffectControl[SCRAM].Effintensity/5000)));
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_NetEffectControl->NetEffectControl[SCRAM].Pos;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*15;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*15;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*15;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					} break;

				case 1:
					{
					jet=0;
					while((jet < ((Q_NetEffectControl->NetEffectControl[SCRAM].Effintensity * 100) + 20)) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.135f;		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 8;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 225;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 225;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 100;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = (0.3 + (6 * Q_NetEffectControl->NetEffectControl[SCRAM].Effintensity));

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = ((float)rand() / 32767);
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

						Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

						if(Q_NetEffectControl->NetEffectControl[SCRAM].AvID == player[g_Player]->NetUPDATE.ServerCONTROLID)
							{ Qpo->Vec3d_AddScaled(&player[g_Player]->Shield.Xform.Translation, (65 * player[g_Player]->Cleric.ShieldScale), &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec, &Q_PntSprite->PntSprite[_->NomPntSprite].Pos); }
						else
							{
							if(Q_NetEffectControl->NetEffectControl[SCRAM].AvID == 250)
								{ Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Shield.Xform.Translation, (65 * Q_Forge->Forge[Q_Netplayer->Netplayer[0].LocalCONTROLID].Cleric.ShieldScale), &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec, &Q_PntSprite->PntSprite[_->NomPntSprite].Pos); }
							else
								{ Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Q_NetEffectControl->NetEffectControl[SCRAM].AvID].Shield.Xform.Translation, (65 * Q_Forge->Forge[Q_NetEffectControl->NetEffectControl[SCRAM].AvID].Cleric.ShieldScale), &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec, &Q_PntSprite->PntSprite[_->NomPntSprite].Pos); }
							}

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = 0;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = -1;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = 0;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = 250;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}
					} break;
				}
			}

		SCRAM++;
		}


	//########  - Avatar Position Control -  ########//
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		player[g_Player]->oldAPC = player[g_Player]->newAPC;
		player[g_Player]->newAPC = playerAV[g_Player]->Xform.Translation;
		Qpo->Vec3d_Subtract(&player[g_Player]->newAPC, &player[g_Player]->oldAPC, &player[g_Player]->INvectorAPC);
		Qpo->Vec3d_Normalize(&player[g_Player]->INvectorAPC);

		jet = 0;
		while(jet < _->NomAI)
			{
			if(Q_Forge->Forge[jet].LIVE == 1)
				{
				Q_Forge->Forge[jet].oldAPC = Q_Forge->Forge[jet].newAPC;
				Q_Forge->Forge[jet].newAPC = Q_Forge->Forge[jet].AV.Xform.Translation;
				Qpo->Vec3d_Subtract(&Q_Forge->Forge[jet].newAPC, &Q_Forge->Forge[jet].oldAPC, &Q_Forge->Forge[jet].INvectorAPC);
				Qpo->Vec3d_Normalize(&Q_Forge->Forge[jet].INvectorAPC);
				}
			jet++;
			}
		}


	//########  - Avatar ENERGY Control -  ########//
	if(_->NetworkOption != 1)
		{
		for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
			{
			g_Player = f_CountPlayer;

			if(player[g_Player]->JinkSpecialON == 0 && player[g_Player]->HB_Dead == 0)
				{
				if( TIME > player[g_Player]->HB_EnergyTimer + 45 )
					{
					player[g_Player]->HB_Energy += ((0.03 + (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence / 3000)) / (1 + (player[g_Player]->JINK3_PowerFactor / 50))) * _->TimeScale;
					if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
					}
				}
			else player[g_Player]->HB_EnergyTimer = TIME;
			}


		jet = 0;
		while(jet < _->NomAI)
			{
			if(Q_Forge->Forge[jet].LIVE == 1)
				{
				if(Q_Forge->Forge[jet].JinkSpecialON == 0 && Q_Forge->Forge[jet].HB_Dead == 0)
					{
					if( TIME > Q_Forge->Forge[jet].HB_EnergyTimer + 45 )
						{
						Q_Forge->Forge[jet].HB_Energy += ((0.03 + (Q_Forge->Forge[jet].CharDATA.BodySKILL.Intelligence / 3000)) / (1 + (Q_Forge->Forge[jet].JINK3_PowerFactor / 50))) * _->TimeScale;
						if(Q_Forge->Forge[jet].HB_Energy > Q_Forge->Forge[jet].HB_MaxEnergy) Q_Forge->Forge[jet].HB_Energy = Q_Forge->Forge[jet].HB_MaxEnergy;
						}
					}
				else Q_Forge->Forge[jet].HB_EnergyTimer = TIME;
				}
			jet++;
			}
		}


	//########  - Avatar POWER Control -  ########//
	if(_->NetworkOption != 1)
		{
		for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
			{
			g_Player = f_CountPlayer;

			if(player[g_Player]->Mposestate != 16)
				{
				Q.DeactivateItems();

				player[g_Player]->JINK3_PowerFactor -= ((0.08 / (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity) / 10) + 1))) * _->TimeScale;
				if(player[g_Player]->JINK3_PowerFactor < 1) player[g_Player]->JINK3_PowerFactor = 1;

				Q.ActivateItems();
				}
			}

		jet = 0;
		while(jet < _->NomAI)
			{
			if(Q_Forge->Forge[jet].LIVE == 1)
				{
				if(Q_Forge->Forge[jet].Mposestate != 16)
					{
					Q.DeactivateItemsAI(jet);

					Q_Forge->Forge[jet].JINK3_PowerFactor -= ((0.08 / (((Q_Forge->Forge[jet].CharDATA.Level + Q_Forge->Forge[jet].CharDATA.BodySKILL.JINKINC3intensity) / 10) + 1))) * _->TimeScale;
					if(Q_Forge->Forge[jet].JINK3_PowerFactor < 1) Q_Forge->Forge[jet].JINK3_PowerFactor = 1;

					Q.ActivateItemsAI(jet);
					}
				}
			jet++;
			}
		}


	//########  - Avatar WEAPON BOOST Control -  ########//
	if(_->NetworkOption != 1)
		{
		for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
			{
			g_Player = f_CountPlayer;

			if(player[g_Player]->Mposestate != 16)
				{
				player[g_Player]->JINK3_WeaponFactor -= (((3 / (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level + player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity) / 10) + 1)) / 100)) * _->TimeScale;
				if(player[g_Player]->JINK3_WeaponFactor < 1) player[g_Player]->JINK3_WeaponFactor = 1;
				}
			}

		jet = 0;
		while(jet < _->NomAI)
			{
			if(Q_Forge->Forge[jet].LIVE == 1)
				{
				if(Q_Forge->Forge[jet].Mposestate != 16)
					{
					Q_Forge->Forge[jet].JINK3_WeaponFactor -= (((3 / (((Q_Forge->Forge[jet].CharDATA.Level + Q_Forge->Forge[jet].CharDATA.BodySKILL.JINKINC3intensity) / 10) + 1)) / 100)) * _->TimeScale;
					if(Q_Forge->Forge[jet].JINK3_WeaponFactor < 1) Q_Forge->Forge[jet].JINK3_WeaponFactor = 1;
					}
				}
			jet++;
			}
		}


	//########  - MELEE DAMAGE CONTROL -  ########//

	//###- Reset Melee Damage (player) -###
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(TIME > player[g_Player]->HB_DmgSTORETimer + (45 * (1-(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower/500))))
			{
			if(player[g_Player]->HB_DmgSTORE - (((25 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/500))) * _->TimeScale) >= 0) player[g_Player]->HB_DmgSTORE -= (((25 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution/500))) * _->TimeScale);
			else player[g_Player]->HB_DmgSTORE = 0;
			}
		}

	jet = 0;
	while(jet < _->NomAI)
		{
		if(Q_Forge->Forge[jet].LIVE == 1)
			{
			//###- Reset Melee Damage (AI) -###
			if(TIME > Q_Forge->Forge[jet].HB_DmgSTORETimer + (45 * (1-(Q_Forge->Forge[jet].CharDATA.BodySKILL.DefPower/500))))
				{
				if(Q_Forge->Forge[jet].HB_DmgSTORE - (((25 * (Q_Forge->Forge[jet].CharDATA.BodySKILL.Constitution/500))) * _->TimeScale) >= 0) Q_Forge->Forge[jet].HB_DmgSTORE -= (((25 * (Q_Forge->Forge[jet].CharDATA.BodySKILL.Constitution/500))) * _->TimeScale);
				else Q_Forge->Forge[jet].HB_DmgSTORE = 0;
				}
			}
		jet++;
		}


	//########  - IMPACT DAMAGE CONTROL -  ########//

	//###- Reset Impact Damage (player) -###
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(TIME > player[g_Player]->BulletHitCntTimer + 15) player[g_Player]->BulletHitCnt = 0;

		//###- Regenerate Armour (player) -###
		if(TIME > player[g_Player]->BulletHitCntTimer + 40)
			{
			if(player[g_Player]->HB_Armour + (((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourREGEN / 5000) * 20) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourREGEN / 5000) * 20) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourREGEN / 5000) * 20) * _->TimeScale) <= player[g_Player]->HB_MaxArmour) player[g_Player]->HB_Armour += (((float)(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrHEADARMOUR].ArmourREGEN / 5000) * 20) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrUPPERARMOUR].ArmourREGEN / 5000) * 20) + ((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrLOWERARMOUR].ArmourREGEN / 5000) * 20) * _->TimeScale);
			else player[g_Player]->HB_Armour = player[g_Player]->HB_MaxArmour;
			}
		}


	jet = 0;
	while(jet < _->NomAI)
		{
		if(Q_Forge->Forge[jet].LIVE == 1)
			{
			//###- Reset Impact Damage (AI) -###
			if(TIME > Q_Forge->Forge[jet].BulletHitCntTimer + 15) Q_Forge->Forge[jet].BulletHitCnt = 0;

			//###- Regenerate Armour (AI) -###
			if(TIME > Q_Forge->Forge[jet].BulletHitCntTimer + 40)
				{
				if(Q_Forge->Forge[jet].CharDATA.CurrHEADARMOUR >= 0 && Q_Forge->Forge[jet].CharDATA.CurrHEADARMOUR < 150
				&& Q_Forge->Forge[jet].CharDATA.CurrUPPERARMOUR >= 0 && Q_Forge->Forge[jet].CharDATA.CurrUPPERARMOUR < 150
				&& Q_Forge->Forge[jet].CharDATA.CurrLOWERARMOUR >= 0 && Q_Forge->Forge[jet].CharDATA.CurrLOWERARMOUR < 150)
					{
					if(Q_Forge->Forge[jet].HB_Armour + (((float)(Q_Forge->Forge[jet].CharDATA.ItemDATA[Q_Forge->Forge[jet].CharDATA.CurrHEADARMOUR].ArmourREGEN / 5000) * 20) + ((Q_Forge->Forge[jet].CharDATA.ItemDATA[Q_Forge->Forge[jet].CharDATA.CurrUPPERARMOUR].ArmourREGEN / 5000) * 20) + ((Q_Forge->Forge[jet].CharDATA.ItemDATA[Q_Forge->Forge[jet].CharDATA.CurrLOWERARMOUR].ArmourREGEN / 5000) * 20) * _->TimeScale) <= Q_Forge->Forge[jet].HB_MaxArmour) Q_Forge->Forge[jet].HB_Armour += (((float)(Q_Forge->Forge[jet].CharDATA.ItemDATA[Q_Forge->Forge[jet].CharDATA.CurrHEADARMOUR].ArmourREGEN / 5000) * 20) + ((Q_Forge->Forge[jet].CharDATA.ItemDATA[Q_Forge->Forge[jet].CharDATA.CurrUPPERARMOUR].ArmourREGEN / 5000) * 20) + ((Q_Forge->Forge[jet].CharDATA.ItemDATA[Q_Forge->Forge[jet].CharDATA.CurrLOWERARMOUR].ArmourREGEN / 5000) * 20) * _->TimeScale);
					else Q_Forge->Forge[jet].HB_Armour = Q_Forge->Forge[jet].HB_MaxArmour;
					}
				else
					{
					if((Q_Forge->Forge[jet].HB_Armour + ((Q_Forge->Forge[jet].HB_MaxArmour / 18) * _->TimeScale)) <= Q_Forge->Forge[jet].HB_MaxArmour) Q_Forge->Forge[jet].HB_Armour += ((Q_Forge->Forge[jet].HB_MaxArmour / 18) * _->TimeScale);
					else Q_Forge->Forge[jet].HB_Armour = Q_Forge->Forge[jet].HB_MaxArmour;
					}
				}
			}
		jet++;
		}


	//########  - POWER BANK DAMAGE CONTROL -  ########//

	if(_->NetworkOption != 1)
		{
		//###- Reset Block Damage (player) -###
		for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
			{
			g_Player = f_CountPlayer;

			if(TIME > player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PBTIMER + (200 - ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower)) / 2 )
				{
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK += ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower / 10) * _->TimeScale;
				if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK >= ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100))
					player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = ((((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower + (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity) * 2) + 100);
				}

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK < 0) player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.POWERBANK = 0;
			}

		jet = 0;
		while(jet < _->NomAI)
			{
			if(Q_Forge->Forge[jet].LIVE == 1)
				{
				//###- Reset Block Damage (AI) -###
				if(TIME > Q_Forge->Forge[jet].CharDATA.BodySKILL.PBTIMER + (200 - ((float)Q_Forge->Forge[jet].CharDATA.BodySKILL.DefPower)) / 2 )
					{
					Q_Forge->Forge[jet].CharDATA.BodySKILL.POWERBANK += ((float)Q_Forge->Forge[jet].CharDATA.BodySKILL.DefPower / 10) * _->TimeScale;
					if(Q_Forge->Forge[jet].CharDATA.BodySKILL.POWERBANK >= ((((float)Q_Forge->Forge[jet].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[jet].CharDATA.BodySKILL.Dexterity) * 2) + 100))
						Q_Forge->Forge[jet].CharDATA.BodySKILL.POWERBANK = ((((float)Q_Forge->Forge[jet].CharDATA.BodySKILL.DefPower + (float)Q_Forge->Forge[jet].CharDATA.BodySKILL.Dexterity) * 2) + 100);

					if(Q_Forge->Forge[jet].CharDATA.BodySKILL.POWERBANK < 0) Q_Forge->Forge[jet].CharDATA.BodySKILL.POWERBANK = 0;
					}
				}
			jet++;
			}
		}


	//########  - Jinks -  ########//
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		Q.CONTROL_Jinks();
		}


	//########  - TIME CONTROL -  ########//
	if((_->TimeHole != 0) && (player[0]->JumpFG > 0))
		{
		if(_->TimeInit == 0)
			{
			player[g_Player]->STRAngles = player[g_Player]->Angles;
			_->TimeInit = 1;

			//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,&player[g_Player]->RFistPos.Translation,600.0f,2.0f,&Volume,&Pan,&Frequency);
			Qpo->Sound_Play(Medias->S_MatStart, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
			}

		_->TimeScale = (_->TimeFactor/1000)*_->TimeScaleREAL;

		if(!(KEY_PRESS_DOWN(QIN_x) && (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE > 0)))
			{
			player[g_Player]->camrotdist = ( 90 + ( 55 * ( 1 - _->TimeScale ) ) );
			player[g_Player]->WeaponZoomFACT = ( ( /*1 -*/ _->TimeScale ) * -15 );	//-5	//-3
			}


		if(_->TimeHoleDir == 0)
			{
			_->TimeFactor -= 334*_->TimeScaleREAL;	//250 V_Good
			if(_->TimeFactor < 1)
				{
				_->TimeFactor = 1;
				_->TimeHoleDir = 1;
				}
			}

		if(_->TimeHoleDir == 1)
			{
			if(_->TimeHole == 1) _->TimeFactor *= 1+(0.25*_->TimeScaleREAL);	//1.35
			if(_->TimeHole == 2) _->TimeFactor *= 1+(0.8*_->TimeScaleREAL);
			if(_->TimeHole == 3) _->TimeFactor *= 1+(_->TimeScaleREAL);
			if(_->TimeHole == 4) _->TimeFactor *= 1+(0.1*_->TimeScaleREAL);
			if(_->TimeHole == 5)
				{
				if(player[g_Player]->attackon == 1) _->TimeFactor = 750*_->TimeScaleREAL;
				else _->TimeFactor *= 1+(0.25*_->TimeScaleREAL);
				}
			if(_->TimeHole == 6) _->TimeFactor *= 1+(0.4*_->TimeScaleREAL);

			if(_->TimeScale >= (0.4*_->TimeScaleREAL) && _->TimeHole != 5)
				{
				if(_->TimeRotate == 0)	_->TimeReset = 1;
				}


			if(_->TimeScale >= (0.7*_->TimeScaleREAL) && _->TimeHole != 5)
				{
				////QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm,&player[g_Player]->RFistPos.Translation,600.0f,2.0f,&Volume,&Pan,&Frequency);
				Qpo->Sound_Play(Medias->S_MatEnd, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->RFistPos.Translation);
				}


			if(_->TimeScale > (1*_->TimeScaleREAL))
				{
				_->TimeScale = (1*_->TimeScaleREAL);
				_->TimeFactor = 1000;
				_->TimeHoleDir = 0;
				_->TimeHole = 0;
				_->TimeInit = 0;
				_->TimeRotate = 0;
				_->JinkTime = 0;
				if(!(KEY_PRESS_DOWN(QIN_x) && (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ScopeTYPE > 0)))
					{
					player[g_Player]->camrotdist = 140;
					player[g_Player]->WeaponZoomFACT = 0;
					}
				}
			}

		//#####---  Set Sound Timescale  ---#####
		_->S_TimeScale = _->TimeScale;
		if(_->FRLON == 1) _->S_TimeScale *= _->FRLresult / _->FRLtarget;
		_->S_TimeScale = ((_->S_TimeScale / 2) + 0.5);
		}
	else
		{
		if(_->TimeReset == 1 && _->TimePlayerLock == 0)
			{
			if(!(((player[g_Player]->STRAngles.y - player[g_Player]->Angles.y) < 0.08) && ((player[g_Player]->STRAngles.y - player[g_Player]->Angles.y) > -0.08)))
				{
				if(player[g_Player]->Angles.y > player[g_Player]->STRAngles.y)
					{
					player[g_Player]->Angles.y += (player[g_Player]->STRAngles.y - player[g_Player]->Angles.y)/3;
					}

				if(player[g_Player]->Angles.y < player[g_Player]->STRAngles.y)
					{
					player[g_Player]->Angles.y += (player[g_Player]->STRAngles.y - player[g_Player]->Angles.y)/3;
					}
				}
			else
				{
				player[g_Player]->Angles.y = player[g_Player]->STRAngles.y;
				_->TimeReset = 0;
				}
			}

		//#####---  Set Timescale  ---#####
		_->TimeScale = _->TimeScaleREAL;

		if(_->TimeScaleREAL < 0.35)
			{
			_->TimeScaleREAL = 0.35;
			}

		if(_->TimeScale < 0.35)
			{
			_->TimeScale = 0.35;
			}
		}

	//#####---  Set Sound Timescale  ---#####
	_->S_TimeScale = _->TimeScale * 6.66f;

	//not the place for timescae global search QActiveFramework.cpp
	//_->TimeScale = 0.038;
	
	//########  - CLERIC SUB-SYSTEMS -  ########//

	//########  - CLERIC SPELL SYSTEM -  ########//

	if(_->NetworkOption != 1)
		{
		if(_->NomSpell > 0)
			{
			aero = 0;
			while(aero < _->NomSpell)
				{
				if(Q_ClericSpell->ClericSpell[aero].Live == 1)
					{
					Q_EFFControl.ClericSpell_ServerFrame(aero);
					}
				aero++;
				}
			}
		}
	else	//###### Phantom Cleric Spells
		{
		if(_->NomSpell > 0)
			{
			aero = 0;
			while(aero < _->NomSpell)
				{
				if(Q_ClericSpell->ClericSpell[aero].Live == 1)
					{
					Q_EFFControl.ClericSpell_ClientFrame(aero);
					}
				aero++;
				}
			}
		}


	//#### WINDWAKES
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		Q_EFFControl.WindWake_PlayerFrame();
		}


	aero = 0;
	while(aero < _->NomAI)
		{
		if(Q_Forge->Forge[aero].LIVE == 1)
			{
			Q_EFFControl.WindWake_AvatarFrame(aero);
			}
		aero++;
		}


	//#### PLAYER TEXTURED TRI

#if 0
	if(player[g_Player]->NomTriEffect > 0)
		{
		SCRAM = player[g_Player]->NomTriEffect - 1;
		while(SCRAM >= 0)
			{
			if(player[g_Player]->Q_TexTriEffect[SCRAM].Live == 1)
				{
				Q_EFFControl.TexTriEffect_PlayerFrame(SCRAM);
				}
			SCRAM--;
			}
		}


	//######## AI Textured Tri Effects ########

	aero=0;
	while(aero < _->NomAI)	//AI Loop
		{
		if(Q_Forge->Forge[aero].LIVE == 1)
			{
			if(Q_Forge->Forge[aero].NomTriEffect > 0)
				{
				SCRAM = Q_Forge->Forge[aero].NomTriEffect - 1;
				while(SCRAM >= 0)
					{
					if(Q_Forge->Forge[aero].Q_TexTriEffect[SCRAM].Live == 1)
						{
						Q_EFFControl.TexTriEffect_AvatarFrame(aero, SCRAM);
						}//END Live
					SCRAM--;
					}//END SCRAM
				}//END NomTriEffects
			}
		aero++;
		}//END AI loop


	//------******[  <RENDER PIN EFFECT MESHES>------[EFFECTS RENDERING COMPONENT]  ]******------

	if(_->NomPEFMesh > 0)
		{
		aero = 0;
		while(aero < _->NomPEFMesh)
			{
			if(Q_PinEffectMesh->PinEffectMesh[aero].EffectLive == 1)
				{
				Q_EFFControl.PinEffectMesh_ControlFrame(aero);
				}
			aero++;
			}
		}
#endif

	if(g_NetConnect)
		{
		_->NetworkOption = 0;
		}

	///END World_Event_Engine
	}

};