/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	- Minor Component -Heart-
			-Header File Classifications-

*/

#ifndef __Q_AI_Heart__
#define __Q_AI_Heart__

namespace GVARS
{

	//*----Class Structures----*

class Q_Chemical		//### Class Structure For Q_Chemical
{
public:
	float		EnergyEff;
	float		Aggression;
	float		Strength;
	float		Focus;

	float		BurnRate;
	int			Potency;
};

class Q_Hearts			//### Class Structure For Q_Heart
{
public:
	float		PulseRate;
	float		Reactions;
	float		Metabolism;
	float		Endurance;
	float		AblDecisive;
	float		AblForgive;
	float		Manic;

	// Position Increments
	float		HeartIncrement;
	float		EnduranceIncrement;

	Q_Chemical	Contamination[15];
};

};//END namespace GVARS

#endif