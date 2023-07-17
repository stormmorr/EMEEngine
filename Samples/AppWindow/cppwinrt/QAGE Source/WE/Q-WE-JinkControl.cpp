/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Player Jink Control-

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
#include "Q-WE-PntSprite.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-WE-BulletSystem.h"

using namespace GVARS;

namespace GVARS
{

//########  - Jinks -  ########//

void Q_COREFunctions::CONTROL_Jinks(void)
	{
	if(player[g_Player]->Q_Jink.Live == 1)
		{
		if(player[g_Player]->Q_Jink.ON > 0)
			{
			if(player[g_Player]->Q_Jink.Init == 0)
				{
				player[g_Player]->Q_Jink.Init = 1;

				//player[g_Player]->Q_Jink.Expandro.StartFade = 255;
				//player[g_Player]->Q_Jink.Expandro.Radius = 0;
				//player[g_Player]->Q_Jink.Expandro.MaterialCNT = 0;

				player[g_Player]->Q_Jink.SpinValue = 0;
				player[g_Player]->Q_Jink.SpinValueINC = -0.001;
				}

			Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), player[g_Player]->Q_Jink.Limb, &player[g_Player]->Q_Jink.RoTMatrix);

			if(player[g_Player]->Q_Jink.FogON == 1)
				{
				if(player[g_Player]->Q_Jink.JFogExist == 0)
					{
					Fogo = Qpo->Fog_AddtoWorld();
					player[g_Player]->Q_Jink.JFogExist = 1;
					player[g_Player]->Q_Jink.Light = Qpo->Light_AddtoWorld(_->GenericLightPos);

					if(player[g_Player]->Q_Jink.ON == 1)
						{
						player[g_Player]->Q_Jink.LightColor.red = 0;
						player[g_Player]->Q_Jink.LightColor.green = 0;
						player[g_Player]->Q_Jink.LightColor.blue = 0;
						player[g_Player]->Q_Jink.LightColor.alpha = 255;
						}
					else
						{
						player[g_Player]->Q_Jink.LightColor.red = -255;
						player[g_Player]->Q_Jink.LightColor.green = -255;
						player[g_Player]->Q_Jink.LightColor.blue = -255;
						player[g_Player]->Q_Jink.LightColor.alpha = 255;
						}
					}

				if(player[g_Player]->Q_Jink.ON == 1)
					{
					if(player[g_Player]->Q_Jink.JFogSize < 200) player[g_Player]->Q_Jink.JFogSize += 10;
					if(player[g_Player]->Q_Jink.JFogLight < 100) player[g_Player]->Q_Jink.JFogLight += 20;
					if(player[g_Player]->Q_Jink.JFogVLight > -2980) player[g_Player]->Q_Jink.JFogVLight -= 200;	//100 - 20
					}
				else
					{
					if(player[g_Player]->Q_Jink.JFogSize < 20000) player[g_Player]->Q_Jink.JFogSize += 50;
					if(player[g_Player]->Q_Jink.JFogLight < 500) player[g_Player]->Q_Jink.JFogLight += 20;
					if(player[g_Player]->Q_Jink.JFogVLight < 2980) player[g_Player]->Q_Jink.JFogVLight += 200;	//100 - 20
					}

				Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->Q_Jink.JFogIn);
				Qpo->Vec3d_Inverse(&player[g_Player]->Q_Jink.JFogIn);
				Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&player[g_Player]->Q_Jink.JFogLeft);

