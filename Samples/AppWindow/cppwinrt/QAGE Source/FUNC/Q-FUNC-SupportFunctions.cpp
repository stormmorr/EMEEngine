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

#include "math.h"

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-WE-PntSprite.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-MeleeHits.h"
#include "Q-WE-BulletSystem.h"
#include "Q-WE-EnergyMatrix.h"
#include "Q-WE-CloudControl.h"
#include "Q-ENE-EnergyTypes.h"
#include "Q-OBJ-ObjectTypes.h"
#include "Q-AI-NNbot.h"

#include "Q-WE-ShellATypes.h"

using namespace GVARS;

namespace GVARS
{

//--------------------------------------------------------------------- 

//~~~~~    CORE AQUIRE     ~~~~~
void Q_COREFunctions::CoreAcquire(bool i_new)
{
	Q_PlacementMarker.Acquire("Q_PlacementMarker", 0);
	Q_PlacementMarker->m_Count++;

	printf("QAcquire:::PlacementMarker::%i:::", Q_PlacementMarker->m_Count);

	// Acquire Global Variables Structure
	_.Acquire("GVariablesStruct", Q_PlacementMarker->m_Count);

	// Acquire Q Media Assets
	Medias.Acquire("QMedias", Q_PlacementMarker->m_Count);

	// Prepare // {- Q Player -}
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		player[f_CountPlayer].Acquire("Qplayer", Q_PlacementMarker->m_Count);
		playerSTR[f_CountPlayer].Acquire("QplayerSTR", Q_PlacementMarker->m_Count);
		playerU[f_CountPlayer].Acquire("QplayerU", Q_PlacementMarker->m_Count);

		player[f_CountPlayer]->ScanTurnAngSTR = 0;
		}

	// Prepare // {- Q Forge -}
	Q_Forge.Acquire("QForge", Q_PlacementMarker->m_Count);

	// Prepare // {- NNBOTrewardSTATS -}
	NNBOTrewardSTATS.Acquire("NNBOTrewardSTATS", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_NNBot -}
	Q_NNBot.Acquire("QNNBot", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_PntSprite -}
	Q_PntSprite.Acquire("QPntSprite", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_SEnergy -}
	Q_SEnergy.Acquire("QSEnergy", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_LEnergy -}
	Q_LEnergy.Acquire("QLEnergy", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_Explosion -}
	Q_Explosion.Acquire("QExplosion", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_ClericPlasma -}
	Q_ClericPlasma.Acquire("QClericPlasma", Q_PlacementMarker->m_Count);

	// Prepare // {- Q_ClericSpell -}
	Q_ClericSpell.Acquire("QClericSpell", Q_PlacementMarker->m_Count);


	Q_BMSentry.Acquire("QBMSentry", Q_PlacementMarker->m_Count);

	Q_Building.Acquire("QBuilding", Q_PlacementMarker->m_Count);

	Q_Object.Acquire("QObject", Q_PlacementMarker->m_Count);

	Q_VoxelDamage.Acquire("QVoxelDamage", Q_PlacementMarker->m_Count);

	Q_MeMPathway.Acquire("QMeMPathway", Q_PlacementMarker->m_Count);

	Q_Lightning.Acquire("QLightning", Q_PlacementMarker->m_Count);

	Q_EnergyWake.Acquire("QEnergyWake", Q_PlacementMarker->m_Count);

	Q_NetEffectControl.Acquire("QNetEffectControl", Q_PlacementMarker->m_Count);

	Q_HealEnergy.Acquire("QHealEnergy", Q_PlacementMarker->m_Count);

	Q_NetZoneENTITY.Acquire("QNetZoneENTITY", Q_PlacementMarker->m_Count);

	Q_StartPoints.Acquire("QStartPoints", Q_PlacementMarker->m_Count);

	Q_ANGELeditMAP.Acquire("QANGELeditMAP", Q_PlacementMarker->m_Count);

	Q_AvatarEntity.Acquire("QAvatarEntity", Q_PlacementMarker->m_Count);

	Q_Netplayer.Acquire("QNetplayer", Q_PlacementMarker->m_Count);

	Q_PlayerEntity.Acquire("QPlayerEntity", Q_PlacementMarker->m_Count);

	Q_Bullet.Acquire("QBullet", Q_PlacementMarker->m_Count);

