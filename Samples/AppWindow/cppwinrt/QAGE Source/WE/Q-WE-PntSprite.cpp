/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Point Sprites-

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

using namespace GVARS;

namespace GVARS
{

//######===-- POINT SPRITE CONTROL FRAME --===######

void Q_EFFCon::PntSprite_ControlFrame(int Count)
	{
#if 0
	printf("Trace Count %i PartType %i\n", Count, Q_PntSprite->PntSprite[Count].PartType);
#endif

	float f_TimescaleMeM = _->TimeScale;
	_->TimeScale /= 40;

	switch(Q_PntSprite->PntSprite[Count].PartType)
		{
		case 0:
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (40*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (40*_->TimeScale);	//25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			//if(Q_PntSprite->PntSprite[Count].Speed - 0.5 > 0) Q_PntSprite->PntSprite[Count].Speed -= 0.5;
			//else Q_PntSprite->PntSprite[Count].Speed = 0;

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5 > 0) Q_PntSprite->PntSprite[Count].Speed += 0.5;
			else Q_PntSprite->PntSprite[Count].Speed = 0;


			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 1

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 2

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 3

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 4

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			} break;

		case 1:
			{
			//### Progress Speed
			if(Q_PntSprite->PntSprite[Count].Direction < 3)
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (12.5*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Speed -= (12.5*_->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Direction++;
					Q_PntSprite->PntSprite[Count].Speed = 0;
					}
				}
			else
				{
				Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE2", &BoneMat);

				if(Q_PntSprite->PntSprite[Count].Speed - (20*_->TimeScale) > -65) Q_PntSprite->PntSprite[Count].Speed -= (20*_->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = -65;

				Qpo->Vec3d_Subtract(&Q_PntSprite->PntSprite[Count].Pos, &BoneMat.Translation, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

				if(Q_PntSprite->PntSprite[Count].Pos.x > BoneMat.Translation.x - 30 && Q_PntSprite->PntSprite[Count].Pos.x < BoneMat.Translation.x + 30
					&& Q_PntSprite->PntSprite[Count].Pos.y > BoneMat.Translation.y - 30 && Q_PntSprite->PntSprite[Count].Pos.y < BoneMat.Translation.y + 30
					&& Q_PntSprite->PntSprite[Count].Pos.z > BoneMat.Translation.z - 30 && Q_PntSprite->PntSprite[Count].Pos.z < BoneMat.Translation.z + 30)
					{
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}


			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			//##### Sprite Trail 1

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -(Q_PntSprite->PntSprite[Count].Speed/5), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 2

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -(Q_PntSprite->PntSprite[Count].Speed/5), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 3

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -(Q_PntSprite->PntSprite[Count].Speed/5), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 4

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -(Q_PntSprite->PntSprite[Count].Speed/5), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			} break;

		case 2:
			{
			//### Progress Speed
			/*if(Q_PntSprite->PntSprite[Count].Direction < 16)
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (10*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Speed -= (10*_->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Direction++;
					Q_PntSprite->PntSprite[Count].Speed = 0;
					}
				}
			else
				{
				Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE2", &BoneMat);

				if(Q_PntSprite->PntSprite[Count].Speed - (15*_->TimeScale) > -65) Q_PntSprite->PntSprite[Count].Speed -= (15*_->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = -65;

				Qpo->Vec3d_Subtract(&Q_PntSprite->PntSprite[Count].Pos, &BoneMat.Translation, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);


				if(Q_PntSprite->PntSprite[Count].Pos.x > BoneMat.Translation.x - 30 && Q_PntSprite->PntSprite[Count].Pos.x < BoneMat.Translation.x + 30
					&& Q_PntSprite->PntSprite[Count].Pos.y > BoneMat.Translation.y - 30 && Q_PntSprite->PntSprite[Count].Pos.y < BoneMat.Translation.y + 30
					&& Q_PntSprite->PntSprite[Count].Pos.z > BoneMat.Translation.z - 30 && Q_PntSprite->PntSprite[Count].Pos.z < BoneMat.Translation.z + 30) Q_PntSprite->PntSprite[Count].Live = 0;
				}*/


			if(Q_PntSprite->PntSprite[Count].Direction < 16)
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Speed -= (2*_->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Direction++;
					Q_PntSprite->PntSprite[Count].Speed = 0;
					}
				}
			else
				{
				//### Progress Alpha
				if(Q_PntSprite->PntSprite[Count].Alpha - (40*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (40*_->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}


			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 1

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 2

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 3

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 4

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			} break;

		case 3:		//Trail Sprites
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (35*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 20;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed/7)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.09;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 4:		//KO Sprites
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (10*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (10*_->TimeScale);	//25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.45*_->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 0.45*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 0;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= Q_PntSprite->PntSprite[Count].Speed*_->TimeScale;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 5:		//Trail Sprites II
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (35*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (35*_->TimeScale);	//25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 1*_->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 1*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 0;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed/3)*_->TimeScale;

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 6:		//Trail Sprites III
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (20*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (20*_->TimeScale);	//25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 3.5 * _->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 3.5 * _->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 0;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].TraVec.x += (((float)rand() / 32767)-0.5)/4;
			Q_PntSprite->PntSprite[Count].TraVec.y += (((float)rand() / 32767)-0.5)/4;
			Q_PntSprite->PntSprite[Count].TraVec.z += (((float)rand() / 32767)-0.5)/4;

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 7:
			{
			//### Progress Speed
			if(Q_PntSprite->PntSprite[Count].Direction < 3)
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (12.5*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Speed -= (12.5*_->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Direction++;
					Q_PntSprite->PntSprite[Count].Speed = 0;
					}
				}
			else
				{
				Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE2", &BoneMat);

				if(Q_PntSprite->PntSprite[Count].Speed - (20*_->TimeScale) > -65) Q_PntSprite->PntSprite[Count].Speed -= (20*_->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = -65;

				Qpo->Vec3d_Subtract(&Q_PntSprite->PntSprite[Count].Pos, &BoneMat.Translation, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);


				if(Q_PntSprite->PntSprite[Count].Pos.x > BoneMat.Translation.x - 30 && Q_PntSprite->PntSprite[Count].Pos.x < BoneMat.Translation.x + 30
					&& Q_PntSprite->PntSprite[Count].Pos.y > BoneMat.Translation.y - 30 && Q_PntSprite->PntSprite[Count].Pos.y < BoneMat.Translation.y + 30
					&& Q_PntSprite->PntSprite[Count].Pos.z > BoneMat.Translation.z - 30 && Q_PntSprite->PntSprite[Count].Pos.z < BoneMat.Translation.z + 30)
					{
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}


			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 1

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 2

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 3

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 4

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->greenyN2, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			} break;

		case 8:		//QA EFFECT 01
			{

			//Particle ejjector LVL02
			Q_PntSprite->PntSprite[Count].CNTR += 1 *_->TimeScale;

			jet=0;
			while((jet < 5 * _->TimeScale) && (Q_PntSprite->PntSprite[Count].CNTR > 3) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.06f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 10;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Q_PntSprite->PntSprite[Count].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_PntSprite->PntSprite[_->NomPntSprite].IR > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IG > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IB > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = Q_PntSprite->PntSprite[Count].Alpha;
				//if(Q_PntSprite->PntSprite[_->NomPntSprite].Alpha > 255) Q_PntSprite->PntSprite[Count].Alpha = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;
				//Q_PntSprite->PntSprite[Count].ATTLightON = 0;
				//Qpo->Light_Remove(Q_PntSprite->PntSprite[Count].ATTLight);

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.05 *_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.05 * _->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;	//0.2


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed/6)*_->TimeScale;

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02/player[g_Player]->TestVALUE09;

			//geWorld_SetLightAttributes(World, Q_PntSprite->PntSprite[Count].ATTLight, &Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].ATTLightColor, 200, GE_true);
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 9:	//Mind Flakes
			{
			player[g_Player]->CNTR1 += 1 *_->TimeScale;

			jet=0;
			while((jet < 2 * _->TimeScale) && (player[g_Player]->CNTR1 > 3) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				player[g_Player]->CNTR1 = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.045f * player[g_Player]->TestVALUE03;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 10;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.5;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*7;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*7;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*7;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			//Particle ejector LVL02

			//geWorld_SetLightAttributes(World, Q_PntSprite->PntSprite[Count].ATTLight, &Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].ATTLightColor, 250, GE_true);


			//### Progress Speed
			Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 HEAD", &BoneMat);

			if(Q_PntSprite->PntSprite[Count].Speed + (0.1*_->TimeScale) > 10) Q_PntSprite->PntSprite[Count].Speed += (0.1*_->TimeScale);
			else Q_PntSprite->PntSprite[Count].Speed = 3;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Qpo->Vec3d_Subtract(&Q_PntSprite->PntSprite[Count].Pos, &BoneMat.Translation, &Q_PntSprite->PntSprite[Count].TempVec1);

			Q_PntSprite->PntSprite[Count].TempDist = Qpo->Vec3d_Length(&Q_PntSprite->PntSprite[Count].TempVec1);

			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TempVec1);

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, 30 - Q_PntSprite->PntSprite[Count].TempDist, &Q_PntSprite->PntSprite[Count].TempVec1, &Q_PntSprite->PntSprite[Count].Pos);


			Q_PntSprite->PntSprite[Count].TraVec.x += (((float)rand() / 32767)-0.5) * 0.15;
			Q_PntSprite->PntSprite[Count].TraVec.y += (((float)rand() / 32767)-0.5) * 0.15;
			Q_PntSprite->PntSprite[Count].TraVec.z += (((float)rand() / 32767)-0.5) * 0.15;


			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (30*_->TimeScale) <= 200) Q_PntSprite->PntSprite[Count].Alpha += (30*_->TimeScale);	//3  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 200;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (5*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5*_->TimeScale);	//3  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					Q_PntSprite->PntSprite[Count].AlphaCNT++;

					if(Q_PntSprite->PntSprite[Count].AlphaCNT > 2)
						{
						Q_PntSprite->PntSprite[Count].Live = 0;
						Q_PntSprite->PntSprite[Count].ATTLightON = 0;
						Qpo->Light_Remove(Q_PntSprite->PntSprite[Count].ATTLight);

						//### Array Reorder
						int K = Count;
						while(K < _->NomPntSprite - 1)
							{
							Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
							K++;
							}

						_->NomPntSprite--;
						}
					}
				}


			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;

			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 1

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 2

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 3

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			//##### Sprite Trail 4

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 50 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 50;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->attsprite, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);


			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			} break;


		case 10:		//QA EFFECT 03
			{

			//Particle ejjector LVL02
			/*jet=0;
			while((jet < 1) && (_->NomPntSprite < 24999))
				{
				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.015f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 10;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*7;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*7;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*7;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}*/

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (4*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (4*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 11:		//QA EFFECT 03
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.2*_->TimeScale < 6) Q_PntSprite->PntSprite[Count].Speed += 0.2*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 18;

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.03;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			
			if(Qpo->Collision_RayTest(//World,
				 NULL,
				 NULL,
				 &Q_PntSprite->PntSprite[Count].OldPos,
				 &Q_PntSprite->PntSprite[Count].Pos,
				 ////GE_CONTENTS_CANNOT_OCCUPY,
				 ////GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
				 0xffffffff, NULL, NULL,
				 &Q_PntSprite->PntSprite[Count].Collision))
				{
				Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].OldPos;

				/*if(Q_BSparks->BSparks[Count].Bounce < 2)	//2
					{*/
					Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);

					//BETTER
					//Q_PntSprite->PntSprite[Count].Gravity = Q_PntSprite->PntSprite[Count].Gravity * 2;
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].Speed / 1.5;
				/*	Q_PntSprite->PntSprite[Count].Bounce++;
					}
				else
					{
					Q_BSparks->BSparks[Count].Live = 0;
					Q_BSparks->BSparks[Count].Pos.y = -255;

					//### Array Reorder
					int K = Count;
					while(K < _->NomSparks - 1)
						{
						Q_BSparks->BSparks[K] = Q_BSparks->BSparks[K+1];
						K++;
						}

					_->NomSparks--;
					}*/
				}

	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 12:		//QA EFFECT 01
			{
			//Particle ejjector LVL02
			Q_PntSprite->PntSprite[Count].CNTR += 1 *_->TimeScale;

			jet=0;
			while((jet < 5 * _->TimeScale) && (Q_PntSprite->PntSprite[Count].CNTR > 3) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.06f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 13;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Q_PntSprite->PntSprite[Count].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_PntSprite->PntSprite[_->NomPntSprite].IR > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IG > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IB > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = Q_PntSprite->PntSprite[Count].Alpha;
				//if(Q_PntSprite->PntSprite[_->NomPntSprite].Alpha > 255) Q_PntSprite->PntSprite[Count].Alpha = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF05, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;
				//Q_PntSprite->PntSprite[Count].ATTLightON = 0;
				//Qpo->Light_Remove(Q_PntSprite->PntSprite[Count].ATTLight);

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.2 *_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.2 * _->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed/6)*_->TimeScale;

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02/player[g_Player]->TestVALUE09;

			//geWorld_SetLightAttributes(World, Q_PntSprite->PntSprite[Count].ATTLight, &Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].ATTLightColor, 200, GE_true);
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 13:		//QA EFFECT 03
			{
			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF05, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (4*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (4*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 14:		//ORIG SPRITE EFF QA EFFECT 01
			{

			//Particle ejjector LVL02
			Q_PntSprite->PntSprite[Count].CNTR += 1 *_->TimeScale;

			jet=0;
			while((jet < 5 * _->TimeScale) && (Q_PntSprite->PntSprite[Count].CNTR > 3) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.06f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 15;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Q_PntSprite->PntSprite[Count].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_PntSprite->PntSprite[_->NomPntSprite].IR > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IG > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IB > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = Q_PntSprite->PntSprite[Count].Alpha;
				//if(Q_PntSprite->PntSprite[_->NomPntSprite].Alpha > 255) Q_PntSprite->PntSprite[Count].Alpha = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.2 *_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.2 * _->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed/6)*_->TimeScale;

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02/player[g_Player]->TestVALUE09;

			//geWorld_SetLightAttributes(World, Q_PntSprite->PntSprite[Count].ATTLight, &Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].ATTLightColor, 200, GE_true);
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 15:		//QA EFFECT 03
			{
			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (4*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (4*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 16:	//QA EFFECT 01
			{
			//Particle ejjector LVL02
			Q_PntSprite->PntSprite[Count].CNTR += 1 *_->TimeScale;

			jet=0;
			while((jet < 5 * _->TimeScale) && (Q_PntSprite->PntSprite[Count].CNTR > 3) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.06f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 17;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Q_PntSprite->PntSprite[Count].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_PntSprite->PntSprite[_->NomPntSprite].IR > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IG > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IB > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = Q_PntSprite->PntSprite[Count].Alpha;
				//if(Q_PntSprite->PntSprite[_->NomPntSprite].Alpha > 255) Q_PntSprite->PntSprite[Count].Alpha = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.8 *_->TimeScale < 35) Q_PntSprite->PntSprite[Count].Speed += 0.8 * _->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 35;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 17:		//QA EFFECT 03
			{
			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (4*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (4*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 9) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 9;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 18:		//QA EFFECT 03
			{
			//Particle ejjector LVL02
			Q_PntSprite->PntSprite[Count].CNTR += 1 *_->TimeScale;

			jet=0;
			while((jet < 8 * _->TimeScale) && (Q_PntSprite->PntSprite[Count].CNTR > 2) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
				Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
				Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.06f;		//0.025f//0.002f
				Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 19;

				Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				Q_PntSprite->PntSprite[_->NomPntSprite].IG = Q_PntSprite->PntSprite[Count].Alpha;
				Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				if(Q_PntSprite->PntSprite[_->NomPntSprite].IR > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IG > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
				if(Q_PntSprite->PntSprite[_->NomPntSprite].IB > 255) Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = Q_PntSprite->PntSprite[Count].Alpha;
				//if(Q_PntSprite->PntSprite[_->NomPntSprite].Alpha > 255) Q_PntSprite->PntSprite[Count].Alpha = 255;

				Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.4;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
				Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
				Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

				Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

				Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

				_->NomPntSprite++;
				jet++;
				}

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			//Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);


			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (4*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (4*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.8*_->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 0.8*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 20;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF06, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 19:		//QA EFFECT 03
			{
			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			//Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (5*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}


			/*TEMP CHANGEif(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + 0.25*_->TimeScale < 4) Q_PntSprite->PntSprite[Count].Speed += 0.25*_->TimeScale;
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = 4;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - 0.5*_->TimeScale > 0.3) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
				else Q_PntSprite->PntSprite[Count].Speed = 0.3;
				}*/


				/*if(Q_PntSprite->PntSprite[Count].Speed - 0.01*_->TimeScale > 0.0025) Q_PntSprite->PntSprite[Count].Speed += 0.01*_->TimeScale;
				else Q_PntSprite->PntSprite[Count].Speed = 0.0025;*/


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF07, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->shadow, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, shadow, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 20:	//QA EFFECT PLASMA EJECTOR
			{
			//Particle ejjector LVL02
			player[g_Player]->CNTR5 += 1;
			RotAMT = 0;

			TempVec1 = Q_PntSprite->PntSprite[Count].Pos;

			//TempVec1.y += (((float)rand() / 32767)-0.5)*9;

			if(player[g_Player]->CNTR5 > 3)
				{
				player[g_Player]->CNTR5 = 0;

				jet=0;
				while((jet < 20) && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.0165f;		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 21;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 55;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].SpeedDIR = 0.2;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = TempVec1;

					Q_PntSprite->PntSprite[_->NomPntSprite].VecUp = Q_PntSprite->PntSprite[Count].TraVec;

						//Calculate Direction Vectors
					Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
					Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft.y = 0;
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft);
					
					Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft, &Q_PntSprite->PntSprite[_->NomPntSprite].VecUp, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[_->NomPntSprite].VecLeft,&Q_PntSprite->PntSprite[_->NomPntSprite].VecUp,&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Transform_New_YRotation(&RotateMatrix3, RotAMT);

					RotAMT += 0.314;

					Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
					Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);
					Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[_->NomPntSprite].TraVec);

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//Q_PntSprite->PntSprite[Count].ATTLightON = 0;
				//Qpo->Light_Remove(Q_PntSprite->PntSprite[Count].ATTLight);

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			//if(Q_PntSprite->PntSprite[Count].Speed + 0.8 *_->TimeScale < 35) Q_PntSprite->PntSprite[Count].Speed += 0.8 * _->TimeScale;
			//else Q_PntSprite->PntSprite[Count].Speed = 35;


			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*7*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);


			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[Count].Scale * 70, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);

			//geWorld_SetLightAttributes(World, Q_PntSprite->PntSprite[Count].ATTLight, &Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].ATTLightColor, 200, GE_true);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF01, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 255;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 255;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha/2.2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->SparkCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.15);

			//### Increment Corona Material
			if(Q_PntSprite->PntSprite[Count].CoronaMatCntDIR == 0)
				{
				Q_PntSprite->PntSprite[Count].CoronaMatCnt++;
				if(Q_PntSprite->PntSprite[Count].CoronaMatCnt > 3)
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt = 3;
					Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 1;
					}
				}
			else
				{
				Q_PntSprite->PntSprite[Count].CoronaMatCnt--;
				if(Q_PntSprite->PntSprite[Count].CoronaMatCnt < 0)
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt = 0;
					Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 0;
					}
				}
			} break;


		case 21:		//QA EFFECT 03
			{
			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			//Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, Q_PntSprite->PntSprite[_->NomPntSprite].Scale * 215, Medias->QAEFF03, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (7*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (7*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}


			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + 0.25*_->TimeScale < 10) Q_PntSprite->PntSprite[Count].Speed += 0.25*_->TimeScale;
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = 10;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - 0.5*_->TimeScale > 0.3) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
				else Q_PntSprite->PntSprite[Count].Speed = 0.3;
				}

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF07, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 23:	//SOLID QA EFFECT INTELLIGENCE BOOST
			{
			if(Q_PntSprite->PntSprite[Count].Speed < 0.25 && Q_PntSprite->PntSprite[Count].SpeedDIR == 0) Q_PntSprite->PntSprite[Count].Alpha = 1;
			else
				{
				if(Q_PntSprite->PntSprite[Count].AlphaLOCK == 0)
					{
					Q_PntSprite->PntSprite[Count].AlphaLOCK = 1;
					Q_PntSprite->PntSprite[Count].Alpha = Q_PntSprite->PntSprite[Count].AlphaSTR;
					Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
					}
				}

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.65*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.65*_->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}


			if(Q_PntSprite->PntSprite[Count].HeightPos < 7.5) Q_PntSprite->PntSprite[Count].SpeedMAX = (Q_PntSprite->PntSprite[Count].HeightPos/3) * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);
			else Q_PntSprite->PntSprite[Count].SpeedMAX = ((15 - Q_PntSprite->PntSprite[Count].HeightPos)/3) * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + (Q_PntSprite->PntSprite[Count].SpeedMAX/7)*_->TimeScale < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += (Q_PntSprite->PntSprite[Count].SpeedMAX/7)*_->TimeScale;
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (Q_PntSprite->PntSprite[Count].SpeedMAX/3)*_->TimeScale > 0.1) Q_PntSprite->PntSprite[Count].Speed -= (Q_PntSprite->PntSprite[Count].SpeedMAX/3)*_->TimeScale;
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}


			Q_PntSprite->PntSprite[Count].PushOUT += Q_PntSprite->PntSprite[Count].Speed*_->TimeScale;

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);
			TempVec1 = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			TempVec1.y += 10;
			TempVec1.y -= Q_PntSprite->PntSprite[Count].HeightPos;
			Q_PntSprite->PntSprite[Count].InitPos = TempVec1;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF07, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 24:	//SOLID QA EFFECT REL ENERGY EFFICIENCY
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (7*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (7*_->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + (0.15*_->TimeScale) < 2) Q_PntSprite->PntSprite[Count].Speed += (0.15*_->TimeScale);
			else Q_PntSprite->PntSprite[Count].Speed = 2;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, (Q_PntSprite->PntSprite[Count].Speed*_->TimeScale), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF09 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 25:	//SOLID QA EFFECT REL ENERGY EFFICIENCY
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/250))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/250))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/7) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/7) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);
			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].CNTR += (1 * _->TimeScale);
			
			if(Q_PntSprite->PntSprite[Count].CNTR > (8 + (23 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/250)))))
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				jet=0;
				while(jet < 3 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.012f;
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 24;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 120;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 75;
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF09, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 26:		//QA EFFECT 03
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.85) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.85);	//1  //3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + 0.1 < 0.9) Q_PntSprite->PntSprite[Count].Speed += 0.1;
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = 0.9;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - 0.05 > 0.02) Q_PntSprite->PntSprite[Count].Speed -= 0.05;
				else Q_PntSprite->PntSprite[Count].Speed = 0.02;
				}

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].Alpha+130;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].Alpha+130;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 27:	//SOLID QA EFFECT STRENGTH BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (5.3 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5.3 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 10 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);


			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

			Q_PntSprite->PntSprite[Count].RotAMT += (0.025 + (0.45 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500))) * _->TimeScale;

			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].RotAMTSTR = Q_PntSprite->PntSprite[Count].RotAMT;
			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 50)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 1
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 100)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 2
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 150)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 3
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 250)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 4
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			Q_PntSprite->PntSprite[Count].RotAMT = Q_PntSprite->PntSprite[Count].RotAMTSTR;
			} break;


		case 28:	//SOLID QA EFFECT INTELLIGENCE BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (5.3 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5.3 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 10 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);


			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

			Q_PntSprite->PntSprite[Count].RotAMT += (0.025 + (0.45 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500))) * _->TimeScale;

			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].RotAMTSTR = Q_PntSprite->PntSprite[Count].RotAMT;
			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 50)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 1
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 100)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 2
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 150)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 3
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 250)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 4
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			Q_PntSprite->PntSprite[Count].RotAMT = Q_PntSprite->PntSprite[Count].RotAMTSTR;
			} break;


		case 29:	//SOLID QA EFFECT PHYSICAL STR BOOST
			{
			if(Q_PntSprite->PntSprite[Count].Speed < 0.25 && Q_PntSprite->PntSprite[Count].SpeedDIR == 0) Q_PntSprite->PntSprite[Count].Alpha = 1;
			else
				{
				if(Q_PntSprite->PntSprite[Count].AlphaLOCK == 0)
					{
					Q_PntSprite->PntSprite[Count].AlphaLOCK = 1;
					Q_PntSprite->PntSprite[Count].Alpha = Q_PntSprite->PntSprite[Count].AlphaSTR;
					Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
					}
				}

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.75) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.75);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}


			//if(Q_PntSprite->PntSprite[Count].HeightPos < 7.5) Q_PntSprite->PntSprite[Count].SpeedMAX = Q_PntSprite->PntSprite[Count].HeightPos/3;
			//else Q_PntSprite->PntSprite[Count].SpeedMAX = (15 - Q_PntSprite->PntSprite[Count].HeightPos)/3;

			Q_PntSprite->PntSprite[Count].SpeedMAX = 3;

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + (Q_PntSprite->PntSprite[Count].SpeedMAX/3) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += (Q_PntSprite->PntSprite[Count].SpeedMAX/3);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (Q_PntSprite->PntSprite[Count].SpeedMAX/2) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= (Q_PntSprite->PntSprite[Count].SpeedMAX/2);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += Q_PntSprite->PntSprite[Count].Speed;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);


			//Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed);

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 30:	//SOLID QA EFFECT QUICKNESS BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.75 * (((float)rand() / 32767) * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/1000))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.75 * (((float)rand() / 32767) * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/1000))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 3;

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + (Q_PntSprite->PntSprite[Count].SpeedMAX/3) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += (Q_PntSprite->PntSprite[Count].SpeedMAX/3);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (Q_PntSprite->PntSprite[Count].SpeedMAX/2) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= (Q_PntSprite->PntSprite[Count].SpeedMAX/2);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
			
				if((Q_PntSprite->PntSprite[Count].CNTR > (20 - (8 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/5000)))) && (((float)rand() / 32767) < (((float)rand() / 32767) * Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2000)))
					{
					Q_PntSprite->PntSprite[Count].CNTR = 0;

					jet=0;
					while(jet < 1 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.012f;
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 31;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 65;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.3;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec = Q_PntSprite->PntSprite[Count].TraVec;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x += (((float)rand() / 32767)-0.5)*0.3;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y += ((((float)rand() / 32767)-0.5)*0.5)+0.75;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z += (((float)rand() / 32767)-0.5)*0.3;

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}

					Q_PntSprite->PntSprite[Count].CoronaON = 1;
					Q_PntSprite->PntSprite[Count].CoronaALPHADIR = 0;
					Q_PntSprite->PntSprite[Count].CoronaALPHA = 0;
					}
				}


			//if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			//else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			player[g_Player]->QA_EFF_BONEMATRIX.Translation.x = playerAV[g_Player]->Xform.Translation.x;
			player[g_Player]->QA_EFF_BONEMATRIX.Translation.y = playerAV[g_Player]->Xform.Translation.y + 65;
			player[g_Player]->QA_EFF_BONEMATRIX.Translation.z = playerAV[g_Player]->Xform.Translation.z;

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].CoronaON == 1)
				{
				if(Q_PntSprite->PntSprite[Count].CoronaALPHADIR == 0)
					{
					if(Q_PntSprite->PntSprite[Count].CoronaALPHA + 4*_->TimeScale < 30) Q_PntSprite->PntSprite[Count].CoronaALPHA += 4*_->TimeScale;
					else
						{
						Q_PntSprite->PntSprite[Count].CoronaALPHA = 85;
						Q_PntSprite->PntSprite[Count].CoronaALPHADIR = 1;
						}
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].CoronaALPHA - 3*_->TimeScale > 0) Q_PntSprite->PntSprite[Count].CoronaALPHA -= 3*_->TimeScale;
					else
						{
						Q_PntSprite->PntSprite[Count].CoronaON = 0;
						Q_PntSprite->PntSprite[Count].CoronaALPHA = 0;
						}
					}

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.r = 255;
				Q_PntSprite->PntSprite[Count].Lvert.g = 255;
				Q_PntSprite->PntSprite[Count].Lvert.b = 255;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].CoronaALPHA;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->SparkCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.05);

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].OldPos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].OldPos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].OldPos.z;
				Q_PntSprite->PntSprite[Count].Lvert.r = 255;
				Q_PntSprite->PntSprite[Count].Lvert.g = 255;
				Q_PntSprite->PntSprite[Count].Lvert.b = 255;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].CoronaALPHA;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->SparkCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.05);

				//### Increment Corona Material
				if(Q_PntSprite->PntSprite[Count].CoronaMatCntDIR == 0)
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt++;
					if(Q_PntSprite->PntSprite[Count].CoronaMatCnt > 3)
						{
						Q_PntSprite->PntSprite[Count].CoronaMatCnt = 3;
						Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt--;
					if(Q_PntSprite->PntSprite[Count].CoronaMatCnt < 0)
						{
						Q_PntSprite->PntSprite[Count].CoronaMatCnt = 0;
						Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 0;
						}
					}
				}

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF17, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 31:	//SOLID QA EFFECT QUICKNESS
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (3*_->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.2*_->TimeScale < 8) Q_PntSprite->PntSprite[Count].Speed += 0.2*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 8;

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Qpo->Collision_RayTest(//World,
				 NULL,
				 NULL,
				 &Q_PntSprite->PntSprite[Count].OldPos,
				 &Q_PntSprite->PntSprite[Count].Pos,
				 //GE_CONTENTS_CANNOT_OCCUPY,
				 //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
				 0xffffffff, NULL, NULL,
				 &Q_PntSprite->PntSprite[Count].Collision))
				{
				if(Q_PntSprite->PntSprite[Count].Collision.Avatar == 0)
					{
					Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].OldPos;
					Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].Collision.Avatar.IDflag != playerAV[g_Player]->Avatar.IDflag)
						{
						Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].OldPos;
						Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
						}
					}
				}

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 32:	//SOLID QA EFFECT CONSTITUTION BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (5.3 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5.3 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 16 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);


			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			//Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			//Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecLeft);

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 1.0f, 0.25f);
	//*glBegin(GL_LINES);
	glVertex3f(Q_PntSprite->PntSprite[Count].InitPos.x, Q_PntSprite->PntSprite[Count].InitPos.y, Q_PntSprite->PntSprite[Count].InitPos.z);
	glVertex3f(Q_PntSprite->PntSprite[Count].InitPos.x + (Q_PntSprite->PntSprite[Count].VecLeft.x * 250), Q_PntSprite->PntSprite[Count].InitPos.y + (Q_PntSprite->PntSprite[Count].VecLeft.y * 250), Q_PntSprite->PntSprite[Count].InitPos.z + (Q_PntSprite->PntSprite[Count].VecLeft.z * 250));
	//*glEnd();
