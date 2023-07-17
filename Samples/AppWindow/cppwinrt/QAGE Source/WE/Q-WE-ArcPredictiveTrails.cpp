/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Arc Predictive Trails-

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
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

//#### Effect Progression - Increment Material Counters

void Q_EFFCon::TrailLine_PlayerFrame(int Count)
	{
	if(player[g_Player]->Trail[Count].BitmapPTR == 4)
		{
		player[g_Player]->Trail[Count].MaterialCNT--;
		if(player[g_Player]->Trail[Count].MaterialCNT < 82) player[g_Player]->Trail[Count].MaterialCNT = 96;
		if(player[g_Player]->Trail[Count].MaterialCNT > 96) player[g_Player]->Trail[Count].MaterialCNT = 96;
		}

	if(player[g_Player]->Trail[Count].BitmapPTR == 3)
		{
		player[g_Player]->Trail[Count].MaterialCNT--;
		if(player[g_Player]->Trail[Count].MaterialCNT < 124) player[g_Player]->Trail[Count].MaterialCNT = 136;
		if(player[g_Player]->Trail[Count].MaterialCNT > 136) player[g_Player]->Trail[Count].MaterialCNT = 136;
		}

	aero = 0;
	while(aero < player[g_Player]->Trail[Count].LengNum)
		{
		if(player[g_Player]->Trail[Count].SectionLIVE[aero] == 1)
			{
			if(player[g_Player]->Trail[Count].BitmapPTR != 1 && player[g_Player]->Trail[Count].LINK != 10)
				{
#if 0
				//### Expand Trails
				player[g_Player]->Trail[Count].EXvert.x = player[g_Player]->Trail[Count].Lvert[aero][0].x;
				player[g_Player]->Trail[Count].EXvert.y = player[g_Player]->Trail[Count].Lvert[aero][0].y;
				player[g_Player]->Trail[Count].EXvert.z = player[g_Player]->Trail[Count].Lvert[aero][0].z;
				Qpo->Vec3d_Subtract(&player[g_Player]->Trail[Count].EXvert, &player[g_Player]->Trail[Count].AvatarCENTER, &player[g_Player]->Trail[Count].EXpandVec);
				Qpo->Vec3d_Normalize(&player[g_Player]->Trail[Count].EXpandVec);

				player[g_Player]->Trail[Count].EXvert1.x = player[g_Player]->Trail[Count].Lvert[aero][0].x;
				player[g_Player]->Trail[Count].EXvert1.y = player[g_Player]->Trail[Count].Lvert[aero][0].y;
				player[g_Player]->Trail[Count].EXvert1.z = player[g_Player]->Trail[Count].Lvert[aero][0].z;
				player[g_Player]->Trail[Count].EXvert2.x = player[g_Player]->Trail[Count].Lvert[aero][1].x;
				player[g_Player]->Trail[Count].EXvert2.y = player[g_Player]->Trail[Count].Lvert[aero][1].y;
				player[g_Player]->Trail[Count].EXvert2.z = player[g_Player]->Trail[Count].Lvert[aero][1].z;
				player[g_Player]->Trail[Count].EXvert3.x = player[g_Player]->Trail[Count].Lvert[aero][2].x;
				player[g_Player]->Trail[Count].EXvert3.y = player[g_Player]->Trail[Count].Lvert[aero][2].y;
				player[g_Player]->Trail[Count].EXvert3.z = player[g_Player]->Trail[Count].Lvert[aero][2].z;
				player[g_Player]->Trail[Count].EXvert4.x = player[g_Player]->Trail[Count].Lvert[aero][3].x;
				player[g_Player]->Trail[Count].EXvert4.y = player[g_Player]->Trail[Count].Lvert[aero][3].y;
				player[g_Player]->Trail[Count].EXvert4.z = player[g_Player]->Trail[Count].Lvert[aero][3].z;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert1, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower/35, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert1);
				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert2, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower/35, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert2);
				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert3, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower/35, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert3);
				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert4, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.RELRawPower/35, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert4);

				player[g_Player]->Trail[Count].Lvert[aero][0].x = player[g_Player]->Trail[Count].EXvert1.x;
				player[g_Player]->Trail[Count].Lvert[aero][0].y = player[g_Player]->Trail[Count].EXvert1.y;
				player[g_Player]->Trail[Count].Lvert[aero][0].z = player[g_Player]->Trail[Count].EXvert1.z;
				player[g_Player]->Trail[Count].Lvert[aero][1].x = player[g_Player]->Trail[Count].EXvert2.x;
				player[g_Player]->Trail[Count].Lvert[aero][1].y = player[g_Player]->Trail[Count].EXvert2.y;
				player[g_Player]->Trail[Count].Lvert[aero][1].z = player[g_Player]->Trail[Count].EXvert2.z;
				player[g_Player]->Trail[Count].Lvert[aero][2].x = player[g_Player]->Trail[Count].EXvert3.x;
				player[g_Player]->Trail[Count].Lvert[aero][2].y = player[g_Player]->Trail[Count].EXvert3.y;
				player[g_Player]->Trail[Count].Lvert[aero][2].z = player[g_Player]->Trail[Count].EXvert3.z;
				player[g_Player]->Trail[Count].Lvert[aero][3].x = player[g_Player]->Trail[Count].EXvert4.x;
				player[g_Player]->Trail[Count].Lvert[aero][3].y = player[g_Player]->Trail[Count].EXvert4.y;
				player[g_Player]->Trail[Count].Lvert[aero][3].z = player[g_Player]->Trail[Count].EXvert4.z;