	Q_BulletHit.Acquire("QBulletHit", Q_PlacementMarker->m_Count);

	Q_Cartridge.Acquire("QCartridge", Q_PlacementMarker->m_Count);

	Q_MFlash.Acquire("QMFlash", Q_PlacementMarker->m_Count);

	Q_Cloud.Acquire("QCloud", Q_PlacementMarker->m_Count);

	Q_EnergyMatrix.Acquire("QEnergyMatrix", Q_PlacementMarker->m_Count);

	Q_MeleeHit.Acquire("QMeleeHit", Q_PlacementMarker->m_Count);

	Q_BBlood.Acquire("QBBlood", Q_PlacementMarker->m_Count);

	Q_PowerFlash.Acquire("QPowerFlash", Q_PlacementMarker->m_Count);

	Q_HHSpike.Acquire("QHHSpike", Q_PlacementMarker->m_Count);

	Q_HealSpark.Acquire("QHealSpark", Q_PlacementMarker->m_Count);

	Q_BSparks.Acquire("QBSparks", Q_PlacementMarker->m_Count);

	Q_VaporTrail.Acquire("QVaporTrail", Q_PlacementMarker->m_Count);

	Q_WindWake.Acquire("QWindWake", Q_PlacementMarker->m_Count);

	Q_PinEffectMesh.Acquire("QPinEffectMesh", Q_PlacementMarker->m_Count);

	Q_Decal.Acquire("QDecal", Q_PlacementMarker->m_Count);

	Q_ValidPointer.Acquire("QValidPointer", Q_PlacementMarker->m_Count);
}

//~~~~~    CORE AQUIRE     ~~~~~
void Q_COREFunctions::CoreRelease(void)
{
	printf(":::QDeAllocate\n");

	// Acquire Global Variables Structure
	_.Release();

	// Release Q Media Assets
	Medias.Release();

	// Prepare // {- Q Player -}
	player[g_Player].Release();

	// Prepare // {- Q Forge -}
	Q_Forge.Release();

	// Prepare // {- NNBOTrewardSTATS -}
	NNBOTrewardSTATS.Release();

	// Prepare // {- Q_NNBot -}
	Q_NNBot.Release();

	// Prepare // {- Q_PntSprite -}
	Q_PntSprite.Release();

	// Prepare // {- Q_SEnergy -}
	Q_SEnergy.Release();

	// Prepare // {- Q_LEnergy -}
	Q_LEnergy.Release();

	// Prepare // {- Q_Explosion -}
	Q_Explosion.Release();

	// Prepare // {- Q_ClericPlasma -}
	Q_ClericPlasma.Release();

	// Prepare // {- Q_ClericSpell -}
	Q_ClericSpell.Release();

	Q_BMSentry.Release();

	Q_Object.Release();

	Q_VoxelDamage.Release();

	Q_MeMPathway.Release();

	Q_Lightning.Release();

	Q_EnergyWake.Release();

	Q_NetEffectControl.Release();

	Q_HealEnergy.Release();

	Q_NetZoneENTITY.Release();

	Q_StartPoints.Release();

	Q_ANGELeditMAP.Release();

	Q_AvatarEntity.Release();

	Q_Netplayer.Release();

	Q_PlayerEntity.Release();

	Q_Bullet.Release();

	Q_BulletHit.Release();

	Q_Cartridge.Release();

	Q_MFlash.Release();

	Q_Cloud.Release();

	Q_EnergyMatrix.Release();

	Q_MeleeHit.Release();

	Q_BBlood.Release();

	Q_PowerFlash.Release();

	Q_HHSpike.Release();

	Q_HealSpark.Release();

	Q_BSparks.Release();

	Q_VaporTrail.Release();

	Q_WindWake.Release();

	Q_PinEffectMesh.Release();

	//Q_Decal.Release();

	Q_ValidPointer.Release();
}

void Q_COREFunctions::CoreAllocate(void)
{
#if 0
	printf("QAllocate:::");
#endif

	// Allocate Global Variables Structure
	_.Allocate();//"GVariablesStruct");

#if !defined(_QAGE_SERVER)
	// Allocate Q Media Assets
	Medias.Allocate();//"QMedias");
#endif

	// Prepare // {- Q Player -}
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		player[g_Player].Allocate();//"Qplayer");
		playerU[g_Player].Allocate();//"QplayerU");
		}

	g_Player = 0;

	// Prepare // {- Q Forge -}
	Q_Forge.Allocate();//"QF");

