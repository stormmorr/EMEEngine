/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Nueral Net Functions-
	*/#include "pch.h"/*- Minor Component -Player Spawn NNbot-

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
#include "Q-AI-NNbot.h"

using namespace GVARS;

namespace GVARS
{

void Q_COREFunctions::PlayerSpawnNNbot(QpoVec3d PointOrigin)
{
#if 0
	if(_->NomNNBots < 499)
#endif
	if(0)
		{
		//#### Initialise One Particle ####//
		Q_NNBot->NNBot[_->NomNNBots].Scale = 0.1f;		//0.025f//0.002f
		Q_NNBot->NNBot[_->NomNNBots].Alpha = 255;
		Q_NNBot->NNBot[_->NomNNBots].Speed = ((((float)rand() / 32767)*60)+30);
		Q_NNBot->NNBot[_->NomNNBots].Pos = PointOrigin;
		Q_NNBot->NNBot[_->NomNNBots].Direction = 0;

		Q_NNBot->NNBot[_->NomNNBots].TraVec.x = (((float)rand() / 32767)-0.5);
		Q_NNBot->NNBot[_->NomNNBots].TraVec.y = (((float)rand() / 32767)-0.5);
		Q_NNBot->NNBot[_->NomNNBots].TraVec.z = (((float)rand() / 32767)-0.5);

		Q_NNBot->NNBot[_->NomNNBots].R = 255;
		Q_NNBot->NNBot[_->NomNNBots].G = 255;
		Q_NNBot->NNBot[_->NomNNBots].B = 255;

		Q_NNBot->NNBot[_->NomNNBots].LIVE = 1;

		Q_NNBot->NNBot[_->NomNNBots].AvID = 250;

		Q_NNBot->NNBot[_->NomNNBots].Aggression = 0;

		Q_NNBot->NNBot[_->NomNNBots].HB_Health = 100;
		Q_NNBot->NNBot[_->NomNNBots].HB_Energy = 100;


		//### SET Level
		Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger = (((float)rand() / 32767) * 5.7);

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 0 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 3)
			{
			Q_NNBot->NNBot[_->NomNNBots].Level = 1;
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 3 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 4)
			{
			Q_NNBot->NNBot[_->NomNNBots].Level = (((float)rand() / 32767) * 5);
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 4 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 5)
			{
			Q_NNBot->NNBot[_->NomNNBots].Level = (((float)rand() / 32767) * 10);
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 5 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 6)
			{
			Q_NNBot->NNBot[_->NomNNBots].Level = (((float)rand() / 32767) * 20);
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 5 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger <= 5.7)
			{
			Q_NNBot->NNBot[_->NomNNBots].Level = (((float)rand() / 32767) * 100);
			}


		//### SET Experience Level
		Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger = (((float)rand() / 32767) * 5.7);

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 0 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 3)
			{
			Q_NNBot->NNBot[_->NomNNBots].UnusedXP = 0;
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 3 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 4)
			{
			Q_NNBot->NNBot[_->NomNNBots].UnusedXP = (((float)rand() / 32767) * 300);
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 4 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 5)
			{
			Q_NNBot->NNBot[_->NomNNBots].UnusedXP = (((float)rand() / 32767) * 500);
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 5 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 6)
			{
			Q_NNBot->NNBot[_->NomNNBots].UnusedXP = (((float)rand() / 32767) * 1000);
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 5 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger <= 5.7)
			{
			Q_NNBot->NNBot[_->NomNNBots].UnusedXP = (((float)rand() / 32767) * 5000);
			}


		//### Set class
		Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger = (((float)rand() / 32767) * 15);
		
		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 0 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 3)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 0;	//NN Healer

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/5;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff * 1.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height * 1.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight * 0.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness * 1.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution * 0.65;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * 0.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity * 0.5;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 0 || Q_MeMPathway->MeMPathway[helly].OutputType == 1)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_NNBot->NNBot[_->NomNNBots].Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed / 10;
					}
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 10)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution;
					}
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 5 || Q_MeMPathway->MeMPathway[helly].OutputType == 11 || Q_MeMPathway->MeMPathway[helly].OutputType == 14 || Q_MeMPathway->MeMPathway[helly].OutputType == 17)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[1].Potency;
					}
				helly++;
				}

			#pragma message ("EDIT: - Set Skills on Spawn")
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 3 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 5)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 1;	//NN Soldier

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/3;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence * 0.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff * 0.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height * 0.9;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution * 2.25;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * 1.7;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower * 1.1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed * 1.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity * 2.5;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 0 || Q_MeMPathway->MeMPathway[helly].OutputType == 1)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_NNBot->NNBot[_->NomNNBots].Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed / 10;
					}
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 10)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution;
					}
				helly++;
				}
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 5 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 6)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 2;	//NN Freak

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/(((float)rand() / 32767) * 3);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/(((float)rand() / 32767) * 3);

			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Cost * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Potency * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Amount * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Speed * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Duration * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Accuracy * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					trans++;
					}
				}

			//### SET SKILLS
			helly=0;
			while(helly < _->NomRealisation)
				{
				Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = (((float)rand() / 32767) * 150);
				Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
				if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
				Q_NNBot->NNBot[_->NomNNBots].Skill[helly] *= Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
				helly++;
				}
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 6 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 8)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 3;	//NN ResEdit

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/10;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/10;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness * 1.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution * 1.65;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower * 0.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower * 1.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity * 1;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 0 || Q_MeMPathway->MeMPathway[helly].OutputType == 1)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_NNBot->NNBot[_->NomNNBots].Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed / 10;
					}
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 10)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution;
					}
				helly++;
				}
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 8 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 10)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 4;	//NN Hacker

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/10;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/10;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence * 1.9;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff * 3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr * 0.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness * 1.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity * 1.95;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution * 0.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed * 1.9;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower * 0.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity * 0.9;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 0 || Q_MeMPathway->MeMPathway[helly].OutputType == 1)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_NNBot->NNBot[_->NomNNBots].Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed / 10;
					}
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 10)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution;
					}
				helly++;
				}
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 10 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 15)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 5;	//NN Defender

			//### SET ATTRIBUTESs
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level/8;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Intelligence * 0.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.EnergyEff * 1.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.PhysicalStr * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Quickness * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Dexterity * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution * 3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.AggPower * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.DefPower * 5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightArmSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftArmSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RightLegSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.LeftLegSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.DrawSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.ReloadSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.RecoilHEIGHTrecover * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCmovespeed * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINCpower * 0.7;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.JINKINC3intensity * 0.7;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS - hello?
			helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 0 || Q_MeMPathway->MeMPathway[helly].OutputType == 1)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_NNBot->NNBot[_->NomNNBots].Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed / 10;
					}
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 10)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution;
					}
				helly++;
				}
			}

		_->NomNNBots++;
		}
}

};