#endif


				/*player[g_Player]->Trail[Count].EXvert.x = player[g_Player]->Trail[Count].Lvert[aero][0].x;
				player[g_Player]->Trail[Count].EXvert.y = player[g_Player]->Trail[Count].Lvert[aero][0].y;
				player[g_Player]->Trail[Count].EXvert.z = player[g_Player]->Trail[Count].Lvert[aero][0].z;

				player[g_Player]->Trail[Count].EXvert1.x = player[g_Player]->Trail[Count].Lvert[aero][4].x;
				player[g_Player]->Trail[Count].EXvert1.y = player[g_Player]->Trail[Count].Lvert[aero][4].y;
				player[g_Player]->Trail[Count].EXvert1.z = player[g_Player]->Trail[Count].Lvert[aero][4].z;

				//### Expand Trails
				Qpo->Vec3d_Subtract(&player[g_Player]->Trail[Count].EXvert1, &player[g_Player]->Trail[Count].EXvert, &player[g_Player]->Trail[Count].EXpandVec);
				Qpo->Vec3d_Normalize(&player[g_Player]->Trail[Count].EXpandVec);

				player[g_Player]->Trail[Count].EXvert1.x = player[g_Player]->Trail[Count].Lvert[aero][0].x;
				player[g_Player]->Trail[Count].EXvert1.y = player[g_Player]->Trail[Count].Lvert[aero][0].y;
				player[g_Player]->Trail[Count].EXvert1.z = player[g_Player]->Trail[Count].Lvert[aero][0].z;
				player[g_Player]->Trail[Count].EXvert2.x = player[g_Player]->Trail[Count].Lvert[aero][1].x;
				player[g_Player]->Trail[Count].EXvert2.y = player[g_Player]->Trail[Count].Lvert[aero][1].y;
				player[g_Player]->Trail[Count].EXvert2.z = player[g_Player]->Trail[Count].Lvert[aero][1].z;
				player[g_Player]->Trail[Count].EXvert3.x = player[g_Player]->Trail[Count].Lvert[aero][2].x;
				player[g_Player]->Trail[Count].EXvert3.y = player[g_Player]->Trail[Count].Lvert[aero][2].y;
				player[g_Player]->Trail[Count].EXvert3.z = player[g_Player]->Trail[Count].Lvert[aero][2].z;
				player[g_Player]->Trail[Count].EXvert4.x = player[g_Player]->Trail[Count].Lvert[aero][3].x;
				player[g_Player]->Trail[Count].EXvert4.y = player[g_Player]->Trail[Count].Lvert[aero][3].y;
				player[g_Player]->Trail[Count].EXvert4.z = player[g_Player]->Trail[Count].Lvert[aero][3].z;

				//Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert1, -1, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert1);
				//Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert2, -1, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert2);
				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert3, 1, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert3);
				Qpo->Vec3d_AddScaled(&player[g_Player]->Trail[Count].EXvert4, 1, &player[g_Player]->Trail[Count].EXpandVec, &player[g_Player]->Trail[Count].EXvert4);

				player[g_Player]->Trail[Count].Lvert[aero][0].x = player[g_Player]->Trail[Count].EXvert1.x;
				player[g_Player]->Trail[Count].Lvert[aero][0].y = player[g_Player]->Trail[Count].EXvert1.y;
				player[g_Player]->Trail[Count].Lvert[aero][0].z = player[g_Player]->Trail[Count].EXvert1.z;
				player[g_Player]->Trail[Count].Lvert[aero][1].x = player[g_Player]->Trail[Count].EXvert2.x;
				player[g_Player]->Trail[Count].Lvert[aero][1].y = player[g_Player]->Trail[Count].EXvert2.y;
				player[g_Player]->Trail[Count].Lvert[aero][1].z = player[g_Player]->Trail[Count].EXvert2.z;
				player[g_Player]->Trail[Count].Lvert[aero][2].x = player[g_Player]->Trail[Count].EXvert3.x;
				player[g_Player]->Trail[Count].Lvert[aero][2].y = player[g_Player]->Trail[Count].EXvert3.y;
				player[g_Player]->Trail[Count].Lvert[aero][2].z = player[g_Player]->Trail[Count].EXvert3.z;
				player[g_Player]->Trail[Count].Lvert[aero][3].x = player[g_Player]->Trail[Count].EXvert4.x;
				player[g_Player]->Trail[Count].Lvert[aero][3].y = player[g_Player]->Trail[Count].EXvert4.y;
				player[g_Player]->Trail[Count].Lvert[aero][3].z = player[g_Player]->Trail[Count].EXvert4.z;*/

				if(player[g_Player]->Trail[Count].LINK == 0)
					{
					if(aero != 0)
						{
						player[g_Player]->Trail[Count].Lvert[aero][0].x = player[g_Player]->Trail[Count].Lvert[aero-1][3].x;
						player[g_Player]->Trail[Count].Lvert[aero][0].y = player[g_Player]->Trail[Count].Lvert[aero-1][3].y;
						player[g_Player]->Trail[Count].Lvert[aero][0].z = player[g_Player]->Trail[Count].Lvert[aero-1][3].z;
						player[g_Player]->Trail[Count].Lvert[aero][1].x = player[g_Player]->Trail[Count].Lvert[aero-1][2].x;
						player[g_Player]->Trail[Count].Lvert[aero][1].y = player[g_Player]->Trail[Count].Lvert[aero-1][2].y;
						player[g_Player]->Trail[Count].Lvert[aero][1].z = player[g_Player]->Trail[Count].Lvert[aero-1][2].z;
						}
					else
						{
						if(Count != 0)
							{
							player[g_Player]->Trail[Count].Lvert[aero][0].x = player[g_Player]->Trail[Count-1].Lvert[9][3].x;
							player[g_Player]->Trail[Count].Lvert[aero][0].y = player[g_Player]->Trail[Count-1].Lvert[9][3].y;
							player[g_Player]->Trail[Count].Lvert[aero][0].z = player[g_Player]->Trail[Count-1].Lvert[9][3].z;
							player[g_Player]->Trail[Count].Lvert[aero][1].x = player[g_Player]->Trail[Count-1].Lvert[9][2].x;
							player[g_Player]->Trail[Count].Lvert[aero][1].y = player[g_Player]->Trail[Count-1].Lvert[9][2].y;
							player[g_Player]->Trail[Count].Lvert[aero][1].z = player[g_Player]->Trail[Count-1].Lvert[9][2].z;
							}
						}
					}

				}

			if(player[g_Player]->Trail[Count].BitmapPTR == 1) Qpo->Poly_AddOnce(&player[g_Player]->Trail[Count].Lvert[aero][0], 4, Medias->trail2, player[g_Player]->Trail[Count].Type, player[g_Player]->Trail[Count].RenderFlags, player[g_Player]->Trail[Count].Scale);

			if(player[g_Player]->Trail[Count].BitmapPTR == 2) Qpo->Poly_AddOnce(&player[g_Player]->Trail[Count].Lvert[aero][0], 4, Medias->trail1, player[g_Player]->Trail[Count].Type, player[g_Player]->Trail[Count].RenderFlags, player[g_Player]->Trail[Count].Scale);

			if(player[g_Player]->Trail[Count].BitmapPTR == 3) Qpo->Poly_AddOnce(&player[g_Player]->Trail[Count].Lvert[aero][0], 4, Medias->Water[player[g_Player]->Trail[Count].MaterialCNT], player[g_Player]->Trail[Count].Type, player[g_Player]->Trail[Count].RenderFlags, player[g_Player]->Trail[Count].Scale);

			if(player[g_Player]->Trail[Count].BitmapPTR == 4) Qpo->Poly_AddOnce(&player[g_Player]->Trail[Count].Lvert[aero][0], 4, Medias->flametrail[player[g_Player]->Trail[Count].MaterialCNT], player[g_Player]->Trail[Count].Type, player[g_Player]->Trail[Count].RenderFlags, player[g_Player]->Trail[Count].Scale);

			//### Reversed NUMERACY Algorithym

			player[g_Player]->Trail[Count].AFADE[aero] = ((1 - ((((float)Count * player[g_Player]->Trail[Count].LengNum) + (float)aero) / ((float)player[g_Player]->NomTrailL * player[g_Player]->Trail[Count].LengNum))) * 30) * _->TimeScale;	//50 = VERY GOOD

			if(player[g_Player]->Trail[Count].Lvert[aero][0].a - player[g_Player]->Trail[Count].AFADE[aero] > 0) player[g_Player]->Trail[Count].Lvert[aero][0].a -= player[g_Player]->Trail[Count].AFADE[aero];
			else player[g_Player]->Trail[Count].SectionLIVE[aero] = 0;

			if(player[g_Player]->Trail[Count].Lvert[aero][1].a - player[g_Player]->Trail[Count].AFADE[aero] > 0) player[g_Player]->Trail[Count].Lvert[aero][1].a -= player[g_Player]->Trail[Count].AFADE[aero];
			else player[g_Player]->Trail[Count].SectionLIVE[aero] = 0;

			if(player[g_Player]->Trail[Count].Lvert[aero][2].a - player[g_Player]->Trail[Count].AFADE[aero] > 0) player[g_Player]->Trail[Count].Lvert[aero][2].a -= player[g_Player]->Trail[Count].AFADE[aero];
			else player[g_Player]->Trail[Count].SectionLIVE[aero] = 0;

			if(player[g_Player]->Trail[Count].Lvert[aero][3].a - player[g_Player]->Trail[Count].AFADE[aero] > 0) player[g_Player]->Trail[Count].Lvert[aero][3].a -= player[g_Player]->Trail[Count].AFADE[aero];
			else player[g_Player]->Trail[Count].SectionLIVE[aero] = 0;
			}
		else
			{
			if(aero == (player[g_Player]->Trail[Count].LengNum - 1))
				{
				player[g_Player]->Trail[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < player[g_Player]->NomTrailL - 1)
					{
					player[g_Player]->Trail[K] = player[g_Player]->Trail[K+1];
					K++;
					}

				player[g_Player]->NomTrailL--;
				Count--;
				}
			}


		/*jet = 0;
		while(jet < player[g_Player]->Trail[Count].LengNum)
			{
			if(player[g_Player]->TrailFadeSpan[jet][0] == Count && player[g_Player]->TrailFadeSpan[jet][1] == aero)
				{
				if(player[g_Player]->TrailsOn == 1) player[g_Player]->Trail[Count].AlpFade = (50 - ((jet*20)*((10-player[g_Player]->Trail[Count].LengNum)+1)));
				if(player[g_Player]->TrailsOn == 0)							//**200**
					{
					player[g_Player]->Trail[Count].AlpFade = (125 - ((jet*20)*((10-player[g_Player]->Trail[Count].LengNum)+1)));
					}

				if(player[g_Player]->Trail[Count].AlpFade < 0) player[g_Player]->Trail[Count].AlpFade = 0;

				if(player[g_Player]->Trail[Count].Lvert[aero][0].a - (player[g_Player]->Trail[Count].AlpFade) >= 0) player[g_Player]->Trail[Count].Lvert[aero][0].a -= player[g_Player]->Trail[Count].AlpFade;
				else player[g_Player]->Trail[Count].ShiftFlag = 1;
				if(player[g_Player]->Trail[Count].Lvert[aero][1].a - (player[g_Player]->Trail[Count].AlpFade) >= 0) player[g_Player]->Trail[Count].Lvert[aero][1].a -= player[g_Player]->Trail[Count].AlpFade;
				else player[g_Player]->Trail[Count].ShiftFlag = 1;
				if(player[g_Player]->Trail[Count].Lvert[aero][2].a - (player[g_Player]->Trail[Count].AlpFade) >= 0) player[g_Player]->Trail[Count].Lvert[aero][2].a -= player[g_Player]->Trail[Count].AlpFade;
				else player[g_Player]->Trail[Count].ShiftFlag = 1;
				if(player[g_Player]->Trail[Count].Lvert[aero][3].a - (player[g_Player]->Trail[Count].AlpFade) >= 0) player[g_Player]->Trail[Count].Lvert[aero][3].a -= player[g_Player]->Trail[Count].AlpFade;
				else player[g_Player]->Trail[Count].ShiftFlag = 1;

				if(player[g_Player]->Trail[Count].ShiftFlag == 1 && jet == 0)
					{
					player[g_Player]->Trail[Count].ShiftFlag = 0;

					player[g_Player]->Trail[Count].Lvert[aero][0].a = 0;
					player[g_Player]->Trail[Count].Lvert[aero][1].a = 0;
					player[g_Player]->Trail[Count].Lvert[aero][2].a = 0;
					player[g_Player]->Trail[Count].Lvert[aero][3].a = 0;

					player[g_Player]->Trail[Count].SectionLIVE[aero] = 0;

					//Shift UP
					warp = 0;
					while(warp < player[g_Player]->Trail[Count].LengNum)
						{
						if(player[g_Player]->TrailFadeSpan[warp][1] + 1 < player[g_Player]->Trail[Count].LengNum) player[g_Player]->TrailFadeSpan[warp][1]++;
						else
							{
							if(player[g_Player]->TrailFadeSpan[warp][0] + 1 < player[g_Player]->NomTrailL) player[g_Player]->TrailFadeSpan[warp][0]++;
							else if(warp == 0)
								{
								trans = 0;
								while(trans < player[g_Player]->NomTrailL)
									{
									player[g_Player]->Trail[trans].Live = 0;
									trans++;
									}

								player[g_Player]->TrailFadeSpan[0][0] = 0;
								player[g_Player]->TrailFadeSpan[1][0] = 0;
								player[g_Player]->TrailFadeSpan[2][0] = 0;
								player[g_Player]->TrailFadeSpan[3][0] = 0;
								player[g_Player]->TrailFadeSpan[4][0] = 0;
								player[g_Player]->TrailFadeSpan[5][0] = 0;
								player[g_Player]->TrailFadeSpan[6][0] = 0;
								player[g_Player]->TrailFadeSpan[7][0] = 0;
								player[g_Player]->TrailFadeSpan[8][0] = 0;
								player[g_Player]->TrailFadeSpan[9][0] = 0;
								player[g_Player]->TrailFadeSpan[0][1] = 0;
								player[g_Player]->TrailFadeSpan[1][1] = 1;
								player[g_Player]->TrailFadeSpan[2][1] = 2;
								player[g_Player]->TrailFadeSpan[3][1] = 3;
								player[g_Player]->TrailFadeSpan[4][1] = 4;
								player[g_Player]->TrailFadeSpan[5][1] = 5;
								player[g_Player]->TrailFadeSpan[6][1] = 6;
								player[g_Player]->TrailFadeSpan[7][1] = 7;
								player[g_Player]->TrailFadeSpan[8][1] = 8;
								player[g_Player]->TrailFadeSpan[9][1] = 9;
								warp = 10;
								jet = 10;
								aero = player[g_Player]->Trail[Count].LengNum;
								Count = player[g_Player]->NomTrailL;
								player[g_Player]->NomTrailL = 0;
								}
							player[g_Player]->TrailFadeSpan[warp][1] = 0;
							}
						warp++;
						}
					}
				}
			jet++;
			}*/
		aero++;
		}
	}