#if !defined(_QAGE_SERVER)
	// Prepare // {- NNBOTrewardSTATS -}
	NNBOTrewardSTATS.Allocate();//"NNBOTrewardSTATS");

	// Prepare // {- Q_NNBot -}
	Q_NNBot.Allocate();//"QNNBot");

	// Prepare // {- Q_PntSprite -}
	Q_PntSprite.Allocate();//"QPntSprite");

	// Prepare // {- Q_SEnergy -}
	Q_SEnergy.Allocate();//"QSEnergy");

	// Prepare // {- Q_LEnergy -}
	Q_LEnergy.Allocate();//"QLEnergy");

	// Prepare // {- Q_Explosion -}
	Q_Explosion.Allocate();//"QExplosion");

	// Prepare // {- Q_ClericPlasma -}
	Q_ClericPlasma.Allocate();//"QClericPlasma");

	// Prepare // {- Q_ClericSpell -}
	Q_ClericSpell.Allocate();//"QClericSpell");

	Q_BMSentry.Allocate();//"QBMSentry");

	Q_Building.Allocate();//"QBMSentry");

	Q_Object.Allocate();//"QObject");

	Q_VoxelDamage.Allocate();//"QVoxelDamage");

	Q_MeMPathway.Allocate();//"QMeMPathway");

	Q_Lightning.Allocate();//"QLightning");

	Q_EnergyWake.Allocate();//"QEnergyWake");

	Q_NetEffectControl.Allocate();//"QNetEffectControl");

	Q_HealEnergy.Allocate();//"QHealEnergy");

	Q_NetZoneENTITY.Allocate();//"QNetZoneENTITY");

	Q_StartPoints.Allocate();//"QStartPoints");

	Q_ANGELeditMAP.Allocate();//"QANGELeditMAP");

	Q_AvatarEntity.Allocate();//"QAvatarEntity");

	Q_Netplayer.Allocate();//"QNetplayer");

	Q_PlayerEntity.Allocate();//"QPlayerEntity");

	Q_Bullet.Allocate();//"QBullet");

	Q_BulletHit.Allocate();//"QBulletHit");

	Q_Cartridge.Allocate();//"QCartridge");

	Q_MFlash.Allocate();//"QMFlash");

	Q_Cloud.Allocate();//"QCloud");

	Q_EnergyMatrix.Allocate();//"QEnergyMatrix");

	Q_MeleeHit.Allocate();//"QMeleeHit");

	Q_BBlood.Allocate();//"QBBlood");

	Q_PowerFlash.Allocate();//"QPowerFlash");

	Q_HHSpike.Allocate();//"QHHSpike");

	Q_HealSpark.Allocate();//"QHealSpark");

	Q_BSparks.Allocate();//"QBSparks");

	Q_VaporTrail.Allocate();//"QVaporTrail");

	Q_WindWake.Allocate();//"QWindWake");

	Q_PinEffectMesh.Allocate();//"QPinEffectMesh");

	Q_Decal.Allocate();//"QDecal");

	Q_ValidPointer.Allocate();//"QValidPointer");
#endif
}

