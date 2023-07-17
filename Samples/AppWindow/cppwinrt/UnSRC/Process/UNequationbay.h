/*

    UNequationbuilder - Equation Generating Conscious State
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef _UN_EquationBay_
#define _UN_EquationBay_

#include <windows.h>

#include "../Utility/datatypes.h"

#include <vector>
#include <string>

using namespace std;

namespace UN
{

#define PI ((float)3.141592f)
#define PHI ((float)1.618033f)
#define EPS ((float)0.000797f)

typedef float (*LPFNDLLFUNC10)(unsigned int i_Select, int in_X, int in_Y, float in_Z);

class UNequationbay
{
public:
	UNequationbay();
	~UNequationbay() {};

	float acRun(unsigned int i_Select, int in_X, int in_Y, float in_Z);
	float acRunReduced(unsigned int i_Select, int in_X, int in_Y, float in_Z);
	float acRunAlpha(unsigned int i_Select, int in_X, int in_Y, float in_Z);
	float acRunImage(unsigned int i_Select, int in_X, int in_Y, float in_Z);
	float acRunDll(unsigned int i_Select, int in_X, int in_Y, float in_Z);

	int acLoadDll(void);
	int acLoadDll(std::string i_Filename);
	void acFreeDll(void);
	HMODULE m_hDll;
	LPFNDLLFUNC10 m_PATCH;

	///// Sliding Random Structure Functions /////
	float acRandFN0(void);
	float acRandFN1(void);
	float acRandFN2(void);
	float acRandFN3(void);
	float acRandFN4(void);

	float acRandF0(void);
	float acRandF1(void);
	float acRandF2(void);
	float acRandF3(void);
	float acRandF4(void);

	float acRandFRN0(void);
	float acRandFRN1(void);
	float acRandFRN2(void);
	float acRandFRN3(void);
	float acRandFRN4(void);

	float acRandFR0(void);
	float acRandFR1(void);
	float acRandFR2(void);
	float acRandFR3(void);
	float acRandFR4(void);

	float acRandFRPN0(void);
	float acRandFRPN1(void);
	float acRandFRPN2(void);
	float acRandFRPN3(void);
	float acRandFRPN4(void);

	float acRandFRP0(void);
	float acRandFRP1(void);
	float acRandFRP2(void);
	float acRandFRP3(void);
	float acRandFRP4(void);

	float acRandFRPWN0(void);
	float acRandFRPWN1(void);
	float acRandFRPWN2(void);
	float acRandFRPWN3(void);
	float acRandFRPWN4(void);

	float acRandFRPW0(void);
	float acRandFRPW1(void);
	float acRandFRPW2(void);
	float acRandFRPW3(void);
	float acRandFRPW4(void);

	float acRandFRPWQN0(void);
	float acRandFRPWQN1(void);
	float acRandFRPWQN2(void);
	float acRandFRPWQN3(void);
	float acRandFRPWQN4(void);

	float acRandFRPWQ0(void);
	float acRandFRPWQ1(void);
	float acRandFRPWQ2(void);
	float acRandFRPWQ3(void);
	float acRandFRPWQ4(void);

	float FN0_min, FN1_min, FN2_min, FN3_min, FN4_min;
	float FN0_max, FN1_max, FN2_max, FN3_max, FN4_max;

	float FN0_point, FN1_point, FN2_point, FN3_point, FN4_point;
	float FN0_change0, FN1_change0, FN2_change0, FN3_change0, FN4_change0;
	float FN0_factor0, FN1_factor0, FN2_factor0, FN3_factor0, FN4_factor0;

	float FRPWQN0_min, FRPWQN1_min, FRPWQN2_min, FRPWQN3_min, FRPWQN4_min;
	float FRPWQN0_max, FRPWQN1_max, FRPWQN2_max, FRPWQN3_max, FRPWQN4_max;

	float FRPWQN0_point, FRPWQN1_point, FRPWQN2_point, FRPWQN3_point, FRPWQN4_point;
	float FRPWQN0_change0, FRPWQN1_change0, FRPWQN2_change0, FRPWQN3_change0, FRPWQN4_change0;
	float FRPWQN0_factor0, FRPWQN1_factor0, FRPWQN2_factor0, FRPWQN3_factor0, FRPWQN4_factor0;

	float FRN0_min, FRN1_min, FRN2_min, FRN3_min, FRN4_min;
	float FRN0_max, FRN1_max, FRN2_max, FRN3_max, FRN4_max;

	float FRN0_point, FRN1_point, FRN2_point, FRN3_point, FRN4_point;
	float FRN0_change0, FRN1_change0, FRN2_change0, FRN3_change0, FRN4_change0;
	float FRN0_factor0, FRN1_factor0, FRN2_factor0, FRN3_factor0, FRN4_factor0;

	float FRPN0_min, FRPN1_min, FRPN2_min, FRPN3_min, FRPN4_min;
	float FRPN0_max, FRPN1_max, FRPN2_max, FRPN3_max, FRPN4_max;

	float FRPN0_point, FRPN1_point, FRPN2_point, FRPN3_point, FRPN4_point;
	float FRPN0_change0, FRPN1_change0, FRPN2_change0, FRPN3_change0, FRPN4_change0;
	float FRPN0_factor0, FRPN1_factor0, FRPN2_factor0, FRPN3_factor0, FRPN4_factor0;

	float FRPWN0_min, FRPWN1_min, FRPWN2_min, FRPWN3_min, FRPWN4_min;
	float FRPWN0_max, FRPWN1_max, FRPWN2_max, FRPWN3_max, FRPWN4_max;

	float FRPWN0_point, FRPWN1_point, FRPWN2_point, FRPWN3_point, FRPWN4_point;
	float FRPWN0_change0, FRPWN1_change0, FRPWN2_change0, FRPWN3_change0, FRPWN4_change0;
	float FRPWN0_factor0, FRPWN1_factor0, FRPWN2_factor0, FRPWN3_factor0, FRPWN4_factor0;

	//// Helper functions ////
	float acRandom(void);

	FILE* m_ppfileoptions;
	int m_ppfilecount;
};

};

#endif