/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Flame Trails-

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
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

	//##### -+ Flame Trails +- #####

void Q_COREFunctions::FlameTrailCreate(int AvID, int LengNum, QpoVec3d PosStart, QpoVec3d PosEnd, int BitmapPTR, float Red, float Green, float Blue, int Dir)
	{
	if(AvID == 250)
		{
		//INIT
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Pos = playerAV[g_Player]->Xform.Translation;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Pos.y += 60;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].STRPos = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Pos;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale = 30;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Alpha = 255;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].PolyType = QPOLY_TYPE_TRI;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].RenderFlags = QPOLY_REND_DEPTH_SORT;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].ScaleBIT = 1.0f;
		//END INIT

		//Material Counter
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT++;
		if(player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT < 82) player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT = 82;
		if(player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT > 141) player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT = 82;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT2++;
		if(player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT2 < 124) player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT2 = 124;
		if(player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT2 > 174) player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].MaterialCNT2 = 124;


			//## Starting Vertical Line Vector
		Qpo->Vec3d_Subtract(&PosStart, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].LineStartXF.Translation, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecStart);
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecStart;
		Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL);
		Qpo->Vec3d_Inverse(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL);

			//## Ending Vertical Line Vector
		Qpo->Vec3d_Subtract(&PosEnd, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].LineEndXF.Translation, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecEnd);
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInR = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecEnd;
		Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInR);
		Qpo->Vec3d_Inverse(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInR);

			//## Bottom Horizontal Line Vector
		Qpo->Vec3d_Subtract(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].LineEndXF.Translation, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].LineStartXF.Translation, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB);
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB;
		Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB);
		Qpo->Vec3d_Inverse(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB);

			//## Top Horizontal Line Vector
		Qpo->Vec3d_Subtract(&PosEnd, &PosStart, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT);
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT;
		Qpo->Vec3d_Normalize(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT);
		Qpo->Vec3d_Inverse(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT);

			//## Up Vectors
		Qpo->Vec3d_CrossProduct(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpLB);
		Qpo->Vec3d_CrossProduct(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpLT);
		Qpo->Vec3d_CrossProduct(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInR, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpRB);
		Qpo->Vec3d_CrossProduct(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInR, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpRT);


		//### Starting Edge Vertices
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1 = PosStart;
		Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1, player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale/2, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1);

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT2 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].LineStartXF.Translation;
		Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT2, -player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale*2, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT2);

		Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1, player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale/3, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpLB, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT3);

		Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1, -player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale*6, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInL, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT4);
		Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT4, -player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale/3, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpLT, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT4);


		//### Ending Edge Vertices
		if(player[g_Player]->NomTriEffect == 0)
			{
			Qpo->Vec3d_Add(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT1, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftB, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB1);
			Qpo->Vec3d_Add(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertT2, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecLeftT, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB2);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB1, player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale/3, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpRB, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB3);

			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB1, -player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale*6, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecInR, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB4);
			Qpo->Vec3d_AddScaled(&player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB4, -player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Scale/3, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VecUpRT, &player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB4);
			}
		else
			{
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB1 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT1;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB2 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT2;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB3 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT3;
			player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].VertB4 = player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect-1].VertT4;
			}
		

		//###### Initialise one Textured Tri Effect - Flame Energy Trails
		if(player[g_Player]->NomTriEffect == 0)
			{
			TriEffectUt = 1;
			TriEffectUb = 0.9;
			}
		else
			{
			TriEffectUt -= 0.1;
			TriEffectUb -= 0.1;
			if(TriEffectUb < 0)
				{
				TriEffectUt = 0.1;
				TriEffectUb = 0;
				}
			}

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Live = 1;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].EffectType = 2;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].ExpandDist = 1;

		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Ut = TriEffectUt;
		player[g_Player]->Q_TexTriEffect[player[g_Player]->NomTriEffect].Ub = TriEffectUb;

		player[g_Player]->NomTriEffect++;
		if(player[g_Player]->NomTriEffect > 299) player[g_Player]->NomTriEffect = 0;
		}
	}

};