void Q_EFFCon::TrailLine_AvatarFrame(int Avatar, int Count)
	{
	//#### Effect Progression - Increment Material Counters
	if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR == 4)
		{
		Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT--;
		if(Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT < 82) Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT = 96;
		if(Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT > 96) Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT = 96;
		}

	if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR == 3)
		{
		Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT--;
		if(Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT < 124) Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT = 136;
		if(Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT > 136) Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT = 136;
		}

	aero = 0;
	while(aero < Q_Forge->Forge[Avatar].Trail[Count].LengNum)
		{
		if(Q_Forge->Forge[Avatar].Trail[Count].SectionLIVE[aero] == 1)
			{
			if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR != 1 && Q_Forge->Forge[Avatar].Trail[Count].LINK != 10)
				{
#if 0
				//### Expand Trails
				Q_Forge->Forge[Avatar].Trail[Count].EXvert.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z;
				Qpo->Vec3d_Subtract(&Q_Forge->Forge[Avatar].Trail[Count].EXvert, &Q_Forge->Forge[Avatar].Trail[Count].AvatarCENTER, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec);
				Qpo->Vec3d_Normalize(&Q_Forge->Forge[Avatar].Trail[Count].EXpandVec);

				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert2.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert2.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert2.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].z;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert3.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert3.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert3.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].z;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert4.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert4.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert4.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].z;

				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert1, Q_Forge->Forge[Avatar].CharDATA.BodySKILL.RELRawPower/10, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert1);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert2, Q_Forge->Forge[Avatar].CharDATA.BodySKILL.RELRawPower/10, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert2);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert3, Q_Forge->Forge[Avatar].CharDATA.BodySKILL.RELRawPower/10, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert3);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert4, Q_Forge->Forge[Avatar].CharDATA.BodySKILL.RELRawPower/10, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert4);

				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert1.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert1.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert1.z;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert2.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert2.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert2.z;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert3.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert3.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert3.z;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert4.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert4.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert4.z;
