/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Character Item and Attributes-
	*/#include "pch.h"/*- Minor Component -Avatar Spawn Item-

*/

//### INCLUDES
#include "SecondaryAppWindowPageOGL.h"

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include <stdio.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-WE-CloudControl.h"
#include "Q-WE-PntSprite.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

//##### -+ Avatar Item Spawning +- #####

Q_ItemRef Q_COREFunctions::CreateAvatarItem(int CharDataID, float VICTIMLVL)
{
	Q_ItemRef	ItemREF;

	int			ItemREFERENCE = 0;
	float		QUALFinger;
	float		QUALLevel = 0.0f;
	float		DECFinger;
	float		LVLFinger;
	float		QUALFactor = 0.0f;
	float		LVLRestrict;
	float		RAND;
	float		RANDinc;
	float		ATTRadd = 0;
	int			HYPERITEM = 0;
	int			EFFECTID;
	int			EFFECTON = 0;
	int			ATTR00=0,ATTR01=0,ATTR02=0,ATTR03=0,ATTR04=0,ATTR05=0,ATTR06=0,ATTR07=0,ATTR08=0,ATTR09=0,ATTR10=0,ATTR11=0,ATTR12=0,ATTR13=0,ATTR14=0,ATTR15=0,ATTR16=0,ATTR17=0,ATTR18=0,ATTR19=0,ATTR20=0,ATTR21=0,ATTR22=0,ATTR23=0,ATTR24=0;

	if(player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS < 150)
		{
		//### Create Item for attacking Avatar
		DECFinger = ((float)rand() / 32767) * 4;

		if(DECFinger >= 0 && DECFinger < 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 0;
		if(DECFinger >= 1 && DECFinger < 2) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 1;
		if(DECFinger >= 2 && DECFinger < 3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 2;
		if(DECFinger >= 3 && DECFinger < 4) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 3;

		//if(DECFinger >= 0 && DECFinger < 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 0;
		//if(DECFinger >= 1 && DECFinger < 2) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 0;
		//if(DECFinger >= 2 && DECFinger < 3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 0;
		//if(DECFinger >= 3 && DECFinger < 4) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 0;
		//if(DECFinger >= 4 && DECFinger < 5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 0;
		//if(DECFinger >= 5 && DECFinger < 6) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 1;
		//if(DECFinger >= 6 && DECFinger < 7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 2;
		//if(DECFinger >= 7 && DECFinger < 8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 3;
		if(DECFinger >= 8 && DECFinger < 9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 4;
		if(DECFinger >= 9 && DECFinger < 10) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 5;
		if(DECFinger >= 10 && DECFinger < 11) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 6;
		if(DECFinger >= 11 && DECFinger < 12) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 7;
		if(DECFinger >= 12 && DECFinger < 13) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 8;
		if(DECFinger >= 13 && DECFinger < 14) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type = 9;


		//#### SELECT ITEM TYPE
		if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 0)
			{
			DECFinger = ((float)rand() / 32767) * 17.5;

			if(DECFinger >= 0 && DECFinger < 2)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "w_sg5520.cal3d");
				//sprintf_s(//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "Actors\\\\awphighq.cal3d";
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "AstRifle  ");
				ItemREFERENCE = 1;
				}
			if(DECFinger >= 2 && DECFinger < 3)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "famassvX.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "Famass    ");
				ItemREFERENCE = 2;
				}
			if(DECFinger >= 3 && DECFinger < 4)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "IncaMKII.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "Incapacit ");
				ItemREFERENCE = 3;
				}
			if(DECFinger >= 4 && DECFinger < 4.5)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "MiniGUN1.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "MINIGUN   ");
				ItemREFERENCE = 4;
				}
			if(DECFinger >= 4.5 && DECFinger < 6)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "M4A1actr.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "M4-A1     ");
				ItemREFERENCE = 5;
				}
			if(DECFinger >= 6 && DECFinger < 8)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "Swat552X.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "Swat552    ");
				ItemREFERENCE = 6;
				}
			if(DECFinger >= 8 && DECFinger < 10.5)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "ak47lowq.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "AK47     ");
				ItemREFERENCE = 7;
				}
			if(DECFinger >= 10.5 && DECFinger < 11.5)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "psg1lowq.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "PSG-1     ");
				ItemREFERENCE = 8;
				}
			if(DECFinger >= 11.5 && DECFinger < 14)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "spas12lq.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "Spas12    ");
				ItemREFERENCE = 9;
				}
			if(DECFinger >= 14 && DECFinger < 16)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "g3lowqua.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "G3        ");
				ItemREFERENCE = 10;
				}
			if(DECFinger >= 16 && DECFinger < 17)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "l96a1low.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "l96a1     ");
				ItemREFERENCE = 11;
				}
			if(DECFinger >= 17 && DECFinger < 17.5)
				{
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemActorREF, "awphighq.cal3d");
				//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "AWP       ");
				ItemREFERENCE = 12;
				}
			}

		if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 1)
			{
			//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "HeadArmour");
			ItemREFERENCE = 100;
			}

		if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 2)
			{
			//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "UppArmour ");
			ItemREFERENCE = 101;
			}

		if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 3)
			{
			//sprintf_s(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Name, "LowArmour ");
			ItemREFERENCE = 102;
			}

		//####### --- Factor based QUALITY LEVEL --- #######
		QUALFinger = ((float)rand() / 32767) * 49.75;

		if(QUALFinger >= 0 && QUALFinger < 10)			//Quality Level 01
			{ QUALLevel = 0; }

		if(QUALFinger >= 10 && QUALFinger < 19)			//Quality Level 01
			{ QUALLevel = 0.1; }

		if(QUALFinger >= 19 && QUALFinger < 27)			//Quality Level 02
			{ QUALLevel = 0.2; }

		if(QUALFinger >= 27 && QUALFinger < 34)			//Quality Level 03
			{ QUALLevel = 0.3; }

		if(QUALFinger >= 34 && QUALFinger < 39)			//Quality Level 04
			{ QUALLevel = 0.4; }

		if(QUALFinger >= 39 && QUALFinger < 43)			//Quality Level 05
			{ QUALLevel = 0.5; }

		if(QUALFinger >= 43 && QUALFinger < 46)			//Quality Level 06
			{ QUALLevel = 0.6; }
		
		if(QUALFinger >= 46 && QUALFinger < 48)			//Quality Level 07
			{ QUALLevel = 0.7; }

		if(QUALFinger >= 48 && QUALFinger < 49)			//Quality Level 08
			{ QUALLevel = 0.8; }

		if(QUALFinger >= 49 && QUALFinger < 49.5)		//Quality Level 09
			{ QUALLevel = 0.9; }

		if(QUALFinger >= 49.5 && QUALFinger < 49.75)	//Quality Level 10
			{ QUALLevel = 1; }

		//#######  - Item Level Restrictions -  #######
		LVLFinger = VICTIMLVL / 1000;	//IMP add enemy level factor
		//if(LVLFinger > 1) LVLFinger = 1;
		if(LVLFinger < 0) LVLFinger = 0;
		LVLRestrict = player[g_Player]->BFO.CharDATA[CharDataID].Level / 1000;
		//if(LVLRestrict > 1) LVLRestrict = 1;
		if(LVLRestrict < 0) LVLRestrict = 0;
		QUALFactor = (QUALLevel + (LVLFinger * (QUALLevel + 0.5)) + (LVLRestrict * (QUALLevel + 0.5))) / 3;
		if(QUALFactor > 1) QUALFactor = 1;
		if(QUALFactor < 0) QUALFactor = 0;
		
		switch(ItemREFERENCE)
			{
			case 1:	//## AstRifle ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 300;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 150;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 550) + 300;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 850) + 700;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 850;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1150) + 1000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1350) + 1200;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 1500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 200;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 300) + 100;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 400) + 200;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 300;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 600) + 400;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 800) + 600;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1000;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 150;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 200;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1200) + 1000;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3300;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3600;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4350;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3700;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4300;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4550;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 600) + 4400;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 0;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;


			case 2:	//## Famass ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 100;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 150) + 50;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 200) + 100;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 300) + 200;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 450) + 300;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 500) + 450;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 650;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 1000;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 50;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 50) + 50;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 100) + 100;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 200) + 200;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 300) + 300;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 400) + 400;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 500;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 700;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 250;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 500;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 550) + 700;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 700) + 800;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 850) + 850;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1000) + 900;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 200)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 200 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 200)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 200 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 200)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3700;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 4000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4600;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 200 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3800;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4200;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4550;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3600;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3900;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4200;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4750;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3700;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 4000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 400) + 4600;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3700;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 4000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4600;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4850;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1200)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1200 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1600)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1600 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 7.900012;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -25.799892;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -1.200000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = -11.600026;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 7;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 7;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 7;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 7;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 7;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.1));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				} break;

			case 3:	//## Incapacitator ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 300;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 150;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 550) + 300;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 850) + 700;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 850;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1150) + 1000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1350) + 1200;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 1500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 200;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 300) + 100;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 400) + 200;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 300;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 600) + 400;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 800) + 600;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1000;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 150;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 200;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1200) + 1000;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3300;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3600;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4350;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3700;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4300;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4550;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 600) + 4400;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 2;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;

			case 4:	//## MINIGUN ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 300;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 150;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 550) + 300;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 850) + 700;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 850;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1150) + 1000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1350) + 1200;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 1500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 200;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 300) + 100;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 400) + 200;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 300;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 600) + 400;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 800) + 600;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1000;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 150;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 200;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1200) + 1000;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3300;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3600;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4350;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3700;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4300;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4550;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 600) + 4400;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 2;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 2;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;

			case 5:	//## M4-A1 ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 300;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 150;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 550) + 300;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 850) + 700;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 850;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1150) + 1000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1350) + 1200;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 1500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 450;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 625) + 600;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 775) + 800;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 875) + 1000;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1200;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1200) + 1400;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1350) + 1600;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1700) + 1800;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 150;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 200;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1200) + 1000;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3600;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3700;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 4000;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4550;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3200;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3500;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 3900;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3300;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3600;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 3900;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4200;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4450;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3400;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3700;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4000;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 500) + 4300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3400;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3700;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4550;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1800;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2300;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2800;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3800;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 4700;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.050000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 3.749998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -10.650022;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.850000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -1.600000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 5.850004;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 0;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.7));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.7));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.3));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;

			case 6:	//## Swat552 ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 300;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 150;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 550) + 300;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 850) + 700;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 850;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1150) + 1000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1350) + 1200;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 1500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 450;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 625) + 600;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 775) + 800;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 875) + 1000;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1200;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1200) + 1400;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1350) + 1600;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1700) + 1800;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 300) + 250;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 400;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 550) + 650;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 700) + 800;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1000) + 1000;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1300) + 1200;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3600;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 3900;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4200;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4450;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3100;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3400;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 3800;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4150;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4400;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3200;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 3800;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4200;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3300;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3600;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 3900;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 400) + 4200;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4400;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3300;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 3600;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 3900;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 4200;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 150) + 4450;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1800;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2300;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2800;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3800;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1600) + 1700;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1300) + 2200;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 950) + 2700;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 3700;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 4700;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.050000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 3.749998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -10.650022;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.850000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -1.600000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 5.850004;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 0;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.7));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.7));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.3));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.3));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				} break;

			case 7:	//## AK47 ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 700;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 800) + 550;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 950) + 700;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 1000;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1250) + 1100;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1400) + 1250;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1450) + 1400;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1650) + 1600;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1800) + 1900;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 450;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 625) + 600;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 775) + 800;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 875) + 1000;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1200;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1200) + 1400;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1350) + 1600;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1700) + 1800;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 150;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 200;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1200) + 1000;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1900) + 1900;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1600) + 900;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1400) + 800;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 900;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 750;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2400) + 1650;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1900) + 1400;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1600) + 900;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1100) + 650;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 900;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 1750;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1900) + 1900;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1800) + 1400;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1400) + 1100;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 1250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2900) + 2400;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2800) + 1900;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2200) + 1650;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1400) + 1300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1400) + 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2400) + 3400;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3400) + 2400;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2900) + 1400;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1900) + 1400;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1400) + 900;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3600;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3700;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 4000;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4550;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3200;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3500;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 3900;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3300;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3600;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 3900;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4200;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4450;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2800)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3400;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3700;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4000;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 500) + 4300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2800 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3400;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 3700;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 4300;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 4550;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1400) + 1600;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1100) + 2100;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 750) + 2600;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 3600;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 900)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1400) + 1500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1100) + 2000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 750) + 2500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 3500;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 900 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1550)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1400) + 1500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1100) + 2000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 750) + 2500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 3500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1550 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2200)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1400) + 1500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1100) + 2000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 750) + 2500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 3500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2200 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1400) + 1500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1100) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 750) + 2500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 3500;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 400) + 4500;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 3.499998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -3.499998;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.000000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 1;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 1;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 1;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 1;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 1;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.3));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;

			case 8:	//## PSG-1 ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 3000;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 1750;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2000) + 2250;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2250) + 2750;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2125) + 2875;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2000) + 3000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 3500;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 500) + 4500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 500;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 350;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 700;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1300) + 1000;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1700) + 1500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2000) + 180;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2300) + 2000;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2500) + 2250;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 30) + 20;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 50) + 40;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 75) + 60;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 100) + 80;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 125) + 100;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 175) + 120;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 100;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 300;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 800;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 1000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 75) + 75;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 250;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 400;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 650) + 600;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 50) + 50;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 200;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 450;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 25) + 25;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 175) + 100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 200;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 350) + 300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 400;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 15) + 15;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 75;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 150;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 200;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4750;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4850;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4900;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4950;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4600;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4675;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 150) + 4750;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 125) + 4825;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4900;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 150) + 4600;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 175) + 4700;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 3900;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4300;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 3200;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 3500;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 125) + 3800;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 275) + 4300;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 400) + 4600;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 5;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 3;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 5;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 9;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 11;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 13;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				} break;

			case 9:	//## SPAS12 ##
				{
				//### WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 80;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 150) + 50;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 275) + 75;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 300) + 100;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 350) + 150;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 275;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 375) + 350;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 450) + 500;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 675) + 700;

				//### WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 80;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 150) + 50;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 275) + 75;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 300) + 100;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 350) + 150;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 400) + 275;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 375) + 350;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 450) + 500;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 675) + 700;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 30) + 20;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 50) + 40;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 75) + 60;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 100) + 80;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 125) + 100;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 175) + 120;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 275)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 100;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 300;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 800;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 1000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 275 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 550)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 75) + 75;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 250;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 400;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 650) + 600;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 550 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 825)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 50) + 50;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 200;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 450;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 825 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 25) + 25;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 175) + 100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 200;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 350) + 300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 400;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 1375)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 15) + 15;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 75;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 150;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 200;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 275)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1000) + 500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 1000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 450) + 1500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 2000;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 3000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 275 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 550)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1000) + 500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 450) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 2000;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 3000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 550 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 825)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1000) + 500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 1000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 450) + 1500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 2000;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 3000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 825 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1100)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1000) + 500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 700) + 1000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 450) + 1500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 2000;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 3000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1100 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 1375)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 1000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 1500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 2000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 3000;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 8.100013;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -0.050000;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = 1.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 32.899784;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 4;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 4;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 4;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 4;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 4;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 5) + 3;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 6) + 5;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 7) + 7;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 8) + 9;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 9) + 12;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 10) + 14;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 11) + 17;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 12) + 19;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = (((float)rand() / 32767) * 13) + 22;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;

			case 10:	//## G3 ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 300;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 400) + 150;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 550) + 300;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 850) + 700;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 850;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1150) + 1000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1350) + 1200;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 1500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 200;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 300) + 100;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 400) + 200;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 300;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 600) + 400;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 800) + 600;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 1000;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 200) + 150;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 350) + 200;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 450) + 450;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 600) + 600;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 900) + 800;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 1200) + 1000;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1500 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 300)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 300 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 700)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3300;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3600;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4350;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 700 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3700;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4300;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4550;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1500)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 600) + 4400;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4600;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 3800;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 700) + 4100;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 4400;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 350) + 4650;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 850)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 850 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1400)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1400 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 1200) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 850) + 2500;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 600) + 3500;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 500) + 4500;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 5;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 0;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 1;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 1;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 2;
				} break;

			case 11:	//## l96a1 ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 3000;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 1750;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2000) + 2250;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2250) + 2750;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2125) + 2875;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2000) + 3000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 3500;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 500) + 4500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 500;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 350;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 700;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1300) + 1000;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1700) + 1500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2000) + 180;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2300) + 2000;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2500) + 2250;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 30) + 20;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 50) + 40;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 75) + 60;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 100) + 80;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 125) + 100;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 175) + 120;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 100;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 300;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 800;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 1000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 75) + 75;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 250;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 400;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 650) + 600;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 50) + 50;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 200;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 450;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 25) + 25;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 175) + 100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 200;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 350) + 300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 400;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 15) + 15;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 75;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 150;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 200;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4750;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4850;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4900;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4950;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4600;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4675;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 150) + 4750;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 125) + 4825;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4900;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 150) + 4600;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 175) + 4700;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 3900;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4300;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 3200;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 3500;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 125) + 3800;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 275) + 4300;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 400) + 4600;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 5;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 5;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 3;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 5;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 9;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 11;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 13;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				} break;

			case 12:	//## AWP ##
				{
				//######## WEAPON DAMAGE
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = ((float)rand() / 32767) * 3000;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1000) + 1750;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2000) + 2250;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2250) + 2750;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2125) + 2875;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 2000) + 3000;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 1500) + 3500;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = (((float)rand() / 32767) * 500) + 4500;

				//######## WEAPON POWER
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = ((float)rand() / 32767) * 500;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 500) + 350;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 700) + 600;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1000) + 700;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1300) + 1000;
				if(DECFinger >= 95 && DECFinger <= 97.5) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 1700) + 1500;
				if(DECFinger >= 97.5 && DECFinger <= 98.75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2000) + 180;
				if(DECFinger >= 98.75 && DECFinger <= 99.375) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2300) + 2000;
				if(DECFinger >= 99.375 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = (((float)rand() / 32767) * 2500) + 2250;

				//### WEAPON AMMO
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 30) + 20;
				if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 50) + 40;
				if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 75) + 60;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 100) + 80;
				if(DECFinger >= 90 && DECFinger <= 95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 125) + 100;
				if(DECFinger >= 95 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = (((float)rand() / 32767) * 175) + 120;

				//#### WEAPON RECOIL HEIGHT
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilHeight = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON RECOIL DIST
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 300;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 250;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 1250;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1200) + 500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 700) + 250;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1250;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1300) + 1000;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 600;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = ((float)rand() / 32767) * 850;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 2000;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2300) + 1500;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1700) + 1250;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 900;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 350;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2000) + 3000;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 3000) + 2000;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 2500) + 1000;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1500) + 1000;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].RecoilDistance = (((float)rand() / 32767) * 1000) + 500;
					}

				//#### WEAPON FIRE RATE
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 100;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 300;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 600) + 500;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 800) + 800;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 1000) + 1000;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 75) + 75;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 250;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 400;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 650) + 600;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 900) + 800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 50) + 50;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 200;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 450;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 500) + 500;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 25) + 25;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 175) + 100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 200;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767)  * 350) + 300;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 400) + 400;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 15) + 15;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 100) + 75;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 200) + 150;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 250) + 200;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = (((float)rand() / 32767) * 300) + 300;
					}

				//#### WEAPON ACCURACY
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power >= 0 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 1000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 20) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4750;
					if(DECFinger >= 20 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4800;
					if(DECFinger >= 40 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4850;
					if(DECFinger >= 60 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4900;
					if(DECFinger >= 80 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4950;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 1000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 2000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 30) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4600;
					if(DECFinger >= 30 && DECFinger < 60) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4675;
					if(DECFinger >= 60 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 150) + 4750;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 125) + 4825;
					if(DECFinger >= 90 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4900;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 2000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 3000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 40) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 4400;
					if(DECFinger >= 40 && DECFinger < 72) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4500;
					if(DECFinger >= 72 && DECFinger < 82) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 150) + 4600;
					if(DECFinger >= 82 && DECFinger < 91) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 175) + 4700;
					if(DECFinger >= 91 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4800;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 3000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 4000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 45) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 3900;
					if(DECFinger >= 45 && DECFinger < 75) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 75) + 4100;
					if(DECFinger >= 75 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 4300;
					if(DECFinger >= 90 && DECFinger < 96) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 200) + 4500;
					if(DECFinger >= 96 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 300) + 4700;
					}
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage >= 4000 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage <= 5000)
					{
					DECFinger = ((float)rand() / 32767) * 100;

					if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 50) + 3200;
					if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 100) + 3500;
					if(DECFinger >= 80 && DECFinger < 93) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 125) + 3800;
					if(DECFinger >= 93 && DECFinger < 98) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 275) + 4300;
					if(DECFinger >= 98 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = (((float)rand() / 32767) * 400) + 4600;
					}

				//### Scope LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.x = 0.450000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.y = 4.650000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeLOC.z = -14.300035;

				//### Laser LOCATION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.x = 0.000000;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.y = -3.349998;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserLOC.z = 0.700000;

				//### Sound IDs
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_Fire = 6;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltOut = 6;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadBoltIn = 6;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipOut = 6;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QAS_ReloadClipIn = 6;

				//### Armour Factors
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;

				//############# =- QUALITY BASED VALUES -= #############

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Damage = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power *= (1 + ((QUALFactor - 0.5) * 0.75));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Power = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo *= (1 + ((QUALFactor - 0.5) * 0.5));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Ammo = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].FireRate = 5000;

				//### +- ACCURACY Quality Adjustment -+ ###
				if(QUALFactor >= 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 2500 || QUALFactor < 0.5 && player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy >= 2500) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 1.2));
				else player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy *= (1 + ((QUALFactor - 0.5) * 0.2));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Accuracy = 5000;

				//#### BULLET COUNT ADD CONDITIONAL FEW BULLET EJECTION
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].BulletCNT = 1;

				//### Scope TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 2;
				if(DECFinger >= 0.3 && DECFinger < 0.65) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 3;
				if(DECFinger >= 0.65 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 5;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 9;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 11;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ScopeTYPE = 13;

				//### Laser TYPE
				DECFinger = ((float)rand() / 32767) * 1;
				DECFinger = (DECFinger + QUALFactor) / 2;

				if(DECFinger >= 0 && DECFinger < 0.3) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.3 && DECFinger < 0.7) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.7 && DECFinger < 0.8) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.8 && DECFinger < 0.9) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.9 && DECFinger <= 0.95) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				if(DECFinger >= 0.95 && DECFinger <= 1) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].LaserTYPE = 0;
				} break;

			case 100:	//### HEAD ARMOUR
				{
				//### ARMOUR FACTOR
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 500) + 4500;

				//#### ARMOUR AMOUNT
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 500) + 4500;

				//#### ARMOUR REGENERATION
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 500) + 4500;


				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 5000;
				} break;

			case 101:	//### HEAD ARMOUR
				{
				//### ARMOUR FACTOR
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 500) + 4500;

				//#### ARMOUR AMOUNT
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 500) + 4500;

				//#### ARMOUR REGENERATION
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 500) + 4500;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 5000;
				} break;

			case 102:	//### HEAD ARMOUR
				{
				//### ARMOUR FACTOR
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = (((float)rand() / 32767) * 500) + 4500;

				//#### ARMOUR AMOUNT
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = (((float)rand() / 32767) * 500) + 4500;

				//#### ARMOUR REGENERATION
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 50) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = ((float)rand() / 32767) * 2000;
				if(DECFinger >= 50 && DECFinger < 80) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 1000) + 2000;
				if(DECFinger >= 80 && DECFinger < 90) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 1000) + 3000;
				if(DECFinger >= 90 && DECFinger < 97) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 500) + 4000;
				if(DECFinger >= 97 && DECFinger <= 100) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = (((float)rand() / 32767) * 500) + 4500;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourFACTOR = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourAMOUNT = 5000;

				//### +- Quality Adjustment -+ ###
				player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN *= (1 + ((QUALFactor - 0.5) * 0.15));

				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN < 0) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 0;
				if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN > 5000) player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ArmourREGEN = 5000;
				} break;
			}


		//##### QUALITY CHECK FOR ATTRIBUTES  #####

		if(QUALFactor > 0.7 && QUALFactor < 0.78)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = 0;
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = (((float)rand() / 32767) * 1.25);
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = (((float)rand() / 32767) * 1.5);
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = (((float)rand() / 32767) * 1.75);
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = (((float)rand() / 32767) * 2);
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = (((float)rand() / 32767) * 2.75);
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = (((float)rand() / 32767) * 3);
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = (((float)rand() / 32767) * 3.5);
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = (((float)rand() / 32767) * 4);
			}

		if(QUALFactor > 0.78 && QUALFactor > 0.86)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = (((float)rand() / 32767) * 1.75);
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = (((float)rand() / 32767) * 2);
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = (((float)rand() / 32767) * 2.5);
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = (((float)rand() / 32767) * 2.75);
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = (((float)rand() / 32767) * 3);
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = (((float)rand() / 32767) * 4.5);
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = (((float)rand() / 32767) * 5);
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = (((float)rand() / 32767) * 6);
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = (((float)rand() / 32767) * 7);

			if(DECFinger >= 97.5) HYPERITEM = 1;
			}

		if(QUALFactor > 0.86 && QUALFactor > 0.92)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = (((float)rand() / 32767) * 1.3) + 1;
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = (((float)rand() / 32767) * 1.5) + 1;
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = (((float)rand() / 32767) * 2.3) + 1;
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = (((float)rand() / 32767) * 2.75) + 1;
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = (((float)rand() / 32767) * 3.5) + 1;
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = (((float)rand() / 32767) * 3.5) + 2;
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = (((float)rand() / 32767) * 4) + 2;
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = (((float)rand() / 32767) * 5) + 2;
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = (((float)rand() / 32767) * 6) + 2;

			if(DECFinger >= 95) HYPERITEM = 1;
			}

		if(QUALFactor > 0.92 && QUALFactor > 0.96)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = (((float)rand() / 32767) * 1.5) + 2;
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = (((float)rand() / 32767) * 1.75) + 2;
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = (((float)rand() / 32767) * 2.25) + 2;
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = (((float)rand() / 32767) * 2.5) + 2;
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = (((float)rand() / 32767) * 2.75) + 2;
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = (((float)rand() / 32767) * 3.5) + 2;
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = (((float)rand() / 32767) * 4) + 2;
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = (((float)rand() / 32767) * 5) + 2;
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = (((float)rand() / 32767) * 6) + 2;

			if(DECFinger >= 95) HYPERITEM = 1;
			}

		if(QUALFactor > 0.96 && QUALFactor > 0.98)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = (((float)rand() / 32767) * 1.5) + 2;
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = (((float)rand() / 32767) * 2.5) + 2;
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = (((float)rand() / 32767) * 3) + 3;
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = (((float)rand() / 32767) * 3.5) + 3;
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = (((float)rand() / 32767) * 4.5) + 3;
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = (((float)rand() / 32767) * 5.75) + 3;
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = (((float)rand() / 32767) * 6) + 3;
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = (((float)rand() / 32767) * 8) + 3;
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = (((float)rand() / 32767) * 10) + 3;

			if(DECFinger >= 60) HYPERITEM = 1;
			}

		if(QUALFactor > 0.98 && QUALFactor > 0.995)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = (((float)rand() / 32767) * 1.5) + 3;
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = (((float)rand() / 32767) * 2.5) + 3;
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = (((float)rand() / 32767) * 3.5) + 4;
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = (((float)rand() / 32767) * 4.5) + 5;
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = (((float)rand() / 32767) * 5.5) + 4;
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = (((float)rand() / 32767) * 6) + 5;
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = (((float)rand() / 32767) * 8) + 5;
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = (((float)rand() / 32767) * 10) + 5;
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = (((float)rand() / 32767) * 12) + 6;

			if(DECFinger >= 30) HYPERITEM = 1;
			}

		if(QUALFactor > 0.995 && QUALFactor > 1)
			{
			DECFinger = ((float)rand() / 32767) * 100;
			if(DECFinger >= 0 && DECFinger < 30) ATTRadd = 6;
			if(DECFinger >= 30 && DECFinger < 60) ATTRadd = 7;
			if(DECFinger >= 60 && DECFinger < 80) ATTRadd = 8;
			if(DECFinger >= 80 && DECFinger < 90) ATTRadd = 9;
			if(DECFinger >= 90 && DECFinger <= 95) ATTRadd = 10;
			if(DECFinger >= 95 && DECFinger <= 97.5) ATTRadd = 12;
			if(DECFinger >= 97.5 && DECFinger <= 98.75) ATTRadd = 16;
			if(DECFinger >= 98.75 && DECFinger <= 99.375) ATTRadd = 20;
			if(DECFinger >= 99.375 && DECFinger <= 100) ATTRadd = 24;

			HYPERITEM = 1;
			}

		//#### RESET EFFECT ID COUNTERS
		if(ATTRadd >= 1) EFFECTON = 1;
		RANDinc = 0;
		EFFECTID = 0;

		//### - WEAPON SPECIFIC ATTRIBUTES
		if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 0)
			{
			while(ATTRadd >= 1 && !(ATTR00 == 1 && ATTR01 == 1 && ATTR02 == 1 && ATTR03 == 1))
				{
				DECFinger = ((float)rand() / 32767) * 100;

				if(DECFinger >= 0 && DECFinger < 25 && ATTR00 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 1;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_WEPAccuracy = ((RAND * (1500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR00 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 25 && DECFinger < 50 && ATTR01 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 2;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_WEPDrawSPD = ((RAND * (1500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR01 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 50 && DECFinger < 75 && ATTR02 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 3;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_WEPReloadSPD = ((RAND * (1500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR02 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 75 && DECFinger < 100 && ATTR03 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 4;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_WEPRecoilHR = ((RAND * (1500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR03 = 1;
					ATTRadd--;
					}
				}
			}

		//### - ARMOUR ATTRIBUTES
		if(player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 1 || player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 2 || player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Type == 3 || HYPERITEM == 1)
			{
			while(ATTRadd >= 1 && !(ATTR04 == 1 && ATTR05 == 1 && ATTR06 == 1 && ATTR07 == 1 && ATTR08 == 1 && ATTR09 == 1 && ATTR10 == 1 && ATTR11 == 1 && ATTR12 == 1 && ATTR13 == 1 && ATTR14 == 1 && ATTR15 == 1 && ATTR16 == 1 && ATTR17 == 1 && ATTR18 == 1 && ATTR19 == 1 && ATTR20 == 1 && ATTR21 == 1 && ATTR22 == 1 && ATTR23 == 1 && ATTR24 == 1))
				{
				DECFinger = ((float)rand() / 32767) * 21;

				if(DECFinger >= 0 && DECFinger < 1 && ATTR04 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 5;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_EnergyEff = ((RAND * (1500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR04 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 1 && DECFinger < 2 && ATTR05 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 6;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_Height = (((RAND * (75 * QUALFactor)) - (37.5 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR05 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 2 && DECFinger < 3 && ATTR06 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 7;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_Weight = (((RAND * (75 * QUALFactor)) - (37.5 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR06 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 3 && DECFinger < 4 && ATTR07 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 8;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_Strength = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR07 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 4 && DECFinger < 5 && ATTR08 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 9;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_Quickness = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR08 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 5 && DECFinger < 6 && ATTR09 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 10;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_Dexterity = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR09 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 6 && DECFinger < 7 && ATTR10 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 11;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_Constitution = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR10 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 7 && DECFinger < 8 && ATTR11 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 12;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_AggPower = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR11 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 8 && DECFinger < 9 && ATTR12 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 13;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_DefPower = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR12 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 9 && DECFinger < 10 && ATTR13 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 14;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_RArmStr = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR13 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 10 && DECFinger < 11 && ATTR14 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 15;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_LArmStr = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR14 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 11 && DECFinger < 12 && ATTR15 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 16;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_RLegStr = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR15 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 12 && DECFinger < 13 && ATTR16 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 17;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_LLegStr = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR16 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 13 && DECFinger < 14 && ATTR17 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 18;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_RArmSnap = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR17 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 14 && DECFinger < 15 && ATTR18 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 19;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_LArmSnap = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR18 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 15 && DECFinger < 16 && ATTR19 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 20;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_RLegSnap = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR19 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 16 && DECFinger < 17 && ATTR20 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 21;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_LLegSnap = ((RAND * (25 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR20 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 17 && DECFinger < 18 && ATTR21 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 22;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_JINKmovespeed = ((RAND * (10 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR21 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 18 && DECFinger < 19 && ATTR22 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 23;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_JINKpower = ((RAND * (100 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR22 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 19 && DECFinger < 20 && ATTR23 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 24;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_JINK3intensity = ((RAND * (500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR23 = 1;
					ATTRadd--;
					}
				if(DECFinger >= 20 && DECFinger < 21 && ATTR24 == 0)
					{
					RAND = ((float)rand() / 32767);
					if(RAND > RANDinc)
						{
						EFFECTID = 25;
						RANDinc = RAND;
						}
					player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QA_ITEMINC_IntBoost = ((RAND * (1500 * QUALFactor)) * QUALFactor) / ((1.05 - QUALFactor) * 20);
					ATTR24 = 1;
					ATTRadd--;
					}

				}
			
			}

		//### QUANTUM ANGEL EFFECT MATRIX
		if(EFFECTON == 1)
			{
			player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].TYPE = EFFECTID;
			player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].INT = (RANDinc * QUALFactor) / ((1.05 - QUALFactor) * 20);
			player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].ON = 1;
			}
		else
			{
			player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].TYPE = 0;
			player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].INT = 0;
			player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].ON = 0;
			}

		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].Red = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].Green = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].Blue = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[0].Alpha = 255;

		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[1].Red = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[1].Green = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[1].Blue = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[1].Alpha = 255;

		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[2].Red = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[2].Green = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[2].Blue = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[2].Alpha = 255;

		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[3].Red = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[3].Green = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[3].Blue = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[3].Alpha = 255;

		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[4].Red = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[4].Green = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[4].Blue = 255;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].Effect[4].Alpha = 255;

		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].ItemREF = ItemREFERENCE;
		player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS].QualLVL = QUALFactor;

		//#### Increment Number of Items
		player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS++;

		ItemREF.RefNUM = ItemREFERENCE;
		ItemREF.Quality = QUALFactor;

		//##### Unification Console #####//
		char* f_Char = ag_ClearChar(1024);
		sprintf(f_Char, "Avater Item Spawn . type%i . quality%f . ---TYPE0=Weapon TYPE1-3=Armour", player[g_Player]->BFO.CharDATA[CharDataID].ItemDATA[player[g_Player]->BFO.CharDATA[CharDataID].NomITEMS - 1].Type, ItemREF.Quality);
		std::string f_ConsoleString = f_Char;
		delete f_Char;

		g_swapChainPanel_ogl.Dispatcher().RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::High, [f_ConsoleString]()
			{
			std::string f_CurrentConsole = to_string(g_ConsoleTextBox.Text());

			f_CurrentConsole += "\n" + f_ConsoleString;

			g_ConsoleTextBox.Text(StrUsingStr(f_CurrentConsole));
			});

#if 1
		g_unCoutcnt++;
#endif
		//##### Unification Console #####//

		return ItemREF;
		}

	return ItemREF;
}

};