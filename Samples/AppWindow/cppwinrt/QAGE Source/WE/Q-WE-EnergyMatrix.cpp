/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Energy Matrix-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "math.h"
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
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-EnergyMatrix.h"

using namespace GVARS;

namespace GVARS
{

//============== PLAYER AFFECT MATRIX ===============

void Q_EnergyMatrixCLS::PlayerAffectMatrix(void)
	{
	Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->EnergyArchitect.CurrentPOSMAT);

	//#### DETERMINE POSITION MINS
	player[g_Player]->EnergyArchitect.CurrentPOSX = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.x;
	player[g_Player]->EnergyArchitect.CurrentPOSY = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.y;
	player[g_Player]->EnergyArchitect.CurrentPOSZ = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.z;

	player[g_Player]->EnergyArchitect.CurrentPOSX /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentPOSY /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentPOSZ /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	player[g_Player]->EnergyArchitect.CurrentDTESTX = floor( player[g_Player]->EnergyArchitect.CurrentPOSX );
	player[g_Player]->EnergyArchitect.CurrentDTESTY = floor( player[g_Player]->EnergyArchitect.CurrentPOSY );
	player[g_Player]->EnergyArchitect.CurrentDTESTZ = floor( player[g_Player]->EnergyArchitect.CurrentPOSZ );

	player[g_Player]->EnergyArchitect.CurrentMINS.x = player[g_Player]->EnergyArchitect.CurrentDTESTX;
	player[g_Player]->EnergyArchitect.CurrentMINS.y = player[g_Player]->EnergyArchitect.CurrentDTESTY;
	player[g_Player]->EnergyArchitect.CurrentMINS.z = player[g_Player]->EnergyArchitect.CurrentDTESTZ;

	player[g_Player]->EnergyArchitect.CurrentMINS.x *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentMINS.y *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentMINS.z *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	//#### DETERMINE POSITION MAXS
	player[g_Player]->EnergyArchitect.CurrentPOSX = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.x;
	player[g_Player]->EnergyArchitect.CurrentPOSY = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.y;
	player[g_Player]->EnergyArchitect.CurrentPOSZ = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.z;

	player[g_Player]->EnergyArchitect.CurrentPOSX /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentPOSY /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentPOSZ /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	player[g_Player]->EnergyArchitect.CurrentDTESTX = ceil( player[g_Player]->EnergyArchitect.CurrentPOSX );
	player[g_Player]->EnergyArchitect.CurrentDTESTY = ceil( player[g_Player]->EnergyArchitect.CurrentPOSY );
	player[g_Player]->EnergyArchitect.CurrentDTESTZ = ceil( player[g_Player]->EnergyArchitect.CurrentPOSZ );

	player[g_Player]->EnergyArchitect.CurrentMAXS.x = player[g_Player]->EnergyArchitect.CurrentDTESTX;
	player[g_Player]->EnergyArchitect.CurrentMAXS.y = player[g_Player]->EnergyArchitect.CurrentDTESTY;
	player[g_Player]->EnergyArchitect.CurrentMAXS.z = player[g_Player]->EnergyArchitect.CurrentDTESTZ;

	player[g_Player]->EnergyArchitect.CurrentMAXS.x *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentMAXS.y *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	player[g_Player]->EnergyArchitect.CurrentMAXS.z *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	//#### SEARCH LOOP TO FIND IF CURRENT ZONE IS OWNED
	player[g_Player]->EnergyArchitect.ZoneACTIVE = 0;
	SCRAM=0;
	while(SCRAM < Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks)
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Active == 1)
			{
			if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.x == player[g_Player]->EnergyArchitect.CurrentMINS.x
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.y == player[g_Player]->EnergyArchitect.CurrentMINS.y
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.z == player[g_Player]->EnergyArchitect.CurrentMINS.z
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.x == player[g_Player]->EnergyArchitect.CurrentMAXS.x
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.y == player[g_Player]->EnergyArchitect.CurrentMAXS.y
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.z == player[g_Player]->EnergyArchitect.CurrentMAXS.z)
				{
				player[g_Player]->EnergyArchitect.ZoneACTIVE = 1;
				player[g_Player]->EnergyArchitect.ZoneCHECK = SCRAM;
				}
			}

		SCRAM++;
		}

	//TEST ZONE VALUES

	//==- Check IDs -==
	if(player[g_Player]->EnergyArchitect.ZoneACTIVE == 0)
		{
		//====---- AQUIRE ZONE ----====
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = 250;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = player[g_Player]->EnergyArchitect.CurrentMINS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = player[g_Player]->EnergyArchitect.CurrentMAXS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = player[g_Player]->EnergyArchitect.CurrentMINS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = player[g_Player]->EnergyArchitect.CurrentMAXS;

		//### FIND CORE
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
		Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
		Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

		//### EXPAND OUTWARDS MINS AND MAXS
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
		Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
		Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
		Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
		Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

		//Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = player[g_Player]->EnergyArchitect.ExpandSTRENGTH;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = TestfloatALPHA1;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Smoke;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[0];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[1];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[2];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[3];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[4];

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Fog;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].FogLight;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_TimeScale;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Gravity;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LifeINC;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_EnergyINC;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_IntBoost;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_EnergyEff;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Height;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Weight;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Strength;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Quickness;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Dexterity;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Constitution;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_AggPower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_DefPower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RArmStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LArmStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RLegStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LLegStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RArmSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LArmSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RLegSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LLegSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPAccuracy;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPDrawSPD;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPReloadSPD;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPRecoilHR;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_JINKmovespeed;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_JINKpower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_JINK3intensity;

		qCorner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
		qDX = TempVec1;
		qDX.y = 0;
		qDX.z = 0;
		qDY = TempVec1;
		qDY.x = 0;
		qDY.z = 0;
		qDZ = TempVec1;
		qDZ.y = 0;
		qDZ.x = 0;
		Q.DrawOrientedBoundBox(&qCorner, &qDX, &qDY, &qDZ);

		if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998)
			{
			if(_->NetworkOption == 2)
				{
				Q_EnergyMatrix->EnergyMatrix.NetZONEINC[Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC] = Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks;
				Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC++;
				}

			Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;
			}

		//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		Qpo->Sound_Play(Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation);
		}
	else
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.ZoneCHECK].Active == 0)	//Zone Owned
			{	//Check Ownership
			if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.ZoneCHECK].AVID != 250)	//Player Does Not Own this Zone
				{	//TODO add strength of ownership
				//====---- AQUIRE ZONE ----====
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = 250;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core = player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = player[g_Player]->EnergyArchitect.CurrentMINS;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = player[g_Player]->EnergyArchitect.CurrentMAXS;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = player[g_Player]->EnergyArchitect.CurrentMINS;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = player[g_Player]->EnergyArchitect.CurrentMAXS;

				//### FIND CORE
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
				Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
				Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

				//### EXPAND OUTWARDS MINS AND MAXS
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
				Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
				Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
				Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
				Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

				//Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = player[g_Player]->EnergyArchitect.ExpandSTRENGTH;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = TestfloatALPHA1;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Smoke;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[0];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[1];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[2];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[3];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Effect[4];

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].Fog;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].FogLight;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_TimeScale;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Gravity;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LifeINC;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_EnergyINC;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_IntBoost;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_EnergyEff;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Height;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Weight;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Strength;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Quickness;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Dexterity;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_Constitution;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_AggPower;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_DefPower;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RArmStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LArmStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RLegStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LLegStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RArmSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LArmSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_RLegSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_LLegSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPAccuracy;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPDrawSPD;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPReloadSPD;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_WEPRecoilHR;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_JINKmovespeed;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_JINKpower;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrZCAPTURE].QA_ITEMINC_JINK3intensity;

				qCorner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
				qDX = TempVec1;
				qDX.y = 0;
				qDX.z = 0;
				qDY = TempVec1;
				qDY.x = 0;
				qDY.z = 0;
				qDZ = TempVec1;
				qDZ.y = 0;
				qDZ.x = 0;
				Q.DrawOrientedBoundBox(&qCorner, &qDX, &qDY, &qDZ);

				if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998)
					{
					if(_->NetworkOption == 2)
						{
						Q_EnergyMatrix->EnergyMatrix.NetZONEINC[Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC] = Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks;
						Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC++;
						}
					Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;
					}

				//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation);
				}
			}
		}
	}//END PLAYER AFFECT MATRIX


	//============== AVATAR AFFECT MATRIX ===============

