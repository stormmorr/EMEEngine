/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Nueral Net Functions-
	*/#include "pch.h"/*- Minor Component -Avatar Spawn NNbot-

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

void Q_COREFunctions::AISpawnNNbot(int AIcounter, QpoVec3d PointOrigin)
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

		Q_NNBot->NNBot[_->NomNNBots].AvID = AIcounter;

		Q_NNBot->NNBot[_->NomNNBots].Aggression = 100;

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
			Q_NNBot->NNBot[_->NomNNBots].UnusedXP = 50;
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
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.Level;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.Level/5;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff * 1.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height * 1.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight * 0.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness * 1.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution * 0.65;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower * 0.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP * 0.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity * 0.5;

			if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 5 || Q_MeMPathway->MeMPathway[helly].OutputType == 11 || Q_MeMPathway->MeMPathway[helly].OutputType == 14 || Q_MeMPathway->MeMPathway[helly].OutputType == 17)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_Forge->Forge[AIcounter].CharDATA.Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[1].Potency;
					}
				helly++;
				}
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 3 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 5)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 1;	//NN Soldier

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.Level/3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.Level/3;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence * 0.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff * 0.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height * 0.9;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution * 2.25;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower * 1.7;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower * 1.1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH * 2.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover * 2.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed * 1.2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity * 2.5;

			if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			/*helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 5 || Q_MeMPathway->MeMPathway[helly].OutputType == 11 || Q_MeMPathway->MeMPathway[helly].OutputType == 14 || Q_MeMPathway->MeMPathway[helly].OutputType == 17)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_Forge->Forge[AIcounter].CharDATA.Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[1].Potency;
					}
				helly++;
				}*/
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 5 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 6)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 2;	//NN Freak

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.Level/(((float)rand() / 32767) * 3);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.Level/(((float)rand() / 32767) * 3);

			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
			Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
			if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;

			if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Cost * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Potency * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Amount * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Speed * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Duration * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
					Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = (((float)rand() / 32767) * 2);
					if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe > 1) Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe = ((Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe - 1) * 5);
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Accuracy * Q_NNBot->NNBot[_->NomNNBots].Decisions.Toe;
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
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.Level/10;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.Level/10;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness * 1.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution * 1.65;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower * 0.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower * 1.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity * 1;

			if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			/*helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 5 || Q_MeMPathway->MeMPathway[helly].OutputType == 11 || Q_MeMPathway->MeMPathway[helly].OutputType == 14 || Q_MeMPathway->MeMPathway[helly].OutputType == 17)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_Forge->Forge[AIcounter].CharDATA.Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[1].Potency;
					}
				helly++;
				}*/
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 8 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 10)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 4;	//NN Hacker

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.Level/10;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.Level/10;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence * 1.9;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff * 3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr * 0.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness * 1.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity * 1.95;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution * 0.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH * 0.85;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP * 1.35;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed * 1.9;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower * 0.8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity * 0.9;

			if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			/*helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 5 || Q_MeMPathway->MeMPathway[helly].OutputType == 11 || Q_MeMPathway->MeMPathway[helly].OutputType == 14 || Q_MeMPathway->MeMPathway[helly].OutputType == 17)
					{
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_Forge->Forge[AIcounter].CharDATA.Level;
					Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[1].Potency;
					}
				helly++;
				}*/
			}

		if(Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger >= 10 && Q_NNBot->NNBot[_->NomNNBots].Decisions.Finger < 15)
			{
			Q_NNBot->NNBot[_->NomNNBots].Class = 5;	//NN Defender

			//### SET ATTRIBUTES
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_NoWEP = 0;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_TimeScale = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Gravity = 0;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.Level/8;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.Level/8;

			Q_NNBot->NNBot[_->NomNNBots].NNBOT_IntBoost = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Intelligence * 0.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.EnergyEff * 1.3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Height = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Weight = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Strength = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.PhysicalStr * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Quickness = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Quickness * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Dexterity * 1.15;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_Constitution = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Constitution * 3;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_AggPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.AggPower * 1;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_DefPower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.DefPower * 5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSTRENGTH * 0.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightArmSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftArmSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RightLegSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.LeftLegSNAP * 1.75;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.DrawSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.ReloadSPD * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.RecoilHEIGHTrecover * 1.5;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCmovespeed * 2;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINCpower * 0.7;
			Q_NNBot->NNBot[_->NomNNBots].NNBOT_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.JINKINC3intensity * 0.7;

			if(Q_Forge->Forge[AIcounter].CharDATA.Class == 2)
				{
				trans=0;
				while(trans < 12)
					{
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Cost = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Cost;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Potency = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Potency;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Amount = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Amount;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Speed = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Speed;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Duration = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Duration;
					Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[trans].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[trans].Accuracy;
					trans++;
					}
				}

			//### SET SKILLS
			/*helly=0;
			while(helly < _->NomRealisation)
				{
				if(Q_MeMPathway->MeMPathway[helly].OutputType == 5 || Q_MeMPathway->MeMPathway[helly].OutputType == 11 || Q_MeMPathway->MeMPathway[helly].OutputType == 14 || Q_MeMPathway->MeMPathway[helly].OutputType == 17)
					{
					//Q_NNBot->NNBot[_->NomNNBots].Skill[helly] = Q_Forge->Forge[AIcounter].CharDATA.Level;
					//Q_NNBot->NNBot[_->NomNNBots].Skill[helly] += Q_NNBot->NNBot[_->NomNNBots].CLSClericSKILL[1].Potency;
					}
				helly++;
				}*/
			}

		_->NomNNBots++;
		}
}

};