void Q_COREFunctions::CoreDeAllocate(void)
	{
	printf(":::QDeAllocate\n");

	// DeAllocate Global Variables Structure
	/*_.DeAllocate();

	// DeAllocate Q Media Assets
	Media.DeAllocate();

	// Prepare // {- Q Player -}
	player.DeAllocate();

	// Prepare // {- Q Forge -}
	Q_Forge.DeAllocate();

	// Prepare // {- NNBOTrewardSTATS -}
	NNBOTrewardSTATS.DeAllocate();

	// Prepare // {- Q_NNBot -}
	Q_NNBot.DeAllocate();

	// Prepare // {- Q_PntSprite -}
	Q_PntSprite.DeAllocate();

	// Prepare // {- Q_SEnergy -}
	Q_SEnergy.DeAllocate();

	// Prepare // {- Q_LEnergy -}
	Q_LEnergy.DeAllocate();

	// Prepare // {- Q_Explosion -}
	Q_Explosion.DeAllocate();

	// Prepare // {- Q_ClericPlasma -}
	Q_ClericPlasma.DeAllocate();

	// Prepare // {- Q_ClericSpell -}
	Q_ClericSpell.DeAllocate();

	Q_BMSentry.DeAllocate();

	Q_Object.DeAllocate();

	Q_VoxelDamage.DeAllocate();

	Q_MeMPathway.DeAllocate();

	Q_Lightning.DeAllocate();

	Q_EnergyWake.DeAllocate();

	Q_NetEffectControl.DeAllocate();

	Q_HealEnergy.DeAllocate();

	Q_NetZoneENTITY.DeAllocate();

	Q_StartPoints.DeAllocate();

	Q_ANGELeditMAP.DeAllocate();

	Q_AvatarEntity.DeAllocate();

	Q_Netplayer.DeAllocate();

	Q_PlayerEntity.DeAllocate();

	Q_Bullet.DeAllocate();

	Q_BulletHit.DeAllocate();

	Q_Cartridge.DeAllocate();

	Q_MFlash.DeAllocate();

	Q_Cloud.DeAllocate();

	Q_EnergyMatrix.DeAllocate();

	Q_MeleeHit.DeAllocate();

	Q_BBlood.DeAllocate();

	Q_PowerFlash.DeAllocate();

	Q_HHSpike.DeAllocate();

	Q_HealSpark.DeAllocate();

	Q_BSparks.DeAllocate();

	Q_VaporTrail.DeAllocate();

	Q_WindWake.DeAllocate();

	Q_PinEffectMesh.DeAllocate();

	//Q_Decal.DeAllocate();*/
	}