#endif

				/*Q_Forge->Forge[Avatar].Trail[Count].EXvert.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z;

				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][4].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][4].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][4].z;

				//### Expand Trails
				geVec3d_Subtract(&Q_Forge->Forge[Avatar].Trail[Count].EXvert1, &Q_Forge->Forge[Avatar].Trail[Count].EXvert, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec);
				geVec3d_Normalize(&Q_Forge->Forge[Avatar].Trail[Count].EXpandVec);

				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert1.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert2.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert2.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert2.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].z;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert3.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert3.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert3.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].z;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert4.x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].x;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert4.y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].y;
				Q_Forge->Forge[Avatar].Trail[Count].EXvert4.z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].z;

				//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert1, -1, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert1);
				//Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert2, -1, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert2);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert3, 1, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert3);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[Avatar].Trail[Count].EXvert4, 1, &Q_Forge->Forge[Avatar].Trail[Count].EXpandVec, &Q_Forge->Forge[Avatar].Trail[Count].EXvert4);

				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert1.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert1.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert1.z;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert2.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert2.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert2.z;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert3.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert3.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert3.z;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].x = Q_Forge->Forge[Avatar].Trail[Count].EXvert4.x;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].y = Q_Forge->Forge[Avatar].Trail[Count].EXvert4.y;
				Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].z = Q_Forge->Forge[Avatar].Trail[Count].EXvert4.z;*/



				if(Q_Forge->Forge[Avatar].Trail[Count].LINK == 0)
					{
					if(aero != 0)
						{
						Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero-1][3].x;
						Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero-1][3].y;
						Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero-1][3].z;
						Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].x = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero-1][2].x;
						Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].y = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero-1][2].y;
						Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].z = Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero-1][2].z;
						}
					else
						{
						if(Count != 0 && Q_Forge->Forge[Avatar].Trail[Count-1].LINK != 1)
							{
							Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].x = Q_Forge->Forge[Avatar].Trail[Count-1].Lvert[9][3].x;
							Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].y = Q_Forge->Forge[Avatar].Trail[Count-1].Lvert[9][3].y;
							Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].z = Q_Forge->Forge[Avatar].Trail[Count-1].Lvert[9][3].z;
							Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].x = Q_Forge->Forge[Avatar].Trail[Count-1].Lvert[9][2].x;
							Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].y = Q_Forge->Forge[Avatar].Trail[Count-1].Lvert[9][2].y;
							Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].z = Q_Forge->Forge[Avatar].Trail[Count-1].Lvert[9][2].z;
							}
						}
					}
				}


			if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR == 1) Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0], 4, Medias->trail2, Q_Forge->Forge[Avatar].Trail[Count].Type, Q_Forge->Forge[Avatar].Trail[Count].RenderFlags, Q_Forge->Forge[Avatar].Trail[Count].Scale);

			if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR == 2) Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0], 4, Medias->trail1, Q_Forge->Forge[Avatar].Trail[Count].Type, Q_Forge->Forge[Avatar].Trail[Count].RenderFlags, Q_Forge->Forge[Avatar].Trail[Count].Scale);

			if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR == 3) Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0], 4, Medias->Water[Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT], Q_Forge->Forge[Avatar].Trail[Count].Type, Q_Forge->Forge[Avatar].Trail[Count].RenderFlags, Q_Forge->Forge[Avatar].Trail[Count].Scale);

			if(Q_Forge->Forge[Avatar].Trail[Count].BitmapPTR == 4) Qpo->Poly_AddOnce(&Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0], 4, Medias->flametrail[Q_Forge->Forge[Avatar].Trail[Count].MaterialCNT], Q_Forge->Forge[Avatar].Trail[Count].Type, Q_Forge->Forge[Avatar].Trail[Count].RenderFlags, Q_Forge->Forge[Avatar].Trail[Count].Scale);

			//### Reversed NUMERACY Algorithym

			Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero] = (1 - (((Count * Q_Forge->Forge[Avatar].Trail[Count].LengNum) + aero) / (Q_Forge->Forge[Avatar].NomTrailL * Q_Forge->Forge[Avatar].Trail[Count].LengNum))) * 30;	//50 = VERY GOOD

			if(Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].a - Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero] > 0) Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][0].a -= Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero];
			else Q_Forge->Forge[Avatar].Trail[Count].SectionLIVE[aero] = 0;

			if(Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].a - Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero] > 0) Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][1].a -= Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero];
			else Q_Forge->Forge[Avatar].Trail[Count].SectionLIVE[aero] = 0;

			if(Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].a - Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero] > 0) Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][2].a -= Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero];
			else Q_Forge->Forge[Avatar].Trail[Count].SectionLIVE[aero] = 0;

			if(Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].a - Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero] > 0) Q_Forge->Forge[Avatar].Trail[Count].Lvert[aero][3].a -= Q_Forge->Forge[Avatar].Trail[Count].AFADE[aero];
			else Q_Forge->Forge[Avatar].Trail[Count].SectionLIVE[aero] = 0;
			}
		else
			{
			if(aero == (Q_Forge->Forge[Avatar].Trail[Count].LengNum - 1))
				{
				Q_Forge->Forge[Avatar].Trail[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < Q_Forge->Forge[Avatar].NomTrailL - 1)
					{
					Q_Forge->Forge[Avatar].Trail[K] = Q_Forge->Forge[Avatar].Trail[K+1];
					K++;
					}

				Q_Forge->Forge[Avatar].NomTrailL--;
				Count--;
				}
			}
		aero++;
		}
	}
};