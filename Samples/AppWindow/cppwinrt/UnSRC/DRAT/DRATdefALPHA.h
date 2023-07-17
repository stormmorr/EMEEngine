/*

	DRAT Definition ALPHA - Deep Recursive Attributes
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

/// DRAT TEST BASE

#ifndef __DRATBASE_H__
#define __DRATBASE_H__

#include "DRATdefBETA.h"

#pragma message ("Change Include Order")

namespace DRAT
{

class DratDef : public DratDefREF1
{
public:
	float			NoWEP;
	float			TimeScale;
	float			Gravity;
	float			LifeINC;
	float			EnergyINC;
	float			intBoost;
	float			EnergyEff;
	float			Height;
	float			Weight;
	float			Strength;
	float			Quickness;
	float			Dexterity;
	float			Constitution;
	float			AggPower;
	float			DefPower;
	float			RArmStr;
	float			LArmStr;
	float			RLegStr;
	float			LLegStr;
	float			RArmSnap;
	float			LArmSnap;
	float			RLegSnap;
	float			LLegSnap;
	float			WEPAccuracy;
	float			WEPDrawSPD;
	float			WEPReloadSPD;
	float			WEPRecoilHR;
	float			JINKmovespeed;
	float			JINKpower;
	float			JINK3intensity;
	int				m_Nom;
	bool			SaveIncrement;

	float acServeAttribute(int Address)
		{
		switch(Address)
			{
			case 0:
			return NoWEP;
			case 1:
			return TimeScale;
			case 2:
			return Gravity;
			case 3:
			return LifeINC;
			case 4:
			return EnergyINC;
			case 5:
			return intBoost;
			case 6:
			return EnergyEff;
			case 7:
			return Height;
			case 8:
			return Weight;
			case 9:
			return Strength;
			case 10:
			return Quickness;
			case 11:
			return Dexterity;
			case 12:
			return Constitution;
			case 13:
			return AggPower;
			case 14:
			return DefPower;
			case 15:
			return RArmStr;
			case 16:
			return LArmStr;
			case 17:
			return RLegStr;
			case 18:
			return LLegStr;
			case 19:
			return RArmSnap;
			case 20:
			return LArmSnap;
			case 21:
			return RLegSnap;
			case 22:
			return LLegSnap;
			case 23:
			return WEPAccuracy;
			case 24:
			return WEPDrawSPD;
			case 25:
			return WEPReloadSPD;
			case 26:
			return WEPRecoilHR;
			case 27:
			return JINKmovespeed;
			case 28:
			return JINKpower;
			case 29:
			return JINK3intensity;
			}
		}

	~DratDef() {};
	DratDef()
		{
		NoWEP = 0;
		TimeScale = 0;
		Gravity = 0;
		LifeINC = 0;
		EnergyINC = 0;
		intBoost = 0;
		EnergyEff = 0;
		Height = 0;
		Weight = 0;
		Strength = 0;
		Quickness = 0;
		Dexterity = 0;
		Constitution = 0;
		AggPower = 0;
		DefPower = 0;
		RArmStr = 0;
		LArmStr = 0;
		RLegStr = 0;
		LLegStr = 0;
		RArmSnap = 0;
		LArmSnap = 0;
		RLegSnap = 0;
		LLegSnap = 0;
		WEPAccuracy = 0;
		WEPDrawSPD = 0;
		WEPReloadSPD = 0;
		WEPRecoilHR = 0;
		JINKmovespeed = 0;
		JINKpower = 0;
		JINK3intensity = 0;
		m_Nom = 30;
		SaveIncrement = true;
		};

	//// FIXME DRAT Math
};

};

#endif