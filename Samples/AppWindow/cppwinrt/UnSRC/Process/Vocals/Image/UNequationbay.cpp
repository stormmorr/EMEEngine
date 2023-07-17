/*

    UNconsciousness - Code Generating Conscious State
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "UNequationbay.h"

using namespace UN;

namespace UN
{

UNequationbay::UNequationbay()
{
	FN0_point = 0;
	FN1_point = 0;
	FN2_point = 0;
	FN3_point = 0;
	FN4_point = 0;
	FN0_factor0 = 0.5;
	FN1_factor0 = 0.15;
	FN2_factor0 = 0.75;
	FN3_factor0 = 0.5;
	FN4_factor0 = 0.25;
	FN0_change0 = 3;
	FN1_change0 = 1;
	FN2_change0 = 5;
	FN3_change0 = 2;
	FN4_change0 = 4;

	FRPWQN0_point = 0;
	FRPWQN1_point = 0;
	FRPWQN2_point = 0;
	FRPWQN3_point = 0;
	FRPWQN4_point = 0;
	FRPWQN0_factor0 = 0.5;
	FRPWQN1_factor0 = 0.15;
	FRPWQN2_factor0 = 0.75;
	FRPWQN3_factor0 = 0.500;
	FRPWQN4_factor0 = 0.25;
	FRPWQN0_change0 = 3;
	FRPWQN1_change0 = 1;
	FRPWQN2_change0 = 5;
	FRPWQN3_change0 = 2;
	FRPWQN4_change0 = 4;

	FRN0_point = 0;
	FRN1_point = 0;
	FRN2_point = 0;
	FRN3_point = 0;
	FRN4_point = 0;
	FRN0_factor0 = 1;
	FRN1_factor0 = 0.015;
	FRN2_factor0 = 5;
	FRN3_factor0 = 0.0500;
	FRN4_factor0 = 25;
	FRN0_change0 = 3;
	FRN1_change0 = 1;
	FRN2_change0 = 5;
	FRN3_change0 = 2;
	FRN4_change0 = 4;

	FRPN0_point = 0;
	FRPN1_point = 0;
	FRPN2_point = 0;
	FRPN3_point = 0;
	FRPN4_point = 0;
	FRPN0_factor0 = 0.5;
	FRPN1_factor0 = 0.15;
	FRPN2_factor0 = 0.75;
	FRPN3_factor0 = 0.500;
	FRPN4_factor0 = 0.25;
	FRPN0_change0 = 3;
	FRPN1_change0 = 1;
	FRPN2_change0 = 5;
	FRPN3_change0 = 2;
	FRPN4_change0 = 4;

	FRPWN0_point = 0;
	FRPWN1_point = 0;
	FRPWN2_point = 0;
	FRPWN3_point = 0;
	FRPWN4_point = 0;
	FRPWN0_factor0 = 0.05;
	FRPWN1_factor0 = 50.015;
	FRPWN2_factor0 = 5000;
	FRPWN3_factor0 = 5000;
	FRPWN4_factor0 = 0.025;
	FRPWN0_change0 = 3;
	FRPWN1_change0 = 1;
	FRPWN2_change0 = 5;
	FRPWN3_change0 = 2;
	FRPWN4_change0 = 4;
}

float UNequationbay::acRun(unsigned int i_Select, int in_X, int in_Y, float in_Z)
{
	float x = in_X;
	float y = in_Y / 1000;
	float v;
	float b;
	float i;
	float z = in_Z;

	switch(i_Select)
		{
		case 0:
			v = acRandFN0() + 0.1;
			b = acRandFN4() + 0.1;
			i = acRandFN3() + 0.1;
			z = (z + i )+ i + PI * ((atan2( v,  z * i )+ v )+ PI )+ ((atan2( v,  0 + (z + i )+ x )+ PI )+ ((atan2( v,  z + i )+ i )+ PI )* ((atan2( v,  0 + (z + (atan2( v,  0 + (i ))))))));
			//z = 0;
			//z  = (i )+ b + PI + ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (i ))))))));
			break;
		case 1:
			v = acRandFRN3() + 0.1;
			b = acRandFRN1() + 0.1;
			i = acRandFRN0() + 0.1;
			z = (i) + (int)b * (int)i / (int)PI * (int)(pow(v, 0 + (z + i)+ i)+ PI)+ (abs(0 + (z - i)+ i)+ PI)+ ((atan2(v, 0 - (z + y) - x) + PI) - ((atan2(v, 0 + (i)))));
			//z  = (2 + (z * (log ( z / 2 / (sin ( 3 / z + b )+ x )+ v )+ ((sqrt ( 4 + (z + b )+ i )- v )+ (sin ( z - z + 4 + (v )))))));
			//z  = (v / i / z / x / y / b );
			//z  = i + i + PI + (atan2( v,  0 + (z + x )- v )- ((atan2( v,  0 + (z + x )+ i )+ PI )+ ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (i ))))))));	
			break;
		case 2:
			v = acRandFRPN0() + 0.1;
			b = acRandFRPN4() + 0.1;
			i = acRandFRPN3() + 0.1;
			z = (i )+ i + PI + ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (z + v )+ i )+ PI )+ ((max( v,  y )+ v )+ PI )+ ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((atan2( v,  0 + (x )))))));
			//z = 0;
			//z  = 0 % ((int)i + 1) + i + PI + ((pow( v,  0 - (i ))));
			//z  = i + i + PI + (0 + (z + i )- i )+ PI + ((atan2( v,  0 + (z + i )+ i )+ PI )+ ((int)(atan2( v,  0 + (z + i )+ i )+ PI ) % (int)((abs( 0 + (z + i )+ i )+ PI )+ (0 + i ))));
			break;
		}

	return z;
}

float UNequationbay::acRandom(void)
{
	return (float)rand() / 32767;
}

float UNequationbay::acRandFN0(void)
{
	FN0_min = 0;
	FN0_max = 1000000;

	FN0_point += FN0_change0 * (((float)rand() / 32767) * FN0_factor0);

	if(FN0_point < FN0_min)
		{
		FN0_point = FN0_min;
		FN0_change0 *= -1;
		}
	if(FN0_point > FN0_max)
		{
		FN0_point = FN0_max;
		FN0_change0 *= -1;
		}

	return FN0_point;
}

float UNequationbay::acRandFN1(void)
{
	FN1_min = 50;
	FN1_max = 7500;

	FN1_point += FN1_change0 * (((float)rand() / 32767) * FN1_factor0);

	if(FN1_point < FN1_min)
		{
		FN1_point = FN1_min;
		FN1_change0 *= -1;
		}
	if(FN1_point > FN1_max)
		{
		FN1_point = FN1_max;
		FN1_change0 *= -1;
		}

	return FN1_point;
}

float UNequationbay::acRandFN2(void)
{
	FN2_min = 0;
	FN2_max = 1000000;

	FN2_point += FN2_change0 * (((float)rand() / 32767) * FN2_factor0);

	if(FN2_point < FN2_min)
		{
		FN2_point = FN2_min;
		FN2_change0 *= -1;
		}
	if(FN2_point > FN2_max)
		{
		FN2_point = FN2_max;
		FN2_change0 *= -1;
		}

	return FN2_point;
}

float UNequationbay::acRandFN3(void)
{
	FN3_min = 0;
	FN3_max = 500000;

	FN3_point += FN3_change0 * (((float)rand() / 32767) * FN3_factor0);

	if(FN3_point < FN3_min)
		{
		FN3_point = FN3_min;
		FN3_change0 *= -1;
		}
	if(FN3_point > FN3_max)
		{
		FN3_point = FN3_max;
		FN3_change0 *= -1;
		}

	return FN3_point;
}

float UNequationbay::acRandFN4(void)
{
	FN4_min = 5;
	FN4_max = 75000000;

	FN4_point += FN4_change0 * (((float)rand() / 32767) * FN4_factor0);

	if(FN4_point < FN4_min)
		{
		FN4_point = FN4_min;
		FN4_change0 *= -1;
		}
	if(FN4_point > FN4_max)
		{
		FN4_point = FN4_max;
		FN4_change0 *= -1;
		}

	return FN4_point;
}

float UNequationbay::acRandF0(void)
{
	return FN0_point;
}

float UNequationbay::acRandF1(void)
{
	return FN1_point;
}

float UNequationbay::acRandF2(void)
{
	return FN2_point;
}

float UNequationbay::acRandF3(void)
{
	return FN3_point;
}

float UNequationbay::acRandF4(void)
{
	return FN4_point;
}

float UNequationbay::acRandFRN0(void)
{
	FRN0_min = 0;
	FRN0_max = 1000000;

	FRN0_point += FRN0_change0 * (((float)rand() / 32767) * FRN0_factor0);

	if(FRN0_point < FRN0_min)
		{
		FRN0_point = FRN0_min;
		FRN0_change0 *= -1;
		}
	if(FRN0_point > FRN0_max)
		{
		FRN0_point = FRN0_max;
		FRN0_change0 *= -1;
		}

	return FRN0_point;
}

float UNequationbay::acRandFRN1(void)
{
	FRN1_min = 0;
	FRN1_max = 1000000;

	FRN1_point += FRN1_change0 * (((float)rand() / 32767) * FRN1_factor0);

	if(FRN1_point < FRN1_min)
		{
		FRN1_point = FRN1_min;
		FRN1_change0 *= -1;
		}
	if(FRN1_point > FRN1_max)
		{
		FRN1_point = FRN1_max;
		FRN1_change0 *= -1;
		}

	return FRN1_point;
}

float UNequationbay::acRandFRN2(void)
{
	FRN2_min = 0;
	FRN2_max = 1000000;

	FRN2_point += FRN2_change0 * (((float)rand() / 32767) * FRN2_factor0);

	if(FRN2_point < FRN2_min)
		{
		FRN2_point = FRN2_min;
		FRN2_change0 *= -1;
		}
	if(FRN2_point > FRN2_max)
		{
		FRN2_point = FRN2_max;
		FRN2_change0 *= -1;
		}

	return FRN2_point;
}

float UNequationbay::acRandFRN3(void)
{
	FRN3_min = 0;
	FRN3_max = 1000000;

	FRN3_point += FRN3_change0 * (((float)rand() / 32767) * FRN3_factor0);

	if(FRN3_point < FRN3_min)
		{
		FRN3_point = FRN3_min;
		FRN3_change0 *= -1;
		}
	if(FRN3_point > FRN3_max)
		{
		FRN3_point = FRN3_max;
		FRN3_change0 *= -1;
		}

	return FRN3_point;
}

float UNequationbay::acRandFRN4(void)
{
	FRN4_min = 0;
	FRN4_max = 1000000;

	FRN4_point += FRN4_change0 * (((float)rand() / 32767) * FRN4_factor0);

	if(FRN4_point < FRN4_min)
		{
		FRN4_point = FRN4_min;
		FRN4_change0 *= -1;
		}
	if(FRN4_point > FRN4_max)
		{
		FRN4_point = FRN4_max;
		FRN4_change0 *= -1;
		}

	return FRN4_point;
}

float UNequationbay::acRandFR0(void)
{
	return FRN0_point;
}

float UNequationbay::acRandFR1(void)
{
	return FRN1_point;
}

float UNequationbay::acRandFR2(void)
{
	return FRN2_point;
}

float UNequationbay::acRandFR3(void)
{
	return FRN3_point;
}

float UNequationbay::acRandFR4(void)
{
	return FRN4_point;
}

float UNequationbay::acRandFRPN0(void)
{
	FRPN0_min = 0;
	FRPN0_max = 1000000;

	FRPN0_point += FRPN0_change0 * (((float)rand() / 32767) * FRPN0_factor0);

	if(FRPN0_point < FRPN0_min)
		{
		FRPN0_point = FRPN0_min;
		FRPN0_change0 *= -1;
		}
	if(FRPN0_point > FRPN0_max)
		{
		FRPN0_point = FRPN0_max;
		FRPN0_change0 *= -1;
		}

	return FRPN0_point;
}

float UNequationbay::acRandFRPN1(void)
{
	FRPN1_min = 0;
	FRPN1_max = 1000000;

	FRPN1_point += FRPN1_change0 * (((float)rand() / 32767) * FRPN1_factor0);

	if(FRPN1_point < FRPN1_min)
		{
		FRPN1_point = FRPN1_min;
		FRPN1_change0 *= -1;
		}
	if(FRPN1_point > FRPN1_max)
		{
		FRPN1_point = FRPN1_max;
		FRPN1_change0 *= -1;
		}

	return FRPN1_point;
}

float UNequationbay::acRandFRPN2(void)
{
	FRPN2_min = 0;
	FRPN2_max = 1000000;

	FRPN2_point += FRPN2_change0 * (((float)rand() / 32767) * FRPN2_factor0);

	if(FRPN2_point < FRPN2_min)
		{
		FRPN2_point = FRPN2_min;
		FRPN2_change0 *= -1;
		}
	if(FRPN2_point > FRPN2_max)
		{
		FRPN2_point = FRPN2_max;
		FRPN2_change0 *= -1;
		}

	return FRPN2_point;
}

float UNequationbay::acRandFRPN3(void)
{
	FRPN3_min = 0;
	FRPN3_max = 1000000;

	FRPN3_point += FRPN3_change0 * (((float)rand() / 32767) * FRPN3_factor0);

	if(FRPN3_point < FRPN3_min)
		{
		FRPN3_point = FRPN3_min;
		FRPN3_change0 *= -1;
		}
	if(FRPN3_point > FRPN3_max)
		{
		FRPN3_point = FRPN3_max;
		FRPN3_change0 *= -1;
		}

	return FRPN3_point;
}

float UNequationbay::acRandFRPN4(void)
{
	FRPN4_min = 0;
	FRPN4_max = 1000000;

	FRPN4_point += FRPN4_change0 * (((float)rand() / 32767) * FRPN4_factor0);

	if(FRPN4_point < FRPN4_min)
		{
		FRPN4_point = FRPN4_min;
		FRPN4_change0 *= -1;
		}
	if(FRPN4_point > FRPN4_max)
		{
		FRPN4_point = FRPN4_max;
		FRPN4_change0 *= -1;
		}

	return FRPN4_point;
}

float UNequationbay::acRandFRP0(void)
{
	return FRPN0_point;
}

float UNequationbay::acRandFRP1(void)
{
	return FRPN1_point;
}

float UNequationbay::acRandFRP2(void)
{
	return FRPN2_point;
}

float UNequationbay::acRandFRP3(void)
{
	return FRPN3_point;
}

float UNequationbay::acRandFRP4(void)
{
	return FRPN4_point;
}

float UNequationbay::acRandFRPWN0(void)
{
	FRPWN0_min = 0;
	FRPWN0_max = 1000000;

	FRPWN0_point += FRPWN0_change0 * (((float)rand() / 32767) * FRPWN0_factor0);

	if(FRPWN0_point < FRPWN0_min)
		{
		FRPWN4_point = FRPWN0_min;
		FRPWN4_change0 *= -1;
		}
	if(FRPWN0_point > FRPWN0_max)
		{
		FRPWN0_point = FRPWN0_max;
		FRPWN0_change0 *= -1;
		}

	return FRPWN0_point / FRPWN0_max;
}

float UNequationbay::acRandFRPWN1(void)
{
	FRPWN1_min = 0;
	FRPWN1_max = 1000000;

	FRPWN1_point += FRPWN1_change0 * (((float)rand() / 32767) * FRPWN1_factor0);

	if(FRPWN1_point < FRPWN1_min)
		{
		FRPWN1_point = FRPWN1_min;
		FRPWN1_change0 *= -1;
		}
	if(FRPWN1_point > FRPWN1_max)
		{
		FRPWN1_point = FRPWN1_max;
		FRPWN1_change0 *= -1;
		}

	return FRPWN1_point / FRPWN1_max;
}

float UNequationbay::acRandFRPWN2(void)
{
	FRPWN2_min = 0;
	FRPWN2_max = 1000000;

	FRPWN2_point += FRPWN2_change0 * (((float)rand() / 32767) * FRPWN2_factor0);

	if(FRPWN2_point < FRPWN2_min)
		{
		FRPWN2_point = FRPWN2_min;
		FRPWN2_change0 *= -1;
		}
	if(FRPWN2_point > FRPWN2_max)
		{
		FRPWN2_point = FRPWN2_max;
		FRPWN2_change0 *= -1;
		}

	return FRPWN2_point / FRPWN2_max;
}

float UNequationbay::acRandFRPWN3(void)
{
	FRPWN3_min = 0;
	FRPWN3_max = 1000000;

	FRPWN3_point += FRPWN3_change0 * (((float)rand() / 32767) * FRPWN3_factor0);

	if(FRPWN3_point < FRPWN3_min)
		{
		FRPWN3_point = FRPWN3_min;
		FRPWN3_change0 *= -1;
		}
	if(FRPWN3_point > FRPWN3_max)
		{
		FRPWN3_point = FRPWN3_max;
		FRPWN3_change0 *= -1;
		}

	return FRPWN3_point / FRPWN3_max;
}

float UNequationbay::acRandFRPWN4(void)
{
	FRPWN4_min = 0;
	FRPWN4_max = 1000000;

	FRPWN4_point += FRPWN4_change0 * (((float)rand() / 32767) * FRPWN4_factor0);

	if(FRPWN4_point < FRPWN4_min)
		{
		FRPWN4_point = FRPWN4_min;
		FRPWN4_change0 *= -1;
		}
	if(FRPWN4_point > FRPWN4_max)
		{
		FRPWN4_point = FRPWN4_max;
		FRPWN4_change0 *= -1;
		}

	return FRPWN4_point / FRPWN4_max;
}

float UNequationbay::acRandFRPW0(void)
{
	return FRPWN0_point;
}

float UNequationbay::acRandFRPW1(void)
{
	return FRPWN1_point;
}

float UNequationbay::acRandFRPW2(void)
{
	return FRPWN2_point / FRPWN2_max;
}

float UNequationbay::acRandFRPW3(void)
{
	return FRPWN3_point;
}

float UNequationbay::acRandFRPW4(void)
{
	return FRPWN4_point;
}

float UNequationbay::acRandFRPWQN0(void)
{
	FRPWQN0_min = 0;
	FRPWQN0_max = 1000000;

	FRPWQN0_point += FRPWQN0_change0 * (((float)rand() / 32767) * FRPWQN0_factor0);

	if(FRPWQN0_point < FRPWQN0_min)
		{
		FRPWQN4_point = FRPWQN0_min;
		FRPWQN4_change0 *= -1;
		}
	if(FRPWQN0_point > FRPWQN0_max)
		{
		FRPWQN0_point = FRPWQN0_max;
		FRPWQN0_change0 *= -1;
		}

	return FRPWQN0_point / FRPWQN0_max;
}

float UNequationbay::acRandFRPWQN1(void)
{
	FRPWQN1_min = 0;
	FRPWQN1_max = 1000000;

	FRPWQN1_point += FRPWQN1_change0 * (((float)rand() / 32767) * FRPWQN1_factor0);

	if(FRPWQN1_point < FRPWQN1_min)
		{
		FRPWQN1_point = FRPWQN1_min;
		FRPWQN1_change0 *= -1;
		}
	if(FRPWQN1_point > FRPWQN1_max)
		{
		FRPWQN1_point = FRPWQN1_max;
		FRPWQN1_change0 *= -1;
		}

	return FRPWQN1_point / FRPWQN1_max;
}

float UNequationbay::acRandFRPWQN2(void)
{
	FRPWQN2_min = 0;
	FRPWQN2_max = 1000000;

	FRPWQN2_point += FRPWQN2_change0 * (((float)rand() / 32767) * FRPWQN2_factor0);

	if(FRPWQN2_point < FRPWQN2_min)
		{
		FRPWQN2_point = FRPWQN2_min;
		FRPWQN2_change0 *= -1;
		}
	if(FRPWQN2_point > FRPWQN2_max)
		{
		FRPWQN2_point = FRPWQN2_max;
		FRPWQN2_change0 *= -1;
		}

	return FRPWQN2_point / FRPWQN2_max;
}

float UNequationbay::acRandFRPWQN3(void)
{
	FRPWQN3_min = 0;
	FRPWQN3_max = 1000000;

	FRPWQN3_point += FRPWQN3_change0 * (((float)rand() / 32767) * FRPWQN3_factor0);

	if(FRPWQN3_point < FRPWQN3_min)
		{
		FRPWQN3_point = FRPWQN3_min;
		FRPWQN3_change0 *= -1;
		}
	if(FRPWQN3_point > FRPWQN3_max)
		{
		FRPWQN3_point = FRPWQN3_max;
		FRPWQN3_change0 *= -1;
		}

	return FRPWQN3_point / FRPWQN3_max;
}

float UNequationbay::acRandFRPWQN4(void)
{
	FRPWQN4_min = 0;
	FRPWQN4_max = 1000000;

	FRPWQN4_point += FRPWQN4_change0 * (((float)rand() / 32767) * FRPWQN4_factor0);

	if(FRPWQN4_point < FRPWQN4_min)
		{
		FRPWQN4_point = FRPWQN4_min;
		FRPWQN4_change0 *= -1;
		}
	if(FRPWQN4_point > FRPWQN4_max)
		{
		FRPWQN4_point = FRPWQN4_max;
		FRPWQN4_change0 *= -1;
		}

	return FRPWQN4_point / FRPWQN4_max;
}

float UNequationbay::acRandFRPWQ0(void)
{
	return FRPWQN0_point / FRPWQN0_max;
}

float UNequationbay::acRandFRPWQ1(void)
{
	return FRPWQN1_point / FRPWQN1_max;
}

float UNequationbay::acRandFRPWQ2(void)
{
	return FRPWQN2_point / FRPWQN2_max;
}

float UNequationbay::acRandFRPWQ3(void)
{
	return FRPWQN3_point / FRPWQN3_max;
}

float UNequationbay::acRandFRPWQ4(void)
{
	return FRPWQN4_point / FRPWQN4_max;
}

};