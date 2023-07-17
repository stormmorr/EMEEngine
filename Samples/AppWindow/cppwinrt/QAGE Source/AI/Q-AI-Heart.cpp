/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Nueral Net Functions-
	*/#include "pch.h"/*- Minor Component -Player Spawn NNbot-

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
#include "Q-WE-PntSprite.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-WE-CloudControl.h"
#include "Q-Structs.h"
#include "Q-WE-MeleeHits.h"
#include "Q-CORE-Avatar.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-AI-NNbot.h"

using namespace GVARS;

namespace GVARS
{


void Q_COREFunctions::AIFighterHeart(int AIcounter)
{
	//Explicit MEMORY
	int exMeM_LOCKON = 0;
	int exMeM_TargetLOCK = 0;
	int exMeM_TargetLOCKID = 0;

	if(Q_Forge->Forge[AIcounter].HB_Dead == 0)
		{
		Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter++;
		if(!Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime && Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter > 65)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = true;
			Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
			}

		Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcounter++;
		if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST == 0 ||
		   Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcounter > 155)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcountON = false;
			}
	
		//Target DEADLOCK
		if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
			{
			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID < _->NomAI)
				{
				if(Q_Forge->Forge[Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID].HB_Dead == 0)
					{
					exMeM_LOCKON = 1;
					exMeM_TargetLOCK = Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK;
					exMeM_TargetLOCKID = Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID;

					/*if(Q_Forge->Forge[AIcounter].ScanAvatarDist < 170)	//Long Range
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
						}
					else												//Hand To Hand
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime &&
						   Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 &&
						   Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
							}
						}*/

					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST > 0)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcounter >= 15 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcounter < 45)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LOOK;
							}

						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcounter >= 45)
							{
							exMeM_LOCKON = 0;
							exMeM_TargetLOCK = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 0;
							exMeM_TargetLOCKID = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = 0;
							//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
							}
						}
					}
				}
			}

		//#####--  Avatar View Scan  --#####//
		if(Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK == 1)
			{
			//### Avatar Scans View
			Q.AIFunctionsScannerCheck(AIcounter);

			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 0;
			}

		//#####-- Pulse --#####//
		Q_Forge->Forge[AIcounter].Q_Heart.HeartIncrement -= Q_Forge->Forge[AIcounter].Q_Heart.PulseRate;

		//#####-- Brain --#####//
		if(Q_Forge->Forge[AIcounter].Q_Heart.HeartIncrement < 0)
			{
			Q.AIFighterBrain(AIcounter);
			//HeartIncrement += Q_Forge->Forge[AIcounter].Q_Heart.PulseRate;
			Q_Forge->Forge[AIcounter].Q_Heart.HeartIncrement += 1;
			}

		//#####-- Calculate Chemical State --#####//
		Q.AIChemicalCalc(AIcounter);

		//#####-- Fatigue --#####//
		//Q_Forge->Forge[AIcounter].Q_Heart.PulseRate = Q_Forge->Forge[AIcounter].Q_Heart.Metabolism * ;
		//Q_Forge->Forge[AIcounter].Q_Heart.Endurance = Q_Forge->Forge[AIcounter].Q_Heart.Metabolism / Q_Forge->Forge[AIcounter].Q_Heart.EnduranceIncrement;
		//Q_Forge->Forge[AIcounter].Q_Heart.EnduranceIncrement += 1;
		//Q_Forge->Forge[AIcounter].Q_Heart.EnduranceIncrement -= Q_Forge->Forge[AIcounter].Q_Heart.Metabolism / Q_Forge->Forge[AIcounter].Q_Heart.PulseRate;
	#pragma message("FIXME:::perhaps add define solids for the body sets")

		// Set Increments

		switch(Q_Forge->Forge[AIcounter].Role)	//####- Switch Avatar's Current Role
			{
			case 0:	//## Standard Freelance Mode
				{
				switch(Q_Forge->Forge[AIcounter].Q_Brain.LocationState) //####- Switch Avatar's Current Location Mode
					{
					case 0:	//## Initialisation Mode Avatar Just Spawned or reset
						{
						} break;

					}
				} break;


			case 1:	//## Active Team Mode
				{
				switch(Q_Forge->Forge[AIcounter].Q_Brain.LocationState)
					{

					case 0:	//## Initialisation Mode Avatar Just Spawned or reset
						{

							//### Leader Is Present
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1) Q_Forge->Forge[AIcounter].Q_Brain.LocationState = 1;

						} break;


					case 1:
						{
							//### Not Locked Onto Enemy Then Lock On the Leader
						if((Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1) || (Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 1500))
							{
							Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
							Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 3;
							if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
							if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

							Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 3);
							Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						
							//Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							//Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
							//Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
							//Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
							//Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;

							Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;


							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist > 80)
								{

								if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist < 160 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))
									{
									//### Walk Towards Player
									Q_Forge->Forge[AIcounter].ForwardSpeed = 2*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
									Q_Forge->Forge[AIcounter].Running = 0;

									if(Q_Forge->Forge[AIcounter].Mposestate != 1 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//Movement mode switch
										{
										Q_Forge->Forge[AIcounter].Mposestate = 1;
										Q_Forge->Forge[AIcounter].StepTimer = 0;
										//Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].runposecnt = 0;
										//Q_Forge->Forge[AIcounter].idleposecnt = 0;
										}
									}
								else
									{
									//### Run Towards Player
									Q_Forge->Forge[AIcounter].ForwardSpeed = 8*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
									Q_Forge->Forge[AIcounter].Running = 1;

									if(Q_Forge->Forge[AIcounter].Mposestate != 3 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//Movement mode switch
										{
										Q_Forge->Forge[AIcounter].Mposestate = 3;
										Q_Forge->Forge[AIcounter].StepTimer = 0;
										//Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
										//Q_Forge->Forge[AIcounter].runposecnt = 0;
										//Q_Forge->Forge[AIcounter].idleposecnt = 0;
										}
									}

								//*** Actor
								Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
								Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

								Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
								Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

								// This does collision detection
								if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
									{ /*Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Collision.Impact;*/ Q_Forge->Forge[AIcounter].collide = 1; }

								Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
								Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
					
								// Set the player to the new pos
								if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
								}
							else
								{
								Q_Forge->Forge[AIcounter].Running = 0;

								if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 0)
									{
									Q_Forge->Forge[AIcounter].Mposestate = 0;
									//Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].runposecnt = 0;
									//Q_Forge->Forge[AIcounter].idleposecnt = 0;
									}
								}
							}
						else
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist > 100 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))
								{
								//### Run Towards Player
								Q_Forge->Forge[AIcounter].ForwardSpeed = 8*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
								Q_Forge->Forge[AIcounter].Running = 1;
							
								if(Q_Forge->Forge[AIcounter].Mposestate != 3 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//Movement mode switch
									{
									Q_Forge->Forge[AIcounter].Mposestate = 3;
									Q_Forge->Forge[AIcounter].StepTimer = 0;
									//Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].runposecnt = 0;
									//Q_Forge->Forge[AIcounter].idleposecnt = 0;
									}

								//*** Actor
								Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;

								Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].Pos, &Q_Forge->Forge[AIcounter].AV.Xform.Translation, &Q_Forge->Forge[AIcounter].AV.Up);
								Q_Forge->Forge[AIcounter].AV.Up.y = 0;
								Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].AV.Up);
								Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Up);


								Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

								Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
								Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

								// This does collision detection
								if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
									{ /*Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Collision.Impact;*/ Q_Forge->Forge[AIcounter].collide = 1; }

								Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
								Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
												
								// Set the player to the new pos
								if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
								}
							else
								{
								Q_Forge->Forge[AIcounter].Running = 0;

								if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 0)
									{
									Q_Forge->Forge[AIcounter].Mposestate = 0;
									//Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
									//Q_Forge->Forge[AIcounter].runposecnt = 0;
									//Q_Forge->Forge[AIcounter].idleposecnt = 0;
									}
								}
							}

						} break;

					}
				} break;


			case 2:	//Sentry Mode
				{
				switch(Q_Forge->Forge[AIcounter].Q_Brain.LocationState)
					{


					}
				} break;


			case 3:	//Search and Destroy Mode
				{
				switch(Q_Forge->Forge[AIcounter].Q_Brain.LocationState)
					{



					}
				} break;

			}//END Role Switch

		//Explicit MEMORY
		if(exMeM_LOCKON)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = exMeM_TargetLOCK;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = exMeM_TargetLOCKID;
			}
		}
}

void Q_COREFunctions::AIChemicalCalc(int AIcounter)
{
	Q_Forge->Forge[AIcounter].Q_Heart.Metabolism = 23;

	/*for(int i_Iter = 0; i_Iter < Q_Forge->Forge[AIcounter].Q_Heart.nomChemicals; i_Iter++)
		{
		if(Q_Forge->Forge[AIcounter].Q_Heart.Contamination[i_Iter].Potency > 0)
			{
			float		PulseRate;
			float		Reactions;
			float		Metabolism;
			float		Endurance;
			float		AblDecisive;
			float		AblForgive;
			float		Manic;

			Q_Forge->Forge[AIcounter].Q_Brain.TestKEY1 Aggression += Q_Forge->Forge[AIcounter].Q_Heart.Contamination[i_Iter].Aggression;

			float		EnergyEff;
			float		Strength;
			float		Focus;

			Q_Forge->Forge[AIcounter].Q_Heart.Contamination[i_Iter].Potency -= 1 * Q_Forge->Forge[AIcounter].Q_Heart.Contamination[i_Iter].BurnRate;
			}
		}*/
}

};