void Q_COREFunctions::StructureAInitialize(void)
{
	g_StructureAString.push_back("BIP01");
	g_StructureAString.push_back("BIP01 FOOTSTEPS");
	g_StructureAString.push_back("BIP01 PELVIS");
	g_StructureAString.push_back("BIP01 SPINE");
	g_StructureAString.push_back("BIP01 SPINE1");
	g_StructureAString.push_back("BIP01 SPINE2");
	g_StructureAString.push_back("BIP01 SPINE3");
	g_StructureAString.push_back("BIP01 NECK");
	g_StructureAString.push_back("BIP01 HEAD");
	g_StructureAString.push_back("BIP01 L CLAVICLE");
	g_StructureAString.push_back("BIP01 L UPPERARM");
	g_StructureAString.push_back("BIP01 L FOREARM");
	g_StructureAString.push_back("BIP01 L HAND");
	g_StructureAString.push_back("BIP01 L FINGER0");
	g_StructureAString.push_back("BIP01 L FINGER01");
	g_StructureAString.push_back("BIP01 L FINGER02");
	g_StructureAString.push_back("BIP01 L FINGER1");
	g_StructureAString.push_back("BIP01 L FINGER11");
	g_StructureAString.push_back("BIP01 L FINGER12");
	g_StructureAString.push_back("BIP01 L FINGER2");
	g_StructureAString.push_back("BIP01 L FINGER21");
	g_StructureAString.push_back("BIP01 L FINGER22");
	g_StructureAString.push_back("BIP01 L FINGER3");
	g_StructureAString.push_back("BIP01 L FINGER31");
	g_StructureAString.push_back("BIP01 L FINGER32");
	g_StructureAString.push_back("BIP01 L FINGER4");
	g_StructureAString.push_back("BIP01 L FINGER41");
	g_StructureAString.push_back("BIP01 L FINGER42");
	g_StructureAString.push_back("BIP01 R CLAVICLE");
	g_StructureAString.push_back("BIP01 R UPPERARM");
	g_StructureAString.push_back("BIP01 R FOREARM");
	g_StructureAString.push_back("BIP01 R HAND");
	g_StructureAString.push_back("BIP01 R FINGER0");
	g_StructureAString.push_back("BIP01 R FINGER01");
	g_StructureAString.push_back("BIP01 R FINGER02");
	g_StructureAString.push_back("BIP01 R FINGER1");
	g_StructureAString.push_back("BIP01 R FINGER11");
	g_StructureAString.push_back("BIP01 R FINGER12");
	g_StructureAString.push_back("BIP01 R FINGER2");
	g_StructureAString.push_back("BIP01 R FINGER21");
	g_StructureAString.push_back("BIP01 R FINGER22");
	g_StructureAString.push_back("BIP01 R FINGER3");
	g_StructureAString.push_back("BIP01 R FINGER31");
	g_StructureAString.push_back("BIP01 R FINGER32");
	g_StructureAString.push_back("BIP01 R FINGER4");
	g_StructureAString.push_back("BIP01 R FINGER41");
	g_StructureAString.push_back("BIP01 R FINGER42");
	g_StructureAString.push_back("BIP01 L THIGH");
	g_StructureAString.push_back("BIP01 L CALF");
	g_StructureAString.push_back("BIP01 L FOOT");
	g_StructureAString.push_back("BIP01 L TOE0");
	g_StructureAString.push_back("BIP01 R THIGH");
	g_StructureAString.push_back("BIP01 R CALF");
	g_StructureAString.push_back("BIP01 R FOOT");
	g_StructureAString.push_back("BIP01 R TOE0");

	_->StructureAInt.push_back(0);
	_->StructureAInt.push_back(1);
	_->StructureAInt.push_back(2);
	_->StructureAInt.push_back(3);
	_->StructureAInt.push_back(4);
	_->StructureAInt.push_back(5);
	_->StructureAInt.push_back(6);
	_->StructureAInt.push_back(7);
	_->StructureAInt.push_back(8);
	_->StructureAInt.push_back(9);
	_->StructureAInt.push_back(10);
	_->StructureAInt.push_back(11);
	_->StructureAInt.push_back(12);
	_->StructureAInt.push_back(13);
	_->StructureAInt.push_back(14);
	_->StructureAInt.push_back(15);
	_->StructureAInt.push_back(16);
	_->StructureAInt.push_back(17);
	_->StructureAInt.push_back(18);
	_->StructureAInt.push_back(19);
	_->StructureAInt.push_back(20);
	_->StructureAInt.push_back(21);
	_->StructureAInt.push_back(22);
	_->StructureAInt.push_back(23);
	_->StructureAInt.push_back(24);
	_->StructureAInt.push_back(25);
	_->StructureAInt.push_back(26);
	_->StructureAInt.push_back(27);
	_->StructureAInt.push_back(28);
	_->StructureAInt.push_back(29);
	_->StructureAInt.push_back(30);
	_->StructureAInt.push_back(31);
	_->StructureAInt.push_back(32);
	_->StructureAInt.push_back(33);
	_->StructureAInt.push_back(34);
	_->StructureAInt.push_back(35);
	_->StructureAInt.push_back(36);
	_->StructureAInt.push_back(37);
	_->StructureAInt.push_back(38);
	_->StructureAInt.push_back(39);
	_->StructureAInt.push_back(40);
	_->StructureAInt.push_back(41);
	_->StructureAInt.push_back(42);
	_->StructureAInt.push_back(43);
	_->StructureAInt.push_back(44);
	_->StructureAInt.push_back(45);
	_->StructureAInt.push_back(46);
	_->StructureAInt.push_back(47);
	_->StructureAInt.push_back(48);
	_->StructureAInt.push_back(49);
	_->StructureAInt.push_back(50);
	_->StructureAInt.push_back(51);
	_->StructureAInt.push_back(52);
	_->StructureAInt.push_back(53);
	_->StructureAInt.push_back(54);
}

int Q_COREFunctions::StructureA(const char* String)
{
	std::string f_MapString = String;
	bool Match = false;
	int MatchCount = 0;

	if(g_StructureAString.size() > 0)
		{
		for(count = 0; count < 55; count++)
		while(!Match)
			{
			if(count < g_StructureAString.size())
				{
				if(f_MapString.length() == g_StructureAString[count].length())
					{
					if(f_MapString.compare(g_StructureAString[count].c_str()) == 0)
						{
						Match = true;
						MatchCount = count;
						}
					}
				}
		
			count++;
			}
		}

	return _->StructureAInt[MatchCount];
}