void Q_EnergyMatrixCLS::AvatarAffectMatrix(int AIcounter)
	{
	Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 HEAD", &Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT);

	//#### DETERMINE POSITION MINS
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSX = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.x;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSY = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.y;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSZ = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.z;

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSX /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSY /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSZ /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTX = floor( Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSX );
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTY = floor( Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSY );
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTZ = floor( Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSZ );

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.x = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTX;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.y = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTY;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.z = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTZ;

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.x *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.y *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.z *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	//#### DETERMINE POSITION MAXS
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSX = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.x;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSY = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.y;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSZ = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation.z;

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSX /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSY /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSZ /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTX = ceil( Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSX );
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTY = ceil( Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSY );
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTZ = ceil( Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSZ );

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.x = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTX;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.y = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTY;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.z = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentDTESTZ;

	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.x *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.y *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
	Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.z *= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

	//#### SEARCH LOOP TO FIND IF CURRENT ZONE IS OWNED
	Q_Forge->Forge[AIcounter].EnergyArchitect.ZoneACTIVE = 0;
	SCRAM=0;
	while(SCRAM < Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks)
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Active == 1)
			{
			if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.x == Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.x
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.y == Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.y
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.z == Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS.z
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.x == Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.x
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.y == Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.y
				&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.z == Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS.z)
				{
				Q_Forge->Forge[AIcounter].EnergyArchitect.ZoneACTIVE = 1;
				Q_Forge->Forge[AIcounter].EnergyArchitect.ZoneCHECK = SCRAM;
				}
			}

		SCRAM++;
		}


	//TEST ZONE VALUES

	//==- Check IDs -==
	if(Q_Forge->Forge[AIcounter].EnergyArchitect.ZoneACTIVE == 0)
		{
		//====---- AQUIRE ZONE ----====
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = 250;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS;

		//### FIND CORE
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
		Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
		Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

		//### EXPAND OUTWARDS MINS AND MAXS
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
		Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
		Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
		Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
		Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

		//Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = Q_Forge->Forge[AIcounter].EnergyArchitect.ExpandSTRENGTH;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = TestfloatALPHA1;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Smoke;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[0];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[1];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[2];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[3];
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[4];

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Fog;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].FogLight;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_TimeScale;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Gravity;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LifeINC;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_EnergyINC;

		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_IntBoost;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_EnergyEff;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Height;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Weight;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Strength;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Quickness;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Dexterity;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Constitution;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_AggPower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_DefPower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RArmStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LArmStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RLegStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LLegStr;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RArmSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LArmSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RLegSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LLegSnap;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPAccuracy;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPDrawSPD;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPReloadSPD;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPRecoilHR;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_JINKmovespeed;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_JINKpower;
		Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_JINK3intensity;

		qCorner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
		Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
		qDX = TempVec1;
		qDX.y = 0;
		qDX.z = 0;
		qDY = TempVec1;
		qDY.x = 0;
		qDY.z = 0;
		qDZ = TempVec1;
		qDZ.y = 0;
		qDZ.x = 0;
		Q.DrawOrientedBoundBox(&qCorner, &qDX, &qDY, &qDZ);

		if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998)
			{
			if(_->NetworkOption == 2)
				{
				Q_EnergyMatrix->EnergyMatrix.NetZONEINC[Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC] = Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks;
				Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC++;
				}
			Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;
			}

		//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		Qpo->Sound_Play(Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation);
		}
	else
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.ZoneCHECK].Active == 0)	//Zone Owned
			{	//Check Ownership
			if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.ZoneCHECK].AVID != 250)	//Player Does Not Own this Zone
				{	//TODO add strength of ownership
				//====---- AQUIRE ZONE ----====
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = 250;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMINS;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentMAXS;

				//### FIND CORE
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
				Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
				Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

				//### EXPAND OUTWARDS MINS AND MAXS
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
				Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core);
				Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS);

				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
				Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core);
				Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS, -(Q_EnergyMatrix->EnergyMatrix.GlobalSCALE/4), &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS);

				//Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = Q_Forge->Forge[AIcounter].EnergyArchitect.ExpandSTRENGTH;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = TestfloatALPHA1;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Smoke;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[0];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[1];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[2];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[3];
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Effect[4];

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].Fog;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].FogLight;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_TimeScale;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Gravity;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LifeINC;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_EnergyINC;

				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_IntBoost;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_EnergyEff;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Height;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Weight;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Strength;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Quickness;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Dexterity;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_Constitution;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_AggPower;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_DefPower;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RArmStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LArmStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RLegStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LLegStr;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RArmSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LArmSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_RLegSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_LLegSnap;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPAccuracy;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPDrawSPD;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPReloadSPD;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_WEPRecoilHR;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_JINKmovespeed;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_JINKpower;
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZCAPTURE].QA_ITEMINC_JINK3intensity;

				qCorner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
				qDX = TempVec1;
				qDX.y = 0;
				qDX.z = 0;
				qDY = TempVec1;
				qDY.x = 0;
				qDY.z = 0;
				qDZ = TempVec1;
				qDZ.y = 0;
				qDZ.x = 0;
				Q.DrawOrientedBoundBox(&qCorner, &qDX, &qDY, &qDZ);

				if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998)
					{
					if(_->NetworkOption == 2)
						{
						Q_EnergyMatrix->EnergyMatrix.NetZONEINC[Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC] = Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks;
						Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC++;
						}
					Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;
					}

				//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				Qpo->Sound_Play(Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].EnergyArchitect.CurrentPOSMAT.Translation);
				}
			}
		}
	}//END AVATAR AFFECT MATRIX


	//============== ENERGY MATRIX CONTROL ====== ZONE CONTROL