#endif

			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

			Q_PntSprite->PntSprite[Count].RotAMT += (0.025 + (0.45 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500))) * _->TimeScale;

			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].RotAMTSTR = Q_PntSprite->PntSprite[Count].RotAMT;
			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &player[g_Player]->QA_EFF_BONEMATRIX.Translation, &player[g_Player]->ViewXForm.Translation, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].AlphaSTR, 255, 255, 255, 0);
			//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 50 && 0)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 1
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &player[g_Player]->QA_EFF_BONEMATRIX.Translation, &player[g_Player]->ViewXForm.Translation, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].AlphaSTR, 255, 255, 255, 0);
				//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 100 && 0)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 2
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &player[g_Player]->QA_EFF_BONEMATRIX.Translation, &player[g_Player]->ViewXForm.Translation, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].AlphaSTR, 255, 255, 255, 0);
				//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 150 && 0)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 3
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &player[g_Player]->QA_EFF_BONEMATRIX.Translation, &player[g_Player]->ViewXForm.Translation, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].AlphaSTR, 255, 255, 255, 0);
				//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 250 && 0)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 4
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &player[g_Player]->QA_EFF_BONEMATRIX.Translation, &player[g_Player]->ViewXForm.Translation, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].AlphaSTR, 255, 255, 255, 0);
				//Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF32, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			Q_PntSprite->PntSprite[Count].RotAMT = Q_PntSprite->PntSprite[Count].RotAMTSTR;
			} break;


		case 33:	//SOLID QA EFFECT DEXTERITY BOOST
			{
			if(Q_PntSprite->PntSprite[Count].Speed < 0.25 && Q_PntSprite->PntSprite[Count].SpeedDIR == 0) Q_PntSprite->PntSprite[Count].Alpha = 1;
			else
				{
				if(Q_PntSprite->PntSprite[Count].AlphaLOCK == 0)
					{
					Q_PntSprite->PntSprite[Count].AlphaLOCK = 1;
					Q_PntSprite->PntSprite[Count].Alpha = Q_PntSprite->PntSprite[Count].AlphaSTR;
					Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
					}
				}

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.75)*_->TimeScale > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.75*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}


			//Anti Gravity
			//Q_PntSprite->PntSprite[Count].TraVec.y += 0.02;

			//Q_PntSprite->PntSprite[Count].Scale += 0.003;


			Q_PntSprite->PntSprite[Count].SpeedMAX = 5;

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + (Q_PntSprite->PntSprite[Count].SpeedMAX/4)*_->TimeScale < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += (Q_PntSprite->PntSprite[Count].SpeedMAX/4)*_->TimeScale;
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (Q_PntSprite->PntSprite[Count].SpeedMAX/3)*_->TimeScale > 0.05) Q_PntSprite->PntSprite[Count].Speed -= (Q_PntSprite->PntSprite[Count].SpeedMAX/3)*_->TimeScale;
				else Q_PntSprite->PntSprite[Count].Speed = 0.05;

				//Q_PntSprite->PntSprite[Count].TraVec.y += (((float)rand() / 32767)-0.5)*0.95;
				//Q_PntSprite->PntSprite[Count].TraVec.x += (((float)rand() / 32767)-0.5)*0.1;
				//Q_PntSprite->PntSprite[Count].TraVec.z += (((float)rand() / 32767)-0.5)*0.1;

				Q_PntSprite->PntSprite[Count].CNTR += ((float)rand() / 32767)*10;
			
				if(Q_PntSprite->PntSprite[Count].CNTR > 60 && Q_PntSprite->PntSprite[Count].LinkALPHADIR == 0)
					{
					Q_PntSprite->PntSprite[Count].CNTR = 0;

					if((_->NomPntSprite > 1) && (Count - 1) >= 0)
						{
						Tempint1 = Count - 1;

						if(Qpo->Vec3d_DistanceBetween(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Tempint1].Pos) < 150)
							{
							Q_PntSprite->PntSprite[Count].LinkON = 1;
							Q_PntSprite->PntSprite[Count].LinkTARGET = Tempint1;
							Q_PntSprite->PntSprite[Count].LinkALPHA = 0;
							Q_PntSprite->PntSprite[Count].LinkALPHADIR = 0;
							Q_PntSprite->PntSprite[Count].Alpha = 70;
							Q_PntSprite->PntSprite[Q_PntSprite->PntSprite[Count].LinkTARGET].Alpha = 70;
							}
						}
					}
				}


			if(Q_PntSprite->PntSprite[Count].LinkON == 1)
				{
				if(Q_PntSprite->PntSprite[Count].LinkALPHADIR == 0)
					{
					if(Q_PntSprite->PntSprite[Count].LinkALPHA + 20*_->TimeScale < 85) Q_PntSprite->PntSprite[Count].LinkALPHA += 20*_->TimeScale;
					else
						{
						Q_PntSprite->PntSprite[Count].LinkALPHA = 85;
						Q_PntSprite->PntSprite[Count].LinkALPHADIR = 1;
						}
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].LinkALPHA - 20*_->TimeScale > 0) Q_PntSprite->PntSprite[Count].LinkALPHA -= 20*_->TimeScale;
					else
						{
						Q_PntSprite->PntSprite[Count].LinkALPHA = 0;
						Q_PntSprite->PntSprite[Count].LinkON = 0;
						Q_PntSprite->PntSprite[Count].LinkTARGET = Tempint1;
						Q_PntSprite->PntSprite[Count].LinkALPHA = 0;
						}
					}

				Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Q_PntSprite->PntSprite[Count].LinkTARGET].Pos;

				//Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, 1, Medias->QAEFF16, Q_PntSprite->PntSprite[Count].LinkALPHA, 255, 255, 255, 0);

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.r = 255;
				Q_PntSprite->PntSprite[Count].Lvert.g = 255;
				Q_PntSprite->PntSprite[Count].Lvert.b = 255;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].LinkALPHA;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->SparkCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.05);

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].OldPos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].OldPos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].OldPos.z;
				Q_PntSprite->PntSprite[Count].Lvert.r = 255;
				Q_PntSprite->PntSprite[Count].Lvert.g = 255;
				Q_PntSprite->PntSprite[Count].Lvert.b = 255;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].LinkALPHA;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->SparkCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.05);

				//### Increment Corona Material
				if(Q_PntSprite->PntSprite[Count].CoronaMatCntDIR == 0)
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt++;
					if(Q_PntSprite->PntSprite[Count].CoronaMatCnt > 3)
						{
						Q_PntSprite->PntSprite[Count].CoronaMatCnt = 3;
						Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt--;
					if(Q_PntSprite->PntSprite[Count].CoronaMatCnt < 0)
						{
						Q_PntSprite->PntSprite[Count].CoronaMatCnt = 0;
						Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 0;
						}
					}
				}



			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += Q_PntSprite->PntSprite[Count].Speed;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);


			//Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed);

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;


			/*Tempint1 = rand() % (_->NomPntSprite - 1);

			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Tempint1].Pos;

			//Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].OldPos, -Q_PntSprite->PntSprite[Count].Speed*3*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].OldPos);

			Q.ShowLine(&Q_PntSprite->PntSprite[Count].Pos, &Q_PntSprite->PntSprite[Count].OldPos, &player[g_Player]->ViewXForm.Translation, 0.35, Medias->QAEFF16, Q_PntSprite->PntSprite[Count].Alpha, 255, 255, 255, 0);*/




			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF17, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 34:	//SOLID QA EFFECT DEXTERITY BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = (0.6 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)));

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/6) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/6) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);
			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);

			Q_PntSprite->PntSprite[Count].RotAMT += 0.02 + (0.55 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500));

			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF18, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 35:	//SOLID QA EFFECT DEXTERITY
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (2*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (2*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (11*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (11*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;

					Q_PntSprite->PntSprite[Count].CNTR = 0;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (15*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha2 += (15*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}



			if(Q_PntSprite->PntSprite[Count].Speed + 0.15*_->TimeScale < 8) Q_PntSprite->PntSprite[Count].Speed += 0.15*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 8;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.02;


			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			
			if(Qpo->Collision_RayTest(//World,
				 NULL,
				 NULL,
				 &Q_PntSprite->PntSprite[Count].OldPos,
				 &Q_PntSprite->PntSprite[Count].Pos,
				 //GE_CONTENTS_CANNOT_OCCUPY,
				 //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
				 0xffffffff, NULL, NULL,
				 &Q_PntSprite->PntSprite[Count].Collision))
				{
				if(Q_PntSprite->PntSprite[Count].Collision.Avatar == NULL)
					{
					Q_PntSprite->PntSprite[Count].Pos.acSet(Q_PntSprite->PntSprite[Count].Collision.Impact.m_X, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Y, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Z);
					Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
					//Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].Speed / 1.5;
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].Collision.Avatar.IDflag != playerAV[g_Player]->Avatar.IDflag)
						{
						Q_PntSprite->PntSprite[Count].Pos.acSet(Q_PntSprite->PntSprite[Count].Collision.Impact.m_X, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Y, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Z);
						Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
						//Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].Speed / 1.5;
						}
					}
				}


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF09 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF19 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 36:	//SOLID QA EFFECT AGG POWER BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (3*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (1.35*_->TimeScale) < 16) Q_PntSprite->PntSprite[Count].Alpha2 += (1.35*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 16;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + ((Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)* 10);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.2) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.2;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF20, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF21 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 37:	//SOLID QA EFFECT AGG POWER BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (3*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (1.35*_->TimeScale) < 16) Q_PntSprite->PntSprite[Count].Alpha2 += (1.35*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 16;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + ((Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)* 10);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF20, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF21 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 38:	//SOLID QA EFFECT AGG POWER BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (3*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (1.35*_->TimeScale) < 16) Q_PntSprite->PntSprite[Count].Alpha2 += (1.35*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 16;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + ((Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)* 10);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF20, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF21 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 39:	//SOLID QA EFFECT DEFENSIVE POWER BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (3.7*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (3.7*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (0.35*_->TimeScale) < 16) Q_PntSprite->PntSprite[Count].Alpha2 += (0.35*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 16;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + ((Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)* 10);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.2) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.2;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF23, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF22 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 40:	//SOLID QA EFFECT WEAPON PACK
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.5 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.5 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/7) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/7) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 NECK", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 NECK", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Q_PntSprite->PntSprite[Count].InitPos.y += 2;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].CNTR += 1;
			
			if(Q_PntSprite->PntSprite[Count].CNTR > 15)
				{
				Q_PntSprite->PntSprite[Count].CNTR = 0;

				jet=0;
				while(jet < 3 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
					{
					Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
					Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
					Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.012f;	//0.02		//0.025f//0.002f
					Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 41;

					Q_PntSprite->PntSprite[_->NomPntSprite].IR = 120;
					Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
					Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

					Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 20 + (80 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10000));
					Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5);
					Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5);

					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
					Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

					Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

					Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

					_->NomPntSprite++;
					jet++;
					}
				}

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF24, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 41:	//SOLID QA EFFECT WEAPON PACK
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (8.5*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (8.5*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.15*_->TimeScale < 2) Q_PntSprite->PntSprite[Count].Speed += 0.15*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 2;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			
			if(Qpo->Collision_RayTest(//World,
				 NULL,
				 NULL,
				 &Q_PntSprite->PntSprite[Count].OldPos,
				 &Q_PntSprite->PntSprite[Count].Pos,
				 //GE_CONTENTS_CANNOT_OCCUPY,
				 //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
				 0xffffffff, NULL, NULL,
				 &Q_PntSprite->PntSprite[Count].Collision))
				{
				if(Q_PntSprite->PntSprite[Count].Collision.Avatar == NULL)
					{
					Q_PntSprite->PntSprite[Count].Pos.acSet(Q_PntSprite->PntSprite[Count].Collision.Impact.m_X, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Y, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Z);
					Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].Collision.Avatar.IDflag != playerAV[g_Player]->Avatar.IDflag)
						{
						Q_PntSprite->PntSprite[Count].Pos.acSet(Q_PntSprite->PntSprite[Count].Collision.Impact.m_X, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Y, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Z);
						Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
						}
					}
				}

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF24 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 42:	//SOLID QA EFFECT WEAPON SOMETHING
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.75 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.75 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 3;

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
			
				if(Q_PntSprite->PntSprite[Count].CNTR > 18)
					{
					Q_PntSprite->PntSprite[Count].CNTR = 0;

					jet=0;
					while(jet < 1 && (_->NomPntSprite < Q_PntSprite->m_ArrayMx))
						{
						Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
						Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
						Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.012f;	//0.02		//0.025f//0.002f
						Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 43;

						Q_PntSprite->PntSprite[_->NomPntSprite].IR = 255;	//120
						Q_PntSprite->PntSprite[_->NomPntSprite].IG = 255;
						Q_PntSprite->PntSprite[_->NomPntSprite].IB = 255;

						Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 65;
						Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0.3;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos = Q_PntSprite->PntSprite[Count].Pos;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec = Q_PntSprite->PntSprite[Count].TraVec;

						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x += (((float)rand() / 32767)-0.5)*0.3;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y += ((((float)rand() / 32767)-0.5)*0.5)+0.75;
						Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z += (((float)rand() / 32767)-0.5)*0.3;

						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y += (((float)rand() / 32767)-0.5)*1;
						Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z += (((float)rand() / 32767)-0.5)*1;

						Q_PntSprite->PntSprite[_->NomPntSprite].AvID = Q_PntSprite->PntSprite[Count].AvID;

						Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

						_->NomPntSprite++;
						jet++;
						}


					Q_PntSprite->PntSprite[Count].CoronaON = 1;
					Q_PntSprite->PntSprite[Count].CoronaALPHADIR = 0;
					Q_PntSprite->PntSprite[Count].CoronaALPHA = 0;
					}
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 SPINE", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);


			
			if(Q_PntSprite->PntSprite[Count].CoronaON == 1)
				{
				if(Q_PntSprite->PntSprite[Count].CoronaALPHADIR == 0)
					{
					if(Q_PntSprite->PntSprite[Count].CoronaALPHA + 4*_->TimeScale < 30) Q_PntSprite->PntSprite[Count].CoronaALPHA += 4*_->TimeScale;
					else
						{
						Q_PntSprite->PntSprite[Count].CoronaALPHA = 85;
						Q_PntSprite->PntSprite[Count].CoronaALPHADIR = 1;
						}
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].CoronaALPHA - 3*_->TimeScale > 0) Q_PntSprite->PntSprite[Count].CoronaALPHA -= 3*_->TimeScale;
					else
						{
						Q_PntSprite->PntSprite[Count].CoronaON = 0;
						Q_PntSprite->PntSprite[Count].CoronaALPHA = 0;
						}
					}

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.r = 255;
				Q_PntSprite->PntSprite[Count].Lvert.g = 255;
				Q_PntSprite->PntSprite[Count].Lvert.b = 255;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].CoronaALPHA;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->EGrabCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.05);

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].OldPos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].OldPos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].OldPos.z;
				Q_PntSprite->PntSprite[Count].Lvert.r = 255;
				Q_PntSprite->PntSprite[Count].Lvert.g = 255;
				Q_PntSprite->PntSprite[Count].Lvert.b = 255;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].CoronaALPHA;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->EGrabCorona[Q_PntSprite->PntSprite[Count].CoronaMatCnt], QPOLY_TYPE_PNT, Q_PntSprite->PntSprite[Count].RenderFlags, 0.05);

				//### Increment Corona Material
				if(Q_PntSprite->PntSprite[Count].CoronaMatCntDIR == 0)
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt++;
					if(Q_PntSprite->PntSprite[Count].CoronaMatCnt > 3)
						{
						Q_PntSprite->PntSprite[Count].CoronaMatCnt = 3;
						Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 1;
						}
					}
				else
					{
					Q_PntSprite->PntSprite[Count].CoronaMatCnt--;
					if(Q_PntSprite->PntSprite[Count].CoronaMatCnt < 0)
						{
						Q_PntSprite->PntSprite[Count].CoronaMatCnt = 0;
						Q_PntSprite->PntSprite[Count].CoronaMatCntDIR = 0;
						}
					}
				}

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF24, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 43:	//SOLID QA EFFECT WEAPON SOMETHING
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (3*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.2*_->TimeScale < 8) Q_PntSprite->PntSprite[Count].Speed += 0.2*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 8;

			//Q_PntSprite->PntSprite[Count].TraVec.y -= 0.01;


			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed)*_->TimeScale;

			
			if(Qpo->Collision_RayTest(//World,
				 NULL,
				 NULL,
				 &Q_PntSprite->PntSprite[Count].OldPos,
				 &Q_PntSprite->PntSprite[Count].Pos,
				 //GE_CONTENTS_CANNOT_OCCUPY,
				 //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
				 0xffffffff, NULL, NULL,
				 &Q_PntSprite->PntSprite[Count].Collision))
				{
				if(Q_PntSprite->PntSprite[Count].Collision.Avatar == NULL)
					{
					Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].OldPos;
					Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
					//Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].Speed / 1.5;
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].Collision.Avatar.IDflag != playerAV[g_Player]->Avatar.IDflag)
						{
						Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].OldPos;
						Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
						//Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].Speed / 1.5;
						}
					}
				}


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF25 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 44:	//SOLID QA EFFECT WEAPON ACCURACY
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.45 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.45 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + (7 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10000));

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/(6 * (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10000)))) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/(6 * (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10000)))) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}
			
			if(Q_PntSprite->PntSprite[Count].AvID == 250) {}//Qpo->AvatarView_GetBoneTransform_PntSprite(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->Avatar_GetWeaponTransform(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R HAND", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);

			Q_PntSprite->PntSprite[Count].RotAMT += 0.025 + (0.85 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10000));

			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT * _->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);
			
			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].RotAMTSTR = Q_PntSprite->PntSprite[Count].RotAMT;

			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF26, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);

			Q_PntSprite->PntSprite[Count].RotAMT -= 0.02;

			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT * _->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Sprite Trail 1

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 40 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 10;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF26, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);

			Q_PntSprite->PntSprite[Count].RotAMT -= 0.02;

			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT * _->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Sprite Trail 2
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 40 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 10;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF26, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);

			Q_PntSprite->PntSprite[Count].RotAMT -= 0.02;

			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT * _->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Sprite Trail 3
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 40 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 10;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF26, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);

			Q_PntSprite->PntSprite[Count].RotAMT -= 0.02;

			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT * _->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Sprite Trail 4

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 40 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 10;

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF26, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			Q_PntSprite->PntSprite[Count].RotAMT = Q_PntSprite->PntSprite[Count].RotAMTSTR;
			} break;



		case 45:		//QA EFFECT 03
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (3) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (3);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}


			if(Q_PntSprite->PntSprite[Count].Speed - 0.1 > 1) Q_PntSprite->PntSprite[Count].Speed -= 0.1;
			else Q_PntSprite->PntSprite[Count].Speed = 1;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);


			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].Alpha+130;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].Alpha+130;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 46:	//SOLID QA EFFECT STR BOOST LEG
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (5.3 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5.3 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 10 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);


			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

			Q_PntSprite->PntSprite[Count].RotAMT += (0.025 + (0.45 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500))) * _->TimeScale;

			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].RotAMTSTR = Q_PntSprite->PntSprite[Count].RotAMT;
			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 50)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 1
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 100)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 2
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 150)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 3
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 250)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 4
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			Q_PntSprite->PntSprite[Count].RotAMT = Q_PntSprite->PntSprite[Count].RotAMTSTR;
			} break;


		case 47:	//SOLID QA EFFECT STR BOOST LEG
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (5.3 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (5.3 * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 10 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((0.5 + (2 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((1 + (3 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY / 500))) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &Q_PntSprite->PntSprite[Count].VecUp);


			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

				//Calculate Direction Vectors
			Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
			Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
			Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
			Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

			Q_PntSprite->PntSprite[Count].RotAMT += (0.025 + (0.45 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500))) * _->TimeScale;

			Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
			Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
			Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
			Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
			Q_PntSprite->PntSprite[Count].RotAMTSTR = Q_PntSprite->PntSprite[Count].RotAMT;
			//## Store Pos
			Q_PntSprite->PntSprite[Count].PosSTR = Q_PntSprite->PntSprite[Count].Pos;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 50)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);

				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 1
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 100)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 2
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 150)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 3
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			if(Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY > 250)
				{
				Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].InitPos);
					//Calculate Direction Vectors
				Qpo->Transform_New_YRotation(&RotateMatrix, PI/2);
				Qpo->Transform_RotateVector(&RotateMatrix, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].VecLeft);
				Q_PntSprite->PntSprite[Count].VecLeft.y = 0;
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].VecLeft);
				Qpo->Vec3d_CrossProduct(&Q_PntSprite->PntSprite[Count].VecLeft, &Q_PntSprite->PntSprite[Count].VecUp, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Transform_New_LeftUpIn(&RotateMatrix2,&Q_PntSprite->PntSprite[Count].VecLeft,&Q_PntSprite->PntSprite[Count].VecUp,&Q_PntSprite->PntSprite[Count].TraVec);

				Q_PntSprite->PntSprite[Count].RotAMT -= 0.075;

				Qpo->Transform_New_YRotation(&RotateMatrix3, Q_PntSprite->PntSprite[Count].RotAMT);
				Qpo->Transform_Multiply(&RotateMatrix2, &RotateMatrix3, &RotateMatrix2);
				Qpo->Transform_GetIn(&RotateMatrix2, &Q_PntSprite->PntSprite[Count].TraVec);
				Qpo->Vec3d_Normalize(&Q_PntSprite->PntSprite[Count].TraVec);
				//### Move Sprite
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				//##### Sprite Trail 4
				Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, -Q_PntSprite->PntSprite[Count].Speed/5, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

				if(Q_PntSprite->PntSprite[Count].AlphaSTR - 25 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 25;

				Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
				Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
				Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
				Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].AlphaSTR;

				Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
				}

			Q_PntSprite->PntSprite[Count].Pos = Q_PntSprite->PntSprite[Count].PosSTR;
			Q_PntSprite->PntSprite[Count].RotAMT = Q_PntSprite->PntSprite[Count].RotAMTSTR;
			} break;


		case 48:	//SOLID QA EFFECT AGG POWER BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (3*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (1.35*_->TimeScale) < 16) Q_PntSprite->PntSprite[Count].Alpha2 += (1.35*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 16;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + ((Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)* 10);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF20, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF21 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 49:	//SOLID QA EFFECT AGG POWER BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					}
				}
			/*else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha + (5*_->TimeScale) < 65) Q_PntSprite->PntSprite[Count].Alpha += (5*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 65;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 0;
					}
				}*/

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].AlphaDIR2 == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha2 -= (3*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 0;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 1;
					Q_PntSprite->PntSprite[Count].AlphaDIR = 1;
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Alpha2 + (1.35*_->TimeScale) < 16) Q_PntSprite->PntSprite[Count].Alpha2 += (1.35*_->TimeScale);	//5  //25
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha2 = 16;
					Q_PntSprite->PntSprite[Count].AlphaDIR2 = 0;
					}
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 2 + ((Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)* 10);

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/4) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;

				Q_PntSprite->PntSprite[Count].CNTR += 1;
				}


			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF20, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha2;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF21 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 50:	//SOLID QA EFFECT LEFT LEG STR BOOST
			{
			if(Q_PntSprite->PntSprite[Count].Speed < 0.25 && Q_PntSprite->PntSprite[Count].SpeedDIR == 0) Q_PntSprite->PntSprite[Count].Alpha = 1;
			else
				{
				if(Q_PntSprite->PntSprite[Count].AlphaLOCK == 0)
					{
					Q_PntSprite->PntSprite[Count].AlphaLOCK = 1;
					Q_PntSprite->PntSprite[Count].Alpha = Q_PntSprite->PntSprite[Count].AlphaSTR;
					Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
					}
				}

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.65) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.65);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 1.3;

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + (Q_PntSprite->PntSprite[Count].SpeedMAX/3) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += (Q_PntSprite->PntSprite[Count].SpeedMAX/3);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (Q_PntSprite->PntSprite[Count].SpeedMAX/2) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= (Q_PntSprite->PntSprite[Count].SpeedMAX/2);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += Q_PntSprite->PntSprite[Count].Speed;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 51:	//SOLID QA EFFECT RIGHT LEG STR BOOST
			{
			if(Q_PntSprite->PntSprite[Count].Speed < 0.25 && Q_PntSprite->PntSprite[Count].SpeedDIR == 0) Q_PntSprite->PntSprite[Count].Alpha = 1;
			else
				{
				if(Q_PntSprite->PntSprite[Count].AlphaLOCK == 0)
					{
					Q_PntSprite->PntSprite[Count].AlphaLOCK = 1;
					Q_PntSprite->PntSprite[Count].Alpha = Q_PntSprite->PntSprite[Count].AlphaSTR;
					Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;
					}
				}

			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (0.65) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (0.65);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = 1.3;

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + (Q_PntSprite->PntSprite[Count].SpeedMAX/3) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += (Q_PntSprite->PntSprite[Count].SpeedMAX/3);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - (Q_PntSprite->PntSprite[Count].SpeedMAX/2) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= (Q_PntSprite->PntSprite[Count].SpeedMAX/2);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += Q_PntSprite->PntSprite[Count].Speed;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF08, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 52:	//SOLID QA EFFECT LEFT ARM DEX BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = (0.3 + (1 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)));

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF18, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 53:	//SOLID QA EFFECT RIGHT ARM DEX BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = (0.3 + (1 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)));

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R FOREARM", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF18, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 54:	//SOLID QA EFFECT LEFT LEG DEX BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = (0.3 + (1 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)));

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 L THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF18, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 55:	//SOLID QA EFFECT RIGHT LEG DEX BOOST
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= ((0.2 + (0.8 * (1 - (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/2500)))) * _->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			Q_PntSprite->PntSprite[Count].SpeedMAX = (0.3 + (1 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/500)));

			if(Q_PntSprite->PntSprite[Count].SpeedDIR == 0)
				{
				if(Q_PntSprite->PntSprite[Count].Speed + ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale) < Q_PntSprite->PntSprite[Count].SpeedMAX) Q_PntSprite->PntSprite[Count].Speed += ((Q_PntSprite->PntSprite[Count].SpeedMAX/3) * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Speed = Q_PntSprite->PntSprite[Count].SpeedMAX;
					Q_PntSprite->PntSprite[Count].SpeedDIR = 1;
					}
				}
			else
				{
				if(Q_PntSprite->PntSprite[Count].Speed - ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale) > 0.1) Q_PntSprite->PntSprite[Count].Speed -= ((Q_PntSprite->PntSprite[Count].SpeedMAX/2) * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 0.1;
				}

			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 R THIGH", &player[g_Player]->QA_EFF_BONEMATRIX);

			Q_PntSprite->PntSprite[Count].InitPos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

			Qpo->Transform_GetUp(&player[g_Player]->QA_EFF_BONEMATRIX, &player[g_Player]->In);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, -Q_PntSprite->PntSprite[Count].HeightPos, &player[g_Player]->In, &Q_PntSprite->PntSprite[Count].InitPos);

			Q_PntSprite->PntSprite[Count].PushOUT += (Q_PntSprite->PntSprite[Count].Speed * _->TimeScale);

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].InitPos, Q_PntSprite->PntSprite[Count].PushOUT, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF18, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 56:	//SOLID QA EFFECT JINK 3RD LEVEL
			{
			if(Q_PntSprite->PntSprite[Count].AvID == 250) Qpo->AvatarView_GetBoneTransform_PntSprite(playerAV[g_Player].operator ->(), "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);
			else Qpo->AvatarView_GetBoneTransform_PntSprite(&Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].AV, "BIP01 HEAD", &player[g_Player]->QA_EFF_BONEMATRIX);

			if(Q_PntSprite->PntSprite[Count].Vert1.y > (player[g_Player]->QA_EFF_BONEMATRIX.Translation.y + 120))
				{
				//### Progress Alpha
				if(Q_PntSprite->PntSprite[Count].Alpha - (20 * _->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (20 * _->TimeScale);
				else
					{
					Q_PntSprite->PntSprite[Count].Alpha = 0;
					Q_PntSprite->PntSprite[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomPntSprite - 1)
						{
						Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
						K++;
						}

					_->NomPntSprite--;
					}
				}
			
			//if(Q_PntSprite->PntSprite[Count].AvID == 250)
			//	{
				if(Q_PntSprite->PntSprite[Count].Speed + (0.05 * _->TimeScale) < 4 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10)) Q_PntSprite->PntSprite[Count].Speed += (0.05 * _->TimeScale);
				else Q_PntSprite->PntSprite[Count].Speed = 4 * (Q_PntSprite->PntSprite[Count].QA_EFF_INTENSITY/10);
			//	}
			//else
			//	{
			//	if(Q_PntSprite->PntSprite[Count].Speed + (0.05 * _->TimeScale) < 4 * (Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].JINK3_PowerFactor/1000)) Q_PntSprite->PntSprite[Count].Speed += (0.05 * _->TimeScale);
			//	else Q_PntSprite->PntSprite[Count].Speed = 4 * (Q_Forge->Forge[Q_PntSprite->PntSprite[Count].AvID].JINK3_PowerFactor/1000);
			//	}

			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert1, Q_PntSprite->PntSprite[Count].Speed*6*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert1);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert2, Q_PntSprite->PntSprite[Count].Speed*6*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert2);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert3, Q_PntSprite->PntSprite[Count].Speed*6*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert3);

			//### Store Alpha
			Q_PntSprite->PntSprite[Count].AlphaSTR = Q_PntSprite->PntSprite[Count].Alpha;

			//## Store Pos
			Q_PntSprite->PntSprite[Count].Vert1STR = Q_PntSprite->PntSprite[Count].Vert1;
			Q_PntSprite->PntSprite[Count].Vert2STR = Q_PntSprite->PntSprite[Count].Vert2;
			Q_PntSprite->PntSprite[Count].Vert3STR = Q_PntSprite->PntSprite[Count].Vert3;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lverts[0].x = Q_PntSprite->PntSprite[Count].Vert1STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[0].y = Q_PntSprite->PntSprite[Count].Vert1STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[0].z = Q_PntSprite->PntSprite[Count].Vert1STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[0].u = 0;
			Q_PntSprite->PntSprite[Count].Lverts[0].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[0].r = 255;
			Q_PntSprite->PntSprite[Count].Lverts[0].g = 255;
			Q_PntSprite->PntSprite[Count].Lverts[0].b = 255;
			Q_PntSprite->PntSprite[Count].Lverts[0].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[1].x = Q_PntSprite->PntSprite[Count].Vert2STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[1].y = Q_PntSprite->PntSprite[Count].Vert2STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[1].z = Q_PntSprite->PntSprite[Count].Vert2STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[1].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].r = 255;
			Q_PntSprite->PntSprite[Count].Lverts[1].g = 255;
			Q_PntSprite->PntSprite[Count].Lverts[1].b = 255;
			Q_PntSprite->PntSprite[Count].Lverts[1].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[2].x = Q_PntSprite->PntSprite[Count].Vert3STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[2].y = Q_PntSprite->PntSprite[Count].Vert3STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[2].z = Q_PntSprite->PntSprite[Count].Vert3STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[2].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[2].v = 0;
			Q_PntSprite->PntSprite[Count].Lverts[2].r = 255;
			Q_PntSprite->PntSprite[Count].Lverts[2].g = 255;
			Q_PntSprite->PntSprite[Count].Lverts[2].b = 255;
			Q_PntSprite->PntSprite[Count].Lverts[2].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lverts[0], 3, Medias->QAEFF27, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			//##### Sprite Trail 1
			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert1STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert1STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert2STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert2STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert3STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert3STR);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 20 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 20;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lverts[0].x = Q_PntSprite->PntSprite[Count].Vert1STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[0].y = Q_PntSprite->PntSprite[Count].Vert1STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[0].z = Q_PntSprite->PntSprite[Count].Vert1STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[0].u = 0;
			Q_PntSprite->PntSprite[Count].Lverts[0].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[0].r = 200;
			Q_PntSprite->PntSprite[Count].Lverts[0].g = 200;
			Q_PntSprite->PntSprite[Count].Lverts[0].b = 200;
			Q_PntSprite->PntSprite[Count].Lverts[0].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[1].x = Q_PntSprite->PntSprite[Count].Vert2STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[1].y = Q_PntSprite->PntSprite[Count].Vert2STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[1].z = Q_PntSprite->PntSprite[Count].Vert2STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[1].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].r = 200;
			Q_PntSprite->PntSprite[Count].Lverts[1].g = 200;
			Q_PntSprite->PntSprite[Count].Lverts[1].b = 200;
			Q_PntSprite->PntSprite[Count].Lverts[1].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[2].x = Q_PntSprite->PntSprite[Count].Vert3STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[2].y = Q_PntSprite->PntSprite[Count].Vert3STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[2].z = Q_PntSprite->PntSprite[Count].Vert3STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[2].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[2].v = 0;
			Q_PntSprite->PntSprite[Count].Lverts[2].r = 200;
			Q_PntSprite->PntSprite[Count].Lverts[2].g = 200;
			Q_PntSprite->PntSprite[Count].Lverts[2].b = 200;
			Q_PntSprite->PntSprite[Count].Lverts[2].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lverts[0], 3, Medias->QAEFF27, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			//##### Sprite Trail 2
			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert1STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert1STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert2STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert2STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert3STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert3STR);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 20 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 20;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lverts[0].x = Q_PntSprite->PntSprite[Count].Vert1STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[0].y = Q_PntSprite->PntSprite[Count].Vert1STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[0].z = Q_PntSprite->PntSprite[Count].Vert1STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[0].u = 0;
			Q_PntSprite->PntSprite[Count].Lverts[0].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[0].r = 150;
			Q_PntSprite->PntSprite[Count].Lverts[0].g = 150;
			Q_PntSprite->PntSprite[Count].Lverts[0].b = 150;
			Q_PntSprite->PntSprite[Count].Lverts[0].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[1].x = Q_PntSprite->PntSprite[Count].Vert2STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[1].y = Q_PntSprite->PntSprite[Count].Vert2STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[1].z = Q_PntSprite->PntSprite[Count].Vert2STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[1].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].r = 150;
			Q_PntSprite->PntSprite[Count].Lverts[1].g = 150;
			Q_PntSprite->PntSprite[Count].Lverts[1].b = 150;
			Q_PntSprite->PntSprite[Count].Lverts[1].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[2].x = Q_PntSprite->PntSprite[Count].Vert3STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[2].y = Q_PntSprite->PntSprite[Count].Vert3STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[2].z = Q_PntSprite->PntSprite[Count].Vert3STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[2].u = 0;
			Q_PntSprite->PntSprite[Count].Lverts[2].v = 0;
			Q_PntSprite->PntSprite[Count].Lverts[2].r = 150;
			Q_PntSprite->PntSprite[Count].Lverts[2].g = 150;
			Q_PntSprite->PntSprite[Count].Lverts[2].b = 150;
			Q_PntSprite->PntSprite[Count].Lverts[2].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lverts[0], 3, Medias->QAEFF27, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			//##### Sprite Trail 3
			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert1STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert1STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert2STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert2STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert3STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert3STR);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 20 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 20;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lverts[0].x = Q_PntSprite->PntSprite[Count].Vert1STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[0].y = Q_PntSprite->PntSprite[Count].Vert1STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[0].z = Q_PntSprite->PntSprite[Count].Vert1STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[0].u = 0;
			Q_PntSprite->PntSprite[Count].Lverts[0].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[0].r = 100;
			Q_PntSprite->PntSprite[Count].Lverts[0].g = 100;
			Q_PntSprite->PntSprite[Count].Lverts[0].b = 100;
			Q_PntSprite->PntSprite[Count].Lverts[0].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[1].x = Q_PntSprite->PntSprite[Count].Vert2STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[1].y = Q_PntSprite->PntSprite[Count].Vert2STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[1].z = Q_PntSprite->PntSprite[Count].Vert2STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[1].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].r = 100;
			Q_PntSprite->PntSprite[Count].Lverts[1].g = 100;
			Q_PntSprite->PntSprite[Count].Lverts[1].b = 100;
			Q_PntSprite->PntSprite[Count].Lverts[1].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[2].x = Q_PntSprite->PntSprite[Count].Vert3STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[2].y = Q_PntSprite->PntSprite[Count].Vert3STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[2].z = Q_PntSprite->PntSprite[Count].Vert3STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[2].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[2].v = 0;
			Q_PntSprite->PntSprite[Count].Lverts[2].r = 100;
			Q_PntSprite->PntSprite[Count].Lverts[2].g = 100;
			Q_PntSprite->PntSprite[Count].Lverts[2].b = 100;
			Q_PntSprite->PntSprite[Count].Lverts[2].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lverts[0], 3, Medias->QAEFF27, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			//##### Sprite Trail 4
			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert1STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert1STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert2STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert2STR);
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Vert3STR, -Q_PntSprite->PntSprite[Count].Speed*2*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Vert3STR);

			if(Q_PntSprite->PntSprite[Count].AlphaSTR - 20 >= 0) Q_PntSprite->PntSprite[Count].AlphaSTR -= 20;

			//##### Render Main Sprite
			Q_PntSprite->PntSprite[Count].Lverts[0].x = Q_PntSprite->PntSprite[Count].Vert1STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[0].y = Q_PntSprite->PntSprite[Count].Vert1STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[0].z = Q_PntSprite->PntSprite[Count].Vert1STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[0].u = 0;
			Q_PntSprite->PntSprite[Count].Lverts[0].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[0].r = 50;
			Q_PntSprite->PntSprite[Count].Lverts[0].g = 50;
			Q_PntSprite->PntSprite[Count].Lverts[0].b = 50;
			Q_PntSprite->PntSprite[Count].Lverts[0].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[1].x = Q_PntSprite->PntSprite[Count].Vert2STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[1].y = Q_PntSprite->PntSprite[Count].Vert2STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[1].z = Q_PntSprite->PntSprite[Count].Vert2STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[1].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].v = 1;
			Q_PntSprite->PntSprite[Count].Lverts[1].r = 50;
			Q_PntSprite->PntSprite[Count].Lverts[1].g = 50;
			Q_PntSprite->PntSprite[Count].Lverts[1].b = 50;
			Q_PntSprite->PntSprite[Count].Lverts[1].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Q_PntSprite->PntSprite[Count].Lverts[2].x = Q_PntSprite->PntSprite[Count].Vert3STR.x;
			Q_PntSprite->PntSprite[Count].Lverts[2].y = Q_PntSprite->PntSprite[Count].Vert3STR.y;
			Q_PntSprite->PntSprite[Count].Lverts[2].z = Q_PntSprite->PntSprite[Count].Vert3STR.z;
			Q_PntSprite->PntSprite[Count].Lverts[2].u = 1;
			Q_PntSprite->PntSprite[Count].Lverts[2].v = 0;
			Q_PntSprite->PntSprite[Count].Lverts[2].r = 50;
			Q_PntSprite->PntSprite[Count].Lverts[2].g = 50;
			Q_PntSprite->PntSprite[Count].Lverts[2].b = 50;
			Q_PntSprite->PntSprite[Count].Lverts[2].a = Q_PntSprite->PntSprite[Count].AlphaSTR;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lverts[0], 3, Medias->QAEFF27, Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);

			} break;

		case 57:	//SOLID QA EFFECT REL ENERGY EFFICIENCY
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + (0.35*_->TimeScale) < 3) Q_PntSprite->PntSprite[Count].Speed += (0.35*_->TimeScale);
			else Q_PntSprite->PntSprite[Count].Speed = 6;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, (Q_PntSprite->PntSprite[Count].Speed*_->TimeScale), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 58:	//SOLID QA EFFECT REL ENERGY EFFICIENCY
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (1*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (1*_->TimeScale);
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + (0.55*_->TimeScale) < 6) Q_PntSprite->PntSprite[Count].Speed += (0.55*_->TimeScale);
			else Q_PntSprite->PntSprite[Count].Speed = 6;


			Q_PntSprite->PntSprite[Count].OldPos = Q_PntSprite->PntSprite[Count].Pos;

			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, (Q_PntSprite->PntSprite[Count].Speed*_->TimeScale), &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.005;

			if(Qpo->Collision_RayTest(//World,
				 NULL,
				 NULL,
				 &Q_PntSprite->PntSprite[Count].OldPos,
				 &Q_PntSprite->PntSprite[Count].Pos,
				 //GE_CONTENTS_CANNOT_OCCUPY,
				 //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,
				 0xffffffff, NULL, NULL,
				 &Q_PntSprite->PntSprite[Count].Collision))
				{
				if(Q_PntSprite->PntSprite[Count].Collision.Avatar == NULL)
					{
					Q_PntSprite->PntSprite[Count].Pos.acSet(Q_PntSprite->PntSprite[Count].Collision.Impact.m_X, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Y, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Z);
					Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
					}
				else
					{
					if(Q_PntSprite->PntSprite[Count].Collision.Avatar.IDflag != playerAV[g_Player]->Avatar.IDflag)
						{
						Q_PntSprite->PntSprite[Count].Pos.acSet(Q_PntSprite->PntSprite[Count].Collision.Impact.m_X, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Y, Q_PntSprite->PntSprite[Count].Collision.Impact.m_Z);
						Q_PntSprite->PntSprite[Count].TraVec = Q.PHY_BounceVector(Q_PntSprite->PntSprite[Count].TraVec, Q_PntSprite->PntSprite[Count].Collision.Plane.Normal);
						}
					}
				}

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->QAEFF04 , Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;


		case 59:		//Trail Sprites
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (35*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 20;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y -= (Q_PntSprite->PntSprite[Count].Speed/7)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y -= 0.09;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = 100;
			Q_PntSprite->PntSprite[Count].Lvert.g = 255;
			Q_PntSprite->PntSprite[Count].Lvert.b = 0;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Q_PntSprite->PntSprite[Count].MATCNT++;
			if(Q_PntSprite->PntSprite[Count].MATCNT < 0) Q_PntSprite->PntSprite[Count].MATCNT = 0;
			if(Q_PntSprite->PntSprite[Count].MATCNT > 25) Q_PntSprite->PntSprite[Count].MATCNT = 0;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->Star[Q_PntSprite->PntSprite[Count].MATCNT], Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;

		case 60:		//Trail Sprites
			{
			//### Progress Alpha
			if(Q_PntSprite->PntSprite[Count].Alpha - (3*_->TimeScale) > 0) Q_PntSprite->PntSprite[Count].Alpha -= (35*_->TimeScale);	//3  //25
			else
				{
				Q_PntSprite->PntSprite[Count].Alpha = 0;
				Q_PntSprite->PntSprite[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomPntSprite - 1)
					{
					Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
					K++;
					}

				_->NomPntSprite--;
				}

			if(Q_PntSprite->PntSprite[Count].Speed + 0.5*_->TimeScale < 20) Q_PntSprite->PntSprite[Count].Speed += 0.5*_->TimeScale;
			else Q_PntSprite->PntSprite[Count].Speed = 20;


			//### Move Sprite
			Qpo->Vec3d_AddScaled(&Q_PntSprite->PntSprite[Count].Pos, Q_PntSprite->PntSprite[Count].Speed*_->TimeScale, &Q_PntSprite->PntSprite[Count].TraVec, &Q_PntSprite->PntSprite[Count].Pos);

			Q_PntSprite->PntSprite[Count].Pos.y += (Q_PntSprite->PntSprite[Count].Speed/7)*_->TimeScale;

			Q_PntSprite->PntSprite[Count].TraVec.y += 0.09;

			Q_PntSprite->PntSprite[Count].Scale += 0.002;
	

			//##### Render Main Sprite

			Q_PntSprite->PntSprite[Count].Lvert.x = Q_PntSprite->PntSprite[Count].Pos.x;
			Q_PntSprite->PntSprite[Count].Lvert.y = Q_PntSprite->PntSprite[Count].Pos.y;
			Q_PntSprite->PntSprite[Count].Lvert.z = Q_PntSprite->PntSprite[Count].Pos.z;
			Q_PntSprite->PntSprite[Count].Lvert.r = Q_PntSprite->PntSprite[Count].IR;
			Q_PntSprite->PntSprite[Count].Lvert.g = Q_PntSprite->PntSprite[Count].IG;
			Q_PntSprite->PntSprite[Count].Lvert.b = Q_PntSprite->PntSprite[Count].IB;
			Q_PntSprite->PntSprite[Count].Lvert.a = Q_PntSprite->PntSprite[Count].Alpha;

			Q_PntSprite->PntSprite[Count].MATCNT++;
			if(Q_PntSprite->PntSprite[Count].MATCNT < 0) Q_PntSprite->PntSprite[Count].MATCNT = 0;
			if(Q_PntSprite->PntSprite[Count].MATCNT > 25) Q_PntSprite->PntSprite[Count].MATCNT = 0;

			Qpo->Poly_AddOnce(&Q_PntSprite->PntSprite[Count].Lvert, 1, Medias->Star[Q_PntSprite->PntSprite[Count].MATCNT], Q_PntSprite->PntSprite[Count].Type, Q_PntSprite->PntSprite[Count].RenderFlags, Q_PntSprite->PntSprite[Count].Scale);
			} break;
		}

	_->TimeScale = f_TimescaleMeM;
	}

void Q_COREFunctions::PntSpriteManagement(void)
	{
#if 1
	while(_->NomPntSprite > (Q_PntSprite->m_ArrayMx / 1.1555f))
		{
		helly = rand() % (_->NomPntSprite - 1);

		Q_PntSprite->PntSprite[helly].Alpha = 0;
		Q_PntSprite->PntSprite[helly].Live = 0;

		//### Array Reorder
		int K = helly;
		while(K < _->NomPntSprite - 1)
			{
			Q_PntSprite->PntSprite[K] = Q_PntSprite->PntSprite[K+1];
			K++;
			}

		_->NomPntSprite--;
		}
#else
	if(_->NomPntSprite >= Q_PntSprite->m_ArrayMx)
		{
		_->NomPntSprite = 0;
		}
#endif
	}
};