void Q_COREFunctions::DigitizeNumber(float Input)
	{
	//### Calculate Number of digits
	if(Input <= 9999)
		{
		if(Input <= 999)
			{
			if(Input <= 99)
				{
				if(Input <= 9)
					{
					//### Single Digit Calculation
					player[g_Player]->MSG_TESTDigits = 1;
					}
				else
					{
					//### TWO Digit Calculation
					player[g_Player]->MSG_TESTDigits = 2;
					}
				}
			else
				{
				//### THREE Digit Calculation
				player[g_Player]->MSG_TESTDigits = 3;
				}
			}
		else
			{
			//### FOUR Digit Calculation
			player[g_Player]->MSG_TESTDigits = 4;
			}
		}
	else
		{
		//### FIVE Digit Calculation
		player[g_Player]->MSG_TESTDigits = 5;
		}

	if(player[g_Player]->MSG_TESTDigits == 5)
		{
		//### RESET DIGIT
		player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 0;

		if(Input >= 10000 && Input < 20000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 1;
			Input -= 10000;
			}
		if(Input >= 20000 && Input < 30000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 2;
			Input -= 20000;
			}
		if(Input >= 30000 && Input < 40000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 3;
			Input -= 30000;
			}
		if(Input >= 40000 && Input < 50000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 4;
			Input -= 40000;
			}
		if(Input >= 50000 && Input < 60000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 5;
			Input -= 50000;
			}
		if(Input >= 60000 && Input < 70000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 6;
			Input -= 60000;
			}
		if(Input >= 70000 && Input < 80000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 7;
			Input -= 70000;
			}
		if(Input >= 80000 && Input < 90000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 8;
			Input -= 80000;
			}
		if(Input >= 90000 && Input < 100000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 9;
			Input -= 90000;
			}

		player[g_Player]->MSG_NomDigits++;
		player[g_Player]->MSG_TESTDigits--;
		}

	if(player[g_Player]->MSG_TESTDigits == 4)
		{
		//### RESET DIGIT
		player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 0;

		if(Input >= 1000 && Input < 2000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 1;
			Input -= 1000;
			}
		if(Input >= 2000 && Input < 3000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 2;
			Input -= 2000;
			}
		if(Input >= 3000 && Input < 4000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 3;
			Input -= 3000;
			}
		if(Input >= 4000 && Input < 5000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 4;
			Input -= 4000;
			}
		if(Input >= 5000 && Input < 6000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 5;
			Input -= 5000;
			}
		if(Input >= 6000 && Input < 7000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 6;
			Input -= 6000;
			}
		if(Input >= 7000 && Input < 8000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 7;
			Input -= 7000;
			}
		if(Input >= 8000 && Input < 9000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 8;
			Input -= 8000;
			}
		if(Input >= 9000 && Input < 10000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 9;
			Input -= 9000;
			}

		player[g_Player]->MSG_NomDigits++;
		player[g_Player]->MSG_TESTDigits--;
		}

	if(player[g_Player]->MSG_TESTDigits == 3)
		{
		//### RESET DIGIT
		player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 0;

		if(Input >= 100 && Input < 200)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 1;
			Input -= 100;
			}
		if(Input >= 200 && Input < 300)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 2;
			Input -= 200;
			}
		if(Input >= 300 && Input < 400)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 3;
			Input -= 300;
			}
		if(Input >= 400 && Input < 500)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 4;
			Input -= 400;
			}
		if(Input >= 500 && Input < 600)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 5;
			Input -= 500;
			}
		if(Input >= 600 && Input < 700)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 6;
			Input -= 600;
			}
		if(Input >= 700 && Input < 800)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 7;
			Input -= 700;
			}
		if(Input >= 800 && Input < 900)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 8;
			Input -= 800;
			}
		if(Input >= 900 && Input < 1000)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 9;
			Input -= 900;
			}

		player[g_Player]->MSG_NomDigits++;
		player[g_Player]->MSG_TESTDigits--;
		}

	if(player[g_Player]->MSG_TESTDigits == 2)
		{
		//### RESET DIGIT
		player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 0;

		if(Input >= 10 && Input < 20)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 1;
			Input -= 10;
			}
		if(Input >= 20 && Input < 30)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 2;
			Input -= 20;
			}
		if(Input >= 30 && Input < 40)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 3;
			Input -= 30;
			}
		if(Input >= 40 && Input < 50)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 4;
			Input -= 40;
			}
		if(Input >= 50 && Input < 60)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 5;
			Input -= 50;
			}
		if(Input >= 60 && Input < 70)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 6;
			Input -= 60;
			}
		if(Input >= 70 && Input < 80)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 7;
			Input -= 70;
			}
		if(Input >= 80 && Input < 90)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 8;
			Input -= 80;
			}
		if(Input >= 90 && Input < 100)
			{
			player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 9;
			Input -= 90;
			}

		player[g_Player]->MSG_NomDigits++;
		player[g_Player]->MSG_TESTDigits--;
		}

	if(player[g_Player]->MSG_TESTDigits == 1)
		{
		//### RESET DIGIT
		player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 0;

		if(Input == 0)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 0; }
		if(Input == 1)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 1; }
		if(Input == 2)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 2; }
		if(Input == 3)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 3; }
		if(Input == 4)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 4; }
		if(Input == 5)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 5; }
		if(Input == 6)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 6; }
		if(Input == 7)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 7; }
		if(Input == 8)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 8; }
		if(Input == 9)
			{ player[g_Player]->MSG_Digit[player[g_Player]->MSG_NomDigits] = 9; }

		player[g_Player]->MSG_NomDigits++;
		}
	}


