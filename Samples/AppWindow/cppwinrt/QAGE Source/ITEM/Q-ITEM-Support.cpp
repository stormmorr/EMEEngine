/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Character Item and Attributes-
	*/#include "pch.h"/*- Minor Component -Avatar Spawn Item-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

//##### -+ Avatar Item Spawning +- #####

int Q_COREFunctions::GetItemFACTORY(const char	*ItemREF)
{
	std::string f_Comp = ItemREF;

	if(f_Comp.compare("ak47lowq.cal3d") == 0)
		{
		return MFACT_WEP_AK47LOWQ;
		}

	if(f_Comp.compare("awphighq.cal3d") == 0)
		{
		return MFACT_WEP_AWPHIGHQ;
		}

	if(f_Comp.compare("famassvX.cal3d") == 0)
		{
		return MFACT_WEP_FAMASSVX;
		}

	if(f_Comp.compare("g3lowqua.cal3d") == 0)
		{
		return MFACT_WEP_G3LOWQUA;
		}

	if(f_Comp.compare("IncaMKII.cal3d") == 0)
		{
		return MFACT_WEP_INCAMKII;
		}

	if(f_Comp.compare("l96a1low.cal3d") == 0)
		{
		return MFACT_WEP_L96A1LOW;
		}

	if(f_Comp.compare("M4A1actr.cal3d") == 0)
		{
		return MFACT_WEP_M4A1ACTR;
		}

	if(f_Comp.compare("MiniGUN1.cal3d") == 0)
		{
		return MFACT_WEP_MINIGUN1;
		}

	if(f_Comp.compare("psg1lowq.cal3d") == 0)
		{
		return MFACT_WEP_PSG1LOWQ;
		}

	if(f_Comp.compare("spas12lq.cal3d") == 0)
		{
		return MFACT_WEP_SPAS12LQ;
		}

	if(f_Comp.compare("Swat552X.cal3d") == 0)
		{
		return MFACT_WEP_SWAT552X;
		}

#if 0
	printf("WARNING| Weapon Type Unknown |");
#endif

	return 0;
}

};