void Q_EnergyMatrixCLS::ZoneControl(void)
	{
#if 0
	//### RESET PLAYER ZONING
	player[g_Player]->EnergyArchitect.ZONINGSTR = player[g_Player]->EnergyArchitect.ZONING;
	player[g_Player]->EnergyArchitect.ZONING = 0;

	helly = 0;
	while(helly < _->NomAI)
		{
		if(Q_Forge->Forge[helly].LIVE == 1)
			{
			Q_Forge->Forge[helly].EnergyArchitect.ZONINGSTR = Q_Forge->Forge[helly].EnergyArchitect.ZONING;
			Q_Forge->Forge[helly].EnergyArchitect.ZONING = 0;
			}
		helly++;
		}


	SCRAM=0;
	while(SCRAM < Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks)
		{
		if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Active == 1)
			{
			//###### CHECKS TO FIND AVATARS WITHIN BLOCK
			//#### CHECK PLAYER WITHIN
			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->EnergyArchitect.CurrentPOSMAT);

			if((player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.x < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.x
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.x > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.x
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.y < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.y
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.y > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.y
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.z < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.z
			&& player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation.z > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.z) && player[g_Player]->HB_Dead == 0)
				{
				if(player[g_Player]->EnergyArchitect.ZONINGSTR == 0 || player[g_Player]->EnergyArchitect.WithinZONEAVID != Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID)
					{
					//+++ NEW ZONE ENTERED
					Q.DeactivateItems();

					player[g_Player]->EnergyArchitect.ZONING = 1;
					player[g_Player]->EnergyArchitect.WithinZONEAVID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID;
					player[g_Player]->EnergyArchitect.WithinZONE = SCRAM;

					//### RESET FOG
					if(player[g_Player]->EnergyArchitect.FogON == 1)
						{
						player[g_Player]->EnergyArchitect.FogON = 0;
						Qpo->Fog_RemovefromWorld(player[g_Player]->EnergyArchitect.Fogobj);
						}

					if(player[g_Player]->EnergyArchitect.FogLightON == 1)
						{
						player[g_Player]->EnergyArchitect.FogLightON = 0;
						Qpo->Light_Remove(player[g_Player]->EnergyArchitect.FogLightobj);
						}

					//####### REACTIVATE ITEM ATTRIBUTES
					Q.ActivateItems();
					}

				player[g_Player]->EnergyArchitect.ZONING = 1;
				player[g_Player]->EnergyArchitect.WithinZONEAVID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID;
				player[g_Player]->EnergyArchitect.WithinZONE = SCRAM;

				//+++ PLAYER WITHIN ZONE +++

				//+++ FOG CONTROL +++

				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.ON == 1)
					{
					if(player[g_Player]->EnergyArchitect.FogON == 0)
						{
						player[g_Player]->EnergyArchitect.FogON = 1;
						player[g_Player]->EnergyArchitect.Fogobj = Qpo->Fog_AddtoWorld();

						player[g_Player]->EnergyArchitect.FogColour.red = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.Red;
						player[g_Player]->EnergyArchitect.FogColour.green = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.Green;
						player[g_Player]->EnergyArchitect.FogColour.blue = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.Blue;
						player[g_Player]->EnergyArchitect.FogColour.alpha = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.Alpha;
						}

					Qpo->Fog_SetAttr(player[g_Player]->EnergyArchitect.Fogobj, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation, &player[g_Player]->EnergyArchitect.FogColour, 50, Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog.Scale, 20000);
					}


				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight.ON == 1)
					{
					if(player[g_Player]->EnergyArchitect.FogLightON == 0)
						{
						player[g_Player]->EnergyArchitect.FogLightON = 1;
						player[g_Player]->EnergyArchitect.FogLightobj = Qpo->Light_AddtoWorld(_->GenericLightPos);

						player[g_Player]->EnergyArchitect.FogLightColour.red = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight.Red;
						player[g_Player]->EnergyArchitect.FogLightColour.green = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight.Green;
						player[g_Player]->EnergyArchitect.FogLightColour.blue = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight.Blue;
						player[g_Player]->EnergyArchitect.FogLightColour.alpha = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight.Alpha;
						}
					
					Qpo->Light_SetAttr(player[g_Player]->EnergyArchitect.FogLightobj, &player[g_Player]->EnergyArchitect.CurrentPOSMAT.Translation, &player[g_Player]->EnergyArchitect.FogLightColour, Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight.Scale, true);
					}


				//+++ GRAVITY CHANGE +++

				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity != 1 && Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity != 0)
					{
					player[g_Player]->GravityAlter += ((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity - player[g_Player]->GravityAlter) / 5);
					}

				//+++ TIMESCALE ALTERING +++

				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale != 1 && Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale != 0)
					{
					_->TimeScaleALTER += ((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale - _->TimeScaleALTER) / 5);
					}

				//+++ NO WEAPON ZONE +++
				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_NoWEP == 1 && (player[g_Player]->WeaponStatus != 0 && player[g_Player]->WeaponStatus != 7))
					{
					player[g_Player]->attposecnt = 1.0;
					player[g_Player]->WeaponStatus = 7;
					player[g_Player]->blendamount[25] = 0;
					}

				//+++ PLAYER LIFE/ENERGY INCREMENT +++

				player[g_Player]->HB_Energy += Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_EnergyINC;
				if(player[g_Player]->HB_Energy < 0) player[g_Player]->HB_Energy = 0;
				if(player[g_Player]->HB_Energy > player[g_Player]->HB_MaxEnergy) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

				player[g_Player]->HB_Health += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
				if(player[g_Player]->HB_Health < 0) player[g_Player]->HB_Health = 0;
				if(player[g_Player]->HB_Health > player[g_Player]->HB_MaxHealth) player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;

				//### Experience Storage
				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID == 250) player[g_Player]->AvatarDMGSTORE[250] += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);
				else Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[250] += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC) * ((1 - (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Constitution / 400)) + 0.75);

				if(player[g_Player]->HB_Health <= 0)
					{
					player[g_Player]->HB_Health = 0;

					//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm,&player[g_Player]->ViewXForm.Translation,600.0f,2.0f,&Volume,&Pan,&Frequency);

					//'AVATAR DEATH' SOUND
					Qpo->Sound_Play(Medias->S_PlayerKO, _->Volume, _->Pan, _->S_TimeScale, false,&player[g_Player]->ViewXForm.Translation);

					if(_->TimeHole == 0) { _->TimeHole = 4;
					_->TimeRotate = 1; }

					player[g_Player]->HB_Dead = 1;

					//### Add Experience to attacking AVATAR
					if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID == 250)
						{
						if((player[g_Player]->AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
							{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }
						}
					else
						{
						if((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
							{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].CDATID].UnusedXP += Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000); }
						}

					//##### Find KO Owner
					UniversalDMGSTR = 0;

					jet = 0;
					while(jet < _->NomAI)
						{
						if(Q_Forge->Forge[jet].LIVE == 1)
							{
							if(Q_Forge->Forge[jet].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000) > UniversalDMGSTR) DeliverKOID = jet;
							}
						jet++;
						}

					g_Sp = 0;

					//##### Check All Active Avatars for XP and KO's
					AVATARCNT = 0;
					while(AVATARCNT < _->NomAI)
						{
						if(Q_Forge->Forge[AVATARCNT].LIVE == 1)
							{
							if((Q_Forge->Forge[AVATARCNT].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000)) > 0)
								{
								//### Add Experience to attacking AVATAR
								player[g_Player]->BFO.CharDATA[Q_Forge->Forge[AVATARCNT].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[AVATARCNT].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								g_Sp += Q_Forge->Forge[AVATARCNT].AvatarDMGSTORE[250] * (10 * player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level / 1000);

								//### Force Net player to update (Net Play Only)
								if(Q_Forge->Forge[AVATARCNT].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[AVATARCNT].NetPID].UpdateCHAR = 1;
								}

							if(DeliverKOID == AVATARCNT)
								{
								//### Create Item for attacking Avatar
								Q_Forge->Forge[AVATARCNT].DecFinger = ((float)rand() / 32767) * 100;

								if(Q_Forge->Forge[AVATARCNT].DecFinger <= 50)
									{
									//### CREATE NEW ITEM
									if(Q_Forge->Forge[AVATARCNT].NetplayerFLAG == 1 && 0)
										{
										Q_Netplayer->Netplayer[Q_Forge->Forge[AVATARCNT].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[AVATARCNT].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);

										Q_Netplayer->Netplayer[Q_Forge->Forge[AVATARCNT].NetPID].UpdateCHAR = 2;
										}
									else Q.CreateAvatarItem(Q_Forge->Forge[AVATARCNT].CharDATA.CDataID,player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].Level);
									}
								}
							}

						AVATARCNT++;
						}

					//####### DEACTIVATE ITEM ATTRIBUTES
					Q.DeactivateItems();

					ag_ApplyUpdate(g_Sp);

					//### Write out CHARDATA
					//WW2Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

					//####### REACTIVATE ITEM ATTRIBUTES
					Q.ActivateItems();
					}
				}

			helly = 0;
			while(helly < _->NomAI)
				{
				if(Q_Forge->Forge[helly].LIVE == 1)
					{
					//#### CHECK AI WITHIN
					Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[helly].AV, "BIP01 HEAD", &Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT);

					if((Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT.Translation.x > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.x
					&& Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT.Translation.x < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.x
					&& Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT.Translation.y > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.y
					&& Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT.Translation.y < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.y
					&& Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT.Translation.z > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs.z
					&& Q_Forge->Forge[helly].EnergyArchitect.CurrentPOSMAT.Translation.z < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins.z) && Q_Forge->Forge[helly].HB_Dead == 0)
						{
						if(Q_Forge->Forge[helly].EnergyArchitect.ZONINGSTR == 0 || Q_Forge->Forge[helly].EnergyArchitect.WithinZONEAVID != Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID)
							{
							Q.DeactivateItemsAI(helly);

							Q_Forge->Forge[helly].EnergyArchitect.ZONING = 1;
							Q_Forge->Forge[helly].EnergyArchitect.WithinZONEAVID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID;
							Q_Forge->Forge[helly].EnergyArchitect.WithinZONE = SCRAM;

							//####### REACTIVATE ITEM ATTRIBUTES
							Q.ActivateItemsAI(helly);
							}

						Q_Forge->Forge[helly].EnergyArchitect.ZONING = 1;
						Q_Forge->Forge[helly].EnergyArchitect.WithinZONEAVID = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID;
						Q_Forge->Forge[helly].EnergyArchitect.WithinZONE = SCRAM;

						//+++ AVATAR WITHIN ZONE +++

						//+++ GRAVITY CHANGE +++

						if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity != 1 && Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity != 0)
							{
							Q_Forge->Forge[helly].GravityAlter += ((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity - Q_Forge->Forge[helly].GravityAlter) / 5);
							}

						//+++ TIMESCALE ALTERING +++

						if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale != 1 && Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale != 0)
							{
							_->TimeScaleALTER += ((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale - _->TimeScaleALTER) / 5);
							}

						//+++ NO WEAPON ZONE +++
						if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_NoWEP == 1 && (Q_Forge->Forge[helly].WeaponStatus != 0 && Q_Forge->Forge[helly].WeaponStatus != 7))
							{
							Q_Forge->Forge[helly].attposecnt = 1.0;
							Q_Forge->Forge[helly].WeaponStatus = 7;
							Q_Forge->Forge[helly].blendamount[25] = 0;
							}


						//+++ AVATAR LIFE/ENERGY INCREMENT +++

						Q_Forge->Forge[helly].HB_Energy += Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_EnergyINC;
						if(Q_Forge->Forge[helly].HB_Energy < 0) Q_Forge->Forge[helly].HB_Energy = 0;
						if(Q_Forge->Forge[helly].HB_Energy > Q_Forge->Forge[helly].HB_MaxEnergy) Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;

						Q_Forge->Forge[helly].HB_Health += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC) * ((1 - (Q_Forge->Forge[helly].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						if(Q_Forge->Forge[helly].HB_Health < 0) Q_Forge->Forge[helly].HB_Health = 0;
						if(Q_Forge->Forge[helly].HB_Health > Q_Forge->Forge[helly].HB_MaxHealth) Q_Forge->Forge[helly].HB_Health = Q_Forge->Forge[helly].HB_MaxHealth;

						//### Experience Storage
						if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID == 250) player[g_Player]->AvatarDMGSTORE[helly] += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC) * ((1 - (Q_Forge->Forge[helly].CharDATA.BodySKILL.Constitution / 400)) + 0.75);
						else Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[helly] += (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC) * ((1 - (Q_Forge->Forge[helly].CharDATA.BodySKILL.Constitution / 400)) + 0.75);

								//#### Avatar DEATH
						if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID == 250)
							{
							if(Q_Forge->Forge[helly].HB_Health <= 0)
								{
								Q_Forge->Forge[helly].HB_Health = 0;

								//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &player[g_Player]->ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[helly].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[helly].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.PlayerSpawnNNbot(Q_Forge->Forge[helly].AV.Xform.Translation);

									jet++;
									}

								if((player[g_Player]->AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10)) > 0)
									{
									//### Add Experience to attacking AVATAR
									player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].UnusedXP += player[g_Player]->AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10);

									player[g_Player]->MSG_XPON = 1;
									player[g_Player]->MSG_XPInit = 0;
									player[g_Player]->MSG_XPScreenDIST = 0;
									player[g_Player]->MSG_XPScreenDistINC = 50;
									player[g_Player]->MSG_XPScreenDIR = 0;
									player[g_Player]->MSG_XpInc = player[g_Player]->AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10);
									}

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(player[g_Player]->AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if((player[g_Player]->DecFinger <= 50))
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[helly].CharDATA.Level);
										player[g_Player]->MSG_ITEMON = 1;
										player[g_Player]->MSG_ITEMInit = 0;
										player[g_Player]->MSG_ITEMScreenDIST = 800;
										player[g_Player]->MSG_ITEMScreenDistINC = 17;
										player[g_Player]->MSG_ITEMScreenDIR = 0;
										}

									//SET Knockout
									_->KnockOutFLAG = 1;
									_->KnockOutTIMER = 0;
									_->KnockOutCNT = 0;
									_->KnockOutINIT = 0;
									_->KnockOutHEIGHT = 0;
									}

								g_Sp = 0;

								//##### Check All Active Avatars for XP and KO's
								AIcounter = 0;
								while(AIcounter < _->NomAI)
									{
									if(Q_Forge->Forge[AIcounter].LIVE == 1)
										{
										if((Q_Forge->Forge[AIcounter].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[AIcounter].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[AIcounter].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[AIcounter].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[AIcounter].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[AIcounter].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == AIcounter)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[AIcounter].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[AIcounter].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[AIcounter].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[AIcounter].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[AIcounter].CharDATA.CDataID,Q_Forge->Forge[helly].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[AIcounter].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[AIcounter].CharDATA.CDataID,Q_Forge->Forge[helly].CharDATA.Level);
												}
											}
										}

									AIcounter++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

								//####### REACTIVATE ITEM ATTRIBUTES
								Q.ActivateItems();
								}
							}
						else
							{
							if(Q_Forge->Forge[helly].HB_Health <= 0)
								{
								Q_Forge->Forge[helly].HB_Health = 0;

								//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &player[g_Player]->ViewXForm.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);

								//'AVATAR DEATH' SOUND
								Qpo->Sound_Play(Medias->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[helly].RFistPos.Translation);

								if(_->TimeHole == 0)
								{ _->TimeHole = 4;	_->TimeRotate = 1; }

								Q_Forge->Forge[helly].HB_Dead = 1;

								jet = 0;
								while(jet < 5)
									{
									Q.AISpawnNNbot(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID, Q_Forge->Forge[helly].AV.Xform.Translation);

									jet++;
									}

								//### Add XP to avatar
								if((Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10)) > 0)
									{ player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].CDATID].UnusedXP += Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10); }

								//##### Find KO Owner
								UniversalDMGSTR = 0;
								
								if(Q_Forge->Forge[Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].AVID].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = 250;

								jet = 0;
								while(jet < _->NomAI)
									{
									if(Q_Forge->Forge[jet].LIVE == 1)
										{
										if(Q_Forge->Forge[jet].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10) > UniversalDMGSTR) DeliverKOID = jet;
										}
									jet++;
									}

								if(DeliverKOID == 250)
									{
									//### Create Item for attacking Avatar
									player[g_Player]->DecFinger = ((float)rand() / 32767) * 100;

									if(player[g_Player]->DecFinger <= 50)
										{
										player[g_Player]->MSG_ItemREF = Q.CreatePlayerItem(Q_Forge->Forge[helly].CharDATA.Level);
										player[g_Player]->MSG_ITEMON = 1;
										player[g_Player]->MSG_ITEMInit = 0;
										player[g_Player]->MSG_ITEMScreenDIST = 800;
										player[g_Player]->MSG_ITEMScreenDistINC = 17;
										player[g_Player]->MSG_ITEMScreenDIR = 0;
										}

									//SET Knockout
									_->KnockOutFLAG = 1;
									_->KnockOutTIMER = 0;
									_->KnockOutCNT = 0;
									_->KnockOutINIT = 0;
									_->KnockOutHEIGHT = 0;
									}

								g_Sp = 0;

								//##### Check All Active Avatars for XP and KO's
								AIcounter = 0;
								while(AIcounter < _->NomAI)
									{
									if(Q_Forge->Forge[AIcounter].LIVE == 1)
										{
										if((Q_Forge->Forge[AIcounter].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10)) > 0)
											{
											//### Add Experience to attacking AVATAR
											player[g_Player]->BFO.CharDATA[Q_Forge->Forge[AIcounter].CharDATA.CDataID].UnusedXP += Q_Forge->Forge[AIcounter].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10);

											g_Sp += Q_Forge->Forge[AIcounter].AvatarDMGSTORE[helly] * (10 * Q_Forge->Forge[helly].CharDATA.Level / 10);

											//### Force Net player to update (Net Play Only)
											if(Q_Forge->Forge[AIcounter].NetplayerFLAG == 1 && 0) Q_Netplayer->Netplayer[Q_Forge->Forge[AIcounter].NetPID].UpdateCHAR = 1;
											}

										if(DeliverKOID == AIcounter)
											{
											//### Create Item for attacking Avatar
											Q_Forge->Forge[AIcounter].DecFinger = ((float)rand() / 32767) * 100;

											if(Q_Forge->Forge[AIcounter].DecFinger <= 50)
												{
												//### CREATE NEW ITEM
												if(Q_Forge->Forge[AIcounter].NetplayerFLAG == 1 && 0)
													{
													Q_Netplayer->Netplayer[Q_Forge->Forge[AIcounter].NetPID].NewITEMREF = Q.CreateAvatarItem(Q_Forge->Forge[AIcounter].CharDATA.CDataID,Q_Forge->Forge[helly].CharDATA.Level);

													Q_Netplayer->Netplayer[Q_Forge->Forge[AIcounter].NetPID].UpdateCHAR = 2;
													}
												else Q.CreateAvatarItem(Q_Forge->Forge[AIcounter].CharDATA.CDataID,Q_Forge->Forge[helly].CharDATA.Level);
												}
											}
										}

									AIcounter++;
									}

								//####### DEACTIVATE ITEM ATTRIBUTES
								Q.DeactivateItems();

								ag_ApplyUpdate(g_Sp);

								//### Write out CHARDATA
								//Q.WriteNEWCharacterDataV2(&player[g_Player]->BFO);

								//####### REACTIVATE ITEM ATTRIBUTES
								Q.ActivateItems();
								}
							}
						}
					}
				helly++;
				}


			//+++ SMOKE GEN +++
			if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.ON == 1)
				{
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.CNT += (1 * _->TimeScale);

				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.CNT > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.TIMER)
					{
					Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.CNT = 0;

					Tempint1 = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.TYPE;

					switch(Tempint1)
						{
						case 0:	//TYPE ZERO
							{
							aero = 0;
							while(aero < Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.INT)
								{
								Q_Cloud->Cloud[_->NomCloud].CloudType = 12;

								Q_Cloud->Cloud[_->NomCloud].CloudPos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins;
								
								Q_Cloud->Cloud[_->NomCloud].CloudPos.x += ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
								Q_Cloud->Cloud[_->NomCloud].CloudPos.y += ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
								Q_Cloud->Cloud[_->NomCloud].CloudPos.z += ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

								Q_Cloud->Cloud[_->NomCloud].CloudAlpha = (((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.Alpha)+(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.Alpha/2);
								Q_Cloud->Cloud[_->NomCloud].CloudScale = ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.Scale;

								Qpo->Vec3d_New(&Q_Cloud->Cloud[_->NomCloud].CloudTraVec);

								Q_Cloud->Cloud[_->NomCloud].CloudTraVec.x += (((float)rand() / 32767)-0.5)*0.1;
								Q_Cloud->Cloud[_->NomCloud].CloudTraVec.y += ((float)rand() / 32767) * -1;
								Q_Cloud->Cloud[_->NomCloud].CloudTraVec.z += (((float)rand() / 32767)-0.5)*0.1;

								Q_Cloud->Cloud[_->NomCloud].CloudRED = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.Red;
								Q_Cloud->Cloud[_->NomCloud].CloudBLUE = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.Blue;
								Q_Cloud->Cloud[_->NomCloud].CloudGREEN = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke.Green;

								Q_Cloud->Cloud[_->NomCloud].CloudMins = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins;
								Q_Cloud->Cloud[_->NomCloud].CloudMaxs = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs;

								Q_Cloud->Cloud[_->NomCloud].CloudSpeed = ((float)rand() / 32767)*3;

								Q_Cloud->Cloud[_->NomCloud].CloudALPHAINC = (((float)rand() / 32767)*13) + 6;

								Q_Cloud->Cloud[_->NomCloud].CloudSCALEINC = (((float)rand() / 32767)*0.075) + 0.03;

								Q_Cloud->Cloud[_->NomCloud].CloudGRAVITY = (((float)rand() / 32767)*0.5) + 0.1;

								Q_Cloud->Cloud[_->NomCloud].CloudMatCNT = 0;

								Q_Cloud->Cloud[_->NomCloud].CloudLive = 1;

								_->NomCloud++;
								if(_->NomCloud > (Q_Cloud->m_ArrayMx - 1)) _->NomCloud = (Q_Cloud->m_ArrayMx - 1);
								aero++;
								}

							}break;
						}
					}
				}


			//#### ZONE WALL FLICKER
			Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].WallCNT += (((float)rand() / 32767)*10);

			if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].WallCNT > 500)
				{
				Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].WallCNT = 0;

				Corner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins;
				Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins, &TempVec1);
				DX = TempVec1;
				DX.y = 0;
				DX.z = 0;
				DY = TempVec1;
				DY.x = 0;
				DY.z = 0;
				DZ = TempVec1;
				DZ.y = 0;
				DZ.x = 0;
				Q.DrawOrientedBoundBox(&Corner, &DX, &DY, &DZ);
				}


			//+++ EFFECTS GEN +++
			aero = 0;
			while(aero < 5)
				{
				if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].ON == 1)
					{
					Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].CNT += (1 * _->TimeScale);

					if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].CNT > Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].TIMER)
						{
						Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].CNT = 0;

						Tempint1 = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].TYPE;

						switch(Tempint1)
							{
							case 0:	//TYPE ZERO
								{
								jet=0;
								while(jet < (Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].INT*_->TimeScale) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
									{
									Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
									Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
									Q_PntSprite->PntSprite[_->NomPntSprite].Scale = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].Scale;		//0.025f//0.002f
									Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 60;

									Q_PntSprite->PntSprite[_->NomPntSprite].IR = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].Red;
									Q_PntSprite->PntSprite[_->NomPntSprite].IG = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].Green;
									Q_PntSprite->PntSprite[_->NomPntSprite].IB = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[aero].Blue;

									Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
									Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 3;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins;

									//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
									Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5)* 5;
									//Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
									Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += ((float)rand() / 32767)*Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

									Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

									_->NomPntSprite++;
									jet++;
									}

								}break;
							}
						}
					}

				aero++;
				}


			//#### ---==== ENERGY EXPANDING TECH ====--- #######

			//### FIND CORE
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core);
			Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core);
			Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core);

			//### EXPAND OUTWARDS MINS AND MAXS
			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].MINS2Core);
			Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].MINS2Core);
			Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMINS, Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandSTRENGTH, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].MINS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMINS);

			Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMAXS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].MAXS2Core);
			Qpo->Vec3d_Normalize(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].MAXS2Core);
			Qpo->Vec3d_AddScaled(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMAXS, Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandSTRENGTH, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].MAXS2Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMAXS);

			Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandSTRENGTH /= TestfloatALPHA2;

			//#### OBTAIN CORRECT 3D PARENTHESIS

			//#### POSITION MIN-MINS
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSX = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMINS.x;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSY = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMINS.y;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSZ = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMINS.z;

			Q_EnergyMatrix->EnergyMatrix.CurrentPOSX /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSY /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSZ /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

			Q_EnergyMatrix->EnergyMatrix.CurrentDTESTX = floor( Q_EnergyMatrix->EnergyMatrix.CurrentPOSX );
			Q_EnergyMatrix->EnergyMatrix.CurrentDTESTY = floor( Q_EnergyMatrix->EnergyMatrix.CurrentPOSY );
			Q_EnergyMatrix->EnergyMatrix.CurrentDTESTZ = floor( Q_EnergyMatrix->EnergyMatrix.CurrentPOSZ );

			Q_EnergyMatrix->EnergyMatrix.CurrentMINS.x = Q_EnergyMatrix->EnergyMatrix.CurrentDTESTX;
			Q_EnergyMatrix->EnergyMatrix.CurrentMINS.y = Q_EnergyMatrix->EnergyMatrix.CurrentDTESTY;
			Q_EnergyMatrix->EnergyMatrix.CurrentMINS.z = Q_EnergyMatrix->EnergyMatrix.CurrentDTESTZ;

			Q_EnergyMatrix->EnergyMatrix.ActualMINS.x = Q_EnergyMatrix->EnergyMatrix.CurrentMINS.x * Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.ActualMINS.y = Q_EnergyMatrix->EnergyMatrix.CurrentMINS.y * Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.ActualMINS.z = Q_EnergyMatrix->EnergyMatrix.CurrentMINS.z * Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;


			//#### POSITION MAX-MAXS
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSX = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMAXS.x;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSY = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMAXS.y;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSZ = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandMAXS.z;

			Q_EnergyMatrix->EnergyMatrix.CurrentPOSX /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSY /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.CurrentPOSZ /= Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

			Q_EnergyMatrix->EnergyMatrix.CurrentDTESTX = ceil( Q_EnergyMatrix->EnergyMatrix.CurrentPOSX );
			Q_EnergyMatrix->EnergyMatrix.CurrentDTESTY = ceil( Q_EnergyMatrix->EnergyMatrix.CurrentPOSY );
			Q_EnergyMatrix->EnergyMatrix.CurrentDTESTZ = ceil( Q_EnergyMatrix->EnergyMatrix.CurrentPOSZ );

			Q_EnergyMatrix->EnergyMatrix.CurrentMAXS.x = Q_EnergyMatrix->EnergyMatrix.CurrentDTESTX;
			Q_EnergyMatrix->EnergyMatrix.CurrentMAXS.y = Q_EnergyMatrix->EnergyMatrix.CurrentDTESTY;
			Q_EnergyMatrix->EnergyMatrix.CurrentMAXS.z = Q_EnergyMatrix->EnergyMatrix.CurrentDTESTZ;

			Q_EnergyMatrix->EnergyMatrix.ActualMAXS.x = Q_EnergyMatrix->EnergyMatrix.CurrentMAXS.x * Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.ActualMAXS.y = Q_EnergyMatrix->EnergyMatrix.CurrentMAXS.y * Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
			Q_EnergyMatrix->EnergyMatrix.ActualMAXS.z = Q_EnergyMatrix->EnergyMatrix.CurrentMAXS.z * Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

			//#### Shadow Increments
			//Q_EnergyMatrix->EnergyMatrix.ShadINCX = (Q_EnergyMatrix->EnergyMatrix.ActualMAXS.x - Q_EnergyMatrix->EnergyMatrix.ActualMINS.x);
			//Q_EnergyMatrix->EnergyMatrix.ShadINCY = (Q_EnergyMatrix->EnergyMatrix.ActualMAXS.y - Q_EnergyMatrix->EnergyMatrix.ActualMINS.y);
			//Q_EnergyMatrix->EnergyMatrix.ShadINCZ = (Q_EnergyMatrix->EnergyMatrix.ActualMAXS.z - Q_EnergyMatrix->EnergyMatrix.ActualMINS.z);


			//### SHADOW ZONE LOOP ITERATION LEVEL ONE
			SHADOWY = Q_EnergyMatrix->EnergyMatrix.ActualMINS.y;
			while(SHADOWY < Q_EnergyMatrix->EnergyMatrix.ActualMAXS.y)
				{
				//### SHADOW ZONE LOOP ITERATION LEVEL TWO
				SHADOWZ = Q_EnergyMatrix->EnergyMatrix.ActualMINS.z;
				while(SHADOWZ < Q_EnergyMatrix->EnergyMatrix.ActualMAXS.z)
					{
					//### SHADOW ZONE LOOP ITERATION LEVEL THREE
					SHADOWX = Q_EnergyMatrix->EnergyMatrix.ActualMINS.x;
					while(SHADOWX < Q_EnergyMatrix->EnergyMatrix.ActualMAXS.x)
						{
						//##### CONSTRUCT MINS AND MAXS
						Q_EnergyMatrix->EnergyMatrix.ConstructMINS.x = SHADOWX;
						Q_EnergyMatrix->EnergyMatrix.ConstructMINS.y = SHADOWY;
						Q_EnergyMatrix->EnergyMatrix.ConstructMINS.z = SHADOWZ;

						Q_EnergyMatrix->EnergyMatrix.ConstructMAXS.x = SHADOWX + Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
						Q_EnergyMatrix->EnergyMatrix.ConstructMAXS.y = SHADOWY + Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
						Q_EnergyMatrix->EnergyMatrix.ConstructMAXS.z = SHADOWZ + Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;

						//ZONE CHECK ########
						//#### SEARCH LOOP TO FIND IF CURRENT ZONE IS OWNED
						Q_EnergyMatrix->EnergyMatrix.ZoneACTIVE = 0;
						AIcounter=0;
						while(AIcounter < Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks)
							{
							if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Active == 1)
								{
								if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Mins.x == Q_EnergyMatrix->EnergyMatrix.ConstructMINS.x
									&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Mins.y == Q_EnergyMatrix->EnergyMatrix.ConstructMINS.y
									&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Mins.z == Q_EnergyMatrix->EnergyMatrix.ConstructMINS.z
									&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Maxs.x == Q_EnergyMatrix->EnergyMatrix.ConstructMAXS.x
									&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Maxs.y == Q_EnergyMatrix->EnergyMatrix.ConstructMAXS.y
									&& Q_EnergyMatrix->EnergyMatrix.QMATBlock[AIcounter].Maxs.z == Q_EnergyMatrix->EnergyMatrix.ConstructMAXS.z)
									{
									Q_EnergyMatrix->EnergyMatrix.ZoneACTIVE = 1;
									Q_EnergyMatrix->EnergyMatrix.ZoneCHECK = AIcounter;
									}
								}

							AIcounter++;
							}

						//TEST ZONE VALUES

						//==- Check IDs -==
						if(Q_EnergyMatrix->EnergyMatrix.ZoneACTIVE == 0)
							{
							//====---- AQUIRE ZONE ----====
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = 250;

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = Q_EnergyMatrix->EnergyMatrix.ConstructMINS;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = Q_EnergyMatrix->EnergyMatrix.ConstructMAXS;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = Q_EnergyMatrix->EnergyMatrix.ConstructMINS;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = Q_EnergyMatrix->EnergyMatrix.ConstructMAXS;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = 0;//(((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandSTRENGTH - 1) / TestfloatALPHA2) + 1);

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke;

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[0];
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[1];
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[2];
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[3];
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[4];

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog;

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight;

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_EnergyINC;

							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_intBoost;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_EnergyEff;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Height;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Weight;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Strength;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Quickness;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Dexterity;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Constitution;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_AggPower;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_DefPower;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RArmStr;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LArmStr;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RLegStr;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LLegStr;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RArmSnap;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LArmSnap;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RLegSnap;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LLegSnap;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPAccuracy;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPDrawSPD;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPReloadSPD;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPRecoilHR;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_JINKmovespeed;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_JINKpower;
							Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_JINK3intensity;

							Corner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
							Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
							DX = TempVec1;
							DX.y = 0;
							DX.z = 0;
							DY = TempVec1;
							DY.x = 0;
							DY.z = 0;
							DZ = TempVec1;
							DZ.y = 0;
							DZ.x = 0;
							Q.DrawOrientedBoundBox(&Corner, &DX, &DY, &DZ);

							if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998) Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;

							//### FIND CORE
							Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.ConstructMAXS, &Q_EnergyMatrix->EnergyMatrix.ConstructMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
							Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
							Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.ConstructMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

							//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
							Qpo->Sound_Play(Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, false, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
							}
						else
							{
							if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.ZoneCHECK].Active == 0)	//Zone Owned
								{	//Check Ownership
								if(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.ZoneCHECK].AVID != 250)	//Player Does Not Own this Zone
									{	//TODO add strength of ownership
									//====---- AQUIRE ZONE ----====
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Active = 1;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].AVID = 250;

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins = Q_EnergyMatrix->EnergyMatrix.ConstructMINS;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs = Q_EnergyMatrix->EnergyMatrix.ConstructMAXS;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMINS = Q_EnergyMatrix->EnergyMatrix.ConstructMINS;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandMAXS = Q_EnergyMatrix->EnergyMatrix.ConstructMAXS;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ExpandSTRENGTH = 0;//(((Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ExpandSTRENGTH - 1) / TestfloatALPHA2) + 1);

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Smoke = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Smoke;

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[0] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[0];
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[1] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[1];
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[2] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[2];
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[3] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[3];
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Effect[4] = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Effect[4];

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Fog = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].Fog;

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].FogLight = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].FogLight;

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_TimeScale = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_TimeScale;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Gravity = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Gravity;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LifeINC = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LifeINC;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyINC = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_EnergyINC;

									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_intBoost = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_intBoost;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_EnergyEff = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_EnergyEff;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Height = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Height;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Weight = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Weight;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Strength = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Strength;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Quickness = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Quickness;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Dexterity = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Dexterity;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_Constitution = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_Constitution;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_AggPower = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_AggPower;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_DefPower = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_DefPower;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RArmStr;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LArmStr;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RLegStr;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegStr = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LLegStr;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RArmSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RArmSnap;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LArmSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LArmSnap;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_RLegSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_RLegSnap;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_LLegSnap = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_LLegSnap;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPAccuracy = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPAccuracy;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPDrawSPD = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPDrawSPD;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPReloadSPD = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPReloadSPD;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_WEPRecoilHR = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_WEPRecoilHR;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKmovespeed = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_JINKmovespeed;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINKpower = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_JINKpower;
									Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].ZONEINC_JINK3intensity = Q_EnergyMatrix->EnergyMatrix.QMATBlock[SCRAM].ZONEINC_JINK3intensity;

									Corner = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins;
									Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Mins, &TempVec1);
									DX = TempVec1;
									DX.y = 0;
									DX.z = 0;
									DY = TempVec1;
									DY.x = 0;
									DY.z = 0;
									DZ = TempVec1;
									DZ.y = 0;
									DZ.x = 0;
									Q.DrawOrientedBoundBox(&Corner, &DX, &DY, &DZ);

									if(Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks < 9998) Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks++;

									//### FIND CORE
									Qpo->Vec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.ConstructMAXS, &Q_EnergyMatrix->EnergyMatrix.ConstructMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
									Qpo->Vec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
									Qpo->Vec3d_Add(&Q_EnergyMatrix->EnergyMatrix.ConstructMINS, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);

									//QpoSound3D_GetConfig(&player[g_Player]->ViewXForm, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
									Qpo->Sound_Play(Medias->S_ZoneCapture, _->Volume, _->Pan, _->S_TimeScale, false, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NomQMatBlocks].Core);
									}
								}
							}

						SHADOWX += Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
						}
					SHADOWZ += Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
					}
				SHADOWY += Q_EnergyMatrix->EnergyMatrix.GlobalSCALE;
				}

			}
		SCRAM++;