void Q_COREFunctions::ShowLine(QpoVec3d *Start, QpoVec3d *End, QpoVec3d *CameraPos, float width, unsigned int bitmapPtr, float alpha, float red, float green, float blue, int Flags)
{
	/*
	** draw a laser beam between two speciied points
	** beam is comprised of flat polygons orientated
	** so that they always face camera
	*/
	QpoVec3d CameraVector; //vector between camera pos and Start
	QpoVec3d LaserVector;	//vector between end and start	

	QpoVec3d StartRight, StartLeft; //note that these are VECTORS
	QpoVec3d EndRight, EndLeft;			  //not POSITIONS
									//will have to translate
									//beam when finished
	//char buf[1024];

	//'right' means the direction the vector product goes in

	//sprintf(buf,"start: %.2f, %.2f, %.2f",Start->X, Start->Y, Start->Z);
	//geEngine_Printf(Engine, Width-300,100,buf);
	//sprintf(buf,"end: %.2f, %.2f, %.2f",End->X, End->Y, End->Z);
	//geEngine_Printf(Engine, Width-300,130,buf);

	Qpo->Vec3d_Subtract(CameraPos, Start, &CameraVector);

	Qpo->Vec3d_Subtract(End, Start, &LaserVector);

	Qpo->Vec3d_CrossProduct(&CameraVector, &LaserVector, &StartRight);


	Qpo->Vec3d_Copy(&StartRight, &StartLeft);
	Qpo->Vec3d_Inverse(&StartLeft);
	Qpo->Vec3d_Normalize(&StartRight);
	Qpo->Vec3d_Normalize(&StartLeft);
	Qpo->Vec3d_Scale(&StartLeft, width, &StartLeft);
	Qpo->Vec3d_Scale(&StartRight,width, &StartRight);
	Qpo->Vec3d_Add(End, &StartLeft, &EndLeft);
	Qpo->Vec3d_Add(End, &StartRight, &EndRight);

	//08-09-01 have to calculate START *points* as well, we have only
	//calculated start *vectors* from start midpoint, need to calculate
	//endge points as well. Confused yet...?
	Qpo->Vec3d_Add(Start, &StartLeft, &StartLeft);
	Qpo->Vec3d_Add(Start, &StartRight, &StartRight);

	
	Q.DrawRectFromVec3ds(
		&StartLeft, 
		&StartRight,
		&EndRight, 
		&EndLeft, 
		bitmapPtr,
		alpha,
		red,
		green,
		blue,Flags);

}


float Q_COREFunctions::AnglesToPoint(QpoVec3d *s, QpoVec3d *d, QpoVec3d *a)
{
	float x,l;

	Qpo->Vec3d_Subtract( d,s,a );
	l = Qpo->Vec3d_Length(a);

	//protect from Div by zero
	if(l>0.0f)
		{
		x = a->x;
		a->x = (float)( PI*0.5 ) - (float)acos(a->y / l);
		a->y = (float)atan2( x , a->z ) + PI;
		// roll is zero - always!
		a->z = 0.0;
		}

	return l;
}


//--------------------------------------------------------------------- 
void Q_COREFunctions::DrawInVector(QpoTransform XForm, QpoVec3d Pos) 

