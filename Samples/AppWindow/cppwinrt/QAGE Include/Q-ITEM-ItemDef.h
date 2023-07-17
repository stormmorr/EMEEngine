/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	- Minor Component -Melee Hits System-
		-Header File Classifications-

*/

#ifndef __Q_ITEM_ItemDef__
#define __Q_ITEM_ItemDef__

#include "Q-FUNC-Datatypes.h"

namespace GVARS
{

class Q_ITEMDATA
{
public:
	std::string		Name;
	std::string		ItemActorREF;
	float			ItemScaleFACT;
	QInt			Type;
	QInt			ItemREF;
	float			QualLVL;

	float			Damage;
	float			Power;
	float			Ammo;
	float			RecoilHeight;
	float			RecoilDistance;
	float			FireRate;
	float			Accuracy;
	QInt			BulletCNT;

	QInt			ScopeTYPE;
	QpoVec3d		ScopeLOC;
	QInt			LaserTYPE;
	QpoVec3d		LaserLOC;

	QInt			QAS_Fire;
	QInt			QAS_ReloadBoltOut;
	QInt			QAS_ReloadBoltIn;
	QInt			QAS_ReloadClipOut;
	QInt			QAS_ReloadClipIn;

	float			ArmourFACTOR;
	float			ArmourAMOUNT;
	float			ArmourREGEN;

	Q_EffectObject	Smoke;

	Q_EffectObject	Effect[5];	//EFFECT MATRIX

	Q_EffectObject	Fog;

	Q_EffectObject	FogLight;

	float			ExpandSTRENGTH;

	float			QA_ITEMINC_NoWEP;

	float			QA_ITEMINC_TimeScale;
	float			QA_ITEMINC_Gravity;
	float			QA_ITEMINC_LifeINC;
	float			QA_ITEMINC_EnergyINC;

	float			QA_ITEMINC_IntBoost;
	float			QA_ITEMINC_EnergyEff;
	float			QA_ITEMINC_Height;
	float			QA_ITEMINC_Weight;
	float			QA_ITEMINC_Strength;
	float			QA_ITEMINC_Quickness;
	float			QA_ITEMINC_Dexterity;
	float			QA_ITEMINC_Constitution;
	float			QA_ITEMINC_AggPower;
	float			QA_ITEMINC_DefPower;
	float			QA_ITEMINC_RArmStr;
	float			QA_ITEMINC_LArmStr;
	float			QA_ITEMINC_RLegStr;
	float			QA_ITEMINC_LLegStr;
	float			QA_ITEMINC_RArmSnap;
	float			QA_ITEMINC_LArmSnap;
	float			QA_ITEMINC_RLegSnap;
	float			QA_ITEMINC_LLegSnap;
	float			QA_ITEMINC_WEPAccuracy;
	float			QA_ITEMINC_WEPDrawSPD;
	float			QA_ITEMINC_WEPReloadSPD;
	float			QA_ITEMINC_WEPRecoilHR;
	float			QA_ITEMINC_JINKmovespeed;
	float			QA_ITEMINC_JINKpower;
	float			QA_ITEMINC_JINK3intensity;
};

class Q_ItemRef
{
public:
	Q_ItemRef() { acClear(); };
	~Q_ItemRef() { acClear(); };

	void acClear(void)
		{
		RefNUM = -1;
		Quality = -1.0f;
		}

	QInt	RefNUM;
	float	Quality;
};

};//END namespace GVARS

#endif