#endif
	}//END ZONE CONTROL


void Q_EnergyMatrixCLS::ZoneExitCheck(void)
	{
	//##### CHECK FOR MOVING OUTSIDE ALL ZONES
	if(player[g_Player]->EnergyArchitect.ZONINGSTR == 1 && player[g_Player]->EnergyArchitect.ZONING == 0)
		{
		player[g_Player]->EnergyArchitect.ZONING = 1;

		Q.DeactivateItems();

		player[g_Player]->EnergyArchitect.ZONING = 0;

		Q.ActivateItems();
		}

	//##### GRAVITY RESETING +++ NON ZONING
	if(player[g_Player]->EnergyArchitect.ZONING == 0 || Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_Gravity == 1)
		{
		player[g_Player]->GravityAlter += ((1 - player[g_Player]->GravityAlter) / 5);
		}

	helly = 0;
	while(helly < _->NomAI)
		{
		if(Q_Forge->Forge[helly].LIVE == 1)
			{
			if(Q_Forge->Forge[helly].EnergyArchitect.ZONINGSTR == 1 && Q_Forge->Forge[helly].EnergyArchitect.ZONING == 0)
				{
				Q_Forge->Forge[helly].EnergyArchitect.ZONING = 1;

				Q.DeactivateItemsAI(helly);

				Q_Forge->Forge[helly].EnergyArchitect.ZONING = 0;

				Q.ActivateItemsAI(helly);
				}

			//##### GRAVITY RESETING +++ NON ZONING

			if(Q_Forge->Forge[helly].EnergyArchitect.ZONING == 0 || Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[helly].EnergyArchitect.WithinZONE].ZONEINC_Gravity == 1)
				{
				Q_Forge->Forge[helly].GravityAlter += ((1 - Q_Forge->Forge[helly].GravityAlter) / 5);
				}
			}
		helly++;
		}
	}//END ZONE EXIT CHECK


void Q_EnergyMatrixCLS::TimeScaleReset(void)
	{
	//##### TIMESCALE RESETING +++ NON ZONING
	if(player[g_Player]->EnergyArchitect.ZONING == 0 || Q_EnergyMatrix->EnergyMatrix.QMATBlock[player[g_Player]->EnergyArchitect.WithinZONE].ZONEINC_TimeScale == 1 && !(player[g_Player]->Scan == 1 && player[g_Player]->ScanUP == 0))
		{
		_->TimeScaleALTER += ((1 - _->TimeScaleALTER) / 5);
		}

	if(player[g_Player]->EnergyArchitect.ZONING == 0)
		{
		if(player[g_Player]->EnergyArchitect.FogON == 1)
			{
			player[g_Player]->EnergyArchitect.FogON = 0;
			Qpo->Fog_RemovefromWorld(player[g_Player]->EnergyArchitect.Fogobj);
			}

		if(player[g_Player]->EnergyArchitect.FogLightON == 1)
			{
			player[g_Player]->EnergyArchitect.FogLightON = 0;
			Qpo->Light_Remove(player[g_Player]->EnergyArchitect.FogLightobj);
			}
		}
	}

};