// Purpose: add polys to the world representing the In vector 
// The In vector of an XForm is the vector that points in the direction in which it is oriented 

//NOTE: I have not debugged passing in XForm and Pos-- I just accessed globals in my program. I think this is correct, though. 

{ 
QpoVec3d In;
QpoVec3d tempPos;


Qpo->Transform_GetIn (&XForm, &In);

tempPos = Pos;
//tempPos.y += 75; //Get the vector up off the floor (for an actor)--Optional 
Q.DrawVector (tempPos, In, 50);
} 


//--------------------------------------------------------------------- 
void Q_COREFunctions::DrawVector(QpoVec3d Pos, QpoVec3d Vector, int Mult) 

// Purpose: add polys to the world representing the vector 

//Input: Pos (passed by reference)-- The position of the base of the vector 
// Vector (passed by ref) -- The vector to draw 
// Mult -- A multiplier, to make the vector big enough to see (I use about 50) 

//Note: This code is modified from the Draw Ext Box function from Seven's ProjectZ, which in turn is code modified from the genesis drawbbox.c file 

{ 
float dx; 
float dy; 
float dz; 
QpoVec3d In; 
int i; 
QpoVec3d Verts[8]; 
QpoVec3d* Faces[6][4] = { 
{ &Verts[0], &Verts[1], &Verts[2], &Verts[3] }, //Top 
{ &Verts[4], &Verts[5], &Verts[6], &Verts[7] }, //Bottom 
{ &Verts[3], &Verts[2], &Verts[6], &Verts[7] }, //Side 
{ &Verts[1], &Verts[0], &Verts[4], &Verts[5] }, //Side 
{ &Verts[0], &Verts[3], &Verts[7], &Verts[4] }, //Front 
{ &Verts[2], &Verts[1], &Verts[5], &Verts[6] }, //Back 
};
QpoVec3d Height;
QpoVec3d Right;

//First set all points at the vector's origin (Pos) 
for (i = 0; i < 8; i++) { 
Verts[i] = Pos; 
} 

//Now extrude top based on length of vector, scaled by Mult 
for (i = 0; i < 4; i++) { 
Qpo->Vec3d_AddScaled(&Verts[i], Mult, &Vector, &Verts[i]);
} 

//Now extrude "front" side
Qpo->Vec3d_Set(&Height, 0, 5, 0);
Qpo->Vec3d_Add (&Verts[0], &Height, &Verts[0]); 
Qpo->Vec3d_Add (&Verts[3], &Height, &Verts[3]); 
Qpo->Vec3d_Add (&Verts[4], &Height, &Verts[4]); 
Qpo->Vec3d_Add (&Verts[7], &Height, &Verts[7]); 

//Now extrude the "right" side 
//The cross product returns a vector at right angles from the two imputs 
Qpo->Vec3d_CrossProduct (&Vector, &Height, &Right); 
Qpo->Vec3d_Normalize (&Right); 
Qpo->Vec3d_AddScaled (&Verts[2], 5, &Right, &Verts[2]); 
Qpo->Vec3d_AddScaled (&Verts[3], 5, &Right, &Verts[3]); 
Qpo->Vec3d_AddScaled (&Verts[6], 5, &Right, &Verts[6]); 
Qpo->Vec3d_AddScaled (&Verts[7], 5, &Right, &Verts[7]); 

//Now draw faces.
//for (i = 0; i < 6; i++) DrawFace2(&Faces[i][0]);
}

//-------------------------------------------------------------------
// Load Setup File
//-------------------------------------------------------------------

void Q_COREFunctions::LoadSetupFile(void)
{
	// Open our config file and get the gamma, width, height and our driver
    _->stream = fopen("Config\\video.ini","r");
    //fscanf(stream,"%s",&ourdriver);
    //fscanf(stream,"%d",&CWidth);
    //fscanf(stream,"%d",&CHeight);
    fclose(_->stream);

	_->stream = fopen("Config\\gamma.ini","r");
	fscanf(_->stream,"%f",&_->gama);
	fclose(_->stream);
}

//-------------------------------------------------------------------
// ShutDown
//-------------------------------------------------------------------

void Q_COREFunctions::ShutDown(void)
{
	
}

};