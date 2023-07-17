/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Spike Effect-

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
#include "Q-ENE-EnergyTypes.h"

using namespace GVARS;

namespace GVARS
{

void Q_EFFCon::Spike_ControlFrame(int Count)
	{
	switch(Q_HHSpike->HHSpike[Count].EffectType)
		{
		case 0:	//##### - Heavy Hit Spikes - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//### Conditionally Apply Gravity	//FROZEN
			//Q_HHSpike->HHSpike[Count].TraVec.y -= Q_HHSpike->HHSpike[Count].Gravity*_->TimeScale;

			//#### Move End Of Spike Outwards
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			if(Q_HHSpike->HHSpike[Count].MoveTail == 1) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].TailPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].TailPos);

			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween > 130) Q_HHSpike->HHSpike[Count].MoveTail = 1;


			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 70 < 255) Q_HHSpike->HHSpike[Count].AlpFade += 70;
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 255;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 6 > 0) Q_HHSpike->HHSpike[Count].AlpFade -= 6;
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomSpikes - 1)
						{
						Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
						K++;
						}

					_->NomSpikes--;
					}
				}


			//###### Increase Width
			if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 8) Q_HHSpike->HHSpike[Count].Width += 0.25;
			else Q_HHSpike->HHSpike[Count].Width = 8;

			//####### Draw Spike Tris
			if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].TailPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->HHSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 255, 255, 0);

			} break;


		case 1:	//##### - Hadou-ken Spikes - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//###### Move End Of Spike Outwards ######
			//### Check Distance
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween < 180) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			
			//### Follow Trajectory
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, (Q_HHSpike->HHSpike[Count].Speed*_->TimeScale)*50, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			Q_HHSpike->HHSpike[Count].FrontPos.x += Q_HHSpike->HHSpike[Count].IncX;
			Q_HHSpike->HHSpike[Count].FrontPos.y += Q_HHSpike->HHSpike[Count].IncY;
			Q_HHSpike->HHSpike[Count].FrontPos.z += Q_HHSpike->HHSpike[Count].IncZ;

			//### Clip to Spike distance
			Qpo->Vec3d_Subtract(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].OutVec);
			Qpo->Vec3d_Normalize(&Q_HHSpike->HHSpike[Count].OutVec);

			//#### Maintain Spike Start Positions
			Q_HHSpike->HHSpike[Count].CenterPos = Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].LightPos;
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);


			//### Randomly Alter Trajectory
			Q_HHSpike->HHSpike[Count].IncX += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncY += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncZ += ((((float)rand() / 32767)-0.5)/50);

			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 25 < 255)
					{
					Q_HHSpike->HHSpike[Count].AlpFade += 25;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 12;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 255;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					Q_HHSpike->HHSpike[Count].Width = 8;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 25 > 0)
					{
					Q_HHSpike->HHSpike[Count].AlpFade -= 25;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width - 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 0;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].FadeDir = 0;
					Q_HHSpike->HHSpike[Count].Width = 0;
					}
				}
			
			//####### Draw Spike Tris
			if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->HADSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 255, 255, 0);

			if(Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].Live == 0)
				{
				Q_HHSpike->HHSpike[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomSpikes - 1)
					{
					Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
					K++;
					}

				_->NomSpikes--;
				}
			} break;


		case 2:	//##### - Spawn Spikes - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//### Conditionally Apply Gravity	//FROZEN
			//Q_HHSpike->HHSpike[Count].TraVec.y -= Q_HHSpike->HHSpike[Count].Gravity*_->TimeScale;

			//#### Move End Of Spike Outwards
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			if(Q_HHSpike->HHSpike[Count].MoveTail == 1) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].TailPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].TailPos);

			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween > 130) Q_HHSpike->HHSpike[Count].MoveTail = 1;


			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 70 < 255) Q_HHSpike->HHSpike[Count].AlpFade += 70;
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 255;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 6 > 0) Q_HHSpike->HHSpike[Count].AlpFade -= 6;
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].Live = 0;

					//### Array Reorder
					int K = Count;
					while(K < _->NomSpikes - 1)
						{
						Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
						K++;
						}

					_->NomSpikes--;
					}
				}


			//###### Increase Width
			if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 8) Q_HHSpike->HHSpike[Count].Width += 0.25;
			else Q_HHSpike->HHSpike[Count].Width = 8;

			//####### Draw Spike Tris
			if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].TailPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->SPAWNSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 255, 255, 0);

			} break;


		case 3:	//##### - Trail Spikes - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//###### Move End Of Spike Outwards ######
			//### Check Distance
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween < 180) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			
			//### Follow Trajectory
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, (Q_HHSpike->HHSpike[Count].Speed*_->TimeScale)*50, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			Q_HHSpike->HHSpike[Count].FrontPos.x += Q_HHSpike->HHSpike[Count].IncX;
			Q_HHSpike->HHSpike[Count].FrontPos.y += Q_HHSpike->HHSpike[Count].IncY;
			Q_HHSpike->HHSpike[Count].FrontPos.z += Q_HHSpike->HHSpike[Count].IncZ;

			//### Clip to Static distance
			Qpo->Vec3d_Subtract(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].OutVec);
			Qpo->Vec3d_Normalize(&Q_HHSpike->HHSpike[Count].OutVec);

			//#### Maintain Spike Start Positions
			//Q_HHSpike->HHSpike[Count].CenterPos = player[g_Player]->AttPos.Translation;
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			//#### Maintain Spike Start Positions
			Q_HHSpike->HHSpike[Count].CenterPos = Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].LightPos;
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			//### Randomly Alter Trajectory
			Q_HHSpike->HHSpike[Count].IncX += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncY += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncZ += ((((float)rand() / 32767)-0.5)/50);

			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 10 < 170)	//100	//25  255
					{
					Q_HHSpike->HHSpike[Count].AlpFade += 10;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 12;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 170;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					Q_HHSpike->HHSpike[Count].Width = 8;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 10 > 0)
					{
					Q_HHSpike->HHSpike[Count].AlpFade -= 10;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width - 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 0;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].FadeDir = 0;
					Q_HHSpike->HHSpike[Count].Width = 0;
					}
				}
			
			//####### Draw Spike Tris
			if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->HADSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 130, 130, 0);

			if(Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].Live == 0)
				{
				player[g_Player]->JSSpikes = 0;
				Q_HHSpike->HHSpike[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomSpikes - 1)
					{
					Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
					K++;
					}

				_->NomSpikes--;
				}
			} break;


		case 4:	//##### - AI Trail Spikes - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//###### Move End Of Spike Outwards ######
			//### Check Distance
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween < 180) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			
			//### Follow Trajectory
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, (Q_HHSpike->HHSpike[Count].Speed*_->TimeScale)*50, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			Q_HHSpike->HHSpike[Count].FrontPos.x += Q_HHSpike->HHSpike[Count].IncX;
			Q_HHSpike->HHSpike[Count].FrontPos.y += Q_HHSpike->HHSpike[Count].IncY;
			Q_HHSpike->HHSpike[Count].FrontPos.z += Q_HHSpike->HHSpike[Count].IncZ;

			//### Clip to Static distance
			Qpo->Vec3d_Subtract(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].OutVec);
			Qpo->Vec3d_Normalize(&Q_HHSpike->HHSpike[Count].OutVec);

			//#### Maintain Spike Start Positions
			Q_HHSpike->HHSpike[Count].CenterPos = Q_Forge->Forge[Q_HHSpike->HHSpike[Count].AvID].AttPos.Translation;
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);


			//### Randomly Alter Trajectory
			Q_HHSpike->HHSpike[Count].IncX += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncY += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncZ += ((((float)rand() / 32767)-0.5)/50);

			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 25 < 170)
					{
					Q_HHSpike->HHSpike[Count].AlpFade += 25;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 12;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 170;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					Q_HHSpike->HHSpike[Count].Width = 8;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 25 > 0)
					{
					Q_HHSpike->HHSpike[Count].AlpFade -= 25;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width - 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 0;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].FadeDir = 0;
					Q_HHSpike->HHSpike[Count].Width = 0;
					}
				}
			
			//####### Draw Spike Tris
			//if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->HADSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 255, 255, 0);

			if(Q_Forge->Forge[Q_HHSpike->HHSpike[Count].AvID].attackon == 0 || Q_Forge->Forge[Q_HHSpike->HHSpike[Count].AvID].HitLethal == 0)
				{
				Q_Forge->Forge[Q_HHSpike->HHSpike[Count].AvID].JSSpikes = 0;
				Q_HHSpike->HHSpike[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomSpikes - 1)
					{
					Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
					K++;
					}

				_->NomSpikes--;
				}
			} break;


		case 5:	//##### - Trail Spikes (Small) - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//###### Move End Of Spike Outwards ######
			//### Check Distance
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween < 180) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			
			//### Follow Trajectory
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, (Q_HHSpike->HHSpike[Count].Speed*_->TimeScale)*50, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			Q_HHSpike->HHSpike[Count].FrontPos.x += Q_HHSpike->HHSpike[Count].IncX;
			Q_HHSpike->HHSpike[Count].FrontPos.y += Q_HHSpike->HHSpike[Count].IncY;
			Q_HHSpike->HHSpike[Count].FrontPos.z += Q_HHSpike->HHSpike[Count].IncZ;

			//### Clip to Static distance
			Qpo->Vec3d_Subtract(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].OutVec);
			Qpo->Vec3d_Normalize(&Q_HHSpike->HHSpike[Count].OutVec);

			//#### Maintain Spike Start Positions
			//Q_HHSpike->HHSpike[Count].CenterPos = player[g_Player]->AttPos.Translation;
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			//#### Maintain Spike Start Positions
			Q_HHSpike->HHSpike[Count].CenterPos = Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].LightPos;
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			//### Randomly Alter Trajectory
			Q_HHSpike->HHSpike[Count].IncX += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncY += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncZ += ((((float)rand() / 32767)-0.5)/50);

			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 10 < 170)	//25  255
					{
					Q_HHSpike->HHSpike[Count].AlpFade += 10;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 12;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 170;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					Q_HHSpike->HHSpike[Count].Width = 8;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 10 > 0)
					{
					Q_HHSpike->HHSpike[Count].AlpFade -= 10;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width - 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 0;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].FadeDir = 0;
					Q_HHSpike->HHSpike[Count].Width = 0;
					}
				}

			Q_HHSpike->HHSpike[Count].Width = 1;
			
			//####### Draw Spike Tris
			if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->HADSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 255, 255, 0);

			if(Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].Live == 0)
				{
				player[g_Player]->JSSpikes = 0;
				Q_HHSpike->HHSpike[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomSpikes - 1)
					{
					Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
					K++;
					}

				_->NomSpikes--;
				}
			} break;


		case 6:	//##### - AI Trail Spikes HUGE - #####
			{
			//## Increment Timer (Unused)
			Q_HHSpike->HHSpike[Count].Timer++;

			//###### Move End Of Spike Outwards ######
			//### Check Distance
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			if(Q_HHSpike->HHSpike[Count].DistBetween < 180) Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, Q_HHSpike->HHSpike[Count].Speed*_->TimeScale, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);
			Q_HHSpike->HHSpike[Count].DistBetween = Qpo->Vec3d_DistanceBetween(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos);
			
			//### Follow Trajectory
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].FrontPos, (Q_HHSpike->HHSpike[Count].Speed*_->TimeScale)*50, &Q_HHSpike->HHSpike[Count].TraVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			Q_HHSpike->HHSpike[Count].FrontPos.x += Q_HHSpike->HHSpike[Count].IncX;
			Q_HHSpike->HHSpike[Count].FrontPos.y += Q_HHSpike->HHSpike[Count].IncY;
			Q_HHSpike->HHSpike[Count].FrontPos.z += Q_HHSpike->HHSpike[Count].IncZ;

			//### Clip to Static distance
			Qpo->Vec3d_Subtract(&Q_HHSpike->HHSpike[Count].FrontPos, &Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].OutVec);
			Qpo->Vec3d_Normalize(&Q_HHSpike->HHSpike[Count].OutVec);

			//#### Maintain Spike Start Positions
			//Q_HHSpike->HHSpike[Count].CenterPos = Q_Forge->Forge[Q_HHSpike->HHSpike[Count].AvID].AttPos.Translation;
			//Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);

			//#### Maintain Spike Start Positions
			Q_HHSpike->HHSpike[Count].CenterPos = Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].LightPos;
			Qpo->Vec3d_AddScaled(&Q_HHSpike->HHSpike[Count].CenterPos, Q_HHSpike->HHSpike[Count].DistBetween, &Q_HHSpike->HHSpike[Count].OutVec, &Q_HHSpike->HHSpike[Count].FrontPos);


			//### Randomly Alter Trajectory
			Q_HHSpike->HHSpike[Count].IncX += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncY += ((((float)rand() / 32767)-0.5)/50);
			Q_HHSpike->HHSpike[Count].IncZ += ((((float)rand() / 32767)-0.5)/50);

			//##### Alpha Control
			if(Q_HHSpike->HHSpike[Count].FadeDir == 0)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade + 25 < 170)
					{
					Q_HHSpike->HHSpike[Count].AlpFade += 25;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width + 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 12;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 170;
					Q_HHSpike->HHSpike[Count].FadeDir = 1;
					Q_HHSpike->HHSpike[Count].Width = 8;
					}
				}

			if(Q_HHSpike->HHSpike[Count].FadeDir == 1)
				{
				if(Q_HHSpike->HHSpike[Count].AlpFade - 25 > 0)
					{
					Q_HHSpike->HHSpike[Count].AlpFade -= 25;
					//###### Increase Width
					if(Q_HHSpike->HHSpike[Count].Width - 0.25 < 12) Q_HHSpike->HHSpike[Count].Width += 0.25;
					else Q_HHSpike->HHSpike[Count].Width = 0;
					}
				else
					{
					Q_HHSpike->HHSpike[Count].AlpFade = 0;
					Q_HHSpike->HHSpike[Count].FadeDir = 0;
					Q_HHSpike->HHSpike[Count].Width = 0;
					}
				}

			Q_HHSpike->HHSpike[Count].Width = 120;
			
			//####### Draw Spike Tris
			if(Q_HHSpike->HHSpike[Count].AlpFade > 0) Q.ShowLine(&Q_HHSpike->HHSpike[Count].CenterPos, &Q_HHSpike->HHSpike[Count].FrontPos, &player[g_Player]->ViewXForm.Translation, Q_HHSpike->HHSpike[Count].Width, Medias->HADSpikeBmp, Q_HHSpike->HHSpike[Count].AlpFade, 255, 255, 255, 0);

			if(Q_LEnergy->LEnergy[Q_HHSpike->HHSpike[Count].EnergyID].Live == 0)
				{
				Q_Forge->Forge[Q_HHSpike->HHSpike[Count].AvID].JSSpikes = 0;
				Q_HHSpike->HHSpike[Count].Live = 0;

				//### Array Reorder
				int K = Count;
				while(K < _->NomSpikes - 1)
					{
					Q_HHSpike->HHSpike[K] = Q_HHSpike->HHSpike[K+1];
					K++;
					}

				_->NomSpikes--;
				}
			} break;
		}
	}

};