				player[g_Player]->Q_Jink.JFogPos = playerAV[g_Player]->Xform.Translation;
				player[g_Player]->Q_Jink.JFogPos.y += 60;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.JFogPos, 0, &player[g_Player]->Q_Jink.JFogIn, &player[g_Player]->Q_Jink.JFogFront);
				Qpo->Fog_SetAttr(Fogo, &player[g_Player]->Q_Jink.JFogFront, &fontcol, player[g_Player]->Q_Jink.JFogLight, player[g_Player]->Q_Jink.JFogVLight, player[g_Player]->Q_Jink.JFogSize);
				Qpo->Light_SetAttr(player[g_Player]->Q_Jink.Light, &player[g_Player]->Q_Jink.RoTMatrix.Translation, &player[g_Player]->Q_Jink.LightColor, player[g_Player]->Q_Jink.JFogLight*20, true);
				}

			
			if(player[g_Player]->Q_Jink.Expandro.StartFade >= 0)
				{
				helly = 0;
				while(helly < 2)
					{
					//Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->Q_Jink.RoTMatrix);
					//player[g_Player]->Q_Jink.RoTMatrix = playerAV[g_Player]->Xform;
					//player[g_Player]->Q_Jink.RoTMatrix.Translation = Origin;

					Qpo->Transform_New(&player[g_Player]->Q_Jink.RoTMatrix);
					Qpo->Transform_New(&player[g_Player]->Q_Jink.RoTMatrix2);

					//Qpo->Transform_RotateZ(&player[g_Player]->Q_Jink.RoTMatrix, player[g_Player]->Q_Jink.SpinValue);
					//Qpo->Transform_Multiply(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.RoTMatrix2, &player[g_Player]->Q_Jink.RoTMatrix);

					player[g_Player]->Q_Jink.SpinValue -= player[g_Player]->Q_Jink.SpinValueINC;
					player[g_Player]->Q_Jink.SpinValueINC -= 0.0025;

					Qpo->Transform_New_ZRotation(&player[g_Player]->Q_Jink.RoTMatrix2, 0.79);
					Qpo->Transform_Multiply(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.RoTMatrix2, &player[g_Player]->Q_Jink.RoTMatrix);
					Qpo->Transform_RotateY(&player[g_Player]->Q_Jink.RoTMatrix, player[g_Player]->Angles.y + player[g_Player]->Q_Jink.SpinValue);

					//Qpo->Transform_New_ZRotation(&player[g_Player]->Q_Jink.RoTMatrix2, 1.2);
					//Qpo->Transform_Multiply(&player[g_Player]->Q_Jink.RoTMatrix2, &player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.RoTMatrix);
					//Qpo->Transform_RotateY(&player[g_Player]->Q_Jink.RoTMatrix, ((((float)rand() / 32767) * 0.2)-0.1));
					//Qpo->Transform_RotateZ(&player[g_Player]->Q_Jink.RoTMatrix, 1.2);
					Qpo->Transform_GetIn(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.Expandro1.Leftvec);
					//Qpo->Vec3d_Inverse(&player[g_Player]->Q_Jink.Expandro1.Leftvec);
					//Qpo->Transform_GetLeft(&player[g_Player]->Q_Jink.RoTMatrix,&player[g_Player]->Q_Jink.Expandro1.Leftvec);
					Qpo->Transform_GetUp(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.Expandro1.Upvec);

					//player[g_Player]->Q_Jink.RoTMatrix = playerAV[g_Player]->Xform;
					//player[g_Player]->Q_Jink.RoTMatrix.Translation = Origin;

					Qpo->Transform_New(&player[g_Player]->Q_Jink.RoTMatrix);
					Qpo->Transform_New(&player[g_Player]->Q_Jink.RoTMatrix2);

					//Qpo->Transform_RotateZ(&player[g_Player]->Q_Jink.RoTMatrix, player[g_Player]->Q_Jink.SpinValue2);
					//Qpo->Transform_Multiply(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.RoTMatrix2, &player[g_Player]->Q_Jink.RoTMatrix);

					//player[g_Player]->Q_Jink.SpinValue2 += player[g_Player]->Q_Jink.SpinValueINC2;
					//player[g_Player]->Q_Jink.SpinValueINC2 += 0.1;

					Qpo->Transform_New_ZRotation(&player[g_Player]->Q_Jink.RoTMatrix2, -0.79);	//1.2
					Qpo->Transform_Multiply(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.RoTMatrix2, &player[g_Player]->Q_Jink.RoTMatrix);
					Qpo->Transform_RotateY(&player[g_Player]->Q_Jink.RoTMatrix, player[g_Player]->Angles.y - player[g_Player]->Q_Jink.SpinValue);

					//Qpo->Transform_New_ZRotation(&player[g_Player]->Q_Jink.RoTMatrix2, -1.2);
					//Qpo->Transform_Multiply(&player[g_Player]->Q_Jink.RoTMatrix2, &player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.RoTMatrix);
					//Qpo->Transform_RotateY(&player[g_Player]->Q_Jink.RoTMatrix, ((((float)rand() / 32767) * 0.2)-0.1));
					//Qpo->Transform_RotateZ(&player[g_Player]->Q_Jink.RoTMatrix, -1.2);
					Qpo->Transform_GetIn(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.Expandro2.Leftvec);
					//Qpo->Vec3d_Inverse(&player[g_Player]->Q_Jink.Expandro2.Leftvec);
					//Qpo->Transform_GetLeft(&player[g_Player]->Q_Jink.RoTMatrix,&player[g_Player]->Q_Jink.Expandro2.Leftvec);
					Qpo->Transform_GetUp(&player[g_Player]->Q_Jink.RoTMatrix, &player[g_Player]->Q_Jink.Expandro2.Upvec);
				

					//NON PLAYER AVATAR
					//Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[player[g_Player]->Q_Jink.AvID].AV, "BIP01 HEAD", &player[g_Player]->Q_Jink.RoTMatrix);
					//Qpo->Transform_GetUp(&player[g_Player]->Q_Jink.RoTMatrix,&player[g_Player]->Q_Jink.Expandro.Leftvec);
					//Qpo->Transform_GetLeft(&player[g_Player]->Q_Jink.RoTMatrix,&player[g_Player]->Q_Jink.Expandro.Forvec);
					//Qpo->Transform_GetIn(&player[g_Player]->Q_Jink.RoTMatrix,&player[g_Player]->Q_Jink.Expandro.Upvec);


					player[g_Player]->Q_Jink.Expandro.Vert1 = playerAV[g_Player]->Xform.Translation;

					//NON PLAYER AVATAR
					//player[g_Player]->Q_Jink.Expandro.Vert1 = Q_Forge->Forge[player[g_Player]->Q_Jink.AvID].AV.Xform.Translation;

					player[g_Player]->Q_Jink.Expandro.Vert1.y += 60;

					if(helly == 0)
						{
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, player[g_Player]->Q_Jink.Expandro.Radius, &player[g_Player]->Q_Jink.Expandro1.Upvec, &player[g_Player]->Q_Jink.Expandro.Vert1);
												//Distance to the Left of the player
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, player[g_Player]->Q_Jink.Expandro.Radius, &player[g_Player]->Q_Jink.Expandro1.Leftvec, &player[g_Player]->Q_Jink.Expandro.Vert1);

										//Distance to the Right of the player from the left
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, -player[g_Player]->Q_Jink.Expandro.Radius * 2, &player[g_Player]->Q_Jink.Expandro1.Leftvec, &player[g_Player]->Q_Jink.Expandro.Vert2);

										//Distance to the Top of the player
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert2, -player[g_Player]->Q_Jink.Expandro.Radius * 2, &player[g_Player]->Q_Jink.Expandro1.Upvec, &player[g_Player]->Q_Jink.Expandro.Vert3);

										//Distance to the Top of the player
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, -player[g_Player]->Q_Jink.Expandro.Radius * 2, &player[g_Player]->Q_Jink.Expandro1.Upvec, &player[g_Player]->Q_Jink.Expandro.Vert4);
						}
					else
						{
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, player[g_Player]->Q_Jink.Expandro.Radius, &player[g_Player]->Q_Jink.Expandro2.Upvec, &player[g_Player]->Q_Jink.Expandro.Vert1);
												//Distance to the Left of the player
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, player[g_Player]->Q_Jink.Expandro.Radius, &player[g_Player]->Q_Jink.Expandro2.Leftvec, &player[g_Player]->Q_Jink.Expandro.Vert1);

										//Distance to the Right of the player from the left
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, -player[g_Player]->Q_Jink.Expandro.Radius * 2, &player[g_Player]->Q_Jink.Expandro2.Leftvec, &player[g_Player]->Q_Jink.Expandro.Vert2);

										//Distance to the Top of the player
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert2, -player[g_Player]->Q_Jink.Expandro.Radius * 2, &player[g_Player]->Q_Jink.Expandro2.Upvec, &player[g_Player]->Q_Jink.Expandro.Vert3);

										//Distance to the Top of the player
						Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.Expandro.Vert1, -player[g_Player]->Q_Jink.Expandro.Radius * 2, &player[g_Player]->Q_Jink.Expandro2.Upvec, &player[g_Player]->Q_Jink.Expandro.Vert4);
						}

					player[g_Player]->Q_Jink.Expandro.Lvert[0].a = player[g_Player]->Q_Jink.Expandro.StartFade;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].b = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].g = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].r = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].u = 0;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].v = 0;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].x = player[g_Player]->Q_Jink.Expandro.Vert1.x;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].y = player[g_Player]->Q_Jink.Expandro.Vert1.y;
					player[g_Player]->Q_Jink.Expandro.Lvert[0].z = player[g_Player]->Q_Jink.Expandro.Vert1.z;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].a = player[g_Player]->Q_Jink.Expandro.StartFade;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].b = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].g = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].r = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].u = 1;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].v = 0;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].x = player[g_Player]->Q_Jink.Expandro.Vert2.x;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].y = player[g_Player]->Q_Jink.Expandro.Vert2.y;
					player[g_Player]->Q_Jink.Expandro.Lvert[1].z = player[g_Player]->Q_Jink.Expandro.Vert2.z;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].a = player[g_Player]->Q_Jink.Expandro.StartFade;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].b = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].g = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].r = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].u = 1;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].v = 1;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].x = player[g_Player]->Q_Jink.Expandro.Vert3.x;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].y = player[g_Player]->Q_Jink.Expandro.Vert3.y;
					player[g_Player]->Q_Jink.Expandro.Lvert[2].z = player[g_Player]->Q_Jink.Expandro.Vert3.z;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].a = player[g_Player]->Q_Jink.Expandro.StartFade;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].b = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].g = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].r = 255;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].u = 0;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].v = 1;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].x = player[g_Player]->Q_Jink.Expandro.Vert4.x;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].y = player[g_Player]->Q_Jink.Expandro.Vert4.y;
					player[g_Player]->Q_Jink.Expandro.Lvert[3].z = player[g_Player]->Q_Jink.Expandro.Vert4.z;

						
					//if(player[g_Player]->Q_Jink.Expandro.Radius < 80) player[g_Player]->Q_Jink.Expandro.Radius += (80/10) * _->TimeScale;	//15	//30
					//if(player[g_Player]->Q_Jink.Expandro.StartFade > 0) player[g_Player]->Q_Jink.Expandro.StartFade -= 12 * _->TimeScale;	//20
					//else player[g_Player]->Q_Jink.Expandro.StartFade = 0;

					if(player[g_Player]->Q_Jink.Expandro.Radius < 50) player[g_Player]->Q_Jink.Expandro.Radius += (50/10) * _->TimeScale;	//15	//30
					if(player[g_Player]->Q_Jink.Expandro.StartFade > 0) player[g_Player]->Q_Jink.Expandro.StartFade -= 12 * _->TimeScale;	//20
					else player[g_Player]->Q_Jink.Expandro.StartFade = 0;
					
					player[g_Player]->Q_Jink.Expandro.MaterialCNT = ((1 - ( player[g_Player]->Q_Jink.Expandro.Radius / 50 )) * 15 );
					if(player[g_Player]->Q_Jink.Expandro.MaterialCNT > 15) player[g_Player]->Q_Jink.Expandro.MaterialCNT = 15;
					if(player[g_Player]->Q_Jink.Expandro.MaterialCNT < 0) player[g_Player]->Q_Jink.Expandro.MaterialCNT = 0;

					//FROZEN
					if(player[g_Player]->Q_Jink.Expandro.StartFade > 0) Qpo->Poly_AddOnce(&player[g_Player]->Q_Jink.Expandro.Lvert[0], 4, Medias->JEnergy[player[g_Player]->Q_Jink.Expandro.MaterialCNT], QPOLY_TYPE_TRI, QPOLY_REND_NO_OCCLUDE, 1.0f);//player[g_Player]->Q_Jink.Expandro.Radius/170);
					//player[g_Player]->Q_Jink.Expandro.Lvert[0].a /= 3;
					//Qpo->Poly_AddOnce(&player[g_Player]->Q_Jink.Expandro.Lvert[0], 1, Medias->JEnergy[player[g_Player]->Q_Jink.Expandro.MaterialCNT], QPOLY_TYPE_PNT, QPOLY_REND_OCCLUDE_ON, player[g_Player]->Q_Jink.Expandro.Radius/150);

					helly++;
					}
				}
			}
		else
			{
			player[g_Player]->Q_Jink.Init = 0;

			if(player[g_Player]->Q_Jink.JFogVLight < 0)
				{
				if(player[g_Player]->Q_Jink.JFogSize > 0) player[g_Player]->Q_Jink.JFogSize -= 10;

				if(player[g_Player]->Q_Jink.JFogLight > 0) player[g_Player]->Q_Jink.JFogLight -= 20;

				if(player[g_Player]->Q_Jink.JFogVLight < 0) player[g_Player]->Q_Jink.JFogVLight += 300;	//3000


				Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/&player[g_Player]->Q_Jink.JFogIn);

				Qpo->Vec3d_Inverse(&player[g_Player]->Q_Jink.JFogIn);

				Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/&player[g_Player]->Q_Jink.JFogLeft);

				player[g_Player]->Q_Jink.JFogPos = playerAV[g_Player]->Xform.Translation;
				player[g_Player]->Q_Jink.JFogPos.y += 60;

				Qpo->Vec3d_AddScaled(&player[g_Player]->Q_Jink.JFogPos, 0, &player[g_Player]->Q_Jink.JFogIn, &player[g_Player]->Q_Jink.JFogFront);

				Qpo->Fog_SetAttr(Fogo, &player[g_Player]->Q_Jink.JFogFront, &fontcol, player[g_Player]->Q_Jink.JFogLight, player[g_Player]->Q_Jink.JFogVLight, player[g_Player]->Q_Jink.JFogSize);
				
				//player[g_Player]->Q_Jink.Expandro.StartFade = 255;
				//player[g_Player]->Q_Jink.Expandro.Radius = 0;
				}
			else
				{
				player[g_Player]->Q_Jink.JFogSize = 0;
				player[g_Player]->Q_Jink.JFogLight = 0;
				player[g_Player]->Q_Jink.JFogVLight = 0;

				if(player[g_Player]->Q_Jink.JFogExist == 1)
					{
					Qpo->Fog_RemovefromWorld(Fogo);
					Qpo->Light_Remove(player[g_Player]->Q_Jink.Light);
					player[g_Player]->Q_Jink.JFogExist = 0;
					player[g_Player]->Q_Jink.Live = 0;
					}
				}
			}
		}
	}

};